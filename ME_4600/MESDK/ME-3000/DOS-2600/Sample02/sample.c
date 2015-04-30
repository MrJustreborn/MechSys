/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         kh                                                                                      */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com in special www.amcc.com/TechLib/pcidev.htm)                               */
/*                                                                                                          */
/*  Description:    simple scope example                                                                    */
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
// board to simulate a simple oscilloscope.

// This example was wriiten for BorlandC 3.1 compiler.

// To run this example, the current directory MUST contain a
// sub-directory "bgi" containing the borland graphic drivers.

// You can change the behaviour of the oscilloscope by changing
// the values of the defines and constants below.

// With a little work you could extend this example to a fully
// configurable software oscilloscope with a graphical user
// interface

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

// Colors of the data plots - constants taken from graphics.h - change if required

int ad_channel_color[NO_OF_AD_CHANNELS]             = { LIGHTRED,
                                                        LIGHTGREEN,
                                                        LIGHTBLUE,
                                                        YELLOW                      };

double ad_scan_sum_sampling_rate                    = 100000;   // Sum sampling rate in Hz - change if required
                                                                // Maximum 300000 Hz

double window_width                                 = 4.0;      // Window width in seconds - change if required

// Size of the internal data buffer IN SHORTS - cannot be made larger than 0x7ff0 (?) without
// using the compiler's huge model

#define DATA_BUFFER_SIZE_USHORTS                    30000

////////////////////////////////////////////////////////////////////////
//      No user changeable defines and constants below this point     //
////////////////////////////////////////////////////////////////////////

// Previous interrupt handler

void interrupt (*fnc_prev_irq_handler) (void);

// Forward declaration for IRQ Handler

void interrupt IRQHandler(void);

// Global variables used in interrupt

long l_next_write_offset;

unsigned short us_me2600_port   = REQUIRED_ME2600_PORT;

unsigned char uc_irq_line       = REQUIRED_IRQ_LINE;

unsigned short us_plx_port;

unsigned short* p_us_data_buffer;

