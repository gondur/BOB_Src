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

// RowanDialog: // BoBFrag.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "BoBFrag.h"
#include "package.h"
#include "squick1.h"
#include "winmove.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

SLong pselectedsquadron=0;

/////////////////////////////////////////////////////////////////////////////
// BoBFrag dialog
typedef FragScreenBody::ButtonPos	CP_;
FragScreenBody::ButtonPos	FragScreenBody::buttonpos[FragScreenBody::FT_MAX][16]=
{
	{
		{{100,230},0,CP_::CP_LEADER},	{{26,260},0,CP_::CP_OTHER},		{{174,260},0,CP_::CP_OTHER},
		{{440,230},0,CP_::CP_OTHER},	{{366,260},0,CP_::CP_OTHER},	{{514,260},0,CP_::CP_OTHER},
		{{110,300},0,CP_::CP_SECOND},	{{26,330},0,CP_::CP_OTHER},		{{174,330},0,CP_::CP_OTHER},
		{{440,300},0,CP_::CP_OTHER},	{{366,330},0,CP_::CP_OTHER},	{{514,330},0,CP_::CP_OTHER},

	},
	
	{
		{{100,210},0,CP_::CP_LEADER},	{{26,240},0,CP_::CP_OTHER},		{{174,240},0,CP_::CP_OTHER},	{{248,270},0,CP_::CP_OTHER},
		{{440,210},0,CP_::CP_OTHER},	{{366,240},0,CP_::CP_OTHER},	{{514,240},0,CP_::CP_OTHER},	{{588,270},0,CP_::CP_OTHER},
		{{100,280},0,CP_::CP_SECOND},	{{26,310},0,CP_::CP_OTHER},		{{174,310},0,CP_::CP_OTHER},	{{248,340},0,CP_::CP_OTHER},

	},
	
	{
		{{300,230},0,CP_::CP_LEADER},	{{150,240},0,CP_::CP_OTHER},{{450,240},0,CP_::CP_OTHER},	{{0,250},0,CP_::CP_OTHER},	{{600,250},0,CP_::CP_OTHER},
		{{300,280},0,CP_::CP_OTHER},	{{150,290},0,CP_::CP_OTHER},{{450,290},0,CP_::CP_OTHER},	{{0,300},0,CP_::CP_OTHER},	{{600,300},0,CP_::CP_OTHER},
		{{300,330},0,CP_::CP_SECOND},	{{150,340},0,CP_::CP_OTHER},{{450,340},0,CP_::CP_OTHER},	{{0,350},0,CP_::CP_OTHER},	{{600,350},0,CP_::CP_OTHER},
//DEADCODE MS 16/03/00 		{{100,230},0,CP_::CP_LEADER},	{{26,260},0,CP_::CP_OTHER},{{174,260},0,CP_::CP_OTHER},		{{0,290},0,CP_::CP_OTHER},	{{248,290},0,CP_::CP_OTHER},
//DEADCODE MS 16/03/00 		{{440,230},0,CP_::CP_OTHER},	{{366,260},0,CP_::CP_OTHER},{{514,260},0,CP_::CP_OTHER},	{{258,290},0,CP_::CP_OTHER},	{{588,290},0,CP_::CP_OTHER},
//DEADCODE MS 16/03/00 		{{110,300},0,CP_::CP_SECOND},	{{26,330},0,CP_::CP_OTHER},{{174,330},0,CP_::CP_OTHER},		{{0,360},0,CP_::CP_OTHER},	{{248,360},0,CP_::CP_OTHER},

	}
	
	
};
static int	Prefs_Showline=-1,Prefs_Selline=0,Prefs_Selslot=0;
RDialog*	BoBFrag::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new BoBFrag())
			);
}


BoBFrag::BoBFrag(CWnd* pParent /*=NULL*/)
	:	RowanDialog(BoBFrag::IDD, pParent),
		squadinfo(*new FragScreenBody)
{
	//{{AFX_DATA_INIT(BoBFrag)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pselectedsquadron=0;
	squadinfo.acnuminsquad=0;
}
BoBFrag::~BoBFrag()
{
	delete	&squadinfo;
}

void BoBFrag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BoBFrag)
	DDX_Control(pDX, IDC_RLIST_UNITDETAILS, m_IDC_RLIST_UNITDETAILS);
	DDX_Control(pDX, IDC_PLAYERCHAT, m_IDC_PLAYERCHAT);
	DDX_Control(pDX, IDC_RLIST_INCOMING_CHAT, m_IDC_RLIST_INCOMING_CHAT);
	DDX_Control(pDX, IDC_COMBO_UNIT, m_IDC_COMBO_UNIT);
	DDX_Control(pDX, IDC_UNASSIGNFLAG, m_IDC_UNASSIGNFLAG);
	DDX_Control(pDX, IDC_UNASSIGN, m_IDC_UNASSIGN);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_PILOT_0, m_IDC_PILOT_[0]);
	DDX_Control(pDX, IDC_PILOT_1, m_IDC_PILOT_[1]);
	DDX_Control(pDX, IDC_PILOT_10, m_IDC_PILOT_[10]);
	DDX_Control(pDX, IDC_PILOT_11, m_IDC_PILOT_[11]);
	DDX_Control(pDX, IDC_PILOT_12, m_IDC_PILOT_[12]);
	DDX_Control(pDX, IDC_PILOT_13, m_IDC_PILOT_[13]);
	DDX_Control(pDX, IDC_PILOT_14, m_IDC_PILOT_[14]);
	DDX_Control(pDX, IDC_PILOT_2, m_IDC_PILOT_[2]);
	DDX_Control(pDX, IDC_PILOT_3, m_IDC_PILOT_[3]);
	DDX_Control(pDX, IDC_PILOT_4, m_IDC_PILOT_[4]);
	DDX_Control(pDX, IDC_PILOT_5, m_IDC_PILOT_[5]);
	DDX_Control(pDX, IDC_PILOT_6, m_IDC_PILOT_[6]);
	DDX_Control(pDX, IDC_PILOT_7, m_IDC_PILOT_[7]);
	DDX_Control(pDX, IDC_PILOT_8, m_IDC_PILOT_[8]);
	DDX_Control(pDX, IDC_PILOT_9, m_IDC_PILOT_[9]);

}


