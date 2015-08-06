# Microsoft Developer Studio Project File - Name="BOB" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=BOB - Win32 DemoDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "bob.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "bob.mak" CFG="BOB - Win32 DemoDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "BOB - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "BOB - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "BOB - Win32 Profile" (based on "Win32 (x86) Application")
!MESSAGE "BOB - Win32 DemoDebug" (based on "Win32 (x86) Application")
!MESSAGE "BOB - Win32 DemoRelease" (based on "Win32 (x86) Application")
!MESSAGE "BOB - Win32 Preview1Day" (based on "Win32 (x86) Application")
!MESSAGE "BOB - Win32 Release No Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\BOB\release\exe"
# PROP Intermediate_Dir "\BOB\release\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /Zp1 /MD /W3 /GX /O2 /Ob2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 quartz.lib strmbase.lib ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib htmlhelp.lib dsound.lib \bob\release\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Tagging date and time of compilation...
PreLink_Cmds=cl /nologo /G6 /Zp1 /DUSER#"%USER%" /MD /W3 /GX /O2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"\BOB\release\obj/" /Fo"\BOB\release\obj/" /Fd"\BOB\release\obj/" /FD /c "000tools.cpp"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\BOB\debug\exe"
# PROP Intermediate_Dir "\BOB\debug\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gi /GX /Zi /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 quartz.lib strmbase.lib Htmlhelp.lib ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib dsound.lib \bob\debug\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Pre Link
PreLink_Cmds=cl /nologo /Zp1 /DUSER#"%USER%" /MDd /W3 /Gi /GX /Zi /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"\BOB\debug\obj/" /Fo"\BOB\debug\obj/" /Fd"\BOB\debug\obj/" /FD /c "000tools.cpp"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BOB___Wi"
# PROP BASE Intermediate_Dir "BOB___Wi"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\BOB\debug\ttexe"
# PROP Intermediate_Dir "\BOB\debug\ttobj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /Gi /GX /Zi /Od /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /Gi /GX /Zi /Od /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 quartz.lib strmbase.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib mss32.lib dplay.lib winmm.lib dinput.lib dxguid.lib smackw32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Pre Link
PreLink_Cmds=cl 000tools.cpp /c /nologo /W3 /GX /Zi /I "..\h"                                                                                    /FR"\BOB\debug\obj/" /Od /D "_DEBUG"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "BOB___Win32_DemoDebug"
# PROP BASE Intermediate_Dir "BOB___Win32_DemoDebug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\BOB\demodeb\exe"
# PROP Intermediate_Dir "\BOB\demodeb\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Zp1 /MDd /W3 /Gi /GX /Zi /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gi /GX /Zi /Od /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "BOB_DEMO_VER" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Htmlhelp.lib ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib dsound.lib \bob\debug\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /libpath:"..\lib"
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 quartz.lib strmbase.lib Htmlhelp.lib ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib dsound.lib \bob\debug\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libc" /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Pre Link
PreLink_Cmds=cl /nologo /DUSER#"%USER%" /Zp1 /MDd /W3 /Gi /GX /Zi /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"\BOB\debug\obj/" /Fo"\BOB\debug\obj/" /Fd"\BOB\debug\obj/" /FD /c "000tools.cpp"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BOB___Win32_DemoRelease"
# PROP BASE Intermediate_Dir "BOB___Win32_DemoRelease"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\bob\demorel\exe"
# PROP Intermediate_Dir "\bob\demorel\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /Zp1 /MD /W3 /GX /O2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /Zp1 /MD /W3 /GX /O2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "BOB_DEMO_VER" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib htmlhelp.lib dsound.lib \bob\release\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\lib"
# ADD LINK32 quartz.lib strmbase.lib ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib htmlhelp.lib dsound.lib \bob\release\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Tagging date and time of compilation...
PreLink_Cmds=cl /nologo /G6 /Zp1 /DUSER#"%USER%" /MD /W3 /GX /O2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"\BOB\release\obj/" /Fo"\BOB\release\obj/" /Fd"\BOB\release\obj/" /FD /c "000tools.cpp"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BOB___Win32_Preview1Day"
# PROP BASE Intermediate_Dir "BOB___Win32_Preview1Day"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\BOB\release\exe"
# PROP Intermediate_Dir "\BOB\release\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /Zp1 /MD /W3 /GX /O2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /Zp1 /MD /W3 /GX /O2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib htmlhelp.lib dsound.lib \bob\release\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\lib"
# ADD LINK32 quartz.lib strmbase.lib ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib htmlhelp.lib dsound.lib \bob\release\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"\BOB\release\exe/bobview.exe" /libpath:"..\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Tagging date and time of compilation...
PreLink_Cmds=cl /nologo /G6 /DUSER#"%USER%" /Zp1 /MD /W3 /GX /O2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"\BOB\release\obj/" /Fo"\BOB\release\obj/" /Fd"\BOB\release\obj/" /FD /c "000tools.cpp"
# End Special Build Tool

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "BOB___Win32_Release_No_Debug"
# PROP BASE Intermediate_Dir "BOB___Win32_Release_No_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\BOB\release\exe"
# PROP Intermediate_Dir "\BOB\release\obj"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /Zp1 /MD /W3 /GX /O2 /Ob2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /Zp1 /MD /W3 /GX /O2 /Ob2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 quartz.lib strmbase.lib ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib htmlhelp.lib dsound.lib \bob\release\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /debug /machine:I386 /libpath:"..\lib"
# ADD LINK32 quartz.lib strmbase.lib ddraw.lib dplay.lib winmm.lib dinput.lib dxguid.lib htmlhelp.lib dsound.lib \bob\release\exe\lib3d.lib vfw32.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\lib"
# SUBTRACT LINK32 /debug
# Begin Special Build Tool
SOURCE="$(InputPath)"
PreLink_Desc=Tagging date and time of compilation...
PreLink_Cmds=cl /nologo /G6 /Zp1 /DUSER#"%USER%" /MD /W3 /GX /O2 /I "\BOB\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"\BOB\release\obj/" /Fo"\BOB\release\obj/" /Fd"\BOB\release\obj/" /FD /c "000tools.cpp"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "BOB - Win32 Release"
# Name "BOB - Win32 Debug"
# Name "BOB - Win32 Profile"
# Name "BOB - Win32 DemoDebug"
# Name "BOB - Win32 DemoRelease"
# Name "BOB - Win32 Preview1Day"
# Name "BOB - Win32 Release No Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "new files trap"

# PROP Default_Filter "cpp"
# End Group
# Begin Group "tool dependency compiled first"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\000tools.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\H\000tools.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /Z7 /O1 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Gm- /Zi /Od /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Gm- /Zi /Od /Yc"stdafx.h"
# ADD CPP /Gm- /Zi /Od /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /Z7 /O2 /Yc"stdafx.h"
# ADD CPP /Z7 /O2 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /Z7 /O2 /Yc"stdafx.h"
# ADD CPP /Z7 /O2 /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /Z7 /O2 /Yc"stdafx.h"
# ADD CPP /O1 /Yc"stdafx.h"
# SUBTRACT CPP /Z<none>

!ENDIF 

# End Source File
# End Group
# Begin Group "assembler"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\Graphics\Grafpasm.asm

!IF  "$(CFG)" == "BOB - Win32 Release"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# Begin Custom Build
IntDir=\BOB\debug\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# Begin Custom Build
IntDir=\BOB\debug\ttobj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# Begin Custom Build
IntDir=\BOB\demodeb\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# Begin Custom Build
IntDir=\bob\demorel\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\Graphics\Grafpasm.asm
InputName=Grafpasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Lstrasm.asm

!IF  "$(CFG)" == "BOB - Win32 Release"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# Begin Custom Build
IntDir=\BOB\debug\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# Begin Custom Build
IntDir=\BOB\debug\ttobj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# Begin Custom Build
IntDir=\BOB\demodeb\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# Begin Custom Build
IntDir=\bob\demorel\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\3d\Lstrasm.asm
InputName=Lstrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Math\Matrasm.asm

!IF  "$(CFG)" == "BOB - Win32 Release"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# Begin Custom Build
IntDir=\BOB\debug\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# Begin Custom Build
IntDir=\BOB\debug\ttobj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# Begin Custom Build
IntDir=\BOB\demodeb\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# Begin Custom Build
IntDir=\bob\demorel\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# Begin Custom Build
IntDir=\BOB\release\obj
InputPath=..\Math\Matrasm.asm
InputName=Matrasm

