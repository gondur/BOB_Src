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

// RowanDialog: // RAFCombt.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFCombt.h"
#include "mytime.h"
#include	"rchatter.h"						//RJS 18May00
#include "winmove.h"


#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
/////////////////////////////////////////////////////////////////////////////
// RAFCombat dialog


RDialog*	RAFCombat::Make(int index, bool date)
{
  	FileNum artnum;

	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
  		artnum = FIL_D_LWCOMBAT;
	else
		artnum = FIL_D_RAFCOMBAT;


	

	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(artnum,new RAFCombat(index, date))
			);
}


RAFCombat::RAFCombat(int index, bool date, CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFCombat::IDD, pParent)
{
	entry = index;
	datereq = date;
	//{{AFX_DATA_INIT(RAFCombat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void RAFCombat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFCombat)
	DDX_Control(pDX, IDC_RSTATICCRDATE, m_IDC_RSTATICCRDATE);
	DDX_Control(pDX, IDC_RSTATICENEMYAC, m_IDC_RSTATICENEMYAC);
	DDX_Control(pDX, IDC_RSTATICENEMYCONC, m_IDC_RSTATICENEMYCONC);
	DDX_Control(pDX, IDC_RSTATICFLIGHTSQUAD, m_IDC_RSTATICFLIGHTSQUAD);
	DDX_Control(pDX, IDC_RSTATICHTENEMY, m_IDC_RSTATICHTENEMY);
	DDX_Control(pDX, IDC_RSTATICOURAC, m_IDC_RSTATICOURAC);
	DDX_Control(pDX, IDC_RSTATICOURPERS, m_IDC_RSTATICOURPERS);
	DDX_Control(pDX, IDC_RSTATICPLACEATTK, m_IDC_RSTATICPLACEATTK);
	DDX_Control(pDX, IDC_RSTATICTIMEATTK, m_IDC_RSTATICTIMEATTK);
	DDX_Control(pDX, IDC_RSTATICTYPEENEMYAC, m_IDC_RSTATICTYPEENEMYAC);
	DDX_Control(pDX, IDC_NAME, m_IDC_NAME);
	DDX_Control(pDX, IDC_RSTATICUNIT, m_IDC_RSTATICUNIT);
	DDX_Control(pDX, IDJ_TITLE, m_IDJ_TITLE);
	DDX_Control(pDX, IDC_RSTATICCTRL24, m_IDC_RSTATICCTRL24);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(RAFCombat, CDialog)
	//{{AFX_MSG_MAP(RAFCombat)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFCombat message handlers



void RAFCombat::RAFRefresh()
{

	CRStatic*   s;

	s = GETDLGITEM(IDC_RSTATICUNIT);
	s->SetString(RESSTRING(SQUADRON));

	Diary::Player*	pptr = Squad_Diary.GetFirstPlayer();
	Diary::Intercept* intercept;

	Diary::RaidGroup* raidgroup;
	Diary::RaidPack* raidpack;
	SquadronBase*	squad;

	int index = 0;
	while(	(pptr)	&&	(index != entry))
	{
		squad =	Squad_Diary.GetSquadron(pptr);
		if (squad)
		{
			intercept = Squad_Diary.GetIntercept(squad);
			raidgroup = Squad_Diary.GetRaidGroup(intercept);
			if (raidgroup)
			{
				raidpack = Squad_Diary.GetRaidPack(raidgroup);
				if (raidpack)
					index++;
			}
 
		}
		if (index != entry)
			pptr = Squad_Diary.GetNextPlayerAll(pptr);
	}

	if (pptr)
	{
		squad =	Squad_Diary.GetSquadron(pptr);
		if (squad)
		{
			intercept = Squad_Diary.GetIntercept(squad);
			raidgroup = Squad_Diary.GetRaidGroup(intercept);
			if (raidgroup)
			{

				CRStatic*   s;
				CRStatic*   ss;


				raidpack = Squad_Diary.GetRaidPack(raidgroup);


				s = GETDLGITEM(IDC_RSTATICCRDATE);
				ss = GETDLGITEM(IDC_RSTATICCTRL24);
				if (datereq)
				{
					s->ShowWindow(true);
					ss->ShowWindow(true);
					s->SetString(GetDateName(raidpack->date * SECSPERDAY, DATE_LONG));
				}else
				{
					s->ShowWindow(false);
					ss->ShowWindow(false);
				}


				s = GETDLGITEM(IDC_RSTATICFLIGHTSQUAD);
				Squadron* sq = &Node_Data[(SquadNum)squad->squadnum];
				CString name = sq->FullName() ;
				s->SetString(name);
				StatsPerType	counts[6]={PT_SPIT_A};

//DeadCode JIM 23Oct00 				for (int cnt=0; cnt < (PT_HE59 - PT_GER_FLYABLE); cnt++)
//DeadCode JIM 23Oct00 				{
//DeadCode JIM 23Oct00 					totalacseen [cnt] = 0;
//DeadCode JIM 23Oct00 					totalackilled [cnt] = 0;
//DeadCode JIM 23Oct00 				}
				int totaltotalacseen = 0;

				Diary::RaidGroup*	lwraidgroup = Squad_Diary.GetFirstRaidGroup(raidpack);

				while(lwraidgroup)
				{
					Diary::Gruppen* gr = Squad_Diary.GetFirstSquadron(lwraidgroup);
					while (gr)
					{
						Squadron* sq  = Node_Data[(SquadNum)gr->squadnum];
						int index = (int)sq->AcType() - PT_GER_FLYABLE;
						if (	(index >=0)	&&	(index < (PT_HE59 - PT_GER_FLYABLE)) && gr->noaclaunched)
						{
						
							counts[index][0]=sq->AcType();
							counts[index][1]+=gr->noaclaunched;
							counts[index][2]+= gr->numlosses;

							totaltotalacseen += gr->noaclaunched;
						}

						gr = Squad_Diary.GetNextSquadron(gr);
					}
					lwraidgroup = Squad_Diary.GetNextRaidGroup(lwraidgroup);
				}
				{for (int i=0;i<6;i++)
					counts[i][3]=pptr->kills[i];						//RJS 30Oct00
				}
				s = GETDLGITEM(IDC_RSTATICENEMYAC);
				if (totaltotalacseen)
					s->SetString(CSprintf("%i", totaltotalacseen));
				else
					s->SetString(RESSTRING(NOAIRCRAFT));

				s = GETDLGITEM(IDC_RSTATICTYPEENEMYAC);
				s->SetString(EnemyReport(counts, 1,0));
				s = GETDLGITEM(IDC_RSTATICENEMYCONC);
				s->SetString(EnemyReport(counts, 3,2));

				if (intercept)
				{
					s = GETDLGITEM(IDC_RSTATICTIMEATTK);
					int t=intercept->intercepttime/60;
					if (t)
						s->SetString(CSprintf("%02i:%02i",t/60,t%60));
					else
						s->SetString("");
 
					s = GETDLGITEM(IDC_RSTATICPLACEATTK);
					CString	placename;
					if (intercept->interceptloc)
						_Radio.GetLocationString(placename,intercept->interceptloc);
					else
						placename = "";
					s->SetString(placename);

					s = GETDLGITEM(IDC_RSTATICHTENEMY);
					int alt = (intercept->interceptheight*10)/Save_Data.alt.mediummm;
					alt = 100*((alt + 50)/100);
					CString altstring = CSprintf("%i%s",alt,LoadResString(Save_Data.alt.mediumabbr));
					if (alt)						//RJS 18Oct00
						s->SetString(altstring);
					else
						s->SetString("");
				}else
				{
					s = GETDLGITEM(IDC_RSTATICTIMEATTK);
					s->SetString("");
					s = GETDLGITEM(IDC_RSTATICPLACEATTK);
					s->SetString("");
					s = GETDLGITEM(IDC_RSTATICHTENEMY);
					s->SetString("");
				}
				CString personnel;
				personnel = CSprintf("%i ", squad->numpilotslost);
				if (squad->numpilotslost == 0)
					personnel = RESSTRING(NOAIRCRAFT);
				else if (squad->numpilotslost == 1)
					personnel = personnel + RESSTRING(PILOT);
				else
					personnel = personnel + RESSTRING(PILOTS);

				s = GETDLGITEM(IDC_RSTATICOURPERS);
				s->SetString(personnel);


				s = GETDLGITEM(IDC_RSTATICOURAC);
				CString acloss;
				acloss = CSprintf("%i ", squad->numlosses);
				if (squad->numlosses == 0)
					acloss = RESSTRING(NOAIRCRAFT);
				else if (squad->numlosses == 1)
					acloss = acloss + RESSTRING(AIRCRAFT);
				else
					acloss = acloss + RESSTRING(AIRCRAFT);
			   	s->SetString(acloss);

//DeadCode RDH 22Aug00 				bool acdamage = false;
//DeadCode RDH 22Aug00 				int maxdam = 0, maxdamtype;
//DeadCode RDH 22Aug00 				int elementsdestroyed = 0;
//DeadCode RDH 22Aug00 				for(int i = 0; i < DIARY_MAXDAMAGE; i++)
//DeadCode RDH 22Aug00 					if (pptr->specificdamage[i] >50)
//DeadCode RDH 22Aug00 					{
//DeadCode RDH 22Aug00 						acdamage = true;
//DeadCode RDH 22Aug00 						if (pptr->specificdamage[i] > maxdam)
//DeadCode RDH 22Aug00 						{
//DeadCode RDH 22Aug00 							maxdam = pptr->specificdamage[i];
//DeadCode RDH 22Aug00 							maxdamtype = i;
//DeadCode RDH 22Aug00 						}
//DeadCode RDH 22Aug00 						if (pptr->specificdamage[i] > 250)
//DeadCode RDH 22Aug00 							elementsdestroyed++;
//DeadCode RDH 22Aug00 					}
//DeadCode RDH 22Aug00 				if (elementsdestroyed > 1)
//DeadCode RDH 22Aug00 					s->SetString(RESSTRING(WRITEOFF));
//DeadCode RDH 22Aug00 				else if 	(acdamage)
//DeadCode RDH 22Aug00 				{
//DeadCode RDH 22Aug00 					if (maxdam < 200)
//DeadCode RDH 22Aug00 						s->SetString(RESLIST(DIARYDAM_LEFTWING, pptr->specificdamage[maxdamtype]));
//DeadCode RDH 22Aug00 					else
//DeadCode RDH 22Aug00 						s->SetString(RESLIST(DIARYDEST_LEFTWING, pptr->specificdamage[maxdamtype]));
//DeadCode RDH 22Aug00 				}else
//DeadCode RDH 22Aug00 					s->SetString(RESSTRING(NOAIRCRAFT));
//DeadCode RDH 22Aug00 

				CREdit* editbox;
				editbox=GETDLGITEM(IDC_NAME);
				int	size =		Squad_Diary.DiaryEditable(pptr);	//returns max length
				if (size)
				{
					Squad_Diary.FillEndOfDayReport(pptr);					//RJS 29Oct00

					editbox->SetEnabled(true);
				}
				else
					editbox->SetEnabled(false);

				editbox->SetCaption(Squad_Diary.GetDiaryText(pptr));
			}
		}

	}

}



void RAFCombat::LWRefresh()
{

	CRStatic*   s;

	s = GETDLGITEM(IDC_RSTATICUNIT);
	s->SetString(RESSTRING(GRUPPE));

	Diary::Player*	pptr = Squad_Diary.GetFirstPlayer();

	Diary::RaidGroup* raidgroup;
	Diary::RaidPack* raidpack;
	SquadronBase*	squad;

	int index = 0;
	while(	(pptr)	&&	(index != entry))
	{
		squad =	Squad_Diary.GetSquadron(pptr);
		if (squad)
		{
			raidgroup = Squad_Diary.GetRaidGroup(squad);
			if (raidgroup)
			{
				raidpack = Squad_Diary.GetRaidPack(raidgroup);
				if (raidpack)
					index++;
			}
 
		}
		if (index != entry)
			pptr = Squad_Diary.GetNextPlayerAll(pptr);
	}

	if (pptr)
	{
		squad =	Squad_Diary.GetSquadron(pptr);
		if (squad)
		{
			raidgroup = Squad_Diary.GetRaidGroup(squad);
			if (raidgroup)
			{
				raidpack = Squad_Diary.GetRaidPack(raidgroup);
				if (raidpack)
				{
					CRStatic*   s;

					s = GETDLGITEM(IDC_RSTATICCRDATE);
					s->SetString(GetDateName(raidpack->date * SECSPERDAY, DATE_LONG));	//RJS 18Oct00


					s = GETDLGITEM(IDC_RSTATICFLIGHTSQUAD);
					Squadron* sq = &Node_Data[(SquadNum)squad->squadnum];
					CString name = sq->FullName() + "/";
					name = name + sq->SubName();
					s->SetString(name);

				
					int hurrseen = 0, spitseen = 0, hurrkilled = 0, spitkilled = 0;

					Diary::Intercept* intercept = 	Squad_Diary.GetFirstIntercept(raidgroup);
					StatsPerType	counts[6]={PT_SPIT_A};
					int totalseen=0;
					while(intercept)
					{
						Diary::Squadron* othersq = Squad_Diary.GetFirstSquadron(intercept);
						while (othersq)
						{
							if (othersq->noaclaunched)
							{
								Squadron* sq  = Node_Data[(SquadNum)othersq->squadnum];
								int	actype=sq->AcType();
								counts[actype/2][0]=actype;
								actype/=2;
								counts[actype][2]+=othersq->numlosses;	//RJS 10Nov00
								counts[actype][1]+=othersq->noaclaunched;	//RJS 10Nov00
								totalseen+=othersq->noaclaunched;
							}
							othersq = Squad_Diary.GetNextSquadron(othersq);
						}


						intercept = Squad_Diary.GetNextIntercept(intercept);
					}
					counts[0][3]=pptr->kills[0];
					counts[1][3]=pptr->kills[1];
					counts[2][3]=pptr->kills[2];
					s = GETDLGITEM(IDC_RSTATICENEMYAC);
					if (totalseen)
						s->SetString(CSprintf("%i", totalseen));
					else
						s->SetString(RESSTRING(NOAIRCRAFT));

					s = GETDLGITEM(IDC_RSTATICTYPEENEMYAC);
					s->SetString(EnemyReport(counts,1,0));
					s = GETDLGITEM(IDC_RSTATICENEMYCONC);
					s->SetString(EnemyReport(counts,3,2));

					intercept = 	Squad_Diary.GetFirstIntercept(raidgroup);	//RJS 18Oct00
					if (intercept)
					{
//DeadCode RJS 18Oct00 						s = GETDLGITEM(IDC_RSTATICTIMEATTK);
//DeadCode RJS 18Oct00 						int t=intercept->intercepttime/60;
//DeadCode RJS 18Oct00 						s->SetString(CSprintf("%02i:%02i",t/60,t%60));
//DeadCode RJS 18Oct00  
//DeadCode RJS 18Oct00 						s = GETDLGITEM(IDC_RSTATICPLACEATTK);
//DeadCode RJS 18Oct00 						s->SetString("Over Dover");
//DeadCode RJS 18Oct00 
//DeadCode RJS 18Oct00 						s = GETDLGITEM(IDC_RSTATICHTENEMY);
//DeadCode RJS 18Oct00 						int alt = (intercept->interceptheight*10)/Save_Data.alt.mediummm;
//DeadCode RJS 18Oct00 						alt = 100*((alt + 50)/100);
//DeadCode RJS 18Oct00 						CString altstring = CSprintf("%i%s",alt,LoadResString(Save_Data.alt.mediumabbr));
//DeadCode RJS 18Oct00 						s->SetString(altstring);
						s = GETDLGITEM(IDC_RSTATICTIMEATTK);			//RJS 18Oct00
						int t=intercept->intercepttime/60;
						if (t)
							s->SetString(CSprintf("%02i:%02i",t/60,t%60));
						else
							s->SetString("");
 
						s = GETDLGITEM(IDC_RSTATICPLACEATTK);
						CString	placename;
						if (intercept->interceptloc)
							_Radio.GetLocationString(placename,intercept->interceptloc);
						else
							placename = "";
						s->SetString(placename);

						s = GETDLGITEM(IDC_RSTATICHTENEMY);
						int alt = (intercept->interceptheight*10)/Save_Data.alt.mediummm;
						alt = 100*((alt + 50)/100);
						CString altstring = CSprintf("%i%s",alt,LoadResString(Save_Data.alt.mediumabbr));
						if (alt)										//RJS 18Oct00
							s->SetString(altstring);
						else
							s->SetString("");
					}else
					{
						s = GETDLGITEM(IDC_RSTATICTIMEATTK);
						s->SetString("");
						s = GETDLGITEM(IDC_RSTATICPLACEATTK);
						s->SetString("");
						s = GETDLGITEM(IDC_RSTATICHTENEMY);
						s->SetString("");
					}
					CString personnel;
					personnel = CSprintf("%i ", squad->numpilotslost);
					if (squad->numpilotslost == 0)
						personnel = RESSTRING(NOAIRCRAFT);
					else if (squad->numpilotslost == 1)
						personnel = personnel + RESSTRING(PILOT);
					else
						personnel = personnel + RESSTRING(PILOTS);

					s = GETDLGITEM(IDC_RSTATICOURPERS);
					s->SetString(personnel);


					s = GETDLGITEM(IDC_RSTATICOURAC);
					CString acloss;
					acloss = CSprintf("%i ", squad->numlosses);
					if (squad->numlosses == 0)
						acloss = RESSTRING(NOAIRCRAFT);
					else if (squad->numlosses == 1)
						acloss = acloss + RESSTRING(AIRCRAFT);
					else
						acloss = acloss + RESSTRING(AIRCRAFT);
				   	s->SetString(acloss);

//DeadCode RDH 22Aug00 					bool acdamage = false;
//DeadCode RDH 22Aug00 					int maxdam = 0, maxdamtype;
//DeadCode RDH 22Aug00 					int elementsdestroyed = 0;
//DeadCode RDH 22Aug00 					for(int i = 0; i < DIARY_MAXDAMAGE; i++)
//DeadCode RDH 22Aug00 						if (pptr->specificdamage[i] >50)
//DeadCode RDH 22Aug00 						{
//DeadCode RDH 22Aug00 							acdamage = true;
//DeadCode RDH 22Aug00 							if (pptr->specificdamage[i] > maxdam)
//DeadCode RDH 22Aug00 							{
//DeadCode RDH 22Aug00 								maxdam = pptr->specificdamage[i];
//DeadCode RDH 22Aug00 								maxdamtype = i;
//DeadCode RDH 22Aug00 							}
//DeadCode RDH 22Aug00 							if (pptr->specificdamage[i] > 250)
//DeadCode RDH 22Aug00 								elementsdestroyed++;
//DeadCode RDH 22Aug00 						}
//DeadCode RDH 22Aug00 					if (elementsdestroyed > 1)
//DeadCode RDH 22Aug00 						s->SetString(RESSTRING(WRITEOFF));
//DeadCode RDH 22Aug00 					else if 	(acdamage)
//DeadCode RDH 22Aug00 					{
//DeadCode RDH 22Aug00 						if (maxdam < 200)
//DeadCode RDH 22Aug00 							s->SetString(RESLIST(DIARYDAM_LEFTWING, pptr->specificdamage[maxdamtype]));
//DeadCode RDH 22Aug00 						else
//DeadCode RDH 22Aug00 							s->SetString(RESLIST(DIARYDEST_LEFTWING, pptr->specificdamage[maxdamtype]));
//DeadCode RDH 22Aug00 					}else
//DeadCode RDH 22Aug00 						s->SetString(RESSTRING(NOAIRCRAFT));

					CREdit* editbox;
					editbox=GETDLGITEM(IDC_NAME);
					int	size =		Squad_Diary.DiaryEditable(pptr);	//returns max length
					if (size)
					{
						Squad_Diary.FillEndOfDayReport(pptr);				//RJS 29Oct00

						editbox->SetEnabled(true);
					}
					else
						editbox->SetEnabled(false);

					editbox->SetCaption(Squad_Diary.GetDiaryText(pptr));

				}
			}
		}

	}

}
//DeadCode JIM 23Oct00 CString RAFCombat::EnemyReport(int hurr, int spit, bool shownumbers)
//DeadCode JIM 23Oct00 {
//DeadCode JIM 23Oct00 	CString type= "";
//DeadCode JIM 23Oct00 	if (hurr)
//DeadCode JIM 23Oct00 	{
//DeadCode JIM 23Oct00 		if (shownumbers)
//DeadCode JIM 23Oct00 			type = CSprintf("%i ", hurr);
//DeadCode JIM 23Oct00 		type = type + RESSTRING(HURRICANES);
//DeadCode JIM 23Oct00 	}
//DeadCode JIM 23Oct00 	if (spit)
//DeadCode JIM 23Oct00 	{
//DeadCode JIM 23Oct00 		if (type != "")
//DeadCode JIM 23Oct00 			type = type + " and ";
//DeadCode JIM 23Oct00 		if (shownumbers)
//DeadCode JIM 23Oct00 			type = type + CSprintf("%i ", spit);
//DeadCode JIM 23Oct00 		type= type + RESSTRING(SPITFIRES);
//DeadCode JIM 23Oct00 	}
//DeadCode JIM 23Oct00 	if (type == "")
//DeadCode JIM 23Oct00 		type = RESSTRING(NOAIRCRAFT);
//DeadCode JIM 23Oct00 	return (type);
//DeadCode JIM 23Oct00 }
CString RAFCombat::EnemyReport(StatsPerType* acarray,int c0,int c1)
{
	CString type= "";
	int totaltypes = 0;
	for (int i =0; i < 6; i++)
		if (acarray[i][c1] || acarray[i][c0])
			totaltypes++;
	if (totaltypes)
		for (int i =0; i < 6; i++)
		{
			if (acarray[i][c1] != 0 || acarray[i][c0] != 0)
			{
				if (c0 && c1)
					type += CSprintf("%i/", acarray [i][c0]);
				if (c1)
					type += CSprintf("%i ", acarray [i][c1]);
				type += RESLIST(SPIT_A,acarray[i][0]);
				if (--totaltypes > 1)
					type += ", ";
				else if (totaltypes == 1)
					type += " and ";

			}	

		}
	else
		type = RESSTRING(NOAIRCRAFT);
	return (type);
}



BOOL RAFCombat::OnInitDialog() 
{
		CDialog::OnInitDialog();

    CRButton* title;
    title = GETDLGITEM(IDJ_TITLE);
    title->SetHelpButton(false);

	GETDLGITEM(IDC_NAME)->SetCaption("");
	GETDLGITEM(IDC_NAME)->SetCaption("\b\b\x0C\r");
	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		LWRefresh();
	else
		RAFRefresh();
//DEADCODE RDH 24/02/00 	CDialog::OnInitDialog();
//DEADCODE RDH 24/02/00 	CRStatic*   s;
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICCRDATE);
//DEADCODE RDH 24/02/00 	s->SetString("10th July 1940");
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICFLIGHTSQUAD);
//DEADCODE RDH 24/02/00 	s->SetString("Flight A 56 Sqdn.");
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	int ac = 16;
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICENEMYAC);
//DEADCODE RDH 24/02/00 	s->SetString(CSprintf("%i", ac));
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICTYPEENEMYAC);
//DEADCODE RDH 24/02/00 	s->SetString(RESSTRING(JU88));
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICTIMEATTK);
//DEADCODE RDH 24/02/00 	s->SetString("17:00 hours");
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICPLACEATTK);
//DEADCODE RDH 24/02/00 	s->SetString("Over Dover");
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICHTENEMY);
//DEADCODE RDH 24/02/00 	s->SetString("10,000ft");
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICENEMYCONC);
//DEADCODE RDH 24/02/00 	s->SetString("3 Me109s");
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICENEMYINCONC);
//DEADCODE RDH 24/02/00 	s->SetString("1 Me109s");
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICOURAC);
//DEADCODE RDH 24/02/00 	s->SetString("Tail shredded");
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICOURPERS);
//DEADCODE RDH 24/02/00 	s->SetString("NIL.");
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	s = GETDLGITEM(IDC_RSTATICGUNCAM);
//DEADCODE RDH 24/02/00 	s->SetString("film00");
	
	debrief_timer=SetTimer(DPlay::TIMER_READYROOM,0,NULL); // set sheet up first before starting timer
	_DPlay.SendStatusChange(DPlay::CPS_DEBRIEF);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void RAFCombat::OnOK() 
{
	SaveText();
	CDialog::OnOK();
}
void RAFCombat::PreDestroyPanel()
{
		SaveText();

}
void RAFCombat::SaveText()
{
	Diary::Player*	pptr = Squad_Diary.GetFirstPlayer();

	Diary::RaidGroup* raidgroup;
	Diary::RaidPack* raidpack;
	SquadronBase*	squad;

	int index = 0;
	while(	(pptr)	&&	(index != entry))
	{
		squad =	Squad_Diary.GetSquadron(pptr);
		if (squad)
		{
			raidgroup = Squad_Diary.GetRaidGroup(squad);
			if (raidgroup)
			{
				raidpack = Squad_Diary.GetRaidPack(raidgroup);
				if (raidpack)
					index++;
			}
 
		}
		if (index != entry)
			pptr = Squad_Diary.GetNextPlayerAll(pptr);
	}
	if (pptr)
	{

		CREdit* editbox;
		CString	buffer;

		editbox=GETDLGITEM(IDC_NAME);
		buffer = editbox->GetCaption();

		Squad_Diary.SetDiaryText(pptr, buffer);
	}
}

void RAFCombat::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==debrief_timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}

	CDialog::OnTimer(nIDEvent);
}

void RAFCombat::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(debrief_timer);
}
