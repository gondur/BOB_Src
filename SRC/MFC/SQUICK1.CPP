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

// RowanDialog: // SQuick1.cpp : implementation file
//

#include "stdafx.h"
//#include "mig.h"
//#include "SQuick1.h"
#include	"mathasm.h"
#include	"bitfield.h"
#include "FullPane.h"
#include "RRadio.h"
#include "comms.h"
#include "winmove.h"   
#include "package.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSQuick1 dialog
typedef	 QuickFields	Q;
typedef	 QuickFields::QFD	QFD;
//QuickDef	CSQuick1::quickdef=
//{
//	{	{	{	{1,4,0,20000,IDS_SDETAIL4}	}	},
//		{	{	{9,2,0,20000,IDS_SDETAIL5,Q::QFD_MIG_PLAYER_ONLY},
//				{10,3,0,4000,IDS_SDETAIL6,Q::QFD_MIG_PLAYER_ONLY}	},
//			{	{9,2,0,5000,IDS_SDETAIL7,Q::QFD_MIG_PLAYER_ONLY},
//				{10,1,0,6000,IDS_SDETAIL8,Q::QFD_MIG_PLAYER_ONLY}	}	}	},
//	0,0,0,0,
//	0,0,0,0,
//	{ IDS_BRIDGE,IDS_SUPPLYPOINT,IDS_AIRFIELD,IDS_AIRFIELD	},
//	{	{UID_Null,UID_Null,UID_Null,UID_Null},
//		{UID_Null,UID_Null,UID_Null,UID_Null},
//		{UID_Null,UID_Null,UID_Null,UID_Null},
//		{UID_Null,UID_Null,UID_Null,UID_Null}	},
//	UID_Null
//};
#ifndef QFDFIELD
#define QFDFIELD
MAKEFIELD(QFD,0,Q::QFD_LAST);
#endif

QFDField	CSQuick1::nonplayer;
CSQuick1::CSQuick1(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSQuick1::IDD, pParent)
{
	wassingle=false;
	if (currquickmiss==-1)
	{
//done in SetQuickState		Miss_Man.currcampaignnum = MissMan::SCRAMBLECAMPAIGN;		//RDH 16Apr96
//		Miss_Man.camp = Miss_Man.campaigntable[MissMan::SCRAMBLECAMPAIGN];

// done elsewhere AMM 24Nov98
//		MMC.Sky.SetMissionConditions ();

		currquickmiss=0;
		currquickfamily=0;
		quickdef=quickmissions[currquickmiss];
		if (RFullPanelDial::incomms)
		{
// dont set side for deathmatch or teamplay, always want plside==0 for these

			if (!_DPlay.Side && _DPlay.GameType==DPlay::COMMSQUICKMISSION)
				quickdef.plside=1;
		}
	}
	Todays_Packages[0].packagestatus=Profile::PS_SPARE;	//flag that there are no packages!
	//{{AFX_DATA_INIT(CSQuick1)
	//}}AFX_DATA_INIT
	quickdef.parent=this;
	nonplayer=0;
	nonplayer	|=Q::QFD_BRIT_BOMBER_AUTO_ONLY;
	nonplayer	|=Q::QFD_BRIT_PLAYER_AUTO_IS_AUTO;
	nonplayer	|=Q::QFD_FIXED_AUTO;
	nonplayer	|=Q::QFD_FIXED_NUM_AUTO;
	nonplayer	|=Q::QFD_GERM_BOMBER_AUTO_ONLY;
	nonplayer	|=Q::QFD_GERM_BOMBER_PLAYER_AUTO_IS_AUTO;
}

