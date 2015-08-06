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

// RowanDialog: // CampName.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "CampName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CampaignEnterName dialog


RDialog*	CampaignEnterName::Make(int whichcamp)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new CampaignEnterName(whichcamp))
			);
}


CampaignEnterName::CampaignEnterName(int whichcamp,CWnd* pParent /*=NULL*/)
	: RowanDialog(CampaignEnterName::IDD, pParent)
{
	this->whichcamp=whichcamp;
	//{{AFX_DATA_INIT(CampaignEnterName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CampaignEnterName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CampaignEnterName)
	DDX_Control(pDX, IDC_NAME, m_IDC_NAME);
	DDX_Control(pDX, IDC_PERIOD, m_IDC_PERIOD);
	DDX_Control(pDX, IDC_PERIOD2, m_IDC_PERIOD2);
	DDX_Control(pDX, IDC_ROLE, m_IDC_ROLE);
	DDX_Control(pDX, IDC_SIDE, m_IDC_SIDE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CampaignEnterName, CDialog)
	//{{AFX_MSG_MAP(CampaignEnterName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CampaignEnterName message handlers

BEGIN_EVENTSINK_MAP(CampaignEnterName, CDialog)
    //{{AFX_EVENTSINK_MAP(CampaignEnterName)
	ON_EVENT(CampaignEnterName, IDC_ROLE, 1 /* Clicked */, OnClickedRole, VTS_NONE)
	ON_EVENT(CampaignEnterName, IDC_PERIOD2, 1 /* Clicked */, OnClickedPeriod2, VTS_NONE)
	ON_EVENT(CampaignEnterName, IDC_PERIOD, 1 /* Clicked */, OnClickedPeriod, VTS_NONE)
	ON_EVENT(CampaignEnterName, IDC_NAME, 2 /* TextChanged */, OnTextChangedName, VTS_I4)
	ON_EVENT(CampaignEnterName, IDC_SIDE, 1 /* Clicked */, OnClickedSide, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CampaignEnterName::OnClickedRole() 
{
#ifndef NDEBUG
	// TODO: Add your control notification handler code here
	FullPanel()->OnSelectRlistbox(3,3);
#endif
}

void CampaignEnterName::OnClickedPeriod2() 
{
	// TODO: Add your control notification handler code here
	FullPanel()->OnSelectRlistbox(2,2);
	
}

void CampaignEnterName::OnClickedPeriod() 
{
	// TODO: Add your control notification handler code here
	FullPanel()->OnSelectRlistbox(2,2);
	
}

void CampaignEnterName::OnTextChangedName(LPTSTR text) 
{
	// TODO: Add your control notification handler code here
	trunc(text,PLAYERNAMELEN - 1);	
	strcpy(Save_Data.CommsPlayerName,text);

	
}

void CampaignEnterName::OnClickedSide() 
{
	// TODO: Add your control notification handler code here
	FullPanel()->OnSelectRlistbox(4,4);
	
}

BOOL CampaignEnterName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (RFullPanelDial::gamestate==RFullPanelDial::PILOT)
		m_IDC_ROLE.SetString(RESSTRING(PILOT));
	else
		m_IDC_ROLE.SetString(RESSTRING(COMMANDER));
	if (RFullPanelDial::gameside==RFullPanelDial::SIDE_RAF)
		m_IDC_SIDE.SetString(RESSTRING(RAF));
	else
		m_IDC_SIDE.SetString(RESSTRING(LUFTWAFFE));
	
	m_IDC_PERIOD.SetString(RESLIST(SCAMPAIGNSELECT1,whichcamp));
	m_IDC_PERIOD2.SetString(RESLIST(SCAMPAIGNDATE1,whichcamp));
	GETDLGITEM(IDC_NAME)->SetCaption("\b\t\n\v");
	GETDLGITEM(IDC_NAME)->SetCaption(Save_Data.CommsPlayerName);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
