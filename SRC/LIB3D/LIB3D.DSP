# Microsoft Developer Studio Project File - Name="Lib3D" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Lib3D - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Lib3D.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Lib3D - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\bob\release\exe"
# PROP Intermediate_Dir "\bob\release\lib3d"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIB3D_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MT /W3 /GX /O2 /Ob2 /I "\bob\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIB3D_EXPORTS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 winmm.lib dxguid.lib ddraw.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /base:"0x10000000" /dll /debug /machine:I386 /libpath:"\bob\src\lib"

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\bob\Debug\exe"
# PROP Intermediate_Dir "\bob\Debug\Lib3D"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIB3D_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /Zp1 /MTd /W3 /Gm /GX /Zi /O2 /Ob2 /I "\bob\src\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIB3D_EXPORTS" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib kernel32.lib user32.lib gdi32.lib winspool.lib dxguid.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ddraw.lib /nologo /base:"0x10000000" /dll /map /debug /machine:I386 /pdbtype:sept /libpath:"\bob\src\lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy .\cardbase.txt ..\..\game\cardbase.rc
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "Lib3D - Win32 Release"
# Name "Lib3D - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\alloc.c

!IF  "$(CFG)" == "Lib3D - Win32 Release"

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

# ADD CPP /Gm- /O2 /Ob2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\cardbase.txt

!IF  "$(CFG)" == "Lib3D - Win32 Release"

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\flagsw.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\Getdxver.cpp

!IF  "$(CFG)" == "Lib3D - Win32 Release"

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

# ADD CPP /Gm- /O2 /Ob2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\l3dguid.cpp

!IF  "$(CFG)" == "Lib3D - Win32 Release"

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

# ADD CPP /Gm- /O2 /Ob2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Lib3D.cpp

!IF  "$(CFG)" == "Lib3D - Win32 Release"

# ADD CPP /Z7 /Ob2

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

# ADD CPP /Gm- /O2 /Ob2

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\3d\Monotxt.cpp

!IF  "$(CFG)" == "Lib3D - Win32 Release"

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

# ADD CPP /O2
# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\radix.c

!IF  "$(CFG)" == "Lib3D - Win32 Release"

!ELSEIF  "$(CFG)" == "Lib3D - Win32 Debug"

# ADD CPP /Gm- /O2 /Ob2

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Lib3D.h
# End Source File
# Begin Source File

SOURCE=.\matstak.h
# End Source File
# Begin Source File

SOURCE=.\polyvert.h
# End Source File
# Begin Source File

SOURCE=.\radix.h
# End Source File
# End Group
# End Target
# End Project
