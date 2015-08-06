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

// RowanDialog: // LWDiaryL.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include	"sqddiary.h"

#include "LWDiaryL.h"
#include "mytime.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// LWDiaryList dialog


RDialog*	LWDiaryList::Make(SquadNum* grupnumptr, int* currentryptr, SquadronBase**	grdetailsptr)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_RAFDIRECTIVES,new LWDiaryList(grupnumptr, currentryptr, grdetailsptr))
			);
}


LWDiaryList::LWDiaryList(SquadNum* grupnumptr, int* currentryptr, SquadronBase**	grdetailsptr,CWnd* pParent /*=NULL*/)
	: RowanDialog(LWDiaryList::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWDiaryList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	grnumptr = grupnumptr;
	currentptr = currentryptr;
	grdtlsptr = grdetailsptr;
}


void LWDiaryList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWDiaryList)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RRADIODISPLAY, m_IDC_RRADIODISPLAY);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWDiaryList, CDialog)
	//{{AFX_MSG_MAP(LWDiaryList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWDiaryList message handlers

void LWDiaryList::Refresh()
{
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
	rlistbox->AddString(RESSTRING(RAID),1);
	rlistbox->AddString(RESSTRING(SIZE),2);
	rlistbox->AddString(RESSTRING(TOT),3);
	rlistbox->AddString(RESSTRING(MISSION),4);
	rlistbox->AddString(RESSTRING(TARGET),5);
	rlistbox->AddString(RESSTRING(TALLY),6);

	Diary::RaidGroup* raidgroup;
	Diary::Gruppen*	grentry;
	int i = 0;
 	while (	(i < LWDiary::MAX_SQDETAILS) && (grdtlsptr[i]))
 	{
			grentry = (Diary::Gruppen*)grdtlsptr[i];

 			//size
 			rlistbox->AddString(CSprintf("%i",grentry->noaclaunched),2);
		
 
 		raidgroup = Squad_Diary.GetRaidGroup(grdtlsptr[i]);
		if (raidgroup)
		{
 			//raid
	 		rlistbox->AddString("",1);//CSprintf("R%i", raidgroup->diaryraidpackindex),1);	//JIM 15Oct00
	 		//tot
 			int t=raidgroup->targettime/60;
 			rlistbox->AddString(CSprintf("%02i:%02i",t/60,t%60),3);
 
 			//mission
 			int cnt = (int)	raidgroup->misstype;
 			rlistbox->AddString(RESLIST(MT_RAID, cnt),4);
 
 			//target
 			if(!raidgroup->target)
 				rlistbox->AddString(RESSTRING(DASH),5);
			else
				rlistbox->AddString(GetTargName(raidgroup->target),5);

			Diary::RaidPack* raidpack = Squad_Diary.GetRaidPack(raidgroup);
			if (raidpack)
			{
				//date
		 		rlistbox->AddString(GetDateName(raidpack->date * SECSPERDAY, DATE_LONG),0);
 
			}


		}
 		//tally
 		int kills = grentry->kills[0] + grentry->kills[1];
 		rlistbox->AddString(CSprintf("+%i -%i", kills, grdtlsptr[i]->numlosses),6);
 
 
 		i++;
 	}
 
	rlistbox->SetHilightRow(*currentptr+1);



//DeadCode RDH 11Feb00 	rlistbox->AddString("10 July 1940",0);
//DeadCode RDH 11Feb00 	rlistbox->AddString("100",1);
//DeadCode RDH 11Feb00 	rlistbox->AddString("40",2);
//DeadCode RDH 11Feb00 	rlistbox->AddString("13:00",3);
//DeadCode RDH 11Feb00 	rlistbox->AddString("Strike",4);
//DeadCode RDH 11Feb00 	rlistbox->AddString("Biggin Hill",5);
//DeadCode RDH 11Feb00 	rlistbox->AddString("0/4",6);
//DeadCode RDH 11Feb00 
//DeadCode RDH 11Feb00 	rlistbox->AddString("10 July 1940",0);
//DeadCode RDH 11Feb00 	rlistbox->AddString("100",1);
//DeadCode RDH 11Feb00 	rlistbox->AddString("40",2);
//DeadCode RDH 11Feb00 	rlistbox->AddString("13:00",3);
//DeadCode RDH 11Feb00 	rlistbox->AddString("Strike",4);
//DeadCode RDH 11Feb00 	rlistbox->AddString("Biggin Hill",5);
//DeadCode RDH 11Feb00 	rlistbox->AddString("0/4",6);

}
BOOL LWDiaryList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Refresh();

