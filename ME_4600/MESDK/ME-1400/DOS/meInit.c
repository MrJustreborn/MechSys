// This file contains the implementation of the function me1400Init used to
// initialise the board. Normally you can use this function unchanged
// in your own applications.

// This code was writen for BorlandC 3.1 compiler

// For an explanation of the parameters passed to the routine, please see
// the file me1400.h

// Standard includes

#include <stdio.h>
#include <conio.h>
#include <dos.h>

// Other includes

#include "..\amcc.h"        // Low level PCI Bios routines
#include "..\me1400.h"      // Error codes


unsigned int me1400Init(
    unsigned short* p_me1400_port,
    unsigned char* p_me1400_irq,
    unsigned short* p_plx_port,
    unsigned int* p_me_DevID)
{
    int amcc_result = SUCCESSFUL;

    byte b_bus_no;
    byte b_dev_fct;
    dword i;

    unsigned long ul_file_length;
    unsigned short us_cfgreg;
    unsigned char uc_mask;

    /*--- Look for a valid PCI BIOS -----------------------------*/

    amcc_result = pci_bios_present(NULL,NULL,NULL);

    if(amcc_result != SUCCESSFUL)
    {
        printf("Error - PCI Bios not present\n");
        return(ME1400_ERROR_PCI_BIOS_NOT_PRESENT);
    }
    printf("... PCI Bios found\n");
    sleep(1);


    /*--- Look for the Meilhaus ME-1400 board -----------------*/

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
        for((*p_me_DevID)=0x1400; (*p_me_DevID)<0x1500; (*p_me_DevID)++)
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
        printf("Error - No ME1400 Board Found\n");
        return(ME1400_ERROR_ME1400_NOT_FOUND);
    }

    switch (*p_me_DevID)
    {
    case 0x1400:
        {
            printf("... ME-1400 Standard found\n");
            break;
        }
    case 0x140A:
        {
            printf("... ME-1400 A found\n");
            break;
        }
    case 0x140B:
        {
            printf("... ME-1400 B found\n");
            break;
        }
    case 0x140C:
        {
            printf("... ME-1400 C or D found\n");
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
        return(ME1400_ERROR_PLX_MEMORY_MAPPED);
    }

    /*--- PLX bug ??  --*/
    if(*p_plx_port & 0x80)
    {
        unsigned short* p_swp_port;

        // We must change the plx base address to a 256 byte boundary
        printf("PLX bug - replace Base address 1 with base address 5\n");
        sleep(1);

        // Read base address 5, we can use this as a substitute for the
        // PLX base address
        read_configuration_word(b_bus_no,                       // Bus number
                                b_dev_fct,                      // Slot and function number
                                PCI_CS_BASE_ADDRESS_5,          // We read base address 5
                                p_swp_port                  );  // Port address returned here

        printf("Base address 5: 0x%04X\n", *p_swp_port);
        sleep(1);

        if ((*p_swp_port != 0x0000) && (*p_swp_port & 0x0001))
        {
            *p_plx_port = *p_swp_port;
        }
        else
        {
            printf("There are no swap register reserved in the PCI address space.\n");
            printf("We change the base address manually without any feedback from the OS\n");
            printf("Under certain circumstances the system could hang\n");
            sleep(1);

            // first subtract 0x80 if that does not work try to add 0x80
            *p_plx_port = *p_plx_port - 0x80;
        }

        printf("New base address 1: 0x%04X\n", *p_swp_port);
        sleep(1);

        // We write the contents of base address 5 (now contained in p_plx_port)
        // to base address 1
        write_configuration_word(   b_bus_no,                   // Bus number
                                    b_dev_fct,                  // Slot and function number
                                    PCI_CS_BASE_ADDRESS_1,      // We write base address 1
                                    *p_plx_port             );  // New base address
    }

    *p_plx_port &= 0xFFFC;

    printf("PLX Port: 0x%04X\n", *p_plx_port);

    if(*p_me1400_port != 0)
    {
        // *p_me1400_port was not zero, this means the user wishes to force the
        // ME1400 board to use a given base address. We write the required value
        // to base address 2 (ME1400 base register).

        write_configuration_word(b_bus_no,                  // Bus number
                                b_dev_fct,                  // Slot and function number
                                PCI_CS_BASE_ADDRESS_2,      // We write base address 1
                                *p_me1400_port          );  // New base address
    }


    // Read base address 2, this is the ME1400 base register

    read_configuration_word(b_bus_no,                   // Bus number
                            b_dev_fct,                  // Slot and function number
                            PCI_CS_BASE_ADDRESS_2,      // We read base address 1
                            p_me1400_port           );  // Port address returned here

    printf("Base address 2: 0x%04X\n", *p_me1400_port);

    if( (*p_me1400_port & 0x0001) == 0)
    {
        // The ME1400 registers are memory mapped - we cannot use this board under DOS
        printf("Error - ME1400 registers are memory mapped\n");
        return(ME1400_ERROR_ME1400_REGS_MEMORY_MAPPED);
    }

    *p_me1400_port&= 0xFFFC;

    printf("ME1400 Port: 0x%04X\n", *p_me1400_port);

    if(*p_me1400_irq != 0)
    {
        // *p_me1400_irq was not zero, this means the user wishes to force the
        // ME1400 board to use a given irq line. We write the required value
        // to PCI_CS_INTERRUPT_LINE in the PCI configuration space (ME1400 base register).

        write_configuration_byte(   b_bus_no,                   // Bus number
                                    b_dev_fct,                  // Slot and function number
                                    PCI_CS_INTERRUPT_LINE,      // We write the interrupt line number
                                    *p_me1400_irq           );  // New interrupt line number
    }

    // Read from offset PCI_CS_INTERRUPT_LINE in the PCI configuration space, this is
    // the ME1400 irq line.
    read_configuration_byte(b_bus_no,                   // Bus number
                            b_dev_fct,                  // Slot and function number
                            PCI_CS_INTERRUPT_LINE,      // We read the interrupt line number
                            p_me1400_irq            );  // Interrupt line number returned here
    printf("ME1400 IRQ: 0x%02X\n", *p_me1400_irq);


    printf("If you running this sample under Windows 9x\n");
    printf("make sure that the windows driver is not running.\n");
    printf("(Restart Windows and dont start any Windows sample before)\n");

    // Make sure the system 8259 enables the IRQ with OCW1 @ I/O 21h
    // for IRQ0-7 or @ I/O A1h for IRQ8-15
    if(*p_me1400_irq < 8)
    {
        uc_mask = inportb(0x21);
        uc_mask = uc_mask & ~(1 << *p_me1400_irq);
        outportb(0x21, uc_mask);
    }
    else
    {
        uc_mask = inportb(0xA1);
        uc_mask = uc_mask & ~( 1 << (*p_me1400_irq - 8) );
        outportb(0xA1, uc_mask);
    }

    // Return no error
    return(ME1400_NO_ERROR);
}
