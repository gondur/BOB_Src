////////////////////////////////////////////////////////////////////////
//
// Module:      package.h
//
// Created:     12/01/99 by JIM
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
#ifndef	PACKAGE_INCLUDED
#define	PACKAGE_INCLUDED
//package structure definition
//
//This defines everything that we don't want in battlefield file
//if packages are supposed to be reusable.
//There may be an instance of it at the top of the BF, 
//but we will often override it.
//
//Globrefs required to manage waypoint system:


#include	"bitcount.h"
enum FileNum;
enum	Ranges;
enum	SquadNum;
enum	FormationTypeIndex;
enum	BFieldWaypointActions;
enum	Nationality;
struct	lchpak;
struct	SquadList;
struct	Squadron;
struct	info_airgrp;
enum	PlaneTypeSelect;
struct	info_waypoint;
class	BOStream;
class	BIStream;
enum	SquadNum;
class	CString;

enum	SavedGlobrefs
{
	SGR_Pack_BlankZero=0,
	SGR_Pack_Takeoff=1,	//package key points
	SGR_Pack_DogLeg,
	SGR_Pack_Target,
	SGR_Pack_Target1,
	SGR_Pack_Target2,
	SGR_Pack_Target3,
	SGR_Pack_Target4,
	SGR_Pack_Target5,
	SGR_Pack_Target6,
	SGR_Pack_Target7,
	SGR_Pack_Target8,
	SGR_Pack_Target9,

	SGR_WPP_TakeOff,
	SGR_WPP_BombRendezvous,
	SGR_WPP_EscRendezvous,
	SGR_WPP_DogLeg,
	SGR_WPP_IP,
	SGR_WPP_EstPoint,
	SGR_WPP_Target,
	SGR_WPP_Egress,
	SGR_WPP_EscDisperse,
	SGR_WPP_BombDisperse,
	SGR_WPP_Landing,

	SGR_WPC_TakeOff,			//Note that there are multiple instances
	SGR_WPC_Target,				//of each of these globrefs in a route
	SGR_WPC_PatrolS,			//This means that they cannot be used as
	SGR_WPC_PatrolE,			//as reference locks
	SGR_WPC_Landing,			//for intermediate waypoints.

	SGR_WPC_FighterLimit,

	SGR_WPP_Msg0,
	SGR_WPP_Msg1,
	SGR_WPP_Msg2,
	SGR_WPP_Msg3,
	SGR_WPP_Msg4,
	SGR_WPP_Msg5,
	SGR_WPP_Msg6,
	SGR_WPP_Msg7,
	SGR_WPP_Msg8,
	SGR_WPP_Msg9



};
struct	Profile					
{
	enum	{MAXRAFPLANNEDSQUADRONS = 32, MAXRAFPATROLS = 30,MAXLWPLANNEDSTAFFELN = 96}; 
	enum	{MAX_PACKS=512,MAX_TARGETS=10,MAX_NEGTARGETS=3,MAX_SQUADS=96};
	enum	AttackMethod	
	{
	AM_RAF=0,			AM_PATROL=0,AM_INTERCEPT,
	AM_FIELD_MIN=8,
	AM_LWPACKS=8,		AM_DECOYPATROL,AM_RECON,AM_DIVEBOMB,AM_LEVELBOMB,AM_CHAINBOMB,
	AM_ESCORTTYPES=16,
	AM_DETACHED=16,		AM_CEILING, AM_HIGH, AM_FORWARD_HIGH, AM_FORWARD, AM_FORWARD_LOW, AM_LATE ,AM_PASTDETACHED,
	AM_ATTACHED=24,		AM_ASTERN, AM_INFRONT, AM_PORT, AM_STARBOARD,AM_ABOVE, AM_BELOW,
	AM_RETURNESCORT = 32, AM_RET_ASTERN, AM_RET_INFRONT, AM_RET_PORT, AM_RET_STARBOARD,AM_RET_ABOVE, AM_RET_BELOW,

/**/AM_GROUPMASK=-8,
	AM_NULL = 255,
	AM_FIELD_MAX=39,
	AM_GOODLIMIT=40
	};
	typedef MakeField<AttackMethod, AM_FIELD_MIN,AM_FIELD_MAX> AttackMethodField;
	enum	PackageStatus	
	{	//squad status	//tote status
		PS_SPARE,		PS_OFFBASE=PS_SPARE,
		PS_ORDER_30,
		PS_AT_30,	
		PS_ORDER_5,
		PS_AT_5,	
		PS_ORDER_2,
		PS_AT_2,
		PS_PLANNING,	
		PS_PLANNED,		PS_ORDER_ONPOSITION=PS_PLANNED,
		PS_PLAN_30,
		PS_PLAN_5,
		PS_PLAN_2,
		PS_ACTIVE_MIN,
		PS_TAKINGOFF,
		PS_FORMING,
		PS_INCOMING,	
		PS_TARGETAREA,	PS_INPOSITION=PS_TARGETAREA,
		PS_DETAILRAID,
		PS_ENEMYSIGHTED,
		PS_OUTGOING,	PS_ORDERLAND=PS_OUTGOING,
		PS_ACTIVE_MAX,
		PS_LANDING,
		PS_REFUELLING,
		PS_COMPLETE,
		PS_AIRFIELDOUT
	};

