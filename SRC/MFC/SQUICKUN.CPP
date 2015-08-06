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

// RowanDialog: // SQuickUN.cpp : implementation file
//

#include "stdafx.h"
//#include "mig.h"
//#include "SQuickUN.h"
#include	"bitfield.h"
typedef	 QuickFields	Q;

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif
typedef	 QuickFields::QFD	QFD;
#ifndef QFDFIELD
#define QFDFIELD
MAKEFIELD(QFD,0,Q::QFD_LAST);
#endif


//////////////////////////////////////////////////////////////////////
//
// Function:    ACPerFlight
// Date:		02/05/00
// Author:		MS
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
int	QuickFields::ACPerFlight()
{
	return 	CSQuick1::ACPerFlight(PlaneTypeSelect(actype));
}

int	CSQuick1::ACPerFlight(PlaneTypeSelect actype)
{
	int	acperflight;
	if (actype<PT_GER_FLYABLE)
		acperflight=3;
	elseif (actype<PT_JU87)
		acperflight=4;
	elseif (actype>PT_JU87)
		acperflight=5;
	else
		acperflight=3;
	return acperflight;
}
int	CSQuick1::MaxFlights(PlaneTypeSelect actype)
{
	int	flights;
	if (actype<PT_GER_FLYABLE)
		flights=4;
	elseif (actype<PT_JU87)
		flights=3;
	elseif (actype>PT_JU87)
		flights=3;
	else
		flights=4;
	return flights;
}
int	 CSQuick1::MaxGrFlights(PlaneTypeSelect actype)
{
	int	flights;
	if (actype<PT_GER_FLYABLE)
		flights=4;
	elseif (actype<PT_JU87)
		flights=9;
	elseif (actype>PT_JU87)
		flights=8;
	else
		flights=12;
	return flights;

}


/////////////////////////////////////////////////////////////////////////////
// CSQuickLine dialog


CSQuickLine::CSQuickLine(int side,int wave,int group,CWnd* pParent /*=NULL*/)
	: RowanDialog(CSQuickLine::IDD, pParent)
{
	SetProjSpecific(side,wave,group);
	fields=&CSQuick1::quickdef.line[side][wave][group];
	//{{AFX_DATA_INIT(CSQuickLine)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSQuickLine::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSQuickLine)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_GRPDESC,m_IDC_GRPDESC);
	DDX_Control(pDX,IDC_FLIGHTS,m_IDC_FLIGHTS);
	DDX_Control(pDX,IDC_TYPE,m_IDC_TYPE);
	DDX_Control(pDX,IDC_ALT,m_IDC_ALT);
	DDX_Control(pDX,IDC_SKILL,m_IDC_SKILL);
	DDX_Control(pDX,IDC_PILOTEDFLAG,m_IDC_PILOTEDFLAG);
	DDX_Control(pDX,IDC_RSTATICCTRL41,m_IDC_RSTATICCTRL41);
	DDX_Control(pDX,IDC_RSTATICCTRL42,m_IDC_RSTATICCTRL42);
	//}}AFX_DATA_MAP
}

BOOL CSQuickLine::OnInitDialog() 		//FP
{
	CDialog::OnInitDialog();
	fields->dialog=this;
	return OnInitDialog2();
}


