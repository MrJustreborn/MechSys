/*----------------------------------------------------------------------------
    File: DLLINIT.H
------------------------------------------------------------------------------ 

    Meilhaus Electronic GmbH

    Header file containing Typedefs for the board.  This header is
    for use in projects using dynamic function calls (no library file is
    included in the project)

    Version 1.01:   020626
-------------------------------------------------------------------------------
    Author: Andreas Bernau / Ralph Timm
-----------------------------------------------------------------------------*/


#ifndef DLLINIT_H
#define DLLINIT_H

#define SUCCESS             0x01
#define DLLNOTFOUND         0x02
#define FUNCTIONNOTFOUND    0x03
#define DLLNAME             "me3000.dll"


typedef void (_stdcall *PSERVICE_PROC) (void);
void _stdcall pCallBack (void);                 // user defined callback routine


typedef   int(__cdecl *PF_ME3000FILENAME) (int iBoardNumber, int iType, char *pcFileName);
typedef   int(__cdecl *PF_ME3000FREQUENCYTOCOUNTER) (double dwFreq);
typedef   int(__cdecl *PF_ME3000GENERALRESET) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000GETDLLVERSION) (void);
typedef   int(__cdecl *PF_ME3000GETDRIVERVERSION) (char *pcBuffer);
typedef   int(__cdecl *PF_ME3000GETSERIALNUMBER) (int iBoardNumber, int *iSerialNumber);
typedef   int(__cdecl *PF_ME3000GETVECMODEL) (int iBoardNumber, int *iMEVECModel);
typedef   int(__cdecl *PF_ME3000INITIALIZE) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000SETPRIORITY) (int iBoardNumber, int iPriority);
typedef   int(__cdecl *PF_ME3000AIADDTOCHANNELLIST) (int iBoardNumber, int iEntry);
typedef   int(__cdecl *PF_ME3000AICLEARCHANNELLIST) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000AIMAKECHANNELLISTENTRY) (int iChannel, int iRange, int iMode, int *iEntry);
typedef   int(__cdecl *PF_ME3000AIMULTIPLE) (int iBoardNumber, short *asBuffer, int iCount, int iMode);
typedef   int(__cdecl *PF_ME3000AIMULTIPLEEX) (int iBoardNumber,
                                               short *asBuffer,
                                               int iCount,
                                               int iMode,
                                               int iLoops,
                                               int iDelay,
                                               PSERVICE_PROC pCallBack);
typedef   int(__cdecl *PF_ME3000AIQUICK) (int iBoardNumber,
                                          short *asBuffer,
                                          int iCount,
                                          int iMode);
typedef   int(__cdecl *PF_ME3000AIQUICKEX) (int iBoardNumber,
                                            short *asBuffer,
                                            int iCount,
                                            int iMode,
                                            int iLoops,
                                            int iDelay,
                                            PSERVICE_PROC pCallBack);
typedef   int(__cdecl *PF_ME3000AISCAN) (int iBoardNumber,
                                         short *asBuffer,
                                         int iSize,
                                         int iCount,
                                         int iMode);
typedef   int(__cdecl *PF_ME3000AISCANEX) (int iBoardNumber, short *asBuffer,
                                           int iSize, int iCount,
                                           int iMode, int iLoops,
                                           int iDelay, P_1_PROC pCallBack);
typedef   int(__cdecl *PF_ME3000AISETSIMULTANEOUS) (int iBoardNumber, int iMode);
typedef   int(__cdecl *PF_ME3000AISETTIMER) (int iBoardNumber, int iScan, int iChan);
typedef   int(__cdecl *PF_ME3000AISETTRIGGER) (int iBoardNumber, int iModePolarity);
typedef   int(__cdecl *PF_ME3000AISINGLE) (int iBoardNumber, int iChannel,
                                           int iMode, short *iValue);
typedef   int(__cdecl *PF_ME3000AISINGLEEX) (int iBoardNumber, int iChannel,
                                             int iMode, int iLoops,
                                             int iDelay, short *iValue,
                                             PSERVICE_PROC pCallBack);
