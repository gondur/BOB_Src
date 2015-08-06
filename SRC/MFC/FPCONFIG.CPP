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

//////////////////////////////////////////////////////////////////////
//
// Function:    
// Date:		03/12/99
// Author:		JIM
//
//Description: Layout and code for config screens in fullpane
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "FullPane.h"

typedef FullScreen::Resolutions::Dial DIAL;
typedef FullScreen::Align ALIGN;


#define	OPTIONSTITLE\
	{											\
	/*0*/	{IDS_3D_CONFIG,&options3d},				\
	/*1*/	{IDS_3DII,&options3d2},	 \
	/*2*/	{IDS_CONTROLLER_CONFIG,&controloptions},			   \
	/*3*/	{IDS_SOUND_CONFIG,&soundoptions},			  \
	/*4*/	{IDS_2D,&twodoptions},				\
	/*5*/	{IDS_BLANK},				\
	/*6*/	{IDS_SIM, &flightoptions},				\
	/*7*/	{IDS_CONTINUE_CONFIG,NULL,PreferencesExitPath}						\
	}

#define	SIMOPTIONSTITLE\
	{											\
	/*0*/	{IDS_FLIGHT_CONFIG,&flightoptions},		 \
	/*1*/	{IDS_GAME_CONFIG,&gameoptions},		   \
	/*2*/	{IDS_MISSION_CONFIG,&missionoptions},	\
	/*3*/	{IDS_VIEW_CONFIG,&vieweroptions},		 \
	/*4*/	{IDS_GESCHWADERLIST},/*IDS_BLANK},*/				\
	/*5*/	{IDS_MACHINE, &options3d},				\
	/*6*/	{IDS_CONTINUE_CONFIG,NULL,PreferencesExitPath}						\
  	}

#define	OPTIONSXY640	15,5
#define	OPTIONSXY800	10,10
#define	OPTIONSXY1024	10,10
#define	OPTIONSXY1280	20,10						/*0*//*0*//*0*/
													/*1*//*1*//*1*/
#define	PANELXY640	15,50							/*2*//*2*//*2*/				  //RDH 11/06/99
#define	PANELXY800	50,70							/*3*//*3*//*3*/				  //RDH 11/06/99
#define	PANELXY1024	300,110							/*4*//*4*//*4*/				  //RDH 04/11/99
#define	PANELXY1280	90,150							/*5*//*5*//*5*/
													/*6*//*6*//*6*/
