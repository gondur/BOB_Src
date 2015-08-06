//------------------------------------------------------------------------------
//Filename       sqddiary.h
//System         
//Author         Robert Slater
//Date           Mon 24 Jan 2000
//Description    
//------------------------------------------------------------------------------
#ifndef	SQDDIARY_Included
#define	SQDDIARY_Included

#define	DEFAULT_SQDDIARY 0


// Raid Pack....


enum		MissResult	
{
	MR_NULL=0,
	MR_PATROLUNEVENTFUL,	//German free escorts will set these
	MR_INTERCEPTMISSED,		//RAF fighters will print them
	MR_ENGAGEDGOODRES,
	MR_ENGAGEDMEDRES,
	MR_ENGAGEDBADRES,
	MR_LOSTAPPRTARG,		//German bombers will set these
	MR_LOSTLEAVETARG,
	MR_ABORTEDTARG,
	MR_ATTACKNODAMAGE,
	MR_ATTACKSLIGHTDAMAGE,
	MR_ATTACKSUCCESS,
	MR_RECONCOMPLETED,

	MR_MISSCOMPLETEFLAG=0x80	//If this is not flagged then don't report status!
};
enum		MissType	{MT_RAID,MT_RECON, MT_PATROL,MT_ESCORT,MT_CLOSEESCORT};

enum	InterceptDesc
{
	INT_UID_MASK = 0x0000FFFF,
	INT_UID_SHIFT = 0,
	INT_DIR_MASK = 0x000F0000,
	INT_DIR_SHIFT = 16,
	INT_RANGE_MASK = 0xFFF00000,
	INT_RANGE_SHIFT = 20
};

enum	DiaryDamage
{
	DIARY_LEFTWING=0,
	DIARY_RIGHTWING,
	DIARY_ENGINE,
	DIARY_TAIL,
	DIARY_CANOPY,
	DIARY_FUSELAGE,
	DIARY_MAXDAMAGE
};

const	UWord	DIARY_EMPTYINDEX = 0xFFFF;
const	ULong	GRUPPENMASK	= 0x40000000;
const	ULong	DIARYMASK	= GRUPPENMASK-1;

class	AirStruc;
class	BIStream;
class	BOStream;
class	MinAnimData;
class	ViewPoint;
class	CString;														//RJS 9Nov00

// Gruppen Record...

enum		LeadKilled	{LK_NONE,LK_1ST,LK_2ND,LK_OTHER};

class	SquadronBase
{
public:

	UByte		squadnum;	//
	UByte		numlosses;	// filled in when ac in this squadron is killed
	UByte		numacdamaged;	// filled in when ac in this squadron is damaged
	UByte		numpilotslost;	// if killed ac, not ejected
	LeadKilled	leaderkilled;	// if killed is leader, LK_1ST (formpos==0) or LK_OTHER (formpos!=0)
	UByte		noaclaunched;	//these count up to 40. 64 is 6 bits.

	void		Clear()
	{
		squadnum = 0;
//DeadCode RDH 21Feb100 		kills[0]=0;
//DeadCode RDH 21Feb100 		kills[1]=0;
		numlosses = 0;
		numacdamaged = 0;
		numpilotslost = 0;
		noaclaunched = 0;										//RDH 21Feb100
		leaderkilled = LK_NONE;
	}

	void	AddKilled(AirStruc*,const int&);							//RJS 21Sep00
	void	CreditClaim(PlaneTypeSelect pt,int number);
	void	AddDamage();
	void	AddEjected(AirStrucPtr,int);

	void	KillPilot();												//RJS 23Aug00
};



// Intercept record...



// Squadron Record...


// Player Record...

enum	EndFlightStatus
{
	EFS_NULL = 0,			//*			Uneventful.
	EFS_LandedOK,			// Craig	Safe landing.
	EFS_LandedOtherAF,		// Craig	Landed away from home.
	EFS_LandedField,		// Craig	Landed in a field.
	EFS_DitchedField,		// Craig	Aircraft ditched.
//DeadCode RJS 30Oct00 	EFS_BadCrashAF,			//* Craig 3d\transite.cpp (LandedEffect)	Survived a bad crash.
	EFS_ACLOST,				//*			Aircraft written off.
	EFS_KIA,				//*			Killed in action.
	EFS_BadCrashAF,			//Survived a bad crash.
	EFS_PILOTLOST,			//*			Fatal crash.
	EFS_Parachute,			//*			Baled out.
	EFS_BadCrashField = EFS_BadCrashAF		//* Craig
};


