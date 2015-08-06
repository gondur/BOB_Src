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

// RowanDialog: // PltLogBk.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include	"sqddiary.h"
#include "PltLogBk.h"
#include "mytime.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// PilotLogBook dialog


RDialog*	PilotLogBook::Make()
{
	FileNum artnum;

	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
  		artnum = FIL_D_GRUPPEN_LOGBOOK;
	else
		artnum = FIL_D_RAFLOGBOOK;


	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(artnum,new PilotLogBook())
			);
}


PilotLogBook::PilotLogBook(CWnd* pParent /*=NULL*/)
	: RowanDialog(PilotLogBook::IDD, pParent)
{
	//{{AFX_DATA_INIT(PilotLogBook)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void PilotLogBook::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PilotLogBook)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	DDX_Control(pDX, IDC_NAME, m_IDC_NAME);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
}


BEGIN_MESSAGE_MAP(PilotLogBook, CDialog)
	//{{AFX_MSG_MAP(PilotLogBook)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PilotLogBook message handlers
void PilotLogBook::RAFRefreshList()
{
		CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(70);            //MIKE
	//rlistbox->AddColumn(60);										  //RDH 02/06/99
	//rlistbox->AddColumn(80);										  //RDH 02/06/99
	//rlistbox->AddColumn(90);										  //RDH 02/06/99
	//rlistbox->AddColumn(280);
	//rlistbox->AddColumn(45);										  //RDH 02/06/99
//DeadCode JIM 18Oct00 	rlistbox->AddColumn(30);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(DATE),0);
	rlistbox->AddString(RESSTRING(HOUR),1);
	rlistbox->AddString(RESSTRING(ACTYPE),2);
	rlistbox->AddString(RESSTRING(DUTY),3);
	rlistbox->AddString(RESSTRING(REMARKS),4);
	rlistbox->AddString(RESSTRING(CLAIMS),5);
//DeadCode JIM 18Oct00 	rlistbox->AddString(RESSTRING(FLYINGHOURS),6);

	Diary::Player*	pptr;
//TEMPCODE RDH 05/04/00 	//###temp
//TEMPCODE RDH 05/04/00 	int pack=0;
//TEMPCODE RDH 05/04/00 	while (	pack < Profile::MAX_PACKS)
//TEMPCODE RDH 05/04/00 	{
//TEMPCODE RDH 05/04/00 		if (Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
//TEMPCODE RDH 05/04/00 		{
//TEMPCODE RDH 05/04/00 		 	Profile& pk = Todays_Packages.pack[pack];
//TEMPCODE RDH 05/04/00 			if  (pk.attackmethod < Profile::AM_LWPACKS)
//TEMPCODE RDH 05/04/00 				break;
//TEMPCODE RDH 05/04/00 		}
//TEMPCODE RDH 05/04/00 		pack++;
//TEMPCODE RDH 05/04/00 	}
//TEMPCODE RDH 05/04/00 	RDialog::m_pView->SetHiLightInfo(pack, 0,UID_Null);
//TEMPCODE RDH 05/04/00 
//TEMPCODE RDH 05/04/00 	if (Todays_Packages[pack][0].diaryentry == -1)		//RJS 27Jan00
//TEMPCODE RDH 05/04/00 			Squad_Diary.CreateEntry(Todays_Packages,pack);	//RJS 27Jan00
//TEMPCODE RDH 05/04/00 
//TEMPCODE RDH 05/04/00 	Squad_Diary.CreatePlayer(Todays_Packages);					//RJS 27Jan00
//TEMPCODE RDH 05/04/00 	pptr = Squad_Diary.GetFirstPlayer();
//TEMPCODE RDH 05/04/00 	pptr->howendedmission = EFS_LandedOK;
//TEMPCODE RDH 05/04/00 	//###end temp

	pptr = Squad_Diary.GetFirstPlayer();


	while(pptr)	
	{
		SquadronBase*	squad =	Squad_Diary.GetSquadron(pptr);
		if (squad)
		{
			Diary::RaidGroup* raidgroup;
			Diary::RaidPack* raidpack;
			Diary::Intercept* intercept;

			intercept = Squad_Diary.GetIntercept(squad);
			raidgroup = Squad_Diary.GetRaidGroup(intercept);
			if (raidgroup)
			{
				raidpack = Squad_Diary.GetRaidPack(raidgroup);
				if (raidpack)
				{
					//date
		 			rlistbox->AddString(GetDateName(raidpack->date * SECSPERDAY, DATE_LONG),0);

					int	t;												//RJS 12Nov00
					if (intercept->intercepttime)						//RJS 12Nov00
						t = intercept->intercepttime;					//RJS 12Nov00
					else												//RJS 12Nov00
						t = intercept->takeofftime;						//RJS 12Nov00

					t /= 60;											//RJS 12Nov00

					rlistbox->AddString(CSprintf("%02i:%02i",t/60,t%60),1);

					Squadron* sq  = Node_Data[(SquadNum)squad->squadnum];
					rlistbox->AddString(RESLIST(SPIT_A, sq->AcType()),2);

					//mission
 					int cnt = int(!intercept->waspatrolinitially);
					rlistbox->AddString(RESLIST(AM_PATROL, cnt),3);

					CString	remarkstring;								//RJS 9Nov00
																		//RJS 9Nov00
					pptr->DamageReport(remarkstring);					//RJS 9Nov00
																		//RJS 9Nov00
					rlistbox->AddString(remarkstring,4);				//RJS 9Nov00


 					int kills = 0;
					for (int k = 0; k < 6; k++)
							kills += pptr->kills[k];
 					rlistbox->AddString(CSprintf("%i", kills),5);
 
 
				}
			}
 

		}
		pptr = Squad_Diary.GetNextPlayerAll(pptr);



	}


}

