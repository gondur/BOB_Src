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

// RowanDialog: // MscTlbr.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "MscTlbr.h"
#include "MigView.h"
#include "thumnail.h"
#include "savegame.h"
#include "package.h"
#include "replay.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// CMiscToolbar dialog


CMiscToolbar::CMiscToolbar(CWnd* pParent /*=NULL*/)
	: CRToolBar(pParent)
{
	//{{AFX_DATA_INIT(CMiscToolbar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMiscToolbar::DoDataExchange(CDataExchange* pDX)
{
	CRToolBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMiscToolbar)
	DDX_Control(pDX,IDC_REPLAY,m_IDC_REPLAY);
	DDX_Control(pDX,IDC_READYROOM,m_IDC_READYROOM);
	//}}AFX_DATA_MAP
	for (int id=0;dialids[id];id++)
		DDX_Control(pDX,dialids[id],m_dialids[id]);

}


BEGIN_MESSAGE_MAP(CMiscToolbar, CRToolBar)
	//{{AFX_MSG_MAP(CMiscToolbar)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMiscToolbar message handlers
				

BEGIN_EVENTSINK_MAP(CMiscToolbar, CRToolBar)
    //{{AFX_EVENTSINK_MAP(CMiscToolbar)
	ON_EVENT(CMiscToolbar, IDC_REPLAY, 1 /* Clicked */, OnClickedReplay, VTS_NONE)
	ON_EVENT(CMiscToolbar, IDC_READYROOM, 1 /* Clicked */, OnClickedReadyRoom, VTS_NONE)
	ON_EVENT(CMiscToolbar, IDC_THUMBNAIL, 1 /* Clicked */, OnClickedThumbnail, VTS_NONE)
	ON_EVENT(CMiscToolbar, IDC_FILES, 1 /* Clicked */, OnClickedFiles, VTS_NONE)
	ON_EVENT(CMiscToolbar, IDC_MAPFILTERS, 1 /* Clicked */, OnClickedMapfilters, VTS_NONE)
	ON_EVENT(CMiscToolbar, IDC_DIRECTIVETOGGLE, 1 /* Clicked */, OnClickedDirectivetoggle, VTS_NONE)
	ON_EVENT(CMiscToolbar, IDC_TOGGLEZOOM, 1 /* Clicked */, OnClickedTogglezoom, VTS_NONE)
	ON_EVENT(CMiscToolbar, IDC_ZOOMLEVEL, 1 /* Clicked */, OnClickedZoomlevel, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()
int CMiscToolbar::dialids[]={
		IDC_THUMBNAIL, IDC_ZOOMLEVEL,IDC_DIRECTIVETOGGLE,
			IDC_MAPFILTERS,IDC_FILES,/*DIRECTIVERESULTS, , DIRECTIVES*/NULL, 0};

void CMiscToolbar::OnClickedReplay() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	Todays_Packages.SaveBin();
//DeadCode AMM 7Aug00 	if (MMC.indebrief)
//DeadCode AMM 7Aug00 	{
//DeadCode AMM 7Aug00 // there is no debrief in campaign now, so go to save screen only
//DeadCode AMM 7Aug00 		INT3;
//DeadCode AMM 7Aug00 		if (_Replay.badrecord)									//AMM 09Mar99
//DeadCode AMM 7Aug00 			RFullPanelDial::RMessageBox(IDS_BOB,IDS_BADREPLAY,NULL,IDS_OK);
//DeadCode AMM 7Aug00 		else
//DeadCode AMM 7Aug00 		{
//DeadCode AMM 7Aug00 			_Replay.MapPlayback=true;
//DeadCode AMM 7Aug00 			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::replaysave,SaveData::UIR_FRAG);
//DeadCode AMM 7Aug00 		}
//DeadCode AMM 7Aug00 //DeadCode AMM 10Mar99 		RDialog::m_pView->LaunchFullPane(&RFullPanelDial::replaysave);
//DeadCode AMM 7Aug00 	}
//DeadCode AMM 7Aug00 	else
	{
		if (_Replay.badrecord)									//AMM 09Mar99
			RFullPanelDial::RMessageBox(IDS_BOB,IDS_BADREPLAY,NULL,IDS_OK);
		else
		{
			_Replay.MapPlayback=true;
			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::replaysave,SaveData::UIR_FRAG);
		}
//DeadCode AMM 7Aug00 		_Replay.MapPlayback=true;
//DeadCode AMM 7Aug00 //DeadCode AMM 26Feb99 		Todays_Packages.SaveBin();
//DeadCode AMM 7Aug00 //	if (!RFullPanelDial::incomms)								//rdh 10/1/99
//DeadCode AMM 7Aug00 		RDialog::m_pView->LaunchFullPane(&RFullPanelDial::replayload,SaveData::UIR_FRAG);
//DeadCode AMM 7Aug00 //	else
//DeadCode AMM 7Aug00 //		RDialog::m_pView->LaunchFullPane(&RFullPanelDial::SelectReadyRoom);
	}
		
}
void CMiscToolbar::OnClickedReadyRoom() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	if (_DPlay.UIPlayerType==DPlay::PLAYER_HOST)							//AMM 03Mar99
		_DPlay.UpdateMission=TRUE;								//AMM 03Mar99

	FullScreen* fs;
	RFullPanelDial::SelectReadyRoomStatic(fs);
	RDialog::m_pView->LaunchFullPane(fs,SaveData::UIR_FRAG);
		
}

