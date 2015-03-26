@echo off
set path=U:\ProjEnv\BC31\bin
u:
cd \ProjME\me0630\_app\DOS\
@echo on
U:\ProjEnv\BC31\bin\bcc -3 sample.c Amcclib.c
@echo off
del *.obj
if exist e:\ copy sample.exe e:\Meilhaus\ME-630\DOSTest.exe
@echo on
pause
