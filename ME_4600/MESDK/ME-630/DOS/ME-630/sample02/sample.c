/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2000 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab (Andreas Bernau)                                                                     */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com)                                                                          */
/*                  special thanks to Mr. W. Seitz for the interrupt module for DOS                         */
/*                  (from DaimlerChrysler Aerospace / Dornier Satellitensysteme)                            */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    000222  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/

#include <dos.h>
#include <stddef.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#include "amcc.h"
#include "sample.h"

#ifdef MSC
#define outport(port,val)   outp(port,val)
#define inport(port)        inp(port)
#endif



void IRQ_Enable (int irq_nr);
void IRQ_Disable (int irq_nr);
void (interrupt *install_IRQ_Handler (int irq_nr, void (interrupt *new_handler) () ) ) ();
void IRQ_SendEOI(int irq_nr);
void interrupt abIsrForME630PCI();




/* Global Variable Definition */

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


DEVINFO gDI;
void(interrupt *oldhandler)(void);





#define  PIC_MASTER_PORT    0x20  /* Port-Adresse Master-PIC */
#define  PIC_SLAVE_PORT     0xA0  /* Port-Adresse Slave-PIC  */
#define  FIRST_MASTER_INTR  0x08  /* Nr. des ersten Master-Interrupts */
#define  FIRST_SLAVE_INTR   0x70  /* Nr. des ersten Slave-Interrupts  */



















/*****************************************************************/
/* MAIN Code Segment                                            */
/*****************************************************************/
void main()
{
    /* Look for a valid PCI BIOS */
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
        }
    }

    /* look for the Meilhaus ME-630 device */
    {
        gDI.wVenID      = 0x1402;
        gDI.wDevID      = 0x0630;
        gDI.wDeviceIdx  = 0;

        if(find_pci_device(
            gDI.wDevID,
            gDI.wVenID,
            gDI.wDeviceIdx,
            &gDI.bBusNo,
            &gDI.bDevFct)  ==  SUCCESSFUL)
        {
          printf("ME-630 Device Found: \n\tBus=%d \n\tDevice=%d \n\tFunction=%d\n\n",
                gDI.bBusNo,
                gDI.bDevFct>>3,
                gDI.bDevFct&0x7);
      }
      else
        {
          printf("Meilhaus ME-630 Device Not Found\n\n");
            printf("Exit program\n\n");
            getch();
        }
    }


    /* if you need special address and interrupt settings for compatibility */
    /* this works not under windows !!! ??? */
//#define VERBIEGEN
#ifdef VERBIEGEN
    {
        gDI.wBaseIO = 0x300;
        gDI.bIrqLine= 5;

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
        printf("\tBase address ME-630 register:    0x%04x\n", gDI.wBaseIO);

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


    /* check if PLX bug occured, if so make the work around*/
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
                /* board with old mon file (no mem address at base 5) */
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
        }
    }


    /*--- 1. reset board -----*/
    {
        printf("reset board ...\n");
        outport (gDI.wBaseIO + 0x00, 0x00);
    }


    /*--- 2. set relais ------*/
    {
        int iCnt;

        printf("set relais ...\n");
        for(iCnt=0; iCnt<0x10; iCnt++)
        {
            outport (gDI.wBaseIO + 0x01, iCnt);
            outport (gDI.wBaseIO + 0x02, iCnt>>8);
            printf("0x%02x\t",iCnt);
            sleep(1);
            if (kbhit()) break;
        }
        getch();
    }


    /*--- 3. read TTL inputs ------*/
    {
        char cValue;

        printf("read TTL inputs ...\n");
        printf("Press any key to continue\n");
        do
        {
            cValue = inportb(gDI.wBaseIO + 0x03);
            printf("Value 0x%02x\n",cValue);
            sleep(1);
        }while (!kbhit());
        getch();
    }


    /*--- 4. read opto isolated inputs ------*/
    {
        char cValue;

        printf("read opto isolated inputs ...\n");
        printf("Press any key to continue\n");
        do
        {
            cValue = inportb(gDI.wBaseIO + 0x04);
            printf("Value 0x%02x\n",cValue);
            sleep(1);
        }while (!kbhit());
        getch();
    }


    /*--- 5. interrupt processing ----------*/
    /* As interrupts are enabled, the interrupt handler must be installed   */
    /* and the previous handler must be chained to it                        */
#if(0)
    {
        setup_int_vect();

        outport(gDI.wBasePLX + 0x4C, 0x53);
        inportb(gDI.wBaseIO + 0x05);
        inportb(gDI.wBaseIO + 0x06);

        printf("Press any key to continue\n");
        do
        {
            gDI.ulIrqCnt = 0;
            sleep(1);
            // es wurden auf unseren system bis zu 70000 irqs pro sec gemessen
            printf("Irq per Second: %7lu\n", gDI.ulIrqCnt);
        }while (!kbhit());

        getch();

        outport(gDI.wBasePLX + 0x4C, 0x12);
    }
