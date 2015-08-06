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

// RowanDialog: // ToteTop.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "ToteTop.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// ToteTop dialog


RDialog*	ToteTop::Make()
{  
		return
		MakeTopDialog(::Place(POSN_MAX,POSN_MIN),
			DialBox(FIL_D_TOTEBOARD,new ToteTop())
			);

//DEADCODE RDH 09/12/99 	CString	tabtitle[6];
//DEADCODE RDH 09/12/99 	tabtitle[0] = RESSTRING(GROUP10); 
//DEADCODE RDH 09/12/99 	tabtitle[1] = RESSTRING(GROUP11); 
//DEADCODE RDH 09/12/99 	tabtitle[2] = RESSTRING(GROUP11);
//DEADCODE RDH 09/12/99 	tabtitle[3] = RESSTRING(GROUP12);
//DEADCODE RDH 09/12/99 
//DEADCODE RDH 09/12/99 	return
//DEADCODE RDH 09/12/99 			MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
//DEADCODE RDH 09/12/99 					DialList(DialBox(FIL_NULL,new ToteTop,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//DEADCODE RDH 09/12/99 						HTabBox(FIL_NULL,IdList(tabtitle[0],tabtitle[1],tabtitle[2],tabtitle[3]),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//DEADCODE RDH 09/12/99 							DialBox(FIL_D_TOTEBOARD,new ToteSector()),
//DEADCODE RDH 09/12/99 							DialBox(FIL_D_TOTEBOARD,new ToteSector()),
//DEADCODE RDH 09/12/99 							DialBox(FIL_D_TOTEBOARD,new ToteSector()),
//DEADCODE RDH 09/12/99 							DialBox(FIL_D_TOTEBOARD,new ToteSector())
//DEADCODE RDH 09/12/99 
//DEADCODE RDH 09/12/99 										)	)	);
//DEADCODE RDH 09/12/99 
}


ToteTop::ToteTop(CWnd* pParent /*=NULL*/)
	: RowanDialog(ToteTop::IDD, pParent)
{
	//{{AFX_DATA_INIT(ToteTop)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ToteTop::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ToteTop)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ToteTop, CDialog)
	//{{AFX_MSG_MAP(ToteTop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ToteTop message handlers

BOOL ToteTop::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
