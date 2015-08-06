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

// RowanDialog: // QuickPar.cpp : implementation file
//

#include "stdafx.h"
#include "bob.h"
#include "QuickPar.h"
#include "time.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// QuickParameters dialog


RDialog*	QuickParameters::Make()
{
	return
		MakeTopDialog(::Place(POSN_CENTRE,POSN_CENTRE),
			DialBox(FIL_NULL,new QuickParameters())
			);
}


QuickParameters::QuickParameters(CWnd* pParent /*=NULL*/)
	: RowanDialog(QuickParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(QuickParameters)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	targtype = 0;
	targentry = 0;
}


void QuickParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(QuickParameters)
	DDX_Control(pDX, IDC_TARGNAME, m_IDC_TARGNAME);
	DDX_Control(pDX, IDC_TARGTYPE, m_IDC_TARGTYPE);
	DDX_Control(pDX, IDC_TIME, m_IDC_TIME);
	DDX_Control(pDX, IDC_CLOUD, m_IDC_CLOUD);
	DDX_Control(pDX,IDC_NAME,m_IDC_NAME);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(QuickParameters, CDialog)
	//{{AFX_MSG_MAP(QuickParameters)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// QuickParameters message handlers

BEGIN_EVENTSINK_MAP(QuickParameters, CDialog)
    //{{AFX_EVENTSINK_MAP(QuickParameters)
	ON_EVENT(QuickParameters, IDC_TARGNAME, 1 /* TextChanged */, OnTextChangedTargname, VTS_BSTR VTS_I2)
	ON_EVENT(QuickParameters, IDC_TARGTYPE, 1 /* TextChanged */, OnTextChangedTargtype, VTS_BSTR VTS_I2)
	ON_EVENT(QuickParameters, IDC_CLOUD, 1 /* TextChanged */, OnTextChangedCloud, VTS_BSTR VTS_I2)
	ON_EVENT(QuickParameters, IDC_TIME, 1 /* TextChanged */, OnTextChangedTime, VTS_BSTR VTS_I2)
	ON_EVENT(QuickParameters, IDC_NAME, 2 /* TextChanged */, OnTextChangedName, VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void	QuickParameters::TargNameCombo()
{
	CRCombo* combo;

	combo=GETDLGITEM(IDC_TARGNAME);
	combo->Clear();
	combo->AddString(GetTargName(CSQuick1::quickdef.targets[targtype][0]));
	if (CSQuick1::quickdef.targets[targtype][1])
	combo->AddString(GetTargName(CSQuick1::quickdef.targets[targtype][1]));
	if (CSQuick1::quickdef.targets[targtype][2])
		combo->AddString(GetTargName(CSQuick1::quickdef.targets[targtype][2]));
	if (CSQuick1::quickdef.targets[targtype][3])
		combo->AddString(GetTargName(CSQuick1::quickdef.targets[targtype][3]));
	combo->SetIndex(targentry);
}

void	QuickParameters::ReinitCombo()
{
	CRCombo* combo;
	targtype=0,targentry=0;
	for (int t=0;t<4;t++)
		for (int e=0;e<4;e++)
			if(CSQuick1::quickdef.targets[t][e]==CSQuick1::quickdef.target)
				targtype=t,targentry=e;

	combo=GETDLGITEM(IDC_TARGTYPE);
	combo->Clear();
	combo->AddString(LoadResString(CSQuick1::quickdef.targtypeIDs[0]));
	if (CSQuick1::quickdef.targtypeIDs[1])
		combo->AddString(LoadResString(CSQuick1::quickdef.targtypeIDs[1]));
	if (CSQuick1::quickdef.targtypeIDs[2])
		combo->AddString(LoadResString(CSQuick1::quickdef.targtypeIDs[2]));
	if (CSQuick1::quickdef.targtypeIDs[3])
		combo->AddString(LoadResString(CSQuick1::quickdef.targtypeIDs[3]));
	if (CSQuick1::quickdef.targtypeIDs[0])
		combo->SetIndex(targtype);

	TargNameCombo();


	SWord Latitude = 51;												//RDH 25/02/00
	MMC.Sky.SetMissionDawnDusk(Latitude, MMC.currdate, MMC.dawntime, MMC.dusktime);

	int timeindex = CSQuick1::quickdef.time;
	SetTime(timeindex);
	

	combo=GETDLGITEM(IDC_TIME);
	combo->Clear();
	combo->RESCOMBO(DAWN,4)->SetIndex(timeindex);

	int weatherindex = CSQuick1::quickdef.weather;
	SetWeather(weatherindex);


	combo=GETDLGITEM(IDC_CLOUD);
	combo->Clear();
	combo->RESCOMBO(CLEARSKY,4)->SetIndex(weatherindex);

}

BOOL QuickParameters::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GETDLGITEM(IDC_NAME)->SetCaption("\b\t\n\v");
//	if (Save_Data.CommsPlayerName[0])
	{
		GETDLGITEM(IDC_NAME)->SetCaption(Save_Data.CommsPlayerName);
	}
#ifdef BOB_DEMO_VER
	GETDLGITEM(IDC_TIME)->ShowWindow(false);
#endif
	ReinitCombo();


	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void QuickParameters::OnTextChangedName(LPTSTR text) 
{
	// TODO: Add your control notification handler code here
//	CString	buffer,buffer2;
//	CREdit* editbox;
//	editbox=GETDLGITEM(IDC_NAME);
//	buffer = editbox->GetCaption();
//	buffer2 = buffer.GetBufferSetLength(PLAYERNAMELEN-1);	
//	editbox->SetWindowText(buffer);
	trunc(text,PLAYERNAMELEN - 1);	
	strcpy(Save_Data.CommsPlayerName,text);
 	strcpy(MMC.PlayerName,text);
}

void QuickParameters::OnTextChangedTargname(LPCTSTR Caption, short index) 
{
	targentry=GETDLGITEM(IDC_TARGNAME)->GetIndex();
	CSQuick1::quickdef.target=CSQuick1::quickdef.targets[targtype][targentry];
	ReinitCombo();
}

void QuickParameters::OnTextChangedTargtype(LPCTSTR Caption, short index) 
{
	targtype=GETDLGITEM(IDC_TARGTYPE)->GetIndex();
	targentry=0;
	CSQuick1::quickdef.target=CSQuick1::quickdef.targets[targtype][targentry];

	TargNameCombo();
}

void QuickParameters::OnTextChangedCloud(LPCTSTR Caption, short index) 
{
	CSQuick1::quickdef.weather = index;
	SetWeather(index);

}
void QuickParameters::SetWeather(int index)
{
	switch(index)
	{
		case	0:	  //clear
		{
			MMC.Sky.SetMissionClouds(	0,0,0,
										0,0,0,
										0,0,0,
										0,0,0);
			break;
		}
		case	1:	//patchy
		{
			MMC.Sky.SetMissionClouds(	FT_15000,FT_16000,120,
										0,0,0,
										0,0,0,
										0,0,0
										);
			break;
		}
		case	2:	//low cloud
		{
			MMC.Sky.SetMissionClouds(	FT_4000,FT_5000,240,
										0,0,0,
										0,0,0,
										0,0,0);
			break;
		}
		case	3:	//high cloud
		{
			MMC.Sky.SetMissionClouds(	FT_24000,FT_25000,150,
										0,0,0,
										0,0,0,
										0,0,0);
			break;
		}
//DeadCode RDH 9Aug00 		case	4:
//DeadCode RDH 9Aug00 		{
//DeadCode RDH 9Aug00 			MMC.Sky.SetMissionClouds(	FT_15000,FT_16000,128,
//DeadCode RDH 9Aug00 										0,0,0,
//DeadCode RDH 9Aug00 										0,0,0,
//DeadCode RDH 9Aug00 										0,0,0);
//DeadCode RDH 9Aug00 			break;
//DeadCode RDH 9Aug00 		}
	}
	
}
void QuickParameters::OnTextChangedTime(LPCTSTR Caption, short index) 
{
	CSQuick1::quickdef.time = index;
	SetTime(index);
}
void QuickParameters::SetTime(int index)
{
	switch(index)
	{
		case	0:
		{
			MMC.currtime = MMC.dawntime;
			break;
		}
		case	1:
		{
			MMC.currtime = HR10;
			break;
		}
		case	2:
		{
			MMC.currtime = HR14;
			break;
		}
		case	3:
		{
			MMC.currtime = MMC.dusktime;
			break;
		}
	}
}

void QuickParameters::OnDestroy() 
{
	CREdit* e=GETDLGITEM(IDC_NAME);
	CString name;

	name=e->GetCaption();
	strcpy(Save_Data.CommsPlayerName,name);

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	
}
