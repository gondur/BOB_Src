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

//////////////////////////////////////////////////////////////////////
//
// Module:      FullPSys.cpp
//
// Created:     03/12/99 by JIM
//
// Description: The system part of FULLPANE dialogs
//
//////////////////////////////////////////////////////////////////////
#define F_SOUNDS
#define F_BATTLE
#define F_COMMON
#include "stdafx.h"
#include "mig.h"
#include "stdlib.h"
#include "FullPane.h"
#include "messages.h"
#include "MIGView.h"
#include "replay.h"
#include "winmove.h"
#include "aggrgtor.h"
#include "stub3d.h"
#include "vfw.h"
#include	"miles.h"													//RJS 18Oct00

//DeadCode JON 10Nov00 extern HINSTANCE	g_hinst;
//DeadCode JON 10Nov00 extern HWND		g_hwndMCIWnd;

#define INITGUID
#include <streams.h>
#define WM_GRAPHNOTIFY  WM_USER+13										//JON 10Nov00
#define HELPER_RELEASE(x) { if (x) x->Release(); x = NULL; }			//JON 10Nov00

IGraphBuilder *pigb  = NULL;											//JON 10Nov00
IMediaControl *pimc  = NULL;											//JON 10Nov00
IMediaEventEx *pimex = NULL;											//JON 10Nov00
IVideoWindow  *pivw  = NULL;											//JON 10Nov00
IBasicAudio   *videoAudio = NULL;										//JON 10Nov00

const SLong videoWidth = 384;											//JON 12Nov00
const SLong videoHeight = 288;											//JON 12Nov00

int RFullPanelDial::resolutions[]={800,800,1024};//,1280};



RFullPanelDial::RFullPanelDial(CWnd* pParent /*=NULL*/)
	: RowanDialog(RFullPanelDial::IDD, pParent)
{
	//{{AFX_DATA_INIT(RFullPanelDial)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_currentscreen=NULL;
	whichcamp=0;
	pdial[0]=NULL;
	pdial[1]=NULL;
	pdial[2]=NULL;
	m_timerID=NULL;
	m_currentres=-1;
}

RFullPanelDial::~RFullPanelDial()
{
	m_pView->m_pfullpane=NULL;

}



void RFullPanelDial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RFullPanelDial)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLISTBOX,m_IDC_RLISTBOX);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RFullPanelDial, CDialog)
	//{{AFX_MSG_MAP(RFullPanelDial)
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_ENABLE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE_CLASS( WM_GETGLOBALFONT,RFullPanelDial,OnGetGlobalFont)
	ON_MESSAGE_CLASS( WM_GETARTWORK,RFullPanelDial, OnGetArt)
	ON_MESSAGE_CLASS( WM_SELECTTAB,RFullPanelDial, OnMciDidQuit)
//DeadCode JON 10Nov00 	ON_MESSAGE_CLASS( 0x04c8, RFullPanelDial, OnMciNotify)
	ON_MESSAGE_CLASS( WM_GRAPHNOTIFY, RFullPanelDial, OnMciNotify)				//JON 10Nov00
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// RFullPanelDial message handlers


void RFullPanelDial::LaunchMain(FullScreen* startscreen)
{ // launches the main dialog window
	CRect rect;
//DeadCode DAW 18Jun99 	if (GetCurrentRes()==0)
//DeadCode DAW 18Jun99 		MessageBox("Resolution is too small to run Mig Alley - this message to be removed","Warning",MB_OK);
//DeadCode DAW 18Jun99 	else
	{

	m_pView->GetClientRect(rect);
	RDialog* dial=RDialog::MakeTopDialog(rect,
								DialBox(FIL_NULL,this,EDGES_NOSCROLLBARS_NODRAGGING)
							);
// launch the first sheet...
//	CWnd* parent=GetParent()->GetParent();
//	ASSERT(parent==m_pView);
	GetParent()->BringWindowToTop();
	m_pStartScreen=startscreen;
	LaunchScreen(startscreen);
	UpdateSize();
	}
}