	enum	BetterRule
	{	//Rules playes can set to select aircraft types more precicely
		BR_NONE			=	0,
		BR_WIDESTPOSSIBLE=0x0ffff,	//I have coded this in select routines
		BR_B_SPITONLY	=0x0000D,		//spitfire from any group with/without leader. These can choose a squad with enough aircraft who's
		BR_B_HURRONLY	=0x0000E,		//leader is already in the air
		BR_B_ANYRAF		=0x0000F,		//
		BR_B_LEADOPTNL	=0x00008,		//leader optional: This should only be applied to 1,2,3 aircraft
		BR_B_ALLOWGRP11	=0x00004,
		BR_B_EITHERWL_ALLOW11 = 0x00007,
		BR_B_EITHERWL	=0x00003,	//The leader must be on the ground for these
		BR_B_SPITWL		=0x00001,	//spitfire with leader but not from 11 group. This is to support the ACE option primarily,
		BR_B_HURRWL		=0x00002,	//but should also be used for 6,9, or 12 aircraft requests.
		BR_B_SPITTEST	=0x00001,	//spitfire with leader but not from 11 group. This is to support the ACE option primarily,
		BR_B_HURRTEST	=0x00002,	//but should also be used for 6,9, or 12 aircraft requests.
		//bit=8 is spare...

		BR_R_ANYFIGHTER	=0x00030,
		BR_R_109FONLY	=0x00010,		//Only select 109s
		BR_R_110FONLY	=0x00020,		//Only select 110s

		BR_R_ASTRAFE	=0x00040,	//When set up the attached group can straffe
		BR_R_DSTRAFE	=0x00080,	//When set up the detached group can straffe

		BR_R_FREACHTARG	=0x00100,	//When set up the escort will reach the target

		BR_R_ANYBOMB	=0x0fC00,	//Allow anything that can bomb
		BR_R_REALBOMB	=0x0f800,	//Except 110s

		BR_R_DIVEBOMB	=0x00C00,	//Any dive bomber
		BR_R_110BONLY	=0x00400,
		BR_R_JU87ONLY	=0x00800,

		BR_R_FLATBOMB	=0x0f000,
		BR_R_HE111ONLY	=0x02000,
		BR_R_DO17ONLY	=0x04000,
		BR_R_JU88ONLY	=0x08000,
	};

	enum	RaidNumEntryCounts
	{
		RNEC_RAF=2,
		RNEC_MAXLWBOMBERS=MAX_TARGETS,
		RNEC_LWCLOSEESCORT=MAX_TARGETS,
		RNEC_LWDETACHED_M1=MAX_TARGETS,
		RNEC_LWRETURNESCORT=MAX_TARGETS+AM_PASTDETACHED-AM_DETACHED,
		RNEC_LWMAXBLANKEEND,
		RNEC_LWMAXREQ,

		RNEC_LISTVALISLASTREC=255, //put in	squadliststart field
	};
		enum	SubMethod
		{
			SM_ANYA2A,
			SM_NOTBOMBERS=1,
			SM_NOTFIGHTERS=2,
			SM_ACCHOICE = 3,	//3 is not valid because it means there is nothing to attack
			SM_DOSTRAFFEGROUND=4,

			SM_ATTACKMETHODUNDEFINED = 0,
			SM_DIVEANDZOOM = 8,
			SM_HEADON = 16,
			SM_LINEABREAST = 24,
			SM_LINEASTERN = 32,
			SM_VIC = 40,
			SM_INDIVIDUAL = 48,
			SM_ATTACKMETHODSALL = 56,
			SM_RETURN_ESCORT=64,
			SM_109RETURNING=128,
		};
	struct	SquadSetFormType;
	struct 	Squad
	{	//This information is duplicated inside the info_airgroup
		ONLYFIELD(UWord,UniqueID,		instance);
		ONLYFIELD(UByte,SquadNum,		squadnum);		//info_airgroup::squadron
		SByte		targetindex;	//associated with a waypoint on route	//CSB 24/05/00

