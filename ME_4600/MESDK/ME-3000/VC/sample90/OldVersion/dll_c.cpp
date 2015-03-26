#pragma optimize("", off)

#include <windows.h>
#include <winioctl.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include ".\dll.h"

extern DWORD        DLLErrorCode;
extern BOARD        Board[];


extern "C" {

_declspec(dllexport) int _cdecl  meTickTimer(int iFct)
{  
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600ErrorMessage(char *AppName)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600GetDriverErrorString(char *errortext )
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600SetPriority(int iBoardNumber, 
                                                  int iPriority)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl  me2600AIMakeChannelListEntry(int    iChannel,
                                                              int    iRange,
                                                              int    iMode,
                                                              int   *piEntry)
{ 
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl  me2600FrequencyToCounter(double dFreq)
{ 
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600GeneralReset(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl  me2600FileName(int iBoardNumber,
                                                int iType,
                                                char *pFileName)
{ 
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600AIClearChannelList(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AIAddToChannelList(int iBoardNumber,
                                                         int iEntry)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600AISetSimultaneous(int iBoardNumber,
                                                        int iMode)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600GetDLLVersion(void)
{
    DLLErrorCode = 0;
    return 0x00;
} 


_declspec(dllexport) int _cdecl me2600GetSerialNumber(int iBoardNumber,
                                                      int *piSerialNumber)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600GetVECModel(int iBoardNumber, 
                                                  int *piMEVECModel)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600GetDLLTimeStamp(char *pBuffer)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600GetDriverTimeStamp(char *pBuffer)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600GetDriverVersion(char *pBuffer)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600GetPCIConfiguration(int iBoardNumber,
                                                PME_PLX9050_INFO pBoardData)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600GetBoardInfo(int iBoardNumber, 
                                                   PME_BOARD_INFO pInfo)
{   
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600GetInterrupts(int iBoardNumber, 
                                                    PME_BOARD_ISR pInt)
{   
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600GetDriverStatus(int iBoardNumber, 
                                                 PME_DRIVER_STATUS pStatus)
{   
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DLLBoardInfo(int iBoardNumber, 
                                                   PME_BOARD_INFO pInfo)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DIOSetPortDirection(int iBoardNumber, 
                                                          int iPortNo, 
                                                          int iDir) 
{   
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DIGetBit(int iBoardNumber, 
                                               int iPortNo, 
                                               int iBitNo, 
                                               int *piBitValue)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DIGetByte(int iBoardNumber, 
                                                int iPortNo, 
                                                int iByteNo, 
                                                int *piByteValue)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DIGetWord(int iBoardNumber, 
                                                int iPortNo, 
                                                int *piValue)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DOSetBit(int iBoardNumber, 
                                               int iPortNo, 
                                               int iBitNo, 
                                               int iBitValue)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DOSetByte(int iBoardNumber, 
                                                int iPortNo, 
                                                int iByteNo, 
                                                int iByteValue)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DOSetWord(int iBoardNumber, 
                                                int iPortNo, 
                                                int iValue)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DOReset(int iBoardNumber,
                                              int iPortNo)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600Initialize(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600AISingle(int iBoardNumber,
                                               int iChannel, 
                                               int iMode,
                                               short *psValue)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600AIStop(int iBoardNumber) 
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600AISingleEx(int          iBoardNumber, 
                                                 int          iChannel, 
                                                 int          iRange, 
                                                 int          iLoops, 
                                                 int          iDelay, 
                                                 short       *psValue, 
                                                 PSHORT_PROC  pCallback)
{
    DLLErrorCode = 0;
    return true;
}


 
_declspec(dllexport) int _cdecl me2600AOContinuousEx(int        iBoardNumber, 
                                                     int        iMode,
                                                     int        iSize,
                                                     short     *psBuffer,
                                                     int        iLoops,
                                                     int        iDelay,
                                                     PVOID_PROC pCallback)
{
    DLLErrorCode = 0;
    return true;
} 


 
_declspec(dllexport) int _cdecl me2600AIScanEx(int      iBoardNumber, 
                                               short   *psBuffer,
                                               int      iSize,
                                               int      iCount,
                                               int      iMode,
                                               int      iLoops,
                                               int      iDelay,
                                               P_1_PROC pCallback)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600AIMultipleEx(int      iBoardNumber, 
                                                   short   *psBuffer,
                                                   int      iCount,
                                                   int      iMode,
                                                   int      iLoops,
                                                   int      iDelay,
                                                   P_1_PROC pCallback)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600AIQuickEx(int      iBoardNumber, 
                                                short   *psBuffer,
                                                int      iCount,
                                                int      iMode,
                                                int      iLoops,
                                                int      iDelay,
                                                P_1_PROC pCallback)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600AIQuick(int    iBoardNumber,
                                              short *psBuffer,
                                              int    iCount,
                                              int    iMode)
{
    DLLErrorCode = 0;
    return true;
}


int _cdecl me2600AIQuickInt(int iBoardNumber, short *psBuffer, int iCount)                                                                                               
{
    DLLErrorCode = 0;
    return true;
}


int _cdecl me2600AIMultiplePoll(int iBoardNumber, short *psBuffer, int iCount)
{
    DLLErrorCode = 0;
    return true;
}


int _cdecl me2600AIMultipleInt(int iBoardNumber, short *psBuffer, int iCount)                                                          
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AIMultiple(int    iBoardNumber,
                                                 short *psBuffer,
                                                 int    iCount,
                                                 int    iMode)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AIScan(int    iBoardNumber,
                                             short *psBuffer,
                                             int    iSize,
                                             int    iCount,
                                             int    iMode)
{
    DLLErrorCode = 0;
    return true;
}


int _cdecl me2600AIScanPoll(int iBoardNumber, short *psBuffer, 
                            int iSize, int iCount)
{
    DLLErrorCode = 0;
    return true;
}


int _cdecl me2600AIScanInt(int iBoardNumber, short *psBuffer, int iSize,
                           int iCount, int iScanToDisk)                                                        
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AISetTimer(int iBoardNumber,
                                                 int iScan,
                                                 int iChan)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AISetTrigger(int iBoardNumber,
                                                   int iModePolarity)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOSetTimer(int iBoardNumber, int iTime)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOSetTrigger(int iBoardNumber,
                                                   int iModePolarity)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOSetMode(int iBoardNumber,
                                                int iChannel,
                                                int iRange,
                                                int iMode)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOClearDACFIFO(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOAddToDACFIFO(int iBoardNumber, 
                                                     int iEntry)                                                  
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOWrapAround(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOContinuous(int   iBoardNumber,
                                                  int   iMode,
                                                  int   iSize,
                                                  short *psBuffer)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOStop(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOStopEx(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOReset(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOUpdate(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600AOSingle(int   iBoardNumber,
                                               int   iChannel,
                                               short sValue)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600PWMStart(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600PWMStop(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600PWMSetMode(int    iBoardNumber,
                                                 double dFrequency,
                                                 int    iDutyCycle,
                                                 int    iInverted)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600CNTSetRange(int   iBoardNumber, 
                                                  int   iCounter,
                                                  int   iEndValue,
                                                  int   iStartValue)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600CNTReset(int iBoardNumber, int iCounter)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600CNTStart(int iBoardNumber, int iCounter)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600CNTRead(int    iBoardNumber, 
                                              int    iCounter,
                                              short *psCounterValue)
{
    DLLErrorCode = 0;
    return true;
} 


_declspec(dllexport) int _cdecl me2600CNTInterrupt(int iBoardNumber, 
                                                   int iCounter,
                                                   int iFlag,
                                                   PVOID_PROC pCallback)
                                                  
{
    DLLErrorCode = 0;
    return true;
} 


int _cdecl me2600EnableCounterAInt(int iBoardNumber, PVOID_PROC pCallback)
{
    DLLErrorCode = 0;
    return true;
}


int _cdecl me2600DisableCounterAInt(int iBoardNumber)                                                       
{
    DLLErrorCode = 0;
    return true;
}


int _cdecl me2600EnableCounterBInt(int iBoardNumber, PVOID_PROC pCallback)
{
    DLLErrorCode = 0;
    return true;
}


int _cdecl me2600DisableCounterBInt(int iBoardNumber)                                                       
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600SetControlRegister(int    iBoardNumber,
                                                         USHORT usRegister,
                                                         USHORT usMode,
                                                         USHORT usBits)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600EnableExternalInt(int iBoardNumber,
                                                        PVOID_PROC pCallback )
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600DisableExternalInt(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600SIOGetRegisters(int iBoardNumber, 
                                                      PME_BOARD_SIO_REGS buffer)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) char _cdecl me2600SIOReadRegister(int iBoardNumber, 
                                                       char cReg)
{
    return cReg;
}



_declspec(dllexport) char _cdecl me2600SIOWriteRegister(int iBoardNumber, 
                                                        char cReg, 
                                                        char cVal)
{
    return cVal;
}



_declspec(dllexport) int _cdecl me2600SIOSetup(int iBoardNumber,  
                                               int iBaud, 
                                               int iLen, 
                                               int iStop, 
                                               char cParity)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600SIOLoopBackTest(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600SIOOpen(int iBoardNumber, 
                                              int iMode,
                                              int InBufferSize,
                                              int OutBufferSize)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600SIOClose(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600SIOCheckBuffer(int iBoardNumber,
                                                     PME_BOARD_SIO pSio)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600SIOClearBuffer(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}




_declspec(dllexport) int _cdecl me2600SIOReceive(int iBoardNumber,
                                                 int iMode,
                                                 int iCount,
                                                 char *pcBuffer)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600SIOTransmit(int iBoardNumber,
                                                  int iMode,
                                                  int iCount,
                                                  char *pcBuffer)
{
    DLLErrorCode = 0;
    return true;
}



_declspec(dllexport) int _cdecl me2600SIOCheckError(int iBoardNumber)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600ReadWord(int iBoardNumber,
                                               int iOffset, 
                                               int* piValue)
{
    DLLErrorCode = 0;
    return true;
}


_declspec(dllexport) int _cdecl me2600WriteWord(int iBoardNumber,
                                                int iOffset, 
                                                int iValue)
{
    DLLErrorCode = 0;
    return true;
}


int CheckBoardNumber(int nr)
{ 
    if (Board[nr].hBoard==INVALID_HANDLE_VALUE) 
        return 0; 
    else 
        return 1;
}


void StopADCandPrepareNextRun(int nr)
{
}

}


