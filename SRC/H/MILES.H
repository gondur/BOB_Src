//------------------------------------------------------------------------------
//Filename       Sound.h
//System         
//Author         Robert Slater
//Date           Fri 1 Mar 1996
//Description	Header file for the Sound midi and sample library    
//------------------------------------------------------------------------------
#ifndef	Sound_Included
#define	Sound_Included

#define	DEFAULT_Sound 0

typedef struct SmackTag Smack;		//RJS 13Apr99
struct	EnginePlayInfo;											//RJS 21Oct97
struct	SequenceStruct;
typedef SequenceStruct *TuneStrucP;
struct	MusicRequest;
struct	SampleLibrary;
struct	SampleRec;
struct	PlayingRec;		
struct	StatusRec;											
struct	SampleRequest;
typedef PlayingRec *SQueuePtr;									//RJS 17Oct97
typedef SLong     HTIMER;            // Handle to timer
#include	"fileman.h"
class	ItemBase;
typedef ItemBase		*ItemBasePtr;							//JIM 14Feb96
class	rotitem;
typedef rotitem			*RotItemPtr;
struct	PlaneType;
typedef	PlaneType	*ClassPtr;
#include	"flyinit.h"
	struct	SampleRequest
	{
		FileNum	thesample;
		SLong	vol;
		SLong	pan;
	};

	enum	SpotEffects
	{
		SPOT_FRIENDLY_KILLED	=	0,
		SPOT_PLAYER_IN_DANGER	=	1,
		SPOT_PLAYER_GETS_HIT	=	2,
		SPOT_PLAYER_MAKES_HIT	=	3,
		SPOT_PLAYER_MAKES_KILL	=	4
	};

enum	MoodSetting												//RJS 30Jun98
{
	MOOD_TOP	= 127,											//RJS 03Feb99
	MOOD_HERO	= MOOD_TOP,										//RJS 03Feb99
	MOOD_CONFIDENT = 84,
	MOOD_HOPEFUL = 42,
	MOOD_NEUTRAL = 0,
	MOOD_TENSE = -26,
	MOOD_ANGRY = -52,
	MOOD_TROUBLED =	-78,
	MOOD_DESPERATE = -104,
	MOOD_DOOMED	= -128,
	MOOD_BOTTOM = MOOD_DOOMED
};																//RJS 30Jun98

enum	MoodDelta												//RJS 30Jun98
{
	MOOD_DOWN = -2,
	MOOD_NOCHANGE = 0,
	MOOD_UP = 2
};																//RJS 30Jun98

enum	SoundType												//RJS 08Sep98
{																//RJS 08Sep98
	SOUND_DIGITAL = 0,											//RJS 08Sep98
	SOUND_MIDI,													//DAW 18Aug99
	SOUND_RADIO												//DAW 18Aug99
};																//RJS 08Sep98

struct	EngineInfo												//RJS 13Jan00
{
	UByte	power;			// 0 = none 255 = full
	UByte	rattle;			// 0 = none 255 = very frequent
	SWord	rpm_engine;
	SWord	rpm_starter;
	SWord	xoffset;		// cm
	SLong	velocity;		// for wind vol calc
	SWord	cockpitnobble;	// for canopy damage
};

struct	PercRec
{
	SLong	sampleindex;
	SLong	volume;

public:
	PercRec()	{Reset();}

	void	Reset()
	{
		sampleindex = -1;
		volume = 0;
	}
};

class	Music;													//RJS 08Nov99
class	DigitalDriver;											//RJS 08Nov99

class SoundBase
{
public:
	Bool	incombat;											//RJS 12Nov96
	int		allowedsamples;										//RJS 03Dec96
	int	MusicDir;
	SByte	Mood;												//RJS 03Apr97
	SLong	noTracks;											//RJS 26Feb98
	char*	digerror;
 	Music*			mdi;
	DigitalDriver*	dig;
	ULong	currWin;

	enum
	{
		MAXTUNES 		= 35,									//RJS 30Aug96
		MAXSEQUENCES 	= 16,
		MAXHANDLERS 	= 16,									//JIM 25Jul96
		MAXSAMPLES 		= 256,									//MS 23Sep98
		PRIORITYFACTOR	= 8
	};

