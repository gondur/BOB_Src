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

// RowanDialog: // CntrlFly.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "CntrlFly.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// ControlFly dialog


RDialog*	ControlFly::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new ControlFly())
			);
}


ControlFly::ControlFly(CWnd* pParent /*=NULL*/)
	: RowanDialog(ControlFly::IDD, pParent)
{
	//{{AFX_DATA_INIT(ControlFly)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ControlFly::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ControlFly)
	DDX_Control(pDX, IDC_GROUNDATTACK_ALL, m_IDC_GROUNDATTACK_ALL);
	DDX_Control(pDX, IDC_GROUNDATTACK_FAV, m_IDC_GROUNDATTACK_FAV);
	DDX_Control(pDX, IDC_LANDING_FAV, m_IDC_LANDING_FAV);
	DDX_Control(pDX, IDC_TO_FAV, m_IDC_TO_FAV);
	DDX_Control(pDX, IDC_SMALLENGAGEMENT_FAV, m_IDC_SMALLENGAGEMENT_FAV);
	DDX_Control(pDX, IDC_LARGEENGAGEMENT_FAV, m_IDC_LARGEENGAGEMENT_FAV);
	DDX_Control(pDX, IDC_LOSSES_FAV, m_IDC_LOSSES_FAV);
	DDX_Control(pDX, IDC_TO_ALL, m_IDC_TO_ALL);
	DDX_Control(pDX, IDC_SMALLENGAGEMENT_ALL, m_IDC_SMALLENGAGEMENT_ALL);
	DDX_Control(pDX, IDC_LARGEENGAGEMENT_ALL, m_IDC_LARGEENGAGEMENT_ALL);
	DDX_Control(pDX, IDC_LOSSES_ALL, m_IDC_LOSSES_ALL);
	DDX_Control(pDX, IDC_RCOMBOAIRCRAFT, m_IDC_RCOMBOAIRCRAFT);
	DDX_Control(pDX, IDC_RCOMBOSQUADRON, m_IDC_RCOMBOSQUADRON);
	DDX_Control(pDX, IDC_RCOMBOSECTOR, m_IDC_RCOMBOSECTOR);
	DDX_Control(pDX, IDC_REACHCOAST_FAV, m_IDC_REACHCOAST_FAV);
	DDX_Control(pDX, IDC_REACHCOAST_ALL, m_IDC_REACHCOAST_ALL);
	DDX_Control(pDX, IDC_RCOMBOGROUP, m_IDC_RCOMBOGROUP);
	DDX_Control(pDX, IDC_LANDING_ALL, m_IDC_LANDING_ALL);
	DDX_Control(pDX, IDC_RSTATICCTRL_0, m_IDC_RSTATICCTRL_0);
	DDX_Control(pDX, IDC_RSTATICCTRL_1, m_IDC_RSTATICCTRL_1);
	DDX_Control(pDX, IDC_RSTATICCTRL_2, m_IDC_RSTATICCTRL_2);
	DDX_Control(pDX, IDC_RSTATICCTRL_3, m_IDC_RSTATICCTRL_3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ControlFly, CDialog)
	//{{AFX_MSG_MAP(ControlFly)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ControlFly message handlers

void ControlFly::FindSquadrons()
{
 	int j=0, i = 0;
	Favorite[j++] = -1;

	while (		(Node_Data.squadron[i].squadron != SQ_ZERO)
			&&	(j < MAX_SQUAD)			
		  )
	{
		PlaneTypeSelect	actype = Node_Data.squadron[i].AcType();
		if  (	(MMC.fav.ac == 0)
				||
				(
					(MMC.fav.ac == 1)
					&&  (		(actype == PT_SPIT_A)
							||	(actype == PT_SPIT_B) 
						)

				)
				||
				(	(MMC.fav.ac == 2)
					&&  (		(actype == PT_HURR_A)
							||	(actype == PT_HURR_B) 
						)
				)
			)
		{
			UniqueID uid = Node_Data.squadron[i].homeairfield;
			TargetFighterField* af;
			af = Node_Data[uid];
		 	TargetSectorField*	sectorfield = af->getsectoraf();
			if	(	(MMC.fav.group == 0)
					||
					(sectorfield->groupname == IDS_GROUP_10+MMC.fav.group-1)
				)
			{
				{
					  Favorite[j] = i;
						j++;
				}
			}
		}
	  i++;
	 }
	maxsquads = j;
}


void ControlFly::RefreshSector()
{
}
void ControlFly::RefreshSquadron()
{
	FindSquadrons();
	CRCombo* combo;

	combo=GETDLGITEM(IDC_RCOMBOSQUADRON);
	combo->Clear();
			
	if (maxsquads > 0)
	{
		combo->ShowWindow(true);
		bool indexset = false;
		for (int i = 0; i < maxsquads; i++)
		{
			if (i)
			{
				combo->AddString(Node_Data.squadron[Favorite[i]].SubName());

				if (MMC.fav.squadron == 	Node_Data.squadron[Favorite[i]].squadron)
				{
					combo->SetIndex(i);
					indexset = true;
				}
			}else
			{
				combo->AddString(RESSTRING(L_ANY));
			}
		}
//DEADCODE RDH 19/04/00 		if	(MMC.favgroup < maxsquads) 
//DEADCODE RDH 19/04/00 			combo->SetIndex(MMC.favsquadron);
//DEADCODE RDH 19/04/00 		else
		if (!indexset)
		{
			combo->SetIndex(0);
			MMC.fav.squadron = 0;
		}
	}else
		combo->ShowWindow(false);

}
void ControlFly::FindGeschwader()
{
	int i = 0;
	int j = 0;
	Favorite[j++] = -1;
	while (Node_Data.geschwader[i].wadernum != 0)
	{
		if (	(	(!MMC.fav.flotte)
					||
					(MMC.fav.flotte == Node_Data.geschwader[i].luftflotte)
				)
				&&	(MMC.fav.geschwadertype  == Node_Data.geschwader[i].wadername)
		   )
		{
			Favorite[j++] = i;
		}
		i++;
	}
	maxsquads = j;
}
void ControlFly::RefreshGeschwader()
{
	FindGeschwader();	
	CRCombo* combo;

	combo=GETDLGITEM(IDC_RCOMBOSECTOR);
	combo->ShowWindow(true);
	combo->Clear();
	bool indexset = false;
		if (maxsquads > 0)
	{
		combo->ShowWindow(true);

		for (int i = 0; i < maxsquads; i++)
		{
			if (i)
			{
				combo->AddString(RESLIST(J, Node_Data.geschwader[Favorite[i]].wadername)
								+ CSprintf("%i",	Node_Data.geschwader[Favorite[i]].wadernum) 
								);
				if (MMC.fav.geschwader == Favorite[i])
				{
					combo->SetIndex(i);
					indexset = true;
				}
			}else
			{
				combo->AddString(RESSTRING(L_ANY));
			}
		}
		if	(!indexset) 
		{
			combo->SetIndex(0);
			MMC.fav.geschwader = -1;
		}
	}else
		combo->ShowWindow(false);


 	
}

void ControlFly::RefreshCombos()
{
		CRStatic*   s;
	CRCombo* combo;

  	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{

		s = GETDLGITEM(IDC_RSTATICCTRL_0);
		s->SetString(RESSTRING(LUFTFLOTTE));
		s = GETDLGITEM(IDC_RSTATICCTRL_1);
		s->SetString(RESSTRING(GESCHWADERTYPE));
		s = GETDLGITEM(IDC_RSTATICCTRL_2);
		s->ShowWindow(true);
		s->SetString(RESSTRING(GESCHWADER));
		s = GETDLGITEM(IDC_RSTATICCTRL_3);
		s->SetString(RESSTRING(GRUPPE));

		combo=GETDLGITEM(IDC_RCOMBOGROUP);
		combo->Clear();
		combo->AddString(RESSTRING(LUFTFLOTTEBOTH));
		combo->AddString(RESSTRING(L_LUFTFLOTTE2));
		combo->AddString(RESSTRING(L_LUFTFLOTTE3));
		int index =MMC.fav.flotte;
		if (index > 1)
			index = index -1;
		combo->SetIndex(index);
		
		combo=GETDLGITEM(IDC_RCOMBOAIRCRAFT);
		if (MMC.fav.geschwadertype == WN_BETTERRULE)
			index = 0;
		else
			index = MMC.fav.geschwadertype+ 1;
		combo->Clear()->RESCOMBO(ANY_A,5)->
					SetIndex(index);

		combo=GETDLGITEM(IDC_RCOMBOSQUADRON);
		combo->Clear()->RESCOMBO(ANY,4)->
					SetIndex(MMC.fav.gruppe);

		RefreshGeschwader();

	}else
	{
		s = GETDLGITEM(IDC_RSTATICCTRL_0);
		s->SetString(RESSTRING(GROUP));
		s = GETDLGITEM(IDC_RSTATICCTRL_1);
		s->SetString(RESSTRING(AIRCRAFT));
		s = GETDLGITEM(IDC_RSTATICCTRL_2);
//DEADCODE RDH 25/04/00 		s->SetString(RESSTRING(SECTOR));
		s->ShowWindow(false);
		combo=GETDLGITEM(IDC_RCOMBOSECTOR);
		combo->ShowWindow(false);

		s = GETDLGITEM(IDC_RSTATICCTRL_3);
		s->SetString(RESSTRING(SQUADRON));


		combo=GETDLGITEM(IDC_RCOMBOGROUP);
		combo->Clear()->RESCOMBO(GRP_ANY,4)->
					SetIndex(MMC.fav.group);
		
		combo=GETDLGITEM(IDC_RCOMBOAIRCRAFT);
		combo->Clear()->RESCOMBO(EITHERAC,3)->
					SetIndex(MMC.fav.ac);
		RefreshSector();
		RefreshSquadron();
	}
 

}

BOOL ControlFly::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRButton* b = GETDLGITEM(IDC_GROUNDATTACK_FAV);
	b->SetPressed(MMC.fav.flyonfav[AS_TARG]);
	
	b = GETDLGITEM(IDC_LANDING_FAV);
	b->SetPressed(MMC.fav.flyonfav[AS_LAND]);

	b = GETDLGITEM(IDC_TO_FAV);
	b->SetPressed(MMC.fav.flyonfav[AS_TAKEOFF]);

	b = GETDLGITEM(IDC_SMALLENGAGEMENT_FAV);
	b->SetPressed(MMC.fav.flyonfav[AS_SMALL_ENGAGEMENT]);

	b = GETDLGITEM(IDC_LARGEENGAGEMENT_FAV);
	b->SetPressed(MMC.fav.flyonfav[AS_LARGE_ENGAGEMENT]);

	b = GETDLGITEM(IDC_LOSSES_FAV);
	b->SetPressed(MMC.fav.flyonfav[AS_LOSSES]);

	b = GETDLGITEM(IDC_REACHCOAST_FAV);
	b->SetPressed(MMC.fav.flyonfav[AS_COAST]);


	b = GETDLGITEM(IDC_GROUNDATTACK_ALL);
	b->SetPressed(MMC.fav.flyon[AS_TARG]);
	
	b = GETDLGITEM(IDC_LANDING_ALL);
	b->SetPressed(MMC.fav.flyon[AS_LAND]);

	b = GETDLGITEM(IDC_TO_ALL);
	b->SetPressed(MMC.fav.flyon[AS_TAKEOFF]);

	b = GETDLGITEM(IDC_SMALLENGAGEMENT_ALL);
	b->SetPressed(MMC.fav.flyon[AS_SMALL_ENGAGEMENT]);

	b = GETDLGITEM(IDC_LARGEENGAGEMENT_ALL);
	b->SetPressed(MMC.fav.flyon[AS_LARGE_ENGAGEMENT]);

	b = GETDLGITEM(IDC_LOSSES_ALL);
	b->SetPressed(MMC.fav.flyon[AS_LOSSES]);

	b = GETDLGITEM(IDC_REACHCOAST_ALL);
	b->SetPressed(MMC.fav.flyon[AS_COAST]);

	RefreshCombos();

	//for LW: Lflotte, Geschwader type, Geschwader, Gruppe	
	//add separate set on MMC for RAF and LW
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(ControlFly, CDialog)
    //{{AFX_EVENTSINK_MAP(ControlFly)
	ON_EVENT(ControlFly, IDC_GROUNDATTACK_ALL, 1 /* Clicked */, OnClickedGroundattackAll, VTS_NONE)
	ON_EVENT(ControlFly, IDC_GROUNDATTACK_FAV, 1 /* Clicked */, OnClickedGroundattackFav, VTS_NONE)
	ON_EVENT(ControlFly, IDC_LANDING_ALL, 1 /* Clicked */, OnClickedLandingAll, VTS_NONE)
	ON_EVENT(ControlFly, IDC_LANDING_FAV, 1 /* Clicked */, OnClickedLandingFav, VTS_NONE)
	ON_EVENT(ControlFly, IDC_LARGEENGAGEMENT_ALL, 1 /* Clicked */, OnClickedLargeengagementAll, VTS_NONE)
	ON_EVENT(ControlFly, IDC_LARGEENGAGEMENT_FAV, 1 /* Clicked */, OnClickedLargeengagementFav, VTS_NONE)
	ON_EVENT(ControlFly, IDC_LOSSES_ALL, 1 /* Clicked */, OnClickedLossesAll, VTS_NONE)
	ON_EVENT(ControlFly, IDC_LOSSES_FAV, 1 /* Clicked */, OnClickedLossesFav, VTS_NONE)
	ON_EVENT(ControlFly, IDC_REACHCOAST_ALL, 1 /* Clicked */, OnClickedReachcoastAll, VTS_NONE)
	ON_EVENT(ControlFly, IDC_REACHCOAST_FAV, 1 /* Clicked */, OnClickedReachcoastFav, VTS_NONE)
	ON_EVENT(ControlFly, IDC_SMALLENGAGEMENT_ALL, 1 /* Clicked */, OnClickedSmallengagementAll, VTS_NONE)
	ON_EVENT(ControlFly, IDC_SMALLENGAGEMENT_FAV, 1 /* Clicked */, OnClickedSmallengagementFav, VTS_NONE)
	ON_EVENT(ControlFly, IDC_TO_ALL, 1 /* Clicked */, OnClickedToAll, VTS_NONE)
	ON_EVENT(ControlFly, IDC_TO_FAV, 1 /* Clicked */, OnClickedToFav, VTS_NONE)
	ON_EVENT(ControlFly, IDC_RCOMBOAIRCRAFT, 1 /* TextChanged */, OnTextChangedRcomboaircraft, VTS_BSTR VTS_I2)
	ON_EVENT(ControlFly, IDC_RCOMBOGROUP, 1 /* TextChanged */, OnTextChangedRcombogroup, VTS_BSTR VTS_I2)
	ON_EVENT(ControlFly, IDC_RCOMBOSECTOR, 1 /* TextChanged */, OnTextChangedRcombosector, VTS_BSTR VTS_I2)
	ON_EVENT(ControlFly, IDC_RCOMBOSQUADRON, 1 /* TextChanged */, OnTextChangedRcombosquadron, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void ControlFly::OnClickedGroundattackAll() 
{
	if	(MMC.fav.flyon[AS_TARG])
	   MMC.fav.flyon %= AS_TARG;
	else
	   MMC.fav.flyon |= AS_TARG;
	
}

void ControlFly::OnClickedGroundattackFav() 
{
	if	(MMC.fav.flyonfav[AS_TARG])
	   MMC.fav.flyonfav %= AS_TARG;
	else
	   MMC.fav.flyonfav |= AS_TARG;
	
}

void ControlFly::OnClickedLandingAll() 
{
	if	(MMC.fav.flyon[AS_LAND])
	   MMC.fav.flyon %= AS_LAND;
	else
	   MMC.fav.flyon |= AS_LAND;
	
}

void ControlFly::OnClickedLandingFav() 
{
	if	(MMC.fav.flyonfav[AS_LAND])
	   MMC.fav.flyonfav %= AS_LAND;
	else
	   MMC.fav.flyonfav |= AS_LAND;
	
}

void ControlFly::OnClickedLargeengagementAll() 
{
	if	(MMC.fav.flyon[AS_LARGE_ENGAGEMENT])
	   MMC.fav.flyon %= AS_LARGE_ENGAGEMENT;
	else
	   MMC.fav.flyon |= AS_LARGE_ENGAGEMENT;
	
}

void ControlFly::OnClickedLargeengagementFav() 
{
	if	(MMC.fav.flyonfav[AS_LARGE_ENGAGEMENT])
	   MMC.fav.flyonfav %= AS_LARGE_ENGAGEMENT;
	else
	   MMC.fav.flyonfav |= AS_LARGE_ENGAGEMENT;
	
}

void ControlFly::OnClickedLossesAll() 
{
	if	(MMC.fav.flyon[AS_LOSSES])
	   MMC.fav.flyon %= AS_LOSSES;
	else
	   MMC.fav.flyon |= AS_LOSSES;
	
}

void ControlFly::OnClickedLossesFav() 
{
	if	(MMC.fav.flyonfav[AS_LOSSES])
	   MMC.fav.flyonfav %= AS_LOSSES;
	else
	   MMC.fav.flyonfav |= AS_LOSSES;
	
}

void ControlFly::OnClickedReachcoastAll() 
{
	if	(MMC.fav.flyon[AS_COAST])
	   MMC.fav.flyon %= AS_COAST;
	else
	   MMC.fav.flyon |= AS_COAST;
	
}

void ControlFly::OnClickedReachcoastFav() 
{
	if	(MMC.fav.flyonfav[AS_COAST])
	   MMC.fav.flyonfav %= AS_COAST;
	else
	   MMC.fav.flyonfav |= AS_COAST;
	
}

void ControlFly::OnClickedSmallengagementAll() 
{
	if	(MMC.fav.flyon[AS_SMALL_ENGAGEMENT])
	   MMC.fav.flyon %= AS_SMALL_ENGAGEMENT;
	else
	   MMC.fav.flyon |= AS_SMALL_ENGAGEMENT;
	
}

void ControlFly::OnClickedSmallengagementFav() 
{
	if	(MMC.fav.flyonfav[AS_SMALL_ENGAGEMENT])
	   MMC.fav.flyonfav %= AS_SMALL_ENGAGEMENT;
	else
	   MMC.fav.flyonfav |= AS_SMALL_ENGAGEMENT;
	
}

void ControlFly::OnClickedToAll() 
{
	if	(MMC.fav.flyon[AS_TAKEOFF])
	   MMC.fav.flyon %= AS_TAKEOFF;
	else
	   MMC.fav.flyon |= AS_TAKEOFF;
	
}

void ControlFly::OnClickedToFav() 
{
	if	(MMC.fav.flyonfav[AS_TAKEOFF])
	   MMC.fav.flyonfav %= AS_TAKEOFF;
	else
	   MMC.fav.flyonfav |= AS_TAKEOFF;
	
}

void ControlFly::OnTextChangedRcomboaircraft(LPCTSTR Caption, short index) 
{
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (index == 0)
			MMC.fav.geschwadertype = WN_BETTERRULE;
		else
			MMC.fav.geschwadertype = index -1;
		RefreshCombos();
	}else
	{
		MMC.fav.ac = index;
		RefreshCombos();
	}
}

void ControlFly::OnTextChangedRcombogroup(LPCTSTR Caption, short index) 
{
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (index > 0)
			index = index + 1;
		MMC.fav.flotte = index;
		RefreshCombos();
	}else
	{
		MMC.fav.group = index;
		RefreshCombos();

	}
}

void ControlFly::OnTextChangedRcombosector(LPCTSTR Caption, short index) 
{
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		int fav = Favorite[index];
		if (fav >= 0)
			MMC.fav.geschwader = fav;
		else
			MMC.fav.geschwader = -1;

	}else
		MMC.fav.sector = index;
	RefreshCombos();
	
}

void ControlFly::OnTextChangedRcombosquadron(LPCTSTR Caption, short index) 
{
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		MMC.fav.gruppe = index;

	}else
	{
		int fav = Favorite[index];
		if (fav >= 0)
			MMC.fav.squadron = 	Node_Data.squadron[fav].squadron;

		else
			MMC.fav.squadron = 0;

		
	}
	RefreshCombos();

	
}
