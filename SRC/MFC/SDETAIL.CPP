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

// SDetaimfc\l.cpp : implementation file
//

#include "stdafx.h"
#include "mig.h"
#include "SDetail.h"
#include "rcombo.h"
#include "savegame.h"
#include "display.h"
#include "overlay.h"
#include "gameset.h"
#include "comms.h"
#include "winmove.h"
#include "replay.h"
extern void GetDrivers(int&,char**&);
extern void GetModes(int&,SDrvrModes*&);

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDetail dialog


CSDetail::CSDetail(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSDetail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSDetail)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSDetail)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_RSTATICCTRL5,m_IDC_RSTATICCTRL5);
	DDX_Control(pDX,IDC_RSTATICCTRL6,m_IDC_RSTATICCTRL6);
	DDX_Control(pDX,IDC_RSTATICCTRL7,m_IDC_RSTATICCTRL7);
	DDX_Control(pDX,IDC_RSTATICCTRL8,m_IDC_RSTATICCTRL8);
	DDX_Control(pDX,IDC_RSTATICCTRL9,m_IDC_RSTATICCTRL9);
	DDX_Control(pDX,IDC_RSTATICCTRL10,m_IDC_RSTATICCTRL10);
	DDX_Control(pDX,IDC_RSTATICCTRL12,m_IDC_RSTATICCTRL12);
	DDX_Control(pDX,IDC_CBO_DISPLAYDRIVERS,m_IDC_CBO_DISPLAYDRIVERS);
	DDX_Control(pDX,IDC_CBO_RESOLUTIONS,m_IDC_CBO_RESOLUTIONS);
	DDX_Control(pDX,IDC_CBO_AUTOFRAMERATE,m_IDC_CBO_AUTOFRAMERATE);
	DDX_Control(pDX,IDC_CBO_LOWESTFRAMERATE,m_IDC_CBO_LOWESTFRAMERATE);
	DDX_Control(pDX,IDC_CBO_DISPLAYDRIVERS,m_IDC_CBO_DISPLAYDRIVERS);
//DEADCODE JIM 12/06/00 	DDX_Control(pDX,IDC_CBO_RESOLUTIONS,m_IDC_CBO_RESOLUTIONS);
	DDX_Control(pDX,IDC_CBO_GAMMACORRECTION,m_IDC_CBO_GAMMACORRECTION);
	DDX_Control(pDX,IDC_CBO_GROUNDSHADING,m_IDC_CBO_GROUNDSHADING);
	DDX_Control(pDX,IDC_CBO_ITEMSHADING,m_IDC_CBO_ITEMSHADING);
//DEADCODE RDH 15/02/99 	DDX_Control(pDX,IDC_CBO_SHOWIRONWORK,m_IDC_CBO_SHOWIRONWORK);
	DDX_Control(pDX,IDC_CBO_REFLECTIONS,m_IDC_CBO_REFLECTIONS);
	DDX_Control(pDX,IDC_RSTATICCTRL48,m_IDC_RSTATICCTRL48);
	DDX_Control(pDX,IDC_CBO_WEATHER,m_IDC_CBO_WEATHER);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSDetail, CDialog)
	//{{AFX_MSG_MAP(CSDetail)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDetail message handlers	  //IDS_L_DIST_NEAR

#define OPTIONS	\
	SETFIELD(CHAR(gammacorrection,0,1),									IDC_CBO_GAMMACORRECTION,RESCOMBO(BLMHT_BOT,5),NOLEVEL)	\
	SETFIELD(BIT(detail_3d,DETAIL3D_AUTODETAIL),						IDC_CBO_AUTOFRAMERATE,RESCOMBO(OFF,2),	NOLEVEL)	\
	SETFIELD(CHAR(desiredfps,5,1),										IDC_CBO_LOWESTFRAMERATE,MakeNumList(30,5),NOLEVEL)	\
	SETFIELD(BIT(detail_3d,DETAIL3D_GROUNDSHADING),						IDC_CBO_GROUNDSHADING,RESCOMBO(OFF,2),	NOLEVEL)	\
	SETFIELD(CHAR(itemShading,0,1),										IDC_CBO_ITEMSHADING,RESCOMBO(OFF,3),	NOLEVEL)	\
	SETFIELD(BIT(cockpit3Ddetail,COCK3D_SKYIMAGES),						IDC_CBO_REFLECTIONS,RESCOMBO(OFF,2),	NOLEVEL)	\
	SETFIELD(ADDBIT(hardwareconfig,HW_FLUFFYCLOUDS,HW_WEATHEREFFECTS),	IDC_CBO_WEATHER,RESCOMBO(WEATHER_OFF,2),		NOLEVEL)	\

