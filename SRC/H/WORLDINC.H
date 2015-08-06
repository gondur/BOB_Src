//------------------------------------------------------------------------------
//Filename       worldinc.h
//System         
//Author         Paul.   
//Date           Thu 19 Oct 1995
//Description    
//------------------------------------------------------------------------------
#ifndef	WORLDINC_Included
#define	WORLDINC_Included
#include	"movement.h"										//RDH 19Feb96
#include	"myangles.h"
#include	"shapenum.g"										//JIM 31Oct95
#include	"uniqueid.h"										//JIM 31Oct95
#include	"flyinit.h"
#include	"bitcount.h"
#include	"modvec.h"
#define	DEFAULT_WORLDINC 0

struct	GunnerInfo												//RJS 11Oct00
{
	ShapeNum	theShape;
	SWord		eyeHdg;
	SWord		eyePitch;
};

typedef class Model* PMODEL;									//ARM 07Mar97
typedef class AcmModel* PACMMODEL;								//ARM 14May97
typedef class _instruments *PINSTRUMENTS;						//ARM 27Aug97

#ifndef	NDEBUG
void	DbgMemTest2(void*);
#endif

class	MinAnimData;

typedef	ULong	AnimFlagField;									//RJS 30Nov99
typedef	UWord	AnimSizeField;									//RJS 30Nov99

const	AnimSizeField	ANIM_NULL = 0;							//RJS 30Nov99
 
typedef	char	(MinAnimData::*Animfieldref);
typedef	char	(MinAnimData::*AFR);

enum TAKEOFFPOINT{														  //CSB 16/12/99
		TP_SQUADRONSTART,
		TP_SQUADRONTOUCHDOWN,
		TP_RUNWAYEND,
		TP_TAXI1,
		TP_TAXI2,
		TP_TAXI3,
		TP_SQUADRONTURN,
		TP_FLIGHTTURN,
		TP_ACPARK,
		TP_BOWSER1,
		TP_BOWSER2,
		TP_BOWSER3,
		TP_BOWSER4,
	};	
//FileItem - part of worldload - discarded
//

//DeadCode PD 12Oct95 typedef	UWord	shapeindx;

//DeadCode RJS 21Apr99 typedef	void	*animptr;
//Protected animdata stuff....
class	GrpMinAnimData;
class	SunAnimData;
class	ExplodeAnimData;
class	FireAnimData;
class	BalloonAnimData;
class	BarageAnimData;
class	TroopAnimData;
class	TrainAnimData;
class	BlokesAnimData;					
class	WeapAnimData;
class	MoveGunAnimData;
class	TwoGunAnimData;
class	AircraftAnimData;
class	PolyPitAnimData;
class	LauncherAnimData;
class	WindsocAnimData;
class	CloneAnimData;
class	FlareAnimData;
class	ParachuteAnimData;
class	ThugAnimData;
class	MissileAnimData;
class	DebrisAnimData;
class	SmokeTrailAnimData;
struct	Coords3DList;						
class	SimpleAircraftAnimData;									//RJS 17Nov99
class	BirdLauncherAnimData;									//RJS 01Dec99
class	BlastAnimData;											//RJS 13Dec99
class	animptr
{
	//This anim class has been re-written by
	//RJS .... 30 June 1999

	void*	ptr;
#ifndef	NDEBUG
	AnimFlagField	flags;			// up to 31 anim flags		//RJS 30Nov99
	AnimSizeField	size;			// size of anim data		//RJS 30Nov99
#endif
public:

	animptr()	
	{
		ptr=NULL;
#ifndef	NDEBUG
		size = 0;
		flags = 0;												//RJS 30Nov99
#endif
	}

	void	operator = (UByteP a){ptr = a;};
	UByte&	operator[] (int a);
	UByte&	operator[] (SWord a);
	UByte&	operator[] (UWord a);
	UByte&	operator[] (UByte a);
	Bool	operator == (void* a){if (ptr==a) return TRUE; return FALSE;}
	int		operator - (animptr& a);
	Bool	operator != (void* a){if (ptr!=a) return TRUE; return FALSE;}
	void	operator += (int a);
	void	operator ++ ();
	UByteP	operator & ();
	ULong	Offset(void*	a);
	inline void	SetItemState(const int);
	inline int	GetItemState();

#ifndef	NDEBUG
void	MemTest();
void	Delete()	{delete [](char*)ptr; ptr=NULL; size = 0; flags = 0;}
void	operator = (animptr& a){ptr = a.ptr; size = a.size; flags = a.flags;};
void	operator = (AnimSizeField a){size = UWord(a);if (a==0){ptr = NULL; flags=NULL;}};//RJS 01Dec99
void	operator = (AnimFlagField a){flags = ULong(a);if (a==0){ptr = NULL;size=0;}};//RJS 01Dec99

operator MinAnimData*();
operator GrpMinAnimData*();
operator SunAnimData*();
operator ExplodeAnimData*();
operator FireAnimData*();
operator BalloonAnimData*();
operator BarageAnimData*();
operator TroopAnimData*();
operator TrainAnimData*();
operator BlokesAnimData*();		
operator WeapAnimData*();
operator MoveGunAnimData*();
operator TwoGunAnimData*();
operator AircraftAnimData*();
operator PolyPitAnimData*();
operator LauncherAnimData*();
operator WindsocAnimData*();
operator CloneAnimData*();
operator FlareAnimData*();
operator ParachuteAnimData*();
operator ThugAnimData*();
operator MissileAnimData*();
operator DebrisAnimData*();
operator SmokeTrailAnimData*();
operator Coords3DList*();
operator void*();												//RJS 17Nov99
operator SimpleAircraftAnimData*();								//RJS 17Nov99
operator BirdLauncherAnimData*();								//RJS 01Dec99
operator BlastAnimData*();										//RJS 13Dec99
#else
void	Delete()	{delete [](char*)ptr; ptr=NULL;}
void	operator = (animptr& a){ptr = a.ptr;};
void	operator = (AnimSizeField a){if (a==0)ptr = NULL;};		//RJS 30Nov99
void	operator = (AnimFlagField a){if (a==0)ptr = NULL;};		//RJS 30Nov99

operator MinAnimData*(){return (MinAnimData*)ptr;}
operator GrpMinAnimData*(){return (GrpMinAnimData*)ptr;}
operator SunAnimData*(){return (SunAnimData*)ptr;}
operator ExplodeAnimData*(){return (ExplodeAnimData*)ptr;}
operator FireAnimData*(){return (FireAnimData*)ptr;}
operator BalloonAnimData*(){return (BalloonAnimData*)ptr;}
operator BarageAnimData*(){return (BarageAnimData*)ptr;}
operator TroopAnimData*(){return (TroopAnimData*)ptr;}
operator TrainAnimData*(){return (TrainAnimData*)ptr;}
operator BlokesAnimData*(){return (BlokesAnimData*)ptr;}
operator WeapAnimData*(){return (WeapAnimData*)ptr;}
operator MoveGunAnimData*(){return (MoveGunAnimData*)ptr;}
operator TwoGunAnimData*(){return (TwoGunAnimData*)ptr;}
operator AircraftAnimData*(){return (AircraftAnimData*)ptr;}
operator PolyPitAnimData*(){return (PolyPitAnimData*)ptr;}
operator LauncherAnimData*(){return (LauncherAnimData*)ptr;}
operator WindsocAnimData*(){return (WindsocAnimData*)ptr;}
operator CloneAnimData*(){return (CloneAnimData*)ptr;}
operator FlareAnimData*(){return (FlareAnimData*)ptr;}
operator ParachuteAnimData*(){return (ParachuteAnimData*)ptr;}
operator ThugAnimData*(){return (ThugAnimData*)ptr;}
operator MissileAnimData*(){return (MissileAnimData*)ptr;}
operator DebrisAnimData*(){return (DebrisAnimData*)ptr;}
operator SmokeTrailAnimData*(){return (SmokeTrailAnimData*)ptr;}
operator Coords3DList*(){return (Coords3DList*)ptr;}
operator void*(){return (void*)ptr;}							//RJS 17Nov99
operator SimpleAircraftAnimData*(){return (SimpleAircraftAnimData*)ptr;}//RJS 17Nov99
operator BirdLauncherAnimData*(){return (BirdLauncherAnimData*)ptr;}//RJS 01Dec99
operator BlastAnimData*(){return (BlastAnimData*)ptr;}			//RJS 13Dec99
#endif


};



typedef	struct WayPoint	*WayPointPtr;
typedef	FormationTypeIndex	FORMATIONDESC;
typedef	void	*msgptr;
struct	WEAPCLASS
{
	UWord	group,entry;
};
typedef	void	*CALLPTR;
typedef	void	*LIGHTS;
//DeadCode PD 20Feb96 typedef	void	*VIEWDEF;
typedef	void	*animrtnref;
typedef	void	*shpintrpptr;
typedef	void	*weapptr;
//DeadCode RJS 10Feb97 typedef	void	*detectrtnref;
//DeadCode RDH 19Feb96 typedef	ULong	ActionRtnRef;

struct	PlaneType;
typedef	PlaneType	*ClassPtr;

//DeadCode RDH 28Feb96 enum	DUTYDESC	{dummy_duty = 0,DUTY_ALIGN=255};
//moved to h\movement.h											//RDH 19Feb96
//DeadCode RDH 19Feb96 enum	MANOEUVRE	{MANOEUVRE_SELECT=0,MANOEUVRE_IMMELMAN,MANOEUVRE_LOOP,MANOEUVRE_BARREL,MANOEUVRE_STALL};
//
//Blues are aggressive friendly forces (do the killing)
//Reds are aggressive unfriendly forces (get killed)
//green are non-aggressive neutral forces (bugger 'em)
//amber are aggressive neutral forces (bugger me)
//DeadCode RDH 26Oct95 enum	CONTROLMODE	{AUTO = 0,MANUAL};
//MovedTo3ddefs.h DAW 28Nov95 enum	Obj3DType	{STATIC = 0, MOBILE};
//DeadCode PD 07Mar96 enum	SHAPETYPE	{DUMMY_TYPE = 0};
//TempCode DAW 28Nov95 typedef	Obj3DType	OBJ3DTYPE;


#define	TDXBASE	0
#define	TDZBASE	0

#define MAXNUMBEROFTRANSIENTS 64								//MGA 27Feb96

struct	UNIQUE_ID
			{
				FIRSTFIELD (UWord,UniqueID,count,13)
				BITFIELD(Bool,changed,14,14)
////				LASTFIELD(Bool,sector,15,15)
//DeadCode AMM 10Jun98 				LASTFIELD(Bool,deaded,	15,15)		//RJS 27Feb98

				LASTFIELD(Bool,commsmove,	15,15)				//AMM 10Jun98

//				UniqueID	count	:14;
//				UWord		changed	:1,
//							sector	:1;
#ifdef	TRACKBADASSIGNMENTS	
			operator=(UNIQUE_ID&);
#endif
			};