		ONLYFIELD(UWord,	FormationTypeIndex,formtype);		//o36s02
		ONLYFIELD(UByte,AttackMethod,	method);
		ONLYFIELD(UByte,SubMethod,		submethod);

		int		takeofftime;		//not transmitted - converted to position
		int		lastwptime;
		int		fuelleft;
		ONLYFIELD(UWord,UniqueID,takeoffwp);
		ONLYFIELD(UWord,UniqueID,landingwp);
		union
		{
#pragma warning( disable : 4201)
			struct
			{	//these are max 15
#pragma warning( disable : 4201)
				ULong	numacoriginal:4,			//Unchanged from launch
						numacleft:4,				//Left+ditched=original
						numacditched:4,
						numacrecoveredlow:4,		//these don't go in ditched or reduce left 
						numacrecoveredmed:4,		//recoveredmed+recoveredbad+pilotslost<=ditched
						numacrecoveredbad:4,		
						numpilotslost:4,
						leaderlost:1,

						playercansee:1,			//these bools are to give the RAF poorer info
						squaddetected:1,
						squadintercepted:1;		//this is to allow the RAF a later auto intercept.
			};
			ULong	numbers;		//savedata shortcut
		};
 		ULong	diaryentry;
		ONLYFIELD(UByte,PackageStatus,status);
		UByte		fightperiods;

		UByte	filler[2];

		int		WaveNum()	{return targetindex;}	//was if (method>=AM_DETACHED) return -1; else	//JIM 30/05/00
		UniqueID	SetSquad(SquadNum);	//returns new homebase to make package homebase easy to modify.
		void	Clear();	//clear out a slot.
		void	SetStatus(PackageStatus);
		int	FixTakeOffTime(int absrvtime,int rvtime);
		int	KillSome(int howmanytokill,Squad& killer);
		void	ApplyDiaryLosses(int moreslots);
		void	ApplyFlyingLosses(int acbitslaunched);
		void	SendHome();

		::Squadron&	Squadron();
		SquadSetFormType& FormType()	{return *(SquadSetFormType*)this;}
	};
	struct	SquadSetFormType:Squad
	{
		operator FormationTypeIndex()	{return formtype;}
		void	operator=(FormationTypeIndex);
	};
	struct	SquadListRef	
	{	//Pretends to be pointer to an array of Squad (above)
		SquadList*	pointer;
		Squad&		Squadron(int);
		Squad&		operator[](int i) {return Squadron(i);}
// 		operator 	SquadList*();
		int			Max();
		operator	int()	{return Max();}
//DEADCODE DAW 26/01/00 		operator	++();
 		Free();
		Squad*		Find(int	squadnum);
		bool		AllInStatus(PackageStatus);
		bool		AnyInStatus(PackageStatus);
		bool		AnyMainInStatus(PackageStatus);
		bool		AllMainInStatus(PackageStatus);
//DeadCode MS 26Sep00 		void		FixPackageStatus();
		int			AcBitsFirstSquad();
		int			AcBitsSquad(int index);
		bool		SetAcBitsFirstSquad(int pattern);
		Squad*		InsertEnd(UniqueID);
		Squad*		operator	+=(UniqueID u)	{return InsertEnd(u);}
		void	DeleteAll();
	};

	Squad*		InsertSquadAt(int,UniqueID);
	void		DeleteSquadAt(int);
	void		SwapNeighborSquadsAt(int lowerneighbor);
	enum	{	UNDETECTED=0,	EYE=1, NOWLOST=2,
				ACCONTACTBASE=64,
				CHBASE=128,
				CLBASE=192
			};
 	struct	RaidNumEntry
 	{
					
 		UWord	raidnum;			//Initially 0=not detected
 		UByte	squadliststart;
 		UByte	detector;		//0=undetected,1=eye,64-127=RAF a/c
 								//128-191=chhigh,192-255=chlow
		union
		{
			ULong	alertlevel;	//stop repeating alert messages
			struct
			{
		 		UByte	detectlatency;	//256 seconds is 4 minutes
				UByte	raidintercepted:1;
				UByte	cantfindsaid:4;
			};
		};
		ULong	firstsquaddiaryentry;
		Coords3D	prevpositions[4];  //USING Y FOR TIME!!!!