	enum	HSampRate
	{
		MIN_SAMP_VAL	= 11025,								//RJS 30Oct96
		NOM_SAMP_VAL	= 22050,								//RJS 30Oct96
		MAX_SAMP_VAL	= 44100									//RJS 30Oct96
	};

	enum	TuneType
	{
		T_main			=	0,
		T_spoteffects,											//RJS 06May99
		T_seqeffects, 											//RJS 06May99
		T_independent,											//RJS 06May99
		T_independent_pri										//RJS 06May99
	};

	enum	CBTCodes
	{
		CODE_JUMP1		=	1,
		CODE_JUMP2,
		CODE_JUMP3,
		CODE_STANDALONE,
		CODE_SFX,
		CODE_SPECIAL	=	12,
		CODE_HIPRIORITY	=	125,
		CODE_LOPRIORITY	=	126,
		CODE_STOP		=	127
	};

	enum	CBTCodesLo
	{
		CODE_SFX_VOL = 0,
		CODE_SFX_PAN,
		CODE_SFX_BAR
	};

///////////////////

	static	SequenceStruct	tune[MAXTUNES];
	static	MusicRequest	request;
	static	SampleLibrary	wavetable;
	static	SampleRec		*thesample;							//MS 23Sep98
//DeadCode MS 23Sep98 	static	SampleRec		thesample[MAXSAMPLES];
//DeadCode RJS 01Jun98 	static	SampleRec		radiosamples[MAXSAMPLES];				//RJS 19Dec97
	static	PlayingRec*		soundqueue;
	static	StatusRec		status;
	static	HTIMER			timer;
	static	SampleRequest	soundtoplay;
	static	EnginePlayInfo	EngineSound;						//RJS 21May98

	static  Bool			canplaynothing;						//RJS 21May98
	static  Bool			critical;							//RJS 21May98
	static  Bool			inprefs;							//RJS 21May98
	static  Bool			onground;							//RJS 21May98
	static  Bool			musicstopped;						//RJS 21May98
	static 	int				damagelevel;						//RJS 21May98
	static 	int				delindex;							//RJS 21May98
	static	int				thesmackervol;						//RJS 21May98
	static	FileNum			currentengine;						//RJS 21May98
	static	int				bouncecount;						//RJS 21May98
	static	SLong			MAXSAMPLES_LOADED;					//MS 23Sep98
	static	SampleRec		*themusicsample;					//RJS 14Apr99
	static	SLong			percvolscale;						//RJS 29Jun99
	static	PercRec			percussionLog;						//RJS 18Aug99

	static	HSampRate		CUR_SAMP_VAL;						//RJS 14Jun00
	static	float			sampRateScale;						//RJS 14Jun00
	static	int				directoryOffset;							//RJS 14Jun00
};

struct	LogSoundRec
{
	ItemBasePtr	theitem;
	FileNum		thefile;
	Bool		isLooped;
	Bool		isSet;
	SLong		vol;
	FileNum		sfile;
	FileNum		efile;
	bool		isOnce;

public:
	LogSoundRec()
	{
		isSet = FALSE;
	}

	void	Add(FileNum p1, ItemBasePtr	p2, SLong p3, Bool lp, FileNum p4, FileNum p5, bool p6=false);

	Bool	Get(FileNum& p1, ItemBasePtr&	p2, SLong& p3, Bool& lp, FileNum& p4, FileNum& p5, bool& p6)
	{
		if (isSet)
		{
			isSet = FALSE;

			p1 = thefile;
			p2 = theitem;
			p3 = vol;
			p4 = sfile;
			p5 = efile;
			lp = isLooped;
			p6 = isOnce;

			return TRUE;
		}
		return FALSE;
	}
};

struct	SubjectStruc;											//RJS 12Jan00
struct	ListenerStruc;											//RJS 12Jan00
class	ViewPoint;												//RJS 25May99
class	fileblock;
class	mobileitem;
class	item			;
class	AirStruc		;
typedef item			Item,*ItemPtr,*itemptr;
typedef	AirStruc		*AirStrucPtr;

class Sound:public SoundBase
{
//DeadCode RJS 07Jun99 	Bool		CockpitView;
	void*		pooMidiDev;
	SLong		bestDrivers[16];
	ULong		uDriverID;
	bool		trySoundFonts;

