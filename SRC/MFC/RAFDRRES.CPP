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

// RowanDialog: // RAFDrRes.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFDrRes.h"
#include "mymath.h"
#include "mytime.h"
#include "rchatter.h"
#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// RAFDirectiveResults dialog

RDialog*	RAFDirectiveResults::Make(RAFDirectivesResults* dirres)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_RAFDIRECTIVES,new RAFDirectiveResults(dirres))
			);
	return(NULL);
}
RAFDirectiveResults::RAFDirectiveResults(RAFDirectivesResults* dirres,  CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFDirectiveResults::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFDirectiveResults)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		dr = dirres;

}

RAFDirectiveResults::~RAFDirectiveResults()
{
	if (dr)
		delete dr;
}

void RAFDirectiveResults::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFDirectiveResults)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFDirectiveResults, CDialog)
	//{{AFX_MSG_MAP(RAFDirectiveResults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFDirectiveResults message handlers

BEGIN_EVENTSINK_MAP(RAFDirectiveResults, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFDirectiveResults)
	ON_EVENT(RAFDirectiveResults, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RAFDirectiveResults::OnSelectRlistboxctrl1(long row, long column) 
{
	// TODO: Add your control notification handler code here
	
}
void RAFDirectiveResults::Refresh()
{
	CDialog::OnInitDialog();
		CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->AddString("",0);
	rlistbox->Clear();

		//rlistbox->AddColumn(120);
		//rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
		rlistbox->AddString(RESSTRING(SIZE),0);
		rlistbox->AddString(RESSTRING(TARGET),1);


			int i = 0;
	while (dr->dirresults[i].target != UID_NULL)
	{

		rlistbox->AddString(RESLIST(SQUADRONORLESS,dr->dirresults[i].unitsize),0);
		rlistbox->AddString(GetTargName(dr->dirresults[i].target),1);
		i++;
	}



}
BOOL RAFDirectiveResults::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
		Refresh();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void RAFDirectiveResults::OnCancel() 
{
#ifndef	BOB_DEMO_VER

	// TODO: Add your message handler code here and/or call default
	if (m_pView->m_currentpage==0)
		MiscToolBar().OpenRAFDirectivetoggle(dr);
#endif

	dr = NULL;
	
	CDialog::OnCancel();
}

//DEADCODE RDH 03/04/00 int RAFDirectiveResults::SquadsAtField(UniqueID uidaf)
//DEADCODE RDH 03/04/00 {
//DEADCODE RDH 03/04/00 
//DEADCODE RDH 03/04/00 
//DEADCODE RDH 03/04/00 	int k=0, numsq = 0;
//DEADCODE RDH 03/04/00 	while (Node_Data.squadron[k].squadron != SQ_ZERO)
//DEADCODE RDH 03/04/00 	{
//DEADCODE RDH 03/04/00 			if (Node_Data.squadron[k].homeairfield == uidaf)
//DEADCODE RDH 03/04/00 			numsq++;
//DEADCODE RDH 03/04/00 		k++;
//DEADCODE RDH 03/04/00 	}
//DEADCODE RDH 03/04/00 	return (numsq);
//DEADCODE RDH 03/04/00 }
//DEADCODE RDH 03/04/00 
void RAFDirectivesResults::MoveSquadron(int sqnum,  int loc0, int loc1, int loc2)
{
	//loc0, 1 and 2 are the preferred locations in order of merit, first is best

	//don't accept a loc that is the same as the hone airfield
 	UniqueID uid = Node_Data.squadron[sqnum].homeairfield;
	TargetFighterField* af;
	af = Node_Data[uid];
	if	(af->truestatus < Target::TS_BADDAMAGE)
	{
		if (af->location == loc0)
		{
			loc0 = -1;
			loc1 = -1;
			loc2 = -1;
		}
		elseif (af->location == loc1)
		{
			loc1 = -1;
			loc2 = -1;
		}else
			loc2 = -1;
	}

		
	AirField Airfields[MAX_AF];

//DeadCode JIM 20Oct00 	int index = -1;
	int i = 0;
	int j;
	while (i < MAX_AF)
	{
		Airfields[i].uid = UID_NULL;
		i++;
	}

	j = 0;
	i = 0;
	while (	(j < (RAFDirectivesResults::MAX_AF-1)) && (Node_Data.sectorlist[i].uid != UID_NULL))
	{
			af = &Node_Data.sectorlist[i];
			if (		(af->location == loc0)
					||	(af->location == loc1)
					||	(af->location == loc2)
				)
			{
					int status = af->truestatus;						//RDH 9Sep00
				if	(	(		(status < Target::TS_BADDAMAGE)
						)
						&&
						(Node_Data.SquadsAtField(af->uid) < af->maxsquads)
					)
				{
					if 	(af->location == loc0)
					{
						Airfields[j].priority = 0;
						Airfields[j].uid= af->uid;
						j++;
					}else if	(af->location == loc1)
					{
						Airfields[j].priority = 1;
						Airfields[j].uid= af->uid;
						j++;
					}else if	(af->location == loc2)
					{
						Airfields[j].priority = 2;
						Airfields[j].uid= af->uid;
						j++;
					}
				}
			}
			while ((af = af->nextsatelite())!= NULL)
			{
				if (		(af->location == loc0)
						||	(af->location == loc1)
						||	(af->location == loc2)
					)
				{
					int status = af->truestatus;						//RDH 9Sep00
					if	(	(		(status == Target::TS_FLAG_UNKNOWN)				//RDH 9Sep00
								||	(status < Target::TS_BADDAMAGE)
							)
							&&
							(Node_Data.SquadsAtField(af->uid) < af->maxsquads)
						)
					{
						if 	(af->location == loc0)
						{
							Airfields[j].priority = 0;
							Airfields[j].uid= af->uid;
							j++;
						}else if	(af->location == loc1)
						{
							Airfields[j].priority = 1;
							Airfields[j].uid= af->uid;
							j++;
						}else if	(af->location == loc2)
						{
							Airfields[j].priority = 2;
							Airfields[j].uid= af->uid;
							j++;
						}
					}
				}
			}
		
		i++;
	}
	Airfields[j].uid = UID_NULL;


//DeadCode RDH 10Sep00 	Squadron* sq = &Node_Data[Node_Data.squadron[sqnum].squadron];
	Squadron* sq = Node_Data.squadron[sqnum];
	int maxaf = j;
	if (j > 0)
	{
		int priority = 0;
		int af= FindAirfield(priority, maxaf, Airfields);
		if 	(af>=0)
			((BritSquadron*)sq)->moveto = Airfields[af].uid;
		else 
		{
			priority = 1;
			int af= FindAirfield(priority, maxaf, Airfields);
			if 	(af>=0)
				((BritSquadron*)sq)->moveto = Airfields[af].uid;
			else 
			{
				priority = 2;
				int af= FindAirfield(priority, maxaf, Airfields);
				if 	(af>=0)
					((BritSquadron*)sq)->moveto = Airfields[af].uid;
				//else group 13
			}
		}
	}

}

int RAFDirectivesResults::FindAirfield(int priority, int maxaf, AirField* Airfields)
{
	int affound = -1;

	int   start = Math_Lib.rnd(maxaf);
	int cnt = start;
	cnt++;
	if (cnt >= maxaf)
		cnt = 0;

	while (	(cnt != start)	&&	(Airfields[cnt].priority != priority))
	{
		cnt++;
		if (cnt >= maxaf)
			cnt = 0;
	}
	if (Airfields[cnt].priority == priority)
		affound = cnt;

	return(affound);
}







void RAFDirectivesResults::MoveSquadronswrtFrontLine()
{
	int i = 0;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
		  )
	{
		UniqueID uid = Node_Data.squadron[i].homeairfield;
		TargetFighterField* af;
		af = Node_Data[uid];
//DeadCode JIM 20Oct00 		int loc = af->location;
		if 	(af->location == Target::LOC_N_LON)
		{
			if (newfrontlinefields	== COASTAL)
			{
				MoveSquadron(i, Target::LOC_COAST, Target::LOC_S_LON, -1);
			}else if (newfrontlinefields	== SOUTHLONDON)
			{
				MoveSquadron(i, Target::LOC_S_LON, Target::LOC_N_LON, -1);
			}
		}else if (af->location == Target::LOC_S_LON)
		{
			if (newfrontlinefields	== NORTHLONDON)
			{
				MoveSquadron(i, Target::LOC_N_LON, -1, -1);
			}else if (newfrontlinefields	== COASTAL)
			{
				MoveSquadron(i, Target::LOC_COAST, Target::LOC_S_LON, -1);
			}
		}else  if (af->location == Target::LOC_COAST)
		{
			if (newfrontlinefields	== NORTHLONDON)
			{
				MoveSquadron(i, Target::LOC_N_LON, -1, -1);
			}else if (newfrontlinefields	== SOUTHLONDON)
			{
				MoveSquadron(i, Target::LOC_S_LON, Target::LOC_N_LON, -1);
			}
		}
		i++;
	}

}
void RAFDirectiveResults::OnOK() 
{
#ifndef BOB_DEMO_VER
	if (dr->oldfrontlinefields != dr->newfrontlinefields)
		dr->MoveSquadronswrtFrontLine();

	MMC.directives.raf.current =	dr->tempdir;

	Node_Data.SetRAFReadiness();

	RAFDirectivesResults::MakeRAFPatrols(dr);
	m_pView->m_mapdlg.Invalidate();
	if (Save_Data.minsbetweensavegame)						//RJS 26Oct00
		CFiling::SaveTimedGame();							//RJS 26Oct00


	CDialog::OnOK();
#endif
}
void RAFDirectivesResults::MakeRAFPatrols(RAFDirectivesResults* dr)
{
			int i = 0;
	while (dr->dirresults[i].target != UID_NULL)
	{
		int packnum;
//DEADCODE RDH 15/05/00 		packnum=Todays_Packages.NewPackage(dr->dirresults[i].target,
//DEADCODE RDH 15/05/00 								NAT_RAF,
//DEADCODE RDH 15/05/00 								Profile::AM_PATROL,
//DEADCODE RDH 15/05/00 								(dr->dirresults[i].unitsize+1)*12,	//0 squad, 1 paired, 2 big wing
//DEADCODE RDH 15/05/00 								dr->dirresults[i].mission.acselectionrules
//DEADCODE RDH 15/05/00 
//DEADCODE RDH 15/05/00 											);
		packnum=Todays_Packages_NewPackage(dr->dirresults[i].target,
								dr->dirresults[i].mission);					
		if (packnum!=-1)
		{
//DEADCODE RDH 17/04/00 			Todays_Packages[packnum].AddNumerousEscorts(0,0,0,Profile::BR_WIDESTPOSSIBLE);
//DeadCode JIM 9Oct00 			if (dr->dirresults[i].mission.acselectionrules&Profile::BR_B_ALLOWGRP11)
//DeadCode JIM 9Oct00 				Todays_Packages[packnum].CalcRoutePositionsAndTime(MMC.currperiodtime+HR01 );
//DeadCode JIM 9Oct00 			else
			Todays_Packages[packnum].CalcRoutePositionsAndTime(MMC.currperiodtime+dr->dirresults[i].ETA );
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].RecalcRoutePositions();
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].primarytargetETA = Todays_Packages[packnum].FindEarliestPrimaryTargetETA();//+(int)HR01;
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].SetPredictedPointFromETA(true);
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].RecalcRoutePositions();
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].primarytargetETA = Todays_Packages[packnum].FindEarliestPrimaryTargetETA();//+(int)HR01;
		}
		i++;
	}

}
void RAFDirectivesResults::AutoRAFPatrols()
{

	RAFDirectivesResults*	dr = new RAFDirectivesResults;
	dr->tempdir = MMC.directives.raf.current;
	FindSquadsAvail(dr);
	SetDirectivesResults(dr);

	MakeRAFPatrols(dr);
	if (dr)
		delete dr;

}
void RAFDirectivesResults::RaidAcNumbers(int pack,int raid, int& strike, int& detachedescort, int& attachedescort, int& returnescort)
{
 	Profile& pk = Todays_Packages.pack[pack];

	int firstsquad=0;
	int lastsquad=pk.squadlist;
	strike=detachedescort=attachedescort=returnescort=0;
	if (raid>=0)
	{
		firstsquad = pk.raidnumentries[raid].squadliststart;
		lastsquad = pk.raidnumentries[raid+1].squadliststart;
		if (	(lastsquad > pk.squadlist) ||(lastsquad < firstsquad))
			lastsquad = pk.squadlist;
	}
	if (lastsquad > firstsquad)
	{

		int i=firstsquad;												//RDH 30/05/00
		while (i < lastsquad)											//MS 24Oct00
 		{
			if (pk[i].method == pk.attackmethod)
			{
				strike += pk[i].numacoriginal;
			}
			if (pk[i].method >= Profile::AM_RETURNESCORT)
			{
				returnescort += pk[i].numacoriginal;
			}
			if (pk[i].method >= Profile::AM_ATTACHED)
			{
				attachedescort += pk[i].numacoriginal;
			}
			else if (pk[i].method >= Profile::AM_DETACHED)
			{
				detachedescort =+ pk[i].numacoriginal;
			}
			i++;
		}
	}
}

