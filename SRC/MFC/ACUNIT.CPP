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

// RowanDialog: // AcUnit.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "AcUnit.h"
#include "package.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// AircraftUnit dialog

 // 11/02/00
RDialog*	AircraftUnit::Make(int oldunit, TypesToList typestolist, int tab, int am, int unitdisplaylevel)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_UNIT,new AircraftUnit(oldunit,typestolist,tab,am,unitdisplaylevel))
			);
}


AircraftUnit::AircraftUnit(int oldunit, TypesToList typestolist, int tab, int am, int unitdisplaylevel, CWnd* pParent /*=NULL*/)
	: RowanDialog(AircraftUnit::IDD, pParent)
{
	//{{AFX_DATA_INIT(AircraftUnit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->oldunit = oldunit;
//DeadCode JIM 14Nov00 	acisfighter = fighter;
	currtab = tab;
	attackmethod = am;
//DeadCode JIM 14Nov00 	me110isbomber = me110bomber;
	udisplayl = unitdisplaylevel;
	this->typestolist=typestolist;
}


void AircraftUnit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AircraftUnit)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AircraftUnit, CDialog)
	//{{AFX_MSG_MAP(AircraftUnit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AircraftUnit message handlers
static bool	SqIsAvail(int gruppindex,AircraftUnit::TypesToList typestolist)
{
	Gruppen& gruppe=Node_Data.gruppe[gruppindex];
	if (gruppe.Busy())
		return false;
	//enum	TypesToList	{TTL_RECONN,TTL_JU87,TTL_110,TTL_FIGHTER,TTL_BOMBER,TTL_SPITFIRE,TTL_HURRICANE};
 	Geshwader&		geschwader=Node_Data.geschwader[gruppe.wadernum];
	switch (typestolist)
	{
	case AircraftUnit::TTL_RECONN1:
		if (gruppe.acavail < 1)		return false;
	case AircraftUnit::TTL_RECONN2:
		if (gruppe.acavail < 2)		return false;
	case AircraftUnit::TTL_RECONN3:
		if (gruppe.acavail < 3)		return false;
	{
		if (!geschwader.reconn) 
			return false;
	}
	break;
	case AircraftUnit::TTL_JU87:
	{
		if (gruppe.acavail<gruppe.MIN_GRUPPEAC)
			return false;
		if (geschwader.aircrafttype!=PT_JU87)
			return false;
	}
	break;
	case AircraftUnit::TTL_110:
	{
		if (gruppe.acavail<gruppe.MIN_GRUPPEAC)
			return false;
		if (geschwader.aircrafttype!=PT_ME110)
			return false;
	}
	break;
	case AircraftUnit::TTL_BOMBER:
	{
		if (gruppe.acavail<gruppe.MIN_GRUPPEAC)
			return false;
		if (geschwader.aircrafttype<PT_GER_NONFLY)
			return false;
	}
	break;
	case AircraftUnit::TTL_FIGHTER :
	{
		if (gruppe.acavail<gruppe.MIN_GRUPPEFIGHTERS)
			return false;
		if (geschwader.aircrafttype!=PT_ME110 && geschwader.aircrafttype!=PT_ME109)
			return false;
	}
	break;
	}
	return true;
}
BOOL AircraftUnit::OnInitDialog() 
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

	
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];



