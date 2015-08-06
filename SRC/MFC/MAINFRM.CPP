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

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
//
//	This file manages the toolbars
//

//void CMainFrame::OnBye() 

#include "stdafx.h"
#include "MIG.h"
#undef	HtmlHelp
#undef	HtmlHelpA
#undef	HtmlHelpU
#include	"htmlhelp.h"		//for HTML help


#include "MainFrm.h"
#include <afxpriv.h>
#include "migview.h"
#include "fileman.h"
//TEMPCODE DAW 13/04/00 #include "smack.h"
#include "winmove.h"
#include	"stub3d.h"	//Inst3d
#include	"shapes.h"													//RJS 28Aug00
#include	"miles.h"													//RJS 28Aug00
#include	"rchatter.h"												//RJS 28Aug00
#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef	THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
bool	HELPWASLAUNCHEDRECENTLY=false;

extern CFont* g_AllFonts[MAXFONTS][4];
#ifndef	BOB_DEMO_VER
CRToolBar*	CMainFrame::toolbars[TB_TOTAL]={NULL};
#endif
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_COMMAND(ID_HELP_FINDER, OnHelpFinder)
	ON_COMMAND(ID_CONTEXT_HELP, OnContextHelp)
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_WM_GETMINMAXINFO()
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	ON_WM_DEVMODECHANGE()
	//}}AFX_MSG_MAP
	// Global help commands
//	ON_COMMAND(ID_HELP_FINDER, CFrameWnd::OnHelpFinder)
//	ON_COMMAND(ID_HELP, CFrameWnd::OnHelp)
	ON_COMMAND(ID_CONTEXT_HELP, CFrameWnd::OnContextHelp)
	ON_COMMAND(ID_DEFAULT_HELP, OnHelpFinder)
	ON_MESSAGE( WM_COMMANDHELP,OnCommandHelp)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

//DeadCode RJS 03May100 #if !defined (NDEBUG)
#define NOT_TOPMOST
//DeadCode RJS 03May100 #endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
#ifndef	BOB_DEMO_VER
:	m_reportbar(IntellMessages::Make),
	m_commsbar(RadioComms::Make)
#endif
{
	// TODO: add member initialization code here
	m_doIExist=0;
	m_bHideToolbars=TRUE;
/////	FILEMAN.InitFileSystem();
	havedrawn=havesafe=false;
//DeadCode AMM 7Aug00 	m_oldindebrief=(Bool)2;
}

