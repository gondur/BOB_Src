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

// RowanDialog: // MainTbar.cpp : implementation file
//

#include "stdafx.h"
#include "MainTbar.h"
#include "MIGView.h"
#include "MainFrm.h"
#include	"persons2.h"
#include "nodebob.h"
#include "radio.g"
#include "bstream.h"
#include "mymath.h"
#include "mytime.h"
#include "rchatter.h"

typedef	Profile::AttackMethod	AttackMethod;
MAKEFIELD (AttackMethod, Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);
#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
int   CMainToolbar::LWReview[LWENDDAYREVIEW]=
{	SCRIPT_LUFMSC1,SCRIPT_LUFMSC2,SCRIPT_LUFMSC3
}; 
int   CMainToolbar::RAFReview[RAFENDDAYREVIEW]=
{
	SCRIPT_RAFHEADON,SCRIPT_ROYAL,SCRIPT_CANNON,SCRIPT_RAFMSC1,SCRIPT_RAFMSC2,
	SCRIPT_RAFMSC3,SCRIPT_RAFMSC4
};/////////////////////////////////////////////////////////////////////////////
// CMainToolbar dialog


CMainToolbar::CMainToolbar(CWnd* pParent /*=NULL*/)
	: CRToolBar(pParent)
{
	//{{AFX_DATA_INIT(CMainToolbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMainToolbar::DoDataExchange(CDataExchange* pDX)
{
	CRToolBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMainToolbar)
		// NOTE: the ClassWizard will add DDX and DDV calls here
//DEADCODE DAW 23/11/99 			DDX_Control(pDX,IDC_FRAG2,m_IDC_FRAG2);

	//}}AFX_DATA_MAP
	for (int id=0;id<MAX_ID;id++)
		if (dialids[id])
		{
			DDX_Control(pDX,	dialids[id],	m_dialids[id]);		
		}

}


BEGIN_MESSAGE_MAP(CMainToolbar, CRToolBar)
	//{{AFX_MSG_MAP(CMainToolbar)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainToolbar message handlers

BEGIN_EVENTSINK_MAP(CMainToolbar, CRToolBar)
    //{{AFX_EVENTSINK_MAP(CMainToolbar)
//DEADCODE DAW 23/11/99 	ON_EVENT(CMainToolbar, IDC_CHANGE_TO_TITLE, 1 /* Clicked */, OnClickedChangeToTitle, VTS_NONE)
//DEADCODE JIM 16/12/99 	ON_EVENT(CMainToolbar, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_BASES, 1 /* Clicked */, OnClickedBases, VTS_NONE)
//DEADCODE DAW 23/11/99 	ON_EVENT(CMainToolbar, IDC_DIRECTIVES, 1 /* Clicked */, OnClickedDirectives, VTS_NONE)
//DEADCODE JIM 30/11/99 	ON_EVENT(CMainToolbar, IDC_MISSIONRESULTS, 1 /* Clicked */, OnClickedMissionresults, VTS_NONE)
//DEADCODE RDH 06/01/00 	ON_EVENT(CMainToolbar, IDC_OVERVIEW, 1 /* Clicked */, OnClickedOverview, VTS_NONE)
//DEADCODE RDH 06/01/00 	ON_EVENT(CMainToolbar, IDC_PLAYERLOG, 1 /* Clicked */, OnClickedPlayerlog, VTS_NONE)
//DEADCODE RDH 11/11/99 	ON_EVENT(CMainToolbar, IDC_SQUADS, 1 /* Clicked */, OnClickedSquads, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_WEATHER, 1 /* Clicked */, OnClickedWeather, VTS_NONE)
//DEADCODE JIM 30/11/99 	ON_EVENT(CMainToolbar, IDC_DIS, 1 /* Clicked */, OnClickedDis, VTS_NONE)
//DEADCODE DAW 23/11/99 	ON_EVENT(CMainToolbar, IDC_MISSION_FOLDER, 1 /* Clicked */, OnClickedMissionFolder, VTS_NONE)
//DEADCODE DAW 23/11/99 	ON_EVENT(CMainToolbar, IDC_AUTHORISE11, 1 /* Clicked */, OnClickedAuthorise11, VTS_NONE)
//DEADCODE DAW 23/11/99 	ON_EVENT(CMainToolbar, IDC_FRAG2, 1 /* Clicked */, OnClickedFrag2, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_AIRCRAFTALLOC, 1 /* Clicked */, OnClickedAircraftalloc, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_SQUARONLIST, 1 /* Clicked */, OnClickedSquaronlist, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_REVIEW, 1 /* Clicked */, OnClickedReview, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_PILOTDATA, 1 /* Clicked */, OnClickedPilotdata, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_ASSETLIST, 1 /* Clicked */, OnClickedAssetlist, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_MISSIONFOLDER, 1 /* Clicked */, OnClickedMissionfolder, VTS_NONE)
	ON_EVENT(CMainToolbar, IDC_HOSTILESLIST, 1 /* Clicked */, OnClickedHostileslist, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
int CMainToolbar::dialids[]={
		IDC_AIRCRAFTALLOC,IDC_BASES,IDC_SQUARONLIST,IDC_WEATHER,IDC_REVIEW,
		IDC_PILOTDATA,IDC_ASSETLIST,IDC_MISSIONFOLDER,IDC_HOSTILESLIST, //RDH 03/04/99
		NULL/*DOSSIER*/,NULL/*AcDossier*/,NULL/*INTERCEPTOFFERED*/,NULL/*TAKEOVEROFFERED*/,
		NULL/*ROUTE*/, NULL/*WAYPOINT*/, NULL/*TOTE*/};




void CMainToolbar::OnClickedBases() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	CloseAllDialogsBut(BASES);

	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (!LoggedChild(BASES))
			LogChild(BASES,LuftFlotte::Make()
							);
		else
			CloseLoggedChild(BASES);
	}else
	{
		if (!LoggedChild(BASES))
			LogChild(BASES,BasesLuftflotte::Make()
							);
		else
			CloseLoggedChild(BASES);
	}
}


