//------------------------------------------------------------------------------
//Filename       savegame.h
//System         
//Author         R. Hyde 
//Date           Mon 22 Apr 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	SAVEGAME_Included
#define	SAVEGAME_Included

#include "analogue.h"
#include "myangles.h"
#include "bitcount.h"
#include "config.h"
//TEMPCODE JIM 07/02/00 #include "misssub.h"

#define	DEFAULT_SAVEGAME 0

enum	{PLAYERNAMELEN			= 21};

enum	FlightDifficulty		{FD_MIN = 0,
				FD_SPINS,
				FD_ENGINEMANAGMENT,
				FD_PROPPITCH,
				FD_POWERBOOST,
				FD_WINDEFFECTS,
				FD_WINDGUSTS,
				FD_EXCESSIVEACCELDAMAGE,
				FD_SLIPSTREAMEFFECTS,
				FD_109FUEL,
				FD_STORESWEIGHTDRAG,
//DEADCODE CSB 30/11/99 				FD_THRUSTPOWERCONTROL = 0,
//DEADCODE DAW 30/11/99 				FD_TORQUEEFFECTS,
//DEADCODE CSB 30/11/99 				FD_JETFLAMEOUT,
//DEADCODE CSB 30/11/99 				FD_LIMITEDFUEL,
//DEADCODE CSB 30/11/99 				FD_AIRCRAFTINTERFERENCE,
//DEADCODE CSB 30/11/99 				FD_IDEALSANDCONTROL,
//DEADCODE CSB 30/11/99 				FD_COORDINATEDRUDDER,
//DEADCODE CSB 30/11/99 				FD_GEARSUSPENSION,
//DEADCODE CSB 30/11/99 				FD_AUTOTHROTTLE,
//DeadCode AMM 21Feb100 				FD_FF_GUN,					   //not setup			  //RDH 29/11/99
//DeadCode AMM 21Feb100 				FD_FF_BUFFET,		//FD_FF_STALL,//not setup			  //RDH 29/11/99
//DeadCode AMM 21Feb100 				FD_FF_AERODYNAMIC,	//FD_FF_SPEED,//not setup			  //RDH 29/11/99
//DeadCode AMM 21Feb100 				FD_FF_AIRFRAME,//not setup			  //RDH 29/11/99

								FD_MAX};

MAKEFIELD(FlightDifficulty,FD_MIN,FD_MAX);


enum	GameDifficulty		{GD_MIN = 0,

		GD_UNLIMITEDARM = 0,									//RJS 06May99
//DeadCode AMM 9Oct00 		GD_RELOADARMS,											//RJS 25Jan99
//DeadCode AMM 9Oct00 		GD_USAIRCRAFTFITTEDWITHGUNS,
//DeadCode AMM 9Oct00 		GD_GUNJAM,
//DeadCode AMM 9Oct00 		GD_STICKINGORDINANCE,
//DeadCode AMM 9Oct00 		GD_INSIDECOCKPITONLYAVAILABLE,
//DeadCode AMM 9Oct00 		GD_TEXTCHATTER,
		GD_PADLOCKONLYWHENVIS,
//DeadCode AMM 9Oct00 		GD_ALTXTOEXIT,
		GD_TACTICALRANGE,
//DeadCode AMM 9Oct00 		GD_BESTVARIANTS,
		GD_REALISTICRADARASSISTEDGUNSIGHT,
		GD_PERFECTRADARASSISTEDGUNSIGHT,
		GD_VULNERABLE,
		GD_GROUNDCOLLISIONS,
		GD_COLLISIONS,
//DeadCode AMM 9Oct00 		GD_WHITEOUT,
//DeadCode AMM 9Oct00 		GD_BLACKOUT,	//superceded by geffects and injury effects				//last of 1st set
//DeadCode AMM 9Oct00 		GD_PERFECTUSGCI,
//DeadCode AMM 9Oct00 		GD_PERFECTCOMMUNISTGCI,
//DeadCode AMM 9Oct00 		GD_PERFECTCOMMUNISTAAA,
		GD_AUTOPADLOCKTOG,										//PD 18Nov97
		GD_VIEWMODESELECT,										//PD 18Nov97
		GD_UPTOGGLESTICKS,										//PD 18Nov97
//DeadCode AMM 9Oct00 		GD_REDOUT,		//superceded by geffects and injury effects
		GD_AIPILOTSALLTIME,
		GD_MAXOPTION,
//DeadCode AMM 9Oct00 		FRAME_RATE_DISPLAY,
		GD_WEATHEREFFECTS,			//stop using						  //RDH 29/11/99
		GD_PERIPHERALVISION,
		GC_MULTIPLAYERVIEWRESTRICTED,
//DeadCode AMM 10Jul00 		GD_GUNCAMERACOLOUR,
//DeadCode AMM 9Oct00 		GD_INFOLINESTATUS,
		GD_UNITS,
		GD_GUNCAMERAATSTART,
		GD_GUNCAMERAONTRIGGER,
//DeadCode AMM 9Oct00 		GD_GEFFECTS,
//DeadCode AMM 9Oct00 		GD_INJURYEFFECTS,
		GD_AUTOVECTORING,
		GD_HUDINSTACTIVE,
		GD_VISIBLEMIGSCHEAT,
		GD_DISPLAYMESSAGES,
		GD_NOPLAYERVOICE,
		GD_AUTOCANOPY,
		GD_TEXTINFO,		//RJS 30Jun99
		GD_LWTACTICS,
		GD_MAPPLOTTING,
		GD_LWINTELL,
		GD_FLYOPTION,
		GD_RAFTACTICS,

