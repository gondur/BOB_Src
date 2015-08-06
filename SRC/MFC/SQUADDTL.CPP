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

// RowanDialog: // SquadDtl.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "SquadDtl.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// SquadronDetails dialog


RDialog*	SquadronDetails::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_SQUADDETAILS,new SquadronDetails((SquadNum)0))
			);
		
}


SquadronDetails::SquadronDetails(SquadNum squadnum, CWnd* pParent /*=NULL*/)
	: RowanDialog(SquadronDetails::IDD, pParent)
{
	sqnum = squadnum;
	//{{AFX_DATA_INIT(SquadronDetails)
	//}}AFX_DATA_INIT
}


void SquadronDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SquadronDetails)
	DDX_Control(pDX, IDC_RSTATICLDR, m_IDC_RSTATICLDR);
	DDX_Control(pDX, IDC_RSTATICLDRMORALE, m_IDC_RSTATICLDRMORALE);
	DDX_Control(pDX, IDC_RSTATICACTYPE, m_IDC_RSTATICACTYPE);
	DDX_Control(pDX, IDC_RSTATICACAVAIL, m_IDC_RSTATICACAVAIL);
	DDX_Control(pDX, IDC_RSTATICACTIVITY, m_IDC_RSTATICACTIVITY);
	DDX_Control(pDX, IDC_RSTATICAIRFIELD, m_IDC_RSTATICAIRFIELD);
	DDX_Control(pDX, IDC_RSTATICATKPATT, m_IDC_RSTATICATKPATT);
	DDX_Control(pDX, IDC_RSTATICCR, m_IDC_RSTATICCR);
	DDX_Control(pDX, IDC_RSTATICFORMATION, m_IDC_RSTATICFORMATION);
	DDX_Control(pDX, IDC_RSTATICNOPILOTS, m_IDC_RSTATICNOPILOTS);
	DDX_Control(pDX, IDC_RSTATICSQUADMORALE, m_IDC_RSTATICSQUADMORALE);
	DDX_Control(pDX, IDC_RSTATICSQUADSTATUS, m_IDC_RSTATICSQUADSTATUS);
	DDX_Control(pDX, IDC_RBUTTONSQUADRON, m_IDC_RBUTTONSQUADRON);
	DDX_Control(pDX, IDC_RSTATICCTRL53, m_IDC_RSTATICCTRL53);
	DDX_Control(pDX, IDC_RSTATICCTRL54, m_IDC_RSTATICCTRL54);
	DDX_Control(pDX, IDC_RSTATICCTRL70, m_IDC_RSTATICCTRL70);
	DDX_Control(pDX, IDC_RSTATICCTRL71, m_IDC_RSTATICCTRL71);
	DDX_Control(pDX, IDC_RCOMBOREQUIRED, m_IDC_RCOMBOREQUIRED);
	DDX_Control(pDX, IDC_RCOMBOAIRFIELD, m_IDC_RCOMBOAIRFIELD);
	DDX_Control(pDX, IDC_RCOMBOGROUP, m_IDC_RCOMBOGROUP);
	DDX_Control(pDX, IDC_RSTATICMOVETO, m_IDC_RSTATICMOVETO);
	DDX_Control(pDX, IDC_RBUTTONAIRFIELD, m_IDC_RBUTTONAIRFIELD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SquadronDetails, CDialog)
	//{{AFX_MSG_MAP(SquadronDetails)
	//}}AFX_MSG_MAP
		ON_MESSAGE( WM_SELECTTAB, OnSelectTab)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SquadronDetails message handlers
void	SquadronDetails::OnSelectTab()
{
	Refresh();
}