void CMainToolbar::OpenDirectives() 
{
}



void CMainToolbar::DialoguesVisible( bool vis)
{
		MakeChildrenVisible(vis);

}

void CMainToolbar::OnClickedPlayerlog() 
{

}

void CMainToolbar::OnClickedWeather() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	int f;
	f = FIL_D_WEATHER;
//DEADCODE RDH 09/11/99 	if (MMC.Sky.MaxMagnitude > 0)
//DEADCODE RDH 09/11/99 		f++;
	if (!LoggedChild(WEATHER))
		LogChild(WEATHER,
			RDialog::MakeTopDialog(Place(POSN_CENTRE,POSN_CENTRE),
										DialBox((FileNum)f/*IDB_GENERALS*/,new CWeather)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
				)					);	
	else
		CloseLoggedChild(WEATHER);
}

void CMainToolbar::ChildDialClosed(int dialnum,RDialog*,int rv)
{	if (dialids[dialnum])
		GETDLGITEM(dialids[dialnum])->SetPressed(FALSE);
}
#define	IsScriptRepeated(name)	IsScriptRepeated(ReviewBuffer::UnrepeatableScripts:: name)
#define	SetScriptRepeated(name)	SetScriptRepeated(ReviewBuffer::UnrepeatableScripts:: name)
void CMainToolbar::AnythingImportantToReview()
{
	Node_Data.FillRAFStrengthInfo(false);


   	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if 	(MMC.phasechanged)
		{
			MMC.phasechanged = 0;
			if 	(MMC.lwdir ==  Directives::LW::HistTypes::LWHISTORICALPHASE2A)
			//FIL_VID_LWPHASE2BEGINS
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LWPHASE2BEGINS);
			if 	(MMC.lwdir ==  Directives::LW::HistTypes::LWHISTORICALPHASE3A)
			//FIL_VID_LWPHASE3BEGINS
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LWPHASE3BEGINS);
			if 	(MMC.lwdir ==  Directives::LW::HistTypes::LWHISTORICALPHASE4A)
			//FIL_VID_LWPHASE4BEGINS
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LWPHASE4BEGINS);
		}
		if (MMC.currdate == SEP2nd1940)
		//If Operation Sea-lion in 2 weeks
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_SEALION);
		if (MMC.currdate == SEP7th1940)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_SEALIONPOSTPONED);

		
		//Notification of highest day record broken - losses / kills
		if (		(MMC.thisweekreview.raftodaylosses > MMC.thisweekreview.rafrecordlosses)
				&&	(MMC.thisweekreview.raftodaylosses >= 10)
		   )
		{
			MMC.thisweekreview.rafrecordlosses = MMC.thisweekreview.raftodaylosses;
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LWRECORDKILLS, UID_Null, UID_Null, TargetIndexes (SQ_ZERO,MMC.thisweekreview.rafrecordlosses) );
		}
		if (		(MMC.thisweekreview.lwtodaylosses > MMC.thisweekreview.lwrecordlosses)
				&&	(MMC.thisweekreview.lwtodaylosses >= 10)
		   )
		{
			MMC.thisweekreview.lwrecordlosses = MMC.thisweekreview.lwtodaylosses;
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RECORDLOSSES,  UID_Null, UID_Null, TargetIndexes (SQ_ZERO,MMC.thisweekreview.lwrecordlosses) );
		}


		//Enemy Tactic Change:
		
		//If big wing used for first time:
		if (		(Todays_Packages.BiggestRAFSquadronOnDay() >= 3)
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_BIGWINGUSED))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_BIGWINGUSED);

		int RAFsqCatAB =	Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catA +
							Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catB;


		//If Operation Sea-lion in 11 days and Invasion conditions not being fullfilled
		if  (		(MMC.currdate >= SEP4th1940)
				&&	(RAFsqCatAB > 12)
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_BIGWINGUSED))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_SEALIONDOUBTS);
 
		//If Operation Sea-lion in 1 week and Invasion conditions being fullfilled.
		if  (		(MMC.currdate >= SEP4th1940)
				&&	(RAFsqCatAB <6)
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_SEALIONONCOURSE))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_SEALIONONCOURSE);


		//If PAC is fired and german ac brought down (only display this once per game)
		if	(		(MMC.pacsuccessful)
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_LUFPAC))
			)
		Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LUFPAC);

		//If estimated number of fighters < 100 
		if (Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].acready < 100)		
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RAFDECIMATED);

		if (		(MMC.currdate >= AUG12th1940)
				&&	(Todays_Packages.TargetDamaged(CLRadarBAND, LUF_FighterLF2BAND))
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_RAFRADIONET))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RAFRADIONET);

		if (		(MMC.currdate >= AUG12th1940)
				&&	(Todays_Packages.TargetDestroyed(CLRadarBAND, LUF_FighterLF2BAND))
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_RAFRADIONETSUCCESS))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RAFRADIONETSUCCESS);


	}else
	{	//Player is RAF
		if 	(MMC.phasechanged > 1)		//also check weather
		{
 			MMC.phasechanged = 0;

			if 	(MMC.lwdir ==  Directives::LW::HistTypes::LWHISTORICALPHASE2A)
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_PHASE2BEGINS);
			if 	(MMC.lwdir ==  Directives::LW::HistTypes::LWHISTORICALPHASE3A)
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_PHASE3BEGINS);
			if 	(MMC.lwdir ==  Directives::LW::HistTypes::LWHISTORICALPHASE4A)
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_PHASE4BEGINS);
		}

		if (MMC.currdate == SEP10th1940)
		//Worried about invasion - barges building up
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_BARGESBUILDUP);

		//If demand outstripping production for Spits:
		if (MMC.thisweekreview.dayssincedeltapos[0] >= 7)
		{
			MMC.thisweekreview.dayssincedeltapos[0] = 0;
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_SPITFIRESHORTAGEPREDICTED);
		}

		//If demand outstripping production for Hurricanes:
		if (MMC.thisweekreview.dayssincedeltapos[1] >= 7)
		{
			MMC.thisweekreview.dayssincedeltapos[1] = 0;
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_HURICANESHORTAGEPREDICTED);
		}

		if ((MMC.newpilotskill < SKILL_POOR)	&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_PILOTSHORTAGE)))
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_PILOTSHORTAGE);

		if	(Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catA == 0)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_FIGHTERCOMMANDEXHAUSTED);

		int totalsq =	Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catA +
						Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catB +
						Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catC; 
		int halfsq = totalsq/2;
		if	(Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catA < halfsq)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_FIGHTERCOMMANDNEARLYEXHAUSTED);
		if	(Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catC > halfsq)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_FIGHTERCOMMANDUNFIT);


