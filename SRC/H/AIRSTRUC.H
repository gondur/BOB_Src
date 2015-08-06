//////////////////////////////////////////////////////////////////////
//
// Function:    
// Date:		08/12/99
// Author:		JIM
//
//Description: Dummy subclasses of AirStruc for standard movement
//			   The main airstruc is defined in "worldinc.h"
//
//				THESE SUBCLASSES MUST NOT CONTAIN DATA FIELDS
//				They should only contain functions
//				They can contain static data if you must
//
//////////////////////////////////////////////////////////////////////
#ifndef	AIRSTRUC_INCLUDED
#define	AIRSTRUC_INCLUDED
#pragma once
class	ACMAirStruc:public	AirStruc
{
	friend	struct SAGAirstruc;										  //CSB 20/12/99
	friend	class MoveAirStruc;
	friend	class AirStruc;
	friend	class TransObj;

	void SimpleACM();	
	void ManualACM();

	void SelectNextEngageManoeuvre();									//RDH 12Mar96
	void	SetACMType();											  //RDH 26/03/99
	void	ChooseRadioMessage();							  //RDH 04/03/99
	void SelectNextEvadeManoeuvre();									//RDH 12Mar96

	ANGLES ActualLead(AirStrucPtr  subjt, AirStrucPtr trgt);
	void FrightenBogie();						//rdh 17/12/98
	void SelectNextTwoSeaterManoeuvre ();				//RDH 19Nov96
	void TwoSeaterDefence();										//RDH 19Nov96

//ACM member functions
//DEADCODE RDH 21/02/99 	void	MoveToHdg (ANGLES);
	void	MoveToHdg (ANGLES desiredhdg, ANGLES desiredpitch);		  //RDH 21/02/99
 
	void	MoveToHdgOnThisRoll (ANGLES,ANGLES);
	void	MoveToAoA (ANGLES);
	void	MoveToRudder (SWord);
	void	MoveToSlip (ANGLES);
	void	MoveToPitch (ANGLES,SWord);
	void	MoveToAcPitch (ANGLES);
	SWord	MoveToDesiredPitch (ANGLES,ANGLES);
	SWord	DesiredPitchChk (ANGLES,ANGLES);
	SWord	DesiredAcPitchChk (ANGLES,ANGLES);					//RDH 01Nov96
//DEADCODE RDH 21/02/99 	Bool	MoveToDesiredHdg (ANGLES,ANGLES);
	Bool	MoveToDesiredHdg (ANGLES desiredhdg,ANGLES desiredpitch,ANGLES target);

	Bool	ChkAtDesiredHdg (ANGLES,ANGLES);						//RDH 01Apr96
	Bool	ChkAtDesiredAcHdg (ANGLES,ANGLES);					//RDH 01Nov96
	Bool	ChkAtDesiredRoll (ANGLES desiredroll,ANGLES target);

	SWord	MoveToDesiredHdgOnThisRoll (ANGLES,ANGLES,ANGLES);
	void	ClimbAtBestSpeed ();
	void	MoveToRoll (SWord,SWord);
//DeadCode RDH 05Jan99 	void	TightClimbingTurn (ANGLES);
	void	MoveToThrust (SWord);
	void	SimpleMoveToThrust (SWord);							//RDH 11Oct96
	void	SimpleCalcVel ();
	SWord 	ManoeuvreTimeLeft ();
	bool	WeldedWingSixOK();
	bool	BreakCallNecessary(AirStrucPtr currac,AirStrucPtr unf, int range);

//DeadCode RDH 05Jan99  	void	TightTurn (SLong recovery_alt);					//RDH 12Jul96
 	void	AutoShoot (Bool manual);							//RDH 22Oct96
	void	SplitS ();
	void	ZoomandDrop ();
	void	StandOnTail ( );
	void	GainHeight ( );
	void	ShootToFrighten ( );
	void	DiveAndZoom ( );
	void	FlatTurn ();										//RDH 28Mar96
	void 	GainSpeed();										//RDH 27Apr98
	void 	LookAround ();										//RDH 19Aug96
	void	WeldedWingMan();
	void	BailOut();
	void 	TopCover ();										//RDH 19Aug96
	void 	ForceTopCover();											//CSB 09/03/00
	void	LineAbreast();
	void	Scatter();
	void	Pincer();
	void	MultiWave();

//rdh	void	DiveAndZoom ();
	void	LeadPursuit();
	void	LagPursuit();
	void	Circumvent();
//	void	DecoyActive();
//	void	DecoyPassive();
	void	RoundAbout();
	void	SplitManoeuvre();
	void	ResetUnfriendly();
	void	HeadOn ( );
	void	LineAstern();
	void	VicAttack();
	void ShootTooEarly();