void RFullPanelDial::LaunchDial(RDialog* dial, UINT dialID,FileNum art) // typically pass new CSoundDialog for example
{
	if (pdial[dialID]) 
	{
		pdial[dialID]->PreDestroyPanel();
		pdial[dialID]->DestroyPanel();
	}
//	dial->Create(dial->MY_IID,this);
	// scale the dialog if necessary due to font size change
//	dial->m_scalingfactor=(float)fontdpi/96;
//	dial->ScaleDialog(1);
	if (art==FIL_NULL)
		art=m_currentscreen->resolutions[m_currentres].artwork;
	pdial[dialID]=AddPanel(dial,
		m_currentscreen->resolutions[m_currentres].dials[dialID].flags & FullScreen::Dial::X2, 
		CRect(	m_currentscreen->resolutions[m_currentres].dials[dialID].X,
				m_currentscreen->resolutions[m_currentres].dials[dialID].Y,
				0,
				m_currentscreen->resolutions[m_currentres].dials[dialID].flags  & FullScreen::Dial::CENTRE
			),
		art,
		EDGES_NOSCROLLBARS_NODRAGGING);
	pdial[dialID]->m_bDrawBackground=pdial[dialID]->m_bDrawBackground||enablepanelselfdrawstate;
//	dial->ShowWindow(SW_SHOW);
}
void RFullPanelDial::LaunchDial(UINT dialID,const DialBox* d) // typically pass new CSoundDialog for example
{
	if (pdial[dialID]) 
	{
		pdial[dialID]->PreDestroyPanel();
		pdial[dialID]->DestroyPanel();
	}
//	dial->Create(dial->MY_IID,this);
	// scale the dialog if necessary due to font size change
//	dial->m_scalingfactor=(float)fontdpi/96;
	pdial[dialID]=AddPanel(d,
				m_currentscreen->resolutions[m_currentres].dials[dialID].flags & FullScreen::Dial::X2, 
				CRect(	m_currentscreen->resolutions[m_currentres].dials[dialID].X,
						m_currentscreen->resolutions[m_currentres].dials[dialID].Y,
						0,
						m_currentscreen->resolutions[m_currentres].dials[dialID].flags  & FullScreen::Dial::CENTRE
					)
				);
	pdial[dialID]->m_bDrawBackground=pdial[dialID]->m_bDrawBackground||enablepanelselfdrawstate;
//	dial->ShowWindow(SW_SHOW);
}


//extern	Smack*	OpenSmack(FileNum filenumber,int win,int X,int Y,int w,int h);
//extern	cdecl	UWord	DoSmack(int poo);

FileNum	lastsmacker;