void	PackageList::SplitExistingResponsesTo(int targpack,int newraidind)
{		//I don't know what to do, so I'm leaving it for now...
	int	numresponses=0;
	int raidsrespondedbits=0;
	int	raidsresponded=0;
	int reponses[10][40][2];
	for (int p=0;p<Profile::MAX_PACKS;p++)
		if (	pack[p].attackmethod<Profile::AM_LWPACKS
			&&	pack[p].packagestatus!=Profile::PS_SPARE 
			&&	pack[p].packagestatus<Profile::PS_ENEMYSIGHTED	)
		{
			int packtpack,packtsquad,packtraid;
			UniqueID packt=pack[p].packagetarget[0];
			if (packt>SagBANDEND)
			{
				packt=pack[p].packagetarget[1];
				if (packt>SagBANDEND)
					packt=UID_NULL;
			}
			if (packt && GetACSquadEntry(packt,packtpack) && packtpack==targpack)
			{	//the above if statement uses sequenced dependencies...
				//Need to 



			}
		}
}
void RAFDirectivesResults::SetRAFIntercept(int pack,int raid,bool afteregress)
{
#ifndef	BOB_DEMO_VER

	if (afteregress==MMC.directives.raf.current.interceptbeforetarget)
		return;
	int strike=0,detachedescort =0, attachedescort =0, returnescort = 0;
	RaidAcNumbers(pack, raid, strike, detachedescort, attachedescort, returnescort);
	int totalescort = detachedescort+ attachedescort+returnescort;
	if (!MMC.directives.raf.current.sanctioned[Directives::RAF::ANTISWEEP])							//MS 24Oct00
	{																						//MS 24Oct00
		int dummystrike;																	//MS 24Oct00
		RaidAcNumbers(pack, -1, dummystrike, detachedescort, attachedescort, returnescort);	//MS 24Oct00
		totalescort = detachedescort+ attachedescort+returnescort;							//MS 24Oct00
	}																						//MS 24Oct00

	bool sanctioned = false;
	if	(		(MMC.directives.raf.current.sanctioned[Directives::RAF::MissTypes::ANTISWEEP])
			&&	(strike == 0)	&&	(totalescort != 0)
		)
		sanctioned = true;
	else if	(		(MMC.directives.raf.current.sanctioned[Directives::RAF::MissTypes::ANTISINGLE])
			&&	(strike == 1)	&&	(totalescort == 0)
		)
			sanctioned = true;
	else if	(		(MMC.directives.raf.current.sanctioned[Directives::RAF::MissTypes::ANTIUNESC])
			&&	(strike > 1)	&&	(attachedescort == 0)
		)
		sanctioned = true;
	else if	(		(MMC.directives.raf.current.sanctioned[Directives::RAF::MissTypes::ANTIESC])
			&&	(strike > 1)	&&	(attachedescort != 0)
			)
		sanctioned = true;
	else if	(		(MMC.directives.raf.current.sanctioned[Directives::RAF::MissTypes::ANTIBIG])
				&&	(strike > 50)	&&	(attachedescort > 100)
			)
		sanctioned = true;

	if (sanctioned)
	{//check whether to respond if target is convoy
		int uidband;
	 	Profile& pk = Todays_Packages.pack[pack];

		uidband=Persons2::getbandfromUID(pk.packagetarget[0].currentid);	
		if (uidband == BritBoatBAND)
		{
			float conv = 65536 * MMC.directives.raf.current.convoylevel;
			if (Math_Lib.rnd(RndValMAX) > conv)
				sanctioned = false;
		}
	}

	if (sanctioned)
	{
		if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
				||	(MMC.autoscramble)
			)
			RAFDirectivesResults::InterceptSanctioned(pack,raid);
		else
		{
				MainToolBar().OpenInterceptOffered(pack,raid); 
		}
		
	}
