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

//DEADCODE DAW 07/02/00 // RowanDialog: // DosBut.cpp : implementation file
//DEADCODE DAW 07/02/00 //
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 #include "stdafx.h"
//DEADCODE DAW 07/02/00 #include "mig.h"
//DEADCODE DAW 07/02/00 #include "DosBut.h"
//DEADCODE DAW 07/02/00 #include "MigView.h"
//DEADCODE DAW 07/02/00 #include "palette.h"
//DEADCODE DAW 07/02/00 #include "display.h"
//DEADCODE DAW 07/02/00 #include "overlay.h"
//DEADCODE DAW 07/02/00 #include "persons2.h"
//DEADCODE DAW 07/02/00 #define F_COMMON
//DEADCODE DAW 07/02/00 #define F_SOUNDS
//DEADCODE DAW 07/02/00 #define F_BATTLE
//DEADCODE DAW 07/02/00 #undef F_GRAFIX
//DEADCODE DAW 07/02/00 #include "files.g"
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 #ifdef _DEBUG
//DEADCODE DAW 07/02/00 //#define new DEBUG_NEW
//DEADCODE DAW 07/02/00 #ifndef THIS_FILE_DEFINED
//DEADCODE DAW 07/02/00 #undef THIS_FILE
//DEADCODE DAW 07/02/00 static char THIS_FILE[] = __FILE__;
//DEADCODE DAW 07/02/00 #endif
//DEADCODE DAW 07/02/00 #endif
//DEADCODE DAW 07/02/00 /////////////////////////////////////////////////////////////////////////////
//DEADCODE DAW 07/02/00 // DossierButtons dialog
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 DossierButtons::DossierButtons(int uid,CWnd* pParent /*=NULL*/)
//DEADCODE DAW 07/02/00 	: RowanDialog(DossierButtons::IDD, pParent)
//DEADCODE DAW 07/02/00 {
//DEADCODE DAW 07/02/00 	SetProjSpecific(-1,uid);
//DEADCODE DAW 07/02/00 	//{{AFX_DATA_INIT(DossierButtons)
//DEADCODE DAW 07/02/00 		// NOTE: the ClassWizard will add member initialization here
//DEADCODE DAW 07/02/00 	//}}AFX_DATA_INIT
//DEADCODE DAW 07/02/00 }
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 void DossierButtons::DoDataExchange(CDataExchange* pDX)
//DEADCODE DAW 07/02/00 {
//DEADCODE DAW 07/02/00 	CDialog::DoDataExchange(pDX);
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 //	CRButton*	but = GetDlgItem(IDC_AUTHORISE);
//DEADCODE DAW 07/02/00 //	int	pack=Todays_Packages.FindPackage();
//DEADCODE DAW 07/02/00 //	if  (		(MMC.indebrief)
//DEADCODE DAW 07/02/00 //			||	(pack < 0)
//DEADCODE DAW 07/02/00 //		)
//DEADCODE DAW 07/02/00 //	{
//DEADCODE DAW 07/02/00 //		but->SetForeColor(RGB(80,80,80));
//DEADCODE DAW 07/02/00 //		but->SetDisabled(true);
//DEADCODE DAW 07/02/00 //	}
//DEADCODE DAW 07/02/00 //	else
//DEADCODE DAW 07/02/00 //	{
//DEADCODE DAW 07/02/00 //		but->SetForeColor(RGB(255,255,0));
//DEADCODE DAW 07/02/00 //		but->SetDisabled(false);
//DEADCODE DAW 07/02/00 //	}
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 	
//DEADCODE DAW 07/02/00 	//{{AFX_DATA_MAP(DossierButtons)
//DEADCODE DAW 07/02/00 		// NOTE: the ClassWizard will add DDX and DDV calls here
//DEADCODE DAW 07/02/00 	DDX_Control(pDX,IDC_AUTHORISE	,m_IDC_AUTHORISE);
//DEADCODE DAW 07/02/00 	DDX_Control(pDX,IDC_CENTRE		,m_IDC_CENTRE);
//DEADCODE DAW 07/02/00 	DDX_Control(pDX,IDC_PHOTO 		,m_IDC_PHOTO);
//DEADCODE DAW 07/02/00 	DDX_Control(pDX,IDC_Zoom		,m_IDC_Zoom);
//DEADCODE DAW 07/02/00 	//}}AFX_DATA_MAP
//DEADCODE DAW 07/02/00 }
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 BEGIN_MESSAGE_MAP(DossierButtons, CDialog)
//DEADCODE DAW 07/02/00 	//{{AFX_MSG_MAP(DossierButtons)
//DEADCODE DAW 07/02/00 	//}}AFX_MSG_MAP
//DEADCODE DAW 07/02/00 END_MESSAGE_MAP()
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 /////////////////////////////////////////////////////////////////////////////
//DEADCODE DAW 07/02/00 // DossierButtons message handlers
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 BEGIN_EVENTSINK_MAP(DossierButtons, CDialog)
//DEADCODE DAW 07/02/00     //{{AFX_EVENTSINK_MAP(DossierButtons)
//DEADCODE DAW 07/02/00 	ON_EVENT(DossierButtons, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
//DEADCODE DAW 07/02/00 	ON_EVENT(DossierButtons, IDC_CENTRE, 1 /* Clicked */, OnClickedCentre, VTS_NONE)
//DEADCODE DAW 07/02/00 	ON_EVENT(DossierButtons, IDC_PHOTO, 1 /* Clicked */, OnClickedPhoto, VTS_NONE)
//DEADCODE DAW 07/02/00 	ON_EVENT(DossierButtons, IDC_Zoom, 1 /* Clicked */, OnClickedZoom, VTS_NONE)
//DEADCODE DAW 07/02/00 	//}}AFX_EVENTSINK_MAP
//DEADCODE DAW 07/02/00 END_EVENTSINK_MAP()
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 void DossierButtons::OnClickedAuthorise() 
//DEADCODE DAW 07/02/00 {
//DEADCODE DAW 07/02/00 //DEADCODE DAW 23/11/99 	MainToolBar().OpenLoadProfile(wavenum);
//DEADCODE DAW 07/02/00 	
//DEADCODE DAW 07/02/00 }
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 void DossierButtons::OnClickedCentre() 
//DEADCODE DAW 07/02/00 {
//DEADCODE DAW 07/02/00 	m_pView->ZoomToUID(UniqueID(wavenum),m_pView->m_zoom);
//DEADCODE DAW 07/02/00 	RDialog::m_pView->m_mapdlg.ResetIcon((UniqueID)wavenum);
//DEADCODE DAW 07/02/00 }
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 void DossierButtons::OnClickedPhoto() 
//DEADCODE DAW 07/02/00 {
//DEADCODE DAW 07/02/00 #ifndef NDEBUG
//DEADCODE DAW 07/02/00 #define PLACEMENT	CRect(0,0,512,384)
//DEADCODE DAW 07/02/00 #else
//DEADCODE DAW 07/02/00 #define	PLACEMENT	Place(POSN_CENTRE,POSN_CENTRE, 0, 0)
//DEADCODE DAW 07/02/00 #endif
//DEADCODE DAW 07/02/00 //	#define PLACEMENT	CRect(0,0,512,384)
//DEADCODE DAW 07/02/00 	UniqueID targID=UniqueID(wavenum);
//DEADCODE DAW 07/02/00 	CString tname=GetTargName(targID);
//DEADCODE DAW 07/02/00 	OverLay.SetTargName((char*)LPCTSTR(tname));
//DEADCODE DAW 07/02/00 	OverLay.loader_art=FIL_PHOTOART;	//FIL_PHOTOART_800;
//DEADCODE DAW 07/02/00 	LogChild(0,MakeTopDialog(PLACEMENT,DialBox(OverLay.loader_art,new Rtestsh1(UniqueID(targID)),EDGES_NOSCROLLBARS)));
//DEADCODE DAW 07/02/00 	Rtestsh1::Start3d(Rtestsh1::S3D_DONEBACK);
//DEADCODE DAW 07/02/00 }
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 void DossierButtons::OnClickedZoom() 
//DEADCODE DAW 07/02/00 {
//DEADCODE DAW 07/02/00 	m_pView->ZoomToUID(UniqueID(wavenum),m_pView->m_zoom*2);
//DEADCODE DAW 07/02/00 	RDialog::m_pView->m_mapdlg.ResetIcon((UniqueID)wavenum);
//DEADCODE DAW 07/02/00 	
//DEADCODE DAW 07/02/00 }
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 BOOL DossierButtons::OnInitDialog() 
//DEADCODE DAW 07/02/00 {
//DEADCODE DAW 07/02/00 	CDialog::OnInitDialog();
//DEADCODE DAW 07/02/00 	
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99    	SupplyTree::Supply2UID	relation;
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	SupplyNode*	node=SupplyTree::FindSupplyNodeForItem((UniqueID)wavenum,&relation);
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	int uidband=Persons2::getbandfromUID((UniqueID)wavenum);
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	bool	canauthorise = true;
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	if ((node) && (node->status == BEHINDBLUELINES)) 
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		canauthorise = false;
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	if(uidband == AmberAirfieldBAND)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	{
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		for (int af=0;SupplyTree::airfieldinfo[af].nationality!=NAT_ALIGN;af++)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		{
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 			if (		(SupplyTree::airfieldinfo[af].airfield == (UniqueID)wavenum)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 					&&	(SupplyTree::airfieldinfo[af].nationality == NAT_BLUE)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 				)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 			{
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 				canauthorise = false;
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 				break;
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 			}
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		}
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	}
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	CRButton*	but = GETDLGITEM(IDC_AUTHORISE);
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	int	pack=Todays_Packages.FindPackage();
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	if  (		(MMC.indebrief)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 			||	(pack < 0)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 			||	(		(Todays_Packages.FindSquadExlMedBombers() < 0) //RDH 25/06/99
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 					&&	(Todays_Packages.CAPAircraftcnt() < 32)						  //RDH 25/06/99
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 				)	
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 			||	(!canauthorise)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	{
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		but->SetForeColor(RGB(80,80,80));
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		but->SetDisabled(true);
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	}
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	else
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	{
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		but->SetForeColor(RGB(255,255,0));
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		but->SetDisabled(false);
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	}
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	but = GETDLGITEM(IDC_PHOTO);
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	if  (		(uidband == RedRoadBAND)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 			||	(uidband == RedRailBand)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		)
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	{
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		but->SetForeColor(RGB(80,80,80));
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		but->SetDisabled(true);
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	}
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	else
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	{
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		but->SetForeColor(RGB(255,255,0));
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 		but->SetDisabled(false);
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 	}
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 07/02/00 //DEADCODE JIM 16/11/99 
//DEADCODE DAW 07/02/00 
//DEADCODE DAW 07/02/00 	return TRUE;  // return TRUE unless you set the focus to a control
//DEADCODE DAW 07/02/00 	              // EXCEPTION: OCX Property Pages should return FALSE
//DEADCODE DAW 07/02/00 }
