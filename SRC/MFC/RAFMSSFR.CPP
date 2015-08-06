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

// RowanDialog: // RAFMssFr.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFMssFr.h"
#include "package.h"
#include "persons2.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFMissionFolder dialog


RDialog*	RAFMissionFolder::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_MAX),
			DialBox(FIL_D_RAFMISSONFOLDER,new RAFMissionFolder())
			);
}


RAFMissionFolder::RAFMissionFolder(CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFMissionFolder::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFMissionFolder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RAFMissionFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFMissionFolder)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RBUTTONTASK, m_IDC_RBUTTONTASK);
	DDX_Control(pDX, IDC_RBUTTONROUTE, m_IDC_RBUTTONROUTE);
	DDX_Control(pDX, IDC_RBUTTONRTB, m_IDC_RBUTTONRTB);
	DDX_Control(pDX, IDC_RBUTTONSQUADRON, m_IDC_RBUTTONSQUADRON);
	DDX_Control(pDX, IDC_RBUTTONINTELL, m_IDC_RBUTTONINTELL);
	DDX_Control(pDX, IDC_RBUTTONDELETE, m_IDC_RBUTTONDELETE);
	DDX_Control(pDX, IDC_PLANNED, m_IDC_PLANNED);
	DDX_Control(pDX, IDC_ENGAGING, m_IDC_ENGAGING);
	DDX_Control(pDX, IDC_INCOMING, m_IDC_INCOMING);
	DDX_Control(pDX, IDC_LANDED, m_IDC_LANDED);
	DDX_Control(pDX, IDC_OUTGOING, m_IDC_OUTGOING);
	DDX_Control(pDX, IDC_RBUTTONFRAG, m_IDC_RBUTTONFRAG);
	DDX_Control(pDX, IDC_INTERCEPTS, m_IDC_INTERCEPTS);
	DDX_Control(pDX, IDC_PATROLS, m_IDC_PATROLS);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
//DeadCode JIM 3Nov00 	int	colwidtotal=GETDLGITEM(IDC_RLISTBOXCTRL1)->GetColumnWidth(4)+GETDLGITEM(IDC_RLISTBOXCTRL1)->GetColumnWidth(5);
//DeadCode JIM 3Nov00 	GETDLGITEM(IDC_RLISTBOXCTRL1)->SetColumnWidth(4,colwidtotal-3);
//DeadCode JIM 3Nov00 	GETDLGITEM(IDC_RLISTBOXCTRL1)->SetColumnWidth(5,1);
//DeadCode JIM 3Nov00 
}


BEGIN_MESSAGE_MAP(RAFMissionFolder, CDialog)
	//{{AFX_MSG_MAP(RAFMissionFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFMissionFolder message handlers
