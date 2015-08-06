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

// RowanDialog: // MFTarget.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "MFTarget.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// MapFiltersTarget dialog


RDialog*	MapFiltersTarget::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new MapFiltersTarget())
			);
}


MapFiltersTarget::MapFiltersTarget(CWnd* pParent /*=NULL*/)
	: RowanDialog(MapFiltersTarget::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapFiltersTarget)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MapFiltersTarget::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MapFiltersTarget)
	DDX_Control(pDX, IDC_OPERATIONALITEMS, m_IDC_OPERATIONALITEMS);
	DDX_Control(pDX, IDC_AIRFIELDS, m_IDC_AIRFIELDS);
	DDX_Control(pDX, IDC_RBUTTONCOASTAL, m_IDC_RBUTTONCOASTAL);
	DDX_Control(pDX, IDC_RBUTTONBOMBER, m_IDC_RBUTTONBOMBER);
	DDX_Control(pDX, IDC_RBUTTONFIGHTER, m_IDC_RBUTTONFIGHTER);
	DDX_Control(pDX, IDC_BALLOONZONES, m_IDC_BALLOONZONES);
	DDX_Control(pDX, IDC_STRIKE, m_IDC_STRIKE);
	DDX_Control(pDX, IDC_CH, m_IDC_CH);
	DDX_Control(pDX, IDC_CHL, m_IDC_CHL);
	DDX_Control(pDX, IDC_CONVOYS, m_IDC_CONVOYS);
	DDX_Control(pDX, IDC_DAMAGEDITEMS, m_IDC_DAMAGEDITEMS);
	DDX_Control(pDX, IDC_DEFENCES, m_IDC_DEFENCES);
	DDX_Control(pDX, IDC_DESTROYEDITEMS, m_IDC_DESTROYEDITEMS);
	DDX_Control(pDX, IDC_DOCKS, m_IDC_DOCKS);
	DDX_Control(pDX, IDC_FACTORIES, m_IDC_FACTORIES);
	DDX_Control(pDX, IDC_FLAKZONES, m_IDC_FLAKZONES);
	DDX_Control(pDX, IDC_LARGEICONS, m_IDC_LARGEICONS);
	DDX_Control(pDX, IDC_NAVPOINTS, m_IDC_NAVPOINTS);
	DDX_Control(pDX, IDC_RBUTTON_DOCK_CIV, m_IDC_RBUTTON_DOCK_CIV);
	DDX_Control(pDX, IDC_RBUTTON_DOCK_NAVAL, m_IDC_RBUTTON_DOCK_NAVAL);
	DDX_Control(pDX, IDC_RBUTTON_FACTORYBOMBER, m_IDC_RBUTTON_FACTORYBOMBER);
	DDX_Control(pDX, IDC_RBUTTON_FACTORYFIGHTER, m_IDC_RBUTTON_FACTORYFIGHTER);
	DDX_Control(pDX, IDC_RBUTTON_FACTORYOTHER, m_IDC_RBUTTON_FACTORYOTHER);
	DDX_Control(pDX, IDC_RBUTTON_OIL, m_IDC_RBUTTON_OIL);
	DDX_Control(pDX, IDC_RBUTTON_POWER, m_IDC_RBUTTON_POWER);
	DDX_Control(pDX, IDC_RBUTTONCITY, m_IDC_RBUTTONCITY);
	DDX_Control(pDX, IDC_RBUTTONLIGHTHOUSES, m_IDC_RBUTTONLIGHTHOUSES);
	DDX_Control(pDX, IDC_RBUTTONTOWN, m_IDC_RBUTTONTOWN);
	DDX_Control(pDX, IDC_RBUTTONTUNNELS, m_IDC_RBUTTONTUNNELS);
	DDX_Control(pDX, IDC_RBUTTONVILAGES, m_IDC_RBUTTONVILAGES);
	DDX_Control(pDX, IDC_RDF, m_IDC_RDF);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MapFiltersTarget, CDialog)
	//{{AFX_MSG_MAP(MapFiltersTarget)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MapFiltersTarget message handlers

