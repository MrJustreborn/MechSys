/*----------------------------------------------------------------------------
    File: meDefs.h
------------------------------------------------------------------------------

    Meilhaus Electronic GmbH

    Common header file providing #defines to be used in DLL or applications
    which are connected to the 32-Bit driver for ME3000


    Version 0.001:      16.12.97    Adapted from cdr ME3000 driver project
            0.002:      17.12.97    Support of SIO registers added
            0.003:      06.01.98    #defines for Bits of Virtual Model 2 added
            0.500:      08.02.98    Preliminary working version
            1.000:      25.03.98    Release of version 1

-------------------------------------------------------------------------------
    Author: Max Kormaier                                        (c) 1998   MK
-----------------------------------------------------------------------------*/
#ifndef MEDEFS_H
#define MEDEFS_H

    // Thread priority
    //--------------------------------------------------------------------
    #define PRIORITY_HIGH   0x1
    #define PRIORITY_LOW    0x0


    // ADC base clock frequency
    //--------------------------------------------------------------------
    #define ADC_BASE_FREQUENCY_1 3000000.0
    #define ADC_BASE_FREQUENCY_2 2950000.0

    // we support up to ME_MAX_DEVICES boards
    //--------------------------------------------------------------------
    #define ME_MAX_DEVICES  32



    // Defines used for the Serial Interface UART 16C550
    //--------------------------------------------------------------------
    #define SIO_RHR         0x0
    #define SIO_THR         0x0
    #define SIO_IER         0x1
    #define SIO_FCR         0x2
    #define SIO_ISR         0x2
    #define SIO_LCR         0x3
    #define SIO_MCR         0x4
    #define SIO_LSR         0x5
    #define SIO_MSR         0x6
    #define SIO_SPR         0x7

    #define SIO_DLL         0x0
    #define SIO_DLM         0x1

    #define SIO_NO_PARITY   (char) 0x00
    #define SIO_ODD_PARITY  (char) 0x08
    #define SIO_EVEN_PARITY (char) 0x18
    #define SIO_FORCE_ODD   (char) 0x28
    #define SIO_FORCE_EVEN  (char) 0x38

    #define SIO_LEN_7       (char) 0x02
    #define SIO_LEN_8       (char) 0x03

    #define SIO_STOP_1      (char) 0x00
    #define SIO_STOP_2      (char) 0x04

    #define SIO_LATCH_ENA   (char) 0x80

    #define SIO_1200_DIV    (char) 0x60
    #define SIO_2400_DIV    (char) 0x30
    #define SIO_4800_DIV    (char) 0x18
    #define SIO_9600_DIV    (char) 0x0C
    #define SIO_19200_DIV   (char) 0x06
    #define SIO_38400_DIV   (char) 0x03
    #define SIO_57600_DIV   (char) 0x02
    #define SIO_115200_DIV  (char) 0x01
    #define SIO_250000_DIV  (char) 0x0

    #define SIO_LOOPBACK    (char) 0x10

    #define SIO_ERROR       (char) 0xE

    #define SIO_POLLING     (char) 0x1
    #define SIO_INTERRUPT   (char) 0x2

    #define SIO_OVERWRITE   (char) 0x20

    #define SIO_RS485_HALF_DUPLEX   (char) 0x10



    // Interrupt sources
    //--------------------------------------------------------------------
    #define IS_ADFIFO_HALF          0x0100
    #define IS_EXTERN               0x0200
    #define IS_CHANLIST_READY       0x0400
    #define IS_COUNTER_A            0x0800
    #define IS_COUNTER_B            0x1000
    #define IS_UART                 0x2000
    #define IS_DAFIFO_HALF          0x4000


    // PWM
    //--------------------------------------------------------------------
    #define PWM3000_NORMAL              0x1
    #define PWM3000_INVERTED            0x2

    // Analog Output Ranges
    //--------------------------------------------------------------------
    #define AO3000_PLUS_10              0x1     //   0V ..  10V
    #define AO3000_MINUS_5              0x4     // - 5V .. + 5V
    #define AO3000_MINUS_10             0x8     // -10V .. +10V

    // Analog Output Modes
    //--------------------------------------------------------------------
    #define AO3000_BUFFERED             0x1
    #define AO3000_TRANSPARENT          0x2

    // Analog Output Trigger Modes
    //--------------------------------------------------------------------
    #define AO3000_TRIGGER_TIMER        0x01
    #define AO3000_TRIGGER_EXT_LOW      0x02
    #define AO3000_TRIGGER_EXT_HIGH     0x04

    // Analog Input Modes and Ranges
    //--------------------------------------------------------------------
    #define AI3000_DIFFERENTIAL         0x80
    #define AI3000_SINGLE_ENDED         0x00

    #define AI3000_PLUS_10              0x40
    #define AI3000_PLUS_5               0x50
    #define AI3000_PLUS_2               0x60
    #define AI3000_PLUS_1               0x70
    #define AI3000_MINUS_10             0x00
    #define AI3000_MINUS_5              0x10
    #define AI3000_MINUS_2              0x20
    #define AI3000_MINUS_1              0x30


    // Analog Input Trigger Modes
    //--------------------------------------------------------------------
    #define AI3000_TRIGGER_TIMER    0x01
    #define AI3000_TRIGGER_EXT_LOW  0x02
    #define AI3000_TRIGGER_EXT_HIGH 0x04
    #define AI3000_TRIGGER_CONTI    0x08

    // AO Modes
    //--------------------------------------------------------------------
    #define AO3000_INFINITE             0xFFFFFFFF
    #define AO3000_INTERRUPT            0x00000001
    #define AO3000_POLLING              0x00000002


    // AI Modes
    //--------------------------------------------------------------------
    #define AI3000_INFINITE             0xFFFFFFFF
    #define AI3000_INTERRUPT            0x00000001
    #define AI3000_POLLING              0x00000002
    #define AI3000_CHANLIST_INTERRUPT   0x00000004
    #define AI3000_ADFIFO_INTERRUPT     0x00000008
    #define AI3000_ENABLE               0x00000010
    #define AI3000_DISABLE              0x00000020
    #define AI3000_SCAN_TO_DISK         0x00010000
    #define AI3000_SCAN_INFINITE        0x00020000

    // DIO
    //--------------------------------------------------------------------
    #define LOW_BYTE                0x0
    #define HIGH_BYTE               0x1

    #define MEINPUT                 0x0
    #define MEOUTPUT                0x1

    #define PORTA                   0x0
    #define PORTB                   0x1


    // Counter
    //--------------------------------------------------------------------
    #define COUNTER3000_A           0x1
    #define COUNTER3000_B           0x2
    #define COUNTER3000_ENABLE      0x4
    #define COUNTER3000_DISABLE     0x8

    // Signal forms for the function ME3000AOGenerateSignal
    //--------------------------------------------------------------------
    #define AO_SQUARE_WAVE          0
    #define AO_TRIANGLE             1
    #define AO_SAW_TOOTH            2
    #define AO_SINUS                3


    // Some helper defines
    //--------------------------------------------------------------------
    #define SETBIT(x) (1 << (x))

    // 1 / 204.8 = 0.0048828125
    //#define ADC_TO_VOLT(x) ((x)>=0x800)?(double)(x)*0.0048828125-20:(double)(x)*0.0048828125

    // 2 / 4096 = 0.00048828125
    //#define ADC_TO_VOLT(x,y,z) (double)((x)^0x800)*0.00048828125*(y)-(z)
    #define ADC_TO_VOLT(x,y,z) (double)(x)*0.00048828125*(y)-(z)

    #define MAKE_CHANNELLIST(ch,range) ((ch) & 0x0F) + ((range) & 0xF0)
    #define MAKE_DACFIFOENTRY(ch,val) ((ch) <<12) + ((val) & 0xFFF)





    /* imported from COMMON.H   */


    // API structure for board infos
    //--------------------------------------------------------------------
    typedef struct _ME_PLX9050_INFO 
    {                               //  offset  comment
        USHORT  VendorID;           //  0x00    vendor identifier
        USHORT  DeviceID;           //  0x02    device identifier
        USHORT  Command;            //  0x04    command register
        USHORT  Status;             //  0x06    status register
        UCHAR   Revision;           //  0x08    revison number
        UCHAR   Class[3];           //  0x09    device class code
        UCHAR   CacheSize;          //  0x0C    size of cache lines
        UCHAR   Latency;            //  0x0D    latency time
        UCHAR   HeaderType;         //  0x0E    header type
        UCHAR   Bist;               //  0x0F    built-in self-test
        ULONG   BaseAddr[6];        //  0x10    base addr. 0-5
        ULONG   Cis;                //  0x28    CIS-pointer (cardbus)
        USHORT  SubVendor;          //  0x2C    subsystem vendor ID
        USHORT  SubSystem;          //  0x2E    subsystem ID
        ULONG   ROMAddr;            //  0x30    base addr. of Extension ROM 
        ULONG   Reserved[2];        //  0x34    
        UCHAR   IRQ;                //  0x3C    number of IRQ
        UCHAR   IPin;               //  0x3D    pin number of IRQ
        UCHAR   Min_Gnt;            //  0x3E    min. burst in 1/4 micro secs.
        UCHAR   Max_Lat;            //  0x3F    max. latency in 1/4 micro secs.
        UCHAR   Device[192];        //  0x40    device-specific data
    } ME_PLX9050_INFO, *PME_PLX9050_INFO;   // total size: 0x100


    // 
    //--------------------------------------------------------------------
    typedef void (_stdcall *PVOID_PROC)  (void);
    typedef void (_stdcall *P_1_PROC)    (short*, int);
    typedef void (_stdcall *PSHORT_PROC) (short*);

    // SIO register structure 
    //---------------------------------------------------------------------
    typedef struct _ME3000_SIO_REGS
    {
        char    RHR;        // Reveive Register
        char    IER;        // Interrupt Enable Register
        char    FCR;        // FIFI Control Register 
        char    LCR;        // Line Control Register
        char    MCR;        // Modem Control Register
        char    LSR;        // Line Status Register
        char    MSR;        // Modem Satus Register
        char    SPR;        // ScatchPad Register
    } ME3000_SIO_REGS, *PME3000_SIO_REGS;

    // SIO communication structure 
    //---------------------------------------------------------------------
    typedef struct _ME3000_SIO
    {
        int     Mode;
        int     InBufferSize;
        int     InBufferCount;
        int     InBufferReadPointer;
        int     InBufferWritePointer;
        int     InBufferOverwrite;
        int     InBufferOverwriteCount;
        int     InStop;
        int     InError;

        int     OutBufferSize;
        int     OutBufferCount;
        int     OutBufferEndPointer;
        int     OutError;

        char    *pInBuffer;     
        char    *pOutBuffer;    
    } ME3000_SIO, *PME3000_SIO;


    // Driver Board Info structure 
    //---------------------------------------------------------------------
    typedef struct _ME3000_BOARD_INFO
    {
        // Take care of 4-bytes-alignment: Add padding bytes if necessary!
        ULONG   ErrorCode;      // Driver error code
        ULONG   NoOfBoards;     // No. of boards detected by DriverEntry
        ULONG   DeviceNumber;   // Number of selected board
        ULONG   Word;           // General purpose debug value
        ULONG   RTPhysAddr;     // Phys. address of PLX RT registers
        ULONG   XilinxPhysAddr; // Phys. address of XILINX
        ULONG   SioPhysAddr;    // Phys. address of SIO
        ULONG   MEVECModel;     // Actually loaded Firmware Model     
        ULONG   FileStatus;     // Status after reading Firmware file
        ULONG   FileLength;     // Length of Firmware file
        ULONG   FileVersion;    // Version of Firmware file
        ULONG   FileDate;       // Date of Firmware file
        ULONG   ADCFifo;        // Size of ADC FIFO
        ULONG   DACFifo;        // Size of DAC FIFO
        ULONG   ChanListFifo;   // Size of channel list FIFO
        ULONG   SerialNumber;   
        ULONG   Date;           // Date when eeprom was written
        ULONG   SlotNumber;     // PCI slot number
    } ME3000_BOARD_INFO, *PME3000_BOARD_INFO;


    // Driver Interrupt Service Info structure 
    //---------------------------------------------------------------------
    typedef struct _ME3000_ISR
    {
        // Take care of 4-bytes-alignment: Add padding bytes if necessary!
        ULONG   ISR;            
        ULONG   AdcFifo;            
        ULONG   ChanList;   
        ULONG   Extern;     
        ULONG   CountA;     
        ULONG   CountB;     
        ULONG   UART;       
        ULONG   DacFifo;        

    } ME3000_ISR, *PME3000_ISR;



    // Transfer structure DLL->Driver
    //---------------------------------------------------------------------
    typedef struct _ME3000_TRANSFER_OBJECT
    {
        // Take care of 4-bytes-alignment: Add padding bytes if necessary!
        int     iBoardNumber;
        USHORT  usRegister;
        USHORT  usBits;
        USHORT  usMode;
        USHORT  usControl1;
        USHORT  usControl2;
        USHORT  usControl3;
        ULONG   ulValue;            
        ULONG   ulSize;         
        ULONG   ulBlocks;           
        ULONG   ulInterrupt;            
        ULONG   ulScanToDisk;
        ULONG   ulFileNameLength;
        char    FileName[256];
    } ME3000_TRANSFER_OBJECT, *PME3000_TRANSFER_OBJECT;
    

    // Control register debug structure 
    //---------------------------------------------------------------------
    typedef struct _ME3000_DRIVER_STATUS
    {
        // Take care of 4-bytes-alignment: Add padding bytes if necessary!
        USHORT  usControl1;
        USHORT  usControl2;
        USHORT  usControl3;
        USHORT  usIRQMask;
        USHORT  usISRMask;
        USHORT  usStatus;
        USHORT  usDACStatus;
        USHORT  usPadding;
        ULONG   ulDebugWord;
    } ME3000_DRIVER_STATUS, *PME3000_DRIVER_STATUS;
#endif