BOOL CSQuickLine::OnInitDialog2() 		//FP
{
//DEADCODE RDH 18/01/00 	m_IDC_FLIGHTS.SetCircularStyle(TRUE);
//DEADCODE RDH 18/01/00 	m_IDC_TYPE.SetCircularStyle(TRUE);
//DEADCODE RDH 18/01/00 	m_IDC_ALT.SetCircularStyle(TRUE);
//DEADCODE RDH 18/01/00 	m_IDC_SKILL.SetCircularStyle(TRUE);
//DEADCODE RDH 18/01/00 

	CRButton* currfl=GETDLGITEM(IDC_PILOTEDFLAG);
//DeadCode AMM 14Oct98 	if (_DPlay.CurrPlayers == 0)
	if (!RFullPanelDial::incomms)								//AMM 14Oct98
	{
		currfl->ShowWindow(SW_SHOW);
		if(CSQuick1::quickdef.plside==packnum && CSQuick1::quickdef.plwave==wavenum && CSQuick1::quickdef.plgrp==groupnum)
			currfl->SetPressed(true);
	}else
	{
		currfl->ShowWindow(SW_HIDE);
	}
	CRStatic* desc=GETDLGITEM(IDC_GRPDESC);
	desc->SetString(LoadResString(fields->descID));
	CRCombo* combo=GETDLGITEM(IDC_ALT);
	if (fields->alt==0)
	{

	}
	else
	if (fields->alt<=0)
	{
		combo->AddString(LoadResString(-fields->alt));
		combo->SetIndex(0);
	}
	else
	{
		int altind=(fields->alt+METRES100)*10/(Save_Data.alt.mediummm*Save_Data.alt.mediumstepsize)-Save_Data.alt.minstepcount;
		if (altind<0)
			altind=0;													  //JIM 14/05/99
		else
			if (altind>=Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount)
				altind=Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount-1; //JIM 14/05/99
		combo->MakeNumList(Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount,
							Save_Data.alt.minstepcount*Save_Data.alt.mediumstepsize,
							Save_Data.alt.mediumstepsize
						)->SetIndex(altind);
	}
	combo=GETDLGITEM(IDC_SKILL);
	combo->RESCOMBO(SKILL_NOVICE,6)->SetIndex(fields->skill/SKILL_STAGE);

	SetVariableBits();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CSQuickLine::SetVariableBits(bool Icanbeplayer)
{	//the input flag set false forces redrawing with player deselected rather than selected
	CRCombo* combo=GETDLGITEM(IDC_TYPE);
	combo->Clear();
	int sqstart,sqcount;
	bool Iamplayer=(	Icanbeplayer 
		&&	packnum==CSQuick1::quickdef.plside
		&&	wavenum==CSQuick1::quickdef.plwave
		&&	groupnum==CSQuick1::quickdef.plgrp	);
	switch (fields->Duty())
	{
	default_neverreferenced;
	case	Q::QFD_BRIT_FIGHTER:
	case	Q::QFD_BRIT_LONE:
		sqstart=PT_BRIT_FLYABLE;sqcount=IDSL_SPIT_A;	break;
	case	Q::QFD_BRIT_BOMBER_PLAYER_ONLY:
		INT3;
//		sqstart=PT_F80;sqcount=3;	break;
	case	Q::QFD_BRIT_BOMBER_AUTO_ONLY:
		sqstart=PT_BRIT_NONFLY;sqcount=IDSL_DEFIANT;	break;
	case	Q::QFD_BRIT_PLAYER_AUTO:
	case	Q::QFD_BRIT_PLAYER_AUTO_IS_AUTO:
		sqstart=PT_DEFIANT;sqcount=IDSL_ALLAC;	
		if (Iamplayer || RFullPanelDial::incomms)	sqcount=IDSL_SPIT_A;
		break;
	case	Q::QFD_GERM_FIGHTER:
		sqstart=PT_GER_FLYABLE;sqcount=IDSL_ME109_110;	break;
	case	Q::QFD_GERM_LONE:
		sqstart=PT_GER_FLYABLE;sqcount=IDSL_ME109_JU87;	break;
	case	Q::QFD_GERM_BOMBER_PLAYER_ONLY:
		sqstart=PT_ME109;sqcount=IDSL_ME109_JU87;	break;
	case	Q::QFD_GERM_BOMBER_PLAYER_AUTO:
	case	Q::QFD_GERM_BOMBER_PLAYER_AUTO_IS_AUTO:
		sqstart=PT_ME110;sqcount=IDSL_GERMBMB;	
		if (Iamplayer || RFullPanelDial::incomms)	sqcount=2;
		break;
	case	Q::QFD_GERM_BOMBER_AUTO_ONLY:
		sqstart=PT_GER_NONFLY;sqcount=IDSL_DO17;	break;
		
	case	Q::QFD_FIXED_PLAYER:
	case	Q::QFD_FIXED_AUTO:
	case	Q::QFD_FIXED_NUM_PLAYER:
	case	Q::QFD_FIXED_NUM_AUTO:
		sqstart=fields->actype;sqcount=1;	break;
	}
	int line=0;
	int min=0;
	if (Iamplayer)
		min=1;
	if (!fields->AllowZero())
		min=1;
	for (int sq=sqstart;sqcount;sq++,sqcount--)
	{
		int avail=CSQuick1::quickdef.SpareFlights(sq);
		if (sq==fields->actype)
		{
			avail+=fields->flights;
			if (avail>3)
				avail=CSQuick1::MaxFlights(PlaneTypeSelect(sq));					//MS 02/05/00
//DEADCODE MS 02/05/00 			if (sq>=PT_GER_FLYABLE && avail>3)
//DEADCODE MS 02/05/00 				avail=3;
//DEADCODE MS 02/05/00 			elseif (avail>4)
//DEADCODE MS 02/05/00 				avail=4;
		}
		if (avail>=min)
		{
			combo->AddString(RESLIST(MK_SPIT_A,sq)); 
			aclines[line++]=sq;
		}
	}
	int l;
	for (l=0;l<line;l++)
		breakif (aclines[l]==fields->actype);
	if (l==line)
		assert (l!=line);
	combo->SetIndex(l);


	combo=GETDLGITEM(IDC_FLIGHTS);
	combo->Clear();
	if (	fields->Duty()==Q::QFD_FIXED_NUM_PLAYER 
		||	fields->Duty()==Q::QFD_FIXED_NUM_AUTO
		||	fields->Duty()==Q::QFD_BRIT_LONE
		||	fields->Duty()==Q::QFD_GERM_LONE
		)
	{
		combo->MakeNumList(1,fields->flights);
		combo->SetIndex(0);
	}
	else
	{
		ULong numflights=CSQuick1::quickdef.SpareFlights(fields->actype)+fields->flights;
		ULong index=fields->flights;

// for LW if combo is 0/1 to 4 then make it 0/1 to 3

		if (numflights>3)
		{
			numflights=CSQuick1::MaxFlights(PlaneTypeSelect(fields->actype));					//MS 02/05/00

//DEADCODE MS 02/05/00 			if (packnum)
//DEADCODE MS 02/05/00 				numflights=3;
//DEADCODE MS 02/05/00 			else
//DEADCODE MS 02/05/00 				numflights=4;
		}

// check to make sure that index/number of flights are valid and reduce if necessary

		if (fields->flights>numflights)
		{
			index=numflights;
			fields->flights=numflights;
		}
	

		if (min==0) 
		{
//DEADCODE AMM 06/03/00 			combo->MakeNumList(CSQuick1::quickdef.SpareFlights(fields->actype)+fields->flights+1,0)
//DEADCODE AMM 06/03/00 				->SetIndex(fields->flights);
			combo->MakeNumList(numflights+1,0);
			combo->SetIndex(index);
		}
		else
		{
//DEADCODE AMM 06/03/00 			combo->MakeNumList(CSQuick1::quickdef.SpareFlights(fields->actype)+fields->flights,1)
//DEADCODE AMM 06/03/00 				->SetIndex(fields->flights-1);
			combo->MakeNumList(numflights,1);
			combo->SetIndex(index-1);
		}
	}
	CRButton* currfl=GETDLGITEM(IDC_PILOTEDFLAG);
		switch (fields->Duty())
		{
		case	Q::QFD_BRIT_FIGHTER:
		case	Q::QFD_BRIT_LONE:
			currfl->SetDisabled(false);
			currfl->SetNormalFileNum(B_ICON_RAF_INTERECEPT);
		break;
		case	Q::QFD_BRIT_BOMBER_PLAYER_ONLY:
			INT3;
	//		sqstart=PT_F80;sqcount=3;	break;
		case	Q::QFD_BRIT_BOMBER_AUTO_ONLY:
			currfl->SetNormalFileNum(B_ICON_RAF_PATROL);
			currfl->SetDisabled(true);
		break;
		case	Q::QFD_BRIT_PLAYER_AUTO:
			currfl->SetNormalFileNum(B_ICON_RAF_INTERECEPT);
			currfl->SetDisabled(false);
		break;
		case	Q::QFD_BRIT_PLAYER_AUTO_IS_AUTO:
			currfl->SetNormalFileNum(B_ICON_RAF_PATROL);
			currfl->SetDisabled(true);
		break;
		case	Q::QFD_GERM_FIGHTER:
		case	Q::QFD_GERM_LONE:
			currfl->SetNormalFileNum(B_ICON_LW_FIGHTER);
			currfl->SetDisabled(false);
		break;
		case	Q::QFD_GERM_BOMBER_PLAYER_ONLY:
			currfl->SetNormalFileNum(B_ICON_LW_BOMBER);
			currfl->SetDisabled(false);
		break;
		case	Q::QFD_GERM_BOMBER_PLAYER_AUTO:
			currfl->SetNormalFileNum(B_ICON_LW_BOMBER);
			currfl->SetDisabled(false);
		break;
		case	Q::QFD_GERM_BOMBER_PLAYER_AUTO_IS_AUTO:
			currfl->SetNormalFileNum(B_ICON_LW_BOMBER);
			currfl->SetDisabled(false);
		break;
		case	Q::QFD_GERM_BOMBER_AUTO_ONLY:
			currfl->SetNormalFileNum(B_ICON_LW_BOMBER);
			currfl->SetDisabled(false);
		break;
		case	Q::QFD_FIXED_PLAYER:
		case	Q::QFD_FIXED_NUM_PLAYER:
			if (fields->actype<PT_BRIT_NONFLY)
				currfl->SetNormalFileNum(B_ICON_RAF_PATROL);
			elseif (fields->actype<PT_GER_FLYABLE)
	 			currfl->SetNormalFileNum(B_ICON_RAF_PATROL);
			elseif (fields->actype<PT_JU87)
				currfl->SetNormalFileNum(B_ICON_LW_FIGHTER);
			else
				currfl->SetNormalFileNum(B_ICON_LW_BOMBER);
			currfl->SetDisabled(false);
		break;
		case	Q::QFD_FIXED_AUTO:
		case	Q::QFD_FIXED_NUM_AUTO:
			if (fields->actype<PT_BRIT_NONFLY)
				currfl->SetNormalFileNum(B_ICON_RAF_PATROL);
			elseif (fields->actype<PT_GER_FLYABLE)
	 			currfl->SetNormalFileNum(B_ICON_RAF_PATROL);
			elseif (fields->actype<PT_JU87)
				currfl->SetNormalFileNum(B_ICON_LW_FIGHTER);
			else
				currfl->SetNormalFileNum(B_ICON_LW_BOMBER);
			currfl->SetDisabled(true);
		break;
		}
	if (Iamplayer)
	{
		currfl->SetPressed(true);
	}
	else
	{
		currfl->SetPressed(false);
	}
}


BEGIN_MESSAGE_MAP(CSQuickLine, CDialog)
	//{{AFX_MSG_MAP(CSQuickLine)
	ON_WM_CANCELMODE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSQuickLine message handlers

BEGIN_EVENTSINK_MAP(CSQuickLine, CDialog)
    //{{AFX_EVENTSINK_MAP(CSQuickLine)
	ON_EVENT(CSQuickLine, IDC_TYPE, 1 /* TextChanged */, OnTextChangedType, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuickLine, IDC_SKILL, 1 /* TextChanged */, OnTextChangedSkill, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuickLine, IDC_FLIGHTS, 1 /* TextChanged */, OnTextChangedFlights, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuickLine, IDC_ALT, 1 /* TextChanged */, OnTextChangedAlt, VTS_BSTR VTS_I2)
	ON_EVENT(CSQuickLine, IDC_PILOTEDFLAG, 1 /* Clicked */, OnClickedPilotedflag, VTS_NONE)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CSQuickLine::OnTextChangedType(LPCTSTR text, short index) 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_TYPE);
