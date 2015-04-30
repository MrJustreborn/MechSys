// This file contains the declaration for the function ME1400Init
// used to initialise the ME1400 Board and definitions for board
// registers and individual bits which you can use in yourt own 
// programs

// After calling ME1400Init below, p_me1400_port contains the base 
// address for the ME1400 registers, p_me1400_irq contains the irq
// line used by the card and p_plx_port contains the base address
// for the PLX register.
// In order to use the system allocated default values, which you
// should normally do, you should set *p_me1400_port and *p_plx_port
// to zero before calling the function. If you wish to force the board
// to use a particular base address for the ME1400 registers or a 
// particular irq line, you should set the appropriate parameter to the 
// required value before calling the function.

// The return value from the function is one the constants 
// ME1400_NO_ERROR etc. below. A return value other than ME1400_NO_ERROR
// indicates a software or hardware error. 

unsigned int me1400Init(
                        unsigned short* p_me1400_port, 
                        unsigned char* p_me1400_irq, 
                        unsigned short* p_plx_port, 
                        unsigned int* p_me1400_DevID);

// Possible return values from the function ME1400Init .

// Board successfully initialised
#define ME1400_NO_ERROR								0x0000  

// No PCI BIOS found
#define ME1400_ERROR_PCI_BIOS_NOT_PRESENT           0x0001  

// No ME1400 board found  
#define ME1400_ERROR_ME1400_NOT_FOUND               0x0002  

// ME1400 board with 'Memory Mapped' PLX register
#define ME1400_ERROR_PLX_MEMORY_MAPPED              0x0003  

// ME1400 board with 'Memory Mapped' IO registers
#define ME1400_ERROR_ME1400_REGS_MEMORY_MAPPED      0x0004  


// ME1400 Register Set
#define ME1400_S_PORT_A						    0x0000
#define ME1400_S_PORT_B						    0x0001
#define ME1400_S_PORT_C						    0x0002
#define ME1400_S_PORT_CTRL					    0x0003
#define ME1400_A_TIMER_0						0x0004
#define ME1400_A_TIMER_1						0x0005
#define ME1400_A_TIMER_2						0x0006
#define ME1400_A_TIMER_CTRL					    0x0007
#define ME1400_B_PORT_A						    0x0008
#define ME1400_B_PORT_B						    0x0009
#define ME1400_B_PORT_C						    0x000A
#define ME1400_B_PORT_CTRL					    0x000B
#define ME1400_B_TIMER_0						0x000C
#define ME1400_B_TIMER_1						0x000D
#define ME1400_B_TIMER_2						0x000E
#define ME1400_B_TIMER_CTRL					    0x000F
#define ME1400_A_MODE					        0x0010
#define ME1400_A_IRQ_CLK					    0x0011


#define ME1400_PORT_CTRL_XXX				0xfffc
//....
#define ME1400_TIMER_CTRL_XXX				0x0001
//....

#define ME1400_MODE_TMR_A_1MHZ			0x00
#define ME1400_MODE_TMR_A_10MHZ			0x80
#define ME1400_MODE_TMR_A_SUBD_CLC0		0x00    // Source is 
#define ME1400_MODE_TMR_A_CLK_CLK0		0x40
#define ME1400_MODE_TMR_A_SUBD_CLC1		0x00    // Source is 
#define ME1400_MODE_TMR_A_CLK0_CLK1		0x20
#define ME1400_MODE_TMR_A_SUBD_CLC2		0x00    // Source is 
#define ME1400_MODE_TMR_A_CLK1_CLK2		0x10
#define ME1400_MODE_TMR_B_1MHZ			0x00
#define ME1400_MODE_TMR_B_10MHZ			0x08
#define ME1400_MODE_TMR_B_SUBD_CLC0		0x00    // Source is 
#define ME1400_MODE_TMR_B_CLK_CLK0		0x04
#define ME1400_MODE_TMR_B_SUBD_CLC1		0x00    // Source is 
#define ME1400_MODE_TMR_B_CLK0_CLK1		0x02
#define ME1400_MODE_TMR_B_SUBD_CLC2		0x00    // Source is 
#define ME1400_MODE_TMR_B_CLK1_CLK2		0x01

#define ME1400_IRQ_CLK_IRQ_RESET	    0x00
#define ME1400_IRQ_CLK_IRQ_ENABLE	    0x02
#define ME1400_IRQ_CLK_IRQ_IN	        0x00
#define ME1400_IRQ_CLK_CLK_OUT	        0x01



												
// PLX Register									
#define PLX_INT_STATUS							0x004C		// R | W		

