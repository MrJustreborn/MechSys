
#include <windows.h>
#include <winioctl.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dll.h"


extern "C" {

_declspec(dllexport) int _stdcall VBme9xGetDLLVersion()
{
	return 0x00;
}

_declspec(dllexport) int _stdcall VBme9xGetBoardVersion(int iBoardNumber, int *iVersion)
{
	return 1;
}

_declspec(dllexport) int _stdcall VBme94EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _stdcall VBme94DisableInt(int iBoardNumber, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _stdcall VBme96EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _stdcall VBme96DisableInt(int iBoardNumber, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme9xGetDrvErrMess(char *errortext )
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme9xGetIrqCnt(int iBoardNumber, int dwTyp, int* dwCnt)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme9xInportByte(int iBoardNumber, int iPortOffset, int* bValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme9xOutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme9xInportWord(int iBoardNumber, int iPortOffset, int* wValue)
{
	return 1;
}

_declspec(dllexport) int   _stdcall VBme9xOutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
	return 1;
}

int _declspec(dllexport) _stdcall VBme94DIGetBit(int iBoardNumber, int iBitNo, int *piValue)
{
	return 1;
}

int _declspec(dllexport) _stdcall VBme96DIGetBit(int iBoardNumber, int iBitNo, int *piValue)
{
	return 1;
}

int _declspec(dllexport) _stdcall VBme94DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
	return 1;
}

int _declspec(dllexport) _stdcall VBme96DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
	return 1;
}

int _declspec(dllexport) _stdcall VBme95DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return 1;
}

int _declspec(dllexport) _stdcall VBme96DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return 1;
}

int _declspec(dllexport) _stdcall VBme95DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
	return 1;
}

int _declspec(dllexport) _stdcall VBme96DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
	return 1;
}

}
