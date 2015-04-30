(*----------------------------------------------------------------------------
	File: meDefs.pas
------------------------------------------------------------------------------

	Meilhaus Electronic GmbH

	Common header file providing #defines to be used in DLL or applications
	which are connected to the 32-Bit driver

	Version 0.001:	    05.08.98	Adapted from cdr ME3000 driver project

-------------------------------------------------------------------------------
	Author: Wagner Armin (WA)                                (c) 1998   WA
-----------------------------------------------------------------------------*)

unit medefs;

interface

(*Thread priority*)
CONST PRIORITY_HIGH = 1;
CONST PRIORITY_LOW  = 0;

(*ADC base clock frequency*)
CONST ADC_BASE_FREQUENCY_1 = 3000000;
CONST ADC_BASE_FREQUENCY_2 = 2950000;

(*FIFO half full flag is used to read data*)
CONST ADC_FIFO_HALF_SIZE   = 1024;

(*For a first version we support up to 4 me3000 boards*)
CONST ME_MAX_DEVICES = 4;

         (*Define used for the serial interface UART 16c550*)
         CONST SIO_RHR         = $0;
         CONST SIO_THR         = $0;
         CONST SIO_IER         = $1;
         CONST SIO_FCR         = $2;
         CONST SIO_ISR         = $2;
         CONST SIO_LCR         = $3;
         CONST SIO_MCR         = $4;
         CONST SIO_LSR         = $5;
         CONST SIO_MSR         = $6;
         CONST SIO_SPR         = $7;
         CONST SIO_DLL         = $0;
         CONST SIO_DLM         = $0;
         CONST SIO_NO_PARITY   = $0;
         CONST SIO_ODD_PARITY  = $08;
         CONST SIO_EVEN_PARITY = $18;
         CONST SIO_FORCE_ODD   = $28;
         CONST SIO_FORCE_EVEN  = $38;
         CONST SIO_LEN_7       = $02;
         CONST SIO_LEN_8       = $03;
         CONST SIO_STOP_1      = $0;
         CONST SIO_STOP_2      = $04;
         CONST SIO_LATCH_ENA   = $80;
         CONST SIO_1200_DIV    = $60;
         CONST SIO_2400_DIV    = $30;
         CONST SIO_4800_DIV    = $18;
         CONST SIO_9600_DIV    = $0C;
         CONST SIO_19200_DIV   = $06;
         CONST SIO_38400_DIV   = $03;
         CONST SIO_57600_DIV   = $02;
         CONST SIO_115200_DIV  = $01;
         CONST SIO_250000_DIV  = $0;
         CONST SIO_LOOPBACK    = $10;
         CONST SIO_ERROR       = $0e;
         CONST SIO_POLLING     = $01;
         CONST SIO_INTERRUPT   = $02;
         CONST SIO_OVERWRITE   = $20;
         CONST SIO_RS485_HALF_DUPLEX = $10;

         (*Interrupt sources*)
         CONST IS_ADFIFO_HALF        = $0100;
         CONST IS_EXTERN             = $0200;
         CONST IS_CHANLIST_READY     = $0400;
         CONST IS_COUNTER_A          = $0800;
         CONST IS_COUNTER_B          = $1000;
         CONST IS_UART               = $2000;
         CONST IS_DAFIFO_HALF        = $4000;

        (*PWM*)
	CONST PWM3000_NORMAL	 =1;
	CONST PWM3000_INVERTED	 =2;

	// Analog Output Ranges
	//--------------------------------------------------------------------
	CONST AO3000_PLUS_10	=1;     //   0V ..  10V
	CONST AO3000_MINUS_5	=4;     // - 5V .. + 5V
	CONST AO3000_MINUS_10	=8;     // -10V .. +10V

	// Analog Output Modes
	//--------------------------------------------------------------------
	CONST AO3000_BUFFERED	=1;
	CONST AO3000_TRANSPARENT=2;

	// Analog Output Trigger Modes
	//--------------------------------------------------------------------
	CONST AO3000_TRIGGER_TIMER		=01;
	CONST AO3000_TRIGGER_EXT_LOW		=02;
	CONST AO3000_TRIGGER_EXT_HIGH		=04;

	// Analog Input Modes and Ranges
	//--------------------------------------------------------------------
	CONST AI3000_DIFFERENTIAL		=$80;
	CONST AI3000_SINGLE_ENDED		=$00;

	CONST AI3000_PLUS_10			=$40;
	CONST AI3000_PLUS_5			=$50;
	CONST AI3000_PLUS_2			=$60;
	CONST AI3000_PLUS_1			=$70;
	CONST AI3000_MINUS_10			=$00;
	CONST AI3000_MINUS_5			=$10;
	CONST AI3000_MINUS_2			=$20;
	CONST AI3000_MINUS_1			=$30;


	// Analog Input Trigger Modes
	//--------------------------------------------------------------------
	CONST AI3000_TRIGGER_TIMER	=$01;
	CONST AI3000_TRIGGER_EXT_LOW    =$02;
	CONST AI3000_TRIGGER_EXT_HIGH   =$04;
	CONST AI3000_TRIGGER_CONTI	=$08;

	// AO Modes
	//--------------------------------------------------------------------
	CONST AO3000_INFINITE		=$FFFFFFFF;
	CONST AO3000_INTERRUPT		=$00000001;
	CONST AO3000_POLLING		=$00000002;


	// AI Modes
	//--------------------------------------------------------------------
	CONST AI3000_INFINITE			=$FFFFFFFF;
	CONST AI3000_INTERRUPT			=$00000001;
	CONST AI3000_POLLING			=$00000002;
	CONST AI3000_CHANLIST_INTERRUPT	        =$00000004;
	CONST AI3000_ADFIFO_INTERRUPT		=$00000008;
	CONST AI3000_ENABLE			=$00000010;
	CONST AI3000_DISABLE			=$00000020;
	CONST AI3000_SCAN_TO_DISK		=$00010000;
	CONST AI3000_SCAN_INFINITE		=$00020000;

	// DIO
	//--------------------------------------------------------------------
	CONST LOW_BYTE				=$0;
	CONST HIGH_BYTE				=$1;

	CONST MEINPUT				=$0;
	CONST MEOUTPUT				=$1;

	CONST PORTA				=$0;
	CONST PORTB				=$1;


	// Counter
	//--------------------------------------------------------------------
	CONST COUNTER3000_A			=$1;
	CONST COUNTER3000_B			=$2;
	CONST COUNTER3000_ENABLE		=$4;
	CONST COUNTER3000_DISABLE		=$8;


	// Bits of the Control Register 1 of VM1
	//--------------------------------------------------------------------
	CONST VM1_CR1_ENABLE_INT		=$8000;
	CONST VM1_CR1_RESERVED_14		=$4000;
	CONST VM1_CR1_INT_UART			=$2000;
	CONST VM1_CR1_INT_COUNT_B		=$1000;
	CONST VM1_CR1_INT_COUNT_A		=$0800;
	CONST VM1_CR1_INT_CHANLIST_READY	=$0400;
	CONST VM1_CR1_INT_EXTERN		=$0200;
	CONST VM1_CR1_INT_AD_FIFO_HALF	        =$0100;
	CONST VM1_CR1_RESERVED_7		=$0080;
	CONST VM1_CR1_RESERVED_6		=$0040;
	CONST VM1_CR1_SCAN_MODE			=$0020;
	CONST VM1_CR1_SIMULTANEOUS		=$0010;
	CONST VM1_CR1_EXT_TRIGGER_EDGE	        =$0008;
	CONST VM1_CR1_EXT_TRIGGER_MODE	        =$0004;
	CONST VM1_CR1_ADC_MODE_BIT_1		=$0002;
	CONST VM1_CR1_ADC_MODE_BIT_0		=$0001;


	// Bits of the Control Register 2 of VM1
	//--------------------------------------------------------------------
	CONST VM1_CR2_RESERVED_15		=$8000;
	CONST VM1_CR2_RESERVED_14		=$4000;
	CONST VM1_CR2_RESERVED_13		=$2000;
	CONST VM1_CR2_RESERVED_12		=$1000;
	CONST VM1_CR2_RESERVED_11		=$0800;
	CONST VM1_CR2_RESET_AD_FIFO		=$0400;
	CONST VM1_CR2_RESET_CH_FIFO		=$0200;
	CONST VM1_CR2_RESERVED_8		=$0100;
	CONST VM1_CR2_RESET_PORT_B		=$0080;
	CONST VM1_CR2_RESET_PORT_A		=$0040;
	CONST VM1_CR2_RESERVED_5		=$0020;
	CONST VM1_CR2_RESET_COUNT_B		=$0010;
	CONST VM1_CR2_RESET_COUNT_A		=$0008;
	CONST VM1_CR2_RESEREVED			=$0004;
	CONST VM1_CR2_RESET_DAC			=$0002;
	CONST VM1_CR2_DAC_MODE			=$0001;


	// Bits of the Control Register 1 of VM2
	//--------------------------------------------------------------------
	CONST VM2_CR1_INT_DA_FIFO_HALF	        =$4000;

	// Bits of the Control Register 2 of VM2
	//--------------------------------------------------------------------
	CONST VM2_CR2_RESET_DA_FIFO		=$0800;

	// Bits of the Control Register 3 of VM2
	//--------------------------------------------------------------------
	CONST VM2_CR3_RESET_PWM			=$0080;
	CONST VM2_CR3_PWM_INV			=$0040;
	CONST VM2_CR3_RESERVED_5		=$0020;
	CONST VM2_CR3_RESERVED_4		=$0010;
	CONST VM2_CR3_DAC_TRIGGER_EDGE	        =$0008;
	CONST VM2_CR3_DAC_TRIGGER		=$0004;
	CONST VM2_CR3_DAC_MODE_BIT1		=$0002;
	CONST VM2_CR3_DAC_MODE_BIT0		=$0001;

	// Bits of the Status Register of VM1
	//--------------------------------------------------------------------
	CONST VM1_ST_RESERVED_15		=$8000;
	CONST VM1_ST_RESERVED_14		=$4000;
	CONST VM1_ST_INT_UART			=$2000;
	CONST VM1_ST_INT_COUNT_B		=$1000;
	CONST VM1_ST_INT_COUNT_A		=$0800;
	CONST VM1_ST_INT_CHANLIST_READY	        =$0400;
	CONST VM1_ST_INT_EXTERN			=$0200;
	CONST VM1_ST_INT_AD_FIFO_HALF		=$0100;
	CONST VM1_ST_RESERVED_7			=$0080;
	CONST VM1_ST_RESERVED_6			=$0040;
	CONST VM1_ST_RESERVED_5			=$0020;
	CONST VM1_ST_ADC_FIFO_FULL		=$0010;
	CONST VM1_ST_ADC_FIFO_HALFFULL	        =$0008;
	CONST VM1_ST_ADC_FIFO_EMPTY		=$0004;
	CONST VM1_ST_CH_FIFO_FULL		=$0002;
	CONST VM1_ST_ADC_FST_ACTIVE		=$0001;


	// Bits of the Status Register 2 of VM2
	//--------------------------------------------------------------------
	CONST VM2_ST2_DAC_FIFO_FULL		=$0008;
	CONST VM2_ST2_DAC_FIFO_HALFFULL	        =$0004;
	CONST VM2_ST2_DAC_FIFO_EMPTY		=$0002;
	CONST VM2_ST2_DAC_FST_ACTIVE		=$0001;

implementation

end.
