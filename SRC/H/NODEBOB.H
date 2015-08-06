//////////////////////////////////////////////////////////////////////
//
// Module:      nodebob.h
//
// Created:     17/11/99 by DAW
//
// Description: 
//
//////////////////////////////////////////////////////////////////////
#ifndef nodebob_DEFINED_17_11_1999
#define nodebob_DEFINED_17_11_1999
#include "bitcount.h"
#ifdef	DEFAULT_NODEBOB

//
// If the module is declared a second time, then this alternate construction 
// is made to allow instances to occur.
//
#pragma warnmsg("defining static version of nodebob")
	#define	BASESTRUCT(subname)							\
	namespace	{

	#define	BODYSTRUCT(subname)		}						\
	struct	II_##subname			{	typedef subname base;typedef II_##subname This;\
		operator subname&()	{return *(subname*)this;}		  \
		operator subname*()	{return (subname*)this;}		   \
		base&	Base()	{return *(base*)this;}

	#define	SUBSTRUCT(subname,parentname)				\
	struct	II_##subname			{typedef	II_##subname	This;	 \
		operator subname&()	{return *(subname*)this;}	  \
		operator subname*()	{return (subname*)this;}	   \
		II_##subname*	Next()	{return this+1;}			\
		II_##parentname	parentinst;							 \
		typedef	parentname::base base;						  \
		base&	Base()	{return *(base*)this;}

	#define	ENDSTRUCT(subname)		};					\
	union	I_##subname									 \
		{	II_##subname II;subname I;}

#define	ONLYFIELDI(Size,Type,name)							\
	struct	{												 \
			Size	value;									  \
		}	name

#else
//
// This definition defines substructures by simple inheritance
// That will not allow initialisation.
//
	

	#define	BASESTRUCT(subname)							\
	struct	subname					{  typedef subname base,This;

	#define	BODYSTRUCT(subname)

	#define	SUBSTRUCT(subname,parentname)				\
	struct	subname : parentname	{  typedef	subname	This;

	#define	ENDSTRUCT(subname)		};typedef subname	*subname##Ptr;
#define ONLYFIELDI(Size,Type,name)	ONLYFIELD(Size,Type,name)
#endif
//PUT CLEVER INSTANCING DERIVED TYPES HERE

struct	TargetSateliteField;
struct	TargetSectorField;
struct	TargetNoDetail;
struct	TargetGroup;
struct	TargetRadar;
struct	TargetFakeFactory;
struct	TargetFactory;
struct	TargetFighterField;
struct	TargetConvoy;

enum	SquadNum;

typedef	TargetSateliteField		*TargetSateliteFieldPtr	;
typedef	TargetSectorField		*TargetSectorFieldPtr	;
typedef	TargetNoDetail			*TargetNoDetailPtr		;
typedef	TargetGroup				*TargetGroupPtr			;
typedef	TargetRadar				*TargetRadarPtr			;
typedef	TargetFakeFactory		*TargetFakeFactoryPtr	;	
typedef	TargetFactory			*TargetFactoryPtr		;
typedef	TargetFighterField		*TargetFighterFieldPtr;
typedef	TargetConvoy			*TargetConvoyPtr;

struct	II_TargetFactory;
struct	II_TargetFighterField;
struct	II_TargetSateliteField;
struct	II_TargetSectorField;
struct	II_TargetNoDetail;
struct	II_TargetGroup;
struct	II_TargetRadar;
struct	II_TargetFakeFactory;
struct	II_TargetConvoy;

BASESTRUCT	(Target)
#define	virtual	/*fake virtual*/
enum	Defenses
		{AAA_NONE=0x00,AAA_LOW=0x20,AAA_MED=0x40,AAA_HIGH=0x60,AAA_DANGER=0x90,
 		 BALL_NONE=0x0,BALL_LOW=0x2,BALL_MED=0x4,BALL_HIGH=0x6,BALL_DANGER=0x9,
		 BAL_NONE=0x00,BAL_LOW=0x02,BAL_MED=0x04,BAL_HIGH=0x06,BAL_DANGER=0x09,
		MASK_AAA	=	0x000000f0,
		MASK_BALL	=	0x0000000f,
		MASK_DEFENSES=	0x000000ff,
		MASK_STRUCSIZE=	0x000fff00,
		MASK_OTHER	=	0xff000000,
		DEF_LONDON	=	0x01000000,
		DEF_LW_NE	=	0x10000000,	//if attack is only from 1 region then used AF in that region is key to route
		DEF_LW_C	=	0x20000000,	
		DEF_LW_SW	=	0x40000000,	//if A/F is from 2 of these 3 regions Rosieres will be used as key to route
		DEF_LW_SE	=	0x80000000,	//if A/F from this region is used, then used AF in this region is key to route
		};
//NOTE: I AM USING HIGHER BITS OF DEFENSES TO SPECIFY CASTING TYPE OF TARGET
enum	TargetStrucSize
{	
	TSS_TargetNoDetail			=0x00100,TSS_SetTargetNoDetail		=0x000100,	
	TSS_TargetGroup				=0x00200,TSS_SetTargetGroup			=0x000300,
	TSS_TargetRadar				=0x00400,TSS_SetTargetRadar			=0x000700,	
	TSS_TargetConvoy			=0x00800,TSS_SetTargetConvoy		=0x000B00,	
	TSS_TargetAirfield			=0x01000,TSS_SetTargetAirfield		=0x001300,	TSS_TargetFighterField=TSS_TargetAirfield,
	TSS_TargetSateliteField		=0x02000,TSS_SetTargetSateliteField	=0x003300,	
	TSS_TargetSectorField		=0x04000,TSS_SetTargetSectorField	=0x005300,
	TSS_TargetFakeFactory		=0x10000,TSS_SetTargetFakeFactory	=0x010300,
	TSS_TargetFactory			=0x20000,TSS_SetTargetFactory		=0x030300

};
	
	enum	TargType
		{	TT_AS_KNOWN,
//TEMPCODE RDH 05/01/00 			TT_SECTORAF,TT_SATELLITEAF,
			TT_DUMMY0, TT_DUMMY1,
			TT_FIGHTERAF,TT_NAVALAF,TT_BOMBERAF,TT_OTHERAF,
			TT_SPITASSEMBLY,TT_HURRASSEMBLY,TT_SPITPARTS,TT_HURRPARTS,TT_UNKNOWNAIRCRAFT,
			TT_WELLINGTON,TT_BEAUFIGHTER,TT_DEFIANT,TT_STIRLING,TT_BOMBERPARTS,
			TT_ARMAMENTS,TT_CARS,TT_BOMBERS,TT_INDUSTRY,TT_DOCKS,TT_NAVALBASE,
			TT_CHAINHOME,TT_CHAINLOW,TT_UNKNOWN,
			TT_CONVOY,
			TT_GERMANBOMBERAF,TT_GERMAN,
			TT_CITY,TT_TOWN,TT_VILLAGE,TT_LANDMARK,TT_SECONDARYAIRFIELD,TT_PRIMARYAIRFIELD,
			TT_LONDON,
			TT_MAX
		};

	enum	TargPriority
		{	TP_NODETAILS,TP_AS_KNOWN,
			TP_PRIMARYCOASTALAF,TP_SECONDARYCOASTALAF,
			TP_PRIMARYINLANDAF,TP_SECONDARYINLANDAF,
			TP_NON_GR11_PRIMARYAF,TP_NON_GR11_SECONDARYAF,
			TP_RADAR_HP,TP_RADAR_MP,TP_RADAR,
			TP_GR11_PORT_HP,TP_GR11_PORT_LP,TP_NAVALBASE,
			TP_GRxx_PORT_HP,TP_GRxx_PORT_LP,
			TP_LARGERESOURCE,TP_SMALLRESOURCE,
			TP_FIGHTERFACTORY,TP_COMPONENTFACTORY,
			TP_NAVALAF,TP_BOMBERAF,
			TP_FACTORY,TP_INDUSTRY,TP_OTHERAF,
			TP_BOMBERFACTORY,
			TP_CONVOY,
			TP_IRRELEVENT,TP_LANDMARK,TP_SECONDARYAIRFIELD,TP_PRIMARYAIRFIELD,TP_OTHERFACTORY,
			TP_MAX
		};

//TempCode MS 06Jun00 	enum	TargPriority
//TempCode MS 06Jun00 		{	TP_NODETAILS,TP_AS_KNOWN,
//TempCode MS 06Jun00 			TP_PRIMARYCOASTALAF,TP_SECONDARYCOASTALAF,
//TempCode MS 06Jun00 			TP_PRIMARYINLANDAF,TP_SECONDARYINLANDAF,
//TempCode MS 06Jun00 			TP_NON_GR11_PRIMARYAF,TP_NON_GR11_SECONDARYAF,
//TempCode MS 06Jun00 			TP_RADAR_HP,TP_RADAR_MP,TP_RADAR,
//TempCode MS 06Jun00 			TP_GRxx_PORT_LP,TP_GRxx_PORT_HP,
//TempCode MS 06Jun00 			TP_NAVALBASE,TP_SMALLRESOURCE,TP_LARGERESOURCE,
//TempCode MS 06Jun00 			TP_GR11_PORT_LP,TP_GR11_PORT_HP,
//TempCode MS 06Jun00 			TP_FIGHTERFACTORY,TP_COMPONENTFACTORY,
//TempCode MS 06Jun00 			TP_NAVALAF,TP_BOMBERAF,
//TempCode MS 06Jun00 			TP_FACTORY,TP_INDUSTRY,TP_OTHERAF,
//TempCode MS 06Jun00 			TP_BOMBERFACTORY,
//TempCode MS 06Jun00 			TP_CONVOY,
//TempCode MS 06Jun00 			TP_IRRELEVENT,TP_LANDMARK,TP_SECONDARYAIRFIELD,TP_PRIMARYAIRFIELD,TP_OTHERFACTORY,
//TempCode MS 06Jun00 			TP_MAX
//TempCode MS 06Jun00 		};
//DeadCode JON 4Sep00 	Target::TS_PERFECT=0,
//DeadCode JON 4Sep00 	Target::TS_LIGHTDAMAGE=30,
//DeadCode JON 4Sep00 	Target::TS_BADDAMAGE=70,
//DeadCode JON 4Sep00 	Target::TS_DESTROYED=100,
//DeadCode JON 4Sep00 	Target::TS_MAXIMUM=250,
//DeadCode JON 4Sep00 	Target::TS_NEARLYDESTROYED
//DeadCode JON 4Sep00	Target::TS_FLAG_UNKNOWN
		
	enum	TargStatus
		{	TS_NEARPERFECT=5,TS_LIGHTDAMAGE=20,TS_BADDAMAGE=60,TS_NEARLYDESTROYED=90,TS_DESTROYED=100,TS_MAXIMUM=250,
			TS_FLAG1=251,TS_FLAG2=252,TS_FLAG3=253,TS_FLAG4=254,
			TS_FLAG_UNKNOWN=255
		};

	enum	OutputStatus
		{	OS_NORMAL, OS_OUTFORDAY, OS_DISPERSED,
	  		OS_DEST1PERIODLEFT,   OS_DEST2PERIODSLEFT,  OS_DEST3PERIODSLEFT,
		  	OS_DEST4PERIODSLEFT,  OS_DEST5PERIODSLEFT,  OS_DEST6PERIODSLEFT,
  			OS_DEST7PERIODSLEFT,  OS_DEST8PERIODSLEFT,  OS_DEST9PERIODSLEFT,
		  	OS_DEST10PERIODSLEFT, OS_DEST11PERIODSLEFT, OS_DEST12PERIODSLEFT,
		  	OS_DEST13PERIODSLEFT, OS_DEST14PERIODSLEFT, OS_DEST15PERIODSLEFT}; 
enum	Location		{LOC_COAST,LOC_S_LON,LOC_N_LON,LOC_WEST,LOC_NORTH};

enum	Days
	{	//BOB days
		D_0July=-10,	//before battle proper
		D_1July=-9,

		D_10July=0,	 //wed	//first day of battle
			D_W1=5,		//mon
			D_W2=12,
			D_W3=19,
		D_31July=21,
		D_0Aug=21,
		D_1Aug=22,
			D_W4=26,
			D_W5=33,
				D_PH2=33,	//12th
			D_W6=40,
				D_PH3=45,	//24th
			D_W7=47,
		D_31Aug=52,
		D_0Sept=52,
		D_1Sept=53,
			D_W8=54,
				D_PH4=59,	//7th
			D_W9=61,
		D_14Sept=66,
		D_16Sept=68,
		D_17Sept=69,		//last day of battle
		D_=4,		//this is subtracted off damage date so damage date can't exceed 63
		D_FIRSTDAMAGEDDATE=D_
	};
enum	DamageLevel
	{
		DL_NONE=0,
		DL_LOW=64,
		DL_MED=128,
		DL_OUT=192,
		DL_LEVELMASK=0xc0,
		DL_LEVELSH=6,
		DL_DATEMASK=0x3f
	};


BODYSTRUCT	(Target)
	
	UniqueID	uid;
	TargType	truetargtype;
	TargPriority truepriority;
	UByte		truestatus;				//0=operational 100 = non-operational
	Defenses	truedefenses;//32 bit. Top part of truedefenses is strucsize and flags...

	TargType	falsetargtype;
	TargPriority falsepriority;											//JIM 3Jul00
	UByte		knownstatus;			//-1, ie 255(rdh) if LW don't even know desc	//JIM 3Jul00

	static	TargPriority	This::*	playerpriority;
	static	TargType		This::*	playertype;
	static	UByte			This::*	playerstatus;
	const TargPriority&	PlayerPriority() const	{return (this->*playerpriority);}
	const TargType&		PlayerType()	const 	{return (this->*playertype);}
	const UByte&			PlayerStatus() const	{return (this->*playerstatus);}
	TargPriority&	PlayerPriority() 	{return (this->*playerpriority);}
	TargType&		PlayerType()	 	{return (this->*playertype);}
	UByte&			PlayerStatus() 	{return (this->*playerstatus);}
	enum	{RECON_ADVISED_LEVEL=8};
	bool		ReconAdvised()	{return (!IsA(TSS_TargetConvoy)) && ((truestatus+RECON_ADVISED_LEVEL<knownstatus) || (knownstatus+RECON_ADVISED_LEVEL<truestatus));}

	//these should error check!!!
#ifdef assert
	#define castassert(n) assert (this==NULL||(n))
#else
	#define castassert(n)
#endif

#define	FreeCast(type)						\
	operator type*()						 \
	{										  \
		castassert(truedefenses&TSS_##type);   \
		return (type*)this;						\
	}											 \
	operator type&()							  \
	{											   \
		castassert(truedefenses&TSS_##type);		\
		return *(type*)this;						 \
	}

	FreeCast(TargetSateliteField)
	FreeCast(TargetSectorField)
	FreeCast(TargetNoDetail)
	FreeCast(TargetGroup)	
	FreeCast(TargetConvoy)	
	FreeCast(TargetRadar)		
	FreeCast(TargetFakeFactory)
	FreeCast(TargetFactory)
	FreeCast(TargetFighterField)
////Cant do this no bits! Use targetNoDetail...	FreeCast(Target)		

	operator	bool					(){return this!=NULL;}
	operator	int					(){return this!=NULL;}
	bool		operator ==		(const int){return this==NULL;}
	bool		operator !=		(const int){return this!=NULL;}
	bool	IsA(TargetStrucSize tss) {if (this) return (truedefenses&tss)!=0; else return false;}
	bool	operator==(TargetStrucSize tss) {return IsA(tss);}
	bool	operator>=(TargetStrucSize tss) {return IsA(tss);}
	bool	operator<(TargetStrucSize tss) {return !IsA(tss);}
	bool	operator&(TargetStrucSize tss) {return IsA(tss);}
	bool	London()	{return (truedefenses&DEF_LONDON)!=0;}
	
//Virtualised functions callable from top level
//The base function must handle the virtuality...




//Non-virtualised functions:




#undef virtual
ENDSTRUCT (Target);
struct	DamageRate;
SUBSTRUCT(TargetNoDetail,Target)
ENDSTRUCT (TargetNoDetail);

SUBSTRUCT(TargetGroup,TargetNoDetail)
enum{MAXDOGLEGS = 3, MAXSECONDARIES = 5	, MAXDATES= 8};
	UniqueID	doglegs[MAXDOGLEGS];
	UniqueID	secondaries[MAXSECONDARIES];		//for >5 see the secondary secondaries
	DamageRate*	damagerates;
	UByte		keydates[MAXDATES];
	FileNum		detailbattlefield;
	FileNum		inconsequentialbattlefield[1];	//Can index 3 if on airfield
	void	FixInitialStatusLW();
	void	FixInitialStatusRAF();
	void	SetDamage(UByte newlevel,bool reduceifnegative=false,UniqueID reportsuccess=UID_NULL);
	void	ApplyDamage(int totaldamage,UniqueID reportsuccess=UID_NULL);
ENDSTRUCT (TargetGroup);

SUBSTRUCT(TargetConvoy,TargetGroup)
	SLong		X,Z;
	SLong		wpnum;
	SLong		remainingstrength;
ENDSTRUCT(TargetConvoy);

SUBSTRUCT(TargetRadar,TargetGroup)
	bool		mobileunit,
				patroller;
ENDSTRUCT(TargetRadar);

SUBSTRUCT(TargetFakeFactory,TargetGroup)
	int			currperweek;
ENDSTRUCT(TargetFakeFactory);

SUBSTRUCT(TargetFactory,TargetFakeFactory)
	int	maxperweek,perweekwhenout,maxdispersedperweek;
ENDSTRUCT(TargetFactory);

SUBSTRUCT(TargetFighterField,TargetGroup)
	FileNum 	moreinconsequentialbattlefield[2];
	FileNum		taxibattlefield;
	char		maxsquads;
	UniqueID	satelitelist;
	Location	location;
	enum		SubDamageLevels	{SDL_REPAIR,SDL_FUEL,SDL_RUNWAY, SDL_STAFF};
	UByte		subdamagelevels[4];

	TargetSateliteField*	nextsatelite();
	UniqueID			getsectoruid();	//returns itself if is sector AF
	TargetSectorField*	getsectoraf();	//returns itself if is sector AF
	void	AircraftRepairs4Hour();
	void	ApplyDamage(int totaldamage,int	sdl_repair,int sdl_fuel,int sdl_runway,int sdl_staff,UniqueID reportsuccess=UID_NULL);
ENDSTRUCT(TargetFighterField);


SUBSTRUCT(TargetSateliteField,TargetFighterField)
	UniqueID	sectorAF;

ENDSTRUCT(TargetSateliteField);

SUBSTRUCT(TargetSectorField,TargetFighterField)
	UniqueID	primarycontrolcentre,	
				secondarycontrolcentre;
	int			sectorname,	groupname;
	char		minsquadsinsector,maxsquadsinsector;
ENDSTRUCT(TargetSectorField);

struct II_Squadron;
struct II_BritSquadron;
struct II_Gruppen;
struct	Squadron;
struct	BritSquadron;
struct	Gruppen;
enum	PlaneTypeSelect;
class	CString;
BASESTRUCT(Squadron)
	
enum	WaderNum
{				//on 10th

	WN_JG_3,	//y	
	WN_JG_26,	
	WN_JG_51,	
	WN_JG_52,	
	WN_JG_54,	
	WN_ZG_26,	//y	
	WN_ZG_76,	
	WN_KG_1,	
	WN_KG_2,	
	WN_KG_3,	
	WN_KG_4,	
	WN_KG_53,	
	WN_KG_76,
	
	WN_JG_2,	
	WN_JG_27,	
	WN_JG_53,	
	WN_SG_1,	//y	
	WN_SG_2,	
	WN_SG_77,	
	WN_ZG_2,	
	WN_KG_27,	
	WN_KG_51,	
	WN_KG_54,	
	WN_KG_55,	
	WN_LAST,
	GN_I=0,
	GN_II=1,
	GN_III=2,
	GN_1=0,
	GN_2=1,
	GN_3=2
};
enum	ACMarkings
{
	ACM_STANDARD


};

BODYSTRUCT(Squadron)
	enum	PeriodStatus	{LEAD_KILLED,LEAD_GOTKILL,OTHER_GOTKILL,GOT_LOSSES,GOT_ACTION,NO_ACTION,NO_FLYING,ON_LEAVE,BAD_WEATHER, GRP_13};

	ONLYFIELDI(UByte,SquadNum,	squadron);
	UWord	leadername;
	UWord	replaceleadername;

	UByte	leadermorale;
	UByte	leaderskill;
	UByte	averagemorale;

	UByte	averageskill;
	ONLYFIELDI(UWord,UniqueID,		homeairfield);
	UByte	pilotsavail;											  //JIM 07/01/00

	UByte	acavail;												  //JIM 07/01/00
	UByte	acquickrepairable;										  //JIM 07/01/00
	UByte	acslowrepairable;
	UByte	pilotlosses;
 	UByte		totestatus;	   //Profile::PackageStatus
	ONLYFIELDI(UByte,PeriodStatus,		periodstatus);	//Initially >=NO_FLYING
	UWord	markingscheme;


	int		ACTotal()	{return	acavail+acquickrepairable+acslowrepairable;}
	PlaneTypeSelect	AcType();
	UByte	Category();
	CString			FullName();
	CString			ShortName();
	CString			SubName();
	CString			CallName();
	void	ModifyMoraleNonCombat();
	void	ModifyMoraleAcCombat(PeriodStatus periodstatus,int times=1);

	bool			Busy();
#ifndef	DEFAULT_NODEBOB
	operator Squadron*()	{return (Squadron*)this;}
#endif
	operator BritSquadron*()	{return (BritSquadron*)this;}
	operator Gruppen*()			{return (Gruppen*)this;}
ENDSTRUCT(Squadron);

SUBSTRUCT(BritSquadron,Squadron)
	enum	{MAX_AC=20};
	enum	ACMarkings 	{};

	UByte	totetimer;
	ONLYFIELDI(UByte,PlaneTypeSelect,	actype);
	UWord		baseACcode;
 	int			deadACcodebits;

	ONLYFIELDI(UWord,UniqueID,			moveto);
	UWord		usedacbits;	//these aircraft are flying 'now'
	UWord		deadacbits;	//these a/c are dead and not replaced

	PlaneTypeSelect	AcType();
	CString			FullName();
	CString			ShortName();
	CString			SubName();
	void			UpdateReadiness(ULong periodsperframe=0xffffffff);
	bool			Busy() {return (usedacbits!=0);}

ENDSTRUCT(BritSquadron);

SUBSTRUCT(Gruppen,Squadron)
 	UByte		wadernum;
 	UByte		gruppennum;
 	SByte		periodsuntilready;	//negative is non-signalling

	enum	{MIN_STAFFELAC=10,MIN_STAFFELFIGHTERS=12,MIN_GRUPPEAC = 30,MIN_GRUPPEFIGHTERS=36,MAX_AC=44,MAX_RECON_AC=5,BUSY_IN_EUROPE=100};
	PlaneTypeSelect	AcType();
	CString			FullName();
	CString			ShortName();
	CString			SubName();
	bool			Busy()	{return (periodsuntilready!=0);}

ENDSTRUCT(Gruppen);


#ifndef	DEFAULT_NODEBOB
//PUT STANDARD STUFF HERE
//enum	WaderName	{WN_JG,WN_LG,WN_ZG,WN_KG,WN_SG};
enum	WaderName	{WN_JG,WN_SG,WN_ZG,WN_KG,WN_BETTERRULE};						  //RDH 20/12/99
enum	LuftFlotteNum	{LF_DET=0,LF_1=1,LF_2,LF_3,LF_4,LF_5};
enum	SquadNum
{
	SQ_ZERO=0,
	SQ_QMSPITA=SQ_ZERO,	//these entries are intended to make PT to PT conversion transparent.
	SQ_QMSPITB,
	SQ_QMHURRA,
	SQ_QMHURRB,
	SQ_QMDEF,
	SQ_QMBLEN,
	SQ_QM109,
	SQ_QM110,
	SQ_QM87,
	SQ_QM17,
	SQ_QM88,
	SQ_QM111,
	SQ_QM59,
	SQ_GM_ATruck,
	SQ_GM_ATank,
	SQ_GM_ATroop,
	SQ_GM_ATrain,
	SQ_GM_ATransportShip,	//18


	
	
	SQ_BR_START=PT_BADMAX,
	SQ_BR_32,
	SQ_BR_610,
	SQ_BR_501,
	SQ_BR_56,
	SQ_BR_151,
	SQ_BR_85,
	SQ_BR_64,
	SQ_BR_615,
	SQ_BR_111,
	SQ_BR_1Can,
	SQ_BR_54,
	SQ_BR_65,
	SQ_BR_74,
	SQ_BR_266,
	SQ_BR_43,
	SQ_BR_601,
	SQ_BR_145,
	SQ_BR_17,
	SQ_BR_85x,	 //??????
	SQ_BR_1,
	SQ_BR_257,
	SQ_BR_303,
	SQ_BR_87,
	SQ_BR_213,
	SQ_BR_238,
	SQ_BR_609,
	SQ_BR_152,
	SQ_BR_234,
	SQ_BR_92,
	SQ_BR_310,
	SQ_BR_19,
	SQ_BR_66,
	SQ_BR_242,
	SQ_BR_222,
	SQ_BR_611,
	SQ_BR_46,
	SQ_BR_229,
	SQ_BR_72,
	SQ_BR_249,
	SQ_BR_253,
	SQ_BR_605,
	SQ_BR_603,
	SQ_BR_41,
	SQ_BR_607,
	SQ_BR_602,
	SQ_BR_73,
	SQ_BR_504,
	SQ_BR_79,
	SQ_BR_302,
	SQ_BR_616,
	SQ_BR_3,
	SQ_BR_232,
	SQ_BR_245,	 //53
	SQ_BR_END,
	SQ_BR_DEFIENT,
	SQ_BR_BLENHEIM,

	SQ_LW_START, //72

	SQ_JG_3_1,	SQ_JG_3_2,	SQ_JG_3_3,
	SQ_JG_26_1,	SQ_JG_26_2,	SQ_JG_26_3,
	SQ_JG_51_1,	SQ_JG_51_2,	SQ_JG_51_3,
	SQ_JG_52_1,	SQ_JG_52_2,	SQ_JG_52_3,
	SQ_JG_54_1,	SQ_JG_54_2,	SQ_JG_54_3,
	SQ_ZG_26_1,	SQ_ZG_26_2,	SQ_ZG_26_3,
	SQ_ZG_76_1,	SQ_ZG_76_2,	SQ_ZG_76_3,
	SQ_KG_1_1,	SQ_KG_1_2,	SQ_KG_1_3,
	SQ_KG_2_1,	SQ_KG_2_2,	SQ_KG_2_3,
	SQ_KG_3_1,	SQ_KG_3_2,	SQ_KG_3_3,
	SQ_KG_4_1,	SQ_KG_4_2,	SQ_KG_4_3,
	SQ_KG_53_1,	SQ_KG_53_2,	SQ_KG_53_3,
	SQ_KG_76_1,	SQ_KG_76_2,	SQ_KG_76_3,
 //112
	SQ_JG_2_1,	SQ_JG_2_2,	SQ_JG_2_3,
	SQ_JG_27_1,	SQ_JG_27_2,	SQ_JG_27_3,
	SQ_JG_53_1,	SQ_JG_53_2,	SQ_JG_53_3,
	SQ_SG_1_1,	SQ_SG_1_2,	SQ_SG_1_3,
	SQ_SG_2_1,	SQ_SG_2_2,	SQ_SG_2_3,
	SQ_SG_77_1,	SQ_SG_77_2,	SQ_SG_77_3,
	SQ_ZG_2_1,	SQ_ZG_2_2,	SQ_ZG_2_3,
	SQ_KG_27_1,	SQ_KG_27_2,	SQ_KG_27_3,
	SQ_KG_51_1,	SQ_KG_51_2,	SQ_KG_51_3,
	SQ_KG_54_1,	SQ_KG_54_2,	SQ_KG_54_3,
	SQ_KG_55_1,	SQ_KG_55_2,	SQ_KG_55_3,	//24*3=72 Gruppen

	SQ_MAX		  //145 approx
};
struct	Geshwader
{
	UByte		wadername;
	UByte		wadernum;
	UByte		luftflotte;
	UByte		aircrafttype;
 	UByte		startdate;
	bool		reconn;
};

struct	ProductionAC
{
	SquadNum	recipient;
	ULong		acperweek;
	ULong		maxacperweek;
	ULong		minsperac;
	ULong		nextaceta;
	ULong		required;
	ULong		scrappedaircraft;
	ULong		spare1;
	
};
struct	HistoricInfo
{
	enum	WeatherType {NOFLY,OVERCAST, CLOUD60, CLOUD30, CLEAR};
	struct	Day
	{
		WeatherType	morning;
		WeatherType	midday;
		WeatherType	afternoon;

	};
	Day	day[70];
};
////////////////////////////////////////////////////////////////////////
class	BOStream;
class	BIStream;
enum	AccelSwitches;
enum	MapSFX;													//RJS 08May00
struct	IntelMsg
{
	enum	Priority	{LOWEST,VLOW,LOW,MED,HIGH,VHIGH,ALWAYS};
	enum	Voice		{PILOT,MAN,WOMAN,EXTERNAL,LUFT=4,LWMAN=LUFT+MAN,LWWOMAN=LUFT+WOMAN};
	enum	About		{FLIGHT,ENGAGEMENT,SPOTTING,TARGETSTATUS,MANAGEMENT,ANNOUNCEMENT};
	enum	{MAXBODYSCRIPT=32};
	struct	PVA
	{
		Priority	priority;	//3 bits
		Voice		voice;		//3 bits
		About		about;		//2 bits
		MapSFX		sfxTrigger;							//RJS 08May00
	}	pva;
	static const PVA	//LOW_ENG_PILOT,
						HIGH_FLIGHT_WOMAN,
						HIGH_SPOTTING_WOMAN,
						MED_MANAGEMENT_MAN,
						HIGH_SPOTTING_LW_WOMAN,
						HIGH_FLIGHT_LW_WOMAN,
						MED_MANAGEMENT_LW_MAN,
						MED_MANAGEMENT_LW,
						HIGH_FLIGHT_LW,
						HIGH_SPOTTING_LW,
						HIGH_TARGET_LW_WOMAN,
						HIGH_TARGET_LW,
						HIGH_TARGET_WOMAN,
						HIGH_ENGAGEMENT_WOMAN,
						HIGH_ENGAGEMENT_LW,
						HIGH_ENGAGEMENT_LW_WOMAN,

						MED_ANNOUNCEMENT_EXTERNAL;	  //KEEP AT END. END OF DAY ANNOUNCEMENTS!
	UWord		bodyscript[MAXBODYSCRIPT];
	UWord		title;
	UWord		time;	//65535 is yesterday. Only need 4am to 10pm = 18*3600=60000
	UniqueID	what;
};
inline IntelMsg::PVA PVA(IntelMsg::Priority p,IntelMsg::Voice 	v,IntelMsg::About a)
{IntelMsg::PVA rv;rv.about=a;rv.priority=p;rv.voice=v;rv.sfxTrigger=MapSFX(0);return rv;}//2 bits

inline IntelMsg::PVA PVA(IntelMsg::Priority p,IntelMsg::Voice 	v,IntelMsg::About a,MapSFX s)
	{IntelMsg::PVA rv;rv.about=a;rv.priority=p;rv.voice=v;rv.sfxTrigger=s;return rv;}		//2 bits

enum	ScriptTables;
struct	TargetIndexes;
class	CString;	
class	DeadStream;
struct	IntelBuffer
{
	enum	{BUFFERSIZE=256};
	IntelMsg	messages[BUFFERSIZE];
	int		latest;		//this slot is full with the latest message
	enum	{Bwrap,Bsaidupto,Bviewedupto,Blistedupto,Bmaxupto};
	int		B[Bmaxupto];
//			wrap,		//this slot is always empty - slot before oldest
//			saidupto,	//this slot has been vocalised
//			viewedupto;	//this slot has been displayed
	int	lastwhoandwhat;
	IntelMsg::Priority displaypriority,saypriority;
	bool	stoppedspeaking;
	IntelBuffer()	{latest=B[Bwrap]=B[Bsaidupto]=B[Bviewedupto]=B[Blistedupto]=0;displaypriority=saypriority=IntelMsg::LOWEST;stoppedspeaking=true;}
	bool AddMessage(	//Add a message to the intell
		const IntelMsg::PVA pva,AccelSwitches actiontype,
		ScriptTables script,UniqueID friendly=UID_NULL,UniqueID target=UID_NULL,const TargetIndexes&ti=*(TargetIndexes*)NULL);
	void	ChangeAccelOn(AccelSwitches actiontype,UniqueID friendly,UniqueID target, int		latestmsg);
	bool	SayNextMessage();
	bool	SayMessage(int messagenum);
	CString	MessageTitleToText(int messagenum);
	int		MessageTitle(int messagenum);
	CString	MessageBodyToText(int messagenum);
	void	ChangeMessagesUID(UniqueID old,int newid);
	void	OpenTakeOffOffered(int packf, int sqf, int latest);
	void	ClickPlay();
	int		IVoiceToRVoice(int);
	int		RVoiceToIVoice(int);



};
struct	ReviewBuffer:IntelBuffer
{
	ReviewBuffer()
	{
		repeatedscripts = 0;
	}
		

//DeadCode JIM 13Nov00 	static	 ScriptTables unrepeatablescripts[];
	struct 	UnrepeatableScripts
	{
		enum	Script	
		{
			SCRIPT_LUFPAC,SCRIPT_SEALIONONCOURSE,SCRIPT_SEALIONDOUBTS,SCRIPT_RDFHOLES,
			SCRIPT_BIGWINGUSED,SCRIPT_RAFRADIONET, SCRIPT_RAFRADIONETSUCCESS,SCRIPT_PILOTSHORTAGE,
			SCRIPT_LUFTWAFFEBOMBLONDON,SCRIPT_RAFBOMBBERLIN,SCRIPT_THOUSANDBOMBER,SCRIPT_BIGESCORT,
			SCRIPT_CRITICALSHIPPINGLOSS, SCRIPT_CRITICALTARGETS,SCRIPT_CRITICALSHIPPINGLOSS2

	};	};

	ULong	repeatedscripts;
	bool	IsScriptRepeated(UnrepeatableScripts::Script script);
	bool	SetScriptRepeated(UnrepeatableScripts::Script script);
};
class item;
class	NodeData
{
#ifdef	AFX_MIGVIEW_H__DB0342A1_1B07_11D1_A1F0_444553540000__INCLUDED_
	friend	void CMIGView::PlotAirfields(CDC* pDC);
#endif
	enum	{SUBTABLESIZE=128};
	typedef	Target*	TargetPtr;
	TargetPtr*	TargetPointers[SUBTABLESIZE];
	static	II_TargetSateliteField	satelites[];
	static	II_TargetSectorField	sectors[];
	static	II_TargetNoDetail		nodetails[];
	static	II_TargetGroup			groups[];
	static	II_TargetRadar			radars[];
	static	II_TargetGroup			notfacts[];
	static	II_TargetFakeFactory	fakefacts[];
	static	II_TargetFactory		factories[];
	static	II_TargetConvoy			convoys[];

	static	II_BritSquadron			britsquadinst[];
	static	II_Gruppen				germsquadinst[];
	static	Geshwader				germwaderinst[];
	void	AddToTargetTable(Target*,int targetstrucsize);

public:
	CON		NodeData();
	DES		~NodeData();
	Target&		GetTarget(UniqueID uid);	//will auto-cast to any Target subtype
	Target&		operator[](UniqueID uid)	{return GetTarget(uid);}
	Squadron&	operator[](SquadNum sq);
	void	BuildTargetTable();
	void	ClearTargetTable();
	void	LoadConvoys();
	FileNum TargetToBf(UniqueID targ,bool	inconsequentials=false);
	BritSquadron*		squadron;
	Gruppen*			gruppe;
	Geshwader*			geschwader;
	TargetConvoy*		convoylist;
	TargetSectorField*	sectorlist;
	TargetFactory*		factorylist;
	TargetFakeFactory*	fakelist;
	TargetRadar*		radarlist;

	IntelBuffer		intel;
	ReviewBuffer		review;
	static	ProductionAC	production[PT_BADMAX];
	static	HistoricInfo	historicinfo;	
	void	GenerateProductionRates();
	int		EstimateProduction(Target::TargType testtargtype);
	int		EstimateProduction(PlaneTypeSelect  testtype);
	int		CountProduction(Target::TargType testtargtype);

	void	IncreasePilotsIfRequired(Squadron* sq);
	void	DeliverProductionRates(int	secondspassed);
	void	UpdateReadiness(int	secondspassed);
	void	AutoReassignProduction(PlaneTypeSelect planetype,bool force13=false);
	SquadNum	WhereToReassignProduction(PlaneTypeSelect planetype,bool force13,bool&dosay,int&reqstr);
	void	UpgradeAircraftTypes();
	int		PerformMoveCycle();			//non-zero next period number when reach end of period
	void	PerformNextPeriod(int periodnum);
	void	FourHourPeriod(bool endofday=false);
	void	EndOfDay();
	void	DirectivesLogic();
	void	StartOfDay();
	bool	GoToEndDayReview();
	bool	GoToEndDayRouting();

	void	SetRAFReadiness();
	void	SetRAFReadiness(Profile::PackageStatus ps);
	bool	BadWeatherCheck();
	bool	GotBadWeatherPeriod(bool& alldayreturn=*(bool*)NULL,bool& informreturn=*(bool*)NULL);
	void	SetRAFPeriodStatus(Squadron::PeriodStatus ps);
	bool	AssignSecondaryRadars();
	void	UndefendedConvoyChecks();
	void	UndefendedCriticalTargetChecks();

	int	GenerateSecondaries(UniqueID* buffer,int minsize,int maxsize=0,int currsize=1);

	Gruppen*		FindNearestGruppen(UniqueID closepoint,WaderName wname,int minavailac,Profile::BetterRule br);
	BritSquadron*	FindNearestBritSquad(UniqueID closepoint,int minavailac,Profile::BetterRule br,SquadNum after);
	void	SetPlayerInfoLevel();
	void	LoadCleanNodeTree();
	void	Load(BIStream&bis);
	void	Save(BOStream&bos);
	FileNum	CheckTargetLoaded(UniqueID uid,bool	inconsequentials=false);
	int		CountSquadsAtAirfield(UniqueID u);
	void	AircraftRepairs4Hour();
	int SquadsAtField(UniqueID uidaf);
	 int	SquadsInSector(TargetFighterField* af);
	void	SkipToDate(int newdate);
	void	FillRAFStrengthInfo(bool countallincluding_gr13);
	void	FillLWStrengthInfo();
 	int RAFFindPercentAvail(int uidbandstart, int uidbandend, int trgpriority0, int trgpriority1);
 	int LWFindPercentAvail(int uidbandstart, int uidbandend, int trgpriority0, int trgpriority1);
	void	SwapSquadron();
	void	CheckDamage(DeadStream& ds);
	int		CheckDamage(DeadStream& ds,UniqueID sgt);
	int		GetCheckDamage(DeadStream& ds,UniqueID SGT);
	int		GetCheckDamage(DeadStream& ds,UniqueID SGT,int&a,int&b,int&c,int&d);
	bool Response(int pack, int firstsq);
	int		GroundVisible(Coords3D& trg,int* failedspotter);
	int		GroundVisible(item* trg,int* failedspotter);//	{return GroundVisible(trg->World,failedspotter); }
	enum {SPITS, HURR, RAFTOTAL,RAFMAXTYPES,LWTOTAL = 6,LWMAXTYPES = 7};
	struct	StrengthInfo
	{
		int catA;
		int catB;
		int catC;
		int acready;
		int actotal;
		int	pilots;
	};

	StrengthInfo	RAFstrengthinfo[RAFMAXTYPES];
	StrengthInfo	LWstrengthinfo[LWMAXTYPES];



//DEADCODE JIM 22/02/00 	FileNum TargetToBf(UniqueID targ,bool	inconsequentials=false);
};	
extern	NodeData	Node_Data;

#endif	define	DEFAULT_NODEBOB
#define	DEFAULT_NODEBOB 1
#undef	BASESTRUCT
#undef	BODYSTRUCT
#undef	SUBSTRUCT
#undef	ENDSTRUCT
#undef	ONLYFIELDI
#endif define nodebob_DEFINED_17_11_1999
