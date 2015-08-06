//------------------------------------------------------------------------------
//Filename       model.h
//System         
//Author         Andrew McRae
//Date           Tue 7 Jan 1997
//Description    
//------------------------------------------------------------------------------
//variables commented to indicate action required for replay, rdh
//				save			need to save the variable in the replay file
//				set by ***		use the function *** to set the variable
//				unchanged		the variable, once set is never changed
//				zero			the variable should be zeroed on replaying 
//				transient		don't bother with this variable, it is a working variable




#ifndef	MODEL_Included
#define	MODEL_Included
class Ctrl ;
class NewCtrl ;
class Surface ;
class MainPlane ;
class Cylinder ;
class ThrustPoint ;
class AeroDevice ;

typedef class Ctrl *PCTRL;
typedef class NewCtrl *PNEWCTRL;
typedef class Surface *PSURFACE;
typedef class MainPlane *PMAINPLANE;
typedef class Cylinder *PCYLINDER;
typedef class ThrustPoint *PTHRUSTPOINT;
typedef class AeroDevice *PAERODEVICE;
#include "keytest.h"
#include "link.h"
#include "curves.h"

#include "collided.h"
#include "sky.h"
#include "gear.h"
#include "modint.h"
#include "aerodev.h"
#include "acmmodel.h"
#include "engine.h"

#include "modinst.h"

#include "animdata.h"

#include "3DCode.h"
#include "mytime.h"

#define	DEFAULT_MODEL 0

#define FRAMESPERCALC 128		// This is the number of operations of the flight model per 
								// calculation of atmosphere, fuel burn, etc.
//DEADCODE AMM 24/11/99 #define EVERY512cs 0x00ff											  //DAW 02/07/99
//DEADCODE AMM 24/11/99 #define EVERY256cs 0x007f
//DEADCODE AMM 24/11/99 #define EVERY64cs  0x001f
//DEADCODE AMM 24/11/99 #define EVERY16cs  0x0007
//DEADCODE AMM 24/11/99 #define EVERY8cs   0x0003

#define EVERY512cs 0x007f											  //DAW 02/07/99
#define EVERY256cs 0x003f
#define EVERY64cs  0x000f
#define EVERY16cs  0x0003
#define EVERY8cs   0x0001

#define GRAVITY 0.098065

#define AILERONCTRL (FP)0.35	// 0.15 24/7/97

#define MAXAIRCRAFTSIZE 1200

#define MODLIMIT(val,lim) 	if (val>lim) val=lim; \
							elseif (val<-lim) val=-lim

#define MODSTEPUP(val,step)	if (val>0) val+=step; \
							elseif (val<0) val-=step

#define MODMAXMIN(val,min,max)	if (val<min) val=min; \
								elseif (val>max) val=max

#define CONTROL_RESET 999.999

#define CALC_FORCE_MOMENT_LIMITS
#define FULL_RANGE_JOYSTICK

//remove // for next 3 defines to get calib data
//#define EMIT_HM_DATA
//#define EMIT_DOGHOUSE_DATA
//#define PS_CALCS


#define	ANIM_GEAR_UP	255										//RJS 08Apr98
#define	ANIM_GEAR_DOWN	0										//RJS 08Apr98
#define	ANIM_GEAR_AUTO	-32768									//RJS 08Apr98

#define	ANIM_BOMBDOORS_CLOSE	0										//CSB 31Aug00
#define	ANIM_BOMBDOORS_OPEN		255										//CSB 31Aug00
#define	ANIM_BOMBDOORS_AUTO		-32768							//RJS 11May00

enum AIRCRAFT_TYPE
{
	AT_VOID,

//BOB Aircraft		//CSB 22/09/99	
	AT_SPITFIRE,	//CSB 22/09/99	
	AT_HURRICANE,	//CSB 22/09/99	
	AT_BF109,		//CSB 22/09/99	
	AT_BF110,		//CSB 22/09/99	
	AT_JU87B,		//CSB 22/09/99
	
