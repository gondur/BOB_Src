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

//  RowanDialog: // LWRevAc.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "LWRevAc.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif


/////////////////////////////////////////////////////////////////////////////
// LWReviewAircraft dialog


RDialog*	LWReviewAircraft::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new LWReviewAircraft())
			);
}


LWReviewAircraft::LWReviewAircraft(CWnd* pParent /*=NULL*/)
	: RowanDialog(LWReviewAircraft::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWReviewAircraft)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void LWReviewAircraft::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWReviewAircraft)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
}


BEGIN_MESSAGE_MAP(LWReviewAircraft, CDialog)
	//{{AFX_MSG_MAP(LWReviewAircraft)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWReviewAircraft message handlers

BOOL LWReviewAircraft::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
		CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(120);		 //MIKE
	//rlistbox->AddColumn(42);										  //RDH 02/06/99
	//rlistbox->AddColumn(42);
	//rlistbox->AddColumn(42);
	//rlistbox->AddColumn(42);										  //RDH 02/06/99
	//rlistbox->AddColumn(42);
	//rlistbox->AddColumn(42);
	//rlistbox->AddColumn(42);										  //RDH 02/06/99
	//rlistbox->AddColumn(42);
	rlistbox->AddString("",0);
	rlistbox->AddString(RESSTRING(L_ME109),1);
	rlistbox->AddString(RESSTRING(ME110),2);
	rlistbox->AddString(RESSTRING(JU87),3);
	rlistbox->AddString(RESSTRING(L_DO17),4);
	rlistbox->AddString(RESSTRING(JU88),5);
	rlistbox->AddString(RESSTRING(HE111),6);
	rlistbox->AddString(RESSTRING(TOTAL),7);

	
	rlistbox->AddString(RESSTRING(AIRCRAFT),0);
	rlistbox->AddString("   "+ RESSTRING(BFCOMBATREADY),0);
	rlistbox->AddString("   "+ RESSTRING(DAMAGED),0);
	rlistbox->AddString("   "+ RESSTRING(REPAIRED),0);
	rlistbox->AddString("   "+ RESSTRING(DESTROYED),0);
	rlistbox->AddString("   "+ RESSTRING(NEW),0);
	rlistbox->AddString("   "+ RESSTRING(CFCOMBATREADY),0);
//DeadCode RDH 28Jun00 	rlistbox->AddString("   "+ RESSTRING(FULLCOMPLEMENT),0);
	rlistbox->AddString(RESSTRING(FACTORIES),0);
	rlistbox->AddString("   "+ RESSTRING(MAXPRODUCTION),0);
	rlistbox->AddString("   "+ RESSTRING(ACTUALPRODUCTION),0);
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
	 	rlistbox->AddString(RESSTRING(REPAIRS)+" / "+RESSTRING(HOUR),0);
		rlistbox->AddString("   "+ RESSTRING(AIRCRAFTINSYSTEM),0);
		rlistbox->AddString("   "+ RESSTRING(MAXREPAIRRATE),0);
		rlistbox->AddString("   "+ RESSTRING(ACTUALREPAIRRATE),0);
	}
	int totalavailablestart = 0;
	int totaldamaged = 0;
	int totalrepaired = 0;
	int totaldestroyed = 0;
	int totalcreated = 0;
	int totalcombatready = 0;
	int	totalmaxfact=0;
	int	totalfact=0;
	float	totalmaxrep=0;
	float	totalrep=0;
	int		totalinsys=0;

	for (int i = 0; i <6; i++)
	{
		rlistbox->AddString("",1+i);
		rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[i].availablestart),1+i);
		rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[i].damaged),1+i);
		rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[i].repaired),1+i);
		rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[i].destroyed),1+i);
		rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[i].created),1+i);
		int combatready = MMC.thisweekreview.lw[i].availablestart -
							MMC.thisweekreview.lw[i].damaged + 
							MMC.thisweekreview.lw[i].repaired - 
							MMC.thisweekreview.lw[i].destroyed +
							MMC.thisweekreview.lw[i].created;
		rlistbox->AddString(CSprintf("%i",combatready),1+i);


		rlistbox->AddString("",1+i);	//FACTORIES
		rlistbox->AddString(CSprintf("%i",Node_Data.production[PT_ME109+i].maxacperweek),1+i);
		rlistbox->AddString(CSprintf("%i",Node_Data.production[PT_ME109+i].acperweek),1+i);
 		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		{
			rlistbox->AddString("",1+i);	//REPAIRS
			rlistbox->AddString(CSprintf("%i",MMC.thisweekreview.lw[i].repairsinsystem),i+1);
			rlistbox->AddString(CSprintf("%4.1f",(MMC.thisweekreview.lw[i].potentialrepairs/4.5)),i+1);
			rlistbox->AddString(CSprintf("%4.1f",(MMC.thisweekreview.lw[i].newrepairs/4.5)),i+1);
		}
