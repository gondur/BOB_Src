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

// RowanDialog: // RAFDryD.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include	"sqddiary.h"
#include "RAFDiary.h"
#include "RAFDryD.h"
#include "mytime.h"
#include "winmove.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFDiaryDetails dialog


RDialog*	RAFDiaryDetails::Make(SquadNum* squadnumptr, int* currentryptr, SquadronBase**	sqdetailsptr, bool quickmsn)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new RAFDiaryDetails(squadnumptr, currentryptr, sqdetailsptr, quickmsn))
			);
}


RAFDiaryDetails::RAFDiaryDetails(SquadNum* squadnumptr, int* currentryptr, SquadronBase**	sqdetailsptr, bool quickmsn,CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFDiaryDetails::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFDiaryDetails)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	sqnumptr = squadnumptr;
	currentptr = currentryptr;
	sqdtlsptr = sqdetailsptr;
	quickmission = quickmsn;
}


void RAFDiaryDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFDiaryDetails)
	DDX_Control(pDX, IDC_RBUTTON_NEXT, m_IDC_RBUTTON_NEXT);
	DDX_Control(pDX, IDC_RBUTTON_PREV, m_IDC_RBUTTON_PREV);
	DDX_Control(pDX, IDC_RRADIODISPLAY, m_IDC_RRADIODISPLAY);
	DDX_Control(pDX, IDC_RSTATICDIARYDATE, m_IDC_RSTATICDIARYDATE);
	DDX_Control(pDX, IDC_RSTATICPERSONNEL, m_IDC_RSTATICPERSONNEL);
	DDX_Control(pDX, IDC_RSTATICSTRIKEFORCE, m_IDC_RSTATICSTRIKEFORCE);
	DDX_Control(pDX, IDC_RSTATICTASK, m_IDC_RSTATICTASK);
	DDX_Control(pDX, IDC_RSTATICTIME, m_IDC_RSTATICTIME);
	DDX_Control(pDX, IDC_RSTATICDETACHEDFORCE, m_IDC_RSTATICDETACHEDFORCE);
	DDX_Control(pDX, IDC_RSTATICDESTROYED, m_IDC_RSTATICDESTROYED);
	DDX_Control(pDX, IDC_RSTATICDAMAGED, m_IDC_RSTATICDAMAGED);
	DDX_Control(pDX, IDC_RSTATICATTACHEDFORCE, m_IDC_RSTATICATTACHEDFORCE);
	DDX_Control(pDX, IDC_RSTATICAIRCREW, m_IDC_RSTATICAIRCREW);
	DDX_Control(pDX, IDC_RLISTBOXOTHERS, m_IDC_RLISTBOXOTHERS);
	DDX_Control(pDX, IDC_RSTATICINTERCEPT1, m_IDC_RSTATICINTERCEPT1);
	DDX_Control(pDX, IDC_RSTATICINTERCEPT2, m_IDC_RSTATICINTERCEPT2);
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RSTATICCTRLHURR, m_IDC_RSTATICCTRLHURR);
	DDX_Control(pDX, IDC_RSTATICCTRLSPIT, m_IDC_RSTATICCTRLSPIT);
	DDX_Control(pDX, IDC_RSTATICCTRLTOTAL, m_IDC_RSTATICCTRLTOTAL);
	DDX_Control(pDX, IDC_RSTATICDATE, m_IDC_RSTATICDATE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFDiaryDetails, CDialog)
	//{{AFX_MSG_MAP(RAFDiaryDetails)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFDiaryDetails message handlers

