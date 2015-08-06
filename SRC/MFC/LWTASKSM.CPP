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

// RowanDialog: // LWTaskSm.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "LWTaskSm.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
int LWTaskSummary::AcSpin[LWTaskSummary::ACMAX]={1,2,3,5,6,9,30};
int LWTaskSummary::FighterSpin[LWTaskSummary::FIGHTERMAX]={0,1,2,4,8,30};

LWTaskSummary::SquadInfo	LWTaskSummary::squadinfo[LWTaskSummary::SQUADMAX] = 
{
	{1,1, IDS_STAFFEL},
	{2,2, IDS_L_STAFFELN},
	{3,1, IDS_GRUPPE},
	{6,2, IDS_GRUPPEN},
	{9,3, IDS_GRUPPEN},
	{12,4, IDS_GRUPPEN},
	{15,5, IDS_GRUPPEN},
	{18,2, IDS_GESCHWADER},
	{27,3, IDS_GESCHWADER},
	{36,4, IDS_GESCHWADER},
	{45,5, IDS_GESCHWADER},
	{54,6, IDS_GESCHWADER},
	{63,7, IDS_GESCHWADER},
	{72,8, IDS_GESCHWADER}
};
/////////////////////////////////////////////////////////////////////////////
// LWTaskSummary dialog
static	struct	Fractional
{
	short	toppc;
	char ratio[6];
	char*	GetFract(int pc)	{for (int i=0;this[i].toppc<pc;i++);return this[i].ratio;} 
}	_Fractionals[]=
{
	{5,"  0%"},
	{15,"1:10"},{22,"1:4"},{29,"1:3"},{36,"1:2"},{45,"2:3"},
	{55,"1:1"},
	{63,"3:2"},{71,"2:1"},{78,"3:1"},{85,"4:1"},{95,"10:1"},
	{101,"100%"}
};

RDialog*	LWTaskSummary::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new LWTaskSummary())
			);
}


LWTaskSummary::LWTaskSummary(CWnd* pParent /*=NULL*/)
	: RowanDialog(LWTaskSummary::IDD, pParent)
{
	packnum=Todays_Packages.hipack;
	//{{AFX_DATA_INIT(LWTaskSummary)
	//}}AFX_DATA_INIT
}


void LWTaskSummary::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWTaskSummary)
	DDX_Control(pDX, IDC_RCOMBOBOMBERTYPE, m_IDC_RCOMBOBOMBERTYPE);
	DDX_Control(pDX, IDC_RCOMBOFIGHTERTYPE, m_IDC_RCOMBOFIGHTERTYPE);
	DDX_Control(pDX, IDC_RSPINBUT_BOMBERS, m_IDC_RSPINBUT_BOMBERS);
	DDX_Control(pDX, IDC_RSPINBUT_FIGHTERS, m_IDC_RSPINBUT_FIGHTERS);
	DDX_Control(pDX, IDC_RSPINBUT_PERCENTFIGHTERS, m_IDC_RSPINBUT_PERCENTFIGHTERS);
	DDX_Control(pDX, IDC_RSPINBUT_TARGETS, m_IDC_RSPINBUT_TARGETS);
//DeadCode JIM 30Oct00 	DDX_Control(pDX, IDC_PC_ATTACHED, m_IDC_PC_ATTACHED);
//DeadCode JIM 30Oct00 	DDX_Control(pDX, IDC_PC_DETACHED, m_IDC_PC_DETACHED);
	DDX_Control(pDX, IDC_PC_FIGHTERS, m_IDC_PC_FIGHTERS);
//DeadCode JIM 30Oct00 	DDX_Control(pDX, IDC_PC_RETURNING, m_IDC_PC_RETURNING);
	DDX_Control(pDX, IDC_SPC_ATTACHED, m_IDC_SPC_ATTACHED);
	DDX_Control(pDX, IDC_SPC_DETACHED, m_IDC_SPC_DETACHED);
	DDX_Control(pDX, IDC_SPC_RETURNING, m_IDC_SPC_RETURNING);
	DDX_Control(pDX, IDC_TARGETS, m_IDC_TARGETS);
	DDX_Control(pDX, IDC_TICK_MAINTAIN_PC, m_IDC_TICK_MAINTAIN_PC);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWTaskSummary, CDialog)
	//{{AFX_MSG_MAP(LWTaskSummary)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
		ON_MESSAGE( WM_SELECTTAB, OnSelectTab)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWTaskSummary message handlers
void	LWTaskSummary::OnSelectTab()
{
	Refresh();
	MakeFighterSpinLists(false);

}

