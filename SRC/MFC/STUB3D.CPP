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

//
//WinMode:	stub3d.cpp
//
//TASK:		manages the 3d thread
//
//ROUTINES:	presently about 5 routines:
//
//	MakeInteractive(WinMode,Coords)
//	MakePassive(WinMode,Coords)
//	MakeResize(WinMode,Coords)
//	ToggleInteractive(bool)
//	TogglePaused(bool)
//	ToggleAccel(bool)
//	DeleteWorld()
//	
//	WinMode:	
//		FullScreen/Windowed/DualScreen 
//							0x0000,0x1000,0x2000
//		Accelerated			0x000=no,0x100=yes,
//							0x10n=specific card									
//							0x1m0=specific mode


#include	"stdafx.h"
#include	<afxmt.h>
#include	<dinput.h>
#include	<mmsystem.h>
#include	"dosdefs.h"

#include	"stub3d.h"
#include	"gameset.h"
#include	"keytest.h"


#include	"hardpasm.h"
#include	"worldinc.h"
#include	"aaa.h"
#include	"flymodel.h"
#include	"mytime.h"
#include	"ai.h"
#include	"persons2.h"
#include	"collided.h"
#include	"3dcode.h"
#include	"world.h"
#include	"shapes.h"
//#include	"lstream.h"
#include	"3dinstr.h"
#include	"savegame.h"
#include	"winmove.h"
#include	"miles.h"
#undef LPDDCAPS
#include	"win3d.h"
#include	"polygon.h"
#include	"Analogue.h"
#include	"transite.h"
#include	"ViewSel.h"
#include	"rchatter.h"										//RJS 11Jun98
#include	"replay.h"
#include	"globrefs.h"
#include	"replay.h"
#include	"aggrgtor.h"
#include	"OverLay.h"
#include	"messengn.h"										//RJS 27Jan99
#include	"3dcom.h"											//RJS 08Apr99
#include	"..\lib3d\lib3d.h"
#include	"mytime.h"
#include "model.h"
#include "ai.h"
#include	"sqddiary.h"										//RJS 18Feb00
#include "grid.h"
#include "monotxt.h"
#include "fastmath.h"
enum	{BUFFERED_KEYS=100};


#ifndef	NDEBUG
//#define	DBGMEMTEST
#endif

//#define	_FRAMESHITE_

//#define COMMSTIMERDEBUG

//extern ULong 
//		GR_FriendlyScoutType00,									//JIM 09Apr96
//		GR_Quit3DNow,
//		GR_OkToQuit3DNow;
static	volatile Bool	insidetimer = FALSE;

//inline	int	LockExchange(int* loc,int newval=0)
//{
//	int rv;
//	_asm	{	mov		eax,newval
//				mov		ebx,loc
//				xchg	ds:[ebx],eax
//				mov		rv,eax
//			}
//	return	rv;
//}
extern Replay _Replay;
//DeadCode RJS 22Jun100 extern UByte videoBuffer;
//DEADCODE PD 03/12/99 extern bool mono3d;

///////////////////////////////////////////////////////////////////////

//HANDLE	View3d::htable[NUM_EVENTS];
//LPDIRECTINPUT  Inst3d::Master_3d.g_lpDI=NULL;
//LPDIRECTINPUTDEVICE  Inst3d::Master_3d.g_lpDIDevice=NULL;
//HINSTANCE	View3d::hinst=NULL;
//HWND		View3d::hwind=NULL;
///View3d*		Inst3d::viewedwin=NULL;
//char		Inst3d::lastkeys[256]={0};
//Inst3d*		Inst3d::Master_3d.currinst=NULL;
KeyMap3d*	Inst3d::commonkeymaps=NULL;
extern	KeyMapping	*Debug3dMapTable;

// *********************************** Jon's debug timer stuff *******************************************
#define DO_TIMER_DIAGS
#ifdef DO_TIMER_DIAGS
#include <fstream.h> // for filestream stuff..
int timerBufferI = 0;
//tempcode JON 21/03/01	const int TIMER_BUFFER_SIZE = 500;
//tempcode JON 21/03/01	LARGE_INTEGER timerBufferIn[TIMER_BUFFER_SIZE];
//tempcode JON 21/03/01	LARGE_INTEGER timerBufferOut[TIMER_BUFFER_SIZE];
LARGE_INTEGER* timerBufferIn;
LARGE_INTEGER* timerBufferOut;
#endif
// *********************************** End of Jon's stuff ************************************************

Mast3d	Master_3d;
///////////////////////////////////////////////////////////////////////
enum	{REQUIREDTIMEPERIOD=0};
Mast3d::Mast3d()
{
	TIMECAPS tcaps;
	timeGetDevCaps ( &tcaps, sizeof (TIMECAPS));

	UINT delay=Timer_Code.FRAMETIME*10; // want millisecs 
	timeBeginPeriod (REQUIREDTIMEPERIOD);	  //timeEndPeriod

	uTimerID = timeSetEvent (delay, REQUIREDTIMEPERIOD, Master_3d.StaticTimeProc, (int)&Master_3d, TIME_PERIODIC); //AMM 25/11/99
	
	currinst=NULL;
//DeadCode JIM 20Oct00 	int mv=0;
	ticknum=0;
	g_lpLib3d=Lib3DCreate(IID_ILib3D);
}

void Mast3d::Init(HINSTANCE			Hinst,HWND				Hwind)
{

	winst=Hwind;
	hinst=Hinst;
	MainInit();
	if (FAILED(DirectInputCreate(hinst, DIRECTINPUT_VERSION, &g_lpDI, NULL)))
		_Error.EmitSysErr("Can't access DirectInput!");
			;;;;;//ERROR 

}

void	Mast3d::BigWin()
{
//	_DirectDraw::lpDirectDD->SetSmackerMode(false,Master_3d.winst);
	AfxGetMainWnd()->ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border!
//	SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,FALSE,NULL,NULL);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
}
void	Mast3d::SmallWin()
{
//	_DirectDraw::lpDirectDD->SetSmackerMode(true,Master_3d.winst);
	AfxGetMainWnd()->ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border!
//	SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,FALSE,NULL,NULL);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
}

void	Mast3d::MainInit(void)
{
	FILEMAN.InitFileSystem(); // moved to a place where it will happen sooner (Mainfrm.cpp) DBM

	Image_Map.InitImageMaps();									//DAW 27Oct98

	_DPlay.Implemented = FALSE;

 	_Miles.Init((ULong)winst);											//RJS 02Nov98
	_Radio.Init();														//RJS 16Aug00

	if ( g_lpLib3d->Initialise(winst, fastMath.fastSqrtTable ) != S_OK ) 
	{
		_Error.ReallyEmitSysErr("Unable to find suitable DirectX 7.0 or later 3D Driver");
	}
	g_lpLib3d->GetDefaultDriverAndMode(Save_Data.hDriver,Save_Data.hMode);

//DEADCODE PD 03/12/99 	Display* Whole_Screen;
//	if (DDrawInitialised==FALSE)
//	{
//		_Main.DDrawInitialised = TRUE;

//		_DirectDraw::lpDirectDD=new DirectDD;
//		_DirectDraw::lpDirectDD->SetSmackerMode(true,Master_3d.winst);
//		_DirectDraw::lpDirectDD->SetSmackerMode(false,Master_3d.winst);
		///_Analogue.Test();

//		if((Whole_Screen = new Display) == NULL)
//			_Error.EmitSysErr(__FILE__":Failed to create screen record\n");
//		Whole_Screen->InitDirectDraw ();
//		delete Whole_Screen;

//		Whole_Screen->DD.hWnd = hwind;
 //		if(	Whole_Screen->Init(NULL) == FALSE)	
  //			_Error.EmitSysErr(__FILE__":Failed to initialise screen record\n");
//	}
	Grid_Base::OpenGridFiles();

//Resources tell me which language now, and they haven't been loaded yet!	OverLay.FindLanguage();										//RJS 07Dec00
}
	
//////////////////////////////////////////////////////////////////////
struct	Post3DInfo
{
	Coords3D	position;
	UWord		waypoint;
	UWord		fuelkilos;
	UniqueID	unfriendly;
	UWord		movecode;

	void		Set(AirStrucPtr a);
#ifdef	PACKAGE_INCLUDED
	int			Get(info_airgrp* a,Profile::Squad* sq,UniqueID route);	//returns fuel
#endif
	static		Post3DInfo*	New();
	void		Delete();

};
Mast3d::~Mast3d()
{
	Dead_Stream.ClrWorldDead();
	Grid_Base::CloseGridFiles();
	Persons3::post3dinfo->Delete();

	_Miles.ShutDownSound();
	Inst3d*	ilist=currinst;
	while (ilist)
	{
		currinst=ilist->nextinst;
		delete ilist;
		ilist=currinst;
	}
	if (uTimerID)
		timeKillEvent(uTimerID);
	uTimerID=0;
	timeEndPeriod(REQUIREDTIMEPERIOD);	  //timeEndPeriod
	if (Master_3d.g_lpDI)
	{
		Master_3d.g_lpDI->Release();
		Master_3d.g_lpDI=NULL;
	}
//	delete _DirectDraw::lpDirectDD;
	g_lpLib3d->Release();

}
//MakeInteractive
void	Mast3d::Stop()
{
	if (uTimerID)
		timeKillEvent(uTimerID); 
	uTimerID=0;
}

///////////////////////////////////////////////////////////////////////
Inst3d::Inst3d(bool flag)
{
#ifdef DO_TIMER_DIAGS
//tempcode JON 21/03/01		if ( gameSettings.m_bDoTimerDiags == true )
//tempcode JON 21/03/01		{
	timerBufferIn = new LARGE_INTEGER[ gameSettings.m_dwTimerBufferSize ]; // will be 1 if no diags set
	timerBufferOut = new LARGE_INTEGER[ gameSettings.m_dwTimerBufferSize ];
//tempcode JON 21/03/01		}

	// clear my timer stores.
	for ( int i = 0; i<gameSettings.m_dwTimerBufferSize; i++ )
	{
		timerBufferIn[i].QuadPart = timerBufferOut[i].QuadPart = 0i64;
	}
#endif

	_DPlay.SimulateExitKey = FALSE;										//RJS 20Oct00

	mapview=flag;
//DEADCODE PD 03/12/99 	mono3d=false;
//DEADCODE JIM 29/03/99 	FILEMAN.flushcachedfiles();
 	paused=TRUE;
	accel=FALSE;
	interactive=FALSE;
	commonkeymaps=(KeyMap3d*) Key_Tests.reftable3d.flat;
	world=new WorldStuff;
	(&world)->SetViewpoint(NULL);
	blocktick=blockticks=TRUE;	//no movecodes
	viewedwin=NULL;
	nextinst=Master_3d.currinst;
	Master_3d.currinst=this;
	livelist=NULL;
	Manual_Pilot.ControlledAC2=NULL;
	GR_Quit3DNow=0;
	GR_OkToQuit3DNow=0;
//DEADCODE DAW 28/03/99 	Timer_Code.Quit3DTimer=500;
	_Replay.DeleteReplayLog(); // want new log every time we enter non-playback 3D//AMM 07Oct98
	_Replay.SuperHeaderStored=false;
	_Miles.ResetSoundFlags();
	Three_Dee.InitialiseCache();
	Land_Scape.Init(Master_3d.g_lpLib3d);
	Three_Dee.current_world=&world;
	//Load in the shape files requested by the battle field file loads
//DeadCode RJS 6Oct00 	SHAPESTUFF.LoadRequiredShapes();
	Three_Dee.livelist=livelist;
	_Collide.tdalt=TRUE;
//DEADCODE DAW 28/03/99 	Timer_Code.accel=FALSE;
	Trans_Obj.View_Point=NULL;
	Key_Tests.Reg3dConv(FIL_3D_KEYBOARD_TABLE);
	timeofday=11*60*60*100;
	OverLay.SetToMapViewScreen();
	Dead_Stream.GetWorldDead(&world);				//RDH 02Oct96	  //JIM 03/06/99

	Squad_Diary.New3DSession();											//RJS 30Oct00
	Trans_Obj.Enter3D();										//RJS 09Mar00

	_Miles.KillAll();													//RJS 6Oct00
	_Radio.SetUpRandomVoices();											//RJS 6Oct00

// Purge...
	if (	FILEMAN.getTotalMem() <= (32*1024*1024)
		||	(	(FILEMAN.getTotalMem() <= (64*1024*1024))
			 &&	(Save_Data.vol.rchat || Save_Data.hardwareconfig[HW_SFXQUALITY])
			)
		)
		fileblocklink::deletelink(-1);
}