BEGIN_EVENTSINK_MAP(RAFDiaryDetails, CDialog)
    //{{AFX_EVENTSINK_MAP(RAFDiaryDetails)
	ON_EVENT(RAFDiaryDetails, IDC_RRADIODISPLAY, 1 /* Selected */, OnSelectedRradiodisplay, VTS_I4)
	ON_EVENT(RAFDiaryDetails, IDC_RBUTTON_NEXT, 1 /* Clicked */, OnClickedRbuttonNext, VTS_NONE)
	ON_EVENT(RAFDiaryDetails, IDC_RBUTTON_PREV, 1 /* Clicked */, OnClickedRbuttonPrev, VTS_NONE)
	ON_EVENT(RAFDiaryDetails, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(RAFDiaryDetails, IDC_RLISTBOXOTHERS, 1 /* Select */, OnSelectRlistboxothers, VTS_I4 VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void RAFDiaryDetails::OnSelectedRradiodisplay(long ButtonNum) 
{
	// TODO: Add your control notification handler code here
	parent->RefreshData(0);
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
	pradio->SetCurrentSelection(0);
	
}

void	RAFDiaryDetails::RefreshButtons()
{
	CRButton*	but;
	if (quickmission)
	{
		but = GETDLGITEM(IDC_RBUTTON_PREV);
		but->ShowWindow(false);
		but = GETDLGITEM(IDC_RBUTTON_NEXT);
		but->ShowWindow(false);
	}else
	{

		but = GETDLGITEM(IDC_RBUTTON_PREV);
		but->ShowWindow(true);
		if (*currentptr != 0)
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetBackColor(RGB(255,255,0));
			but->SetDisabled(false);
		}else
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}

		but = GETDLGITEM(IDC_RBUTTON_NEXT);
		but->ShowWindow(true);
		if (sqdtlsptr[*currentptr +1] != NULL)
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetBackColor(RGB(255,255,0));
			but->SetDisabled(false);
		}else
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}
	}
}

void RAFDiaryDetails::TotalUpAc(int& hurr, int& spit, int& total)
{ 
	Diary::Intercept* intercept;

	intercept = Squad_Diary.GetIntercept((Diary::Squadron*)sqdtlsptr[*currentptr]);
	Diary::Squadron* othersq = Squad_Diary.GetFirstSquadron(intercept);
	while (othersq)
	{
		Squadron* sq  = Node_Data[(SquadNum)othersq->squadnum];
		switch (sq->AcType())
		{
			case PT_SPIT_A:
			case PT_SPIT_B:
			{
				spit += othersq->noaclaunched;
				break;
			}
			case PT_HURR_A:
			case PT_HURR_B:
			{
				hurr += othersq->noaclaunched;
				break;
			}
		}
		total += othersq->noaclaunched;
		othersq = Squad_Diary.GetNextSquadron(othersq);
	}
}





