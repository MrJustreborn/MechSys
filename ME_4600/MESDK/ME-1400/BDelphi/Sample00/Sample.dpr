{*----------------------------------------------------------------------------------------------------------*/
/*  Source File:    sample.pas (Sample.dpr)                                                                 */
/*  Compiler:       Delphi 6.0                                                                              */
/*  Copyright:      2002 Meilhaus Electronic GmbH                                                           */
/*  Author:         ew (Erwin Wisura)                                                                       */
/*                                                                                                          */
/*  Description:    General Example                                                                         */
/*                                                                                                          */
/*  File History:   Version Date    Editor  Action                                                          */
/*------------------------------------------------------------                                              */
/*                  1.00    020327  ew     General Board Info                                               */
/*                                                                                                          */
/*----------------------------------------------------------------------------------------------------------*}

program
  Sample;

uses
  medefs  in '..\medefs.pas',
  me1400  in '..\me1400.pas',
  SysUtils;

var
  iDllVersion       : Integer;
  sDllVersion       : string;
  iBoardnumber      : Integer;
  iBoardVersion     : Integer;
  sBoardVersion     : string;
  iErrorCode        : Integer;
  sErrorText        : errorstring;
  DevInfo           : DEVICEINFOSTRUCT;
  sBoardNumber      : string;     {Board number of Board}
  sVendorID         : string;     {PCI vendor ID}
  sDeviceID         : string;     {PCI device ID}
  sSystemSlotNumber : string;     {Slot number in PCI bus}
  sPortBase         : string;     {base port address}
  sPortCount        : string;     {Count of I/O addresses used.}
  sIntChannel       : string;     {first Interrupt Channel}
  sPortBasePLX      : string;	  {base port address}
  sPortCountPLX     : string;	  {Count of I/O addresses used.}
  sSerialNumber     : string;     {Serial number of the board}
  sBusNumber        : string;     {Bus number of the PCI bus (in most cases 0)}
  sHWRevision       : string;     {hardware revision of board}
  sIrqCnt           : string;     {number of interrupts }
  sVersion          : string;     {which board of the board family}





Procedure ChkErrCode ;
Begin
  if iErrorCode<>1 then
  begin
    me1400GetDrvErrMess(sErrorText);
    Write('Error: ', sErrorText);
    Readln;
    exit;
  end;
End;


begin
  {Function me1400GetDllVersion}
  Writeln('Sample 00 - Board Parameter');
  Writeln('---------------------------',#10);  // Get DLL Version
  iDllVersion := me1400GetDLLVersion;
  sDllVersion := IntToHex(iDllVersion, 10);
  Writeln('DLL version: ', sDllVersion);

  // Set the board number
  iBoardnumber := 0;
  // determine board version
  iErrorCode := me1400GetBoardVersion (iBoardnumber, iBoardVersion);
  ChkErrCode;   // Basically after every function call an error check by the function
  sBoardVersion := IntToHex(iBoardVersion, 10);
  Writeln('Board typ: ', sBoardVersion,#10,#10);

   iErrorCode :=me1400GetDevInfo(iBoardNumber, DevInfo);
   ChkErrCode;
   
    sBoardNumber      := IntToHex(DevInfo.dwBoardNumber,4);
    sVendorID         := IntToHex(DevInfo.dwVendorID,4);
    sDeviceID         := IntToHex(DevInfo.dwDeviceID,4);
    sSystemSlotNumber := IntToHex(DevInfo.dwSystemSlotNumber,4);
    sPortBase         := IntToHex(DevInfo.dwPortBase,4);
    sPortCount        := IntToHex(DevInfo.dwPortCount,4);
    sIntChannel       := IntToHex(DevInfo.dwIntChannel,4);
    sPortBasePLX      := IntToHex(DevInfo.dwPortBasePLX,4);
    sPortCountPLX     := IntToHex(DevInfo.dwPortCountPLX,4);
    sSerialNumber     := IntToHex(DevInfo.dwSerialNumber,4);
    sBusNumber        := IntToHex(DevInfo.dwBusNumber,4);
    sHWRevision       := IntToHex(DevInfo.dwHWRevision,4);
    sIrqCnt           := IntToHex(DevInfo.dwIrqCnt,4);
    sVersion          := IntToHex(DevInfo.dwVersion,4);

    Writeln('BoardNumber                   :   ',sBoardnumber);
    Writeln('Vendor ID                     :   ',sVendorID);
    Writeln('Device ID                     :   ',sDeviceID);
    Writeln('SystemSlotNumber              :   ',sSystemSlotNumber);
    Writeln('Base Port Address             :   ',sPortBase);
    Writeln('Count of I/O addresses used   :   ',sPortCount);
    Writeln('first Interrupt channel       :   ',sIntChannel);
    Writeln('PLX Base Port Address         :   ',sPortBasePLX);
    Writeln('PLX Count of I/O adresses used:   ',sPortCountPLX);
    Writeln('Serial number of the board    :   ',sSerialNumber);
    Writeln('Bus number of the PCI bus     :   ',sBusNumber);
    Writeln('Hardware revision of the board:   ',sHWRevision);
    Writeln('number of interrupts          :   ',sIrqCnt);
    Writeln('Board Version                 :   ',sVersion);



  Writeln('Press any key to end!');
  Readln;

end.
