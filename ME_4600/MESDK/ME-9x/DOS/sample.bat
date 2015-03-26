@echo off
set path=U:\ProjEnv\BC31\bin
u:
cd \ProjME\meSDK\meData\ME-9x\DOS
@echo on
U:\ProjEnv\BC31\bin\bcc -3 sample.c Amcclib.c
@echo off
del *.obj
if exist e:\ copy sample.exe e:\Meilhaus\ME-9x\DOSTest.exe
@echo on
pause
