/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         kh                                                                                      */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com in special www.amcc.com/TechLib/pcidev.htm)                               */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
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


// This example shows the basic steps required to program the ME2600 board
// by exercising the boards main functions consecutively.

// This example was writen for BorlandC 3.1 compiler

// You can change the behaviour of this application by changing
// the values of the defines and constants below

// Standard includes
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <memory.h>

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

double ad_scan_sum_sampling_rate                    = 50000;        // Sum sampling rate in Hz
                                                                    // Maximum 300000 Hz

// Change the define 'NO_OF_DA_CHANNELS' and the contents of the arrays
// 'da_channel_id' and da_channel_range below, if required, to influence
// the DA output.

#define NO_OF_DA_CHANNELS                           2   // Maximum 4 (ME2600_DAC_DATA_A - ME2600_DAC_DATA_D)

unsigned short da_channel_no[NO_OF_DA_CHANNELS]     = { 0, 1};

unsigned short da_channel_range[NO_OF_DA_CHANNELS]  = { ME2600_DA_RANGE_MINUS_FIVE_PLUS_FIVE,
                                                        ME2600_DA_RANGE_MINUS_FIVE_PLUS_FIVE    };

////////////////////////////////////////////////////////////////////////
//      No user changeable defines and constants below this point     //
////////////////////////////////////////////////////////////////////////

// Previous interrupt handler

void interrupt (*fnc_prev_irq_handler) (void);

// Forward declaration for IRQ Handlers

void interrupt ScanIRQHandler(void);

void interrupt ExternalIRQHandler(void);

// Global variables used in interrupt

unsigned long ul_values_acquired;

unsigned short us_next_ad_channel;

unsigned long ul_external_int_count;

unsigned short us_me2600_port   = REQUIRED_ME2600_PORT;

unsigned char uc_irq_line       = REQUIRED_IRQ_LINE;

unsigned short us_plx_port;

unsigned short usDevID;

unsigned short us_channel_value[NO_OF_AD_CHANNELS];

