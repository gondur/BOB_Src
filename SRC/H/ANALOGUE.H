//------------------------------------------------------------------------------
//Filename       analogue.h
//System         
//Author         Jim Taylor
//Date           Thu 14 Mar 1996
//Description    Rowan DirectX joystick interface header.
//
//------------------------------------------------------------------------------
#ifndef	ANALOGUE_Included
#define	ANALOGUE_Included

#include	"DosDefs.h"
#include	"Enumbits.m"
#include	"BitField.h"
#include	"HardPAsm.h"
//DEADCODE JIM 30/04/99 #include	"text.h"
//DEADCODE JIM 30/04/99 #include	"stub.m"
//DEADCODE JIM 30/04/99 #include	"files.g"
#include	"keytest.h"

//DeadCode JIM 30Apr97 #else
//DeadCode JIM 30Apr97 	#define XP
//DeadCode JIM 30Apr97 	#define CB
//DeadCode JIM 30Apr97 #endif

//DeadCode ARM 09Jul96 #include	"windows.h"
//DeadCode ARM 09Jul96 #include	"windowsx.h"
//DeadCode ARM 09Jul96 #include	"mmsystem.h"

#define	DEFAULT_ANALOGUE 0
#ifndef AXIS_USES
#define	AXIS_USES
//DeadCode CSB 06/04/99	enum	DeadZones	{DZ_SMALL = 1024, DZ_MEDIUM = 2048, DZ_LARGE = 3096};
enum	DeadZones	{DZ_SMALL = 512, DZ_MEDIUM = 1536, DZ_LARGE = 3072};	//CSB 06/04/99	
enum	AnalogMode	{ AM_ARCADE, AM_REALISTIC,
						 AM_LOW, AM_MEDIUM, AM_HIGH, AM_ABSOULTE};
enum	AxisUses		{	AU_UNUSED=-1,AU_UNASSIGNED=-1,
							AU_AILERON=0,AU_ELEVATOR,AU_RUDDER,AU_THROTTLE,
							AU_UI_X=4,AU_UI_Y,AU_COCKPIT=AU_UI_X,
							AU_COLLECTIVE=6,AU_COOLIEHAT=7,
							AU_VIEWH=8,AU_VIEWP,AU_VIEWR,AU_VIEWZ,
							AU_GUNH=12,AU_GUNP,
						  	AU_WALKSPEED=14,AU_WALKTURN,
							AU_FLAPS=16,AU_BRAKE,AU_TRIM_ELEV,AU_ABSTEPS,

							AU_THROTTLE2=20,AU_PROPPITCH, AU_PROPPITCH2, 

							AU_MIN=0,AU_MAX=31,AU_ILLEGAL=127,
							MAXFORCEAXES=10	//list of FF actuator GUIDs
						};
#endif
//enum	FeedBackUses	{
//							//spares: 20-29
//							AU_FB_CTRLFORCE=0,
//							AU_FB_CTRLSTIFF=1,
//							AU_FB_CTRLSHAKE=2,
//							AU_FB_PILOTFORCES=3,
//						};


#ifndef GUID_DEFINED
#define GUID_DEFINED

#ifdef DECLARE_HANDLE
DECLARE_HANDLE(HINSTANCE);
#else

#ifdef STRICT
typedef void *HANDLE;
#else
typedef	void*	PVOID;
typedef PVOID HANDLE;
#endif

//DEADCODE DAW 29/01/00 #ifndef IN_SAGMOVE
//DEADCODE DAW 29/01/00 typedef HANDLE HINSTANCE ;
//DEADCODE DAW 29/01/00 #endif
//DEADCODE DAW 29/01/00 
#endif


typedef struct _GUID {          // size is 16
    SLong	Data1;
    SWord   Data2;
    SWord   Data3;
    SByte	Data4[8];
} GUID;

#endif // !GUID_DEFINED
struct IDirectInputA;
struct IDirectInputDeviceA;
struct IDirectInputDevice2A;
typedef struct IDirectInputEffect *LPDIRECTINPUTEFFECT;


struct	RunTimeDevDesc
{
	enum	{MAXMAPS=8};
	GUID	devid;
	bool	useff,
			usedelta,bigdead,ismouse;		//not implemented
	IDirectInputDeviceA*
			dev;
	IDirectInputDevice2A*
			dev2;
	char	axismaps[MAXMAPS];
	char	backupaxismaps[MAXMAPS];
	char	sh_axismaps[MAXMAPS];
	char	hatmaps[MAXMAPS];
//DEADCODE RDH 25/05/00 	char	sh_hatmaps[MAXMAPS];
	char	prevhatbuts[MAXMAPS];
//DEADCODE RDH 25/05/00 	char	sh_prevhatbuts[MAXMAPS];
	RunTimeDevDesc()	{dev2=NULL;dev=NULL;}

};

