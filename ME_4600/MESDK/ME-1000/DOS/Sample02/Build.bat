@echo off
set path=g:\bc\BIN
e:
cd \ProjME\me1000\_appl\DOS\bc01
@echo on
g:\bc\bin\bcc -3 DOSTest.c
@echo off
del DOSTest.obj
@echo on
