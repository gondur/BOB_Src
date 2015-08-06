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

// RowanDialog: // SelTrg.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "SelTrg.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// SelectTarget dialog


RDialog*	SelectTarget::Make(int squad, int tab, int unitdisplaylevel, SelectTargetMode selecttargetmode)
{
	return
		MakeTopDialog(::Place(POSN_MIN,POSN_MIN),
			DialBox(FIL_D_BLANK,new SelectTarget(squad, tab, unitdisplaylevel, selecttargetmode))
			);
}


SelectTarget::SelectTarget(int squad, int tab,int unitdisplaylevel, SelectTargetMode selecttargetmode,CWnd* pParent /*=NULL*/)
	: RowanDialog(SelectTarget::IDD, pParent)
{
#ifndef	BOB_DEMO_VER

	//{{AFX_DATA_INIT(SelectTarget)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	MainToolBar().DialoguesVisible(false);
	TitleBarPtr().DialoguesVisible(false);

	currsquad = squad;
	currtab = tab;
	m_pView->m_mapdlg.TargetSelectSink=this;
	m_pView->m_mapdlg.TargetSelectMode=selecttargetmode;
	udl = unitdisplaylevel ;


//DeadCode JIM 26Sep00 	Save_Data_tmp = Save_Data;
//DeadCode JIM 26Sep00 	Save_Data.mapfilters %=	FILT_RAFSAG;		//never want raf on sel trg

//DeadCode JIM 26Sep00 	if (lwonly)
//DeadCode JIM 26Sep00 	{
//DeadCode JIM 26Sep00 		Save_Data.mapfilters = 0;
//DeadCode JIM 26Sep00 		Save_Data.mapfilters|=FILT_LWSAG;
//DeadCode JIM 26Sep00 	}
	m_pView->m_mapdlg.Invalidate();

#endif

}
void	SelectTarget::SetTargetIndex(int trgindex)
{
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
		UByte		wadernum;
	 	UByte		gruppennum;
		Gruppen* sq = Node_Data[(SquadNum)pk[currsquad].squadnum];
		wadernum = sq->wadernum;
 		gruppennum = sq->gruppennum;
		int i =0;
		while (i < pk.squadlist)
		{
			sq = Node_Data[(SquadNum)pk[i].squadnum];
			if	(	(	(udl == PackageList::DISPLAY_STAFFEL)
						&&	(i == currsquad)
					)
					||
					(	(udl == PackageList::DISPLAY_GRUPPE)
						&&	(gruppennum == sq->gruppennum)
						&&	(wadernum == sq->wadernum)
					)
					||
					(	(udl == PackageList::DISPLAY_GESCHWADER)
						&&	(wadernum == sq->wadernum)
					)
				)
				   pk[i].targetindex = trgindex;

			i++;
		}
		//Find target zero waypoint and get alt.
		//Try to find trgindex waypoint and if so skip
		int targetalt=METRES3000;
		for (info_waypointPtr wp=Persons2::ConvertPtrUID(Todays_Packages.pack[Todays_Packages.hipack].route);wp;wp=Persons2::ConvertPtrUID(wp->nextwp))
			if (wp->applywave.Evaluate()==trgindex)
			{
				targetalt=0;
				break;
			}
			else
				if (wp->applywave.Evaluate()==0)
				{
					Coords3D c;
					wp->position.EvalW(c);
					targetalt=c.Y;
				}
		if (targetalt)
			pk.AddAttackWP(trgindex,pk[currsquad].method,targetalt);
		AttackMethodField	am=pk.ScanAttackMethods();
		pk.ReorderPackage(am);
		pk.RecalcRoutePositionsAndTime();
}
void	SelectTarget::RefreshData(int targetid)
{
#ifndef	BOB_DEMO_VER

	if ((targetid<0))											//DAW 11Jul00
		return;													//DAW 11Jul00

	UniqueIDBand b=Persons2::getbandfromUID((UniqueID)targetid);

	if (b != SagBAND)
	{
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
		if (pk.packagetarget[pk[currsquad].targetindex].currentid != (UniqueID)targetid)
		{
			int i = 0;
			while (			( i <Profile::MAX_TARGETS) 
						&&	(pk.packagetarget[i].currentid != UID_NULL)
						&&	(pk.packagetarget[i].currentid != targetid)
					)
				i++;
			if (i!=Profile::MAX_TARGETS)
			{
			   pk.packagetarget[i] = (UniqueID)targetid;
			   SetTargetIndex(i);
 			}else
				pk.packagetarget[pk[currsquad].targetindex].currentid = (UniqueID)targetid;
		}
//DEADCODE RDH 08/05/00 		MainToolBar().DialoguesVisible(true);
//DEADCODE RDH 08/05/00 		TitleBarPtr().DialoguesVisible(true);

		RDialog*	taskdial = TitleBarPtr().LoggedChild(TitleBar::TASK);
		if (taskdial)
		{
			CRTabs* tab=(CRTabs*)taskdial->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
			tab->SelectTab(currtab);
		}
	}else
	{
		int packnum,sqline;
		if (Todays_Packages.GetACSquadEntry((UniqueID)targetid,packnum,sqline))
		{
			Todays_Packages.pack[Todays_Packages.hipack].ReassignTo((UniqueID)targetid, true);;
		}
	}

	Todays_Packages.SetTaskData();
#endif
	OnOK();

}
void SelectTarget::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelectTarget)
	DDX_Control(pDX, IDC_RCOMBOTARGET, m_IDC_RCOMBOTARGET);
	DDX_Control(pDX, IDC_RBUTTONRESET, m_IDC_RBUTTONRESET);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelectTarget, CDialog)
	//{{AFX_MSG_MAP(SelectTarget)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelectTarget message handlers

