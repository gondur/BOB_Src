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

// RowanDialog: // Ready.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "migview.h"
#include "Ready.h"
#include "winmove.h"
#include "comms.h"
#include "FullPane.h"
#include "commchat.h"



#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

extern UByte listptr;

/////////////////////////////////////////////////////////////////////////////
// CReadyRoom dialog


CReadyRoom::CReadyRoom(CWnd* pParent /*=NULL*/)
	: RowanDialog(CReadyRoom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReadyRoom)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CReadyRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReadyRoom)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_RLIST_UN_PLAYER,m_IDC_RLIST_UN_PLAYER);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RLIST_INCOMING_CHAT,m_IDC_RLIST_INCOMING_CHAT);
	DDX_Control(pDX,IDC_PLAYERCHAT,m_IDC_PLAYERCHAT);
	DDX_Control(pDX,IDC_RRADIO_DETAILS,m_IDC_RRADIO_DETAILS);
	DDX_Control(pDX,IDC_GAMENAME,m_IDC_GAMENAME);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	//}}AFX_DATA_MAP
	m_IDC_RLIST_UN_PLAYER.AddString("",0);
}


BEGIN_MESSAGE_MAP(CReadyRoom, CDialog)
	//{{AFX_MSG_MAP(CReadyRoom)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReadyRoom message handlers

void CReadyRoom::RedrawRadioButtons()
{
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_DETAILS);
//DeadCode JIM 20Oct00 	CRStatic* s = GETDLGITEM(IDC_RSTATICCTRL3);
	
	if (_DPlay.sendtowho==0 || _DPlay.GameType==DPlay::DEATHMATCH)
	{
		_DPlay.sendtowho=0;
		pradio->SetCurrentSelection(0);
	}
	else
	{
		_DPlay.sendtowho=1;
		pradio->SetCurrentSelection(1);
	}

	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLIST_UN_PLAYER);
	rlistbox->SetHilightRow(-1);



}

