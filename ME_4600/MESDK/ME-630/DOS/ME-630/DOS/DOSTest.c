/***************************************************************************
          DaimlerChrysler Aerospace
      Dornier Satellitensysteme 
      ST23  -  W. Seitz  -  28.01.2000
****************************************************************************

NAME:       SYNC.C     

FUNKTION:   Programm zur Synchronisation von Ausgabesequenzen durch ein H/W-
        Signal unter Verwendung der Meilhauskarte ME94 ISA/PCI. 
            
        Das Demoprogramm in der vorliegenden Form untersucht, ob das PCI-
        BIOS vorhanden ist, initialisert die ME94 und gibt am PC-Laut-
        sprecher einen Knackton aus, wenn auf PIN 5 des 25-pol. D-Sub der 
        ME94 ein 15 V Impuls gegeben wird. Die Ausgabe erfolgt mit der 
        fallenden Flanke.

        Die Adressierung der ME94 hängt vom Ergebnis der PCI-BIOS-Suche ab.
        Wird das PCI-BIOS gefunden wird die ME94 als PCI-Karte adressiert,
        andernfalls als ISA-Karte.

PARAMETER : keine

COMPILER  : BORLAND C 3.1
        Speichermodell 'Large'


****************************************************************************/

#include <conio.h>          // low-level I/O calls
#include <dos.h>            // dos routines
#include <stdio.h>          // C I/O calls
#include <ctype.h>
#include <string.h>

#include "DOSTest.h"





PCIENTRY gDevInfo;
long unsigned int ulIrqCnt = 0;




/**************************************************************************/
int main  (void)
/**************************************************************************/
{
    printf("Entering main ...\n");

    /*--- determine base and irq line -------------*/
    if (abGetME630Ressources())
    {
        printf("Could not determine resources!");
        return 1;
    }

    /*--- reset board -----*/
    {
        printf("reset board ...\n");
        outport (gDevInfo.wBaseIO + 0x00, 0x00);
    }


    /*--- set relais ------*/
    {
        int iTest=0;
        printf("set relais ...\n");
        printf("Press any key to continue\n");
        do
        {
            outport (gDevInfo.wBaseIO + 0x01, iTest);
            outport (gDevInfo.wBaseIO + 0x02, iTest>>8);
            printf("\rSet 0x%02x\n",iTest);
            iTest++;
            sleep(1);
        }while (!kbhit());
        getch();
    }

    /*--- read TTL inputs ------*/
    {
        char cValue;

        printf("read TTL inputs ...\n");
        printf("Press any key to continue\n");
        do
        {
            cValue = ReadByte(gDevInfo.wBaseIO + 0x03);
            printf("Value 0x%02x\n",cValue);
            sleep(1);
        }while (!kbhit());
        getch();
    }


    /*--- read opto isolated inputs ------*/
    {
        char cValue;

        printf("read opto isolated inputs ...\n");
        printf("Press any key to continue\n");
        do
        {
            cValue = ReadByte(gDevInfo.wBaseIO + 0x04);
            printf("Value 0x%02x\n",cValue);
            sleep(1);
        }while (!kbhit());
        getch();
    }

    /*--- count interrupts ----------*/
    {
        abEnableIrqOnOS();
        abEnable630IrqOnPLX();

        ReadByte(gDevInfo.wBaseIO + 0x05);
        ReadByte(gDevInfo.wBaseIO + 0x06);


        printf("Press any key to continue\n");
        do
        {
            ulIrqCnt = 0;
            sleep(1);
            // es wurden auf unseren system bis zu 70000 irqs pro sec gemessen
            printf("Irq per Second: %7lu\n", ulIrqCnt); 
        }while (!kbhit());

        getch();

        abDisable630IrqOnPLX();
        abDisableIrqOnOS();
    }

    return 0;
}



