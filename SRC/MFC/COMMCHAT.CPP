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

// RowanDialog: // CommChat.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "CommChat.h"
#include "winmove.h"
#include "comms.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CommsChat dialog


RDialog*	CommsChat::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new CommsChat())
			);
}


CommsChat::CommsChat(CWnd* pParent /*=NULL*/)
	: RowanDialog(CommsChat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CommsChat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CommsChat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CommsChat)
	DDX_Control(pDX, IDC_RLIST_INCOMING_CHAT, m_IDC_RLIST_INCOMING_CHAT);
	DDX_Control(pDX, IDC_PLAYERCHAT, m_IDC_PLAYERCHAT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CommsChat, CDialog)
	//{{AFX_MSG_MAP(CommsChat)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CommsChat message handlers

BEGIN_EVENTSINK_MAP(CommsChat, CDialog)
    //{{AFX_EVENTSINK_MAP(CommsChat)
	ON_EVENT(CommsChat, IDC_PLAYERCHAT, 1 /* ReturnPressed */, OnReturnPressedPlayerchat, VTS_BSTR)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

BOOL CommsChat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRListBox* rlistbox;
	
	CREdit* e=GETDLGITEM(IDC_PLAYERCHAT);
	e->SetCaption("\b\b\x20");	//set max length of 32 characters
	e->SetCaption("\b\t\v\n");	//block these characters. Space is allowed.
	e->SetCaption("");

	rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
	rlistbox->Clear();
	rlistbox->AddColumn(120);
	rlistbox->AddColumn(30);
	_DPlay.listptr=(UByteP)rlistbox;
	_DPlay.UpdateChatBox();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CommsChat::OnReturnPressedPlayerchat(LPCTSTR text) 
{
	if (text[0])
	{
		CRListBox* rlistbox;
		CREdit* poo;

		rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);
//DeadCode RDH 14Dec99 		if (!strcmp(text,"megashootcheaton"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.megashootcheat=true;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"megashootcheatoff"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.megashootcheat=false;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"invulnerablecheaton"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.megashootcheat=false;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"invulnerablecheatoff"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.megashootcheat=false;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"liftcheaton"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.liftcheat=true;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else if (!strcmp(text,"liftcheatoff"))
//DeadCode RDH 14Dec99 		{
//DeadCode RDH 14Dec99 			_DPlay.liftcheat=false;
//DeadCode RDH 14Dec99 		}
//DeadCode RDH 14Dec99 		else
		{
//DeadCode AMM 16Nov99 			rlistbox=GETDLGITEM(IDC_RLIST_INCOMING_CHAT);

	//DeadCode AMM 05Aug98 	rlistbox->AddString(&_DPlay.PlayerName[0],0);
			rlistbox->AddString((DPlay::H2H_Player+_DPlay.mySlot)->name,0);
			rlistbox->AddString(text,1);
	//	_DPlay.UISendDialogue((DPlay::H2H_Player+_DPlay.mySlot),(char*)text);
			_DPlay.UISendDialogue((char*)text);
			_DPlay.AddChatMessageToBuffer((DPlay::H2H_Player+_DPlay.mySlot)->name,(char*)text);

//DeadCode AMM 12Oct00 			if (!strcmp(text,"whateveron"))
//DeadCode AMM 12Oct00 				_DPlay.whatever=true;
//DeadCode AMM 12Oct00 			else if (!strcmp(text,"whateveroff"))
//DeadCode AMM 12Oct00 				_DPlay.whatever=false;
		}
		rlistbox->SetHilightRow(-1) ;							//AMM 10Jul99
		poo=GETDLGITEM(IDC_PLAYERCHAT);
		poo->SetCaption("");										  //AMM 06/07/99

//DeadCode AMM 07Jul99 		poo->SetWindowText("");
	}
	
}

void CommsChat::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
	_DPlay.listptr=NULL;
}
