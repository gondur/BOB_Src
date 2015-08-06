/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

// RButtonPpg.cpp : Implementation of the CRButtonPropPage property page class.

#include "stdafx.h"
#include "RButton.h"
#include "RButtonP.h"
#include "propdial.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#undef THIS_FILE
#ifndef THIS_FILE_DEFINED
static char THIS_FILE[] = __FILE__;
#endif
#endif

ComboTexts Font_Combo_Texts(PROJDIR "\\src\\h\\fontlist.h",50);
ComboTexts Icon_Combo_Texts(PROJDIR "\\src\\h\\iconnum.g",500);


IMPLEMENT_DYNCREATE(CRButtonPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CRButtonPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CRButtonPropPage)
	ON_CBN_SELCHANGE(IDC_COMBOMODE, OnSelchangeCombo2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CRButtonPropPage, "RBUTTON.RButtonPropPage.1",
	0x78918647, 0xa917, 0x11d6, 0xa1, 0xf0, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage::CRButtonPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CRButtonPropPage

BOOL CRButtonPropPage::CRButtonPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_RBUTTON_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage::CRButtonPropPage - Constructor

CRButtonPropPage::CRButtonPropPage() :
	COlePropertyPage(IDD, IDS_RBUTTON_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CRButtonPropPage)
	m_bMovesParent = FALSE;
	m_bCloseButton = FALSE;
	m_bTickButton = FALSE;
	m_bToggle = FALSE;
	m_bShowShadow = FALSE;
	m_NormalFileNumString = _T("");
	m_PressedFileNumString = _T("");
	m_hintStringID = _T("");
	m_FontNum = -1;
	m_PressedFileNum = -1;
	m_NormalFileNum = -1;
	m_left = FALSE;
	m_right = FALSE;
	m_cap = FALSE;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage::DoDataExchange - Moves data between page and properties

void CRButtonPropPage::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_COMBOFONT, m_FontNumCtrl);
	DDX_Control(pDX, IDC_COMBOFILE, m_FileList);
	if (!pDX->m_bSaveAndValidate)
	{
		Font_Combo_Texts.SetComboList(&m_FontNumCtrl);
		Icon_Combo_Texts.SetComboList(&m_FileList);
	}
	//{{AFX_DATA_MAP(CRButtonPropPage)
	DDX_Control(pDX, IDC_COMBOFILE, m_FileList);
	DDX_Control(pDX, IDC_COMBOMODE, m_PressedChanged);
	DDX_Control(pDX, IDC_COMBOFONT, m_FontNumCtrl);
	DDP_Check(pDX, IDC_MOVES_PARENT, m_bMovesParent, _T("MovesParent") );
	DDX_Check(pDX, IDC_MOVES_PARENT, m_bMovesParent);
	DDP_Check(pDX, IDC_CLOSE, m_bCloseButton, _T("CloseButton") );
	DDX_Check(pDX, IDC_CLOSE, m_bCloseButton);
	DDP_Check(pDX, IDC_TICK, m_bTickButton, _T("TickButton") );
	DDX_Check(pDX, IDC_TICK, m_bTickButton);
	DDP_Check(pDX, IDC_DROP_SHADOWS, m_bShowShadow, _T("ShowShadow") );
	DDX_Check(pDX, IDC_DROP_SHADOWS, m_bShowShadow);
	DDP_Text(pDX, IDC_PRESSED_PICTURE_FILE_NUM2, m_hintStringID, _T("HintStringID") );
	DDX_Text(pDX, IDC_PRESSED_PICTURE_FILE_NUM2, m_hintStringID);
	DDP_CBIndex(pDX, IDC_COMBOFONT, m_FontNum, _T("FontNum") );
	DDX_CBIndex(pDX, IDC_COMBOFONT, m_FontNum);
	DDP_CBIndex(pDX, IDC_COMBOMODE, m_PressedFileNum, _T("PressedFileNum") );
	DDX_CBIndex(pDX, IDC_COMBOMODE, m_PressedFileNum);
	DDP_CBIndex(pDX, IDC_COMBOFILE, m_NormalFileNum, _T("NormalFileNum") );
	DDX_CBIndex(pDX, IDC_COMBOFILE, m_NormalFileNum);
	DDP_Check(pDX, IDC_LEFT, m_left, _T("Pressed") );
	DDX_Check(pDX, IDC_LEFT, m_left);
	DDP_Check(pDX, IDC_RIGHT, m_right, _T("Disabled") );
	DDX_Check(pDX, IDC_RIGHT, m_right);
	DDP_Check(pDX, IDC_UPDATE_CAPTION, m_cap, _T("UpdateCaption") );
	DDX_Check(pDX, IDC_UPDATE_CAPTION, m_cap);
	//}}AFX_DATA_MAP
	if (!pDX->m_bSaveAndValidate)
	{
		if (m_PressedFileNum<7 || m_PressedFileNum>20)
		{
			if (m_PressedFileNum>20)
			{
				m_PressedFileNum=6;
				m_PressedChanged.SetCurSel(6);
			}
			m_FileList.ResetContent();
			m_FileList.SetCurSel(-1);
			m_FileList.SetWindowText("File name");
		}
	}
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CRButtonPropPage message handlers

void CRButtonPropPage::OnSelchangeCombo2() 
{
	// TODO: Add your control notification handler code here
	int sel=m_PressedChanged.GetCurSel();
	int prevsel=m_PressedFileNum;
	if (sel==7)
	{
		Icon_Combo_Texts.SetComboList(&m_FileList);
	}
	else
	{
		m_FileList.ResetContent();
		m_FileList.SetCurSel(-1);
		m_FileList.SetWindowText("File name");
	}

}
