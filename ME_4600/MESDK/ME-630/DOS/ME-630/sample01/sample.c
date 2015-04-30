/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special settings)                        */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com)                                                                          */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                  without an interrupt                                                                    */
/*                  without PLX bug workaround (we need it only for interrupt processing)                   */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    000222  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#include <dos.h>
#include <stddef.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "amcc.h"
#include "sample.h"

#ifdef MSC
#define outport(port,val)   outp(port,val)
#define inport(port)        inp(port)
#endif




/* Global Variable Definition */

typedef struct _DEV_INFO
{
    word    wVenID;
    word    wDevID;
    byte    bBusNo;
    byte    bDevFct;
    word    wDeviceIdx;
    dword   dwSerialNumber;
    word    wBaseIO;
} DEVINFO;


DEVINFO gDI;


/*****************************************************************/
/* MAIN Code Segment                                            */
/*****************************************************************/
void main()
{
    /* Look for a valid PCI BIOS */
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
        }
    }

    /* look for the Meilhaus ME-630 device */
    {
        gDI.wVenID      = 0x1402;
        gDI.wDevID      = 0x0630;
        gDI.wDeviceIdx  = 0;

        if(find_pci_device(
            gDI.wDevID,
            gDI.wVenID,
            gDI.wDeviceIdx,
            &gDI.bBusNo,
            &gDI.bDevFct)  ==  SUCCESSFUL)
        {
          printf("ME-630 Device Found: \n\tBus=%d \n\tDevice=%d \n\tFunction=%d\n\n",
                gDI.bBusNo,
                gDI.bDevFct>>3,
                gDI.bDevFct&0x7);
      }
      else
        {
          printf("Meilhaus ME-630 Device Not Found\n\n");
            printf("Exit program\n\n");
            getch();
        }
    }


    /* if you need special address and interrupt settings for compatibility */
    /* this works not under windows !!! ??? */
//#define VERBIEGEN
#ifdef VERBIEGEN
    {
        gDI.wBaseIO = 0x300;
        gDI.bIrqLine= 5;

        write_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_2,
            gDI.wBaseIO);
    }
#endif


    /* determine resources */
    {
        word    wSerialNumberHigh;
        word    wSerialNumberLow;

        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_2,
            &gDI.wBaseIO);
        gDI.wBaseIO = gDI.wBaseIO & 0xFFFC;
        printf("\tBase address ME-630 register:    0x%04x\n", gDI.wBaseIO);

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


    /*--- 1. reset board -----*/
    {
        printf("reset board ...\n");
        outport (gDI.wBaseIO + 0x00, 0x00);
    }


    /*--- 2. set relais ------*/
    {
        int iCnt;

        printf("set relais ...\n");
        for(iCnt=0; iCnt<0x10; iCnt++)
        {
            outport (gDI.wBaseIO + 0x01, iCnt);
            outport (gDI.wBaseIO + 0x02, iCnt>>8);
            printf("0x%02x\t",iCnt);
            sleep(1);
            if (kbhit()) break;
        }
        getch();
    }


    /*--- 3. read TTL inputs ------*/
    {
        byte cValue;

        printf("\nread TTL inputs ...\n");
        printf("Press any key to continue\n");
        do
        {
            cValue = inportb(gDI.wBaseIO + 0x03);
            printf("Value 0x%02x\n",cValue);
            sleep(1);
        }while (!kbhit());
        getch();
    }


    /*--- 4. read opto isolated inputs ------*/
    {
        byte cValue;

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


    /*--- 5. interrupt processing ----------*/
    {
    }

    getch();
}



