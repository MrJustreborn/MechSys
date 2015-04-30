// This file contains the implementation of the function ME2600Init used to
// initialise the board. Normally you can use this function unchanged
// in your own applications.

// This code was writen for BorlandC 3.1 compiler

// For an explanation of the parameters passed to the routine, please see
// the file me2600.h

// Standard includes

#include <stdio.h>
#include <conio.h>
#include <dos.h>

// Other includes

#include "..\amcc.h"        // Low level PCI Bios routines
#include "..\vec.h"         // Download key
#include "..\me2600.h"      // Error codes

unsigned int me2600Init(
    unsigned short* p_me2600_port,
    unsigned char* p_me2600_irq,
    unsigned short* p_plx_port,
    unsigned int* p_me_DevID)
{
    int amcc_result = SUCCESSFUL;

    byte b_bus_no;
    byte b_dev_fct;
    byte  *MeVec;
    dword i;

    unsigned long ul_file_length;
    unsigned short us_cfgreg;
    unsigned char uc_mask;

    /*--- Look for a valid PCI BIOS -----------------------------*/

    amcc_result = pci_bios_present(NULL,NULL,NULL);

    if(amcc_result != SUCCESSFUL)
    {
        printf("Error - PCI Bios not present\n");
        return(ME2600_ERROR_PCI_BIOS_NOT_PRESENT);
    }

    /*--- Look for the Meilhaus ME-2600 board -----------------*/

    if(*p_me_DevID != 0)
    {
        amcc_result = find_pci_device(
            *p_me_DevID,        // Device ID
            0x1402,             // Vendor ID - Meilhaus Electronic
            0,                  // Device index, we are looking for the FIRST ME1400 device
            &b_bus_no,          // Bus number returned here
            &b_dev_fct);        // Slot (device) and function number returned here
    }
    else
    {
        for((*p_me_DevID)=0x2000; (*p_me_DevID)<0x4000; (*p_me_DevID)++)
        {
            amcc_result = find_pci_device(
                *p_me_DevID,    // Device ID
                0x1402,         // Vendor ID - Meilhaus Electronic
                0,              // Device index, we are looking for the FIRST ME1400 device
                &b_bus_no,      // Bus number returned here
                &b_dev_fct);    // Slot (device) and function number returned here

            if(amcc_result == SUCCESSFUL)
                break;
        }
    }

    if(amcc_result != SUCCESSFUL)
    {
        printf("Error - No ME2600 Board Found\n");
        return(ME2600_ERROR_ME2600_NOT_FOUND);
    }

    switch (*p_me_DevID)
    {
    case 0x2000:
        {
            printf("... ME-2000 found\n");
            MeVec = MeVec1;
            break;
        }
    case 0x2600:
        {
            printf("... ME-2000 or ME-2600 found\n");
            MeVec = MeVec1;
            break;
        }
    case 0x3000:
        {
            printf("... ME-3000 found\n");
            MeVec = MeVec1;
            break;
        }
    default:
        {
            printf("... unknown ME-2000/2600/3000 found\n");
            MeVec = MeVec1;
            break;
        }
    }
    sleep(1);

    // Read base address 1, this is the PLX base register
    read_configuration_word(b_bus_no,                       // Bus number
                            b_dev_fct,                      // Slot and function number
                            PCI_CS_BASE_ADDRESS_1,          // We read base address 1
                            p_plx_port                  );  // Port address returned here

    printf("Base address 1: 0x%04X\n", *p_plx_port);

    if( (*p_plx_port & 0x0001) == 0)
    {
        // The PLX is memory mapped - we cannot use this board under DOS
        printf("Error - PLX is memory mapped\n");
        return(ME2600_ERROR_PLX_MEMORY_MAPPED);
    }

    /*--- PLX bug ??  --*/
    if(*p_plx_port & 0x80)
    {
        // We must change the plx base address to a 256 byte boundary
        printf("PLX bug - replace Base address 1 with base address 5\n");

        // Read base address 5, we can use this as a substitute for the
        // PLX base address
        read_configuration_word(b_bus_no,                       // Bus number
                                b_dev_fct,                      // Slot and function number
                                PCI_CS_BASE_ADDRESS_5,          // We read base address 5
                                p_plx_port                  );  // Port address returned here

        printf("Base address 5: 0x%04X\n", *p_plx_port);

        if( (*p_plx_port & 0x0001) == 0)
        {
            // Base address 5 is memory mapped, we cannot use this as a substitute
            // for the PLX base address under DOS

            printf("Error - Base address 5 is memory mapped\n");

            return(ME2600_ERROR_PLX_MEMORY_MAPPED);
        }

        // We write the contents of base address 5 (now contained in p_plx_port)
        // to base address 1
        write_configuration_word(   b_bus_no,                   // Bus number
                                    b_dev_fct,                  // Slot and function number
                                    PCI_CS_BASE_ADDRESS_1,      // We write base address 1
                                    *p_plx_port             );  // New base address
    }

    *p_plx_port &= 0xFFFC;

    printf("PLX Port: 0x%04X\n", *p_plx_port);

    if(*p_me2600_port != 0)
    {
        // *p_me2600_port was not zero, this means the user wishes to force the
        // ME2600 board to use a given base address. We write the required value
        // to base address 2 (ME2600 base register).

        write_configuration_word(b_bus_no,                  // Bus number
                                b_dev_fct,                  // Slot and function number
                                PCI_CS_BASE_ADDRESS_2,      // We write base address 1
                                *p_me2600_port          );  // New base address
    }


    // Read base address 2, this is the ME2600 base register

    read_configuration_word(b_bus_no,                   // Bus number
                            b_dev_fct,                  // Slot and function number
                            PCI_CS_BASE_ADDRESS_2,      // We read base address 1
                            p_me2600_port           );  // Port address returned here

    printf("Base address 2: 0x%04X\n", *p_me2600_port);

    if( (*p_me2600_port & 0x0001) == 0)
    {
        // The ME2600 registers are memory mapped - we cannot use this board under DOS

        printf("Error - ME2600 registers are memory mapped\n");

        return(ME2600_ERROR_ME2600_REGS_MEMORY_MAPPED);
    }

    *p_me2600_port&= 0xFFFC;

    printf("ME2600 Port: 0x%04X\n", *p_me2600_port);

    if(*p_me2600_irq != 0)
    {
        // *p_me2600_irq was not zero, this means the user wishes to force the
        // ME2600 board to use a given irq line. We write the required value
        // to PCI_CS_INTERRUPT_LINE in the PCI configuration space (ME2600 base register).

        write_configuration_byte(   b_bus_no,                   // Bus number
                                    b_dev_fct,                  // Slot and function number
                                    PCI_CS_INTERRUPT_LINE,      // We write the interrupt line number
                                    *p_me2600_irq           );  // New interrupt line number
    }

    // Read from offset PCI_CS_INTERRUPT_LINE in the PCI configuration space, this is
    // the ME2600 irq line.

    read_configuration_byte(b_bus_no,                   // Bus number
                            b_dev_fct,                  // Slot and function number
                            PCI_CS_INTERRUPT_LINE,      // We read the interrupt line number
                            p_me2600_irq            );  // Interrupt line number returned here

    printf("ME2600 IRQ: 0x%02X\n", *p_me2600_irq);

    /*--- Download ---*/

    // First, we do a dummy read to reset xilinx
    //------------------------------------------
    inport(*p_me2600_port + 0x42);
    delay(3);       // at least this delay is important

    // Write a dummy value to xilinx
    //--------------------------------------------------------------------
    outportb(*p_me2600_port + 0x00, 0x00);

    // Build long from the byte-wise coded header
    //   Byte 1-3:   length of the array

    //--------------------------------------------------------------------
    ul_file_length = (MeVec[0]<<24) +(MeVec[1]<<16) +(MeVec[2]<<8) +MeVec[3];

    // Loop for writing firmware byte by byte to xilinx
    // Firmware data start at offset 16
    //--------------------------------------------------------------------
    for (i = 0; i < ul_file_length; i++)
    {
        outportb(*p_me2600_port + 0x00, MeVec[16+i]);
    }

    // Write 5 dummy values to xilinx
    //--------------------------------------------------------------------
    for (i = 0;i < 5; i++)
    {
        outportb(*p_me2600_port + 0x00, 0x00);
    }

    // Test if there was an error during download
    // -> INTB was thrown
    //--------------------------------------------------------------------
    us_cfgreg = inport(*p_plx_port + 0x4C);

    if(us_cfgreg & 0x20)
    {
        // An error ocurred during the download

        printf("Error - ME2600 download failed\n");

        return(ME2600_ERROR_DOWNLOAD_FAILED);
    }

    //--- reset board -----

    delay(1);
    outport(*p_me2600_port + ME2600_CONTROL_1, 0x0000);

    delay(1);
    outport(*p_me2600_port + ME2600_CONTROL_2, 0x0000);

    delay(1);
    outport(*p_me2600_port + ME2600_RESET_INTERRUPT, 0x0000);

    // Make sure the system 8259 enables the IRQ with OCW1 @ I/O 21h
    // for IRQ0-7 or @ I/O A1h for IRQ8-15
    if(*p_me2600_irq < 8)
    {
        uc_mask = inportb(0x21);
        uc_mask = uc_mask & ~(1 << *p_me2600_irq);
        outportb(0x21, uc_mask);
    }
    else
    {
        uc_mask = inportb(0xA1);
        uc_mask = uc_mask & ~( 1 << (*p_me2600_irq - 8) );
        outportb(0xA1, uc_mask);
    }

    // Return no error
    return(ME2600_NO_ERROR);
}