void RFullPanelDial::LaunchSmacker(int dialID,FileNum smackerID)
{
	int	X=	m_currentscreen->resolutions[m_currentres].dials[dialID].X;
	int	Y=	m_currentscreen->resolutions[m_currentres].dials[dialID].Y;
//	if (lastsmacker!=smackerID)	//new video
//	{
	pleasestartthissmacker=smackerID;
		if (smackerID)	//If we have a video to play
		{
			File_Man.MakeRoomFor(10000000);	//force 10MB to be dumped...
			File_Man.MakeRoomFor(-10000000);
			File_Man.DiscardDirList(smackerID);
			Bool exist=File_Man.ExistNumberedFile(smackerID);
#ifdef	BOB_DEMO_VER
			if (!exist)		  //demo can live without videos
			{
				pleasestartthissmacker=FIL_NULL;
				PostMessage(WM_SELECTTAB,0,0);
			}
			else
#endif
			{

//DeadCode JIM 19Oct00 MCIWNDF_NOAUTOSIZEWINDOW	Will not change the dimensions of an MCIWnd window when the image size changes. 
//DeadCode JIM 19Oct00 MCIWNDF_NOAUTOSIZEMOVIE	Will not change the dimensions of the destination rectangle when an MCIWnd window size changes.  
//DeadCode JIM 19Oct00 MCIWNDF_NOERRORDLG		Inhibits display of MCI errors to users. 
//DeadCode JIM 19Oct00 MCIWNDF_NOMENU			Hides the Menu button from view on the toolbar and prohibits users from accessing its pop-up menu. 
//DeadCode JIM 19Oct00 MCIWNDF_NOOPEN			Hides the open and close commands from the MCIWnd menu and prohibits users from accessing these choices in the pop-up menu. 
//DeadCode JIM 19Oct00 MCIWNDF_NOPLAYBAR		Hides the toolbar from view and prohibits users from accessing it. 
//DeadCode JIM 19Oct00 MCIWNDF_NOTIFYANSI		Causes MCIWnd to use an ANSI string instead of a Unicode string when notifying the parent window of device mode changes. This flag is used in combination with MCIWNDF_NOTIFYMODE and is exclusive to Windows NT/Windows 2000. 
//DeadCode JIM 19Oct00 MCIWNDF_NOTIFYMODE		Causes MCIWnd to notify the parent window with an MCIWNDM_NOTIFYMODE message whenever the device changes operating modes. The lParam parameter of this message identifies the new mode, such as MCI_MODE_STOP. 
//DeadCode JIM 19Oct00 MCIWNDF_NOTIFYPOS		Causes MCIWnd to notify the parent window with an MCIWNDM_NOTIFYPOS message whenever a change in the playback or record position within the content occurs. The lParam parameter of this message contains the new position in the content. 
//DeadCode JIM 19Oct00 MCIWNDF_NOTIFYMEDIA		Causes MCIWnd to notify the parent window with an MCIWNDM_NOTIFYMEDIA message whenever a new device is used or a data file is opened or closed. The lParam parameter of this message contains a pointer to the new filename. 
//DeadCode JIM 19Oct00 MCIWNDF_NOTIFYSIZE		Causes MCIWnd to notify the parent window when the MCIWnd window size changes. 
//DeadCode JIM 19Oct00 MCIWNDF_NOTIFYERROR		Causes MCIWnd to notify the parent window when an MCI error occurs. 
//DeadCode JIM 19Oct00 MCIWNDF_NOTIFYALL		Causes all MCIWNDF window notification styles to be used. 
//DeadCode JIM 19Oct00 MCIWNDF_RECORD			Adds a Record button to the toolbar and adds a new file command to the menu if the MCI device has recording capability.  
//DeadCode JIM 19Oct00 MCIWNDF_SHOWALL			Causes all MCIWNDF_SHOW styles to be used. 
//DeadCode JIM 19Oct00 MCIWNDF_SHOWMODE			Displays the current mode of the MCI device in the window title bar. For a list of device modes, see the MCIWndGetMode macro. 
//DeadCode JIM 19Oct00 MCIWNDF_SHOWNAME			Displays the name of the open MCI device or data file in the MCIWnd window title bar. 
//DeadCode JIM 19Oct00 MCIWNDF_SHOWPOS			Displays the current position within the content of the MCI device in the window title bar. 

//DeadCode JON 10Nov00 #pragma warnmsg ( "remove the g_hwndMCIWnd" )
//DeadCode JON 10Nov00 				g_hwndMCIWnd=MCIWndCreate(m_hWnd,g_hinst,WS_CHILD|WS_VISIBLE|MCIWNDF_NOTIFYMODE|MCIWNDF_NOPLAYBAR|MCIWNDF_NOMENU,FILEMAN.namenumberedfile(smackerID));
//DeadCode JON 10Nov00 				::SetWindowPos(g_hwndMCIWnd,NULL,X,Y,0,0,SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
//			MCIWndPlay(g_hwndMCIWnd);				//MCI did not run on all our machines. Switched to DirectMedia

			WCHAR wFile[MAX_PATH];
		    MultiByteToWideChar( CP_ACP, 0, FILEMAN.namenumberedfile(smackerID), -1, wFile, MAX_PATH );

			HRESULT hr =
				CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pigb);

			if (SUCCEEDED(hr))
			{ // Graphbuilder instance

				// QueryInterface for some basic interfaces
				pigb->QueryInterface(IID_IMediaControl, (void **)&pimc);
				pigb->QueryInterface(IID_IMediaEventEx, (void **)&pimex);
				pigb->QueryInterface(IID_IVideoWindow, (void **)&pivw);
				pigb->QueryInterface(IID_IBasicAudio, (void **)&videoAudio);

				// Have the graph construct its the appropriate graph automatically
				hr = pigb->RenderFile(wFile, NULL);

				pivw->put_Owner((OAHWND)m_hWnd);
				pivw->put_WindowStyle(WS_CHILD|WS_CLIPSIBLINGS|WS_CLIPCHILDREN);

				// Have the graph signal event via window callbacks for performance
				pimex->SetNotifyWindow((OAHWND)m_hWnd, WM_GRAPHNOTIFY, 0);

				if ( smackerID == FIL_VID_INTRO )
				{ // don't bother scaling..
					pivw->put_Left( X );
					pivw->put_Top( Y );
				} else
				{	
//DeadCode JON 12Nov00 					RECT grc;
//DeadCode JON 12Nov00 					grc.left = X;
//DeadCode JON 12Nov00 					grc.top = Y;
//DeadCode JON 12Nov00 					grc.right = X+videoWidth;
//DeadCode JON 12Nov00 					grc.bottom = Y+videoHeight;
					pivw->SetWindowPosition(X, Y, videoWidth, videoHeight);	
				}
//DeadCode JON 10Nov00 				GetClientRect(ghApp, &grc);
//DeadCode JON 10Nov00 				pivw->SetWindowPosition(grc.left, grc.top, grc.right, grc.bottom);

				// Run the graph if RenderFile succeeded
				if (!SUCCEEDED(hr))
					CloseVideo();
			//	  pimc->Run();

			} // Graphbuilder instance


				lastsmacker=smackerID;
				if (m_currentscreen->textlists[0].text==NULL)
					SetCapture();
			}
		}
		else
		{			//stop video
//DeadCode JON 10Nov00 			if (g_hwndMCIWnd)
//DeadCode JON 10Nov00 			{
//DeadCode JON 10Nov00 				MCIWndClose(g_hwndMCIWnd);
				CloseVideo();
				lastsmacker=(FileNum)-1;
//DeadCode JON 10Nov00 			}
		}
