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

// RowanDialog: // Supply.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "Supply.h"
#include "RCombo.h"
#include "rlistbox.h"
//TEMPCODE DAW 13/04/00 #include "dossier.h"
//TEMPCODE DAW 13/04/00 #include "general.h"
//TEMPCODE DAW 13/04/00 #include "damage.h"
//TEMPCODE DAW 13/04/00 #include "notes.h"
//TEMPCODE DAW 13/04/00 #include "Author.h"
//TEMPCODE DAW 13/04/00 #include "persons2.h"
//TEMPCODE DAW 13/04/00 #include "nodebob.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSupply dialog


CSupply::CSupply(int index, CWnd* pParent /*=NULL*/)
	: RowanDialog(CSupply::IDD, pParent)
//DEADCODE  08/02/00 	,
//DEADCODE  08/02/00 	target(new LWDirectivesResultsTargetList[LWDirectivesResultsTargetList::MAX_TARGETS])
{

	sortindex = 0;
	currrow = -1;	
	panel = index;
	dr = new LWDirectivesResults;

	//{{AFX_DATA_INIT(CSupply)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}
CSupply::~CSupply()
{
	if (dr)
		delete dr;

//DEADCODE  08/02/00 	delete []target;
}

void CSupply::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSupply)
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_SORTCOMBO,m_IDC_SORTCOMBO);
	DDX_Control(pDX,IDC_RLISTBOXCTRL1,m_IDC_RLISTBOXCTRL1);
//DEADCODE JIM 16/12/99 	DDX_Control(pDX,IDC_AUTHORISE,m_IDC_AUTHORISE);
//DEADCODE JIM 30/11/99 	DDX_Control(pDX,IDC_DOSSIER,m_IDC_DOSSIER);
	DDX_Control(pDX, IDC_RBUTTONAUTHORISE, m_IDC_RBUTTONAUTHORISE);
	DDX_Control(pDX, IDC_RBUTTONDETAILS, m_IDC_RBUTTONDETAILS);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
}


BEGIN_MESSAGE_MAP(CSupply, CDialog)
	//{{AFX_MSG_MAP(CSupply)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void	CSupply::ReDrawButtons()
{

	CRButton*	dosbut = GETDLGITEM(IDC_RBUTTONDETAILS);
	CRButton*	authbut = GETDLGITEM(IDC_RBUTTONAUTHORISE);
	if (currrow != -1)
	{
		dosbut->SetForeColor(RGB(255,255,0));
		dosbut->SetDisabled(false);
		if (Node_Data.GotBadWeatherPeriod())
			authbut->ShowWindow(SW_HIDE);
	  		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
			{
				authbut->ShowWindow(true);
				authbut->SetForeColor(RGB(255,255,0));
				authbut->SetDisabled(false);
			}else
			{
				authbut->ShowWindow(false);
			}

	}
	else
	{
		dosbut->SetForeColor(RGB(160,160,80));
		dosbut->SetBackColor(RGB(160,160,80));
		dosbut->SetDisabled(true);
		if (Node_Data.GotBadWeatherPeriod())
			authbut->ShowWindow(SW_HIDE);
	  		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
			{
				authbut->ShowWindow(true);
				authbut->SetForeColor(RGB(160,160,80));
				authbut->SetBackColor(RGB(160,160,80));
				authbut->SetDisabled(true);
			}else
			{
				authbut->ShowWindow(false);
			}
	}

}


