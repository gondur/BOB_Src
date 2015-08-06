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

// RowanDialog: // AfDetl.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "AfDetl.h"
#include "overlay.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// AirfieldDetails dialog


RDialog*	AirfieldDetails::Make(UniqueID  uid)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new AirfieldDetails(uid))
			);
}


AirfieldDetails::AirfieldDetails(UniqueID  uid,CWnd* pParent /*=NULL*/)
	: RowanDialog(AirfieldDetails::IDD, pParent)
{
	//{{AFX_DATA_INIT(AirfieldDetails)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	afuid = uid;
}


void AirfieldDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AirfieldDetails)
	DDX_Control(pDX, IDC_RSTATICFIELD, m_IDC_RSTATICFIELD);
	DDX_Control(pDX, IDC_RSTATICHURRSQUAD, m_IDC_RSTATICHURRSQUAD);
	DDX_Control(pDX, IDC_RSTATICMAXSQUAD, m_IDC_RSTATICMAXSQUAD);
	DDX_Control(pDX, IDC_RSTATICREFUEL, m_IDC_RSTATICREFUEL);
	DDX_Control(pDX, IDC_RSTATICREPAIR, m_IDC_RSTATICREPAIR);
	DDX_Control(pDX, IDC_RSTATICSECTOROPS, m_IDC_RSTATICSECTOROPS);
	DDX_Control(pDX, IDC_RSTATICSPITSQUAD, m_IDC_RSTATICSPITSQUAD);
	DDX_Control(pDX, IDC_RSTATICSTAFF, m_IDC_RSTATICSTAFF);
	DDX_Control(pDX, IDC_RBUTTONCENTRE, m_IDC_RBUTTONCENTRE);
	DDX_Control(pDX, IDC_DOSSNOTES, m_IDC_DOSSNOTES);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AirfieldDetails, CDialog)
	//{{AFX_MSG_MAP(AirfieldDetails)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AirfieldDetails message handlers

BOOL AirfieldDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	TargetFighterField* af;
	af = Node_Data[afuid];

	CRStatic*   s;
	s= GETDLGITEM(IDC_RSTATICSECTOROPS);
 	TargetSectorField*	sectorfield = af->getsectoraf();
	UniqueID  uid = sectorfield->primarycontrolcentre;

	TargetGroup* sector;
	sector = Node_Data[uid];
	if ((sector) && (sector->truestatus >= Target::TS_DESTROYED))
		uid = sectorfield->secondarycontrolcentre;

	s->SetString(GetTargName(uid));

	UByte damage;
	s= GETDLGITEM(IDC_RSTATICREFUEL);
	
	damage = af->subdamagelevels[TargetFighterField::SDL_FUEL];
	damage = damage/25;
	if (damage >3)
		damage = 3;
#ifndef	NDEBUG
	#define SHOWNUMDEBUG(val)	+CSprintf(" (%i%%)",val)
#else
	#define SHOWNUMDEBUG(val)
#endif

	s->SetString(RESLIST(UNDAMAGED,damage) SHOWNUMDEBUG(af->subdamagelevels[TargetFighterField::SDL_FUEL]));

	s= GETDLGITEM(IDC_RSTATICREPAIR);
	damage = af->subdamagelevels[TargetFighterField::SDL_REPAIR];
	damage = damage/25;
	if (damage >3)
		damage = 3;
	s->SetString(RESLIST(UNDAMAGED,damage) SHOWNUMDEBUG(af->subdamagelevels[TargetFighterField::SDL_REPAIR]));

	s= GETDLGITEM(IDC_RSTATICFIELD);
	damage = af->subdamagelevels[TargetFighterField::SDL_RUNWAY];
	damage = damage/25;
	if (damage >3)
		damage = 3;
	s->SetString(RESLIST(UNDAMAGED,damage) SHOWNUMDEBUG(af->subdamagelevels[TargetFighterField::SDL_RUNWAY]));


	s= GETDLGITEM(IDC_RSTATICSTAFF);
	damage = af->subdamagelevels[TargetFighterField::SDL_STAFF];
	damage = damage/25;
	if (damage >3)
		damage = 3;
	s->SetString(RESLIST(UNDAMAGED,damage) SHOWNUMDEBUG(af->subdamagelevels[TargetFighterField::SDL_STAFF]));

