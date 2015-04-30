/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special settings)                        */
/*  Copyright:      1998-2002 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau), sw (Stefan Weidlich)                                               */
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
/*                  1.00    020201  sw      AOSingle, Reset, Timer, WrapAround for Channel 0 and 2          */
/*                  1.01    020219  ab      download, fix some checks,                                      */
/*----------------------------------------------------------------------------------------------------------*/




/****************************************************************************/
/* Include Files                                                            */
/****************************************************************************/
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "..\amcc.h"
#include "..\sample.h"


/****************************************************************************/
/*   Prototypes                                                             */
/****************************************************************************/
void WriteSval( int, unsigned short );
short ReadCtrl( int );
void WriteCtrl( int, short );
void WriteTimer( int, DWORD);
void WriteFifo( int, short*, unsigned );

/****************************************************************************/
/* Global variables                                                         */
/****************************************************************************/
DEVINFO gDI;
char buffer[256];



/*****************************************************************/
/*  MAIN Code Segment                                            */
/*****************************************************************/
void main(void)
{
    int iValue;
    unsigned long int iCnt = 0;
    char line[50];
    char szInputFile[256] ="mefw.stp";
    FILE *readfile;
    char digit[10] = "0x00";
    int iTimeOut;
    unsigned int i;

    clrscr();

    ReStart:    // we restart if the PLX bug occure (or if we change the addresses)

    printf( "\n--- ME-6000/6100 DOS sample ---\n\n" );

    /*--- Look for a valid PCI BIOS -----------------------------*/
    {
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
            return;
        }
    }

    /*--- look for the Meilhaus ME-6x00 devices ------------------*/
    {
        gDI.wVenID      = 0x1402;   // our Vendor ID
        gDI.wDevID      = 0x0000;   // our Device ID
        gDI.wDeviceIdx  = 0;        // first device we could found

        printf( "looking for a ME-6xxx board ...\n" );

        for (gDI.wDevID=0x6000; gDI.wDevID<0x6400; gDI.wDevID++)
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

        if (gDI.wDevID==0x6400)
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
                char ch;

                gDI.wDevID = 0x0000;
                printf( "\t ... no device found!\n" );
                printf("Press any key to exit program\n\n");
                ch = getch();
                printf("Press any key to exit program\n%c\n", ch);
                getch();
                return;
            }
        }

        switch (gDI.wDevID)
        {
        case 0x6114:
            printf("\t... found a ME-6100 Opto 4 channels with FIFO \n");
            break;
        default:
            printf("Unknown ME-6000/6100 board!\n\n");
        }

        printf("General PCI data: \n\tBus=%d \n\tDevice=%d \n\tFunction=%d\n",
            gDI.bBusNo,
            gDI.bDevFct>>3,
            gDI.bDevFct&0x7);
        printf("\tVendor ID:   0x%04x\n", gDI.wVenID);
        printf("\tDevice ID:   0x%04x\n", gDI.wDevID);
    }


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
            PCI_CS_BASE_ADDRESS_3,
            &gDI.wBaseIO2);
        gDI.wBaseIO2 = gDI.wBaseIO2 & 0xFFFC;

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


    /*--- download firmware ------------------*/
    {
        printf("download firmware ...");

        readfile   = fopen( szInputFile,  "rt" );
        if (readfile == NULL)
        {
            printf("\n\t--> error: Can't open inputfile: %s\n", szInputFile);
            return;
        }

        // Set PLX local interrupt 2 polarity to high  (nessecary)
        outp((gDI.wBasePLX + 0x4c), 0x10);

        /*             _____     __         */
        /* User Drives WRITE and CS Low     */
        iValue = inpw(gDI.wBasePLX + 0x50);     // PLX_ICR
        iValue = iValue | 0x0100;
        outpw(gDI.wBasePLX + 0x50, iValue);

        // Init Xilinx with CS1 (Prog)
        inp(gDI.wBaseIO2 + 0x200);

        // wait of Init pin (till set)
        while(1)
        {
            iValue = inp(gDI.wBasePLX + 0x4c);  // PLX_INTCSR
            if (iValue & 0x20) break;
        }

        // Write User DIO (CSWrite resets Xilinx)
        iValue = inpw(gDI.wBasePLX + 0x50);     // PLX_ICR
        iValue = iValue & 0xFEFF;
        outpw(gDI.wBasePLX + 0x50, iValue);

        while(fgets(line, 40, readfile))
        {
            // convert line into binary
            for(i=0; i<(strlen(line)/2); i++)
            {
                digit[2] = line[2 * i];
                digit[3] = line[2 * i + 1];

                /* Load One Configuration Byte on   */
                /* Next CCLK Rising Edge            */
                outp(gDI.wBaseIO, strtol(digit, NULL, 16));

                iCnt++;
                if ((iCnt%0x900)==0) printf(".");

                /* FPGA Driving BUSY High           */
                for(iTimeOut=0; iTimeOut<0x100; iTimeOut++)
                {
                    iValue = inpw(gDI.wBasePLX + 0x50); // PLX_ICR

                    if ((iValue & 0x0800) == 0)     // busy flag
                        break;                      // springt aus WHILE Schleife
                                                    // => schreibt nächsten Wert
                }

                /* Done Pin */
                if ((iValue & 0x0004) && (iCnt == 1))       // done flag
                {
                    printf("\n\t... second download in this session ==> no download neccesary\n");
                    fseek(readfile, 0, SEEK_END);       // force EOF
                }
            }
        }

        /* done flag ? */
        if ( iValue & 0x0004)       // done flag
        {
            printf("\n\t... download successfully\n");
        }
        else
        {
            printf("\n\t... download failed\n");
        }

        printf("\n%lu bytes written..\n", iCnt);

        /*             _____     __         */
        /* User Drives WRITE and CS High    */
        outpw(gDI.wBasePLX + 0x50, (inpw(gDI.wBasePLX + 0x50) | 0x0100));

        fclose(readfile);
    }

    printf("Please connect a high density voltmeter to channel 2 (third line: 0,1,2) \n\n");
    {
        int iChannel = 2;
        unsigned short value;

        if( iChannel < 4 )
        {
            // stop converting, set single mode
            WriteCtrl( iChannel, 0x04 );
        }
        
        // 0x7FFF -> output voltage = 0 Volt
        for (value = 0x7FFF; value < 0x8009; value++)
        {
            printf("Press any key to confirm value 0x%04x\n", value);
            getch();
            WriteSval( iChannel, value );
        }
    }
}