//------------------------------------------------------------------------------
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//Modified
//
//Description	This record describes 1 axis.
//		To set a force use _Analogue.ForceName.Set(parmeters)
//						or _Analogue.ForceName.SetX(reduced parmeters)
//						or _Analogue.ForceName.SetZ(reduced parmeters)
//
//Inputs		
//------------------------------------------------------------------------------
struct	FF_Push
{
//DeadCode CSB 17Aug00 	UByte	level;
	bool	triggerX,triggerZ;
	SWord	MX,MZ;
	int		durationX,durationZ;
	IDirectInputDevice2A* dev;
	LPDIRECTINPUTEFFECT pForceX;
	LPDIRECTINPUTEFFECT pForceY;
	FF_Push()	{pForceX=pForceY=NULL;}
	void	Init(IDirectInputDevice2A* d);
	bool	Set(SWord x,SWord z,int duration);
	bool	SetX(SWord val,int duration);
	bool	SetZ(SWord val,int duration);
	bool	Poll();
	bool	Tick();
};
struct	FF_Damp
{
//DeadCode CSB 17Aug00 	UByte	level;
	bool	trigger;
	SWord	MX,MZ;
	IDirectInputDevice2A* dev;
	LPDIRECTINPUTEFFECT pDampX;
	LPDIRECTINPUTEFFECT pDampY;
	FF_Damp()	{pDampX=pDampY=NULL;}
	void	Init(IDirectInputDevice2A* d);
	bool	Set(SWord x,SWord z);
	bool	SetX(SWord val);
	bool	SetZ(SWord val);
	bool	Poll();
	bool	Tick()	{return false;}
};

struct	FF_Stiff
{
//DeadCode CSB 17Aug00 	UByte	level;
	bool	trigger;
	SWord	CX,CZ;
	SWord	SX,SZ;
	IDirectInputDevice2A* dev;
	LPDIRECTINPUTEFFECT pStiffX,pStiffY;
	FF_Stiff()	{pStiffX=pStiffY=NULL;}
	void	Init(IDirectInputDevice2A* d);	
	bool	Set(SWord cx,SWord cz,SWord sx,SWord sz);
	bool	SetX(SWord centre,SWord size);
	bool	SetZ(SWord centre,SWord size);
	bool	Poll();
	bool	Tick()	{return false;}
};
struct	FF_Shake
{
//DeadCode CSB 17Aug00 	UByte	level;
	bool	triggerX,triggerZ,
			randomX,randomZ,
			lastrandomX,lastrandomZ;
	IDirectInputDevice2A* dev;
	LPDIRECTINPUTEFFECT pRandX;
	LPDIRECTINPUTEFFECT pRandY;
	LPDIRECTINPUTEFFECT pShakeX;
	LPDIRECTINPUTEFFECT pShakeY;
	SWord	MX,MZ;
	SWord	FX,FZ;
	FF_Shake()	{pRandX=pRandY=pShakeX=pShakeY=NULL;}
	void	Init(IDirectInputDevice2A* d);
	bool	Set(SWord mx,SWord mz,SWord fx,SWord fz,bool rnd);
	bool	SetX(SWord mag,SWord freq,bool rnd);
	bool	SetZ(SWord mag,SWord freq,bool rnd);
	bool	Poll();
	bool	Tick()	{return false;}
};

#define	WORKSPACESIZE	5120
#define	MAXDEVICES		20
#define	MAXPAGES		5
#define NUMBUTTONS		4
typedef	AxisUses	axisconfigpage[4];
typedef	axisconfigpage	*	const	axisconfigpages;
//------------------------------------------------------------------------------
//Author		Jim Taylor
//Date			Thu 14 Mar 1996
//Modified	
//
//Description	
//
//Inputs		
//------------------------------------------------------------------------------
class	Inst3d;
class	BOStream;
class	BIStream;
class	CRCombo;
class	ViewPoint;
	enum	AllowAliasing	{
							AA_NONE=0,		AA_GUNNER_JOYVIEW,		AA_THROTTLE2_PROP1,		AA_UI_PAN,	
								AA_TT_REVERSE,	//this is a cludge: 1 bit flag to say axis is reversed...
								AA_PAIR_MAX,AA_AA_SETUP
							};
