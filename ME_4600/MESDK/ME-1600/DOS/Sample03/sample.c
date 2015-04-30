/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special settings)                        */
/*  Copyright:      1998-2002 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com)                                                                          */
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
/*                  0.00                    AMCC framework for PCI bus access                               */
/*                  0.01    000727  ab      DOS sample frame for ME-Boards                                  */
/*----------------------------------------------------------------------------------------------------------*/




/****************************************************************************/
/* Include Files                                                            */
/****************************************************************************/
#include <dos.h>
#include <stddef.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "..\amcc.h"
#include "..\sample.h"


/****************************************************************************/
/*   Prototypes                                                             */
/****************************************************************************/


/****************************************************************************/
/* Global variables                                                         */
/****************************************************************************/
DEVINFO gDI;



/*****************************************************************/
/*  MAIN Code Segment                                            */
/*****************************************************************/
int main(void)
{
    clrscr();

    printf( "\n--- ME-1600 DOS sample ---\n\n" );

    ReStart:    // we restart if the PLX bug occure (or if we change the addresses)

    /*--- Look for a valid PCI BIOS -----------------------------*/
    {
        printf("Lokking for a PCI BIOS interface ...\n");

        if(pci_bios_present(NULL,NULL,NULL)==SUCCESSFUL)
        {
            printf("\t... PCI BIOS Found\n");
        }
        else
        {
            printf("PCI BIOS not present\n\n");
            printf("This utility runs only under Windows 95/98 or on a DOS boot disk !\n");
            printf("You can not programming registers directly under Windows NT\n");
            printf("Exit program\n\n");
            getch();
            return(1);
        }
    }

    /*--- look for the Meilhaus ME-1600 devices ------------------*/
    {
        gDI.wVenID      = 0x1402;   // our Vendor ID
        gDI.wDevID      = 0x0000;   // our Device ID
        gDI.wDeviceIdx  = 0;        // first device we could found

        printf( "looking for a ME-16xx board ...\n" );

        for (gDI.wDevID=0x1600; gDI.wDevID<0x1700; gDI.wDevID++)
        {
            if(find_pci_device(
                gDI.wDevID,
                gDI.wVenID,
                gDI.wDeviceIdx,
                &gDI.bBusNo,
                &gDI.bDevFct) == SUCCESSFUL)
            {
                break;
            }
        }

        if (gDI.wDevID==0x1700)
        {
            printf( "\t ... no device found!\n" );

            gDI.wVenID      = 0x10B5;   // PLX Vendor ID
            gDI.wDevID      = 0x9050;   // PLX Device ID
            gDI.wDeviceIdx  = 0;        // first device we could found

            printf( "looking for a alternative board ...\n" );

            if(find_pci_device(
                gDI.wDevID,
                gDI.wVenID,
                gDI.wDeviceIdx,
                &gDI.bBusNo,
                &gDI.bDevFct) != SUCCESSFUL)
            {
                gDI.wDevID = 0x0000;
            }
        }

        switch (gDI.wDevID)
        {
        case 0x1600:
            printf("\t... found a ME-1600 PCI\n");
            break;
        case 0x0000:
            {
                char ch;
                printf( "\t ... no device found!\n" );
                printf("Press any key to exit program\n\n");
                ch = getch();
                printf("Press any key to exit program\n%c\n", ch);
                getch();
                return;
            }
        default:
            printf("... unknown ME-1600 board!\n\n");
        }

        printf("General PCI data: \n\tBus=%d \n\tDevice=%d \n\tFunction=%d\n",
            gDI.bBusNo,
            gDI.bDevFct>>3,
            gDI.bDevFct&0x7);
        printf("\tVendor ID:   0x%04x\n", gDI.wVenID);
        printf("\tDevice ID:   0x%04x\n", gDI.wDevID);
    }


    /*--- Set own resources (if needed) -------------------------*/

    /* if you need special address or interrupt settings         */
    /* for compatibility, this does not work in every case       */
    /* (under windows ???), check it out                         */
#define VERBIEGEN
#undef VERBIEGEN                // comment this if you need
#ifdef VERBIEGEN
    {
        static int DoIt = TRUE;

        gDI.wBaseIO = 0x300;

        if (DoIt == TRUE)
        {
            printf("Set address to specific values:\n");
            printf("\taddress:   0x%04x\n", gDI.wBaseIO);

            write_configuration_word(
                gDI.bBusNo,
                gDI.bDevFct,
                PCI_CS_BASE_ADDRESS_2,
                gDI.wBaseIO);

            DoIt = FALSE;
            printf("Now we restart the sample !\n");
            printf("Press any key to continue\n");
            while(!kbhit());
            getch();
            goto ReStart;
        }
    }
#endif


    /*--- determine resources  -----------------------------------*/
    {
        word    wSerialNumberHigh;
        word    wSerialNumberLow;


        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_1,
            &gDI.wBasePLX);
        gDI.wBasePLX = gDI.wBasePLX & 0xFFFC;

        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_2,
            &gDI.wBaseIO);
        gDI.wBaseIO = gDI.wBaseIO & 0xFFFC;

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

        printf("\tPLX:\t\t%#04X\n\tBase 0:\t\t%#04X\n\tBase 1:\t\t%#04X\n\tserial number:\t\t0x%08lx\n",
            gDI.wBasePLX, gDI.wBaseIO, gDI.wBaseIO2, gDI.dwSerialNumber);
    }



    /*--- now we can play --------------------------------------*/

    /*
    registers:
    (the board consists of 4 DAC chips with 4 channels in it)

    //  0x00:   wr      DA channel 0    (16 bit wide, we use bit 0..11 only)
    //  0x02:   wr      DA channel 1    (16 bit wide, we use bit 0..11 only)
    //  ..
    //  0x1E:   wr      DA channel 15   (16 bit wide, we use bit 0..11 only)
    //  0x20:   rd      unipolar/bipolar (every channel - one bit)
    //  0x22:   rd/wr   0..20 mA / 4..20 mA (only lower 8 bit valid)
    //  0x24:   wr      load/set all channels in one DAC chip (only lower 4 bit valid)
                        (gepuffertes schreiben simultan)
    //  0x26:   rd/wr   current on/off (only lower 8 bit valid)
    */

    /*--- reset board -----*/
    {
        long iCtrl50;

        // after power on or software reset following settings are valid:
        //  * current: off
        //  * mode: bipolar
        //  * outputs: 0 Volt

        // software reset via PLX controller
        printf("reset board ...\n");

        iCtrl50 = inpd(gDI.wBasePLX + 0x50);

        iCtrl50 = iCtrl50 | 0x40000000;
        outpd(gDI.wBasePLX + 0x50, iCtrl50);

        iCtrl50 = iCtrl50 & 0xBFFFFFFF;
        outpd(gDI.wBasePLX + 0x50, iCtrl50);
    }



    /*--- set values on unipolar mode voltage out ------*/
    {
        int iValue;

        printf("write single values in unipolar mode ...\n");
        printf("Press a key to start ...\n");
        getch();
        printf("Press a key to stop ...\n");


        // set bipolar mode
        outport(gDI.wBaseIO + 0x20, 0x0000);

        // transparent output
        outport(gDI.wBaseIO + 0x24, 0x0000);

        while(!kbhit())
        {
            for (iValue=0; iValue<=0x0FFF; iValue = iValue+2)
            {
                delay(1);
                outport(gDI.wBaseIO, iValue);
            }
        }
        getch();
    }

    return 0;
}
