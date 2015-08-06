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

// RowanDialog: // LWTaskAc.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "LWTaskAc.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
typedef	Profile::AttackMethod	AttackMethod;
MAKEFIELD (AttackMethod, Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);

/////////////////////////////////////////////////////////////////////////////
// LWTaskAircraft dialog


RDialog*	LWTaskAircraft::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new LWTaskAircraft(0))
			);
}


LWTaskAircraft::LWTaskAircraft(int acnum, CWnd* pParent /*=NULL*/)
	: RowanDialog(LWTaskAircraft::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWTaskAircraft)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	attackmethod = acnum;
	unitdisplaylevel = DISPLAY_GRUPPE;
	me110bomber = true;
}


void LWTaskAircraft::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWTaskAircraft)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RCOMBOATTACKMETHOD, m_IDC_RCOMBOATTACKMETHOD);
	DDX_Control(pDX, IDC_RCOMBOBOMBERTYPE, m_IDC_RCOMBOBOMBERTYPE);
	DDX_Control(pDX, IDC_RSTATICBOMBERSALLOCATED, m_IDC_RSTATICBOMBERSALLOCATED);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWTaskAircraft, CDialog)
	//{{AFX_MSG_MAP(LWTaskAircraft)
	//}}AFX_MSG_MAP
		ON_MESSAGE( WM_SELECTTAB, OnSelectTab)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWTaskAircraft message handlers
void	LWTaskAircraft::OnSelectTab()
{
	Refresh();
}


void	LWTaskAircraft::FillList()
{
		int i=0;
	maxunits = 0;
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];


	UByte		wadernum;
 	UByte		gruppennum;
	Gruppen* sq = Node_Data[(SquadNum)pk[i].squadnum];
	wadernum = sq->wadernum;
 	gruppennum = sq->gruppennum;
	bool forcedisplay = true;
	if (pk.squadlist) 
	{
		do
		{
			sq = Node_Data[(SquadNum)pk[i].squadnum];
//DeadCode JIM 20Oct00 			int am = pk[i].method;
			if (		(pk[i].method == pk.attackmethod)
					&&	(	(forcedisplay)
							||
							(unitdisplaylevel == DISPLAY_STAFFEL)
							||
							(	(unitdisplaylevel == DISPLAY_GRUPPE)
								&&	(		(gruppennum != sq->gruppennum)
										||	(wadernum != sq->wadernum)
									)
							)
							||
							(	(unitdisplaylevel == DISPLAY_GESCHWADER)
								&&	(wadernum != sq->wadernum)
							)
						)
					&&	(i < MAXSQUADS)
				)
			{
				forcedisplay = false;
				wadernum = sq->wadernum;
				gruppennum = sq->gruppennum;
				UnitList[maxunits] = i;

				for (int actype = PT_JU87; actype < PT_VEHICLES;actype++)
						if (sq->AcType() == actype)
							me110bomber = false;
				maxunits++;

			}
			i++;
		}while (i < pk.squadlist);
	}
}

void	LWTaskAircraft::Refresh()
{
  	CRCombo* combo;														//RDH 30/05/00
	int index = Todays_Packages.taskdata.attackmethod - Profile::AM_DIVEBOMB;
	if (index < 0)
		index = 0;
	if (index > 2)
		index = 0;
	combo=GETDLGITEM(IDC_RCOMBOATTACKMETHOD);
	if (index == 0)
	{
		combo->Clear()->RESCOMBO(AM_DIVEBOMB, 1)->
					SetIndex(index);
	}else
	{
		index--;
		combo->Clear()->RESCOMBO(AM_LEVELBOMB, 2)->
					SetIndex(index);
	}
   
   	combo=GETDLGITEM(IDC_RCOMBOBOMBERTYPE);
	combo->Clear()->RESCOMBO(GESCHWADER,3)->
					SetIndex(unitdisplaylevel);

	CRStatic*   s;

	s=GETDLGITEM(IDC_RSTATICBOMBERSALLOCATED);
	CString string = RESSTRING(AIRCRAFT);
	int acnum;
	if (Todays_Packages.taskdata.strike.acnum == 1)
		acnum = 1;
	else if (Todays_Packages.taskdata.strike.acnum > 1)
	{
		acnum = Todays_Packages.taskdata.strike.acnum;
		string = RESSTRING(AIRCRAFT_PLURAL);
	}else
	{
		acnum = Todays_Packages.taskdata.strike.squadnum;
		if (acnum < 2)
			string = RESSTRING(STAFFEL);
		else if (acnum <3)
			string = RESSTRING(L_STAFFELN);
		else if (acnum <6)
		{
			acnum = acnum/3;
			string = RESSTRING(GRUPPE);
		}else if (acnum <18)
		{
			acnum = acnum/3;
			string = RESSTRING(GRUPPEN);
		}else
		{
			acnum = acnum/9;
			string = RESSTRING(GESCHWADER);
		}
	}
	s->SetString(CSprintf("%i %s", acnum, string));


	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(120);
	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	rlistbox->AddColumn(80);
	rlistbox->AddString(RESSTRING(UNIT),0);
	rlistbox->AddString(RESSTRING(TARGET),1);
	rlistbox->AddString(RESSTRING(STATUS),2);

	
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];


