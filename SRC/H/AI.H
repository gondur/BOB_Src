//------------------------------------------------------------------------------
//Filename       ai.h
//System         
//Author         Jim Taylor
//Date           Tue 28 May 1996
//Description    artificial stupidity....
//------------------------------------------------------------------------------
#ifndef	AI_Included
#define	AI_Included
//DEADCODE MS 31/01/00 #ifndef	__BCPLUSPLUS__
//DEADCODE MS 31/01/00 #include	"rchatter.h"
//DEADCODE MS 31/01/00 #else
//DEADCODE MS 31/01/00 	typedef	int	PhraseTables;
//DEADCODE MS 31/01/00 #endif
#ifndef	__BCPLUSPLUS__
enum	PhraseTables;
enum	ScriptTables;
enum	MsgType;
#else
typedef	int	PhraseTables,ScriptTables,MsgType;
#endif

#define	DEFAULT_AI 0
#define	FRAMES_PER_SPOT 5

class	AirStruc;
//fake class interface between derivatives of ArtInt
class	MESSAGE_STRUC;
class	DecisionAI													  //JIM 22/01/99
{
public:
struct	OptionRef													  //JIM 22/01/99
{
	PhraseTables	optionmsg;		//this is printed in user alternatives. If null use saidmsg
	DecisionAI**	airesult;		//next user choice table	If null do nowt
	int	saidmsg;		//the message to say. If null say nowt. Recipient will respond anyway?
};
																  //JIM 22/01/99
	bool	UserMsgDecision(AirStrucPtr callee,ItemBasePtr trg,			  //JIM 22/01/99
		AirStrucPtr caller,ArtInt* artint,MESSAGE_STRUC* PriorityMessage);
	virtual OptionRef*	GetMsgOptions()=NULL;								  //JIM 22/01/99
	virtual	bool													  //JIM 22/01/99
		AutoMsgDecision(AirStrucPtr callee,ItemBasePtr trg,			  //JIM 22/01/99
		AirStrucPtr caller,ArtInt* artint,MESSAGE_STRUC* PriorityMessage=NULL)=0;						  //JIM 22/01/99
    #ifndef	__BCPLUSPLUS__
	PhraseTables GetDefaultPhrase(AirStrucPtr callee,ItemBasePtr trg);// {return PHRASE_CONTINUE;}
    #endif
	enum	{OPTIONTABLEMAX=100};
	static DecisionAI* optiontable[OPTIONTABLEMAX];
	static int optiontablemax;
	int		optionnumber;
	DecisionAI()	{optiontable[optionnumber=++optiontablemax]=this;}
};																	  //JIM 22/01/99



class	ArtInt
{
	friend	struct	AcArrayItterator;
	friend 	class	TrgListProc;
	friend	class	Replay;										//DAW 28Jun99
	friend	class	DPlay;										//DAW 28Jun99
	friend	class	Inst3d;
	friend 	class	AirStruc;											//CSB 10/03/00
	friend 	class	MoveAirStruc;											//CSB 10/03/00
	friend	struct	SleepList;											//CSB 20/03/00
	int		spotcount;
//DEADCODE CSB 02/02/00 	enum	{ACARRAYSIZE = 256,	MEMBERLISTSIZE = 4};				  //CSB 01/02/00
	enum	{ACARRAYSIZE = 128,	MEMBERLISTSIZE = 4,	COLLIDECHECKLISTSIZE = 16,	COLLIDEAGAINSTLISTSIZE = 32};				  //CSB 01/02/00
	static	AirStruc*	ACArray[ACARRAYSIZE];
	static	AirStrucPtr	MemberList[MEMBERLISTSIZE];					  //CSB 01/02/00
	static	float		Dist2List[MEMBERLISTSIZE];					  //CSB 02/02/00

