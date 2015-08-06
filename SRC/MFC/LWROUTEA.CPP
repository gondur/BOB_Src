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

// RowanDialog: // LWRouteA.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "LWRouteA.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// LWRouteAirfield dialog


RDialog*	LWRouteAirfield::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_ROUTE,new LWRouteAirfield())
			);
}


LWRouteAirfield::LWRouteAirfield(CWnd* pParent /*=NULL*/)
	: RowanDialog(LWRouteAirfield::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWRouteAirfield)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void LWRouteAirfield::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWRouteAirfield)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWRouteAirfield, CDialog)
	//{{AFX_MSG_MAP(LWRouteAirfield)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWRouteAirfield message handlers

BOOL LWRouteAirfield::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(80);
	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
	rlistbox->AddColumn(60);										  //RDH 02/06/99
	rlistbox->AddColumn(60);										  //RDH 02/06/99
	rlistbox->AddColumn(60);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(LOCATION),1);
	rlistbox->AddString(RESSTRING(ETA),2);
	rlistbox->AddString(RESSTRING(RELTOT),3);
	rlistbox->AddString(RESSTRING(FUEL),4);
	
	rlistbox->AddString("Strike",0);
	rlistbox->AddString("Wissen",1);
	rlistbox->AddString("14:00",2);
	rlistbox->AddString("-01:20",3);
	rlistbox->AddString("3000",4);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