CMainFrame::~CMainFrame()
{
	for (int i=0;i<MAXFONTS;i++)
	{
		for (int j=0;j<4;j++)
		{
			if (g_AllFonts[i][j]!=NULL)
			{
				delete g_AllFonts[i][j];
			}
		}
	}
	if (RDialog::m_pMessageBox)
		delete RDialog::m_pMessageBox;
	if (RDialog::m_pHintBox)
		delete RDialog::m_pHintBox;
	if (RDialog::m_pListBox)
		delete RDialog::m_pListBox;
///	SmackSetSystemRes(SMACKRESRESET);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

//DeadCode JIM 29Oct00 #if !defined(NOT_TOPMOST)
//DeadCode JIM 29Oct00 	cs.dwExStyle|=WS_EX_TOPMOST;
//DeadCode JIM 29Oct00 #endif

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnBye() 
{
#ifndef	BOB_DEMO_VER
	int rv = RDialog::RMessageBox(IDS_QUITGAME, IDS_AREYOUSURE,IDS_SAVE,IDS_YES,IDS_CANCEL);
	if (rv==0)
	{
		MiscToolBar().OpenSaveOnly(true);

///		else
		return;
	}
	else
	if (rv<2)
	{
		if (RFullPanelDial::incomms)
		{
 			_DPlay.ExitDirectPlay();
		}
//DEADCODE AMM 17/05/99 		m_oldindebrief=FALSE;
// About to quit campaign, so...
// ...Kill shapes, stop sounds
//DeadCode RJS 1Sep00 		SHAPESTUFF.UnLoadRequiredShapes();								//RJS 28Aug00
//DeadCode RJS 1Sep00 		_Miles.KillAll();												//RJS 28Aug00
//DeadCode RJS 1Sep00 		_Radio.Enter3D(false);											//RJS 28Aug00
//DeadCode RJS 1Sep00 
//DeadCode RJS 1Sep00 
//DeadCode RJS 1Sep00 		Todays_Packages.WipeAll();

		ExitCampaign();													//RJS 1Sep00

		RDialog::m_pView->LaunchFullPane(&RFullPanelDial::title);	
	}
#endif
}

void	CMainFrame::ExitCampaign()
{
	SHAPESTUFF.UnLoadRequiredShapes();								//RJS 28Aug00
	_Miles.KillAll();												//RJS 28Aug00
	_Radio.Enter3D(false);											//RJS 28Aug00


	Todays_Packages.WipeAll();
}

void CMainFrame::OnGoSmall() 
{
//	ShowWindow(SW_SHOWMINIMIZED);
	// show/hide toolbars instead...
	if (m_bHideToolbars)
		ShowToolbars(false);
	else
		HideToolbars();
#ifndef	BOB_DEMO_VER
	m_wndSystemBox->InDialAncestor()->ShowWindow(SW_SHOW);
#endif
}

void CMainFrame::OnGoBig() 
{
//TEMPCODE DAW 08/05/99 	if (!IsZoomed())
		ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border
		HELPWASLAUNCHEDRECENTLY=false;
//DeadCode JIM 29Oct00 #if !defined(NOT_TOPMOST)
//DeadCode JIM 29Oct00 				SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DeadCode JIM 29Oct00 #endif
//DeadCode DAW 17Jun99 		ModifyStyleEx(0,WS_EX_TOPMOST);
//DeadCode MS 16Aug00 		MoveWindow(0,0,1050,800);
	ShowWindow(SW_SHOWMAXIMIZED);
//	m_wndSystemBox.GetDlgItem(ID_GONORMAL)->ShowWindow(SW_SHOW);
//	m_wndSystemBox.GetDlgItem(ID_GOBIG)->ShowWindow(SW_HIDE);
}

void CMainFrame::OnGoNormal() 
{
//TEMPCODE DAW 08/05/99 	if (IsZoomed())
		ModifyStyle(NULL,WS_THICKFRAME); // Come back border!
//DeadCode DAW 17Jun99 	ModifyStyleEx(WS_EX_TOPMOST,0);
	ShowWindow(SW_SHOWNORMAL);
//DeadCode JIM 29Oct00 #if !defined(NOT_TOPMOST)
//DeadCode JIM 29Oct00 				SetWindowPos(&wndBottom,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DeadCode JIM 29Oct00 #endif
//	m_wndSystemBox.GetDlgItem(ID_GONORMAL)->ShowWindow(SW_HIDE);
//	m_wndSystemBox.GetDlgItem(ID_GOBIG)->ShowWindow(SW_SHOW);
}

void CMainFrame::Initialise()
{
	CMIGView* view = (CMIGView*)GetActiveView();
		m_doIExist=2;	
		// Init toolbars
//DeadCode JIM 05Jul98 		m_toolbar1.Create(CMainToolbar::IDD,view);
//DeadCode JIM 05Jul98 		CRect rect;
//DeadCode JIM 05Jul98 		m_toolbar1.GetWindowRect(rect);
//DeadCode JIM 05Jul98 		m_toolbar1.Init(this,rect.Width(),rect.Width(),40,AFX_IDW_DOCKBAR_TOP,0);
//DeadCode JIM 05Jul98 		m_toolbar2.Create(CMainToolbar::IDD,view);
//DeadCode JIM 05Jul98 		m_toolbar2.Init(this,rect.Width(),rect.Width(),40,AFX_IDW_DOCKBAR_TOP,0);
//DeadCode JIM 05Jul98 		m_toolbar4.Create(CScaleBar::IDD,view);
//DeadCode JIM 05Jul98 		m_toolbar4.Init(this,200,400,40,AFX_IDW_DOCKBAR_LEFT,4);

		CRect rect;

#ifndef	BOB_DEMO_VER
		m_titlebar.Create(TitleBar::IDD,view);
		m_titlebar.GetWindowRect(rect);
		m_titlebar.Init(this,rect.Width(),rect.Width(),CRToolBar::TOOBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0,CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);

//		m_toolbar1.Create(CMapFilters::IDD,view);
//		m_toolbar1.GetWindowRect(rect);
//		m_toolbar1.Init(this,rect.Width(),rect.Width(),CRToolBar::TOOBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0,CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);

		m_toolbar2.Create(CMainToolbar::IDD,view);
		m_toolbar2.GetWindowRect(rect);
		m_toolbar2.Init(this,rect.Width(),rect.Width(),CRToolBar::TOOBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0,CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
//DEADCODE RDH 08/11/99 		m_toolbar5.Create(CDebriefToolbar::IDD,view);
//DEADCODE RDH 08/11/99 		m_toolbar5.GetWindowRect(rect);
//DEADCODE RDH 08/11/99 		m_toolbar5.Init(this,rect.Width(),rect.Width(),CRToolBar::TOOBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0);
		m_reportbar.Create(m_reportbar.IDD,view);
		m_reportbar.GetWindowRect(rect);
		m_reportbar.Init(this,rect.Width(),rect.Width(),CRToolBar::TOOBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0,CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);

		m_toolbar3.Create(CMiscToolbar::IDD,view);
		m_toolbar3.GetWindowRect(rect);
		m_toolbar3.Init(this,rect.Width(),rect.Width(),CRToolBar::TOOBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0,CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);


//		m_commsbar.Create(m_commsbar.IDD,view);
//		m_commsbar.GetWindowRect(rect);
//		m_commsbar.Init(this,rect.Width(),rect.Width(),CRToolBar::TOOBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0,CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);

//		m_statusbar.Create(m_statusbar.IDD,view);   //m_commsbar
//		m_statusbar.GetWindowRect(rect);
//		m_statusbar.Init(this,rect.Width(),rect.Width(),CRToolBar::TOOBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0,CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);

		m_spacebar.Create(m_spacebar.IDD,view);
		m_spacebar.GetWindowRect(rect);
		m_spacebar.Init(this,1000,1000,CRToolBar::TOPBAR_THICKNESS,AFX_IDW_DOCKBAR_BOTTOM,0,CBRS_ALIGN_BOTTOM);
		m_toolbar4.Create(m_toolbar4.IDD,view);
		m_toolbar4.GetWindowRect(rect);
		m_toolbar4.Init(this,500,500,CRToolBar::SIDEBAR_THICKNESS,AFX_IDW_DOCKBAR_RIGHT,4,CBRS_ALIGN_TOP+CBRS_ALIGN_LEFT+CBRS_ALIGN_RIGHT+CBRS_GRIPPER);

		view->m_pScaleBar=&m_toolbar4;
	//{	TB_FILTERS,TB_MAIN,TB_MISC,TB_TITLE,TB_REPORT,TB_COMMS,TB_STATUS,TB_SCALE,TB_SPACE,TB_TOTAL};

		toolbars[TB_FILTERS]=NULL;//&m_toolbar1;
		toolbars[TB_MAIN]=&m_toolbar2;
		toolbars[TB_MISC]=&m_toolbar3;
		toolbars[TB_TITLE]=&m_titlebar;
		toolbars[TB_REPORT]=&m_reportbar;
		toolbars[TB_COMMS]=NULL;//&m_commsbar;
		toolbars[TB_STATUS]=NULL;//&m_statusbar;
		toolbars[TB_SCALE]=&m_toolbar4;
		toolbars[TB_SPACE]=&m_spacebar;


		typedef	HideEdgeControl	EDGE;
		RDialog::MakeTopDialog(CRect(0,0,CRToolBar::SIDEBAR_THICKNESS,CRToolBar::TOOBAR_THICKNESS),
			DialBox(FIL_NULL,m_wndSystemBox=new CSystemBox(this),Edges(EDGE::OCCLUDE_EXACT+EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)));
		PositionSysBox();

#endif// #ifndef	BOB_DEMO_VER

//		m_wndSystemBox-.Init(CSystemBox::IDD,this);
//		m_wndSystemBox.ShowWindow(SW_SHOW);
		HideToolbars();
		view->LaunchFullPane(&RFullPanelDial::introsmack,SaveData::UIR_FIRST);			  //JIM 18/01/99
		m_doIExist=1;	
}

void	CMainFrame::InitialiseSafe()
{
	havesafe=true;
	if (havedrawn)
		Initialise();
}
void CMainFrame::OnPaint() 
{
//	CDC* pDC=GetWindowDC();
//	CRect windrect;
//	GetWindowRect(windrect);
//	pDC->FillSolidRect(0,0,windrect.Width(),windrect.Height(),RGB(0,0,0));
//DeadCode JIM 20Oct00 	CMIGView* view = (CMIGView*)GetActiveView();
	havedrawn=true;
	if (m_doIExist==0)
	{
		if (havesafe)
			Initialise();

	}
	if (m_doIExist==1)
	{
//DEADCODE JIM 14/06/00 		PositionSysBox();
	}
	PAINTSTRUCT ps;
	::BeginPaint(m_hWnd, &ps);
//	pDC->FillSolidRect(0,0,windrect.Width(),windrect.Height(),RGB(0,0,0));
}

void	CMainFrame::PositionSysBox() 
{
#ifndef	BOB_DEMO_VER
	if (!m_doIExist)
		return;
	if (!m_wndSystemBox)
		return;
	CRect rect;
	GetWindowRect(rect);
	CRect systemrect;

	m_wndSystemBox->InDialAncestor()->GetClientRect(systemrect);
	CRect viewrect;
	CMIGView* view = (CMIGView*)GetActiveView();
	view->GetClientRect(viewrect);
	view->ClientToScreen(viewrect);
	int	bs=(viewrect.top-rect.top)%CRToolBar::BARTHICK_MODULO;
	if (viewrect.top-rect.top+10>systemrect.bottom || view->m_currentpage!=0) // check if there is room for the system box 
		m_wndSystemBox->InDialAncestor()->MoveWindow(CRect(rect.right-systemrect.right-bs,rect.top+bs,rect.right-bs,rect.top+systemrect.bottom+bs));
	else 
	{
		CRect	insidenoscroll	(	viewrect.right-systemrect.right,	rect.top+bs,
									viewrect.right,						rect.top+systemrect.bottom+bs),

				insidescroll	(	viewrect.right-systemrect.right-CRToolBar::SCROLLBAR_THICKNESS,	rect.top+bs,
									viewrect.right-CRToolBar::SCROLLBAR_THICKNESS,					rect.top+systemrect.bottom+bs),

				outsidescroll	(	rect.right-bs-systemrect.right,		rect.top+bs,
									rect.right-bs,						rect.top+systemrect.bottom+bs);
		{


		}
		if (m_top.IsEmpty() && m_right.IsEmpty())
			if (view->m_rVertScrollBar.IsWindowVisible())
				m_wndSystemBox->InDialAncestor()->MoveWindow( insidescroll);
			else
				m_wndSystemBox->InDialAncestor()->MoveWindow( insidenoscroll);
		else
			if (!m_right.IsEmpty() || viewrect.top-rect.top>=systemrect.bottom)
				m_wndSystemBox->InDialAncestor()->MoveWindow(outsidescroll);
			else
				m_wndSystemBox->InDialAncestor()->MoveWindow( insidescroll);

	}
#endif
}

void CMainFrame::HideToolbars()
{
	m_bHideToolbars=TRUE;
#ifndef	BOB_DEMO_VER
//	m_titlebar.ShowWindow(SW_HIDE);
//	m_toolbar1.ShowWindow(SW_HIDE);
//	m_toolbar2.ShowWindow(SW_HIDE);
//	m_toolbar3.ShowWindow(SW_HIDE);
//	m_toolbar4.ShowWindow(SW_HIDE);
//DEADCODE RDH 08/11/99 	m_toolbar5.ShowWindow(SW_HIDE);
	m_spacebar.ShowWindow(SW_HIDE);
	m_wndSystemBox->InDialAncestor()->ShowWindow(SW_HIDE);
	UpdateToolbars(true);
#endif #ifndef	BOB_DEMO_VER
//	RecalcLayout();
}

void CMainFrame::ShowToolbars(bool firsttime)
{
#ifndef	BOB_DEMO_VER
	m_bHideToolbars=FALSE;
//DEADCODE RDH 09/11/99 	m_titlebar.ShowWindow(SW_SHOW);
//DEADCODE RDH 09/11/99 	m_toolbar1.ShowWindow(SW_SHOW);
//DEADCODE RDH 09/11/99 
//DEADCODE RDH 09/11/99 	m_toolbar2.ShowWindow(SW_SHOW);
//DEADCODE RDH 09/11/99 	m_toolbar3.ShowWindow(SW_SHOW);
//DEADCODE RDH 09/11/99 	m_toolbar4.ShowWindow(SW_SHOW);
//DEADCODE RDH 08/11/99 	m_toolbar5.ShowWindow(SW_SHOW);
//DEADCODE RDH 09/11/99 	m_spacebar.ShowWindow(SW_SHOW);
	m_wndSystemBox->InDialAncestor()->ShowWindow(SW_SHOW);
	UpdateToolbars(false);
//DEADCODE RDH 09/11/99 	RecalcLayout();
#endif #ifndef	BOB_DEMO_VER
//	if  (firsttime && (RFullPanelDial::incomms && _DPlay.UIPlayerType==PLAYER_GUEST))
//		m_oldindebrief=TRUE;
//DEADCODE JIM 14/05/99  	if (firsttime)
//DEADCODE JIM 14/05/99  	{
//DEADCODE  14/05/99  		//first time in set this flag to opposite of what we want to ensure we
//DEADCODE  14/05/99  		//get a refresh. 
//DEADCODE  14/05/99  		if  (		(RFullPanelDial::incomms)
//DEADCODE  14/05/99  				&&	(_DPlay.UIPlayerType==PLAYER_GUEST)
//DEADCODE  14/05/99  			)
//DEADCODE  14/05/99  			m_oldindebrief=FALSE;
//DEADCODE  14/05/99  		else
//DEADCODE  14/05/99  			if 	(MMC.indebrief)
//DEADCODE  14/05/99  				m_oldindebrief=FALSE;
//DEADCODE  14/05/99  			else
//DEADCODE  14/05/99  				m_oldindebrief=TRUE;
//DEADCODE  14/05/99 	}
//DEADCODE  14/05/99 */
//DEADCODE JIM 30/03/00 	UpdateToolbars(false);
}

void CMainFrame::RePositionLayout(int dx,int dy) 
{
	RePositionLayout(dx,dy,&m_left);
	RePositionLayout(dx,dy,&m_top);
	RePositionLayout(dx,dy,&m_right);
	RePositionLayout(dx,dy,&m_bottom);
	PositionSysBox();

}
void CMainFrame::RePositionLayout(int dx,int dy,CMainFrame::ToolBarList* toollist)
{
	POSITION position;
	CRToolBar* pToolbar;
	position=toollist->GetHeadPosition();
	int	count=toollist->GetCount();
	for (int y=0;y<count;y++)
	{
		pToolbar=toollist->GetNext(position);
		CRect rect;
 		pToolbar->GetWindowRect(rect);
		pToolbar->MoveWindow(rect+CPoint(dx,dy));
	}
}
void CMainFrame::RecalcLayout(BOOL bNotify) 
{

	// TODO: Add your specialized code here and/or call the base class
	CFrameWnd::RecalcLayout(bNotify); // if this isnt called the frame window doesnt appear at all
#ifndef	BOB_DEMO_VER
	if (!m_hWnd)
		return;
	if (m_doIExist==0) return;
	CMIGView* view = (CMIGView*)GetActiveView();
	if (!view) return; // If the view doesnt exist yet return
	CRect rect2;
	GetClientRect(rect2);
	if (m_bHideToolbars) 
	{
		view->MoveWindow(rect2);
		return;
	}
	// draw the toolbars
	m_borderRect=CRect(0,0,0,0); // keeps track of the width of each edge
	int x;
	int y;
	int count;
	int start;
	int row;
	int total;
	int priority;
	CRToolBar* pToolbar;
	CRToolBar* pPriorityToolbar;
	BOOL foundend;
	POSITION position;
	CRect rect;
	view->GetWindowRect(rect);
	CRect systemrect;

	m_wndSystemBox->GetWindowRect(systemrect);

	// first row on top row is a bit shorter because of system box
	int totalwidth=rect2.Width()-systemrect.Width()+1;
	int totalheight=rect2.Height();
	ClientToScreen(rect2);
	// Start with the top

	position=m_top.GetHeadPosition();
	count=m_top.GetCount();
	start=0;
	row=0;
	total=0;
	priority=0;
	foundend=FALSE;
	for (y=0;y<count;y++)
	{
		pToolbar=m_top.GetNext(position);
		pToolbar->toprow=&CRToolBar::toptoprow;
		pToolbar->m_currentlength=pToolbar->m_minlength;
		total+=pToolbar->m_minlength;
		if (total>totalwidth && start!=y)
		{
			y--;
			foundend=TRUE;
			total-=pToolbar->m_minlength;
		}
		else if (pToolbar->m_priority >= priority)
		{
			priority=pToolbar->m_priority;
			pPriorityToolbar=pToolbar;
		}
		// found a row now draw it
		if (foundend || y==count-1)
		{
			pPriorityToolbar->m_currentlength+=totalwidth-total;
			position=m_top.FindIndex(start);
			total=0;
			for (x=start;x<=y;x++)
			{
				pToolbar=m_top.GetNext(position);
				pToolbar->m_index=x+1;
//				pToolbar->MoveWindow(rect2.left+total,rect2.top+(row*pToolbar->m_width),pToolbar->m_currentlength,pToolbar->m_width);
				pToolbar->SetWindowPos(this,rect2.left+total,rect2.top+(row*pToolbar->m_width),pToolbar->m_currentlength,pToolbar->m_width,SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
				pToolbar->m_row=row;
				total+=pToolbar->m_currentlength;
			}
			// initialise the next row if its there
			m_borderRect.top+=pToolbar->m_width; // assumed all of them are the same width for now...
			if (foundend)
			{
				start=y+1;
				row++;
				totalwidth=rect2.Width();
				total=0;
				foundend=FALSE;
				priority=0;
			}
		}
	}
	totalwidth=rect2.Width();
	// repeat for the other edges
	// probably look nicer doing these 4 things as a very complicated
	// loop but whats the point?  its faster and simpler this way
	// plus its easy to have special conditions for a particular edge

	// next the bottom
	//rewritten this to fix 2 bugs. NOTE: These bugs are still in the other versions!!
	//Bug1) Not handling different height tools.
	//			Still a problem here if diff height tools are on same row.
	//Bug2) Not returning useful row number for artwork positioning.
	position=m_bottom.GetHeadPosition();
	count=m_bottom.GetCount();
	start=0;
	row=count-1;
	total=0;
	priority=0;
	foundend=FALSE;
	int	currbottom=0,worstheight=0;

	struct	RowDesc
	{	int	left,right,priority,height,width;	}
	rowdesc[8];
	
	int	rowindex=0;
	rowdesc[rowindex].left=0;
	rowdesc[rowindex].priority=0;
	rowdesc[rowindex].height=0;
	
	for (y=0;y<=count;y++)
	{
		rowdesc[rowindex].width=total;
		if (y<count)
		{
			pToolbar=m_bottom.GetNext(position);
			pToolbar->m_currentlength=pToolbar->m_minlength;
			total+=pToolbar->m_minlength;
		}
		else
		{
			total=totalwidth+1;
		}
		if ((total>totalwidth && y!=rowdesc[rowindex].left))
		{
			rowdesc[rowindex].right=y-1;
			rowdesc[rowindex].height=worstheight;

			//put this row on next line
			rowindex++;
			if (y<count)
			{
				total=pToolbar->m_minlength;
				priority=pToolbar->m_priority;
				rowdesc[rowindex].priority=y;
				rowdesc[rowindex].left=y;
				worstheight=pToolbar->m_width;
				rowdesc[rowindex].width=total;
			}
		}
		else
			if (y<count)
			{
				if (pToolbar->m_priority >= priority)
				{
					priority=pToolbar->m_priority;
					rowdesc[rowindex].priority=y;
				}
				if (pToolbar->m_width>worstheight)
					worstheight=pToolbar->m_width;
			}
	}

	currbottom=0;
	for (row=0,count=rowindex-1;row<rowindex;row++,count--)
	{	// found a row now draw it
		total=0;
		currbottom+=rowdesc[row].height;
		position=m_bottom.FindIndex(rowdesc[row].priority);
		pToolbar=m_bottom.GetNext(position);
		pToolbar->m_currentlength+=totalwidth-rowdesc[row].width;

		for (y=rowdesc[row].left;y<=rowdesc[row].right;y++)
		{
			position=m_bottom.FindIndex(y);
			pToolbar=m_bottom.GetNext(position);
			pToolbar->m_index=y+1;
			pToolbar->SetWindowPos(this,rect2.left+total,rect2.top+(totalheight)-currbottom,pToolbar->m_currentlength,pToolbar->m_width,SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
			pToolbar->m_row=count;
			total+=pToolbar->m_currentlength;
		}
	}
	m_borderRect.bottom+=currbottom;
	totalheight-=(m_borderRect.bottom+m_borderRect.top);
	// Next the left

	position=m_left.GetHeadPosition();
	count=m_left.GetCount();
	start=0;
	row=0;
	total=0;
	priority=0;
	foundend=FALSE;
	for (y=0;y<count;y++)
	{
		pToolbar=m_left.GetNext(position);
		pToolbar->m_currentlength=pToolbar->m_minlength;
		total+=pToolbar->m_minlength;
		if (total>totalheight && start!=y)
		{
			y--;
			foundend=TRUE;
			total-=pToolbar->m_minlength;
		}
		else if (pToolbar->m_priority >= priority)
		{
			priority=pToolbar->m_priority;
			pPriorityToolbar=pToolbar;
		}
		// found a row now draw it
		if (foundend || y==count-1)
		{
			pPriorityToolbar->m_currentlength+=totalheight-total;
			position=m_left.FindIndex(start);
			total=0;
			for (x=start;x<=y;x++)
			{
				pToolbar=m_left.GetNext(position);
				pToolbar->m_index=x+1;
				pToolbar->MoveWindow(rect2.left+(row*pToolbar->m_width),rect2.top+(m_borderRect.top+total),pToolbar->m_width,pToolbar->m_currentlength);
				pToolbar->SetWindowPos(this,rect2.left+(row*pToolbar->m_width),rect2.top+(m_borderRect.top+total),pToolbar->m_width,pToolbar->m_currentlength,SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
				pToolbar->m_row=row;
				total+=pToolbar->m_currentlength;
			}
			// initialise the next row if its there
			m_borderRect.left+=pToolbar->m_width; // assumed all of them are the same width for now...
			if (foundend)
			{
				start=y+1;
				row++;
				total=0;
				foundend=FALSE;
				priority=0;
			}
		}
	}
	// Next the right

	position=m_right.GetHeadPosition();
	count=m_right.GetCount();
	start=0;
	row=0;
	priority=0;
	foundend=FALSE;
	
	int	yfix=0;
	if (m_top.IsEmpty())
		yfix=systemrect.Height();
	total=yfix;
	for (y=0;y<count;y++)
	{
		pToolbar=m_right.GetNext(position);
		pToolbar->m_currentlength=pToolbar->m_minlength;
		total+=pToolbar->m_minlength;
		if (total>totalheight && start!=y)
		{
			y--;
			foundend=TRUE;
			total-=pToolbar->m_minlength;
		}
		else if (pToolbar->m_priority >= priority)
		{
			priority=pToolbar->m_priority;
			pPriorityToolbar=pToolbar;
		}
		// found a row now draw it
		if (foundend || y==count-1)
		{
			pPriorityToolbar->m_currentlength+=totalheight-total;
			position=m_right.FindIndex(start);
			total=yfix;
			yfix=0;
			for (x=start;x<=y;x++)
			{
				pToolbar=m_right.GetNext(position);
				pToolbar->m_index=x+1;
//				pToolbar->MoveWindow(rect2.left+totalwidth-pToolbar->m_width-(row*pToolbar->m_width),rect2.top+m_borderRect.top+total,pToolbar->m_width,pToolbar->m_currentlength);
				pToolbar->SetWindowPos(this,rect2.left+totalwidth-pToolbar->m_width-(row*pToolbar->m_width),rect2.top+m_borderRect.top+total,pToolbar->m_width,pToolbar->m_currentlength,SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
				pToolbar->m_row=row;
				total+=pToolbar->m_currentlength;
			}
			// initialise the next row if its there
			m_borderRect.right+=pToolbar->m_width; // assumed all of them are the same width for now...
			if (foundend)
			{
				start=y+1;
				row++;
				total=0;
				foundend=FALSE;
				priority=0;
			}
		}
	}
//DeadCode MS 21Nov00 	__asm	{	int 3
//DeadCode MS 21Nov00 	};
	// create the border depending on borderrect
	rect-=rect2.TopLeft();
	view->MoveWindow(CRect(rect.left+m_borderRect.left,rect.top+m_borderRect.top,rect.right-m_borderRect.right,rect.bottom-m_borderRect.bottom));
	// move system box to top

	m_wndSystemBox->InDialAncestor()->SetWindowPos(&wndTop,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	PositionSysBox();
#endif
//	Invalidate();
}

//DEADCODE DAW 07/05/99 void CMainFrame::OnNcPaint() 
//DEADCODE DAW 07/05/99 {
//DEADCODE DAW 07/05/99 //	CDC* pDC=GetWindowDC();
//DEADCODE DAW 07/05/99 //	CRect windrect;
//DEADCODE DAW 07/05/99 //	GetWindowRect(windrect);
//DEADCODE DAW 07/05/99 //	pDC->FillSolidRect(0,0,windrect.Width(),windrect.Height(),RGB(0,0,0));
//DEADCODE DAW 07/05/99 	// Do not call CFrameWnd::OnNcPaint() for painting messages
//DEADCODE DAW 07/05/99 }
void	Campaign::GlobalRefreshData()
{
#ifndef	BOB_DEMO_VER

	MainToolBar().GlobalRefreshData();
	MiscToolBar().GlobalRefreshData();
	TitleBarPtr().GlobalRefreshData();
	((CMainFrame*)AfxGetMainWnd())->m_reportbar.GlobalRefreshData();
#endif
}

bool	Campaign::AnyDialogsOpen()
{
#ifndef	BOB_DEMO_VER

	if (MainToolBar().LoggedChild()!=-1) return true;
	if (MiscToolBar().LoggedChild()>MiscToolBar().ZOOMLEVEL) return true;
//DEADCODE RDH 14/04/00 	if (TitleBarPtr().LoggedChild()!=-1) return true;
#endif
	return false;
}
LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
#ifndef NDEBUG
	// TODO: Add your specialized code here and/or call the base class
//DEADCODE DAW 07/06/99 	CRect rect;														  //DAW 07/06/99
//DEADCODE DAW 07/06/99 	AfxGetMainWnd()->GetWindowRect(rect);							  //DAW 07/06/99
//TempCode JIM 11Oct00 static int r=0;
//TempCode JIM 11Oct00 	if ( message!=0x113)	//message!=0x363 &&
//TempCode JIM 11Oct00 	{
//TempCode JIM 11Oct00 		Mono_Text.PrintAt(70,r,(UByte*)"   ");
//TempCode JIM 11Oct00 		r++;
//TempCode JIM 11Oct00 		if (r==25) r=0;
//TempCode JIM 11Oct00 		Mono_Text.PrintAt(70,r,(UByte*)"<--");
//TempCode JIM 11Oct00 		Mono_Text.PrintHexAt(40,r,message,8);
//TempCode JIM 11Oct00 		Mono_Text.PrintHexAt(50,r,wParam,8);
//TempCode JIM 11Oct00 		Mono_Text.PrintHexAt(60,r,lParam,8);
//TempCode JIM 11Oct00 	}
	return CFrameWnd::WindowProc(message, wParam, lParam);
#else
	return 0;
#endif

}

#ifndef	BOB_DEMO_VER

void CMainFrame::UpdateToolbars(bool	hideall)
{
	for (int t=0,i=0;t<TB_TOTAL;t++)
	{
		if (toolbars[t])
			if (hideall)
				toolbars[t]->ReAttach(false,false);
			else
				if (Save_Data.toolbars[ToolBars(t)])
					toolbars[t]->ReAttach(true,false,i++);
				else
					toolbars[t]->ReAttach(false,false);
	}
//DeadCode MS 21Nov00 	__asm	{int 3
//DeadCode MS 21Nov00 	};
	RecalcLayout();
//DeadCode MS 21Nov00 	__asm	{int 3
//DeadCode MS 21Nov00 	};
	MainToolBar().TailorHints();
//DeadCode MS 21Nov00 	__asm	{int 3
//DeadCode MS 21Nov00 	};
	m_toolbar3.m_dialids[m_toolbar3.DIRECTIVESTOGGLE].SetPressed(!MMC.directivespopup);
	m_toolbar3.m_dialids[m_toolbar3.DIRECTIVESTOGGLE].SetHintString(RESSTRING(DIRECTIVES)+": "+RESLIST(OFF,!MMC.directivespopup));

//DEADCODE RDH 08/11/99 #ifndef	BOB_DEMO_VER
//DEADCODE RDH 08/11/99 	if (m_oldindebrief==MMC.indebrief) return;
//DEADCODE RDH 08/11/99 	m_oldindebrief=MMC.indebrief;
//DEADCODE RDH 08/11/99 	if (MMC.indebrief)// && m_toolbar2.IsWindowVisible())
//DEADCODE RDH 08/11/99 	{
//DEADCODE RDH 08/11/99 		m_toolbar5.ShowWindow(SW_SHOW);
//DEADCODE RDH 08/11/99 		m_toolbar2.Replace(&m_toolbar5);
//DEADCODE RDH 08/11/99 	}
//DEADCODE RDH 08/11/99 	else// if (!MMC.indebrief && m_toolbar5.IsWindowVisible())
//DEADCODE RDH 08/11/99 	{
//DEADCODE RDH 08/11/99 		m_toolbar2.ShowWindow(SW_SHOW);
//DEADCODE RDH 08/11/99 		m_toolbar5.Replace(&m_toolbar2);
//DEADCODE RDH 08/11/99 	}
//DEADCODE RDH 08/11/99 #endif
}

#endif

#ifndef	BOB_DEMO_VER

void CMainFrame::CloseToolChildren(RDialog* skipthis)
{
	for (int t=0;t<TB_TOTAL;t++)
	{
		if (toolbars[t])
			toolbars[t]->CloseLoggedChildren(skipthis);
	}
	m_wndSystemBox->CloseLoggedChildren(skipthis);
}

#endif

void CMainFrame::OnHelp() 
{
	// TODO: Add your command handler code here
	if (!Inst3d::InThe3D())
	{
		HELPWASLAUNCHEDRECENTLY=true;
//DEADCODE JIM 21/06/00 		HWND upperwnd=HWND_BOTTOM;  
//DEADCODE JIM 21/06/00 		::SetWindowPos(m_hWnd,upperwnd,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
		CFrameWnd::OnHelp() ;
	}
}

void CMainFrame::OnHelpFinder() 
{
	// TODO: Add your command handler code here
	if (!Inst3d::InThe3D())
		CFrameWnd::OnHelpFinder() ;
	
}

void CMainFrame::OnContextHelp() 
{
	// TODO: Add your command handler code here
	if (!Inst3d::InThe3D())
		CFrameWnd::OnContextHelp() ;
	
}
LRESULT CMainFrame::OnCommandHelp(WPARAM w, LPARAM lParam)
{
	if (!Inst3d::InThe3D())
	{
		CMIGView* view = (CMIGView*)GetActiveView();
		if ((disablehelp&1)==0 || (view && view->m_currentpage==0))
		{
			if (Todays_Packages.localplayer == NAT_RAF)
				AfxGetApp()->WinHelp(HID_BASE_RESOURCE+IDD_RAFCOMMANDBRIEFING);
			else
				AfxGetApp()->WinHelp(HID_BASE_RESOURCE+IDD_RAFCOMMANDBRIEFING);
		}
	}
	return 1;//CFrameWnd::OnCommandHelp(w,lParam);
}

void CMainFrame::WinHelp(DWORD dwData, UINT nCmd)
{
	if (RDialog::m_pHintBox)
		RDialog::m_pHintBox->ShowWindow(false);
	CWinApp* pApp = AfxGetApp();
	ASSERT_VALID(pApp);
	ASSERT(pApp->m_pszHelpFilePath != NULL);

	CWaitCursor wait;
	if (IsFrameWnd())
	{
		// CFrameWnd windows should be allowed to exit help mode first
		CFrameWnd* pFrameWnd = (CFrameWnd*)this;
		pFrameWnd->ExitHelpMode();
	}

	// cancel any tracking modes
	SendMessage(WM_CANCELMODE);
	SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

	// need to use top level parent (for the case where m_hWnd is in DLL)
	CWnd* pWnd = GetTopLevelParent();
	pWnd->SendMessage(WM_CANCELMODE);
	pWnd->SendMessageToDescendants(WM_CANCELMODE, 0, 0, TRUE, TRUE);

	// attempt to cancel capture
	HWND hWndCapture = ::GetCapture();
	if (hWndCapture != NULL)
		::SendMessage(hWndCapture, WM_CANCELMODE, 0, 0);

	TRACE3("WinHelp: pszHelpFile = '%s', dwData: $%lx, fuCommand: %d.\n",
		pApp->m_pszHelpFilePath, dwData, nCmd);

//Command equates are different between WinHelp and HTMLHelp. Why?
	switch (nCmd)
	{
	case	HELP_CONTEXT:
 //DeadCode RJS 03May100			nCmd=HH_DISPLAY_TOPIC;
			nCmd=HH_HELP_CONTEXT;
			break;
	}


	// finally, run the Windows Help engine
//DeadCode RJS 03May100 	if (!HtmlHelp(pWnd->m_hWnd, CString(pApp->m_pszHelpFilePath)+"::/asset.htm", nCmd, 0))
//DEADCODE DAW 15/05/00 	if (!HtmlHelp(NULL, pApp->m_pszHelpFilePath, nCmd, dwData&0xffff))
	if (!HtmlHelp(pWnd->m_hWnd, pApp->m_pszHelpFilePath, nCmd, dwData&0xffff))
	{
		dwData=IDD_RAFCOMMANDBRIEFING;
		if (!HtmlHelp(pWnd->m_hWnd, pApp->m_pszHelpFilePath, nCmd, dwData&0xffff))
			AfxMessageBox(AFX_IDP_FAILED_TO_LAUNCH_HELP);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnSize
//Author		Paul.   
//Date			Mon 25 Jan 1999
//------------------------------------------------------------------------------
void CMainFrame::OnMove(int x, int y) 
{
//DEADCODE DAW 07/05/99 	CRect oldpos;
//DEADCODE DAW 07/05/99 	GetWindowRect(oldpos);
//DEADCODE DAW 07/05/99 	CFrameWnd::OnMove(x, y);
//DEADCODE DAW 07/05/99 	x-=oldpos.left;
//DEADCODE DAW 07/05/99 	y-=oldpos.top;
//DEADCODE DAW 07/05/99 	RePositionLayout(x,y);
//	RecalcLayout();
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	if (m_doIExist==1)
		PositionSysBox();
	if (nType==SIZE_MINIMIZED)
	{
		//window has been minimized
		bAppMinimized=true;
	}
	else if (bAppMinimized)
	{
		//window has been restored
		bAppMinimized=false;
	}
	HELPWASLAUNCHEDRECENTLY=false;
	CFrameWnd::OnSize(nType,cx,cy);
}

void CMainFrame::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMainFrame::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return true;//CFrameWnd::OnEraseBkgnd(pDC);
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_doIExist=false;
	Save_Data.ChangeMode(SaveData::UIR_FIRST);

	CFrameWnd::OnClose();
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO FAR* lpMMI) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
	lpMMI->ptMinTrackSize=CPoint(300,400);
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
//DeadCode DAW 22Jun99 		TRACE2("Activate %i ==> %08x\n",nState,::GetWindowThreadProcessId(pWndOther->m_hWnd, NULL) );
//DeadCode DAW 22Jun99 	else
//DeadCode DAW 22Jun99 	{
//DeadCode DAW 22Jun99 		TRACE1("Activate %i xxx\n",nState);
		//If in the 3D && state==0 then discard DD here
#ifdef NDEBUG
 	if (!pWndOther)
		if (Inst3d::InThe3D())
		{
			if (!nState)	Inst3d::ReleaseDirectX();
			else
			{
				Inst3d::RestoreDirectX();
				CMIGView* view=(CMIGView*)GetActiveView();
				RFullPanelDial*	dial=GetFullPanel(view);
				dial->LaunchScreen(&RFullPanelDial::quickmissionflight);
			}
		}
#endif
//DeadCode DAW 22Jun99 	}

	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	
}
static BOOL CALLBACK EnumThreadWndProc(  HWND hwnd,  LPARAM lParam)
{
	*(int*)lParam=(int)hwnd;
	return	FALSE;
}
   

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CFrameWnd::OnActivateApp(bActive, hTask);
//DeadCode DAW 22Jun99 	TRACE2("Activate Ap %i ==>%08x\n",bActive,hTask);
	
	// TODO: Add your message handler code here
	//BOOL SetWindowPos( const CWnd* pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags );
	//const CWnd* pWndInsertAfter= wndBottom/wndTop/ wndTopMost/wndNoTopMost
//BOOL SetWindowPos(
//  HWND hWnd,             // handle to window
//  HWND hWndInsertAfter,  // placement-order handle
//  int X,                 // horizontal position
//  int Y,                 // vertical position
//  int cx,                // width
//  int cy,                // height
//  UINT uFlags            // window-positioning flags
//);
		if (!bActive)
		{  
//TEMPCODE JIM 05/04/00 			HWND upperwnd=HWND_BOTTOM;  
//TEMPCODE JIM 05/04/00 			::SetWindowPos(m_hWnd,upperwnd,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DEADCODE DAW 16/06/99 			if (hTask)
//DEADCODE DAW 16/06/99 				EnumThreadWindows((int)hTask,EnumThreadWndProc,(int)&upperwnd);
//DEADCODE DAW 16/06/99  			if (upperwnd!=HWND_BOTTOM)
//DEADCODE DAW 16/06/99 			{
//DEADCODE DAW 16/06/99 				::SetWindowPos(m_hWnd,HWND_TOP,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DEADCODE DAW 16/06/99 				::SetWindowPos(upperwnd,HWND_TOP,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DEADCODE DAW 16/06/99 			}
		}
		else
		{
//TEMPCODE JIM 05/04/00 #if !defined(NOT_TOPMOST)
//TEMPCODE JIM 05/04/00 			if (IsZoomed() && HELPWASLAUNCHEDRECENTLY==false)
//TEMPCODE JIM 05/04/00 				SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//TEMPCODE JIM 05/04/00 #endif
		}
	
}
/* 
pWndInsertAfter젨쟅dentifies the CWnd object that will precede this CWnd object in the Z-order. 
This parameter can be a pointer to a CWnd or a Pointer to one of the following values:

wndBottom젨쟑laces the window at the bottom of the Z-order. 
If this CWnd is a topmost window, the window loses its topmost status; 
the system places the window at the bottom of all other windows.

wndTop젨쟑laces the window at the top of the Z-order.

wndTopMost젨쟑laces the window above all nontopmost windows. 
The window maintains its topmost position even when it is deactivated.

wndNoTopMost젨쟓epositions the window to the top of all nontopmost windows (that is, behind all topmost windows). 
This flag has no effect if the window is already a nontopmost window.


nFlags젨쟔pecifies sizing and positioning options. This parameter can be a combination of the following:

SWP_DRAWFRAME젨잻raws a frame (defined when the window was created) around the window. 

SWP_FRAMECHANGED젨쟔ends a WM_NCCALCSIZE message to the window, even if the window's size is not being changed. If this flag is not specified, WM_NCCALCSIZE is sent only when the window's size is being changed.

SWP_HIDEWINDOW젨쟄ides the window.

SWP_NOACTIVATE젨잻oes not activate the window. If this flag is not set, the window is activated and moved to the top of either the topmost or the nontopmost group (depending on the setting of the pWndInsertAfter parameter).

SWP_NOCOPYBITS젨잻iscards the entire contents of the client area. If this flag is not specified, the valid contents of the client area are saved and copied back into the client area after the window is sized or repositioned.

SWP_NOMOVE젨쟓etains current position (ignores the x and y parameters).

SWP_NOOWNERZORDER젨잻oes not change the owner window's position in the Z-order.

SWP_NOREDRAW젨잻oes not redraw changes. If this flag is set, no repainting of any kind occurs. This applies to the client area, the nonclient area (including the title and scroll bars), and any part of the parent window uncovered as a result of the moved window. When this flag is set, the application must explicitly invalidate or redraw any parts of the window and parent window that must be redrawn.

SWP_NOREPOSITION젨쟔ame as SWP_NOOWNERZORDER. 

SWP_NOSENDCHANGING젨쟑revents the window from receiving the WM_WINDOWPOSCHANGING message.

SWP_NOSIZE젨쟓etains current size (ignores the cx and cy parameters).

SWP_NOZORDER젨쟓etains current ordering (ignores pWndInsertAfter).

SWP_SHOWWINDOW젨잻isplays the window.
*/

void CMainFrame::OnDevModeChange(LPTSTR lpDeviceName) 
{
	CFrameWnd::OnDevModeChange(lpDeviceName);
	
	// TODO: Add your message handler code here
//DEADCODE JIM 04/04/00 	ShowWindow(SW_SHOWMAXIMIZED);

	
}

LRESULT CMainFrame::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	int rv= CFrameWnd::DefWindowProc(message, wParam, lParam);
//DeadCode JIM 11Oct00 	switch (message)
//DeadCode JIM 11Oct00 	{
//DeadCode JIM 11Oct00 	case	WM_NCCREATE:			case	0x036d:	//WM_FLOATSTATUS
//DeadCode JIM 11Oct00 	case	WM_NCCALCSIZE:			case	0x04c8:	//MCIWNDM_NOTIFY:
//DeadCode JIM 11Oct00 	case	WM_CREATE:				case	WM_NCPAINT:
//DeadCode JIM 11Oct00 	case	WM_SIZE:				case	WM_SETCURSOR:
//DeadCode JIM 11Oct00 	case	WM_MOVE:				case	WM_SETFONT:
//DeadCode JIM 11Oct00 	case	WM_INITDIALOG:			case	WM_DISPLAYCHANGE:
//DeadCode JIM 11Oct00 	case	WM_CTLCOLORSTATIC:		case	WM_IDLEUPDATECMDUI:
//DeadCode JIM 11Oct00 	case	WM_GETFONT:				case	WM_ACTIVATE:
//DeadCode JIM 11Oct00 	case	WM_WINDOWPOSCHANGING:	case	WM_NCACTIVATE:
//DeadCode JIM 11Oct00 	case	WM_SHOWWINDOW:			case	WM_PARENTNOTIFY:	case	WM_SYNCPAINT:		
//DeadCode JIM 11Oct00 	case	WM_PAINT:				case	WM_GETTEXT:			case	WM_GETMINMAXINFO:
//DeadCode JIM 11Oct00 	case	WM_WINDOWPOSCHANGED:	case	WM_SETTEXT:			case	WM_KILLFOCUS:
//DeadCode JIM 11Oct00 	case	 WM_NCHITTEST:			case	WM_STYLECHANGING:	case	WM_STYLECHANGED:
//DeadCode JIM 11Oct00 
//DeadCode JIM 11Oct00 
//DeadCode JIM 11Oct00 
//DeadCode JIM 11Oct00 		return rv;
//DeadCode JIM 11Oct00 	}
	return rv;
}