void RAFDiaryDetails::Refresh()
{
		CRRadio* pradio;

	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
	if (quickmission)
		pradio->ShowWindow(false);
	else
		pradio->ShowWindow(true);

	pradio->AddButton(RESSTRING(VIEWSINGLE));
	pradio->AddButton(RESSTRING(ALL));
	pradio->SetCurrentSelection(0);

	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
	rlistbox->Clear();
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(40);										  //RDH 02/06/99
	rlistbox->AddColumn(40);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(TYPE),0);
	rlistbox->AddString(RESSTRING(L_ME109),0);
	rlistbox->AddString(RESSTRING(ME110),0);
	rlistbox->AddString(RESSTRING(L_JU87),0);
	rlistbox->AddString(RESSTRING(L_DO17),0);
	rlistbox->AddString(RESSTRING(JU88),0);
	rlistbox->AddString(RESSTRING(HE111),0);
	rlistbox->AddString(RESSTRING(TOTAL),0);
	rlistbox->AddString(RESSTRING(SEEN),1);
	rlistbox->AddString(RESSTRING(CLAIMS),2);



	rlistbox=GETDLGITEM(IDC_RLISTBOXOTHERS);
	rlistbox->Clear();
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(60);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(SQUADRON),0);
	rlistbox->AddString(RESSTRING(TASK),1);
	Diary::Intercept* intercept;
	

	if (*currentptr >= 0)
	{

		intercept = Squad_Diary.GetIntercept(sqdtlsptr[*currentptr]);
		if (intercept)
		{
			Diary::Squadron* othersq = Squad_Diary.GetFirstSquadron(intercept);
			while (othersq)
			{
				if (othersq != sqdtlsptr[*currentptr])
				{
					Squadron* sq = &Node_Data[(SquadNum)othersq->squadnum];
					if (othersq->noaclaunched)
					{
						if (sq->squadron>SQ_BR_END)
							rlistbox->AddString(RESLIST(SPIT_A,sq->AcType()),0);
						else
							rlistbox->AddString(sq->SubName(),0);

						intercept = Squad_Diary.GetIntercept(othersq);
						int cnt = int(!intercept->waspatrolinitially);	//RJS 29Aug00

 						rlistbox->AddString(RESLIST(AM_PATROL, cnt),1);
					}
				}
				othersq = Squad_Diary.GetNextSquadron(othersq);
			}


			intercept = Squad_Diary.GetIntercept(sqdtlsptr[*currentptr]);

			CRStatic*   s;
			CRStatic*   ss;
			Diary::RaidGroup* raidgroup;
			raidgroup = Squad_Diary.GetRaidGroup(intercept);

			//date

			ss=GETDLGITEM(IDC_RSTATICDATE);
			s=GETDLGITEM(IDC_RSTATICDIARYDATE);
			if (quickmission)
			{
				s->SetString(RESLIST(SPIT_A,Node_Data[SquadNum(sqdtlsptr[*currentptr]->squadnum)].AcType()));
				ss->SetString(Node_Data[SquadNum(sqdtlsptr[*currentptr]->squadnum)].SubName());
//DeadCode JIM 23Oct00 				s->ShowWindow(false);
//DeadCode JIM 23Oct00 				ss->ShowWindow(false);
			}else																			
			{
				s->ShowWindow(true);
				ss->ShowWindow(true);
			
				CString string = "";
				if (raidgroup)
				{
					Diary::RaidPack* raidpack = Squad_Diary.GetRaidPack(raidgroup);
					if (raidpack)
		 				string = GetDateName(raidpack->date * SECSPERDAY, DATE_LONG);
				}
				s->SetString(string);
			}			
//DEADCODE RDH 16/05/00 			s=GETDLGITEM(IDC_RSTATICPERSONNEL);
//DEADCODE RDH 16/05/00 			s->SetString("");
			if (intercept->interceptloc)
			{
				CString str;
				_Radio.GetLocationString(str,intercept->interceptloc);
				str=CSprintf("%s %s: %i %s",str,RESSTRING(ALT),
					(intercept->interceptheight+METRES100)/Save_Data.alt.longcm,
					LoadResString(Save_Data.alt.longabbr));
				GETDLGITEM(IDC_RSTATICINTERCEPT1)->SetString(str);

				CString	missString;										//RJS 9Nov00

				Squad_Diary.GetMissResult(sqdtlsptr[*currentptr],raidgroup,missString);

				GETDLGITEM(IDC_RSTATICINTERCEPT2)->SetString(missString);								//RJS 9Nov00
//DeadCode RJS 09Nov100 				GETDLGITEM(IDC_RSTATICINTERCEPT2)->SetString(RESLIST(MR_NULL,raidgroup->missresult));
			}
			else
			{
				GETDLGITEM(IDC_RSTATICINTERCEPT1)->SetString("");
				GETDLGITEM(IDC_RSTATICINTERCEPT2)->SetString("");
			}

			int hurr = 0, spit = 0, total = 0;
			TotalUpAc(hurr, spit, total);
 			int typeline=Node_Data[SquadNum(sqdtlsptr[*currentptr]->squadnum)].AcType()/2;
			s=GETDLGITEM(IDC_RSTATICCTRLHURR);
			if (typeline==1)
				s->SetString(CSprintf("%i/%i",sqdtlsptr[*currentptr]->noaclaunched,hurr));
			else
				s->SetString(CSprintf("%i",hurr));
			s=GETDLGITEM(IDC_RSTATICCTRLSPIT);
			if (typeline==0)
				s->SetString(CSprintf("%i/%i",sqdtlsptr[*currentptr]->noaclaunched,spit));
			else
				s->SetString(CSprintf("%i",spit));
			s=GETDLGITEM(IDC_RSTATICCTRLTOTAL);
			if (typeline==2)
				s->SetString(CSprintf("%i/%i",sqdtlsptr[*currentptr]->noaclaunched,total));
			else
				s->SetString(CSprintf("%i",total));

			s=GETDLGITEM(IDC_RSTATICTASK);
			int cnt = int(!intercept->waspatrolinitially);				//RJS 29Aug00
			s->SetString(RESLIST(AM_PATROL, cnt));

			s=GETDLGITEM(IDC_RSTATICTIME);

// we want intercept time if we've got it...
			int	t;
			if (intercept->intercepttime)								//RJS 7Sep00
				t = intercept->intercepttime;							//RJS 7Sep00
			else														//RJS 7Sep00
				t = intercept->takeofftime;								//RJS 7Sep00

			t /= 60;													//RJS 7Sep00
			s->SetString(CSprintf("%02i:%02i",t/60,t%60));

	//		s=GETDLGITEM(IDC_RSTATICDETACHEDFORCE);
	//		s->SetString("");
	//		s=GETDLGITEM(IDC_RSTATICATTACHEDFORCE);
	//		s->SetString("");
			s=GETDLGITEM(IDC_RSTATICDAMAGED);
			s->SetString(CSprintf("%i",sqdtlsptr[*currentptr]->numacdamaged));

			s=GETDLGITEM(IDC_RSTATICDESTROYED);
			s->SetString(CSprintf("%i",sqdtlsptr[*currentptr]->numlosses));
			s=GETDLGITEM(IDC_RSTATICAIRCREW);
			s->SetString(CSprintf("%i",sqdtlsptr[*currentptr]->numpilotslost));


			TotalEncounteredAc();

			CRListBox* rlistbox;
			rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
			for (cnt=0; cnt < (MAXTYPES); cnt++)
			{
				rlistbox->AddString(CSprintf("%i",enemyac[cnt].seen),1);
				rlistbox->AddString(CSprintf("%i/%i",enemyac[cnt].localkilled,enemyac[cnt].killed),2);
			}
		}else
		{

			CRStatic*   s;

			s=GETDLGITEM(IDC_RSTATICDIARYDATE);
			s->SetString("");
//DEADCODE CSB 08/05/00 			s=GETDLGITEM(IDC_RSTATICPERSONNEL);
//DEADCODE CSB 08/05/00 			s->SetString("");
			s=GETDLGITEM(IDC_RSTATICINTERCEPT1);
			s->SetString("");
			s=GETDLGITEM(IDC_RSTATICINTERCEPT2);
			s->SetString("");

			s=GETDLGITEM(IDC_RSTATICCTRLHURR);
			s->SetString("");
			s=GETDLGITEM(IDC_RSTATICCTRLSPIT);
			s->SetString("");
			s=GETDLGITEM(IDC_RSTATICCTRLTOTAL);
			s->SetString("");


			s=GETDLGITEM(IDC_RSTATICTASK);
			s->SetString("");

			s=GETDLGITEM(IDC_RSTATICTIME);
			s->SetString("");

	//		s=GETDLGITEM(IDC_RSTATICDETACHEDFORCE);
	//		s->SetString("");
	//		s=GETDLGITEM(IDC_RSTATICATTACHEDFORCE);
	//		s->SetString("");

			s=GETDLGITEM(IDC_RSTATICDAMAGED);
			s->SetString("");
			s=GETDLGITEM(IDC_RSTATICDESTROYED);
			s->SetString("");
			s=GETDLGITEM(IDC_RSTATICAIRCREW);
			s->SetString("");
		}
	}
	RefreshButtons();

}
void RAFDiaryDetails::TotalEncounteredAc()
{
	for (int cnt=0; cnt < (MAXTYPES); cnt++)
	{
		enemyac[cnt].seen = 0;
		enemyac[cnt].killed = 0;
		enemyac[cnt].localkilled = 0;
	}
	Diary::Intercept* intercept;

	intercept = Squad_Diary.GetIntercept((Diary::Squadron*)sqdtlsptr[*currentptr]);
	Diary::RaidGroup* raidgroup;

	raidgroup = Squad_Diary.GetRaidGroup(intercept);
	if (raidgroup)
	{
		Diary::RaidPack*	raidpack = Squad_Diary.GetRaidPack(raidgroup);
		Diary::RaidGroup*	otherraidgroup = Squad_Diary.GetFirstRaidGroup(raidpack);

		while(otherraidgroup)
		{
			Diary::Gruppen* othergr = Squad_Diary.GetFirstSquadron(otherraidgroup);
			while (othergr)
			{
				Squadron* sq  = Node_Data[(SquadNum)othergr->squadnum];
				int index = (int)sq->AcType() - PT_GER_FLYABLE;
				if (	(index >=0)	&&	(index < (PT_LWTOTAL)))
				{
					enemyac[index].seen += othergr->noaclaunched;
//DeadCode RJS 14Sep00 					enemyac[index].killed +=  othergr->numlosses;;
					enemyac[PT_LWTOTAL].seen += othergr->noaclaunched;
//DeadCode RJS 14Sep00 					enemyac[PT_LWTOTAL].killed +=  othergr->numlosses;;
				}

				othergr = Squad_Diary.GetNextSquadron(othergr);
			}
			otherraidgroup = Squad_Diary.GetNextRaidGroup(otherraidgroup);
		}

//We want to tot up all the KILLS for this intercept (NOT enemy LOSSES)
		Diary::Squadron*	squadptr = Squad_Diary.GetFirstSquadron(intercept);	//RJS 14Sep00
		while (squadptr)
		{
			int	index;
			for (index=0; index < 5; index++)
			{
				enemyac[index].killed += squadptr->kills[index];
				enemyac[PT_LWTOTAL].killed += squadptr->kills[index];
			}

			squadptr = Squad_Diary.GetNextSquadron(squadptr);
		}
		squadptr=(Diary::Squadron*)sqdtlsptr[*currentptr];
			int	index;
			for (index=0; index < 5; index++)
			{
				enemyac[index].localkilled = squadptr->kills[index];
				enemyac[PT_LWTOTAL].localkilled += squadptr->kills[index];
			}

	}
}


