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
#define DLLNAME             "me1000.dll"


typedef   int(__cdecl *PF_ME1000GETBOARDVERSION) (int iBoardNumber, int *piVersion);
typedef   int(__cdecl *PF_ME1000GETDEVINFO) (int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
typedef   int(__cdecl *PF_ME1000GETDLLVERSION) (void);
typedef   int(__cdecl *PF_ME1000GETDRIVERVERSION)(int *piDriverVersion);
typedef   int(__cdecl *PF_ME1000GETSERIALNUMBER)(int iBoardNumber, int *piSerialNumber);
typedef   int(__cdecl *PF_ME1000READUSERSTRING) (int iBoardNumber, char* pcUserText, int iMaxLength);
typedef   int(__cdecl *PF_ME1000WRITEUSERSTRING) (int iBoardNumber, char* pcUserText);
typedef   int(__cdecl *PF_ME1000GETDRVERRMESS) (char *pcErrortext, int iBufferSize);
typedef   int(__cdecl *PF_ME1000DIOSETPORTDIRECTION) (int iBoardNumber, int iPortNumber, int iDirection);
typedef   int(__cdecl *PF_ME1000DIORESET) (int iBoardNumber);
typedef   int(__cdecl *PF_ME1000DIGETBIT) (int iBoardNumber, int iPortNumber, int iBitNo, int *piValue);
typedef   int(__cdecl *PF_ME1000DIGETBYTE) (int iBoardNumber, int iPortNumber, int iByteNo, int *piValue);
typedef   int(__cdecl *PF_ME1000DIGETWORD) (int iBoardNumber, int iPortNumber, int iWordNo, int *piValue);
typedef   int(__cdecl *PF_ME1000DIGETLONG) (int iBoardNumber, int iPortNumber, int *piValue);
typedef   int(__cdecl *PF_ME1000DOSETBIT) (int iBoardNumber, int iPortNumber, int iBitNo, int iValue);
typedef   int(__cdecl *PF_ME1000DOSETBYTE) (int iBoardNumber, int iPortNumber, int iByteNo, int iValue);
typedef   int(__cdecl *PF_ME1000DOSETWORD) (int iBoardNumber, int iPortNumber, int iWordNo, int iValue);
typedef   int(__cdecl *PF_ME1000DOSETLONG) (int iBoardNumber, int iPortNumber, int iValue);




// -------------------- Function Prototypes --------------------------------

void meOpen(void);
void meClose(void);

int me1000GetBoardVersion(int iBoardNumber, int *piVersion);
int me1000GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
int me1000GetDLLVersion(void);
int me1000GetDriverVersion(int *piDriverVersion);
int me1000GetSerialNumber(int iBoardNumber, int *piSerialNumber);
int me1000ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);
int me1000WriteUserString(int iBoardNumber, char* pcUserText);
int me1000GetDrvErrMess(char *pcErrortext, int iBufferSize);
int me1000DIOSetPortDirection(int iBoardNumber, int iPortNumber, int iDirection);
int me1000DIOReset(int iBoardNumber);
int me1000DIGetBit (int iBoardNumber, int iPortNumber, int iBitNo, int *piValue);
int me1000DIGetByte(int iBoardNumber, int iPortNumber, int iByteNo, int *piValue);
int me1000DIGetWord(int iBoardNumber, int iPortNumber, int iWordNo, int *piValue);
int me1000DIGetLong(int iBoardNumber, int iPortNumber, int *piValue);
int me1000DOSetBit (int iBoardNumber, int iPortNumber, int iBitNo,  int iValue);
int me1000DOSetByte(int iBoardNumber, int iPortNumber, int iByteNo, int iValue);
int me1000DOSetWord(int iBoardNumber, int iPortNumber, int iWordNo, int iValue);
int me1000DOSetLong(int iBoardNumber, int iPortNumber, int iValue);

#endif