								GD_MAX};

MAKEFIELD(GameDifficulty,GD_MIN,GD_MAX);

enum	HardwareConfig		{	HW_MIN = 0,
								HW_FRONTART,
								HW_MAPEVENTS,
								HW_OPTIONSDIALOG,
								HW_WEATHEREFFECTS,
								HW_GEFFECTS,
								HW_INJURYEFFECTS,
								HW_WHITEOUT,
								HW_RAFVOICE,
								HW_LWVOICE,
								HW_SFXQUALITY,							//RJS 14Jun00
								HW_3DSOUND,
								HW_FLUFFYCLOUDS,

								HW_FF_GUN,						//AMM 07Feb00
								HW_FF_BUFFET,					//AMM 07Feb00
								HW_FF_AERODYNAMIC,				//AMM 07Feb00
								HW_FF_AIRFRAME,					//AMM 07Feb00

								HW_MAX
							};
MAKEFIELD(HardwareConfig, HW_MIN, HW_MAX );
enum	SG_Detail_3D		{DETAIL3D_MIN = 0,
							DETAIL3D_HORIZONFADE=0,
							DETAIL3D_HORIZONDIST,
							DETAIL3D_INCONSEQUENTIALS,
							DETAIL3D_AUTODETAIL,
							DETAIL3D_TRANSSMOKE,
//DeadCode JON 22Sep00 							DETAIL3D_ITEMSHADING,
//DeadCode JON 22Sep00 							DETAIL3D_SPECITEM,							//JON 22Sep00
							DETAIL3D_GROUNDSHADING,
							DETAIL3D_ITEMSHADOWS,
							DETAIL3D_AIRCRAFTSHADOWS,
							DETAIL3D_ROUTES,
							DETAIL3D_CONTOURDETAIL,
							DETAIL3D_PADLOCKCHEAT,
							DETAIL3D_MAX};

MAKEFIELD(SG_Detail_3D,DETAIL3D_MIN,DETAIL3D_MAX);

// Cockpit detail switches...									//RJS 23Jan98
enum	SG_Detail_Cockpit3D
{
	COCK3D_MIN = 0,
	COCK3D_PANELPLAIN = 0,		//plain panel behind dials
	COCK3D_PANELHOODPLAIN,		//plain cowling
	COCK3D_PANELIMAPDSPLIT,		//split panels to stop bend	
	COCK3D_PANELGLASSFRONT,		//reflection map on front
	COCK3D_PANELSHADOWFRONT,	//moving dial shadow maps on front
	COCK3D_DIALSROW1ON,			//top row
	COCK3D_DIALSROW2ON,
	COCK3D_DIALSROW3ON,
	COCK3D_DIALSROW4ON,			//bottom row
	COCK3D_FRONTQIMAPD,			//front quarter artwork
	COCK3D_SIDEQIMAPD,			//side artwork
	COCK3D_REARQIMAPD,			//rear quarter artwork
	COCK3D_GUNSIGHTPANE,		//pane of glass in gunsite
	COCK3D_GUNSIGHTFURNITURE,	//furniture at bottom truncated
	COCK3D_GUNSIGHTTRANS,		//whole gunsite transparent
	COCK3D_SKYTRANS,			//imagemaps in the sky rather than lines
	COCK3D_SKYIMAGES,			//translucent
	COCK3D_SKYWHENDOWN,			//even when looking down into cockpit
	COCK3D_INTERACTIVEON,		//interactive cockpit stuff
	COCK3D_MAX //= 31
};											


