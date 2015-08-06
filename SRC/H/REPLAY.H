//------------------------------------------------------------------------------
//Filename       replay.h
//Date           Wed 29 Apr 1998
//------------------------------------------------------------------------------
#ifndef	REPLAY_Included
#define	REPLAY_Included

#define	DEFAULT_REPLAY 0

#include	"DOSDefs.h"	
#include	<stdio.h>
#include	"fileman.h"
#include	"winmove.h"
#include	"worldinc.h"
#include	"modvec.h"											
#include	"savegame.h"
#include	"cbuffer.h"
#include	"sky.h"
class  Engine;
typedef class  Engine ENGINE, *PENGINE, **PPENGINE;
class Ctrl ;
class NewCtrl ;
class Surface ;
class MainPlane ;
class Cylinder ;
class ThrustPoint ;
class AeroDevice ;

typedef class Ctrl *PCTRL;
typedef class NewCtrl *PNEWCTRL;
typedef class Surface *PSURFACE;
typedef class MainPlane *PMAINPLANE;
typedef class Cylinder *PCYLINDER;
typedef class ThrustPoint *PTHRUSTPOINT;
typedef class AeroDevice *PAERODEVICE;
class Gear;
typedef class Gear  GEAR, *PGEAR, **PPGEAR;


enum {REPLAYHEADBEGINID=(('G'<<24)+('E'<<16)+('B'<<8)+'H')};
enum {REPLAYHEADENDID=(('D'<<24)+('N'<<16)+('E'<<8)+'H')};
enum {REPLAYSUPERHEADBEGINID=(('G'<<24)+('E'<<16)+('B'<<8)+'S')};
enum {REPLAYSUPERHEADENDID=(('D'<<24)+('N'<<16)+('E'<<8)+'S')};

// bullets and missiles get 10 secs, bombs 1 min
// this value is in frames

#define MISSILEDELAY	(100/TimerCode.FRAMETIME)*10
#define	BULLETDELAY		(100/TimerCode.FRAMETIME)*10
#define BOMBDELAY		(100/TimerCode.FRAMETIME)*60


#define	POSBSIZE		5

typedef struct _basic_packet REPLAYPACKET;
typedef struct _basic_packet* LPREPLAYPACKET;

typedef struct _miss_conds MISSIONCONDS;
typedef struct _miss_conds* LPMISSIONCONDS;

struct _miss_conds {

	FP	TempVar;			//K variation in temp last time
	FP	Temp0;				//K	temp at seal level
	FP	Press0;				//millibar
	FP  Density0;			//kg/m3 @ SL	
	FP	wind0;				//mph
	FP	dir0;				//direction in degrees
	FP	windalt;			//mph
	FP	diralt;				//direction in degrees
	FCRD Wind0;				// wind at zero height
	FCRD WindAlt;			// wind at altitude
	SLong WindAltHeight;		// height of above		
	SWord MinDuration;		// csecs
	SWord MaxDuration;		// csecs
	FP MinMagnitude;		// 1 = 1 m/s
	FP MaxMagnitude;		// 1 = 1 m/s
	UWord Frequency;		// 0 = always, 65535 = very infrequent
	//contrails
	FP	ContrailBandCentre;
	FP	ContrailBandWidth;

	FP	Visibility;			// in cm
	FP	Conditions;			//CLEAR, RAIN, SNOW
	FP	CloudLayer;			// bottom layer in cm

	Cloud Layer[3];
	Cloud FluffyCloud;

	bool	MistInValley;

};



typedef struct _grentry REPGRENTRY;
typedef struct _grentry* LPREPGRENTRY;

struct _grentry {
	int	val;
	LPREPGRENTRY next;
};

typedef struct _grlist GRLIST;
typedef struct _grlist* LPGRLIST;

struct _grlist {
	FileNum			file;
	ULong			bfctrl;
	LPREPGRENTRY	list;
	UWord			ordernum;
	LPGRLIST		next;
};

typedef struct _sagglobs SAGGLOBS;
typedef struct _sagglobs* LPSAGGLOBS;

struct _sagglobs
{
	int			mintriggerrange;									
	int			maxtriggerrange;									
	int			currenttriggerrange;
	UniqueID	basenum;
	int			numavailable;
	int			numactive;
	int			reservedactive;
	int			SAGsoftype;
	int			SAGsexpanded;
};

