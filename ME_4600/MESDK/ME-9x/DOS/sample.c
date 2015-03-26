/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com in special www.amcc.com/TechLib/pcidev.htm)                               */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                  Some input or output signals have to be convert !!                                      */
/*                  This is not a full working sample, it should show, how you can determin the resources   */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    000510  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#include <dos.h>
#include <stddef.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "amcc.h"
#include "sample.h"


typedef struct _DEV_INFO
{
    word    wVenID;
    word    wDevID;
    byte    bBusNo;
    byte    bDevFct;

    word    wDeviceIdx;

    dword   dwSerialNumber;

    word    wBaseIO;
    word    wBasePLX;
    word    wBaseSwap;
    byte    bIrqLine;
    byte    bIrqVector;
    long unsigned int ulIrqCnt;

} DEVINFO;



void(interrupt *oldhandler)(void);
DEVINFO gDI;




/*****************************************************************/
/*  MAIN Code Segment                                            */
/*****************************************************************/
int main(void)
{
    ReStart:    // we restart if the PLX bug occure (or if we change the addresses)

    /*--- Look for a valid PCI BIOS -----------------------------*/
    {
        if(pci_bios_present(NULL,NULL,NULL)==SUCCESSFUL)
        {
            printf("PCI BIOS Found\n\n");
        }
        else
        {
            printf("PCI BIOS not present\n\n");
            printf("Exit program\n\n");
            getch();
            return(1);
        }
    }

    /*--- look for the Meilhaus devices -------------------*/
    {
        gDI.wVenID      = 0x1402;   // our Vendor ID
        gDI.wDevID      = 0x0960;   // our Device ID, a value of 0x0960, 0x0950 or 0x0940
        gDI.wDeviceIdx  = 0;        // first device we could found

        if(find_pci_device(
            gDI.wDevID,
            gDI.wVenID,
            gDI.wDeviceIdx,
            &gDI.bBusNo,
            &gDI.bDevFct)  !=  SUCCESSFUL)
        {
            gDI.wDevID      = 0x0950;           // no ME-96 exist, maybe a ME-95 ?

            if(find_pci_device(
                gDI.wDevID,
                gDI.wVenID,
                gDI.wDeviceIdx,
                &gDI.bBusNo,
                &gDI.bDevFct)  !=  SUCCESSFUL)
            {
                gDI.wDevID      = 0x0940;       // no ME-96,95 exist, maybe a ME-94 ?

                if(find_pci_device(
                    gDI.wDevID,
                    gDI.wVenID,
                    gDI.wDeviceIdx,
                    &gDI.bBusNo,
                    &gDI.bDevFct)  !=  SUCCESSFUL)
                {
                    gDI.wDevID      = 0x0000;   // not one of the ME-9x boards found !!
                }
            }
        }

        switch (gDI.wDevID & 0xFFF0)            // PCI and cPCI is the same
        {
        case 0x0940:
            printf("Found a ME-94 PCI\n");
            break;
        case 0x0950:
            printf("Found a ME-95 PCI\n");
            break;
        case 0x0960:
            printf("Found a ME-96 PCI\n");
            break;
        case 0x0000:
            printf("Can not found any appropriate device!\n\n");
            printf("Exit program\n\n");
            getch();
            return(2);
        }

        printf("General PCI data: \n\tBus=%d \n\tDevice=%d \n\tFunction=%d\n\n",
                    gDI.bBusNo,
                    gDI.bDevFct>>3,
                    gDI.bDevFct&0x7);
        printf("\tVendor ID:   0x%04x\n", gDI.wVenID);
        printf("\tDevice ID:   0x%04x\n", gDI.wDevID);
    }


    /*--- Set own resources (if needed) -------------------------*/

    /* if you need special address or interrupt settings         */
    /* for compatibility, this works not in every case (under    */
    /* windows ???), check it out                                */
#define VERBIEGEN
#undef VERBIEGEN                // comment this if you need
#ifdef VERBIEGEN
    {
        static int DoIt = TRUE;

        gDI.wBaseIO = 0x300;
        gDI.bIrqLine= 5;

        if (DoIt == TRUE)
        {
            printf("Set address and interrupt to specific values:\n");
            printf("\taddress:   0x%04x\n", gDI.wBaseIO);
            printf("\tinterrupt: %d\n",     gDI.bIrqLine);

            write_configuration_word(
                gDI.bBusNo,
                gDI.bDevFct,
                PCI_CS_BASE_ADDRESS_2,
                gDI.wBaseIO);

            write_configuration_word(
                gDI.bBusNo,
                gDI.bDevFct,
                PCI_CS_INTERRUPT_LINE,
                gDI.bIrqLine);

            DoIt = FALSE;
            printf("Now we restart the sample !\n");
            printf("Press any key to continue\n");
            while(!kbhit());
            getch();
            goto ReStart;
        }
    }
#endif


    /* determine resources */
    {
        word    wSerialNumberHigh;
        word    wSerialNumberLow;


        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_1,
            &gDI.wBasePLX);
        gDI.wBasePLX = gDI.wBasePLX & 0xFFFC;
        printf("\tBase address PLX IO register:    0x%04x\n", gDI.wBasePLX);

        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_2,
            &gDI.wBaseIO);
        gDI.wBaseIO = gDI.wBaseIO & 0xFFFC;
        printf("\tMain Base address:               0x%04x\n", gDI.wBaseIO);

        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_BASE_ADDRESS_5,
            &gDI.wBaseSwap);
        gDI.wBaseSwap = gDI.wBaseSwap & 0xFFFC;
        printf("\tBase address PLX swap register:  0x%04x\n", gDI.wBaseSwap);


        read_configuration_byte(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_INTERRUPT_LINE,
            &gDI.bIrqLine);
        printf("\tInterrupt line:                  %d (dec)\n", gDI.bIrqLine);


        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_SUB_VENDOR_ID,
            &wSerialNumberLow);
        read_configuration_word(
            gDI.bBusNo,
            gDI.bDevFct,
            PCI_CS_SUB_DEVICE_ID,
            &wSerialNumberHigh);
        gDI.dwSerialNumber = ((dword)wSerialNumberHigh<<16)+ wSerialNumberLow;
        printf("\tserial number:                   0x%08lx\n", gDI.dwSerialNumber);
    }


    /*--- check if PLX bug occured, if so make the workaround --*/
    {
        if(gDI.wBasePLX & 0x80)
        {
            printf("PLX-Bug:\n");
            printf("\tBit 7 is set, we can not read\n");
            printf("\tthe PLX register, so we\n");
            printf("\thave to change the address.\n");

            if ((gDI.wBaseSwap > 0) &&    // base5 exist
                (gDI.wBaseSwap < 0xFFFF)) // it is not a memory addr.
                                          // normally we have to test wit & 0x01
            {
                /* board with new mon file */
                printf("\tnew hardware revision found (new mon file)\n");

                write_configuration_word(
                    gDI.bBusNo,
                    gDI.bDevFct,
                    PCI_CS_BASE_ADDRESS_1,
                    gDI.wBaseSwap);

                read_configuration_word(
                    gDI.bBusNo,
                    gDI.bDevFct,
                    PCI_CS_BASE_ADDRESS_1,
                    &gDI.wBasePLX);
                gDI.wBasePLX = gDI.wBasePLX & 0xFFFC;
                printf("\tChange Base address PLX to:    0x%04x\n", gDI.wBasePLX);
            }
            else
            {
                /* board with old mon file (no address at base 5) */
                printf("Old hardware (old mon file)\n");

                gDI.wBaseSwap = gDI.wBasePLX - 0x80;

                write_configuration_word(
                    gDI.bBusNo,
                    gDI.bDevFct,
                    PCI_CS_BASE_ADDRESS_1,
                    gDI.wBaseSwap);

                read_configuration_word(
                    gDI.bBusNo,
                    gDI.bDevFct,
                    PCI_CS_BASE_ADDRESS_1,
                    &gDI.wBasePLX);
                gDI.wBasePLX = gDI.wBasePLX & 0xFFFC;
                printf("\tChange Base address PLX to:    0x%04x\n", gDI.wBasePLX);
            }

            printf("Now we restart the sample !\n");
            printf("Press any key to continue\n");
            while(!kbhit());
            getch();
            goto ReStart;
        }
    }



    /*--- now we can play --------------------------------------*/

    /*--- switch to mode A write ports without irq --*/
    if ((gDI.wDevID == 0x0960) ||
        (gDI.wDevID == 0x0950) ||
        (gDI.wDevID == 0x096c) ||
        (gDI.wDevID == 0x095c))
    {
        // init hardware
        if ((gDI.wDevID == 0x0960) || (gDI.wDevID == 0x096c))
        {
            outport (gDI.wBaseIO + ME9x_PORT_CONTROL, 0x8B);
        }
        else
        {
            outport (gDI.wBaseIO + ME9x_PORT_CONTROL, 0x89);
        }
        outportb(gDI.wBaseIO + ME9x_WRITE_ENABLE, 0x00);    // write any value to enable

        printf("Write ports:\n");
        printf("Press any key to continue\n");
        do
        {
            static unsigned int cValue = 1;

            // write the values
            if ((gDI.wDevID == 0x0960) ||                   // ME-96
                (gDI.wDevID == 0x096c))
            {
                // we have to inverte the values
                outportb(gDI.wBaseIO + ME96_WRITE_PORT_A, ~cValue);
                printf("Write value port A: 0x%02x\n",cValue);
            }
            else                                            // ME-95
            {
                outportb(gDI.wBaseIO + ME95_WRITE_PORT_A, ~cValue);
                printf("Write value port A: 0x%02x\n",  cValue);
                outportb(gDI.wBaseIO + ME95_WRITE_PORT_B, ~cValue);
                printf("Write value port B: 0x%02x\n",  cValue);
            }

            if (cValue > 0x40)
            {   cValue = 1;             }
            else
            {   cValue = cValue * 2;    }

            sleep(1);
        }
        while(!kbhit());
        getch();
    }


    /*--- work in mode B read ports without irq -----*/
    if ((gDI.wDevID == 0x0960) ||                   // with ME-94 and 96 only
        (gDI.wDevID == 0x0940) ||
        (gDI.wDevID == 0x096c) ||
        (gDI.wDevID == 0x094c))
    {
        // init hardware
        outport (gDI.wBaseIO + ME9x_PORT_CONTROL, 0x9B);    //

        printf("Read ports:\n");
        printf("Press any key to continue\n");
        do
        {
            unsigned char cValue;

            // read the values
            if ((gDI.wDevID == 0x0960) ||                   // ME-96
                (gDI.wDevID == 0x096c))
            {

                cValue = inportb(gDI.wBaseIO + ME96_READ_PORT_B);
                cValue = (~cValue) & 0xFF;                  // we have to inverte the values
                printf("Read value port B: 0x%02x\n", cValue);

                cValue = inportb(gDI.wBaseIO + ME96_READ_PORT_C);
                cValue = (~cValue) & 0xFF;                  // we have to inverte the values
                printf("Read value port C: 0x%02x\n",cValue);
            }
            else                                            // ME-94
            {
                cValue = inportb(gDI.wBaseIO + ME94_READ_PORT_A);
                printf("Read value port A: 0x%02x\n",cValue);
                cValue = inportb(gDI.wBaseIO + ME94_READ_PORT_B);
                printf("Read value port B: 0x%02x\n",cValue);
                cValue = inportb(gDI.wBaseIO + ME94_READ_PORT_C);
                printf("Read value port C: 0x%02x\n",cValue & 0x14);
            }

            sleep(1);
        }
        while (!kbhit());

        getch();
    }



    /*--- switch to mode C irq proccessing ----------*/
    if ((gDI.wDevID == 0x0960) ||
        (gDI.wDevID == 0x0940) ||
        (gDI.wDevID == 0x096c) ||
        (gDI.wDevID == 0x094c))
    {
        // init hardware
        outport (gDI.wBaseIO + ME9x_PORT_CONTROL, 0xB7);  /* PC2 Strobe Input     */
        outport (gDI.wBaseIO + ME9x_PORT_CONTROL, 0x08);  /* PC2 freigeben        */
        outport (gDI.wBaseIO + ME9x_PORT_CONTROL, 0x05);  /* PC4 sperren          */
        outport (gDI.wBaseIO + ME9x_PORT_CONTROL, 0x0f);  /* PC2 setzen           */
        outport (gDI.wBaseIO + ME9x_PORT_CONTROL, 0x0d);  /* PC4 ruecksetzen      */

        // Enable interrupt on operating system
        // setup_int_vect();
        oldhandler = install_IRQ_Handler (gDI.bIrqLine, meIsr);

        // Enable interrupt on PLX PCI controller
        outportb(gDI.wBasePLX + PLX_INT_STA, 0x41);

        printf("Press any key to continue\n");
        do
        {
            gDI.ulIrqCnt = 0;
            sleep(1);
            // es wurden auf unseren system bis zu 70000 irqs pro sec gemessen
            printf("Irq per Second: %7lu\n", gDI.ulIrqCnt);
        }while (!kbhit());

        getch();

        // Disable interrupt on PLX PCI controller
        outportb(gDI.wBasePLX + PLX_INT_STA, 0x00);

        // Disable intzerrupt on operating system
    }

    printf("Press any key to continue\n");
    while(!kbhit());
    getch();

    /*--- disable outputs ---*/
    outportb(gDI.wBaseIO + ME9x_WRITE_DISABLE, 0x00);    // write any value to disable

    return 0;
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
       intrNr = FIRST_SLAVE_INTR + irq_nr - 8;

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
        + 0x01;                 // Offset Mask-Register

    irq_nr &= 0x0007;                   // zur Sicherheit nur 0-15 zulassen

    mask = inportb (pic_mask_reg) | (1 << irq_nr);  // Bit 'irq_nr' setzen
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
    {
        outportb (PIC_SLAVE_PORT, 0x20);    // EOI an Slave Base-Port
    }

    outportb (PIC_MASTER_PORT, 0x20);       // EOI an Master Base-Port
}


void interrupt meIsr()
{

    WORD wCfgW;
    WORD wCfgR;


    _disable ();                //  SW-Interrupts sperren (Aber wozu das?)

    wCfgR = inportb(gDI.wBasePLX + PLX_INT_STA);

    /* Note: If you using interrupt mode, */
    /* you have to enable PLX-Irq line    */
    /* wBasePLX + PLX_INT_STA (0x4C) is the PLX-IRQ status register
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

    if ((wCfgR & 0x04) || (wCfgR & 0x20))
    {
        //printf("huhu ! ich bin's!\n");
    }
    else
    {
        //printf("shared IRQ not for us\n");
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
            gDI.ulIrqCnt++;
        }
    }

    outport(gDI.wBasePLX + PLX_INT_STA, (WORD)wCfgW);

    _enable ();                         /* SW-Interrupts freigeben */
    IRQ_SendEOI (gDI.bIrqLine);    /* Ende des Interrupts an PIC(s) melden */
}
