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

// RowanDialog: // LWMssFr.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "LWMssFr.h"
#include "package.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// LWMissionFolder dialog


RDialog*	LWMissionFolder::Make(bool specialnotakeoffs)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_MAX),
			DialBox(FIL_D_LWMISSONFOLDER,new LWMissionFolder(specialnotakeoffs))
			);
}


LWMissionFolder::LWMissionFolder(bool specialnotakeoffs,CWnd* pParent /*=NULL*/)
	: RowanDialog(LWMissionFolder::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWMissionFolder)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->specialnotakeoffs=specialnotakeoffs;
}


void LWMissionFolder::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWMissionFolder)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RBUTTONROUTE, m_IDC_RBUTTONROUTE);
	DDX_Control(pDX, IDC_RBUTTONSQUADRON, m_IDC_RBUTTONSQUADRON);
	DDX_Control(pDX, IDC_RBUTTONTASK, m_IDC_RBUTTONTASK);
	DDX_Control(pDX, IDC_RBUTTONINTELL, m_IDC_RBUTTONINTELL);
	DDX_Control(pDX, IDC_RBUTTONDELETE, m_IDC_RBUTTONDELETE);
	DDX_Control(pDX, IDC_ACTIVE, m_IDC_ACTIVE);
	DDX_Control(pDX, IDC_ESCORT, m_IDC_ESCORT);
	DDX_Control(pDX, IDC_LANDED, m_IDC_LANDED);
	DDX_Control(pDX, IDC_PLANNED, m_IDC_PLANNED);
	DDX_Control(pDX, IDC_RECONN, m_IDC_RECONN);
	DDX_Control(pDX, IDC_STRIKE, m_IDC_STRIKE);
	DDX_Control(pDX, IDC_SWEEP, m_IDC_SWEEP);
	DDX_Control(pDX, IDC_RBUTTONFRAG, m_IDC_RBUTTONFRAG);

	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
	if (specialnotakeoffs)
	{
		CRButton* button=GetDlgItem(IDJ_TITLE);
		button->SetString(RESSTRING(BINGOWARNING));
	}
}


BEGIN_MESSAGE_MAP(LWMissionFolder, CDialog)
	//{{AFX_MSG_MAP(LWMissionFolder)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWMissionFolder message handlers
void LWMissionFolder::RefreshData(int childnum)
{
	if (childnum == -2)
	{
		TotalRefresh();
	}
}