typedef struct _sag_values SAGPRIMARYVALUES;
typedef struct _sag_values* LPSAGPRIMARYVALUES;
struct _sag_values
{
	ONLYFIELD(UWord,UniqueID,expandedsag);
	SWord 	numinsag;
};

typedef struct _miprim_values MIPRIMARYVALUES;
typedef struct _miprim_values* LPMIPRIMARYVALUES;
enum	AutoMoveCodeTypeSelect;
enum	UniqueID;
struct _miprim_values
{
// ItemBase
 
	COORDS3D	pos;
	ITEM_STATUS	Status;

// item

	ShapeNum	shape;

// hdgitem

	ANGLES		hdg;

// hpitem

	ANGLES		pitch;

// rotitem

	ANGLES		roll;

// moving item

	SLong vel;

//mobile item

	ONLYFIELD(UWord,UniqueID,waypoint);
	AutoMoveCodeTypeSelect movecode;
	ONLYFIELD(UWord,UniqueID,leader);							
	ONLYFIELD(UWord,UniqueID,follower);							

	UWord		manoeuvretime;									
};

typedef struct _asprim_values ASPRIMARYVALUES;
typedef struct _asprim_values* LPASPRIMARYVALUES;

struct _asprim_values
{

// airstruc

// pack bools into a byte

	FIRSTFIELD (UByte, Bool,simpleacm,0)
		BITFIELD(Bool,beenseen,1,1)								
		BITFIELD(Bool,slowdownleader,3,3)
		BITFIELD(Bool,advantage,4,4)
		BITFIELD(Bool,disadvantage,5,5)
		BITFIELD(Bool,UseIntFuel,6,6)
		LASTFIELD(Bool,FuelDumped,7,7)

	FIRSTFIELD (UByte, Bool, StoresDumped,0)
		BITFIELD(Bool,Ejected,1,1)
		BITFIELD(InFormation,information,2,5)
		BITFIELD(Bool,playermoving,6,6)
		LASTFIELD(Bool,Spare5,7,7)


	// ai

	ONLYFIELD(UWord,UniqueID,homebase);							//AMM 02Jun99
	ONLYFIELD(UWord,UniqueID,unfriendly);
	ONLYFIELD(UWord,UniqueID,spottedunfriendly0);						//CSB 21Aug00
	ONLYFIELD(UWord,UniqueID,spottedunfriendly1);						//CSB 21Aug00
	ONLYFIELD(UWord,UniqueID,spottedunfriendly2);						//CSB 21Aug00
	ONLYFIELD(UWord,UniqueID,spottedunfriendly3);						//CSB 21Aug00



	ONLYFIELD(UWord,UniqueID,expandedsag);
	ONLYFIELD(UWord,UniqueID,attacker);
	ONLYFIELD(UByte,MANOEUVRE,manoeuvre);
	SWord		numinsag;
	UByte		ManStep;
	UByte		morale;
	SByte		moraleinc;
	SLong		lastdelta;
	ANGLES		desiredroll;
	ANGLES		desiredpitch;
	ANGLES		desiredaoa;

	ANGLES		desiredhdg;
	Float		desiredturn;
	Float		desiredpitchrate;
	ULong		desiredrange;
	ULong		desiredalt;
	SLong		deltapitchsum;

	//weap


	int	rreloadmass;
	int	creloadmass;
	int	lreloadmass;

	int	rreloaddrag;
	int	creloaddrag;
	int	lreloaddrag;

	int	rmass;
	int	cmass;
	int	lmass;

	int	rdrag;
	int	cdrag;
	int	ldrag;

	int fuel_cont[4];

	UWord	shpweapindex;
	SWord	ShootDelay;
	SWord	weapforce;

	//flight_ctl

	ONLYFIELD(UByte,FormationIndex,originalformpos);			//AMM 02Jun99
	ONLYFIELD(UWord,UniqueID,nextflight);
	ONLYFIELD(UWord,UniqueID,leadflight);
	SWord		rpm;
	SWord		thrustpercent;
	ONLYFIELD(UWord,UniqueID,backupWP);
	SLong		gforce;
	SWord		aileron;
	SWord		elevator;
	SWord		rudder;
	Float		dhdg;
	bool		use_this_tank[4];							//CB 05/11/99	//save