//struct	BRIEF_ID
//			{
//			 	short	int	count:12,
//							spare:4;
//			};

enum	ITEM_SIZE	{	ItemBaseSize,WayPointSize,	//this layout is intended
						ItemSize,					//to show the hierachy of
						HdgSize,					//ItemBase derived types.
						HPSize,
						RotatedSize,
						MovingSize,
						MobileSize,TransientSize,VIEWPOINTSIZE2,
						FormationSize,
						ShipSize,
						AirStrucSize,

						ITEMBASESIZE=0,WAYPOINTSIZE,//this layout is intended
						ITEMSIZE,					//to show the hierachy of
						HDGSIZE,					//ItemBase derived types.
						HPSIZE,
						ROTATEDSIZE,
						MOVINGSIZE,
						MOBILESIZE,TRANSIENTSIZE,VIEWPOINTSIZE,
						FORMATIONSIZE,
						SHIPSIZE,
						AIRSTRUCSIZE,


						ITEM_SIZE_ALIGN=255
						};

struct	ITEM_STATUS
{
	FIRSTFIELD	(UWord,	Bool,BlueLaunch,0)
		BITFIELD(Bool,ManLaunch,1,1)
		BITFIELD(Bool,Drawn,2,2)
		BITFIELD(ITEM_SIZE,size,3,7)
		BITFIELD(UByte,deadtime,8,12)
		BITFIELD(UByte,deadscale,13,14)
		LASTFIELD(Bool,deaded,15,15)	 						//AMM 10Jun98
//DeadCode AMM 10Jun98 		SPAREFIELD(15,15)

//	Bool		BlueLaunch:	1,
//				ManLaunch:	1,
//				Drawn:		1;
//	ITEM_SIZE	size:		5;
//	UByte		deadtime:	5,	//max=32
//				deadscale:	2;	//¬hours/2hours/days/weeks
//	ITEM_STATUS() {};

	ITEM_STATUS()
	{
#ifdef	__MSVC__
		overview_BlueLaunch.value=0;
#endif
	}
	ITEM_STATUS(Bool bl,Bool ml=FALSE,Bool d=FALSE,ITEM_SIZE is=ITEMBASESIZE,UByte dt=0,UByte ds=0)
	{
		BlueLaunch=bl;
		ManLaunch=ml;
		Drawn=d;
		size=is;
		deadtime=dt;
		deadscale=ds;
	}
#ifdef	TRACKBADASSIGNMENTS	
			operator=(ITEM_STATUS&);
#endif
};

inline ITEM_STATUS SetStatus(UByte dt,UByte ds) {ITEM_STATUS rv(TRUE,TRUE,TRUE,ITEMBASESIZE,dt,ds);return rv;};

			
//DeadCode JIM 06Nov96 typedef	struct	COORDS3D	{	SLong	X,Y,Z;	} Coords3D;
struct	EventLog
{
		enum		Stage											//RDH 01Dec96
				{	EMPTY,UNSEEN,SEENBYOTHERS,ATTACKEDBYOTHERS,
					SEENBYPLAYERS,HOSTILE,SPOTTEDDOGFIGHT,
					APPROACHED,ATTACKED,DAMAGED,KILLED,TAKEOFF,     //RDH 01Dec96
					BENTWING,FATALCRASH,CRASHLAND,CRASHLANDTOOFAST,
					LANDOK,LANDOKATHOME,MIDAIRCOLLISION,
					DAMAGEDSTATIC,DAMAGEDTRUCK,KILLEDSTATIC,KILLEDTRUCK,
					PARACHUTED,
				};                                               //RDH 01Dec96
	Stage	stage;
	EventLog()	{stage=UNSEEN;}

};
struct	EventLogPtr:EventLog
{
	EventLog* operator->()	{return this;}
	operator= (const int)	{;}
};
//DEADCODE DAW 08/03/00 typedef	EventLog	*EventLogPtr;

typedef Bool	TellLeader;										//DAW 30Jun96
enum	NextLeadAct		{NL_OnCourse,NL_CircleFlights,NL_CircleSingles,NL_Flights,NL_DoubleFlighs,NL_PrevRipple,NL_PrevDouble,NL_align=255};
enum	NextFollAct		{NF_PersonalThreat,NF_CircleSingle,NF_Single,NF_Double,NF_ReDouble,NF_align=255};
class	ItemBase		;
class	item			;
class	hdgitem			;
class	hpitem			;
class	rotitem			;
class	MovingItem		;
class	mobileitem		;
class	TransientItem	;
class	formationitem	;
class	shipitem		;
class	AirStruc		;
struct	info_itemS;
struct	info_base;
struct	info_waypoint;
struct	info_grndgrp;
struct	info_airgrp;

struct	SAGAirstruc;
struct	SAGairgrp;

//class	;
//class	;


typedef ItemBase		*ItemBasePtr;							//JIM 14Feb96
typedef item			Item,*ItemPtr,*itemptr;
typedef hdgitem			*HdgItemPtr;
typedef hpitem			*HpItemPtr;
typedef rotitem			*RotItemPtr;
typedef MovingItem		*MovingItemPtr;
typedef mobileitem		MobileItem,*MobileItemPtr;
typedef TransientItem	*TransientItemPtr;
typedef formationitem	FormationItem,*FormationItemPtr;
typedef shipitem		*ShipItemPtr;
typedef	AirStruc		*AirStrucPtr;


/////////////////////////////////
class	ItemBase//:public	TextBlockKnown
{
protected:
	ItemBase()	{Status.size=ItemBaseSize;(UWord&)uniqueID=(UWord&)Status=0;}//JIM 12Sep96
public:
	~ItemBase();
static	ULong	desposrange;
static	COORDS3D despos;										//RDH 27Feb96

static	bool	OverFrance(Coords3D&);									//RJS 18Sep00
	bool	OverFrance()												//RJS 18Sep00
	{																	//RJS 18Sep00
		return ItemBase::OverFrance(this->World);						//RJS 18Sep00
	}																	//RJS 18Sep00

	void	operator	delete(void*);
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
	UNIQUE_ID	uniqueID;	//o00s02//access with myitem->uniqueID.count
	ITEM_STATUS	Status;		//o02s02//access with myitem->Status.size
	COORDS3D	World;		//o04s0C//access with myitem->World.X

#ifndef NDEBUG
//#define _OLDWORLD														//CSB 7Aug00
#ifdef _OLDWORLD														//CSB 7Aug00
	COORDS3D OldWorld;													//CSB 7Aug00
	int		 OldSector;													//CSB 8Aug00
#endif																	//CSB 7Aug00
#endif

// Fix against "condition is always true"
#ifdef __WATCOMC__
#pragma warning	690	6
#endif
#ifdef	worldincassert
	#undef	worldincassert
#endif

#if !defined(NOWORLDINCASSERT) && defined(__MSVC__)
#if !defined(NDEBUG) && defined(GOTASSERT)
	#define	worldincassert
#else

#endif
#endif
#ifdef	__BCPLUSPLUS__
#define	__forceinline
#endif
__forceinline	ItemBase& operator*()	
		{return *this;}
__forceinline	ItemBase* operator->()	
		{return this;}
__forceinline	operator bool()
		{return this!=NULL;}
__forceinline	bool	operator !()
		{return this==NULL;}
__forceinline 	operator	ItemBase* ()
		{return(ItemBase*) (this);}

#ifndef	worldincassert
__forceinline 	operator	item* ()	  	{
	 			return(item*) (this);	}
__forceinline 	operator	WayPoint* ()  	{
	 			return(WayPoint*) (this);	}
	 
__forceinline 	operator	hdgitem* ()  	{
	 			return(hdgitem*) (this);	}
	 
__forceinline 	operator	hpitem* ()  	{
	 			return(hpitem*) (this);	}
	 
__forceinline 	operator	rotitem* ()  	{
	 			return(rotitem*) (this);	}
	 
__forceinline 	operator	mobileitem* ()  	{
	 			return(mobileitem*) (this);	}
	 
__forceinline 	operator	MovingItem* ()  	{
	 			return(MovingItem*) (this);	}
	 
__forceinline 	operator	TransientItem* ()  	{
	 			return(TransientItem*) (this);	}
	 
__forceinline 	operator	FormationItemPtr ()  	{
	 			return(FormationItemPtr) (this);	}
	 
__forceinline 	operator	ShipItemPtr ()  	{
	 			return(ShipItemPtr) (this);	}
	 
__forceinline 	operator	AirStrucPtr ()  	{
	 			return(AirStrucPtr) (this);	}
 
__forceinline	operator    info_itemS*	()		{
				return	(info_itemS*)(this);	}

__forceinline	operator    info_base*	()		{
				return	(info_base*)(this);	}

__forceinline	operator    info_waypoint*	()		{
				return	(info_waypoint*)(this);	}

__forceinline	operator    info_grndgrp*	()		{
				return	(info_grndgrp*)(this);	}

__forceinline	operator    info_airgrp*	()		{
				return	(info_airgrp*)(this);	}
__forceinline	operator    SAGAirstruc*	()		{
				return	(SAGAirstruc*)(this);	}
__forceinline	operator    SAGairgrp*	()		{
				return	(SAGairgrp*)(this);	}
#else
 	operator	item* ()	  	{
			 if (this)	 assert (Status.size>=ItemSize);
	 			return(item*) (this);	}
 	operator	WayPoint* ()  	{
			 if (this)	 assert ( Status.size==WayPointSize);
	 			return(WayPoint*) (this);	}
	 
 	operator	hdgitem* ()  	{
			 if (this)	 assert ( Status.size>=HdgSize);
	 			return(hdgitem*) (this);	}
	 
 	operator	hpitem* ()  	{
			 if (this)	 assert ( Status.size>=HPSize);
	 			return(hpitem*) (this);	}
	 
 	operator	rotitem* ()  	{
			 if (this)	 assert ( Status.size>=RotatedSize);
	 			return(rotitem*) (this);	}
	 
 	operator	MovingItem* ()  	{
			 if (this)	 assert ( Status.size>=MovingSize);
	 			return(MovingItem*) (this);	}
	 
 	operator	mobileitem* ()  	{
			 if (this)	 assert ( Status.size>=MobileSize);
	 			return(mobileitem*) (this);	}
	 
 	operator	TransientItem* ()  	{
			 if (this)	 assert ( Status.size>=TransientSize);
	 			return(TransientItem*) (this);	}
	 
 	operator	FormationItemPtr ()  	{
			 if (this)	 assert ( Status.size>=FormationSize);
	 			return(FormationItemPtr) (this);	}
	 
 	operator	ShipItemPtr ()  	{
			 if (this)	 assert ( Status.size>=ShipSize);
	 			return(ShipItemPtr) (this);	}
	 
 	operator	AirStrucPtr ()  	{
			 if (this)	 assert ( Status.size>=AirStrucSize);
	 			return(AirStrucPtr) (this);	}

	operator    info_itemS*	()		{
			 if (this)	 assert (Status.size>=ItemSize);
				return	(info_itemS*)(this);	}

