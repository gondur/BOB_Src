# Microsoft Developer Studio Project File - Name="lspaCln" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) External Target" 0x0106

CFG=lspaCln - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "lspacln.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "lspacln.mak" CFG="lspaCln - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "lspaCln - Win32 Release" (based on "Win32 (x86) External Target")
!MESSAGE "lspaCln - Win32 Debug" (based on "Win32 (x86) External Target")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""

!IF  "$(CFG)" == "lspaCln - Win32 Release"

# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Cmd_Line "NMAKE /f lspaCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "lspaCln.exe"
# PROP BASE Bsc_Name "lspaCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ELSEIF  "$(CFG)" == "lspaCln - Win32 Debug"

# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "lspaCln_"
# PROP BASE Intermediate_Dir "lspaCln_"
# PROP BASE Cmd_Line "NMAKE /f lspaCln.mak"
# PROP BASE Rebuild_Opt "/a"
# PROP BASE Target_File "lspaCln.exe"
# PROP BASE Bsc_Name "lspaCln.bsc"
# PROP BASE Target_Dir ""
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "lspaCln_"
# PROP Intermediate_Dir "lspaCln_"
# PROP Cmd_Line "..\mycmds\mlangcln.bat"
# PROP Rebuild_Opt ""
# PROP Target_File "cleaned.flg"
# PROP Bsc_Name ""
# PROP Target_Dir ""

!ENDIF 

# Begin Target

# Name "lspaCln - Win32 Release"
# Name "lspaCln - Win32 Debug"

!IF  "$(CFG)" == "lspaCln - Win32 Release"

!ELSEIF  "$(CFG)" == "lspaCln - Win32 Debug"

!ENDIF 

# Begin Source File

SOURCE=..\MYCMDS\mlangcln.bat
# End Source File
# End Target
# End Project
