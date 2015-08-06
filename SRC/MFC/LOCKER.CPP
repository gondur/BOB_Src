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

// RowanDialog: // Locker.cpp : implementation file
//


#include "stdafx.h"
#include "mig.h"
#include "Locker.h"
#include "Visitors.h"
#include "RRadio.h"
#include "winmove.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED											  //RDH 17/03/99
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CLockerRoom dialog


CLockerRoom::CLockerRoom(CWnd* pParent /*=NULL*/)
	: RowanDialog(CLockerRoom::IDD, pParent)
{
	currquickmiss = 0;
	//{{AFX_DATA_INIT(CLockerRoom)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLockerRoom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLockerRoom)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_NAME,m_IDC_NAME);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_GAME_TITLE,m_IDC_GAME_TITLE);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL24,m_IDC_RSTATICCTRL24);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RRADIO_GAMETYPE,m_IDC_RRADIO_GAMETYPE);
	DDX_Control(pDX,IDC_RRADIO_SELECTSIDE,m_IDC_RRADIO_SELECTSIDE);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_PLAYERCHAT,m_IDC_PLAYERCHAT);
	DDX_Control(pDX,IDC_RSTATICCTRL26,m_IDC_RSTATICCTRL26);
	DDX_Control(pDX,IDC_GRPDESC,m_IDC_GRPDESC);
	DDX_Control(pDX,IDC_PILOTEDFLAG,m_IDC_PILOTEDFLAG);
	DDX_Control(pDX,IDC_GAME_TITLECOMBO,m_IDC_GAME_TITLECOMBO);
	DDX_Control(pDX,IDC_DATARATE,m_IDC_DATARATE);
	DDX_Control(pDX,IDC_SCENARIO,m_IDC_SCENARIO);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLockerRoom, CDialog)
	//{{AFX_MSG_MAP(CLockerRoom)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLockerRoom message handlers

BEGIN_EVENTSINK_MAP(CLockerRoom, CDialog)
    //{{AFX_EVENTSINK_MAP(CLockerRoom)
//DEADCODE DAW 23/11/99 	ON_EVENT(CLockerRoom, IDC_VISITORS, 1 /* Clicked */, OnClickedVisitors, VTS_NONE)
	ON_EVENT(CLockerRoom, IDC_RRADIO_GAMETYPE, 1 /* Selected */, OnSelectedRradioGametype, VTS_I4)
	ON_EVENT(CLockerRoom, IDC_PILOTEDFLAG, 1 /* Clicked */, OnClickedPilotedflag, VTS_NONE)
	ON_EVENT(CLockerRoom, IDC_NAME, 2 /* TextChanged */, OnTextChangedName, VTS_I4)
	ON_EVENT(CLockerRoom, IDC_GAME_TITLE, 2 /* TextChanged */, OnTextChangedGameTitle, VTS_I4)
	ON_EVENT(CLockerRoom, IDC_PLAYERCHAT, 2 /* TextChanged */, OnTextChangedPlayerchat, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CLockerRoom::OnClickedVisitors() 
{
	RDialog::MakeTopDialog(CRect(50,50,0,0),
								DialBox(FIL_VISITORS,new CVisitorsBook)//,Edges(EDGE::ALIGN_MIN + EDGE::ACTIONS_SPLITTER,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE))
							);		
}

void CLockerRoom::RedrawSide()
{
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIO_SELECTSIDE);

	if (_DPlay.GameType == DPlay::DEATHMATCH)
//DeadCode AMM 21Feb100 		||	(		(_DPlay.GameType == DPlay::COMMSCAMPAIGN)
//DeadCode AMM 21Feb100 //DEADCODE AMM 10/06/99 				&&	(_DPlay.UIPlayerType == PLAYER_HOST)
//DeadCode AMM 21Feb100 			)
//DeadCode AMM 21Feb100 		)
		pradio->ShowWindow(SW_HIDE);
	else
		pradio->ShowWindow(SW_SHOW);

}
void CLockerRoom::RedrawCombo()
{
	CRStatic* s=GETDLGITEM(IDC_SCENARIO);
	CRCombo* combo;
	combo=GETDLGITEM(IDC_GAME_TITLECOMBO);
	if (_DPlay.GameType == DPlay::COMMSQUICKMISSION)
	{
		combo->ShowWindow(SW_HIDE);
		s->ShowWindow(SW_HIDE);
	}else 
	{
		combo->ShowWindow(SW_SHOW);
		s->ShowWindow(SW_SHOW);
		combo->Clear();
		if (_DPlay.GameType == DPlay::DEATHMATCH)
		{
			combo->RESCOMBO(DEATHMATCH0,8)->SetIndex(currquickmiss);
		}else if (_DPlay.GameType == DPlay::TEAMPLAY)
		{
			combo->RESCOMBO(TEAMPLAY0,8)->SetIndex(currquickmiss);
		}else
		{
			combo->RESCOMBO(SCAMPAIGNSELECT1,5)->SetIndex(currquickmiss);
		}
	}

	if (_DPlay.UIPlayerType==DPlay::PLAYER_GUEST)
		combo->SetEnabled(false);

}

