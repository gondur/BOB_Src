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

// RowanDialog: // CntrlAcl.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "CntrlAcl.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
int ControlAccel::NonRaidSpd[MAXSPDMAXINDEX]	={1,2,4,5,10,15,20,30,40,60,100,120,180,300,420,600};
int ControlAccel::ReconnSpd[MAXSPDMAXINDEX]		={1,2,4,5,10,15,20,30,40,60,100,120,180,300,420,600};
int ControlAccel::RaidSpd[MAXSPDMAXINDEX]		={1,2,4,5,10,15,20,30,40,60,100,120,180,300,420,600};
int ControlAccel::DialogSpd[DIALOGSPDMAXINDEX]={0,1,2,4,5,10};
/////////////////////////////////////////////////////////////////////////////
// ControlAccel dialog


RDialog*	ControlAccel::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new ControlAccel())
			);
}


ControlAccel::ControlAccel(CWnd* pParent /*=NULL*/)
	: RowanDialog(ControlAccel::IDD, pParent)

{
//	ACCEL_NONRAIDSPD,ACCEL_RECONNSPD,ACCEL_RAIDSPD,ACCEL_DIALOGSPEED, 
	accelcontrols[MMC.ACCEL_DIALOGSPEED]=GETDLGITEM(IDC_RSPINBUT_DIALOGSPEED);
	accelcontrols[MMC.ACCEL_RAIDSPD]=GETDLGITEM(IDC_RSPINBUT_RAID);
	accelcontrols[MMC.ACCEL_RECONNSPD]=GETDLGITEM(IDC_RSPINBUT_RECONN);
	accelcontrols[MMC.ACCEL_NONRAIDSPD]=GETDLGITEM(IDC_RSPINBUT_NONRAID);
	acceltables[MMC.ACCEL_DIALOGSPEED]=	DialogSpd;
	acceltables[MMC.ACCEL_RAIDSPD]=	   RaidSpd;
	acceltables[MMC.ACCEL_RECONNSPD]=  ReconnSpd;
	acceltables[MMC.ACCEL_NONRAIDSPD]= NonRaidSpd;
	//{{AFX_DATA_INIT(ControlAccel)
	//}}AFX_DATA_INIT
}

void	ControlAccel::FixSpeedsInToRange(int against)
{
	int level=MMC.accelrates[against];
	{for (int r=against+1;r<MMC.ACCEL_MAX;r++)
		if (MMC.accelrates[r]>level)
		{	//fix to level
			MMC.accelrates[r]=level;
			int	index = FindIndex(acceltables[r], level);
			accelcontrols[r]->SetIndex(index);
	}	}

	{for (int r=against-1;r>MMC.ACCEL_NORMAL;r--)
		if (MMC.accelrates[r]<level)
		{	//fix to level
			MMC.accelrates[r]=level;
			int	index = FindIndex(acceltables[r], level);
			accelcontrols[r]->SetIndex(index);
	}	}
}

void ControlAccel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ControlAccel)
	DDX_Control(pDX, IDC_RAIDFORMING, m_IDC_RAIDFORMING);
	DDX_Control(pDX, IDC_LOSSES, m_IDC_LOSSES);
	DDX_Control(pDX, IDC_GROUNDATTACK, m_IDC_GROUNDATTACK);
	DDX_Control(pDX, IDC_LANDING, m_IDC_LANDING);
	DDX_Control(pDX, IDC_LARGEENGAGEMENT, m_IDC_LARGEENGAGEMENT);
	DDX_Control(pDX, IDC_REACHCOAST, m_IDC_REACHCOAST);
	DDX_Control(pDX, IDC_RSPINBUT_NONRAID, m_IDC_RSPINBUT_NONRAID);
	DDX_Control(pDX, IDC_RSPINBUT_RAID, m_IDC_RSPINBUT_RAID);
	DDX_Control(pDX, IDC_RSPINBUT_RECONN, m_IDC_RSPINBUT_RECONN);
	DDX_Control(pDX, IDC_SCRAMBLE, m_IDC_SCRAMBLE);
	DDX_Control(pDX, IDC_SMALLENGAGEMENT, m_IDC_SMALLENGAGEMENT);
	DDX_Control(pDX, IDC_RSPINBUT_DIALOGSPEED, m_IDC_RSPINBUT_DIALOGSPEED);
	DDX_Control(pDX, IDC_RSTATIC_NRS, m_IDC_RSTATIC_NRS);
	DDX_Control(pDX, IDC_RSTATIC_RECONS, m_IDC_RSTATIC_RECONS);
	DDX_Control(pDX, IDC_RSTATIC_RS, m_IDC_RSTATIC_RS);
	DDX_Control(pDX, IDC_DIALOGSPD, m_IDC_DIALOGSPD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ControlAccel, CDialog)
	//{{AFX_MSG_MAP(ControlAccel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ControlAccel message handlers

