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
#define DLLNAME             "me9x_32.dll"



typedef   int(__cdecl *PF_ME9XGETDLLVERSION)    (void);
typedef   int(__cdecl *PF_ME9XGETDRIVERVERSION) (int *piDriverVersion);
typedef   int(__cdecl *PF_ME9XGETBOARDVERSION)  (int iBoardNumber, int *piVersion);
typedef   int(__cdecl *PF_ME9XGETDRVERRMESS)(char *pcErrorText);

typedef   int(__cdecl *PF_ME9XENABLEINT)(int iBoardNumber, PSERVICE_PROC IrqFunc);
typedef   int(__cdecl *PF_ME9XDISABLEINT)(int iBoardNumber);
typedef   int(__cdecl *PF_ME9XGETIRQCNT)(int iBoardNumber, int dwTyp, int* dwCnt);

typedef   int(__cdecl *PF_ME9XDIGETBIT)(int iBoardNumber, int iBitNo, int *piBitValue);
typedef   int(__cdecl *PF_ME9XDIGETBYTE)(int iBoardNumber, int iPortNo, int *piValue);
typedef   int(__cdecl *PF_ME9XDOSETBIT)(int iBoardNumber, int iBitNo, int iBitValue);
typedef   int(__cdecl *PF_ME9XDOSETBYTE)(int iBoardNumber, int iPortNo, int iValue);

typedef   int(__cdecl *PF_ME9XGETSERIALNUMBER)  (int iBoardNumber, int *piSerialNumber);
typedef   int(__cdecl *PF_ME9XGETDEVINFO)       (int iBoardNumber, PDEVICEINFOSTRUCT DevInfo);
typedef   int(__cdecl *PF_ME9XINPORTBYTE)       (int iBoardNumber, int iPortOffset, int* pbValue);
typedef   int(__cdecl *PF_ME9XOUTPORTBYTE)      (int iBoardNumber, int iPortOffset, int bValue);
typedef   int(__cdecl *PF_ME9XINPORTWORD)       (int iBoardNumber, int iPortOffset, int* pwValue);
typedef   int(__cdecl *PF_ME9XOUTPORTWORD)      (int iBoardNumber, int iPortOffset, int wValue);
typedef   int(__cdecl *PF_ME9XINPORTDWORD)      (int iBoardNumber, int iPortOffset, int* pwValue);
typedef   int(__cdecl *PF_ME9XOUTPORTDWORD)     (int iBoardNumber, int iPortOffset, int wValue);
typedef   int(__cdecl *PF_ME9XRESETBOARD)       (int iBoardNumber);
typedef   int(__cdecl *PF_ME9XINITBOARD)        (int iBoardNumber);

typedef   int(__cdecl *PF_ME9XWRITEUSERSTRING)  (int iBoardNumber, char* pcUserText);
typedef   int(__cdecl *PF_ME9XREADUSERSTRING)   (int iBoardNumber, char* pcUserText, int iMaxLength);



// -------------------- Function Prototypes --------------------------------

void meOpen(void);
void meClose(void);

int me9xGetDLLVersion(void);
int me9xGetDriverVersion(int *piDriverVersion);
int me9xGetBoardVersion(int iBoardNumber, int *piVersion);
int me9xGetDrvErrMess(char *pcErrorText);

int me9xEnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc);
int me94EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc);
int me96EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc);
int me9xDisableInt(int iBoardNumber);
int me94DisableInt(int iBoardNumber);
int me96DisableInt(int iBoardNumber);
int me9xGetIrqCnt(int iBoardNumber, int dwTyp, int* dwCnt);

int me9xDIGetBit(int iBoardNumber, int iBitNo, int *piBitValue);
int me94DIGetBit(int iBoardNumber, int iBitNo, int *piBitValue);
int me96DIGetBit(int iBoardNumber, int iBitNo, int *piBitValue);
int me9xDIGetByte(int iBoardNumber, int iPortNo, int *piValue);
int me94DIGetByte(int iBoardNumber, int iPortNo, int *piValue);
int me96DIGetByte(int iBoardNumber, int iPortNo, int *piValue);
int me9xDOSetBit(int iBoardNumber, int iBitNo, int iBitValue);
int me95DOSetBit(int iBoardNumber, int iBitNo, int iBitValue);
int me96DOSetBit(int iBoardNumber, int iBitNo, int iBitValue);
int me9xDOSetByte(int iBoardNumber, int iPortNo, int iValue);
int me95DOSetByte(int iBoardNumber, int iPortNo, int iValue);
int me96DOSetByte(int iBoardNumber, int iPortNo, int iValue);

int me9xGetSerialNumber(int iBoardNumber, int *piSerialNumber);
int me9xGetDevInfo (int iBoardNumber, PDEVICEINFOSTRUCT DevInfo);
int me9xInportByte(int iBoardNumber, int iPortOffset, int* pbValue);
int me9xOutportByte(int iBoardNumber, int iPortOffset, int bValue);
int me9xInportWord(int iBoardNumber, int iPortOffset, int* pwValue);
int me9xOutportWord(int iBoardNumber, int iPortOffset, int wValue);
int me9xInportDWord(int iBoardNumber, int iPortOffset, int* pwValue);
int me9xOutportDWord(int iBoardNumber, int iPortOffset, int wValue);
int me9xResetBoard(int iBoardNumber);
int me9xInitBoard(int iBoardNumber);

int me9xWriteUserString(int iBoardNumber, char* pcUserText);
int me9xReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);



// we support both function names for obsolete functions
// (with or without "_"):
// _meAnyFunction(); and
// meAnyFunction();
#define _me9xGetDLLVersion      me9xGetDLLVersion
#define _me9xGetBoardVersion    me9xGetBoardVersion
#define _me94EnableInt          me94EnableInt
#define _me96EnableInt          me96EnableInt
#define _me94DisableInt         me94DisableInt
#define _me96DisableInt         me96DisableInt
#define _me9xGetIrqCnt          me9xGetIrqCnt
#define _me9xGetDrvErrMess      me9xGetDrvErrMess
#define _me94DIGetBit           me94DIGetBit
#define _me96DIGetBit           me96DIGetBit
#define _me94DIGetByte          me94DIGetByte
#define _me96DIGetByte          me96DIGetByte
#define _me95DOSetBit           me95DOSetBit
#define _me96DOSetBit           me96DOSetBit
#define _me95DOSetByte          me95DOSetByte
#define _me96DOSetByte          me96DOSetByte

#endif