void CSQuick1::MakeFlightCombo()
{
//DEADCODE RDH 18/01/00   CRCombo* combo;
//DEADCODE RDH 18/01/00   CRCombo* combo2;
//DEADCODE RDH 18/01/00   combo=GETDLGITEM(IDC_FLIGHTNUM);
//DEADCODE RDH 18/01/00   combo2 = GETDLGITEM(IDC_ELTNUM);
//DEADCODE RDH 18/01/00   CRStatic*   s=GETDLGITEM(IDC_RSTATICCTRL4);
//DEADCODE RDH 18/01/00 
//DEADCODE RDH 18/01/00 //DeadCode AMM 14Oct98   if (_DPlay.CurrPlayers != 0)
//DEADCODE RDH 18/01/00   if (RFullPanelDial::incomms)									//AMM 14Oct98
//DEADCODE RDH 18/01/00   {
//DEADCODE RDH 18/01/00 	combo->ShowWindow(SW_HIDE);
//DEADCODE RDH 18/01/00 	combo2->ShowWindow(SW_HIDE);
//DEADCODE RDH 18/01/00 	s->ShowWindow(SW_HIDE);
//DEADCODE RDH 18/01/00   }else
//DEADCODE RDH 18/01/00   {
//DEADCODE RDH 18/01/00   	combo->ShowWindow(SW_SHOW);
//DEADCODE RDH 18/01/00   	combo2->ShowWindow(SW_SHOW);
//DEADCODE RDH 18/01/00   	s->ShowWindow(SW_SHOW);
//DEADCODE RDH 18/01/00 
//DEADCODE RDH 18/01/00 
//DEADCODE RDH 18/01/00 	//cockup recovery. If current player position illegal find a legal one!
//DEADCODE RDH 18/01/00 	if (	nonplayer[quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].Duty()]
//DEADCODE RDH 18/01/00 		||	quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights==0
//DEADCODE RDH 18/01/00 		)
//DEADCODE RDH 18/01/00 	{	//find lowest numbered group on this side first, but then that side
//DEADCODE RDH 18/01/00 		bool gotone=false;
//DEADCODE RDH 18/01/00 		for (int pls=1-quickdef.plside,tries=2;tries--;pls=1-pls)
//DEADCODE RDH 18/01/00 			for (int w=8;w>=0;w--)
//DEADCODE RDH 18/01/00 				for (int g=2;g>=0;g--)
//DEADCODE RDH 18/01/00 					if (!gotone)
//DEADCODE RDH 18/01/00 					if (quickdef.line[pls][w][g].flights && 
//DEADCODE RDH 18/01/00 						!nonplayer[quickdef.line[pls][w][g].Duty()])
//DEADCODE RDH 18/01/00 					{	//if zero flights then not flyable, even if it 'exists'
//DEADCODE RDH 18/01/00 						quickdef.plside=pls;
//DEADCODE RDH 18/01/00 						quickdef.plwave=w;
//DEADCODE RDH 18/01/00 						quickdef.plgrp=g;
//DEADCODE RDH 18/01/00 						gotone=true;
//DEADCODE RDH 18/01/00 					}
//DEADCODE RDH 18/01/00 		if (!gotone)
//DEADCODE RDH 18/01/00 			INT3;
//DEADCODE RDH 18/01/00 	}
//DEADCODE RDH 18/01/00 	if (quickdef.plac/4>=quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights)
//DEADCODE RDH 18/01/00 	{
//DEADCODE RDH 18/01/00 		quickdef.plac%=4;
//DEADCODE RDH 18/01/00 		quickdef.plac+=4*quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights;
//DEADCODE RDH 18/01/00 		quickdef.plac-=4;
//DEADCODE RDH 18/01/00 	}
//DEADCODE RDH 18/01/00 
//DEADCODE RDH 18/01/00 	//fills IDC_FLIGHTNUM & selects it & selects IDC_ELTNUM;
//DEADCODE RDH 18/01/00 
//DEADCODE RDH 18/01/00 	combo->Clear();
//DEADCODE RDH 18/01/00 	int line=0;
//DEADCODE RDH 18/01/00 	int pls=quickdef.plside;
//DEADCODE RDH 18/01/00 	int ens=1-pls;
//DEADCODE RDH 18/01/00 	//find an enemy flyable squadron...
//DEADCODE RDH 18/01/00 	bool gotone=false;
//DEADCODE RDH 18/01/00 	int w,g;
//DEADCODE RDH 18/01/00 		for (w=7;w>=0;w--)
//DEADCODE RDH 18/01/00 			for (g=2;g>=0;g--)
//DEADCODE RDH 18/01/00 				if (!gotone)
//DEADCODE RDH 18/01/00 				if (quickdef.line[ens][w][g].flights && 
//DEADCODE RDH 18/01/00 					!nonplayer[quickdef.line[ens][w][g].Duty()])
//DEADCODE RDH 18/01/00 				{	//if zero flights then not flyable, even if it 'exists'
//DEADCODE RDH 18/01/00 					flightlines[0][0]=ens;
//DEADCODE RDH 18/01/00 					flightlines[0][1]=w;
//DEADCODE RDH 18/01/00 					flightlines[0][2]=g;
//DEADCODE RDH 18/01/00 					flightlines[0][3]=-1;
//DEADCODE RDH 18/01/00 					gotone=true;
//DEADCODE RDH 18/01/00 				}
//DEADCODE RDH 18/01/00 	if (gotone)
//DEADCODE RDH 18/01/00 	{
//DEADCODE RDH 18/01/00 	   if (ens)
//DEADCODE RDH 18/01/00 			combo->AddString(RESSTRING(RED));
//DEADCODE RDH 18/01/00 	   else
//DEADCODE RDH 18/01/00 			combo->AddString(RESSTRING(UN));
//DEADCODE RDH 18/01/00 	   line++;
//DEADCODE RDH 18/01/00 	}
//DEADCODE RDH 18/01/00 		
//DEADCODE RDH 18/01/00 	CString myside=pls?RESSTRING(RED):RESSTRING(UN);
//DEADCODE RDH 18/01/00 	for (w=0;w<8;w++)
//DEADCODE RDH 18/01/00 		for(g=0;g<3;g++)
//DEADCODE RDH 18/01/00 			if (quickdef.line[pls][w][g].flights && !nonplayer[quickdef.line[pls][w][g].Duty()])
//DEADCODE RDH 18/01/00 				if (w!=quickdef.plwave || g!=quickdef.plgrp)
//DEADCODE RDH 18/01/00 				{
//DEADCODE RDH 18/01/00 					char buffer[30];
//DEADCODE RDH 18/01/00 					combo->AddString(CSprintf("%s %s",myside,LoadResString(quickdef.line[pls][w][g].descID)));
//DEADCODE RDH 18/01/00 					flightlines[line][0]=pls;
//DEADCODE RDH 18/01/00 					flightlines[line][1]=w;
//DEADCODE RDH 18/01/00 					flightlines[line][2]=g;
//DEADCODE RDH 18/01/00 					flightlines[line][3]=-1;
//DEADCODE RDH 18/01/00 					line++;
//DEADCODE RDH 18/01/00 				}
//DEADCODE RDH 18/01/00 				else
//DEADCODE RDH 18/01/00 				{
//DEADCODE RDH 18/01/00 					int plflst=line;
//DEADCODE RDH 18/01/00 					int m=quickdef.line[pls][w][g].flights;
//DEADCODE RDH 18/01/00 					for (int f=0;f<m;f++)
//DEADCODE RDH 18/01/00 					{
//DEADCODE RDH 18/01/00 						combo->AddString(CSprintf("%s %s %s %i",myside,LoadResString(quickdef.line[pls][w][g].descID),RESSTRING(FLIGHT),f+1));
//DEADCODE RDH 18/01/00 						flightlines[line][0]=pls;
//DEADCODE RDH 18/01/00 						flightlines[line][1]=w;
//DEADCODE RDH 18/01/00 						flightlines[line][2]=g;
//DEADCODE RDH 18/01/00 						flightlines[line][3]=f;
//DEADCODE RDH 18/01/00 						line++;
//DEADCODE RDH 18/01/00 					}
//DEADCODE RDH 18/01/00 					combo->SetIndex(plflst+quickdef.plac/4);
//DEADCODE RDH 18/01/00 				}
//DEADCODE RDH 18/01/00 	combo=GETDLGITEM(IDC_ELTNUM);
//DEADCODE RDH 18/01/00 ///    bool wassingle=(combo->GetListboxLength()==1);
//DEADCODE RDH 18/01/00 	bool nowsingle=(	(quickdef.line[pls][quickdef.plwave][quickdef.plgrp].duty & QuickFields::QFD_MASK)
//DEADCODE RDH 18/01/00 							==QuickFields::QFD_BRIT_LONE
//DEADCODE RDH 18/01/00 					||	(quickdef.line[pls][quickdef.plwave][quickdef.plgrp].duty & QuickFields::QFD_MASK)
//DEADCODE RDH 18/01/00 							==QuickFields::QFD_GERM_LONE
//DEADCODE RDH 18/01/00 					);
//DEADCODE RDH 18/01/00 	if (wassingle!=nowsingle)
//DEADCODE RDH 18/01/00 		if (nowsingle)
//DEADCODE RDH 18/01/00 		{
//DEADCODE RDH 18/01/00 			quickdef.plac &=-4;
//DEADCODE RDH 18/01/00 			combo->Clear()->RESCOMBO(ELTPOS_0,1);
//DEADCODE RDH 18/01/00 			wassingle=true;
//DEADCODE RDH 18/01/00 		}
//DEADCODE RDH 18/01/00 		else
//DEADCODE RDH 18/01/00 		{
//DEADCODE RDH 18/01/00 			combo->Clear()->RESCOMBO(ELTPOS_0,4);
//DEADCODE RDH 18/01/00 			wassingle=false;
//DEADCODE RDH 18/01/00 		}
//DEADCODE RDH 18/01/00 	GETDLGITEM(IDC_ELTNUM)->SetIndex(quickdef.plac%4);
//DEADCODE RDH 18/01/00 
//DEADCODE RDH 18/01/00   }
}
void CSQuick1::DoDataExchange(CDataExchange* pDX)
{
	quickdef.parent=this;
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQuick1)
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_SDETAIL2,m_IDC_SDETAIL2);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_MISSLISTS,m_IDC_MISSLISTS);
	DDX_Control(pDX,IDC_FLIGHTNUM,m_IDC_FLIGHTNUM);
	DDX_Control(pDX,IDC_ELTNUM,m_IDC_ELTNUM);
	DDX_Control(pDX,IDC_WEATHER,m_IDC_WEATHER);
	DDX_Control(pDX,IDC_TARGTYPE,m_IDC_TARGTYPE);
	DDX_Control(pDX,IDC_TARGNAME,m_IDC_TARGNAME);
	DDX_Control(pDX,IDC_RRADIO,m_IDC_RRADIO);
	DDX_Control(pDX,IDC_DISABLEDEMO,m_IDC_DISABLEDEMO);
	DDX_Control(pDX, IDC_FAMILYLISTS, m_IDC_FAMILYLISTS);
	//}}AFX_DATA_MAP

}