void	LWMissionFolder::FindPackages()
{
	currpacklist = 0;
	int pack=0;

	for (int i = 0; i <= MAX_PACKLIST;i++)
		packlist[i].pack = 65535;
	MakeField<Profile::PackageStatus,Profile::PS_SPARE,Profile::PS_AIRFIELDOUT>	statusmask={0};
	if (specialnotakeoffs ||  !MMC.lwplanned)
	{
		statusmask<<Profile::PS_ORDER_30<<Profile::PS_AT_30<<Profile::PS_ORDER_5<<Profile::PS_AT_5<<Profile::PS_ORDER_2<<Profile::PS_AT_2<<Profile::PS_PLANNING;
		statusmask<<Profile::PS_PLANNED<<Profile::PS_PLAN_30<<Profile::PS_PLAN_5<<Profile::PS_PLAN_2<<Profile::PS_ACTIVE_MIN;
	}
	if (!specialnotakeoffs)
	{
		if (!MMC.lwactive)
			statusmask<<Profile::PS_TAKINGOFF<<Profile::PS_FORMING<<Profile::PS_INCOMING<<Profile::PS_TARGETAREA<<Profile::PS_DETAILRAID<<Profile::PS_ENEMYSIGHTED<<Profile::PS_OUTGOING;
		if (!MMC.lwlanded)
			statusmask<<Profile::PS_ACTIVE_MAX<<Profile::PS_LANDING<<Profile::PS_REFUELLING<<Profile::PS_COMPLETE;
	}
	int mincancelsquad=0;
	if (specialnotakeoffs)
		mincancelsquad=1;

	while (pack < Profile::MAX_PACKS)
	{
	 	Profile& pk = Todays_Packages.pack[pack];
		if (	statusmask[pk.packagestatus]
			&&	pk.cancelsquad>=mincancelsquad
			)

		{
			if  (		(pk.attackmethod >= Profile::AM_LWPACKS)
				)
			{
				int targetnum = 0;
				int tnreal = 0, tnfake = 0;
				while (		(pk.packagetarget[tnreal].currentid)
						||	(tnfake > -4)
					   )
				{
					if	(pk.packagetarget[tnreal].currentid)
					{
						targetnum = tnreal++;
					}else
					{
						targetnum = --tnfake;
					}
					int i=0;
					int strike=0,detachedescort =0, attachedescort =0, returnescort = 0;
					int strikeleft=0,detachedescortleft =0, attachedescortleft =0, returnescortleft = 0;
					int striketo=0,detachedescortto =0, attachedescortto =0, returnescortto = 0;
					enum {NOTDEFINED = 65535};
					UWord strikegruppe = NOTDEFINED, detachedgruppe = NOTDEFINED, attachedgruppe =NOTDEFINED, returngruppe = NOTDEFINED;
					while (i < pk.squadlist)
 					{
						if	(		specialnotakeoffs
								||	(	(!MMC.lwstrike)	&&	(pk[i].method < Profile::AM_DETACHED))
								||	(	(!MMC.lwattachedescort)	&&	(pk[i].method >= Profile::AM_DETACHED)	&&	(pk[i].method < Profile::AM_ATTACHED))
								||	(	(!MMC.lwdetachedescort)	&&	(pk[i].method >= Profile::AM_ATTACHED)	&&	(pk[i].method < Profile::AM_RETURNESCORT))
								||	(	(!MMC.lwreconn)	&&	(pk[i].method >= Profile::AM_RETURNESCORT)	)
							)
						{
							if (pk[i].targetindex == targetnum)
							{
								if (pk[i].method == pk.attackmethod)
								{
									strike += pk[i].numacoriginal;
									strikeleft += pk[i].numacleft;
									if (strikegruppe ==NOTDEFINED)
									{
										striketo = pk[i].takeofftime;
										strikegruppe = pk[i].squadnum;
									}
								}
								if (pk[i].method >= Profile::AM_RETURNESCORT)
								{
									returnescort += pk[i].numacoriginal;
									returnescortleft += pk[i].numacleft;
									if (returngruppe ==NOTDEFINED)
									{
										returnescortto = pk[i].takeofftime;
										returngruppe  = pk[i].squadnum;
									}
								}else if (pk[i].method >= Profile::AM_ATTACHED)
								{
									attachedescort += pk[i].numacoriginal;
									attachedescortleft += pk[i].numacleft;
									if (attachedgruppe ==NOTDEFINED)
									{
										attachedescortto = pk[i].takeofftime;
										attachedgruppe  = pk[i].squadnum;
									}
								}
								else if (pk[i].method >= Profile::AM_DETACHED)
								{
									detachedescort += pk[i].numacoriginal;
									detachedescortleft += pk[i].numacleft;
									if (detachedgruppe ==NOTDEFINED)
									{
										detachedescortto = pk[i].takeofftime;
										detachedgruppe = pk[i].squadnum;
									}
								}
							}		
						}
						i++;
					}
					if (strike)
						FillPackList(pack, targetnum, pk.attackmethod, strike, striketo, strikegruppe, strikeleft);
					if (attachedescort)
						FillPackList(pack, targetnum,
										 Profile::AM_ATTACHED, attachedescort, attachedescortto, attachedgruppe, attachedescortleft);
					if (detachedescort)
						FillPackList(pack, targetnum,
										 Profile::AM_DETACHED, detachedescort, detachedescortto, detachedgruppe, detachedescortleft);
					if (returnescort)
						FillPackList(pack, targetnum,
										 Profile::AM_RETURNESCORT, returnescort, returnescortto, returngruppe, returnescortleft);
					
				}
			}
		}


		pack++;
	}


}
int LWMissionFolder::FillPackList(UWord	pack, UByte	target, UByte method, UWord numofac, int takeofftime, UWord gruppe, UWord numofacleft)
{
	enum {WRAPTHROW=10};
	if (currpacklist == MAX_PACKLIST)
	{
		for (int i=0;i<MAX_PACKLIST-WRAPTHROW;i++)
			packlist[i]=packlist[i+WRAPTHROW];
		currpacklist-=WRAPTHROW;
	}
	packlist[currpacklist].pack = pack;
	packlist[currpacklist].target = target;
	packlist[currpacklist].method = method;
	packlist[currpacklist].takeofftime = takeofftime;
	packlist[currpacklist].gruppe = gruppe;
	packlist[currpacklist].numofacleft = numofacleft;
	packlist[currpacklist].numofac = numofac;
	return currpacklist++;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    RefreshButtons
// Date:		06/11/00
// Author:		JIM
//
//Description: No attempt is made to keep buttons in UP position,
//				so must set BAck as well as Fore Colour.
//////////////////////////////////////////////////////////////////////
void	LWMissionFolder::RefreshButtons()
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
		if 	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_ACTIVE_MIN)
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetBackColor(RGB(255,255,0));
			but->SetDisabled(false);
		}else
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}
		but = GETDLGITEM(IDC_RBUTTONDELETE);
		if 	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_ACTIVE_MIN)
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetBackColor(RGB(255,255,0));
			but->SetDisabled(false);
		}else
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}
		but = GETDLGITEM(IDC_RBUTTONSQUADRON);
		but->SetForeColor(RGB(255,255,0));
		but->SetBackColor(RGB(255,255,0));
		but->SetDisabled(false);
   		but = GETDLGITEM(IDC_RBUTTONFRAG);
		if 	(		(Todays_Packages.pack[Todays_Packages.hipack].packagestatus > Profile::PS_ACTIVE_MIN)
				&&	(Todays_Packages.pack[Todays_Packages.hipack].packagestatus <= Profile::PS_LANDING)
			)
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetBackColor(RGB(255,255,0));
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