//	}else{
//	}
}
void RFullPanelDial::ChangeSmacker(int dialID,FileNum aviID)
{
//DeadCode JON 10Nov00 	MCIWndClose(g_hwndMCIWnd);
	CloseVideo();
	LaunchSmacker(dialID,aviID);
}


void RFullPanelDial::OnTimer(UINT nIDEvent) 
{
	// Nick the Enum loop thing
	if (nIDEvent==m_timerID)
	{
//DeadCode DAW 25Feb100 		if (!DoSmack((int)m_hWnd))
//DeadCode DAW 25Feb100 		{
//DeadCode DAW 25Feb100 //			Master_3d.BigWin();
//DeadCode DAW 25Feb100 //			Invalidate();
//DeadCode DAW 25Feb100 			CloseSmack();
//DeadCode DAW 25Feb100 			OnLButtonUp(0, CPoint (0,0)) ;
//DeadCode DAW 25Feb100 			//KillTimer(m_timerID);
//DeadCode DAW 25Feb100 			//m_timerID=0;
//DeadCode DAW 25Feb100 		}
	}
}

void RFullPanelDial::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_currentscreen && m_currentscreen->textlists[0].text==NULL) 
	{
		OnSelectRlistbox(0,0);
//DEADCODE DAW 15/06/99 		UpdateSize();
//DEADCODE DAW 15/06/99 
//DEADCODE DAW 15/06/99 		_Miles.InitSoundFonts();		//RJS 24Nov98
	}
//	{
//		LaunchScreen();
//		UpdateSize();
//	}

}

int RFullPanelDial::GetCurrentRes()
{ // the screen height is assumed to be 3/4 the screen width...
	CRect rect;
//	m_pView->GetClientRect(rect);
	AfxGetMainWnd()->GetWindowRect(rect); // a slightly more accurate representation
	int bestresX=0;
	int res;
	for (res=0;res<6;res++)
	{
		if (resolutions[res] &&
			rect.Width()>=resolutions[res] && 
			rect.Width()-resolutions[res]<=rect.Width()-resolutions[bestresX])
			bestresX=res;
	}
	int bestresY=0;
	for (res=0;res<6;res++)
	{
		if (resolutions[res] &&
			rect.Height()*4>=resolutions[res]*3 && 
			rect.Height()-resolutions[res]<=rect.Width()-resolutions[bestresY])
			bestresY=res;
	}
//	if (resolutions[bestresX]<=resolutions[bestresY]) return bestresX;
//	return bestresY;
	if (resolutions[bestresX]<=resolutions[bestresY]) res = bestresX;
	else res=bestresY;
	// now check if the artwork for this resolution is available, if not
	// search downwards until you find one that is there (Note there must be
	// one at the lowest resolution...
//	if (!m_currentscreen->resolutions[res].artwork)
//		return res;
	if (m_currentscreen)
		if (!m_currentscreen->resolutions[res].artwork)
			return res;
		else{}
	else
		return res;


	if (m_currentscreen)
	{
		if (!m_currentscreen->resolutions[res].artwork) return res;
		while (!m_currentscreen->resolutions[res].artwork || !FILEMAN.existnumberedfile(m_currentscreen->resolutions[res].artwork))
		{
			// find the next lowest resolution...
			int currentres=resolutions[res];
			int closestres=0;
			for (int newres=0;newres<6;newres++)
			{
				if (resolutions[newres]<currentres && resolutions[newres]>closestres)
				{
					closestres=resolutions[newres];
					res=newres;
				}
			}
			if (closestres==0)
			{
//				ASSERT(FALSE); // cannot find artwork for this sheet make sure there
								// is one at the lowest resolution...
				return 0;
			}
		}
	}
	return res;
}


