/*      ME 1000 Digital Input/Output demo           */
/*                                                  */
/*      Program for use with Borland C++            */
/*      and Visual C++ programs                     */
/*                                                  */
/*      This Program uses dynamic function calls    */
/*      and Wrappers for all the ME1000 functions   */


/*
dynamic vs. static binding of a DLL:
------------------------------------

static binding:
    - you have to include the me1000.lib file
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
    - use the include file me1000.h
    - use the compiler MS Visual C 6.00
If you would like to use dynamic binding:
      (All the following steps are done in 
      this example:)
    - use the include file me1000Init.h
    - use the function me1000Open at the
      start of the program
    - use the function me1000Close at the
      end of the program
    - include the source code file 
      "me1000Init.cpp" in the project.  This 
      file contains the "me1000Open" and 
      "me1000Close" functions which must be 
      called from the main program.  The 
      "me1000Open" function opens the library 
      and gets the address of all the DLL 
      functions.  The "me1000Close" function 
      simply closes the library at the end of
      the program.
    - The source code file "me1000Init" also 
      has all of the "Wrapper" functions.  This 
      allows the user to use the full and proper
      function names when calling them from the 
      main program.
*/


/* Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEUNIT("..\me1000Init.cpp");
#endif

/* These are system header files  */
#include <stdio.h>
#include <windows.h>
#include <conio.h>

/* These are the me1000 header files    */
//#include ".\..\me1000.h"
#include "..\DLLInit.h"


/* Prototypes   */
void Call_me1000GetDLLVersion(void);
void Call_me1000GetBoardVersion(int iBoardNumber);
void Call_me1000GetDevInfo(int iBoardNumber);
void Call_me1000DIOReset(int iBoardNumber);

void Call_me1000GetDriverVersion(void);
void Call_me1000GetSerialNumber(int iBoardNumber);
void Call_me1000ReadUserString(int iBoardNumber);
void Call_me1000WriteUserString(int iBoardNumber);

void Call_me1000DIOSetPortDirection(int iBoardNumber, int iDirection);
void Call_me1000DOSetBit(int iBoardNumber, int iValue);
void Call_me1000DOSetByte(int iBoardNumber, int iValue);
void Call_me1000DOSetWord(int iBoardNumber, int iValue);
void Call_me1000DOSetLong(int iBoardNumber, int iValue);

void Call_me1000DIGetLong(int iBoardNumber);
void Call_me1000DIGetWord(int iBoardNumber);
void Call_me1000DIGetByte(int iBoardNumber);
void Call_me1000DIGetBit(int iBoardNumber);


/* ------------------------  Main Program ------------------------------- */
void main(void)
{
    int iBoardNumber = 0;           // declare the BoardNumber variable

    meOpen ();  // calls the initialize function

    Call_me1000GetDLLVersion();

    Call_me1000GetBoardVersion(iBoardNumber);
    Call_me1000GetDevInfo(iBoardNumber);
	printf("Press any key to continue\n");
	getch();

	Call_me1000GetDriverVersion();
	Call_me1000GetSerialNumber(iBoardNumber);
	Call_me1000WriteUserString(iBoardNumber);
	Call_me1000ReadUserString(iBoardNumber);
	printf("Press any key to continue\n");
	getch();

	Call_me1000DIOReset(iBoardNumber);

	printf("Be careful not to cause a short circuit!\n");
	printf("Do not connect a output with a output!\n");
    printf("Press any key to continue\n");
    getch();

	Call_me1000DIOSetPortDirection(iBoardNumber, MEOUTPUT);
	Call_me1000DOSetBit (iBoardNumber,0x01);
	Call_me1000DOSetByte(iBoardNumber,0xFF);
	Call_me1000DOSetWord(iBoardNumber,0xFFFF);
	Call_me1000DOSetLong(iBoardNumber,0xFFFFFFFF);

	Call_me1000DIOSetPortDirection(iBoardNumber, MEINPUT);	
	Call_me1000DIGetLong(iBoardNumber);
	Call_me1000DIGetWord(iBoardNumber);
	Call_me1000DIGetByte(iBoardNumber);
	Call_me1000DIGetBit (iBoardNumber);

    meClose();

    printf("Press any key to continue\n");
    getch();
}

/*  ------------------------------------------------------------ */

