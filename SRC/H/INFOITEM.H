////////////////////////////////////////////////////////////////////////
//
// Module:      infoitem.h
//
// Created:     17/12/98 by JIM
//
// Description: info_item variants of item
//
////////////////////////////////////////////////////////////////////////
#ifndef	INFOITEM_INCLUDED
#define	INFOITEM_INCLUDED
struct	info_event;
typedef	info_event* info_event_ptr;

////struct	info_debug
////{
////static int highestaddr,lowestaddr,numelts;
////
////	DES	~info_debug()
////		{numelts--;
//////	(*(char*)0xB0002)='d';
////		}
////	CON	info_debug()
////	{		if ((int)this<lowestaddr)
////				lowestaddr=(int)this;
////			if ((int)this>highestaddr)
////				highestaddr=(int)this;
////			numelts++;
//// //	(*(char*)0xB0002)='D';
////// 	(*(char*)0xB0004)='0';
////
////	}
////};
////
struct	info_event_suicide_ptr
{
	info_event_ptr p;
	info_event_suicide_ptr()
	{	p=NULL;
	}
	info_event_suicide_ptr(info_event_ptr q)	{p=q;}
	DES	~info_event_suicide_ptr();
	info_event* operator= (info_event_ptr q)				{return p=q;}
//	info_event_suicide_ptr& operator= (info_event_suicide_ptr& q)		{p=q.p;q.p=NULL;return *this;}
	operator info_event_ptr& ()					{return p;}
	info_event_ptr* operator & ()				{return &p;}
	info_event_ptr operator ->()				{return p;}
	Bool	operator== (int i)				{if (p)	return FALSE;else return TRUE; }
	Bool	operator!= (int i)				{if (p)	return TRUE;else return FALSE; }
};

struct	info_event
#ifdef	BFNUMBER_Included
	   //				:info_debug
{
	SWord	FrFighterSq,FrBomberSq,EnFighterSq,EnBomberSq;
	SWord	used_redac,used_blueac;
	SWord	used_redmob,used_bluemob;
	SWord	used_statics,used_waypoints;
	
	int	usedsetvals,allsetvals;
	info_event()	{	usedsetvals=allsetvals=0;
						used_redac=used_blueac=
							used_redmob=used_bluemob=
								used_statics=used_waypoints=0;
						FrFighterSq=FrBomberSq=EnFighterSq=EnBomberSq=0;
					}
	~info_event()	{usedsetvals=allsetvals=0;}
	EventVar	setvals[MAXEVENTS];
	EventVal	starth;
	EventVal	startm;
	EventVal	starts;
	EventVal	winh;
	EventVal	winm;
	EventVal	wins;
	EventVal	bfields;

	info_event_suicide_ptr next;


				
}
#endif
;

#ifdef	BFNUMBER_Included
inline DES	info_event_suicide_ptr::~info_event_suicide_ptr()
{
	delete p;
}
#endif
//////////////////////////////////////	//notes on whether saved in airgroups
structptr(info_base);
structptr(info_itemS);
structptr(info_waypoint);
structptr(info_grndgrp);
structptr(info_airgrp);
struct	EventVal;

#ifdef	BFNUMBER_Included
struct	info_base
					:hdgitem //changed from Item to allow "pointed" things.
{

///	UniqueID	SGT;	
	UWord	 	bfieldindex;			//no							//JIM 8Nov00
//DeadCode JIM 8Nov00 	UByte 		extra;					//no
EventVal	uid,						//not saved for aircraft	//negative for key waypoints
			position;					//not saved for aircraft
protected:
	info_base()	{SGT=UID_Null;(int&)Next=-1;bfieldindex=1023;}
public:
	enum	VisibilityConditionSlot	 {VCS_BEFORE=0,VCS_AFTER,VCS_ICON,VCS_TABLESIZE};
	enum	VisibilityCondition 
			{	VC_KNOWN=2,VC_DRAWN=4,VC_DRAWNLAST=1,
				VC_ALL=7,
				VC_REFRESHMASK=7,VC_DRAWMASK=6,	VC_NODRAW=2,
				VCW_HILIGHT=8
			};

};
					
