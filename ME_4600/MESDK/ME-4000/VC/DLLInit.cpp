/*----------------------------------------------------------------------------
    File: DLLINIT.CPP
------------------------------------------------------------------------------ 

    Meilhaus Electronic GmbH

    C source file containing wrapper for all DLL functions.  This file is
    for use in projects using dynamic function calls (no library file is
    included in the project)

    Version 1.00:   001012
-------------------------------------------------------------------------------
    Author: Andreas Bernau
-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include ".\me4000defs.h"
#include ".\DLLInit.h"

/*  Definitions  used for Borland C only */
#ifdef __BORLANDC__
#include <condefs.h>
USEFILE("..\me4000defs.h");
USEFILE(".\DLLInit.h");
USEUNIT(".\DLLInit.cpp");
#endif

PF_ME4000ERRORSETDEFAULTPROC       pf_me4000ErrorSetDefaultProc;
PF_ME4000ERRORSETUSERPROC          pf_me4000ErrorSetUserProc;
PF_ME4000ERRORGETMESSAGE           pf_me4000ErrorGetMessage;
PF_ME4000ERRORGETLASTMESSAGE       pf_me4000ErrorGetLastMessage;
PF_ME4000GETDLLVERSION             pf_me4000GetDLLVersion;
PF_ME4000GETDRIVERVERSION          pf_me4000GetDriverVersion;
PF_ME4000FREQUENCYTOTICKS          pf_me4000FrequencyToTicks;
PF_ME4000TIMETOTICKS               pf_me4000TimeToTicks;
PF_ME4000GETBOARDVERSION           pf_me4000GetBoardVersion;
PF_ME4000GETSERIALNUMBER           pf_me4000GetSerialNumber;
PF_ME4000AISINGLE                  pf_me4000AISingle;
PF_ME4000AIMAKECHANNELLISTENTRY    pf_me4000AIMakeChannelListEntry;
PF_ME4000AICONFIG                  pf_me4000AIConfig;
PF_ME4000AISCAN                    pf_me4000AIScan;
PF_ME4000AICONTINUOUS              pf_me4000AIContinuous;
PF_ME4000AISTART                   pf_me4000AIStart;
PF_ME4000AIGETNEWVALUES            pf_me4000AIGetNewValues;
PF_ME4000AISTOP                    pf_me4000AIStop;
PF_ME4000AIEXTRACTVALUES           pf_me4000AIExtractValues;
PF_ME4000AIDIGITTOVOLT             pf_me4000AIDigitToVolt;
PF_ME4000AIRESET                   pf_me4000AIReset;
PF_ME4000AIGETSTATUS               pf_me4000AIGetStatus;
PF_ME4000AOSINGLE                  pf_me4000AOSingle;
PF_ME4000AOSINGLESIMULTANEOUS      pf_me4000AOSingleSimultaneous;
PF_ME4000AOUPDATE                  pf_me4000AOUpdate;
PF_ME4000AOCONFIG                  pf_me4000AOConfig;
PF_ME4000AOWRAPAROUND              pf_me4000AOWraparound;
PF_ME4000AOCONTINUOUS              pf_me4000AOContinuous;
PF_ME4000AOSTART                   pf_me4000AOStart;
PF_ME4000AOSTARTSYNCHRONOUS        pf_me4000AOStartSynchronous;
PF_ME4000AOAPPENDNEWVALUES         pf_me4000AOAppendNewValues;
PF_ME4000AOSTOP                    pf_me4000AOStop;
PF_ME4000AOVOLTTODIGIT             pf_me4000AOVoltToDigit;
PF_ME4000AORESET                   pf_me4000AOReset;
PF_ME4000AOWAVEGEN                 pf_me4000AOWaveGen;
PF_ME4000AOGETSTATUS               pf_me4000AOGetStatus;
PF_ME4000DIOCONFIG                 pf_me4000DIOConfig;
PF_ME4000DIORESETALL               pf_me4000DIOResetAll;
PF_ME4000DIOGETBIT                 pf_me4000DIOGetBit;
PF_ME4000DIOGETBYTE                pf_me4000DIOGetByte;
PF_ME4000DIOSETBIT                 pf_me4000DIOSetBit;
PF_ME4000DIOSETBYTE                pf_me4000DIOSetByte;
PF_ME4000CNTWRITE                  pf_me4000CntWrite;
PF_ME4000CNTREAD                   pf_me4000CntRead;
PF_ME4000CNTPWMSTART               pf_me4000CntPWMStart;
PF_ME4000CNTPWMSTOP                pf_me4000CntPWMStop;
PF_ME4000EXTIRQENABLE              pf_me4000ExtIrqEnable;
PF_ME4000EXTIRQDISABLE             pf_me4000ExtIrqDisable;
PF_ME4000EXTIRQGETCOUNT            pf_me4000ExtIrqGetCount;
PF_ME4000DIOBPPORTCONFIG           pf_me4000DIOBPPortConfig;
PF_ME4000DIOBPCONFIG               pf_me4000DIOBPConfig;
PF_ME4000DIOBPWRAPAROUND           pf_me4000DIOBPWraparound;
PF_ME4000DIOBPCONTINUOUS           pf_me4000DIOBPContinuous;
PF_ME4000DIOBPSTART                pf_me4000DIOBPStart;
PF_ME4000DIOBPAPPENDNEWVALUES      pf_me4000DIOBPAppendNewValues;
PF_ME4000DIOBPSTOP                 pf_me4000DIOBPStop;
PF_ME4000DIOBPRESET                pf_me4000DIOBPReset;
PF_ME4000DIOBPGETSTATUS            pf_me4000DIOBPGetStatus;
PF_ME4000MULTISIGOPEN              pf_me4000MultiSigOpen;
PF_ME4000MULTISIGRESET             pf_me4000MultiSigReset;
PF_ME4000MULTISIGADDRESSLED        pf_me4000MultiSigAddressLED;
PF_ME4000MULTISIGSETGAIN           pf_me4000MultiSigSetGain;
PF_ME4000MULTISIGCLOSE             pf_me4000MultiSigClose;
PF_ME4000MULTISIGAIOPEN            pf_me4000MultiSigAIOpen;
PF_ME4000MULTISIGAISINGLE          pf_me4000MultiSigAISingle;
PF_ME4000MULTISIGAICONFIG          pf_me4000MultiSigAIConfig;
PF_ME4000MULTISIGAISCAN            pf_me4000MultiSigAIScan;
PF_ME4000MULTISIGAICONTINUOUS      pf_me4000MultiSigAIContinuous;
PF_ME4000MULTISIGAISTART           pf_me4000MultiSigAIStart;
PF_ME4000MULTISIGAIGETNEWVALUES    pf_me4000MultiSigAIGetNewValues;
PF_ME4000MULTISIGAISTOP            pf_me4000MultiSigAIStop;
PF_ME4000MULTISIGAIEXTRACTVALUES   pf_me4000MultiSigAIExtractValues;
PF_ME4000MULTISIGAIDIGITTOSIZE     pf_me4000MultiSigAIDigitToSize;
PF_ME4000MULTISIGAIRESET           pf_me4000MultiSigAIReset;
PF_ME4000MULTISIGAIGETSTATUS       pf_me4000MultiSigAIGetStatus;
PF_ME4000MULTISIGAICLOSE           pf_me4000MultiSigAIClose;
PF_ME4000MULTISIGAOOPEN            pf_me4000MultiSigAOOpen;
PF_ME4000MULTISIGAOSINGLE          pf_me4000MultiSigAOSingle;
PF_ME4000MULTISIGAOCONFIG          pf_me4000MultiSigAOConfig;
PF_ME4000MULTISIGAOWRAPAROUND      pf_me4000MultiSigAOWraparound;
PF_ME4000MULTISIGAOCONTINUOUS      pf_me4000MultiSigAOContinuous;
PF_ME4000MULTISIGAOSTART           pf_me4000MultiSigAOStart;
PF_ME4000MULTISIGAOAPPENDNEWVALUES pf_me4000MultiSigAOAppendNewValues;
PF_ME4000MULTISIGAOSTOP            pf_me4000MultiSigAOStop;
PF_ME4000MULTISIGAOVOLTTODIGIT     pf_me4000MultiSigAOVoltToDigit;
PF_ME4000MULTISIGAORESET           pf_me4000MultiSigAOReset;
PF_ME4000MULTISIGAOGETSTATUS       pf_me4000MultiSigAOGetStatus;
PF_ME4000MULTISIGAOCLOSE           pf_me4000MultiSigAOClose;
PF_ME6000ERRORSETDEFAULTPROC       pf_me6000ErrorSetDefaultProc;
PF_ME6000ERRORSETUSERPROC          pf_me6000ErrorSetUserProc;
PF_ME6000ERRORGETMESSAGE           pf_me6000ErrorGetMessage;
PF_ME6000ERRORGETLASTMESSAGE       pf_me6000ErrorGetLastMessage;
PF_ME6000GETDLLVERSION             pf_me6000GetDLLVersion;
PF_ME6000GETDRIVERVERSION          pf_me6000GetDriverVersion;
PF_ME6000FREQUENCYTOTICKS          pf_me6000FrequencyToTicks;
PF_ME6000TIMETOTICKS               pf_me6000TimeToTicks;
PF_ME6000GETBOARDVERSION           pf_me6000GetBoardVersion;
PF_ME6000GETSERIALNUMBER           pf_me6000GetSerialNumber;
PF_ME6000AOSINGLE                  pf_me6000AOSingle;
PF_ME6000AOUPDATE                  pf_me6000AOUpdate;
PF_ME6000AOCONFIG                  pf_me6000AOConfig;
PF_ME6000AOWRAPAROUND              pf_me6000AOWraparound;
PF_ME6000AOCONTINUOUS              pf_me6000AOContinuous;
PF_ME6000AOSTART                   pf_me6000AOStart;
PF_ME6000AOAPPENDNEWVALUES         pf_me6000AOAppendNewValues;
PF_ME6000AOSTOP                    pf_me6000AOStop;
PF_ME6000AOVOLTTODIGIT             pf_me6000AOVoltToDigit;
PF_ME6000AORESET                   pf_me6000AOReset;
PF_ME6000AOWAVEGEN                 pf_me6000AOWaveGen;
PF_ME6000AOGETSTATUS               pf_me6000AOGetStatus;