void Call_me1000GetDLLVersion(void)
{
    int iDLLVersion;

    iDLLVersion = me1000GetDLLVersion();

    printf(
        "Version of DLL is %04x.%04x\n",
        (iDLLVersion>>16)& 0xFFFF,
        (iDLLVersion)    & 0xFFFF);
}


void Call_me1000GetBoardVersion(int iBoardNumber)
{
    int iBoardVersion;
    int iErrorCode;

    iErrorCode = me1000GetBoardVersion (iBoardNumber, &iBoardVersion);

    if(iErrorCode)
    {
        printf(
            "Board %d has a Board version of 0x%04X:\n",
            iBoardNumber,
            iBoardVersion);

        switch (iBoardVersion)
        {
            case 0x100a:
                printf("\tIt is a ME-1000 A with 64 lines\n");
                break;

            case 0x100b:
                printf("\tIt is a ME-1000 B with 128 lines\n");
                break;

            default:
                printf("\tIt is a unknown typ of ME-1000 \n");
        }
    }
    else
    {
        printf(
            "Error in Function Call_me1000GetBoardVersion\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}


void Call_me1000GetDevInfo(int iBoardNumber)
{
    int iErrorCode;
    DEVICEINFOSTRUCT DevInfo;

    iErrorCode = me1000GetDevInfo(iBoardNumber, &DevInfo);

    if(iErrorCode)
    {
        printf("\n");
        printf("Board: %2d Device Info\n", iBoardNumber);
        printf("----------------------\n");

        printf("\tVendor ID:          0x%04X\n",  DevInfo.dwVendorID);
        printf("\tDevice ID:          0x%04X\n",  DevInfo.dwDeviceID);
        printf("\tBus Number:         %u\n",      DevInfo.dwBusNumber);
        printf("\tSystem Slot Number: %u\n",      DevInfo.dwSystemSlotNumber);
        printf("\tPort Base:          0x%04X\n",  DevInfo.dwPortBase);
        printf("\tPort Count:         %u\n",      DevInfo.dwPortCount);
        printf("\tPLX Port Base:      0x%04X\n",  DevInfo.dwPortBasePLX);
        printf("\tPLX Port Count:     %u\n",      DevInfo.dwPortCountPLX);
        printf("\tSerial Number:      0x%08X\n",  DevInfo.dwSerialNumber);
        printf("\tHardware Revision:  0x%04X\n",  DevInfo.dwHWRevision);
        printf("\tVersion:            0x%04X\n",  DevInfo.dwVersion);
    }
    else
    {
        printf("ERROR!\n\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}


void Call_me1000DIOReset(int iBoardNumber)
{
    int iErrorCode;

    iErrorCode = me1000DIOReset(iBoardNumber);

    if(iErrorCode)
    {
        printf(
            "Board %d successfully reseted\n",
            iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DIOReset\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}

void Call_me1000DIOSetPortDirection(int iBoardNumber, int iDirection)
{
    int iErrorCode;

    iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTA, iDirection);

    if(iErrorCode)
    {
		iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTB, iDirection);
		if(iErrorCode)
		{
			iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTC, iDirection);
			if(iErrorCode)
			{
				iErrorCode = me1000DIOSetPortDirection(iBoardNumber, PORTD, iDirection);
			}
		}
    }

    if(iErrorCode)
    {
        printf(
            "Set direction for Board %d successfully \n", iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DIOSetPortDirection\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}


void Call_me1000DOSetLong(int iBoardNumber, int iValue)
{
    int iErrorCode;

    iErrorCode = me1000DOSetLong(iBoardNumber, PORTA, iValue);

    if(iErrorCode)
    {
		iErrorCode = me1000DOSetLong(iBoardNumber, PORTB, iValue);
    }

    if(iErrorCode)
    {
        printf(
            "Set value 0x%08x for Board %d successfully \n", iValue, iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DOSetLong\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}


void Call_me1000DOSetWord(int iBoardNumber, int iValue)
{
    int iErrorCode;

    iErrorCode = me1000DOSetWord(iBoardNumber, PORTA, 0, iValue);

    if(iErrorCode)
    {
        printf(
            "Set value 0x%04x for Board %d successfully \n", iValue, iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DOSetWord\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}

void Call_me1000DOSetByte(int iBoardNumber, int iValue)
{
    int iErrorCode;

    iErrorCode = me1000DOSetByte(iBoardNumber, PORTA, 0, iValue);

    if(iErrorCode)
    {
        printf(
            "Set value 0x%04x for Board %d successfully \n", iValue, iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DOSetByte\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}

void Call_me1000DOSetBit(int iBoardNumber, int iValue)
{
    int iErrorCode;

    iErrorCode = me1000DOSetBit(iBoardNumber, PORTA, 0, iValue);

    if(iErrorCode)
    {
        printf(
            "Set value 0x%04x for Board %d successfully \n", iValue, iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DOSetBit\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}


void Call_me1000DIGetLong(int iBoardNumber)
{
    int iErrorCode;
	int iValue;

    iErrorCode = me1000DIGetLong(iBoardNumber, PORTA, &iValue);

    if(iErrorCode)
    {
        printf(
            "Get value 0x%08x for Board %d successfully \n", iValue, iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DIGetLong\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}

void Call_me1000DIGetWord(int iBoardNumber)
{
    int iErrorCode;
	int iValue;

    iErrorCode = me1000DIGetWord(iBoardNumber, PORTA, 0, &iValue);

    if(iErrorCode)
    {
        printf(
            "Get value 0x%08x for Board %d successfully \n", iValue, iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DIGetWord\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}


void Call_me1000DIGetByte(int iBoardNumber)
{
    int iErrorCode;
	int iValue;

    iErrorCode = me1000DIGetByte(iBoardNumber, PORTA, 0, &iValue);

    if(iErrorCode)
    {
        printf(
            "Get value 0x%08x for Board %d successfully \n", iValue, iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DIGetByte\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}

void Call_me1000DIGetBit(int iBoardNumber)
{
    int iErrorCode;
	int iValue;

    iErrorCode = me1000DIGetBit(iBoardNumber, PORTA, 0, &iValue);

    if(iErrorCode)
    {
        printf(
            "Get value 0x%08x for Board %d successfully \n", iValue, iBoardNumber);
    }
    else
    {
        printf(
            "Error in Function Call_me1000DIGetBit\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}


void Call_me1000GetDriverVersion(void)
{
    int iErrorCode;
	int iDrvVersion;

    iErrorCode = me1000GetDriverVersion(&iDrvVersion);

    if(iErrorCode)
    {
	    printf(
			"Version of Driver is %04x.%04x\n",
			(iDrvVersion>>16)& 0xFFFF,
			(iDrvVersion)    & 0xFFFF);

    }
    else
    {
        printf(
            "Error in Function Call_me1000GetDriverVersion\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}

void Call_me1000GetSerialNumber(int iBoardNumber)
{
    int iErrorCode;
	int iSerial;

    iErrorCode = me1000GetSerialNumber(iBoardNumber, &iSerial);

    if(iErrorCode)
    {
	    printf(
			"Serial Number of the board is %08x\n",
			iSerial);
    }
    else
    {
        printf(
            "Error in Function Call_me1000GetSerialNumber\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}

void Call_me1000WriteUserString(int iBoardNumber)
{
	#define MAX_STR_CNT 0xFF

    int iErrorCode;
	char pcUserText[] = "This is our first board on the right slot of the rear";

	iErrorCode = me1000WriteUserString(iBoardNumber, pcUserText);

    if(iErrorCode)
    {
	    printf(
			"Write the user string:\n\t%s\n",
			pcUserText);
    }
    else
    {
        printf(
            "Error in Function Call_me1000WriteUserString\n"
            "Or there is no board on the spezified board number!\n");

		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}


void Call_me1000ReadUserString(int iBoardNumber)
{
	#define MAX_STR_CNT 0xFF

    int iErrorCode;
	int iMaxLength = MAX_STR_CNT;
	char pcUserText[MAX_STR_CNT];

	iErrorCode = me1000ReadUserString(iBoardNumber, pcUserText, iMaxLength);

    if(iErrorCode)
    {
	    printf(
			"User String of the board is\n\t%s\n",
			pcUserText);
    }
    else
    {
        printf(
            "Error in Function Call_me1000ReadUserString\n"
            "Or there is no board on the spezified board number!\n");
		{
			#define MAX_STR_CNT 0xFF

			int iErrorCode;
			int iMaxLength = MAX_STR_CNT;
			char pcErrortext[MAX_STR_CNT];

			iErrorCode = me1000GetDrvErrMess(pcErrortext, iMaxLength);
			printf(
				"Error String of the board is\n\t%s\n",
				pcErrortext);
		}
    }
}
