# Microsoft Developer Studio Project File - Name="Projects" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=Projects - Win32 DemoDebug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Projects.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Projects.mak" CFG="Projects - Win32 DemoDebug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Projects - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "Projects - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE "Projects - Win32 DemoDebug" (based on "Win32 (x86) External Target")
!MESSAGE "Projects - Win32 DemoRelease" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "Projects - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f Projects.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Projects.exe"
# PROP BASE Bsc_Name "Projects.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "fixhdrs|tee \bob\release\obj\projects.dep"
# PROP Rebuild_Opt ""
# PROP Target_File "\bob\release\obj\projects.dep"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "Projects - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Cmd_Line "NMAKE /f Projects.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "Projects.exe"
# PROP BASE Bsc_Name "Projects.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Cmd_Line "fixhdrs|tee \bob\debug\obj\projects.dep"
# PROP Rebuild_Opt ""
# PROP Target_File "\bob\debug\obj\projects.dep"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "Projects - Win32 DemoDebug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Projects___Win32_DemoDebug"
# PROP BASE Intermediate_Dir "Projects___Win32_DemoDebug"
# PROP BASE Cmd_Line "fixhdrs|tee \bob\debug\obj\projects.dep"
# PROP BASE Rebuild_Opt ""
# PROP BASE Target_File "\bob\debug\obj\projects.dep"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Projects___Win32_DemoDebug"
# PROP Intermediate_Dir "Projects___Win32_DemoDebug"
# PROP Cmd_Line "copy /u \bob\debug\exe\*.ocx;*.dll \bob\demodeb\exe|tee \bob\demorel\obj\projects.dep"
# PROP Rebuild_Opt ""
# PROP Target_File "\bob\demodeb\obj\projects.dep"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "Projects - Win32 DemoRelease"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Projects___Win32_DemoRelease"
# PROP BASE Intermediate_Dir "Projects___Win32_DemoRelease"
# PROP BASE Cmd_Line "fixhdrs|tee \bob\release\obj\projects.dep"
# PROP BASE Rebuild_Opt ""
# PROP BASE Target_File "\bob\release\obj\projects.dep"
# PROP BASE Bsc_Name ""
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Projects___Win32_DemoRelease"
# PROP Intermediate_Dir "Projects___Win32_DemoRelease"
# PROP Cmd_Line "copy /u \bob\release\exe\*.ocx;*.dll \bob\demorel\exe|tee \bob\demorel\obj\projects.dep"
# PROP Rebuild_Opt ""
# PROP Target_File "\bob\demorel\obj\projects.dep"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "Projects - Win32 Release"
# Name "Projects - Win32 Debug"
# Name "Projects - Win32 DemoDebug"
# Name "Projects - Win32 DemoRelease"

!IF  "$(CFG)" == "Projects - Win32 Release"

!ELSEIF  "$(CFG)" == "Projects - Win32 Debug"

!ELSEIF  "$(CFG)" == "Projects - Win32 DemoDebug"

!ELSEIF  "$(CFG)" == "Projects - Win32 DemoRelease"

!ENDIF 

# Begin Source File

SOURCE=.\Fixhdrs.bat
# End Source File
# End Target
# End Project
