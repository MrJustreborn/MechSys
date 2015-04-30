
#include <stdio.h>
#include <windows.h>

#include "dll.h"



int meGetDLLVersion()
{
    return 0x00090099;
}



int meGetDriverVersion(int *piDriverVersion)
{
    *piDriverVersion = 0x00090098;

    return TRUE;
}



int meGetBoardVersion(int iBoardNumber, int *piBoardVersion)
{
    *piBoardVersion = 0x00090097;

    return TRUE;
}



int meGetSerialNumber(int iBoardNumber, int *piSerialNumber)
{
    *piSerialNumber = 0x00090096;

    return TRUE;
}



int meGetIrqCnt(int iBoardNumber, int iIRQNum, int* piCnt)
{
    *piCnt = 0;

    return TRUE;
}



int meGetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo)
{
    pDevInfo;

    return TRUE;
}



int meWriteUserString(int iBoardNumber, char* pcUserText)
{
    pcUserText;

    return TRUE;
}



int meReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength)
{
    pcUserText, iMaxLength;

    return TRUE;
}



int meInportByte(int iBoardNumber, int iPortOffset, int* pbValue)
{
    iPortOffset, pbValue;

    return TRUE;
}



int meOutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
    iPortOffset, bValue;

    return TRUE;
}



int meInportWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    iPortOffset, pwValue;

    return TRUE;
}



int meOutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
    iPortOffset, wValue;

    return TRUE;
}



int meInportDWord(int iBoardNumber, int iPortOffset, int* pwValue)
{
    iPortOffset, pwValue;

    return TRUE;
}



int meOutportDWord(int iBoardNumber, int iPortOffset, int wValue)
{
    iPortOffset, wValue;

    return TRUE;
}



int meResetBoard(int iBoardNumber)
{
    return TRUE;
}



int meInitBoard(int iBoardNumber)
{
    return TRUE;
}



int meEnableInt(int iBoardNumber, int iIRQNum, ME_PSERVICE_PROC IrqFunc, int iContext)
{
    iIRQNum, IrqFunc, iContext;
    return TRUE;
}



int meDisableInt(int iBoardNumber, int iIRQNum)
{
    iIRQNum;
    return TRUE;
}



int meGetDrvErrMess(char *pcErrortext, int iBufferSize)
{
    pcErrortext[0] = 0;

    return TRUE;
}






int meResetRelays(int iBoardNumber)
{
    return TRUE;
}



int meDIGetTTLBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    iBitNo, piBitValue;
    return TRUE;
}



int meDIGetTTLByte(int iBoardNumber, unsigned char *pcValue)
{
    pcValue;
    return TRUE;
}



int meDIGetOptoBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    iBitNo, piBitValue;
    return TRUE;
}



int meDIGetOptoByte(int iBoardNumber, unsigned char *pcValue)
{
    pcValue;
    return TRUE;
}



int meDOSetRelayBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    iBitNo, iBitValue;
    return TRUE;
}



int meDOSetRelayWord(int iBoardNumber, unsigned short usValue)
{
    usValue;
    return TRUE;
}



int meDIGetRelayBit(int iBoardNumber, int iBitNo, int *piBitValue)
{
    iBitNo, piBitValue;
    return TRUE;
}



int meDIGetRelayWord(int iBoardNumber, unsigned short *pusValue)
{
    pusValue;
    return TRUE;
}

int meDIOResetAll(int iBoardNumber)
{
    return TRUE;
}

int meDIOConfig(int iBoardNumber, int iPortNumber, int iPortDirection)
{
    iPortNumber, iPortDirection;
	return TRUE;
}

int meDIOGetBit(int iBoardNumber, int iPortNumber, int iBitNo, int* piBitValue)
{
	iPortNumber, iBitNo, piBitValue;
    return TRUE;
}

int meDIOGetByte(int iBoardNumber, int iPortNumber, unsigned char* pucByteValue)
{
	iPortNumber, pucByteValue;
    return TRUE;
}

int meDIOSetBit(int iBoardNumber, int iPortNumber, int iBitNo, int iBitValue)
{
	iPortNumber, iBitNo, iBitValue;
    return TRUE;
}

int meDIOSetByte(int iBoardNumber, int iPortNumber, unsigned char ucByteValue)
{
	iPortNumber, ucByteValue;
    return TRUE;
}