		RaidNumEntry()	{alertlevel=detector=0;}
	};
 	RaidNumEntry*	raidnumentries;	
	ULong	firstsquaddiaryentry;
					//max 13: 10 bomber targs + close,high,return escort. 
	int	RaidNumEntriesMinSq(int entry)	{return raidnumentries[entry].squadliststart;}
	int	RaidNumEntriesMaxSq(int entry);	//this is more complicated
	SquadListRef		squadlist;	//Pointer to array of Squad
	Squad&		operator[](int i)	{return squadlist[i];}

//DEADCODE DAW 25/11/99 	enum	WaveSplitting	{WS_SINGLE_PRIMARY};

//DEADCODE AMM 12/01/00 	char		packname[MAX_TARGETS];		//basis of file-name, probably
	union
	{
		int	flags;
		struct
		{
//DeadCode JIM 25Oct00 			bool		redo:1;
//DeadCode JIM 25Oct00 			bool		edited:1;
			bool		break109:1;
			bool		packagehasbeenintercepted:1;
			UByte		cancelsquad;	//SQ_ZERO==>OK SQ_MAX==>ALL
			UWord		wpsused;
		};
	};
//DeadCode JIM 25Oct00 	int			wpsused;
//DEADCODE DAW 24/11/99 	DutyType	duty;
	UniqueID	packagetakeoff;
	struct	TargetDesc
	{
		ONLYFIELD(UWord,UniqueID,		currentid);
		ONLYFIELD(UWord,UniqueID,		targetwaypoint);
		ONLYFIELD(UWord,UniqueID,		SGT);
		ONLYFIELD(UWord,UniqueIDBand,	band);
		UWord		bandoff;
		operator UniqueID()		{return currentid;}
		bool operator!=(UniqueID u)	{return currentid!=u;}
		bool operator==(UniqueID u)	{return currentid==u;}
		void operator =(UniqueID u);	//splits SGT info out.
		operator int()		{return currentid;}
		operator bool()		{return SGT!=NULL;}
		bool operator !()	{return SGT==NULL;}
		void	SetTargetFromSGTBandOff();
		void	SetSGTBandOffFromTarget();
	};
	TargetDesc	packagetarget[MAX_TARGETS];	//this is the overview target
//	UniqueID	regrouploc;		//everyone flys to the same egress
	UniqueID	doglegloc;		//everyone flys to the same dogleg
								//either east coast or west coast
								//bf route can delta from this default
	UniqueID			route;

	int				primarytargetETA;		//original setup time
	int				playerETAdelta;	//mod made by player without moving waypoint
	AttackMethod	attackmethod;		//fighter/bomber/dive
 	PackageStatus	packagestatus;
//////////////////////////////////
	bool	SetPredictedPointFromETA(SavedGlobrefs faketo=SGR_Pack_BlankZero,bool recalcfromETA=false);
//DEADCODE AMM 12/01/00 	FileNum		loadedbf;
	UniqueID	MakePrimaryRoute(int Y);
	void	RecalcRoutePositions();
	void	RecalcRoutePositionsAndTime();
	int	CalcRoutePositionsAndTime(int preferredtime = 0,SavedGlobrefs faketo=SGR_Pack_BlankZero,bool allowETArecalc=true);
	int	CalcRoutePositionsAndTime(int preferredtime,bool allowETArecalc)
	{	return	CalcRoutePositionsAndTime(preferredtime, SGR_Pack_BlankZero,allowETArecalc);	}


	void	ResetPatrolItems();
	void	SetTargetGlobrefs(bool fixconvoys=false);
	void	RecalcPrimaryPositions();
	void	ApplyDiaryLosses();
	void	FixPackageStatus();
	void	SetGlobRefsForRoute(UniqueID wpuid);
	void	RepositionSubWaypoints(UniqueID wpuid);
	bool	Profile::Remove109ReturnWP();
	bool	Insert109ReturnWP(int distbackcm);
	bool	RemoveOverExtendedFlights();
public:
//DEADCODE DAW 21/02/00 	int		FindSpareGlobref();

