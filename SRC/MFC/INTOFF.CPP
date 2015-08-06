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

// InttOff.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "IntOff.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// InterceptOffered dialog

 RDialog*	InterceptOffered::Make(int pack,int raid)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_BLANK,new InterceptOffered(pack,raid))
			);
}


InterceptOffered::InterceptOffered(int pack,int raid, CWnd* pParent /*=NULL*/)
	: RowanDialog(InterceptOffered::IDD, pParent)
{
	p = pack;
	rd = raid;
	//{{AFX_DATA_INIT(InterceptOffered)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	currreoffer=0,maxreoffer=0;

}


void InterceptOffered::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(InterceptOffered)
	DDX_Control(pDX, IDC_RSTATICINTERCEPTOFFERED, m_IDC_RSTATICINTERCEPTOFFERED);
	DDX_Control(pDX, IDC_DONTSHOW, m_IDC_DONTSHOW);
	DDX_Control(pDX, IDC_OK, m_IDC_OK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(InterceptOffered, CDialog)
	//{{AFX_MSG_MAP(InterceptOffered)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// InterceptOffered message handlers
void InterceptOffered::RefreshData(int childnum)
{
	if (childnum != -2)
	{
		int newp=childnum>>16;
		int newr=childnum&0xffff;
		if (maxreoffer==MAX_REOFFERS)
		 	RAFDirectivesResults::InterceptSanctioned(newp,newr);
		else
		{
			ReOffers[maxreoffer][0]=newp;
			ReOffers[maxreoffer][1]=newr;
			maxreoffer++;
			InitDialog();



		}

	}
}

BOOL InterceptOffered::OnInitDialog() 
{
	countdown=60;
	CDialog::OnInitDialog();
	InitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void InterceptOffered::OnOK()
{
 	RAFDirectivesResults::InterceptSanctioned(p,rd);

	CloseOrRedo();
}

void InterceptOffered::CloseOrRedo()
{
	if (currreoffer!=maxreoffer)
	{
		if (MMC.autoscramble)
		{
			while (currreoffer!=maxreoffer)
			{
			 	RAFDirectivesResults::InterceptSanctioned(ReOffers[currreoffer][0],ReOffers[currreoffer][1]);
				currreoffer++;
			}

			OnCancel();

		}
		else
		{
		 	p = ReOffers[currreoffer][0];
			rd = ReOffers[currreoffer][1];
			currreoffer++;
			if (countdown<10)
				countdown=10;
			else
				countdown=60;
			InitDialog();
		}


	}
	else
		OnCancel();
}

void InterceptOffered::InitDialog() 
{
 	maptimer=SetTimer(DPlay::TIMER_MAP,1000,NULL);

	CRStatic*   s;

	Profile& pk = Todays_Packages.pack[p];

	CRButton* b;
	b = GETDLGITEM(IDC_DONTSHOW);
	b->SetPressed(MMC.autoscramble);


	s=GETDLGITEM(IDC_RSTATICINTERCEPTOFFERED);
	if (maxreoffer)
		s->SetString(
			CSprintf("%s %03i (%i/%i): %s", 
			RESSTRING(RAID),pk.raidnumentries[rd].raidnum,currreoffer+1,maxreoffer+1,RESSTRING(INTERCEPTMSG)));
	else
		s->SetString(
			CSprintf("%s %03i: %s", 
			RESSTRING(RAID),pk.raidnumentries[rd].raidnum, RESSTRING(INTERCEPTMSG)));
	
}

BEGIN_EVENTSINK_MAP(InterceptOffered, CDialog)
    //{{AFX_EVENTSINK_MAP(InterceptOffered)
	ON_EVENT(InterceptOffered, IDC_DONTSHOW, 1 /* Clicked */, OnClickedDontshow, VTS_NONE)
	ON_EVENT(InterceptOffered, IDC_FLY, 1 /* Clicked */, OnClickedFly, VTS_NONE)
	ON_EVENT(InterceptOffered, IDC_OK, 1 /* Clicked */, OnClickedOk, VTS_NONE)
	ON_EVENT(InterceptOffered, IDC_CANCEL, 1 /* Clicked */, OnClickedCancel, VTS_NONE)
	ON_EVENT(InterceptOffered, IDC_TASK, 1 /* Clicked */, OnClickedTask, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void InterceptOffered::OnClickedDontshow() 
{
	if (MMC.autoscramble)
		MMC.autoscramble = false;
	else
		MMC.autoscramble = true;
}	


void InterceptOffered::OnClickedFly() 
{
	int packnum;
	packnum =  RAFDirectivesResults::InterceptSanctioned(p,rd);
	if (packnum >= 0)
	{
	 	Profile& pk = Todays_Packages.pack[packnum];
		MMC.fav.forcesquadron = pk[0].squadnum;
	}

	CloseOrRedo();
	
}

void InterceptOffered::OnClickedOk() 
{
	OnOK();
	
}

void InterceptOffered::OnClickedCancel() 
{
	CloseOrRedo();
	
}
void InterceptOffered::OnClickedTask() 
{
#ifndef	BOB_DEMO_VER

 	int packnum =  RAFDirectivesResults::InterceptSanctioned(p,rd);
	RDialog::m_pView->SetHiLightInfo(packnum, 0,UID_Null);

	TitleBarPtr().OpenRAFTask();	

#endif
	CloseOrRedo();

}

void InterceptOffered::OnDestroy() 
{
	KillTimer(maptimer);
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void InterceptOffered::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
	if (MMC.accelrates[MMC.ACCEL_DIALOGSPEED]<MMC.curraccelrate)
		countdown-=MMC.accelrates[MMC.ACCEL_DIALOGSPEED];
	else
		countdown-=MMC.curraccelrate;
	if (countdown<=0)
		OnOK();
	else
		GETDLGITEM(IDC_OK)->SetString(CSprintf("%s: %i",RESSTRING(OK),countdown));

}