HINSTANCE hDll;


void meOpen(void)
{
    hDll = LoadLibrary(DLLNAME);
    if (hDll == NULL)
    {
        MessageBox( NULL, "DLL not Found", "Error", MB_OK | MB_ICONINFORMATION );
        exit(1);
    }
    
    pf_me4000ErrorSetDefaultProc =      (PF_ME4000ERRORSETDEFAULTPROC)
                            (GetProcAddress (hDll,"me4000ErrorSetDefaultProc"));
    
    pf_me4000ErrorSetUserProc =         (PF_ME4000ERRORSETUSERPROC)
                            (GetProcAddress (hDll,"me4000ErrorSetUserProc"));
    
    pf_me4000ErrorGetMessage =          (PF_ME4000ERRORGETMESSAGE)
                            (GetProcAddress (hDll,"me4000ErrorGetMessage"));
    
    pf_me4000ErrorGetLastMessage =      (PF_ME4000ERRORGETLASTMESSAGE)
                            (GetProcAddress (hDll,"me4000ErrorGetLastMessage"));
    
    pf_me4000GetDLLVersion =            (PF_ME4000GETDLLVERSION)
                            (GetProcAddress (hDll,"me4000GetDLLVersion"));
    
    pf_me4000GetDriverVersion =         (PF_ME4000GETDRIVERVERSION)
                            (GetProcAddress (hDll,"me4000GetDriverVersion"));
    
    pf_me4000FrequencyToTicks =         (PF_ME4000FREQUENCYTOTICKS)
                            (GetProcAddress (hDll,"me4000FrequencyToTicks"));
    
    pf_me4000TimeToTicks =              (PF_ME4000TIMETOTICKS)
                            (GetProcAddress (hDll,"me4000TimeToTicks"));
    
    pf_me4000GetBoardVersion =          (PF_ME4000GETBOARDVERSION)
                            (GetProcAddress (hDll,"me4000GetBoardVersion"));
    
    pf_me4000GetSerialNumber =          (PF_ME4000GETSERIALNUMBER)
                            (GetProcAddress (hDll,"me4000GetSerialNumber"));
    
    pf_me4000AISingle =                 (PF_ME4000AISINGLE)
                            (GetProcAddress (hDll,"me4000AISingle"));
    
    pf_me4000AIMakeChannelListEntry =   (PF_ME4000AIMAKECHANNELLISTENTRY)
                            (GetProcAddress (hDll,"me4000AIMakeChannelListEntry"));
    
    pf_me4000AIConfig =                 (PF_ME4000AICONFIG)
                            (GetProcAddress (hDll,"me4000AIConfig"));
    
    pf_me4000AIScan =                   (PF_ME4000AISCAN)
                            (GetProcAddress (hDll,"me4000AIScan"));
    
    pf_me4000AIContinuous =             (PF_ME4000AICONTINUOUS)
                            (GetProcAddress (hDll,"me4000AIContinuous"));
    
    pf_me4000AIStart =                  (PF_ME4000AISTART)
                            (GetProcAddress (hDll,"me4000AIStart"));
    
    pf_me4000AIGetNewValues =           (PF_ME4000AIGETNEWVALUES)
                            (GetProcAddress (hDll,"me4000AIGetNewValues"));
    
    pf_me4000AIStop =                   (PF_ME4000AISTOP)
                            (GetProcAddress (hDll,"me4000AIStop"));
    
    pf_me4000AIExtractValues =          (PF_ME4000AIEXTRACTVALUES)
                            (GetProcAddress (hDll,"me4000AIExtractValues"));
    
    pf_me4000AIDigitToVolt =            (PF_ME4000AIDIGITTOVOLT)
                            (GetProcAddress (hDll,"me4000AIDigitToVolt"));
    
    pf_me4000AIReset =                  (PF_ME4000AIRESET)
                            (GetProcAddress (hDll,"me4000AIReset"));
    
    pf_me4000AIGetStatus =              (PF_ME4000AIGETSTATUS)
                            (GetProcAddress (hDll,"me4000AIGetStatus"));
    
    pf_me4000AOSingle =                 (PF_ME4000AOSINGLE)
                            (GetProcAddress (hDll,"me4000AOSingle"));
    
    pf_me4000AOSingleSimultaneous =     (PF_ME4000AOSINGLESIMULTANEOUS)
                            (GetProcAddress (hDll,"me4000AOSingleSimultaneous"));
    
    pf_me4000AOUpdate =                 (PF_ME4000AOUPDATE)
                            (GetProcAddress (hDll,"me4000AOUpdate"));
    
    pf_me4000AOConfig =                 (PF_ME4000AOCONFIG)
                            (GetProcAddress (hDll,"me4000AOConfig"));
    
    pf_me4000AOWraparound =             (PF_ME4000AOWRAPAROUND)
                            (GetProcAddress (hDll,"me4000AOWraparound"));
    
    pf_me4000AOContinuous =             (PF_ME4000AOCONTINUOUS)
                            (GetProcAddress (hDll,"me4000AOContinuous"));
    
    pf_me4000AOStart =                  (PF_ME4000AOSTART)
                            (GetProcAddress (hDll,"me4000AOStart"));
    
    pf_me4000AOStartSynchronous =       (PF_ME4000AOSTARTSYNCHRONOUS)
                            (GetProcAddress (hDll,"me4000AOStartSynchronous"));
    
    pf_me4000AOAppendNewValues =        (PF_ME4000AOAPPENDNEWVALUES)
                            (GetProcAddress (hDll,"me4000AOAppendNewValues"));
    
    pf_me4000AOStop =                   (PF_ME4000AOSTOP)
                            (GetProcAddress (hDll,"me4000AOStop"));
    
    pf_me4000AOVoltToDigit =            (PF_ME4000AOVOLTTODIGIT)
                            (GetProcAddress (hDll,"me4000AOVoltToDigit"));
    
    pf_me4000AOReset =                  (PF_ME4000AORESET)
                            (GetProcAddress (hDll,"me4000AOReset"));
    
    pf_me4000AOWaveGen =                (PF_ME4000AOWAVEGEN)
                            (GetProcAddress (hDll,"me4000AOWaveGen"));
    
    pf_me4000AOGetStatus =              (PF_ME4000AOGETSTATUS)
                            (GetProcAddress (hDll,"me4000AOGetStatus"));
    
    pf_me4000DIOConfig =                (PF_ME4000DIOCONFIG)
                            (GetProcAddress (hDll,"me4000DIOConfig"));
    
    pf_me4000DIOResetAll =              (PF_ME4000DIORESETALL)
                            (GetProcAddress (hDll,"me4000DIOResetAll"));
    
    pf_me4000DIOGetBit =                (PF_ME4000DIOGETBIT)
                            (GetProcAddress (hDll,"me4000DIOGetBit"));
    
    pf_me4000DIOGetByte =               (PF_ME4000DIOGETBYTE)
                            (GetProcAddress (hDll,"me4000DIOGetByte"));
    
    pf_me4000DIOSetBit =                (PF_ME4000DIOSETBIT)
                            (GetProcAddress (hDll,"me4000DIOSetBit"));
    
    pf_me4000DIOSetByte =               (PF_ME4000DIOSETBYTE)
                            (GetProcAddress (hDll,"me4000DIOSetByte"));
    
    pf_me4000CntWrite =                 (PF_ME4000CNTWRITE)
                            (GetProcAddress (hDll,"me4000CntWrite"));
    
    pf_me4000CntRead =                  (PF_ME4000CNTREAD)
                            (GetProcAddress (hDll,"me4000CntRead"));
    
    pf_me4000CntPWMStart =              (PF_ME4000CNTPWMSTART)
                            (GetProcAddress (hDll,"me4000CntPWMStart"));
    
    pf_me4000CntPWMStop =               (PF_ME4000CNTPWMSTOP)
                            (GetProcAddress (hDll,"me4000CntPWMStop"));
    
    pf_me4000ExtIrqEnable =             (PF_ME4000EXTIRQENABLE)
                            (GetProcAddress (hDll,"me4000ExtIrqEnable"));
    
    pf_me4000ExtIrqDisable =            (PF_ME4000EXTIRQDISABLE)
                            (GetProcAddress (hDll,"me4000ExtIrqDisable"));
    
    pf_me4000ExtIrqGetCount =           (PF_ME4000EXTIRQGETCOUNT)
                            (GetProcAddress (hDll,"me4000ExtIrqGetCount"));
    
    pf_me4000DIOBPPortConfig =          (PF_ME4000DIOBPPORTCONFIG)
                            (GetProcAddress (hDll,"me4000DIOBPPortConfig"));
    
    pf_me4000DIOBPConfig =              (PF_ME4000DIOBPCONFIG)
                            (GetProcAddress (hDll,"me4000DIOBPConfig"));
    
    pf_me4000DIOBPWraparound =          (PF_ME4000DIOBPWRAPAROUND)
                            (GetProcAddress (hDll,"me4000DIOBPWraparound"));
    
    pf_me4000DIOBPContinuous =          (PF_ME4000DIOBPCONTINUOUS)
                            (GetProcAddress (hDll,"me4000DIOBPContinuous"));
    
    pf_me4000DIOBPStart =               (PF_ME4000DIOBPSTART)
                            (GetProcAddress (hDll,"me4000DIOBPStart"));
    
    pf_me4000DIOBPAppendNewValues =     (PF_ME4000DIOBPAPPENDNEWVALUES)
                            (GetProcAddress (hDll,"me4000DIOBPAppendNewValues"));
    
    pf_me4000DIOBPStop =                (PF_ME4000DIOBPSTOP)
                            (GetProcAddress (hDll,"me4000DIOBPStop"));
    
    pf_me4000DIOBPReset =               (PF_ME4000DIOBPRESET)
                            (GetProcAddress (hDll,"me4000DIOBPReset"));
    
    pf_me4000DIOBPGetStatus =           (PF_ME4000DIOBPGETSTATUS)
                            (GetProcAddress (hDll,"me4000DIOBPGetStatus"));
    
    pf_me4000MultiSigOpen =             (PF_ME4000MULTISIGOPEN)
                            (GetProcAddress (hDll,"me4000MultiSigOpen"));
    
    pf_me4000MultiSigReset =            (PF_ME4000MULTISIGRESET)
                            (GetProcAddress (hDll,"me4000MultiSigReset"));
    
    pf_me4000MultiSigAddressLED =       (PF_ME4000MULTISIGADDRESSLED)
                            (GetProcAddress (hDll,"me4000MultiSigAddressLED"));
    
    pf_me4000MultiSigSetGain =          (PF_ME4000MULTISIGSETGAIN)
                            (GetProcAddress (hDll,"me4000MultiSigSetGain"));
    
    pf_me4000MultiSigClose =            (PF_ME4000MULTISIGCLOSE)
                            (GetProcAddress (hDll,"me4000MultiSigClose"));
    
    pf_me4000MultiSigAIOpen =           (PF_ME4000MULTISIGAIOPEN)
                            (GetProcAddress (hDll,"me4000MultiSigAIOpen"));
    
    pf_me4000MultiSigAISingle =         (PF_ME4000MULTISIGAISINGLE)
                            (GetProcAddress (hDll,"me4000MultiSigAISingle"));
    
    pf_me4000MultiSigAIConfig =         (PF_ME4000MULTISIGAICONFIG)
                            (GetProcAddress (hDll,"me4000MultiSigAIConfig"));
    
    pf_me4000MultiSigAIScan =           (PF_ME4000MULTISIGAISCAN)
                            (GetProcAddress (hDll,"me4000MultiSigAIScan"));
    
    pf_me4000MultiSigAIContinuous =     (PF_ME4000MULTISIGAICONTINUOUS)
                            (GetProcAddress (hDll,"me4000MultiSigAIContinuous"));
    
    pf_me4000MultiSigAIStart =          (PF_ME4000MULTISIGAISTART)
                            (GetProcAddress (hDll,"me4000MultiSigAIStart"));
    
    pf_me4000MultiSigAIGetNewValues =   (PF_ME4000MULTISIGAIGETNEWVALUES)
                            (GetProcAddress (hDll,"me4000MultiSigAIGetNewValues"));
    
    pf_me4000MultiSigAIStop =           (PF_ME4000MULTISIGAISTOP)
                            (GetProcAddress (hDll,"me4000MultiSigAIStop"));
    
    pf_me4000MultiSigAIExtractValues =  (PF_ME4000MULTISIGAIEXTRACTVALUES)
                            (GetProcAddress (hDll,"me4000MultiSigAIExtractValues"));
    
    pf_me4000MultiSigAIDigitToSize =    (PF_ME4000MULTISIGAIDIGITTOSIZE)
                            (GetProcAddress (hDll,"me4000MultiSigAIDigitToSize"));
    
    pf_me4000MultiSigAIReset =          (PF_ME4000MULTISIGAIRESET)
                            (GetProcAddress (hDll,"me4000MultiSigAIReset"));
    
    pf_me4000MultiSigAIGetStatus =      (PF_ME4000MULTISIGAIGETSTATUS)
                            (GetProcAddress (hDll,"me4000MultiSigAIGetStatus"));
    
    pf_me4000MultiSigAIClose =          (PF_ME4000MULTISIGAICLOSE)
                            (GetProcAddress (hDll,"me4000MultiSigAIClose"));
    
    pf_me4000MultiSigAOOpen =           (PF_ME4000MULTISIGAOOPEN)
                            (GetProcAddress (hDll,"me4000MultiSigAOOpen"));
    
    pf_me4000MultiSigAOSingle =         (PF_ME4000MULTISIGAOSINGLE)
                            (GetProcAddress (hDll,"me4000MultiSigAOSingle"));
    
    pf_me4000MultiSigAOConfig =         (PF_ME4000MULTISIGAOCONFIG)
                            (GetProcAddress (hDll,"me4000MultiSigAOConfig"));
    
    pf_me4000MultiSigAOWraparound =     (PF_ME4000MULTISIGAOWRAPAROUND)
                            (GetProcAddress (hDll,"me4000MultiSigAOWraparound"));
    
    pf_me4000MultiSigAOContinuous =     (PF_ME4000MULTISIGAOCONTINUOUS)
                            (GetProcAddress (hDll,"me4000MultiSigAOContinuous"));
    
    pf_me4000MultiSigAOStart =          (PF_ME4000MULTISIGAOSTART)
                            (GetProcAddress (hDll,"me4000MultiSigAOStart"));
    
    pf_me4000MultiSigAOAppendNewValues = (PF_ME4000MULTISIGAOAPPENDNEWVALUES)
                            (GetProcAddress (hDll,"me4000MultiSigAOAppendNewValues"));
    
    pf_me4000MultiSigAOStop =           (PF_ME4000MULTISIGAOSTOP)
                            (GetProcAddress (hDll,"me4000MultiSigAOStop"));
    
    pf_me4000MultiSigAOVoltToDigit =    (PF_ME4000MULTISIGAOVOLTTODIGIT)
                            (GetProcAddress (hDll,"me4000MultiSigAOVoltToDigit"));
    
    pf_me4000MultiSigAOReset =          (PF_ME4000MULTISIGAORESET)
                            (GetProcAddress (hDll,"me4000MultiSigAOReset"));
    
    pf_me4000MultiSigAOGetStatus =      (PF_ME4000MULTISIGAOGETSTATUS)
                            (GetProcAddress (hDll,"me4000MultiSigAOGetStatus"));
    
    pf_me4000MultiSigAOClose =          (PF_ME4000MULTISIGAOCLOSE)
                            (GetProcAddress (hDll,"me4000MultiSigAOClose"));
    
    pf_me6000ErrorSetDefaultProc =      (PF_ME6000ERRORSETDEFAULTPROC)
                            (GetProcAddress (hDll,"me6000ErrorSetDefaultProc"));
    
    pf_me6000ErrorSetUserProc =         (PF_ME6000ERRORSETUSERPROC)
                            (GetProcAddress (hDll,"me6000ErrorSetUserProc"));
    
    pf_me6000ErrorGetMessage =          (PF_ME6000ERRORGETMESSAGE)
                            (GetProcAddress (hDll,"me6000ErrorGetMessage"));
    
    pf_me6000ErrorGetLastMessage =      (PF_ME6000ERRORGETLASTMESSAGE)
                            (GetProcAddress (hDll,"me6000ErrorGetLastMessage"));
    
    pf_me6000GetDLLVersion =            (PF_ME6000GETDLLVERSION)
                            (GetProcAddress (hDll,"me6000GetDLLVersion"));
    
    pf_me6000GetDriverVersion =         (PF_ME6000GETDRIVERVERSION)
                            (GetProcAddress (hDll,"me6000GetDriverVersion"));
    
    pf_me6000FrequencyToTicks =         (PF_ME6000FREQUENCYTOTICKS)
                            (GetProcAddress (hDll,"me6000FrequencyToTicks"));
    
    pf_me6000TimeToTicks =              (PF_ME6000TIMETOTICKS)
                            (GetProcAddress (hDll,"me6000TimeToTicks"));
    
    pf_me6000GetBoardVersion =          (PF_ME6000GETBOARDVERSION)
                            (GetProcAddress (hDll,"me6000GetBoardVersion"));
    
    pf_me6000GetSerialNumber =          (PF_ME6000GETSERIALNUMBER)
                            (GetProcAddress (hDll,"me6000GetSerialNumber"));
    
    pf_me6000AOSingle =                 (PF_ME6000AOSINGLE)
                            (GetProcAddress (hDll,"me6000AOSingle"));
    
    pf_me6000AOUpdate =                 (PF_ME6000AOUPDATE)
                            (GetProcAddress (hDll,"me6000AOUpdate"));
    
    pf_me6000AOConfig =                 (PF_ME6000AOCONFIG)
                            (GetProcAddress (hDll,"me6000AOConfig"));
    
    pf_me6000AOWraparound =             (PF_ME6000AOWRAPAROUND)
                            (GetProcAddress (hDll,"me6000AOWraparound"));
    
    pf_me6000AOContinuous =             (PF_ME6000AOCONTINUOUS)
                            (GetProcAddress (hDll,"me6000AOContinuous"));
    
    pf_me6000AOStart =                  (PF_ME6000AOSTART)
                            (GetProcAddress (hDll,"me6000AOStart"));
    
    pf_me6000AOAppendNewValues =        (PF_ME6000AOAPPENDNEWVALUES)
                            (GetProcAddress (hDll,"me6000AOAppendNewValues"));
    
    pf_me6000AOStop =                   (PF_ME6000AOSTOP)
                            (GetProcAddress (hDll,"me6000AOStop"));
    
    pf_me6000AOVoltToDigit =            (PF_ME6000AOVOLTTODIGIT)
                            (GetProcAddress (hDll,"me6000AOVoltToDigit"));
    
    pf_me6000AOReset =                  (PF_ME6000AORESET)
                            (GetProcAddress (hDll,"me6000AOReset"));
    
    pf_me6000AOWaveGen =                (PF_ME6000AOWAVEGEN)
                            (GetProcAddress (hDll,"me6000AOWaveGen"));
    
    pf_me6000AOGetStatus =              (PF_ME6000AOGETSTATUS)
                            (GetProcAddress (hDll,"me6000AOGetStatus"));

}





