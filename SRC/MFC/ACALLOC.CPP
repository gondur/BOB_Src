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

// RowanDialog: // acalloc.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "acalloc.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// AircraftAllocation dialog

 RDialog*	AircraftAllocation::Make()
{
   	FileNum artnum;

	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
  		artnum = FIL_D_LUFTWAFFE_ALLOC;
	else
		artnum = FIL_D_AIRCRAFTALLOC;



	 
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(artnum,new AircraftAllocation())
			);
}


AircraftAllocation::AircraftAllocation(CWnd* pParent /*=NULL*/)
	: RowanDialog(AircraftAllocation::IDD, pParent)
{
	//{{AFX_DATA_INIT(AircraftAllocation)
	//}}AFX_DATA_INIT
}


void AircraftAllocation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AircraftAllocation)
	DDX_Control(pDX, IDC_STATIC_AIRCRAFT0, m_IDC_STATIC_AIRCRAFT0);
	DDX_Control(pDX, IDC_STATIC_AIRCRAFT1, m_IDC_STATIC_AIRCRAFT1);
	DDX_Control(pDX, IDC_STATIC_AIRCRAFT2, m_IDC_STATIC_AIRCRAFT2);
	DDX_Control(pDX, IDC_STATIC_AIRCRAFT3, m_IDC_STATIC_AIRCRAFT3);
	DDX_Control(pDX, IDC_STATIC_AIRCRAFT4, m_IDC_STATIC_AIRCRAFT4);
	DDX_Control(pDX, IDC_STATIC_AIRCRAFT5, m_IDC_STATIC_AIRCRAFT5);
	DDX_Control(pDX, IDC_STATIC_AIRFIELD0, m_IDC_STATIC_AIRFIELD0);
	DDX_Control(pDX, IDC_STATIC_AIRFIELD1, m_IDC_STATIC_AIRFIELD1);
	DDX_Control(pDX, IDC_STATIC_AIRFIELD2, m_IDC_STATIC_AIRFIELD2);
	DDX_Control(pDX, IDC_STATIC_AIRFIELD3, m_IDC_STATIC_AIRFIELD3);
	DDX_Control(pDX, IDC_STATIC_AIRFIELD4, m_IDC_STATIC_AIRFIELD4);
	DDX_Control(pDX, IDC_STATIC_AIRFIELD5, m_IDC_STATIC_AIRFIELD5);
	DDX_Control(pDX, IDC_STATIC_ETA0, m_IDC_STATIC_ETA0);
	DDX_Control(pDX, IDC_STATIC_ETA1, m_IDC_STATIC_ETA1);
	DDX_Control(pDX, IDC_STATIC_ETA2, m_IDC_STATIC_ETA2);
	DDX_Control(pDX, IDC_STATIC_ETA3, m_IDC_STATIC_ETA3);
	DDX_Control(pDX, IDC_STATIC_ETA4, m_IDC_STATIC_ETA4);
	DDX_Control(pDX, IDC_STATIC_ETA5, m_IDC_STATIC_ETA5);
	DDX_Control(pDX, IDC_STATIC_RATE0, m_IDC_STATIC_RATE0);
	DDX_Control(pDX, IDC_STATIC_RATE1, m_IDC_STATIC_RATE1);
	DDX_Control(pDX, IDC_STATIC_RATE2, m_IDC_STATIC_RATE2);
	DDX_Control(pDX, IDC_STATIC_RATE3, m_IDC_STATIC_RATE3);
	DDX_Control(pDX, IDC_STATIC_RATE4, m_IDC_STATIC_RATE4);
	DDX_Control(pDX, IDC_STATIC_RATE5, m_IDC_STATIC_RATE5);
	DDX_Control(pDX, IDC_RSTATICCTRL1, m_IDC_RSTATICCTRL1);
	DDX_Control(pDX, IDC_COMBO_SQUAD0, m_IDC_COMBO_SQUAD0);
	DDX_Control(pDX, IDC_COMBO_SQUAD1, m_IDC_COMBO_SQUAD1);
	DDX_Control(pDX, IDC_COMBO_SQUAD2, m_IDC_COMBO_SQUAD2);
	DDX_Control(pDX, IDC_COMBO_SQUAD3, m_IDC_COMBO_SQUAD3);
	DDX_Control(pDX, IDC_COMBO_SQUAD4, m_IDC_COMBO_SQUAD4);
	DDX_Control(pDX, IDC_COMBO_SQUAD5, m_IDC_COMBO_SQUAD5);
	DDX_Control(pDX, IDC_SPIN_REQUIREMENT0, m_IDC_SPIN_REQUIREMENT0);
	DDX_Control(pDX, IDC_SPIN_REQUIREMENT1, m_IDC_SPIN_REQUIREMENT1);
	DDX_Control(pDX, IDC_SPIN_REQUIREMENT2, m_IDC_SPIN_REQUIREMENT2);
	DDX_Control(pDX, IDC_SPIN_REQUIREMENT3, m_IDC_SPIN_REQUIREMENT3);
	DDX_Control(pDX, IDC_SPIN_REQUIREMENT4, m_IDC_SPIN_REQUIREMENT4);
	DDX_Control(pDX, IDC_SPIN_REQUIREMENT5, m_IDC_SPIN_REQUIREMENT5);
	DDX_Control(pDX, IDC_STAIC_READY0, m_IDC_STAIC_READY0);
	DDX_Control(pDX, IDC_STAIC_READY1, m_IDC_STAIC_READY1);
	DDX_Control(pDX, IDC_STAIC_READY2, m_IDC_STAIC_READY2);
	DDX_Control(pDX, IDC_STAIC_READY3, m_IDC_STAIC_READY3);
	DDX_Control(pDX, IDC_STAIC_READY4, m_IDC_STAIC_READY4);
	DDX_Control(pDX, IDC_STAIC_READY5, m_IDC_STAIC_READY5);
	DDX_Control(pDX, IDC_STATICPRODUCTIONPAUSED, m_IDC_STATICPRODUCTIONPAUSED);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AircraftAllocation, CDialog)
	//{{AFX_MSG_MAP(AircraftAllocation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AircraftAllocation message handlers