"$(IntDir)\$(InputName).obj" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ml /c /Cp /Cx /Fo$(IntDir)\$(InputName).obj $(InputPath)

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "3D"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\3D\3dcode.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\3dcom.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\_3D.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /Ob2 /D "BOB_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /G5 /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /Gm- /Gi- /O2 /D "BOB_3D"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Gm- /Gi- /O2 /D "BOB_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /G5 /Od
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /G5 /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_3D"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "BOB_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /Ob2 /D "BOB_3D"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Ob2 /D "BOB_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /Ob2 /D "BOB_3D"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Ob2 /D "BOB_3D"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Anmcntrl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Anmradio.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Btree.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Collided.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Decomp.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Imagemap.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Impact.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Jimcol.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Jimtri.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Landscap.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Lstream.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Migland.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Overlay.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\particle.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Shapes.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Shpbld.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Smktrls.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Tilemake.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /Ob2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /Ob2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Ob2
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Transite.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\Viewsel.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Weappak.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3D\World.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "AI"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\AI\_AI.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Od /D "BOB_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2 /D "BOB_AI"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_AI"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_AI"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_AI"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_AI"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_AI"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AI\Aaa.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Ai\Grid.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AI\Msgai.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\AI\Spotted.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Ai\Usermsg.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "AIRCRAFT"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\AIRCRAFT\_AIRC.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2 /D "BOB_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2 /D "BOB_AIRCRAFT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_AIRCRAFT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_AIRCRAFT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_AIRCRAFT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_AIRCRAFT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_AIRCRAFT"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Cd_bob.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Dt_bf109.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Dt_bf110.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Dt_hurri.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Dt_ju87b.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Dt_other.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Aircraft\Dt_spitf.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "BFIELDS"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\BFIELDS\_BFIE.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /Zd /O2 /D "BOB_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /O2 /D "BOB_BFIELDS" /FR
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /Od /D "BOB_BFIELDS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "BOB_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od /D "BOB_BFIELDS" /FR
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Zi /Od /D "BOB_BFIELDS" /FR
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_BFIELDS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_BFIELDS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_BFIELDS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /Zd /D "BOB_BFIELDS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_BFIELDS"
# SUBTRACT CPP /Z<none> /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Globrefs.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Mapcode.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Messages.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Persons2.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Persons3.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Persons4.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Persons7.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\qmiss.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Savebin.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\BFIELDS\Tank.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "FILES"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\FILES\_FILE.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2 /D "BOB_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /Od /D "BOB_FILES"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "BOB_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_FILES"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "BOB_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_FILES"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_FILES"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_FILES"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_FILES"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\FILES\Fileman.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\FILES\Loadlib.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\FILES\Loadlist.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\FILES\Winfile.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "GENERAL"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\GENERAL\_GENE.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2 /D "BOB_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2 /D "BOB_GENERAL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_GENERAL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_GENERAL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_GENERAL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_GENERAL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_GENERAL"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GENERAL\Malloc.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GENERAL\Static.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\GENERAL\Winerror.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "HARDWARE"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\HARDWARE\_HARD.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Od /D "BOB_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2 /D "BOB_HARDWARE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_HARDWARE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_HARDWARE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_HARDWARE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_HARDWARE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_HARDWARE"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Hardware\Config.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Ddrwinit.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Hardware\Digdrvr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Hardpub.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Hardwin.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Hardware\Messengn.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Hardware\Music.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Rchatter.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Hardware\Sample.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Sfonts.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Hardware\Sound.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\HARDWARE\Win3d.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "INPUT"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\INPUT\_INPU.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Od /D "BOB_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2 /D "BOB_INPUT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_INPUT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_INPUT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_INPUT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_INPUT"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_INPUT"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\INPUT\Analogue.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MATH"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\MATH\_MATH.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2 /D "BOB_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2 /D "BOB_MATH"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_MATH"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_MATH"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_MATH"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_MATH"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MATH"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MATH\Math.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MATH\Matrix.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MISSMAN"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\MISSMAN\_MISS.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /Zd /D "BOB_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od /D "BOB_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /Od /D "BOB_MISSMAN"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "BOB_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od /D "BOB_MISSMAN"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Zi /Od /D "BOB_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_MISSMAN"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_MISSMAN"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MISSMAN"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /Zd /D "BOB_MISSMAN"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MISSMAN"
# SUBTRACT CPP /Z<none> /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Formatn.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Intrmiss.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Missinit.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Node.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Missman\nodebob.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Zi /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Missman\Noderev.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /Od
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Onemiss.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\packages.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Peacmiss.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\Savegame.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MISSMAN\So51miss.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Missman\Sqddiary.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Missman\Uimsg.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MODEL"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\MODEL\_MODE.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Od /D "BOB_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2 /D "BOB_MODEL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_MODEL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_MODEL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_MODEL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_MODEL"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MODEL"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Acmai.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Acmman.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Acmmodel.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Acmsimpl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Aerodev.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Cdat.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Ctrl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Curves.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Dervs.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Elmt.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Engine.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Gear.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Model\Intcock.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Model.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Modint.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Modvec.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MODEL\Sky.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MOVECODE"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\MOVECODE\_MOVE.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /O2 /Ob2 /D "BOB_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Od /D "BOB_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /Od /D "BOB_MOVECODE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "BOB_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Od /D "BOB_MOVECODE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od /D "BOB_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_MOVECODE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_MOVECODE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /O2 /Ob2 /D "BOB_MOVECODE"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /Ob2 /D "BOB_MOVECODE"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Automove.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Flyinit.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Flymodel.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Keyfly.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Moveall.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Movecode\Sagmove.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Od
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Od
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\MOVECODE\Wpaction.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "COMMS"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=..\COMMS\_COMM.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /D "BOB_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Od /D "BOB_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /O2 /D "BOB_COMMS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2 /D "BOB_COMMS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2 /D "BOB_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /D "BOB_COMMS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /D "BOB_COMMS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /D "BOB_COMMS"
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /D "BOB_COMMS"
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\COMMS\Aggrgtor.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\COMMS\Comms.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\COMMS\Replay.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\COMMS\Winmove.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "MFCSTUFF"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\_MFC.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /Z7 /O1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# SUBTRACT BASE CPP /O<none>
# SUBTRACT CPP /O<none>

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od
# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /Z7 /O2
# ADD CPP /Z7 /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1
# ADD BASE CPP /Z7 /O2
# ADD CPP /Z7 /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /Z7 /O2
# ADD CPP /O1
# SUBTRACT CPP /Z<none>

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_MFCPRVW.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CntrItem.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Fullpsys.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O1
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Hintbox.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Input\Keystub.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Listbx.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MapDlg.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MIG.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MIGDoc.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MIGView.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Monotxt.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# SUBTRACT BASE CPP /YX /Yc /Yu
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O1
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MTChild.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RDEmptyD.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RDEmptyP.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rdiallog.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rdialmsg.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RDialog.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rdlgbar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rmdldlg.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RowTasks.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rtestsh1.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rtoolbar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Stub3d.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /Z7 /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /Z7 /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Z7 /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /Z7 /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Z7 /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /Z7 /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /O1
# SUBTRACT CPP /Z<none> /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Uiicons.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /Zi /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /Zi /O2
# SUBTRACT BASE CPP /YX /Yc /Yu
# ADD CPP /Zi /O2
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD CPP /O1

!ENDIF 

# End Source File
# End Group
# Begin Group "AFXSTUB"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\_AFX.CPP

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# ADD BASE CPP /Od
# ADD CPP /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od
# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /O2
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Afxauto.h

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\afxstub.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\font.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\picture.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rbutton.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rcombo.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RComboX.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\redit.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\redtbt.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rjoycfg.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rlistbox.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rradio.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rscrlbar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rspinbut.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rspltbar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rstatic.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rtabs.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rtitle.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "TOOL BARS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_tool.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od
# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dbrftlbr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Maintbar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MapFltrs.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Msctlbr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Scalebar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Statbar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\sysbox.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Teletype.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /O2
# ADD CPP /O2

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Titlebar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "OLD SHEETS"

# PROP Default_Filter "cpp"
# End Group
# Begin Group "FULLPANE SHEETS"

# PROP Default_Filter ""
# Begin Group "fullpane"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_full.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# ADD CPP /Z7

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od
# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# ADD BASE CPP /Z7
# ADD CPP /Z7

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1
# ADD BASE CPP /Z7
# ADD CPP /Z7

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD BASE CPP /Z7
# ADD CPP /O1
# SUBTRACT CPP /Z<none>

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_FULLPRV.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Fpconfig.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Fplayout.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Fullpane.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "CAMP"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Campback.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Campname.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Enddayrl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Enddayrv.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Enddybmp.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Gameselt.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sidesel.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Apilot.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Scamp.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Scontrol.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sdetail.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sflight.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sgame.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Smission.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ssound.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sviewer.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Twodpref.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "FP comms"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Commchat.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Commsac.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Commspnt.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Currembl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Radcomms.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Radio.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Ready.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Service.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Session.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sqview.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Sreplay.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Visitors.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Vwqlist.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "QM_FRAG"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bobfrag.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Quickpar.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squick1.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squick2.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squickp.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squickun.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\Credits.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "DIALOG SHEETS"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\_LW.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od
# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_RAF.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od
# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\_sA.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# ADD BASE CPP /Zi /Od
# ADD CPP /Zi /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Acalloc.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Acunit.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Acunitrf.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Afdetl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Afdossr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1
# ADD CPP /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD BASE CPP /Od
# ADD CPP /Od

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1
# ADD CPP /O1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Author.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Baseslft.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Clock.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Cntrlacl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Cntrlfly.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Cntrltop.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Damage.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dirnores.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dirrsult.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dosbut.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dossdetl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Dossierb.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Filing.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Geschwdr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Grpgesch.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Gwadlist.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Hostiles.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Intelmsg.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Intoff.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Load.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Locker.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Luftflot.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwdiary.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwdiaryd.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwdiaryl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwdirect.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwmssfr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwrevac.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwrevcl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwreven.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwrevst.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwrevtp.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwroutea.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwroutem.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwroutet.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwtaskac.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwtaskfr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwtasksm.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lwtasktp.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Mapfltlw.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Mfraids.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Mftarget.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Mftop.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Phsdscr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Pltlogbk.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafcombt.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafdiary.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafdir.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafdrres.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafdryd.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafdryl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafmssfr.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafrevac.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafrevas.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafrevcl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafreven.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafrevst.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafrevtp.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafroutt.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rafsqlst.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Raftaskf.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Raftasks.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Raftaskt.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Rdempty.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Seltrg.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Squaddtl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Supply.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Thumnail.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tlbrcntl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Tooff.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Totesect.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Totetop.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Weather.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Wpdialog.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Zoomlevl.cpp

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "New Headers Trap"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\BoBFrag.h
# End Source File
# Begin Source File

SOURCE=.\CommChat.h
# End Source File
# Begin Source File

SOURCE=.\Geschwdr.h
# End Source File
# Begin Source File

SOURCE=.\LuftFlot.h
# End Source File
# End Group
# Begin Group "0-9"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=..\H\3dcode.h
# End Source File
# Begin Source File

SOURCE=..\H\3dcom.h
# End Source File
# Begin Source File

SOURCE=..\H\3ddefs.h
# End Source File
# Begin Source File

SOURCE=..\H\3dinstr.h
# End Source File
# End Group
# Begin Group "A"

# PROP Default_Filter "h"
# Begin Group "Astub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AC_view.h
# End Source File
# Begin Source File

SOURCE=.\Acunitrf.h
# End Source File
# Begin Source File

SOURCE=.\AFields.h
# End Source File
# Begin Source File

SOURCE=.\Apilot.h
# End Source File
# Begin Source File

SOURCE=.\Army.h
# End Source File
# Begin Source File

SOURCE=.\Army_dos.h
# End Source File
# Begin Source File

SOURCE=.\ArmyDetl.h
# End Source File
# Begin Source File

SOURCE=.\Armyrqst.h
# End Source File
# Begin Source File

SOURCE=.\Author.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Aaa.h
# End Source File
# Begin Source File

SOURCE=..\H\Ac_view.h
# End Source File
# Begin Source File

SOURCE=..\H\acalloc.h
# End Source File
# Begin Source File

SOURCE=..\H\Acmmodel.h
# End Source File
# Begin Source File

SOURCE=..\H\Acunit.h
# End Source File
# Begin Source File

SOURCE=.\Acunit.h
# End Source File
# Begin Source File

SOURCE=..\H\Acunitrf.h
# End Source File
# Begin Source File

SOURCE=..\H\Aerodev.h
# End Source File
# Begin Source File

SOURCE=..\H\Afdetl.h
# End Source File
# Begin Source File