//DeadCode JIM 20Oct00 	CRButton* but=GETDLGITEM(IDC_PILOTEDFLAG);
	int newtype=aclines[combo->GetIndex()];
	switch (fields->Duty())
	{
	case	Q::QFD_BRIT_FIGHTER:
	case	Q::QFD_BRIT_BOMBER_PLAYER_ONLY:
	case	Q::QFD_BRIT_BOMBER_AUTO_ONLY:
	case	Q::QFD_GERM_FIGHTER:
	case	Q::QFD_GERM_BOMBER_PLAYER_ONLY:
	case	Q::QFD_GERM_BOMBER_AUTO_ONLY:
	case	Q::QFD_GERM_LONE:
	case	Q::QFD_BRIT_LONE:
	break;
	case	Q::QFD_BRIT_PLAYER_AUTO:
	case	Q::QFD_BRIT_PLAYER_AUTO_IS_AUTO:
		if (newtype>=PT_DEFIANT)
			fields->SetDuty(Q::QFD_BRIT_PLAYER_AUTO_IS_AUTO);
		else
			fields->SetDuty(Q::QFD_BRIT_PLAYER_AUTO);
		break;
	case	Q::QFD_GERM_BOMBER_PLAYER_AUTO:
	case	Q::QFD_GERM_BOMBER_PLAYER_AUTO_IS_AUTO:
		if (newtype>=PT_DO17)
			fields->SetDuty(Q::QFD_GERM_BOMBER_PLAYER_AUTO_IS_AUTO);
		else
			fields->SetDuty(Q::QFD_GERM_BOMBER_PLAYER_AUTO);
		break;
	case	Q::QFD_FIXED_PLAYER:
	case	Q::QFD_FIXED_AUTO:
	case	Q::QFD_FIXED_NUM_PLAYER:
	case	Q::QFD_FIXED_NUM_AUTO:
		return;		//should not happen!!!
	}
	//should always be legal, now!
	if (newtype!=fields->actype)
	{
		int availcount=CSQuick1::quickdef.SpareFlights(newtype);
//DeadCode JIM 20Oct00 		int oldtype=fields->actype;
		fields->actype=newtype;
		int oldcount=fields->flights;
		fields->flights=0;
		if (oldcount>availcount)
			oldcount=availcount;
		fields->flights=oldcount;
		CSQuick1::quickdef.FixOtherLines(newtype);
		CSQuick1::quickdef.parent->MakeFlightCombo();
	}
	SetVariableBits();
}

