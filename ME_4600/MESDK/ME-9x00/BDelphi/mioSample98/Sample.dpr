program Sample98;

{$APPTYPE CONSOLE}

uses
  me9000miodefs in '..\me9000miodefs.pas',
  me9000miodll in '..\me9000miodll.pas',
  SysUtils,
  IdGlobal,
  IdTrivialFTPBase;

var

  bTerminate: Boolean;
  sText: String;
  chCommand: Char;
  iError: Integer;
  lwVersion: LongWord;
  cBoardCount: Cardinal;
  wVersion: Word;
  lwSerialNumber: LongWord;
  cBitNumber: Cardinal;
  iDirection: Integer;
  iInvert: Integer;
  iInterrupt: Integer;
  iBitValue: Integer;
  bByteValue: Byte;
  cByteValue: Cardinal;
  iOutput: Integer;
  lwIRQCount: LongWord;
  iRetrigger: Integer;
  iCntEvent: Integer;
  iClockSource: Integer;
  cCntValue: Cardinal;
  wCntValue: Word;

Procedure
        DIO_IRQ_Proc(pDIOIrqContext: Pointer); stdcall;

begin

  writeln;
  writeln;
  writeln('*** DIOIrqProc ***');
  writeln;

end;

Procedure
        CNT_IRQ_Proc(pDIOIrqContext: Pointer); stdcall;

begin

  writeln;
  writeln;
  writeln('*** CntIrqProc ***');
  writeln;

end;