// Diary Master Control...
enum	DiaryOneDay
{
	D1DAY_PLAYER = 5,
	D1DAY_SQUAD = 35,
	D1DAY_GRUPPEN = 60,
	D1DAY_INTERCEPT = 30,
	D1DAY_RAIDGRP = 30,
	D1DAY_RAIDPACK = 15,
	D1DAY_PLAYERDESC = 512		//BYTES
};



struct	Profile;
struct	PackageList;
enum	SquadNum;



class	Diary
{
	enum	DSearchDir
	{
		DSEARCH_BACK, DSEARCH_FORWARD
	};

public:

	struct	Player
	{
		UWord			diarysquadindex;
		UByte			kills[6];	//see squadbase
//Dead		bool			isGruppen;
		EndFlightStatus	howendedmission;	//log when player ends mission... like mig  *
		UByte			specificdamage[DIARY_MAXDAMAGE];	// copy of damage anim data *
		UWord			descriptionstringindex;
		ULong			flyingcs;
		void	Tick(int cs)	{flyingcs+=cs;}
		Player()
		{
			Clear();
		}

		void	Clear()
		{
			diarysquadindex = DIARY_EMPTYINDEX;
			descriptionstringindex = DIARY_EMPTYINDEX;
			for (int i=0;i<DIARY_MAXDAMAGE;i++)	specificdamage[i]=0;
			kills[0]=kills[1]=kills[2]=kills[3]=kills[4]=kills[5]=0;
			howendedmission = EFS_NULL;
			flyingcs=0;
		}

		void	DamageReport(CString&);									//RJS 9Nov00

	};

	struct	Intercept
	{
		UWord	diaryraidindex;
		bool	waspatrolinitially;	//set when patrol
		bool	leadthere;	//AcIndexFirstSquad() -> lowest number ac in 1st squad. (if more than 1 squad, returns 0) 
										//if returns <> 0 , leader is not there (so leader can't be killed!)
		ULong	takeofftime;		//copy from raid								*
		ULong	intercepttime;		//at point of intercept (Craig?)
		ULong	interceptloc;		//... radio message index (may need 2 fields)
		ULong	interceptheight;	//... World.Y						//RJS 18Oct00
		UWord	firstsquadronrec;

		Intercept()
		{
			Clear();
		}

		void	Clear()
		{
			diaryraidindex = DIARY_EMPTYINDEX;
			leadthere = false;
			takeofftime = 0;
			waspatrolinitially = false;
			intercepttime = 0;
			interceptloc = 0;
			interceptheight = 0;
			firstsquadronrec = DIARY_EMPTYINDEX;
		}
	};

	class	Gruppen : public SquadronBase
	{
	public:

		UWord		diaryraidgroupindex;
		UByte		kills[3];									//RDH 21Feb100
//DeadCode RJS 23Feb00		UByte		pad;

		Gruppen()
		{
			Clear();
		}

		void	Clear()
		{
			diaryraidgroupindex = DIARY_EMPTYINDEX;
//DeadCode RDH 21Feb100 			noaclaunched = 0;
			kills[0]=0;											//RDH 21Feb100
			kills[1]=0;											//RDH 21Feb100
			kills[2]=0;											//RDH 21Feb100

			((SquadronBase*)this)->Clear();
		}
	};

	class	Squadron : public SquadronBase
	{
	public:

		UWord		diaryinterceptindex;
		UByte		kills[6];									//RJS 23Feb00
		ULong		landingtime;										//RJS 24Oct00
		FIRSTFIELD(UWord,	UniqueID,	takeoffairfield,	13);	//if transfer, holds new airfield
		LASTFIELD(			bool,		wastransfer,		14,14);

		Squadron()
		{
			Clear();
		}

