/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2002 Meilhaus Electronic GmbH                                                      */
/*  Author:         kh                                                                                      */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com in special www.amcc.com/TechLib/pcidev.htm)                               */
/*                                                                                                          */
/*  Description:    EMS example                                                                             */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                  Some input or output signals have to be convert !!                                      */
/*                  This is not a full working application, it should show, how you can determine the       */
/*                  resources and programming some registers                                                */
/*                  For internal reasons we are not in a position to publish the whole register description */
/*                  You can use the samples "as is" Meilhaus Electronic offers no support on this samples   */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    001005  kh      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/

// This example shows the how you can programm the ME2600
// to store collect data and store it in file. The example
// uses a large EMS buffer to help ensure that no data is
// lost even at very high acquisition rates.

// This example was wriiten for BorlandC 3.1 compiler.

// The data is stored multiplexed in the data file.

// You can change the behaviour of this example, by changing
// the values of the defines and constants below.

// Standard includes

#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <memory.h>
#include <alloc.h>

#include <graphics.h>

// Include-file for register defines and init routine

#include "..\me2600.h"

// You can force the ME2600 board to use a particular port address or a
// particular interrupt by changing the values for required_me2600_port
// and required_irq_line below. The value '0' means, in both cases, use
// the default values assigned by the system.


#define REQUIRED_ME2600_PORT                        0   // 0 = Use default

#define REQUIRED_IRQ_LINE                           0   // 0 = Use default

// Change the define 'NO_OF_AD_CHANNELS' and the contents of the arrays
// 'ad_channel_no', 'ad_channel_gain', 'ad_channel_polarity' and
// ad_channel_mode below, if required, to influence the AD acquisition.

#define NO_OF_AD_CHANNELS                           4   // Maximum 16 (0 - 15)

unsigned short ad_channel_no[NO_OF_AD_CHANNELS]     = {0, 1, 2, 3};

unsigned short ad_channel_gain[NO_OF_AD_CHANNELS]   = { ME2600_AD_GAIN_1,
                                                        ME2600_AD_GAIN_2,
                                                        ME2600_AD_GAIN_4,
                                                        ME2600_AD_GAIN_8            };

int ad_channel_polarity[NO_OF_AD_CHANNELS]          = { ME2600_AD_BIPOLAR,
                                                        ME2600_AD_BIPOLAR,
                                                        ME2600_AD_BIPOLAR,
                                                        ME2600_AD_BIPOLAR           };

int ad_channel_mode[NO_OF_AD_CHANNELS]              = { ME2600_AD_SINGLE_ENDED,
                                                        ME2600_AD_SINGLE_ENDED,
                                                        ME2600_AD_SINGLE_ENDED,
                                                        ME2600_AD_SINGLE_ENDED      };

double ad_scan_sum_sampling_rate                    = 100000;   // Sum sampling rate in Hz - change if required
                                                                // Maximum 300000 Hz

// Name of the file in which the sampled data will be stored,
// Cahnge if required.

char sz_file_name[]                                 = "me2600.edt";

////////////////////////////////////////////////////////////////////////
//      No user changeable defines and constants below this point     //
////////////////////////////////////////////////////////////////////////

// Previous interrupt handler

void interrupt (*fnc_prev_irq_handler) (void);

// Forward declaration for IRQ Handler

void interrupt IRQHandler(void);

// Forward declarations for the EMS functions used here

int EMSIsInstalled(void);

int EMSGetPageFrameSegment(int* p_frame_segment);

int EMSAllocatePages(int no_pages, int* p_ems_handle);

int EMSMapExpandedMemoryPage(int handle, int physical_page, int logical_page);

int EMSReleasePages(int handle);

// Global variables used in interrupt

long l_next_write_offset;

int i_current_logical_write_page;

unsigned short us_me2600_port   = REQUIRED_ME2600_PORT;

unsigned char uc_irq_line       = REQUIRED_IRQ_LINE;

unsigned short us_plx_port;

int i_ems_handle;

int i_ems_frame_segment;

unsigned short* p_write_pointer;

