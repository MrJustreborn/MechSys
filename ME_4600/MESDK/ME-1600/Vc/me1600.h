// File Name 'me1600.h'
// Header File for me1600.dll


#ifndef ME1600_H
#define ME1600_H

#include "meDefs.h"

// Supports ME-1600, ME-160

/*
    IMPORTANT NOTE :
        only for use with Microsoft Visual C++ V4.0 or later
        for other compilers you must change the macro
        "_declspec(dllimport)" into the form your compiler needs to
        import functions from an external dll !
*/


// ME-1600 Routines

// General Routines
extern "C" _declspec(dllimport) int _cdecl me1600GetDLLVersion();
extern "C" _declspec(dllimport) int _cdecl me1600GetDriverVersion(int *piDriverVersion);
extern "C" _declspec(dllimport) int _cdecl me1600GetBoardVersion(int iBoardNumber, int *piVersion);
extern "C" _declspec(dllimport) int _cdecl me1600GetSerialNumber(int iBoardNumber, int *piSerialNumber);
extern "C" _declspec(dllimport) int _cdecl me1600GetDevInfo(int iBoardNumber, DEVICEINFOSTRUCT* pDevInfo);
extern "C" _declspec(dllimport) int _cdecl me1600WriteUserString(int iBoardNumber, char* pcUserText);
extern "C" _declspec(dllimport) int _cdecl me1600ReadUserString(int iBoardNumber, char* pcUserText, int iMaxLength);
extern "C" _declspec(dllimport) int _cdecl me1600GetDrvErrMess(char *pcErrortext, int iBufferSize);

// Analog I/O output Functions
extern "C" _declspec(dllimport) int _cdecl me1600AOSetMode(
                                                        int iBoardNumber,       // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                                                        int iChannelGroup,      // AO_GROUP_A, AO_GROUP_B, AO_GROUP_C, AO_GROUP_D
                                                        int iOutMode);          // AO_BUFFERED, AO_TRANSPARENT

extern "C" _declspec(dllimport) int _cdecl me1600AOSetRange(
                                                        int iBoardNumber,       // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                                                        int iChannelNumber,     // AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_15
                                                        int iRange);            // AO_BIPOLAR, AO_UNIPOLAR

extern "C" _declspec(dllimport) int _cdecl me1600AOSingle(
                                                        int iBoardNumber,       // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                                                        int iChannelNumber,     // AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_15
                                                        short iValue);          // 0x000..0xFFF

extern "C" _declspec(dllimport) int _cdecl me1600AOUpdate(
                                                        int iBoardNumber,       // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                                                        int iChannelGroup);     // AO_GROUP_A, AO_GROUP_B, AO_GROUP_C, AO_GROUP_D

extern "C" _declspec(dllimport) int _cdecl me1600AOUpdateAll(
                                                        int iBoardNumber);      // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31

extern "C" _declspec(dllimport) int _cdecl me1600AOResetAll(
                                                        int iBoardNumber);      // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31

extern "C" _declspec(dllimport) int _cdecl me1600AOSetCurrent(
                                                        int iBoardNumber,       // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                                                        int iChannelNumber,     // AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_07
                                                        int iCurrentMode,       // AO_CURRENT_ON, AO_CURRENT_OFF
                                                        int iRange);            // AO_RANGE_0_20, AO_RANGE_4_20


// ME160 routines for compatability with earlier versions
// Do not use them for new projects

// general routines
extern "C" _declspec(dllimport) int _cdecl _me160GetDLLVersion();
extern "C" _declspec(dllimport) int _cdecl _me160GetBoardVersion(int iBoardNumber, int *piVersion);
extern "C" _declspec(dllimport) int _cdecl _me160GetDrvErrMess(char *errortext );

// Port I/O functions
extern "C" _declspec(dllimport) int _cdecl _me160InportByte(int iBoardNumber, int iPortOffset, int* bValue);
extern "C" _declspec(dllimport) int _cdecl _me160OutportByte(int iBoardNumber, int iPortOffset, int bValue);
extern "C" _declspec(dllimport) int _cdecl _me160InportWord(int iBoardNumber, int iPortOffset, int* wValue);
extern "C" _declspec(dllimport) int _cdecl _me160OutportWord(int iBoardNumber, int iPortOffset, int wValue);

// Analog I/O output Functions
extern "C" _declspec(dllimport) int _cdecl _me160AOSetMode(
                                                        int iBoardNumber,       // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                                                        int iChannelNumbers,    // AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_07
                                                        int iOutMode);          // AO_BUFFERED, AO_TRANSPARENT

extern "C" _declspec(dllimport) int _cdecl _me160AOSingle(
                                                        int iBoardNumber,       // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                                                        int iChannelNumber,     // AO_CHAN_00, AO_CHAN_01, ..., AO_CHAN_15
                                                        int iRange,             // AO_PLUS_10, AO_PLUS_5, AO_MINUS_5, AO_MINUS_10
                                                        short iValue);          // 0x000..0xFFF

extern "C" _declspec(dllimport) int _cdecl _me160AOUpdate(
                                                        int iBoardNumber,       // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31
                                                        int iChannelNumbers);   // CH0_3, CH4_7, CH8_11, CH12_15

extern "C" _declspec(dllimport) int _cdecl _me160AOUpdateAll(
                                                        int iBoardNumber);      // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31

extern "C" _declspec(dllimport) int _cdecl _me160AOResetAll(
                                                        int iBoardNumber);      // BOARD_00, BOARD_01, BOARD_02, ..., BOARD_31


#endif // #ifndef ME1600_H
