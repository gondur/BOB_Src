//------------------------------------------------------------------------------
//Filename       misssub.h
//System         
//Author         Jim Taylor
//Date           Thu 22 Aug 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MISSSUB_Included
#define	MISSSUB_Included

#define	DEFAULT_MISSSUB 0

//DEADCODE MS 31/01/00 #include	"text.h"
#include	"ranges.h"
//#include	"node.h"

enum	{	
				MAXTNKWPINROUTE = 2

			};

//DeadCode MS 27Nov96 enum					{LOWCLOUD = 0,CLOUDAT10000FT,CLEARWEATHER,BADWEATHER, MAXWEATHERNUM = 4};
enum					{LOWCLOUD = 0,CLOUDAT10000FT,BADWEATHER,BADWEATHER10000FT, MAXWEATHERNUM = 4};

enum	SpecialEventBit {SpecialEventMIN = 0,HOMEBASEDESTROYED = 0,
						PLAYERKILLED, RESERVEEXHAUSTED,
//above this you are dead
						PLAYERWOUNDED,RESERVES_2LEFT,RESERVES_6LEFT,
						ACEKILLED,NEARTARGET,
						FATALITYINSQUAD,WOUNDEDINSQUAD,
						MORALEEXCELLENT,MORALEGOOD,MORALEPOOR,MORALEROCKBOTTOM,
//DeadCode RDH 13Mar97 						BESTDAY,SUGGESTEASIERAREA,SUGGESTDIFFICULTAREA,
						BESTDAY,
//
						LIEUTENANTPROMOTION,CAPTAINPROMOTION,

//Spring Offensive training
//DeadCode RDH 13Mar97 						CRASHLAND,BENTGEAR,GOODLANDING,LANDEDONSQUARE,
//DeadCode RDH 13Mar97 						STAYEDVCLOSETOCO,STAYEDCLOSETOCO,STAYEDINVICINITYOFCO,MILESFROMCO,
//DeadCode RDH 13Mar97 						SEENBYCO,NOTSEENBYCO,HITSNEARCO,
						CRASHLAND,BENTGEAR,GOODLANDING,
						QUITTOOSOON,QUITTOOSOONSO_1,
//DeadCode RDH 13Mar97 //SO debriefs
//DeadCode RDH 13Mar97 						LASTMISSIONSTRONG,LASTMISSIONWEAK,
//DeadCode RDH 13Mar97 						SO_WON,SO_LOST,
//DeadCode RDH 25Aug96 //tank debriefs
//DeadCode RDH 25Aug96 						HITTANKANIM,
//DeadCode RDH 13Mar97 
//DeadCode RDH 13Mar97 						EVACUATEFAILED,EVACUATESUCCESSFUL,
//DeadCode RDH 13Mar97 						SO_EVACUATEFAILED,SO_EVACUATESUCCESSFUL,//RDH 18Dec96
//DeadCode RDH 13Mar97 
//DeadCode RDH 13Mar97 //tank lost
//DeadCode RDH 13Mar97 						TANKCAMPAIGNLOST,TANK_BUILDPONTOONBRIDGE,TANKNEARBRIDGES,

						CAMPAIGNLOSTTAEJONOVERRUN,
						CAMPAIGNWONENTEREDPYONGYANG,
						CAMPAIGNLOST,
//awarded medals
						AWARDED_MEDALOFHONOUR,
//DeadCode RDH 13Mar97 //player decisions in combat
//DeadCode RDH 13Mar97 						PLAYER_ENGAGES_SHOULD,PLAYER_ENGAGES_SHOULDNOT,
//DeadCode RDH 13Mar97 						PLAYER_NOTENGAGE_SHOULD,PLAYER_NOTENGAGE_SHOULDNOT,
//landing
						PLAYERLANDEDINCOUNTRY,PLAYERCAPTURED,	//RDH 29Nov96
//target hit
						ATTACKEDAIRFRIENDLY,KILLEDAIRFRIENDLY,KILLEDGROUNDFRIENDLY,
						ENEMYDESTROYEDTARGET,FRIENDLYDESTROYEDTARGET,
//DeadCode RDH 25Aug96 					  HOMEBASEDAMAGED,SpecialEventMAX};
					  SpecialEventMAX};
//			In 3d Temp_Pilots morale

MAKEFIELD (SpecialEventBit,SpecialEventMIN,SpecialEventMAX);


enum	NewsEvent {NewsEventMIN = 0, NEWSWOUNEDRECOVERED, NEWSACEIN,
									 NEWSACEOUT,NEWSMISSION,NEWSMERITPROMOTION,
									 NEWSDEADMANPROMOTION,NEWSTHEPROMOTION,
									NEWSWOUNDEDMANPROMOTION,	//DAW 23Aug96
									//Spring Offensive: go operational
									 NEWSOPERATIONALGOOD,NEWSOPERATIONALBAD,
//last mission
						NEWSLASTMISSIONOFCAMPAIGN,
//updates
						NEWSCRCUPDATE,	
						NEWS_HAT_25_GOOD,
						NEWS_HAT_25_BAD,
						NEWS_HAT_50_GOOD,
						NEWS_HAT_50_BAD,
						NEWS_HAT_75_GOOD,
						NEWS_HAT_75_BAD,
						NEWS_SPRING_25_GOOD,
						NEWS_SPRING_25_BAD,
						NEWS_SPRING_50_GOOD,
						NEWS_SPRING_50_BAD,
						NEWS_SPRING_75_GOOD,
						NEWS_SPRING_75_BAD,



									//Spring Offensive: lastday
									NEWSSTRONGPOSITION,NEWSWEAKPOSITION,NEWSAVERAGEPOSITION,
									NEWSBESTDAY,				//DAW 23Aug96
										NewsEventMAX};


MAKEFIELD (NewsEvent,NewsEventMIN,NewsEventMAX);



enum	pilotstatus	{NOTFLYING = 0,FLYING, WOUNDED, MIA, IS_DEAD = MIA, KIA};
//moved to flyinit.h											//RDH 23Sep96
//DeadCode JIM 10Jun96 enum	SkillType
//DeadCode JIM 10Jun96 		{SKILL_NOVICE = 0,SKILL_STAGE = 1,SKILL_POOR,SKILL_REGULAR,SKILL_VETERAN,SKILL_ACE,SKILL_HERO};
//DeadCode RDH 23Sep96 enum	MeritType
//DeadCode RDH 23Sep96 		{MERIT_ROCKBOTTOM = 0,MERIT_INITIAL = 1000,MERIT_2LFTEXPERIENCED =5000,
//DeadCode RDH 23Sep96 		MERIT_LFT = 8000,
//DeadCode RDH 23Sep96 		MERIT_CAPTAIN = 12000,MERIT_MAJOR =18000,MERIT_MAJORHONOUR = 27000,
//DeadCode RDH 23Sep96 		MERIT_MAJORHONOURPLUS = 30000,MERIT_TOP = 65534,MERIT_IMPOSSIBLE = 65535,
//DeadCode RDH 23Sep96 		
//DeadCode RDH 23Sep96 //Spring Offensive merits to get operational		
//DeadCode RDH 23Sep96 		MERIT_OPERATIONAL = 3000
//DeadCode RDH 23Sep96 			
//DeadCode RDH 23Sep96 
//DeadCode RDH 23Sep96 		};
//DeadCode RDH 23Sep96 //aims is to get 30000 merit points by end of campaign			//RDH 23Sep96
//DeadCode RDH 23Sep96 //Circus	36 kills: 2 kills a mission, 20 missions -> 750 merit per kill
//DeadCode RDH 23Sep96 enum	DeltaMeritType
//DeadCode RDH 23Sep96 		{
//DeadCode RDH 23Sep96 		MERIT_TARGET_DESTROYED = 3000,
//DeadCode RDH 23Sep96 		MERIT_KILL = 750,
//DeadCode RDH 23Sep96 		MERIT_VIS_MSN_SUCCESS =4000,
//DeadCode RDH 23Sep96 		MERIT_OP_CRASHLAND = -300,
//DeadCode RDH 23Sep96 		MERIT_OP_BENTGEAR = -100,
//DeadCode RDH 23Sep96 		MERIT_OP_KANGAROO = 300,
//DeadCode RDH 23Sep96 		MERIT_OP_GOODLANDING = 100,
//DeadCode RDH 23Sep96 		MERIT_OP_LANDEDONSQUARE = 500,
//DeadCode RDH 23Sep96 		MERIT_OP_STAYEDVCLOSETOCO = 3000,
//DeadCode RDH 23Sep96 		MERIT_OP_STAYEDCLOSETOCO = 1500,
//DeadCode RDH 23Sep96 		MERIT_OP_STAYEDINVICINITYOFCO = 1000,
//DeadCode RDH 23Sep96 		MERIT_OP_MILESFROMCO = -1000,
//DeadCode RDH 23Sep96 		MERIT_OP_SEENBYCO = -1000,
//DeadCode RDH 23Sep96 		MERIT_OP_NOTSEENBYCO =1000,
//DeadCode RDH 23Sep96 		MERIT_OP_HITSNEARCO = 3000
//DeadCode RDH 23Sep96 
//DeadCode RDH 23Sep96 		};


