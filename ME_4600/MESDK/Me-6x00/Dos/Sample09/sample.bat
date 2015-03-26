Path = U:\ProjEnv\BC31\bin;U:\ProjEnv\BC31\lib;

rem U:\ProjEnv\BC31\bin\bcc -3 sample.c .\..\Amcclib.c
rem U:\ProjEnv\BC31\bin\bcc
U:\ProjEnv\BC31\bin\bcc -IU:\ProjEnv\BC31\Include -LU:\ProjEnv\BC31\Lib -ml -3 sample.c ..\Amcclib.c 

if exist a: copy SAMPLE.EXE a:

del *.obj