	void	LagRoll();
	void	ExtensionManoeuvre();
	void	DivingSpin();
	void	ReverseTurn();
	void	SelfAsBait();
	void	Jink();
	void	BreakTurn();
	void	LazyTurn();
	void	Break180();
	void	BreakLow();
	void	BreakHigh();
	void	Break90();
	void	HiGBarrelRoll();
	void	PanicTurn();
	void	UnBalancedFlight();
//	void	TrackingShot();
	void	LowAlt();
	void	SnapShot();
	void	StayOnTail();
	void	HeadOnAttack();
	void	Lufberry();									  //CB 18/11/99
	void	SteepDive();									  //CB 18/11/99
	void	UpAndUnder();									  //CB 18/11/99
	void	StallTurn();									  //CB 18/11/99
	void	SlashingAttack();								  //CB 18/11/99
	void	ClimbTurn();									  //CB 18/11/99
	void	Roll360();									  //CB 18/11/99
	void	Straffe();									  //CB 18/11/99
	void	PeelOff();
	void	FlyThroughCloud();										  //CSB 10/01/00
	void	Regroup();										  //CSB 10/01/00


//DeadCode AMM 21Sep00 	Bool	TurnToHdgAndPitch();
//DeadCode RDH 07Jan99 	void	HotSideLagPursuitFight();
//DeadCode RDH 07Jan99 	Bool	SandwichManoeuvres();
//	SWord	RollforTurn(SWord reqdeltapitch,SWord deltahdg, Float& desiredturn);
	SWord	RollforTurn(SWord reqdeltapitch,SWord deltahdg, Float& desiredturn,COORDS3D	target);
//DeadCode AMM 21Sep00 	void		CalcDesiredPitchRate(SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos);
	FP		CoarseRollAdjust(FP rroll, FP fpitch);
	FP		FineRollAdjust(SWord reqdeltapitch,SWord deltahdg,FP rroll, FP fpitch, FP fhdg);
//DeadCode AMM 21Sep00 	Bool	UnfriendlyOnSameRoll();


//DeadCode RDH 07Jan99 	void	SustainedTurn();
	void	TurningFight();
	void	TurningFightBomber();
//	void	CalcLead(SWord& velx,SWord& vely,SWord& velz);
//	void	CalcLead(AirStrucPtr  subject, AirStrucPtr target, SWord& velx,SWord& vely,SWord& velz);
	void	CalcLead(AirStrucPtr  subject, AirStrucPtr target, SLong& velx,SLong& vely,SLong& velz, Bool cutcorner);

//	void	TurnFightSub(ANGLES	HdgIntercept);
//	void	TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch);
	void	TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target);
	void	TurnFightPhase1(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target);

//	void	TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget);
	void	SlowDownCheck(UWord reqdeltahdg_pos);
	void	SlowDown(FP velc);
//DeadCode AMM 21Sep00 	void	SpeedUp(FP velc);

	SWord	ThrustfromFF();


//	void	TurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget);
	void	TurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target);

	void	HighYoYo();
	void	Zoom();
//DeadCode AMM 21Sep00 	void	LowYoYo ( );
	void	TurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign,UWord	reqdeltapitch_pos, ANGLES	deltapitch);
	void	RollAndPull(SWord	reqdeltahdg, SWord dpitch);

	void	InterceptHigh();
	void	InterceptLow();
//DeadCode AMM 21Sep00 	void	ClimbAtSustainedTurnSpeed();
	
	Bool	BanditOnColdSide();