	SLong		freechannelstart;
	SLong		lastBuffetVol;									//RJS 28Jan99
	bool		donePreLoad;
	bool		playerShooting;									//RJS 12Apr99
	SampleRec*	GunSampleIndex;									//RJS 12Apr99
	SLong		shootTimer;

	bool		havePercussion;									//RJS 14Apr99
	bool		setPercussion;									//RJS 14Apr99
	SLong		nomusicsamples;									//RJS 14Apr99
	SLong		channel_percussion;
	SLong		channel_radiochatter;

	void		PreLoadSFX();
	Bool		PreLoadRadioChatter();
	Bool		PreLoadMusicSamples();							//RJS 14Apr99
	void		DeleteMusicSamples();							//RJS 14Apr99

	UByte		randomFAC;										//RJS 17May99
	UByte		randomTOWER;									//RJS 17May99
	bool		donePreLoadRadio_2D;									//RJS 14Aug00
	bool		donePreLoadRadio_3D;									//RJS 14Aug00

	bool		playingMiller;									//RJS 21May99
	UByte		randomV2;										//RJS 08Jun99
	bool		rchatter_allowed;								//RJS 16Aug99

	SubjectStruc	*theSubject;								//RJS 12Jan00
	ListenerStruc	*theListener;								//RJS 12Jan00

	SWord		ambientList[MAXHANDLERS];						//RJS 08May00
	SWord		ambientCnt;										//RJS 08May00

	bool		wasWindy;												//RJS 9Jun00
	bool		hiResSFXAvailable;									//RJS 14Jun00

	bool		preLoadChatStatus;										//RJS 16Aug00

	float		eyeVector_x;											//RJS 15Sep00
	float		eyeVector_y;											//RJS 15Sep00
	float		eyeVector_z;											//RJS 15Sep00

	Coords3D	eyeWorld;												//RJS 15Sep00
	Coords3D	eyeVelocity;											//RJS 15Sep00

	SWord		eyeHdg;													//RJS 16Sep00
	SWord		eyePitch;												//RJS 16Sep00

	SLong		volumeDesktop;											//RJS 18Oct00
	bool		usingSmacker;											//RJS 20Oct00


public:
	mobileitem* View_Point;
	Bool		CockpitView;									//RJS 07Jun99
	LogSoundRec		delayedsounds;