#else
    {
        oldhandler = install_IRQ_Handler(gDI.bIrqLine, abIsrForME630PCI);


        outport(gDI.wBasePLX + 0x4C, 0x53);
        inportb(gDI.wBaseIO + 0x05);
        inportb(gDI.wBaseIO + 0x06);

        printf("Press any key to continue\n");
        do
        {
            gDI.ulIrqCnt = 0;
            sleep(1);
            // es wurden auf unseren system bis zu 70000 irqs pro sec gemessen
            printf("Irq per Second: %7lu\n", gDI.ulIrqCnt);
        }while (!kbhit());

        getch();

        outport(gDI.wBasePLX + 0x4C, 0x12);
    }
#endif


    getch();
}






/************************************************************************/
/*    Function:   handler                                                 */
/*   Purpose:    check interrupt source and service S593x int's          */
/*   Inputs:     None                                                    */
/*  Outputs: None                                                    */
/************************************************************************/
void interrupt handler(void)
{
    byte bIntStatus;

    printf("*\n");

    bIntStatus = inportb(gDI.wBasePLX + PLX_INT_STA);

    if ((bIntStatus & 0x04) || (bIntStatus & 0x20))
    {
      /* Identify AMCC Interrupt Source(s) 
      printf("AMCC Hardware Interrupt Source:\n ");
      if((int_status & READ_TC_INT) != 0)
        {
            printf("  Read Transfer Count Interrupt\n");
         /* Clear Read Interrupt and Disable Read Channel 
          outpd(op_reg_base_address+AMCC_OP_REG_INTCSR, (int_status|0x00880000L));
           outpd(op_reg_base_address+AMCC_OP_REG_MCSR, (master_status&0xFFFFBFFFL));
          /* Insert Read TC interrupt code here 
        }

        if((int_status & WRITE_TC_INT) != 0)
        {
          printf("  Write Transfer Count Interrupt\n");

           /* Clear Write interrupt and Disable Write Channel 
            outpd(op_reg_base_address+AMCC_OP_REG_INTCSR,(int_status|0x00840000L));
            outpd(op_reg_base_address+AMCC_OP_REG_MCSR,(master_status&0xFFFFFBFFL));
           /*Insert Write TC interrupt code here 
        }

       if((int_status & MASTER_ABORT_INT) != 0)
        {
          printf("  Master Abort Interrupt\n");
          outpd(op_reg_base_address+AMCC_OP_REG_INTCSR,(int_status|0x00900000L));
            /* Insert Master Abort interrupt code here
        }

       if((int_status & TARGET_ABORT_INT) != 0)
        {
          printf("  Target Abort Interrupt\n");
          outpd(op_reg_base_address+AMCC_OP_REG_INTCSR,(int_status|0x00A00000L));
            /* Insert Target Abort interrupt code here 
        }*/

        gDI.ulIrqCnt++;

        outport(gDI.wBasePLX + PLX_INT_STA, 0x12);
        printf("Irq for us switch it off");
    }
  else
    {
        /* Interrupt is not from the ME-630, call the previous handler */
        outport(gDI.wBasePLX + PLX_INT_STA, 0x12);
        printf("Irq not for us switch it off");
        _chain_intr(oldhandler);
   }
    

    /* Specific End of interrupt to clear in-service bit */
    /* Mask upper 5 bits of int. line register             */
    if(gDI.bIrqLine<8)
    {
        outportb(0x20, 0x60|(gDI.bIrqLine&0x07));
    }
    else
    {
      /* Issue master then slave EOI */
      outportb(0xa0,0x60|((gDI.bIrqLine-8)&0x07));
       outportb(0x20,0x62);
    }
}


/************************************************************************/
/* SETUP_INT_VECT                                                       */
/*                                                                      */
/* Purpose:     Install the interrupt vector for the S5933 interrupt    */
/*              handler and reference the previous handler routine.     */
/* Inputs:      S5933 Operation registers base address                  */
/* Outputs:     None                                                    */
/************************************************************************/
void setup_int_vect(void)
{
  int mask;

 if(gDI.bIrqLine != 0xff)
    {
        if(gDI.bIrqLine < 8)
        {
            gDI.bIrqVector = 0x08 + gDI.bIrqLine;
        }
        else
        {
            gDI.bIrqVector = 0x70 + gDI.bIrqLine - 8;
        }
    }

 /* Make sure the system 8259 enables the IRQ with OCW1 @ I/O 21h */
    /* for IRQ0-7 or @ I/O A1h for IRQ8-15 */
  if(gDI.bIrqLine < 8)
    {
      mask = inportb(0x21);
      mask = mask & ~(1<<gDI.bIrqLine);
      outportb(0x21,mask);
   }
  else
    {
      mask = inportb(0xA1);
      mask = mask & ~(1<<(gDI.bIrqLine-8));
      outportb(0xA1,mask);
   }

 /* Save the old interrupt vector */
    oldhandler=getvect(gDI.bIrqVector);

   /* Install the new interrupt vector */
 setvect(gDI.bIrqVector, handler);
}



