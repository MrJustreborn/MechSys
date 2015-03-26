
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
WORD ReadWord(WORD wPortAddress);

void delay(clock_t wait);

/****************************************************************************/
/* Global variables                                                         */
/****************************************************************************/
PCIENTRY gDevInfo;



 

/****************************************************************************/
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

	WORD wRead;

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
        wDeviceID = 0x810B;     // our Device ID, also 810A
        wIndex    = 0x00;       // first Device if more then one

        wErrorCode = GetPciDevice(
            wDeviceID,
            wVendorID,
            wIndex,
            &gDevInfo);
        
        if (wErrorCode == NOT_SUCCESSFUL)
        {
            printf("\rReady\n\tNo device found!\n", wDeviceID);
            printf("\rPlease change the device ID for other types (8100A)\n");
        }
        else
        {
            printf("\rReady\n\tFound a ME-8100!\n\n");

            printf("BasisIO:  0x%04x\n", gDevInfo.wBaseIO);
            printf("BasisPLX: 0x%04x\n\n", gDevInfo.wBasePLX);

	        printf("Register set A - Setting Tristate Off and Source mode ... \n");
	        printf("Write 0x0090 to control register of register set A ... \n\n");
            WriteWord(gDevInfo.wBaseIO, 0x0090);

			// Write example value

			printf("Register Set A - Output 0xabcd...\n"); 
			printf("Write 0xabcd to output register of register set A...\n\n"); 
            WriteWord(gDevInfo.wBaseIO + 0x06, 0xabcd);
 
			// Read example value

			printf("Register Set A - Input word...\n"); 
			printf("Read word form input register of of register set A...\n\n"); 
            wRead = ReadWord(gDevInfo.wBaseIO + 0x04);
                    
			printf("Result = %#4x\n", wRead);                    
 
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
            WriteByte(gDevInfo.wBasePLX+0x4C, 0x43);
            //printf("Read IrqPlx 0x%02x\n",ReadByte(gDevInfo.wBasePLX+0x4C));
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