SOURCE=.\Afdetl.h
# End Source File
# Begin Source File

SOURCE=..\H\Afdossr.h
# End Source File
# Begin Source File

SOURCE=.\Afdossr.h
# End Source File
# Begin Source File

SOURCE=..\H\Afields.h
# End Source File
# Begin Source File

SOURCE=..\H\Aggrgtor.h
# End Source File
# Begin Source File

SOURCE=..\H\Ai.h
# End Source File
# Begin Source File

SOURCE=..\H\Airstruc.h
# End Source File
# Begin Source File

SOURCE=..\H\Analogue.h
# End Source File
# Begin Source File

SOURCE=..\H\Animdata.h
# End Source File
# Begin Source File

SOURCE=..\H\Animmove.h
# End Source File
# Begin Source File

SOURCE=..\H\Anmradio.h
# End Source File
# Begin Source File

SOURCE=..\H\Apilot.h
# End Source File
# Begin Source File

SOURCE=..\H\Areatype.h
# End Source File
# Begin Source File

SOURCE=..\H\Army.h
# End Source File
# Begin Source File

SOURCE=..\H\Army_dos.h
# End Source File
# Begin Source File

SOURCE=..\H\Armydetl.h
# End Source File
# Begin Source File

SOURCE=..\H\Armyrqst.h
# End Source File
# Begin Source File

SOURCE=..\H\Author.h
# End Source File
# End Group
# Begin Group "B"

# PROP Default_Filter ""
# Begin Group "Bstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bases.h
# End Source File
# Begin Source File

SOURCE=.\Basest.h
# End Source File
# Begin Source File

SOURCE=.\Battdetl.h
# End Source File
# Begin Source File

SOURCE=.\Butonbar.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Bases.h
# End Source File
# Begin Source File

SOURCE=..\H\Baseslft.h
# End Source File
# Begin Source File

SOURCE=.\Baseslft.h
# End Source File
# Begin Source File

SOURCE=..\H\Basest.h
# End Source File
# Begin Source File

SOURCE="C:\Program Files\Microsoft Visual Studio\Vc98\Include\Basetsd.h"
# End Source File
# Begin Source File

SOURCE="..\..\..\Program Files\Microsoft Visual Studio\Vc98\Include\Basetsd.h"
# End Source File
# Begin Source File

SOURCE=..\H\Batnode.h
# End Source File
# Begin Source File

SOURCE=..\H\Battdetl.h
# End Source File
# Begin Source File

SOURCE=..\H\Bfcommon.h
# End Source File
# Begin Source File

SOURCE=..\H\Bfenum.h
# End Source File
# Begin Source File

SOURCE=..\H\Bfnumber.h
# End Source File
# Begin Source File

SOURCE=..\H\Bitcount.h
# End Source File
# Begin Source File

SOURCE=..\H\Bitfield.h
# End Source File
# Begin Source File

SOURCE=..\H\Bobfrag.h
# End Source File
# Begin Source File

SOURCE=..\H\Boxcol.h
# End Source File
# Begin Source File

SOURCE=..\H\Briefing.h
# End Source File
# Begin Source File

SOURCE=..\H\Bstream.h
# End Source File
# Begin Source File

SOURCE=..\H\Btree.h
# End Source File
# Begin Source File

SOURCE=..\H\Butonbar.h
# End Source File
# End Group
# Begin Group "C"

# PROP Default_Filter ""
# Begin Group "Cstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Campback.h
# End Source File
# Begin Source File

SOURCE=.\Camplist.h
# End Source File
# Begin Source File

SOURCE=.\Campwar.h
# End Source File
# Begin Source File

SOURCE=.\Career.h
# End Source File
# Begin Source File

SOURCE=.\Chain.h
# End Source File
# Begin Source File

SOURCE=.\Choke.h
# End Source File
# Begin Source File

SOURCE=.\ChSquad.h
# End Source File
# Begin Source File

SOURCE=.\Cmbtview.h
# End Source File
# Begin Source File

SOURCE=.\Comit_e.h
# End Source File
# Begin Source File

SOURCE=.\Commsac.h
# End Source File
# Begin Source File

SOURCE=.\Commspnt.h
# End Source File
# Begin Source File

SOURCE=.\Currembl.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Campback.h
# End Source File
# Begin Source File

SOURCE=..\H\Camplist.h
# End Source File
# Begin Source File

SOURCE=..\H\Campname.h
# End Source File
# Begin Source File

SOURCE=.\Campname.h
# End Source File
# Begin Source File

SOURCE=..\H\Campwar.h
# End Source File
# Begin Source File

SOURCE=..\H\Career.h
# End Source File
# Begin Source File

SOURCE=..\H\Cbuffer.h
# End Source File
# Begin Source File

SOURCE=..\H\Chain.h
# End Source File
# Begin Source File

SOURCE=..\H\Choke.h
# End Source File
# Begin Source File

SOURCE=..\H\Chsquad.h
# End Source File
# Begin Source File

SOURCE=..\H\Clock.h
# End Source File
# Begin Source File

SOURCE=.\Clock.h
# End Source File
# Begin Source File

SOURCE=..\H\Cmbtview.h
# End Source File
# Begin Source File

SOURCE=..\H\Cntritem.h
# End Source File
# Begin Source File

SOURCE=..\H\Cntrlacl.h
# End Source File
# Begin Source File

SOURCE=.\Cntrlacl.h
# End Source File
# Begin Source File

SOURCE=..\H\Cntrlfly.h
# End Source File
# Begin Source File

SOURCE=.\Cntrlfly.h
# End Source File
# Begin Source File

SOURCE=..\H\Cntrltop.h
# End Source File
# Begin Source File

SOURCE=.\Cntrltop.h
# End Source File
# Begin Source File

SOURCE=..\H\Collided.h
# End Source File
# Begin Source File

SOURCE=..\H\Comit_e.h
# End Source File
# Begin Source File

SOURCE=..\H\Commchat.h
# End Source File
# Begin Source File

SOURCE=..\H\Comms.h
# End Source File
# Begin Source File

SOURCE=..\H\Commsac.h
# End Source File
# Begin Source File

SOURCE=..\H\Commspnt.h
# End Source File
# Begin Source File

SOURCE=..\H\Config.h
# End Source File
# Begin Source File

SOURCE=..\H\Contlist.h
# End Source File
# Begin Source File

SOURCE=..\H\Credits.h
# End Source File
# Begin Source File

SOURCE=.\Credits.h
# End Source File
# Begin Source File

SOURCE=..\H\Cstring.h
# End Source File
# Begin Source File

SOURCE=..\H\Ctimeout.h
# End Source File
# Begin Source File

SOURCE=..\H\Ctrl.h
# End Source File
# Begin Source File

SOURCE=..\H\Currembl.h
# End Source File
# Begin Source File

SOURCE=..\H\Curves.h
# End Source File
# Begin Source File

SOURCE=..\H\Custbb.h
# End Source File
# End Group
# Begin Group "D"

# PROP Default_Filter ""
# Begin Group "Dstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Damage.h
# End Source File
# Begin Source File

SOURCE=.\Dbrftlbr.h
# End Source File
# Begin Source File

SOURCE=.\Directs.h
# End Source File
# Begin Source File

SOURCE=.\Directs1.h
# End Source File
# Begin Source File

SOURCE=.\Directs2.h
# End Source File
# Begin Source File

SOURCE=.\DIS.h
# End Source File
# Begin Source File

SOURCE=.\disnotes.h
# End Source File
# Begin Source File

SOURCE=.\DosBut.h
# End Source File
# Begin Source File

SOURCE=.\Dossier.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\D3dmacs.h
# End Source File
# Begin Source File

SOURCE=..\H\Damage.h
# End Source File
# Begin Source File

SOURCE=..\H\Dbrftlbr.h
# End Source File
# Begin Source File

SOURCE=..\H\Debrief.h
# End Source File
# Begin Source File

SOURCE=.\Debrief.h
# End Source File
# Begin Source File

SOURCE=..\H\Digdrvr.h
# End Source File
# Begin Source File

SOURCE=..\H\Dinput.h
# End Source File
# Begin Source File

SOURCE=..\H\Directs.h
# End Source File
# Begin Source File

SOURCE=..\H\Directs1.h
# End Source File
# Begin Source File

SOURCE=..\H\Directs2.h
# End Source File
# Begin Source File

SOURCE=..\H\Dirnores.h
# End Source File
# Begin Source File

SOURCE=.\Dirnores.h
# End Source File
# Begin Source File

SOURCE=..\H\Dirrsult.h
# End Source File
# Begin Source File

SOURCE=.\Dirrsult.h
# End Source File
# Begin Source File

SOURCE=..\H\Dis.h
# End Source File
# Begin Source File

SOURCE=..\H\Dis_note.h
# End Source File
# Begin Source File

SOURCE=.\Dis_note.h
# End Source File
# Begin Source File

SOURCE=..\H\Disnotes.h
# End Source File
# Begin Source File

SOURCE=..\H\Display.h
# End Source File
# Begin Source File

SOURCE=..\H\Dls1.h
# End Source File
# Begin Source File

SOURCE=..\H\Dmdls.h
# End Source File
# Begin Source File

SOURCE=..\H\Dmerror.h
# End Source File
# Begin Source File

SOURCE=..\H\Dmusicc.h
# End Source File
# Begin Source File

SOURCE=..\H\Dmusici.h
# End Source File
# Begin Source File

SOURCE=..\H\Dosbut.h
# End Source File
# Begin Source File

SOURCE=..\H\Dosdefs.h
# End Source File
# Begin Source File

SOURCE=..\H\Dossdetl.h
# End Source File
# Begin Source File

SOURCE=.\Dossdetl.h
# End Source File
# Begin Source File

SOURCE=..\H\Dossier.h
# End Source File
# Begin Source File

SOURCE=..\H\Dossierb.h
# End Source File
# Begin Source File

SOURCE=.\Dossierb.h
# End Source File
# Begin Source File

SOURCE=..\H\Dplobby.h
# End Source File
# End Group
# Begin Group "E"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Elmt.h
# End Source File
# Begin Source File

SOURCE=..\H\Enddayrl.h
# End Source File
# Begin Source File

SOURCE=.\Enddayrl.h
# End Source File
# Begin Source File

SOURCE=..\H\Enddayrv.h
# End Source File
# Begin Source File

SOURCE=.\Enddayrv.h
# End Source File
# Begin Source File

SOURCE=..\H\Enddybmp.h
# End Source File
# Begin Source File

SOURCE=.\Enddybmp.h
# End Source File
# Begin Source File

