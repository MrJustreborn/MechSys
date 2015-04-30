// This file contains the declaration for the function ME4000Init
// used to initialise the ME4000 Board and definitions for board
// registers and individual bits which you can use in yourt own 
// programs

// After calling ME4000Init below, p_ME4000_port contains the base 
// address for the ME4000 registers, p_ME4000_irq contains the irq
// line used by the card and p_plx_port contains the base address
// for the PLX register.
// In order to use the system allocated default values, which you
// should normally do, you should set *p_ME4000_port and *p_plx_port
// to zero before calling the function. If you wish to force the board
// to use a particular base address for the ME4000 registers or a 
// particular irq line, you should set the appropriate parameter to the 
// required value before calling the function.

// The return value from the function is one the constants 
// ME4000_NO_ERROR etc. below. A return value other than ME4000_NO_ERROR
// indicates a software or hardware error. 

unsigned int ME4000Init(int iBoardNo, unsigned short* p_ME4000_port, unsigned char* p_ME4000_irq, unsigned short* p_plx_port);

// Possible return values from the function ME4000Init .

// Board successfully initialised

#define ME4000_NO_ERROR								0x0000  

// No PCI BIOS found

#define ME4000_ERROR_PCI_BIOS_NOT_PRESENT           0x0001  

// No ME4000 board found  

#define ME4000_ERROR_ME4000_NOT_FOUND               0x0002  

// ME4000 board with 'Memory Mapped' PLX register

#define ME4000_ERROR_PLX_MEMORY_MAPPED              0x0003  

// ME4000 board with 'Memory Mapped' IO registers

#define ME4000_ERROR_ME4000_REGS_MEMORY_MAPPED      0x0004  

// Error executingthe download routine

#define ME4000_ERROR_DOWNLOAD_FAILED                0x0005  

// ME4000 registers and individual bit definitions

#define ME4000_AO_CTRL_0_REG				0x00  // R/W

	#define ME4000_AO_CTRL_X_MODE_MASK					0x00000003 	 // Bits 0 & 1 determine the mode
	#define ME4000_AO_CTRL_X_MODE_SINGLE				0x00000000
	#define ME4000_AO_CTRL_X_MODE_WRAPAROUND			0x00000001	
	#define ME4000_AO_CTRL_X_MODE_CONTINUOUS			0x00000002	
	#define ME4000_AO_CTRL_X_STOP						0x00000004
	#define ME4000_AO_CTRL_X_ENABLE_FIFO				0x00000008
	#define ME4000_AO_CTRL_X_ENABLE_EX_TRIG				0x00000010
	#define ME4000_AO_CTRL_X_EX_TRIG_FALLING			0x00000020
//	Not used											0x00000040
	#define ME4000_AO_CTRL_X_IMMEDIATE_STOP				0x00000080
	#define ME4000_AO_CTRL_X_ENABLE_DIO					0x00000100
	#define ME4000_AO_CTRL_X_ENABLE_IRQ					0x00000200
	#define ME4000_AO_CTRL_X_RESET_IRQ					0x00000400

 
#define ME4000_AO_STAT_0_REG				0x04  // R/_

	#define ME4000_AO_STATUS_X_FIFO_FSM_ACTIVE_FLAG		0x00000001	

	#define ME4000_AO_STATUS_X_FIFO_NOT_EMPTY_FLAG		0x00000002	// 0 --> FIFO empty
																	// 1 --> FIFO NOT empty

	#define ME4000_AO_STATUS_X_FIFO_NOT_HALF_FULL_FLAG	0x00000004	// 0 --> FIFO half full
																	// 1 --> FIFO NOT half full

	#define ME4000_AO_STATUS_X_FIFO_NOT_FULL_FLAG		0x08000008	// 0 --> FIFO full
																	// 1 --> FIFO NOT full


#define ME4000_AO_FIFO_0_REG				0x08  // _/W
#define ME4000_AO_SVAL_0_REG				0x0C  // _/W	// Mode Single
#define ME4000_AO_START_0_REG				0x0C  // _/W	// Mode Wraparound or Continuous
#define ME4000_AO_TIME_0_REG				0x10  // _/W

