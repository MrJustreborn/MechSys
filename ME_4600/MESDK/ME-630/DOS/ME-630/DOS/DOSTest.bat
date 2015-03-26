@echo off
set path=U:\ProjEnv\BC31\bin
c:
cd \ProjME\me630\_app\DOS
@echo on
U:\ProjEnv\BC31\bin\bcc -3 DOSTest.c
@echo off
del DOSTest.obj
if exist i:\ copy DOSTest.exe I:\Meilhaus\ME-630\DOSTest.exe
@echo on
pause