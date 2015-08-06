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
//Description: Full Pane layouts go in this file....
//			   The Code is still in FullPane
//////////////////////////////////////////////////////////////////////
// Initialise sheets here.  This means they are initialised at
// compile time instead of run time.
#include "stdafx.h"
#include "FullPane.h"

typedef FullScreen::Resolutions::Dial DIAL;
typedef FullScreen::Align ALIGN;

FullScreen RFullPanelDial::introsmack=
{
	{
		{
			FIL_NULL,
//DEADCODE DAW 21/03/99 			{{320,74}},
			{{110,180}},
			0,0
		},
		{
			FIL_NULL,
//DEADCODE DAW 21/03/99 			{{80,234}},
			{{100,130}},
			0,0
		},
		{
			FIL_NULL,
//DEADCODE DAW 21/03/99 			{{192,218}},
			{{270,370}},
			0,0
		},
		{
			FIL_NULL,
//DEADCODE DAW 21/03/99 			{{320,346}},
			{{70,70}},
			0,0
		},
	},
	FullScreen::Align::CENTRE,
			{{0,&title,CheckLobby}},
	IntroSmackInit
};
FullScreen RFullPanelDial::endwarreview=
{
#ifndef	BOB_DEMO_VER
	{
		{
			FIL_NULL,
			{{220,180}},
			0,0
		},
		{
			FIL_NULL,
			{{70,70}},
			0,0
		},
		{
			FIL_NULL,
			{{300,370}},
			0,0
		},
		{
			FIL_NULL,
			{{70,70}},
			0,0
		},
	},
	FullScreen::Align::CENTRE,
			{{0,&lastdayreview, ExitLastDay}},
	EndWarInit
#else
	{	{	FIL_NULL	}	}
#endif
};
FullScreen RFullPanelDial::Blank={	{	{	FIL_NULL	}	}	};

FullScreen RFullPanelDial::credits=
{
	{
		{
			FIL_NULL,
//DEADCODE DAW 30/03/99 			{{0,0},{0,350}},
 			{{0,0},{100,50}},
			0,200
		},
		{
			FIL_NULL,
//DEADCODE DAW 30/03/99 			{{0,0},{0,450}},
			{{80,250},{80,10}},									  //JIM 15/06/99
			0,200
		},
		{
			FIL_NULL,
//DEADCODE DAW 30/03/99 			{{0,0},{0,550}},
			{{192,350},{200,100}},									  //JIM 15/06/99
			0,200
		},
		{
			FIL_NULL,
//DEADCODE DAW 30/03/99 			{{0,0},{0,750}},
			{{320,350},{300,100}},									  //JIM 15/06/99
			0,300
		},
	},
// for lobbied games need to goto locker room instead of main menu
	FullScreen::Align::CENTRE,
	{{0,&title,CheckForDemo}},
	IntroSmackInitForCredits
};


FullScreen RFullPanelDial::title=
{
	{
		{	//Not got any 640 artwork, but need a backdrop for error box!
			FIL_TITLE_1024,
			{{100,100}},	// no dialogs
			900,0
		},
		{
			FIL_TITLE_1024,
			{{200,180}},	// no dialogs
			900,0														//RDH 04/04/00
		},
		{
			FIL_TITLE_1024,
			{{100,100,FullScreen::Resolutions::Dial::X2}},	// no dialogs
//DEADCODE RDH 03/11/99 			675,260
			210,220	//release numbers													//RDH 04/04/00
		},
		{
			FIL_TITLE_1024,
			{{200,200,FullScreen::Resolutions::Dial::X2}},	// no dialogs
			810,370
		},
	},
	FullScreen::Align(FullScreen::Align::CENTRE+FullScreen::Align::MID),
	{
#ifndef	 BOB_DEMO_VER
		{IDS_QUICKSHOTS,&quickmission,SetQuickState},
		{IDS_CAMPAIGNS,&singleplayer},
		{IDS_TITLE3,&selectservice,StartComms},
		{IDS_LOADGAME,&loadgame},
		{IDS_REPLAYTITLE,&replayload,InitReplay},
		{IDS_MACHINECONFIG,&options3d},
		{IDS_CONFIGGAME,&flightoptions},
		{IDS_CREDITSTITLE,&credits},
		{IDS_TITLE7,NULL,ConfirmExit},
#ifndef NDEBUG
		{IDS_HOTSHOT,&quickmissionflight,SetUpHotShot}
#else
		{IDS_WEBSITE,NULL,JumpToWebSite}
#endif
#else
		{IDS_QUICKSHOTS,&quickmission,SetQuickState},
		//{IDS_NOT_CAMPAIGN},
		//{IDS_NOT_MULTIPLAYER},
		//{IDS_NOT_LOADGAME},
		//{IDS_NOT_REPLAY},	//TITLE,&replayload,InitReplay},
		{IDS_MACHINECONFIG,&options3d},
		{IDS_CONFIGGAME,&flightoptions},
		{IDS_CREDITSTITLE,&credits},
		{IDS_TITLE7,NULL,ConfirmExit},
		{IDS_NONE},
		{IDS_NONE},
		{IDS_NONE},
		{IDS_NONE},
		{IDS_NOT_REPLAY}	//DISABLEDEMO}
#endif
	},
	TitleInit
};