#define ME4000_AO_CTRL_1_REG				0x18  // R/W 
#define ME4000_AO_STAT_1_REG				0x1C  // R/_
#define ME4000_AO_FIFO_1_REG				0x20  // _/W
#define ME4000_AO_SVAL_1_REG				0x24  // _/W	// Mode Single
#define ME4000_AO_START_1_REG				0x24  // _/W	// Mode Wraparound or Continuous
#define ME4000_AO_TIME_1_REG				0x28  // _/W

#define ME4000_AO_CTRL_2_REG				0x30  // R/W 
#define ME4000_AO_STAT_2_REG				0x34  // R/_
#define ME4000_AO_FIFO_2_REG				0x38  // _/W
#define ME4000_AO_SVAL_2_REG				0x3C  // _/W	// Mode Single
#define ME4000_AO_START_2_REG				0x3C  // _/W	// Mode Wraparound or Continuous
#define ME4000_AO_TIME_2_REG				0x40  // _/W

#define ME4000_AO_CTRL_3_REG				0x48  // R/W 
#define ME4000_AO_STAT_3_REG				0x4C  // R/_
#define ME4000_AO_FIFO_3_REG				0x50  // _/W
#define ME4000_AO_SVAL_3_REG				0x54  // _/W	// Mode Single
#define ME4000_AO_START_3_REG				0x54  // _/W	// Mode Wraparound or Continuous
#define ME4000_AO_TIME_3_REG				0x58  // _/W

// AI control register
#define ME4000_AI_CTRL_REG					0x74  // R/W

    // Bit definitions for AI control register
	#define ME4000_AI_CTRL_MODE_MASK					0x00000007	// Bits 0, 1 & 2 determine the mode

	#define ME4000_AI_CTRL_MODE_A						0x00000000	
	#define ME4000_AI_CTRL_MODE_B						0x00000001	
	#define ME4000_AI_CTRL_MODE_C						0x00000002	
	#define ME4000_AI_CTRL_MODE_D						0x00000003	
	#define ME4000_AI_CTRL_MODE_E						0x00000004	

	#define ME4000_AI_CTRL_SAMPLE_AND_HOLD				0x00000008	

	#define ME4000_AI_CTRL_STOP_ALL						0x00000010	

	#define ME4000_AI_CTRL_STOP_CHANNEL					0x00000020	

	#define ME4000_AI_CTRL_CHAN_FIFO_ENABLE				0x00000040	// 0 --> Clear FIFO
																	// 1 --> Enable FIFO	

	#define ME4000_AI_CTRL_DATA_FIFO_ENABLE				0x00000080	// 0 --> Clear FIFO
																	// 1 --> Enable FIFO	

	#define ME4000_AI_CTRL_FULL_SCALE					0x00000100	

	#define ME4000_AI_CTRL_OFFSET						0x00000200	

	#define ME4000_AI_CTRL_EXT_TRIG_ANALOG				0x00000400	

	#define ME4000_AI_CTRL_EXT_TRIG_ENABLE				0x00000800	

	#define ME4000_AI_CTRL_EXT_TRIG_EDGE_HL				0x00001000	

	#define ME4000_AI_CTRL_EXT_IRQ_ENABLE				0x00002000	

	#define ME4000_AI_CTRL_EXT_IRQ_RESET				0x00004000	

	#define ME4000_AI_CTRL_LAST_ENTRY_IRQ_ENABLE		0x00008000	

	#define ME4000_AI_CTRL_LAST_ENTRY_IRQ_RESET			0x00010000	

	#define ME4000_AI_CTRL_DATA_FIFO_HF_ENABLE_IRQ		0x00020000	

	#define ME4000_AI_CTRL_DATA_FIFO_HF_RESET_IRQ		0x00040000	

	#define ME4000_AI_CTRL_SAMPLE_CTR_IRQ_ENABLE		0x00080000	

	#define ME4000_AI_CTRL_SAMPLE_CTR_IRQ_RESET			0x00100000	

	#define ME4000_AI_CTRL_SAMPLE_CTR_RELOAD_ENABLE		0x00200000	

	#define ME4000_AI_CTRL_EXT_TRIG_EDGE_BOTH			0x80000000	