void UpdateRAFTally(Profile& rafpk, int& acorg, int& acleft)
{
	int i=0;
	while (i < rafpk.squadlist)
	{
		acorg	+= rafpk[i].numacoriginal;
		acleft	+= rafpk[i].numacleft;
		i++;
	}

}


int LWMissionFolder::FindAssociatedRAFPackInfo(UniqueID lwuid, int& acorg, int& acleft)
{
	int p=0;
	acorg = 0; acleft = 0;
	int retval = -1;
	while (p < Profile::MAX_PACKS)
	{	
		if (Todays_Packages.pack[p].packagestatus!=Profile::PS_SPARE)
		{
			Profile& pk = Todays_Packages.pack[p];
			if (pk.packagetarget[0] == lwuid || pk.packagetarget[1] == lwuid )
			{
				retval = p;
				UpdateRAFTally(pk, acorg, acleft);
			}
		}
		p++;
	}
	return (retval);
}
void	LWMissionFolder::RefreshList()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00  	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(40);
	//rlistbox->AddColumn(30);										  //RDH 02/06/99
	//rlistbox->AddColumn(90);										  //RDH 02/06/99
	//rlistbox->AddColumn(50);										  //RDH 02/06/99
	//rlistbox->AddColumn(50);
//DEADCODE RDH 08/05/00 	rlistbox->AddColumn(50);										  //RDH 02/06/99
	//rlistbox->AddColumn(70);										  //RDH 02/06/99
	//rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	//rlistbox->AddColumn(50);
	//rlistbox->AddColumn(60);
	rlistbox->AddString(RESSTRING(RAID),0);
	rlistbox->AddString(RESSTRING(SIZE),1);
	rlistbox->AddString(RESSTRING(TYPE),2);
	rlistbox->AddString(RESSTRING(TO),3);
	rlistbox->AddString(RESSTRING(TOT),4);
