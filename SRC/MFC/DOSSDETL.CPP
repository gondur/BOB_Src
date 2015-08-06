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

// RowanDialog: // DossDetl.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "DossDetl.h"
#include "package.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// DossierDetails dialog


RDialog*	DossierDetails::Make(UniqueID sgt)
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new DossierDetails(sgt))
			);
}


DossierDetails::DossierDetails(UniqueID sgt,CWnd* pParent /*=NULL*/)
	: RowanDialog(DossierDetails::IDD, pParent)
{
	//{{AFX_DATA_INIT(DossierDetails)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	trguid=sgt;
}


void DossierDetails::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DossierDetails)
	DDX_Control(pDX, IDC_DOSSNOTES, m_IDC_DOSSNOTES);
	DDX_Control(pDX, IDC_RSTATICAAA, m_IDC_RSTATICAAA);
	DDX_Control(pDX, IDC_RSTATICBALLOON, m_IDC_RSTATICBALLOON);
	DDX_Control(pDX, IDC_RSTATICDAMAGE, m_IDC_RSTATICDAMAGE);
	DDX_Control(pDX, IDC_RSTATICNAME, m_IDC_RSTATICNAME);
	DDX_Control(pDX, IDC_RSTATICPROD, m_IDC_RSTATICPROD);
	DDX_Control(pDX, IDC_RSTATICSTATUS, m_IDC_RSTATICSTATUS);
	DDX_Control(pDX, IDC_RSTATICTYPE, m_IDC_RSTATICTYPE);
	DDX_Control(pDX, IDC_RSTATICCTRL_PROD, m_IDC_RSTATICCTRL_PROD);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DossierDetails, CDialog)
	//{{AFX_MSG_MAP(DossierDetails)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DossierDetails message handlers

void DossierDetails::DosNotes()
{

	
	Profile* pk ;
	bool packfound = false;
	CString notes="";
	for (int pack = Profile::MAX_PACKS-1,lines=4;lines>0 && pack>=0;pack--)
	{
		if (Todays_Packages.pack[pack].packagestatus!=Profile::PS_SPARE)
		{
		 	pk = &Todays_Packages.pack[pack];
			if (pk->raidnumentries[0].raidnum)
				for(int targetnum = 0;(pk->packagetarget[targetnum].currentid);targetnum++	)
				{
					packfound=false;
					if (pk->packagetarget[targetnum].currentid == trguid)
						packfound=true;
					else
						if (pk->packagetarget[targetnum].currentid <= SagBANDEND)
						{
							int tp,ts;
							if (Todays_Packages.GetACSquadEntry(pk->packagetarget[targetnum].currentid,tp,ts))
								if (Todays_Packages[tp].SquadTarget(ts)==trguid)
									packfound=true;
						}
					if (packfound)
					{
						notes=CString("   ")+ RESLIST(AM_PATROL,pk->attackmethod)+":    "+RESLIST(PS_SPARE,pk->packagestatus)+"\n"+notes;
						lines--;
					}

				}
		}
		
	}


 	CRStatic*   s;

	s= GETDLGITEM(IDC_DOSSNOTES);
	if (notes!="")
	{
#ifndef	NDEBUG
		TargetNoDetail* trg = Node_Data[trguid];
		if (trg)
			notes=CSprintf("Damage Levels: True: %i%% LWIntel: %i%%\n%s",trg->truestatus,trg->knownstatus,notes);
#endif
		s->SetString(RESSTRING(MISSIONS)+":\n"+notes);
	}else
	{
		int string = IDS_BLANK;
		TargetNoDetail* trg = Node_Data[trguid];
		if (trg)
		{	
//DeadCode JIM 3Jul00 			int dstatus = trg->knownstatus - trg->truestatus;
//DeadCode JIM 3Jul00 			if (dstatus < 0)
//DeadCode JIM 3Jul00 				dstatus = -dstatus;
			if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
					&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
					&&	trg->ReconAdvised()
				)
				string = IDS_RECONNREQUIRED;
		}
#ifndef	NDEBUG
		s->SetString(LoadResString(string)+CSprintf("\nDamage Levels: True: %i%% LWIntel: %i%%\n",trg->truestatus,trg->knownstatus));
#else
		s->SetString(LoadResString(string));
#endif
	}

	
}


