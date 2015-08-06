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

//DEADCODE MS 01/02/00 // RowanDialog: // SReplay.cpp : implementation file
//DEADCODE MS 01/02/00 //
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 #include "stdafx.h"
//DEADCODE MS 01/02/00 #include "mig.h"
//DEADCODE MS 01/02/00 #include "SReplay.h"
//DEADCODE MS 01/02/00 #include	"replay.h"
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 #ifdef _DEBUG
//DEADCODE MS 01/02/00 //#define new DEBUG_NEW
//DEADCODE MS 01/02/00 #ifndef THIS_FILE_DEFINED
//DEADCODE MS 01/02/00 #undef THIS_FILE
//DEADCODE MS 01/02/00 static char THIS_FILE[] = __FILE__;
//DEADCODE MS 01/02/00 #endif
//DEADCODE MS 01/02/00 #endif
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 /////////////////////////////////////////////////////////////////////////////
//DEADCODE MS 01/02/00 // CSReplay message handlers
//DEADCODE MS 01/02/00 /////////////////////////////////////////////////////////////////////////////
//DEADCODE MS 01/02/00 // CReplay dialog
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 CSReplay::CSReplay(CWnd* pParent /*=NULL*/)
//DEADCODE MS 01/02/00 	: RowanDialog(CSReplay::IDD, pParent)
//DEADCODE MS 01/02/00 {
//DEADCODE MS 01/02/00 	//{{AFX_DATA_INIT(CSReplay)
//DEADCODE MS 01/02/00 		// NOTE: the ClassWizard will add member initialization here
//DEADCODE MS 01/02/00 	//}}AFX_DATA_INIT
//DEADCODE MS 01/02/00 }
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 void CSReplay::DoDataExchange(CDataExchange* pDX)
//DEADCODE MS 01/02/00 {
//DEADCODE MS 01/02/00 	CDialog::DoDataExchange(pDX);
//DEADCODE MS 01/02/00 	//{{AFX_DATA_MAP(CSReplay)
//DEADCODE MS 01/02/00 		// NOTE: the ClassWizard will add DDX and DDV calls here
//DEADCODE MS 01/02/00  	DDX_Control(pDX,IDC_LOADNAME,m_IDC_REDITCTRL1);
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 	//}}AFX_DATA_MAP
//DEADCODE MS 01/02/00 }
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 BEGIN_MESSAGE_MAP(CSReplay, CDialog)
//DEADCODE MS 01/02/00 	//{{AFX_MSG_MAP(CSReplay)
//DEADCODE MS 01/02/00 	//}}AFX_MSG_MAP
//DEADCODE MS 01/02/00 END_MESSAGE_MAP()
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 /////////////////////////////////////////////////////////////////////////////
//DEADCODE MS 01/02/00 // CSReplay message handlers
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 BOOL CSReplay::OnInitDialog() 
//DEADCODE MS 01/02/00 {
//DEADCODE MS 01/02/00 	CDialog::OnInitDialog();
//DEADCODE MS 01/02/00 	
//DEADCODE MS 01/02/00 	CREdit*	editbox;
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 //	_Replay.GetReplayFileName();
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 //	if (_Replay.RealFilename[0]==NULL)
//DEADCODE MS 01/02/00 //	{
//DEADCODE MS 01/02/00 //		strcpy(_Replay.RealFilename,_Replay.filename);
//DEADCODE MS 01/02/00 //	}
//DEADCODE MS 01/02/00 
//DEADCODE MS 01/02/00 	editbox=GETDLGITEM(IDC_REDITCTRL1);
//DEADCODE MS 01/02/00 	editbox->SetWindowText(_Replay.RealFilename);
//DEADCODE MS 01/02/00 	
//DEADCODE MS 01/02/00 	return TRUE;  // return TRUE unless you set the focus to a control
//DEADCODE MS 01/02/00 	              // EXCEPTION: OCX Property Pages should return FALSE
//DEADCODE MS 01/02/00 }