void CSQuickLine::OnTextChangedSkill(LPCTSTR text, short index) 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_SKILL);
	fields->skill=combo->GetIndex()*SKILL_STAGE;
}

void CSQuickLine::OnTextChangedFlights(LPCTSTR text, short index) 
{
	// TODO: Add your control notification handler code here
	CRCombo* combo=GETDLGITEM(IDC_FLIGHTS);
//DeadCode JIM 20Oct00 	bool oldcount=(fields->flights==0);
	if (fields->AllowZero()											  //RDH 03/03/99
		&&	(	packnum!=CSQuick1::quickdef.plside
			||	wavenum!=CSQuick1::quickdef.plwave
			||	groupnum!=CSQuick1::quickdef.plgrp
		)	)
		fields->flights=combo->GetIndex();
	else
		fields->flights=combo->GetIndex()+1;
	CSQuick1::quickdef.FixOtherLines(fields->actype);
	CSQuick1::quickdef.parent->MakeFlightCombo();
	SetVariableBits();
}

void CSQuickLine::OnTextChangedAlt(LPCTSTR text, short index) 
{
	//this is the setup code that needs to be reversed
//	int altind=fields->alt*10/(Save_Data.alt.mediummm*Save_Data.alt.mediumstepsize)-Save_Data.alt.minstepcount;
//	combo->MakeNumList(Save_Data.alt.maxstepcount-Save_Data.alt.minstepcount,
//						Save_Data.alt.mediumstepsize,
//						Save_Data.alt.minstepcount*Save_Data.alt.mediumstepsize
//					)->SetIndex(altind);
	CRCombo* combo=GETDLGITEM(IDC_ALT);
	fields->alt=(combo->GetIndex()+Save_Data.alt.minstepcount)*Save_Data.alt.mediumstepsize
		*Save_Data.alt.mediummm/10+1;
}

