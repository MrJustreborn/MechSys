@echo off
set path=U:\ProjEnv\BC31\bin
u:
cd \ProjME\me630\_app\dos\sample02\
@echo on
U:\ProjEnv\BC31\bin\bcc -3 sample.c Amcclib.c
@echo off
del *.obj
if exist i:\ copy sample.exe I:\Meilhaus\ME-630\sample.exe
if exist i:\ copy sample.exe I:\sample.exe
@echo on
pause