//this gives 1 bit per flag above
MAKEFIELD(SG_Detail_Cockpit3D,COCK3D_MIN,COCK3D_MAX);			//RJS 23Jan98

enum	MapFilters	
{
	MAPFILTERSMIN,
//DeadCode RDH 06Jan100 	FILT_BLUE_CIVILIAN,
//DeadCode RDH 06Jan100 	FILT_BLUE_SUPPLY,
//DeadCode RDH 06Jan100 	FILT_BLUE_MYARD,
//DeadCode RDH 06Jan100 	FILT_BLUE_BRIDGE,
//DeadCode RDH 06Jan100 	FILT_BLUE_ROADLINK,
//DeadCode RDH 06Jan100 	FILT_BLUE_RAILLINK,
//DeadCode RDH 06Jan100 	FILT_BLUE_TRUCK,
//DeadCode RDH 06Jan100 	FILT_BLUE_TRAIN,
//DeadCode RDH 06Jan100 	FILT_BLUE_ARTIE,
//DeadCode RDH 06Jan100 	FILT_BLUE_TROOP,
//DeadCode RDH 06Jan100 	FILT_BLUE_TANK,
//DeadCode RDH 06Jan100 	FILT_BLUE_AIRFIELDS,
//DeadCode RDH 06Jan100 	MAPFILTERSMAXBLUE,
//DeadCode RDH 06Jan100 	FILT_RED_CIVILIAN,
//DeadCode RDH 06Jan100 	FILT_RED_SUPPLY,
//DeadCode RDH 06Jan100 	FILT_RED_MYARD,
//DeadCode RDH 06Jan100 	FILT_RED_BRIDGE,
//DeadCode RDH 06Jan100 	FILT_RED_ROADLINK,
//DeadCode RDH 06Jan100 	FILT_RED_RAILLINK,
//DeadCode RDH 06Jan100 	FILT_RED_TRUCK,
//DeadCode RDH 06Jan100 	FILT_RED_TRAIN,
//DeadCode RDH 06Jan100 	FILT_RED_ARTIE,
//DeadCode RDH 06Jan100 	FILT_RED_TROOP,
//DeadCode RDH 06Jan100 	FILT_RED_TANK,
//DeadCode RDH 06Jan100 	FILT_RED_AIRFIELDS,											//RDH 06Jan100

	FILT_OPERATIONALITEMS,
	FILT_DAMAGEDITEMS,
	FILT_DESTROYEDITEMS,
	FILT_STRIKE,

	FILT_AF_FIGHTER,
	FILT_AF_BOMBER,
	FILT_AF_COASTAL,
	FILT_LARGEICONS,

	FILT_BALLOONZONES,
	FILT_FLAKZONES,
	FILT_CH,
	FILT_CHL,
	FILT_DOCK_NAVAL,
	FILT_DOCK_CIV,
	FILT_CONVOYS,
	FILT_FACTORYFIGHTER,
	FILT_FACTORYBOMBER,
	FILT_FACTORYOTHER,
	FILT_OIL,
	FILT_POWER,

	FILT_CITY,
	FILT_TOWN,
	FILT_VILLAGES,
	FILT_LIGHTHOUSES,
	FILT_TUNNELS,

