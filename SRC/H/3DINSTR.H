//------------------------------------------------------------------------------
//Filename       3dinstr.h
//System         
//Author         Paul.   
//Date           Wed 16 Aug 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	Dinstr_Included
#define	Dinstr_Included


//DeadCode RJS 21Apr99 enum	AnimSizes	{MINANIM=0,									//RJS 11Feb97
//DeadCode RJS 21Apr99 					AIRCRAFTANIM,
//DeadCode RJS 21Apr99 					WEAPANIM,									//PD 01Apr96
//DeadCode RJS 21Apr99 					DIRECTANIM,
//DeadCode RJS 21Apr99 					EXPLODEANIM,								//PD 15Apr96
//DeadCode RJS 21Apr99 					POLYPITANIM,								//PD 24Jun96
//DeadCode RJS 21Apr99 					SUNANIM,									//PD 24Jun96
//DeadCode RJS 21Apr99 					FLAMEANIM,									//RJS 10Jul96
//DeadCode RJS 21Apr99 					BALLOONANIM,								//RJS 05Aug96
//DeadCode RJS 21Apr99 					WINDSOCANIM,								//RJS 05Jun97
//DeadCode RJS 21Apr99 					MOVEGUNANIM,								//RJS 26Sep96
//DeadCode RJS 21Apr99 					BARAGEANIM,									//RJS 26Sep96
//DeadCode RJS 21Apr99 					FIREBALLANIM,								//RJS 07Oct96
//DeadCode RJS 21Apr99 					TANKANIM,									//RJS 17Oct96
//DeadCode RJS 21Apr99 					TRUCKANIM,									//RJS 17Oct96
//DeadCode RJS 21Apr99 					TRAINANIM,									//RJS 17Oct96
//DeadCode RJS 21Apr99 					TROOPANIM,									//RJS 18Oct96
//DeadCode RJS 21Apr99 					BRIDGEANIM,									//RJS 20Nov96
//DeadCode RJS 21Apr99 					LAUNCHERANIM,								//RJS 03Mar97
//DeadCode RJS 21Apr99 					CLONEANIM,									//RJS 01Oct97
//DeadCode RJS 21Apr99 					FLAREANIM,									//RJS 21Jan98
//DeadCode RJS 21Apr99 					THUGANIM,									//RJS 03Mar98
//DeadCode RJS 21Apr99 					MISSILEANIM,								//RJS 03Mar98
//DeadCode RJS 21Apr99 					DEBRISANIM,									//RJS 20Jan99
//DeadCode RJS 21Apr99 					SMOKETRAILANIM,								//RJS 21Jan99
//DeadCode RJS 21Apr99 					PARACHUTEANIM								//RJS 25Mar99
//DeadCode RJS 21Apr99 					};											//PD 24Jun96

//Offset in animdata...
//DeadCode RJS 30Nov99#define	ABITOFF		9											//RJS 21Apr99

enum	AnimSizes	{MINANIM=0,									//RJS 30Nov99
					AIRCRAFTANIM,
					SIMPLEAIRCRAFTANIM,	   						//RJS 17Nov99
					BLOKESANIM,									//RJS 01Jun99
					POLYPITANIM,   
					SUNANIM,	   
					WINDSOCANIM,   
					MOVEGUNANIM,   
					BARAGEANIM,	   
					TANKANIM,	   
					TRUCKANIM,	   
					TRAINANIM,	   
					TROOPANIM,	   
					BRIDGEANIM,	   
					LAUNCHERANIM,  
					CLONEANIM,	   
					FLAREANIM,	   
					THUGANIM,	   
					MISSILEANIM,   
					DEBRISANIM,	   
					SMOKETRAILANIM,
					PARACHUTEANIM,
					BIRDLAUNCHERANIM,							//RJS 13Dec99
					BLASTANIM,									//RJS 15Dec99
					BALLOONANIM,									//RJS 15Dec99
					WIREANIM,									//RJS 21Dec99
					AMBIENCEANIM,										//RJS 27Jun00
					TWOGUNANIM  										//RJS 27Jun00
					};								

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

