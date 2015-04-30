# Microsoft Developer Studio Generated NMAKE File, Based on dll.dsp
!IF "$(CFG)" == ""
CFG=me9x_32 - Win32 Debug
!MESSAGE Keine Konfiguration angegeben. me9x_32 - Win32 Debug wird als Standard\
 verwendet.
!ENDIF 

!IF "$(CFG)" != "me9x_32 - Win32 Release" && "$(CFG)" !=\
 "me9x_32 - Win32 Debug"
!MESSAGE Ungültige Konfiguration "$(CFG)" angegeben.
!MESSAGE Sie können beim Ausführen von NMAKE eine Konfiguration angeben
!MESSAGE durch Definieren des Makros CFG in der Befehlszeile. Zum Beispiel:
!MESSAGE 
!MESSAGE NMAKE /f "dll.mak" CFG="me9x_32 - Win32 Debug"
!MESSAGE 
!MESSAGE Für die Konfiguration stehen zur Auswahl:
!MESSAGE 
!MESSAGE "me9x_32 - Win32 Release" (basierend auf\
  "Win32 (x86) Dynamic-Link Library")
!MESSAGE "me9x_32 - Win32 Debug" (basierend auf\
  "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR Eine ungültige Konfiguration wurde angegeben.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "me9x_32 - Win32 Release"

OUTDIR=.\..\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\me9x_32.dll"

!ELSE 

ALL : "$(OUTDIR)\me9x_32.dll"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dll.res"
	-@erase "$(INTDIR)\dll_c.obj"
	-@erase "$(INTDIR)\dll_class.obj"
	-@erase "$(INTDIR)\dll_main.obj"
	-@erase "$(INTDIR)\dll_pascal.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\me9x_32.dll"
	-@erase "$(OUTDIR)\me9x_32.exp"
	-@erase "$(OUTDIR)\me9x_32.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fp"$(INTDIR)\dll.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dll.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dll.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:no\
 /pdb:"$(OUTDIR)\dll.pdb" /machine:I386 /out:"$(OUTDIR)\me9x_32.dll"\
 /implib:"$(OUTDIR)\me9x_32.lib" 
LINK32_OBJS= \
	"$(INTDIR)\dll.res" \
	"$(INTDIR)\dll_c.obj" \
	"$(INTDIR)\dll_class.obj" \
	"$(INTDIR)\dll_main.obj" \
	"$(INTDIR)\dll_pascal.obj" \
	"..\_lib\medlg32.lib"

"$(OUTDIR)\me9x_32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
PostBuild_Desc=DLL kopieren
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\..\Release
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\me9x_32.dll"
   copy .\Release\me9x_32.dll c:\WINNT\system32
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ELSEIF  "$(CFG)" == "me9x_32 - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\me9x_32.dll" "$(OUTDIR)\dll.bsc"

!ELSE 

ALL : "$(OUTDIR)\me9x_32.dll" "$(OUTDIR)\dll.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\dll.res"
	-@erase "$(INTDIR)\dll_c.obj"
	-@erase "$(INTDIR)\dll_c.sbr"
	-@erase "$(INTDIR)\dll_class.obj"
	-@erase "$(INTDIR)\dll_class.sbr"
	-@erase "$(INTDIR)\dll_main.obj"
	-@erase "$(INTDIR)\dll_main.sbr"
	-@erase "$(INTDIR)\dll_pascal.obj"
	-@erase "$(INTDIR)\dll_pascal.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\dll.bsc"
	-@erase "$(OUTDIR)\me9x_32.dll"
	-@erase "$(OUTDIR)\me9x_32.exp"
	-@erase "$(OUTDIR)\me9x_32.ilk"
	-@erase "$(OUTDIR)\me9x_32.lib"
	-@erase "$(OUTDIR)\me9x_32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FAcs /Fa"$(INTDIR)\\" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\dll.pch" /YX\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

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
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\dll.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\dll.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\dll_c.sbr" \
	"$(INTDIR)\dll_class.sbr" \
	"$(INTDIR)\dll_main.sbr" \
	"$(INTDIR)\dll_pascal.sbr"

"$(OUTDIR)\dll.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib\
 odbccp32.lib /nologo /subsystem:windows /dll /incremental:yes\
 /pdb:"$(OUTDIR)\dll.pdb" /debug /machine:I386 /out:"$(OUTDIR)\me9x_32.dll"\
 /implib:"$(OUTDIR)\me9x_32.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\dll.res" \
	"$(INTDIR)\dll_c.obj" \
	"$(INTDIR)\dll_class.obj" \
	"$(INTDIR)\dll_main.obj" \
	"$(INTDIR)\dll_pascal.obj" \
	"..\_lib\medlg32.lib"

"$(OUTDIR)\me9x_32.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

SOURCE=$(InputPath)
PostBuild_Desc=DLL nach NT kopieren
DS_POSTBUILD_DEP=$(INTDIR)\postbld.dep

ALL : $(DS_POSTBUILD_DEP)

# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

$(DS_POSTBUILD_DEP) : "$(OUTDIR)\me9x_32.dll" "$(OUTDIR)\dll.bsc"
   copy .\Debug\me9x_32.dll c:\WINdows\system
	copy   .\Debug\me9x_32.dll .\..\_inst\Me9x\me9x_32.dll
	rem copy .\Debug\me9x_32.dll   "C:\Program Files\Hewlett-Packard\VEE 4.0\Me9x_32v.dll"
	copy         .\Debug\me9x_32.dll .\..\_inst\Me9x\Me9x_32v.dll
	rem c:\siw95\nmsym.exe      /TRANSLATE:PACKAGE,ALWAYS,SOURCE /SOURCE:.\
      /OUTPUT:c:\windows\system\me9x_32.nms c:\windows\system\me9x_32.dll
	copy   .\Debug\me9x_32.dll c:\WINNT\system32
	copy  .\Debug\me9x_32.dll  .\..\_inst_PEP\Me9x\me9x_32.dll
	copy .\Debug\me9x_32.dll  .\..\_inst_PEP\Me9x\Me9x_32v.dll
	echo Helper for Post-build step > "$(DS_POSTBUILD_DEP)"

!ENDIF 


!IF "$(CFG)" == "me9x_32 - Win32 Release" || "$(CFG)" ==\
 "me9x_32 - Win32 Debug"
SOURCE=dll.rc

"$(INTDIR)\dll.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=dll_c.cpp
DEP_CPP_ME9X_=\
	"..\_osi\9xPio.h"\
	"..\_osi\defs.h"\
	".\dll.h"\
	

!IF  "$(CFG)" == "me9x_32 - Win32 Release"


"$(INTDIR)\dll_c.obj" : $(SOURCE) $(DEP_CPP_ME9X_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "me9x_32 - Win32 Debug"


"$(INTDIR)\dll_c.obj"	"$(INTDIR)\dll_c.sbr" : $(SOURCE)\
 $(DEP_CPP_ME9X_) "$(INTDIR)"


!ENDIF 

SOURCE=dll_class.cpp
DEP_CPP_ME9X_3=\
	"..\_osi\9xPio.h"\
	"..\_osi\defs.h"\
	".\dll.h"\
	

!IF  "$(CFG)" == "me9x_32 - Win32 Release"


"$(INTDIR)\dll_class.obj" : $(SOURCE) $(DEP_CPP_ME9X_3) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "me9x_32 - Win32 Debug"


"$(INTDIR)\dll_class.obj"	"$(INTDIR)\dll_class.sbr" : $(SOURCE)\
 $(DEP_CPP_ME9X_3) "$(INTDIR)"


!ENDIF 

SOURCE=dll_main.cpp
DEP_CPP_ME9X_32=\
	"..\_osi\9xPio.h"\
	"..\_osi\defs.h"\
	".\dll.h"\
	

!IF  "$(CFG)" == "me9x_32 - Win32 Release"


"$(INTDIR)\dll_main.obj" : $(SOURCE) $(DEP_CPP_ME9X_32) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "me9x_32 - Win32 Debug"


"$(INTDIR)\dll_main.obj"	"$(INTDIR)\dll_main.sbr" : $(SOURCE)\
 $(DEP_CPP_ME9X_32) "$(INTDIR)"


!ENDIF 

SOURCE=dll_pascal.cpp
DEP_CPP_ME9X_32_=\
	"..\_osi\9xPio.h"\
	"..\_osi\defs.h"\
	".\dll.h"\
	

!IF  "$(CFG)" == "me9x_32 - Win32 Release"


"$(INTDIR)\dll_pascal.obj" : $(SOURCE) $(DEP_CPP_ME9X_32_) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "me9x_32 - Win32 Debug"


"$(INTDIR)\dll_pascal.obj"	"$(INTDIR)\dll_pascal.sbr" : $(SOURCE)\
 $(DEP_CPP_ME9X_32_) "$(INTDIR)"


!ENDIF 


!ENDIF 

