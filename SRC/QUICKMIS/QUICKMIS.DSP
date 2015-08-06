# Microsoft Developer Studio Project File - Name="quickmis" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=quickmis - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "QUICKMIS.MAK".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "QUICKMIS.MAK" CFG="quickmis - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "quickmis - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "quickmis - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "quickmis - Win32 DemoDebug" (based on "Win32 (x86) Console Application")
!MESSAGE "quickmis - Win32 DemoRelease" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "quickmis - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\bob\release\exe"
# PROP Intermediate_Dir "\bob\Release\qmiss"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\h" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "STANDALONE" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# Begin Special Build Tool
TargetPath=\bob\release\exe\QUICKMIS.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=$(TargetPath) ..\..\game\bfields\quick.dat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "quickmis - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\Debug\exe"
# PROP Intermediate_Dir "..\..\Debug\utilobj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /GX /ZI /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "STANDALONE" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
TargetPath=\bob\Debug\exe\QUICKMIS.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Saving quick missions...
PostBuild_Cmds=$(TargetPath) ..\..\game\bfields\quick.dat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "quickmis - Win32 DemoDebug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "quickmis___Win32_Debug_Demo"
# PROP BASE Intermediate_Dir "quickmis___Win32_Debug_Demo"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\BOB\demodeb\qm"
# PROP Intermediate_Dir "\BOB\demodeb\qm"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /ZI /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "STANDALONE" /YX /FD /c
# ADD CPP /nologo /W3 /GX /ZI /O2 /I "..\h" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "STANDALONE" /D "BOB_DEMO_VER" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# Begin Special Build Tool
TargetPath=\BOB\demodeb\qm\QUICKMIS.exe
SOURCE="$(InputPath)"
PostBuild_Desc=Saving quick missions...
PostBuild_Cmds=$(TargetPath) ..\..\game\bfields\dquick.dat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "quickmis - Win32 DemoRelease"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "quickmis___Win32_Release_Demo"
# PROP BASE Intermediate_Dir "quickmis___Win32_Release_Demo"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\BOB\demorel\qm"
# PROP Intermediate_Dir "\BOB\demorel\qm"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /I "..\h" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "STANDALONE" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\h" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "STANDALONE" /D "BOB_DEMO_VER" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# Begin Special Build Tool
TargetPath=\BOB\demorel\qm\QUICKMIS.exe
SOURCE="$(InputPath)"
PostBuild_Cmds=$(TargetPath) ..\..\game\bfields\dquick.dat
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "quickmis - Win32 Release"
# Name "quickmis - Win32 Debug"
# Name "quickmis - Win32 DemoDebug"
# Name "quickmis - Win32 DemoRelease"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Bfields\Qmiss.cpp

!IF  "$(CFG)" == "quickmis - Win32 Release"

!ELSEIF  "$(CFG)" == "quickmis - Win32 Debug"

# ADD CPP /Gm /Zi /O2
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "quickmis - Win32 DemoDebug"

# ADD BASE CPP /Gm /Zi /O2
# SUBTRACT BASE CPP /YX
# ADD CPP /Gm /Zi /O2
# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "quickmis - Win32 DemoRelease"

!ENDIF 

# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
