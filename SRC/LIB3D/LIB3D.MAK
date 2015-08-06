# Microsoft Developer Studio Generated NMAKE File, Based on Lib3D.dsp
!IF "$(CFG)" == ""
CFG=Lib3D - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Lib3D - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Lib3D - Win32 Release" && "$(CFG)" != "Lib3D - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Lib3D.mak" CFG="Lib3D - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Lib3D - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Lib3D - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "Lib3D - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\Lib3D.dll"


CLEAN :
	-@erase "$(INTDIR)\alloc.obj"
	-@erase "$(INTDIR)\l3dguid.obj"
	-@erase "$(INTDIR)\Lib3D.obj"
	-@erase "$(INTDIR)\radix.obj"
	-@erase "$(INTDIR)\texmgr.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Lib3D.dll"
	-@erase "$(OUTDIR)\Lib3D.exp"
	-@erase "$(OUTDIR)\Lib3D.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIB3D_EXPORTS" /Fp"$(INTDIR)\Lib3D.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Lib3D.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\Lib3D.pdb" /machine:I386 /out:"$(OUTDIR)\Lib3D.dll" /implib:"$(OUTDIR)\Lib3D.lib" 
LINK32_OBJS= \
	"$(INTDIR)\alloc.obj" \
	"$(INTDIR)\l3dguid.obj" \
	"$(INTDIR)\Lib3D.obj" \
	"$(INTDIR)\radix.obj" \
	"$(INTDIR)\texmgr.obj"

"$(OUTDIR)\Lib3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

OUTDIR=\bob\Debug\exe
INTDIR=\bob\Debug\Lib3D
# Begin Custom Macros
OutDir=\bob\Debug\exe
# End Custom Macros

ALL : "$(OUTDIR)\Lib3D.dll" "$(OUTDIR)\Lib3D.bsc"


CLEAN :
	-@erase "$(INTDIR)\alloc.obj"
	-@erase "$(INTDIR)\alloc.sbr"
	-@erase "$(INTDIR)\l3dguid.obj"
	-@erase "$(INTDIR)\l3dguid.sbr"
	-@erase "$(INTDIR)\Lib3D.obj"
	-@erase "$(INTDIR)\Lib3D.sbr"
	-@erase "$(INTDIR)\radix.obj"
	-@erase "$(INTDIR)\radix.sbr"
	-@erase "$(INTDIR)\texmgr.obj"
	-@erase "$(INTDIR)\texmgr.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Lib3D.bsc"
	-@erase "$(OUTDIR)\Lib3D.dll"
	-@erase "$(OUTDIR)\Lib3D.exp"
	-@erase "$(OUTDIR)\Lib3D.ilk"
	-@erase "$(OUTDIR)\Lib3D.lib"
	-@erase "$(OUTDIR)\Lib3D.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /G6 /Zp1 /MTd /W3 /Gm /GX /Zi /Od /I "\bob\src\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIB3D_EXPORTS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GM /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Lib3D.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\alloc.sbr" \
	"$(INTDIR)\l3dguid.sbr" \
	"$(INTDIR)\Lib3D.sbr" \
	"$(INTDIR)\radix.sbr" \
	"$(INTDIR)\texmgr.sbr"

"$(OUTDIR)\Lib3D.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib dxguid.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\Lib3D.pdb" /debug /machine:I386 /out:"$(OUTDIR)\Lib3D.dll" /implib:"$(OUTDIR)\Lib3D.lib" /pdbtype:sept /libpath:"\bob\src\lib" 
LINK32_OBJS= \
	"$(INTDIR)\alloc.obj" \
	"$(INTDIR)\l3dguid.obj" \
	"$(INTDIR)\Lib3D.obj" \
	"$(INTDIR)\radix.obj" \
	"$(INTDIR)\texmgr.obj"

"$(OUTDIR)\Lib3D.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("Lib3D.dep")
!INCLUDE "Lib3D.dep"
!ELSE 
!MESSAGE Warning: cannot find "Lib3D.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Lib3D - Win32 Release" || "$(CFG)" == "Lib3D - Win32 Debug"
SOURCE=.\alloc.c

!IF  "$(CFG)" == "Lib3D - Win32 Release"


"$(INTDIR)\alloc.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Lib3D.pch"


!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"


"$(INTDIR)\alloc.obj"	"$(INTDIR)\alloc.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\l3dguid.cpp

!IF  "$(CFG)" == "Lib3D - Win32 Release"


"$(INTDIR)\l3dguid.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Lib3D.pch"


!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"


"$(INTDIR)\l3dguid.obj"	"$(INTDIR)\l3dguid.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Lib3D.cpp

!IF  "$(CFG)" == "Lib3D - Win32 Release"


"$(INTDIR)\Lib3D.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Lib3D.pch"


!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"


"$(INTDIR)\Lib3D.obj"	"$(INTDIR)\Lib3D.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\radix.c

!IF  "$(CFG)" == "Lib3D - Win32 Release"


"$(INTDIR)\radix.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Lib3D.pch"


!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"


"$(INTDIR)\radix.obj"	"$(INTDIR)\radix.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\texmgr.cpp

!IF  "$(CFG)" == "Lib3D - Win32 Release"


"$(INTDIR)\texmgr.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Lib3D.pch"


!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"


"$(INTDIR)\texmgr.obj"	"$(INTDIR)\texmgr.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