// AI status register
#define ME4000_AI_STATUS_REG				0x74  // R/_

    // Bit definitions for AI status register
	#define ME4000_AI_STATUS_FIFO_NOT_EMPTY_FLAG		0x02000000	// 0 --> FIFO empty
																	// 1 --> FIFO NOT empty

	#define ME4000_AI_STATUS_FIFO_NOT_HALF_FULL_FLAG	0x04000000	// 0 --> FIFO half full
																	// 1 --> FIFO NOT half full

	#define ME4000_AI_STATUS_FIFO_NOT_FULL_FLAG			0x08000000	// 0 --> FIFO Full
																	// 1 --> FIFO NOT Full

	#define ME4000_AI_STATUS_FIFO_FSM_ACTIVE_FLAG		0x20000000	

// AI channel list register
#define ME4000_AI_CHANNEL_LIST_REG			0x78	// _/W

    // Bit definitions for AI channel list register
	#define ME4000_AI_CHANNEL_LIST_LAST_ENTRY			0x00000100
	

#define ME4000_AI_DATA_REG					0x7C	// R/_
#define ME4000_AI_CHAN_TIMER_REG			0x80	// _/W
#define ME4000_AI_CHAN_PRE_TIMER_REG		0x84	// _/W
#define ME4000_AI_SCAN_TIMER_LOW_REG		0x88	// _/W
#define ME4000_AI_SCAN_TIMER_HIGH_REG		0x8C	// _/W
#define ME4000_AI_SCAN_PRE_TIMER_LOW_REG	0x90	// _/W
#define ME4000_AI_SCAN_PRE_TIMER_HIGH_REG	0x94	// _/W
#define ME4000_AI_START_REG					0x98	// R/_

// IRQ status register
#define ME4000_IRQ_STATUS_REG				0x9C	// R/_

    // Bit definitions for IRQ status register
	#define ME4000_IRQ_STATUS_EXTERNAL_INT				0x00000001	

	#define ME4000_IRQ_STATUS_AI_LAST_ENTRY				0x00000002	

	#define ME4000_IRQ_STATUS_AI_FIFO_HALF_FULL			0x00000004	

	#define ME4000_IRQ_STATUS_AO_0_HALF_FULL			0x00000008	

	#define ME4000_IRQ_STATUS_AO_1_HALF_FULL			0x00000010	

	#define ME4000_IRQ_STATUS_AO_2_HALF_FULL			0x00000020	

	#define ME4000_IRQ_STATUS_AO_3_HALF_FULL			0x00000040	

	#define ME4000_IRQ_STATUS_AI_SAMPLE_COUNTER			0x00000080	


#define ME4000_SAMPLE_COUNTER_REG			0xC0	// _/W

#define ME4000_FIRMWARE_ID_REG				0xC4	// R/_

	#define ME4000_FIRMWARE_ID_REV_MASK					0x0000000F
	#define ME4000_FIRMWARE_ID_REV_SHIFT				0

	#define ME4000_FIRMWARE_ID_VER_MASK					0x000000F0
	#define ME4000_FIRMWARE_ID_VER_SHIFT				4

	#define ME4000_FIRMWARE_ID_YEAR_MASK				0x000FFF00
	#define ME4000_FIRMWARE_ID_YEAR_SHIFT				8

	#define ME4000_FIRMWARE_ID_MONTH_MASK				0x00F00000
	#define ME4000_FIRMWARE_ID_MONTH_SHIFT				20

	#define ME4000_FIRMWARE_ID_DAY_MASK					0xFF000000
	#define ME4000_FIRMWARE_ID_DAY_SHIFT				24

