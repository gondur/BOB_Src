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

// RowanDialog: // RAFRevEn.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFRevEn.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFReviewEnemy dialog


RDialog*	RAFReviewEnemy::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new RAFReviewEnemy())
			);
}


RAFReviewEnemy::RAFReviewEnemy(CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFReviewEnemy::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFReviewEnemy)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RAFReviewEnemy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFReviewEnemy)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
}


BEGIN_MESSAGE_MAP(RAFReviewEnemy, CDialog)
	//{{AFX_MSG_MAP(RAFReviewEnemy)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFReviewEnemy message handlers

BOOL RAFReviewEnemy::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(120);          //MIKE
	//rlistbox->AddColumn(60);										  //RDH 02/06/99
	//rlistbox->AddColumn(60);
	//rlistbox->AddColumn(60);
	//rlistbox->AddColumn(60);
	//rlistbox->AddColumn(60);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(JU87),1);
	rlistbox->AddString(RESSTRING(BOMBERS),2);
	rlistbox->AddString(RESSTRING(L_ME109),3);
	rlistbox->AddString(RESSTRING(ME110),4);
	rlistbox->AddString(RESSTRING(TOTAL),5);

	
	rlistbox->AddString(RESSTRING(SORTIES),0);

	rlistbox->AddString(RESSTRING(AIRCRAFT),0);
	rlistbox->AddString("   "+ RESSTRING(BFCOMBATREADY),0);
	rlistbox->AddString("   "+ RESSTRING(DAMAGED),0);
	rlistbox->AddString("   "+ RESSTRING(REPAIRED),0);
	rlistbox->AddString("   "+ RESSTRING(DESTROYED),0);
	rlistbox->AddString("   "+ RESSTRING(NEW),0);
	rlistbox->AddString("   "+ RESSTRING(CFCOMBATREADY),0);
	rlistbox->AddString("   "+ RESSTRING(FULLCOMPLEMENT),0);
	rlistbox->AddString(RESSTRING(FACTORIES),0);
	rlistbox->AddString("   "+ RESSTRING(MAXPRODUCTION),0);
	rlistbox->AddString("   "+ RESSTRING(ACTUALPRODUCTION),0);
 


	rlistbox->AddString("30",1);
	rlistbox->AddString("",1);
	rlistbox->AddString("10",1);
	rlistbox->AddString("4",1);
	rlistbox->AddString("3",1);
	rlistbox->AddString("10",1);
	rlistbox->AddString("4",1);
	rlistbox->AddString("3",1);
	rlistbox->AddString("3",1);
	rlistbox->AddString("",1);
	rlistbox->AddString("80",1);
	rlistbox->AddString("120",1);


	rlistbox->AddString("30",2);
	rlistbox->AddString("",2);
	rlistbox->AddString("10",2);
	rlistbox->AddString("4",2);
	rlistbox->AddString("3",2);
	rlistbox->AddString("10",2);
	rlistbox->AddString("4",2);
	rlistbox->AddString("3",2);
	rlistbox->AddString("3",2);
	rlistbox->AddString("",2);
	rlistbox->AddString("80",2);
	rlistbox->AddString("120",2);

	rlistbox->AddString("30",3);
	rlistbox->AddString("",3);
	rlistbox->AddString("10",3);
	rlistbox->AddString("4",3);
	rlistbox->AddString("3",3);
	rlistbox->AddString("10",3);
	rlistbox->AddString("4",3);
	rlistbox->AddString("3",3);
	rlistbox->AddString("3",3);
	rlistbox->AddString("",3);
	rlistbox->AddString("80",3);
	rlistbox->AddString("120",3);

	rlistbox->AddString("30",4);
	rlistbox->AddString("",4);
	rlistbox->AddString("10",4);
	rlistbox->AddString("4",4);
	rlistbox->AddString("3",4);
	rlistbox->AddString("10",4);
	rlistbox->AddString("4",4);
	rlistbox->AddString("3",4);
	rlistbox->AddString("3",4);
	rlistbox->AddString("",4);
	rlistbox->AddString("80",4);
	rlistbox->AddString("120",4);

	rlistbox->AddString("30",5);
	rlistbox->AddString("",5);
	rlistbox->AddString("10",5);
	rlistbox->AddString("4",5);
	rlistbox->AddString("3",5);
	rlistbox->AddString("10",5);
	rlistbox->AddString("4",5);
	rlistbox->AddString("3",5);
	rlistbox->AddString("3",5);
	rlistbox->AddString("",5);
	rlistbox->AddString("80",5);
	rlistbox->AddString("120",5);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
