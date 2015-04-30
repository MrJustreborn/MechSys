/*      Sample.cpp : Text based (Console)           */
/*      program to test all the routines in the     */
/*      ME6x00 interface.                           */
/*                                                  */
/*      Program for use with Borland C++            */
/*      and Visual C++ programs                     */
/*                                                  */
/*      This Program uses dynamic function calls    */
/*      and Wrappers for all the ME6x00 functions   */

/*
dynamic vs. static binding of a DLL:
------------------------------------

static binding:
    - you have to include the me6x00.lib file
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
    - use the include file me6x00.h
    - use the compiler MS Visual C 6.00
If you would like to use dynamic binding:
      (All the following steps are done in
      this exsample:)
    - use the include file me6x00Init.h
    - use the function me6x00Open at the
      start of the program
    - use the function me6x00Close at the
      end of the program
    - include the source code file
      "DLLInit.cpp" in the project.  This
      file contains the "me6x00Open" and
      "me6x00Close" functions which must be
      called from the main program.  The
      "me6x00Open" function opens the library
      and gets the address of all the DLL
      functions.  The "me6x00Close" function
      simply closes the library at the end of
      the program.
    - The source code file "me6x00Init" also
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

/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

/*  These are the me6x00 header files    */
//#include ".\..\me6x00.h"
#include ".\..\me6x00init.h"
#include ".\..\DLLInit.h"

#define BUFFER_SIZE (32*1024)   // must be less or equal 64 K
#define VALUE_RANGE 65536

short pBuffer[4][BUFFER_SIZE];

//------ CB_Data ------
struct CB_Data
{
  int board;
  int channel;
  int size;
  short* pBuffer;
  int loops;
} cbData;

