/****************************************************************************/
/* Include Files                                                            */
/****************************************************************************/
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
void WriteDWord(WORD, DWORD);
DWORD ReadDWord(WORD);


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

#define DEVICE_ID_A 0x100A     // our Device ID
#define DEVICE_ID_B 0x100B

        wVendorID  = 0x1402;     // our Vendor ID
        wDeviceID  = DEVICE_ID_A;
        wIndex     = 0x00;       // first Device if more then one

        wErrorCode = GetPciDevice(
            wDeviceID,
            wVendorID,
            wIndex,
            &gDevInfo);

        if (wErrorCode == NOT_SUCCESSFUL)
        {
            wDeviceID  = DEVICE_ID_B;

            wErrorCode = GetPciDevice(
                wDeviceID,
                wVendorID,
                wIndex,
                &gDevInfo);
        }


        if (wErrorCode == NOT_SUCCESSFUL)
        {
            printf("\rReady\n\tNo device found!\n");
        }
        else
        {
            printf("\rReady\n\tFound a ME-1000!");
            if (wDeviceID == DEVICE_ID_A)
                printf(" (ME-1000A with 64 lines) \n\n");
            else
                printf(" (ME-1000B with 128 lines) \n\n");

            printf("BasisIO:  0x%04x\n", gDevInfo.wBaseIO);
            printf("BasisPLX: 0x%04x\n\n", gDevInfo.wBasePLX);

            /*
            Register set:
            Basis + 0x00:   R/W     Port 0 read/write
            Basis + 0x04:   R/W     Port 1 read/write
            Basis + 0x08:   R/W     Port 2 read/write
            Basis + 0x0C:   R/W     Port 3 read/write
            Basis + 0x10:   R/W     Bit0 set direction Port0 (0=Input; 1=Output)
                                    Bit1 set direction Port1 (0=Input; 1=Output)
                                    Bit2 set direction Port2 (0=Input; 1=Output)
                                    Bit3 set direction Port3 (0=Input; 1=Output)
            default after power on: all registers "0" (all lines are input)
            */

            printf("Be careful not to cause a short circuit!\n");
            {
                register unsigned long int Value;
                register unsigned long int iCnt;

                WriteDWord(gDevInfo.wBaseIO+0x10, 0x03);    // Set port 1 to output

                for (iCnt=0; iCnt<0xFFFFFFFF; iCnt++)
                {
                    WriteDWord(gDevInfo.wBaseIO+0x00, ~iCnt);
                    Value = ReadDWord(gDevInfo.wBaseIO+0x08);   // port 0 == 2 with the testadaptor

                    if (iCnt != ~Value)
                    {
                        printf("dismatch (0x%08lx)\n", iCnt);
                    }


                    WriteDWord(gDevInfo.wBaseIO+0x04, ~iCnt);
                    Value = ReadDWord(gDevInfo.wBaseIO+0x0c);   // port 1 == 3 with the testadaptor

                    if (iCnt != ~Value)
                    {
                        printf("dismatch (0x%08lx)\n", iCnt);
                    }

                    if ((iCnt & 0xFFFFF) == 0)
                    {
                        printf("passing 0x%08lx\n", iCnt);
                    }
                }
            }
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


/* Some compilers dont know the 32 bit out / in command     */
/* Thats why we use the __emit__ pseudo instruction         */
/* If there are problems to set 32 bit words, refer the     */
/* the appropriate Intel / Microsoft specifications         */
/* This sample is tested with MS-DOS without Windows and    */
/* and in a MS Windows 98 DOS box.                          */

void WriteDWord(WORD wPortAddress, DWORD dwDataWord)
{
   _DX  = wPortAddress;
   _EAX = dwDataWord;

   __emit__(0x66, 0xEF);
}


DWORD ReadDWord(WORD wPortAddress)
{
   _DX = wPortAddress;

   __emit__(0x66, 0xED);

   return(_EAX);
}