void RAFMissionFolder::RefreshData(int childnum)
{
	if (childnum == -2)
	{
		TotalRefresh();
	}
}
void	RAFMissionFolder::FindPackages()
{
	currpacklist = 0;
	int pack=0;

	for (int i = 0; i <= MAX_PACKLIST;i++)
		packlist[i].pack = 65535;

	while (pack < Profile::MAX_PACKS)
	{
		if (		(Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
				&&	(		(	(!MMC.rafplanned)	&&	(Todays_Packages.pack[pack].packagestatus>=Profile::PS_PLANNING)	&&	(Todays_Packages.pack[pack].packagestatus<Profile::PS_TAKINGOFF))
						||	(	(!MMC.rafoutgoing)	&&	(Todays_Packages.pack[pack].packagestatus>=Profile::PS_TAKINGOFF)	&&	(Todays_Packages.pack[pack].packagestatus<Profile::PS_ENEMYSIGHTED))
						||	(	(!MMC.rafengaged)	&&	(Todays_Packages.pack[pack].packagestatus>=Profile::PS_ENEMYSIGHTED)	&&	(Todays_Packages.pack[pack].packagestatus<Profile::PS_OUTGOING))
						||	(	(!MMC.rafincoming)	&&	(Todays_Packages.pack[pack].packagestatus>=Profile::PS_OUTGOING)	&&	(Todays_Packages.pack[pack].packagestatus<Profile::PS_ACTIVE_MAX))
						||	(	(!MMC.raflanded)	&&	(Todays_Packages.pack[pack].packagestatus>=Profile::PS_ACTIVE_MAX))
					)
				&&	(
							(	(!MMC.rafpatrol)	&&	(Todays_Packages.pack[pack].attackmethod == Profile::AM_PATROL))
						||	(	(!MMC.rafintercept)	&&	(Todays_Packages.pack[pack].attackmethod == Profile::AM_INTERCEPT))
					)
			)
	
		{
		 	Profile& pk = Todays_Packages.pack[pack];
			if (pk.attackmethod < Profile::AM_LWPACKS)
			{

				int i=0;
//DeadCode JIM 20Oct00 				int acnum = 0;
				while (i < pk.squadlist)
				{
						FillPackList(pack, pk[i].targetindex, pk.attackmethod, 
							pk[i].numacleft, pk[i].takeofftime, pk[i].squadnum, i);
						i++;
				}
			}
		}
		pack++;
	}


}
void RAFMissionFolder::FillPackList(UWord	pack, UByte	target, UByte method, UWord numofac, int takeofftime, UWord squadron, int sqnum)
{
	enum {WRAPTHROW=10};
	if (currpacklist == MAX_PACKLIST)
	{
		for (int i=0;i<MAX_PACKLIST-WRAPTHROW;i++)
			packlist[i]=packlist[i+WRAPTHROW];
		currpacklist-=WRAPTHROW;
	}
//DeadCode JIM 2Oct00 	if (currpacklist < MAX_PACKLIST)
//DeadCode JIM 2Oct00 	{
		packlist[currpacklist].pack = pack;
		packlist[currpacklist].target = target;
		packlist[currpacklist].method = method;
		packlist[currpacklist].takeofftime = takeofftime;
		packlist[currpacklist].squadron = squadron;
		packlist[currpacklist].sqnum = sqnum;
		packlist[currpacklist++].numofac = numofac;
//DeadCode JIM 2Oct00 	}
}
void	RAFMissionFolder::RefreshButtons()
{
	if (Todays_Packages.hipack != -1)
	{
		CRButton*	but = GETDLGITEM(IDC_RBUTTONINTELL);
		but->SetForeColor(RGB(255,255,0));
		but->SetBackColor(RGB(255,255,0));
		but->SetDisabled(false);
		but = GETDLGITEM(IDC_RBUTTONROUTE);
		but->SetForeColor(RGB(255,255,0));
		but->SetBackColor(RGB(255,255,0));
		but->SetDisabled(false);

		but = GETDLGITEM(IDC_RBUTTONTASK);
		if (Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_TARGETAREA)
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetBackColor(RGB(255,255,0));
			if 	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_ACTIVE_MIN)
				but->SetString(RESSTRING(TASK));
			else
				but->SetString(RESSTRING(REVECTOR));
			but->SetDisabled(false);
		}
		else
		{
			but->SetDisabled(true);
		}

		if 	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus >= Profile::PS_REFUELLING)	//RDH 28Aug00
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetDisabled(true);										//RDH 28Aug00
		}

		but = GETDLGITEM(IDC_RBUTTONDELETE);
		but->SetDisabled(false);
		but->SetForeColor(RGB(255,255,0));
		if 	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_ACTIVE_MIN)
			but->SetString(RESSTRING(DELETE));
		else
			but->SetString(RESSTRING(RTB));

		if 	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus >= Profile::PS_REFUELLING)	//RDH 28Aug00
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetDisabled(true);										//RDH 28Aug00
		}


		but = GETDLGITEM(IDC_RBUTTONSQUADRON);
		but->SetForeColor(RGB(255,255,0));
		but->SetDisabled(false);
   		but = GETDLGITEM(IDC_RBUTTONFRAG);
		if 	(		(Todays_Packages.pack[Todays_Packages.hipack].packagestatus > Profile::PS_ACTIVE_MIN)
				&&	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_LANDING)
			)
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetDisabled(false);
		}else
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}




	}else
	{
		CRButton*	but = GETDLGITEM(IDC_RBUTTONINTELL);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONROUTE);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONTASK);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONDELETE);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONSQUADRON);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
		but = GETDLGITEM(IDC_RBUTTONFRAG);
		but->SetForeColor(RGB(160,160,0));
		but->SetBackColor(RGB(160,160,0));
		but->SetDisabled(true);
	}

}
void	RAFMissionFolder::RefreshList()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(40);
	//rlistbox->AddColumn(70);										  //RDH 02/06/99
	//rlistbox->AddColumn(70);										  //RDH 02/06/99
	//rlistbox->AddColumn(50);										  //RDH 02/06/99
	//rlistbox->AddColumn(60);
	//rlistbox->AddColumn(50);										  //RDH 02/06/99
	//rlistbox->AddColumn(70);										  //RDH 02/06/99
	//rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	//rlistbox->AddColumn(60);
	rlistbox->AddString(RESSTRING(ORDER),0);
	rlistbox->AddString(RESSTRING(SQUADRON),1);
	rlistbox->AddString(RESSTRING(STATUS),2);
	rlistbox->AddString(RESSTRING(TALLY),3);
	rlistbox->AddString(RESSTRING(OBJECTIVE)+" ("+RESSTRING(SIZE)+")",4);
	rlistbox->AddString("",5);
	rlistbox->AddString(RESSTRING(STATUS),6);
	rlistbox->AddString(RESSTRING(TARGET),7);
	rlistbox->AddString(RESSTRING(STATUS),8);

	int p=0;
	int t;