void AircraftAllocation::SetSide()
{
	CRStatic*   s;
	CRCombo* combo;
	CRSpinBut* spinbut;

	int k,i;

	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		s= GETDLGITEM(IDC_RSTATICCTRL1);
		s->SetString(RESSTRING(GRUPPE));
		
		k = 0;
		if (Node_Data.production[6].recipient	!= SQ_ZERO)
			actoalloc[k++] = 6;
		if (Node_Data.production[7].recipient	!= SQ_ZERO)
			actoalloc[k++] = 7;
		if (Node_Data.production[9].recipient	!= SQ_ZERO)
			actoalloc[k++] = 9;
		if (Node_Data.production[10].recipient	!= SQ_ZERO)
			actoalloc[k++] = 10;
		if (Node_Data.production[11].recipient	!= SQ_ZERO)
			actoalloc[k++] = 11;
		actoalloc[k] = -1;

	}else
	{
		s= GETDLGITEM(IDC_RSTATICCTRL1);
		s->SetString(RESSTRING(SQUADRON));
		k = 0;
		if (Node_Data.production[0].recipient	!= SQ_ZERO)
			actoalloc[k++] = 0;
		if (Node_Data.production[2].recipient	!= SQ_ZERO)
			actoalloc[k++] = 2;
		actoalloc[k] = -1;

	}
	for (i =0;i<k;i++)
	{
		s= GETDLGITEM(IDC_STATIC_AIRCRAFT0+i);
		s->ShowWindow(true);
		s= GETDLGITEM(IDC_STATIC_AIRFIELD0+i);
		s->ShowWindow(true);
		s= GETDLGITEM(IDC_STAIC_READY0+i);
		s->ShowWindow(true);
		s= GETDLGITEM(IDC_STATIC_ETA0+i);
		s->ShowWindow(true);
		s= GETDLGITEM(IDC_STATIC_RATE0+i);
		s->ShowWindow(true);
		combo=GETDLGITEM(IDC_COMBO_SQUAD0+i);
		combo->ShowWindow(true);
		spinbut=GETDLGITEM(IDC_SPIN_REQUIREMENT0+i);
		spinbut->ShowWindow(true);
		}
	for (i =k;i<5;i++)
	{
		s= GETDLGITEM(IDC_STATIC_AIRCRAFT0+i);
		s->ShowWindow(false);
		s= GETDLGITEM(IDC_STATIC_AIRFIELD0+i);
		s->ShowWindow(false);
		s= GETDLGITEM(IDC_STAIC_READY0+i);
		s->ShowWindow(false);
		s= GETDLGITEM(IDC_STATIC_ETA0+i);
		s->ShowWindow(false);
		s= GETDLGITEM(IDC_STATIC_RATE0+i);
		s->ShowWindow(false);
		combo=GETDLGITEM(IDC_COMBO_SQUAD0+i);
		combo->ShowWindow(false);
		spinbut=GETDLGITEM(IDC_SPIN_REQUIREMENT0+i);
		spinbut->ShowWindow(false);
	}

	s= GETDLGITEM(IDC_STATICPRODUCTIONPAUSED);
	if (k!=0)
		s->ShowWindow(false);
	else
		s->ShowWindow(true);

}