//DeadCode AMM 21Sep00 	Bool	BanditHasLead();

	Bool 	AllOnTopCover ();										//RDH 19Aug96
	Bool	AllButLdrNotOnCombat ();								//RDH 11Nov96
	void	BarrelRollAttack ( );
	void	Scissors ( );
	void	MildScissors ( );
	void	StraightandLevel ( );
//DeadCode RDH 30Mar98 	void	AcmSideSlip ( );
	void	SpinOut ( );
	void	DiveforHome ( );
	void	ClimbforHome ( );
	void	StraightDive ( );
	void	GoHome ( );
	void	MakeForFriendly ( );
	void	MoveAway ( );
//DeadCode RDH 06Jan99 	void	AccidentalSpinOut ( );
	void	SpinRecovery ( );								//RDH 21Aug96
//rdh	void	TurningFight ( );
	void	LowGYoYo ( );
	void	RollAway ( );
//DeadCode RDH 07Jan99 	void	VerticalLoop ( );
	void	ImmelmannTurn ( );
	void	HeadOnOffset ( );
	void	Immelmann ( );
	void	StayWithPrey ( );
//DeadCode RDH 05Jan99 	void	GatherSpeed ();
//DeadCode AMM 21Sep00 	void	LeadUnFriendly ();
	void	CollisionAvoidance();									  //CSB 03/02/00
	void FlyWing(AirStrucPtr lead, ANGLES relhdg, int dist);										//CSB 15/03/00


	Float	CalcSimpleAccel ();

	void	SimpleLowAlt();											  //RDH 25/05/99

	void	SimpleTurningFight();
	void	SimpleTurningFightBomber();
	void	SimpleTurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target);
	void	SimpleTurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target);
	void	SimpleTurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos, ANGLES	deltapitch);

	void	SimpleWeldedWingMan();
	void	SimpleBailOut();
	void	SimpleLineAbreast();
	void	SimpleScatter();
	void	SimplePincer();
	void	SimpleMultiWave();
	void	SimpleDiveAndZoom ();
	void	SimpleLeadPursuit();
	void	SimpleLagPursuit();
	void	SimpleCircumvent();
//	void	SimpleDecoyActive();
//	void	SimpleDecoyPassive();
	void	SimpleRoundAbout();
	void	SimpleSplitManoeuvre();
	void	SimpleHeadOn ( );
	void	SimpleLineAstern();
	void	SimpleVicAttack();
	void SimpleShootTooEarly();
	void	SimpleLagRoll();
	void	SimpleExtensionManoeuvre();
	void	SimpleDivingSpin();
	void	SimpleReverseTurn();
	void	SimpleSelfAsBait();
	void	SimpleJink();
	void	SimpleBreakTurn();
	void	SimpleLazyTurn();
	void	SimpleBreak180();
	void	SimpleBreakLow();
	void	SimpleBreakHigh();
	void	SimpleBreak90();
	void	SimpleHiGBarrelRoll();
	void	SimplePanicTurn();
	void	SimpleUnBalancedFlight();
	void	SimpleTrackingShot();
	void	SimpleSnapShot();
	void	SimpleStayOnTail();
	void	SimpleHeadOnAttack();
	void	SimpleLufberry();
	void	SimpleSteepDive();
	void	SimpleUpAndUnder();
	void	SimpleStallTurn();
	void	SimpleSlashingAttack();
	void	SimpleClimbTurn();
	void	SimpleRoll360();
	void	SimpleStraffe();
	void	SimplePeelOff();
	void	SimpleFlyThroughCloud();
	void	SimpleRegroup();
	void	SimpleDisengaged();
	void	SimpleImGoingHome();
	void	SimpleCollisionAvoidance();
	void	SimpleCollide();
	
	Bool	SimpleTurnToHdgAndPitch();
	void	SimpleHotSideLagPursuitFight();
	Bool	SimpleSandwichManoeuvres();
	void	SimpleSustainedTurn();
	void	SimpleHighYoYo();
	void	SimpleZoom();
	void	SimpleLowYoYo ( );
	void	SimpleInterceptHigh();
	void	SimpleInterceptLow();
	void	SimpleClimbAtSustainedTurnSpeed();
	void	SimpleMakeForFriendly();
	void	SimpleImmelmann();
	void	SimpleGainSpeed();									//RDH 27Apr98

	void	SimpleGatherSpeed ();
	void	SimpleLeadUnFriendly ();
	void	SimpleSplitS ();
	void	SimpleZoomandDrop ();
