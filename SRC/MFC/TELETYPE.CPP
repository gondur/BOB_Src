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

// RowanDialog: // TeleType.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "TeleType.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// TeleType dialog





TeleType::TeleType(MakeRtn maker,CWnd* pParent /*=NULL*/)
	: CRToolBar( pParent)
{
	makertn=maker;
	//{{AFX_DATA_INIT(TeleType)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void TeleType::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TeleType)
	DDX_Control(pDX, IDC_LINE1, m_IDC_LINE1);
	DDX_Control(pDX, IDC_LINE2, m_IDC_LINE2);
	DDX_Control(pDX, IDC_LINE3, m_IDC_LINE3);
	DDX_Control(pDX, IDC_ITEM1, m_IDC_ITEM1);
	DDX_Control(pDX, IDC_ITEM2, m_IDC_ITEM2);
	DDX_Control(pDX, IDC_ITEM3, m_IDC_ITEM3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TeleType, CRToolBar)
	//{{AFX_MSG_MAP(TeleType)
	ON_WM_INITMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TeleType message handlers

BEGIN_EVENTSINK_MAP(TeleType, CRToolBar)
    //{{AFX_EVENTSINK_MAP(TeleType)
	ON_EVENT(TeleType, IDC_LINE1, 1 /* Clicked */, OnClickedLine1, VTS_NONE)
	ON_EVENT(TeleType, IDC_LINE2, 1 /* Clicked */, OnClickedLine2, VTS_NONE)
	ON_EVENT(TeleType, IDC_LINE3, 1 /* Clicked */, OnClickedLine3, VTS_NONE)
	ON_EVENT(TeleType, IDC_ITEM1, 1 /* Clicked */, OnClickedLine1, VTS_NONE)
	ON_EVENT(TeleType, IDC_ITEM2, 1 /* Clicked */, OnClickedLine2, VTS_NONE)
	ON_EVENT(TeleType, IDC_ITEM3, 1 /* Clicked */, OnClickedLine3, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void TeleType::OnClickedLine1() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	Refresh();
	if (makertn)
		if (!LoggedChild(0))
			LogChild(0,makertn(messages[3]));
		else
			CloseLoggedChild(0);
	
}

void TeleType::OnClickedLine2() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	// TODO: Add your control notification handler code here
	Refresh();
	if (makertn)
		if (!LoggedChild(0))
			LogChild(0,makertn(messages[2]));
		else
			CloseLoggedChild(0);
	
}

void TeleType::OnClickedLine3() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	// TODO: Add your control notification handler code here
	Refresh();
	if (makertn)
		if (!LoggedChild(0))
			LogChild(0,makertn(messages[1]));
		else
			CloseLoggedChild(0);
	
}

void TeleType::Refresh(bool force)
{
	if  (		force
			||	(Node_Data.intel.latest != Node_Data.intel.B[IntelBuffer::Bviewedupto])
		)
	{	Node_Data.intel.B[IntelBuffer::Bviewedupto]=Node_Data.intel.latest;
		int i = 3;
		int msg = Node_Data.intel.latest;
		CString msgstr, placestr;
		while (	(i)	&&	(msg != Node_Data.intel.B[IntelBuffer::Bwrap]))
		{
			UniqueID uid = Node_Data.intel.messages[msg].what;
			if (uid)
				placestr = GetTargName(uid);
			else
				placestr = "";

			msgstr = Node_Data.intel.MessageTitleToText(msg);
			FillTextLines(3-i, msgstr, placestr);
			messages[i] = msg;
			i--;
			msg--;
			if (msg < 0)
				msg = IntelBuffer::BUFFERSIZE-1;
		}
		while (i)
		{
			FillTextLines(3-i, "", "");
			i--;
		}
	}	
		
}

void TeleType::OnInitMenu(CMenu* pMenu) 
{
	CRToolBar::OnInitMenu(pMenu);
	
	CRButton*	line = GETDLGITEM(IDC_LINE1);
	line->SetString("Hostiles Approaching");

	// TODO: Add your message handler code here
	
}
void TeleType::FillTextLines( int line,CString str1,CString str2)
{
	CRButton *name=NULL,*text=NULL;
	switch(line)
	{
	case 0:
		text=GETDLGITEM(IDC_LINE1);
		name=GETDLGITEM(IDC_ITEM1);
	break;
	case 1:
		text=GETDLGITEM(IDC_LINE2);
		name=GETDLGITEM(IDC_ITEM2);
	break;
	case 2:
		text=GETDLGITEM(IDC_LINE3);
		name=GETDLGITEM(IDC_ITEM3);
	break;
	}
	text->SetString(str1);
	name->SetString(str2);
}
