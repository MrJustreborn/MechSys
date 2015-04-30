
typedef unsigned char  BYTE;     /* 8-bit  */
typedef unsigned short WORD;     /* 16-bit */
typedef unsigned long  DWORD;    /* 32-bit */

typedef struct _PCIENTRY
{
    WORD    wVenID;
    WORD    wDevID;
    WORD    wBaseIO;
    WORD    wBasePLX;
    WORD    wIrqLine;
    WORD    wSerialNumberHigh;
    WORD    wSerialNumberLow;
} PCIENTRY;

#define HIGH_BYTE(ax) (ax >> 8)
#define LOW_BYTE(ax) (ax & 0xff)

#define CARRY_FLAG 0x01

/****************************************************************************/
/*   PCI Return Code List                                                   */
/****************************************************************************/
#define SUCCESSFUL               0x00
#define NOT_SUCCESSFUL           0x01


/****************************************************************************/
/*   PCI Functions                                                          */
/****************************************************************************/

#define PCI_FUNCTION_ID           0xb1
#define PCI_BIOS_PRESENT          0x01
#define FIND_PCI_DEVICE           0x02
#define FIND_PCI_CLASS_CODE       0x03
#define GENERATE_SPECIAL_CYCLE    0x06
#define READ_CONFIG_BYTE          0x08
#define READ_CONFIG_WORD          0x09
#define READ_CONFIG_DWORD         0x0a
#define WRITE_CONFIG_BYTE         0x0b
#define WRITE_CONFIG_WORD         0x0c
#define WRITE_CONFIG_DWORD        0x0d



#define __CPPARGS


// ME94 Register Set
#define ME94_READ_PORT_A		0x00  //R
#define ME94_READ_PORT_B		0x01  //R
#define ME94_READ_PORT_C		0x02  //R

// ME95 Register Set
#define ME95_WRITE_PORT_A		0x00  //W
#define ME95_WRITE_PORT_B		0x01  //W

// ME96 Register Set
#define ME96_WRITE_PORT_A		0x00  //W
#define ME96_READ_PORT_B		0x01  //R
#define ME96_READ_PORT_C		0x02  //R

// ME9x Register Set
#define ME9x_PORT_CONTROL	    0x03  //W
#define ME9x_WRITE_ENABLE	    0x04  //RW
#define ME9x_WRITE_DISABLE	    0x08  //RW

// PLX Register Set
#define PLX_INT_STA             0x4C  //RW


#ifdef MSC
#define outport(port,val)   outp(port,val)
#define inport(port)        inp(port)
#endif

#define LOBYTE( w ) ( ( unsigned char ) ( ( w ) & 0xFF ) )
#define HIBYTE( w ) ( ( unsigned char ) ( ( ( w ) >> 8 ) & 0xFF ) )

#define  PIC_MASTER_PORT    0x20  /* Port-Adresse Master-PIC */
#define  PIC_SLAVE_PORT     0xA0  /* Port-Adresse Slave-PIC  */
#define  FIRST_MASTER_INTR  0x08  /* Nr. des ersten Master-Interrupts */
#define  FIRST_SLAVE_INTR   0x70  /* Nr. des ersten Slave-Interrupts  */


/* Define Function Prototypes */
void IRQ_Enable (int irq_nr);
void IRQ_Disable (int irq_nr);
void IRQ_SendEOI (int irq_nr);
void interrupt get_out(__CPPARGS);    /* interrupt prototype */
void interrupt (*oldfunc)(__CPPARGS); /* interrupt function pointer */
void ( interrupt *install_IRQ_Handler ( int irq_nr,
		   void (interrupt *new_handler) () ) ) ();
void IRQ_SendEOI 		(int irq_nr);
void setup_int_vect(void);
void interrupt IsrForME9xPCI(void);
