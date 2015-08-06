//------------------------------------------------------------------------------
//Filename       missman2.h
//System         
//Author         Jim Taylor
//Date           Thu 22 Aug 1996
//Description    
//------------------------------------------------------------------------------
#ifndef	MISSMAN2_Included
#define	MISSMAN2_Included

#define	DEFAULT_MISSMAN2 0

//this means that I dont want any common files							//RDH 18/05/00
#define	f_common

//DEADCODE MS 02/02/00 #include	"textref.h"
#define		F_SOUNDS
#define		F_COMMON
#include	"Files.g"
#include	"myangles.h"											//RDH 20Dec95
//DEADCODE MS 02/02/00 #include	"flyinit.h"											//RDH 20Dec95
#include	"worldinc.h"										//RDH 11Aug96
//DEADCODE MS 02/02/00 #include	"debrief.h"
#ifdef	PACKAGE_INCLUDED
#include	"sky.h"

#ifdef	DEFAULT_MISS_MAN
//
// If the module is declared a second time, then this alternate construction 
// is made to allow instances to occur.
//
	#define	basestruct(subname)							\
	struct	II_##subname			{

	#define	substruct(subname,parentname)				\
	struct	II_##subname			{					\
		II_##parentname	parentinst;

	#define	endstruct(subname)		};					\
	union	I_##subname									\
		{	II_##subname II;subname I;}

	#define	startinst(strucname,instname)	 			\
		II_##strucname	I_##instname	=	{

	#define	endinst(strucname,instname)	 	};			\
		strucname&	instname=*(strucname*)&I_##instname;

#else
//
// This definition defines substructures by simple inheritance
// That will not allow initialisation.
//
	#define	basestruct(subname)							\
	struct	subname					{

	#define	substruct(subname,parentname)				\
	struct	subname : parentname	{

	#define	endstruct(subname)		}

#endif

#endif //package_included

#define	DEFAULT_MISS_MAN 0
struct	MissionType;
struct	PilotType;
struct	PeriodReview;																//DAW 23Aug96
#ifndef	MISS_MAN_Included2										//DAW 23Aug96

#include "bitfield.h"											//DAW 23Aug96
#include	"misssub.h"

#endif
//////////////////////////
//
// This is a far better subdivision of fields
// in order to manage a copy of the active campaign
//
//////////////////////////
#if defined(PACKAGE_INCLUDED) //&& defined (DIRECTIVES_DEFINED)
basestruct	(CampaignBase)
	int	garbage;
	FileNum	introsmack;
	FileNum	introquarterart;
endstruct(CampaignBase);
//////////////////////////
substruct	(CampaignPtrs,CampaignBase)
//	MissionType*	currmission;
//	MissionType*	dfltmission;

endstruct(CampaignPtrs);
//////////////////////////

substruct	(CampaignStatic,CampaignPtrs)
	UniqueID		playerhomebase;
	UniqueID		playertakeoff;
	bool			firsttime;
	SLong			startdate;
	SLong			ripdate;
	SLong			currdate;
	SLong			lastdate;
	SLong			currtime;
	SLong			currperiodtime;
	SLong			dawntime;
	SLong			dusktime;
	SLong			sunsouth;
	UByte			sl_category;		//squadlist 

//	SWord			weathernum;											//RDH 02Oct96
//	struct			Wind {
//						SWord	speed;
//						SWord	velx;
//						SWord	velz;
//						ANGLESInst	direction;			//direction from which the wind comes
//						}	wind;

	RankType		playerrank;
	SkillType		newpilotskill;
	SWord			frontdeltastrength,
					reservesavail;
	SWord			currentplayerslot;
//DeadCode RDH 25Mar97 	SWord			correctplayerslot;
	char	PlayerName[PLAYERNAMELEN];
	char	aircraftname[20];
	UniqueID	InitialFront[3];
//	FileNum	mainbfield;
	Directives::LW::HistTypes	lwdir;
	Directives::RAF::HistTypes	rafdir;
	FileNum			camp_win_anim;
	FileNum			camp_lost_anim;
endstruct(CampaignStatic);
//////////////////////////
substruct	(CampaignBlueSquad,CampaignStatic)
	Directives		directives;
//DEADCODE JIM 28/01/00  	enum					{MAX_AC_NUM = 19};
//DEADCODE DAW 24/11/99 struct	SquadronInfo
//DEADCODE DAW 24/11/99 {
//DEADCODE DAW 24/11/99 	PlaneTypeSelect	actype;										//RDH 07Apr96
//DEADCODE DAW 24/11/99 	int				name;	//TextSnip0	 		name;
//DEADCODE DAW 24/11/99 	SWord			airfieldindex;
//DEADCODE DAW 24/11/99 	SWord			movetoairfieldindex;
//DEADCODE DAW 24/11/99 	SWord			nextacnumber;
//DEADCODE DAW 24/11/99 	SWord			ac_total_avail;
//DEADCODE DAW 24/11/99 	SWord			rotatefreq;
//DEADCODE DAW 24/11/99 	SLong			lastrotatedate;
//DEADCODE DAW 24/11/99 	SWord			flt_used;		//not used!
//DEADCODE DAW 24/11/99 	int				bingofuel;					//0.01kg
//DEADCODE DAW 24/11/99 	AcTactics		elementtactics;
//DEADCODE DAW 24/11/99 	AcTactics		flighttactics;
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 //	SWord			flt_pilots_avail;
//DEADCODE DAW 24/11/99 //	SWord			lastflightform,lastgrpform;
//DEADCODE DAW 24/11/99 //	SWord			flightnum [MAX_FLIGHT_NUM];
//DEADCODE DAW 24/11/99 //	SWord			formationnum [MAX_FLIGHT_NUM];
//DEADCODE DAW 24/11/99 //	SWord			squadronform;
//DEADCODE DAW 24/11/99 //	NextLeadAct		nextleadact [MAX_FLIGHT_NUM];
//DEADCODE DAW 24/11/99 };
//DEADCODE DAW 24/11/99 	SquadronInfo	squad[PILOTABLE_SQUADRONS];

endstruct(CampaignBlueSquad);
//////////////////////////
substruct	(CampaignSquad,CampaignBlueSquad)

//DEADCODE DAW 24/11/99 struct	MigSquadronInfo
//DEADCODE DAW 24/11/99 {
//DEADCODE DAW 24/11/99 	PlaneTypeSelect	actype;				//15 or 15bis 
//DEADCODE DAW 24/11/99 	SWord			colourscheme;		//0..7			
//DEADCODE DAW 24/11/99 	int				squadnameindex;		//name and desc index
//DEADCODE DAW 24/11/99 	int				startdate;			//earliest date this squad can be used
//DEADCODE DAW 24/11/99 	SWord			ac_total_avail;		//red squad size
//DEADCODE DAW 24/11/99 	SWord			aclosses;			//total since squad launched
//DEADCODE DAW 24/11/99 	SWord			aclosseslast;		//last 3d session
//DEADCODE DAW 24/11/99 	SkillType		generalskill;		//ONE FIELD improve over time
//DEADCODE DAW 24/11/99 	MoraleType		morale;				//squadron variable
//DEADCODE DAW 24/11/99 	tAggressionLevel	agglevel;		//squad - improve slowly
//DEADCODE DAW 24/11/99 	RedEvents		maxevent;			//improve very slowly - every 16 days?
//DEADCODE DAW 24/11/99 
//DEADCODE DAW 24/11/99 };
//DEADCODE DAW 24/11/99 	MigSquadronInfo	migsquad[MAXMIGSQUADRONS];	//first 2 are active squadrons
//DEADCODE DAW 24/11/99 	int	nextsquadtocopy;						//copy to 1 of first 2

endstruct(CampaignSquad);
//////////////////////////
substruct	(CampaignPackages,CampaignSquad)
//	Package package[MAX_PACKAGE_NUM];
enum					{MAX_MISSIONPERCAMPAIGN = 8};
//DEADCODE DAW 24/11/99 struct CampMissionDef
//DEADCODE DAW 24/11/99 {
//DEADCODE DAW 24/11/99 	SLong			msn_date;
//DEADCODE DAW 24/11/99 	SLong			msn_time;
//DEADCODE DAW 24/11/99 	UniqueID		target;
//DEADCODE DAW 24/11/99 	UniqueID		captarget;
//DEADCODE DAW 24/11/99 	FileNum			profile;
//DEADCODE DAW 24/11/99 };
//DEADCODE DAW 24/11/99 	int				winscore;
//DEADCODE DAW 24/11/99 	Debrief::DisEntry		dis;
//DEADCODE DAW 24/11/99 	CampMissionDef		missions[MAX_MISSIONPERCAMPAIGN];


endstruct(CampaignPackages);
//////////////////////////
substruct	(CampaignPilots,CampaignPackages)
//DEADCODE DAW 24/11/99 	PilotType	Active_Pilots[PILOTS_PER_CAMPAIGN];
endstruct(CampaignPilots);
//////////////////////////
//DEADsubstruct	(CampaignFiles,CampaignPilotsOnly)
//DEAD//DeadCode RDH 18Feb97 
//DEAD//DeadCode RDH 18Feb97 	FileNum	introsheetart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	intropadart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	introiconart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	cr_iconart;
//DEAD//DeadCode RDH 18Feb97  	FileNum	lc_iconart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	historyart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	personnelart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	junctionart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	squadart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	saveart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	savedialogue;
//DEAD//DeadCode RDH 18Feb97 	FileNum	quitart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	padart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	mainiconart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	flightart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	newstextart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	newsgraphicart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	flightgraphicart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	acsmallart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	acmedart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	aclargeart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	paintshopart;
//DEAD//DeadCode RDH 18Feb97 	FileNum	introtextart;
//DEAD
//DEAD	TextSnip0	objecttext;
//DEAD	TextSnip0	introtext;
//DEAD	TextSnip0	editnametext;
//DEAD	TextSnip0	editnametitle;
//DEAD
//DEADendstruct(CampaignFiles);
//////////////////////////
//DEADsubstruct	(CampaignPilots,CampaignFiles)
//DEAD	PilotType	Reserve_Pilots[PILOTS_IN_RESERVE];
//DEAD//DeadCode RDH 27Mar97 	PilotType	aces[ACESLIST];
//DEADendstruct(CampaignPilots);
//DEAD//////////////////////////
//DEADsubstruct	(CampaignTank,CampaignPilots)
//DEAD	SLong		Tank_timer;
//DEAD	SLong		Truck_timer;
//DEAD//DeadCode RDH 24Feb97 	UniqueID	routesstartuids[MAXROUTES];
//DEAD//DeadCode RDH 24Feb97 	UniqueID	routesenduids[MAXROUTES];
//DEADendstruct(CampaignTank);
//DEAD//////////////////////////
//DEADsubstruct	(CampaignTankZero,CampaignTank)
//DEAD	int			blueacflying;
//DEAD	UniqueID	blueguns[MAXGUNS];
//DEAD	UniqueID	blueaaa[MAXGUNS];
//DEAD	TnkMapWpSet	tankcampwp[MAXTNKWPINROUTE];							//RDH 08Oct96
//DEAD	struct Convoy {
//DEAD		UniqueID	uid;
//DEAD 		FileNum		bfield;
//DEAD		SWord		size;
//DEAD
//DEAD		};	Convoy convoys[MAXCONVOYS];
//DEAD
//DEADendstruct(CampaignTankZero);
//////////////////////////
#undef	basestruct
#undef	substruct
#undef	endstruct

#ifndef	MISS_MAN_Included2
#define	MISS_MAN_Included2

struct	CampaignZPilots:CampaignPilots
{
//DEAD	PilotType		Wounded_Pilots[CASUALTYLIST],
//DEAD					Dead_Pilots[CASUALTYLIST];
//DEAD	SquadronInfo	Temp_Squadron;
//DEAD	PilotType		Temp_Pilots[PILOTS_PER_CAMPAIGN];
  PilotHist		dead_pilots[CASUALTYLIST];
};

struct	CampaignZero:CampaignZPilots
{
//DeadCode RDH 02Oct96 	enum					{MAXWEATHERNUM = 4};
//Dead	WpSetType		players_wpset;
//Dead	SLong			TrainingCount;
//Dead	SLong			TrainingRange;
//DeadCode RDH 02Oct96 	SWord 			currweathernum;
//DeadCode RDH 02Oct96 	SWord 			currwindnum;
//Dead	SWord			currmission_no;
//Dead	SWord			missionwpset;
	PeriodReview	firstweek,prevweeks[6];
	LastWeekReview	thisweekreview;
	int				earliestquit3dtimecs;
	SWord			missionarea;
	MeritType		playermerit;
	SWord			killsonbestday;
	SWord			currmissionfamily;
	SWord			dayssincetransfer;
	SWord			nextdeadpilot;
	SWord			playersquadron,playeracnum;
	int				curr_score;				//used in mission scoring //RDH 19/03/99
	int				curr_msn;				//used in mission scoring //RDH 19/03/99
	bool			wincamp;	
	FileNum			smacker;				//a smacker generated by last mission
	int				msgwithsmacker;				//a smacker generated by last mission //RDH 26/06/99
	UByte			sl_group;				//squad list setup
	UByte			sl_ac;
	UByte			sl_flotte;				//squad list setup
	UByte			sl_geschwadertype;
	UByte			sl_status;
	UByte			sl_min_ac;
	UByte			sl_min_pilot;			//squad list setup
	SLong			curraccelrate;
	SLong			accumulator;
	bool			directivespopup;
	bool			autoscramble;
	enum	AccelType	{ACCEL_PAUSED,ACCEL_NORMAL,
				ACCEL_NONRAIDSPD,ACCEL_RECONNSPD,ACCEL_RAIDSPD,ACCEL_DIALOGSPEED, 
				ACCEL_MAX};
	AccelType		curracceltype;
	SLong			accelrates[ACCEL_MAX];
	HostileListFiltersField	hostilefilters;
	struct Fav
	{
		AccelSwitchesField	decelon,flyon, flyonfav;
		int				group;
		int				ac;
		int				sector;
		int				squadron;
		int				forcesquadron;		//go to frag without dialog request	//RDH 27/03/00
		int				flotte;
		int				geschwadertype;
		int				geschwader;
		int				gruppe;
		int				forcegruppe;		//go to frag without dialog request	//RDH 27/03/00		

	}	fav;
//mission folder flags
	bool			rafplanned;
	bool			rafoutgoing;
	bool			rafengaged;
	bool			rafincoming;
	bool			raflanded;
	bool			rafpatrol;
	bool			rafintercept;
	bool			lwplanned;
	bool			lwactive;
	bool			lwlanded;
	bool			lwstrike;
	bool			lwattachedescort;
	bool			lwdetachedescort;
	bool			lwreconn;
//intell flags
	bool		intel[6];//engagement;
//	bool		intelflight;
//	bool		intelmanagement;
//	bool		intelspotting;
//	bool		inteltargetstatus;
	bool		pacsuccessful;				//jt
	UByte		phasechanged;				//rdh	periods since change
//	UByte		dayssinceacincreased[2];	//jt
	UniqueID	historictargetuiddamaged;	//jt
	UniqueID	historictargetuiddestroyed;	//jt
//	UWord		lwtodayslosses;				//jt
//	UWord		raftodayslosses;			//jt
//	UWord		lwrecordlosses;				//rdh
//	UWord		rafrecordlosses;			//rdh
	SWord		undefendedconvoylosses;
	SWord		undefendedcriticaltargetlosses;
			

//DEADCODE RDH 20/12/99 	UniqueID		pilotonaf;
//DEADCODE RDH 20/12/99 	int				pilotonsquad;
//DEADCODE RDH 20/12/99 	int				pilotonwader;

//Dead	SWord			lastrecoveredpilot;
//Dead	TextSnip0		lasttransferee;
//Dead	TextSnip0		lastdeadsuperior;
//Dead	TextSnip0		specialeventtext;							//RDH 06Sep96
//Dead	FileNum		playerbfield;
//Dead	TextPerm	playernameref;
//DeadCode JIM 17Aug00 	SpecialEventBitField	specialeventbits;
//DeadCode JIM 17Aug00 	NewsEventField			newsevent;
//DeadCode AMM 7Aug00 	Bool		indebrief;
//DEADCODE DAW 29/01/00 	Debrief		debrief;
	ATMOSPHERE		Sky;
//DEADCODE DAW 29/01/00 	SG_DirControl	directives;
 	char	CommsPassword[11];
	SWord	packageprevscores[10];

	void	SetCurrMission (MissionType*);
	bool	ChkEndCampaign();
//DEADCODE DAW 29/01/00 	int		StoresDestroyedForNodeRoute(SupplyNode* node);
//DEADCODE DAW 29/01/00 	void	BattleLossesForNode(SupplyNode* node, int& redlosses, int& bluelosses);


	void	NextMission();
	void	NextDay();
	void	ReplenishAcStock(); //RDH 15/02/99
	void	RotateMiGSquadron(int squad);							  //RDH 09/03/99
	void	ChkRotateMiGSquadrons();								  //RDH 09/03/99
	void	ModifyMiGAggressionLevel(int squad);					  //RDH 09/03/99 //RDH 09/03/99
	void	SwapPilot(int groupnum, int src,int dest);	
	void	SwapElement(int groupnum, int src, int dest);
	void	SwapFlight(int groupnum, int src, int dest);
	void	RotateFlightsCheck();
	void	ModifySkill(int groupnum, int daysonduty);

//DEADCODE RDH 03/04/00 	void	EndDebrief();
	void	CampaignInit();
	void	InitIcons();
//DEADCODE DAW 29/01/00 	void	AddDebriefData(Debrief::SquadKills& src, Debrief::SquadKills& dest);
//DEADCODE DAW 29/01/00 	void	ZeroDebriefData(Debrief::SquadKills& dest);
//DEADCODE DAW 29/01/00 	void	DisDayEntry(Debrief::TypeFlag type, int msgowner, int msgtextid);
//DEADCODE DAW 29/01/00 	void	UpdateAllDis();
	void	UpdatePlayerLog();										  //RDH 19/06/99
	void	ZeroDisDay();
	FileNum	FindSmacker(int index);
	void	MakeNewPilot(int pilot);
	void	KillPilot(int pilot, pilotstatus status);
	void	MoveDeadPilots();
	void	SetOldPackScore(int packnum);
	bool	GetMissionSuccess(int packnum);
	enum	TimeColours	{TC_RED,TC_YELLOW,TC_BLUE,TC_OLD};
	static bool	AnyDialogsOpen();
	static void	GlobalRefreshData();
	TimeColours	TimeColour(int timetotest=0);	//

//DEADCODE RDH 06/04/00 	bool	inentirewar;

	//Set campaign up
	CampaignZero& operator = (CampaignBase	*);
	CampaignZero& operator = (CampaignZero&	);
	//Update existing campaign
	CampaignZero& operator += (CampaignBase	*);
	CampaignZero& operator += (CampaignZero&	);


//DEADCODE DAW 24/11/99 	static	 MigEvent	migevents[MIGEV_MAX];
//DEADCODE DAW 24/11/99 	static	PilotType	Active_Pilots_Init[PILOTS_PER_CAMPAIGN];

};

struct	CampaignZero;
struct	CampaignBase;
typedef	CampaignZero	Campaign;



//------------------------------------------------------------------------------
//DeadCode RDH 13Jun96 #include	"uid.g"												//RDH 21Dec95
class	 MissMan
{
public:
	static enum	CampaignName {
		INTROCAMPAIGN = 0,
		CONVOY_CAMPAIGN = 0,
		RADAR_CAMPAIGN,
		ARFIELD_CAMPAIGN,
		BLITZ_CAMPAIGN,
//DEADCODE RDH 03/04/00 		SO51_CAMPAIGN,
//DEADCODE RDH 19/03/99 		PEACETALKCAMPAIGN,
//DEADCODE RDH 19/03/99 		RUNDEMOCAMPAIGN,
 		SCRAMBLECAMPAIGN,
//DEADCODE RDH 19/03/99 		H2HCAMPAIGN,											//RDH 05Sep96
		MINCAMPAIGNNUM = 0,
 		MAXCAMPAIGNNUM = 5,										//RDH 05Sep96
//DEADCODE RDH 19/03/99 		MAXACTUALCAMPAIGNNUM = 3
		} 	currcampaignnum;

	static CampaignBase	*campaigntable[MAXCAMPAIGNNUM];
	Campaign	camp;
//DeadCode JIM 30Oct00 	Campaign	backup;

};
extern	MissMan Miss_Man;
extern	Campaign&	MMC;		//This is to help the completion wizard
#define	MMC	Miss_Man.camp
//#pragma warnmsg()
#endif
//#pragma warnmsg()
#endif
//#pragma warnmsg()
class Atmosphere;
typedef Atmosphere ATMOSPHERE, *PATMOSPHERE;
	ATMOSPHERE&	MissManCampSky();
int	MissManDawnTime();
int	MissManDuskTime();
int	MissManSunSouth();


#endif