	SquadNum	AddSquadron(int numac,Profile::AttackMethod duty,SquadNum sn)	;
	SquadNum	AddSquadron(int numac,Profile::AttackMethod duty,int targnum,BetterRule br,SquadNum after=(SquadNum)0);
	SquadNum	AddSquadron(int numac,Profile::AttackMethod duty,int targnum,SquadNum sn);
//DEADCODE JIM 31/03/00 	void	ModifyRoute(int wavenum,int	groupnum,int	acnum);
//DEADCODE JIM 31/03/00 	void	ModifyPatrolRoute(int wavenum,int	groupnum,int	acnum);
//DEADCODE JIM 31/03/00 	void	SetACTypesFromGeneric();
	static	UniqueID MakeInterceptWP(SavedGlobrefs a,SavedGlobrefs b,int percent,UniqueID next,SavedGlobrefs as=(SavedGlobrefs)-1,int relalt=0,BFieldWaypointActions action=wpacnoactionno);
	static	UniqueID MakeInterceptWP(SavedGlobrefs a,SavedGlobrefs b,Ranges distance,UniqueID next,SavedGlobrefs as=(SavedGlobrefs)-1,int deltaalt=0,BFieldWaypointActions action=wpacnoactionno);
	static int	CalcTime(COORDS3D* last,const COORDS3D* wp,int type, int esctype, SWord StoresDrag);							//CSB 18/06/99	

	static int	ValidateTime(CString* buffer, int packnum, int wavenum);

	static int	CalcFuel(COORDS3D* last,const COORDS3D* wp,int escorteetype,int escortertype, SWord StoresDrag);	//CSB 18/06/99	
	bool CalcWPTimes();
	void	CalcRangeBrgFromPrev(UniqueID wpuid, ULong& range, ULong& brg);
	int FindEarliestPrimaryTargetETA(int& absrvtime, int& slowestsq);
	int FindEarliestPrimaryTargetETA(int targettime);
	void CalcWPRelTimes(int sqnum, int& targettime, int& rvtime);
	int CalcWPAbsTimes(int absrvtime, int slowestsq);

	bool CalcFuel(int sqnum,  UniqueID wpuid, int& reqfueltime, int& fueltime);	
	bool CalcFuel(int sqnum, int trgnum,  UniqueID wpuid, int& reqfueltime, int& fueltime);	
	Float Calc109FuelShortCut(int sqnum);	
	SquadNum CalcFuel(UniqueID uid, int& strikereqfueltime, int& escortreqfueltime,bool usetargets=true);	
	static	bool Profile::NonLeadElementSet(int applyflight, int applyelt);

	static	Float RelDensity(SLong alt);

	static int CalcHoriAndClimbTime(const struct COORDS3D * last,const struct COORDS3D * wp,SLong& horitime,SLong& climbtime,int type, int esctype, SWord StoresDrag);	//CSB 18/06/99
	static	bool GetPackageFromWP(UniqueID req_wpuid,int& pack,int& squad=*(int*)NULL,int& target=*(int*)NULL);
	static	int Profile::WPType(UniqueID u);

	int		DecodePackage(string packstr,bool decodebinary); //returns num flights. -ve if other targets
	void	SetTargetUIDs(bool	fixconvoys=false);
	int		CountWaypoints();
//DeadCode RDH 16Mar100 	bool	GetKeyTargetWPs(UniqueID& targetarea,UniqueID& firststartpatrolbomb,UniqueID& laststartpatrolbomb,UniqueID& firstendpatrol,UniqueID& lastendpatrol,UniqueID& regrouparea);
#ifdef	RANGES_Included
	UniqueID	AddAttackWP(int targetnum,Profile::AttackMethod duty,int alt=METRES3000);
#endif
	UniqueID	MakeWayPoints(int targetnum,int squadinpack,Profile::AttackMethod duty,SquadNum sq);
//DEADCODE DAW 14/03/00 	bool	GetKeyTargetWPs(UniqueID& targetarea,UniqueID& firststartpatrolbomb,UniqueID& laststartpatrolbomb,UniqueID& firstendpatrol,UniqueID& lastendpatrol,UniqueID& regrouparea);
	bool	GetKeyMainWPs(UniqueID& firsttakeoff,UniqueID &takeoffarea,UniqueID& targetarea,UniqueID& regrouparea,UniqueID& landingarea,UniqueID& lastlanding);
	static UniqueID	FindSquadWpBetween(UniqueID wp1,UniqueID wp2,int group);
	static UniqueID	FindSquadWpAfter(UniqueID wp1,UniqueID wp2,int group);
	static UniqueID	FindTargetWpBetween(UniqueID wp1,UniqueID wp2,SavedGlobrefs targnum);
	static UniqueID	FindTargetWpAfter(UniqueID wp1,UniqueID wp2,SavedGlobrefs targnum);
	static void		RemoveWpBetween(UniqueID&wp1,UniqueID&wp2,UniqueID wptoremove);
#ifdef	RANGES_Included
	static UniqueID	InsertWpBetween(UniqueID&wp1,UniqueID&wp2,SavedGlobrefs targ,	BFieldWaypointActions a,int group,int wave,UniqueID targuid=UID_NULL,SavedGlobrefs setgr=SGR_Pack_BlankZero,int alt=METRES3000);
	static UniqueID	InsertWpBetween(UniqueID&wp1,UniqueID&wp2,UniqueID targ,		BFieldWaypointActions a,int group,int wave,SavedGlobrefs setgr=SGR_Pack_BlankZero,int alt=METRES3000)
	{	return 	InsertWpBetween(wp1,wp2,SGR_Pack_BlankZero,a,group,wave,targ,setgr,alt);	}
#endif