int	ironlevels;

//DeadCode JON 20Sep00 inline bool IsValidMode(SModeFlags* pmf,UWord w,UWord h)
//DeadCode JON 20Sep00 {
//DeadCode JON 20Sep00 	if (w*3!=h*4) return false;
//DeadCode JON 20Sep00 	for (int x=0;x<SModeFlags::Max_Modes;x++) if (pmf->widths[x]==w) return true;
//DeadCode JON 20Sep00 	return false;
//DeadCode JON 20Sep00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnInitDialog
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
BOOL CSDetail::OnInitDialog()
{
//DEADCODE PD 03/12/99 	static char modeString[32];

#define	SG2C_DISPLAY	setlevel
#include "sg2combo.h"
	
	CDialog::OnInitDialog();

	if (_DPlay.PlayerCreated)									//AMM 12Jul99
	{															//AMM 12Jul99
//DeadCode AMM 16Nov99 		_DPlay.UISendInPrefsMessage();							//AMM 12Jul99
//DeadCode AMM 16Nov99 		DPlay::H2H_Player[_DPlay.mySlot].status=CPS_PREFS;		//AMM 12Jul99
		_DPlay.SendStatusChange(DPlay::CPS_PREFS);
	}															//AMM 12Jul99

	if (RFullPanelDial::gamestate!=RFullPanelDial::TITLE)		//AMM 31Mar99
		_Replay.prefscheck=true;								//AMM 31Mar99
	
	if (Save_Data.desiredfps<5) Save_Data.desiredfps=20;

	UIDrivers uiDrivers;
	UIModes uiModes;
	int selected;
	CRCombo* combo;
	CString temp;
	CLib3D *g_lpLib3d;

	g_lpLib3d=Master_3d.g_lpLib3d;

	uiDrivers.size=sizeof(UIDrivers);
	g_lpLib3d->GetDrivers(uiDrivers); //PD 06/12/99
	
	combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);

	selected = 0;
	for (int i=0;i<uiDrivers.numDrivers;i++)
	{
		if (uiDrivers.driver[i].hDriver==Save_Data.hDriver)
			selected=i;
		combo->AddString((LPCTSTR)uiDrivers.driver[i].name);
	}
	combo->SetIndex(selected);

	uiModes.size=sizeof(UIModes);
	g_lpLib3d->GetModes(uiDrivers.driver[selected].hDriver,uiModes);

	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);

	selected=0;
	for (i=0;i<uiModes.numModes;i++)
	{
		if (uiModes.mode[i].hMode==Save_Data.hMode)
		{
			selected=i;
		}
		char rezStr[64];
		sprintf(rezStr,"%d x %d x %d",uiModes.mode[i].width,uiModes.mode[i].height,uiModes.mode[i].bpp);
		combo->AddString(rezStr);
	}
	combo->SetIndex(selected);

