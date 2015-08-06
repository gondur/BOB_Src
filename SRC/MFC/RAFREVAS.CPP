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

// RowanDialog: // RAFRevAs.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "RAFRevAs.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// RAFReviewAsset dialog


RDialog*	RAFReviewAsset::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new RAFReviewAsset())
			);
}


RAFReviewAsset::RAFReviewAsset(CWnd* pParent /*=NULL*/)
	: RowanDialog(RAFReviewAsset::IDD, pParent)
{
	//{{AFX_DATA_INIT(RAFReviewAsset)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
		dr = new LWDirectivesResults;

}
RAFReviewAsset::~RAFReviewAsset()
{
	if (dr)
		delete dr;
}


void RAFReviewAsset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(RAFReviewAsset)
	DDX_Control(pDX, IDC_RLISTBOXCTRL1, m_IDC_RLISTBOXCTRL1);
	//}}AFX_DATA_MAP
	GETDLGITEM(IDC_RLISTBOXCTRL1)->AddString("",0);
}


BEGIN_MESSAGE_MAP(RAFReviewAsset, CDialog)
	//{{AFX_MSG_MAP(RAFReviewAsset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// RAFReviewAsset message handlers
void RAFReviewAsset::FillTrgInfo(int out, int in, int cnt)
{
	TargetNoDetail* trg = Node_Data[dr->trgarray[in].target[cnt].target];
	int status;
	status=trg->PlayerStatus();
//DeadCode JON 4Sep00 		if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
//DeadCode JON 4Sep00 				&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
//DeadCode JON 4Sep00 			)
//DeadCode JON 4Sep00 		status = trg->knownstatus;
//DeadCode JON 4Sep00 	else
//DeadCode JON 4Sep00 		status = trg->truestatus;
	if		(status > Target::TS_MAXIMUM)		trginfo[out].unknown++;
	elseif		(status >= Target::TS_NEARLYDESTROYED)	trginfo[out].destroyed++;
	elseif	(status>=Target::TS_BADDAMAGE)		trginfo[out].damaged++;
	elseif	(status>=Target::TS_LIGHTDAMAGE)	trginfo[out].damaged++;
	else										trginfo[out].ok++;
		
}


void RAFReviewAsset::FillTrgInfoArray()
{
	LWDirectivesResults::FillTargetLists(dr);

	for (int i = 0; i <MAXTARGETTYPES; i++)
	{
		trginfo[i].ok = 0;
		trginfo[i].damaged = 0;
		trginfo[i].destroyed = 0;
		trginfo[i].unknown = 0;
	}
	int trgtype;

	int in = Directives::LW::Targ::DOCKS;
	int out = DOCKS;
	int j = 0;
	while (	(dr->trgarray[in].target[j].target != IllegalBAND))
	{
		FillTrgInfo(out, in, j);
		j++;
	}


	in = Directives::LW::Targ::RADARS;
	j = 0;
	while (	(dr->trgarray[in].target[j].target != IllegalBAND))
	{
		TargetNoDetail* trg = Node_Data[dr->trgarray[in].target[j].target];
	
		if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
				&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
			)
				trgtype = trg->falsetargtype;
			else
				trgtype = trg->truetargtype;
//DeadCode JIM 3Jul00 			if ( trgtype == Target::TT_AS_KNOWN)
//DeadCode JIM 3Jul00 				trgtype = trg->truetargtype;
		if (trgtype == Target::TT_CHAINHOME)
			out = CHAINHOME;
		else
			out = CHAINLOW;
		FillTrgInfo(out, in, j);
		j++;
	}

	in = Directives::LW::Targ::FACTORIES;
	j = 0;
	while (	(dr->trgarray[in].target[j].target != IllegalBAND))
	{
		TargetNoDetail* trg = Node_Data[dr->trgarray[in].target[j].target];
	
		if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
				&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
			)
				trgtype = trg->falsetargtype;
			else
				trgtype = trg->truetargtype;
//DeadCode JIM 3Jul00 			if ( trgtype == Target::TT_AS_KNOWN)
//DeadCode JIM 3Jul00 				trgtype = trg->truetargtype;
		if	(		(trgtype == Target::TT_SPITASSEMBLY)
				||	(trgtype == Target::TT_HURRASSEMBLY)
			)
			out = KEYINDUSTRY;
		else
			out = SUPPORTINDUSTRY;
		FillTrgInfo(out, in, j);
		j++;
	}

	in = Directives::LW::Targ::AIRFIELDS;
	j = 0;
	while (	(dr->trgarray[in].target[j].target != IllegalBAND))
	{
		if (Node_Data[dr->trgarray[in].target[j].target].IsA(Target::TSS_TargetAirfield))
		{
			TargetFighterField* af = Node_Data[dr->trgarray[in].target[j].target];
	 		TargetSectorField*	sectorfield = af->getsectoraf();
			if		(sectorfield->groupname == IDS_GROUP_10)
				out = GR10AF;
			else if		(sectorfield->groupname == IDS_GROUP_11)
				out = GR11AF;
			else
				out = GR12AF;

			FillTrgInfo(out, in, j);
			FillTrgInfo(TOTALAF, in, j);
		}		
		j++;
	}
	in = Directives::LW::Targ::LONDON;
	j = 0;
	while (	(dr->trgarray[in].target[j].target != IllegalBAND))
	{
		FillTrgInfo(LONDON, in, j);
		
		j++;
	}


}