	operator    info_base*	()		{
				return	(info_base*)(this);	}

	operator    info_waypoint*	()		{
			 if (this)	 assert ( Status.size==WayPointSize);
				return	(info_waypoint*)(this);	}

	operator    info_grndgrp*	()		{
			 if (this)	 assert ( Status.size>=MobileSize);
				return	(info_grndgrp*)(this);	}

	operator    info_airgrp*	()		{
			 if (this)	 assert ( Status.size>=AirStrucSize);
				return	(info_airgrp*)(this);	}

	operator    SAGAirstruc*	()		{
	 		 if (this)	assert (Status.size>=AirStrucSize);
				return	(SAGAirstruc*)(this);	}
	operator    SAGairgrp*	()		{
	 		 assert (this && Status.size>=AirStrucSize);
				return	(SAGairgrp*)(this);	}
#endif
#ifdef	worldincassert
	#undef	worldincassert
#endif
// #ifdef __WATCOMC__
// #pragma warning	690	2
// #endif
};

inline	COORDS3D&	operator += (COORDS3D& trg,COORDS3D& src)	{trg.X+=src.X;trg.Y+=src.Y;trg.Z+=src.Z;return(trg);}
inline	COORDS3D&	operator -= (COORDS3D& trg,COORDS3D& src)	{trg.X-=src.X;trg.Y-=src.Y;trg.Z-=src.Z;return(trg);}
inline	COORDS3D&	operator += (COORDS3D& trg,ItemBase* src)	{trg.X+=src->World.X;trg.Y+=src->World.Y;trg.Z+=src->World.Z;return(trg);}
inline	COORDS3D&	operator -= (COORDS3D& trg,ItemBase* src)	{trg.X-=src->World.X;trg.Y-=src->World.Y;trg.Z-=src->World.Z;return(trg);}


//Nasty cludge number 67: This field contains -1 for map items...
struct WPOverlayItem:public ItemBase			//o10s04
{	WayPointPtr	next;	WPOverlayItem()	{next=NULL;}	};
struct ItemOverlayWP:public ItemBase
{	ItemPtr	Next;		ItemOverlayWP()	{Next=NULL;}	};
struct InfoItemFlag:public ItemBase
{	int		Minus1;};
typedef	InfoItemFlag*	InfoItemFlagPtr;

//
//Waypoint structure											//RDH 28Nov95
//Like an item, only different!
//


struct	WayPoint:public	WPOverlayItem	//o14 //o30	//uniqueid and position	
{
	friend	COORDS3D* FindDesPos(WayPointPtr);
	void	operator delete(void* obj)	{::delete(WayPointPtr) obj;}
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
//	WayPointPtr		next;
	WayPointPtr		prev;							//o14s04
	SLong			range;							//o18s04
	itemptr			target;							//o1Cs04
	SLong			ETA;							//o20s04
	SLong			_vel;							//o24s02
	ONLYFIELD(UWord,BFieldWaypointActions,action);	//o26s02
	ONLYFIELD(UByte,WPNames,wpname);				//o28s01//WPNAME_None means no name
	UByte			wpnum;							//o29s01//0 means no number
	//During init I use 1 upper bit of skip UID as forward reference flag.
	ONLYFIELD(UWord,UniqueID,skipunder);			//o2As02
	ONLYFIELD(UWord,UniqueID,skipover);				//o2Cs02
	SWord			DUMMYSPARE;						//o2Es02
protected:
	WayPoint*	NextWP(UniqueID uniqueID);
public:
	WayPoint*	NextWP(MobileItemPtr owner);
	WayPoint*	NextWP(AirStrucPtr sagableowner);

	WayPoint()	{Status.size=WayPointSize;target=NULL;next=prev=NULL;
					skipunder=UID_Null;skipover=IllegalSepID;}
	COORDS3D*	FindDesPos();
	WayPointPtr		FindWP(WPNames name);										  //RDH 08/03/99
//DEADCODE DAW 08/06/99 	#ifdef	TEXT_Included
//DEADCODE DAW 08/06/99 	TextSnip0	GetWpName();
//DEADCODE DAW 08/06/99 	#endif
#ifdef TRACKBADASSIGNMENTS
	operator=(WayPoint&);
#endif

};
COORDS3D* FindDesPos(WayPointPtr w);

//
//	Basic item in world must have shape and world pos + unique ID
//  Do we need briefID?
//
//
struct	FormationType;

class	item:public	ItemOverlayWP				//o14	//o1C
{
//private:
//DeadCode PD 26Mar96 	animptr		Anim;		//This is the new shape element linked data area
public:
	animptr		Anim;						//o14s04//This is the new shape element linked data area//PD 26Mar96
	ONLYFIELD(UWord,ShapeNum,shape);		//o18s02
	ONLYFIELD(UWord,UniqueID,SGT);			//o1As02

static	ANGLES	PitchIntercept;									//RDH 01Dec95
static	ANGLES	HdgIntercept;									//RDH 01Dec95
static	SLong	Range;											//RDH 01Dec95
	void	firstshape(UWord ,animptr );
	void	nextshape(UWord ,animptr );
	void	firstweap(UWord ,animptr );
	void	nextweap(UWord	,animptr );
	int		Distance3D(COORDS3D*);
static int	Distance3D(COORDS3D*, COORDS3D*);	//CSB 26/04/99	
	FP		Distance3DSquared(COORDS3D*);
	FP		DistanceApprox(COORDS3D*, COORDS3D*);					  //CSB 02/02/00
	void InterceptandRange (COORDS3D*);
static 	void item::InterceptandRange (COORDS3D* subject, COORDS3D* target);
//RDH 01Dec95
	void InterceptandRange (ItemBasePtr i) {InterceptandRange(&i->World);}//JIM 31Jul96
	UByte&	AnimByte(Animfieldref);

//public:							//and also controls weapon launching
//	itemptr		Next;
//DeadCode RDH 04Dec95 	UNIQUE_ID	UniqueID;	//access with myitem->UniqueID.count
//	BRIEF_ID	BriefID;
//DeadCode RDH 04Dec95 	ITEM_STATUS	Status;		
//DeadCode RDH 04Dec95 	ITEM_SIZE	ItemSize;
	item()	{Status.size=ItemSize;Next=NULL;SGT=UID_NULL;shape=ShapeNum(0);}		//RJS 7Nov00
//DEADCODE JIM 16/11/99 	int	FACReportDamage(bool	waskill);
//DEADCODE JIM 16/11/99 	static	void	FACReportGround();
//DeadCode AMM 10Oct00 	void	ScoreSimpleItemKilled(bool itsdead,AirStrucPtr killer);
#ifdef TRACKBADASSIGNMENTS
	operator=(Item&);
#endif
	COORDS3D*	Formation_xyz(ANGLES hdg,FormationType* formtype,int formindex);//RDH 17Jun96
};

//DeadCode RJS 21Apr99 inline	ItemBase::~ItemBase()	
//DeadCode RJS 21Apr99 {	if ((int)Status.size>=(int)ItemSize) 
//DeadCode RJS 21Apr99 		delete [] (char*) ((ItemPtr) this)->Anim;
//DeadCode RJS 21Apr99 	((ItemPtr) this)->Anim=NULL;
//DeadCode RJS 21Apr99 //DEADCODE JIM 19/01/99 	Status.size=ItemBaseSize;
//DeadCode RJS 21Apr99 }
inline	ItemBase::~ItemBase()									//RJS 21Apr99
{	if ((int)Status.size>=(int)ItemSize) 						//RJS 21Apr99
	{															//RJS 21Apr99
		((ItemPtr) this)->Anim.Delete();						//RJS 21Apr99
	}															//RJS 21Apr99
}																//RJS 21Apr99

//
//	Subdividing rotated item to allow simpler objects
//
//
class	hdgitem:public	item			//o1Cs02
{
public:
	ANGLES		hdg;
	hdgitem()	{Status.size=HdgSize;}
	void	operator delete(void* obj)	{::delete(HdgItemPtr) obj;}
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
};

//
//
//
//
class	hpitem:public	hdgitem			//o1Es02
{
public:
	ANGLES		pitch;
	hpitem()	{Status.size=HPSize;}
	void	operator delete(void* obj) {::delete(hpitem*) obj;}
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
};

//
//
//
//
class	rotitem:public	hpitem			//o20s02
{
public:
	ANGLES		roll;
	rotitem()	{Status.size=RotatedSize;}
	void	operator delete(void* obj) {::delete(rotitem*) obj;}
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
};

//
// Mobile item subdivided into vel movement and controled movement
//
class	MovingItem:public	rotitem		//o22
{
public:

void CalcNewPos(SLong deltax,SLong deltay,SLong deltaz);
//DEADCODE CSB 08/11/99     SWord		velx,					//o22s02						//RDH 13Nov95
//DEADCODE CSB 08/11/99 				vely,					//o24s02						//RDH 30Oct95
//DEADCODE CSB 08/11/99 				velz,					//o26s02						//RDH 30Oct95
//DEADCODE CSB 08/11/99 				velhori,				//o28s02						//RDH 30Oct95
//DEADCODE CSB 08/11/99 				vel;					//o2As02//units mm/cs - max 3276m/s=mach 10		//RDH 30Oct95
	//VelX,VelY is not equivalent to VelHori,Hdg when sliding.
	//no longer want deltas inside moving item - calc. as local longs
	//they are useful for collision, of course
	//Delta was Vel * cs /10 -> cm. Max cs=33
	//Vel*4 is a good overestimator throwout before recalc.

	SLong	vel_x,	//micrometers / cs = 1/10000 m/s = 0.0001 m/s	//CSB 08/11/99
			vel_y,													//CSB 08/11/99
			vel_z,													//CSB 08/11/99
			vel_;													//CSB 08/11/99

	MovingItem()	{Status.size=MovingSize;}
};

//DeadCode AMM 27Aug98 typedef struct _packet PACKET;
//DeadCode AMM 27Aug98 typedef struct _packet* LPPACKET;
//
// MobileItem allows a movecode and a waypoint
//
//
class WorldStuff;
class	shape;
typedef shape Shape;
class	mobileitem:public	MovingItem	//o2C
{
	friend class item;
	friend class ManualPilot;									//AMM 01Jun98
	friend class Replay;										//AMM 01Jun98
	friend class DPlay;											//AMM 01Jun98
	friend class Persons2;	friend class Persons3;
	friend class TransObj;										//PD 01May96
	friend	void SendInit2Packet ();							//ARM 17Sep96
//DeadCode AMM 27Aug98 	friend	void CopyPacket (ItemBasePtr lpItemBase);		//AMM 25Aug98
	friend Shape;											//RJS 05Aug96
	friend class State3dOnGoing;											//RJS 05Aug96
	friend class ArtInt;											//RJS 05Aug96
	friend class TrgListProc;											//RJS 05Aug96
	friend class BoxCol;											//RJS 05Aug96
//LastModified:	JIM 24Sep96

private:
static	void MoveList(MobileItemPtr entry,WorldStuff& world);
static	MobileItemPtr	MobileList;
protected:
static	void MoveItem(MobileItemPtr entry,WorldStuff&);				//PD 02May96
static	MobileItemPtr	ACList;
static	MobileItemPtr	SAGList;
public:
static  WorldStuff*		currworld;								//DAW 02Apr96
static	UByte	timerseed;
static int	timeofday;
static	void SetWorld(WorldStuff* w)	{currworld=w;}					//JIM 25Jul96
static	WorldStuff& GetWorld() {return *currworld;}				//ARM 25Jul96
	void	operator delete(void* obj)	{::delete(MovingItemPtr) obj;}
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
static	void MoveAll(WorldStuff& world);
static	MobileItemPtr	GetACList(){return ACList;}					//RJS 27Apr00
static	MobileItemPtr	GetSAGList(){return SAGList;}					//RJS 27Apr00

