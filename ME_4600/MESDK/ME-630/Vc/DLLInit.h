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
#define DLLNAME             "me630.dll"


typedef void (_stdcall *PSERVICE_PROC) (void);

typedef   int(__cdecl *PF_ME630GETDLLVERSION)   (void);
typedef   int(__cdecl *PF_ME630GETBOARDVERSION) (int iBoardNumber, int *piVersion);
typedef   int(__cdecl *PF_ME630RESETRELAYS)     (int iBoardNumber);
typedef   int(__cdecl *PF_ME630ENABLEINT)       (int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext);
typedef   int(__cdecl *PF_ME630DISABLEINT)      (int iBoardNumber, int iIRQNum);
typedef   int(__cdecl *PF_ME630GETDRVERRMESS)   (char *pcErrortext, int iBufferSize);
typedef   int(__cdecl *PF_ME630DIGETTTLBIT)     (int iBoardNumber, int iBitNo, int *piBitValue);
typedef   int(__cdecl *PF_ME630DIGETTTLBYTE)    (int iBoardNumber, unsigned char *pcValue);
typedef   int(__cdecl *PF_ME630DIGETOPTOBIT)    (int iBoardNumber, int iBitNo, int *piBitValue);
typedef   int(__cdecl *PF_ME630DIGETOPTOBYTE)   (int iBoardNumber, unsigned char *pcValue);
typedef   int(__cdecl *PF_ME630DOSETRELAYBIT)   (int iBoardNumber, int iBitNo, int iBitValue);
typedef   int(__cdecl *PF_ME630DOSETRELAYWORD)  (int iBoardNumber, unsigned short usValue);
typedef   int(__cdecl *PF_ME630DIGETRELAYBIT)   (int iBoardNumber, int iBitNo, int *piBitValue);
typedef   int(__cdecl *PF_ME630DIGETRELAYWORD)  (int iBoardNumber, unsigned short *pusValue);
typedef   int(__cdecl *PF_ME630GETIRQCNT)       (int iBoardNumber, int iIRQNum, int* piCnt);
typedef   int(__cdecl *PF_ME630GETDEVINFO)      (int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
typedef   int(__cdecl *PF_ME630WRITEUSERSTRING) (int iBoardNumber, char* pcUserText);
typedef   int(__cdecl *PF_ME630READUSERSTRING)  (int iBoardNumber, char* pcUserText, int iMaxLength);

typedef   int(__cdecl *PF_ME630DIORESETALL)		(int iBoardNumber);
typedef   int(__cdecl *PF_ME630DIOCONFIG)		(int iBoardNumber, int iPortNumber, int iPortDirection);
typedef   int(__cdecl *PF_ME630DIOGETBIT)		(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue);
typedef   int(__cdecl *PF_ME630DIOGETBYTE)		(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue);
typedef   int(__cdecl *PF_ME630DIOSETBIT)		(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue);
typedef   int(__cdecl *PF_ME630DIOSETBYTE)		(int iBoardNumber, int iPortNumber, unsigned char ucByteValue);

// -------------------- Function Prototypes --------------------------------

void meOpen(void);
void meClose(void);
int me630GetDLLVersion(void);
int me630GetBoardVersion(int iBoardNumber, int *piVersion);
int me630ResetRelays(int iBoardNumber);
int me630EnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext);
int me630DisableInt(int iBoardNumber, int iIRQNum);
int me630GetDrvErrMess(char *pcErrortext, int iBufferSize);
int me630DIGetTTLBit(int iBoardNumber, int iBitNo, int *piBitValue);
int me630DIGetTTLByte(int iBoardNumber, unsigned char *pcValue);
int me630DIGetOptoBit(int iBoardNumber, int iBitNo, int *piBitValue);
int me630DIGetOptoByte(int iBoardNumber, unsigned char *pcValue);
int me630DOSetRelayBit(int iBoardNumber, int iBitNo, int iBitValue);
int me630DOSetRelayWord(int iBoardNumber, unsigned short usValue);
int me630DIGetRelayBit(int iBoardNumber, int iBitNo, int *piBitValue);
int me630DIGetRelayWord(int iBoardNumber, unsigned short *pusValue);
int me630GetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt);
int me630GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
int me630WriteUserString(int iBoardNumber, char* pcUserText);
int me630ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);

int me630DIOResetAll(int iBoardNumber);
int me630DIOConfig(int iBoardNumber, int iPortNumber, int iPortDirection);
int me630DIOGetBit(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue);
int me630DIOGetByte(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue);
int me630DIOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue);
int me630DIOSetByte(int iBoardNumber, int iPortNumber, unsigned char ucByteValue);

// we support both function names (with or without "_"):
// _meAnyFunction(); and
// meAnyFunction();
#define _me630GetDLLVersion     me630GetDLLVersion
#define _me630GetBoardVersion   me630GetBoardVersion
#define _me630ResetRelays       me630ResetRelays
#define _me630EnableInt         me630EnableInt
#define _me630DisableInt        me630DisableInt
#define _me630GetDrvErrMess     me630GetDrvErrMess
#define _me630DIGetTTLBit       me630DIGetTTLBit
#define _me630DIGetTTLByte      me630DIGetTTLByte
#define _me630DIGetOptoBit      me630DIGetOptoBit
#define _me630DIGetOptoByte     me630DIGetOptoByte
#define _me630DOSetRelayBit     me630DOSetRelayBit
#define _me630DOSetRelayWord    me630DOSetRelayWord
#define _me630DIGetRelayBit     me630DIGetRelayBit
#define _me630DIGetRelayWord    me630DIGetRelayWord
#define _me630GetIrqCnt         me630GetIrqCnt
#define _me630GetDevInfo        me630GetDevInfo
#define _me630WriteUserString   me630WriteUserString
#define _me630ReadUserString    me630ReadUserString

#define _me630DIOResetAll		me630DIOResetAll	
#define _me630DIOConfig			me630DIOConfig		
#define _me630DIOGetBit			me630DIOGetBit		
#define _me630DIOGetByte		me630DIOGetByte	
#define _me630DIOSetBit			me630DIOSetBit		
#define _me630DIOSetByte		me630DIOSetByte	

#endif