#define	CONTROLXY1024	150,100						/*7*//*7*//*7*/					//RDH 01/03/00
FullScreen RFullPanelDial::options3d=
{
	{
		{
			FIL_3DDISPLAY_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_3DDISPLAY_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_MCPREF_3D,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_3DDISPLAY_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	Options3dInit
};
//#define	OPTIONSXY640	15,5
//#define	OPTIONSXY800	10,10
//#define	OPTIONSXY1024	10,10
//#define	OPTIONSXY1280	20,10


FullScreen RFullPanelDial::gameoptions=
{
	{
		{
			FIL_GAMESETUP_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_GAMESETUP_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_SMPREF_GAMESETUP,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_GAMESETUP_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	SIMOPTIONSTITLE,
	GameOptionsInit
};

FullScreen RFullPanelDial::missionoptions=
{
	{
		{
			FIL_GAMESETUP_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_GAMESETUP_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_SMPREF_MISSION,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_GAMESETUP_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	SIMOPTIONSTITLE,
	MissionOptionsInit
};

FullScreen RFullPanelDial::options3d2=
{
	{
		{
			FIL_3DDISPLAY_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_3DDISPLAY_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_MCPREF_3DII,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_3DDISPLAY_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	Options3d2Init
};

FullScreen RFullPanelDial::vieweroptions=
{
	{
		{
			FIL_VIEWOPTIONS_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_VIEWOPTIONS_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_SMPREF_VIEW,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_VIEWOPTIONS_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	SIMOPTIONSTITLE,
	ViewerOptionsInit
};

FullScreen RFullPanelDial::soundoptions=
{
	{
		{
			FIL_SOUNDSETUP_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_SOUNDSETUP_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_MCPREF_SOUNDSETUP,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_SOUNDSETUP_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	SoundOptionsInit
};
FullScreen RFullPanelDial::twodoptions=
{
	{
		{
			FIL_SOUNDSETUP_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_SOUNDSETUP_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_MCPREF_SOUNDSETUP,
			{{250,110}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_SOUNDSETUP_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	TwoDOptionsInit
};
FullScreen RFullPanelDial::flightoptions=
{
	{
		{
			FIL_FLIGHTCONFIG_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_FLIGHTCONFIG_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_SMPREF_FLIGHTOPTIONS,
			{{PANELXY1024}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1024
		},
		{
			FIL_FLIGHTCONFIG_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	SIMOPTIONSTITLE,
	FlightOptionsInit
};

FullScreen RFullPanelDial::controloptions=
{
	{
		{
			FIL_FLIGHTCONFIG_640,
			{{PANELXY640}},
			OPTIONSXY640
		},
		{
			FIL_FLIGHTCONFIG_800,
			{{PANELXY800}},
			OPTIONSXY800
		},
		{
			FIL_MCPREF_CONTROLLER,
			{{CONTROLXY1024}},												  //RDH 14/05/99
			OPTIONSXY1024
		},
		{
			FIL_FLIGHTCONFIG_1280,
			{{PANELXY1280}},//,FullScreen::Resolutions::Dial::X2}},
			OPTIONSXY1280
		},
	},
	FullScreen::Align::HORIZ,// + FullScreen::Align::HORIZ,
	OPTIONSTITLE,
	ControlOptionsInit
};

////////////////////////////////////////////////////////////////////////
//
// Function:	LoadCol
// Author:		JIM
// Date:		28/06/01
//
// Description:	
//
////////////////////////////////////////////////////////////////////////
static int	col4=-650,col5=-700,collast=-800,repeated;
static void LoadCol()
{
	if (!repeated++)
	{
		CString params;
		params=RESSTRING(PREFSFIXEDCOLS);
		if (!params.IsEmpty())
		{	sscanf(params,"%i %i %i",&col4,&col5,&collast);		}
	}
}

Bool RFullPanelDial::Options3dInit()
{	LoadCol();
	LaunchDial(new CSDetail,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(0);
	prlistbox->SetHilightRow(0);
	prlistbox->ReplaceString("",0,5);
	prlistbox->SetColumnWidth(5,col5);
	prlistbox->SetColumnWidth(6,collast);
	return TRUE;
}

Bool RFullPanelDial::Options3d2Init()
{	LoadCol();
	LaunchDial(new CAutoPilot,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(1);
	prlistbox->SetHilightRow(0);
	prlistbox->ReplaceString("",0,5);
	prlistbox->SetColumnWidth(5,col5   );
	prlistbox->SetColumnWidth(6,collast);
	return TRUE;
}

Bool RFullPanelDial::ControlOptionsInit()
{	LoadCol();
	LaunchDial(new SController,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(2);
	prlistbox->SetHilightRow(0);
	prlistbox->ReplaceString("",0,5);
	prlistbox->SetColumnWidth(5,col5   );
	prlistbox->SetColumnWidth(6,collast);
	return TRUE;
}

Bool RFullPanelDial::SoundOptionsInit()
{	LoadCol();
	LaunchDial(new CSSound,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(3);
	prlistbox->SetHilightRow(0);
	prlistbox->ReplaceString("",0,5);
	prlistbox->SetColumnWidth(5,col5   );
	prlistbox->SetColumnWidth(6,collast);
	return TRUE;
}

Bool RFullPanelDial::TwoDOptionsInit()
{	LoadCol();
	LaunchDial(new TwoDPref,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(4);
	prlistbox->SetHilightRow(0);
	prlistbox->ReplaceString("",0,5);
	prlistbox->SetColumnWidth(5,col5   );
	prlistbox->SetColumnWidth(6,collast);
	return TRUE;
}
//////////////////////////////////////////////
Bool RFullPanelDial::FlightOptionsInit()
{
	LoadCol();
	LaunchDial(new CSFlight,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(0);
	prlistbox->SetHilightRow(0);
	prlistbox->ReplaceString("",0,4);
	prlistbox->SetColumnWidth(4,col4   );
	prlistbox->SetColumnWidth(5,collast);
	return TRUE;
}

Bool RFullPanelDial::GameOptionsInit()
{	LoadCol();
	LaunchDial(new CSGame,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(1);
	prlistbox->SetHilightRow(0);
	prlistbox->ReplaceString("",0,4);
	prlistbox->SetColumnWidth(4,col4   );
	prlistbox->SetColumnWidth(5,collast);
	return TRUE;
}
Bool RFullPanelDial::MissionOptionsInit()
{	LoadCol();
	LaunchDial(new SMissionConfigure,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(2);
	prlistbox->SetHilightRow(0);
	prlistbox->ReplaceString("",0,4);
	prlistbox->SetColumnWidth(4,col4   );
	prlistbox->SetColumnWidth(5,collast);
	return TRUE;
}


Bool RFullPanelDial::ViewerOptionsInit()
{	LoadCol();
	LaunchDial(new CSViewer,0);
	CRListBox* prlistbox;
	prlistbox=GETDLGITEM(IDC_RLISTBOX);
	prlistbox->SetHilightCol(3);
	prlistbox->ReplaceString("",0,4);
	prlistbox->SetColumnWidth(4,col4   );
	prlistbox->SetColumnWidth(5,collast);
	prlistbox->SetHilightRow(0);
	return TRUE;
}

Bool	RFullPanelDial::PreferencesExitPath(FullScreen*&fs)
{
	if (in3d)
	{
		fs=&quickmissionflight;
		return TRUE;
	}																	//RDH 16/05/00
	else
		if (gamestate==TITLE)
			fs=&title;
#ifndef	BOB_DEMO_VER
		else if (incomms)
				SelectReadyRoom(fs);
#endif
//DeadCode CSB 11Sep00 		else if (gamestate==QUICK)
//DeadCode CSB 11Sep00 			fs = &bobfrag;												//RDH 16/05/00
		else
		{
			fs = &bobfrag;
		}


	return CheckForDemo(fs);
}

