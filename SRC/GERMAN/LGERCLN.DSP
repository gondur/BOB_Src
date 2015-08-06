# Microsoft Developer Studio Project File - Name="lgerCln" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=lgerCln - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "lgercln.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "lgercln.mak" CFG="lgerCln - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lgerCln - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "lgerCln - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "lgerCln - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f lgerCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "lgerCln.exe"
# PROP BASE Bsc_Name "lgerCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "lgerCln - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "lgerCln_"
# PROP BASE Intermediate_Dir "lgerCln_"
# PROP BASE Cmd_Line "NMAKE /f lgerCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "lgerCln.exe"
# PROP BASE Bsc_Name "lgerCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "lgerCln_"
# PROP Intermediate_Dir "lgerCln_"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "lgerCln - Win32 Release"
# Name "lgerCln - Win32 Debug"

!IF  "$(CFG)" == "lgerCln - Win32 Release"

!ELSEIF  "$(CFG)" == "lgerCln - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=..\MYCMDS\mlangcln.bat
# End Source File
# End Target
# End Project