#ifdef	 BOB_DEMO_VER
FullScreen RFullPanelDial::singleplayer={	{	{	FIL_NULL	}	}	};
#endif
#ifndef	 BOB_DEMO_VER
FullScreen RFullPanelDial::loadcommsgame=
{
	{
		{
			FIL_LOADSAVE_640,
			{{100,100}},	// no dialogs
			425,170
		},
		{
			FIL_LOADSAVE_800,
			{{30,200}},
			20,560
		},
		{
			FIL_LOADSAVE,
			{{40,260}},
			35,720
		},
		{
			FIL_LOADSAVE_1280,
			{{30,520}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&multiplayer},
		{IDS_LOAD,&readyroomhostcampaign,DoLoadCommsGame}
	},
	SetUpLoadGame
};

FullScreen RFullPanelDial::loadgame=
{
	{
		{
			FIL_LOADSAVE_640,
			{{100,100}},	// no dialogs
			425,170
		},
		{
			FIL_LOADSAVE_800,
			{{30,180}},
			20,560
		},
		{
			FIL_LOADSAVE,
			{{40,260}},
			35,720
		},
		{
			FIL_LOADSAVE_1280,
			{{30,520}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_RAF,NULL,SetUpRafLoadGame},
		{IDS_LUFTWAFFE,NULL,SetUpLWLoadGame},

		{IDS_BACK,&title},
		{IDS_LOAD,NULL,DoLoadGame}
	},
	SetUpLoadGame
};

#endif	//#ifndef	 BOB_DEMO_VER

FullScreen RFullPanelDial::replayload=
{
	{
		{
			FIL_REPLAY_640,
			{{15,15}},
			15,440
		},
		{
			FIL_REPLAY_800,
			{{4,150}},
			20,560
		},
		{
			FIL_REPLAY,
			{{40,260}},
			50,700
		},
		{
			FIL_REPLAY_1280,
			{{40,325}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&title,ReplayLoadBack},
//DeadCode AMM 17Feb99 		{IDS_LOAD,NULL,ReplayLoad},
		{IDS_LOAD,&quickmissionflight,ReplayLoad},			//AMM 17Feb99
//		{IDS_SAVE,NULL,ReplaySave},
//		{IDS_VIEW,NULL,ReplayView},
//DeadCode AMM 17Feb99 		{IDS_VIEW,&quickmissionflight,ReplayView},
	},
	ReplayLoadInit
};

#ifndef	 BOB_DEMO_VER

FullScreen RFullPanelDial::replaysave=
{
	{
		{
			FIL_REPLAY_640,
			{{15,15}},
			15,440
		},
		{
			FIL_REPLAY_800,
			{{4,150}},
			20,560
		},
		{
			FIL_REPLAY,
			{{40,260}},
			50,700
		},
		{
			FIL_REPLAY_1280,
			{{40,325}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
//		{IDS_TITLE7,&title},
//DeadCode  26Sep00 		{IDS_QUICKMISSION1,&quickmissiondebrief,ReplaySaveBack},
		{IDS_QUICKMISSION1,&quickmission,ReplaySaveBack},
//		{IDS_LOAD,NULL,ReplayLoad},
		{IDS_SAVE,&replaysave,ReplaySave},
//		{IDS_VIEW,NULL,ReplayView},
		{IDS_VIEW,&quickmissionflight,ReplayView},
	},
	ReplaySaveInit
};

FullScreen RFullPanelDial::singleplayer=
{
	{
		{
			FIL_TITLE_1024,					//FIL_TITLE_640,	//DAW 14Nov100
			{{0}},	// no dialogs
			300,400
		},
		{
			FIL_TITLE_1024,					//FIL_TITLE_800,	//DAW 14Nov100
			{{0}},	// no dialogs
			300,550
		},
		{
			FIL_SIDESELECT,
			{{0}},	// no dialogs
			500,700
		},
		{
			FIL_TITLE_1024,					//FIL_TITLE_1280,	//DAW 14Nov100
			{{0}},	// no dialogs
			600,980
		},
	},
	FullScreen::Align::HORIZ,
	{
		{0,&campaignselect,SetUpRAF},
		{0,&campaignselect,SetUpLW},
		{0,&title},
	},
	SinglePlayerInit
};

FullScreen RFullPanelDial::gametype=
{
	{
		{
			FIL_TITLE_1024,					//FIL_TITLE_640,	//DAW 14Nov100
			{{0}},	// no dialogs
			300,400
		},
		{
			FIL_TITLE_1024,					//FIL_TITLE_800,	//DAW 14Nov100
			{{0}},	// no dialogs
			400,550
		},
		{
			FIL_GAMESELECT,
			{{0}},	// no dialogs
			500,700
		},
		{
			FIL_TITLE_1024,					//FIL_TITLE_1280,	//DAW 14Nov100
			{{0}},	// no dialogs
			600,950
		},
	},
	FullScreen::Align::HORIZ,
	{
		{0,&campaignselect,SetUpCommander},
		{0,&campaignselect,SetUpPilot},
		{0,&title},
	},
	GameTypeInit
};


FullScreen RFullPanelDial::selectservice=
{
	{
		{
			FIL_LOCKERROOM_640,
			{
				{15,180}
			},
			15,440
		},
		{
			FIL_LOCKERROOM_800,
			{
				{20,280}
			},
			20,560
		},
		{
			FIL_LOCKERROOM,
			{
				{25,50}//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_LOCKERROOM_1280,
			{
				{40,680}//,FullScreen::Resolutions::Dial::X2}
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&title,CleanUpComms},
//DeadCode AMM 12Jul98 		{IDS_SELECT,&selectsession},
//DeadCode AMM 20Jan99 		{IDS_SELECT,&selectsession,GetSessions},
		{IDS_CREATEGAME,&multiplayer,CreateCommsGame},
		{IDS_JOINGAME,&selectsession,GetSessions},

	},
	SelectServiceInit
};

FullScreen RFullPanelDial::selectsession=
{
	{
		{
			FIL_LOCKERROOM_640,
			{
				{15,180}
			},
			15,440
		},
		{
			FIL_LOCKERROOM_800,
			{
				{20,280}
			},
			20,560
		},
		{
			FIL_LOCKERROOM,
			{
				{25,50}//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_LOCKERROOM_1280,
			{
				{40,680}//,FullScreen::Resolutions::Dial::X2}
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&selectservice,ReInitCommsInterface},
//DeadCode AMM 20Jan99 		{IDS_CREATEGAME,&multiplayer,CreateCommsGame},
//DeadCode AMM 20Jan99 		{IDS_JOINGAME,&multiplayer,JoinCommsGame},
//DeadCode AMM 20Jan99 //		{IDS_PREFERENCES9,&selectsession,RefreshSessions},
		{IDS_SELECT,&multiplayer,JoinCommsGame},
	},
	SelectSessionInit
};

FullScreen RFullPanelDial::multiplayer=
{
	{
		{
			FIL_LOCKERROOM_640,
			{{15,180}},
			15,440
		},
		{
			FIL_LOCKERROOM_800,
			{{20,240}},
			20,560
		},
		{
			FIL_LOCKERROOM,
			{{25,50}},//,FullScreen::Resolutions::Dial::X2}},
			25,720
		},
		{
			FIL_LOCKERROOM_1280,
			{{40,620}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&selectsession,LobbyCheck},
		{IDS_CONTINUE,&readyroomhostmatch,CreatePlayer},
		{IDS_LOADGAME,&loadcommsgame, LoadCampaign},
//		{IDS_VISITORS,&visitorsbook,VisitorsBook},
	},
	LockerRoomInit
};

FullScreen RFullPanelDial::visitorsbook=
{
	{
		{
			FIL_PAINTSHOP_640,
			{{15,180}},
			15,440
		},
		{
			FIL_PAINTSHOP_800,
			{{20,250}},
			20,560
		},
		{
			FIL_VISITORS,
			{{25,50}},//,FullScreen::Resolutions::Dial::X2}},
			25,720
		},
		{
			FIL_PAINTSHOP_1280,
			{{40,450}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&readyroomhostmatch, SelectReadyRoom},
//		{IDS_CONTINUE,&visitorsbook},
	},
	VisitorsBookInit
};

//DeadCode JIM 12Oct00 FullScreen RFullPanelDial::singlefrag=
//DeadCode JIM 12Oct00 {
//DeadCode JIM 12Oct00 	{
//DeadCode JIM 12Oct00 		{
//DeadCode JIM 12Oct00 			FIL_READYROOM_640,
//DeadCode JIM 12Oct00 			{{70,50}},
//DeadCode JIM 12Oct00 			15,440
//DeadCode JIM 12Oct00 		},
//DeadCode JIM 12Oct00 		{
//DeadCode JIM 12Oct00 			FIL_READYROOM_800,
//DeadCode JIM 12Oct00 			{{60,16}},
//DeadCode JIM 12Oct00 			20,560
//DeadCode JIM 12Oct00 		},
//DeadCode JIM 12Oct00 		{
//DeadCode JIM 12Oct00 			FIL_LWFRAG,
//DeadCode JIM 12Oct00 			{
//DeadCode JIM 12Oct00 				{20,20},//,FullScreen::Resolutions::Dial::X2},
//DeadCode JIM 12Oct00 				{25,150}//,FullScreen::Resolutions::Dial::X2}
//DeadCode JIM 12Oct00 			},
//DeadCode JIM 12Oct00 			25,720
//DeadCode JIM 12Oct00 		},
//DeadCode JIM 12Oct00 		{
//DeadCode JIM 12Oct00 			FIL_READYROOM_1280,
//DeadCode JIM 12Oct00 			{{100,24}},//,FullScreen::Resolutions::Dial::X2}},
//DeadCode JIM 12Oct00 			40,960
//DeadCode JIM 12Oct00 		},
//DeadCode JIM 12Oct00 	},
//DeadCode JIM 12Oct00 	FullScreen::Align::HORIZ,
//DeadCode JIM 12Oct00 	{
//DeadCode JIM 12Oct00 		{IDS_BACK,&readyroomhostmatch,ReturnToMap},
//DeadCode JIM 12Oct00 		{IDS_FLY,&quickmissionflight, FragFly},
//DeadCode JIM 12Oct00 		{IDS_TITLE1,&options3d}
//DeadCode JIM 12Oct00 		#ifndef NDEBUG 
//DeadCode JIM 12Oct00 			,{IDS_CONTINUE,NULL,Pseudo3D}
//DeadCode JIM 12Oct00 		#endif
//DeadCode JIM 12Oct00 	},
//DeadCode JIM 12Oct00 	FragInit
//DeadCode JIM 12Oct00 };
//DeadCode JIM 12Oct00 
FullScreen RFullPanelDial::commsfrag=
{
	{
		{
			FIL_READYROOM_640,
			{{70,50}},
			15,440
		},
		{
			FIL_READYROOM_800,
			{	{60,16},
				{16,117},
			},
			20,560
		},
		{
			FIL_READYROOM,
			{
				{20,20},//,FullScreen::Resolutions::Dial::X2},
				{25,450},//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_READYROOM_1280,
			{{100,24},//,FullScreen::Resolutions::Dial::X2},
			{25,188},
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&readyroomhostmatch, SelectReadyRoom},
		{IDS_FLY,&quickmissionflight, FragFly}
	},
//DEADCODE AMM 14/01/00 	FragInit
	BoBFragInit
};

FullScreen RFullPanelDial::radio=
{
	{
		{
			FIL_PAINTSHOP_640,
			{{15,180}},
			15,440
		},
		{
			FIL_PAINTSHOP_800,
			{{20,230}},
			20,570
		},
		{
			FIL_RADIO,
			{{25,50}},//,FullScreen::Resolutions::Dial::X2}},
			25,720
		},
		{
			FIL_PAINTSHOP_1280,
			{{40,400}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,&readyroomhostmatch, SelectReadyRoomFromRadio},
		{IDS_RESETMSG,&radio, ResetMessages},
//DeadCode AMM 17Nov98 		{IDS_QUICKMISSION1,&selectsession},
//DeadCode AMM 17Nov98 		{IDS_LOADGAME,&quickmission},
//DeadCode AMM 17Nov98 		{IDS_SCAMPAIGNSELECT7,&campaignselect},
//DeadCode AMM 17Nov98 		{IDS_VISITORS,&visitorsbook},
	},
	RadioInit
};

FullScreen RFullPanelDial::paintshop=
{
	{
		{
			FIL_PAINTSHOP_640,
			{{15,180},
			{25,354},//FullScreen::Resolutions::Dial::X2},
			{320,374}},//,FullScreen::Resolutions::Dial::X2}},
			15,440
		},
		{
			FIL_PAINTSHOP_800,
			{{32,200},
			{32,464},//FullScreen::Resolutions::Dial::X2},
			{32,544}},//,FullScreen::Resolutions::Dial::X2}},
			20,570
		},
		{
			FIL_NULL,
//			{{25,280},
//			{25,560},//,FullScreen::Resolutions::Dial::X2},
//			{480,560}},//,FullScreen::Resolutions::Dial::X2}},
			{{86,330},
			{86,600},
			{86,680}},
			25,720
		},
		{
			FIL_PAINTSHOP_1280,
			{{40,450},
			{40,800},//FullScreen::Resolutions::Dial::X2},
			{40,910}},//,FullScreen::Resolutions::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,&readyroomhostmatch, SelectReadyRoom},
//DEADCODE RDH 27/01/00 		{IDS_VARIANTS,&variants,SelectRRVariants},
//DeadCode DAW 27Jun99 		{IDS_VARIANTS,&variants},
	},
	PaintShopInit
};

//FullScreen RFullPanelDial::readyroom=
//{
//	{
//		{
//			FIL_READYROOM_640,
//			{{70,50}},
//			15,440
//		},
//		{
//			FIL_READYROOM_800,
//			{{130,100}},
//			20,550
//		},
//		{
//			FIL_READYROOM_1024,
//			{{15,15,FullScreen::Resolutions::Dial::X2}},
//			25,720
//		},
//		{
//			FIL_READYROOM_1280,
//			{{130,150,FullScreen::Resolutions::Dial::X2}},
//			40,960
//		},
//	},
//	FullScreen::Align::HORIZ,
//	{
////DeadCode AMM 05Aug98 		{IDS_BACK,&multiplayer},
//		{IDS_QUICKMISSION1,&title,CleanUpComms},
//		{IDS_FRAG,&singlefrag, PrepareForFrag},
//		{IDS_FLY,&quickmission,CommsSelectFly},
//		{IDS_VISITORS,&visitorsbook},
//		{IDS_RADIO,&radio},
//		{IDS_PAINTSHOP,&paintshop},
//		{IDS_MAP,&paintshop},
//	},
//	ReadyRoomInit
//};

#define READYROOMLAYOUT										\
	{														 \
		{													  \
			FIL_READYROOM_640,								\
			{{70,50}},										 \
			15,440											  \
		},													   \
		{														\
			FIL_READYROOM_800,									 \
			{{60,15}},										  \
			20,560												   \
		},															\
		{															 \
			FIL_RAFFRAG,										  \
			{{15,15},{20,400}},			   \
			25,720														\
		},																 \
		{																  \
			FIL_READYROOM_1280,											   \
			{{100,20}},					\
			40,960															 \
		},																	  \
	}																		   

FullScreen RFullPanelDial::readyroomhostmatch=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_FRAG,&commsfrag},
		{IDS_FLY,&quickmissionflight,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_SETUP,&radio},
//DEADCODE RDH 27/01/00 		{IDS_PAINTSHOP,&paintshop},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestmatch=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_FRAG,&commsfrag},
		{IDS_FLY,&quickmissionflight,CanGuestJoin},	// to simulate selecting fly
		{IDS_SETUP,&radio},
//DEADCODE RDH 27/01/00 		{IDS_PAINTSHOP,&paintshop},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomhostmatchred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_FRAG,&commsfrag},
		{IDS_FLY,&quickmissionflight,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_SETUP,&radio},
//DEADCODE RDH 27/01/00 		{IDS_PAINTSHOP,&paintshop},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestmatchred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
//		{IDS_FRAG,&commsfrag},
		{IDS_FLY,&quickmissionflight,CanGuestJoin},				//DAW 27Jun99
		{IDS_SETUP,&radio},
//DEADCODE RDH 27/01/00 		{IDS_PAINTSHOP,&paintshop},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};

FullScreen RFullPanelDial::readyroomhostqmission=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
//		{IDS_FLY,&quickmission,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_SETUP,&radio},
//DEADCODE RDH 27/01/00 		{IDS_PAINTSHOP,&paintshop},
		{IDS_EDITMISSION,&commsquick},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestqmission=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_SETUP,&radio},
//DEADCODE RDH 27/01/00 		{IDS_PAINTSHOP,&paintshop},
		{IDS_VIEWMISSION,&quickview},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomhostqmissionred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
//		{IDS_FLY,&quickmission,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_RADIO,&radio},
		{IDS_EDITMISSION,&commsquick},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestqmissionred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_RADIO,&radio},
		{IDS_VIEWMISSION,&quickview},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};


FullScreen RFullPanelDial::readyroomhostcampaign=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
//		{IDS_FLY,&quickmission,CommsSelectFly},
		{IDS_VISITORS,&visitorsbook},
		{IDS_SETUP,&radio},
//DeadCode AMM 04Jan99 		{IDS_MAP,&paintshop},
//DEADCODE RDH 27/01/00 		{IDS_MAP,&paintshop,ReturnToMap},
		{IDS_CPS_PREFS,&options3d},

	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestcampaign=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_SETUP,&radio},
//DeadCode AMM 04Jan99 		{IDS_MAP,&paintshop},
//DeadCode AMM 18Feb99 		{IDS_MAP,&paintshop,ReturnToMap},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};

FullScreen RFullPanelDial::readyroomhostcampaignred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_VISITORS,&visitorsbook},
		{IDS_RADIO,&radio},
		{IDS_CPS_PREFS,&options3d},

	},
	ReadyRoomInit
};
FullScreen RFullPanelDial::readyroomguestcampaignred=
{
	READYROOMLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_FRAG,&commsfrag},
		{IDS_RADIO,&radio},
		{IDS_CPS_PREFS,&options3d},
	},
	ReadyRoomInit
};


FullScreen RFullPanelDial::campaignselect=
{
	{
		{
			FIL_CAMPAIGNSELECT_640,
			{{5,370},
			{50,30},
			{0,0}
			},
			540,10
		},
		{
			FIL_CAMPAIGNSELECT_800,
			{{7,380},
			{30,60},
			{30,20}
			},
			20,560
		},
		{
			FIL_PHASESELECT,
			{{150,10},
			{250,500},													//RDH 30/03/00
			{316,144}
			},
			35,710
		},
		{
			FIL_CAMPAIGNSELECT_1280,
			{{40,800},	
			{120,150},		//smacker
			{60,150}		//text
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&title},
//DEADCODE RDH 26/10/99 		{IDS_FILM,NULL,StartCampSmacker},
//DEADCODE RDH 26/10/99 		{IDS_BACKGROUND,NULL,StartCampBackground},
//DEADCODE RDH 26/10/99 		{IDS_OBJECTIVES,NULL,StartCampObjectives},
		{IDS_BEGIN,&campaignentername},
	},
	CampaignSelectInit
};

FullScreen RFullPanelDial::campaignentername=
{
	{
		{
			FIL_CAMPAIGNSELECT_640,
			{{5,370},
			{50,30},
			{0,0}
			},
			540,10
		},
		{
			FIL_CAMPAIGNSELECT_800,
			{{7,380},
			{30,60},
			{30,20}
			},
			20,560
		},
		{
			FIL_PHASESELECT,
			{{316,88},
			{250,500},													//RDH 30/03/00
			{316,144}
			},
			35,710
		},
		{
			FIL_CAMPAIGNSELECT_1280,
			{{40,800},	
			{120,150},		//smacker
			{60,150}		//text
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&title},
		{IDS_BEGIN,NULL,LaunchMapFirstTime},
		{0,&campaignselect},
		{0,&gametype},
		{0,&singleplayer},
	},
	CampaignEnterNameInit
};

FullScreen RFullPanelDial::enddayreview=
{
	{
		{
			FIL_CAMPAIGNSELECT_640,
			{{5,370},
			{50,30},
			{0,0}
			},
			540,10
		},
		{
			FIL_CAMPAIGNSELECT_800,
			{{7,380},
			{30,60},
			{30,20}
			},
			20,560
		},
		{
			FIL_ENDOFDAYREVIEW,
			{{10,30},
			{513, 437},
			{507, 72}													//RDH 31/03/00
			},
			35,710
		},
		{
			FIL_CAMPAIGNSELECT_1280,
			{{40,800},	
			{120,150},		//smacker
			{60,150}		//text
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
#ifndef BOB_PREVIEW_VER
		{IDS_CONTINUE,NULL,ReturnToMapAfterReview},
#else
		{IDS_CONTINUE,&title},
		{IDS_DISABLEDEMO,&title},
#endif
	},
	EndDayReviewInit
};
FullScreen RFullPanelDial::lastdayreview=
{
	{
		{
			FIL_CAMPAIGNSELECT_640,
			{{5,370},
			{50,30},
			{0,0}
			},
			540,10
		},
		{
			FIL_CAMPAIGNSELECT_800,
			{{7,380},
			{30,60},
			{30,20}
			},
			20,560
		},
		{
			FIL_ENDOFDAYREVIEW,
			{{10,30},
			{513, 437},
			{507, 72}													//RDH 31/03/00
			},
			35,710
		},
		{
			FIL_CAMPAIGNSELECT_1280,
			{{40,800},	
			{120,150},		//smacker
			{60,150}		//text
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,&title},
	},
	EndDayReviewInit
};

FullScreen RFullPanelDial::campover=
{
	{
		{
			FIL_CAMPAIGNSELECT_640,
			{{5,370},
			{5,5},
			{5,5}
			},
			20,560
		},
		{
			FIL_CAMPAIGNSELECT_800,
			{{7,500},
			{5,5},
			{5,5}
			},
			20,560
		},
		{
			FIL_NULL,
			{{0,0},//,FullScreen::Resolutions::Dial::X2},
			{100,50},
			{5,5}//,FullScreen::Resolutions::Dial::X2}
			},
			25,720
		},
		{
			FIL_CAMPAIGNSELECT_1280,
			{{40,800},//FullScreen::Resolutions::Dial::X2},
			{5,5},
			{5,5}//,FullScreen::Resolutions::Dial::X2}
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&title},
	},
	CampaignOverInit
};
#define  MAPSPECIALLAYOUT									   \
	{															\
		{														 \
			FIL_CAMPAIGNSELECT_640,								  \
			{{5,370},											   \
			{5,5},													\
			{5,5}													 \
			},														  \
			540,10													   \
		},																\
		{																 \
			FIL_CAMPAIGNSELECT_800,										  \
			{{7,500},													   \
			{10,24},															\
			{10,320}															 \
			},																  \
			20,560															   \
		},																		\
		{																		 \
			FIL_NULL,											  \
			{{10,500},						   \
			{80,40},																\
			{80,360}							 \
			},																		  \
			25,720																	   \
		},																				\
		{														\
			FIL_CAMPAIGNSELECT_1280,							 \
			{{40,800},		  \
			{100,50},												   \
			{100,450}				\
			},														 \
			40,960													  \
		},															   \
	}

FullScreen RFullPanelDial::mapspecials=
{
	MAPSPECIALLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,NULL,LaunchMapIfAlive},
	},
	MapSpecialsInit
};

FullScreen RFullPanelDial::deadpilot=
{
	MAPSPECIALLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_TITLE7,&singleplayer,CleanUpComms},  //AMM 16/05/99
		{IDS_CONTINUE,NULL,ContinueAlthoughDead},
		{IDS_LOADGAME,NULL,ReloadBecauseDead},
	},
	DeadPilotInit
};
FullScreen RFullPanelDial::specialdebrief=
{
	MAPSPECIALLAYOUT,
	FullScreen::Align::HORIZ,
	{
		{IDS_CONTINUE,NULL,ContinueAfterSpecialDebrief},
	},
};


FullScreen RFullPanelDial::quickview=
{
	{
		{
			FIL_QUICKMISSION_640,
			{{15,15}},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{{20,20}},
			20,560
		},
		{
			FIL_QUICKSHOTMAIN,
			{
				{25,20},//, FullScreen::Dial::X2},
			},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{{40,100}},//,FullScreen::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_READYROOM,&readyroomhostmatch, SelectReadyRoom}
	},
	QuickViewInit
};


FullScreen RFullPanelDial::commsquick=
{
	{
		{
			FIL_QUICKMISSION_640,
			{{15,15}},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{{20,20},{20,234}},
			20,560
		},
		{
			FIL_QUICKSHOTMAIN,
			
			{{25,20},{25,300},{600,300}},//, FullScreen::Dial::X2},},
			
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{{40,100},{40,375}},//,FullScreen::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
//DEADCODE AMM 07/03/00 		{IDS_TITLE7,&title,CleanUpComms},
		{IDS_TITLE7,&title,AllowExitFromComms},
//		{IDS_QUICKMISSION1,&multiplayer},
//DEADCODE RDH 27/01/00 		{IDS_VARIANTS,&variants},
		{IDS_READYROOM,&readyroomhostmatch, SelectReadyRoom}
	},
	QuickMissionInit
};

#endif	//BOB_DEMO_VER

FullScreen RFullPanelDial::quickmission=
{
	{
		{
			FIL_QUICKMISSION_640,
			{{15,15},{15,200}},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{{20,20},{20,234},{400,400}},
			20,560
		},
		{
			FIL_QUICKSHOTMAIN,
			{{25,20},{25,250},{600,300}}, //25
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{{40,100},{40,375}},//,FullScreen::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_BACK,&title,CheckForDemo},
//DEADCODE RDH 28/10/99 		{IDS_VARIANTS,&variants},
//DeadCode RDH 9Aug00  		{IDS_QUICKMISSION2,&quickmissiondebrief},						//RDH 28/02/00
		{IDS_FLY,&bobfrag,CheckForMissingMission}						//RJS 30Jul00
	},
	QuickMissionInit
};
FullScreen RFullPanelDial::bobfrag=
{
	{
		{
			FIL_QUICKMISSION_640,										//RDH 14/03/00
			{{15,15},{15,200}},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{{20,20},{20,234}},
			20,560
		},
		{
			FIL_LWFRAG,
			{{20,20},{20,800}},//, FullScreen::Dial::X2},},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{{40,100},{40,375}},//,FullScreen::Dial::X2}},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
//DEADCODE RDH 28/02/00 		{IDS_BACK,&title,CheckForDemo},
		{IDS_BACK,&quickmission,ReturnToMap},
		{IDS_CONFIGGAME,&flightoptions,FragBackupOptions},
//DEADCODE RDH 28/10/99 		{IDS_VARIANTS,&variants},
//DeadCode DAW 09Jul99 		{IDS_QUICKMISSION2,&quickmissiondebrief},
//DeadCode AMM 10Jul00 		{IDS_FLY,&quickmissionflight}
// need to backup savegame for replay
		{IDS_FLY,&quickmissionflight,FragFly2}							//AMM 10Jul00
	},
	BoBFragInit
};
FullScreen RFullPanelDial::quickmissionflight=
{

	{	{FIL_NULL,{0,0},50,400},
		{FIL_NULL,{0,0},50,600},
		{FIL_NULL,{0,0},50,700},
		{FIL_NULL,{0,0},50,1000}
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION2,NULL,QuitFlying}
	},
	StartFlying
};

FullScreen RFullPanelDial::quickmissiondebrief=
{
	{
		{
			FIL_QUICKMISSION_640,
			{
				{15,15},
				{15,190}
			},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{
				{20,20},
				{20,234}
			},
			20,560
		},
		{
			FIL_QUICKSHOTDEBRIEF,
			{
				{25,25},//FullScreen::Resolutions::Dial::X2},
				{25,300},//FullScreen::Resolutions::Dial::X2},
			},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{
				{40,100},//FullScreen::Resolutions::Dial::X2},
				{40,380},//FullScreen::Resolutions::Dial::X2},
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&quickmission,IfCommsToReadyRoom},
		{IDS_REPORT,NULL},
		{IDS_DIARY,&quickmissiondebriefgrnd},
#ifndef	 BOB_DEMO_VER
		{IDS_REPLAYTITLE,&replaysave,DebriefReplayCheck}								//AMM 10Feb99
#endif
	},
	QuickMissionDebriefInit
};
	
FullScreen RFullPanelDial::quickmissiondebriefgrnd=
{
	{
		{
			FIL_QUICKMISSION_640,
			{
				{15,15},
				{15,190}
			},
			15,440
		},
		{
			FIL_QUICKMISSION_800,
			{
				{20,20},
				{20,234}
			},
			20,560
		},
		{
			FIL_QUICKSHOTDEBRIEF,
			{
				{25,25},//FullScreen::Resolutions::Dial::X2},
				{25,300},//FullScreen::Resolutions::Dial::X2},
			},
			25,710
		},
		{
			FIL_QUICKMISSION_1280,
			{
				{40,100},//FullScreen::Resolutions::Dial::X2},
				{40,380},//FullScreen::Resolutions::Dial::X2},
			},
			40,960
		},
	},
	FullScreen::Align::HORIZ,
	{
		{IDS_QUICKMISSION1,&quickmission,IfCommsToReadyRoom},
		{IDS_REPORT,&quickmissiondebrief},
		{IDS_DIARY,NULL},
#ifndef	 BOB_DEMO_VER
		{IDS_REPLAYTITLE,&replaysave,DebriefReplayCheck}								//AMM 10Feb 99
#endif
	},
	QuickMissionDebriefGrndInit
};


//DEADCODE RDH 27/01/00 FullScreen RFullPanelDial::variants=
//DEADCODE RDH 27/01/00 {
//DEADCODE RDH 27/01/00 	{
//DEADCODE RDH 27/01/00 		{
//DEADCODE RDH 27/01/00 			FIL_QUICKMISSION_640,
//DEADCODE RDH 27/01/00 			{{15,15}},
//DEADCODE RDH 27/01/00 			15,440
//DEADCODE RDH 27/01/00 		},
//DEADCODE RDH 27/01/00 		{
//DEADCODE RDH 27/01/00 			FIL_QUICKMISSION_800,
//DEADCODE RDH 27/01/00 			{{20,20}},
//DEADCODE RDH 27/01/00 			20,560
//DEADCODE RDH 27/01/00 		},
//DEADCODE RDH 27/01/00 		{
//DEADCODE RDH 27/01/00 			FIL_NULL,
//DEADCODE RDH 27/01/00 			{
//DEADCODE RDH 27/01/00 				{40,40},// FullScreen::Dial::X2},
//DEADCODE RDH 27/01/00 			},
//DEADCODE RDH 27/01/00 			25,710
//DEADCODE RDH 27/01/00 		},
//DEADCODE RDH 27/01/00 		{
//DEADCODE RDH 27/01/00 			FIL_QUICKMISSION_1280,
//DEADCODE RDH 27/01/00 			{{40,100}},//,FullScreen::Dial::X2}},
//DEADCODE RDH 27/01/00 			40,960
//DEADCODE RDH 27/01/00 		},
//DEADCODE RDH 27/01/00 	},
//DEADCODE RDH 27/01/00 	FullScreen::Align::HORIZ,
//DEADCODE RDH 27/01/00 	{
//DEADCODE RDH 27/01/00 		{IDS_QUICKMISSION1,&quickmission, ExitVariant}
//DEADCODE RDH 27/01/00 	},
//DEADCODE RDH 27/01/00 	VariantsInit
//DEADCODE RDH 27/01/00 };