typedef   int(__cdecl *PF_ME3000AISTOP)                     (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000AICLEARDATAFIFO)            (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000AIREADFIFO)                 (int iBoardNumber, short* asBuffer, int iSize);
typedef   int(__cdecl *PF_ME3000AISTARTBYEXTERNALTRIGGER)   (int iBoardNumber, int iTriggerMode);
typedef   int(__cdecl *PF_ME3000AOADDTODACFIFO) (int iBoardNumber, int iEntry);
typedef   int(__cdecl *PF_ME3000AOCLEARDACFIFO) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000AOCONTINUOUS) (int iBoardNumber, int iMode, int iSize, short *asBuffer);
typedef   int(__cdecl *PF_ME3000AOCONTINUOUSEX) (int iBoardNumber, int iMode, int iSize, short *asBuffer, int iLoops,
                                                 int iDelay, PSERVICE_PROC pCallBack);
typedef   int(__cdecl *PF_ME3000AORESET) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000AOSETMODE) (int iBoardNumber, int iChannel, int iRange, int iMode);
typedef   int(__cdecl *PF_ME3000AOSETTIMER) (int iBoardNumber, int iTime);
typedef   int(__cdecl *PF_ME3000AOSETTRIGGER) (int iBoardNumber, int iModePolarity);
typedef   int(__cdecl *PF_ME3000AOSINGLE) (int iBoardNumber, int iChannel, short iValue);
typedef   int(__cdecl *PF_ME3000AOSTOP) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000AOSTOPEX) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000AOUPDATE) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000AOWRAPAROUND) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000DIOSETPORTDIRECTION) (int iBoardNumber, int iPortNo, int iDir);
typedef   int(__cdecl *PF_ME3000DIGETBIT) (int iBoardNumber, int iPortNo, int iBitNo, int *iBitValue);
typedef   int(__cdecl *PF_ME3000DIGETBYTE) (int iBoardNumber, int iPortNo, int iByteNo, int *iByteValue);
typedef   int(__cdecl *PF_ME3000DIGETWORD) (int iBoardNumber, int iPortNo, int *iValue);
typedef   int(__cdecl *PF_ME3000DORESET) (int iBoardNumber, int iPortNo);
typedef   int(__cdecl *PF_ME3000DOSETBIT) (int iBoardNumber, int iPortNo, int iBitNo, int iValue);
typedef   int(__cdecl *PF_ME3000DOSETBYTE) (int iBoardNumber, int iPortNo, int iByteNo, int iByteValue);
typedef   int(__cdecl *PF_ME3000DOSETWORD) (int iBoardNumber, int iPortNo, int iValue);
typedef   int(__cdecl *PF_ME3000PWMSETMODE) (int iBoardNumber, double dwFreq, int iDutyCycle, int iInverted);
typedef   int(__cdecl *PF_ME3000PWMSTART) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000PWMSTOP) (int iBoardNumber);
typedef   int(__cdecl *PF_ME3000CNTINTERRUPT) (int iBoardNumber, int iCounter, int iFlag, PSERVICE_PROC pCallBack);
typedef   int(__cdecl *PF_ME3000CNTREAD) (int iBoardNumber, int iCounter, short *iCounterValue);
typedef   int(__cdecl *PF_ME3000CNTRESET) (int iBoardNumber, int iCounter);
typedef   int(__cdecl *PF_ME3000CNTSETRANGE) (int iBoardNumber, int iCounter, int iEndValue, int iStartValue);
typedef   int(__cdecl *PF_ME3000CNTSTART) (int iBoardNumber, int iCounter);
typedef   int(__cdecl *PF_ME3000DISABLEEXTERNALINT)(int iBoardNumber);
typedef   int(__cdecl *PF_ME3000ENABLEEXTERNALINT)(int iBoardNumber, PSERVICE_PROC pCallBack);
typedef   int(__cdecl *PF_ME3000SIOCHECKBUFFER)(int iBoardNumber, PME3000_SIO_REGS pSIO);
typedef   int(__cdecl *PF_ME3000SIOCHECKERROR)(int iBoardNumber); 
typedef   int(__cdecl *PF_ME3000SIOCLEARBUFFER)(int iBoardNumber); 
typedef   int(__cdecl *PF_ME3000SIOCLOSE)(int iBoardNumber); 
typedef   int(__cdecl *PF_ME3000SIOGETREGISTERS)(int iBoardNumber, PME3000_SIO pBuffer);
typedef   int(__cdecl *PF_ME3000SIOLOOPBACKTEST)(int iBoardNumber); 
typedef   int(__cdecl *PF_ME3000SIOOPEN)(int iBoardNumber, int iMode, int iInBufferSize, int iOutBufferSize);   
typedef   int(__cdecl *PF_ME3000SIOREADREGISTER)(int iBoardNumber, char cReg);  
typedef   int(__cdecl *PF_ME3000SIORECEIVE)(int iBoardNumber, int iMode, int iCount, char pcBuffer);
typedef   int(__cdecl *PF_ME3000SIOSETUP)(int iBoardNumber, int iBaud, int iLen, int iStop, char cParity);
typedef   int(__cdecl *PF_ME3000SIOTRANSMIT)(int iBoardNumber, int iMode, int iCount, char *pcBuffer);
typedef   int(__cdecl *PF_ME3000SIOWRITEREGISTER)(int iBoardNumber, char cReg, char cVal);
typedef   int(__cdecl *PF_ME3000ERRORMESSAGE) (char *pcAppName);
typedef   int(__cdecl *PF_ME3000GETDRIVERERRORSTRING) (char *pcErrorText);