	static	AirStrucPtr	CollideCheckList[COLLIDECHECKLISTSIZE];
	static	AirStrucPtr	CollideAgainstList[COLLIDEAGAINSTLISTSIZE];
protected:
	int		gunstimer;
	enum	tGroupLevel {GROUP_LONER, GROUP_ELEMENT, GROUP_FLIGHT, GROUP_SQUADRON};
	enum	UnitSize {UNIT_VOID,	UNIT_RAF_WING,	  UNIT_RAF_SQUADRON, UNIT_RAF_FLIGHT,   UNIT_RAF_SECTION, UNIT_RAF_SINGLE,
			   UNIT_LUF_GESCHWADER, UNIT_LUF_GRUPPEN, UNIT_LUF_STAFFEL,	 UNIT_LUF_SCHWARME, UNIT_LUF_ROTTE,	  UNIT_LUF_SINGLE};
public:
	int		exittimer;
	DecisionAI*	blocking;
	ArtInt()	{blocking=NULL;}
	ViewPoint*	View_Point;
	int		ACArrayInd;
	int		MemberListInd;											  //CSB 01/02/00
	int		CollideListInd;											  //CSB 03/02/00
//DeadCode AMM 20Oct100 	int		GetGroundSpotter(ItemPtr trg);	//returns UID of potential spotter
	UniqueID	GetSecondarySpotter(Coords3D& trg,UniqueID primary,int slot);
	UniqueID	GetSecondarySpotter(Coords3D& trg,UniqueID primary);//ALL SLOTS
	int		GroundVisible(Coords3D& trg,int* failedspotter);		//returns UID of spotter if spotted
	int		GroundVisible(ItemPtr trg,int* failedspotter)	{return  GroundVisible(trg->World,failedspotter);}
	int		GroundVisible(ItemPtr trg)	{int dummy;return GroundVisible(trg,&dummy);}
//DeadCode AMM 20Oct100 	void	SpottedFromGround( AirStruc* trg);
	bool	Add(AirStruc*);
	bool	Remove(AirStruc*);
	bool	Visible(AirStruc*,AirStruc*);
	bool	Seen(AirStruc*	eye,AirStruc*	trg);
	void	VisibleCheck();
	void	CollisionCheck();										  //CSB 03/02/00
	void	MakeCollisionLists();									  //CSB 03/02/00
	void	CollisionAvoidance(AirStrucPtr ac1, AirStrucPtr ac2);
	void	ArtInt::VisibleAcCheck();
	void	ArtInt::MakeMemberList(AirStrucPtr ac);
	void	ArtInt::AddToMemberList(AirStrucPtr eye, AirStrucPtr ac, float dist2);	  //CSB 02/02/00
//DeadCode AMM 20Oct100 	void	ArtInt::ProcessWPEvents();
//DeadCode AMM 20Oct100 	void	ArtInt::LaunchMiGs(AirStruc* trg,tAggressionLevel al);
//DeadCode AMM 20Oct100 	void	ArtInt::VisibleContrailsCheck();
	void	ArtInt::VisibleAAACheck();
//DeadCode AMM 20Oct100 	void	ArtInt::SpottedContrails(AirStruc* eye,AirStruc* trg);
//DeadCode AMM 20Oct100 	void	ArtInt::SpottedOldContrails(AirStruc* eye,AirStruc* trg);
	bool	ArtInt::AlertFighters(AirStruc* eye,AirStruc* trg, AirStruc* friendlythatneedshelp);
	void ArtInt::InterceptRangeFromTo(AirStruc* from, AirStruc* to);
	SLong ArtInt::RangeFromTo(AirStruc* from, AirStruc* to);
//DeadCode AMM 20Oct100 	bool ArtInt::AcHasBombs(AirStruc* trg);
//DeadCode AMM 20Oct100 	bool ArtInt::ForceHasBombers(AirStruc* trg);
//DeadCode AMM 20Oct100 	bool ArtInt::BingoFuel(AirStruc* trg);
//DeadCode AMM 20Oct100 	bool ArtInt::Winchester(AirStruc* trg);
	void ArtInt::ResetUnfriendly();
	bool ArtInt::LeaveTopCover(AirStruc* caller, AirStruc* trg);	  //CSB 21/01/00
 	bool ArtInt::EngageFormation(AirStrucPtr caller, AirStrucPtr trg);	  //CSB 21/01/00
 	bool ArtInt::EngageTrg(AirStrucPtr caller, AirStrucPtr trg);	  //CSB 21/01/00
 	bool ArtInt::MeBombersYouFighters(AirStrucPtr caller, AirStrucPtr trg);	  //CSB 21/01/00
 	bool ArtInt::MeFightersYouBombers(AirStrucPtr caller, AirStrucPtr trg);	  //CSB 21/01/00

//DeadCode AMM 20Oct100 	void	ArtInt::GroupEngage(AirStruc* caller,AirStruc* trg);
	tGroupLevel ArtInt::GroupLevel(AirStruc* caller);
	tGroupLevel ArtInt::GroupLevelNotInFormation(AirStruc* caller);	  //RDH 10/05/99

//DeadCode AMM 20Oct100 	void	ArtInt::DefensiveSplitHiLo(AirStruc* caller,AirStruc* caller2,AirStruc* trg);
//DeadCode AMM 20Oct100 	void	ArtInt::ChooseSplitManoeuvre(AirStruc* caller,AirStruc* caller2,AirStruc* trg);
//DeadCode AMM 20Oct100 	void	ArtInt::SetUpPincer(AirStruc* caller,AirStruc* caller2,AirStruc* trg);
	void	ArtInt::SetUpRemainderOfGroupToEngage(AirStruc* caller,AirStruc* trg,MANOEUVRE manoeuvre,ANGLES desiredhdg,ANGLES  desiredpitch, bool TRUE);
//DeadCode AMM 20Oct100 	bool	ArtInt::MakeForceToRespond (AirStruc* caller, AirStruc* trg, tGroupLevel group, bool& splitmanappropriate);
//DeadCode AMM 20Oct100 	bool	ArtInt::TrgIsVulnerable(AirStruc* caller, AirStruc* trg);

//DeadCode AMM 20Oct100 	void	ArtInt::SubsequentIDasUnfriendly(AirStruc* caller,AirStruc* trg);
//DeadCode AMM 20Oct100 	void	ArtInt::InCombatWithoutUnfriendly(AirStruc* caller,AirStruc*  trg);
//DeadCode AMM 20Oct100 	void	ArtInt::SetRoundAboutAc(AirStruc*  ac);
//DeadCode AMM 20Oct100 	AirStruc* FreeUpAFlight(AirStruc* caller, AirStruc*  currtrg);
//DeadCode AMM 20Oct100 	AirStruc* FindFreeFlight(AirStruc* caller);
	AirStruc* FindEscort(AirStruc* caller);
    #ifndef __BCPLUSPLUS__
	ScriptTables BreakCall(AirStrucPtr caller, AirStrucPtr callee, AirStrucPtr agg);			  //CSB 08/02/00
	#endif
	void	DefensiveSplit(AirStruc* caller,AirStruc* trg, ANGLES leftpitch,ANGLES rightpitch);
	bool	ChooseManoeuvre(AirStruc* caller,AirStruc* trg, bool newspot);
#ifndef     __BCPLUSPLUS__
	MESSAGE_STRUC	ChooseBanditRelMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot);
	MESSAGE_STRUC	ChooseBanditOnTailMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot);
	MESSAGE_STRUC	ChooseBanditHeadOnMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot);