void PilotLogBook::LWRefreshList()
{
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00 	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(70);
	//rlistbox->AddColumn(60);										  //RDH 02/06/99
	//rlistbox->AddColumn(80);										  //RDH 02/06/99
	//rlistbox->AddColumn(90);										  //RDH 02/06/99
	//rlistbox->AddColumn(280);
	//rlistbox->AddColumn(45);										  //RDH 02/06/99
//DeadCode JIM 18Oct00 	rlistbox->AddColumn(30);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(DATE),0);
	rlistbox->AddString(RESSTRING(HOUR),1);
	rlistbox->AddString(RESSTRING(ACTYPE),2);
	rlistbox->AddString(RESSTRING(DUTY),3);
	rlistbox->AddString(RESSTRING(REMARKS),4);
	rlistbox->AddString(RESSTRING(CLAIMS),5);
//DeadCode JIM 18Oct00 	rlistbox->AddString(RESSTRING(FLYINGHOURS),6);

	Diary::Player*	pptr;


//TEMPCODE RDH 05/04/00 	//###temp
//TEMPCODE RDH 05/04/00 	int pack=0;
//TEMPCODE RDH 05/04/00 	while (	pack < Profile::MAX_PACKS)
//TEMPCODE RDH 05/04/00 	{
//TEMPCODE RDH 05/04/00 		if (Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
//TEMPCODE RDH 05/04/00 		{
//TEMPCODE RDH 05/04/00 		 	Profile& pk = Todays_Packages.pack[pack];
//TEMPCODE RDH 05/04/00 			if  (pk.attackmethod >= Profile::AM_LWPACKS)
//TEMPCODE RDH 05/04/00 				break;
//TEMPCODE RDH 05/04/00 		}
//TEMPCODE RDH 05/04/00 		pack++;
//TEMPCODE RDH 05/04/00 	}
//TEMPCODE RDH 05/04/00 	RDialog::m_pView->SetHiLightInfo(pack, 0,UID_Null);
//TEMPCODE RDH 05/04/00 
//TEMPCODE RDH 05/04/00 	if (Todays_Packages[pack][0].diaryentry == -1)		//RJS 27Jan00
//TEMPCODE RDH 05/04/00 			Squad_Diary.CreateEntry(Todays_Packages,pack);	//RJS 27Jan00
//TEMPCODE RDH 05/04/00 
//TEMPCODE RDH 05/04/00 	Squad_Diary.CreatePlayer(Todays_Packages);					//RJS 27Jan00
//TEMPCODE RDH 05/04/00 	pptr = Squad_Diary.GetFirstPlayer();
//TEMPCODE RDH 05/04/00 	pptr->howendedmission = EFS_LandedOK;
//TEMPCODE RDH 05/04/00 	//###end temp

	pptr = Squad_Diary.GetFirstPlayer();


	while(pptr)	
	{
		SquadronBase*	squad =	Squad_Diary.GetSquadron(pptr);
		if (squad)
		{
			Diary::RaidGroup* raidgroup;
			Diary::RaidPack* raidpack;
			raidgroup = Squad_Diary.GetRaidGroup(squad);
			if (raidgroup)
			{
				raidpack = Squad_Diary.GetRaidPack(raidgroup);
				if (raidpack)
				{
					//date
		 			rlistbox->AddString(GetDateName(raidpack->date * SECSPERDAY, DATE_LONG),0);
					int t=raidgroup->targettime/60;
 					rlistbox->AddString(CSprintf("%02i:%02i",t/60,t%60),1);

					Squadron* sq  = Node_Data[(SquadNum)squad->squadnum];
					rlistbox->AddString(RESLIST(SPIT_A, sq->AcType()),2);

					rlistbox->AddString(RESLIST(MT_RAID, raidgroup->misstype),3);

					CString	remarkstring;								//RJS 9Nov00
																		//RJS 9Nov00
					pptr->DamageReport(remarkstring);					//RJS 9Nov00
																		//RJS 9Nov00
					rlistbox->AddString(remarkstring,4);				//RJS 9Nov00

//DeadCode RJS 9Nov00 					bool acdamage = false;
//DeadCode RJS 9Nov00 					int maxdam = 0, maxdamtype;
//DeadCode RJS 9Nov00 					for(int i = 0; i < DIARY_MAXDAMAGE; i++)
//DeadCode RJS 9Nov00 						if (pptr->specificdamage[i] >50)
//DeadCode RJS 9Nov00 						{
//DeadCode RJS 9Nov00 							acdamage = true;
//DeadCode RJS 9Nov00 							if (pptr->specificdamage[i] > maxdam)
//DeadCode RJS 9Nov00 							{
//DeadCode RJS 9Nov00 								maxdam = pptr->specificdamage[i];
//DeadCode RJS 9Nov00 								maxdamtype = i;
//DeadCode RJS 9Nov00 							}
//DeadCode RJS 9Nov00 						}
//DeadCode RJS 9Nov00 
//DeadCode RJS 9Nov00 					if (	acdamage									//RJS 9Nov00
//DeadCode RJS 9Nov00 						&&	(pptr->howendedmission < EFS_BadCrashAF)	)	//RJS 9Nov00
//DeadCode RJS 9Nov00 					{
//DeadCode RJS 9Nov00 						if (maxdam < 200)
//DeadCode RJS 9Nov00 							rlistbox->AddString(RESLIST(DIARYDAM_LEFTWING, maxdamtype),4);	//RJS 9Nov00
//DeadCode RJS 9Nov00 						else
//DeadCode RJS 9Nov00 							rlistbox->AddString(RESLIST(DIARYDEST_LEFTWING, maxdamtype),4);	//RJS 9Nov00
//DeadCode RJS 9Nov00 
//DeadCode RJS 9Nov00 					}else
//DeadCode RJS 9Nov00 						rlistbox->AddString(RESLIST(EFS_NULL, pptr->howendedmission),4);


					int kills = pptr->kills[0] + pptr->kills[1];
 					rlistbox->AddString(CSprintf("%i", kills),5);
 
 
				}
			}
 

		}
		pptr = Squad_Diary.GetNextPlayerAll(pptr);



	}

}