BOOL CSQuick1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here

	QuickParameters::SetWeather(CSQuick1::quickdef.weather);								//RDH 9Sep00
	QuickParameters::SetTime(CSQuick1::quickdef.time);					//RDH 30Sep00

	CRRadio* pradio;
	CString string;

//	m_IDC_MISSLISTS.SetCircularStyle(TRUE);
//	m_IDC_FLIGHTNUM.SetCircularStyle(TRUE);
//	m_IDC_ELTNUM.SetCircularStyle(TRUE);
//	m_IDC_TARGTYPE.SetCircularStyle(TRUE);
//	m_IDC_TARGNAME.SetCircularStyle(TRUE);

	if (_DPlay.PlayerCreated)
	{
		FullPanel()->ResetQuitOption();
	}

	pradio=GETDLGITEM(IDC_RRADIO);
	string.LoadString(IDS_SCENARIO);
	pradio->AddButton(string);

	string.LoadString(IDS_PARAMETERS);
	pradio->AddButton(string);

	string.LoadString(IDS_UN);
	pradio->AddButton(string);
	string.LoadString(IDS_RED);
	pradio->AddButton(string);

	CRCombo* combo;
	combo=GETDLGITEM(IDC_FAMILYLISTS);
	char i = 0,j=0;
	int	currtitle = quickmissions[0].titlename;
	if (MissionsFound(i, currtitle))
	{
		combo->AddString(LoadResString(quickmissions[0].titlename));
 		missionfamily[j++] = 0;
	}
	while (quickmissions[i].missionname !=NULL)
	{
		if (quickmissions[i].titlename != currtitle)
		{
			currtitle = quickmissions[i].titlename;
 			if (MissionsFound(i, currtitle))
			{
				combo->AddString(LoadResString(quickmissions[i].titlename));
				missionfamily[j++] = i;
			}

		}
		i++;
	}
	missionfamily[j] = 255;
	combo->SetIndex(currquickfamily);


	RefreshMissionCombo();