	MAPFILTERSMAXITEMS,
//DEADCODE RDH 13/03/00 	FILT_AUTHENTICPLOTS,
//DEADCODE RDH 13/03/00 	FILT_ESCORTEDBOMBERS,
//DEADCODE DAW 01/06/00 	FILT_FIGHTERSWEEPS,
	FILT_LWARROWS,
//DEADCODE RDH 13/03/00 	FILT_LWROUTELINES,
	FILT_LWTARGETLINES,
//DEADCODE DAW 01/06/00 	FILT_RAFTARGETLINES,
//DEADCODE DAW 31/05/00 	FILT_MYWAYPOINTS,
//DEADCODE RDH 10/03/00 	FILT_ONEPLOTPERGESCHWADER,
//DEADCODE RDH 10/03/00 	FILT_ONEPLOTPERGRUPPE,
//DEADCODE RDH 10/03/00 	FILT_ONEPLOTPERRAID,
	FILT_RAFINTERCEPTS,
	FILT_RAFPATROLS,
	FILT_BOMBERS,
	FILT_RECONN,
	FILT_RAFSAG,
	FILT_LWSAG,

//DEADCODE RDH 13/03/00 	  FILT_MAINWP,
//DEADCODE RDH 13/03/00 	  FILT_SUBWP,
//DEADCODE RDH 13/03/00 	  FILT_ROUTES,
//DEADCODE RDH 13/03/00 	  FILT_FRONTLINE,

	MAPFILTERSMAX
};
MAKEFIELD(MapFilters,MAPFILTERSMIN,MAPFILTERSMAX);
enum	ToolBars	
{	TB_TITLE,TB_MAIN,TB_REPORT,TB_MISC,TB_COMMS,TB_FILTERS,TB_STATUS,TB_SCALE,TB_SPACE,TB_TOTAL};
MAKEFIELD(ToolBars,0,TB_TOTAL);



enum ProcType {PROC_SLOW=0,PROC_MIN,PROC_MED,PROC_MAX};

enum	TargetSize		{TS_MIN = 0,TS_SMALL=0,TS_MEDIUM,TS_LARGE,TS_MAX};//PD 30Aug96
//DeadCode RDH 24Oct96 	enum					{MAXWEATHERNUM = 3};
//DEADCODE RDH 10/03/00 enum	LWPlots	{
//DEADCODE RDH 10/03/00 	LARGEPLOTS, ONEPLOTPERRAID,ONEPLOTPERGESCHWADER, 
//DEADCODE RDH 10/03/00 		ONEPLOTPERGRUPPE,  ONEPLOTPERSTAFFEL};

//------------------------------------------------------------------------------
//Author		R. Hyde 
//Date			Mon 22 Apr 1996
//Modified	
//
//Description	
//
//Inputs		
//------------------------------------------------------------------------------
enum	DateOrder	{DO_UK_DMY,DO_US_MDY,DO_JP_YMD};

struct	DistanceFactors
{
	int	shortnm,		//CM or IN				in nm
		mediummm,		//METRES or YARDS		in mm
		longcm;			//KM or MILES			in cm
	int	shortname,
		mediumname,
		longname;
	int	shortabbr,
		mediumabbr,
		longabbr;
};