//		MMC.historictargetuiddamaged = (UniqueID)0x28ff;

		//if  item and in BritHistoricBAND is damaged then
		if (MMC.historictargetuiddamaged)
		{
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_MONUMENTSURVIVES, MMC.historictargetuiddamaged, MMC.historictargetuiddamaged);
			MMC.historictargetuiddamaged = UID_NULL;
		}

		//if  item and in BritHistoricBAND is destroyed then
		if (MMC.historictargetuiddestroyed)
		{
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_MONUMENTDESTROYED, MMC.historictargetuiddestroyed, MMC.historictargetuiddestroyed);
			MMC.historictargetuiddestroyed = UID_NULL;
		}

		//if RAF bomb Berlin for first time
		if (		(Node_Data.review.IsScriptRepeated(SCRIPT_LUFTWAFFEBOMBLONDON))
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_RAFBOMBBERLIN))
		   )
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RAFBOMBBERLIN);

		//if LuftWaffe bomb London for first time
		if (		(Todays_Packages.LondonTargetted())
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_LUFTWAFFEBOMBLONDON))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LUFTWAFFEBOMBLONDON);


//Notification of highest day record broken - kills
		//Notification of highest day record broken - losses / kills
		if (		(MMC.thisweekreview.lwtodaylosses > MMC.thisweekreview.lwrecordlosses)
				&&	(MMC.thisweekreview.lwtodaylosses >= 10)
			)
		{
			MMC.thisweekreview.lwrecordlosses = MMC.thisweekreview.lwtodaylosses;
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RAFRECORDKILLS, UID_Null, UID_Null, TargetIndexes (SQ_ZERO,MMC.thisweekreview.lwrecordlosses) );
		}

		int escortratio2;
		//first time we get over 1000 lw a/c (ie total ac): review lw packages
		if (		(Todays_Packages.ThousandAcRaid(escortratio2))
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_THOUSANDBOMBER))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_THOUSANDBOMBER);

		//If Germans start using close escort
		//	Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_CLOSEESCORTTACTIC);

		//If Germans change fighter to bomber ratio to >2 to 1
		if (		(escortratio2)
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_BIGESCORT))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_BIGESCORT);

		//Close to Sack
		if (	(MMC.undefendedconvoylosses > 4)
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_CRITICALSHIPPINGLOSS))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_CRITICALSHIPPINGLOSS);
		if (	(MMC.undefendedconvoylosses > 6)
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_CRITICALSHIPPINGLOSS2))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_CRITICALSHIPPINGLOSS);

		//If too many economic targets being hit
		if (		(MMC.undefendedcriticaltargetlosses > 20)			//JIM 15Nov00
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_CRITICALTARGETS))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_CRITICALTARGETS);