BOOL SquadronDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();

	

	CRButton*	but;
	CRStatic*   s;



	Squadron* sq = &Node_Data[sqnum];


	if (sqnum>=SQ_LW_START)
	{
		CRCombo* combo;
 		combo=GETDLGITEM(IDC_RCOMBOGROUP);
		combo->ShowWindow(false);
 		combo=GETDLGITEM(IDC_RCOMBOAIRFIELD);
		combo->ShowWindow(false);
		combo=GETDLGITEM(IDC_RCOMBOREQUIRED);
		combo->ShowWindow(false);
		 s=GETDLGITEM(IDC_RSTATICMOVETO);
		 s->ShowWindow(SW_HIDE);
		 s=GETDLGITEM(IDC_RSTATICCTRL53);
		 s->ShowWindow(SW_HIDE);
		 s=GETDLGITEM(IDC_RSTATICCTRL54);
		 s->ShowWindow(SW_HIDE);
		 s=GETDLGITEM(IDC_RSTATICCTRL70);
		 s->ShowWindow(SW_HIDE);
		 s=GETDLGITEM(IDC_RSTATICCTRL71);
		 s->ShowWindow(SW_HIDE);
		 s=GETDLGITEM(IDC_RSTATICCR);
		 s->ShowWindow(SW_HIDE);
		 s=GETDLGITEM(IDC_RSTATICATKPATT);
		 s->ShowWindow(SW_HIDE);
		 s=GETDLGITEM(IDC_RSTATICFORMATION);
		 s->ShowWindow(SW_HIDE);
		 but=GETDLGITEM(IDC_RBUTTONAIRFIELD);
		 but->ShowWindow(SW_SHOW);
	}else
	{
		TargetFighterField* af = Node_Data[Node_Data[sqnum].homeairfield];

	 	TargetSectorField* sectorfield = af->getsectoraf();


		CRCombo* combo;
		if (sectorfield->groupname == IDS_GROUP_13)
		{
			combo=GETDLGITEM(IDC_RCOMBOREQUIRED);
			combo->ShowWindow(false);
			s=GETDLGITEM(IDC_RSTATICCTRL53);
			s->ShowWindow(SW_HIDE);
			s=GETDLGITEM(IDC_RSTATICCTRL54);
			s->ShowWindow(SW_HIDE);
			s=GETDLGITEM(IDC_RSTATICCR);
			s->ShowWindow(SW_HIDE);
		}else
		{
			combo=GETDLGITEM(IDC_RCOMBOREQUIRED);
			combo->ShowWindow(true);
			s=GETDLGITEM(IDC_RSTATICCTRL53);
			s->ShowWindow(SW_SHOW);
			s=GETDLGITEM(IDC_RSTATICCTRL54);
			s->ShowWindow(SW_SHOW);
			s=GETDLGITEM(IDC_RSTATICCR);
			s->ShowWindow(SW_SHOW);
		}
 		combo=GETDLGITEM(IDC_RCOMBOGROUP);
		combo->ShowWindow(true);
 		combo=GETDLGITEM(IDC_RCOMBOAIRFIELD);
		combo->ShowWindow(true);
		s=GETDLGITEM(IDC_RSTATICMOVETO);
		s->ShowWindow(SW_SHOW);
		s=GETDLGITEM(IDC_RSTATICCTRL70);
		s->ShowWindow(SW_HIDE);
		s=GETDLGITEM(IDC_RSTATICCTRL71);
		s->ShowWindow(SW_HIDE);
		s=GETDLGITEM(IDC_RSTATICATKPATT);
		s->ShowWindow(SW_HIDE);
		s=GETDLGITEM(IDC_RSTATICFORMATION);
		s->ShowWindow(SW_HIDE);
		but=GETDLGITEM(IDC_RBUTTONAIRFIELD);
		but->ShowWindow(SW_HIDE);
		if (((BritSquadron*)sq)->moveto)
		{
			movedalready = true;
			group = FindAirfieldGroup(((BritSquadron*)sq)->moveto);

		}
		else
		{
			movedalready = false;
			group = FindAirfieldGroup(Node_Data[sqnum].homeairfield);
		}
	}

	
	but=GETDLGITEM(IDC_RBUTTONSQUADRON);								//RDH 9Sep00
	SquadronBase*	sqentry;
	sqentry = Squad_Diary.FindLast(sqnum);
	if (sqentry)				//user wp
	{
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
		but->SetBackColor(RGB(255,255,0));
	}else
	{
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
	}																	//RDH 9Sep00



	s=GETDLGITEM(IDC_RSTATICLDR);
	s->SetString(LoadResString(sq->leadername));

	UByte morale = sq->leadermorale/MORALE_STAGE;
	s=GETDLGITEM(IDC_RSTATICLDRMORALE);
	s->SetString(RESLIST(MORALE_ROCKBOTTOM, morale));

	s=GETDLGITEM(IDC_RSTATICACTYPE);
	int actype= sq->AcType();
	s->SetString(RESLIST(SPIT_A, actype));


