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

// RowanDialog: // LWTaskFr.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"

#include "LWTaskFr.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// LWTaskFighter dialog


RDialog*	LWTaskFighter::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new LWTaskFighter(0))
			);
}


LWTaskFighter::LWTaskFighter(int acnum,CWnd* pParent /*=NULL*/)
	: RowanDialog(LWTaskFighter::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWTaskFighter)
	//}}AFX_DATA_INIT
	attackmethod = acnum;
	me110bomber = false;
	unitdisplaylevel = PackageList::DISPLAY_GRUPPE;
	
 
	

}


void LWTaskFighter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWTaskFighter)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RSTATICFIGHTERSALLOCATED, m_IDC_RSTATICFIGHTERSALLOCATED);
	DDX_Control(pDX, IDC_RCOMBOFORMATION, m_IDC_RCOMBOFORMATION);
	DDX_Control(pDX, IDC_RCOMBOUNITTYPE, m_IDC_RCOMBOUNITTYPE);
	DDX_Control(pDX, IDC_RSTATICCTRL00, m_IDC_RSTATICCTRL00);
	DDX_Control(pDX, IDC_RSTATICCTRL01, m_IDC_RSTATICCTRL01);
	DDX_Control(pDX, IDC_RSTATICCTRL02, m_IDC_RSTATICCTRL02);
	DDX_Control(pDX, IDC_RSTATICCTRL03, m_IDC_RSTATICCTRL03);
	DDX_Control(pDX, IDC_RSTATICCTRL04, m_IDC_RSTATICCTRL04);
	DDX_Control(pDX, IDC_RSTATICCTRL05, m_IDC_RSTATICCTRL05);
	DDX_Control(pDX, IDC_STRAFTARGET, m_IDC_STRAFTARGET);
	DDX_Control(pDX, IDC_TICK1, m_IDC_TICK1);
	DDX_Control(pDX, IDC_TICK2, m_IDC_TICK2);
	DDX_Control(pDX, IDC_TICK3, m_IDC_TICK3);
	DDX_Control(pDX, IDC_TICK4, m_IDC_TICK4);
	DDX_Control(pDX, IDC_TICK5, m_IDC_TICK5);
	DDX_Control(pDX, IDC_TICK6, m_IDC_TICK6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWTaskFighter, CDialog)
	//{{AFX_MSG_MAP(LWTaskFighter)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
		ON_MESSAGE( WM_SELECTTAB, OnSelectTab)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWTaskFighter message handlers