//DeadCode RDH 11Feb00 	CRRadio* pradio;
//DeadCode RDH 11Feb00 
//DeadCode RDH 11Feb00 	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
//DeadCode RDH 11Feb00 	pradio->AddButton(RESSTRING(VIEWSINGLE));
//DeadCode RDH 11Feb00 	pradio->AddButton(RESSTRING(ALL));
//DeadCode RDH 11Feb00   	pradio->SetCurrentSelection(1);
//DeadCode RDH 11Feb00 
//DeadCode RDH 11Feb00 
//DeadCode RDH 11Feb00 	CRListBox* rlistbox;
//DeadCode RDH 11Feb00 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 11Feb00 	rlistbox->Clear();
//DeadCode RDH 11Feb00 	rlistbox->AddColumn(100);
//DeadCode RDH 11Feb00 	rlistbox->AddColumn(60);
//DeadCode RDH 11Feb00 	rlistbox->AddColumn(60);
//DeadCode RDH 11Feb00 	rlistbox->AddColumn(60);
//DeadCode RDH 11Feb00 	rlistbox->AddColumn(70);
//DeadCode RDH 11Feb00 	rlistbox->AddColumn(TARGETFIELDWIDTH);										  //RDH 02/06/99
//DeadCode RDH 11Feb00 	rlistbox->AddColumn(60);
//DeadCode RDH 11Feb00 
//DeadCode RDH 11Feb00 	rlistbox->AddString(RESSTRING(DATE),0);
//DeadCode RDH 11Feb00 	rlistbox->AddString(RESSTRING(RAID),1);
//DeadCode RDH 11Feb00 	rlistbox->AddString(RESSTRING(SIZE),2);
//DeadCode RDH 11Feb00 	rlistbox->AddString(RESSTRING(TO),3);
//DeadCode RDH 11Feb00 	rlistbox->AddString(RESSTRING(MISSION),4);
//DeadCode RDH 11Feb00 	rlistbox->AddString(RESSTRING(TARGET),5);
//DeadCode RDH 11Feb00 	rlistbox->AddString(RESSTRING(TALLY),6);
//DeadCode RDH 11Feb00 
//DeadCode RDH 11Feb00 	rlistbox->AddString("10 July 1940",0);
//DeadCode RDH 11Feb00 	rlistbox->AddString("100",1);
//DeadCode RDH 11Feb00 	rlistbox->AddString("40",2);
//DeadCode RDH 11Feb00 	rlistbox->AddString("13:00",3);
//DeadCode RDH 11Feb00 	rlistbox->AddString("Strike",4);
//DeadCode RDH 11Feb00 	rlistbox->AddString("Biggin Hill",5);
//DeadCode RDH 11Feb00 	rlistbox->AddString("0/4",6);
//DeadCode RDH 11Feb00 
//DeadCode RDH 11Feb00 	rlistbox->AddString("10 July 1940",0);
//DeadCode RDH 11Feb00 	rlistbox->AddString("100",1);
//DeadCode RDH 11Feb00 	rlistbox->AddString("40",2);
//DeadCode RDH 11Feb00 	rlistbox->AddString("13:00",3);
//DeadCode RDH 11Feb00 	rlistbox->AddString("Strike",4);
//DeadCode RDH 11Feb00 	rlistbox->AddString("Biggin Hill",5);
//DeadCode RDH 11Feb00 	rlistbox->AddString("0/4",6);


	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(LWDiaryList, CDialog)
    //{{AFX_EVENTSINK_MAP(LWDiaryList)
	ON_EVENT(LWDiaryList, IDC_RRADIOSIZE, 1 /* Selected */, OnSelectedRradiosize, VTS_I4)
	ON_EVENT(LWDiaryList, IDC_RRADIODISPLAY, 1 /* Selected */, OnSelectedRradiodisplay, VTS_I4)
	ON_EVENT(LWDiaryList, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void LWDiaryList::OnSelectedRradiosize(long ButtonNum) 
{
	// TODO: Add your control notification handler code here
	parent->RefreshData(0);
}

void	LWDiaryList::RefreshData(int gruppen)
{	
		Refresh();

}

void LWDiaryList::OnSelectedRradiodisplay(long ButtonNum) 
{
	parent->RefreshData(0);
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
	pradio->SetCurrentSelection(1);
	
}

void LWDiaryList::OnSelectRlistboxctrl1(long row, long column) 
{	
	if (row)
		*currentptr=row-1;
	// TODO: Add your control notification handler code here
	
}
