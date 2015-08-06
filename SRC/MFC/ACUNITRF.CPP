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

// RowanDialog: // AcUnitRF.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "AcUnitRF.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// AcUnitRAF dialog


RDialog*	AcUnitRAF::Make(int unit, bool spitfire, int tab, int am)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_BLANK,new AcUnitRAF(unit,spitfire, tab, am))
			);
}


AcUnitRAF::AcUnitRAF(int unit, bool spitfire, int tab, int am,CWnd* pParent /*=NULL*/)
	: RowanDialog(AcUnitRAF::IDD, pParent)
{
	//{{AFX_DATA_INIT(AcUnitRAF)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	oldunit = unit;
	acisspitfire = spitfire;
	currtab = tab;
	attackmethod = am;

}


void AcUnitRAF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AcUnitRAF)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AcUnitRAF, CDialog)
	//{{AFX_MSG_MAP(AcUnitRAF)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AcUnitRAF message handlers

BEGIN_EVENTSINK_MAP(AcUnitRAF, CDialog)
    //{{AFX_EVENTSINK_MAP(AcUnitRAF)
	ON_EVENT(AcUnitRAF, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(AcUnitRAF, IDC_RLISTBOXCTRL1, 2 /* DoubleSelect */, OnDoubleSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void AcUnitRAF::OnSelectRlistboxctrl1(long row, long column) 
{
	if (row)
		newunit = (int)(row );

	
}

BOOL AcUnitRAF::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	newunit = -1;
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(100);	 
	rlistbox->AddColumn(70);
	rlistbox->AddColumn(50);
	rlistbox->AddColumn(2);		//TARGETFIELDWIDTH);
	rlistbox->AddString(RESSTRING(UNIT),0);
	rlistbox->AddString(RESSTRING(TYPE),1);
	rlistbox->AddString(RESSTRING(SIZE),2);
 	rlistbox->AddString(RESSTRING(BASE),3);


	


//DeadCode JIM 20Oct00 		int acavail = 0;
	int j = 0;
	sqlist=0;
	while (Node_Data.squadron[j].squadron != SQ_ZERO)
	{
		Squadron* sq  = Node_Data[Node_Data.squadron[j].squadron];
		int actype = sq->AcType();

		UniqueID uid = Node_Data.squadron[j].homeairfield;
		TargetFighterField* af;
		af = Node_Data[uid];
	 	TargetSectorField*	sectorfield = af->getsectoraf();

		if  (	(	(	(acisspitfire) &&	(	(actype == PT_SPIT_A)
												||
												(actype == PT_SPIT_B)	
											 )
					)
					||
					(	(!acisspitfire) &&	  (	(actype == PT_HURR_A)
												||
												(actype == PT_HURR_B)	
											 )
					)
				)
	 			&&	(!sq->Busy())
				&&	(sectorfield->groupname != IDS_GROUP_13)
			)
		{
			CString name = sq->FullName();
			rlistbox->AddString(name,0);
			rlistbox->AddString(RESLIST(SPIT_A, actype),1);
			rlistbox->AddString(CSprintf("%i", sq->acavail),2);
			rlistbox->AddString(CSprintf("%s", GetTargName(sq->homeairfield)),3);
			sqlist|=sq->squadron;										//JIM 04/07/01
			

		}
		j++;
	}
	rlistbox->AddString(RESSTRING(CANCEL),0);
	rlistbox->AddString("",1);
	rlistbox->AddString("",2);
	rlistbox->AddString("",3);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void AcUnitRAF::OnOK() 
{
#ifndef	BOB_DEMO_VER
	
//	if ( oldunit < 0)
//		add unit to package
//	else
//		replace oldunit with new
	int l_newunit = newunit;
	if (l_newunit > 0)
	{
		int j = 0, k = 0;
		while  (		(Node_Data.squadron[j].squadron != SQ_ZERO)
				&&		(k != l_newunit)
				)
		{
			Squadron* sq  = Node_Data[Node_Data.squadron[j].squadron];
		int actype = sq->AcType();
//deadcode JIM 04/07/01			if  (	(	(	(acisspitfire) &&	(	(actype == PT_SPIT_A)
//deadcode JIM 04/07/01													||
//deadcode JIM 04/07/01													(actype == PT_SPIT_B)	
//deadcode JIM 04/07/01												 )
//deadcode JIM 04/07/01						)
//deadcode JIM 04/07/01						||
//deadcode JIM 04/07/01						(	(!acisspitfire) &&	  (	(actype == PT_HURR_A)
//deadcode JIM 04/07/01													||
//deadcode JIM 04/07/01													(actype == PT_HURR_B)	
//deadcode JIM 04/07/01												 )
//deadcode JIM 04/07/01						)
//deadcode JIM 04/07/01					)
//deadcode JIM 04/07/01		 			&&	(!sq->Busy())	//NO CHECK FOR GRP 13!!
//deadcode JIM 04/07/01				)
			if (sqlist[sq->squadron])										//JIM 04/07/01
			{
				k++;
			}
			j++;
		}
		if (k==l_newunit)
		{
			Squadron* sq  = Node_Data[Node_Data.squadron[j].squadron];
			if (sq->Busy())
			{	//ok... found right squad, but now they are busy!
				k=-1;
				Make(oldunit,acisspitfire,currtab,attackmethod);
			}
		}
		if (k==l_newunit)
		{
			j = j + SQ_BR_START;
			Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];


			Todays_Packages.InvalidateRoute(&pk,true,true);

			if (oldunit >= 0)
			{
				((BritSquadron&) pk[oldunit].Squadron()).usedacbits=0;	//JIM 14Nov00
				pk[oldunit].SetSquad((SquadNum)j);
			}else
			{
				if ((Profile::AttackMethod)attackmethod == Profile::AM_ATTACHED)
					pk.IncreaseSubSquadronToSquadron(Profile::AM_DETACHED);
				else
					pk.IncreaseSubSquadronToSquadron(Profile::AM_ATTACHED);

	//DeadCode RDH 9Aug00 			pk.AddSquadron(-1, (Profile::AttackMethod)attackmethod,pk.packagetarget[0].currentid,(SquadNum)j);
	//make method same as 1st																		//RDH 9Aug00
				pk.AddSquadron(-1, pk[0].method, pk.packagetarget[0].currentid,(SquadNum)j);

			}
			Todays_Packages.SetRAFTaskData();
			typedef	Profile::AttackMethod AttackMethod;
			MAKEFIELD(AttackMethod,Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);
			AttackMethodField	am={0};//pk.ScanAttackMethods();
			pk.ReorderPackage(am);
			pk.packagetakeoff=pk[0].Squadron().homeairfield;
			pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
			Todays_Packages.CheckHilightValid();
			Todays_Packages.InvalidateRoute(&pk,true,true);

			RDialog*	taskdial = TitleBarPtr().LoggedChild(TitleBar::TASK);
			if (taskdial)
			{
				CRTabs* tab=(CRTabs*)taskdial->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
				tab->SelectTab(0);
				tab=(CRTabs*)taskdial->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
				tab->SelectTab(currtab);
			}

		}
	}

#endif

	CDialog::OnOK();
	
}

void AcUnitRAF::OnDoubleSelectRlistboxctrl1(long row, long column) 
{
	if (row)
	{
		newunit = (int)(row );
		OnOK();
	}

	
}