void RFullPanelDial::LaunchScreen(FullScreen * pfullscreen)
{
	pleasestartthissmacker=FIL_NULL;
	bool	closedsmack=false;
//DeadCode DAW 25Feb100 	if (m_timerID) 
//DeadCode DAW 25Feb100 	{
//DeadCode DAW 25Feb100 		CloseSmack();
//DeadCode DAW 25Feb100 		Master_3d.BigWin();
//DeadCode DAW 25Feb100 		KillTimer(m_timerID);
//DeadCode DAW 25Feb100 		m_txosedsmack=true;
//DeadCode DAW 25Feb100 	}
//DeadCode JON 10Nov00 	if (g_hwndMCIWnd)
	if ( pivw )
	{
		CloseVideo();
//DEADCODE RDH 18/04/00 		OnMciNotify(0,MCI_MODE_STOP);
//DEADCODE RDH 18/05/00 		Save_Data.ChangeMode(SaveData::UIR_SCRAMBLE);
		closedsmack=true;
//DEADCODE RDH 18/05/00 		ReleaseCapture();
	}
	polylist.Clear();
	pdial[0]=pdial[1]=pdial[2]=NULL;
	Invalidate();
	m_currentscreen=pfullscreen;
	artnum=pfullscreen->resolutions[m_currentres].artwork;
	PositionRListBox();
	localnote=NULL;
	enablepanelselfdrawstate=false;
	if (m_currentscreen->InitProc) (this->*m_currentscreen->InitProc)();
	enablepanelselfdrawstate=false;
}