// ---------------- Function Prototypes ------------------------------------

int me3000FileName (int iBoardNumber, int iType, char *pcFileName);
int me3000FrequencyToCounter (double dwFreq);
int me3000GeneralReset (int iBoardNumber);
int me3000GetDLLVersion (void);
int me3000GetDriverVersion (char *pcBuffer);
int me3000GetSerialNumber (int iBoardNumber, int *iSerialNumber);
int me3000GetVECModel (int iBoardNumber, int *iMEVECModel);
int me3000Initialize (int iBoardNumber);
int me3000SetPriority (int iBoardNumber, int iPriority);
int me3000AIAddToChannelList (int iBoardNumber, int iEntry);
int me3000AIClearChannelList (int iBoardNumber);
int me3000AIMakeChannelListEntry (int iChannel,
                                  int iRange,
                                  int iMode,
                                  int *iEntry);
int me3000AIMultiple (int iBoardNumber,
                      short *asBuffer,
                      int iCount,
                      int iMode);
int me3000AIMultipleEx (int iBoardNumber,
                        short *asBuffer,
                        int iCount,
                        int iMode,
                        int iLoops,
                        int iDelay,
                        PSERVICE_PROC pCallBack);
int me3000AIQuick (int iBoardNumber,
                   short *asBuffer,
                   int iCount,
                   int iMode);
int me3000AIQuickEx (int iBoardNumber,
                     short *asBuffer,
                     int iCount,
                     int iMode,
                     int iLoops,
                     int iDelay,
                     PSERVICE_PROC pCallBack);
int me3000AIScan  (int iBoardNumber,
                   short *asBuffer,
                   int iSize,
                   int iCount,
                   int iMode);
int me3000AIScanEx  (int iBoardNumber,
                     short *asBuffer,
                     int iSize,
                     int iCount,
                     int iMode,
                     int iLoops,
                     int iDelay,
                     P_1_PROC pCallBack);
int me3000AISetSimultaneous (int iBoardNumber, int iMode);
int me3000AISetTimer (int iBoardNumber, int iScanFreq, int iChanFreq);
int me3000AISetTrigger (int iBoardNumber, int iModePolarity);
int me3000AISingle (int iBoardNumber, int iChannel, int iMode, short *iValue);
int me3000AISingleEx (int iBoardNumber,
                     int iChannel,
                     int iMode,
                     int iLoops,
                     int iDelay,
                     short *iValue,
                     PSERVICE_PROC pCallBack);