//DEADCODE RDH 18/01/00 	combo=GETDLGITEM(IDC_ELTNUM);
//DEADCODE RDH 18/01/00 	combo->RESCOMBO(ELTPOS_0,4);
	wassingle=false;
	ReinitCombo();

//	if (RFullPanelDial::incomms)
	if (_DPlay.PlayerCreated)
	{
//DeadCode AMM 16Nov99 		_DPlay.SendInMissionBriefMessage();
//DeadCode AMM 16Nov99 		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_MISSIONBRIEF;
		_DPlay.SendStatusChange(DPlay::CPS_MISSIONBRIEF);
	}

	 missbrief_timer=SetTimer(DPlay::TIMER_MISSIONBRIEF,0,NULL); 

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}
bool	CSQuick1::MissionsFound(int i, int	currtitle)
{
	bool multifound = false;
	if (!RFullPanelDial::incomms)
		multifound=true;
	else
	{
		while (			(quickmissions[i].missionname !=NULL)
				  &&	(quickmissions[i].titlename == currtitle)
			  )
		{
			 if (MissionAllowed(i))
			 {
				multifound = true;
				break;
			 }
 			i++;
		}
	}
	return (multifound);
}
bool	CSQuick1::MissionAllowed(int i)
{
	bool	missallowed=true;
	if (RFullPanelDial::incomms)
	{


		int magic=9;

		if (i<magic)
			return false;

		for (int s=0;s<2;s++)
			for (int w=0;w<8;w++)
				for (int g=0;g<4;g++)
 						if (	(quickmissions[i].line[s][w][g].duty & QuickFields::QFD_MASK)
 									==QuickFields::QFD_BRIT_LONE
 							||	(quickmissions[i].line[s][w][g].duty & QuickFields::QFD_MASK)
 									==QuickFields::QFD_GERM_LONE
 							)
 							missallowed=false;
	}
	return (missallowed);
}



