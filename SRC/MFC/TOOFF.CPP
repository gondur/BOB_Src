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

// RowanDialog: // TOOff.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "TOOff.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// TakeOverOffered dialog



RDialog*	TakeOverOffered::Make(int packf, int sqf, int latest)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_BLANK,new TakeOverOffered(packf,sqf, latest))
			);
}
TakeOverOffered::TakeOverOffered(int packf, int sqf, int latest,CWnd* pParent /*=NULL*/)
	: RowanDialog(TakeOverOffered::IDD, pParent)
{
	//{{AFX_DATA_INIT(TakeOverOffered)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	 packnum = packf;
	 sqnum = sqf;
	latestmsg = latest;
}


void TakeOverOffered::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TakeOverOffered)
	DDX_Control(pDX, IDC_RSTATICTAKEOVEROFFERED, m_IDC_RSTATICTAKEOVEROFFERED);
	DDX_Control(pDX, IDC_PAUSE, m_IDC_PAUSE);
	DDX_Control(pDX, IDC_NORMALTIME, m_IDC_NORMALTIME);
	DDX_Control(pDX, IDC_CANCEL, m_IDC_CANCEL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TakeOverOffered, CDialog)
	//{{AFX_MSG_MAP(TakeOverOffered)
	ON_WM_DESTROY()
	ON_WM_TIMER()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TakeOverOffered message handlers

BOOL TakeOverOffered::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	CRStatic*   s;

 	maptimer=SetTimer(DPlay::TIMER_MAP,1000,NULL);
	countdown=60;
	s=GETDLGITEM(IDC_RSTATICTAKEOVEROFFERED);
	s->SetString(Node_Data.intel.MessageBodyToText(latestmsg));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(TakeOverOffered, CDialog)
    //{{AFX_EVENTSINK_MAP(TakeOverOffered)
	ON_EVENT(TakeOverOffered, IDC_PAUSE, 1 /* Clicked */, OnClickedPause, VTS_NONE)
	ON_EVENT(TakeOverOffered, IDC_NORMALTIME, 1 /* Clicked */, OnClickedNormaltime, VTS_NONE)
	ON_EVENT(TakeOverOffered, IDC_FLY, 1 /* Clicked */, OnClickedFly, VTS_NONE)
	ON_EVENT(TakeOverOffered, IDC_CANCEL, 1 /* Clicked */, OnClickedCancel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void TakeOverOffered::OnClickedPause() 
{
#ifndef	BOB_DEMO_VER

	TitleBarPtr().ClickPause();	
	CRButton* b;

	b = GETDLGITEM(IDC_PAUSE);
	b->SetPressed(FALSE);

#endif
}

void TakeOverOffered::OnClickedNormaltime() 
{
#ifndef	BOB_DEMO_VER

	TitleBarPtr().ClickPlay();

	CRButton* b;

	b = GETDLGITEM(IDC_NORMALTIME);
	b->SetPressed(FALSE);
#endif	
}



void TakeOverOffered::OnClickedFly() 
{
	OnOK();
}
void TakeOverOffered::OnOK() 
{
#ifndef	BOB_DEMO_VER

	RDialog::m_pView->SetHiLightInfo(packnum,sqnum, UID_Null);
	MainToolBar().OnClickedFrag2();
#endif
}

void TakeOverOffered::OnClickedCancel() 
{
	OnCancel();	
}

void TakeOverOffered::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
	if (MMC.accelrates[MMC.ACCEL_DIALOGSPEED]<MMC.curraccelrate)
		countdown-=MMC.accelrates[MMC.ACCEL_DIALOGSPEED];
	else
		countdown-=MMC.curraccelrate;
	if (countdown<=0)
		OnCancel();
	else
		GETDLGITEM(IDC_CANCEL)->SetString(CSprintf("%s: %i",RESSTRING(CANCEL),countdown));

}

void TakeOverOffered::OnDestroy() 
{
	KillTimer(maptimer);
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
