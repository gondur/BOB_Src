# Microsoft Developer Studio Project File - Name="RListBox" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=RListBox - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RListBox.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RListBox.mak" CFG="RListBox - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RListBox - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RListBox - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RListBox - Win32 Unicode Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "RListBox - Win32 Unicode Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RListBox - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "\BOB\release\exe"
# PROP Intermediate_Dir "\BOB\Release\list"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "\bob\src\h" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /base:"0x10600000" /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=\BOB\release\exe
TargetPath=\BOB\release\exe\RListBox.ocx
InputPath=\BOB\release\exe\RListBox.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RListBox - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "RListBox"
# PROP BASE Intermediate_Dir "RListBox"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "\bob\Debug\exe"
# PROP Intermediate_Dir "\bob\Debug\RListBox"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /Zi /O2 /I "\bob\src\h" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /base:"0x10600000" /subsystem:windows /dll /pdb:none /debug /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=\bob\Debug\exe
TargetPath=\bob\Debug\exe\RListBox.ocx
InputPath=\bob\Debug\exe\RListBox.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RListBox - Win32 Unicode Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "RListBoxU"
# PROP BASE Intermediate_Dir "RListBoxU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "RListBoxU"
# PROP Intermediate_Dir "RListBoxU"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /base:"0x10600000" /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\RListBoxU
TargetPath=.\RListBoxU\RListBox.ocx
InputPath=.\RListBoxU\RListBox.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "RListBox - Win32 Unicode Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ReleaseU"
# PROP BASE Intermediate_Dir "ReleaseU"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseU"
# PROP Intermediate_Dir "ReleaseU"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_USRDLL" /D "_UNICODE" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x809 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /base:"0x10600000" /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\ReleaseU
TargetPath=.\ReleaseU\RListBox.ocx
InputPath=.\ReleaseU\RListBox.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "RListBox - Win32 Release"
# Name "RListBox - Win32 Debug"
# Name "RListBox - Win32 Unicode Debug"
# Name "RListBox - Win32 Unicode Release"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Mfc\Getshadw.cpp
# End Source File
# Begin Source File

SOURCE=.\LP2.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp

!IF  "$(CFG)" == "RListBox - Win32 Release"

!ELSEIF  "$(CFG)" == "RListBox - Win32 Debug"

# ADD CPP /D "NO_AFX_AUTO"

!ELSEIF  "$(CFG)" == "RListBox - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RListBox - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\RListBox.def
# End Source File
# Begin Source File

SOURCE=.\RListBox.odl
# End Source File
# Begin Source File

SOURCE=.\RListBox.rc
# End Source File
# Begin Source File

SOURCE=.\rlistbxc.cpp

!IF  "$(CFG)" == "RListBox - Win32 Release"

!ELSEIF  "$(CFG)" == "RListBox - Win32 Debug"

# ADD CPP /Od

!ELSEIF  "$(CFG)" == "RListBox - Win32 Unicode Debug"

!ELSEIF  "$(CFG)" == "RListBox - Win32 Unicode Release"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rlistbxp.cpp
# End Source File
# Begin Source File

SOURCE=.\rscrlbar.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DropTarget.h
# End Source File
# Begin Source File

SOURCE=.\Lp2.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RListBox.h
# End Source File
# Begin Source File

SOURCE=.\rlistbxc.h
# End Source File
# Begin Source File

SOURCE=.\rlistbxp.h
# End Source File
# Begin Source File

SOURCE=.\rscrlbar.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RListBoxCtl.bmp
# End Source File
# Begin Source File

SOURCE=.\Rlistbxc.bmp
# End Source File
# Begin Source File

SOURCE=.\Smap1_4.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\RListBox.lic

!IF  "$(CFG)" == "RListBox - Win32 Release"

# Begin Custom Build - Copying license file...
OutDir=\BOB\release\exe
ProjDir=.
TargetName=RListBox
InputPath=.\RListBox.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RListBox - Win32 Debug"

# Begin Custom Build - Copying license file...
OutDir=\bob\Debug\exe
ProjDir=.
TargetName=RListBox
InputPath=.\RListBox.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RListBox - Win32 Unicode Debug"

# Begin Custom Build - Copying license file...
OutDir=.\RListBoxU
ProjDir=.
TargetName=RListBox
InputPath=.\RListBox.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ELSEIF  "$(CFG)" == "RListBox - Win32 Unicode Release"

# Begin Custom Build - Copying license file...
OutDir=.\ReleaseU
ProjDir=.
TargetName=RListBox
InputPath=.\RListBox.lic

"$(OutDir)\$(TargetName).lic" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	copy "$(ProjDir)\$(TargetName).lic" "$(OutDir)"

# End Custom Build

!ENDIF 

# End Source File
# End Target
# End Project
# Section RListBox : {48814009-65AE-11d6-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rlistbox2.h
# 	2:16:DefaultSinkClass:CRListBox
# End Section
# Section RListBox : {90B5EDA6-666F-11d6-A1F0-444553540000}
# 	2:5:Class:CRListBox
# 	2:10:HeaderFile:rlistbox1.h
# 	2:8:ImplFile:rlistbox1.cpp
# End Section
# Section RListBox : {505AEE44-6A66-11d6-A1F0-444553540000}
# 	2:5:Class:CRScrlBar
# 	2:10:HeaderFile:rscrlbar.h
# 	2:8:ImplFile:rscrlbar.cpp
# End Section
# Section RListBox : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section RListBox : {505AEE46-6A66-11d6-A1F0-444553540000}
# 	2:21:DefaultSinkHeaderFile:rscrlbar.h
# 	2:16:DefaultSinkClass:CRScrlBar
# End Section
