# Microsoft Developer Studio Project File - Name="_me4000" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=_me4000 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "_me4000.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "_me4000.mak" CFG="_me4000 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "_me4000 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "_me4000 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "_me4000 - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/me4000.exe"
# SUBTRACT LINK32 /debug

!ELSEIF  "$(CFG)" == "_me4000 - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x407 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/me4000.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "_me4000 - Win32 Release"
# Name "_me4000 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AnalogInputPP.cpp
# End Source File
# Begin Source File

SOURCE=.\AnalogOutputPP.cpp
# End Source File
# Begin Source File

SOURCE=..\meScope\ColourBox.cpp
# End Source File
# Begin Source File

SOURCE=.\CounterPWMPP.cpp
# End Source File
# Begin Source File

SOURCE=.\DigitalIOPP.cpp
# End Source File
# Begin Source File

SOURCE=.\DIOBitPatternPP.cpp
# End Source File
# Begin Source File

SOURCE=.\ExternalInterruptPP.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoPP.cpp
# End Source File
# Begin Source File

SOURCE=.\me4000.cpp
# End Source File
# Begin Source File

SOURCE=.\ME4000PropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiSigAnalogInputPP.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiSigAnalogOutputPP.cpp
# End Source File
# Begin Source File

SOURCE=.\MultiSigPP.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\WinSweep.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AnalogInputPP.h
# End Source File
# Begin Source File

SOURCE=.\AnalogOutputPP.h
# End Source File
# Begin Source File

SOURCE=..\meScope\ColourBox.h
# End Source File
# Begin Source File

SOURCE=.\CounterPWMPP.h
# End Source File
# Begin Source File

SOURCE=.\DigitalIOPP.h
# End Source File
# Begin Source File

SOURCE=.\DIOBitPatternPP.h
# End Source File
# Begin Source File

SOURCE=.\ExternalInterruptPP.h
# End Source File
# Begin Source File

SOURCE=.\InfoPP.h
# End Source File
# Begin Source File

SOURCE=.\me4000.h
# End Source File
# Begin Source File

SOURCE=..\me4000defs.h
# End Source File
# Begin Source File

SOURCE=..\me4000dll.h
# End Source File
# Begin Source File

SOURCE=.\ME4000PropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\MultiSigAnalogInputPP.h
# End Source File
# Begin Source File

SOURCE=.\MultiSigAnalogOutputPP.h
# End Source File
# Begin Source File

SOURCE=.\MultiSigPP.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\WinSweep.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\_me4000.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap.bmp
# End Source File
# Begin Source File

SOURCE=.\me4000.rc
# End Source File
# Begin Source File

SOURCE=".\res\ME_LOGO 89x89.BMP"
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\me4000.lib
# End Source File
# End Target
# End Project