	AT_DEFIANT,		//CSB 25/10/99	
	AT_BLENHIEM,	//CSB 25/10/99	
	AT_JU88,		//CSB 25/10/99	
	AT_HE111,		//CSB 25/10/99	
	AT_DO17,		//CSB 25/10/99	
	AT_HE59			//CSB 25/10/99	
};


enum ITERATION_MASK
{
	ALL,
	Y_ONLY,
	XZ_ONLY,
	YZ_ONLY
};


enum ENGINE_SELECTED
{
	ES_PORT,
	ES_STBD,
	ES_BOTH
};


enum FUELCOCK_TYPE
{
	FC_VOID,
	FC_2LEVERS,
	FC_4POSITION
};


const FP MODEL_DT = Timer_Code.FRAMETIME;												//UnChanged at the moment
const FP MODEL_ENGINE_DT = Timer_Code.FRAMETIME*4;									//UnChanged at the moment

class Model {

	bool	subGunSet;
	Float	subGun_x;
	Float	subGun_y;
	Float	subGun_z;

	static SWord stretchyNeck;

public:

	LINKEDLIST<Model> List;

	ULong Ident;// save	//AMM 31Jan00? NO, only gets used in setup	//AMM 3Jul00
	UWord FrameCount;	// Used to work out the timing for atmosphere, fuel burn worked out 
						// once every n frames
						// set in ResetSecondaryValues to UID //AMM 31/01/00

	Bool FirstCycle;	// Used to set engine speed for first model loop //save //AMM 31/01/00
	AIRCRAFT_TYPE Type;

	FCRD PilotEyePos;

	Bool Controlled;
	Bool bACM;
	Bool Spinning;// save

	ACMMODEL ACMModel;

	// World Coords
	FCRDlong Pos;													//set by UpdateModel

	FORI Ori;													//set by UpdateModel
	FORI GunOri;													//set by UpdateModel//RDH 30Nov98
	FORI BakOri;												//for gunsight//RJS 25Jun99
	FCRD BakRotVel;												//Save//RJS 25Jun99
	bool fixgunsight;											//CSB 09Jun99
																
	FCRD Vel;	// rel to ground								//set by UpdateModel
	FCRD GunVel;												//OldVel = Vel//RDH 30Nov98
	FP	 Speed;	// rel to ground								//set by CalcAirVel
	FCRD CheatAcc;	//CSB 09/12/98 //Used to change the speed of the computer controlled aircraft for easy option//reset to 32767//AMM 15Dec99

	GUST Gust;													//Zero

// for replay purposes when model is not maintained these values are used

	SWord	replay_roll;										//AMM 31Mar99
	SWord	replay_pitch;										//AMM 31Mar99
	SWord	replay_hdg;											//AMM 31Mar99


	// Aircraft Coords

	FCRD RotVel;												//Save

	FCRD AirVel;	// rel to cg								//Save
//DEADCODE CSB 23/12/99 	FCRD InstAirVel;											//Transient	
	FP AirSpeed;												//Transient
	FP DynamicPressure;											//Might Need for Slats/Airbrakes, Set by CalcAirVel

	FCRD Acc;	// no gravity									//Transient
	FCRD wAcc;													//Not Used ????
	FCRD RotAcc;

	FCRD NettForce;											//transient
	FCRD NettMoment;										//transient

	FCRD StoresForce;										//Transient
	FCRD StoresMoment;										//Transient

	// Devices
	FP DeltaCl;												//Transient
	FP DeltaCd;												//Transient
	FP DeltaCm;												//Transient
	FP DeltaAlpha;											//Transient

	Bool EmergencyGearUsed;// player only						//AMM 15Dec99
	Bool GearTouched;	// include gear forces if TRUE		//Set by GearCalcs
	Bool GearSkid;
	Bool RestartEngine;	//CSB 25/11/98
	SLong GroundHeight;										//Set by AccurateGroundAltitude


	FP TotalBuffet;