int LWTaskSummary::FindAcSpinEntry(int ac)
{
//DEADCODE RDH 14/01/00 	int entry= 0;
//DEADCODE RDH 14/01/00 	while (	(entry < 18) && (AcSpin[entry] < ac))
//DEADCODE RDH 14/01/00 		entry++;
//DEADCODE RDH 14/01/00 	return (entry);
   return (0);
}
void LWTaskSummary::Refresh()
{
//DeadCode JIM 30Oct00 	MakeFighterSpinLists(false);
	CRSpinBut* spinbut;
//DEADCODE RDH 12/01/00 	spinbut=GETDLGITEM(IDC_RSPINBUT_TARGETS);
//DEADCODE RDH 12/01/00 	spinbut->Clear()->MakeNumList(10,1,1)->SetIndex(Todays_Packages.taskdata.targetnum-1);
//DEADCODE RDH 12/01/00  
//DEADCODE RDH 12/01/00 	spinbut=GETDLGITEM(IDC_RSPINBUT_PERCENTFIGHTERS);
//DEADCODE RDH 12/01/00 	int fighters = Todays_Packages.taskdata.acttached_no + Todays_Packages.taskdata.detached_no;
//DEADCODE RDH 12/01/00 	int percent =  fighters/(fighters+Todays_Packages.taskdata.strike_no);
//DEADCODE RDH 12/01/00 	spinbut->Clear()->MakeNumList(100,0,1)->SetIndex(percent);

	CRStatic*   s;
	s=GETDLGITEM(IDC_TARGETS);
	s->SetString(CSprintf("%i",	Todays_Packages.taskdata.targetnum));

	int fighters = Todays_Packages.taskdata.totalfighter.acnum;
	int fightersquads = Todays_Packages.taskdata.totalfighter.squadnum;
//DEADCODE RDH 24/03/00 	bool squads = false;
//DEADCODE RDH 24/03/00 		
//DEADCODE RDH 24/03/00 	if (Todays_Packages.taskdata.returned.acnum == -1)
//DEADCODE RDH 24/03/00 	{
//DEADCODE RDH 24/03/00 		fightersquads +=Todays_Packages.taskdata.returned.squadnum;
//DEADCODE RDH 24/03/00 		squads = true;
//DEADCODE RDH 24/03/00 	}else
//DEADCODE RDH 24/03/00 		fighters +=Todays_Packages.taskdata.returned.acnum;
//DEADCODE RDH 24/03/00 
//DEADCODE RDH 24/03/00 	if (Todays_Packages.taskdata.attached.acnum == -1)
//DEADCODE RDH 24/03/00 	{
//DEADCODE RDH 24/03/00 		fightersquads +=Todays_Packages.taskdata.attached.squadnum;
//DEADCODE RDH 24/03/00 		squads = true;
//DEADCODE RDH 24/03/00 	}else
//DEADCODE RDH 24/03/00 		fighters +=Todays_Packages.taskdata.attached.acnum;
//DEADCODE RDH 24/03/00 
//DEADCODE RDH 24/03/00 	if (Todays_Packages.taskdata.detached.acnum == -1)
//DEADCODE RDH 24/03/00 	{
//DEADCODE RDH 24/03/00 		fightersquads +=Todays_Packages.taskdata.detached.squadnum;
//DEADCODE RDH 24/03/00 		squads = true;
//DEADCODE RDH 24/03/00 	}else
//DEADCODE RDH 24/03/00 		fighters +=Todays_Packages.taskdata.detached.acnum;
//DEADCODE RDH 24/03/00 
//DEADCODE RDH 24/03/00 	if (squads)
//DEADCODE RDH 24/03/00 	{
//DEADCODE RDH 24/03/00 		fighters = -1;
//DEADCODE RDH 24/03/00 		if (Todays_Packages.taskdata.returned.acnum > 0)
//DEADCODE RDH 24/03/00 			fightersquads ++;
//DEADCODE RDH 24/03/00 
//DEADCODE RDH 24/03/00 		if (Todays_Packages.taskdata.attached.acnum > 0)
//DEADCODE RDH 24/03/00 			fightersquads ++;
//DEADCODE RDH 24/03/00 
//DEADCODE RDH 24/03/00 		if (Todays_Packages.taskdata.detached.acnum > 0)
//DEADCODE RDH 24/03/00 			fightersquads ++;
//DEADCODE RDH 24/03/00 	}

//DEADCODE RDH 04/04/00 	int strikeac = Todays_Packages.taskdata.strike.realacnum;
//DEADCODE RDH 04/04/00 	int fighter_pc = fighters;
//DEADCODE RDH 04/04/00 	if ((strikeac == -1) || (fighters == -1))
//DEADCODE RDH 04/04/00 	{
//DEADCODE RDH 04/04/00 		if (fightersquads <= 0)
//DEADCODE RDH 04/04/00 			fightersquads = 1;
//DEADCODE RDH 04/04/00 		if (strikesquads <= 0 )
//DEADCODE RDH 04/04/00 			strikesquads = 1;
//DEADCODE RDH 04/04/00 		strike_pc = strikesquads;
//DEADCODE RDH 04/04/00 		fighter_pc = fightersquads; 
//DEADCODE RDH 04/04/00 	}
//DEADCODE RDH 04/04/00 
		
	int percent =  100* Todays_Packages.taskdata.totalfighter.realacnum
						/(Todays_Packages.taskdata.totalfighter.realacnum+Todays_Packages.taskdata.strike.realacnum);

	s=GETDLGITEM(IDC_PC_FIGHTERS);
	s->SetString(CSprintf("%i",	percent));

//DeadCode JIM 30Oct00 	if (fighters)
//DeadCode JIM 30Oct00 	{
//DeadCode JIM 30Oct00 		s=GETDLGITEM(IDC_PC_ATTACHED);
//DeadCode JIM 30Oct00 		s->SetString(CSprintf("%i",	100 * Todays_Packages.taskdata.attached.realacnum
//DeadCode JIM 30Oct00 					/Todays_Packages.taskdata.totalfighter.realacnum ));
//DeadCode JIM 30Oct00 
//DeadCode JIM 30Oct00 		s=GETDLGITEM(IDC_PC_DETACHED);
//DeadCode JIM 30Oct00 		s->SetString(CSprintf("%i",	100 * Todays_Packages.taskdata.detached.realacnum
//DeadCode JIM 30Oct00 					/Todays_Packages.taskdata.totalfighter.realacnum ));
//DeadCode JIM 30Oct00 
//DeadCode JIM 30Oct00 		s=GETDLGITEM(IDC_PC_RETURNING);
//DeadCode JIM 30Oct00 		s->SetString(CSprintf("%i",	100 * Todays_Packages.taskdata.returned.realacnum
//DeadCode JIM 30Oct00 					/Todays_Packages.taskdata.totalfighter.realacnum ));
//DeadCode JIM 30Oct00 	}else
//DeadCode JIM 30Oct00 	{
//DeadCode JIM 30Oct00 		s=GETDLGITEM(IDC_PC_ATTACHED);
//DeadCode JIM 30Oct00 		s->SetString(RESSTRING(NA));
//DeadCode JIM 30Oct00 
//DeadCode JIM 30Oct00 		s=GETDLGITEM(IDC_PC_DETACHED);
//DeadCode JIM 30Oct00 		s->SetString(RESSTRING(NA));
//DeadCode JIM 30Oct00 
//DeadCode JIM 30Oct00 		s=GETDLGITEM(IDC_PC_RETURNING);
//DeadCode JIM 30Oct00 		s->SetString(RESSTRING(NA));
//DeadCode JIM 30Oct00 
//DeadCode JIM 30Oct00 	}

  	spinbut=GETDLGITEM(IDC_RSPINBUT_BOMBERS);
	spinbut->Clear();

	int maxac =12;
	//..strike.maxac should either be <12 or -1. -1 means that we are counting in squads
	if (Todays_Packages.taskdata.strike.maxac != -1)
		maxac = Todays_Packages.taskdata.strike.maxac;
//DeadCode JIM 16Oct00 	if (maxac>12*3*3*5)
//DeadCode JIM 16Oct00 		maxac=12*3*3*5;
	int index = 0;
	int entry = 0;
	while (AcSpin[entry] <= maxac)
	{
		spinbut->AddString(CSprintf("%i %s", AcSpin[entry], RESSTRING(AIRCRAFT)));
		if  (	(Todays_Packages.taskdata.strike.acnum != -1)
			&&	(Todays_Packages.taskdata.strike.acnum >= AcSpin[entry])
			)
			spinbut->SetIndex(index);
		index++;
		entry++;
	}

	if  (Todays_Packages.taskdata.strike.maxac == -1)
	{
		entry = 0;
		if (Todays_Packages.taskdata.strike.maxsquad>3*3*5)		//JIM 16Oct00
			Todays_Packages.taskdata.strike.maxsquad=3*3*5;
		while (squadinfo[entry].numofsquads <= Todays_Packages.taskdata.strike.maxsquad)
		{
			spinbut->AddString(CSprintf("%i %s", squadinfo[entry].number, LoadResString(squadinfo[entry].name)));
			if  (	(Todays_Packages.taskdata.strike.acnum == -1)
				&&	(Todays_Packages.taskdata.strike.squadnum >= squadinfo[entry].numofsquads)
				)
				spinbut->SetIndex(index);

			entry++;
			index++;
		}
	}
 
  	spinbut=GETDLGITEM(IDC_RSPINBUT_FIGHTERS);
	spinbut->Clear();
	

	 maxac =12;
	if (Todays_Packages.taskdata.attached.maxac != -1)
		maxac = Todays_Packages.taskdata.attached.maxac;


	index = 0;
	entry = 0;
	while (FighterSpin[entry] <= maxac)
	{
		spinbut->AddString(CSprintf("%i %s", FighterSpin[entry], RESSTRING(AIRCRAFT)));
		if  (	(fighters != -1)
			&&	(fighters >= FighterSpin[entry])
			)
		{
			spinbut->SetIndex(index);
			oldindex = index;
		}
		index++;
		entry++;
	}

	if  (Todays_Packages.taskdata.attached.maxac == -1)
	{
		entry = 0;
		while (squadinfo[entry].numofsquads <= Todays_Packages.taskdata.attached.maxsquad)
		{
			spinbut->AddString(CSprintf("%i %s", squadinfo[entry].number, LoadResString(squadinfo[entry].name)));
			if  (	(fighters == -1)
				&&	(fightersquads >= squadinfo[entry].numofsquads)
				)
			{
				spinbut->SetIndex(index);
	 			oldindex = index;
			}

			entry++;
			index++;
		}
	}




	CRCombo* combo;
	combo=GETDLGITEM(IDC_RCOMBOBOMBERTYPE);
	combo->Clear();
	int i = 0;
	while	( i < PackageList::STRIKEOPTIONS)
	{	
		if (Todays_Packages.taskdata.strikeactypes[i] != PackageList::NOTDEFINED)
		{
			if (Todays_Packages.taskdata.strikeactypes[i] == PackageList::MIXED)
				combo->AddString(RESSTRING(MIXED));
			else
				combo->AddString(RESLIST(SPIT_A, Todays_Packages.taskdata.strikeactypes[i]));
		}
		i++;
	};
	combo->SetIndex(0);

 	combo=GETDLGITEM(IDC_RCOMBOFIGHTERTYPE);
	if (fighters)
	{
		combo->Clear();
		int i = 0;
		while	(		( i < PackageList::ESCORTOPTIONS)
				&&	(Todays_Packages.taskdata.escortactypes[i] != PackageList::NOTDEFINED)
			)
		{	
			if (Todays_Packages.taskdata.escortactypes[i] == PackageList::MIXED)
				combo->AddString(RESSTRING(MIXED));
			else
				combo->AddString(RESLIST(SPIT_A, Todays_Packages.taskdata.escortactypes[i]));
			i++;
		};
		combo->SetIndex(0);

	}else
	{
		combo->Clear()->SetList(IDS_NO_AIRCRAFT,1)->
					SetIndex(0);

	}



}
BOOL LWTaskSummary::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GETDLGITEM(IDC_SPC_RETURNING)->EnableWindow(false);
	MakeFighterSpinLists(true);
	Refresh();


	 



	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(LWTaskSummary, CDialog)
    //{{AFX_EVENTSINK_MAP(LWTaskSummary)
	ON_EVENT(LWTaskSummary, IDC_RCOMBOBOMBERTYPE, 1 /* TextChanged */, OnTextChangedRcombobombertype, VTS_BSTR VTS_I2)
	ON_EVENT(LWTaskSummary, IDC_RCOMBOFIGHTERTYPE, 1 /* TextChanged */, OnTextChangedRcombofightertype, VTS_BSTR VTS_I2)
	ON_EVENT(LWTaskSummary, IDC_RSPINBUT_BOMBERS, 1 /* TextChanged */, OnTextChangedRspinbutBombers, VTS_BSTR VTS_I2)
	ON_EVENT(LWTaskSummary, IDC_RSPINBUT_FIGHTERS, 1 /* TextChanged */, OnTextChangedRspinbutFighters, VTS_BSTR VTS_I2)