//DEADCODE RDH 05/01/00 	int ac = 16;
//DEADCODE RDH 05/01/00 	s=GETDLGITEM(IDC_RSTATICACTOTAL);
//DEADCODE RDH 05/01/00 	s->SetString(CSprintf("%i", sq->acavail + sq->acquickrepairable + sq->acslowrepairable));

	s=GETDLGITEM(IDC_RSTATICACAVAIL);
	s->SetString(CSprintf("%i (%i)", sq->acavail, sq->acavail + sq->acquickrepairable + sq->acslowrepairable));

	s=GETDLGITEM(IDC_RSTATICACTIVITY);
	s->SetString(RESSTRING(L_READY));

	s=GETDLGITEM(IDC_RSTATICAIRFIELD);
	s->SetString(GetTargName(sq->homeairfield));

	s=GETDLGITEM(IDC_RSTATICATKPATT);
	s->SetString(RESSTRING(LINEABREAST));

	s=GETDLGITEM(IDC_RSTATICCR);
	s->SetString(RESLIST(PS_SPARE,sq->totestatus));

	CRCombo* combo;
	combo=GETDLGITEM(IDC_RCOMBOREQUIRED);


	if (sq->totestatus == Profile::PS_AIRFIELDOUT)							//JIM 8Aug00
		combo->Clear()->RESCOMBO(NOORDER,2)->
					SetIndex(0);
	else
	if (sq->totestatus >= Profile::PS_PLANNING)							//JIM 8Aug00
		combo->Clear()->RESCOMBO(INAIR,1)->
					SetIndex(0);
	else
		combo->Clear()->RESCOMBO(NOORDER,5)->
					SetIndex(0);

	
	s=GETDLGITEM(IDC_RSTATICFORMATION);
	s->SetString(RESSTRING(VIC));

	s=GETDLGITEM(IDC_RSTATICNOPILOTS);
	s->SetString(CSprintf("%i", sq->pilotsavail));


	morale = sq->averagemorale/MORALE_STAGE;								//RDH 27/03/00

	s=GETDLGITEM(IDC_RSTATICSQUADMORALE);
	s->SetString(RESLIST(MORALE_ROCKBOTTOM, morale));

	s=GETDLGITEM(IDC_RSTATICSQUADSTATUS);

	s->SetString(RESLIST(CATEGORYA, sq->Category()));


	afindex =0;
	Refresh();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