//DEADCODE  15/02/00 	UByte		wadernum;
//DEADCODE  15/02/00  	UByte		gruppennum;
//DEADCODE  15/02/00 	Gruppen* sq = Node_Data[(SquadNum)pk[i].squadnum];
//DEADCODE  15/02/00 	wadernum = sq->wadernum;
//DEADCODE  15/02/00  	gruppennum = sq->gruppennum;
//DEADCODE  15/02/00 	bool forcedisplay = true;
//DEADCODE  15/02/00 	if (pk.squadlist) 
//DEADCODE  15/02/00 	{
//DEADCODE  15/02/00 		do
//DEADCODE  15/02/00 		{
//DEADCODE  15/02/00 			sq = Node_Data[(SquadNum)pk[i].squadnum];
//DEADCODE  15/02/00 			int am = pk[i].method;
//DEADCODE  15/02/00 			if (		(pk[i].method == pk.attackmethod)
//DEADCODE  15/02/00 					&&	(	(forcedisplay)
//DEADCODE  15/02/00 							||
//DEADCODE  15/02/00 							(unitdisplaylevel == DISPLAY_STAFFEL)
//DEADCODE  15/02/00 							||
//DEADCODE  15/02/00 							(	(unitdisplaylevel = DISPLAY_GRUPPE)
//DEADCODE  15/02/00 								&&	(gruppennum != sq->gruppennum)
//DEADCODE  15/02/00 							)
//DEADCODE  15/02/00 							||
//DEADCODE  15/02/00 							(	(unitdisplaylevel = DISPLAY_GESCHWADER)
//DEADCODE  15/02/00 								&&	(wadernum != sq->wadernum)
//DEADCODE  15/02/00 							)
//DEADCODE  15/02/00 						)
//DEADCODE  15/02/00 				)
//DEADCODE  15/02/00 			{
//DEADCODE  15/02/00 				forcedisplay = false;
//DEADCODE  15/02/00 				wadernum = sq->wadernum;
//DEADCODE  15/02/00 				gruppennum = sq->gruppennum;
//DEADCODE  15/02/00  				CString name = sq->ShortName() + "/";
//DEADCODE  15/02/00 				name = name + sq->SubName();
//DEADCODE  15/02/00 				rlistbox->AddString(name,0);
//DEADCODE  15/02/00 				rlistbox->AddString(GetTargName(pk.packagetarget[pk[i].targetindex].currentid),1);
//DEADCODE  15/02/00 				rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),2);
//DEADCODE  15/02/00 				for (int actype = PT_JU87; actype < PT_VEHICLES;actype++)
//DEADCODE  15/02/00 						if (sq->AcType() == actype)
//DEADCODE  15/02/00 							me110bomber = false;
//DEADCODE  15/02/00 				maxunits++;
//DEADCODE  15/02/00 
//DEADCODE  15/02/00 			}
//DEADCODE  15/02/00 			i++;
//DEADCODE  15/02/00 		}while (i < pk.squadlist);
//DEADCODE  15/02/00 	}
	FillList();
	int i = 0;
 	UByte		gruppennum;
	Gruppen* sq = Node_Data[(SquadNum)pk[UnitList[0]].squadnum];
	SquadNum gruppnum=(SquadNum)pk[UnitList[0]].squadnum;
	int staffel = 0;
	while (i < maxunits)
	{
		Gruppen* sq = Node_Data[(SquadNum)pk[UnitList[i]].squadnum];
		CString name = sq->ShortName();
		if (unitdisplaylevel != DISPLAY_GESCHWADER)
		{
			name =   name + "/" + sq->SubName();
		}
		if (unitdisplaylevel == DISPLAY_STAFFEL)
		{
			if (gruppnum == (SquadNum)pk[UnitList[i]].squadnum)
				staffel++;
			else
			{
				gruppnum = (SquadNum)pk[UnitList[i]].squadnum;
				staffel =1;
			}
			name = name + CSprintf(" (%i)", staffel + (sq->gruppennum*3));
		}
		rlistbox->AddString(name,0);
		rlistbox->AddString(GetTargName(pk.packagetarget[pk[UnitList[i]].targetindex].currentid),1);
		rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),2);
		i++;
	}

	int maxsquad = Todays_Packages.SquadronsPlanned(NAT_LUF);
	if	(	(	Todays_Packages.taskdata.strike.maxac != -1
			||	(maxsquad < 93)
			)
		&&	pk.attackmethod!=pk.AM_RECON
		)
		 rlistbox->AddString(RESSTRING(NEXTAVAILABLE),0);

}
BOOL LWTaskAircraft::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Refresh();
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
 int LWTaskAircraft::FindSquad(long index)
{
	int i = UnitList[index];
//DEADCODE  15/02/00 	Profile* pk = &Todays_Packages.pack[Todays_Packages.hipack];
//DEADCODE  15/02/00 	int i=0, j =-1;
//DEADCODE  15/02/00 	while (		(i < pk->squadlist)
//DEADCODE  15/02/00 			&&	(j != index)
//DEADCODE  15/02/00 		)
//DEADCODE  15/02/00 	{
//DEADCODE  15/02/00 		if (pk->squadlist[i].method == pk->attackmethod)
//DEADCODE  15/02/00 		{
//DEADCODE  15/02/00 			j++;
//DEADCODE  15/02/00 		}
//DEADCODE  15/02/00 		i++;
//DEADCODE  15/02/00 	}
//DEADCODE  15/02/00 	i--;
//DEADCODE  15/02/00 	if (j != index)
//DEADCODE  15/02/00 		i = -1;
	return(i);
 
}
BEGIN_EVENTSINK_MAP(LWTaskAircraft, CDialog)
    //{{AFX_EVENTSINK_MAP(LWTaskAircraft)
	ON_EVENT(LWTaskAircraft, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(LWTaskAircraft, IDC_RCOMBOBOMBERTYPE, 1 /* TextChanged */, OnTextChangedRcombobombertype, VTS_BSTR VTS_I2)
	ON_EVENT(LWTaskAircraft, IDC_RCOMBOATTACKMETHOD, 1 /* TextChanged */, OnTextChangedRcomboattackmethod, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void LWTaskAircraft::OnSelectRlistboxctrl1(long row, long column) 
{
#ifndef	BOB_DEMO_VER

	if (row > 0)
	{
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
		AircraftUnit::TypesToList	typestolist=AircraftUnit::TTL_BOMBER;
		if (pk.attackmethod==pk.AM_RECON)
		{
			if (pk.squadlist)
				typestolist=(AircraftUnit::TypesToList)(AircraftUnit::TTL_RECONN1+pk[0].numacoriginal-1);
			else
				typestolist=(AircraftUnit::TypesToList)(AircraftUnit::TTL_RECONN1);
		}
		if (pk.attackmethod==pk.AM_DIVEBOMB)
			typestolist=AircraftUnit::TTL_JU87;
		if (pk.squadlist&&pk[0].Squadron().AcType()==PT_ME110)
			typestolist=AircraftUnit::TTL_110;

		if (column == 0)
		{
			if (row > maxunits)
			{
				if 	(Todays_Packages.taskdata.strike.acnum >= 1)
					pk.CompleteSquadron((Profile::AttackMethod) attackmethod);
				else if (Todays_Packages.taskdata.strike.squadnum < 3)
					pk.CompleteGroup((Profile::AttackMethod) attackmethod, Todays_Packages.taskdata.strike.squadnum);
				else
					 TitleBarPtr().OpenAcUnit(-1,typestolist,1, pk.attackmethod, unitdisplaylevel);
			}else
				TitleBarPtr().OpenAcUnit(FindSquad(row-1), typestolist,1, pk.attackmethod, unitdisplaylevel);
		}else
		{
			if ((column == 1) && (row <= maxunits) && (maxunits != 0))
				TitleBarPtr().OpenSelTrg(FindSquad(row-1), 1, unitdisplaylevel, STM_GROUND);
		}
		Todays_Packages.SetTaskData();
//DeadCode JIM 13Nov00 		pk.ReShareSecondaries();												//JIM 28Aug00
		AttackMethodField	am=pk.ScanAttackMethods();
		pk.ReorderPackage(am);
		pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
		Refresh();

	}
#endif	
}

void LWTaskAircraft::OnTextChangedRcombobombertype(LPCTSTR Caption, short index) 
{
	unitdisplaylevel = index;	
	Refresh();
}

void LWTaskAircraft::OnTextChangedRcomboattackmethod(LPCTSTR Caption, short index) 
{
	if (Todays_Packages.taskdata.attackmethod !=  Profile::AM_DIVEBOMB)
	{
		index++;
		Todays_Packages.taskdata.attackmethod =  Profile::AM_DIVEBOMB + index;
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];

		pk.attackmethod =  (AttackMethod)(Profile::AM_DIVEBOMB + index);
		int i =0;
		while (i < pk.squadlist)
		{
			if (pk[i].method < Profile::AM_ESCORTTYPES)
				pk[i].method = (AttackMethod)(Profile::AM_DIVEBOMB + index);
			i++;
		}
	}
	
}
