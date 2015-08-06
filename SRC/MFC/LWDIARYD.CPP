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

// RowanDialog: // LWDiaryD.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include	"sqddiary.h"
#include "mytime.h"

#include "LWDiaryD.h"
#include "winmove.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// LWDiaryDetails dialog
//DEADCODE  11/02/00 cloakdef(Diary::RaidGroup,LWDiaryDetails::RaidGroup);


RDialog*	LWDiaryDetails::Make(SquadNum* grupnumptr, int* currentryptr, SquadronBase**	grdetailsptr, bool quickmsn)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_D_RAFDIRECTIVES,new LWDiaryDetails(grupnumptr, currentryptr, grdetailsptr,quickmsn))
			);
}


LWDiaryDetails::LWDiaryDetails(SquadNum* grupnumptr, int* currentryptr, SquadronBase**	grdetailsptr, bool quickmsn,CWnd* pParent /*=NULL*/)
	: RowanDialog(LWDiaryDetails::IDD, pParent)
{
	//{{AFX_DATA_INIT(LWDiaryDetails)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	grnumptr = grupnumptr;
	currentptr = currentryptr;
	grdtlsptr = grdetailsptr;
	quickmission = quickmsn;

}


void LWDiaryDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LWDiaryDetails)
	DDX_Control(pDX, IDC_RRADIODISPLAY, m_IDC_RRADIODISPLAY);
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_RSTATICDIARYDATE, m_IDC_RSTATICDIARYDATE);
	DDX_Control(pDX, IDC_RSTATICPERSONNEL, m_IDC_RSTATICPERSONNEL);
	DDX_Control(pDX, IDC_RSTATICRESULT, m_IDC_RSTATICRESULT);
	DDX_Control(pDX, IDC_RSTATICSTRIKEFORCE, m_IDC_RSTATICSTRIKEFORCE);
	DDX_Control(pDX, IDC_RSTATICTARGET, m_IDC_RSTATICTARGET);
	DDX_Control(pDX, IDC_RSTATICTASK, m_IDC_RSTATICTASK);
	DDX_Control(pDX, IDC_RSTATICTIME, m_IDC_RSTATICTIME);
	DDX_Control(pDX, IDC_RSTATICDETACHEDFORCE, m_IDC_RSTATICDETACHEDFORCE);
	DDX_Control(pDX, IDC_RSTATICATTACHEDFORCE, m_IDC_RSTATICATTACHEDFORCE);
	DDX_Control(pDX, IDC_RSTATICAIRCRAFT, m_IDC_RSTATICAIRCRAFT);
	DDX_Control(pDX, IDC_RLISTBOXOTHERS, m_IDC_RLISTBOXOTHERS);
	DDX_Control(pDX, IDC_RSTATICDAMAGED, m_IDC_RSTATICDAMAGED);
	DDX_Control(pDX, IDC_RSTATICDESTROYED, m_IDC_RSTATICDESTROYED);
	DDX_Control(pDX, IDC_RSTATICAIRCREW, m_IDC_RSTATICAIRCREW);
	DDX_Control(pDX, IDC_RBUTTON_NEXT, m_IDC_RBUTTON_NEXT);
	DDX_Control(pDX, IDC_RBUTTON_PREV, m_IDC_RBUTTON_PREV);
	DDX_Control(pDX, IDC_RSTATICDETACHED, m_IDC_RSTATICDETACHED);
	DDX_Control(pDX, IDC_RSTATICMAIN, m_IDC_RSTATICMAIN);
	DDX_Control(pDX, IDC_RSTATICATTACHED, m_IDC_RSTATICATTACHED);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LWDiaryDetails, CDialog)
	//{{AFX_MSG_MAP(LWDiaryDetails)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LWDiaryDetails message handlers

