if not exist ..\..\..\..\..\me8100	goto NothingToCopy
copy .\release\meTST.exe	.\..\..\test\ME8100.exe
copy .\release\meTST.exe	.\..\..\test\ME8100.exe
copy .\release\meTST.exe	..\..\..\..\..\me8100\_inst\meWDM\meData\ME8100.exe
copy .\release\meTST.exe	..\..\..\..\..\me8100\_inst\meVxD\meScript\Disk1\ME8100.exe
copy .\release\meTST.exe	..\..\..\..\..\me8100\_inst\meVxD\meData\ME8100.exe
copy .\release\meTST.exe	..\..\..\..\..\me8100\_inst\meSYS\meScript\Disk1\ME8100.exe
copy .\release\meTST.exe	..\..\..\..\..\me8100\_inst\meSYS\meData\ME8100.exe
:NothingToCopy