SOURCE=..\H\Engine.h
# End Source File
# Begin Source File

SOURCE=..\H\Enumbits.m
# End Source File
# End Group
# Begin Group "F"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Fastmath.h
# End Source File
# Begin Source File

SOURCE=..\H\Fileman.h
# End Source File
# Begin Source File

SOURCE=..\H\Filing.h
# End Source File
# Begin Source File

SOURCE=.\Filing.h
# End Source File
# Begin Source File

SOURCE=..\H\Filters.h
# End Source File
# Begin Source File

SOURCE=.\Filters.h
# End Source File
# Begin Source File

SOURCE=..\H\flt_task.h
# End Source File
# Begin Source File

SOURCE=.\Flt_Task.h
# End Source File
# Begin Source File

SOURCE=..\H\Flyinit.h
# End Source File
# Begin Source File

SOURCE=..\H\Flymodel.h
# End Source File
# Begin Source File

SOURCE=..\H\Font.h
# End Source File
# Begin Source File

SOURCE=.\Font.h
# End Source File
# Begin Source File

SOURCE=..\H\Fontlist.h
# End Source File
# Begin Source File

SOURCE=..\H\Fonts.h
# End Source File
# Begin Source File

SOURCE=..\H\Footage.h
# End Source File
# Begin Source File

SOURCE=.\Footage.h
# End Source File
# Begin Source File

SOURCE=..\H\Frag.h
# End Source File
# Begin Source File

SOURCE=.\Frag.h
# End Source File
# Begin Source File

SOURCE=..\H\Fragpilt.h
# End Source File
# Begin Source File

SOURCE=.\FragPilt.h
# End Source File
# Begin Source File

SOURCE=..\H\Frmap2.h
# End Source File
# Begin Source File

SOURCE=..\H\Frmap2sk.h
# End Source File
# Begin Source File

SOURCE=..\H\Frmap3.h
# End Source File
# Begin Source File

SOURCE=..\H\Frmap3sk.h
# End Source File
# Begin Source File

SOURCE=..\H\Frontmap.h
# End Source File
# Begin Source File

SOURCE=..\H\Fullpane.h
# End Source File
# Begin Source File

SOURCE=.\Fullpane.h
# End Source File
# End Group
# Begin Group "G"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Gameselt.h
# End Source File
# Begin Source File

SOURCE=.\Gameselt.h
# End Source File
# Begin Source File

SOURCE=..\H\Gameset.h
# End Source File
# Begin Source File

SOURCE=..\H\Gear.h
# End Source File
# Begin Source File

SOURCE=..\H\General.h
# End Source File
# Begin Source File

SOURCE=.\General.h
# End Source File
# Begin Source File

SOURCE=..\H\Geschwdr.h
# End Source File
# Begin Source File

SOURCE=..\H\Getset.h
# End Source File
# Begin Source File

SOURCE=..\H\Globdefs.h
# End Source File
# Begin Source File

SOURCE=..\H\globrefs.h
# End Source File
# Begin Source File

SOURCE=..\H\Grid.h
# End Source File
# Begin Source File

SOURCE=..\H\Grndview.h
# End Source File
# Begin Source File

SOURCE=.\Grndview.h
# End Source File
# Begin Source File

SOURCE=..\H\Groupitt.h
# End Source File
# Begin Source File

SOURCE=..\H\Grpgesch.h
# End Source File
# Begin Source File

SOURCE=.\Grpgesch.h
# End Source File
# Begin Source File

SOURCE=..\H\Gwadlist.h
# End Source File
# Begin Source File

SOURCE=.\Gwadlist.h
# End Source File
# End Group
# Begin Group "H"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\acalloc.h
# End Source File
# Begin Source File

SOURCE=..\H\Hardpasm.h
# End Source File
# Begin Source File

SOURCE=..\H\Hdata.h
# End Source File
# Begin Source File

SOURCE=..\H\Hdata2.h
# End Source File
# Begin Source File

SOURCE=..\H\Hintbox.h
# End Source File
# Begin Source File

SOURCE=.\Hintbox.h
# End Source File
# Begin Source File

SOURCE=..\Rbutton\Hintbox.h
# End Source File
# Begin Source File

SOURCE=..\H\Hostiles.h
# End Source File
# Begin Source File

SOURCE=.\Hostiles.h
# End Source File
# Begin Source File

SOURCE=..\H\Hotkeys.h
# End Source File
# Begin Source File

SOURCE=..\H\Htmlhelp.h
# End Source File
# End Group
# Begin Group "I"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Imagemap.h
# End Source File
# Begin Source File

SOURCE=..\H\Impact.h
# End Source File
# Begin Source File

SOURCE=..\H\Infoitem.h
# End Source File
# Begin Source File

SOURCE=..\H\Intcock.h
# End Source File
# Begin Source File

SOURCE=..\H\Intelmsg.h
# End Source File
# Begin Source File

SOURCE=.\Intelmsg.h
# End Source File
# Begin Source File

SOURCE=..\H\Intoff.h
# End Source File
# Begin Source File

SOURCE=.\Intoff.h
# End Source File
# Begin Source File

SOURCE=..\H\Inttest.h
# End Source File
# End Group
# Begin Group "J"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Joyconfg.h
# End Source File
# Begin Source File

SOURCE=.\JoyConfg.h
# End Source File
# Begin Source File

SOURCE=..\H\Joyerror.h
# End Source File
# Begin Source File

SOURCE=.\JoyError.h
# End Source File
# End Group
# Begin Group "K"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Keymaps.h
# End Source File
# Begin Source File

SOURCE=..\H\Keytest.h
# End Source File
# End Group
# Begin Group "L"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Landscap.h
# End Source File
# Begin Source File

SOURCE=..\H\Lbm.h
# End Source File
# Begin Source File

SOURCE=..\H\Lbmcpp.h
# End Source File
# Begin Source File

SOURCE=..\H\Lghtshad.h
# End Source File
# Begin Source File

SOURCE=..\Lib3D\Lib3D.h
# End Source File
# Begin Source File

SOURCE=..\H\Libdefs.h
# End Source File
# Begin Source File

SOURCE=..\H\Link.h
# End Source File
# Begin Source File

SOURCE=..\H\Listbx.h
# End Source File
# Begin Source File

SOURCE=.\Listbx.h
# End Source File
# Begin Source File

SOURCE=..\H\Lnchrdat.h
# End Source File
# Begin Source File

SOURCE=..\H\Load.h
# End Source File
# Begin Source File

SOURCE=.\Load.h
# End Source File
# Begin Source File

SOURCE=..\H\Loadprof.h
# End Source File
# Begin Source File

SOURCE=.\Loadprof.h
# End Source File
# Begin Source File

SOURCE=..\H\Locker.h
# End Source File
# Begin Source File

SOURCE=.\Locker.h
# End Source File
# Begin Source File

SOURCE=..\H\Lstmsnlg.h
# End Source File
# Begin Source File

SOURCE=.\Lstmsnlg.h
# End Source File
# Begin Source File

SOURCE=..\H\Lstream.h
# End Source File
# Begin Source File

SOURCE=..\H\Luftflot.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwdiary.h
# End Source File
# Begin Source File

SOURCE=.\Lwdiary.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwdiaryd.h
# End Source File
# Begin Source File

SOURCE=.\Lwdiaryd.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwdiaryl.h
# End Source File
# Begin Source File

SOURCE=.\Lwdiaryl.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwdirect.h
# End Source File
# Begin Source File

SOURCE=.\Lwdirect.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwmssfr.h
# End Source File
# Begin Source File

SOURCE=.\Lwmssfr.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwrevac.h
# End Source File
# Begin Source File

SOURCE=.\Lwrevac.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwrevcl.h
# End Source File
# Begin Source File

SOURCE=.\Lwrevcl.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwreven.h
# End Source File
# Begin Source File

SOURCE=.\Lwreven.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwrevst.h
# End Source File
# Begin Source File

SOURCE=.\Lwrevst.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwrevtp.h
# End Source File
# Begin Source File

SOURCE=.\Lwrevtp.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwroutea.h
# End Source File
# Begin Source File

SOURCE=.\Lwroutea.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwroutem.h
# End Source File
# Begin Source File

SOURCE=.\Lwroutem.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwroutet.h
# End Source File
# Begin Source File

SOURCE=.\Lwroutet.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwtaskac.h
# End Source File
# Begin Source File

SOURCE=.\Lwtaskac.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwtaskfr.h
# End Source File
# Begin Source File

SOURCE=.\Lwtaskfr.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwtasksm.h
# End Source File
# Begin Source File

SOURCE=.\Lwtasksm.h
# End Source File
# Begin Source File

SOURCE=..\H\Lwtasktp.h
# End Source File
# Begin Source File

SOURCE=.\Lwtasktp.h
# End Source File
# End Group
# Begin Group "M"

# PROP Default_Filter ""
# Begin Group "Mstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Maintbar.h
# End Source File
# Begin Source File

SOURCE=.\MapFltrs.h
# End Source File
# Begin Source File

SOURCE=.\Misn_log.h
# End Source File
# Begin Source File

SOURCE=.\Misntext.h
# End Source File
# Begin Source File

SOURCE=.\Missfldr.h
# End Source File
# Begin Source File

SOURCE=.\Msctlbr.h
# End Source File
# Begin Source File

SOURCE=.\MTChild.h
# End Source File
# End Group
# Begin Group "MY"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Myangles.h
# End Source File
# Begin Source File

SOURCE=..\H\Myerror.h
# End Source File
# Begin Source File

SOURCE=..\H\Mymath.h
# End Source File
# Begin Source File

SOURCE=..\H\Mystack.h
# End Source File
# Begin Source File

SOURCE=..\H\Mytime.h
# End Source File
# Begin Source File

SOURCE=..\H\Myvector.h
# End Source File
# End Group
# Begin Group "BOB"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\bob.h
# End Source File
# Begin Source File

SOURCE=..\H\Mig.h
# End Source File
# Begin Source File

SOURCE=..\H\Migdoc.h
# End Source File
# Begin Source File

SOURCE=..\H\Migview.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Mainfrm.h
# End Source File
# Begin Source File

SOURCE=..\H\maintbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Makebf.h
# End Source File
# Begin Source File

SOURCE=..\H\MapDlg.h
# End Source File
# Begin Source File

SOURCE=..\H\Mapedge.h
# End Source File
# Begin Source File

SOURCE=..\H\Mapfltlw.h
# End Source File
# Begin Source File

SOURCE=.\Mapfltlw.h
# End Source File
# Begin Source File

SOURCE=..\H\Mapfltrs.h
# End Source File
# Begin Source File

