/*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.c                                                                                */
/*  Compiler:       tested with Borland C 3.1  (see batch file for special setting)                         */
/*  Copyright:      1998-2002 Meilhaus Electronic GmbH                                                      */
/*  Author:         ab                                                                                      */
/*                  special thanks to AMCC for the PCI BIOS library                                         */
/*                  (www.amcc.com in special www.amcc.com/TechLib/pcidev.htm)                               */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  Application Notes:                                                                                      */
/*                  This is not a full working application, it should show, how you can determine the       */
/*                  resources and programming some registers                                                */
/*                  For internal reasons we are not in a position to publish the whole register description */
/*                  You can use the samples "as is" Meilhaus Electronic offers no support on this samples   */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020503  ab      create                                                          */
/*----------------------------------------------------------------------------------------------------------*/



/****************************************************************************/
/*                                                                          */
/* Include Files                                                            */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <stddef.h>

#include "..\amcc.h"        // Low level PCI Bios routines


/****************************************************************************/
/*                                                                          */
/* Define macros to obtain individual bytes from a word register            */
/*                                                                          */
/****************************************************************************/

#define HIGH_BYTE(ax) (ax >> 8)
#define LOW_BYTE(ax) (ax & 0xff)





void main(void)
{
    byte hardware_mechanism;
    word interface_level_version;
    byte last_pci_bus_number;
    word device_id;
    word vendor_id;
    word index;
    byte bus_number;
    byte device_and_function;
    word wErrorCode;
    word word_read1;
    word word_read2;
    FILE *pFile;
    word wFound = 0;

    if ((pFile = fopen("GetMEpci.txt","wt")) == NULL)
    {
        pFile = stderr;
    }

    wErrorCode = pci_bios_present(&hardware_mechanism,
                                  &interface_level_version,
                                  &last_pci_bus_number);

    if (wErrorCode != SUCCESSFUL)
    {
        fprintf(pFile,"PCI BIOS not presented !\n");
        fprintf(stdout,"PCI BIOS not presented !\n");
        fprintf(pFile,"This utility runs only under Windows 95 or on a DOS boot disk !\n");
        fprintf(stdout,"This utility runs only under Windows 95 or on a DOS boot disk !\n");
        getch();
    }
    else
    {
        fprintf(pFile, "This program reads the PCI settings and serial number of meilhaus boards\n");
        fprintf(pFile, "-------------------------------------------\n\n");
        fprintf(pFile, "Copyright (c) 25.11.98 Andreas Bernau\n");
        fprintf(pFile, "This process can take several minutes\n");
        fprintf(pFile, "All values are hexadecimal\n\n");
        fprintf(pFile, "\nSee file Getmepci.txt!\n\n");

        fprintf(stdout, "This program reads the PCI settings and serial number of meilhaus boards\n");
        fprintf(stdout, "-------------------------------------------\n\n");
        fprintf(stdout, "Copyright (c) 25.11.98 Andreas Bernau\n");
        fprintf(stdout, "This process can take several minutes\n");
        fprintf(stdout, "All values are hexadecimal\n\n");
        fprintf(stdout, "\nSee file Getmepci.txt!\n\n");

        //fprintf("PCI BIOS present !\n\n");

        //fprintf("hardware_mechanism:      0x%02x\n",hardware_mechanism);
        //fprintf("interface_level_version: 0x%02x\n",interface_level_version);
        //fprintf("last_pci_bus_number:     0x%02x\n",last_pci_bus_number);
        //fprintf("\n");

        vendor_id = 0x1402;

        for (device_id=0; device_id<0xFFFF; device_id++)
        {
            if ((device_id % 0x500) == 0)
            {
                fprintf(stdout,"\r%02ld\%",(((dword)device_id) * 100L) / 0xFFFF);
            }

            index     = 0x00;
            do
            {
                wErrorCode = find_pci_device(device_id,
                                             vendor_id,
                                             index,
                                             &bus_number,
                                             &device_and_function);

                if (wErrorCode == SUCCESSFUL)
                {
                    wFound = 1;

                    fprintf(pFile, "Found device:  ");
                    fprintf(pFile, "VID: %04x  ",device_id);
                    fprintf(pFile, "DID: %04x  ",vendor_id);
                    fprintf(pFile, "Idx: %02x  ",index);
                    fprintf(pFile, "Bus: %02x  ",bus_number);
                    fprintf(pFile, "D&F: %02x\n",device_and_function);

                    fprintf(stdout, "\rFound device:  ");
                    fprintf(stdout, "VID: %04x  ",device_id);
                    fprintf(stdout, "DID: %04x  ",vendor_id);
                    fprintf(stdout, "Idx: %02x  ",index);
                    fprintf(stdout, "Bus: %02x  ",bus_number);
                    fprintf(stdout, "D&F: %02x\n",device_and_function);

                    index++;

                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x2c,
                                             &word_read1);
                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x2e,
                                             &word_read2);
                    fprintf(pFile, "Ser-#:  %04x%04x\n", word_read2,word_read1);
                    fprintf(stdout, "Ser-#:  %04x%04x\n", word_read2,word_read1);


                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x3c,
                                             &word_read1);
                    word_read1 = (byte)(word_read1 & 0xFF);
                    fprintf(pFile, "IRQ:    %02x        [%02d(dec)]\n", word_read1,word_read1);
                    fprintf(stdout, "IRQ:    %02x        [%02d(dec)]\n", word_read1,word_read1);


                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x10,
                                             &word_read1);
                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x12,
                                             &word_read2);
                    fprintf(pFile, "PLXMM:  %04x%04x\n", word_read2,word_read1);
                    fprintf(stdout, "PLXMM:  %04x%04x\n", word_read2,word_read1);
////////

                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x14,
                                             &word_read1);
                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x16,
                                             &word_read2);
                    fprintf(pFile, "PLXIO:  %04x%04x\n", word_read2,word_read1);
                    fprintf(stdout, "PLXIO:  %04x%04x\n", word_read2,word_read1);



                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x18,
                                             &word_read1);
                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x1A,
                                             &word_read2);
                    fprintf(pFile, "BASE0:  %04x%04x\n", word_read2,word_read1);
                    fprintf(stdout, "BASE0:  %04x%04x\n", word_read2,word_read1);

                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x1c,
                                             &word_read1);
                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x1e,
                                             &word_read2);
                    fprintf(pFile, "BASE1:  %04x%04x\n", word_read2,word_read1);
                    fprintf(stdout, "BASE1:  %04x%04x\n", word_read2,word_read1);


                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x20,
                                             &word_read1);
                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x22,
                                             &word_read2);
                    fprintf(pFile, "BASE2:  %04x%04x\n", word_read2,word_read1);
                    fprintf(stdout, "BASE2:  %04x%04x\n", word_read2,word_read1);


                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x24,
                                             &word_read1);
                    read_configuration_word(bus_number,
                                             device_and_function,
                                             0x26,
                                             &word_read2);
                    fprintf(pFile, "BASE3:  %04x%04x\n", word_read2,word_read1);
                    fprintf(stdout, "BASE3:  %04x%04x\n", word_read2,word_read1);

                    fprintf(pFile, "\n");
                    fprintf(stdout, "\n");

                }
            }
            while (wErrorCode == SUCCESSFUL);
        }
        
        {
            
        }

        if (wFound==0)
        {
            fprintf(stdout, "\rReady\n\tNo Device found!");
            fprintf(pFile, "No Device found!\n");
        }
        else
        {
            fprintf(stdout, "\rReady\n\tSee Getmepci.txt for information!");
        }

        if (pFile != stderr)
        {
            fclose(pFile);
        }
    }
}