BEGIN_MESSAGE_MAP(BoBFrag, CDialog)
	//{{AFX_MSG_MAP(BoBFrag)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BoBFrag message handlers
void	BoBFrag::RefreshData(int targetid)
{
	Prefs_Selline=pselectedsquadron;
	Prefs_Showline=squadinfo.currfrag->currsquadoption;
	Prefs_Selslot=squadinfo.acnuminsquad;

}

BOOL BoBFrag::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

//DeadCode JIM 22Oct00 	Node_Data.BuildTargetTable();


	GetSideAndSetFrag();
	squadinfo.currfrag->currsquadoption = 0;
	if (Todays_Packages[0].packagestatus==Profile::PS_SPARE)
	 	FillSquadronsFromQM();
	else
		FillSquadronsFromCamp();

//DEADCODE RDH 23/03/00 	squadinfo.currfrag->currsquadoption = 0;							//CSB 01/03/00
	//Node_Data[squadnum] returns ref to Squadron
	//BritSquadron* mysq=Node_Data[squadnum];

	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLIST_UNITDETAILS);
	rlistbox->Clear();
	rlistbox->AddColumn(100);
	rlistbox->AddColumn(100);										  //RDH 02/06/99
	rlistbox->AddColumn(100);										  //RDH 02/06/99
	rlistbox->AddColumn(100);										  //RDH 02/06/99
	rlistbox->AddString(RESSTRING(UNIT),0);
	rlistbox->AddString(RESSTRING(AIRCRAFT),1);
	rlistbox->AddString(RESSTRING(DUTY),2);
	rlistbox->AddString(RESSTRING(CALLSIGN),3);

	CString string;