int i_buffer_rollovers;

int i_data_lost;

int main(void)
{
    double d_latch_reg;

    unsigned long ul_scan_latch_reg;

    unsigned long us_sample_latch_reg;

    unsigned char uc_irq_vector;

    int index;

    unsigned short* p_read_pointer;

    unsigned long ul_total_stored_values;

    int i_next_logical_read_page;

    FILE* p_file;

    unsigned int init_error;

    int i_current_logical_read_page;

    unsigned int ui_remaining_values;

    ////////////////////////////////////////////////////////////////////////////////
    //          Attempt to reserve 1 Mb (64 16 Kb pages) of EMS Memory            //
    ////////////////////////////////////////////////////////////////////////////////

    // First we inquire if EMS support is available

    if(EMSIsInstalled() != 0)
    {
        // No EMS support is installed on the system

        printf("No EMS support available\n");

        return(-1);
    }

    // Now determine the page frame segment for EMS access

    if(EMSGetPageFrameSegment(&i_ems_frame_segment) != 0)
    {
        // For some reason we couldn't obtain the EMS page frame segment.
        // We are unable to continue

        printf("Unable to obtain EMS page frame segment\n");

        return(-1);
    }

    // We will write to the data buffer in the interrupt routine using the
    // first physical EMS page

    p_write_pointer = (unsigned short *)( MK_FP(i_ems_frame_segment, 0) );

    // We will read from the data buffer here in the 'main' function
    // using the second physical EMS page.

    p_read_pointer = (unsigned short *)( MK_FP(i_ems_frame_segment, 0x4000) );

    // We try to allocate 1 Mb of EMS memory for our data buffer

    if(EMSAllocatePages(64, &i_ems_handle) != 0)
    {
        // We were unable to allocate the 64 pages of EMS memory which we require

        printf("Unable to allocate 1 Mb (64 pages) of EMS memory\n");

        return(-1);
    }

    // We map the first logical page (start of our data buffer) to the first
    // physical page p_write_pointer

    EMSMapExpandedMemoryPage(i_ems_handle, 0, 0);

    // Initialise the write offset

    l_next_write_offset = 0L;

    // Initialise the last logical write page

    i_current_logical_write_page = 0;

    ////////////////////////////////////////////////////////////////////////////////
    //                          Initialise ME2600 board                           //
    ////////////////////////////////////////////////////////////////////////////////

    init_error = ME2600Init(&us_me2600_port, &uc_irq_line, &us_plx_port);

    if(init_error != ME2600_NO_ERROR)
    {
        // Error initialising the ME2600 board

        printf("ME2600 Init error: %u\n", init_error);

        // We should remember to release the EMS memory

        EMSReleasePages(i_ems_handle);

        return(init_error);
    }

    printf("Press any key to continue\n\n");

    getch();

    p_file = fopen(sz_file_name, "wb");

    ////////////////////////////////////////////////////////////////////////////////
    //                      Program the ME2600 board for AD scan                  //
    ////////////////////////////////////////////////////////////////////////////////

    // Write 0x0000 to control register 2 - This will empty the channel list and
    // the AD FIFO.

    outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

    // Prepare the channel list and the AD FIFO to receive new entries

    outport(us_me2600_port + ME2600_CONTROL_2, ME2600_C2_PREPARE_CH_FIFO | ME2600_C2_PREPARE_AD_FIFO);

    // Fill the channel list

    for(index = 0; index < NO_OF_AD_CHANNELS; index++)
    {
        unsigned short us_channel_entry =   ad_channel_no[index]        |
                                            ad_channel_gain[index]      |
                                            ad_channel_polarity[index]  |
                                            ad_channel_mode[index];

        outport(us_me2600_port + ME2600_CHANNEL_LIST, us_channel_entry);
    }

    // Program the scan sampling rate

    // Calculate the required latch value - The scan clock has a basic frequency of 3 MHz

    d_latch_reg = (3000000.0 / ad_scan_sum_sampling_rate) * (double)NO_OF_AD_CHANNELS + 0.5;

    ul_scan_latch_reg = (unsigned long)d_latch_reg;

    // We must subtract 1 from the calculated latch register value to obtain the correct scan rate

    --ul_scan_latch_reg;

    // Write the latch value (24 bit) to the appropriate registers

    outport( us_me2600_port + ME2600_TIMER_DATA_0, (unsigned short)(ul_scan_latch_reg & 0x0000ffff) );

    outport(us_me2600_port + ME2600_TIMER_DATA_1, (unsigned short)(ul_scan_latch_reg >> 16) );

    // Program the channel sampling rate

    // The channel clock also has a basic frequency of 3 MHz. 0x000000A therefore corresponds to
    // 3.33 microseconds

    us_sample_latch_reg = 0x0000000A;

    // The sampling must be finished when a new scan begins, so sample latch * NO_OF_AD_CHANNELS
    // must be less than scan latch

    if( (unsigned long)us_sample_latch_reg * NO_OF_AD_CHANNELS >= ul_scan_latch_reg )
    {
        us_sample_latch_reg = (unsigned short)( (ul_scan_latch_reg - 1) / NO_OF_AD_CHANNELS );
    }

    // Write the latch value (16 bit) to the appropriate register

    outport(us_me2600_port + ME2600_TIMER_DATA_2, us_sample_latch_reg);

    // Reset status register

    outport(us_me2600_port + ME2600_STATUS, 0x0000);

    // Determine the interrupt vector from the boards irq line

    if(uc_irq_line < 8)
    {
        uc_irq_vector = 0x08 + uc_irq_line;
    }
    else
    {
        uc_irq_vector = 0x70 + (uc_irq_line - 8);
    }

    // Save the old interrupt vector

    fnc_prev_irq_handler = getvect(uc_irq_vector);

    // Install the new interrupt vector

    setvect(uc_irq_vector, IRQHandler);

    // Enable interrupt on PLX

    outportb(us_plx_port + PLX_INT_STATUS, 0x43);

    // Set Continuous Data Acquisition and scan mode and enable FIFO half full interrupt

    outport(us_me2600_port + ME2600_CONTROL_1,
                            ME2600_C1_SCAN_MODE | ME2600_C1_ADC_COUNTER_CONVERT |
                                            ME2600_C1_FIFO_HALF_FULL_INTERRUPT | ME2600_C1_ENABLE_INTERRUPTS);

    // Initialise the buffer rollovers count

    i_buffer_rollovers = 0;

    // Initialise the data lost count

    i_data_lost = 0;

    // Start Data Acquisition

    inport(us_me2600_port + ME2600_ADC_START);

    // Initialise the next logical read page variable

    i_next_logical_read_page = 0;

    // Initialise the number of stored values

    ul_total_stored_values = 0L;

    // We continuously check for new data and and store it in the requested file.
    // At the same time, we print the total number of stored values on the screen.
    //  This process can be terminated by pressing any key

    while(1)
    {
        int i_last_logical_write_page;

        int i_last_rollover_count;

        if( kbhit() )
        {
            getch();

            break;
        }

        // Disable interrupts before reading i_last_logical_write_page as this
        // this variable will be changed by the interrupt procedure

        _asm cli

        i_last_logical_write_page = i_current_logical_write_page;

        i_last_rollover_count = i_buffer_rollovers;

        // Reenable interrupts

        _asm sti

        // Check to see if data was overwritten

        if(i_last_rollover_count >= 1)
        {
            if( (i_last_logical_write_page >= i_next_logical_read_page)||(i_last_rollover_count >= 2) )
            {
                // Data was overwritten, we are acquiring data faster than
                // we can write it to disk

                ++i_data_lost;

                // Reset the rollover counter after disabling interrupts

                _asm cli

                i_buffer_rollovers = 0;

                // Reenable interrupts

                _asm sti

            }
        }

        while(i_next_logical_read_page != i_last_logical_write_page)
        {
            // We store all those logical pages which have not yet
            // been written to the file. To save time we always store
            // a complete logical page at a time.

            // We map the next logical EMS page to the first physical EMS
            // page. Since the EMS routines are, apparently, not reentrant,
            // we must disable interrupts while doing this

            _asm cli

            EMSMapExpandedMemoryPage(i_ems_handle, 1, i_next_logical_read_page);

            _asm sti

            // Write the entire page to the file, p_read_pointer points to the
            // second physical EMS page

            fwrite(p_read_pointer, sizeof(unsigned short), 0x2000, p_file);

            if(++i_next_logical_read_page >= 64)
            {
                i_next_logical_read_page = 0;

                // We have to disable interrupts before decrementing the buffer
                // rollover counter, because this variable may also be changed
                // in the interrupt routine

                _asm cli

                --i_buffer_rollovers;

                _asm sti
            }

            ul_total_stored_values+= 0x2000;

            printf("Total number of stored values: %lu  Buffer overwritten: %d\n",
                                                                ul_total_stored_values, i_data_lost);
        }
    }

    // Reset control and status registers

    outport(us_me2600_port + ME2600_CONTROL_1, 0x0000);

    outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

    outport(us_me2600_port + ME2600_STATUS, 0x0000);

    // Disable interrupt on PLX

    outportb(us_plx_port + PLX_INT_STATUS, 0x00);

    // Reinstall the old interrupt vector

    setvect(uc_irq_vector, fnc_prev_irq_handler);

    // Write the remaining values to the file

    while(i_next_logical_read_page != i_current_logical_write_page)
    {
        // We store our all those logical pages which have not yet
        // been written to the file. To save time we always store
        // a complete logical page at a time.

        // We map the next logical EMS page to the first physical EMS
        // page.

        EMSMapExpandedMemoryPage(i_ems_handle, 1, i_next_logical_read_page);

        // Write the entire page to the file, p_read_pointer points to the
        // second physical EMS page

        fwrite(p_read_pointer, sizeof(unsigned short), 0x2000, p_file);

        if(++i_next_logical_read_page >= 64)
        {
            i_next_logical_read_page = 0;

            --i_buffer_rollovers;
        }

        ul_total_stored_values+= 0x2000;

        printf("Total number of stored values: %lu\n", ul_total_stored_values);
    }

    // We still have to write those values contained in the current logical
    // write page to the file

    EMSMapExpandedMemoryPage(i_ems_handle, 1, i_current_logical_write_page);

    ui_remaining_values = (unsigned int)(l_next_write_offset & 0x00001fff);

    fwrite(p_read_pointer, sizeof(unsigned short), ui_remaining_values, p_file);

    fclose(p_file);

    // We should remember to release the EMS memory

    EMSReleasePages(i_ems_handle);

    return(0);
}

