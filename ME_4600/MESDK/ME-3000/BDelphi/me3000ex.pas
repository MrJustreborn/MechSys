(*
File: ME3000EX.PAS
-------------------------------------------------------------------------------

	Meilhaus Electronic GmbH

	This module contains sample code for callback routines.



	Version 1.000:		02.03.98	First version

-------------------------------------------------------------------------------
	Author: Wagner Armin                                    (c) 1998   MK
-----------------------------------------------------------------------------*/
//
//
// The functionality of a callback routine depends on the application,
// so it is up to you to define how your callbacks should work.
//
// The functions below are intended to demonstrate the parameters
// of callback routines used by the ME3000 API *)

unit me3000ex;

interface

CONST count = 100;
Type TArray = array[1..count] of smallint;

Procedure ExternInterruptHandler;
Procedure AIMultipleHandler(VAR psBuffer :TArray;count : integer);
Procedure AISingleHandler(VAR psValue : smallint);



implementation
USES Windows;
(*---------------------------------------------------------------

   ExternInterruptHandler

---------------------------------------------------------------*)
PROCEDURE  ExternInterruptHandler;
Begin
	MessageBeep($FFFFFFFF);
End;

(*---------------------------------------------------------------

   AISingleHandler

---------------------------------------------------------------*)
PROCEDURE AISingleHandler(VAR psValue:smallint);
Begin
    psValue:=psValue+1;
End;



(*---------------------------------------------------------------

   AIMultipleHandler

---------------------------------------------------------------*)
Procedure AIMultipleHandler(VAR psBuffer : TArray;count : integer);
VAR i : Integer;
Begin
	for i:=1 to count-1 do
	Begin
		psBuffer[count-i] := psBuffer[i];
	End
End;



End.