	//	misc

	UNIQUE_ID	lasthitter;

	UByte		Weapons;

// formationitem

	ONLYFIELD(UWord,FormationIndex,formpos);
	ONLYFIELD(UWord,FormationTypeIndex,formation);
	ONLYFIELD(UByte,UByte,duty);

	SWord		FuelCockPos;											//AMM 24Jul00
	SWord	FrameCount;													//CSB 14Nov00
};

typedef struct _fm_full_prim_values FMPRIMARYVALUES;
typedef struct _fm_full_prim_values* LPFMPRIMARYVALUES;

struct _fm_full_prim_values 
{
// model.h

	Bool	FirstCycle;											//AMM 29Jun99
	FCRD	RotVel;
	int		Elevator;
	int		Aileron;
	int		Rudder;
	int		ElevatorTrim;
	int		AileronTrim;
	int		RudderTrim;

	SWord	ModelThrottle;
	SWord	ModelPropSetting;
	SWord	LeftWheelBrake;
	SWord	RightWheelBrake;


	Bool	Spinning;
	FP		TotalBuffet;

// acmmodel.h

	FP		lastdeltapitch;
	FP		deltapitchsum;						
	FP 		deltarollsum;						
	FP 		deltayawsum;						
	FP 		maxdeltaforclosework;
	FP		OldCtrlRoll;
	FP		OldCtrlTurnRate;
	FP		OldCtrlYawRate;
	FP		desiredRoll;

};

typedef struct _prim_engine_vals PRIMARYENGINEVALUES;
typedef struct _prim_engine_vals* LPPRIMARYENGINEVALUES;

// engine.h

struct _prim_engine_vals {

	FP		Speed;
	FP		SpeedRpm;
	FP		Power0;
	FP		Power100;
	FP		Power;
	FP		MaxThrust;
	FP		Thrust;
	FP		Torque;
	FCRD	moment;
	FP		PropInc;
	FP		PropVel;
	FP		SlipVel;
	FP		SlipRot;
	FP		FuelInPipes;
	SWord	ThrottleSetting;									//AMM 24Jul00
	FP		PropSetting;										//AMM 24Jul00
};

// elmt.h

typedef struct _prim_elmt_vals PRIMARYELMTVALUES;
typedef struct _prim_elmt_vals* LPPRIMARYELMTVALUES;

struct _prim_elmt_vals {

	FP		aoa[2][2];
	FP		DownWashAng[2];
	FP		BuffetAoaMin;
	FP		BuffetAoaMax;
	FCRD	eForce[2][2];
	FCRD	eMoment[2][2];
};

typedef struct _aerodev_vals AERODEVVALUES;
typedef struct _aerodev_vals* LPAERODEVVALUES;

struct _aerodev_vals {

	SWord	Val;
	SWord	Attractor;
	SWord	OldAttractor;
	SWord	ReqVal;
	Bool	Broken;
};

//surface 

typedef struct _surface_vals SURFACEVALUES;
typedef struct _surface_vals* LPSURFACEVALUES;

struct _surface_vals {

	FCRD	Force;
	FCRD	Moment;
};

//thrust

typedef struct _thrust_vals THRUSTVALUES;
typedef struct _thrust_vals* LPTHRUSTVALUES;

struct _thrust_vals {

	FCRD	Force;
	FCRD	Moment;
};

//cylinder

typedef struct _cylinder_vals CYLINDERVALUES;
typedef struct _cylinder_vals* LPCYLINDERVALUES;

struct _cylinder_vals {

	FCRD	Force;
};

enum	RDEATH													//RJS 28Oct98
{																//RJS 28Oct98
	RDEATH_NULL	= 0,											//RJS 28Oct98
	RDEATH_SKID,												//RJS 28Oct98
	RDEATH_ROLL,												//RJS 28Oct98
	RDEATH_DIVE													//RJS 28Oct98
};																//RJS 28Oct98

typedef struct ReplaySmkCloud REPLAYSMOKECLOUD;
typedef struct ReplaySmkCloud* LPREPLAYSMOKECLOUD;

struct ReplaySmkCloud
{
	SLong index;
	SLong timealive;
	COORDS3D pos;
};