//DeadCode JIM 30Oct00 	ON_EVENT(LWTaskSummary, IDC_TICK_MAINTAIN_PC, 1 /* Clicked */, OnClickedTickMaintainPc, VTS_NONE)
	ON_EVENT(LWTaskSummary, IDC_SPC_ATTACHED, 1 /* TextChanged */, OnTextChangedRspinbutSpcAttached, VTS_BSTR VTS_I2)
	ON_EVENT(LWTaskSummary, IDC_SPC_DETACHED, 1 /* TextChanged */, OnTextChangedRspinbutSpcDetached, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
typedef	Profile::AttackMethod	AttackMethod;
MAKEFIELD(AttackMethod,Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);

void LWTaskSummary::OnTextChangedRcombobombertype(LPCTSTR Caption, short index) 
{
	int actype = Todays_Packages.taskdata.strikeactypes[index];
	if (Todays_Packages.taskdata.strikeactypes[index] == PackageList::MIXED)
		Todays_Packages.taskdata.mixedstrikeset = true;
	else
	{
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
		Todays_Packages.InvalidateRoute(&pk,true,true);
		pk.ChangeStrikeAcType(actype);
		pk.ReShareSecondaries();												//JIM 28Aug00
		AttackMethodField	am=pk.ScanAttackMethods();
		pk.ReorderPackage(am);
		pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
		Todays_Packages.InvalidateRoute(&pk,true,true);
 	}

	Todays_Packages.SetTaskData();
	Refresh();
	MakeFighterSpinLists(false);
	
}

void LWTaskSummary::OnTextChangedRcombofightertype(LPCTSTR Caption, short index) 
{
	Todays_Packages.taskdata.mixedescortset = false;
	int actype = Todays_Packages.taskdata.escortactypes[index];
	if (actype == PackageList::MIXED)
		Todays_Packages.taskdata.mixedescortset = true;
	else
		if (index>0)
		{
			Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
			Todays_Packages.InvalidateRoute(&pk,true,true);
			for (int a=Profile::AM_ESCORTTYPES;a<=Profile::AM_RETURNESCORT;a+=Profile::AM_FIELD_MIN)
			{
				int numac=0,numstaff=0;
				Profile::SubMethod reqsubmethod=Profile::SM_ANYA2A;
				for (int s=0,max=pk.squadlist;s<max;s++)
					if ((pk[s].method&Profile::AM_GROUPMASK)==a)
					{
						if (numac)
							numstaff++;
						else
						{
							numac=pk[s].numacoriginal;
							reqsubmethod=pk[s].submethod;
						}
					}
				if (numstaff && numac)
				{
					numstaff++;
					numac=0;
				}
				numac=numac-numstaff;	//one should be zero
				if (numac)
				{
					Profile::BetterRule	br=Profile::BR_R_109FONLY;
					if (actype!=PT_ME109)
						br=Profile::BR_R_110FONLY;
			 		pk.DeleteNumerousSquadrons(Profile::AttackMethod(a));
					pk.AddNumerousSquadrons(numac,Profile::AttackMethod(a),SQ_ZERO,br);
					pk.SetSubMethod((Profile::AttackMethod)a,reqsubmethod);	//RDH 02/04/00
				}
			}
//DeadCode JIM 30Oct00 			pk.ReShareSecondaries();												//JIM 28Aug00
			AttackMethodField	am2=pk.ScanAttackMethods();
			pk.ReorderPackage(am2);
			pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
			Todays_Packages.InvalidateRoute(&pk,true,true);
		}
//		function to change actype
	Todays_Packages.SetTaskData();
	Refresh();
	MakeFighterSpinLists(false);
									
}

void LWTaskSummary::OnTextChangedRspinbutBombers(LPCTSTR caption, short Index) 
{
	int maxac =12;
	if (Todays_Packages.taskdata.strike.maxac != -1)
		maxac = Todays_Packages.taskdata.strike.maxac;

	int acreq = 0;
	int squadreq = 0;

	int index = -1;
	int entry = 0;
	while (		(AcSpin[entry] <= maxac)								//JIM 16Oct00
			&&	(index != Index)
		  )
	{
		index++;
		if (index == Index)
			acreq = AcSpin[entry];
		entry++;
	}

	if (index != Index)
	{
		acreq = -1;
		entry = 0;
		while	(		(squadinfo[entry].numofsquads <= Todays_Packages.taskdata.strike.maxsquad)
					&&	(index != Index)
				)
		{
			index++;
			if (index == Index)
				squadreq = squadinfo[entry].numofsquads;
			entry++;
		}
	}

	int orggrp, reqgrp, deltaac;
	if (	(acreq >=0)	||	(squadreq <3))
		reqgrp = 0;
	else
		reqgrp = squadreq/3;

	if (	(Todays_Packages.taskdata.strike.acnum >=0)	||	(Todays_Packages.taskdata.strike.squadnum <3))
		orggrp = 0;
	else
		orggrp = Todays_Packages.taskdata.strike.squadnum/3;
	if (reqgrp < 1)
	{
		if (acreq >=0)
			deltaac = acreq ;
		else
			deltaac = squadreq * 12 ;
	}else
		deltaac = -1;
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	Todays_Packages.InvalidateRoute(&pk,true,true);
	pk.ResetAcNumbers((Profile::AttackMethod)Todays_Packages.taskdata.attackmethod, orggrp, reqgrp, deltaac);
//TEMPCODE RDH 02/04/00 	if (oldindex > Index)
//TEMPCODE RDH 02/04/00 	{//	add aircraft rqeuired function
//TEMPCODE RDH 02/04/00 		if(Index >=LWTaskSummary::ACMAX)
//TEMPCODE RDH 02/04/00 		{//now adding staffel or more
//TEMPCODE RDH 02/04/00 			if ( oldindex < LWTaskSummary::ACMAX)
//TEMPCODE RDH 02/04/00 			{//was adding singles
//TEMPCODE RDH 02/04/00 			}else
//TEMPCODE RDH 02/04/00 			{//was adding staffel or more
//TEMPCODE RDH 02/04/00 			}
//TEMPCODE RDH 02/04/00 		}else
//TEMPCODE RDH 02/04/00 		{//still adding singles
//TEMPCODE RDH 02/04/00 			acreq = AcSpin[Index];
//TEMPCODE RDH 02/04/00 		}
//TEMPCODE RDH 02/04/00 	}
	//subtract aircraft function required
//	if  acreq != -1
//		use acreq
//	else
//		iuse squadreq

//DEADCODE RDH 02/04/00 		{
//DEADCODE RDH 02/04/00 		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
//DEADCODE RDH 02/04/00 
//DEADCODE RDH 02/04/00 		int j = 0, k = 0;
//DEADCODE RDH 02/04/00 		while  (		(Node_Data.gruppe[j].squadron != SQ_ZERO)
//DEADCODE RDH 02/04/00 					&&		(k != l_newunit)
//DEADCODE RDH 02/04/00 				)
//DEADCODE RDH 02/04/00 		{
//DEADCODE RDH 02/04/00 			if SqIsAvail(j, acisfighter)
//DEADCODE RDH 02/04/00 			{
//DEADCODE RDH 02/04/00 				k++;
//DEADCODE RDH 02/04/00 			}
//DEADCODE RDH 02/04/00 			j++;
//DEADCODE RDH 02/04/00 		}
//DEADCODE RDH 02/04/00 		j = j + SQ_LW_START;
//DEADCODE RDH 02/04/00 
//DEADCODE RDH 02/04/00 		
//DEADCODE RDH 02/04/00 		if ( oldunit < 0)
//DEADCODE RDH 02/04/00 		{//add unit to package
//DEADCODE RDH 02/04/00 			pk.AddSquadron(-1, (Profile::AttackMethod)attackmethod,pk.packagetarget[0].currentid,(SquadNum)j);
//DEADCODE RDH 02/04/00 
//DEADCODE RDH 02/04/00 
	pk.ReShareSecondaries();												//JIM 28Aug00
	AttackMethodField	am=pk.ScanAttackMethods();
	pk.ReorderPackage(am);
	pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
	Todays_Packages.InvalidateRoute(&pk,true,true);
	Todays_Packages.SetTaskData();


		//now check whether mixed should be reset

	if (Todays_Packages.taskdata.mixedstrikeset)
	{
		bool mixed = false;
		int i = pk.FirstSquadofMethod(Profile::AM_LWPACKS);
		if (i < pk.squadlist)
		{
			int staffel, actype;
			int firstactype;
			staffel = pk[i].squadnum;
			firstactype = Node_Data[(SquadNum)staffel].AcType();
			while (i < pk.squadlist)
			{
				if (Profile::AM_LWPACKS == (pk[i].method&Profile::AM_GROUPMASK))
				{
					staffel = pk[i].squadnum;
					actype = Node_Data[(SquadNum)staffel].AcType();
					if (actype != firstactype)
						mixed = true;
				}
				i++;
			}
			if (!mixed)
			{
				Todays_Packages.taskdata.mixedstrikeset = false;
				Todays_Packages.SetTaskData();

			}
		}
	}






	Refresh();
	MakeFighterSpinLists(false);
	
}

void LWTaskSummary::OnTextChangedRspinbutFighters(LPCTSTR caption, short Index) 
{
	int maxac =12;
	if (Todays_Packages.taskdata.attached.maxac != -1)
		maxac = Todays_Packages.taskdata.attached.maxac;

	int acreq = 0;
	int squadreq = 0;

	int index = -1;
	int entry = 0;
	while (		(FighterSpin[entry] < maxac)
			&&	(index != Index)
		  )
	{
		index++;
		if (index == Index)
			acreq = FighterSpin[entry];
		entry++;
	}

	if (index != Index)
	{
		acreq = -1;
		entry = 0;
		while (	(index != Index)	)
//DeadCode JIM 30Oct00 			(squadinfo[entry].numofsquads <= Todays_Packages.taskdata.attached.maxsquad)	&&	
		{
			index++;
			if (index == Index)
				squadreq = squadinfo[entry].numofsquads;
			entry++;
		}
	}

	int orggrp, reqgrp, deltaac;
//DeadCode JIM 30Oct00 	if (	(acreq >0))
//DeadCode JIM 30Oct00 		reqgrp = 0;
//DeadCode JIM 30Oct00 	else
//DeadCode JIM 30Oct00 		reqgrp = squadreq/3;
	Profile::AttackMethod	changemethod=Profile::AM_RETURNESCORT;
	int currstaffeln;
	int deltastaffeln=squadreq-totalfighterstaffeln;
	if (squadreq)
	{
		float	currlevel=1.0-(attachedfraccurr+detachedfraccurr);
		if (deltastaffeln>0)
		{
			if (attachedfraccurr<=attachedfracreq && attachedfracreq!=0)
			{
				changemethod=Profile::AM_ATTACHED;
				currlevel=attachedfraccurr;
			}
			else
			if (detachedfraccurr<=detachedfracreq && detachedfracreq!=0)
			{
				changemethod=Profile::AM_DETACHED;
				currlevel=detachedfraccurr;
			}
		}
		else
		if (deltastaffeln<0)	//Do nowt if zero
		{
			if (attachedfraccurr>=attachedfracreq && attachedfraccurr!=0)
			{
				changemethod=Profile::AM_ATTACHED;
				currlevel=attachedfraccurr;
			}
			else
			if (detachedfraccurr>=detachedfracreq && detachedfraccurr!=0)
			{
				changemethod=Profile::AM_DETACHED;
				currlevel=detachedfraccurr;
			}
		}
		else
			return;	//NOTHING ACTUALLY HAPPENED!!!!!
		currstaffeln=totalfighterstaffeln*currlevel+0.00000001;
	}
	else										//Less than 1 grupp total
		if (attachedfraccurr>0.00001)			//So 'up' any duty
			changemethod=Profile::AM_ATTACHED;
		else
		if (detachedfraccurr>0.00001)
			changemethod=Profile::AM_DETACHED;

	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	Todays_Packages.InvalidateRoute(&pk,true,true);

	if (squadreq)
	{

		if (deltastaffeln<0)
			if (currstaffeln<-deltastaffeln)
			{	//Need to get rid of something else... don't care what!
				int otherdelta=deltastaffeln+currstaffeln;
				deltastaffeln=-currstaffeln;
				if (otherdelta && changemethod!=Profile::AM_ATTACHED && attachedfraccurr>0.000001)
				{
					int currstaffeln=attachedfraccurr*totalfighterstaffeln+0.00000001;
					if (currstaffeln>-otherdelta)
					{
			 			pk.DeleteNumerousSquadrons(Profile::AM_DETACHED,-otherdelta);
						otherdelta=0;
					}
					else
					{
			 			pk.DeleteNumerousSquadrons(Profile::AM_DETACHED);
						otherdelta+=currstaffeln;
					}
				}
				if (otherdelta && changemethod!=Profile::AM_DETACHED && detachedfraccurr>0.000001)
				{
					int currstaffeln=detachedfraccurr*totalfighterstaffeln+0.00000001;
					if (currstaffeln>-otherdelta)
					{
			 			pk.DeleteNumerousSquadrons(Profile::AM_ATTACHED,-otherdelta);
						otherdelta=0;
					}
					else
					{
			 			pk.DeleteNumerousSquadrons(Profile::AM_ATTACHED);
						otherdelta+=currstaffeln;
					}
				}
				if (otherdelta && changemethod!=Profile::AM_RETURNESCORT)
				{
					int currstaffeln=(1.0-attachedfraccurr-detachedfraccurr)*totalfighterstaffeln+0.00000001;
					if (currstaffeln>-otherdelta)
					{
			 			pk.DeleteNumerousSquadrons(Profile::AM_RETURNESCORT,-otherdelta);
						otherdelta=0;
					}
					else
					{
			 			pk.DeleteNumerousSquadrons(Profile::AM_RETURNESCORT);
						otherdelta+=currstaffeln;
						INT3;
					}
				}
			}
		if (pk.squadlist==1 && (pk.squadlist[0].method&Profile::AM_GROUPMASK)!=changemethod)
			pk.ResetAcNumbers(Profile::AttackMethod(pk.squadlist[0].method&Profile::AM_GROUPMASK), 0, 0,10);
		if (currstaffeln+deltastaffeln<3)
			pk.ResetAcNumbers(changemethod, 0, 0,(currstaffeln+deltastaffeln)*10);
		else
			pk.ResetAcNumbers(changemethod, currstaffeln/3, (currstaffeln+deltastaffeln)/3, 0);
	}
	else
		pk.ResetAcNumbers(changemethod, 0, 0, acreq);

//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 	if (	(Todays_Packages.taskdata.totalfighter.acnum >=0)	||	(Todays_Packages.taskdata.totalfighter.squadnum <3))
//DeadCode JIM 28Oct00 		orggrp = 0;
//DeadCode JIM 28Oct00 	else
//DeadCode JIM 28Oct00 		orggrp = Todays_Packages.taskdata.totalfighter.squadnum/3;
//DeadCode JIM 28Oct00 	if (reqgrp < 1)
//DeadCode JIM 28Oct00 	{
//DeadCode JIM 28Oct00 		if (acreq >=0)
//DeadCode JIM 28Oct00 			deltaac = acreq ;
//DeadCode JIM 28Oct00 		else
//DeadCode JIM 28Oct00 			deltaac = squadreq * 12 ;
//DeadCode JIM 28Oct00 	}else
//DeadCode JIM 28Oct00 		deltaac = -1;
//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 	//find the lowest and highest non zero esort type
//DeadCode JIM 28Oct00 	int i = 0;
//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 	if (
//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 	enum	{DETACHED, ATTACHED, RETURNED, MAXESCORT};
//DeadCode JIM 28Oct00 	int fighter[3];
//DeadCode JIM 28Oct00 	for (i=0; i < MAXESCORT; i++)
//DeadCode JIM 28Oct00 		fighter[i] = 0;
//DeadCode JIM 28Oct00 	i = 0;
//DeadCode JIM 28Oct00 	while (i < pk.squadlist)
//DeadCode JIM 28Oct00  	{
//DeadCode JIM 28Oct00 		if	((pk[i].method&Profile::AM_GROUPMASK) == Profile::AM_DETACHED)
//DeadCode JIM 28Oct00 			fighter[DETACHED]++;
//DeadCode JIM 28Oct00 		if	((pk[i].method&Profile::AM_GROUPMASK) == Profile::AM_ATTACHED)
//DeadCode JIM 28Oct00 			fighter[ATTACHED]++;
//DeadCode JIM 28Oct00 		if	((pk[i].method&Profile::AM_GROUPMASK) == Profile::AM_RETURNESCORT)
//DeadCode JIM 28Oct00 			fighter[RETURNED]++;
//DeadCode JIM 28Oct00 		i++;
//DeadCode JIM 28Oct00 	}
//DeadCode JIM 28Oct00 	int lowestescortnumber = 255; 
//DeadCode JIM 28Oct00 	int lowestescorttype = DETACHED;
//DeadCode JIM 28Oct00 	int highestescortnumber = -1; 
//DeadCode JIM 28Oct00 	int highestescorttype = DETACHED;
//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 	for (i=0; i < MAXESCORT; i++)
//DeadCode JIM 28Oct00 	{
//DeadCode JIM 28Oct00 		if 	((fighter[i]!=0) &&	(fighter[i] < lowestescortnumber) )
//DeadCode JIM 28Oct00 		{
//DeadCode JIM 28Oct00 			 lowestescorttype = i;
//DeadCode JIM 28Oct00 			 lowestescortnumber = fighter[i];
//DeadCode JIM 28Oct00 		}
//DeadCode JIM 28Oct00 		if 	(fighter[i] >= highestescortnumber)
//DeadCode JIM 28Oct00 		{
//DeadCode JIM 28Oct00 			 highestescorttype = i;
//DeadCode JIM 28Oct00 			 highestescortnumber = fighter[i];
//DeadCode JIM 28Oct00 		}
//DeadCode JIM 28Oct00 	}
//DeadCode JIM 28Oct00 	int am;
//DeadCode JIM 28Oct00 	if (orggrp <= reqgrp)
//DeadCode JIM 28Oct00 		am =  Profile::AM_ESCORTTYPES  +  (Profile::AM_FIELD_MIN *lowestescorttype); 
//DeadCode JIM 28Oct00 	else
//DeadCode JIM 28Oct00 		am =  Profile::AM_ESCORTTYPES  +  (Profile::AM_FIELD_MIN *highestescorttype); 
//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 	if (orggrp < 1)
//DeadCode JIM 28Oct00 	{
//DeadCode JIM 28Oct00 		if (am != Profile::AM_DETACHED)
//DeadCode JIM 28Oct00 			pk.DeleteNumerousSquadrons(Profile::AM_DETACHED);
//DeadCode JIM 28Oct00 		if (am != Profile::AM_ATTACHED)
//DeadCode JIM 28Oct00 			pk.DeleteNumerousSquadrons(Profile::AM_ATTACHED);
//DeadCode JIM 28Oct00 		if (am != Profile::AM_RETURNESCORT)
//DeadCode JIM 28Oct00 			pk.DeleteNumerousSquadrons(Profile::AM_RETURNESCORT);
//DeadCode JIM 28Oct00 	}
//DeadCode JIM 28Oct00 
//DeadCode JIM 28Oct00 	pk.ResetAcNumbers((Profile::AttackMethod)am, orggrp, reqgrp, deltaac);
//DeadCode JIM 28Oct00 	pk.ReShareSecondaries();												//JIM 28Aug00
	AttackMethodField	am2=pk.ScanAttackMethods();
	pk.ReorderPackage(am2);
	pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
	Todays_Packages.InvalidateRoute(&pk,true,true);
	Todays_Packages.SetTaskData();

	//now check whether mixed should be reset

	if (Todays_Packages.taskdata.mixedescortset)
	{
		bool mixed = false;
		int i = pk.FirstSquadNotofMethod(Profile::AM_LWPACKS);
		if (i < pk.squadlist)
		{
			int staffel, actype;
			int firstactype;
			staffel = pk[i].squadnum;
			firstactype = Node_Data[(SquadNum)staffel].AcType();
			while (i < pk.squadlist)
			{
				if (Profile::AM_LWPACKS != (pk[i].method&Profile::AM_GROUPMASK))
				{
					staffel = pk[i].squadnum;
					actype = Node_Data[(SquadNum)staffel].AcType();
					if (actype != firstactype)
						mixed = true;
				}
				i++;
			}
			if (!mixed)
			{
				Todays_Packages.taskdata.mixedescortset = false;
				Todays_Packages.SetTaskData();
			}
		}
	}
	Refresh();
	MakeFighterSpinLists(false);
	
}
void	LWTaskSummary::MakeFighterSpinLists(bool setreq)
{	//sorts out percentages and step sizes
	//First count number of squads
	int	dutycount[5]={0};
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	for (int i=0,max=pk.squadlist;i<max;i++)
		dutycount[pk.squadlist[i].method/Profile::AM_FIELD_MIN]++;
	totalfighterstaffeln=dutycount[2]+dutycount[3]+dutycount[4];
	attachedfraccurr=float(dutycount[3])/totalfighterstaffeln;
	detachedfraccurr=float(dutycount[2])/totalfighterstaffeln;
	Float	returnfraccurr=float(dutycount[4])/totalfighterstaffeln;
	if (setreq)
	{
		attachedfracreq=attachedfraccurr;
		detachedfracreq=detachedfraccurr;
	}
	if (dutycount[2]>3||dutycount[3]>3||dutycount[4]>3)
		if (totalfighterstaffeln<60)
			stepsize=3.0/totalfighterstaffeln;
		else
			stepsize=0.05;
	else
		stepsize=1.0/totalfighterstaffeln;

	GETDLGITEM(IDC_SPC_ATTACHED)->Clear();	
	GETDLGITEM(IDC_SPC_DETACHED)->Clear();
	GETDLGITEM(IDC_SPC_RETURNING)->Clear();
	int index=0,attindex=0,detindex=0,retindex=0;
	if (totalfighterstaffeln)
	{
		for (Float v=0;v<=1.000001;v=v+stepsize,index++)
		{	
			int dispval=5*int(0.5+20.0*v);
			float	u=dispval*0.01-stepsize*0.5,
					w=dispval*0.01+stepsize*0.5;
			CString disp=CSprintf("%3i",dispval);
			GETDLGITEM(IDC_SPC_ATTACHED)->AddString(disp);	
			GETDLGITEM(IDC_SPC_DETACHED)->AddString(disp);
			GETDLGITEM(IDC_SPC_RETURNING)->AddString(disp);
			if (u<=attachedfraccurr && w>attachedfraccurr)
				attindex=index;
			if (u<=detachedfraccurr && w>detachedfraccurr)
				detindex=index;
			if (u<=returnfraccurr && w>returnfraccurr)
				retindex=index;
		}
	}
	else
	{
			GETDLGITEM(IDC_SPC_ATTACHED)->AddString("-");	
			GETDLGITEM(IDC_SPC_DETACHED)->AddString("-");
			GETDLGITEM(IDC_SPC_RETURNING)->AddString("-");
	}

	GETDLGITEM(IDC_SPC_ATTACHED)->SetIndex(attindex);	
	GETDLGITEM(IDC_SPC_DETACHED)->SetIndex(detindex);
	GETDLGITEM(IDC_SPC_RETURNING)->SetIndex(retindex);

}
void LWTaskSummary::OnTextChangedRspinbutSpcAttached(LPCTSTR caption, short Index) 
{
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	Float newval=Index*stepsize;
	if (newval<=0 && attachedfraccurr>=0)
		return;
	if (newval>=1.0 && attachedfraccurr>=1.0)
		return;
	Profile::AttackMethod toincrease,todecrease;
	int returncount=totalfighterstaffeln-int((attachedfraccurr+detachedfraccurr)*totalfighterstaffeln+0.5);
	int	decreasecount=(attachedfraccurr*totalfighterstaffeln+0.5),increasecount=decreasecount;
	if (newval<attachedfraccurr)
	{
		increasecount=returncount;
		toincrease=Profile::AM_RETURNESCORT;
		todecrease=Profile::AM_ATTACHED;
	}
	else
	{
		toincrease=Profile::AM_ATTACHED;
		if (1.0-detachedfraccurr>=newval)
		{
			todecrease=Profile::AM_RETURNESCORT;
			decreasecount=returncount;
		}
		else
		{
			if (returncount)
				pk.ResetAcNumbers(Profile::AM_RETURNESCORT, 0, 0, 0);
			decreasecount=(detachedfraccurr*totalfighterstaffeln+0.5);
			todecrease=Profile::AM_DETACHED;
		}
	}
	int	numtochange=stepsize*totalfighterstaffeln+0.000001;
	Todays_Packages.InvalidateRoute(&pk,true,true);
	if (numtochange>=3)
	{
		pk.ResetAcNumbers(toincrease, increasecount/3, increasecount/3+1, -1);
		pk.ResetAcNumbers(todecrease, decreasecount/3, decreasecount/3-1, -1);
	}
	else
	{
		if (totalfighterstaffeln>1)
		{
			pk.ResetAcNumbers(toincrease,0, 0, increasecount*10+10*numtochange);
			pk.ResetAcNumbers(todecrease,0, 0, decreasecount*10-10*numtochange);
		}
		else
		{
			int	numac=pk.squadlist[0].numacoriginal;
			pk.ResetAcNumbers(toincrease,0, 0, numac);
			pk.ResetAcNumbers(todecrease,0, 0, 0);
		}
	}
	AttackMethodField	am2=pk.ScanAttackMethods();
	pk.ReorderPackage(am2);
	pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
	Todays_Packages.InvalidateRoute(&pk,true,true);
	Todays_Packages.SetTaskData();
	MakeFighterSpinLists(true);
}
void LWTaskSummary::OnTextChangedRspinbutSpcDetached(LPCTSTR caption, short Index) 
{
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	Float newval=Index*stepsize;
	if (newval<=0 && detachedfraccurr<=0)
		return;
	if (newval>=1.0 && detachedfraccurr>=1.0)
		return;
	Profile::AttackMethod toincrease,todecrease;
	int returncount=totalfighterstaffeln-int((attachedfraccurr+detachedfraccurr)*totalfighterstaffeln+0.5);
	int	decreasecount=(detachedfraccurr*totalfighterstaffeln+0.5),increasecount=decreasecount;
	if (newval<detachedfraccurr)
	{
		increasecount=returncount;
		toincrease=Profile::AM_RETURNESCORT;
		todecrease=Profile::AM_DETACHED;
	}
	else
	{
		toincrease=Profile::AM_DETACHED;
		if (1.0-attachedfraccurr>=newval)
		{
			todecrease=Profile::AM_RETURNESCORT;
			decreasecount=returncount;
		}
		else
		{
			if (returncount)
				pk.ResetAcNumbers(Profile::AM_RETURNESCORT, 0, 0, 0);
			decreasecount=(attachedfraccurr*totalfighterstaffeln+0.5);
			todecrease=Profile::AM_ATTACHED;
		}
	}
	int	numtochange=stepsize*totalfighterstaffeln+0.0000001;
	Todays_Packages.InvalidateRoute(&pk,true,true);
	if (numtochange>=3)
	{
		pk.ResetAcNumbers(toincrease, increasecount/3, increasecount/3+1, -1);
		pk.ResetAcNumbers(todecrease, decreasecount/3, decreasecount/3-1, -1);
	}
	else
	{
		if (totalfighterstaffeln>1)
		{
			pk.ResetAcNumbers(toincrease,0, 0, increasecount*10+10*numtochange);
			pk.ResetAcNumbers(todecrease,0, 0, decreasecount*10-10*numtochange);
		}
		else
		{
			int	numac=pk.squadlist[0].numacoriginal;
			pk.ResetAcNumbers(toincrease,0, 0, numac);
			pk.ResetAcNumbers(todecrease,0, 0, 0);
		}
	}
	AttackMethodField	am2=pk.ScanAttackMethods();
	pk.ReorderPackage(am2);
	pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
	Todays_Packages.InvalidateRoute(&pk,true,true);
	Todays_Packages.SetTaskData();
	MakeFighterSpinLists(true);
}
//DeadCode JIM 30Oct00 void LWTaskSummary::OnClickedTickMaintainPc() 
//DeadCode JIM 30Oct00 {
//DeadCode JIM 30Oct00 	Todays_Packages.SetTaskData();
//DeadCode JIM 30Oct00 	Refresh();
//DeadCode JIM 30Oct00 	MakeFighterSpinLists(false);
//DeadCode JIM 30Oct00 	
//DeadCode JIM 30Oct00 }

void LWTaskSummary::OnClose() 
{
	CDialog::OnClose();
}