BEGIN_EVENTSINK_MAP(MapFiltersTarget, CDialog)
    //{{AFX_EVENTSINK_MAP(MapFiltersTarget)
	ON_EVENT(MapFiltersTarget, IDC_OPERATIONALITEMS, 1 /* Clicked */, OnClickedOperationalitems, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTONFIGHTER, 1 /* Clicked */, OnClickedRbuttonfighter, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTONBOMBER, 1 /* Clicked */, OnClickedRbuttonbomber, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTONCOASTAL, 1 /* Clicked */, OnClickedRbuttoncoastal, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_AIRFIELDS, 1 /* Clicked */, OnClickedAirfields, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_DAMAGEDITEMS, 1 /* Clicked */, OnClickedDamageditems, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_DESTROYEDITEMS, 1 /* Clicked */, OnClickedDestroyeditems, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_DEFENCES, 1 /* Clicked */, OnClickedDefences, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_FLAKZONES, 1 /* Clicked */, OnClickedFlakzones, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_BALLOONZONES, 1 /* Clicked */, OnClickedBalloonzones, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RDF, 1 /* Clicked */, OnClickedRdf, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_CH, 1 /* Clicked */, OnClickedCh, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_CHL, 1 /* Clicked */, OnClickedChl, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_DOCKS, 1 /* Clicked */, OnClickedDocks, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTON_DOCK_CIV, 1 /* Clicked */, OnClickedRbuttonDockCiv, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTON_DOCK_NAVAL, 1 /* Clicked */, OnClickedRbuttonDockNaval, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_CONVOYS, 1 /* Clicked */, OnClickedConvoys, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_FACTORIES, 1 /* Clicked */, OnClickedFactories, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTON_FACTORYFIGHTER, 1 /* Clicked */, OnClickedRbuttonFactoryfighter, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTON_FACTORYBOMBER, 1 /* Clicked */, OnClickedRbuttonFactorybomber, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTON_FACTORYOTHER, 1 /* Clicked */, OnClickedRbuttonFactoryother, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTON_OIL, 1 /* Clicked */, OnClickedRbuttonOil, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTON_POWER, 1 /* Clicked */, OnClickedRbuttonPower, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_NAVPOINTS, 1 /* Clicked */, OnClickedNavpoints, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTONCITY, 1 /* Clicked */, OnClickedRbuttoncity, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTONTOWN, 1 /* Clicked */, OnClickedRbuttontown, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTONVILAGES, 1 /* Clicked */, OnClickedRbuttonvilages, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTONLIGHTHOUSES, 1 /* Clicked */, OnClickedRbuttonlighthouses, VTS_NONE)
	ON_EVENT(MapFiltersTarget, IDC_RBUTTONTUNNELS, 1 /* Clicked */, OnClickedRbuttontunnels, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void MapFiltersTarget::Refresh(bool redrawmap)
{
	CRButton* b;

	b = GETDLGITEM(IDC_RBUTTONFIGHTER);
	b->SetPressed(Save_Data.mapfilters[FILT_AF_FIGHTER]);

	b = GETDLGITEM(IDC_RBUTTONBOMBER);
	b->SetPressed(Save_Data.mapfilters[FILT_AF_BOMBER]);

	b = GETDLGITEM(IDC_RBUTTONCOASTAL);
	b->SetPressed(Save_Data.mapfilters[FILT_AF_COASTAL]);

	b = GETDLGITEM(IDC_AIRFIELDS);
	if		(		(Save_Data.mapfilters[FILT_AF_FIGHTER])
				&&	(Save_Data.mapfilters[FILT_AF_BOMBER])
				&&	(Save_Data.mapfilters[FILT_AF_COASTAL])
			 )
		b->SetPressed(true);
	else
		b->SetPressed(false);

	b = GETDLGITEM(IDC_DOCKS);
	if		(		(Save_Data.mapfilters[FILT_DOCK_NAVAL])
				&&	(Save_Data.mapfilters[FILT_DOCK_CIV])
			 )
		b->SetPressed(true);
	else
		b->SetPressed(false);



	b = GETDLGITEM(IDC_RBUTTON_DOCK_NAVAL);
	b->SetPressed(Save_Data.mapfilters[FILT_DOCK_NAVAL]);

	b = GETDLGITEM(IDC_RBUTTON_DOCK_CIV);
	b->SetPressed(Save_Data.mapfilters[FILT_DOCK_CIV]);


	b = GETDLGITEM(IDC_DEFENCES);
	if		(		(Save_Data.mapfilters[FILT_BALLOONZONES])
				&&	(Save_Data.mapfilters[FILT_FLAKZONES])
			 )
		b->SetPressed(true);
	else
		b->SetPressed(false);

	b = GETDLGITEM(IDC_BALLOONZONES);
	b->SetPressed(Save_Data.mapfilters[FILT_BALLOONZONES]);

	b = GETDLGITEM(IDC_FLAKZONES);
	b->SetPressed(Save_Data.mapfilters[FILT_FLAKZONES]);


	b = GETDLGITEM(IDC_RDF);
	if		(		(Save_Data.mapfilters[FILT_CH])
				&&	(Save_Data.mapfilters[FILT_CHL])
			 )
		b->SetPressed(true);
	else
		b->SetPressed(false);


	b = GETDLGITEM(IDC_CH);
	b->SetPressed(Save_Data.mapfilters[FILT_CH]);


	b = GETDLGITEM(IDC_CHL);
	b->SetPressed(Save_Data.mapfilters[FILT_CHL]);

	b = GETDLGITEM(IDC_CONVOYS);
	b->SetPressed(Save_Data.mapfilters[FILT_CONVOYS]);

	b = GETDLGITEM(IDC_FACTORIES);
	if		(		(Save_Data.mapfilters[FILT_FACTORYFIGHTER])
				&&	(Save_Data.mapfilters[FILT_FACTORYBOMBER])
				&&	(Save_Data.mapfilters[FILT_FACTORYOTHER])
				&&	(Save_Data.mapfilters[FILT_OIL])
				&&	(Save_Data.mapfilters[FILT_POWER])
			 )
		b->SetPressed(true);
	else
		b->SetPressed(false);

	b = GETDLGITEM(IDC_RBUTTON_FACTORYFIGHTER);
	b->SetPressed(Save_Data.mapfilters[FILT_FACTORYFIGHTER]);

	b = GETDLGITEM(IDC_RBUTTON_FACTORYBOMBER);
	b->SetPressed(Save_Data.mapfilters[FILT_FACTORYBOMBER]);


	b = GETDLGITEM(IDC_RBUTTON_FACTORYOTHER);
	b->SetPressed(Save_Data.mapfilters[FILT_FACTORYOTHER]);


	b = GETDLGITEM(IDC_RBUTTON_OIL);
	b->SetPressed(Save_Data.mapfilters[FILT_OIL]);


	b = GETDLGITEM(IDC_RBUTTON_POWER);
	b->SetPressed(Save_Data.mapfilters[FILT_POWER]);

 	b = GETDLGITEM(IDC_NAVPOINTS);
	if		(		(Save_Data.mapfilters[FILT_CITY])
				&&	(Save_Data.mapfilters[FILT_TOWN])
				&&	(Save_Data.mapfilters[FILT_VILLAGES])
				&&	(Save_Data.mapfilters[FILT_LIGHTHOUSES])
//DeadCode RDH 9Sep00 				&&	(Save_Data.mapfilters[FILT_TUNNELS])
			 )
		b->SetPressed(true);
	else
		b->SetPressed(false);


	b = GETDLGITEM(IDC_RBUTTONCITY);
	b->SetPressed(Save_Data.mapfilters[FILT_CITY]);


	b = GETDLGITEM(IDC_RBUTTONTOWN);
	b->SetPressed(Save_Data.mapfilters[FILT_TOWN]);


	b = GETDLGITEM(IDC_RBUTTONVILAGES);
	b->SetPressed(Save_Data.mapfilters[FILT_VILLAGES]);


	b = GETDLGITEM(IDC_RBUTTONLIGHTHOUSES);
	b->SetPressed(Save_Data.mapfilters[FILT_LIGHTHOUSES]);


//DeadCode RDH 2Aug00 	b = GETDLGITEM(IDC_RBUTTONTUNNELS);
//DeadCode RDH 2Aug00 	b->SetPressed(Save_Data.mapfilters[FILT_TUNNELS]);

	b = GETDLGITEM(IDC_OPERATIONALITEMS);
	b->SetPressed(Save_Data.mapfilters[FILT_OPERATIONALITEMS]);

	b = GETDLGITEM(IDC_DAMAGEDITEMS);
	b->SetPressed(Save_Data.mapfilters[FILT_DAMAGEDITEMS]);

	b = GETDLGITEM(IDC_DESTROYEDITEMS);
	b->SetPressed(Save_Data.mapfilters[FILT_DESTROYEDITEMS]);

	if (redrawmap)
			m_pView->m_mapdlg.Invalidate();


}


BOOL MapFiltersTarget::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Refresh();	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MapFiltersTarget::OnClickedOperationalitems() 
{
	if (Save_Data.mapfilters[FILT_OPERATIONALITEMS])
	{
		if (Save_Data.mapfilters[FILT_DAMAGEDITEMS] || Save_Data.mapfilters[FILT_DESTROYEDITEMS])
			Save_Data.mapfilters%=FILT_OPERATIONALITEMS;
	}
	else
		Save_Data.mapfilters|=FILT_OPERATIONALITEMS;
	Refresh();
}
void MapFiltersTarget::OnClickedDamageditems() 
{
	if (Save_Data.mapfilters[FILT_DAMAGEDITEMS])
	{
		if (Save_Data.mapfilters[FILT_OPERATIONALITEMS] || Save_Data.mapfilters[FILT_DESTROYEDITEMS])
			Save_Data.mapfilters%=FILT_DAMAGEDITEMS;
	}
	else
		Save_Data.mapfilters|=FILT_DAMAGEDITEMS;
	Refresh();
	
}

void MapFiltersTarget::OnClickedDestroyeditems() 
{
	if (Save_Data.mapfilters[FILT_DESTROYEDITEMS])
	{
		if (Save_Data.mapfilters[FILT_OPERATIONALITEMS] || Save_Data.mapfilters[FILT_DAMAGEDITEMS])
			Save_Data.mapfilters%=FILT_DESTROYEDITEMS;
	}
	else
		Save_Data.mapfilters|=FILT_DESTROYEDITEMS;
	Refresh();
	
}



void MapFiltersTarget::OnClickedRbuttonfighter() 
{
	if (Save_Data.mapfilters[FILT_AF_FIGHTER])
		Save_Data.mapfilters%=FILT_AF_FIGHTER;
	else
		Save_Data.mapfilters|=FILT_AF_FIGHTER;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonbomber() 
{
	if (Save_Data.mapfilters[FILT_AF_BOMBER])
		Save_Data.mapfilters%=FILT_AF_BOMBER;
	else
		Save_Data.mapfilters|=FILT_AF_BOMBER;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttoncoastal() 
{
	if (Save_Data.mapfilters[FILT_AF_COASTAL])
		Save_Data.mapfilters%=FILT_AF_COASTAL;
	else
		Save_Data.mapfilters|=FILT_AF_COASTAL;
	Refresh();
	
}

void MapFiltersTarget::OnClose() 
{
	m_pView->m_mapdlg.Invalidate();

	CDialog::OnClose();
}

void MapFiltersTarget::OnOK() 
{
	CDialog::OnOK();
	
	m_pView->m_mapdlg.Invalidate();
	
}

void MapFiltersTarget::OnClickedAirfields() 
{
	if		(		(Save_Data.mapfilters[FILT_AF_FIGHTER])
				&&	(Save_Data.mapfilters[FILT_AF_BOMBER])
				&&	(Save_Data.mapfilters[FILT_AF_COASTAL])
			 )
	{
		Save_Data.mapfilters%=FILT_AF_FIGHTER;
		Save_Data.mapfilters%=FILT_AF_BOMBER;
		Save_Data.mapfilters%=FILT_AF_COASTAL;

	}else
	{
 		Save_Data.mapfilters|=FILT_AF_FIGHTER;
 		Save_Data.mapfilters|=FILT_AF_BOMBER;
 		Save_Data.mapfilters|=FILT_AF_COASTAL;

	}
	Refresh();
}


void MapFiltersTarget::OnClickedDefences() 
{
	if		(		(Save_Data.mapfilters[FILT_BALLOONZONES])
				&&	(Save_Data.mapfilters[FILT_FLAKZONES])
			 )
	{
		Save_Data.mapfilters%=FILT_BALLOONZONES;
		Save_Data.mapfilters%=FILT_FLAKZONES;

	}else
	{
 		Save_Data.mapfilters|=FILT_BALLOONZONES;
 		Save_Data.mapfilters|=FILT_FLAKZONES;

	}
	Refresh();
	
}

void MapFiltersTarget::OnClickedFlakzones() 
{
	if (Save_Data.mapfilters[FILT_FLAKZONES])
		Save_Data.mapfilters%=FILT_FLAKZONES;
	else
		Save_Data.mapfilters|=FILT_FLAKZONES;
	Refresh();
	
}

void MapFiltersTarget::OnClickedBalloonzones() 
{
	if (Save_Data.mapfilters[FILT_BALLOONZONES])
		Save_Data.mapfilters%=FILT_BALLOONZONES;
	else
		Save_Data.mapfilters|=FILT_BALLOONZONES;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRdf() 
{
	if		(		(Save_Data.mapfilters[FILT_CH])
				&&	(Save_Data.mapfilters[FILT_CHL])
			 )
	{
		Save_Data.mapfilters%=FILT_CH;
		Save_Data.mapfilters%=FILT_CHL;

	}else
	{
 		Save_Data.mapfilters|=FILT_CH;
 		Save_Data.mapfilters|=FILT_CHL;

	}
	Refresh();
	
}

void MapFiltersTarget::OnClickedCh() 
{
	if (Save_Data.mapfilters[FILT_CH])
		Save_Data.mapfilters%=FILT_CH;
	else
		Save_Data.mapfilters|=FILT_CH;
	Refresh();
	
}

void MapFiltersTarget::OnClickedChl() 
{
	if (Save_Data.mapfilters[FILT_CHL])
		Save_Data.mapfilters%=FILT_CHL;
	else
		Save_Data.mapfilters|=FILT_CHL;
	Refresh();
	
}

void MapFiltersTarget::OnClickedDocks() 
{
	if		(		(Save_Data.mapfilters[FILT_DOCK_NAVAL])
				&&	(Save_Data.mapfilters[FILT_DOCK_CIV])
			 )
	{
		Save_Data.mapfilters%=FILT_DOCK_NAVAL;
		Save_Data.mapfilters%=FILT_DOCK_CIV;

	}else
	{
 		Save_Data.mapfilters|=FILT_DOCK_NAVAL;
 		Save_Data.mapfilters|=FILT_DOCK_CIV;

	}
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonDockCiv() 
{
	if (Save_Data.mapfilters[FILT_DOCK_CIV])
		Save_Data.mapfilters%=FILT_DOCK_CIV;
	else
		Save_Data.mapfilters|=FILT_DOCK_CIV;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonDockNaval() 
{
	if (Save_Data.mapfilters[FILT_DOCK_NAVAL])
		Save_Data.mapfilters%=FILT_DOCK_NAVAL;
	else
		Save_Data.mapfilters|=FILT_DOCK_NAVAL;
	Refresh();
	
}

void MapFiltersTarget::OnClickedConvoys() 
{
	if (Save_Data.mapfilters[FILT_CONVOYS])
		Save_Data.mapfilters%=FILT_CONVOYS;
	else
		Save_Data.mapfilters|=FILT_CONVOYS;
	Refresh();
	
}

void MapFiltersTarget::OnClickedFactories() 
{
	if		(		(Save_Data.mapfilters[FILT_FACTORYFIGHTER])
				&&	(Save_Data.mapfilters[FILT_FACTORYBOMBER])
				&&	(Save_Data.mapfilters[FILT_FACTORYOTHER])
				&&	(Save_Data.mapfilters[FILT_OIL])
				&&	(Save_Data.mapfilters[FILT_POWER])
			 )
	{
		Save_Data.mapfilters%=FILT_FACTORYFIGHTER;
		Save_Data.mapfilters%=FILT_FACTORYBOMBER;
 		Save_Data.mapfilters%=FILT_FACTORYOTHER;
 		Save_Data.mapfilters%=FILT_OIL;
 		Save_Data.mapfilters%=FILT_POWER;


	}else
	{
 		Save_Data.mapfilters|=FILT_FACTORYFIGHTER;
 		Save_Data.mapfilters|=FILT_FACTORYBOMBER;
 		Save_Data.mapfilters|=FILT_FACTORYOTHER;
 		Save_Data.mapfilters|=FILT_OIL;
 		Save_Data.mapfilters|=FILT_POWER;

	}
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonFactoryfighter() 
{
	if (Save_Data.mapfilters[FILT_FACTORYFIGHTER])
		Save_Data.mapfilters%=FILT_FACTORYFIGHTER;
	else
		Save_Data.mapfilters|=FILT_FACTORYFIGHTER;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonFactorybomber() 
{
	if (Save_Data.mapfilters[FILT_FACTORYBOMBER])
		Save_Data.mapfilters%=FILT_FACTORYBOMBER;
	else
		Save_Data.mapfilters|=FILT_FACTORYBOMBER;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonFactoryother() 
{
	if (Save_Data.mapfilters[FILT_FACTORYOTHER])
		Save_Data.mapfilters%=FILT_FACTORYOTHER;
	else
		Save_Data.mapfilters|=FILT_FACTORYOTHER;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonOil() 
{
	if (Save_Data.mapfilters[FILT_OIL])
		Save_Data.mapfilters%=FILT_OIL;
	else
		Save_Data.mapfilters|=FILT_OIL;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonPower() 
{
	if (Save_Data.mapfilters[FILT_POWER])
		Save_Data.mapfilters%=FILT_POWER;
	else
		Save_Data.mapfilters|=FILT_POWER;
	Refresh();
	
}

void MapFiltersTarget::OnClickedNavpoints() 
{
	if		(		(Save_Data.mapfilters[FILT_CITY])
				&&	(Save_Data.mapfilters[FILT_TOWN])
				&&	(Save_Data.mapfilters[FILT_VILLAGES])
				&&	(Save_Data.mapfilters[FILT_LIGHTHOUSES])
//DeadCode RDH 2Aug00 				&&	(Save_Data.mapfilters[FILT_TUNNELS])
			 )
	{
		Save_Data.mapfilters%=FILT_CITY;
		Save_Data.mapfilters%=FILT_TOWN;
 		Save_Data.mapfilters%=FILT_VILLAGES;
 		Save_Data.mapfilters%=FILT_LIGHTHOUSES;
//DeadCode RDH 2Aug00  		Save_Data.mapfilters%=FILT_TUNNELS;


	}else
	{
 		Save_Data.mapfilters|=FILT_CITY;
 		Save_Data.mapfilters|=FILT_TOWN;
 		Save_Data.mapfilters|=FILT_VILLAGES;
 		Save_Data.mapfilters|=FILT_LIGHTHOUSES;
//DeadCode RDH 2Aug00  		Save_Data.mapfilters|=FILT_TUNNELS;

	}
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttoncity() 
{
	if (Save_Data.mapfilters[FILT_CITY])
		Save_Data.mapfilters%=FILT_CITY;
	else
		Save_Data.mapfilters|=FILT_CITY;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttontown() 
{
	if (Save_Data.mapfilters[FILT_TOWN])
		Save_Data.mapfilters%=FILT_TOWN;
	else
		Save_Data.mapfilters|=FILT_TOWN;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonvilages() 
{
	if (Save_Data.mapfilters[FILT_VILLAGES])
		Save_Data.mapfilters%=FILT_VILLAGES;
	else
		Save_Data.mapfilters|=FILT_VILLAGES;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttonlighthouses() 
{
	if (Save_Data.mapfilters[FILT_LIGHTHOUSES])
		Save_Data.mapfilters%=FILT_LIGHTHOUSES;
	else
		Save_Data.mapfilters|=FILT_LIGHTHOUSES;
	Refresh();
	
}

void MapFiltersTarget::OnClickedRbuttontunnels() 
{
	if (Save_Data.mapfilters[FILT_TUNNELS])
		Save_Data.mapfilters%=FILT_TUNNELS;
	else
		Save_Data.mapfilters|=FILT_TUNNELS;
	Refresh();
	
}
