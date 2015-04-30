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


// This example shows the basic steps required to program the ME1400 board
// by exercising the boards main functions consecutively.

// This example was written for BorlandC 3.1 compiler

// You can change the behaviour of this application by changing
// the values of the defines and constants below

// Standard includes
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <memory.h>

// Include-file for register defines and init routine
#include "..\me1400.h"

// You can force the ME1400 board to use a particular port address or a
// particular interrupt by changing the values for required_me1400_port
// and required_irq_line below. The value '0' means, in both cases, use
// the default values assigned by the system.
// If REQUIRED_ME_DEVID is 0 then we looking for any board
#define REQUIRED_ME1400_PORT                        0   // 0 = Use default
#define REQUIRED_IRQ_LINE                           0   // 0 = Use default
#define REQUIRED_ME_DEVID                           0   // 0 = Use default


////////////////////////////////////////////////////////////////////////
//      No user changeable defines and constants below this point     //
////////////////////////////////////////////////////////////////////////

// Previous interrupt handler
void interrupt (*fnc_prev_irq_handler) (void);

// Forward declaration for IRQ Handlers
void interrupt ExternalIRQHandler(void);

// Global variables used in interrupt
unsigned long ul_external_int_count;

unsigned short us_me1400_port   = REQUIRED_ME1400_PORT;
unsigned char uc_irq_line       = REQUIRED_IRQ_LINE;
unsigned short us_plx_port;
unsigned int ui_me_DevID        = REQUIRED_ME_DEVID;


int main(void)
{
    unsigned char uc_irq_vector;
    int index;

    ////////////////////////////////////////////////////////////////////////////////
    //                          Initialise ME1400 board                           //
    ////////////////////////////////////////////////////////////////////////////////

    unsigned int init_error;

    init_error = me1400Init(&us_me1400_port, &uc_irq_line, &us_plx_port, &ui_me_DevID);

    if(init_error != ME1400_NO_ERROR)
    {
        // Error initialising the ME1400 board
        printf("ME1400 Init error: %u\n", init_error);
        return(init_error);
    }

    printf("Press any key to continue\n\n");
    getch();


    ////////////////////////////////////////////////////////////////////////////////
    //                              Digital In- Output                            //
    ////////////////////////////////////////////////////////////////////////////////

    // Prepare the card
    // See manual for details
    printf("Preparing ME-1400... \n");
    outportb(us_me1400_port+0x03, 0x9B);
    outportb(us_me1400_port+0x07, 0x34);
    outportb(us_me1400_port+0x07, 0x74);
    outportb(us_me1400_port+0x07, 0xB4);
    outportb(us_me1400_port+0x03, 0x8B);



    // write example values
    printf("Write 0xAA ... \n");
    outportb(us_me1400_port+0x00, 0xAA);
    printf("Read 0x%02x\n",inportb(us_me1400_port+0x00));
    delay(2000);

    printf("Write 0x55 ... \n");
    outportb(us_me1400_port+0x00, 0x55);
    printf("Read 0x%02x\n",inportb(us_me1400_port+0x00));
    delay(2000);

    printf("Write 0xAA ... \n");
    outportb(us_me1400_port+0x00, 0xAA);
    printf("Read 0x%02x\n",inportb(us_me1400_port+0x00));
    delay(2000);

    printf("Write 0x55 ... \n");
    outportb(us_me1400_port+0x00, 0x55);
    printf("Read 0x%02x\n",inportb(us_me1400_port+0x00));



    ////////////////////////////////////////////////////////////////////////////////
    //                              External interrupt                            //
    ////////////////////////////////////////////////////////////////////////////////

    printf("\n\nExternal interrupt - Press any key to terminate\n\n");

    // Reset (disable) interrupt on PLX
    outportb(us_plx_port + PLX_INT_STATUS, 0x00);

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

    // Reset status register
    outport(
        us_me1400_port + ME1400_A_IRQ_CLK,
        ME1400_IRQ_CLK_IRQ_RESET | ME1400_IRQ_CLK_IRQ_IN);

    // Enable interrupt on PLX
    // Note: If you using interrupt mode,
    // you have to enable PLX-Irq line
    // wBasePLX+0x4C is the PLX-IRQ status register
    //   Meaning of the bits: (0x43)
    //   7:   Software Irq    - not used              - 0
    //   6:   PCI Irq Enable - we need this           - 1
    //   5:   Irq 2 status    - not used              - 0
    //   4:   Irq 2 polarity  - not used              - 0
    //   3:   Irq 2 enable    - not used              - 0
    //   2:   Irq 1 status    - we have to read this
    //   1:   Irq 1 polarity  - we need High active   - 1
    //   0:   Irq 1 enable    - we have to enable it  - 1


    outportb(us_plx_port + PLX_INT_STATUS, 0x43);

    // Reset status register and make the multifunction pin to an external interrupt input
    outport(
        us_me1400_port + ME1400_A_IRQ_CLK,
        ME1400_IRQ_CLK_IRQ_ENABLE | ME1400_IRQ_CLK_IRQ_IN);

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
        printf("0x4C: 0x%02X\n", inportb(us_plx_port + PLX_INT_STATUS));
    }

    // disable interrupt on PLX
    outportb(us_plx_port + PLX_INT_STATUS, 0x00);

    // Reinstall the old interrupt vector
    setvect(uc_irq_vector, fnc_prev_irq_handler);



    ////////////////////////////////////////////////////////////////////////////////
    //                              clock out to multifunction pin                //
    ////////////////////////////////////////////////////////////////////////////////

    // make the multifunction pin to an clock output
    outport(
        us_me1400_port + ME1400_A_IRQ_CLK,
        ME1400_IRQ_CLK_IRQ_RESET | ME1400_IRQ_CLK_CLK_OUT);

    printf("Multifunction pin is the clock output ...\n");
    printf("Press any key to continue\n\n");
    getch();

    outport(
        us_me1400_port + ME1400_A_IRQ_CLK,
        ME1400_IRQ_CLK_IRQ_RESET | ME1400_IRQ_CLK_IRQ_IN);

    return(0);
}


// Interrupt handler for the external interrupt
void interrupt ExternalIRQHandler(void)
{
    // Read the PLX status register
    unsigned char plx_status = inportb(us_plx_port + PLX_INT_STATUS);

    // Has our device caused the interrupt ?
    if( (plx_status & 0x04)||(plx_status & 0x20) )
    {
        // Reset status register
        outport(
            us_me1400_port + ME1400_A_IRQ_CLK,
            ME1400_IRQ_CLK_IRQ_RESET | ME1400_IRQ_CLK_IRQ_IN);

        // All we do in this example is increase the interrupt counter
        ++ul_external_int_count;

        // Enable status register
        outport(
            us_me1400_port + ME1400_A_IRQ_CLK,
            ME1400_IRQ_CLK_IRQ_ENABLE | ME1400_IRQ_CLK_IRQ_IN);
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