//   -------------------- Wrappers for all Functions -------------------------

int me4000GetDLLVersion(unsigned long *pulDLLVersion)
{
    if (pf_me4000GetDLLVersion)
        return (pf_me4000GetDLLVersion)(
            pulDLLVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000GetDriverVersion(unsigned long *pulDrvVersion)
{
    if (pf_me4000GetDriverVersion)
        return (pf_me4000GetDriverVersion)(
            pulDrvVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me4000GetBoardVersion(int iBoardNumber, unsigned short *pusBrdVersion)
{
    if (pf_me4000GetBoardVersion)
        return (pf_me4000GetBoardVersion)(
            iBoardNumber, 
            pusBrdVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}


int me4000GetSerialNumber(int iBoardNumber, unsigned long *pulSerialNumber)
{
    if (pf_me4000GetSerialNumber)
        return (pf_me4000GetSerialNumber)(
            iBoardNumber, 
            pulSerialNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}




int me4000ErrorSetDefaultProc(
    int iDefaultProcStatus)
{
    if (pf_me4000ErrorSetDefaultProc)
        return (pf_me4000ErrorSetDefaultProc)(
            iDefaultProcStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000ErrorSetUserProc(
    ME4000_P_ERROR_PROC pErrorProc)
{
    if (pf_me4000ErrorSetUserProc)
        return (pf_me4000ErrorSetUserProc)(
            pErrorProc);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000ErrorGetMessage(
    int iErrorCode,
    char* pcBuffer,
    unsigned int uiBufferSize)
{
    if (pf_me4000ErrorGetMessage)
        return (pf_me4000ErrorGetMessage)(
            iErrorCode, 
            pcBuffer, 
            uiBufferSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000ErrorGetLastMessage(
    char* pcBuffer,
    unsigned int uiBufferSize)
{
    if (pf_me4000ErrorGetLastMessage)
        return (pf_me4000ErrorGetLastMessage)(
            pcBuffer, 
            uiBufferSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000GetDLLVersion(
    unsigned long* pulVersion)
{
    if (pf_me4000GetDLLVersion)
        return (pf_me4000GetDLLVersion)(
            pulVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000GetDriverVersion(
    unsigned long* pulVersion)
{
    if (pf_me4000GetDriverVersion)
        return (pf_me4000GetDriverVersion)(
            pulVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000FrequencyToTicks(
    double dRequiredFreq,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedFreq)
{
    if (pf_me4000FrequencyToTicks)
        return (pf_me4000FrequencyToTicks)(
            dRequiredFreq, 
            pulTicksLowPart, 
            pulTicksHighPart, 
            pdAchievedFreq);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000TimeToTicks(
    double dRequiredTime,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedTime)
{
    if (pf_me4000TimeToTicks)
        return (pf_me4000TimeToTicks)(
            dRequiredTime, 
            pulTicksLowPart, 
            pulTicksHighPart, 
            pdAchievedTime);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000GetBoardVersion(
    unsigned int uiBoardNumber,
    unsigned short* pusVersion)
{
    if (pf_me4000GetBoardVersion)
        return (pf_me4000GetBoardVersion)(
            uiBoardNumber, 
            pusVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000GetSerialNumber(
    unsigned int uiBoardNumber,
    unsigned long* pulSerialNumber)
{
    if (pf_me4000GetSerialNumber)
        return (pf_me4000GetSerialNumber)(
            uiBoardNumber, 
            pulSerialNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AISingle(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iRange,
    int iSDMode,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short* psDigitalValue)
{
    if (pf_me4000AISingle)
        return (pf_me4000AISingle)(
            uiBoardNumber, 
            uiChannelNumber, 
            iRange, 
            iSDMode, 
            iTriggerMode, 
            iExtTriggerEdge, 
            ulTimeOutSeconds, 
            psDigitalValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIMakeChannelListEntry(
    unsigned int uiChannelNumber,
    int iRange,
    unsigned char* pucChanListEntry)
{
    if (pf_me4000AIMakeChannelListEntry)
        return (pf_me4000AIMakeChannelListEntry)(
            uiChannelNumber,
            iRange,
            pucChanListEntry);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIConfig(
    unsigned int uiBoardNumber,
    unsigned char* pucChanList,
    unsigned int uiChanListCount,
    int iSDMode,
    int iSimultaneous,
    unsigned long ulReserved,
    unsigned long ulChanTicks,
    unsigned long ulScanTicksLow,
    unsigned long ulScanTicksHigh,
    int iAcqMode,
    int iExtTriggerMode,
    int iExtTriggerEdge)
{
    if (pf_me4000AIConfig)
        return (pf_me4000AIConfig)(
            uiBoardNumber,
            pucChanList,
            uiChanListCount,
            iSDMode,
            iSimultaneous,
            ulReserved,
            ulChanTicks,
            ulScanTicksLow,
            ulScanTicksHigh,
            iAcqMode,
            iExtTriggerMode,
            iExtTriggerEdge);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIScan(
    unsigned int uiBoardNumber,
    unsigned int uiNumberOfChanLists,
    short* psBuffer,
    unsigned long ulBufferSizeValues,
    int iExecutionMode,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    ME4000_P_AI_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me4000AIScan)
        return (pf_me4000AIScan)(
            uiBoardNumber,
            uiNumberOfChanLists,
            psBuffer,
            ulBufferSizeValues,
            iExecutionMode,
            pCallbackProc,
            pCallbackContext,
            uiRefreshFrequency,
            pTerminateProc,
            pTerminateContext,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIContinuous(
    unsigned int uiBoardNumber,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me4000AIContinuous)
        return (pf_me4000AIContinuous)(
            uiBoardNumber,
            pCallbackProc,
            pCallbackContext,
            uiRefreshFrequency,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIStart(
    unsigned int uiBoardNumber)
{
    if (pf_me4000AIStart)
        return (pf_me4000AIStart)(
            unsigned int uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIGetNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToRead,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesRead,
    int* piLastError)
{
    if (pf_me4000AIGetNewValues)
        return (pf_me4000AIGetNewValues)(
            uiBoardNumber,
            psBuffer,
            ulNumberOfValuesToRead,
            iExecutionMode,
            pulNumberOfValuesRead,
            piLastError);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIStop(
    unsigned int uiBoardNumber,
    int iReserved)
{
    if (pf_me4000AIStop)
        return (pf_me4000AIStop)(
            uiBoardNumber,
            iReserved);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIExtractValues(
    unsigned int uiChannelNumber,
    short* psAIBuffer,
    unsigned long ulAIDataCount,
    unsigned char* pucChanList,
    unsigned int uiChanListCount,
    short* psChanBuffer,
    unsigned long ulChanBufferSizeValues,
    unsigned long* pulChanDataCount)
{
    if (pf_me4000AIExtractValues)
        return (pf_me4000AIExtractValues)(
            uiChannelNumber,
            psAIBuffer,
            ulAIDataCount,
            pucChanList,
            uiChanListCount,
            psChanBuffer,
            ulChanBufferSizeValues,
            pulChanDataCount);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIDigitToVolt(
    short sDigit,
    int iRange,
    double* pdVolt)
{
    if (pf_me4000AIDigitToVolt)
        return (pf_me4000AIDigitToVolt)(
            sDigit,
            iRange,
            pdVolt);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIReset(
    unsigned int uiBoardNumber)
{
    if (pf_me4000AIReset)
        return (pf_me4000AIReset)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AIGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus)
{
    if (pf_me4000AIGetStatus)
        return (pf_me4000AIGetStatus)(
            uiBoardNumber,
            iWaitIdle,
            piStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOSingle(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short sValue)
{
    if (pf_me4000AOSingle)
        return (pf_me4000AOSingle)(
            uiBoardNumber,
            uiChannelNumber,
            iTriggerMode,
            iExtTriggerEdge,
            ulTimeOutSeconds,
            sValue    );
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOSingleSimultaneous(
    unsigned int uiBoardNumber,
    unsigned int* puiChannelNumber,
    unsigned long ulCount,
    int iTriggerMode,
    int* piExtTriggerEnable,
    int* piExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short* psValue  )
{
    if (pf_me4000AOSingleSimultaneous)
        return (pf_me4000AOSingleSimultaneous)(
            uiBoardNumber,
            puiChannelNumber,
            ulCount,
            iTriggerMode,
            piExtTriggerEnable,
            piExtTriggerEdge,
            ulTimeOutSeconds,
            psValue  );
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOUpdate(
    unsigned int uiBoardNumber)
{
    if (pf_me4000AOUpdate)
        return (pf_me4000AOUpdate)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge)
{
    if (pf_me4000AOConfig)
        return (pf_me4000AOConfig)(
            uiBoardNumber,
            uiChannelNumber,
            ulTicks,
            iTriggerMode,
            iExtTriggerEdge);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOWraparound(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me4000AOWraparound)
        return (pf_me4000AOWraparound)(
            uiBoardNumber,
            uiChannelNumber,
            psBuffer,
            ulDataCount,
            ulLoops,
            iExecutionMode,
            pTerminateProc,
            pTerminateContext,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOContinuous(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_AO_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten)
{
    if (pf_me4000AOContinuous)
        return (pf_me4000AOContinuous)(
            uiBoardNumber,
            uiChannelNumber,
            psBuffer,
            ulDataCount,
            pCallbackProc,
            pCallbackContext,
            ulTimeOutSeconds,
            pulNumberOfValuesWritten);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOStart(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber)
{
    if (pf_me4000AOStart)
        return (pf_me4000AOStart)(
            uiBoardNumber,
            uiChannelNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOStartSynchronous(
    unsigned int uiBoardNumber,
    unsigned int* puiChannelNumber,
    unsigned long ulCount,
    int iTriggerMode,
    int* piExtTriggerEnable,
    int* piExtTriggerEdge,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me4000AOStartSynchronous)
        return (pf_me4000AOStartSynchronous)(
            uiBoardNumber,
            puiChannelNumber,
            ulCount,
            iTriggerMode,
            piExtTriggerEnable,
            piExtTriggerEdge,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOAppendNewValues(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended)
{
    if (pf_me4000AOAppendNewValues)
        return (pf_me4000AOAppendNewValues)(
            uiBoardNumber,
            uiChannelNumber,
            psBuffer,
            ulNumberOfValuesToAppend,
            iExecutionMode,
            pulNumberOfValuesAppended);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOStop(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iStopMode)
{
    if (pf_me4000AOStop)
        return (pf_me4000AOStop)(
            uiBoardNumber,
            uiChannelNumber,
            iStopMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOVoltToDigit(
    double dVolt,
    short* psDigit)
{
    if (pf_me4000AOVoltToDigit)
        return (pf_me4000AOVoltToDigit)(
            dVolt,
            psDigit);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOReset(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber)
{
    if (pf_me4000AOReset)
        return (pf_me4000AOReset)(
            uiBoardNumber,
            uiChannelNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOWaveGen(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iShape,
    double dAmplitude,
    double dOffset,
    double dFrequency)
{
    if (pf_me4000AOWaveGen)
        return (pf_me4000AOWaveGen)(
            uiBoardNumber,
            uiChannelNumber,
            iShape,
            dAmplitude,
            dOffset,
            dFrequency);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000AOGetStatus(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iWaitIdle,
    int* piStatus)
{
    if (pf_me4000AOGetStatus)
        return (pf_me4000AOGetStatus)(
            uiBoardNumber,
            uiChannelNumber,
            iWaitIdle,
            piStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    int iPortDirection)
{
    if (pf_me4000DIOConfig)
        return (pf_me4000DIOConfig)(
            uiBoardNumber,
            uiPortNumber,
            iPortDirection);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOResetAll(
    unsigned int uiBoardNumber)
{
    if (pf_me4000DIOResetAll)
        return (pf_me4000DIOResetAll)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOGetBit(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned int uiBitNumber,
    int* piBitValue)
{
    if (pf_me4000DIOGetBit)
        return (pf_me4000DIOGetBit)(
            uiBoardNumber,
            uiPortNumber,
            uiBitNumber,
            piBitValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOGetByte(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned char* pucByteValue)
{
    if (pf_me4000DIOGetByte)
        return (pf_me4000DIOGetByte)(
            uiBoardNumber,
            uiPortNumber,
            pucByteValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOSetBit(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned int uiBitNumber,
    int iBitValue)
{
    if (pf_me4000DIOSetBit)
        return (pf_me4000DIOSetBit)(
            uiBoardNumber,
            uiPortNumber,
            uiBitNumber,
            iBitValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOSetByte(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    unsigned char ucByteValue)
{
    if (pf_me4000DIOSetByte)
        return (pf_me4000DIOSetByte)(
            uiBoardNumber,
            uiPortNumber,
            ucByteValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000CntWrite(
    unsigned int uiBoardNumber,
    unsigned int uiCounterNumber,
    int iMode,
    unsigned short usValue)
{
    if (pf_me4000CntWrite)
        return (pf_me4000CntWrite)(
            uiBoardNumber,
            uiCounterNumber,
            iMode,
            usValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000CntRead(
    unsigned int uiBoardNumber,
    unsigned int uiCounterNumber,
    unsigned short* pusValue)
{
    if (pf_me4000CntRead)
        return (pf_me4000CntRead)(
            uiBoardNumber,
            uiCounterNumber,
            pusValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000CntPWMStart(
    unsigned int uiBoardNumber,
    unsigned int uiPreScaler,
    int iDutyCycle)
{
    if (pf_me4000CntPWMStart)
        return (pf_me4000CntPWMStart)(
            uiBoardNumber,
            uiPreScaler,
            iDutyCycle);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000CntPWMStop(
    unsigned int uiBoardNumber)
{
    if (pf_me4000CntPWMStop)
        return (pf_me4000CntPWMStop)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000ExtIrqEnable(
    unsigned int uiBoardNumber,
    ME4000_P_EXT_IRQ_PROC pExtIrqProc,
    void* pExtIrqContext)
{
    if (pf_me4000ExtIrqEnable)
        return (pf_me4000ExtIrqEnable)(
            uiBoardNumber,
            pExtIrqProc,
            pExtIrqContext);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000ExtIrqDisable(
    unsigned int uiBoardNumber)
{
    if (pf_me4000ExtIrqDisable)
        return (pf_me4000ExtIrqDisable)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000ExtIrqGetCount(
    unsigned int uiBoardNumber,
    unsigned int* puiIrqCount)
{
    if (pf_me4000ExtIrqGetCount)
        return (pf_me4000ExtIrqGetCount)(
            uiBoardNumber,
            puiIrqCount);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPPortConfig(
    unsigned int uiBoardNumber,
    unsigned int uiPortNumber,
    int iOutputMode)
{
    if (pf_me4000DIOBPPortConfig)
        return (pf_me4000DIOBPPortConfig)(
            uiBoardNumber,
            uiPortNumber,
            iOutputMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPConfig(
    unsigned int uiBoardNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge)
{
    if (pf_me4000DIOBPConfig)
        return (pf_me4000DIOBPConfig)(
            uiBoardNumber,
            ulTicks,
            iTriggerMode,
            iExtTriggerEdge);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPWraparound(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_DIOBP_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me4000DIOBPWraparound)
        return (pf_me4000DIOBPWraparound)(
            uiBoardNumber,
            psBuffer,
            ulDataCount,
            ulLoops,
            iExecutionMode,
            pTerminateProc,
            pTerminateContext,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPContinuous(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_DIOBP_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten)
{
    if (pf_me4000DIOBPContinuous)
        return (pf_me4000DIOBPContinuous)(
            uiBoardNumber,
            psBuffer,
            ulDataCount,
            pCallbackProc,
            pCallbackContext,
            ulTimeOutSeconds,
            pulNumberOfValuesWritten);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPStart(
    unsigned int uiBoardNumber)
{
    if (pf_me4000DIOBPStart)
        return (pf_me4000DIOBPStart)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPAppendNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended)
{
    if (pf_me4000DIOBPAppendNewValues)
        return (pf_me4000DIOBPAppendNewValues)(
            uiBoardNumber,
            psBuffer,
            ulNumberOfValuesToAppend,
            iExecutionMode,
            pulNumberOfValuesAppended);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPStop(
    unsigned int uiBoardNumber,
    int iStopMode)
{
    if (pf_me4000DIOBPStop)
        return (pf_me4000DIOBPStop)(
            uiBoardNumber,
            iStopMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPReset(
    unsigned int uiBoardNumber)
{
    if (pf_me4000DIOBPReset)
        return (pf_me4000DIOBPReset)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000DIOBPGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus)
{
    if (pf_me4000DIOBPGetStatus)
        return (pf_me4000DIOBPGetStatus)(
            uiBoardNumber,
            iWaitIdle,
            piStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigOpen(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigOpen)
        return (pf_me4000MultiSigOpen)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigReset(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigReset)
        return (pf_me4000MultiSigReset)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAddressLED(
    unsigned int uiBoardNumber,
    unsigned int uiBase,
    int iLEDStatus)
{
    if (pf_me4000MultiSigAddressLED)
        return (pf_me4000MultiSigAddressLED)(
            uiBoardNumber,
            uiBase,
            iLEDStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigSetGain(
    unsigned int uiBoardNumber,
    unsigned int uiBase,
    int iChannelGroup,
    int iGain)
{
    if (pf_me4000MultiSigSetGain)
        return (pf_me4000MultiSigSetGain)(
            uiBoardNumber,
            uiBase,
            iChannelGroup,
            iGain);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigClose(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigClose)
        return (pf_me4000MultiSigClose)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIOpen(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigAIOpen)(
        uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAISingle(
            uiBoardNumber,
            uiAIChannelNumber,
            uiMuxChannelNumber,
            iGain,
            iTriggerMode,
            iExtTriggerEdge,
            ulTimeOutSeconds,
            psDigitalValue)
{
    if (pf_me4000MultiSigAISingle)
        return (pf_me4000MultiSigAISingle)(
            uiBoardNumber,
            uiAIChannelNumber,
            uiMuxChannelNumber,
            iGain,
            iTriggerMode,
            iExtTriggerEdge,
            ulTimeOutSeconds,
            psDigitalValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIConfig(
    unsigned int uiBoardNumber,
    unsigned int uiAIChannelNumber,
    unsigned char* pucMuxChanList,
    unsigned int uiMuxChanListCount,
    unsigned long ulReserved,
    unsigned long ulChanTicks,
    unsigned long ulScanTicksLow,
    unsigned long ulScanTicksHigh,
    int iAcqMode,
    int iExtTriggerMode,
    int iExtTriggerEdge)
{
    if (pf_me4000MultiSigAIConfig)
        return (pf_me4000MultiSigAIConfig)(
            uiBoardNumber,
            uiAIChannelNumber,
            pucMuxChanList,
            uiMuxChanListCount,
            ulReserved,
            ulChanTicks,
            ulScanTicksLow,
            ulScanTicksHigh,
            iAcqMode,
            iExtTriggerMode,
            iExtTriggerEdge);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIScan(
    unsigned int uiBoardNumber,
    unsigned int uiNumberOfMuxLists,
    short* psBuffer,
    unsigned long ulBufferSizeValues,
    int iExecutionMode,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    ME4000_P_AI_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me4000MultiSigAIScan)
        return (pf_me4000MultiSigAIScan)(
            uiBoardNumber,
            uiNumberOfMuxLists,
            psBuffer,
            ulBufferSizeValues,
            iExecutionMode,
            pCallbackProc,
            pCallbackContext,
            uiRefreshFrequency,
            pTerminateProc,
            pTerminateContext,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIContinuous(
    unsigned int uiBoardNumber,
    ME4000_P_AI_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned int uiRefreshFrequency,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me4000MultiSigAIContinuous)
        return (pf_me4000MultiSigAIContinuous)(
            uiBoardNumber,
            pCallbackProc,
            pCallbackContext,
            uiRefreshFrequency,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIStart(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigAIStart)
        return (pf_me4000MultiSigAIStart)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIGetNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToRead,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesRead,
    int* piLastError)
{
    if (pf_me4000MultiSigAIGetNewValues)
        return (pf_me4000MultiSigAIGetNewValues)(
            uiBoardNumber,
            psBuffer,
            ulNumberOfValuesToRead,
            iExecutionMode,
            pulNumberOfValuesRead,
            piLastError);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIStop(
    unsigned int uiBoardNumber,
    int iReserved)
{
    if (pf_me4000MultiSigAIStop)
        return (pf_me4000MultiSigAIStop)(
            uiBoardNumber,
            iReserved);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIExtractValues(
    unsigned int uiMuxChannelNumber,
    short* psAIBuffer,
    unsigned long ulAIDataCount,
    unsigned char* pucMuxChanList,
    unsigned int uiMuxChanListCount,
    short* psChanBuffer,
    unsigned long ulChanBufferSizeValues,
    unsigned long* pulChanDataCount)
{
    if (pf_me4000MultiSigAIExtractValues)
        return (pf_me4000MultiSigAIExtractValues)(
            uiMuxChannelNumber,
            psAIBuffer,
            ulAIDataCount,
            pucMuxChanList,
            uiMuxChanListCount,
            psChanBuffer,
            ulChanBufferSizeValues,
            pulChanDataCount);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIDigitToSize(
    short sDigit,
    int iGain,
    int iModuleType,
    double dIMeasured,
    double* pdSize)
{
    if (pf_me4000MultiSigAIDigitToSize)
        return (pf_me4000MultiSigAIDigitToSize)(
            sDigit,
            iGain,
            iModuleType,
            dIMeasured,
            pdSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIReset(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigAIReset)
        return (pf_me4000MultiSigAIReset)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus)
{
    if (pf_me4000MultiSigAIGetStatus)
        return (pf_me4000MultiSigAIGetStatus)(
            uiBoardNumber,
            iWaitIdle,
            piStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAIClose(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigAIClose)
        return (pf_me4000MultiSigAIClose)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOOpen(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigAOOpen)
        return (pf_me4000MultiSigAOOpen)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOSingle(
    unsigned int uiBoardNumber,
    unsigned int uiDemuxChannelNumber,
    int iTriggerMode,
    int iExtTriggerEdge,
    unsigned long ulTimeOutSeconds,
    short sValue)
{
    if (pf_me4000MultiSigAOSingle)
        return (pf_me4000MultiSigAOSingle)(
            uiBoardNumber,
            uiDemuxChannelNumber,
            iTriggerMode,
            iExtTriggerEdge,
            ulTimeOutSeconds,
            sValue);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOConfig(
    unsigned int uiBoardNumber,
    unsigned char* pucDemuxChanList,
    unsigned int uiDemuxChanListCount,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge)
{
    if (pf_me4000MultiSigAOConfig)
        return (pf_me4000MultiSigAOConfig)(
            uiBoardNumber,
            pucDemuxChanList,
            uiDemuxChanListCount,
            ulTicks,
            iTriggerMode,
            iExtTriggerEdge);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOWraparound(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME4000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me4000MultiSigAOWraparound)
        return (pf_me4000MultiSigAOWraparound)(
            uiBoardNumber,
            psBuffer,
            ulDataCount,
            ulLoops,
            iExecutionMode,
            pTerminateProc,
            pTerminateContext,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOContinuous(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    ME4000_P_AO_CALLBACK_PROC pCallbackProc,
    void* pCallbackContext,
    unsigned long ulTimeOutSeconds,
    unsigned long* pulNumberOfValuesWritten)
{
    if (pf_me4000MultiSigAOContinuous)
        return (pf_me4000MultiSigAOContinuous)(
            uiBoardNumber,
            psBuffer,
            ulDataCount,
            pCallbackProc,
            pCallbackContext,
            ulTimeOutSeconds,
            pulNumberOfValuesWritten);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOStart(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigAOStart)
        return (pf_me4000MultiSigAOStart)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOAppendNewValues(
    unsigned int uiBoardNumber,
    short* psBuffer,
    unsigned long ulNumberOfValuesToAppend,
    int iExecutionMode,
    unsigned long* pulNumberOfValuesAppended)
{
    if (pf_me4000MultiSigAOAppendNewValues)
        return (pf_me4000MultiSigAOAppendNewValues)(
            uiBoardNumber,
            psBuffer,
            ulNumberOfValuesToAppend,
            iExecutionMode,
            pulNumberOfValuesAppended);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOStop(
    unsigned int uiBoardNumber,
    int iStopMode)
{
    if (pf_me4000MultiSigAOStop)
        return (pf_me4000MultiSigAOStop)(
            uiBoardNumber,
            iStopMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOVoltToDigit(
    double dVolt,
    short* psDigit)
{
    if (pf_me4000MultiSigAOVoltToDigit)
        return (pf_me4000MultiSigAOVoltToDigit)(
            dVolt,
            psDigit);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOReset(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigAOReset)
        return (pf_me4000MultiSigAOReset)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOGetStatus(
    unsigned int uiBoardNumber,
    int iWaitIdle,
    int* piStatus)
{
    if (pf_me4000MultiSigAOGetStatus)
        return (pf_me4000MultiSigAOGetStatus)(
            uiBoardNumber,
            iWaitIdle,
            piStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me4000MultiSigAOClose(
    unsigned int uiBoardNumber)
{
    if (pf_me4000MultiSigAOClose)
        return (pf_me4000MultiSigAOClose)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000ErrorSetDefaultProc(
    int iDefaultProcStatus)
{
    if (pf_me6000ErrorSetDefaultProc)
        return (pf_me6000ErrorSetDefaultProc)(
            iDefaultProcStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000ErrorSetUserProc(
    ME4000_P_ERROR_PROC pErrorProc)
{
    if (pf_me6000ErrorSetUserProc)
        return (pf_me6000ErrorSetUserProc)(
            pErrorProc);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000ErrorGetMessage(
    int iErrorCode,
    char* pcBuffer,
    unsigned int uiBufferSize)
{
    if (pf_me6000ErrorGetMessage)
        return (pf_me6000ErrorGetMessage)(
            iErrorCode,
            pcBuffer,
            uiBufferSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000ErrorGetLastMessage(
    char* pcBuffer,
    unsigned int uiBufferSize)
{
    if (pf_me6000ErrorGetLastMessage)
        return (pf_me6000ErrorGetLastMessage)(
            pcBuffer,
            uiBufferSize);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000GetDLLVersion(
    unsigned long* pulVersion)
{
    if (pf_me6000GetDLLVersion)
        return (pf_me6000GetDLLVersion)(
            pulVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000GetDriverVersion(
    unsigned long* pulVersion)
{
    if (pf_me6000GetDriverVersion)
        return (pf_me6000GetDriverVersion)(
            pulVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000FrequencyToTicks(
    double dRequiredFreq,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedFreq)
{
    if (pf_me6000FrequencyToTicks)
        return (pf_me6000FrequencyToTicks)(
            dRequiredFreq,
            pulTicksLowPart,
            pulTicksHighPart,
            pdAchievedFreq);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000TimeToTicks(
    double dRequiredTime,
    unsigned long* pulTicksLowPart,
    unsigned long* pulTicksHighPart,
    double* pdAchievedTime)
{
    if (pf_me6000TimeToTicks)
        return (pf_me6000TimeToTicks)(
            dRequiredTime,
            pulTicksLowPart,
            pulTicksHighPart,
            pdAchievedTime);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000GetBoardVersion(
    unsigned int uiBoardNumber,
    unsigned short* pusVersion)
{
    if (pf_me6000GetBoardVersion)
        return (pf_me6000GetBoardVersion)(
            uiBoardNumber,
            pusVersion);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000GetSerialNumber(
    unsigned int uiBoardNumber,
    unsigned long* pulSerialNumber)
{
    if (pf_me6000GetSerialNumber)
        return (pf_me6000GetSerialNumber)(
            uiBoardNumber,
            pulSerialNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOSingle(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iTriggerMode,
    int iReserved,
    unsigned long ulReserved,
    short sValue    )
{
    if (pf_me6000AOSingle)
        return (pf_me6000AOSingle)(
            uiBoardNumber,
            uiChannelNumber,
            iTriggerMode,
            iReserved,
            ulReserved,
            sValue    );
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOUpdate(
    unsigned int uiBoardNumber)
{
    if (pf_me6000AOUpdate)
        return (pf_me6000AOUpdate)(
            uiBoardNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    unsigned long ulTicks,
    int iTriggerMode,
    int iExtTriggerEdge)
{
    if (pf_me6000AOConfig)
        return (pf_me6000AOConfig)(
            uiBoardNumber,
            uiChannelNumber,
            ulTicks,
            iTriggerMode,
            iExtTriggerEdge);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOWraparound(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    short* psBuffer,
    unsigned long ulDataCount,
    unsigned long ulLoops,
    int iExecutionMode,
    ME6000_P_AO_TERMINATE_PROC pTerminateProc,
    void* pTerminateContext,
    unsigned long ulTimeOutSeconds)
{
    if (pf_me6000AOWraparound)
        return (pf_me6000AOWraparound)(
            uiBoardNumber,
            uiChannelNumber,
            psBuffer,
            ulDataCount,
            ulLoops,
            iExecutionMode,
            pTerminateProc,
            pTerminateContext,
            ulTimeOutSeconds);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOContinuous(
            uiBoardNumber,
            uiChannelNumber,
            psBuffer,
            ulDataCount,
            pCallbackProc,
            pCallbackContext,
            ulTimeOutSeconds,
            pulNumberOfValuesWritten)
{
    if (pf_me6000AOContinuous)
        return (pf_me6000AOContinuous)(
            uiBoardNumber,
            uiChannelNumber,
            psBuffer,
            ulDataCount,
            pCallbackProc,
            pCallbackContext,
            ulTimeOutSeconds,
            pulNumberOfValuesWritten);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOStart(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber)
{
    if (pf_me6000AOStart)
        return (pf_me6000AOStart)(
            uiBoardNumber,
            uiChannelNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOAppendNewValues(
            uiBoardNumber,
            uiChannelNumber,
            psBuffer,
            ulNumberOfValuesToAppend,
            iExecutionMode,
            pulNumberOfValuesAppended)
{
    if (pf_me6000AOAppendNewValues)
        return (pf_me6000AOAppendNewValues)(
            uiBoardNumber,
            uiChannelNumber,
            psBuffer,
            ulNumberOfValuesToAppend,
            iExecutionMode,
            pulNumberOfValuesAppended);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOStop(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iStopMode)
{
    if (pf_me6000AOStop)
        return (pf_me6000AOStop)(
            uiBoardNumber,
            uiChannelNumber,
            iStopMode);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOVoltToDigit(
    double dVolt,
    short* psDigit)
{
    if (pf_me6000AOVoltToDigit)
        return (pf_me6000AOVoltToDigit)(
            dVolt,
            psDigit);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOReset(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber)
{
    if (pf_me6000AOReset)
        return (pf_me6000AOReset)(
            uiBoardNumber,
            uiChannelNumber);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOWaveGen(
            uiBoardNumber,
            uiChannelNumber,
            iShape,
            dAmplitude,
            dOffset,
            dFrequency)
{
    if (pf_me6000AOWaveGen)
        return (pf_me6000AOWaveGen)(
            uiBoardNumber,
            uiChannelNumber,
            iShape,
            dAmplitude,
            dOffset,
            dFrequency);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}

int me6000AOGetStatus(
    unsigned int uiBoardNumber,
    unsigned int uiChannelNumber,
    int iWaitIdle,
    int* piStatus)
{
    if (pf_me6000AOGetStatus)
        return (pf_me6000AOGetStatus)(
            uiBoardNumber,
            uiChannelNumber,
            iWaitIdle,
            piStatus);
    else
    {
        printf("Error on call function in line %d\n", __LINE__);
        return FUNCTIONNOTFOUND;
    }
}




































/* -------------------------  Close Function ----------------------------*/
void meClose (void)
{
    if (hDll)
    {
        FreeLibrary(hDll);
    }
}