int main(void)
{
    unsigned short us_port_A;
    double ad_true_sampling_rate;
    double d_latch_reg;
    unsigned long ul_scan_latch_reg;
    unsigned short us_sample_latch_reg;
    unsigned char uc_irq_vector;
    unsigned short us_dac_control;
    int da_channel;
    unsigned short us_dac_port;
    int index;

    ////////////////////////////////////////////////////////////////////////////////
    //                          Initialise ME2600 board                           //
    ////////////////////////////////////////////////////////////////////////////////

    unsigned int init_error = me2600Init(&us_me2600_port, &uc_irq_line, &us_plx_port, &usDevID);

    if(init_error != ME2600_NO_ERROR)
    {
        // Error initialising the ME2600 board

        printf("ME2600 Init error: %u\n", init_error);

        return(init_error);
    }

    printf("Press any key to continue\n\n");

    getch();

    ////////////////////////////////////////////////////////////////////////////////
    //                              Digital input                                 //
    ////////////////////////////////////////////////////////////////////////////////

    printf("Digital input from port A - Press any key to terminate\n\n");

    // Once every second we read the contents of port A from the ME2600 board
    // and print the result on the screen. This process can be terminated by
    // pressing any key

    while(1)
    {
        if( kbhit() )
        {
            getch();

            break;
        }

        // 1 second delay

        delay(1000);

        us_port_A = inport(us_me2600_port + ME2600_DIO_PORT_A);

        printf("Port A: %#04X\n", us_port_A);
    }

    ////////////////////////////////////////////////////////////////////////////////
    //                              Digital output                                //
    ////////////////////////////////////////////////////////////////////////////////

    printf("\n\nDigital ouput to port B - Enter '0' to terminate\n\n");

    // Enable write to port A

    outport(us_me2600_port + ME2600_CONTROL_2, ME2600_C2_ENABLE_PORT_A);

    // We continue to request values from the user and write them to
    // port A until the user enters a '0'

    while(1)
    {
        while(1)
        {
            int values_read = 0;

            printf("\nOutput value: 0x");

            values_read = scanf("%x", &us_port_A);

            if(values_read == 1)
            {
                break;
            }
        }

        if(us_port_A == 0)
        {
            break;
        }

        outport(us_me2600_port + ME2600_DIO_PORT_A, us_port_A);
    }

    // Disable write to port A

    outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

    printf("\n\n");

    ////////////////////////////////////////////////////////////////////////////////
    //                              External interrupt                            //
    ////////////////////////////////////////////////////////////////////////////////

    printf("\n\nExternal interrupt - Press any key to terminate\n\n");

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

    setvect(uc_irq_vector, ExternalIRQHandler);

    // Initialise the interrupt count

    ul_external_int_count = 0;

    // Enable interrupt on PLX

    outportb(us_plx_port + PLX_INT_STATUS, 0x43);

    // Enable external interrupt

    outport(us_me2600_port + ME2600_CONTROL_1, ME2600_C1_EXTERNAL_INTERRUPT | ME2600_C1_ENABLE_INTERRUPTS);

    // Once every second we print the current value of the interrupt counter
    // to the screen. This process can be terminated by pressing any key.

    while(1)
    {
        unsigned long ul_int_count;

        if( kbhit() )
        {
            getch();

            break;
        }

        // 1 second delay

        delay(1000);

        // Disable interrupt while reading ul_external_int_count as
        // this variable is also changed by the interrupt routine

        _asm cli

        ul_int_count = ul_external_int_count;

        // Reenable interrupts

        _asm sti

        printf("Total external interrupts: %lu\n", ul_int_count);
    }

    // Reset control and status registers

    outport(us_me2600_port + ME2600_CONTROL_1, 0x0000);

    outport(us_me2600_port + ME2600_STATUS, 0x0000);

    // Reinstall the old interrupt vector

    setvect(uc_irq_vector, fnc_prev_irq_handler);

    ////////////////////////////////////////////////////////////////////////////////
    //                          One-shot analog input                             //
    ////////////////////////////////////////////////////////////////////////////////

    printf("One-shot analog input - Press any key to terminate\n\n");

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

    // Set single scan Data Acquisition

    outport(us_me2600_port + ME2600_CONTROL_1, ME2600_C1_ADC_SW_CONVERT);

    // Program the channel sampling rate

    outport(us_me2600_port + ME2600_TIMER_DATA_2, 0x000A);

    // Reset status register

    outport(us_me2600_port + ME2600_STATUS, 0x0000);

    // Once every second we sample all the required channels and print the
    // results on the screen. This process can be terminated by pressing any
    // key.

    while(1)
    {
        if( kbhit() )
        {
            getch();

            break;
        }

        // 1 second delay

        delay(1000);

        // Start Data Acquisition

        inport(us_me2600_port + ME2600_ADC_START);

        for(index = 0; index < NO_OF_AD_CHANNELS; index++)
        {
            while(1)
            {
                // Read status

                unsigned short us_status = inport(us_me2600_port + ME2600_STATUS);

                if( (us_status & ME2600_S_AD_FIFO_EMPTY) != ME2600_S_AD_FIFO_EMPTY )
                {
                    // There is at least one value in the AD FIFO

                    break;
                }
            }

            us_channel_value[index] = inport(us_me2600_port + ME2600_READ_AD_FIFO);

            us_channel_value[index]^= 0x0800;
        }

        // Print the channel values to the screen

        for(index = 0; index < NO_OF_AD_CHANNELS; index++)
        {
            if( (index %6) == 0)
            {
                // Six values to a line

                printf("\n");
            }

            printf("%2d: %4hu    ", index, us_channel_value[index]);
        }
    }

    printf("\n\n");

    // Reset control and status registers

    outport(us_me2600_port + ME2600_CONTROL_1, 0x0000);

    outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

    outport(us_me2600_port + ME2600_STATUS, 0x0000);

    ////////////////////////////////////////////////////////////////////////////////
    //                          Analog output                                     //
    ////////////////////////////////////////////////////////////////////////////////

    printf("Analog output - Enter '0' to terminate\n\n");

    // Deactivate DAC channels

    outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

    // Activate DAC channels

    outport(us_me2600_port + ME2600_CONTROL_2, ME2600_C2_DAC_ACTIVE);

    // Set gain and modus for the DA channels

    us_dac_control = 0;

    for(index = 0; index < NO_OF_DA_CHANNELS; index++)
    {
        us_dac_control|= ( da_channel_range[index] >> da_channel_no[index] );
    }

    outport(us_me2600_port + ME2600_DAC_CONTROL, us_dac_control);

    // Update DAC control register

    inport(us_me2600_port + ME2600_DAC_CONTROL_UPDATE);

    // We continue to request values from the user and write them to
    // the DA channels in turn until the user enters a '0'

    da_channel = 0;

    while(1)
    {
        while(1)
        {
            int values_read = 0;

            printf( "\nOutput value DAC %c (001 - FFF): 0x", 'A' + da_channel_no[da_channel] );

            values_read = scanf("%x", &us_dac_port);

            if(values_read == 1)
            {
                break;
            }
        }

        if(us_dac_port == 0)
        {
            break;
        }

        // Write the value to the appropriate DAC

        outport(us_me2600_port + ME2600_DAC_DATA_A + 2 * da_channel_no[da_channel], us_dac_port);

        if(++da_channel >= NO_OF_DA_CHANNELS)
        {
            da_channel = 0;
        }
    }

    // Deactivate DAC channels

    outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

    printf("\n\n");

    ////////////////////////////////////////////////////////////////////////////////
    //                          Analog input scan                                 //
    ////////////////////////////////////////////////////////////////////////////////

    printf("Analog input scan - Press any key to terminate\n\n");

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

    // Calculate the sampling rate actually obtained with this latch value

    ad_true_sampling_rate = (3000000.0 / (double)ul_scan_latch_reg) * (double)NO_OF_AD_CHANNELS;

    printf("\nRequired sampling rate: %lg    True sampling rate: %lg\n\n",
                                                    ad_scan_sum_sampling_rate, ad_true_sampling_rate);

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

    setvect(uc_irq_vector, ScanIRQHandler);

    // Enable interrupt on PLX

    outportb(us_plx_port + PLX_INT_STATUS, 0x43);

    // Set Continuous Data Acquisition and scan mode and enable FIFO half full interrupt

    outport(us_me2600_port + ME2600_CONTROL_1,
                            ME2600_C1_SCAN_MODE | ME2600_C1_ADC_COUNTER_CONVERT |
                                            ME2600_C1_FIFO_HALF_FULL_INTERRUPT | ME2600_C1_ENABLE_INTERRUPTS);

    // Initialise global variables

    ul_values_acquired = 0;

    us_next_ad_channel = 0;

    // Start Data Acquisition

    inport(us_me2600_port + ME2600_ADC_START);

    // Once every second we print the last values of the sampled channels on the screen,
    // together with the total number of values acquired so far.  This process can be
    // terminated by pressing any key.

    while(1)
    {
        unsigned long ul_total_values;

        unsigned short us_last_values[NO_OF_AD_CHANNELS];

        if( kbhit() )
        {
            getch();

            break;
        }

        // 1 second delay

        delay(1000);

        // Disable interrupts while reading values changed in interrupt procedure

        _asm cli

        ul_total_values = ul_values_acquired;

        memcpy( &us_last_values[0], &us_channel_value[0], NO_OF_AD_CHANNELS * sizeof(unsigned short) );

        // Reenable interrupts

        _asm sti

        // Print the channel values to the screen

        for(index = 0; index < NO_OF_AD_CHANNELS; index++)
        {
            if( (index % 6) == 0)
            {
                // Four values to a line

                printf("\n");
            }

            printf("%2d: %4hu    ", index, us_last_values[index]);
        }

        printf("\nTotal number of values acquired: %lu\n\n", ul_total_values);
    }


    // Reset control and status registers

    outport(us_me2600_port + ME2600_CONTROL_1, 0x0000);

    outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

    outport(us_me2600_port + ME2600_STATUS, 0x0000);

    // Disable interrupt on PLX

    outportb(us_plx_port + PLX_INT_STATUS, 0x00);

    // Reinstall the old interrupt vector

    setvect(uc_irq_vector, fnc_prev_irq_handler);

    return(0);
}

