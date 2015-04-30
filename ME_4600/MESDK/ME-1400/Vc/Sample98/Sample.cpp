/*      Sample.cpp : Text based (Console)           */
/*      program to test all the routines in the     */
/*      ME1400 interface.                           */
/*                                                  */
/*      Program for use with Borland C++            */
/*      and Visual C++ programs                     */
/*                                                  */
/*      This Program uses dynamic function calls    */
/*      and Wrappers for all functions              */

/*
dynamic vs. static binding of a DLL:
------------------------------------

static binding:
    - you have to include the me1400.lib file
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
    - use the include file me1400.h
    - use the compiler MS Visual C 6.00
If you would like to use dynamic binding:
      (All the following steps are done in
      this exsample:)
    - use the include file me1400Init.h
    - use the function meOpen at the
      start of the program
    - use the function meClose at the
      end of the program
    - include the source code file
      "me1400Init.cpp" in the project.  This
      file contains the "meOpen" and
      "meClose" functions which must be
      called from the main program.  The
      "meOpen" function opens the library
      and gets the address of all the DLL
      functions.  The "meClose" function
      simply closes the library at the end of
      the program.
    - The source code file "me1400Init" also
      has all of the "Wrapper" functions.  This
      allows the user to use the full and proper
      function names when calling them from the
      main program.
*/


#include <stdio.h>
#include <conio.h>
#include <windows.h>

//#include ".\..\me1400.h"
#include ".\..\meDefs.h"
#include ".\..\DLLInit.h"

/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\DLLInit.cpp");
#endif


void _stdcall Beep(void)
{
    printf("\n\n******************   INTERRUPT!   *****************\n\n");
}