BOOL CLockerRoom::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRRadio* pradio;
	CString string;
	CREdit*	editbox;

	if (_DPlay.UIPlayerType==DPlay::PLAYER_HOST)
	{
		_DPlay.GameType=DPlay::DEATHMATCH;
	}

//DEADCODE RDH 25/11/99 	m_IDC_GAME_TITLECOMBO.SetCircularStyle(TRUE);

	pradio=GETDLGITEM(IDC_RRADIO_GAMETYPE);




	if (_DPlay.UIPlayerType==DPlay::PLAYER_HOST)
	{
		string.LoadString(IDS_DEATHMATCH);
		pradio->AddButton(string);
		string.LoadString(IDS_TEAMPLAY);
		pradio->AddButton(string);
		string.LoadString(IDS_QUICKMISSIONCOMM);
		pradio->AddButton(string);
//DEADCODE RDH 09/05/00  		string.LoadString(IDS_CAMPAIGNCOMMS);
//DEADCODE RDH 09/05/00  		pradio->AddButton(string);

		pradio=GETDLGITEM(IDC_RRADIO_SELECTSIDE);
		pradio->AddButton(RESSTRING(RED));
		pradio->AddButton(RESSTRING(UN));


	}
	else
	{
		switch (_DPlay.GameType)
		{
		case DPlay::DEATHMATCH:
			string.LoadString(IDS_DEATHMATCH);
			pradio->AddButton(string);
			break;

		case DPlay::TEAMPLAY:
			string.LoadString(IDS_TEAMPLAY);
			pradio->AddButton(string);
			break;

		case DPlay::COMMSQUICKMISSION:
			string.LoadString(IDS_QUICKMISSIONCOMM);
			pradio->AddButton(string);
			break;

//DeadCode AMM 21Feb100  		case DPlay::COMMSCAMPAIGN:
//DeadCode AMM 21Feb100  			string.LoadString(IDS_CAMPAIGNCOMMS);
//DeadCode AMM 21Feb100  			pradio->AddButton(string);
//DeadCode AMM 21Feb100  			break;

		default :
			_DPlay.GameType=DPlay::DEATHMATCH;
			break;
		}

		currquickmiss=_DPlay.GameIndex;

		if (_DPlay.GameType!=DPlay::DEATHMATCH)
		{
			pradio=GETDLGITEM(IDC_RRADIO_SELECTSIDE);
			pradio->AddButton(RESSTRING(RED));
			pradio->AddButton(RESSTRING(UN));
		}
	}
	CRCombo* combo;
	combo=GETDLGITEM(IDC_DATARATE);
	int index;