	void	ReassignTo(UniqueID newtarget,bool immediate);
	void	ReturnHome();

	void	SquadComplete(int squadline);

	bool	StopFighting(int squadline,info_airgrp* a,bool forcehome=false); //returns true if destroyed
	void	PackageComplete();
	void	ApplyFlyingLossesDiary();

	int	AddNumerousSquadrons(int initialfarfighters,AttackMethod duty,SquadNum sq,BetterRule br,int* actypecounts=NULL);
#ifdef	RANGES_Included
	AttackMethodField	AddNumerousEscorts(int initialclosefighters,int initialfarfighters,int initialreturnfighters,Profile::BetterRule br,AttackMethodField am,int alt=METRES3000,int* actypecounts=NULL);
#endif
	void SetSubMethod(Profile::AttackMethod escorttype, Profile::SubMethod sm);
	void SetSubMethod(Profile::AttackMethod escorttype, FormationTypeIndex formation);
	void SetSubMethod(PlaneTypeSelect actype, Profile::SubMethod sm,FormationTypeIndex formation);
	int		AddTargetWaypoints(int numtargets,bool patrol);
	void	AddNumerousEscorts(int initialclosefighters,int initialfarfighters=0,int initialreturnfighters=0,Profile::BetterRule br=Profile::BR_NONE,int* actypecounts=NULL);
	AttackMethodField	FixCloseEscortPositions(AttackMethod escorttype,AttackMethodField amf);
	AttackMethodField	FixRAFPositions(AttackMethod escorttype,AttackMethodField amf);
	AttackMethodField	FixIndipendentPositions(AttackMethod flyingmethod,AttackMethodField amf);
	int	RemakeRaidList(bool splitbombers,bool splitfighters);
	int	RecostRaidList();
	AttackMethodField	ReorderPackage(AttackMethodField amf);
	UniqueID	FixTakeOffUID();
	int		GetRaidIndFromSquadEntry(int sqentry);
	int		CountRaid(int squadentry);
	bool	GetACSquadEntry(UniqueID ac,int&sq);
	UniqueID	SquadTarget(int squadline)	{return packagetarget[squadlist[squadline].targetindex];}
	static void	MoveSAGs();
	bool UnitIsFighter(int j, bool me110isbomber);
	bool UnitIsBomber(int j, bool me110isbomber);
	bool SqIsAvail(int j, bool acisfighter, bool me110isbomber);
	bool	StraffRequired(int attackmethod);
	int		FindAttackMethod(PlaneTypeSelect actype);
	int		FindPreferredTarget(PlaneTypeSelect actype);
	void	DeleteNumerousSquadrons(Profile::AttackMethod attackmethod, int delsq =100);
	void	DeleteNumerousSquadrons(BetterRule	br, int delsq=100);
	int		FirstSquadofMethod(Profile::AttackMethod attackmethod);
	int		FirstSquadNotofMethod(Profile::AttackMethod attackmethod);
	void	CompleteSquadron(Profile::AttackMethod attackmethod);	
	void	CompleteGroup(Profile::AttackMethod attackmethod, int currsquads);
	void	ResetAcNumbers(Profile::AttackMethod attackmethod, int orggrp, int reqgrp, int deltaac);
	void	RAFResetAcNumbers(Profile::BetterRule betterrule, int orgsq, int reqsq, int newnumac);
	BetterRule	 FindBetterRule();
	BetterRule	 RAFFindBetterRule();
	bool	IncreaseSubSquadronToSquadron(Profile::AttackMethod attackmethod);
	void	Profile::ChangeStrikeAcType(int actype);
	void	ShareSecondaries(UniqueID* u,int alt);	//copies table and sets number
	void	ShareSecondaries(int numsec);			//devides evenly between number
	void	ReShareSecondaries();					//gets current number of targets
	AttackMethodField	ScanAttackMethods();
	void	SaveAirItemBin(Profile::Squad* squad,UniqueID route,BOStream&file);
//DeadCode MS 28Oct00 		bool	StopFighting(int squadline,info_airgrp* a,bool forcehome=false); //returns true if destroyed
};
inline int	operator-(const Profile::Squad* entry,Profile::SquadListRef& base)
{
	int rv=entry-&base[0];
//	assert(rv>0 && rv<base.Max());
	return rv;
}
struct	PackageList
{
	Profile	pack[Profile::MAX_PACKS + 1];				//the top one is reserved for comms red
	bool		germanisauto;
	bool		britishisauto;
	int			nextraidnum,nextsortienum;
	Nationality	localplayer;
 	char	oldhipack, hipack, oldhisquad, hisquad;
	bool squelchfuelwarning;
	UniqueID	hiwp;
	Profile&	operator[](int i)	{return pack[i];}
//DeadCode JIM 24Sep00 	int			GetSpareSquad(Nationality n);
	void	BuildReorderTable(bool actuallyreorder=true);

