
#include <windows.h>
#include <winioctl.h>
#include <process.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "dll.h"

extern "C" {

_declspec(dllexport) int _cdecl _me9xGetDLLVersion()
{
	return 0x00;
}

_declspec(dllexport) int _me9xGetBoardVersion(int iBoardNumber, int *iVersion)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me94EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me94DisableInt(int iBoardNumber, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me96EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me96DisableInt(int iBoardNumber, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me9xGetDrvErrMess(char *errortext )
{
	return 1;
}

_declspec(dllexport) int _cdecl _me9xGetIrqCnt(int iBoardNumber, int dwTyp, int* dwCnt)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me9xInportByte(int iBoardNumber, int iPortOffset, int* bValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me9xOutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me9xInportWord(int iBoardNumber, int iPortOffset, int* wValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me9xOutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me94DIGetBit(int iBoardNumber, int iBitNo, int *piValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me96DIGetBit(int iBoardNumber, int iBitNo, int *piValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me94DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me96DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me95DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return 1;
}

_declspec(dllexport) int _cdecl  _me96DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return 1;
}

_declspec(dllexport) int _cdecl _me95DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl _me96DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
	return 1;
}


_declspec(dllexport) int _cdecl me9xGetDLLVersion()
{
	return 0x00;
}

_declspec(dllexport) int me9xGetBoardVersion(int iBoardNumber, int *iVersion)
{
	return 1;
}

_declspec(dllexport) int _cdecl me94EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _cdecl me94DisableInt(int iBoardNumber, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _cdecl me96EnableInt(int iBoardNumber, PSERVICE_PROC IrqFunc, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _cdecl me96DisableInt(int iBoardNumber, int iServiceNo)
{
	return 1;
}

_declspec(dllexport) int _cdecl me9xGetDrvErrMess(char *errortext )
{
	return 1;
}

_declspec(dllexport) int _cdecl me9xGetIrqCnt(int iBoardNumber, int dwTyp, int* dwCnt)
{
	return 1;
}

_declspec(dllexport) int _cdecl me9xInportByte(int iBoardNumber, int iPortOffset, int* bValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me9xOutportByte(int iBoardNumber, int iPortOffset, int bValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me9xInportWord(int iBoardNumber, int iPortOffset, int* wValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me9xOutportWord(int iBoardNumber, int iPortOffset, int wValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me94DIGetBit(int iBoardNumber, int iBitNo, int *piValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me96DIGetBit(int iBoardNumber, int iBitNo, int *piValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me94DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me96DIGetByte(int iBoardNumber, int iPortNo, int *piValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me95DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return 1;
}

_declspec(dllexport) int _cdecl  me96DOSetBit(int iBoardNumber, int iBitNo, int iBitValue)
{
    return 1;
}

_declspec(dllexport) int _cdecl me95DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
	return 1;
}

_declspec(dllexport) int _cdecl me96DOSetByte(int iBoardNumber, int iPortNo, int iValue)
{
	return 1;
}

}