//DEADCODE AMM 03/03/00 	Gruppen* mystfl=Node_Data[squadinfo.currfrag->squadoptions[0].squadnum];	//RDH 28/02/00
//DEADCODE AMM 03/03/00 	int gruppennum = mystfl->gruppennum;
	int staffel = 0;													//RDH 28/02/00
	Gruppen* prevst = 0;
	for(int i = 0; i < squadinfo.currfrag->maxsquadoption; i++)
	{
		int side=GetSideAndSetFrag();

		if (!side)
		{
			BritSquadron* mysq=Node_Data[squadinfo.currfrag->squadoptions[i].squadnum];
			rlistbox->AddString(mysq->FullName(),0);
			rlistbox->AddString(RESLIST(SPIT_A, mysq->AcType()),1);
			string.LoadString(squadinfo.currfrag->squadoptions[i].somesortofduty);	//RDH 23/03/00
			rlistbox->AddString(string,2);
			rlistbox->AddString(mysq->CallName(),3);		
		}
		else
		{
			Gruppen* mystfl=Node_Data[squadinfo.currfrag->squadoptions[i].squadnum];	
//DEADCODE RDH 23/03/00 			int gruppennum = mystfl->gruppennum;
			CString name = mystfl->ShortName() + "/";					//RDH 28/02/00
			name = name + mystfl->SubName();
			if (prevst == mystfl)
				staffel++;
			else
			{
				prevst =mystfl;
				staffel =1;
			}

			name = name + CSprintf(" (%i)", staffel + (mystfl->gruppennum*3));	//RDH 28/02/00

			rlistbox->AddString(name,0);
			rlistbox->AddString(RESLIST(SPIT_A, mystfl->AcType()),1);
			string.LoadString(squadinfo.currfrag->squadoptions[i].somesortofduty);	//RDH 23/03/00
			rlistbox->AddString(string,2);
			rlistbox->AddString(mystfl->CallName() ,3);		
		}
	}
	
	if (Prefs_Showline!=-1)
	{
		squadinfo.currfrag->currsquadoption=Prefs_Selline;
		OnClickedPilot0(Prefs_Selslot+IDC_PILOT_0);
		OnSelectRlistUnitdetails(Prefs_Showline+1,0);
		Prefs_Showline=-1;
	}
	rlistbox->SetHilightRow(squadinfo.currfrag->currsquadoption+1);
	if (!RFullPanelDial::incomms)
	{
		CRButton* but=GETDLGITEM(IDC_UNASSIGNFLAG);
		but->ShowWindow(SW_HIDE);

//DeadCode AMM 25Sep00 		CRStatic* s=GETDLGITEM(IDC_UNASSIGN);							//AMM 28Jul00
//DeadCode AMM 25Sep00 		s->ShowWindow(SW_HIDE);											//AMM 28Jul00

//DEADCODE AMM 25/02/00 		CRStatic* s=GETDLGITEM(IDC_UNASSIGN);
//DEADCODE AMM 25/02/00 		s->ShowWindow(SW_HIDE);
	}
	else
	{
		_DPlay.SendStatusChange(DPlay::CPS_FRAG);
	}

	bobfrag_timer=SetTimer(DPlay::TIMER_FRAG,0,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//DeadCode AMM 08Mar00 void BoBFrag::ResetRemotePlayerEntry(int plyr)
void BoBFrag::ResetRemotePlayerEntry()
{
	int n;
	int	prev;

// first clear all slots

	for (n = 0; n < FragScreenBody::FE_MAX_PILOTS;n++)
	{
		squadinfo.currfrag->pilotentries[n].remoteplayerinslot = false;
	}

// OK, now fill in players positions

	for (n=0;n<MAXPLAYERS;n++)
	{
		if (DPlay::H2H_Player[n].dpid && n!=_DPlay.mySlot)
		{
// find which slot (if any) this player is in
// player may have selected an AC slot which is not currently displayed,

			if (squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum==DPlay::H2H_Player[n].squadron)
			{
// squadron being split over multiple lines?

				prev=0;

				ULong sel_pos=DPlay::H2H_Player[n].position;

				for( int i = 0; i < squadinfo.currfrag->maxsquadoption; i++)
				{
					if (squadinfo.currfrag->squadoptions[i].squadnum==DPlay::H2H_Player[n].squadron)
					{
						if (i==squadinfo.currfrag->currsquadoption)
						{
							sel_pos-=prev;
							squadinfo.currfrag->pilotentries[sel_pos].remoteplayerinslot = true;
							break;
						}
						prev+=squadinfo.currfrag->squadoptions[i].totalac;
					}
				}
			}
		}
	}
}

void BoBFrag::ResetPlayerEntry(int plyrpos)
{
	for (int i = 0; i < FragScreenBody::FE_MAX_PILOTS;i++)
	{
		squadinfo.currfrag->pilotentries[i].playerallowed      = true; 
	
		if (squadinfo.currfrag->pilotentries[i].playerinslot == true)
		{
//			squadinfo.currfrag->pilotentries[i].playerslotname = NULL;
			squadinfo.currfrag->pilotentries[i].playerinslot = false;
		}
	}

	int ppos2=plyrpos,prev;

	if (plyrpos >= 0)
	{
		prev=GetPreviousSquadronNumber(squadinfo.currfrag->currsquadoption);

		if (ppos2>prev)
			ppos2-=prev;

		if (RFullPanelDial::incomms)
		{
//DeadCode CSB 11Sep100 			squadinfo.currfrag->pilotentries[plyrpos].playerslotname     = DPlay::H2H_Player[_DPlay.mySlot].name;
			squadinfo.currfrag->pilotentries[ppos2].playerslotname     = DPlay::H2H_Player[_DPlay.mySlot].name;
		}
		else
		{
//DeadCode CSB 11Sep100 			squadinfo.currfrag->pilotentries[plyrpos].playerslotname     = MMC.PlayerName;
			squadinfo.currfrag->pilotentries[ppos2].playerslotname     = MMC.PlayerName;
		}

//DeadCode CSB 11Sep100 		squadinfo.currfrag->pilotentries[plyrpos].playerinslot       = true;
		squadinfo.currfrag->pilotentries[ppos2].playerinslot       = true;
	}

 	SetPlayersPosition(ppos2);
}

int	BoBFrag::GetPreviousSquadronNumber(int pos)
{
	int currsquadnum=squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum;
	int prev=0;

	int i;

	for (i=0;i<squadinfo.currfrag->currsquadoption;i++)
	{
		if (squadinfo.currfrag->squadoptions[i].squadnum==currsquadnum)
		{
			prev+=squadinfo.currfrag->squadoptions[i].totalac;
		}
	}

	return prev;
}

void BoBFrag::SetPlayersPositionCamp(int plyrpos)
{
	int side=GetSideAndSetFrag(),j,curr=0;

	if (plyrpos>=0)
	{
		char index=Todays_Packages.hipack;
//DeadCode JIM 20Oct00 		char sqindex=Todays_Packages.hisquad;

//DeadCode AMM 24Feb00 		j=sqindex;

		ULong numsquads=Todays_Packages[index].squadlist;

// for each squadron - see FillSquadronsFromCamp also
		
		for (j=0;j<numsquads;j++)
		{
			if (Todays_Packages[index].squadlist[j].status>Profile::PS_ACTIVE_MIN && Todays_Packages[index].squadlist[j].status<Profile::PS_REFUELLING)	//JIM 17Aug00
			{
//DEADCODE AMM 25/02/00 				if (curr++==squadinfo.currfrag->currsquadoption)
				if (curr++==pselectedsquadron)
				{
					MMC.playersquadron=Todays_Packages[index].squadlist[j].squadnum;
//DeadCode JIM 20Sep00 					MMC.playeracnum=plyrpos; // each squadron has own line
					break; // when loop is implemented
				}
			}
		}
		int	plyrnum=plyrpos;
		if (MMC.playersquadron<SQ_LW_START)
		{
			if (j==0)
			for (j=0;j<index;j++)
			{
				if (Todays_Packages[j][0].instance && Todays_Packages[j][0].squadnum==MMC.playersquadron)
					plyrnum+=Todays_Packages[j][0].numacleft;
			}
		}
		else
		{
			for (j=j-1;j>=0;j--)
				if (Todays_Packages[index][j].instance && Todays_Packages[index][j].squadnum==MMC.playersquadron)
					plyrnum+=Todays_Packages[index][j].numacleft;
		}
		MMC.playeracnum=plyrnum;
	}
//DEADCODE AMM 27/01/00 	else
//DEADCODE AMM 27/01/00 	{
//DEADCODE AMM 27/01/00 		MMC.playersquadron=6;
//DEADCODE AMM 27/01/00 		MMC.playeracnum=0;
//DEADCODE AMM 27/01/00 	}
}

void BoBFrag::SetPlayersPositionQM(int plyrpos)
{
// squadrons can be split over 2 lines in frag screen, so need to count
// number of previous ac in each squadron, and add these the ac num
	
	int side=GetSideAndSetFrag(),i,j,curr=0;//,prev;
	bool found=false;
// set previous to an ac type that will never be selectable
//DEADCODE AMM 08/03/00 	ULong prevsquad=PT_HE59;

	int	prev[PT_HE59];

	for (i=0;i<PT_HE59;i++)
	{
		prev[i]=0;
	}

	if (plyrpos>=0)
	{
		for (i=0;i<8;i++)
		{
//DEADCODE AMM 08/03/00 			prev=0; // reset number of previous ac in squadron

			for (j=0;j<4;j++)
			{
				int numflights=CSQuick1::quickdef.line[side][i][j].flights;

				if (numflights)
				{
					bool allowed=false;
					int side=GetSide();

//DeadCode AMM 08Aug00 					switch (CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype)
					switch (CSQuick1::quickdef.line[side][i][j].actype)
					{
					case PT_SPIT_A:
					case PT_SPIT_B:
					case PT_HURR_A:
					case PT_HURR_B:
					case PT_ME109:
					case PT_ME110:
					case PT_JU87:
						allowed=true;
						break;
					case PT_DO17:
					case PT_JU88:
					case PT_HE111:
						if (!_DPlay.PlayerCreated)
						{
							allowed=true;
						}
					}

//DEADCODE AMM 02/03/00 					if (squadinfo.currfrag->squadoptions[i].playerallowed)
					if (allowed)
					{
//DEADCODE AMM 25/02/00 						if (curr++==squadinfo.currfrag->currsquadoption)
						if (curr++==pselectedsquadron)
						{
							MMC.playersquadron=CSQuick1::quickdef.line[side][i][j].actype;;
							MMC.playeracnum=prev[MMC.playersquadron]+plyrpos;
							//quickdef.plac=plyrpos;
							found=true;
							break;
						}

						prev[CSQuick1::quickdef.line[side][i][j].actype]+=squadinfo.currfrag->squadoptions[i].totalac;

//DEADCODE AMM 08/03/00 						prevsquad=MMC.playersquadron;
					}
				}
			}
			if (found)
				break;
		}

		if (RFullPanelDial::incomms)
		{
			DPlay::H2H_Player[_DPlay.mySlot].squadron=MMC.playersquadron;
			DPlay::H2H_Player[_DPlay.mySlot].position=MMC.playeracnum;
		}
	}
	else
	{
//DeadCode AMM 27Jun00 		if (RFullPanelDial::incomms)
//DeadCode AMM 27Jun00 		{
//DeadCode AMM 27Jun00 			DPlay::H2H_Player[_DPlay.mySlot].squadron=-1;
//DeadCode AMM 27Jun00 			DPlay::H2H_Player[_DPlay.mySlot].position=-1;
//DeadCode AMM 27Jun00 		}
	}
//DEADCODE AMM 27/01/00 	else
//DEADCODE AMM 27/01/00 	{
//DEADCODE AMM 27/01/00 // player not allocated
//DEADCODE AMM 27/01/00 
//DEADCODE AMM 27/01/00 //		INT3;
//DEADCODE AMM 27/01/00 
//DEADCODE AMM 27/01/00 		MMC.playersquadron=-1;
//DEADCODE AMM 27/01/00 		MMC.playeracnum=0;
//DEADCODE AMM 27/01/00 	}

//DEADCODE AMM 07/03/00 	if (RFullPanelDial::incomms)
//DEADCODE AMM 07/03/00 	{
//DEADCODE AMM 07/03/00 		DPlay::H2H_Player[_DPlay.mySlot].squadron=MMC.playersquadron;
//DEADCODE AMM 07/03/00 		DPlay::H2H_Player[_DPlay.mySlot].position=MMC.playeracnum;
//DEADCODE AMM 07/03/00 	}
}

void BoBFrag::SetPlayersPosition(int plyrpos)
{

	if (plyrpos!=-1)
		squadinfo.acnuminsquad=plyrpos;
	if (Todays_Packages[0].packagestatus==Profile::PS_SPARE)
	{
// quick mission

		SetPlayersPositionQM(plyrpos);
	}
	else
	{
// campaign

		SetPlayersPositionCamp(plyrpos);
	}
}

void BoBFrag::PositionPilots()
{
	int pilots = squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].totalac;
	int formation = squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].acperflight-3; 
	if (formation < 0)
		formation = 0;
	if (formation > 3)
		formation = 3;

	CREdtBt*   b;
 
	
	int i;
	int flightnum=0,acinflight=0;
	int j;//, k =0;

