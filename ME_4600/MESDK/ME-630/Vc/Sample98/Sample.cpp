/*      Sample.cpp : Text based (Console)           */
/*      program to test all the routines in the     */
/*      ME-630 interface.                           */
/*                                                  */
/*      Program for use with Borland C++            */
/*      and Visual C++ programs                     */
/*                                                  */
/*      This Program uses dynamic function calls    */
/*      and Wrappers for all the ME-630 functions   */

/*
dynamic vs. static binding of a DLL:
------------------------------------

static binding:
    - you have to include the me630.lib file
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
    - use the include file me630.h
    - use the compiler MS Visual C 6.00
If you would like to use dynamic binding:
      (All the following steps are done in 
      this exsample:)
    - use the include file me630Init.h
    - use the function me630Open at the
      start of the program
    - use the function me630Close at the
      end of the program
    - include the source code file 
      "m3630Init.cpp" in the project.  This 
      file contains the "me630Open" and 
      "m3630Close" functions which must be 
      called from the main program.  The 
      "m3630Open" function opens the library 
      and gets the address of all the DLL 
      functions.  The "m3630Close" function 
      simply closes the library at the end of
      the program.
    - The source code file "m3630Init" also 
      has all of the "Wrapper" functions.  This 
      allows the user to use the full and proper
      function names when calling them from the 
      main program.
*/


/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\me630Init.cpp");
#endif

/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>

/*  These are the me630 header files    */
//#include ".\..\me630.h"
#include ".\..\meDefs.h"
#include ".\..\DLLInit.h"


void _stdcall Beep(int i_context)
{
    printf("\n\n******************   INTERRUPT!   *****************\n\n");
}