void	CSQuick1::RefreshMissionCombo()
{
	CRCombo* combo;
	combo=GETDLGITEM(IDC_MISSLISTS);
	combo->Clear();

//	combo->RESCOMBO(QUICK_1,20)->SetIndex(currquickmiss);
//DeadCode AMM 12May99 	char i = 0;
//DeadCode AMM 12May99 	while (quickmissions[i].missionname !=NULL)
//DeadCode AMM 12May99 	{
//DeadCode AMM 12May99 		combo->AddString(LoadResString(quickmissions[i].missionname));
//DeadCode AMM 12May99 		i++;
//DeadCode AMM 12May99 	}
//DeadCode AMM 12May99 	combo->SetIndex(currquickmiss);

	int i,j=0;
	i = missionfamily[currquickfamily];
	bool		currmissionfound = false;

	while (		(quickmissions[i].missionname !=NULL)
		&&	(i < missionfamily[currquickfamily+1])
	   )
	{
		if 	(currquickmiss == i)
			currmissionfound = true;
		i++;

	}
	if (!currmissionfound)
	 	currquickmiss = missionfamily[currquickfamily];


	i = missionfamily[currquickfamily];
	j=0;
	while (		(quickmissions[i].missionname !=NULL)
			&&	(i < missionfamily[currquickfamily+1])
		   )
	{
		if (MissionAllowed(i))
		{
			misslistbackindex[i]=j;
			misslistindex[j]=i;
			j++;
			combo->AddString(LoadResString(quickmissions[i].missionname));
		}
		else
			misslistbackindex[i]=255;
		i++;
	}
	if (misslistbackindex[currquickmiss]!=255)
	{
//DeadCode JIM 20Oct00  		for (int t=0; t<20;t++)
//DeadCode JIM 20Oct00 		{
//DeadCode JIM 20Oct00 			int r = misslistbackindex[t];
//DeadCode JIM 20Oct00 		}
		combo->SetIndex(misslistbackindex[currquickmiss]);
	}
	else
	{
		currquickmiss=misslistindex[0];
		quickdef=quickmissions[currquickmiss];
		combo->SetIndex(0);
	}
}




void	CSQuick1::ReinitCombo()
{
	quickdef.parent=this;
//DEADCODE RDH 18/01/00 	MakeFlightCombo();
 	CRRadio*	pradio=GETDLGITEM(IDC_RRADIO);
 	pradio->SetCurrentSelection(0);

	if (quickdef.currmissnum == FIL_NULL)
	{
		pradio->ShowWindow(SW_HIDE);

		GETDLGITEM(IDC_DISABLEDEMO)->ShowWindow(SW_SHOW);
	}
	else
	{
		pradio->ShowWindow(SW_SHOW);

		GETDLGITEM(IDC_DISABLEDEMO)->ShowWindow(SW_HIDE);
	}

//DEADCODE RDH 18/01/00 	CRCombo* combo;
//DEADCODE RDH 18/01/00 	targtype=0,targentry=0;
//DEADCODE RDH 18/01/00 	for (int t=0;t<4;t++)
//DEADCODE RDH 18/01/00 		for (int e=0;e<4;e++)
//DEADCODE RDH 18/01/00 			if(quickdef.targets[t][e]==quickdef.target)
//DEADCODE RDH 18/01/00 				targtype=t,targentry=e;
//DEADCODE RDH 18/01/00 	combo=GETDLGITEM(IDC_TARGTYPE);
//DEADCODE RDH 18/01/00 	combo->Clear();
//DEADCODE RDH 18/01/00 	combo->AddString(LoadResString(quickdef.targtypeIDs[0]));
//DEADCODE RDH 18/01/00 	if (quickdef.targtypeIDs[1])
//DEADCODE RDH 18/01/00 		combo->AddString(LoadResString(quickdef.targtypeIDs[1]));
//DEADCODE RDH 18/01/00 	if (quickdef.targtypeIDs[2])
//DEADCODE RDH 18/01/00 		combo->AddString(LoadResString(quickdef.targtypeIDs[2]));
//DEADCODE RDH 18/01/00 	if (quickdef.targtypeIDs[3])
//DEADCODE RDH 18/01/00 		combo->AddString(LoadResString(quickdef.targtypeIDs[3]));
//DEADCODE RDH 18/01/00 	if (quickdef.targtypeIDs[0])
//DEADCODE RDH 18/01/00 		combo->SetIndex(targtype);
//DEADCODE RDH 18/01/00 	combo=GETDLGITEM(IDC_TARGNAME);
//DEADCODE RDH 18/01/00 
//DEADCODE RDH 18/01/00 	//may pull this off as subroutine:
//DEADCODE RDH 18/01/00 	combo->Clear();
//DEADCODE RDH 18/01/00 	combo->AddString(GetTargName(quickdef.targets[targtype][0]));
//DEADCODE RDH 18/01/00 	if (quickdef.targets[targtype][1])
//DEADCODE RDH 18/01/00 	combo->AddString(GetTargName(quickdef.targets[targtype][1]));
//DEADCODE RDH 18/01/00 	if (quickdef.targets[targtype][2])
//DEADCODE RDH 18/01/00 		combo->AddString(GetTargName(quickdef.targets[targtype][2]));
//DEADCODE RDH 18/01/00 	if (quickdef.targets[targtype][3])
//DEADCODE RDH 18/01/00 		combo->AddString(GetTargName(quickdef.targets[targtype][3]));
//DEADCODE RDH 18/01/00 	combo->SetIndex(targentry);
//DEADCODE RDH 18/01/00 
//	combo=GETDLGITEM(IDC_WEATHER);
//	combo->Clear()->RESCOMBO(WEATHER_CLEAR,3)->SetIndex(quickdef.weather);
//	combo=GetDlgItem(IDC_CLOUD);
//	combo->Clear()->MakeNumList(35,5000,1000)->SetIndex(quickdef.cloudbaseK);
	
}