int	 ControlAccel::FindIndex(int* spdarray,int spd, int maxindex)
{
	int retval = 0;
	int i = 0;
	int diff = 100;
	int tdiff;
	while (i <maxindex)
	{
		tdiff = spdarray[i] - spd;
		if (tdiff <0 )
			tdiff = -tdiff;
		if (tdiff < diff)
		{
			diff = tdiff;
			retval = i;
		}
		i++;
	}
//	retval = 0;
	return (retval);
}
void ControlAccel::FillSpin(int* spdarray, CRSpinBut* spinbut, int maxindex)
{
	spinbut->Clear();
	CString string;
	for (int i=0;i<maxindex;i++)
	{
		string = CSprintf("%i",spdarray[i]);
		spinbut->AddString(string);
	}

}

void	ControlAccel::Refresh()
{
	CRSpinBut* spinbut;
	int index;

//	curracceltype
	CRStatic*	s;
	s=GETDLGITEM(IDC_RSTATIC_NRS);
	s->SetForeColor(RGB(0xBA,0xD8,0xF0));
	s=GETDLGITEM(IDC_RSTATIC_RECONS);
	s->SetForeColor(RGB(0xBA,0xD8,0xF0));
	s=GETDLGITEM(IDC_RSTATIC_RS);
	s->SetForeColor(RGB(0xBA,0xD8,0xF0));
	s=GETDLGITEM(IDC_DIALOGSPD);
	s->SetForeColor(RGB(0xBA,0xD8,0xF0));

	if (MMC.curracceltype == MMC.ACCEL_NONRAIDSPD)
 		GETDLGITEM(IDC_RSTATIC_NRS)->SetForeColor(RGB(0xFF,0x00,0x00));
	else if (MMC.curracceltype == MMC.ACCEL_RECONNSPD)
 		GETDLGITEM(IDC_RSTATIC_RECONS)->SetForeColor(RGB(0xFF,0x00,0x00));
	else if (MMC.curracceltype == MMC.ACCEL_RAIDSPD)
		GETDLGITEM(IDC_RSTATIC_RS)->SetForeColor(RGB(0xFF,0x00,0x00));
	else if (MMC.curracceltype == MMC.ACCEL_DIALOGSPEED)
		GETDLGITEM(IDC_DIALOGSPD)->SetForeColor(RGB(0xFF,0x00,0x00));


 	spinbut=GETDLGITEM(IDC_RSPINBUT_NONRAID);
	FillSpin(&NonRaidSpd[0], spinbut);
	index = FindIndex(&NonRaidSpd[0], MMC.accelrates[MMC.ACCEL_NONRAIDSPD]);
	spinbut->SetIndex(index);

	spinbut=GETDLGITEM(IDC_RSPINBUT_RECONN);
	FillSpin(&ReconnSpd[0], spinbut);
	index = FindIndex(&ReconnSpd[0], MMC.accelrates[MMC.ACCEL_RECONNSPD]);
	spinbut->SetIndex(index);


	spinbut=GETDLGITEM(IDC_RSPINBUT_RAID);
	FillSpin(&RaidSpd[0], spinbut);
	index = FindIndex(&RaidSpd[0], MMC.accelrates[MMC.ACCEL_RAIDSPD]);
	spinbut->SetIndex(index);

  	spinbut=GETDLGITEM(IDC_RSPINBUT_DIALOGSPEED);
	FillSpin(&DialogSpd[0], spinbut, DIALOGSPDMAXINDEX);
	index = FindIndex(&DialogSpd[0], MMC.accelrates[MMC.ACCEL_DIALOGSPEED], DIALOGSPDMAXINDEX);
	spinbut->SetIndex(index);


}
BOOL ControlAccel::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	//set tick boxes using decelon, do similiar for controlfly
	//curraccelrate changed by toolbar
	//change enum	AccelType	{ACCEL_PAUSED,ACCEL_NORMAL,ACCEL_MAJORACT,ACCEL_MINORACT,ACCEL_NOACT,ACCEL_MAX};
	//in missman2.h 
	//ACCEL_PAUSED,ACCEL_NORMAL,ACCEL_NONRAID,ACCEL_RECONN,ACCEL_RAID,ACCEL_MAX
	//fill accelrates in missman2 from spins
	//use statics arrays to define range of spins

	GETDLGITEM(IDC_RAIDFORMING)->SetPressed(MMC.fav.decelon[AS_RAID_FORMING]);

	GETDLGITEM(IDC_SCRAMBLE)->SetPressed(MMC.fav.decelon[AS_TAKEOFF]);

	GETDLGITEM(IDC_SMALLENGAGEMENT)->SetPressed(MMC.fav.decelon[AS_SMALL_ENGAGEMENT]);

	GETDLGITEM(IDC_LANDING)->SetPressed(MMC.fav.decelon[AS_LAND]);

	GETDLGITEM(IDC_LARGEENGAGEMENT)->SetPressed(MMC.fav.decelon[AS_LARGE_ENGAGEMENT]);

	GETDLGITEM(IDC_LOSSES)->SetPressed(MMC.fav.decelon[AS_LOSSES]);

	GETDLGITEM(IDC_REACHCOAST)->SetPressed(MMC.fav.decelon[AS_COAST]);

	GETDLGITEM(IDC_GROUNDATTACK)->SetPressed(MMC.fav.decelon[AS_TARG]);

	Refresh();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(ControlAccel, CDialog)
    //{{AFX_EVENTSINK_MAP(ControlAccel)
	ON_EVENT(ControlAccel, IDC_RAIDFORMING, 1 /* Clicked */, OnClickedRaidforming, VTS_NONE)
	ON_EVENT(ControlAccel, IDC_SCRAMBLE, 1 /* Clicked */, OnClickedScramble, VTS_NONE)
	ON_EVENT(ControlAccel, IDC_SMALLENGAGEMENT, 1 /* Clicked */, OnClickedSmallengagement, VTS_NONE)
	ON_EVENT(ControlAccel, IDC_LANDING, 1 /* Clicked */, OnClickedLanding, VTS_NONE)
	ON_EVENT(ControlAccel, IDC_GROUNDATTACK, 1 /* Clicked */, OnClickedGroundattack, VTS_NONE)
	ON_EVENT(ControlAccel, IDC_LARGEENGAGEMENT, 1 /* Clicked */, OnClickedLargeengagement, VTS_NONE)
	ON_EVENT(ControlAccel, IDC_LOSSES, 1 /* Clicked */, OnClickedLosses, VTS_NONE)
	ON_EVENT(ControlAccel, IDC_RSPINBUT_NONRAID, 1 /* TextChanged */, OnTextChangedRspinbutNonraid, VTS_BSTR VTS_I2)
	ON_EVENT(ControlAccel, IDC_RSPINBUT_RAID, 1 /* TextChanged */, OnTextChangedRspinbutRaid, VTS_BSTR VTS_I2)
	ON_EVENT(ControlAccel, IDC_RSPINBUT_RECONN, 1 /* TextChanged */, OnTextChangedRspinbutReconn, VTS_BSTR VTS_I2)
	ON_EVENT(ControlAccel, IDC_REACHCOAST, 1 /* Clicked */, OnClickedReachcoast, VTS_NONE)
	ON_EVENT(ControlAccel, IDC_RSPINBUT_DIALOGSPEED, 1 /* TextChanged */, OnTextChangedRspinbutDialogspeed, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void ControlAccel::OnClickedRaidforming() 
{
	if	(MMC.fav.decelon[AS_RAID_FORMING])
	   MMC.fav.decelon %= AS_RAID_FORMING;
	else
	   MMC.fav.decelon |= AS_RAID_FORMING;

}

void ControlAccel::OnClickedScramble() 
{
	if	(MMC.fav.decelon[AS_TAKEOFF])
	   MMC.fav.decelon %= AS_TAKEOFF;
	else
	   MMC.fav.decelon |= AS_TAKEOFF;
	
}

void ControlAccel::OnClickedSmallengagement() 
{
	if	(MMC.fav.decelon[AS_SMALL_ENGAGEMENT])
	   MMC.fav.decelon %= AS_SMALL_ENGAGEMENT;
	else
	   MMC.fav.decelon |= AS_SMALL_ENGAGEMENT;
	
}

void ControlAccel::OnClickedLanding() 
{
	if	(MMC.fav.decelon[AS_LAND])
	   MMC.fav.decelon %= AS_LAND;
	else
	   MMC.fav.decelon |= AS_LAND;
	
}

void ControlAccel::OnClickedGroundattack() 
{
	if	(MMC.fav.decelon[AS_TARG])
	   MMC.fav.decelon %= AS_TARG;
	else
	   MMC.fav.decelon |= AS_TARG;
	
}

void ControlAccel::OnClickedLargeengagement() 
{
	if	(MMC.fav.decelon[AS_LARGE_ENGAGEMENT])
	   MMC.fav.decelon %= AS_LARGE_ENGAGEMENT;
	else
	   MMC.fav.decelon |= AS_LARGE_ENGAGEMENT;
	
}

void ControlAccel::OnClickedLosses() 
{
	if	(MMC.fav.decelon[AS_LOSSES])
	   MMC.fav.decelon %= AS_LOSSES;
	else
	   MMC.fav.decelon |= AS_LOSSES;
	
}

void ControlAccel::OnTextChangedRspinbutNonraid(LPCTSTR caption, short Index) 
{
	MMC.accelrates[MMC.ACCEL_NONRAIDSPD] = NonRaidSpd[Index];
	FixSpeedsInToRange(MMC.ACCEL_NONRAIDSPD);
}

void ControlAccel::OnTextChangedRspinbutRaid(LPCTSTR caption, short Index) 
{
	MMC.accelrates[MMC.ACCEL_RAIDSPD] = RaidSpd[Index];	
	FixSpeedsInToRange(MMC.ACCEL_RAIDSPD);
	
}

void ControlAccel::OnTextChangedRspinbutReconn(LPCTSTR caption, short Index) 
{
	MMC.accelrates[MMC.ACCEL_RECONNSPD] = ReconnSpd[Index];	
	FixSpeedsInToRange(MMC.ACCEL_RECONNSPD);
	
}

void ControlAccel::OnTextChangedRspinbutDialogspeed(LPCTSTR caption, short Index) 
{
	MMC.accelrates[MMC.ACCEL_DIALOGSPEED] = DialogSpd[Index];	
	FixSpeedsInToRange(MMC.ACCEL_DIALOGSPEED);
	
}

void ControlAccel::OnClickedReachcoast() 
{
	if	(MMC.fav.decelon[AS_COAST])
	   MMC.fav.decelon %= AS_COAST;
	else
	   MMC.fav.decelon |= AS_COAST;
	
}
void ControlAccel::OnOK()
{
//DeadCode CSB 1Aug00 	if (MMC.curraccelrate > 1)
		MMC.curraccelrate = MMC.accelrates[MMC.curracceltype];
		CDialog::OnOK();
}