BOOL RAFReviewAsset::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CRListBox* rlistbox;
	rlistbox=GETDLGITEM(IDC_RLISTBOXCTRL1);
//DeadCode RDH 31Oct00  	rlistbox->AddString("",0);
	rlistbox->Clear();
	//rlistbox->AddColumn(140);				//MIKE
 	//rlistbox->AddColumn(70);
 	//rlistbox->AddColumn(70);										  //RDH 02/06/99
 	//rlistbox->AddColumn(70);
 	//rlistbox->AddColumn(70);
	rlistbox->AddString(RESSTRING(ASSET),0);
	rlistbox->AddString(RESSTRING(HL_UNKNOWN),1);
	rlistbox->AddString(RESSTRING(OK),2);
	rlistbox->AddString(RESSTRING(DESTROYED),3);
	rlistbox->AddString(RESSTRING(DAMAGED),4);
	

	rlistbox->AddString(RESSTRING(RDFCH),0);
	rlistbox->AddString(RESSTRING(RDFCL),0);
	rlistbox->AddString(RESSTRING(KEYINDUSTRY),0);
	rlistbox->AddString(RESSTRING(SUPPORTINDUSTRY),0);
	rlistbox->AddString(RESSTRING(DOCKS),0);
	rlistbox->AddString(RESSTRING(LONDON),0);
	rlistbox->AddString(RESSTRING(GROUP10AF),0);
	rlistbox->AddString(RESSTRING(GROUP11AF),0);
	rlistbox->AddString(RESSTRING(GROUP12AF),0);
	rlistbox->AddString(RESSTRING(ALLAF),0);

	FillTrgInfoArray();

	for (int i = 0; i <MAXTARGETTYPES; i++)
	{
		int total = trginfo[i].unknown + trginfo[i].ok + 
						trginfo[i].destroyed + trginfo[i].damaged;
		
		int pc = (trginfo[i].unknown * 100)/total;
		rlistbox->AddString(CSprintf("%i (%i%%)",trginfo[i].unknown, pc),1);
		pc = (trginfo[i].ok * 100)/total;
		rlistbox->AddString(CSprintf("%i (%i%%)",trginfo[i].ok, pc),2);
		pc = (trginfo[i].destroyed * 100)/total;
		rlistbox->AddString(CSprintf("%i (%i%%)",trginfo[i].destroyed, pc),3);
		pc = (trginfo[i].damaged * 100)/total;
		rlistbox->AddString(CSprintf("%i (%i%%)",trginfo[i].damaged, pc),4);
	}


//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("5",1);
//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("65",1);
//DEADCODE  17/02/00 	rlistbox->AddString("120",1);
//DEADCODE  17/02/00 	rlistbox->AddString("80",1);
//DEADCODE  17/02/00 	rlistbox->AddString("20",1);
//DEADCODE  17/02/00 	rlistbox->AddString("80",1);
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("5",2);
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("65",2);
//DEADCODE  17/02/00 	rlistbox->AddString("120",2);
//DEADCODE  17/02/00 	rlistbox->AddString("80",2);
//DEADCODE  17/02/00 	rlistbox->AddString("20",2);
//DEADCODE  17/02/00 	rlistbox->AddString("80",2);
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("5",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("65",3);
//DEADCODE  17/02/00 	rlistbox->AddString("120",3);
//DEADCODE  17/02/00 	rlistbox->AddString("80",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 	rlistbox->AddString("20",3);
//DEADCODE  17/02/00 
//DEADCODE  17/02/00 	rlistbox->AddString("20",4);
//DEADCODE  17/02/00 	rlistbox->AddString("5",4);
//DEADCODE  17/02/00 	rlistbox->AddString("20",4);
//DEADCODE  17/02/00 	rlistbox->AddString("20",4);
//DEADCODE  17/02/00 	rlistbox->AddString("65",4);
//DEADCODE  17/02/00 	rlistbox->AddString("120",4);
//DEADCODE  17/02/00 	rlistbox->AddString("80",4);
//DEADCODE  17/02/00 	rlistbox->AddString("20",4);
//DEADCODE  17/02/00 	rlistbox->AddString("20",4);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