BOOL CReadyRoom::OnInitDialog() 
{
#ifndef	BOB_DEMO_VER

	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	CString string;

	if (_DPlay.UpdateMission)
	{
		_DPlay.SendCSQuickStrucToPlayers(FALSE);
		_DPlay.UpdateMission=FALSE;
	}

// create dplay session if host

	Bool res;

	if (_DPlay.UIPlayerType==DPlay::PLAYER_HOST && !_DPlay.PlayerCreated)
	{
		if (_DPlay.Lobbied)
		{
			res=_DPlay.LobbyConnect();
		}
		else
		{
			res=_DPlay.UINewPlayer(&_DPlay.PlayerName[0],&_DPlay.SessionName[0]);
		}

		if (res)
		{
			res=_DPlay.SetUpPlayerInfo(&_DPlay.PlayerName[0]);

			if (!res)
			{
				RMessageBox(IDS_BOB,IDS_COULDNTSETUPPLAYER,NULL,IDS_OK);

				_DPlay.LeaveCommsFlag=TRUE;
			}
		}
		else
		{
			RMessageBox(IDS_BOB,IDS_NOTSESSION,NULL,IDS_OK);

// dont create ready room - leave

			_DPlay.LeaveCommsFlag=TRUE;
		}
	}

	if (_DPlay.GameType==DPlay::COMMSQUICKMISSION) // && _DPlay.Host)
	{
		_DPlay.GameIndex=CSQuick1::currquickmiss;

//DeadCode AMM 25Aug00 		if (CSQuick1::quickdef.plside)
		if (!_DPlay.Side)
			RFullPanelDial::gameside = RFullPanelDial::SIDE_LW;
		else
			RFullPanelDial::gameside = RFullPanelDial::SIDE_RAF;
	}

//DEADCODE RDH 06/12/99 	rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
//DEADCODE RDH 06/12/99 	rlistbox->Clear();
//DEADCODE RDH 06/12/99 	rlistbox->AddColumn(120);
//DEADCODE RDH 06/12/99 	rlistbox->AddColumn(30);
//DEADCODE RDH 06/12/99 

	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_DETAILS);
	CRStatic* s = GETDLGITEM(IDC_RSTATICCTRL3);

	pradio->ShowWindow(SW_SHOW);
	s->ShowWindow(SW_SHOW);
	pradio->AddButton(RESSTRING(EVERYBODY));

	if (_DPlay.GameType!=DPlay::DEATHMATCH)
		pradio->AddButton(RESSTRING(MYSIDEONLY));

	RedrawRadioButtons();

	_DPlay.FlyNowFlag=FALSE;

	if (!_DPlay.LoadRadioMessages())
	{//initialise messages
		_DPlay.InitMessages();
	}
	
	rroom_timer=SetTimer(DPlay::TIMER_READYROOM,0,NULL); // set sheet up first before starting timer

	_DPlay.SendStatusChange(DPlay::CPS_READYROOM);

	if (_DPlay.Host)
	{
		if (_DPlay.GameType==DPlay::COMMSQUICKMISSION)
		{
// when host enters ready room reset pilots to NOTFLYING because this will 
// be a new game

//DEADCODE DAW 24/11/99 			for (int p=0;p<PILOTS_PER_CAMPAIGN;p++)
//DEADCODE DAW 24/11/99 			{
//DEADCODE DAW 24/11/99 				MMC.Active_Pilots[p]=MMC.Active_Pilots_Init[p];
//DEADCODE DAW 24/11/99 			}
			_DPlay.ClearDeadPilots();
		}
		_DPlay.SendPilotsStatus(false);

// send prefs when host returns to ready room so guests get updates

		_DPlay.UISendPrefs(_DPlay.playergroupID);
	}

	Save_Data.gamedifficulty|=GD_VULNERABLE;
	Save_Data.gamedifficulty|=GD_GROUNDCOLLISIONS;			
	Save_Data.gamedifficulty|=GD_COLLISIONS;			
	Save_Data.flightdifficulty%=FD_ENGINEMANAGMENT;

	_DPlay.DisplayInfo=TRUE;
