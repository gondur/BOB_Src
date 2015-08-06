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

// RowanDialog: // SSound.cpp : implementation file
//

#include "stdafx.h"
#include "music.h"
#include "mig.h"
#include "SSound.h"
#include "rcombo.h"
#include "miles.h"
//DeadCode AMM 23Nov99 #include "comms.h"
#include "winmove.h"

#ifdef _DEBUG
//#define new DEBUG_NEW
#ifndef THIS_FILE_DEFINED
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSound dialog
 

CSSound::CSSound(CWnd* pParent /*=NULL*/)
	: RowanDialog(CSSound::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSSound)
	//}}AFX_DATA_INIT
}
#define OPTIONS	\
	SETFIELD(CHAR(vol.sfx,0,25),				IDC_CBO_SFX,RESCOMBO(OBLMHT_OFF,6),						NOLEVEL)	\
	SETFIELD(CHAR(vol.uisfx,0,25),				IDC_CBO_SFX2,RESCOMBO(OBLMHT_OFF,6),						NOLEVEL)	\
	SETFIELD(CHAR(vol.anim,0,25),				IDC_CBO_SFX3,RESCOMBO(OBLMHT_OFF,6),						NOLEVEL)	\
 	SETFIELD(CHAR(vol.rchat,0,25),				IDC_CBO_RADIOCHATTER,RESCOMBO(OBLMHT_OFF,6),			NOLEVEL)	\
 	SETFIELD(CHAR(vol.engine,0,25),				IDC_CBO_ENGINESOUND,RESCOMBO(OBLMHT_OFF,6),				NOLEVEL)	 \
	SETFIELD(BIT(hardwareconfig,HW_3DSOUND),		IDC_CBO_SFXPROCESSING,RESCOMBO(STEREO,2),		NOLEVEL)	\
	SETFIELD(BIT(hardwareconfig,HW_SFXQUALITY),		IDC_CBO_RADIOQUALITY,RESCOMBO(LOWQUAL,2),		NOLEVEL)	\


//DEADCODE RDH 07/03/00   	SETFIELD(CHAR(vol.music,0,25),				IDC_CBO_MUSIC,RESCOMBO(OBLMHT_OFF,6),					NOLEVEL)	\
//DEADCODE RDH 23/05/00  	SETFIELD(BIT(hardwareconfig,HW_RAFVOICE),		IDC_CBO_RAFVOICE,RESCOMBO(ENGLISH,2),		NOLEVEL)	\
//DEADCODE RDH 23/05/00 	SETFIELD(BIT(hardwareconfig,HW_LWVOICE),		IDC_CBO_LWVOICE,RESCOMBO(GERMAN,2),		NOLEVEL)	


void CSSound::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSSound)
	DDX_Control(pDX,IDC_SDETAIL1,m_IDC_SDETAIL1);
	DDX_Control(pDX,IDC_RSTATICCTRL2,m_IDC_RSTATICCTRL2);
	DDX_Control(pDX,IDC_RSTATICCTRL3,m_IDC_RSTATICCTRL3);
	DDX_Control(pDX,IDC_RSTATICCTRL4,m_IDC_RSTATICCTRL4);
	DDX_Control(pDX,IDC_CBO_MUSIC,m_IDC_CBO_MUSIC);
	DDX_Control(pDX,IDC_CBO_SFX,m_IDC_CBO_SFX);
	DDX_Control(pDX,IDC_CBO_SFX2,m_IDC_CBO_SFX2);
	DDX_Control(pDX,IDC_CBO_SFX3,m_IDC_CBO_SFX3);
	DDX_Control(pDX,IDC_CBO_RADIOCHATTER,m_IDC_CBO_RADIOCHATTER);
	DDX_Control(pDX,IDC_CBO_ENGINESOUND,m_IDC_CBO_ENGINESOUND);
	DDX_Control(pDX,IDC_CBO_AUTOVECTORING,m_IDC_CBO_AUTOVECTORING);
	DDX_Control(pDX, IDC_CBO_RAFVOICE, m_IDC_CBO_RAFVOICE);
	DDX_Control(pDX, IDC_CBO_RADIOQUALITY, m_IDC_CBO_RADIOQUALITY);
	DDX_Control(pDX, IDC_CBO_LWVOICE, m_IDC_CBO_LWVOICE);
	DDX_Control(pDX, IDC_CBO_SOUNDDRIVER, m_IDC_CBO_SOUNDDRIVER);
	DDX_Control(pDX, IDC_CBO_MUSICDRIVER, m_IDC_CBO_MUSICDRIVER);
	DDX_Control(pDX, IDC_CBO_SFXPROCESSING, m_IDC_CBO_SFXPROCESSING);
	//}}AFX_DATA_MAP