#endif
}
int	RAFDirectivesResults::InterceptSanctioned(int pack, int raid)
{
	int	packnum=-1;
	int firstpacknum=-1;
	Profile& pk = Todays_Packages.pack[pack];
	int squadnum = pk.RaidNumEntriesMinSq(raid);
	int	squadmax = pk.RaidNumEntriesMaxSq(raid);
	for (int sqt=squadnum;sqt<=squadmax;sqt++)
		if (pk[sqt].playercansee)
		{
			squadnum=sqt;
			break;
		}
	pk.packagehasbeenintercepted=true;
	pk.raidnumentries[raid].raidintercepted=true;
	Directives::RAF::MissTypes 	misstype = RAFInterceptType(pack, squadnum);


	if (pk[squadnum].instance)
	{
		int strike=0,detachedescort =0, attachedescort =0, returnescort = 0;
		RaidAcNumbers(pack, raid, strike, detachedescort, attachedescort, returnescort);
		int totallw = strike + detachedescort+ attachedescort+returnescort;
 		if (!MMC.directives.raf.current.sanctioned[Directives::RAF::ANTISWEEP])							//MS 24Oct00
		{																						//MS 24Oct00
			int dummystrike;																	//MS 24Oct00
			RaidAcNumbers(pack, -1, dummystrike, detachedescort, attachedescort, returnescort);	//MS 24Oct00
			totallw =  detachedescort+ attachedescort+returnescort;						//MS 24Oct00
			totallw=totallw*strike/dummystrike;
			totallw+=strike;
		}																						//MS 24Oct00

		//+ve numac means  num of ac, -ve means squad
		int numac = MMC.directives.raf.userprofiles[misstype].hurr.numac;
		if (numac < 0)
			numac = numac * -12;

		int numspit= MMC.directives.raf.userprofiles[misstype].spit.numac;
		if (numspit < 0)
			numspit = numspit * -12;

		numac = numac + numspit;
		info_airgrpPtr ag=Persons2::ConvertPtrUID(pk[squadnum].instance);
		int	reqalt=0;
		if (ag->wpref)
		{
			info_waypointPtr wp=Persons2::ConvertPtrUID(ag->wpref);
			reqalt=(ag->knownposition.Y+wp->World.Y)/2;
		}

		
//TempCode MS 20Oct00 		int raids = totallw/(3 * numac);		//???
//WARNING - This has a major impact!
		int raids = totallw/(2 * numac);		//MS 20Oct00
		if	(raids < 1)
			raids = 1;
		for (int i = 0;i <raids; i++)
		{
			packnum=Todays_Packages_NewPackage(pk[squadnum].instance,
				MMC.directives.raf.userprofiles[misstype],reqalt);
			if (packnum!=-1)
			{
//DeadCode JIM 6Sep00 				Todays_Packages[packnum].CalcRoutePositionsAndTime();
				if (MMC.directives.raf.current.interceptbeforetarget)
					Todays_Packages[packnum].CalcRoutePositionsAndTime(0,SGR_WPP_DogLeg);
				else
					Todays_Packages[packnum].CalcRoutePositionsAndTime(0,SGR_WPP_Egress);
				if (firstpacknum==-1)
					firstpacknum=packnum;
				Todays_Packages.InvalidateRoute(&Todays_Packages[packnum],true,true);



			}
			else
			{
//DeadCode JIM 5Sep00 				INT3;	//WARNING: RAF COULDN'T RESPOND
				Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ALLUP ,Todays_Packages[pack][squadnum].instance,Todays_Packages[pack][squadnum].instance,TargetIndexes(Todays_Packages[pack][squadnum].squadnum,Todays_Packages[pack].CountRaid(squadnum)));

			}

		}
	}
	return(firstpacknum);
}