	MobileItemPtr			nextmobile;			//o2Cs04
	WayPointPtr	waypoint;						//o30s04


	FIRSTFIELD( UByte,	AutoMoveCodeTypeSelect,movecode,	5)		//o34s01
	LASTFIELD(			Nationality,nationality,			6,7)
//	AutoMoveCodeTypeSelect	movecode:6;
//	Nationality				nationality:2;

	mobileitem()	{Status.size=MobileSize;waypoint=NULL;}
	void AddToList();

void	ExecuteWayPointAction ();								//RDH 19Feb96
void	DoWayPointAction (AutoMoveCodeTypeSelect	oldmove,WayPointPtr	oldwp,BFieldWaypointActions wpa);

void	NextWayPoint ();										//RDH 19Feb96
void	TeleportWayPoint ();										//RDH 19Feb96
BFieldWaypointActions
		EndLoopWayPoint ();										//RDH 19Feb96
BFieldWaypointActions
		MidLoopWayPoint ();										//RDH 19Feb96
bool	EscorteePastWP(WayPointPtr);
void	ForceBreakLoopWayPoint();		
//DeadCode DAW 19Nov96 void	MidLoopWayPoint ();										//RDH 19Feb96
void	WaitDeadWayPoint ();										//RDH 19Feb96
void	StartBombing ();										//RDH 19Feb96
void	StartStraffe ();										//RDH 19Feb96
void	LandingWayPoint ();
void	KillItNow ();
COORDS3D*	FindDesPos();
void	CalcXYZVel ();
void	NewPosition ();
static	void	WinMove (int timeofday,WorldStuff* worldref);							//ARM 16Sep96
static	void DosMove (int timeofday,WorldStuff* worldref);										//ARM 09Oct96
WorldStuff* GetCurrWorld () { return currworld; }				//ARM 06Sep96

static	void	ResetACGears();									//RJS 01Jun99

void	BlokeDawdle();											//RJS 10Jan00
void	BlokeTalk();											//RJS 10Jan00
void	EmergencyService();										//RJS 11Jan00

};

//
//transient item has targets and timers
//
class	TransientItem:public	mobileitem		//o35	//o50
{
public:
	static int transcount;
	void	operator delete(void* obj)	{::delete(TransientItemPtr) obj;}
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
	TransientItem()
	{
		Status.size=TransientSize;														//RJS 15Jun99
//DeadCode RJS 15Jun99 		Status.deadtime = 0;															//RJS 15Jun99
//DeadCode RJS 15Jun99 		Status.deadscale = 0;															//RJS 15Jun99
//DeadCode RJS 15Jun99 		Status.deaded = FALSE;															//RJS 15Jun99
		transcount++;
		isDeleted=0;
		isArmed=0;
		isOwned = 0;											//RJS 16Dec99
		TmpLaunchTime = 0;										//RJS 16Dec99
	}																					//RJS 15Jun99
	void AddToList();
static	TransientItemPtr	TransientList;						//MGA 13Mar96
static	void MoveTransList(TransientItemPtr entry, WorldStuff& world);//DAW 12Mar96
static	void MoveTransItem(TransientItemPtr entry,WorldStuff&);		//PD 26Apr96
static	void MoveAllTrans(WorldStuff& world);						//MGA 20Mar96

	void	CalcVels();											//RJS 12Nov99
	void	BombPitch();										//RJS 16Dec99


	UByte	CollTestEnabled		:1,				//o35s01				//RJS 21Jul98
			CollSuccessTrans	:1,								//RJS 21Jul98
			isOwned				:1,								//RJS 29Mar99
			isDeleted			:1,								//DAW 19May99
			isArmed				:1;								//DAW 19May99

	UWord	DrawOffset;							//o36s02				//RJS 27Nov98
	itemptr	Launcher;							//o38s04				//MGA 22Feb96
	itemptr Target;								//o3Cs04				//MGA 22Feb96
//TempCode MGA 29Feb96 	ShapeNum shape; //already have a shape in item definition
	SLong	LaunchTime;							//o40s04

	TransientItemPtr	nexttrans;				//o44s04			//MGA 28Feb96
	TransientItemPtr	nexttogo;				//o48s04

	UWord	TransRandom;						//o4Cs02				//PD 29Apr96
	UWord	TmpLaunchTime;							//o4Es02	//DAW 19May99
	ULong	TimeOfLaunch;										//DAW 19May99

};												//o50


//
// FormationItem allows mobiles to link together
//
//
//DEADCODE DAW 22/03/00 inline DutyType	BasicDuty(DutyType duty)
//DEADCODE DAW 22/03/00 {
//DEADCODE DAW 22/03/00 	if ((int)duty&(int)ACTIONSUBCODE)
//DEADCODE DAW 22/03/00 		return DutyType((int)duty&(int)DUTYMASK);
//DEADCODE DAW 22/03/00 	else
//DEADCODE DAW 22/03/00 		return duty;
//DEADCODE DAW 22/03/00 }

struct	ContourList;

class	formationitem:public	mobileitem		//o35	//o4A
{
public:
	ONLYFIELD(UByte,FormationIndex,formpos);	//o35s01//alignment optimisation			//JIM 20Aug96

	ONLYFIELD(UWord,	FormationTypeIndex,formation);		//o36s02

	FIRSTFIELD(UWord,	Bool,slowdownleader,		1)
		BITFIELD(		InFormation,information,	2,7)
		BITFIELD(		UWord,duty,				8,13)
		BITFIELD(		Bool,advantage,				14,14)
	LASTFIELD(		Bool,disadvantage,			15,15)


	FormationItemPtr
				leader,							//o38s04
				follower;						//o3Cs04

FormationItemPtr&	Leader()	{return (leader);}
FormationItemPtr&	Follower()	{return (follower);}
	ClassPtr	classtype;					   //o40s04

	ContourList*	contourlist;				//o44s04
	
	UWord		manoeuvretime;					//o48s02//max 655sec=11min								//JIM 20/01/99

//DEADCODE DAW 22/03/00 	DutyType	BasicDuty()
//DEADCODE DAW 22/03/00 	{
//DEADCODE DAW 22/03/00 		if ((int)duty&(int)ACTIONSUBCODE)
//DEADCODE DAW 22/03/00 			return DutyType((int)duty&(int)DUTYMASK);
//DEADCODE DAW 22/03/00 		else
//DEADCODE DAW 22/03/00 			return duty;
//DEADCODE DAW 22/03/00 	}

	formationitem()
	{	Status.size=FormationSize;
		leader=NULL;follower=NULL;contourlist=NULL;
	}

	void	operator delete(void* obj)	{::delete(FormationItemPtr) obj;}
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
	SWord TimeLeft();
	void SetManoeuvreTime (UWord time=6000);
	void	AutoTaxi ();
	void	AutoTaxiCornerUpTo();
	void	AutoTaxiCornerTurn();
	void	WaitToTaxi();
	SLong CalcReqVel ();
	Bool CalcVel ();
	Bool CalcVelSub (SLong reqvel);			//RDH 28Feb96
//DeadCode CSB 12/02/99		SWord CalcAccel (SWord, SWord);
//DeadCode CSB 12/02/99		void AddAccel2Vel(SWord);
	Bool CalcHdgRollFlat ();
	Bool AutoCalcPitch ();
	void MoveRollToZero(SWord	reqdeltahdg);	
	void GetFollower_xyz (FormationTypeIndex formationtype, FormationItemPtr leader = NULL);			//RDH 27Feb96	//CSB 25/05/99	
	void BreakForm();
	void RemoveDeadMember();
	void	DisperseWayPoint();
	void	FighterLimitWayPoint();
#ifdef	FILE_Included
bool	PlayerSequenceAudible(FileNum f); //msgai
#endif

	ItemPtr				SelectTarget(ItemPtr currtarget,int* selectedelt=NULL,int counter=0);
	int					SelectElement(ItemPtr currtarget,int counter=0);
	FormationItemPtr	SelectConvoyMember(FormationItemPtr curr,int count);
	bool				EnoughDamage3D(ItemPtr currtarget);
//	Coords3D*			FormationItem::SelectedElement(ItemPtr currtarget,int counter=0,Coords3D* coords=&despos);
	bool				FormationItem::SelectedElement(ItemPtr currtarget,int counter=0,Coords3D* coords=&despos); //alive flag

	void	AutoBloke();										//RJS 10Jan00
	void	AutoEmergencyVehicle();								//RJS 10Jan00
	void	AutoSlowTaxi ();


};

class	shipitem:public	formationitem
{
public:
	shipitem()	{Status.size=ShipSize;}
};

class	SquadronBase;				//RJS 18Feb00
struct	ai_info						//contains floats	//o??s60
{
	SquadronBase*	diaryptr;		//RJS 18Feb00

	itemptr		unfriendly,
//DeadCode CSB 21Aug00 				secondunfriendly[3],											//o00s04//save
				spottedunfriendly[4],											//o00s04//save
				homebase;											//o04s04//unchanged
	AirStrucPtr	Unfriendly()	{return *unfriendly;}
//DeadCode CSB 21Aug00 	AirStrucPtr	Unfriendly(int i){return *secondunfriendly[i];}
	AirStrucPtr	attacker;											//o08s04//save
	ONLYFIELD(UByte,SkillType,combatskill); // unchanged?
//DEADCODE JIM 01/12/99 	ONLYFIELD(UByte,SkillType,flyingskill);
		enum	SubMethod
		{
			SM_ANYA2A,
			SM_NOTBOMBERS		=1,
			SM_NOTFIGHTERS		=2,
			SM_MASK_A2A			=0x03,
			SM_DOSTRAFFEGROUND	=4,

