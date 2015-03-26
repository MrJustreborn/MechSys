#include "me9000mioDefs.h"

#ifdef __cplusplus
extern "C"
{
#endif


/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|         ME9000mio Interface (DIO + Counter Routines for ME9000 Boards)        |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         Board Independant Routines                            |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Error Routines                                  |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me9000mioErrorSetDefaultProc(
    int iDefaultProcStatus);

int _declspec(dllexport) me9000mioErrorSetUserProc(
    ME9000MIO_P_ERROR_PROC pErrorProc);

int _declspec(dllexport) me9000mioErrorGetMessage(
    int iErrorCode,
    char* pcBuffer,
    unsigned int uiBufferSize);

int _declspec(dllexport) me9000mioErrorGetLastMessage(
    char* pcBuffer,
    unsigned int uiBufferSize);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               Version Routines                                |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me9000mioGetDLLVersion(
    unsigned long* pulVersion);

int _declspec(dllexport) me9000mioGetDriverVersion(
    unsigned long* pulVersion);

int _declspec(dllexport) me9000mioGetBoardCount(
    unsigned int* puiCount);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                         Board Specific Routines                               |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                            General Routines                                   |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me9000mioGetBoardVersion(
    unsigned int uiBoardNumber,
    unsigned short* pusVersion);

int _declspec(dllexport) me9000mioGetSerialNumber(
    unsigned int uiBoardNumber,
    unsigned long* pulSerialNumber);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                               DIO Routines                                    |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me9000mioDIOOpen(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me9000mioDIOReset(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me9000mioDIOConfig(
    unsigned int uiBoardNumber,
    unsigned int uiBitNumber,
    int iDirection,
    int iInvert,
    int iInterrupt);

int _declspec(dllexport) me9000mioDIOGetBit(
    unsigned int uiBoardNumber,
    unsigned int uiBitNumber,
    int *piBitValue);

int _declspec(dllexport) me9000mioDIOSetBit(
    unsigned int uiBoardNumber,
    unsigned int uiBitNumber,
    int iBitValue);

int _declspec(dllexport) me9000mioDIOGetByte(
    unsigned int uiBoardNumber,
    unsigned char *pucByteValue);

int _declspec(dllexport) me9000mioDIOSetByte(
    unsigned int uiBoardNumber,
    unsigned char ucByteValue);

int _declspec(dllexport) me9000mioDIOOutput(
    unsigned int uiBoardNumber,
    unsigned int uiBitNumber, 
    int iOutputMode);

int _declspec(dllexport) me9000mioDIOSetCallback(
    unsigned int uiBoardNumber,
    ME9000MIO_P_DIO_PROC pDIOIrqProc, 
    void *pDIOIrqContext);

int _declspec(dllexport) me9000mioDIOGetIrqCount(
    unsigned int uiBoardNumber,
    unsigned long *pulCount);

int _declspec(dllexport) me9000mioDIOClose(
    unsigned int uiBoardNumber);

/*------------------------------------------------------------------------------+
|-------------------------------------------------------------------------------|
|                                                                               |
|                           Counter Routines                                    |
|                                                                               |
|-------------------------------------------------------------------------------|
+------------------------------------------------------------------------------*/

int _declspec(dllexport) me9000mioCntOpen(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me9000mioCntReset(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me9000mioCntConfig(
    unsigned int uiBoardNumber,
    int iRetrigger,
    int iCntEvent,
    int iClockSource,
    int iInterrupt,
    ME9000MIO_P_CNT_PROC pCntIrqProc,
    void *pCntIrqContext);

int _declspec(dllexport) me9000mioCntWrite(
    unsigned int uiBoardNumber,
    unsigned short usValue);

int _declspec(dllexport) me9000mioCntStart(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me9000mioCntRead(
    unsigned int uiBoardNumber,
    unsigned short *pusValue);

int _declspec(dllexport) me9000mioCntStop(
    unsigned int uiBoardNumber);

int _declspec(dllexport) me9000mioCntGetIrqCount(
    unsigned int uiBoardNumber,
    unsigned long *pulCount);

int _declspec(dllexport) me9000mioCntClose(
    unsigned int uiBoardNumber);

#ifdef __cplusplus
} // extern "C"
#endif
