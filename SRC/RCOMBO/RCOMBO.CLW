; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CRComboCtrl
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RCombo.h"
CDK=Y

ClassCount=3
Class1=CRComboCtrl
Class2=CRComboPropPage

ResourceCount=2
LastPage=0
Resource1=IDD_LISTBOX
Class3=CListBx
Resource2=IDD_PROPPAGE_RCOMBO

[CLS:CRComboCtrl]
Type=0
HeaderFile=RComboC.h
ImplementationFile=RComboC.cpp
Filter=W
BaseClass=COleControl
VirtualFilter=wWC
LastObject=CRComboCtrl

[CLS:CRComboPropPage]
Type=0
HeaderFile=RComboP.h
ImplementationFile=RComboP.cpp
Filter=D
BaseClass=COlePropertyPage
VirtualFilter=idWC

[DLG:IDD_PROPPAGE_RCOMBO]
Type=1
Class=CRComboPropPage
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_LISTBOX_LENGTH,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STYLECOMBO,combobox,1344339971
Control7=IDC_CHECK1,button,1342242819
Control8=IDC_COMBOFONT,combobox,1344339971

[DLG:IDD_LISTBOX]
Type=1
Class=CListBx
ControlCount=1
Control1=IDC_RLISTBOXCTRL1,{48814009-65AE-11D1-A1F0-444553540000},1342242816

[CLS:CListBx]
Type=0
HeaderFile=ListBx.h
ImplementationFile=ListBx.cpp
BaseClass=CDialog
Filter=W
LastObject=CListBx
VirtualFilter=dWC