	FP PowerBoost;											//UnChanged

	// Non Vector Parameters

	FP Mass;												//Save
	FCRD InertiaEmpty;		//CSB  08/09/98		The inertia of the aircraft without stores, fuel		//UnChanged
	FCRD RotInertia;										//Save

	FP MaxG, MinG;	// cm/csec^2 (G * GRAVITY)				//UnChanged
	FCRD InertiaMoment;		//The moment produced due to the aircraft rotating around two or more axis at once
	FCRD ShapeCoG;

	FP fHdg,fPitch,fRoll;	// calculated attitude angles	//Set by SetAirStrucOrientation

	INSTRUMENTS Inst;										//Set by SetInstruments


	// Player inputs
	int Elevator;											//Save
	int Aileron;											//Save
	int Rudder;												//Save
	int ElevatorTrim;										//Save
	int AileronTrim;										//Save	//CSB 27/09/99	
	int RudderTrim;											//Save	//CSB 27/09/99	

	ENGINE_SELECTED EngineSelected;


	SWord ModelThrottle;
	SWord ModelPropSetting;	// CSB // for piston engine with constant speed propellor		//Save
	bool  BoostCutout;
	SWord LeftWheelBrake;									//Save
	SWord RightWheelBrake;									//Save
	UWord BombingPhase;// player only

//DEADCODE CSB 02/12/99 	FP SlatOutPressure;										//UnChanged
//DEADCODE CSB 02/12/99 	FP SlatInPressure;										//UnChanged
 	SWord MaxElevatorTrim;	//CSB 27/09/99	
	SWord MaxAileronTrim;	//CSB 27/09/99	
	SWord MaxRudderTrim;	//CSB 27/09/99	
	SWord SlipstreamRudder;	//CSB 28/10/99	

	FP ControlLossV0;		//For loss of elevator power at high speeds	/CSB
	FP ControlLossV1;		//For loss of elevator power at high speeds	/CSB
	FP FControlLoss;// calculated every frame

	int ControlForce;		// % of max available control force feedback
	int BuffetForce;		// % of max available buffet force feedback

	Bool Gear;	// flag for anims

	// Atmosphere
	FP AmbDensity;											//Set by MMC.Sky.Ambient every 128 frames in latest version
	FP AmbTemp;												//Set by MMC.Sky.Ambient every 128 frames in latest version
	FP AmbPres;												//Set by MMC.Sky.Ambient every 128 frames in latest version

	FP ContrailDuration;						//UnChanged		//AMM 29Jun99

	UWord	CrashTime;//RJS 25Aug98							//Save

	FP Blood;	//CSB 09/06/99

	bool			FuelCockTanks[4][4];// unchanged					//AMM 24Jul00
	FUELCOCK_TYPE	FuelCockType;	//unchanged							//AMM 24Jul00
// moved to AirStruc
//DeadCode AMM 24Jul00 	SWord			FuelCockPos;//save									//AMM 24Jul00
	// Functions

	void ClearLists ();

	void SetupAircraft (AirStrucPtr const ControlledAC);
	void RemoveStore(weap_info*,SLong,int mass, int drag, Bool fueltank);//RJS 13May98
	void RemoveMass(FP amount, FP massX, FP massY, FP massZ);
	void AddMass(FP amount, FP massX, FP massY, FP massZ);
	void SetMassInertias (AirStrucPtr const ControlledAC, FP EmptyIxx, FP EmptyIyy, FP EmptyIzz);
	void UpdateMassInertias (AirStrucPtr const ControlledAC);
	
	void SetTrim(SWord elevtrim, SWord ailtrim, SWord rudtrim);	//CSB 27/09/99	
	void SetFuelCockTanks(SWord, bool, bool, bool, bool);
	