#define	SG2C_DISPLAY setlevel
#include "sg2combo.h"
	OPTIONS	
//		m_IDC_CBO_MUSIC.SetCircularStyle(TRUE);
//		m_IDC_CBO_SFX.SetCircularStyle(TRUE);
//		m_IDC_CBO_RADIOCHATTER.SetCircularStyle(TRUE);
//		m_IDC_CBO_ENGINESOUND.SetCircularStyle(TRUE);
//		m_IDC_CBO_GEFFECTS.SetCircularStyle(TRUE);
//		m_IDC_CBO_INJURYEFFECTS.SetCircularStyle(TRUE);
//		m_IDC_CBO_WHITEOUTS.SetCircularStyle(TRUE);
//		m_IDC_CBO_AUTOVECTORING.SetCircularStyle(TRUE);


//DEADCODE RDH 24/11/99 		m_IDC_CBO_MUSIC.SetCircularStyle(TRUE);						  //RDH 03/04/99
//DEADCODE RDH 24/11/99 		m_IDC_CBO_SFX.SetCircularStyle(TRUE);
//DEADCODE RDH 24/11/99 		m_IDC_CBO_SFX2.SetCircularStyle(TRUE);
//DEADCODE RDH 24/11/99 		m_IDC_CBO_SFX3.SetCircularStyle(TRUE);
//DEADCODE RDH 24/11/99 		m_IDC_CBO_RADIOCHATTER.SetCircularStyle(TRUE);
//DEADCODE RDH 24/11/99 		m_IDC_CBO_ENGINESOUND.SetCircularStyle(TRUE);
//DEADCODE RDH 24/11/99 		m_IDC_CBO_GEFFECTS.SetCircularStyle(TRUE);
//DEADCODE RDH 24/11/99 		m_IDC_CBO_INJURYEFFECTS.SetCircularStyle(TRUE);
//DEADCODE RDH 24/11/99 		m_IDC_CBO_WHITEOUTS.SetCircularStyle(TRUE);
//DEADCODE RDH 24/11/99 		m_IDC_CBO_AUTOVECTORING.SetCircularStyle(TRUE);				  //RDH 03/04/99
		
		if (!_Miles.IsEnabled(SOUND_DIGITAL))
		{
			GETDLGITEM(IDC_CBO_SFX)->Clear();
			GETDLGITEM(IDC_CBO_SFX)->AddString(RESSTRING(NOTAVAILABLE));
			GETDLGITEM(IDC_CBO_SFX)->SetIndex(0);
			GETDLGITEM(IDC_CBO_SFX)->Clear();
			if (	_Miles.digerror
				&&	ULongP(_Miles.digerror)[0]==*(int*)"Dire"
				&&	ULongP(_Miles.digerror)[1]==*(int*)"ctSo"
				)
				GETDLGITEM(IDC_CBO_SFX)->AddString(CString("DS:")+(_Miles.digerror+11));
			else
				GETDLGITEM(IDC_CBO_SFX)->AddString(_Miles.digerror);
		}
		if (!_Miles.IsEnabled(SOUND_MIDI))
		{
			GETDLGITEM(IDC_CBO_MUSIC)->Clear();
			GETDLGITEM(IDC_CBO_MUSIC)->AddString(RESSTRING(NOTAVAILABLE));
			GETDLGITEM(IDC_CBO_MUSIC)->SetIndex(0);
		}
		if (!_Miles.IsEnabled(SOUND_RADIO))						//DAW 18Aug99
		{
			GETDLGITEM(IDC_CBO_RADIOCHATTER)->Clear();
			GETDLGITEM(IDC_CBO_RADIOCHATTER)->AddString(RESSTRING(NOTAVAILABLE));
			GETDLGITEM(IDC_CBO_RADIOCHATTER)->SetIndex(0);
		}


//	calib=GetDlgItem(IDC_CALIB2);
//	calib->SetCaption(RESSTRING(CONFIG));

}



BEGIN_MESSAGE_MAP(CSSound, CDialog)
	//{{AFX_MSG_MAP(CSSound)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSound message handlers

