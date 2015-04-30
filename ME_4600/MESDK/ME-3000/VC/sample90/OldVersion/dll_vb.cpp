#include <windows.h>

#include ".\dll.h" 

extern "C" 
{

_declspec(dllexport) int _stdcall VBme2600ErrorMessage(char *AppName)
{
    return me2600ErrorMessage(AppName);
}

_declspec(dllexport) int _stdcall VBme2600Initialize(int iBoardNumber)
{
    return me2600Initialize(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600GeneralReset(int iBoardNumber)
{
    return me2600GeneralReset(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600GetDLLVersion(void) 
{
    return me2600GetDLLVersion();
}

_declspec(dllexport) int _stdcall VBme2600GetDriverVersion(char *pBuffer)
{
    return me2600GetDriverVersion(pBuffer);
}

_declspec(dllexport) int _stdcall VBme2600GetDriverTimeStamp(char *pBuffer)
{
    return me2600GetDriverTimeStamp(pBuffer);
}

_declspec(dllexport) int _stdcall VBme2600GetSerialNumber(int iBoardNumber,
                                                          int *piSerialNumber)
{
    return me2600GetSerialNumber(iBoardNumber, piSerialNumber);
}

_declspec(dllexport) int _stdcall VBme2600GetVECModel(int iBoardNumber, 
                                                      int *piMEVECModel)
{
    return me2600GetVECModel(iBoardNumber, piMEVECModel);
}

_declspec(dllexport) int _stdcall VBme2600GetInterrupts(int iBoardNumber, 
                                                        PME_BOARD_ISR pInt)
{
    return me2600GetInterrupts(iBoardNumber, pInt);
}

_declspec(dllexport) int _stdcall VBme2600GetDriverStatus(int iBoardNumber, 
                                            PME_DRIVER_STATUS pStatus)
{
    return me2600GetDriverStatus(iBoardNumber, pStatus);
}

_declspec(dllexport) int _stdcall VBme2600DLLBoardInfo(int iBoardNumber, 
                                                       PME_BOARD_INFO pInfo)
{
    return me2600DLLBoardInfo(iBoardNumber, pInfo); 
}

_declspec(dllexport) int _stdcall VBme2600GetPCIConfiguration(int iBoardNumber, 
                                                   PME_PLX9050_INFO pBoardData)
{
    return me2600GetPCIConfiguration(iBoardNumber, pBoardData);
}

_declspec(dllexport) int _stdcall VBme2600AIAddToChannelList(int iBoardNumber,
                                                             int iChannelList)
{
    return me2600AIAddToChannelList(iBoardNumber, iChannelList);
}

_declspec(dllexport) int _stdcall VBme2600AIClearChannelList(int iBoardNumber)
{
    return me2600AIClearChannelList(iBoardNumber);
}

__declspec(dllexport) int _stdcall VBme2600AIMultiple(int   iBoardNumber,
                                                      short *psBuffer,
                                                      int   iCount,
                                                      int   iMode)
{
    return me2600AIMultiple(iBoardNumber, psBuffer, iCount, iMode);
}

_declspec(dllexport) int _stdcall VBme2600AISetTrigger(int iBoardNumber,
                                                       int iModePolarity)
{
    return me2600AISetTrigger(iBoardNumber, iModePolarity);
}

_declspec(dllexport) int _stdcall VBme2600AISetTimer(int iBoardNumber,
                                                     int iScan,
                                                     int iChan)
{
    return me2600AISetTimer(iBoardNumber, iScan, iChan);
}

_declspec(dllexport) int _stdcall VBme2600AISetSimultaneous(int iBoardNumber,
                                                            int iMode)
{
    return me2600AISetSimultaneous(iBoardNumber, iMode);
}

_declspec(dllexport) int _stdcall VBme2600AIMakeChannelListEntry(int    iChannel,
                                                                 int    iRange,
                                                                 int    iMode,
                                                                 int   *piEntry)
{
    return me2600AIMakeChannelListEntry(iChannel, iRange,  iMode, piEntry);
}

_declspec(dllexport) int _stdcall VBme2600FrequencyToCounter(double dFreq)
{
    return me2600FrequencyToCounter(dFreq);
}

_declspec(dllexport) int _stdcall VBme2600FileName(int iBoardNumber,
                                                   int iType,
                                                   char *pFileName)
{
    return me2600FileName(iBoardNumber, iType, pFileName);
}

_declspec(dllexport) int _stdcall VBme2600AISingle(int   iBoardNumber,
                                                   int   iChannel,
                                                   int   iMode,
                                                   short *psValue)
{
    return me2600AISingle(iBoardNumber, iChannel, iMode, psValue);
}

_declspec(dllexport) int _stdcall VBme2600AIQuick(int    iBoardNumber,
                                                  short *psBuffer,
                                                  int    iCount,
                                                  int    iMode)
{
    return me2600AIQuick(iBoardNumber, psBuffer, iCount, iMode);
}

_declspec(dllexport) int _stdcall VBme2600AIScan(int    iBoardNumber,
                                                 short *psBuffer,
                                                 int    iSize,
                                                 int    iCount,
                                                 int    iMode)
{
    return me2600AIScan(iBoardNumber, psBuffer, iSize, iCount, iMode);
}

_declspec(dllexport) int _stdcall VBme2600AIStop(int iBoardNumber) 
{
    return me2600AIStop(iBoardNumber); 
}

_declspec(dllexport) int _stdcall VBme2600AISingleEx(int          iBoardNumber, 
                                                     int          iChannel, 
                                                     int          iRange, 
                                                     int          iLoops, 
                                                     int          iDelay, 
                                                     short       *psValue, 
                                                     PSHORT_PROC  pCallback)
{
    return me2600AISingleEx(iBoardNumber, iChannel, iRange, iLoops, iDelay, 
                            psValue, pCallback);
}

_declspec(dllexport) int _stdcall VBme2600AIQuickEx(int      iBoardNumber, 
                                                    short   *psBuffer,
                                                    int      iCount,
                                                    int      iMode,
                                                    int      iLoops,
                                                    int      iDelay,
                                                    P_1_PROC pCallback)
{
    return me2600AIQuickEx(iBoardNumber, psBuffer, iCount, iMode,
                           iLoops, iDelay, pCallback);
}

_declspec(dllexport) int _stdcall VBme2600AIMultipleEx(int      iBoardNumber, 
                                                       short   *psBuffer,
                                                       int      iCount,
                                                       int      iMode,
                                                       int      iLoops,
                                                       int      iDelay,
                                                       P_1_PROC pCallback)
{
    return me2600AIMultipleEx(iBoardNumber, psBuffer, iCount, iMode,
                              iLoops, iDelay, pCallback);
}

_declspec(dllexport) int _stdcall VBme2600AIScanEx(int      iBoardNumber, 
                                                   short   *psBuffer,
                                                   int      iSize,
                                                   int      iCount,
                                                   int      iMode,
                                                   int      iLoops,
                                                   int      iDelay,
                                                   P_1_PROC pCallback)
{
    return me2600AIScanEx(iBoardNumber, psBuffer, iSize, iCount, iMode,
                          iLoops, iDelay, pCallback);
}

_declspec(dllexport) int _stdcall VBme2600SetPriority(int iBoardNumber, 
                                                      int iPriority)
{
    return me2600SetPriority(iBoardNumber, iPriority);
}

_declspec(dllexport) int _stdcall VBme2600AOAddToDACFIFO(int iBoardNumber, 
                                                         int iEntry)                                                  
{
    return me2600AOAddToDACFIFO(iBoardNumber, iEntry);
}


_declspec(dllexport) int _stdcall VBme2600AOClearDACFIFO(int iBoardNumber)
{
    return me2600AOClearDACFIFO(iBoardNumber);
}


_declspec(dllexport) int _stdcall VBme2600AOReset(int iBoardNumber)
{
    return me2600AOReset(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600AOSetMode(int iBoardNumber,
                                                     int iChannel,
                                                     int iRange,
                                                     int iMode)
{
    return me2600AOSetMode(iBoardNumber, iChannel, iRange, iMode);
}

_declspec(dllexport) int _stdcall VBme2600AOSetTimer(int iBoardNumber, int iTime)
{
    return me2600AOSetTimer(iBoardNumber, iTime);
}

_declspec(dllexport) int _stdcall VBme2600AOSetTrigger(int iBoardNumber,
                                                       int iModePolarity)
{
    return me2600AOSetTrigger(iBoardNumber, iModePolarity);
}

_declspec(dllexport) int _stdcall VBme2600AOSingle(int   iBoardNumber,
                                                   int   iChannel,
                                                   short sValue)
{
    return me2600AOSingle(iBoardNumber, iChannel, sValue);
}

_declspec(dllexport) int _stdcall VBme2600AOStop(int iBoardNumber)
{
    return me2600AOStop(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600AOStopEx(int iBoardNumber)
{
    return me2600AOStopEx(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600AOUpdate(int iBoardNumber)
{
    return me2600AOUpdate(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600AOWrapAround(int iBoardNumber)
{
    return me2600AOWrapAround(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600AOContinuous(int   iBoardNumber,
                                                      int   iMode,
                                                      int   iSize,
                                                      short *psBuffer)
{
    return me2600AOContinuous(iBoardNumber, iMode, iSize, psBuffer);
}

_declspec(dllexport) int _stdcall VBme2600AOContinuousEx(int            iBoardNumber, 
                                                        int         iMode,
                                                        int         iSize,
                                                        short      *psBuffer,
                                                        int         iLoops,
                                                        int         iDelay,
                                                        PVOID_PROC  pCallback)
{
    return me2600AOContinuousEx(iBoardNumber, iMode, iSize, psBuffer,
                               iLoops, iDelay, pCallback);
}

_declspec(dllexport) int _stdcall VBme2600DIOSetPortDirection(int iBoardNumber, 
                                                              int iPortNo, 
                                                              int iDir) 
{
    return me2600DIOSetPortDirection(iBoardNumber, iPortNo, iDir);
}

_declspec(dllexport) int _stdcall VBme2600DIGetBit(int iBoardNumber, 
                                                   int iPortNo, 
                                                   int iBitNo, 
                                                   int *piBitValue)
{
    return me2600DIGetBit(iBoardNumber, iPortNo, iBitNo, piBitValue);
}

_declspec(dllexport) int _stdcall VBme2600DIGetByte(int iBoardNumber, 
                                                    int iPortNo, 
                                                    int iBitNo, 
                                                    int *piByteValue)
{
    return me2600DIGetByte(iBoardNumber, iPortNo, iBitNo, piByteValue);
}

_declspec(dllexport) int _stdcall VBme2600DIGetWord(int iBoardNumber, 
                                                    int iPortNo, 
                                                    int *piValue)
{
    return me2600DIGetWord(iBoardNumber, iPortNo, piValue);
}

_declspec(dllexport) int _stdcall VBme2600DOSetBit(int iBoardNumber, 
                                                   int iPortNo, 
                                                   int iBitNo, 
                                                   int iBitValue)
{
    return me2600DOSetBit(iBoardNumber, iPortNo, iBitNo, iBitValue);
}

_declspec(dllexport) int _stdcall VBme2600DOSetByte(int iBoardNumber, 
                                                    int iPortNo, 
                                                    int iBitNo, 
                                                    int iByteValue)
{
    return me2600DOSetByte(iBoardNumber, iPortNo, iBitNo, iByteValue);
}

_declspec(dllexport) int _stdcall VBme2600DOSetWord(int iBoardNumber, 
                                                    int iPortNo, 
                                                    int iValue)
{
    return me2600DOSetWord(iBoardNumber, iPortNo, iValue);
}

_declspec(dllexport) int _stdcall VBme2600DOReset(int iBoardNumber, 
                                                  int iPortNo) 
{
    return me2600DOReset(iBoardNumber, iPortNo);
}

_declspec(dllexport) int _stdcall VBme2600PWMStart(int iBoardNumber)
{
    return me2600PWMStart(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600PWMStop(int iBoardNumber)
{
    return me2600PWMStop(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600PWMSetMode(int iBoardNumber,
                                                     double dFrequency,
                                                     int    iDutyCycle,
                                                     int    iInverted)
{
    return me2600PWMSetMode(iBoardNumber, dFrequency, iDutyCycle, iInverted);
}

_declspec(dllexport) int _stdcall VBme2600EnableExternalInt(int iBoardNumber,
                                                            PVOID_PROC pCallback)
{
    return me2600EnableExternalInt(iBoardNumber, pCallback);
}

_declspec(dllexport) int _stdcall VBme2600DisableExternalInt(int iBoardNumber)
{
    return me2600DisableExternalInt(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600CNTRead(int    iBoardNumber,
                                                  int    iCounter,
                                                  short *psCounterValue)
{
    return me2600CNTRead(iBoardNumber, iCounter, psCounterValue);
}

_declspec(dllexport) int _stdcall VBme2600CNTStart(int iBoardNumber,
                                                   int iCounter)
{
    return me2600CNTStart(iBoardNumber, iCounter);
}

_declspec(dllexport) int _stdcall VBme2600CNTReset(int iBoardNumber,
                                                   int iCounter)
{
    return me2600CNTReset(iBoardNumber, iCounter);
}

_declspec(dllexport) int _stdcall VBme2600CNTSetRange(int iBoardNumber,
                                                      int iCounter,
                                                      int iEndValue,
                                                      int iStartValue)
{
    return me2600CNTSetRange(iBoardNumber, iCounter, iEndValue, iStartValue);
}

_declspec(dllexport) int _stdcall VBme2600CNTInterrupt(int        iBoardNumber,
                                                       int        iCounter,
                                                       int        iFlag,
                                                       PVOID_PROC pCallback)
{
    return me2600CNTInterrupt(iBoardNumber, iCounter, iFlag, pCallback);
}

_declspec(dllexport) int _stdcall VBme2600SIOSetup(int iBoardNumber,
                                                   int iBaud, 
                                                   int iLen, 
                                                   int iStop, 
                                                   char cParity)
{
    return me2600SIOSetup(iBoardNumber, iBaud, iLen, iStop, cParity);
}

_declspec(dllexport) int _stdcall VBme2600SIOLoopBackTest(int iBoardNumber)
{
    return me2600SIOLoopBackTest(iBoardNumber);
}

_declspec(dllexport) char _stdcall VBme2600SIOReadRegister(int iBoardNumber, 
                                                           char cReg)
{
    return me2600SIOReadRegister(iBoardNumber, cReg);
}

_declspec(dllexport) char _stdcall VBme2600SIOWriteRegister(int iBoardNumber, 
                                                            char cReg,
                                                            char cVal)
{
    return me2600SIOWriteRegister(iBoardNumber, cReg, cVal);
}

_declspec(dllexport) int  _stdcall VBme2600SIOGetRegisters(int iBoardNumber,  
                                                    PME_BOARD_SIO_REGS buffer)

{
    return me2600SIOGetRegisters(iBoardNumber, buffer);
}                                                       

_declspec(dllexport) int _stdcall VBme2600SIOTransmit(int iBoardNumber,
                                                      int iMode,
                                                      int iCount,
                                                      char *pcBuffer)
{
    return me2600SIOTransmit(iBoardNumber, iMode, iCount, pcBuffer);
}

_declspec(dllexport) int _stdcall VBme2600SIOReceive(int iBoardNumber,
                                                     int iMode,
                                                     int iCount,
                                                     char *pcBuffer)
{
    return me2600SIOReceive(iBoardNumber, iMode, iCount, pcBuffer);
}


_declspec(dllexport) int _stdcall VBme2600SIOOpen(int iBoardNumber,
                                                  int iMode,
                                                  int InBufferSize,
                                                  int OutBufferSize)
{
    return me2600SIOOpen(iBoardNumber, iMode, InBufferSize, OutBufferSize);
}


_declspec(dllexport) int _stdcall VBme2600SIOClose(int iBoardNumber)
{
    return me2600SIOClose(iBoardNumber);
}


_declspec(dllexport) int _stdcall VBme2600SIOClearBuffer(int iBoardNumber)
{
    return me2600SIOClearBuffer(iBoardNumber);
}

_declspec(dllexport) int _stdcall VBme2600SIOCheckBuffer(int iBoardNumber,
                                                         PME_BOARD_SIO pSio)
{
    return me2600SIOCheckBuffer(iBoardNumber, pSio);
}


_declspec(dllexport) int _stdcall VBme2600SIOCheckError(int iBoardNumber)
{
    return me2600SIOCheckError(iBoardNumber);
}

} 