//If Key Assembly Factory knocked out:
//	If dispersed sites take over 

//	Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_ACFACTORYOUTGOOD);

//If dispersed sites not ready
//	Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_ACFACTORYOUTBAD);

		//If PAC is fired and german ac brought down (only display this once per game)
		if	(		(MMC.pacsuccessful)
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_LUFPAC))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RAFPAC);

		//If radar site knocked out for first time and mobiles used
		if (		(Todays_Packages.TargetDamaged(CLRadarBAND, LUF_FighterLF2BAND))
				&&	(!Node_Data.review.SetScriptRepeated(SCRIPT_RDFHOLES))
			)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RDFHOLES);


  }

	//If  British command reduces shipping through channel Date, Aug 16th is day of penultimate convoy
	if (MMC.currdate == AUG16th1940)
		Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_REDIRECTCONVOYS);
}
void CMainToolbar::FindSomethingToReview()
{
//If today is a boring day and we want something to say
	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (		(MMC.thisweekreview.raftodaylosses > MMC.thisweekreview.lwtodaylosses)
				&&	(MMC.thisweekreview.raftodaylosses >= 10)
			)
		{
			if (MMC.thisweekreview.raftodaylosses  > 20)
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
					AS_NOTSWITCH,SCRIPT_KILLS2, UID_NULL, UID_NULL, TargetIndexes(SQ_ZERO, (int)MMC.thisweekreview.raftodaylosses) );
			else
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
					AS_NOTSWITCH,SCRIPT_KILLS, UID_NULL, UID_NULL, TargetIndexes(SQ_ZERO, (int)MMC.thisweekreview.raftodaylosses) );
		}else if (MMC.thisweekreview.lwtodaylosses > 0)
		{
			if (MMC.thisweekreview.lwtodaylosses  > 40)
 				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
					AS_NOTSWITCH,SCRIPT_LOSSES2, UID_NULL, UID_NULL, TargetIndexes(SQ_ZERO, (int)MMC.thisweekreview.lwtodaylosses));
			else
 				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
					AS_NOTSWITCH,SCRIPT_LOSSES, UID_NULL, UID_NULL, TargetIndexes(SQ_ZERO, (int)MMC.thisweekreview.lwtodaylosses));

		}else
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
				AS_NOTSWITCH,SCRIPT_KILLSQUIET);


		//then random also do a general  msg
		int   index = Math_Lib.rnd(200);								//RDH 12Oct00
		if (index < LWENDDAYREVIEW && LWReview[index])
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
				AS_NOTSWITCH,ScriptTables(LWReview[index]));
	}else
	{

		if (MMC.thisweekreview.raftodaylosses < MMC.thisweekreview.lwtodaylosses)
		{
			if (MMC.thisweekreview.lwtodaylosses > 20)
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
					AS_NOTSWITCH,SCRIPT_KILLS2, UID_NULL, UID_NULL, TargetIndexes(SQ_ZERO, (int)MMC.thisweekreview.lwtodaylosses) );
			else
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
					AS_NOTSWITCH,SCRIPT_KILLS, UID_NULL, UID_NULL, TargetIndexes(SQ_ZERO, (int)MMC.thisweekreview.lwtodaylosses) );
		}else if (MMC.thisweekreview.raftodaylosses > 0)
		{
 			if (MMC.thisweekreview.raftodaylosses  > 20)
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
					AS_NOTSWITCH,SCRIPT_LOSSES2, UID_NULL, UID_NULL, TargetIndexes(SQ_ZERO, (int)MMC.thisweekreview.raftodaylosses));
			else
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
					AS_NOTSWITCH,SCRIPT_LOSSES, UID_NULL, UID_NULL, TargetIndexes(SQ_ZERO, (int)MMC.thisweekreview.raftodaylosses));

		}
		else
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
				AS_NOTSWITCH,SCRIPT_KILLSQUIET);
		//then random also do a general  msg
		int   index = Math_Lib.rnd(100);								//RDH 12Oct00
		if (index < RAFENDDAYREVIEW && RAFReview[index])
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,
				AS_NOTSWITCH,ScriptTables(RAFReview[index]));
	}

	
}
bool CMainToolbar::EndofWar()
{
	int latest  = Node_Data.review.latest;
//DeadCode JIM 20Oct00 	int viewed = Node_Data.review.B[IntelBuffer::Bviewedupto];


	Node_Data.FillRAFStrengthInfo(false);
 	int RAFsqCatAB =	Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catA +
							Node_Data.RAFstrengthinfo[Node_Data.RAFTOTAL].catB;


   	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (MMC.currdate == SEP16th1940)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_SEALIONCANCELLED);

		if (MMC.currdate < SEP7th1940)
		{
			if (RAFsqCatAB < 15)		//Were all 4					//JIM 24Oct00
			 	Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LUFWIN2);
		}
		else
		{
			if (RAFsqCatAB < 8)											//JIM 24Oct00
			 	Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LUFWIN1);
		}
	}else
	{
		if (MMC.undefendedconvoylosses > 8)						//RJS 16Nov00
		{
			if (MMC.currdate < AUG15th1940)						//RJS 16Nov00
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_SHIPPINGLOSS_SACK);
			else
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_CRITTARGSACK);//RJS 16Nov00
		}

		if (MMC.currdate == SEP16th1940)
			Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_RAFWIN);

		if (MMC.currdate < SEP7th1940)
		{
			if (RAFsqCatAB < 10)										//JIM 24Oct00
		 		Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LUFWIN3);
		}
		else
		{
			if (RAFsqCatAB < 6)											//JIM 24Oct00
				Node_Data.review.AddMessage(IntelMsg::MED_ANNOUNCEMENT_EXTERNAL,AS_NOTSWITCH,SCRIPT_LUFWIN4);
		}
	}
	if 	 (latest == Node_Data.review.latest)
		return (false);
	else
	{
		Node_Data.review.B[IntelBuffer::Bviewedupto] = latest;
		return(true);
	}

}
#undef	IsScriptRepeated	//(name)	IsScriptRepeated(ReviewBuffer::name)
#undef	SetScriptRepeated	//(name)	IsScriptRepeated(ReviewBuffer::name)

