@echo off
set path=g:\bc\BIN
e:
cd \ProjME\me1000\_app\DOS\ASM
@echo on
g:\bc\bin\bcc -3 -B DOSTest.c
g:\bc\bin\bcc -3 -S DOSTest.c