void CSSound::OnDestroy() 
{
	KillTimer(OthersPref_Timer);

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
}
void CSSound::PreDestroyPanel()
{
#define	SG2C_WRITEBACK setlevel
#include "sg2combo.h"

	OPTIONS

	_Miles.SetVolumes(FALSE);									//RJS 12Mar99

// set up new sound and music devices

	{
		if (_Miles.dig && _Miles.dig->DIG_valid())
		{
			HWND oldwin=_Miles.dig->GetWindow();
			_Miles.InitUI((int)oldwin);
		}
	}

// used to test switching between stereo/3d sound

//DEADCODE AMM 24/11/99 	if (Save_Data.ThreeDeeSound)
//DEADCODE AMM 24/11/99 		Save_Data.ThreeDeeSound=false;
//DEADCODE AMM 24/11/99 	else
//DEADCODE AMM 24/11/99 		Save_Data.ThreeDeeSound=true;
}
#define SG2C_CLEANUP
#include "sg2combo.h"

BEGIN_EVENTSINK_MAP(CSSound, CDialog)
    //{{AFX_EVENTSINK_MAP(CSSound)
	ON_EVENT(CSSound, IDC_RBUTTONMUSICTEST, 1 /* Clicked */, OnClickedRbuttonmusictest, VTS_NONE)
	ON_EVENT(CSSound, IDC_CBO_SOUNDDRIVER, 1 /* TextChanged */, OnTextChangedCboSounddriver, VTS_BSTR VTS_I2)
	ON_EVENT(CSSound, IDC_CBO_MUSICDRIVER, 1 /* TextChanged */, OnTextChangedCboMusicdriver, VTS_BSTR VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()


BOOL CSSound::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (_DPlay.PlayerCreated)									//AMM 12Jul99
	{															//AMM 12Jul99
		_DPlay.SendStatusChange(DPlay::CPS_PREFS);
	}															//AMM 12Jul99

	OthersPref_Timer=SetTimer(DPlay::TIMER_PREFSOTHERS,0,NULL);

//DEADCODE RDH 25/11/99 	CRCombo* combo;
//DEADCODE RDH 25/11/99 	if	(		(RFullPanelDial::incomms)
//DEADCODE RDH 25/11/99 			&&	(_DPlay.UIPlayerType==PLAYER_GUEST)
//DEADCODE RDH 25/11/99 		)
//DEADCODE RDH 25/11/99 	{
//DEADCODE RDH 25/11/99 		combo=GETDLGITEM(IDC_CBO_GEFFECTS);
//DEADCODE RDH 25/11/99 		combo->SetEnabled(false);
//DEADCODE RDH 25/11/99 		combo=GETDLGITEM(IDC_CBO_INJURYEFFECTS);
//DEADCODE RDH 25/11/99 		combo->SetEnabled(false);
//DEADCODE RDH 25/11/99 		combo=GETDLGITEM(IDC_CBO_WHITEOUTS);
//DEADCODE RDH 25/11/99 		combo->SetEnabled(false);
//DEADCODE RDH 25/11/99 		combo=GETDLGITEM(IDC_CBO_AUTOVECTORING);
//DEADCODE RDH 25/11/99 		combo->SetEnabled(false);
//DEADCODE RDH 25/11/99 	}else
//DEADCODE RDH 25/11/99 	{
//DEADCODE RDH 25/11/99 		combo=GETDLGITEM(IDC_CBO_GEFFECTS);
//DEADCODE RDH 25/11/99 		combo->SetEnabled(true);
//DEADCODE RDH 25/11/99 		combo=GETDLGITEM(IDC_CBO_INJURYEFFECTS);
//DEADCODE RDH 25/11/99 		combo->SetEnabled(true);
//DEADCODE RDH 25/11/99 		combo=GETDLGITEM(IDC_CBO_WHITEOUTS);
//DEADCODE RDH 25/11/99 		combo->SetEnabled(true);
//DEADCODE RDH 25/11/99 		combo=GETDLGITEM(IDC_CBO_AUTOVECTORING);
//DEADCODE RDH 25/11/99 		combo->SetEnabled(true);
//DEADCODE RDH 25/11/99 	}
//DEADCODE RDH 25/11/99 


	CRCombo* combo;
	combo=GETDLGITEM(IDC_CBO_SOUNDDRIVER);
	combo->Clear();

	LPDSPORTINFO dstemp=NULL;
	ULong index=0;

	if (_Miles.dig && _Miles.dig->DIG_valid())
	{
		dstemp=_Miles.dig->PortInfo;
	}

	if (!dstemp)
	{
		combo->AddString(RESSTRING(NOTAVAILABLE));
	}
	else
	{
		ULong n=0;

		while (dstemp)
		{
			combo->AddString(dstemp->device);
			if (dstemp->port==Save_Data.SFXDevice)
				index=n;

			n++;
			dstemp=dstemp->next;
		}
	}

	combo->SetIndex(index);

//DEADCODE RDH 07/03/00 	combo=GETDLGITEM(IDC_CBO_MUSICDRIVER);
//DEADCODE RDH 07/03/00 	combo->Clear();
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 	LPDMPORTINFO temp=NULL;
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 	index=0;
//DEADCODE RDH 07/03/00 	
//DEADCODE RDH 07/03/00 	if (_Miles.mdi && _Miles.mdi->MDI_valid())
//DEADCODE RDH 07/03/00 	{
//DEADCODE RDH 07/03/00 		temp=_Miles.mdi->PortInfo;
//DEADCODE RDH 07/03/00 	}
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 	if (!temp)
//DEADCODE RDH 07/03/00 	{
//DEADCODE RDH 07/03/00 		combo->AddString(RESSTRING(NOTAVAILABLE));
//DEADCODE RDH 07/03/00 	}
//DEADCODE RDH 07/03/00 	else
//DEADCODE RDH 07/03/00 	{
//DEADCODE RDH 07/03/00 		ULong n=0;
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 		while (temp)
//DEADCODE RDH 07/03/00 		{
//DEADCODE RDH 07/03/00 			combo->AddString(temp->device);
//DEADCODE RDH 07/03/00 			if (temp->port==Save_Data.MusicDevice)
//DEADCODE RDH 07/03/00 				index=n;
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 			n++;
//DEADCODE RDH 07/03/00 			temp=temp->next;
//DEADCODE RDH 07/03/00 		}
//DEADCODE RDH 07/03/00 	}
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 	combo->SetIndex(index);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSSound::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent==OthersPref_Timer && _DPlay.PlayerCreated)
	{
		_DPlay.UIUpdateMainSheet();
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CSSound::OnClickedRbuttonmusictest() 
{
//DEADCODE RDH 07/03/00 	// TODO: Add your control notification handler code here
//DEADCODE RDH 07/03/00 	
//DEADCODE RDH 07/03/00 	{
//DEADCODE RDH 07/03/00 		if (_Miles.mdi && _Miles.mdi->MDI_valid())
//DEADCODE RDH 07/03/00 		{
//DEADCODE RDH 07/03/00 			_Miles.mdi->Stop();
//DEADCODE RDH 07/03/00 			_Miles.mdi->CreateAndAddPort(Save_Data.MusicDevice);
//DEADCODE RDH 07/03/00 			_Miles.mdi->Play(NULL,NULL,true);
//DEADCODE RDH 07/03/00 		}
//DEADCODE RDH 07/03/00 	}
}

void CSSound::OnTextChangedCboSounddriver(LPCTSTR Caption, short index) 
{
	// TODO: Add your control notification handler code here
	
	{
		CRCombo* combo;
		combo=GETDLGITEM(IDC_CBO_RADIOCHATTER);

		LPDSPORTINFO temp=NULL;
		
		if (_Miles.dig && _Miles.dig->DIG_valid())
		{
			temp=_Miles.dig->PortInfo;

			while (temp && index--)
			{
				temp=temp->next;
			}
			if (temp)
			{
				Save_Data.SFXDevice=temp->port;
			}
		}
	}
}

void CSSound::OnTextChangedCboMusicdriver(LPCTSTR Caption, short index) 
{
	
//DEADCODE RDH 07/03/00 	{
//DEADCODE RDH 07/03/00 		CRCombo* combo;
//DEADCODE RDH 07/03/00 		combo=GETDLGITEM(IDC_CBO_ENGINESOUND);
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 		LPDMPORTINFO temp=NULL;
//DEADCODE RDH 07/03/00 		
//DEADCODE RDH 07/03/00 		if (_Miles.mdi && _Miles.mdi->MDI_valid())
//DEADCODE RDH 07/03/00 		{
//DEADCODE RDH 07/03/00 			temp=_Miles.mdi->PortInfo;
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 			while (temp && index--)
//DEADCODE RDH 07/03/00 			{
//DEADCODE RDH 07/03/00 				temp=temp->next;
//DEADCODE RDH 07/03/00 			}
//DEADCODE RDH 07/03/00 			if (temp)
//DEADCODE RDH 07/03/00 			{
//DEADCODE RDH 07/03/00 				Save_Data.MusicDevice=temp->port;
//DEADCODE RDH 07/03/00 			}
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 // changed device, stop any music currently playing in case confusion arises
//DEADCODE RDH 07/03/00 // as to which music device is playing music. To test music players will have to
//DEADCODE RDH 07/03/00 // re-click on TestMusic button
//DEADCODE RDH 07/03/00 
//DEADCODE RDH 07/03/00 			_Miles.mdi->Stop();
//DEADCODE RDH 07/03/00 		}
//DEADCODE RDH 07/03/00 	}
}
