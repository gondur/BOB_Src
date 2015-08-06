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

// RowanDialog: // mapfltlw.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "MapFltLw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MapFiltersRaidsLW dialog


RDialog*	MapFiltersRaidsLW::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new MapFiltersRaidsLW())
			);
}


MapFiltersRaidsLW::MapFiltersRaidsLW(CWnd* pParent /*=NULL*/)
	: RowanDialog(MapFiltersRaidsLW::IDD, pParent)
{
	//{{AFX_DATA_INIT(MapFiltersRaidsLW)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MapFiltersRaidsLW::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MapFiltersRaidsLW)
	DDX_Control(pDX, IDC_RRADIO_PLOTS, m_IDC_RRADIO_PLOTS);
	DDX_Control(pDX, IDC_LWROUTELINES, m_IDC_LWROUTELINES);
	DDX_Control(pDX, IDC_FIGHTERSWEEPS, m_IDC_FIGHTERSWEEPS);
	DDX_Control(pDX, IDC_BOMBERS, m_IDC_BOMBERS);
	DDX_Control(pDX, IDC_LWTARGETLINES, m_IDC_LWTARGETLINES);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MapFiltersRaidsLW, CDialog)
	//{{AFX_MSG_MAP(MapFiltersRaidsLW)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MapFiltersRaidsLW message handlers

BEGIN_EVENTSINK_MAP(MapFiltersRaidsLW, CDialog)
    //{{AFX_EVENTSINK_MAP(MapFiltersRaidsLW)
	ON_EVENT(MapFiltersRaidsLW, IDC_FIGHTERSWEEPS, 1 /* Clicked */, OnClickedFightersweeps, VTS_NONE)
	ON_EVENT(MapFiltersRaidsLW, IDC_LWROUTELINES, 1 /* Clicked */, OnClickedLwroutelines, VTS_NONE)
	ON_EVENT(MapFiltersRaidsLW, IDC_LWTARGETLINES, 1 /* Clicked */, OnClickedLwtargetlines, VTS_NONE)
	ON_EVENT(MapFiltersRaidsLW, IDC_BOMBERS, 1 /* Clicked */, OnClickedBombers, VTS_NONE)
	ON_EVENT(MapFiltersRaidsLW, IDC_RRADIO_PLOTS, 1 /* Selected */, OnSelectedRradioPlots, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void MapFiltersRaidsLW::Refresh()
{
		CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIO_PLOTS);
	pradio->Clear();

	pradio->AddButton(RESSTRING(AUTHENTICPLOTS));
	pradio->AddButton(RESSTRING(ICONSREP));
	pradio->AddButton(RESSTRING(ONEPLOTPERGESCHWADER));
	pradio->AddButton(RESSTRING(ONEPLOTPERGRUPPE));
	pradio->AddButton(RESSTRING(ONEPLOTPERSTAFFEL));
  	pradio->SetCurrentSelection((int)Save_Data.lwplots);

	CRButton* b;


	b = GETDLGITEM(IDC_FIGHTERSWEEPS);
	b->SetPressed(Save_Data.mapfilters[FILT_RECONN]);

	
	b = GETDLGITEM(IDC_LWTARGETLINES);
	b->SetPressed(Save_Data.mapfilters[FILT_LWTARGETLINES]);
	b = GETDLGITEM(IDC_BOMBERS);
	b->SetPressed(Save_Data.mapfilters[FILT_BOMBERS]);

	b = GETDLGITEM(IDC_LWROUTELINES);
	if (		(Save_Data.mapfilters[FILT_RECONN])
			&&	(Save_Data.mapfilters[FILT_BOMBERS])
			&&	(Save_Data.mapfilters[FILT_LWTARGETLINES])
		)
		b->SetPressed(true);
	else
		b->SetPressed(false);


}

BOOL MapFiltersRaidsLW::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Refresh();

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MapFiltersRaidsLW::OnClickedFightersweeps() 
{
	if (Save_Data.mapfilters[FILT_RECONN])
		Save_Data.mapfilters%=FILT_RECONN;
	else
		Save_Data.mapfilters|=FILT_RECONN;
	m_pView->m_mapdlg.Invalidate();
	Refresh();
	
}

void MapFiltersRaidsLW::OnClickedLwroutelines() 
{
	if (		(Save_Data.mapfilters[FILT_RECONN])
			&&	(Save_Data.mapfilters[FILT_BOMBERS])
			&&	(Save_Data.mapfilters[FILT_LWTARGETLINES])
		)
	{
		Save_Data.mapfilters%=FILT_RECONN;
		Save_Data.mapfilters%=FILT_BOMBERS;
		Save_Data.mapfilters%=FILT_LWTARGETLINES;
	}else
	{
		Save_Data.mapfilters|=FILT_RECONN;
		Save_Data.mapfilters|=FILT_BOMBERS;
		Save_Data.mapfilters|=FILT_LWTARGETLINES;
	}
	m_pView->m_mapdlg.Invalidate();
	Refresh();
	
}

void MapFiltersRaidsLW::OnClickedLwtargetlines() 
{
	if (Save_Data.mapfilters[FILT_LWTARGETLINES])
		Save_Data.mapfilters%=FILT_LWTARGETLINES;
	else
		Save_Data.mapfilters|=FILT_LWTARGETLINES;
	m_pView->m_mapdlg.Invalidate();
	Refresh();
}

void MapFiltersRaidsLW::OnClickedBombers() 
{
	if (Save_Data.mapfilters[FILT_BOMBERS])
		Save_Data.mapfilters%=FILT_BOMBERS;
	else
		Save_Data.mapfilters|=FILT_BOMBERS;
	m_pView->m_mapdlg.Invalidate();
	Refresh();
	
}

void MapFiltersRaidsLW::OnSelectedRradioPlots(long ButtonNum) 
{
	Save_Data.lwplots = (PlotLevels)ButtonNum;	
	m_pView->m_mapdlg.Invalidate();
	Refresh();

}