#define ME4000_DIO_DIR_REG					0xB0	// R/W
#define ME4000_DIO_CTRL_REG					0xB8	// R/W

	#define ME4000_DIO_CTRL_MODE_MASK_0					0x00000003	// Bits 0 & 1 determine the mode
	#define ME4000_DIO_CTRL_MODE_INPUT_0				0x00000000
	#define ME4000_DIO_CTRL_MODE_OUTPUT_0				0x00000001
	#define ME4000_DIO_CTRL_MODE_FIFO_0					0x00000003

	#define ME4000_DIO_CTRL_MODE_MASK_1					0x0000000C	// Bits 2 & 3 determine the mode
	#define ME4000_DIO_CTRL_MODE_INPUT_1				0x00000000
	#define ME4000_DIO_CTRL_MODE_OUTPUT_1				0x00000004
	#define ME4000_DIO_CTRL_MODE_FIFO_1					0x0000000C

	#define ME4000_DIO_CTRL_MODE_MASK_2					0x00000030	// Bits 4 & 5 determine the mode
	#define ME4000_DIO_CTRL_MODE_INPUT_2				0x00000000
	#define ME4000_DIO_CTRL_MODE_OUTPUT_2				0x00000010
	#define ME4000_DIO_CTRL_MODE_FIFO_2					0x00000030

	#define ME4000_DIO_CTRL_MODE_MASK_3					0x000000C0	// Bits 6 & 7 determine the mode
	#define ME4000_DIO_CTRL_MODE_INPUT_3				0x00000000
	#define ME4000_DIO_CTRL_MODE_OUTPUT_3				0x00000040
	#define ME4000_DIO_CTRL_MODE_FIFO_3					0x000000C0

	#define ME4000_DIO_CTRL_FUNCTION_MASK				0x00000300	// Bits 8 & 9 determine the function
	#define ME4000_DIO_CTRL_FUNCTION_BIT_PATTERN		0x00000000
	#define ME4000_DIO_CTRL_MODE_FUNCTION_DEMUX			0x00000100
	#define ME4000_DIO_CTRL_MODE_FUNCTION_MUX			0x00000200

	#define ME4000_DIO_CTRL_FIFO_HIGH_BYTE_0			0x00000400

	#define ME4000_DIO_CTRL_FIFO_HIGH_BYTE_1			0x00000800

	#define ME4000_DIO_CTRL_FIFO_HIGH_BYTE_2			0x00001000

	#define ME4000_DIO_CTRL_FIFO_HIGH_BYTE_3			0x00002000

#define ME4000_DIO_PORT_0_REG				0xA0	// R/W
#define ME4000_DIO_PORT_1_REG				0xA4	// R/W
#define ME4000_DIO_PORT_2_REG				0xA8	// R/W
#define ME4000_DIO_PORT_3_REG				0xAC	// R/W

#define ME4000_AO_LOADSET_REG				0xB4	// R/W

	#define ME4000_AO_LOADSET_HOLD_0					0x00000001
	#define ME4000_AO_LOADSET_HOLD_1					0x00000002
	#define ME4000_AO_LOADSET_HOLD_2					0x00000004
	#define ME4000_AO_LOADSET_HOLD_3					0x00000008

#define ME4000_CNT_COUNTER_0_REG			0x00
#define ME4000_CNT_COUNTER_1_REG			0x01
#define ME4000_CNT_COUNTER_2_REG			0x02
#define ME4000_CNT_CTRL_REG					0x03

#define ME4000_DEMUX_ADJUST_REG				0xBC	// _/W
			#define ME4000_DEMUX_ADJUST_VALUE			0x0000004C	

// PLX registers and individual bit definitions

// PLX interrupt status register
#define PLX_ISR_REG							0x4C

    // Bit definitions for PLX interrupt status register
    #define PLX_ISR_I1_ENABLE							0x01		// Bit 0
    #define PLX_ISR_I1_POLARITY							0x02		// Bit 1
    #define PLX_ISR_I1_STATUS							0x04		// Bit 2
    #define PLX_ISR_I2_ENABLE							0x08		// Bit 3
    #define PLX_ISR_I2_POLARITY							0x10		// Bit 4
    #define PLX_ISR_I2_STATUS							0x20		// Bit 5
    #define PLX_ISR_PCI_ENABLE							0x40		// Bit 6
    #define PLX_ISR_SOFTWARE_IRQ						0x80		// Bit 7

// PLX interrupt control register
#define PLX_ICR_REG							0x50

    // Bit definitions for PLX interrupt control register
	#define PLX_ICR_RESET								0x40000000	// Bit 30

#define ME4000_AI_BIPOLAR_10					0x0000
#define ME4000_AI_BIPOLAR_2_5					0x0040
#define ME4000_AI_UNIPOLAR_10					0x0080
#define ME4000_AI_UNIPOLAR_2_5					0x00C0

#define ME4000_AI_SINGLE_ENDED					0x0000
#define ME4000_AI_DIFFERENTIAL					0x0020