BEGIN_EVENTSINK_MAP(RFullPanelDial, CDialog)
    //{{AFX_EVENTSINK_MAP(RFullPanelDial)
	ON_EVENT(RFullPanelDial, IDC_RLISTBOX, 1 /* Select */, OnSelectRlistbox, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RFullPanelDial::OnSelectRlistbox(long row, long column) 
{
	int x=max(row,column);
	Bool retval=TRUE;

	//Nuke any running smacker
//	CloseSmack();
//	OnMciNotify(0,MCI_MODE_STOP);

	FullScreen* nextscreen=m_currentscreen->textlists[x].nextscreen;
	if (m_currentscreen->textlists[x].onselect) 
		retval=(this->*m_currentscreen->textlists[x].onselect)(nextscreen);
	if (retval && nextscreen)
	{
		// Nuke all panels then launch relevant sheet.
		RDialog* nextchild;

		for (int dialID=0;dialID<3;dialID++)
			if (pdial[dialID])
			{
				pdial[dialID]->PreDestroyPanel();
				pdial[dialID]->DestroyPanel();
				pdial[dialID]=NULL;
			}
		fchild=NULL;
		LaunchScreen(nextscreen);
	}
}

void RFullPanelDial::UpdateSize()
{
	// first move this so that it fits one of the resolutions
	int m_prevresart=m_currentscreen->resolutions[m_currentres].artwork;
	m_currentres=GetCurrentRes();
	int width=resolutions[m_currentres];
	int height=(resolutions[m_currentres]*3)/4;
	if (resolutions[m_currentres]==1280)
		height=1024;
	artnum=m_currentscreen->resolutions[m_currentres].artwork;
	CRect rect;
	AfxGetMainWnd()->GetClientRect(rect);
	if (m_currentscreen->textlists[0].text==NULL && height!=600)
		NOP;
//DEADCODE RDH 18/05/00 	{
//DEADCODE RDH 18/05/00 		parent->MoveWindow(rect);
//DEADCODE RDH 18/05/00 		MoveWindow(0,0,rect.Width(),rect.Height());
//DEADCODE RDH 18/05/00 	}
//DEADCODE RDH 18/05/00 	else
	{
		parent->MoveWindow((rect.Width()-width)/2,(rect.Height()-height)/2,
				width,height);
		MoveWindow(0,0,width,height);
	}
	PositionRListBox();
	for (int x=0;x<3;x++)
	{
		if (pdial[x])
		{
			if (pdial[x]->artnum==m_prevresart)
				pdial[x]->artnum=artnum;
			pdial[x]->MoveWindow(GetDialPosition(pdial[x],x));
			if (m_currentscreen->resolutions[m_currentres].dials[x].flags & FullScreen::Resolutions::Dial::X2) pdial[x]->ScaleDialog(2);
			else pdial[x]->ScaleDialog(1);
		}
	}
}

CRect RFullPanelDial::GetDialPosition(RDialog * dial, UINT dialID)
{
	CRect rect;
	dial->GetClientRect(rect);
	CPoint bottomright=rect.BottomRight();
	rect+=CPoint(m_currentscreen->resolutions[m_currentres].dials[dialID].X,
					 m_currentscreen->resolutions[m_currentres].dials[dialID].Y);
	if (m_currentscreen->resolutions[m_currentres].dials[dialID].flags & FullScreen::Resolutions::Dial::CENTRE)
	{
		bottomright.x/=2;
		bottomright.y/=2;
		rect-=bottomright;
	}
	return rect;
}

void RFullPanelDial::PositionRListBox()
{
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetBorder(FALSE);
	prlistbox->Clear();
	int seperation=100;

	if (m_currentscreen->listalign & FullScreen::Align::HORIZ)
	{	// a horizontal listbox...
		// spacing depends on resolution...
		for (int x=0;x<10;x++)
		{
			if (m_currentscreen->textlists[x].text==NULL) break;
			prlistbox->AddColumn(seperation);
			CString string;
			string.LoadString(m_currentscreen->textlists[x].text);
			prlistbox->AddString(string,x);
		}
	}
	else // a vertical one
	{
		prlistbox->AddColumn(100);
		for (int x=0;x<10;x++)
		{
			if (m_currentscreen->textlists[x].text==NULL) break;
			CString string;
			string.LoadString(m_currentscreen->textlists[x].text);
			prlistbox->AddString(string,0);
		}
	}
	// move to correct position.
	prlistbox->Shrink();
	prlistbox->ResizeToFit();
	CRect rect;
	prlistbox->GetClientRect(rect);
	CPoint bottomright=rect.BottomRight();
	CPoint topleft(m_currentscreen->resolutions[m_currentres].ListX,m_currentscreen->resolutions[m_currentres].ListY);
	switch (m_currentscreen->listalign&0xF8)
	{
		case FullScreen::Align::TOP:
			break;
		case FullScreen::Align::BOT:
			bottomright.x/=2;
			bottomright.y/=2;
			rect-=bottomright;
			break;
		case FullScreen::Align::MID:
			topleft.x-=bottomright.x/2;
			rect-=bottomright;
			break;
	}
	switch (m_currentscreen->listalign&0x3)
	{
		case FullScreen::Align::LEFT:
			prlistbox->SetCentred(FALSE);
			break;
		case FullScreen::Align::RIGHT:
			prlistbox->SetCentred(FALSE);
			break;
		case FullScreen::Align::CENTRE:
			prlistbox->SetCentred(TRUE);
			break;
		case FullScreen::Align::ONSPACE:
			prlistbox->SetCentred(FALSE);
			break;
	}
	prlistbox->MoveWindow(topleft.x,topleft.y,bottomright.x,bottomright.y);
}

// some utility procedures for launching map or 3d
#ifndef	BOB_DEMO_VER

Bool RFullPanelDial::LaunchMap(FullScreen*&fs, bool firsttime)
{
//DeadCode DAW 25Feb100 	CloseSmack();
	CloseVideo();
//DEADCODE RDH 18/04/00 	OnMciNotify(0,MCI_MODE_STOP);
	Save_Data.ChangeMode(SaveData::UIR_MAP);
//	Persons4::StartUpMapWorld();
	Node_Data.SetPlayerInfoLevel();
	m_pView->LaunchMap(firsttime);

	return FALSE;
}
#endif

Bool RFullPanelDial::Launch3d(FullScreen*&fs)
{
	CloseVideo();
//DEADCODE RDH 18/04/00 	OnMciNotify(0,MCI_MODE_STOP);
//	closedsmack=true;
//DeadCode DAW 25Feb100 	CloseSmack();
	return TRUE;
}

CFont* RFullPanelDial::OnGetGlobalFont(int fontnum)
{
	if (m_currentres==-1) m_currentres=GetCurrentRes();
	if (g_AllFonts[fontnum][1])
	{
//DeadCode JIM 20Oct00 		int currentres=resolutions[m_currentres];
		if (m_currentres>=3)
			return g_AllFonts[fontnum][3];
		else
			return g_AllFonts[fontnum][m_currentres];
//DEADCODE MS 01/02/00 		if (currentres>=1280) return g_AllFonts[fontnum][3];
//DEADCODE MS 01/02/00 		else if (currentres>=1024) return g_AllFonts[fontnum][2];
//DEADCODE MS 01/02/00 		else if (currentres>=800) return g_AllFonts[fontnum][1];
//DEADCODE MS 01/02/00 		else return g_AllFonts[fontnum][0];	
	}
	else if (m_scalingfactor==2) return g_AllFonts[fontnum][3];
	else return g_AllFonts[fontnum][0];
}

void	RFullPanelDial::SetTitleText(bool clear)
{	
	if (clear)
		AfxGetMainWnd()->SetWindowText(RESSTRING(BOB));
	else
	if (Miss_Man.currcampaignnum!=Miss_Man.SCRAMBLECAMPAIGN)
		AfxGetMainWnd()->SetWindowText(RESSTRING(BOB)+": "+LoadResString(IDS_L_SCAMPAIGNSELECT1+Miss_Man.currcampaignnum));
	else
		if (CSQuick1::currquickmiss>=0)
		AfxGetMainWnd()->SetWindowText(RESSTRING(BOB)+": "+LoadResString(CSQuick1::quickmissions[CSQuick1::currquickmiss].missionname));
}

LRESULT RFullPanelDial::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL RFullPanelDial::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreCreateWindow(cs);
}