typedef struct ReplaySmkStruc REPLAYSMOKE;
typedef struct ReplaySmkStruc* LPREPLAYSMOKE;

struct	ReplaySmkStruc											//AMM 04Nov98
{
 	ULong			lifetime;									
	SLong			lastwx,										
					lastwy,										
					lastwz;										
	UByte			nextlist:6,									
					beendrawn:1,
					cloudlaunched:1;								
	SWord			LaunchCountdown;							
	SWord			SampleTime;									
	SByte			smkindex:7,									//RJS 18Feb99
					transient:1;								//RJS 18Feb99
	UByte			nopoints;
	ULong			currTime;									//RJS 16Jun99
};																//AMM 04Nov98

struct	ReplaySmlSmkStruc											//RJS 18Feb99
{																//RJS 18Feb99
	UWord			uniqueid;									//RJS 18Feb99
 	ULong			lifetime;									//RJS 18Feb99
	SByte			smkindex;									//RJS 18Feb99
	UByte			nopoints;									//RJS 18Feb99
	ULong			currTime;									//RJS 16Jun99
};																//RJS 18Feb99

struct	ReplaySmkPoint											//RJS 17Feb99
{
	SLong	x,y,z;
	ULong	lifeleft:18,								
			radius:14;									
	ULong	LifeTime:18,								
			FadeTime:13,								
			KillMe:1;									
};

typedef struct _markinfo MARKINFO;
typedef struct _markinfo* LPMARKINFO;

struct _markinfo 
{
	ULong blocknum;
	UWord framenum;
	UByteP memaddress;
};

enum	ReplayFlags
{
	RF_NONE=0,
	RF_SKIPFRAMES,
	RF_BLOCKFORWARD,
	RF_BLOCKREWIND,
	RF_FRAMEFORWARD,
	RF_FRAMEREWIND,
	RF_SKIPTOPREVIOUSMARK,
	RF_SKIPTONEXTMARK
	
};

struct ArmedTransient
{
	COORDS3D	Pos;
	UWord		shape;
	SLong		vel_x; //CSB 08/11/99
	SLong		vel_y; //CSB 08/11/99
	SLong		vel_z; //CSB 08/11/99
	UByte		movecode;
	UByte		strength;
	UWord		launcher;
	UWord		lifetime;
	ANGLES		hdg;
	ANGLES		pitch;
	UWord		deadtime:1,
				trailindex:6,
				transrandom:9;
	UByte		groupCount;										//RJS 1Sep00
};


class Replay {

public:
	bool	replayskip;											//RJS 08Nov99
	bool	ResetFileFlag;
	Bool	Record;
	Bool	Playback;
	ULong	PlaybackGameState;
	Bool	PlaybackPaused;

	void* 	playbackfilestart;
	UByteP	playbackfilepos;
	UByteP	playbackfileend;
	HANDLE	mappedplaybackfile;
	HANDLE	playbackstorage;

	HANDLE	recordstorage;

	char	rfilename[256];
	char	pfilename[256];
	char	RealFilename[256];
	ULong	replayframecount;

	UWord	thisblockstartframe;
	UWord	thisblockendframe;
	UWord	thisblocknumframes;

	MARKINFO	beginmark;
	MARKINFO	endmark;

	void	DeleteReplayLog();
	
	RDEATH	ReplayDeathMode;									//RJS 28Oct98

	UWord	lastRpmLeft;												//RJS 21Jun00
	UWord	lastRpmRight;												//RJS 21Jun00


	CON Replay();
	CON ~Replay();

	Bool	StoreDeltas();
	Bool	EndRecord();
	Bool	EndPlayback();
	Bool	SaveReplayData(char* name);
	Bool	LoadReplayData(char* name);
	Bool	OpenRecordLog();
	void	CloseRecordLog();
	Bool	OpenPlaybackLog();
	void	ClosePlaybackLog();
	Bool	LoadDeltas();
	Bool	StoreRandomList();
	Bool	LoadRandomList();
	Bool	StoreInitialGlobRefs();
	Bool	LoadInitialGlobRefs();
	Bool	StoreDeadItems();
	Bool	LoadDeadItems();
	void	UpdateGhostAC();
	Bool	LoadItemAnims();
	Bool	StoreItemAnims();