//DeadCode JIM 9Oct00 	enum	AllowReset		{
//DeadCode JIM 9Oct00 							AR_NORESET
//DeadCode JIM 9Oct00 							AR_DEADZONE80000000
class	Analogue
{
public:
	bool	mouseusesabsolute,forcedevicerestart;
	friend class CSSound;
	friend	BOStream& operator	<<	(BOStream& bos,Analogue& analogue);
	friend	BIStream& operator	>>	(BIStream& bis,Analogue& analogue);
//private:
	bool	GetFirstJoystick(GUID &,int* axes=NULL,int* buttons=NULL,int* hats=NULL);
	bool	GetFirstMouse(GUID &,int* axes=NULL,int* buttons=NULL);
	SWord		axisvalues[(int)AU_MAX+1];
public:
	struct Tuning
	{
		SWord	deadzones;
		UByte	mode;
		MAKEFIELD(AllowAliasing,AA_NONE,AA_PAIR_MAX);
		AllowAliasingField	aliased;
		bool	allowmouseresetF5;
		bool	discardnegative;
//DeadCode JIM 4Sep00 		bool	reverse:1,
//DeadCode JIM 4Sep00 				isaliased:1;

	}	tune[AU_MAX];


	struct	AliassingOption
	{	AllowAliasing	gamereason;
		AxisUses		aliasedtask;
		int				aliaseed_IDS;
		int				aliassertask;
		bool			aliassedtaskgotanalogueinput;
		int				aliassercomboindex;
		CRCombo*			aliassedcombo;
	};

	static	  AliassingOption	Aliassing_List[],*Aliassing_Table[];
	AllowAliasing	curraliasingmode,currUIaliasingmode;
//DEADCODE JIM 19/06/00 	SWord		deadzones[(int)AU_MAX]; 
//DEADCODE JIM 19/06/00 	SWord		mode[(int)AU_MAX];
//DEADCODE JIM 19/06/00 	bool		reverse[(int)AU_MAX];							//AMM 28Mar100
	UByte FF_gun, FF_buffet, FF_aerodynamic, FF_airframe;				//CSB 17Aug00
	int		axisbases[+AU_MAX+1];
	SWord		axisscales[+AU_MAX+1];
	SWord		axisdeltas[+AU_MAX+1];
	int			ForceAxes[MAXFORCEAXES];//list of FF actuator GUIDs
	RunTimeDevDesc	
				runtimedevices[MAXDEVICES];
	IDirectInputA*	DIdev;
	FF_Push		FFpush;
	FF_Stiff	FFstiff;
	FF_Shake	FFshake;
	FF_Damp		FFdamp;
//private:
	IDirectInputDevice2A*	FFdevice;
	int	lastFFeffect;
public:

	bool	usingMouseToPan;											//RJS 28Jul00
	bool	noGunner;													//RJS 29Aug00

	void	ResetF5();
//DeadCode AMM 21Feb100 	Bool	Initialise(int HWNDw,int HINSTANCEi);
	Bool	Initialise(int HWNDw,int HINSTANCEi,AllowAliasing mousemode,AllowAliasing aliasmode,bool reinit=false);
	bool	WhatAliasModes(AllowAliasing& mousemode,AllowAliasing& aliasmode,ViewPoint* newwin);
	Bool	LoadGame();
	Bool	CloseDown();
	void	ZeroForces();
	void	PollPosition();
	void	PollForces();
	SWord	ReadPosition(AxisUses reqaxis);
	bool	readytopoll;
//DeadCode  11Aug00 	bool	IsTaskShiftedMouse(int task);
//DeadCode  11Aug00 	bool	IsTaskShiftedJoystick(int task);
//DeadCode AMM 27Jul00 	void	SetAxesFromShiftedAxes(int devnum);
	void	BackupAxes(int devnum);
	void	SetAxesFromBackup(int devnum);
	void	BackupAllDeviceAxes();
	void	SetAllAxesFromBackup();
	void	SetDeviceAxisFlags();
	int		TransAxis(int startaxis);

	UWord	AxisDeviceFlags;

	enum	DeviceFlags
	{
		COCKPIT_ON_SH_MOUSE=0,
		COCKPIT_ON_SH_JOYSTICK,
		PAN_ON_SH_MOUSE,
		PAN_ON_SH_JOYSTICK,
		PAN_ON_MOUSE,
		PAN_ON_JOYSTICK,
		GUN_ON_SH_MOUSE,
		GUN_ON_SH_JOYSTICK,
		GUN_ON_JOYSTICK,
		GUN_ON_MOUSE
	};

//DeadCode  11Aug00 	bool	CockpitOnShiftedMouse;
//DeadCode  11Aug00 	bool	CockpitOnShiftedJoystick;
//DeadCode  11Aug00 	bool	PanOnShiftedMouse;
//DeadCode  11Aug00 	bool	PanOnShiftedJoystick;
//DeadCode  11Aug00 	bool	PanOnMouse;
//DeadCode  11Aug00 	bool	PanOnJoystick;
//DeadCode  11Aug00 	bool	GunnerOnShiftedMouse;
//DeadCode  11Aug00 	bool	GunnerOnShiftedJoystick;
//DeadCode  11Aug00 	bool	GunnerOnJoystick;
//DeadCode  11Aug00 	bool	GunnerOnMouse;

	Analogue();
	~Analogue();
	void Test();
};

extern	Analogue	_Analogue;
#endif