//DEADCODE PD 03/12/99 	//fill in display drivers field
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	int driverCount,modesCount,selectedDriver,driver_index;
//DEADCODE PD 03/12/99 	char** driverNames;
//DEADCODE PD 03/12/99 	SDrvrModes* driverModes;
//DEADCODE PD 03/12/99 	GetDrivers(driverCount,driverNames);
//DEADCODE PD 03/12/99 	GetModes(modesCount,driverModes);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	CString pdd;
//DEADCODE PD 03/12/99 	CRCombo* combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	//the first entry must always be the 'Software Display Driver'
//DEADCODE PD 03/12/99 	pdd.LoadString(IDS_SOFTWAREDRIVER);
//DEADCODE PD 03/12/99 	combo->AddString(pdd);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	//the second entry must always be 'Primary Display Driver' if it is 3D capeable
//DEADCODE PD 03/12/99 	if (!Save_Data.fNoHardwareAtAll && Save_Data.sd.fFirstHardIsPrimary)
//DEADCODE PD 03/12/99 	{
//DEADCODE PD 03/12/99 		pdd.LoadString(IDS_PRIMARYDISPLAYDRIVER);
//DEADCODE PD 03/12/99 		combo->AddString(pdd);
//DEADCODE PD 03/12/99 	}
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	//driver count doesn't include primary!
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	for (SLong x=0;x<driverCount;x++) 
//DEADCODE PD 03/12/99 		combo->AddString(driverNames[x]);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	if (Save_Data.fSoftware)					selectedDriver=0;
//DEADCODE PD 03/12/99 	else if (Save_Data.sd.fFirstHardIsPrimary)	selectedDriver=Save_Data.dddriver+2; //-1 to ... => 1 to ...+2
//DEADCODE PD 03/12/99 	else 										selectedDriver=Save_Data.dddriver+1; // 0 to ... => 1 to ...+1
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	driver_index=Save_Data.dddriver;
//DEADCODE PD 03/12/99 //	if (Save_Data.fNoHardwareAtAll)
//DEADCODE PD 03/12/99 //b		driver_index++;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	combo->SetIndex(selectedDriver);
//DEADCODE PD 03/12/99 	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	SModeFlags* modeFlags;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	if (Save_Data.fSoftware)					modeFlags=&Save_Data.sd.soft_modes;
//DEADCODE PD 03/12/99 	else if (Save_Data.sd.fFirstHardIsPrimary)	modeFlags=Save_Data.sd.hard_modes+selectedDriver-1;
//DEADCODE PD 03/12/99 	else										modeFlags=Save_Data.sd.hard_modes+selectedDriver;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	SLong rez_index=0,add_index=0;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	for (x=0;x<modesCount;x++)
//DEADCODE PD 03/12/99 		if (driverModes[x].driverNo-1==driver_index &&
//DEADCODE PD 03/12/99 			driverModes[x].displayBPP==16 &&
//DEADCODE PD 03/12/99 			IsValidMode(modeFlags,driverModes[x].displayWidth,driverModes[x].displayHeight))
//DEADCODE PD 03/12/99 		{
//DEADCODE PD 03/12/99 		 	if (Save_Data.screenresolution==add_index)	rez_index=add_index;
//DEADCODE PD 03/12/99 			sprintf(modeString,"%d X %d\0",driverModes[x].displayWidth,driverModes[x].displayHeight);
//DEADCODE PD 03/12/99 			combo->AddString(CString(modeString));
//DEADCODE PD 03/12/99 			add_index++;
//DEADCODE PD 03/12/99 		}
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	combo->SetIndex(rez_index);

	OPTIONS
	ThreeDeePref_Timer=SetTimer(DPlay::TIMER_PREFS3D,0,NULL);

	if	(		(RFullPanelDial::incomms)
			&&	(_DPlay.UIPlayerType==DPlay::PLAYER_GUEST)
		)
	{
		combo=GETDLGITEM(IDC_CBO_WEATHER);
		combo->SetEnabled(false);
	}
	else
	{
		combo=GETDLGITEM(IDC_CBO_WEATHER);
		combo->SetEnabled(true);
	}
//DEADCODE RDH 25/11/99 	m_IDC_CBO_DISPLAYDRIVERS.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 	m_IDC_CBO_RESOLUTIONS.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 	m_IDC_CBO_GAMMACORRECTION.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 	m_IDC_CBO_AUTOFRAMERATE.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 	m_IDC_CBO_LOWESTFRAMERATE.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 	m_IDC_CBO_GROUNDSHADING.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 	m_IDC_CBO_ITEMSHADING.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 	m_IDC_CBO_REFLECTIONS.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 	m_IDC_CBO_WEATHER.SetCircularStyle(TRUE);
//DEADCODE RDH 25/11/99 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