	void CalcAirVel (AirStrucPtr const ControlledAC);
	void TrimAircraft(AirStrucPtr const ControlledAC);
	void SetLocalGust(COORDS3D AcPos, COORDS3D HitPos, SWord Strength);
	FP   CalcFuelRate(AirStrucPtr const ControlledAC);		//CSB
	void SetFuelTank(AirStrucPtr const ControlledAC, bool player);	
	void InitialiseEngines(AirStrucPtr const ControlledAC);	//CSB 24/11/98
	void ProcessEngines (AirStrucPtr const ControlledAC);
	void RestartEngines (AirStrucPtr const ControlledAC);
	void ProcessMainElements (AirStrucPtr const ControlledAC);
//DeadCode CSB 05/11/98		void ProcessStabElements (AirStrucPtr const ControlledAC);
	void ProcessDevices ();
	void GearUp (AirStrucPtr const ControlledAC);
	void GearDown (AirStrucPtr const ControlledAC);
	void FlapsDown (AirStrucPtr const ControlledAC);
	bool AutoOpenCanopy();			  //CSB 02/12/99
	
	void ProcessStoresDrag (AirStrucPtr const ControlledAC);			//CSB 03Sep98

	void ProcessCylinders (AirStrucPtr const ControlledAC);		//CSB 05/11/98

//DeadCode CSB 26/02/99		void ProcessAeroCtrls ();
//DeadCode CSB 26/02/99		void ProcessAeroCouples ();

	void ProcessGears (AirStrucPtr const ControlledAC, FP forcex, FP forcey, FP forcez, FP momenty);	//CSB 11/01/99
	void CheckGearPos (AirStrucPtr const ControlledAC);	//CSB 12/01/99

	void CalcNettForceMoment (FCRD&, FCRD&);
	void WingDamage (AirStrucPtr const ControlledAC, FP forcey);

	void CalcAcc ();
	void CalcRotAcc ();

	void MovePilotEye();

	void SetSpeed(AirStrucPtr const ControlledAC, FP desiredspeed);	//CSB 09/12/98
	void ModifyAcc(FCRD OldAcc, FCRD NewAcc);
	void ChangeDirection(AirStrucPtr const ControlledAC, FP DeltaPitch, FP DeltaYaw, FP DeltaRoll);	//CSB 14/12/98
	void TransInt (ITERATION_MASK, FP);
	void RotInt (ITERATION_MASK);
	void RotVelInt ();

	void Ground (AirStrucPtr const ControlledAC);
//DeadCode CSB 01/02/99		void GroundCalcs ();	// Simple Gear calcs

	void CalcStickForceFeedback ();	//CSB
	void ResetGearPos(bool);									//RJS 30Jun99
	void	SetGunOri(Float,Float,Float);						//RJS 13Mar00
	bool	GetGunOri(Float&,Float&,Float&);					//RJS 13Mar00

	void	HandleHead(SLong,SLong,SWord&);								//RJS 12Oct00

	bool	CanopyOpen();												//RJS 28Aug00

#ifdef CALIBRATION_CODE
	void CalibrationInputs ();
#endif

public:

	// Software Params

	PENGINE EngineList;
	PGEAR GearList;
	PMODELANIM AnimList;
	PTHRUSTPOINT ThrustList;
	PSURFACE SurfaceList;
	PMAINPLANE MainPlaneList;
	PCYLINDER CylinderList;
	PAERODEVICE DeviceList;

	Model ();
	~Model ();

	void Initialise (AirStrucPtr const ControlledAC, Bool);
	void Base (AirStrucPtr const ControlledAC);
	void SubBase (AirStrucPtr const ControlledAC);
	void RealBase (AirStrucPtr const ControlledAC);
	void ArcadeBase (AirStrucPtr const ControlledAC);	//CSB 13/09/99	
	void ACMBase (AirStrucPtr const ControlledAC);
	void DerivativeBase ();

	// Interface Functions

	void ResetDeltaPos (AirStrucPtr const ControlledAC,SLong, SLong, SLong);
	void ResetPosition (AirStrucPtr const ControlledAC,SLong, SLong, SLong);
	void ResetVelocity (AirStrucPtr const ControlledAC,SLong, SLong, SLong, Bool);
	void ResetAngles (AirStrucPtr const ControlledAC,UWord, UWord, UWord);

