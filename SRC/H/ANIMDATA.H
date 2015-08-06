//------------------------------------------------------------------------------
//Filename       animdata.h
//System         
//Author         Robert Slater
//Date           Mon 10 Feb 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	ANIMDATA_Included
#define	ANIMDATA_Included

#define	DEFAULT_ANIMDATA 0

typedef	void	*detectrtnref;

const	int		MAX_WEAP_LAUNCHERS =	5;							//RJS 15Nov99


//For now, keep anim flags under 1 byte each to allow easy indexing

//enum	ItemState {DEAD = -1,ALIVE,DAMMAGED,DYING};
enum	ItemState {ALIVE=0,DAMMAGED,DYING,DEAD};				//RJS 23Nov99

enum	WarningLights	{STALLON=1,PRESTALLON=2,BRAKEON=4,WBRAKEON=8};
enum	ToggleLights	{FLAPSON=1,GEARON=2,WBREAKON=4,BREAKON=8};


class	MinAnimData
{
public:
	UByte		nolaunchers:3,									//RJS 23Nov99
				IsBullied:1,									//RJS 03Dec98
				itemstate:2,									//RJS 23Nov99
				IsInvisible:1,									//RJS 23Nov99
				repair:1;										//RJS 23Nov99
};

class	GrpMinAnimData
{
public:
	UByte		nolaunchers:3,									//RJS 23Nov99
				IsBullied:1,
				itemstate:2,									//RJS 23Nov99
				IsInvisible:1,									//RJS 23Nov99
				repair:1;										//RJS 23Nov99
};

class	SunAnimData:public	MinAnimData							
{																
public:															
	Bool	wasdrawn;
	UByte	fader;												//RJS 22Jun98
	UByte	frameno;											//RJS 02Jul98
};																

class	ExplodeAnimData:public	MinAnimData						
{
public:
	SWord	frameno;
};

class	FireAnimData:public	MinAnimData							
{
public:
	SWord	frameno;
};

class	BalloonAnimData:public	MinAnimData	
{
public:
	UByte	frameno;
	ULong	animclock;
	UWord	morphframe;
};

class	BarageAnimData:public	MinAnimData						
{
public:
	SWord	countdown;
};

class	TroopAnimData:public	MinAnimData						
{
public:
	UByte	animframe;											//RJS 22Dec99
	SLong	xpos, ypos, zpos;									//RJS 01Oct97
	UByte	homing:1,						
			oncourse:1,
			skydiving:1,
			goodchute:1,
			haschute:1,
			hasfriend:1,
			nofriends:1;
	UByte	animpose;											
	UByte	looptog;											
	UByte	loopable;											
	UByte	newanimpose;										
	UByte	swapnow;											
	UWord	animtime;											
	UWord	animCtrl_prev:5,
			animCtrl_new:5,
			animCtrl_current:6;
	UByte	stripno;
	UByte	fireframeno;
	UWord	BITSOFFFLAGS;

};

class	DirectAnimData					
{
public:
	SWord		hdg,pitch;										//RJS 12Jan98
};

class	WeapAnimData:public	DirectAnimData
{
public:
	UByte			launcherIndex:5,							//RJS 15Nov99
					currGun:3;									//RJS 15Nov99
	UByte			LauncherType;								
	UWord			LaunchTime;
	SWord			Stores,
					LoadedStores;
	UWord			target;										//RJS 24Nov97
	UWord			stationshape:10,
					SubDamage:5,
					IsArmed:1;									//RJS 11Jun97
	ULong			currLink;									//RJS 12Nov99
};

class	MoveGunAnimData:public	MinAnimData
{
public:
	WeapAnimData	weaponlaunchers[1];							
};

class	TwoGunAnimData:public	MinAnimData						
{																
public:															
	WeapAnimData	weaponlaunchers[2];							
};

class	AircraftAnimData:public	MinAnimData						
{
public:
	WeapAnimData	weaponlaunchers[5];							//RJS 15Nov99

	UByte			imagemapemblem;								//RJS 12Mar99
	UByte			imagemapacid1;								//RJS 11Mar99
	UByte			imagemapacid2;								//RJS 11Mar99
	UByte			imagemapacid3;								//RJS 11Mar99
	UByte			imagemapacid4;								//RJS 23Feb00

	UByte			nokills;									//RJS 09Jun97

	UByte			acaileronl,
					acaileronr,
					acelevator,								
					acrudder;

	UByte			acflaps,
					acbreak;									//RJS 17Feb98
	UByte			acslats,	//CB 03/11/99
					accanopy;	//CB 01/11/99

	UByte			acleglowerl,
					acleglowerr,
					acleglowerf,
					acleglowerb;

	UByte			aclegsuspl,
					aclegsuspr,
					aclegsuspf,
					aclegsuspb;

	UByte			acbombbays;									//RJS 25Jan99
	UByte			acwheell,									//RJS 01Jun00
					acwheelr,									//RJS 01Jun00
					acwheelb;									//RJS 01Jun00