	DES	~PackageList()	{WipeAll();}

	enum	{MAX_REORDERLOOKUP=512};
static 	UniqueID	ReorderLookup[MAX_REORDERLOOKUP];
static 	UniqueID	Reorder(UniqueID);
static 	UniqueID	ReorderNoCheck(UniqueID);
static	UniqueID	ReorderZero(UniqueID u);


	enum {STRIKEOPTIONS = 7, ESCORTOPTIONS =4};
	enum {NOTDEFINED = -1, MIXED = 255, FIGHTER=254, MAX_METHODS = 8};
	enum {DISPLAY_GESCHWADER,DISPLAY_GRUPPE, DISPLAY_STAFFEL};
	struct AMType
	{
		bool attackmethods[MAX_METHODS];
		int	acnum;
		int realacnum;
		int squadnum;
		ONLYFIELD(UWord,	FormationTypeIndex,formtype);
		int maxac;
		int maxsquad;
		int squadtype;

	};
	struct TaskData
	{
		int	targetnum;
		bool mixedstrikeset;
		bool mixedescortset;
		int	strikeactypes[STRIKEOPTIONS];
		int escortactypes[ESCORTOPTIONS];
		AMType strike;
		AMType attached;
		AMType detached;
		AMType returned;
		AMType totalfighter;
		int attackmethod;
	};
	TaskData	taskdata;	  //Should I be saving this or what?
	void		SetTaskData();
	bool			AcAvailable(AMType* amtype,int actype, int actype2,int& acnum, int& squadnum, bool includecommitted );
	void		SetRAFTaskData();
	bool		RAFAcAvailable(AMType* amtype,int actype, int actype2,int& acnum, int& squadnum, bool includecommitted);