BEGIN_MESSAGE_MAP(CSQuick1, CDialog)
	//{{AFX_MSG_MAP(CSQuick1)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQuick1 message handlers

BEGIN_EVENTSINK_MAP(CSQuick1, CDialog)
    //{{AFX_EVENTSINK_MAP(CSQuick1)
	ON_EVENT(CSQuick1, IDC_MISSLISTS, 1 /* TextChanged */, OnTextChangedMisslists, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuick1, IDC_FLIGHTNUM, 1 /* TextChanged */, OnTextChangedFlightnum, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuick1, IDC_TARGTYPE, 1 /* TextChanged */, OnTextChangedTargtype, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuick1, IDC_TARGNAME, 1 /* TextChanged */, OnTextChangedTargname, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuick1, IDC_ELTNUM, 1 /* TextChanged */, OnTextChangedEltnum, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuick1, IDC_RRADIO, 1 /* Selected */, OnSelectedRradio, VTS_I4)
	ON_EVENT(CSQuick1, IDC_FAMILYLISTS, 1 /* TextChanged */, OnTextChangedFamilylists, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
//	ON_EVENT(CSQuick1, IDC_WEATHER, 1 /* TextChanged */, OnTextChangedWeather, VTS_BSTR VTS_I2)
//	ON_EVENT(CSQuick1, IDC_CLOUD, 1 /* TextChanged */, OnTextChangedCloud, VTS_BSTR VTS_I2)
END_EVENTSINK_MAP()

void CSQuick1::OnTextChangedMisslists(LPCTSTR text, short index) 
{
//DEADCODE RDH 09/03/00 	// TODO: Add your control notification handler code here
//DEADCODE RDH 09/03/00 	//actually need to shut everything down....
//DEADCODE RDH 09/03/00 //DeadCode DAW 18May99 	currquickmiss=GETDLGITEM(IDC_MISSLISTS)->GetIndex();
//DEADCODE RDH 09/03/00 	if (!RFullPanelDial::incomms)								//AMM 18May99
//DEADCODE RDH 09/03/00 		currquickmiss=misslistindex[GETDLGITEM(IDC_MISSLISTS)->GetIndex()]; //DAW 03/02/00
//DEADCODE RDH 09/03/00 	else														//AMM 18May99
//DEADCODE RDH 09/03/00 	{															//AMM 18May99
//DEADCODE RDH 09/03/00 		int i=0,j=0,index=GETDLGITEM(IDC_MISSLISTS)->GetIndex();
//DEADCODE RDH 09/03/00 
//DEADCODE RDH 09/03/00 		while (quickmissions[i].missionname !=NULL)
//DEADCODE RDH 09/03/00 		{
//DEADCODE RDH 09/03/00 			bool	missallowed;
//DEADCODE RDH 09/03/00 
//DEADCODE RDH 09/03/00 			missallowed=true;
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 			for (int s=0;s<2;s++)
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 				for (int w=0;w<8;w++)
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 					for (int g=0;g<4;g++)
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 						if (	(quickdef.line[s][w][g].duty & QuickFields::QFD_MASK) //DAW 03/02/00
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 									==QuickFields::QFD_BRIT_LONE
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 							||	(quickdef.line[s][w][g].duty & QuickFields::QFD_MASK) //DAW 03/02/00
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 									==QuickFields::QFD_GERM_LONE
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 							)
//DEADCODE RDH 09/03/00 //TEMPCODE DAW 03/02/00 							missallowed=false;
//DEADCODE RDH 09/03/00 
//DEADCODE RDH 09/03/00 			if (missallowed)
//DEADCODE RDH 09/03/00 			{
//DEADCODE RDH 09/03/00 				misslistbackindex[i]=j;
//DEADCODE RDH 09/03/00 				misslistindex[j]=i;
//DEADCODE RDH 09/03/00 				j++;
//DEADCODE RDH 09/03/00 				if (!index)
//DEADCODE RDH 09/03/00 					break;
//DEADCODE RDH 09/03/00 				index--;
//DEADCODE RDH 09/03/00 			}
//DEADCODE RDH 09/03/00 			else
//DEADCODE RDH 09/03/00 				misslistbackindex[i]=255;
//DEADCODE RDH 09/03/00 			i++;
//DEADCODE RDH 09/03/00 		}
//DEADCODE RDH 09/03/00 		currquickmiss=i;
//DEADCODE RDH 09/03/00 	}
	currquickmiss = misslistindex[index];
	quickdef=quickmissions[currquickmiss];
	if (RFullPanelDial::incomms)
	{
		if (!_DPlay.Side)
			quickdef.plside=1;
	}
//DeadCode JIM 12Jan99 	RFullPanelDial* fullscreen=(RFullPanelDial*)GetParent();
	ReinitCombo();
	FullPanel()->QuickMissionDesc();							//JIM 12Jan99
//	DestroyPanel();
//  if (_DPlay.CurrPlayers == 0)
//		fullscreen->LaunchScreen(&fullscreen->quickmission);
//	else
//		fullscreen->LaunchScreen(&fullscreen->commsquick);
//DeadCode AMM 14Oct98   if (_DPlay.CurrPlayers == 0)
//  if (!RFullPanelDial::incomms)									//AMM 14Oct98
//		fullscreen->LaunchScreen(&fullscreen->quickmission);
//	else
//		fullscreen->LaunchScreen(&fullscreen->commsquick);
}

void CSQuick1::OnTextChangedFlightnum(LPCTSTR text, short Xindex) 
{
//DEADCODE RDH 18/01/00 	int index=GETDLGITEM(IDC_FLIGHTNUM)->GetIndex();
//DEADCODE RDH 18/01/00 	//ok... this is easy, now... index into flightlines!
//DEADCODE RDH 18/01/00 	if (	flightlines[index][0]!=quickdef.plside
//DEADCODE RDH 18/01/00 		||	flightlines[index][1]!=quickdef.plwave
//DEADCODE RDH 18/01/00 		||	flightlines[index][2]!=quickdef.plgrp
//DEADCODE RDH 18/01/00 		)
//DEADCODE RDH 18/01/00 	{
//DEADCODE RDH 18/01/00 		quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].dialog->SetIconPressed(false);
//DEADCODE RDH 18/01/00 		quickdef.plside=flightlines[index][0];
//DEADCODE RDH 18/01/00 		quickdef.plwave=flightlines[index][1];
//DEADCODE RDH 18/01/00 		quickdef.plgrp=flightlines[index][2];
//DEADCODE RDH 18/01/00 		quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].dialog->SetIconPressed(true);
//DEADCODE RDH 18/01/00 		if (quickdef.plac>=quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights*4)
//DEADCODE RDH 18/01/00 			quickdef.plac=quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].flights*4
//DEADCODE RDH 18/01/00 							-4+(quickdef.plac%4);
//DEADCODE RDH 18/01/00 		MakeFlightCombo();
//DEADCODE RDH 18/01/00 	}
//DEADCODE RDH 18/01/00 	else
//DEADCODE RDH 18/01/00 	{
//DEADCODE RDH 18/01/00 		quickdef.plac=(quickdef.plac%4)+4*(flightlines[index][3]);
//DEADCODE RDH 18/01/00 	}
}

void CSQuick1::OnTextChangedTargtype(LPCTSTR text, short index) 
{
//DEADCODE RDH 18/01/00 	// TODO: Add your control notification handler code here
//DEADCODE RDH 18/01/00 	targtype=GETDLGITEM(IDC_TARGTYPE)->GetIndex();
//DEADCODE RDH 18/01/00 	targentry=0;
//DEADCODE RDH 18/01/00 	quickdef.target=quickdef.targets[targtype][targentry];
//DEADCODE RDH 18/01/00 	CRCombo* combo;
//DEADCODE RDH 18/01/00 	(combo=GETDLGITEM(IDC_TARGNAME))->Clear();
//DEADCODE RDH 18/01/00 	//may pull this off as subroutine:
//DEADCODE RDH 18/01/00 	combo->AddString(GetTargName(quickdef.targets[targtype][0]));
//DEADCODE RDH 18/01/00 	if (quickdef.targets[targtype][1])
//DEADCODE RDH 18/01/00 	combo->AddString(GetTargName(quickdef.targets[targtype][1]));
//DEADCODE RDH 18/01/00 	if (quickdef.targets[targtype][2])
//DEADCODE RDH 18/01/00 		combo->AddString(GetTargName(quickdef.targets[targtype][2]));
//DEADCODE RDH 18/01/00 	if (quickdef.targets[targtype][3])
//DEADCODE RDH 18/01/00 		combo->AddString(GetTargName(quickdef.targets[targtype][3]));
//DEADCODE RDH 18/01/00 	combo->SetIndex(targentry);
}

void CSQuick1::OnTextChangedTargname(LPCTSTR text, short index) 
{
//DEADCODE RDH 18/01/00 	targentry=GETDLGITEM(IDC_TARGNAME)->GetIndex();
//DEADCODE RDH 18/01/00 	quickdef.target=quickdef.targets[targtype][targentry];
	
}

//void CSQuick1::OnTextChangedWeather(LPCTSTR text, short index) 
//{
//	// TODO: Add your control notification handler code here
//	quickdef.weather=CRComboPtr(GetDlgItem(IDC_WEATHER))->GetIndex();
//
//}

//void CSQuick1::OnTextChangedCloud(LPCTSTR text, short index) 
//{
//	// TODO: Add your control notification handler code here
//	quickdef.cloudbaseK=CRComboPtr(GetDlgItem(IDC_CLOUD))->GetIndex();
//	
//}

int		QuickDef::SpareFlights(int squad)
{
	int rv=CSQuick1::MaxGrFlights(PlaneTypeSelect(squad));
	int w,g;
	for (int s=0;s<2;s++)
		for (w=0;w<8;w++)
			for(g=0;g<3;g++)
				if (line[s][w][g].actype==squad)
					rv-=line[s][w][g].flights;
	if (rv>3)					//but only 1 squad right now
		rv=CSQuick1::MaxFlights(PlaneTypeSelect(squad));					//MS 02/05/00
//DEADCODE MS 02/05/00 	if (squad>=PT_GER_FLYABLE && rv>3)
//DEADCODE MS 02/05/00 		rv=3;
//DEADCODE MS 02/05/00 	elseif (rv>4)
//DEADCODE MS 02/05/00 		rv=4;
		
	return rv;
}

void	QuickDef::FixOtherLines(int squad)	  //IDS_TARGET
{
	int spares=SpareFlights(squad);
	int w,g;
	for (int s=0;s<2;s++)
		for (w=0;w<8;w++)
			for(g=0;g<3;g++)
/////				if (line[s][w][g].actype==squad)
					line[s][w][g].dialog->RecalcFlightsCombo(spares);
}		

void CSQuick1::OnTextChangedEltnum(LPCTSTR text, short index) 
{

	// TODO: Add your control notification handler code here
	quickdef.plac=(quickdef.plac&-4)
					+GETDLGITEM(IDC_ELTNUM)->GetIndex();
	
}

void CSQuick1::OnClose() 
{
}

BOOL CSQuick1::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	
// if in comms need to send an update saying that mission has changed	
	return CDialog::DestroyWindow();
}

