// This file contains the declaration for the function ME2600Init
// used to initialise the ME2600 Board and definitions for board
// registers and individual bits which you can use in yourt own 
// programs

// After calling ME2600Init below, p_me2600_port contains the base 
// address for the ME2600 registers, p_me2600_irq contains the irq
// line used by the card and p_plx_port contains the base address
// for the PLX register.
// In order to use the system allocated default values, which you
// should normally do, you should set *p_me2600_port and *p_plx_port
// to zero before calling the function. If you wish to force the board
// to use a particular base address for the ME2600 registers or a 
// particular irq line, you should set the appropriate parameter to the 
// required value before calling the function.

// The return value from the function is one the constants 
// ME2600_NO_ERROR etc. below. A return value other than ME2600_NO_ERROR
// indicates a software or hardware error. 

unsigned int me2600Init(
    unsigned short* p_me2600_port,
    unsigned char* p_me2600_irq,
    unsigned short* p_plx_port,
    unsigned int* p_me_DevID);

// Possible return values from the function ME2600Init .

// Board successfully initialised

#define ME2600_NO_ERROR								0x0000  

// No PCI BIOS found

#define ME2600_ERROR_PCI_BIOS_NOT_PRESENT           0x0001  

// No ME2600 board found  

#define ME2600_ERROR_ME2600_NOT_FOUND               0x0002  

// ME2600 board with 'Memory Mapped' PLX register

#define ME2600_ERROR_PLX_MEMORY_MAPPED              0x0003  

// ME2600 board with 'Memory Mapped' IO registers

#define ME2600_ERROR_ME2600_REGS_MEMORY_MAPPED      0x0004  

// Error executingthe download routine

#define ME2600_ERROR_DOWNLOAD_FAILED                0x0005  


// ME2600 Register Set

// ME2600 Control Register 1

#define ME2600_CONTROL_1						0x0000		// - | W 

#define ME2600_C1_STOP_ADC_CONVERT				0xfffc

#define ME2600_C1_ADC_SW_CONVERT				0x0001

#define ME2600_C1_ADC_COUNTER_CONVERT			0x0002

#define ME2600_C1_SIMULTANEOUS_SAMPLING			0x0010

#define ME2600_C1_SCAN_MODE						0x0020
												
#define ME2600_C1_FIFO_HALF_FULL_INTERRUPT		0x0100
												
#define ME2600_C1_EXTERNAL_INTERRUPT			0x0200
												
#define ME2600_C1_ENABLE_INTERRUPTS				0x8000
												
// ME2600 ADC Start Register					
												
#define ME2600_ADC_START						0x0000		// R | -
												
// ME2600 Control Register 2					
												
#define ME2600_CONTROL_2						0x0002		// - | W 
												
#define ME2600_C2_DAC_BUFFERED					0x0001		 
												
#define ME2600_C2_DAC_ACTIVE					0x0002		 
												
#define ME2600_C2_ENABLE_PORT_A					0x0040
												
#define ME2600_C2_PREPARE_CH_FIFO				0x0200
												
#define ME2600_C2_PREPARE_AD_FIFO				0x0400
												
// ME2600 Status Register						
												
#define ME2600_STATUS							0x0004		// R | - 
												
#define ME2600_S_AD_FIFO_FULL					0x0010
												
#define ME2600_S_AD_FIFO_HALF_FULL				0x0008
												
#define ME2600_S_AD_FIFO_EMPTY					0x0004
												
#define ME2600_RESET_INTERRUPT					0x0004		// - | W 
												
// ME2600 DIO Port A register						
												
#define ME2600_DIO_PORT_A						0x0006		// R | W 
												
// ME2600 DIO Port B register						
												
#define ME2600_DIO_PORT_B						0x0008		// R | W 
												
// ME2600 DIO timer data 0 register						
												
#define ME2600_TIMER_DATA_0						0x000A		// - | W 
												
// ME2600 DIO timer data 1 register						
												
#define ME2600_TIMER_DATA_1						0x000C		// - | W 
												
// ME2600 DIO timer data 2 register						
												
#define ME2600_TIMER_DATA_2						0x000E		// - | W 
												
// ME2600  channel list register						
												
#define ME2600_CHANNEL_LIST						0x0010		// - | W 
												
// ME2600 read AD FIFO register						
												
#define ME2600_READ_AD_FIFO						0x0010		// R | - 
												
// ME2600 DAC control register						
												
#define ME2600_DAC_CONTROL						0x0012		// - | W 
												
// ME2600 DAC control update register						
												
#define ME2600_DAC_CONTROL_UPDATE				0x0012		// R | - 
												
// ME2600 DAC data A register						
												
#define ME2600_DAC_DATA_A						0x0014		// - | W 
												
// ME2600 DAC data B register						
												
#define ME2600_DAC_DATA_B						0x0016		// - | W 
												
// ME2600 DAC data C register						
												
#define ME2600_DAC_DATA_C						0x0018		// - | W 
												
// ME2600 DAC data D register						
												
#define ME2600_DAC_DATA_D						0x001A		// - | W 
												
// Defines for AD gain, polarity and channel mode

#define ME2600_AD_GAIN_1						0x0000
#define ME2600_AD_GAIN_2						0x0010
#define ME2600_AD_GAIN_4						0x0020
#define ME2600_AD_GAIN_8						0x0030

#define ME2600_AD_BIPOLAR						0x0000
#define ME2600_AD_UNIPOLAR						0x0040

#define ME2600_AD_SINGLE_ENDED					0x0000
#define ME2600_AD_DIFFERENTIAL					0x0080

// Defines for DA range

#define ME2600_DA_RANGE_ZERO_PLUS_TEN			0x0000
#define ME2600_DA_RANGE_MINUS_FIVE_PLUS_FIVE	0x0080
#define ME2600_DA_RANGE_MINUS_TEN_PLUS_TEN		0x0880

// PLX Register									
												
#define PLX_INT_STATUS							0x004C		// R | W		