	bool			diveBrakesOn;										//RJS 25Oct00

///////////////////

CON     Sound();
void	Init(ULong newwin)		{StartUpSound(newwin);}			//RJS 13Mar98
void	StartUpSound(ULong);									//RJS 13Mar98
void	SetVP(mobileitem*);										//RJS 21May98
void	ShutDownSound();
///////////////////			

//TempCode RJS 08Nov99 #ifdef __DOS__													//ARM 02Aug96
//TempCode RJS 08Nov99 DES		~Sound()	{ShutDownSound();}
//TempCode RJS 08Nov99 static	void	cdecl mainbeatint(HSEQUENCE callerseq, SLong	channel, SLong	value);
//TempCode RJS 08Nov99 static	void	cdecl subbeatint(HSEQUENCE callerseq, SLong	channel, SLong	value);
//TempCode RJS 08Nov99 static	void	cdecl mainendint(HSEQUENCE callerseq);
//TempCode RJS 08Nov99 static	void	cdecl subendint(HSEQUENCE callerseq);
//TempCode RJS 08Nov99 static	void	cdecl timerint(ULong	user);
//TempCode RJS 08Nov99 #endif															//ARM 02Aug96
//TempCode RJS 08Nov99 #ifdef WIN95													//ARM 02Aug96
//TempCode RJS 08Nov99 #ifdef __WATCOMC__
//TempCode RJS 08Nov99 static	void	AILEXPORT mainbeatint (HSEQUENCE callerseq,signed long channel, signed long value);//ARM 15Jul96
//TempCode RJS 08Nov99 static	void	AILEXPORT subbeatint(HSEQUENCE callerseq, signed long	channel, signed long value);
//TempCode RJS 08Nov99 static	void	AILEXPORT mainendint(HSEQUENCE callerseq);
//TempCode RJS 08Nov99 static	void	AILEXPORT subendint(HSEQUENCE callerseq);
//TempCode RJS 08Nov99 #endif
//TempCode RJS 08Nov99 #ifdef __MSVC__
//TempCode RJS 08Nov99 static	void	__stdcall mainbeatint (HSEQUENCE callerseq,signed long channel, signed long value);//ARM 15Jul96
//TempCode RJS 08Nov99 static	void	__stdcall subbeatint(HSEQUENCE callerseq, signed long	channel, signed long value);
//TempCode RJS 08Nov99 static	void	__stdcall mainendint(HSEQUENCE callerseq);
//TempCode RJS 08Nov99 static	void	__stdcall subendint(HSEQUENCE callerseq);
//TempCode RJS 08Nov99 static	signed long	__stdcall MIDIEventInterrupt(HMDIDRIVER,HSEQUENCE,signed long,signed long,signed long);//RJS 14Apr99
//TempCode RJS 08Nov99 #endif
//TempCode RJS 08Nov99 static	void	cdecl timerint(ULong	user);
//TempCode RJS 08Nov99 	fileblock	*theblock;
//TempCode RJS 08Nov99 #endif															//ARM 15Jul96

~Sound()	{ShutDownSound();}

///////////////////
private:
Bool		TuneInRange(int	tuneno);
Bool		SequenceInRange(TuneStrucP, int	seqno);
Bool		SampleInRange(int	sampleno);
Bool		HandlerInRange(int	qpos);
void		InitTune(TuneStrucP);
int			GetIndex(FileNum	thefile);
Bool		StartMain(SLong	vol=127);
TuneStrucP	LoadTune(FileNum	thefile);						//RJS 15Aug96
void		InstallWaveTable(FileNum,Bool useDLS=FALSE);		//RJS 19May98
void		StartSequence(FileNum	thefile, int	sequenceno=0, SLong	fadeval=500, SLong	vol=127);
//void		SequenceAudible(SpotEffects spotnum, SLong	vol=127, SLong	fadeval=500);//RJS 29Aug96
void		StopSequence(FileNum	thefile, int	sequenceno=0);
void		SequenceMute(FileNum	thefile, int	sequenceno=0, SLong	fadeval=0);
void		reporterror(int	eno, char	*text=NULL);
SampleRec*	LoadSample(FileNum	thefile,Bool inUI=FALSE);				//RJS 25May99
//DeadCode RJS 16Oct97 SQueuePtr	FindFreeHandler(int	priority, int	spos, ItemBasePtr	sampleitem, SQueuePtr &oldqueue, UByte	looplength=2);//RJS 16Oct97
//DeadCode RJS 17Oct97 void		OverrideSample(SQueuePtr, FileNum	thefile, SLong	vol=-1, SLong	pan=0, SLong	newfreq=-1);//RJS 17Oct97
SLong		ClipVolume(SLong	maxvol, SLong	vol);								
inline void	ClipVolume(SLong& theVol);									//RJS 14Sep00
SLong		ClipPan(SLong	pan);
void		FreeSamples();
void		FreeTunes();
SLong		SampleRate(FileNum	thefile);
void		Update3d();											//RJS 19Nov96
void		KillEngine(ClassPtr	classtype, int	dlevel = 5);		//RJS 03Jul96
void		HardStop(SQueuePtr);								//RJS 21Oct97
void		DeleteSample(FileNum	thefile);					//RJS 23Jul96
void		StopLanded();										//RJS 23Jul96
void		GamePaused();										//RJS 09Aug96
void		StopMusic();										//RJS 22Aug96
void		ResumeMusic();										//RJS 22Aug96
void		ResetMidiFlags();									//RJS 29Aug96
void		DiscardMusic(TuneStrucP exception=NULL);			//RJS 26Feb98
bool		FadeAll(SLong);										//RJS 18Jun99
void		OverRevCheck();										//RJS 03Dec96
void		StopMain();											//RJS 12Nov96
void		UpdateEngine();										//RJS 03Dec96
void		PlaySampleEcho(FileNum, ItemBasePtr, SLong	vol = 128);//RJS 05Dec96
void		ProcessInterfaceSpot();								//RJS 17Nov98
void		SequenceAudible(MoraleType, SLong	vol=127, SLong	fadeval=500);//RJS 03Feb99
//DEADCODE RJS 5/8/00 void		UIPlayAmbient(FileNum,SLong,SLong vol=128);			//RJS 12Mar99

private:

void		DeleteSample(SLong );								//RJS 21May98
Bool		NewDigitalDriver(HSampRate	srate, int	nohandlers, Bool	usemono=FALSE, bool have3d=false);//RJS 12Jan00
SQueuePtr	FindFreeHandlerOnce(SampleRec*, ItemBasePtr	sampleitem, SQueuePtr&,int	stblock, int	endblock);//RJS 29Jan99
void		PlaySettings(SQueuePtr, SLong	vol, SLong	pan);//RJS 21Oct97
void		SetUpSample(SQueuePtr, SampleRec*, SLong	maxvol, SLong	vol, SLong	pan, ItemBasePtr	sampleitem,const float startscale=0);	//RJS 13Sep00
void		SoundInWorld(const COORDS3D&, SLong&, SLong&);				//RJS 12Jun00
void		GetSampleVolumes();									//RJS 03Apr97
SQueuePtr	FindFreeHandler(SampleRec*, ItemBasePtr	sampleitem, SQueuePtr &oldqueue, UByte	looplength=2);//RJS 16Oct97
void		OverrideSample(SQueuePtr, FileNum	thefile, SLong	vol=32767, SLong	pan=0, SLong	newfreq=-1);//RJS 17Oct97
Bool		StartSeqEffect(TuneStrucP,SLong,SLong);				//RJS 26Feb98
Bool		StartSeqMain(TuneStrucP,SLong,SLong);				//RJS 26Feb98
Bool		StartSeqIndependent(TuneStrucP,SLong,SLong);		//RJS 26Feb98
void		SetCompressedDLS(TuneStrucP,void*,SLong);				//RJS 18May98
void		SetUncompressedDLS(TuneStrucP,void*,SLong);				//RJS 18May98
void		SetXMidi(TuneStrucP);								//RJS 19May98
void		SetDLS(TuneStrucP);									//RJS 19May98
void		PlayWind();											//RJS 20May98
SQueuePtr	FindFreeRadioHandler();								//RJS 09Jun98
void		RowanToPan(SLong&);									//RJS 29Jan99
void		RowanToPan(SWord&);									//RJS 29Jan99
SQueuePtr	FindFreeHandlerUI(SampleRec*);						//RJS 12Mar99
void		PreLoadFile(SLong);									//RJS 01Apr99
void		MultiMediaError(ULong);					  			//RJS 08Nov99
SLong		SoundInWorld(const ItemPtr,SLong&);						//RJS 12Jan00
void		SetSubject(Coords3D&,SLong,SLong,SLong,SLong);		//RJS 12Jan00
SQueuePtr	FindFreeHandlerRestart(SampleRec*, ItemBasePtr	sampleitem, int	stblock, int	endblock);//RJS 13Jun00

void		PreLoadChatChunk(SLong,bool preLoadRAF=false,bool preLoadLW=false);	//RJS 6Oct00
inline void	GetEyeVelocity(SLong&, SLong&, SLong&);						//RJS 15Sep00
inline void	SetPriority(const SQueuePtr,SLong&);				//RJS 22Sep00
inline void	UpdatePriority(const SQueuePtr, const int&, SLong&, SLong&);	//RJS 22Sep00

void		ClearSoundQueue();											//RJS 28Sep00
void		CloseDownSmall();											//RJS 16Nov00




public:
//UI
Bool		IsEnabled(SoundType);								//RJS 08Sep98
void		StopAll();
void		SetVolumes(Bool);									//RJS 12Mar99
Bool		InitUI(int);										//RJS 06Apr99
Bool		Init3D();										//RJS 26Jul96
void		SetDirectSoundWindow(ULong);						//RJS 03Apr98
void		KillAll();
void		DisableAll();
void		UIPlaySample(FileNum,SLong vol=128);				//RJS 12Mar99
void		InitSoundFonts();
void		UIPlayAmbient(SLong);								//RJS 08May00
void		UIProcessAmbience();								//RJS 08May00

void		ChatterStatus(bool);										//RJS 16Aug00

//COMMS
//DEADCODE AMM 14/01/00 ULong		GetSysTime();										//AMM 11Jun99
//MOVE
void		ResetSoundFlags();									//RJS 12Jul96
//DeadCode RJS 13Jan00 void		PlayEngine(SLong,AirStrucPtr,SLong	rpm, SLong	vel,SWord);//RJS 17Nov98
void		PlayEngine(AirStrucPtr,EngineInfo&,EngineInfo&);	//RJS 13Jan00
void		PlayLanded(ItemBasePtr	sampleitem, SLong	velocity,Bool skid);//RJS 14Jan99
void		PlayBuffet(SLong vol, SLong pan=0);					//RJS 28Jan99
void		ProcessPercussion();								//RJS 18Aug99
void		SetListener(ViewPoint*);							//RJS 12Jan00
void		Commit();
//MODEL
void		PlayWindyMiller(AirStrucPtr);						//RJS 21May99
void		SetEngine();//RJS 06Oct98
void		SequenceMute(SLong	fadeval=500);					//RJS 24Mar99
//GENERAL
void		ProcessSpot(ViewPoint*);							//RJS 25May99
void		PlayOnce(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol=128,FileNum	stsam=FIL_NULL, FileNum	endsam=FIL_NULL,float startscale=0);	//RJS 13Sep00
void		PlayOnce(FileNum	thefile, int	vol=128,SLong thepan=0);//RJS 28Jan99
SLong		SmackerOn(int);										//RJS 10Nov00
void		SmackerOff(int	wind=0);									//RJS 18Oct00
void		SetCockpit(Bool);									//RJS 20May98
void		PlayDelayed(FileNum,ItemPtr,SLong vol=128,Bool islooped=FALSE,FileNum	stsam=FIL_NULL, FileNum	endsam=FIL_NULL);
void		SequenceAudible(FileNum	thefile, SLong	vol=127, SLong	fadeval=500);//RJS 29Aug96
void		HaltItemSound(ItemBasePtr	sampleitem);			//RJS 11Jul96
Bool		StartShooting(FileNum,SLong,SLong);					//RJS 31May99
void		PlayLooped(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol=128, UByte	looplength=2, Bool sound3d=TRUE);//RJS 01Jun99
void 		PlaySample(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol = 128);//RJS 17Oct97
void 		PlaySample(FileNum	thefile, SLong	vol=128, SLong	pan=0);//RJS 17Oct97
void		StopShooting();								//RJS 12Apr99
void		StopEngine(int	velocity=-1);
void		PlayFlyAway(ItemBasePtr);							//RJS 21May98
void		StopSample(FileNum	thefile, ItemBasePtr	sampleitem = NULL);//RJS 15Jul96
void		SequenceAudible(MoodSetting, SLong	vol=127, SLong	fadeval=500);//RJS 30Jun98
void		SequenceAudible(MoodDelta, SLong	vol=127, SLong	fadeval=500);//RJS 30Jun98
void		SetUpRandomVoices(SLong,SLong,SLong);				//RJS 08Jun99
Bool		SampleFinished(UByteP,bool);						//RJS 25May99
UByteP		PlaySampleRadio(UByteP, int, SWord,int, int);		//RJS 14Jan99
void		SetGlobalVolumes(int	sfxvol=127, int	midivol=-1, int	engvol=-1,int smackervol=-1, Bool	saveset=FALSE);//RJS 29Sep96
bool		SamplePlaying(FileNum);										//RJS 13Jun00
void		PlayRestart(FileNum	thefile, ItemBasePtr	sampleitem, SLong	vol=128,FileNum	stsam=FIL_NULL, FileNum	endsam=FIL_NULL);
void		PlayRestart(FileNum	thefile, SLong	vol=128, SLong thepan=0);	//RJS 13Jun00
bool		HiResSFX(){return hiResSFXAvailable;}						//RJS 14Jun00
void		SetUpListener(const ItemPtr,const ULong&, const ULong&, const ULong&,const float&,const float&, const float&,const ANGLES&,const ANGLES&);	//RJS 15Sep00
int			GetEngineVol();												//RJS 28Sep00
void		GoingToMapScreen();											//RJS 6Oct00
void		StopItemSamples(ItemBasePtr);						//RJS 10Oct00
void		PlayAnyDelayed(FileNum,ItemPtr,SLong vol=128,Bool islooped=FALSE,FileNum	stsam=FIL_NULL, FileNum	endsam=FIL_NULL);	//RJS 16Oct00


};
extern Sound _Miles;											//RJS 05Nov99

#endif