BOOL RAFDiaryDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();

	Refresh();
	
//DEADCODE  09/02/00 	CRRadio* pradio;
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
//DEADCODE  09/02/00 	pradio->AddButton(RESSTRING(VIEWSINGLE));
//DEADCODE  09/02/00 	pradio->AddButton(RESSTRING(ALL));
//DEADCODE  09/02/00 	pradio->SetCurrentSelection(0);
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	CRListBox* rlistbox;
//DEADCODE  09/02/00 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DEADCODE  09/02/00 	rlistbox->Clear();
//DEADCODE  09/02/00 	rlistbox->AddColumn(60);
//DEADCODE  09/02/00 	rlistbox->AddColumn(80);										  //RDH 02/06/99
//DEADCODE  09/02/00 	rlistbox->AddColumn(60);										  //RDH 02/06/99
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(TYPE),0);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(JU88),0);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(L_ME109),0);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(TOTAL),0);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(ENCOUNTERED),1);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(CLAIMS),2);
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	rlistbox->AddString("10",1);
//DEADCODE  09/02/00 	rlistbox->AddString("4",2);
//DEADCODE  09/02/00 	rlistbox->AddString("20",1);
//DEADCODE  09/02/00 	rlistbox->AddString("3",2);
//DEADCODE  09/02/00 	rlistbox->AddString("30",1);
//DEADCODE  09/02/00 	rlistbox->AddString("7",2);
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	rlistbox=GETDLGITEM(IDC_RLISTBOXOTHERS);
//DEADCODE  09/02/00 	rlistbox->Clear();
//DEADCODE  09/02/00 	rlistbox->AddColumn(60);
//DEADCODE  09/02/00 	rlistbox->AddColumn(60);										  //RDH 02/06/99
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(SQUADRON),0);
//DEADCODE  09/02/00 	rlistbox->AddString(RESSTRING(TASK),1);
//DEADCODE  09/02/00 	rlistbox->AddString("222",0);
//DEADCODE  09/02/00 	rlistbox->AddString("Bombers",1);
//DEADCODE  09/02/00 	
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	CRStatic*   s;
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICDIARYDATE);
//DEADCODE  09/02/00 	s->SetString("20 July 1940");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICPERSONNEL);
//DEADCODE  09/02/00 	s->SetString("Captain White went missing today");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICINTERCEPT1);
//DEADCODE  09/02/00 	s->SetString("Over Dover. 18,000ft");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICSTRIKEFORCE);
//DEADCODE  09/02/00 	s->SetString("30 Ju88");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICINTERCEPT2);
//DEADCODE  09/02/00 	s->SetString("Over Biggin Hill. 20,000ft");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICTASK);
//DEADCODE  09/02/00 	s->SetString("Intercept");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICTIME);
//DEADCODE  09/02/00 	s->SetString("13:40");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICDETACHEDFORCE);
//DEADCODE  09/02/00 	s->SetString("30 Me109");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICATTACHEDFORCE);
//DEADCODE  09/02/00 	s->SetString("20 Me110");
//DEADCODE  09/02/00 
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICDAMAGED);
//DEADCODE  09/02/00 	s->SetString("4");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICDESTROYED);
//DEADCODE  09/02/00 	s->SetString("5");
//DEADCODE  09/02/00 	s=GETDLGITEM(IDC_RSTATICAIRCREW);
//DEADCODE  09/02/00 	s->SetString("8");

	rafdiary_timer=SetTimer(DPlay::TIMER_DEBRIEF,0,NULL); // set sheet up first before starting timer
	_DPlay.SendStatusChange(DPlay::CPS_DEBRIEF);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void RAFDiaryDetails::OnClickedRbuttonNext() 
{
	*currentptr = *currentptr + 1;
	Refresh();
}