Inst3d::Inst3d()
{
#ifdef DO_TIMER_DIAGS
//tempcode JON 21/03/01		if ( gameSettings.m_bDoTimerDiags == true )
//tempcode JON 21/03/01		{
	timerBufferIn = new LARGE_INTEGER[ gameSettings.m_dwTimerBufferSize ]; // will be 1 if no diags set
	timerBufferOut = new LARGE_INTEGER[ gameSettings.m_dwTimerBufferSize ];
//tempcode JON 21/03/01		}

	// clear my timer stores.
	{
	for ( int i = 0; i<gameSettings.m_dwTimerBufferSize; i++ )
	{
		timerBufferIn[i].QuadPart = timerBufferOut[i].QuadPart = 0i64;
	}
	}
#endif

	
	_DPlay.SimulateExitKey = FALSE;										//RJS 20Oct00

	_Miles.KillAll();													//RJS 6Oct00

	int oldprec=GETPREC();
	SETPREC(3);

	OverLay.MouseSet=false;												//AMM 13Jul00
	OverLay.MouseRestore=false;											//AMM 13Jul00
	Squad_Diary.New3DSession();											//RJS 30Oct00
	Trans_Obj.Enter3D();										//RJS 09Mar00

	mapview=false;
//DEADCODE PD 03/12/99 	if (_Replay.Playback && !Save_Data.gamedifficulty[GD_GUNCAMERACOLOUR])
//DEADCODE PD 03/12/99 		mono3d=true;
//DEADCODE PD 03/12/99 	else
//DEADCODE PD 03/12/99 		mono3d=false;
	//Inst3d itself:
//DEADCODE JIM 29/03/99 	FILEMAN.flushcachedfiles();
 	paused=TRUE;
	accel=FALSE;
	interactive=FALSE;
	commonkeymaps=(KeyMap3d*) Key_Tests.reftable3d.flat;
	world=new WorldStuff;
	blocktick=blockticks=0;
	viewedwin=NULL;
	nextinst=Master_3d.currinst;
	Master_3d.currinst=this;
	_Replay.inst=this;											//AMM 11May99
	livelist=NULL;
//	Copied from State3d:
	Persons3	Persons_2(world,NULL,this);

//  MMC.specialeventbits = 0;									//RDH 23Sep96
//	GR_FriendlyScoutType00 = Miss_Man.camp.squad[0].actype;		//RDH 17Feb97

	Manual_Pilot.ControlledAC2 = NULL;							//RDH 24Oct96
	GR_Quit3DNow=0;
	GR_OkToQuit3DNow=0;
//DEADCODE DAW 28/03/99 	Timer_Code.Quit3DTimer = 500;

	_Replay.DeleteFileAndGlobRefList(_Replay.bfgrlist);	//need to reset bfields if new mission

	if (!_Replay.Playback)
	{
		_Replay.badrecord=true;									//AMM 09Mar99
		_Replay.DeleteReplayLog(); // want new log every time we enter non-playback 3D//AMM 07Oct98
	}

	if (Save_Data.gamedifficulty[GD_GUNCAMERAATSTART] && !_DPlay.Implemented && !_Replay.Playback)			//AMM 05Jan99
	{
		_Replay.Record=TRUE;
	}
	
	_Replay.SuperHeaderStored=false;
	
//TEMP	_Miles.DiscardMusic();	//previous debrief may be playing?
//	Three_Dee.livelist=NULL;	//AAA list 
	Art_Int.CleanUp();			//A/C recognition list

	timeofday = 11*60*60*100;										//PD 19Jan99

//TEMP	Timer_Code.realtime = Miss_Man.camp.currmission->timeofday * 100;//RDH 02Aug96
	_Miles.ResetSoundFlags();									//DAW 01Sep98
	_Radio.SetUpRandomVoices();										//RJS 08Jun99
//PD 30Sep96 - this needs to be done before PERSONS_2 call
//TEMP	_Collide.tdalt = FALSE;
//TEMP	LandStream.InitialiseCache();								//PD 30Sep96
 	_Collide.tdalt = FALSE;
//	LandStream.InitialiseCache();
	Three_Dee.InitialiseCache();
	Land_Scape.Init(Master_3d.g_lpLib3d);
	Persons_2.LoadSetPiece(&world);//RDH 25Mar96
	Dead_Stream.GetWorldDead(&world);				//RDH 02Oct96

	Manual_Pilot.SetWorldPtr(&world);							//PD 25Jun96
	_Collide.SetWorld(&world);								//PD 22Mar96
	MobileItem::SetWorld(&world);
	Three_Dee.current_world=&world;
	Trans_Obj.CleanUpTrailList();								//JIM 26Mar99

	//Load in the shape files requested by the battle field file loads
//DeadCode RJS 6Oct00 	SHAPESTUFF.LoadRequiredShapes();
 	//Set up animation data...
	(*world).SetLaunchers();										//RJS 21Aug96

	livelist= new LiveList(&world);
	Three_Dee.livelist=livelist;

	Three_Dee.livelist->BackupSleepList();

	//Back-up miles flags first
	SWord	oldsfxvol = Save_Data.vol.sfx;							  //RJS 07/07/99
	SWord	oldsfxmusic = Save_Data.vol.music;						   //RJS 07/07/99
	SWord	oldsfxchat = Save_Data.vol.rchat;						   //RJS 07/07/99
																	  //RJS 07/07/99
	Save_Data.vol.sfx = 0;											   //RJS 07/07/99
	Save_Data.vol.music = 0;										  //RJS 07/07/99
	Save_Data.vol.rchat = 0;										  //RJS 07/07/99

	_MsgBuffer.SetPlayer(Persons2::PlayerGhostAC,Persons2::PlayerSeenAC);//RJS 05May00
	_Radio.Enter3D(true);												//RJS 17May00
 
	if(Persons2::PlayerSeenAC->fly.expandedsag)
		Persons2::PlayerSeenAC->PreExpandSags(Persons_2.baseSAGshape + 1);

	for(int i=0; i < Art_Int.ACARRAYSIZE * 2; i++)	//CSB 06/07/99	
 		Art_Int.VisibleCheck();

	for(i = 0; i < 10 * AaaMainList::SUBLISTSIZE; i++)								//CSB 14Aug00
		(*Three_Dee.livelist).sleeplist.Event();									//CSB 14Aug00

	//Restore miles flags...
	Save_Data.vol.sfx = oldsfxvol;									  //RJS 07/07/99
	Save_Data.vol.music = oldsfxmusic;								  //RJS 07/07/99
	Save_Data.vol.rchat = oldsfxchat;								  //RJS 07/07/99

	if (Persons2::PlayerSeenAC&&Persons2::PlayerSeenAC->classtype->aerobaticfactor==AEROBATIC_LOW)
	{
		_Replay.Record=FALSE;
	}

	if (_Replay.Record)											//AMM 14Jun99
	{															//AMM 14Jun99
		_Replay.lastRpmLeft = _Replay.lastRpmRight = 65535;		//RJS 21Jun00
		_Replay.InitPosBuffer();								//AMM 14Jun99
		_Replay.StoreFinalRecordData();							//AMM 14Jun99
	}															//AMM 14Jun99
	else if (_Replay.Playback)									//AMM 14Jun99
	{															//AMM 14Jun99
		_Replay.LoadFinalPlaybackData();						//AMM 14Jun99
																//AMM 14Jun99
		if (!_Replay.Playback)									//AMM 14Jun99
			_Error.EmitSysErr("Error reading playback log");	//AMM 14Jun99
	}															//AMM 14Jun99
	else														//AMM 14Jun99
		_Replay.InitPosBuffer();								//AMM 14Jun99

	_DPlay.BackupSeen();
	_DPlay.BackupGhost();

//	Timer_Code.GetLoopTime();

//  	MMC.specialeventbits = 0;									//RDH 01Dec96
//	MMC.newsevent = 0;											//RDH 01Dec96
	_Collide.tdalt = TRUE;										//PD 30Sep96

//	_MsgBuffer.SetPlayer(Persons2::PlayerGhostAC,Persons2::PlayerSeenAC);			//RJS 27Jan99

//DEADCODE DAW 28/03/99 	Timer_Code.accel = FALSE;									//PD 15Mar96
	Trans_Obj.View_Point=Manual_Pilot.ControlledAC2;
	//	LandStream.View_Point=Manual_pilot.ControlledAC2;

//	Timer_Code.paused = TRUE;									//PD 15Mar96
//	LandStream.BigInit();										//PD 18Nov96
//	Timer_Code.paused = FALSE;									//PD 15Mar96
//	FILEMAN.preload();											//RJS 02Dec96

	SendInit2Packet ();											//ARM 15Aug96

// clear locks

	Key_Tests.Reg3dConv(FIL_3D_KEYBOARD_TABLE);

	if (_Replay.RestorePosition)
	{
		_Replay.RestorePlaybackPosition();
	}

// Purge...
	if (	FILEMAN.getTotalMem() <= (32*1024*1024)
		||	(	(FILEMAN.getTotalMem() <= (64*1024*1024))
			 &&	(Save_Data.vol.rchat || Save_Data.hardwareconfig[HW_SFXQUALITY])
			)
		)
		fileblocklink::deletelink(-1);

//	while	(Timer_Code.TestLoopTime()<Timer_Code.FRAMEMIN)
//	{}//WAIT FOR FRAMEMIN
  		//_Mouse.Move();
//	while (Timer_Code.TestMsgTime())	{}
//	Timer_Code.msgcounttime=0;
//	Timer_Code.GetLoopTime();	//ensure min. frametime...
//	Whole_Screen->SetMouseImage(0);

//DEADCODE rdh 13/04/99 #ifndef NDEBUG		//if not defined then no debug
//DEADCODE DAW 13/04/99 //DEADCODE rdh 13/04/99 	if (_DPlay.Implemented)
//DEADCODE DAW 13/04/99 //just have pause when in debug mode
//DEADCODE DAW 13/04/99 		paused=FALSE;
//DEADCODE DAW 13/04/99 #endif
//DeadCode AMM 29Mar99 	_Replay.PrefsInterrupt=RS_NOINTERRUPT;

#ifndef NDEBUG
//DeadCode AMM 9Aug00 		if (GETPREC()!=3)
//DeadCode AMM 9Aug00 			INT3;
#endif
	SETPREC(oldprec);
}
///////////////////////////////////////////////////////////////////////
Inst3d::~Inst3d()
{
//DeadCode CSB 11Sep00 	Mono_Text.PrintAt(30,20,(UByte*)"~Inst3d[                         ");
	_Miles.KillAll();

	Squad_Diary.UpdatePlayerLog(Manual_Pilot.ControlledAC2);//RJS 18Feb00

	//FIRST, remove all viewports:
	Paused(TRUE);
	{
		View3d* sptr=viewedwin;
		while (sptr)
		{
			sptr->SetEndDraw(View3d::D_CLOSE);
			sptr=sptr->nextview;
		}
		sptr=viewedwin;
		Interactive(NULL);
		viewedwin=NULL;
		while (sptr)
		{
			View3d* sp2=sptr;
			sptr=sptr->nextview;
			delete sp2;
		}
	}
	//Next, remove instance from list
	if (Master_3d.currinst)
	{
		Inst3d**	sptr=&Master_3d.currinst;
		while (*sptr!=this)
			sptr=&sptr[0]->nextinst;
		*sptr=nextinst;
	}

	//Next, start freeing resources:

	_DPlay.GameRunning=FALSE;

	if (!mapview)
	{
		Persons3 	Persons_3(world,NULL,this);
		if (!_Replay.Playback)
		{
	//DEADCODE JIM 16/11/99 		Art_Int.FakeMissionSuccess();
			Dead_Stream.SetWorldDead(world);				//RDH 02Oct96
	//DEADCODE JIM 16/11/99 		Dead_Stream.ScoreSGKills();
	//	Persons_3.EndGameScoring();
	//DEADCODE DAW 29/01/00 #ifndef	BOB_DEMO_VER
	//DEADCODE DAW 29/01/00 		Persons_3.ProcessLogList();
	//DEADCODE DAW 29/01/00 #endif	BOB_DEMO_VER
		}
		Persons_3.SaveAircraftPositions(this);

		Persons_3.FreeRoutes();
		Persons_3.FreeEvents();

//DEADCODE JIM 23/02/99 DON'T DO THIS!!!	Dead_Stream.ClrWorldDead();				//RDH 02Oct96

//	Timer_Code.PauseToggle(FALSE);
//	Timer_Code.AccelToggle(FALSE);
//DeadCode RDH 11Dec96 	Dead_Stream.SetWorldDead();
	// THIS LINE CAN CAUSE A CRASH									//ARM 06Mar97
//TempCode ARM 06Mar97 	AirStruc::EndGameScoring();									//RDH 11Dec96
//TEMP	if (!(MMC.specialeventbits[CAMPAIGNLOST]))					//RDH 11Dec96
//TEMP		Dead_Stream.SetWorldDead();								//RDH 11Dec96
//DeadCode JIM 06Oct96 	Persons_2.TankEndMission();
//	Whole_Screen->SetMouseImage(1);
	}
	else 
		Persons4::ShutDownViewFromMap();

	delete	livelist;
	Three_Dee.livelist=NULL;
	SHAPESTUFF.UnLoadRequiredShapes();
	Three_Dee.Done3D();											//DAW 30Nov95
 	Image_Map.UnLoadImageMaps();								//RJS 14Jun99
	if (!mapview) (*world).ClearWorld();
	delete Persons2::PlayerGhostAC;
	Persons2::PlayerSeenAC=NULL;
	Persons2::PlayerGhostAC=NULL;

	_Radio.SetUpRandomVoices();											//RJS 6Oct00

	if (_Replay.Playback)
	{
// want to remove deadlist and restore from save game, otherwise it becomes garbage

		Dead_Stream.ClrWorldDead();								//AMM 29Mar99

		if (_Replay.MapPlayback)									  //AMM 25/06/99
			_Replay.RestoreSaveGame();
		_Replay.ClosePlaybackLog();
		_Replay.RestorePrefs(false);
		RFullPanelDial::gamestate=(RFullPanelDial::GameStates)_Replay.PlaybackGameState;
	}
	else
	{
		_Replay.CloseRecordLog();
	}

// if I am exiting a comms game I always want to clear the dead items, if I rejoin
// in a coop game then the host will send me the dead item list

	if (_DPlay.PlayerCreated)											//AMM 23Oct00
	{																	//AMM 23Oct00
		Dead_Stream.ClrWorldDead();										//AMM 23Oct00
	}																	//AMM 23Oct00
	_Replay.inst=NULL;

//	Key_Tests.RegUIConv(INVALIDFILENUM);
//TEMP 	for (int i=0;i<MAX_VAPOURS;i++)	SHAPE.KillVapourStream(i);	//RJS 02Jun97

//TEMP	_Miles.StopAll();
//TEMP	_Miles.DiscardMusic();										//RJS 27Sep96
//TEMP	_Miles.FreeSamples();										//RJS 04Oct96
	_Miles.ResetSoundFlags();									//DAW 01Sep98
	if (!mapview) Art_Int.CleanUp();
	delete world;
	MobileItem::SetWorld(NULL);

	OverLay.pCurScr=OverLay.pNewScr=NULL;

	_Radio.Enter3D(false);										//RJS 17May00

// Purge...
	if (	FILEMAN.getTotalMem() <= (32*1024*1024)
		||	(	(FILEMAN.getTotalMem() <= (64*1024*1024))
			 &&	(Save_Data.vol.rchat || Save_Data.hardwareconfig[HW_SFXQUALITY])
			)
		)
		fileblocklink::deletelink(-1);

//DEADCODE JIM 29/03/99 	FILEMAN.flushcachedfiles();

//	RDialog::m_pView->ModifyStyleEx(RDialog::m_pView->GetExStyle(),NULL); // Bye bye annoying border!
	AfxGetMainWnd()->ModifyStyle(WS_THICKFRAME,NULL); // Bye bye border!
//DeadCode JIM 29Oct00 #if defined(NDEBUG)
//DeadCode JIM 29Oct00 	AfxGetMainWnd()->SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOACTIVATE+SWP_NOMOVE+SWP_NOSIZE);
//DeadCode JIM 29Oct00 #endif
//	SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,FALSE,NULL,NULL);
	AfxGetMainWnd()->ShowWindow(SW_SHOWMAXIMIZED);
//DeadCode CSB 11Sep00 	Mono_Text.Print((UByte*)"]~Inst3d");

#ifdef DO_TIMER_DIAGS
	if ( gameSettings.m_bDoTimerDiags==true ) // do we want to write out the timing information
	{
		class To
		{
		public:
			static char* str( __int64 v )
			{
				const int TEXT_SIZE = 32;
				const int BUFF_SIZE = 8;
				static char buff[TEXT_SIZE*BUFF_SIZE];
				static int curI = 0;
				curI++;
				curI%=BUFF_SIZE;
				_i64toa( v, buff+(TEXT_SIZE*curI), 10 );
				return buff+(TEXT_SIZE*curI);
			}
			static char* str( LARGE_INTEGER v )
			{
				return str( v.QuadPart );
			}
		};
		// Now we need to write this information to a log file
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency( &frequency );
		LARGE_INTEGER freqms;
		freqms.QuadPart = frequency.QuadPart/1000i64;
		fstream timeFile;
		timeFile.open( "AI_Timings.txt", ios::out );
		if ( timeFile.is_open() )
		{	
			timeFile << "Perfromance counter frequency " << To::str(frequency) << " ticks per second\n";
			int last = -1;
			int term = timerBufferI++;
			timerBufferI%=gameSettings.m_dwTimerBufferSize;
			while ( timerBufferI !=term )
			{
				timeFile 
					<< To::str(timerBufferIn[timerBufferI]) << " <-In" 
					<< " \tOut: " << To::str(timerBufferOut[timerBufferI])
					<< " \tDiff: " << To::str(timerBufferOut[timerBufferI].QuadPart - timerBufferIn[timerBufferI].QuadPart )
					<< " ticks - \t"
					<< " In: " << To::str(timerBufferIn[timerBufferI].QuadPart/freqms.QuadPart)
					<< " \tOut: " << To::str(timerBufferOut[timerBufferI].QuadPart/freqms.QuadPart)
					<< " \tDiff: " << To::str((timerBufferOut[timerBufferI].QuadPart - timerBufferIn[timerBufferI].QuadPart)/freqms.QuadPart)
					<< " ms";
				if ( last !=-1 )
				{
					timeFile 
						<< " \tGapTime: " << To::str(timerBufferIn[timerBufferI].QuadPart - timerBufferIn[last].QuadPart)
						<< " ticks - \t"
						<< To::str((timerBufferIn[timerBufferI].QuadPart - timerBufferIn[last].QuadPart)/freqms.QuadPart)
						<< " ms";
				}
				timeFile << "\n";
				last = timerBufferI;
				timerBufferI++;
				timerBufferI%=gameSettings.m_dwTimerBufferSize;
			}
			timeFile.close();
		}
	}
	delete[]timerBufferIn;
	delete[]timerBufferOut;
	timerBufferIn = timerBufferOut = NULL;
#endif


}
///////////////////////////////////////////////////////////////////////

