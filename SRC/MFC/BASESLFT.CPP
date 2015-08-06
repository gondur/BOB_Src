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

// RowanDialog: // BasesLft.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "BasesLft.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// BasesLuftflotte dialog


RDialog*	BasesLuftflotte::Make()
{
//DeadCode JIM 20Oct00 	int numopts = 1;
//DeadCode JIM 20Oct00 	DialBox* ND = NULL;
	CString	tabtitle[4];

//DEADCODE RDH 06/04/00 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//DEADCODE RDH 06/04/00 	{
//DEADCODE RDH 06/04/00 		tabtitle[0] = RESSTRING(L_JAGD); 
//DEADCODE RDH 06/04/00 		tabtitle[1] = RESSTRING(ZEROSTORER); 
//DEADCODE RDH 06/04/00 		tabtitle[2] = RESSTRING(KAMPF);
//DEADCODE RDH 06/04/00 		tabtitle[3] = RESSTRING(STUKA);
//DEADCODE RDH 06/04/00 		return
//DEADCODE RDH 06/04/00 		MakeTopDialog(::Place(POSN_MIN,POSN_MIN),
//DEADCODE RDH 06/04/00 				DialList(DialBox(FIL_NULL,new BasesLuftflotte,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
//DEADCODE RDH 06/04/00 					HTabBox(FIL_NULL,IdList(tabtitle[0],tabtitle[1],tabtitle[2],tabtitle[3]),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
//DEADCODE RDH 06/04/00 						DialBox(FIL_D_GESCH,new GroupGeschwader(0)),
//DEADCODE RDH 06/04/00 						DialBox(FIL_D_GESCH,new GroupGeschwader(1)),
//DEADCODE RDH 06/04/00 						DialBox(FIL_D_GESCH,new GroupGeschwader(2)),
//DEADCODE RDH 06/04/00 						DialBox(FIL_D_GESCH,new GroupGeschwader(3))
//DEADCODE RDH 06/04/00 
//DEADCODE RDH 06/04/00 									)	)	);
//DEADCODE RDH 06/04/00 
//DEADCODE RDH 06/04/00 	}else
	{
		tabtitle[0] = RESSTRING(GROUP10); 
		tabtitle[1] = RESSTRING(GROUP11); 
		tabtitle[2] = RESSTRING(GROUP12);
		tabtitle[3] = RESSTRING(GROUP13);
		return
		MakeTopDialog(::Place(POSN_MIN,POSN_MIN),
				DialList(DialBox(FIL_NULL,new BasesLuftflotte,Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE,EDGE::ALIGN_MAX + EDGE::OCCLUDE_INSIDE)),
					HTabBox(FIL_NULL,IdList(tabtitle[0],tabtitle[1],tabtitle[2],tabtitle[3]),Edges(EDGE::ALIGN_MIN,EDGE::ALIGN_MIN,EDGE::ALIGN_MAX,EDGE::ALIGN_MAX), 
						DialBox(FIL_D_GROUPS,new GroupGeschwader(IDS_GROUP_10)),
						DialBox(FIL_D_GROUPS,new GroupGeschwader(IDS_GROUP_11)),
						DialBox(FIL_D_GROUPS,new GroupGeschwader(IDS_GROUP_12)),
						DialBox(FIL_D_GROUPS,new GroupGeschwader(IDS_GROUP_13))

									)	)	);
	}
	


}


BasesLuftflotte::BasesLuftflotte(CWnd* pParent /*=NULL*/)
	: RowanDialog(BasesLuftflotte::IDD, pParent)
{
	//{{AFX_DATA_INIT(BasesLuftflotte)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void BasesLuftflotte::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BasesLuftflotte)
		// NOTE: the ClassWizard will add DDX and DDV calls here
		DDX_Control(pDX,IDJ_TITLE,m_IDJ_TITLE);


	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BasesLuftflotte, CDialog)
	//{{AFX_MSG_MAP(BasesLuftflotte)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BasesLuftflotte message handlers

BOOL BasesLuftflotte::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	CRButton* title;
	title = GETDLGITEM(IDJ_TITLE);

	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		title->SetString(RESSTRING(LUFTWAFFERESOURCES));
	else
		title->SetString(RESSTRING(RAFRESOURCES));




	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