//DeadCode RDH 09Sep96 enum	MoraleType
//DeadCode RDH 09Sep96 		{MORALE_ROCKBOTTOM = 0,MORALE_VERYPOOR = 40,MORALE_STAGE = 40,MORALE_HALFSTAGE = 20,
//DeadCode RDH 09Sep96 			MORALE_MINUSHALFSTAGE = -20,
//DeadCode RDH 09Sep96 		MORALE_POOR =80,MORALE_MEDIUM = 120,MORALE_GOOD =160,MORALE_VERYGOOD = 200,MORALE_EXCELLENT = 240,MORALE_TOPMORALE = 255 };
//DeadCode JIM 10Jun96 enum	CharacterType	- now in flyinit.h
//DeadCode JIM 10Jun96 		{CHAR_TACTICIAN = 0,CHAR_MRAVERAGE,CHAR_CAVALIER,CHAR_align=255};		
enum 	RankType {SECLIEUTENANT= 0,SECLIEUTENANT_EXPERT,LIEUTENANT,CAPTAIN,MAJOR, RANK_INC = 1};
enum					{MAXCONVOYS = 12,MAXTANKCONVOYS = 8,MAXTRUCKCONVOYS = 6,MAXROUTES = 4,MAXGUNS = 16};

enum	HatMissionFamily {HP_VOLUNTEER = 0,
			HP_NOCHOICE = 0, HP_BALLOON,HP_PATROL,HP_ESCORT,HP_ROVING};

enum	SquadPanelSelection {PERSONNEL = 0, CONFIGURE, PREFERENCES, PAINTSHOP,SAVEGAME};
enum	ConfigureSelection	{SAVECONFIGURE,RETURNFROMCONFIGURE,CANCELCONFIGURE,GOTOJOYSTICKCONFIG,
								CANCELSCRNCONFIG,ACCEPTSCREENCONFIG,TRYSELECTEDSCREENCONFIG

								};
enum	CtrlVar	{
								GOTOACCEL,GOTOMAP
				};
enum	FlightInfoSelection { FLYNOW= 0, JUSTRETURN};

enum	{
//		MAXCIRCUSMISSIONS 		= 21,
//		MAXHATMISSIONS 			= 21,
//DeadCode RDH 23Nov96 		MAXSPRINGMISSIONS 		= 24,
//		MAXSPRINGMISSIONS 		= 15,							//RDH 23Nov96
//		MAXTANKMISSIONS 		= 16,

//		CIRCUSPLAYERSLOT 		= 0,
//		HATPLAYERSLOT 			= 11,

//		CIRCUSTARGETKILL 		= 52,
//DeadCode AMM 21Feb100 		RADIOMESSAGELEN			= 128,
		RADIOMESSAGELEN			= 64, //AMM 21/02/00
		PASSWORDNAMELEN			= 11,
//DeadCode AMM 21Feb100 		SESSIONNAMELEN			= 128,
		SESSIONNAMELEN			= 32,
		MAXPLAYERS				=8,
//DEADCODE JIM 07/02/00 		PLAYERNAMELEN			= 21,
		PILOTS_PER_SQUADRON 	= 24,
		PILOTABLE_SQUADRONS		=	5,
		PILOTS_PER_CAMPAIGN 	= (int)PILOTS_PER_SQUADRON* (int)PILOTABLE_SQUADRONS,
		PILOTACTIVE 			= 0,
		PILOTDEAD 				= -1,
		PILOTS_IN_RESERVE 		= 80,
		ACESLIST 				= 0,
		CASUALTYLIST 			= 20,		//(int)ACESLIST + (int)PILOTS_IN_RESERVE,
		FLIGHTSPERSQUADRON	 	= 4,
		FLYINGFLIGHTSPERSQUADRON= 32,//(int)FLIGHTSPERSQUADRON - 1,//Jim 30 jun 98

		WRAPMIGSQUADRONS		=4,
		MAXMIGSQUADRONS			=12,		
//		MAXIMAGEMAPSPERAIRCRAFT = 8,
		};

struct	MissionType;
typedef	MissionType* DayMission [3];
typedef	MissionType* SingleMission;

typedef	MissionType* MissionFamily [6];
typedef MissionFamily MissionArea [5];

extern	SingleMission Spring51_Missions [];
extern	SingleMission PeaceTalk_Missions [];
extern	SingleMission Intro_Missions [];
extern	SingleMission Scramble_Missions [];						//RDH 02Aug96
extern	SingleMission H2H_Missions [];						//RDH 02Aug96
extern 	MissionArea Hat_Missions [2];

struct FormationPos
{
	SLong	range;
	ANGLESInst	bearing;
	SLong	delta_alt;
//DEADCODE JIM 10/12/99 	SWord	alt_icon;
};

	enum					{MAXFLIGHT_FORMS_NUM = 4};
	enum					{MAXAC_FORMATIONS_NUM = 4,MAXAC_EXTENDEDFORMATIONS_NUM=10};
struct FormationType
{
	int		numentries;
//	TextRef			name;
#pragma warning( disable : 4200)
	FormationPos	wingpos[];//MAXAC_FORMATIONS_NUM];
#pragma warning( default : 4200)
//DeadCode RDH 24Sep96 	FormationPos	wingpos [MAXAC_FORMATIONS_NUM];
	int	GetPerFl(int totalac)	
	{	int fl,fl2,fln=numentries;
		if (fln<0)	return -fln;
		if (fln<10) return fln;
		//The logic here is that these are a number of digits.
		//Above the highest digit is a zero digit which indicates the end of the list
		//Above that may be a 2 digit to indicate that pairs are handled by this movecode. This is currently not tested for. It is a debug
		//As we strip off each digit,
		//	If the next digit is a zero we must accept the current digit
		//	If the current digit is a divisor of the totalac then we want the current digit
		for (fl=fln%10,fl2=fln/10,fln=fl2%10,fl2=fl2/10; fln; fl=fln,fln=fl2%10,fl2=fl2/10)		//JIM 9Aug00
			breakif (totalac%fl==0);
		return	fl;
	}
};

struct	ExtFormationType
{
	FormationType formationtype;
//	FormationPos	extrawingpos[MAXAC_EXTENDEDFORMATIONS_NUM];	

};

struct	WaypointOffsetSub
{
	int	deltatime,	//up to 15 mins (in cs = 90000)
		deltahori,	//up to 4km		(in cm = 400000)
		deltavert;	//up to 10,000ft(in cm = 300000)
};
struct	WayPointOffset
{

	WaypointOffsetSub	members[16];	//LEADER GETS AN ENTRY;
};
//DEADCODE JIM 10/12/99 	enum					{MAXSQUAD_FORMS_NUM = 4};			//RDH 18Aug96
//DEADCODE JIM 10/12/99 struct SquadronType
//DEADCODE JIM 10/12/99 {
//DEADCODE JIM 10/12/99 	int numentries;
//DEADCODE JIM 10/12/99 //	TextRef			name;
//DEADCODE JIM 10/12/99 	FormationPos	wingpos [FLYINGFLIGHTSPERSQUADRON];
//DEADCODE JIM 10/12/99 
//DEADCODE JIM 10/12/99 };