//rdh	void	SimpleDiveAndZoom ( );
	void	SimpleGainHeight ( );
	void 	SimpleTopCover ();
	void 	SimpleForceTopCover ();
	void 	SimpleLookAround ();
	void 	SimpleBarrelRollAttack ( );
	void 	SimpleScissors ( );
	void 	SimpleMildScissors ( );
	void 	SimpleStraightandLevel ( );
	void 	SimpleAcmSideSlip ( );
	void 	SimpleSpinRecovery ();
	void 	SimpleSpinOut ( );
	void 	SimpleDiveforHome ( );
	void 	SimpleClimbforHome ( );
	void 	SimpleStraightDive ( );
	void 	SimpleStandOnTail ( );
	void 	SimpleShootToFrighten ( );
	void 	SimpleGoHome ( );
	void 	SimpleMoveAway ( );
	void 	SimpleAccidentalSpinOut ( );
//rdh	void 	SimpleTurningFight ();
//	void	SimpleTurningFight();
//	void	SimpleTurnFightSub(ANGLES	HdgIntercept);

	void 	SimpleLowGYoYo ( );
	void 	SimpleVerticalLoop ( );
	void	SimpleImmelmannTurn ( );
	void 	SimpleHeadOnOffset ( );
	void 	SimpleStayWithPrey ( );
	void 	SimpleTightTurn (SLong recovery_alt);
	void 	SimpleTightTurnSub (SLong recovery_alt,COORDS3D	target);
 	void	SimpleTightTurnSubSub (SWord	deltapitch);									//RDH 13Oct96
 	void	SimpleTightClimbingTurn (ANGLES);
	Bool	SimpleMoveToDesiredHdg (ANGLES,ANGLES);
	void	SimpleMoveToHdg (ANGLES);
	SWord	SimpleMoveToDesiredPitch (ANGLES,ANGLES);
	void SimpleFlyWing(AirStrucPtr lead, ANGLES relhdg = ANGLES_0Deg, int dist = 2500);								//CSB 15/03/00



//DeadCode RDH 30Mar98 	void	SelectDefendManoeuvre();
//DeadCode RDH 30Mar98 	void	SelectAttackManoeuvre();
//DeadCode RDH 30Mar98 	Bool	SelectDefendManoeuvreSub(DEFENDMANOEUVRE);
//DeadCode RDH 30Mar98 	Bool	SelectAttackManoeuvreSub(ATTACKMANOEUVRE);
	Bool	TimeToChangeToEvade ();
	Bool	WeHaveNumbersAdvantage ();
//DeadCode RDH 30Mar98 	Bool	WeHaveNumbersAndACMAdvantage ();
	Bool	DisengageAppropriate ();
	Bool	NoseToTail (ANGLES angle);
	void	SelectNextDisengageManoeuvre ();
	void	PanicManoeuvres();
	void	BanditHighManoeuvre();
	void	BanditLowManoeuvre();
	void	LowAltManoeuvre();
	Bool	TooLow();

	void	MoraleMod();

//rdh	void	SelectNextEngageManoeuvre ();
	Bool	LooseDeuceSituation();
	void	TakeLooseDeuceOption();
	Bool	TimeToChangeToDisengage ();
	Bool	ShouldDisengage();											//CSB 25Aug00
	SLong SubjectClosure();
	Bool SubjectClosureGreaterThan(SLong dvel);
	Bool	SubjectLeadingTarget();
	Bool TargetClosureGreaterThan(SLong dvel);
	Bool ClosureLessThan(SLong dvel);
	Bool M_LagRoll();
	Bool 	M_FlightSeparation();
	bool AboveGround(SLong height);
	void	ManoeuvreBasedOnClosure();
	Bool 	M_BarrelRoll();
	Bool 	M_ZoomAndDrop();
	Bool 	M_SpinOut();