//DEADCODE RDH 24/02/00 		//###temp fix
//DEADCODE RDH 24/02/00  		if (!squad)
//DEADCODE RDH 24/02/00 		{
//DEADCODE RDH 24/02/00 			int squadnum = -1;
//DEADCODE RDH 24/02/00 			int pack=0;
//DEADCODE RDH 24/02/00 			while (	(squadnum == -1)	&&	(pack < Profile::MAX_PACKS))
//DEADCODE RDH 24/02/00 			{
//DEADCODE RDH 24/02/00 				if (Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
//DEADCODE RDH 24/02/00 				{
//DEADCODE RDH 24/02/00 				 	Profile& pk = Todays_Packages.pack[pack];
//DEADCODE RDH 24/02/00 					if  (pk.attackmethod >= Profile::AM_LWPACKS)
//DEADCODE RDH 24/02/00 					{
//DEADCODE RDH 24/02/00 						int i=0;
//DEADCODE RDH 24/02/00 						while (	(squadnum == -1)	&&	(i < pk.squadlist))
//DEADCODE RDH 24/02/00 						{
//DEADCODE RDH 24/02/00 							squadnum = pk[i].squadnum;
//DEADCODE RDH 24/02/00 							i++;
//DEADCODE RDH 24/02/00 						}
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 					}
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 				}
//DEADCODE RDH 24/02/00 				pack++;
//DEADCODE RDH 24/02/00 			}
//DEADCODE RDH 24/02/00 			squad = Squad_Diary.FindLast((SquadNum)squadnum);
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 		}
//DEADCODE RDH 24/02/00 		//##end temp
//DEADCODE RDH 24/02/00 





