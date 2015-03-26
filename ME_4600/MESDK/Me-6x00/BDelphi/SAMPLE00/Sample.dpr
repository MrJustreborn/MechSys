{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    General Dev Info                                                                        */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020228  ew    print board parameter                                             */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  me6x00 in '..\me6x00.pas',
  medefs in '..\medefs.pas',
  SysUtils;

var
  iDllVersion       : Integer;
  sDllVersion       : string;
  iBoardnumber      : Integer;
  iVersion          : Integer;
  iErrorCode        : Integer;
  iSerial           : Integer;
  ssVersion         : string;
  sErrortext        : errorstring;
  sSerial           : string;
  DevInfo           : DEVICEINFOSTRUCT;
  sVendorID         : string;
  sDeviceID         : string;
  sBusNumber        : string;
  sSystemSlotNumber : string;
  sPortBase         : string;
  sPortCount        : string;
  sIntChannel       : string;
  sPortBasePLX      : string;
  sPortCountPLX     : string;
  sSerialNumber     : string;
  sHWRevision       : string;
  sIrqCnt           : string;
  sVersion          : string;

Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    me6x00GetDrvErrMess(sErrorText,255);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;


begin

  {Function me6x00GetDllVersion}
  Writeln('Sample 00 - Board Parameter');
  Writeln('---------------------------',#10);
  {Get DLL Version}
  iDllVersion := me6x00GetDllVersion;
  sDllVersion := IntToHex(iDllVersion, 10);
  Writeln('DLL version   : ', sDllVersion);

  {Set the board number}
  iBoardnumber := 0;

  {Get Board Typ}
  iErrorCode := me6x00GetBoardVersion (iBoardnumber, iVersion);
  {Basically after every function call an error check by the function
   me6x00ErrorMessage should be done}
  ChkErrCode ;
  ssVersion := IntToHex (iVersion, 10);
  Writeln('BoardVersion  : ', ssVersion);


  {Get Driver SerialNumber}
  iErrorCode :=me6x00GetSerialNumber (iBoardnumber, iSerial);
  ChkErrCode ;
  sSerial := IntToHex(iSerial, 8);
  Writeln('SeriaNumber   : ', sSerial,#10,#10);

  {Get Dev Info}
  iErrorCode :=me6x00GetDevInfo(iBoardNumber,DevInfo);
  ChkErrCode ;

        sVendorID         := IntToHex(DevInfo.dwVendorID, 4);
        sDeviceID         := IntToHex(DevInfo.dwDeviceID, 4);
        sBusNumber        := IntToHex(DevInfo.dwBusNumber, 4);
        sSystemSlotNumber := IntToHex(DevInfo.dwSystemSlotNumber, 4);
        sPortBase         := IntToHex(DevInfo.dwPortBase, 4);
        sPortCount        := IntToHex(DevInfo.dwPortCount, 4);
        sIntChannel       := IntToHex(DevInfo.dwIntChannel, 4);
        sPortBasePLX      := IntToHex(DevInfo.dwPortBasePLX, 4);
        sPortCountPLX     := IntToHex(DevInfo.dwPortCountPLX, 4);
        sSerialNumber     := IntToHex(DevInfo.dwSerialNumber, 8);
        sHWRevision       := IntToHex(DevInfo.dwHWRevision, 4);
        sIrqCnt           := IntToHex(DevInfo.dwIrqCnt, 4);
        sVersion          := IntToHex(DevInfo.dwVersion, 4);

        writeln('Vendor ID:          ', sVendorID);
        writeln('Device ID:          ', sDeviceID);
        writeln('Bus Number:         ', sBusNumber);
        writeln('System Slot Number: ', sSystemSlotNumber);
        writeln('Port Base:          ', sPortBase);
        writeln('Port Count:         ', sPortCount);
        writeln('Interrupt Channel:  ', sIntChannel);
        writeln('PLX Port Base:      ', sPortBasePLX);
        writeln('PLX Port Count:     ', sPortCountPLX);
        writeln('Serial Number:      ', sSerialNumber);
        writeln('Hardware Revision:  ', sHWRevision);
        writeln('IRQ Count:          ', sIrqCnt);
        writeln('Version:            ', sVersion);

   Writeln('Press any key to exit!');

  Readln;
end.