bool SquadronDetails::CheckSatellites(int sectorindex, UniqueID afuid)
{
	TargetFighterField* af = &Node_Data.sectorlist[sectorindex];
	bool affound = false;

	while ((af = af->nextsatelite())!= NULL)
	{
	   if (af->uid== afuid)
	   {
		  affound = true;
		  break;
	   }
	 }

	return (affound);
}
int SquadronDetails::FindAirfieldGroup(UniqueID afuid)
{
	int i = 0;
	int group = 11;
	while (Node_Data.sectorlist[i].uid != UID_NULL)
	{
		if (Node_Data.sectorlist[i].uid == 	afuid)
		{
			group = Node_Data.sectorlist[i].groupname;
			break;
		}
		if (CheckSatellites(i, afuid))
		{
			group = Node_Data.sectorlist[i].groupname;
			break;
		}

		i++;
		
	}
	return(group);
}
int SquadronDetails::FillAirfieldList()
{
	int index = -1;
	int i = 0;
	int j;
	while (i < MAX_AF)
	{
		Airfields[i] = UID_NULL;
		i++;
	}

	j = 0;
	i = 0;
	TargetFighterField* af;
	af = Node_Data[Node_Data[sqnum].homeairfield];
 	TargetSectorField* homesectorfield = af->getsectoraf();
	TargetFighterField* trgaf;
 	TargetSectorField* trgsectraf;


	bool movementoutofsectorallowed = true;
	if (Node_Data.SquadsInSector(homesectorfield) <= homesectorfield->minsquadsinsector)
		movementoutofsectorallowed = false;

	while ((i < (MAX_AF-1)) && (Node_Data.sectorlist[i].uid != UID_NULL) )
	{
		if (Node_Data.sectorlist[i].groupname == group)
		{
			af = &Node_Data.sectorlist[i];
			int squadsinsector = Node_Data.SquadsInSector(af);

		   	Squadron* sq = &Node_Data[sqnum];

			if (((BritSquadron*)sq)->moveto != NULL)
			{

				trgaf = Node_Data[((BritSquadron*)sq)->moveto];
				trgsectraf = trgaf->getsectoraf();

				if (af == trgsectraf)
				//the sq has been ordered to move to sector in question, so don't count proposed move here
					  squadsinsector--;
			}
			
			if  (		(	(		(squadsinsector	< ((TargetSectorField*)af)->maxsquadsinsector)
								&&	(movementoutofsectorallowed)
									
							)
							||
							(((BritSquadron*)sq)->moveto != UID_NULL)
						)
					||	(homesectorfield == af)
				)
			{
				int squadatfield = Node_Data.SquadsAtField(af->uid);
				if (af->uid == ((BritSquadron*)sq)->moveto)
					 squadatfield--;
				if (		(squadatfield < af->maxsquads)
						||	(af->uid  == Node_Data[sqnum].homeairfield)
					)
				{//only offer if not at max
			 		Airfields[j] = af->uid;
					if (Airfields[j]  == ((BritSquadron*)sq)->moveto)
						index = j;
					j++;
				}
				while ((af = af->nextsatelite())!= NULL)
				{
					squadatfield = Node_Data.SquadsAtField(af->uid);
 				if (af->uid == ((BritSquadron*)sq)->moveto)
					 squadatfield--;

					if (		(squadatfield < af->maxsquads)
							||	(af->uid  == Node_Data[sqnum].homeairfield)
						)
					{
						Airfields[j]= af->uid;
						if (Airfields[j]  == ((BritSquadron*)sq)->moveto)
							index = j;
						j++;
					}
				}
			}
		}
		i++;
	}
	Airfields[j] = UID_NULL;
	return (index);
}


void SquadronDetails::Refresh()
{
	CRStatic*   s;

//DeadCode RDH 16Sep00 	if (	(!movedalready)
//DeadCode RDH 16Sep00 		)
	if (sqnum<SQ_LW_START)
	{
		CRCombo* combo;
 		combo=GETDLGITEM(IDC_RCOMBOGROUP);
		combo->ShowWindow(true);
		combo->Clear()->RESCOMBO(10,4);
		 s=GETDLGITEM(IDC_RSTATICMOVETO);
		 s->ShowWindow(SW_SHOW);
		
		int i = group - IDS_GROUP_10;
		combo->SetIndex(i);

		int index = FillAirfieldList();
		if (movedalready)
			afindex = index;											//RDH 16Sep00

 		combo=GETDLGITEM(IDC_RCOMBOAIRFIELD);
		combo->ShowWindow(true);
		combo->Clear();
		if (Airfields[0] == UID_NULL)
		{
			combo->AddString(RESSTRING(NONEAVAIL));
			combo->SetIndex(0);
		}else
		{
			int af =0 ;
			combo->AddString(RESSTRING(SELECTAIRFIELD));
			while (Airfields[af] != UID_NULL)
			{
				TargetSectorField* afield;
	 			CString afstring = GetTargName(Airfields[af++]);
				combo->AddString(afstring);
			}
			Squadron* sq = &Node_Data[sqnum];

			if (((BritSquadron*)sq)->moveto != NULL) 
				combo->SetIndex(afindex+1);
			else
				combo->SetIndex(0);
		}
		 s=GETDLGITEM(IDC_RSTATICMOVETO);
		 s->ShowWindow(SW_SHOW);
 	}
//DeadCode JIM 19Sep00 else
//DeadCode RDH 16Sep00 	{
//DeadCode RDH 16Sep00 		CRCombo* combo;
//DeadCode RDH 16Sep00  		combo=GETDLGITEM(IDC_RCOMBOGROUP);
//DeadCode RDH 16Sep00 		combo->ShowWindow(false);
//DeadCode RDH 16Sep00  		combo=GETDLGITEM(IDC_RCOMBOAIRFIELD);
//DeadCode RDH 16Sep00 		combo->ShowWindow(false);
//DeadCode RDH 16Sep00 		 s=GETDLGITEM(IDC_RSTATICMOVETO);
//DeadCode RDH 16Sep00 		 s->ShowWindow(SW_HIDE);
//DeadCode RDH 16Sep00 		
//DeadCode RDH 16Sep00 
//DeadCode RDH 16Sep00 	}
//DeadCode RDH 16Sep00 

}

