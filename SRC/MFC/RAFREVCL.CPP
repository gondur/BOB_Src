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

// RowanDialog: // RAFRevCl.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFRevCl.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFReviewClaims dialog


RDialog*	RAFReviewClaims::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new RAFReviewClaims())
			);
}


RAFReviewClaims::RAFReviewClaims(CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFReviewClaims::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFReviewClaims)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RAFReviewClaims::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFReviewClaims)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
}


BEGIN_MESSAGE_MAP(RAFReviewClaims, CDialog)
	//{{AFX_MSG_MAP(RAFReviewClaims)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFReviewClaims message handlers

BOOL RAFReviewClaims::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(120);
	//rlistbox->AddColumn(80);										  //RDH 02/06/99
	//rlistbox->AddColumn(80);
	//rlistbox->AddColumn(80);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(L_SPIT_A),1);
	rlistbox->AddString(RESSTRING(HURR_A),2);
	rlistbox->AddString(RESSTRING(TOTAL),3);

	
	rlistbox->AddString(RESSTRING(SORTIES),0);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(CLAIMS),0);
	rlistbox->AddString("   "+ RESSTRING(L_ME109),0);					//JIM 4Oct00
	rlistbox->AddString("   "+ RESSTRING(ME110),0);						//JIM 4Oct00
	rlistbox->AddString("   "+ RESSTRING(BOMBERS),0);					//JIM 4Oct00
	rlistbox->AddString("   "+ RESSTRING(TOTAL),0);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(LOSSES),0);

	rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.raf[0].sorties),1);
	rlistbox->AddString(CSprintf("%i", MMC.thisweekreview.raf[1].sorties),2);
	int totalsorties = MMC.thisweekreview.raf[0].sorties+ MMC.thisweekreview.raf[1].sorties;
	rlistbox->AddString(CSprintf("%i",totalsorties),3);


	for (int i = 0; i< 2; i++)
	{
		rlistbox->AddString("",1);
		rlistbox->AddString("",2);
		rlistbox->AddString("",3);
	}
	int totalspitkills = 0;
	int totalhurrkills = 0;

	for (i= 0; i < 3; i++)
	{
		int spitkills = MMC.thisweekreview.raf[0].totalkills[i];
		int hurrkills = MMC.thisweekreview.raf[1].totalkills[i];
		int totalkills = spitkills + hurrkills;
		rlistbox->AddString(CSprintf("%i",spitkills),1);
		rlistbox->AddString(CSprintf("%i",hurrkills),2);
		rlistbox->AddString(CSprintf("%i",totalkills),3);
		totalspitkills += spitkills;
		totalhurrkills += hurrkills;
	}
	int totaltotalkills = totalspitkills + totalhurrkills;

	rlistbox->AddString(CSprintf("%i",totalspitkills),1);
	rlistbox->AddString(CSprintf("%i",totalhurrkills),2);
	rlistbox->AddString(CSprintf("%i",totaltotalkills),3);

	rlistbox->AddString("",1);
	rlistbox->AddString("",2);
	rlistbox->AddString("",3);

	rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.raf[0].totallosses),1);
	rlistbox->AddString(CSprintf("%i", MMC.thisweekreview.raf[1].totallosses),2);
	int totaltotallosses = MMC.thisweekreview.raf[0].totallosses+ MMC.thisweekreview.raf[1].totallosses;
	rlistbox->AddString(CSprintf("%i",totaltotallosses),3);


//DeadCode RDH 22Jun00 	rlistbox->AddString("30",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("10",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("4",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("3",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("80",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("120",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",1);
//DeadCode RDH 22Jun00 	rlistbox->AddString("80",1);
//DeadCode RDH 22Jun00 
//DeadCode RDH 22Jun00 	rlistbox->AddString("30",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("10",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("4",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("3",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("80",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("120",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",2);
//DeadCode RDH 22Jun00 	rlistbox->AddString("80",2);
//DeadCode RDH 22Jun00 
//DeadCode RDH 22Jun00 
//DeadCode RDH 22Jun00 	rlistbox->AddString("30",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("10",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("4",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("3",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("80",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("120",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("",3);
//DeadCode RDH 22Jun00 	rlistbox->AddString("80",3);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
