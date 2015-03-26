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
USEFILE("..\Common.h");
USEFILE("..\meDefs.h");
USEFILE("..\DLLInit.h");
USEUNIT("DLLInit.cpp");
#endif


PF_ME6x00FREQUENCYTOTIMER       pf_me6x00FrequencyToTimer;
PF_ME6x00GETBOARDVERSION        pf_me6x00GetBoardVersion;
PF_ME6x00GETDEVINFO             pf_me6x00GetDevInfo;
PF_ME6x00GETDLLVERSION          pf_me6x00GetDLLVersion;
PF_ME6x00GETDRIVERVERSION       pf_me6x00GetDriverVersion;
PF_ME6x00GETSERIALNUMBER        pf_me6x00GetSerialNumber;
PF_ME6x00AOCONTINUOUS           pf_me6x00AOContinuous;
PF_ME6x00AOCONTINUOUSEX         pf_me6x00AOContinuousEx;
PF_ME6x00AORESET                pf_me6x00AOReset;
PF_ME6x00AORESETALL             pf_me6x00AOResetAll;
PF_ME6x00AOSETTIMER             pf_me6x00AOSetTimer;
PF_ME6x00AOSETTRIGGER           pf_me6x00AOSetTrigger;
PF_ME6x00AOSINGLE               pf_me6x00AOSingle;
PF_ME6x00AOSTART                pf_me6x00AOStart;
PF_ME6x00AOSTART4               pf_me6x00AOStart4;
PF_ME6x00AOSTOP                 pf_me6x00AOStop;
PF_ME6x00AOSTOPEX               pf_me6x00AOStopEx;
PF_ME6x00AOWAVEGEN              pf_me6x00AOWaveGen;
PF_ME6x00AOWRAPAROUND           pf_me6x00AOWrapAround;
PF_ME6x00GETDRVERRMESS          pf_me6x00GetDrvErrMess;


HINSTANCE hDll;


void meOpen( void )
{
    hDll = LoadLibrary(DLLNAME);      // load the library
    if(hDll == NULL)
    {
	    MessageBox( NULL, "DLL not Found", "Error", MB_OK | MB_ICONINFORMATION );
	    exit(1);
    }
    
    pf_me6x00FrequencyToTimer = (PF_ME6x00FREQUENCYTOTIMER)
                              (GetProcAddress(hDll,"me6x00FrequencyToTimer"));
    pf_me6x00GetBoardVersion  = (PF_ME6x00GETBOARDVERSION)
                              (GetProcAddress(hDll,"me6x00GetBoardVersion"));
    pf_me6x00GetDLLVersion    = (PF_ME6x00GETDLLVERSION)
                              (GetProcAddress(hDll,"me6x00GetDLLVersion"));
    pf_me6x00GetDevInfo       = (PF_ME6x00GETDEVINFO)
                              (GetProcAddress(hDll,"me6x00GetDevInfo"));
    pf_me6x00GetDriverVersion = (PF_ME6x00GETDRIVERVERSION)
                              (GetProcAddress(hDll,"me6x00GetDriverVersion"));
    pf_me6x00GetSerialNumber  = (PF_ME6x00GETSERIALNUMBER)
                              (GetProcAddress(hDll,"me6x00GetSerialNumber"));
    
    pf_me6x00AOContinuous     = (PF_ME6x00AOCONTINUOUS)
                              (GetProcAddress(hDll,"me6x00AOContinuous"));
    pf_me6x00AOContinuousEx   = (PF_ME6x00AOCONTINUOUSEX)
                              (GetProcAddress(hDll,"me6x00AOContinuousEx"));
    pf_me6x00AOReset          = (PF_ME6x00AORESET)
                              (GetProcAddress(hDll,"me6x00AOReset"));
    pf_me6x00AOResetAll       = (PF_ME6x00AORESETALL)
                              (GetProcAddress(hDll,"me6x00AOResetAll"));
    pf_me6x00AOSetTimer       = (PF_ME6x00AOSETTIMER)
                              (GetProcAddress(hDll,"me6x00AOSetTimer"));
    pf_me6x00AOSetTrigger     = (PF_ME6x00AOSETTRIGGER)
                              (GetProcAddress(hDll,"me6x00AOSetTrigger"));
    pf_me6x00AOSingle         = (PF_ME6x00AOSINGLE)
                              (GetProcAddress(hDll,"me6x00AOSingle"));
    pf_me6x00AOStart          = (PF_ME6x00AOSTART)
                              (GetProcAddress(hDll,"me6x00AOStart"));
    pf_me6x00AOStart4         = (PF_ME6x00AOSTART4)
                              (GetProcAddress(hDll,"me6x00AOStart4"));
    pf_me6x00AOStop           = (PF_ME6x00AOSTOP)
                              (GetProcAddress(hDll,"me6x00AOStop"));
    pf_me6x00AOStopEx         = (PF_ME6x00AOSTOPEX)
                              (GetProcAddress(hDll,"me6x00AOStopEx"));
    pf_me6x00AOWaveGen        = (PF_ME6x00AOWAVEGEN)
                              (GetProcAddress(hDll,"me6x00AOWaveGen"));
    pf_me6x00AOWrapAround     = (PF_ME6x00AOWRAPAROUND)
                              (GetProcAddress(hDll,"me6x00AOWrapAround"));
    
    pf_me6x00GetDrvErrMess    = (PF_ME6x00GETDRVERRMESS)
                              (GetProcAddress(hDll,"me6x00GetDrvErrMess"));
}