void CSQuick1::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//Calc ac type and player slot number
	//from quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp] &	 quickdef.plac
	//to MMC.	playersquadron,playeracnum;
//DeadCode JIM 20Oct00 	int plsquad=quickdef.line[quickdef.plside][quickdef.plwave][quickdef.plgrp].actype;
//DeadCode JIM 20Oct00 	int plind=quickdef.plac;
//DeadCode JIM 20Oct00 	int s = quickdef.plside;
//DEADCODE MS 16/03/00 	for (int w=0;w<quickdef.plwave;w++)
//DEADCODE MS 16/03/00 		for(int g=0;g<3;g++)
//DEADCODE MS 16/03/00 				if (quickdef.line[s][w][g].actype==plsquad)
//DEADCODE MS 16/03/00 					plind+=quickdef.line[s][w][g].flights*4;
//DEADCODE MS 16/03/00 	for(int g=0;g<quickdef.plgrp;g++)
//DEADCODE MS 16/03/00 		if (quickdef.line[s][w][g].actype==plsquad)
//DEADCODE MS 16/03/00 			plind+=quickdef.line[s][w][g].flights*4;
//DEADCODE MS 16/03/00 
//DEADCODE MS 16/03/00 //DeadCode AMM 17Nov98  	if ( _DPlay.CurrPlayers == 0)
//DEADCODE MS 16/03/00  	if ( !RFullPanelDial::incomms)								//JIM 12Jan99
//DEADCODE MS 16/03/00 	{
//DEADCODE MS 16/03/00 		MMC.playersquadron=plsquad;
//DEADCODE MS 16/03/00 		MMC.playeracnum=plind;
//DEADCODE MS 16/03/00 	}

	_DPlay.UpdateMission=TRUE;

	KillTimer(missbrief_timer);
}