 	UWord			acrpm;										//RJS 03Sep97
 	UWord			acrpm1;										//RJS 21Jun00

	UByte			exhaustframe;								//RJS 17Jun98
 	UByte			frameno;									//RJS 27Aug97
	SWord			randvel;									//RJS 14Feb97
	UByte			animtoggle;									//RJS 18Feb97
	UByte			animtimer;									//RJS 18Feb97
	UWord			timenotvis;									//RJS 30Jun99

	UByte			aclightclock1;								//RJS 15Feb99
	UByte			aclightclock2;								//RJS 15Feb99
	UByte			lighttoggle:1,								//RJS 12Mar99
					hassmoked:1,								//RJS 06Jun99
					muzzleflash:1,								//RJS 06Jun99
					rearshooting:1,								//RJS 03Dec99
					enginestart:1,								//RJS 22Feb00
					ejected:1,									//RJS 05Jul00
					cannonflash:1,								//RJS 25Aug00
					pad:1;										//RJS 25Aug00

	UByte			currweapindex:6,
					hasdust:1,
					justlanded:1;

	UByte			gunshooting:1,
					cannonshooting:1,
					pad2:6;

	UByte			LEFTWINGOUT,
					LEFTWINGIN,
					RIGHTWINGOUT,
					RIGHTWINGIN,
					ENGINELEFT,
					ENGINERIGHT,
					TAIL,
					FINLEFT,
					FINRIGHT,
					FRONT,
					LEFTWHEEL,
					RIGHTWHEEL,
					FUELTANK,
					CANOPY,
					OTHER;
};

class	InteractiveAnimData
{
public:
	SWord	anim_x;
	SWord	anim_y;
	SWord	anim_z;
};

class	PolyPitAnimData:public	AircraftAnimData				
{
public:
	UByte	acclockhour;
	UByte	acclockmin;
	UByte	acclocksec;
	UByte	acairspeed;
	UByte	acairspeed100;
	UByte	acarthoriz;
	UByte	acclimb;
	UByte	acaltitude;
	UByte	acalt10;
	UByte	acalt100;
	UByte	acaltradio;
	UByte	acaltradio10;
	UByte	acdirection;
	UByte	acslip;
	UByte	acturn;
	UByte	acelevatortrim;
	UByte	acfuelcontent;
	UByte	acfuelpressure;
	UByte	acoilcontent;
	UByte	acoilpressure;
	UByte	acoiltemp;
	UByte	acradiatortemp;
	UByte	acradiatortemp2;
	UByte	acboost;
	UByte	acboost2;
	UByte	acenginespeed;
	UByte	acengine2speed;
	UByte	acproppitch01;
	UByte	acproppitch02;
	UByte	acproppitch11;
	UByte	acproppitch12;
	UByte	acvoltmeter;
	SWord	accompass;
	UByte	acpitch;
	UByte	acflapindicator;
	UByte	acgearindicator;
	UWord	acgunammoleft;							
	UWord	acprevammoleft;							
	UWord	accannonammoleft;
	UWord	acprevammoleft2;
	SWord	acgyrocompass;										//RJS 20Mar00
	SWord	acgyrocompassflip;									//RJS 20Mar00
	UWord	actotalammoleft;											//RJS 5Oct00
	UByte	acunderflap;			// 5-stage h-gate (0 = default)
	UByte	acundercarriage;
	UByte	acundercarriage2;



	UByte	i_control;
	UByte	i_rudder;
	UByte	i_flaps;
	UByte	i_divebrakes;
	UByte	i_undercarriage;
	UByte	i_elevator;
	UByte	i_arm;
	UByte	i_emergencyunder;
	UByte	i_throttle;
	UByte	i_throttle2;
	UByte	i_proppitch;
	UByte	i_proppitch2;
	UByte	i_magnetos;
	UByte	i_magnetos2;
	UByte	i_primer;
	UByte	i_primer2;
	UByte	i_fuelcock;
	UByte	i_fuelcock2;
	UByte	i_enginestarter;
	UByte	i_enginestarter2;
	UByte	i_boostcutout;
	UByte	i_landing;
	UByte	i_guncam;
	UByte	i_hoodcatch;
	UByte	i_fueltankselect;
	UByte	i_radio;											//RJS 17Apr00

	UWord	canopyclock;										//RJS 23Feb00
	UWord	canopydelta;										//RJS 23Feb00

	UByte	lightfire;											//RDH 13Apr99
	UByte	lightstall;											//RDH 13Apr99
	UByte	lightguncamera;										//RDH 13Apr99
	UByte	lightgunsight;										//RDH 13Apr99

	UByte	fuelswitch:1,										//RDH 13Apr99
			gunotherswitch:1,									//RDH 13Apr99
			bombrocketswitch;									//RJS 24Nov99
//DeadCode RJS 18Apr00 			acundercarriage:1,									//RJS 24Nov99
//DeadCode RJS 18Apr00 			acundercarriage2:1,									//RJS 24Nov99
//DeadCode RJS 18Apr00 			acundercarriage3:1,									//RJS 24Nov99
//DeadCode RJS 18Apr00 			acundercarriage4:1;									//RJS 24Nov99