			SM_ATTACKMETHODUNDEFINED = 0,
			SM_DIVEANDZOOM = 8,
			SM_HEADON = 16,
			SM_LINEABREAST = 24,
			SM_LINEASTERN = 32,
			SM_VIC = 40,
			SM_INDIVIDUAL = 48,
			SM_ATTACKMETHODSALL = 56,
			SM_MASK_FIRST		=0x38,
			SM_RETURN_ESCORT	=0x40,
			SM_109RETURNING		=0x80  //Also used for general out of fuel...
		};
																//o0Cs04
		FIRSTFIELD(ULong,UByte,ManStep,4)						//4	//unchanged
		BITFIELD(		Bool,radiosilent,			5,5)		//1	//unchanged
		BITFIELD(		Bool,simpleacm,				6,6)		//1	//save	
		BITFIELD(		Bool,beenseen,				7,7)		//1	//save
		BITFIELD(		SubMethod,submethod,		8,15)		// unchanged
		BITFIELD(		MANOEUVRE,manoeuvre,		16,22)		//7	//save
//LOTS OF SPARE BITS!!!! - Not really Lots any more...
//DEADCODE CSB 07/03/00 		BITFIELD(		Bool,flatturn,				23,23)		//1	//save
		BITFIELD(		Bool,moved,					23,23)		//1		//CSB 12Oct00
		LASTFIELD(		int,pilotnum,				24,31)		//8 
	UByte	morale;												//o10s01	//save
	SByte	moraleinc;								//o11s01	//save

//		BITFIELD(		NextLeadAct,leaderaction,	8,10)		//3	//unchanged
//		BITFIELD(		NextFollAct,followeraction,	27,29)		//3	//unchanged

	ONLYFIELD(UByte,tThreatLevel,			threatlevel);		//o12s01						//unchanged
	ONLYFIELD(UByte,tAggressionLevel,		aggressionlevel);	//o13s01						//unchanged
	ONLYFIELD(UByte,tFirstEncounterTactics,	firsttactic);		//o14s01					//unchanged
	ONLYFIELD(UByte,AcTactics,		elementtactics);			//o15s01						//unchanged	
	ONLYFIELD(UByte,AcTactics,		flighttactics);				//o16s01					//unchanged
	ONLYFIELD(UByte,AcTactics,		squadrontactics);			//o17s01					//unchanged	
//##not
//word aligned:
//DeadCode RDH 10Aug98 	UWord		JinkTime;										//DAW 12Jun96
//DeadCode AMM 14Aug00 	SLong		lastdelta;		//Dead?								//o18s04	//save, //delta from ideal shooting position
//DeadCode CSB 29/03/99		SLong		oldufposx, oldoldufposx, oldoldoldufposx,
//DeadCode CSB 29/03/99					oldufposy, oldoldufposy, oldoldoldufposy,
//DeadCode CSB 29/03/99					oldufposz, oldoldufposz, oldoldoldufposz;
	ANGLES		desiredroll,									//o1Cs02	//save
				desiredpitch,									//o1Es02	//save
//DEADCODE JIM 28/04/99 				lastdeltaroll,									//o20s02	//save
 				desiredaoa,		//								//o20s02	//save
				oldpitchI,		//								//o22s02	//save
				oldoldpitchI,	//								//o24s02	//save
				oldoldoldpitchI,//								//o26s02	//save
				oldhdgI,		//								//o28s02	//save
				oldoldhdgI,		//								//o2As02	//save
				oldoldoldhdgI,	//					t			//o2Cs02	//save
				desiredhdg;										//o3Es02	//save

	Float		desiredturn,	//Dead?								//o40s08	//save
				desiredpitchrate;//Dead?							//o48s08	//save
	ULong		desiredrange,	//Also used in FindDesPos to remember req ETA		//o50s04	//save
				desiredalt;		//Dead?								//o54s04	//save
//there is also a deltapitchsum in acm. The acm one controls the 
//elevator integral control. This one is at a higher level
	SLong		deltapitchsum;	//Also used in FindDesPos to remember req vel		//o58s04	//save

//I am reusing the above ACM based fields to drive AutoFollowWP 
//waypoint ETA cacheing. The intent is that if these fields do not match the
//current waypoint exactly then they are recalculated immediately.
//I am intentionally trying not to use fields above that may now be dead
	ULong&			DesEta()			{return desiredrange;}						  //JIM 17/01/00
	SLong&			DesVel()			{return deltapitchsum;}						  //JIM 17/01/00
	WayPointPtr&	LastClipped()		{return *(WayPointPtr*)&desiredroll;}
	BFieldWaypointActions& LastAction()	{return *(BFieldWaypointActions*)&desiredaoa;}
	ULong&			Lettering()			{return	*(ULong*)&oldoldpitchI;}
//DeadCode RDH 20Sep98 	SWord		currentbuffet;									//RDH 06Jun96
	EventLogPtr	eventlog;										//o5Cs04	//ask jim
//DeadCode JIM 10Jun96 	msgptr		MessageList;	//this is it.. use msg->flags to say done/read
	 							//Use fixed speed looping to process times.
	ai_info()	{unfriendly=homebase=NULL;attacker=NULL;eventlog=NULL;diaryptr=NULL;for(int i=0;i<4;i++)spottedunfriendly[i]=NULL;}//RJS 18Feb00	//CSB 1Nov00
	enum	{PROPER_PILOT_MAX=1};
	int	squadnum()	{/*if (pilotnum<(int)PROPER_PILOT_MAX) return (pilotnum*11)>>8; else*/ return pilotnum-(int)PROPER_PILOT_MAX;	}
};
struct	weap_info					   //o??s20
{
	int		reloadmass;			//o00s04//0.01 g includes all weapons and weight of fuel tank but not weight of fuel
	int		reloaddrag;			//o04s04//N
	int		mass;				//o08s04//0.01 g includes all weapons and weight of fuel tank but not weight of fuel
	int		drag;				//o0Cs04//N
//DeadCode RJS 26Nov99	int		int_fuel;			//o10s04//0.01 g
//DeadCode RJS 26Nov99	int		ext_fuel;			//o14s04//0.01 g
//DeadCode RJS 26Nov99	SWord	int_fuel_leakage;	//o18s02//g/s
//DeadCode RJS 26Nov99	SWord	ext_fuel_leakage;	//o1As02//g/s
//DeadCode RJS 26Nov99	SByte	int_launcher;		//o1Cs01									//RJS 25Mar99
//DeadCode RJS 26Nov99	SByte	ext_launcher;		//o1Ds01									//RJS 25Mar99
//DeadCode RJS 26Nov99	UWord	DUMMYWASTAGE;		//o1Es02
};
struct	weap_ctl			//o??s6C
{
	weap_info	right;			//o00s20
	weap_info	centre;			//o20s20
	weap_info	left;			//o40s20
	
	SWord		ShootDelay;		//o60s02									//save
	FIRSTFIELD(UWord,Bool,UseIntFuel,0)		//o62s02
	BITFIELD(		Bool,FuelDumped,1,1)
	BITFIELD(		Bool,StoresDumped,2,2)
	BITFIELD(		Bool,Ejected,3,3)
	BITFIELD(		Bool,reportedbingo,4,4)
	BITFIELD(		Bool,reportedbingohurting,5,5)
//
//	Spare bits 6-10
//
//need to store AnimWeaponPack for ac to reset rockets etc
	LASTFIELD(		int,Weapons,11,15)					//AMM 07Apr99
	SByte	weapontype;						//o64s01		//LT_ byte	//RJS 08Dec99
	UByte	shpweapindex;					//o65s01		//Index is basically aircraft type...
	SWord		weapforce;					//o66s02					//RJS 16Sep98
//DeadCode RJS 15Nov99 	TransientItem*	currentbullet;			//o68s04					//RJS 29Mar99
};

struct	flight_ctl						//o??s40
{
										//save //RDH 03/03/99
	AirStrucPtr	nextflight,				//o00s04							//save
				leadflight,
				expandedsag;	//2-WAY. NULL if not expanded SAG

	AirStrucPtr	leadelt();
	SWord		numinsag;  //Zero if a (expanded) SAG member OR lone AC
	SWord		rpm,					//o08s02							//save
				thrustpercent;			//o0As02							//save
	SWord		propsetting;

//DEADCODE CB 01/11/99 				afterburner;			//o0Cs02							//not used
//				LastRoll;
	ANGLES		cpitch;					//o0Es02							//calc
	WayPointPtr	backupWP;				//o10s04							//save
	SLong		//cposy,
				gforce;					//o14s04							//save
	SLong		groundlevel;			//o18s04							//calc _Collide.LowestSafeAlt(this,					//JIM 29Oct96
																	//			pitch,				//JIM 29Oct96
																	//		roll);	
	ONLYFIELD(UWord,FormationIndex,originalformpos);	//o1Cs01

//DEADCODE JIM 09/12/99 	FIRSTFIELD(UByte,	UByte,comefrommap,		6)		//o1Ds01			//ask jim
//DEADCODE JIM 09/12/99 	LASTFIELD(			Bool,inRadarSight,		7,7)	//RJS 13May99
	SByte		redeffect;								//o1Es01	//ask Paul
	UByte		callname;								//o1Fs01		//ask Jim
	UByte		callnum;								//o20s01		//sak Jim
//TEMPCODE JIM 28/04/99 	UByte		callvoice;
	UByte		AeroDeviceCnt;							//o21s01		//RJS 18Sep98

//DEADCODE JIM 10/12/99 	SWord		i_a_s,									//o22s02		//calc from SetInstruments
//DEADCODE JIM 10/12/99 				vel_cms;								//o24s02		//calc from setFlightParams, questio need
																
	SWord		aileron,								//o26s02		//save
				elevator,								//o28s02		//save
				rudder;									//o2As02		//save


	PMODEL		pModel;									//02Cs04		//model.h	
	PACMMODEL	pAcmModel;								//030s04		//acmmodel.h
	PINSTRUMENTS	pInst;								//034s04		//ask Robert

	Float		dhdg;									//038s08		//save

	int			fuel_content[4];	//centigrammes			//CB 05/11/99	//save
	bool		use_this_tank[4];							//CB 05/11/99	//save

	SWord		rpm1;													//RJS 21Jun00 (don't save)

	SWord		FuelCockPos;


	flight_ctl()	{backupWP=NULL;nextflight=leadflight=NULL;}

};

//DEADCODE JIM 28/04/99 struct	instrum_ctl
//DEADCODE JIM 28/04/99 {
//DEADCODE JIM 28/04/99 //LIGHTS		InstrumLights;	//most flags are in animation data
//DEADCODE JIM 28/04/99 
//DEADCODE JIM 28/04/99 };

//

struct RequiredBankDataElement									//RDH 18Dec95
	{															//RDH 18Dec95
//Old_Code PD 10Nov97 		ANGLES hdg; ANGLES roll;								//RDH 18Dec95
		ANGLESInst hdg; ANGLESInst roll;								//RDH 18Dec95
	};															//RDH 18Dec95

// Don't want to include "model.h"								//ARM 01May97
Bool NewModel (AirStrucPtr const);								//ARM 01May97
void DeleteModel (AirStrucPtr const);							//ARM 01May97


//variables commented to indicate action required for replay, rdh
//				save			need to savethe variable in the replay file
//				set by ***		use the function *** to set the variable
//				unchanged		the variable, once set is never changed
//				zero			the variable should be zeroed on replaying 