struct	info_itemS
					:info_base//,info_debug
{
	info_event_suicide_ptr events;
EventVal	band,						//not set up	
			shape,						//not set up
			attitude;					//not set up
		info_itemS()	{Status.size=ITEMSIZE;}
	~info_itemS()
	{}
#ifndef __BCPLUSPLUS__
	VisibilityCondition	GetVC()
	{	return VisibilityCondition(Status.overview_BlueLaunch.value&VC_ALL);}
	VisibilityCondition	SetVC(VisibilityCondition newvc)	//returns old VC
	{	VisibilityCondition rv=VisibilityCondition(Status.overview_BlueLaunch.value&VC_ALL);
		Status.overview_BlueLaunch.value=(Status.overview_BlueLaunch.value&~VC_ALL)+newvc;
		return rv;
	}
	VisibilityCondition	ClearDraw()	//returns new VC
	{
		Status.overview_BlueLaunch.value&=~VC_DRAWN;
		return GetVC();
	}
	VisibilityCondition	SetDraw()	//returns new VC
	{
		Status.overview_BlueLaunch.value|=VC_DRAWN;
		return GetVC();
	}
	VisibilityCondition	SetKnown()	//returns new VC
	{
		Status.overview_BlueLaunch.value|=VC_KNOWN;
		return GetVC();
	}
	VisibilityCondition	ClearDrawLast()	//returns new VC
	{
		Status.overview_BlueLaunch.value&=~VC_DRAWNLAST;
		return GetVC();
	}
	VisibilityCondition	SetDrawLast()	//returns new VC
	{
		Status.overview_BlueLaunch.value|=VC_DRAWNLAST;
		return GetVC();
	}
	VisibilityCondition	UpdateDrawLast()	//returns new VC
	{
		VisibilityCondition currcond=GetVC();
		if (currcond&VC_DRAWN)
			SetDrawLast();
		else
			ClearDrawLast();
		return GetVC();
	}
#endif
};
#ifndef __BCPLUSPLUS__
enum	SavedGlobrefs;
#endif
struct	info_waypoint
					:info_base//,info_debug
{
	info_event_suicide_ptr events;
UniqueID	prevwp;
UniqueID	nextwp;
UniqueID	owner;
EventVal	useexistingWP;
EventVal
			etah,
			etam,
			etas,
			vel,
			target,
			wpact,
			applygroup,
			applyflight,
			applyelt,
			applywave,
			range;
Bool		rangeispercent;
#ifndef __BCPLUSPLUS__
	//
	//	Call with squadindex=-1 only to get main route only
	//	Call with squadindex only to get take-off/landing points
	//	Call with targetnum=0-9 to get target waypoints
	//	Call with targetnum=-1 to get escort patrol waypoints
	UniqueID	NextWP(int squadindex,int targetnum=0x80000000);
#endif
	info_waypoint()
	{	rangeispercent=FALSE;
		prevwp=nextwp=UID_Null;
		Status.size=WAYPOINTSIZE;
		vc[0]=vc[1]=vc[2]=0;
	}
	~info_waypoint()
	{
	}
	char	vc[VCS_TABLESIZE];
#ifndef __BCPLUSPLUS__
	VisibilityCondition	GetVC(VisibilityConditionSlot s)
	{	return VisibilityCondition(vc[s]);}
	VisibilityCondition	SetVC(VisibilityConditionSlot s,VisibilityCondition newvc)	//returns old VC
	{	VisibilityCondition rv=VisibilityCondition(vc[s]);
		vc[s]=newvc;
		return rv;
	}
	VisibilityCondition	SetKnown(VisibilityConditionSlot s)	//returns new VC
	{
		vc[s]|=VC_KNOWN;
		vc[VCS_ICON]|=VC_KNOWN;
		return GetVC(s);
	}
	VisibilityCondition	SetDraw(VisibilityConditionSlot s)	//returns new VC
	{
		vc[s]|=VC_DRAWN;
		vc[VCS_ICON]|=VC_DRAWN;
		return GetVC(s);
	}
	VisibilityCondition	ClearDraw(VisibilityConditionSlot s)	//returns new VC
	{
		vc[s]&=~(VC_DRAWN+VCW_HILIGHT);
		return GetVC(s);
	}
	VisibilityCondition	SetHilight(VisibilityConditionSlot s)	//returns new VC
	{
		vc[s]|=VC_DRAWN+VCW_HILIGHT;
		vc[VCS_ICON]|=VC_DRAWN+VCW_HILIGHT;
		return GetVC(s);
	}
	VisibilityCondition	ClearHilight(VisibilityConditionSlot s)	//returns new VC
	{
		vc[s]&=~VCW_HILIGHT;
		return GetVC(s);
	}
	VisibilityCondition	UpdateDrawLast(VisibilityConditionSlot s)	//returns new VC
	{
		VisibilityCondition currcond=GetVC(s);
		if (currcond&VC_DRAWN)
			SetDrawLast(s);
		else
			ClearDrawLast(s);
		return GetVC(s);
	}
	VisibilityCondition	ClearDrawLast(VisibilityConditionSlot s)	//returns new VC
	{
		vc[s]&=~VC_DRAWNLAST;
		return GetVC(s);
	}
	VisibilityCondition	SetDrawLast(VisibilityConditionSlot s)	//returns new VC
	{
		vc[s]|=VC_DRAWNLAST;
		return GetVC(s);
	}
#endif
};