int main(void)
{
    BOOL bBoardPresent[ME_MAX_DEVICES];
    int iBoardNumber = -1;

    // calls the initialize function
    meOpen();

    // Find all the me1400 boards in the system by calling _me1400GetBoardVersion
    // for all possible board indexes

    for(int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
    {
        int iVersion;

        if( me1400GetBoardVersion(index_board, &iVersion) )
        {
            bBoardPresent[index_board] = TRUE;

            if(iBoardNumber == -1)
            {
                // Choose the first board found as the current board
                iBoardNumber = index_board;
            }
        }
        else
        {
            bBoardPresent[index_board] = FALSE;
        }
    }

    if(iBoardNumber == -1)
    {
        printf("\n\nNo boards were found!\n\n");
        exit(-1);
    }

    char buffer[256];
    BOOL bEndProgram = FALSE;

    while(TRUE)
    {
        printf("Current Board Number: %d\n", iBoardNumber);
        printf("========================\n\n");
        
        printf("Please be sure you made the right hardware\n");
        printf("connections for the function of your choice\n\n");

        printf("Choose a command                            \n");

        printf("A) Set board number                         \n\n");

        printf("B) GetDLLVersion        C) GetDriverVersion \n");
        printf("D) GetBoardVersion      E) GetDrvErrMess    \n\n");
        
        printf("F) EnableInt            G) DisableInt       \n");
        printf("H) GetIrqCnt                                \n\n");

        printf("I) CntInitSrc                               \n");
        printf("J) CntWrite             K) CntRead          \n\n");

        printf("L) CntPWMStart          M) CntPWMStop       \n\n");

        printf("N) DIOSetPortDirection                      \n");
        printf("O) DIGetBit             P) DIGetByte        \n");
        printf("Q) DOSetBit             R) DOSetByte        \n\n");

        printf("Z) internal or obsolete functions           \n\n");
        
        printf("X) End Program                              \n");

        printf("Choose a command: ");
        gets( &buffer[0] );
        buffer[0] = toupper(buffer[0]);
        printf("\n\n");

        if (buffer[0] == 'Z')
        {
            printf("The following functions are not part of the regular API or board \n");
            printf("specifications. Most of them are obsolete or for internal test \n");
            printf("purposes. Meilhaus Electronic offers no support of the following \n");
            printf("functions. A wrong use of this function can damage your hardware.\n\n");

            {
                static int iTimesRead = 0;

                if (iTimesRead < 5)
                {
                    while(!kbhit())
                    {
                        printf("\rPlease read first, press a key when ready");
                        Sleep(700);
                        printf("\r                                         ");
                        Beep(1000, 300);
                        iTimesRead++;
                    }
                    getch();
                }
            }

            printf("\n");
            printf("A) GetSerialNumber      B) GetDevInfo       \n\n");

            printf("C) InportByte           D) OutportByte      \n");
            printf("E) InportWord           F) OutportWord      \n");
            printf("G) InportDWord          H) OutportDWord     \n\n");

            printf("I) ResetBoard           J) InitBoard        \n");
            printf("K) WriteUserString      L) ReadUserString   \n\n");


            printf("M) InitModeTimerA       N) InitModeTimerB   \n\n");

            printf("O) SetMultifunctionPin  P) DIOSetMode       \n\n");

            printf("Q) Return to previous screen                \n\n");

            printf("X) End Program                              \n");

            printf("Choose a command: ");
            gets( &buffer[0] );
            buffer[0] = tolower(buffer[0]);
            printf("\n\n");
        }


        switch(buffer[0])
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
                            iBoardNumber = board_number;
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


        case 'B':   // int me1400GetDLLVersion();
        {
            int iDllVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetDllVersion\n");

            iDllVersion = me1400GetDLLVersion();
            printf("dll version is 0x%08X\n", iDllVersion);

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'C':   // int me1400GetDriverVersion(int *piDriverVersion);
        {
            int iDriverVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetDriverVersion\n");

            if( me1400GetDriverVersion(&iDriverVersion) )
                printf("driver version is 0x%08X\n", iDriverVersion);
            else
                printf("me1400GetDriverVersion: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'D':   // int me1400GetBoardVersion(int iBoardNumber, int *piVersion);
        {
            int iBoardVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetBoardVersion\n");

            if( me1400GetBoardVersion(iBoardNumber, &iBoardVersion) )
                printf("board version is 0x%08X\n", iBoardVersion);
            else
                printf("me1400GetBoardVersion: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'E':   //int me1400GetDrvErrMess(char *pcErrortext, int iBufferSize);
        {
            int iErrorNo;
            char pErrorMessage[256];

            printf("-----------------------------------------------------------\n");
            printf("GetDrvErrMess\n");

            pErrorMessage[0] = 0;
            iErrorNo = me1400GetDrvErrMess(pErrorMessage);
            printf("Error No.: 0x%08X\n", iErrorNo);
            if(pErrorMessage[0] != 0)
                printf("Error message: %s\n", pErrorMessage);
            else
                printf("No Error!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'F':   /*--- EnableInt ---*/
        {
            if( me1400EnableInt(iBoardNumber, Beep, 1) )
            {
                printf("Board: %d -  Interrupt Enabled\n\n", iBoardNumber);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;
        }


        case 'G':   /*--- DisableInt ---*/
        {
            if( me1400DisableInt(iBoardNumber, 1) )
            {
                printf("Board: %d -  Interrupt Disabled\n\n", iBoardNumber);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;
        }


        case 'H':   /*--- GetIrqCnt  ---*/
        {
            int iCount;

            if( me1400GetIrqCnt(iBoardNumber, &iCount) )
            {
                printf("Board: %d -  IRQ Count: %d\n\n", iBoardNumber, iCount);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;
        }




        case 'a':   // int me1400GetSerialNumber(int iBoardNumber, int *piSerialNumber);
        {
            int iSerialNumber;

            printf("-----------------------------------------------------------\n");
            printf("GetSerialNumber\n");

            if( me1400GetSerialNumber(iBoardNumber, &iSerialNumber))
                printf("serial number is 0x%08X\n", iSerialNumber);
            else
                printf("me1400GetSerialNumber: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'b':   // int me1400GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
        {
            DEVICEINFOSTRUCT dev_info;

            printf("-----------------------------------------------------------\n");
            printf("GetDevInfo\n");

            if(me1400GetDevInfo(iBoardNumber, &dev_info))
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
                printf("me1400GetDevInfo: ERROR!\n\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'c':   /*--- me1400InportByte(int iBoardNumber, int iPortOffset, int* pbValue); ---*/
            {
                int iPortOffset;
                int iByte;

                while(TRUE)
                {
                    printf("Port Offset: \n");
                    printf("    Please note: \n");
                    printf("    Get maximum offset with the value of \"Port Count\" \n");
                    printf("    from the function GetDeviceInfo\n");
                    printf("Port Offset (2 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iPortOffset) >= 1 )
                    {
                        if((iPortOffset>=0) && (iPortOffset<=255))
                        {
                            break;
                        }
                    }
                }

                if(me1400InportByte(iBoardNumber, iPortOffset, &iByte))
                {
                    printf("Board: %d - Inport Byte on offset 0x02x has a value of 0x%02x\n",
                        iBoardNumber, iPortOffset, iByte);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'd':   /*--- me1400OutportByte(int iBoardNumber, int iPortOffset, int bValue); ---*/
            {
                int iPortOffset;
                int iByte;

                while(TRUE)
                {
                    printf("Port Offset: \n");
                    printf("    Please note: \n");
                    printf("    Get maximum offset with the value of \"Port Count\" \n");
                    printf("    from the function GetDeviceInfo\n");
                    printf("Port Offset (2 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iPortOffset) >= 1 )
                    {
                        if((iPortOffset>=0) && (iPortOffset<=255))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Output Byte Value (2 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iByte) >= 1 )
                    {
                        if((iByte>=0) && (iByte<=0xFF))
                        {
                            break;
                        }
                    }
                }

                if(me1400OutportByte(iBoardNumber, iPortOffset, iByte))
                {
                    printf("Board: %d - Write Value 0x02x on an adress offset of 0x%02x\n",
                        iBoardNumber, iByte, iPortOffset);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'e':   /*--- me1400InportWord(int iBoardNumber, int iPortOffset, int* pwValue); ---*/
            {
                int iPortOffset;
                int iWord;

                while(TRUE)
                {
                    printf("Port Offset: \n");
                    printf("    Please note: \n");
                    printf("    Get maximum offset with the value of \"Port Count\" \n");
                    printf("    from the function GetDeviceInfo\n");
                    printf("Port Offset (2 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iPortOffset) >= 1 )
                    {
                        if((iPortOffset>=0) && (iPortOffset<=255))
                        {
                            break;
                        }
                    }
                }

                if(me1400InportWord(iBoardNumber, iPortOffset, &iWord))
                {
                    printf("Board: %d - Inport Word with offset 0x02x has a value of 0x%04x\n",
                        iBoardNumber, iPortOffset, iWord);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }

        
        case 'f':   /*--- me1400OutportWord(int iBoardNumber, int iPortOffset, int wValue); ---*/
            {
                int iPortOffset;
                int iWord;

                while(TRUE)
                {
                    printf("Port Offset: \n");
                    printf("    Please note: \n");
                    printf("    Get maximum offset with the value of \"Port Count\" \n");
                    printf("    from the function GetDeviceInfo\n");
                    printf("Port Offset (2 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iPortOffset) >= 1 )
                    {
                        if((iPortOffset>=0) && (iPortOffset<=255))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Output Word Value (4 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iWord) >= 1 )
                    {
                        if((iWord>=0) && (iWord<=0xFFFF))
                        {
                            break;
                        }
                    }
                }

                if(me1400OutportWord(iBoardNumber, iPortOffset, iWord))
                {
                    printf("Board: %d - Write Value 0x04x on an adress offset of 0x%02x\n",
                        iBoardNumber, iWord, iPortOffset);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'g':   /*--- me1400InportDWord(int iBoardNumber, int iPortOffset, int* pwValue); ---*/
            {
                int iPortOffset;
                int iDWord;

                while(TRUE)
                {
                    printf("Port Offset: \n");
                    printf("    Please note: \n");
                    printf("    Get maximum offset with the value of \"Port Count\" \n");
                    printf("    from the function GetDeviceInfo\n");
                    printf("Port Offset (2 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iPortOffset) >= 1 )
                    {
                        if((iPortOffset>=0) && (iPortOffset<=255))
                        {
                            break;
                        }
                    }
                }

                if(me1400InportDWord(iBoardNumber, iPortOffset, &iDWord))
                {
                    printf("Board: %d - Inport Word with offset 0x02x has a value of 0x%08x\n",
                        iBoardNumber, iPortOffset, iDWord);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }

        case 'h':   /*--- me1400OutportDWord(int iBoardNumber, int iPortOffset, int wValue); ---*/
            {
                int iPortOffset;
                int iDWord;

                while(TRUE)
                {
                    printf("Port Offset: \n");
                    printf("    Please note: \n");
                    printf("    Get maximum offset with the value of \"Port Count\" \n");
                    printf("    from the function GetDeviceInfo\n");
                    printf("Port Offset (2 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iPortOffset) >= 1 )
                    {
                        if((iPortOffset>=0) && (iPortOffset<=255))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Output DWord Value (8 Digit Hex Integer) : \n");

                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iDWord) >= 1 )
                    {
                        if((iDWord>=0) && (iDWord<=0xFFFFFFFF))
                        {
                            break;
                        }
                    }
                }

                if(me1400OutportDWord(iBoardNumber, iPortOffset, iDWord))
                {
                    printf("Board: %d - Write Value 0x08x on an adress offset of 0x%02x\n",
                        iBoardNumber, iDWord, iPortOffset);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'i':   /*--- me1400ResetBoard(int iBoardNumber); ---*/
            {
                if(me1400ResetBoard(iBoardNumber))
                {
                    printf("Board: %d - Reset board\n", iBoardNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'j':   /*--- me1400InitBoard(int iBoardNumber); ---*/
            {
                if(me1400InitBoard(iBoardNumber))
                {
                    printf("Board: %d - Init board\n", iBoardNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }

                
        case 'k':   /*--- me1400WriteUserString(int iBoardNumber, char* pcUserText); ---*/
            {
                printf("User String: ");

                gets( &buffer[0] );

                printf("\n\n");
                
                if( me1400WriteUserString(iBoardNumber, &buffer[0]) )
                {
                    printf("Board: %d  -  Write User String: %s\n\n", iBoardNumber, &buffer[0]);
                }
                else
                {
                    printf("ERROR!\n\n");
                }

                break;
            }


        case 'l':   /*--- me1400ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength) ---*/
            {
                if( me1400ReadUserString(iBoardNumber, &buffer[0], 256) )
                {
                    printf("Board: %d  -  Read User String: %s\n\n", iBoardNumber, &buffer[0]);
                }
                else
                {
                    printf("ERROR!\n\n");
                }

                break;
            }


        case 'm':   /*--- me1400InitModeTimerA(int iBoardNumber, int CtrlWordA); ---*/
            {
                int CtrlWordA;

                while(TRUE)
                {
                    printf("Control Word (1 Digit Hex Integer) : ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &CtrlWordA) >= 1 )
                    {
                        if((CtrlWordA>=0) && (CtrlWordA<=0x0F))
                        {
                            break;
                        }
                    }
                }

                if(me1400InitModeTimerA(iBoardNumber, CtrlWordA))
                {
                        printf("Board: %d - ControlWordA 0x%x\n",
                            iBoardNumber, CtrlWordA);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'n':   /*--- me1400InitModeTimerB(int iBoardNumber, int CtrlWordB); ---*/
            {
                int CtrlWordB;

                while(TRUE)
                {
                    printf("Control Word (1 Digit Hex Integer) : ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &CtrlWordB) >= 1 )
                    {
                        if((CtrlWordB>=0) && (CtrlWordB<=0x0F))
                        {
                            break;
                        }
                    }
                }

                if(me1400InitModeTimerB(iBoardNumber, CtrlWordB))
                {
                        printf("Board: %d - ControlWordB 0x%x\n",
                            iBoardNumber, CtrlWordB);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'o':   /*--- me1400SetMultifunctionPin(int iBoardNumber, int iMultiPin); ---*/
            {
                int iMultiPin;

                while(TRUE)
                {
                    printf("IrqIn (0) or ClockOut (1) : ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iMultiPin) >= 1 )
                    {
                        if((iMultiPin>=0) && (iMultiPin<=1))
                        {
                            break;
                        }
                    }
                }

                if(me1400SetMultifunctionPin(iBoardNumber, iMultiPin))
                {
                        printf("Board: %d - MultiPin 0x%x\n",
                            iBoardNumber, iMultiPin);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }

        case 'p':   /*--- me1400DIOSetMode(int iBoardNumber,int iPio, int iMode); ---*/
            {
                int iPio;
                int iMode;

                while(TRUE)
                {
                    printf("Pio : ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iPio) >= 1 )                    
                        break;
                }

                while(TRUE)
                {
                    printf("Mode : ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iMode) >= 1 )                    
                        break;
                }

                if(me1400DIOSetMode(iBoardNumber, iPio, iMode))
                {
                    printf("Board: %d - me1400DIOSetMode OK\n",
                        iBoardNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'I':   /*--- CntInitSrc ---*/
            {
                int iCounter;
                int iCounterSource;

                while(TRUE)
                {
                    printf("Counter Number (0..29): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iCounter) >= 1 )
                    {
                        if((iCounter>=0) && (iCounter<=29))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Counter Source(0..3 for SubD(0), 1MHz(1), 10MHz(2),  Prev(3)): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iCounterSource) >= 1 )
                    {
                        if((iCounterSource>=0) && (iCounterSource<=3))
                        {
                            break;
                        }
                    }
                }

                if(me1400CntInitSrc(iBoardNumber, iCounter, iCounterSource))
                {
                    printf("Board: %d - Set source for counter %d to %d\n",
                        iBoardNumber, iCounter, iCounterSource);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'J':   /*--- me1400CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue); ---*/
            {
                int iCounter;
                int iMode;
                int iValue;

                while(TRUE)
                {
                    printf("Counter Number (0..29): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iCounter) >= 1 )
                    {
                        if((iCounter>=0) && (iCounter<=29))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Counter Mode (0..5): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iMode) >= 1 )
                    {
                        if((iMode>=0) && (iMode<=5))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Counter Value (4 Digit Hex Integer) : ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iValue) >= 1 )
                    {
                        if ((iValue >= 0) && (iValue <= 0xFFFF))
                            break;
                    }
                }

                if(me1400CntWrite(iBoardNumber, iCounter, iMode, iValue))
                {
                    printf("Board: %d - Write Counter %d in Mode %d with Value 0x%04x\n",
                        iBoardNumber, iCounter, iMode, iValue);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'K':   /*--- me1400CntRead(int iBoardNumber, int iCounter, int* piValue); ---*/
            {
                int iCounter;
                int iValue;

                while(TRUE)
                {
                    printf("Counter Number (0..29): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iCounter) >= 1 )
                    {
                        if((iCounter>=0) && (iCounter<=29))
                        {
                            break;
                        }
                    }
                }

                if(me1400CntRead(iBoardNumber, iCounter, &iValue))
                {
                    printf("Board: %d - Read value 0x%04X on Counter %d \n",
                        iBoardNumber, iValue, iCounter);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'L':   /*--- me1400CntPWMStart(int iBoardNumber, int iDeviceNumber, int iClockSource, int iPrescaler, int iDutyCycle); ---*/
            {
                int iDeviceNumber;
                int iClockSource;
                int iPrescaler;
                int iDutyCycle;

                while(TRUE)
                {
                    printf("Device Number (0..9): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iDeviceNumber) >= 1 )
                    {
                        if((iDeviceNumber>=0) && (iDeviceNumber<=9))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Clock Source(0..3 for SubD(0), 1MHz(1), 10MHz(2),  Prev(3)): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iClockSource) >= 1 )
                    {
                        if((iClockSource>=0) && (iClockSource<=3))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Prescaler (2..65535): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iPrescaler) >= 1 )
                    {
                        if((iPrescaler>=2) && (iPrescaler<=65535))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Duty Cycle (1..99): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iDutyCycle) >= 1 )
                    {
                        if((iDutyCycle>=1) && (iDutyCycle<=99))
                        {
                            break;
                        }
                    }
                }

                if(me1400CntPWMStart(iBoardNumber, iDeviceNumber, iClockSource, iPrescaler, iDutyCycle))
                {
                    printf("Board: %d - PWM Start Device %d - Clk. Source: %d Pre-Scaler: %d Duty Cycle: %d\n",
                        iBoardNumber, iDeviceNumber, iClockSource, iPrescaler,iDutyCycle );
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'M':   /*--- me1400CntPWMStop(int iBoardNumber, int iDeviceNumber); ---*/
            {
                int iDeviceNumber;

                while(TRUE)
                {
                    printf("Device Number (0..2): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iDeviceNumber) >= 1 )
                    {
                        if((iDeviceNumber>=0) && (iDeviceNumber<=2))
                        {
                            break;
                        }
                    }
                }


                if(me1400CntPWMStop(iBoardNumber, iDeviceNumber))
                {
                    printf("Board: %d - PWM Stop Device %d\n", iBoardNumber, iDeviceNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'N':   /*--- me1400DIOSetPortDirection(int iBoardNumber, int iPort, int iDir); ---*/
            {
                int iPort;
                int iDir;


                while(TRUE)
                {
                    printf("Port Number (A(0) B(1) C(2) CL(3) CH(4) D(8) E(9) F(10) FL(11) FH(12)): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iPort) >= 1 )
                    {
                        if((iPort>=0) && (iPort<=12))
                        {
                            break;
                        }
                    }
                }

                while(TRUE)
                {
                    printf("Port Direction: INPUT(0) or OUTPUT(1): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iDir) >= 1 )
                    {
                        if((iDir>=0) && (iDir<=1))
                        {
                            break;
                        }
                    }
                }

                if(me1400DIOSetPortDirection(iBoardNumber, iPort, iDir))
                {
                    if (iDir==0)
                        printf("Board: %d - SetPortDirection on Port %d to INPUT\n",
                            iBoardNumber, iPort);
                    else
                        printf("Board: %d - SetPortDirection on Port %d to OUTPUT\n",
                            iBoardNumber, iPort);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'O':   /*--- int me1400DIGetBit(int iBoardNumber, int iPort,int iBitNo, int *piValue); ---*/
            {
                int iPort;
                int iBitNo;
                int iValue;

                while(TRUE)
                {
                    printf("Port Number (A(0) B(1) C(2) CL(3) CH(4) D(8) E(9) F(10) FL(11) FH(12)): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iPort) >= 1 )
                    {
                        if((0<=iPort) && (iPort<=12))
                        break;
                    }
                }

                while(TRUE)
                {
                    printf("Bit Number (0..7): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iBitNo) >= 1 )
                    {
                        if((0<=iBitNo) && (iBitNo<=7))
                        break;
                    }
                }

                if(me1400DIGetBit(iBoardNumber, iPort, iBitNo, &iValue))
                {
                    if (iValue==0)
                        printf("Board: %d - Bit Number %d on Port %d is 0 (0 Volt)\n",
                            iBoardNumber, iBitNo, iPort);
                    else
                        printf("Board: %d - Bit Number %d on Port %d is 1 (5 Volt)\n",
                            iBoardNumber, iBitNo, iPort);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'P':   /*--- int me1400DIGetByte(int iBoardNumber, int iPortNo, int *piValue); ---*/
            {
                int iPortNo;
                int iValue;

                while(TRUE)
                {
                    printf("Port Number (A(0) B(1) C(2) CL(3) CH(4) D(8) E(9) F(10) FL(11) FH(12)): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iPortNo) >= 1 )
                    {
                        if((0<=iPortNo) && (iPortNo<=12))
                        break;
                    }
                }

                if(me1400DIGetByte(iBoardNumber, iPortNo, &iValue))
                {
                    printf("Board: %d - Byte on Port: %d is 0x%02x \n", 
                        iBoardNumber, iPortNo, iValue);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'Q':   /*--- int me1400DOSetBit(int iBoardNumber,int iPort, int iBitNo, int iBitValue); ---*/
            {
                int iPort;
                int iBitNo;
                int iBitValue;

                while(TRUE)
                {
                    printf("Port Number (A(0) B(1) C(2) CL(3) CH(4) D(8) E(9) F(10) FL(11) FH(12)): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iPort) >= 1 )
                    {
                        if((0<=iPort) && (iPort<=12))
                        break;
                    }
                }

                while(TRUE)
                {
                    printf("Bit Number (0..7): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iBitNo) >= 1 )
                    {
                        if((0<=iBitNo) && (iBitNo<=7))
                        break;
                    }
                }

                while(TRUE)
                {
                    printf("Bit Value: 0(0) or 1(1): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iBitValue) >= 1 )
                    {
                        if((0<=iBitValue) && (iBitValue<=1))
                        break;
                    }
                }

                if(me1400DOSetBit(iBoardNumber, iPort, iBitNo, iBitValue))
                {
                    printf("Board: %d - Set Bit on Port %d bit number %d is %d\n",
                        iBoardNumber, iPort, iBitNo, iBitValue);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'R':   /*--- int me1400DOSetByte(int iBoardNumber, int iPortNo, int iValue); ---*/
            {
                int iPortNo;
                int iValue;

                while(TRUE)
                {
                    printf("Port Number (A(0) B(1) C(2) CL(3) CH(4) D(8) E(9) F(10) FL(11) FH(12)): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iPortNo) >= 1 )
                    {
                        if((0<=iPortNo) && (iPortNo<=12))
                        break;
                    }
                }

                while(TRUE)
                {
                    printf("Byte Value (2 Digit Hex Integer) : ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%x", &iValue) >= 1 )
                    {
                        if ((iValue >= 0) && (iValue <= 0xFF))
                            break;
                    }
                }

                if(me1400DOSetByte(iBoardNumber, iPortNo, iValue))
                {
                    printf("Board: %d - Set Byte on Port %d to 0x%02x\n",
                        iBoardNumber, iPortNo, iValue);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'X':   /*--- beenden ---*/
        {
            bEndProgram = TRUE;
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

    meClose();

    return 0;
}