#endif
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(CReadyRoom, CDialog)
    //{{AFX_EVENTSINK_MAP(CReadyRoom)
	ON_EVENT(CReadyRoom, IDC_PLAYERCHAT, 1 /* ReturnPressed */, OnReturnPressedPlayerchat, VTS_BSTR)
	ON_EVENT(CReadyRoom, IDC_RRADIO_DETAILS, 1 /* Selected */, OnSelectedRradioDetails, VTS_I4)
	ON_EVENT(CReadyRoom, IDC_RLIST_UN_PLAYER, 1 /* Select */, OnSelectRlistUnPlayer, VTS_I4 VTS_I4)
	ON_EVENT(CReadyRoom, IDC_PLAYERCHAT, 2 /* TextChanged */, OnTextChangedPlayerchat, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CReadyRoom::OnReturnPressedPlayerchat(LPCTSTR text) 
{
//DEADCODE RDH 06/12/99 	if (text[0])
//DEADCODE RDH 06/12/99 	{
//DEADCODE RDH 06/12/99 		CRListBox* rlistbox;
//DEADCODE RDH 06/12/99 		CREdit* poo;
//DEADCODE RDH 06/12/99 
//DEADCODE RDH 06/12/99 		rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
//DEADCODE RDH 06/12/99 		if (!strcmp(text,"megashootcheaton"))
//DEADCODE RDH 06/12/99 		{
//DEADCODE RDH 06/12/99 			_DPlay.megashootcheat=true;
//DEADCODE RDH 06/12/99 		}
//DEADCODE RDH 06/12/99 		else if (!strcmp(text,"megashootcheatoff"))
//DEADCODE RDH 06/12/99 		{
//DEADCODE RDH 06/12/99 			_DPlay.megashootcheat=false;
//DEADCODE RDH 06/12/99 		}
//DEADCODE RDH 06/12/99 		else if (!strcmp(text,"invulnerablecheaton"))
//DEADCODE RDH 06/12/99 		{
//DEADCODE RDH 06/12/99 			_DPlay.megashootcheat=false;
//DEADCODE RDH 06/12/99 		}
//DEADCODE RDH 06/12/99 		else if (!strcmp(text,"invulnerablecheatoff"))
//DEADCODE RDH 06/12/99 		{
//DEADCODE RDH 06/12/99 			_DPlay.megashootcheat=false;
//DEADCODE RDH 06/12/99 		}
//DEADCODE RDH 06/12/99 		else if (!strcmp(text,"liftcheaton"))
//DEADCODE RDH 06/12/99 		{
//DEADCODE RDH 06/12/99 			_DPlay.liftcheat=true;
//DEADCODE RDH 06/12/99 		}
//DEADCODE RDH 06/12/99 		else if (!strcmp(text,"liftcheatoff"))
//DEADCODE RDH 06/12/99 		{
//DEADCODE RDH 06/12/99 			_DPlay.liftcheat=false;
//DEADCODE RDH 06/12/99 		}
//DEADCODE RDH 06/12/99 		else
//DEADCODE RDH 06/12/99 		{
//DEADCODE RDH 06/12/99 //DeadCode AMM 16Nov99 			rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
//DEADCODE RDH 06/12/99 
//DEADCODE RDH 06/12/99 	//DeadCode AMM 05Aug98 	rlistbox->AddString(&_DPlay.PlayerName[0],0);
//DEADCODE RDH 06/12/99 			rlistbox->AddString((DPlay::H2H_Player+_DPlay.mySlot)->name,0);
//DEADCODE RDH 06/12/99 			rlistbox->AddString(text,1);
//DEADCODE RDH 06/12/99 	//	_DPlay.UISendDialogue((DPlay::H2H_Player+_DPlay.mySlot),(char*)text);
//DEADCODE RDH 06/12/99 			_DPlay.UISendDialogue((char*)text);
//DEADCODE RDH 06/12/99 			_DPlay.AddChatMessageToBuffer((DPlay::H2H_Player+_DPlay.mySlot)->name,(char*)text);
//DEADCODE RDH 06/12/99 		}
//DEADCODE RDH 06/12/99 		rlistbox->SetHilightRow(-1) ;							//AMM 10Jul99
//DEADCODE RDH 06/12/99 		poo=GETDLGITEM(IDC_PLAYERCHAT);
//DEADCODE RDH 06/12/99 		poo->SetCaption("");										  //AMM 06/07/99
//DEADCODE RDH 06/12/99 
//DEADCODE RDH 06/12/99 //DeadCode AMM 07Jul99 		poo->SetWindowText("");
//DEADCODE RDH 06/12/99 	}
}

void CReadyRoom::OnTimer(UINT nIDEvent) 
{
// have this first for quick exit in case bad session creation 

	if (_DPlay.LeaveCommsFlag)
	{
		KillTimer(rroom_timer);

// get me outta here asap

		FullPanel()->OnSelectRlistbox(0,0);					
		return;

	}

	if (nIDEvent==rroom_timer && _DPlay.PlayerCreated)
	{
		if (_DPlay.DisplayInfo)
		{
			_DPlay.DisplayPlayerInfo();
			_DPlay.DisplayInfo=FALSE;
		}

		_DPlay.UIUpdateMainSheet();

		if (_DPlay.FlyNowFlag)
		{
			if (_DPlay.UINetworkSelectFly())
			{
				KillTimer(rroom_timer);

// need to launch quickmissionflight sheet

				FullPanel()->OnSelectRlistbox(1,1);
				return;
			}
			else
			{
				_DPlay.FlyNowFlag=FALSE;
				_DPlay.MainSheetCount=2;
				_DPlay.SendStatusChange(DPlay::CPS_READYROOM);
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void CReadyRoom::OnClose() 
{
	KillTimer(rroom_timer);
	CDialog::OnClose();
}

//DEADCODE AMM 11/01/00 void	DPlay::DisplayReadyDialogue(char* name, char* text)
//DEADCODE AMM 11/01/00 {
//DEADCODE AMM 11/01/00  	CRListBox* rlistbox;
//DEADCODE AMM 11/01/00 
//DEADCODE AMM 11/01/00 	rlistbox=(CRListBox*)_DPlay.listptr;
//DEADCODE AMM 11/01/00 //DeadCode AMM 11Jan00  	rlistbox=(CRListBox*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_RLIST_INCOMING_CHAT);
//DEADCODE AMM 11/01/00  	if (rlistbox)
//DEADCODE AMM 11/01/00  	{
//DEADCODE AMM 11/01/00  	 	rlistbox->AddString(name,0);
//DEADCODE AMM 11/01/00   		rlistbox->AddString(text,1);
//DEADCODE AMM 11/01/00  	}
//DEADCODE AMM 11/01/00 //DEADCODE AMM 11/01/00 	rlistbox->SetHilightRow(-1) ;								//AMM 10Jul99
//DEADCODE AMM 11/01/00 	//delete rlistbox;
//DEADCODE AMM 11/01/00 }

void	DPlay::DisplayChatDialogue(char* name, char* text)
{
	CRListBox* rlistbox;
	rlistbox=(CRListBox*)_DPlay.listptr;
  	if (rlistbox)
  	{
  	 	rlistbox->AddString(name,0);
   		rlistbox->AddString(text,1);
		rlistbox->SetHilightRow(-1) ;
  	}
}


void	DPlay::DisplayPlayerInfo()
{
	CRListBox* rlistbox;
	CString string;
	ULong n,t;

// may need to update gamename as well

	if (_DPlay.GameType==COMMSQUICKMISSION) 
	{
		_DPlay.GameIndex=CSQuick1::currquickmiss;
	}

	rlistbox=(CRListBox*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_RLIST_UN_PLAYER);
	rlistbox->Clear();
//DeadCode RDH 30Nov00 	rlistbox->AddColumn(40);
//DeadCode RDH 30Nov00 	rlistbox->AddColumn(120);
//DeadCode RDH 30Nov00 	rlistbox->AddColumn(65);
//DeadCode RDH 30Nov00 	rlistbox->AddColumn(60);
//DeadCode RDH 30Nov00 	rlistbox->AddColumn(30);
//DeadCode RDH 30Nov00 	rlistbox->AddColumn(25);
//DeadCode RDH 30Nov00 	rlistbox->AddColumn(55);
//DeadCode RDH 30Nov00 	rlistbox->AddColumn(30);

	rlistbox->AddString("",0);

	string.LoadString(IDS_NAME);
	rlistbox->AddString(string,1);

	string.LoadString(IDS_AIRCRAFT);
	rlistbox->AddString(string,2);

	string.LoadString(IDS_STATUS);
	rlistbox->AddString(string,3);

	string.LoadString(IDS_TOTAL);										//AMM 11Oct00
	rlistbox->AddString(string,4);										//AMM 11Oct00

	string.LoadString(IDS_KILLS);
	rlistbox->AddString(string,5);
//DeadCode AMM 11Oct00 	rlistbox->AddString(string,4);

	string.LoadString(IDS_DAMAGESTAT_REPAIR);
	rlistbox->AddString(string,6);										//AMM 11Oct00

	string.LoadString(IDS_LOSSES);
	rlistbox->AddString(string,7);										//AMM 11Oct00
//DeadCode AMM 11Oct00 	rlistbox->AddString(string,5);

	t=1;
	char num[8],num2[8];
	char score[128];

	for (n=0;n<MAXPLAYERS;n++)
	{
		if ((H2H_Player+n)->MyTeam==TS_BLUE || (H2H_Player+n)->MyTeam==TS_NONE)
		{
			if (_DPlay.GameType==DEATHMATCH)
			{
				_itoa(t++,score,10);
			}
			else
			{
//DEADCODE RDH 25/11/99 				_itoa(t++,num,10);
//DEADCODE RDH 25/11/99 				strcpy(score,"UN ");
//DEADCODE RDH 25/11/99 				strcat(score,num);
				_itoa(t++,num,10);

				strcpy(score,"RAF ");
				strcat(score,num);	
			}
			rlistbox->AddString(score,0);

//DEADCODE AMM 10/01/00 			if (H2H_Player[n].Controller && _DPlay.GameType>TEAMPLAY)
//DEADCODE AMM 10/01/00 			{
//DEADCODE AMM 10/01/00 				strcpy(score,H2H_Player[n].name);
//DEADCODE AMM 10/01/00 				strcat(score," (C)");
//DEADCODE AMM 10/01/00 				rlistbox->AddString(score,1);
//DEADCODE AMM 10/01/00 			}
//DEADCODE AMM 10/01/00 			else
			{
				rlistbox->AddString(H2H_Player[n].name,1);
			}
			if (H2H_Player[n].squadron!=-1)
			{
				rlistbox->AddString(RESLIST(SPIT_A, H2H_Player[n].squadron), 2);
			}
			else 
			{
				rlistbox->AddString(LoadResString(IDS_NONE_WORD), 2);
			}
			rlistbox->AddString(RESLIST(CPS_STATUS,H2H_Player[n].status),3);

//create score
			
			int total=(((H2H_Player+n)->kills)*3)+((H2H_Player+n)->assists)-((H2H_Player+n)->deaths);

			if (_DPlay.GameType!=TEAMPLAY)
			{
				_itoa(total,num,10);
				rlistbox->AddString(num,4);

				_itoa((H2H_Player+n)->kills,num,10);
				rlistbox->AddString(num,5);
				
				_itoa((H2H_Player+n)->assists,num,10);
				rlistbox->AddString(num,6);

				_itoa((H2H_Player+n)->deaths,num,10);
				rlistbox->AddString(num,7);
			}
			else
			{
// need form 1/3 etc to indicate kills/team kills etc

				_itoa(total,num,10);
				rlistbox->AddString(num,4);
				
				_itoa((H2H_Player+n)->kills,num,10);
				if ((H2H_Player+n)->MyTeam==(H2H_Player+mySlot)->MyTeam)
				{
					_itoa(MyTeamKills,num2,10);
				}
				else
				{
					_itoa(EnemyTeamKills,num2,10);
				}
				strcpy(score,num);
				strcat(score,"/");
				strcat(score,num2);
				rlistbox->AddString(score,5);

				_itoa((H2H_Player+n)->assists,num,10);
				rlistbox->AddString(num,6);

				_itoa((H2H_Player+n)->deaths,num,10);
				if ((H2H_Player+n)->MyTeam==(H2H_Player+mySlot)->MyTeam)
				{
					_itoa(MyTeamDeaths,num2,10);
				}
				else
				{
					_itoa(EnemyTeamDeaths,num2,10);
				}
				strcpy(score,num);
				strcat(score,"/");
				strcat(score,num2);
				rlistbox->AddString(score,7);
			}

		}
	}

	if (_DPlay.GameType!=DEATHMATCH)
		t=1;

	for (n=0;n<MAXPLAYERS;n++)
	{
		if ((H2H_Player+n)->MyTeam==TS_RED)
		{
			if (_DPlay.GameType==DEATHMATCH)
			{
				_itoa(t++,score,10);
			}
			else
			{
				_itoa(t++,num,10);
				strcpy(score,"LW ");
				strcat(score,num);
			}
			rlistbox->AddString(score,0);

//DEADCODE AMM 10/01/00 			if (H2H_Player[n].Controller && _DPlay.GameType>TEAMPLAY)
//DEADCODE AMM 10/01/00 			{
//DEADCODE AMM 10/01/00 				strcpy(score,H2H_Player[n].name);
//DEADCODE AMM 10/01/00 				strcat(score," (C)");
//DEADCODE AMM 10/01/00 				rlistbox->AddString(score,1);
//DEADCODE AMM 10/01/00 			}
//DEADCODE AMM 10/01/00 			else
			{
				rlistbox->AddString(H2H_Player[n].name,1);
			}

			if (H2H_Player[n].squadron!=-1)
			{
				rlistbox->AddString(RESLIST(SPIT_A, H2H_Player[n].squadron), 2);
			}
			else 
			{
				rlistbox->AddString(LoadResString(IDS_NONE_WORD), 2);
			}
			rlistbox->AddString(RESLIST(CPS_STATUS,H2H_Player[n].status),3);

//create score
			
			int total=(((H2H_Player+n)->kills)*3)+((H2H_Player+n)->assists)-((H2H_Player+n)->deaths);

			if (_DPlay.GameType!=TEAMPLAY)
			{
				_itoa(total,num,10);
				rlistbox->AddString(num,4);

				_itoa((H2H_Player+n)->kills,num,10);
				rlistbox->AddString(num,5);
				
				_itoa((H2H_Player+n)->assists,num,10);
				rlistbox->AddString(num,6);

				_itoa((H2H_Player+n)->deaths,num,10);
				rlistbox->AddString(num,7);

//DeadCode AMM 11Oct00 				_itoa((H2H_Player+n)->kills,num,10);
//DeadCode AMM 11Oct00 				rlistbox->AddString(num,4);
//DeadCode AMM 11Oct00 				_itoa((H2H_Player+n)->deaths,num,10);
//DeadCode AMM 11Oct00 				rlistbox->AddString(num,5);
			}
			else
			{
// need form 1/3 etc to indicate kills/team kills etc

				_itoa(total,num,10);
				rlistbox->AddString(num,4);
				
				_itoa((H2H_Player+n)->kills,num,10);
				if ((H2H_Player+n)->MyTeam==(H2H_Player+mySlot)->MyTeam)
				{
					_itoa(MyTeamKills,num2,10);
				}
				else
				{
					_itoa(EnemyTeamKills,num2,10);
				}
				strcpy(score,num);
				strcat(score,"/");
				strcat(score,num2);
				rlistbox->AddString(score,5);

				_itoa((H2H_Player+n)->assists,num,10);
				rlistbox->AddString(num,6);

				_itoa((H2H_Player+n)->deaths,num,10);
				if ((H2H_Player+n)->MyTeam==(H2H_Player+mySlot)->MyTeam)
				{
					_itoa(MyTeamDeaths,num2,10);
				}
				else
				{
					_itoa(EnemyTeamDeaths,num2,10);
				}
				strcpy(score,num);
				strcat(score,"/");
				strcat(score,num2);
				rlistbox->AddString(score,7);			
			}
		}
	}	
	//delete rlistbox;

	CRStatic* rstatic;

	rstatic=(CRStatic*)RDialog::m_pView->m_pfullpane->pdial[0]->GetDlgItem(IDC_GAMENAME);
	//delete	rstatic;
	if (_DPlay.GameType==COMMSQUICKMISSION)
		rstatic->SetString(LoadResString(CSQuick1::quickmissions[CSQuick1::currquickmiss].missionname));
	else
		rstatic->SetString(_DPlay.GameName);

}

void CReadyRoom::OnDestroy() 
{
	KillTimer(rroom_timer);

	CDialog::OnDestroy();
}

void CReadyRoom::OnSelectedRradioDetails(long ButtonNum) 
{
	if (ButtonNum)
		_DPlay.sendtowho=1;
	else
		_DPlay.sendtowho=0;

	RedrawRadioButtons();
}


void CReadyRoom::OnSelectRlistUnPlayer(long row, long column) 
{
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_DETAILS);
	pradio->SetCurrentSelection(-1);
	_DPlay.SelectPlayerToChatTo(row-1);
	
}

void CReadyRoom::OnTextChangedPlayerchat(LPSTR text) 
{
	// TODO: Add your control notification handler code here
		trunc(text,40);
}