int main(void)
{
    int g_driver, g_mode;

    int scr_width, scr_height;

    double d_latch_reg;

    unsigned long ul_scan_latch_reg;

    unsigned long us_sample_latch_reg;

    long l_next_read_offset;

    unsigned char uc_irq_vector;

    int index;

    // Local variables for the graphic

    float f_y_factor;

    float f_y_constant;

    double d_x_inc;

    double d_x_pix;

    int b_first_data;

    int i_last_x_pix;

    int i_last_y_pix[NO_OF_AD_CHANNELS];

    ////////////////////////////////////////////////////////////////////////////////
    //                          Initialise ME2600 board                           //
    ////////////////////////////////////////////////////////////////////////////////

    unsigned int init_error = ME2600Init(&us_me2600_port, &uc_irq_line, &us_plx_port);

    if(init_error != ME2600_NO_ERROR)
    {
        // Error initialising the ME2600 board

        printf("ME2600 Init error: %u\n", init_error);

        return(init_error);
    }

    printf("Press any key to continue\n\n");

    getch();

    ////////////////////////////////////////////////////////////////////////////////
    //                          Change to graphic modus                           //
    ////////////////////////////////////////////////////////////////////////////////

    detectgraph(&g_driver, &g_mode);
    initgraph(&g_driver, &g_mode, "bgi");

    scr_width = getmaxx();

    scr_height = getmaxy();

    // Allocate memory for our data buffer

    p_us_data_buffer = (unsigned short *)malloc( DATA_BUFFER_SIZE_USHORTS * sizeof(unsigned short) );

    l_next_write_offset = 0;

    l_next_read_offset = 0;

    f_y_factor = (float)-scr_height / 4095.0F;

    f_y_constant = (float)scr_height;

    d_x_inc = (double)scr_width * (double)NO_OF_AD_CHANNELS / ad_scan_sum_sampling_rate / window_width;

    d_x_pix = 1.0;

    b_first_data = 0;

    i_last_x_pix = 0;

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

    // Start Data Acquisition

    inport(us_me2600_port + ME2600_ADC_START);

    // We continuously check for new data and plot it on the screen when it arrives.
    // This process can be terminated by pressing any key.

    while(1)
    {
        long l_last_write_offset;

        long l_no_frames;

        long index_frame;

        int next_x_pix;

        int last_x_pix;

        if( kbhit() )
        {
            getch();

            break;
        }

        // Disable interrupts before reading l_next_write_offset as this
        // this variable will be changed by the interrupt procedure

        _asm cli

        l_last_write_offset = l_next_write_offset;

        // Reenable interrupts

        _asm sti

        // The new data values lie in the buffer p_us_data_buffer between
        // l_next_read_offset and l_last_write_offset

        if(l_last_write_offset == l_next_read_offset)
        {
            // No new data available

            continue;
        }

        // How many frames of new data are available

        l_no_frames = l_last_write_offset - l_next_read_offset;

        if(l_no_frames < 0)
        {
            // Buffer rollover!

            l_no_frames+= DATA_BUFFER_SIZE_USHORTS;
        }

        // Each frame contains NO_OF_AD_CHANNELS values

        l_no_frames/= NO_OF_AD_CHANNELS;

        // We erase the part of the screen where the new values will be plotted

        // First X-coordinate to erase

        next_x_pix = (int)d_x_pix + 1;

        // Last X-coordinate to erase

        last_x_pix = (int)(d_x_pix + (double)l_no_frames * d_x_inc);

        // Erase the screen to the right of the old values

        if( (last_x_pix >= next_x_pix)&&(next_x_pix <= scr_width) )
        {
            int right_x_pix = last_x_pix;

            if(right_x_pix >= scr_width)
            {
                right_x_pix = scr_width;
            }

            setfillstyle(SOLID_FILL, BLACK);

            // Erase from next_x_pix to right_x_pix

            bar(next_x_pix, 1, right_x_pix, scr_height);
        }

        // If necessary, erase the left hand size of the screen where the data will be plotted

        if(d_x_pix + (double)l_no_frames  * d_x_inc > (double)scr_width)
        {
            // Last X-coordinate to erase

            int right_x_pix = 1 + (int)(d_x_pix + (double)l_no_frames * d_x_inc - (double)scr_width);

            setfillstyle(SOLID_FILL, BLACK);

            // Erase from 1 to right_x_pix

            bar(1, 1, right_x_pix, scr_height);
        }

        // Now plot the new values

        // Loop through the new frames

        for(index_frame = 0; index_frame < l_no_frames; index_frame++)
        {
            // X-coordinates for the new values begin here

            int x_pix = (int)d_x_pix;

            // Loop through the channels

            for(index = 0; index < NO_OF_AD_CHANNELS; index++)
            {
                // Calculate the Y-coordinate

                int y_pix = (int)( (float)p_us_data_buffer[l_next_read_offset] * f_y_factor + f_y_constant);

                if(b_first_data == 0)
                {
                    // No previous plotted point - move to the current point

                    moveto(x_pix, y_pix);
                }
                else
                {
                    // There is a previous plotted point - If our new point DOESN'T
                    // have the same coordinates, then we draw a line connecting the two

                    if( (x_pix != i_last_x_pix)||(y_pix != i_last_y_pix[index]) )
                    {
                        // Different coordinates - Set the color....

                        setcolor( ad_channel_color[index] );

                        // ... and draw the line

                        moveto(i_last_x_pix, i_last_y_pix[index]);
                        lineto(x_pix, y_pix);
                    }
                }

                // Update the last Y-coordinate

                i_last_y_pix[index] = y_pix;

                // Update the data buffer offset

                if(++l_next_read_offset >= DATA_BUFFER_SIZE_USHORTS)
                {
                    // Buffer rollover

                    l_next_read_offset = 0;
                }
            }

            // Update the X-value

            d_x_pix+= d_x_inc;

            // Update the X-coordinate

            i_last_x_pix = x_pix;

            // We now have a previous point

            b_first_data = 1;

            if(d_x_pix >= (double)scr_width)
            {
                // The screen is full - start again on the right hand side

                d_x_pix = d_x_pix - scr_width + 1;

                // This will be our first point on the screen

                b_first_data = 0;
            }
        }

        // Now draw the line separating the new data from the old data if necessary

        next_x_pix = (int)d_x_pix + 1;

        if(next_x_pix <= scr_width)
        {
            setcolor(LIGHTGRAY);

            moveto(next_x_pix, 1);
            lineto(next_x_pix, scr_height);
        }
    }

    // Free the data buffer

    free(p_us_data_buffer);

    // Reset control and status registers

    outport(us_me2600_port + ME2600_CONTROL_1, 0x0000);

    outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

    outport(us_me2600_port + ME2600_STATUS, 0x0000);

    // Disable interrupt on PLX

    outportb(us_plx_port + PLX_INT_STATUS, 0x00);

    // Reinstall the old interrupt vector

    setvect(uc_irq_vector, fnc_prev_irq_handler);

    // Exit graphic modus

    closegraph();

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
                p_us_data_buffer[l_next_write_offset] = inport(us_me2600_port + ME2600_READ_AD_FIFO);

                // IMPORTANT! - The measured values are returned in 12 bit two's complement
                // format. To convert these to straight binary we have to XOR with 0x800.

                p_us_data_buffer[l_next_write_offset]^= 0x0800;

                // Increment the write pointer index

                if(++l_next_write_offset >= DATA_BUFFER_SIZE_USHORTS)
                {
                    // Buffer rollover

                    l_next_write_offset = 0;
                }
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

