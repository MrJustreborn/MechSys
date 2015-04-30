/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2000 Meilhaus Elektronik GmbH                                                      */
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


// This example shows the basic steps required to program the ME4000 board
// to sample a single value from an AI channel

// This example was written for BorlandC 3.1 compiler

// You can change the behaviour of this application by changing
// the values of the defines and constants below

// Standard includes
#include <stdio.h>
#include <conio.h>
#include <dos.h>

// Include-file for register defines and init routine
#include "..\amcc.h"        // Low level PCI Bios routines
#include "..\me4000.h"

unsigned short us_ME4000_port;


int main(void)
{
    int index_channel;
    unsigned long dw_ctrl_reg = 0;
    unsigned long dw_reg =  0;
    short s_value;
    double d_volt;
    unsigned long dw_status;


    us_ME4000_port = 0xb400;    /* von me4kInit.exe übernehmen ! */

    printf("\n\n");
    printf("Mit einem Takt von 1Hz die Werte von den Kanaelen 0 bis 15 messen\n\n");
    printf("Druecken Sie eine beliebige Taste um fortzufuehren\n\n");

    getch();


    // Init
    outpd(us_ME4000_port + ME4000_AI_CTRL_REG, dw_ctrl_reg );

    while( !kbhit() )
    {
        int index_channel;

        for(index_channel = 0; index_channel < 16; index_channel++)
        {
            // Write PRE_CHAN register
            outpd(us_ME4000_port + ME4000_AI_CHAN_PRE_TIMER_REG, 0x41);

            // Write CHAN register
            outpd(us_ME4000_port + ME4000_AI_CHAN_TIMER_REG, 0x41);
            dw_ctrl_reg = inpd(us_ME4000_port + ME4000_AI_CTRL_REG);

            // Set Mode A
            dw_ctrl_reg|= ME4000_AI_CTRL_MODE_A;
            outpd(us_ME4000_port + ME4000_AI_CTRL_REG, dw_ctrl_reg );

            // Clear (and disable) data FIFO
            dw_ctrl_reg&= ~ME4000_AI_CTRL_DATA_FIFO_ENABLE;
            outpd(us_ME4000_port + ME4000_AI_CTRL_REG, dw_ctrl_reg );

            // Clear chan FIFO enable bit (clears channel FIFO)
            dw_ctrl_reg&= ~ME4000_AI_CTRL_CHAN_FIFO_ENABLE;
            outpd(us_ME4000_port + ME4000_AI_CTRL_REG, dw_ctrl_reg );

            // Set chan FIFO enable bit
            dw_ctrl_reg|= ME4000_AI_CTRL_CHAN_FIFO_ENABLE;
            outpd(us_ME4000_port + ME4000_AI_CTRL_REG, dw_ctrl_reg );

            // Load channel FIFO
            dw_reg =    index_channel           |
                        ME4000_AI_UNIPOLAR_10   |
                        ME4000_AI_SINGLE_ENDED  ;


            // IMPORTANT: Don't forget to set the last entry bit
            dw_reg|= ME4000_AI_CHANNEL_LIST_LAST_ENTRY;
            outpd(us_ME4000_port + ME4000_AI_CHANNEL_LIST_REG, dw_reg);

            // Enable data fifo
            dw_ctrl_reg|= ME4000_AI_CTRL_DATA_FIFO_ENABLE;
            outpd(us_ME4000_port + ME4000_AI_CTRL_REG, dw_ctrl_reg );

            // Start conversion by dummy read
            inpd(us_ME4000_port + ME4000_AI_START_REG);

            // Wait until FSM is idle
            do
            {
                dw_status = inpd(us_ME4000_port + ME4000_AI_STATUS_REG);
            }
            while( (dw_status & ME4000_AI_STATUS_FIFO_NOT_EMPTY_FLAG) != ME4000_AI_STATUS_FIFO_NOT_EMPTY_FLAG );

            s_value = inport(us_ME4000_port + ME4000_AI_DATA_REG);

            // Convert the digital value to a potential
            d_volt = 5.0 * (double)s_value / (double)0x8000 + 5.0;

            printf("%2d.    Digital value: %6d    Physical Value: %7.3f V\n", index_channel, s_value, d_volt);
        }

        sleep(1);

        printf("\n\n");
    }

    printf("Druecken Sie eine beliebige Taste um zu beenden\n\n");

    getch();

    return(0);
}