void	LWTaskFighter::OnSelectTab()
{
	Refresh();
}
void LWTaskFighter::RefreshCombos()
{


}
void	LWTaskFighter::FillList()
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
			int am = pk[i].method;
			if (		(		(pk[i].method >= attackmethod)
				&&	(pk[i].method < (attackmethod + Profile::AM_FIELD_MIN))
						)
					&&	(	(forcedisplay)
							||
							(unitdisplaylevel == PackageList::DISPLAY_STAFFEL)
							||
							(	(unitdisplaylevel == PackageList::DISPLAY_GRUPPE)
								&&	(		(gruppennum != sq->gruppennum)
										||	(wadernum != sq->wadernum)
									)

							)
							||
							(	(unitdisplaylevel == PackageList::DISPLAY_GESCHWADER)
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

void LWTaskFighter::Refresh()
{
		CRStatic*   s;


	PackageList::AMType*	amtype;

	switch	(attackmethod)
	{
		case	Profile::AM_DETACHED:
		{
			amtype = &Todays_Packages.taskdata.detached;
			tab = 3;
			break;
		}
		case	Profile::AM_ATTACHED:
		{
			amtype = &Todays_Packages.taskdata.attached;
			tab = 2;
			break;
		}
		case	Profile::AM_RETURNESCORT:
		{
			amtype = &Todays_Packages.taskdata.returned;
			tab = 4;
			break;
		}
		default_neverreferenced; 
		
	}



	s=GETDLGITEM(IDC_RSTATICFIGHTERSALLOCATED);
	CString string = RESSTRING(AIRCRAFT);
	int acnum;
	if (amtype->acnum == 1)
		acnum = 1;
	else if (amtype->acnum > 1)
	{
		acnum = amtype->acnum;
		string = RESSTRING(AIRCRAFT_PLURAL);
	}else
	{
		acnum = amtype->squadnum;
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








	CRCombo* combo;
	int form = (amtype->formtype & FORMTYPE_SQUAD)>>FORMTYPE_SQUAD_SH;
	if (form > 6) form = 6;
	if (form < 0) form = 0;
	combo=GETDLGITEM(IDC_RCOMBOFORMATION);
	combo->Clear()->RESCOMBO(AUTO,1)-> SetIndex(0);

//DeadCode JIM 14Nov00 	combo->Clear()->RESCOMBO(ECHELONL,7)-> SetIndex(form);


	  	combo=GETDLGITEM(IDC_RCOMBOUNITTYPE);
	combo->Clear()->RESCOMBO(GESCHWADER,3)->
					SetIndex(unitdisplaylevel);




	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(120);
	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	rlistbox->AddColumn(80);
	rlistbox->AddString(RESSTRING(UNIT),0);
	rlistbox->AddString(RESSTRING(TARGET),1);
	rlistbox->AddString(RESSTRING(STATUS),2);

	
	if (attackmethod == Profile::AM_DETACHED)
	{
		GETDLGITEM(IDC_RSTATICCTRL00)->SetString(RESSTRING(L_CEILING));
 		GETDLGITEM(IDC_RSTATICCTRL01)->SetString(RESSTRING(LHIGH));
		GETDLGITEM(IDC_RSTATICCTRL02)->SetString(RESSTRING(FORWARDHIGH));
		GETDLGITEM(IDC_RSTATICCTRL03)->SetString(RESSTRING(FORWARD));
		GETDLGITEM(IDC_RSTATICCTRL04)->SetString(RESSTRING(FORWARDLOW));
		GETDLGITEM(IDC_RSTATICCTRL05)->SetString(RESSTRING(LATE));
	}else
	{
		GETDLGITEM(IDC_RSTATICCTRL00)->SetString(RESSTRING(BEHIND));
 		GETDLGITEM(IDC_RSTATICCTRL01)->SetString(RESSTRING(INFRONT));
		GETDLGITEM(IDC_RSTATICCTRL02)->SetString(RESSTRING(PORT));
		GETDLGITEM(IDC_RSTATICCTRL03)->SetString(RESSTRING(STARBOARD));
		GETDLGITEM(IDC_RSTATICCTRL04)->SetString(RESSTRING(ABOVE));
		GETDLGITEM(IDC_RSTATICCTRL05)->SetString(RESSTRING(BELOW));
	}


		for (int i=1; i< PackageList::MAX_METHODS-1;i++)
		{
			CRButton* b = GETDLGITEM(IDC_TICK1+i-1);
			b->SetPressed(amtype->attackmethods[i]);
		}



	

	
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];

	CRButton* b = GETDLGITEM(IDC_STRAFTARGET);

//DEADCODE RDH 02/04/00 	straf = false;
//DEADCODE RDH 02/04/00 	for (int num=pk.squadlist.Max()-1;num>=0;num--)
//DEADCODE RDH 02/04/00 		if  (	((pk.squadlist[num].method&Profile::AM_GROUPMASK)==attackmethod)
//DEADCODE RDH 02/04/00 			&&	(pk.squadlist[num].submethod == Profile::SM_DOSTRAFFEGROUND)
//DEADCODE RDH 02/04/00 			)
//DEADCODE RDH 02/04/00 			straf = true;
//DEADCODE RDH 02/04/00 	b->SetPressed(straf);
//DEADCODE RDH 02/04/00 
	b->SetPressed(pk.StraffRequired(attackmethod));		

	i=0;

//DEADCODE  15/02/00 	maxunits = 0;
//DEADCODE  15/02/00 	while (i < pk.squadlist)
//DEADCODE  15/02/00 	{
//DEADCODE  15/02/00 		int am = pk[i].method;
//DEADCODE  15/02/00 
//DEADCODE  15/02/00 		if (pk[i].method == attackmethod)
//DEADCODE  15/02/00 		{
//DEADCODE  15/02/00 			Squadron* sq = Node_Data[(SquadNum)pk[i].squadnum];
//DEADCODE  15/02/00  			CString name = sq->ShortName() + "/";
//DEADCODE  15/02/00 			name = name + sq->SubName();
//DEADCODE  15/02/00 			rlistbox->AddString(name,0);
//DEADCODE  15/02/00 			rlistbox->AddString(GetTargName(pk.packagetarget[pk[i].targetindex].currentid),1);
//DEADCODE  15/02/00 			rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),2);
//DEADCODE  15/02/00 			maxunits++;
//DEADCODE  15/02/00 		}
//DEADCODE  15/02/00 		i++;
//DEADCODE  15/02/00 	}

	FillList();
	if ((UnitList[0] >= 0)	&&	(maxunits > 0))
	{
		i = 0;
		UByte		gruppennum;
		Gruppen* sq = Node_Data[(SquadNum)pk[UnitList[0]].squadnum];
 		gruppennum = (SquadNum)pk[UnitList[0]].squadnum;
		int staffel = 0;

		while (i < maxunits)
		{
			Gruppen* sq = Node_Data[(SquadNum)pk[UnitList[i]].squadnum];
			CString name = sq->ShortName();
			if (unitdisplaylevel != PackageList::DISPLAY_GESCHWADER)
			{
				name =   name + "/" + sq->SubName();
			}

			if (unitdisplaylevel == PackageList::DISPLAY_STAFFEL)
			{
				if (gruppennum == (SquadNum)pk[UnitList[i]].squadnum)
					staffel++;
				else
				{
					gruppennum = (SquadNum)pk[UnitList[i]].squadnum;
					staffel =1;
				}
				name = name + CSprintf(" (%i)", staffel + (sq->gruppennum*3));
			}
			rlistbox->AddString(name,0);
			int ti=pk[UnitList[i]].targetindex;
			if (ti<0)
				ti=0;
			rlistbox->AddString(GetTargName(pk.packagetarget[ti].currentid),1);
			rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),2);
			i++;
		}
	}
	int maxsquad = Todays_Packages.SquadronsPlanned(NAT_LUF);
	if	(	(Todays_Packages.taskdata.attached.maxac != -1)
			||
			(
			 (maxsquad < 93)
			)
		)
		rlistbox->AddString(RESSTRING(NEXTAVAILABLE),0);

}

BOOL LWTaskFighter::OnInitDialog() 
{
	return CDialog::OnInitDialog();
}
BOOL LWTaskFighter::OnEraseBkgnd(CDC* pDC) 
{
//TempCode JIM 28Aug00 	Refresh();

	return CDialog::OnEraseBkgnd(pDC);
	
//	
//	return TRUE;  // return TRUE unless you set the focus to a control
//	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(LWTaskFighter, CDialog)
    //{{AFX_EVENTSINK_MAP(LWTaskFighter)
	ON_EVENT(LWTaskFighter, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(LWTaskFighter, IDC_RCOMBOFORMATION, 1 /* TextChanged */, OnTextChangedRcomboformation, VTS_BSTR VTS_I2)
	ON_EVENT(LWTaskFighter, IDC_RCOMBOUNITTYPE, 1 /* TextChanged */, OnTextChangedRcombounittype, VTS_BSTR VTS_I2)
	ON_EVENT(LWTaskFighter, IDC_TICK1, 1 /* Clicked */, OnClickedTick1, VTS_NONE)
	ON_EVENT(LWTaskFighter, IDC_TICK2, 1 /* Clicked */, OnClickedTick2, VTS_NONE)
	ON_EVENT(LWTaskFighter, IDC_TICK3, 1 /* Clicked */, OnClickedTick3, VTS_NONE)
	ON_EVENT(LWTaskFighter, IDC_TICK4, 1 /* Clicked */, OnClickedTick4, VTS_NONE)
	ON_EVENT(LWTaskFighter, IDC_TICK5, 1 /* Clicked */, OnClickedTick5, VTS_NONE)
	ON_EVENT(LWTaskFighter, IDC_TICK6, 1 /* Clicked */, OnClickedTick6, VTS_NONE)
	ON_EVENT(LWTaskFighter, IDC_STRAFTARGET, 1 /* Clicked */, OnClickedStraftarget, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

int LWTaskFighter::FindSquad(long index)
{
	int i = UnitList[index];

//DEADCODE  15/02/00 	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
//DEADCODE  15/02/00 	int i=0, j =-1;
//DEADCODE  15/02/00 	while (		(i < pk.squadlist)
//DEADCODE  15/02/00 			&&	(j != index)
//DEADCODE  15/02/00 		   )
//DEADCODE  15/02/00 	{
//DEADCODE  15/02/00 		if (pk[i].method == attackmethod)
//DEADCODE  15/02/00 		{
//DEADCODE  15/02/00 			j++;
//DEADCODE  15/02/00 		}
//DEADCODE  15/02/00 			i++;
//DEADCODE  15/02/00 	}
//DEADCODE  15/02/00 	i--;
//DEADCODE  15/02/00 	if (j != index)
//DEADCODE  15/02/00 		i = -1;
	return(i);
 
}


void LWTaskFighter::OnSelectRlistboxctrl1(long row, long column) 
{ 	
#ifndef	BOB_DEMO_VER


	PackageList::AMType*	amtype;

	switch	(attackmethod)
	{
		default_neverreferenced;
		case	Profile::AM_DETACHED:
		{
			amtype = &Todays_Packages.taskdata.detached;
			tab = 3;
			break;
		}
		case	Profile::AM_ATTACHED:
		{
			amtype = &Todays_Packages.taskdata.attached;
			tab = 2;
			break;
		}
		case	Profile::AM_RETURNESCORT:
		{
			amtype = &Todays_Packages.taskdata.returned;
			tab = 4;
			break;
		}

	}
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];


	if (row > 0)
	{
		if (column == 0)
		{
			if (row > maxunits)
			{	
				if (maxunits == 0)
				{
					Profile::BetterRule	br = pk.FindBetterRule();
					if (Todays_Packages.taskdata.totalfighter.squadnum <3)
						pk.AddSquadron(-1,(Profile::AttackMethod) attackmethod,0,br);
					else
						pk.AddNumerousSquadrons(-3,(Profile::AttackMethod)attackmethod,SQ_ZERO,br);

				}else if 	(amtype->acnum >= 1)
					pk.CompleteSquadron((Profile::AttackMethod) attackmethod);
				else if (amtype->squadnum < 3)
					pk.CompleteGroup((Profile::AttackMethod) attackmethod, amtype->squadnum);
				else
			 		TitleBarPtr().OpenAcUnit(-1,AircraftUnit::TTL_FIGHTER, tab, attackmethod,  unitdisplaylevel);
			}else
				TitleBarPtr().OpenAcUnit(FindSquad(row-1), AircraftUnit::TTL_FIGHTER, tab, attackmethod, unitdisplaylevel);
		}else
		{
//DeadCode JIM 26Sep00 			if ((column == 1) && (row <= maxunits) && (maxunits != 0))
//DeadCode JIM 26Sep00 				TitleBarPtr().OpenSelTrg(FindSquad(row-1), tab, unitdisplaylevel, false);
		}
		pk.ReShareSecondaries();												//JIM 28Aug00
		AttackMethodField	am=pk.ScanAttackMethods();
		pk.ReorderPackage(am);
		pk.CalcRoutePositionsAndTime(pk.primarytargetETA,false);
		Todays_Packages.SetTaskData();
		Refresh();

	}	
#endif
}


void LWTaskFighter::OnTextChangedRcomboformation(LPCTSTR Caption, short index) 
{

	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	int i = 0;
	while (i < pk.squadlist)
	{
		if  (		(pk[i].method >= attackmethod)
				&&	(pk[i].method < (attackmethod + Profile::AM_FIELD_MIN))
			)
		{
			int form = index<<FORMTYPE_SQUAD_SH;
			int form2  = pk[i].formtype & (~FORMTYPE_SQUAD);
			form  = form2 |	form;
			pk[i].FormType() = (FormationTypeIndex)form;
		}
		i++;
	}


	Todays_Packages.SetTaskData();
	RefreshCombos();

}

void LWTaskFighter::OnTextChangedRcombounittype(LPCTSTR Caption, short index) 
{
	unitdisplaylevel = index;	
	Refresh();
	
}

void LWTaskFighter::OnClickedTick(int tick) 
{
  	PackageList::AMType*	amtype;

	switch	(attackmethod)
	{
		case	Profile::AM_DETACHED:
		{
			amtype = &Todays_Packages.taskdata.detached;
			tab = 3;
			break;
		}
		case	Profile::AM_ATTACHED:
		{
			amtype = &Todays_Packages.taskdata.attached;
			tab = 2;
			break;
		}
		case	Profile::AM_RETURNESCORT:
		{
			amtype = &Todays_Packages.taskdata.returned;
			tab = 4;
			break;
		}
		default_neverreferenced; 
	}


	if	(amtype->attackmethods[tick+1])
	   amtype->attackmethods[tick+1] = false;
	else
	   amtype->attackmethods[tick+1] = true;

}

void LWTaskFighter::OnClickedTick1() 
{
	OnClickedTick(0);	
}

void LWTaskFighter::OnClickedTick2() 
{
	OnClickedTick(1);	
	
}

void LWTaskFighter::OnClickedTick3() 
{
	OnClickedTick(2);	
}

void LWTaskFighter::OnClickedTick4() 
{
	OnClickedTick(3);	
}

void LWTaskFighter::OnClickedTick5() 
{
	OnClickedTick(4);	
	
}

void LWTaskFighter::OnClickedTick6() 
{
	OnClickedTick(5);	
	
}

void LWTaskFighter::OnClickedStraftarget() 
{
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];

	Profile::SubMethod sm;

	if (pk.StraffRequired(attackmethod))
		sm = Profile::SM_ANYA2A;
	else
		sm = Profile::SM_DOSTRAFFEGROUND;
	pk.SetSubMethod((Profile::AttackMethod)attackmethod, sm);
 	Refresh();

	
}