//DEADCODE  08/02/00 int	CSupply::FillPanel(LWDirectivesResults::TargetList* target, int panel)
int	CSupply::FillPanel( int panel)
{
	int uidbandstart, uidbandend;
	switch (panel)
	{
	default_neverreferenced;
	case	Target::TT_FIGHTERAF:
		{
			uidbandstart = 	RAF_FighterAFBAND;
			uidbandend =  CLRadarBAND;
			break;
		}
	case	Target::TT_DOCKS:
		{
			uidbandstart = 	DocksBAND;
			uidbandend =  CityBAND;										//RDH 12Oct00
			break;
		}
	case	Target::TT_CHAINHOME:
		{
			uidbandstart = 	CLRadarBAND;
			uidbandend =  LUF_FighterLF2BAND;
			break;
		}
	case	Target::TT_CONVOY:
		{
			uidbandstart = 	BritBoatBAND;
			uidbandend =  GermBoatBAND;
			break;
		}
	case	Target::TT_LONDON:
		{
			uidbandstart = 	PowerStationBAND;
			uidbandend =  PortBAND;										//RDH 30Sep00
			break;
		}
	case	Target::TT_SPITASSEMBLY:
		{
			uidbandstart = 	PowerStationBAND;
			uidbandend =  DocksBAND;
			break;
		}
   
	}
	int currtrg;
	currtrg = LWDirectivesResults::FillTargetList(dr->target,uidbandstart, uidbandend, panel);
	return (currtrg);

}
int	LWDirectivesResults::FillTargetList(TargetList* target,int uidbandstart, int uidbandend, int trgtype)
{


	int i = 0, uid= uidbandstart, currtrg = 0;
	while 	(i < LWDirectivesResults::MAX_TARGETS)
	{
		target[i].priority = 30000;	//Target::TP_MAX;
		target[i++].target = (UniqueID)IllegalBAND;

	}


	while (		(uid < uidbandend)
		&&	(currtrg < LWDirectivesResults::MAX_TARGETS)
		   )
	{
		TargetGroup* trg;
		trg = Node_Data[(UniqueID)uid];
		ItemBasePtr p;
		p=Persons2::ConvertPtrUID((UniqueID)uid);
		//only statics and convoys in the world have a pointer

//DeadCode RDH 12Oct00 		if (		(trg) && (p) && uid!=UID_AF_NEWCASTLE
//DeadCode RDH 12Oct00 				&&	(		(trgtype != Target::TT_LONDON)
//DeadCode RDH 12Oct00 						||	(		(trgtype == Target::TT_LONDON)
//DeadCode RDH 12Oct00 								&&	(trg->London())
//DeadCode RDH 12Oct00 							)
//DeadCode RDH 12Oct00 					)
//DeadCode RDH 12Oct00 			)
//
//only allow trg insert if (trgtype and trg is london) or (trgtype and trg is not london)
		if (		(trg) && (p) && uid!=UID_AF_NEWCASTLE
				&&	(		(trg->London() == (trgtype == Target::TT_LONDON))	//RDH 12Oct00
					)
			)
		{
			currtrg = InsertTarget(target,(UniqueID)uid, currtrg,uidbandstart);
		}
		uid++;
	}



	return (currtrg);
}
int LWDirectivesResults::TargetX(int i)
{
	ItemBasePtr p;
  	p=Persons2::ConvertPtrUID((UniqueID)i);
	return(p->World.X);
}
int	LWDirectivesResults::InsertTarget(TargetList* target, UniqueID uid, int currtrg, int uidbandstart)
{
	int i = 0, trgpriority;
	TargetGroup*	tg = Node_Data[uid];

//DeadCode JIM 3Jul00 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		trgpriority = tg->falsepriority;   //PlayerPriority();//
//DeadCode JIM 3Jul00 	else
//DeadCode JIM 3Jul00 		trgpriority = tg->truepriority;

	if (		(tg->knownstatus >= Target::TS_NEARLYDESTROYED)
			&&	(tg->knownstatus < Target::TS_MAXIMUM)
	   )
		trgpriority = trgpriority + Target::TP_MAX;

	ItemBasePtr p;
 	p=Persons2::ConvertPtrUID((UniqueID)uid);
	

	while  (		(i < currtrg)
				&&	(		(target[i].priority  < 	trgpriority)
						||	(			(target[i].priority  ==	trgpriority)
								&&	(TargetX(target[i].target) > p->World.X)
								&&	(uidbandstart == BritBoatBAND)
							)
					)
			)
		i++;

	for (int j = LWDirectivesResults::MAX_TARGETS-1; j > i;j--)
		target[j] = target[j-1];

	
	target[i].target = uid;
	target[i].priority = trgpriority;

	currtrg++;
	return(currtrg);
}