void CSQuickLine::OnCancelMode() 
{
	CDialog::OnCancelMode();
	
	// TODO: Add your message handler code here
	
}

void	CSQuickLine::SetIconPressed(bool turnon)
{
	if (!this)
		return;
	SetVariableBits(turnon);
}
void CSQuickLine::RecalcFlightsCombo(int spares) 
{
	if (!this)
		return;
	SetVariableBits();
}

void CSQuickLine::OnClickedPilotedflag() 
{
	// TODO: Add your control notification handler code here
	if	(!(CSQuick1::quickdef.plside==packnum && CSQuick1::quickdef.plwave==wavenum && CSQuick1::quickdef.plgrp==groupnum))
	{
		if (CSQuick1::quickdef.line[packnum][wavenum][groupnum].flights!=0)
		{
			CSQuick1::quickdef.line[CSQuick1::quickdef.plside][CSQuick1::quickdef.plwave][CSQuick1::quickdef.plgrp].dialog->SetIconPressed(false);
			CSQuick1::quickdef.plside=packnum;
			CSQuick1::quickdef.plwave=wavenum;
			CSQuick1::quickdef.plgrp=groupnum;
			SetVariableBits();
			CSQuick1::quickdef.parent->MakeFlightCombo();
		}
		else
			GETDLGITEM(IDC_PILOTEDFLAG)->SetPressed(false);

// in quick missions only the wavenum or the groupnum are valid, if one value is >0
// then the other must be 0

		assert(!(groupnum && wavenum));
	}
	else
	{	//turn it back on!
		CRButton* currfl=GETDLGITEM(IDC_PILOTEDFLAG);
		currfl->SetPressed(true);
	}
}

void CSQuickLine::OnDestroy() 
{
	CDialog::OnDestroy();
	fields->dialog=NULL;
	// TODO: Add your message handler code here
	
}

bool QuickFields::AllowZero()
{
	if (RFullPanelDial::incomms)
		return false;

	return (duty&QFD_ALLOW_ZERO_FL)!=0;
}