// Interrupt handler for analog input scan

void interrupt ScanIRQHandler(void)
{
    // Read the PLX status register

    unsigned char plx_status = inportb(us_plx_port + PLX_INT_STATUS);

    // Has our device caused the interrupt ?

    if( (plx_status & 0x04)||(plx_status & 0x20) )
    {
        // Read the ME2600 status register

        unsigned short us_status = inport(us_me2600_port + ME2600_STATUS);

        if(us_status & ME2600_S_AD_FIFO_HALF_FULL)
        {
            // There are certainly at least 1024 in the FIFO, otherwise
            // the interrupt would not have been triggered. We can read these entries at once

            int fifo_index;

            for(fifo_index = 0; fifo_index < 1024; fifo_index++)
            {
                us_channel_value[us_next_ad_channel] = inport(us_me2600_port + ME2600_READ_AD_FIFO);

                // IMPORTANT! - The measured values are returned in 12 bit two's complement
                // format. To convert these to straight binary we have to XOR with 0x800.

                us_channel_value[us_next_ad_channel]^= 0x0800;

                if(++us_next_ad_channel >= NO_OF_AD_CHANNELS)
                {
                    us_next_ad_channel = 0;
                }
            }

            // Increment the number of values acquired

            ul_values_acquired+= 1024;
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

// Interrupt handler for the external interrupt

void interrupt ExternalIRQHandler(void)
{
    // Read the PLX status register

    unsigned char plx_status = inportb(us_plx_port + PLX_INT_STATUS);

    // Has our device caused the interrupt ?

    if( (plx_status & 0x04)||(plx_status & 0x20) )
    {
        // All we do in this example is increase the interrupt counter

        ++ul_external_int_count;

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
