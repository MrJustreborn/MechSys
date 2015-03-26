#include <windows.h>
#include <winioctl.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


extern "C" {

_declspec(dllexport) int _cdecl _me300GetDLLVersion()
{
	return 0x00;
}

_declspec(dllexport) int  _cdecl _me300PROMVersion(int iBoardNumber, int *iVersion)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300MakeChannelList(int *Channellist)
{
	return 1;
}


_declspec(dllexport) int _cdecl _me300GetDrvErrMess(char *errortext )
{
	return 1;
}


_declspec(dllexport) int _cdecl _me300InportByte(int iBoardNumber, int iPortOffset, int* bValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300InportWord(int iBoardNumber, int iPortOffset, int* wValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300DIOSetPortDirection(int iBoardNumber, int iPort, int iDir)
{
	return 1;
}


_declspec(dllexport) int _cdecl _me300DIGetBit(int iBoardNumber, int iPort, int iBitNo, int* Bit)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300DIGetByte(int iBoardNumber, int iPort, int* iValue)
{
	return 1;
}


_declspec(dllexport) int _cdecl _me300DOSetBit(int iBoardNumber, int iPort,int iBitNo, int iBitValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300DOSetByte(int iBoardNumber,  int iPort, int iValue)
{
	return 1;
}


_declspec(dllexport) int _cdecl _me300AISetTrigger(int iBoardNumber, int iModePolarity)
{
	return 1;
}


_declspec(dllexport) int _cdecl _me300AISingle(int iBoardNumber, int iChannelNumber, int iRange, short *pValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300AISetTimer(int iBoardNumber, int Scan0, int Scan1, int Chan)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300AISetChannelList(int iBoardNumber, int* iChannelList)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300AIScanStartEx(int iBoardNumber, int iMode, int iNumberOfSamples, HANDLE hScanReady)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300AIReadBuffer(int iBoardNumber, int iChannelNumber, int iStart, int iMode,
						  int *pNumberOfValues, short *iArray)
{
	return 1;
}

_declspec(dllexport) int  _cdecl _me300AIScan(int iBoardNumber, int *iNumberOfSamples, short *iArray)
{
	return 1;
}

_declspec(dllexport) int  _cdecl _me300AIScanStop(int iBoardNumber)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300AOSingle(int iBoardNumber, int iChannelNumber, int iRange, int iValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me300AOResetAll(int iBoardNumber)
{
	return 1;
}

}