//DEADCODE RDH 08/11/99 void CMiscToolbar::OnClickedZoomin() 
//DEADCODE RDH 08/11/99 {
//DEADCODE RDH 08/11/99 
//DEADCODE RDH 08/11/99 	if (!LoggedChild(CONTROL))
//DEADCODE RDH 08/11/99 		LogChild(CONTROL,ControlTopLevel::Make()
//DEADCODE RDH 08/11/99 						);
//DEADCODE RDH 08/11/99 	else
//DEADCODE RDH 08/11/99 		CloseLoggedChild(CONTROL);
//DEADCODE RDH 08/11/99 
//DEADCODE RDH 08/11/99 
//DEADCODE RDH 08/11/99 	
//DEADCODE RDH 08/11/99 //DEADCODE RDH 08/11/99 	RDialog::m_pView->OnZoomIn();
//DEADCODE RDH 08/11/99 }

//DEADCODE RDH 08/11/99 void CMiscToolbar::OnClickedZoomout() 
//DEADCODE RDH 08/11/99 {
//DEADCODE RDH 08/11/99 	RDialog::m_pView->OnZoomOut();
//DEADCODE RDH 08/11/99 }

void CMiscToolbar::OnClickedThumbnail() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	typedef	HideEdgeControl	EDGE;
	if (!LoggedChild(THUMBNAIL))
	{
		CMIGView::m_thumbnail=new CThumbnail;
		LogChild(THUMBNAIL,
			RDialog::MakeTopDialog(
			//CRect(140,140,0,0),
			Place(POSN_MIN,POSN_MIN),
								DialBox(FIL_NULL,CMIGView::m_thumbnail,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
				)					);
	}
	else
		CloseLoggedChild(THUMBNAIL);
}

void CMiscToolbar::ChildDialClosed(int dialnum,RDialog*,int rv)
{
	if (dialids[dialnum] && dialnum!=DIRECTIVESTOGGLE)
	{
		GETDLGITEM(dialids[dialnum])->SetPressed(FALSE);
		if (dialnum==0)
			CMIGView::m_thumbnail=NULL;
	}
}

void CMiscToolbar::OnClickedFiles() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	typedef	HideEdgeControl	EDGE; 
	CString	wildcard="*.bs";
	CFiling::selectedfile=Save_Data.lastsavegame;
	if (Todays_Packages.localplayer==NAT_RAF)
		wildcard+="R";
	else
		wildcard+="L";
