/*      Sample.cpp : Text based (Console)           */
/*      program to test all the routines in the     */
/*      ME9000mio interface.                        */
/*                                                  */
/*      Program for use with Borland C++            */
/*      and Visual C++ programs                     */
/*                                                  */
/*      This Program uses dynamic function calls    */
/*      and Wrappers for all functions              */


#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include ".\..\me9000miodll.h"

void _stdcall DIO_IRQ_Proc(void* pContext)
{
    printf("\n\n*** DIOIrqProc ***\n\n");
}

void _stdcall CNT_IRQ_Proc(void* pContext)
{
    printf("\n\n*** CntIrqProc ***\n\n");
}

int main(void)
{
	printf(	"This program presents you with a menu enabling you to\n"
			"call any of the me9x00mio functions\n\n"
			"Having chosen a particular function you will be required\n"
			"to enter appropriate values for each of its parameters\n\n"
			"Once the desired function has been executed you will be\n"
			"presented with the main menu once again\n\n"
			"This will continue until you press 'z' to exit the program\n\n"
			"All functions operate on the FIRST ME9000 board found on the\n"
			"system. For this reason the first parameter to many functions,\n"
			"the board number, is missing here.\n\n");

	printf("Press any key to continue...");

	getch();

	printf("\n\n");
	
	BOOL b_end_program = FALSE;

	// Enable default error routine (Window with error message)
	me9000mioErrorSetDefaultProc(ME9000MIO_ERROR_DEFAULT_PROC_ENABLE);

	char buffer[128];
    
	while(!b_end_program)
    {
        printf("A) GetDLLVersion        B) GetDriverVersion \n");
        printf("C) GetBoardCount                            \n\n");
        
        printf("D) GetBoardVersion      E) GetSerialNumber  \n\n");

        printf("F) DIOOpen                                  \n");
        printf("G) DIOReset             H) DIOConfig        \n");
        printf("I) DIOGetBit            J) DIOSetBit        \n");
        printf("K) DIOGetByte           L) DIOSetByte       \n");
        printf("M) DIOOutput                                \n");
		printf("N) DIOSetCallback       O) DIOGetIrqCount   \n");
		printf("P) DIOClose                                 \n\n");

        printf("Q) CntOpen                                  \n");
        printf("R) CntReset             S) CntConfig        \n");
        printf("T) CntWrite             U) CntStart         \n");
        printf("V) CntRead              W) CntStop          \n");
        printf("X) CntGetIrqCount                           \n");
        printf("Y) CntClose                                 \n\n");

        printf("Z) End Program	                            \n\n");
        
        printf("Choose a command: ");

        gets( &buffer[0] );

        buffer[0] = toupper(buffer[0]);

        printf("\n\n");

		int i_error;

        switch(buffer[0])
        {
        case 'A':   // int me9000mioGetDLLVersion(unsigned long *plVersion);
        {
            printf("-----------------------------------------------------------\n");
            printf("GetDllVersion\n");

			unsigned long ul_dll_version;	
            
			i_error = me9000mioGetDLLVersion(&ul_dll_version);
            printf("dll version is 0x%08X\n", ul_dll_version);

            printf("-----------------------------------------------------------\n\n");
            
			break;
        }


        case 'B':   // int me9000mioGetDriverVersion(unsigned long *plVersion);
        {
            printf("-----------------------------------------------------------\n");
            printf("GetDriverVersion\n");

			unsigned long ul_drv_version;	
            
            i_error = me9000mioGetDriverVersion(&ul_drv_version);
            printf("Driver version is 0x%08X\n", ul_drv_version);

            printf("-----------------------------------------------------------\n\n");

            break;
        }


        case 'C':   // int me9000mioGetBoardCount(unsigned int* puiCount);
        {
            printf("-----------------------------------------------------------\n");
            printf("GetBoardCount\n");

            unsigned int ui_board_count;

            i_error = me9000mioGetBoardCount(&ui_board_count);
            printf("Board count is %u\n", ui_board_count);

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'D':   // int me9000mioGetBoardVersion(unsigned int uiBoardNumber, unsigned short* pusVersion)
        {
            printf("-----------------------------------------------------------\n");
            printf("GetBoardVersion\n");

			unsigned short us_version;	
			
			i_error =  me9000mioGetBoardVersion(0, &us_version);
            printf("Board version is 0x%04X\n", us_version);

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'E':   // int me9000mioGetSerialNumber(unsigned int uiBoardNumber, unsigned long* pulSerialNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("GetBoardSerialNumber\n");

			unsigned long ul_serial_number;	
			
			i_error =  me9000mioGetSerialNumber(0, &ul_serial_number);
            printf("Board serial number is 0x%08X\n", ul_serial_number);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'F':   // int me9000mioDIOOpen(unsigned int uiBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("DIOOpen\n");

			int i_error = me9000mioDIOOpen(0);

			printf("DIO is opened\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'G':   // me9000mioDIOReset(unsigned int uiBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("DIOReset\n");

			int i_error = me9000mioDIOReset(0);

			printf("DIO is reset\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'H':   // int me9000mioDIOConfig(unsigned int uiBoardNumber, unsigned int uiBitNumber,
					//										int iDirection, int iInvert, int iInterrupt);
        {
			unsigned int ui_bit_number;
            int i_direction;
            int i_invert;
            int i_interrupt;

            printf("-----------------------------------------------------------\n");
            printf("DIOConfig\n");

            while(TRUE)
            {
                printf("Bit Number (0..7): ");
                gets( &buffer[0] );
                printf("\n");
                if( sscanf(&buffer[0], "%u", &ui_bit_number) >= 1 )
                {
                    if((ui_bit_number>=0) && (ui_bit_number<=7))
                    {
                        break;
                    }
                }
            }

            while(TRUE)
            {
                printf("Direction\n\n");

				printf(	"O) ME9000MIO_DIO_OUTPUT\n"
						"I) ME9000MIO_DIO_OUTPUT\n"
						"Your choice: "				);

                gets( &buffer[0] );
                printf("\n");

                if( (buffer[0] == 'o')||(buffer[0] == 'O') ) 
                {
					i_direction = ME9000MIO_DIO_OUTPUT;
					
					break;
                }
                else if( (buffer[0] == 'i')||(buffer[0] == 'I') ) 
                {
					i_direction = ME9000MIO_DIO_INPUT;
					
					break;
                }
			}

            while(TRUE)
            {
                printf("Invert\n\n");

				printf(	"D) ME9000MIO_DIO_INV_DISABLE\n"
						"E) ME9000MIO_DIO_INV_ENABLE\n"
						"Your choice: "						);

                gets( &buffer[0] );
                printf("\n");

                if( (buffer[0] == 'd')||(buffer[0] == 'D') ) 
                {
					i_invert = ME9000MIO_DIO_INV_DISABLE;
					
					break;
                }
                else if( (buffer[0] == 'e')||(buffer[0] == 'E') ) 
                {
					i_invert = ME9000MIO_DIO_INV_ENABLE;
					
					break;
                }
			}

            while(TRUE)
            {
                printf("Interrupt\n\n");

				printf(	"D) ME9000MIO_DIO_INT_DISABLE\n"
						"E) ME9000MIO_DIO_INT_ENABLE\n"
						"Your choice: "						);

                gets( &buffer[0] );
                printf("\n");

                if( (buffer[0] == 'd')||(buffer[0] == 'D') ) 
                {
					i_interrupt = ME9000MIO_DIO_INT_DISABLE;
					
					break;
                }
                else if( (buffer[0] == 'e')||(buffer[0] == 'E') ) 
                {
					i_interrupt = ME9000MIO_DIO_INT_ENABLE;
					
					break;
                }
			}

			int i_error = me9000mioDIOConfig(0, ui_bit_number, i_direction, i_invert, i_interrupt);

			printf("DIOConfig called\n");

            printf("-----------------------------------------------------------\n\n");
            
			break;
        }

        case 'I':   // int me9000mioDIOGetBit(unsigned int uiBoardNumber, unsigned int uiBitNumber, int *piBitValue)
        {
			unsigned int ui_bit_number;

            printf("-----------------------------------------------------------\n");
            printf("DIOGetBit\n");

            while(TRUE)
            {
                printf("Bit Number (0..7): ");
                gets( &buffer[0] );
                printf("\n");
                if( sscanf(&buffer[0], "%u", &ui_bit_number) >= 1 )
                {
                    if((ui_bit_number>=0) && (ui_bit_number<=7))
                    {
                        break;
                    }
                }
            }

			int i_bit_value;
			
			int i_error = me9000mioDIOGetBit(0, ui_bit_number, &i_bit_value);

			printf("Bit %u is %d\n", ui_bit_number, i_bit_value);

            printf("-----------------------------------------------------------\n\n");

			break;
        }

        case 'J':   // int me9000mioSetBit(unsigned int uiBoardNumber, unsigned int uiBitNumber, int iBitValue)
        {
			unsigned int ui_bit_number;
			int i_bit_value;

            printf("-----------------------------------------------------------\n");
            printf("DIOSetBit\n");

            while(TRUE)
            {
                printf("Bit Number (0..7): ");
                gets( &buffer[0] );
                printf("\n");
                if( sscanf(&buffer[0], "%u", &ui_bit_number) >= 1 )
                {
                    if((ui_bit_number>=0) && (ui_bit_number<=7))
                    {
                        break;
                    }
                }
            }

            while(TRUE)
            {
                printf("Bit Value (0 or 1): ");
                gets( &buffer[0] );
                printf("\n");
                if( sscanf(&buffer[0], "%u", &i_bit_value) >= 1 )
                {
                    if((i_bit_value>=0) && (i_bit_value<=1))
                    {
                        break;
                    }
                }
            }

			int i_error = me9000mioDIOSetBit(0, ui_bit_number, i_bit_value);

			printf("DIOSetBit called\n");

            printf("-----------------------------------------------------------\n\n");

			break;
        }

        case 'K':   // int me9000mioDIOGetByte(unsigned int uiBoardNumber,  unsigned char *pucByteValue);
        {
            unsigned char uc_byte;

            printf("-----------------------------------------------------------\n");
            printf("DIOGetByte\n");

            i_error = me9000mioDIOGetByte(0, &uc_byte);
            printf("Byte is 0x%02X\n", uc_byte);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'L':   // int me9000mioDIOSetByte(unsigned int uiBoardNumber,  unsigned char ucByteValue);
        {
            unsigned char uc_byte;

            printf("-----------------------------------------------------------\n");
            printf("DIOSetByte\n");

            while(TRUE)
            {
                printf("Byte Value (2 Digit Hex Integer) : ");
                gets( &buffer[0] );
                printf("\n");
                if( sscanf(&buffer[0], "%x", &uc_byte) >= 1 )
                {
                    if ((uc_byte >= 0) && (uc_byte <= 0xFF))
					{
                        break;
					}
                }
            }

            i_error = me9000mioDIOSetByte(0, uc_byte);
            printf("Byte set to 0x%04X\n", uc_byte);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'M':   // int me9000mioDIOOutput(unsigned int uiBoardNumber, unsigned int uiBitNumber, int iOutputMode)
        {
			unsigned int ui_bit_number;
            int i_output;

            printf("-----------------------------------------------------------\n");
            printf("DIOOutput\n");

            while(TRUE)
            {
                printf("Bit Number (0..7): ");
                gets( &buffer[0] );
                printf("\n");
                if( sscanf(&buffer[0], "%u", &ui_bit_number) >= 1 )
                {
                    if((ui_bit_number>=0) && (ui_bit_number<=7))
                    {
                        break;
                    }
                }
            }

            while(TRUE)
            {
                printf("Output\n\n");

				printf(	"D) ME9000MIO_DIO_OUTPUT_DISABLE\n"
						"E) ME9000MIO_DIO_OUTPUT_ENABLE\n"
						"Your choice: "						);

                gets( &buffer[0] );
                printf("\n");

                if( (buffer[0] == 'd')||(buffer[0] == 'D') ) 
                {
					i_output = ME9000MIO_DIO_OUTPUT_DISABLE;
					
					break;
                }
                else if( (buffer[0] == 'e')||(buffer[0] == 'E') ) 
                {
					i_output = ME9000MIO_DIO_OUTPUT_ENABLE;
					
					break;
                }
			}

			int i_error = me9000mioDIOOutput(0, ui_bit_number, i_output);

			printf("DIOOutput called\n");

            printf("-----------------------------------------------------------\n\n");
            
			break;
        }

        case 'N':   // int me9000mioDIOSetCallback(unsigned int uiBoardNumber, ME9000MIO_P_DIO_PROC pDIOIrqProc, void *pDIOIrqContext);
        {
            printf("-----------------------------------------------------------\n");
            printf("DIOSetCallback\n\n");

			printf( "The arguments for this function will be supplied:\n\n"
					"pDIOIrqProc - Prints '*** DIOIrqProc ***' on the screen\n"
					"pDIOIrqContext - is null\n\n"
					"Press any key to call DIOSetCallback..."					);

			getch();

			printf("\n\n");

			int i_error = me9000mioDIOSetCallback(0, DIO_IRQ_Proc, NULL);

			printf("DIOSetCallback called\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'O':   // int me9000mioDIOGetIrqCount(unsigned int uiBoardNumber, unsigned long *pulCount);
        {
			unsigned long ul_count;
			
            printf("-----------------------------------------------------------\n");
            printf("DIOGetIrqCount\n");

			i_error =  me9000mioDIOGetIrqCount(0, &ul_count);
            printf("DIO IRQ Count is %lu\n", ul_count);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'P':   // int me9000mioDIOClose(unsigned int uiBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("DIOClose\n");

			int i_error = me9000mioDIOClose(0);

			printf("DIO is closed\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'Q':   // int me9000mioCntOpen(unsigned int uiBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("CntOpen\n");

			int i_error = me9000mioCntOpen(0);

			printf("Cnt is opened\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'R':   // me9000mioCntReset(unsigned int uiBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("CntReset\n");

			int i_error = me9000mioCntReset(0);

			printf("Cnt is reset\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'S':   // int me9000mioCntConfig(unsigned int uiBoardNumber, int iRetrigger, int iCntEvent,
					//														int iClockSource, int iInterrupt, 
					//									ME9000MIO_P_CNT_PROC pCntIrqProc, void *pCntIrqContext);
        {
			int i_retrigger;
            int i_cnt_event;
            int i_clock_source;
            int i_interrupt;

            printf("-----------------------------------------------------------\n");
            printf("CntConfig\n");

            while(TRUE)
            {
                printf("Retrigger\n\n");

				printf(	"D) ME9000MIO_CNT_RETRIGGER_DISABLE\n"
						"E) ME9000MIO_CNT_RETRIGGER_ENABLE\n"
						"Your choice: "							);

                gets( &buffer[0] );
                printf("\n");

                if( (buffer[0] == 'd')||(buffer[0] == 'D') ) 
                {
					i_retrigger = ME9000MIO_CNT_RETRIGGER_DISABLE;
					
					break;
                }
                else if( (buffer[0] == 'e')||(buffer[0] == 'E') ) 
                {
					i_retrigger = ME9000MIO_CNT_RETRIGGER_ENABLE;
					
					break;
                }
			}

            while(TRUE)
            {
                printf("Count event\n\n");

				printf(	"D) ME9000MIO_CNT_EVENT_DISABLE\n"
						"E) ME9000MIO_CNT_EVENT_ENABLE\n"
						"Your choice: "						);

                gets( &buffer[0] );
                printf("\n");

                if( (buffer[0] == 'd')||(buffer[0] == 'D') ) 
                {
					i_cnt_event = ME9000MIO_CNT_EVENT_DISABLE;
					
					break;
                }
                else if( (buffer[0] == 'e')||(buffer[0] == 'E') ) 
                {
					i_cnt_event = ME9000MIO_CNT_EVENT_ENABLE;
					
					break;
                }
			}

            while(TRUE)
            {
                printf("Clock source\n\n");

				printf(	"I) ME9000MIO_CNT_CLOCK_INTERNAL\n"
						"E) ME9000MIO_CNT_CLOCK_EXTERNAL\n"
						"Your choice: "						);

                gets( &buffer[0] );
                printf("\n");

                if( (buffer[0] == 'i')||(buffer[0] == 'I') ) 
                {
					i_clock_source = ME9000MIO_CNT_CLOCK_INTERNAL;
					
					break;
                }
                else if( (buffer[0] == 'e')||(buffer[0] == 'E') ) 
                {
					i_clock_source = ME9000MIO_CNT_CLOCK_EXTERNAL;
					
					break;
                }
			}


            while(TRUE)
            {
                printf("Interrupt\n\n");

				printf(	"D) ME9000MIO_CNT_INT_DISABLE\n"
						"E) ME9000MIO_CNT_INT_ENABLE\n"
						"Your choice: "						);

                gets( &buffer[0] );
                printf("\n\n");

                if( (buffer[0] == 'd')||(buffer[0] == 'D') ) 
                {
					i_interrupt = ME9000MIO_CNT_INT_DISABLE;
					
					break;
                }
                else if( (buffer[0] == 'e')||(buffer[0] == 'E') ) 
                {
					i_interrupt = ME9000MIO_CNT_INT_ENABLE;
					
					break;
                }
			}

			printf( "The remaining arguments for this function will be supplied:\n\n"
					"pCntIrqProc - Prints '*** CntIrqProc ***' on the screen\n"
					"pCntIrqContext - is null\n\n"
					"Press any key to call DIOSetCallback..."					);

			getch();

			printf("\n\n");

			int i_error = me9000mioCntConfig(0, i_retrigger, i_cnt_event, i_clock_source, i_interrupt, CNT_IRQ_Proc, NULL);

			printf("CntConfig called\n");

            printf("-----------------------------------------------------------\n\n");
            
			break;
        }

        case 'T':   // int me9000mioCntWrite(unsigned int uiBoardNumber, unsigned short usValue);
        {
            unsigned short us_value;

            printf("-----------------------------------------------------------\n");
            printf("CntWrite\n");

            while(TRUE)
            {
                printf("Write Value (4 Digit Hex Integer) : ");
                gets( &buffer[0] );
                printf("\n");
                if( sscanf(&buffer[0], "%x", &us_value) >= 1 )
                {
                    if ((us_value >= 0) && (us_value <= 0xFFFF))
					{
                        break;
					}
                }
            }

            i_error = me9000mioCntWrite(0, us_value);
            printf("0x%04X written\n", us_value);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'U':   // int me9000mioCntStart(unsigned int uiBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("CntStart\n");

			int i_error = me9000mioCntStart(0);

			printf("CntStart called\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'V':   // int me9000mioCntRead(unsigned int uiBoardNumber, unsigned short *pusValue);
        {
            unsigned short us_value;

            printf("-----------------------------------------------------------\n");
            printf("CntRead\n");

            i_error = me9000mioCntRead(0, &us_value);
            printf("Read 0x%04X\n", us_value);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'W':   // int me9000mioCntStop(unsigned int uiBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("CntStop\n");

			int i_error = me9000mioCntStop(0);

			printf("CntStop called\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'X':   // int me9000mioCntGetIrqCount(unsigned int uiBoardNumber, unsigned long *pulCount);
        {
			unsigned long ul_count;
			
            printf("-----------------------------------------------------------\n");
            printf("CntGetIrqCount\n");

			i_error =  me9000mioCntGetIrqCount(0, &ul_count);
            printf("Cnt IRQ Count is %lu\n", ul_count);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'Y':   // int me9000mioCntClose(unsigned int uiBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("CntClose\n");

			int i_error = me9000mioCntClose(0);

			printf("Cnt is closed\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

		case 'Z':

			b_end_program = TRUE;

			break;

		}

		if(b_end_program)
		{
			break;
		}

		printf("\n\nPress any key to continue\n\n");

		getch();
	}

    return 0;
}