// find if any previous squadrons are same AC type and therefore have used up
// callsigns, work out new offset

//DeadCode JIM 20Oct00 	int thissquadnum=squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum;

	flightnum=squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].startingcolour;
//DeadCode JIM 20Sep00 	if (thissquadnum>SQ_LW_START
//DeadCode JIM 20Sep00 		for (i=0;i<squadinfo.currfrag->currsquadoption;i++)
//DeadCode JIM 20Sep00 		{
//DeadCode JIM 20Sep00 			if (squadinfo.currfrag->squadoptions[i].squadnum==thissquadnum)
//DeadCode JIM 20Sep00 			{
//DeadCode JIM 20Sep00 				flightnum+=4;	//this is what I do in Persons3
//DeadCode JIM 20Sep00 			}
//DeadCode JIM 20Sep00 		}
//DeadCode JIM 20Sep00 	else
//DeadCode JIM 20Sep00 	{
//DeadCode JIM 20Sep00 
//DeadCode JIM 20Sep00 
//DeadCode JIM 20Sep00 	}
	i=0;

	while (i < pilots)
	{

		b=GETDLGITEM(IDC_PILOT_[i]);

		int side=GetSideAndSetFrag();

		if (!side)
		{
			BritSquadron* mysq=Node_Data[squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum];


			if (_DPlay.PlayerCreated && _DPlay.IsPilotDead(squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum+1,i+1))
			{
				b->SetCaption(RESSTRING(COMMSKIA));
			}
			else
			if (squadinfo.currfrag->pilotentries[i].playerinslot == true)
				b->SetCaption(squadinfo.currfrag->pilotentries[i].playerslotname);
			else if (squadinfo.currfrag->pilotentries[i].remoteplayerinslot)// == true)
			{
//DeadCode AMM 09Mar00 				SLong sel_squad,sel_pos;
//DeadCode AMM 09Mar00 
//DeadCode AMM 09Mar00 				GetSquadronAndPos(sel_squad,sel_pos,i);
//DeadCode AMM 09Mar00 
//DeadCode AMM 09Mar00 				if (sel_squad!=-1 && sel_pos!=-1)
//DeadCode AMM 09Mar00 				{
//DeadCode AMM 09Mar00 					ULong n;
//DeadCode AMM 09Mar00 
//DeadCode AMM 09Mar00 					for (n=0;n<MAXPLAYERS;n++)
//DeadCode AMM 09Mar00 					{
//DeadCode AMM 09Mar00 						if (DPlay::H2H_Player[n].squadron==sel_squad
//DeadCode AMM 09Mar00 						&& DPlay::H2H_Player[n].position==sel_pos)
//DeadCode AMM 09Mar00 						{
//DeadCode AMM 09Mar00 							b->SetCaption(DPlay::H2H_Player[n].name);
//DeadCode AMM 09Mar00 							break;
//DeadCode AMM 09Mar00 						}
//DeadCode AMM 09Mar00 					}
//DeadCode AMM 09Mar00 				}
				ULong n;

				for (n=0;n<MAXPLAYERS;n++)
				{
					if (DPlay::H2H_Player[n].squadron==squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum)
					{
// check for split squadron

						SLong sel_pos=GetSelectedPosition(DPlay::H2H_Player[n].squadron,DPlay::H2H_Player[n].position);

						if (sel_pos==i)
						{
							b->SetCaption(DPlay::H2H_Player[n].name);
							break;
						}
					}
				}
			}
			else if (FragScreenBody::buttonpos[formation][i].commandposition == CP_::CP_LEADER && !flightnum)
				b->SetCaption(LoadResString(mysq->leadername));
			else if (FragScreenBody::buttonpos[formation][i].commandposition == CP_::CP_SECOND && !flightnum)
				b->SetCaption(LoadResString(mysq->replaceleadername));
			else
			{
				if (mysq->squadron<SQ_LW_START)
					b->SetCaption(LoadResString((IDS_PHRASE_CALLEE_SN01+(flightnum*5))+acinflight));
				else
					b->SetCaption(LoadResString((IDS_PHRASE_CALLEE_LWSN01+(flightnum*5))+acinflight));
			}
		}
		else
		{
			Gruppen* mysq=Node_Data[squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum];


			if (_DPlay.PlayerCreated && _DPlay.IsPilotDead(squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum+1,i+1))
			{
				b->SetCaption(RESSTRING(COMMSKIA));
			}
			else
			if (squadinfo.currfrag->pilotentries[i].playerinslot == true)
				b->SetCaption(squadinfo.currfrag->pilotentries[i].playerslotname);
			else if (squadinfo.currfrag->pilotentries[i].remoteplayerinslot)
			{
//DEADCODE AMM 08/03/00 				SLong sel_squad,sel_pos;
//DEADCODE AMM 08/03/00 
//DEADCODE AMM 08/03/00 				GetSquadronAndPos(sel_squad,sel_pos,i);
//DEADCODE AMM 08/03/00 
//DEADCODE AMM 08/03/00 				if (sel_squad!=-1 && sel_pos!=-1)
//DEADCODE AMM 08/03/00 				{
					ULong n;

					for (n=0;n<MAXPLAYERS;n++)
					{
//DEADCODE AMM 08/03/00 						if (DPlay::H2H_Player[n].squadron==sel_squad
//DEADCODE AMM 08/03/00 						&& DPlay::H2H_Player[n].position==sel_pos)
						if (DPlay::H2H_Player[n].squadron==squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum)
						{
// check for split squadron

							SLong sel_pos=GetSelectedPosition(DPlay::H2H_Player[n].squadron,DPlay::H2H_Player[n].position);

							if (sel_pos==i)
							{
								b->SetCaption(DPlay::H2H_Player[n].name);
								break;
							}
						}
					}
			}
			else if (FragScreenBody::buttonpos[formation][i].commandposition == CP_::CP_LEADER && !flightnum)
				b->SetCaption(LoadResString(mysq->leadername));
			else if (FragScreenBody::buttonpos[formation][i].commandposition == CP_::CP_SECOND && !flightnum)
				b->SetCaption(LoadResString(mysq->replaceleadername));
			else
			{
//DeadCode JIM 22Sep00 				b->SetCaption(LoadResString((IDS_PHRASE_CALLEE_SN01+(flightnum*5))+acinflight));
				if (mysq->squadron<SQ_LW_START)
					b->SetCaption(LoadResString((IDS_PHRASE_CALLEE_SN01+(flightnum*5))+acinflight));
				else
					b->SetCaption(LoadResString((IDS_PHRASE_CALLEE_LWSN01+(flightnum*5))+acinflight));
			}
		}

		CRect currpos;
		b->GetWindowRect(currpos);
		currpos.bottom = 	currpos.bottom - currpos.top;
		currpos.right = 	currpos.right - currpos.left;


		currpos.left =  FragScreenBody::buttonpos[formation][i].coords.x;
		currpos.top = FragScreenBody::buttonpos[formation][i].coords.y;

		currpos.right += currpos.left;
		currpos.bottom += currpos.top;
		b->MoveWindow(currpos);
		b->ShowWindow(SW_SHOW);

		i++;

		if (++acinflight==squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].acperflight)
		{
			acinflight=0;
			flightnum++;
		}
	}
	while (i<15)
	{
		b=GETDLGITEM(IDC_PILOT_[i]);
		b->ShowWindow(SW_HIDE);
		i++;
	}
  	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLIST_UNITDETAILS);

	rlistbox->SetHilightRow(squadinfo.currfrag->currsquadoption+1);
}