SOURCE=..\H\Mapsfx.h
# End Source File
# Begin Source File

SOURCE=..\H\Mathasm.h
# End Source File
# Begin Source File

SOURCE=..\H\Matrix.h
# End Source File
# Begin Source File

SOURCE=..\H\Messages.h
# End Source File
# Begin Source File

SOURCE=..\H\Messengn.h
# End Source File
# Begin Source File

SOURCE=..\H\Mfraids.h
# End Source File
# Begin Source File

SOURCE=.\Mfraids.h
# End Source File
# Begin Source File

SOURCE=..\H\Mftarget.h
# End Source File
# Begin Source File

SOURCE=.\Mftarget.h
# End Source File
# Begin Source File

SOURCE=..\H\Mftop.h
# End Source File
# Begin Source File

SOURCE=.\Mftop.h
# End Source File
# Begin Source File

SOURCE=..\H\Migland.h
# End Source File
# Begin Source File

SOURCE=..\H\Miles.h
# End Source File
# Begin Source File

SOURCE=..\H\Milesxtr.h
# End Source File
# Begin Source File

SOURCE=..\H\Misn_log.h
# End Source File
# Begin Source File

SOURCE=..\H\Misntext.h
# End Source File
# Begin Source File

SOURCE=..\H\missfldr.h
# End Source File
# Begin Source File

SOURCE=..\H\Missman2.h
# End Source File
# Begin Source File

SOURCE=..\H\Misssub.h
# End Source File
# Begin Source File

SOURCE=..\H\Model.h
# End Source File
# Begin Source File

SOURCE=..\H\Modfile.h
# End Source File
# Begin Source File

SOURCE=..\H\Modinst.h
# End Source File
# Begin Source File

SOURCE=..\H\Modint.h
# End Source File
# Begin Source File

SOURCE=..\H\Modvec.h
# End Source File
# Begin Source File

SOURCE=..\H\Monotxt.h
# End Source File
# Begin Source File

SOURCE=..\H\Mouse.h
# End Source File
# Begin Source File

SOURCE=..\H\Movement.h
# End Source File
# Begin Source File

SOURCE=..\H\Mresult.h
# End Source File
# Begin Source File

SOURCE=.\MResult.h
# End Source File
# Begin Source File

SOURCE=..\H\Mscdex.h
# End Source File
# Begin Source File

SOURCE=..\H\Msctlbr.h
# End Source File
# Begin Source File

SOURCE=..\H\Msn_ctrl.h
# End Source File
# Begin Source File

SOURCE=..\H\Msndebrf.h
# End Source File
# Begin Source File

SOURCE=.\Msndebrf.h
# End Source File
# Begin Source File

SOURCE=..\H\Mssw.h
# End Source File
# Begin Source File

SOURCE=..\H\Mtchild.h
# End Source File
# Begin Source File

SOURCE=..\H\Music.h
# End Source File
# End Group
# Begin Group "N"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Node.h
# End Source File
# Begin Source File

SOURCE=..\h\nodebob.h
# End Source File
# Begin Source File

SOURCE=..\H\Nose_art.h
# End Source File
# Begin Source File

SOURCE=.\Nose_art.h
# End Source File
# Begin Source File

SOURCE=..\H\Notes.h
# End Source File
# Begin Source File

SOURCE=.\Notes.h
# End Source File
# End Group
# Begin Group "O"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Overlay.h
# End Source File
# Begin Source File

SOURCE=..\H\Overview.h
# End Source File
# Begin Source File

SOURCE=.\Overview.h
# End Source File
# End Group
# Begin Group "P"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\package.h
# End Source File
# Begin Source File

SOURCE=..\H\Paint.h
# End Source File
# Begin Source File

SOURCE=.\Paint.h
# End Source File
# Begin Source File

SOURCE=..\H\Palette.h
# End Source File
# Begin Source File

SOURCE=..\H\Payload.h
# End Source File
# Begin Source File

SOURCE=.\Payload.h
# End Source File
# Begin Source File

SOURCE=..\H\Personal.h
# End Source File
# Begin Source File

SOURCE=.\personal.h
# End Source File
# Begin Source File

SOURCE=..\H\Persons2.h
# End Source File
# Begin Source File

SOURCE=..\H\Phsdscr.h
# End Source File
# Begin Source File

SOURCE=.\Phsdscr.h
# End Source File
# Begin Source File

SOURCE=..\H\Picture.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=..\H\Pilots.h
# End Source File
# Begin Source File

SOURCE=.\Pilots.h
# End Source File
# Begin Source File

SOURCE=..\H\Planetyp.h
# End Source File
# Begin Source File

SOURCE=..\H\Pltlogbk.h
# End Source File
# Begin Source File

SOURCE=.\Pltlogbk.h
# End Source File
# Begin Source File

SOURCE=..\H\Plyr_log.h
# End Source File
# Begin Source File

SOURCE=.\Plyr_log.h
# End Source File
# Begin Source File

SOURCE=..\H\Polygon.h
# End Source File
# Begin Source File

SOURCE=..\H\Prof.h
# End Source File
# Begin Source File

SOURCE=..\H\Prof_lib.h
# End Source File
# Begin Source File

SOURCE=.\Prof_lib.h
# End Source File
# Begin Source File

SOURCE=..\H\profile.h
# End Source File
# Begin Source File

SOURCE=.\Profile.h
# End Source File
# End Group
# Begin Group "Q"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Quickpar.h
# End Source File
# Begin Source File

SOURCE=.\Quickpar.h
# End Source File
# Begin Source File

SOURCE=..\H\Quikmisn.h
# End Source File
# Begin Source File

SOURCE=.\Quikmisn.h
# End Source File
# End Group
# Begin Group "R"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\rad.h
# End Source File
# Begin Source File

SOURCE=..\H\Radcomms.h
# End Source File
# Begin Source File

SOURCE=.\Radcomms.h
# End Source File
# Begin Source File

SOURCE=..\H\Raddef.h
# End Source File
# Begin Source File

SOURCE=..\H\Radio.h
# End Source File
# Begin Source File

SOURCE=.\Radio.h
# End Source File
# Begin Source File

SOURCE=..\H\Radiocht.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafcombt.h
# End Source File
# Begin Source File

SOURCE=.\Rafcombt.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafdiary.h
# End Source File
# Begin Source File

SOURCE=.\Rafdiary.h
# End Source File
# Begin Source File

SOURCE=..\H\rafdir.h
# End Source File
# Begin Source File

SOURCE=.\Rafdir.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafdrres.h
# End Source File
# Begin Source File

SOURCE=.\Rafdrres.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafdryd.h
# End Source File
# Begin Source File

SOURCE=.\Rafdryd.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafdryl.h
# End Source File
# Begin Source File

SOURCE=.\Rafdryl.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafmssfr.h
# End Source File
# Begin Source File

SOURCE=.\Rafmssfr.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafrevac.h
# End Source File
# Begin Source File

SOURCE=.\Rafrevac.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafrevas.h
# End Source File
# Begin Source File

SOURCE=.\Rafrevas.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafrevcl.h
# End Source File
# Begin Source File

SOURCE=.\Rafrevcl.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafreven.h
# End Source File
# Begin Source File

SOURCE=.\Rafreven.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafrevst.h
# End Source File
# Begin Source File

SOURCE=.\Rafrevst.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafrevtp.h
# End Source File
# Begin Source File

SOURCE=.\Rafrevtp.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafrouta.h
# End Source File
# Begin Source File

SOURCE=.\Rafrouta.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafroutm.h
# End Source File
# Begin Source File

SOURCE=.\Rafroutm.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafroutt.h
# End Source File
# Begin Source File

SOURCE=.\Rafroutt.h
# End Source File
# Begin Source File

SOURCE=..\H\Rafsqlst.h
# End Source File
# Begin Source File

SOURCE=.\Rafsqlst.h
# End Source File
# Begin Source File

SOURCE=..\H\Raftaskf.h
# End Source File
# Begin Source File

SOURCE=.\Raftaskf.h
# End Source File
# Begin Source File

SOURCE=..\H\Raftasks.h
# End Source File
# Begin Source File

SOURCE=.\Raftasks.h
# End Source File
# Begin Source File

SOURCE=..\H\Raftaskt.h
# End Source File
# Begin Source File

SOURCE=.\Raftaskt.h
# End Source File
# Begin Source File

SOURCE=..\H\Ranges.h
# End Source File
# Begin Source File

SOURCE=..\H\Rbutton.h
# End Source File
# Begin Source File

SOURCE=.\rbutton.h
# End Source File
# Begin Source File

SOURCE=..\rbutton\rbuttonc.h
# End Source File
# Begin Source File

SOURCE=..\H\Rchatter.h
# End Source File
# Begin Source File

SOURCE=..\H\Rchatxtr.h
# End Source File
# Begin Source File

SOURCE=..\H\Rcombo.h
# End Source File
# Begin Source File

SOURCE=.\rcombo.h
# End Source File
# Begin Source File

SOURCE=..\H\RComboX.h
# End Source File
# Begin Source File

SOURCE=.\RComboX.h
# End Source File
# Begin Source File

SOURCE=..\H\Rcstmbtn.h
# End Source File
# Begin Source File

SOURCE=.\Rcstmbtn.h
# End Source File
# Begin Source File

SOURCE=..\H\Rdempty.h
# End Source File
# Begin Source File

SOURCE=..\H\Rdemptyd.h
# End Source File
# Begin Source File

SOURCE=.\RDEmptyD.h
# End Source File
# Begin Source File

SOURCE=..\H\Rdemptyp.h
# End Source File
# Begin Source File

SOURCE=.\RDEmptyP.h
# End Source File
# Begin Source File

SOURCE=..\H\Rdialmsg.h
# End Source File
# Begin Source File

SOURCE=..\H\Rdialog.h
# End Source File
# Begin Source File

SOURCE=..\H\rdlgbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Ready.h
# End Source File
# Begin Source File

SOURCE=.\Ready.h
# End Source File
# Begin Source File

SOURCE=..\H\redit.h
# End Source File
# Begin Source File

SOURCE=.\Redit.h
# End Source File
# Begin Source File

SOURCE=..\H\redtbt.h
# End Source File
# Begin Source File

SOURCE=.\Redtbt.h
# End Source File
# Begin Source File

SOURCE=..\H\Replay.h
# End Source File
# Begin Source File

SOURCE=..\H\Rip_list.h
# End Source File
# Begin Source File

SOURCE=.\RIP_List.h
# End Source File
# Begin Source File

SOURCE=..\H\Rjoycfg.h
# End Source File
# Begin Source File