//DEADCODE RDH 08/05/00 	rlistbox->AddString(RESSTRING(ETA),5);
	rlistbox->AddString(RESSTRING(STATUS),5);
	rlistbox->AddString(RESSTRING(TARGET),6);
	if (specialnotakeoffs)
	{
		rlistbox->AddString(RESSTRING(RTB),7);
		rlistbox->AddString(RESSTRING(CANCEL),8);

	}
	else
	{
		rlistbox->AddString(RESSTRING(RAF),7);
		rlistbox->AddString(RESSTRING(TALLY),8);
	}


	int p=0;
	int t;
	while (packlist[p].pack != 65535)
	{
		Profile& pk = Todays_Packages.pack[packlist[p].pack];
		if (packlist[p].method < Profile::AM_DETACHED)
		{
	 		char* raidletter = Todays_Packages.RaidFormatString(packlist[p].pack,0);
			rlistbox->AddString(CSprintf(raidletter, pk.raidnumentries[0].raidnum),0);

			rlistbox->AddString(GetTargName(pk.packagetarget[packlist[p].target].currentid),6);
			t=pk.primarytargetETA/60;
			rlistbox->AddString(CSprintf("%02i:%02i",t/60,t%60),4);
			rlistbox->AddString(RESLIST(PS_SPARE,pk.packagestatus),5);


 			int acnum = 0, acorg = 0, acleft = 0,finishedacorg=0,finishedacleft=0,finishedrafpack=-1;
			int rafpack =0;
			if (pk[0].instance)
				rafpack = FindAssociatedRAFPackInfo(pk[0].instance, acorg, acleft);
//DeadCode JIM 13Nov00 			else
			finishedrafpack = FindAssociatedRAFPackInfo(UniqueID(UID_BIT14+(packlist[p].pack<<5)), finishedacorg, finishedacleft);
			
			if  (	(rafpack >= 0) || finishedrafpack>=0
//DeadCode JIM 13Nov00 				&&	(Todays_Packages.pack[rafpack].packagestatus!=Profile::PS_SPARE)
				)
			{	   acorg+=finishedacorg;acleft+=finishedacleft;
//DeadCode RDH 16Sep00 				int i=0;
//DeadCode RDH 16Sep00 				acorg = 0;
//DeadCode RDH 16Sep00 				acleft = 0;
//DeadCode RDH 16Sep00 				while (i < pk.squadlist)
//DeadCode RDH 16Sep00 				{
//DeadCode RDH 16Sep00 					acorg = pk[i].numacoriginal;
//DeadCode RDH 16Sep00 					acleft = pk[i].numacleft;
//DeadCode RDH 16Sep00 					i++;
//DeadCode RDH 16Sep00 				}
				int losses = packlist[p].numofac - packlist[p].numofacleft;

//DeadCode RDH 16Sep00 				rlistbox->AddString(CSprintf("%i", acleft),7);


//DeadCode RDH 16Sep00 				i=0;
//DeadCode RDH 16Sep00 				acorg = 0;
//DeadCode RDH 16Sep00 				acleft = 0;
//DeadCode RDH 16Sep00 				Profile& rafpk = Todays_Packages.pack[rafpack];
//DeadCode RDH 16Sep00 
//DeadCode RDH 16Sep00 				while (i < rafpk.squadlist)
//DeadCode RDH 16Sep00 				{
//DeadCode RDH 16Sep00 					acorg = rafpk[i].numacoriginal;
//DeadCode RDH 16Sep00 					acleft = rafpk[i].numacleft;
//DeadCode RDH 16Sep00 					i++;
//DeadCode RDH 16Sep00 				}
//DeadCode RDH 16Sep00 
//DeadCode MS 26Sep00 				FindAssociatedRAFPackInfo(pk[0].instance, acorg, acleft);

				int kills = acorg - acleft;
				rlistbox->AddString(CSprintf("%i", acleft),7);
				rlistbox->AddString(CSprintf("+%i -%i", kills, losses),8);
			}else
			{
				if (pk.packagestatus<=Profile::PS_FORMING && pk.cancelsquad)
				{
					rlistbox->AddString(RESSTRING(RTB),7);
					if (pk.cancelsquad==SQ_MAX)
						rlistbox->AddString(RESSTRING(RAID),8);
					else
						rlistbox->AddString(Node_Data[SquadNum(pk.cancelsquad)].ShortName(),8);
				}
				else
				{
					rlistbox->AddString("",7);
					rlistbox->AddString("",8);
				}
			}
		}else
		{
			rlistbox->AddString("",0);
			rlistbox->AddString("",4);
			rlistbox->AddString("",5);
			rlistbox->AddString("",6);
 				rlistbox->AddString("",7);								//MS 26Sep00
				rlistbox->AddString("",8);

		}
		rlistbox->AddString(CSprintf("%i", packlist[p].numofacleft),1);
		rlistbox->AddString(RESLIST(AM_PATROL,packlist[p].method),2);
		t=packlist[p].takeofftime/60;
		rlistbox->AddString(CSprintf("%02i:%02i",t/60,t%60),3);

		p++;
	}
}
void LWMissionFolder::TotalRefresh()
{
	RefreshTickBoxes();
	FindPackages();
	RefreshList();
 	FindHiLight();
	RefreshButtons();

}

