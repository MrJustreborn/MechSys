
#include <windows.h>
#include <winioctl.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


extern "C" {

_declspec(dllexport) int _stdcall VBme300GetDLLVersion()
{
	return 0x00;
}

_declspec(dllexport) int _stdcall VBme300PROMVersion(int iBoardNumber, int *iVersion)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300MakeChannelList(int *Channellist)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300GetDrvErrMess(char *errortext )
{
    return 1;
}

_declspec(dllexport) int   _stdcall VBme300InportByte(int iBoardNumber, int iPortOffset, int* bValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300OutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300InportWord(int iBoardNumber, int iPortOffset, int* wValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300OutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300DIOSetPortDirection(int iBoardNumber, int iPort, int iDir)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300DIGetBit(int iBoardNumber, int iPort, int iBitNo, int* Bit)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300DIGetByte(int iBoardNumber, int iPort, int* iValue)
{
	return 1;
}


_declspec(dllexport) int   _stdcall VBme300DOSetBit(int iBoardNumber, int iPort,int iBitNo, int iBitValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300DOSetByte(int iBoardNumber,  int iPort, int iValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300AISetTrigger(int iBoardNumber, int iModePolarity)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300AISingle(int iBoardNumber, int iChannelNumber, int iRange, short *pValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300AISetTimer(int iBoardNumber, int Scan0, int Scan1, int Chan)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300AISetChannelList(int iBoardNumber, int* iChannelList)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300AIScanStartEx(int iBoardNumber, int iMode, int iNumberOfSamples, HANDLE hScanReady)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300AIReadBuffer(int iBoardNumber, int iChannelNumber, int iStart, int iMode,
						  int *pNumberOfValues, short *iArray)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300AIScan(int iBoardNumber, int *iNumberOfSamples, short *iArray)
{
	return 1;
}

_declspec(dllexport) int  _stdcall VBme300AIScanStop(int iBoardNumber)
{
	return 1;
}


_declspec(dllexport) int   _stdcall VBme300AOSingle(int iBoardNumber, int iChannelNumber, int iRange, int iValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme300AOResetAll(int iBoardNumber)
{
	return 1;
}

}
