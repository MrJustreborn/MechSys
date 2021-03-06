/****************************************************************************/
/*                                                                          */
/* Module: AMCC.H                                                           */
/*                                                                          */
/* Purpose: Definitions for AMCC PCI Library                                */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*  General Constants                                                       */
/****************************************************************************/

#define TRUE    1
#define FALSE   0

typedef unsigned char byte;     /* 8-bit  */
typedef unsigned short word;    /* 16-bit */
typedef unsigned long dword;    /* 32-bit */

#define CARRY_FLAG 0x01         /* 80x86 Flags Register Carry Flag bit */

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

/****************************************************************************/
/*   PCI Return Code List                                                   */
/****************************************************************************/

#define SUCCESSFUL               0x00
#define NOT_SUCCESSFUL           0x01
#define FUNC_NOT_SUPPORTED       0x81
#define BAD_VENDOR_ID            0x83
#define DEVICE_NOT_FOUND         0x86
#define BAD_REGISTER_NUMBER      0x87

/****************************************************************************/
/*   PCI Configuration Space Registers                                      */
/****************************************************************************/

#define PCI_CS_VENDOR_ID         0x00
#define PCI_CS_DEVICE_ID         0x02
#define PCI_CS_COMMAND           0x04
#define PCI_CS_STATUS            0x06
#define PCI_CS_REVISION_ID       0x08
#define PCI_CS_CLASS_CODE        0x09
#define PCI_CS_CACHE_LINE_SIZE   0x0c
#define PCI_CS_MASTER_LATENCY    0x0d
#define PCI_CS_HEADER_TYPE       0x0e
#define PCI_CS_BIST              0x0f
#define PCI_CS_BASE_ADDRESS_0    0x10
#define PCI_CS_BASE_ADDRESS_1    0x14
#define PCI_CS_BASE_ADDRESS_2    0x18
#define PCI_CS_BASE_ADDRESS_3    0x1c
#define PCI_CS_BASE_ADDRESS_4    0x20
#define PCI_CS_BASE_ADDRESS_5    0x24
#define PCI_CS_SUB_VENDOR_ID     0x2c
#define PCI_CS_SUB_DEVICE_ID     0x2e
#define PCI_CS_EXPANSION_ROM     0x30
#define PCI_CS_INTERRUPT_LINE    0x3c
#define PCI_CS_INTERRUPT_PIN     0x3d
#define PCI_CS_MIN_GNT           0x3e
#define PCI_CS_MAX_LAT           0x3f

/****************************************************************************/
/*   AMCC Operation Register Offsets                                        */
/****************************************************************************/

#define PLX_INT_STA         0x4C

#define AMCC_OP_REG_OMB1         0x00
#define AMCC_OP_REG_OMB2         0x04
#define AMCC_OP_REG_OMB3         0x08 
#define AMCC_OP_REG_OMB4         0x0c
#define AMCC_OP_REG_IMB1         0x11
#define AMCC_OP_REG_IMB2         0x14
#define AMCC_OP_REG_IMB3         0x18 
#define AMCC_OP_REG_IMB4         0x1c
#define AMCC_OP_REG_FIFO         0x20
#define AMCC_OP_REG_MWAR         0x24
#define AMCC_OP_REG_MWTC         0x28
#define AMCC_OP_REG_MRAR         0x2c
#define AMCC_OP_REG_MRTC         0x30
#define AMCC_OP_REG_MBEF         0x34
#define AMCC_OP_REG_INTCSR       0x38
#define AMCC_OP_REG_MCSR         0x3c
#define AMCC_OP_REG_MCSR_NVDATA  (AMCC_OP_REG_MCSR + 2) /* Data in byte 2 */
#define AMCC_OP_REG_MCSR_NVCMD   (AMCC_OP_REG_MCSR + 3) /* Command in byte 3 */

/****************************************************************************/
/*   AMCCLIB Prototypes                                                     */
/****************************************************************************/

int pci_bios_present(byte *hardware_mechanism,
			    word *interface_level_version,
			    byte *last_pci_bus_number);

int find_pci_device(word device_id,
		    word vendor_id,
		    word index,
		    byte *bus_number,
		    byte *device_and_function);

int find_pci_class_code(dword class_code,
		    word index,
		    byte *bus_number,
		    byte *device_and_function);

int generate_special_cycle(byte bus_number,
			   dword special_cycle_data);

int read_configuration_byte(byte bus_number,
			    byte device_and_function,
			    byte register_number,
			    byte *byte_read);

int read_configuration_word(byte bus_number,
			    byte device_and_function,
			    byte register_number,
			    word *word_read);

int read_configuration_dword(byte bus_number,
			     byte device_and_function,
			     byte register_number,
			     dword *dword_read);

int write_configuration_byte(byte bus_number,
			     byte device_and_function,
			     byte register_number,
			     byte byte_to_write);

int write_configuration_word(byte bus_number,
			     byte device_and_function,
			     byte register_number,
			     word word_to_write);

int write_configuration_dword(byte bus_number,
			      byte device_and_function,
			      byte register_number,
			      dword dword_to_write);

void outpd(word port, dword value);
dword inpd(word port);

void insb(word port, void *buf, int count);
void insw(word port, void *buf, int count);
void insd(word port, void *buf, int count);

void outsb(word port, void *buf, int count);
void outsw(word port, void *buf, int count);
void outsd(word port, void *buf, int count);

