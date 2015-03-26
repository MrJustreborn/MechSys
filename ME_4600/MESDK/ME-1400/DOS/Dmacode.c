SAMPLE S5933 DMA SUPPORT CODE



#include <dos.h>
#include <stddef.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "amcc.h"

#define HIGH_BYTE(ax)	(ax >> 8)
#define LOW_BYTE(ax)		(ax & 0xff)

/****************************************************************/
/*  A2P = Add-on to PCI FIFO												 */
/*  P2A = PCI to Add-on FIFO												 */
/****************************************************************/

/* Interrupt Enables */
#define EN_READ_TC_INT		0x00008000L
#define EN_WRITE_TC_INT		0x00004000L

/* FIFO Flag Reset */
#define RESET_A2P_FLAGS		0x04000000L
#define RESET_P2A_FLAGS		0x02000000L

/* FIFO Management Scheme */
#define A2P_REQ_AT_4FULL	0x00000200L
#define P2A_REQ_AT_4EMPTY	0x00002000L

/* FIFO Relative Priority */
#define A2P_HI_PRIORITY		0x00000100L
#define P2A_HI_PRIORITY		0x00001000L

/* Enable Transfer Count */
#define EN_TCOUNT			0x10000000L

/* Enable Bus Mastering */
#define EN_A2P_TRANSFERS	0x00000400L
#define EN_P2A_TRANSFERS	0x00004000L

/* Identify Interrupt Sources */
#define ANY_S593X_INT		0x00800000L
#define READ_TC_INT		0x00080000L
#define WRITE_TC_INT		0x00040000L
#define MASTER_ABORT_INT	0x00100000L
#define TARGET_ABORT_INT	0x00200000L
#define BUS_MASTER_INT		0x00200000L

/* Global Variable Definition */
word	op_reg_base_address;
byte interrupt_line, int_vector;
void(interrupt *oldhandler)(void);

/*****************************************************************/
/*	MAIN Code Segment															  */
/*****************************************************************/

void main()
{
	/* Define Function Prototypes */
	void setup_pci_dma(word op_reg_base_address);
	void setup_int_vect(byte bus_num,byte dev_func);

	word	vendor_id, device_id, index;
	byte	bus_num, dev_func, command;
	int 	bios_present;

	vendor_id = 0x10E8;
	device_id = 0x4750;
	index = 0;

/* Look for a valid PCI BIOS */
if(pci_bios_present(NULL,NULL,NULL)==SUCCESSFUL){
	bios_present=TRUE;
	printf("PCI BIOS Found\n\n");
}
else{
	printf("PCI BIOS not present\n\n");
	bios_present=FALSE;
}


/* If the BIOS is present, look for the AMCC device */
if(bios_present){
	if(find_pci_device(device_id,vendor_id,index,&bus_num,
					&dev_func)==SUCCESSFUL){
		printf("AMCC Device Found: Bus=%d Device=%d Function=%d\n\n",
			bus_num,(dev_func>>3),(dev_func&0x7));
	}
	else{
		printf("AMCC Device Not Found\n\n");
	}
}


/* Check to make sure BIOS enabled bus mastering in PCI Command Register */
	read_configuration_byte(bus_num,dev_func,PCI_CS_COMMAND,&command);
	if(command!=0x07)
		printf("BIOS did not enable S5933 Bus Mastering");

/* Find the physical location of S5933 operation Registers in I/O space */
	read_configuration_word(bus_num,dev_func,
					 PCI_CS_BASE_ADDRESS_0,&op_reg_base_address);

/* Mask Lower 2 bits of BADR0 - they are not part of the address*/
	op_reg_base_address = (op_reg_base_address & 0xFFFC);


/* As interrupts are enabled, the interrupt handler must be installed */
/* and the previous handler must be chained to it							 */

setup_int_vect(bus_num,dev_func);

/* Call routine to setup PCI initiated bus mastering */

setup_pci_dma(op_reg_base_address);

}

void setup_pci_dma(word op_reg_base)
{
	char src[20], dest[20], rtc[20], wtc[20];
	dword	source, destination;
	dword readtc, writetc;

/* Read in source,destination and transfer counts.  They are read as	   */
/* string values and strtoul() converts to a long int value.  Addresses	*/
/* must be input in hex in the format 0x_______ and transfer counts are */
/* decimal values.																		*/

	printf("Read from address: ");
	gets(src);
	source=strtoul(src,NULL,16);

	printf("Write to address: ");
	gets(dest);
	destination=strtoul(dest,NULL,16);

	printf("Read transfer byte count: ");
	gets(rtc);
	readtc=strtoul(rtc,NULL,10);

	printf("Write transfer byte count: ");
	gets(wtc);
	writetc=strtoul(wtc,NULL,10);

/* Program S5933 DMA Registers */
	outpd(op_reg_base+AMCC_OP_REG_MWAR, destination);
	outpd(op_reg_base+AMCC_OP_REG_MRAR, source);
	outpd(op_reg_base+AMCC_OP_REG_MWTC, writetc);
	outpd(op_reg_base+AMCC_OP_REG_MRTC, readtc);

/* Enable Bus Mastering */
	outpd(op_reg_base+AMCC_OP_REG_MCSR, inpd(op_reg_base+AMCC_OP_REG_MCSR)|
					RESET_A2P_FLAGS|
					RESET_P2A_FLAGS|
					A2P_HI_PRIORITY|
					P2A_HI_PRIORITY|
					EN_A2P_TRANSFERS|
					EN_P2A_TRANSFERS);
}