SOURCE=.\rjoycfg.h
# End Source File
# Begin Source File

SOURCE=..\H\rlistbox.h
# End Source File
# Begin Source File

SOURCE=.\rlistbox.h
# End Source File
# Begin Source File

SOURCE=..\rlistbox\rlistbxc.h
# End Source File
# Begin Source File

SOURCE=..\H\Rmdldlg.h
# End Source File
# Begin Source File

SOURCE=.\Rmdldlg.h
# End Source File
# Begin Source File

SOURCE=..\H\Route.h
# End Source File
# Begin Source File

SOURCE=.\Route.h
# End Source File
# Begin Source File

SOURCE=..\H\Rowtasks.h
# End Source File
# Begin Source File

SOURCE=.\RowTasks.h
# End Source File
# Begin Source File

SOURCE=..\H\Rradio.h
# End Source File
# Begin Source File

SOURCE=.\Rradio.h
# End Source File
# Begin Source File

SOURCE=..\H\Rscrlbar.h
# End Source File
# Begin Source File

SOURCE=.\rscrlbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Rsheets.h
# End Source File
# Begin Source File

SOURCE=..\H\Rspinbut.h
# End Source File
# Begin Source File

SOURCE=.\Rspinbut.h
# End Source File
# Begin Source File

SOURCE=..\H\Rspltbar.h
# End Source File
# Begin Source File

SOURCE=.\Rspltbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Rstatic.h
# End Source File
# Begin Source File

SOURCE=.\rstatic.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtabs.h
# End Source File
# Begin Source File

SOURCE=.\Rtabs.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtest1.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtestsh1.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtickbox.h
# End Source File
# Begin Source File

SOURCE=.\Rtickbox.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtitle.h
# End Source File
# Begin Source File

SOURCE=..\H\Rtoolbar.h
# End Source File
# Begin Source File

SOURCE=.\Rtoolbar.h
# End Source File
# End Group
# Begin Group "S"

# PROP Default_Filter ""
# Begin Group "Sstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Sairclms.h
# End Source File
# Begin Source File

SOURCE=.\Saveprof.h
# End Source File
# Begin Source File

SOURCE=.\Saverep.h
# End Source File
# Begin Source File

SOURCE=.\Scalebar.h
# End Source File
# Begin Source File

SOURCE=.\Scamp.h
# End Source File
# Begin Source File

SOURCE=.\Scontrol.h
# End Source File
# Begin Source File

SOURCE=.\Sdetail.h
# End Source File
# Begin Source File

SOURCE=.\Selects.h
# End Source File
# Begin Source File

SOURCE=.\service.h
# End Source File
# Begin Source File

SOURCE=.\session.h
# End Source File
# Begin Source File

SOURCE=.\Sgame.h
# End Source File
# Begin Source File

SOURCE=.\Sgrdclms.h
# End Source File
# Begin Source File

SOURCE=.\Smkdlg.h
# End Source File
# Begin Source File

SOURCE=.\Sqdnlb.h
# End Source File
# Begin Source File

SOURCE=.\Sqdnlbut.h
# End Source File
# Begin Source File

SOURCE=.\Sqdnlist.h
# End Source File
# Begin Source File

SOURCE=.\Squads.h
# End Source File
# Begin Source File

SOURCE=.\Squick1.h
# End Source File
# Begin Source File

SOURCE=.\Squick2.h
# End Source File
# Begin Source File

SOURCE=.\Squickp.h
# End Source File
# Begin Source File

SOURCE=.\Squickun.h
# End Source File
# Begin Source File

SOURCE=.\Sqview.h
# End Source File
# Begin Source File

SOURCE=.\Ssound.h
# End Source File
# Begin Source File

SOURCE=.\Stitle.h
# End Source File
# Begin Source File

SOURCE=.\Strike.h
# End Source File
# Begin Source File

SOURCE=.\Supply.h
# End Source File
# Begin Source File

SOURCE=.\Sviewer.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Sagmove.h
# End Source File
# Begin Source File

SOURCE=..\H\Sairclms.h
# End Source File
# Begin Source File

SOURCE=..\H\Sample.h
# End Source File
# Begin Source File

SOURCE=..\H\Savegame.h
# End Source File
# Begin Source File

SOURCE=..\H\Saveprof.h
# End Source File
# Begin Source File

SOURCE=..\H\Saverep.h
# End Source File
# Begin Source File

SOURCE=..\H\Scalebar.h
# End Source File
# Begin Source File

SOURCE=..\H\Scamp.h
# End Source File
# Begin Source File

SOURCE=..\H\Scontrol.h
# End Source File
# Begin Source File

SOURCE=..\H\Screenxy.h
# End Source File
# Begin Source File

SOURCE=..\H\Sdetail.h
# End Source File
# Begin Source File

SOURCE=..\H\Selects.h
# End Source File
# Begin Source File

SOURCE=..\H\Seltrg.h
# End Source File
# Begin Source File

SOURCE=.\Seltrg.h
# End Source File
# Begin Source File

SOURCE=..\H\Service.h
# End Source File
# Begin Source File

SOURCE=..\H\Session.h
# End Source File
# Begin Source File

SOURCE=..\H\Sflight.h
# End Source File
# Begin Source File

SOURCE=.\Sflight.h
# End Source File
# Begin Source File

SOURCE=..\H\Sfman.h
# End Source File
# Begin Source File

SOURCE=..\H\Sg2combo.h
# End Source File
# Begin Source File

SOURCE=..\H\Sgame.h
# End Source File
# Begin Source File

SOURCE=..\H\Sgrdclms.h
# End Source File
# Begin Source File

SOURCE=..\H\Shapenam.h
# End Source File
# Begin Source File

SOURCE=..\H\Shapes.h
# End Source File
# Begin Source File

SOURCE=..\H\Shpbld.h
# End Source File
# Begin Source File

SOURCE=..\H\Shpinstr.h
# End Source File
# Begin Source File

SOURCE=..\H\Shpweap.h
# End Source File
# Begin Source File

SOURCE=..\H\Sidesel.h
# End Source File
# Begin Source File

SOURCE=.\Sidesel.h
# End Source File
# Begin Source File

SOURCE=..\H\Sky.h
# End Source File
# Begin Source File

SOURCE=..\H\Smack.h
# End Source File
# Begin Source File

SOURCE=..\H\Smission.h
# End Source File
# Begin Source File

SOURCE=.\Smission.h
# End Source File
# Begin Source File

SOURCE=..\H\Smkdlg.h
# End Source File
# Begin Source File

SOURCE=..\H\Smktrls.h
# End Source File
# Begin Source File

SOURCE=..\H\Sndfonts.h
# End Source File
# Begin Source File

SOURCE=..\H\Sound.h
# End Source File
# Begin Source File

SOURCE=..\H\Speed.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqddiary.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqdnlb.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqdnlbut.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqdnlist.h
# End Source File
# Begin Source File

SOURCE=..\H\Squaddtl.h
# End Source File
# Begin Source File

SOURCE=.\Squaddtl.h
# End Source File
# Begin Source File

SOURCE=..\H\Squads.h
# End Source File
# Begin Source File

SOURCE=..\h\SQUICK1.H
# End Source File
# Begin Source File

SOURCE=..\H\Squick2.h
# End Source File
# Begin Source File

SOURCE=..\H\Squickp.h
# End Source File
# Begin Source File

SOURCE=..\H\Squickun.h
# End Source File
# Begin Source File

SOURCE=..\H\Sqview.h
# End Source File
# Begin Source File

SOURCE=..\..\Src
# End Source File
# Begin Source File

SOURCE=..\H\Sreplay.h
# End Source File
# Begin Source File

SOURCE=.\Sreplay.h
# End Source File
# Begin Source File

SOURCE=..\H\Ssound.h
# End Source File
# Begin Source File

SOURCE=..\H\Stack.h
# End Source File
# Begin Source File

SOURCE=..\H\Statbar.h
# End Source File
# Begin Source File

SOURCE=.\Statbar.h
# End Source File
# Begin Source File

SOURCE=..\H\Stdafx.h
# End Source File
# Begin Source File

SOURCE=..\H\Stitle.h
# End Source File
# Begin Source File

SOURCE=.\Stores.h
# End Source File
# Begin Source File

SOURCE=..\H\Strike.h
# End Source File
# Begin Source File

SOURCE=..\H\Stub.m
# End Source File
# Begin Source File

SOURCE=..\H\Stub3d.h
# End Source File
# Begin Source File

SOURCE=..\H\Supply.h
# End Source File
# Begin Source File

SOURCE=..\H\Sviewer.h
# End Source File
# Begin Source File

SOURCE=..\H\Sw_error.hpp
# End Source File
# Begin Source File

SOURCE=..\H\Sw_force.h
# End Source File
# Begin Source File

SOURCE=..\H\Sw_guid.hpp
# End Source File
# Begin Source File

SOURCE=..\H\sysbox.h
# End Source File
# End Group
# Begin Group "T"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Targets.h
# End Source File
# Begin Source File

SOURCE=..\H\Task.h
# End Source File
# Begin Source File

SOURCE=.\Task.h
# End Source File
# Begin Source File

SOURCE=..\H\Tasktabs.h
# End Source File
# Begin Source File

SOURCE=.\Tasktabs.h
# End Source File
# Begin Source File

SOURCE=..\H\Teletype.h
# End Source File
# Begin Source File

SOURCE=.\Teletype.h
# End Source File
# Begin Source File

SOURCE=..\H\Text.h
# End Source File
# Begin Source File

SOURCE=..\H\Textfixd.h
# End Source File
# Begin Source File

SOURCE=..\H\Textref.h
# End Source File
# Begin Source File

SOURCE=..\H\Textrefl.h
# End Source File
# Begin Source File

SOURCE=..\H\Tga.h
# End Source File
# Begin Source File

SOURCE=..\H\thumnail.h
# End Source File
# Begin Source File

SOURCE=..\H\Tilemake.h
# End Source File
# Begin Source File

SOURCE=..\H\Title.h
# End Source File
# Begin Source File

SOURCE=.\Title.h
# End Source File
# Begin Source File

SOURCE=..\H\Titlebar.h
# End Source File
# Begin Source File

SOURCE=.\Titlebar.h
# End Source File
# Begin Source File

SOURCE=..\H\Tlbrcntl.h
# End Source File
# Begin Source File

SOURCE=.\Tlbrcntl.h
# End Source File
# Begin Source File

SOURCE=..\H\Tooff.h
# End Source File
# Begin Source File

SOURCE=.\Tooff.h
# End Source File
# Begin Source File

SOURCE=..\H\Totesect.h
# End Source File
# Begin Source File