typedef FormationType* SingleFormation;
extern SingleFormation Aircraft_Formations [];	//Index by FORMTYPE_WING
extern SingleFormation Squadron_Formations [];	//Index by FORMTYPE_SQUAD+FORMTYPE_WING
extern SingleFormation Escort_Formations [];	//Index by FORMTYPE_INTERCHILD+FORMTYPE_SQUAD	
extern	ExtFormationType	TakeOff_FormationWing, TakeOff_FormationSquad,	TakeOff_RefuelSpots;
//DEADCODE JIM 22/01/00 extern	ExtFormationType	Truck_VFormation,	Truck_LineFormation;
extern	WayPointOffset		WayPointOffsets_Escort,*WayPointOffsets_CourseSel[];
extern SingleFormation Ground_Formations [];	//Index by FORMTYPE_WING
//DEADCODE JIM 25/03/99 struct MapWpSet
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	UniqueID	uid;
//DEADCODE JIM 25/03/99 	SLong		worldx;
//DEADCODE JIM 25/03/99 	SLong		worldy;
//DEADCODE JIM 25/03/99 	SLong		worldz;
//DEADCODE JIM 25/03/99 	BFieldWaypointActions	action;
//DEADCODE JIM 25/03/99 	SLong		mapx;
//DEADCODE JIM 25/03/99 	SLong		mapy;
//DEADCODE JIM 25/03/99 	SWord		flags;
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 struct TnkMapWpSet {										//RDH 08Oct96
//DEADCODE JIM 25/03/99 					UniqueID	target_uid;
//DEADCODE JIM 25/03/99 					SLong		worldx;
//DEADCODE JIM 25/03/99 					SLong		worldy;
//DEADCODE JIM 25/03/99 					SLong		worldz;
//DEADCODE JIM 25/03/99 					SWord		action;
//DEADCODE JIM 25/03/99 					SLong		mapx;
//DEADCODE JIM 25/03/99 					SLong		mapy;
//DEADCODE JIM 25/03/99 					SWord		flags;
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 					};
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 struct PaperMaps
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	SLong		mapx;
//DEADCODE JIM 25/03/99 	SLong		mapy;
//DEADCODE JIM 25/03/99 	SLong		mapw;
//DEADCODE JIM 25/03/99 	SLong		maph;
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 
//#define MAXPLAYERS 12


struct 	PilotName	{ UWord nameref;char initial1,initial2; };

struct PilotHist
{
	typedef PilotName Name;
	Name	name;
	SWord	kills;
	pilotstatus	status;
	RankType	rank;
	SLong		lastdate;
};

//structure redefined 11/8/98 rdh
enum	HideSkills
{
	HSflyingskill=0,
	HScombatskill=8,
	HSflyingpotential=16,
	HScombatpotential=24,
	HStoskill=4,
	HSmask=255,
	HSskillmask=15,
	HSallskills=0x01010101
};
//DEADCODE JIM 08/12/99 struct PilotType
//DEADCODE JIM 08/12/99 {
//DEADCODE JIM 08/12/99 	typedef PilotName Name;
//DEADCODE JIM 08/12/99 	Name		name;
//DEADCODE JIM 08/12/99 	HideSkills	hideskills;
//DEADCODE JIM 08/12/99 #ifndef	__BCPLUSPLUS__
//DEADCODE JIM 08/12/99 	int	BigFlyingSkill()		{return (UByte)((hideskills>>HSflyingskill)&HSmask);}
//DEADCODE JIM 08/12/99 	int	BigCombatSkill()		{return (UByte)((hideskills>>HScombatskill)&HSmask);}
//DEADCODE JIM 08/12/99 	int	BigFlyingPotential()	{return (UByte)((hideskills>>HSflyingpotential)&HSmask);}
//DEADCODE JIM 08/12/99 	int	BigCombatPotential()	{return (UByte)((hideskills>>HScombatpotential)&HSmask);}
//DEADCODE JIM 08/12/99 	SkillType	FlyingSkill()		{return (SkillType)(UByte)((hideskills>>(HSflyingskill+HStoskill))&HSskillmask);}
//DEADCODE JIM 08/12/99 	SkillType	CombatSkill()		{return (SkillType)(UByte)((hideskills>>(HScombatskill+HStoskill))&HSskillmask);}
//DEADCODE JIM 08/12/99 	void	SetFlySkill(SkillType s)	{hideskills=HideSkills((hideskills&~(HSmask<<HSflyingskill))+(s<<(HSflyingskill+HStoskill)));}//DAW 26May99
//DEADCODE JIM 08/12/99 	void	SetCombSkill(SkillType s)	{hideskills=HideSkills((hideskills&~(HSmask<<HScombatskill))+(s<<(HScombatskill+HStoskill)));}//DAW 26May99
//DEADCODE JIM 08/12/99 	void	SetBigFlySkill(int s)	{hideskills=HideSkills((hideskills&~(HSmask<<HSflyingskill))+(s<<HSflyingskill));}//DAW 26May99
//DEADCODE JIM 08/12/99 	void	SetBigCombSkill(int s)	{hideskills=HideSkills((hideskills&~(HSmask<<HScombatskill))+(s<<HScombatskill));}//DAW 26May99
//DEADCODE JIM 08/12/99 //DeadCode DAW 09Jul99 	void	SetFlySkill(SkillType s)	{hideskills=HideSkills((hideskills&~(HSskillmask<<HSflyingskill))+(s<<(HSflyingskill+HStoskill)));}//DAW 26May99
//DEADCODE JIM 08/12/99 //DeadCode DAW 09Jul99 	void	SetCombSkill(SkillType s)	{hideskills=HideSkills((hideskills&~(HSskillmask<<HScombatskill))+(s<<(HScombatskill+HStoskill)));}//DAW 26May99
//DEADCODE JIM 08/12/99 //DeadCode DAW 09Jul99 	void	SetBigFlySkill(int s)	{hideskills=HideSkills((hideskills&~(HSskillmask<<HSflyingskill))+(s<<HSflyingskill));}//DAW 26May99
//DEADCODE JIM 08/12/99 //DeadCode DAW 09Jul99 	void	SetBigCombSkill(int s)	{hideskills=HideSkills((hideskills&~(HSskillmask<<HScombatskill))+(s<<HScombatskill));}//DAW 26May99
//DEADCODE JIM 08/12/99 #endif
//DEADCODE JIM 08/12/99 	pilotstatus	status;
//DEADCODE JIM 08/12/99 	MoraleType	morale;
//DEADCODE JIM 08/12/99 	RankType	rank;
//DEADCODE JIM 08/12/99 	SWord		missionscompleted;
//DEADCODE JIM 08/12/99 	NextFollAct	nextfollact;
//DEADCODE JIM 08/12/99 	SWord	dayssincerest; //actually periods.
//DEADCODE JIM 08/12/99 	SWord	kills;
//DEADCODE JIM 08/12/99 	SWord	airkillslastmsn;
//DEADCODE JIM 08/12/99 	SWord	daystorecover;
//DEADCODE JIM 08/12/99 	SWord	aircraftnum;
//DEADCODE JIM 08/12/99 	UByte	decal;
//DEADCODE JIM 08/12/99 //	UByte	airkillslastmiss;
//DEADCODE JIM 08/12/99 	UByte	grndhitslastmiss;
//DEADCODE JIM 08/12/99 };



