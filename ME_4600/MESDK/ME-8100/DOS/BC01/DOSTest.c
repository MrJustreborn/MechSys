
/****************************************************************************/
/* Include Files                                                            */
/****************************************************************************/
#include <dos.h>
#include <stdio.h>
#include <conio.h>

#include "DOSTest.h"


/****************************************************************************/
/*   Prototypes                                                             */
/****************************************************************************/
int PciBiosPresent(void);
int GetPciDevice(WORD, WORD, WORD, PCIENTRY *);
int FindPciDevice(WORD, WORD, WORD, BYTE *, BYTE *);
int ReadConfigurationArea(BYTE, BYTE, BYTE, BYTE, DWORD *);
void WriteByte(WORD wPortAddress, BYTE bDataWord);
BYTE ReadByte(WORD wPortAddress);


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


    wErrorCode = PciBiosPresent();

    if (wErrorCode == NOT_SUCCESSFUL)
    {
        printf("PCI BIOS not presented !\n");
        printf("This utility runs only under Windows 95/98 or on a DOS boot disk !\n");
        printf("You can not programming registers directly under Windows NT\n");
        getch();
    }
    else
    {
        wVendorID = 0x1402;     // our Vendor ID
        wDeviceID = 0x810A;     // our Device ID, also 140a, 140b or 1401, 1402
        //wDeviceID = 0x810B;
        wIndex    = 0x00;       // first Device if more then one

        wErrorCode = GetPciDevice(
            wDeviceID,
            wVendorID,
            wIndex,
            &gDevInfo);
        
        if (wErrorCode == NOT_SUCCESSFUL)
        {
            printf("\rReady\n\tNo device found!\n", wDeviceID);
            printf("\rPlease change the device ID for other types (810A, 810B)\n");
        }
        else
        {
            printf("\rReady\n\tFound a ME-8100!\n\n");

            printf("BasisIO:  0x%04x\n", gDevInfo.wBaseIO);
            printf("BasisPLX: 0x%04x\n\n", gDevInfo.wBasePLX);


            // Prepare the card
            // See manual for details
            printf("Preparing ME-8100... \n");
            printf("See VC152C_1 sample for more details !!! \n");

            // See VC152C_1 sample for more details

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
            //WriteByte(gDevInfo.wBasePLX+0x4C, 0x43);
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
   DWORD PciSignature;
   WORD ax, flags;

   _AH = PCI_FUNCTION_ID;
   _AL = PCI_BIOS_PRESENT;

   geninterrupt(0x1a);          // Call PCI BIOS Int 1Ah interface

   /* Save registers */
   ax = _AX;
   PciSignature = _EDX;
   flags = _FLAGS;
   BiosStatus = HIGH_BYTE(ax);


    /* if CARRY FLAG Set, BIOS not present */
    if ((flags & CARRY_FLAG) != 0) 
    {
        return NOT_SUCCESSFUL;
    }
    else
    {
        /* Next, must check that BIOS Present Status == 0 */
        if (BiosStatus != 0) 
        {
            return NOT_SUCCESSFUL;
        }
        else
        {
            /* Check bytes for PCI Signature */
            if ((PciSignature & 0xff)        == 'P' &&
               ((PciSignature >> 8) & 0xff)  == 'C' &&
               ((PciSignature >> 16) & 0xff) == 'I' &&
               ((PciSignature >> 24) & 0xff) == ' ') 
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
    DWORD dwData1;
    DWORD dwData2;


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


        ReadConfigurationArea(READ_CONFIG_WORD, 
                              bBusNumber, 
                              DeviceFunctionBMP, 
                              0x2c, 
                              &dwData1);
        ReadConfigurationArea(READ_CONFIG_WORD, 
                              bBusNumber, 
                              DeviceFunctionBMP, 
                              0x2e, 
                              &dwData2);
        gpDevInfo->wSerialNumberLow = (WORD)(dwData1 & 0xffff);
        gpDevInfo->wSerialNumberHigh = (WORD)(dwData2 & 0xffff);


        ReadConfigurationArea(READ_CONFIG_WORD, 
                              bBusNumber, 
                              DeviceFunctionBMP, 
                              0x3c, 
                              &dwData1);
        gpDevInfo->wIrqLine = (BYTE)(dwData1 & 0xFF);


        ReadConfigurationArea(READ_CONFIG_WORD, 
                              bBusNumber, 
                              DeviceFunctionBMP, 
                              0x14, 
                              &dwData1);
        gpDevInfo->wBasePLX = (WORD)(dwData1 & 0xFFFE);

        ReadConfigurationArea(READ_CONFIG_WORD, 
                              bBusNumber, 
                              DeviceFunctionBMP, 
                              0x18, 
                              &dwData1);
        gpDevInfo->wBaseIO = (WORD)(dwData1 & 0xFFFE);
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
    WORD ax, bx, flags;


    _CX = wDeviceID;
    _DX = wVendorID;
    _SI = wIndex;
    _AH = PCI_FUNCTION_ID;
    _AL = FIND_PCI_DEVICE;

    /* Call PCI BIOS Int 1Ah interface */
    geninterrupt(0x1a);        

    /* Save registers */
    ax = _AX;
    bx = _BX;
    flags = _FLAGS;

    /* First check if CARRY FLAG Set, if so, error has occurred */
    if ((flags & CARRY_FLAG) == 0) 
    {
        /* Return code from BIOS */
        RetStatus = HIGH_BYTE(ax);
        if (RetStatus == SUCCESSFUL) 
        {
            if (bBusNumber != NULL) 
            {
                *bBusNumber = HIGH_BYTE(bx);
            }

            if (DeviceFunctionBMP != NULL) 
            {
                *DeviceFunctionBMP = LOW_BYTE(bx);
            }
        }
    }
    else 
    {
        RetStatus = NOT_SUCCESSFUL;
    }

    return (RetStatus);
}



/****************************************************************************/
/* Purpose: Reads from the configuration space of a specific device         */
/****************************************************************************/
static int 
    ReadConfigurationArea(
        BYTE function, 
        BYTE bBusNumber,
        BYTE DeviceFunctionBMP,
        BYTE register_number,
        DWORD *data)
{
    int RetStatus;
    WORD ax, flags;
    DWORD ecx;

    _BH = bBusNumber;
    _BL = DeviceFunctionBMP;
    _DI = register_number;
    _AH = PCI_FUNCTION_ID;
    _AL = function;

    /* Call PCI BIOS Int 1Ah interface */
    geninterrupt(0x1a);

    /* Save registers */
    ecx = _ECX;
    ax = _AX;
    flags = _FLAGS;

    /* First check if CARRY FLAG Set, if so, error has occurred */
    if ((flags & CARRY_FLAG) == 0) 
    {
        /* Get Return code from BIOS */
        RetStatus = HIGH_BYTE(ax);

        /* If successful, return data */
        if (RetStatus == SUCCESSFUL) 
        {
            *data = ecx;   
        }
    }
    else 
    {
        RetStatus = NOT_SUCCESSFUL;
    }

    return RetStatus;
}



void WriteByte(WORD wPortAddress, BYTE bDataWord)
{
    _asm   mov al,bDataWord
    _asm   mov dx,wPortAddress
    _asm   out dx,al
}


BYTE ReadByte(WORD wPortAddress)
{   
    BYTE bDataWord;

    _asm   mov dx,wPortAddress
    _asm   in  al,dx
    _asm   mov bDataWord,al

    return(bDataWord);
}