//DeadCode JIM 20Oct00 		int acavail = 0;
	int j = 0;
	while (Node_Data.gruppe[j].squadron != SQ_ZERO)
	{
		if (SqIsAvail(j, typestolist))
		{
			Squadron* sq  = Node_Data[Node_Data.gruppe[j].squadron];
			CString name = sq->ShortName() + "/";
			name = name + sq->SubName();
			rlistbox->AddString(name,0);
			rlistbox->AddString(RESLIST(SPIT_A, sq->AcType()),1);
			rlistbox->AddString(CSprintf("%i", sq->acavail),2);
			rlistbox->AddString(GetTargName(sq->homeairfield),3);
			

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



BEGIN_EVENTSINK_MAP(AircraftUnit, CDialog)
    //{{AFX_EVENTSINK_MAP(AircraftUnit)
	ON_EVENT(AircraftUnit, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(AircraftUnit, IDC_RLISTBOXCTRL1, 2 /* DoubleSelect */, OnDoubleSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void AircraftUnit::OnSelectRlistboxctrl1(long row, long column) 
{

	if (row)
		newunit = (int)(row );
	

}
void AircraftUnit::OnOK() 
{
#ifndef	BOB_DEMO_VER

	if (newunit > 0)
	{
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];

		int j = 0, k = 0;
		while  (		(Node_Data.gruppe[j].squadron != SQ_ZERO)
					&&		(k != newunit)
				)
		{
			if (SqIsAvail(j, typestolist))
			{
				k++;
			}
			j++;
		}
		j = j + SQ_LW_START;
		if (k==newunit)
		{
			
			Todays_Packages.InvalidateRoute(&pk,true,true);
			if ( oldunit < 0)
			{//add group, we always add in groups, don't get here for other cases
				Profile::BetterRule	br = Profile::BR_WIDESTPOSSIBLE;
				pk.AddNumerousSquadrons(-3,(Profile::AttackMethod)attackmethod,(SquadNum)j,br);
	//DEADCODE RDH 04/04/00 			pk.AddSquadron(-3, (Profile::AttackMethod)attackmethod,pk.packagetarget[0].currentid,(SquadNum)j);
			}else
			{//		replace oldunit with new

					if (oldunit >= 0)
					{
						SquadNum	sqnum;
						sqnum = pk[oldunit].squadnum;

						int oldactype = Node_Data[(SquadNum)pk[oldunit].squadnum].AcType();
						int newactype = Node_Data[(SquadNum)j].AcType();

						if (		(oldactype <= PT_JU87)
								&&	(newactype > PT_JU87)
							)
					   		pk.attackmethod =  Profile::AM_LEVELBOMB;

						if (		(oldactype <= PT_JU87)
								&&	(newactype > PT_JU87)
							)
					   		pk.attackmethod =  Profile::AM_DIVEBOMB;


						int i = pk.squadlist - 1;
						int numstaffel = 0;int oldindex;
						Profile::AttackMethod	am;
						while (i >= 0)
						{
							if (pk[i].squadnum == sqnum)
							{	oldindex=pk[i].targetindex;
								am = pk[i].method;
								numstaffel++;
								pk.DeleteSquadAt(i);
							}
							i--;
						}	i=pk.squadlist;
						if (typestolist>=AircraftUnit::TTL_RECONN1)
							pk.AddNumerousSquadrons(1+typestolist-AircraftUnit::TTL_RECONN1,(Profile::AttackMethod)attackmethod,(SquadNum)j, Profile::BR_WIDESTPOSSIBLE);
						else
							pk.AddNumerousSquadrons(-numstaffel,(Profile::AttackMethod)attackmethod,(SquadNum)j, Profile::BR_WIDESTPOSSIBLE);
						for(int max=pk.squadlist;i<max;i++)
							pk[i].targetindex=oldindex;
					}


			}
			//DeadCode JIM 7Nov00 		pk.ReShareSecondaries();								//JIM 28Aug00
			typedef	Profile::AttackMethod	AttackMethod;
			MAKEFIELD(AttackMethod,Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);
			AttackMethodField	am=pk.ScanAttackMethods();
			pk.ReorderPackage(am);
			pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
			Todays_Packages.InvalidateRoute(&pk,true,true);
		}
	}
	Todays_Packages.SetTaskData();
	RDialog*	taskdial = TitleBarPtr().LoggedChild(TitleBar::TASK);
	if (taskdial)
	{
		CRTabs* tab=(CRTabs*)taskdial->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
		tab->SelectTab(0);
		tab=(CRTabs*)taskdial->fchild->fchild->GetDlgItem(IDJ_TABCTRL);
		tab->SelectTab(currtab);
	}

	CDialog::OnOK();
#endif	
}

void AircraftUnit::OnDoubleSelectRlistboxctrl1(long row, long column) 
{
	if (row)
	{
		newunit = (int)(row );
		OnOK();
	}
	
}
