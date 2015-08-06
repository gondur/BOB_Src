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

// RowanDialog: // RAFTaskF.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFTaskF.h"
#include "package.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFTaskFighter dialog


RDialog*	RAFTaskFighter::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new RAFTaskFighter(0))
			);
}


RAFTaskFighter::RAFTaskFighter(int acnum,CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFTaskFighter::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFTaskFighter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	attackmethod = acnum;
	unitdisplaylevel = DISPLAY_SQUADRON;

}


void RAFTaskFighter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFTaskFighter)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RCOMBOPREFERREDTARGET, m_IDC_RCOMBOPREFERREDTARGET);
	DDX_Control(pDX, IDC_RCOMBOATTACKMETHOD, m_IDC_RCOMBOATTACKMETHOD);
//DEADCODE RDH 10/04/00 	DDX_Control(pDX, IDC_RCOMBOUNITTYPE, m_IDC_RCOMBOUNITTYPE);
	DDX_Control(pDX, IDC_RCOMBOFORMATION, m_IDC_RCOMBOFORMATION);
	DDX_Control(pDX, IDC_RSTATICFIGHTERSALLOCATED, m_IDC_RSTATICFIGHTERSALLOCATED);
	DDX_Control(pDX, IDC_RSTATICFORMATION, m_IDC_RSTATICFORMATION);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFTaskFighter, CDialog)
	//{{AFX_MSG_MAP(RAFTaskFighter)
	//}}AFX_MSG_MAP
		ON_MESSAGE( WM_SELECTTAB, OnSelectTab)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFTaskFighter message handlers
void	RAFTaskFighter::OnSelectTab()
{
	Refresh();
}

bool RAFTaskFighter::FindAssociatedLWPack(UniqueID raftrg, int& pack, int& sq)
{
	int p=0;
	bool found = false;
	while (p < Profile::MAX_PACKS)
	{	
		if (Todays_Packages.pack[p].packagestatus!=Profile::PS_SPARE)
		{
			int i = 0;
			Profile& pk = Todays_Packages.pack[p];
			while (i < pk.squadlist)
			{
				if (raftrg == pk[i].instance)
				{
					pack = p;
					sq = i;
					found = true;
					break;
				}
				i++;
			}
		}
		p++;
	}
	return (found);
}


void RAFTaskFighter::FillList()
{

	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	int i=0;
	maxunits = 0;
	while (i < pk.squadlist)
	{
		Squadron* sq = Node_Data[(SquadNum)pk[i].squadnum];
		int actype = sq->AcType();

		if (	(	(		(Profile::AM_DETACHED == attackmethod)
						&&	(	(actype == PT_SPIT_A)	||	(actype == PT_SPIT_B))
					)
					||
					(		  (Profile::AM_ATTACHED == attackmethod)
						&&	(	(actype == PT_HURR_A)	||	(actype == PT_HURR_B))
					)
				)
				&&
				(maxunits < MAXSQUADS)

	
			)
		{
			UnitList[maxunits] = i;
			maxunits++;
		}
		i++;
	}

}