//DeadCode JIM 5Nov00 	sq;
//DeadCode JIM 5Nov00 	Squadron* lwsq;
	
	while (packlist[p].pack != 65535)
	{
		Pack& packlistP=packlist[p];
		Profile& pk = Todays_Packages.pack[packlistP.pack];

 		char* raidletter = Todays_Packages.RaidFormatString(packlistP.pack,0);
		rlistbox->AddString(CSprintf(raidletter, pk.raidnumentries[0].raidnum),0);

//DEADCODE RDH 12/04/00 		rlistbox->AddString(CSprintf("F%03i", pk.raidnumentries[0].raidnum),0);

//DEADCODE RDH 21/01/00 		int sqnum = packlist[p].squadron;
//DEADCODE RDH 21/01/00 		SquadNum squid = Node_Data.squadron[sqnum].squadron;
//DEADCODE RDH 21/01/00 		sq = Node_Data[squid];

		Squadron* sq = Node_Data[(SquadNum)packlistP.squadron];
		rlistbox->AddString(CSprintf("%4s (%i)",sq->SubName(), packlistP.numofac),1);



//DEADCODE CSB 08/05/00 		rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),2);
 		rlistbox->AddString(RESLIST(PS_SPARE,pk[packlistP.sqnum].status),2);		//JIM 6Sep00



		int lwpack = 0, sqnum;
		UniqueID trguid=pk.packagetarget[1];
		int uidband=Persons2::getbandfromUID(trguid);	
		if (uidband != SagBAND)
		{
			trguid = pk.packagetarget[packlistP.target];
			uidband=Persons2::getbandfromUID(trguid);	
		}

		if (trguid>IllegalBAND || uidband == SagBAND)
		{
			Todays_Packages.GetACSquadEntry(trguid,lwpack,sqnum);
			
			Profile& lwpk = Todays_Packages.pack[lwpack];
//DEADCODE RDH 12/04/00 			rlistbox->AddString(GetTargName(trguid),4);

			int raidline = lwpk.GetRaidIndFromSquadEntry(sqnum);

			char* raidletter = Todays_Packages.RaidFormatString(lwpack,raidline);
			CString raidmsg=CSprintf(raidletter, lwpk.raidnumentries[raidline].raidnum);
//DeadCode JIM 3Nov00 			rlistbox->AddString(raidmsg,4);


//DEADCODE RDH 12/04/00  			rlistbox->AddString(CSprintf("R%03i", lwpk.raidnumentries[raidline].raidnum),4);

			int firstsq = lwpk.raidnumentries[raidline].squadliststart;
			int i = firstsq;
			int lastsq;
			lastsq = lwpk.RaidNumEntriesMaxSq(raidline);

 

			int lwac=0;
			while (i <= lastsq)
				lwac += lwpk[i++].numacleft;							//RDH 9Aug00
			rlistbox->AddString(CSprintf("%s     (%i)", raidmsg,lwac),4);

			rlistbox->AddString(RESLIST(PS_SPARE,lwpk.packagestatus),6);
			if (	pk.packagestatus<=Profile::PS_FORMING
				&&	(pk.cancelsquad==SQ_MAX||pk.cancelsquad==packlistP.squadron)
				)
				rlistbox->AddString(RESSTRING(BINGOWARNING),7);
			else
				rlistbox->AddString(GetTargName(lwpk.packagetarget[0].currentid),7);



	 		TargetNoDetail* trg = Node_Data[lwpk.packagetarget[0].currentid];
			if (trg)
			{
				int j = trg->truestatus;
				if		(j >= Target::TS_DESTROYED)		j=3;
				elseif	(j>=Target::TS_BADDAMAGE)		j=2;
				elseif	(j>=Target::TS_LIGHTDAMAGE)		j=1;
				else									j=0;
				rlistbox->AddString(RESLIST(UNDAMAGED, j),8);
			}
	//3 tally
			int acnum = 0, acorg = 0, acleft = 0;
			int rafraidline = pk.GetRaidIndFromSquadEntry((SquadNum)packlistP.squadron);

			int raffirstsq = pk.raidnumentries[rafraidline].squadliststart;
			i = raffirstsq;
			int raflastsq;
			raflastsq = pk.RaidNumEntriesMaxSq(rafraidline);


			while (i <= raflastsq)
			{
				acorg += pk[i].numacoriginal;
				acleft += pk[i].numacleft;
				i++;
			}

			int losses = acorg - acleft;


			i=firstsq;
			acorg = 0;
			acleft = 0;
			while (i <=lastsq)
			{
				acorg += lwpk[i].numacoriginal;
				acleft += lwpk[i].numacleft;
				i++;
			}

			int kills = acorg - acleft;

			rlistbox->AddString(CSprintf("+%i -%i", kills, losses),3);



		}else
		{
			rlistbox->AddString(GetTargName(trguid),4);
			rlistbox->AddString(RESSTRING(DASH),3);
			rlistbox->AddString(" ",5);
			rlistbox->AddString(" ",6);
			if (	pk.packagestatus<=Profile::PS_FORMING
				&&	(pk.cancelsquad==SQ_MAX||pk.cancelsquad==packlistP.squadron)
				)
				rlistbox->AddString(RESSTRING(BINGOWARNING),7);
			else
				rlistbox->AddString(" ",7);
			rlistbox->AddString(" ",8);
		}
		p++;
	}
}
void RAFMissionFolder::RefreshTickBoxes()
{
 	CRButton* b;

	b = GETDLGITEM(IDC_PLANNED);
	b->SetPressed(!MMC.rafplanned);

	b = GETDLGITEM(IDC_OUTGOING);
	b->SetPressed(!MMC.rafoutgoing);


	b = GETDLGITEM(IDC_ENGAGING);
	b->SetPressed(!MMC.rafengaged);


	b = GETDLGITEM(IDC_INCOMING);
	b->SetPressed(!MMC.rafincoming);


	b = GETDLGITEM(IDC_LANDED);
	b->SetPressed(!MMC.raflanded);

	b = GETDLGITEM(IDC_PATROLS);
	b->SetPressed(!MMC.rafpatrol);

		b = GETDLGITEM(IDC_INTERCEPTS);
	b->SetPressed(!MMC.rafintercept);

}
void RAFMissionFolder::TotalRefresh()
{
	RefreshTickBoxes();

	FindPackages();
	RefreshList();
 	FindHiLight();
	RefreshButtons();

}
void RAFMissionFolder::FindHiLight()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	currpack = -1;
	int p=0;
	while  (		(packlist[p].pack != 65535)
				&&	(	!(		(packlist[p].pack == Todays_Packages.hipack)
							&&	(packlist[p].sqnum == Todays_Packages.hisquad)
						)
					)
			)
	{
		p++;
	}
	if (packlist[p].pack == Todays_Packages.hipack)
	{
			currpack = p;
			RDialog::m_pView->SetHiLightInfo(packlist[currpack].pack, Todays_Packages.hisquad,UID_Null);

			rlistbox->SetHilightRow(currpack+1);
	}else if (p > 0)
	{
			currpack = 0;
			RDialog::m_pView->SetHiLightInfo(packlist[currpack].pack, 0,UID_Null);
			rlistbox->SetHilightRow(currpack+1);
	}else
	{
		Todays_Packages.hipack = -1;
	}
}
BOOL RAFMissionFolder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	TotalRefresh();


