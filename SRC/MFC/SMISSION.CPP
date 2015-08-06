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

// RowanDialog: // SMission.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "SMission.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// SMissionConfigure dialog

#define OPTIONS	\
	SETFIELD(CHAR(autopilotskillLW,0,1),						IDC_CBO_LWSKILL,RESCOMBO(BLMHT_BOT,5),				NOLEVEL)	\
	SETFIELD(CHAR(autopilotskillRAF,0,1),						IDC_CBO_RAFSKILL,RESCOMBO(BLMHT_BOT,5),			NOLEVEL)	\
 	SETFIELD(BIT(gamedifficulty,GD_AUTOVECTORING),		IDC_CBO_AUTOVECTOR,RESCOMBO(OFF,2),		DISABLEDINCOMMS)	\
	SETFIELD(BIT(gamedifficulty,GD_LWTACTICS),			IDC_CBO_LWTACTICS,RESCOMBO(HISTORIC,2),		NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_MAPPLOTTING),		IDC_CBO_MAPPLOTTING,RESCOMBO(OFF,2),	NOLEVEL)	\
	SETFIELD(BIT(gamedifficulty,GD_LWINTELL),			IDC_CBO_LWINTELL,RESCOMBO(HISTORIC2,2),		NOLEVEL)	\


//DEADCODE RDH 23/05/00   	SETFIELD(BIT(gamedifficulty,GD_RAFTACTICS),			IDC_CBO_RAFTACTICS,RESCOMBO(OFF,2),		NOLEVEL)	\
//SETFIELD(BIT(gamedifficulty,GD_FLYOPTION),			IDC_CBO_FLYOPTION,RESCOMBO(EITHER,2),		NOLEVEL)	


RDialog*	SMissionConfigure::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new SMissionConfigure())
			);
}


SMissionConfigure::SMissionConfigure(CWnd* pParent /*=NULL*/)
	: RowanDialog(SMissionConfigure::IDD, pParent)
{
	//{{AFX_DATA_INIT(SMissionConfigure)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void SMissionConfigure::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SMissionConfigure)
	DDX_Control(pDX, IDC_CBO_LWSKILL, m_IDC_CBO_LWSKILL);
	DDX_Control(pDX, IDC_CBO_RAFSKILL, m_IDC_CBO_RAFSKILL);
	DDX_Control(pDX, IDC_CBO_AUTOVECTOR, m_IDC_CBO_AUTOVECTOR);
	DDX_Control(pDX, IDC_CBO_LWTACTICS, m_IDC_CBO_LWTACTICS);
	DDX_Control(pDX, IDC_CBO_MAPPLOTTING, m_IDC_CBO_MAPPLOTTING);
	DDX_Control(pDX, IDC_CBO_LWINTELL, m_IDC_CBO_LWINTELL);
	DDX_Control(pDX, IDC_CBO_FLYOPTION, m_IDC_CBO_FLYOPTION);
	DDX_Control(pDX, IDC_CBO_RAFTACTICS, m_IDC_CBO_RAFTACTICS);
	//}}AFX_DATA_MAP
#define	SG2C_DISPLAY setlevel
#include "sg2combo.h"
	OPTIONS	
}


BEGIN_MESSAGE_MAP(SMissionConfigure, CDialog)
	//{{AFX_MSG_MAP(SMissionConfigure)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SMissionConfigure message handlers





BOOL SMissionConfigure::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void SMissionConfigure::PreDestroyPanel()
{
#define	SG2C_WRITEBACK setlevel
#include "sg2combo.h"
	OPTIONS	
}

 #define SG2C_CLEANUP
#include "sg2combo.h"