//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 struct	WpSetType
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	UniqueID	mainobjective;
//DEADCODE JIM 25/03/99 	UniqueID	subobjective;
//DEADCODE JIM 25/03/99 	UniqueID	wp1;
//DEADCODE JIM 25/03/99 	UniqueID	wp2;
//DEADCODE JIM 25/03/99 	UniqueID	wp3;
//DEADCODE JIM 25/03/99 	UniqueID	zero;
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 struct	WpListType
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99  	SWord	noofentries;
//DEADCODE JIM 25/03/99 	WpSetType*	wpset[1];
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 struct	MissionType
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99 	FileNum	introsmack;
//DEADCODE JIM 25/03/99 	TextRef	newstext;
//DEADCODE JIM 25/03/99 	TextRef	missiontext;
//DEADCODE JIM 25/03/99 	SLong	missiondate;
//DEADCODE JIM 25/03/99 	SLong	timeofday;
//DEADCODE JIM 25/03/99 	WpListType* wplist;
//DEADCODE JIM 25/03/99 	FileNum	playerbf;
//DEADCODE JIM 25/03/99 	SWord	numofsquadronac;	
//DEADCODE JIM 25/03/99 	SWord	numofflightac;	
//DEADCODE JIM 25/03/99 	FormationTypeIndex	formationtypeindex;
//DEADCODE JIM 25/03/99 	SWord		weathernum;											//RDH 02Oct96
//DEADCODE JIM 25/03/99 	SWord	windspeed;
//DEADCODE JIM 25/03/99 	ANGLESInst	winddirection;			//direction from which the wind comes
//DEADCODE JIM 25/03/99 	FileNum	backdropart;
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 //------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 struct	BfTypeList
//DEADCODE JIM 25/03/99 {
//DEADCODE JIM 25/03/99  	SWord	noofentries;
//DEADCODE JIM 25/03/99 	SWord	bfields[2];
//DEADCODE JIM 25/03/99 };
//DEADCODE JIM 25/03/99 



//DEADCODE JIM 24/05/00  	enum		{MAX_PACKAGE_NUM = 5,MAX_COMPONENT_NUM = 4};
//DEADCODE JIM 24/05/00 
//DEADCODE JIM 24/05/00 	enum	FamilyType{PFT_NULL = 4,
//DEADCODE JIM 24/05/00 					PFT_HEAVYSTRIKE = 0,
//DEADCODE JIM 24/05/00 					PFT_STRIKE = 1,		
//DEADCODE JIM 24/05/00 					PFT_PATROL = 2,		
//DEADCODE JIM 24/05/00 					PFT_CAS = 3,
//DEADCODE JIM 24/05/00 					PFT_ALIGN = 0xffff
//DEADCODE JIM 24/05/00 					};
//DEADCODE JIM 24/05/00 inline	SWord&	operator *(FamilyType& f){return(SWord&) f;}
//DEADCODE JIM 24/05/00 					
//DEADCODE JIM 24/05/00 
//DEADCODE JIM 24/05/00 	enum	Type{
//DEADCODE JIM 24/05/00 			HS_BASE = 0,	
//DEADCODE JIM 24/05/00 			HS_ALPHADIRECT = HS_BASE,	
//DEADCODE JIM 24/05/00 			HS_ALPHAINDIRECT,	
//DEADCODE JIM 24/05/00 			HS_BETADIRECT,		
//DEADCODE JIM 24/05/00 			HS_BETAINDIRECT,	
//DEADCODE JIM 24/05/00 			HS_UNESCORTED,		
//DEADCODE JIM 24/05/00 			HS_UNESCORTEDNIGHT,
//DEADCODE JIM 24/05/00 			S_BASE,	
//DEADCODE JIM 24/05/00 			S_BOMB = S_BASE,	
//DEADCODE JIM 24/05/00 			S_ROCKET,	
//DEADCODE JIM 24/05/00 			S_CRACKBURN,
//DEADCODE JIM 24/05/00 			S_NAPALM,	
//DEADCODE JIM 24/05/00 			S_STRAFF,
//DEADCODE JIM 24/05/00 			PTRL_BASE,		
//DEADCODE JIM 24/05/00 			PTRL_BARCAP = PTRL_BASE,		
//DEADCODE JIM 24/05/00 			PTRL_TACTICALINTERDICT,
//DEADCODE JIM 24/05/00 			PTRL_AGGCAP,
//DEADCODE JIM 24/05/00 			CAS_BASE,	
//DEADCODE JIM 24/05/00 			CAS_BOMB = CAS_BASE,	
//DEADCODE JIM 24/05/00 			CAS_ROCKET,	
//DEADCODE JIM 24/05/00 			CAS_CRACKBURN,
//DEADCODE JIM 24/05/00 			CAS_NAPALM,	
//DEADCODE JIM 24/05/00 			CAS_STRAFF,
//DEADCODE JIM 24/05/00 			T_NULL,
//DEADCODE JIM 24/05/00 			T_ALIGN = 0xffff
//DEADCODE JIM 24/05/00 				};
//DEADCODE JIM 24/05/00 
//DEADCODE JIM 24/05/00 inline	SWord&	operator *(Type& f){return(SWord&) f;}
//DEADCODE JIM 24/05/00 
//DEADCODE JIM 24/05/00 
//DEADCODE JIM 24/05/00 enum	Stores	{
//DEADCODE JIM 24/05/00 				GUNSONLY = 0,	B29_STD = 0,
//DEADCODE JIM 24/05/00 				LR_BOMB = 1,	B29_TARZON = 1,
//DEADCODE JIM 24/05/00 				LR_HDBOMB,
//DEADCODE JIM 24/05/00 				LR_ROCKET,
//DEADCODE JIM 24/05/00 				LR_NAPALM,
//DEADCODE JIM 24/05/00 				CAS_NB,
//DEADCODE JIM 24/05/00 				CAS_RB,
//DEADCODE JIM 24/05/00 				CAS_NR,
//DEADCODE JIM 24/05/00 				STORES_ALIGN = 0xffff
//DEADCODE JIM 24/05/00 			};
//DEADCODE JIM 24/05/00 
//DEADCODE JIM 24/05/00 inline	SWord&	operator *(Stores& f){return(SWord&) f;}

//DEADCODE DAW 25/11/99 enum	Squadron{
//DEADCODE DAW 25/11/99 		F86Squad = 0,
//DEADCODE DAW 25/11/99 		F84Squad,
//DEADCODE DAW 25/11/99 		F80Squad,
//DEADCODE DAW 25/11/99 		F51Squad,
//DEADCODE DAW 25/11/99 		B29Squad,
//DEADCODE DAW 25/11/99 
//DEADCODE DAW 25/11/99 
//DEADCODE DAW 25/11/99 
//DEADCODE DAW 25/11/99 
//DEADCODE DAW 25/11/99 		};

//DEADCODE DAW 25/11/99 inline	SWord&	operator *(Squadron& f){return(SWord&) f;}

//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 enum  	{
//DEADCODE JIM 25/03/99 			PASSIVE,ACTIVE,SIBLING,CONTROL
//DEADCODE JIM 25/03/99 		};	
//DEADCODE JIM 25/03/99 
//DEADCODE JIM 25/03/99 enum	ListControl{LISTINACTIVE,LISTACTIVE};
//DEADCODE JIM 25/03/99 enum	{LISTCONTROLMAX = 16, STORESPERACMAX = 8,CONFIGSTORESAC = 6};

//MARK, this is the list of events in the order of use			//MS 04Mar99

