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

// ListProp2.cpp : implementation file
//

#include "stdafx.h"
#include "rlistbox.h"
#include "LP2.h"				//9character file names are not allowd
#include "propdial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
ComboTexts Icon_Combo_Texts(PROJDIR "\\src\\h\\iconnum.g",500);

/////////////////////////////////////////////////////////////////////////////
// ListProp2 dialog

IMPLEMENT_DYNCREATE(ListProp2, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(ListProp2, COlePropertyPage)
	//{{AFX_MSG_MAP(ListProp2)
	ON_EN_CHANGE(IDC_EDITCOLUMN0, OnChangeEditcolumn0)
	ON_EN_KILLFOCUS(IDC_EDITCOLUMN0, OnKillfocusEditcolumn0)
	ON_EN_UPDATE(IDC_EDITCOLUMN0, OnUpdateEditcolumn0)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

// {186D94E3-88B1-11D3-8ADB-00A0D21BD395}
IMPLEMENT_OLECREATE_EX(ListProp2, "RListBox.ListProp2",
	0x186d94e3, 0x88b1, 0x11d3, 0x8a, 0xdb, 0x0, 0xa0, 0xd2, 0x1b, 0xd3, 0x95)


/////////////////////////////////////////////////////////////////////////////
// ListProp2::ListProp2Factory::UpdateRegistry -
// Adds or removes system registry entries for ListProp2

BOOL ListProp2::ListProp2Factory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Define string resource for page type; replace '0' below with ID.

	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_PPG2_CAPTION);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// ListProp2::ListProp2 - Constructor

// TODO: Define string resource for page caption; replace '0' below with ID.