#endif
//DeadCode AMM 20Oct100 	bool		EyeIsAndTrgIsNotInPlayersGroup(AirStruc* caller,AirStruc* trg);
	bool		EngageAppropriate(AirStruc* caller,AirStruc* trg);
//DeadCode AMM 20Oct100 	bool		Escorting(AirStruc* ac);


	bool CallerOnRight(AirStruc* ac,AirStruc* trg);					  //RDH 18/02/99
	void SwitchCallerToLeft(AirStruc*& caller, AirStruc*& callee);

	void FindGroupAndLeader2(AirStruc*& caller, AirStruc*& caller2,tGroupLevel& group);

	ANGLES HdgIntFromTo(AirStruc* ac,AirStruc* trg);
	bool	ArtInt::TargetOnCallerTail(AirStruc*  caller,AirStruc*  trg,ANGLES angle);
//DeadCode AMM 20Oct100 	bool	ArtInt::CallerOnTargetTail(AirStruc*  caller,AirStruc*  trg,ANGLES angle);

	bool	ArtInt::TargetFacingCaller(AirStruc*  caller,AirStruc*  trg,ANGLES angle);
//DeadCode AMM 20Oct100 	bool	ArtInt::CallerFacingTarget(AirStruc*  caller,AirStruc*  trg,ANGLES angle);
	AirStrucPtr	ArtInt::SetFollowerEngage(AirStrucPtr eye,AirStrucPtr trg,MANOEUVRE  manoeuvre,ANGLES desiredhdg,ANGLES  desiredpitch, bool surprised);
//DeadCode AMM 20Oct100 	AirStrucPtr	ArtInt::SetFlightEngage(AirStrucPtr eye,AirStrucPtr trg,MANOEUVRE  manoeuvre,ANGLES desiredhdg,ANGLES  desiredpitch, bool surprised);


//DeadCode AMM 20Oct100 	bool	DoesFriendNeedHelp(AirStruc* eye,AirStruc* trg);
//DeadCode AMM 20Oct100 	bool	SpottedNeutral(AirStruc* eye,AirStruc* trg);
	bool	SpottedUnfriendly(AirStruc* eye,AirStruc* trg);
