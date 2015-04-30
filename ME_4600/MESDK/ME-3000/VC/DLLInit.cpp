/*----------------------------------------------------------------------------
    File: DLLINIT.CPP
------------------------------------------------------------------------------

    Meilhaus Electronic GmbH

    C source file containing wrapper for all DLL functions.  This file is
    for use in projects using dynamic function calls (no library file is
    included in the project)

    Version 1.00:   001012
-------------------------------------------------------------------------------
    Author: Andreas Bernau / Ralph Timm
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include ".\meDefs.h"
#include ".\DLLInit.h"

/*  Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEFILE(".\meDefs.h");
USEFILE(".\DLLInit.h");
#endif



PF_ME3000FILENAME               pf_me3000FileName;
PF_ME3000FREQUENCYTOCOUNTER     pf_me3000FrequencyToCounter;
PF_ME3000GENERALRESET           pf_me3000GeneralReset;
PF_ME3000GETDLLVERSION          pf_me3000GetDLLVersion;
PF_ME3000GETDRIVERVERSION       pf_me3000GetDriverVersion;
PF_ME3000GETSERIALNUMBER        pf_me3000GetSerialNumber;
PF_ME3000GETVECMODEL            pf_me3000GetVECModel;
PF_ME3000INITIALIZE             pf_me3000Initialize;
PF_ME3000SETPRIORITY            pf_me3000SetPriority;
PF_ME3000AIADDTOCHANNELLIST     pf_me3000AIAddToChannelList;
PF_ME3000AICLEARCHANNELLIST     pf_me3000AIClearChannelList;
PF_ME3000AIMAKECHANNELLISTENTRY pf_me3000AIMakeChannelListEntry;
PF_ME3000AIMULTIPLE             pf_me3000AIMultiple;
PF_ME3000AIMULTIPLEEX           pf_me3000AIMultipleEx;
PF_ME3000AIQUICK                pf_me3000AIQuick;
PF_ME3000AIQUICKEX              pf_me3000AIQuickEx;
PF_ME3000AISCAN                 pf_me3000AIScan;
PF_ME3000AISCANEX               pf_me3000AIScanEx;
PF_ME3000AISETSIMULTANEOUS      pf_me3000AISetSimultaneous;
PF_ME3000AISETTIMER             pf_me3000AISetTimer;
PF_ME3000AISETTRIGGER           pf_me3000AISetTrigger;
PF_ME3000AISINGLE               pf_me3000AISingle;
PF_ME3000AISINGLEEX             pf_me3000AISingleEx;
PF_ME3000AISTOP                 pf_me3000AIStop;
PF_ME3000AICLEARDATAFIFO        pf_me3000AIClearDataFIFO;
PF_ME3000AIREADFIFO             pf_me3000AIReadFIFO;
PF_ME3000AISTARTBYEXTERNALTRIGGER   pf_me3000AIStartByExternalTrigger;
PF_ME3000AOADDTODACFIFO         pf_me3000AOAddToDACFIFO;
PF_ME3000AOCLEARDACFIFO         pf_me3000AOClearDACFIFO;
PF_ME3000AOCONTINUOUS           pf_me3000AOContinuous;
PF_ME3000AOCONTINUOUSEX         pf_me3000AOContinuousEx;
PF_ME3000AORESET                pf_me3000AOReset;
PF_ME3000AOSETMODE              pf_me3000AOSetMode;
PF_ME3000AOSETTIMER             pf_me3000AOSetTimer;
PF_ME3000AOSETTRIGGER           pf_me3000AOSetTrigger;
PF_ME3000AOSINGLE               pf_me3000AOSingle;
PF_ME3000AOSTOP                 pf_me3000AOStop;
PF_ME3000AOSTOPEX               pf_me3000AOStopEx;
PF_ME3000AOUPDATE               pf_me3000AOUpdate;
PF_ME3000AOWRAPAROUND           pf_me3000AOWrapAround;
PF_ME3000DIOSETPORTDIRECTION    pf_me3000DIOSetPortDirection;
PF_ME3000DIGETBIT               pf_me3000DIGetBit;
PF_ME3000DIGETBYTE              pf_me3000DIGetByte;
PF_ME3000DIGETWORD              pf_me3000DIGetWord;
PF_ME3000DORESET                pf_me3000DOReset;
PF_ME3000DOSETBIT               pf_me3000DOSetBit;
PF_ME3000DOSETBYTE              pf_me3000DOSetByte;
PF_ME3000DOSETWORD              pf_me3000DOSetWord;
PF_ME3000PWMSETMODE             pf_me3000PWMSetMode;
PF_ME3000PWMSTART               pf_me3000PWMStart;
PF_ME3000PWMSTOP                pf_me3000PWMStop;
PF_ME3000CNTINTERRUPT           pf_me3000CNTInterrupt;
PF_ME3000CNTREAD                pf_me3000CNTRead;
PF_ME3000CNTRESET               pf_me3000CNTReset;
PF_ME3000CNTSETRANGE            pf_me3000CNTSetRange;
PF_ME3000CNTSTART               pf_me3000CNTStart;
PF_ME3000DISABLEEXTERNALINT     pf_me3000DisableExternalInt;
PF_ME3000ENABLEEXTERNALINT      pf_me3000EnableExternalInt;
PF_ME3000SIOCHECKBUFFER         pf_me3000SIOCheckBuffer;
PF_ME3000SIOCHECKERROR          pf_me3000SIOCheckError;
PF_ME3000SIOCLEARBUFFER         pf_me3000SIOClearBuffer;
PF_ME3000SIOCLOSE               pf_me3000SIOClose;
PF_ME3000SIOGETREGISTERS        pf_me3000SIOGetRegisters;
PF_ME3000SIOLOOPBACKTEST        pf_me3000SIOLoopBackTest;
PF_ME3000SIOOPEN                pf_me3000SIOOpen;
PF_ME3000SIOREADREGISTER        pf_me3000SIOReadRegister;
PF_ME3000SIORECEIVE             pf_me3000SIOReceive;
PF_ME3000SIOSETUP               pf_me3000SIOSetup;
PF_ME3000SIOTRANSMIT            pf_me3000SIOTransmit;
PF_ME3000SIOWRITEREGISTER       pf_me3000SIOWriteRegister;
PF_ME3000ERRORMESSAGE           pf_me3000ErrorMessage;
PF_ME3000GETDRIVERERRORSTRING   pf_me3000GetDriverErrorString;


HINSTANCE hDll;


void meOpen (void)
{
    hDll = LoadLibrary(DLLNAME);
    if (hDll == NULL)
    {
        MessageBox( NULL, "DLL not Found", "Error", MB_OK | MB_ICONINFORMATION );
        exit(1);
    }

    pf_me3000FileName = (PF_ME3000FILENAME)
                       (GetProcAddress (hDll,"me3000FileName"));

    pf_me3000FrequencyToCounter = (PF_ME3000FREQUENCYTOCOUNTER)
                       (GetProcAddress (hDll,"me3000FrequencyToCounter"));

    pf_me3000GeneralReset = (PF_ME3000GENERALRESET)
                       (GetProcAddress (hDll,"me3000GeneralReset"));

    pf_me3000GetDLLVersion = (PF_ME3000GETDLLVERSION)
                       (GetProcAddress (hDll,"me3000GetDLLVersion"));

    pf_me3000GetDriverVersion = (PF_ME3000GETDRIVERVERSION)
                       (GetProcAddress (hDll,"me3000GetDriverVersion"));

    pf_me3000GetSerialNumber = (PF_ME3000GETSERIALNUMBER)
                       (GetProcAddress (hDll,"me3000GetSerialNumber"));

    pf_me3000GetVECModel = (PF_ME3000GETVECMODEL)
                       (GetProcAddress (hDll,"me3000GetVECModel"));

    pf_me3000Initialize = (PF_ME3000INITIALIZE)
                       (GetProcAddress (hDll,"me3000Initialize"));

    pf_me3000SetPriority = (PF_ME3000SETPRIORITY)
                       (GetProcAddress (hDll,"me3000SetPriority"));

    pf_me3000AIAddToChannelList = (PF_ME3000AIADDTOCHANNELLIST)
                       (GetProcAddress (hDll,"me3000AIAddToChannelList"));

    pf_me3000AIClearChannelList = (PF_ME3000AICLEARCHANNELLIST)
                       (GetProcAddress (hDll,"me3000AIClearChannelList"));

    pf_me3000AIMakeChannelListEntry = (PF_ME3000AIMAKECHANNELLISTENTRY)
                       (GetProcAddress (hDll,"me3000AIMakeChannelListEntry"));

    pf_me3000AIMultiple = (PF_ME3000AIMULTIPLE)
                       (GetProcAddress (hDll,"me3000AIMultiple"));

    pf_me3000AIMultipleEx = (PF_ME3000AIMULTIPLEEX)
                       (GetProcAddress (hDll,"me3000AIMultipleEx"));

    pf_me3000AIQuick = (PF_ME3000AIQUICK)
                       (GetProcAddress (hDll,"me3000AIQuick"));

    pf_me3000AIQuickEx = (PF_ME3000AIQUICKEX)
                       (GetProcAddress (hDll,"me3000AIQuickEx"));

    pf_me3000AIScan = (PF_ME3000AISCAN)
                       (GetProcAddress (hDll,"me3000AIScan"));

    pf_me3000AIScanEx = (PF_ME3000AISCANEX)
                       (GetProcAddress (hDll,"me3000AIScanEx"));

    pf_me3000AISetSimultaneous = (PF_ME3000AISETSIMULTANEOUS)
                       (GetProcAddress (hDll,"me3000AISetSimultaneous"));

    pf_me3000AISetTimer = (PF_ME3000AISETTIMER)
                       (GetProcAddress (hDll,"me3000AISetTimer"));

    pf_me3000AISetTrigger = (PF_ME3000AISETTRIGGER)
                       (GetProcAddress (hDll,"me3000AISetTrigger"));

    pf_me3000AISingle = (PF_ME3000AISINGLE)
                       (GetProcAddress (hDll,"me3000AISingle"));

    pf_me3000AISingleEx = (PF_ME3000AISINGLEEX)
                       (GetProcAddress (hDll,"me3000AISingleEx"));

    pf_me3000AIStop = (PF_ME3000AISTOP)
                       (GetProcAddress (hDll,"me3000AIStop"));

    pf_me3000AIClearDataFIFO = (PF_ME3000AICLEARDATAFIFO)
                       (GetProcAddress (hDll,"me3000AIClearDataFIFO"));

    pf_me3000AIReadFIFO = (PF_ME3000AIREADFIFO)
                       (GetProcAddress (hDll,"me3000AIReadFIFO"));

    pf_me3000AIStartByExternalTrigger = (PF_ME3000AISTARTBYEXTERNALTRIGGER)
                       (GetProcAddress (hDll,"me3000AIStartByExternalTrigger"));

    pf_me3000AOAddToDACFIFO = (PF_ME3000AOADDTODACFIFO)
                       (GetProcAddress (hDll,"me3000AOAddToDACFIFO"));

    pf_me3000AOClearDACFIFO = (PF_ME3000AOCLEARDACFIFO)
                       (GetProcAddress (hDll,"me3000AOClearDACFIFO"));

    pf_me3000AOContinuous = (PF_ME3000AOCONTINUOUS)
                       (GetProcAddress (hDll,"me3000AOContinuous"));

    pf_me3000AOContinuousEx = (PF_ME3000AOCONTINUOUSEX)
                       (GetProcAddress (hDll,"me3000AOContinuousEx"));

    pf_me3000AOReset = (PF_ME3000AORESET)
                       (GetProcAddress (hDll,"me3000AOReset"));

    pf_me3000AOSetMode = (PF_ME3000AOSETMODE)
                       (GetProcAddress (hDll,"me3000AOSetMode"));

    pf_me3000AOSetTimer = (PF_ME3000AOSETTIMER)
                       (GetProcAddress (hDll,"me3000AOSetTimer"));

    pf_me3000AOSetTrigger = (PF_ME3000AOSETTRIGGER)
                       (GetProcAddress (hDll,"me3000AOSetTrigger"));

    pf_me3000AOSingle = (PF_ME3000AOSINGLE)
                       (GetProcAddress (hDll,"me3000AOSingle"));

    pf_me3000AOStop = (PF_ME3000AOSTOP)
                       (GetProcAddress (hDll,"me3000AOStop"));

    pf_me3000AOStopEx = (PF_ME3000AOSTOPEX)
                       (GetProcAddress (hDll,"me3000AOStopEx"));

    pf_me3000AOUpdate = (PF_ME3000AOUPDATE)
                       (GetProcAddress (hDll,"me3000AOUpdate"));

    pf_me3000AOWrapAround = (PF_ME3000AOWRAPAROUND)
                       (GetProcAddress (hDll,"me3000AOWrapAround"));

    pf_me3000DIOSetPortDirection = (PF_ME3000DIOSETPORTDIRECTION)
                       (GetProcAddress (hDll,"me3000DIOSetPortDirection"));

    pf_me3000DIGetBit = (PF_ME3000DIGETBIT)
                       (GetProcAddress (hDll,"me3000DIGetBit"));

    pf_me3000DIGetByte = (PF_ME3000DIGETBYTE)
                       (GetProcAddress (hDll,"me3000DIGetByte"));

    pf_me3000DIGetWord = (PF_ME3000DIGETWORD)
                       (GetProcAddress (hDll,"me3000DIGetWord"));

    pf_me3000DOReset = (PF_ME3000DORESET)
                       (GetProcAddress (hDll,"me3000DOReset"));

    pf_me3000DOReset = (PF_ME3000DORESET)
                       (GetProcAddress (hDll,"me3000DOReset"));

    pf_me3000DOSetBit = (PF_ME3000DOSETBIT)
                       (GetProcAddress (hDll,"me3000DOSetBit"));

    pf_me3000DOSetByte = (PF_ME3000DOSETBYTE)
                       (GetProcAddress (hDll,"me3000DOSetByte"));

    pf_me3000DOSetWord = (PF_ME3000DOSETWORD)
                       (GetProcAddress (hDll,"me3000DOSetWord"));

    pf_me3000PWMSetMode = (PF_ME3000PWMSETMODE)
                       (GetProcAddress (hDll,"me3000PWMSetMode"));

    pf_me3000PWMStart = (PF_ME3000PWMSTART)
                       (GetProcAddress (hDll,"me3000PWMStart"));

    pf_me3000PWMStop = (PF_ME3000PWMSTOP)
                       (GetProcAddress (hDll,"me3000PWMStop"));

    pf_me3000CNTInterrupt = (PF_ME3000CNTINTERRUPT)
                       (GetProcAddress (hDll,"me3000CNTInterrupt"));

    pf_me3000CNTRead = (PF_ME3000CNTREAD)
                       (GetProcAddress (hDll,"me3000CNTRead"));

    pf_me3000CNTReset = (PF_ME3000CNTRESET)
                       (GetProcAddress (hDll,"me3000CNTReset"));

    pf_me3000CNTSetRange = (PF_ME3000CNTSETRANGE)
                       (GetProcAddress (hDll,"me3000CNTSetRange"));

    pf_me3000CNTStart = (PF_ME3000CNTSTART)
                       (GetProcAddress (hDll,"me3000CNTStart"));

    pf_me3000DisableExternalInt = (PF_ME3000DISABLEEXTERNALINT)
                       (GetProcAddress (hDll,"me3000DisableExternalInt"));

    pf_me3000EnableExternalInt = (PF_ME3000ENABLEEXTERNALINT)
                       (GetProcAddress (hDll,"me3000EnableExternalInt"));

    pf_me3000SIOCheckBuffer = (PF_ME3000SIOCHECKBUFFER)
                       (GetProcAddress (hDll,"me3000SIOCheckBuffer"));

    pf_me3000SIOCheckError = (PF_ME3000SIOCHECKERROR)
                       (GetProcAddress (hDll,"me3000SIOCheckError"));

    pf_me3000SIOClearBuffer = (PF_ME3000SIOCLEARBUFFER)
                       (GetProcAddress (hDll,"me3000SIOClearBuffer"));

    pf_me3000SIOClose = (PF_ME3000SIOCLOSE)
                       (GetProcAddress (hDll,"me3000SIOClose"));

    pf_me3000SIOGetRegisters = (PF_ME3000SIOGETREGISTERS)
                       (GetProcAddress (hDll,"me3000SIOGetRegisters"));

    pf_me3000SIOLoopBackTest = (PF_ME3000SIOLOOPBACKTEST)
                       (GetProcAddress (hDll,"me3000SIOLoopBackTest"));

    pf_me3000SIOOpen = (PF_ME3000SIOOPEN)
                       (GetProcAddress (hDll,"me3000SIOOpen"));

    pf_me3000SIOReadRegister = (PF_ME3000SIOREADREGISTER)
                       (GetProcAddress (hDll,"me3000SIOReadRegister"));

    pf_me3000SIOReceive = (PF_ME3000SIORECEIVE)
                       (GetProcAddress (hDll,"me3000SIOReceive"));

    pf_me3000SIOSetup = (PF_ME3000SIOSETUP)
                       (GetProcAddress (hDll,"me3000SIOSetup"));

    pf_me3000SIOTransmit = (PF_ME3000SIOTRANSMIT)
                       (GetProcAddress (hDll,"me3000SIOTransmit"));

    pf_me3000SIOWriteRegister = (PF_ME3000SIOWRITEREGISTER)
                       (GetProcAddress (hDll,"me3000SIOWriteRegister"));

    pf_me3000ErrorMessage = (PF_ME3000ERRORMESSAGE)
                       (GetProcAddress (hDll,"me3000ErrorMessage"));

    pf_me3000GetDriverErrorString = (PF_ME3000GETDRIVERERRORSTRING)
                       (GetProcAddress (hDll,"me3000GetDriverErrorString"));

}




//   -------------------- Wrappers for all Functions -------------------------

int me3000FileName (int iBoardNumber, int iType, char *pcFileName)
{
    if (pf_me3000FileName)
        return (pf_me3000FileName)(iBoardNumber, iType, pcFileName);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me3000FrequencyToCounter (double dwFreq)
{
    if (pf_me3000FrequencyToCounter)
        return (pf_me3000FrequencyToCounter)( dwFreq);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000GeneralReset (int iBoardNumber)
{
    if (pf_me3000GeneralReset)
        return (pf_me3000GeneralReset)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000GetDLLVersion (void)
{
    if (pf_me3000GetDLLVersion)
        return (pf_me3000GetDLLVersion)();
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000GetDriverVersion (char *pcBuffer)
{
    if (pf_me3000GetDriverVersion)
        return (pf_me3000GetDriverVersion)(pcBuffer);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000GetSerialNumber (int iBoardNumber, int *iSerialNumber)
{
    if (pf_me3000GetSerialNumber)
        return (pf_me3000GetSerialNumber)(iBoardNumber, iSerialNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000GetVECModel (int iBoardNumber, int *iMEVECModel)
{
    if (pf_me3000GetVECModel)
        return (pf_me3000GetVECModel)(iBoardNumber, iMEVECModel);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000Initialize (int iBoardNumber)
{
    if (pf_me3000Initialize)
        return (pf_me3000Initialize)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SetPriority (int iBoardNumber, int iPriority)
{
    if (pf_me3000SetPriority)
        return (pf_me3000SetPriority)(iBoardNumber, iPriority);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me3000AIAddToChannelList (int iBoardNumber, int iEntry)
{
    if (pf_me3000AIAddToChannelList)
        return (pf_me3000AIAddToChannelList)(iBoardNumber, iEntry);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIClearChannelList (int iBoardNumber)
{
    if (pf_me3000AIClearChannelList)
        return (pf_me3000AIClearChannelList)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIMakeChannelListEntry (int iChannel,
                                  int iRange,
                                  int iMode,
                                  int *iEntry)
{
    if (pf_me3000AIMakeChannelListEntry)
        return (pf_me3000AIMakeChannelListEntry)(iChannel, iRange,
                                                        iMode, iEntry);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIMultiple (int iBoardNumber,
                      short *asBuffer,
                      int iCount,
                      int iMode)
{
    if (pf_me3000AIMultiple)
        return (pf_me3000AIMultiple)(iBoardNumber, asBuffer, iCount, iMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIMultipleEx (int iBoardNumber,
                        short *asBuffer,
                        int iCount,
                        int iMode,
                        int iLoops,
                        int iDelay,
                        PSERVICE_PROC pCallBack)
{
    if (pf_me3000AIMultipleEx)
        return (pf_me3000AIMultipleEx)(iBoardNumber, asBuffer, iCount, iMode,
                                                    iLoops, iDelay, pCallBack);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIQuick (int iBoardNumber,
                   short *asBuffer,
                   int iCount,
                   int iMode)
{
    if (pf_me3000AIQuick)
        return (pf_me3000AIQuick)(iBoardNumber, asBuffer, iCount, iMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIQuickEx (int iBoardNumber,
                     short *asBuffer,
                     int iCount,
                     int iMode,
                     int iLoops,
                     int iDelay,
                     PSERVICE_PROC pCallBack)
{
    if (pf_me3000AIQuickEx)
        return (pf_me3000AIQuickEx)(iBoardNumber, asBuffer, iCount, iMode,
                                                    iLoops, iDelay, pCallBack);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIScan  (int iBoardNumber,
                   short *asBuffer,
                   int iSize,
                   int iCount,
                   int iMode)
{
    if (pf_me3000AIScan)
        return (pf_me3000AIScan)(iBoardNumber, asBuffer, iSize, iCount, iMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIScanEx  (int iBoardNumber,
                     short *asBuffer,
                     int iSize,
                     int iCount,
                     int iMode,
                     int iLoops,
                     int iDelay,
                     P_1_PROC pCallBack)
{
    if (pf_me3000AIScanEx)
        return (pf_me3000AIScanEx)(iBoardNumber, asBuffer, iSize, iCount, iMode,
                                                    iLoops, iDelay, pCallBack);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AISetSimultaneous (int iBoardNumber, int iMode)
{
    if (pf_me3000AISetSimultaneous)
        return (pf_me3000AISetSimultaneous)(iBoardNumber, iMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }

}
int me3000AISetTimer (int iBoardNumber,
                      int iScan,
                      int iChan)
{
    if (pf_me3000AISetTimer)
        return (pf_me3000AISetTimer)(iBoardNumber, iScan, iChan);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AISetTrigger (int iBoardNumber, int iModePolarity)
{
    if (pf_me3000AISetTrigger)
        return (pf_me3000AISetTrigger)(iBoardNumber, iModePolarity);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AISingle (int iBoardNumber, int iChannel, int iMode, short *iValue)
{
    if (pf_me3000AISingle)
        return (pf_me3000AISingle)(iBoardNumber, iChannel, iMode, iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AISingleEx (int iBoardNumber,
                     int iChannel,
                     int iMode,
                     int iLoops,
                     int iDelay,
                     short *iValue,
                     PSERVICE_PROC pCallBack)
{
    if (pf_me3000AISingleEx)
        return (pf_me3000AISingleEx)(iBoardNumber, iChannel, iMode, iLoops,
                                                    iDelay, iValue, pCallBack);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AIStop (int iBoardNumber)
{
    if (pf_me3000AIStop)
        return (pf_me3000AIStop)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int  me3000AIClearDataFIFO (int iBoardNumber)
{
    if (pf_me3000AIClearDataFIFO)
        return (pf_me3000AIClearDataFIFO)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int  me3000AIReadFIFO(int iBoardNumber, short* asBuffer, int iSize)
{
    if (pf_me3000AIReadFIFO)
        return (pf_me3000AIReadFIFO)(iBoardNumber, asBuffer, iSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int  me3000AIStartByExternalTrigger(int iBoardNumber, int iTriggerMode)
{
    if (pf_me3000AIStartByExternalTrigger)
        return (pf_me3000AIStartByExternalTrigger)(iBoardNumber, iTriggerMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me3000AOAddToDACFIFO (int iBoardNumber, int iEntry)
{
    if (pf_me3000AOAddToDACFIFO)
        return (pf_me3000AOAddToDACFIFO)(iBoardNumber, iEntry);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOClearDACFIFO (int iBoardNumber)
{
    if (pf_me3000AOClearDACFIFO)
        return (pf_me3000AOClearDACFIFO)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOContinuous ( int iBoardNumber,
                         int iMode,
                         int iSize,
                         short *asBuffer)
{
    if (pf_me3000AOContinuous)
        return (pf_me3000AOContinuous)(iBoardNumber, iMode, iSize, asBuffer);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOContinuousEx ( int iBoardNumber,
                           int iMode,
                           int iSize,
                           short *asBuffer,
                           int iLoops,
                           int iDelay,
                           PSERVICE_PROC pCallBack)
{
    if (pf_me3000AOContinuousEx)
        return (pf_me3000AOContinuousEx)(iBoardNumber, iMode, iSize, asBuffer,
                                            iLoops, iDelay, pCallBack);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOReset (int iBoardNumber)
{
    if (pf_me3000AOReset)
        return (pf_me3000AOReset)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOSetMode (int iBoardNumber,
                     int iChannel,
                     int iRange,
                     int iMode)
{
    if (pf_me3000AOSetMode)
        return (pf_me3000AOSetMode)(iBoardNumber, iChannel, iRange, iMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOSetTimer (int iBoardNumber, int iTime)
{
    if (pf_me3000AOSetTimer)
        return (pf_me3000AOSetTimer)(iBoardNumber, iTime);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOSetTrigger (int iBoardNumber, int iModePolarity)
{
    if (pf_me3000AOSetTrigger)
        return (pf_me3000AOSetTrigger)(iBoardNumber, iModePolarity);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOSingle (int iBoardNumber, int iChannel, short iValue)
{
    if (pf_me3000AOSingle)
        return (pf_me3000AOSingle)(iBoardNumber, iChannel, iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOStop (int iBoardNumber)
{
    if (pf_me3000AOStop)
        return (pf_me3000AOStop)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOStopEx (int iBoardNumber)
{
    if (pf_me3000AOStopEx)
        return (pf_me3000AOStopEx)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOUpdate (int iBoardNumber)
{
    if (pf_me3000AOUpdate)
        return (pf_me3000AOUpdate)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000AOWrapAround (int iBoardNumber)
{
    if (pf_me3000AOWrapAround)
        return (pf_me3000AOWrapAround)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me3000DIOSetPortDirection (int iBoardNumber, int iPortNo, int iDir)
{
    if (pf_me3000DIOSetPortDirection)
        return (pf_me3000DIOSetPortDirection)(iBoardNumber, iPortNo, iDir);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000DIGetBit (int iBoardNumber, int iPortNo, int iBitNo, int *iBitValue)
{
    if (pf_me3000DIGetBit)
        return (pf_me3000DIGetBit)(iBoardNumber, iPortNo, iBitNo, iBitValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000DIGetByte (int iBoardNumber, int iPortNo, int iByteNo, int *iByteValue)
{
    if (pf_me3000DIGetByte)
        return (pf_me3000DIGetByte)(iBoardNumber, iPortNo, iByteNo, iByteValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000DIGetWord (int iBoardNumber, int iPortNo, int *iValue)
{
    if (pf_me3000DIGetWord)
        return (pf_me3000DIGetWord)(iBoardNumber, iPortNo, iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000DOReset (int iBoardNumber, int iPortNo)
{
    if (pf_me3000DOReset)
        return (pf_me3000DOReset)(iBoardNumber, iPortNo);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000DOSetBit (int iBoardNumber, int iPortNo, int iBitNo, int iBitValue)
{
    if (pf_me3000DOSetBit)
        return (pf_me3000DOSetBit)(iBoardNumber, iPortNo, iBitNo, iBitValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000DOSetByte (int iBoardNumber, int iPortNo, int iByteNo, int iByteValue)
{
    if (pf_me3000DOSetByte)
        return (pf_me3000DOSetByte)(iBoardNumber, iPortNo, iByteNo, iByteValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000DOSetWord (int iBoardNumber, int iPortNo, int iValue)
{
    if (pf_me3000DOSetWord)
        return (pf_me3000DOSetWord)(iBoardNumber, iPortNo, iValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me3000PWMSetMode (int iBoardNumber, double dFreq, int iDutyCycle, int iInverted)
{
    if (pf_me3000PWMSetMode)
        return (pf_me3000PWMSetMode)(iBoardNumber, dFreq, iDutyCycle, iInverted);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000PWMStart (int iBoardNumber)
{
    if (pf_me3000PWMStart)
        return (pf_me3000PWMStart)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000PWMStop (int iBoardNumber)
{
    if (pf_me3000PWMStop)
        return (pf_me3000PWMStop)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000CNTInterrupt ( int iBoardNumber,
                         int iCounter,
                         int iFlag,
                         PSERVICE_PROC pCallBack)
{
    if (pf_me3000CNTInterrupt)
        return (pf_me3000CNTInterrupt)(iBoardNumber, iCounter, iFlag, pCallBack);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000CNTRead (int iBoardNumber, int iCounter, short *iCounterValue)
{
    if (pf_me3000CNTRead)
        return (pf_me3000CNTRead)(iBoardNumber, iCounter, iCounterValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000CNTReset (int iBoardNumber, int iCounter)
{
    if (pf_me3000CNTReset)
        return (pf_me3000CNTReset)(iBoardNumber, iCounter);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000CNTSetRange (int iBoardNumber, int iCounter, int iEndValue, int iStartValue)
{
    if (pf_me3000CNTSetRange)
        return (pf_me3000CNTSetRange)(iBoardNumber, iCounter, iEndValue, iStartValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000CNTStart (int iBoardNumber, int iCounter)
{
    if (pf_me3000CNTStart)
        return (pf_me3000CNTStart)(iBoardNumber, iCounter);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000DisableExternalInt (int iBoardNumber)
{
    if (pf_me3000DisableExternalInt)
        return (pf_me3000DisableExternalInt)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000EnableExternalInt (int iBoardNumber, PSERVICE_PROC pCallBack)
{
    if (pf_me3000EnableExternalInt)
        return (pf_me3000EnableExternalInt)(iBoardNumber, pCallBack);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me3000SIOCheckBuffer (int iBoardNumber, PME3000_SIO_REGS pSIO)
{
    if (pf_me3000SIOCheckBuffer)
        return (pf_me3000SIOCheckBuffer)(iBoardNumber, pSIO);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOCheckError (int iBoardNumber)
{
    if (pf_me3000SIOCheckError)
        return (pf_me3000SIOCheckError)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOClearBuffer (int iBoardNumber)
{
    if (pf_me3000SIOClearBuffer)
        return (pf_me3000SIOClearBuffer)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOClose (int iBoardNumber)
{
    if (pf_me3000SIOClose)
        return (pf_me3000SIOClose)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOGetRegisters (int iBoardNumber, PME3000_SIO pBuffer)
{
    if (pf_me3000SIOGetRegisters)
        return (pf_me3000SIOGetRegisters)(iBoardNumber, pBuffer);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOLoopBackTest (int iBoardNumber)
{
    if (pf_me3000SIOLoopBackTest)
        return (pf_me3000SIOLoopBackTest)(iBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOOpen (int iBoardNumber,
                   int iMode,
                   int iInBufferSize,
                   int iOutBufferSize)
{
    if (pf_me3000SIOOpen)
        return (pf_me3000SIOOpen)(iBoardNumber, iMode, iInBufferSize, iOutBufferSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOReadRegister (int iBoardNumber, char cReg)
{
    if (pf_me3000SIOReadRegister)
        return (pf_me3000SIOReadRegister)(iBoardNumber, cReg);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOReceive (int iBoardNumber,
                      int iMode,
                      int iCount,
                      char pcBuffer)
{
    if (pf_me3000SIOReceive)
        return (pf_me3000SIOReceive)(iBoardNumber, iMode, iCount, pcBuffer);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOSetup (int iBoardNumber,
                    int iBaud,
                    int iLen,
                    int iStop,
                    char cParity)
{
    if (pf_me3000SIOSetup)
        return (pf_me3000SIOSetup)(iBoardNumber, iBaud, iLen, iStop, cParity);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOTransmit (int iBoardNumber,
                       int iMode,
                       int iCount,
                       char *pcBuffer)
{
    if (pf_me3000SIOTransmit)
        return (pf_me3000SIOTransmit)(iBoardNumber, iMode, iCount, pcBuffer);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000SIOWriteRegister (int iBoardNumber,
                            char cReg,
                            char cVal)
{
    if (pf_me3000SIOWriteRegister)
        return (pf_me3000SIOWriteRegister)(iBoardNumber, cReg, cVal);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000ErrorMessage (char *pcAppName)
{
    if (pf_me3000ErrorMessage)
        return (pf_me3000ErrorMessage)(pcAppName);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me3000GetDriverErrorString (char *pcErrorText)
{
    if (pf_me3000GetDriverErrorString)
        return (pf_me3000GetDriverErrorString)(pcErrorText);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}



/* -------------------------  Close Function ----------------------------*/

void meClose (void)
{
    FreeLibrary (hDll);    //  close the library
}
