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

// RowanDialog: // RAFDiyL.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include	"sqddiary.h"
#include "RAFDiary.h"
#include "RAFDryL.h"
#include "mytime.h"
#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFDiaryList dialog

RDialog*	RAFDiaryList::Make(SquadNum* squadnumptr, int* currentryptr, SquadronBase**	sqdetailsptr)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_RAFDIRECTIVES,new RAFDiaryList(squadnumptr, currentryptr, sqdetailsptr))
			);
}

RAFDiaryList::RAFDiaryList(SquadNum* squadnumptr, int* currentryptr, SquadronBase**	sqdetailsptr,CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFDiaryList::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFDiaryList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	currentptr = currentryptr;
//DeadCode JIM 20Oct00 	SquadNum* sqnumptr = squadnumptr;
	sqdtlsptr = sqdetailsptr;

}



void RAFDiaryList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFDiaryList)
	DDX_Control(pDX, IDC_RRADIODISPLAY, m_IDC_RRADIODISPLAY);
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFDiaryList, CDialog)
	//{{AFX_MSG_MAP(RAFDiaryList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFDiaryList message handlers

void RAFDiaryList::FindDetails()
{
//TEMPCODE  10/02/00 	SquadronBase*	sqentry;
//TEMPCODE  10/02/00 	Diary::Intercept* intercept;
//TEMPCODE  10/02/00 	sqentry = Squad_Diary.FindLast(sqnum);
//TEMPCODE  10/02/00 	int i = 0;
//TEMPCODE  10/02/00 
//TEMPCODE  10/02/00 	while (	(i < RAFDiary::MAX_SQDETAILS) && (sqentry))
//TEMPCODE  10/02/00 	{
//TEMPCODE  10/02/00 		parent->sqdetails[i] = sqentry;
//TEMPCODE  10/02/00 		sqentry = Squad_Diary.FindPrev(sqentry);
//TEMPCODE  10/02/00 		i++;
//TEMPCODE  10/02/00 	}
//TEMPCODE  10/02/00 	while (i < RAFDiary::MAX_SQDETAILS)
//TEMPCODE  10/02/00 	{
//TEMPCODE  10/02/00 		parent->sqdetails[i++] = NULL;
//TEMPCODE  10/02/00 	}
//TEMPCODE  10/02/00 	*currentptr = 0;

}
void RAFDiaryList::Refresh()
{

//DEADCODE  10/02/00 	FindDetails();
	
	CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
	pradio->AddButton(RESSTRING(VIEWSINGLE));
	pradio->AddButton(RESSTRING(ALL));
  	pradio->SetCurrentSelection(1);


	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(100);
	rlistbox->AddColumn(1);
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(70);
	rlistbox->AddColumn(TARGETFIELDWIDTH+50);										  //RDH 02/06/99
	rlistbox->AddColumn(60);

	
	rlistbox->AddString(RESSTRING(DATE),0);
	rlistbox->AddString("",1);
	rlistbox->AddString(RESSTRING(SIZE),2);
	rlistbox->AddString(RESSTRING(TO),3);
	rlistbox->AddString(RESSTRING(MISSION),4);
	rlistbox->AddString(RESSTRING(TARGET),5);
	rlistbox->AddString(RESSTRING(TALLY),6);


	Diary::RaidGroup* raidgroup;

	Diary::Intercept* intercept;
	Diary::Squadron*	sqentry;
	int i = 0;
 	while (	(i < RAFDiary::MAX_SQDETAILS) && (sqdtlsptr[i]))
 	{
		sqentry = (Diary::Squadron*)sqdtlsptr[i];
		intercept = Squad_Diary.GetIntercept(sqdtlsptr[i]);
		if (intercept)
		{
 			raidgroup = Squad_Diary.GetRaidGroup(intercept);
			//date
			if (raidgroup)
			{
				Diary::RaidPack* raidpack = Squad_Diary.GetRaidPack(raidgroup);
				if (raidpack)
		 			rlistbox->AddString(GetDateName(raidpack->date * SECSPERDAY, DATE_LONG),0);
			}
 
 			//TIME! NOT raid
//DeadCode JIM 15Oct00 			char* raidletter="F%03i";
//DeadCode JIM 15Oct00 			rlistbox->AddString(GetTimeName(intercept->takeofftime),1);

	//DEADCODE RDH 15/05/00  		rlistbox->AddString(CSprintf("F%i", intercept->diaryraidindex),1);
 			
 			//size
 				rlistbox->AddString(CSprintf("%i",sqentry->noaclaunched),2);

 			//to
 			int t=intercept->takeofftime/60;
 			rlistbox->AddString(CSprintf("%02i:%02i",t/60,t%60),3);
 
 			//mission
 			int cnt = int(!intercept->waspatrolinitially);				//RJS 29Aug00
 			rlistbox->AddString(RESLIST(AM_PATROL, cnt),4);
 
 			//target
 			if(!intercept->interceptloc)
 				rlistbox->AddString(RESSTRING(DASH),5);
 			//tally
 			int kills = 0;
			for (int k = 0; k < 5; k++)
				kills += sqentry->kills[k];
 			rlistbox->AddString(CSprintf("+%i -%i", kills, sqdtlsptr[i]->numlosses),6);
		} 
 
 		i++;
 	}
 
	rlistbox->SetHilightRow(*currentptr+1);


}
BOOL RAFDiaryList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Refresh();
//DEADCODE  09/02/00 	CRRadio* pradio;
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
//DEADCODE  09/02/00 	pradio->AddButton(RESSTRING(VIEWSINGLE));
//DEADCODE  09/02/00 	pradio->AddButton(RESSTRING(ALL));
//DEADCODE  09/02/00   	pradio->SetCurrentSelection(1);
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	CRListBox* rlistbox;
//DEADCODE  09/02/00 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DEADCODE  09/02/00 	rlistbox->Clear();
//DEADCODE  09/02/00 	rlistbox->AddColumn(100);
//DEADCODE  09/02/00 	rlistbox->AddColumn(60);
//DEADCODE  09/02/00 	rlistbox->AddColumn(60);
//DEADCODE  09/02/00 	rlistbox->AddColumn(60);
//DEADCODE  09/02/00 	rlistbox->AddColumn(70);
//DEADCODE  09/02/00 	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
//DEADCODE  09/02/00 	rlistbox->AddColumn(60);
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(DATE),0);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(RAID),1);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(SIZE),2);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(TO),3);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(MISSION),4);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(TARGET),5);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(TALLY),6);
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	rlistbox->AddString("10 July 1940",0);
//DEADCODE  09/02/00 	rlistbox->AddString("100",1);
//DEADCODE  09/02/00 	rlistbox->AddString("40",2);
//DEADCODE  09/02/00 	rlistbox->AddString("13:00",3);
//DEADCODE  09/02/00 	rlistbox->AddString("Strike",4);
//DEADCODE  09/02/00 	rlistbox->AddString("Biggin Hill",5);
//DEADCODE  09/02/00 	rlistbox->AddString("0/4",6);
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	rlistbox->AddString("10 July 1940",0);
//DEADCODE  09/02/00 	rlistbox->AddString("100",1);
//DEADCODE  09/02/00 	rlistbox->AddString("40",2);
//DEADCODE  09/02/00 	rlistbox->AddString("13:00",3);
//DEADCODE  09/02/00 	rlistbox->AddString("Strike",4);
//DEADCODE  09/02/00 	rlistbox->AddString("Biggin Hill",5);
//DEADCODE  09/02/00 	rlistbox->AddString("0/4",6);


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(RAFDiaryList, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFDiaryList)
	ON_EVENT(RAFDiaryList, IDC_RRADIODISPLAY, 1 /* Selected */, OnSelectedRradiodisplay, VTS_I4)
	ON_EVENT(RAFDiaryList, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RAFDiaryList::OnSelectedRradiodisplay(long ButtonNum) 
{
	parent->RefreshData(0);
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
	pradio->SetCurrentSelection(1);
	
}

void RAFDiaryList::OnSelectRlistboxctrl1(long row, long column) 
{
	if (row > 0)
		*currentptr = row -1;	
}
void	RAFDiaryList::RefreshData(int effect)
{
	Refresh();
}