void RAFDiaryDetails::OnClickedRbuttonPrev() 
{
	*currentptr = *currentptr - 1;
	Refresh();
	
}
void	RAFDiaryDetails::RefreshData(int effect)
{
	Refresh();
}

void RAFDiaryDetails::OnSelectRlistboxctrl1(long row, long column) 
{
	// TODO: Add your control notification handler code here
	
}

void RAFDiaryDetails::OnSelectRlistboxothers(long row, long column) 
{
	if (*currentptr >= 0)
	{
		Diary::Intercept* intercept;
		intercept = Squad_Diary.GetIntercept((Diary::Squadron*)sqdtlsptr[*currentptr]);
		Diary::Squadron* othersq = Squad_Diary.GetFirstSquadron(intercept);
		int index = 0;
		while (othersq)
		{
			if ((othersq != sqdtlsptr[*currentptr])	&& (othersq->noaclaunched))
				index++;
			if (index == row)
				break;
			else
				othersq = Squad_Diary.GetNextSquadron(othersq);
		}
		if (index == row)
		{	
			*sqnumptr = (SquadNum)othersq->squadnum;
			RAFDiary::FillSquadronDetails(*sqnumptr,othersq,sqdtlsptr,*currentptr);
			parent->RefreshData(2);
			Refresh();
		}
	}
	
}

void RAFDiaryDetails::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(rafdiary_timer);
}

void RAFDiaryDetails::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==rafdiary_timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}
