// File Name 'me9x.h'
// Header File for me9x_32.dll in the case of using a lib file
// Supports ME-94, ME-95, ME-96

#ifndef ME9X_H
#define ME9X_H

/* IMPORTANT NOTE :
		only for use with Microsoft Visual C++ V4.0 or later
		for other compilers you must change the macro
		"_declspec(dllimport)" into the form your compiler needs to
		import functions from an external dll !
*/

// general routines
extern "C" int _declspec(dllimport) _cdecl _me9xGetDLLVersion();
extern "C" int _declspec(dllimport) _cdecl _me9xGetBoardVersion(int ,int*);
extern "C" int _declspec(dllimport) _cdecl _me94EnableInt(int iBoadNumber, PSERVICE_PROC IrqFunc);
extern "C" int _declspec(dllimport) _cdecl _me96EnableInt(int iBoadNumber, PSERVICE_PROC IrqFunc);
extern "C" int _declspec(dllimport) _cdecl _me94DisableInt(int iBoadNumber);
extern "C" int _declspec(dllimport) _cdecl _me96DisableInt(int iBoadNumber);

// low level IO routines (internal use only, no support!!)
extern "C" int _declspec(dllimport) _cdecl _me9xInportByte(int iBoardNumber, int iPortOffset, int* pbValue);
extern "C" int _declspec(dllimport) _cdecl _me9xOutportByte(int iBoardNumber, int iPortOffset, int bValue);

// A.B.: New for version 3.3
extern "C" int _declspec(dllimport) _cdecl _me9xGetIrqCnt(int iBoardNumber, int dwTyp, int* dwCnt);

// error handling
//extern "C" int _declspec(dllimport) _cdecl _me9xGetDrvErrMess(char *pcErrortext);

// Digital I/O Input-Functions
extern "C" int _declspec(dllimport) _cdecl _me94DIGetBit(int iBoadNumber, int iBitNo, int *piBitValue);
extern "C" int _declspec(dllimport) _cdecl _me96DIGetBit(int iBoadNumber, int iBitNo, int *piBitValue);
extern "C" int _declspec(dllimport) _cdecl _me94DIGetByte(int iBoadNumber, int iPortNo, int *piValue);
extern "C" int _declspec(dllimport) _cdecl _me96DIGetByte(int iBoadNumber, int iPortNo, int *piValue);

// Digital I/O Output-Functions
extern "C" int _declspec(dllimport) _cdecl _me95DOSetBit(int iBoadNumber, int iBitNo, int iBitValue);
extern "C" int _declspec(dllimport) _cdecl _me96DOSetBit(int iBoadNumber, int iBitNo, int iBitValue);
extern "C" int _declspec(dllimport) _cdecl _me95DOSetByte(int iBoadNumber, int iPortNo, int iValue);
extern "C" int _declspec(dllimport) _cdecl _me96DOSetByte(int iBoadNumber, int iPortNo, int iValue);


#endif

