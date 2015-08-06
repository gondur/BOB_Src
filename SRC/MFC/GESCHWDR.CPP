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

// RowanDialog: // Geschwdr.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "Geschwdr.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// Geschwader dialog


RDialog*	Geschwader::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new Geschwader(0))
			);
}


Geschwader::Geschwader(int geschwader,CWnd* pParent /*=NULL*/)
	: RowanDialog(Geschwader::IDD, pParent)
{
	//{{AFX_DATA_INIT(Geschwader)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		geschwadertype = geschwader;


}


void Geschwader::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Geschwader)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Geschwader, CDialog)
	//{{AFX_MSG_MAP(Geschwader)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Geschwader message handlers

BEGIN_EVENTSINK_MAP(Geschwader, CDialog)
    //{{AFX_EVENTSINK_MAP(Geschwader)
	ON_EVENT(Geschwader, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void	Geschwader::RefreshLW()
{
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(100);
	rlistbox->AddColumn(40);
	rlistbox->AddColumn(40);
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(100);
	rlistbox->AddColumn(40);
	rlistbox->AddColumn(40);
	rlistbox->AddColumn(40);
	rlistbox->AddString(RESSTRING(LUFTFLOTTE2),0);
	rlistbox->AddString("I",1);
	rlistbox->AddString("II",2);
	rlistbox->AddString("III",3);
	rlistbox->AddString(RESSTRING(LUFTFLOTTE3),4);
	rlistbox->AddString("I",5);
	rlistbox->AddString("II",6);
	rlistbox->AddString("III",7);

	FindGeschwader();

	for(int flotte = 0; flotte <2;flotte++)
		for (int name = 0; name <MAX_GESCH; name++)
		
		{
			CString string;
			if(geschwaderarray[flotte][geschwadertype][name] != -1)
			{
				int wader = geschwaderarray[flotte][geschwadertype][name];
				int wadernum = 	Node_Data.geschwader[wader].wadernum;
 //CSprintf("%i",	wadernum)
				if (Node_Data.geschwader[wader].reconn)
					string =   CSprintf("%s%i<%s>",
									RESLIST(J, Node_Data.geschwader[wader].wadername),
									wadernum,
									RESLIST(SPIT_A,Node_Data.geschwader[wader].aircrafttype));
				else
					string =   CSprintf("%s%i(%s)",
									RESLIST(J, Node_Data.geschwader[wader].wadername),
									wadernum,
									RESLIST(SPIT_A,Node_Data.geschwader[wader].aircrafttype));
				rlistbox->AddString(string,flotte*4);
		
				int i = 0, numsquad = 0;
				int sq, w;
				while (Node_Data.gruppe[i].squadron != SQ_ZERO)
				{
				  sq = Node_Data.gruppe[i].squadron;
				  w =Node_Data.gruppe[i].wadernum;

				  if (Node_Data.gruppe[i].wadernum == wader)
				  {
						string = CSprintf("%i", Node_Data.gruppe[i].acavail);
						if (Node_Data.gruppe[i].periodsuntilready == Gruppen::BUSY_IN_EUROPE)
							rlistbox->AddString("",flotte*4+numsquad+1);
						else if (Node_Data.gruppe[i].periodsuntilready == 0)
					  		rlistbox->AddString(string,flotte*4+numsquad+1);
						else
					  		rlistbox->AddString(CSprintf("(%s)", string),flotte*4+numsquad+1);

						numsquad++;
				  }

				  i++;
				}


			}

		}			


}


void Geschwader::FindGeschwader()
{ //stores the index into the 	germwaderinst array

	for(int flotte = 0; flotte <2;flotte++)
		for(int wader = 0; wader < 4;wader++)
			for (int name = 0; name <MAX_GESCH; name++)
				geschwaderarray[flotte][wader][name] = -1;

	int i = 0;
	int currwadername = Node_Data.geschwader[0].wadername;
	int curractype = Node_Data.geschwader[0].aircrafttype;
	int count = 0;
	while (Node_Data.geschwader[i].wadernum != 0)
	{
		if (		(currwadername != Node_Data.geschwader[i].wadername)
				&&	(curractype != Node_Data.geschwader[i].aircrafttype)
		   )
		{
			count = 0;
			currwadername = Node_Data.geschwader[i].wadername;
			curractype = Node_Data.geschwader[i].aircrafttype;
		}
		geschwaderarray[Node_Data.geschwader[i].luftflotte - LF_2]
				[Node_Data.geschwader[i].wadername][count++] = i;
		i++;
	}
	
}

BOOL Geschwader::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
		RefreshLW();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void Geschwader::OnSelectRlistboxctrl1(long row, long column) 
{
#ifndef	BOB_DEMO_VER

	int flotte;
	if (column < 4)
		flotte = 0;
	else
		flotte = 1;

	if (row > 0)
	{
		int geschwader = geschwaderarray[flotte][geschwadertype][row-1];
		if (		(column == 0)
				||	(column == 4)
			)	
		{
			MainToolBar().OpenACDossier(geschwader,0);
		}else
		{
			MainToolBar().OpenACDossier(geschwader,column -1 -(4*flotte));
		}
	}
#endif
}