void AircraftAllocation::RefreshOneLine(int i)
{
	CRStatic*   s;
 	CRSpinBut* spinbut;
	Squadron* sq = &Node_Data[Node_Data.production[actoalloc[i]].recipient];

		s= GETDLGITEM(IDC_STATIC_AIRCRAFT0+i);
		s->SetString(RESLIST(SPIT_A, actoalloc[i]));

		s= GETDLGITEM(IDC_STATIC_AIRFIELD0+i);
		sq = &Node_Data[Node_Data.production[actoalloc[i]].recipient];
		s->SetString(GetTargName(sq->homeairfield));

		s= GETDLGITEM(IDC_STAIC_READY0+i);
		CString str = CSprintf("%i", sq->acavail) + "(" + 
						CSprintf("%i", sq->acavail + sq->acquickrepairable + sq->acslowrepairable) + ")";					
		s->SetString(str);


  		spinbut=GETDLGITEM(IDC_SPIN_REQUIREMENT0+i);
		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
			spinbut->Clear()->MakeNumList(45,0,1)->SetIndex(Node_Data.production[actoalloc[i]].required);
		else
			spinbut->Clear()->MakeNumList(28,0,1)->SetIndex(Node_Data.production[actoalloc[i]].required);

		 
		s= GETDLGITEM(IDC_STATIC_ETA0+i);
		int t=Node_Data.production[actoalloc[i]].nextaceta/60;
		if (t>=22*60)
			if (t>=(22+22-7)*60)
			{
				t-=(22-7)*2*60;
				s->SetForeColor(RGB(255,0,0));
			}
			else
			{
				t-=(22-7)*60;
				s->SetForeColor(RGB(250,200,0));
			}
		s->SetString(CSprintf("%02i:%02i",t/60,t%60));

		s= GETDLGITEM(IDC_STATIC_RATE0+i);
		
		s->SetString(CSprintf("%i", Node_Data.production[actoalloc[i]].acperweek));

}
void AircraftAllocation::Refresh()
{

	int i = 0;

	while (actoalloc[i] != -1)
	{
		RefreshOneLine(i);


 		i++;
	}
}
void AircraftAllocation::FillOneSqCombo(int i)
{

	
//DEADCODE RDH 06/01/00 	BritSquadron* sq = Node_Data[Node_Data.production[actoalloc[i]].recipient];
	CRCombo* combo;
	int recipientfound = -1;

	combo=GETDLGITEM(IDC_COMBO_SQUAD0+i);
	combo->Clear();
	int j = 0;
	int recipcount=0;
	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		int wader;
//			wader = Node_Data[Node_Data.production[actoalloc[i]].recipient].wadernum; 
//			CString name = RESLIST(J, Node_Data.geschwader[wader].wadername) ;
//			name = name + CSprintf("%i/", Node_Data.geschwader[wader].wadernum);
//			name = name + sq->SubName();
//			combo->AddString(name);
		Gruppen* sq;
//DeadCode JIM 22Oct00 		sq = Node_Data[Node_Data.production[actoalloc[i]].recipient];
//DeadCode JIM 22Oct00 		if (Node_Data.production[actoalloc[i]].recipient != SQ_ZERO)
//DeadCode JIM 22Oct00 		{
//DeadCode JIM 22Oct00 			CString name = sq->ShortName() + "/";
//DeadCode JIM 22Oct00 			name = name + sq->SubName();
//DeadCode JIM 22Oct00 			combo->AddString(name);
//DeadCode JIM 22Oct00 			recipientfound = true;
//DeadCode JIM 22Oct00 		}
	   	while (Node_Data.gruppe[j].squadron != SQ_ZERO)
		{


			sq = &Node_Data.gruppe[j];
			int actype= sq->AcType();
			if (
//DeadCode JIM 22Oct00 				(Node_Data.gruppe[j].squadron != Node_Data.production[actoalloc[i]].recipient)
					(actype == actoalloc[i])
				&&	(sq->periodsuntilready != Gruppen::BUSY_IN_EUROPE)		//only include squads that are
				)
				{
//DEADCODE RDH 06/01/00 					int wader;
//DEADCODE RDH 06/01/00 					wader = Node_Data.gruppe[j].wadernum; 
//DEADCODE RDH 06/01/00 					CString name = RESLIST(J, Node_Data.geschwader[wader].wadername) ;
//DEADCODE RDH 06/01/00 					name = name + CSprintf("%i/", Node_Data.geschwader[wader].wadernum);
					CString name = sq->ShortName() + "/";
					name = name + sq->SubName();
					combo->AddString(name);
					if (Node_Data.gruppe[j].squadron == Node_Data.production[actoalloc[i]].recipient)
						recipientfound = recipcount;
					recipcount++;
				}	
			j++;
		}
	}else
	{
		Squadron* sq;
		sq = Node_Data[Node_Data.production[actoalloc[i]].recipient];
//DeadCode JIM 22Oct00 		if (Node_Data.production[actoalloc[i]].recipient != SQ_ZERO)
//DeadCode JIM 22Oct00 		{
//DeadCode JIM 22Oct00 			combo->AddString(sq->SubName());
//DeadCode JIM 22Oct00 			recipientfound = true;
//DeadCode JIM 22Oct00 
//DeadCode JIM 22Oct00 		}
		while (Node_Data.squadron[j].squadron != SQ_ZERO)
		{
			sq = Node_Data[Node_Data.squadron[j].squadron];
			int actype= sq->AcType();
			if (
//DeadCode JIM 22Oct00 				(Node_Data.squadron[j].squadron != Node_Data.production[actoalloc[i]].recipient)
//DeadCode JIM 22Oct00 					&&
					((actype&-2) == actoalloc[i])
				)
			{
				combo->AddString(sq->SubName());
				if (Node_Data.squadron[j].squadron == Node_Data.production[actoalloc[i]].recipient)
				recipientfound = recipcount;

				recipcount++;


			}
			j++;
		}
	}
	if (recipientfound!=-1)
		combo->SetIndex(recipientfound);


}