BEGIN_EVENTSINK_MAP(LWDiaryDetails, CDialog)
    //{{AFX_EVENTSINK_MAP(LWDiaryDetails)
	ON_EVENT(LWDiaryDetails, IDC_RRADIOSIZE, 1 /* Selected */, OnSelectedRradiosize, VTS_I4)
	ON_EVENT(LWDiaryDetails, IDC_RRADIODISPLAY, 1 /* Selected */, OnSelectedRradiodisplay, VTS_I4)
	ON_EVENT(LWDiaryDetails, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(LWDiaryDetails, IDC_RLISTBOXOTHERS, 1 /* Select */, OnSelectRlistboxothers, VTS_I4 VTS_I4)
	ON_EVENT(LWDiaryDetails, IDC_RBUTTON_NEXT, 1 /* Clicked */, OnClickedRbuttonNext, VTS_NONE)
	ON_EVENT(LWDiaryDetails, IDC_RBUTTON_PREV, 1 /* Clicked */, OnClickedRbuttonPrev, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void LWDiaryDetails::OnSelectedRradiosize(long ButtonNum) 
{
	// TODO: Add your control notification handler code here
	
}

void	LWDiaryDetails::RefreshData(int gruppen)
{
		Refresh();


}
void	LWDiaryDetails::RefreshButtons()
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
			but->SetDisabled(false);
		}else
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}

		but = GETDLGITEM(IDC_RBUTTON_NEXT);
		but->ShowWindow(true);
		if (grdtlsptr[*currentptr +1] != NULL)
		{
			but->SetForeColor(RGB(255,255,0));
			but->SetDisabled(false);
		}else
		{
			but->SetForeColor(RGB(160,160,0));
			but->SetBackColor(RGB(160,160,0));
			but->SetDisabled(true);
		}
	}
}

void LWDiaryDetails::TotalEncounteredAc(EncounteredAcType * encounters)
{
	Diary::RaidGroup* raidgroup = Squad_Diary.GetRaidGroup(grdtlsptr[*currentptr]);
	Diary::Intercept* intercept = 	Squad_Diary.GetFirstIntercept(raidgroup);

	while(intercept)
	{
		Diary::Squadron* othersq = Squad_Diary.GetFirstSquadron(intercept);
		while (othersq)
		{
			Squadron* sq  = Node_Data[(SquadNum)othersq->squadnum];
			int encounter=sq->AcType()/2;
			encounters[encounter].encountered+=othersq->noaclaunched;
			if (othersq->noaclaunched)
				encounters[encounter].type=sq->AcType();
			encounters[encounter].totalkilled+=othersq->numlosses;

			othersq = Squad_Diary.GetNextSquadron(othersq);
		}


		intercept = Squad_Diary.GetNextIntercept(intercept);
	}
	Diary::Gruppen* thisrec=(Diary::Gruppen*)(grdtlsptr[*currentptr]);
	encounters[0].localkilled=thisrec->kills[0];
	encounters[1].localkilled=thisrec->kills[1];
	encounters[2].localkilled=thisrec->kills[2];

}


