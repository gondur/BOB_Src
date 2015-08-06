//------------------------------------------------------------------------------
//Filename       intcock.h
//System         
//Author         Robert Slater
//Date           Fri 19 Nov 1999
//Description    
//------------------------------------------------------------------------------
#ifndef	INTCOCK_Included
#define	INTCOCK_Included

#define	DEFAULT_INTCOCK 0


enum	InstDirection
{
	INSTDIR_NULL = 0,
	INSTDIR_LEFTRIGHT,
	INSTDIR_UPDOWN
};

enum	InstrumentKey
{
	INST_NULL = 0,
// Interactive levers/buttons/switches...
	INST_MAP,
	INST_RADIO,
	INST_THROTTLE,
	INST_THROTTLE1,
	INST_MAGNETO1,
	INST_MAGNETO2,
//DeadCode CSB 03/12/99		INST_MAGNETO3,
//DeadCode CSB 03/12/99		INST_MAGNETO4,
	INST_MAGSLIDE1,
	INST_MAGSLIDE2,
	INST_FLAPSUP,
	INST_FLAPSDOWN,
	INST_CONTROL,
	INST_RUDDER,				//rudder trim
	INST_UNDERCARRIAGE,
	INST_ARMED,
	INST_UNDERFLAP,
	INST_ELEVATOR, 				//elevator trim
	INST_EMERGENCYUC,
	INST_PROPPITCH,
	INST_PROPPITCH1,
	INST_PRIMER,
	INST_PRIMER1,
	INST_FUELCOCKMAIN,
	INST_FUELCOCKRESERVE,
	INST_ENGINESTARTER,
	INST_ENGINESTARTER1,										//RJS 13Apr00
	INST_BOOSTCUTOUT,
	INST_LANDING,
	INST_GUNCAM,
	INST_GUNSIGHT,
	INST_HOODCATCH,
	INST_HOODJETTISON,
	INST_FUELTANKSELECT,
	INST_DIVEBRAKES,											//CSB 24May00

// Dials / Lights info...

	INST_ALT,
	INST_CLOCK,
	INST_AIRSPEED,
	INST_ARTHORIZ,
	INST_CLIMB,
	INST_RADIOALT,
	INST_DIRECTION,
	INST_TURN,
	INST_MECHUC,
	INST_FUELCONTENT,
	INST_FUELPRESSURE,
	INST_OILCONTENT,
	INST_OILPRESSURE,
	INST_OILTEMP,
	INST_RADIATORTEMP,
	INST_BOOST,
	INST_VOLTMETER,
	INST_COMPASS,
	INST_PITCH,
	INST_FLAPINDICATOR,
	INST_GUNAMMO,
	INST_CANNONAMMO,

// New info...
	INST_ENGINESPEED,
	INST_ELEVDIAL,
	INST_UCINDICATOR,
	INST_PPITCHDIAL,
	INST_DIVEPRESETIND,

	INST_MAXINSTRUMENT
};

enum	InstControlType
{
	ICT_NULL = 0,
	ICT_SWITCH = 1,
	ICT_SELECT = 2,
	ICT_SLIDE = 4,
	ICT_HOLDDOWN = 8													  //CSB 25/01/00
};

struct	InstTableMap
{
	KeyVal3D		keyenum;
	InstControlType	control;
	ULong			resourcestring;
	InstDirection	direction;
	SWord			theDelta;
	SLong			theVal;
	ULong			fontColour;
	FileNum			sfxfile;

private:

	bool			isSet;

public:

	InstTableMap()
	{
		keyenum = (KeyVal3D)0;
		control = ICT_NULL;
		resourcestring = 0;
		direction = INSTDIR_NULL;
		fontColour = 0x00FFFFFF;
		sfxfile	= FIL_NULL;

		theDelta = 0;
		theVal = 0;
		isSet = false;
	}

	void	Add(ULong	newkey, InstControlType newcontrol, ULong newstring, InstDirection newdir, const ULong& theCol, FileNum sfx)
	{
		keyenum = (KeyVal3D)newkey;
		control = newcontrol;
		resourcestring = newstring;
		direction = newdir;
		fontColour = theCol;								//RJS 09May00
		sfxfile = sfx;
	}

	bool	IsSet(){return isSet;}
	void	Set(bool	newstate){isSet = newstate; if (newstate==false) theDelta=0;}
};


class	InteractiveCockpit
{
	bool			lastWasValid;
	bool			lastMousePressed;
	InstControlType	lastControl;
	KeyVal3D		lastKeyPress;
	ULong			lastString;
	SWord			lastMouseX,hitMouseX;
	SWord			lastMouseY,hitMouseY;
	InstDirection	lastDirection;
	SLong			screenWidth,screenHeight;
	InstrumentKey	lastIndex;
	ULong			lastFontColour;


	InstTableMap	keytocontrol[INST_MAXINSTRUMENT];

	void	Add(InstrumentKey p1, ULong p2, InstControlType p3, ULong p4, InstDirection p5=INSTDIR_NULL, const ULong& theCol=0x00FFFF00)
	{
		keytocontrol[p1].Add(p2,p3,p4,p5,theCol, FIL_NULL);
	}

	void	Add(InstrumentKey p1, ULong p2, InstControlType p3, ULong p4, FileNum sfx = FIL_NULL, const ULong& theCol=0x00FFFF00)
	{
		keytocontrol[p1].Add(p2,p3,p4,INSTDIR_NULL,theCol, sfx);
	}

	void	Add(InstrumentKey p1, ULong p4, const ULong& theCol=0x00FF8800)
	{
		// No key, or control

		keytocontrol[p1].Add(0,ICT_NULL,p4,INSTDIR_NULL,theCol, FIL_NULL);
	}


public:

	InteractiveCockpit();
	
	void	Clear();
	void	ClearCollide(bool);
	void	Collide(InstrumentKey,bool);
	void	LogMousePos(SWord,SWord,SLong,SLong);
	void	Process();
	void	ProcessSlider();
	void	ProcessHoldDown();
	SLong	GetDelta(InstrumentKey, SLong&);
	ULong	GetStringResource(ULong&);


	
};

extern class InteractiveCockpit	_Interactive;


#endif