BOOL DossierDetails::OnInitDialog() 
{
	CDialog::OnInitDialog();
//	if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
	
	CRStatic*   s;
	CRStatic*   stat;
	s= GETDLGITEM(IDC_RSTATICNAME);
	s->SetString(GetTargName(trguid));

	const TargetNoDetail* trg = Node_Data[trguid];

	s= GETDLGITEM(IDC_RSTATICTYPE);
	int trgtype;
	if (trg)
	{
		if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
				&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
			)
			trgtype = trg->falsetargtype;
		else
			trgtype = trg->truetargtype;
//DeadCode JIM 3Jul00 		if ( trgtype == Target::TT_AS_KNOWN)
//DeadCode JIM 3Jul00 			trgtype = trg->truetargtype;
		s->SetString(RESLIST(TT_AS_KNOWN, trgtype));
	}else
		s->SetString("");

	if (trg)
	{
		s= GETDLGITEM(IDC_RSTATICAAA);
		int def = trg->truedefenses & Target::MASK_AAA;
		def =def/16;
		if (def >5)
			def = 5;
		s->SetString(RESLIST(NONE_ACTIVITY,def));

		s= GETDLGITEM(IDC_RSTATICBALLOON);
		def = trg->truedefenses & Target::MASK_BALL;
		if (def >5)
			def = 5;
		s->SetString(RESLIST(NONE_ACTIVITY,def));
	}else
	{
		s= GETDLGITEM(IDC_RSTATICAAA);
		s->SetString("");

		s= GETDLGITEM(IDC_RSTATICBALLOON);
		s->SetString("");

	}
	
	int uidband;
	uidband=Persons2::getbandfromUID(trguid);
	s= GETDLGITEM(IDC_RSTATICPROD);
	stat = GETDLGITEM(IDC_RSTATICCTRL_PROD);

	if (	(uidband == AircraftFactoryBAND)
			&&
			 (	(	(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
					&&	(		(trgtype == Target::TT_SPITASSEMBLY)
							||	(trgtype == Target::TT_HURRASSEMBLY)
							||	(trgtype == Target::TT_UNKNOWNAIRCRAFT)
						)
				)
				||
				(RFullPanelDial::gameside != RFullPanelDial::SIDE_LW)
			)
		)
	{
		s->ShowWindow(true);
		stat->ShowWindow(true);
		TargetFakeFactory* fact = Node_Data[trguid];

		int capacity = fact->currperweek;
		if (RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
			capacity = 20 * ((capacity+10)/20);


		s->SetString(CSprintf("%i %s",capacity, RESSTRING(PERWEEK)));
	}else
	{
		s->ShowWindow(false);
		stat->ShowWindow(false);

	}

	s= GETDLGITEM(IDC_RSTATICSTATUS);
	if (trg)
	{
		int j;
		if (		(RFullPanelDial::gameside == RFullPanelDial::SIDE_LW)
		//		&&	(!Save_Data.gamedifficulty[GD_LWINTELL])
			)
			j = trg->PlayerStatus();
		else
		{
			j = trg->truestatus;
			if (	j>Target::TS_NEARLYDESTROYED 
				&& (trgtype==Target::TT_CHAINHOME || trgtype==Target::TT_CHAINLOW)
				&& 	TargetRadarPtr(Node_Data[trguid])->mobileunit
				)
				j=Target::TS_FLAG4;//254;
		}
		if	(j == Target::TS_FLAG_UNKNOWN)	//had <0 check								//JIM 3Jul00
			s->SetString(RESSTRING(TT_UNKNOWN));
		else if (j==Target::TS_FLAG4)
			s->SetString(RESSTRING(SHP_RADTRK));
		else
		{
			if		(j >= Target::TS_NEARLYDESTROYED)		j = 3;
			elseif	(j>Target::TS_BADDAMAGE)				j=2;
			elseif	(j>Target::TS_LIGHTDAMAGE)				j=1;
			else											j=0;
			s->SetString(RESLIST(UNDAMAGED, j));
		}
	}else
	{
		s->SetString("");
	}
	
//DeadCode  13Sep00 	s= GETDLGITEM(IDC_RSTATICDAMAGE);
//DeadCode  13Sep00 	s->SetString("");


	DosNotes();

	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
