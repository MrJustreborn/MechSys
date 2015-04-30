/*      Sample.cpp : Text based (Console)           */
/*      program to test all the routines in the     */
/*      ME1600 interface.                           */
/*                                                  */
/*      Program for use with Borland C++            */
/*      and Visual C++ programs                     */
/*                                                  */
/*      This Program uses dynamic function calls    */
/*      and Wrappers for all the ME1600 functions   */

/*
dynamic vs. static binding of a DLL:
------------------------------------

static binding:
    - you have to include the me1600.lib file
      in the project workspace
    - then you can use every function in the DDL
      like a locally existing function
      (with the appropriate prototypes)
    - in some cases there are problems with
      different compiler versions !!!

dynamic binding:
    - you have to open a DLL with
      "LoadLibrary"
    - you have to get a function pointer with
      "GetProcAddress"
    - then you can use every DLL exported
      function with its function pointer

In this sample we have done most of the steps
for you:
If you would like to use static binding:
    - include the lib file
    - use the include file me1600.h
    - use the compiler MS Visual C 6.00
If you would like to use dynamic binding:
      (All the following steps are done in
      this exsample:)
    - use the include file me1600Init.h
    - use the function me1600Open at the
      start of the program
    - use the function me1600Close at the
      end of the program
    - include the source code file
      "me1600Init.cpp" in the project.  This
      file contains the "me1600Open" and
      "me1600Close" functions which must be
      called from the main program.  The
      "me160Open" function opens the library
      and gets the address of all the DLL
      functions.  The "me1600Close" function
      simply closes the library at the end of
      the program.
    - The source code file "me1600Init" also
      has all of the "Wrapper" functions.  This
      allows the user to use the full and proper
      function names when calling them from the
      main program.
*/


/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\me1600Init.cpp");
#endif

/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>

/*  These are the me1600 header files    */
#include ".\..\me1600.h"
#include ".\..\meDefs.h"
//#include ".\..\me1600Init.h"