void CMainToolbar::EndDayReview()
{
		AnythingImportantToReview();
		if 	 (Node_Data.review.latest == Node_Data.review.B[IntelBuffer::Bviewedupto])
		{
			FindSomethingToReview();
		}
}
void CMainToolbar::EndDayRouting()
{
	Persons4::ShutDownMapWorld();

	if (EndofWar())
		RDialog::m_pView->LaunchFullPane(&RFullPanelDial::endwarreview,SaveData::UIR_FRAG);	//AMM 27Nov98
	else
	{
		RDialog::m_pView->LaunchFullPane(&RFullPanelDial::enddayreview,SaveData::UIR_FRAG);	//AMM 27Nov98
	}
}
void CMainToolbar::OnClickedFrag2() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	if	(false)//!Todays_Packages.FlyableAircraftAvailable())
	{
		int rv;
//DEADCODE DAW 23/11/99 		if (!Todays_Packages.pack[0][0][0].uid)
//DEADCODE RDH 09/05/00 			rv = RDialog::RMessageBox(IDS_NOMISSIONS, IDS_SETMISSIONS,NULL,IDS_NEXT_PERIOD,IDS_CONTINUE);
//DEADCODE DAW 23/11/99 		else														  //RDH 14/06/99
//DEADCODE DAW 23/11/99 			rv = RDialog::RMessageBox(IDS_MISSIONINVALID, IDS_NOTCLEARED,NULL,IDS_NEXT_PERIOD,IDS_CONTINUE); //RDH 14/06/99
		rv = 1;															//RDH 09/05/00
		if (rv < 2)	
		{
			
			CMainFrame* main=(CMainFrame*)AfxGetMainWnd();

			main->CloseToolChildren();
//DeadCode JIM 18Oct00 			main->m_toolbar1.CloseLoggedChildren();
//DeadCode JIM 18Oct00 			main->m_toolbar2.CloseLoggedChildren();
//DeadCode JIM 18Oct00 			main->m_toolbar3.CloseLoggedChildren();
//DeadCode JIM 18Oct00 			main->m_toolbar4.CloseLoggedChildren();
//DEADCODE RDH 08/11/99 			main->m_toolbar5.CloseLoggedChildren();

//DEADCODE DAW 29/01/00 			MMC.UpdateAllDis();											  //RDH 19/06/99
//DEADCODE DAW 29/01/00 		  	MMC.ZeroDisDay();
			MMC.msgwithsmacker = 0;										  //RDH 26/06/99
			MMC.smacker = FIL_NULL;


			MMC.NextMission();
//DEADCODE JIM 16/11/99 			SupplyTree::ProcessAirFields();
//DeadCode JIM 18Oct00 			CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();
//DEADCODE RDH 08/11/99 			pmainwnd->m_toolbar5.OnClickedNextPeriod(); 
 		}
	}
	else
	{
// need to find best place for this
//		_Replay.SaveTempSaveGame("dreplay.dat");

		Todays_Packages.HandleLaterEvents();

		Todays_Packages.SaveBin();
//DeadCode JIM 20Oct00 		RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
		FullScreen* fs;
//DeadCode AMM 21Aug00 		fullscreen->SetDefaultPilotPositions();

		if (Save_Data.minsbetweensavegame)
			CFiling::SaveTimedGame();

		if (Todays_Packages.localplayer==NAT_RAF)
			CFiling::SaveGame("Auto Save.BSR");
		else
			CFiling::SaveGame("Auto Save.BSL");

		//save out the individual packages: (can only be 128)
		{
			char buffer[fileman::pathnamesize];
			BOStream bos(File_Man.namenumberedfile(
				File_Man.fakefile(FIL_SAVEGAMEDIR,"Package.dat"),buffer));
			if (bos.is_open())
				Todays_Packages.SaveGame(bos);
		}
		//manage stores_destroyed									  //RDH 25/05/99
//DEADCODE JIM 16/11/99 		SupplyTree::ProcessStoresDestroyed ();

	//DeadCode AMM 27Nov98 	RDialog::m_pView->LaunchFullPane(&RFullPanelDial::singlefrag);	
//	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
//DeadCode AMM 21Aug00 	RFullPanelDial::SetDefaultPilotPositions();
//DeadCode AMM 27Nov98 	RDialog::m_pView->LaunchFullPane(&RFullPanelDial::singlefrag);	

		if (_DPlay.PlayerCreated && _DPlay.Host)
		{
//DeadCode PD 23May99 			_DPlay.SendSaveGame();
			_DPlay.SendSaveGame(false,false);
		}

		if (!RFullPanelDial::incomms)								//AMM 27Nov98
		{
			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::bobfrag,SaveData::UIR_FRAG);	//AMM 27Nov98
		}
		else														//AMM 27Nov98
		{
//DEADCODE rdh 23/04/99 			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::commsfrag);	//AMM 27Nov98
			if	(_DPlay.Side)
					if (_DPlay.UIPlayerType == DPlay::PLAYER_HOST)
						RDialog::m_pView->LaunchFullPane(&RFullPanelDial::readyroomhostcampaign,SaveData::UIR_FRAG);	
					else
						RDialog::m_pView->LaunchFullPane(&RFullPanelDial::readyroomguestcampaign,SaveData::UIR_FRAG);	

			else
				RDialog::m_pView->LaunchFullPane(&RFullPanelDial::readyroomguestcampaignred,SaveData::UIR_FRAG);
		}
	}
}

