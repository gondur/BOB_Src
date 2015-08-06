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

// RowanDialog: // Dossierb.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "Dossierb.h"
#include "overlay.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// Dossier dialog


RDialog*	Dossier::Make(UniqueID item)
{

//Remember, if you are RAF and select an airfield we want the airfield dossier...
	FileNum filenum;
	int uidband;

	uidband=Persons2::getbandfromUID(item);

	switch (uidband)
	{
		case	NavalBaseBAND:
		case	DocksBAND:
		case		PortBAND:
		{
			filenum = FIL_D_DOSSIER_DOCKS;
			break;
		}
		case		PowerStationBAND:
		case		OilRefineryBAND:
		case		IndustryBAND:
		case		AircraftFactoryBAND:
		{
			filenum = FIL_D_DOSSIER_FACTORIES;
			break;
		}
		case		CityBAND:
		{
			filenum = FIL_D_DOSSIER_LONDON;
			break;
		}
		case		TownBAND:
		case		NavigationBAND:
		case		VillageBAND:
		{
			filenum = FIL_D_BLANKNOHEADER;
			break;
		}
		case		RAF_FighterAFBAND:
		case		RAF_BomberAFBAND:
		case		RAF_CoastalAFBAND:
		case		LUF_FighterLF2BAND:
		case		LUF_FighterLF3BAND:
		case		LUF_BomberLF2BAND:
		{
			filenum = FIL_D_DOSSIER_AIRFIELD;
			break;
		}
		case		CLRadarBAND:
		case		CHRadarBAND:
		{
			filenum = FIL_D_DOSSIER_RADAR;
			break;
		}
		case		BritBoatBAND:
		case		GermBoatBAND:
		{
			filenum = FIL_D_DOSSIER_CONVOYS;
			break;
		}
		default:
		{
			filenum = FIL_D_BLANKNOHEADER;
			break;
		}


	}
	
	
	
	UniqueID SGT=item;
	info_itemS* i=Persons2::ConvertPtrUID(item);
	if (i->SGT)
		SGT=i->SGT;
	TargetNoDetail* trg = Node_Data[SGT];
	if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
			&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
			&&	(trg) && trg->ReconAdvised()
		)
		return
			MakeTopDialog(::Place(POSN_MAX,POSN_MIN),
					DialList(DialBox(FIL_D_BLANKNOHEADER,new Dossier(SGT),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
							HTabBox(FIL_NULL,IdList(IDS_GENERAL, IDS_DAMAGE),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
								DialBox(filenum,new DossierDetails(SGT))
						)	)	);
	else
		return
			MakeTopDialog(::Place(POSN_MAX,POSN_MIN),
					DialList(DialBox(FIL_D_BLANKNOHEADER,new Dossier(SGT),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
							HTabBox(FIL_NULL,IdList(IDS_GENERAL, IDS_DAMAGE),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
								DialBox(filenum,new DossierDetails(SGT)),
								DialBox(FIL_D_DAMAGE,new CDamage(SGT,item))
						)	)	);
}

//RAF:							Center/Zoom/Photo/Patrol
//LW:	recon  up to date:		Center/Zoom/Photo/Authorise
//			Recon out of date:	Center/Zoom/Recon/Authorise
//RAF aircraft by RAF			Center/Zoom/Fly
//RAF aircraft by LW			Center/Zoom
//LW aircraft by RAF			Center/Zoom/Authorise
//LW aircraft by LW				Center/Zoom/Fly


Dossier::Dossier(UniqueID item, CWnd* pParent /*=NULL*/)
	: RowanDialog(Dossier::IDD, pParent)
{
	//{{AFX_DATA_INIT(Dossier)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	uid = item;
}
bool Dossier::ReconnRequired()
{
	bool reconn = false;
	TargetNoDetail* trg = Node_Data[uid];
	if (trg)
	{
//DeadCode JIM 3Jul00 		int dstatus = trg->knownstatus - trg->truestatus;
//DeadCode JIM 3Jul00 		if (dstatus < 0)
//DeadCode JIM 3Jul00 			dstatus = -dstatus;
		if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW) 
				&&	(!Save_Data.gamedifficulty[GD_LWINTELL])			//JIM 18Aug00
				&&	(trg->ReconAdvised())
			)
			reconn = true;
	}
	return (reconn);
}