struct	AltitudeFactors
{
	int	shortnm,		//CM or IN							in nm
		mediummm,		//METRES or FEET					in mm
		longcm;			//thousands of metres or feet		in cm
	int	shortname,
		mediumname,
		longname;		//THOUSAND FEET
	int	shortabbr,
		mediumabbr,
		longabbr;		//'000FT
	int mediumstepsize,
		minstepcount,	//controls list of offered altitudes
		maxstepcount;
};
struct	SpeedFactors
{
	float
		mmpcs2persec,
		mmpcs2permin,
		mmpcs2perhr;
	int	persecname,
		perminname,
		perhrname;
	int	persecabbr,
		perminabbr,
		perhrabbr;

};
struct	MoneyFactors
{
	int		penceperunit;
	int		fractionsperunit;
	char	fractionseparator;
	int		fractionmane,
			unitname,
			fractionabbr,
			unitabbr;
};
struct	MassFactors
{
	int		gm;		  //in kg or lb
	int		nametype;
	int		abbrtype;
};
struct	VolumeFactors
{
	int		type;
	int		nametype;
	int		abbrtype;
};
enum	PlotLevels	{PL_REALISTIC,PL_RAID,PL_GESH,PL_GRUP,PL_STAFF};
class	SaveDataSoftware			//Only this portion is saved in a savegame
{
public:
	enum	Units		{METRIC,IMPERIAL,UNITS_LEN};
	enum	Currency	{ENGLISH,CURRENCY_LEN};
	enum	{NAMEARRAYSIZE = 20};
	FlightDifficultyField	flightdifficulty;
	GameDifficultyField	gamedifficulty;
	//GameSettings	gameSettings;
	MapFiltersField		mapfilters;
	PlotLevels			lwplots;
	ToolBarsField		toolbars;
	TargetSize targetsize;										//PD 30Aug96
	DateOrder	dateorder;
	UByte	metricdistance:1,
			metricspeed:1,
			metricalt:1;
	SWord	messagelines;										//RDH 01Oct96
//DeadCode CSB 27Jul00 	SWord	autopilotskillUN;		//csb remove					  //RDH 24/11/99
//DeadCode CSB 27Jul00 	SWord	autopilotskillRED;		//csb remove					  //RDH 24/11/99
	SWord	autopilotskillLW;
	SWord	autopilotskillRAF;
	SWord	rangediv,speeddiv;
	DistanceFactors	dist;
	AltitudeFactors	alt;
	SpeedFactors	speed;
	MoneyFactors	curr;
	MassFactors		mass;
	int			keysensitivity;										  //JIM 11/06/99
	SWord	infoLineCount;
	float	defaultzoom;
	float	secondzoom;
	float	currzoom;
	int		currmapx,currmapy;
	int		currmapx2,currmapy2;
	char	CommsPlayerName[PLAYERNAMELEN];
	struct	DialPosMem
	{
		SWord	ID,
				l,t,r,b;
		SWord	flagsspare[3];
	};
	DialPosMem	dialposmem[70];		//currently 46 dialogues
	UWord	nextdialposmem;
	int	minsbetweensavegame,savegamesecscounter;
};

class	SaveDataLoad:public SaveDataSoftware  //Both portions saved on exit
{		//NOTE THIS SECTION IS FOR HARDWARE SETTINGS
		//IT IS NOT SAVED IN A SAVEGAME. IT IS NOT TRANSMITTED IN COMMS!
public:
	enum	ResUI		{UIR_SMACKER,UIR_SCRAMBLE,UIR_MAP,UIR_FRAG,UIR_FIRST,UIR_FIRSTH,UIR_FIRSTFREQ,UIR_FIRST_DEPTH,UIR_FIRST_FLAGS,UIR_APPBARSIDES_ON,UIR_APPBARSIDES_TOP,UIR_MAX};
	enum	ResUICopy	{UIRC_DESK,UIRC_MAP};	
	//GameSettings	gameSettings;
	HardwareConfigField		hardwareconfig;
	SWord	ui_horizontalres[UIR_MAX];
	SWord	ui_colourdepth;
	SWord	ui_winx,ui_winy,	//zero width means never set up
			ui_winw,ui_winh;	//negative width means start fullscreen
//TEMPCODE JIM 05/04/00 	HWND	appbars[4];
	void	ChangeMode(ResUI modepoint);