void CMainToolbar::OpenACDossier(int item, int gruppe) 
{
//DEADCODE  09/02/00 	if (Todays_Packages[Todays_Packages.hipack].attackmethod >= Profile::AM_LWPACKS) 
//DeadCode AM 10Oct00    	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	if (item<Squadron::WN_LAST)
	{	//LW:	item is wadernum(0-3 or 1-4). Gruppe is gruppennum

		if (LoggedChild(ACDOSSIER))
			CloseLoggedChild(ACDOSSIER);

		LogChild(ACDOSSIER,AirfieldDossier::Make(item, gruppe));
		CRTabs* tab=(CRTabs*)LoggedChild(ACDOSSIER)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
		tab->SelectTab(gruppe);
	}else
	{	//RAF:	item is UID, Gruppe is either tab number or squad number
		if (LoggedChild(ACDOSSIER))
			CloseLoggedChild(ACDOSSIER);

		LogChild(ACDOSSIER,AirfieldDossier::Make(item, gruppe));
		CRTabs* tab=(CRTabs*)LoggedChild(ACDOSSIER)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
		if (tab && gruppe > 1)
 			tab->SelectTab(gruppe);
	}

}
void CMainToolbar::OpenInterceptOffered(int pack,int raid) 
{

	if (!LoggedChild(INTERCEPTOFFERED))
	{
		LogChild(INTERCEPTOFFERED,InterceptOffered::Make(pack,raid));
	}
	else
		//dialog open so just set up intercept
		LoggedChild(INTERCEPTOFFERED)->fchild->RefreshData((pack<<16)+raid);

//DeadCode JIM 18Aug00 		RAFDirectivesResults::InterceptSanctioned(pack,0);

//	else
//		CloseLoggedChild(INTERCEPTOFFERED);


}
void IntelBuffer::OpenTakeOffOffered(int packf, int sqf, int latest) 
{

	if (!MainToolBar().LoggedChild(CMainToolbar::TAKEOVEROFFERED))
	{
		MainToolBar().LogChild(CMainToolbar::TAKEOVEROFFERED,TakeOverOffered::Make(packf,sqf, latest));
	}


}
void CMainToolbar::OpenRoute() 
{
	if (LoggedChild(DOSSIER))
			CloseLoggedChild(DOSSIER);

	if (LoggedChild(MISSIONFOLDER))
		CloseLoggedChild(MISSIONFOLDER);

	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (LoggedChild(ROUTE))
			CloseLoggedChild(ROUTE);
		LogChild(ROUTE,LWRouteTop::Make());
		CRTabs* tab=(CRTabs*)LoggedChild(ROUTE)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
		tab->SelectTab(1);

	}else
	{
		if (LoggedChild(ROUTE))
			CloseLoggedChild(ROUTE);
		LogChild(ROUTE,RAFRouteTop::Make());
		CRTabs* tab=(CRTabs*)LoggedChild(ROUTE)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
		tab->SelectTab(1);
	}

}