void RAFTaskFighter::Refresh()
{
	CRStatic*   s;
   	
	PackageList::AMType*	amtype;

	switch	(attackmethod)
	{
		default_neverreferenced;
		case	Profile::AM_DETACHED:
		{
			amtype = &Todays_Packages.taskdata.detached;
			tab = 2;
			break;
		}
		case	Profile::AM_ATTACHED:
		{
			amtype = &Todays_Packages.taskdata.attached;
			tab = 1;
			break;
		}
	}

	s=GETDLGITEM(IDC_RSTATICFIGHTERSALLOCATED);
		CString string = RESSTRING(SQUADRONLEADER);
	int acnum;
	if (amtype->acnum == 0)
	{
		acnum = 0;
		string = RESSTRING(NONE_WORD);
	}else if (amtype->acnum == 1)
		acnum = 0;
	else if (amtype->acnum >= 6)
	{
		acnum = 1;
		string = RESSTRING(FLIGHT);
	}else if (amtype->acnum >= 3)
	{
		acnum = 1;
		string = RESSTRING(ELEMENT);
	}else
	{
		acnum = amtype->squadnum;
		if (acnum < 2)
			string = RESSTRING(SQUADRON);
		else 
			string = RESSTRING(SQUADRONS);
	}
	if (acnum  == 0)
		s->SetString(CSprintf("%s", string));
	else
		s->SetString(CSprintf("%i %s", acnum, string));


	CRCombo* combo;

	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
		PlaneTypeSelect actype = PT_SPIT_A;
	if (attackmethod == Profile::AM_ATTACHED )
		actype=  PT_HURR_A;



	int index = pk.FindPreferredTarget(actype);
	combo=GETDLGITEM(IDC_RCOMBOPREFERREDTARGET);
	combo->Clear()->RESCOMBO(FREE,3)->
					SetIndex(index);

	index = pk.FindAttackMethod(actype);
	combo=GETDLGITEM(IDC_RCOMBOATTACKMETHOD);
	combo->Clear()->RESCOMBO(DIVEANDZOOM,6)->
					SetIndex(index);

//	combo=GETDLGITEM(IDC_RCOMBOFORMATION);
//	combo->Clear()->RESCOMBO(BOMBONLEADER,3)->
//					SetIndex(1);



//DEADCODE RDH 10/04/00 	  	combo=GETDLGITEM(IDC_RCOMBOUNITTYPE);
//DEADCODE RDH 10/04/00 		combo->ShowWindow(false);
//DEADCODE RDH 10/04/00 //	combo->Clear()->RESCOMBO(SQUADRON,3)->
//					SetIndex(unitdisplaylevel);



	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(120);
	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	rlistbox->AddColumn(80);
	rlistbox->AddString(RESSTRING(UNIT),0);
	rlistbox->AddString(RESSTRING(TARGET),1);
	rlistbox->AddString(RESSTRING(STATUS),2);


	
//DEADCODE RDH 17/01/00 	rlistbox->AddString("56 Squadron",0);
//DEADCODE RDH 17/01/00 	rlistbox->AddString("H101",1);

//DEADCODE  16/02/00 	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
//DEADCODE  16/02/00 	int i=0;
//DEADCODE  16/02/00 	maxunits = 0;
//DEADCODE  16/02/00 	while (i < pk.squadlist)
//DEADCODE  16/02/00 	{
//DEADCODE  16/02/00 		Squadron* sq = Node_Data[(SquadNum)pk[i].squadnum];
//DEADCODE  16/02/00 		int actype = sq->AcType();
//DEADCODE  16/02/00 
//DEADCODE  16/02/00 		if (	(		(Profile::AM_DETACHED == attackmethod)
//DEADCODE  16/02/00 					&&	(	(actype == PT_SPIT_A)	||	(actype == PT_SPIT_B))
//DEADCODE  16/02/00 				)
//DEADCODE  16/02/00 				||
//DEADCODE  16/02/00 				(		  (Profile::AM_ATTACHED == attackmethod)
//DEADCODE  16/02/00 					&&	(	(actype == PT_HURR_A)	||	(actype == PT_HURR_B))
//DEADCODE  16/02/00 				)
//DEADCODE  16/02/00 			)
//DEADCODE  16/02/00 		{
//DEADCODE  16/02/00  			CString name = sq->FullName();
//DEADCODE  16/02/00 			rlistbox->AddString(name,0);
//DEADCODE  16/02/00 			int lwpack = FindAssociatedLWPack(pk.packagetarget[0]);
//DEADCODE  16/02/00 
//DEADCODE  16/02/00 			if (lwpack >= 0)
//DEADCODE  16/02/00 			{
//DEADCODE  16/02/00 				Profile& lwpk = Todays_Packages.pack[lwpack];
//DEADCODE  16/02/00 				rlistbox->AddString(CSprintf("R%i", lwpk.raidnumentries[0].raidnum),1);
//DEADCODE  16/02/00 				rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),2);
//DEADCODE  16/02/00 			}else
//DEADCODE  16/02/00 			{
//DEADCODE  16/02/00 				rlistbox->AddString("",1);
//DEADCODE  16/02/00 				rlistbox->AddString("",2);
//DEADCODE  16/02/00 			}
//DEADCODE  16/02/00 			maxunits++;
//DEADCODE  16/02/00 		}
//DEADCODE  16/02/00 		i++;
//DEADCODE  16/02/00 	}
//DEADCODE  16/02/00 
//DEADCODE  16/02/00 	 rlistbox->AddString(RESSTRING(NEXTAVAILABLE),0);

	FillList();

	pk = Todays_Packages.pack[Todays_Packages.hipack];
	int i=0;
	while (i < maxunits)
	{
		Squadron* sq = Node_Data[(SquadNum)pk[UnitList[i]].squadnum];
		CString name = sq->FullName();
		rlistbox->AddString(name,0);
		rlistbox->AddString(RESLIST(PS_SPARE,sq->totestatus),2);



		int lwpack = 0, sqnum;
 		UniqueID trguid = pk.packagetarget[pk[UnitList[i]].targetindex];
		int uidband=Persons2::getbandfromUID(trguid);	

		if (uidband == SagBAND)
		{
			Todays_Packages.GetACSquadEntry(trguid,lwpack,sqnum);
			Profile& lwpk = Todays_Packages.pack[lwpack];

			int raidline = lwpk.GetRaidIndFromSquadEntry(sqnum);
			char* raidletter = Todays_Packages.RaidFormatString(lwpack,raidline);
			rlistbox->AddString(CSprintf(raidletter, lwpk.raidnumentries[raidline].raidnum),1);


		}else
		{
			rlistbox->AddString(GetTargName(trguid),1);
		}		





//DEADCODE RDH 18/05/00 		int sqnum;
//DEADCODE RDH 18/05/00 		int lwpack;
//DEADCODE RDH 18/05/00 		if (FindAssociatedLWPack(pk.packagetarget[0], lwpack, sqnum) )
//DEADCODE RDH 18/05/00 		{
//DEADCODE RDH 18/05/00 			Profile& lwpk = Todays_Packages.pack[lwpack];
//DEADCODE RDH 18/05/00  			int raid = lwpk.GetRaidIndFromSquadEntry(sqnum);
//DEADCODE RDH 18/05/00 
//DEADCODE RDH 18/05/00 			char* raidletter = Todays_Packages.RaidFormatString(lwpack, raid);
//DEADCODE RDH 18/05/00 			rlistbox->AddString(CSprintf(raidletter, lwpk.raidnumentries[raid].raidnum),1);
//DEADCODE RDH 18/05/00 
//DEADCODE RDH 18/05/00 
//DEADCODE RDH 18/05/00 //DEADCODE RDH 13/04/00 			rlistbox->AddString(CSprintf("R%03i", lwpk.raidnumentries[0].raidnum),1);
//DEADCODE RDH 18/05/00 			rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),2);
//DEADCODE RDH 18/05/00 		}else
//DEADCODE RDH 18/05/00 		{
//DEADCODE RDH 18/05/00 			rlistbox->AddString("",1);
//DEADCODE RDH 18/05/00 			rlistbox->AddString("",2);
//DEADCODE RDH 18/05/00 		}
		i++;
	}
	if (maxunits < 3)
		rlistbox->AddString(RESSTRING(NEXTAVAILABLE),0);






}
int RAFTaskFighter::FindSquad(long index)
{
	int i = UnitList[index];

//DEADCODE  16/02/00 	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
//DEADCODE  16/02/00 	int i=0, j =-1;
//DEADCODE  16/02/00 	while (		(i < pk.squadlist)
//DEADCODE  16/02/00 			&&	(j != index)
//DEADCODE  16/02/00 		   )
//DEADCODE  16/02/00 	{
//DEADCODE  16/02/00 		Squadron* sq = Node_Data[(SquadNum)pk[i].squadnum];
//DEADCODE  16/02/00 		int actype = sq->AcType();
//DEADCODE  16/02/00 
//DEADCODE  16/02/00 		if (	(		(Profile::AM_DETACHED == attackmethod)
//DEADCODE  16/02/00 					&&	(	(actype == PT_SPIT_A)	||	(actype == PT_SPIT_B))
//DEADCODE  16/02/00 				)
//DEADCODE  16/02/00 				||
//DEADCODE  16/02/00 				(		  (Profile::AM_ATTACHED == attackmethod)
//DEADCODE  16/02/00 					&&	(	(actype == PT_HURR_A)	||	(actype == PT_HURR_B))
//DEADCODE  16/02/00 				)
//DEADCODE  16/02/00 			)
//DEADCODE  16/02/00 		{
//DEADCODE  16/02/00 			j++;
//DEADCODE  16/02/00 		}
//DEADCODE  16/02/00 			i++;
//DEADCODE  16/02/00 	}
//DEADCODE  16/02/00 	i--;
//DEADCODE  16/02/00 	if (j != index)
//DEADCODE  16/02/00 		i = -1;
	return(i);
 
}