int main(void)
{
    BOOL bBoardPresent[ME_MAX_DEVICES];
    int iCurrentBoardNumber = -1;

    // calls the initialize function
    // me1600Open();

    // Find all the me1600 boards in the system by calling _me1600GetBoardVersion
    // for all possible board indexes

    for(int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
    {
        int iVersion;

        if( me1600GetBoardVersion(index_board, &iVersion) )
        {
            bBoardPresent[index_board] = TRUE;

            if(iCurrentBoardNumber == -1)
            {
                // Choose the first board found as the current board
                iCurrentBoardNumber = index_board;
            }
        }
        else
        {
            bBoardPresent[index_board] = FALSE;
        }
    }

    if(iCurrentBoardNumber == -1)
    {
        printf("\n\nNo ME1600 boards were found!\n\n");
        exit(-1);
    }

    int iCurrentRegisterSet = 0;
    char buffer[256];
    BOOL bEndProgram = FALSE;

    while(TRUE)
    {
        printf("Current Board Number: %d\n", iCurrentBoardNumber);
        printf("========================\n\n");

        printf("Choose a command                            \n");
        printf("General functions:                          \n");
        printf("A) Set board number     B) GetBoardVersion  \n");
        printf("C) GetDLLVersion        D) GetDriverVersion \n");
        printf("E) GetSerialNumber      F) GetDevInfo       \n");
        printf("G) GetDrvErrMess        \n");
        printf("X) End Program          \n\n");

        printf("Hardware functions:     \n");
        printf("L) AOSetMode    \n");
        printf("M) AOSetRange   \n");
        printf("N) AOSingle     \n");
        printf("O) AOUpdate     \n");
        printf("P) AOUpdateAll  \n");
        printf("Q) AOResetAll   \n");
        printf("R) AOSetCurrent \n");

        printf("Choose a command: ");
        gets( &buffer[0] );
        printf("\n\n");

        switch(toupper(buffer[0]))
        {
        case 'A':   /*--- Set Board Number ---*/
        {
            while(TRUE)
            {
                printf("Board Number (");

                BOOL b_board_found = FALSE;

                for(int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
                {
                    if( bBoardPresent[index_board] )
                    {
                        if(!b_board_found)
                        {
                            printf("%d", index_board);
                            b_board_found = TRUE;
                        }
                        else
                        {
                            printf(", %d", index_board);
                        }
                    }
                }
                printf(") :");

                gets( &buffer[0] );
                printf("\n");

                int board_number;

                if( sscanf(&buffer[0], "%d", &board_number) >= 1 )
                {
                    if( (0 <= board_number)&&(board_number < ME_MAX_DEVICES) )
                    {
                        if( bBoardPresent[board_number] )
                        {
                            iCurrentBoardNumber = board_number;
                            break;
                        }
                        else
                        {
                            printf("Board not found\n");
                        }
                    }
                }
            }

            break;
        }

        case 'B':   // int me1600GetBoardVersion(int iBoardNumber, int *piVersion);
        {
            int iBoardVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetBoardVersion\n");

            if( me1600GetBoardVersion(iCurrentBoardNumber, &iBoardVersion) )
                printf("board version is 0x%08X\n", iBoardVersion);
            else
                printf("me1600GetBoardVersion: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'C':   // int me1600GetDLLVersion();
        {
            int iDllVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetDllVersion\n");

            iDllVersion = me1600GetDLLVersion();
            printf("dll version is 0x%08X\n", iDllVersion);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'D':   // int me1600GetDriverVersion(int *piDriverVersion);
        {
            int iDriverVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetDriverVersion\n");

            if( me1600GetDriverVersion(&iDriverVersion) )
                printf("driver version is 0x%08X\n", iDriverVersion);
            else
                printf("me1600GetDriverVersion: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'E':   // int me1600GetSerialNumber(int iBoardNumber, int *piSerialNumber);
        {
            int iSerialNumber;

            printf("-----------------------------------------------------------\n");
            printf("GetSerialNumber\n");

            if( me1600GetSerialNumber(iCurrentBoardNumber, &iSerialNumber))
                printf("serial number is 0x%08X\n", iSerialNumber);
            else
                printf("me1600GetSerialNumber: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'F':   // int me1600GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
        {
            DEVICEINFOSTRUCT dev_info;

            printf("-----------------------------------------------------------\n");
            printf("GetDevInfo\n");

            if(me1600GetDevInfo(iCurrentBoardNumber, &dev_info))
            {
                printf("Vendor ID:          0x%04X\n",  dev_info.dwVendorID);
                printf("Device ID:          0x%04X\n",  dev_info.dwDeviceID);
                printf("Bus Number:         %u\n",      dev_info.dwBusNumber);
                printf("System Slot Number: %u\n",      dev_info.dwSystemSlotNumber);
                printf("Port Base:          0x%04X\n",  dev_info.dwPortBase);
                printf("Port Count:         %u\n",      dev_info.dwPortCount);
                printf("Interrupt Channel:  %u\n",      dev_info.dwIntChannel);
                printf("PLX Port Base:      0x%04X\n",  dev_info.dwPortBasePLX);
                printf("PLX Port Count:     %u\n",      dev_info.dwPortCountPLX);
                printf("Serial Number:      0x%08X\n",  dev_info.dwSerialNumber);
                printf("Hardware Revision:  0x%04X\n",  dev_info.dwHWRevision);
                printf("IRQ Count:          %u\n",      dev_info.dwIrqCnt);
                printf("Version:            0x%04X\n",  dev_info.dwVersion);
            }
            else
                printf("me1600GetDevInfo: ERROR!\n\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'G':   //int me1600GetDrvErrMess(char *pcErrortext, int iBufferSize);
        {
            int iErrorNo;
            char pErrorMessage[256];

            printf("-----------------------------------------------------------\n");
            printf("GetDrvErrMess\n");

            pErrorMessage[0] = 0;
            iErrorNo = me1600GetDrvErrMess(pErrorMessage, 256);
            printf("Error No.: 0x%08X\n", iErrorNo);
            if(pErrorMessage[0] != 0)
                printf("Error message: %s\n", pErrorMessage);
            else
                printf("No Error!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'X':   /*--- beenden ---*/
        {
            bEndProgram = TRUE;
            break;
        }



        case 'L':   /*--- AOSetMode ---*/
            {
                int ch;
                int iChannelGroup;
                int iOutMode;

                while(TRUE)
                {
                    printf("Channel Group (A..D or 0..3): ");
                    ch = getche();
                    printf("\n");
                    if (((ch>='A') && (ch<='D'))  ||
                        ((ch>='a') && (ch<='d'))  ||
                        ((ch>='0') && (ch<='3')))
                    {
                        if ((ch>='A') && (ch<='D'))
                            iChannelGroup = ch - 'A';
                        else if ((ch>='a') && (ch<='d'))
                            iChannelGroup = ch - 'a';
                        else
                            iChannelGroup = ch - '0';
                        break;
                    }
                }

                while(TRUE)
                {
                    printf("Out Mode BUFFERED (simultaneously)(B or 0) or TRANSPARENT(T or 1): ");
                    ch = getche();
                    printf("\n");
                    if ((ch=='B') || (ch=='b') || (ch=='0') || (ch=='T') || (ch=='T') || (ch=='1'))
                    {
                        switch (ch)
                        {
                        case 'B':
                        case 'b':
                        case '0':
                            iOutMode = 0;
                            break;
                        case 'T':
                        case 't':
                        case '1':
                            iOutMode = 1;
                            break;
                        }
                        break;
                    }
                }

                if(me1600AOSetMode(iCurrentBoardNumber, iChannelGroup, iOutMode))
                {
                    if (iOutMode == 0)
                    {
                        printf("Board: %d - Set Mode for Channel Group: %c to BUFFERED\n",
                                                iCurrentBoardNumber, iChannelGroup+'A');
                    }
                    else
                    {
                        printf("Board: %d - Set Mode for Channel Group: %c to TRANSPARENT\n",
                                                iCurrentBoardNumber, iChannelGroup+'A');
                    }
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'm':
        case 'M':   /*--- AOSetRange ---*/
            {
                int ch;
                int iChannelNumber;
                int iRange;             // AO_BIPOLAR, AO_UNIPOLAR

                while(TRUE)
                {
                    printf("Channel Number (0..15): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iChannelNumber) >= 1 )
                    {
                        if((iChannelNumber>=0) && (iChannelNumber<=15))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Output Range UNIPOLAR(U or 0) or BIPOLAR(B or 1): ");
                    ch = getche();
                    printf("\n");
                    if ((ch=='U') || (ch=='u') || (ch=='0') || (ch=='B') || (ch=='b') || (ch=='1'))
                    {
                        switch (ch)
                        {
                        case 'U':
                        case 'u':
                        case '0':
                            iRange = 0;
                            break;
                        case 'B':
                        case 'b':
                        case '1':
                            iRange = 1;
                            break;
                        }
                        break;
                    }
                }

                if(me1600AOSetRange(iCurrentBoardNumber, iChannelNumber, iRange))
                {
                    if (iRange == 0)
                    {
                        printf("Board: %d - Set Range for Channel: %d to UNIPOLAR\n",
                                                iCurrentBoardNumber, iChannelNumber);
                    }
                    else
                    {
                        printf("Board: %d - Set Range for Channel: %d to BIPOLAR\n",
                                                iCurrentBoardNumber, iChannelNumber);
                    }
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }



        case 'n':
        case 'N':   /*--- AOSingle ---*/
            {
                int iChannelNumber;     // AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_15
                short iValue;           // 0x000..0xFFF

                while(TRUE)
                {
                    printf("Channel Number (0..15): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iChannelNumber) >= 1 )
                    {
                        if((iChannelNumber>=0) && (iChannelNumber<=15))
                        {
                            break;
                        }
                    }
                }


                while(TRUE)
                {
                    printf("Output Word (3 Digit Hex Integer) : ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iValue) >= 1 )
                    {
                        if ((iValue >= 0) && (iValue <= 0xFFF))
                            break;
                    }
                }

                if(me1600AOSingle(iCurrentBoardNumber, iChannelNumber, iValue))
                {
                    printf("Board: %d - Write value 0x%03X on Channel %d \n",
                        iCurrentBoardNumber, iValue, iChannelNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }

        case 'o':
        case 'O':   /*--- AOUpdate ---*/
            {
                int ch;
                int iChannelGroup;

                while(TRUE)
                {
                    printf("Channel Group (A..D or 0..3): ");
                    ch = getche();
                    printf("\n");
                    if (((ch>='A') && (ch<='D'))  ||
                        ((ch>='a') && (ch<='d'))  ||
                        ((ch>='0') && (ch<='3')))
                    {
                        if ((ch>='A') && (ch<='D'))
                            iChannelGroup = ch - 'A';
                        else if ((ch>='a') && (ch<='d'))
                            iChannelGroup = ch - 'a';
                        else
                            iChannelGroup = ch - '0';
                        break;
                    }
                }

                if(me1600AOUpdate(iCurrentBoardNumber, iChannelGroup))
                {
                    printf("Board: %d - Update Channel Group: %c \n",
                        iCurrentBoardNumber, iChannelGroup+'A');
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }

        case 'p':
        case 'P':   /*--- AOUpdateAll ---*/
            {
                if(me1600AOUpdateAll(iCurrentBoardNumber))
                {
                    printf("Board: %d - Update All Channels\n", iCurrentBoardNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }

        case 'q':
        case 'Q':   /*--- AOResetAll ---*/
            {
                if(me1600AOResetAll(iCurrentBoardNumber))
                {
                    printf("Board: %d - Reset board\n", iCurrentBoardNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'r':
        case 'R':   /*--- AOSetCurrent ---*/
            {
                int ch;
                int iChannelNumber;     // AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_15
                int iCurrentMode;       // AO_CURRENT_ON, AO_CURRENT_OFF
                int iRange;             // AO_BIPOLAR, AO_UNIPOLAR

                while(TRUE)
                {
                    printf("Channel Number (0..15): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iChannelNumber) >= 1 )
                    {
                        if((iChannelNumber>=0) && (iChannelNumber<=15))
                        {
                            break;
                        }
                    }
                }


                while(TRUE)
                {
                    printf("Current mode: CURRENT_OFF(0) or CURRENT_ON(1): ");
                    ch = getche();
                    printf("\n");
                    if ((ch=='0') || (ch=='1'))
                    {
                        if (ch=='0')
                            iCurrentMode = AO_CURRENT_OFF;
                        else
                            iCurrentMode = AO_CURRENT_ON;
                        break;
                    }
                }

                while(TRUE)
                {
                    printf("Output Range 0..20(0) or 4..20(4): ");
                    ch = getche();
                    printf("\n");
                    if ((ch=='0') || (ch=='4'))
                    {
                        switch (ch)
                        {
                        case '0':
                            iRange = AO_RANGE_0_20;
                            break;
                        case '4':
                            iRange = AO_RANGE_4_20;
                            break;
                        }
                        break;
                    }
                }

                if(me1600AOSetCurrent(
                    iCurrentBoardNumber,
                    iChannelNumber,
                    iCurrentMode,
                    iRange))
                {
                    printf("Board: %d - Set Current on Channel %d ",
                        iCurrentBoardNumber,
                        iChannelNumber);

                    if (iCurrentMode == 0)
                    {
                        printf("OFF ");
                    }
                    else
                    {
                        printf("ON ");
                    }

                    if (iRange == 0)
                    {
                        printf("with a RANGE of 0..20 mA\n");
                    }
                    else
                    {
                        printf("with a RANGE of 4..20 mA\n");
                    }
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }
        }

        if(!bEndProgram)
        {
            printf("Press any key for main menu, ESC to exit\n");

            char ch = _getch();

            if(ch == 27)
            {
                bEndProgram = TRUE;
            }
        }

        if(bEndProgram)
        {
            break;
        }
    }

    //me1600Close();

    return 0;
}
