// Sample_01.cpp : Text based (Console) program to demonstrate the use
// of the simplest WIN32 API routines.

// This test program is by no means intended to provide a full coverage
// of the WIN32 communications API. The ports on the ME9100 family of boards 
// can be programmed in the same way as any other standard COM port under 
// Windows NT/95/98. For more information the user should refer to the 
// information from Microsoft concerning the WIN32 communications API, in 
// particular the article "Serial Communications in Win32" by Allen Denver on
// the MSDN library, or to one of the many books which cover this aspect of 
// WIN32 programming.

#include "stdafx.h"

#include <stdio.h>
#include <conio.h>

void main(int argc, char* argv[])
{
	printf("This test program sends text from one port to another\n");
	printf("using the WIN32 communications API.\n");
	printf("The transmitting and receiving port must be connected\n");
	printf("using a null modem cable.\n\n\n");
	
	HANDLE hCommTx;
		
	char port_name[80];
	
	char win32_port_name[80];

	// Ask the user for the name of the transmitter port
	
	while(TRUE)
	{
		printf("Name of the transmitter port (e.g. COM4 - RETURN to exit) : ");
		gets(&port_name[0]);
		printf("\n");

		if( strlen(port_name) == 0 )
		{
			return;
		}

		strcpy(win32_port_name, "\\\\.\\");

		strcat(win32_port_name, port_name);
		
		// Try to open the transmitter port.
		
		hCommTx = CreateFile(	win32_port_name,  
								GENERIC_READ | GENERIC_WRITE, 
								0, 
								0, 
								OPEN_EXISTING,
								0,
								0	);
 
		if(hCommTx == INVALID_HANDLE_VALUE)
		{
			printf("%s could not be opened\n", port_name);
		}
		else
		{
			break;
		}
	}

	HANDLE hCommRx;
		
	// Ask the user for the name of the receiver port
	
	while(TRUE)
	{
		printf("Name of the receiver port (e.g. COM5 - RETURN to exit) : ");
		gets(&port_name[0]);
		printf("\n");

		if( strlen(port_name) == 0 )
		{
			return;
		}

		strcpy(win32_port_name, "\\\\.\\");

		strcat(win32_port_name, port_name);
		
		// Try to open the receiver port.
		
		hCommRx = CreateFile(	win32_port_name,  
								GENERIC_READ | GENERIC_WRITE, 
								0, 
								0, 
								OPEN_EXISTING,
								0,
								0	);
 
		if(hCommRx == INVALID_HANDLE_VALUE)
		{
			printf("%s could not be opened\n", port_name);
		}
		else
		{
			break;
		}
	}

	// Set baud rate, parity etc. for the ports
	
	DCB dcb;

	FillMemory(&dcb, sizeof(dcb), 0);

	dcb.DCBlength = sizeof(dcb);
	
	// Copy the string "baud=9600 parity=N data=8 stop=1" to a local buffer
	// due to WIN32 API error under WIN95 - see Microsoft Knowledge Base
	
	char sz_comm_settings[64];

	strcpy(&sz_comm_settings[0], "baud=9600 parity=N data=8 stop=1");

	BuildCommDCB(&sz_comm_settings[0], &dcb);
   
	// Setting for first port
   	
	SetCommState(hCommTx, &dcb);
   
	// Setting for second port
   	
	SetCommState(hCommRx, &dcb);

	// Set timeouts for the ports
	
	COMMTIMEOUTS timeouts;

	timeouts.ReadIntervalTimeout = 20; 
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.ReadTotalTimeoutConstant = 100;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 100;

	// Timeouts for first port
	
	SetCommTimeouts(hCommTx, &timeouts);

	// Timeouts for second port
	
	SetCommTimeouts(hCommRx, &timeouts);

	char sz_tx_text[256]; 
	char sz_rx_text[256];

	// Ask the user in a loop for text to send from the first port to
	// the second port. End the loop when the usaer enters an empty text.
	
	while(TRUE)
	{
		printf("Text to transmit (RETURN to exit) : ");
		gets(&sz_tx_text[0]);
		printf("\n");

		if( strlen(sz_tx_text) == 0 )
		{
			break;
		}
		
		// Write the user text to the first port.
		
		DWORD dw_bytes_written;

		WriteFile(hCommTx, (void*)sz_tx_text, strlen(sz_tx_text) + 1, &dw_bytes_written, NULL);

		FillMemory(&sz_rx_text[0], 256, 0);

		DWORD dw_bytes_read;
		
		// Read from the second port and display the result..
		
		ReadFile(hCommRx, (void*)&sz_rx_text[0], 256, &dw_bytes_read, NULL);

		printf("Received Text                     : \"%s\"\n\n", &sz_rx_text[0]);
	}

	// Close both ports.
	
	CloseHandle(hCommRx);

	CloseHandle(hCommTx);
}