class	ACMAirStruc;
class	MoveAirStruc;
struct	SAGAirstruc;
struct	FormationType;
struct	WaypointOffsetSub;	
struct	GroupItterator;
typedef FormationType* SingleFormation;
class	AirStruc:public shipitem		//o4A
{							//0					1							2							3
public:
// used in coop multiplayer games to decide which player transmits an AI ACs collisions
// with players
	UNIQUE_ID	lasthitter;					//o4As02					//save

public:		
	ai_info		ai;							//o4Cs60
	weap_ctl	weap;						//oACs6C	//ask Rob
	flight_ctl	fly;						//o118s40

//DEADCODE AMM 07/03/00 	bool		sentexpanded;
//DEADCODE AMM 07/03/00 	bool		sentcontracted;

//DEADCODE JIM 28/04/99   	instrum_ctl	inst;						//o158s	//ask Robert

//DEADCODE AMM 07/03/00 	ONLYFIELD(UWord,UniqueID,CommsOwner);	//o158s02

	FIRSTFIELD(UWord,UniqueID,CommsOwner,13)
	BITFIELD(Bool,sentcontracted,14,14)
	LASTFIELD(Bool,sentexpanded,15,15)


	operator   ACMAirStruc*()	{return  (ACMAirStruc*)this;}
	operator   MoveAirStruc*()	{return  (MoveAirStruc*)this;}
	operator   SAGAirstruc*()	{return  (SAGAirstruc*)this;}
	SAGAirstruc&   SAG()	{return  *(SAGAirstruc*)*this;}
	ACMAirStruc&   ACMAS()	{return  *(ACMAirStruc*)*this;}
	MoveAirStruc&   Move()	{return  *(MoveAirStruc*)*this;}
//DeadCode AMM 29Aug00 static	bool		playermoving;
//DeadCode AMM 29Aug00 static	AirStrucPtr	playernotmovingheldac;
//DeadCode AMM 29Aug00 static	bool		PlayerStartedMoving();

static UWord airdensityratiosquareroot[];

static UWord vel_to_aoa[];

//constructors

	AirStruc()													//ARM 01May97
	{															//ARM 01May97
		Status.size = AirStrucSize;								//ARM 01May97
		NewModel (this);										//ARM 01May97
	}															//ARM 01May97
	~AirStruc()													//ARM 01May97
	{															//ARM 01May97
		DeleteModel (this);										//ARM 01May97
	}															//ARM 01May97
#ifdef TRACKBADASSIGNMENTS
	operator=(AirStruc&);
#endif

	void AddToList();
	void	operator delete(void* obj)	{::delete(AirStrucPtr) obj;}
#ifndef	__BCPLUSPLUS__
	void	operator	delete(void* p,const char*,int)	{operator delete(p);}
#endif
//DEADCODE CSB 16/12/99 	void AutoCrossOverTurn();										  //CSB 14/12/99
//DEADCODE CSB 16/12/99 //DeadCode RDH 05Jan99 	void AutoTrainingACM ();
//DEADCODE CSB 16/12/99 	void AutoCrashSkid();
//DEADCODE CSB 16/12/99 	void AutoAccelerate();
//DEADCODE CSB 16/12/99 	void AutoCrashRoll();
//DEADCODE CSB 16/12/99 //DeadCode RDH 05Jan99 	void AutoTrainingPreMerge ();
//DEADCODE CSB 16/12/99 //DeadCode RDH 05Jan99 	void SelectNextTrainingManoeuvre();
//DEADCODE CSB 16/12/99 	void AutoFollowWpWing (AirStrucPtr MyLeader = NULL);		//RDH 27Feb96	//CSB 20/04/99	
//DEADCODE CSB 16/12/99 	void	AutoTakeOff ();										//RDH 17Jun96
//DEADCODE CSB 16/12/99 	void
//DEADCODE CSB 16/12/99  	AutoLanding ();
//DEADCODE CSB 16/12/99 	void	HeldACCheck();
//DEADCODE DAW 27/01/00 	void AutoCrashSkid();
//DEADCODE DAW 27/01/00 	void AutoAccelerate();
//DEADCODE DAW 27/01/00 	void AutoCrashRoll();
//DeadCode RDH 05Jan99 	void AutoTrainingPreMerge ();
//DeadCode RDH 05Jan99 	void SelectNextTrainingManoeuvre();
//DEADCODE DAW 27/01/00 	void AutoFollowWpWing (AirStrucPtr MyLeader = NULL);		//RDH 27Feb96	//CSB 20/04/99	
//DEADCODE DAW 27/01/00 	void	AutoTakeOff ();										//RDH 17Jun96
//DEADCODE DAW 27/01/00 	void
//DEADCODE DAW 27/01/00  	AutoLanding ();
//DEADCODE DAW 27/01/00 	void	HeldACCheck();


//DEADCODE DAW 27/01/00 	void	AutoTakeOffWing ();									//RDH 17Jun96
	void	AirStruc::TrackBogey();
	void	AirStruc::TrackBandit();
//DEADCODE CSB 16/12/99 	void	AutoTakeOffWing ();									//RDH 17Jun96
//DEADCODE CSB 16/12/99 	void	AirStruc::TrackBogey();
//DEADCODE CSB 16/12/99 	void	AirStruc::TrackBandit();


	void	FirstTimeInCombatMsg();						  //RDH 04/03/99
	bool	OutNumbered(AirStruc* trg);								  //RDH 04/03/99

	void	InformOfDanger(AirStruc* caller, AirStruc* callee);													  //RDH 04/03/99
	void AirCombat();
	void BreakCallandReaction(AirStrucPtr buddy,AirStrucPtr currac,AirStrucPtr unf); //RDH 13/06/99
	void BreakCallReaction(AirStrucPtr currac,AirStrucPtr unf);		  //RDH 27/06/99
	AirStrucPtr	FindFreeAcInGroup();									//CSB 21/03/00
	void	SetLettering(int letteringcode);

	void SetDesiredVel();			//rdh9/12/98
//DeadCode RDH 10Sep96 static	void AutoDeathSequence(MobileItemPtr);							//RJS 08Aug96
//DEADCODE JIM 16/11/99 	void	AutoFAC ();
//DEADCODE JIM 16/11/99 	int		GetFACStage();

//DEADCODE JIM 16/11/99 	void	AutoCAS();
//DEADCODE JIM 16/11/99 	AirStrucPtr	FindMyFAC();
//DEADCODE JIM 16/11/99 	void	SetToCAS(bool firsttime=true);

	void	AutoToGrndPitchRoll(ANGLES grndroll,ANGLES grndpitch);
	void	SimpleMoveToRoll (SWord);
	UWord	CalcMaxPitchRate();	//CSB 01/06/99	

	void	FireABullet(SWord delaybetweenbursts,Bool isArmed=TRUE); //RJS 27May99
	void	FireARocket(SWord delaybetweenbursts,Bool isArmed=TRUE); //RJS 27May99
//DeadCode DAW 27Jun99 	Bool CheckForWeapon(UByte ltype);							//CSB 26/03/99	
	Bool CheckForAnyWeapon();									//CSB 26/03/99	
	Bool CheckForWeapon(UByte ltype);							//CSB 26/03/99
	Bool ChooseAWeapon();										//CSB 02/04/99	
	Bool CarryingNapalm();										//CSB 29/04/99	
	Bool SelectBombTarget(Bool NewTarg);						//CSB 03/04/99	
	Bool AnyoneInPhaseN(char PhaseNum);							//CSB 03/04/99
	Bool IsThisBombLeader();									//CSB 23/04/99	
	bool IsLocalLeader();									//CSB 11/05/99	
	UWord CountGroup();											//CSB 23/04/99	
	COORDS3D* RotateToHdg(COORDS3D GlobDelta, COORDS3D& LocalDelta, ANGLES Heading);	//CSB 23/04/99	
	UniqueID FindLeadUID();	//CSB 07/06/99
	void WindTrackCorrection(SLong, SWord, SWord, SLong&, SWord&, SWord&);	//CSB 10/06/99	
	void WindBulletDrift    (SLong, SWord, SWord, SLong&, SWord&, SWord&);	//CSB 10/06/99	
	void CalcBulletVel(SLong MuzVel, SWord &Hdg, SWord &Pitch, SLong &BullVel);	//CSB 11/06/99	
	void CalcBulletVel(SLong MuzVel, SLong posx, SLong posy, SLong posz, SLong& vx, SLong& vy, SLong& vz);

//DEADCODE JIM 16/11/99 	ItemPtr	CheckFACTarget(ItemBasePtr targ);
//DEADCODE JIM 16/11/99 	void	LogAutoCASKill();

//DEADCODE JIM 16/11/99 	void SendFACMessage(PhaseFAC phase);
	Bool	HasSmoked();										//RJS 12Mar99	
	AirStrucPtr	FlyEscortTo();	//returns null if independent
	AirStrucPtr	FindLeadCandidate();	//CSB 20/04/99	
	AirStrucPtr	FindFormpos0();								  //CSB 20/01/00
	void	ChainBingoMessage(bool atbingohurting);

//secondary stuff
public:
AirStrucPtr&	Leader()	{return *(AirStrucPtr*)(&leader);}
AirStrucPtr&	Follower()	{return *(AirStrucPtr*)(&follower);}
//	UByte	AirStruc::FightingFactor();
	UByte	CombatFactor();
	UByte	FlyingFactor();

//DeadCode JIM 15Oct96 	void RemoveDeadMember();
	void BreakForm();
	void SAGBreakForm();
	bool ShouldDumpAndRun(bool FromSpot, bool FromKill, AirStrucPtr Enemy = NULL);
	void DumpAndRun();

	Bool	IsUsingPilotedAcLog();
	COORDS3D*	FindDesPos ();
	COORDS3D*	InterceptandRangeFindDesPosAndVel();
static void		GenWaypointOffsetSub(FormationTypeIndex formation,WaypointOffsetSub& wos,bool isescort);
static	int		ModifyHdgRangeForFormation(int dhori);

	COORDS3D* FindCombatPos ();
//	void GetFollower_xyz (FormationTypeIndex formationtype, FormationItemPtr leader = NULL);			//RDH 27Feb96	//CSB 25/05/99	
	void GetFlightLeader_xyz (FormationTypeIndex formationtype, FormationItemPtr leader = NULL);//RDH 17Jun96
	void	GetFollower_xyz (FormationTypeIndex	formationtype, AirStrucPtr leader);
	void GetEscort_xyz (FormationTypeIndex formationtype, FormationItemPtr leader = NULL);//RDH 17Jun96
	COORDS3D* PositionWRTLeader (AirStrucPtr lf = NULL);										//RDH 27Feb96	//CSB 25/05/99	
	COORDS3D* PositionTakeOffWRTLeader (AirStrucPtr lf = NULL);						//RDH 17Jun96
	void SetManualFlightParams ();								//RDH 22Apr96
//DEADCODE RDH 30/04/99 	void SendEveryOneHome ();									//RDH 24Sep96
	void LeaderBreakOff ();									//RDH 24Sep96
//DEADCODE RDH 30/04/99 	void SetWaypointForEveryBody(AirStrucPtr,WayPointPtr);									//RDH 24Sep96
	SWord RequiredDRoll (SWord);
	SWord RequiredDRollSub (SWord);								//RDH 11Oct96
	void AirStruc::RemoveFuelLeakage(weap_info weapinfo, SWord Xpos, UWord NFrames);

