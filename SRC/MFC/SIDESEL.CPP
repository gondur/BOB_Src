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

// RowanDialog: // SideSel.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "SideSel.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// SideSelect dialog


RDialog*	SideSelect::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new SideSelect(0))
			);
}


SideSelect::SideSelect(int screen,CWnd* pParent /*=NULL*/)
	: RowanDialog(SideSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(SideSelect)
	//}}AFX_DATA_INIT
	scrn = screen;
}


void SideSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SideSelect)
	DDX_Control(pDX, IDC_LUFTWAFFE, m_IDC_LUFTWAFFE);
	DDX_Control(pDX, IDC_RAF, m_IDC_RAF);
	DDX_Control(pDX, IDC_CANCEL, m_IDC_CANCEL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SideSelect, CDialog)
	//{{AFX_MSG_MAP(SideSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SideSelect message handlers
 static	PolyOutLine	  //note: if poly goes through 0,0 that must be first point!
	SideSelectOutlines[]=
	{	{NULL,0,	{{0,0},		{700,0},	{300,650},	{0,650}}	},
		{NULL,-1,	{{1024,0},	{1024,768},	{300,768},	{300,650},{700,0}}	},
		{NULL,-1,	{{0,650},	{300,650},	{300,768},	{0,768}}	}
	};

BOOL SideSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SideSelectOutlines[0].button=&m_IDC_RAF;
	SideSelectOutlines[1].button=&m_IDC_LUFTWAFFE;
	SideSelectOutlines[2].button=&m_IDC_CANCEL;
	polylist.Add(SideSelectOutlines,3);

	CRButton*	topbut = GETDLGITEM(IDC_RAF);
	CRButton*	btmbut = GETDLGITEM(IDC_LUFTWAFFE);
//DEADCODE DAW 24/11/99 	if (scrn == 0)
//DEADCODE DAW 24/11/99 	{

		topbut->SetString(RESSTRING(RAF));
		btmbut->SetString(RESSTRING(LUFTWAFFE));
//DEADCODE RDH 07/01/00 //DEADCODE DAW 24/11/99 	}else
//DEADCODE DAW 24/11/99 	{
//DEADCODE DAW 24/11/99 		topbut->SetString(RESSTRING(COMMANDER));
//DEADCODE DAW 24/11/99 		btmbut->SetString(RESSTRING(PILOT));
//DEADCODE DAW 24/11/99 	}
//DEADCODE DAW 24/11/99 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(SideSelect, CDialog)
    //{{AFX_EVENTSINK_MAP(SideSelect)
	ON_EVENT(SideSelect, IDC_LUFTWAFFE, 1 /* Clicked */, OnClickedLuftwaffe, VTS_NONE)
	ON_EVENT(SideSelect, IDC_RAF, 1 /* Clicked */, OnClickedRaf, VTS_NONE)
	ON_EVENT(SideSelect, IDC_CANCEL, 1 /* Clicked */, OnClickedCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void SideSelect::OnClickedLuftwaffe() 
{
	// TODO: Add your control notification handler code here
	FullPanel()->OnSelectRlistbox(1,1);					//JIM 12Jan99
	
}

void SideSelect::OnClickedRaf() 
{
	// TODO: Add your control notification handler code here
	FullPanel()->OnSelectRlistbox(0,0);					//JIM 12Jan99

}

void SideSelect::OnClickedCancel() 
{
	// TODO: Add your control notification handler code here
	FullPanel()->OnSelectRlistbox(2,2);					//JIM 12Jan99
	
}