void LWDiaryDetails::TotalUpAc(int& strikeac, int& attachedac, int& detachedac,int& myrole)
{
	Diary::RaidGroup* raidgroup = Squad_Diary.GetRaidGroup(grdtlsptr[*currentptr]);
	myrole=raidgroup->misstype;
	Diary::RaidPack* raidpack = Squad_Diary.GetRaidPack(raidgroup);
	Diary::RaidGroup*	otherraidgroup = Squad_Diary.GetFirstRaidGroup(raidpack);
	while(otherraidgroup)
	{
		Diary::Gruppen* othergr = Squad_Diary.GetFirstSquadron(otherraidgroup);
		while (othergr)
		{
			switch (otherraidgroup->misstype)							//RJS 4Sep00
			{
				case MT_RAID:
				case MT_RECON:
				case MT_PATROL:
				{
					strikeac +=  othergr->noaclaunched;
					break;
				}
				case MT_ESCORT:
				{
					detachedac += othergr->noaclaunched;
					break;
				}
				case MT_CLOSEESCORT:
				{
					detachedac += othergr->noaclaunched;
					break;
				}
			}

			othergr = Squad_Diary.GetNextSquadron(othergr);
		}


		otherraidgroup = Squad_Diary.GetNextRaidGroup(otherraidgroup);
	}

}
void LWDiaryDetails::Refresh()
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
	rlistbox->AddColumn(80);										  //RDH 02/06/99
	rlistbox->AddColumn(60);										  //RDH 02/06/99

	rlistbox=GETDLGITEM(IDC_RLISTBOXOTHERS);
	rlistbox->Clear();
	rlistbox->AddColumn(60);
	rlistbox->AddColumn(60);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(GRUPPE),0);
	rlistbox->AddString(RESSTRING(TASK),1);
	CRStatic*   s;


	if (		(*currentptr >= 0)
			&&	(grdtlsptr[*currentptr])
		)
	{
		Diary::RaidGroup* raidgroup;
		Diary::Gruppen*	grentry;
	 	raidgroup = Squad_Diary.GetRaidGroup(grdtlsptr[*currentptr]);

		Diary::Gruppen* othergr = Squad_Diary.GetFirstSquadron(raidgroup);
		rlistbox=GETDLGITEM(IDC_RLISTBOXOTHERS);
	

		while (othergr)
		{
			if (othergr != grdtlsptr[*currentptr] && othergr->noaclaunched)
			{
				Squadron* sq = &Node_Data[(SquadNum)othergr->squadnum];
				CString name = sq->ShortName() + "/";
				name = name + sq->SubName();

				rlistbox->AddString(name,0);

				raidgroup = Squad_Diary.GetRaidGroup(othergr);
				int cnt = (int)	raidgroup->misstype;
	 			rlistbox->AddString(RESLIST(MT_RAID, cnt),1);
 
			}
			othergr = Squad_Diary.GetNextSquadron(othergr);
		}


//DeadCode RJS 4Sep00 		raidgroup = Squad_Diary.GetRaidGroup(grdtlsptr[*currentptr]);
		
		
		raidgroup = Squad_Diary.GetRaidGroup(grdtlsptr[*currentptr]);
		if (raidgroup)
		{
			int	theTime = 0;											//RJS 4Sep00

			//raid
			s=GETDLGITEM(IDC_RSTATICDIARYDATE);
			Diary::RaidPack* raidpack = Squad_Diary.GetRaidPack(raidgroup);
			if (raidpack)
			{
				s->SetString(GetDateName(raidpack->date * SECSPERDAY, DATE_LONG));

				int strikeac = 0, attachedac = 0, detachedac = 0,myrole=0;
				TotalUpAc( strikeac, attachedac, detachedac ,myrole);
				s=GETDLGITEM(IDC_RSTATICMAIN);
				myrole&=Profile::AM_GROUPMASK;
				if (myrole==Profile::AM_LWPACKS)
					s->SetString(CSprintf("%i/%i",grdtlsptr[*currentptr]->noaclaunched,strikeac));
				else
					s->SetString(CSprintf("%i",strikeac));
				s=GETDLGITEM(IDC_RSTATICDETACHED);
				if (myrole==Profile::AM_DETACHED)
					s->SetString(CSprintf("%i/%i",grdtlsptr[*currentptr]->noaclaunched,detachedac));
				else
					s->SetString(CSprintf("%i",detachedac));
				s=GETDLGITEM(IDC_RSTATICATTACHED);
				if (myrole>=Profile::AM_ATTACHED)
					s->SetString(CSprintf("%i/%i",grdtlsptr[*currentptr]->noaclaunched,attachedac));
				else
					s->SetString(CSprintf("%i",attachedac));

				EncounteredAcType seenac[3]={{PT_BADMAX}};
				int hurrseen = 0, spitseen = 0, hurrkilled = 0, spitkilled = 0;
				TotalEncounteredAc(seenac);
				CRListBox* rlistbox;
				rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
				rlistbox->AddString(RESSTRING(TYPE),0);
				rlistbox->AddString(RESSTRING(ENCOUNTERED),1);
				rlistbox->AddString(RESSTRING(CLAIMS),2);
//DeadCode JIM 23Oct00 				if (seenac[2].totalkilled)
//DeadCode JIM 23Oct00 					if (seenac[0].encountered==0)
//DeadCode JIM 23Oct00 						seenac[2].localkilled = seenac[0].localkilled;
//DeadCode JIM 23Oct00 					else
//DeadCode JIM 23Oct00 						if (seenac[1].encountered==0)
//DeadCode JIM 23Oct00 							seenac[2].localkilled = seenac[1].localkilled;
				for (int i=0;i<3;i++)
					if (seenac[i].encountered)
					{	
						if (seenac[i].localkilled>seenac[i].totalkilled)
							seenac[i].localkilled=seenac[i].totalkilled;
							
						rlistbox->AddString(RESLIST(SPIT_A,seenac[i].type),0);
 						rlistbox->AddString(CSprintf("%i",seenac[i].encountered),1);
						rlistbox->AddString(CSprintf("%i/%i",seenac[i].localkilled,seenac[i].totalkilled),2);
					}
				rlistbox->AddString(RESSTRING(TOTAL),0);
				rlistbox->AddString(CSprintf("%i",
					seenac[0].encountered+seenac[1].encountered+seenac[2].encountered),1);
				rlistbox->AddString(CSprintf("%i/%i",
					seenac[0].localkilled+seenac[1].localkilled+seenac[2].localkilled,
					seenac[0].totalkilled+seenac[1].totalkilled+seenac[2].totalkilled
					),2);

				theTime = raidpack->takeofftime;						//RJS 4Sep00
			}
			else
			{
				s->SetString("");
				s=GETDLGITEM(IDC_RSTATICMAIN);
				s->SetString("");
				s=GETDLGITEM(IDC_RSTATICDETACHED);
				s->SetString("");
				s=GETDLGITEM(IDC_RSTATICATTACHED);
				s->SetString("");


			}
			s=GETDLGITEM(IDC_RSTATICPERSONNEL);
			s->SetString("");

			s=GETDLGITEM(IDC_RSTATICTARGET);
			if(!raidgroup->target)
			{
				s->SetString("");
				s=GETDLGITEM(IDC_RSTATICRESULT);
				s->SetString("");
			}
			else
			{
				s->SetString(GetTargName(raidgroup->target));

				s=GETDLGITEM(IDC_RSTATICRESULT);
//DeadCode JIM 20Oct00 			 	TargetNoDetail* trg = Node_Data[raidgroup->target];

				CString	missString;										//RJS 9Nov00

				Squad_Diary.GetMissResult(grdtlsptr[*currentptr],raidgroup,missString);

				s->SetString(missString);								//RJS 9Nov00
//DeadCode RJS 09Nov00 				s->SetString(RESLIST(MR_NULL,raidgroup->missresult));
//DeadCode JIM 13Oct00 				int j = trg->PlayerStatus();
//DeadCode JIM 13Oct00 				if	(		(j == Target::TS_FLAG_UNKNOWN))
//DeadCode JIM 13Oct00 					s->SetString(RESSTRING(TT_UNKNOWN));
//DeadCode JIM 13Oct00 				else
//DeadCode JIM 13Oct00 				{
//DeadCode JIM 13Oct00 					if		(j >= Target::TS_NEARLYDESTROYED)		j = 3;
//DeadCode JIM 13Oct00 					elseif	(j>Target::TS_BADDAMAGE)				j=2;
//DeadCode JIM 13Oct00 					elseif	(j>Target::TS_LIGHTDAMAGE)				j=1;
//DeadCode JIM 13Oct00 					else											j=0;
//DeadCode JIM 13Oct00 					s->SetString(RESLIST(UNDAMAGED, j));
//DeadCode JIM 13Oct00 				}
			}

			s=GETDLGITEM(IDC_RSTATICTASK);
			s->SetString(RESLIST(MT_RAID, raidgroup->misstype));

			s=GETDLGITEM(IDC_RSTATICTIME);

			if (raidgroup->targettime)									//RJS 4Sep00
				theTime = raidgroup->targettime;						//RJS 4Sep00
																		//RJS 4Sep00
 			theTime/=60;												//RJS 4Sep00
			s->SetString(CSprintf("%02i:%02i",theTime/60,theTime%60));	//RJS 4Sep00


			s=GETDLGITEM(IDC_RSTATICAIRCRAFT);
			Squadron* sq  = Node_Data[*grnumptr];
			s->SetString(RESLIST(SPIT_A, sq->AcType()));
		}

		s=GETDLGITEM(IDC_RSTATICDAMAGED);
		s->SetString(CSprintf("%i",grdtlsptr[*currentptr]->numacdamaged));

		s=GETDLGITEM(IDC_RSTATICDESTROYED);
		s->SetString(CSprintf("%i",grdtlsptr[*currentptr]->numlosses));
		s=GETDLGITEM(IDC_RSTATICAIRCREW);
		s->SetString(CSprintf("%i",grdtlsptr[*currentptr]->numpilotslost));

	}else
	{



		s=GETDLGITEM(IDC_RSTATICDIARYDATE);
		s->SetString("");
		s=GETDLGITEM(IDC_RSTATICTASK);
		s->SetString("");
		s=GETDLGITEM(IDC_RSTATICTIME);
		s->SetString("");

		s=GETDLGITEM(IDC_RSTATICAIRCRAFT);
		s->SetString("");
		s=GETDLGITEM(IDC_RSTATICRESULT);
		s->SetString("");
		s=GETDLGITEM(IDC_RSTATICTARGET);
		s->SetString("");

		s=GETDLGITEM(IDC_RSTATICMAIN);
		s->SetString("");
		s=GETDLGITEM(IDC_RSTATICDETACHED);
		s->SetString("");
		s=GETDLGITEM(IDC_RSTATICATTACHED);
		s->SetString("");


		s=GETDLGITEM(IDC_RSTATICPERSONNEL);
		s->SetString("");

		s=GETDLGITEM(IDC_RSTATICDAMAGED);
		s->SetString("");
		s=GETDLGITEM(IDC_RSTATICDESTROYED);
		s->SetString("");
		s=GETDLGITEM(IDC_RSTATICAIRCREW);
		s->SetString("");
	}
	RefreshButtons();
}