// Interrupt handler for the application

void interrupt IRQHandler(void)
{
    // Read the PLX status

    unsigned char plx_status = inportb(us_plx_port + PLX_INT_STATUS);

    // Has our device caused the interrupt ?

    if( (plx_status & 0x04)||(plx_status & 0x20) )
    {
        // Read status register

        unsigned short us_status = inport(us_me2600_port + ME2600_STATUS);

        if(us_status & ME2600_S_AD_FIFO_HALF_FULL)
        {
            // There are certainly at least 1024 in the FIFO, otherwise
            // the interrupt would not have been triggered. We can read these entries at once
            // and store them in the data buffer

            int fifo_index;

            for(fifo_index = 0; fifo_index < 1024; fifo_index++)
            {
                p_write_pointer[l_next_write_offset] = inport(us_me2600_port + ME2600_READ_AD_FIFO);

                // IMPORTANT! - The measured values are returned in 12 bit two's complement
                // format. To convert these to straight binary we have to XOR with 0x800.

                p_write_pointer[l_next_write_offset]^= 0x0800;

                l_next_write_offset++;
            }

            // Since the number of values which we read each time (1024 = 0x0400) exactly divides
            // both the size of our buffer in unsigned shorts (1 Mb = 0x80000 unsigned shorts) and
            // the size of a logical EMS page in bytes ( 16 Kb = 0x2000 unsigned shorts), we do not
            // have to check l_next_write_offset after reading each value from the FIFO. It is
            // sufficient to do this here after all 1024 values have been read.

            if(l_next_write_offset >= 0x2000)
            {
                // We have filled the current logical page

                // Reset the page offset

                l_next_write_offset-= 0x2000;

                // Increment the logical page number

                i_current_logical_write_page++;

                if(i_current_logical_write_page >= 64)
                {
                    // Buffer rollover

                    ++i_buffer_rollovers;

                    i_current_logical_write_page = 0;
                }

                // Map logical EMS page i_current_logical_write_page to
                // the first physical EMS page.

                EMSMapExpandedMemoryPage(i_ems_handle, 0, i_current_logical_write_page);
            }
        }

        // Reset interrupt bits on xilinx status register

        outport(us_me2600_port + ME2600_RESET_INTERRUPT, 0x00);

        // Reset int on PLX chip

        outportb(us_plx_port + PLX_INT_STATUS, 0x43);
    }
    else
    {
        // Interrupt is not from our board, call the previous handler

        _chain_intr(fnc_prev_irq_handler);
    }

    // Specific End of interrupt to clear in-service bit
    // Mask upper 5 bits of int. line register

    if(uc_irq_line < 8)
    {
        outportb( 0x20, 0x60 | (uc_irq_line & 0x07) );
    }
    else
    {
        // Issue master then slave EOI

        outportb(0xa0, 0x60 | ( (uc_irq_line - 8) & 0x07 ) );

        outportb(0x20, 0x62);
    }
}