BEGIN_EVENTSINK_MAP(BoBFrag, CDialog)
    //{{AFX_EVENTSINK_MAP(BoBFrag)
	ON_EVENT(BoBFrag, IDC_PLAYERCHAT, 1 /* ReturnPressed */, OnReturnPressedPlayerchat, VTS_BSTR)
	ON_EVENT(BoBFrag, IDC_RLIST_UNITDETAILS, 1 /* Select */, OnSelectRlistUnitdetails, VTS_I4 VTS_I4)
	ON_EVENT(BoBFrag, IDC_UNASSIGNFLAG, 1 /* Clicked */, OnClickedUnassignflag, VTS_NONE)
	ON_EVENT(BoBFrag, IDC_RETURNTOPLAYER, 1 /* Clicked */, OnClickedReturntoplayer, VTS_NONE)
	ON_EVENT_RANGE(BoBFrag, IDC_PILOT_0, IDC_PILOT_14,1 /* Clicked */, OnClickedPilot0, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


void BoBFrag::OnReturnPressedPlayerchat(LPCTSTR text) 
{
	// TODO: Add your control notification handler code here
	
}					

bool BoBFrag::IsControlledByGroup()
{
// determine if plwave or plgrp controls the number of squadrons in a quick mission
// It is going to be set so that wave is always the controller
	return false;
}

void BoBFrag::SetMissSelSquadron(int sel)
{
// update these so that mission select screen shows changed made in frag...sheesh

	if (IsControlledByGroup())
		CSQuick1::quickdef.plgrp=sel;
	else
		CSQuick1::quickdef.plwave=sel;
}

void BoBFrag::SetSelectedSquadron()
{
// need to set pselectedplayer and squadinfo.currfrag->currsquadoption to index of squadron
// chosen on mission select screen, controlled by either plwave xor plgrp

	if (CSQuick1::quickdef.plwave)
		pselectedsquadron=squadinfo.currfrag->currsquadoption=CSQuick1::quickdef.plwave;
	else
		pselectedsquadron=squadinfo.currfrag->currsquadoption=CSQuick1::quickdef.plgrp;
}

void BoBFrag::FillSquadronsFromQM()
{
//decide on side here and use currfrag from then on
	squadinfo.currfrag = &squadinfo.britfrag;

// fill in which side player has selected
// needs to be done before setting player entry

	int side=GetSideAndSetFrag();

//DeadCode AMM 25Jul00 	//temp
	if (!RFullPanelDial::incomms)
	{
//DeadCode AMM 10Jul00 		strcpy(MMC.PlayerName,"Me");
		strcpy(MMC.PlayerName,Save_Data.CommsPlayerName);					//AMM 10Jul00
	}


//DEADCODE AMM 02/03/00 	if (!RFullPanelDial::incomms)
//DEADCODE AMM 02/03/00 	{
//DEADCODE AMM 02/03/00 		ResetPlayerEntry(0);
//DEADCODE AMM 02/03/00 	}
//DEADCODE AMM 02/03/00 	else
//DEADCODE AMM 02/03/00 	{
//DEADCODE AMM 02/03/00 		ResetPlayerEntry(DPlay::H2H_Player[_DPlay.mySlot].position);
//DEADCODE AMM 02/03/00 	}
	ResetRemotePlayerEntry();

	squadinfo.currfrag->maxsquadoption = 0;
	squadinfo.currfrag->currsquadoption = 0;

	SetSelectedSquadron();

// find out how many squadrons there are

	int numsquads=0,i,j;
	int	countflights[PT_VEHICLES]={0};
	for (i=0;i<8;i++)
	{
		for (j=0;j<4;j++)
		{
			int numflights=CSQuick1::quickdef.line[side][i][j].flights;

			if (numflights)
			{
	// got a wave, fill in squadrons

				int num=3;
				int side=GetSide();

//DeadCode AMM 08Aug00 				if (!CSQuick1::quickdef.plside)
				squadinfo.currfrag->squadoptions[numsquads].startingcolour=countflights[CSQuick1::quickdef.line[side][i][j].actype];
				if (!side)
				{
					countflights[CSQuick1::quickdef.line[side][i][j].actype]+=numflights;
					num=3;
//DeadCode AMM 08Aug00 					switch (CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype)
					switch (CSQuick1::quickdef.line[side][i][j].actype)
					{
					case PT_SPIT_A:
					case PT_SPIT_B:
					case PT_HURR_A:
					case PT_HURR_B:
						squadinfo.currfrag->squadoptions[numsquads].playerallowed = true;
//DeadCode AMM 08Aug00 						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype;
						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[side][i][j].actype;
						
						break;
					case PT_DEFIANT:
					case PT_BLEN:
					default:
						squadinfo.currfrag->squadoptions[numsquads].playerallowed = false;
						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[side][i][j].actype;
						break;
					}
				}
				else
				{
//DeadCode AMM 08Aug00 					switch (CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype)
					countflights[CSQuick1::quickdef.line[side][i][j].actype]+=4;
					switch (CSQuick1::quickdef.line[side][i][j].actype)
					{
					case PT_ME109:
						num=4;
//DeadCode AMM 08Aug00 						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype;
						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[side][i][j].actype;
						squadinfo.currfrag->squadoptions[numsquads].playerallowed = true;
						break;
					case PT_ME110:
						num=4;
//DeadCode AMM 08Aug00 						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype;
						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[side][i][j].actype;
						squadinfo.currfrag->squadoptions[numsquads].playerallowed = true;
						break;
					case PT_JU87:
						num=3;
//DeadCode AMM 08Aug00 						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype;
						squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[side][i][j].actype;
						squadinfo.currfrag->squadoptions[numsquads].playerallowed = true;
						break;
					case PT_DO17:
					case PT_JU88:
					case PT_HE111:
// although these AC are not pilotable, player can play as gunner 
// though not in comms
						num=5;
						if (!_DPlay.PlayerCreated)
						{
//DeadCode AMM 08Aug00 							squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype;
							squadinfo.currfrag->squadoptions[numsquads].squadnum = (SquadNum)CSQuick1::quickdef.line[side][i][j].actype;
							squadinfo.currfrag->squadoptions[numsquads].playerallowed = true;
						}
						else
						{
							squadinfo.currfrag->squadoptions[numsquads].playerallowed = false;
						}
						break;
					case PT_HE59:
					default:
						num=5;
						squadinfo.currfrag->squadoptions[numsquads].playerallowed = false;
						break;
					}
				}
//DeadCode AMM 08Aug00 				num=CSQuick1::ACPerFlight(PlaneTypeSelect(CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype));
				num=CSQuick1::ACPerFlight(PlaneTypeSelect(CSQuick1::quickdef.line[side][i][j].actype));
//DeadCode AMM 08Aug00 				if (CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].Duty()==QuickFields::QFD_BRIT_LONE||CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].Duty()==QuickFields::QFD_GERM_LONE)
//DeadCode AMM 08Aug00 				if (CSQuick1::quickdef.line[side][i][j].Duty()==QuickFields::QFD_BRIT_LONE||CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].Duty()==QuickFields::QFD_GERM_LONE)
				if (	CSQuick1::quickdef.line[side][i][j].Duty()==QuickFields::QFD_BRIT_LONE
					||	CSQuick1::quickdef.line[side][i][j].Duty()==QuickFields::QFD_GERM_LONE
					||	CSQuick1::quickdef.line[side][i][j].Duty()==QuickFields::QFD_FIXED_NUM_PLAYER
					)
					num=1;
				if (squadinfo.currfrag->squadoptions[numsquads].playerallowed)
				{
					squadinfo.currfrag->squadoptions[numsquads].acperflight = num;
					squadinfo.currfrag->squadoptions[numsquads].totalac = numflights*num;
//DeadCode AMM 08Aug00 					squadinfo.currfrag->squadoptions[numsquads].somesortofduty = CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].descID;	//RDH 23/03/00
					squadinfo.currfrag->squadoptions[numsquads].somesortofduty = CSQuick1::quickdef.line[side][i][j].descID;	//RDH 23/03/00

					squadinfo.currfrag->maxsquadoption++;
					numsquads++;
				}
			}
		}
	}

	if (!RFullPanelDial::incomms)
	{
		ResetPlayerEntry(0);
	}
	else
	{
		ResetPlayerEntry(DPlay::H2H_Player[_DPlay.mySlot].position);
	}
	ResetRemotePlayerEntry();

	PositionPilots();
}

void BoBFrag::FillSquadronsFromCamp()
{
	int side=GetSideAndSetFrag(),j;

//DeadCode AMM 27Sep00 	//temp
//DeadCode AMM 27Sep00 	strcpy(MMC.PlayerName,"Me");
	strcpy(MMC.PlayerName,Save_Data.CommsPlayerName);					//AMM 27Sep00
//DeadCode JIM 12Oct00 	ResetPlayerEntry(0);
	ResetRemotePlayerEntry();

	squadinfo.currfrag->maxsquadoption = 0;
	squadinfo.currfrag->currsquadoption = 0;

// use Todays_Packages hipack and hisquad to find the correct squadron to
// put into currfrag

	char index=Todays_Packages.hipack;
	char sqindex=Todays_Packages.hisquad;

	ULong numsquads=Todays_Packages[index].squadlist;
	int	startcolour=0;
	if (numsquads==1)
	{
		int colourmap=Todays_Packages[index].squadlist.AcBitsFirstSquad();
		while (!(colourmap&7))
		{
			startcolour++;
			colourmap>>=3;
		}
	}

	for (j=0;j<numsquads;j++)
// for each squadron - see SetPlayersPositionCamp also
	{
//DEADCODE JIM 09/02/00 		j=sqindex;

// only allow player to take control of squadron if takeofftime>currtime
		//Test poor: takeofftime is not best criteria... some flights take off just before takeoff time.								//JIM 2Oct00
		//I have fixed this before. If there is a problem please tell me.
		if (	Todays_Packages[index].squadlist[j].status>Profile::PS_ACTIVE_MIN 		//JIM 2Oct00
			&&	Todays_Packages[index].squadlist[j].status<Profile::PS_REFUELLING	)	//JIM 2Oct00
//DeadCode JIM 2Oct00 			takeofftime<=MMC.currtime)
		{
// numacoriginal + formation type gives numacper flight

			//In 3d I only have numacleft available for this calculation...
			ULong numoriginal=Todays_Packages[index].squadlist[j].numacleft;	//numacoriginal;

// find formation

			UWord tempform=Todays_Packages[index].squadlist[j].formtype&FORMTYPE_WING;

// determine number of ac per flight

			SingleFormation	
				wingmanpos=Aircraft_Formations[tempform];
			int totalac=numoriginal;
			int perfl=wingmanpos->GetPerFl(totalac);
//DeadCode JIM 7Jul00 			if (perfl>=10)
//DeadCode JIM 7Jul00 			{
//DeadCode JIM 7Jul00 				UWord fl2=perfl;
//DeadCode JIM 7Jul00 				while (fl2>0)
//DeadCode JIM 7Jul00 				{
//DeadCode JIM 7Jul00 					perfl=fl2%10;										//RDH 23/03/00
//DeadCode JIM 7Jul00 					breakif (totalac%perfl==0);
//DeadCode JIM 7Jul00 					fl2/=10;
//DeadCode JIM 7Jul00 				}
//DeadCode JIM 7Jul00 			}
			int mso=squadinfo.currfrag->maxsquadoption;
			if (j==sqindex)
				pselectedsquadron=
					squadinfo.currfrag->currsquadoption=mso;
			{for (int c=0,currsq=Todays_Packages[index].squadlist[j].squadnum;c<j;c++)
				if (Todays_Packages[index].squadlist[c].squadnum==currsq)
					startcolour+=4;
			}
			squadinfo.currfrag->squadoptions[mso].startingcolour=startcolour;
			startcolour=0;
			squadinfo.currfrag->squadoptions[mso].acperflight = perfl;

			squadinfo.currfrag->squadoptions[mso].totalac = Todays_Packages[index].squadlist[j].numacleft;
			squadinfo.currfrag->squadoptions[mso].somesortofduty =IDS_L_AM_PATROL + Todays_Packages[index].squadlist[j].method;
			squadinfo.currfrag->squadoptions[mso].playerallowed = true;
			squadinfo.currfrag->squadoptions[mso].squadnum = Todays_Packages[index].squadlist[j].squadnum;
			squadinfo.currfrag->maxsquadoption++;
		}
	}
	ResetPlayerEntry(0);
	if (squadinfo.currfrag->maxsquadoption)
		PositionPilots();
	else
		MMC.playersquadron=-1;
}

void BoBFrag::OnSelectRlistUnitdetails(long row, long column) 
{
	if (row>0)
	{
		squadinfo.currfrag->currsquadoption = row-1;

		if (pselectedsquadron!=row-1 || pselectedsquadron==-1)
		{
			ResetPlayerEntry(-1);
		}
		else
		{
			ResetPlayerEntry(squadinfo.acnuminsquad);
		}

		if (RFullPanelDial::incomms)
		{
			ResetRemotePlayerEntry();
		}
	}
	PositionPilots();
	
}

void BoBFrag::OnClickedPilot0(int id) 
{
	int butnum = id - IDC_PILOT_0;

//DeadCode AMM 5Sep00 	pselectedsquadron=squadinfo.currfrag->squadoptions[squadinfo.currfrag->currsquadoption].squadnum;
	pselectedsquadron=squadinfo.currfrag->currsquadoption;

	if (RFullPanelDial::incomms)
	{
		SLong sel_squad,sel_pos;

		GetSquadronAndPos(sel_squad,sel_pos,butnum);

//		sel_squad=squadinfo.currfrag->squadoptions[squadinto.currfrag->currsquadoption].squadnum;
		if (sel_squad!=-1 && sel_pos!=-1)
		{
			if (!_DPlay.IsPilotDead(pselectedsquadron+1,sel_pos+1))
			{
				if (_DPlay.SlotFree(sel_pos,sel_squad))
				{
					ResetPlayerEntry(butnum);
					SetPlayersPosition(butnum);
  					PositionPilots();
				}
			}
		}
	}
	else
	{
		ResetPlayerEntry(butnum);
//DEADCODE AMM 25/02/00 		SetPlayersPosition(butnum);
  		PositionPilots();
	}

	SetMissSelSquadron(pselectedsquadron);
}

void BoBFrag::OnClickedUnassignflag() 
{
	if (RFullPanelDial::incomms)
	{
		pselectedsquadron=-1;
		ResetPlayerEntry(-1);
  		PositionPilots();

		SLOTPOSPACK s;

		s.PacketID=PID_SLOTINFOUPDATE;
		s.squadron=-1;
		s.position=0;
		s.PlayerID=_DPlay.myDPlayID;

		DPlay::H2H_Player[_DPlay.mySlot].squadron=-1;
		DPlay::H2H_Player[_DPlay.mySlot].position=-1;

		_DPlay.SendMessageToGroup((char*)&s,sizeof(SLOTPOSPACK));
	}
}

int	BoBFrag::GetSideAndSetFrag()
{
	int side;

	if (Todays_Packages[0].packagestatus==Profile::PS_SPARE)
	{
		Node_Data.BuildTargetTable();									//JIM 22Oct00
		if (_DPlay.PlayerCreated)
		{
			if (DPlay::H2H_Player[_DPlay.mySlot].MyTeam==DPlay::TS_RED)
			{
				squadinfo.currfrag = &squadinfo.germanfrag;
				side=1;
			}
			else
			{
				squadinfo.currfrag = &squadinfo.britfrag;
				side=0;
			}
		}
		else
		{
			if (!CSQuick1::quickdef.plside)
			{
				squadinfo.currfrag = &squadinfo.britfrag;
				side=0;
			}
			else
			{
				squadinfo.currfrag = &squadinfo.germanfrag;
				side=1;
			}
		}
	}
	else
	{
		if (Todays_Packages.localplayer==NAT_RED)
		{
			squadinfo.currfrag = &squadinfo.britfrag;
			side=0;
		}
		else
		{
			squadinfo.currfrag = &squadinfo.germanfrag;
			side=1;
		}
	}

	return side;
}

void	BoBFrag::GetSquadronAndPos(SLong& sel_squad, SLong& sel_pos, ULong plyrpos)
{
	int side=GetSideAndSetFrag(),i,j,curr=0;//,prev=0;
	bool found=false;
//DEADCODE AMM 08/03/00 	ULong prevsquad=PT_HE59;

	int prev[PT_HE59];

	for (i=0;i<PT_HE59;i++)
	{
		prev[i]=0;
	}

	if (plyrpos>=0)
	{
		for (i=0;i<8;i++)
		{
			for (j=0;j<4;j++)
			{
				int numflights=CSQuick1::quickdef.line[side][i][j].flights;

				bool allowed=false;
				int side=GetSide();

//DeadCode AMM 08Aug00 				switch (CSQuick1::quickdef.line[CSQuick1::quickdef.plside][i][j].actype)
				switch (CSQuick1::quickdef.line[side][i][j].actype)
				{
				case PT_SPIT_A:
				case PT_SPIT_B:
				case PT_HURR_A:
				case PT_HURR_B:
				case PT_ME109:
				case PT_ME110:
				case PT_JU87:
					allowed=true;
					break;
				case PT_DO17:
				case PT_JU88:
				case PT_HE111:
					if (!_DPlay.PlayerCreated)
					{
						allowed=true;
					}
				}

				if (numflights && allowed)
				{
					if (curr++==pselectedsquadron)
					{
						sel_squad=CSQuick1::quickdef.line[side][i][j].actype;;
						sel_pos=prev[sel_squad]+plyrpos;

						found=true;
						break;
					}
					prev[CSQuick1::quickdef.line[side][i][j].actype]+=squadinfo.currfrag->squadoptions[i].totalac;
				}
			}
			if (found)
				break;
		}
	}

	if (!found)
	{
		sel_squad=-1;
		sel_pos=-1;
	}
}




void BoBFrag::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==bobfrag_timer)
	{
		if (_DPlay.PlayerCreated)
		{
			_DPlay.UIUpdateMainSheet();

			if (_DPlay.FlyNowFlag)
			{
				if (_DPlay.UINetworkSelectFly())
				{
					KillTimer(bobfrag_timer);

// need to launch quickmissionflight sheet

					FullPanel()->OnSelectRlistbox(1,1);
					return;
				}
				else
				{
					_DPlay.FlyNowFlag=FALSE;
					_DPlay.SendStatusChange(DPlay::CPS_FRAG);
				}
			}
			else if (_DPlay.UpdateFrag)
			{
				_DPlay.UpdateFrag=FALSE;

				ResetRemotePlayerEntry();
				PositionPilots();
			}
			else if (_DPlay.FragChanged)
			{
// if the frag has changed then leave because reinitisalisation is required 

				_DPlay.FragChanged=false;

				FullPanel()->OnSelectRlistbox(0,0);				//JIM 12Jan99
				return;
			}
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

SLong	BoBFrag::GetSelectedPosition(SLong squad, SLong pos)
{
	int i;

	for(i = 0; i < squadinfo.currfrag->maxsquadoption; i++)
	{
		if (squadinfo.currfrag->squadoptions[i].squadnum==squad)
		{
			if (pos>=squadinfo.currfrag->squadoptions[i].totalac)
			{
				pos-=squadinfo.currfrag->squadoptions[i].totalac;
			}
			break;
		}
	}

	return pos;
}

void BoBFrag::OnDestroy() 
{
	KillTimer(bobfrag_timer);

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

int BoBFrag::GetSide()
{
	if (_DPlay.PlayerCreated)
	{
		if (DPlay::H2H_Player[_DPlay.mySlot].MyTeam==DPlay::TS_RED)
			return 1;
		else
			return 0;
	}
	else
	{
		return CSQuick1::quickdef.plside;
	}

}


void BoBFrag::OnClickedReturntoplayer() 
{
	if (pselectedsquadron>-1)
	{
		squadinfo.currfrag->currsquadoption = pselectedsquadron;

//DeadCode AMM 11Sep00 		if (pselectedsquadron!=row-1)
//DeadCode AMM 11Sep00 		{
//DeadCode AMM 11Sep00 			ResetPlayerEntry(-1);
//DeadCode AMM 11Sep00 		}
//DeadCode AMM 11Sep00 		else
		{
			ResetPlayerEntry(squadinfo.acnuminsquad);
		}

		if (RFullPanelDial::incomms)
		{
			ResetRemotePlayerEntry();
		}
		PositionPilots();	
	}
}