//DeadCode AMM 20Oct100 	bool	SpottedUnknown(AirStruc* eye,AirStruc* trg);
//DeadCode AMM 20Oct100 	bool	SpottedNewUnfriendly(AirStruc* eye,AirStruc* trg);
	ScriptTables ChooseSpottedScript(AirStrucPtr caller, AirStrucPtr trg); //CSB 08/02/00
	bool	AttackSpareInLeadersGroup(AirStruc* eye);				  //RDH 13/06/99
//DeadCode AMM 20Oct100 	bool	LeadersGroupInCombat(AirStruc* eye);

	void	ArtInt::SetEngage(AirStrucPtr eye,AirStrucPtr trg,MANOEUVRE manoeuvre,ANGLES   desiredhdg,ANGLES   desiredpitch, bool surprised);
	void	ArtInt::PrepareForCombat(AirStrucPtr caller);			  //RDH 04/03/99

	int		CountFormationSize(AirStrucPtr);
	int		CountSquadronSize(AirStrucPtr);							  //CSB 20/01/00
	int		GuessFormationSize(AirStrucPtr,AirStrucPtr);
	bool	SameFlight(AirStrucPtr a,AirStrucPtr b);			//DAW 30Jun96
	void	SetPreEngage(AirStrucPtr eye,AirStrucPtr trg);
	AirStrucPtr	SetFollowerPreEngage(AirStrucPtr eye,AirStrucPtr trg);	//returns last targ
	AirStrucPtr	SetFlightPreEngage(AirStrucPtr eye,AirStrucPtr trg);	//returns last targ
	AirStrucPtr	SetFollowerWhoCanEngage(AirStrucPtr eye,AirStrucPtr trg);	//returns last targ
	AirStrucPtr	SetFlightWhoCanEngage(AirStrucPtr eye,AirStrucPtr trg);	//returns last targ
	AirStrucPtr	nextfl(AirStrucPtr trg,bool unassigned=TRUE);
	AirStrucPtr	nextfol(AirStrucPtr trg,bool unassigned=TRUE);
	bool	AircraftAreClose(AirStrucPtr trg, AirStrucPtr foll);

	void	AllBreakOff(AirStrucPtr leadac);
	void	BreakOff(AirStrucPtr ac);
	void	AllEngage(AirStrucPtr leadac);
	void	ClearFollowerFormation(AirStrucPtr	eye);
	void	CleanUp();
	void	PlayerHitConvoy(FormationItemPtr);
	bool	OkToAccel();
	bool	PersonalThreat(AirStrucPtr trg,AirStrucPtr agg, bool process=FALSE);
	void	PersonalThreatMsg(AirStrucPtr trg,AirStrucPtr agg);
	MANOEUVRE ChooseEvasiveManoeuvre(AirStrucPtr trg, AirStrucPtr agg);
	void	DisEngageAll(AirStruc* caller, MESSAGE_STRUC* prioritymessage);	
	void	AllChangeMovecode(AirStrucPtr leadac, AirStrucPtr trg, AutoMoveCodeTypeSelect movecode);
	AirStrucPtr SplitUnit(AirStrucPtr ac, UnitSize& unitsize);
	AirStrucPtr FindTailie(AirStrucPtr ac);								//CSB 13/03/00
	bool	CanAttackType(AirStrucPtr ac, AirStrucPtr trg);				//CSB 21/03/00
		
	bool	SendMsgAndCall(const MESSAGE_STRUC& msg,DecisionAI* processor);
	void	ArtInt::ExpandMigs(AirStrucPtr placeholder);
	void	ArtInt::ReallyExpandMigs(AirStrucPtr placeholder);

};
extern	ArtInt	Art_Int;

//////////////////////////////////////////////////////////////////////
//
// Class:		AcArrayItterator
// Date:		18/05/99
// Author:		RDH
//
//Description: 
//		An AcArrayItterator object pretends to be an AirStrucPtr
//		However, it has a member function .Next()
//		which moves it through the ArtInt::ACArray
//		When the end of the array is reached .Next() returns 'false'
//		This array can contain 'random' NULL entries
//
//////////////////////////////////////////////////////////////////////
struct	AcArrayItterator
{
	AirStrucPtr		THISTHIS;
	AirStrucPtr*	THISTHIS2;
	int	index;
	AcArrayItterator()	
	{index=-1;THISTHIS2=Art_Int.ACArray-1;THISTHIS=NULL;}
	bool	Next()		//true means there is a next one
	{	
		index++;
		THISTHIS2++;
		if (index<ArtInt::ACARRAYSIZE)
		{
			THISTHIS=*THISTHIS2;
			return true;
		}
		else
		{
			THISTHIS=NULL;
			return false;
		}
	}
	operator bool()	{return THISTHIS!=NULL;}
	operator int()	{return THISTHIS!=NULL;}
	operator AirStrucPtr()	{return THISTHIS;}
	AirStrucPtr operator->()	{return THISTHIS;}
};