int abGetME630Ressources(void)
{
    WORD wDeviceID = 0x0630;     // our Device ID
    WORD wVendorID = 0x1402;     // our Vendor ID
    WORD wIndex    = 0x00;       // first Device if more then one
    WORD wErrorCode;
    WORD wCfgR;
    WORD wIdx;
    int x;


    printf("Entering abGetME630Ressources ...\n");

    if (PciBiosPresent() != SUCCESSFUL)
    {
        printf("No PCI BIOS found, this program runs only under DOS based OSs!");
        return(1);       
    }

    wErrorCode = GetPciDevice(wDeviceID,wVendorID,wIndex,&gDevInfo);
    gDevInfo.wDevID = wDeviceID;

    if (wErrorCode == NOT_SUCCESSFUL)
    {
        return 2;
    }
    else
    {
/*        switch (gDevInfo.wDevID & 0xFFF0)    // PCI and cPCI is the same for us
        {
        case 0x0940:
            printf("Found a ME-94 PCI with following settings:\n");
            break;
        case 0x0950:
            printf("Found a ME-95 PCI with following settings:\n");
            break;
        case 0x0960:
            printf("Found a ME-96 PCI with following settings:\n");
            break;
        }
*/
        printf("\tBasisPLX: 0x%04x\n", gDevInfo.wBasePLX);
        printf("\twBaseIO:  0x%04x\n", gDevInfo.wBaseIO);
        printf("\twIrqLine: %d\n", gDevInfo.wIrqLine);
        printf("\twVenID:   0x%04x\n", gDevInfo.wVenID);
        printf("\twDevID:   0x%04x\n", gDevInfo.wDevID);
        printf("\tSerial:   %04x%04x\n", gDevInfo.wSerialNumberHigh, gDevInfo.wSerialNumberLow);

        return(0);
    }
}








int abEnableIrqOnOS(void)
{
    printf("Entering abEnableIrqOnOS ...\n");

    old_sync_handler  = install_IRQ_Handler (gDevInfo.wIrqLine, abIsrForME630PCI);

    return(0);
}



int abEnable630IrqOnPLX(void)
{
    printf("Entering abEnable630IrqOnPLX ...\n");

    //abIsrForME630PCI();

    WriteByte(gDevInfo.wBasePLX+0x4C, 0x41);

    return(0);
}



int abDisable630IrqOnPLX(void)
{
    printf("Entering abDisable630IrqOnPLX ...\n");

    WriteByte(gDevInfo.wBasePLX+0x4C, 0x00);

    return(0);
}



int abDisableIrqOnOS(void)
{
    printf("Entering abDisableIrqOnOS ...\n");

    return(0);
}


void interrupt abIsrForME630PCI()
{
    
    WORD wCfgW;
    WORD wCfgR;


    _disable ();                  /* SW-Interrupts sperren */

    //printf("*\n");

    ReadByte(gDevInfo.wBaseIO + 0x05);
    ReadByte(gDevInfo.wBaseIO + 0x06);

    wCfgR=ReadByte(gDevInfo.wBasePLX+0x4C);

    /* Note: If you using interrupt mode, */
    /* you have to enable PLX-Irq line    */
    /* wBasePLX+0x4C is the PLX-IRQ status register
       Meaning of the bits: (0x43)
       7:   Software Irq    - not used              - 0
       6:   PCI Irq Enable  - we need this          - 1
       5:   Irq 2 status    -
       4:   Irq 2 polarity  -
       3:   Irq 2 enable    -
       2:   Irq 1 status    - we have to read this
       1:   Irq 1 polarity  - alternating from one edge to the next
       0:   Irq 1 enable    - we have to enable it  - 1

    */

/*    if ((wCfgR & 0x04) || (wCfgR & 0x20))
    {
        printf("huhu ! ich bin's!\n");
    }
    else
    {
        printf("shared IRQ not for us\n");
    }

    if ((wCfgR & 0x02) == 0)           // it is the original IRQ
    {
        wCfgW = wCfgR | 0x02;          // set bit 2        (1..8)
    }
    else                               // it is only the end of the IRQ signal
    {
        wCfgW = wCfgR & 0xFD;          // delete bit 2     (1..8)

        /*--- ISR in the true sense of the word ----*/
        {
            // do anything
            ulIrqCnt++;
        }
//    }

    //outport(gDevInfo.wBasePLX+0x4C, (WORD)wCfgW);

    _enable ();                         /* SW-Interrupts freigeben */
    IRQ_SendEOI (gDevInfo.wIrqLine);    /* Ende des Interrupts an PIC(s) melden */
}











