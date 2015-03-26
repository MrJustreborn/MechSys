/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com in special www.amcc.com/TechLib/pcidev.htm)                               */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                  Some input or output signals have to be convert !!                                      */
/*                  This is not a full working sample, it should show, how you can determin the resources   */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    000510  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/


#include <dos.h>
#include <stddef.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "amcc.h"
#include "sample.h"


typedef struct _DEV_INFO
{
    word    wVenID;
    word    wDevID;
    byte    bBusNo;
    byte    bDevFct;

    word    wDeviceIdx;

    dword   dwSerialNumber;

    word    wBaseIO;
    word    wBasePLX;
    word    wBaseSwap;
    byte    bIrqLine;
    byte    bIrqVector;
    long unsigned int ulIrqCnt;

} DEVINFO;


void setup_int_vect(void);
void(interrupt *oldhandler)(void);
DEVINFO gDI;




/*****************************************************************/
/*  MAIN Code Segment                                            */
/*****************************************************************/
int main(void)
{
    ReStart:    // we restart if the PLX bug occure (or if we change the addresses)

    /*--- Look for a valid PCI BIOS -----------------------------*/
    {
        if(pci_bios_present(NULL,NULL,NULL)==SUCCESSFUL)
        {
            printf("PCI BIOS Found\n\n");
        }
        else
        {
            printf("PCI BIOS not present\n\n");
            printf("Exit program\n\n");
            getch();
            return(1);
        }
    }

    /*--- look for the Meilhaus devices -------------------*/
    {
        gDI.wVenID      = 0x1402;   // our Vendor ID
        gDI.wDevID      = 0x0630;   // our Device ID
        gDI.wDeviceIdx  = 0;        // first device we could found

        if(find_pci_device(
            gDI.wDevID,
            gDI.wVenID,
            gDI.wDeviceIdx,
            &gDI.bBusNo,
            &gDI.bDevFct)  !=  SUCCESSFUL)
        {
            gDI.wDevID      = 0x0000;   // not one of the ME-630
        }

        switch (gDI.wDevID & 0xFFF0)            // PCI and cPCI is the same
        {
        case 0x0630:
            printf("Found a ME-630 PCI\n");
            break;
        case 0x0000:
            printf("Can not found any appropriate device!\n\n");
            printf("Exit program\n\n");
            getch();
            return(2);
        }

        printf("General PCI data: \n\tBus=%d \n\tDevice=%d \n\tFunction=%d\n\n",
                    gDI.bBusNo,
                    gDI.bDevFct>>3,
                    gDI.bDevFct&0x7);
        printf("\tVendor ID:   0x%04x\n", gDI.wVenID);
        printf("\tDevice ID:   0x%04x\n", gDI.wDevID);
    }


    /*--- Set own resources (if needed) -------------------------*/

    /* if you need special address or interrupt settings         */
    /* for compatibility, this works not in every case (under    */
    /* windows ???), check it out                                */
#define VERBIEGEN
#undef VERBIEGEN                // comment this if you need
#ifdef VERBIEGEN
    {
        static int DoIt = TRUE;

        gDI.wBaseIO = 0x300;
        gDI.bIrqLine= 5;

        if (DoIt == TRUE)
        {
            printf("Set address and interrupt to specific values:\n");
            printf("\taddress:   0x%04x\n", gDI.wBaseIO);
            printf("\tinterrupt: %d\n",     gDI.bIrqLine);

            write_configuration_word(
                gDI.bBusNo,
                gDI.bDevFct,
                PCI_CS_BASE_ADDRESS_2,
                gDI.wBaseIO);

            write_configuration_word(
                gDI.bBusNo,
                gDI.bDevFct,
                PCI_CS_INTERRUPT_LINE,
                gDI.bIrqLine);

            DoIt = FALSE;
            printf("Now we restart the sample !\n");
            printf("Press any key to continue\n");
            while(!kbhit());
            getch();
            goto ReStart;
        }
    }
#endif


    /* determine resources */
    {
        word    wSerialNumberHigh;
        word    wSerialNumberLow;


        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_1,
            &gDI.wBasePLX);
        gDI.wBasePLX = gDI.wBasePLX & 0xFFFC;
        printf("\tBase address PLX IO register:    0x%04x\n", gDI.wBasePLX);

        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_2,
            &gDI.wBaseIO);
        gDI.wBaseIO = gDI.wBaseIO & 0xFFFC;
        printf("\tMain Base address:               0x%04x\n", gDI.wBaseIO);

        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_5,
            &gDI.wBaseSwap);
        gDI.wBaseSwap = gDI.wBaseSwap & 0xFFFC;
        printf("\tBase address PLX swap register:  0x%04x\n", gDI.wBaseSwap);


        read_configuration_byte(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_INTERRUPT_LINE,
            &gDI.bIrqLine);
        printf("\tInterrupt line:                  %d (dec)\n", gDI.bIrqLine);


        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_SUB_VENDOR_ID,
            &wSerialNumberLow);
        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_SUB_DEVICE_ID,
            &wSerialNumberHigh);
        gDI.dwSerialNumber = ((dword)wSerialNumberHigh<<16)+ wSerialNumberLow;
        printf("\tserial number:                   0x%08lx\n", gDI.dwSerialNumber);
    }


    /*--- check if PLX bug occured, if so make the workaround --*/
    {
        if(gDI.wBasePLX & 0x80)
        {
            printf("PLX-Bug:\n");
            printf("\tBit 7 is set, we can not read\n");
            printf("\tthe PLX register, so we\n");
            printf("\thave to change the address.\n");

            if ((gDI.wBaseSwap > 0) &&    // base5 exist
                (gDI.wBaseSwap < 0xFFFF)) // it is not a memory addr.
                                          // normally we have to test wit & 0x01
            {
                /* board with new mon file */
                printf("\tnew hardware revision found (new mon file)\n");

                write_configuration_word(
                    gDI.bBusNo,
                    gDI.bDevFct,
                    PCI_CS_BASE_ADDRESS_1,
                    gDI.wBaseSwap);

                read_configuration_word(
                    gDI.bBusNo,
                    gDI.bDevFct,
                    PCI_CS_BASE_ADDRESS_1,
                    &gDI.wBasePLX);
                gDI.wBasePLX = gDI.wBasePLX & 0xFFFC;
                printf("\tChange Base address PLX to:    0x%04x\n", gDI.wBasePLX);
            }
            else
            {
                /* board with old mon file (no address at base 5) */
                printf("Old hardware (old mon file)\n");

                gDI.wBaseSwap = gDI.wBasePLX - 0x80;

                write_configuration_word(
                    gDI.bBusNo,
                    gDI.bDevFct,
                    PCI_CS_BASE_ADDRESS_1,
                    gDI.wBaseSwap);

                read_configuration_word(
                    gDI.bBusNo,
                    gDI.bDevFct,
                    PCI_CS_BASE_ADDRESS_1,
                    &gDI.wBasePLX);
                gDI.wBasePLX = gDI.wBasePLX & 0xFFFC;
                printf("\tChange Base address PLX to:    0x%04x\n", gDI.wBasePLX);
            }

            printf("Now we restart the sample !\n");
            printf("Press any key to continue\n");
            while(!kbhit());
            getch();
            goto ReStart;
        }
    }



    /*--- now we can play --------------------------------------*/

    /*--- reset board -----*/
    {
        printf("reset board ...\n");
        outport (gDI.wBaseIO + 0x00, 0x00);         // ToDo: use defines
    }


    /*--- set relais ------*/
    {
        int iTest=0;
        printf("set relais ...\n");
        printf("Press any key to continue\n");
        do
        {
            outport (gDI.wBaseIO + 0x01, iTest);
            outport (gDI.wBaseIO + 0x02, iTest>>8);
            printf("\rSet 0x%02x\n",iTest);
            iTest++;
            sleep(1);
        }while (!kbhit());
        getch();
    }

    /*--- read TTL inputs ------*/
    {
        char cValue;

        printf("read TTL inputs ...\n");
        printf("Press any key to continue\n");
        do
        {
            cValue = inportb(gDI.wBaseIO + 0x03);
            printf("Value 0x%02x\n",cValue);
            sleep(1);
        }while (!kbhit());
        getch();
    }


    /*--- read opto isolated inputs ------*/
    {
        char cValue;

        printf("read opto isolated inputs ...\n");
        printf("Press any key to continue\n");
        do
        {
            cValue = inportb(gDI.wBaseIO + 0x04);
            printf("Value 0x%02x\n",cValue);
            sleep(1);
        }while (!kbhit());
        getch();
    }

    /*--- count interrupts ----------*/
    {
        // Enable interrupt on operating system
        setup_int_vect();

        // Reset irq line on the board
        inportb(gDI.wBaseIO + 0x05);
        inportb(gDI.wBaseIO + 0x06);

        // Enable interrupt on PLX PCI controller
        /* Note: If you using interrupt mode, */
        /* you have to enable PLX-Irq line    */
        /* wBasePLX+0x4C is the PLX-IRQ status register
           Meaning of the bits: (0x43)
           7:   Software Irq    - not used              - 0
           6:   PCI Irq Enable  - we need this          - 1
           5:   Irq 2 status    -
           4:   Irq 2 polarity  -
           3:   Irq 2 enable    -
           2:   Irq 1 status    - we have to read this
           1:   Irq 1 polarity  - alternating from one edge to the next
           0:   Irq 1 enable    - we have to enable it  - 1

        */
        outportb(gDI.wBasePLX + PLX_INT_STA, 0x5B);

        printf("Press any key to continue\n");
        do
        {
            gDI.ulIrqCnt = 0;
            sleep(1);
            // auf einem Pentium 1 mit 100 MHz wurden bis zu 150.000 irqs pro sec gemessen
            printf("Irq per Second: %7lu\n", gDI.ulIrqCnt);

            printf(
                "IrqRegister : %02x\n",
                inportb(gDI.wBasePLX + PLX_INT_STA));
        }while (!kbhit());

        getch();

        // Disable interrupt on PLX PCI controller
        outportb(gDI.wBasePLX + PLX_INT_STA, 0x00);
    }

    /*--- disable outputs ---*/
    //outportb(gDI.wBaseIO + ME9x_WRITE_DISABLE, 0x00);    // write any value to disable

    return 0;
}