void Dossier::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Dossier)
	DDX_Control(pDX, IDJ_TITLE, m_IDJ_TITLE);
	DDX_Control(pDX, IDC_AUTHORISE, m_IDC_AUTHORISE);
	DDX_Control(pDX, IDC_PHOTO, m_IDC_PHOTO);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Dossier, CDialog)
	//{{AFX_MSG_MAP(Dossier)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dossier message handlers




BOOL Dossier::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRButton* title;
	title = GETDLGITEM(IDJ_TITLE);
	title->SetString(GetTargName(uid));

	CRButton*	authbut = GETDLGITEM(IDC_AUTHORISE);
	if (Node_Data.GotBadWeatherPeriod())
		authbut->ShowWindow(SW_HIDE);
	else
	  	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
			authbut->SetString(RESSTRING(AUTHORISE));
		else
		{
			authbut->SetString(RESSTRING(PATROL));
			authbut->SetHintString(RESSTRING(HIDC_PATROL));
		}


	authbut = GETDLGITEM(IDC_PHOTO);
	if (Node_Data.GotBadWeatherPeriod())
		authbut->ShowWindow(SW_HIDE);
	else
		if (Node_Data[uid]==Target::TSS_TargetConvoy || Node_Data[uid]==NULL || Node_Data[uid].truetargtype==Target::TT_GERMAN)
			authbut->ShowWindow(SW_HIDE);
		else
		  	if (ReconnRequired())
			{
				authbut->SetString(RESSTRING(RECONN));
				authbut->SetHintString(RESSTRING(HIDC_RECONN));
			}
			else
				authbut->SetString(RESSTRING(PHOTO));
	if (LUF_FighterLF2BAND==Persons2::GetBandFromUID(uid))
	{
	 	authbut = GETDLGITEM(IDC_AUTHORISE);
		authbut->ShowWindow(SW_HIDE);

		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		{
// we now want to display a button for fighters and/or bombers if there are any
// at this LW AF

			int i=0;
			SLong fighters=-1;
			SLong bombers=-1;

			while (Node_Data.gruppe[i].squadron != SQ_ZERO)
			{
				if (Node_Data.gruppe[i].homeairfield == uid)
				{
					if (Node_Data.gruppe[i].AcType()<PT_LW_BOMBERS)
						fighters=i;
					else
						bombers=i;
				}
				i++;
			}

	// Photo button becomes fighters

			if (fighters!=-1)
			{
		 		authbut = GETDLGITEM(IDC_PHOTO);
				authbut->SetString(RESSTRING(FIGHTERS));
				authbut->SetHintString(Node_Data.gruppe[fighters].ShortName());
				authbut->ShowWindow(SW_SHOW);
			}

	// Authorise button becomes bombers

			if (bombers!=-1)
			{
		 		authbut = GETDLGITEM(IDC_AUTHORISE);
				authbut->SetString(RESSTRING(BOMBERS));
				authbut->SetHintString(Node_Data.gruppe[bombers].ShortName());
				authbut->ShowWindow(SW_SHOW);
			}
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(Dossier, CDialog)
    //{{AFX_EVENTSINK_MAP(Dossier)
	ON_EVENT(Dossier, IDC_CENTRE, 1 /* Clicked */, OnClickedCentre, VTS_NONE)
	ON_EVENT(Dossier, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
	ON_EVENT(Dossier, IDC_PHOTO, 1 /* Clicked */, OnClickedPhoto, VTS_NONE)
	ON_EVENT(Dossier, IDC_ZOOMIN, 1 /* Clicked */, OnClickedZoomin, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void Dossier::OnClickedCentre() 
{
	m_pView->ZoomToUID(UniqueID(uid),m_pView->m_zoom);

	
}

void Dossier::OnClickedAuthorise() 
{
#ifndef	BOB_DEMO_VER

  	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (LUF_FighterLF2BAND==Persons2::GetBandFromUID(uid))
		{
// launch bombers dialog

			int i=0;
			while (Node_Data.gruppe[i].squadron != SQ_ZERO)
			{
				if (Node_Data.gruppe[i].homeairfield == uid)
				{
					if (Node_Data.gruppe[i].AcType()>=PT_LW_BOMBERS)
					{
						MainToolBar().OpenACDossier(Node_Data.gruppe[i].wadernum,
							Node_Data.gruppe[i].gruppennum);

						break;
					}
				}
				i++;
			}
		}
		else
		{
			int packnum=Todays_Packages_NewPackage(uid,MMC.directives.lw.userprofiles[Directives::LW::ATTACK]);
			if (packnum < 0)
				RDialog::RMessageBox(IDS_WARNING, IDS_NOAIRCRAFTAVAIL,NULL,NULL,IDS_CONTINUE);
			else
			{
	//DeadCode JIM 16Oct00 			Todays_Packages[packnum].CalcRoutePositionsAndTime();
				MainToolBar().OnClickedMissionfolder();
				Todays_Packages.InvalidateRoute(&Todays_Packages[packnum],true,true);
			}
		}
	}else
	{
			
		int	packnum=Todays_Packages_NewPackage(uid,
							MMC.directives.raf.userprofiles[Directives::RAF::PATROL]);					
		if (packnum < 0)
			RDialog::RMessageBox(IDS_WARNING, IDS_NOAIRCRAFTAVAIL,NULL,NULL,IDS_CONTINUE);
		else
		{
			Todays_Packages[packnum].CalcRoutePositionsAndTime();		//JIM 16Oct00
			MainToolBar().OnClickedMissionfolder();
			Todays_Packages.InvalidateRoute(&Todays_Packages[packnum],true,true);
		}

	}
#endif
}

void Dossier::OnClickedPhoto() 
{
#ifndef	BOB_DEMO_VER

	if (LUF_FighterLF2BAND==Persons2::GetBandFromUID(uid) && RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
// launch fighters dialog

		int i=0;
		while (Node_Data.gruppe[i].squadron != SQ_ZERO)
		{
			if (Node_Data.gruppe[i].homeairfield == uid)
			{
				if (Node_Data.gruppe[i].AcType()<PT_LW_BOMBERS)
				{
					MainToolBar().OpenACDossier(Node_Data.gruppe[i].wadernum,
						Node_Data.gruppe[i].gruppennum);

					break;
				}
			}
			i++;
		}
	}
	else	
	{
 		if (ReconnRequired())
		{
			int packnum=Todays_Packages_NewPackage(uid,MMC.directives.lw.userprofiles[Directives::LW::RECON]);
			if (packnum < 0)
				RDialog::RMessageBox(IDS_WARNING, IDS_NOAIRCRAFTAVAIL,NULL,NULL,IDS_CONTINUE);
			else
			{
				Todays_Packages[packnum].CalcRoutePositionsAndTime();
				MainToolBar().OnClickedMissionfolder();
				Todays_Packages.InvalidateRoute(&Todays_Packages[packnum],true,true);

			}
		}else
		{
	#ifndef NDEBUG
	#define PLACEMENT	CRect(0,0,512,384)
	#else
	#define	PLACEMENT	Place(POSN_CENTRE,POSN_CENTRE, 0, 0)
	#endif
	//	#define PLACEMENT	CRect(0,0,512,384)
			UniqueID targID=UniqueID(uid);
			CString tname=GetTargName(targID);
			OverLay.SetTargName((char*)LPCTSTR(tname));
			OverLay.loader_art=FIL_LOADING;									//RJS 16Aug00
			LogChild(0,MakeTopDialog(PLACEMENT,DialBox(OverLay.loader_art,new Rtestsh1(UniqueID(uid)),EDGES_NOSCROLLBARS)));
			Rtestsh1::Start3d(Rtestsh1::S3D_DONEBACK);
		}
	}
#endif
}

void Dossier::OnClickedZoomin() 
{
	m_pView->ZoomToUID(UniqueID(uid),m_pView->m_zoom*2);
	
}