	void	SaveGame(BOStream&);
	void	LoadGame(BIStream&);
	void	SaveBin();
	static	CString&	CSprintf(const char* format,...);
	static	void	SaveBin(Profile* p,BOStream& f);
	static	void	SaveRouteBin(UniqueID route,BOStream&file);
	static	void	SaveWaypointBin(info_waypoint* wp,BOStream&file);
//	char	plpack,plwave,plgrp,plac;					//player's slot
	int		NewPackage(UniqueID targ,Nationality nat, Profile::AttackMethod duty,int initialbombers=-1,Profile::BetterRule br=Profile::BR_WIDESTPOSSIBLE,int mainalt=0,int* actypecounts=NULL);
	bool	PackageHasBeenEdited();
//DEADCODE DAW 24/11/99 	void	ProfileFlightsRequired(int pack, int& mb, int& f80,int& f84,int& f51,int& fb,int& f, int& f86a, int& f86b, int& b26, int& b29); //RDH 16/03/99
//DEADCODE DAW 24/11/99 	void	FlightsAvailable(int pack, int& a_mb, int& a_f80,int& a_f84,int& a_f51,int& a_fb,int& a_f, 
//DEADCODE DAW 24/11/99 			int& a_f86a, int& a_f86b, int& a_b26, int& a_b29); //RDH 16/03/99

//DEADCODE DAW 24/11/99 	void	DeleteNonRedoPackages();
	int		FindPackage();
	static SquadNum		FindSquad(Profile::AttackMethod duty,UniqueID doglegloc,UniqueID targloc,int minavailac,Profile::BetterRule br=Profile::BR_WIDESTPOSSIBLE,SquadNum after=(SquadNum)0);
//DEADCODE AMM 12/01/00 	int		FindSquadExlMedBombers();
//DEADCODE DAW 24/11/99 	int		PackageList::CAPAircraftcnt();

//DEADCODE DAW 24/11/99 	void	SetWaveTimes(int p, int w,int targettime);	 //RDH 12/02/99
	void	UpDatePackageTimes();					 //RDH 12/02/99
	UniqueID	GetTakeOff(SquadNum);
	char*	RaidFormatString(int pack, int raid);
	int	FindNumSquadsInPack(int p);
	int	SquadronsPlanned(int nationality);
	int	BiggestRAFSquadronOnDay();
	bool LondonTargetted();
	bool ThousandAcRaid(int& escortratio2);
	bool TargetDamaged(int uidbandstart, int uidbandend);
	bool TargetDestroyed(int uidbandstart, int uidbandend);
	int TargetStatus(int uidbandstart, int uidbandend);
	void	SplitExistingResponsesTo(int packnum,int newraidind);

	bool	GetSquadEntry(SquadNum s,int&p,int&sq=*(int*)NULL);
	bool	GetACSquadEntry(UniqueID ac,int&p,int&sq=*(int*)NULL);
	enum	WPTargSpecials	{WPTS_NONE=-1,WPTS_MAINTAKEOFF=-2,WPTS_DOGLEG=-3,WPTS_LOCALTAKEOFF=-4};
	bool	GetWPTargEntry(UniqueID wp,int&p,int&trg=*(int*)NULL);	 
	bool	GetTargEntry(UniqueID t,int&p,int&trg=*(int*)NULL);

//DEADCODE DAW 24/11/99 	bool	GetSquadEntry(int p, int w, int g, int& squad, int& flight);
	bool	FlyableAircraftAvailable();
//DEADCODE DAW 25/11/99 	bool	PackageList::GetPackage(int& i, int& wave, int& group, int squad, int flight);
	UniqueID FindEgressPoint(UniqueID targ);

//DEADCODE JIM 13/01/00 	int	SquadACUsed(int squadnum);
//DEADCODE JIM 13/01/00 	int SquadACAvail(int squadnum);	//every squadron initially has 19 aircraftso they
	//rdh{return 19;}			//can lose 3 aircraft before dropping to 3 flights
							//If Mark really wants restocking then I suggest 
							//setting a restocking max of 17 so you are fighting 
	bool	PreLoad(int packnum,FileNum fil=FIL_NULL,const char* filename=NULL,bool copyprimary=false,bool copysecondaries=false,int	filecount=0);
	void	Load(int packnum,FileNum fil=FIL_NULL,const char* filename=NULL,int filecount=0);
	void	FixupAircraft(int packnum);	//post load
	void	WipeAll();
	void	ClearPack(int pack);
	void	DeletePack(int p);

	void	ShuntPack(int pack);
	void	PackagePrepareForFrag();							//AMM 17Nov98

	int		MaxWaypoints()		{return	550;}
	int		UsedWaypoints();
	bool	CanAddMoreWaypoints(int	packnum);
	static	int	GetSquadACCountFromGrupp(int requested,int duty)
	{return (GetSquadACCountFromGrupp(requested,requested,duty));}
	static	int	GetSquadACCountFromGrupp(int requested,int available,int duty);
	void	IsPlayerUsedInDirectives();
	void	InvalidateRoute(Profile*,bool iconsaswell=false,bool squadsaswell=false);
	void	InvalidateIcon(UniqueID ac);
	void	ChangeMessagesUID(UniqueID old,int newid);
	void	SetVisibilityFlags();
	void	AllVisibilityUpdated();
	bool	RouteAtAllVisible(int pack);
	Profile::PackageStatus	FindBestResponseStatus(int pack,int squad);
	bool	CheckHilightValid();   //returns true if hilight was changed
	void	MessageBoxFuelWarning(SquadNum sq);
	void	MessageBoxFuelWarning(int package);
	int		HandleLaterEvents();
};
extern	PackageList	Todays_Packages;
#endif