	bool	LoadSaveGame();
	Bool	StoreSaveGame();

	Bool	BlockForward();
	Bool	BlockRewind(Bool onlyone=FALSE);
	ULong	LoadHeaderLength();
	Bool	StoreHeaderLength(ULong length);

	Bool	StartRecordFlag;
	ULong	framestoskip;
	ReplayFlags	ReplayFlag;

	int		PlayerSquad;
	int		PlayerPos;
	ULong	headlength[1024];
	UByteP	headmems[2][1024]; // memory address off beginning/end of block
	UWord	numframes[1024];
	UWord	markers[2][1024]; // begin frame, end frame of block
	UByte	numblocks;
	UByte	currblock;
	LPREPGRENTRY initgrlist;
	LPGRLIST	bfgrlist;
	LPGRLIST	currentry;
	void	AddFileAndGlobRefsToList(FileNum file,ULong bfctrl);
	void	DeleteFileAndGlobRefList(LPGRLIST& list);
	void	GetGlobRefs(LPREPGRENTRY& list);
	Bool	StoreGlobRefList(LPREPGRENTRY list);
	Bool	LoadGlobRefList(LPREPGRENTRY& list);

	void	SetGlobRefs(LPREPGRENTRY list);

	Bool	StoreFileAndGlobRefList();
	Bool	LoadFileAndGlobRefList();

	Bool	ReplayRead(UByte* dest, ULong size);
	Bool	ReplayWrite(UByte* src, ULong size);
	void	GetInitialGlobRefs();
	void	DeleteGRList(LPREPGRENTRY& list);
	Bool	StoreHeaderID();
	Bool	LoadHeaderID();

	FileNum	LoadBFieldNum();
 	Bool	StoreBFieldNum(FileNum bf);

	ULong	LoadBFCtrl();
 	Bool	StoreBFCtrl(ULong a);

	Bool	StoreItemData();
	Bool	LoadItemData();

	void	ResetReplayData();

	void	SkipToBeginning();
	void	SkipToEnd();
	void	FrameForward();
	ULong	FrameRewind();

	Bool	StoreInitFrameCounts();
	Bool	StoreRealFrameCounts(UWord num, UWord start, UWord end);
	Bool	LoadFrameCounts();

	Bool	StorePrimaryASData(AirStrucPtr ac); 
	void	GetPrimaryASData(AirStrucPtr,LPASPRIMARYVALUES aspv);
	Bool	StorePrimaryMIData(MobileItemPtr ac);
	void	GetPrimaryMIData(MobileItemPtr item,LPMIPRIMARYVALUES mipv);

	void	RestorePrimaryASValues(AirStrucPtr ac, LPASPRIMARYVALUES aspv);
	void	RestorePrimaryMIValues(MobileItemPtr ac, LPMIPRIMARYVALUES mipv);

	void	RestorePrimarySAGValues(SAGAirstruc*,LPSAGPRIMARYVALUES);
	void	GetPrimarySAGValues(SAGAirstruc*, LPSAGPRIMARYVALUES);
	bool	StorePrimarySAGData(SAGAirstruc*);

	Bool	StorePrimaryFMData(AirStrucPtr ac);
	void	GetPrimaryFMData(AirStrucPtr ac, LPFMPRIMARYVALUES);
	Bool	StorePrimaryEngineData(AirStrucPtr ac);
	void	GetPrimaryEngineData(LPPRIMARYENGINEVALUES,PENGINE );
	Bool	StorePrimaryElmtData(AirStrucPtr ac);
	void	GetPrimaryElmtData(LPPRIMARYELMTVALUES, PMAINPLANE);

	Bool	LoadFMData(AirStrucPtr ac);
	void	RestorePrimaryFMData(AirStrucPtr ac,LPFMPRIMARYVALUES);
	void	RestorePrimaryEngineData(LPPRIMARYENGINEVALUES,PENGINE);
	void	RestorePrimaryElmtData(LPPRIMARYELMTVALUES,PMAINPLANE);
	void	ResetSecondaryFMValues(AirStrucPtr ac);

	Bool	StoreAeroDevData(AirStrucPtr ac);
	void	GetAeroDevData(LPAERODEVVALUES ,PAERODEVICE);
	void	RestoreAeroDevData(LPAERODEVVALUES,PAERODEVICE);