void LWDiaryDetails::OnSelectedRradiodisplay(long ButtonNum) 
{
	parent->RefreshData(0);
	CRRadio* pradio;
	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
	pradio->SetCurrentSelection(0);
	
}

BOOL LWDiaryDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Refresh();

//DEADCODE  11/02/00 	CRRadio* pradio;
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 	pradio=GETDLGITEM(IDC_RRADIODISPLAY);
//DEADCODE  11/02/00 	pradio->AddButton(RESSTRING(VIEWSINGLE));
//DEADCODE  11/02/00 	pradio->AddButton(RESSTRING(ALL));
//DEADCODE  11/02/00 	pradio->SetCurrentSelection(0);
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 	CRListBox* rlistbox;
//DEADCODE  11/02/00 	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DEADCODE  11/02/00 	rlistbox->Clear();
//DEADCODE  11/02/00 	rlistbox->AddColumn(60);
//DEADCODE  11/02/00 	rlistbox->AddColumn(80);										  //RDH 02/06/99
//DEADCODE  11/02/00 	rlistbox->AddColumn(60);										  //RDH 02/06/99
//DEADCODE  11/02/00 	rlistbox->AddString(RESSTRING(TYPE),0);
//DEADCODE  11/02/00 	rlistbox->AddString(RESSTRING(L_SPIT_A),0);
//DEADCODE  11/02/00 	rlistbox->AddString(RESSTRING(HURR_A),0);
//DEADCODE  11/02/00 	rlistbox->AddString(RESSTRING(TOTAL),0);
//DEADCODE  11/02/00 	rlistbox->AddString(RESSTRING(ENCOUNTERED),1);
//DEADCODE  11/02/00 	rlistbox->AddString(RESSTRING(CLAIMS),2);
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 	rlistbox->AddString("10",1);
//DEADCODE  11/02/00 	rlistbox->AddString("4",2);
//DEADCODE  11/02/00 	rlistbox->AddString("20",1);
//DEADCODE  11/02/00 	rlistbox->AddString("3",2);
//DEADCODE  11/02/00 	rlistbox->AddString("30",1);
//DEADCODE  11/02/00 	rlistbox->AddString("7",2);
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 	rlistbox=GETDLGITEM(IDC_RLISTBOXOTHERS);
//DEADCODE  11/02/00 	rlistbox->Clear();
//DEADCODE  11/02/00 	rlistbox->AddColumn(60);
//DEADCODE  11/02/00 	rlistbox->AddColumn(60);										  //RDH 02/06/99
//DEADCODE  11/02/00 	rlistbox->AddString(RESSTRING(GRUPPE),0);
//DEADCODE  11/02/00 	rlistbox->AddString(RESSTRING(TASK),1);
//DEADCODE  11/02/00 	rlistbox->AddString("26/I",0);
//DEADCODE  11/02/00 	rlistbox->AddString("Strike",1);
//DEADCODE  11/02/00 	rlistbox->AddString("34/II",0);
//DEADCODE  11/02/00 	rlistbox->AddString("Attached",1);
//DEADCODE  11/02/00 	rlistbox->AddString("26/III",0);
//DEADCODE  11/02/00 	rlistbox->AddString("Detached",1);
//DEADCODE  11/02/00 	
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 	CRStatic*   s;
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICDIARYDATE);
//DEADCODE  11/02/00 	s->SetString("20 July 1940");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICPERSONNEL);
//DEADCODE  11/02/00 	s->SetString("Major Schmidt went missing today");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICRESULT);
//DEADCODE  11/02/00 	s->SetString("Target Damaged");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICSTRIKEFORCE);
//DEADCODE  11/02/00 	s->SetString("30 Ju88");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICTARGET);
//DEADCODE  11/02/00 	s->SetString("Biggin Hill");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICTASK);
//DEADCODE  11/02/00 	s->SetString("Attached Escort");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICTIME);
//DEADCODE  11/02/00 	s->SetString("13:40");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICDETACHEDFORCE);
//DEADCODE  11/02/00 	s->SetString("30 Me109");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICATTACHEDFORCE);
//DEADCODE  11/02/00 	s->SetString("20 Me110");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICAIRCRAFT);
//DEADCODE  11/02/00 	s->SetString("40");
//DEADCODE  11/02/00 
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICDAMAGED);
//DEADCODE  11/02/00 	s->SetString("4");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICDESTROYED);
//DEADCODE  11/02/00 	s->SetString("5");
//DEADCODE  11/02/00 	s=GETDLGITEM(IDC_RSTATICAIRCREW);
//DEADCODE  11/02/00 	s->SetString("8");

	lwdiary_timer=SetTimer(DPlay::TIMER_DEBRIEF,0,NULL); // set sheet up first before starting timer
	_DPlay.SendStatusChange(DPlay::CPS_DEBRIEF);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void LWDiaryDetails::OnSelectRlistboxctrl1(long row, long column) 
{
	// TODO: Add your control notification handler code here
	
}