	UByte	acfuelwarning:1,									//RJS 24Nov99
			acfuelwarning2:1,
			acfuelwarning3:1,
			acfuelwarning4:1,									//RJS 03Dec99
			reargunnershooting:1;								//RJS 03Dec99
	  
	UByte	reargunner;											//RJS 03Dec99

	UByte	lastweapindex;										//RJS 17Jun99

	ULong	detailmask;											//RJS 23Jan98

	SWord	prevammo[5];										//RJS 10Jul00

	InteractiveAnimData	moveablelist[8];						//RJS 19Nov99
};

class	LauncherAnimData:public	MinAnimData
{
public:
	UByte	ammoleft;
	UByte	pad;
	UByte	LEFTWINGOUT,
			LEFTWINGIN,
			RIGHTWINGOUT,
			RIGHTWINGIN,
			OTHER;
};

class	WindsocAnimData:public	MinAnimData
{
public:
	UByte	frameno;
	UByte	fadedepth;
	UByte	pad;
	ULong	animclock;
	UWord	morphframe;
};

class	CloneAnimData:public	MinAnimData						//RJS 01Oct97
{																//RJS 01Oct97
public:															//RJS 01Oct97
	UWord	shapename:10,										//RJS 08Sep98
			weapindex:3,										//RJS 08Sep98
			weapindex2:3;										//RJS 08Sep98
	UByte	lnchtype;											//RJS 21Jul98
	UByte	delay;												//RJS 21Jul98
	ULong	originitm;											//RJS 21Jul98
};																//RJS 21Jul98

class	FlareAnimData:public	MinAnimData						//RJS 21Jan98
{																//RJS 21Jan98
public:															//RJS 21Jan98
	UByte	colstep;											//RJS 21Jan98
	UByte	depth;												//RJS 21Jan98
};																//RJS 21Jan98

class	ParachuteAnimData:public	MinAnimData
{
public:
	UByte	fireframeno;
	ULong	animclock;
	UWord	frameno;
	UByte	SHAGGED;
	UByte	OTHER;
};

class	ThugAnimData:public	MinAnimData
{
public:
	UWord	prevcount:15,
			disableprev:1;
	UWord	nextcount:15,
			disablenext:1;
	UWord	panimoff;
	UWord	nanimoff;
	SLong	pXPos;
	SLong	pYPos;
	SLong	pZPos;
	SLong	nXPos;
	SLong	nYPos;
	SLong	nZPos;
};

class	MissileAnimData:public	MinAnimData
{
public:
	UByte	frameno;
	UByte	hitstrength;										//DAW 01Dec98
	UByte	novirtualguns;										//RJS 29Mar99
	ULong	lastmissile;										//RJS 29Mar99
	UWord	target;
	UByte	wpIndex;											//RJS 12Nov99
	UByte	pad;												//RJS 12Nov99
};

class	DebrisAnimData:public	MinAnimData						
{
public:
	UByte	frameno;
};

class	SmokeTrailAnimData:public	MinAnimData
{
public:
	WeapAnimData	weaponlaunchers[1];
	ULong			thelist;
	UWord			nopoints;					
 	ULong			lifetime;									
	ULong			currTime;										
	UWord			SmkDescIndex:8,
					isDegraded:8;
};

class	BlokesAnimData:public	MinAnimData
{
public:
	UByte	beenlaunched:1,
			animtype:7;
	UWord	timer;
	UWord	nearestuid;
};

class	TrainAnimData:public	MinAnimData						
{
public:
	WeapAnimData	weaponlaunchers[1];
};


class	SimpleAircraftAnimData:public	MinAnimData						
{
public:
	WeapAnimData	weaponlaunchers[1];		//Smoke trail... i.e. 5th launcher

 	UWord			acrpm;

	UByte			bombbaysopen:1,								
					hassmoked:1,								
					bombsdropped:1,
					station1dead:1,
					station2dead:1,
					station3dead:1,
					station4dead:1,
					DUMMYBIT:1;

	UByte			LEFTWINGOUT,
					LEFTWINGIN,
					RIGHTWINGOUT,
					RIGHTWINGIN,
					ENGINELEFT,
					ENGINERIGHT,
					OTHER;
};

class	BirdLauncherAnimData:public	MinAnimData						
{
public:
	UByte	isPregnant;
	UWord	countdown;
	SWord	theShape;
};

class	FingerAnimData
{
public:
	SWord	velx;
	SWord	vely;
	SWord	velz;
	SLong	wx;
	SLong	wy;
	SLong	wz;
	SLong	wx2;
	SLong	wy2;
	SLong	wz2;
};

class	BlastAnimData:public MinAnimData
{
public:
	UByte			nofingers;
	FingerAnimData	fingerlist[8];
	SWord			timer;
	SLong			timedrawn;
	SWord			maxradius;
	UByte			frameno;
	UByte			pad;
};






#endif
