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

// MIGView.cpp : implementation of the CMIGView class
//
// This file draws the map.  
//		UpdateBitmaps(CDC* pDC)
//		DrawIcons()	  DrawIconTest	 SetVisibilityFlags
//		PlotRoutes	  InvalidateRoute
//
//	Plus mouse wheel input!
//	Plus main Zoom() routine.
//
//
#include "stdafx.h"
#include "_Mfc.h"
#include "MIG.h"
#include "MIGDoc.h"
#include "MIGView.h"
#include	"mymath.h"
#include "mytime.h"
#include <afxodlgs.h>
#include "MainFrm.h"
#include "fullpane.h"
#include "bfnumber.h"
#include	"persons2.h"
#include	"savegame.h"
#include	"node.h"
#include "uiicons.h"
#include	"monotxt.h"
#include	"miles.h"													//RJS 6Oct00
//Supposedly in the windows header file. Ho hum!
#define FIELDOFFSET(type, field)    ((int)&(((type *)0)->field))

//DeadCode RDH 16Mar100 MAKEFIELD(UniqueID,UID_NULL,IllegalSepID);
//DEADCODE RDH 29/02/00 #include "package.h"
//DEADCODE DAW 14/03/00 MAKEFIELD(UniqueID,UID_NULL,IllegalSepID);	//UniqueIDField
#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

const FileNum CMIGView::m_MapFiles[32][32]=
//{{FIL_NULL}};
{	//"frontmap.h"
#include "frmap2.h"
}
;

const FileNum CMIGView::m_MapFiles32[16][16]=
//{{FIL_NULL}};
{	//"frontmap.h"
#include "frmap3.h"
}
;


// the zoom thresholds where the map uses different bitmaps
// they are floats



CThumbnail* CMIGView::m_thumbnail=NULL;
/////////////////////////////////////////////////////////////////////////////
// CMIGView
extern CFont* g_AllFonts[][4];
extern CDC g_OffScreenDC;

//IMPLEMENT_DYNCREATE(CMIGView, CView)

	CObject* PASCAL CMIGView::CreateObject() \
		{ return new CMIGView; } \
	IMPLEMENT_RUNTIMECLASS(CMIGView, CView, 0xFFFF, \
		CMIGView::CreateObject)


BEGIN_MESSAGE_MAP(CMIGView, CView)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CMIGView)
	ON_WM_VSCROLL()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_MOVE()
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE( WM_GETARTWORK, OnGetArt)
	ON_MESSAGE( WM_GETXYOFFSET, OnGetXYOffset)
	ON_MESSAGE( WM_GETGLOBALFONT, OnGetGlobalFont)
	ON_MESSAGE( WM_GETFILE, OnGetFile)
	ON_MESSAGE( WM_RELEASELASTFILE, OnReleaseLastFile)
	ON_MESSAGE( WM_GETX2FLAG, OnGetX2Flag)
	ON_MESSAGE( WM_GETOFFSCREENDC, OnGetOffScreenDC)
	ON_MESSAGE( WM_GETHINTBOX, OnGetHintBox)
	ON_MESSAGE( WM_PLAYSOUND, OnPlaySound)
	ON_MESSAGE( WM_GETCOMBODIALOG, OnGetComboDialog)
	ON_MESSAGE( WM_GETCOMBOLISTBOX, OnGetComboListbox)
	ON_MESSAGE( WM_GETSTRING, OnGetString)
	ON_MESSAGE( WM_ACTIVEXSCROLL, OnActiveXScroll)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_POPUP_ZOOM_IN, OnZoomIn)
	ON_COMMAND(ID_POPUP_ZOOM_OUT, OnZoomOut)
	ON_COMMAND_RANGE(1000,2000, OnToolBarMenuGrid)
   
END_MESSAGE_MAP()

BEGIN_EVENTSINK_MAP(CMIGView, CView)
    //{{AFX_EVENTSINK_MAP(CMIGView)
//	ON_EVENT(CMIGView, IDC_CHANGE_TO_TITLE, 1 /* Clicked */, OnChangeToTitle, VTS_NONE)
//	ON_EVENT(CMIGView, IDC_AUTHORISE, 1 /* Clicked */, OnIntelligence, VTS_NONE)
	ON_EVENT(CMIGView, 1001, 1 /* Scroll */, OnScrollHorzScrollbar, VTS_I4)
	ON_EVENT(CMIGView, 1000, 1 /* Scroll */, OnScrollVertScrollbar, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMIGView construction/destruction
//CCustomBitmapButton* CMIGView::m_pAllButtons[]={{0}};

CMIGView::CMIGView()
{
	// Initialise map arrays
	// remember to change AIRSTRIPS etc. constants in .h file if this is modified
	// (AIRSTRIPS tells you the total number of airstrips)
	// this code is probably obsolete now...

// AIRSTRIPS

//	m_airstripCoords[0] = CPoint(520,1050);
//	m_airstripCoords[1] = CPoint(700,1200);
//	m_airstripCoords[2] = CPoint(620,1340);
//	m_airstripCoords[3] = CPoint(580,1090);
//	m_airstripsChecked = FALSE;

// BRIDGES

//	m_bridgeCoords[0] = CPoint(540,1080);
//	m_bridgeCoords[1] = CPoint(740,1300);
//	m_bridgesChecked = FALSE;

	m_doIexist=0;
//DEADCODE RDH 07/12/99 	m_zoom = ZOOMTHRESHOLD2+0.0001;	//1.02320;//1.11625; // initial zoom position
	m_zoom = Save_Data.defaultzoom+0.0001;
	if (m_zoom < ZOOMMIN)
		m_zoom = ZOOMTHRESHOLD2+0.0001;
	m_size.cx=256*4*m_zoom-5;
	m_size.cy=256*4*m_zoom-5;
	m_oldzoom=m_zoom;
	m_LButtonDown=FALSE;
//	m_scrollpoint=CPoint(m_size.cx/2,m_size.cy/2);
	m_scrollpoint=CPoint(400,800);//CPoint(111,380);//(111,452); // initial map position in pixels from the top left
	RDialog::m_pView=this;
	m_pfullpane=NULL;
//	m_bDontUpdateBitmaps=FALSE;
	m_drawing=FALSE;
	m_pfileblock=NULL;
//DEADCODE ROD 16/12/99 	m_iconradius=12;
	m_mapdlg.m_view=this;
}

CMIGView::~CMIGView()
{
	Persons4::ShutDownMapWorld();
}

BOOL CMIGView::PreCreateWindow(CREATESTRUCT& cs)
{

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMIGView drawing

void CMIGView::OnDraw(CDC* pDC)
{
	CMIGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	if (m_currentpage==0)
		m_mapdlg.ShowWindow(SW_SHOW);	// ensures window is always shown even if
//									// closed with escape key
//	else if (!m_pfullpane)
//	{
//		LaunchFullPane(&RFullPanelDial::introsmack);
//	}
	CRect rect;
	GetClientRect(rect);
	pDC->FillSolidRect(rect.right-16,rect.bottom-16,16,16,RGB(0,0,0));
}

/////////////////////////////////////////////////////////////////////////////
// CMIGView printing

BOOL CMIGView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMIGView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMIGView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMIGView diagnostics

#ifdef _DEBUG
void CMIGView::AssertValid() const
{
	CView::AssertValid();
}

void CMIGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMIGDoc* CMIGView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMIGDoc)));
	return (CMIGDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMIGView message handlers

void CMIGView::OnInitialUpdate()
{
	m_currentpage=1;
	CRect rect;
	GetClientRect(rect);
	// note that mapdlg is a child window instead of a pop-up window
	m_mapdlg.Create(CMapDlg::IDD,this);
//	m_mapdlg.ShowWindow(SW_SHOW);
	m_mapdlg.MoveWindow(0,0,30000,30000);
	m_rVertScrollBar.Create(NULL, WS_VISIBLE | WS_CHILD, CRect(-1,-1,-1,-1), this, 1000);
	m_rHorzScrollBar.Create(NULL, WS_VISIBLE | WS_CHILD, CRect(-1,-1,-1,-1), this, 1001);
	m_rVertScrollBar.SetParentPointer((long)this->m_hWnd);
	m_rHorzScrollBar.SetParentPointer((long)this->m_hWnd);
	m_rHorzScrollBar.SetHorzAlign(TRUE);

	ModifyStyleEx(GetExStyle(),NULL); // Bye bye annoying border!
}


void CMIGView::OnZoomIn() 
{
	CRect rect;
	GetClientRect(rect);
	// Zoom to centre of client window if toolbar used
	m_zoom=m_zoom*2;
	Zoom(CPoint(rect.right/2,rect.bottom/2));
}

void CMIGView::OnZoomOut() 
{
	CRect rect;
	GetClientRect(rect);
	m_zoom=m_zoom/2;
	Zoom(CPoint(rect.right/2,rect.bottom/2));
}

void CMIGView::OnToolBarMenuGrid(UINT nID)
{
#ifndef	BOB_DEMO_VER
	int	toolbarnum=(nID-1000)/10;
	int	toolbaritem=(nID-1000)%10;
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	switch (toolbarnum)
	{
	case 0:	//time
		switch (toolbaritem)
		{
		case 0:		main->m_titlebar.OnClickedDatetime();	break;
		case 1:		main->m_titlebar.OnClickedControl();	break;
		case 2:		main->m_titlebar.OnClickedPause();		break;
		case 3:		main->m_titlebar.OnClickedPlay();		break;
		case 4:		main->m_titlebar.OnClickedFastforward();break;
		}
	break;
	case 1: //main
		switch (toolbaritem)
		{
		case 0:		main->m_toolbar2.OnClickedAircraftalloc();	break;
		case 1:		main->m_toolbar2.OnClickedBases();			break;
		case 2:		main->m_toolbar2.OnClickedSquaronlist();	break;
		case 3:		main->m_toolbar2.OnClickedWeather();		break;
		case 4:		main->m_toolbar2.OnClickedReview();			break;
		case 5:		main->m_toolbar2.OnClickedPilotdata();		break;
		case 6:		main->m_toolbar2.OnClickedAssetlist();		break;
		case 7:		main->m_toolbar2.OnClickedMissionfolder();	break;
		case 8:		main->m_toolbar2.OnClickedHostileslist();	break;
		}
	break;
	case 2: //map tools
		switch (toolbaritem)
		{
		case 0:		main->m_toolbar3.OnClickedThumbnail();		break;
		case 1:		main->m_toolbar3.OnClickedZoomlevel();		break;
		case 2:		main->m_toolbar3.OnClickedTogglezoom();		break;
		case 3:		main->m_toolbar3.OnClickedDirectivetoggle();break;
		case 4:		main->m_toolbar3.OnClickedMapfilters();		break;
		case 5:		main->m_toolbar3.OnClickedFiles();			break;
		case 6:		main->m_toolbar3.OnClickedReplay();			break;
	
		}
	break;
	case 3: //messages
					main->m_reportbar.OnClickedLine1();			break;
	break;
	case 4: //map scale	- now help
		switch (toolbaritem)
		{
		case 0:	main->WinHelp(IDDT_TITLEBAR,HELP_CONTEXT);		break;
		case 1:	main->WinHelp(IDDT_MAINTOOLBAR,HELP_CONTEXT);	break;
		case 2:	main->WinHelp(IDDT_MISCTOOLBAR,HELP_CONTEXT);	break;
		case 3:	main->WinHelp(IDDT_TELETYPE,HELP_CONTEXT);		break;
		case 4:	main->WinHelp(IDDT_SCALE,HELP_CONTEXT);			break;

		case 9:	main->WinHelp(IDDT_SYSTEM,HELP_CONTEXT);		break;
		}

	break;
	}
#endif
}

//////////////////////////////////////////////////////////////////////
//
// Function:    MakeToolMenu
// Date:		05/11/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	CMainFrame::MakeToolMenu(CPoint point,int helpdialindex)
{
		if (point.x == -1 && point.y == -1)
		{
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

	CMenu	menu,secondary;
	menu.CreatePopupMenu();

	secondary.CreatePopupMenu();
	menu.AppendMenu(MF_POPUP|MF_STRING,(int)secondary.m_hMenu,RESSTRING(TIMETOOLBAR));
		secondary.AppendMenu(MF_STRING,1000,RESSTRING(TIMETOOLBAR));
		secondary.AppendMenu(MF_STRING,1001,RESSTRING(SPEEDCONTROL));
		secondary.AppendMenu(MF_STRING,1002,RESSTRING(PAUSE));
		secondary.AppendMenu(MF_STRING,1003,RESSTRING(NORMALTIME));
		secondary.AppendMenu(MF_STRING,1004,RESSTRING(ACCELCONTROL));
	secondary.Detach();
	secondary.CreatePopupMenu();
	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)			//RDH 17/05/00
	{
		menu.AppendMenu(MF_POPUP|MF_STRING,(int)secondary.m_hMenu,RESSTRING(MAIN));
			secondary.AppendMenu(MF_STRING,1010,RESSTRING(AIRCRAFTALLOC));
			secondary.AppendMenu(MF_STRING,1011,RESSTRING(RESOURCES));
			secondary.AppendMenu(MF_STRING,1012,RESSTRING(GESCHWADERLIST));
			secondary.AppendMenu(MF_STRING,1013,RESSTRING(WEATHER));
			secondary.AppendMenu(MF_STRING,1014,RESSTRING(REVIEW));
			secondary.AppendMenu(MF_STRING,1015,RESSTRING(PILOTINFO));
			secondary.AppendMenu(MF_STRING,1016,RESSTRING(TARGETLIST));
			secondary.AppendMenu(MF_STRING,1017,RESSTRING(MISSIONFOLDER));
	}else
	{
		menu.AppendMenu(MF_POPUP|MF_STRING,(int)secondary.m_hMenu,RESSTRING(MAIN));
			secondary.AppendMenu(MF_STRING,1010,RESSTRING(AIRCRAFTALLOC));
			secondary.AppendMenu(MF_STRING,1011,RESSTRING(RESOURCES));
			secondary.AppendMenu(MF_STRING,1012,RESSTRING(SQUADRONLIST));
			secondary.AppendMenu(MF_STRING,1013,RESSTRING(WEATHER));
			secondary.AppendMenu(MF_STRING,1014,RESSTRING(REVIEW));
			secondary.AppendMenu(MF_STRING,1015,RESSTRING(PILOTINFO));
			secondary.AppendMenu(MF_STRING,1016,RESSTRING(ASSETLIST));
			secondary.AppendMenu(MF_STRING,1017,RESSTRING(MISSIONFOLDER));
			secondary.AppendMenu(MF_STRING,1018,RESSTRING(HOSTILESLIST));

	}
	secondary.Detach();
	secondary.CreatePopupMenu();
	menu.AppendMenu(MF_POPUP|MF_STRING,(int)secondary.m_hMenu,RESSTRING(MAPTOOLS));
		secondary.AppendMenu(MF_STRING,1020,RESSTRING(THUMBNAILMAP));
		secondary.AppendMenu(MF_STRING,1021,RESSTRING(ZOOMLEVEL));
		secondary.AppendMenu(MF_STRING,1022,RESSTRING(ZOOMTOGGLE));
		secondary.AppendMenu(MF_STRING,1023,RESSTRING(DIRECTIVETOGGLE));
		secondary.AppendMenu(MF_STRING,1024,RESSTRING(MAPFILTERS));
		secondary.AppendMenu(MF_STRING,1025,RESSTRING(LOADSAVE));
		secondary.AppendMenu(MF_STRING,1026,RESSTRING(REPLAY));
	secondary.Detach();
	menu.AppendMenu(MF_STRING,1030,RESSTRING(MESSAGES));
	menu.AppendMenu(MF_STRING,1040+(helpdialindex%10),RESSTRING(PHRASE_HELPSHORT));
//DEADCODE RDH 12/05/00 	menu.AppendMenu(MF_STRING,1030,RESSTRING(MAPSCALE));
	CWnd* pWndPopupOwner = this;
	while (pWndPopupOwner->GetStyle() & WS_CHILD)
		pWndPopupOwner = pWndPopupOwner->GetParent();
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
		pWndPopupOwner);
	return true;
}

void CMIGView::OnZoom() 
{
	CRect rect;
	GetClientRect(rect);
	Zoom(CPoint(rect.right/2,rect.bottom/2));
}