//	CFiling::selectedfile="test.sav";
	if (!LoggedChild(FILES))
	{
		LogChild(FILES,
			RDialog::MakeTopDialog(Place(POSN_CENTRE,POSN_CENTRE),
								DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new CFiling,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)), //rdh
									HTabBox(FIL_NULL,IdList(IDS_SAVE,IDS_LOAD),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
									DialBox(FIL_D_BLANK/*IDB_BBC3*/,new CLoad(IDDX_SAVE,LSD_SAVE,			FIL_SAVEGAMEDIR,wildcard,CFiling::selectedfile)),
			  						DialBox(FIL_D_BLANK/*IDB_BBC3*/,new CLoad(IDDX_LOAD,LSD_LOAD_DESELECT,FIL_SAVEGAMEDIR,wildcard,CFiling::selectedfile))
				)					)	)	);
	}
	else
		CloseLoggedChild(FILES);
	
}

void CMiscToolbar::OpenSaveOnly(bool quitafter) 
{
	typedef	HideEdgeControl	EDGE;
	CString	wildcard="*.bs";
	CFiling::selectedfile=Save_Data.lastsavegame;
	if (Todays_Packages.localplayer==NAT_RAF)
		wildcard+="R";
	else
		wildcard+="L";
	if (!LoggedChild(FILES))
		LogChild(FILES,
			RDialog::MakeTopDialog(Place(POSN_CENTRE,POSN_CENTRE),
								DialList(DialBox(FIL_NULL/*IDB_BBC3*/,new CFiling(true),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)), //rdh
									HTabBox(FIL_NULL,IdList(IDS_QUITSAVE),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
									DialBox(FIL_D_BLANK/*IDB_BBC3*/,new CLoad(IDDX_SAVE,LSD_SAVE,			FIL_SAVEGAMEDIR,wildcard,CFiling::selectedfile))
				)					)	)	);
	else
		;//bring to front...
}

void CMiscToolbar::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CRToolBar::OnShowWindow(bShow, nStatus);
//DEADCODE RDH 19/03/99 	if (!RFullPanelDial::incomms)								//rdh 10/1/99
//DEADCODE RDH 19/03/99 	{
//DEADCODE RDH 19/03/99 		CRButton*   b;
//DEADCODE RDH 19/03/99 		b=GETDLGITEM(IDC_REPLAY);
//DEADCODE RDH 19/03/99 		b->ShowWindow(SW_SHOW);
//DEADCODE RDH 19/03/99 		b=GETDLGITEM(IDC_READYROOM);
//DEADCODE RDH 19/03/99 		b->ShowWindow(SW_HIDE);
//DEADCODE RDH 19/03/99 	}else
//DEADCODE RDH 19/03/99 	{
//DEADCODE RDH 19/03/99 		CRButton*   b;
//DEADCODE RDH 19/03/99 		b=GETDLGITEM(IDC_REPLAY);
//DEADCODE RDH 19/03/99 		b->ShowWindow(SW_HIDE);
//DEADCODE RDH 19/03/99 		b=GETDLGITEM(IDC_READYROOM);
//DEADCODE RDH 19/03/99 		b->ShowWindow(SW_SHOW);
//DEADCODE RDH 19/03/99 	}

	CRButton*	but = GETDLGITEM(IDC_REPLAY);
	but->SetPressed(FALSE);		//always lift replay button, might have been pressed
	if (RFullPanelDial::incomms)
	{
		but->SetDisabled(true);
		but->SetHintString(RESSTRING(NOTAVAIL));

	}else
	{
		but->SetDisabled(false);
		but->SetHintString(RESSTRING(REPLAY));

	}

  	but = GETDLGITEM(IDC_READYROOM);
	but->SetPressed(FALSE);		//always lift replay button, might have been pressed
	if (!RFullPanelDial::incomms)
	{
		but->SetDisabled(true);
		but->SetHintString(RESSTRING(NOTAVAIL));

	}else
	{
		but->SetDisabled(false);
		but->SetHintString(RESSTRING(READYROOM));

	}
	but = GETDLGITEM(dialids[DIRECTIVESTOGGLE]);
	but->SetPressed(!MMC.directivespopup);
	
		


}

