@echo off
Path = U:\ProjEnv\BC31\bin;U:\ProjEnv\BC31\lib;
U:\ProjEnv\BC31\bin\bcc -IU:\ProjEnv\BC31\Include -LU:\ProjEnv\BC31\Lib -D_ME4000_DEBUG -ml -3 sample.c ..\MEInit.c ..\Amcclib.c
move sample.exe me4kInit.exe
del *.obj
pause
