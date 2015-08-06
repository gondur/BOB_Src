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

// Filing.cpp : implementation file: Load/save savegames...
//

#include "stdafx.h"
#include "mig.h"
#include "Filing.h"
#include "savegame.h"
#include "bstream.h"
#include	"migview.h"
#include "package.h"
#include "uiicons.h"
#include "mymath.h"
#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
CString  CFiling::selectedfile;

/////////////////////////////////////////////////////////////////////////////
// CFiling dialog


CFiling::CFiling(bool quitonok,CWnd* pParent /*=NULL*/)
	: RowanDialog(CFiling::IDD, pParent)
{
	this->quitonok=quitonok;
	acnum=LSD_SAVE;
	//{{AFX_DATA_INIT(CFiling)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFiling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFiling)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFiling, CDialog)
	//{{AFX_MSG_MAP(CFiling)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFiling message handlers

BEGIN_EVENTSINK_MAP(CFiling, CDialog)
    //{{AFX_EVENTSINK_MAP(CFiling)
	ON_EVENT(CFiling, IDJ_TITLE, 3 /* OK */, OnOKTitle, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//////////////////////////////////////////////////////////////////////
//
// Function:    LoadGame
// Date:		21/06/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	CFiling::LoadGame(CString	fname)
{
	//This is the only setup that gets done when a game is loaded..
	char buffer[fileman::pathnamesize];
	BIStream bis(File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,fname),buffer));
	if (!bis.is_open())
		return false;

	bis>>Miss_Man;	//THIS IS THE LOAD
	m_pView->m_zoom=Save_Data.currzoom;
	m_pView->m_oldzoom=m_pView->m_zoom;
	m_pView->m_size.cx=Save_Data.currmapx;
	m_pView->m_size.cy=Save_Data.currmapy;
	m_pView->m_scrollpoint.x=Save_Data.currmapx2;
	m_pView->m_scrollpoint.y=Save_Data.currmapy2;
	m_pView->UpdateScrollbars();
	if ((Todays_Packages.britishisauto)	&&	(Todays_Packages.germanisauto))
		RFullPanelDial::gamestate = RFullPanelDial::PILOT;
	else
		RFullPanelDial::gamestate = RFullPanelDial::COMMANDER;
	if (Todays_Packages.localplayer==NAT_RAF)
	{
		RFullPanelDial::gameside = RFullPanelDial::SIDE_RAF;
		IconDescUI::LoadInstances(::GetDC(NULL),ICON_SET_1);
	}
	else
	{
		RFullPanelDial::gameside = RFullPanelDial::SIDE_LW;
		IconDescUI::LoadInstances(::GetDC(NULL),ICON_SET_1_LW);
	}

//Deadcode JIM 17Nov00	Node_Data.BuildTargetTable();

	RFullPanelDial::SetTitleText();


	return true;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SaveGame
// Date:		21/06/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	CFiling::SaveTimedGame()
{
	CString name=".BSL";
	if (Todays_Packages.localplayer==NAT_RAF)
		name=".BSR";
	short	day,month,year;
	Math_Lib.DateFromSecs (MMC.currdate,day,month,year);
	name=CSprintf("Supasave %s %2i-%i %02i-%02i-%02i%s",
			MMC.PlayerName,
			day,month,
			MMC.currtime/3600,(MMC.currtime/60)%60,MMC.currtime%60,
			name);
	return SaveGame(name);
}

bool	CFiling::SaveGame(CString	fname)
{
	char buffer[fileman::pathnamesize];
	Save_Data.currzoom=	m_pView->m_zoom;
	Save_Data.currmapx=m_pView->m_size.cx;
	Save_Data.currmapy=m_pView->m_size.cy;
	Save_Data.currmapx2=m_pView->m_scrollpoint.x;
	Save_Data.currmapy2=m_pView->m_scrollpoint.y;
	BOStream bos(File_Man.namenumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,fname),buffer));
	if (!bos.is_open())
		return false;
	bos<<Miss_Man;
	return true;

}

//////////////////////////////////////////////////////////////////////
//
// Function:    OnOK
// Date:		21/06/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void CFiling::OnOK() 
{
#ifndef	BOB_DEMO_VER
	bool quit = quitonok;

	if (	(selectedfile!="" && selectedfile[0]!='.')	)
	{

		Save_Data.lastsavegame = selectedfile;
		if (acnum==LSD_LOAD || acnum==LSD_LOAD_DESELECT)
		{
			CMainFrame* main=(CMainFrame*)AfxGetMainWnd();					  //RDH 27/05/99
			m_pView->m_currentpage=1;
			main->CloseToolChildren(this);
			m_pView->m_currentpage=0;
//DeadCode JIM 18Oct00 			main->m_toolbar1.CloseLoggedChildren(this);							  //RDH 27/05/99
//DeadCode JIM 18Oct00 			main->m_toolbar2.CloseLoggedChildren(this);							  //RDH 27/05/99
//DeadCode JIM 18Oct00 			main->m_toolbar3.CloseLoggedChildren(this);							  //RDH 27/05/99
//DeadCode JIM 18Oct00 			main->m_toolbar4.CloseLoggedChildren(this);							  //RDH 27/05/99
//DEADCODE RDH 08/11/99 			main->m_toolbar5.CloseLoggedChildren(this);							  //RDH 27/05/99
			LoadGame(selectedfile);								//JIM 13Jul99
			m_pView->m_mapdlg.Invalidate();									  //RDH 27/05/99
 			main->m_titlebar.Redraw();										  //RDH 27/05/99
//DeadCode JIM 18Oct00 			CMainFrame* pmainwnd=(CMainFrame*)AfxGetMainWnd();				  //RDH 27/05/99
			main->UpdateToolbars(false);										  //RDH 27/05/99


		}
		else
		{
			int rv = 1;
			if (File_Man.existnumberedfile(File_Man.fakefile(FIL_SAVEGAMEDIR,selectedfile)))
			{	//sorry file already exists...
				rv = RDialog::RMessageBox(IDS_SAVE, IDS_AREYOUSURE,NULL,IDS_YES,IDS_CANCEL);	//RDH 31/03/00

			}

			if (rv == 1)
				SaveGame(selectedfile);
		}
	
		if (quit)
		{
			((CMainFrame*)AfxGetMainWnd())->ExitCampaign();							//RJS 1Sep00
			RDialog::m_pView->LaunchFullPane(&RFullPanelDial::title);
		}
		else
			m_pView->m_mapdlg.Invalidate();
	}
#endif #ifndef	BOB_DEMO_VER
	CDialog::OnOK();	
}


void CFiling::OnOKTitle() 
{	//don't allow action if:
	//filename has no body: is "" or  ".ext"
	//
	//
	//
	if (selectedfile=="" || selectedfile[0]=='.')
		if ((acnum&LDS_DISABLE_SEP) || acnum==LSD_SAVE)
			return;
	OnOK();
}

CString&	PackageList::CSprintf(const char* format,...)
{
	class	CS2:public CString
{
public:
	void FormatV(LPCTSTR lpszFormat, va_list argList)
	{CString::FormatV(lpszFormat,argList);}
};
	va_list v;
	va_start(v,format);
	static CS2 rv;
	rv.FormatV(format,v);
	va_end(v);
	return rv;


}

BOStream& BOStream::operator<<(const CString& s)
{
	return operator << ((const char*)s);
}