/***************************************************************************
void install (void interrupt (*farfunc)(), int inumber)
/***************************************************************************
{
  oldfunc  = _dos_getvect(inumber);
  setvect (inumber, farfunc);
}











/**************************************************************************/
/* Funktion: IRQ_Enable                                                   */
/* Aufgabe:  Laesst den Hardware-Interrupt 'irq_nr' zu.                   */
/*           Dazu wird das entsprechende Bit im Mask-Register des Master  */
/*           oder Slave-PICs geloescht.                                   */
/**************************************************************************/
void IRQ_Enable (int irq_nr)
{
    unsigned int   pic_mask_reg;  // Offset 1 zum PIC-Base-Port
    unsigned char  mask;          // Maskierung

   pic_mask_reg = ((irq_nr <= 7) ? PIC_MASTER_PORT : PIC_SLAVE_PORT) + 0x01;

   irq_nr &= 0x0007;                      // zur Sicherheit nur 0-15 zulassen

   mask = inportb (pic_mask_reg) & ~ (1 << irq_nr);  // Bit 'irq_nr' loeschen'
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
                 + 0x01;  // Offset Mask-Register

   irq_nr &= 0x0007;                      // zur Sicherheit nur 0-15 zulassen

   mask = inportb (pic_mask_reg) | (1 << irq_nr); // Bit 'irq_nr' setzen
   outportb (pic_mask_reg, mask);
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
    int intrNr;                         // Interrupt Nummer
    void (interrupt *old_handler) ();   // alter Handler

    if (irq_nr <= 7)                    // Master-PIC
       intrNr = FIRST_MASTER_INTR + irq_nr;
    else                                // Slave-PIC
       intrNr = FIRST_SLAVE_INTR + irq_nr;

    IRQ_Disable (irq_nr);               // HW-Interrupt 'irq_nr' sperren
    _disable ();                        // SW-Interrupts sperren

    old_handler = _dos_getvect ( intrNr );  // alten Handler retten

    _dos_setvect ( intrNr, new_handler);    // neuen Handler installieren

    _enable ();                         // SW-Interrupts freigeben
    IRQ_Enable (irq_nr);                // HW-Interrupt 'irq_nr' freigeben

    return old_handler;
}




/**************************************************************************/
/* Funktion: IRQ_SendEOI                                                  */
/* Aufgabe:  Signalisiert EOI an den Interrupt Controller (Master).       */
/*           Bei irq_nr > 7 wird auch dem Slave ein EOI geschickt.        */
/**************************************************************************/
void IRQ_SendEOI(int irq_nr)
{
   if ( irq_nr > 7)
   {
        outportb(PIC_SLAVE_PORT, 0x20);    // EOI an Slave Base-Port
   }
   outportb (PIC_MASTER_PORT, 0x20);        // EOI an Master Base-Port
}




void interrupt abIsrForME630PCI()
{

    word wCfgW;
    word wCfgR;


    _disable ();                  /* SW-Interrupts sperren */

    printf("*\n");

    inportb(gDI.wBaseIO + 0x05);
    inportb(gDI.wBaseIO + 0x06);

    wCfgR=inportb(gDI.wBasePLX + PLX_INT_STA);

    gDI.ulIrqCnt++;

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

    if ((wCfgR & 0x04) || (wCfgR & 0x20))
    {
        printf("huhu ! ich bin's!\n");
    }
    else
    {
        printf("shared IRQ not for us\n");
    }

/*    if ((wCfgR & 0x02) == 0)           // it is the original IRQ
    {
        wCfgW = wCfgR | 0x02;          // set bit 2        (1..8)
    }
    else                               // it is only the end of the IRQ signal
    {
        wCfgW = wCfgR & 0xFD;          // delete bit 2     (1..8)

        /*--- ISR in the true sense of the word ----
        {
            // do anything
            ulIrqCnt++;
        }
    }
*/

    _enable ();                     /* SW-Interrupts freigeben */
    IRQ_SendEOI (gDI.bIrqLine);     /* Ende des Interrupts an PIC(s) melden */
}