void	CSupply::ReDraw(int	numoftargets)
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(TARGETFIELDWIDTH+60); //MIKE
	//rlistbox->AddColumn(70);
	//rlistbox->AddColumn(70);

   if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
   {
		rlistbox->AddString(RESSTRING(TARGETS),0);
   }else
   {
		rlistbox->AddString(RESSTRING(ASSETS),0);
   }

 	rlistbox->AddString(RESSTRING(TYPE),1);
  	rlistbox->AddString(RESSTRING(STATUS),2);



	for (int i = 0; i < numoftargets; i++)
	{
		rlistbox->AddString(GetTargName((UniqueID)dr->target[i].target),0);

		int j;
		j= Node_Data[(UniqueID)dr->target[i].target].PlayerType();
//DeadCode JIM 30Oct00 		if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//DeadCode JIM 30Oct00 				&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
//DeadCode JIM 30Oct00 			)
//DeadCode JIM 30Oct00 			j = Node_Data[(UniqueID)dr->target[i].target].falsetargtype;
//DeadCode JIM 30Oct00 	   else
//DeadCode JIM 30Oct00 			j = Node_Data[(UniqueID)dr->target[i].target].truetargtype;
//DeadCode JIM 3Jul00 		if ( j == Target::TT_AS_KNOWN)
//DeadCode JIM 3Jul00 			j = Node_Data[(UniqueID)dr->target[i].target].truetargtype;
 		rlistbox->AddString(RESLIST(TT_AS_KNOWN, j),1);


//added the damage status												//RDH 16Aug00

		TargetNoDetail* trg = Node_Data[(UniqueID)dr->target[i].target];
		int trgtype;
		if (trg)
		{
			if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//					&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
				)
			{
				j = trg->PlayerStatus();
				trgtype = trg->PlayerType();
			}else
			{
				j = trg->truestatus;
				trgtype = trg->truetargtype;
				if (	j>Target::TS_NEARLYDESTROYED
				&& (trgtype==Target::TT_CHAINHOME || trgtype==Target::TT_CHAINLOW)
				&& 	TargetRadarPtr(Node_Data[(UniqueID)dr->target[i].target])->mobileunit
				)
				j=Target::TS_FLAG4;
			}
			if	(j == Target::TS_FLAG_UNKNOWN)	//had <0 check								//JIM 3Jul00
				rlistbox->AddString(RESSTRING(TT_UNKNOWN),2);
			else if (j == Target::TS_FLAG4)
				rlistbox->AddString(RESSTRING(SHP_RADTRK),2);
			else
			{
				if		(j >= Target::TS_NEARLYDESTROYED)		j = 3;
				elseif	(j>Target::TS_BADDAMAGE)				j=2;
				elseif	(j>Target::TS_LIGHTDAMAGE)				j=1;
				else											j=0;
				rlistbox->AddString(RESLIST(UNDAMAGED, j),2);
			}
		}else
				rlistbox->AddString("",2);
	}

	   
}
/////////////////////////////////////////////////////////////////////////////
// CSupply message handlers

BOOL CSupply::OnInitDialog() 
{
	CDialog::OnInitDialog();
	


//DEADCODE  08/02/00 	int	numoftargets = FillPanel(target, panel);
	int	numoftargets = FillPanel( panel);
	ReDraw(numoftargets);

	ReDrawButtons();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CSupply, CDialog)
    //{{AFX_EVENTSINK_MAP(CSupply)
