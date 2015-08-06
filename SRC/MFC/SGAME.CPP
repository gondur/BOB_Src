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

// RowanDialog: // SGame.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SGame.h"
#include "rcombo.h"
#include "comms.h"
#include "winmove.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSGame dialog
#define OPTIONS	\
	SETFIELD(BIT(gamedifficulty,GD_UNLIMITEDARM),				IDC_CBO_WEAPONS,RESCOMBO(REALISTICARMS,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_VULNERABLE),					IDC_CBO_VULNERABLETOFIRE,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_GROUNDCOLLISIONS),			IDC_CBO_GROUNDCOLLISIONS,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_COLLISIONS),					IDC_CBO_MIDAIRCOLLISIONS,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_AIPILOTSALLTIME),			IDC_CBO_AIPILOTALLTIME,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_TACTICALRANGE),				IDC_CBO_ACCELOFF,RESCOMBO(RANGE_TACTICAL,2),		NOLEVEL)	\
	SETFIELD(TYPE(targetsize,TargetSize),								IDC_CBO_TARGETSIZE,RESCOMBO(LMH_LOW,3),				NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_AUTOCANOPY),					IDC_CBO_AUTOCANOPY,RESCOMBO(OFF,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_TEXTINFO),				IDC_CBO_TEXTINFO,RESCOMBO(OFF,2),		NOLEVEL)	\
	

CSGame::CSGame(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSGame)
	//}}AFX_DATA_INIT
}


void CSGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSGame)
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL5,m_IDC_RSTATICCTRL5);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL12,m_IDC_RSTATICCTRL12);
	DDX_Control(pDX,IDC_RSTATICCTRL14,m_IDC_RSTATICCTRL14);
	DDX_Control(pDX,IDC_RSTATICCTRL16,m_IDC_RSTATICCTRL16);
	DDX_Control(pDX,IDC_CBO_WEAPONS,m_IDC_CBO_WEAPONS);
	DDX_Control(pDX,IDC_CBO_VULNERABLETOFIRE,m_IDC_CBO_VULNERABLETOFIRE);
	DDX_Control(pDX,IDC_CBO_GROUNDCOLLISIONS,m_IDC_CBO_GROUNDCOLLISIONS);
	DDX_Control(pDX,IDC_CBO_MIDAIRCOLLISIONS,m_IDC_CBO_MIDAIRCOLLISIONS);
	DDX_Control(pDX,IDC_CBO_AIPILOTALLTIME,m_IDC_CBO_AIPILOTALLTIME);
	DDX_Control(pDX,IDC_CBO_ACCELOFF,m_IDC_CBO_ACCELOFF);
	DDX_Control(pDX,IDC_CBO_TARGETSIZE,m_IDC_CBO_TARGETSIZE);
	DDX_Control(pDX, IDC_CBO_AUTOCANOPY, m_IDC_CBO_AUTOCANOPY);
	DDX_Control(pDX, IDC_CBO_TEXTINFO, m_IDC_CBO_TEXTINFO);
	//}}AFX_DATA_MAP
#define	SG2C_DISPLAY setlevel
#include "sg2combo.h"
	OPTIONS	
//DEADCODE RDH 05/11/99 	m_IDC_CBO_WEAPONS.SetCircularStyle(TRUE);
//DEADCODE RDH 05/11/99 	m_IDC_CBO_VULNERABLETOFIRE.SetCircularStyle(TRUE);
//DEADCODE RDH 05/11/99 	m_IDC_CBO_GROUNDCOLLISIONS.SetCircularStyle(TRUE);
//DEADCODE RDH 05/11/99 	m_IDC_CBO_MIDAIRCOLLISIONS.SetCircularStyle(TRUE);
//DEADCODE RDH 05/11/99 	m_IDC_CBO_AIPILOTALLTIME.SetCircularStyle(TRUE);
//DEADCODE RDH 05/11/99 	m_IDC_CBO_ACCELOFF.SetCircularStyle(TRUE);
//DEADCODE RDH 05/11/99 	m_IDC_CBO_TARGETSIZE.SetCircularStyle(TRUE);
//DEADCODE RDH 05/11/99 	m_IDC_CBO_SKILL_UN.SetCircularStyle(TRUE);
//DEADCODE RDH 05/11/99 	m_IDC_CBO_SKILL_REDS.SetCircularStyle(TRUE);
}