#define	SG2C_WRITEBACK
#include "sg2combo.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnClose
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void CSDetail::OnClose()
{
	OPTIONS	
	CDialog::OnClose();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnDestroy
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void CSDetail::OnDestroy()
{
	KillTimer(ThreeDeePref_Timer);
	CDialog::OnDestroy();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreDestroyPanel
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void CSDetail::PreDestroyPanel()
{
	UIDrivers	uiDrivers;
	UIModes		uiModes;
	int			selected;
	CLib3D		*g_lpLib3d;
 	CRCombo		*combo;

	OPTIONS																//DAW 28/03/00


	g_lpLib3d=Master_3d.g_lpLib3d;
	uiDrivers.size=sizeof(UIDrivers);
	g_lpLib3d->GetDrivers(uiDrivers);

	combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);
	selected=combo->GetIndex();
	Save_Data.hDriver=uiDrivers.driver[selected].hDriver;

	uiModes.size=sizeof(UIModes);
	g_lpLib3d->GetModes(Save_Data.hDriver,uiModes);

 	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);
	selected=combo->GetIndex();
	Save_Data.hMode=uiModes.mode[selected].hMode;

//DEADCODE PD 03/12/99 	SDrvrModes* driverModes;
//DEADCODE PD 03/12/99 	char** driverNames;
//DEADCODE PD 03/12/99 	int curMode,selectedMode,selectedDriver;
//DEADCODE PD 03/12/99 	int modesCount,driverCount;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	GetDrivers(driverCount,driverNames);
//DEADCODE PD 03/12/99 	GetModes(modesCount,driverModes);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	OPTIONS
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	CRCombo* combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);
//DEADCODE PD 03/12/99 	selectedDriver=combo->GetIndex();
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	if (selectedDriver==0)	Save_Data.fSoftware=true;
//DEADCODE PD 03/12/99 	else
//DEADCODE PD 03/12/99 	{
//DEADCODE PD 03/12/99 		Save_Data.fSoftware=false;
//DEADCODE PD 03/12/99 		if (Save_Data.sd.fFirstHardIsPrimary)	selectedDriver--;
//DEADCODE PD 03/12/99 	}
//DEADCODE PD 03/12/99 	selectedDriver--;
//DEADCODE PD 03/12/99 	Save_Data.dddriver=selectedDriver;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);
//DEADCODE PD 03/12/99 	selectedMode=combo->GetIndex();
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	SModeFlags* modeFlags;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	if (Save_Data.fSoftware)	modeFlags=&Save_Data.sd.soft_modes;
//DEADCODE PD 03/12/99 	else						modeFlags=Save_Data.sd.hard_modes+selectedDriver+1;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	Save_Data.screenresolution=selectedMode;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	curMode=0;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	for (SLong x=0;x<modesCount;x++)
//DEADCODE PD 03/12/99 	{
//DEADCODE PD 03/12/99 		if (driverModes[x].driverNo-1==selectedDriver &&
//DEADCODE PD 03/12/99 			driverModes[x].displayBPP==16 &&
//DEADCODE PD 03/12/99 			IsValidMode(modeFlags,driverModes[x].displayWidth,driverModes[x].displayHeight))
//DEADCODE PD 03/12/99 		{
//DEADCODE PD 03/12/99 			if (curMode==selectedMode)
//DEADCODE PD 03/12/99 			{
//DEADCODE PD 03/12/99 				Save_Data.displayW=driverModes[x].displayWidth;
//DEADCODE PD 03/12/99 				Save_Data.displayH=driverModes[x].displayHeight;
//DEADCODE PD 03/12/99 				break;
//DEADCODE PD 03/12/99 			}
//DEADCODE PD 03/12/99 			else curMode++;
//DEADCODE PD 03/12/99 		}
//DEADCODE PD 03/12/99 	}