//DEADCODE RDH 14/01/00 	rlistbox->AddString("1",0);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("60 Spitfire(4)",1);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("Engaging",2);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("3/2",3);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("H100",4);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("100+",5);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("Incoming",6);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("Biggin Hill",7);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("Operational",8);
//DEADCODE RDH 14/01/00 
//DEADCODE RDH 14/01/00 	rlistbox->AddString("2",0);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("25 Hurricane(3)",1);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("Approaching",2);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("0/0",3);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("H102",4);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("20+",5);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("Outgoing",6);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("Kenley",7);
//DEADCODE RDH 14/01/00 	rlistbox->AddString("Damaged",8);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(RAFMissionFolder, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFMissionFolder)
	ON_EVENT(RAFMissionFolder, IDC_RBUTTONROUTE, 1 /* Clicked */, OnClickedRbuttonroute, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_RBUTTONTASK, 1 /* Clicked */, OnClickedRbuttontask, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_RBUTTONDELETE, 1 /* Clicked */, OnClickedRbuttondelete, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_RBUTTONINTELL, 1 /* Clicked */, OnClickedRbuttonintell, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_RBUTTONSQUADRON, 1 /* Clicked */, OnClickedRbuttonsquadron, VTS_NONE)
//DeadCode JIM 29Sep00 	ON_EVENT(RAFMissionFolder, IDC_RBUTTONRTB, 1 /* Clicked */, OnClickedRbuttonrtb, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(RAFMissionFolder, IDC_OUTGOING, 1 /* Clicked */, OnClickedOutgoing, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_LANDED, 1 /* Clicked */, OnClickedLanded, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_INCOMING, 1 /* Clicked */, OnClickedIncoming, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_ENGAGING, 1 /* Clicked */, OnClickedEngaging, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_PLANNED, 1 /* Clicked */, OnClickedPlanned, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_RBUTTONFRAG, 1 /* Clicked */, OnClickedRbuttonfrag, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_PATROLS, 1 /* Clicked */, OnClickedPatrols, VTS_NONE)
	ON_EVENT(RAFMissionFolder, IDC_INTERCEPTS, 1 /* Clicked */, OnClickedIntercepts, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RAFMissionFolder::OnClickedRbuttonroute() 
{
#ifndef	BOB_DEMO_VER

	if (Todays_Packages.hipack >= 0)
		MainToolBar().OpenRoute();

#endif	
}

void RAFMissionFolder::OnClickedRbuttontask() 
{
#ifndef	BOB_DEMO_VER

	if 	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_ACTIVE_MIN)
	{
		if (Todays_Packages.pack[Todays_Packages.hipack].packagestatus!=Profile::PS_SPARE)
			TitleBarPtr().OpenRAFTask();
	}else
	{//revector
//DEADCODE RDH 17/05/00 		Save_Data.mapfilters = 0;
//DEADCODE RDH 17/05/00 		Save_Data.mapfilters|=FILT_LWSAG;

//DEADCODE RDH 17/05/00 		m_pView->m_mapdlg.Invalidate();
//DEADCODE RDH 17/05/00 
		TitleBarPtr().OpenSelTrg(packlist[currpack].sqnum, -1, PackageList::DISPLAY_STAFFEL, STM_LWAC);
		TotalRefresh();


	}
#endif	
}
void RAFMissionFolder::ChildDialClosed(int dialnum,RDialog*,int rv)
{
	TotalRefresh();
}
void RAFMissionFolder::OnClickedRbuttondelete() 
{
	if 	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_ACTIVE_MIN)
	{
		Todays_Packages.DeletePack(Todays_Packages.hipack);
	}else
	{//rtb
	  Todays_Packages.pack[Todays_Packages.hipack].ReturnHome();
	}
	TotalRefresh();
	Campaign::GlobalRefreshData();

}