//------ callbackProc ------
void _cdecl callbackProc( void* pArgs )
{
  CB_Data* pData = (CB_Data*)pArgs;
  if( !me6x00AOContinuousEx(pData->board, pData->channel, pData->size,
                            pData->pBuffer, pData->loops, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}

//------ callback0 ------
void _cdecl callback0( void* pArgs )
{
  if( !me6x00AOContinuousEx(0, 0, BUFFER_SIZE, pBuffer[ 0 ], 0, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}

//------ callback1 ------
void _cdecl callback1( void* pArgs )
{
  if( !me6x00AOContinuousEx(0, 1, BUFFER_SIZE, pBuffer[ 1 ], 0, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}

//------ callback2 ------
void _cdecl callback2( void* pArgs )
{
  if( !me6x00AOContinuousEx(0, 2, BUFFER_SIZE, pBuffer[ 2 ], 0, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}

//------ callback3 ------
void _cdecl callback3( void* pArgs )
{
  if( !me6x00AOContinuousEx(0, 3, BUFFER_SIZE, pBuffer[ 3 ], 0, NULL, NULL ))
    printf("me6x00AOContinuousEx: ERROR!\n");
}



int main(void)
{
    BOOL bBoardPresent[ME_MAX_DEVICES];
    int iCurrentBoardNumber = -1;

//  SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
//  SetThreadPriority( GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);

    // calls the initialize function
    me6x00Open();

    for(int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
    {
        int iVersion;

        if( me6x00GetBoardVersion(index_board, &iVersion) )
        {
            bBoardPresent[index_board] = TRUE;

            if(iCurrentBoardNumber == -1)
            {
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
        printf("\n\nNo ME6x00 boards were found!\n\n");
        exit(-1);
    }

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

        printf("H) FrequencyToTimer\n\n");

        printf("Hardware functions:     \n");
        printf("I) AOReset               J) AOResetAll\n");
        printf("K) AOSingle              L) AOStart\n");
        printf("M) AOSetTimer            N) AOSetTrigger\n");
        printf("O) AOWaveGen             P) AOWrapAround\n");
        printf("Q) AOContinuous          R) AOStop\n");
        printf("S) AOContinuous (0..3)   T) AOReset (0..3)\n");
        printf("U) AOContinuousEx        V) AOStopEx\n");
        printf("1) AOContinuousEx (0..3) 2) AOStopEx (0..3)\n");

        printf("\nChoose a command: ");

        Sleep( 1 );
        gets( &buffer[0] );
        printf("\n");

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

        case 'B':   // int me6x00GetBoardVersion(int iBoardNumber, int *piVersion);
        {
            int iBoardVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetBoardVersion\n");

            if( me6x00GetBoardVersion(iCurrentBoardNumber, &iBoardVersion) )
                printf("board version is 0x%08X\n", iBoardVersion);
            else
                printf("me6x00GetBoardVersion: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'C':   // int me6x00GetDLLVersion();
        {
            int iDllVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetDllVersion\n");

            iDllVersion = me6x00GetDLLVersion();
            printf("dll version is 0x%08X\n", iDllVersion);

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'D':   // int me6x00GetDriverVersion(int *piDriverVersion);
        {
            int iDriverVersion;

            printf("-----------------------------------------------------------\n");
            printf("GetDriverVersion\n");

            if( me6x00GetDriverVersion(&iDriverVersion) )
                printf("driver version is 0x%08X\n", iDriverVersion);
            else
                printf("me6x00GetDriverVersion: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'E':   // int me6x00GetSerialNumber(int iBoardNumber, int *piSerialNumber);
        {
            int iSerialNumber;

            printf("-----------------------------------------------------------\n");
            printf("GetSerialNumber\n");

            if( me6x00GetSerialNumber(iCurrentBoardNumber, &iSerialNumber) )
                printf("serial number is 0x%08X\n", iSerialNumber);
            else
                printf("me6x00GetSerialNumber: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'F':   // int me6x00GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
        {
            DEVICEINFOSTRUCT dev_info;

            printf("-----------------------------------------------------------\n");
            printf("GetDevInfo\n");

            if(me6x00GetDevInfo(iCurrentBoardNumber, &dev_info))
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
                printf("me6x00GetDevInfo: ERROR!\n\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'G':   //int me6x00GetDrvErrMess(char *pcErrortext, int iBufferSize);
        {
            int iErrorNo;
            char pErrorMessage[256];

            printf("-----------------------------------------------------------\n");
            printf("GetDrvErrMess\n");

            pErrorMessage[0] = 0;
            iErrorNo = me6x00GetDrvErrMess(pErrorMessage, 256);
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



        case 'H':   // int me6x00FrequencyToTimer(double dFrequency);
        {   
            double dFrequency;
            int iTicks;
            
            printf("-----------------------------------------------------------\n");
            printf("FrequencyToTimer\n");
            
            printf("frequency [0.00769..500000 Hz]: ");
            gets(buffer);
            sscanf(buffer, "%lf", &dFrequency);
            iTicks = me6x00FrequencyToTimer(dFrequency);
            printf("ticks at frequency %f Hz: %u\n", dFrequency, iTicks);
 
            printf("-----------------------------------------------------------\n\n");
            break;
        }


        case 'I':   //int me6x00AOReset(int iBoardNumber, int iChannel);
        {
            int iChannel;
            
            printf("-----------------------------------------------------------\n");
            printf("AOReset\n");

            printf("channel (0..15): ");
            gets(buffer);
            sscanf(buffer, "%d", &iChannel);
            if( !me6x00AOReset(iCurrentBoardNumber, iChannel) )
                printf("me6x00AOReset: ERROR!\n");
            
            printf("-----------------------------------------------------------\n\n");
            break;
        }
        
        case 'J':   //int me6x00AOResetAll(int iBoardNumber);
        {
            printf("-----------------------------------------------------------\n");
            printf("AOResetAll\n");

            if( !me6x00AOResetAll(iCurrentBoardNumber) )
                printf("me6x00AOResetAll: ERROR!\n");
            
            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'K':   //int me6x00AOSingle( int iBoardNumber, int iChannel, int iValue);
        {  
            printf("-----------------------------------------------------------\n");
            printf("AOSingle\n");
            
            printf("channel (0..15)  : ");
            int iChannel;
            gets(buffer);
            sscanf(buffer, "%d", &iChannel);
            int iValue;
            printf("value (0..0xffff): ");
            gets(buffer);
            sscanf(buffer, "%x", &iValue);
            if( !me6x00AOSingle(iCurrentBoardNumber, iChannel, iValue) )
                printf("me6x00AOSingle: ERROR!\n");
                
            printf("-----------------------------------------------------------\n\n");
            break;
        }

        case 'L':   //int me6x00AOStart(int iBoardNumber, int iChannel);
        {  
            printf("-----------------------------------------------------------\n");
            printf("AOStart\n");

            int iChannel;
            printf("channel (0..3): ");
            gets(buffer);
            sscanf(buffer, "%d", &iChannel);
            if( !me6x00AOStart(iCurrentBoardNumber, iChannel) )
                printf("me6x00AOStart: ERROR!\n");

            printf("-----------------------------------------------------------\n\n");
            break;
        }

		case 'M':	//me6x00AOSetTimer(int iBoardNumber, int iChannel, int iTicks);
		{ 
			printf("-----------------------------------------------------------\n");
			printf("AOSetTimer\n");

			int iChannel;
			printf("channel (0..3)  : ");
			gets(buffer);
			sscanf(buffer, "%d", &iChannel);

			int iTicks;
			printf("ticks (66..2^32): ");
			gets(buffer);
			sscanf(buffer, "%d", &iTicks);

			if( !me6x00AOSetTimer(iCurrentBoardNumber, iChannel, iTicks) )
				printf("me6x00AOSetTimer: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case 'N':	//int me6x00AOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity);
		{ 
			printf("-----------------------------------------------------------\n");
			printf("AOSetTrigger\n");

			int iChannel;
			printf("channel (0..3)      : ");
			gets(buffer);
			sscanf(buffer, "%d", &iChannel);

			char c_mode;
			printf("trigger mode (S/H/L): ");
			gets(buffer);
			sscanf(buffer, "%c", &c_mode);

			int iMode;
			switch( c_mode )
			{ 
			case 's': iMode = AO6x00_TRIGGER_TIMER   ; break;
			case 'h': iMode = AO6x00_TRIGGER_EXT_HIGH; break;
			case 'l': iMode = AO6x00_TRIGGER_EXT_LOW;  break;
			};

			if( !me6x00AOSetTrigger(iCurrentBoardNumber, iChannel, iMode) )
				printf("me6x00AOSetTrigger: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case 'O':	//int me6x00AOWaveGen(int iBoardNumber, int iChannel, int iShape,
		{			//                    int iMin, int iMax, double iFreq);

			printf("-----------------------------------------------------------\n");
			printf("AOWaveGen\n");

			int iChannel;
			printf("channel (0..3) : ");
			gets(buffer);
			sscanf(buffer, "%d", &iChannel);

			int iShape;
			printf("shape (0..5)   : ");
			gets(buffer);
			sscanf(buffer, "%d", &iShape);

			double dAmplitude;
			printf("amplitude (0..10): ");
			gets(buffer);
			sscanf(buffer, "%lf", &dAmplitude);

			double dOffset;
			printf("offset (-10..10): ");
			gets(buffer);
			sscanf(buffer, "%lf", &dOffset);

			double dFrequency;
			printf("freq (..250000): ");
			gets(buffer);
			sscanf(buffer, "%lf", &dFrequency);

			if( !me6x00AOWaveGen(iCurrentBoardNumber, iChannel, iShape, dAmplitude, dOffset, dFrequency) )
				printf("me6x00AOWaveGen: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case 'P':	//int me6x00AOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer);
		{ 
			printf("-----------------------------------------------------------\n");
			printf("AOWrapAround\n");

			int iChannel;
			printf("channel (0..3): ");
			gets(buffer);
			sscanf(buffer, "%d", &iChannel);

			int iSize;
			printf("size (2..8192): ");
			gets(buffer);
			sscanf(buffer, "%d", &iSize);
			if( iSize > 8192 )
				iSize = 8192;

			short psBuffer[ 8192 ];
			short delta = 0xffff / (iSize-1);
			for( int i = 0; i < iSize; i++ )
			psBuffer[ i ] = i * delta;

			if( !me6x00AOWrapAround(iCurrentBoardNumber, iChannel, iSize, psBuffer) )
			printf("me6x00AOWrapAround: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case 'Q':	//int me6x00AOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer);
		{ 
			printf("-----------------------------------------------------------\n");
			printf("Continuous\n");

			int iChannel;
			printf("channel (0..3): ");
			gets(buffer);
			sscanf(buffer, "%d", &iChannel);

			int iSize;
			printf("size (..65536): ");
			gets(buffer);
			sscanf(buffer, "%d", &iSize);

			short psBuffer[ 0x10000 ];
			for( int i = 0; i < 0x10000; i++ )
				psBuffer[ i ] = i;

			if( !me6x00AOContinuous(iCurrentBoardNumber, iChannel, iSize, psBuffer) )
				printf("me6x00AOContinuous: ERROR!\n");

			printf("to start press a key!\n");
			getch();

			if( !me6x00AOStart(iCurrentBoardNumber, iChannel) )
				printf("me6x00AOContinuous: ERROR!\n");

			printf("to stop press a key!\n");

			while( !kbhit() )
			{
				if( !me6x00AOContinuous(iCurrentBoardNumber, iChannel, iSize, psBuffer) )
				printf("me6x00AOContinuous: ERROR!\n");
				Sleep( 10 );
			}
			getch();
			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case 'R':	//int me6x00AOStop(int iBoardNumber, int iChannel);
		{
			printf("-----------------------------------------------------------\n");
			printf("AOStop\n");

			int iChannel;
			printf("channel (0..3): ");
			gets(buffer);
			sscanf(buffer, "%d", &iChannel);

			if( !me6x00AOStop(iCurrentBoardNumber, iChannel) )
				printf("me6x00AOStop: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
			break;
		}




		case 'S':	//int me6x00AOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer);
		{
			printf("-----------------------------------------------------------\n");
			printf("Continuous at 4 channels\n");

			printf("frequency [..500000 Hz]: ");
			double dFrequency;
			gets(buffer);
			sscanf(buffer, "%lf", &dFrequency);
			int ticks = me6x00FrequencyToTimer(dFrequency);

			for( int ch = 0; ch < 4; ++ch )
			{ 
				if( !me6x00AOStop(iCurrentBoardNumber, ch) )
					printf("me6x00AOStop: ERROR!\n");
				if( !me6x00AOSetTimer(iCurrentBoardNumber, ch, ticks) )
				{ 
					printf("me6x00AOSetTimer: ERROR!\n");
					break;
				}
			}

			// rectangle
			short psBuffer00[ BUFFER_SIZE ];
			for( int i = 0; i < BUFFER_SIZE; i++ )
				psBuffer00[ i ] = (i < BUFFER_SIZE/2) ? VALUE_RANGE-1 : 0;

			// triangle
			short psBuffer01[ BUFFER_SIZE ];
			for( i = 0; i < BUFFER_SIZE; i++ )
			{
				if( i <= BUFFER_SIZE/2)
					psBuffer01[ i ] = (short)(0.5 + (double)i * 2.0 * (double)VALUE_RANGE / (double)BUFFER_SIZE);
				else
					psBuffer01[ i ] = VALUE_RANGE - (short)(0.5 + (double)(i - BUFFER_SIZE/2) * 2.0 * (double)VALUE_RANGE / (double)BUFFER_SIZE);
			}

			// sinus
			short psBuffer02[ BUFFER_SIZE ];
			for( i = 0; i < BUFFER_SIZE; i++ )
			{ 
				double val = (sin( (double)i / (double)BUFFER_SIZE * 2.0 * 3.14159 ) + 1.0) * (double)(VALUE_RANGE) / 2.0;
				psBuffer02[ i ] = (short)val;
			}

			// pos ramp
			short psBuffer03[ BUFFER_SIZE ];
			for( i = 0; i < BUFFER_SIZE; i++ )
				psBuffer03[ i ] = i * 4;

			if( !me6x00AOContinuous(iCurrentBoardNumber, 0, BUFFER_SIZE, psBuffer00) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOContinuous(iCurrentBoardNumber, 1, BUFFER_SIZE, psBuffer01) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOContinuous(iCurrentBoardNumber, 2, BUFFER_SIZE, psBuffer02) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOContinuous(iCurrentBoardNumber, 3, BUFFER_SIZE, psBuffer03) )
				printf("me6x00AOContinuous: ERROR!\n");
			printf("to start press a key!\n");
			getch();

			if( !me6x00AOStart(iCurrentBoardNumber, 0) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOStart(iCurrentBoardNumber, 1) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOStart(iCurrentBoardNumber, 2) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOStart(iCurrentBoardNumber, 3) )
				printf("me6x00AOContinuous: ERROR!\n");
			printf("to stop press a key!\n");

			while( !kbhit() )
			{
			if( !me6x00AOContinuous(iCurrentBoardNumber, 0, BUFFER_SIZE, psBuffer00) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOContinuous(iCurrentBoardNumber, 1, BUFFER_SIZE, psBuffer01) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOContinuous(iCurrentBoardNumber, 2, BUFFER_SIZE, psBuffer02) )
				printf("me6x00AOContinuous: ERROR!\n");
			if( !me6x00AOContinuous(iCurrentBoardNumber, 3, BUFFER_SIZE, psBuffer03) )
				printf("me6x00AOContinuous: ERROR!\n");
			//Sleep( 1 );
			}
			getch();
			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case 'T':	//int me6x00AOReset(int iBoardNumber, int iChannel);
		{  
			printf("-----------------------------------------------------------\n");
			printf("reset channels 0 .. 3\n");
			for( int ch = 0; ch < 4; ++ch )
			{ 
				if( !me6x00AOReset(iCurrentBoardNumber, ch) )
				printf("me6x00AOReset: ERROR!\n");
			}
			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case 'U':	//int me6x00AOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer,
					//                         int iLoops, PVOID_PROC pCallback, void* pArgs);
		{ 
			printf("ContinuousEx\n");

			int iChannel;
			printf("channel (0..3): ");
			gets(buffer);
			sscanf(buffer, "%d", &iChannel);

			int iSize;
			printf("size (..65536): ");
			gets(buffer);
			sscanf(buffer, "%d", &iSize);

			for( int i = 0; i < iSize; i++ )
			pBuffer[ iChannel ][ i ] = 0x10000-i;

			int iLoops;
			printf("loops (0..x): ");
			gets(buffer);
			sscanf(buffer, "%d", &iLoops);

			cbData.board   = iCurrentBoardNumber;
			cbData.size    = iSize;
			cbData.channel = iChannel;
			cbData.pBuffer = pBuffer[ iChannel ];
			cbData.loops   = iLoops;

			if( !me6x00AOContinuousEx(
				cbData.board, 
				cbData.channel, 
				cbData.size,
				cbData.pBuffer, 
				cbData.loops, 
				callbackProc,
				&cbData))
			{
				printf("me6x00AOContinuousEx: ERROR!\n");
			}

			printf("to start press a key!\n");
			getch();

			if( !me6x00AOStart(cbData.board, cbData.channel) )
				printf("me6x00AOStart: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case 'V':	//int me6x00AOStopEx(int iBoardNumber, int iChannel);
		{ 
			printf("-----------------------------------------------------------\n");
			printf("AOStopEx\n");

			int iChannel;
			printf("channel (0..3): ");
			gets(buffer);
			sscanf(buffer, "%d", &iChannel);

			if( !me6x00AOStopEx(iCurrentBoardNumber, iChannel) )
				printf("me6x00AOStopEx: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case '1':	//int me6x00AOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer,
					//                         int iLoops, PVOID_PROC pCallback, void* pArgs);
		{ 
			printf("ContinuousEx at 4 channels\n");

			printf("frequency [..500000 Hz]: ");
			double dFrequency;
			gets(buffer);
			sscanf(buffer, "%lf", &dFrequency);
			int ticks = me6x00FrequencyToTimer(dFrequency);

			for( int ch = 0; ch < 4; ++ch )
			{ 
				if( !me6x00AOReset(iCurrentBoardNumber, ch) )
					printf("me6x00AOReset: ERROR!\n");
				Sleep( 10 );
				if( !me6x00AOSetTimer(iCurrentBoardNumber, ch, ticks) )
					printf("me6x00AOSetTimer: ERROR!\n");
			}

			// rectangle
			for( int i = 0; i < BUFFER_SIZE; i++ )
				pBuffer[ 0 ][ i ] = (i < BUFFER_SIZE/2) ? VALUE_RANGE-1 : 0;

			// triangle
			for( i = 0; i < BUFFER_SIZE; i++ )
			{
				if( i <= BUFFER_SIZE/2)
					pBuffer[ 1 ][ i ] = (short)(0.5 + (double)i * 2.0 * (double)VALUE_RANGE / (double)BUFFER_SIZE);
				else
					pBuffer[ 1 ][ i ] = VALUE_RANGE - (short)(0.5 + (double)(i - BUFFER_SIZE/2) * 2.0 * (double)VALUE_RANGE / (double)BUFFER_SIZE);
			}

			// sinus
			for( i = 0; i < BUFFER_SIZE; i++ )
			{ 
				double val = (sin( (double)i / (double)BUFFER_SIZE * 2.0 * 3.14159 ) + 1.0) * (double)(VALUE_RANGE) / 2.0;
				pBuffer[ 2 ][ i ] = (short)val;
			}

			// pos ramp
			for( i = 0; i < BUFFER_SIZE; i++ )
				pBuffer[ 3 ][ i ] = i * VALUE_RANGE / BUFFER_SIZE;

			if( !me6x00AOContinuousEx(
				iCurrentBoardNumber, 
				0, 
				BUFFER_SIZE,
				pBuffer[ 0 ], 
				0, 
				callback0, 
				NULL) )
			{
				printf("me6x00AOContinuousEx: ERROR!\n");
			}

			Sleep( 1 );

			if( !me6x00AOContinuousEx(
				iCurrentBoardNumber, 
				1, 
				BUFFER_SIZE,
				pBuffer[ 1 ], 
				0, 
				callback1, 
				NULL) )
			{
				printf("me6x00AOContinuousEx: ERROR!\n");
			}

			Sleep( 1 );

			if( !me6x00AOContinuousEx(
				iCurrentBoardNumber, 
				2, 
				BUFFER_SIZE,
				pBuffer[ 2 ], 
				0, 
				callback2, 
				NULL) )
			{
				printf("me6x00AOContinuousEx: ERROR!\n");
			}

			Sleep( 1 );

			if( !me6x00AOContinuousEx(
				iCurrentBoardNumber, 
				3, 
				BUFFER_SIZE,
				pBuffer[ 3 ], 
				0, 
				callback3, 
				NULL) )
			{
				printf("me6x00AOContinuousEx: ERROR!\n");
			}

			printf("to start press a key!\n");
			getch();
			if( !me6x00AOStart(iCurrentBoardNumber, 0) )
				printf("me6x00AOStart: ERROR!\n");
			if( !me6x00AOStart(iCurrentBoardNumber, 1) )
				printf("me6x00AOStart: ERROR!\n");
			if( !me6x00AOStart(iCurrentBoardNumber, 2) )
				printf("me6x00AOStart: ERROR!\n");
			if( !me6x00AOStart(iCurrentBoardNumber, 3) )
				printf("me6x00AOStart: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
			break;
		}

		case '2':
		{ //int me6x00AOStopEx(int iBoardNumber, int iChannel);
			printf("-----------------------------------------------------------\n");
			printf("stopEx channels 0 .. 3\n");

			if( !me6x00AOStopEx(iCurrentBoardNumber, 0) )
				printf("me6x00AOStopEx: ERROR!\n");
			if( !me6x00AOStopEx(iCurrentBoardNumber, 1) )
				printf("me6x00AOStopEx: ERROR!\n");
			if( !me6x00AOStopEx(iCurrentBoardNumber, 2) )
				printf("me6x00AOStopEx: ERROR!\n");
			if( !me6x00AOStopEx(iCurrentBoardNumber, 3) )
				printf("me6x00AOStopEx: ERROR!\n");

			printf("-----------------------------------------------------------\n\n");
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

    me6x00Close();

    return(0);
}
