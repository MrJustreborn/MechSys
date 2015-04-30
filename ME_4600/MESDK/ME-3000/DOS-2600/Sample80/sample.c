/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2002 Meilhaus Electronic GmbH                                                      */
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

// This example was written for BorlandC 3.1 compiler

// You can change the behaviour of this application by changing
// the values of the defines and constants below

// Standard includes
#include <stdio.h>
#include <conio.h>
#include <dos.h>

// Include-file for register defines and init routine
#include "..\me2600.h"

// You can force the ME2600 board to use a particular port address or a
// particular interrupt by changing the values for required_me2600_port
// and required_irq_line below. The value '0' means, in both cases, use
// the default values assigned by the system.
// If REQUIRED_ME_DEVID is 0 then we looking for any 2600 board
#define REQUIRED_ME2600_PORT                        0   // 0 = Use default
#define REQUIRED_IRQ_LINE                           0   // 0 = Use default
#define REQUIRED_ME_DEVID                           0   // 0 = Use default

// Change the define 'NO_OF_AD_CHANNELS' and the contents of the arrays
// 'ad_channel_no', 'ad_channel_gain', 'ad_channel_polarity' and
// ad_channel_mode below, if required, to influence the AD acquisition.

// Previous interrupt handler
void interrupt (*fnc_prev_irq_handler) (void);

// Forward declaration for IRQ Handlers
void interrupt IRQHandler(void);

// Global variables used in interrupt
int interrupt_count = 0;

unsigned short us_me2600_port   = REQUIRED_ME2600_PORT;
unsigned char uc_irq_line       = REQUIRED_IRQ_LINE;
unsigned short us_plx_port;
unsigned int ui_me_DevID        = REQUIRED_ME_DEVID;


int main(void)
{

    ////////////////////////////////////////////////////////////////////////////////
    //                          Initialise ME2600 board                           //
    ////////////////////////////////////////////////////////////////////////////////

    int arr_no_interrupts[5];
    int no_channels;
    unsigned long ul_scan_latch_reg;
    unsigned short us_sample_latch_reg;
    unsigned char uc_irq_vector;
    int index_test;
    int index_channel;
    unsigned int init_error;

    init_error = me2600Init(
        &us_me2600_port, 
        &uc_irq_line, 
        &us_plx_port, 
        &ui_me_DevID);

    if(init_error != ME2600_NO_ERROR)
    {
        // Error initialising the ME2600 board
        printf("ME2600 Init error: %u\n", init_error);
        return(init_error);
    }

    printf("\n");

    printf( "Mit einer unterschiedlichen Anzahl Kanaele aber mit der gleichen Scanzeit\n"
            "werden Daten erfasst und die ausgeloesten FIFO halb voll Interrupts gezaehlt\n\n"
            "Es waere zu erwarten, dass eine Verdopplung der Kanalanzahl zu einer Verdopplung\n"
            "der Interruptzahl fuehrt. Dies kann in der Regel beobachtet werden, ausser\n"
            "dass wir mit einem Kanal genau so viel Interrupts bekommen wie mit zwei\n\n");

    printf( "Der Test dauert etwa 1..2 Minuten, bitte warten Sie\n\n");


    ////////////////////////////////////////////////////////////////////////////////
    //                          Test                                              //
    ////////////////////////////////////////////////////////////////////////////////

    no_channels = 1;

    for(index_test = 0; index_test < 5; index_test++)
    {
        // Write 0x0000 to control register 2 - This will empty the channel list and
        // the AD FIFO.
        outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);

        // Prepare the channel list and the AD FIFO to receive new entries
        outport(us_me2600_port + ME2600_CONTROL_2, ME2600_C2_PREPARE_CH_FIFO | ME2600_C2_PREPARE_AD_FIFO);

        // Fill the channel list
        for(index_channel = 0; index_channel < no_channels; index_channel++)
        {
            unsigned short us_channel_entry =   index_channel           |
                                                ME2600_AD_GAIN_1        |
                                                ME2600_AD_BIPOLAR       |
                                                ME2600_AD_SINGLE_ENDED;

            outport(us_me2600_port + ME2600_CHANNEL_LIST, us_channel_entry);
        }

        // Program the scan rate to 10240 Hz

        // Calculate the required latch value - The scan clock has a basic frequency of 3 MHz
        ul_scan_latch_reg = (unsigned long)(3000000.0 / (double)10240.0);

        // We must subtract 1 from the calculated latch register value to obtain the correct scan rate
        --ul_scan_latch_reg;

        // Write the latch value (24 bit) to the appropriate registers
        outport( us_me2600_port + ME2600_TIMER_DATA_0, (unsigned short)(ul_scan_latch_reg & 0x0000ffff) );
        outport(us_me2600_port + ME2600_TIMER_DATA_1, (unsigned short)(ul_scan_latch_reg >> 16) );

        // Program the channel sampling rate
        us_sample_latch_reg = 0x0000000A;

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
            ME2600_C1_SCAN_MODE |
            ME2600_C1_ADC_COUNTER_CONVERT |
            ME2600_C1_FIFO_HALF_FULL_INTERRUPT |
            ME2600_C1_ENABLE_INTERRUPTS);

        interrupt_count = 0;

        // Start Data Acquisition
        inport(us_me2600_port + ME2600_ADC_START);

        // Wait approximately 10 seconds
        delay(10000);

        // Reset control and status registers
        outport(us_me2600_port + ME2600_CONTROL_1, 0x0000);
        outport(us_me2600_port + ME2600_CONTROL_2, 0x0000);
        outport(us_me2600_port + ME2600_STATUS, 0x0000);

        // Store the interrupt count in the array
        arr_no_interrupts[index_test] = interrupt_count;

        // Disable interrupt on PLX
        outportb(us_plx_port + PLX_INT_STATUS, 0x00);

        // Reinstall the old interrupt vector
        setvect(uc_irq_vector, fnc_prev_irq_handler);
        no_channels*= 2;
    }

    no_channels = 1;

    for(index_test = 0; index_test < 5; index_test++)
    {
        printf("Anzahl Kanaele: %2d    -    Anzahl Interrupts: %4d\n", no_channels, arr_no_interrupts[index_test]);
        no_channels*= 2;
    }

    return(0);
}



void interrupt IRQHandler(void)
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
                unsigned short us_value = inport(us_me2600_port + ME2600_READ_AD_FIFO);
                us_value^= 0x0800;
            }

            ++interrupt_count;
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