BEGIN_EVENTSINK_MAP(SquadronDetails, CDialog)
    //{{AFX_EVENTSINK_MAP(SquadronDetails)
	ON_EVENT(SquadronDetails, IDC_RBUTTONSQUADRON, 1 /* Clicked */, OnClickedRbuttonsquadron, VTS_NONE)
	ON_EVENT(SquadronDetails, IDC_RBUTTONAIRFIELD, 1 /* Clicked */, OnClickedRbuttonairfield, VTS_NONE)
	ON_EVENT(SquadronDetails, IDC_RCOMBOREQUIRED, 1 /* TextChanged */, OnTextChangedRcomborequired, VTS_BSTR VTS_I2)
	ON_EVENT(SquadronDetails, IDC_RCOMBOGROUP, 1 /* TextChanged */, OnTextChangedRcombogroup, VTS_BSTR VTS_I2)
	ON_EVENT(SquadronDetails, IDC_RCOMBOAIRFIELD, 1 /* TextChanged */, OnTextChangedRcomboairfield, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void SquadronDetails::OnClickedRbuttonsquadron() 
{
#ifndef	BOB_DEMO_VER

	MainToolBar().OpenDiary(sqnum);
#endif	
}

void SquadronDetails::OnClickedRbuttonairfield() 
{
#ifndef	BOB_DEMO_VER

	Squadron* sq = &Node_Data[sqnum];

	m_pView->ZoomToUID(UniqueID(sq->homeairfield),m_pView->m_zoom);
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	   		MainToolBar().OpenDossier(UniqueID(sq->homeairfield));
#endif
}
void SquadronDetails::OnTextChangedRcomborequired(LPCTSTR Caption, short index) 
{
#ifndef	BOB_DEMO_VER

		Squadron* sq = &Node_Data[sqnum];
	//TIME UNITS ARE IN 20 SECOND INTERVALS
	UByte status = -1;
	int time = 3;  //it takes a minute to change orders to lower readiness
	switch (index)
	{
		case	0:
		{
			break;
		}
		case	1:
		{
			status = Profile::PS_OFFBASE;
			break;
		}
		case	2:
		{
			status = Profile::PS_ORDER_30;
			if (sq->totestatus == Profile::PS_SPARE)
				time = 0;		//I have a special to fix this at next period
			break;
		}
		case	3:
		{
			status = Profile::PS_ORDER_5;
			if (sq->totestatus == Profile::PS_SPARE)
				time = 720;
			else if (sq->totestatus < Profile::PS_ORDER_5)
				time = 75;
			break;
		}
		case	4:
		{
			status = Profile::PS_ORDER_2;
			if (sq->totestatus < Profile::PS_ORDER_30)
				time = 720;
			else if (sq->totestatus < Profile::PS_ORDER_5)
				time = 75;
			else if (sq->totestatus < Profile::PS_ORDER_2)
				time = 9;
			break;
		}
	}
	if (status != -1)
	{
		switch (status)
		{
		case  Profile::PS_SPARE:
			Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ORDERSRELEASED,sq->homeairfield,UID_NULL,TargetIndexes(sq->squadron,sq->ACTotal()));
		break;
		case  Profile::PS_ORDER_30:
			Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ORDERS30MINS,sq->homeairfield,UID_NULL,TargetIndexes(sq->squadron,sq->ACTotal()));
		break;
		case  Profile::PS_ORDER_5:
			Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ORDERSREADINESS,sq->homeairfield,UID_NULL,TargetIndexes(sq->squadron,sq->ACTotal()));
		break;
		case  Profile::PS_ORDER_2:
			Node_Data.intel.AddMessage(IntelMsg::MED_MANAGEMENT_MAN,AS_NOTSWITCH,SCRIPT_ORDERSSTANDBY,sq->homeairfield,UID_NULL,TargetIndexes(sq->squadron,sq->ACTotal()));
		break;
		}