void LWDiaryDetails::OnSelectRlistboxothers(long row, long column) 
{
	if (row>0 && *currentptr >= 0)
	{
		Diary::RaidGroup* raidgroup;
		raidgroup = Squad_Diary.GetRaidGroup((Diary::Squadron*)grdtlsptr[*currentptr]);
		Diary::Gruppen* othergr = Squad_Diary.GetFirstSquadron(raidgroup);
		int index = 0;
		while (othergr)
		{
			if (othergr != grdtlsptr[*currentptr] && othergr->noaclaunched)
				index++;
			if (index == row)
				break;
			else
				othergr = Squad_Diary.GetNextSquadron(othergr);
		}
		if (index == row && othergr)
		{	
			*grnumptr = (SquadNum)othergr->squadnum;
			LWDiary::FillGruppeDetails(*grnumptr,othergr,grdtlsptr,*currentptr);
//DeadCode JIM 13Oct00 			grdtlsptr[0]=othergr;

			parent->RefreshData(2);
			Refresh();
		}
	}
	
}

void LWDiaryDetails::OnClickedRbuttonNext() 
{
	*currentptr = *currentptr + 1;
	Refresh();
	
}

void LWDiaryDetails::OnClickedRbuttonPrev() 
{
	*currentptr = *currentptr - 1;
	Refresh();
	
}

void LWDiaryDetails::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(lwdiary_timer);
}

void LWDiaryDetails::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==lwdiary_timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}