//------ ReadCtrl ------
short ReadCtrl( int iChannel )
{
    WORD wReturnValue = inpw(gDI.wBaseIO + iChannel*0x18);
    printf("\t[0x%04x] <= 0x%04x\t(ReadCtrl)\n", gDI.wBaseIO+iChannel*0x18, wReturnValue);
    return wReturnValue;
}

//------ WriteCtrl ------
void WriteCtrl( int iChannel, short ctrl )
{
    printf("\t[0x%04x] => 0x%04x\t(WriteCtrl)\n", gDI.wBaseIO + iChannel*0x18, ctrl);
    outpw( gDI.wBaseIO + iChannel*0x18, ctrl );
}

//------ WriteSval ------
void WriteSval( int iChannel, unsigned short value )
{
    unsigned svalReg = (iChannel < 4) ? gDI.wBaseIO + 0x0c + iChannel*0x18 :
                                     gDI.wBaseIO + 0x74 + (iChannel-4)*4;

    printf("\t[0x%04x] => 0x%04x\t(WriteSval)\n", svalReg, value);
    outpw( svalReg, value);
}

//------ WriteTimer ------
void WriteTimer( int iChannel, DWORD ticks)
{
    unsigned timerReg = gDI.wBaseIO + 0x10 + iChannel*0x18;
    printf("\t[0x%04x] => 0x%08x\t(WriteTimer)\n", timerReg, ticks );
    outpd( timerReg, ticks );
}

//------ WriteFifo ------
void WriteFifo( int iChannel, short* pBuffer, unsigned size )
{
    int i;
    unsigned fifoReg = gDI.wBaseIO + 0x08 + iChannel*0x18;

    for( i = 0; i < size; ++i )
    {
        printf("\t[0x%04x] => 0x%04x\t(WriteFifo)\n", fifoReg, pBuffer[i]);
        outpw( fifoReg, pBuffer[i] );
    }
}