//TEMPCODE DAW 10/03/00 		if (status > sq->totestatus)
		//If you don't put a time in then I will never process the order.
		BritSquadronPtr(sq)->totetimer = time;
		sq->totestatus = status;
	}
#endif
}

void SquadronDetails::OnTextChangedRcombogroup(LPCTSTR Caption, short index) 
{
	group = IDS_GROUP_10 + index;
	afindex = 0;
	Refresh();

}

void SquadronDetails::OnTextChangedRcomboairfield(LPCTSTR Caption, short index) 
{
		Squadron* sq = &Node_Data[sqnum];
		if (index > 0)
		{
			((BritSquadron*)sq)->moveto = Airfields[index-1];
		 	afindex = FillAirfieldList();
			Refresh();

		}
	
}
void NodeData::SetRAFReadiness()
{
	FillRAFStrengthInfo(true);
	int i = 0;
	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
		  )
	{

		int minac, minpilot, mincat;
		if (Todays_Packages.britishisauto)
		{
			minac = 6;
			minpilot = 6;
			mincat = 2;
		}else
		{
			minac = MMC.directives.raf.current.restifavailbelow;
			minpilot = MMC.directives.raf.current.restifavailbelow;	//MMC.sl_min_pilot; // There is no way to set up this factor!
			mincat = MMC.directives.raf.current.restifcatbelow;
		}


		if (	(		(Node_Data.squadron[i].pilotsavail < minpilot)
					||	(Node_Data.squadron[i].acavail < minac)
					||	(Node_Data.squadron[i].Category() >= mincat)
				)
				&&
				(		(RAFstrengthinfo[RAFTOTAL].acready > 100)
				)
		   )
		{
			Node_Data.squadron[i].totestatus = Profile::PS_OFFBASE;
		}
		else 
			if (	Node_Data.squadron[i].homeairfield!=UID_AF_NEWCASTLE
				&&	Node_Data[Node_Data.squadron[i].homeairfield].truestatus<Target::TS_NEARLYDESTROYED
				&&  TargetFighterFieldPtr(Node_Data[Node_Data.squadron[i].homeairfield])->subdamagelevels[TargetFighterField::SDL_RUNWAY]<Target::TS_NEARLYDESTROYED
				) 
			{
//DeadCode JIM 4Oct00 			if (Todays_Packages.britishisauto)		 //Mark asked for this...
				Node_Data.squadron[i].totestatus = Profile::PS_ORDER_5;
				Node_Data.squadron[i].totetimer = 60;	//All at same time to shut up woman!
			}
		i++;
	 }
	FillRAFStrengthInfo(true);

}
void NodeData::SetRAFReadiness(Profile::PackageStatus ps)
{
//DEADCODE RDH 31/05/00 	if (Todays_Packages.britishisauto)
//DEADCODE RDH 11/04/00  	if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//DEADCODE RDH 11/04/00 			||	(RFullPanelDial::gamestate == RFullPanelDial::PILOT)
//DEADCODE RDH 11/04/00 		)								  britishisauto
	{
		int i = 0;
		while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
			  )
		{
			Node_Data.squadron[i].totestatus = ps;
			i++;
		}
							  
	}


}
