
/* These are system header files  */
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

/*  These are the me6x00 header files    */
#include ".\..\meDefs.h"
#include ".\..\DLLInit.h"


//------ main ------
int main(void)
{
  BOOL bBoardPresent[ME_MAX_DEVICES];

  // calls the initialize function
  meOpen();

  int iCurrentBoardNumber = -1;

  for(int index_board = 0; index_board < ME_MAX_DEVICES; index_board++)
  {
    int i_version;
    if( me6x00GetBoardVersion(index_board, &i_version) )
    {
      bBoardPresent[index_board] = TRUE;
      if(iCurrentBoardNumber == -1)
      {
        iCurrentBoardNumber = index_board;
      }
    }
    else
    {
      bBoardPresent[index_board] = FALSE;
    }
  }

  if(iCurrentBoardNumber == -1)
  {
    printf("\n\nNo ME6x00 boards were found!\n\n");
    exit(-1);
  }




      // int me6x00GetBoardVersion(int iBoardNumber, int *piVersion);
      printf("-----------------------------------------------------------\n");
      printf("GetBoardVersion\n");
      int boardVersion;
      if( me6x00GetBoardVersion(iCurrentBoardNumber, &boardVersion) )
        printf("board version is 0x%08X\n", boardVersion);
      else
        printf("me6x00GetBoardVersion: ERROR!\n");
      printf("-----------------------------------------------------------\n\n");
      printf("press a key to continue\n");
      getch();



      // int me6x00GetDLLVersion();
      printf("-----------------------------------------------------------\n");
      printf("GetDllVersion\n");
      int dllVersion;
      dllVersion = me6x00GetDLLVersion();
      printf("dll version is 0x%08X\n", dllVersion);
      printf("-----------------------------------------------------------\n\n");
      printf("press a key to continue\n");
      getch();



      // int me6x00GetDriverVersion(int *piDriverVersion);
      printf("-----------------------------------------------------------\n");
      printf("GetDriverVersion\n");
      int driverVersion;
      if( me6x00GetDriverVersion(&driverVersion) )
        printf("driver version is 0x%08X\n", driverVersion);
      else
        printf("me6x00GetDriverVersion: ERROR!\n");
      printf("-----------------------------------------------------------\n\n");
      printf("press a key to continue\n");
      getch();



      // int me6x00GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
      printf("-----------------------------------------------------------\n");
      printf("GetDevInfo\n");

      DEVICEINFOSTRUCT dev_info;
      if( me6x00GetDevInfo(iCurrentBoardNumber, &dev_info))
      {
        printf("Vendor ID:          0x%04X\n", dev_info.dwVendorID);
        printf("Device ID:          0x%04X\n", dev_info.dwDeviceID);
        printf("Bus Number:         %u\n", dev_info.dwBusNumber);
        printf("System Slot Number: %u\n", dev_info.dwSystemSlotNumber);
        printf("Port Base:          0x%04X\n", dev_info.dwPortBase);
        printf("Port Count:         %u\n", dev_info.dwPortCount);
        printf("Interrupt Channel:  %u\n", dev_info.dwIntChannel);
        printf("PLX Port Base:      0x%04X\n", dev_info.dwPortBasePLX);
        printf("PLX Port Count:     %u\n", dev_info.dwPortCountPLX);
        printf("Serial Number:      0x%08X\n", dev_info.dwSerialNumber);
        printf("Hardware Revision:  0x%04X\n", dev_info.dwHWRevision);
        printf("IRQ Count:          %u\n", dev_info.dwIrqCnt);
        printf("Version:            0x%04X\n", dev_info.dwVersion);
      }
      else
        printf("me6x00GetDevInfo: ERROR!\n\n");
      printf("-----------------------------------------------------------\n\n");
      printf("press a key to continue\n");
      getch();



      //int me6x00GetSerialNumber(int iBoardNumber, int *piSerialNumber);
      printf("-----------------------------------------------------------\n");
      printf("GetSerialNumber\n");
      int serialNumber;
      if( me6x00GetSerialNumber(iCurrentBoardNumber, &serialNumber) )
        printf("serial number is 0x%08X\n", serialNumber);
      else
        printf("me6x00GetSerialNumber: ERROR!\n");
      printf("-----------------------------------------------------------\n\n");
      printf("press a key to exit\n");
      getch();



    meClose();

    return(0);
}
