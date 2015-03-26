# Microsoft Developer Studio Generated NMAKE File, Based on me2600dll.dsp
!IF "$(CFG)" == ""
CFG=me2600dll - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. me2600dll - Win32 Debug wird als\
 Standard verwendet.
!ENDIF 

!IF "$(CFG)" != "me2600dll - Win32 Release" && "$(CFG)" !=\
 "me2600dll - Win32 Debug"
!MESSAGE Ungültige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "me2600dll.mak" CFG="me2600dll - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "me2600dll - Win32 Release" (basierend auf\
  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "me2600dll - Win32 Debug" (basierend auf\
  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungültige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "me2600dll - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\me2600dll.dll"

!ELSE 

ALL : "$(OUTDIR)\me2600dll.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\me2600_dll.res"
	-@erase "$(INTDIR)\me2600_dll_c.obj"
	-@erase "$(INTDIR)\me2600_dll_main.obj"
	-@erase "$(INTDIR)\me2600_dll_vb.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\me2600dll.dll"
	-@erase "$(OUTDIR)\me2600dll.exp"
	-@erase "$(OUTDIR)\me2600dll.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\me2600dll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\me2600_dll.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\me2600dll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\me2600dll.pdb" /machine:I386 /out:"$(OUTDIR)\me2600dll.dll"\
 /implib:"$(OUTDIR)\me2600dll.lib" 
LINK32_OBJS= \
	"$(INTDIR)\me2600_dll.res" \
	"$(INTDIR)\me2600_dll_c.obj" \
	"$(INTDIR)\me2600_dll_main.obj" \
	"$(INTDIR)\me2600_dll_vb.obj"

"$(OUTDIR)\me2600dll.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "me2600dll - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\me2600.dll"

!ELSE 

ALL : "$(OUTDIR)\me2600.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\me2600_dll.res"
	-@erase "$(INTDIR)\me2600_dll_c.obj"
	-@erase "$(INTDIR)\me2600_dll_main.obj"
	-@erase "$(INTDIR)\me2600_dll_vb.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\me2600.dll"
	-@erase "$(OUTDIR)\me2600.exp"
	-@erase "$(OUTDIR)\me2600.ilk"
	-@erase "$(OUTDIR)\me2600.lib"
	-@erase "$(OUTDIR)\me2600.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\me2600dll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x407 /fo"$(INTDIR)\me2600_dll.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\me2600dll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\me2600.pdb" /debug /machine:I386 /out:"$(OUTDIR)\me2600.dll"\
 /implib:"$(OUTDIR)\me2600.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\me2600_dll.res" \
	"$(INTDIR)\me2600_dll_c.obj" \
	"$(INTDIR)\me2600_dll_main.obj" \
	"$(INTDIR)\me2600_dll_vb.obj"

"$(OUTDIR)\me2600.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
PostBuild_Desc=Copy ME2600.DLL
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\me2600.dll"
   Copy.bat
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(CFG)" == "me2600dll - Win32 Release" || "$(CFG)" ==\
 "me2600dll - Win32 Debug"
SOURCE=.\me2600_dll.rc
DEP_RSC_ME260=\
	"..\me2600_error.h"\
	

"$(INTDIR)\me2600_dll.res" : $(SOURCE) $(DEP_RSC_ME260) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\me2600_dll_c.cpp

!IF  "$(CFG)" == "me2600dll - Win32 Release"

DEP_CPP_ME2600=\
	"..\_sys\me2600io.h"\
	"..\me2600_error.h"\
	"..\me2600defs.h"\
	".\me2600_dll.h"\
	

"$(INTDIR)\me2600_dll_c.obj" : $(SOURCE) $(DEP_CPP_ME2600) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "me2600dll - Win32 Debug"

DEP_CPP_ME2600=\
	"..\_sys\me2600io.h"\
	"..\me2600_error.h"\
	"..\me2600defs.h"\
	".\me2600_dll.h"\
	

"$(INTDIR)\me2600_dll_c.obj" : $(SOURCE) $(DEP_CPP_ME2600) "$(INTDIR)"


!ENDIF 

SOURCE=.\me2600_dll_main.cpp

!IF  "$(CFG)" == "me2600dll - Win32 Release"

DEP_CPP_ME2600_=\
	"..\_sys\me2600io.h"\
	"..\me2600defs.h"\
	".\me2600_dll.h"\
	

"$(INTDIR)\me2600_dll_main.obj" : $(SOURCE) $(DEP_CPP_ME2600_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "me2600dll - Win32 Debug"

DEP_CPP_ME2600_=\
	"..\_sys\me2600io.h"\
	"..\me2600defs.h"\
	".\me2600_dll.h"\
	

"$(INTDIR)\me2600_dll_main.obj" : $(SOURCE) $(DEP_CPP_ME2600_) "$(INTDIR)"


!ENDIF 

SOURCE=.\me2600_dll_vb.cpp

!IF  "$(CFG)" == "me2600dll - Win32 Release"

DEP_CPP_ME2600_D=\
	".\me2600_dll.h"\
	

"$(INTDIR)\me2600_dll_vb.obj" : $(SOURCE) $(DEP_CPP_ME2600_D) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "me2600dll - Win32 Debug"

DEP_CPP_ME2600_D=\
	".\me2600_dll.h"\
	

"$(INTDIR)\me2600_dll_vb.obj" : $(SOURCE) $(DEP_CPP_ME2600_D) "$(INTDIR)"


!ENDIF 


!ENDIF 