/****************************************************************************
void install (void interrupt (*farfunc)(), int inumber)
/****************************************************************************
{
  oldfunc  = _dos_getvect(inumber);
  setvect (inumber, farfunc);
}*/








/****************************************************************************/
/* Purpose: Determine the presence of the PCI BIOS                          */
/****************************************************************************/
int PciBiosPresent(void)
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
    {        /* Next, must check that BIOS Present Status == 0 */
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
int GetPciDevice(WORD wDeviceID,WORD wVendorID,WORD wIndex,PCIENTRY *gpDevInfo)
{
    BYTE bBusNumber;
    BYTE DeviceFunctionBMP;
    WORD wErrorCode;
    DWORD dwData1;
    DWORD dwData2;

    wErrorCode = FindPciDevice(wDeviceID,wVendorID,wIndex,&bBusNumber,&DeviceFunctionBMP);

    if (wErrorCode == NOT_SUCCESSFUL)
    {
        return NOT_SUCCESSFUL;
    }
    else
    {
    gpDevInfo->wVenID = wVendorID;
    gpDevInfo->wDevID = wDeviceID;


    ReadConfigurationArea(READ_CONFIG_WORD,bBusNumber,DeviceFunctionBMP,0x2c,&dwData1);
        ReadConfigurationArea(READ_CONFIG_WORD,bBusNumber,DeviceFunctionBMP,0x2e,&dwData2);
        gpDevInfo->wSerialNumberLow = (WORD)(dwData1 & 0xffff);
        gpDevInfo->wSerialNumberHigh = (WORD)(dwData2 & 0xffff);


        ReadConfigurationArea(READ_CONFIG_WORD,bBusNumber,DeviceFunctionBMP,0x3c,&dwData1);
    gpDevInfo->wIrqLine = (BYTE)(dwData1 & 0xFF);


        ReadConfigurationArea(READ_CONFIG_WORD,bBusNumber,DeviceFunctionBMP,0x14,&dwData1);
        gpDevInfo->wBasePLX = (WORD)(dwData1 & 0xFFFE);

        ReadConfigurationArea(READ_CONFIG_WORD,bBusNumber,DeviceFunctionBMP,0x18,&dwData1);
        gpDevInfo->wBaseIO = (WORD)(dwData1 & 0xFFFE);
    return SUCCESSFUL;
    }
}



/****************************************************************************/
/* Purpose: Determine the location of PCI devices given a specific Vendor   */
/*          Device ID and Index number.  To find the first device, specify  */
/*          0 for wIndex, 1 in index finds the second device, etc.          */
/****************************************************************************/
int FindPciDevice(  WORD wDeviceID,WORD wVendorID,WORD wIndex,BYTE *bBusNumber,BYTE *DeviceFunctionBMP)
    {   int RetStatus;
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
    {        /* Return code from BIOS */
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
static int ReadConfigurationArea(
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
    }    return RetStatus;
}


/****************************************************************************/
/* Purpose: Read one Byte from Port                                         */
/****************************************************************************/
void WriteByte(WORD wPortAddress, BYTE bDataWord)
{
    _asm   mov al,bDataWord
    _asm   mov dx,wPortAddress
    _asm   out dx,al
}

/****************************************************************************/
/* Purpose: Write one Byte to Port                                          */
/****************************************************************************/
BYTE ReadByte(WORD wPortAddress)
{
    BYTE bDataWord;

    _asm   mov dx,wPortAddress
    _asm   in  al,dx
    _asm   mov bDataWord,al

    return(bDataWord);
}















/**************************************************************************/
/* Funktion: install_IRQ_Handler                                          */
/* Aufgabe:  Die Routine 'new_handler' wird fuer den Hardware-Interrupt   */
/*           'irq_nr' installiert.                                        */
/*           Zurueckgegeben wird die Adresse einer ggf. bereits zuvor     */
/*           installierten Routine                                        */
/**************************************************************************/
void (interrupt *install_IRQ_Handler (int irq_nr, void (interrupt *new_handler) () ) ) ()
{
    int intrNr;                         /* Interrupt Nummer */
    void (interrupt *old_handler) ();   /* alter Handler    */

    if (irq_nr <= 7)                    /* Master-PIC       */
       intrNr = FIRST_MASTER_INTR + irq_nr;
    else                                /* Slave-PIC        */
       intrNr = FIRST_SLAVE_INTR + irq_nr;

    IRQ_Disable (irq_nr);               /* HW-Interrupt 'irq_nr' sperren */
    _disable ();                        /* SW-Interrupts sperren    */

    old_handler = _dos_getvect ( intrNr );  /* alten Handler retten */

    _dos_setvect ( intrNr, new_handler);    /* neuen Handler installieren */

    _enable ();                         /* SW-Interrupts freigeben  */
    IRQ_Enable (irq_nr);                /* HW-Interrupt 'irq_nr' freigeben */

    return old_handler;
}



/**************************************************************************/
/* Funktion: IRQ_Enable                                                   */
/* Aufgabe:  Laesst den Hardware-Interrupt 'irq_nr' zu.                   */
/*           Dazu wird das entsprechende Bit im Mask-Register des Master  */
/*           oder Slave-PICs geloescht.                                   */
/**************************************************************************/
void IRQ_Enable (int irq_nr)
{
unsigned int   pic_mask_reg;  /* Offset 1 zum PIC-Base-Port */
unsigned char  mask;          /* Maskierung */

   pic_mask_reg = ((irq_nr <= 7) ? PIC_MASTER_PORT : PIC_SLAVE_PORT) + 0x01;

   irq_nr &= 0x0007;                      /* zur Sicherheit nur 0-15 zulassen */

   mask = inportb (pic_mask_reg) & ~ (1 << irq_nr);  /* Bit 'irq_nr' loeschen' */
   outportb (pic_mask_reg, mask);
}



/**************************************************************************/
/* Funktion: IRQ_Disable                                                  */
/* Aufgabe:  Sperrt den Hardware-Interrupt 'irq_nr'.                      */
/*           Dazu wird das entsprechende Bit im Mask-Register des Master  */
/*           oder Slave-PICs gesetzt.                                     */
/**************************************************************************/
void IRQ_Disable (int irq_nr)
{
unsigned  int   pic_mask_reg;
unsigned  char  mask;

   pic_mask_reg = ((irq_nr <= 7) ? PIC_MASTER_PORT
                 : PIC_SLAVE_PORT)
                 + 0x01;  /* Offset Mask-Register */

   irq_nr &= 0x0007;                      /* zur Sicherheit nur 0-15 zulassen */

   mask = inportb (pic_mask_reg) | (1 << irq_nr); /* Bit 'irq_nr' setzen */
   outportb (pic_mask_reg, mask);
}


/**************************************************************************/
/* Funktion: IRQ_SendEOI                                                  */
/* Aufgabe:  Signalisiert EOI an den Interrupt Controller (Master).       */
/*           Bei irq_nr > 7 wird auch dem Slave ein EOI geschickt.        */
/**************************************************************************/
void IRQ_SendEOI (int irq_nr)
{
   if ( irq_nr > 7)
      outportb (PIC_SLAVE_PORT, 0x20);     /* EOI an Slave Base-Port  */
   outportb (PIC_MASTER_PORT, 0x20);       /* EOI an Master Base-Port */
}