//DeadCode RDH 28Jun00 		rlistbox->AddString("",1+i);
		totalavailablestart += MMC.thisweekreview.lw[i].availablestart;
		totaldamaged += MMC.thisweekreview.lw[i].damaged;
		totalrepaired += MMC.thisweekreview.lw[i].repaired;
		totaldestroyed += MMC.thisweekreview.lw[i].destroyed;
		totalcreated += MMC.thisweekreview.lw[i].created;
		totalcombatready += combatready;
		totalmaxfact+=Node_Data.production[PT_ME109+i].maxacperweek;
		totalfact+=Node_Data.production[PT_ME109+i].acperweek;
		totalmaxrep+=MMC.thisweekreview.lw[i].potentialrepairs/4.5;
		totalrep+=MMC.thisweekreview.lw[i].newrepairs/4.5;
		totalinsys+=MMC.thisweekreview.lw[i].repairsinsystem;

	}
	rlistbox->AddString("",7);
	rlistbox->AddString(CSprintf("%i",totalavailablestart),7);
	rlistbox->AddString(CSprintf("%i",totaldamaged),7);
	rlistbox->AddString(CSprintf("%i",totalrepaired),7);
	rlistbox->AddString(CSprintf("%i",totaldestroyed),7);
	rlistbox->AddString(CSprintf("%i",totalcreated),7);
	rlistbox->AddString(CSprintf("%i",totalcombatready),7);
	rlistbox->AddString("",7);
	rlistbox->AddString(CSprintf("%i",totalmaxfact),7);
	rlistbox->AddString(CSprintf("%i",totalfact),7);
 	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		rlistbox->AddString("",7);
		rlistbox->AddString(CSprintf("%i",totalinsys),7);
		rlistbox->AddString(CSprintf("%4.1f",totalmaxrep),7);
		rlistbox->AddString(CSprintf("%4.1f",totalrep),7);
	}
//DeadCode RDH 28Jun00 	rlistbox->AddString("",7);


//DEADCODE  17/02/00 	rlistbox->AddString("",1);
//DEADCODE  17/02/00 	rlistbox->AddString("80",1);
//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("5",1);
//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("65",1);
//DEADCODE  17/02/00 	rlistbox->AddString("120",1);
//DEADCODE  17/02/00 	rlistbox->AddString("",1);
//DEADCODE  17/02/00 	rlistbox->AddString("80",1);
//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("",1);
//DEADCODE  17/02/00 	rlistbox->AddString("80",1);
//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("10",1);
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	rlistbox->AddString("",2);
//DEADCODE  17/02/00 	rlistbox->AddString("80",2);
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("5",2);
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("65",2);
//DEADCODE  17/02/00 	rlistbox->AddString("120",2);
//DEADCODE  17/02/00 	rlistbox->AddString("",2);
//DEADCODE  17/02/00 	rlistbox->AddString("80",2);
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("",2);
//DEADCODE  17/02/00 	rlistbox->AddString("80",2);
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("10",2);
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	rlistbox->AddString("",3);
//DEADCODE  17/02/00 	rlistbox->AddString("80",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("5",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("65",3);
//DEADCODE  17/02/00 	rlistbox->AddString("120",3);
//DEADCODE  17/02/00 	rlistbox->AddString("",3);
//DEADCODE  17/02/00 	rlistbox->AddString("80",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("",3);
//DEADCODE  17/02/00 	rlistbox->AddString("80",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("10",3);


	
	

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