//DEADCODE PD 03/12/99 	if (Save_Data.fSoftware)
//DEADCODE PD 03/12/99 	{
//DEADCODE PD 03/12/99 		Save_Data.textureQuality=4;
//DEADCODE PD 03/12/99 		Save_Data.filtering=0;
//DEADCODE PD 03/12/99 		Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
//DEADCODE PD 03/12/99 		Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
//DEADCODE PD 03/12/99 		Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
//DEADCODE PD 03/12/99 		Save_Data.gamedifficulty%=GD_GEFFECTS;
//DEADCODE PD 03/12/99 		Save_Data.gamedifficulty%=GD_INJURYEFFECTS;
//DEADCODE PD 03/12/99 		Save_Data.gamedifficulty%=GD_WHITEOUT;
//DEADCODE PD 03/12/99 	}
//	else
//	{
//		Save_Data.filtering=1;
//		Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
//		Save_Data.gamedifficulty|=GD_GEFFECTS;
//		Save_Data.gamedifficulty|=GD_INJURYEFFECTS;
//	}
}

#define SG2C_CLEANUP
#include "sg2combo.h"

void CSDetail::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==ThreeDeePref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}

BEGIN_EVENTSINK_MAP(CSDetail, CDialog)
    //{{AFX_EVENTSINK_MAP(CSDetail)
	ON_EVENT(CSDetail, IDC_CBO_DISPLAYDRIVERS, 1 /* TextChanged */, OnTextChangedCboDisplaydrivers, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnTextChangedCboDisplaydrivers
//Author		Paul.   
//Date			Wed 9 Dec 1998
//------------------------------------------------------------------------------
void CSDetail::OnTextChangedCboDisplaydrivers(LPCTSTR text, short index)
{
	UIDrivers uiDrivers;
	UIModes uiModes;
	CLib3D *g_lpLib3d;
 	CRCombo *combo;
	int selected;

	g_lpLib3d=Master_3d.g_lpLib3d;

	combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);
	selected=combo->GetIndex();

	uiDrivers.size=sizeof(UIDrivers);
	g_lpLib3d->GetDrivers(uiDrivers);

	uiModes.size=sizeof(UIModes);
	HRESULT err = g_lpLib3d->GetModes(uiDrivers.driver[selected].hDriver,uiModes);

 	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);
 	combo->Clear();

	for (int i=0;i<uiModes.numModes;i++)
	{
		char rezStr[64];
		sprintf(rezStr,"%d x %d",uiModes.mode[i].width,uiModes.mode[i].height);
		combo->AddString((LPCTSTR)rezStr);
	}
	combo->SetIndex(0);

