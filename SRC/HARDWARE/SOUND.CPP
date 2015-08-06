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

//------------------------------------------------------------------------------
//Filename       sound.cpp
//System         
//Author         Robert Slater
//Date           Wed 21 Feb 1996
//Description    MIDI and sound sample library functions
//				Engine sound is at sample queue position 0,
//				Machine gun sound is at sample queue position 1
//------------------------------------------------------------------------------

//#define		_NO_Sound_AUDIO_

#ifndef	NDEBUG
//	#define		_NO_RADIOCHATTER_
//	#define		_WAITFORCRAIG_	
//#define	_NOVELOCITY_
//#define	_VOLTEST_
//#define	_NOSOUNDIN3D_
#endif
	#define		_NO_MUSIC_
//	#define		_NO_RADIOCHATTER_

//#define	_NO_LUF_

#include 	"dosdefs.h"

#include	<stdlib.h>											//RJS 19Jul96
#include 	<string.h>
#include	"sample.h"											//RJS 08Nov99
#include	"digdrvr.h"											//RJS 08Nov99
#include	"music.h"											//RJS 08Nov99
#define 	F_GRAFIX
#include	"files.g"
#include	"fileman.h"
#include	"worldinc.h"
#include	"miles.h"											//RJS 05Nov99
#include	"rchatxtr.h"										//RJS 10Jun98
#include	"milesxtr.h"										//RJS 05Nov99
//TEMPCODE DAW 13/04/00 #include	"smack.h"
#include	"planetyp.h"
#include	"worldinc.h"
#include	"Mytime.h"											//PD 15Mar96
#include	"mymath.h"
#include	<string.h>
#include	"hardpasm.h"										//RJS 22Jul96
#include	"viewsel.h"											//RJS 02Sep96
#include	"savegame.h"										//RJS 02Sep96
#include	<stdio.h>											//RJS 25Nov96
#include	"monotxt.h"											//RJS 09Mar98
#include	"sndfonts.h"										//RJS 03Jul98
#include	"flymodel.h"
#include "modvec.h"
#include "Model.h"
#include	"analogue.h"
#include	"replay.h"
#include "transite.h"
#include	"persons2.h"
#include	"mapsfx.h"											//RJS 08May00
#include	"missman2.h"
#include	"fastmath.h"
#include	"messengn.h"													//RJS 29Sep00
#include	<Vfw.h>

const	double	VOL_DISTUNIT = 150.;
const	double	VOL_DISTUNITSQRD = 150.*150.;
const	int		VOL_SCALE_SHIFT = 6;								//RJS 14Sep100
const	int		VOL_SCALE_FROM_PREFS = 8-VOL_SCALE_SHIFT;					//RJS 14Sep00
const	int		VOL_TOP_CLIP = 511;											//RJS 14Sep00
const	int		VOL_BOT_CLIP = 0;											//RJS 14Sep00
const	double	VOL_DISTANCESQUAREDOVERVOLSCALE = VOL_DISTUNITSQRD / 64.;			//RJS 14Sep00

const	SLong	VOL_NOTSET = 0x80000000;								//RJS 18Oct00
const	int	SFX_MEMORY_MIN = 64*1024*1024;
const	int	RADIO_MEMORY_MIN = 32*1024*1024;				//32 meg
#define		MIDI_NOTE_ON	0x90
#define		NOTE_ROOT		60

const	SLong	JERICO_VEL_MAX = 175;			//ms					//RJS 25Oct00
const	SLong	JERICO_VEL_MIN = 75;									//RJS 25Oct00
const	SLong	JERICO_SCALE = JERICO_VEL_MAX - JERICO_VEL_MIN;			//RJS 25Oct00


MINMAX	(MTC,0,25) mtc=MTCMIN;
MTC	operator ++(MTC& m)
	{m=(MTC)((m+1)%MTCMAX);return(m);}
int		boffcount;
static SoundBase Blank={FALSE};												//RJS 05Dec96
Sound _Miles;													//RJS 05Nov99
CON Sound::Sound() {SoundBase::operator=(Blank);trySoundFonts=false;directoryOffset=0;volumeDesktop=VOL_NOTSET;usingSmacker = false;}


 		SequenceStruct	Sound::tune[Sound::MAXTUNES];
 		MusicRequest	Sound::request;
		SampleLibrary	Sound::wavetable;
		SampleRec*		Sound::thesample;						//MS 23Sep98
		PlayingRec*		Sound::soundqueue;						//RJS 28Sep00
		StatusRec		Sound::status;
		SampleRequest	Sound::soundtoplay;
		HTIMER			Sound::timer;
		EnginePlayInfo	Sound::EngineSound;						//RJS 21Oct97
		Bool			Sound::canplaynothing;					//RJS 21May98
		Bool			Sound::critical;						//RJS 21May98
		Bool			Sound::inprefs;							//RJS 21May98
		Bool			Sound::onground;						//RJS 21May98
		Bool			Sound::musicstopped;					//RJS 21May98
		int				Sound::damagelevel;						//RJS 21May98
		int				Sound::delindex;						//RJS 21May98
		int				Sound::thesmackervol;					//RJS 21May98
		FileNum			Sound::currentengine;					//RJS 21May98
		int				Sound::bouncecount;						//RJS 21May98
		SLong			Sound::MAXSAMPLES_LOADED;				//MS 23Sep98
		SampleRec*		Sound::themusicsample;					//RJS 14Apr99
		SLong			Sound::percvolscale;					//RJS 29Jun99
		PercRec			Sound::percussionLog;					//RJS 18Aug99
		Sound::HSampRate		Sound::CUR_SAMP_VAL;					//RJS 14Jun00
		float			Sound::sampRateScale;					//RJS 14Jun00
		int				Sound::directoryOffset;							//RJS 14Jun00



const	float	VEL_SCALE = 0.01;										//RJS 12Jun00
const	float	MIN_DISTANCE = 100*100;			//100 m					//RJS 26Sep00
const	float	MAX_DISTANCE = 10000*100;			//10,000 m			//RJS 26Sep00



int	NCIndex(char*	s,char*	t)
{
	int	i, j, k;

	for(i=0;s[i]!='\0';i++)
	{
		for(j=i,k=0;t[k]!='\0' && toupper(s[j])==toupper(t[k]);j++,k++);
			if(t[k]=='\0')
				return(i);
	}
	return(-1);
}

#ifndef	NDEBUG
extern	bool	naughtynaughty;											//RJS 8Nov00
#endif




