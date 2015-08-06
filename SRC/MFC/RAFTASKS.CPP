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

// RowanDialog: // RAFTaskS.cpp : implementation file
//

//
//NOTE!!!
//	Spitfire button is now a COMBO between HURR,SPIT,MIXED
//
//
//

#include "stdafx.h"
#include "bob.h"
#include "RAFTaskS.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

RAFTaskSummary::WingInfo	RAFTaskSummary::winginfo[RAFTaskSummary::MIXWINGMAX] = 
{
	{1,1, IDS_SQUADRON},
	{2,2, IDS_SQUADRONS},
	{3,3, IDS_SQUADRONS},
	{4,4, IDS_SQUADRONS},
	{5,5, IDS_SQUADRONS},
	{6,6, IDS_SQUADRONS},
};
RAFTaskSummary::SquadInfo	RAFTaskSummary::squadinfo[RAFTaskSummary::SQUADMAX] = 
{
	{1,1, IDS_SQUADRONLEADER},
	{1,3, IDS_ELEMENT},
	{1,6, IDS_FLIGHT},
};
/////////////////////////////////////////////////////////////////////////////
// RAFTaskSummary dialog


RDialog*	RAFTaskSummary::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new RAFTaskSummary())
			);
}


RAFTaskSummary::RAFTaskSummary(CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFTaskSummary::IDD, pParent)
{
	packnum=Todays_Packages.hipack;
	//{{AFX_DATA_INIT(RAFTaskSummary)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RAFTaskSummary::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFTaskSummary)
	DDX_Control(pDX, IDC_RSPINBUT_HURRICANES, m_IDC_RSPINBUT_HURRICANES);
	DDX_Control(pDX, IDC_RSPINBUT_SPITFIRES, m_IDC_RSPINBUT_SPITFIRES);
	DDX_Control(pDX, IDC_RSTATICTOTAL, m_IDC_RSTATICTOTAL);
	DDX_Control(pDX, IDC_RSTATICCTRL24, m_IDC_TEMPLATE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFTaskSummary, CDialog)
	//{{AFX_MSG_MAP(RAFTaskSummary)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
			ON_MESSAGE( WM_SELECTTAB, OnSelectTab)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFTaskSummary message handlers
void	RAFTaskSummary::OnSelectTab()
{
	Refresh();
}
void RAFTaskSummary::Refresh()
{
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	//first find out which template we will be mashing:
	Directives::RAF::MissTypes  misstype=RAFDirectivesResults::RAFMissType(Todays_Packages.hipack);
	rafdirectivemisstype=misstype;
//		enum	MissTypes {PATROL,ANTISWEEP,ANTISINGLE,ANTIUNESC,ANTIESC,ANTIBIG,MAXMISSTYPES};
	CString templatename;
	if (misstype==Directives::RAF::PATROL)
		templatename=CSprintf("%s: %s",RESSTRING(PATROL),GetTargName(pk.packagetarget[0]));
	else
	{
		templatename=CSprintf("%s: %s",RESSTRING(INTERCEPT),RESLIST(FIGHTERSWEEP,misstype-1));
	}
	m_IDC_TEMPLATE.SetString(templatename);

	//using	attached and	detached
	//as	hurricanes	and	spitfires	respectively

	int	currentmixmode=MMC.directives.raf.userprofiles[misstype].acselectionrules&Profile::BR_B_EITHERWL;
	int	currentnumac=-1;
	int currentnumsquads= pk.squadlist;
	if (currentnumsquads==1)
		currentnumac=pk[0].numacoriginal;
//		BR_B_SPITONLY	=0x0000D,		//spitfire from any group with/without leader. These can choose a squad with enough aircraft who's
//		BR_B_HURRONLY	=0x0000E,		//leader is already in the air
//		BR_B_ANYRAF		=0x0000F,		//

	int	spitacavail,spitsqavail;
	int	hurracavail,hurrsqavail;
	Todays_Packages.RAFAcAvailable(NULL,PT_SPIT_A,PT_SPIT_B,spitacavail,spitsqavail,false);
	Todays_Packages.RAFAcAvailable(NULL,PT_HURR_A,PT_HURR_B,hurracavail,hurrsqavail,false);
	int numspitsqinpack=0,numhurrsqinpack=0;
	for (int s=0,m=pk.squadlist;s<m;s++)
		if (pk[s].Squadron().AcType()<PT_HURR_A)
			numspitsqinpack++;
		else
			numhurrsqinpack++;

	int allowanceindex=0;
	if (currentnumsquads==1)
	{
		if (	numspitsqinpack	||	spitsqavail || spitacavail>=currentnumac	)
			actypeoptions[allowanceindex++]=Profile::BR_B_SPITWL;
		if (	numhurrsqinpack	||	hurrsqavail || hurracavail>=currentnumac	)
			actypeoptions[allowanceindex++]=Profile::BR_B_HURRWL;
	}
	else
		if (currentnumsquads<=3)		//can only switch to 1 type for less than 3!
		{
			if (numspitsqinpack+spitsqavail>=currentnumsquads)
				actypeoptions[allowanceindex++]=Profile::BR_B_SPITWL;
			if (numhurrsqinpack+hurrsqavail>=currentnumsquads)
				actypeoptions[allowanceindex++]=Profile::BR_B_HURRWL;
			if (numspitsqinpack && numhurrsqinpack)
				currentmixmode=Profile::BR_B_EITHERWL;
		}
		else
			currentmixmode=Profile::BR_B_EITHERWL;						//JIM 19Oct00

	actypeoptions[allowanceindex++]=Profile::BR_B_EITHERWL;
	actypeoptions[allowanceindex]=0;

	m_IDC_RSPINBUT_SPITFIRES.Clear();
	for (int i=0;i<allowanceindex;i++)
	{
		switch (actypeoptions[i])
		{
		case 1:	m_IDC_RSPINBUT_SPITFIRES.AddString(RESSTRING(SPITFIRES));	break;
		case 2:	m_IDC_RSPINBUT_SPITFIRES.AddString(RESSTRING(HURRICANES));	break;
		case 3:	m_IDC_RSPINBUT_SPITFIRES.AddString(RESSTRING(MIXED));	break;
		}
		if (actypeoptions[i]==currentmixmode)
			m_IDC_RSPINBUT_SPITFIRES.SetIndex(i);
	}

	//now find max index for combo...
	int maxsquads=0,maxac=-1;
	if (currentnumsquads==1)
	{
		BritSquadron* sq=pk[0].Squadron();
		int maxcurrentsquad=sq->acavail;
		bool currentsquadcangofull=false;
		if (maxcurrentsquad>=12)
		{
			maxcurrentsquad=12;
			currentsquadcangofull=true;
		}
		int unavailbits=(sq->usedacbits & !pk.squadlist.AcBitsFirstSquad());
		if (unavailbits)
		{
			currentsquadcangofull=false;
			for (int i=1;i<0x1000;i+=i)
				if (unavailbits&i)
					maxcurrentsquad--;
		}

		switch (currentmixmode)
		{
		case  Profile::BR_B_SPITWL:
		{
			if ((spitsqavail+currentsquadcangofull)>=3)
				maxsquads=3;
			else
			{	//if we are only user of our squadron and our squad can field 12 inc spitsqavail
				
				if(spitsqavail+currentsquadcangofull)
					maxsquads=spitsqavail+currentsquadcangofull;
				else
					maxac=maxcurrentsquad;
			}
		}
		break;
		case  Profile::BR_B_HURRWL:
		{
			if ((hurrsqavail+currentsquadcangofull)>=3)
				maxsquads=3;
			else
			{	//if we are only user of our squadron and our squad can field 12 inc spitsqavail
				
				if(hurrsqavail+currentsquadcangofull)
					maxsquads=hurrsqavail+currentsquadcangofull;
				else
					maxac=maxcurrentsquad;
			}

		}
		break;
		case  Profile::BR_B_EITHERWL:
		{
			if ((hurrsqavail+spitsqavail+currentsquadcangofull)>=6)
				maxsquads=6;
			else
			{	//if we are only user of our squadron and our squad can field 12 inc spitsqavail
				
				if(hurrsqavail+spitsqavail+currentsquadcangofull)
					maxsquads=hurrsqavail+spitsqavail+currentsquadcangofull;
				else
					maxac=maxcurrentsquad;
			}
		}
		break;
		}


	}
	else
	{	//somewhat simpler if already up to full squads...
		switch (currentmixmode)
		{
		case  Profile::BR_B_SPITWL:
		{
			maxsquads=currentnumsquads+spitsqavail;
			if (maxsquads>3)
				maxsquads=3;

		}
		break;
		case  Profile::BR_B_HURRWL:
		{
			maxsquads=currentnumsquads+hurrsqavail;
			if (maxsquads>3)
				maxsquads=3;
		}
		break;
		case  Profile::BR_B_EITHERWL:
		{
			maxsquads=currentnumsquads+spitsqavail+hurrsqavail;
			if (maxsquads>6)
				maxsquads=6;
		}
		break;
		}
	}
	//got maxsquads=0,maxac=-1 for the one not to use;
 	CRSpinBut* spinbut;

 	spinbut=GETDLGITEM(IDC_RSPINBUT_HURRICANES);
	spinbut->Clear();
	if (maxac==-1 || maxac>6)
	{
		spinbut->AddString(CSprintf("%i %s",squadinfo[0].numoutput,LoadResString(squadinfo[0].name)));
		spinbut->AddString(CSprintf("%i %s",squadinfo[1].numoutput,LoadResString(squadinfo[1].name)));
		spinbut->AddString(CSprintf("%i %s",squadinfo[2].numoutput,LoadResString(squadinfo[2].name)));
		for (int i=1;i<=maxsquads;i++)
			spinbut->AddString(CSprintf("%i %s",winginfo[i-1].numoutput,LoadResString(winginfo[i-1].name)));
	}
	else
	{
		spinbut->AddString(CSprintf("%i %s",squadinfo[0].numoutput,LoadResString(squadinfo[0].name)));
		if (maxac>=3)
			spinbut->AddString(CSprintf("%i %s",squadinfo[1].numoutput,LoadResString(squadinfo[1].name)));
		if (maxac>=6)
			spinbut->AddString(CSprintf("%i %s",squadinfo[2].numoutput,LoadResString(squadinfo[2].name)));
	}
	if (currentnumsquads>1 || currentnumac>=9)
		spinbut->SetIndex(currentnumsquads+2);
	else
		spinbut->SetIndex(currentnumac/3); //1,3,6 ==> 0,1,2

	CString totalmsg;
	if (numspitsqinpack && numhurrsqinpack)
	{
		totalmsg=CSprintf("%s: %i %s (%i %s)\n%s: %i %s (%i %s)",
			RESSTRING(SPITFIRES),numspitsqinpack,LoadResString(winginfo[numspitsqinpack-1].name),numspitsqinpack*12,RESSTRING(AIRCRAFT_PLURAL),
			RESSTRING(HURRICANES),numhurrsqinpack,LoadResString(winginfo[numspitsqinpack-1].name),numhurrsqinpack*12,RESSTRING(AIRCRAFT_PLURAL));
	}
	else
	{
		if (numspitsqinpack)
			totalmsg=RESSTRING(SPITFIRES);
		else
			totalmsg=RESSTRING(HURRICANES);
		if (currentnumsquads>1 || currentnumac>=9)
			totalmsg=CSprintf("%s: %i %s (%i %s)",
				totalmsg,currentnumsquads,LoadResString(winginfo[currentnumsquads-1].name),currentnumsquads*12,RESSTRING(AIRCRAFT_PLURAL));
		else
			if (currentnumac!=1)
				totalmsg=CSprintf("%s: %i %s (%i %s)",
					totalmsg,squadinfo[currentnumac/3].numoutput,LoadResString(squadinfo[currentnumac/3].name),currentnumac,RESSTRING(AIRCRAFT_PLURAL));
			else
				totalmsg=CSprintf("%s: %i %s (%i %s)",
					totalmsg,squadinfo[0].numoutput,LoadResString(squadinfo[0].name),currentnumac,RESSTRING(AIRCRAFT));
	}
	m_IDC_RSTATICTOTAL.SetString(totalmsg);

}

BOOL RAFTaskSummary::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRStatic*   s;

	Refresh();

//DEADCODE RDH 17/01/00    	CRSpinBut* spinbut;
//DEADCODE RDH 17/01/00 	spinbut=GETDLGITEM(IDC_RSPINBUT_BOMBERS);
//DEADCODE RDH 17/01/00 	spinbut->Clear();
//DEADCODE RDH 17/01/00 	spinbut->AddString("Squadron Leader");
//DEADCODE RDH 17/01/00 	spinbut->AddString("Singleton");
//DEADCODE RDH 17/01/00 	spinbut->AddString("Element");
//DEADCODE RDH 17/01/00 	spinbut->AddString("Flight");
//DEADCODE RDH 17/01/00 	spinbut->AddString("2 Flights");
//DEADCODE RDH 17/01/00 	spinbut->AddString("1 Squadron");
//DEADCODE RDH 17/01/00 	spinbut->AddString("2 Squadrons");
//DEADCODE RDH 17/01/00 	spinbut->AddString("3 Squadrons");
//DEADCODE RDH 17/01/00 
//DEADCODE RDH 17/01/00 
//DEADCODE RDH 17/01/00  	spinbut=GETDLGITEM(IDC_RSPINBUT_FIGHTERS);
//DEADCODE RDH 17/01/00 	spinbut->Clear();
//DEADCODE RDH 17/01/00 	spinbut->AddString("Squadron Leader");
//DEADCODE RDH 17/01/00 	spinbut->AddString("Singleton");
//DEADCODE RDH 17/01/00 	spinbut->AddString("Element");
//DEADCODE RDH 17/01/00 	spinbut->AddString("Flight");
//DEADCODE RDH 17/01/00 	spinbut->AddString("2 Flights");
//DEADCODE RDH 17/01/00 	spinbut->AddString("1 Squadron");
//DEADCODE RDH 17/01/00 	spinbut->AddString("2 Squadrons");
//DEADCODE RDH 17/01/00 	spinbut->AddString("3 Squadrons");
//DEADCODE RDH 17/01/00 
	
	

	
	
	
	
	
		

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(RAFTaskSummary, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFTaskSummary)
	ON_EVENT(RAFTaskSummary, IDC_RSPINBUT_HURRICANES, 1 /* TextChanged */, OnTextChangedRspinbutHurricanes, VTS_BSTR VTS_I2)
	ON_EVENT(RAFTaskSummary, IDC_RSPINBUT_SPITFIRES, 1 /* TextChanged */, OnTextChangedRspinbutSpitfires, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RAFTaskSummary::OnTextChangedRspinbutHurricanes(LPCTSTR caption, short Index) 
{  
//DeadCode JIM 19Oct00 
//DeadCode JIM 19Oct00 	if (	Index==0 
//DeadCode JIM 19Oct00 		&&	Todays_Packages.pack[Todays_Packages.hipack].squadlist.Max()==1 
//DeadCode JIM 19Oct00 		&&	Todays_Packages.pack[Todays_Packages.hipack][0].Squadron().AcType()>=PT_HURR_A
//DeadCode JIM 19Oct00 		)
//DeadCode JIM 19Oct00 	{	//Can spin both to zero!										//JIM 19Oct00
//DeadCode JIM 19Oct00 		GETDLGITEM(IDC_RSPINBUT_HURRICANES)->SetIndex(1);
//DeadCode JIM 19Oct00 		return;
//DeadCode JIM 19Oct00 	}
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	int reqac=-1,reqsq=0;
	int orgac=-1,orgsq=0;
	if (Index>=3)
		reqsq=Index-2;		//0=1ac,1=3ac,2=6ac,3=1sq,4=2sq,etc.
	else
		reqac=squadinfo[Index].number;
	if (pk.squadlist.Max()>1)
		orgsq=pk.squadlist.Max();
	else
		if (pk[0].numacoriginal>6)
			orgsq=1;
		else
			orgac=pk[0].numacoriginal;
		
	if (orgac!=reqac || orgsq!=reqsq)
	{
		Todays_Packages.InvalidateRoute(&pk,true,true);
		pk.RAFResetAcNumbers(MMC.directives.raf.userprofiles[rafdirectivemisstype].acselectionrules, orgsq, reqsq, reqac);
		Todays_Packages.CheckHilightValid();
		Todays_Packages.SetRAFTaskData();
//DeadCode JIM 15Sep00 		pk.ReShareSecondaries();
		typedef	Profile::AttackMethod AttackMethod;
		MAKEFIELD(AttackMethod,Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);
		AttackMethodField	am={0};//pk.ScanAttackMethods();
		pk.ReorderPackage(am);
		pk.packagetakeoff=pk[0].Squadron().homeairfield;
		pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
		Todays_Packages.InvalidateRoute(&pk,true,true);
	}
	Refresh();
	
}

void RAFTaskSummary::OnTextChangedRspinbutSpitfires(LPCTSTR caption, short Index) 
{
	Profile::BetterRule oldmixtype=MMC.directives.raf.userprofiles[rafdirectivemisstype].acselectionrules;
	Profile::BetterRule newmixtype=Profile::BetterRule(actypeoptions[Index]);
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	if (oldmixtype!=newmixtype)
	{
		int oldsquads=0,oldacs=-1;
		if (pk.squadlist.Max()>1 || pk[0].numacoriginal>6)
			oldsquads=pk.squadlist.Max();
		else
			oldacs=pk[0].numacoriginal;
		if (oldsquads>=1 || oldacs!=1)
			newmixtype=Profile::BetterRule(newmixtype+Profile::BR_B_LEADOPTNL+Profile::BR_B_ALLOWGRP11);
		else
			newmixtype=Profile::BetterRule(newmixtype+Profile::BR_B_ALLOWGRP11);
		MMC.directives.raf.userprofiles[rafdirectivemisstype].acselectionrules=newmixtype;
		if ((newmixtype&Profile::BR_B_EITHERWL)!=Profile::BR_B_EITHERWL)
		{	//need to swap...
			Profile::BetterRule oppositerule=Profile::BetterRule(Profile::BR_B_EITHERWL&~newmixtype);
			Todays_Packages.InvalidateRoute(&pk,true,true);
			pk.DeleteNumerousSquadrons(oppositerule);
			pk.RAFResetAcNumbers(newmixtype,pk.squadlist.Max(),oldsquads,oldacs);
			Todays_Packages.SetRAFTaskData();
	//DeadCode JIM 15Sep00 		pk.ReShareSecondaries();
			typedef	Profile::AttackMethod AttackMethod;
			MAKEFIELD(AttackMethod,Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);
			AttackMethodField	am={0};//pk.ScanAttackMethods();
			pk.ReorderPackage(am);
			pk.packagetakeoff=pk[0].Squadron().homeairfield;
			pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
			Todays_Packages.CheckHilightValid();
			Todays_Packages.InvalidateRoute(&pk,true,true);
		}


		Refresh();
	}
}

void RAFTaskSummary::OnClose() 
{
//TEMPCODE DAW 21/03/00 	Todays_Packages.pack[packnum].ReorderPackage();
	
	CDialog::OnClose();
}