//RateDivider is 1 (fastest) - 3 (slowest)

	index = 3 - _DPlay.RateDivider;
	if (index < 0)
		index = 0;
	if (index > 2)
		index = 2;
	combo->RESCOMBO(LMH_LOW,3)->SetIndex(index);

	if (_DPlay.UIPlayerType==DPlay::PLAYER_GUEST)
		combo->SetEnabled(false);


	RedrawSide();
	RedrawCombo();
	FullPanel()->ResetLoadGameOption();							//JIM 12Jan99

	
	CRStatic* s=GETDLGITEM(IDC_GRPDESC);
	CRButton*  b=GETDLGITEM(IDC_PILOTEDFLAG);
	editbox=GetDlgItem(IDC_GAME_TITLE);

	if (_DPlay.UIPlayerType==DPlay::PLAYER_GUEST)
	{
		s->ShowWindow(SW_SHOW);
		b->ShowWindow(SW_SHOW);
		editbox->SetEnabled(false);
//		editbox->SetWindowText(&_DPlay.SessionName[0]);
	}else
	{
		if (_DPlay.Lobbied)
			editbox->SetEnabled(false);
		else
			editbox->SetEnabled(true);
		s->ShowWindow(SW_HIDE);
		b->ShowWindow(SW_HIDE);
	}

	if (_DPlay.UIPlayerType==DPlay::PLAYER_HOST && !_DPlay.Lobbied)
	{
//DEADCODE AMM 26/11/99 		strcpy(_DPlay.SessionName,"MiG Alley");
//DeadCode AMM 6Jul00 		strcpy(_DPlay.SessionName,"Blitz"); //AMM 26/11/99
		strcpy(_DPlay.SessionName,"BoB");								//AMM 6Jul00
	}

	if (_DPlay.SessionName[0])
	{
		editbox=GETDLGITEM(IDC_GAME_TITLE);
//DeadCode AMM 21Feb100 		editbox->SetWindowText(_DPlay.SessionName);
		editbox->SetCaption("\b\t\n\v");
		editbox->SetCaption(_DPlay.SessionName);
	}

	strcpy(_DPlay.PlayerName,Save_Data.CommsPlayerName);
	if (_DPlay.PlayerName[0])
	{
		editbox=GETDLGITEM(IDC_NAME);
//		editbox->SetFontNum(-8);
//		editbox->SetEnabled(FALSE);
//DeadCode AMM 21Feb100 		editbox->SetWindowText(_DPlay.PlayerName);
		editbox->SetCaption("\b\t\n\v");
		editbox->SetCaption(_DPlay.PlayerName);
	}
	GETDLGITEM(IDC_PLAYERCHAT)->SetCaption("\b\t\n\v");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLockerRoom::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();

}
void CLockerRoom::UpDateDPlay()
{																			   
// get info from locker room and put into dplay structures
	CRRadio* radiobox;
	int selection;


	CREdit* editbox;
	CString	buffer;

	editbox=GETDLGITEM(IDC_NAME);
	buffer = editbox->GetCaption();
	if (buffer.GetLength() <= (PLAYERNAMELEN - 1))
	{
		strcpy(_DPlay.PlayerName,buffer);
		strcpy(MMC.PlayerName,buffer);
		strcpy(Save_Data.CommsPlayerName,buffer);
	}	
	editbox=GETDLGITEM(IDC_GAME_TITLE);
	buffer = editbox->GetCaption();
	if (buffer.GetLength() <= (SESSIONNAMELEN - 1))
		strcpy(_DPlay.SessionName,buffer);

	editbox=GETDLGITEM(IDC_PLAYERCHAT);
	buffer = editbox->GetCaption();
	if (buffer.GetLength() <= (PASSWORDNAMELEN - 1))
		strcpy(_DPlay.Password,buffer);
	else
	{
		strncpy(_DPlay.Password,buffer,10);
		_DPlay.Password[10]='\0';
	}

//		strcpy(_DPlay.Password,buffer);

// put password in save game

//	if (_DPlay.UIPlayerType==PLAYER_HOST)
//		strcpy(Save_Data.CommsPassword,_DPlay.Password);
//		strcpy(MMC.CommsPassword,_DPlay.Password);
		

	CRCombo* combo;
	combo=GETDLGITEM(IDC_GAME_TITLECOMBO);
	int index = combo->GetIndex();
	if (_DPlay.GameType == DPlay::DEATHMATCH)
	{
		strncpy(_DPlay.GameName,RESLIST(DEATHMATCH0, index),59);
		_DPlay.GameName[59]=NULL;
		CSQuick1::quickdef.MakeDeathMatchMission(index);
	}
	else if (_DPlay.GameType == DPlay::TEAMPLAY)
	{
		strncpy(_DPlay.GameName,RESLIST(TEAMPLAY0, index),59);
		_DPlay.GameName[59]=NULL;
		CSQuick1::quickdef.MakeTeamPlayMission(index);

	}
//DeadCode AMM 21Feb100  	else if (_DPlay.GameType == DPlay::COMMSCAMPAIGN)
//DeadCode AMM 21Feb100 	{
//DeadCode AMM 21Feb100 		strncpy(_DPlay.GameName,RESLIST(SCAMPAIGNSELECT1, index),59);
//DeadCode AMM 21Feb100 		_DPlay.GameName[59]=NULL;
//DeadCode AMM 21Feb100 	}
//	else
//		strcpy(_DPlay.GameName,"");

	radiobox=GETDLGITEM(IDC_RRADIO_SELECTSIDE);
	selection=radiobox->GetCurrentSelection();

	switch (selection)
	{
	case 0:
		_DPlay.Side=TRUE;
		break;

	case 1:
		_DPlay.Side=FALSE;
		break;

	default:   
		_DPlay.Side=TRUE;
		break;

	}

	_DPlay.SideSelected=true;

	if (_DPlay.GameType==DPlay::DEATHMATCH)
		_DPlay.Side=TRUE;

	_DPlay.GameIndex=index;

	combo=GETDLGITEM(IDC_DATARATE);
	index = combo->GetIndex();

	_DPlay.RateDivider=3-index;

	if (_DPlay.RateDivider<1)
		_DPlay.RateDivider=1;
	else if (_DPlay.RateDivider>3)
		_DPlay.RateDivider=3;
}