void CMainToolbar::OpenWP() 
{
	if (LoggedChild(DOSSIER))
			CloseLoggedChild(DOSSIER);

	if (LoggedChild(WAYPOINT))
		CloseLoggedChild(WAYPOINT);
	LogChild(WAYPOINT,WayPointDialog::Make());
		

}

void CMainToolbar::OpenDiary(int squad) 
{
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (!LoggedChild(DIARY))
			LogChild(DIARY,LWDiary::Make((SquadNum) squad)
							);
		else
			CloseLoggedChild(DIARY);
	}else
	{
		if (!LoggedChild(DIARY))
			LogChild(DIARY,RAFDiary::Make((SquadNum) squad)
							);
		else
			CloseLoggedChild(DIARY);
	}

}
void CMainToolbar::OpenDossier(UniqueID item) 
{
	if (item&(UID_BIT15+UID_BIT14))										//CSB 12Jul00
		return;															//CSB 12Jul00
	int uidband;
	ItemPtr p=Persons2::ConvertPtrUID(item);
	UniqueID SGT=item;
	if (p && p->SGT)
		SGT=p->SGT;
	uidband=Persons2::getbandfromUID(SGT);
	if (uidband==SagBAND)
		return;															//CSB 12Jul00
	if (	(uidband == RAF_FighterAFBAND)
#ifdef NDEBUG
		 &&	(RFullPanelDial::gameside != RFullPanelDial::SIDE_LW)
#endif
		 &&	(Node_Data[SGT]>=Target::TSS_TargetFighterField)
		)

	{
		if (item!=UID_AF_NEWCASTLE)
			OpenACDossier(item,0);
		else
		{
			if (!LoggedChild(BASES))
				LogChild(BASES,BasesLuftflotte::Make());

	 		CRTabs* tab=(CRTabs*)LoggedChild(BASES)->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
			tab->SelectTab(3);
		}

	}else
	{
		if (LoggedChild(DOSSIER))
			CloseLoggedChild(DOSSIER);

		if (item!=UID_AF_NEWCASTLE)
			LogChild(DOSSIER,Dossier::Make(item));
	}

	
}
void CMainToolbar::CloseAllDialogs()
{
	for (int i = 0; i < MAX_ID; i++)
	{
		if 	(LoggedChild(i))
			 CloseLoggedChild(i);
	}
}
void CMainToolbar::CloseAllDialogsBut(int dialid)
{
	for (int i = 0; i < MAX_ID; i++)
	{
		if 	(		(LoggedChild(i))
				&&	(dialid != i)
			)
			 CloseLoggedChild(i);
	}
}

void CMainToolbar::TailorHints() 
{


	CRButton*	but = GETDLGITEM(dialids[SQUADRONLIST]);
	CRButton*	but2 = GETDLGITEM(dialids[ASSETLIST]);
	CRButton*	but3 = GETDLGITEM(dialids[HOSTILESLIST]);


	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		but->SetHintString(RESSTRING(GESCHWADERLIST));
		but2->SetHintString(RESSTRING(TARGETLIST));
		but3->SetHintString("");
	}else
	{
		but->SetHintString(RESSTRING(SQUADRONLIST));
		but2->SetHintString(RESSTRING(ASSETLIST));
		but3->SetHintString(RESSTRING(HOSTILESLIST));
	}

}

void CMainToolbar::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CRToolBar::OnShowWindow(bShow, nStatus);

}

void CMainToolbar::OnClickedAircraftalloc() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	if (!LoggedChild(ACALLOC))
		LogChild(ACALLOC,AircraftAllocation::Make()
							);
	else
		CloseLoggedChild(ACALLOC);
	
}

void CMainToolbar::OnClickedSquaronlist() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	CloseAllDialogsBut(SQUADRONLIST);
 
	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (!LoggedChild(SQUADRONLIST))
				LogChild(SQUADRONLIST,GeschwaderList::Make());
			else
				CloseLoggedChild(SQUADRONLIST);
	}else
	{
		if (!LoggedChild(SQUADRONLIST))
			LogChild(SQUADRONLIST,RAFSquadList::Make()
							);
		else
			CloseLoggedChild(SQUADRONLIST);
	}

	
}

