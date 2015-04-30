// Dostest.c : Dos program to demonstrate how ME9100 boards and their base
// addresses can be located and to show the simplest register level programming
// of the ME9100 ports.

// NOTE:	Once the ME9100 ports have been located they can be programmed on 
//			the register level in exactly the same way as a normal 16550 serial 
//			port. For more information concerning register level port programming
//			the user is referred to the standard literature in book form and on
//			the internet.		

/****************************************************************************/
/* Include Files                                                            */
/****************************************************************************/
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

#include <time.h>

#include "DOSTest.h"


/****************************************************************************/
/*   Prototypes                                                             */
/****************************************************************************/
int PciBiosPresent(void);
int GetPciDevice(WORD, WORD, WORD, PCIENTRY *);
int FindPciDevice(WORD, WORD, WORD, BYTE *, BYTE *);
int ReadConfigurationWord(BYTE, BYTE, BYTE, WORD *);
void WriteByte(WORD wPortAddress, BYTE bDataWord);
void WriteWord(WORD wPortAddress, WORD wDataWord);
BYTE ReadByte(WORD wPortAddress);
WORD ReadWord(WORD wPortAddress);

void delay(clock_t wait);

/****************************************************************************/
/* Global variables                                                         */
/****************************************************************************/
PCIENTRY gDevInfo;



 

/***************************************************************************/
/* main function                                                            */
/****************************************************************************/
void 
    main(
        void)
{
    WORD wDeviceID;
    WORD wVendorID;
    WORD wIndex;
    WORD wErrorCode;
    
    WORD wPort1;
    WORD wPort2;
    
    char cModeCharacter;
    char cTransmitCharacter;
    char cReceiveCharacter;
    
    unsigned char ucLSR;
    
    int bLoopback; 

    wErrorCode = PciBiosPresent();

    if (wErrorCode == NOT_SUCCESSFUL)
    {
        printf("PCI BIOS not present !\n");
        printf("This utility runs only under Windows 95/98 or on a DOS boot disk !\n");
        printf("You can not program registers directly under Windows NT\n");
        _getch();
    }
    else
    {
        wVendorID = 0x1402;     // our Vendor ID
        wDeviceID = 0x9108;     // our Device ID, also 8104
        wIndex    = 0x00;       // first board if more then one

        wErrorCode = GetPciDevice(
            wDeviceID,
            wVendorID,
            wIndex,
            &gDevInfo);
        
        if (wErrorCode == NOT_SUCCESSFUL)
        {
			// No ME9108 board coul be found.

            printf("\rReady\n\tNo device found!\n", wDeviceID);
            printf("\rPlease change the device ID for other types (9104)\n");
        }
        else
        {
			// At least one ME9108 board was found

            printf("\rReady\n\tFound an ME-9100!\n\n");

            printf("BasisIO:  0x%04x\n", gDevInfo.wBaseIO);
            printf("BasisPLX: 0x%04x\n\n", gDevInfo.wBasePLX);
            
            // Loopback mode on port 1 or transmission port 1 -> port 2
            
            while(TRUE)
            {
	            printf("Please choose a test mode:\n\n");
	            
	            printf("A)     Loopback mode on port 1\n");
	            printf("B)     Transmiision from port 1 to port 2\n");
	            printf("       (Requires null modem cable between ports 1 and 2)\n\n");
	            printf("Mode: ");
	            
	            cModeCharacter = getch();
	            
	            printf("%c\n\n", cModeCharacter);
	            
	            if( (cModeCharacter == 'a')||(cModeCharacter == 'A') )
	            {
	            	bLoopback = TRUE;
	            	
	            	break;
            	}

	            if( (cModeCharacter == 'b')||(cModeCharacter == 'B') )
	            {                                                                                                          
	            	bLoopback = FALSE;
	            	
	            	break;
            	}
           	}

			// Base addresses for the first two ports on the board

			wPort1 = gDevInfo.wBaseIO;	 
			wPort2 = gDevInfo.wBaseIO + 8;
			                                                      
			// Initialise port 1                                                      
			
			WriteByte(wPort1 + 1, 0x00);		// Disable interrupts
						                                                      
			WriteByte(wPort1 + 3, 0x80);		// Set DLAB on
						                                                      
			// Set baud rate - Divisor 0x0010 -> Baudrate 14745600 / 16 / 16 = 56,700 BPS
			
			WriteByte(wPort1, 0x10);			// Set Baud rate - Divisor latch low byte
			WriteByte(wPort1, 0x00);			// Set Baud rate - Divisor latch high byte
			
			WriteByte(wPort1 + 3, 0x03);		// 8 bits, no parity, 1 stop bit
			
			WriteByte(wPort1 + 2, 0x00);		// Disable FIFO's 
						                                                      
			if(bLoopback)
			{
				WriteByte(wPort1 + 4, 0x10);		// Enable loopback mode 
			}
			else
			{
				WriteByte(wPort1 + 4, 0x00);		// Disabe loopback mode 
			}
						                                                      
			if(!bLoopback)
			{
				// Initialise port 2                                                      
				
				WriteByte(wPort2 + 1, 0x00);		// Disable interrupts
							                                                      
				WriteByte(wPort2 + 3, 0x80);		// Set DLAB on
							                                                      
				// Set baud rate - Divisor 0x0010 -> Baudrate 14745600 / 16 / 16 = 56,700 BPS
				
				WriteByte(wPort2, 0x10);			// Set Baud rate - Divisor latch low byte
				WriteByte(wPort2, 0x00);			// Set Baud rate - Divisor latch high byte
				
				WriteByte(wPort2 + 3, 0x03);		// 8 bits, no parity, 1 stop bit
				
				WriteByte(wPort2 + 2, 0x00);		// Disable FIFO's

				WriteByte(wPort2 + 4, 0x00);		// Disabe loopback mode 
			} 
			
			// Send keyboard characters from port 1 to port 2 until the user presses the 'ESC' key
			
			printf("Press any key to transmit a character\n");
			printf("Press 'ESC' to terminate the program\n\n");
			
			while(TRUE)
			{
				// Has the user pressed a key?
				
				if( kbhit() )
				{			
					// A key has been pressed, get the character entered
					
					cTransmitCharacter = getch();
				
					// Has the user pressed the 'ESC' key
					
					if(cTransmitCharacter == 27)
					{
						// 'ESC' key pressed -> end the loop
					
						break;
					}
					
					// Send the character to port 1
					
					WriteByte(wPort1, cTransmitCharacter);
				}
					
				// Has a character been received?
					
				if(!bLoopback)
				{
					// Read the line status register of port 2 to see if a character has been received
						
					ucLSR = ReadByte(wPort2 + 5);
	
					if(ucLSR&0x01)
					{
						// Character received -> get the character
							
						cReceiveCharacter = ReadByte(wPort2);
							
						// Print the character to the screen
							
						printf("%c\n", cReceiveCharacter);
					}	
				}					
				else
				{
					// Read the line status register of port 1 to see if a character has been received
						
					ucLSR = ReadByte(wPort1 + 5);
	
					if(ucLSR&0x01)
					{
						// Character received -> get the character
							
						cReceiveCharacter = ReadByte(wPort1);
							
						// Print the character to the screen
							
						printf("%c\n", cReceiveCharacter);
					}	
				}					
			}
									                                                      
            /* Note: If you using interrupt mode, */
            /* you have to enable PLX-Irq line    */
            /* wBasePLX+0x4C is the PLX-IRQ status register
               Meaning of the bits: (0x43)
               7:   Software Irq    - not used              - 0
               6:   PCI Irq Enable - we need this           - 1
               5:   Irq 2 status    - not used              - 0
               4:   Irq 2 polarity  - not used              - 0
               3:   Irq 2 enable    - not used              - 0
               2:   Irq 1 status    - we have to read this 
               1:   Irq 1 polarity  - we need High active   - 1
               0:   Irq 1 enable    - we have to enable it  - 1
               
            */             
        }
    }
}