void CMiscToolbar::OnClickedMapfilters() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	if (!LoggedChild(MAPFILTERS))
		LogChild(MAPFILTERS,MapFiltersTop::Make()
						);
	else
		CloseLoggedChild(MAPFILTERS);

	
}

void CMiscToolbar::OpenDirectiveResultsToggle(LWDirectivesResults* dirres) 
{
			
	if (LoggedChild(DIRECTIVERESULTS))
		CloseLoggedChild(DIRECTIVERESULTS);
	LogChild(DIRECTIVERESULTS,DirectiveResults::Make(dirres));

}
void CMiscToolbar::OpenEmptyDirectiveResults() 
{
			
	if (LoggedChild(DIRECTIVERESULTS))
		CloseLoggedChild(DIRECTIVERESULTS);
	LogChild(DIRECTIVERESULTS,DirectivesNoResults::Make());

}
void CMiscToolbar::OpenRAFDirectiveResultsToggle(RAFDirectivesResults* dirres) 
{
			
	if (LoggedChild(DIRECTIVERESULTS))
		CloseLoggedChild(DIRECTIVERESULTS);
	LogChild(DIRECTIVERESULTS,RAFDirectiveResults::Make(dirres));

}


void CMiscToolbar::OpenDirectivetoggle(LWDirectivesResults* dirres) 
{
	if (!LoggedChild(DIRECTIVES))
		LogChild(DIRECTIVES,LWDirectives::Make(dirres)
							);
	else
		CloseLoggedChild(DIRECTIVES);


}
void CMiscToolbar::OpenRAFDirectivetoggle(RAFDirectivesResults* dirres) 
{
	if (!LoggedChild(DIRECTIVES))
		LogChild(DIRECTIVES,RAFDirectives::Make(dirres)
							);
	else
		CloseLoggedChild(DIRECTIVES);

}
void CMiscToolbar::OnClickedDirectivetoggle() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	if	(MMC.directivespopup)
	   MMC.directivespopup = false;
	else
	   MMC.directivespopup = true;
	m_dialids[DIRECTIVESTOGGLE].SetHintString(RESSTRING(DIRECTIVES)+": "+RESLIST(OFF,!MMC.directivespopup));

	
//DEADCODE  18/02/00 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//DEADCODE  18/02/00 		OpenDirectivetoggle(NULL); 
//DEADCODE  18/02/00 	else
//DEADCODE  18/02/00 		OpenRAFDirectivetoggle(NULL); 

}

void CMiscToolbar::OnClickedTogglezoom() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

	float zoomdefault = m_pView->m_zoom	- Save_Data.defaultzoom;
	if (zoomdefault < 0)
		 zoomdefault = -zoomdefault;
	float secondzoom = m_pView->m_zoom	- Save_Data.secondzoom;
	if (secondzoom < 0)
		 secondzoom = -secondzoom;
	if (zoomdefault > secondzoom)
		m_pView->m_zoom = Save_Data.defaultzoom;
	else
		m_pView->m_zoom = Save_Data.secondzoom;

	RDialog::m_pView->OnZoom();
	
}

void CMiscToolbar::OnClickedZoomlevel() 
{
	if (RDialog::m_pView->m_currentpage != 0)							//RJS 29Oct00
 		return;															//RJS 29Oct00

 	if (!LoggedChild(ZOOMLEVEL))
		LogChild(ZOOMLEVEL,ZoomLevel::Make()
						);
	else
		CloseLoggedChild(ZOOMLEVEL);


}