	void UpdateAirStruc (AirStrucPtr const ControlledAC);
	void SetAirStrucPosition (AirStrucPtr const ControlledAC);
	void SetAirStrucOrientation (AirStrucPtr const ControlledAC);
	void SetAirStrucVelocity (AirStrucPtr const ControlledAC);
	void UpdateModel (AirStrucPtr const ControlledAC);
	void SetPlayerMoving (AirStrucPtr const ControlledAC);
	void TrainingTakeoff(AirStrucPtr const ControlledAC);
	void TrainingLanding(AirStrucPtr const ControlledAC);
	void CommsChecks(AirStrucPtr const ControlledAC);
	bool OnAnAirfield(AirStrucPtr ControlledAC);

	void Instruments (AirStrucPtr const ControlledAC);
	void ACMInstruments (AirStrucPtr const ControlledAC);
	void Animations (AirStrucPtr const ControlledAC, bool forced = false);

	void	DeathSequenceOverride(int);

	void	SetGearAnimPos(AirStrucPtr const ControlledAC,SWord,Bool killnow=FALSE);//RJS 07Sep98
	void	ProcessAeroPacket(AirStrucPtr const ControlledAC, UByte	DeviceID,SWord Attractor);	//CSB 11/05/99	
	void	CalcLauncherVel(SLong, SLong&, SLong&, SLong&, SLong gunposx = 0, SLong gunposy = 0, SLong gunposz = 0);		//RDH 30Nov98
	void	CalcGunsightPos(SLong range, SWord gunvel, SLong& dx, SLong& dy, SLong& dz);		//CSB 03/06/99	
	void	RememberForGunSight(bool,AirStrucPtr);					//RJS 13MAR00
	void	CalcParachuteVel(SLong&, SLong&, SLong&, SWord, SWord, SWord, SLong, SLong, SLong);//RJS 10May99	//CSB 13/06/99	
	void	CalcLauncherPos(SLong&,SLong&,SLong&);				//RJS 02Jun99
	void	BackupForGunsight();								//RJS 25Jun99
	void	TrashModelData(AirStrucPtr const ControlledAC);	//CSB 26/10/99
	void	DamageGear(Coords3D&);								//RJS 17Dec99

#ifdef WRITE_MODEL_LOG
void WriteModelLog ();
#endif

#define PSRANGE	5
#define MACHRANGE	52
#define LIFTLIMITRANGE	26
struct	TurnData
{
	FP			Ps;
	FP			rate[MACHRANGE];
};
struct ThrustData
{
	FP			alt;
	FP			thrust[14];
};
struct	DogHouseData
{
	FP			alt;
	FP			stallspd;
	FP			stallmach;
	FP			maxspd;
	FP			maxmachSL;
	FP			maxPs;
	FP			machatmaxPs;
	FP			ceiling;
	FP			thrust;
	FP			mass;
	FP			liftlimit[LIFTLIMITRANGE];
	TurnData	turndata[PSRANGE];
	FP			minmach[PSRANGE];
	FP			maxmach[PSRANGE];
	ThrustData	thrustatvel[11];
	FP			timeto16400;
	FP			timeto20000;
	FP			timeto30000;
	FP			timeto32800;
	FP			timeto40000;
};

#ifdef EMIT_HM_DATA
	void EmitHMData (AirStrucPtr const ControlledAC);
	DogHouseData	doghousedata;
#endif
 
#ifdef EMIT_DOGHOUSE_DATA
	void EmitDoghouseData (AirStrucPtr const ControlledAC,FP Height);
#endif

#ifdef PS_CALCS 
	Bool CalcPs (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Vel, FP& Ps);
	void Model::CalcnAtPs (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Vel, FP& Ps, FP& n);
	void Model::CalcnAtMaxLift (FP Height, FP Mach, FP& Vel,FP& n);
	void Model::CalcTurnRate(FP n, FP Vel, FP& TurnRate);
	Bool Model::FindFastestAtPsReq (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP PsReq);
	void Model::EmitDoghouseData2 (AirStrucPtr const ControlledAC,FP Height);
	Bool Model::FindSlowestAtPsReq (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP PsReq);
	void Model::EmitLiftLimitedData (FP Height);
	void Model::EmitThrustData (AirStrucPtr const ControlledAC,FP Height);
	void Model::CalcStallSpeed (FP Height, FP& Mach, FP& Vel);
	void Model::PrintDogHouseData(AirStrucPtr const ControlledAC,FP Height);
	void Model::ClrDogHouseData(FP Height);
	void EmitPsData (AirStrucPtr const ControlledAC,FP currheight);
	Bool PsSlope (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP& Slope, FP& Ps);
	Bool FindMaxPs (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel, FP& Ps);
	Bool FindFastestZeroPs (AirStrucPtr const ControlledAC,FP Height, FP& Mach, FP& Vel);
	Bool FindCeiling (AirStrucPtr const ControlledAC,FP& Height, FP& Mach, FP& Vel);
	void CalibCalcThrust (AirStrucPtr const ControlledAC,FP Height, FP Mach, FP Vel, FP& Thrust);
#endif
	
};
typedef class Model MODEL;


