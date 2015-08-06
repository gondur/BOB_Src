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

// RowanDialog: // TlBrCntl.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "TlBrCntl.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// ToolBarControl dialog


RDialog*	ToolBarControl::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_BLANK,new ToolBarControl())
			);
}


ToolBarControl::ToolBarControl(CWnd* pParent /*=NULL*/)
	: RowanDialog(ToolBarControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(ToolBarControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	testall=0;
	testall<<TB_MAIN<<TB_MISC<<TB_TITLE<<TB_REPORT<<TB_SCALE;
}


void ToolBarControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ToolBarControl)
	DDX_Control(pDX, IDC_TB_TITLE, m_IDC_TB_TITLE);
//DEADCODE RDH 06/01/00 	DDX_Control(pDX, IDC_TB_COMMS, m_IDC_TB_COMMS);
	DDX_Control(pDX, IDC_TB_MAIN, m_IDC_TB_MAIN);
	DDX_Control(pDX, IDC_TB_MAPTOOLS, m_IDC_TB_MAPTOOLS);
	DDX_Control(pDX, IDC_TB_MESSAGES, m_IDC_TB_MESSAGES);
//DEADCODE RDH 06/01/00 	DDX_Control(pDX, IDC_TB_OVERVIEW, m_IDC_TB_OVERVIEW);
	DDX_Control(pDX, IDC_TB_MAPSCALE, m_IDC_TB_MAPSCALE);
	DDX_Control(pDX, IDC_TB_ALL, m_IDC_TB_ALL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ToolBarControl, CDialog)
	//{{AFX_MSG_MAP(ToolBarControl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ToolBarControl message handlers

BOOL ToolBarControl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//DEADCODE RDH 06/01/00 	CRButton* b = GETDLGITEM(IDC_TB_COMMS);
//DEADCODE RDH 06/01/00 	b->SetPressed(Save_Data.toolbars[TB_COMMS]);
//DEADCODE RDH 06/01/00 
	CRButton* b = GETDLGITEM(IDC_TB_MAIN);
	b->SetPressed(Save_Data.toolbars[TB_MAIN]);

	b = GETDLGITEM(IDC_TB_MAPTOOLS);
	b->SetPressed(Save_Data.toolbars[TB_MISC]);

	b = GETDLGITEM(IDC_TB_MESSAGES);
	b->SetPressed(Save_Data.toolbars[TB_REPORT]);

//DEADCODE RDH 06/01/00 	b = GETDLGITEM(IDC_TB_OVERVIEW);
//DEADCODE RDH 06/01/00 	b->SetPressed(Save_Data.toolbars[TB_STATUS]);
//DEADCODE RDH 06/01/00 
	b = GETDLGITEM(IDC_TB_TITLE);
	b->SetPressed(Save_Data.toolbars[TB_TITLE]);

	b = GETDLGITEM(IDC_TB_MAPSCALE);
	b->SetPressed(Save_Data.toolbars[TB_SCALE]);

	b = GETDLGITEM(IDC_TB_ALL);
	b->SetPressed(Save_Data.toolbars[TB_SPACE]);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(ToolBarControl, CDialog)
    //{{AFX_EVENTSINK_MAP(ToolBarControl)
//DEADCODE RDH 06/01/00 	ON_EVENT(ToolBarControl, IDC_TB_COMMS, 1 /* Clicked */, OnClickedTbComms, VTS_NONE)
	ON_EVENT(ToolBarControl, IDC_TB_MAIN, 1 /* Clicked */, OnClickedTbMain, VTS_NONE)
	ON_EVENT(ToolBarControl, IDC_TB_MAPTOOLS, 1 /* Clicked */, OnClickedTbMaptools, VTS_NONE)
	ON_EVENT(ToolBarControl, IDC_TB_MESSAGES, 1 /* Clicked */, OnClickedTbMessages, VTS_NONE)