ListProp2::ListProp2() :
	COlePropertyPage(IDD, IDS_PPG2_CAPTION)
{
	//{{AFX_DATA_INIT(ListProp2)
	m_A0 = -1;
	m_A1 = -1;
	m_A2 = -1;
	m_A3 = -1;
	m_A4 = -1;
	m_A5 = -1;
	m_A6 = -1;
	m_A7 = -1;
	m_A8 = -1;
	m_C1 = -1;
	m_C2 = -1;
	m_C3 = -1;
	m_C4 = -1;
	m_C5 = -1;
	m_C6 = -1;
	m_C7 = -1;
	m_C8 = -1;
	m_I0 = -1;
	m_C0 = 0;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// ListProp2::DoDataExchange - Moves data between page and properties

void ListProp2::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_ICON0, m_Icon0);
	DDX_Control(pDX, IDC_ICON1, m_Icon1);
	DDX_Control(pDX, IDC_ICON2, m_Icon2);
	DDX_Control(pDX, IDC_ICON3, m_Icon3);
	DDX_Control(pDX, IDC_ICON4, m_Icon4);
	DDX_Control(pDX, IDC_ICON5, m_Icon5);
	DDX_Control(pDX, IDC_ICON6, m_Icon6);
	DDX_Control(pDX, IDC_ICON7, m_Icon7);
	DDX_Control(pDX, IDC_ICON8, m_Icon8);
	DDX_Control(pDX, IDC_COLUMN0, m_c0);
	DDX_Control(pDX, IDC_COLUMN1, m_c1);
	DDX_Control(pDX, IDC_COLUMN2, m_c2);
	DDX_Control(pDX, IDC_COLUMN3, m_c3);
	DDX_Control(pDX, IDC_COLUMN4, m_c4);
	DDX_Control(pDX, IDC_COLUMN5, m_c5);
	DDX_Control(pDX, IDC_COLUMN6, m_c6);
	DDX_Control(pDX, IDC_COLUMN7, m_c7);
	DDX_Control(pDX, IDC_COLUMN8, m_c8);

	if (!pDX->m_bSaveAndValidate)
	{
		Icon_Combo_Texts.SetComboList(&m_Icon0);
		Icon_Combo_Texts.SetComboList(&m_Icon1);
		Icon_Combo_Texts.SetComboList(&m_Icon2);
		Icon_Combo_Texts.SetComboList(&m_Icon3);
		Icon_Combo_Texts.SetComboList(&m_Icon4);
		Icon_Combo_Texts.SetComboList(&m_Icon5);
		Icon_Combo_Texts.SetComboList(&m_Icon6);
		Icon_Combo_Texts.SetComboList(&m_Icon7);
		Icon_Combo_Texts.SetComboList(&m_Icon8);
		m_c0.SetRange(0,800);
		m_c1.SetRange(0,800);
		m_c2.SetRange(0,800);
		m_c3.SetRange(0,800);
		m_c4.SetRange(0,800);
		m_c5.SetRange(0,800);
		m_c6.SetRange(0,800);
		m_c7.SetRange(0,800);
		m_c8.SetRange(0,800);

	}	

	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_DATA_MAP(ListProp2)
	DDX_Control(pDX, IDC_ICON0, m_Icon0);
	DDX_Control(pDX, IDC_ICON1, m_Icon1);
	DDX_Control(pDX, IDC_ICON2, m_Icon2);
	DDX_Control(pDX, IDC_ICON3, m_Icon3);
	DDX_Control(pDX, IDC_ICON4, m_Icon4);
	DDX_Control(pDX, IDC_ICON5, m_Icon5);
	DDX_Control(pDX, IDC_ICON6, m_Icon6);
	DDX_Control(pDX, IDC_ICON7, m_Icon7);
	DDX_Control(pDX, IDC_ICON8, m_Icon8);
	DDP_CBIndex(pDX, IDC_ALIGNMENT0, m_A0, _T("A0") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT0, m_A0);
	DDP_CBIndex(pDX, IDC_ALIGNMENT1, m_A1, _T("A1") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT1, m_A1);
	DDP_CBIndex(pDX, IDC_ALIGNMENT2, m_A2, _T("A2") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT2, m_A2);
	DDP_CBIndex(pDX, IDC_ALIGNMENT3, m_A3, _T("A3") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT3, m_A3);
	DDP_CBIndex(pDX, IDC_ALIGNMENT4, m_A4, _T("A4") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT4, m_A4);
	DDP_CBIndex(pDX, IDC_ALIGNMENT5, m_A5, _T("A5") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT5, m_A5);
	DDP_CBIndex(pDX, IDC_ALIGNMENT6, m_A6, _T("A6") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT6, m_A6);
	DDP_CBIndex(pDX, IDC_ALIGNMENT7, m_A7, _T("A7") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT7, m_A7);
	DDP_CBIndex(pDX, IDC_ALIGNMENT8, m_A8, _T("A8") );
	DDX_CBIndex(pDX, IDC_ALIGNMENT8, m_A8);
	DDP_Text(pDX, IDC_EDITCOLUMN1, m_C1, _T("C1") );
	DDX_Text(pDX, IDC_EDITCOLUMN1, m_C1);
	DDP_Text(pDX, IDC_EDITCOLUMN2, m_C2, _T("C2") );
	DDX_Text(pDX, IDC_EDITCOLUMN2, m_C2);
	DDP_Text(pDX, IDC_EDITCOLUMN3, m_C3, _T("C3") );
	DDX_Text(pDX, IDC_EDITCOLUMN3, m_C3);
	DDP_Text(pDX, IDC_EDITCOLUMN4, m_C4, _T("C4") );
	DDX_Text(pDX, IDC_EDITCOLUMN4, m_C4);
	DDP_Text(pDX, IDC_EDITCOLUMN5, m_C5, _T("C5") );
	DDX_Text(pDX, IDC_EDITCOLUMN5, m_C5);
	DDP_Text(pDX, IDC_EDITCOLUMN6, m_C6, _T("C6") );
	DDX_Text(pDX, IDC_EDITCOLUMN6, m_C6);
	DDP_Text(pDX, IDC_EDITCOLUMN7, m_C7, _T("C7") );
	DDX_Text(pDX, IDC_EDITCOLUMN7, m_C7);
	DDP_Text(pDX, IDC_EDITCOLUMN8, m_C8, _T("C8") );
	DDX_Text(pDX, IDC_EDITCOLUMN8, m_C8);
	DDP_CBIndex(pDX, IDC_ICON0, m_I0, _T("I0") );
	DDX_CBIndex(pDX, IDC_ICON0, m_I0);
	DDP_CBIndex(pDX, IDC_ICON1, m_I1, _T("I1") );
	DDX_CBIndex(pDX, IDC_ICON1, m_I1);
	DDP_CBIndex(pDX, IDC_ICON2, m_I2, _T("I2") );
	DDX_CBIndex(pDX, IDC_ICON2, m_I2);
	DDP_CBIndex(pDX, IDC_ICON3, m_I3, _T("I3") );
	DDX_CBIndex(pDX, IDC_ICON3, m_I3);
	DDP_CBIndex(pDX, IDC_ICON4, m_I4, _T("I4") );
	DDX_CBIndex(pDX, IDC_ICON4, m_I4);
	DDP_CBIndex(pDX, IDC_ICON5, m_I5, _T("I5") );
	DDX_CBIndex(pDX, IDC_ICON5, m_I5);
	DDP_CBIndex(pDX, IDC_ICON6, m_I6, _T("I6") );
	DDX_CBIndex(pDX, IDC_ICON6, m_I6);
	DDP_CBIndex(pDX, IDC_ICON7, m_I7, _T("I7") );
	DDX_CBIndex(pDX, IDC_ICON7, m_I7);
	DDP_CBIndex(pDX, IDC_ICON8, m_I8, _T("I8") );
	DDX_CBIndex(pDX, IDC_ICON8, m_I8);
	DDP_Text(pDX, IDC_EDITCOLUMN0, m_C0, _T("C0") );
	DDX_Text(pDX, IDC_EDITCOLUMN0, m_C0);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// ListProp2 message handlers

void ListProp2::OnChangeEditcolumn0() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the COlePropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
//	UByteP(0xB0000)[160*6]++; 
//DEADCODE JIM 14/12/99 	UpdateData( );

}

void ListProp2::OnKillfocusEditcolumn0() 
{
	// TODO: Add your control notification handler code here
//	UByteP(0xB0000)[160*6+2]++;
	
}

void ListProp2::OnUpdateEditcolumn0() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the COlePropertyPage::OnInitDialog()
	// function to send the EM_SETEVENTMASK message to the control
	// with the ENM_UPDATE flag ORed into the lParam mask.
	
	// TODO: Add your control notification handler code here
//	UByteP(0xB0000)[160*6+4]++;
	
}