#include "ctrl.h"


#include "elmt.h"

extern void SetBuffetData(CockpitBuf* );


#ifdef DISPLAY_MONO_DATA
void PrintModelData (AirStrucPtr const ControlledAC,Model*, ULong, ULong);
#endif

void PrintVar (ULong, ULong, char*, ULong);
void PrintVar (ULong, ULong, char*, SLong);
void PrintVar (ULong, ULong, char*, FP);
void PrintVar (ULong, ULong, char*, SWord);
void PrintVar (ULong, ULong, char*, UWord);
void PrintVar (ULong, ULong, char*, UByte);
void PrintVar (ULong, ULong, char*, SByte);
void PrintString (ULong, ULong, char*);
void PrintHLine (ULong, ULong, ULong, char*);
void PrintVLine (ULong, ULong, ULong, char*);

extern Model _Model;

extern PMODEL ModelList;

//DEADCODE  01/11/99 void F86E_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void MIG15_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F84E_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F80C_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F51D_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F9F2_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F8_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F82G_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void YAK9_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F4U5_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void SFURY_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void FFLY_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void A1_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 
//DEADCODE  01/11/99 void B26_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void B29_Setup (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void T6_Setup (AirStrucPtr const, ULong);

void SPITFIRE_Setup (AirStrucPtr const, ULong);		//CSB 22/09/99	
void HURRICANE_Setup (AirStrucPtr const, ULong);	//CSB 22/09/99	
void BF109_Setup (AirStrucPtr const, ULong);		//CSB 22/09/99	
void BF110_Setup (AirStrucPtr const, ULong);		//CSB 22/09/99	
void JU87B_Setup (AirStrucPtr const, ULong);		//CSB 22/09/99	
	
void DUMMY_Setup (AirStrucPtr const, ULong);		//CSB 29/10/99	
	
//DEADCODE  01/11/99 void F4U5_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void Mig15_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F8_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F80C_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F51D_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F82G_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F84E_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F86E_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void F9F2_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void FFLY_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void SFURY_SetupAI (AirStrucPtr const, ULong);
//DEADCODE  01/11/99 void YAK9_SetupAI (AirStrucPtr const, ULong);

void SPITFIRE_SetupAI (AirStrucPtr const, ULong);	//CSB 27/10/99	
void HURRICANE_SetupAI (AirStrucPtr const, ULong);	//CSB 27/10/99	
void BF109_SetupAI (AirStrucPtr const, ULong);		//CSB 27/10/99	
void BF110_SetupAI (AirStrucPtr const, ULong);		//CSB 27/10/99	

#endif