void LWMissionFolder::RefreshTickBoxes()
{
 	CRButton* b;
	

	b = GETDLGITEM(IDC_PLANNED);
	if (specialnotakeoffs)
		b->SetPressed(true);
	else
		b->SetPressed(!MMC.lwplanned);

	b = GETDLGITEM(IDC_ACTIVE);
	if (specialnotakeoffs)
		b->SetPressed(false);
	else
	b->SetPressed(!MMC.lwactive);

	b = GETDLGITEM(IDC_LANDED);
	if (specialnotakeoffs)
		b->SetPressed(false);
	else
	b->SetPressed(!MMC.lwlanded);

	b = GETDLGITEM(IDC_STRIKE);
	if (specialnotakeoffs)
		b->SetPressed(true);
	else
	b->SetPressed(!MMC.lwstrike);

	b = GETDLGITEM(IDC_ESCORT);
	if (specialnotakeoffs)
		b->SetPressed(true);
	else
	b->SetPressed(!MMC.lwattachedescort);

	b = GETDLGITEM(IDC_SWEEP);
	if (specialnotakeoffs)
		b->SetPressed(true);
	else
	b->SetPressed(!MMC.lwdetachedescort);

	b = GETDLGITEM(IDC_RECONN);
	if (specialnotakeoffs)
		b->SetPressed(true);
	else
	b->SetPressed(!MMC.lwreconn);
}


