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

// RowanDialog: // LWRevSt.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "LWRevSt.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// LWReviewStrength dialog


RDialog*	LWReviewStrength::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new LWReviewStrength())
			);
}


LWReviewStrength::LWReviewStrength(CWnd* pParent /*=NULL*/)
	: RowanDialog(LWReviewStrength::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWReviewStrength)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void LWReviewStrength::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWReviewStrength)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RSTATIC_COMMENT, m_IDC_RSTATIC_COMMENT);
	//}}AFX_DATA_MAP
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->AddString("",0);

}


BEGIN_MESSAGE_MAP(LWReviewStrength, CDialog)
	//{{AFX_MSG_MAP(LWReviewStrength)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWReviewStrength message handlers



BOOL LWReviewStrength::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(120);
	//rlistbox->AddColumn(42);										  //RDH 02/06/99
	//rlistbox->AddColumn(42);
	//rlistbox->AddColumn(42);
	//rlistbox->AddColumn(42);										  //RDH 02/06/99
	//rlistbox->AddColumn(42);
	//rlistbox->AddColumn(42);
	//rlistbox->AddColumn(42);										  //RDH 02/06/99
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(L_ME109),1);
	rlistbox->AddString(RESSTRING(ME110),2);
	rlistbox->AddString(RESSTRING(JU87),3);
	rlistbox->AddString(RESSTRING(L_DO17),4);
	rlistbox->AddString(RESSTRING(JU88),5);
	rlistbox->AddString(RESSTRING(HE111),6);
	rlistbox->AddString(RESSTRING(TOTAL),7);

	
	rlistbox->AddString(RESSTRING(GRUPPEN),0);
	rlistbox->AddString("   "+ RESSTRING(L_CATA),0);
	rlistbox->AddString("   "+ RESSTRING(CATB),0);
	rlistbox->AddString("   "+ RESSTRING(CATC),0);
	rlistbox->AddString(RESSTRING(AIRCRAFT),0);
	rlistbox->AddString("   "+ RESSTRING(COMBATREADY),0);
	rlistbox->AddString("   "+ RESSTRING(FULLCOMPLEMENT),0);

	Node_Data.FillLWStrengthInfo();

 	for (int i = 0; i <Node_Data.LWMAXTYPES; i++)
 	{
 		rlistbox->AddString("",1+i);
 
 		rlistbox->AddString(CSprintf("%i",Node_Data.LWstrengthinfo[i].catA),1+i);
 		rlistbox->AddString(CSprintf("%i",Node_Data.LWstrengthinfo[i].catB),1+i);
 		rlistbox->AddString(CSprintf("%i",Node_Data.LWstrengthinfo[i].catC),1+i);
 
 		rlistbox->AddString("",1+i);
 
 		rlistbox->AddString(CSprintf("%i",Node_Data.LWstrengthinfo[i].acready),1+i);
 		rlistbox->AddString(CSprintf("%i",Node_Data.LWstrengthinfo[i].actotal),1+i);
 	}


//DEADCODE  17/02/00 	rlistbox->AddString("",1);
//DEADCODE  17/02/00 	rlistbox->AddString("10",1);
//DEADCODE  17/02/00 	rlistbox->AddString("4",1);
//DEADCODE  17/02/00 	rlistbox->AddString("3",1);
//DEADCODE  17/02/00 	rlistbox->AddString("",1);
//DEADCODE  17/02/00 	rlistbox->AddString("80",1);
//DEADCODE  17/02/00 	rlistbox->AddString("120",1);
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	rlistbox->AddString("",2);
//DEADCODE  17/02/00 	rlistbox->AddString("10",2);
//DEADCODE  17/02/00 	rlistbox->AddString("4",2);
//DEADCODE  17/02/00 	rlistbox->AddString("3",2);
//DEADCODE  17/02/00 	rlistbox->AddString("",2);
//DEADCODE  17/02/00 	rlistbox->AddString("80",2);
//DEADCODE  17/02/00 	rlistbox->AddString("120",2);
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	rlistbox->AddString("",3);
//DEADCODE  17/02/00 	rlistbox->AddString("10",3);
//DEADCODE  17/02/00 	rlistbox->AddString("4",3);
//DEADCODE  17/02/00 	rlistbox->AddString("3",3);
//DEADCODE  17/02/00 	rlistbox->AddString("",3);
//DEADCODE  17/02/00 	rlistbox->AddString("80",3);
//DEADCODE  17/02/00 	rlistbox->AddString("120",3);


//DeadCode RDH 22Jun00 	 	CRStatic*   s;
//DeadCode RDH 22Jun00    	
//DeadCode RDH 22Jun00 	s=GETDLGITEM(IDC_RSTATIC_COMMENT);
//DeadCode RDH 22Jun00 	s->SetString("The number of Category A squadrons is very low. Any further dilution will mean that the Luftwaffe is no longer a credible fighting force");
//DeadCode RDH 22Jun00 
//DeadCode RDH 22Jun00 
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
