@echo off
set path=E:\borlandc\BIN
e:
cd \projects\me1400\_appl\DOS\bc99
@echo on
e:\borlandc\bin\bcc -3 Init16.c
@echo off
del Init16.obj
@echo on
pause