SOURCE=.\Totesect.h
# End Source File
# Begin Source File

SOURCE=..\H\Totetop.h
# End Source File
# Begin Source File

SOURCE=.\Totetop.h
# End Source File
# Begin Source File

SOURCE=..\H\Traffic.h
# End Source File
# Begin Source File

SOURCE=.\Traffic.h
# End Source File
# Begin Source File

SOURCE=..\H\Transite.h
# End Source File
# Begin Source File

SOURCE=..\H\Transxtr.h
# End Source File
# Begin Source File

SOURCE=..\H\Tstatic.h
# End Source File
# Begin Source File

SOURCE=..\H\Twodpref.h
# End Source File
# Begin Source File

SOURCE=.\Twodpref.h
# End Source File
# End Group
# Begin Group "U"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Ui.h
# End Source File
# Begin Source File

SOURCE=..\H\Uiicons.h
# End Source File
# Begin Source File

SOURCE=..\H\Uniqueid.h
# End Source File
# Begin Source File

SOURCE=..\H\Userinst.h
# End Source File
# Begin Source File

SOURCE=.\Userinst.h
# End Source File
# End Group
# Begin Group "V"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Variants.h
# End Source File
# Begin Source File

SOURCE=.\Variants.h
# End Source File
# Begin Source File

SOURCE=..\H\Vector.h
# End Source File
# Begin Source File

SOURCE=..\H\Vertex.h
# End Source File
# Begin Source File

SOURCE=..\H\Viewsel.h
# End Source File
# Begin Source File

SOURCE=..\H\Visitors.h
# End Source File
# Begin Source File

SOURCE=.\Visitors.h
# End Source File
# Begin Source File

SOURCE=..\H\Volscale.h
# End Source File
# Begin Source File

SOURCE=..\H\Vwqlist.h
# End Source File
# Begin Source File

SOURCE=.\Vwqlist.h
# End Source File
# End Group
# Begin Group "W"

# PROP Default_Filter ""
# Begin Group "Wstub"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Waveins.h
# End Source File
# Begin Source File

SOURCE=.\Weapons.h
# End Source File
# Begin Source File

SOURCE=.\Weather.h
# End Source File
# Begin Source File

SOURCE=.\WPaaa.h
# End Source File
# Begin Source File

SOURCE=.\WPAir.h
# End Source File
# Begin Source File

SOURCE=.\Wpdetail.h
# End Source File
# Begin Source File

SOURCE=.\WPGround.h
# End Source File
# Begin Source File

SOURCE=.\WPShare.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\H\Wail.h
# End Source File
# Begin Source File

SOURCE=..\H\Wave.h
# End Source File
# Begin Source File

SOURCE=..\H\Waveins.h
# End Source File
# Begin Source File

SOURCE=..\H\WaveTabs.h
# End Source File
# Begin Source File

SOURCE=..\H\Weapons.h
# End Source File
# Begin Source File

SOURCE=..\H\Weappak.h
# End Source File
# Begin Source File

SOURCE=..\H\Weather.h
# End Source File
# Begin Source File

SOURCE=..\H\Win3d.h
# End Source File
# Begin Source File

SOURCE=..\H\Winfile.h
# End Source File
# Begin Source File

SOURCE=..\H\Winmain.h
# End Source File
# Begin Source File

SOURCE=..\H\Winmove.h
# End Source File
# Begin Source File

SOURCE=..\H\World.h
# End Source File
# Begin Source File

SOURCE=..\H\Worldinc.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpaaa.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpair.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpbut.h
# End Source File
# Begin Source File

SOURCE=.\WPBut.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpdetail.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpdialog.h
# End Source File
# Begin Source File

SOURCE=.\Wpdialog.h
# End Source File
# Begin Source File

SOURCE=..\H\Wpground.h
# End Source File
# Begin Source File

SOURCE=..\H\wpshare.h
# End Source File
# End Group
# Begin Group "X"

# PROP Default_Filter ""
# End Group
# Begin Group "Y"

# PROP Default_Filter ""
# End Group
# Begin Group "Z"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Zoomlevl.h
# End Source File
# Begin Source File

SOURCE=.\Zoomlevl.h
# End Source File
# End Group
# Begin Group "__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\_3d.h
# End Source File
# Begin Source File

SOURCE=..\H\_ai.h
# End Source File
# Begin Source File

SOURCE=..\H\_airc.h
# End Source File
# Begin Source File

SOURCE=..\H\_bfie.h
# End Source File
# Begin Source File

SOURCE=..\H\_comm.h
# End Source File
# Begin Source File

SOURCE=..\H\_file.h
# End Source File
# Begin Source File

SOURCE=..\H\_gene.h
# End Source File
# Begin Source File

SOURCE=..\H\_grap.h
# End Source File
# Begin Source File

SOURCE=..\H\_hard.h
# End Source File
# Begin Source File

SOURCE=..\H\_inpu.h
# End Source File
# Begin Source File

SOURCE=..\H\_math.h
# End Source File
# Begin Source File

SOURCE=..\H\_mfc.h
# End Source File
# Begin Source File

SOURCE=..\H\_miss.h
# End Source File
# Begin Source File

SOURCE=..\H\_mode.h
# End Source File
# Begin Source File

SOURCE=..\H\_move.h
# End Source File
# Begin Source File

SOURCE=..\H\_text.h
# End Source File
# End Group
# End Group
# Begin Group "Generated Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\H\Addr00.g
# End Source File
# Begin Source File

SOURCE=..\H\Bfrefs.g
# End Source File
# Begin Source File

SOURCE=..\H\Clouds.g
# End Source File
# Begin Source File

SOURCE=..\H\Const00.g
# End Source File
# Begin Source File

SOURCE=..\H\Deathnum.g
# End Source File
# Begin Source File

SOURCE=..\H\F_battle.g
# End Source File
# Begin Source File

SOURCE=..\H\F_common.g
# End Source File
# Begin Source File

SOURCE=..\H\F_grafix.g
# End Source File
# Begin Source File

SOURCE=..\H\F_sounds.g
# End Source File
# Begin Source File

SOURCE=..\H\Files.g
# End Source File
# Begin Source File

SOURCE=..\H\Iconlist.g
# End Source File
# Begin Source File

SOURCE=..\H\Iconnum.g
# End Source File
# Begin Source File

SOURCE=..\H\iconnum2.g
# End Source File
# Begin Source File

SOURCE=..\H\Imagemap.g
# End Source File
# Begin Source File

SOURCE=..\H\Offs00.g
# End Source File
# Begin Source File

SOURCE=..\H\Radio.g
# End Source File
# Begin Source File

SOURCE=..\H\Radioxtr.g
# End Source File
# Begin Source File

SOURCE=..\H\Shapenum.g
# End Source File
# Begin Source File

SOURCE=..\H\smktrl.g
# End Source File
# Begin Source File

SOURCE=..\H\Textenum.g
# End Source File
# Begin Source File

SOURCE=..\H\Uidvals.g
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Group "Source"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BOB.rc

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Res\Mig.rc2
# End Source File
# Begin Source File

SOURCE=.\Release.rc

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# End Group
# Begin Group "BMP (res)"

# PROP Default_Filter ".bmp"
# Begin Source File

SOURCE=.\Arrow.cur
# End Source File
# Begin Source File

SOURCE=.\Arrowcop.cur
# End Source File
# Begin Source File

SOURCE=.\Res\grip.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\Mig.ico
# End Source File
# Begin Source File

SOURCE=.\res\MIGDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Nodrop.cur
# End Source File
# End Group
# Begin Source File

SOURCE=.\Res\icon1.ico
# End Source File
# Begin Source File

SOURCE=..\H\iconlst2.g
# End Source File
# Begin Source File

SOURCE=.\Resource.hm
# End Source File
# End Group
# Begin Group "Help Files"

# PROP Default_Filter ""
# Begin Group "Source "

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\BOB.cnt

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\BOB.hpj

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

USERDEP__BOB_H="$(ProjDir)\hlp\AfxCore.rtf"	
# Begin Custom Build - Making help file...
OutDir=\BOB\debug\ttexe
ProjDir=.
TargetName=bob
InputPath=.\hlp\BOB.hpj

"$(OutDir)\$(TargetName).hlp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd 
	echo call $(ProjDir)\makehelp.bat 
	call $(ProjDir)\makehelp.bat 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MakeHelp.bat

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "RTF"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\hlp\AfxCore.rtf

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\AfxOleCl.rtf

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "BMP (help)"

# PROP Default_Filter ".bmp"
# Begin Source File

SOURCE=.\hlp\AppExit.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Bullet.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw2.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurArw4.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\CurHelp.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditCopy.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditCut.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditPast.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\EditUndo.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileNew.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileOpen.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FilePrnt.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\FileSave.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\HlpSBar.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\HlpTBar.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecFirst.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecLast.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecNext.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\RecPrev.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Scmax.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\ScMenu.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\hlp\Scmin.bmp

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\BOB.reg

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Utilities"

# PROP Default_Filter ""
# Begin Group "Add all targets as dependencies of fmake.dep"

# PROP Default_Filter ".dep"
# Begin Source File

SOURCE=..\..\debug\obj\fmake.dep

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

USERDEP__FMAKE="\BOB\game\keyboard\keyb3d.bin"	"\BOB\src\bfieldsm.fil"	"\BOB\src\mycmds\rowanu.flg"	
# Begin Custom Build - End of utilities
InputPath=..\..\debug\obj\fmake.dep

"..\h\000tools.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd.>..\h\000tools.h

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

USERDEP__FMAKE="\BOB\game\keyboard\keyb3d.bin"	"\BOB\src\bfieldsm.fil"	"\BOB\src\mycmds\rowanu.flg"	
# Begin Custom Build - End of utilities
InputPath=..\..\debug\obj\fmake.dep

"..\h\000tools.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd.>..\h\000tools.h

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

USERDEP__FMAKE="\BOB\game\keyboard\keyb3d.bin"	"\BOB\src\bfieldsm.fil"	"\BOB\src\mycmds\rowanu.flg"	
# Begin Custom Build - End of utilities
InputPath=..\..\debug\obj\fmake.dep

"..\h\000tools.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	cd.>..\h\000tools.h

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# End Group
# Begin Group "Utility programs generate 1 target"

# PROP Default_Filter ".dep"
# Begin Source File

SOURCE=..\Bfields\Battle.src

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