int me3000AIStop (int iBoardNumber);
int me3000AIClearDataFIFO (int iBoardNumber);
int me3000AIReadFIFO(int iBoardNumber, short* asBuffer, int iSize);
int me3000AIStartByExternalTrigger(int iBoardNumber, int iTriggerMode);
int me3000AOAddToDACFIFO (int iBoardNumber, int iEntry);
int me3000AOClearDACFIFO (int iBoardNumber);
int me3000AOContinuous ( int iBoardNumber,
                         int iMode,
                         int iSize,
                         short *asBuffer);
int me3000AOContinuousEx ( int iBoardNumber,
                           int iMode,
                           int iSize,
                           short *asBuffer,
                           int iLoops,
                           int iDelay,
                           PSERVICE_PROC pCallBack);
int me3000AOReset (int iBoardNumber);
int me3000AOSetMode (int iBoardNumber,
                     int iChannel,
                     int iRange,
                     int iMode);
int me3000AOSetTimer (int iBoardNumber, int iTime);
int me3000AOSetTrigger (int iBoardNumber, int iModePolarity);
int me3000AOSingle (int iBoardNumber, int iChannel, short iValue);
int me3000AOStop (int iBoardNumber);
int me3000AOStopEx (int iBoardNumber);
int me3000AOUpdate (int iBoardNumber);
int me3000AOWrapAround (int iBoardNumber);
int me3000DIOSetPortDirection (int iBoardNumber, int iPortNo, int iDir);
int me3000DIGetBit (int iBoardNumber, int iPortNo, int iBitNo, int *iBitValue);
int me3000DIGetByte (int iBoardNumber, int iPortNo, int iByteNo, int *iByteValue);
int me3000DIGetWord (int iBoardNumber, int iPortNo, int *iValue);
int me3000DOReset (int iBoardNumber, int iPortNo);
int me3000DOSetBit (int iBoardNumber, int iPortNo, int iBitNo, int iBitValue);
int me3000DOSetByte (int iBoardNumber, int iPortNo, int iByteNo, int iByteValue);
int me3000DOSetWord (int iBoardNumber, int iPortNo, int iValue);
int me3000PWMSetMode (int iBoardNumber,
                      double dFreq,
                      int iDutyCycle,
                      int iInverted);
int me3000PWMStart (int iBoardNumber);
int me3000PWMStop (int iBoardNumber);
int me3000CNTInterrupt ( int iBoardNumber,
                         int iCounter,
                         int iFlag,
                         PSERVICE_PROC pCallBack);
int me3000CNTRead (int iBoardNumber, int iCounter, short *iCounterValue);
int me3000CNTReset (int iBoardNumber, int iCounter);
int me3000CNTSetRange (int iBoardNumber,
                       int iCounter,
                       int iEndValue,
                       int iStartValue);
int me3000CNTStart (int iBoardNumber, int iCounter);
int me3000DisableExternalInt (int iBoardNumber);
int me3000EnableExternalInt (int iBoardNumber, PSERVICE_PROC pCallBack);
int me3000SIOCheckBuffer (int iBoardNumber, PME3000_SIO_REGS pSIO);
int me3000SIOCheckError (int iBoardNumber);
int me3000SIOClearBuffer (int iBoardNumber);
int me3000SIOClose (int iBoardNumber);
int me3000SIOGetRegisters (int iBoardNumber, PME3000_SIO pBuffer);
int me3000SIOLoopBackTest   (int iBoardNumber); 
int me3000SIOOpen (int iBoardNumber, 
                   int iMode,
                   int iInBufferSize,
                   int iOutBufferSize); 
int me3000SIOReadRegister (int iBoardNumber, char cReg);
int me3000SIOReceive (int iBoardNumber, 
                      int iMode,
                      int iCount,
                      char pcBuffer);
int me3000SIOSetup (int iBoardNumber, 
                    int iBaud,
                    int iLen,
                    int iStop,
                    char cParity);
int me3000SIOTransmit (int iBoardNumber,
                       int iMode,
                       int iCount,
                       char *pcBuffer);
int me3000SIOWriteRegister (int iBoardNumber,
                            char cReg,
                            char cVal);
int me3000ErrorMessage (char *pcAppName);
int me3000GetDriverErrorString (char *pcErrorText);

void meOpen (void);
void meClose (void);


#endif