/****************************************************************************/
/* Purpose: Determine the presence of the PCI BIOS                          */
/****************************************************************************/
int 
	PciBiosPresent(
					void)
{
   BYTE BiosStatus;
   WORD PciSignature;
   
   union _REGS in_regs;
   union _REGS out_regs;
   
   in_regs.h.ah = PCI_FUNCTION_ID;
   in_regs.h.al = PCI_BIOS_PRESENT;

   _int86(0x1a, &in_regs, &out_regs);	

   /* Read return registers */
   PciSignature = out_regs.x.dx;
   BiosStatus = out_regs.x.ax >> 8;


    /* if CARRY FLAG Set, BIOS not present */
    if ((out_regs.x.cflag & CARRY_FLAG) != 0) 
    {
        return NOT_SUCCESSFUL;
    }
    else
    {
        /* Next, we must check that BIOS Present Status == 0 */
        if (BiosStatus != 0) 
        {
            return NOT_SUCCESSFUL;
        }
        else
        {
            /* Check bytes for PCI Signature */
            if ( ( (PciSignature & 0xff) == 'P') &&
		               ( ( (PciSignature >> 8) & 0xff) == 'C') )
            {
                /* PCI BIOS present */
                return SUCCESSFUL;
            }
            else
            {
                return NOT_SUCCESSFUL;
            }
        }
    }
}