void CSQuick1::OnSelectedRradio(long ButtonNum) 
{
	// TODO: Add your control notification handler code here
	switch (ButtonNum)
	{
	case 0:	FullPanel()->QuickMissionDesc();	break;
	case 1:	FullPanel()->QuickMissionParameters();	break;
	case 2:	FullPanel()->QuickMissionRed();	break;
	case 3:	FullPanel()->QuickMissionBlue();	break;
	}
}

void CSQuick1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if (nIDEvent==missbrief_timer)
	{
		if (_DPlay.PlayerCreated)
		{
			_DPlay.UIUpdateMainSheet();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CSQuick1::OnTextChangedFamilylists(LPCTSTR Caption, short index) 
{
	currquickfamily = index;
	if (		(missionfamily[currquickfamily] > currquickmiss)
			||	(missionfamily[currquickfamily+1] <= currquickmiss)		//RDH 20/03/00
		)
		currquickmiss = missionfamily[currquickfamily];

	RefreshMissionCombo();
	quickdef=quickmissions[currquickmiss];

	if (RFullPanelDial::incomms)
	{
		if (!_DPlay.Side)
			quickdef.plside=1;
	}

	ReinitCombo();
	FullPanel()->QuickMissionDesc();							//JIM 12Jan99
#ifndef	BOB_DEMO_VER

	FullPanel()->ChangeFamilyAnim();

#endif	
}