begin

  { TODO -oUser -cConsole Main : Hier Code einfügen }

  writeln('This program presents you with a menu enabling you to');
  writeln('call any of the me9x00mio functions');
  writeln;
  writeln('Having chosen a particular function you will be required');
  writeln('to enter appropriate values for each of its parameters');
  writeln;
  writeln('Once the desired function has been executed you will be');
  writeln('presented with the main menu once again.');
  writeln;
  writeln('This will continue until you press "z" to exit the program');
  writeln;
  writeln('All functions operate on the FIRST ME9000 board found on the');
  writeln('system. For this reason the first parameter to many functions,');
  writeln('the board number, is missing here.');
  writeln;
  write('Press RETURN to continue...');
  readln;

  writeln;
  writeln;

  // Enable default error procedure

  me9000mioErrorSetDefaultProc(ME9000MIO_ERROR_DEFAULT_PROC_ENABLE);

  bTerminate := False;

  repeat

    writeln('A) GetDLLVersion        B) GetDriverVersion ');
    writeln('C) GetBoardCount                            ');
    writeln;

    writeln('D) GetBoardVersion      E) GetSerialNumber  ');
    writeln;

    writeln('F) DIOOpen                                  ');
    writeln('G) DIOReset             H) DIOConfig        ');
    writeln('I) DIOGetBit            J) DIOSetBit        ');
    writeln('K) DIOGetByte           L) DIOSetByte       ');
    writeln('M) DIOOutput                                ');
    writeln('N) DIOSetCallback       O) DIOGetIrqCount   ');
    writeln('P) DIOClose                                 ');
    writeln;

    writeln('Q) CntOpen                                  ');
    writeln('R) CntReset             S) CntConfig        ');
    writeln('T) CntWrite             U) CntStart         ');
    writeln('V) CntRead              W) CntStop          ');
    writeln('X) CntGetIrqCount                           ');
    writeln('Y) CntClose                                 ');
    writeln;

    writeln('Z) End Program	                         ');

    write('Choose a command: ');

    readln(sText);

    writeln;
    writeln;

    chCommand := ( UpperCase(sText) )[1];

    case chCommand of

      'A':   { me9000mioGetDLLVersion(var pulVersion: LongWord): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('GetDllVersion');

        iError := me9000mioGetDLLVersion(lwVersion);

        sText := IntToHex(lwVersion, 8);

        writeln('dll version is ', sText);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'B':   { me9000mioGetDriverVersion(var pulVersion: LongWord): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('GetDriverVersion');

        iError := me9000mioGetDriverVersion(lwVersion);

        sText := IntToHex(lwVersion, 8);

        writeln('Driver version is ', sText);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'C':   { me9000mioGetBoardCount(var puiCount: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('GetBoardCount');

        iError := me9000mioGetBoardCount(cBoardCount);

        writeln('Board count: ', cBoardCount);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'D':   { me9000mioGetBoardVersion(uiBoardNumber: Cardinal;
                                        var pusVersion: Word): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('GetBoardVersion');

        iError := me9000mioGetBoardVersion(0, wVersion);

        sText := IntToHex(wVersion, 4);

        writeln('Board version is ', sText);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'E':   { me9000mioGetSerialNumber(uiBoardNumber: Cardinal;
                                var pulSerialNumber: LongWord): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('GetSerialNumber');

        iError := me9000mioGetSerialNumber(0, lwSerialNumber);

        sText := IntToHex(lwSerialNumber, 8);

        writeln('Serial  number is ', sText);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'F':   { me9000mioDIOOpen(uiBoardNumber: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOOpen');

        iError := me9000mioDIOOpen(0);

        writeln('DIO is opened.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'G':   { me9000mioDIOReset(uiBoardNumber: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOReset');

        iError := me9000mioDIOReset(0);

        writeln('DIO is reset.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'H':   { me9000mioDIOConfig(uiBoardNumber: Cardinal; uiBitNumber: Cardinal;
                                        iDirection: Integer; iInvert: Integer;
                                                iInterrupt: Integer): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOConfig');

        repeat

          write('Bit number 0 - 7): ');

          readln(sText);

          writeln;

          if ( '0' <= sText[1] ) AND ( sText[1] <= '7' ) then

          begin

            cBitNumber := Cardinal (sText[1])  - Cardinal ('0');

            break;

          end

        until 1 = 0;

        repeat

          writeln('Direction');
          writeln;

	  writeln('O) ME9000MIO_DIO_OUTPUT');
	  writeln('I) ME9000MIO_DIO_OUTPUT');
	  write('Your choice: ');

          readln(sText);

          writeln;

          if ( sText[1] = 'o' ) OR ( sText[1] = 'O' ) then

          begin

            iDirection := ME9000MIO_DIO_OUTPUT;
            break;

          end

          else if ( sText[1] = 'i' ) OR ( sText[1] = 'I' ) then

          begin

            iDirection := ME9000MIO_DIO_INPUT;
            break;

          end

        until 1 = 0;

        repeat

          writeln('Invert');
          writeln;

	  writeln('D) ME9000MIO_DIO_INV_DISABLE');
	  writeln('E) ME9000MIO_DIO_INV_ENABLE');
	  write('Your choice: ');

          readln(sText);

          writeln;

          if ( sText[1] = 'd' ) OR ( sText[1] = 'D' ) then

          begin

            iInvert := ME9000MIO_DIO_INV_DISABLE;
            break;

          end

          else if ( sText[1] = 'e' ) OR ( sText[1] = 'E' ) then

          begin

            iInvert := ME9000MIO_DIO_INV_ENABLE;
            break;

          end

        until 1 = 0;

        repeat

          writeln('Interrupt');
          writeln;

	  writeln('D) ME9000MIO_DIO_INT_DISABLE');
	  writeln('E) ME9000MIO_DIO_INT_ENABLE');
	  write('Your choice: ');

          readln(sText);

          writeln;

          if ( sText[1] = 'd' ) OR ( sText[1] = 'D' ) then

          begin

            iInterrupt := ME9000MIO_DIO_INT_DISABLE;
            break;

          end

          else if ( sText[1] = 'e' ) OR ( sText[1] = 'E' ) then

          begin

            iInterrupt := ME9000MIO_DIO_INT_ENABLE;
            break;

          end

        until 1 = 0;

        iError := me9000mioDIOConfig(0, cBitNumber, iDirection,
                                                        iInvert, iInterrupt);

        writeln('DIO is configured.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'I':   { me9000mioDIOGetBit(uiBoardNumber: Cardinal;
                uiBitNumber: Cardinal; var piBitValue: Integer): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('IOGetBit');

        repeat

          write('Bit number 0 - 7): ');

          readln(sText);

          writeln;

          if ( '0' <= sText[1] ) AND ( sText[1] <= '7' ) then

          begin

            cBitNumber := Cardinal (sText[1])  - Cardinal ('0');

            break;

          end

        until 1 = 0;

        iError := me9000mioDIOGetBit(0, cBitNumber, iBitValue);

        writeln('Bit ', cBitNumber, 'is ', iBitValue);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'J':   { me9000mioDIOSetBit(uiBoardNumber: Cardinal;
                        uiBitNumber: Cardinal; iBitValue: Integer): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOGetBit');

        repeat

          write('Bit number 0 - 7): ');

          readln(sText);

          writeln;

          if ( '0' <= sText[1] ) AND ( sText[1] <= '7' ) then

          begin

            cBitNumber := Cardinal (sText[1])  - Cardinal ('0');

            break;

          end

        until 1 = 0;

        repeat

          write('Bit value 0 or 1): ');

          readln(sText);

          writeln;

          if ( '0' <= sText[1] ) AND ( sText[1] <= '1' ) then

          begin

            iBitValue := Cardinal (sText[1])  - Cardinal ('0');

            break;

          end

        until 1 = 0;

        iError := me9000mioDIOSetBit(0, cBitNumber, iBitValue);

        writeln('Bit set to ', iBitValue);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'K':   { me9000mioDIOGetByte(uiBoardNumber: Cardinal;
                                        var pucByteValue: Byte): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOGetByte');

        iError := me9000mioDIOGetByte(0, bByteValue);

        sText := IntToHex(bByteValue, 2);

        writeln('Byte value is $', sText);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'L':   { me9000mioDIOSetByte(uiBoardNumber: Cardinal;
                                                ucByteValue: Byte): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOSetByte');

        repeat

          write('Byte Value (2 Digit Hex Integer) : $');

          readln(sText);

          writeln;

          Insert('$', sText, 0);

          cByteValue := StrToCard(sText);

          if ( cByteValue <= 255 ) then

          begin

            bByteValue := cByteValue;

            break;

          end

        until 1 = 0;

        iError := me9000mioDIOSetByte(0, bByteValue);

        sText := IntToHex(bByteValue, 2);

        writeln('Byte set to $', sText);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'M':   { me9000mioDIOOutput(uiBoardNumber: Cardinal;
                        uiBitNumber: Cardinal; iOutputMode: Integer): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOOutput');

        repeat

          write('Bit number 0 - 7): ');

          readln(sText);

          writeln;

          if ( '0' <= sText[1] ) AND ( sText[1] <= '7' ) then

          begin

            cBitNumber := Cardinal (sText[1])  - Cardinal ('0');

            break;

          end

        until 1 = 0;

        repeat

          writeln('Output');
          writeln;

	  writeln('D) ME9000MIO_DIO_OUTPUT_DISABLE');
	  writeln('E) ME9000MIO_DIO_OUTPUT_ENABLE');
	  write('Your choice: ');

          readln(sText);

          writeln;

          if ( sText[1] = 'd' ) OR ( sText[1] = 'D' ) then

          begin

            iOutput := ME9000MIO_DIO_OUTPUT_DISABLE;
            break;

          end

          else if ( sText[1] = 'e' ) OR ( sText[1] = 'E' ) then

          begin

            iOutput := ME9000MIO_DIO_OUTPUT_ENABLE;
            break;

          end

        until 1 = 0;

        iError := me9000mioDIOOutput(0, cBitNumber, iOutput);

        writeln('DIOOutput called.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'N':   { me9000mioDIOSetCallback(uiBoardNumber: Cardinal;
                                pDIOIrqProc: TME9000MIO_P_DIO_PROC;
                                        pDIOIrqContext: Pointer): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOSetCallback');
        writeln;

	writeln('The arguments for this function will be supplied');
        writeln;
	writeln('pDIOIrqProc - Prints "*** DIOIrqProc ***" on the screen');
	writeln('pDIOIrqContext - is null');
	write('Press Return to call DIOSetCallback...');

        readln;

        writeln;
        writeln;

        iError := me9000mioDIOSetCallback(0, DIO_IRQ_Proc, nil);

        writeln('DIOSetCallback called.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'O':   { me9000mioDIOGetIrqCount(uiBoardNumber: Cardinal;
                                        var pulCount: LongWord): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOGetIrqCount');

        iError := me9000mioDIOGetIrqCount(0, lwIRQCount);

        writeln('DIO IRQ Count is ', lwIRQCount);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'P':   { me9000mioDIOClose(uiBoardNumber: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('DIOClose');

        iError := me9000mioDIOClose(0);

        writeln('DIO is closed.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'Q':   { me9000mioCntOpen(uiBoardNumber: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntOpen');

        iError := me9000mioCntOpen(0);

        writeln('Cnt is opened.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'R':   { me9000mioCntReset(uiBoardNumber: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntReset');

        iError := me9000mioCntReset(0);

        writeln('Cnt is reset.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'S':   { me9000mioCntConfig(uiBoardNumber: Cardinal;
                iRetrigger: Integer; iCntEvent: Integer; iClockSource: Integer;
                        iInterrupt: Integer; pCntIrqProc: TME9000MIO_P_CNT_PROC;
                                        pCntIrqContext: Pointer): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntConfig');

        repeat

          writeln('Retrigger');
          writeln;

	  writeln('D) ME9000MIO_CNT_RETRIGGER_DISABLE');
	  writeln('E) ME9000MIO_CNT_RETRIGGER_ENABLE');
	  write('Your choice: ');

          readln(sText);

          writeln;

          if ( sText[1] = 'd' ) OR ( sText[1] = 'D' ) then

          begin

            iRetrigger := ME9000MIO_CNT_RETRIGGER_DISABLE;
            break;

          end

          else if ( sText[1] = 'e' ) OR ( sText[1] = 'E' ) then

          begin

            iRetrigger := ME9000MIO_CNT_RETRIGGER_ENABLE;
            break;

          end

        until 1 = 0;

        repeat

          writeln('Count event');
          writeln;

	  writeln('D) ME9000MIO_CNT_EVENT_DISABLE');
	  writeln('E) ME9000MIO_CNT_EVENT_ENABLE');
	  write('Your choice: ');

          readln(sText);

          writeln;

          if ( sText[1] = 'd' ) OR ( sText[1] = 'D' ) then

          begin

            iCntEvent := ME9000MIO_CNT_EVENT_DISABLE;
            break;

          end

          else if ( sText[1] = 'e' ) OR ( sText[1] = 'E' ) then

          begin

            iCntEvent := ME9000MIO_CNT_EVENT_ENABLE;
            break;

          end

        until 1 = 0;

        repeat

          writeln('Clock source');
          writeln;

	  writeln('I) ME9000MIO_CNT_CLOCK_INTERNAL');
	  writeln('E) ME9000MIO_CNT_CLOCK_EXTERNAL');
	  write('Your choice: ');

          readln(sText);

          writeln;

          if ( sText[1] = 'i' ) OR ( sText[1] = 'I' ) then

          begin

            iClockSource := ME9000MIO_CNT_CLOCK_INTERNAL;
            break;

          end

          else if ( sText[1] = 'e' ) OR ( sText[1] = 'E' ) then

          begin

            iClockSource := ME9000MIO_CNT_CLOCK_EXTERNAL;
            break;

          end

        until 1 = 0;

        repeat

          writeln('Interrupt');
          writeln;

	  writeln('D) ME9000MIO_CNT_INT_DISABLE');
	  writeln('E) ME9000MIO_CNT_INT_ENABLE');
	  write('Your choice: ');

          readln(sText);

          writeln;

          if ( sText[1] = 'd' ) OR ( sText[1] = 'D' ) then

          begin

            iInterrupt := ME9000MIO_CNT_INT_DISABLE;
            break;

          end

          else if ( sText[1] = 'e' ) OR ( sText[1] = 'E' ) then

          begin

            iInterrupt := ME9000MIO_CNT_INT_ENABLE;
            break;

          end

        until 1 = 0;

        writeln;

	writeln('The remaining arguments for this function will be supplied');
        writeln;
	writeln('pCntIrqProc - Prints "*** CntIrqProc ***" on the screen');
	writeln('pCntIrqContext - is null');
	write('Press Return to call CntConfig...');

        readln;

        writeln;
        writeln;

        iError := me9000mioCntConfig(0, iRetrigger, iCntEvent, iClockSource,
                                                iInterrupt, CNT_IRQ_Proc, nil);

        writeln('Cnt is configured.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'T':   { me9000mioCntWrite(uiBoardNumber: Cardinal;
                                                usValue: Word): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntWrite');

        repeat

          write('Value to write (0 .. 65635) : ');

          readln(sText);

          writeln;

          cCntValue := StrToCard(sText);

          if (cCntValue <= 65535) then

          Begin

            wCntValue := cCntValue;

            break;
            
          End;

        until 1 = 0;

        iError := me9000mioCntWrite(0, wCntValue);

        writeln(wCntValue, ' written to counter');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'U':   { me9000mioCntStart(uiBoardNumber: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntStart');

        iError := me9000mioCntStart(0);

        writeln('Cnt started.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'V':   { me9000mioCntRead(uiBoardNumber: Cardinal;
                                                var usValue: Word): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntRead');

        iError := me9000mioCntRead(0, wCntValue);

        writeln('Count value is ', wCntValue);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'W':   { me9000mioCntStop(uiBoardNumber: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntStop');

        iError := me9000mioCntStop(0);

        writeln('Cnt stopped.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'X':   { me9000mioCntGetIrqCount(uiBoardNumber: Cardinal;
                                        var pulCount: LongWord): Integer; }
      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntGetIrqCount');

        iError := me9000mioCntGetIrqCount(0, lwIRQCount);

        writeln('Cnt IRQ Count is ', lwIRQCount);

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'Y':   { me9000mioCntClose(uiBoardNumber: Cardinal): Integer; }

      Begin

        writeln('-----------------------------------------------------------');
        writeln('CntClose');

        iError := me9000mioCntClose(0);

        writeln('Cnt is closed.');

        writeln('-----------------------------------------------------------');
        writeln;

      End;

      'Z':

      Begin

        bTerminate := True;

      End;

    End;

    if bTerminate then break;

    writeln;
    writeln;
    writeln('Press RETURN to continue');
    writeln;

    readln;

  until 1 = 0;

  writeln('Press RETURN to terminate the programm');

  readln;

end.