/****************************************************************************/
/* Purpose: Get the specified PCI device                                    */
/****************************************************************************/
int 
    GetPciDevice(
        WORD wDeviceID,
        WORD wVendorID,
        WORD wIndex,
        PCIENTRY *gpDevInfo)
{
    BYTE bBusNumber;
    BYTE DeviceFunctionBMP;
    WORD wErrorCode;
    WORD wData1;
    WORD wData2;


    wErrorCode = FindPciDevice(
        wDeviceID,
        wVendorID,
        wIndex,
        &bBusNumber,
        &DeviceFunctionBMP);

    if (wErrorCode == NOT_SUCCESSFUL)
    {
        return NOT_SUCCESSFUL;
    }
    else
    {
        gpDevInfo->wVenID = wDeviceID;
        gpDevInfo->wDevID = wDeviceID;


        ReadConfigurationWord(bBusNumber, 
                              DeviceFunctionBMP, 
                              0x2c, 
                              &wData1);

        ReadConfigurationWord(bBusNumber, 
                              DeviceFunctionBMP, 
                              0x2e, 
                              &wData2);

        gpDevInfo->wSerialNumberLow = wData1 & 0xffff;
        gpDevInfo->wSerialNumberHigh = wData2 & 0xffff;


        ReadConfigurationWord(bBusNumber, 
                              DeviceFunctionBMP, 
                              0x3c, 
                              &wData1);

        gpDevInfo->wIrqLine = (BYTE)(wData1 & 0xFF);


        ReadConfigurationWord(bBusNumber, 
                              DeviceFunctionBMP, 
                              0x14, 
                              &wData1);

        gpDevInfo->wBasePLX = wData1 & 0xFFFE;

        ReadConfigurationWord(bBusNumber, 
                              DeviceFunctionBMP, 
                              0x18, 
                              &wData1);

        gpDevInfo->wBaseIO = wData1 & 0xFFFE;

        return SUCCESSFUL;
    }
}



/****************************************************************************/
/* Purpose: Determine the location of PCI devices given a specific Vendor   */
/*          Device ID and Index number.  To find the first device, specify  */
/*          0 for wIndex, 1 in index finds the second device, etc.           */
/****************************************************************************/
int 
    FindPciDevice(
        WORD wDeviceID,
        WORD wVendorID,
        WORD wIndex,
        BYTE *bBusNumber,
        BYTE *DeviceFunctionBMP)
{
    int RetStatus;

   union _REGS in_regs;
   union _REGS out_regs;
   
    in_regs.x.cx = wDeviceID;
    in_regs.x.dx = wVendorID;
    in_regs.x.si = wIndex;
    in_regs.h.ah = PCI_FUNCTION_ID;
    in_regs.h.al = FIND_PCI_DEVICE;

    /* Call PCI BIOS Int 1Ah interface */
    _int86(0x1a, &in_regs, &out_regs);        

    /* First check if CARRY FLAG Set, if so, error has occurred */
    if ((out_regs.x.cflag & CARRY_FLAG) != 0) 
    {
        RetStatus = NOT_SUCCESSFUL;
    }
    else 
    {
        /* Return code from BIOS */
        RetStatus = (int)out_regs.h.ah;
        if (RetStatus == SUCCESSFUL) 
        {
            if (bBusNumber != NULL)                    
            {
                *bBusNumber = out_regs.h.bh;
            }

            if (DeviceFunctionBMP != NULL) 
            {
                *DeviceFunctionBMP = out_regs.h.bl;
            }
        }
    }

    return (RetStatus);
}



/****************************************************************************/
/* Purpose: Reads a WORD from the configuration space of a specific device  */
/****************************************************************************/
static int 
    ReadConfigurationWord(
        BYTE bBusNumber,
        BYTE DeviceFunctionBMP,
        BYTE register_number,
        WORD *data)
{
    int RetStatus;

   union _REGS in_regs;
   union _REGS out_regs;
   
    in_regs.h.bh = bBusNumber;
    in_regs.h.bl = DeviceFunctionBMP;
    in_regs.x.di = register_number;
    in_regs.h.ah = PCI_FUNCTION_ID;
    in_regs.h.al = READ_CONFIG_WORD;

    /* Call PCI BIOS Int 1Ah interface */
    _int86(0x1a, &in_regs, &out_regs);


    /* First check if CARRY FLAG Set, if so, error has occurred */
    if ((out_regs.x.cflag & CARRY_FLAG) != 0) 
    {
        RetStatus = NOT_SUCCESSFUL;
    }
    else 
    {
        /* Get Return code from BIOS */
        RetStatus = (int)out_regs.h.ah;

        /* If successful, return data */
        if (RetStatus == SUCCESSFUL) 
        {
            *data = out_regs.x.cx;   
        }
    }

    return RetStatus;
}



void WriteByte(WORD wPortAddress, BYTE bDataWord)
{
    _asm   mov al, bDataWord
    _asm   mov dx, wPortAddress
    _asm   out dx, al
}


void WriteWord(WORD wPortAddress, WORD wDataWord)
{
    _asm   mov ax, wDataWord
    _asm   mov dx, wPortAddress
    _asm   out dx, ax
}


BYTE ReadByte(WORD wPortAddress)
{   
    BYTE bDataWord;

    _asm   mov dx,wPortAddress
    _asm   in  al,dx
    _asm   mov bDataWord, al

    return(bDataWord);
}

WORD ReadWord(WORD wPortAddress)
{   
    WORD wDataWord;

    _asm   mov dx,wPortAddress
    _asm   in  ax,dx
    _asm   mov wDataWord, ax

    return(wDataWord);
}

/* Pauses for a specified number of microseconds. */
void delay( clock_t wait )
{
   clock_t goal;
   goal = wait + clock();
   while( goal > clock() );
}                   