//DEADCODE PD 03/12/99 	static char modeString[32];
//DEADCODE PD 03/12/99 	int selectedDriver,modesCount;
//DEADCODE PD 03/12/99 	SDrvrModes* driverModes;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	GetModes(modesCount,driverModes);
//DEADCODE PD 03/12/99 	CRCombo* combo=GETDLGITEM(IDC_CBO_DISPLAYDRIVERS);
//DEADCODE PD 03/12/99 	selectedDriver=combo->GetIndex();
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	//if Save_Data.sd.fFirstHardIsPrimary then 
//DEADCODE PD 03/12/99 	//	selectedDriver==0	for software				=>-1
//DEADCODE PD 03/12/99 	//	selectedDriver==1	for primary hardware		=>-1
//DEADCODE PD 03/12/99 	//	selectedDriver==2	for secondary hardware		=>0
//DEADCODE PD 03/12/99 	//else
//DEADCODE PD 03/12/99 	//	selectedDriver==0	for software				=>-1
//DEADCODE PD 03/12/99 	//	selectedDriver==1	for secondary hardware		=>0
//DEADCODE PD 03/12/99 	if (selectedDriver==0)	Save_Data.fSoftware=true;
//DEADCODE PD 03/12/99 	else					Save_Data.fSoftware=false;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	if (Save_Data.sd.fFirstHardIsPrimary)	selectedDriver=selectedDriver==0?-1:selectedDriver-2;
//DEADCODE PD 03/12/99 	else									selectedDriver--;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	SModeFlags* modeFlags;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	if (Save_Data.fSoftware)	modeFlags=&Save_Data.sd.soft_modes;
//DEADCODE PD 03/12/99 	else						modeFlags=Save_Data.sd.hard_modes+selectedDriver+1;
//DEADCODE PD 03/12/99 //dead	else						modeFlags=Save_Data.sd.hard_modes+selectedDriver+1;
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	//erase the current list of resolutions
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	combo=GETDLGITEM(IDC_CBO_RESOLUTIONS);
//DEADCODE PD 03/12/99 	combo->Clear();
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	for (SLong x=0;x<modesCount;x++)
//DEADCODE PD 03/12/99 		if (driverModes[x].driverNo-1==selectedDriver &&
//DEADCODE PD 03/12/99 			driverModes[x].displayBPP==16 &&
//DEADCODE PD 03/12/99 			IsValidMode(modeFlags,driverModes[x].displayWidth,driverModes[x].displayHeight))
//DEADCODE PD 03/12/99 		{
//DEADCODE PD 03/12/99 			sprintf(modeString,"%d X %d\0",
//DEADCODE PD 03/12/99 					driverModes[x].displayWidth,
//DEADCODE PD 03/12/99 					driverModes[x].displayHeight);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 			combo->AddString(CString(modeString));
//DEADCODE PD 03/12/99 		}
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	Save_Data.screenresolution=0;
//DEADCODE PD 03/12/99 	combo->SetIndex(Save_Data.screenresolution);
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	if (Save_Data.fSoftware)
//DEADCODE PD 03/12/99 	{
//DEADCODE PD 03/12/99 		Save_Data.textureQuality=4;
//DEADCODE PD 03/12/99 		Save_Data.filtering=0;
//DEADCODE PD 03/12/99 		Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
//DEADCODE PD 03/12/99 		Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
//DEADCODE PD 03/12/99 		Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
//DEADCODE PD 03/12/99 		combo=GETDLGITEM(IDC_CBO_GROUNDSHADING);
//DEADCODE PD 03/12/99 		combo->Clear();
//DEADCODE PD 03/12/99 		combo->AddString(LoadResString(IDS_L_OFF));
//DEADCODE PD 03/12/99 		combo->SetIndex(0);
//DEADCODE PD 03/12/99 		combo=GETDLGITEM(IDC_CBO_REFLECTIONS);
//DEADCODE PD 03/12/99 		combo->Clear();
//DEADCODE PD 03/12/99 		combo->AddString(LoadResString(IDS_L_OFF));
//DEADCODE PD 03/12/99 		combo->SetIndex(0);
//DEADCODE PD 03/12/99 	}
//DEADCODE PD 03/12/99 	else
//DEADCODE PD 03/12/99 	{
//DEADCODE PD 03/12/99 		combo=GETDLGITEM(IDC_CBO_GROUNDSHADING);
//DEADCODE PD 03/12/99 		combo->Clear();
//DEADCODE PD 03/12/99 		combo->AddString(LoadResString(IDS_L_OFF));
//DEADCODE PD 03/12/99 		combo->AddString(LoadResString(IDS_L_OFF+1));
//DEADCODE PD 03/12/99 		combo=GETDLGITEM(IDC_CBO_REFLECTIONS);
//DEADCODE PD 03/12/99 		combo->Clear();
//DEADCODE PD 03/12/99 		combo->AddString(LoadResString(IDS_L_OFF));
//DEADCODE PD 03/12/99 		combo->AddString(LoadResString(IDS_L_OFF+1));
//DEADCODE PD 03/12/99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadString
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
char* COverlay::LdStr(SLong resID)
{
	char* retval;
	CString str;
	str.LoadString(resID);
	const char* tmp=LPCTSTR(str);
	retval=new char[strlen(tmp)+1];
	strcpy(retval,tmp);
	return retval;
}