int RFullPanelDial::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}

BOOL RFullPanelDial::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RFullPanelDial::OnEnable(BOOL bEnable) 
{
	CDialog::OnEnable(bEnable);
	
	// TODO: Add your message handler code here
	
}


void RFullPanelDial::OnPaint() 
{
	if (artnum)
		CDialog::OnPaint();
	else
	{
		PAINTSTRUCT paintstruct;
		CDC* pDC;
		pDC=BeginPaint(&paintstruct);
		Rtestsh1::Setup3dStatuses state=Rtestsh1::Start3d(Rtestsh1::S3D_DONEBACK);
		if (state==Rtestsh1::S3D_STOPPED)
		{
			paintstruct.fErase=TRUE;
			CRect rect;
			GetClientRect(rect);
			pDC->FillSolidRect(rect,RGB(0,0,0));
		}
		else
		if (state==Rtestsh1::S3D_STARTSETUP)
		{
			paintstruct.fErase=TRUE;
			CRect rect;
			GetClientRect(rect);
			pDC->FillSolidRect(rect,RGB(0,0,0));	//RGB(160,184,208));
		}
		EndPaint(&paintstruct);
		
	}
//DeadCode JON 10Nov00 	if (pleasestartthissmacker && g_hwndMCIWnd)
	if (pleasestartthissmacker && pimc)
	{
		pimc->Run();
		videoAudio->put_Volume( _Miles.SmackerOn(0) );
//DeadCode JON 10Nov00 _Miles.SmackerOn(int(g_hwndMCIWnd));									//RJS 18Oct00
//DeadCode JON 10Nov00 		MCIWndPlay(g_hwndMCIWnd);
	}

	pleasestartthissmacker=FIL_NULL;
}

////////////////////////////////////////////////////////////////////////
//
// Function:    OnGetArt
// Date:        18/01/99
// Author:      JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
FileNum RFullPanelDial::OnGetArt()
{
	return artnum;
}


void	RFullPanelDial::ScaleHitAreas(int polygonscale)	//1024 default
{
	polylist.scale=polygonscale/resolutions[m_currentres];
}

// this closes the video
void RFullPanelDial::CloseVideo()
{
    if (pivw)
	{ // Relinquish ownership (IMPORTANT!) after hiding
		pivw->put_Visible(OAFALSE);
		pivw->put_Owner(NULL);
		HELPER_RELEASE(pivw)
		ReleaseCapture();;
		_Miles.SmackerOff();											//RJS 18Oct00
	} // Relinquish ownership (IMPORTANT!) after hiding

    HELPER_RELEASE(pigb);
    HELPER_RELEASE(pimc);
    HELPER_RELEASE(pimex);
	HELPER_RELEASE(videoAudio);

//DeadCode JON 10Nov00 	if (g_hwndMCIWnd)
//DeadCode JON 10Nov00 	{
//DeadCode JON 10Nov00 
//DeadCode JON 10Nov00 		MCIWndClose(g_hwndMCIWnd);
//DeadCode JON 10Nov00 		MCIWndDestroy(g_hwndMCIWnd);
//DeadCode JON 10Nov00 		g_hwndMCIWnd=NULL;
//DeadCode JON 10Nov00 		ReleaseCapture();
//DeadCode JON 10Nov00 		_Miles.SmackerOff();											//RJS 18Oct00
//DeadCode JON 10Nov00 	}																	//JIM 23Oct00
}

void RFullPanelDial::OnMciDidQuit(int wParam,int lParam)
{
	OnLButtonUp(0, CPoint (0,0)); //terminate the sheet also


}