//DEADCODE JIM 28/01/00 enum	RedEvents
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	MIGEV_SANCPAT,
//DEADCODE JIM 28/01/00 	MIGEV_SAFEPAT,
//DEADCODE JIM 28/01/00 	MIGEV_INTERSOUTH1,
//DEADCODE JIM 28/01/00 	MIGEV_STRAIGHTRUN,	//straight run down with no diversions - easy to stop
//DEADCODE JIM 28/01/00 	MIGEV_INTERCEPT1,	
//DEADCODE JIM 28/01/00 	MIGEV_BOMBERS1,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_INTERSOUTH2,
//DEADCODE JIM 28/01/00 	MIGEV_INTERCEPT2,
//DEADCODE JIM 28/01/00 	MIGEV_WAITWEAK,
//DEADCODE JIM 28/01/00 	MIGEV_CUTWEAK,	
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_CONTRAILFOCUS,
//DEADCODE JIM 28/01/00 	MIGEV_BOMBERS2,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_INTERSOUTH3,
//DEADCODE JIM 28/01/00 	MIGEV_INTERCEPT3,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_THREELEVELS,
//DEADCODE JIM 28/01/00 	MIGEV_BOMBERS3,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_MOVINGROUND,
//DEADCODE JIM 28/01/00 	MIGEV_STATICROUND,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_ENDRUNDECOY,
//DEADCODE JIM 28/01/00 	MIGEV_LOWSWEEP,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_UPPERCUT,
//DEADCODE JIM 28/01/00 	MIGEV_INTERCEPT4,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_STAIRCASE,
//DEADCODE JIM 28/01/00 	MIGEV_SUPERIOR1,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_SLEDGEHAMMER,
//DEADCODE JIM 28/01/00 	MIGEV_SUPERIOR2,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_WESTTRAIN,
//DEADCODE JIM 28/01/00 	MIGEV_BIGTRAIN1,
//DEADCODE JIM 28/01/00 //-------------------------------------------------------------------
//DEADCODE JIM 28/01/00 	MIGEV_BIGTRAIN2,
//DEADCODE JIM 28/01/00 	MIGEV_BIGTRAIN3,
//DEADCODE JIM 28/01/00 	MIGEV_BIGTRAIN4,
//DEADCODE JIM 28/01/00 	MIGEV_BIGTRAIN5,
//DEADCODE JIM 28/01/00 	MIGEV_BIGTRAIN6,
//DEADCODE JIM 28/01/00 	MIGEV_EASTCOAST,
//DEADCODE JIM 28/01/00 	MIGEV_CENTTRAIN,
//DEADCODE JIM 28/01/00 	MIGEV_WPOORTRAIN,
//DEADCODE JIM 28/01/00 	MIGEV_CAREFUL,
//DEADCODE JIM 28/01/00 	MIGEV_CONFRONT,		//migs attack sabres to clear them
//DEADCODE JIM 28/01/00 	MIGEV_CAREFUL2,
//DEADCODE JIM 28/01/00 //DeadCode RDH 05Mar99 	MIGEV_TRAIL,
//DEADCODE JIM 28/01/00 //DeadCode RDH 05Mar99 	MIGEV_STRING,
//DEADCODE JIM 28/01/00 //DeadCode RDH 05Mar99 	MIGEV_JAWS,
//DEADCODE JIM 28/01/00 //DeadCode RDH 05Mar99 	MIGEV_ZVENO,
//DEADCODE JIM 28/01/00 //DeadCode MS 04Mar99 	MIGEV_DECOYACTIVE,
//DEADCODE JIM 28/01/00 //DeadCode MS 04Mar99 	MIGEV_DECOYPASSIVE,
//DEADCODE JIM 28/01/00 //DeadCode RDH 05Mar99 	MIGEV_BAIT,
//DEADCODE JIM 28/01/00 //DeadCode RDH 05Mar99 	MIGEV_SLIGHTHAND,
//DEADCODE JIM 28/01/00 	MIGEV_MAX
//DEADCODE JIM 28/01/00 };
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 struct	MigEvent
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	FileNum					eventbf,alteventbf;			//2 versions: 50-50 chance
//DEADCODE JIM 28/01/00 	tAggressionLevel		minlevel;
//DEADCODE JIM 28/01/00 	int						takeofftime;
//DEADCODE JIM 28/01/00 	SWord					minformsize,maxformsize;	//both 0 = no limit
//DEADCODE JIM 28/01/00 	enum					{	TARGET=1,		//goes for a target
//DEADCODE JIM 28/01/00 								DIRECT=2,		//goes direct - no decoy element
//DEADCODE JIM 28/01/00 								BARCAP=4,		//goes for barcaps
//DEADCODE JIM 28/01/00 								LOCAL=8,		//stays in Yalu region
//DEADCODE JIM 28/01/00 								STARTSOUTH=16,	//starts south of MA
//DEADCODE JIM 28/01/00 								BIGTRAIN=32,	//Is a bigtrain. If selected first then all missions that day will be that train.
//DEADCODE JIM 28/01/00 								DECOY=64,		//Has a decoy aspect
//DEADCODE JIM 28/01/00 								TRAIN_TARGET=33,//Its a big train with a target!
//DEADCODE JIM 28/01/00 								SOUTH_TARGET=17,//starts south with a target
//DEADCODE JIM 28/01/00 								DIRECT_TARGET=3,//direct run to a target
//DEADCODE JIM 28/01/00 								LOCAL_TARGET=9,	//local with a target
//DEADCODE JIM 28/01/00 								DECOY_TARGET=65,//local with a target
//DEADCODE JIM 28/01/00 								DECLOC_TARGET=73,
//DEADCODE JIM 28/01/00 							};	//this enum could be more compact...
//DEADCODE JIM 28/01/00 	int						eventdoes;		
//DEADCODE JIM 28/01/00 	tFirstEncounterTactics	firsttactics;
//DEADCODE JIM 28/01/00 	tThreatLevel			mainthreat, secthreat;
//DEADCODE JIM 28/01/00 };
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 struct AcComponent
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 {
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	DutyType	duty;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	Squadron	squadron;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	SWord		numofflights;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	Stores		stores;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 };
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 struct WeaponSets
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 {
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	ranges		range;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	TextSnip0	text;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 };
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 struct	Package
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 {
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	FamilyType	familytype;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	Type		type;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	UniqueID	target_uid;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	SLong		target_eta;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	WayPoint*	maintroute;
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	AcComponent component[MAX_COMPONENT_NUM];
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 	char		name[30];
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 
//DEADCODE JIM 28/01/00 //DeadCode JIM 19Feb99 };
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //DeadCode RDH 11Mar97 struct	AirFieldInfo
//DEADCODE JIM 28/01/00 //DeadCode RDH 11Mar97 {
//DEADCODE JIM 28/01/00 //DeadCode RDH 11Mar97 	Nationality		nationality;
//DEADCODE JIM 28/01/00 //DeadCode RDH 11Mar97 	UniqueIDDummy		airfield;	
//DEADCODE JIM 28/01/00 //DeadCode RDH 11Mar97 	SupplyNode*			northnodes[2];		//used to decide when airfield changes hands
//DEADCODE JIM 28/01/00 //DeadCode RDH 11Mar97 	SupplyNode*			southnodes[2];		//
//DEADCODE JIM 28/01/00 //DeadCode RDH 11Mar97 
//DEADCODE JIM 28/01/00 //DeadCode RDH 11Mar97 };
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //extern Package	Predefined_Package[];
//DEADCODE JIM 28/01/00 //extern WeaponSets Predefined_WeapSet [CONFIGSTORESAC][STORESPERACMAX];
//DEADCODE JIM 28/01/00 //extern ListControl listcontrol [LISTCONTROLMAX];
//DEADCODE JIM 28/01/00 //extern AirFieldInfo	airfieldinfo[];
//DEADCODE JIM 28/01/00 //DEADCODE JIM 25/03/99 extern void SendMsg(UniqueID uid,SWord topfilter,SWord sender,SWord priority,TextRef msg);//RDH 10Mar97
//DEADCODE JIM 28/01/00 struct	SupplyNode;
//DEADCODE JIM 28/01/00 struct	SupplyRoute;
//DEADCODE JIM 28/01/00 struct	SupplyLine;
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 enum	{MAXMISSIONS = 20, MAXDIRECTIVES = 8,  MAXACPERSQUAD = 16, MAX_DIRGROUPS = 5,
//DEADCODE JIM 28/01/00 				WAVE2_FLAK=3, WAVE2_ESCORT=4};
//DEADCODE JIM 28/01/00 struct	DirGroup
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	char		squadron;
//DEADCODE JIM 28/01/00 	char		numflights;
//DEADCODE JIM 28/01/00 };
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 struct	Mission
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	int			score;
//DEADCODE JIM 28/01/00 	FileNum		profile;
//DEADCODE JIM 28/01/00 	char		note;
//DEADCODE JIM 28/01/00 	UniqueID	target;
//DEADCODE JIM 28/01/00 	UniqueID	suppliee;
//DEADCODE JIM 28/01/00 	DirGroup	group[MAX_DIRGROUPS];		//MAX_GROUPS];
//DEADCODE JIM 28/01/00 //	char		acresource[7];
//DEADCODE JIM 28/01/00 //	char		squadron[3];
//DEADCODE JIM 28/01/00 	bool		escort;
//DEADCODE JIM 28/01/00 	bool		missionset;
//DEADCODE JIM 28/01/00 	SupplyNode*	node;
//DEADCODE JIM 28/01/00 };
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 struct	SG_Directive
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	char		type;
//DEADCODE JIM 28/01/00 	char		strikeac;
//DEADCODE JIM 28/01/00 	char		fighterac;
//DEADCODE JIM 28/01/00 };
//DEADCODE JIM 28/01/00 struct	Directive:SG_Directive
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	int			targets;
//DEADCODE JIM 28/01/00 	int			missionsset;
//DEADCODE JIM 28/01/00 	Mission 	missions[MAXMISSIONS];
//DEADCODE JIM 28/01/00 };
//DEADCODE JIM 28/01/00 struct	DirControlData
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	bool		autogen;
//DEADCODE JIM 28/01/00 	bool		autodisplay;
//DEADCODE JIM 28/01/00 	bool		B29avail;
//DEADCODE JIM 28/01/00 	bool		alphastrikesallowed;
//DEADCODE JIM 28/01/00 	char		dayssinceB29;
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 };
//DEADCODE JIM 28/01/00 struct	SG_DirControl:DirControlData
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	SG_Directive	directives[MAXDIRECTIVES];
//DEADCODE JIM 28/01/00 	void	ResetForNewCampaign();
//DEADCODE JIM 28/01/00 };
//DEADCODE JIM 28/01/00 struct	DirControl:DirControlData
//DEADCODE JIM 28/01/00 {
//DEADCODE JIM 28/01/00 	Directive	directives[MAXDIRECTIVES];
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 	CON	DirControl();
//DEADCODE JIM 28/01/00 		void	AllocateAc();
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00    enum	{ALPHASTRIKE, MEDIUMBOMBERSTRIKE, FBSTRIKE, UNDECIDEDSTRIKE};
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 UniqueID targetsalloc[10];		//Profile::MAX_PACKS];
//DEADCODE JIM 28/01/00 int TotalStrikeAc;
//DEADCODE JIM 28/01/00 int TotalFighterAC; 
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 int TotalStrikeAcInUse;
//DEADCODE JIM 28/01/00 int TotalFighterACInUse; 
//DEADCODE JIM 28/01/00 int	MissionsAlreadyDefined;
//DEADCODE JIM 28/01/00 int	TargetsAlreadyDefined;
//DEADCODE JIM 28/01/00 enum {FBTYPES = 3, ACTYPES = 7};
//DEADCODE JIM 28/01/00 enum	{ACT_NOTSET = 0,ACT_PROP, ACT_JET};
//DEADCODE JIM 28/01/00 char	acresource[ACTYPES];
//DEADCODE JIM 28/01/00 char	acalreadyinuse[ACTYPES];
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 int firsttype;
//DEADCODE JIM 28/01/00 DirGroup	tmpgroup[MAX_DIRGROUPS];				//MAX_GROUPS];
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //char	tempacused[ACTYPES];
//DEADCODE JIM 28/01/00 int maxscore[7];			//number of directives - resting
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //DEADCODE JIM 28/01/00 char	jetfirst[PT_BRIT_NONFLY]; 
//DEADCODE JIM 28/01/00 //DEADCODE JIM 28/01/00 char	propfirst[PT_BRIT_NONFLY];
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //	void	FindScoresAndProfile(int pack, UniqueID uid, SupplyNode* node, int& score, int& maxscore, FileNum& profile, int& type);
//DEADCODE JIM 28/01/00 //	FileNum	FindProfile();
//DEADCODE JIM 28/01/00 //	void	AllocateAcToOneTarget(int pack, UniqueID uid, bool countall);
//DEADCODE JIM 28/01/00 //	void	MakeMiniCampaignMission();								  //RDH 21/03/99
//DEADCODE JIM 28/01/00 //	bool	ModifyRedoIfNecessary(int currpack);			  //RDH 21/06/99
//DEADCODE JIM 28/01/00 //
//DEADCODE JIM 28/01/00 //	void AddMission(int d,int j,SupplyNode*  currnode);
//DEADCODE JIM 28/01/00 //	void AddAfMission(int d, int j, int af, int score);
//DEADCODE JIM 28/01/00 //	void ListAirfields(int d);
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //	void ListSupplyNodes(int d);
//DEADCODE JIM 28/01/00 //	void AddChokeMission(int d, int j, SupplyRoute*  currroute);
//DEADCODE JIM 28/01/00 //	void ListChokes(int d);
//DEADCODE JIM 28/01/00 //	void ListRoutes(int d, SWord type);
//DEADCODE JIM 28/01/00 //	void AddRouteMission(int d, int j, SupplyRoute*  currroute, SWord type);
//DEADCODE JIM 28/01/00 //	void ListFrontLines(int d);
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //	void	ProcessFrontLine(int d, SupplyLine* sl);
//DEADCODE JIM 28/01/00 //	void	AddCASMission(int d, int j, int score, SupplyLine* sl);
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //	void	FindTargets(int directive);
//DEADCODE JIM 28/01/00 //	void	AllocateStrike(int d, int i, char& note, int profile);
//DEADCODE JIM 28/01/00 //	void	AllocateFighters(int fightersrequired, int d, int i);
//DEADCODE JIM 28/01/00 //DEADCODE JIM 11/04/99    	void	AllocateTargets(int d, char striketype);
//DEADCODE JIM 28/01/00 //	bool	AllocateTargets(int d, char striketype, bool escortreq);
//DEADCODE JIM 28/01/00 //
//DEADCODE JIM 28/01/00 //	void	AircraftAlreadyUsed(int excludedpack, bool countall);
//DEADCODE JIM 28/01/00 //	void	InitAc();
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //	int 	MedBomberStrikeRequired(int d, int i, UniqueID target);
//DEADCODE JIM 28/01/00 //	bool 	AllocMedBomberStrike(int strike,  int type);
//DEADCODE JIM 28/01/00 //	int 	FBStrikeRequired(int d, int i, UniqueID target);
//DEADCODE JIM 28/01/00 //	int 	EscortRequired(SupplyNode*  node);
//DEADCODE JIM 28/01/00 //	bool	AllocAc(int grptype,int ac, int type, int d);
//DEADCODE JIM 28/01/00 //	void	AllocateAlphaStrike(int d, int i);
//DEADCODE JIM 28/01/00 //	int		StrikeTypeRequired(int d, int i);
//DEADCODE JIM 28/01/00 //	bool	CloseToChina(int node_num, SupplyNode*  node);
//DEADCODE JIM 28/01/00 //	int 	FlakRequired(UniqueID target, SupplyNode*  node);
//DEADCODE JIM 28/01/00 //	void	UpdatePackageAircraft(int packnum, int d, int i);
//DEADCODE JIM 28/01/00 //	void	SetPackagesFromDirectives();
//DEADCODE JIM 28/01/00 //	int		DirControl::CategoryAvailable(int d, int squad);
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 //	void AutoGenerate();
//DEADCODE JIM 28/01/00 //	int		CalcAcUsedofType(int squad);
//DEADCODE JIM 28/01/00 //	bool	TargetAlreadyAlloc(UniqueID target);
//DEADCODE JIM 28/01/00 //	void	SaveDirectiveChanges();
//DEADCODE JIM 28/01/00 //	void	LoadDirectiveChanges();
//DEADCODE JIM 28/01/00 //	void	InitDirectivesStruct();
//DEADCODE JIM 28/01/00 //	void	ModifyAcInGrp(int packnum, int wavenum, int groupnum, int squad, int numflights);
//DEADCODE JIM 28/01/00 //	int		MakePackage(int d, int i);
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 
//DEADCODE JIM 28/01/00 };

//DEADCODE ROD 17/12/99 enum	AccelSwitches	{AS_FAVE,AS_ENG,AS_TARG,AS_COAST,AS_TAKEOFF,AS_RECONCOAST,AS_MAX};
enum	AccelSwitches	{	AS_NOTSWITCH,
							AS_RAID_FORMING,
							AS_TAKEOFF,
							AS_COAST,
							AS_SMALL_ENGAGEMENT,
							AS_LARGE_ENGAGEMENT,
							AS_TARG,
							AS_LOSSES,
							AS_LAND,
							AS_MAX};
MAKEFIELD(AccelSwitches,0,AS_MAX);

enum	HostileListFilters	{
							HL_FORMING,
							HL_INCOMING,	
							HL_TARGETAREA,
							HL_DETAILRAID,
							HL_ENEMYSIGHTED,
							HL_ENEMYNOTSIGHTED,
							HL_OUTGOING,
							HL_NORESPONSE,
							HL_RESPONSES,
							HL_MAX
								};

MAKEFIELD(HostileListFilters,0,HL_MAX);

enum	SelectTargetMode	{STM_NORMAL,STM_LWAC,STM_RAFAC,STM_GROUND};

//////////////////////////////////////////////////////////////////////
//
// Function:    Directives
// Date:		28/01/00
// Author:		JIM
//
//Description: 	BOB directives
//				There are 4 sperate sections:
//					DirLW		LW	directives
//						various fields
//						One main set
//						Contains 1 instance of MissLW, perhaps
//						TargLW	Rule per target class
//						Additional sets for historical strategies
//					DirRAF		RAF directives
//						One main set
//						Additional sets for historical strategies
//					MissLW		LW	missions
//						patrol/recon/attack sets
//						historical sets
//					MissRAF		RAF missions
//						patrol/<1sq/1grupp/<=4grupp/>4grupp
//						historical sets
//
//////////////////////////////////////////////////////////////////////
struct	Directives ;
#ifdef	PACKAGE_INCLUDED
#include "flyinit.h" 
#define	DIRECTIVES_DEFINED

struct	Directives
{	
	typedef	Profile::AttackMethod	AttackMethod;
	typedef	Profile::BetterRule	BetterRule;
	struct	LW	//LUFTWAFFE SPECIFIC DIRECTIVES
	{
		enum	MissTypes {PATROL,RECON,ATTACK,MAXMISSTYPES};
		enum	HistTypes {LWHISTORICALPHASE1A, LWHISTORICALPHASE1B,LWHISTORICALPHASE1C,LWHISTORICALPHASE1D,
							LWHISTORICALPHASE2A, LWHISTORICALPHASE2B, LWHISTORICALPHASE2C, LWHISTORICALPHASE2D, 
							LWHISTORICALPHASE3A, LWHISTORICALPHASE3B, LWHISTORICALPHASE3C, LWHISTORICALPHASE3D, 
							LWHISTORICALPHASE4A, LWHISTORICALPHASE4B, LWHISTORICALPHASE4C, LWHISTORICALPHASE4D, 
							MAXHISTTYPES};
		enum	Ju87Usage	{JU_NONE,JU_AM,JU_MD,JU_PM,JU_ANY};
		MAKEFIELD(AttackMethod,Profile::AM_FIELD_MIN,Profile::AM_FIELD_MAX);

		struct	Targ	//Describes one target category
		{
			enum	Categories	//Note I have broughts non-bombing ones together
			{RECON,AIRFIELDS,DOCKS,RADARS,CONVOYS,LONDON,FACTORIES,SWEEPSNDECOYS,RESTING,MAXTARGTYPES};

			float	attached,detached;	//remainder from 1.0 are return - same order as Directives::LW::Miss
			enum	Flags {NONE = 0, FIGHTERSSTRAFFE=1};
			UByte	flags;
			UByte	secondarytargets;
			UWord	bombersperraid;	//Less than 10 A/C gets that number of A/C
									//>=10 gives bpr/10 staffel
									//>=30 gives bpr/30 gruppe
			float acproportions[PT_GERMCOUNT];
			ULong	lastdateandtimeused;	//used to decide which is highest priority recon
			float&	operator[](int ind)	{return acproportions[ind-PT_GER_FLYABLE];}
		};

		struct	Miss	//Describes one LW Mission profile
		{
			AttackMethodField	escortmethods;
			ONLYFIELD(UWord,BetterRule,			acselectionrules);		//And straffing
			ONLYFIELD(UWord,FormationTypeIndex,	formations)[4];			//1 per "page",bomber, attached,detached, return
			ONLYFIELD(UByte,AttackMethod,		bomberattackmethod);
			SWord		bombers,attfighters,detfighters,retfighters;	//generate proportions at display time
			UByte		NumTargets;
			ULong		mainalt;	//in cm

		};
		struct Reconn 
		{
			UByte	missions;	//spin
			UByte	ac;			//spin 1-3
			bool	escort;
			bool	morningonly;
			int		escortactype;
		};
		struct	Dir		//Describes the directives settings
		{
			Targ	targetlines[Targ::MAXTARGTYPES];
			Reconn	reconn;
			float	morningquota,middayquota;	//remainder from 1.0 are eveningquota
			AttackMethodField	escortmethods;
			int		arrivalminsseperation;	//2=coordinated;15 is consecutive.
			Ju87Usage	ju87usage;
			float		escortproportion;
		};

		struct	OneDirResult	//Describes one resultant mission
		{	enum	{MAXTARGETS=7};					//I think we would want to put patrols on a seperate page
			Miss	mission;
			UniqueID	targets[MAXTARGETS];	//1+MAXSECONDARIES+1				//JIM 14Aug00
			int			ETA;
			int*		usesquadsavail;
			int			squadsavail[PT_VEHICLES];
		};

		Miss	userprofiles[MAXMISSTYPES];
		Dir		current;
		Dir		histdir[MAXHISTTYPES];
//TEMPCODE JIM 28/01/00 		Miss	histmiss[Miss::MAXHIST];
		static void	AI();
		static void	SetUpReconn();


	}	
	lw;


	struct	RAF	//RAF SPECIFIC DIRECTIVES
	{
		enum	MissTypes {PATROL,ANTISWEEP,ANTISINGLE,ANTIUNESC,ANTIESC,ANTIBIG,MAXMISSTYPES};
		enum	MissTypesBits {MTB_PATROL=1,MTB_ANTISWEEP=2,MTB_ANTISINGLE=4,MTB_ANTIUNESC=8,MTB_ANTIESC=16,MTB_ANTIBIG=32,MTB_MAXMISSTYPES=64,MTB_ANTIALL=64-2};
		enum	HistTypes {HISTORICALSCENARIO_PHASE1,
							HISTORICALSCENARIO_PHASE2,
							HISTORICALSCENARIO_PHASE3,
							HISTORICALSCENARIO_PHASE4,
							HISTORICALSCENARIO_A,
							HISTORICALSCENARIO_B,
							HISTORICALSCENARIO_C,
							HISTORICALSCENARIO_D,
							HISTORICALSCENARIO_E,
							HISTORICALSCENARIO_F,
							HISTORICALSCENARIO_G,
							HISTORICALSCENARIO_H,
							MAXHISTTYPES};
		MAKEFIELD(MissTypes,PATROL,MAXMISSTYPES);

		struct	Miss	//Describes one response profile
		{
			ONLYFIELD(UWord,BetterRule,			acselectionrules);		//And straffing
			ONLYFIELD(UByte,Profile::AttackMethod,	packageattackmethod);	//tactics
			int	mainalt;
			struct	PerType		
			{
				SByte				numac;		//div 12 to get squads	or use -ve numbers
				ONLYFIELD(UByte,Profile::SubMethod,		what);	//avoid bombers/fighters
				ONLYFIELD(UWord,FormationTypeIndex,		formation);
			};
			PerType	hurr,spit;
		};
		struct	Dir		//Describes the RAF directives
		{
			MissTypesField	sanctioned;
			enum  GeneralSize	{ONESQ,PAIRED,BIGW};	//I guess these are patrol sizes
			ONLYFIELD(UByte,AttackMethod,	approach);	//tactics is not on directives????

			int		restifcatbelow,restifavailbelow;

			//The squads not resting are partitioned so the following add up to 1.0 each

			float	gr11radarpatrol,gr11convoypatrol,gr11coastalpatrol;	//remainder from 1.0 can intercept
			float	gr1012afpat,gr1012acfactpat,gr1012supfactpat;		//remainder from 1.0 can intercept

			//The squads on intercept are applied using the following rules
			
			float	convoylevel;			//1.0 is matched
			bool	interceptbeforetarget;	//
			GeneralSize	unitsize;

		};
		struct	DirResult	//Describes one patrol mission profile
		{					//We could list the 10/12 and 11 patrols on seperate pages
			Miss		mission;
			UniqueID	target;
			Dir::GeneralSize	unitsize;
			SquadNum	squadrons[6];
			int			ETA;
		};					//We could list rested and intercept ready squads on further pages
		Miss	userprofiles[MAXMISSTYPES];
		Dir		current;
		Dir		histdir[MAXHISTTYPES];
		static void	SessionAI();
		static void	AI();
		static void	ModifyPatrols();


//TEMPCODE JIM 28/01/00 		Miss	histmiss[Miss::MAXHIST];
	}	raf;


};
int	Todays_Packages_NewPackage(UniqueID targ,Directives::RAF::Miss& missiondesc,int targetalt=0);//,int* actypecounts=NULL);
int	Todays_Packages_NewPackage(UniqueID targ,Directives::LW::Miss& missiondesc,UniqueID* secondarytrg= NULL, bool Gruppe = false,int* actypecounts=NULL);
//DeadCode RDH 08Feb00 struct	LWDirectivesResultsTargetList
//DeadCode RDH 08Feb00 {
//DeadCode RDH 08Feb00 	enum	{MAX_TARGETS = 300};
//DeadCode RDH 08Feb00 UniqueID	target;
//DeadCode RDH 08Feb00 int			priority;
//DeadCode RDH 08Feb00 };

struct	LWDirectivesResults
{
	struct	TargetList
	{
  	UniqueID	target;
	int			priority;
	};
	enum	{MAX_TARGETS = 300, MAX_RESULTS =100};

	TargetList target[MAX_TARGETS];

		struct FighterSplit
	{
		float ret;
		float att;
		float det;
	};
			struct	Targets
	{
		TargetList target[MAX_TARGETS];
	};

	Targets trgarray[8];
	int reconntrg[4];

	FighterSplit	otherraids;
	FighterSplit	firstraids;


	Directives::LW::OneDirResult	dirresults[MAX_RESULTS];
	Directives::LW::Dir		tempdir;
	float LWGrAvail[PT_GERMCOUNT];

//DeadCode RDH 08Feb00 	static int	InsertTarget(LWDirectivesResultsTargetList* target, UniqueID uid, int currtrg);
	static int	InsertTarget(TargetList* target, UniqueID uid, int currtrg, int uidbandstart);
	static int TargetX(int i);

	static int	FillTargetList(TargetList* target,int uidbandstart, int uidbandend, int trgtype);
//DeadCode RDH 08Feb00 	static int	FillTargetList(LWDirectivesResultsTargetList* target,int uidbandstart, int uidbandend, int trgtype);
	static	void FillDirectivesResults(LWDirectivesResults* dr);
	static int	FillReconnDirectivesLine(LWDirectivesResults* dr, int k);
	static	int	HowManyReconEscortRequiredThisPeriod(LWDirectivesResults* dr);
	static	int	 FillOneDirectivesLine(LWDirectivesResults* dr, int i, int k, int& missions);
	static 	void FindAcAvail(LWDirectivesResults* dr);
	static int LWDirectivesResults::FindMaxSquads(LWDirectivesResults* dr);
	static	void SetLWDirectivesResults();
	static	void FillTargetLists(LWDirectivesResults* d);
	static	void MakeLWPackages(LWDirectivesResults* dr, bool manual);
	static	void AutoLWPackages();
	static	void LaunchDirectiveMissions();
	static  void LWDirectivesResults::SetUpLWDirectives(Directives::LW::HistTypes dirtype);
 	static Directives::LW::MissTypes  LWMissType();
//DEADCODE RDH 05/04/00 	static  void SetSecondaryTargets(LWDirectivesResults* dr,int i, int packnum);


};
struct	RAFDirectivesResults
{
	struct	AvailSquads
	{

		int gr11radarpatrol;
		int gr11convoypatrol;
		int gr11coastalpatrol;
		int gr11intercept;
		int gr11total;
		int	gr11maxtotal;

		int gr1012afpat;
		int	gr1012acfactpat;
		int gr1012supfactpat;
		int gr1012intercept;
		int gr1012total;
		int	gr1012maxtotal;

	};
	AvailSquads	availsquads;
	struct	TargetList
	{
  	UniqueID	target;
	int			priority;
	};
	enum	{MAX_TARGETS = 300, MAX_RESULTS =100};
	enum	{MAX_AF = 100};
	struct	AirField
	{
		UniqueID uid;
		int		priority;

	};
//DeadCode RDH 10Sep00 	AirField Airfields[MAX_AF];


	TargetList target[MAX_TARGETS];
	enum	{COASTAL, SOUTHLONDON, NORTHLONDON};
	int oldfrontlinefields;
	int newfrontlinefields;
	static 	int	FindAfUsage();


	Directives::RAF::DirResult	dirresults[MAX_RESULTS];
	Directives::RAF::Dir		tempdir;
	static void	FillDirectivesResults(RAFDirectivesResults* dr);
	static void	FindSquadsAvail(RAFDirectivesResults* dr);
	static void SetDirectivesResults(RAFDirectivesResults* dr);
	static int	SetAfPatrols(RAFDirectivesResults* dr, int patrols, int k);
	static int	InsertTarget(TargetList* target, UniqueID uid, int currtrg);
	static void	SetAfPatrolTargets(RAFDirectivesResults* dr);
	static	void	SetFactPatrolTargets(RAFDirectivesResults* dr, bool acfact);
	static int SetPatrols(RAFDirectivesResults* dr, int patrols, int k, Profile::BetterRule br);
	static void	SetStdPatrolTargets(RAFDirectivesResults* dr,int uidbandstart, int uidbandend,bool patrolifalive);
	static	void MakeRAFPatrols(RAFDirectivesResults* dr);
	static	void AutoRAFPatrols();
	static	void SetRAFIntercept(int pack, int raid,bool afteregress);
	static	void RAFDirectivesResults::RaidAcNumbers(int pack,int raid, int& strike, int& detachedescort, int& attachedescort, int& returnescort);
	void 	MoveSquadronswrtFrontLine();
	static	int FindAirfield(int priority, int maxaf, AirField* Airfields);


	static void MoveSquadron(int sqnum,  int loc0, int loc1, int loc2);
	static	void	SetUpRAFDirectives(Directives::RAF::HistTypes dirtype);
	static  int	InterceptSanctioned(int pack, int raid);
   	static Directives::RAF::MissTypes  RAFMissType(int packnum);
	static Directives::RAF::MissTypes  RAFDirectivesResults::RAFInterceptType(int lwpack, int sqnum);


};

struct	PeriodReviewBase
{
	enum	ReviewType {KILL0,KILL1,KILL2,AVAILSTART,DAMAGE,REPAIR,DESTROY,CREATE,TOTALLOSSES, SORTIES, NEWREPAIRS,POTENTIALREPAIRS,REPAIRSINSYSTEM};
	struct	TypeStats
	{

		UWord	totalkills[3],	//Set for SAGs on map //spit/hurr or bomber/109/110

				availablestart,
				damaged,		//Set in Squad::ApplyFlyingLosses
				repaired,		//Set in AircraftRepairs4Hour
				destroyed,		//Set in Squad::ApplyFlyingLosses
				created,		//Set in DeliverProductionRates
				totallosses,
				sorties,
				newrepairs,
				potentialrepairs,
				repairsinsystem
				;
	};
	TypeStats	raf[2],lw[6];
};

struct	LastWeekReview:PeriodReviewBase
{
	int	lwtodaylosses,lwrecordlosses;
	int	raftodaylosses,rafrecordlosses;
	int	acproductiondelta[2],dayssincedeltapos[2];
	float	rafloss[2],lwloss[5];

	int		Note(PlaneTypeSelect scorer,ReviewType field,int delta);
	void	SetNote(PlaneTypeSelect scorer,ReviewType field,int value);
	int		Note(PlaneTypeSelect scorer,PlaneTypeSelect target,int delta);
	void	ClearToday();
	float& DecayingLossRate(PlaneTypeSelect	actype);

};
struct	PeriodReview:PeriodReviewBase
{
	operator=(LastWeekReview* lwr) 
	{ *(PeriodReviewBase*)this=*(PeriodReviewBase*)lwr;	}
};


#endif

#endif