	Bool	StoreSuspensionData(AirStrucPtr ac);
	FP		GetSuspensionData(PGEAR);
	void	RestoreSuspensionData(FP legpos,PGEAR);

	Bool	StoreSurfaceData(AirStrucPtr);
	void	GetSurfaceData(LPSURFACEVALUES, PSURFACE);
	void	RestoreSurfaceData(LPSURFACEVALUES, PSURFACE);

	Bool	StoreThrustData(AirStrucPtr);
	void	GetThrustData(LPTHRUSTVALUES, PTHRUSTPOINT);
	void	RestoreThrustData(LPTHRUSTVALUES, PTHRUSTPOINT);

	Bool	StoreCylinderData(AirStrucPtr);
	void	GetCylinderData(LPCYLINDERVALUES, PCYLINDER);
	void	RestoreCylinderData(LPCYLINDERVALUES, PCYLINDER);

	Bool	LoadGamePrefs();
	Bool	StoreGamePrefs();

	void	StoreFinalRecordData();
	void	LoadFinalPlaybackData();

	void	ResetAICount();
	void	RemoveAllTransients(Bool	totalremove=FALSE);				 //RJS 21Jun99
	void	StopRecord(bool);
	void	GetReplayFileName();

// Dummy death movecodes that go through the motions, but don't actually move...

	void	DummyCrashSkid();									//RJS 28Oct98
	void	DummyCrashRoll();									//RJS 28Oct98
	void	DummyCrashDive();									//RJS 28Oct98

	Bool	StoreDeathMoveState();								//RJS 29Oct98
	Bool	LoadDeathMoveState();								//RJS 29Oct98

	Bool	LoadSmlSmkData(ReplaySmlSmkStruc*,Bool,UByteP&,Coords3D&);//RJS 18Feb99
	Bool	StoreSmlSmkData(ReplaySmlSmkStruc*,UByteP);			//RJS 18Feb99
	Bool	StoreSmkData(LPREPLAYSMOKE,UByteP);					//RJS 17Feb99
	Bool	LoadSmkData(LPREPLAYSMOKE smokey,Bool,UByteP&);		//RJS 18Feb99
	Bool	StoreSmkIndexData(ULong index);
	Bool	LoadSmkIndexData(ULong& index);

	Bool	DoSmokeTrailStuff;

	void	MarkBlockBeginning();
	void	MarkBlockEnd();
	void	RemoveMarks();
	Bool	SaveBlock();
	void	SkipToBeginningMark();
	void	SkipToEndMark();
	void	RemoveBeginningMark();
	void	RemoveEndMark();
	void	SkipToPreviousMark();
	void	SkipToNextMark();

	void	ResetFlags();
	void	ResetRecord();
	void	ToggleRecord();
	bool	ValidReplayFile();

	void	UpdateSeenAIData();
	void	BeginNewBlock();
	void	GetReplayFilename(char* buff);

	ULong	guncameradelay;
	ULong	SuperHeaderSize;
	Bool	LoadSuperHeader();
	Bool	LoadSuperHeaderBeginning();
	Bool	LoadSuperHeaderEnd();

	Bool	StoreSuperHeader();
	Bool	StoreSuperHeaderBeginning();
	Bool	StoreSuperHeaderEnd();

	Bool	LoadSuperHeaderID();
	Bool	StoreSuperHeaderID();

	bool	SuperHeaderStored;
	Bool	StoreBlockHeader();
	Bool	LoadBlockHeader();

	void	BackupPlaybackPosition();
	ULong	backupblock;
	ULong	backupframe;
	UWord	backupstate;
	bool	RestorePosition;
	void	RestorePlaybackPosition();
	bool	MenuViewPlayback;
	bool	MapPlayback;
	bool	QMPlayback;

	DeadStream Replay_Dead_Stream;
	ULong	GetState();
	void	SetState(ULong state);
	bool	IsCampState(ULong state);
	bool	BackupSaveGame();
	bool	RestoreSaveGame();
	bool	SaveTempSaveGame(char* name);//,bool pack);
	void	ResetReplayView();
	void	SetVelsAndOldVals(AirStrucPtr ac);
	  