void RAFMissionFolder::OnClickedRbuttonintell() 
{
#ifndef	BOB_DEMO_VER
	UniqueID objective=Todays_Packages.pack[Todays_Packages.hipack].packagetarget[1];
	if (objective==UID_NULL)
		objective=Todays_Packages.pack[Todays_Packages.hipack].packagetarget[0];
	int lwpack = -1, sqnum=0;
	if (objective)
		if (objective>IllegalBAND || Persons2::getbandfromUID(objective)==SagBAND)
			Todays_Packages.GetACSquadEntry(objective,lwpack,sqnum);
	if (lwpack>=0)
	{
		RDialog::m_pView->SetHiLightInfo(lwpack, sqnum,UID_Null);
		MainToolBar().OpenHostileslist();
	}
	else
		if (objective)
			MainToolBar().OpenDossier(objective);
#endif
}

void RAFMissionFolder::OnClickedRbuttonsquadron() 
{
#ifndef	BOB_DEMO_VER

	UniqueID homeuid = Node_Data[(SquadNum)packlist[currpack].squadron].homeairfield;
	int j=2, i = 0;			//exit the loop on reahing desired squad, inc j for others squads on field

	while	(		(Node_Data.squadron[i].squadron != packlist[currpack].squadron)
				&&	(Node_Data.squadron[i].squadron != SQ_ZERO)
				)	
	{
	  if (Node_Data.squadron[i].homeairfield == homeuid)
	  {
		  j++;
	  }
	  i++;
	}

	if (Node_Data.squadron[i].squadron != SQ_ZERO)
		MainToolBar().OpenACDossier(homeuid,j);

#endif	
}