USERDEP__BATTL="..\bfields\battle.inc"	"..\bfields\globrefs.txt"	"..\bfields\initial.typ"	"..\bfields\mainwld.bfi"	"\BOB\debug\exe\makebf.exe"	"..\bfields\paths.bfi"	"..\bfields\scramble.inc"	"..\h\uniqueid.h"	
# Begin Custom Build - Compiling battlefields
InputPath=..\Bfields\Battle.src

"\BOB\src\bfieldsm.fil" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist \BOB\src\bfieldsm.fil del \BOB\src\bfieldsm.fil 
	if exist \BOB\src\bferr.txt del \BOB\src\bferr.txt 
	start /w /m ..\bfields 
	echo :wait >wait.bat 
	echo delay 1>>wait.bat 
	echo if exist \BOB\src\bferr.txt goto end>>wait.bat 
	echo if not exist \BOB\src\bfieldsm.fil goto wait>>wait.bat 
	echo :end>>wait.bat 
	wait 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

USERDEP__BATTL="..\bfields\battle.inc"	"..\bfields\globrefs.txt"	"..\bfields\initial.typ"	"..\bfields\mainwld.bfi"	"\BOB\debug\exe\makebf.exe"	"..\bfields\paths.bfi"	"..\bfields\scramble.inc"	"..\h\uniqueid.h"	
# Begin Custom Build - Compiling battlefields
InputPath=..\Bfields\Battle.src

"\BOB\src\bfieldsm.fil" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	if exist \BOB\src\bfieldsm.fil del \BOB\src\bfieldsm.fil 
	if exist \BOB\src\bferr.txt del \BOB\src\bferr.txt 
	start /w /m ..\bfields 
	echo :wait >wait.bat 
	echo delay 1>>wait.bat 
	echo if exist \BOB\src\bferr.txt goto end>>wait.bat 
	echo if not exist \BOB\src\bfieldsm.fil goto wait>>wait.bat 
	echo :end>>wait.bat 
	wait 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Master.fil

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

USERDEP__MASTE="..\bfieldsa.fil"	"..\roots.dir"	"..\"	"\BOB\src\bfieldsm.fil"	
# Begin Custom Build - Making file-lists
IntDir=\BOB\debug\obj
InputPath=..\Master.fil

"$(IntDir)\fmake.dep" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m ..\fmake2 
	echo.>$(IntDir)\fmake.dep 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

USERDEP__MASTE="..\bfieldsa.fil"	"..\roots.dir"	"..\"	"\BOB\src\bfieldsm.fil"	
# Begin Custom Build - Making file-lists
IntDir=\BOB\debug\ttobj
InputPath=..\Master.fil

"$(IntDir)\fmake.dep" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m ..\fmake2 
	echo.>$(IntDir)\fmake.dep 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

USERDEP__MASTE="..\bfieldsa.fil"	"..\roots.dir"	"..\"	"\BOB\src\bfieldsm.fil"	
# Begin Custom Build - Making file-lists
IntDir=\BOB\demodeb\obj
InputPath=..\Master.fil

"$(IntDir)\fmake.dep" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m ..\fmake2 
	echo.>$(IntDir)\fmake.dep 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\Mycmds\Rowanx.dsm

!IF  "$(CFG)" == "BOB - Win32 Release"

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# Begin Custom Build
InputDir=\Bob\Src\Mycmds
InputPath=..\Mycmds\Rowanx.dsm

"$(InputDir)\rowanu.flg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End                                                                                        Function>>$(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End                                                                                        Function>$(InputDir)\rowanu.flg 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# Begin Custom Build
InputDir=\Bob\Src\Mycmds
InputPath=..\Mycmds\Rowanx.dsm

"$(InputDir)\rowanu.dsm" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End                                                                                        Function>>$(InputDir)\rowanu.dsm 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# Begin Custom Build
InputDir=\Bob\Src\Mycmds
InputPath=..\Mycmds\Rowanx.dsm

"$(InputDir)\rowanu.flg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy $(InputPath) $(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End                                                                                        Function>>$(InputDir)\rowanu.dsm 
	echo Function myname():myname="%initials%":End                                                                                        Function>$(InputDir)\rowanu.flg 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\Debug\exe\Ukeylist.exe

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# Begin Custom Build - making keyboard table
InputPath=..\..\Debug\exe\Ukeylist.exe

"\BOB\game\keyboard\keyb3d.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m $(InputPath) \BOB\game\keyboard\keyb3d.bin

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# Begin Custom Build - making keyboard table
InputPath=..\..\Debug\exe\Ukeylist.exe

"\BOB\game\keyboard\keyb3d.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m $(InputPath) \BOB\game\keyboard\keyb3d.bin

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# Begin Custom Build - making keyboard table
InputPath=..\..\Debug\exe\Ukeylist.exe

"\BOB\game\keyboard\keyb3d.bin" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	start /w /m $(InputPath) \BOB\game\keyboard\keyb3d.bin

# End Custom Build

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "associated files"

# PROP Default_Filter ""
# Begin Source File

SOURCE="..\bfields\battle.inc"
# End Source File
# Begin Source File

SOURCE=..\bfieldsA.fil
# End Source File
# Begin Source File

SOURCE=..\bfieldsM.fil
# End Source File
# Begin Source File

SOURCE="..\bfields\globrefs.txt"
# End Source File
# Begin Source File

SOURCE=..\Bfields\Initial.typ
# End Source File
# Begin Source File

SOURCE=..\..\game\Keyboard\keyb3d.bin
# End Source File
# Begin Source File

SOURCE=..\Bfields\Mainmig.bfi
# End Source File
# Begin Source File

SOURCE=..\Bfields\Mainwld.bfi
# End Source File
# Begin Source File

SOURCE=..\Mycmds\Makeall.bat
# End Source File
# Begin Source File

SOURCE=..\Bfields\Makebf.cxx

!IF  "$(CFG)" == "BOB - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Profile"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoDebug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 DemoRelease"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Preview1Day"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "BOB - Win32 Release No Debug"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\debug\exe\makebf.exe
# End Source File
# Begin Source File

SOURCE=..\Bfields\Paths.bfi
# End Source File
# Begin Source File

SOURCE=..\Roots.dir
# End Source File
# Begin Source File

SOURCE=..\Mycmds\Rowanu.dsm
# End Source File
# Begin Source File

SOURCE=..\Mycmds\rowanu.flg
# End Source File
# Begin Source File

SOURCE=..\Bfields\Scramble.inc
# End Source File
# End Group
# End Group
# Begin Group "Removed stuff"

# PROP Default_Filter ""
# End Group
# Begin Source File

SOURCE=..\..\backup\history.lst
# End Source File
# End Target
# End Project
# Section BOB : {461A1FE3-B81B-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:redtbt.h
# 	2:16:DefaultSinkClass:CREdtBt
# End Section
# Section BOB : {C42BAC3D-CA3C-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rstatic.h
# 	2:16:DefaultSinkClass:CRStatic
# End Section
# Section BOB : {4A1E1986-8B31-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rtabs.h
# 	2:16:DefaultSinkClass:CRTabs
# End Section
# Section BOB : {C3270E66-6D6B-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rspinbut.h
# 	2:16:DefaultSinkClass:CRSpinBut
# End Section
# Section BOB : {737CB0C7-B42B-11D1-A1F0-444553540000}
# 	2:5:Class:CRCombo
# 	2:10:HeaderFile:rcombo.h
# 	2:8:ImplFile:rcombo.cpp
# End Section
# Section BOB : {78918646-A917-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rbutton.h
# 	2:16:DefaultSinkClass:CRButton
# End Section
# Section BOB : {7EBC74E3-0F3C-11D2-A1F0-0080C8582DE4}
# 	2:5:Class:CRRadio
# 	2:10:HeaderFile:rradio.h
# 	2:8:ImplFile:rradio.cpp
# End Section
# Section BOB : {461A1FE1-B81B-11D1-A1F0-444553540000}
# 	2:5:Class:CREdtBt
# 	2:10:HeaderFile:redtbt.h
# 	2:8:ImplFile:redtbt.cpp
# End Section
# Section BOB : {008F23E7-9243-11D1-A1F0-444553540000}
# 	2:5:Class:CRTitle
# 	2:10:HeaderFile:rtitle.h
# 	2:8:ImplFile:rtitle.cpp
# End Section
# Section BOB : {C42BAC3B-CA3C-11D1-A1F0-444553540000}
# 	2:5:Class:CRStatic
# 	2:10:HeaderFile:rstatic.h
# 	2:8:ImplFile:rstatic.cpp
# End Section
# Section BOB : {4A1E1984-8B31-11D1-A1F0-444553540000}
# 	2:5:Class:CRTabs
# 	2:10:HeaderFile:rtabs.h
# 	2:8:ImplFile:rtabs.cpp
# End Section
# Section BOB : {505AEE46-6A66-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rscrlbar.h
# 	2:16:DefaultSinkClass:CRScrlBar
# End Section
# Section BOB : {499E2BE6-AC32-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:redit.h
# 	2:16:DefaultSinkClass:CREdit
# End Section
# Section BOB : {78918644-A917-11D1-A1F0-444553540000}
# 	2:5:Class:CRButton
# 	2:10:HeaderFile:rbutton.h
# 	2:8:ImplFile:rbutton.cpp
# End Section
# Section BOB : {C3270E64-6D6B-11D1-A1F0-444553540000}
# 	2:5:Class:CRSpinBut
# 	2:10:HeaderFile:rspinbut.h
# 	2:8:ImplFile:rspinbut.cpp
# End Section
# Section BOB : {48814009-65AE-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rlistbox.h
# 	2:16:DefaultSinkClass:CRListBox
# End Section
# Section BOB : {90B5EDA6-666F-11D1-A1F0-444553540000}
# 	2:5:Class:CRListBox
# 	2:10:HeaderFile:rlistbox.h
# 	2:8:ImplFile:rlistbox.cpp
# End Section
# Section BOB : {737CB0C9-B42B-11D1-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rcombo.h
# 	2:16:DefaultSinkClass:CRCombo
# End Section
# Section BOB : {5363BA22-D90A-11D1-A1F0-0080C8582DE4}
# 	2:21:DefaultSinkHeaderFile:rradio.h
# 	2:16:DefaultSinkClass:CRRadio
# End Section
# Section BOB : {499E2BE4-AC32-11D1-A1F0-444553540000}
# 	2:5:Class:CREdit
# 	2:10:HeaderFile:redit.h
# 	2:8:ImplFile:redit.cpp
# End Section
# Section BOB : {505AEE44-6A66-11D1-A1F0-444553540000}
# 	2:5:Class:CRScrlBar
# 	2:10:HeaderFile:rscrlbar.h
# 	2:8:ImplFile:rscrlbar.cpp
# End Section
