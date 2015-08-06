# Microsoft Developer Studio Project File - Name="LitaCln" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=LitaCln - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Litacln.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Litacln.mak" CFG="LitaCln - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LitaCln - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "LitaCln - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "LitaCln - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f LitaCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "LitaCln.exe"
# PROP BASE Bsc_Name "LitaCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "LitaCln - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "LitaCln_"
# PROP BASE Intermediate_Dir "LitaCln_"
# PROP BASE Cmd_Line "NMAKE /f LitaCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "LitaCln.exe"
# PROP BASE Bsc_Name "LitaCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "LitaCln_"
# PROP Intermediate_Dir "LitaCln_"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "LitaCln - Win32 Release"
# Name "LitaCln - Win32 Debug"

!IF  "$(CFG)" == "LitaCln - Win32 Release"

!ELSEIF  "$(CFG)" == "LitaCln - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=..\MYCMDS\mlangcln.bat
# End Source File
# End Target
# End Project