//------ me6x00Close ------
void meClose(void)
{
  FreeLibrary(hDll); // close the library
}

//----------------------------------------------------------------------
// Wrappers for all Functions
//----------------------------------------------------------------------

//------ me6x00FrequencyToTimer ------
int me6x00FrequencyToTimer(double dFreq)
{
  if(pf_me6x00FrequencyToTimer)
    return (pf_me6x00FrequencyToTimer)(dFreq);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00GetBoardVersion ------
int me6x00GetBoardVersion(int iBoardNumber, int *piVersion)
{
  if(pf_me6x00GetBoardVersion)
    return (pf_me6x00GetBoardVersion)(iBoardNumber, piVersion);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00GetDevInfo ------
int me6x00GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
  if(pf_me6x00GetDevInfo)
    return (pf_me6x00GetDevInfo)(iBoardNumber, pDevInfo);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00GetDLLVersion ------
int me6x00GetDLLVersion(void)
{
  if(pf_me6x00GetDLLVersion)
    return (pf_me6x00GetDLLVersion)();
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00GetDriverVersion ------
int me6x00GetDriverVersion(int *piDriverVersion)
{
  if(pf_me6x00GetDriverVersion)
    return (pf_me6x00GetDriverVersion)(piDriverVersion);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00GetSerialNumber ------
int me6x00GetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
  if(pf_me6x00GetSerialNumber)
    return (pf_me6x00GetSerialNumber)(iBoardNumber, piSerialNumber);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOContinuous ------
int me6x00AOContinuous(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
  if(pf_me6x00AOContinuous)
    return (pf_me6x00AOContinuous)(iBoardNumber, iChannel, iSize, psBuffer);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOContinuousEx ------
int me6x00AOContinuousEx(int iBoardNumber, int iChannel, int iSize, short *psBuffer,
                         int iLoops, PVOID_PROC pCallback, void* pArgs)
{
  if(pf_me6x00AOContinuousEx)
    return (pf_me6x00AOContinuousEx)(iBoardNumber, iChannel, iSize, psBuffer,
                                     iLoops, pCallback, pArgs);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOReset ------
int me6x00AOReset(int iBoardNumber, int iChannel)
{
  if(pf_me6x00AOReset)
    return (pf_me6x00AOReset)(iBoardNumber, iChannel);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOResetAll ------
int me6x00AOResetAll(int iBoardNumber)
{
  if(pf_me6x00AOResetAll)
    return (pf_me6x00AOResetAll)(iBoardNumber);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOSetTimer ------
int me6x00AOSetTimer(int iBoardNumber, int iChannel, int iTicks)
{
  if(pf_me6x00AOSetTimer)
    return (pf_me6x00AOSetTimer)(iBoardNumber, iChannel, iTicks);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOSetTrigger ------
int me6x00AOSetTrigger(int iBoardNumber, int iChannel, int iModePolarity)
{
  if(pf_me6x00AOSetTrigger)
    return (pf_me6x00AOSetTrigger)(iBoardNumber, iChannel, iModePolarity);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOSingle ------
int me6x00AOSingle(int iBoardNumber, int iChannel, int iValue)
{
  if(pf_me6x00AOSingle)
    return (pf_me6x00AOSingle)(iBoardNumber, iChannel, iValue);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOStart ------
int me6x00AOStart(int iBoardNumber, int iChannel)
{
  if(pf_me6x00AOStart)
    return (pf_me6x00AOStart)(iBoardNumber, iChannel);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOStart4 ------
int me6x00AOStart4(int iBoardNumber)
{
  if(pf_me6x00AOStart4)
    return (pf_me6x00AOStart4)(iBoardNumber);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOStop ------
int me6x00AOStop(int iBoardNumber, int iChannel)
{
  if(pf_me6x00AOStop)
    return (pf_me6x00AOStop)(iBoardNumber, iChannel);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOStopEx ------
int me6x00AOStopEx(int iBoardNumber, int iChannel)
{
  if(pf_me6x00AOStopEx)
    return (pf_me6x00AOStopEx)(iBoardNumber, iChannel);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOWaveGen ------
int me6x00AOWaveGen(int iBoardNumber, int iChannel, int iShape, double dAmplitude,
                    double dOffset, double dFreq)
{
  if(pf_me6x00AOWaveGen)
    return (pf_me6x00AOWaveGen)(iBoardNumber, iChannel, iShape, dAmplitude, dOffset, dFreq);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00AOWrapAround ------
int me6x00AOWrapAround(int iBoardNumber, int iChannel, int iSize, short *psBuffer)
{
  if(pf_me6x00AOWrapAround)
    return (pf_me6x00AOWrapAround)(iBoardNumber, iChannel, iSize, psBuffer);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}

//------ me6x00GetDrvErrMess ------
int me6x00GetDrvErrMess(char *pcErrortext, int iBufferSize)
{
  if(pf_me6x00GetDrvErrMess)
    return (pf_me6x00GetDrvErrMess)(pcErrortext, iBufferSize);
  else
  {
    printf("Error on call function in line %d\n", __LINE__);
    return FUNCTIONNOTFOUND;
  }
}
