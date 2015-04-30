/*      Sample.cpp : Text based (Console)           */
/*      program to test all the routines in the     */
/*      ME9x interface.                             */
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
    - you have to include the me9x.lib file
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
    - use the include file me9x.h
    - use the compiler MS Visual C 6.00
If you would like to use dynamic binding:
      (All the following steps are done in
      this exsample:)
    - use the include file me9xInit.h
    - use the function meOpen at the
      start of the program
    - use the function meClose at the
      end of the program
    - include the source code file
      "DLLInit.cpp" in the project.  This
      file contains the "meOpen" and
      "meClose" functions which must be
      called from the main program.  The
      "meOpen" function opens the library
      and gets the address of all the DLL
      functions.  The "meClose" function
      simply closes the library at the end of
      the program.
    - The source code file "DLLInit" also
      has all of the "Wrapper" functions.  This
      allows the user to use the full and proper
      function names when calling them from the
      main program.
*/


#include <stdio.h>
#include <conio.h>
#include <windows.h>

//#include ".\..\me9x.h"
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

    // Find all the me9x boards in the system by calling me9xGetBoardVersion
    // for all possible board indexes

    for(int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
    {
        int iVersion;

        if( me9xGetBoardVersion(index_board, &iVersion) )
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

    int iCurrentRegisterSet = 0;
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

        printf("M) DIGetBit             N) DIGetByte        \n");
        printf("O) DOSetBit             P) DOSetByte        \n\n");

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


        case 'B':   // int me9xGetDLLVersion();
        {
            int iDllVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetDllVersion\n");

            iDllVersion = me9xGetDLLVersion();
            printf("dll version is 0x%08X\n", iDllVersion);

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'C':   // int me9xGetDriverVersion(int *piDriverVersion);
        {
            int iDriverVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetDriverVersion\n");

            if( me9xGetDriverVersion(&iDriverVersion) )
                printf("driver version is 0x%08X\n", iDriverVersion);
            else
                printf("me9xGetDriverVersion: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'D':   // int me9xGetBoardVersion(int iBoardNumber, int *piVersion);
        {
            int iBoardVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetBoardVersion\n");

            if( me9xGetBoardVersion(iBoardNumber, &iBoardVersion) )
                printf("board version is 0x%08X\n", iBoardVersion);
            else
                printf("me9xGetBoardVersion: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'E':   //int me9xGetDrvErrMess(char *pcErrortext, int iBufferSize);
        {
            int iErrorNo;
            char pErrorMessage[256];

            printf("-----------------------------------------------------------\n");
            printf("GetDrvErrMess\n");

            pErrorMessage[0] = 0;
            iErrorNo = me9xGetDrvErrMess(pErrorMessage);
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
            if( me9xEnableInt(iBoardNumber, Beep) )
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
            if( me9xDisableInt(iBoardNumber) )
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

            if( me9xGetIrqCnt(iBoardNumber, 0, &iCount) )
            {
                printf("Board: %d -  IRQ Count: %d\n\n", iBoardNumber, iCount);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;
        }




        case 'a':   // int me9xGetSerialNumber(int iBoardNumber, int *piSerialNumber);
        {
            int iSerialNumber;

            printf("-----------------------------------------------------------\n");
            printf("GetSerialNumber\n");

            if( me9xGetSerialNumber(iBoardNumber, &iSerialNumber))
                printf("serial number is 0x%08X\n", iSerialNumber);
            else
                printf("me9xGetSerialNumber: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'b':   // int me9xGetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
        {
            DEVICEINFOSTRUCT dev_info;

            printf("-----------------------------------------------------------\n");
            printf("GetDevInfo\n");

            if(me9xGetDevInfo(iBoardNumber, &dev_info))
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
                printf("me9xGetDevInfo: ERROR!\n\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'c':   /*--- me9xInportByte(int iBoardNumber, int iPortOffset, int* pbValue); ---*/
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

                if(me9xInportByte(iBoardNumber, iPortOffset, &iByte))
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


        case 'd':   /*--- me9xOutportByte(int iBoardNumber, int iPortOffset, int bValue); ---*/
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

                if(me9xOutportByte(iBoardNumber, iPortOffset, iByte))
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


        case 'e':   /*--- me9xInportWord(int iBoardNumber, int iPortOffset, int* pwValue); ---*/
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

                if(me9xInportWord(iBoardNumber, iPortOffset, &iWord))
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

        
        case 'f':   /*--- me9xOutportWord(int iBoardNumber, int iPortOffset, int wValue); ---*/
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

                if(me9xOutportWord(iBoardNumber, iPortOffset, iWord))
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


        case 'g':   /*--- me9xInportDWord(int iBoardNumber, int iPortOffset, int* pwValue); ---*/
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

                if(me9xInportDWord(iBoardNumber, iPortOffset, &iDWord))
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

        case 'h':   /*--- me9xOutportDWord(int iBoardNumber, int iPortOffset, int wValue); ---*/
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

                if(me9xOutportDWord(iBoardNumber, iPortOffset, iDWord))
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


        case 'i':   /*--- me9xResetBoard(int iBoardNumber); ---*/
            {
                if(me9xResetBoard(iBoardNumber))
                {
                    printf("Board: %d - Reset board\n", iBoardNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'j':   /*--- me9xInitBoard(int iBoardNumber); ---*/
            {
                if(me9xInitBoard(iBoardNumber))
                {
                    printf("Board: %d - Init board\n", iBoardNumber);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }

                
        case 'k':   /*--- me9xWriteUserString(int iBoardNumber, char* pcUserText); ---*/
            {
                printf("User String: ");

                gets( &buffer[0] );

                printf("\n\n");
                
                if( me9xWriteUserString(iBoardNumber, &buffer[0]) )
                {
                    printf("Board: %d  -  Write User String: %s\n\n", iBoardNumber, &buffer[0]);
                }
                else
                {
                    printf("ERROR!\n\n");
                }

                break;
            }


        case 'l':   /*--- me9xReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength) ---*/
            {
                if( me9xReadUserString(iBoardNumber, &buffer[0], 256) )
                {
                    printf("Board: %d  -  Read User String: %s\n\n", iBoardNumber, &buffer[0]);
                }
                else
                {
                    printf("ERROR!\n\n");
                }

                break;
            }


        case 'M':   /*--- int me9xDIGetBit(int iBoardNumber, int iPort,int iBitNo, int *piValue); ---*/
            {
                int iBitNo;
                int iValue;

                while(TRUE)
                {
                    printf("Bit Number (0..17): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iBitNo) >= 1 )
                    {
                        if((0<=iBitNo) && (iBitNo<=17))
                        break;
                    }
                }

                if(me9xDIGetBit(iBoardNumber, iBitNo, &iValue))
                {
                    if (iValue==0)
                        printf("Board: %d - Bit Number %d is 0 (0 Volt)\n",
                            iBoardNumber, iBitNo);
                    else
                        printf("Board: %d - Bit Number %d is 1 (5 Volt)\n",
                            iBoardNumber, iBitNo);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'N':   /*--- int me9xDIGetByte(int iBoardNumber, int iPortNo, int *piValue); ---*/
            {
                int iPortNo;
                int iValue;

                while(TRUE)
                {
                    printf("Port Number: ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iPortNo) >= 1 )
                    {
                        if((0<=iPortNo) && (iPortNo<=12))
                        break;
                    }
                }

                if(me9xDIGetByte(iBoardNumber, iPortNo, &iValue))
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


        case 'O':   /*--- int me9xDOSetBit(int iBoardNumber,int iPort, int iBitNo, int iBitValue); ---*/
            {
                int iBitNo;
                int iBitValue;

                while(TRUE)
                {
                    printf("Bit Number (0..17): ");
                    gets( &buffer[0] );
                    printf("\n");
                    if( sscanf(&buffer[0], "%d", &iBitNo) >= 1 )
                    {
                        if((0<=iBitNo) && (iBitNo<=17))
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

                if(me9xDOSetBit(iBoardNumber, iBitNo, iBitValue))
                {
                    printf("Board: %d - Set Bit on bit number %d is %d\n",
                        iBoardNumber, iBitNo, iBitValue);
                }
                else
                {
                    printf("ERROR!\n");
                }

                break;
            }


        case 'P':   /*--- int me9xDOSetByte(int iBoardNumber, int iPortNo, int iValue); ---*/
            {
                int iPortNo;
                int iValue;

                while(TRUE)
                {
                    printf("Port Number: ");
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

                if(me9xDOSetByte(iBoardNumber, iPortNo, iValue))
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
