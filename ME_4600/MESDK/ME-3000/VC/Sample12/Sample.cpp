// TestLoadFirmware.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include "..\meDefs.h"
#include "..\me3000.h"


int main(int argc, char* argv[])
{
    char error_text[256];
    char licence_no[128];
    BOOL b_licence_found = FALSE;
    BOOL bFoundAny = FALSE;
    BOOL bWarning = FALSE;
    BOOL bUpgrade = FALSE;
    int iSrlNmbr;
    int iVecModel;
    int iBrdIdx;
    char sBrdNo[256];
    char ch;

    printf("Table of all boards of the ME-3000, ME-2600 and ME-2000 family found:\n\n");

    while (TRUE)
    {
        printf(":------:----------:---------------:------------:\n");
        printf(":Board : DeviceID : Serial Number :  VEC Model :\n");
        printf(":------:----------:---------------:------------:\n");

        for (iBrdIdx=0; iBrdIdx<ME_MAX_DEVICES; iBrdIdx++)
        {
            ME_PLX9050_INFO PCIInfo;
            int iDevID;

            if (me3000GetPCIConfiguration(iBrdIdx, &PCIInfo))
            {
                iSrlNmbr = PCIInfo.SubSystem;
                iSrlNmbr = iSrlNmbr <<16;
                iSrlNmbr = iSrlNmbr | PCIInfo.SubVendor;
                iDevID =   PCIInfo.DeviceID;

                if (me3000GetVECModel(iBrdIdx, &iVecModel))
                {
                    printf(":  %3d :     %04X :      %08X :          %d :\n", iBrdIdx, iDevID, iSrlNmbr, iVecModel);
                    if (iVecModel != 3)
                        bUpgrade = TRUE;
                }
                else
                {
                    me3000GetDriverErrorString(&error_text[0]);

                    if (strstr(error_text, "not supported"))
                        printf(":  %3d :     %04X :      %08X : not needed :\n", iBrdIdx, iDevID, iSrlNmbr);
                    else
                    if (strstr(error_text, "No valid licence"))
                    {
                        printf(":  %3d :     %04X :      %08X :  not found :\n", iBrdIdx, iDevID, iSrlNmbr);
                        bWarning = TRUE;
                    }
                    else
                        printf("GetVecModel - ERROR: %s\n\n", &error_text[0]);
                }
            }
        }
        printf(":------:----------:---------------:------------:\n");


        if (bWarning == TRUE)
        {
            printf("\nYou have to enter a licence code for at least one ME-3000 board!\n");
            printf("This is required in order for the board to function correctly.\n");
            printf("Do you want to enter a licence key?\n");
        }
        else if (bUpgrade == TRUE)
        {
            printf("Do you want to upgrade a ME-3000 board to a higher VEC model number?\n");
            printf("For the step you require a higher licence key provided by Meilhaus Electronic.\n");
        }
        else
        {
            printf("\nPress any key to continue\n");
            getch();
            exit(0);
        }


        printf("Press 'y' to register an additional licence key\n");
        printf("or any other key to continue\n\n");

        while(TRUE)
        {
            ch = getch();

            if ((ch=='y') || (ch=='Y'))
                break;
            else
                return(0);

        }

        printf("Please enter the board number!\n");
        gets(sBrdNo);
        sscanf(sBrdNo, "%d", &iBrdIdx);
        me3000GetSerialNumber(iBrdIdx, &iSrlNmbr);

        printf("Change licence key for board %d with serial number %08X\n", iBrdIdx, iSrlNmbr);
        printf("Licence No (RETURN to exit): ");
        gets(&licence_no[0]);

        if(licence_no[0] == 0)
        {
            return(0);
        }

        printf("\n\n");

        if( !me3000LoadFirmware(iBrdIdx, &licence_no[0]))
        {
            me3000GetDriverErrorString(&error_text[0]);

            printf("me3000LoadFirmware - ERROR - %s\n\n", &error_text[0]);
        }
        else
        {
            printf("Licence number recognised\n\n");
        }
    }
}