/************************************************************************/
/*   Function:   handler                                                 */
/*   Purpose:    check interrupt source and service the interrupt        */
/*   Inputs:     None                                                    */
/*  Outputs: None                                                    */
/************************************************************************/
void interrupt handler(void)
{
    dword int_status;

    int_status = inportb(gDI.wBasePLX + PLX_INT_STA);

    if ((int_status & 0x04) || (int_status & 0x20))
    {
        inportb(gDI.wBaseIO + 0x05);
        inportb(gDI.wBaseIO + 0x06);

        gDI.ulIrqCnt++;
    }
    else
    {
        /* Interrupt is not from our board, call the previous handler */
        _chain_intr(oldhandler);
    }

    /* Specific End of interrupt to clear in-service bit */
    /* Mask upper 5 bits of int. line register          */
    if(gDI.bIrqLine<8)
    {
        outportb(0x20,0x60|(gDI.bIrqLine&0x07));
    }
    else
    {
        /* Issue master then slave EOI */
        outportb(0xa0,0x60|((gDI.bIrqLine-8)&0x07));
        outportb(0x20,0x62);
    }
}



/************************************************************************/
/* SETUP_INT_VECT                                                       */
/*                                                                      */
/* Purpose:  Install the interrupt vector for the interrupt             */
/*           handler and reference the previous handler routine.        */
/* Inputs:       None                                                   */
/* Outputs:  None                                                       */
/************************************************************************/
void setup_int_vect(void)
{
  int mask;

 if(gDI.bIrqLine != 0xff)
    {
        if(gDI.bIrqLine<8)
        {
            gDI.bIrqVector=0x08+gDI.bIrqLine;
        }
            else
        {
            gDI.bIrqVector=0x70+(gDI.bIrqLine-8);
        }
    }


    /* Make sure the system 8259 enables the IRQ with OCW1 @ I/O 21h */
    /* for IRQ0-7 or @ I/O A1h for IRQ8-15 */
    if(gDI.bIrqLine < 8)
    {
        mask = inportb(0x21);
        mask = mask & ~(1<<gDI.bIrqLine);
        outportb(0x21,mask);
    }
        else
    {
        mask = inportb(0xA1);
        mask = mask & ~(1<<(gDI.bIrqLine-8));
        outportb(0xA1,mask);
    }

    /* Save the old interrupt vector */
    oldhandler=getvect(gDI.bIrqVector);

    /* Install the new interrupt vector */
    setvect(gDI.bIrqVector,handler);
}