	void	PreScanReplayFile();
	bool	prescan;
	ULong	TotalFrames;
	ULong	EndBlockNum;
	UWord	EndFrameNum;
	UWord	BeginBlockFrame;

	UByte	CurrPos;
	UByte	BeginMarkPos;
	UByte	EndMarkPos;

	void	CalcBeginMarkPos();
	void	CalcEndMarkPos();
	void	CalcCurrPos();

	void	UpdateSmokes();
	bool	StoreFMMass(AirStrucPtr ac);
	bool	LoadFMMass(AirStrucPtr ac);
	bool	badrecord;

	bool	prefscheck;
	void	ClearReplayBuffers();

	bool	StorePrevPosBuffer();
	bool	LoadPrevPosBuffer();
	void	InitPosBuffer();
	void	UpdatePosBuffer();

	CBuffer<COORDS3D,POSBSIZE>	PosBuffer;

	bool	skipOK;

	bool	StoreHeaderEndID();
	bool	LoadHeaderEndID();
	bool	StoreSuperHeaderEndID();
	bool	LoadSuperHeaderEndID();

	bool	stopforaccel;
	SByte	setpaused; // 0=do nothing, 1=pause, -1 = unpause
	bool	emptyblock;

	bool	processsmokes;
	void	UpdateSmokeInfo();
	bool	BackupSmokeInfo();
	bool	BackupCloudInfo();
	UByteP	backupsmoke;
	UByteP	tempbackupsmoke;
	UByteP	backupcloud;
	UByteP	tempbackupcloud;
	bool	SmokeRead(void* dest,ULong size);
	bool	CloudRead(void* dest,ULong size);
	bool	StoreSmokeSize(ULong size);

	SByte	DelayedWeapon;
	void	BackupPrefs(bool incomms);
	void	RestorePrefs(bool incomms);

	struct	REPLAYPREFS
	{
		FlightDifficultyField	flightdifficulty;
		GameDifficultyField	gamedifficulty;
		SWord	autopilotskillLW;
		SWord	autopilotskillRAF;
		TargetSize targetsize;
	};

	REPLAYPREFS	ReplayPrefs;

	bool	StoreTimeOfDay();
	bool	LoadTimeOfDay();

	Inst3d*	inst;

	bool	StoreCampaignStruc();
	bool	LoadCampaignStruc();

	void	DeleteTempFiles();

	void	BackupGRRandomList();
	bool	LoadGRRandomList();
	bool	StoreGRRandomList();
	UWord 	BackupRndPacket [RNDPACKETSIZE];
	bool	UpdateLandscape;
	bool	DelayedGearUp;

	bool	StoreAAAList();
	bool	LoadAAAList();

	void	ResetItemAnim();

	bool	StoreArmedTransients();
	bool	LoadArmedTransients();

	bool	LoadHeader;
	bool	StoreHeader;
	void	SetTimeOfDay(int time);								//AMM 30Jun99
	bool	StopRecordFlag;										//DAW 02Jul99

	bool	FakeCollisionOn;									//AMM 12Jul99

	void	Forward_X_Frames(ULong);
	void	Rewind_X_Frames(ULong);

	void	Forward30secs();
	void	Rewind30secs();
	void	Forward1sec();
	void	Rewind1sec();

	inline bool	InReplay()
	{
		if (Record || Playback)
			return true;
		return false;
	}

	inline bool	ReplayOrComms()
	{
		if (Record || _DPlay.Implemented)
			return true;
		return false;
	}


	bool	AtEnd();

// set up before any forward/rewind operation to store the previous position of the AC
// when the operation has completed the new position can be compared to the previous
// to see if a landscape load is required

	COORDS3D	PrevPos;
	void	SetPreviousPos();

	UByte	velshifttest;

	enum {TempID=(('P'<<24)+('M'<<16)+('E'<<8)+'T')};

	void StoreTempID();
	void LoadTempID();
	bool	LoadSmokeClouds(bool);
	bool	StoreSmokeClouds();

	char	replaysavebackup[32];

	void	SetWaypointData();
	void	SetWaypointTargetAlt();
	void	DumpData(char*);


	bool	StoreSagGlobs();
	bool	LoadSagGlobs();

	bool	StoreACArray();
	bool	LoadACArray();
};	

extern Replay _Replay;

#endif