int main(void)
{
	HANDLE  h_console = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;

	coord.X = 120;
	
	coord.Y = 2000;
	
	SetConsoleScreenBufferSize(h_console, coord);

    BOOL bBoardPresent[ME_MAX_DEVICES];

    // calls the initialize function
    meOpen();


    int iCurrentBoardNumber = -1;

	// Find all the me630 boards in the system by calling _me630GetBoardVersion
	// for all possible board indexes
    
	for(int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
    {
        int i_version;
        
        if( _me630GetBoardVersion(index_board, &i_version) )
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
        printf("\n\nNo ME630 boards were found!\n\n");

        exit(-1);
    }
    
    int iCurrentRegisterSet = 0;
    
    char buffer[256];
    
    BOOL bEndProgram = FALSE;
    
    while(TRUE)
    {
        printf("Current Board Number: %d\n\n", iCurrentBoardNumber);
        
        printf("Choose a command							\n\n");

        printf("A) Set board number                         \n\n");
        printf("B) GetDLLVersion        C) GetBoardVersion	\n\n");
        printf("D) EnableInt            E) DisableInt		\n\n");
        printf("F) GetDrvErrMess							\n\n");
        printf("G) ResetRelays								\n");
        printf("H) SetRelayBit          I) SetRelayWord		\n");
        printf("J) GetRelayBit          K) GetRelayWord		\n\n");
        printf("L) GetTTLBit            M) GetTTLByte		\n");
        printf("N) GetOptoBit           O) GetOptoByte   	\n\n");
        printf("P) GetIrqCnt            Q) GetDevInfo		\n\n");
        printf("R) WriteUserString      S) ReadUserString	\n\n");
        
        printf("T) DIOResetAll          U) DIOConfig	    \n\n");
        printf("V) DIOGetByte           W) DIOSetByte	    \n");
        printf("X) DIOGetBit            Y) DIOSetBit	    \n\n");
        
        printf("Z) End Program								\n\n");
        
        printf("Command (A - Z) : ");
        
        gets( &buffer[0] );

        printf("\n\n");
        
        switch( buffer[0] )
        {
        case 'a':
        case 'A':

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
                            iCurrentBoardNumber = board_number;

                            break;
                        }
                        else
                        {
                            printf("Board not found\n\n");
                        }
                    }
                }
            }

            break;

        case 'b':
        case 'B':

            int dll_version;
            dll_version = _me630GetDLLVersion();
            
            printf("DLL Version is 0x%08X\n\n", dll_version);

            break;

        case 'c':
        case 'C':

            int board_version;

            if( _me630GetBoardVersion(iCurrentBoardNumber, &board_version) )
            {
                printf("Board Version is 0x%08X\n\n", board_version);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'd':
        case 'D':

			int int_number;
			
			while(TRUE)
            {
                printf("Interrupt 1/2 : ");

                gets( &buffer[0] );

                printf("\n\n");
                
                if(buffer[0] == '1')
                {
                    int_number = ME630_IRQ_1; 

                    break;
                }
                else if(buffer[0] == '2')
                {
                    int_number = ME630_IRQ_2; 

                    break;
                }
            }

            if( _me630EnableInt(iCurrentBoardNumber, int_number, Beep, int_number) )
            {
                printf("Board: %d Interrupt No.: %d  -  Interrupt Enabled\n\n", 
													iCurrentBoardNumber, int_number );
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'e':
        case 'E':

			while(TRUE)
            {
                printf("Interrupt 1/2 : ");

                gets( &buffer[0] );

                printf("\n\n");
                
                if(buffer[0] == '1')
                {
                    int_number = ME630_IRQ_1; 

                    break;
                }
                else if(buffer[0] == '2')
                {
                    int_number = ME630_IRQ_2; 

                    break;
                }
            }

            if( _me630DisableInt(iCurrentBoardNumber, int_number) )
            {
                printf("Board: %d Interrupt No.: %d  -  Interrupt Disabled\n\n", 
													iCurrentBoardNumber, int_number );
            }
            else
            {
                printf("ERROR!\n\n");
            }


            break;

        case 'f':
        case 'F':

            char error_message[256];
            int error_no;
            
            error_no = _me630GetDrvErrMess(&error_message[0], 256);
            
            printf("Error No.: 0x%08X\n", error_no);
            
            if(error_message[0] != 0)
            {
                printf( "Error message: %s\n", &error_message[0] );
            }

            printf("\n");

            break;

        case 'g':
        case 'G':

            if( _me630ResetRelays(iCurrentBoardNumber) )
            {
                printf("Board: %d - Relays reset\n\n", iCurrentBoardNumber);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'h':
        case 'H':

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
                        if( _me630DOSetRelayBit(iCurrentBoardNumber, i_bit_no, i_bit_value) )
                        {
                            printf("Board: %d -  Set Bit No.: %d to %d\n\n",
			                                        iCurrentBoardNumber, i_bit_no, i_bit_value);
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

        case 'i':
        case 'I':

            while(TRUE)
            {
                printf("Output Word (4 Digit Hex Integer) : ");

                gets( &buffer[0] );

                printf("\n\n");
                
                WORD w_word;
                
                if( sscanf(&buffer[0], "%x", &w_word) >= 1 )
                {
                    if( _me630DOSetRelayWord(iCurrentBoardNumber, w_word) )
                    {
                        printf("Board: %d -  Output Word: 0x%04X\n\n", iCurrentBoardNumber, w_word);
                    }
                    else
                    {
                        printf("ERROR!\n\n");
                    }

                    break;
                }
            }

            break;

        case 'j':
        case 'J':

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
                        
                        if( _me630DIGetRelayBit(iCurrentBoardNumber, i_bit_no, &i_bit_value) )
                        {
                            printf("Board: %d -  Bit No.: %d is %d\n\n",
		                                        iCurrentBoardNumber, i_bit_no, (i_bit_value == 0) ? 0 : 1);
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

        case 'k':
        case 'K':

            WORD w_value;
            
            if( _me630DIGetRelayWord(iCurrentBoardNumber, &w_value) )
            {
                printf("Board: %d Input Word: 0x%04X\n\n", iCurrentBoardNumber, w_value);
            }
            else
            {
                printf("ERROR!\n\n");
            }

			break;


        case 'l':
        case 'L':

            while(TRUE)
            {
                printf("Bit Number (0 - 7): ");

                gets( &buffer[0] );

                printf("\n\n");
                
                int i_bit_no;
            
                if( sscanf(&buffer[0], "%d", &i_bit_no) >= 1 )
                {
                    if( (0 <= i_bit_no)&&(i_bit_no <= 7) )
                    {
                        int i_bit_value;
                        
                        if( _me630DIGetTTLBit(iCurrentBoardNumber, i_bit_no, &i_bit_value) )
                        {
                            printf("Board: %d -  Bit No.: %d is %d\n\n",
		                                        iCurrentBoardNumber, i_bit_no, (i_bit_value == 0) ? 0 : 1);
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

        case 'm':
        case 'M':

            unsigned char uc_value;
            
            if( _me630DIGetTTLByte(iCurrentBoardNumber, &uc_value) )
            {
                printf("Board: %d Input Byte: 0x%02X\n\n", iCurrentBoardNumber, uc_value);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'n':
        case 'N':

            while(TRUE)
            {
                printf("Bit Number (0 - 7): ");

                gets( &buffer[0] );

                printf("\n\n");
                
                int i_bit_no;
            
                if( sscanf(&buffer[0], "%d", &i_bit_no) >= 1 )
                {
                    if( (0 <= i_bit_no)&&(i_bit_no <= 7) )
                    {
                        int i_bit_value;
                        
                        if( _me630DIGetOptoBit(iCurrentBoardNumber, i_bit_no, &i_bit_value) )
                        {
                            printf("Board: %d -  Bit No.: %d is %d\n\n",
		                                        iCurrentBoardNumber, i_bit_no, (i_bit_value == 0) ? 0 : 1);
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

        case 'o':
        case 'O':

            if( _me630DIGetOptoByte(iCurrentBoardNumber, &uc_value) )
            {
                printf("Board: %d Input Byte: 0x%02X\n\n", iCurrentBoardNumber, uc_value);
            }
            else
            {
                printf("ERROR!\n\n");
            }


            break;

        case 'p':
        case 'P':

			while(TRUE)
            {
                printf("Interrupt 1/2 : ");

                gets( &buffer[0] );

                printf("\n\n");
                
                if(buffer[0] == '1')
                {
                    int_number = ME630_IRQ_1; 

                    break;
                }
                else if(buffer[0] == '2')
                {
                    int_number = ME630_IRQ_2; 

                    break;
                }
            }

            int i_count;
            
            if( _me630GetIrqCnt(iCurrentBoardNumber, int_number, &i_count) )
            {
                printf("Board: %d Register set: %C  -  IRQ Count: %d\n\n",
                                iCurrentBoardNumber, (iCurrentRegisterSet == 0 ? 'A' : 'B'), i_count);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'q':
        case 'Q':

            DEVICEINFOSTRUCT dev_info;
            
            if( _me630GetDevInfo(iCurrentBoardNumber, &dev_info) )
            {
                printf("Board: %2d Device Info\n", iCurrentBoardNumber);
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

        case 'r':
        case 'R':

            printf("User String: ");

            gets( &buffer[0] );

            printf("\n\n");
                
            if( _me630WriteUserString(iCurrentBoardNumber, &buffer[0]) )
            {
                printf("Board: %d  -  Write User String: %s\n\n", iCurrentBoardNumber, &buffer[0]);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 's':
        case 'S':

            if( _me630ReadUserString(iCurrentBoardNumber, &buffer[0], 256) )
            {
                printf("Board: %d  -  Read User String: %s\n\n", iCurrentBoardNumber, &buffer[0]);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 't':
        case 'T':

            if( _me630DIOResetAll(iCurrentBoardNumber) )
            {
                printf("Board: %d  -  DIOResetAll called\n\n", iCurrentBoardNumber);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'u':
        case 'U':

			int i_port_number;
			
			while(TRUE)
            {
				printf("Choose a Port\n\n");

				printf("C) Port C \n");
				printf("D) Port D \n\n");
        
				printf("Port C/D : ");
        
				gets( &buffer[0] );

				printf("\n\n");
        
				if( (buffer[0] == 'c')||(buffer[0] == 'C') )
				{
					i_port_number = ME630_DIO_PORT_C;

					break;
				}
				else if( (buffer[0] == 'd')||(buffer[0] == 'D') )
				{
					i_port_number = ME630_DIO_PORT_D;

					break;
				}
			}

			int i_port_dir;
			
			while(TRUE)
            {
				printf("Choose a Port direction\n\n");

				printf("I) Input \n");
				printf("O) Output \n\n");
        
				printf("Dir I/O : ");
        
				gets( &buffer[0] );

				printf("\n\n");
        
				if( (buffer[0] == 'i')||(buffer[0] == 'I') )
				{
					i_port_dir = ME630_DIO_PORT_INPUT;

					break;
				}
				else if( (buffer[0] == 'o')||(buffer[0] == 'O') )
				{
					i_port_dir = ME630_DIO_PORT_OUTPUT;

					break;
				}
			}

            if( _me630DIOConfig(iCurrentBoardNumber, i_port_number, i_port_dir) )
            {
                printf("Board: %d Port %c  configured for %s\n\n",
						iCurrentBoardNumber,
						( (i_port_number == ME630_DIO_PORT_C) ? 'C' : 'D' ), 
						( (i_port_dir == ME630_DIO_PORT_INPUT) ? "Input" : "Output") );
            }
            else
            {
                printf("ERROR!\n\n");
            }


            break;

        case 'v':
        case 'V':

			while(TRUE)
            {
				printf("Choose a Port\n\n");

				printf("C) Port C \n");
				printf("D) Port D \n\n");
        
				printf("Port C/D : ");
        
				gets( &buffer[0] );

				printf("\n\n");
        
				if( (buffer[0] == 'c')||(buffer[0] == 'C') )
				{
					i_port_number = ME630_DIO_PORT_C;

					break;
				}
				else if( (buffer[0] == 'd')||(buffer[0] == 'D') )
				{
					i_port_number = ME630_DIO_PORT_D;

					break;
				}
			}

            if( _me630DIOGetByte(iCurrentBoardNumber, i_port_number, &uc_value) )
            {
                printf("Board: %d Port: %c - Input Byte: 0x%02X\n\n", 
							iCurrentBoardNumber, ( (i_port_number == ME630_DIO_PORT_C) ? 'C' : 'D' ), uc_value);
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

        case 'w':
        case 'W':

			while(TRUE)
            {
				printf("Choose a Port\n\n");

				printf("C) Port C \n");
				printf("D) Port D \n\n");
        
				printf("Port C/D : ");
        
				gets( &buffer[0] );

				printf("\n\n");
        
				if( (buffer[0] == 'c')||(buffer[0] == 'C') )
				{
					i_port_number = ME630_DIO_PORT_C;

					break;
				}
				else if( (buffer[0] == 'd')||(buffer[0] == 'D') )
				{
					i_port_number = ME630_DIO_PORT_D;

					break;
				}
			}

            while(TRUE)
            {
                printf("Output Byte (2 Digit Hex Integer) : ");

                gets( &buffer[0] );

                printf("\n\n");
                
                unsigned char uc_value;
                
                if( sscanf(&buffer[0], "%x", &uc_value) >= 1 )
                {
                    if( _me630DIOSetByte(iCurrentBoardNumber, i_port_number, uc_value) )
                    {
                        printf("Board: %d Port: %c - Output Byte: 0x%02X\n\n", 
									iCurrentBoardNumber, ( (i_port_number == ME630_DIO_PORT_C) ? 'C' : 'D' ), uc_value);
                    }
                    else
                    {
                        printf("ERROR!\n\n");
                    }

                    break;
                }
            }

            break;

		case 'x':
		case 'X':

			while(TRUE)
            {
				printf("Choose a Port\n\n");

				printf("C) Port C \n");
				printf("D) Port D \n\n");
        
				printf("Port C/D : ");
        
				gets( &buffer[0] );

				printf("\n\n");
        
				if( (buffer[0] == 'c')||(buffer[0] == 'C') )
				{
					i_port_number = ME630_DIO_PORT_C;

					break;
				}
				else if( (buffer[0] == 'd')||(buffer[0] == 'D') )
				{
					i_port_number = ME630_DIO_PORT_D;

					break;
				}
			}

            while(TRUE)
            {
                printf("Bit Number (0 - 7): ");

                gets( &buffer[0] );

                printf("\n\n");
                
                if( sscanf(&buffer[0], "%d", &i_bit_no) >= 1 )
                {
                    if( (0 <= i_bit_no)&&(i_bit_no <= 7) )
                    {

                        break;
                    }
                }
            }

            int i_bit_value;
            
            if( _me630DIOGetBit(iCurrentBoardNumber, i_port_number, i_bit_no, &i_bit_value) )
            {
                printf("Board: %d Port: %c -  Bit No.: %d is %d\n\n",
		                            iCurrentBoardNumber, ( (i_port_number == ME630_DIO_PORT_C) ? 'C' : 'D' ), 
																			i_bit_no, ( (i_bit_value == 0) ? 0 : 1) );
            }
            else
            {
                printf("ERROR!\n\n");
            }

            break;

		case 'y':
		case 'Y':

			while(TRUE)
            {
				printf("Choose a Port\n\n");

				printf("C) Port C \n");
				printf("D) Port D \n\n");
        
				printf("Port C/D : ");
        
				gets( &buffer[0] );

				printf("\n\n");
        
				if( (buffer[0] == 'c')||(buffer[0] == 'C') )
				{
					i_port_number = ME630_DIO_PORT_C;

					break;
				}
				else if( (buffer[0] == 'd')||(buffer[0] == 'D') )
				{
					i_port_number = ME630_DIO_PORT_D;

					break;
				}
			}

            while(TRUE)
            {
                printf("Bit Number (0 - 7): ");

                gets( &buffer[0] );

                printf("\n\n");
                
                if( sscanf(&buffer[0], "%d", &i_bit_no) >= 1 )
                {
                    if( (0 <= i_bit_no)&&(i_bit_no <= 7) )
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
                        break;
                    }
                }
            }

            if( _me630DIOSetBit(iCurrentBoardNumber, i_port_number, i_bit_no, i_bit_value) )
            {
                printf("Board: %d Port: %c - Set Bit No.: %d to %d\n\n",
			                            iCurrentBoardNumber, ( (i_port_number == ME630_DIO_PORT_C) ? 'C' : 'D' ), 
																								i_bit_no, i_bit_value);
            }
            else
            {
                printf("ERROR!\n\n");
            }

		case 'z':
		case 'Z':

            bEndProgram = TRUE;

            break;
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
    
    return(0);
}
