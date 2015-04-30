/*      Sample.cpp : Text based (Console)           */
/*      program to test all the routines in the     */
/*      ME8100 interface.                           */
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
    - you have to include the me8100.lib file
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
    - use the include file me8100.h
    - use the compiler MS Visual C 6.00
If you would like to use dynamic binding:
      (All the following steps are done in
      this exsample:)
    - use the include file me8100Init.h
    - use the function me8100Open at the
      start of the program
    - use the function me8100Close at the
      end of the program
    - include the source code file
      "me8100Init.cpp" in the project.  This
      file contains the "me8100Open" and
      "me8100Close" functions which must be
      called from the main program.  The
      "me8100Open" function opens the library
      and gets the address of all the DLL
      functions.  The "me8100Close" function
      simply closes the library at the end of
      the program.
    - The source code file "me8100Init" also
      has all of the "Wrapper" functions.  This
      allows the user to use the full and proper
      function names when calling them from the
      main program.
*/


/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\DLLInit.cpp");
#endif

#include <stdio.h>
#include <conio.h>
#include <windows.h>

//#include ".\..\me8100.h"
#include ".\..\DLLInit.h"


void _stdcall Beep(int i_context)
{
    printf("\n\n******************   INTERRUPT!   *****************\n\n");
}


int main(void)
{
    BOOL bBoardPresent[ME_MAX_DEVICES];
    int iBoardNumber = -1;

    // calls the initialize function
    meOpen();


    for(int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
    {
        int iVersion;

        if( me8100PROMVersion(index_board, &iVersion) )
        {
            bBoardPresent[index_board] = TRUE;

            if(iBoardNumber == -1)
            {
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
        printf("Current Board Number: %d    Current Register Set: %C\n\n",
                                            iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B') );
        printf("========================\n\n");

        printf("Choose a command                            \n");
        printf("A) Set board number and register set        \n\n");
        printf("B) GetDLLVersion        C) GetPROMVersion   \n");
        printf("D) EnableInt            E) DisableInt       \n\n");
        printf("F) GetDrvErrMess                            \n\n");
        printf("G) GetIntStatus         H) SetIntMode       \n");

        printf("I) SetTristateON        J) SetTristateOFF   \n");
        printf("K) SetPattern           L) SetMask          \n\n");
        printf("M) GetBit               N) GetWord          \n");
        printf("O) SetBit               P) SetWord          \n\n");
        printf("Q) GetIrqCnt            R) GetDevInfo       \n");
        printf("S) WriteUserString      T) ReadUserString   \n\n");
        printf("U) CntWrite             V) CntRead          \n\n");
        printf("W) SetSinkSourceMode                        \n\n");
        printf("X) End Program                              \n\n");

        printf("Command (A - X) : ");

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
                printf("\n\n");

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

            while(TRUE)
            {
                printf("Register Set (A/B): ");

                gets( &buffer[0] );

                printf("\n\n");

                if( (buffer[0] == 'a') ||(buffer[0] == 'A'))
                {
                        iCurrentRegisterSet = 0;

                        break;
                }
                else if( (buffer[0] == 'b') ||(buffer[0] == 'B'))
                {
                        iCurrentRegisterSet = 1;

                        break;
                }
            }

            break;
            }

        case 'B':

            int dll_version;
            dll_version = me8100GetDLLVersion();

            printf("DLL Version is 0x%08X\n\n", dll_version);

            break;

        case 'C':

            int prom_version;

            if( me8100PROMVersion(iBoardNumber, &prom_version) )
            {
                printf("PROM Version is 0x%08X\n\n", prom_version);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'D':

            if( me8100EnableInt(iBoardNumber, iCurrentRegisterSet, Beep, 0) )
            {
                printf("Board: %d Register set: %C  -  Interrupt Enabled\n\n",
                                            iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B') );
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'E':

            if( me8100DisableInt(iBoardNumber, iCurrentRegisterSet) )
            {
                printf("Board: %d Register set: %C  -  Interrupt Disabled\n\n",
                                            iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B') );
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'F':

            char error_message[256];
            int error_no;

            error_no = me8100GetDrvErrMess(&error_message[0], 256);

            printf("Error No.: 0x%08X\n", error_no);

            if(error_message[0] != 0)
            {
                printf( "Error message: %s\n", &error_message[0] );
            }

            printf("\n");

            break;

        case 'G':

            int i_status;

            if( me8100DIGetIntStatus(iBoardNumber, iCurrentRegisterSet, &i_status) )
            {
                printf("Board: %d Register set: %C  -  Int Status: 0x%04X\n\n",
                                iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'), i_status);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'H':

            int i_mode;

            while(TRUE)
            {
                printf("Int Mode (P - Pattern Compare / B - Bit Change) : ");

                gets( &buffer[0] );

                printf("\n\n");

                if( (buffer[0] == 'p') ||(buffer[0] == 'P'))
                {
                    i_mode = 0;

                    break;
                }
                else if( (buffer[0] == 'b') ||(buffer[0] == 'B'))
                {
                    i_mode = 1;

                    break;
                }
            }

            if( me8100DIOSetIntMode(iBoardNumber, iCurrentRegisterSet, i_mode) )
            {
                printf("Board: %d Register set: %C  -  Set Int Mode: %d\n\n",
                                iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'), i_mode);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'I':

            if( me8100DIOSetTristateON(iBoardNumber, iCurrentRegisterSet) )
            {
                printf("Board: %d Register set: %C  -  Tristate ON\n\n",
                                            iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B') );
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'J':

            if( me8100DIOSetTristateOFF(iBoardNumber, iCurrentRegisterSet) )
            {
                printf("Board: %d Register set: %C  -  Tristate OFF\n\n",
                                            iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B') );
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'K':

            while(TRUE)
            {
                printf("Pattern (4 Digit Hex Integer) : ");

                gets( &buffer[0] );

                printf("\n\n");

                WORD w_pattern;

                if( sscanf(&buffer[0], "%x", &w_pattern) >= 1 )
                {
                    if( me8100DIOSetPattern(iBoardNumber, iCurrentRegisterSet, (int)w_pattern) )
                    {
                        printf("Board: %d Register set: %C  -  Set Pattern: 0x%04X\n\n",
                                    iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'), w_pattern);
                    }
                    else
                    {
                        printf("ERROR!\n\n");
                    }

                    break;
                }
            }

        case 'L':

            while(TRUE)
            {
                printf("Mask (4 Digit Hex Integer) : ");

                gets( &buffer[0] );

                printf("\n\n");

                WORD w_mask;

                if( sscanf(&buffer[0], "%x", &w_mask) >= 1 )
                {
                    if( me8100DIOSetMask(iBoardNumber, iCurrentRegisterSet, (int)w_mask) )
                    {
                        printf("Board: %d Register set: %C  -  Set Mask: 0x%04X\n\n",
                                    iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'), w_mask);
                    }
                    else
                    {
                        printf("ERROR!\n\n");
                    }

                    break;
                }
            }

            break;

        case 'M':

            while(TRUE)
            {
                printf("Bit Number (0 - 15): ");

                gets( &buffer[0] );

                printf("\n\n");

                int i_bit_no;

                if( sscanf(&buffer[0], "%d", &i_bit_no) >= 1 )
                {
                    if( (0 <= i_bit_no)&&(i_bit_no <= 15) )
                    {
                        int i_bit_value;

                        if( me8100DIGetBit(iBoardNumber, iCurrentRegisterSet, i_bit_no, &i_bit_value) )
                        {
                            printf("Board: %d Register set: %C  -  Bit No.: %d is %d\n\n",
                                        iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'),
                                                                    i_bit_no, (i_bit_value == 0) ? 0 : 1);
                        }
                        else
                        {
                            printf("ERROR!\n\n");
                        }

                        break;
                    }
                }
            }

            break;

        case 'N':

            int i_word_value;

            if( me8100DIGetWord(iBoardNumber, iCurrentRegisterSet, &i_word_value) )
            {
                printf("Board: %d Register set: %C  -  Input Word: 0x%04X\n\n",
                            iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'), i_word_value & 0xffff);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'O':

            int i_bit_no;

            while(TRUE)
            {
                printf("Bit Number (0 - 15): ");

                gets( &buffer[0] );

                printf("\n\n");

                if( sscanf(&buffer[0], "%d", &i_bit_no) >= 1 )
                {
                    if( (0 <= i_bit_no)&&(i_bit_no <= 15) )
                    {
                        break;
                    }
                }
            }

            while(TRUE)
            {
                printf("Bit Value (0 / 1): ");

                gets( &buffer[0] );

                printf("\n\n");

                int i_bit_value;

                if( sscanf(&buffer[0], "%d", &i_bit_value) >= 1 )
                {
                    if( (i_bit_value == 0)||(i_bit_value == 1) )
                    {
                        if( me8100DOSetBit(iBoardNumber, iCurrentRegisterSet, i_bit_no, i_bit_value) )
                        {
                            printf("Board: %d Register set: %C  -  Set Bit No.: %d to %d\n\n",
                                        iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'),
                                                                                    i_bit_no, i_bit_value);
                        }
                        else
                        {
                            printf("ERROR!\n\n");
                        }

                        break;
                    }
                }
            }

            break;

        case 'P':

            while(TRUE)
            {
                printf("Output Word (4 Digit Hex Integer) : ");

                gets( &buffer[0] );

                printf("\n\n");

                WORD w_word;

                if( sscanf(&buffer[0], "%x", &w_word) >= 1 )
                {
                    if( me8100DOSetWord(iBoardNumber, iCurrentRegisterSet, (int)w_word) )
                    {
                        printf("Board: %d Register set: %C  -  Output Word: 0x%04X\n\n",
                                    iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'), w_word);
                    }
                    else
                    {
                        printf("ERROR!\n\n");
                    }

                    break;
                }
            }

            break;

        case 'Q':

            int i_count;

            if( me8100GetIrqCnt(iBoardNumber, iCurrentRegisterSet, &i_count) )
            {
                printf("Board: %d Register set: %C  -  IRQ Count: %d\n\n",
                                iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'), i_count);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'R':

            DEVICEINFOSTRUCT dev_info;

            if( me8100GetDevInfo(iBoardNumber, &dev_info) )
            {
                printf("Board: %2d Device Info\n", iBoardNumber);
                printf("----------------------\n\n");

                printf("Vendor ID:          0x%04X\n", dev_info.dwVendorID);
                printf("Device ID:          0x%04X\n", dev_info.dwDeviceID);
                printf("Bus Number:         %u\n", dev_info.dwBusNumber);
                printf("System Slot Number: %u\n", dev_info.dwSystemSlotNumber);
                printf("Port Base:          0x%04X\n", dev_info.dwPortBase);
                printf("Port Count:         %u\n", dev_info.dwPortCount);
                printf("Interrupt Channel:  %u\n", dev_info.dwIntChannel);
                printf("PLX Port Base:      0x%04X\n", dev_info.dwPortBasePLX);
                printf("PLX Port Count:     %u\n", dev_info.dwPortCountPLX);
                printf("Serial Number:      0x%08X\n", dev_info.dwSerialNumber);
                printf("Hardware Revision:  0x%04X\n", dev_info.dwHWRevision);
                printf("IRQ Count:          %u\n", dev_info.dwIrqCnt);
                printf("Version:            0x%04X\n", dev_info.dwVersion);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'S':

            printf("User String: ");

            gets( &buffer[0] );

            printf("\n\n");

            if( me8100WriteUserString(iBoardNumber, &buffer[0]) )
            {
                printf("Board: %d  -  Write User String: %s\n\n", iBoardNumber, &buffer[0]);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'T':

            if( me8100ReadUserString(iBoardNumber, &buffer[0], 256) )
            {
                printf("Board: %d  -  Read User String: %s\n\n", iBoardNumber, &buffer[0]);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'U':

            int i_counter_no;

            while(TRUE)
            {
                printf("Counter Number (0, 1 or 2): ");

                gets( &buffer[0] );

                printf("\n\n");

                if( sscanf(&buffer[0], "%d", &i_counter_no) >= 1 )
                {
                    if( (0 <= i_counter_no)&&(i_counter_no <= 2) )
                    {
                        break;
                    }
                }
            }

            int i_counter_mode;

            while(TRUE)
            {
                printf("Counter Mode (0 - 5): ");

                gets( &buffer[0] );

                printf("\n\n");

                if( sscanf(&buffer[0], "%d", &i_counter_mode) >= 1 )
                {
                    if( (0 <= i_counter_mode)&&(i_counter_mode <= 5) )
                    {
                        break;
                    }
                }
            }

            while(TRUE)
            {
                printf("Value (0 - 65535): ");

                gets( &buffer[0] );

                printf("\n\n");

                int i_value;

                if( sscanf(&buffer[0], "%d", &i_value) >= 1 )
                {
                    if( (0 <= i_value)&&(i_value <= 65535) )
                    {
                        if( me8100CntWrite(iBoardNumber, i_counter_no, i_counter_mode, i_value) )
                        {
                            printf("Board: %d -  Set Counter No.: %d - Mode %d  Count: %u\n\n",
                                            iBoardNumber, i_counter_no, i_counter_mode, i_value);
                        }
                        else
                        {
                            printf("ERROR!\n\n");
                        }

                        break;
                    }
                }
            }

            break;

        case 'V':

            while(TRUE)
            {
                printf("Counter Number (0, 1 or 2): ");

                gets( &buffer[0] );

                printf("\n\n");

                if( sscanf(&buffer[0], "%d", &i_counter_no) >= 1 )
                {
                    if( (0 <= i_counter_no)&&(i_counter_no <= 2) )
                    {
                        int i_value;

                        if( me8100CntRead(iBoardNumber, i_counter_no, &i_value) )
                        {
                            printf("Board: %d -  Read Counter No.: %d - Count: %u\n\n",
                                                    iBoardNumber, i_counter_no, i_value);
                        }
                        else
                        {
                            printf("ERROR!\n\n");
                        }

                        break;
                    }
                }
            }

            break;

        case 'W':

            while(TRUE)
            {
                printf("Mode (Sink / Source): ");

                gets( &buffer[0] );

                printf("\n\n");

                int i_mode = -1;

                if( !stricmp(&buffer[0], "Sink") )
                {
                    i_mode = 0;
                }
                else if( !stricmp(&buffer[0], "Source") )
                {
                    i_mode = 1;
                }


                if(i_mode != -1)
                {
                    if( me8100SetSinkSourceMode(iBoardNumber, iCurrentRegisterSet, i_mode) )
                    {
                        printf("Board: %d Register set: %C  -  Set mode to: %s\n\n",
                                    iBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'),
                                                                        (i_mode == 0) ? "SINK" : "SOURCE");
                    }
                    else
                    {
                        printf("ERROR!\n\n");
                    }

                    break;
                }
            }

            break;

        case 'X':
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