BEGIN_MESSAGE_MAP(CSGame, CDialog)
	//{{AFX_MSG_MAP(CSGame)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSGame message handlers

BOOL CSGame::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if (_DPlay.PlayerCreated)									//AMM 12Jul99
	{															//AMM 12Jul99
//DeadCode AMM 16Nov99 		_DPlay.UISendInPrefsMessage();							//AMM 12Jul99
//DeadCode AMM 16Nov99 		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PREFS;		//AMM 12Jul99
	_DPlay.SendStatusChange(DPlay::CPS_PREFS);
	}															//AMM 12Jul99

	GamePref_Timer=SetTimer(DPlay::TIMER_PREFSGAME,0,NULL);


	CRCombo* combo;
	if	(		(RFullPanelDial::incomms)
			&&	(_DPlay.UIPlayerType==DPlay::PLAYER_GUEST)
		)
	{
		combo=GETDLGITEM(IDC_CBO_WEAPONS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_VULNERABLETOFIRE);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_GROUNDCOLLISIONS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_MIDAIRCOLLISIONS);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_AIPILOTALLTIME);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_ACCELOFF);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_TARGETSIZE);
		combo->SetEnabled(false);
		combo=GETDLGITEM(IDC_CBO_TEXTINFO);
		combo->SetEnabled(false);
	}else
	{
		combo=GETDLGITEM(IDC_CBO_WEAPONS);
		combo->SetEnabled(true);
		if (RFullPanelDial::incomms && _DPlay.GameType<DPlay::COMMSQUICKMISSION)
		{
			combo=GETDLGITEM(IDC_CBO_VULNERABLETOFIRE);
			combo->SetEnabled(false);
			combo=GETDLGITEM(IDC_CBO_GROUNDCOLLISIONS);
			combo->SetEnabled(false);
			combo=GETDLGITEM(IDC_CBO_MIDAIRCOLLISIONS);
			combo->SetEnabled(false);
		}
		else
		{
			combo=GETDLGITEM(IDC_CBO_VULNERABLETOFIRE);
			combo->SetEnabled(true);
			combo=GETDLGITEM(IDC_CBO_GROUNDCOLLISIONS);
			combo->SetEnabled(true);
			combo=GETDLGITEM(IDC_CBO_MIDAIRCOLLISIONS);
			combo->SetEnabled(true);
		}
		combo=GETDLGITEM(IDC_CBO_AIPILOTALLTIME);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_ACCELOFF);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_TARGETSIZE);
		combo->SetEnabled(true);
		combo=GETDLGITEM(IDC_CBO_TEXTINFO);
		combo->SetEnabled(true);

	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSGame::OnDestroy() 
{
	KillTimer(GamePref_Timer);

//#define	SG2C_WRITEBACK setlevel
//#include "sg2combo.h"
//	OPTIONS	
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
void CSGame::PreDestroyPanel()
{
#define	SG2C_WRITEBACK setlevel
#include "sg2combo.h"
	OPTIONS	
}

void CSGame::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==GamePref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}

	CDialog::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CSGame, CDialog)
    //{{AFX_EVENTSINK_MAP(CSGame)
	ON_EVENT(CSGame, IDC_CBO_AUTOCANOPY, 1 /* TextChanged */, OnTextChangedCboAutocanopy, VTS_BSTR VTS_I2)
	ON_EVENT(CSGame, IDC_CBO_TEXTINFO, 1 /* TextChanged */, OnTextChangedCboTextinfo, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSGame::OnTextChangedCboAutocanopy(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	
}

void CSGame::OnTextChangedCboTextinfo(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	
}
 #define SG2C_CLEANUP
#include "sg2combo.h"