// this function is called when a message is recieved from the smacker...	
void RFullPanelDial::OnMciNotify(int wParam,int lParam)
{
	LONG		evCode;
	LONG		evParam1;
	LONG		evParam2;
	HRESULT		hr;

	if ( pimex ) // check we've not cloded it down already
		while (SUCCEEDED(pimex->GetEvent(&evCode, &evParam1, &evParam2, 0)))
		{ // Spin through the events

			hr = pimex->FreeEventParams(evCode, evParam1, evParam2);

			if (EC_COMPLETE == evCode)
			{ // Finished
				CloseVideo();
				PostMessage(WM_SELECTTAB,0,0);
				break;
			} // Finished
		} // Spin through the events

//DeadCode JON 10Nov00 	switch (lParam)
//DeadCode JON 10Nov00 	{
//DeadCode JON 10Nov00 	case	MCI_MODE_STOP:
//DeadCode JON 10Nov00 		CloseVideo();
//DeadCode JON 10Nov00 		PostMessage(WM_SELECTTAB,0,0);
//DeadCode JON 10Nov00 //DeadCode DAW 2Aug00 		TRACE0("MCI STOP");
//DeadCode JON 10Nov00 //DeadCode JIM 2Aug00 		ReleaseCapture();
//DeadCode JON 10Nov00 //DEADCODE RDH 18/04/00 				MCIWndClose(g_hwndMCIWnd);
//DeadCode JON 10Nov00 //DEADCODE RDH 18/04/00 				MCIWndDestroy(g_hwndMCIWnd);
//DeadCode JON 10Nov00 //DEADCODE RDH 18/04/00 				g_hwndMCIWnd=NULL;
//DeadCode JON 10Nov00 //DeadCode DAW 2Aug00 				OnLButtonUp(0, CPoint (0,0)); //terminate the sheet also
//DeadCode JON 10Nov00 	break;
//DeadCode JON 10Nov00 	default:
//DeadCode JON 10Nov00 //		wParam=lParam;
//DeadCode JON 10Nov00 	break;
//DeadCode JON 10Nov00 	}

}

BOOL RFullPanelDial::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::OnCommand(wParam, lParam);
}

//DEADCODE RDH 18/05/00 LRESULT RFullPanelDial::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
//DEADCODE RDH 18/05/00 {
//DEADCODE RDH 18/05/00 	// TODO: Add your specialized code here and/or call the base class
//DEADCODE RDH 18/05/00 	int rv= CDialog::DefWindowProc(message, wParam, lParam);
//DEADCODE RDH 18/05/00 	switch (message)
//DEADCODE RDH 18/05/00 	{
//DEADCODE RDH 18/05/00 	case	WM_NCCREATE:			case	WM_PARENTNOTIFY:
//DEADCODE RDH 18/05/00 	case	WM_NCCALCSIZE:			case	0x04c8:	//MCIWNDM_NOTIFY:
//DEADCODE RDH 18/05/00 	case	WM_CREATE:				case	WM_NCPAINT:
//DEADCODE RDH 18/05/00 	case	WM_SIZE:				case	WM_SETCURSOR:
//DEADCODE RDH 18/05/00 	case	WM_MOVE:				case	WM_SETFONT:
//DEADCODE RDH 18/05/00 	case	WM_INITDIALOG:			case	WM_DISPLAYCHANGE:
//DEADCODE RDH 18/05/00 	case	WM_CTLCOLORSTATIC:		case	WM_IDLEUPDATECMDUI: //363
//DEADCODE RDH 18/05/00 	case	WM_GETFONT:				//
//DEADCODE RDH 18/05/00 	case	WM_WINDOWPOSCHANGING:	//
//DEADCODE RDH 18/05/00 	case	WM_SHOWWINDOW:			//
//DEADCODE RDH 18/05/00 	case	WM_PAINT:				//
//DEADCODE RDH 18/05/00 	case	WM_WINDOWPOSCHANGED:	//
//DEADCODE RDH 18/05/00 	case	 WM_NCHITTEST:			//
//DEADCODE RDH 18/05/00 		return rv;
//DEADCODE RDH 18/05/00 	}
//DEADCODE RDH 18/05/00 	return rv;
//DEADCODE RDH 18/05/00 }

BOOL RFullPanelDial::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

BOOL RFullPanelDial::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::OnNotify(wParam, lParam, pResult);
}

BOOL RFullPanelDial::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::PreTranslateMessage(pMsg);
}