	void FuelLeft (FP FuelRate);								//RDH 03Jun96	//CSB 15/09/98
//DeadCode CSB 12/02/99		Bool CalcVelSub (SLong reqvel);								//RDH 15Nov96
//DEADCODE CSB 08/11/99 	Bool CalcVel ();											//RDH 22Nov96
	Bool AutoCalcPitch ();
	void NewPosition (bool withwind = true);
	void NewDeadPosition ();									//RJS 23Feb98
	void CalcNewPosWithWind(SLong deltax,SLong deltay,SLong deltaz,SLong groundlevel);
	void	CalcXYZVel ();
	void	CheckManualCourse();
	Bool	FuelShort(int excesstime,int* avail=NULL,int* safety=NULL );
	Bool	AircraftDamaged();
//DEADCODE JIM 25/04/99 static	void EndGameScoring();								//RDH 09Sep96
static	void PrelimActivePilotChk ();					//RDH 11Dec96
static	SkillType IncSkill (AirStrucPtr,SWord aircraft_no);			//RDH 04Dec96
static	void PlayerDecision ();						//RDH 09Sep96
static	void ModifySquadronMorale(MoraleType);		//RDH 09Sep96
static	void ModifyPilotMorale(SWord, MoraleType);				//RDH 09Sep96
static	void ModifyPlayerMerit(DeltaMeritType);				//RDH 09Sep96
	ANGLES AirStruc::BestClimbAngle();
	Bool	IsHealthyMovecode(ULong&);//RJS 28Aug98

	SLong  CalcBestClimbSpeed();	//CSB 28/09/98
	SWord  CalcBestClimbPitch();	//CSB 28/09/98
	SLong  CalcMaxVelSL ();			//CSB 28/09/98
	SLong  CalcMaxVelDive ();		//CSB 28/09/98
	SLong  CalcAccel(SLong);	//CSB 02/02/99
	void   AddAccel2Vel(SLong Accel);	//CSB 12/02/99
	Bool CalcVelAlt ();				//CSB 29/09/98
	Bool CalcVelAlt (SLong	reqvel);								  //JIM 01/02/99
	Bool CalcHdgRollLimited ();		//CSB 29/09/98
	Bool CalcHdgRollLimited (SWord reqdeltahdg);		//CSB 29/09/98
	void	SetWeaponForce(SLong mass=0,SLong velocity=0,SLong delay=1);//RJS 16Sep98
	void	SetFlightParams (bool dotimestuff=true);									//AMM 24Sep98
	void	SetMaccaVels();										//AMM 20Oct98

	Coords3D*	GetTakeOffPos(UniqueID takeoffID,Coords3D& postofill=despos);
	Coords3D*	GetTakeOffPoint(TAKEOFFPOINT point, Coords3D& postofill=despos); //CSB 16/12/99
	Bool	AmISmoking();										//RJS 18Feb99

																	  
	AirStrucPtr	GroupLeader()
	{	AirStrucPtr	rv=this;
		if (leader)			rv=Leader();
		if (rv->formpos)	rv=rv->fly.leadflight;
		return	rv;
	}
	Bool	TargetOnSubjectTail(ANGLES);
	Bool	SubjectOnTargetTail(ANGLES);
	Bool	TargetFacingSubject(ANGLES);
	Bool	SubjectFacingTarget(ANGLES);
	void	SetFollowersTactic(tFirstEncounterTactics);	//CSB 05/07/99	

	inline ShapeNum&	GetDrawShape();									//RJS 12Oct00
	ShapeNum&	_GetDrawShape();										//RJS 13Oct00

protected:
//DeadCode JIM 15Oct96 	void BreakForm();
	void CopyLeader (AirStrucPtr lf);											//RDH 27Feb96
	Bool CopyLeaderSub (AirStrucPtr lf);											//RDH 27Feb96
	SWord CalcWobbleDY();												  //CSB 14/12/99
	SWord CalcWobbleVY();												  //CSB 14/12/99
//DEADCODE JIM 09/02/00 	void GetFlightLeader_xyz (FormationTypeIndex 	formationtype);//RDH 17Jun96
//DeadCode JIM 30Apr96 	void GetFollower_xyz ();			//RDH 27Feb96
//DeadCode JIM 29Apr96 	SLong CalcReqVel ();
//DeadCode JIM 29Apr96 	Bool CalcVel ();
//DeadCode JIM 29Apr96 	Bool CalcVelSub (SLong reqvel);								//RDH 28Feb96
//DeadCode JIM 29Apr96 	Bool CalcHdgRollFlat ();
//DeadCode JIM 29Apr96 	Bool AutoCalcPitch ();
//DeadCode JIM 29Apr96 	void CalcXYZVel ();
//DeadCode JIM 29Apr96 	void SetManoeuvreTime (UWord time=2000);
	SWord ReachedDesPos ();
	void SetRpm ();
	Bool RollLevel (int delta);
	Bool CalcVelWing (AirStrucPtr lf, SLong Dist);										//JIM 29Oct96
	Bool CalcHdgRoll ();									//RDH 28Feb96
	Bool CalcHdgRoll (SWord delta);									//RDH 28Feb96
	SLong CalcHdg ();											//RDH 11Oct96
	void WindCorrection();
	Bool SideSlip (AirStrucPtr);											//RDH 28Feb96
	Bool SideSlide(AirStrucPtr);											//CSB 20/04/99	
	SWord FindRequiredRoll (SWord, RequiredBankDataElement*);
	void	SetControlSurfaces (); //RDH 25Mar96
//	void	SetInstruments (); //RDH 25Mar96
//DEADCODE DAW 18/01/00 	void	AirStruc::HeadOnAttack();								  //CB 24/11/99
//DEADCODE DAW 18/01/00 	void	AirStruc::Lufberry();									  //CB 18/11/99
//DEADCODE DAW 18/01/00 	void	AirStruc::SteepDive();									  //CB 18/11/99
//DEADCODE DAW 18/01/00 	void	AirStruc::UpAndUnder();									  //CB 18/11/99
//DEADCODE DAW 18/01/00 	void	AirStruc::StallTurn();									  //CB 18/11/99
//DEADCODE DAW 18/01/00 	void	AirStruc::SlashingAttack();								  //CB 18/11/99
//DEADCODE DAW 18/01/00 	void	AirStruc::ClimbTurn();									  //CB 18/11/99
//DEADCODE DAW 18/01/00 	void	AirStruc::Roll360();									  //CB 18/11/99
//DEADCODE DAW 18/01/00 	void	AirStruc::Straffe();									  //CB 18/11/99
//DEADCODE DAW 18/01/00 

//DEADCODE DAW 18/01/00 	Bool	AirStruc::TurnToHdgAndPitch();
//DeadCode RDH 07Jan99 	void	AirStruc::HotSideLagPursuitFight();
//DeadCode RDH 07Jan99 	Bool	AirStruc::SandwichManoeuvres();
//	SWord	AirStruc::RollforTurn(SWord reqdeltapitch,SWord deltahdg, Float& desiredturn);
//DEADCODE DAW 18/01/00 	SWord	RollforTurn(SWord reqdeltapitch,SWord deltahdg, Float& desiredturn,COORDS3D	target);
//DEADCODE DAW 18/01/00 	void	CalcDesiredPitchRate(SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos);
//DEADCODE DAW 18/01/00 	FP		CoarseRollAdjust(FP rroll, FP fpitch);
//DEADCODE DAW 18/01/00 	FP		FineRollAdjust(SWord reqdeltapitch,SWord deltahdg,FP rroll, FP fpitch, FP fhdg);
//DEADCODE DAW 18/01/00 	Bool	UnfriendlyOnSameRoll();


//DeadCode RDH 07Jan99 	void	AirStruc::SustainedTurn();
//DEADCODE DAW 18/01/00 	void	AirStruc::TurningFight();
//	void	AirStruc::CalcLead(SWord& velx,SWord& vely,SWord& velz);
//	void	AirStruc::CalcLead(AirStrucPtr  subject, AirStrucPtr target, SWord& velx,SWord& vely,SWord& velz);
//DEADCODE DAW 18/01/00 	void	AirStruc::CalcLead(AirStrucPtr  subject, AirStrucPtr target, SLong& velx,SLong& vely,SLong& velz, Bool cutcorner);

//	void	AirStruc::TurnFightSub(ANGLES	HdgIntercept);
//	void	AirStruc::TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch);
//DEADCODE DAW 18/01/00 	void	AirStruc::TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target);
//DEADCODE DAW 18/01/00 	void	AirStruc::TurnFightPhase1(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target);

//	void	AirStruc::TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget);
//DEADCODE DAW 18/01/00 	void	AirStruc::SlowDownCheck(UWord reqdeltahdg_pos);
//DEADCODE DAW 18/01/00 	void	AirStruc::SlowDown(FP velc);
//DEADCODE DAW 18/01/00 	void	AirStruc::SpeedUp(FP velc);

//DEADCODE DAW 18/01/00 	SWord	AirStruc::ThrustfromFF();


//	void	AirStruc::TurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget);
//DEADCODE DAW 18/01/00 	void	AirStruc::TurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target);

//DEADCODE DAW 18/01/00 	void	AirStruc::HighYoYo();
//DEADCODE DAW 18/01/00 	void	AirStruc::Zoom();
//DEADCODE DAW 18/01/00 	void	AirStruc::LowYoYo ( );
//DEADCODE DAW 18/01/00 	void	AirStruc::TurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign,UWord	reqdeltapitch_pos, ANGLES	deltapitch);
//DEADCODE DAW 18/01/00 	void	AirStruc::RollAndPull(SWord	reqdeltahdg, SWord dpitch);

//DEADCODE DAW 18/01/00 	void	AirStruc::InterceptHigh();
//DEADCODE DAW 18/01/00 	void	AirStruc::ClimbAtSustainedTurnSpeed();
//DEADCODE DAW 18/01/00 	
//DEADCODE DAW 18/01/00 	Bool	AirStruc::BanditOnColdSide();
//DEADCODE DAW 18/01/00 	Bool	AirStruc::BanditHasLead();
//DEADCODE DAW 18/01/00 
//DEADCODE DAW 18/01/00 	Bool 	AllOnTopCover ();										//RDH 19Aug96
//DEADCODE DAW 18/01/00 	Bool	AllButLdrNotOnCombat ();								//RDH 11Nov96
//DEADCODE DAW 18/01/00 	void	BarrelRollAttack ( );
//DEADCODE DAW 18/01/00 	void	Scissors ( );
//DEADCODE DAW 18/01/00 	void	MildScissors ( );
//DEADCODE DAW 18/01/00 	void	StraightandLevel ( );
//DEADCODE DAW 18/01/00 //DeadCode RDH 30Mar98 	void	AcmSideSlip ( );
//DEADCODE DAW 18/01/00 	void	SpinOut ( );
//DEADCODE DAW 18/01/00 	void	DiveforHome ( );
//DEADCODE DAW 18/01/00 	void	ClimbforHome ( );
//DEADCODE DAW 18/01/00 	void	StraightDive ( );
//DEADCODE DAW 18/01/00 	void	GoHome ( );
//DEADCODE DAW 18/01/00 	void	MakeForFriendly ( );
//DEADCODE DAW 18/01/00 	void	MoveAway ( );
//DEADCODE DAW 18/01/00 //DeadCode RDH 06Jan99 	void	AccidentalSpinOut ( );
//DEADCODE DAW 18/01/00 	void	SpinRecovery ( );								//RDH 21Aug96
//DEADCODE DAW 18/01/00 //rdh	void	TurningFight ( );
//DEADCODE DAW 18/01/00 	void	LowGYoYo ( );
//DEADCODE DAW 18/01/00 	void	RollAway ( );
//DEADCODE DAW 18/01/00 //DeadCode RDH 07Jan99 	void	VerticalLoop ( );
//DEADCODE DAW 18/01/00 //DeadCode RDH 07Jan99 	void	ImmelmannTurn ( );
//DEADCODE DAW 18/01/00 	void	HeadOnOffset ( );
//DEADCODE DAW 18/01/00 	void	Immelmann ( );
//DEADCODE DAW 18/01/00 	void	StayWithPrey ( );
//DEADCODE DAW 18/01/00 //DeadCode RDH 05Jan99 	void	GatherSpeed ();
//DEADCODE DAW 18/01/00 	void	LeadUnFriendly ();


//DeadCode RDH 30Mar98 	void	SelectDefendManoeuvre();
//DeadCode RDH 30Mar98 	void	SelectAttackManoeuvre();
//DeadCode RDH 30Mar98 	Bool	SelectDefendManoeuvreSub(DEFENDMANOEUVRE);
//DeadCode RDH 30Mar98 	Bool	SelectAttackManoeuvreSub(ATTACKMANOEUVRE);
//DEADCODE DAW 18/01/00 	Bool	TimeToChangeToEvade ();
//DEADCODE DAW 18/01/00 	Bool	WeHaveNumbersAdvantage ();
//DeadCode RDH 30Mar98 	Bool	WeHaveNumbersAndACMAdvantage ();
//DEADCODE DAW 18/01/00 	Bool	DisengageAppropriate ();
//DEADCODE DAW 18/01/00 	Bool	AirStruc::NoseToTail (ANGLES angle);
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectNextDisengageManoeuvre ();
//DEADCODE DAW 18/01/00 	void	AirStruc::PanicManoeuvres();
//DEADCODE DAW 18/01/00 	void	AirStruc::BanditHighManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::BanditLowManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::LowAltManoeuvre();
//DEADCODE DAW 18/01/00 	Bool	AirStruc::TooLow();

//DEADCODE DAW 18/01/00 	void	AirStruc::MoraleMod();

//rdh	void	AirStruc::SelectNextEngageManoeuvre ();
//DEADCODE DAW 18/01/00 	Bool	AirStruc::LooseDeuceSituation();
//DEADCODE DAW 18/01/00 	void	AirStruc::TakeLooseDeuceOption();
//DEADCODE DAW 18/01/00 	Bool	AirStruc::TimeToChangeToDisengage ();
//DEADCODE DAW 18/01/00 	SLong AirStruc::SubjectClosure();
//DEADCODE DAW 18/01/00 	Bool AirStruc::SubjectClosureGreaterThan(SLong dvel);
//DEADCODE DAW 18/01/00 	Bool	AirStruc::SubjectLeadingTarget();
//DEADCODE DAW 18/01/00 	Bool AirStruc::TargetClosureGreaterThan(SLong dvel);
//DEADCODE DAW 18/01/00 	Bool AirStruc::ClosureLessThan(SLong dvel);
//DEADCODE DAW 18/01/00 	Bool AirStruc::M_LagRoll();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_FlightSeparation();
//DEADCODE DAW 18/01/00 	bool AirStruc::AboveGround(SLong height);
//DEADCODE DAW 18/01/00 	void	AirStruc::ManoeuvreBasedOnClosure();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_BarrelRoll();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_ZoomAndDrop();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_SpinOut();
//DeadCode RDH 07Jan99 	Bool 	AirStruc::M_SideSlip();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_SelfAsBait();
//DEADCODE DAW 18/01/00 	Bool	AirStruc::TargetHasCorrectLead(ANGLES lead, ANGLES maxlead);
//DEADCODE DAW 18/01/00 	ANGLES AirStruc::ActualLead(AirStrucPtr  subjt, AirStrucPtr trgt);
//DEADCODE DAW 18/01/00 	MANOEUVRE	AirStruc::ManoeuvreBasedOnSkill(SkillType skill, MANOEUVRE goodman, MANOEUVRE badman);
//DEADCODE DAW 18/01/00 	Bool	AirStruc::SubjectHasEnergyAdvantage();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_GunDefence(ANGLES lead);
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_UnSighted();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_DiveForHome();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_SplitS();
//DEADCODE DAW 18/01/00 	Bool 	AirStruc::M_Scissors(ANGLES lead);
//DEADCODE DAW 18/01/00 	Bool	AirStruc::M_ShootTooEarly();
//DEADCODE DAW 18/01/00 	void	AirStruc::DefenceManoeuvre();
//DEADCODE DAW 18/01/00 	Bool	AirStruc::M_ShootToFrighten();
//DEADCODE DAW 18/01/00 	SLong		AirStruc::DeltaAltitude();
//DEADCODE DAW 18/01/00 	void	AirStruc::AggressivePassManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::DefensivePassManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectNoseToNoseManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectNoseToTailManoeuvre();
//DEADCODE DAW 18/01/00 	void AirStruc::SelectNoseToBeamManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectBeamToNoseManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectBeamToTailManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectBeamToBeamManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectTailToTailManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectTailToBeamManoeuvre();
//DEADCODE DAW 18/01/00 	void	AirStruc::SelectTailToNoseManoeuvre();
//DEADCODE DAW 18/01/00 	SLong AirStruc::CornerSpeed();
//DEADCODE DAW 18/01/00 	SLong AirStruc::SustainedTurnSpeed();