	SG_Detail_3DField	detail_3d;
	SWord filtering;
	UWord textureQuality;
	SWord	pixelsize;
	SWord	gammacorrection;
	SWord	desiredfps;
	SWord	itemShading;												//JON 22Sep00
	struct	Vol {	// Duplicated in comms.h					//ARM 04Oct96
				SWord	sfx;
				SWord	engine;
				SWord	anim;
				SWord	music;									//RJS 21Aug96
				SWord	rchat;									//RJS 11Jun98
				SWord	uisfx;									//RJS 12Mar99
				SWord	uiambient;								//RJS 12Mar99
				}	vol;
	GUID	MusicDevice;
	GUID	SFXDevice;
//DEADCODE MS 30/11/99 	SLong	missiontime;										//RDH 22Nov96
	ULong	hDriver; //PD 03/12/99
	ULong	hMode; //PD 03/12/99
	UWord	screenshotframe;
//	SWord	screenresolution;									//RDH 22Oct96
//	SWord	colourdepth;										//PD 04Feb97
//	SWord	displayW,displayH;
//	SWord	dddriver;											//PD 22May97
	ProcType processorType;
//	SDrivers sd;
//	bool	fNoHardwareAtAll;
//	bool	fSoftware;
	UByte	viewwobble;											//PD 18Nov97
	UByte	contourDetail;												//JON 2Aug00
	SG_Detail_Cockpit3DField	cockpit3Ddetail;									//RJS 23Jan98
	SWord	SeekStep,PingStep,PingDelay,SeekingDelay;
	ANGLES  fieldOfView;
	bool	successfulLoad;
//DEADCODE JIM 02/12/99 	bool	ThreeDeeSound;										//RJS 08Nov99

//DeadCode AMM 19Jan99 	char	CommsPassword[11];									//AMM 14Dec98

//not included until needed	VolumeFactors	volume;
	protected:
	private:

};
class	SaveDataNoLoad:public	SaveDataLoad
{
public:
#if defined(__AFX_H__) || defined(CSTRING_Included)
	CString		lastsavegame,lastreplayname,lastpackname;
#endif			//Of these only lastreplayname should be stored in savegame.
	void	InitPreferences(int);
	void	SavePreferences();
	void	SetUnits();
	bool	InitMusicDevice();
	bool	InitSoundDevice(int wh);
	bool	LoadedMusicDeviceOK();
	bool	LoadedSFXDeviceOK();

};

typedef SaveDataNoLoad	SaveData;

extern	SaveData Save_Data;
extern	SaveData Temp_Data;

class	BIStream;
class	BOStream;
class	MissMan;
class	SaveDataNoLoad;
typedef	SaveDataNoLoad	SaveData;
//DeadCode RDH 24Sep96 	BIStream& operator	<<	(BIStream&,MissMan&);
//DeadCode RDH 24Sep96 	BOStream& operator	>>	(BOStream&,MissMan&);
//DeadCode RDH 24Sep96 	BIStream& operator	<<	(BIStream&,SaveData&);
//DeadCode RDH 24Sep96 	BOStream& operator	>>	(BOStream&,SaveData&);

//called from mfc\filing.cpp & 
	BIStream& operator	>>	(BIStream&,MissMan&);
//called from mfc\filing.cpp & 
	BOStream& operator	<<	(BOStream&,MissMan&);
	BIStream& operator	>>	(BIStream&,SaveData&);
	BOStream& operator	<<	(BOStream&,SaveData&);




class	WorldStuff;
struct	DamageDef;
class	DeadStream
{
public:
	//This is a stream of records of following format:
	//	UID
	//	HowLongDead
	//	Shape
	//  first byte of anim: contains num launchers to skip
	//	Len of anim
	//	Anim
	enum	{maxblocksize=1024};			//JIM 04Nov96
	struct	DeadBlock
	{
//DEADCODE JIM 24/02/99 	struct	T_SGT{											
//DEADCODE JIM 24/02/99 			UWord	value;									
//DEADCODE JIM 24/02/99 			operator UniqueID()	{return (UniqueID(value));}			
//DEADCODE JIM 24/02/99 			UniqueID operator = (UniqueID v)	{return (UniqueID(value=v));}
//DEADCODE JIM 24/02/99 		}	SGT;	
		ONLYFIELD(UWord,UniqueID,SGT);
		UWord		dataused;
		DeadBlock*	nextblock;
		char data[maxblocksize];
		DeadBlock(UniqueID sgt=UID_NULL) {nextblock=0;(int&)(data[0])=0;dataused=0;SGT=sgt;}
	};
	typedef	DeadBlock* DeadBlockPtr;