BEGIN_EVENTSINK_MAP(SelectTarget, CDialog)
    //{{AFX_EVENTSINK_MAP(SelectTarget)
	ON_EVENT(SelectTarget, IDC_RBUTTONCANCEL, 1 /* Clicked */, OnClickedRbuttoncancel, VTS_NONE)
	ON_EVENT(SelectTarget, IDC_RBUTTONRESET, 1 /* Clicked */, OnClickedRbuttonreset, VTS_NONE)
	ON_EVENT(SelectTarget, IDC_RCOMBOTARGET, 1 /* TextChanged */, OnTextChangedRcombotarget, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void SelectTarget::OnClickedRbuttoncancel() 
{
#ifndef	BOB_DEMO_VER

	m_pView->m_mapdlg.TargetSelectMode=STM_NORMAL;
	m_pView->m_mapdlg.TargetSelectSink=NULL;
	MainToolBar().DialoguesVisible(true);
	TitleBarPtr().DialoguesVisible(true);
//DeadCode JIM 26Sep00 	Save_Data = Save_Data_tmp;
	m_pView->m_mapdlg.Invalidate();

#endif
	CDialog::OnOK();
}

void SelectTarget::OnOK()
{
#ifndef	BOB_DEMO_VER
	m_pView->m_mapdlg.TargetSelectMode=STM_NORMAL;
	m_pView->m_mapdlg.TargetSelectSink=NULL;
	MainToolBar().DialoguesVisible(true);
	TitleBarPtr().DialoguesVisible(true);
//DeadCode JIM 26Sep00 	Save_Data = Save_Data_tmp;
	m_pView->m_mapdlg.Invalidate();
#endif
	OnClickedRbuttonreset() ;
}
void SelectTarget::OnClickedRbuttonreset() 
{
#ifndef	BOB_DEMO_VER

	if (currindex > 0)
	{
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];

		TargetGroup* trg = Node_Data[pk.packagetarget[pk[currsquad].targetindex].currentid];

		pk.packagetarget[pk[currsquad].targetindex].currentid = trg->secondaries[currindex -1];
	}
	if (currtab >= 0)
	{
		RDialog*	taskdial = TitleBarPtr().LoggedChild(TitleBar::TASK);
		if (taskdial)
		{
			CRTabs* tab=(CRTabs*)taskdial->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
			tab->SelectTab(currtab);
		}
	}
#endif
	CDialog::OnOK();
}

void SelectTarget::OnTextChangedRcombotarget(LPCTSTR Caption, short index) 
{
	currindex = index;	
}

BOOL SelectTarget::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRCombo* combo;
	CRButton*	but = GETDLGITEM(IDC_RBUTTONRESET);


	combo=GETDLGITEM(IDC_RCOMBOTARGET);
	if  (	(currtab == -1)
		||	(RFullPanelDial::gameside != RFullPanelDial::SIDE_LW)
		)

	{
		but->ShowWindow(false);
		combo->ShowWindow(false);
		currindex = 0;
	}else
	{

		but->ShowWindow(true);
		combo->ShowWindow(true);
		combo->Clear();
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
		int ti= pk[currsquad].targetindex;
		if (ti<0) ti=0;
		TargetGroup* trg;
		trg = Node_Data[pk.packagetarget[ti].currentid];
 		combo->AddString(GetTargName(trg->uid));

		for (int i=0; i < TargetGroup::MAXSECONDARIES;i++)
		{
			if	(	(trg)	&&	(trg->secondaries[i]))
				combo->AddString(GetTargName(trg->secondaries[i]));
		}
		combo->SetIndex(0);
		currindex = 0;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