BOOL LWMissionFolder::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	currpack = -1;

	
//DEADCODE ROD 17/12/99 	rlistbox->AddString("H100",0);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("20",1);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("Strike",2);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("13:00",3);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("13:40",4);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("14:20",5);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("Inbound",6);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("Biggin Hill",7);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("30",8);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("3/2",9);
//DEADCODE ROD 17/12/99 
//DEADCODE ROD 17/12/99 	rlistbox->AddString("H101",0);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("1",1);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("Reconn",2);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("13:00",3);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("13:40",4);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("14:20",5);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("Inbound",6);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("Woolston",7);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("4",8);
//DEADCODE ROD 17/12/99 	rlistbox->AddString("3/2",9);
	
	TotalRefresh();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(LWMissionFolder, CDialog)
    //{{AFX_EVENTSINK_MAP(LWMissionFolder)
	ON_EVENT(LWMissionFolder, IDC_RBUTTONINTELL, 1 /* Clicked */, OnClickedRbuttonintell, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_RBUTTONROUTE, 1 /* Clicked */, OnClickedRbuttonroute, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_RBUTTONSQUADRON, 1 /* Clicked */, OnClickedRbuttonsquadron, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_RBUTTONTASK, 1 /* Clicked */, OnClickedRbuttontask, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(LWMissionFolder, IDC_RBUTTONRESPOND, 1 /* Clicked */, OnClickedRbuttonrespond, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_STRIKE, 1 /* Clicked */, OnClickedStrike, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_SWEEP, 1 /* Clicked */, OnClickedSweep, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_PLANNED, 1 /* Clicked */, OnClickedPlanned, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_ACTIVE, 1 /* Clicked */, OnClickedActive, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_ESCORT, 1 /* Clicked */, OnClickedEscort, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_LANDED, 1 /* Clicked */, OnClickedLanded, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_RECONN, 1 /* Clicked */, OnClickedReconn, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_RBUTTONDELETE, 1 /* Clicked */, OnClickedRbuttondelete, VTS_NONE)
	ON_EVENT(LWMissionFolder, IDC_RBUTTONFRAG, 1 /* Clicked */, OnClickedRbuttonfrag, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void LWMissionFolder::OnClickedRbuttonintell() 
{
#ifndef	BOB_DEMO_VER

		Profile& pk = Todays_Packages.pack[packlist[currpack].pack];
		if (packlist[currpack].target>=0)
			MainToolBar().OpenDossier(pk.packagetarget[packlist[currpack].target]);
		else
			MainToolBar().OpenDossier(pk.packagetarget[0]);

#endif	
}

void LWMissionFolder::OnClickedRbuttonroute() 
{
#ifndef	BOB_DEMO_VER

	if (Todays_Packages.hipack >= 0)
		MainToolBar().OpenRoute();

#endif
}

void LWMissionFolder::OnClickedRbuttonsquadron() 
{
#ifndef	BOB_DEMO_VER

//DEADCODE RDH 21/01/00 	MainToolBar().OpenACDossier(Node_Data.gruppe[packlist[currpack].gruppe - SQ_LW_START - 1].wadernum,
//DEADCODE RDH 21/01/00 				Node_Data.gruppe[packlist[currpack].gruppe - SQ_LW_START - 1].gruppennum);	
	Gruppen* gruppe = Node_Data[(SquadNum)packlist[currpack].gruppe];
 	MainToolBar().OpenACDossier(gruppe->wadernum,
				Node_Data.gruppe[packlist[currpack].gruppe - SQ_LW_START - 1].gruppennum);	

#endif
}

void LWMissionFolder::OnClickedRbuttontask() 
{
#ifndef	BOB_DEMO_VER

	if (Todays_Packages.pack[Todays_Packages.hipack].packagestatus!=Profile::PS_SPARE)
		TitleBarPtr().OpenLWTask();
#endif	
}

void LWMissionFolder::OnSelectRlistboxctrl1(long row, long column) 
{
	if (row > 0)
	{
		currpack = row - 1;
		int method=packlist[currpack].method&	Profile::AM_GROUPMASK;
		int	target=packlist[currpack].target;
	 	Profile& pk = Todays_Packages.pack[packlist[currpack].pack];
		int i = 0;
		while	(		(i < pk.squadlist)
				&&	(	(pk[i].targetindex!=target)
					||	((pk[i].method&Profile::AM_GROUPMASK)!=method)
				)	)
			i++;
 
		if (i == pk.squadlist)
			i = 0;

		if (packlist[currpack].pack!=Todays_Packages.hipack)
		{
			Todays_Packages.InvalidateRoute(&Todays_Packages[Todays_Packages.hipack],true,true);
		}
		RDialog::m_pView->SetHiLightInfo(packlist[currpack].pack, i,UID_Null);
		Todays_Packages.InvalidateRoute(&Todays_Packages[Todays_Packages.hipack],true,true);
//DeadCode JIM 8Nov00 		m_pView->m_mapdlg.Invalidate();
		RefreshButtons();												//RDH 16Aug00
	}



}
void LWMissionFolder::FindHiLight()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	currpack = -1;
	if (Todays_Packages.hipack != -1 && Todays_Packages[Todays_Packages.hipack].squadlist)
	{
		int am = Todays_Packages[Todays_Packages.hipack][Todays_Packages.hisquad].method;
		am =(am&Profile::AM_GROUPMASK);
		int tn=Todays_Packages[Todays_Packages.hipack][Todays_Packages.hisquad].targetindex;
		int p=0,pq=0;

		while  ((packlist[p].pack != 65535)	&& !(packlist[p].pack == Todays_Packages.hipack))
			p++;
		if (packlist[p].pack != 65535)
		{
			pq=p;
			while (packlist[p].pack == Todays_Packages.hipack)
				p++;
			do{	p--;
				if (packlist[p].target==tn)
				{
					pq=p;
					breakif ((packlist[p].method&Profile::AM_GROUPMASK)==am);
				}
			}while (packlist[p].pack == Todays_Packages.hipack);
		}
		p=pq;
		if (packlist[p].pack == Todays_Packages.hipack)
		{
				currpack = p;
				RDialog::m_pView->SetHiLightInfo(packlist[currpack].pack, Todays_Packages.hisquad,UID_Null);
				rlistbox->SetHilightRow(currpack+1);
		}else
		{
			Todays_Packages.hipack = -1;
		}
	}
}
void LWMissionFolder::OnClickedRbuttonrespond() 
{	//This is an extra key for testing purposes.
#ifndef NDEBUG
	int	packnum=-1;

	packnum=Todays_Packages.NewPackage((UniqueID)
		Todays_Packages[Todays_Packages.hipack][0].instance,
		NAT_RAF,Profile::AM_INTERCEPT);

   	if (packnum!=-1)
	{
		Todays_Packages[packnum].AddNumerousEscorts(10,0,0,Profile::BR_WIDESTPOSSIBLE);
			Todays_Packages[packnum].CalcRoutePositionsAndTime();
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].RecalcRoutePositions();
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].primarytargetETA = Todays_Packages[packnum].FindEarliestPrimaryTargetETA();//+(int)HR01;
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].SetPredictedPointFromETA(true);
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].RecalcRoutePositions();
//DEADCODE RDH 10/03/00 			Todays_Packages[packnum].primarytargetETA = Todays_Packages[packnum].FindEarliestPrimaryTargetETA();//+(int)HR01;
	}	