void CLockerRoom::OnDestroy() 
{
	UpDateDPlay();






//	strcpy(&_DPlay.GameName[0],"deathmatch arena");
	CDialog::OnDestroy();

}

void CLockerRoom::OnSelectedRradioGametype(long ButtonNum) 
{
	if (_DPlay.UIPlayerType==DPlay::PLAYER_HOST)
	{
		_DPlay.GameType = (DPlay::GameTypes)ButtonNum;	
		RedrawSide();
		RedrawCombo();
		FullPanel()->ResetLoadGameOption();						//JIM 12Jan99
	}
}

void CLockerRoom::OnClickedPilotedflag() 
{
	UpDateDPlay();
		Bool res;

	if (_DPlay.UIPlayerType==DPlay::PLAYER_GUEST)
	{	 
		_DPlay.SendUpdateToVisitorsBook(&_DPlay.PlayerName[0],FALSE);
	}


	
}

void CLockerRoom::OnTextChangedName(LPTSTR text) 
{
	// TODO: Add your control notification handler code here
//	CString	buffer,buffer2;
//	CREdit* editbox;
//	editbox=GETDLGITEM(IDC_NAME);
//	buffer = editbox->GetCaption();
//	buffer2 = buffer.GetBufferSetLength(PLAYERNAMELEN-1);	
//	editbox->SetWindowText(buffer);
	trunc(text,PLAYERNAMELEN - 1);	
	
}

void CLockerRoom::OnTextChangedGameTitle(LPTSTR text) 
{
	trunc(text,SESSIONNAMELEN - 1);	
	
}

void CLockerRoom::OnTextChangedPlayerchat(LPTSTR text) 
{
	 	trunc(text,PASSWORDNAMELEN -1);
}
