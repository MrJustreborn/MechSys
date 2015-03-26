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

#include "meDefs.h"

#define SUCCESS             0x01
#define DLLNOTFOUND         0x02
#define FUNCTIONNOTFOUND    0x03
#define DLLNAME             "me8100.dll"


typedef   int(__cdecl *PF_ME8100GETDLLVERSION) (void);
typedef   int(__cdecl *PF_ME8100GETBOARDVERSION) (int iBoardNumber, int *piVersion);
typedef   int(__cdecl *PF_ME8100PROMVERSION)(int iBoardNumber, int *piVersion);
typedef   int(__cdecl *PF_ME8100ENABLEINT) (int iBoardNumber, int iRegisterSet,
                                                    ME_PSERVICE_PROC IrqFunc, int iContext);
typedef   int(__cdecl *PF_ME8100DISABLEINT)(int iBoardNumber, int iRegisterSet);
typedef   int(__cdecl *PF_ME8100GETDRVERRMESS) (char *pcErrortext, int iBufferSize);
typedef   int(__cdecl *PF_ME8100DIGETINTSTATUS) (int iBoardNumber, int iRegisterSet, int *piValue);
typedef   int(__cdecl *PF_ME8100DIOSETINTMODE) (int iBoardNumber, int iRegisterSet, int iMode);
typedef   int(__cdecl *PF_ME8100DIOSETTRISTATEON) (int iBoardNumber, int iRegisterSet);
typedef   int(__cdecl *PF_ME8100DIOSETTRISTATEOFF) (int iBoardNumber, int iRegisterSet);
typedef   int(__cdecl *PF_ME8100DIOSETPATTERN) (int iBoardNumber, int iRegisterSet, int iPattern);
typedef   int(__cdecl *PF_ME8100DIOSETMASK) (int iBoardNumber, int iRegisterSet, int iMask);
typedef   int(__cdecl *PF_ME8100DIGETBIT) (int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue);
typedef   int(__cdecl *PF_ME8100DIGETWORD) (int iBoardNumber, int iRegisterSet, int *piValue);
typedef   int(__cdecl *PF_ME8100DOSETBIT) (int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue);
typedef   int(__cdecl *PF_ME8100DOSETWORD) (int iBoardNumber, int iRegisterSet, int iValue);
typedef   int(__cdecl *PF_ME8100GETIRQCOUNT) (int iBoardNumber, int iRegisterSet, int* piCnt);
typedef   int(__cdecl *PF_ME8100GETDEVINFO) (int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
typedef   int(__cdecl *PF_ME8100WRITEUSERSTRING) (int iBoardNumber, char* pcUserText);
typedef   int(__cdecl *PF_ME8100READUSERSTRING) (int iBoardNumber, char* pcUserText, int iMaxLength);
typedef   int(__cdecl *PF_ME8100CNTWRITE) (int iBoardNumber, int iCounter, int iMode, int iValue);
typedef   int(__cdecl *PF_ME8100CNTREAD) (int iBoardNumber, int iCounter, int* piValue);
typedef   int(__cdecl *PF_ME8100SETSINKSOURCEMODE) (int iBoardNumber, int iRegisterSet, int imode);





// -------------------- Function Prototypes --------------------------------

void meOpen (void);
void meClose (void);

int me8100GetDLLVersion(void);
int me8100GetBoardVersion(int iBoardNumber, int *piVersion);
int me8100PROMVersion(int iBoardNumber, int *piVersion);
int me8100EnableInt(int iBoardNumber, int iRegisterSet,
                            ME_PSERVICE_PROC IrqFunc, int iContext);
int me8100DisableInt(int iBoardNumber, int iRegisterSet);
int me8100GetDrvErrMess(char *pcErrortext, int iBufferSize);
int me8100DIGetIntStatus(int iBoardNumber, int iRegisterSet, int *piValue);
int me8100DIOSetIntMode(int iBoardNumber, int iRegisterSet, int iMode);
int me8100DIOSetTristateON(int iBoardNumber, int iRegisterSet);
int me8100DIOSetTristateOFF(int iBoardNumber, int iRegisterSet);
int me8100DIOSetPattern(int iBoardNumber, int iRegisterSet, int iPattern);
int me8100DIOSetMask(int iBoardNumber, int iRegisterSet, int iMask);
int me8100DIGetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int *piBitValue);
int me8100DIGetWord(int iBoardNumber, int iRegisterSet, int *piValue);
int me8100DOSetBit(int iBoardNumber, int iRegisterSet, int iBitNo, int iBitValue);
int me8100DOSetWord(int iBoardNumber, int iRegisterSet, int iValue);
int me8100GetIrqCnt(int iBoardNumber, int iRegisterSet, int* piCnt);
int me8100GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
int me8100WriteUserString(int iBoardNumber, char* pcUserText);
int me8100ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);
int me8100CntWrite(int iBoardNumber, int iCounter, int iMode, int iValue);
int me8100CntRead(int iBoardNumber, int iCounter, int* piValue);
int me8100SetSinkSourceMode(int iBoardNumber, int iRegisterSet, int imode);


#endif