BOOL RAFTaskFighter::OnInitDialog() 
{
	CDialog::OnInitDialog();

	Refresh();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(RAFTaskFighter, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFTaskFighter)
	ON_EVENT(RAFTaskFighter, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(RAFTaskFighter, IDC_RCOMBOPREFERREDTARGET, 1 /* TextChanged */, OnTextChangedRcombopreferredtarget, VTS_BSTR VTS_I2)
	ON_EVENT(RAFTaskFighter, IDC_RCOMBOATTACKMETHOD, 1 /* TextChanged */, OnTextChangedRcomboattackmethod, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RAFTaskFighter::OnSelectRlistboxctrl1(long row, long column) 
{
#ifndef	BOB_DEMO_VER

//DeadCode JIM 9Oct00 	if (column == 0)
//DeadCode JIM 9Oct00 	{
		Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
		bool spitfire;
		PackageList::AMType*	amtype;
		Profile::BetterRule	br = pk.RAFFindBetterRule();
		br = Profile::BetterRule(br & (!Profile::BR_B_EITHERWL));
		switch	(attackmethod)
		{
			default_neverreferenced;
			case	Profile::AM_DETACHED:
			{
				br =  Profile::BetterRule(br | Profile::BR_B_SPITWL);
				amtype = &Todays_Packages.taskdata.detached;
				spitfire = true;		//SPIT
				break;
			}
			case	Profile::AM_ATTACHED:
			{
				br =  Profile::BetterRule(br | Profile::BR_B_HURRWL);
				amtype = &Todays_Packages.taskdata.attached;
				spitfire = false;
				break;
			}
		}



		if (row > maxunits)
		{
			if (maxunits < 3)
			{
//DEADCODE RDH 10/05/00 				if (maxunits == 0)
//DEADCODE RDH 10/05/00 				{
//DEADCODE RDH 10/05/00 					pk.AddSquadron(-1,(Profile::AttackMethod) pk.attackmethod,0,br);
//DEADCODE RDH 10/05/00 				}else 
				if 	(amtype->acnum >= 1)
					pk.CompleteSquadron((Profile::AttackMethod) pk.attackmethod);
				else
					TitleBarPtr().OpenAcUnitRAF(-1, spitfire,tab, attackmethod);	
			}
		}else
			TitleBarPtr().OpenAcUnitRAF(FindSquad(row-1), spitfire,tab, attackmethod);	


//DeadCode JIM 9Oct00 	}else
//DeadCode JIM 9Oct00 	{
//DeadCode JIM 9Oct00 		if ((column == 1) && (row <= maxunits) && (maxunits != 0))
//DeadCode JIM 9Oct00 		{
//DeadCode JIM 9Oct00 			Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
//DeadCode JIM 9Oct00 			Squadron* sq = Node_Data[(SquadNum)pk[FindSquad(row-1)].squadnum];
//DeadCode JIM 9Oct00 			UniqueID trguid = pk.packagetarget[pk[FindSquad(row-1)].targetindex];
//DeadCode JIM 9Oct00 			int uidband=Persons2::getbandfromUID(trguid);	
//DeadCode JIM 9Oct00 			if (uidband == SagBAND)
//DeadCode JIM 9Oct00 				TitleBarPtr().OpenSelTrg(FindSquad(row-1), tab, PackageList::DISPLAY_STAFFEL,STM_LWAC);
//DeadCode JIM 9Oct00 			else
//DeadCode JIM 9Oct00 				TitleBarPtr().OpenSelTrg(FindSquad(row-1), tab, PackageList::DISPLAY_STAFFEL,STM_GROUND);
//DeadCode JIM 9Oct00 		}
//DeadCode JIM 9Oct00 	}
#endif	
}

void RAFTaskFighter::OnTextChangedRcombopreferredtarget(LPCTSTR Caption, short index) 
{
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	Profile::SubMethod sm  = (Profile::SubMethod)index;

	CRCombo* combo;
	combo=GETDLGITEM(IDC_RCOMBOATTACKMETHOD);
	int amindex = combo->GetIndex();

	sm = Profile::SubMethod(sm  + 	(Profile::SM_DIVEANDZOOM * amindex) + Profile::SM_DIVEANDZOOM);

	PlaneTypeSelect actype = PT_SPIT_A;
	if (attackmethod == Profile::AM_ATTACHED )
		actype =  PT_HURR_A;

	pk.SetSubMethod(actype, sm, FTS_VIC);
 	Refresh();
	
}

void RAFTaskFighter::OnTextChangedRcomboattackmethod(LPCTSTR Caption, short index) 
{
	Profile& pk = Todays_Packages.pack[Todays_Packages.hipack];
	Profile::SubMethod sm;

	sm = Profile::SubMethod(Profile::SM_DIVEANDZOOM + (Profile::SM_DIVEANDZOOM * index));

	CRCombo* combo;
	combo=GETDLGITEM(IDC_RCOMBOPREFERREDTARGET);
	int ptindex = combo->GetIndex();

	sm = Profile::SubMethod(sm + ptindex);

	PlaneTypeSelect actype = PT_SPIT_A;
	if (attackmethod == Profile::AM_ATTACHED )
		actype=  PT_HURR_A;

	pk.SetSubMethod(actype, sm, FTS_VIC);
	Refresh();
	
}