//DeadCode JIM 29Sep00 void RAFMissionFolder::OnClickedRbuttonrtb() 
//DeadCode JIM 29Sep00 {	SUBFUNCTION OF DELETE
//DeadCode JIM 29Sep00 	// TODO: Add your control notification handler code here
//DeadCode JIM 29Sep00 	
//DeadCode JIM 29Sep00 }

void RAFMissionFolder::OnSelectRlistboxctrl1(long row, long column) 
{
	if (row > 0)
	{
		currpack = row - 1;

	 	Profile& pk = Todays_Packages.pack[packlist[currpack].pack];
		int i = 0;
		while	(		(i < pk.squadlist)
					&&	(pk[i].squadnum	 != packlist[currpack].squadron)
				)
		{
			i++;
		}
 
		if (pk[i].squadnum	 != packlist[currpack].squadron)
			i = 0;


		RDialog::m_pView->SetHiLightInfo(packlist[currpack].pack, i,UID_Null);



		TotalRefresh();
		m_pView->m_mapdlg.Invalidate();
	}

	
}

void RAFMissionFolder::OnClickedOutgoing() 
{
	if	(MMC.rafoutgoing)
	   MMC.rafoutgoing = false;
	else
	   MMC.rafoutgoing = true;
	TotalRefresh();
	
}

void RAFMissionFolder::OnClickedLanded() 
{
	if	(MMC.raflanded)
	   MMC.raflanded = false;
	else
	   MMC.raflanded = true;
	TotalRefresh();
	
}

void RAFMissionFolder::OnClickedIncoming() 
{
	if	(MMC.rafincoming)
	   MMC.rafincoming = false;
	else
	   MMC.rafincoming = true;
	TotalRefresh();
	
}

void RAFMissionFolder::OnClickedEngaging() 
{
	if	(MMC.rafengaged)
	   MMC.rafengaged = false;
	else
	   MMC.rafengaged = true;
	TotalRefresh();
	
}

void RAFMissionFolder::OnClickedPlanned() 
{
	if	(MMC.rafplanned)
	   MMC.rafplanned = false;
	else
	   MMC.rafplanned = true;
	TotalRefresh();

	
}

void RAFMissionFolder::OnClickedRbuttonfrag() 
{
#ifndef	BOB_DEMO_VER

	MainToolBar().OnClickedFrag2();
#endif	
}

void RAFMissionFolder::OnClickedPatrols() 
{
	if	(MMC.rafpatrol)
	   MMC.rafpatrol = false;
	else
	   MMC.rafpatrol = true;
	TotalRefresh();
	
}

void RAFMissionFolder::OnClickedIntercepts() 
{
	if	(MMC.rafintercept)
	   MMC.rafintercept = false;
	else
	   MMC.rafintercept = true;
	TotalRefresh();
	
}