void CMainToolbar::OnClickedReview() 
{ 
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (!LoggedChild(REVIEW))
				LogChild(REVIEW,LWReviewTop::Make()
									);
		else
				CloseLoggedChild(REVIEW);
	}else
	{
		if (!LoggedChild(REVIEW))
				LogChild(REVIEW,RAFReviewTop::Make()
									);
		else
				CloseLoggedChild(REVIEW);
	}
	
}

void CMainToolbar::OnClickedPilotdata() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

 		if (!LoggedChild(PILOTDATA))
			LogChild(PILOTDATA,PilotLogBook::Make()
								);
		else
			CloseLoggedChild(PILOTDATA);

	
}

void CMainToolbar::OnClickedAssetlist() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	if (LoggedChild(ACALLOC))
		CloseLoggedChild(ACALLOC);

	typedef	HideEdgeControl	EDGE; 
	if (!LoggedChild(ASSETLIST))
		LogChild(ASSETLIST,
			RDialog::MakeTopDialog(Place(POSN_MIN,POSN_MIN),
								DialList(DialBox(FIL_NULL,new CAuthorise,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
									HTabBox(FIL_NULL,IdList(IDS_AIRFIELDS,IDS_DOCKS,IDS_RADARSTATIONS,IDS_CONVOYS,IDS_LONDON,IDS_FACTORIES),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
		  								DialBox(FIL_D_LIST_AIRFIELD,new CSupply(Target::TT_FIGHTERAF)),//Target::TT_SECTORAF)),
		  								DialBox(FIL_D_LIST_DOCKS,new CSupply(Target::TT_DOCKS)),//Target::TT_DOCKS)),	//Target::TT_ARMAMENTS)), //CChoke
		  								DialBox(FIL_D_LIST_RADAR,new CSupply(Target::TT_CHAINHOME)),//Target::TT_CHAINHOME)),	//Target::TT_ARMAMENTS)), //CChoke
		  								DialBox(FIL_D_LIST_CONVOYS,new CSupply(Target::TT_CONVOY)),//Target::TT_CONVOY)),	//Target::TT_ARMAMENTS)),	//CTraffic
										DialBox(FIL_D_LIST_FACTORIES,new CSupply(Target::TT_LONDON)),//Target::TT_LONDON)),	//Target::TT_ARMAMENTS)),	//CAFields
										DialBox(FIL_D_LIST_FACTORIES,new CSupply(Target::TT_SPITASSEMBLY))//Target::TT_SPITASSEMBLY))	//Target::TT_ARMAMENTS))//CAFields
										
		  								)
								)	)	);
	else
		CloseLoggedChild(ASSETLIST);
	
}

void	CMainToolbar::OpenMissionfolder(bool special) 	
{
	if (LoggedChild(MISSIONFOLDER))
		CloseLoggedChild(MISSIONFOLDER);
	LogChild(MISSIONFOLDER, LWMissionFolder::Make(special));
	GETDLGITEM(dialids[MISSIONFOLDER])->SetPressed(TRUE);
}

void CMainToolbar::OnClickedMissionfolder() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	CloseAllDialogsBut(MISSIONFOLDER);
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		if (!LoggedChild(MISSIONFOLDER))
			LogChild(MISSIONFOLDER, LWMissionFolder::Make()
							);
		else
			CloseLoggedChild(MISSIONFOLDER);
	}else
	{
		if (!LoggedChild(MISSIONFOLDER))
			LogChild(MISSIONFOLDER, RAFMissionFolder::Make()
							);
		else
			CloseLoggedChild(MISSIONFOLDER);

	}
}

void CMainToolbar::OnClickedHostileslist() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

//##TEMPCODE RDH 12/04/00  	if (RFullPanelDial::gameside != RFullPanelDial::SIDE_LW)
	OpenHostileslist();
}
void CMainToolbar::OpenHostileslist() 
{
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_RAF)
	{
//RDH 2Aug00
//I don't know why we had these extra conditions. I've removed them
//because they cause problems with opening and closing the book
//DeadCode RDH 2Aug00 		if (		(Todays_Packages.hipack == Todays_Packages.oldhipack) 
//DeadCode RDH 2Aug00 				&&	(Todays_Packages.hisquad == Todays_Packages.oldhisquad) 
//DeadCode RDH 2Aug00 				&&	(LoggedChild(HOSTILESLIST))
//DeadCode RDH 2Aug00 			)
		if	(LoggedChild(HOSTILESLIST))
		{
			CloseLoggedChild(HOSTILESLIST);
		}else
		{
			CloseAllDialogsBut(HOSTILESLIST);
 			LogChild(HOSTILESLIST,HostilesList::Make());
		}	
	}
}