BOOL PilotLogBook::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
//DEADCODE RDH 24/02/00 	rlistbox->AddString("Aug 8th",0);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("12:45",1);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("Spitfire",2);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("Patrol",3);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("Beachy Head. No combat",4);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("0",5);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("1",6);
//DEADCODE RDH 24/02/00 
//DEADCODE RDH 24/02/00 	rlistbox->AddString("Aug 9th",0);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("12:45",1);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("Spitfire",2);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("Intercept",3);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("Croydon. 200 + Ju88.",4);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("0",5);
//DEADCODE RDH 24/02/00 	rlistbox->AddString("1",6);

	CREdit* edit=GETDLGITEM(IDC_NAME);
	edit->SetCaption(MMC.PlayerName);

	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	{
		LWRefreshList();
	}else
	{
		RAFRefreshList();
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_EVENTSINK_MAP(PilotLogBook, CDialog)
    //{{AFX_EVENTSINK_MAP(PilotLogBook)
	ON_EVENT(PilotLogBook, IDC_RLISTBOXCTRL1, 1 /* Select */, OnSelectRlistboxctrl1, VTS_I4 VTS_I4)
	ON_EVENT(PilotLogBook, IDC_NAME, 2 /* TextChanged */, OnTextChangedName, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void PilotLogBook::OnSelectRlistboxctrl1(long row, long column) 
{
#ifndef	BOB_DEMO_VER
	
	Diary::Player*	pptr = Squad_Diary.GetFirstPlayer();

	if (row > 0)
	{
 		row--;
		int index = -1;													//RJS 13Nov00
		while(pptr && (index != row))
		{
			SquadronBase*	squad =	Squad_Diary.GetSquadron(pptr);
			if (squad)
			{
				Diary::RaidGroup* raidgroup;
				Diary::RaidPack* raidpack;
				raidgroup = Squad_Diary.GetRaidGroup(squad);
				if (raidgroup)
				{
					raidpack = Squad_Diary.GetRaidPack(raidgroup);
					if (raidpack)
					{
						index++;	  //sets the count to 1 when something is found!
 
					}
				}
 

			}
			pptr = Squad_Diary.GetNextPlayerAll(pptr);



		}

		if (index == row)
			TitleBarPtr().OpenCombatReport(index+1, true);				//RJS 13Nov00
	}	
#endif
}

void PilotLogBook::OnTextChangedName(LPTSTR text) 
{
	CREdit* edit=GETDLGITEM(IDC_NAME);
	trunc(text,PLAYERNAMELEN - 1);	

 	strcpy(Save_Data.CommsPlayerName,text);
 	strcpy(MMC.PlayerName,text);
}
