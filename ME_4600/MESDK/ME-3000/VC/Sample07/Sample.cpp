/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         rt (Ralph Timm)                                                                         */
/*                                                                                                          */
/*  Description:    Sample to demonstrate the propertys of the new VEC models                               */
/*                  For this sample you have to use the new VEC driver in the directory tools               */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    981016  rt      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/


/*--- system header files -------*/
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream.h>
#include <stdio.h>
#include <windows.h>

/*--- me3000 header files ---*/
#include ".\..\meDefs.h"
//#include ".\..\me3000.h"
#include ".\..\DLLInit.h"

/*--- Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEFILE("..\meDefs.h");
USEFILE("..\DLLInit.h");
USEUNIT("..\DLLInit.cpp");
#endif


void main (void)
{
    int     i;
    int     retval;
    short   buffer[4096];
    char    szText[1024];

    meOpen();  // calls the initialize function

    retval = me3000AISetTimer (0,0,5);

    //
    // Clear channel list any setup a new one
    //----------------------------------------
    retval = me3000AIClearChannelList (0);
    for (i=0;i < 2;i++)
    {
        retval = me3000AIAddToChannelList (0,i);
    }



    //
    // Clear any oold data
    //----------------------------------------
    retval = me3000AIClearDataFIFO(0);

    //
    // Loop until the job is done
    //---------------------------------------
    retval = me3000AIStartByExternalTrigger(0, AI3000_TRIGGER_EXT_LOW);
    // AI3000_TRIGGER_EXT_LOW  0x02
    // AI3000_TRIGGER_EXT_HIGH 0x04


    //
    // Wait a bit to collect triggers
    //---------------------------------------
    MessageBox(0,"Press any key...","",0);

    //
    // Read data from AD FIFO
    //---------------------------------------
    retval = me3000AIReadFIFO(0, buffer, 2048);


/*
    wsprintf(szText,
             "%d %d %d %d %d %d %d %d %d %d\n"
             "%d %d %d %d %d %d %d %d %d %d\n",
             buffer[0],  buffer[2],  buffer[4],  buffer[6],  buffer[8],
             buffer[10], buffer[12], buffer[14], buffer[16], buffer[18],
             buffer[20], buffer[22], buffer[24], buffer[26], buffer[28],
             buffer[30], buffer[32], buffer[34], buffer[36], buffer[38]
             );

    MessageBox(0,szText,"",0);
*/
#if 1
    i=0;
    wsprintf(szText,
             "%d %d %d %d %d %d %d %d %d %d\n"
             "%d %d %d %d %d %d %d %d %d %d\n",
             buffer[i], buffer[i+1], buffer[i+2], buffer[i+3], buffer[i+4],
             buffer[i+5], buffer[i+6], buffer[i+7], buffer[i+8], buffer[i+9],
             buffer[i+10], buffer[i+11], buffer[i+12], buffer[i+13], buffer[i+14],
             buffer[i+15], buffer[i+16], buffer[i+17], buffer[i+18], buffer[i+19]
             );

    MessageBox(0,szText,"",0);
#else
    i=0;
    wsprintf(szText,
             "%d %d %d %d %d %d %d %d %d %d\n"
             "%d %d %d %d %d %d %d %d %d %d\n",
             buffer[i], buffer[i+2], buffer[i+4], buffer[i+6], buffer[i+8],
             buffer[i+10], buffer[i+12], buffer[i+14], buffer[i+16], buffer[i+18],
             buffer[i+20], buffer[i+22], buffer[i+24], buffer[i+26], buffer[i+28],
             buffer[i+30], buffer[i+32], buffer[i+34], buffer[i+36], buffer[i+38]
             );

    MessageBox(0,szText,"",0);


    i=1;
    wsprintf(szText,
             "%d %d %d %d %d %d %d %d %d %d\n"
             "%d %d %d %d %d %d %d %d %d %d\n",
             buffer[i], buffer[i+2], buffer[i+4], buffer[i+6], buffer[i+8],
             buffer[i+10], buffer[i+12], buffer[i+14], buffer[i+16], buffer[i+18],
             buffer[i+20], buffer[i+22], buffer[i+24], buffer[i+26], buffer[i+28],
             buffer[i+30], buffer[i+32], buffer[i+34], buffer[i+36], buffer[i+38]
             );

    MessageBox(0,szText,"",0);
#endif

    meClose();

    printf ("\n  ***** Press Return to quit *****");
    getchar ();
}