	class	DeadBlockItterator;
//	{
//		bool newpage;
//		UniqueID		SGT;
//		DeadBlockPtr*	base;
//		DeadBlockPtr	curr;
//		char*			off;
//		DeadBlockItterator(DeadBlockPtr& deadbase,UniqueID sgt=UID_NULL);
//		bool	PutInfo(void*,int);			//true if new page
//		bool	PutCountedInfo(void* v,int i) {bool rv=PutWord(i);rv|=PutInfo(v,i);return rv;}
//		bool	PutByte(UByte i)	{return PutInfo(&i,1);}
//		bool	PutWord(UWord i)	{return PutInfo(&i,2);}
//		bool	PutLong(int i)		{return PutInfo(&i,4);}
//		bool	PutItemID(ItemBasePtr);
//		void	GetInfo(void*,int);
//		int		GetCountedInfo(void* v,int max) 
//		{int count=GetWord();if (count<max) GetInfo(v,count) else return -count; return count;}
//		UByte	GetByte()	{UByte	rv;GetInfo(&rv,1);return rv;}
//		UWord	GetWord()	{UWord	rv;GetInfo(&rv,2);return rv;}
//		int		GetLong()	{int	rv;GetInfo(&rv,4);return rv;}
//		ItemBasePtr
//				GetItemID();
//		UniqueID	NextSGT()	
//		{if (curr && curr->nextblock) return curr->nextblock->SGT; else return UID_NULL;}
//	};


	int	olddaytime;
	DeadBlock* firstblock;
	//init all to zero
	bool	ClearForSGT(UniqueID);

	void	SetWorldDead(WorldStuff* world);	//this sets the static data to reflect the world
	void	GetWorldDead(WorldStuff* world);	//this sets the world to reflect the static data
	void	ClrWorldDead();
	void	ReviveWorld(const int repairpointsinperiod=7,const int repairbridgepointsinperiod=2);
	int	DecodeDamage(UniqueID SGT,DamageDef* damagetable);
	static	bool	MainWorldBand(UniqueID u);
	static	bool	DontRecordBand(UniqueID u);
//DeadCode JIM 17Aug00 	void	ScoreSGKills();
	void	FakeDamage(UniqueID,ULong newpercent,bool clearifreducedamage=false);

};
extern	DeadStream	Dead_Stream;
class	ItemBase;
typedef	ItemBase *ItemBasePtr;
#ifndef	__BCPLUSPLUS__
class	DeadStream::DeadBlockItterator
	{
		friend	DeadStream::DeadBlockItterator;
		bool newpage;
		UniqueID		SGT;
		DeadBlockPtr*	base;
		DeadBlockPtr	curr;
		int			off;
		void	DeleteTempBlock();
public:
		int			lastnumelts;
		SWord	lastuniqueID;	//access with myitem->uniqueID.count
		SWord	lastStatus;		//access with myitem->Status.size
		SWord	lastshape;
		CON		DeadBlockItterator(DeadBlockPtr& deadbase,UniqueID sgt=UID_NULL);
		DES		~DeadBlockItterator();
		CON		DeadBlockItterator(const DeadBlockItterator* clone)
		{
			if (clone->newpage && !clone->off)
				INT3;
			*this=*clone;
			newpage=false;
		}
		bool	PutInfo(void*,int);			//true if new page
		bool	PutCountedInfo(void* v,int i) {bool rv=PutWord(i);rv|=PutInfo(v,i);return rv;}
		bool	PutByte(UByte i)	{return PutInfo(&i,1);}
		bool	PutWord(UWord i)	{return PutInfo(&i,2);}
		bool	PutLong(int i)		{return PutInfo(&i,4);}
		bool	PutItemID(ItemBasePtr);
		void	GetInfo(void*,int);
		int		GetCountedInfo(void* v,int max) 
		{int count=GetWord();if (count<max) {GetInfo(v,count); return count;} return -count;}
		int		SkipCountedInfo();
		UByte	GetByte()	{UByte	rv;GetInfo(&rv,1);return rv;}
		UWord	GetWord()	{UWord	rv;GetInfo(&rv,2);return rv;}
		int		GetLong()	{int	rv;GetInfo(&rv,4);return rv;}
		ItemBasePtr	GetItemID();
		UniqueID	NextSGT();
		bool	SkipToSGT(UniqueID sgt);
		char*	GetPointerToCurrent()	{return curr->data+off;}
		void	NextDeadElt(UByte&di1b,int&diplc,char*&dipld);
		void	SetNextDeadElt(char di1b,int diplc,char* dipld);
		void	SkipNextDeadElt();
	 	void	NextEltClearDamage();
		UniqueID	SkipItem();
		bool		SkipToItem(UniqueID u);
		bool	MoveOwnerOfRestOfListToEndOf(DeadStream::DeadBlock* second);
	};
#endif


#endif