//DEADCODE RDH 06/01/00 	ON_EVENT(ToolBarControl, IDC_TB_OVERVIEW, 1 /* Clicked */, OnClickedTbOverview, VTS_NONE)
	ON_EVENT(ToolBarControl, IDC_TB_TITLE, 1 /* Clicked */, OnClickedTbTitle, VTS_NONE)
	ON_EVENT(ToolBarControl, IDC_TB_MAPSCALE, 1 /* Clicked */, OnClickedTbMapscale, VTS_NONE)
	ON_EVENT(ToolBarControl, IDC_TB_ALL, 1 /* Clicked */, OnClickedTbAll, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//DEADCODE RDH 06/01/00 void ToolBarControl::OnClickedTbComms() 
//DEADCODE RDH 06/01/00 {
//DEADCODE RDH 06/01/00 	if (Save_Data.toolbars[TB_COMMS])
//DEADCODE RDH 06/01/00 		Save_Data.toolbars%=TB_COMMS;
//DEADCODE RDH 06/01/00 	else
//DEADCODE RDH 06/01/00 		Save_Data.toolbars|=TB_COMMS;
//DEADCODE RDH 06/01/00 	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
//DEADCODE RDH 06/01/00     main->UpdateToolbars(false);
//DEADCODE RDH 06/01/00 	
//DEADCODE RDH 06/01/00 }
void	ToolBarControl::Redraw()
{
#ifndef	BOB_DEMO_VER

	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	ToolBarsField ontools=Save_Data.toolbars;
	ontools&=testall;
	if (ontools.Count()==0)
	{
		Save_Data.toolbars%=TB_SPACE;
		GETDLGITEM(IDC_TB_ALL)->SetPressed(Save_Data.toolbars[TB_SPACE]);
	    main->UpdateToolbars(true);
	}
	else
		if (Save_Data.toolbars[TB_SPACE])
		    main->UpdateToolbars(false);

#endif
}
void ToolBarControl::OnClickedTbMain() 
{
	if (Save_Data.toolbars[TB_MAIN])
		Save_Data.toolbars%=TB_MAIN;
	else
		Save_Data.toolbars|=TB_MAIN;
	Redraw();
}

void ToolBarControl::OnClickedTbMaptools() 
{
	if (Save_Data.toolbars[TB_MISC])
		Save_Data.toolbars%=TB_MISC;
	else
		Save_Data.toolbars|=TB_MISC;
	Redraw();
}

void ToolBarControl::OnClickedTbMessages() 
{
	if (Save_Data.toolbars[TB_REPORT])
		Save_Data.toolbars%=TB_REPORT;
	else
		Save_Data.toolbars|=TB_REPORT;
	Redraw();
}

//DEADCODE RDH 06/01/00 void ToolBarControl::OnClickedTbOverview() 
//DEADCODE RDH 06/01/00 {
//DEADCODE RDH 06/01/00 	if (Save_Data.toolbars[TB_STATUS])
//DEADCODE RDH 06/01/00 		Save_Data.toolbars%=TB_STATUS;
//DEADCODE RDH 06/01/00 	else
//DEADCODE RDH 06/01/00 		Save_Data.toolbars|=TB_STATUS;
//DEADCODE RDH 06/01/00 	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
//DEADCODE RDH 06/01/00     main->UpdateToolbars(false);
//DEADCODE RDH 06/01/00 	
//DEADCODE RDH 06/01/00 }

void ToolBarControl::OnClickedTbTitle() 
{
	if (Save_Data.toolbars[TB_TITLE])
		Save_Data.toolbars%=TB_TITLE;
	else
		Save_Data.toolbars|=TB_TITLE;
	Redraw();
}

void ToolBarControl::OnClickedTbMapscale() 
{
	if (Save_Data.toolbars[TB_SCALE])
		Save_Data.toolbars%=TB_SCALE;
	else
		Save_Data.toolbars|=TB_SCALE;
	Redraw();
}

void ToolBarControl::OnClickedTbAll() 
{
#ifndef	BOB_DEMO_VER

	// TODO: Add your control notification handler code here
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	if (Save_Data.toolbars[TB_SPACE])
	{
		Save_Data.toolbars%=TB_SPACE;
	    main->UpdateToolbars(true);
	}
	else
	{
		Save_Data.toolbars|=TB_SPACE;
		ToolBarsField ontools=Save_Data.toolbars;
		ontools&=testall;
		if (ontools.Count()==0)
		{
			Save_Data.toolbars|=testall;
			CRButton* b = GETDLGITEM(IDC_TB_MAIN);
			b->SetPressed(Save_Data.toolbars[TB_MAIN]);

			b = GETDLGITEM(IDC_TB_MAPTOOLS);
			b->SetPressed(Save_Data.toolbars[TB_MISC]);

			b = GETDLGITEM(IDC_TB_MESSAGES);
			b->SetPressed(Save_Data.toolbars[TB_REPORT]);

			b = GETDLGITEM(IDC_TB_TITLE);
			b->SetPressed(Save_Data.toolbars[TB_TITLE]);

			b = GETDLGITEM(IDC_TB_MAPSCALE);
			b->SetPressed(Save_Data.toolbars[TB_SCALE]);

		}
		main->UpdateToolbars(false);
	}
#endif	
}