#define	EXTERNAI(name,trgtype)	extern	DecisionAI*	name;

//Decisions are lumps of AI code that can be bypassed by the player
//and lead to Options. Decisions can be used as Options.

#define	DECISIONAI(name,trgtype)										\
class	trgtype##_##name##_AI:public ArtInt							 \
{																		  \
public:																	   \
  bool	name(AirStrucPtr eye,trgtype trg,AirStrucPtr sender,				\
					DecisionAI* currdecision,MESSAGE_STRUC* PM);			 \
};																			  \
class	trgtype##_##name:public	DecisionAI								 \
{																			  \
	static OptionRef opts[];													   \
public:																			\
	OptionRef*	GetMsgOptions() {return opts;}										 \
	bool	AutoMsgDecision(AirStrucPtr eye,ItemBasePtr trg,					  \
					AirStrucPtr sender,ArtInt* artint,MESSAGE_STRUC* PM)							   \
	{	return	((trgtype##_##name##_AI*)artint)->name(							\
							eye,(trgtype)*trg,sender,this,PM);}						 \
};																					  \
EXTERNAI(name,trgtype)


#define	OPTIONAI(name,trgtype)											\
class	trgtype##_##name##_AI:public ArtInt							 \
{																		  \
public:																	   \
  bool	name(AirStrucPtr eye,trgtype trg,AirStrucPtr sender,				\
					DecisionAI* currdecision,MESSAGE_STRUC* PM);			 \
};																			  \
class	trgtype##_##name:public	DecisionAI								 \
{																			  \
public:																			\
	OptionRef*	GetMsgOptions() {return NULL;}										 \
	bool	AutoMsgDecision(AirStrucPtr eye,ItemBasePtr trg,					  \
					AirStrucPtr sender,ArtInt* artint,MESSAGE_STRUC* PM)		   \
	{	return	((trgtype##_##name##_AI*)artint)->name(							\
							eye,(trgtype)*trg,sender,this,PM);}						 \
};																					  \
EXTERNAI(name,trgtype)

#define	TABLEAI(name,trgtype)							 \
DecisionAI::OptionRef	trgtype##_##name::opts[]	=
//Write body of option table here!
//{
//	{PHRASE_,	&DecisionAI,	SCRIPT_},
//	{PHRASE_,	&DecisionAI,	SCRIPT_},
//};

#define	INSTANCEAI(name,trgtype,options)							 \
trgtype##_##name	trgtype##_inst_##name;							  \
DecisionAI*	name=	&trgtype##_inst_##name;								\
bool	trgtype##_##name##_AI::name(AirStrucPtr callee,trgtype trg,AirStrucPtr caller,DecisionAI* currdecision,MESSAGE_STRUC* prioritymessage)
//Write the body of the decision routine here!
//{
//
//	return	true; //if handled. false if no child message
//}


EXTERNAI(DoNothing,AirStrucPtr);
EXTERNAI(TestGuns,AirStrucPtr);
EXTERNAI(RealTestGuns,AirStrucPtr);
EXTERNAI(SetupQuitContinue,AirStrucPtr);
EXTERNAI(SecretMessages,ItemPtr);

//DEADCODE CSB 11/02/00 EXTERNAI(JettisonStores,AirStrucPtr);
//DEADCODE CSB 11/02/00 EXTERNAI(JettisonTanks,AirStrucPtr);
//DEADCODE CSB 11/02/00 EXTERNAI(DoNothing,AirStrucPtr);
//DEADCODE CSB 11/02/00 EXTERNAI(TestGuns,AirStrucPtr);
//DEADCODE CSB 11/02/00 EXTERNAI(AllDisengage,AirStrucPtr);
//DEADCODE CSB 11/02/00 EXTERNAI(Rendezvous,AirStrucPtr);
//DEADCODE CSB 11/02/00 EXTERNAI(SecretMessages,ItemPtr);
//DEADCODE CSB 11/02/00 EXTERNAI(PreCombatMsg,ItemPtr);
//DEADCODE CSB 11/02/00 EXTERNAI(FACMsg,ItemPtr);	enum	{FAC_BombsAway=6};
#endif