//DEADCODE JIM 30/11/99 	ON_EVENT(CSupply, IDC_DOSSIER, 1 /* Clicked */, OnClickedDossier, VTS_NONE)
	ON_EVENT(CSupply, IDC_SORTCOMBO, 1 /* TextChanged */, OnTextChangedSortcombo, VTS_BSTR VTS_I2)
	ON_EVENT(CSupply, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(CSupply, IDC_AUTHORISE, 1 /* Clicked */, OnClickedAuthorise, VTS_NONE)
	ON_EVENT(CSupply, IDC_RBUTTONDETAILS, 1 /* Clicked */, OnClickedRbuttondetails, VTS_NONE)
	ON_EVENT(CSupply, IDC_RBUTTONAUTHORISE, 1 /* Clicked */, OnClickedRbuttonauthorise, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSupply::OnClickedDossier() 
{
//DEADCODE JIM 16/12/99 	if  (		(currrow != -1)
//DEADCODE JIM 16/12/99 			&&	(target[currrow].target != UID_NULL)
//DEADCODE JIM 16/12/99 		)
//DEADCODE JIM 16/12/99 	{
//DEADCODE JIM 16/12/99 		m_pView->ZoomToUID(target[currrow].target,m_pView->m_zoom);
//DEADCODE JIM 16/12/99 		m_pView->m_mapdlg.ResetIcon(target[currrow].target);
//DEADCODE JIM 16/12/99 		MainToolBar().OpenDossier(target[currrow].target);
//DEADCODE JIM 16/12/99 //		CTargetDossier::MakeSheet(CRect(180,400,0,0),target[currrow].target);
//DEADCODE JIM 16/12/99 		OnOK();
//DEADCODE JIM 16/12/99 
//DEADCODE JIM 16/12/99 	}
}

void CSupply::OnTextChangedSortcombo(LPCTSTR text, short index) 
{

//DEADCODE JIM 16/12/99   	CRCombo* combo;
//DEADCODE JIM 16/12/99 	combo=GETDLGITEM(IDC_SORTCOMBO);
//DEADCODE JIM 16/12/99 	sortindex = combo->GetIndex();
//DEADCODE JIM 16/12/99 	if (sortindex > 2)
//DEADCODE JIM 16/12/99 		sortindex++;
//DEADCODE JIM 16/12/99 	SortIntell();
//DEADCODE JIM 16/12/99 	ReDraw();
//DEADCODE JIM 16/12/99 	ReDrawButtons();
		 
}

void CSupply::OnSelectRlistboxctrl1(long row, long column) 
{
	if (row!=0)
		currrow=row-1;	
	ReDrawButtons();
}

void CSupply::OnClickedAuthorise() 
{
//DEADCODE JIM 30/11/99 	if  (		(currrow != -1)
//DEADCODE JIM 30/11/99 			&&	(target[currrow].target != UID_NULL)
//DEADCODE JIM 30/11/99 		)
//DEADCODE JIM 30/11/99 	{
//DEADCODE JIM 30/11/99 		MainToolBar().OpenLoadProfile(target[currrow].target);		  //rdh 29/04/99

//		int	pack=Todays_Packages.NewPackage(target[currrow].target);
//		if (pack>=0)
//		{
//			m_pView->ZoomToUID(target[currrow].target,m_pView->m_zoom);
//			m_pView->m_mapdlg.ResetIcon(target[currrow].target);
//			CMissionFolder::Make();
//			CMissionFolder::OpenOneProfile(pack);
//		}

		OnOK();
//DEADCODE JIM 30/11/99 
//DEADCODE JIM 30/11/99 	}
	
}

void CSupply::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CSupply::OnClickedRbuttondetails() 
{
#ifndef	BOB_DEMO_VER

	if  (		(currrow != -1)
			&&	(dr->target[currrow].target != UID_NULL)
		)
	{
		m_pView->ZoomToUID(dr->target[currrow].target,m_pView->m_zoom);
		m_pView->m_mapdlg.ResetIcon(dr->target[currrow].target);
		MainToolBar().OpenDossier(dr->target[currrow].target);
		OnOK();

	}
#endif
	
}

void CSupply::OnClickedRbuttonauthorise() 
{
#ifndef	BOB_DEMO_VER
 	if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
			&&	(currrow != -1)
		)
	{
		
		int packnum=Todays_Packages_NewPackage(dr->target[currrow].target,MMC.directives.lw.userprofiles[Directives::LW::ATTACK]);
		if (packnum < 0)
			RDialog::RMessageBox(IDS_WARNING, IDS_NOAIRCRAFTAVAIL,NULL,NULL,IDS_CONTINUE);
		else
		{
			Todays_Packages[packnum].CalcRoutePositionsAndTime();
			MainToolBar().OnClickedMissionfolder();
			Todays_Packages.InvalidateRoute(&Todays_Packages[packnum],true,true);
		}
	}
#endif	
}
