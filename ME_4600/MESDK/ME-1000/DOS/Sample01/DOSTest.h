
#define TRUE    1
#define FALSE   0

typedef unsigned char  BYTE;     /* 8-bit  */
typedef unsigned short WORD;    /* 16-bit */
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