void AircraftAllocation::FillSqCombo()
{
	int i = 0;
	while (actoalloc[i] != -1)
	{
		FillOneSqCombo(i);
 		i++;
	}


}
BOOL AircraftAllocation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRStatic*   s;
	CRCombo* combo;
 	CRSpinBut* spinbut;

	SetSide();

	Refresh();

	FillSqCombo();
 


//	BritSquadron* sq = Node_Data[Node_Data.production[0].recipient];


//DEADCODE RDH 20/12/99  		s= GETDLGITEM(IDC_STATIC_ETA0);
//DEADCODE RDH 20/12/99 		s->SetString("10/7/40");
//DEADCODE RDH 20/12/99  		s= GETDLGITEM(IDC_STATIC_ETA1);
//DEADCODE RDH 20/12/99 		s->SetString("20/7/40");


//		combo=GETDLGITEM(IDC_COMBO_SQUAD1);
//		combo->Clear();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(AircraftAllocation, CDialog)
    //{{AFX_EVENTSINK_MAP(AircraftAllocation)
	ON_EVENT_RANGE(AircraftAllocation, IDC_SPIN_REQUIREMENT0, IDC_SPIN_REQUIREMENT4,1 /* TextChanged */, OnTextChangedSpinRequirement0, VTS_I4 VTS_BSTR VTS_I2)
	ON_EVENT_RANGE(AircraftAllocation, IDC_COMBO_SQUAD0, IDC_COMBO_SQUAD4,1 /* TextChanged */, OnTextChangedComboSquad0, VTS_I4 VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//TEMPCODE RDH 11/05/00 	ON_EVENT_RANGE(AircraftAllocation, IDC_SPIN_REQUIREMENT0, IDC_SPIN_REQUIREMENT4,1 /* TextChanged */, OnTextChangedSpinRequirement0, VTS_I4 VTS_BSTR VTS_I2)
//TEMPCODE RDH 11/05/00 	ON_EVENT_RANGE(AircraftAllocation, IDC_COMBO_SQUAD0, IDC_COMBO_SQUAD4,1 /* TextChanged */, OnTextChangedComboSquad0, VTS_I4 VTS_BSTR VTS_I2)
//TEMPCODE RDH 11/05/00 	ON_EVENT(AircraftAllocation, IDC_SPIN_REQUIREMENT0, 1 /* TextChanged */, OnTextChangedSpinRequirement0, VTS_I4 VTS_BSTR VTS_I2)
//TEMPCODE RDH 11/05/00 	ON_EVENT(AircraftAllocation, IDC_COMBO_SQUAD0, 1 /* TextChanged */, OnTextChangedComboSquad0, VTS_I4 VTS_BSTR VTS_I2)


void AircraftAllocation::OnTextChangedSpinRequirement0(int id, LPCTSTR caption, short Index) 
{
	int linenum = id - IDC_SPIN_REQUIREMENT0;

	Node_Data.production[actoalloc[linenum]].required = Index;
  	RefreshOneLine(linenum);
	
}

void AircraftAllocation::OnTextChangedComboSquad0(int id, LPCTSTR Caption, short index) 
{

	int linenum = id - IDC_COMBO_SQUAD0;
	Squadron* sq;
	int recipient;
//DeadCode JIM 22Oct00 	if (index != 0)
	{
			int j = 0, count = -1;
		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		{
			while  (		(Node_Data.gruppe[j].squadron != SQ_ZERO) &&	(count != index) )
			{
				sq = Node_Data[Node_Data.gruppe[j].squadron];
				int actype= sq->AcType();
				if (	(actype == actoalloc[linenum])		)
					count ++;
				j++;

			}
			if (index == count)
				Node_Data.production[actoalloc[linenum]].recipient = Node_Data.gruppe[j-1].squadron;

		}else
		{
			while  (		(Node_Data.squadron[j].squadron != SQ_ZERO)	 &&	(count != index)   )
			{
				sq = Node_Data[Node_Data.squadron[j].squadron];
				int actype= sq->AcType();
				if (	((actype&-2) == actoalloc[linenum])		)
					count ++;
				j++;

			}
 			if (index == count)
				Node_Data.production[actoalloc[linenum]].recipient = Node_Data.squadron[j-1].squadron;

		}
	}
	FillOneSqCombo(linenum);
  	RefreshOneLine(linenum);


	
}
