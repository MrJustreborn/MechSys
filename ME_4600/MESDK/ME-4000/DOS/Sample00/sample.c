/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2000 Meilhaus Elektronik GmbH                                                      */
/*  Author:         kh                                                                                      */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com in special www.amcc.com/TechLib/pcidev.htm)                               */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  The proper hardware connections must be made before the program will function.          */
/*                  See handbook.                                                                           */
/*                  Some input or output signals have to be convert !!                                      */
/*                  This is not a full working application, it should show, how you can determine the       */
/*                  resources and programming some registers                                                */
/*                  For internal reasons we are not in a position to publish the whole register description */
/*                  You can use the samples "as is" Meilhaus Electronic offers no support on this samples   */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    001005  kh      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/


// This example shows the basic steps required to program the ME4000 board
// to sample a single value from an AI channel

// This example was written for BorlandC 3.1 compiler

// You can change the behaviour of this application by changing
// the values of the defines and constants below

// Standard includes
#include <stdio.h> 
#include <conio.h>
#include <dos.h>

// Include-file for register defines and init routine
#include "..\amcc.h"		// Low level PCI Bios routines
#include "..\me4000.h"

// You can force the ME4000 board to use a particular port address or a
// particular interrupt by changing the values for required_ME4000_port
// and required_irq_line below. The value '0' means, in both cases, use
// the default values assigned by the system.
#define REQUIRED_ME4000_PORT						0	// 0 = Use default
#define REQUIRED_IRQ_LINE							0	// 0 = Use default

unsigned short us_ME4000_port	= REQUIRED_ME4000_PORT;
unsigned char uc_irq_line		= REQUIRED_IRQ_LINE;
unsigned short us_plx_port;

void main(void)
{
    unsigned int init_error = ME4000_NO_ERROR;
    FILE *pf;
    int iIdx;

	printf("\n\nprogram description:\n");
	printf("====================\n");
	printf("  * determines base address and irq line\n");
	printf("    (dynamic assigned from PC PCI BIOS)\n");
	printf("  * downloads ME-4000 firmware\n");
	printf("  * creates a text file in the current \n");
	printf("    directory with information of resources\n\n");
	
	pf = fopen(".\\me4kInit.txt","w");
	
	for (iIdx=0; init_error == ME4000_NO_ERROR; iIdx++)
	{
	    init_error = ME4000Init(iIdx, &us_ME4000_port, &uc_irq_line, &us_plx_port);
	    
    	if(init_error != ME4000_NO_ERROR)
    	{
    		printf("board %d not exist or could not initialized (%u)\n", iIdx, init_error);
    		if (pf) printf("board %d not exist or could not initialized (%u)\n", iIdx, init_error);
    	}
    	else
    	{
    	    printf("board %d \n", iIdx);
        	printf("\tIO base address: %4x (hex)\n",      us_plx_port);
        	printf("\tIrq (if needed): %2d   (dec)\n\n",    uc_irq_line);
        	
        	if (pf) fprintf(pf, "board %d \n", iIdx);
        	if (pf) fprintf(pf, "IO base address: %4x (hex)\n",      us_plx_port);
        	if (pf) fprintf(pf, "Irq (if needed): %2d   (dec)\n\n",    uc_irq_line);
    	}
    }
    
    if (pf) fclose(pf);
}