void CMIGView::OnContextMenu(CWnd*, CPoint point)
{
	if (m_currentpage) return; // dont allow popup on frontend screens
	// CG: This block was added by the Pop-up Menu component
		if (point.x == -1 && point.y == -1)
		{
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
//DEADCODE RDH 10/05/00 		VERIFY(menu.CreatePopupMenu());
//DEADCODE RDH 10/05/00 		menu.AppendMenu(MF_STRING|MF_ENABLED,ID_POPUP_ZOOM_OUT,RESSTRING(ZOOMOUT));
//DEADCODE RDH 10/05/00 		menu.AppendMenu(MF_STRING|MF_ENABLED,ID_POPUP_ZOOM_IN,RESSTRING(ZOOMIN));
//DEADCODE RDH 10/05/00 		CMenu* pPopup=&menu;

		VERIFY(menu.LoadMenu(CG_IDR_POPUP_MIG_ALLEY_MFCVIEW));
		CMenu* pPopup=menu.GetSubMenu(0);
//DEADCODE RDH 10/05/00 		int state=pPopup->GetMenuState(ID_POPUP_ZOOM_IN, MF_BYCOMMAND ); 
//DEADCODE RDH 10/05/00 		state=pPopup->GetMenuState(ID_POPUP_ZOOM_OUT, MF_BYCOMMAND ); 
		if (m_zoom >= ZOOMMAX)
			pPopup->EnableMenuItem(ID_POPUP_ZOOM_IN,MF_GRAYED | MF_BYCOMMAND);
		else
			pPopup->EnableMenuItem(ID_POPUP_ZOOM_IN,MF_ENABLED | MF_BYCOMMAND);

		if (m_zoom <= ZOOMMIN)
			pPopup->EnableMenuItem(ID_POPUP_ZOOM_OUT,MF_GRAYED | MF_BYCOMMAND);
		else
			pPopup->EnableMenuItem(ID_POPUP_ZOOM_OUT,MF_ENABLED | MF_BYCOMMAND);

//DEADCODE RDH 10/05/00 
//DEADCODE RDH 10/05/00 		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;
		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
//	::AfxTrace("Menu P (%i,%i)\n", point.x, point.y);
		CRect rect;
		GetWindowRect(rect);
		m_popupPoint=point-rect.TopLeft();
	
}

void CMIGView::ZoomToUID(UniqueID uid, double zoom)
{
	int px,py;
	ItemBasePtr p;
	p=Persons2::ConvertPtrUID(uid);
	ASSERT(p);
	ScreenXY(p,px,py,0,0);
//DEADCODE JIM 06/12/99 	px=((p->World.X*m_zoom)/65536)-(384*m_zoom);
//DEADCODE JIM 06/12/99 	py=(1792*m_zoom)-((p->World.Z*m_zoom)/65536);
	CRect rect;
	GetClientRect(rect);
	// Zoom to centre of client window if toolbar used
	m_scrollpoint.x=px-rect.right/2;
	m_scrollpoint.y=py-rect.bottom/2;
	m_zoom=zoom;
	Zoom(CPoint(rect.right/2,rect.bottom*3/8));						  //RDH 20/12/99
	m_mapdlg.Invalidate();

//	Zoom(CPoint(px,py));
}

//TEMPCODE DAW 18/02/00 void CMIGView::OnPopupZoomIn() 
//TEMPCODE DAW 18/02/00 {
//TEMPCODE DAW 18/02/00 //	::AfxTrace("Zoom IN (%i,%i)\n", m_popupPoint.x, m_popupPoint.y);
//TEMPCODE DAW 18/02/00 	m_zoom=m_zoom*1.2599;
//TEMPCODE DAW 18/02/00 	Zoom(m_popupPoint);
//TEMPCODE DAW 18/02/00 }



//TEMPCODE DAW 18/02/00 void CMIGView::OnPopupZoomOut() 
//TEMPCODE DAW 18/02/00 {
//TEMPCODE DAW 18/02/00 //	::AfxTrace("Zoom OUT (%i,%i)\n", m_popupPoint.x, m_popupPoint.y);
//TEMPCODE DAW 18/02/00 	m_zoom=m_zoom*0.7937;
//TEMPCODE DAW 18/02/00 	Zoom(m_popupPoint);		
//TEMPCODE DAW 18/02/00 }

// The New Way...
void	CMIGView::ScreenXY(int wx,int wz,int&px,int&py)
{
	ScreenXY(wx,wz,px,py,	-m_scrollpoint.x,-m_scrollpoint.y);
}
void	CMIGView::ScreenXY(int wx,int wz,int&px,int&py,int scrollx,int scrolly)
{
	px=((wx*m_zoom)/65536)+scrollx;
	py=(1024*m_zoom)-((wz*m_zoom)/65536)+scrolly;
}
void	CMIGView::ScreenXY(ItemBasePtr p,int&px,int&py)
{
	ScreenXY(p,px,py,	-m_scrollpoint.x,-m_scrollpoint.y);
}

static struct	BandPointOffset
{
	UniqueIDBand	b;
	POINT			p;
}	bandpoints[16]={PilotedAcBAND};

static int	nextpoint=0;
void	CMIGView::ScreenXY(Coords3D* w,int&px,int&py,int scrollx,int scrolly)
{
	ScreenXY(w->X,w->Z,px,py,scrollx,scrolly);

}
void	CMIGView::ScreenXY(ItemBasePtr p,int&px,int&py,int scrollx,int scrolly)
{
	if (p->Status.size==AIRSTRUCSIZE)
		ScreenXY(&info_airgrpPtr(*p)->knownposition,px,py,scrollx,scrolly);
	else
		ScreenXY(&p->World,px,py,scrollx,scrolly);
//DeadCode JIM 8Nov00 	if (p->Status.size>=ITEMSIZE)
//DeadCode JIM 8Nov00 	{
//DeadCode JIM 8Nov00 		ItemPtr q=*p;
//DeadCode JIM 8Nov00 		if (q->SGT)
//DeadCode JIM 8Nov00 		{
//DeadCode JIM 8Nov00 			ItemBasePtr p2=Persons2::ConvertPtrUID(q->SGT);
//DeadCode JIM 8Nov00 			if (p2->World.X==p->World.X && p2->World.Z==p->World.Z)
//DeadCode JIM 8Nov00 			{
//DeadCode JIM 8Nov00 				enum	{SMALLICONSIZE=24,SMALLICONRADIUS=12,LARGEICONRADIUS=36,CENTRE2CENTRE=SMALLICONRADIUS*3};
//DeadCode JIM 8Nov00 				if (!nextpoint)
//DeadCode JIM 8Nov00 					for (int i=0,offset=-CENTRE2CENTRE;i<3;i++,offset+=SMALLICONSIZE)
//DeadCode JIM 8Nov00 					{
//DeadCode JIM 8Nov00 						bandpoints[i].p.x=CENTRE2CENTRE;	bandpoints[i].p.y=offset;			//RHS
//DeadCode JIM 8Nov00 						bandpoints[i+3].p.x=-offset;		bandpoints[i+3].p.y=CENTRE2CENTRE;	//BOTTOM
//DeadCode JIM 8Nov00 						bandpoints[i+6].p.x=-CENTRE2CENTRE;	bandpoints[i+6].p.y=-offset;		//LHS
//DeadCode JIM 8Nov00 						bandpoints[i+9].p.x=offset;			bandpoints[i+9].p.y=-CENTRE2CENTRE;	//TOP
//DeadCode JIM 8Nov00 					}
//DeadCode JIM 8Nov00 				UniqueIDBand b=Persons2::getbandfromUID(p->uniqueID.count);
//DeadCode JIM 8Nov00 				bandpoints[nextpoint].b=b;
//DeadCode JIM 8Nov00 				int	entry;
//DeadCode JIM 8Nov00 				for (entry=0;bandpoints[entry].b!=b;entry++)
//DeadCode JIM 8Nov00 				{}
//DeadCode JIM 8Nov00 				if (entry==nextpoint && entry!=11)
//DeadCode JIM 8Nov00 					nextpoint++;
//DeadCode JIM 8Nov00 				px+=bandpoints[entry].p.x;
//DeadCode JIM 8Nov00 				py+=bandpoints[entry].p.y;
//DeadCode JIM 8Nov00 			}
//DeadCode JIM 8Nov00 		}
//DeadCode JIM 8Nov00 	}
}
int	CMIGView::WorldXY(int& wx,int& wz,int sx,int sy)
{
	wx=((sx+m_scrollpoint.x)*65536.0)/m_zoom;
	wz=65536*1024-((sy+m_scrollpoint.y)*65536.0)/m_zoom;
	return BIGGEST_ICON_RADIUS*65536.0/m_zoom;
}

int	CMIGView::WorldXY(Coords3D& w,int sx,int sy)
{
	return WorldXY((int&)w.X,(int&)w.Z,sx,sy);
}


//DEADCODE AMM 15/12/99 void	CMIGView::DrawIcon(HDC hDC,int px,int py,BYTE* pData,BITMAPINFO* pInfo)
//DEADCODE AMM 15/12/99 {
//DEADCODE AMM 15/12/99 	SetDIBitsToDevice(hDC,px-m_scrollpoint.x-m_iconradius,py-m_scrollpoint.y-m_iconradius+1,m_iconradius*2,m_iconradius*2,
//DEADCODE AMM 15/12/99 		0,0,0,m_iconradius*2,pData,pInfo,DIB_RGB_COLORS);
//DEADCODE AMM 15/12/99 }
void CMIGView::LollyOut(CDC* pDC,int x,int y,CString shortname)
{
	if (shortname.GetLength()>3 && (shortname[1]==' ' || shortname[2]==' '))
	{
		CString l1,l2;
		if (shortname[1]==' ')
		{
			l1=shortname.Left(1);
			l2=(const char*)shortname+2;
			if (l2[0]=='(')
				l2=l2.Mid(1,l2.GetLength()-2);
		}
		else
		{
			l1=shortname.Left(2);
			l2=(const char*)shortname+3;
			if (l2[0]=='(')
				l2=l2.Mid(1,l2.GetLength()-2);
		}
		pDC->TextOut(x,y-5,l1);
		pDC->TextOut(x,y+7,l2);


	}
	else
	if (shortname.GetLength()>3 && (shortname[1]=='(' || shortname[2]=='('))
	{
		CString l1,l2;
		if (shortname[1]=='(')
		{
			l1=shortname.Left(1);
			l2=shortname.Mid(2,shortname.GetLength()-3);
		}
		else
		{
			l1=shortname.Left(2);
			l2=shortname.Mid(3,shortname.GetLength()-4);
		}
		pDC->TextOut(x,y-5,l1);
		pDC->TextOut(x,y+7,l2);


	}

	else
		pDC->TextOut(x,y,shortname);


}

//////////////////////////////////////////////////////////////////////
//
// Function:    DrawIcon/DrawIconText/DrawTextInIcon
// Date:		21/01/00
// Author:		JIM
//
//Description: 	Icon drawing routines
//
//////////////////////////////////////////////////////////////////////
void CMIGView::DrawIconExtra(CDC* pDC,int px,int py,IconsUI	f,UniqueID	i, bool hilight)
{
	enum	{LOLYBORDERX=12,LOLYBORDERY=3,
				RAFACX=18,RAFACY=4,RAFALTX=18,RAFALTY=24,
				LWRAIDX=-21,LWRAIDY=6-36,LWACX=-21,LWACY=28-36,LWALTX=-10,LWALTY=50-36
			};

	IconDescUI ICON=f;
	CPoint ICONWH=ICON.WH();
	if (ICONWH.x>40)
	{
		static int	letterspacing[]={11,11,11,11,11} ;
		static int	RAFletterspacing[]={16,16,16,16} ;

		UniqueIDBand b=Persons2::getbandfromUID(i);
		switch (b)
		{
		case	SagBAND:
		{
			px-=m_scrollpoint.x;
			py-=m_scrollpoint.y;
			CFont* oldfont=pDC->SelectObject(OnGetGlobalFont(13));
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextAlign(TA_LEFT | TA_TOP | TA_NOUPDATECP);


			int packnum,sqline;
			if (Todays_Packages.GetACSquadEntry(i,packnum,sqline))
			{
				int numsquads=Todays_Packages[packnum].squadlist;
				int	totalac=0,raidline,firstsquadoriginal=0;
				int	sqlinemin;
				{
					raidline = Todays_Packages[packnum].GetRaidIndFromSquadEntry(sqline);
					int	sqlinemin=Todays_Packages[packnum].RaidNumEntriesMinSq(raidline);
					firstsquadoriginal=Todays_Packages[packnum][sqlinemin].numacoriginal;
					int	sqlinemax=Todays_Packages[packnum].RaidNumEntriesMaxSq(raidline);
//DEADCODE RDH 29/02/00 					int	sqlinemin=Todays_Packages[packnum].raidnumentries[raidline-1].squadliststart,
//DEADCODE RDH 29/02/00 						sqlinemax=numsquads;
//DEADCODE RDH 29/02/00 					if (sqlinemax>Todays_Packages[packnum].raidnumentries[raidline+1].squadliststart)
//DEADCODE RDH 29/02/00 						sqlinemax=Todays_Packages[packnum].raidnumentries[raidline+1].squadliststart;
					for(;sqlinemax>=sqlinemin;sqlinemax--)
						if (Todays_Packages[packnum][sqlinemax].playercansee)
							totalac+=Todays_Packages[packnum][sqlinemax].numacleft;
				}
				if (Todays_Packages[packnum].raidnumentries[raidline].detector)
				{


					if (Todays_Packages[packnum].attackmethod<Profile::AM_LWPACKS)
					{	//PLOT RAF BOX WITH LOLIPOPS!
						CPoint backupmain(px,py);
						IconDescUI	biglolypop(ICON_SQUAREPADDLE);			//RDH 29/02/00
						py-=ICONWH.y/2;
						CPoint bigqwh=biglolypop.WH();
 						if (Todays_Packages.localplayer==NAT_RAF)	  //No lollies if German!
						{
							pDC->SetTextAlign(TA_CENTER | TA_TOP | TA_NOUPDATECP);

							if (hilight)
								pDC->SetTextColor(RGB(0,0,0));
							else
								pDC->SetTextColor(RGB(100,100,100));

							if (Todays_Packages[packnum].RaidNumEntriesMinSq(raidline)==sqline)
								if (numsquads==1)
								{	//Draw big lolly and small lolly
									px-=ICONWH.x/2;
									{	
										CPoint lolypos(px,py+1-bigqwh.y);
										biglolypop.MaskIcon(pDC,lolypos);		  //Squadron
										CString shortname=Node_Data[SquadNum(Todays_Packages[packnum][0].squadnum)].ShortName();
										LollyOut(pDC,lolypos.x+LOLYBORDERX,lolypos.y+LOLYBORDERY,shortname);
										px+=bigqwh.x/3;
									}
									if (firstsquadoriginal<12)
									{
										int acbitssquad=Todays_Packages[packnum].squadlist.AcBitsFirstSquad();
									
										for (int	masknum=ICON_ROUNDPADDLE_R,flightmask=0x7;flightmask<0x1000;flightmask<<=3,masknum++)	//ENABLE THIS WHEN YOU HAVE (4) ICONS!!!
										if (acbitssquad&flightmask)
										{

											IconDescUI	smalllolypop=IconsUI(masknum);	//RDH 29/02/00


											CPoint bigqwh=smalllolypop.WH();
											CPoint lolypos(px,py-bigqwh.y);
											smalllolypop.MaskIcon(pDC,lolypos);		  //Squadron
									
	//DEADCODE RDH 12/05/00 										CString shortname;shortname.Format("%c",('A'+acindexfirstsquad/3));
	//DEADCODE RDH 12/05/00 										pDC->TextOut(lolypos.x+LOLYBORDERX,lolypos.y+LOLYBORDERY,shortname);
	//DEADCODE RDH 12/05/00 										acdown-=3;
	//DEADCODE RDH 12/05/00 										acindexfirstsquad+=3;
											px+=bigqwh.x/3;
										}
									}
								}
								else
								{	//Draw row of lolypops
									CPoint lolypos(px,py+1-bigqwh.y);
//DeadCode JIM 20Oct00 									int tx=px;
									lolypos.x-=ICONWH.x/2+3;
									{
										biglolypop.MaskIcon(pDC,lolypos);		  //Squadron
										CString shortname=Todays_Packages[packnum][0].Squadron().ShortName();
										LollyOut(pDC,lolypos.x+LOLYBORDERX,lolypos.y+LOLYBORDERY,shortname);
										lolypos.x+=bigqwh.x;
									}
									{
										biglolypop.MaskIcon(pDC,lolypos);		  //Squadron
										CString shortname=Todays_Packages[packnum][1].Squadron().ShortName();
										LollyOut(pDC,lolypos.x+LOLYBORDERX,lolypos.y+LOLYBORDERY,shortname);
										lolypos.x+=bigqwh.x;
									}
									if (numsquads>2)
									{
										lolypos.x+=8-2*bigqwh.x;
										lolypos.y+=16;
										IconDescUI	biglolypop(ICON_SQUAREPADDLE2);			//RDH 29/02/00
										{
											biglolypop.MaskIcon(pDC,lolypos);		  //Squadron
											CString shortname=Todays_Packages[packnum][2].Squadron().ShortName();
											LollyOut(pDC,lolypos.x+LOLYBORDERX,lolypos.y+LOLYBORDERY,shortname);
											lolypos.x+=bigqwh.x;
										}
										if (numsquads>3)
										{
											biglolypop.MaskIcon(pDC,lolypos);		  //Squadron
											CString shortname=Todays_Packages[packnum][3].Squadron().ShortName();
											LollyOut(pDC,lolypos.x+LOLYBORDERX,lolypos.y+LOLYBORDERY,shortname);
											lolypos.x+=bigqwh.x;
										}
									}
									if (numsquads>4)		   //move far enough across
									{
										lolypos.x+=8-2*bigqwh.x;
										lolypos.y+=16;
										IconDescUI	biglolypop(ICON_SQUAREPADDLE3);			//RDH 29/02/00
										{
											biglolypop.MaskIcon(pDC,lolypos);		  //Squadron
											CString shortname=Todays_Packages[packnum][4].Squadron().ShortName();
											LollyOut(pDC,lolypos.x+LOLYBORDERX,lolypos.y+LOLYBORDERY,shortname);
											lolypos.x+=bigqwh.x;
										}
										if (numsquads>5)
										{
											biglolypop.MaskIcon(pDC,lolypos);		  //Squadron
											CString shortname=Todays_Packages[packnum][5].Squadron().ShortName();
											LollyOut(pDC,lolypos.x+LOLYBORDERX,lolypos.y+LOLYBORDERY,shortname);
											lolypos.x+=bigqwh.x;
										}
									}
								}
						}
						//Draw body


						pDC->SetTextAlign(TA_LEFT | TA_TOP | TA_NOUPDATECP);

						px=backupmain.x;
						px-=ICONWH.x/2;
						CString	forcesize;
	//DEADCODE RDH 01/03/00 					if (Todays_Packages.localplayer==NAT_BLUE)	 //Estimate number if german
	//DEADCODE RDH 01/03/00 					{
	//DEADCODE RDH 01/03/00 						if (totalac>50)
	//DEADCODE RDH 01/03/00 							totalac-=totalac%50;
	//DEADCODE RDH 01/03/00 						else
	//DEADCODE RDH 01/03/00 							totalac-=totalac%10;
	//DEADCODE RDH 01/03/00 						forcesize.Format("%i+",totalac);
	//DEADCODE RDH 01/03/00 					}
	//DEADCODE RDH 01/03/00 					else
							forcesize.Format("%2i",totalac);
	//( int x, int y, UINT nOptions, LPCRECT lpRect, const CString& str, LPINT lpDxWidths );
						if (hilight)
							pDC->SetTextColor(RGB(255,0,0));
						else
							pDC->SetTextColor(RGB(255,80,80));

						pDC->ExtTextOut(px+RAFACX,py+RAFACY,0,CRect(0,0,0,0),forcesize,RAFletterspacing);
						info_airgrp* a=Persons2::ConvertPtrUID(i);
						forcesize.Format("%2i",a->knownposition.Y/FT_1000);
						if (hilight)
							pDC->SetTextColor(RGB(255,255,255));
						else
							pDC->SetTextColor(RGB(160,160,160));
						pDC->ExtTextOut(px+RAFALTX,py+RAFALTY,0,CRect(0,0,0,0),forcesize,RAFletterspacing);
					}
					else
					{	//PLOT LW BOX!
						CString	forcesize;
						char* raidletter = Todays_Packages.RaidFormatString(packnum, raidline);
						forcesize.Format(CSprintf(raidletter, Todays_Packages[packnum].raidnumentries[raidline].raidnum));


	//DEADCODE RDH 13/04/00 					if (Todays_Packages.localplayer!=NAT_BLUE)
	//DEADCODE RDH 13/04/00 						if (!Todays_Packages[packnum].raidnumentries[raidline].detector)
	//DEADCODE RDH 13/04/00 //DEADCODE RDH 12/04/00 						if (Todays_Packages[packnum].raidnumentries[raidline].detector>=Profile::CHBASE)
	//DEADCODE RDH 13/04/00 							forcesize.Format("X%03i",Todays_Packages[packnum].raidnumentries[raidline].raidnum);
	//DEADCODE RDH 13/04/00 						else
	//DEADCODE RDH 13/04/00 							forcesize.Format("H%03i",Todays_Packages[packnum].raidnumentries[raidline].raidnum);
	//DEADCODE RDH 13/04/00 					else
	//DEADCODE RDH 13/04/00 						forcesize.Format("R%i",Todays_Packages[packnum].raidnumentries[raidline].raidnum);
	//DEADCODE RDH 13/04/00 

						if (hilight)
							pDC->SetTextColor(RGB(55,55,55));
						else
							pDC->SetTextColor(RGB(130,130,130));
						pDC->ExtTextOut(px+LWRAIDX,py+LWRAIDY,0,CRect(0,0,0,0),forcesize,letterspacing);
						if (Todays_Packages.localplayer!=NAT_BLUE)	//Estimate number if Brit
						{
							if (totalac>=100)
								totalac-=totalac%50;
							else
								if (totalac>=20)
									totalac-=totalac%10;
								else
									if (totalac>=5)
										totalac-=totalac%5;
							if (totalac>=1000)
								forcesize.Format("%4i",totalac);
							else
								forcesize.Format("%3i+",totalac);
						}
						else
							forcesize.Format("%3i",totalac);
						if (hilight)
							pDC->SetTextColor(RGB(255,255,255));
						else
							pDC->SetTextColor(RGB(170,170,170));
						pDC->ExtTextOut(px+LWACX,py+LWACY,0,CRect(0,0,0,0),forcesize,letterspacing);
						info_airgrp* a=Persons2::ConvertPtrUID(i);
						forcesize.Format("%2i",a->knownposition.Y/FT_1000);
						pDC->ExtTextOut(px+LWALTX,py+LWALTY,0,CRect(0,0,0,0),forcesize,letterspacing);
						//PLOT LW ARROW
						//Get heading... Currently reading from route
 						if (Save_Data.mapfilters[FILT_LWARROWS])
						{
//DeadCode JIM 11Nov00 							Coords3D* positions=Todays_Packages[packnum].raidnumentries[raidline].prevpositions;
//DeadCode JIM 20Oct00 							ScreenXY(positions,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
							ANGLES angle=a->knownhdg+ANGLES_180Deg;
//DeadCode JIM 11Nov00 							angle=Math_Lib.HighArcTan(positions[1].X-positions[0].X,positions[1].Z-positions[0].Z);
							double s,c;
							Math_Lib.high_sin_cos(angle,s,c);
							CPen* oldpen;
		//CPen( int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount = 0, const DWORD* lpStyle = NULL );
							POINT	arrowpoints[3];
	#define ARROW_FIXX 30
	#define ARROW_FIXY 35
	#define ARROW_RAD 25
	#define	ARROW_HEAD 15
	#define	ARROW_HF 6
	#define	ARROW_TAIL 4
							arrowpoints[0].x=px-ARROW_FIXX+c*ARROW_HEAD-s*ARROW_HF;	arrowpoints[0].y=py+ARROW_FIXY+s*ARROW_HEAD+c*ARROW_HF;
							arrowpoints[1].x=px-ARROW_FIXX-c*ARROW_HEAD-s*ARROW_HF;	arrowpoints[1].y=py+ARROW_FIXY-s*ARROW_HEAD+c*ARROW_HF;
							arrowpoints[2].x=px-ARROW_FIXX-s*ARROW_RAD;				arrowpoints[2].y=py+ARROW_FIXY+c*ARROW_RAD;
							int	time=a->knowntime;	//positions[0].Y;
							COLORREF arrowcolour=RGB(200,200,200);
							if (MMC.currtime-time<SECSPERMIN*15)
							{
								time/=SECSPERMIN*5;
								time%=3;
								switch (time)
								{
								case 0:	arrowcolour=RGB(255,0,0);	break;
								case 1:	arrowcolour=RGB(230,230,0);	break;
								case 2:	arrowcolour=RGB(0,0,255);	break;
								}

							}

			
							CBrush brush(arrowcolour);
							CBrush* pOldBrush = pDC->SelectObject(&brush);		//				LOGBRUSH	br={BS_SOLID,arrowcolour,0};
							CPen newpen1(PS_SOLID,1,arrowcolour);
							oldpen=pDC->SelectObject(&newpen1);
							pDC->Polygon(arrowpoints,3);
							arrowpoints[0].x=px-ARROW_FIXX+c*ARROW_TAIL+s*ARROW_RAD;arrowpoints[0].y=py+ARROW_FIXY+s*ARROW_TAIL-c*ARROW_RAD;
							arrowpoints[1].x=px-ARROW_FIXX-c*ARROW_TAIL+s*ARROW_RAD;arrowpoints[1].y=py+ARROW_FIXY-s*ARROW_TAIL-c*ARROW_RAD;
	//TEMPCODE RDH 29/02/00 						arrowpoints[2].x=px-FIX-s*30;		arrowpoints[2].y=py+FIX+c*30;
							pDC->Polygon(arrowpoints,3);
							pDC->SelectObject(oldpen);
							pDC->SelectObject(pOldBrush);
						}
					}
				}
			}
			pDC->SelectObject(oldfont);
		}
		break;
		case	RAF_FighterAFBAND:
		{


		}
		break;
		default:;
		}
	}
}

Campaign::TimeColours	Campaign::TimeColour(int timetotest)
{
	if (timetotest)
	{
		if (currtime-timetotest>SECSPERMIN*15)
			return TC_OLD;
	}
	else
		timetotest=currtime;
	return TimeColours((timetotest/(SECSPERMIN*5))%3);
}

void	CMIGView::DrawIcon(CDC* pDC,int px,int py,IconsUI f)
{
	if (f>=0x10000)
	{
		IconDescUI icon(f);
		CPoint wh=icon.WH();
		int dx=wh.x/2,dy=wh.y/2;
		icon.MaskIcon(pDC  ,CPoint(px-m_scrollpoint.x-dx,py-m_scrollpoint.y-dy+1));
	}	   
	else
	{
//DEADCODE AMM 15/12/99 
//DEADCODE AMM 15/12/99 		fileblock	block(f);
//DEADCODE AMM 15/12/99 		BYTE*				pData=(BYTE*)getdata(block);
//DEADCODE AMM 15/12/99 		BITMAPFILEHEADER*	pFile=(BITMAPFILEHEADER*)pData;
//DEADCODE AMM 15/12/99 		BITMAPINFO*			pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
//DEADCODE AMM 15/12/99 		pData+=pFile->bfOffBits;
//DEADCODE AMM 15/12/99 		DrawIcon(hDC,px,py,pData,pInfo);
	}
}				
void	CMIGView::DrawIconText(CDC* pDC,int px,int py,UniqueID u, bool hilight)
{
	CString s;
//Done in gettargname itself
//DEADCODE DAW 10/03/00 	if (u>=SagBAND && u<SagBANDEND)
//DEADCODE DAW 10/03/00 	{
//DEADCODE DAW 10/03/00 		//find pack from sag
//DEADCODE DAW 10/03/00 		int pack = 0;
//DEADCODE DAW 10/03/00 		Todays_Packages.GetACSquadEntry(u,pack);
//DEADCODE DAW 10/03/00 		Profile& pk = Todays_Packages.pack[pack];
//DEADCODE DAW 10/03/00 		s = CSprintf("F%i", pk.raidnumentries[0].raidnum);
//DEADCODE DAW 10/03/00 	}else

	IconsUI i =IconsUI( RDialog::m_pView->DrawIconTest( NULL, u, hilight,false));
	if (i)
	{
		s=GetTargName(u,true);
		CSize size=pDC->GetTextExtent(s);
		CPoint iconsize=IconDescUI(i).WH();
		int dx=iconsize.x/2,dy=iconsize.y/2;
		pDC->SetBkMode(OPAQUE);
		if (hilight)
			pDC->SetTextColor(RGB(5,5,55));
		else
			pDC->SetTextColor(RGB(80,80,135));

		COLORREF backcol=RGB(230,230,230),normcol=RGB(80,80,135),hicol=RGB(5,5,55);
		if (u>=SagBAND && u<SagBANDEND)
		{
			info_airgrpPtr ag=Persons2::ConvertPtrUID(u);
			Campaign::TimeColours tc=MMC.TimeColour(ag->knowntime);
			if (ag->knowntime!=ag->lasttime)
				backcol=RGB(0,0,0);
			switch (tc)
			{
			case	Campaign::TC_RED:		normcol=RGB(255,50,50);hicol=RGB(240,0,0);			break;
			case	Campaign::TC_YELLOW:	normcol=RGB(180,180,0);hicol=RGB(140,140,0);		break;
			case	Campaign::TC_BLUE:		normcol=RGB(50,50,255);hicol=RGB(0,0,240);			break;
			case	Campaign::TC_OLD:		normcol=RGB(200,200,200);hicol=RGB(240,240,240);	break;
			}
		}

		pDC->SetBkColor(backcol);
		if (hilight)
			pDC->SetTextColor(hicol);
		else
			pDC->SetTextColor(normcol);
		

		if (dx>15)
			pDC->TextOut(px-m_scrollpoint.x-dx,py-m_scrollpoint.y+dy,s);
		else
			pDC->TextOut(px-m_scrollpoint.x+dx,py-m_scrollpoint.y-dy+2,s);
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    InvalidateIcon
// Date:		21/01/00
// Author:		JIM
//
//Description: 	Icon invalidation routines. These are better here, next to the draw routines.
//
//////////////////////////////////////////////////////////////////////
void	CMapDlg::InvalidateIconExtra(int px,int py,ItemBasePtr p,IconsUI i)
{
//DeadCode JIM 9Oct00 	#define ARROW_FIX 35
//DeadCode JIM 9Oct00 	#define ARROW_RAD 25
	IconDescUI ICON=i;
	CPoint ICONWH=ICON.WH();
	if (ICONWH.x>40)
	{
		UniqueIDBand b=Persons2::getbandfromUID(p->uniqueID.count);
		switch (b)
		{
		case	SagBAND:
		{
			int packnum,sqline;
			if (Todays_Packages.localplayer==NAT_RAF) //raf PLAYER SEES ARROWS AND LOLIPOPS!
				if (Todays_Packages.GetACSquadEntry(p->uniqueID.count,packnum,sqline))
				{
					int	raidline=Todays_Packages[packnum].GetRaidIndFromSquadEntry(sqline);
//DeadCode JIM 20Oct00 					Coords3D* positions=Todays_Packages[packnum].raidnumentries[raidline].prevpositions;
//DeadCode JIM 20Oct00 					RDialog::m_pView->ScreenXY(positions,px,py,-RDialog::m_pView->m_scrollpoint.x,-RDialog::m_pView->m_scrollpoint.y);

					if (Todays_Packages[packnum].attackmethod<Profile::AM_LWPACKS)
					{	//Refresh lolipops
 						IconDescUI	biglolypop(ICON_SQUAREPADDLE);
//DeadCode JIM 20Oct00 						int	squads=Todays_Packages[packnum].squadlist;
						ICONWH.x+=biglolypop.WH().x/2;
						py-=ICONWH.y/2;
						InvalidateRect(CRect(px-ICONWH.x/2,py-biglolypop.WH().y,px+ICONWH.x/2+1,py));
					}
					else
					{	//Refresh arrows
 						if (Save_Data.mapfilters[FILT_LWARROWS])
							InvalidateRect(CRect(px-ARROW_FIXX-ARROW_RAD-1,py+ARROW_FIXY-ARROW_RAD-1,px-ARROW_FIXX+ARROW_RAD+1,py+ARROW_FIXY+ARROW_RAD+1));
					}


				}

		}
		default:;
		}
	}
}
void	CMapDlg::InvalidateIcon(int px,int py,IconsUI i)
{
		CPoint iconsize=IconDescUI(i).WH();
		int dx=iconsize.x/2,dy=iconsize.y/2;
		InvalidateRect(CRect(px-dx-1,py-dy-1,px+dx+1,py+dy+1));
}
void	CMapDlg::InvalidateDragIcon(int ox,int oy,int px,int py,IconsUI i)
{	//waypoint is somewhere in there...
		px=min(ox,px);
		py=min(oy,py);
		ox=max(ox,px);
		oy=max(oy,py);
		CPoint iconsize=IconDescUI(i).WH();
		int dx=iconsize.x/2,dy=iconsize.y/2;
		InvalidateRect(CRect(px-dx,py-dy,ox+dx,oy+dy));
}
void	CMapDlg::InvalidateIconText(CDC* pDC,int px,int py,UniqueID u)
{
	CString s=GetTargName(u,true);
	CSize size=pDC->GetTextExtent(s);
	IconsUI i =IconsUI( RDialog::m_pView->DrawIconTest( NULL, u, false,true));
	if (i)
	{
		CPoint iconsize=IconDescUI(i).WH();
		int dx=iconsize.x/2,dy=iconsize.y/2;
		if (dx>15)
			InvalidateRect(CRect(px-dx,py+dy,px-dx+size.cx,py+dy+1+size.cy+2));
		else
			InvalidateRect(CRect(px,py-dy+1,px+dx+1+size.cx,py-dy+1+size.cy+2));
	}
}
//////////////////////////////////////////////////////////////////////
//
// Function:    InsideIcon
// Date:		15/12/99
// Author:		JIM
//
//Description: 	Tests for inside icon. Part of MapDlg class, but put with draw code.
//
//////////////////////////////////////////////////////////////////////
bool	CMapDlg::InsideIcon(IconsUI i,ItemBasePtr p,CPoint mousexy)
{
	int sx,sy;
	RDialog::m_pView->ScreenXY(p,sx,sy);
	CPoint iconsize=IconDescUI(i).WH();
	int dx=iconsize.x/2,dy=iconsize.y/2;
	if  (mousexy.x>sx-dx && mousexy.x<sx+dx && mousexy.y>sy-dy && mousexy.y<sy+dy)
		return true;
	return	InsideIconExtra(i,p,mousexy);
}
bool	CMapDlg::InsideIconExtra(IconsUI i,ItemBasePtr p,CPoint mousexy)
{
	return false;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    Zoom
// Date:		21/01/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void CMIGView::Zoom(CPoint screenpoint,bool redrawscalebar)
{
	CPoint prevscroll=m_scrollpoint;
	if (m_zoom<ZOOMMIN) m_zoom=ZOOMMIN;
	if (m_zoom>ZOOMMAX) m_zoom=ZOOMMAX;
//DEADCODE ROD 16/12/99 	if	(m_zoom>ZOOMTHRESHOLD2)
//DEADCODE ROD 16/12/99 		m_iconradius=12;
//DEADCODE ROD 16/12/99 	else 
//DEADCODE ROD 16/12/99 		m_iconradius=3;

	if (m_zoom<ZOOMTHRESHOLD3)
		{
			Float newzoom=0.25;
			Float oldzoom=m_zoom;//*1.3;
			while (oldzoom>0.45)
			{
				newzoom*=2;
				oldzoom/=2;
			}
//TEMPCODE AMM 13/01/00 			if (m_zoom!=newzoom)
//TEMPCODE AMM 13/01/00 				TRACE("Zoom reset: %f --> %f",m_zoom,newzoom);
			m_zoom=newzoom;
		}
//DeadCode RDH 30Mar99 	m_scrollpoint += screenpoint;
//DeadCode RDH 30Mar99 	m_scrollpoint = CPoint(m_scrollpoint.x*(m_zoom/m_oldzoom),m_scrollpoint.y*(m_zoom/m_oldzoom));
//DeadCode RDH 30Mar99 	m_scrollpoint -= screenpoint;
//DeadCode RDH 30Mar99 	m_size.cx=m_size.cx*(m_zoom/m_oldzoom);
//DeadCode RDH 30Mar99 	m_size.cy=m_size.cy*(m_zoom/m_oldzoom);


	CRect rect;
	GetClientRect(rect);

	float oldsizecy = m_size.cy;
	float oldsizecx = m_size.cx;
//TEMPCODE JIM 29/05/99 	float oldsizecx = m_size.cx;
////TEMPCODE DAW 08/05/99 	m_size.cx=m_size.cx*(m_zoom/m_oldzoom);
////TEMPCODE DAW 08/05/99 	m_size.cy=m_size.cy*(m_zoom/m_oldzoom);
	m_size.cx=256*4*m_zoom-5;
	m_size.cy=256*4*m_zoom-5;

	if (rect.bottom>m_size.cy&&rect.bottom>m_size.cy)
	{//min zoom for full screen map
		double m_zoom1 = m_oldzoom * rect.bottom/oldsizecy;
		double m_zoom2 = m_oldzoom * rect.right/oldsizecx;
		if (m_zoom1>m_zoom2)
			m_zoom1=m_zoom2;
		m_zoom1*=0.5;
		while (m_zoom<m_zoom1)
			m_zoom*=2;

////TEMPCODE DAW 08/05/99 		m_size.cx= oldsizecx*(m_zoom/m_oldzoom);
////TEMPCODE DAW 08/05/99 		m_size.cy= oldsizecy*(m_zoom/m_oldzoom);
		m_size.cx=256*4*m_zoom-5;
		m_size.cy=256*4*m_zoom-5;

	}

	m_scrollpoint += screenpoint;
	m_scrollpoint = CPoint(m_scrollpoint.x*(m_zoom/m_oldzoom),m_scrollpoint.y*(m_zoom/m_oldzoom));
	m_scrollpoint -= screenpoint;
	if (m_oldzoom!=m_zoom || prevscroll!=m_scrollpoint)
	{
		m_oldzoom=m_zoom;												  //JIM 29/05/99

		m_mapdlg.Invalidate();
		if (redrawscalebar)				//deafult true
			m_pScaleBar->RedrawWindow();
	}
	UpdateScrollbars();
}

void CMIGView::PlotFrontLine(CDC* pDC)
{
//DEADCODE JIM 16/11/99 	ItemBasePtr pt;
//DEADCODE JIM 16/11/99 	int px,py;
//DEADCODE JIM 16/11/99 	
//DEADCODE JIM 16/11/99 	CPen pen (PS_SOLID,4,RGB(252,156,12));
//DEADCODE JIM 16/11/99 	CPen* oldpen=pDC->SelectObject(&pen);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	pt=Persons2::ConvertPtrUID(UniqueID(SupplyTree::WestRoute.frontline->forward->suppliee->associated_item));
//DEADCODE JIM 16/11/99 	if (pt)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		ScreenXY(pt->World.X,pt->World.Z,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 		pDC->MoveTo(px,py);
//DEADCODE JIM 16/11/99 		pt=Persons2::ConvertPtrUID(UniqueID(SupplyTree::CentralRoute.frontline->forward->suppliee->associated_item));
//DEADCODE JIM 16/11/99 		if (pt)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			ScreenXY(pt->World.X,pt->World.Z,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 			pDC->LineTo(px,py);
//DEADCODE JIM 16/11/99 			pt=Persons2::ConvertPtrUID(UniqueID(SupplyTree::EastRoute.frontline->forward->suppliee->associated_item));
//DEADCODE JIM 16/11/99 			if (pt)
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				ScreenXY(pt->World.X,pt->World.Z,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 				pDC->LineTo(px,py);
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 		}
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	}
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	pDC->SelectObject(oldpen);
}
//////////////////////////////////////////////////////////////////////
//
// Function:    PlotRoute
// Date:		25/01/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void CMIGView::PlotMainRoute(CDC* pDC, int pack,bool drawhilight,UniqueID onlythrough)
{
	UniqueID start=Todays_Packages[pack].route;
	if (start)
	{
		int targ=ENABLE_COMPLEX_VAL;	//Main route:	//No targets
		int	squadline=-1;								//No squads
		info_waypoint* wp=*Persons2::ConvertPtrUID(start);
		start=wp->NextWP(squadline,targ); 
		wp=*Persons2::ConvertPtrUID(start);
		CPen pen (PS_SOLID,2,drawhilight?RGB(255,255,255):RGB(160,160,160));
		CPen* oldpen=NULL;
		if (pDC)
			oldpen=pDC->SelectObject(&pen);
		UniqueID nextwp=wp->NextWP(squadline,targ);
		while (nextwp)
		{
			if (!onlythrough || start==onlythrough || nextwp==onlythrough)
				PlotLine(pDC,start,nextwp);
			info_waypoint* wp=*Persons2::ConvertPtrUID(nextwp);
			start=nextwp;
			nextwp=wp->NextWP(squadline,targ);
		}
		if (pDC && oldpen)
			pDC->SelectObject(oldpen);
	}	
}
void CMIGView::PlotTakeOffRoute(CDC* pDC, int pack,int squadline, bool drawhilight,UniqueID onlythrough)
{
	if (squadline && Todays_Packages[pack][squadline].squadnum==Todays_Packages[pack][squadline-1].squadnum && !drawhilight)
		return;
	UniqueID start=Todays_Packages[pack].route;
	if (start)
	{
		int targ=ENABLE_COMPLEX_VAL;						//No targets
		info_waypoint* wp=*Persons2::ConvertPtrUID(start);	//Specific squad
		start=Todays_Packages[pack][squadline].takeoffwp; 
		wp=*Persons2::ConvertPtrUID(start);
		CPen pen (PS_SOLID,1,drawhilight?RGB(255,255,255):RGB(160,160,160));
		CPen* oldpen=NULL;
		if (pDC)
			oldpen=pDC->SelectObject(&pen);
		UniqueID nextwp=wp->NextWP(squadline,targ);
		//Draw take-off route
		while (nextwp && wp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			wp=*Persons2::ConvertPtrUID(nextwp);
			if (	wp->uid.Evaluate()==-SGR_WPP_BombRendezvous
				&&	Todays_Packages[pack][squadline].method>=Profile::AM_DETACHED	)
				if (Todays_Packages[pack][squadline].method<Profile::AM_RETURNESCORT)
				{	//Skip to escort RV
					UniqueID escwp=wp->NextWP(squadline,targ),
							nwp2=escwp;
					if (escwp)
					do{
						nwp2=escwp;
						wp=*Persons2::ConvertPtrUID(escwp);
						escwp=wp->NextWP(squadline,targ);
					}while (escwp && wp->uid.Evaluate()==ENABLE_COMPLEX_VAL);
					if (escwp && wp->uid.Evaluate()==-SGR_WPP_EscRendezvous)
						nextwp=nwp2;
				}
				else
				{
					do{
						nextwp=wp->NextWP(squadline,targ);
						wp=Persons2::ConvertPtrUID(nextwp);
					}while (	wp->uid.Evaluate()!=-SGR_WPP_EscDisperse
							&&	wp->uid.Evaluate()!=-SGR_WPP_BombDisperse);
				}
			if (!onlythrough || start==onlythrough || nextwp==onlythrough)
				PlotLine(pDC,start,nextwp);
			start=nextwp;
			nextwp=wp->NextWP(squadline,targ);
		}
		//Find landing route
		while (nextwp && wp->uid.Evaluate()!=-SGR_WPP_EscDisperse && wp->uid.Evaluate()!=-SGR_WPP_BombDisperse)
		{
			start=nextwp;
			wp=*Persons2::ConvertPtrUID(nextwp);
			nextwp=wp->NextWP(squadline,targ);
		}
		UniqueID escstart=start;
		if (wp->uid.Evaluate()==-SGR_WPP_EscDisperse)
			while (nextwp && wp->uid.Evaluate()!=-SGR_WPP_BombDisperse)
			{
				start=nextwp;
				wp=*Persons2::ConvertPtrUID(nextwp);
				nextwp=wp->NextWP(squadline,targ);
			}
		if (nextwp==UID_NULL)
		{
			start=escstart;
			nextwp=escstart;
		}
		else
		if (	Todays_Packages[pack][squadline].method>=Profile::AM_DETACHED
			&&	Todays_Packages[pack][squadline].method<Profile::AM_RETURNESCORT
			)
		{
			nextwp=start;
			start=escstart;
		}
		else
			nextwp=start;
		//Draw landing route
		wp=*Persons2::ConvertPtrUID(nextwp);
		nextwp=wp->NextWP(squadline,targ);
		while (nextwp)
		{
			if (!onlythrough || start==onlythrough || nextwp==onlythrough)
				PlotLine(pDC,start,nextwp);
			wp=*Persons2::ConvertPtrUID(nextwp);
			start=nextwp;
			nextwp=wp->NextWP(squadline,targ);
		}
		if (pDC && oldpen)
			pDC->SelectObject(oldpen);
	}	

}
void CMIGView::PlotTargetRoute(CDC* pDC, int pack,int target, bool drawhilight,UniqueID onlythrough)
{
	UniqueID start=Todays_Packages[pack].route;
	if (start)
	{
		CPen pen (PS_SOLID,1,drawhilight?RGB(255,255,255):RGB(160,160,160));
		CPen* oldpen=NULL;
		if (pDC)
			oldpen=pDC->SelectObject(&pen);

		int targ=target;					//specific target
		int	squadline=ENABLE_COMPLEX_VAL;	//no squads
		info_waypoint*	wp=*Persons2::ConvertPtrUID(start);
		UniqueID nextwp=wp->NextWP(squadline,targ);
		//Find target area
		while (nextwp && wp->uid.Evaluate()!=-SGR_WPP_IP)
		{
			start=nextwp;
			wp=*Persons2::ConvertPtrUID(nextwp);
			nextwp=wp->NextWP(squadline,targ);
		}
		wp=*Persons2::ConvertPtrUID(nextwp);
		while (nextwp && wp->uid.Evaluate()!=-SGR_WPP_Egress)
		{
			if (!onlythrough || start==onlythrough || nextwp==onlythrough)
				PlotLine(pDC,start,nextwp);
			start=nextwp;
			wp=*Persons2::ConvertPtrUID(nextwp);
			nextwp=wp->NextWP(squadline,targ);
		}


		if (pDC && oldpen)
			pDC->SelectObject(oldpen);
	}
}
void	LineBetween(CDC* pDC,int px1,int py1,int px2,int py2)
{
	enum	{MIN_COORD=-5000,MAX_COORD=5000};
	if (px1>MAX_COORD)
		if (px2>MAX_COORD)
			return;
		else
		{
			py1=py2+Float(py1-py2)*(MAX_COORD-px2)/(px1-px2);
			px1=MAX_COORD;
		}
	if (py1>MAX_COORD)
		if (py2>MAX_COORD)
			return;
		else
		{
			px1=px2+Float(px1-px2)*(MAX_COORD-py2)/(py1-py2);
			py1=MAX_COORD;
		}
	if (px1<MIN_COORD)
		if (px2<MIN_COORD)
			return;
		else
		{
			py1=py2+Float(py1-py2)*(MIN_COORD-px2)/(px1-px2);
			px1=MIN_COORD;
		}
	if (py1<MIN_COORD)
		if (py2<MIN_COORD)
			return;
		else
		{
			px1=px2+Float(px1-px2)*(MIN_COORD-py2)/(py1-py2);
			py1=MIN_COORD;
		}
	if (px2>MAX_COORD)
	{
		py2=py1+Float(py2-py1)*(MAX_COORD-px1)/(px2-px1);
		px2=MAX_COORD;
	}
	if (px2<MIN_COORD)
	{
		py2=py1+Float(py2-py1)*(MIN_COORD-px1)/(px2-px1);
		px2=MIN_COORD;
	}
	if (py2>MAX_COORD)
	{
		px2=px1+Float(px2-px1)*(MAX_COORD-py1)/(py2-py1);
		py2=MAX_COORD;
	}
	if (py2<MIN_COORD)
	{
		px2=px1+Float(px2-px1)*(MIN_COORD-py1)/(py2-py1);
		py2=MIN_COORD;
	}
	pDC->MoveTo(CPoint(px1,py1));
	pDC->LineTo(CPoint(px2,py2));
}

void CMIGView::PlotLine(CDC* pDC, UniqueID thiswp,UniqueID nextwp,BOOL japanwp)
{
	if (!pDC) 
		m_mapdlg.InvalidateLine(thiswp,nextwp);	
	else
	{
		int px1,py1,px2,py2;
		ItemBasePtr pt1,pt2;
		pt1=Persons2::ConvertPtrUID(UniqueID(thiswp));
		pt2=Persons2::ConvertPtrUID(UniqueID(nextwp));
		if (!pt1 || !pt2) return;
		if (thiswp<WayPointBANDEND && nextwp<WayPointBANDEND)
		{
			//if both ends are known and neither end has draw or hilight then return

			info_base::VisibilityCondition tvc=info_waypointPtr(pt1)->GetVC(info_base::VCS_AFTER);
			info_base::VisibilityCondition nvc=info_waypointPtr(pt2)->GetVC(info_base::VCS_BEFORE);
			if (tvc&nvc& info_base::VC_KNOWN)
				if (((tvc|nvc)&info_base::VC_DRAWMASK)==info_base::VC_NODRAW)
					return;
			//copy draw to lastdraw
		}

		ScreenXY(pt1,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
		ScreenXY(pt2,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
		LineBetween(pDC,px1,py1,px2,py2);

	}
}

//debug details that can be drawn on map:
#ifndef	NDEBUG
//DEADCODE DAW 29/01/00 void CMIGView::PlotMainRoute(CDC* pDC, SupplyLine* SL, int red, int green, int blue)
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	CPen pen (PS_SOLID,8,RGB(red,green,blue));
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	CPen  pen00(PS_SOLID,1,RGB(255,255,255)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen01(PS_SOLID,1,RGB(255,100,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen02(PS_SOLID,2,RGB(255,100,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen03(PS_SOLID,3,RGB(255,100,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen04(PS_SOLID,4,RGB(255,100,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen05(PS_SOLID,5,RGB(255,100,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen06(PS_SOLID,6,RGB(255,100,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen07(PS_SOLID,7,RGB(255,100,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen11(PS_SOLID,1,RGB(100,255,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen12(PS_SOLID,2,RGB(100,255,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen13(PS_SOLID,3,RGB(100,255,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen14(PS_SOLID,4,RGB(100,255,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen15(PS_SOLID,5,RGB(100,255,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen16(PS_SOLID,6,RGB(100,255,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen17(PS_SOLID,7,RGB(100,255,100)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen21(PS_SOLID,1,RGB(100,100,255)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen22(PS_SOLID,2,RGB(100,100,255)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen23(PS_SOLID,3,RGB(100,100,255)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen24(PS_SOLID,4,RGB(100,100,255)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen25(PS_SOLID,5,RGB(100,100,255)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen26(PS_SOLID,6,RGB(100,100,255)),
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  pen27(PS_SOLID,7,RGB(100,100,255));
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		  CPen* penlist[3][7]=
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			{
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				{&pen01,&pen02,&pen03,&pen04,&pen05,&pen06,&pen07},
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				{&pen11,&pen12,&pen13,&pen14,&pen15,&pen16,&pen17},
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				{&pen21,&pen22,&pen23,&pen24,&pen25,&pen26,&pen27},
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			};
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	CPen* oldpen=pDC->SelectObject(&pen);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	SupplyNode*  currnode = SL->firstnode;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	SupplyRoute*  currroute;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	ItemBasePtr pt1,pt2;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	int px1,py1,px2,py2,px3,py3;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	pt1=Persons2::ConvertPtrUID(UniqueID(SL->firstnode->associated_item));
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	pDC->MoveTo(px1,py1);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	int count = 0;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	while (			(count < 80)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				&&	(currnode->forward != NULL)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //or should this be new ?
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 // no comments so I cannot tell
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 // commented out version crashes on entry to the map
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //Old_Code DAW 26Nov98 	while (			(count < 80)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //Old_Code DAW 26Nov98 				&&	(currnode->forward->suppliee != NULL)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //Old_Code DAW 26Nov98 			)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	{
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		currroute = currnode->forward;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		pt2=Persons2::ConvertPtrUID(UniqueID(currroute->suppliee->associated_item));
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		pDC->LineTo(px2,py2);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		for (int i=0;i<3;i++)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			if (currnode->forward->suppliee->route[i])
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			{
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				int proper=0,good=0,bad=0;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				for (SupplyRoute* sr=currnode->forward->suppliee->route[i];sr;sr=sr->alternateroute)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				{
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 					if (currnode->associated_item==UID_MyBlSeoul)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 						currnode=currnode;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 					if (sr->populateBF || (proper&&sr->associated_brdg))
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 						proper+=sr->maxcapacitysummer;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 					else
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 						if (sr->maxcapacitysummer>80)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 							bad+=sr->maxcapacitysummer;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 						else
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 							if (sr->maxcapacitysummer!=0)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 								good+=1;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				}
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				bad/=80;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				proper/=80;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				pt2=Persons2::ConvertPtrUID(UniqueID(currnode->forward->suppliee->route[i]->supplier->associated_item));
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				ScreenXY(pt2->World.X,pt2->World.Z,px3,py3,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				if (bad)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 					if (proper)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 						pDC->SelectObject(penlist[0][bad+good-1]);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 					else
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 						pDC->SelectObject(penlist[1][bad+good-1]);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				else
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 					if (good)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 						pDC->SelectObject(penlist[2][good-1]);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 					else
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 						pDC->SelectObject(&pen00);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				pDC->LineTo(px3,py3);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				pDC->MoveTo(px2,py2);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 				pDC->SelectObject(&pen);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 			}
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //TEMPCODE JIM 28/06/99 		if (currroute->suppliee->route[0]!=currroute)
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //TEMPCODE JIM 28/06/99 		{
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //TEMPCODE JIM 28/06/99 			pt2=Persons2::ConvertPtrUID(UniqueID(currroute->suppliee->route[0]->supplier->associated_item));
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //TEMPCODE JIM 28/06/99 			ScreenXY(pt2->World.X,pt2->World.Z,px3,py3,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //TEMPCODE JIM 28/06/99 			pDC->LineTo(px3,py3);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //TEMPCODE JIM 28/06/99 			pDC->MoveTo(px2,py2);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 //TEMPCODE JIM 28/06/99 		}
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		currnode = currroute->suppliee;		
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 		count++;
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	}
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 	pDC->SelectObject(oldpen);
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 29/01/00 }
#endif
/*
void CMIGView::PlotAirfields(CDC* pDC)
{
//DeadCode JIM 30Nov99 	CPen pen (PS_SOLID,1,RGB(255,255,255));
//DeadCode JIM 30Nov99 	CPen* oldpen=pDC->SelectObject(&pen);
//DeadCode JIM 30Nov99 
//DeadCode JIM 30Nov99 	ItemBasePtr pt1,pt2;
//DeadCode JIM 30Nov99 	int px1,py1,px2,py2;
//DeadCode JIM 30Nov99 
//DeadCode JIM 30Nov99 	SupplyNode* currnode;
//DeadCode JIM 30Nov99 	currnode = SupplyTree::FirstNode;
//DeadCode JIM 30Nov99 	while (currnode->type != LASTONE)
//DeadCode JIM 30Nov99 	{
//DeadCode JIM 30Nov99 		pt1=Persons2::ConvertPtrUID(UniqueID(currnode->associated_item));
//DeadCode JIM 30Nov99 		ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
//DeadCode JIM 30Nov99 		for (int i = 0; i< 3; i++)
//DeadCode JIM 30Nov99 		{
//DeadCode JIM 30Nov99  			if (m_mapdlg.m_buttonid == currnode->airfield[i])
//DeadCode JIM 30Nov99  			{
//DeadCode JIM 30Nov99  				pDC->MoveTo(px1,py1);
//DeadCode JIM 30Nov99 				if (currnode->airfield[i])
//DeadCode JIM 30Nov99  				{
//DeadCode JIM 30Nov99  					pt2=Persons2::ConvertPtrUID(UniqueID(currnode->airfield[i]));
//DeadCode JIM 30Nov99  					ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
//DeadCode JIM 30Nov99 					pDC->LineTo(px2,py2);
//DeadCode JIM 30Nov99  				}
//DeadCode JIM 30Nov99  			}
//DeadCode JIM 30Nov99 
//DeadCode JIM 30Nov99 		
//DeadCode JIM 30Nov99 		currnode = currnode->next;
//DeadCode JIM 30Nov99 	};
//DeadCode JIM 30Nov99 
//DeadCode JIM 30Nov99 
//DeadCode JIM 30Nov99 
//DeadCode JIM 30Nov99 	pDC->SelectObject(oldpen);
//DeadCode JIM 30Nov99 
}

*/
#ifndef	NDEBUG
void CMIGView::PlotAirfields(CDC* pDC)
{
	CPen pen (PS_SOLID,1,RGB(255,255,255));
	CPen* oldpen=pDC->SelectObject(&pen);
	UByte	pr=100,pg=0,pb=0;
	for (int i=0;Node_Data.sectorlist[i].uid;i++)
	{
		CPen pen2 (PS_SOLID,1,RGB(pr,pg,pb));
		pr+=1;pg+=10;pb+=100;
		pDC->SelectObject(&pen2);
		TargetFighterField* ff=&Node_Data.sectorlist[i];
		ItemBasePtr p;
		int px,py;
		p=Persons2::ConvertPtrUID(ff->uid);
		ScreenXY(p,px,py);
		pDC->MoveTo(px,py);
		while (ff->satelitelist)
		{
			UniqueID u2=ff->satelitelist;
			ff=Node_Data[u2];
			p=Persons2::ConvertPtrUID(u2);
			ScreenXY(p,px,py);
			pDC->LineTo(px,py);
		}
		pDC->SelectObject(&pen);
	}

	for (i=1;Node_Data.gruppe[i].squadron;i++)
	{
		CPen pen2 (PS_SOLID,1,RGB(pr,pg,pb));
		pDC->SelectObject(&pen2);
		if (Node_Data.gruppe[i].wadernum==Node_Data.gruppe[i-1].wadernum)
		{
			ItemBasePtr p;
			int px,py;
			p=Persons2::ConvertPtrUID(Node_Data.gruppe[i].homeairfield);
			ScreenXY(p,px,py);
			pDC->MoveTo(px,py);
			p=Persons2::ConvertPtrUID(Node_Data.gruppe[i-1].homeairfield);
			ScreenXY(p,px,py);
			pDC->LineTo(px,py);
			


		}
		else
		{
			pr+=1;pg+=10;pb+=100;
		}
		pDC->SelectObject(&pen);
	}
	pDC->SelectObject(oldpen);

//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	ItemBasePtr pt1,pt2;
//DEADCODE JIM 16/11/99 	int px1,py1,px2,py2;
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 		SWord i = 0;
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	while (SupplyTree::airfieldinfo[i].nationality != NAT_ALIGN)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99  			if (m_mapdlg.m_buttonid == SupplyTree::airfieldinfo[i].airfield)
//DEADCODE JIM 16/11/99  			{
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 				CPen pen (PS_SOLID,3,RGB(0,0,255));
//DEADCODE JIM 16/11/99 				CPen* oldpen=pDC->SelectObject(&pen);
//DEADCODE JIM 16/11/99 				
//DEADCODE JIM 16/11/99 				pt1=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].airfield));
//DEADCODE JIM 16/11/99 				ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 	
//DEADCODE JIM 16/11/99 				pDC->MoveTo(px1,py1);
//DEADCODE JIM 16/11/99 				pt2=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].northnodes[0]->associated_item));
//DEADCODE JIM 16/11/99 				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 				pDC->LineTo(px2,py2);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 				pDC->MoveTo(px1,py1);
//DEADCODE JIM 16/11/99 				pt2=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].northnodes[1]->associated_item));
//DEADCODE JIM 16/11/99 				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 				pDC->LineTo(px2,py2);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 				CPen pen2 (PS_SOLID,3,RGB(255,0,0));
//DEADCODE JIM 16/11/99 				pDC->SelectObject(&pen2);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 				pDC->MoveTo(px1,py1);
//DEADCODE JIM 16/11/99 				pt2=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].southnodes[0]->associated_item));
//DEADCODE JIM 16/11/99 				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 				pDC->LineTo(px2,py2);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 				pDC->MoveTo(px1,py1);
//DEADCODE JIM 16/11/99 				pt2=Persons2::ConvertPtrUID(UniqueID(SupplyTree::airfieldinfo[i].southnodes[1]->associated_item));
//DEADCODE JIM 16/11/99 				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 				pDC->LineTo(px2,py2);
//DEADCODE JIM 16/11/99 				pDC->SelectObject(oldpen);
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 			i++;
//DEADCODE JIM 16/11/99 			
//DEADCODE JIM 16/11/99 	};
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	
//DEADCODE JIM 16/11/99 
}


void CMIGView::PlotSupplyingRoutes(CDC* pDC)
{
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	ItemBasePtr pt1,pt2;
//DEADCODE JIM 16/11/99 	int px1,py1,px2,py2;
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	CPen	pen (PS_SOLID,1,RGB(255,0,0));
//DEADCODE JIM 16/11/99 	CPen* oldpen;
//DEADCODE JIM 16/11/99 	;
//DEADCODE JIM 16/11/99 	oldpen=pDC->SelectObject(&pen);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 	SupplyNode* currnode;
//DEADCODE JIM 16/11/99 	currnode = SupplyTree::FirstNode;
//DEADCODE JIM 16/11/99 	while (currnode->type != LASTONE)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		pt1=Persons2::ConvertPtrUID(UniqueID(currnode->associated_item));
//DEADCODE JIM 16/11/99 		ScreenXY(pt1->World.X,pt1->World.Z,px1,py1,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 		for (int i = 0; i< 3; i++)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			if (currnode->supplyline == &SupplyTree::WestRoute)
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			{
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 				CPen pen (PS_SOLID,1,RGB(255,0,0));
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 				oldpen=pDC->SelectObject(&pen);
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			}
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			if (currnode->supplyline == &SupplyTree::CentralRoute)
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			{
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 				CPen pen (PS_SOLID,1,RGB(0,255,0));
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 				oldpen=pDC->SelectObject(&pen);
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			}
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			if (currnode->supplyline == &SupplyTree::EastRoute)
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			{
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 				CPen pen (PS_SOLID,1,RGB(0,0,255));
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 				oldpen=pDC->SelectObject(&pen);
//DEADCODE JIM 16/11/99 //DEADCODE DAW 14/05/99 			}
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 			pDC->MoveTo(px1,py1);
//DEADCODE JIM 16/11/99 			if (currnode->route[i])
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				pt2=Persons2::ConvertPtrUID(UniqueID(currnode->route[i]->supplier->associated_item));
//DEADCODE JIM 16/11/99 				ScreenXY(pt2->World.X,pt2->World.Z,px2,py2,-m_scrollpoint.x,-m_scrollpoint.y);
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 			if (currnode->supplyline == &SupplyTree::WestRoute)
//DEADCODE JIM 16/11/99 				pDC->LineTo(px2,py2);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 		}
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 		
//DEADCODE JIM 16/11/99 		
//DEADCODE JIM 16/11/99 		currnode = currnode->next;
//DEADCODE JIM 16/11/99 	};
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99    pDC->SelectObject(oldpen);
//DEADCODE JIM 16/11/99 
//DEADCODE JIM 16/11/99  
//DEADCODE JIM 16/11/99 
}
#endif
#ifndef NDEBUG
void	PlotInvalidateBoxes(CDC*	pDC)
{
	for (int pennum=0;pennum<debugboxmem.lastline;pennum++)
	{
		CPen pen(PS_SOLID,1,COLORREF(debugboxmem.debuglineRGB[pennum&7]));
//DeadCode JIM 20Oct00 		bool	gotone=false;
		debugboxmem.debuglineRGB[pennum&7]+=0x1000;
		CPen* oldpen=pDC->SelectObject(&pen);
		for (int box=0;box<debugboxmem.lastbox;box++)
			if (debugboxmem.boxmem[box].linenum==pennum)
			{
				pDC->MoveTo(debugboxmem.boxmem[box].sx,debugboxmem.boxmem[box].sy);
				pDC->LineTo(debugboxmem.boxmem[box].ex,debugboxmem.boxmem[box].ey);
				pDC->LineTo(debugboxmem.boxmem[box].ex,debugboxmem.boxmem[box].sy);
				pDC->LineTo(debugboxmem.boxmem[box].sx,debugboxmem.boxmem[box].sy);
				pDC->LineTo(debugboxmem.boxmem[box].sx,debugboxmem.boxmem[box].ey);
				pDC->LineTo(debugboxmem.boxmem[box].ex,debugboxmem.boxmem[box].ey);
			}
		pDC->SelectObject(oldpen);
	}
	debugboxmem.lastline=0;
	debugboxmem.lastbox=0;
}
#endif

void CMIGView::PlotDebugInfo(CDC* pDC)
{
#ifndef NDEBUG
//TempCode DAW 22Jun99 	PlotMainRoute(pDC, &SupplyTree::WestRoute,255,0,0);
//TempCode DAW 22Jun99 	PlotMainRoute(pDC, &SupplyTree::CentralRoute,0,255,0);
//TempCode DAW 22Jun99 	PlotMainRoute(pDC, &SupplyTree::EastRoute,0,0,255);
//TEMPCODE RDH 17/03/00 	PlotAirfields(pDC);
//	PlotSupplyingRoutes(pDC);
// 	PlotInvalidateBoxes(pDC);
#endif
}

void CMIGView::InvalidateRoute(int	pack,bool iconsaswell,bool squadsaswell)
{
	Todays_Packages.SetVisibilityFlags();
	if (!m_currentpage && Todays_Packages.RouteAtAllVisible(pack))
	{
		PlotMainRoute(NULL,pack,false,UID_NULL);
		for (int group=0,maxgroup=Todays_Packages[pack].squadlist;group<maxgroup;group++)
			PlotTakeOffRoute(NULL, pack,  group, false,UID_NULL);
		for (int t=-2;t<0;t++)
			PlotTargetRoute(NULL, pack,  t, false,UID_NULL);
		for (;Todays_Packages[pack].packagetarget[t];t++)
			PlotTargetRoute(NULL, pack,  t, false,UID_NULL);
		if (iconsaswell)
		{
			UniqueID r=Todays_Packages[pack].route;
			while (r)
			{
				info_waypointPtr w=Persons2::ConvertPtrUID(r);
				m_mapdlg.InvalidateIcon(w);
				if (r==m_mapdlg.m_hintid)
				{
					int	px,py;
					CDC* pDC=GetDC();
					ScreenXY(w,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
					m_mapdlg.InvalidateIconText(pDC,px,py,r);
				}
				r=w->nextwp;
			}
		}
		if (squadsaswell && Todays_Packages[pack][0].instance)
		{
			for (int s=0,m=Todays_Packages[pack].squadlist;s<m;s++)
			{
				UniqueID r=Todays_Packages[pack][s].instance;
				ItemBasePtr w=Persons2::ConvertPtrUID(r);
				m_mapdlg.InvalidateIcon(w);
				if (r==m_mapdlg.m_hintid)
				{
					int	px,py;
					CDC* pDC=GetDC();
					ScreenXY(w,px,py,-m_scrollpoint.x,-m_scrollpoint.y);
					m_mapdlg.InvalidateIconText(pDC,px,py,r);
				}

			}


		}
	}
}


void CMIGView::PlotRoutes(CDC* pDC,UniqueID onlythrough)
{

	for (int pack=0;pack<Profile::MAX_PACKS;pack++)
	{
		if (Todays_Packages.RouteAtAllVisible(pack))
		{
			int hipacktarg=-999;
			if (Todays_Packages.hipack != pack)
				PlotMainRoute(pDC,pack,false,onlythrough);
			else
				if (Todays_Packages[Todays_Packages.hipack].squadlist>Todays_Packages.hisquad)
					hipacktarg=Todays_Packages[pack][Todays_Packages.hisquad].WaveNum();

			for (int group=0,maxgroup=Todays_Packages[pack].squadlist;group<maxgroup;group++)
			{
				if  (		(Todays_Packages.hisquad != group)
						||	(Todays_Packages.hipack != pack)
						)
					PlotTakeOffRoute(pDC, pack,  group, false,onlythrough);
			}
			if ((Save_Data.mapfilters[FILT_LWTARGETLINES]))
			for (int t=-2;t<Profile::MAX_TARGETS;t++)
			{	//-2 is est pt and target item //-1 is patrol area 
				if  ((t!=hipacktarg))
					PlotTargetRoute(pDC, pack,  t, false,onlythrough);
			}
		}
	}
	if (Todays_Packages.RouteAtAllVisible(Todays_Packages.hipack))
	{
		PlotMainRoute(pDC, Todays_Packages.hipack, true,onlythrough);
		PlotTakeOffRoute(pDC, Todays_Packages.hipack, Todays_Packages.hisquad, true,onlythrough);
		PlotTargetRoute(pDC, Todays_Packages.hipack, Todays_Packages[Todays_Packages.hipack][Todays_Packages.hisquad].WaveNum(), true,onlythrough);
	}
//DeadCode RDH 16Mar100 		PlotTargetRoute(pDC, Todays_Packages.hipack, Todays_Packages[Todays_Packages.hipack][Todays_Packages.hisquad].WaveNum(), true,onlythrough);

}
#define NEWICONSYSTEM	  XX
#ifndef NEWICONSYSTEM
#define	TFILENUM	FileNum
#define	FIL(name)		FIL_##name
#define	I_NULL			FIL_NULL
#define	SETFILE(name)		filenum=FIL_##name,hifilenum=FIL_##name##_OFF2
#define	SETFILEOLD(name)		filenum=FIL_##name,hifilenum=FIL_##name##_OFF2
#define	SETFILENEW(name)
#define	SETFILE_ON(name)	filenum=FIL_##name##_ON,hifilenum=FIL_##name##_OFF2
#define	SETFILE_ONOLD(name)	filenum=FIL_##name##_ON,hifilenum=FIL_##name##_OFF2
#else
#define	TFILENUM	IconsUI
#define	FIL(name)	name
#define	I_NULL		ICON_NO_ICON
#define	SETFILE(name)		filenum=name;
#define	SETFILE_ON(name)	filenum=name;
#define	SETFILEOLD(name)
#define	SETFILE_ONOLD(name)
#define	SETFILENEW(name)	filenum=name;
#endif

//////////////////////////////////////////////////////////////////////
//
// Function:    SetVisibilityFlags
// Date:		30/05/00
// Author:		JIM
//
//Description:	Generates visible flags for aircraft and waypoints in 1 pass
//				This allows the usual package based searching to be bypassed
//
// Waypoints have AFTER and BEFORE visible flags
// For Icons: If either flag is set inside one wp then it is drawn/refreshed
// For Lines: If the 1st wp's AFTER is set or the 2nd wp's BEFORE is set then draw/refresh
//
//
// First, clear draw flags for all waypoints and aircraft
//
// For each Pack
//		For each squad
//			If that item is visible set DRAWN
//		For each waypoint
//			If that item is visible set DRAWN
//
// When refreshing,
//		For routes, 
//			if both waypoints flag refresh 
//				invalidateline
//				if either was flagged drawn set then set that one's drawlast
//				if both flagged drawn clear then clear both drawlast
//		For aircraft
//			if flag refresh 
//				invalidateline
//				set drawlast
//
// When drawing
//		if flagged to draw then draw
//////////////////////////////////////////////////////////////////////
void	PackageList::AllVisibilityUpdated()
{
	{for (int i=WayPointBAND;i<WayPointBANDEND;i++)
	{
		info_waypointPtr wp=*Persons2::ConvertPtrUID(UniqueID(i));
		if (wp)
		{
			wp->UpdateDrawLast(wp->VCS_BEFORE);
			wp->UpdateDrawLast(wp->VCS_AFTER);
		}
	}}
	{for (int i=SagBAND;i<SagBANDEND;i++)
	{
		info_airgrpPtr ag=*Persons2::ConvertPtrUID(UniqueID(i));
		if (ag)
			ag->UpdateDrawLast();
	}}


}

bool	PackageList::RouteAtAllVisible(int p)
{	//a selection of the flags and tests used in the routine below!
	bool canseepackac,drawwps=false;
	if (	pack[p].packagestatus!=Profile::PS_SPARE
		&&	pack[p].packagestatus!=Profile::PS_COMPLETE	)
	{
		bool	isRAF=(pack[p].attackmethod<Profile::AM_LWPACKS);
		bool	needdetection=	isRAF!=(localplayer==NAT_RAF);
		if (isRAF)
			canseepackac=Save_Data.mapfilters[FILT_RAFSAG];
		else
			canseepackac=Save_Data.mapfilters[FILT_LWSAG];
		if (canseepackac)
		{
			if ((pack[p].attackmethod&Profile::AM_GROUPMASK)==Profile::AM_RAF)
				if (pack[p].attackmethod==Profile::AM_PATROL)
					drawwps=Save_Data.mapfilters[FILT_RAFPATROLS];
				else
					drawwps=Save_Data.mapfilters[FILT_RAFINTERCEPTS];
			else
				if (pack[p].attackmethod==Profile::AM_RECON)
					drawwps=Save_Data.mapfilters[FILT_RECONN];
				else
					drawwps=Save_Data.mapfilters[FILT_BOMBERS];
			if (p==hipack && !needdetection)
				drawwps=true;
		}
	}
	return drawwps;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    CheckHilightValid
// Date:		24/09/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	PackageList::CheckHilightValid()
{
	if (hipack==-1)
		return false;
	if (pack[hipack].packagestatus==Profile::PS_SPARE)
	{
		hipack=-1;
		hisquad=0;
		hiwp=UID_NULL;
		return true;
	}
	if (pack[hipack].squadlist.Max()<=hisquad)
	{
		hisquad=0;
		hiwp=UID_NULL;
		return true;
	}
	if (hisquad && pack[hipack][hisquad].instance==UID_NULL)
	{
		hisquad=0;
		hiwp=UID_NULL;
		return true;
	}


	if (hiwp)
		if (Persons2::ConvertPtrUID(hiwp)==NULL)
		{
			hiwp=UID_NULL;
			return true;
		}

	return false;
}
void	PackageList::SetVisibilityFlags()
{
	{for (int i=WayPointBAND;i<WayPointBANDEND;i++)
	{
		info_waypointPtr wp=*Persons2::ConvertPtrUID(UniqueID(i));
		if (wp)
		{
			wp->ClearDraw(wp->VCS_BEFORE);
			wp->ClearDraw(wp->VCS_AFTER);
			wp->ClearDraw(wp->VCS_ICON);
			wp->SetKnown(wp->VCS_BEFORE);
			wp->SetKnown(wp->VCS_AFTER);
			wp->SetKnown(wp->VCS_ICON);
		}
	}}
	{for (int i=SagBAND;i<SagBANDEND;i++)
	{
		info_airgrpPtr ag=*Persons2::ConvertPtrUID(UniqueID(i));
		if (ag)
		{
			ag->ClearDraw();
			ag->SetKnown();
		}
	}}
	{for (int p=0;p<Profile::MAX_PACKS;p++)
		if (	Todays_Packages[p].packagestatus!=Profile::PS_SPARE
			&&	Todays_Packages[p].packagestatus!=Profile::PS_COMPLETE	)
		{
			//Need to decide on display rules for this package:
			// get rule flags for this package for waypoints and aircraft

			int r=0,max=Todays_Packages[p].squadlist;
			//Each raid has different detect rules...
			while(Todays_Packages[p].raidnumentries[r].squadliststart<max)
				r++;
			bool	isRAF=(Todays_Packages[p].attackmethod<Profile::AM_LWPACKS);
			bool	needdetection=	isRAF!=(Todays_Packages.localplayer==NAT_RAF);

			int		compareindex=FIELDOFFSET(Squadron,squadron.value);
			if (!isRAF && Save_Data.lwplots==PL_GESH)
					compareindex=FIELDOFFSET(Gruppen,wadernum);
			UByte	comparevalue;

			bool canseepackac;
			if (isRAF)
				canseepackac=Save_Data.mapfilters[FILT_RAFSAG];
			else
				canseepackac=Save_Data.mapfilters[FILT_LWSAG];
			if (canseepackac)
				while (--r>=0)					 
					if (!needdetection ||Todays_Packages[p].raidnumentries[r].detector)
					{	//None drawn if raid not visible
						int s=Todays_Packages[p].RaidNumEntriesMinSq(r);
						Profile::Squad* sl=&Todays_Packages[p][s];
//DeadCode JIM 25Sep00 						int	max=Todays_Packages[p].RaidNumEntriesMaxSq(r)+1;
						int	totalac=0;
						while (!sl->playercansee || sl->status==Profile::PS_COMPLETE)
						{
							if (sl->status!=Profile::PS_COMPLETE)
								totalac+=sl->numacleft;
							else
								totalac-=10000;
							sl++;
							s++;
							if (s>=max)
							{
								assert(totalac<0 || (!needdetection && totalac==0));
								break;
							}
						};
						if (s<max)
						{
							s++;
							info_airgrpPtr ac=*Persons2::ConvertPtrUID(sl->instance);
							ac->SetDraw();	//Leader of raid set is always flagged
							if (Save_Data.lwplots>PL_RAID)		//PL_RAID level: only leader is flagged
								if (Save_Data.lwplots<PL_STAFF)
								{								//PL_GRUPP or PL_GESH level - offset already set up
									if (isRAF)
										comparevalue=UByteP(&Node_Data.squadron[sl->squadnum-SQ_BR_START-1])[compareindex];
									else
										comparevalue=UByteP(&Node_Data.gruppe[sl->squadnum-SQ_LW_START-1])[compareindex];
									bool alreadyseen=true;
									for (;s<max;s++)
										{	//Ok... so I detected it. Next question: is it the right detail level?
											Profile::Squad* sl=&Todays_Packages[p][s];
											UByte squadtest;
											if (isRAF)
												squadtest=UByteP(&Node_Data.squadron[sl->squadnum-SQ_BR_START-1])[compareindex];
											else
												squadtest=UByteP(&Node_Data.gruppe[sl->squadnum-SQ_LW_START-1])[compareindex];
											if (squadtest!=comparevalue)
												alreadyseen=false;
											if (!alreadyseen && sl->playercansee && sl->status!=Profile::PS_COMPLETE)
											{
												alreadyseen=true;
												info_airgrpPtr ac=*Persons2::ConvertPtrUID(sl->instance);
												ac->SetDraw();
												comparevalue=squadtest;
											}
										}
								}
								else	//PL_STAFF level - all flagged - no checks (no post)
								{
									for (int s=Todays_Packages[p].raidnumentries[r].squadliststart+1;s<max;s++)
									{
										Profile::Squad* sl=&Todays_Packages[p][s];
										if (sl->playercansee && sl->status!=Profile::PS_COMPLETE)
										{
											info_airgrpPtr ac=*Persons2::ConvertPtrUID(sl->instance);
											ac->SetDraw();
										}
									}

								}
						}
						max=Todays_Packages[p].raidnumentries[r].squadliststart;	//MS 26Sep00
					}
			//now do waypoints
			//There are different flags depending on side
			//But it is all to do with which packages are viewed.
//DEADCODE DAW 02/06/00 			if (isRAF)
			limitscope
			{
//DeadCode JIM 20Oct00 				UniqueID uwp=Todays_Packages[p].route;
				bool drawwps=false;
				if ((Todays_Packages[p].attackmethod&Profile::AM_GROUPMASK)==Profile::AM_RAF)
					if (Todays_Packages[p].attackmethod==Profile::AM_PATROL)
						drawwps=Save_Data.mapfilters[FILT_RAFPATROLS];
					else
						drawwps=Save_Data.mapfilters[FILT_RAFINTERCEPTS];
				else
					if (Todays_Packages[p].attackmethod==Profile::AM_RECON)
						drawwps=Save_Data.mapfilters[FILT_RECONN];
					else
						drawwps=Save_Data.mapfilters[FILT_BOMBERS];

				bool forcedrawselected=false;
				int	checkplayersquadline=ENABLE_COMPLEX_VAL;
				int	checkplayertargetindex=ENABLE_COMPLEX_VAL;
				if (p==Todays_Packages.hipack && Todays_Packages.hisquad!=-1 && !needdetection)
				{
					checkplayersquadline=Todays_Packages.hisquad;
					checkplayertargetindex=Todays_Packages[Todays_Packages.hipack][Todays_Packages.hisquad].targetindex;
					if (!drawwps)
					{//if set drawwps here then all player squad's routes will get drawn
						forcedrawselected=true;
					}
				}
				if (drawwps || forcedrawselected)
				{	//Take-off waypoints
					info_waypointPtr wp=*Persons2::ConvertPtrUID(Todays_Packages[p].route);
					int		lastwave=ENABLE_COMPLEX_VAL;
					
					//wp points to first takeoff wp.
					if (drawwps)
					for (;wp;wp=*Persons2::ConvertPtrUID(wp->nextwp))
					{	//flag all waypoints on take-off route
						if (wp->applygroup!=ENABLE_COMPLEX_VAL)
						{
							if (lastwave!=wp->applygroup)
								lastwave=wp->applygroup;
							else
								if (lastwave==checkplayersquadline)
									wp->SetHilight(wp->VCS_BEFORE);
								else
									wp->SetDraw(wp->VCS_BEFORE);

							if (lastwave==checkplayersquadline)
								wp->SetHilight(wp->VCS_AFTER);
							else
								wp->SetDraw(wp->VCS_AFTER);
						}
						else
							break;
					}
					else	//only flag checkplayersquadline
					for (;wp;wp=*Persons2::ConvertPtrUID(wp->nextwp))
					{	//flag all waypoints on take-off route
						if (wp->applygroup!=ENABLE_COMPLEX_VAL)
						{
							if (wp->applygroup==checkplayersquadline)
							{
								if (lastwave!=wp->applygroup)
									lastwave=wp->applygroup;
								else
									wp->SetHilight(wp->VCS_BEFORE);
								wp->SetHilight(wp->VCS_AFTER);
							}
						}
						else
							break;
					}

					//wp points to bomber RV.
					//fill to escort rv, but only flag AFTER

					bool	gotdoubledisperse=true;
					if (wp->uid!=-SGR_WPP_EscRendezvous)
						if (	checkplayersquadline!=ENABLE_COMPLEX_VAL && 
								(Todays_Packages[p][checkplayersquadline].method&Profile::AM_GROUPMASK)==Profile::AM_LWPACKS
							)
						{	//flag up to fighter RV as hilighted
							do{
								wp->SetHilight(wp->VCS_AFTER);
								wp=*Persons2::ConvertPtrUID(wp->nextwp);
//DEADCODE DAW 02/06/00 								wp->SetHilight(wp->VCS_BEFORE);
							}while (wp->uid!=-SGR_WPP_EscRendezvous);
						}
						elseif (drawwps)
						{	//flag up to fighter RV as draw
							do{
								wp->SetDraw(wp->VCS_AFTER);
								wp=*Persons2::ConvertPtrUID(wp->nextwp);
//DEADCODE DAW 02/06/00 								wp->SetDraw(wp->VCS_BEFORE);
							}while (wp->uid!=-SGR_WPP_EscRendezvous);

						}
						else
						{	//skip up to fighter RV
							do{
								wp=*Persons2::ConvertPtrUID(wp->nextwp);
							}while (wp->uid!=-SGR_WPP_EscRendezvous);

						}
					else
						gotdoubledisperse=false;

					//do up to intercept as hilight or draw
					if (checkplayersquadline!=ENABLE_COMPLEX_VAL)
						do{
							wp->SetHilight(wp->VCS_AFTER);
							wp=*Persons2::ConvertPtrUID(wp->nextwp);
							wp->SetHilight(wp->VCS_BEFORE);
						}while (wp->uid!=-SGR_WPP_IP);
					else
						do{
							wp->SetDraw(wp->VCS_AFTER);
							wp=*Persons2::ConvertPtrUID(wp->nextwp);
							wp->SetDraw(wp->VCS_BEFORE);
						}while (wp->uid!=-SGR_WPP_IP);
					//do target area
					//wp points to IP
					wp=*Persons2::ConvertPtrUID(wp->nextwp);
					//wp points to first target area waypoint

					if (drawwps || Save_Data.mapfilters[FILT_LWTARGETLINES])
						for (;wp;wp=*Persons2::ConvertPtrUID(wp->nextwp))
						{	//flag all waypoints on target route
							if (wp->applywave!=ENABLE_COMPLEX_VAL)
							{
								if (wp->applywave!=-2||wp->uid!=-SGR_WPP_Target)
									if (wp->applywave==checkplayertargetindex)
									{
										wp->SetHilight(wp->VCS_AFTER);
										wp->SetHilight(wp->VCS_BEFORE);
									}
									else
									{
										wp->SetDraw(wp->VCS_AFTER);
										wp->SetDraw(wp->VCS_BEFORE);
									}
							}
							else
								break;
						}
					else	//only flag checkplayersquadline
						for (;wp;wp=*Persons2::ConvertPtrUID(wp->nextwp))
						{	//flag all waypoints on target route
							if (wp->applywave!=ENABLE_COMPLEX_VAL)
							{
								if (wp->applywave==checkplayertargetindex)
								{
									wp->SetHilight(wp->VCS_BEFORE);
									wp->SetHilight(wp->VCS_AFTER);
								}
							}
							else
								break;
						}
					//Now on egress
					//do up to BUT NOT INCLUDING disperse 1
					wp->SetHilight(wp->VCS_AFTER);
					wp=*Persons2::ConvertPtrUID(wp->nextwp);
					//Now on wp after egress
			
					if (checkplayersquadline!=ENABLE_COMPLEX_VAL)
						while (wp->wpact!=wpdisperseno)
						{
							wp->SetHilight(wp->VCS_AFTER);
							wp->SetHilight(wp->VCS_BEFORE);
							wp=*Persons2::ConvertPtrUID(wp->nextwp);
						}
					else
						while (wp->wpact!=wpdisperseno)
						{
							wp->SetDraw(wp->VCS_AFTER);
							wp->SetDraw(wp->VCS_BEFORE);
							wp=*Persons2::ConvertPtrUID(wp->nextwp);
						}

					//Make fighter disperse visible even though it is not attached to a waypoint as such
					if (	(	checkplayersquadline!=ENABLE_COMPLEX_VAL && 
								(Todays_Packages[p][checkplayersquadline].method&Profile::AM_GROUPMASK)==Profile::AM_LWPACKS
							)
						||	drawwps
						)
						wp->SetDraw(wp->VCS_ICON);

					//wp points to disperse1
					//ok.. now 3-way (hi/draw/skip) code to second disperse if any
					//Only flag BEFORE on waypoints after first disperse up to and including second disperse
					if (gotdoubledisperse)
						if (	checkplayersquadline!=ENABLE_COMPLEX_VAL && 
								(Todays_Packages[p][checkplayersquadline].method&Profile::AM_GROUPMASK)==Profile::AM_LWPACKS
							)
						{	//flag up to fighter RV as hilighted
							do{
//DEADCODE DAW 02/06/00 								wp->SetHilight(wp->VCS_AFTER);
								wp=*Persons2::ConvertPtrUID(wp->nextwp);
								wp->SetHilight(wp->VCS_BEFORE);
							}while (wp->wpact!=wpdisperseno);
						}
						elseif (drawwps)
						{	//flag up to fighter RV as draw
							do{
//DEADCODE DAW 02/06/00 								wp->SetDraw(wp->VCS_AFTER);
								wp=*Persons2::ConvertPtrUID(wp->nextwp);
								wp->SetDraw(wp->VCS_BEFORE);
							}while (wp->wpact!=wpdisperseno);

						}
						else
						{	//skip up to fighter RV
							do{
								wp=*Persons2::ConvertPtrUID(wp->nextwp);
							}while (wp->wpact!=wpdisperseno);
						}
					//wp points to disperse2
					wp=*Persons2::ConvertPtrUID(wp->nextwp);
					//wp points to first landing

					//ok.. now do landing. Last wp in each batch must not have AFTER set
					lastwave=ENABLE_COMPLEX_VAL;
//DeadCode JIM 11Aug00 					wp=*Persons2::ConvertPtrUID(wp->nextwp);
					info_waypoint* prevwp=NULL;
					if (drawwps)
						while (wp)
						{

							if (lastwave!=wp->applygroup)
								lastwave=wp->applygroup;
							else
								if (lastwave==checkplayersquadline)
									prevwp->SetHilight(wp->VCS_AFTER);
								else
									prevwp->SetDraw(wp->VCS_AFTER);
							if (lastwave==checkplayersquadline)
								wp->SetHilight(wp->VCS_BEFORE);
							else
								wp->SetDraw(wp->VCS_BEFORE);
							prevwp=wp;
							wp=*Persons2::ConvertPtrUID(wp->nextwp);
						}
					else
						while (wp)
						{
							if (wp->applygroup==checkplayersquadline)
							{
								if (lastwave!=wp->applygroup)
									lastwave=wp->applygroup;
								else
									prevwp->SetHilight(wp->VCS_AFTER);
							wp->SetHilight(wp->VCS_BEFORE);
							}
							prevwp=wp;
							wp=*Persons2::ConvertPtrUID(wp->nextwp);
						}

				}
			}

	}	}

}
int Icon_Select_Add=0;

//////////////////////////////////////////////////////////////////////
//
// Function:    DrawIconTest
// Date:		30/05/00
// Author:		JIM
//
//Description: 	"refresh" means that a successful icon test will result in a refresh of the screen
//				This should occur if the item was visible and now is not visible,
//				And also allows the fact that it was visible to be forgotten
//
//////////////////////////////////////////////////////////////////////
FileNum  CMIGView::DrawIconTest(ItemBasePtr p, UniqueID i, bool hilight,bool refresh)//,UniqueIDField& redUIDs, FileNum* FL_Icon) 
{
	bool	dodrawonsize=true;
	IconsUI	filenum=ICON_NO_ICON;
	if (p==NULL && i!=UID_NULL)										  //JIM 15/12/99
		p=Persons2::ConvertPtrUID(i);								  //JIM 15/12/99
	if (p==NULL)
		dodrawonsize=false;
	else
	{
		if (((info_base*)p)->SGT != UID_Null)
			if (((Item*)p)->shape == EMPTY)
				dodrawonsize=false;
			else
				if (m_zoom < ZOOMTHRESHOLDDETAIL)
					dodrawonsize=false;
	}
	if (dodrawonsize)
	{
		int uidband;
		if (((info_base*)p)->SGT != UID_Null)
			uidband=Persons2::getbandfromUID(((info_base*)p)->SGT);	
		else	
			uidband=Persons2::getbandfromUID(i);

	{
		switch (uidband)
		{
			case		WayPointBAND:
			{
				info_waypoint* wp=*p;//Persons2::ConvertPtrUID(i);
				info_base::VisibilityCondition	
					vc1=wp->GetVC(wp->VCS_ICON);
//DeadCode JIM 3Oct00 				,
//DeadCode JIM 3Oct00 					vc2=wp->GetVC(wp->VCS_AFTER);
				
				if (vc1&wp->VC_KNOWN)	//&vc2
					if (refresh)
						if (((vc1)&wp->VC_REFRESHMASK)!=wp->VC_NODRAW)	 //|vc2
							filenum = ICON_WP;
						else
						{}
					else
						if (((vc1)&wp->VC_DRAWMASK)!=wp->VC_NODRAW)	   //|vc2
							filenum = ICON_WP;
						else
						{}
//DEADCODE DAW 03/06/00 
//DEADCODE DAW 03/06/00 				int pack, wave, g;
//DEADCODE DAW 03/06/00 				//PROBLEM!!! THE TARGET WAYPOINT IS USED BY A NUMBER OF SQUADRONS!!!!
//DEADCODE DAW 03/06/00 				Profile::GetPackageFromWP(i, pack);
//DEADCODE DAW 03/06/00 
//DEADCODE DAW 03/06/00 				if  (		(		(Todays_Packages.hipack == pack)
//DEADCODE DAW 03/06/00 								&&	(	(		(Todays_Packages[Todays_Packages.hipack].attackmethod >= Profile::AM_LWPACKS)
//DEADCODE DAW 03/06/00 											&&	(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//DEADCODE DAW 03/06/00 										)
//DEADCODE DAW 03/06/00 										||
//DEADCODE DAW 03/06/00 										(		(Todays_Packages[Todays_Packages.hipack].attackmethod < Profile::AM_LWPACKS)
//DEADCODE DAW 03/06/00 											&&	(RFullPanelDial::gameside != RFullPanelDial::SIDE_LW)
//DEADCODE DAW 03/06/00 										)
//DEADCODE DAW 03/06/00 									)
//DEADCODE DAW 03/06/00 							)
//DEADCODE DAW 03/06/00 							||
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 							(		(		(Todays_Packages[pack].attackmethod > Profile::AM_INTERCEPT)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 										&&	(Save_Data.mapfilters[FILT_LWROUTELINES])
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 									)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 									||
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 									(	(
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 												(		(Todays_Packages[pack].attackmethod == Profile::AM_PATROL)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 													&&	(Save_Data.mapfilters[FILT_RAFPATROLS])
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 												)	
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 												||
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 												(		(Todays_Packages[pack].attackmethod == Profile::AM_INTERCEPT)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 													&&	(Save_Data.mapfilters[FILT_RAFINTERCEPTS])
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 												)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 											
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 											)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 									)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 									||	(hilight)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 13/03/00 							 )
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 							(		(Save_Data.mapfilters[FILT_ROUTES])
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 								||	(hilight)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 							)
//DEADCODE DAW 03/06/00 							(		(Todays_Packages.localplayer == NAT_RAF)
//DEADCODE DAW 03/06/00 								&&	(	(		(Todays_Packages[pack].attackmethod == Profile::AM_PATROL)
//DEADCODE DAW 03/06/00 											&&	(Save_Data.mapfilters[FILT_RAFPATROLS])
//DEADCODE DAW 03/06/00 										)
//DEADCODE DAW 03/06/00 										||
//DEADCODE DAW 03/06/00 										(		(Todays_Packages[pack].attackmethod == Profile::AM_INTERCEPT)
//DEADCODE DAW 03/06/00 											&&	(Save_Data.mapfilters[FILT_RAFINTERCEPTS])
//DEADCODE DAW 03/06/00 										)
//DEADCODE DAW 03/06/00 
//DEADCODE DAW 03/06/00 									)
//DEADCODE DAW 03/06/00 							)	
//DEADCODE DAW 03/06/00 							||
//DEADCODE DAW 03/06/00 							(		(Todays_Packages.localplayer != NAT_RAF)					
//DEADCODE DAW 03/06/00 								&&	(	(		(Todays_Packages[pack].attackmethod < Profile::AM_DETACHED)
//DEADCODE DAW 03/06/00 											&&	(Save_Data.mapfilters[FILT_BOMBERS])
//DEADCODE DAW 03/06/00 										)	
//DEADCODE DAW 03/06/00 										||
//DEADCODE DAW 03/06/00 										(		(Todays_Packages[pack].attackmethod >= Profile::AM_DETACHED)
//DEADCODE DAW 03/06/00 											&&	(Save_Data.mapfilters[FILT_RECONN])
//DEADCODE DAW 03/06/00 										)
//DEADCODE DAW 03/06/00 									)
//DEADCODE DAW 03/06/00 							)
//DEADCODE DAW 03/06/00 				)
//DEADCODE DAW 03/06/00 
//DEADCODE DAW 03/06/00 				{
//DEADCODE DAW 03/06/00 					info_waypoint* wp=*Persons2::ConvertPtrUID(i);
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 					if  (		(		(Save_Data.mapfilters[FILT_MAINWP])
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 									||	(hilight)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 								)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 							&&	((wp->applygroup==ENABLE_COMPLEX_VAL))
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 						)
//DEADCODE DAW 03/06/00 					if  ((wp->applygroup==ENABLE_COMPLEX_VAL))
//DEADCODE DAW 03/06/00 					{
//DEADCODE DAW 03/06/00 						filenum = ICON_WP;
//DEADCODE DAW 03/06/00 //DEADCODE JIM 16/12/99 						SETFILE(ICON_MAINWP);
//DEADCODE DAW 03/06/00 					}
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 					if  (		(		(Save_Data.mapfilters[FILT_SUBWP])
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 									||	(hilight)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 								)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 							&&	((wp->applygroup!=ENABLE_COMPLEX_VAL))
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 						)
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 					{
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 						filenum = ICON_WP;
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 //DEADCODE JIM 16/12/99 						SETFILE(ICON_SUBWP);
//DEADCODE DAW 03/06/00 //DEADCODE RDH 07/01/00 					}
//DEADCODE DAW 03/06/00 				}
				break;
			}
			case		BarrageBalloonBAND:
			{
				if (Save_Data.mapfilters[FILT_BALLOONZONES])
					filenum = 	ICON_BALLOON;
				break;
			}

			case		BritAAASiteBAND:
			case		BritAAALargeBAND:
			{
				if (Save_Data.mapfilters[FILT_FLAKZONES])
					filenum = ICON_FLAK;
				break;
			}
			case		GermAAASiteBAND:
			{
				if (Save_Data.mapfilters[FILT_FLAKZONES])
					filenum = ICON_FLAK;
				break;
			}
			case		CivilianBAND:
			{
				if (Save_Data.mapfilters[FILT_TOWN])
					filenum = ICON_TOWN;
				break;
			}
			case		BritBridgeBAND:
			{
				filenum=ICON_NO_ICON;									//RDH 06/03/00
				break;
			}
			case		BritHistoricBAND:
			{
				filenum=ICON_NO_ICON;
				break;
			}
			case		GermMobileBAND:
			{
				filenum = ICON_TICK;
				break;
			}
			case		BritMobileBAND:
			{
				filenum = ICON_TICK;
				break;
			}
			case		RunwaySBAND:
			case		RunwayEBAND:
			case	  	NeutMiscBAND:	//backup cc?
			case		SectorOpsBAND:
			{
				filenum=ICON_NO_ICON;									//RDH 06/03/00	//RDH 14/04/00
				break;
			}
			case		BritBoatBAND:
			{
				if (Save_Data.mapfilters[FILT_CONVOYS])
					filenum = ICON_CONVOY;
				break;
			}
			case		GermBoatBAND:
			{
				if (Save_Data.mapfilters[FILT_CONVOYS])
					filenum = ICON_CONVOY;
				break;
			}
			case		PowerStationBAND:
			{
				if (Save_Data.mapfilters[FILT_POWER])
					filenum = ICON_POWER;
				break;
			}
			case		OilRefineryBAND:
			{
				if (Save_Data.mapfilters[FILT_OIL])
					filenum = ICON_OIL;
				break;
			}
			case		IndustryBAND:
			{
				TargetGroup* g=Node_Data[i];
				if (g)
				switch (g->PlayerPriority())
				{
				case Target::TP_LARGERESOURCE:
					if (Save_Data.mapfilters[FILT_POWER])
						filenum = ICON_POWER;
					break;
				case Target::TP_SMALLRESOURCE:
					if (Save_Data.mapfilters[FILT_OIL])
						filenum = ICON_OIL;
					break;
				case Target::TP_INDUSTRY:
					if (Save_Data.mapfilters[FILT_FACTORYOTHER])
						filenum = ICON_TUNNEL;
					break;
				}
				break;
			}
//DeadCode JIM 10Sep00 The above should not interfere with Rod's edits that go below:
			case		AircraftFactoryBAND:
			{
				TargetGroup* g=Node_Data[i];
				if (g)
				switch (g->PlayerType())
				{
					case Target::TT_WELLINGTON:
					case Target::TT_BEAUFIGHTER:
					case Target::TT_DEFIANT:
					case Target::TT_STIRLING:
					case Target::TT_BOMBERPARTS:
					case Target::TT_BOMBERS:
					{
						if (Save_Data.mapfilters[FILT_FACTORYBOMBER])
							filenum = ICON_BOMBER;
						break;
					}

					case Target::TT_CARS:
					case Target::TT_INDUSTRY:
					{
						if (Save_Data.mapfilters[FILT_FACTORYOTHER])
							filenum = ICON_TUNNEL;
						break;
					}
					case Target::TT_UNKNOWNAIRCRAFT:
					case Target::TT_SPITASSEMBLY:
					case Target::TT_HURRASSEMBLY:
					case Target::TT_SPITPARTS:
					case Target::TT_HURRPARTS:
					case Target::TT_ARMAMENTS:
					{
						if (Save_Data.mapfilters[FILT_FACTORYFIGHTER])
							filenum = ICON_FIGHTER;
						break;
					}
				}
				break;
			}
			case		DocksBAND:
			{
				if (Save_Data.mapfilters[FILT_DOCK_CIV])
					filenum = ICON_CIV;
				break;
			}
			case		PortBAND:
			{
				if (Save_Data.mapfilters[FILT_DOCK_CIV])
					filenum = ICON_CIV;
				break;
			}
			case		NavalBaseBAND:
			{
				if (Save_Data.mapfilters[FILT_DOCK_NAVAL])
					filenum = ICON_NAVAL;
				break;
			}
			case		CityBAND:
			{
				if (Save_Data.mapfilters[FILT_CITY])
					filenum = ICON_CITY;
				break;
			}
			case		TownBAND:
			{
				if (Save_Data.mapfilters[FILT_TOWN])
					filenum = ICON_TOWN;
				break;
			}
			case		VillageBAND:
			{
				if (Save_Data.mapfilters[FILT_VILLAGES])
					filenum = ICON_VILLAGE;
				break;
			}
			case		RAF_FighterAFBAND:
			case		RAF_BomberAFBAND:
			case		RAF_CoastalAFBAND:
			{
				TargetGroup* g=Node_Data[i];
				if (g)
				switch (g->PlayerType())
				{
				case Target::TT_FIGHTERAF:
				{
					if (Save_Data.mapfilters[FILT_AF_FIGHTER])
						filenum = ICON_AF_FIGHTER;
					break;
				}
				case Target::TT_BOMBERAF:
				case Target::TT_OTHERAF:
				{
					if (Save_Data.mapfilters[FILT_AF_BOMBER])
						filenum = ICON_AF_BOMBER;
					break;
				}
				case Target::TT_NAVALAF:
				{
					if (Save_Data.mapfilters[FILT_AF_COASTAL])
						filenum = ICON_AF_COASTAL;
					break;
				}
				}

			}
			break;
			case		CLRadarBAND:
			{
				if (Save_Data.mapfilters[FILT_CHL])
					filenum = ICON_CHL;
				break;
			}
			case		CHRadarBAND:
			{
				if (Save_Data.mapfilters[FILT_CH])
					filenum = ICON_CH;
				break;
			}
			case		LUF_FighterLF2BAND:
			{
				if (Save_Data.mapfilters[FILT_AF_FIGHTER])
					filenum = ICON_AF_FIGHTER;
				break;
			}
			case		LUF_FighterLF3BAND:
			{
				if (Save_Data.mapfilters[FILT_AF_FIGHTER])
					filenum = ICON_AF_FIGHTER;
				break;
			}
			case		LUF_BomberLF2BAND:
			{
				if (Save_Data.mapfilters[FILT_AF_BOMBER])
					filenum = ICON_AF_BOMBER;
				break;
			}
			case		LUF_BomberLF3BAND:
			{
				if (Save_Data.mapfilters[FILT_AF_BOMBER])
					filenum = ICON_AF_BOMBER;
				break;
			}
//DEADCODE JIM 12/06/00 			case		TakeOffPosBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		TaxiBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		SectorOpsBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum=ICON_NO_ICON;									//RDH 06/03/00
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		AfHangarBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		AfStaffBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		AfStoresBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		AfFieldBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		AfNoScoreBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		EventBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		RunwaySBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
//DEADCODE JIM 12/06/00 			case		RunwayEBAND:
//DEADCODE JIM 12/06/00 			{
//DEADCODE JIM 12/06/00 				filenum = ICON_TICK;
//DEADCODE JIM 12/06/00 				break;
//DEADCODE JIM 12/06/00 			}
			case		SagBAND:	
			{
				info_itemS* ac=*Persons2::ConvertPtrUID(i);
				if (refresh)
				{
					info_base::VisibilityCondition vc=ac->GetVC();
					ac->UpdateDrawLast();
					if ((vc&ac->VC_REFRESHMASK)==ac->VC_NODRAW)
						break;
				}
				else
					if ((ac->GetVC()&ac->VC_DRAWMASK)==ac->VC_NODRAW)
						break;
				//No need to check the flight positions, now!


				int packnum,sqline;
				if (Todays_Packages.GetACSquadEntry(i,packnum,sqline))
				{
//DEADCODE DAW 03/06/00 					int raidline = Todays_Packages[packnum].GetRaidIndFromSquadEntry(sqline);
//DEADCODE DAW 03/06/00 					int	sqlinemin=Todays_Packages[packnum].RaidNumEntriesMinSq(raidline);
//DEADCODE DAW 03/06/00 					if (		(Todays_Packages[packnum].raidnumentries[raidline].detector)
//DEADCODE DAW 03/06/00 							&&	(		((Todays_Packages[packnum].attackmethod < Profile::AM_LWPACKS)	&&	(Save_Data.mapfilters[FILT_RAFSAG]))
//DEADCODE DAW 03/06/00 									||	((Todays_Packages[packnum].attackmethod >= Profile::AM_LWPACKS)	&&	(Save_Data.mapfilters[FILT_LWSAG]))									
//DEADCODE DAW 03/06/00 								)
//DEADCODE DAW 03/06/00 						)
					{
						if (Save_Data.lwplots == PL_REALISTIC)
						{
	//DEADCODE RDH 14/04/00 						int raidline = Todays_Packages[packnum].GetRaidIndFromSquadEntry(sqline);
	//DEADCODE RDH 14/04/00 						int	sqlinemin=Todays_Packages[packnum].RaidNumEntriesMinSq(raidline);
//DEADCODE DAW 03/06/00  							if (sqline == sqlinemin)
							{
								if (Todays_Packages[packnum].attackmethod>=Profile::AM_LWPACKS)
									filenum = ICON_BIGLW;
								else
									filenum = ICON_BIGRAF;
							}

						}else
						{
 							if (Todays_Packages[packnum].attackmethod==Profile::AM_PATROL)
 								filenum = ICON_RAF_PATROL;
 							else if (Todays_Packages[packnum].attackmethod==Profile::AM_INTERCEPT)
 								filenum = ICON_RAF_INTERECEPT;
 							else 
							{
								{
									if (Todays_Packages[packnum][sqline].method<Profile::AM_DIVEBOMB)
 										filenum = ICON_LW_RECONN;
	 								else if (Todays_Packages[packnum][sqline].method<Profile::AM_DETACHED)
 										filenum = ICON_LW_BOMBER;
 									else
 										filenum = ICON_LW_FIGHTER;

								}
							}
							if (!Todays_Packages[packnum][sqline].squaddetected)
								filenum = IconsUI(filenum+ICON_SELECT_2);
							else
								if (Todays_Packages[packnum][sqline].status>=Profile::PS_OUTGOING)
									filenum = IconsUI(filenum+ICON_SELECT_1);
						}
					}
				}
				break;
			}
			case		NavigationBAND:
			{
				if (Save_Data.mapfilters[FILT_LIGHTHOUSES])
					filenum = ICON_LIGHTHOUSE;
				break;
			}
			default:
			{
#ifndef NDEBUG
				filenum = ICON_TICK;
#endif
				break;
			}
		}
		if	(filenum != I_NULL)								//DAW 20Jun99 //RDH 05/01/00
		{
			TargetGroup* g=Node_Data[i];
			if (g)
				if (g->PlayerStatus()<Target::TS_MAXIMUM)
					if (g->PlayerStatus()>Target::TS_LIGHTDAMAGE)
						if (g->PlayerStatus()>Target::TS_NEARLYDESTROYED)
							if (Save_Data.mapfilters[FILT_DESTROYEDITEMS])
								filenum = IconsUI(filenum+ICON_SELECT_2);	
							else
								filenum=I_NULL;
						else
							if (Save_Data.mapfilters[FILT_DAMAGEDITEMS])
								filenum = IconsUI(filenum+ICON_SELECT_1);	
							else
								filenum=I_NULL;
					else
						if (!Save_Data.mapfilters[FILT_OPERATIONALITEMS])
							filenum=I_NULL;
						else
						{}
				else
				{}
			else
				if (!Save_Data.mapfilters[FILT_OPERATIONALITEMS])
					filenum=I_NULL;


		}
//DEADCODE RDH 05/01/00 #ifdef NEWICONSYSTEM
//DeadCode RDH 12Nov100 #pragma warnmsg("Icon select Add")
		if (hilight && filenum)
			filenum=IconsUI(filenum+ICON_SELECT_3);

	}
  }
  return FileNum(filenum);

}


//• DCB_ACCUMULATE Bounding rectangle accumulation is occurring.
//• DCB_RESET Bounding rectangle is empty.
//• DCB_SET Bounding rectangle is not empty.
//• DCB_ENABLE Bounding accumulation is on.
//• DCB_DISABLE
void CMIGView::DrawIcons( CDC* pDC,CRect& bounds)
{	
	ItemBasePtr p;
	int px,py;
	IconsUI  f;
	int rv;
	int	Wx1,Wx2,Wz1,Wz2;
	int	Wxb1,Wxb2,Wzb1,Wzb2;
	int radius=
		WorldXY(Wx1,Wz1,bounds.left,bounds.bottom);
		WorldXY(Wx2,Wz2,bounds.right,bounds.top);
	Wx1-=radius;
	Wx2+=radius;
	Wz1-=radius;
	Wz2+=radius;
	radius+=radius;
	Wxb1=Wx1-radius;
	Wxb2=Wx2+radius;
	Wzb1=Wz1-radius;
	Wzb2=Wz2+radius;
//	m_bDontUpdateBitmaps=TRUE;
	int dontdraw=m_mapdlg.m_buttonid;
	if (m_mapdlg.TargetSelectMode)
		dontdraw=0;
	// should work out what the worldrect is here for quicker referencing...
	for (int i=IllegalSepID;i>=UID_NULL;i--)
	{
		p=Persons2::ConvertPtrUID(UniqueID(i));
		if (p)
			if (p->Status.size>=AIRSTRUCSIZE)
			{
				info_airgrpPtr ag=*p;
				if (Save_Data.lwplots == PL_REALISTIC)
				{
					if (	ag->knownposition.X>Wxb2 || ag->knownposition.X<Wxb1
						||	ag->knownposition.Z>Wzb2 || ag->knownposition.Z<Wzb1
						)
						p=NULL;
				}
				else
					if (	ag->knownposition.X>Wx2 || ag->knownposition.X<Wx1
						||	ag->knownposition.Z>Wz2 || ag->knownposition.Z<Wz1
						)
						p=NULL;
			}
			else
				if (	p->World.X>Wx2 || p->World.X<Wx1
					||	p->World.Z>Wz2 || p->World.Z<Wz1
					)
					p=NULL;
		if (p)
		{
			bool	drawselected=false;
			switch (m_mapdlg.TargetSelectMode)
			{
			case	STM_NORMAL:
			break;
			case	STM_LWAC:
				if (i>=SagBAND&& i<SagBANDEND)
				{
					if (info_airgrpPtr(*p)->package->attackmethod>Profile::AM_LWPACKS)
						drawselected=true;
				}
			break;
			case	STM_RAFAC:
				if (i>=SagBAND&& i<SagBANDEND)
				{
					if (info_airgrpPtr(*p)->package->attackmethod<Profile::AM_LWPACKS)
						drawselected=true;
				}
			break;
			case	STM_GROUND:
				if (i>SagBANDEND)
					drawselected=true;
			break;
			}


			f = (IconsUI)DrawIconTest( p, UniqueID(i), drawselected,false);//,redUIDs,FL_Icon);
		  	if ((f))
			{
				ScreenXY(p,px,py,0,0);
				DrawIcon(pDC,px,py, (IconsUI)f);
				DrawIconExtra(pDC,px,py,IconsUI(f),UniqueID(i), drawselected);
			}
				
		}
	}
	p=Persons2::ConvertPtrUID(UniqueID(m_mapdlg.m_buttonid));
	if (p && !m_mapdlg.TargetSelectMode)
	{
		f = (IconsUI)DrawIconTest(p, UniqueID(m_mapdlg.m_buttonid), true,false);//,redUIDs,FL_Icon);
	  	if ((f))
		{
		 	ScreenXY(p,px,py,0,0);
			DrawIcon(pDC,px,py, (IconsUI)f);
			DrawIconExtra(pDC,px,py,IconsUI(f),UniqueID(m_mapdlg.m_buttonid),true);
		}
	}

}

static FileNum	startfilescales[4]={FIL_MAP512_11,FIL_MAP256_11,FIL_MAP128_11,FIL_MAP64_11};
static void	PalTrans(void* &dataarea,ULong& datasize)
{	//On some cards scaling and clipping cause a different palette mapping from 24 to 16 bit
	//so cause patches of darkening	//Trim to 5 bits per gun
	//As artwork is fixed this will be fine.
	BITMAPINFO* pInfo=(BITMAPINFO*)((char*)dataarea+sizeof(BITMAPFILEHEADER));
	if (pInfo->bmiHeader.biBitCount==8)
		for (int i=pInfo->bmiHeader.biClrUsed?pInfo->bmiHeader.biClrUsed-1:255;i;i--)
			(int&)pInfo->bmiColors[i]=((int&)pInfo->bmiColors[i]&0x00f8f8f8)+0x00040404;



}

void CMIGView::UpdateBitmaps(CDC* pDC,CRect bounds)
{
//	if (m_bDontUpdateBitmaps) return;
	Todays_Packages.SetVisibilityFlags();
	int areax;
	int areay;
	int zoomsquaresize;
	FileNum	startfile;
	const float mzoom=m_zoom;

	if (mzoom>=ZOOMTHRESHOLD3)
	{
		areax=32;
		areay=32; // area of bitmap array
		zoomsquaresize=32*mzoom;	// size of one side of bitmap compensated for zoom
	}
	else if (mzoom>=ZOOMTHRESHOLD2)
	{
		areax=16;
		areay=16;
		zoomsquaresize=64*mzoom;
	}
	else //if (mzoom>ZOOMTHRESHOLD1)
	{
		areax=1;
		areay=1;
		zoomsquaresize=1024*(mzoom+0.00001);	//this plus won't effect the result I hope...
		int filestart=0;
		while (zoomsquaresize>256)
		{
			filestart++;
			areax+=areax;
			areay+=areay;
			zoomsquaresize/=2.0;
		}
		startfile=startfilescales[filestart];
	}
	int startx=m_scrollpoint.x/zoomsquaresize;
	int starty=m_scrollpoint.y/zoomsquaresize;
	const int squaresize=256; // size of one side of bitmap
	CRect rect=bounds;													//DAW 13/03/00
//DEADCODE DAW 13/03/00 	GetClientRect(rect);  // top left is always 0,0
//	CDC* pDC;
//	pDC = m_mapdlg.GetDC();
	HDC hDC;
	hDC = pDC->GetSafeHdc( );  // gets and stores handle of mapdlg DC	
	assert(areax==1 || startx<areax)
	assert(areay==1 || starty<areay)
	int sstartx=max((m_scrollpoint.x+rect.left)/zoomsquaresize,0);
	int sstarty=max((m_scrollpoint.y+rect.top)/zoomsquaresize,0);
	int endx=min((m_scrollpoint.x+rect.right+zoomsquaresize-1)/zoomsquaresize,areax);
	int endy=min((m_scrollpoint.y+rect.bottom+zoomsquaresize-1)/zoomsquaresize,areay);
	BYTE* pData;

	if (mzoom>=ZOOMTHRESHOLD3)
	{
		//make sure all portions are loaded before starting to draw
		int numnotloaded=0;
		{for (int x=sstartx;x<endx;x++)
			for (int y=sstarty;y<endy;y++)
				if (!File_Man.LoadedNumberedFile(m_MapFiles[31-y][x]))
					numnotloaded++;
		}
		if (numnotloaded>4)
		{
			pDC->FillSolidRect(CRect(rect.left,rect.top,rect.right,rect.bottom),
							RGB(127,147,137));//180,200,200));
		}
		{for (int x=sstartx;x<endx;x++)
			for (int y=sstarty;y<endy;y++)
				fileblock(m_MapFiles[31-y][x],NULL);
		}
		for (int x=sstartx;x<endx;x++)
		{
			for (int y=sstarty;y<endy;y++)
			{
				fileblock fb(m_MapFiles[31-y][x]);
				pData=(BYTE*)getdata(fb);
				if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
				{
					// now render it...
					BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
					BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
					pData+=pFile->bfOffBits;
					SetStretchBltMode(hDC,HALFTONE);
					if (mzoom>45)
					{
						int X=((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
							Y=((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
							SQS=zoomsquaresize/2+1,
							sqsp1o2=(squaresize+1)/2;
						StretchDIBits(hDC,X,Y+SQS,
							SQS,SQS,
							0,0,sqsp1o2,sqsp1o2,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
						StretchDIBits(hDC,X+SQS,Y+SQS,
							SQS,SQS,
							squaresize/2,0,sqsp1o2,sqsp1o2,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
						StretchDIBits(hDC,X,Y,
							SQS,SQS,
							0,squaresize/2,sqsp1o2,sqsp1o2,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
						StretchDIBits(hDC,X+SQS,Y,
							SQS,SQS,
							squaresize/2,squaresize/2,sqsp1o2,sqsp1o2,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
					}
					else
					{
						StretchDIBits(hDC,					
							((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
							((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
							zoomsquaresize,zoomsquaresize,
							0,0,squaresize,squaresize,
							pData,pInfo,DIB_RGB_COLORS,SRCCOPY);
					}
				}
				CRect block(
					((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
					((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
					((1+x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
					((1+y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize)
						),inter;
				inter.IntersectRect(block,bounds);
				DrawIcons(pDC,inter);//,redUIDs, FL_Icon);
			}
		}
	}			
	else if (mzoom>=ZOOMTHRESHOLD2)
	{
		//make sure all portions are loaded before starting to draw
		int numnotloaded=0;
		{for (int x=sstartx;x<endx;x++)
			for (int y=sstarty;y<endy;y++)
				if (!File_Man.LoadedNumberedFile(m_MapFiles32[15-y][x]))
					numnotloaded++;
		}
		if (numnotloaded>5)
		{
			pDC->FillSolidRect(CRect(rect.left,rect.top,rect.right,rect.bottom),
							RGB(127,147,137));//180,200,200));
		}
		{for (int x=sstartx;x<endx;x++)
			for (int y=sstarty;y<endy;y++)
				fileblock(m_MapFiles32[15-y][x],PalTrans);
		}

		for (int x=sstartx;x<endx;x++)
		{
			for (int y=sstarty;y<endy;y++)
			{
				fileblock fb(m_MapFiles32[15-y][x],PalTrans);
				pData=(BYTE*)getdata(fb);
				if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
				{
					// now render it...
					BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
					BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
					pData+=pFile->bfOffBits;
					{
						SetDIBitsToDevice(hDC,
							((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
							((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
							zoomsquaresize,zoomsquaresize,
							0,0,0,squaresize,
							pData,pInfo,DIB_RGB_COLORS);
					}
				}
				CRect block(
					((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
					((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
					((1+x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
					((1+y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize)
						),inter;
				inter.IntersectRect(block,bounds);
				DrawIcons(pDC,inter);//,redUIDs, FL_Icon);
			}
		}
	}			
	else 
	{
		if (sstartx<0)	sstartx=0;
		if (sstarty<0)	sstarty=0;
		if (endx>=areax)	endx=areax;
		if (endy>=areay)	endy=areay;
		//make sure all portions are loaded before starting to draw
		int	numnotloaded=0;
		{for (int x=sstartx;x<endx;x++)
			for (int y=sstarty;y<endy;y++)
				if (!File_Man.LoadedNumberedFile(FileNum(startfile+x+areax*(areay-y-1))))
					numnotloaded++;
		}
		if (numnotloaded>5)
		{
			pDC->FillSolidRect(CRect(rect.left,rect.top,rect.right,rect.bottom),
							RGB(127,147,137));//180,200,200));
		}
		{for (int x=sstartx;x<endx;x++)
			for (int y=sstarty;y<endy;y++)
				fileblock(FileNum(startfile+x+areax*(areay-y-1)),PalTrans);
		}
		for (int x=sstartx;x<endx;x++)
		{
			for (int y=sstarty;y<endy;y++)
			{
				fileblock fb(FileNum(startfile+x+areax*(areay-y-1)),PalTrans);
				pData=(BYTE*)getdata(fb);
				if (pData && pData[0]=='B' && pData[1]=='M') // checks if its a bitmap file
				{
					// now render it...
					BITMAPFILEHEADER* pFile=(BITMAPFILEHEADER*)pData;
					BITMAPINFO* pInfo=(BITMAPINFO*)(pData+sizeof(BITMAPFILEHEADER));
					pData+=pFile->bfOffBits;
					SetDIBitsToDevice(hDC,
						((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
						((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
						zoomsquaresize,zoomsquaresize,
						0,0,0,squaresize,
						pData,pInfo,DIB_RGB_COLORS);
				}
				CRect block(
					((x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
					((y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize),
					((1+x-startx)*zoomsquaresize)-(m_scrollpoint.x%zoomsquaresize),
					((1+y-starty)*zoomsquaresize)-(m_scrollpoint.y%zoomsquaresize)
						),inter;
				inter.IntersectRect(block,bounds);
				DrawIcons(pDC,inter);//,redUIDs, FL_Icon);

			}
		}
	}
//	if (rect.right>m_size.cx) 
//		pDC->FillSolidRect(CRect(m_size.cx,0,rect.right,rect.bottom),
//							RGB(63,80,111));
//	if (rect.bottom>m_size.cy)
//		pDC->FillSolidRect(CRect(0,m_size.cy,rect.right,rect.bottom),
//							RGB(63,80,111));
	if (rect.right>m_size.cx) 
		pDC->FillSolidRect(CRect(m_size.cx,0,rect.right,rect.bottom),
							RGB(0,0,0));//180,200,200));
	if (rect.bottom>m_size.cy)
		pDC->FillSolidRect(CRect(0,m_size.cy,rect.right,rect.bottom),
							RGB(0,0,0));//180,200,200));
	// now draw the icons...
//DEADCODE ROD 16/12/99 	UniqueIDField redUIDs;
//DEADCODE JIM 16/11/99 	SupplyTree::FillNatForUID(redUIDs);

//DEADCODE ROD 16/12/99 	FileNum  FL_Icon[100];//AmberBattleNodeBANDEND-AmberBattleNodeBAND]; //RJS 16/11/99
//DEADCODE JIM 16/11/99 	if (m_zoom > ZOOMTHRESHOLDFRONTLINE)
//DEADCODE JIM 16/11/99 		SupplyTree::FillFLS_Icons(FL_Icon);

//DEADCODE JIM 16/11/99 	if (Save_Data.mapfilters[FILT_FRONTLINE])
//DEADCODE JIM 16/11/99 		PlotFrontLine(pDC);

//DEADCODE DAW 14/03/00 	DrawIcons(pDC,bounds);//,redUIDs, FL_Icon);
	// now plot the routes...
	PlotRoutes(pDC);
	if (m_mapdlg.m_LButtonDown && m_mapdlg.m_bDragging && m_mapdlg.m_buttonid)
		DrawDraggingRoutes(pDC,UniqueID(m_mapdlg.m_buttonid)) ;

	//now the hint
	ItemBasePtr p;
	int px,py;
	p=Persons2::ConvertPtrUID(UniqueID(m_mapdlg.m_hintid));
//DeadCode DAW 05Jun00 	FileNum  f;
//DeadCode DAW 05Jun00 	f = DrawIconTest(p, UniqueID(m_mapdlg.m_hintid), false);//,redUIDs,FL_Icon);
	if (	(p))//	&& (f))										//DAW 05Jun00
	{
		ScreenXY(p,px,py,0,0);
//DeadCode DAW 05Jun00 		pDC->SetBkColor(RGB(255,255,255));
//DeadCode DAW 05Jun00 		pDC->SetTextColor(RGB(0,0,0));
//DeadCode DAW 05Jun00 		int uidband=Persons2::getbandfromUID(UniqueID(m_mapdlg.m_hintid));

//DEADCODE RJS 16/11/99 		if (uidband == AmberBattleNodeBAND)
//DEADCODE RJS 16/11/99 		{
//DEADCODE RJS 16/11/99 			TeamDef		*team=SupplyTree::WestRoute.groundbattle.FindTeamAtLocation(UniqueID(m_mapdlg.m_hintid));
//DEADCODE RJS 16/11/99 			if (!team) 
//DEADCODE RJS 16/11/99 				team=SupplyTree::CentralRoute.groundbattle.FindTeamAtLocation(UniqueID(m_mapdlg.m_hintid));
//DEADCODE RJS 16/11/99 			else if (!team) 
//DEADCODE RJS 16/11/99 				team=SupplyTree::EastRoute.groundbattle.FindTeamAtLocation(UniqueID(m_mapdlg.m_hintid));
//DEADCODE RJS 16/11/99 			if (team)
//DEADCODE RJS 16/11/99 				DrawIconText(pDC,px,py,LoadResString(team->forcename));
//DEADCODE RJS 16/11/99 
//DEADCODE RJS 16/11/99 			
//DEADCODE RJS 16/11/99 		}else
			DrawIconText(pDC,px,py,UniqueID(m_mapdlg.m_hintid), m_mapdlg.m_buttonid==m_mapdlg.m_hintid);
	}

	PlotDebugInfo(pDC);
//DEADCODE JIM 29/05/99 	m_oldzoom=m_zoom;
	m_drawing=FALSE;
}
/*
void CMIGView::DrawLine(CDC * pDC, int uid1, int uid2)
{
	ItemBasePtr pt1,pt2;
	int px,py;
	pt1=Persons2::ConvertPtrUID(UniqueID(uid1);
	pt2=Persons2::ConvertPtrUID(UniqueID(uid2);
	if (pt1 && pt2)
	{
		px=((p->World.X*m_zoom)/65536)
		py=(1792*m_zoom)-((p->World.Z*m_zoom)/65536);
		pDC->


	}
}
*/
void CMIGView::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
/*
	CPoint oldscrollpoint=m_scrollpoint;
	if (nSBCode == SB_LINEDOWN) m_scrollpoint.y +=40;
	if (nSBCode == SB_LINEUP) m_scrollpoint.y -=40;
	if (nSBCode == SB_PAGEDOWN) m_scrollpoint.y += 400;
	if (nSBCode == SB_PAGEUP) m_scrollpoint.y -= 400;
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK) 
	{
		if (m_drawing) return;
		if (m_scrollpoint.y!=nPos)
		{
			m_drawing=TRUE;
			m_scrollpoint.y=nPos;
		}
	}
//	if (nSBCode != SB_THUMBPOSITION && nSBCode != SB_THUMBTRACK) m_mapdlg.Invalidate();
	UpdateScrollbars();
	m_mapdlg.ScrollWindow(oldscrollpoint.x-m_scrollpoint.x,oldscrollpoint.y-m_scrollpoint.y);
*/
}


void CMIGView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
/*	CPoint oldscrollpoint=m_scrollpoint;
	if (nSBCode == SB_LINERIGHT) m_scrollpoint.x +=40;
	if (nSBCode == SB_LINELEFT) m_scrollpoint.x -=40;
	if (nSBCode == SB_PAGERIGHT) m_scrollpoint.x += 400;
	if (nSBCode == SB_PAGELEFT) m_scrollpoint.x -= 400;
	if (nSBCode == SB_THUMBPOSITION || nSBCode == SB_THUMBTRACK)
	{
		if (m_drawing) return;
		if (m_scrollpoint.x!=nPos)
		{
			m_drawing=TRUE;
			m_scrollpoint.x=nPos;
		}
	}
//	if (nSBCode != SB_THUMBPOSITION && nSBCode != SB_THUMBTRACK) m_mapdlg.Invalidate();
	UpdateScrollbars();
	m_mapdlg.ScrollWindow(oldscrollpoint.x-m_scrollpoint.x,oldscrollpoint.y-m_scrollpoint.y);
*/
}

void CMIGView::UpdateScrollbars()
{

	if (!m_mapdlg.m_hWnd) return;
	if (m_currentpage!=0)
	{
		m_rHorzScrollBar.ShowWindow(SW_HIDE);
		m_rVertScrollBar.ShowWindow(SW_HIDE);
/*		SCROLLINFO scrollinfo;
		scrollinfo.cbSize=sizeof(SCROLLINFO);
		scrollinfo.fMask=SIF_ALL;// | SIF_DISABLENOSCROLL; 
		scrollinfo.nMin=0;
		scrollinfo.nMax=0;
		scrollinfo.nPage=0;
		scrollinfo.nPos=0; 
		scrollinfo.nTrackPos=0; 
		SetScrollInfo(SB_HORZ,&scrollinfo,TRUE);
		scrollinfo.nMax=0;
		scrollinfo.nPage=0;
		scrollinfo.nPos=0;
		SetScrollInfo(SB_VERT,&scrollinfo,TRUE);
	*/
	}
	else
	{
		CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
		CRect rect;
		GetClientRect(rect);
		m_scrollpoint.x=min(m_scrollpoint.x,m_size.cx-rect.right);
		m_scrollpoint.x=max(m_scrollpoint.x,0);
		m_scrollpoint.y=min(m_scrollpoint.y,m_size.cy-rect.bottom);
		m_scrollpoint.y=max(m_scrollpoint.y,0);
		int vert=0;
		int horz=0;
		if (rect.right<(int)m_size.cx)
		{
			m_rHorzScrollBar.SetMinValue(0);
			m_rHorzScrollBar.SetMaxValue(m_size.cx-rect.right);
			m_rHorzScrollBar.SetPageSize(rect.right);
			m_rHorzScrollBar.SetScrollPos(m_scrollpoint.x);
			horz=16;
			m_rHorzScrollBar.ShowWindow(SW_SHOW);
			m_rHorzScrollBar.BringWindowToTop();
		}
		else
			m_rHorzScrollBar.ShowWindow(SW_HIDE);
		if (rect.bottom<(int)m_size.cy)
		{
			m_rVertScrollBar.SetMinValue(0);
			m_rVertScrollBar.SetMaxValue(m_size.cy-rect.bottom);
			m_rVertScrollBar.SetPageSize(rect.bottom);
			m_rVertScrollBar.SetScrollPos(m_scrollpoint.y);
			vert=16;
			if (m_rVertScrollBar.IsWindowVisible())
				main=NULL;
			m_rVertScrollBar.ShowWindow(SW_SHOW);
			if (main)
				main->PositionSysBox();
			m_rVertScrollBar.BringWindowToTop();
		}
		else
		{
			if (!m_rVertScrollBar.IsWindowVisible())
				main=NULL;
			m_rVertScrollBar.ShowWindow(SW_HIDE);
			if (main)
				main->PositionSysBox();
		}
		m_mapdlg.MoveWindow(0,0,rect.right-vert,rect.bottom-horz);
		m_rVertScrollBar.MoveWindow(rect.right-CRToolBar::SCROLLBAR_THICKNESS,0,CRToolBar::SCROLLBAR_THICKNESS,rect.bottom-horz);
		m_rHorzScrollBar.MoveWindow(0,rect.bottom-CRToolBar::SCROLLBAR_THICKNESS,rect.right-vert,CRToolBar::SCROLLBAR_THICKNESS);
/*		SCROLLINFO scrollinfo;
		scrollinfo.cbSize=sizeof(SCROLLINFO);
		scrollinfo.fMask=SIF_ALL;// | SIF_DISABLENOSCROLL; 
		scrollinfo.nMin=0;
		scrollinfo.nMax=m_size.cx;
		scrollinfo.nPage=rect.right;
		scrollinfo.nPos=m_scrollpoint.x; 
		scrollinfo.nTrackPos=0; 
		SetScrollInfo(SB_HORZ,&scrollinfo,TRUE);
		scrollinfo.nMax=m_size.cy;
		scrollinfo.nPage=rect.bottom;
		scrollinfo.nPos=m_scrollpoint.y;
		SetScrollInfo(SB_VERT,&scrollinfo,TRUE);
*/
#ifndef	BOB_DEMO_VER
		if (m_thumbnail)
			m_thumbnail->InvalidateMapOnly();
#endif
	}
}

void CMIGView::OnMove(int x, int y) 
{
	CView::OnMove(x, y);
	
//DEADCODE DAW 07/05/99 	// TODO: Add your message handler code here
//DEADCODE DAW 07/05/99 	if (m_doIexist>2)
//DEADCODE DAW 07/05/99 	{
//DEADCODE DAW 07/05/99 		if (m_pfullpane) m_pfullpane->UpdateSize();
//DEADCODE DAW 07/05/99 		if (m_currentpage==0) m_mapdlg.Invalidate();
//DEADCODE DAW 07/05/99 //DeadCode JIM 15Jul98 		UpdateBitmaps();
//DEADCODE DAW 07/05/99 //DeadCode JIM 15Jul98 		if (m_pfullpane) m_pfullpane->UpdateSize();
//DEADCODE DAW 07/05/99 		RecalcLayout();
//DEADCODE DAW 07/05/99 	}
//DEADCODE DAW 07/05/99 //	UpdateScrollbars();
	
}

void CMIGView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	if (m_doIexist>2)
	{
		if (m_pfullpane) m_pfullpane->UpdateSize();
		if (m_currentpage==0) m_mapdlg.Invalidate();
//DeadCode JIM 15Jul98 		UpdateBitmaps();
//DeadCode JIM 15Jul98 		if (m_pfullpane) m_pfullpane->UpdateSize();
	}
	UpdateScrollbars();
	m_doIexist++; // window only exists after it has been initially sized twice.
}

BOOL CMIGView::OnEraseBkgnd(CDC* pDC) 
{
	if (m_currentpage!=0)
//DEADCODE JIM 19/06/99 		if (Rtestsh1::Start3d(Rtestsh1::S3D_DONEBACK))
		{
			CRect rect;
			GetClientRect(rect);
			pDC->FillRect(rect, CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
		}
	return TRUE;
}

//DEADCODE JIM 04/04/00 void CMIGView::OnChangeToTitle() 
//DEADCODE JIM 04/04/00 {
//DEADCODE JIM 04/04/00 	LaunchFullPane(&RFullPanelDial::introsmack);
//DEADCODE JIM 04/04/00 }

void CMIGView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CView::OnLButtonDown(nFlags, point);

}

void CMIGView::OnMouseMove(UINT nFlags, CPoint point) 
{
		CRect rect;
		GetWindowRect(rect);
		m_popupPoint=point-rect.TopLeft();

	CView::OnMouseMove(nFlags, point);
}

void CMIGView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CView::OnLButtonUp(nFlags, point);
}

#ifndef	BOB_DEMO_VER

void CMIGView::LaunchMap(bool firsttime)
{
// Preload Ground Controller and Female Voices here:

	_Miles.GoingToMapScreen();											//RJS 6Oct00

//DeadCode CSB 11Sep00 	Mono_Text.Print(UByteP("LaunchMap<"));

///	Persons4::StartUpMapWorld();		//do whenever we go to the map screen
	m_pfullpane->DestroyWindow();
	m_currentpage=0;
	m_pfullpane=NULL;
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
	main->ShowToolbars(firsttime);
	main->m_reportbar.Refresh(true);
	main->m_titlebar.Redraw();
	m_mapdlg.ShowWindow(SW_SHOW);
	m_mapdlg.BringWindowToTop();
	m_mapdlg.Invalidate();
	UpdateScrollbars();
//DeadCode CSB 11Sep00 	Mono_Text.Print(UByteP(">LaunchMap"));

//DeadCode JIM 15Jul98 	Persons4::StartUpMapWorld();		//do whenever we go to the map screen
//	Persons4::ShutDownMapWorld();		//do whenever we come off the map screen
}

#endif

void CMIGView::LaunchFullPane(FullScreen * startscreen,SaveData::ResUI reqres)
{
//	Persons4::ShutDownMapWorld();		//do whenever we come off the map screen
	m_currentpage=1;					//no.. only if going somewhere nasty.
	CMainFrame* main=(CMainFrame*)AfxGetMainWnd();
#ifndef	BOB_DEMO_VER
//	if (!main->m_bHideToolbars)
		main->HideToolbars();
//	else
//		main->m_wndSystemBox->InDialAncestor()->ShowWindow(SW_HIDE);		  //JIM 14/06/99
	main->CloseToolChildren();
//DEADCODE RDH 09/11/99 	main->m_toolbar1.CloseLoggedChildren();
//DEADCODE RDH 09/11/99 	main->m_toolbar2.CloseLoggedChildren();
//DEADCODE RDH 09/11/99 	main->m_toolbar3.CloseLoggedChildren();
//DEADCODE RDH 09/11/99 	main->m_toolbar4.CloseLoggedChildren();
//	main->m_toolbar5.CloseLoggedChildren();
	m_mapdlg.ShowWindow(SW_HIDE);
#endif
	UpdateScrollbars();
	main->OnGoBig();	//ShowWindow(SW_SHOWMAXIMIZED);
	Save_Data.ChangeMode(reqres);			//SaveDataNoLoad
	m_pfullpane=new RFullPanelDial; // must create it on the heap
	m_pfullpane->LaunchMain(startscreen);
}

void CMIGView::OnScrollHorzScrollbar(long nPos) 
{
	if (m_drawing) return;
	CPoint oldscrollpoint=m_scrollpoint;
	if (m_scrollpoint.x!=nPos)
	{
		m_drawing=TRUE;
		m_scrollpoint.x=nPos;
	}
	UpdateScrollbars();
	m_mapdlg.ScrollWindow(oldscrollpoint.x-m_scrollpoint.x,oldscrollpoint.y-m_scrollpoint.y);
}

void CMIGView::OnScrollVertScrollbar(long nPos) 
{
	if (m_drawing) return;
	CPoint oldscrollpoint=m_scrollpoint;
	if (m_scrollpoint.y!=nPos)
	{
		m_drawing=TRUE;
		m_scrollpoint.y=nPos;
	}
	UpdateScrollbars();
	m_mapdlg.ScrollWindow(oldscrollpoint.x-m_scrollpoint.x,oldscrollpoint.y-m_scrollpoint.y);
}

#define	 DIALCLASS	CMIGView
#pragma warnmsg("Windows message functions:")
#include	"rdialmsg.cpp"
#undef	 DIALCLASS

FileNum  CMIGView::OnGetArt()
{
	return FIL_NULL;
}
long CMIGView::OnGetXYOffset()
{
	return 0;
}

void CMIGView::OnActiveXScroll(int,int)
{
}
void	CMIGView::SetHiLightInfo(int pack, int squadline, UniqueID wp, bool fullgroup)
{	
	bool	needtoredoglobrefs=wp &&(Todays_Packages.hipack!=pack || Todays_Packages.hiwp==UID_NULL);
	Todays_Packages.oldhipack = Todays_Packages.hipack;
	Todays_Packages.oldhisquad = Todays_Packages.hisquad;
	Todays_Packages.hipack = pack;
	Todays_Packages.hisquad = squadline;
	Todays_Packages.hiwp = wp;
	if (needtoredoglobrefs)
	{
		Todays_Packages.pack[pack].SetTargetGlobrefs();
		Todays_Packages.pack[pack].SetGlobRefsForRoute(Todays_Packages.pack[pack].route);

	}
	if(wp != UID_NULL)
		RDialog::m_pView->m_mapdlg.ResetIcon(Todays_Packages.hiwp);



//DEADCODE RDH 07/01/00 	fullgroup|=(Todays_Packages.hipack!=pack);
//DEADCODE RDH 07/01/00 	if (Todays_Packages.hipack!=-1)
//DEADCODE RDH 07/01/00 		if (fullgroup)
//DEADCODE RDH 07/01/00 		{
//DEADCODE RDH 07/01/00 			for (int sq=0,maxsq=Todays_Packages[Todays_Packages.hipack].squadlist;sq!=maxsq;sq++)
//DEADCODE RDH 07/01/00 				PlotRoute(NULL, Todays_Packages.hipack,sq,false);
//DEADCODE RDH 07/01/00 //DEADCODE DAW 26/11/99 			PlotRoute(NULL, Todays_Packages.hipack, Todays_Packages.hiwave, 1, false);
//DEADCODE RDH 07/01/00 //DEADCODE DAW 26/11/99 			PlotRoute(NULL, Todays_Packages.hipack, Todays_Packages.hiwave, 2, false);
//DEADCODE RDH 07/01/00 		}
//DEADCODE RDH 07/01/00 		else
//DEADCODE RDH 07/01/00 			PlotRoute(NULL, Todays_Packages.hipack, Todays_Packages.hisquad, false);
//DEADCODE RDH 07/01/00 	Todays_Packages.hipack = pack;
//DEADCODE RDH 07/01/00 	Todays_Packages.hisquad = squadline;
//DEADCODE RDH 07/01/00 	Todays_Packages.hiwp = wp;
//DEADCODE RDH 07/01/00 	RDialog::m_pView->m_mapdlg.ResetIcon(Todays_Packages.hiwp);
//DEADCODE RDH 07/01/00 
//DEADCODE RDH 07/01/00 	if (fullgroup)
//DEADCODE RDH 07/01/00 	{
//DEADCODE RDH 07/01/00 		for (int sq=0,maxsq=Todays_Packages[pack].squadlist;sq!=maxsq;sq++)
//DEADCODE RDH 07/01/00 				PlotRoute(NULL, pack,sq,false);
//DEADCODE RDH 07/01/00 	}
//DEADCODE RDH 07/01/00 	else
//DEADCODE RDH 07/01/00 		PlotRoute(NULL, pack, squadline,true);

}			  



CScrollBar* CMIGView::GetScrollBarCtrl(int nBar) const
{
	// TODO: Add your specialized code here and/or call the base class
	//CWnd::OnRegisteredMouseWheel
	return CView::GetScrollBarCtrl(nBar);
}

BOOL CMIGView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if (Rtestsh1::Start3d(Rtestsh1::S3D_STOPPED)==Rtestsh1::S3D_GOING)
		return false;
	if (!m_currentpage)
	{
	// TODO: Add your message handler code here and/or call default
//	::AfxTrace("Zoom WHLP(%i,%i)\n", pt.x, pt.y);
//		CRect rect;
//		GetWindowRect(rect);
//		m_popupPoint=pt-rect.TopLeft();

		if (zDelta)
			if (zDelta<0)
				if (m_zoom>=ZOOMTHRESHOLD3)
					if (zDelta<-900)
						m_zoom=m_zoom*0.5;
					else
						m_zoom=m_zoom*(1.0+zDelta/1200.0);
				else
					m_zoom=m_zoom*0.5;
			else
				if (m_zoom>=ZOOMTHRESHOLD3)
					if (zDelta>900)
						m_zoom=m_zoom*2.0;
					else
						m_zoom=m_zoom*(1.0+zDelta/960.0);
				else
					if (m_zoom>=ZOOMTHRESHOLD2)
						m_zoom=ZOOMTHRESHOLD3;
					else
						m_zoom=m_zoom*2.0;

//	::AfxTrace("Zoom WHL (%i,%i)\n", m_popupPoint.x, m_popupPoint.y);
		Zoom(m_popupPoint);
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}



LRESULT CMIGView::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	int rv= CView::DefWindowProc(message, wParam, lParam);
//deadcode JIM 18/06/01		switch (message)
//deadcode JIM 18/06/01		{
//deadcode JIM 18/06/01		case	WM_NCCREATE:			case	WM_PARENTNOTIFY:
//deadcode JIM 18/06/01		case	WM_NCCALCSIZE:			case	0x04c8:	//MCIWNDM_NOTIFY:
//deadcode JIM 18/06/01		case	WM_CREATE:				case	WM_NCPAINT:
//deadcode JIM 18/06/01		case	WM_SIZE:				case	WM_SETCURSOR:
//deadcode JIM 18/06/01		case	WM_MOVE:				case	WM_SETFONT:
//deadcode JIM 18/06/01		case	WM_INITDIALOG:			case	WM_DISPLAYCHANGE:
//deadcode JIM 18/06/01		case	WM_CTLCOLORSTATIC:		case	WM_IDLEUPDATECMDUI: //363
//deadcode JIM 18/06/01		case	WM_GETFONT:				case	WM_KILLFOCUS:
//deadcode JIM 18/06/01		case	WM_WINDOWPOSCHANGING:	case	WM_STYLECHANGING:
//deadcode JIM 18/06/01		case	WM_SHOWWINDOW:			case	WM_STYLECHANGED:
//deadcode JIM 18/06/01		case	WM_PAINT:				case	WM_SETFOCUS:
//deadcode JIM 18/06/01		case	WM_WINDOWPOSCHANGED:	//
//deadcode JIM 18/06/01		case	 WM_NCHITTEST:			//
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01	
//deadcode JIM 18/06/01			return rv;
//deadcode JIM 18/06/01		}
	return rv;
}