//#pragma on (check_stack);
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartUpSound
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Set up midi and digital samples system	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
extern	void*	ailmalloc(size_t);
extern	void	ailfree(void*);
void	Sound::StartUpSound(ULong	thiswin)					//RJS 19May98
{
#ifdef _NO_Sound_AUDIO_
	mdi = NULL;
	dig = NULL;
	timer = NULL;
	Save_Data.vol.sfx = Save_Data.vol.music = Save_Data.vol.uisfx = 0;//RJS 12Mar99
#else
	int			tuneno;											//RJS 13Mar98
	char		found;											//RJS 13Mar98
	int			size;											//RJS 29Aug96
	SLong		result;											//RJS 29Aug96
	fileblock	*theblock;										//RJS 29Aug96
	int			sequenceno;										//RJS 30Aug96
	MMRESULT	midiRes;										//RJS 03Apr97
	MIDIOUTCAPS midiOutCaps;									//RJS 03Apr97
	SLong		ndevs;
	SLong		driverid;
	LPHMIDIOUT	midiOutDev;
	ULong		bestCnt = 3;

	if (mdi || dig || timer)								//RJS 18May98
		return;

	currWin = thiswin;			
	View_Point=NULL;											//RJS 13Mar98
	midiOutDev=NULL;
																//RJS 13Mar98
	for (bestCnt=0; bestCnt < 16; bestCnt++)
		bestDrivers[bestCnt] = -1;

	bestCnt = 3;

	mdi = NULL;
 	Save_Data.vol.anim = thesmackervol = 80;							//RJS 18Oct00
	uDriverID = MIDI_MAPPER;

	int	cmatch;
	ndevs = midiOutGetNumDevs();
	for (driverid = 0; driverid < ndevs; driverid++)
	{
		midiRes = midiOutGetDevCaps((ULong)driverid, &midiOutCaps, sizeof (MIDIOUTCAPS));
		switch (midiOutCaps.wTechnology)
		{
		case MOD_MAPPER:
			// Sound Font is the 1st choice...
			if (NCIndex(midiOutCaps.szPname,"SoundFont") != -1)
				bestDrivers[0] = driverid;
			else
				bestDrivers[bestCnt++] = driverid;
			break;
		case MOD_SYNTH:
			//Internal synthesizer...
			if (bestDrivers[1] == -1)
			{
				if (	(NCIndex(midiOutCaps.szPname,"Wave") != -1)
					||	(NCIndex(midiOutCaps.szPname,"Software") != -1)
					||	(NCIndex(midiOutCaps.szPname,"S/W") != -1)	)
 					bestDrivers[bestCnt++] = driverid;
				else
 					bestDrivers[1] = driverid;
			}
			else
 				bestDrivers[bestCnt++] = driverid;
			break;
		case MOD_FMSYNTH:
			bestDrivers[2] = driverid;
			break;
		case MOD_SQSYNTH:
			bestDrivers[bestCnt++] = driverid;
			break;
		case MOD_MIDIPORT:
			// not supported...
			break;
		}
	}

	havePercussion = false;										//RJS 14Apr99
#ifndef	_NO_MUSIC_
	for (driverid = 0; driverid < bestCnt; driverid++)
	{
		if (bestDrivers[driverid] > -1)
		{
			switch (driverid)
			{
			case 0:
				MusicDir = 0;
				break;
			case 1:
				MusicDir = FIL_DIR_MUSICMED-FIL_DIR_MUSIC;
				break;
			default:
				MusicDir = FIL_DIR_MUSICLOW-FIL_DIR_MUSIC;
				havePercussion = true;							//RJS 14Apr99
				break;
			}

			break;
		}
	}
#endif

	uDriverID = (ULong) bestDrivers[driverid];

	mdi = new Music;
	pooMidiDev = (void*) midiOutDev;

	MultiMediaError(midiRes);									//RJS 08Nov99

	wavetable.blockptr = NULL;

	for (tuneno = 0; tuneno < MAXTUNES; tuneno++)				//RJS 30Aug96
	{
		tune[tuneno].blockptr = NULL;
		tune[tuneno].dlsPtr = NULL;
		tune[tuneno].xmiPtr = NULL;

		for (sequenceno = 0; sequenceno < MAXSEQUENCES; sequenceno++)
		{
			tune[tuneno].sequence[sequenceno] = NULL;
			tune[tuneno].DLSsequence[sequenceno] = NULL;		//RJS 19May98
		}
	}

	status.nosamples = 0;

	InitUI(thiswin);													//RJS 28Sep00

	EngineSound.ChanPtr = NULL;											//RJS 28Sep00
	EngineSound.SubChanPtr = NULL;										//RJS 28Sep00
#endif

	MAXSAMPLES_LOADED = 0;										//MS 23Sep98
	thesample = NULL;											//MS 23Sep98
	themusicsample = NULL;										//RJS 14Apr99
	nomusicsamples = 0;											//RJS 14Apr99

	status.notunes = 0;

	// Initialise callback values...

	ResetMidiFlags();											//RJS 29Aug96

	canplaynothing = FALSE;

	EngineSound.Volume = 30000;									//RJS 21Oct97
	musicstopped = FALSE;										//RJS 22Aug96

	ResetSoundFlags();											//RJS 22Aug96
	EngineSound.VolLoaded = 0;									//RJS 18Jan99

	GetSampleVolumes();											//RJS 03Apr97
																//MS 23Sep98
	// Reset all samples...										//MS 23Sep98
	for (int	count = 0; count < MAXSAMPLES_LOADED; count ++)		//MS 23Sep98
		thesample[count].blockptr = NULL;						//MS 23Sep98

 	allowedsamples = status.nohandlers / 3;						//RJS 17Nov98

	donePreLoad = false;		//RJS 01Apr99
	shootTimer = 0;

	donePreLoadRadio_2D = false;								//RJS 14Aug00
	donePreLoadRadio_3D = false;								//RJS 14Aug00
	randomFAC = randomTOWER = 0;								//RJS 17May99

	percvolscale = 256;											//RJS 29Jun99
	rchatter_allowed = true;									//RJS 05Nov99

	theSubject = new SubjectStruc;								//RJS 12Jan00
	theListener = new ListenerStruc;							//RJS 12Jan00

//Temp...
#ifndef	BOB_DEMO_VER
	if (FILEMAN.getTotalMem() >= SFX_MEMORY_MIN)
	{	//Forced this to LOW for debugging...	//JIM 2/10/00
		Save_Data.hardwareconfig |= HW_SFXQUALITY;
		hiResSFXAvailable = true;
	}
	else
#endif
	{
		hiResSFXAvailable = false;											//RJS 14Jun00
		Save_Data.hardwareconfig %= HW_SFXQUALITY;
	}

	preLoadChatStatus = false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDigitalDriver
//Author		Robert Slater
//Date			Mon 18 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::NewDigitalDriver(HSampRate	srate,int	nohandlers,Bool	usemono, bool have3d)
{
	int 		count;
	char		found;
	int			size;											
	SLong		result;			
	Bool		ok;
	WAVEFORMATEX PCM_waveformat;
	int			volBeforeCloseDown = Save_Data.vol.sfx;					//RJS 16Nov00

	delayedsounds.isSet = FALSE;										//RJS 30Oct00

	ok = FALSE;

	EngineSound.ChanPtr = NULL;
	EngineSound.SubChanPtr = NULL;

	_MsgBuffer.ClearRadio();										//RJS 29Sep00

	if (dig)
	{
		ClearSoundQueue();

		CloseDownSmall();												//RJS 16Nov00
	}

	// Setup Digital Sounds

	WORD	chans;
	DWORD	rate;
	WORD	bits;

	if (usemono)												//DAW 15Dec96
		chans = 1;												//DAW 15Dec96
	else														//DAW 15Dec96
		chans = 2;												//DAW 15Dec96

	rate = (DWORD) srate;
 	bits = 16;

	PCM_waveformat.wFormatTag = WAVE_FORMAT_PCM;
	PCM_waveformat.nChannels = chans;
	PCM_waveformat.nSamplesPerSec = rate;
	PCM_waveformat.nAvgBytesPerSec = rate * (bits / 8) * chans;
	PCM_waveformat.nBlockAlign = (bits /8) * chans;
	PCM_waveformat.wBitsPerSample = bits;

	if (nohandlers < 4)	nohandlers = 4;

	int	maxhandlers = nohandlers;
	int	oldVol = VOL_NOTSET;											//RJS 18Oct00

	dig = new DigitalDriver((HWND)currWin,&Save_Data.SFXDevice); //AMM 29/11/99
	if (!dig->Init(&PCM_waveformat,have3d,maxhandlers,oldVol))			//RJS 18Oct00
	{
		CloseDownSmall();												//RJS 16Nov00

		Save_Data.vol.rchat = 0;
	}

	if (volumeDesktop == VOL_NOTSET)									//RJS 18Oct00
		volumeDesktop = oldVol;											//RJS 18Oct00

#ifndef	BOB_DEMO_VER
	if (!hiResSFXAvailable)
#endif
		Save_Data.hardwareconfig %= HW_SFXQUALITY;

	if (Save_Data.hardwareconfig[HW_SFXQUALITY])
	{
		directoryOffset = FIL_DIR_SFX_HI - FIL_DIR_SFX;						//RJS 14Jun00

		CUR_SAMP_VAL = NOM_SAMP_VAL;							//RJS 14Jun00
	}
	else
	{
		directoryOffset = 0;

		CUR_SAMP_VAL = MIN_SAMP_VAL;							//RJS 14Jun00
	}

	sampRateScale = CUR_SAMP_VAL / MIN_SAMP_VAL;				//RJS 14Jun00

	if (dig)
	{
		// Initialise as many sound driver handlers as we can
		count = 0;

		soundqueue = new PlayingRec[maxhandlers];
		if (soundqueue)
		{
			if (nohandlers >= maxhandlers)								//RJS 28Sep00
				nohandlers = maxhandlers;								//RJS 28Sep00

			for (count = 0; count < nohandlers; count ++)
			{
				soundqueue[count].handler = dig->AllocateSampleHandle();
				if (soundqueue[count].handler)
					soundqueue[count].Clean();
				else
					break;
			}

			EngineSound.ChanPtr = &soundqueue[0];
			EngineSound.SubChanPtr = &soundqueue[1];
		}

		status.nohandlers = count;
		if (!count)														//RJS 28Sep00
		{
			CloseDownSmall();											//RJS 16Nov00

			Save_Data.vol.uisfx = 0;
			Save_Data.vol.rchat = 0;
			Save_Data.vol.uiambient = 0;
		}
		else
			Save_Data.vol.sfx = volBeforeCloseDown;						//RJS 16Nov00

		if (status.nohandlers || status.nohandlers ==nohandlers)						//JIM 18Dec96
			ok = TRUE;
	}
	else
	{
		Save_Data.vol.sfx = 0;
		Save_Data.vol.uisfx = 0;								//RJS 12Mar99
	}

	playerShooting = false;										//RJS 12Apr99

#ifndef	_NO_MUSIC_
	if (!mdi->Init(dig))
#endif
		Save_Data.vol.music = 0;

// Set up default eye positions...
	eyeVector_x = 0;
	eyeVector_y = 0;
	eyeVector_z = 1;
	eyeVelocity.X = eyeVelocity.Y = eyeVelocity.Z = 0;
	if (Manual_Pilot.ControlledAC2 && !usemono)					//RJS 19Oct00
	{
		eyeWorld = Manual_Pilot.ControlledAC2->World;
		eyeHdg = SWord(Manual_Pilot.ControlledAC2->hdg);
		eyePitch = SWord(Manual_Pilot.ControlledAC2->pitch);
	}
	else
	{
		eyeWorld.X = eyeWorld.Y = eyeWorld.Z = 0;
		eyeHdg = eyePitch = 0;
	}

	return(ok);													//RJS 12Jan00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TuneInRange
//Author		Robert Slater
//Date			Thu 29 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::TuneInRange(int	tuneno)
{
	if (	(tuneno < 0)
		||	(tuneno >= MAXTUNES)	)
		return(FALSE);

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceInRange
//Author		Robert Slater
//Date			Mon 25 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::SequenceInRange(TuneStrucP	TunePtr, int	seqno)
{
	if (	(seqno < 0)											//RJS 26Feb98
		||	(seqno >= TunePtr->nosequences)	)					//RJS 26Feb98
		return(FALSE);											//RJS 26Feb98
																//RJS 26Feb98
	return(TRUE);												//RJS 26Feb98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleInRange
//Author		Robert Slater
//Date			Mon 25 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::SampleInRange(int	sampleno)
{
	if (	(sampleno < 0)
		||	(sampleno >= MAXSAMPLES_LOADED)	)
		return(FALSE);

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HandlerInRange
//Author		Robert Slater
//Date			Mon 25 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::HandlerInRange(int	qpos)
{
	if ((qpos > -1) && (qpos < status.nohandlers))				//RJS 19Nov96
		return(TRUE);											//RJS 19Nov96

	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitTune
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Initialises all the sequences in a tune
//			
//
//Inputs				
//
//Returns		
//	
//------------------------------------------------------------------------------
void	Sound::InitTune(TuneStrucP	TunePtr)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartMain
//Author		Robert Slater
//Date			Thu 29 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::StartMain(SLong	vol)
{
 	int		sequenceno;
 	int		tuneno;
 	int		nosequences;
 	ULong	status, channelno;									//RJS 30Sep96
//DeadCode RJS 20Oct00  	int		combatbase = GetIndex(FIL_MUSIC_MAIN);				//RJS 02Jul98
 
 	if ((Save_Data.vol.music != 0) && !incombat)					//RJS 25Jun98
 	{
		if (mdi->Playing())
			return FALSE;
 
 		TuneStrucP	TunePtr = LoadTune(FIL_MUSIC_MAIN);					//RJS 18May98
 		if (TunePtr && TunePtr->blockptr && !request.activated)
 		{
 			HSEQUENCE	thishandle;
 
 			request.wait = FALSE;
 			request.todiscard = FALSE;
 			request.killnow = FALSE;
 			incombat = TRUE;											//RJS 06Jan97
 			request.mainstopped = FALSE;								//RJS 06Jan97
 			request.alonetuneno = NULL;									//RJS 26Feb98
 			request.forcestop = 0;										//RJS 18Jun99
 
 			// Clip the volume if out of range...
 
 			ClipVolume(vol);							//RJS 14Sep00
 
			mdi->SetVolume(vol);
			mdi->Play(TunePtr->dlsPtr,TunePtr->dlsSize);
 		}
 	}
 
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopMain
//Author		Robert Slater
//Date			Tue 12 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StopMain()
{
 	int	count;
 
 	if (	(Save_Data.vol.music == 0)
 		||	(incombat == FALSE)			
 		||	(request.mainstopped == TRUE)		)
 		return;
 
 	request.activated = INT_NULL;
 
	mdi->SetVolume(0,3000);
 
 	request.activated |= INT_STOPSEQUENCE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiscardMusic
//Author		Robert Slater
//Date			Thu 29 Aug 1996
//
//Description	Throws away all the main music stuff
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::DiscardMusic(TuneStrucP	exception)
{
 	int			endtune = GetIndex(FIL_MUSIC_LAST_TUNE);
 	int			tuneno;
 	int			nosequences;
 	int			sequenceno;
 	Bool		specialcase = FALSE;
 	TuneStrucP	TunePtr;
 
 	if (!mdi)													//RJS 03Dec96
 		return;													//RJS 03Dec96
 
 	request.activated = INT_NULL;
 	incombat = FALSE;											//RJS 12Nov96
 
 	for (tuneno = 0; tuneno < endtune; tuneno++)
 	{
 		TunePtr = &tune[tuneno];
 
 		if (TunePtr == exception)
 			specialcase = TRUE;
 		else
 			specialcase = FALSE;
 
 		if (TunePtr->blockptr)
 		{
 			nosequences = TunePtr->nosequences;

 			mdi->Stop();
 
 			if (!specialcase)
 			{
 				delete TunePtr->blockptr;
 
 				TunePtr->blockptr = NULL;
 			}
 		}
 	}
 
 	request.killnow = FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetIndex
//Author		Robert Slater
//Date			Fri 8 Mar 1996
//
//Description	Calculates the index no of a file
//
//Inputs		The file number
//
//Returns		The file index
//
//------------------------------------------------------------------------------
int	Sound::GetIndex(FileNum	thefile)
{
	return((thefile & FILENUMMASK) - 1);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadTune
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Gets a new tune and initialises it
//
//Inputs		Filename
//
//Returns		TRUE  if success
//				FALSE otherwise
//
//------------------------------------------------------------------------------
TuneStrucP	Sound::LoadTune(FileNum	thefile)
{
	TuneStrucP	TunePtr = NULL;									//RJS 22Nov99
	SLong		result, size;
	void		*tmpptr;
	SLong		*headptr;
	int			count;
//DeadCode RJS 20Oct00 	UWord		noforms = 0;
	SLong		header;
	fileblock	*theblock;
	int			tuneno = GetIndex(thefile);
	TuneType	ttype;
//DeadCode RJS 20Oct00 	HSEQUENCE	tmphandle = NULL;
																//RJS 26Feb98
	if (Save_Data.vol.music && TuneInRange(tuneno))				//RJS 26Feb98
	{															//RJS 26Feb98
		TunePtr = &tune[tuneno];								//RJS 26Feb98
		if (TunePtr->blockptr == NULL)							//RJS 26Feb98
		{
			if (tuneno < GetIndex(FIL_MUSIC_STAND_ALONE))			//RJS 18May98
				ttype = T_main;									//RJS 18May98
			else												//RJS 18May98
			{													//RJS 06May99

				if (tuneno < GetIndex(FIL_MUSIC_PRIORITY))		//RJS 06May99
					ttype = T_independent;						//RJS 06May99
				else											//RJS 06May99
					ttype = T_independent_pri;					//RJS 06May99

			}

			// All clear, so load the sequences file...
			thefile=(FileNum)(thefile+MusicDir);
	
			theblock = new fileblock (thefile);
			if (theblock)
			{
				tmpptr = getdata(theblock);

				size = getsize(theblock);

				TunePtr->blockptr = theblock;						//RJS 18May98
				TunePtr->size = size;								//RJS 18May98
				TunePtr->ttype = ttype;
				status.notunes = status.notunes + 1;

				headptr = (SLong*) tmpptr;

				TunePtr->dlsPtr = tmpptr;
				TunePtr->dlsSize = size;

//UpdateMilesCode RJS 08Nov99 				SLong	ftype = AIL_file_type((void*)headptr,size);
//UpdateMilesCode RJS 08Nov99 				switch (ftype)
//UpdateMilesCode RJS 08Nov99 				{
//UpdateMilesCode RJS 08Nov99 					case AILFILETYPE_XMIDI:
//UpdateMilesCode RJS 08Nov99 					case AILFILETYPE_XMIDI_DLS:
//UpdateMilesCode RJS 08Nov99 						SetUncompressedDLS(TunePtr,tmpptr,size);
//UpdateMilesCode RJS 08Nov99 						break;
//UpdateMilesCode RJS 08Nov99 					case AILFILETYPE_XMIDI_MLS:
//UpdateMilesCode RJS 08Nov99 						SetCompressedDLS(TunePtr,tmpptr,size);
//UpdateMilesCode RJS 08Nov99 						break;
//UpdateMilesCode RJS 08Nov99 				}
//UpdateMilesCode RJS 08Nov99
//UpdateMilesCode RJS 08Nov99				SetXMidi(TunePtr);
//UpdateMilesCode RJS 08Nov99				SetDLS(TunePtr);
			}
		}
	}

	return(TunePtr);											//RJS 26Feb98
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InstallWaveTable
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	
//
//Inputs		Digital waveform table filename		
//
//Returns		
//
//------------------------------------------------------------------------------
void	Sound::InstallWaveTable(FileNum	thefile,Bool	useDLS)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSpot
//Author		Robert Slater
//Date			Mon 25 Mar 1996
//
//Description	Process interrupt spot-effect data if available.
//				This procedure initialises the appropriate sequence for the
//				next callback function with a value of 127.
//
//				Ensures the pan and volume of samples are updated in the
//				3d world.
//
//				Chugs the engine.
//
//Inputs		camera world viewpoint
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ProcessSpot(ViewPoint*	viewobject)
{
#ifdef	_VOLTEST_
	EngineSound.Volume--;
	if (EngineSound.Volume < 0)	EngineSound.Volume = EngineSound.VolLoaded;
#endif
	if (viewobject && Manual_Pilot.ControlledAC2)					//RJS 11Jun99
	{
		if (	viewobject->FrameTime()								//RJS 12Jan00
			&&	!viewobject->Accel()
			&&	(	!viewobject->drawSpecialFlags
				||	(viewobject->drawSpecialFlags & VIEW_SPECIAL_REPLAY) )	)	
		{
			SLong	seqno;
			SLong	tuneno;
			SWord	engtype;
			SLong	engloop;
			SLong	englength;
			TuneStrucP	TunePtr;

			if (Save_Data.vol.music != 0)
			{
//DeadCode RJS 20Oct00 				TuneStrucP	BaseTunePtr = &tune[GetIndex(FIL_MUSIC_MAIN)];//RJS 18May98
				HSEQUENCE	thishandle;

				//This will catch music not caught by the interrrupt...
				if (request.activated & INT_STOPSEQUENCE)
 				{
 					bool		stopnow = true;

					if (mdi->Playing())
 					{
						if (mdi->GetVolume())
 							stopnow = false;
 					}
 
 					if (stopnow)
 					{
 						request.activated &= ~INT_STOPSEQUENCE;
 						request.mainstopped = TRUE;
 						request.killnow = TRUE;
 					}
 				}

				if (request.killnow)
				{
					if (request.forcestop)								//RJS 18Jun99
					{
						request.forcestop = 0;
						TunePtr = NULL;
					}
					else
						TunePtr = request.alonetuneno;					//RJS 26Feb98

					DiscardMusic(TunePtr);								//RJS 26Feb98
					if (TunePtr)
					{
						mdi->SetVolume(request.NewVolume,request.NewFade);
						mdi->Play(TunePtr->dlsPtr,TunePtr->dlsSize);
					}
					else
						request.musictimeout = 0;
				}
				else
				{
					if (request.musictimeout)
					{
						request.musictimeout -= viewobject->FrameTime();
						if (request.musictimeout <= 0)
						{
							request.musictimeout = 0;
							SequenceMute(3000);
						}
					}
				}

				if (request.mainstopped)								//RJS 12Nov96
				{
					request.mainstopped = FALSE;
					incombat = FALSE;
				}
			}

			// For sound effects...

			allowedsamples = status.nohandlers / 3;						//RJS 09Dec96

			if (EngineSound.Freq == 0)									//RJS 21Oct97
				return;													//RJS 03Dec96

			if (Save_Data.vol.sfx != 0)
			{
				if (!_Replay.replayskip)
				{											//PD 13Aug99
					Bool		delLooped;
					ItemBasePtr	delItem;
					FileNum		delFile;
					FileNum		delSFile;
					FileNum		delEFile;
					SLong		delVol;
					bool		isOnce;

					while (delayedsounds.Get(delFile,delItem,delVol,delLooped,delSFile,delEFile,isOnce))	//RJS 16Oct00
					{
						if (delLooped)
							PlayLooped(delFile,delItem,delVol,0);
						else
						{
							if (isOnce)
								PlayOnce(delFile,delItem,delVol,delSFile,delEFile);
							else
								PlaySample(delFile,delItem,delVol);
						}
					}
				}											//PD 13Aug99
				else
					delayedsounds.isSet = FALSE;

//DeadCode RJS 9Jun00 				if (EngineSound.CockpitWind)
					PlayWind();

				if (soundtoplay.thesample != FIL_NULL)
				{
					PlaySample(soundtoplay.thesample,soundtoplay.vol,soundtoplay.pan);

					soundtoplay.thesample = FIL_NULL;
					soundtoplay.vol = 64;
					soundtoplay.pan = 0;
				}

				if (EngineSound.Dying && !EngineSound.Dead)				//RJS 21Oct97
				{
	//				if (abfactor == AEROBATIC_HIGH)
	//				{
	//				}
	//				else
					{
						ULong	thePosition;

						engtype = Math_Lib.rnd(5 + damagelevel);		//RJS 02Dec96
						englength = EngineSound.ChanPtr->sampleindex->size;	//RJS 17Oct97
						engloop = englength / (2 + Math_Lib.rnd(5));
						engloop = englength - engloop;

						if (	(EngineSound.ChanPtr->handler->GetPosition(thePosition) > engloop)
							||	!canplaynothing)
						{
							if ((engtype > 0) && (engtype < 3))			//RJS 19Feb98
							{
								engtype -= 1;
								OverrideSample(EngineSound.ChanPtr,FIL_SFX_ENGINE_SPLUTTER,EngineSound.Volume);//RJS 19Feb98

								canplaynothing = TRUE;
							}
							else
							{
								if (canplaynothing)
								{
									OverrideSample(EngineSound.ChanPtr,EngineSound.CurrentFile,EngineSound.WindVolume,0,CUR_SAMP_VAL);//RJS 14Jun00

									UpdateEngine();						//RJS 03Dec96
									canplaynothing = FALSE;
								}
							}
						}
					}
				}
				else
				{
					if (!EngineSound.Dead)								//RJS 21Oct97
					{
						UpdateEngine();										//RJS 03Dec96
						OverRevCheck();		//RJS 09Apr99
					}
				}

				Update3d();												//RJS 19Nov96
			}
		}

		shootTimer -= viewobject->FrameTime();					//RJS 31May99
		if (shootTimer <= 0)
			shootTimer = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillEngine
//Author		Robert Slater
//Date			Mon 1 Jul 1996
//
//Description	Informs the Sound code that the engine is damaged
//
//Inputs		Damage level (0 - 16)
//				0 is no damage
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::KillEngine(ClassPtr	classtype, int	dlevel)
{
	if (dlevel == damagelevel)
		return;

	damagelevel = dlevel;

	if (damagelevel > 0)
	{
		if (damagelevel > 16)
			damagelevel = 16;

		EngineSound.Dying = TRUE;
	}
	else
 		EngineSound.Dying = FALSE;								//RJS 21Oct97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartSequence
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Hard starts a sequence from scratch	
//
//Inputs		Sequence number, fade time, and fade volume		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StartSequence(FileNum	thefile, int	sequenceno, SLong	fadeval, SLong	vol)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartSeqEffect
//Author		Robert Slater
//Date			Thu 26 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::StartSeqEffect(TuneStrucP	TunePtr,SLong	vol,SLong fadeval)
{
	return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StartSeqMain
//Author		Robert Slater
//Date			Thu 26 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::StartSeqMain(TuneStrucP	TunePtr, SLong	vol,SLong fadeval)
{
	int		lasttrack = request.CurrentTrack;

	request.CurrentTrack = ((Mood+128) * 9)/255;
	if (	((request.activated & INT_STOPSEQUENCE)==0)				//RJS 18Jun99
		&& !request.killnow)										//RJS 18Jun99
	{
		Bool	doInt = TRUE;
//DeadCode RJS 20Oct00 		int		tuneno = 1;

		SLong	volmoodscale = Mood;
		if (volmoodscale < 0)	volmoodscale = -volmoodscale;

		//16 units of volume difference between neutral and peaks
		volmoodscale = (128 - volmoodscale) << 4;
		volmoodscale >>= 7;
		vol -= volmoodscale;
		if (vol < 0)	vol = 0;

		request.activated = INT_NULL;								//RJS 18Jun99
		request.NewVolume = vol;									//RJS 06May99
		request.NewFade = fadeval;									//RJS 06May99


		if (!incombat)										
			doInt = StartMain(request.NewVolume);					//RJS 18Jun99
		else												
		{
			if (lasttrack == request.CurrentTrack)				//RJS 30Jun98
				doInt = FALSE;							
		}													

		if (incombat)										
		{
			if (doInt)
				request.activated |= INT_FADER;
		}

		if (doInt)
			request.activated |= INT_ON;

		return (doInt);
	}

	return (FALSE);
}


Bool	Sound::StartSeqIndependent(TuneStrucP	TunePtr, SLong	vol,SLong fadeval)
{
	Bool	doInt = TRUE;

	request.activated = INT_NULL;								//RJS 18Jun99
	request.NewVolume = vol;									//RJS 06May99
	request.NewFade = fadeval;									//RJS 06May99

 	if (mdi->Playing())
  	{
 		//only interrupt if this is a priority stand-alone piece...
 		if (TunePtr->ttype==T_independent_pri)
 		{
 			if (!request.alonetuneno)
 			{
 				request.alonetuneno = TunePtr;
 				request.activated |= INT_STOPSEQUENCE;			//RJS 18Jun99
 
 				FadeAll(500);
 			}
 			else
 			{
 				if (request.alonetuneno != TunePtr)
 				{
 					request.alonetuneno = TunePtr;
 					request.activated |= INT_STOPSEQUENCE;			//RJS 18Jun99
 
 					FadeAll(500);
 				}
 				else
 					doInt = FALSE;		
 			}
 		}
 		else
 			doInt = FALSE;
  	}
  	else
  	{
 		if (request.alonetuneno != TunePtr)
 		{
 			request.alonetuneno = TunePtr;
 			request.killnow = TRUE;
 
  			FadeAll(500);
 		}
  	}

	return(doInt);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceAudible
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Essentially a track volume fader;
//				Adjusts the volume of the specified sequence	
//
//Inputs		Tune, Sequence, fade time, fade volume and stomp request
//				If stomp is FALSE,
//					a request is placed to fade in/out at an appropriate moment.
//				otherwise
//					adjust volume regardless.		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SequenceAudible(FileNum	thefile, SLong	vol, SLong	fadeval)
{
	TuneStrucP	TunePtr = LoadTune(thefile);					//RJS 26Feb98
	if (TunePtr)												//RJS 26Feb98
	{
		Bool	dochange = FALSE;									//RJS 26Feb98

		ClipVolume(vol);								//RJS 14Sep00

		ULong	oldstate = request.activated;						//RJS 18jUN99


		switch (TunePtr->ttype)									//RJS 26Feb98
		{
			case T_main:
				dochange = StartSeqMain(TunePtr,vol,fadeval);
				break;
			case T_independent:
			case T_independent_pri:
				dochange = StartSeqIndependent(TunePtr,vol,fadeval);
				break;
		}														//RJS 26Feb98

		if (dochange)												//RJS 06Jan97
		{
			request.musictimeout = MUSIC_TIMEOUT;					//RJS 18Jun99
			request.forcestop = 0;
		}
		else														//RJS 06Jan97
			request.activated = oldstate;							//RJS 06Jan97
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceAudible
//Author		Robert Slater
//Date			Thu 29 Aug 1996
//
//Description	For mood settings
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SequenceAudible(MoodSetting	 setMood,SLong vol,SLong fadeval)
{
	Mood = setMood;
	SequenceAudible(FIL_MUSIC_MAIN,vol,fadeval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceAudible
//Author		Robert Slater
//Date			Wed 3 Feb 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SequenceAudible(MoodDelta	 deltaMood,SLong vol,SLong fadeval)
{
	Mood += deltaMood;
	SequenceAudible(FIL_MUSIC_MAIN,vol,fadeval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopSequence
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Stops a sequence from playing	
//
//Inputs		The file, Sequence no
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StopSequence(FileNum	thefile, int	sequenceno)
{
	HSEQUENCE	seqhandle;
	int			tuneno;

	tuneno = GetIndex(thefile);

	if (Save_Data.vol.music == 0)
		return;

	if (tune[tuneno].blockptr == NULL)
		return;

	if (!SequenceInRange(&tune[tuneno],sequenceno))
		return;

	if (request.activated)
		return;

	// Place a request if we do not want an immediate reaction

	request.activated |= INT_STOPSEQUENCE;						//RJS 18Jun99

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopMusic
//Author		Robert Slater
//Date			Thu 22 Aug 1996
//
//Description	Stops all the midi music if any is playing
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StopMusic()
{
	int			tuneno, seqno;

	if ((Save_Data.vol.music != 0) && (musicstopped==FALSE))	//RJS 25Jun98
	{
 		request.activated = INT_NULL;

		if (mdi->Playing())
			mdi->Stop();
	}

	musicstopped = TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FadeAll
//Author		Robert Slater
//Date			Fri 30 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	Sound::FadeAll(SLong fadeval)
{
	bool	somethingplaying = false;
	if (Save_Data.vol.music != 0)								//RJS 25Jun98
	{
		if (mdi->Playing())
 		{
 			somethingplaying = true;

			mdi->SetVolume(0,fadeval);
		}
	}

	return somethingplaying;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResumeMusic
//Author		Robert Slater
//Date			Thu 22 Aug 1996
//
//Description	Resumes all stopped midi music
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ResumeMusic()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceMute
//Author		Robert Slater
//Date			Fri 23 Feb 1996
//
//Description	Fade out sequence	
//
//Inputs		The sequence no, the fade time, a stomp request		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SequenceMute(FileNum	thefile, int	sequenceno, SLong	fadeval)
{
	SequenceAudible(thefile,0,fadeval);							//RJS 29Aug96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		reporterror
//Author		Robert Slater
//Date			Tue 27 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::reporterror(int	eno, char	*text)
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSample
//Author		Robert Slater
//Date			Tue 20 Feb 1996
//
//Description	Gets a sample from disk and stores its information	
//
//Inputs		Sample number and the filename
//
//Returns		TRUE if a success,
//				FALSE otherwise
//
//------------------------------------------------------------------------------
SampleRec*	Sound::LoadSample(FileNum	thefile, Bool inUI)
{
	int			spos = GetIndex(thefile);
	SampleRec*	SamplePtr = NULL;

	if ((Save_Data.vol.sfx || inUI) && SampleInRange(spos))
	{
		SamplePtr = &thesample[spos];

		if (!SamplePtr->blockptr)
		{
//			if (FILEMAN.fileloadedthisframe && !FILEMAN.loadednumberedfile(thefile))
//				SamplePtr = NULL;
//			else
			{
				char		header[10];
				char		*tmpptr;
				void		*tmpaddress;
				int			size;
				int			count;
				SLong		result = 1;
				fileblock	*theblock;
				RIFF		*header1;
				FMT			*header2;
				DATA		*header3;

				theblock = new fileblock (FileNum(thefile+directoryOffset));

				tmpaddress = getdata(theblock);
				size = getsize(theblock);

				// Make sure the sample in memory is secure...
				#ifdef __DOS__
				result = VMM_lock(tmpaddress, size);
				#endif

				if (!result)
					reporterror(3);
				else
				{
					SamplePtr->blockptr = theblock;
					SamplePtr->size = size;
					SamplePtr->wavheader = NULL;

					// Extract header id for file and decide if it is RAW

					tmpptr = (char*) tmpaddress;

					for (count = 0; count < 4; count ++)
						header[count] = *tmpptr++;
	
					header[4] = 0;

					if (	(strcmp(header,"RIFF") == 0)
						||	(strcmp(header,"Crea") == 0) )
					{
						header1 = (RIFF*) tmpaddress;
						header2 = (FMT*) header1->data;
		
						count = 0;											//RJS 24Nov96
						while (strnicmp(header2->FMT_string,"fmt ",4))
    					{
    						header2 = (FMT *) ((BYTE *) header2 +
			      					header2->chunk_size + 8 + (header2->chunk_size & 1));

							count++;										//RJS 24Nov96
							if (count >3)									//RJS 24Nov96
								break;										//RJS 24Nov96
    					}

						if (count > 3)
							SamplePtr->samplerate = CUR_SAMP_VAL;//RJS 14Jun00
						else
						{
							SamplePtr->wavheader = header2;
							SamplePtr->samplerate = header2->data.wf.nSamplesPerSec;
						}

						header3 = (DATA*) header1->data;
						while (strnicmp(header3->DATA_string,"data",4))
	  					{
    						header3 = (DATA *) ((char *) header3 +
			      					header3->chunk_size + 8 + (header3->chunk_size & 1));
    					}

						SamplePtr->datasize = header3->chunk_size;
						SamplePtr->dataptr = (void*) header3->data;
					}
					else													//RJS 16Oct97
						SamplePtr->samplerate = 44100;					//RJS 16Oct97

					SamplePtr->priority = spos * PRIORITYFACTOR;

					status.nosamples++;
				}
			}
		}
	}

	return(SamplePtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleRate
//Author		Robert Slater
//Date			Wed 19 Jun 1996
//
//Description	Returns the sampling rate of a particular sample file
//
//Inputs		the file
//
//Returns		the playback rate
//
//------------------------------------------------------------------------------
SLong	Sound::SampleRate(FileNum	thefile)
{
	return(thesample[GetIndex(thefile)].samplerate);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeHandler
//Author		Robert Slater
//Date			Tue 20 Feb 1996
//
//Description	Finds a free position in the sound queue.
//				If there is not one available then replace lowest priority sound
//
//Inputs		The priority of the sound handlers,
//				The sample number,
//				The world position pointer
//
//Returns		Queue index
//
//------------------------------------------------------------------------------
SQueuePtr	Sound::FindFreeHandler(SampleRec* SamplePtr, ItemBasePtr	sampleitem, SQueuePtr	&OldChannelPtr, UByte	looplength)
{
	int			count;
	SLong		lowest = 0;
	SLong		lowpos = -1;
	SQueuePtr	ChannelPtr;
	SQueuePtr	NewChannelPtr = NULL;

	OldChannelPtr = NULL;
	ChannelPtr = &soundqueue[freechannelstart];		
	for (count = freechannelstart; count < status.nohandlers; count ++)
	{
		if (!ChannelPtr->isRadio)								
		{
			UpdatePriority(ChannelPtr,count,lowest,lowpos);

			if (ChannelPtr->sampleindex)						
			{
				if (ChannelPtr->handler->Status() == SMP_DONE)
				{
					ChannelPtr->Clean();

					if (!NewChannelPtr && !OldChannelPtr)		
						NewChannelPtr = ChannelPtr;				
				}
				else
				{
					if (	(ChannelPtr->looping)				
						&&	(ChannelPtr->worlditem == sampleitem)
						&&	(ChannelPtr->sampleindex == SamplePtr)
						&&	!OldChannelPtr		)				  
					{											  
						OldChannelPtr = ChannelPtr;				  
						NewChannelPtr = NULL;

						ChannelPtr->handler->SetLooping(looplength);
					}
				}
			}
			else
			{
				if (!NewChannelPtr && !OldChannelPtr)			
					NewChannelPtr = ChannelPtr;					
			}
		}

		ChannelPtr++;											
	}

	// If there were no free slots, then grab the one with the lowest priority

	if (!NewChannelPtr && !OldChannelPtr)
	{
		if (SamplePtr->priority <= lowest)									//RJS 22Sep00
		{
			NewChannelPtr = &soundqueue[lowpos];

			NewChannelPtr->Clean();

			NewChannelPtr->handler->End();				
		}
	}

	return(NewChannelPtr);										
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeHandlerOnce
//Author		Robert Slater
//Date			Tue 19 Nov 1996
//
//Description	Same as above, but blocks the sample if already playing
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SQueuePtr	Sound::FindFreeHandlerOnce(SampleRec* SamplePtr, ItemBasePtr	sampleitem, SQueuePtr	&OldChannelPtr, int	stblock, int	endblock)
{
	int		count;
	SLong	lowest = 0;
	SLong	lowpos = -1;
	SQueuePtr	ChannelPtr;
	SQueuePtr	NewChannelPtr = NULL;
	SampleRec*	StBlockPtr = &thesample[stblock];
	SampleRec*	EndBlockPtr = &thesample[endblock];

	OldChannelPtr = NULL;	//RJS 29Jan99

	ChannelPtr = &soundqueue[freechannelstart];					
	for (count = freechannelstart; count < status.nohandlers; count ++)
	{
//DeadCode RJS 22Sep00 		ChannelPtr = &soundqueue[count];					
		if (!ChannelPtr->isRadio)							
		{
			UpdatePriority(ChannelPtr,count,lowest,lowpos);				//RJS 22Sep00

			if (ChannelPtr->sampleindex)					
			{
				if (ChannelPtr->handler->Status() == SMP_DONE)
				{
					ChannelPtr->Clean();								//RJS 22Sep00

					if (!NewChannelPtr && !OldChannelPtr)			
						NewChannelPtr = ChannelPtr;					
				}
				else
				{
					if (	(ChannelPtr->worlditem == sampleitem)	
						&&  (ChannelPtr->sampleindex > StBlockPtr)	
						&&	(ChannelPtr->sampleindex < EndBlockPtr)	
						&&	!OldChannelPtr	)						
					{												
						OldChannelPtr = ChannelPtr;					
					}												
				}
			}
			else
			{
				if (!NewChannelPtr && !OldChannelPtr)
					NewChannelPtr = ChannelPtr;	 
			}
		}

		ChannelPtr++;
	}

	// If there were no free slots, then grab the one with the lowest priority
	if (!NewChannelPtr && !OldChannelPtr)				
	{
		if (SamplePtr->priority <= lowest)									//RJS 22Sep00
		{
			NewChannelPtr = &soundqueue[lowpos];				

			NewChannelPtr->Clean();

			NewChannelPtr->handler->End();				
		}
	}

	return(NewChannelPtr);										//RJS 16Oct97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeRadioHandler
//Author		Robert Slater
//Date			Mon 1 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SQueuePtr	Sound::FindFreeRadioHandler()
{
	SQueuePtr	NewChannelPtr = NULL;
	if (soundqueue)														//RJS 29Sep00
	{
		int			count;
		SQueuePtr	ChannelPtr;
		SQueuePtr	OldChannelPtr = NULL;

		ChannelPtr = &soundqueue[channel_radiochatter];								//RJS 14Apr99
		if (ChannelPtr->sampleindex)								
		{
			if (ChannelPtr->handler->Status() == SMP_DONE)
			{
				ChannelPtr->Clean();

				if (!NewChannelPtr && !OldChannelPtr)		
					NewChannelPtr = ChannelPtr;			
			}
			else
			{
				if (ChannelPtr->isRadio)
				{
					OldChannelPtr = ChannelPtr;
					NewChannelPtr = NULL;
				}
			}
		}
		else
		{
			if (!NewChannelPtr && !OldChannelPtr)
				NewChannelPtr = ChannelPtr;			
		}
	}

	return(NewChannelPtr);							
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeHandlerUI
//Author		Robert Slater
//Date			Fri 12 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SQueuePtr	Sound::FindFreeHandlerUI(SampleRec* SamplePtr)
{
	int		count;
	SLong	lowest = 0;
	SLong	lowpos = -1;
	SQueuePtr	ChannelPtr;
	SQueuePtr	NewChannelPtr = NULL;
	SQueuePtr	OldChannelPtr = NULL;

	ChannelPtr = soundqueue;											//RJS 29Sep00
	for (count = 0; count < status.nohandlers; count ++)
	{
//DeadCode RJS 22Sep00 		ChannelPtr = &soundqueue[count];						
		if (!ChannelPtr->isRadio)								
		{
			UpdatePriority(ChannelPtr,count,lowest,lowpos);				//RJS 22Sep00

			if (ChannelPtr->sampleindex)
			{
				if (ChannelPtr->handler->Status() == SMP_DONE)
				{
					ChannelPtr->Clean();

					if (!NewChannelPtr && !OldChannelPtr)
						NewChannelPtr = ChannelPtr;
				}
				else
				{
					if (	(ChannelPtr->sampleindex == SamplePtr)
						&&	!OldChannelPtr	)						
					{												
						OldChannelPtr = ChannelPtr;
						NewChannelPtr = OldChannelPtr;

						ChannelPtr->handler->End();
						ChannelPtr->Clean();
					}												
				}
			}
			else
			{
				if (!NewChannelPtr && !OldChannelPtr)
					NewChannelPtr = ChannelPtr;
			}
		}

		ChannelPtr++;
	}

	// If there were no free slots, then grab the one with the lowest priority

	if (!NewChannelPtr && !OldChannelPtr)						
	{
		if (SamplePtr->priority <= lowest)									//RJS 22Sep00
		{
			NewChannelPtr = &soundqueue[lowpos];				

			NewChannelPtr->Clean();
			NewChannelPtr->handler->End();				
		}
	}

	return(NewChannelPtr);										
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeHandlerRestart
//Author		Robert Slater
//Date			Tue 13 Jun 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SQueuePtr	Sound::FindFreeHandlerRestart(SampleRec* SamplePtr, ItemBasePtr	sampleitem, int	stblock, int	endblock)
{
	int		count;
	SLong	lowest = 0;
	SLong	lowpos = -1;
	SQueuePtr	ChannelPtr;
	SQueuePtr	NewChannelPtr = NULL;
	SampleRec*	StBlockPtr = &thesample[stblock];
	SampleRec*	EndBlockPtr = &thesample[endblock];
	SQueuePtr	OldChannelPtr = NULL;	//RJS 29Jan99

	ChannelPtr = &soundqueue[freechannelstart];					
	for (count = freechannelstart; count < status.nohandlers; count ++)
	{
//DeadCode RJS 22Sep00 		ChannelPtr = &soundqueue[count];					
		if (!ChannelPtr->isRadio)							
		{
			UpdatePriority(ChannelPtr,count,lowest,lowpos);

			if (ChannelPtr->sampleindex)					
			{
				if (ChannelPtr->handler->Status() == SMP_DONE)
				{
					ChannelPtr->Clean();

					if (!NewChannelPtr && !OldChannelPtr)			
						NewChannelPtr = ChannelPtr;					

					ChannelPtr->sampleindex = NULL;
				}
				else
				{
					if (	(ChannelPtr->worlditem == sampleitem)	
						&&  (ChannelPtr->sampleindex > StBlockPtr)	
						&&	(ChannelPtr->sampleindex < EndBlockPtr)	
						&&	!OldChannelPtr	)						
					{												
						OldChannelPtr = ChannelPtr;
						OldChannelPtr->Clean();
						OldChannelPtr->handler->End();
					}												
				}
			}
			else
			{
				if (!NewChannelPtr && !OldChannelPtr)
					NewChannelPtr = ChannelPtr;	 
			}
		}

		ChannelPtr++;
	}

	// If there were no free slots, then grab the one with the lowest priority
	if (!NewChannelPtr && !OldChannelPtr)				
	{
		if (SamplePtr->priority <= lowest)									//RJS 22Sep00
		{
			NewChannelPtr = &soundqueue[lowpos];				

			NewChannelPtr->Clean();

			NewChannelPtr->handler->End();				
		}
	}
	else
	{
		if (OldChannelPtr)										//RJS 13Jun00
			NewChannelPtr = OldChannelPtr;
	}

	return(NewChannelPtr);										//RJS 16Oct97
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipVolume
//Author		Robert Slater
//Date			Thu 7 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	Sound::ClipVolume(SLong	maxvol, SLong	vol)
{
	if (vol < 0)
		vol = 0;  			// Too quiet

	if (vol > maxvol)
		vol = maxvol;			// Too loud

	return(vol);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipPan
//Author		Robert Slater
//Date			Thu 7 Mar 1996
//
//Description	
//
//Inputs		+/-32K clipped to +/-10K then shifted to +/- 64
//
//Returns		0..127
//
//------------------------------------------------------------------------------
SLong	Sound::ClipPan(SLong	pan)
{

	// Clip the pan...

	if (pan < -16383)
		pan = -16383;		// Hard left

	if (pan > 16383)
		pan = 16383;			// Hard right

	pan >>= 5;			// +- 511										//RJS 14Sep00
//Dead	pan = (pan>>8) + 64;			// Scale and shift to acceptible range

	return(pan);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SoundInWorld
//Author		Robert Slater
//Date			Tue 25 Jun 1996
//
//Description	Calculates the pan angle of the sound relative to view point,
//				And the volume of the sound :
//
//										 2
//						vol = MaxVol * uD			uD = Unit Distance (20000)
//									   ---			D  = Distance from source
//									     2
//									    D
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SoundInWorld(const COORDS3D& WPos, SLong	&vol, SLong& hdg)		//RJS 12Jan00
{
	if (View_Point)
	{
		// Shouldn't get overflow anymore...
		float	dx = Float(WPos.X - eyeWorld.X);						//RJS 15Sep00
		float	dy = Float(WPos.Y - eyeWorld.Y);						//RJS 15Sep00
		float	dz = Float(WPos.Z - eyeWorld.Z);						//RJS 15Sep00
		float	cmDistanceSquared = dx*dx+dy*dy+dz*dz;					//RJS 16Sep00
		double	mDistanceSquared = cmDistanceSquared * 0.0001;			//RJS 16Sep00

		if (mDistanceSquared > 4.)										//RJS 16Sep00
		{
 			SWord	boffang = Math_Lib.arctan(dx,dz);
 			boffang += eyeHdg;
 
 			hdg = boffang;
		}
		else
			hdg = 0;

// E.g.	vol = 32767		distance = 0m		resultant vol = 511	(max)
//		vol = 32767		distance = 4521m	resultant vol = 1	(min)

		double	fvol = double(vol);

		if (mDistanceSquared > VOL_DISTUNITSQRD)
		{
			fvol *= VOL_DISTANCESQUAREDOVERVOLSCALE;
			fvol /= mDistanceSquared;

			vol = SLong(fastMath.DoubleToULong(fvol));						//RJS 16Sep00
		}
		else
			vol >>= VOL_SCALE_SHIFT;									//RJS 26Sep00

		RowanToPan(hdg);
	}
	else
	{
		hdg = 0;
		vol >>= VOL_SCALE_SHIFT;										//RJS 14Sep00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Update3d
//Author		Robert Slater
//Date			Thu 27 Jun 1996
//
//Description	update the 3d sound world if any sound is playing
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::Update3d()
{
	int		count;
	SLong	pan;
	SLong	vol;
	SampleRec*	thissamp;										
	Bool	isused = FALSE;										
	ULong	TimeDiff;											
//DeadCode RJS 12Jan00 	SLong	distance;											
	SQueuePtr	ChannelPtr = soundqueue;						
	float		vx,vy,vz;
	mobileitem*	mitem;
	Coords3D*	pSoundPos;												//RJS 15Sep00

	if (delindex < (MAXSAMPLES_LOADED-1))						
		delindex++;												
	else														
		delindex = 0;											

	for (count = 0; count < status.nohandlers; count++)			
	{
		thissamp = ChannelPtr->sampleindex;
		if (count >= freechannelstart)							
		{
			if (thissamp)		// this channel is occupied
			{
				if (ChannelPtr->handler->Status() == SMP_PLAYING)
				{
					if (ChannelPtr->GameSound)
					{
						vol = ChannelPtr->playingvolume;
						if (ChannelPtr->worlditem)
							pSoundPos = &ChannelPtr->worlditem->World;
						else
							pSoundPos = &ChannelPtr->StaticPos;

						SoundInWorld(*pSoundPos,vol,pan);

						if (Save_Data.hardwareconfig[HW_3DSOUND])
						{
// 3D Sound
							if (!vol)										//RJS 5Sep00
								ChannelPtr->playingpriority+=PRIORITYFACTOR;//RJS 5Sep00

							vx = vy = vz = 0.f;								//RJS 15Sep00

							vol = ChannelPtr->playingvolume;				//RJS 5Sep00
							if (ChannelPtr->worlditem)
							{
#ifndef	_NOVELOCITY_
								if (ChannelPtr->worlditem->Status.size >= MOBILESIZE)
								{
									mitem = MobileItemPtr(ChannelPtr->worlditem);
									vx = float(mitem->vel_x)*VEL_SCALE;
									vy = float(mitem->vel_y)*VEL_SCALE;
									vz = float(mitem->vel_z)*VEL_SCALE;
								}
#endif
							}

							ChannelPtr->handler->Set3DSource(SubjectStruc(	*pSoundPos,
																			vx, vy, vz,
																			vol >> VOL_SCALE_SHIFT,	//RJS 14Sep00
																			MIN_DISTANCE,
																			MAX_DISTANCE	)	);
						}
						else
						{
// Stereo Sound
							if (vol)				
							{
								pan = ClipPan(pan);							//RJS 5Sep00

								ClipVolume(vol);							//RJS 14Sep00

								ChannelPtr->handler->SetPan(pan);
				    			ChannelPtr->handler->SetVolume(vol);
							}
							else
								ChannelPtr->playingpriority+=PRIORITYFACTOR;	
						}
					}
					else
					{
// These sounds are static (or looped piloted gun sounds)
						if (Save_Data.hardwareconfig[HW_3DSOUND])
						{
							vol = ChannelPtr->playingvolume;				//RJS 5Sep00

							vx = vy = vz = 0.f;								//RJS 15Sep00
							if (ChannelPtr->worlditem)
							{
								pSoundPos = &ChannelPtr->worlditem->World;
#ifndef	_NOVELOCITY_
								if (ChannelPtr->worlditem->Status.size >= MOBILESIZE)
								{
									mitem = MobileItemPtr(ChannelPtr->worlditem);
									vx = float(mitem->vel_x)*VEL_SCALE;
									vy = float(mitem->vel_y)*VEL_SCALE;
									vz = float(mitem->vel_z)*VEL_SCALE;
								}
#endif
							}
							else
							{
								pSoundPos = &eyeWorld;
								vx = float(eyeVelocity.X)*VEL_SCALE;
								vy = float(eyeVelocity.Y)*VEL_SCALE;
								vz = float(eyeVelocity.Z)*VEL_SCALE;
							}

							ChannelPtr->handler->Set3DSource(SubjectStruc(	*pSoundPos,
																			vx, vy, vz,
																			vol >> VOL_SCALE_SHIFT,	//RJS 14Sep00
																			MIN_DISTANCE,
																			MAX_DISTANCE	)	);
						}
					}
				}
				else
				{
// This sound has finished playing
					thissamp = NULL;								
					ChannelPtr->sampleindex = NULL;					
				}
			}
		}
		else
		{
			if (ChannelPtr->handler->Status() == SMP_PLAYING)
				ChannelPtr->handler->Set3DSource(SubjectStruc(	eyeWorld,
																float(eyeVelocity.X)*VEL_SCALE,
																float(eyeVelocity.Y)*VEL_SCALE,
																float(eyeVelocity.Z)*VEL_SCALE,
																0,
																MIN_DISTANCE,
																MAX_DISTANCE	)	);
		}

		if (thissamp == &thesample[delindex])					
			isused = TRUE;										

		ChannelPtr++;											
	}

	if (!isused)												
		DeleteSample(delindex);									
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HaltItemSound
//Author		Robert Slater
//Date			Thu 11 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::HaltItemSound(ItemBasePtr	sampleitem)
{
	int	count;
	SQueuePtr	ChannelPtr;										//RJS 16Oct97

	if ((Save_Data.vol.sfx != 0) && sampleitem)					//RJS 19Nov96
		for (count = 1; count < status.nohandlers; count++)
		{
			ChannelPtr = &soundqueue[count];
			if ((ChannelPtr->worlditem == sampleitem) && ChannelPtr->GameSound)//RJS 16Oct97
			{
				ChannelPtr->StaticPos = ChannelPtr->worlditem->World;
				ChannelPtr->worlditem = NULL;
				ChannelPtr->looping = FALSE;
			}
		}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlaySettings
//Author		Robert Slater
//Date			Thu 7 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlaySettings(SQueuePtr	ChannelPtr, SLong	vol, SLong	pan)
{
	SetPriority(ChannelPtr,vol);										//RJS 22Sep00

	if (Save_Data.hardwareconfig[HW_3DSOUND])
	{
		ChannelPtr->handler->SetVolume(vol);
		ChannelPtr->handler->Set3DSource(*theSubject);
	}
	else
	{
		pan = ClipPan(pan);

		ChannelPtr->handler->SetPan(pan);
		ChannelPtr->handler->SetVolume(vol);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpSample
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Initialises a sample for a handler and plays it	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetUpSample(SQueuePtr ChannelPtr, SampleRec* SamplePtr, SLong	maxvol, SLong	vol, SLong	pan, ItemBasePtr	sampleitem, const float startscale)	//RJS 13Sep00
{
	HSAMPLE		theHandler;
	UByte		isloop = FALSE;

	if (	(SamplePtr > &thesample[GetIndex(FIL_SFX_LOOP_FX_START)])
		&&	(SamplePtr < &thesample[GetIndex(FIL_SFX_LOOP_FX_END)])	)
		isloop = TRUE;

	theHandler = ChannelPtr->handler;

	ChannelPtr->sampleindex = SamplePtr;
	ChannelPtr->playingvolume = maxvol;							
	ChannelPtr->worlditem = sampleitem;							
	ChannelPtr->GameSound = TRUE;								
	ChannelPtr->looping = isloop;								
	ChannelPtr->highPriority = false;

	if (!sampleitem)											
 		ChannelPtr->GameSound = FALSE;

	void*	sample_ptr = SamplePtr->dataptr;
	int		sample_length;

	if (startscale > 0.f)
	{
		int	initlength = SamplePtr->datasize;
		int	onzlength = initlength >> 1;

		initlength -= (initlength - (onzlength<<1));

		sample_length = int(fastMath.DoubleToULong(double(1.f-startscale)*double(initlength)));//RJS 13Sep00
		
		onzlength = sample_length >> 1;
		sample_length -= (sample_length - (onzlength<<1));

		sample_ptr = (void*)(UByteP(sample_ptr) + (initlength - sample_length));
	}
	else
		sample_length = SamplePtr->datasize;
	
	if (theHandler->LoadBuffer(SamplePtr->wavheader->data,sample_ptr,sample_length))	//RJS 13Sep00
	{
		PlaySettings(ChannelPtr,vol,pan);								//RJS 22Sep00
																
		if ((ChannelPtr != EngineSound.ChanPtr) || EngineSound.Dying)
		{														
			if (isloop)
				theHandler->SetLooping(2);
		}														
 	}															
 	else														
 		reporterror(2);											
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlaySample
//Author		Robert Slater
//Date			Tue 25 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void 	Sound::PlaySample(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol)
{
#ifndef	_NOSOUNDIN3D_
	SQueuePtr	ChannelPtr;										
	SQueuePtr	OldChannelPtr;									
	SLong	thevol;												
	int		thepan;												
//DeadCode RJS 12Jan00 	SLong	distance;
	SampleRec*	SamplePtr;

	if (allowedsamples)											
	{
		SamplePtr = LoadSample(thefile);
		if (SamplePtr)
		{
			thevol = (SamplePtr->samplevolume * vol) >> 7;		
			vol = thevol;										

			thepan = SoundInWorld(ItemPtr(sampleitem),thevol);			//RJS 12Jan00

			if (thevol)
			{
				ChannelPtr = FindFreeHandler(SamplePtr,sampleitem,OldChannelPtr);
				if (ChannelPtr)											
				{
					allowedsamples--;

					SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem);

					ChannelPtr->handler->Play();
				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlaySample
//Author		Robert Slater
//Date			Tue 20 Feb 1996
//
//Description	Soft start a sample; finds a suitable slot in the sound
//				handler queue then starts it.
//
//Inputs		The sample number, its volume, its stereo pan (0 is central)		
//
//Returns		The sample that has been played.
//				-1 if it has failed
//
//------------------------------------------------------------------------------
void 	Sound::PlaySample(FileNum	thefile, SLong	vol, SLong	pan)
{
#ifndef	_NOSOUNDIN3D_
	SQueuePtr	ChannelPtr;										
	SQueuePtr	OldChannelPtr;									
	SampleRec*	SamplePtr;

	if (allowedsamples)											
	{
		SamplePtr = LoadSample(thefile);
		if (SamplePtr)
		{
			SLong	useVol = (SamplePtr->samplevolume * vol) >> 7;			//RJS 16Oct00

			SoundInWorld(ItemPtr(NULL),useVol);									//RJS 12Jun00

			ChannelPtr = FindFreeHandler(SamplePtr,NULL,OldChannelPtr);
			if (ChannelPtr)											   
			{
				allowedsamples--;									   
				SetUpSample(ChannelPtr,SamplePtr,vol,useVol,pan,NULL);

				ChannelPtr->handler->Play();
			}
		}
	}
#endif
}
		
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OverrideSample
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Hard start a sample on a known handler
//
//Inputs		Sound queue index, sample index, volume, pan and frequency
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::OverrideSample(SQueuePtr ChannelPtr, FileNum	thefile, SLong	vol, SLong	pan,SLong	newfreq)
{
	SampleRec*	SamplePtr = LoadSample(thefile);

	if (SamplePtr && ChannelPtr)									
	{
		//Volume is virtual (32k)					
		SLong	thevol = vol;											//RJS 12Jun00
		HSAMPLE	theHandle = ChannelPtr->handler;

		if (theHandle->Status() == SMP_PLAYING)
			theHandle->Stop();

		SoundInWorld(ItemPtr(NULL),thevol);

		SetUpSample(ChannelPtr,SamplePtr,vol,thevol,pan,NULL);		
	
		if (newfreq > -1)
		{
			theHandle->SetFrequency(newfreq);
			theHandle->SetLooping(0);
		}

		theHandle->Play();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopSample
//Author		Robert Slater
//Date			Mon 15 Jul 1996
//
//Description	Stops a sample in the sample queue, depending on which item
//				had recently requested it.
//
//Inputs		The sample file name,
//				The item pointer.
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StopSample(FileNum	thefile, ItemBasePtr	sampleitem)
{
	int	count;
	int	spos = GetIndex(thefile);
	int	lastpos = GetIndex(FIL_SFX_LASTSOUND);
	SQueuePtr	ChannelPtr = soundqueue;						

	if ((spos >= 0) && (spos < lastpos))						
	{
		SampleRec*	SamplePtr = &thesample[spos];
		if (sampleitem)
		{	
			for (count = 0; count < status.nohandlers; count++)	
			{													
				if (	(ChannelPtr->sampleindex == SamplePtr)	
					&&	(ChannelPtr->worlditem == sampleitem) )	
					HardStop(ChannelPtr);						
																
				ChannelPtr++;									
			}													
		}
		else
		{
			for (count = 0; count < status.nohandlers; count++)	
			{													
				if (ChannelPtr->sampleindex == SamplePtr)		
					HardStop(ChannelPtr);						
																
				ChannelPtr++;									
			}													
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StillPlaying
//Author		Robert Slater
//Date			Tue 13 Jun 2000
//
//Description	Finds a sample
//
//Inputs		
//
//Returns		
//
//------------------------------------------------------------------------------
bool	Sound::SamplePlaying(FileNum	theFile)
{
	bool		retval = false;

	if (theFile != FIL_NULL)
	{
		SQueuePtr	ChannelPtr = soundqueue;
		SampleRec*	SamplePtr = &thesample[GetIndex(theFile)];

		for (int count = 0; count < status.nohandlers; count++)	
		{													
			if (	(ChannelPtr->sampleindex == SamplePtr)	
				&&	(ChannelPtr->handler->Status() == SMP_PLAYING)	)
			{
				retval = true;
				break;
			}
			
			ChannelPtr++;													
		}
	}

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HardStop
//Author		Robert Slater
//Date			Fri 8 Mar 1996
//
//Description	Hard stops the sample from playing
//
//Inputs		Position in sample handler queue
//
//Returns		
//
//------------------------------------------------------------------------------
void	Sound::HardStop(SQueuePtr	ChannelPtr)
{
	if (dig)													
	{
 		if (ChannelPtr->handler->Status() == SMP_PLAYING)
			ChannelPtr->handler->End();				

		if (ChannelPtr == EngineSound.ChanPtr)					
		{
			EngineSound.Playing = FALSE;						
			if (EngineSound.SubChanPtr->handler->Status() == SMP_PLAYING)
				EngineSound.SubChanPtr->handler->End();	
		}

		ChannelPtr->Clean();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateEngine
//Author		Robert Slater
//Date			Tue 3 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::UpdateEngine()
{
	if (EngineSound.isInitialised)								
	{
		if (EngineSound.CurrentFile != FIL_NULL)
		{
			SLong		NewFreq = EngineSound.Freq;						
			SLong		SubFreq = EngineSound.SubHarmonicFreq;						

			if (thesample[GetIndex(EngineSound.CurrentFile)].blockptr && !EngineSound.Changed)
			{
				SLong	thewindvol = EngineSound.WindVolume >> VOL_SCALE_SHIFT;	//RJS 14Sep00
				SLong	themainvol = EngineSound.SubHarmonicVolume >> VOL_SCALE_SHIFT;	//RJS 14Sep00
				SLong	therumblevol = EngineSound.RumbleVolume >> VOL_SCALE_SHIFT;	//RJS 14Sep00
//DeadCode RJS 15Sep00 				float	vel_x = float(eyeVelocity.X)*VEL_SCALE;
//DeadCode RJS 15Sep00 				float	vel_y = float(eyeVelocity.Y)*VEL_SCALE;
//DeadCode RJS 15Sep00 				float	vel_z = float(eyeVelocity.Z)*VEL_SCALE;

				if (EngineSound.Playing)								
				{
					if (EngineSound.IsJet)
						EngineSound.SubChanPtr->handler->SetFrequency(NewFreq);
					else
					{
						EngineSound.SubChanPtr->handler->SetFrequency(SubFreq);
						EngineSound.ChanPtr->handler->SetFrequency(NewFreq);
					}

					ClipVolume(therumblevol);							//RJS 14Sep00
					ClipVolume(themainvol);								//RJS 14Sep00

					EngineSound.SubChanPtr->handler->SetVolume(themainvol);
//DeadCode RJS 15Sep00 					EngineSound.SubChanPtr->handler->Set3DSource(SubjectStruc(	eyeWorld,
//DeadCode RJS 15Sep00 																				vel_x, vel_y, vel_z,
//DeadCode RJS 15Sep00 																				themainvol,
//DeadCode RJS 15Sep00 																				1000,
//DeadCode RJS 15Sep00 																				5000000	)	);
																				
					EngineSound.ChanPtr->handler->SetVolume(therumblevol);
//DeadCode RJS 15Sep00 					EngineSound.ChanPtr->handler->Set3DSource(SubjectStruc(	eyeWorld,
//DeadCode RJS 15Sep00 																			vel_x, vel_y, vel_z,
//DeadCode RJS 15Sep00 																			therumblevol,
//DeadCode RJS 15Sep00 																			1000,
//DeadCode RJS 15Sep00 																			5000000	)	);
				}
				else
				{
					ClipVolume(thewindvol);

					EngineSound.ChanPtr->handler->SetVolume(thewindvol);
//DeadCode RJS 15Sep00 					EngineSound.ChanPtr->handler->Set3DSource(SubjectStruc(	eyeWorld,
//DeadCode RJS 15Sep00 																			vel_x, vel_y, vel_z,
//DeadCode RJS 15Sep00 																			thewindvol,
//DeadCode RJS 15Sep00 																			1000,
//DeadCode RJS 15Sep00 																			5000000	)	);
				}
			}
			else
			{
				if (EngineSound.Playing)								
				{
					if (EngineSound.IsJet)
					{
						OverrideSample(	EngineSound.ChanPtr,				
										EngineSound.CurrentFile,			
										EngineSound.RumbleVolume,			
										0,									
										CUR_SAMP_VAL);			//RJS 14Jun00

						OverrideSample(	EngineSound.SubChanPtr,
										EngineSound.CurrentSubFile,
										EngineSound.SubHarmonicVolume,
										0,
										NewFreq);
					}
					else
					{
						OverrideSample(	EngineSound.ChanPtr,				
										EngineSound.CurrentFile,	
										EngineSound.RumbleVolume,
										0,					
										NewFreq);
						
						OverrideSample(	EngineSound.SubChanPtr,
										EngineSound.CurrentSubFile,
										EngineSound.SubHarmonicVolume,
										0,
										SubFreq);						//RJS 13Jun00
					
						//Boost sound too?
					}
				}
				else							
					OverrideSample(	EngineSound.ChanPtr,				
									EngineSound.CurrentFile,			
									EngineSound.WindVolume,				
									0,									
									CUR_SAMP_VAL);				//RJS 14Jun00
			}
		}
	}
	EngineSound.Changed = FALSE;					
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayEngine
//Author		Robert Slater
//Date			Tue 3 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayEngine(AirStrucPtr	ac, EngineInfo&	leftengine,EngineInfo&	rightengine)
{
#ifndef	_NOSOUNDIN3D_
	if (Save_Data.vol.sfx && EngineSound.Volume)					
	{
//DeadCode RJS 25Oct00 		SLong	revgap;
//DeadCode RJS 25Oct00 		SLong	revlimit;
		SLong	Maxvol = EngineSound.Volume;						
		SLong	RumbleVol;
		SLong	wvol;												
		FileNum	newSound,newSound2;
		ClassPtr	classtype = ac->classtype;
// Take average rpm for the time being...
		SLong		rpm = (leftengine.rpm_engine + rightengine.rpm_engine)>>1;
		SLong		thrustp = (leftengine.power + rightengine.power)>>1;
		SLong		CockpitNobble = (leftengine.cockpitnobble + rightengine.cockpitnobble)>>1;
		SLong		rpm_max = classtype->maxrpm;
		SLong		rpm_min = classtype->minrpm;
		SLong		vel = leftengine.velocity / 10000;		//measure vel in ms

// Scale wind vol to 400 ms max
		EngineSound.WindVolume = (vel * Maxvol)/400;					//RJS 9Jun00

		EngineSound.isInitialised = TRUE;
		EngineSound.StarterMotorFile = FIL_NULL;
		EngineSound.engineStarted = true;

		if (CockpitView)
		{
			if (CockpitNobble)
			{
				// vel is in 1ms * 10000
				// max damage is 255...
				SLong	wVx,wVy,wVz;
				SLong	wTotVel255units;
				float	fTotVel;
				if (MissManCampSky().GetWind(ac->World.Y,wVx,wVy,wVz))
				{
					float	fwVx = float(wVx - ac->vel_x);	// high if travelling in opposite directions
					float	fwVz = float(wVz - ac->vel_z);

					fTotVel = fastMath.FastSqrt(fwVx*fwVx + fwVz*fwVz);
				}
				else
					fTotVel = ac->vel_;

				fTotVel = (fTotVel * 255.) / float(ac->classtype->maxdivevel);

				fastMath.FloatToInt(&wTotVel255units,fTotVel);

				wvol = (Maxvol * CockpitNobble * wTotVel255units)/(255*255);			
				if (wvol > Maxvol)
					wvol = Maxvol;
			}
			else
				wvol = 0;

			EngineSound.CockpitWind = wvol;
			if (CockpitNobble < 192)
				EngineSound.InCockpit = TRUE;
			else
				EngineSound.InCockpit = FALSE;
		}
		else
		{
			EngineSound.InCockpit = FALSE;
			if (EngineSound.CockpitWind)
				StopSample(FIL_SFX_WIND_COCKPIT_LOOP);

			EngineSound.CockpitWind = 0;
		}

		if (EngineSound.Dying == FALSE)
		{
			EngineSound.Playing = TRUE;							

			if (!EngineSound.InCockpit)							
			{
				newSound = FileNum(classtype->enginesnd + 1);
				newSound2 = FileNum(classtype->enginesubsnd + 1);
			}
			else												
			{
				newSound = classtype->enginesnd;
				newSound2 = classtype->enginesubsnd;				
			}

			if (leftengine.rpm_starter)
			{
				EngineSound.StarterMotorFile = FileNum(classtype->enginestartsnd + 1);
				newSound2 = EngineSound.StarterMotorFile;
			}

			if (	(newSound != EngineSound.CurrentFile)
				||	(newSound2 != EngineSound.CurrentSubFile)	)
				EngineSound.Changed = TRUE;						

			if (thrustp < 0)	thrustp = 0;					
			if (thrustp >= 255)	thrustp = 256;					

//DeadCode RJS 13Jun00 			if (rpm < rpm_min)
//DeadCode RJS 13Jun00 				EngineSound.engineStarted = false;

			if (EngineSound.IsJet)
			{
				rpm -= 3975;
				EngineSound.Freq = CUR_SAMP_VAL + (5000.*float(rpm)*sampRateScale/3975);	//RJS 12Sep00

				RumbleVol = Maxvol - (Maxvol/16);
				EngineSound.SubHarmonicVolume = Maxvol / 4;				
				EngineSound.CurrentSubFile = (FileNum) (newSound + 2);	


				EngineSound.RumbleVolume = (RumbleVol * thrustp)>>8;	
			}
			else
			{
// MIN_SAMP_VAL frequency = roughly half max rpm (+- 5000 hz sample variance)
				SLong	newfreq;
				SLong	avrpm = (rpm_max+rpm_min)>>1;
				SLong	rumblevol = (Maxvol*3)>>2;//(Maxvol<<1)/3;//Maxvol>>1;			//RJS 13Sep00
				SLong	mainvol = Maxvol>>1;//Maxvol/3;//Maxvol>>1;					//RJS 13Sep00
				SLong	rpm_thresh = rpm_min>>1;

				newfreq = (float(rpm-avrpm)*5000.*sampRateScale)/(rpm_max-rpm_min);	//RJS 12Sep00
				newfreq += CUR_SAMP_VAL;

// High-end engine sound

				EngineSound.SubHarmonicFreq = newfreq;
				if (rpm < rpm_min)
				{
					EngineSound.engineStarted = false;
					EngineSound.SubHarmonicVolume = (mainvol*rpm)/rpm_min;
//DeadCode RJS 13Sep00 					rumblevol = (rumblevol*rpm)/rpm_min;
				}
				else
					EngineSound.SubHarmonicVolume = mainvol;
// Power sound

				if (leftengine.rpm_starter)
				{
// The Engine-Startup sound in on the sub-harmonic channel...
					SLong	theVol =  thesample[GetIndex(newSound2)].samplevolume;
					SLong	newVol = (theVol * leftengine.rpm_starter)/rpm_thresh;

					if (newVol > theVol)
						newVol = theVol;

					if (leftengine.rpm_starter > rpm_min)
						EngineSound.SubHarmonicFreq = CUR_SAMP_VAL + (3000.*sampRateScale);//RJS 14Jun00
					else
						EngineSound.SubHarmonicFreq = CUR_SAMP_VAL + ((float(leftengine.rpm_starter)*3000.*sampRateScale)/rpm_min);

					EngineSound.SubHarmonicVolume = newVol;
					EngineSound.RumbleVolume = 0;
				}
				else
				{
					EngineSound.Freq = newfreq;
					EngineSound.RumbleVolume = (rumblevol*thrustp)>>8;
				}

				EngineSound.CurrentSubFile = newSound2;
			}

			EngineSound.CurrentFile = newSound;							

			if (diveBrakesOn)											//RJS 25Oct00
			{
				if (vel > JERICO_VEL_MIN)
				{
					SLong	jericoVel = vel - JERICO_VEL_MIN;

					if (jericoVel < JERICO_SCALE)
						EngineSound.JericoVol = (jericoVel * Maxvol) / JERICO_SCALE;
					else
						EngineSound.JericoVol = Maxvol;

					EngineSound.JericoFreq = CUR_SAMP_VAL + (float(jericoVel<<4)*sampRateScale);
				}
				else
					EngineSound.JericoVol = 0;
			}
			else
				EngineSound.JericoVol = 0;
		}
																
		if (!EngineSound.WindVolume)							
			EngineSound.WindVolume = 1;							
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OverRevCheck
//Author		Robert Slater
//Date			Tue 1 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::OverRevCheck()
{
	if (	EngineSound.isInitialised
		&&	Manual_Pilot.ControlledAC2
		&&	(Manual_Pilot.ControlledAC2->classtype->planetext == PT_JU87)	)
	{
		if ((EngineSound.JericoVol + EngineSound.JericoOn)>0)
		{
			SQueuePtr	ChannelPtr;									
			SQueuePtr	OldChannelPtr;								
			SampleRec*	SamplePtr;									
			SLong		vol = EngineSound.JericoVol;
			SLong		thevol;												

			SamplePtr = LoadSample(FIL_SFX_OVERREVVING_LOOP1);		
			if (SamplePtr)											
			{
				thevol = vol;

				SoundInWorld(ItemPtr(NULL),thevol);

				if ((thevol + EngineSound.JericoOn)>0)						//RJS 25Oct00
				{
					ChannelPtr = FindFreeHandler(SamplePtr,NULL,OldChannelPtr,3);
					if (ChannelPtr)
					{
						SetUpSample(ChannelPtr,SamplePtr,vol,thevol,0,NULL);

						ChannelPtr->handler->SetLooping(3);
						ChannelPtr->looping = TRUE;
						ChannelPtr->handler->Play();

						EngineSound.JericoOn = true;
					}
					else
					{
						if (OldChannelPtr) 
						{
							if (OldChannelPtr->handler->Status()==SMP_PLAYING)
							{			
								if (thevol)
								{
									ClipVolume(thevol);
									OldChannelPtr->handler->SetVolume(thevol);

									if (Save_Data.hardwareconfig[HW_3DSOUND])
										OldChannelPtr->handler->Set3DSource(*theSubject);

									OldChannelPtr->handler->SetFrequency(EngineSound.JericoFreq);

									EngineSound.JericoOn = true;
								}
								else
								{
									EngineSound.JericoOn = false;

									OldChannelPtr->handler->End();
									OldChannelPtr->Clean();
								}
							}											
						}
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopEngine
//Author		Robert Slater
//Date			Fri 8 Mar 1996
//
//Description	Stops the engine sample, so wind can kick in
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StopEngine(int	velocity)
{
	if (Save_Data.vol.sfx > 0)								
	{												
		HardStop(EngineSound.ChanPtr);						
		StopSample(FIL_SFX_OVERREVVING_LOOP1);		
		EngineSound.Playing = TRUE;							
		EngineSound.Dead = TRUE;							
		EngineSound.Dying = TRUE;
		EngineSound.engineStarting = false;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayLooped
//Author		Robert Slater
//Date			Thu 9 May 1996
//
//Description	Starts a sample for the gunfire and loops it continuously
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayLooped(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol, UByte	looplength, Bool sound3d)
{
#ifndef	_NOSOUNDIN3D_
	SQueuePtr	ChannelPtr;									
	SQueuePtr	OldChannelPtr;								
	SampleRec*	SamplePtr;									
	SLong	thevol;											
	int	thepan;		

	SamplePtr = LoadSample(thefile);
	if (SamplePtr)
	{
		bool	highPriority = false;
		if (sampleitem == Manual_Pilot.ControlledAC2)
			highPriority = true;

		if (allowedsamples || highPriority)								//RJS 22Sep00
		{
			thevol = (SamplePtr->samplevolume * vol) >> 7;		
			vol = thevol;										

			thepan = SoundInWorld(ItemPtr(sampleitem),thevol);			//RJS 12Jan00

			if (thevol)
			{
				ChannelPtr = FindFreeHandler(SamplePtr,sampleitem,OldChannelPtr,looplength);
				if (ChannelPtr)					
				{
					allowedsamples--;							

					SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem);
					ChannelPtr->handler->SetLooping(looplength);
					ChannelPtr->looping = true;
					ChannelPtr->GameSound = sound3d;
					ChannelPtr->handler->Play();

					ChannelPtr->highPriority = highPriority;			//RJS 22Sep00
				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayLanded
//Author		Robert Slater
//Date			Mon 22 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayLanded(ItemBasePtr	sampleitem, SLong	velocity, Bool skid)
{
#ifndef	_NOSOUNDIN3D_
	if (sampleitem==Persons2::PlayerSeenAC)								//RJS 30Aug00
	{
		AircraftAnimData*	adptr = (AircraftAnimData*) MobileItemPtr(sampleitem)->Anim;	//RJS 30Aug00
		adptr->justlanded = 1;											//RJS 30Aug00

		SQueuePtr	ChannelPtr;										
		SQueuePtr	OldChannelPtr;									
		SampleRec*	SamplePtr;										
		int	vol;
		int	freq;
		SLong	thevol;

		if (allowedsamples)
		{
			allowedsamples--;										

			SamplePtr = LoadSample(FIL_SFX_LANDING_GRASS_LOOP);		
			if (SamplePtr)											
			{
//DeadCode RJS 30Aug00 				AircraftAnimData*	adptr = (AircraftAnimData*) ((mobileitem*)sampleitem)->Anim;
				SLong	legtally = 0;
				SLong	maxvol = SamplePtr->samplevolume;			
				SLong	thisvol = SamplePtr->samplevolume;			

				if (!adptr->acleglowerl)							
					legtally++;

				if (!adptr->acleglowerr)							
					legtally++;

				if (!adptr->acleglowerf)							
					legtally++;

				if (!adptr->acleglowerb)							
					legtally++;

				maxvol *= legtally;
				maxvol /= 3;			// Probably only ever get 3 wheels at once
				if (maxvol)
				{
					maxvol *= velocity;
					maxvol /= 7500;			//(ie. 75m/s * 100)

					bouncecount = 100;
					vol = ClipVolume(thisvol,maxvol);				

					thevol = vol;
					SoundInWorld(ItemPtr(NULL),thevol);

					if (skid)										
					{
						// Perhaps check ground type.....


						SLong	skidvol = (128 * vol)/thisvol;		

						PlayOnce(FIL_SFX_TYRE_SCREECH1,sampleitem,skidvol);	//RJS 30Aug00
					}

					if (thevol)										
					{
						ChannelPtr = FindFreeHandler(SamplePtr,sampleitem,OldChannelPtr);
						freq = CUR_SAMP_VAL + (vol/3);				//RJS 14Jun00
						onground = TRUE;

						if (ChannelPtr)
						{
							SetUpSample(ChannelPtr,SamplePtr,vol,thevol,0,sampleitem);
							ChannelPtr->handler->SetLooping(4);
							ChannelPtr->looping = TRUE;
							ChannelPtr->handler->Play();
						}
						else
						{
							if (OldChannelPtr)							
							{
								if (OldChannelPtr->handler->Status()==SMP_PLAYING)
								{
									ClipVolume(thevol);	//RJS 14Sep00

									OldChannelPtr->handler->SetVolume(thevol);
									OldChannelPtr->handler->SetFrequency(freq);
									if (Save_Data.hardwareconfig[HW_3DSOUND])			//RJS 12Jun00
										OldChannelPtr->handler->Set3DSource(*theSubject);	//RJS 12Jun00
								}											
							}
						}
					}
				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopLanded
//Author		Robert Slater
//Date			Tue 23 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StopLanded()
{
	onground = FALSE;

	if (bouncecount > 0)
		bouncecount--;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayOnce
//Author		Robert Slater
//Date			Fri 19 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayOnce(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol, FileNum	stsam, FileNum	endsam, float startscale)
{
#ifndef	_NOSOUNDIN3D_
	SQueuePtr	ChannelPtr;										
	SampleRec*	SamplePtr;										
	int			spos;
	int	stblock = 0;
	int	endblock = 0;
	SLong	thevol;												
	int	thepan;													
//DeadCode RJS 12Jan00 	SLong	distance;

	SamplePtr = LoadSample(thefile);
	if (SamplePtr)
	{
		if (allowedsamples || (sampleitem == Manual_Pilot.ControlledAC2))
		{
			thevol = (SamplePtr->samplevolume * vol) >> 7;			
			vol = thevol;											

			spos = GetIndex(thefile);
			stblock = spos - 1;										
			endblock = spos + 1;									

			if (	(stsam != FIL_NULL)
				&&	(endsam != FIL_NULL)	)
			{
				stblock = GetIndex(stsam) - 1;
				endblock = GetIndex(endsam) + 1;
			}

			thepan = SoundInWorld(ItemPtr(sampleitem),thevol);			//RJS 12Jan00

			if (thevol)													
			{
				SQueuePtr	OldChannelPtr;

				ChannelPtr = FindFreeHandlerOnce(SamplePtr,sampleitem,OldChannelPtr,stblock,endblock);
				if (ChannelPtr)			   
				{
					allowedsamples--;	   

					if (startscale > 1.f)	startscale = 1.f;			//RJS 13Sep00

					SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem,startscale);	//RJS 13Sep00

					ChannelPtr->handler->Play();
				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayOnce
//Author		Robert Slater
//Date			Thu 26 Sep 1996
//
//Description	Simplified version for static items
//
//Inputs		pan is in rowan angles...
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayOnce(FileNum	thefile, int	vol, SLong thepan)
{
#ifndef	_NOSOUNDIN3D_
	SQueuePtr	ChannelPtr;										
	SampleRec*	SamplePtr;										
	int	spos;													
	int	stblock = 0;
	int	endblock = 0;
	ItemBasePtr	sampleitem = NULL;
	SLong	thevol;													

	SamplePtr = LoadSample(thefile);
	if (SamplePtr)
	{
		SQueuePtr	OldChannelPtr;

		spos = GetIndex(thefile);

		thevol = (SamplePtr->samplevolume * vol) >> 7;			
		vol = thevol;											

		SoundInWorld(ItemPtr(NULL),thevol);									//RJS 12Jun00

//DeadCode RJS 12Jun00 		thevol >>= 8;

		stblock = spos - 1;										
		endblock = spos + 1;									

		ChannelPtr = FindFreeHandlerOnce(SamplePtr,sampleitem,OldChannelPtr,stblock,endblock);
		if (ChannelPtr && allowedsamples)							
		{
			allowedsamples--;										

			RowanToPan(thepan);

			SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem);

			ChannelPtr->handler->Play();
		}
		else
		{
			if (OldChannelPtr)						
			{
				if (OldChannelPtr->handler->Status() == SMP_PLAYING)
				{
					ClipVolume(thevol);			//RJS 14Sep00
					OldChannelPtr->handler->SetVolume(thevol);

					if (Save_Data.hardwareconfig[HW_3DSOUND])			//RJS 12Jun00
						OldChannelPtr->handler->Set3DSource(*theSubject);	//RJS 12Jun00
					else
					{
						RowanToPan(thepan);
						OldChannelPtr->handler->SetPan(ClipPan(thepan));
					}
				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopAll
//Author		Robert Slater
//Date			Thu 9 May 1996
//
//Description	Halts all the sound samples
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StopAll()
{
	int	qpos;

	if (dig)													//RJS 26Sep96
	{
		for (qpos = 0; qpos < status.nohandlers; qpos ++)
			HardStop(&soundqueue[qpos]);						//RJS 21Oct97
	}

	EngineSound.Dying = FALSE;									
	EngineSound.Dead = FALSE;									
	EngineSound.Playing = FALSE;								
	EngineSound.CurrentFile = FIL_NULL;							
	EngineSound.OldFile = FIL_NULL;								
	EngineSound.Freq = 8000;									
	EngineSound.SubHarmonicFreq = 8000;							
	EngineSound.SubHarmonicVolume = 1;							
	EngineSound.WindVolume = 1;									
	EngineSound.JericoVol = 0;								
	EngineSound.JericoFreq = MIN_SAMP_VAL;						//RJS 13Jan00
	EngineSound.CockpitWind = 0;								
	EngineSound.InCockpit = TRUE;								
	EngineSound.RumbleVolume = 1;
	EngineSound.Changed = TRUE;
	EngineSound.isInitialised = FALSE;
	EngineSound.StarterMotorFile = FIL_NULL;
	EngineSound.engineStarting = false;
	EngineSound.JericoOn = false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteSample
//Author		Robert Slater
//Date			Tue 23 Jul 1996
//
//Description	Removes a sample from memory and frees its location
//
//Inputs		The sample file
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::DeleteSample(FileNum	thefile)
{
	DeleteSample(GetIndex(thefile));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteSample
//Author		Robert Slater
//Date			Thu 3 Oct 1996
//
//Description	Alternative private delete sample function
//
//Inputs		Internal sample number
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::DeleteSample(SLong	spos)
{
	if ((spos >= 0) && (spos < MAXSAMPLES_LOADED))				//MS 23Sep98
	{
		if (thesample[spos].blockptr)
		{
			delete thesample[spos].blockptr;
			thesample[spos].blockptr = NULL;	
		}
	}
	else
		_Error.EmitSysErr("Bullpoop sample delete %d",spos);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeSamples
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Frees all the samples in memory
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::FreeSamples()
{
	int	count;

	donePreLoad = false;												//RJS 6Oct00

	if (dig == NULL)
		return;

	for (count = 0; count < MAXSAMPLES_LOADED; count ++)		//MS 23Sep98
	{
		if (thesample[count].blockptr)
		{
			delete thesample[count].blockptr;
			
			thesample[count].blockptr = NULL;	
		}

	}

	status.nosamples = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeTunes
//Author		Robert Slater
//Date			Mon 4 Mar 1996
//
//Description	Frees all the tunes in memory	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::FreeTunes()
{
	int	tuneno;

	if (mdi == NULL)
		return;

	for (tuneno = 0; tuneno < MAXTUNES; tuneno++)
	{
		if (tune[tuneno].blockptr)
		{
			#ifdef	__DOS__
			VMM_unlock(getdata(tune[tuneno].blockptr),tune[tuneno].size);
			#endif
			delete tune[tuneno].blockptr;

			tune[tuneno].blockptr = NULL;
		}

	}

	status.notunes = 0;
}

	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShutDownSound
//Author		Robert Slater
//Date			Wed 21 Feb 1996
//
//Description	Close down all music drivers and free associated memory	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ShutDownSound()
{
	int		tuneno;
	int		count;
	SLong	result;

	StopAll();													//RJS 21Jul98

	_SndFonts.KillSFont();

	FreeTunes();
	FreeSamples();

	ClearSoundQueue();

	wavetable.blockptr = NULL;
	mdi->Close(&mdi);				//must come before dig delete.

	if (	dig															//RJS 18Oct00
		&& (volumeDesktop != VOL_NOTSET)	)							//RJS 18Oct00
		dig->SetVolumeDirect(volumeDesktop);							//RJS 18Oct00

	dig->Close(&dig);
	timer = NULL;
	delete []thesample;											//MS 23Sep98
	thesample = NULL;											//MS 23Sep98
	if (themusicsample)											//RJS 14Apr99
		delete []themusicsample;								//RJS 14Apr99
	themusicsample=NULL;										//RJS 14Apr99

	delete theSubject;											//RJS 12Jan00
	delete theListener;											//RJS 12Jan00

	theSubject = NULL;
	theListener = NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GamePaused
//Author		Robert Slater
//Date			Fri 9 Aug 1996
//
//Description	Stops the engine sound
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::GamePaused()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetSoundFlags
//Author		Robert Slater
//Date			Fri 12 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ResetSoundFlags()
{
	EngineSound.Dying = FALSE;									//RJS 21Oct97
	EngineSound.Dead = FALSE;									//RJS 21Oct97
	EngineSound.Playing = FALSE;								//RJS 21Oct97
	EngineSound.IsJet = FALSE;									//RJS 21Oct97
	EngineSound.CurrentFile = FIL_NULL;							//RJS 21Oct97
	EngineSound.OldFile = FIL_NULL;								//RJS 21Oct97
	EngineSound.Freq = 8000;									//RJS 21Oct97
	EngineSound.SubHarmonicFreq = 8000;							//RJS 21Oct97
	EngineSound.SubHarmonicVolume = 1;							//RJS 21Oct97
	EngineSound.WindVolume = 1;									//RJS 21Oct97
	EngineSound.JericoVol = 0;								//RJS 21Oct97
	EngineSound.JericoFreq = MIN_SAMP_VAL;						//RJS 13Jan00
	EngineSound.CockpitWind = 0;								//RJS 19May98
	EngineSound.InCockpit = TRUE;								//RJS 19May98
	EngineSound.RumbleVolume = 1;
	EngineSound.Changed = TRUE;
	EngineSound.isInitialised = FALSE;							//RJS 25May99
	EngineSound.StarterMotorFile = FIL_NULL;					//RJS 13Jan00
	EngineSound.engineStarting = false;									//RJS 13Jun00
	EngineSound.JericoOn = false;										//RJS 25Oct00

	canplaynothing = FALSE;

	inprefs = FALSE;											//RJS 29Nov96

	onground = FALSE;
	bouncecount = 0;
	delindex = 0;												//RJS 29Nov96
	allowedsamples = 1;											//RJS 25May99
	boffcount = 0;
	CockpitView = TRUE;

	lastBuffetVol = 0;											//RJS 28Jan99

	diveBrakesOn = false;												//RJS 25Oct00

	ambientCnt = 0;														//RJS 16Nov00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetMidiFlags
//Author		Robert Slater
//Date			Thu 29 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ResetMidiFlags()
{
	request.activated = INT_NULL;								//RJS 18Jun99
	request.wait = FALSE;
	request.todiscard = FALSE;
	request.killnow = FALSE;
	request.alonetuneno = NULL;									//RJS 26Feb98
	request.mainstopped = FALSE;								//RJS 12Nov96
	request.musictimeout = 0;									//RJS 18Jun99
	incombat = FALSE;											//RJS 12Nov96
	request.CurrentTrack = 0;
	Mood = MOOD_NEUTRAL;

	request.forcestop = 0;										//RJS 18Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitUI
//Author		Robert Slater
//Date			Tue 6 Apr 1999
//
//Description	Set up user interface handler for sfx
//				and Smacker
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::InitUI(int	wind)
{
	Bool	theresult = FALSE;
#ifndef _NO_Sound_AUDIO_
 	if (dig)
		StopAll();
	
 	if (NewDigitalDriver(NOM_SAMP_VAL,4,TRUE,false))
 	{
//DeadCode RJS 18Oct00 		HWND	thiswin = (HWND) wind;
//DeadCode RJS 18Oct00 
//UpdateMilesCode RJS 08Nov99		SmackSoundUseMSS (dig);
//UpdateMilesCode RJS 08Nov99 		AIL_set_DirectSound_HWND(dig,thiswin);
 		theresult = TRUE;

		SetVolumes(FALSE);
 	}
#endif

	ambientCnt = 0;

	return(theresult);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init3D
//Author		Dave Whiteside
//Date			Tue 6 Apr 1999
//
//Description	Set up 3d digital handler
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::Init3D()
{
	Bool	theresult = FALSE;									//RJS 30Oct96
#ifndef _NO_Sound_AUDIO_

	wasWindy = false;

	if (NewDigitalDriver(MAX_SAMP_VAL,CHANNELS_MAX,FALSE,bool(Save_Data.hardwareconfig[HW_3DSOUND])))	//RJS 28Sep00
	{
		SetVolumes(FALSE);
		theresult = TRUE;
 	}
#endif
	playingMiller = false;										//RJS 21May99

	ambientCnt = 0;

	return(theresult);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGlobalVolumes
//Author		Robert Slater
//Date			Tue 13 Aug 1996
//
//Description	Sets the global volumes for sfx, midi and engine	
//
//Inputs		sfx vol, midi vol, engine vol
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetGlobalVolumes(int	sfxvol, int	midivol, int	engvol, int	smackervol, Bool	saveset)
{
	int	spos;
	TuneStrucP	TunePtr;

	inprefs = TRUE;												//RJS 06Dec96

	if (dig)
	{
		if (sfxvol > -1)
		{
 			if (sfxvol)
				dig->SetMasterVolume(VOL_TOP_CLIP);						//RJS 14Sep00

			Save_Data.vol.sfx = sfxvol;							//RJS 09Dec96
		}

		if (engvol > -1)
			EngineSound.Volume = (EngineSound.VolLoaded * engvol) >> 7;//RJS 18Jan99
		else
			EngineSound.Volume = 0;

		if (smackervol > -1)
		 	thesmackervol = smackervol;
	}
	else
		Save_Data.vol.sfx = 0;

	if (mdi)
	{
		if (midivol > -1)
		{
			if (!saveset)
			{
				if (midivol == 0)
				{
					DiscardMusic();
					Save_Data.vol.music = 0;
				}
				else
				{
					Save_Data.vol.music = midivol;

					TunePtr = LoadTune(FIL_MUSIC_OBJECTIVE_FAILED);
					if (TunePtr)
					{
						if (!mdi->Playing())
							request.alonetuneno = NULL;
					}
				}
			}

			mdi->SetMasterVolume((midivol*VOL_TOP_CLIP)/125);		//RJS 14Sep00
		}
	}
	else
		Save_Data.vol.music = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSampleVolumes
//Author		Robert Slater
//Date			Thu 3 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::GetSampleVolumes()
{
	int			novolumes=0;									//RJS 23Feb99
	int			count;											//RJS 23Feb99
	SLongP		volptr;											//RJS 23Feb99
																//RJS 23Feb99
	fileblock*	theblock = new fileblock (FIL_SFX_VOLUMES);					//RJS 23Feb99
	if (theblock)												//RJS 23Feb99
	{															//RJS 23Feb99
		volptr = (SLongP) getdata(theblock);					//RJS 23Feb99
																//RJS 23Feb99
		novolumes = *volptr;									//RJS 23Feb99
		volptr++;												//RJS 23Feb99
																//RJS 23Feb99
		if (novolumes > MAXSAMPLES)								//RJS 23Feb99
			novolumes = MAXSAMPLES;								//RJS 23Feb99
																//RJS 23Feb99
		thesample = new SampleRec[novolumes];					//RJS 23Feb99
		if (thesample)											//RJS 23Feb99
		{														//RJS 23Feb99
			MAXSAMPLES_LOADED = novolumes;						//RJS 23Feb99
			count = 0;											//RJS 23Feb99
			SLong	maxvol,boost;								//RJS 23Feb99
																//RJS 23Feb99
			do													//RJS 23Feb99
			{													//RJS 23Feb99
				maxvol = *volptr++;								//RJS 23Feb99
				boost = *volptr++;								//RJS 23Feb99
																//RJS 23Feb99
				maxvol *= boost;								//RJS 23Feb99
				maxvol /= 100;									//RJS 23Feb99
																//RJS 23Feb99
				thesample[count++].samplevolume = maxvol;		//RJS 23Feb99
			}													//RJS 23Feb99
			while (count < novolumes);							//RJS 23Feb99
																//RJS 23Feb99
			EngineSound.VolLoaded = 32768;						//RJS 11Jun99
		}														//RJS 23Feb99
		else													//RJS 23Feb99
			Save_Data.vol.sfx = 0;								//RJS 23Feb99
																//RJS 23Feb99
		delete theblock;										//RJS 23Feb99
	}															//RJS 23Feb99
	else														//RJS 23Feb99
		Save_Data.vol.sfx = 0;									//RJS 23Feb99
}												

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDirectSoundWindow
//Author		Robert Slater
//Date			Mon 18 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetDirectSoundWindow(ULong	newwin)
{
	if (dig)
	{
//DeadCode RJS 20Oct00 		HWND	thiswin = (HWND) newwin;

//UpdateMilesCode RJS 08Nov99 		AIL_set_DirectSound_HWND(dig,thiswin);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCompressedDLS
//Author		Robert Slater
//Date			Mon 18 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetCompressedDLS(TuneStrucP TunePtr, void*	ptr, SLong	size)
{
//UpdateMilesCode RJS 08Nov99 	SLong	resval = AIL_extract_DLS(ptr,
//UpdateMilesCode RJS 08Nov99 									 size,
//UpdateMilesCode RJS 08Nov99 									 &TunePtr->xmiPtr,
//UpdateMilesCode RJS 08Nov99 									 0,
//UpdateMilesCode RJS 08Nov99 									 &TunePtr->dlsPtr,
//UpdateMilesCode RJS 08Nov99 									 0	);
//UpdateMilesCode RJS 08Nov99 
//UpdateMilesCode RJS 08Nov99 	if (TunePtr->dlsPtr)
//UpdateMilesCode RJS 08Nov99 	{
//UpdateMilesCode RJS 08Nov99 		TunePtr->dlsID = AIL_DLS_load_memory(wavetable.DLSwavesynth,
//UpdateMilesCode RJS 08Nov99 				 							 TunePtr->dlsPtr,
//UpdateMilesCode RJS 08Nov99 				 							 0						);
//UpdateMilesCode RJS 08Nov99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUncompressedDLS
//Author		Robert Slater
//Date			Mon 18 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetUncompressedDLS(TuneStrucP TunePtr, void* ptr, SLong	size)
{
//UpdateMilesCode RJS 08Nov99 	SLong	resval = AIL_find_DLS(	ptr,
//UpdateMilesCode RJS 08Nov99 									size,
//UpdateMilesCode RJS 08Nov99 									&TunePtr->xmiPtr,
//UpdateMilesCode RJS 08Nov99 									0,
//UpdateMilesCode RJS 08Nov99 									&TunePtr->dlsPtr,
//UpdateMilesCode RJS 08Nov99 									0	);
//UpdateMilesCode RJS 08Nov99 
//UpdateMilesCode RJS 08Nov99 	if (TunePtr->dlsPtr)
//UpdateMilesCode RJS 08Nov99 	{
//UpdateMilesCode RJS 08Nov99 		TunePtr->dlsID = AIL_DLS_load_memory(wavetable.DLSwavesynth,
//UpdateMilesCode RJS 08Nov99 											 TunePtr->dlsPtr,
//UpdateMilesCode RJS 08Nov99 											 0						);
//UpdateMilesCode RJS 08Nov99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetXMidi
//Author		Robert Slater
//Date			Tue 19 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetXMidi(TuneStrucP	TunePtr)
{
//DeadCode RJS 09Nov99 	if (TunePtr->xmiPtr)
//DeadCode RJS 09Nov99 	{
//DeadCode RJS 09Nov99 		SLong		result, size;
//DeadCode RJS 09Nov99 		void		*tmpptr;
//DeadCode RJS 09Nov99 		SLong		*headptr;
//DeadCode RJS 09Nov99 		int			count;
//DeadCode RJS 09Nov99 		UWord		noforms = 0;
//DeadCode RJS 09Nov99 		SLong		header;
//DeadCode RJS 09Nov99 		HSEQUENCE	tmphandle = NULL;
//DeadCode RJS 09Nov99 
//DeadCode RJS 09Nov99 		// Get IFF_ number of sequences information from header...
//DeadCode RJS 09Nov99 		headptr = (SLongP) TunePtr->xmiPtr;
//DeadCode RJS 09Nov99 
//DeadCode RJS 09Nov99 		for (count = 0; count < 5; count ++)
//DeadCode RJS 09Nov99 			header = *headptr++;
//DeadCode RJS 09Nov99 
//DeadCode RJS 09Nov99 		noforms = (UWord) *headptr;
//DeadCode RJS 09Nov99 
//DeadCode RJS 09Nov99 		TunePtr->nosequences = noforms;
//DeadCode RJS 09Nov99 		if (	(TunePtr->ttype == T_independent)				//RJS 06May99
//DeadCode RJS 09Nov99 			||	(TunePtr->ttype == T_independent_pri)	)		//RJS 06May99
//DeadCode RJS 09Nov99 		{
//DeadCode RJS 09Nov99 			tmphandle = tune[GetIndex(FIL_MUSIC_MAIN)].sequence[0];
//DeadCode RJS 09Nov99 			if (tmphandle == NULL)
//DeadCode RJS 09Nov99 				LoadTune(FIL_MUSIC_MAIN);				
//DeadCode RJS 09Nov99 			tmphandle = tune[GetIndex(FIL_MUSIC_MAIN)].sequence[0];
//DeadCode RJS 09Nov99 		}
//DeadCode RJS 09Nov99 		else
//DeadCode RJS 09Nov99 		{
//UpdateMilesCode RJS 08Nov99 			if (TunePtr->sequence[0] == NULL)
//UpdateMilesCode RJS 08Nov99 				tmphandle = AIL_allocate_sequence_handle(mdi);
//UpdateMilesCode RJS 08Nov99 			else
//UpdateMilesCode RJS 08Nov99 				tmphandle = TunePtr->sequence[0];
//DeadCode RJS 09Nov99 		}
//DeadCode RJS 09Nov99 
//DeadCode RJS 09Nov99 		for (count = 0; count < TunePtr->nosequences; count ++)
//DeadCode RJS 09Nov99 		{
//DeadCode RJS 09Nov99 			TunePtr->sequence[count] = tmphandle;		
//UpdateMilesCode RJS 08Nov99 			if (TunePtr->sequence[count] == NULL)
//UpdateMilesCode RJS 08Nov99 			{
//UpdateMilesCode RJS 08Nov99 				AIL_shutdown();
//UpdateMilesCode RJS 08Nov99 
//UpdateMilesCode RJS 08Nov99 				_Error.EmitSysErr(AIL_last_error());
//UpdateMilesCode RJS 08Nov99 			}
//DeadCode RJS 09Nov99 		}
//DeadCode RJS 09Nov99 	}
//DeadCode RJS 09Nov99 	else
//DeadCode RJS 09Nov99 	{
//UpdateMilesCode RJS 08Nov99 		AIL_shutdown();
//DeadCode RJS 09Nov99 		_Error.EmitSysErr("Not an XMIDI file!");
//DeadCode RJS 09Nov99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDLS
//Author		Robert Slater
//Date			Tue 19 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetDLS(TuneStrucP	TunePtr)
{
	if (TunePtr->dlsPtr)
	{
		SLong		result, size;
		void		*tmpptr;
		SLong		*headptr;
		int			count;
		UWord		noforms = 0;
		SLong		header;
		HSEQUENCE	tmphandle = NULL;

		noforms = TunePtr->nosequences;
		if (TunePtr->ttype == T_independent)
		{
			tmphandle = tune[GetIndex(FIL_MUSIC_MAIN)].DLSsequence[0];
			if (tmphandle == NULL)
				LoadTune(FIL_MUSIC_MAIN);				
			tmphandle = tune[GetIndex(FIL_MUSIC_MAIN)].DLSsequence[0];
		}
		else
		{
//UpdateMilesCode RJS 08Nov99 			if (TunePtr->DLSsequence[0] == NULL)
//UpdateMilesCode RJS 08Nov99 				tmphandle = AIL_allocate_sequence_handle(mdi);
//UpdateMilesCode RJS 08Nov99 			else
//UpdateMilesCode RJS 08Nov99 				tmphandle = TunePtr->DLSsequence[0];
		}

		for (count = 0; count < noforms; count ++)
		{
			TunePtr->DLSsequence[count] = tmphandle;		
//UpdateMilesCode RJS 08Nov99 			if (TunePtr->DLSsequence[count] == NULL)
//UpdateMilesCode RJS 08Nov99 			{
//UpdateMilesCode RJS 08Nov99 				AIL_shutdown();
//UpdateMilesCode RJS 08Nov99 
//UpdateMilesCode RJS 08Nov99 				_Error.EmitSysErr(AIL_last_error());
//UpdateMilesCode RJS 08Nov99 			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCockpit
//Author		Robert Slater
//Date			Wed 20 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetCockpit(Bool	thecock)
{
	CockpitView = thecock;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVP
//Author		Robert Slater
//Date			Thu 21 May 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetVP(mobileitem *vp)
{
	View_Point = vp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayWind
//Author		Robert Slater
//Date			Wed 20 May 1998
//
//Description	Plays cockpit wind, adjusting the volume on-the-fly
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayWind()
{
#ifndef	_NOSOUNDIN3D_
	if (Save_Data.vol.sfx != 0)
	{
		SQueuePtr	ChannelPtr;								   
		SQueuePtr	OldChannelPtr;							   
		SampleRec*	SamplePtr;								   
		int			vol;
		SLong		thevol;											   

		SamplePtr = LoadSample(FIL_SFX_WIND_COCKPIT_LOOP);	   
		if (SamplePtr)										   
		{
			vol = EngineSound.CockpitWind;	
			
			thevol = vol;
			SoundInWorld(ItemPtr(NULL),thevol);							//RJS 12Jun00

			if (thevol || wasWindy)
			{
				ChannelPtr = FindFreeHandler(SamplePtr,NULL,OldChannelPtr,3);
				if (ChannelPtr)
				{
					wasWindy = true;

					SetUpSample(ChannelPtr,SamplePtr,vol,thevol,0,NULL);

					ChannelPtr->handler->SetLooping(3);
					ChannelPtr->looping = TRUE;
					ChannelPtr->handler->Play();
				}
				else
				{
					if (OldChannelPtr)				
					{
						if (OldChannelPtr->handler->Status() == SMP_PLAYING)
						{
							if (Save_Data.hardwareconfig[HW_3DSOUND])			//RJS 12Jun00
								OldChannelPtr->handler->Set3DSource(*theSubject);	//RJS 12Jun00

							if (thevol)
							{
								wasWindy = true;

								ClipVolume(thevol);	//RJS 14Sep00

			 					OldChannelPtr->handler->SetVolume(thevol);
							}
							else
							{
								wasWindy = false;

								OldChannelPtr->handler->End();
								OldChannelPtr->sampleindex = NULL;							
								OldChannelPtr->looping = FALSE;							
								OldChannelPtr->worlditem = NULL;							
 								OldChannelPtr->GameSound = FALSE;
							}
						}
					}
				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayFlyAway
//Author		Robert Slater
//Date			Mon 1 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayFlyAway(ItemBasePtr	sampleitem)
{
	if (Save_Data.vol.sfx)										//RJS 31May99
	{
		if (EngineSound.CurrentFile < FIL_SFX_LOOP_FX_START)
		{
			StopEngine();

			if (AirStrucPtr(sampleitem)->nationality == NAT_RAF)		//RJS 13Sep00
				_Miles.PlayOnce(FIL_SFX_FLYBY_SLOW_RAF,sampleitem,GetEngineVol(),FIL_NULL,FIL_NULL,.31149);
			else
				_Miles.PlayOnce(FIL_SFX_FLYBY_SLOW_LUF,sampleitem,GetEngineVol(),FIL_NULL,FIL_NULL,.31169);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SampleFinished
//Author		Robert Slater
//Date			Tue 9 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::SampleFinished(UByteP	QueuePtr, bool hipriset)
{
	Bool		retval = FALSE;

	if (dig)								
	{
		SQueuePtr	ChannelPtr = (SQueuePtr) QueuePtr;
		if (ChannelPtr)
		{
			if (	(ChannelPtr->handler->Status() == SMP_DONE)
				||	hipriset											)
			{
				if (hipriset)
					ChannelPtr->handler->End();							//RJS 16Aug00

				ChannelPtr->sampleindex = NULL;						
				ChannelPtr->playingvolume = 0;							
				ChannelPtr->worlditem = NULL;							
				ChannelPtr->GameSound = FALSE;								
				ChannelPtr->looping = FALSE;
				ChannelPtr->isRadio = FALSE;

				retval = TRUE;
			}
		}
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlaySampleRadio
//Author		Robert Slater
//Date			Tue 9 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP	Sound::PlaySampleRadio(UByteP	DataPtr, int Size, SWord volscale, int Frequency, int noBits)
{
	SQueuePtr	ChannelPtr=NULL;
	if (dig)													
	{
		if (Save_Data.vol.rchat)								
		{														
			ChannelPtr = FindFreeRadioHandler();				
			if (ChannelPtr)										
			{
				SWord	theVol = (volscale * Save_Data.vol.rchat)>>(7-VOL_SCALE_FROM_PREFS);	//RJS 14Sep00

				ChannelPtr->sampleindex = NULL;						
				ChannelPtr->playingvolume = 0;							
				ChannelPtr->worlditem = NULL;							
				ChannelPtr->GameSound = FALSE;								
				ChannelPtr->isRadio = TRUE;								
				ChannelPtr->looping = FALSE;

				if (ChannelPtr->handler->LoadBuffer(DIG_F_MONO_8,(void*)DataPtr,Size))
				{
					ChannelPtr->handler->SetFrequency(Frequency);
					ChannelPtr->handler->SetVolume(theVol);
					if (View_Point)
					{
						SLong	vx,vy,vz;
						GetEyeVelocity(vx,vy,vz);					//RJS 15Sep00
						ChannelPtr->handler->Set3DSource(SubjectStruc(eyeWorld,float(vx)*VEL_SCALE,float(vy)*VEL_SCALE,float(vz)*VEL_SCALE,theVol,MIN_DISTANCE,MAX_DISTANCE));	//RJS 15Sep00
					}

					ChannelPtr->handler->Play();
				}
			}
		}
	}

	return((UByteP)ChannelPtr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisableAll
//Author		Robert Slater
//Date			Mon 27 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::DisableAll()
{
	StopAll();
	DiscardMusic();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		KillAll
//Author		Robert Slater
//Date			Mon 27 Jul 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::KillAll()
{
	StopAll();
	DiscardMusic();

	FreeSamples();
	ResetSoundFlags();
	ResetMidiFlags();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVolumes
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetVolumes(Bool goinginto3d)
{
//Temp
//DeadCode RJS 31May00 	Save_Data.vol.sfx = 32;
//DeadCode RJS 31May00 	Save_Data.vol.uisfx = 32;
	int	FreeChannelStartWithRadio = 1;							//RJS 25Oct00
	int	FreeChannelRadio = 0;

	allowedsamples = status.nohandlers / 3;
	if (goinginto3d)
	{
		// Set 3d volume...
		if ((Save_Data.vol.sfx >= 0) && (Save_Data.vol.sfx < 128) && IsEnabled(SOUND_DIGITAL))
		{
			dig->SetMasterVolume((Save_Data.vol.sfx*VOL_TOP_CLIP)/125);	//RJS 14Sep00

			if (!donePreLoad)
			{
				donePreLoad = true;
				PreLoadSFX();
			}

			if (!donePreLoadRadio_3D && !_Replay.Playback)				//RJS 21Sep00
			{
				if (!PreLoadRadioChatter())
				{
					Save_Data.vol.rchat = 0;
//DeadCode RJS 06Oct100 					rchatter_allowed = false;									//RJS 16Aug99
				}
				else
				{
					donePreLoadRadio_3D = true;
//DeadCode RJS 06Oct100 					rchatter_allowed = true;
				}
			}
		}
		else
		{
			Save_Data.vol.sfx = 0;
			Save_Data.vol.rchat = 0;
		}

		FreeChannelStartWithRadio = 3;
		FreeChannelRadio = 2;
	}
	else
	{
//DeadCode RJS 6Oct00 #ifndef	_NO_RADIOCHATTER_
//DeadCode RJS 6Oct00 		if (!donePreLoadRadio_2D)
//DeadCode RJS 6Oct00 		{
//DeadCode RJS 6Oct00 			donePreLoadRadio_2D = true;

//			PreLoadChatChunk(FIL_DIR_RCHAT_GROUND-FIL_DIR_RCHAT_RAFPLAYR);
//			PreLoadChatChunk(FIL_DIR_RCHAT_FEMALE-FIL_DIR_RCHAT_RAFPLAYR);

//DeadCode RJS 14Aug00 			if (!PreLoadRadioChatter())
//DeadCode RJS 14Aug00 			{
//DeadCode RJS 14Aug00 				Save_Data.vol.rchat = 0;
//DeadCode RJS 14Aug00 				rchatter_allowed = false;
//DeadCode RJS 14Aug00 			}
//DeadCode RJS 14Aug00 			else
//DeadCode RJS 14Aug00 				rchatter_allowed = true;
//DeadCode RJS 6Oct00 		}
//DeadCode RJS 6Oct00 #else
//DeadCode RJS 6Oct00 		Save_Data.vol.rchat = 0;
//DeadCode RJS 6Oct00 		rchatter_allowed = false;
//DeadCode RJS 6Oct00 #endif
		// Set User Interface volume...
		if (Save_Data.vol.uisfx || Save_Data.vol.rchat)			//RJS 05Apr00
 			dig->SetMasterVolume(VOL_TOP_CLIP);							//RJS 14Sep00

		if (	(Save_Data.vol.uisfx < 0)						//RJS 05Apr00
			||	(Save_Data.vol.uisfx > 127)						//RJS 05Apr00
			|| !IsEnabled(SOUND_DIGITAL)	)					//RJS 05Apr00
			Save_Data.vol.uisfx = 0;							//RJS 05Apr00
	}

	if ((Save_Data.vol.music >= 0) && (Save_Data.vol.music < 128) && IsEnabled(SOUND_MIDI))
	{
		mdi->SetMasterVolume((Save_Data.vol.music*VOL_TOP_CLIP)/125);//RJS 14Sep00

		if (havePercussion==true)								//RJS 14Apr99
		{
			if (goinginto3d)
			{
				if (IsEnabled(SOUND_DIGITAL))					//RJS 29Jun99
				{
					if (PreLoadMusicSamples())
					{
						//if we want sampled percussion, but no sfx, make sure we get volume!
						if (Save_Data.vol.sfx)
						{
							percvolscale = (Save_Data.vol.music<<8)/Save_Data.vol.sfx;
							if (percvolscale > 256)
								percvolscale = 256;
						}
						else
						{
							percvolscale = 256;
							dig->SetMasterVolume((Save_Data.vol.music*VOL_TOP_CLIP)/125);	//RJS 14Sep00
						}

						if (setPercussion)
						{
//UpdateMilesCode RJS 08Nov99 							AIL_register_event_callback(mdi,MIDIEventInterrupt);
							setPercussion = FALSE;
						}
					}
				}
			}
			else
				DeleteMusicSamples();
		}
	}
	else
		Save_Data.vol.music = 0;

	if (IsEnabled(SOUND_DIGITAL))
		EngineSound.Volume = (EngineSound.VolLoaded * Save_Data.vol.engine) >> 7;
	else
		EngineSound.Volume = 0;

	// Free up channel if we don't need it...
	if (Save_Data.vol.rchat)									
		freechannelstart = FreeChannelStartWithRadio;									//RJS 25Oct00
	else														
		freechannelstart = FreeChannelStartWithRadio-1;									

	channel_radiochatter = FreeChannelRadio;									
	channel_percussion = FreeChannelRadio+1;										
	if (havePercussion)											
		freechannelstart++;										

	thesmackervol = Save_Data.vol.anim;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsEnabled
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::IsEnabled(SoundType	theSound)
{
	Bool	retval = FALSE;
	switch (theSound)
	{
	case SOUND_DIGITAL:
	{
		if (dig)	retval = TRUE;
	}
	break;
	case SOUND_MIDI:
	{
		if (mdi)	retval = TRUE;
	}
	break;
	case SOUND_RADIO:
	{
		if (rchatter_allowed)	retval = TRUE;
	}
	break;
	}

	return(retval);
}

void	Sound::SetEngine()
{
	if (Manual_Pilot.ControlledAC2)								//DAW 21Jun99
	{
		if (Manual_Pilot.ControlledAC2->fly.pModel->EngineList->Type == ET_PISTON)
			EngineSound.IsJet = FALSE;
		else
			EngineSound.IsJet = TRUE;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessInterfaceSpot
//Author		Bobby Parp
//Date			Tue 17 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ProcessInterfaceSpot()
{
 	allowedsamples = status.nohandlers / 3;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitSoundFonts
//Author		Robert Slater
//Date			Thu 28 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::InitSoundFonts()
{
//UpdateMilesCode RJS 08Nov99 	if (trySoundFonts == true)
//UpdateMilesCode RJS 08Nov99 	{
//UpdateMilesCode RJS 08Nov99 		LPHMIDIOUT	midiOutDev = (LPHMIDIOUT) pooMidiDev;
//UpdateMilesCode RJS 08Nov99 
//UpdateMilesCode RJS 08Nov99 		trySoundFonts = false;
//UpdateMilesCode RJS 08Nov99 
//UpdateMilesCode RJS 08Nov99 		if (_SndFonts.LoadSoundFont(midiOutDev,FIL_SFONT_SNARES) == FALSE)
//UpdateMilesCode RJS 08Nov99 		{
//UpdateMilesCode RJS 08Nov99  			AIL_midiOutClose(mdi);
//UpdateMilesCode RJS 08Nov99 
//UpdateMilesCode RJS 08Nov99 			havePercussion = false;								//RJS 14Apr99
//UpdateMilesCode RJS 08Nov99 			if (bestDrivers[1] > -1)
//UpdateMilesCode RJS 08Nov99 			{
//UpdateMilesCode RJS 08Nov99 				MusicDir = FIL_DIR_MUSICMED-FIL_DIR_MUSIC;
//UpdateMilesCode RJS 08Nov99 				uDriverID = (ULong) bestDrivers[1];
//UpdateMilesCode RJS 08Nov99 				if (AIL_midiOutOpen (&mdi, &midiOutDev, uDriverID))				
//UpdateMilesCode RJS 08Nov99 				{
//UpdateMilesCode RJS 08Nov99 					MusicDir = FIL_DIR_MUSICLOW-FIL_DIR_MUSIC;
//UpdateMilesCode RJS 08Nov99 					if (bestDrivers[2] > -1)
//UpdateMilesCode RJS 08Nov99 					{
//UpdateMilesCode RJS 08Nov99 						uDriverID = (ULong) bestDrivers[2];
//UpdateMilesCode RJS 08Nov99 						if (AIL_midiOutOpen (&mdi, &midiOutDev, uDriverID))				
//UpdateMilesCode RJS 08Nov99 							mdi = NULL;
//UpdateMilesCode RJS 08Nov99 						else
//UpdateMilesCode RJS 08Nov99 							havePercussion=true;				//RJS 14Apr99
//UpdateMilesCode RJS 08Nov99 					}
//UpdateMilesCode RJS 08Nov99 				}
//UpdateMilesCode RJS 08Nov99 			}
//UpdateMilesCode RJS 08Nov99 			else
//UpdateMilesCode RJS 08Nov99 			{
//UpdateMilesCode RJS 08Nov99 				MusicDir = FIL_DIR_MUSICLOW-FIL_DIR_MUSIC;
//UpdateMilesCode RJS 08Nov99 				if (bestDrivers[2] > -1)
//UpdateMilesCode RJS 08Nov99 				{
//UpdateMilesCode RJS 08Nov99 					uDriverID = (ULong) bestDrivers[2];
//UpdateMilesCode RJS 08Nov99 					if (AIL_midiOutOpen (&mdi, &midiOutDev, uDriverID))				
//UpdateMilesCode RJS 08Nov99 						mdi = NULL;
//UpdateMilesCode RJS 08Nov99 					else
//UpdateMilesCode RJS 08Nov99 						havePercussion=true;
//UpdateMilesCode RJS 08Nov99 				}
//UpdateMilesCode RJS 08Nov99 				else
//UpdateMilesCode RJS 08Nov99 					mdi = NULL;
//UpdateMilesCode RJS 08Nov99 			}
//UpdateMilesCode RJS 08Nov99 		}
//UpdateMilesCode RJS 08Nov99 
//UpdateMilesCode RJS 08Nov99 		if (mdi == NULL)
//UpdateMilesCode RJS 08Nov99 			Save_Data.vol.music = 0;
//UpdateMilesCode RJS 08Nov99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayBuffet
//Author		Robert Slater
//Date			Thu 28 Jan 1999
//
//Description	
//
//Inputs		vol is 0 - 128 scale factor,
//				pan is in Rowan angles
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayBuffet(SLong vol, SLong thepan)
{
#ifndef	_NOSOUNDIN3D_
	if (vol || lastBuffetVol)
	{
		SampleRec*	SamplePtr = LoadSample(FIL_SFX_SPRING1);
		if (SamplePtr)
		{
			SQueuePtr	ChannelPtr;										
			SQueuePtr	OldChannelPtr;
			SLong		thevol,audiblevol;											
//DeadCode RJS 12Jan00 			SLong		distance;
			Bool		dothis = FALSE;


			thevol = (SamplePtr->samplevolume * vol) >> 7;			
			vol = thevol;
			audiblevol = vol;

			SoundInWorld(ItemPtr(NULL),audiblevol);

			if (audiblevol)
				dothis = TRUE;
			else
			{	
				if (lastBuffetVol)
					dothis = TRUE;
			}

			if (dothis)
			{
				RowanToPan(thepan);

				ChannelPtr = FindFreeHandler(SamplePtr,NULL,OldChannelPtr);
				if (ChannelPtr && allowedsamples)
				{
					allowedsamples--;

					SetUpSample(ChannelPtr,SamplePtr,vol,audiblevol,thepan,NULL);
					ChannelPtr->handler->SetLooping(2);	
					ChannelPtr->handler->Play();			
					ChannelPtr->looping = TRUE;						
				}
				else
				{
					if (OldChannelPtr)	
					{
						if (OldChannelPtr->handler->Status() == SMP_PLAYING)
						{
							ClipVolume(audiblevol);						//RJS 14Sep00

							if (!audiblevol)							//RJS 30Aug00
							{											//RJS 30Aug00
								OldChannelPtr->handler->End();			//RJS 30Aug00
								OldChannelPtr->sampleindex = NULL;		//RJS 30Aug00
								OldChannelPtr->looping = FALSE;			//RJS 30Aug00
								OldChannelPtr->worlditem = NULL;		//RJS 30Aug00
 								OldChannelPtr->GameSound = FALSE;		//RJS 30Aug00
							}											//RJS 30Aug00
							else
							{
								OldChannelPtr->handler->SetVolume(audiblevol);

								if (Save_Data.hardwareconfig[HW_3DSOUND])			//RJS 12Jun00
									OldChannelPtr->handler->Set3DSource(*theSubject);	//RJS 12Jun00
								else
									OldChannelPtr->handler->SetPan(ClipPan(thepan));
							}
						}
					}
				}
			}

			lastBuffetVol = audiblevol;
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RowanToPan
//Author		Robert Slater
//Date			Fri 29 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::RowanToPan(SLong	&theAngle)
{
	if (theAngle > 16384)
		theAngle = 32768 - theAngle;
	
	if (theAngle < -16384)
		theAngle = -32768 - theAngle;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RowanToPan
//Author		Robert Slater
//Date			Fri 29 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::RowanToPan(SWord	&theAngle)
{
	if (theAngle > 16384)
		theAngle = 32768 - theAngle;
	
	if (theAngle < -16384)
		theAngle = -32768 - theAngle;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SequenceAudible
//Author		Robert Slater
//Date			Wed 3 Feb 1999
//
//Description	Scale morale to fit mood...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SequenceAudible(MoraleType	 morale,SLong vol,SLong fadeval)
{
	SLong	newmood = (MOOD_TOP - MOOD_BOTTOM)*morale;
	newmood /= (MORALE_TOPMORALE-MORALE_ROCKBOTTOM);
	newmood += MOOD_BOTTOM;

	Mood = (MoodSetting) newmood;

	SequenceAudible(FIL_MUSIC_MAIN,vol,fadeval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UIPlaySample
//Author		Robert Slater
//Date			Fri 12 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::UIPlaySample(FileNum	thefile,SLong vol)
{
	if (Save_Data.vol.uisfx)
	{
		SQueuePtr	ChannelPtr;										
		SQueuePtr	OldChannelPtr;									
		SampleRec*	SamplePtr;

		vol *= Save_Data.vol.uisfx;								//RJS 05Apr00
		vol >>= 7;												//RJS 05Apr00

		if (allowedsamples)											
		{
			SamplePtr = LoadSample(thefile,TRUE);
			if (SamplePtr)
			{
//DeadCode RJS 20Oct00 				SLong	spos = GetIndex(thefile);
				SLong	thepan = 0;
				SLong	thevol = (SamplePtr->samplevolume * vol) >> 7;
				vol = thevol;
				thevol >>= VOL_SCALE_SHIFT;								//RJS 14Sep00

				ChannelPtr = FindFreeHandlerUI(SamplePtr);	
				if (ChannelPtr)												
				{
					allowedsamples--;										
					SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,NULL);	
					ChannelPtr->handler->Play();
				}
			}
		}
	}

 	allowedsamples = status.nohandlers / 3;						//RJS 12Mar99
}

void	Sound::SequenceMute(SLong	fadeval)
{
//	if (!request.stopsequence)
	if ((request.activated & INT_STOPSEQUENCE)==0)				//RJS 18Jun99
	{
		fadeval *= 10;				//to millisecs
		if (FadeAll(fadeval))
		{
			request.activated &= ~INT_ON;
			request.activated |= INT_STOPSEQUENCE;					//RJS 18Jun99
			request.forcestop = 1;									//RJS 18Jun99
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreLoadSFX
//Author		Robert Slater
//Date			Thu 1 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PreLoadSFX()
{
	if (Save_Data.vol.sfx)
	{
//DeadCode RJS 6Oct00 		FreeSamples();

		SLong	thefile = FIL_SFX_COLLISION_BUILDING+directoryOffset;//RJS 30Aug00
		SLong	lastsnd = FIL_SFX_AMB_FIREENGINE+directoryOffset;		//RJS 14Jun00
		SLong	index;

//DeadCode RJS 25Sep00 		thefile++;
		for (index=thefile; index < lastsnd; index++)
		{
			FileNum	realname = FileNum(index-directoryOffset);			//RJS 14Jun00

			if (	(realname != FIL_SFX_LOOP_FX_START)					//RJS 14Jun00
				&&	(realname != FIL_SFX_LOOP_FX_END))					//RJS 14Jun00
				PreLoadFile(index);										//RJS 25Sep00
		}
	}

#ifndef	_NO_MUSIC_
	if (Save_Data.vol.music)
	{
		SLong	thedir = FIL_DIR_MUSIC+MusicDir;
		SLong	thefile;
		SLong	lastsnd = FIL_MUSIC_LAST_TUNE - FIL_DIR_MUSIC;
		SLong	index;

		for (index=1; index < lastsnd; index++)
		{
			thefile = FIL_DIR_MUSIC+index;
			if (	(thefile != FIL_MUSIC_STAND_ALONE)
 				&&	(thefile != FIL_MUSIC_PRIORITY)					  //DAW 07/05/99
				)
				PreLoadFile(thedir+index);
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreLoadRadioChatter
//Author		Robert Slater
//Date			Thu 1 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::PreLoadRadioChatter()
{
	Bool	retval = FALSE;
	if (Manual_Pilot.ControlledAC2)
	{
#ifndef	NDEBUG
	SLong	memused = FILEMAN.getTotalFileMemUsed();
#endif

#ifndef	_NO_RADIOCHATTER_
		if (Save_Data.vol.rchat)
		{
			rchatter_allowed = false;							//RJS 06Oct00

			if (FILEMAN.getTotalMem() >= RADIO_MEMORY_MIN)				//RJS 14Jun00
			{
				AirStrucPtr	ac = Manual_Pilot.ControlledAC2;
				Bool		playerLeader;
				Bool		haveFAC;
				SLong		thefile;
				SLong		theroot = FIL_DIR_RCHAT_RAFPLAYR;	//RJS 14Aug00

				SLong	pilots_raf[] = {	FIL_DIR_RCHAT_RAFPLAYR,
											FIL_DIR_RCHAT_PLYEXT,
											FIL_DIR_RCHAT_OTHER,
											FIL_DIR_RCHAT_OTHEXT,
											FIL_DIR_RCHAT_TOWER,
											FIL_DIR_RCHAT_GROUND,
											0	};

				SLong	pilots_luf[] = {	FIL_DIR_RCHAT_LWPLAYER,
											FIL_DIR_RCHAT_LWPLYEXT,
											FIL_DIR_RCHAT_LWOTHER,
											FIL_DIR_RCHAT_LWOTHEXT,
											FIL_DIR_RCHAT_LWTOWER,
											0	};

				SLong*	preloadptr = pilots_raf;				//RJS 16Aug100

// Choose nationality...
				bool	preLoadRAF = true;
				bool	preLoadLW = true;

				if (ac->nationality != NAT_RAF)
				{
					preloadptr = pilots_luf;
					preLoadRAF = false;
				}
				else
					preLoadLW = false;

				while (*preloadptr)
				{
					PreLoadChatChunk((*preloadptr)-theroot,preLoadRAF,preLoadLW);	//RJS 6Oct00
					preloadptr++;
				}

				retval = TRUE;

				rchatter_allowed = true;						//RJS 06Oct00
			}
#ifndef	NDEBUG
	memused = FILEMAN.getTotalFileMemUsed() - memused;
#endif
		}
#endif

	}

	return(retval);
}

void	Sound::PreLoadFile(SLong	thefile)
{
	fileblock (FileNum(thefile));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmackerOn
//Author		Dave Whiteside
//Date			Tue 6 Apr 1999
//
//Description	Vol toggle
//
//Inputs		
//
//Returns		smacker volume in 100*db
//
//------------------------------------------------------------------------------
SLong	Sound::SmackerOn(int	wind)
{
	_MsgBuffer.ClearRadio();

	if (dig)
	{
		ClearSoundQueue();

		dig->Close(&dig);
	}

	status.nohandlers = 0;

	//DeadCode JON 10Nov00 	MCIWndSetVolume(HWND(wind),(Save_Data.vol.anim*800)/125);

	usingSmacker = true;												//RJS 20Oct00

	return DigitalDriver::GetDecibels(Save_Data.vol.anim << VOL_SCALE_FROM_PREFS);	//RJS 13Nov00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmackerOff
//Author		Dave Whiteside
//Date			Tue 6 Apr 1999
//
//Description	Vol toggle
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SmackerOff(int	wind)
{
	if (usingSmacker)												//RJS 20Oct00
	{
		usingSmacker = false;											//RJS 20Oct00

		InitUI(wind);
	}
}

void	Sound::StopShooting()
{
	if (playerShooting)
	{
		Trans_Obj.ClearWeaponChain(Manual_Pilot.ControlledAC2);			//RJS 15Nov99
		if (!shootTimer)
		{
//DeadCode AMM 21Feb100 			if(Save_Data.flightdifficulty[FD_FF_GUN])	//CSB 05/07/99	
//DeadCode CSB 17Aug00 			if(Save_Data.hardwareconfig[HW_FF_GUN])	 //AMM 07/02/00
			if((_Analogue.FFdevice) && (_Analogue.FF_gun))
				_Analogue.FFshake.SetX(0,0,false);

			if (Save_Data.vol.sfx)
			{
				int	qpos;
				for (qpos = freechannelstart; qpos < status.nohandlers; qpos ++)
				{
					if (	(soundqueue[qpos].sampleindex == GunSampleIndex)
						&&	(soundqueue[qpos].worlditem == Manual_Pilot.ControlledAC2)	)
						HardStop(&soundqueue[qpos]);
				}
			}

			playerShooting = false;
		}
	}
}

Bool	Sound::StartShooting(FileNum	theSample,SLong shoottime,SLong	gunfreq)
{
	Bool	shootnow = FALSE;
	if (!playerShooting)
	{
//DeadCode AMM 21Feb100 		if(Save_Data.flightdifficulty[FD_FF_GUN])	//CSB 05/07/99	
//DeadCode CSB 17Aug00 		if(_Analogue.FFdevice)	 //AMM 07/02/00
		if((_Analogue.FFdevice) && (_Analogue.FF_gun))
		{
			int strength = (10000 * _Analogue.FF_gun) / 5;				//CSB 17Aug00
			_Analogue.FFshake.SetX(strength, gunfreq / 4, false);				  //RJS 31/05/99	//CSB 18/06/99	
		}

		shootTimer = shoottime;
		shootnow = TRUE;
		playerShooting = true;
		GunSampleIndex = &thesample[GetIndex(theSample)];
	}
	else
	{
		if (!shootTimer)
			shootTimer = shoottime;
	}

	return(shootnow);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreLoadMusicSamples
//Author		Robert Slater
//Date			Wed 14 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	Sound::PreLoadMusicSamples()
{
	Bool	retval = TRUE;
	if (Save_Data.vol.music)
	{
#ifndef	_NO_MUSIC_
		SLong	nosamples = FIL_MUSIC_LAST_SAMPLE-FIL_MUSIC_FIRST_SAMPLE;
		if (!themusicsample)
		{
			themusicsample = new SampleRec[nosamples];
			if (themusicsample)
			{
				SLong index;
				for (index=0; index < nosamples; index++)
					themusicsample[index].blockptr = NULL;

				setPercussion = TRUE;
			}

			nomusicsamples = 0;
		}

		if (themusicsample)
		{
			SLong		thedir = FIL_DIR_MUSICLOW;
			SLong		lastsnd = FIL_MUSIC_LAST_SAMPLE - FIL_DIR_MUSIC;
			SLong		firstsnd = FIL_MUSIC_FIRST_SAMPLE - FIL_DIR_MUSIC;
			SLong		index,realindex;
			SampleRec*	SamplePtr;
			char		header[10];
			char		*tmpptr;
			void		*tmpaddress;
			int			size;
			int			count;
			SLong		result = 1;
			RIFF		*header1;
			FMT			*header2;
			DATA		*header3;

			for (index=firstsnd; index < lastsnd; index++)
			{
				FileNum	thefile = (FileNum) (index+thedir);

				realindex= index-firstsnd;
				SamplePtr = &themusicsample[realindex];

				if (SamplePtr->blockptr==NULL)
				{
					SamplePtr->blockptr = new fileblock(thefile);
					if (SamplePtr->blockptr)
					{
						nomusicsamples++;

						SamplePtr->size = getsize(SamplePtr->blockptr);

						tmpaddress = getdata(SamplePtr->blockptr);

						tmpptr = (char*) tmpaddress;

						for (count = 0; count < 4; count ++)
							header[count] = *tmpptr++;
	
						header[4] = 0;

						if (	(strcmp(header,"RIFF") == 0)
							||	(strcmp(header,"Crea") == 0) )
						{
							header1 = (RIFF*) tmpaddress;
							header2 = (FMT*) header1->data;
		
							count = 0;								
							while (strnicmp(header2->FMT_string,"fmt ",4))
    						{
    							header2 = (FMT *) ((BYTE *) header2 +
			      						header2->chunk_size + 8 + (header2->chunk_size & 1));

								count++;										
								if (count >3)									
									break;										
    						}

							if (count > 3)
								SamplePtr->samplerate = CUR_SAMP_VAL;//RJS 14Jun00
							else
								SamplePtr->samplerate = header2->data.wf.nSamplesPerSec;

							header3 = (DATA*) header1->data;
							while (strnicmp(header3->DATA_string,"data",4))
	  						{
    							header3 = (DATA *) ((char *) header3 +
			      						header3->chunk_size + 8 + (header3->chunk_size & 1));
    						}

							SamplePtr->datasize = header3->chunk_size;
							SamplePtr->dataptr = (void*) header3->data;
						}
						else					
							SamplePtr->samplerate = 44100;

						SamplePtr->priority = 0;
					}
					else
					{
						nomusicsamples = 0;
						retval = FALSE;
						break;
					}
				}
			}
		}
		else
			retval = FALSE;
#else
		retval = FALSE;
#endif
	}
	else
		retval = FALSE;

	return (retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteMusicSamples
//Author		Robert Slater
//Date			Wed 14 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::DeleteMusicSamples()
{
	if (themusicsample)
	{
		SLong	nosamples = FIL_MUSIC_LAST_SAMPLE - FIL_MUSIC_FIRST_SAMPLE;
		SLong	index;

		for (index=0; index < nosamples; index++)
		{
			if (themusicsample[index].blockptr)
				delete themusicsample[index].blockptr;

			themusicsample[index].blockptr = NULL;
		}

		nomusicsamples = 0;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpRandomVoices
//Author		Robert Slater
//Date			Fri 21 May 1999
//
//Description	Called from radio chatter to reset preload with alternate voices
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetUpRandomVoices(SLong	fac, SLong	tower, SLong v2)
{
	randomFAC = fac;
	randomTOWER = tower;
	randomV2 = v2;

	donePreLoadRadio_2D = false;										//RJS 14Aug00
	donePreLoadRadio_3D = false;										//RJS 14Aug00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayWindyMiller
//Author		Robert Slater
//Date			Fri 21 May 1999
//
//Description	VEL SCALE :   1MS   = 10000 UNITS
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayWindyMiller(AirStrucPtr	ac)
{
#ifndef	_NOSOUNDIN3D_
	bool	notplayed = true;
	Float	fvelScale = (Float(ac->vel_) * 32768.) / 1500000. ;

//UpdateVEL	ULong	velscale = (ac->vel << 15)/1500;
	ULong	velscale = fastMath.DoubleToULong(fvelScale);				//RJS 9Jun00
	if (CockpitView && velscale && (allowedsamples || playingMiller))//RJS 07Jun99
	{
		AircraftAnimData*	adptr = (AircraftAnimData*) ac->Anim;
		ULong				acflaps = adptr->acflaps;
		ULong				acbreak = adptr->acbreak;
		ULong				acgear = adptr->acleglowerl;
		SLong				thevol;

		if (acbreak || acflaps || !acgear)
		{
			SampleRec*	SamplePtr = LoadSample(FIL_SFX_WIND_COCKPIT_LOOP);
			if (SamplePtr)
			{
				acgear = 255 - acgear;
				if (acgear > 128)	acgear = 128;

				acbreak += acflaps<<1;	//cos flaps are noisier
				acbreak += acgear;		
			
				if (velscale > 32768)
					velscale = 32768;

				thevol = acbreak * velscale;
				thevol >>= VOL_SCALE_SHIFT;								//RJS 14Sep00
				thevol *= 13000;
				thevol >>= 15;
				thevol /= 893;
				if (thevol)
				{
					SQueuePtr	OldChannelPtr;
					SQueuePtr	ChannelPtr;

					playingMiller = true;
					allowedsamples--;

					ClipVolume(thevol);									//RJS 14Sep00

					SLong	realvol = thevol<<VOL_SCALE_SHIFT;

					thevol = realvol;
					SoundInWorld(ItemPtr(NULL),thevol);

					notplayed = false;
					ChannelPtr = FindFreeHandler(SamplePtr,ac,OldChannelPtr);
					if (ChannelPtr)
					{
						SetUpSample(ChannelPtr,SamplePtr,realvol,thevol,0,ac);

						ChannelPtr->looping = TRUE;
						ChannelPtr->GameSound = FALSE;

						ChannelPtr->handler->SetLooping(0);
						ChannelPtr->handler->Play();
					}
					else
					{
						if (OldChannelPtr)
						{
							if (OldChannelPtr->handler->Status() == SMP_PLAYING)
							{
								OldChannelPtr->handler->SetVolume(thevol);
								if (Save_Data.hardwareconfig[HW_3DSOUND])			//RJS 12Jun00
									OldChannelPtr->handler->Set3DSource(*theSubject);	//RJS 12Jun00
							}
						}
					}
				}
			}
		}
	}

	if (notplayed && playingMiller)
	{
		StopSample(FIL_SFX_WIND_COCKPIT_LOOP,ac);
		playingMiller = false;
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSysTime
//Author		Andy McMaster
//Date			Fri 11 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE AMM 14/01/00 ULong		Sound::GetSysTime()
//DEADCODE AMM 14/01/00 {
//DEADCODE AMM 14/01/00 	return timeGetTime();
//DEADCODE AMM 14/01/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayDelayed
//Author		Robert Slater
//Date			Wed 16 Aug 1999
//
//Description	Log a sample to be played from a different thread, if it is not
//				already playing.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayDelayed(FileNum	thefile, ItemPtr	theitm,SLong vol,Bool looped,FileNum	stsam, FileNum	endsam)
{
#ifndef	_NOSOUNDIN3D_
	if (Save_Data.vol.sfx && thefile != FIL_NULL)						//RJS 9Jun00
	{
//DeadCode RJS 16Oct00 		int	spos = GetIndex(thefile);
//DeadCode RJS 16Oct00 
//DeadCode RJS 16Oct00 		SampleRec*	SamplePtr = &thesample[spos];
//DeadCode RJS 16Oct00 
//DeadCode RJS 16Oct00 		for (int count = freechannelstart; count < status.nohandlers; count ++)
//DeadCode RJS 16Oct00 		{
//DeadCode RJS 16Oct00 			if (	(soundqueue[count].sampleindex == SamplePtr)
//DeadCode RJS 16Oct00 				&&	(soundqueue[count].worlditem == theitm)	)
//DeadCode RJS 16Oct00 				return;
//DeadCode RJS 16Oct00 		}

		delayedsounds.Add(thefile,theitm,vol,looped,stsam,endsam,true);
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPercussion
//Author		Robert Slater
//Date			Wed 18 Aug 1999
//
//Description	Play percussion sample that has been logged by a midi event.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ProcessPercussion()
{
	if (percussionLog.sampleindex > -1)
	{
		SQueuePtr	ChannelPtr = &soundqueue[channel_percussion];
		HSAMPLE		handler = ChannelPtr->handler;
		SLong		volume = percussionLog.volume;

		if (ChannelPtr->sampleindex)
		{
			if (handler->Status()!=SMP_DONE)
				handler->End();
		}

		ChannelPtr->sampleindex = &themusicsample[percussionLog.sampleindex];

		if (handler->LoadBuffer(	ChannelPtr->sampleindex->wavheader->data,
									ChannelPtr->sampleindex->dataptr,
									ChannelPtr->sampleindex->datasize)	)
		{
			//Balance the percussion volume between 3d sample and music volume...
			volume *= percvolscale;
			volume >>= VOL_SCALE_SHIFT;									//RJS 14Sep00

			handler->SetVolume(volume);
			handler->Play();
		}

		percussionLog.sampleindex = -1;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MultiMediaError
//Author		Robert Slater
//Date			Mon 8 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::MultiMediaError(ULong	midiRes)
{
#ifdef	_MMREPORTERROR_
	if (midiRes != MMSYSERR_NOERROR)
	{
		switch (midiRes)
		{
		case MMSYSERR_BADDEVICEID:
			MessageBox (NULL, "The specified device identifier is out of range.", "MIDI", MB_OK);
			break;
		case MMSYSERR_INVALPARAM:
			MessageBox (NULL, "The specified pointer or structure is invalid.", "MIDI", MB_OK);
			break;
		case MMSYSERR_NODRIVER:
			MessageBox (NULL, "The driver is not installed.", "MIDI", MB_OK);
			break;
		case MMSYSERR_NOMEM:
			MessageBox (NULL, "The system is unable to load mapper string description.", "MIDI", MB_OK);
			break;
		default:
			MessageBox (NULL, "No MIDI Card?", "MIDI", MB_OK);
			break;
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SoundInWorld
//Author		Robert Slater
//Date			Wed 12 Jan 2000
//
//Description	Top level call to calculate pan & vol for an item
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	Sound::SoundInWorld(const ItemPtr	theItem, SLong	&vol)
{
	SLong	pan;
	SLong	vx,vy,vz;													//RJS 15Sep00

	if (theItem)
	{
		if (Save_Data.hardwareconfig[HW_3DSOUND])
		{
#ifndef	_NOVELOCITY_
			if (theItem->Status.size >= MOBILESIZE)
			{
				mobileitem*	mitem = (mobileitem*)theItem;

				vx = mitem->vel_x;
				vy = mitem->vel_y;
				vz = mitem->vel_z;
			}
			else
#endif
			{
				vx = vy = vz = 0;
			}

			pan = 0;
			vol >>= VOL_SCALE_SHIFT;			// scale to 511

			ClipVolume(vol);											//RJS 16Sep00

			SetSubject(	theItem->World,
						vx,
						vy,
						vz,
						vol	);
		}
		else
			SoundInWorld(theItem->World,vol,pan);
	}
	else
	{
		GetEyeVelocity(vx,vy,vz);					//RJS 15Sep00

		pan = 0;														//RJS 12Jun00
		vol >>= VOL_SCALE_SHIFT;										//RJS 14Sep00

		SetSubject(	eyeWorld,
					vx,
					vy,
					vz,
					vol	);
	}

	return pan;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSubject
//Author		Robert Slater
//Date			Wed 12 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetSubject(Coords3D&	pos, SLong vx, SLong vy, SLong vz, SLong vol)
{
	theSubject->x = D3DVALUE(pos.X);
	theSubject->y = D3DVALUE(pos.Y);
	theSubject->z = D3DVALUE(pos.Z);
	theSubject->vx = float(vx) * VEL_SCALE;
	theSubject->vy = float(vy) * VEL_SCALE;
	theSubject->vz = float(vz) * VEL_SCALE;
	theSubject->volume = vol;
	theSubject->mindistance = MIN_DISTANCE;//1000;
	theSubject->maxdistance = MAX_DISTANCE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetListener
//Author		Robert Slater
//Date			Wed 12 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetListener(ViewPoint*	vp)
{
	if (vp && Manual_Pilot.ControlledAC2 && Save_Data.hardwareconfig[HW_3DSOUND])
	{
		mobileitem*	mitem;
		SLong		vx,vy,vz;
		Float		sin_ang, cos_ang;
		Float		hsin_ang, hcos_ang;
		Float		ori_y, ori_x, ori_z, ori_h;

		GetEyeVelocity(vx,vy,vz);							//RJS 15Sep00

		theListener->x = D3DVALUE(eyeWorld.X);
		theListener->y = D3DVALUE(eyeWorld.Y);
		theListener->z = D3DVALUE(eyeWorld.Z);
		theListener->vx = float(vx) * VEL_SCALE;
		theListener->vy = float(vy) * VEL_SCALE;
		theListener->vz = float(vz) * VEL_SCALE;
		theListener->front_vecx = eyeVector_x;
		theListener->front_vecy = eyeVector_y;
		theListener->front_vecz = eyeVector_z;

		Math_Lib.high_sin_cos(Angles(eyePitch+ANGLES_90Deg),sin_ang,cos_ang);	//RJS 16Sep00

		ori_y = sin_ang;
		ori_h = cos_ang;

		ori_x = ori_h * eyeVector_x;//hsin_ang;
		ori_z = ori_h * eyeVector_z;//hcos_ang;

		theListener->top_vecx = D3DVALUE(ori_x);
		theListener->top_vecy = D3DVALUE(ori_y);
		theListener->top_vecz = D3DVALUE(ori_z);

		dig->Set3DListener(*theListener);
	}
}

void	Sound::Commit()
{
	dig->DirectSound_Commit();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UIPlayAmbient
//Author		Robert Slater
//Date			Mon 8 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::UIPlayAmbient(SLong sfxTrigger)
{
	if (Save_Data.vol.anim)										//RJS 02Jun00
	{
		if (	(sfxTrigger != SFX_NULL)
			&&	(ambientCnt < status.nohandlers)	)
		{
			ambientList[ambientCnt] = sfxTrigger;
			ambientCnt++;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UIProcessAmbience
//Author		Robert Slater
//Date			Mon 8 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::UIProcessAmbience()
{
	if (Save_Data.vol.anim)										//RJS 02Jun00
	{	
		SampleRec*	SamplePtr;
		SLong		vol;
		FileNum		thefile = FIL_NULL;
		SLong		randsample;

		for (int amb=0; amb<ambientCnt; amb++)
		{
			vol = 128;
			switch (ambientList[amb])
			{
			case SFX_PhoneIn:
				thefile = FIL_SFX_OFFICE_TELEPHONE;
			break;
			case SFX_PhoneOut:
				thefile = FIL_SFX_OFFICE_PICKUPPHONE;
			break;
			case SFX_TeleType:
				thefile = FIL_SFX_OFFICE_TELETYPE;
			break;
			case SFX_AlertRaid:
				thefile = FIL_SFX_OFFICE_MUTED_SIREN;
			break;
			case SFX_AlertScramble:
				thefile = FIL_SFX_OFFICE_MUTED_SIREN;
			break;
			case SFX_OfficeAmbience:
			{
				vol = 32;

				UWord	rand = Math_Lib.rnd();
				if (rand > 11000)
				{
					if (rand > 60000)
					{
						if (rand > 64000)
						{
							rand-=64000;
							thefile = FileNum(FIL_SFX_OFFICE_DOOR_OPEN+((rand*2)/1536));
						}
						else
						{
							rand-=60000;
							thefile = FileNum(FIL_SFX_OFFICE_CHAIR1+((rand*4)/5536));
						}
					}
				}
				else
					thefile = FIL_SFX_OFFICE_TELEPHONE;
			}
			break;
			}

			if (thefile != FIL_NULL)
			{
				vol *= Save_Data.vol.anim;						//RJS 02Jun00
				vol >>= 7;

				SamplePtr = LoadSample(thefile,TRUE);
				if (SamplePtr)
				{
					SQueuePtr	ChannelPtr;										
					SQueuePtr	OldChannelPtr;	
					SLong		spos = GetIndex(thefile);
					SLong		thepan = 0;
					SLong		thevol = (SamplePtr->samplevolume * vol) >> 7;
					int			stblock = spos - 1;										
					int			endblock = spos + 1;										

					vol = thevol;
					thevol >>= VOL_SCALE_SHIFT;							//RJS 14Sep00

//DeadCode RJS 20Jun00 					ChannelPtr = FindFreeHandlerUI(SamplePtr);	
					ChannelPtr = FindFreeHandlerOnce(SamplePtr,NULL,OldChannelPtr,stblock,endblock);
					if (ChannelPtr)												
					{
						SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,NULL);	
						ChannelPtr->handler->Play();
					}
				}
			}
		}

		ambientCnt = 0;

		PlayLooped(FIL_SFX_OFFICE_CONVERSATION_RAF,NULL,Save_Data.vol.anim);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayRestart
//Author		Robert Slater
//Date			Tue 13 Jun 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayRestart(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol,FileNum	stsam, FileNum	endsam)
{
#ifndef	_NOSOUNDIN3D_

	SQueuePtr	ChannelPtr;										
	SampleRec*	SamplePtr;										
	int			spos;
	int	stblock = 0;
	int	endblock = 0;
	SLong	thevol;												
	int	thepan;													

	SamplePtr = LoadSample(thefile);
	if (SamplePtr)
	{
		if (allowedsamples || (sampleitem == Manual_Pilot.ControlledAC2))
		{
			thevol = (SamplePtr->samplevolume * vol) >> 7;			
			vol = thevol;											

			spos = GetIndex(thefile);
			stblock = spos - 1;										
			endblock = spos + 1;									

			if (	(stsam != FIL_NULL)
				&&	(endsam != FIL_NULL)	)
			{
				stblock = GetIndex(stsam) - 1;
				endblock = GetIndex(endsam) + 1;
			}

			thepan = SoundInWorld(ItemPtr(sampleitem),thevol);			//RJS 12Jan00

			if (thevol)													
			{
				SQueuePtr	OldChannelPtr;

				ChannelPtr = FindFreeHandlerRestart(SamplePtr,sampleitem,stblock,endblock);
				if (ChannelPtr)			   
				{
					allowedsamples--;	   

					SetUpSample(ChannelPtr,SamplePtr,vol,thevol,thepan,sampleitem);

					ChannelPtr->handler->Play();
				}
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PlayRestart
//Author		Robert Slater
//Date			Tue 13 Jun 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PlayRestart(FileNum	thefile, SLong	vol, SLong thepan)
{
	PlayRestart(thefile,ItemPtr(NULL),vol);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreLoadChatChunk
//Author		Robert Slater
//Date			Mon 14 Aug 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::PreLoadChatChunk(SLong	diroffset, bool preLoadRAF, bool preLoadLW)
{
	if (preLoadChatStatus && !_Replay.Playback)							//RJS 25Sep00
	{
		FileNum theDir = FileNum(FIL_DIR_RCHAT_RAFPLAYR + diroffset);	//RJS 30Aug00
		if (	(theDir == FIL_DIR_RCHAT_VOICE2)
			||	(theDir == FIL_DIR_RCHAT_LWVOICE2)	)
			PreLoadFile(diroffset+FIL_RCHAT_VOICE2);
		else
		{
//DeadCode RJS 6Oct00 			bool	preLoadRAF = true;							//RJS 30Aug00
//DeadCode RJS 6Oct00 			bool	preLoadLW = true;							//RJS 30Aug00
//DeadCode RJS 6Oct00 			if (Manual_Pilot.ControlledAC2)
//DeadCode RJS 6Oct00 			{
//DeadCode RJS 6Oct00 				if (Manual_Pilot.ControlledAC2->nationality == NAT_RAF)
//DeadCode RJS 6Oct00 					preLoadLW = false;
//DeadCode RJS 6Oct00 				else
//DeadCode RJS 6Oct00 					preLoadRAF = false;
//DeadCode RJS 6Oct00 			}

			if (preLoadLW)
			{
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_GLW);
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_LWSN);
				PreLoadFile(diroffset+FIL_RCHAT_LWPLAYER);
				PreLoadFile(diroffset+FIL_RCHAT_LWPILOT);
				PreLoadFile(diroffset+FIL_RCHAT_LWTOTALPILOT);
			}

			if (preLoadRAF)
			{
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_GWINGRAF);
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_GSQUADRAF);
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_GFIGHTERS);
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_GL_RAF);
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_GFLIGHTRAF);
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_GSECTIONRAF);
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_RAFSN);
				PreLoadFile(diroffset+FIL_RCHAT_RAFPILOT);
				PreLoadFile(diroffset+FIL_RCHAT_RAFPILOT_GROUND);
			}

// These are silent, so no preload...

//DeadCode RJS 30Aug00 			PreLoadFile(diroffset+FIL_RCHAT_GESCHWADERTYPE);
//DeadCode RJS 30Aug00 			PreLoadFile(diroffset+FIL_RCHAT_GESCHWADERTYPEABBREV);
//DeadCode RJS 30Aug00 			PreLoadFile(diroffset+FIL_RCHAT_GESCHWADERNUMBERSHORT);
//DeadCode RJS 30Aug00 			PreLoadFile(diroffset+FIL_RCHAT_ROMANNUMBERS);
//DeadCode RJS 30Aug00 			PreLoadFile(diroffset+FIL_RCHAT_BRITHISTORICBAND);
//DeadCode RJS 30Aug00 			PreLoadFile(diroffset+FIL_RCHAT_P_SILENT);
//DeadCode RJS 30Aug00 			PreLoadFile(diroffset+FIL_RCHAT_P_SLNTARCHIVE);
//DeadCode RJS 30Aug00 			PreLoadFile(diroffset+FIL_RCHAT_P_SLNTBITMAP);

			if (theDir == FIL_DIR_RCHAT_GROUND)
			{
				PreLoadFile(diroffset+FIL_RCHAT_CALLEE_GRAF);
				PreLoadFile(diroffset+FIL_RCHAT_SQUADRONNUMBER);
				PreLoadFile(diroffset+FIL_RCHAT_P_GROUND);
			}

			if (	(theDir == FIL_DIR_RCHAT_GROUND)
				||	(theDir == FIL_DIR_RCHAT_FEMALE)	)
			{
				PreLoadFile(diroffset+FIL_RCHAT_HDGCARDINAL);
				PreLoadFile(diroffset+FIL_RCHAT_CITYBAND);
				PreLoadFile(diroffset+FIL_RCHAT_TOWNBAND);
				PreLoadFile(diroffset+FIL_RCHAT_NAVIGATIONBAND);
				PreLoadFile(diroffset+FIL_RCHAT_P_GRNDSTAFF);

			}

			if (	(theDir == FIL_DIR_RCHAT_GROUND)
				||	(theDir == FIL_DIR_RCHAT_FEMALE)
				||	preLoadRAF							)
			{
				PreLoadFile(diroffset+FIL_RCHAT_RAF_FIGHTERAFBAND);
				PreLoadFile(diroffset+FIL_RCHAT_RAF_BOMBERAFBAND);
			}

			if (theDir == FIL_DIR_RCHAT_FEMALE)
			{
				PreLoadFile(diroffset+FIL_RCHAT_SECTOROPSBAND);
				PreLoadFile(diroffset+FIL_RCHAT_DOCKSBAND);
				PreLoadFile(diroffset+FIL_RCHAT_CLRADARBAND);
				PreLoadFile(diroffset+FIL_RCHAT_CHRADARBAND);
				PreLoadFile(diroffset+FIL_RCHAT_BRITBOATBAND);
				PreLoadFile(diroffset+FIL_RCHAT_INDUSTRYBAND);
				PreLoadFile(diroffset+FIL_RCHAT_AIRCRAFTFACTORYBAND);
				PreLoadFile(diroffset+FIL_RCHAT_FEMALE);
			}

			if (	(theDir == FIL_DIR_RCHAT_FEMALE)
				||	preLoadLW	)
				PreLoadFile(diroffset+FIL_RCHAT_LUF_FIGHTERLF2BAND);

			PreLoadFile(diroffset+FIL_RCHAT_PUNCTUATION);
			PreLoadFile(diroffset+FIL_RCHAT_RANGESCLOSE);
			PreLoadFile(diroffset+FIL_RCHAT_NUMBER);
			PreLoadFile(diroffset+FIL_RCHAT_FIFTIES);
			PreLoadFile(diroffset+FIL_RCHAT_HDGOCLOCK);
			PreLoadFile(diroffset+FIL_RCHAT_RELPOSITION);
//DeadCode RJS 6Oct00 			PreLoadFile(diroffset+FIL_RCHAT_LUF_FIGHTERLF2BAND);
//DeadCode RJS 6Oct00 			PreLoadFile(diroffset+FIL_RCHAT_RAF_FIGHTERAFBAND);
//DeadCode RJS 6Oct00 			PreLoadFile(diroffset+FIL_RCHAT_RAF_BOMBERAFBAND);
			PreLoadFile(diroffset+FIL_RCHAT_GROUNDCONTROLLERLW);
			PreLoadFile(diroffset+FIL_RCHAT_GROUNDCONTROLLERRAF);
			PreLoadFile(diroffset+FIL_RCHAT_ONE_AIRCRAFT);
			PreLoadFile(diroffset+FIL_RCHAT_ONE_AIRCRAFT_EXCLAIM);
			PreLoadFile(diroffset+FIL_RCHAT_PLURAL_AIRCRAFT);
			PreLoadFile(diroffset+FIL_RCHAT_PLURAL_AIRCRAFT_EXCLAIM);
			PreLoadFile(diroffset+FIL_RCHAT_USER_DEFINED);
			PreLoadFile(diroffset+FIL_RCHAT_PLAYERNAMES);
			PreLoadFile(diroffset+FIL_RCHAT_P_TOWER);
			PreLoadFile(diroffset+FIL_RCHAT_P_GROUNDTOWER);
			PreLoadFile(diroffset+FIL_RCHAT_PLAYER);
			PreLoadFile(diroffset+FIL_RCHAT_EXCITED_PLAYER);
			PreLoadFile(diroffset+FIL_RCHAT_EXCITED_OTHER);
			PreLoadFile(diroffset+FIL_RCHAT_PILOT);
			PreLoadFile(diroffset+FIL_RCHAT_EXCITED);
//DeadCode RJS 6Oct00 			PreLoadFile(diroffset+FIL_RCHAT_LWTOTALPILOT);
			PreLoadFile(diroffset+FIL_RCHAT_TOTALPILOT);
			PreLoadFile(diroffset+FIL_RCHAT_OTHER);
			PreLoadFile(diroffset+FIL_RCHAT_ALLBUT_TVFGC);
			PreLoadFile(diroffset+FIL_RCHAT_ALLBUT_VF);
			PreLoadFile(diroffset+FIL_RCHAT_PILOT_GROUND);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChatterStatus
//Author		Robert Slater
//Date			Fri 15 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ChatterStatus(bool	preLoadFlag)
{
	preLoadChatStatus = preLoadFlag;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipVolume
//Author		Robert Slater
//Date			Fri 15 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void	Sound::ClipVolume(SLong& theVol)							//RJS 14Sep00
{
	if (theVol > VOL_TOP_CLIP)
		theVol = VOL_TOP_CLIP;
	else
	{
		if (theVol < VOL_BOT_CLIP)
			theVol = VOL_BOT_CLIP;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetEyeVelocity
//Author		Robert Slater
//Date			Fri 15 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void	Sound::GetEyeVelocity(SLong& vx, SLong& vy, SLong& vz)
{
#ifndef	_NOVELOCITY_
	vx = eyeVelocity.X;
	vy = eyeVelocity.Y;
	vz = eyeVelocity.Z;
#else
	vx = vy = vz = 0;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpListener
//Author		Robert Slater
//Date			Fri 15 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::SetUpListener(const ItemPtr	trackeditem,
							 const ULong& viewer_x, const ULong& viewer_y, const ULong& viewer_z,
							 const float& eye_x, const float& eye_y, const float& eye_z,
							 const ANGLES&	hdg,	const ANGLES& pitch)
{
	if (trackeditem && (trackeditem->Status.size >= MOBILESIZE))
	{
		eyeVelocity.X = MobileItemPtr(trackeditem)->vel_x;
		eyeVelocity.Y = MobileItemPtr(trackeditem)->vel_y;
		eyeVelocity.Z = MobileItemPtr(trackeditem)->vel_z;
	}
	else
	{
		eyeVelocity.X = eyeVelocity.Y = eyeVelocity.Z = 0;
	}

	eyeWorld.X = SLong(viewer_x);
	eyeWorld.Y = SLong(viewer_y);
	eyeWorld.Z = SLong(viewer_z);

	eyeVector_x = eye_x;
	eyeVector_y = eye_y;
	eyeVector_z = eye_z;

	eyeHdg = SWord(hdg);
	eyePitch = SWord(pitch);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPriority
//Author		Robert Slater
//Date			Fri 22 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline	void	Sound::SetPriority(const SQueuePtr	ChannelPtr,SLong& vol)
{
	ClipVolume(vol);

	ChannelPtr->playingpriority = ChannelPtr->sampleindex->priority + ((511-vol)>>6);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdatePriority
//Author		Robert Slater
//Date			Fri 22 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline	void	Sound::UpdatePriority(const SQueuePtr	ChannelPtr, const int& count, SLong& lowest, SLong& lowpos)
{
	if (!ChannelPtr->highPriority)
	{
		ChannelPtr->playingpriority++;					

		if (ChannelPtr->playingpriority > lowest)		
		{
			lowest = ChannelPtr->playingpriority;
			lowpos = count;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Clean
//Author		Robert Slater
//Date			Fri 22 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	PlayingRec::Clean()
{
	sampleindex = NULL;					
	looping = false;						
	worlditem = NULL;					
	GameSound = false;					
	isRadio = false;
	highPriority = false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearSoundQueue
//Author		Robert Slater
//Date			Thu 28 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::ClearSoundQueue()
{
	if (soundqueue)
	{
		int	count;
		for (count=0; count < status.nohandlers; count++)
		{
			soundqueue[count].handler->Release();
			soundqueue[count].handler = NULL;
		}

		delete []soundqueue;
		soundqueue = NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetEngineVol
//Author		Robert Slater
//Date			Thu 28 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int		Sound::GetEngineVol()
{
	return ((EngineSound.SubHarmonicVolume + EngineSound.RumbleVolume) >> 8);
}

void	Sound::GoingToMapScreen()
{
#ifndef	_NO_RADIOCHATTER_
	if (!donePreLoadRadio_2D)
	{
		if (Save_Data.vol.rchat)
		{
			if (FILEMAN.getTotalMem() >= (RADIO_MEMORY_MIN>>2))
			{
				donePreLoadRadio_2D = true;

#ifndef	NDEBUG
				naughtynaughty = false;
#endif
				PreLoadChatChunk(FIL_DIR_RCHAT_GROUND-FIL_DIR_RCHAT_RAFPLAYR);
				PreLoadChatChunk(FIL_DIR_RCHAT_FEMALE-FIL_DIR_RCHAT_RAFPLAYR);
			}
		}
	}
#else
	Save_Data.vol.rchat = 0;
	rchatter_allowed = false;
#endif
#ifndef	NDEBUG
	naughtynaughty = false;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StopItemSamples
//Author		Robert Slater
//Date			Tue 10 Oct 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::StopItemSamples(ItemBasePtr	theItem)
{
	if (Save_Data.vol.sfx)
	{
		int			count;
		SQueuePtr	ChannelPtr = soundqueue;

		for (count = 0; count < status.nohandlers; count++)	
		{		
			if (	ChannelPtr->sampleindex
				&&	(ChannelPtr->worlditem == theItem)	)
				HardStop(ChannelPtr);						

			ChannelPtr++;									
		}		
	}
}

void	Sound::PlayAnyDelayed(FileNum	thefile, ItemPtr	theitm,SLong vol,Bool looped,FileNum	stsam, FileNum	endsam)
{
#ifndef	_NOSOUNDIN3D_
	if (Save_Data.vol.sfx && thefile != FIL_NULL)						//RJS 9Jun00
		delayedsounds.Add(thefile,theitm,vol,looped,stsam,endsam);
#endif
}

void	LogSoundRec::Add(FileNum p1, ItemBasePtr	p2, SLong p3, Bool lp, FileNum p4, FileNum p5, bool p6)
{
	if (p2 && (p2->Status.size == TRANSIENTSIZE))
		isSet = FALSE;
	else
	{
		isSet = TRUE;
		thefile = p1;
		theitem = p2;
		vol = p3;
		isLooped = lp;
		sfile = p4;
		efile = p5;
		isOnce = p6;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloseDownSmall
//Author		Robert Slater
//Date			Thu 16 Nov 2000
//
//Description	Used for edge-case protection...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Sound::CloseDownSmall()
{
	status.nohandlers = 0;											//RJS 16Nov00
	Save_Data.vol.sfx = 0;

	dig->Close(&dig);
}