//DeadCode RDH 07Jan99 	Bool 	M_SideSlip();
	Bool 	M_SelfAsBait();
	Bool	TargetHasCorrectLead(ANGLES lead, ANGLES maxlead);
	MANOEUVRE	ManoeuvreBasedOnSkill(SkillType skill, MANOEUVRE goodman, MANOEUVRE badman);
	Bool	SubjectHasEnergyAdvantage();
	Bool 	M_GunDefence(ANGLES lead);
	Bool 	M_UnSighted();
	Bool 	M_DiveForHome();
	Bool 	M_SplitS();
	Bool 	M_Scissors(ANGLES lead);
	Bool	M_ShootTooEarly();
	void	DefenceManoeuvre();
	Bool	M_ShootToFrighten();
	SLong		DeltaAltitude();
	void	AggressivePassManoeuvre();
	void	DefensivePassManoeuvre();
	void	SelectNoseToNoseManoeuvre();
	void	SelectNoseToTailManoeuvre();
	void SelectNoseToBeamManoeuvre();
	void	SelectBeamToNoseManoeuvre();
	void	SelectBeamToTailManoeuvre();
	void	SelectBeamToBeamManoeuvre();
	void	SelectTailToTailManoeuvre();
	void	SelectTailToBeamManoeuvre();
	void	SelectTailToNoseManoeuvre();
	SLong CornerSpeed();
	SLong SustainedTurnSpeed();

};


class	MoveAirStruc:public	AirStruc
{
	friend	struct SAGAirstruc;
	friend	class AirStruc;
	friend class mobileitem;
	friend class ACMAirStruc;
	friend struct SAGAirstruc;
	friend class Model;

//movecodes
	void AutoCommsAccel();
	void MoveMissionDiceThrow();
	void AutoTaxi();											//RDH 28Feb96
	void AutoFollowWp ();
	void AutoCrossOverTurn();
//DeadCode RDH 05Jan99 	void AutoTrainingACM ();
	void AutoCrashSkid();
	void AutoCrashBelly();
	void AutoCrashDitch();
	void AutoCrashOneWheel();
	void AutoCrashNose();
	void AutoCrashFlip();
	void AutoCrashTumble();

	void AutoAccelerate();
	void AutoCrashRoll();
//DeadCode RDH 05Jan99 	void AutoTrainingPreMerge ();
//DeadCode RDH 05Jan99 	void SelectNextTrainingManoeuvre();
	void AutoFollowWpWing (AirStrucPtr MyLeader = NULL);		//RDH 27Feb96	//CSB 20/04/99	
	void AutoWait4Time();												//CSB 6Jul00
	void AutoTakeOff ();										//RDH 17Jun96
	void AutoLanding ();
	void HeldACCheck();

	void AutoTakeOffWing ();									//RDH 17Jun96
	void AutoFollowTheLeader();
	void TrackBogey();
	void TrackBandit();
	void AutoPreCombat ();
	void AutoDeathSequence();									//RDH 10Sep96
	void AutoDeathGlide();												//CSB 15Aug00
	void AutoResurrect(AirStrucPtr);							//ARM 05Dec96
//DEADCODE DAW 27/01/00 	void AutoToGrndPitchRoll(ANGLES grndroll,ANGLES grndpitch);	//RJS 03Oct96
	void AutoStraffe();											//MS 18Oct96
	void CheckBombingStatus();
	void AutoBomb();											//MS 18Oct96
	void AutoSpiral2Ground(WorldStuff&);							
	void AutoBombHigh();										//CSB 25/03/99	
	void AutoBombLow();											//CSB 25/03/99	
	void AutoBombDive();										//CSB 25/03/99	
	void AutoBombFollow();										//CSB 11/05/99	
	void AutoOrbit(COORDS3D centre, int radius);				//CSB 31/03/99
	void UpdateDeathTime(UWord,bool launchTransient=false);//RJS 10Oct00
	bool	AssignFuelTruck();

};
typedef	MoveAirStruc *MoveAirStrucPtr;
#endif	AIRSTRUC_INCLUDED