//temp until we can set in migldg in code, see ££
	Todays_Packages.hipack  = 1;
	m_pView->m_mapdlg.Invalidate();
	TotalRefresh();

#endif
}

void LWMissionFolder::OnClickedStrike() 
{
	if (specialnotakeoffs)
		specialnotakeoffs=false;
	else
		if	(MMC.lwstrike)
		   MMC.lwstrike = false;
		else
		   MMC.lwstrike = true;
	TotalRefresh();
}

void LWMissionFolder::OnClickedSweep() 
{
	if (specialnotakeoffs)
		specialnotakeoffs=false;
	else
		if	(MMC.lwdetachedescort)
		   MMC.lwdetachedescort = false;
		else
		   MMC.lwdetachedescort = true;
	TotalRefresh();
}

void LWMissionFolder::OnClickedPlanned() 
{
	if (specialnotakeoffs)
		specialnotakeoffs=false;
	else
		if	(MMC.lwplanned)
		   MMC.lwplanned = false;
		else
		   MMC.lwplanned = true;
	TotalRefresh();
}

void LWMissionFolder::OnClickedActive() 
{
	if (specialnotakeoffs)
		specialnotakeoffs=false;
	else
		if	(MMC.lwactive)
		   MMC.lwactive = false;
		else
		   MMC.lwactive = true;
	TotalRefresh();
}

void LWMissionFolder::OnClickedEscort() 
{
	if (specialnotakeoffs)
		specialnotakeoffs=false;
	else
		if	(MMC.lwattachedescort)
		   MMC.lwattachedescort = false;
		else
		   MMC.lwattachedescort = true;
	TotalRefresh();
}

void LWMissionFolder::OnClickedLanded() 
{
	if (specialnotakeoffs)
		specialnotakeoffs=false;
	else
		if	(MMC.lwlanded)
		   MMC.lwlanded = false;
		else
		   MMC.lwlanded = true;
	TotalRefresh();
}

void LWMissionFolder::OnClickedReconn() 
{
	if (specialnotakeoffs)
		specialnotakeoffs=false;
	else
		if	(MMC.lwreconn)
		   MMC.lwreconn = false;
		else
		   MMC.lwreconn = true;
	TotalRefresh();
	
}

void LWMissionFolder::OnClickedRbuttondelete() 
{

	Todays_Packages.DeletePack(Todays_Packages.hipack);
	TotalRefresh();
	Campaign::GlobalRefreshData();
	
}

void LWMissionFolder::OnClickedRbuttonfrag() 
{
#ifndef	BOB_DEMO_VER

	// TODO: Add your control notification handler code here
	MainToolBar().OnClickedFrag2();
#endif	
}