/************************************************************************/
/*	Function:	handler																	*/
/*	Purpose:		check interrupt source and service S593x int's				*/
/*	Inputs:		None																		*/
/* Outputs:		None																		*/
/************************************************************************/
void interrupt handler(void)
{
	dword int_status,master_status;
	int_status = inpd(op_reg_base_address+AMCC_OP_REG_INTCSR);
	master_status = inpd(op_reg_base_address+AMCC_OP_REG_MCSR);

	if((int_status & ANY_S593X_INT)!= 0){
		/* Identify AMCC Interrupt Source(s) */
		printf("AMCC Hardware Interrupt Source:\n ");
		if((int_status & READ_TC_INT) != 0){
			printf("  Read Transfer Count Interrupt\n");
			/* Clear Read Interrupt and Disable Read Channel */
			outpd(op_reg_base_address+AMCC_OP_REG_INTCSR,
					(int_status|0x00880000L));
			outpd(op_reg_base_address+AMCC_OP_REG_MCSR,
					(master_status&0xFFFFBFFFL));

			/* Insert Read TC interrupt code here */
						}
		if((int_status & WRITE_TC_INT) != 0){
			printf("  Write Transfer Count Interrupt\n");
			/* Clear Write interrupt and Disable Write Channel */
			outpd(op_reg_base_address+AMCC_OP_REG_INTCSR,
					(int_status|0x00840000L));
			outpd(op_reg_base_address+AMCC_OP_REG_MCSR,
					(master_status&0xFFFFFBFFL));

			/*Insert Write TC interrupt code here */
						}
		if((int_status & MASTER_ABORT_INT) != 0){
			printf("  Master Abort Interrupt\n");
			outpd(op_reg_base_address+AMCC_OP_REG_INTCSR,
					(int_status|0x00900000L));

			/* Insert Master Abort interrupt code here */
			}
		if((int_status & TARGET_ABORT_INT) != 0){
			printf("  Target Abort Interrupt\n");
			outpd(op_reg_base_address+AMCC_OP_REG_INTCSR,
					(int_status|0x00A00000L));

			/* Insert Target Abort interrupt code here */
			}
	}
		else{
  /* Interrupt is not from the S5933, call the previous handler */
	_chain_intr(oldhandler);
	}

   /* Specific End of interrupt to clear in-service bit */
	/* Mask upper 5 bits of int. line register			*/
		if(interrupt_line<8)
			outportb(0x20,0x60|(interrupt_line&0x07));
		else{
			/* Issue master then slave EOI */
			outportb(0xa0,0x60|((interrupt_line-8)&0x07));
			outportb(0x20,0x62);
			}

}


/************************************************************************/
/* SETUP_INT_VECT                                                       */
/*                                                                      */
/* Purpose: 	Install the interrupt vector for the S5933 interrupt		*/
/*          	handler and reference the previous handler routine.		*/
/* Inputs: 		S5933 Operation registers base address                  	*/
/* Outputs: 	None 																		*/
/************************************************************************/
void setup_int_vect(byte bus_num,byte dev_func)
{
	int mask;

	/* Read the Interrupt Line register to determine the hardware IRQ */
	/* assigned to the S5933, then convert this to a software interrupt */
	/* number to insert the interrupt vector for the S5933 */

	if(read_configuration_byte(bus_num,dev_func,PCI_CS_INTERRUPT_LINE,
		&interrupt_line)==SUCCESSFUL){

		printf("Interrupt Line Register = %d \n",interrupt_line);

		if(interrupt_line != 0xff){
			if(interrupt_line<8){
				int_vector=0x08+interrupt_line;
			}
			else{
				int_vector=0x70+(interrupt_line-8);
			}
		}

	/* Make sure the system 8259 enables the IRQ with OCW1 @ I/O 21h */
	/* for IRQ0-7 or @ I/O A1h for IRQ8-15 */
	if(interrupt_line < 8){
	mask = inportb(0x21);
	mask = mask & ~(1<<interrupt_line);
	outportb(0x21,mask);
	}
	else {
	mask = inportb(0xA1);
	mask = mask & ~(1<<(interrupt_line-8));
	outportb(0xA1,mask);
	}

	/* Save the old interrupt vector */
	oldhandler=getvect(int_vector);

	/* Install the new interrupt vector */
	setvect(int_vector,handler);
	}
}