// The following function are used in the above example to
// allocate, map and free EMS pages.

int EMSIsInstalled(void)
{
    char* sz_emm_name = "EMMXXXX0";

    unsigned name_seg =  ( (unsigned long)sz_emm_name ) >> 16;

    unsigned name_off =  ( (unsigned long)sz_emm_name ) & 0xffff;

    _asm    mov dx, name_seg

    _asm    mov ds, dx;

    _asm    mov dx, name_off

    _asm    mov ax, 0x3D00

    _asm    int 21h

    _asm    jc error

    return(0);

    error:

    return(-1);
}

int EMSGetPageFrameSegment(int* p_page_frame_segment)
{
    int _page_frame_segment;

    int error;

    *p_page_frame_segment = 0;

    _asm    mov ah, 41h
    _asm    int 67h
    _asm    or ah, ah

    _asm    jnz error

    _asm    mov _page_frame_segment, bx

    *p_page_frame_segment = _page_frame_segment;

    return(0);

    error:

    _asm    xchg ah, al

    _asm    xor ah, ah

    _asm    mov error, ax

    return(error);
}

int EMSAllocatePages(int no_pages, int* p_handle)
{
    int _handle;

    int error;

    *p_handle = 0;

    _asm    mov ah, 43h
    _asm    mov bx, no_pages

    _asm    int 67h
    _asm    or ah, ah

    _asm    jnz error

    _asm    mov _handle, dx

    *p_handle = _handle;

    return(0);

    error:

    _asm    xchg ah, al

    _asm    xor ah, ah

    _asm    mov error, ax

    return(error);
}


int EMSReleasePages(int handle)
{
    int error;

    _asm    mov ah, 45h
    _asm    mov dx, handle

    _asm    int 67h
    _asm    or ah, ah

    _asm    jnz error

    return(0);

    error:

    _asm    xchg ah, al

    _asm    xor ah, ah

    _asm    mov error, ax

    return(error);
}

int EMSMapExpandedMemoryPage(int handle, int physical_page, int logical_page)
{
    unsigned char uc_physical_page = (unsigned char)physical_page;

    int error;

    _asm    mov ah, 44h
    _asm    mov dx, handle
    _asm    mov al, uc_physical_page
    _asm    mov bx, logical_page

    _asm    int 67h
    _asm    or ah, ah

    _asm    jnz error

    return(0);

    error:

    _asm    xchg ah, al

    _asm    xor ah, ah

    _asm    mov error, ax

    return(error);
}

