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
void WriteSval( int, short );
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

    /*--- now we can play ------------------*/
    {
        short pBuffer[8192];
        pBuffer[0] = 0xFFFF;
        pBuffer[1] = 0x0000;

        // reset
        /*
        printf("Press a key to AOReset (0V out)\n");
        getch();
        WriteCtrl( 0, 0x04 );
        WriteSval( 0, 0x7FFF);
        */

        // wrap around
        printf("Press a key to AOWrapAround\n");
        getch();
        WriteCtrl( 0, 0x00);        // clear mode, reset fifo, disable interrupt, allow converting, triggered by software
        WriteCtrl( 0, 0x01 | 0x08); // set wrap mode, enable fifo
        WriteFifo( 0, pBuffer, 2);  // fill fifo
        WriteTimer( 0, 64);         // set timer
        WriteSval( 0, 0 );          // start converting by dummy write to sval reg

        // stop wrap around
        printf("Press a key to AOStop\n");
        getch();
        WriteCtrl( 0, ReadCtrl(0) | 0x04);  // stop converting
    }


    while( TRUE )
    {
        printf("\n");
        printf("R) reset channel\n");
        printf("S) set single value\n");
        printf("T) set timer \n");
        printf("W) start 'wrapAround' mode\n");
        printf("X) stop 'wrapAround' mode\n");
        printf("E) end program\n\n");

        printf("Choose a command: ");
        gets( &buffer[0] );

        switch( toupper(buffer[0]) )
        {
            case 'R':
            {
                int iChannel;

                printf("reset channel\n");

                printf("channel (0..15) : ");
                gets(buffer);
                sscanf(buffer, "%d", &iChannel);

                if( iChannel > 15 )
                {
                    printf( "Wrong channel!\n" );
                    break;
                }

                if( iChannel < 4 )
                {
                    // stop converting, set single mode
                    WriteCtrl( iChannel, 0x04 );
                }

                WriteSval( iChannel, 0x7FFF ); // 0x7FFF -> output voltage = 0 Volt

                break;
            }

            case 'S':
            {
                int iChannel, value;

                printf("set single value\n");

                printf("channel (0..15) : ");
                gets(buffer);
                sscanf(buffer, "%d", &iChannel);

                if( iChannel > 15 )
                {
                    printf( "Wrong channel!\n" );
                    break;
                }

                printf("value (0..ffff) : ");
                gets(buffer);
                sscanf(buffer, "%x", &value);

                if( iChannel < 4 )
                {
                    // stop converting, set single mode
                    WriteCtrl( iChannel, 0x04 );
                }

                WriteSval( iChannel, value );
                break;
            }

            case 'T':
            {
                int iChannel, ticks;

                printf("set timer\n");

                // check if timer (FIFO) available:
                if( !(gDI.wDevID & 0x100) )
                {
                    printf( "No timer available!\n" );
                    break;
                }

                printf("channel (0..3)  : ");
                gets(buffer);
                sscanf(buffer, "%d", &iChannel);

                if( iChannel > 3 )
                {
                    printf( "Wrong channel!\n" );
                    break;
                }

                printf("ticks (66..2^32): ");
                gets(buffer);
                sscanf(buffer, "%d", &ticks);

                if( ticks < 66 )
                {
                    printf( "Wrong tick count!\n" );
                    break;
                }

                WriteTimer( iChannel, ticks );
                break;
            }

            case 'W':
            {
                int iChannel, size, ticks, i;
                short delta, ctrl, pBuffer[ 8192 ];

                printf("start 'wrapAround' mode\n");

                // check if FIFO available:
                if( !(gDI.wDevID & 0x100) )
                {
                    printf( "No FIFO available!\n" );
                    break;
                }

                printf("channel (0/2)   : ");
                gets(buffer);
                sscanf(buffer, "%d", &iChannel);

                if( (iChannel != 0) && (iChannel != 2) )
                {
                    printf( "Wrong channel!\n" );
                    break;
                }

                printf("size (2..8192)  : ");
                gets(buffer);
                sscanf(buffer, "%d", &size);

                if( size > 8192 )
                    size = 8192;

                printf("ticks (66..2^32): ");
                gets(buffer);
                sscanf(buffer, "%d", &ticks);
                if( ticks < 66 )
                {
                    printf( "Wrong tick count!\n" );
                    break;
                }

                delta = 0xffff / (size-1);
                for( i = 0; i < size; i++ )
                    pBuffer[ i ] = i * delta;

                // clear mode, reset fifo, disable interrupt, allow converting,
                // triggered by software
                ctrl = 0;
                WriteCtrl( iChannel, ctrl );

                // set wrap mode, enable fifo
                ctrl |= 0x01 | 0x08;
                WriteCtrl( iChannel, ctrl );

                // fill fifo
                WriteFifo( iChannel, pBuffer, size );

                // set timer
                WriteTimer( iChannel, ticks );

                // start converting by dummy write to sval reg
                WriteSval( iChannel, 0 );

                break;
            }

            case 'X':
            {
                int iChannel;
                short ctrl;

                printf("stop 'wrapAround' mode\n");

                printf("channel (0/2)   : ");
                gets(buffer);
                sscanf(buffer, "%d", &iChannel);

                if( (iChannel != 0) && (iChannel != 2) )
                {
                    printf( "Wrong channel!\n" );
                    break;
                }

                // read control reg
                ctrl = ReadCtrl( iChannel);

                // stop converting
                ctrl |= 0x04;
                WriteCtrl( iChannel, ctrl );

                break;
            }

            case 'E':
                return;

            default:
                printf( "Wrong command!\n" );
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
void WriteSval( int iChannel, short value )
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