		void	Clear()
		{
			diaryinterceptindex = DIARY_EMPTYINDEX;
			wastransfer = false;
			landingtime = 0;
			takeoffairfield = UID_NULL;
			kills[0]=0;											//RDH 21Feb00
			kills[1]=0;											//RDH 21Feb00
			kills[2]=0;											//RDH 21Feb00
			kills[3]=0;											//RDH 21Feb00
			kills[4]=0;											//RDH 21Feb00
			kills[5]=0;											//RDH 21Feb00


			((SquadronBase*)this)->Clear();
		}
	};

	struct RaidPack
	{
		UWord		date;//day no.	//missman campaign (long in seconds by secs/day)currdate *
		ULong		takeofftime;		// secs... again, from missman::currtime				*
		ULong		dispersetime;	//fill when dispersed... mapscreen, on wp action(disperse)
		UWord		doglegpos;		//profile												*
		UWord		firstraidgrouprec;
		UWord		firstinterceptrec;

		RaidPack()
		{
			Clear();
		}

		void	Clear()
		{
			date = 0;
			takeofftime = 0;
			dispersetime = 0;
			doglegpos = 0;
			firstraidgrouprec = DIARY_EMPTYINDEX;
			firstinterceptrec = DIARY_EMPTYINDEX;
		}
	};

	struct	RaidGroup
	{
		UWord		diaryraidpackindex;
		ULong		targettime;	//timetoreachtarget (playerETAdelta+primarytargetETA)	* modify when we reach target?
		UniqueID	target;		//uid target entry										*
		UWord		attackheight;	//find wp from target, get world.y (metres)	<- fill when we reach the target
		MissType	misstype;		//squad attack method Squad::method					*
		MissResult	missresult;		//for all collisions by weapons, look at uid of hitter (damage.cpp)
		UWord		firstgruppenrec;

		RaidGroup()
		{
			Clear();
		}

		void	Clear()
		{
			diaryraidpackindex = DIARY_EMPTYINDEX;
			targettime = 0;
			target = (UniqueID)0;
			attackheight = 0;
			missresult = MR_NULL;
			firstgruppenrec = DIARY_EMPTYINDEX;
		}
	};

	struct	Master
	{
		Player*	playertable;
		int				playertablenext;
		int				playertablemax;
		Squadron*	squadtable;
		int				squadtablenext;
		int				squadtablemax;
		Intercept*	intercepttable;
		int				intercepttablenext;
		int				intercepttablemax;
		Gruppen*	gruppentable;
		int				gruppentablenext;
		int				gruppentablemax;
		RaidPack*	raidpacktable;
		int				raidpacknext;
		int				raidpackmax;
		RaidGroup*	raidgrouptable;
		int				raidgroupnext;
		int				raidgroupmax;
		char*			playerdescspace;
		int				prevplayerdesc;
		int				nextplayerdesc;
		int				maxplayerdesc;

		bool			playerIsGruppen;

		Master()
		{
			playertable = NULL;
			squadtable = NULL;
			gruppentable = NULL;
			raidpacktable = NULL;
			raidgrouptable = NULL;
			playerdescspace = NULL;
			intercepttable = NULL;

			playerIsGruppen = false;

			Clear();
		}

		~Master()
		{
			Clear();
		}

		void	Clear()
		{
			delete [] playertable;
			delete [] squadtable;
			delete [] gruppentable;
			delete [] raidpacktable;
			delete [] raidgrouptable;
			delete [] playerdescspace;
			delete [] intercepttable;

			playertable = NULL;
			squadtable = NULL;
			gruppentable = NULL;
			raidpacktable = NULL;
			raidgrouptable = NULL;
			playerdescspace = NULL;
			intercepttable = NULL;

			playertablenext =
				squadtablenext =
				intercepttablenext =
				gruppentablenext =
				raidpacknext = 
				raidgroupnext = -1;
				
			prevplayerdesc =
				nextplayerdesc = -D1DAY_PLAYERDESC;

			playertablemax =
				squadtablemax = 
				intercepttablemax =
				gruppentablemax =
				raidpackmax =
				raidgroupmax =
				maxplayerdesc = 0;
		}
	};

private:

	bool			isQuickMission;												//RJS 9Nov00
	EndFlightStatus	lastplayerstatus;
	Master	*diaryptr;
	AirStruc*		current_ac;
	ULong			current_itemstate;
	SLong			current_depth;
	ViewPoint*		vp;
	int				toBeKilled;											//RJS 4Sep00
	int				current_pilotcount;									//RJS 21Sep00
	int				trainingReport;										//RJS 30Oct00
	animptr			current_adptr;										//RJS 3Nov00

