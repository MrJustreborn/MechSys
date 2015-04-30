Path = U:\ProjEnv\BC31\bin;U:\ProjEnv\BC31\lib;

U:\ProjEnv\BC31\bin\bcc -IU:\ProjEnv\BC31\Include -LU:\ProjEnv\BC31\Lib -ml -3 sample.c ..\Amcclib.c

del *.obj

pause