	Float	Model_InstTurnRate(AirStrucPtr subject);
//rdh	FP	Model_MachNo(){return 0.0;}
//	FP	Model_Speed(){return 0.0;}
public:
//DeadCode DAW 09Mar99 	bool		AcIsFlightLeader()	{return	(fly.position()==0);}
//DeadCode DAW 09Mar99 	bool		AcIsGroupLeader()	{return	(formpos==0);}
	bool		AcIsFlightLeader()	{return	((int)position()==0);}
	bool		AcIsGroupLeader()	{return	((int)formpos==0);}
	AirStrucPtr		AcIsPlayer();
	AirStrucPtr		InPlayersElement();
 	AirStrucPtr		FindBuddy();
 	AirStrucPtr		PlayerInGroup();
 	AirStrucPtr		PlayerInFlight();
 	AirStrucPtr		FindAirEscortLeader();
 	AirStrucPtr		AcCloseAttackingOneOfGroup(bool& victimfound);	  //RDH 27/06/99
 	AirStrucPtr		RemoveElement();								  //RDH 03/03/99
	AirStruc*		FindGroupLeaderInFormation();
	AirStruc*		FindGroupLeaderClose();						  //RDH 23/06/99
	AirStruc*		FindGroupLeader();								  //RDH 03/03/99
	AirStrucPtr		FindABuddyWithPlayerGivenPriority();			  //RDH 04/03/99
	AirStrucPtr		FindABuddyNotPlayer();							  //RDH 20/05/99

	AirStrucPtr		FindBandit(int& count);									  //RDH 05/03/99
	AirStrucPtr		FindAnyBandit(SLong& range, int& count);			  //RDH 08/03/99
	AirStrucPtr		FindAcInGroup();						  //RDH 05/03/99
	bool			InSameWave(AirStruc* trg);	  //RDH 04/05/99
	AirStrucPtr	GetLeadAc();											//CSB 03/03/00
	bool		IsUnexpandedSAG();										//CSB 21/03/00
	bool	IsOutNumberedBy(FP factor = 1.0);							//CSB 31Jul00
	void	SetUnfriendly(AirStrucPtr newtrg = NULL);					//CSB 1Aug00
	Bool	ShouldGoHome();												//CSB 25Aug00
	Bool	GroupShouldGoHome(FP fract = 0.5);

	AirStrucPtr		FindBanditOnTail();
	void			SetGroupWP(WayPoint*	newwp);					  //RDH 09/03/99
	AirStruc*	AcShouldGoHome();									  //RDH 09/03/99
	void	AiLeaderBingoInstructions();
	void	SayEndPatrolFuel();
	void	PublicFireABullet(SWord delaybetweenbursts,Bool isArmed=TRUE); //RJS 27May99
	int		position() {return (formpos&InWingMAX);}
	void	MissionDiceThrow(WayPointPtr targetwp=NULL);


	AirStrucPtr ActivateACFromSag(GroupItterator& gi);
	void	PatchGroupAndAnim(ShapeNum shapetouse,int numactoenable);
	void	PatchGroupAndAnim(SingleFormation wingmanpos,SingleFormation leaderpos,int numinwing);
	void	PatchGroupAndAnim(SingleFormation wingmanpos,SingleFormation leaderpos);
	void	PatchGroupAndAnim(FormationTypeIndex formation);
	void	PatchGroupAndAnim()	{PatchGroupAndAnim(formation);}
	void	ContractSag(bool forcedcontract=false);
	AirStrucPtr	ExpandSag(bool forceexpand=false);
	void	TryToExpandSag(bool forced=false);
	void	PreExpandSags(int baseSAGshape);
//	Existing in chat.cpp	AirStruc* FindGroupLeader(AirStruc* ac)
	void	DestroySag();													//CSB 4Aug00
	Bool	SAGDeathSequenceOverride(AutoMoveCodeTypeSelect);
	void	RecycleAC();												//CSB 10Aug00
	int		SAGCountSquadronSize();										//CSB 20/03/00
	void	DoSAGChecks();												//CSB 26/05/00
	void	DoAllSAGChecks();											//CSB 1Aug00
	void	ClearUpAI();												//CSB 23Aug00
};

//SLong const 	MAXRPM			=	8192;



//
// Shapes: Now 2 parts to each shape... the shape data and the anim data
// There is only 1 instance of the shape data which all items share.
// There is 1 copy of the anim data for each item.
// This anim data may include weaponry records.
//

enum	ScaleType {SHP_1CM=0,SHP_4CM,SHP_16CM,SHP_GRP};			//PD 06Mar96


#endif