enum	LnchrType	{LT_BULLET = 0, LT_BULLET_RAF = 0, LT_BULLET_LUF, LT_BULLET_REAR,
					 LT_CANNON = 0x10,
					 LT_BOMB = 0x20, LT_BOMB500 = 0x20, LT_BOMBPAIR500, LT_BOMB1000,LT_SMALLBOMB,LT_NAPALM,LT_BOMBB29,LT_BMB1B29,
					 LT_ROCKET = 0x30,LT_ROCKET4=0x30,LT_ROCKET6,LT_ROCKET8,
					 LT_WEAPON = 0x40,
					 LT_MOVEGUN = 0x70,
						LT_BRIT_CANNON = 0x70, LT_BRIT_BOFORS, LT_BRIT_3IN, LT_BRIT_3_7IN, LT_BRIT_4_5IN, LT_BRIT_PAC,
						LT_LUF_NOSE, LT_LUF_REARTOP, LT_LUF_REARBOT,
						LT_RAF_TURRET,
					 LT_SMKTRAILS = 0x80, LT_FUEL = 0x80, LT_VAPOUR, LT_CONTRAIL, LT_INTFUEL,
					 LT_DUST,LT_MUDDY,LT_JETDUST,LT_WINGVAP,LT_ENGINE, LT_FUNNEL,
					 LT_CONTACT = 0xd0, CT_WHLLEFT = 0xd0, CT_WHLRIGHT, CT_WHLFRONT,
					 CT_WHLBACK, CT_FRONT, CT_BACK, CT_LEFT, CT_RIGHT, CT_BELLY,
					 CT_EYE,CT_EYEGUN,CT_GRAVITY,CT_PILOT,CT_DUMMY,//RJS 06Dec99
					 LT_ANYWEAPON = 0xe0, LT_AWBULLET = 0xe0,LT_AWCANNON,//RJS 06Dec99
					 LT_MASK = 0xf0
					};											//RJS 01Oct98

enum	DialType	{DT_RPM = 0, DT_ALT = 1, DT_MPH = 2, DT_FUEL = 3};//RJS 16Sep96


//PD 17Apr96 - new a/c bits off code to cope with drawing dammaged
//				a/c sections

enum BitFlags {	BF_LBWing	=	0x00,
				BF_LTWing	=	0x02,
				BF_RBWing	=	0x04,
				BF_RTWing	=	0x06,
				BF_Tail		=	0x08,
				BF_Gear		=	0x0A,
				BF_Nose		=	0x0C,
				BF_TheRest	=	0x0E,							
				BF_Pilot	=	0x10,							
				BF_Engine	=	0x12,							
				BF_Fuel		=	0x14
			  };												//RJS 27Feb97

enum BitStates {BS_ALIVE=0,
				BS_DAMLV1=85,									//RJS 02Apr98
				BS_DAMLV2=170,									//RJS 02Apr98
				BS_DEAD = 255};

enum DamageTypes
{
	DMT_BULLET = 0,
	DMT_FIRE,
	DMT_SHOCKWAVE,												//RJS 06Dec98
	DMT_EXPLOSION												//RJS 06Dec98
};

enum	BitFlagsMan												//RJS 05Nov99
{																//RJS 05Nov99
	BF_LEFTARM = 0,												//RJS 05Nov99
	BF_RIGHTARM,												//RJS 05Nov99
	BF_LEFTLEG,													//RJS 05Nov99
	BF_RIGHTLEG,												//RJS 05Nov99
	BF_HEAD,													//RJS 05Nov99
	BF_ONFIRE,													//RJS 05Nov99
	BF_HELMET,													//RJS 05Nov99
	BF_PARACHUTE,												//RJS 22Dec99
	BF_GUN,														//RJS 22Dec99
	BF_TORSO													//RJS 22Dec99
};																//RJS 22Dec99



#endif