bool	Inst3d::InThe3D()
{
	
	for (Inst3d*	t=Master_3d.currinst;t;t=t->nextinst)	
	{	 
		for (View3d*	v=t->viewedwin;v;v=v->nextview)
			if (v->drawing)	// &&  v->mode!=NONE)
				return TRUE;
	}
	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseDirectX
//Author		Paul.   
//Date			Mon 25 Jan 1999
//------------------------------------------------------------------------------
void Inst3d::ReleaseDirectX()
{
	//remove all viewports...
	for (Inst3d* t=Master_3d.currinst;t;t=t->nextinst)
	{
		t->Paused(TRUE);
		View3d *v=t->viewedwin;
		while (v)
		{
			v->WaitEndDraw(View3d::D_CLOSE);
			v->MakeResize(WinMode::NONE);
			v->CloseWindow(IDCANCEL);
			v=v->nextview;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestoreDirectX
//Author		Paul.   
//Date			Mon 25 Jan 1999
//------------------------------------------------------------------------------
void Inst3d::RestoreDirectX()
{
}

///////////////////////////////////////////////////////////////////////
View3d::View3d(Inst3d* ofinst,HWND newwin,CWnd* d):
	coords(0,0,0,0),E(NULL)

{
//DeadCode RJS 18May98 	_Miles.Init((ULong)newwin);									//RJS 03Apr98
	mfcwin=d;
	window=newwin;
	inst=ofinst;
	View_Point=NULL;
 	lastrealframetime=5;			//should be in for photo rotation //DAW 19/6/99
//DEADCODE PD 03/12/99 	Whole_Screen=NULL;
	mode=WinMode::NONE;
	drawing=D_NO;


	if (ofinst->Interactive())
	{	//Remember: The movecodes can see this view object from this point onwards!
		nextview=ofinst->Interactive()->nextview;
		ofinst->Interactive()->nextview=this;
	}
	else
	{
		nextview=ofinst->viewedwin;
		ofinst->viewedwin=this;
	}	//Remember: The movecodes can see this view object from this point onwards!
	AfxBeginThread( drawloop, this, THREAD_PRIORITY_NORMAL, 50000);
	//THREAD_PRIORITY_ABOVE_NORMAL	    //AFX_THREADPROC

//	oldmessagelines=Save_Data.messagelines;
//	currmessagelines=Save_Data.messagelines;
//	msgtimer =0;												//RDH 24Oct96
//	viewmsgtimer =0;

	SHAPESTUFF.LoadRequiredShapes();									//RJS 6Oct00

	OverLay.PreLoadImageMaps();											//RJS 25Sep00
  	Image_Map.LoadImageMapPtrs();								//PD 29Nov95
	doneframe=TRUE;

	SHAPE.SwitchToPilot(true);

	if (Persons2::PlayerSeenAC&&Persons2::PlayerSeenAC->classtype->aerobaticfactor==AEROBATIC_LOW)
	{
		_Analogue.noGunner = false;								//RJS 29Aug00
		SHAPE.SwitchToRearGunner(Persons2::PlayerSeenAC);
	}
	else
		_Analogue.noGunner = true;								//RJS 29Aug00
}
///////////////////////////////////////////////////////////////////////
View3d::~View3d()
{
	SHAPE.SwitchToPilot();												//RJS 2Aug00

	_Miles.DisableAll();

	Interactive(false);
	//free thread

//DEADCODE RDH 26/04/00 	_Analogue.Initialise((int)Master_3d.winst,(int)Master_3d.hinst,false,false);

	if (drawing!=D_NO)
	{
		WaitEndDraw(D_CLOSE);
	}
	if (mode!=WinMode::NONE)
	{	//screen is allocated - free resources
	}
	View3d**	sptr=&inst->viewedwin;
	while (*sptr!=this)
		sptr=&sptr[0]->nextview;
	*sptr=nextview;


//	if (View_Point)
//		View_Point->deathview = FALSE;								//RJS 01Nov96
//	ScreenRez	srez;
//	srez.width = 640;
//	srez.colourdepth = 8;
//	srez.driver =-1;
//
//	if (	(Save_Data.screenresolution != srez.width
//		&&	Save_Data.screenresolution != -srez.width)
//		||	Save_Data.colourdepth != srez.colourdepth
//		||	Save_Data.dddriver != srez.driver)
//		{
//			Whole_Screen->ChangeRes(srez);
//			LandStream.RezChanged(srez);						//PD 06Jun97
//		}
//
	MakeResize(WinMode::NONE);

	Master_3d.g_lpLib3d->FreeLandscapeTextures();
	Master_3d.g_lpLib3d->RestoreDisplayMode();
	_Miles.InitUI((int)window);									//DAW 06Apr99

	Three_Dee.FreeLandscapeTextures();							//RJS 31Jul00
	Three_Dee.DeleteFor2D();									//RJS 08Sep00

	Squad_Diary.Enter3D(NULL);
}
void	View3d::CloseWindow(const ULong id)
{
	if (mfcwin)
//		mfcwin->PostMessage(WM_COMMAND,IDOK,NULL);
		mfcwin->PostMessage(WM_COMMAND,id,NULL);
}
///////////////////////////////////////////////////////////////////////
int	View3d::MakeInteractive(WinMode	v,const CRect& pos,bool flag,bool flag2)
{

	ASSERT(mode==WinMode::NONE);
	if (!MakePassive(v,pos,flag,flag2))
		return (0);
	Interactive(true);
	return 1;
}
///////////////////////////////////////////////////////////////////////
int	View3d::MakePassive(WinMode	v,const CRect& pos,bool flag,bool flag2)
{
	ASSERT(mode==WinMode::NONE);
	Interactive(false);
	if (&pos)
		coords=pos;
	else
	{

	}
	HDC	dcTmp = GetDC(window);
	SetSystemPaletteUse(dcTmp,SYSPAL_NOSTATIC);		 //SYSPAL_ERROR
	ReleaseDC(window,dcTmp);

	//make sure loaderart is cached
//DeadCode RJS 16Aug00 	fileblockptr fbp=new fileblock(FIL_LOADERART);
//DeadCode RJS 16Aug00 	delete fbp;

	//handle resolution change
//	delete _DirectDraw::lpDirectDD;
//	_DirectDraw::lpDirectDD=new DirectDD;

//DEADCODE PD 03/12/99 	Whole_Screen=new Display(this);
//	Whole_Screen->DD.hWnd = window;
//	Whole_Screen->DD.hWndApp = Master_3d.winst;
	int rv;

	if (gameSettings.m_bFullScreenMode)
		rv=Master_3d.g_lpLib3d->SetDriverAndMode(Save_Data.hDriver,Save_Data.hMode,NULL);
	else
		rv=Master_3d.g_lpLib3d->SetDriverAndMode(Save_Data.hDriver,Save_Data.hMode,window);
	if (rv)
		_Error.ReallyEmitSysErr("Failed to set up Direct 3D");

	// set the master lightshading
	LIGHTFLAG lf = LIGHTFLAG( LF_AMBIENT+Save_Data.itemShading );
	Master_3d.g_lpLib3d->SetMasterShading( lf );

	// set the master texture quality options
	switch( Save_Data.textureQuality )
	{
		case 0: // minimum
			Master_3d.g_lpLib3d->GiveHint( 	HINT_EIGHTH_RES_TEXTURE );
			break;
		case 1: // low
			Master_3d.g_lpLib3d->GiveHint( 	HINT_QUARTER_RES_TEXTURE );
			break;
		case 2: // medium
			Master_3d.g_lpLib3d->GiveHint( 	HINT_HALF_RES_TEXTURE );
			break;
		case 3: // high
		case 4: // maximum - also gives hi rez city tops
			Master_3d.g_lpLib3d->GiveHint( 	HINT_FULL_RES_TEXTURE );
			break;
		NODEFAULT;
	}

	// set the master texture blending options
	switch( Save_Data.filtering )
	{
		case 0: // none
			Master_3d.g_lpLib3d->GiveHint( 	HINT_NOBLEND );
			break;
		case 1:	// bi-linear
			Master_3d.g_lpLib3d->GiveHint( 	HINT_BILINEAR );
			break;
		case 2:	// tri-linear
		case 3: // all (tri-linear+dithering)
			Master_3d.g_lpLib3d->GiveHint( 	HINT_TRILINEAR );
			break;
		NODEFAULT;
	}
	
	Master_3d.g_lpLib3d->AllocateLandscapeTextures();
	_Miles.SetDirectSoundWindow((ULong)Master_3d.winst);

	// now set the gamma
	Master_3d.g_lpLib3d->SetGammaLevel( Save_Data.gammacorrection );

//	Whole_Screen->InitDirectDraw ();
//	Whole_Screen->Init(v,coords.left,coords.top,coords.right,coords.bottom);
	
	View_Point=new ViewPoint(Master_3d.g_lpLib3d,this);

	Squad_Diary.Enter3D(View_Point);							//RJS 29Feb00

	OverLay.SetScreen(Master_3d.g_lpLib3d);
	OverLay.SetViewpoint(View_Point);
	OverLay.LoaderScreen(0);									//PD 02Mar99
	_Miles.Init3D();											//RJS 06Apr99
	_Miles.SetDirectSoundWindow((ULong)Master_3d.winst);
//	_Miles.SetVolumes(TRUE);									//RJS 12Mar99
	OverLay.LoaderScreen(0+32);									//PD 02Mar99
//DEADCODE DAW 13/04/99 	_Miles.SetVolumes(TRUE);
	if (!flag)
	{
		_Miles.SetVolumes(TRUE);								//RJS 13Apr99
		View_Point->SetToPiloted(Manual_Pilot.ControlledAC2);
		View_Point->SetReplayView(_Replay.Playback);//RJS 20Oct98
	}
	else View_Point->SetToMapItem(NULL);
	OverLay.LoaderScreen(0+48);									//PD 02Mar99
	Trans_Obj.View_Point=View_Point;
	Trans_Obj.View_Object=View_Point;							//RJS 21Apr98
	Land_Scape.View_Point=View_Point;
	Art_Int.View_Point=View_Point;
//DEADCODE PD 03/12/99 	Land_Scape.currscreen=Whole_Screen;
	OverLay.LoaderScreen(0+64);									//PD 02Mar99
	Three_Dee.Init3D(Master_3d.g_lpLib3d,View_Point);					//RJS 19Nov98
	if (flag2) 
		Land_Scape.RefreshLandscape();
	Three_Dee.ResetPalette();									//RJS 24Oct96
	doneframe=TRUE;		//forces frametime to zero
	Drawing(true);
	mode=v;
	if (_DPlay.Implemented)										//DAW 22Jun99
	{															//DAW 22Jun99
		_DPlay.csync=true;										//DAW 22Jun99
	}															//DAW 22Jun99
	WaitEndDraw(D_YES);
	WaitEndDraw(D_YES);
	if (_DPlay.Implemented)										//DAW 22Jun99
	{															//DAW 22Jun99
		_DPlay.csync=false;										//DAW 22Jun99
	}															//DAW 22Jun99
	_Replay.skipOK=true;
	return 1;
}
///////////////////////////////////////////////////////////////////////
int	View3d::MakeResize(WinMode	v,const CRect& pos)
{
	if ((&pos && pos!=coords) || v!=mode)
	{
		//delete old surface...
		if (&pos)
			coords=pos;

		//some legality check before we start screwing things up 10 ways

		if (v!=mode)
		{	//delete windowing object
			v=WinMode::NONE;
			//WaitEndDraw(D_CLOSE);
			drawing=D_CLOSE;
//DEAD			POLYGON.DeleteYList();
//CRASHED CRAIGS M/C
//DEADCODE PD 03/12/99 				delete Whole_Screen;
//DEADCODE PD 03/12/99 				Whole_Screen=NULL;
			Trans_Obj.View_Point=Manual_Pilot.ControlledAC2;
			delete View_Point;
			View_Point=NULL;
			HDC	dcTmp = GetDC(window);
			SetSystemPaletteUse(dcTmp,SYSPAL_STATIC);
			ReleaseDC(window,dcTmp);
		}
		//make or convert to new diasplay 


		v=mode;
	}
	//else no change

	return 1;
}	 
//////////////////////////////////////////////////////////////////////
//
// Function:    WhatAliasModes
// Date:		04/09/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	Analogue::WhatAliasModes(AllowAliasing& aliassingUI,AllowAliasing& aliassing,ViewPoint* newwin)
{
	aliassing=AA_NONE,aliassingUI=AA_NONE;
	bool aliasinginuse=false;

	if (Manual_Pilot.ControlledAC2)										//RJS 6Sep00
	{
		if (Manual_Pilot.ControlledAC2->classtype->planetext>PT_JU87)
		{	//only if on inside view
			aliasinginuse=_Analogue.tune[AU_VIEWH].aliased[AA_GUNNER_JOYVIEW];	 //if true then need to reinitialise whenever switch inside / outside view.
			if (newwin->InCockpit())
			{
				aliassing=AA_GUNNER_JOYVIEW;
			}
		}
		else
			if (Manual_Pilot.ControlledAC2->classtype->planetext==PT_ME110)
				aliassing=AA_THROTTLE2_PROP1;
	}
	 
	if (OverLay.pNewScr)
	{
		aliassingUI=AA_UI_PAN;
	}
	else
 	if (Key_Tests.mshift)
	{
		aliassingUI=AA_UI_PAN;
	}
	if (aliassingUI!=currUIaliasingmode)
		return	aliasinginuse ||	_Analogue.tune[AU_VIEWH].aliased[AA_UI_PAN];
	else
	if (aliassing!=curraliasingmode)
		return	aliasinginuse;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////
View3d* Inst3d::Interactive(View3d* newwin)
{
	TRACE("Interactive entry\n");
	View3d* rv=interactive?viewedwin:NULL;
	interactive=(newwin!=NULL);
	if (newwin)	
	{
		View3d** vw=&viewedwin;
		while (*vw!=newwin)
			vw=&vw[0]->nextview;
		*vw=newwin->nextview;				//unhooks newwin
		newwin->nextview=viewedwin;
		viewedwin=newwin;				//reinserts at front
	}
	if (newwin!=rv)
		if (newwin)
		{
			Key_Tests.mshift=false;
//DeadCode JIM 2Nov00 			Key_Tests.jshift=false;

//DeadCode JIM 8Sep00 			_Analogue.BackupAllDeviceAxes();

//DeadCode AMM 27Jul00 			if (Persons2::PlayerSeenAC&&Persons2::PlayerSeenAC->classtype->aerobaticfactor==AEROBATIC_LOW)
//DeadCode AMM 27Jul00 			{
//DeadCode AMM 27Jul00 				if (_Analogue.IsTaskShiftedMouse(AU_GUNP))
//DeadCode AMM 27Jul00 					Key_Tests.SetMouseShiftMode(SHIFTED);
//DeadCode AMM 27Jul00 
//DeadCode AMM 27Jul00 				if (_Analogue.IsTaskShiftedJoystick(AU_GUNP))
//DeadCode AMM 27Jul00 					Key_Tests.SetJoystickShiftMode(SHIFTED);
//DeadCode AMM 27Jul00 			}

//DeadCode AMM 27Jul00 // mouse in replay playback is AU_UI_X, AU_UI_Y, which are locked to cockpit,
//DeadCode AMM 27Jul00 // so lock to shifteed mode for cockpit?
//DeadCode AMM 27Jul00 
//DeadCode AMM 27Jul00 			if (_Replay.Playback)
//DeadCode AMM 27Jul00 			{
//DeadCode AMM 27Jul00 				Key_Tests.SetMouseShiftMode(SHIFTED);
//DeadCode AMM 27Jul00 			}
			AllowAliasing	aliassingUI,aliassing;
			_Analogue.WhatAliasModes(aliassingUI,aliassing,newwin->View_Point);

			_Analogue.Initialise((int)Master_3d.winst,(int)Master_3d.hinst,aliassingUI,aliassing);

			TRACE("Interactive setup success1\n");
			if (Master_3d.g_lpDI)
			if (!Master_3d.g_lpDIDevice)
			{
//			TRACE("Interactive setup success2\n");
				if (!FAILED(Master_3d.g_lpDI->CreateDevice(GUID_SysKeyboard, &Master_3d.g_lpDIDevice, NULL)))
				{
//			TRACE("Interactive setup success3\n");

					if (!FAILED(Master_3d.g_lpDIDevice->SetDataFormat(&c_dfDIKeyboard)))
						if (!FAILED(Master_3d.g_lpDIDevice->SetCooperativeLevel(Master_3d.winst,DISCL_BACKGROUND | DISCL_NONEXCLUSIVE)))
						{	//E_INVALIDARG	//DIERR_NOTINITIALIZED
//			TRACE("Interactive setup success4\n");
							DIPROPDWORD	buffsize={{sizeof(DIPROPDWORD),sizeof(DIPROPHEADER),0,DIPH_DEVICE},BUFFERED_KEYS};
							DIDEVCAPS DIDevCaps={sizeof(DIDEVCAPS)};
							Master_3d.g_lpDIDevice->GetCapabilities(&DIDevCaps); 
							//DIDC_ATTACHED   DIERR_INVALIDPARAM 
							Master_3d.g_lpDIDevice->SetProperty(DIPROP_BUFFERSIZE,&buffsize.diph);
							if (!FAILED(Master_3d.g_lpDIDevice->SetEventNotification(Master_3d.htable[Master_3d.EVENT_KEYS])))
							{

//			TRACE("Interactive setup success5\n");


								if (!FAILED(Master_3d.g_lpDIDevice->Acquire()))
								{
									TRACE("Interactive setup success\n");
//									*(char*)0xb0000='1';
									return	rv;
								}
							}
						}
					Master_3d.g_lpDIDevice->Release();
					Master_3d.g_lpDIDevice=NULL;
				}
				TRACE("Interactive setup fail\n");
				_Error.EmitSysErr("Couldn't access keyboard with directinput?");
				//syserr??
			}
		}
		else
		{
			_Analogue.CloseDown();
			if (Master_3d.g_lpDIDevice)
			{
//				TRACE("Interactive removal\n");

				Master_3d.g_lpDIDevice->Unacquire();
				Master_3d.g_lpDIDevice->SetEventNotification(NULL);
				Master_3d.g_lpDIDevice->Release();
				Master_3d.g_lpDIDevice=NULL;
//				*(char*)0xb0000='0';
									
//				TRACE("Interactive removal exit\n");
			}
		}	 
	return rv;
}
///////////////////////////////////////////////////////////////////////
bool Inst3d::Paused(bool newmode)
{
	bool rv=paused;
	paused=newmode;
	if (newmode!=rv)
	{
		_Analogue.ZeroForces();
		if (newmode)
		{
			_Miles.StopAll();				//RJS 07Jun99
			_Miles.SequenceMute(500);		//RJS 07Jun99
			_Miles.SetEngine();				//RJS 07Jun99
			accel=false;
		}
		else
		{
		}
	}
	return rv;
}
///////////////////////////////////////////////////////////////////////
bool Inst3d::Accel(bool newmode)
{
	bool rv=accel;
	accel=newmode;
	if (newmode!=rv)
		if (newmode)
		{
			if (_Replay.Record)									//AMM 26May99
			{													//AMM 26May99
				if (Save_Data.gamedifficulty[GD_GUNCAMERAONTRIGGER]
				&& !Save_Data.gamedifficulty[GD_GUNCAMERAATSTART])
				{
					_Replay.guncameradelay=0;
					_Replay.stopforaccel=false;
				}
				else
				{
					_Replay.stopforaccel=true;						//AMM 26May99
				}
				_Replay.StopRecord(true);							//AMM 26May99
			}													//AMM 26May99

			_Miles.StopAll();				//RJS 11May99
			_Miles.SequenceMute(500);		//RJS 11May99
			_Miles.SetEngine();									//RJS 01Jun99
			paused=false;
		}
		else
		{
			_Radio.ClearMessages(MSG_TAKEOFFROLLING);			//RJS 14Jun99
			_Radio.ClearMessages(PRI_LOW);						//RJS 03Jun99
			mobileitem::ResetACGears();							//RJS 01Jun99

			if (_Replay.stopforaccel)							//AMM 26May99
			{													//AMM 26May99
				_Replay.stopforaccel=false;						//AMM 26May99
				if (Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)
				{
					_Replay.StartRecordFlag=TRUE;					//AMM 26May99
				}
				_Replay.DelayedGearUp=true;
			}													//AMM 26May99
		}

	Persons2::PlayerSeenAC->fly.pModel->Blood = 1;
	return rv;
}
///////////////////////////////////////////////////////////////////////
View3d* Inst3d::Interactive()
{
	return interactive?viewedwin:NULL;
}
///////////////////////////////////////////////////////////////////////
bool Inst3d::Paused()
{
	if (this==NULL)
		return	false;
	return paused;
}
///////////////////////////////////////////////////////////////////////
bool Inst3d::Accel()
{
	return accel;
}
///////////////////////////////////////////////////////////////////////
bool	View3d::Drawing(bool newval)
{
	bool rv=(drawing==D_YES);
	if (drawing<=D_YES)
	{
		drawing=newval?D_YES:D_NO;
		if (newval)
		{
		}
		else
		{
		}
	}
	return rv;
}
///////////////////////////////////////////////////////////////////////
void Inst3d::OnKeyInput()
{
	if (!Master_3d.g_lpDIDevice)
		return;
	DIDEVICEOBJECTDATA	keys[BUFFERED_KEYS];
	DWORD	dwItems=BUFFERED_KEYS;
//DeadCode JON 22Oct00 	int		rv= 
		IDirectInputDevice_GetDeviceData( 
			Master_3d.g_lpDIDevice,sizeof(DIDEVICEOBJECTDATA), 
			keys,&dwItems,0); 
	for(DIDEVICEOBJECTDATA*	key=keys;dwItems;dwItems--,key++)
	{
		int keynum=key->dwOfs;
		char keyval=key->dwData;
		if (keyval<0)
			OnKeyDown(keynum);
		else
			OnKeyUp(keynum);
	}						   
}
void	Inst3d::OnKeyDown(int keynum)
{
	int	index=commonkeymaps->mappings[keynum][commonkeymaps->currshifts];
	if (index)
	{
		if (index<16)
		{	//it's a shift key!
			commonkeymaps->currshifts=index>>1;
		}
		else if (index<32)
		{
//DeadCode AMM 27Jul00 // its a shift lock
//DeadCode AMM 27Jul00 			if (index==KeySrc_BN_MsgLock)
//DeadCode AMM 27Jul00 			{
//DeadCode AMM 27Jul00 // MsgLock mode
//DeadCode AMM 27Jul00 				if (commonkeymaps->currshifts==KEYSH_BN_Msg)
//DeadCode AMM 27Jul00 				{
//DeadCode AMM 27Jul00 					commonkeymaps->currshifts=0;
//DeadCode AMM 27Jul00 
//DeadCode AMM 27Jul00 // clear chat entry box
//DeadCode AMM 27Jul00 					OverLay.pNewScr=OverLay.pCurScr=NULL;
//DeadCode AMM 27Jul00 				}
//DeadCode AMM 27Jul00 				else
//DeadCode AMM 27Jul00 				{
//DeadCode AMM 27Jul00 					commonkeymaps->currshifts=KEYSH_BN_Msg;
//DeadCode AMM 27Jul00 
//DeadCode AMM 27Jul00 // since we have gone into chat mode, display chat entry box
//DeadCode AMM 27Jul00 					OverLay.SetToCommsChatScr();
//DeadCode AMM 27Jul00 				}
//DeadCode AMM 27Jul00 			}
//DeadCode AMM 27Jul00 			else if (index==KeySrc_BN_ShMsgLock)
//DeadCode AMM 27Jul00 			{
//DeadCode AMM 27Jul00 // ShMsgLock mode
//DeadCode AMM 27Jul00 				commonkeymaps->currshifts=KEYSH_BN_ShMsg;
//DeadCode AMM 27Jul00 			}
//DeadCode AMM 27Jul00 			else
//DeadCode AMM 27Jul00 			{
//DeadCode AMM 27Jul00 				commonkeymaps->currshifts=(index>>1)-8;
//DeadCode AMM 27Jul00 			}
		}
		else
		{
			if (!BITSET(commonkeymaps->bitflags,index+1))
				BITSET(commonkeymaps->bitflags,index);
		}
	}
}
void	Inst3d::OnKeyUp(int keynum)
{	//release	
	UWord*	indtable=commonkeymaps->mappings[keynum];
	for (int ent=8;ent;ent--)
	{
		int index=*indtable++;
		if (index)
		{
			if (index<16)
			{	//it's a shift key!

				if (commonkeymaps->currshifts==(index>>1))
					commonkeymaps->currshifts=0;
			}
			else if (index<32)
			{
// its a shift lock - MsgLock dealt with separately

//DeadCode AMM 27Jul00 				if(index!=KeySrc_BN_MsgLock)
//DeadCode AMM 27Jul00 				{
//DeadCode AMM 27Jul00 					if (index==KeySrc_BN_ShMsgLock && commonkeymaps->currshifts==KEYSH_BN_ShMsg)
//DeadCode AMM 27Jul00 					{
//DeadCode AMM 27Jul00 						commonkeymaps->currshifts=KEYSH_BN_Msg;
//DeadCode AMM 27Jul00 					}
//DeadCode AMM 27Jul00 					else
//DeadCode AMM 27Jul00 					{
//DeadCode AMM 27Jul00 						commonkeymaps->currshifts=0;	
//DeadCode AMM 27Jul00 					}
//DeadCode AMM 27Jul00 				}
			}
			else
			{
				BITRESET(commonkeymaps->bitflags,index);
			}
		}
	}
}
//DEADCODE MS 14/04/00 bool	StopMeNow=false;
UINT AFX_CDECL View3d::drawloop(LPVOID THISTHIS)
{	//can get hwnd etcetera no problem!
	View3d* This=(View3d*) THISTHIS;
	forever
	{
		if (This->drawing==D_YES)
		{
			//actual draw code here!
//			while (++(((char*)0xb0000)[160*10])&7)
//				for (((char*)0xb0000)[160*10+2]=0;++(((char*)0xb0000)[160*10+2]);)
//					for (((char*)0xb0000)[160*10+4]=0;++(((char*)0xb0000)[160*10+4]);)
//					{}

			if (This->mode!=WinMode::NONE)
#pragma warnmsg("**** DRAW TIME MONOTEXT REMOVED **** //CSB")
//DeadCode CSB 29Jun00 			if (ProbeTime a24(24,"Draw"))
			{
//DEADCODE MS 14/04/00 				StopMeNow=true;
//				Window	window3d(*This->Whole_Screen,WINSH_MID,WINSH_MID);

//DeadCode RJS 27Aug98 				_Miles.SetVP(This->View_Point);					//RJS 26Feb98
//Dead 				_Miles.ProcessSpot(This->View_Point);			//RJS 25May99
//Dead				_Radio.ProcessMessages(This->View_Point->FrameTime());			//RJS 01Apr99
 
//DeadCode AMM 8Sep00 				static UWord doit=0;							//AMM 07Jul99
//DeadCode AMM 8Sep00 				static UWord stage=0;							//AMM 07Jul99

				if (!_DPlay.Implemented || _DPlay.csync)		//DAW 22Jun99
					Three_Dee.render(Master_3d.g_lpLib3d,This->View_Point,This->inst->world);
//DeadCode AMM 8Sep00 				else if (doit&0x1000)							//AMM 08Jul99
//DeadCode AMM 8Sep00 				{												//AMM 07Jul99
//DeadCode AMM 8Sep00 					UByte num=256/_DPlay.CurrPlayers;
//DeadCode AMM 8Sep00 					num*=_DPlay.NumPlayersSynched;
//DeadCode AMM 8Sep00 
				else
				{
					if (_DPlay.resyncbar)
					{
						static UByte num=0;
						OverLay.CommsWaitingScreen(num++);		//AMM 07Jul99
					}
				}
//DeadCode AMM 8Sep00 				}												//AMM 07Jul99
//DeadCode AMM 8Sep00 				doit++;											//AMM 07Jul99
//DeadCode RJS 2Nov00 				This->BlockTick(TRUE);
//DeadCode RJS 2Nov00 				//Transients must always go last...
//DeadCode RJS 2Nov00 				if (!_DPlay.Implemented || _DPlay.csync)		//DAW 22Jun99
//DeadCode RJS 2Nov00 				{												//DAW 22Jun99
//DeadCode RJS 2Nov00 					SHAPE.GenerateProbeTrails();								//RJS 08Apr99
//DeadCode RJS 2Nov00 					SHAPE.KillVapourStreamDeadList();							//RJS 08Apr99
//DeadCode RJS 2Nov00 					Trans_Obj.RemoveDeadListFromWorld(This->inst->world);
//DeadCode RJS 2Nov00 
//DeadCode RJS 2Nov00 					if (_Replay.Playback && _Replay.processsmokes)
//DeadCode RJS 2Nov00 						_Replay.UpdateSmokeInfo();
//DeadCode RJS 2Nov00 				}												//DAW 22Jun99
//DeadCode RJS 2Nov00 				else
//DeadCode RJS 2Nov00 				{
//DeadCode RJS 2Nov00 					if (_DPlay.Implemented && !_DPlay.csync)
//DeadCode RJS 2Nov00 					{
//DeadCode RJS 2Nov00 						if (_DPlay.CommsGameSync())
//DeadCode RJS 2Nov00 							This->Paused(FALSE);
//DeadCode RJS 2Nov00 					}
//DeadCode RJS 2Nov00 				}
//DeadCode RJS 2Nov00 
//DeadCode RJS 2Nov00 				This->BlockTick(FALSE);

				OverLay.screenshot.VideoShot(Master_3d.g_lpLib3d);
				if (Key_Tests.KeyPress3d(SCREENSHOT))
				{
					if (!OverLay.screenshot.framebuffer)
						OverLay.screenshot.SaveScreenShot(Master_3d.g_lpLib3d);
					else
						OverLay.screenshot.SaveVideoStream(Master_3d.g_lpLib3d);
				}
// to stop screen strobe in comms sync phase!
				if (!_DPlay.Implemented || _DPlay.csync)		//AMM 09Jun99
				{
					Master_3d.g_lpLib3d->ScreenSwap();
					Three_Dee.RenderMirror();
				}

// Killing objects, or transients MUST come after the mirror render...
				This->BlockTick(TRUE);
				//Transients must always go last...
				if (!_DPlay.Implemented || _DPlay.csync)		//DAW 22Jun99
				{												//DAW 22Jun99
					SHAPE.GenerateProbeTrails();								//RJS 08Apr99
					SHAPE.KillVapourStreamDeadList();							//RJS 08Apr99
					Trans_Obj.RemoveDeadListFromWorld(This->inst->world);

					if (_Replay.Playback && _Replay.processsmokes)
						_Replay.UpdateSmokeInfo();
				}												//DAW 22Jun99
				else
				{
					if (_DPlay.Implemented && !_DPlay.csync)
					{
						if (_DPlay.CommsGameSync())
							This->Paused(FALSE);
					}
				}

				This->BlockTick(FALSE);
			}
		}
		if (This->E)
			This->E->SetEvent();
		if (This->drawing==D_CLOSE)
			return 0;
		This->DoneFrame();

		if (Manual_Pilot.ControlledAC2!=NULL && !_Replay.Playback && Key_Tests.KeyPress3d(EXITKEY))
			_DPlay.SimulateExitKey=TRUE;


		if ((Manual_Pilot.ControlledAC2==NULL || !Manual_Pilot.ControlledAC2->Status.deadtime)
			&& !This->Accel() && OverLay.pCurScr==NULL && Key_Tests.KeyPress3d(KEY_CONFIGMENU))
		{
			if (!(_DPlay.Implemented || _Replay.Playback))		//AMM 14Apr99
			{													//AMM 14Apr99
				_Replay.prefscheck=true;
//DeadCode JIM 8Sep00 				_Analogue.SetAllAxesFromBackup();						//AMM 27Jul00

				This->inst->Paused(TRUE); //AMM 21/05/99
				This->MakeResize(WinMode::NONE);
				This->CloseWindow(IDCANCEL);
			}													//AMM 14Apr99
		}
		else if (_DPlay.SimulateExitKey)
		{
//DeadCode RJS 11Oct00 			OverLay.quit3d=0;
			if (_DPlay.Implemented && _DPlay.hitResurrect)				//RJS 11Oct00
			{
				if (_DPlay.GameType<DPlay::COMMSQUICKMISSION)
				{
					if (Persons2::PlayerSeenAC->movecode!=AUTO_NOPPILOT
						&& Persons2::PlayerSeenAC->movecode!=AUTO_RESURRECT)
					{
						Persons2::PlayerSeenAC->movecode=AUTO_NOPPILOT;
					}
				}
				This->View_Point->UnQuit3D();
			}
			else
			{
				_DPlay.hitResurrect = false;							//RJS 11Oct00
				{
					This->inst->Paused(TRUE); //AMM 21/05/99
					_DPlay.ExitCommsAndReplay3D();						//AMM 11Dec98

	//DeadCode JIM 8Sep00 				_Analogue.SetAllAxesFromBackup();
				}

				This->MakeResize(WinMode::NONE);
				This->CloseWindow();
			}
		}
	}
	return 0;
}

void	View3d::SetEndDraw(DrawState d)
{
	if (drawing==D_YES)
		if (!E)
			E=new CEvent();
	drawing=d;	
}
int	View3d::WaitEndDraw(DrawState d,int timeoutmilisec)
{
	if (drawing==D_YES)
		if (!E)
			E=new CEvent();
	drawing=d;	
	if (E)
		if (!E->Lock(timeoutmilisec))
			return false;
	CEvent* t=E;
	E=NULL;
	delete t;
	return true;
}

//DeadCode AMM 24Aug00 void	Mast3d::QuitGame(void )
//DeadCode AMM 24Aug00 {
//TEMP	_DPlay.ExitDirectPlay();
//TEMP
//TEMP	if (_Main.DDrawInitialised==TRUE)
//TEMP	{
//TEMP		_Main.DDrawInitialised=FALSE;
//TEMP
//TEMP		Whole_Screen->ExitDirectDraw ();	// put in Display::Exit
//TEMP
//TEMP		Whole_Screen->SetTextMode();
//TEMP	}
//TEMP
//TEMP	delete	Whole_Screen;
//TEMP
//TEMP	Whole_Screen=NULL;
//TEMP
//TEMP	if (debugfile!=NULL) fclose (debugfile);
//TEMP
//DeadCode AMM 24Aug00 }

static int	howcamehere;
void CALLBACK Mast3d::StaticTimeProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2 )
{

#ifdef DO_TIMER_DIAGS
	QueryPerformanceCounter(&timerBufferIn[timerBufferI]);
#endif

//DEADCODE JIM 21/06/00 	Mono_Text.Print(UByteP("t"));
//DeadCode JIM 20Oct00 	ULong t=0;
	if (_DPlay.Implemented)
	{
		if (_DPlay.Host && _DPlay.GameRunning)
		{
			if (!_DPlay.ResyncPhase)
			{
				_Agg.AggregatorGetPackets();
			}
		}

 // whilst player is entering 3d cannot rely on any piece of code to process
 // packets so process any here. This is needed so that players can enter game 
 // whilst host is entering 3d
 
 		if (_DPlay.firsttimein && _DPlay.Host)
 		{
 			_DPlay.ProcessPlayerMessages();
 		}
	}

	insidetimer = TRUE;
	if (!_DPlay.Implemented || (_DPlay.Implemented && _DPlay.csync))
		((Mast3d*)dwUser)->TimeProc(uID,uMsg,dw1,dw2);
	insidetimer = FALSE;

#ifdef DO_TIMER_DIAGS
	QueryPerformanceCounter(&timerBufferOut[timerBufferI++]);
	timerBufferI%=gameSettings.m_dwTimerBufferSize;
#endif

}

void Mast3d::TimeProc(UINT uID, UINT uMsg, DWORD dw1, DWORD dw2 )
{
#ifdef COMMSTIMERDEBUG
	static ULong ltim=0;
	LARGE_INTEGER count;
	ULong freq;

	if(_DPlay.Implemented && _DPlay.csync)
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)(&freq));
		QueryPerformanceCounter(&count);

		ULong smlcount=count.LowPart;
		ULong Rtime=((smlcount-ltim)*1000)/freq;

		FILE* fp=fopen("toptim.txt","at");
		fprintf(fp,"%d %d\n",_DPlay.FrameCount,Rtime);
		fclose(fp);

		ltim=smlcount;
	}
#endif
//#pragma message("Stub3D.cpp - don't forget to take this out")	//RJS 25Nov98
//	if (currinst && currinst->blocktick) return;				//RJS 25Nov98
//	if (currinst &&												//RJS 25Nov98
//		currinst->viewedwin && 									//RJS 25Nov98
//		!currinst->viewedwin->doneframe &&						//RJS 25Nov98
//		currinst->viewedwin->frametime>10) return;				//RJS 25Nov98
	ticknum++;
	for (Inst3d* inst=currinst;inst;inst=inst->nextinst)
	{
		if (inst->blocktick)
		{
			if (currinst && currinst->viewedwin && !inst->paused)
//DEADCODE AMM 24/11/99 				currinst->viewedwin->timeSinceLastMove+=2;
				currinst->viewedwin->timeSinceLastMove+=Timer_Code.FRAMETIME; //AMM 24/11/99

			int bt=1;
			bt+=LockExchange(&inst->blockticks);
			bt=LockExchange(&inst->blockticks,bt);
			while (bt)
			{
				bt+=LockExchange(&inst->blockticks);
				bt=LockExchange(&inst->blockticks,bt);
			}
		}	
		else
		{
			if (currinst && currinst->viewedwin)
				currinst->viewedwin->timeSinceLastMove=0;
			howcamehere=0xf00;
			inst->DoMoveCycle();
		}
	}
} 

WINBASEAPI
BOOL
WINAPI
QueryPerformanceCounter(
    LARGE_INTEGER *lpPerformanceCount
    );

WINBASEAPI
BOOL
WINAPI
QueryPerformanceFrequency(
    LARGE_INTEGER *lpFrequency
    );

void	Inst3d::DoMoveCycle()
{
#ifdef	_FRAMESHITE_
	fprintf(Three_Dee.framefp,"-\n");
#endif
	bool	timeout=false;
//DEADCODE RDH 12/07/99 	ULong num=1;
	OverLay.accelcountdown=1;
	for (View3d* view=viewedwin;view;view=view->nextview)
	{
		_Miles.SetListener(view->View_Point);						//RJS 12Jan00

		if (view->doneframe)
		{
//DeadCode RJS 9Aug00 			if (view->View_Point)								//RJS 12Jan00
//DeadCode RJS 9Aug00 			{
//DeadCode RJS 9Aug00 				_Miles.ProcessSpot(view->View_Point);				//RJS 12Jan00
//DeadCode RJS 9Aug00 				_Radio.ProcessMessages(view->View_Point->FrameTime());//RJS 12Jan00
//DeadCode RJS 9Aug00 			}

			if (!Paused())												//RJS 9Aug00
			{
				if (view->View_Point)								//RJS 12Jan00
				{
					_Miles.ProcessSpot(view->View_Point);				//RJS 12Jan00
					_Radio.ProcessMessages(view->View_Point->FrameTime());//RJS 12Jan00
				}

				view->lastframetime=view->frametime;
			}
			else
				view->lastframetime=0;
			view->lastrealframetime=view->frametime;
			view->frametime=0;
			view->realframetime=0;
			view->doneframe=FALSE;
			if (Accel())
				if (accelframes>0)
					if (view->lastrealframetime<MAX_ACCEL_FRAME)
					{
						accelframes++;
						if (	accelframes>10 
							&& (OverLay.keyFlags&KF_ACCELFRAMESMASK)!=KF_SLOWACCEL
							&& (OverLay.keyFlags&KF_ACCELFRAMESMASK)<KF_BESTACCEL)
						{
							accelframes=0;
							OverLay.keyFlags++;
						}
					}
					else
						accelframes=0;
				else
					if (view->lastrealframetime>=MAX_ACCEL_FRAME)
					{
						accelframes--;
						if (accelframes<-10 && (OverLay.keyFlags&KF_ACCELFRAMESMASK)>KF_SLOWACCEL+1)
						{
							accelframes=0;
							OverLay.keyFlags--;
						}
					}
					else
						accelframes=1;

			_Miles.Commit();											//RJS 15Sep00
		}

		UWord framemax=Accel()?MAX_ACCEL_FRAME:MAX_NORMAL_FRAME;

// for comms we want a higher number, because throwing away frames means that
// a machine will begin to lag behind other machines.

		if (_DPlay.Implemented)
			framemax=5000;

		if (view->frametime<framemax)		//max buffer up of 2 seconds of action.
		{								//reduce this to 20 for profiling @ 5 fps
			view->frametime+=Timer_Code.FRAMETIME; //AMM 24/11/99

			//Pause key && accel key must not be pressed on any 3D UI screens!
			if (OverLay.pCurScr!=NULL) 						  //JIM 08/06/99
			{
				Key_Tests.KeyPress3d(PAUSEKEY);
				Key_Tests.KeyPress3d(ACCELKEY);
			}
			else
			{
				if (!Accel())
				{
				if (!Paused())
				{
					if (Key_Tests.KeyPress3d(PAUSEKEY)
						&& !_DPlay.Implemented)							//AMM 23Nov98
					{
						Paused(TRUE);
						OverLay.TriggerMessage(COverlay::PAUSEMESS);
						if (_Replay.Playback)
						{
							_Replay.PlaybackPaused=TRUE;
							OverLay.pCurScr=OverLay.pNewScr=&OverLay.replayScr;
						}
					}
				}
				else
				{
					_Analogue.PollPosition();
					if (Key_Tests.KeyPress3d(PAUSEKEY))
					{
						if (!_DPlay.Implemented)
						{
							Paused(FALSE);
							OverLay.TriggerMessage(COverlay::CLEARMESS);
							if (_Replay.Playback)
							{
								_Replay.PlaybackPaused=FALSE;
								OverLay.pCurScr=OverLay.pNewScr=&OverLay.replayPlayingScr;
							}
						}
					}
				}
				}
				if(		(!Paused()) && (Key_Tests.KeyPress3d(ACCELKEY))
					&&	(Persons2::PlayerSeenAC) && (Persons2::PlayerSeenAC->movecode == AUTO_FOLLOWWP)
					&&	(Persons2::PlayerSeenAC->fly.fuel_content[0] + Persons2::PlayerSeenAC->fly.fuel_content[1] + 
						 Persons2::PlayerSeenAC->fly.fuel_content[2] + Persons2::PlayerSeenAC->fly.fuel_content[3] > 0)	)
				{
					if (!_DPlay.Implemented)
					{
						if (!Accel())		
						{
							Accel(TRUE);
							OverLay.TriggerMessage(COverlay::ACCELMESS);
							Manual_Pilot.AutoToggle(ManualPilot::AUTOACCEL_WAYPT);
							UByte okey=(OverLay.keyFlags&~KF_ACCELFRAMESMASK)+KF_SLOWACCEL;
							OverLay.keyFlags=okey;
						}	
						else
						{
							Accel(FALSE);
							OverLay.TriggerMessage(COverlay::CLEARMESS);
							Manual_Pilot.AutoToggle(ManualPilot::MANUAL);
							OverLay.keyFlags&=~KF_ACCELFRAMESMASK;
						}
					}
				}
			}
			if (Key_Tests.KeyPress3d(RECORDTOGGLE))				//AMM 16Apr99
			{													//AMM 16Apr99
				_Replay.ToggleRecord();							//AMM 16Apr99
/*				if (_DPlay.LosePackets)
					_DPlay.LosePackets=0;
				else
					_DPlay.LosePackets=10;
*/
			}													//AMM 16Apr99
			if (Key_Tests.KeyPress3d(RESETRECORD))				//AMM 16Apr99
			{													//AMM 16Apr99
#ifndef NDBEUG
				if (_DPlay.SpookyGhostMode)
					_DPlay.SpookyGhostMode=false;
				else
					_DPlay.SpookyGhostMode=true;
#endif
//DeadCode AMM 12Jul00 				if (_DPlay.Implemented)
//DeadCode AMM 12Jul00 				{
//DeadCode AMM 12Jul00 					_DPlay.Initiator=TRUE;
//DeadCode AMM 12Jul00 					_DPlay.BeginSyncPhase();
//DeadCode AMM 12Jul00 				}

				_Replay.ResetRecord();							//AMM 16Apr99
			}													//AMM 16Apr99
			if (Key_Tests.KeyPress3d(MOUSEMODETOGGLE))
			{
				if (!SHAPE.UsingRearGunner())				//RJS 26Oct00
//DeadCode AMM 27Jul00 				if (Persons2::PlayerSeenAC->classtype->aerobaticfactor!=AEROBATIC_LOW)
				{
//DeadCode AMM 27Jul00 					if (Save_Data.flightdifficulty[FD_ENGINEMANAGMENT])
					{
						if (Key_Tests.mshift)
						{
		//DEADCODE AMM 14/02/00 					Key_Tests.mshift=false;
							Key_Tests.SetMouseShiftMode(NORMAL);
						}
						else
						{
		//DEADCODE AMM 14/02/00 					Key_Tests.mshift=true;
							Key_Tests.SetMouseShiftMode(SHIFTED);
							view->View_Point->FocusCockpit();			//RJS 7Sep00
						}

//DeadCode JIM 4Sep00 						_Analogue.SetAllAxesFromBackup();
//DeadCode JIM 4Sep00 						_Analogue.Initialise((int)Master_3d.winst,(int)Master_3d.hinst,Key_Tests.mshift,AA_NONE);

					}
				}
//				INT3;
			}
			AllowAliasing mainmode,uimode;
			if (	Master_3d.g_lpDIDevice								//JIM 2Nov00
				&&	_Analogue.WhatAliasModes(uimode,mainmode,view->View_Point) 
				&& !Key_Tests.KeyHeld3d(MOUSEMODETOGGLE)
				&& !Key_Tests.KeyHeld3d(MENUSELECT)
				&& !_DPlay.SimulateExitKey
				&& !_DPlay.Implemented									//JIM 24Oct00
				)
				_Analogue.Initialise((int)Master_3d.winst,(int)Master_3d.hinst,uimode,mainmode);

//DeadCode JIM 31Aug00 			if (Key_Tests.KeyPress3d(JOYSTICKMODETOGGLE))
//DeadCode JIM 31Aug00 			{
//DeadCode JIM 31Aug00 				if (Key_Tests.jshift)
//DeadCode JIM 31Aug00 					Key_Tests.SetJoystickShiftMode(NORMAL);
//DeadCode JIM 31Aug00 				else
//DeadCode JIM 31Aug00 					Key_Tests.SetJoystickShiftMode(SHIFTED);
//DeadCode JIM 31Aug00 
//DeadCode JIM 31Aug00 				_Analogue.SetAllAxesFromBackup();
//DeadCode JIM 31Aug00 				_Analogue.Initialise((int)Master_3d.winst,(int)Master_3d.hinst,Key_Tests.mshift,Key_Tests.jshift,true);
//DeadCode JIM 31Aug00 			}

			if (Key_Tests.KeyPress3d(SUICIDE))					//AMM 16Apr99
			{													//AMM 16Apr99
//DEADCODE AMM 06/03/00 				strcpy(_DPlay.PlayerDialogue,"hello there");
//DEADCODE AMM 06/03/00 				_DPlay.SendPlayerDialogue();


//DEADCODE AMM 25/02/00 				if (Key_Tests.jshift)
//DEADCODE AMM 25/02/00 					Key_Tests.jshift=false;
//DEADCODE AMM 25/02/00 				else
//DEADCODE AMM 25/02/00 					Key_Tests.jshift=true;
//DEADCODE AMM 25/02/00 
//DEADCODE AMM 25/02/00 				_Analogue.Initialise((int)Master_3d.winst,(int)Master_3d.hinst,Key_Tests.mshift,Key_Tests.jshift);

//DeadCode AMM 10Oct00 				if (!_DPlay.ResyncPhase)
//DeadCode AMM 10Oct00 				{
//DeadCode AMM 10Oct00 					_DPlay.Initiator=TRUE;
//DeadCode AMM 10Oct00 					_DPlay.BeginSyncPhase();
//DeadCode AMM 10Oct00 				}

				if (_DPlay.Implemented)							//AMM 16Apr99
					_DPlay.CommitSuicide();						//AMM 16Apr99
			}													//AMM 16Apr99

			if (_Replay.Playback)
			{
				if (_Replay.PlaybackPaused)
				{
// stops animations from continuing when playback reaches end of file and pauses

					Paused(TRUE);
				}
			}

			UByte okey=OverLay.keyFlags;
			OverLay.keyFlags&=KF_ACCELFRAMESMASK;
			
			if (!_DPlay.Implemented)
			{
				if (okey&KF_PAUSEOFF)		Paused(FALSE);
				else if (okey&KF_PAUSEON)	Paused(TRUE);
			}

			if (okey&KF_ACCELOFF)
			{
				{
					Accel(FALSE);
				}
			}
			else if (okey&KF_ACCELON)	Accel(TRUE);

			if (Accel()) 
			{
				if ( view->View_Point && view->View_Point->drawSpecialFlags )	//JON 3Oct00
				{	// can't be in replay - no need to test - we must be in the map screen
					OverLay.accelcountdown=(okey&KF_ACCELFRAMESMASK)<<1; // slow down the map accel...	//JON 3Oct00
				} else													//JON 3Oct00
				{														//JON 3Oct00
//DeadCode CSB 4Oct00 #ifdef NDEBUG
					OverLay.accelcountdown=(okey&KF_ACCELFRAMESMASK)<<2;	//Max value is 60 moves/timer call
//DeadCode CSB 4Oct00 #else			
//DeadCode CSB 4Oct00 					OverLay.accelcountdown=(okey&KF_ACCELFRAMESMASK)<<3;	//Max value is 60 moves/timer call
//DeadCode CSB 4Oct00 #pragma warnmsg("************************")
//DeadCode CSB 4Oct00 #pragma warnmsg("**** 3D ACCEL = x 8 **** //CSB 08/06/00")
//DeadCode CSB 4Oct00 #pragma warnmsg("************************")
//DeadCode CSB 4Oct00 #endif

					OverLay.accelcountdown=(okey&KF_ACCELFRAMESMASK)<<3;	//Max value is 60 moves/timer call
				} // end of are we in map screen						//JON 3Oct00
			}
		}
		else
		{
			timeout=true;
//DeadCode  11Oct00 			if (_DPlay.Implemented && _DPlay.csync)
//DeadCode  11Oct00 				INT3;
		}
///		((char*)0xb0000+160)[view->frametime]++;
	}

	for (view = viewedwin; view; view = view->nextview)					//CSB 08/03/00
		if((view) && (view->View_Point))								//CSB 08/03/00
		{																//CSB 08/03/00
			view->View_Point->move_time_ms += Timer_Code.FRAMETIME * 10;	//cs -> ms	//CSB 02/03/00	//CSB 08/03/00
#ifdef	_FRAMESHITE_
			fprintf(Three_Dee.framefp,"+\n");
#endif
//DEADCODE CSB 08/03/00 			PrintVar(65, 20, "mt %.0f ", FP(view->View_Point->move_time_ms));	//CSB 08/03/00
		}																//CSB 08/03/00

	if (!timeout)
	{
#ifndef NDEBUG
		static LARGE_INTEGER	pc,pc2;
		QueryPerformanceCounter(&pc);
		int cycles=OverLay.accelcountdown;
#endif

		while (OverLay.accelcountdown--)
		{
			MoveCycle(world);									//AMM 11May99
			if (OverLay.accelcountdown)
				if (	Key_Tests.KeyPress3d(RPM_00) 
					||	Key_Tests.KeyPress3d(RESETVIEW)
					||	Key_Tests.KeyPress3d(PADLOCKTOG)
					||	Key_Tests.KeyPress3d(SHOOT)
					||	Key_Tests.KeyPress3d(MENUSELECT)
					)
					OverLay.CancelAccel();
		}
//DeadCode CSB 15/06/99	#ifndef NDEBUG
//DeadCode CSB 15/06/99			int prevdif=pc.LowPart-pc2.LowPart;
//DeadCode CSB 15/06/99			QueryPerformanceCounter(&pc2);
//DeadCode CSB 15/06/99			int nextdif=pc2.LowPart-pc.LowPart;
//DeadCode CSB 15/06/99			static int monopos=0;
//DeadCode CSB 15/06/99			Mono_Text.PrintHexAt(monopos,0,cycles+howcamehere,3);
//DeadCode CSB 15/06/99			Mono_Text.PrintHexAt(monopos+4,0,prevdif/16,4);
//DeadCode CSB 15/06/99			Mono_Text.PrintHexAt(monopos+9,0,nextdif/16,4);
//DeadCode CSB 15/06/99			monopos+=16;
//DeadCode CSB 15/06/99			Mono_Text.PrintAt(monopos,0,UByteP("                  "));
//DeadCode CSB 15/06/99			if (monopos>=24*80)
//DeadCode CSB 15/06/99				monopos=0;
//DeadCode CSB 15/06/99	#endif

//DeadCode RJS 15Sep00 		_Miles.Commit();							//RJS 12Jan99
	}
}



void	Inst3d::MoveCycle(WorldStuff* worldref)					//AMM 11May99
{
	ULong num=1;
	_Replay.replayskip=false;									//RJS 08Nov99

	if (_Replay.Playback)										//AMM 08Feb99
	{
		if (_Replay.setpaused==1)								//AMM 22Apr99
		{														//AMM 14Apr99
			Paused(TRUE);										//AMM 14Apr99
			_Replay.setpaused=0;									//AMM 22Apr99
		}														//AMM 14Apr99
		else if (_Replay.setpaused==-1)							//AMM 22Apr99
		{														//AMM 22Apr99
			Paused(FALSE);										//AMM 22Apr99
			_Replay.setpaused=0;									//AMM 22Apr99
		}														//AMM 22Apr99

		switch (_Replay.ReplayFlag)									//AMM 14Jan99
		{
		case RF_NONE:
			break;

		case RF_SKIPFRAMES:
		case RF_BLOCKREWIND:
		case RF_SKIPTOPREVIOUSMARK:
		case RF_SKIPTONEXTMARK:
			_Replay.CalcCurrPos();									  //JIM 19/05/99
			if (_Replay.skipOK)
			{
				num=_Replay.framestoskip;//+1;
 				_Replay.ResetFlags();
				_Replay.replayskip=true;						//RJS 08Nov99
			}
			break;

		case RF_BLOCKFORWARD:
 			_Replay.ResetFlags();
			break;

		case RF_FRAMEFORWARD:
			if (Paused())
				_Replay.FrameForward();
			else
				_Replay.ResetFlags();
			break;

		case RF_FRAMEREWIND:
			if (!Paused())
			{
				Paused(TRUE);
				_Replay.PlaybackPaused=TRUE;
				OverLay.pCurScr=OverLay.pNewScr=&OverLay.replayScr;
			}
			num=_Replay.FrameRewind();
			_Replay.replayskip=true;							//RJS 08Nov99
			_DPlay.BackupSeen();
			_DPlay.BackupGhost();
			break;
		}
	}

	if (!Paused()												//AMM 14Jan99
	|| _Replay.ReplayFlag==RF_FRAMEFORWARD						//AMM 14Jan99
	|| _Replay.ReplayFlag==RF_FRAMEREWIND						//AMM 14Jan99
	|| _Replay.replayskip)										//RJS 08Nov99
	{
		int oldprec=GETPREC();
		SETPREC(3);
#ifndef NDEBUG
//DeadCode AMM 9Aug00 			if (GETPREC()!=3)
//DeadCode AMM 9Aug00 				INT3;
#endif
		
		while (num--)											//AMM 06Oct98
		{
			MobileItem::WinMove(timeofday,worldref);

			if (_Replay.replayskip)								//RJS 08Nov99
			{	
				if (viewedwin)
				{
					View3d* view=viewedwin;

					view->frametime=Timer_Code.FRAMETIME;
					_Replay.UpdateSmokes();
				}
			}
		}

		if (_DPlay.Implemented)
		{
			if (_DPlay.ResyncPhase)
			{
				Paused(TRUE);
				_DPlay.csync=false;
			}
		}

#pragma warnmsg(__HERE__"GETPREC()!=3  !!!!")
#ifndef NDEBUG
//DeadCode AMM 9Aug00 			if (GETPREC()!=3)
//DeadCode AMM 9Aug00 				INT3;
#endif
		SETPREC(oldprec);

		if (_Replay.Playback)
			_Replay.CalcCurrPos();
	}

	if (_Replay.Playback)
	{
		if (_Replay.ReplayFlag==RF_FRAMEREWIND || _Replay.ReplayFlag==RF_FRAMEFORWARD)						//AMM 14Jan99
		{															//AMM 14Jan99
			_Replay.ResetFlags();										//AMM 18Feb99
		}															//AMM 14Jan99
	}
}

void	View3d::BlockTick(Bool setit)
{
	inst->BlockTick(setit);
}

void	ViewPoint::BlockTick(Bool q)
{
	view3dwin->BlockTick(q);
}

void	Inst3d::BlockTick(Bool setit)
{
	while (insidetimer == TRUE)
	{Sleep(0);}

 //		insidetimer = insidetimer;

	if (!mapview)
	{
	if (setit)
	{		
		int bt=LockExchange(&blocktick,1);
		while (bt==1)
		{
			Sleep(0);												  //JIM 21/12/98
			;;//cope with simultanious accesses by releasing timeslice? //JIM 21/12/98
			bt=LockExchange(&blocktick,1);							  //JIM 21/12/98
		}
	}
	else
	{
		howcamehere=0;
		int bt=LockExchange(&blockticks,0);
		do{
			while (bt--)
			{
				howcamehere+=0x100;
				if (!_DPlay.Implemented || (_DPlay.Implemented && _DPlay.csync)) //AMM 09/07/99
					DoMoveCycle();
			}
			bt=LockExchange(&blockticks,0);
		} while (bt);
		//there's always a chance one will slip through, but we will pick it up later!
		bt=LockExchange(&blocktick,0);
		if (bt!=1)
			_Error.EmitSysErr("Something wrong in semaphore logic!");
	}
	}
}

int	View3d::PeekFrameTime()
{
	if (doneframe)
		return 0;
	else
		return frametime;
}
int	View3d::LastFrameTime()
{
//	*(char*)0xb0000='0'+lastframetime;
	return lastframetime;
}
int View3d::TimeSinceLastMove()
{
	return timeSinceLastMove;
}
//DeadCode PD 24Nov99 int	Display::FrameTime()
//DeadCode PD 24Nov99 {
//DeadCode PD 24Nov99 	return	view3dwin->LastFrameTime();
//DeadCode PD 24Nov99 }

int	ViewPoint::FrameTime()
{
	return	view3dwin->LastFrameTime();
}

int ViewPoint::TimeSinceLastMove()
{
	return view3dwin->TimeSinceLastMove();
}

int	ViewPoint::RealFrameTime()
{
//	*(char*)0xb0002='0'+view3dwin->RealFrameTime();
	return	view3dwin->RealFrameTime();
}

int	ViewPoint::TimeOfDay()
{
//	*(char*)0xb0002='0'+view3dwin->RealFrameTime();
	if (!this)														  //AMM 25/06/99
		return 0;													  //AMM 25/06/99
	return	view3dwin->TimeOfDay();
}

void	View3d::DoneFrame()
{
	doneframe=TRUE;
}

void	AggTracer(char* str)
{
//	TRACE0(str);
}

bool ViewPoint::Accel()
{
	if (!this) return false;
	if (!view3dwin) return false;
	return view3dwin->Accel();
}
int COverlay::GetTime()
{
	return 0;	//Master_3d.currinst->timeofday;
}