	void	NewDay_RaidPack();
	void	NewDay_RaidGroup();
	void	NewDay_Gruppen();
	void	NewDay_Intercept();
	void	NewDay_Squad();
	void	NewDay_Player();
	int		NewDay_Desc(int);

// Internal record creation...

	int		AllocatePlayer(SLong,bool);
	int		AllocateRaidPack();
	int		AllocateRaidGroup(SLong);
	int		AllocateIntercept(SLong,SLong);								//RJS 7Sep00
	int		AllocateIntercept(RaidGroup*,SLong);						//RJS 7Sep00
	bool	AllocateGruppen(SLong,UWord,ULong&);
	int		AllocateSquadron(SLong,SLong);						//RDH 21Feb00
	int		AllocateDesc();


// Internal navigation...

	SquadronBase*	GruppenSearch(SquadronBase*,UWord,DSearchDir sdir=DSEARCH_BACK);
	SquadronBase*	SquadronSearch(SquadronBase*,UWord,DSearchDir sdir=DSEARCH_BACK);
	int				TextBufferSize(Player*,int&);

// Stub...

	void	SetDisperseTime(SquadronBase*,int);							//RJS 7Sep00
	void	SetLandingTime(SquadronBase*,int);							//RJS 7Sep00

	void	NewSession();												//RJS 30Oct00


public:


	Diary()
	{
		current_pilotcount = 1;											//RJS 21Sep00
		current_depth = 0;
		current_ac = NULL;
		current_itemstate = 0;
		diaryptr = NULL;
		New();

	}

	~Diary()
	{
		delete diaryptr;
	}

	void			New();
	void			Load(BIStream&);
	void			Save(BOStream&);
	Diary::Player*	CreatePlayer(SquadronBase*);
	void			CreateEntry(PackageList&,SLong);
	void			CreateLWEntry(Profile*);
	void			CreateRAFEntry(Profile*,SLong);
	void			New3DSession();										//RJS 30Oct00
//DeadCode RJS 30Oct00 	{
//DeadCode RJS 30Oct00 		vp = NULL;
//DeadCode RJS 30Oct00 		current_depth = 0;
//DeadCode RJS 30Oct00 		current_ac = NULL;
//DeadCode RJS 30Oct00 		current_itemstate = 0;
//DeadCode RJS 30Oct00 		current_pilotcount = 1;											//RJS 21Sep00
//DeadCode RJS 30Oct00 
//DeadCode RJS 30Oct00 		trainingReport = 0;												//RJS 30Oct00
//DeadCode RJS 30Oct00 	}


// User Functions...

	SquadronBase*		FindLast(SquadNum);
	SquadronBase*		FindPrev(SquadronBase*);
	SquadronBase*		FindFirst(SquadNum);
	SquadronBase*		FindNext(SquadronBase*);
	
	Diary::RaidGroup*	GetRaidGroup(SquadronBase*);
	Diary::RaidPack*	GetRaidPack(RaidGroup*);

	Diary::RaidGroup*	GetFirstRaidGroup(RaidPack*);
	Diary::RaidGroup*	GetNextRaidGroup(RaidGroup*); 

	Diary::Intercept*	GetFirstIntercept(RaidGroup*);
	Diary::Intercept*	GetIntercept(SquadronBase*);
	Diary::Intercept*	GetNextIntercept(Intercept *); 

	Diary::Gruppen*		GetFirstSquadron(RaidGroup*);
	Diary::Squadron*	GetFirstSquadron(Intercept*);
	Diary::Gruppen*		GetNextSquadron(Gruppen*);
	Diary::Squadron*	GetNextSquadron(Squadron*);

	Diary::Player*		GetFirstPlayer(SquadronBase*);
	Diary::Player*		GetNextPlayerInSq(Player*);
	Diary::Player*		GetFirstPlayer();
	Diary::Player*		GetFirstPlayerInDay(int day);
	Diary::Player*		GetNextPlayerInDay(Player*);
	Diary::Player*		GetNextPlayerAll(Player*);
	Diary::Player*		GetFirstPlayerInRaid(SquadronBase*,RaidGroup*);	//RJS 9Nov00

