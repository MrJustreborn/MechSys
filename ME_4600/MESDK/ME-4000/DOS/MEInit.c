// This file contains the implementation of the function ME4000Init used to
// initialise the ME4000 board. Normally you can use this function unchanged 
// in your own applications.

// This code was wriiten for BorlandC 3.1 compiler

// For an explanation of the parameters passed to the routine, please see 
// the file ME4000.h

// Comment the following line out if you do not wish to see diagnostic
// output on the screen.

#define _ME4000_DEBUG

// Standard includes

#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>

// Other includes

#include "..\amcc.h"		// Low level PCI Bios routines
#include "..\me4000.h"		// Error codes

unsigned short ME4000_IDs[] = {	0x4650, 
								0x4660, 
								0x4661, 
								0x4662, 
								0x4663, 
								0x4670, 
								0x4671, 
								0x4672, 
								0x4673, 
								0x4680, 
								0x4681, 
								0x4682, 
								0x4683	};

unsigned int ME4000Init(int iBoardNo, unsigned short* p_ME4000_port, unsigned char* p_ME4000_irq, unsigned short* p_plx_port)
{
	byte b_bus_no;
	byte b_dev_fct;

    dword i;

	unsigned long ul_file_length;

    unsigned short us_cfgreg;
    
	unsigned char uc_mask;

	unsigned short* p_download_port;

	unsigned short us_reg_icr; 

	unsigned long ul_reg_icr; 

	FILE* p_firmware_file;

	int amcc_result = SUCCESSFUL;
	
	int i_board_found = 0;

	int index_board_id;

	unsigned long firmware_bytes;

	char line[50];

    char digit[10] = "0x00";

	int b_done = 0;

	/*--- Look for a valid PCI BIOS -----------------------------*/
    
	amcc_result = pci_bios_present(NULL,NULL,NULL);

	if(amcc_result != SUCCESSFUL)
    {
#ifdef _ME4000_DEBUG
		
		printf("Error - PCI Bios not present\n");

#endif
		
        return(ME4000_ERROR_PCI_BIOS_NOT_PRESENT);
    }

    /*--- Look for the Meilhaus ME-4000 board -----------------*/

	for(index_board_id = 0; index_board_id < sizeof(ME4000_IDs) / sizeof(unsigned short); index_board_id++)
	{
		amcc_result = find_pci_device(	ME4000_IDs[index_board_id],		// Device ID - ME4000 Board
										0x1402,							// Vendor ID - Meilhaus Electronic
										iBoardNo,					    // Device index, we are looking for the FIRST ME4000 device
										&b_bus_no,						// Bus number returned here
										&b_dev_fct					);	// Slot (device) and function number returned here

		if(amcc_result == SUCCESSFUL)
		{
			i_board_found = 1;

			break;
		}
	}

	if(i_board_found == 0)
	{
#ifdef _ME4000_DEBUG
		
		printf("Error - No ME4000 Board Found\n");

#endif
		
		return(ME4000_ERROR_ME4000_NOT_FOUND);
	}
									
	// Read base address 1, this is the PLX base register
	
	read_configuration_word(b_bus_no,						// Bus number
							b_dev_fct,						// Slot and function number
							PCI_CS_BASE_ADDRESS_1,			// We read base address 1
							p_plx_port					);	// Port address returned here

#ifdef _ME4000_DEBUG
		
		printf("Base address 1: 0x%04X\n", *p_plx_port);

#endif
		
 	*p_plx_port&= 0xFFFC;

#ifdef _ME4000_DEBUG
		
	printf("PLX Port: 0x%04X\n", *p_plx_port);

#endif
		
	if(*p_ME4000_port != 0)
	{
		// *p_ME4000_port was not zero, this means the user wishes to force the
		// ME4000 board to use a given base address. We write the required value
		// to base address 2 (ME4000 base register).
		
		write_configuration_word(b_bus_no,					// Bus number
								b_dev_fct,					// Slot and function number
								PCI_CS_BASE_ADDRESS_2,		// We write base address 1
								*p_ME4000_port			);	// New base address
	}


	// Read base address 2, this is the ME4000 base register
	
	read_configuration_word(b_bus_no,					// Bus number
							b_dev_fct,					// Slot and function number
							PCI_CS_BASE_ADDRESS_2,		// We read base address 1
							p_ME4000_port			);	// Port address returned here

#ifdef _ME4000_DEBUG
		
		printf("Base address 2: 0x%04X\n", *p_ME4000_port);

#endif
		

 	*p_ME4000_port&= 0xFFFC;

#ifdef _ME4000_DEBUG
		
	printf("ME4000 Port: 0x%04X\n", *p_ME4000_port);

#endif
		
	// Read base address 5, this is the download base register
	
	read_configuration_word(b_bus_no,					// Bus number
							b_dev_fct,					// Slot and function number
							PCI_CS_BASE_ADDRESS_5,		// We read base address 1
							p_download_port			);	// Port address returned here

#ifdef _ME4000_DEBUG
		
		printf("Base address 5: 0x%04X\n", *p_download_port);

#endif
		

 	*p_download_port&= 0xFFFC;

#ifdef _ME4000_DEBUG
		
	printf("Download Port: 0x%04X\n", *p_download_port);

#endif
		
	if(*p_ME4000_irq != 0)
	{
		// *p_ME4000_irq was not zero, this means the user wishes to force the
		// ME4000 board to use a given irq line. We write the required value
		// to PCI_CS_INTERRUPT_LINE in the PCI configuration space (ME4000 base register).
		
		write_configuration_byte(	b_bus_no,					// Bus number
									b_dev_fct,					// Slot and function number
									PCI_CS_INTERRUPT_LINE,		// We write the interrupt line number
									*p_ME4000_irq			);	// New interrupt line number
	}

	// Read from offset PCI_CS_INTERRUPT_LINE in the PCI configuration space, this is 
	// the ME4000 irq line.
	
	read_configuration_byte(b_bus_no,					// Bus number
							b_dev_fct,					// Slot and function number
				            PCI_CS_INTERRUPT_LINE,		// We read the interrupt line number
							p_ME4000_irq			);	// Interrupt line number returned here

#ifdef _ME4000_DEBUG
		
	printf("ME4000 IRQ: %d\n", *p_ME4000_irq);

#endif
		
	/*--- Download ---*/

	outport(*p_plx_port + PLX_ISR_REG, 0x0010);

	/* Set /CS and /WRITE of the Xilinx */
	us_reg_icr = inport(*p_plx_port + PLX_ICR_REG); 
	us_reg_icr|= 0x0100;
	outport(*p_plx_port + PLX_ICR_REG, us_reg_icr );
  
	/* Init Xilinx with CS1 */
	inportb(*p_download_port + 0xC8);

    delay(3);       // at least this delay is important

	/* Check if /INIT pin is set */
	if( ( inportb(*p_plx_port + PLX_ISR_REG) & 0x20) != 0x20 )
	{
#ifdef _ME4000_DEBUG
		
		printf("Download error - Cannot initialise XILINX\n");

#endif
		
		return(ME4000_ERROR_DOWNLOAD_FAILED);
	}

	/* Reset /CS and /WRITE of the Xilinx */
	us_reg_icr = inport(*p_plx_port + PLX_ICR_REG); 
	us_reg_icr&= ~0x0100;
	outport(*p_plx_port + PLX_ICR_REG, us_reg_icr );

	p_firmware_file = fopen("me4000.stp", "rt");

	if(p_firmware_file == NULL)
	{
#ifdef _ME4000_DEBUG
		
		printf("Download error - Cannot open me4000.stp\n");

#endif
		
		return(ME4000_ERROR_DOWNLOAD_FAILED);
	}

	firmware_bytes = 0;
	
	b_done = 0;
    
    printf("\n");
	while( (!b_done)&&(fgets(line, 40, p_firmware_file) ) )
    {
        {
            static long lCnt = 0;
            lCnt++;
            if ((lCnt%4)== 3) printf("download...  \\\r");
            if ((lCnt%4)== 2) printf("download...  |\r");
            if ((lCnt%4)== 1) printf("download...  /\r");
            if ((lCnt%4)== 0) printf("download...  -\r");
        }

        // convert line into binary
        for(i=0; i<(strlen(line)/2); i++)
        {
            digit[2] = line[2 * i];
            digit[3] = line[2 * i + 1];

			outportb( *p_download_port, strtol(digit, NULL, 16) );

			++firmware_bytes;
    
			/* Check if BUSY flag is low */
			if( ( inportb(*p_plx_port + PLX_ICR_REG) & 0x20) == 0x20 )
			{
	#ifdef _ME4000_DEBUG
			
				printf("Download error - XILINX busy\n");

	#endif
			
				return(ME4000_ERROR_DOWNLOAD_FAILED);
			}

			/* If DONE is high, programming is complete */
			if( ( inportb(*p_plx_port + PLX_ICR_REG) & 0x04) == 0x04 )
			{
	#ifdef _ME4000_DEBUG
			
				printf("Download complete after %lu bytes\n", firmware_bytes);

	#endif
			
				b_done = 1;
				
				break;
			}
		}
	}

	fclose(p_firmware_file);

#ifdef _ME4000_DEBUG
		
	/*printf("Download complete - %lu bytes\n\n", firmware_bytes);*/

#endif
		
	/* If done flag is NOT high download was NOT successful */
	if( ( inportb(*p_plx_port + PLX_ICR_REG) & 0x04) != 0x04 )
	{
#ifdef _ME4000_DEBUG
		
		printf("Error downloading\n\n");

#endif
		
		return(ME4000_ERROR_DOWNLOAD_FAILED);
	}
  
	/* Set /CS and /WRITE of the Xilinx */
	us_reg_icr = inport(*p_plx_port + PLX_ICR_REG); 
	us_reg_icr|= 0x0100;
	outport(*p_plx_port + PLX_ICR_REG, us_reg_icr );


	//--- reset board -----
    
   /* Make a hardware reset */
	ul_reg_icr = inpd(*p_plx_port + PLX_ICR_REG); 
	ul_reg_icr|= 0x40000000;
	outpd(*p_plx_port + PLX_ICR_REG, ul_reg_icr );
	ul_reg_icr&= ~0x40000000;
	outpd(*p_plx_port + PLX_ICR_REG, ul_reg_icr );

	// Reset all bits in AI control register
	
	outpd(*p_ME4000_port + ME4000_AI_CTRL_REG, 0x00000000);

   /* 0x7FFF to the DACs means an output voltage of 0V */
	outpd(*p_ME4000_port + ME4000_AO_SVAL_0_REG, 0x7FFF );
	outpd(*p_ME4000_port + ME4000_AO_SVAL_1_REG, 0x7FFF );
	outpd(*p_ME4000_port + ME4000_AO_SVAL_2_REG, 0x7FFF );
	outpd(*p_ME4000_port + ME4000_AO_SVAL_3_REG, 0x7FFF );

   /* Enable interrupts on the INT1 on the PLX */
	outpd(*p_plx_port + PLX_ISR_REG, PLX_ISR_PCI_ENABLE | PLX_ISR_I1_POLARITY | PLX_ISR_I1_ENABLE );

	// Make sure the system 8259 enables the IRQ with OCW1 @ I/O 21h 
	// for IRQ0-7 or @ I/O A1h for IRQ8-15 

	if(*p_ME4000_irq < 8)
    {
	    uc_mask = inportb(0x21);
	    
		uc_mask = uc_mask & ~(1 << *p_ME4000_irq);
	    
		outportb(0x21, uc_mask);
	}
	else 
    {
	    uc_mask = inportb(0xA1);

		uc_mask = uc_mask & ~( 1 << (*p_ME4000_irq - 8) );
	    
		outportb(0xA1, uc_mask);
	}

	// Return no error
	
	return(ME4000_NO_ERROR);
}

