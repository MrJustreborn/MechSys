/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.cpp                                                                              */
/*  Compiler:       tested with Visual C++ 6.0 and Borland C Builder 4.0                                    */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to Ralph Timm for the function wrapper                                   */
/*                                                                                                          */
/*  Description:    Example for GeneralReset                                                                */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    030731  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/


/*--- system header files -------*/
#include <stdio.h>
#include <windows.h>
#include <conio.h>

/*--- me3000 header files -------*/
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


void ErrorHandler(int);
void WrongParameters();

int main (int argc, char *argv[])
{	
    int iErrorCode;
    int iBoardNumber;
    int iFoundIt;
    int iDelay;
    int iArgvCnt;

    printf("This program will cancel all AI functions after a given time\n");

    /*--- Boardnumber ---*/
    iFoundIt = 0;
    for(iArgvCnt=1; iArgvCnt<argc; iArgvCnt++)
    {
        if (strstr(argv[iArgvCnt], "board"))
        {
            sscanf(1+strchr(argv[iArgvCnt],':'), "%d", &iBoardNumber);
            iFoundIt = 1;
            break;
        }
    }

    if (!iFoundIt)
    {
        WrongParameters();
        return 1;
    }

    /*--- delay: ---*/
    iFoundIt = 0;
    for(iArgvCnt=1; iArgvCnt<argc; iArgvCnt++)
    {
        if (strstr(argv[iArgvCnt], "delay"))
        {
            sscanf(1+strchr(argv[iArgvCnt],':'), "%d", &iDelay);
            iFoundIt = 1;
            break;
        }
    }

    if (!iFoundIt)
    {
        WrongParameters();
        return 1;
    }
    
    printf("Bord number is %d\n", iBoardNumber);
    printf("Wait %d milliseconds ...\n", iDelay);
    printf("... run AIStop\n");
    
    Sleep(iDelay);
    meOpen();  // calls the initialize function
    //iErrorCode = me3000GeneralReset(iBoardNumber);
    iErrorCode = me3000AIStop (iBoardNumber);
    meClose();

    return 0;
}





void WrongParameters(void)
{
    printf("Wrong parameters\n");

    printf("Please using following format and values:\n");
    printf("resettimer.exe /board:0 /delay:5\n");
    printf("/board:     number of board\n");
    printf("/delay:     reset in xxx milliseconds (decimal)\n");
   
    printf("Program aborted!\n");
}

void ErrorHandler(int iLine)
{
    printf("Error in file %s in line: %04d\n", __FILE__, iLine);
    exit(0);
}