//DeadCode JIM 20Oct00 	int ac = 16;
	s= GETDLGITEM(IDC_RSTATICMAXSQUAD);

	s->SetString(CSprintf("%i", af->maxsquads));

	int k=0, spitsq = 0, hurrsq = 0;
	while (Node_Data.squadron[k].squadron != SQ_ZERO)
	{
 		if (Node_Data.squadron[k].homeairfield == afuid)
		{
			BritSquadron* sq = Node_Data.squadron[k];
			PlaneTypeSelect type = sq->AcType();
			if (		(type == PT_SPIT_A)
					||	(type == PT_SPIT_B)
			   )
				spitsq++;
			else
				hurrsq++;
		}
		k++;
	}


 	s= GETDLGITEM(IDC_RSTATICSPITSQUAD);
	s->SetString(CSprintf("%i", spitsq));
	s= GETDLGITEM(IDC_RSTATICHURRSQUAD);
	s->SetString(CSprintf("%i", hurrsq));
	
	CString notes="";
	for (int pack = Profile::MAX_PACKS-1,lines=3;lines>0 && pack>=0;pack--)
	{
		if (Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
		{
		 	Profile *pk = &Todays_Packages.pack[pack];
			bool	packfound;
			if (pk->raidnumentries[0].raidnum)
			for(int targetnum = 0;(pk->packagetarget[targetnum].currentid);targetnum++	)
			{
				packfound=false;
				if (pk->packagetarget[targetnum].currentid == afuid)
					packfound=true;
				else
					if (pk->packagetarget[targetnum].currentid <= SagBANDEND)
					{
						int tp,ts;
						if (Todays_Packages.GetACSquadEntry(pk->packagetarget[targetnum].currentid,tp,ts))
							if (Todays_Packages[tp].SquadTarget(ts)==afuid)
								packfound=true;
					}
				if (packfound)
				{
					notes=CString("   ")+ RESLIST(AM_PATROL,pk->attackmethod)+":    "+RESLIST(PS_SPARE,pk->packagestatus)+"\n"+notes;
					lines--;
				}

			}
		}
		
	}
	s= GETDLGITEM(IDC_DOSSNOTES);
#ifndef	NDEBUG
	notes+=CSprintf("Damage Levels: True: %i%% LWIntel: %i%%\n",af->truestatus,af->knownstatus);
#endif
	if (notes!="")
		s->SetString(RESSTRING(MISSIONS)+":\n"+notes);
	else
		s->SetString(notes);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(AirfieldDetails, CDialog)
    //{{AFX_EVENTSINK_MAP(AirfieldDetails)
	ON_EVENT(AirfieldDetails, IDC_RBUTTONCENTRE, 1 /* Clicked */, OnClickedRbuttoncentre, VTS_NONE)
	ON_EVENT(AirfieldDetails, IDC_PHOTO, 1 /* Clicked */, OnClickedPhoto, VTS_NONE)
	ON_EVENT(AirfieldDetails, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void AirfieldDetails::OnClickedRbuttoncentre() 
{
	m_pView->ZoomToUID(afuid,m_pView->m_zoom);
 	
}
void AirfieldDetails::OnClickedAuthorise() 
{
#ifndef	BOB_DEMO_VER

//DeadCode JIM 9Oct00   	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//DeadCode JIM 9Oct00 	{
//DeadCode JIM 9Oct00 		
//DeadCode JIM 9Oct00 		int packnum=Todays_Packages_NewPackage(uid,MMC.directives.lw.userprofiles[Directives::LW::ATTACK]);
//DeadCode JIM 9Oct00 		if (packnum < 0)
//DeadCode JIM 9Oct00 			RDialog::RMessageBox(IDS_WARNING, IDS_NOAIRCRAFTAVAIL,NULL,NULL,IDS_CONTINUE);
//DeadCode JIM 9Oct00 		else
//DeadCode JIM 9Oct00 		{
//DeadCode JIM 9Oct00 			Todays_Packages[packnum].CalcRoutePositionsAndTime();
//DeadCode JIM 9Oct00 			MainToolBar().OnClickedMissionfolder();
//DeadCode JIM 9Oct00 			Todays_Packages.InvalidateRoute(&Todays_Packages[packnum],true,true);
//DeadCode JIM 9Oct00 		}
//DeadCode JIM 9Oct00 	}else
	{
			
		int	packnum=Todays_Packages_NewPackage(afuid,
							MMC.directives.raf.userprofiles[Directives::RAF::PATROL]);					
		if (packnum < 0)
			RDialog::RMessageBox(IDS_WARNING, IDS_NOAIRCRAFTAVAIL,NULL,NULL,IDS_CONTINUE);
		else
		{
			Todays_Packages[packnum].CalcRoutePositionsAndTime();
			MainToolBar().OnClickedMissionfolder();
			Todays_Packages.InvalidateRoute(&Todays_Packages[packnum],true,true);
		}

	}
#endif
}

void AirfieldDetails::OnClickedPhoto() 
{
#ifndef	BOB_DEMO_VER

 	{
#ifndef NDEBUG
#define PLACEMENT	CRect(0,0,512,384)
#else
#define	PLACEMENT	Place(POSN_CENTRE,POSN_CENTRE, 0, 0)
#endif
//	#define PLACEMENT	CRect(0,0,512,384)
		UniqueID targID=UniqueID(afuid);
		CString tname=GetTargName(targID);
		OverLay.SetTargName((char*)LPCTSTR(tname));
		OverLay.loader_art=FIL_LOADING;									//RJS 16Aug00
		LogChild(0,MakeTopDialog(PLACEMENT,DialBox(OverLay.loader_art,new Rtestsh1(UniqueID(afuid)),EDGES_NOSCROLLBARS)));
		Rtestsh1::Start3d(Rtestsh1::S3D_DONEBACK);
	}
#endif
	
}