struct	TargetConvoy;
struct	info_grndgrp
					:info_itemS
{
UniqueID	wpref;
EventVal	inform,						//saved
			form,						//saved
			nat,						//saved
			type,						//saved
			vel,						//not set up
			damage,						//never
			movecode,					//never
			leader;
		info_grndgrp()	{Status.size=MOBILESIZE;wpref=UID_NULL;}
		~info_grndgrp()	{}
		void	AutoFollowWP(TargetConvoy* c);
		int		CruiseToWp(int seconds,bool isescortfighter,bool ignorewaypointrange=false);
		bool	GetCruiseToWp(int seconds,bool escortfighter,bool ignorerange,
/*returned values*/					int& travel,info_waypoint* &wp,	WaypointOffsetSub& wos	);
		static void MoveConvoySAGs();
		int	GetCruiseAt(Coords3D& pos,ANGLES& pitchintercept=*(ANGLES*)NULL);  //returns cm per second...
		int	GetMinVel(int* getmaxaswell=NULL);  //returns cm per second...
		int	GetMinCruiseVel(int cruisevelin,int* getmaxaswell=NULL);  //returns cm per second...

};
struct	Profile;
#ifndef	__BCPLUSPLUS__
enum	IconsUI;
#endif
struct	info_airgrp
					:info_grndgrp
{
Profile*	package;
EventVal
			inwing,						//saved
			duty,						//saved
			skill,						//never
			morale,						//never
			character,					//never
			bombs,						//always
			target,						//never
			attacker,					//never
			follower,					//never
			homebase,					//never
			squadname,					//not set up
//new fields for mig alley:
			attmethod,					//NEED TO SAVE
			pattern,					//NEED TO SAVE
			radiosilence,				//NEED TO SAVE
			wpnum,
			applywave,
//
			paintrules[5];				//never
int			usedpaintrules;
//the following fields are used to maintain plot history...

#ifndef	__BCPLUSPLUS__
	Coords3D	knownposition;
	ANGLES		knownhdg;
	int			knowntime;
	int			lasttime;
	IconsUI		knownicon;
#endif
		info_airgrp()	{Status.size=AIRSTRUCSIZE;package=NULL;usedpaintrules=0;
#ifndef	__BCPLUSPLUS__
						 knownicon=IconsUI(0);
#endif
		}
	~info_airgrp()		{}
}
#endif
;
//DEADCODE DAW 08/03/00 struct	EventLog;
//DEADCODE DAW 08/03/00 typedef	EventLog	*EventLogPtr;
//DEADCODE DAW 08/03/00 
//DEADCODE DAW 08/03/00 struct	EventEntry
//DEADCODE DAW 08/03/00 {
//DEADCODE DAW 08/03/00  	ULong		launchtime;
//DEADCODE DAW 08/03/00 	enum		Stage											//RDH 01Dec96
//DEADCODE DAW 08/03/00 				{	EMPTY,UNSEEN,SEENBYOTHERS,ATTACKEDBYOTHERS,
//DEADCODE DAW 08/03/00 					SEENBYPLAYERS,HOSTILE,SPOTTEDDOGFIGHT,
//DEADCODE DAW 08/03/00 					APPROACHED,ATTACKED,DAMAGED,KILLED,TAKEOFF,     //RDH 01Dec96
//DEADCODE DAW 08/03/00 					BENTWING,FATALCRASH,CRASHLAND,CRASHLANDTOOFAST,
//DEADCODE DAW 08/03/00 					LANDOK,LANDOKATHOME,MIDAIRCOLLISION,
//DEADCODE DAW 08/03/00 					DAMAGEDSTATIC,DAMAGEDTRUCK,KILLEDSTATIC,KILLEDTRUCK,
//DEADCODE DAW 08/03/00 					PARACHUTED,
//DEADCODE DAW 08/03/00 				};                                               //RDH 01Dec96
//DEADCODE DAW 08/03/00 	ONLYFIELD(UByte,Stage,stage);
//DEADCODE DAW 08/03/00 	UByte		hits;	//kills for air groups... hits for damaged ground
//DEADCODE DAW 08/03/00 	UByte		losses;
//DEADCODE DAW 08/03/00 	UByte		encsize;
//DEADCODE DAW 08/03/00 
//DEADCODE DAW 08/03/00 	UWord		place;
//DEADCODE DAW 08/03/00 	ONLYFIELD(UWord,UniqueID,homebase);
//DEADCODE DAW 08/03/00 	ONLYFIELD(UByte,PlaneTypeSelect,encounteredtype);
//DEADCODE DAW 08/03/00 	ONLYFIELD(UByte,PlaneTypeSelect,escorttype);
//DEADCODE DAW 08/03/00 	
//DEADCODE DAW 08/03/00 };
#endif
