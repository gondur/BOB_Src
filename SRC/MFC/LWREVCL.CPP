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

// RowanDialog: // LWRevCl.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "LWRevCl.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// LWReviewClaims dialog


RDialog*	LWReviewClaims::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new LWReviewClaims())
			);
}


LWReviewClaims::LWReviewClaims(CWnd* pParent /*=NULL*/)
	: RowanDialog(LWReviewClaims::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWReviewClaims)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void LWReviewClaims::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWReviewClaims)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->AddString("",0);
}


BEGIN_MESSAGE_MAP(LWReviewClaims, CDialog)
	//{{AFX_MSG_MAP(LWReviewClaims)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWReviewClaims message handlers

BOOL LWReviewClaims::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(120);
	//rlistbox->AddColumn(60);										  //RDH 02/06/99
	//rlistbox->AddColumn(60);
	//rlistbox->AddColumn(60);
	//rlistbox->AddColumn(60);										  //RDH 02/06/99
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(BOMBERS),1);
	rlistbox->AddString(RESSTRING(L_ME109),2);
	rlistbox->AddString(RESSTRING(ME110),3);
	rlistbox->AddString(RESSTRING(TOTAL),4);

	
	rlistbox->AddString(RESSTRING(SORTIES),0);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(CLAIMS),0);
	rlistbox->AddString("   "+ RESSTRING(L_SPIT_A),0);
	rlistbox->AddString("   "+ RESSTRING(HURR_A),0);
	rlistbox->AddString("   "+ RESSTRING(TOTAL),0);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(LOSSES),0);


	int totalsorties = 0;
	int totalbmbsorties = 0;
	for (int i = 2; i< 6; i++)
	{
		totalbmbsorties += MMC.thisweekreview.lw[i].sorties;
	}

	//bombers
	rlistbox->AddString(CSprintf("%i",totalbmbsorties),1);

	//109
	rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[0].sorties),2);
	//110
	rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[1].sorties),3);

	totalsorties = totalbmbsorties +  MMC.thisweekreview.lw[0].sorties +
						MMC.thisweekreview.lw[1].sorties;

	rlistbox->AddString(CSprintf("%i",totalsorties),4);


	for (i = 0; i< 2; i++)
	{
		rlistbox->AddString("",1);
		rlistbox->AddString("",2);
		rlistbox->AddString("",3);
		rlistbox->AddString("",4);
	}
	int totalme109kills = 0;
	int totalme110kills = 0;
	int totalbmbkills = 0;
 	int bmbkills = 0;


	for (i= 0; i < 2; i++)
	{
		bmbkills = 0;
		for (int j = 2; j< 6; j++)
		{
			bmbkills += MMC.thisweekreview.lw[j].totalkills[i];
		}
		rlistbox->AddString(CSprintf("%i",bmbkills),1);
		totalbmbkills += bmbkills;

		int me109kills = MMC.thisweekreview.lw[0].totalkills[i];
		int me110kills = MMC.thisweekreview.lw[1].totalkills[i];
		int totalkills = me109kills + me110kills;
		rlistbox->AddString(CSprintf("%i",me109kills),2);
		rlistbox->AddString(CSprintf("%i",me110kills),3);
		rlistbox->AddString(CSprintf("%i",totalkills),4);
		totalme109kills += me109kills;
		totalme110kills += me110kills;
	}
	int totaltotalkills = totalme109kills + totalme110kills + totalbmbkills;

	rlistbox->AddString(CSprintf("%i",totalbmbkills),1);
	rlistbox->AddString(CSprintf("%i",totalme109kills),2);
	rlistbox->AddString(CSprintf("%i",totalme110kills),3);
	rlistbox->AddString(CSprintf("%i",totaltotalkills),4);

	rlistbox->AddString("",1);
	rlistbox->AddString("",2);
	rlistbox->AddString("",3);
	rlistbox->AddString("",4);


	int totalbmblosses = 0;
	for (int j = 2; j< 6; j++)
	{
		totalbmblosses += MMC.thisweekreview.lw[j].totallosses;
	}

	
	rlistbox->AddString(CSprintf("%i",totalbmblosses),1);
	rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[0].totallosses),2);
	rlistbox->AddString(CSprintf("%i", MMC.thisweekreview.lw[1].totallosses),3);
	int totaltotallosses = totalbmblosses + MMC.thisweekreview.lw[0].totallosses+ MMC.thisweekreview.lw[1].totallosses;
	rlistbox->AddString(CSprintf("%i",totaltotallosses),4);



	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