	Diary::RaidPack*	GetFirstRaidPack(int date);				//RDH 21Feb00
	Diary::RaidPack*	GetNextPack(RaidPack*);					//RDH 21Feb00
	Diary::RaidGroup*	GetRaidGroup(Intercept*);				//RDH 21Feb00

	SquadronBase*		GetSquadron(Player*);
	SquadronBase*		GetDiaryPtr(ULong);

	char*		GetDiaryText(Player*);
	int			DiaryEditable(Player*);	//returns max length
	void		SetDiaryText(Player*,const char* externalcopy);

	void		UpdatePlayerLog(AirStruc*);
	void		UpdatePlayerLog(EndFlightStatus);

	void		CreateDailyRaidGroup(int date);					//RDH 21Feb00
	void		EmptyDiary();		//wipes the lot				//RDH 21Feb00
	void		CreateQuickEntry(ULong*,ULong*,ULong*,int,UWord);		//RJS 24Feb00

	void		ArrivedAtTarget(ULong, void*);							//RJS 4Sep00

	void		FillEndOfDayReport(Player*);					//RJS 29Oct00
	void		AddTrainingReport(const int&);					//RJS 30Oct00


// Invoked from the 3D...

	void		Enter3D(ViewPoint* thevp);
//DeadCode RJS 30Oct00 	{
//DeadCode RJS 30Oct00 		vp = thevp;
//DeadCode RJS 30Oct00 
//DeadCode RJS 30Oct00 		trainingReport = 0;												//RJS 30Oct00
//DeadCode RJS 30Oct00 	}

	void		SetAC(void*,animptr&);							//RJS 21Sep00
	void		UpdateACDamage();								//RJS 21Feb00
	void		AddKill(void*,AirStruc*);						//RJS 21Feb00
	void		ArrivedAtTarget(AirStruc*,void*);				//RJS 29Feb00
	void		RaidResult(AirStruc*,MissResult);				//RJS 23Feb00
	void		HitTarget(void*, void*, void*);
	void		CreateTransfer(void*);							//RJS 29Feb00
	void		SetLandingTime(SquadronBase*);					//RJS 29Feb00
	void		SetLandingTime(ULong entry);							//RJS 7Sep00
//DeadCode RJS 7Sep00 	{
//DeadCode RJS 7Sep00 		SquadronBase*	ptr;
//DeadCode RJS 7Sep00 		ULong			base = entry&DIARYMASK;
//DeadCode RJS 7Sep00 		if (entry & GRUPPENMASK)
//DeadCode RJS 7Sep00 			ptr = &diaryptr->gruppentable[base];
//DeadCode RJS 7Sep00 		else
//DeadCode RJS 7Sep00 			ptr = &diaryptr->squadtable[base];
//DeadCode RJS 7Sep00 
//DeadCode RJS 7Sep00 		SetLandingTime(ptr);
//DeadCode RJS 7Sep00 	}

	void		SetDisperseTime(SquadronBase*);					//RJS 29Feb00
	void		SetDisperseTime(ULong entry);					//RJS 29Feb00
//DeadCode RJS 7Sep00 	{
//DeadCode RJS 7Sep00 		SquadronBase*	ptr;
//DeadCode RJS 7Sep00 		ULong			base = entry&DIARYMASK;
//DeadCode RJS 7Sep00 		if (entry & GRUPPENMASK)
//DeadCode RJS 7Sep00 			ptr = &diaryptr->gruppentable[base];
//DeadCode RJS 7Sep00 		else
//DeadCode RJS 7Sep00 			ptr = &diaryptr->squadtable[base];
//DeadCode RJS 7Sep00 
//DeadCode RJS 7Sep00 		SetDisperseTime(ptr);
//DeadCode RJS 7Sep00 	}

	void	UpdateIntercept(Intercept*, ItemPtr, const int&);	//RJS 18May00

	void	SetACState(int);											//RJS 4Sep00
	void	SetKilledAC(void*,animptr&);								//RJS 21Sep00
	void	UpdateKilledAC();											//RJS 4Sep00

	void	GetMissResult(SquadronBase*,RaidGroup*, CString&);				//RJS 9Nov00


};

extern	Diary	Squad_Diary;

																		   

#endif