void	RAFDirectivesResults::SetUpRAFDirectives(Directives::RAF::HistTypes dirtype)
{
	MMC.directives.raf.current = MMC.directives.raf.histdir[dirtype];

	switch (dirtype)
	{
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_PHASE1:
		{
//DeadCode RDH 10Sep00 			Directives::RAF::SessionAI(); done in LaunchDirectiveMissions()
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_PHASE2:
		{
//DeadCode RDH 10Sep00 			Directives::RAF::SessionAI(); done in LaunchDirectiveMissions()
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_PHASE3:
		{
//DeadCode RDH 10Sep00 			Directives::RAF::SessionAI(); done in LaunchDirectiveMissions()
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_PHASE4:
		{
//DeadCode RDH 10Sep00 			Directives::RAF::SessionAI(); done in LaunchDirectiveMissions()
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_A:
		{
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_B:
		{
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_C:
		{
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_D:
		{
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_E:
		{
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_F:
		{
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_G:
		{
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	case	Directives::RAF::HistTypes::HISTORICALSCENARIO_H:
		{
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIUNESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIESC;
			MMC.directives.raf.current.sanctioned |= Directives::RAF::MissTypes::ANTIBIG;
			break;
		}
	}
}
Directives::RAF::MissTypes  RAFDirectivesResults::RAFMissType(int packnum)
{
	Profile& pk = Todays_Packages.pack[packnum];
	Directives::RAF::MissTypes misstype;
	if (pk.attackmethod == Profile::AM_PATROL)
	{
		misstype = Directives::RAF::PATROL;
	}else
	{

		int lwpack = 0, sq;
		UniqueID trguid = pk.packagetarget[0];
		int uidband=Persons2::getbandfromUID(trguid);	

		if (uidband == SagBAND)
		{
			Todays_Packages.GetACSquadEntry(trguid,lwpack,sq);
			misstype = RAFInterceptType(lwpack, sq);

		}else
			misstype = Directives::RAF::PATROL;


	}
	return (misstype);
}
Directives::RAF::MissTypes  RAFDirectivesResults::RAFInterceptType(int lwpack, int sqnum)
{
	Directives::RAF::MissTypes misstype;

	Profile& lwpk = Todays_Packages.pack[lwpack];
	int raidline = lwpk.GetRaidIndFromSquadEntry(sqnum);
	int i = lwpk.raidnumentries[raidline].squadliststart;
	int lastsq;
	lastsq = lwpk.RaidNumEntriesMaxSq(raidline);

 	int count = 0;
	bool nobombers = true, nofighters = true;
	SquadNum	gruppe;
	while (i <= lastsq)
	{
		count += lwpk[i].numacoriginal;
		gruppe = lwpk[i].squadnum;
		int actype = Node_Data[gruppe].AcType();
		if (actype >= PT_LW_BOMBERS)
			nobombers = false;
		else
			nofighters = false;
		i++;
	}
	if (count ==1)
 	{
		misstype = Directives::RAF::ANTISINGLE;
	}else if (count > 300)			//MS 09Sep00
	{
		misstype = Directives::RAF::ANTIBIG;
	}elseif (nobombers)
	{
		misstype = Directives::RAF::ANTISWEEP;
	}elseif(nofighters)
	{
		misstype = Directives::RAF::ANTIUNESC;
	}else
	{
		misstype = Directives::RAF::ANTIESC;
	}
	return (misstype);

}
