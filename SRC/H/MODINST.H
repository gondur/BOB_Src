//------------------------------------------------------------------------------
//Filename       modinst.h
//System         
//Author         Andrew McRae
//Date           Wed 27 Aug 1997
//Description    
//------------------------------------------------------------------------------
#ifndef	MODINST_Included
#define	MODINST_Included

#define	DEFAULT_MODINST 0

//typedef class Model *PMODEL;
#include "modvec.h"

enum	AnimSteps
{
	ARC_IMMEDIATE = 1,
	ARC_1SEC = 100,
	ARC_30SEC = 3000,
	ARC_240SEC = 24000
};

enum	SrcBaseType
{
	SBASE_DEFAULT = 0,
	SBASE_AC,
	SBASE_ANIM
};

#define	RUNNING_VOLTS  28
#define	MaxDialSrc 		8
#define	MaxAutoDial		48					//RJS 03Dec99

struct	DialSpec
{
	int	DestValOffset;
	int	SrcValOffset;
	int	SrcValStructIndex;

	FP	ValScale;

	FP	minval;
	FP	maxval;

	int		minIntval;
	int		maxIntval;
	int		Intvalscale;

	UWord	shiftsrc:6,
			shiftdest:6,
			useint:1;

	UWord	torestval;
	SrcBaseType	btype;

	void	SetDialValue(ItemPtr,UByteP,UByteP*);
};

struct	TimedDialSpec											//RJS 29Jun98
{
	SWord	theTimer;
	SLong	SrcVal;
	SLong	OldGap;
	SLong	OldVal;

	int		destOffset;

	int		timeUp;
	int		timeDown;

//DeadCode RJS 30Jun98 	Bool	signedSrc;
	Bool	signedDest;

	UByte	nobitsDest;

	void	SetTimedAnim(void*	adptr);
};


typedef class _instruments
{

public:

	//BOB INSTRUMENTS
	FP I_TrueGroundSpeed;
	FP I_TrueAirSpeed;
	FP I_IndicatedAirSpeed;
	FP I_MachNo;
	FP I_PitchAngle;
	FP I_RollAngle;
	FP I_Heading;
	FP I_RateOfClimb;
	FP I_Altitude;
	FP I_RadioAltitude;
	FP I_Turn;
	FP I_Slip;
	SWord I_UndercarraigePosition0;
	SWord I_UndercarraigePosition1;
	SWord I_MechanicalUndercarraigeIndicator;
	SWord I_ElevatorTrimTab;
	SWord I_FuelContents;
	SByte I_FuelWarningLamp0;
	SByte I_FuelWarningLamp1;
	SByte I_FuelWarningLamp2;
	SByte I_FuelWarningLamp3;
	FP I_FuelPressure;
	FP I_OilContent;
	FP I_OilPressure;
	FP I_OilTemperature;
	FP I_RadiatorTemperature0;
	FP I_RadiatorTemperature1;
	FP I_Boost0;
	FP I_Boost1;
	FP I_EngineRpm0;
	FP I_EngineRpm1;
	FP I_VoltMeter;
	FP I_PropPitch0;
	FP I_PropPitch1;
	FP I_FlapsIndicator;
	FP I_NormalAcc;

	//BOB CONTROLS
	SWord C_FlapLever;
	SWord C_UndercarraigeLever;
	SWord C_DiveBrakeLever;
	FP C_ElevatorTrim;
	FP C_RudderTrim;
	FP C_H_Gate;
	SWord C_EmergencyUndercarraige;
	FP C_Throttle0;
	FP C_Throttle1;
	FP C_PropPitch0;
	FP C_PropPitch1;
	SWord C_Magnetos0;
	SWord C_Magnetos1;
	SWord C_PrimerPump0;
	SWord C_PrimerPump1;
	SWord C_FuelCock0;
	SWord C_FuelCock1;
	SWord C_StarterButton0;
	SWord C_StarterButton1;
	SWord C_BoostControlCutout;
	SWord C_HoodCatch;
	SWord C_FuelGuageSelector;

	
//DeadCode CSB 01/12/99		// Instruments
//DeadCode CSB 01/12/99		FP ActualSpeed;			// miles per hour
//DeadCode CSB 01/12/99		FP TrueAirSpeed;		// knotts
//DeadCode CSB 01/12/99		FP IndicatedAirSpeed; 	// knotts
//DeadCode CSB 01/12/99		FP MachNo;				// no units
//DeadCode CSB 01/12/99		ULong Altitude;			// feet
//DeadCode CSB 01/12/99	//	ULong RateOfClimb;		// feet per minute
//DeadCode CSB 01/12/99		SLong RateOfClimb;		// feet per minute
//DeadCode CSB 01/12/99		FP BankAngle;		// degrees
//DeadCode CSB 01/12/99		FP PitchAngle;		// degrees
//DeadCode CSB 01/12/99		FP HdgAngle;		// degrees
//DeadCode CSB 01/12/99		FP LastHdgAngle;
//DeadCode CSB 01/12/99		FP NormalAcc;			// gravities
//DeadCode CSB 01/12/99		FP Rpm1;				// rpm
//DeadCode CSB 01/12/99		FP Rpm2;				// rpm
//DeadCode CSB 01/12/99		FP Slip;				// slip								//RJS 06Apr98
//DeadCode CSB 01/12/99		SWord Turn;				// turn								//RJS 21Apr98
//DeadCode CSB 01/12/99		FP	turn;				//turn in rads/cs
//DeadCode CSB 01/12/99		FP pitchrate;			//in rads/cs
//DeadCode CSB 01/12/99		FP Turn;				// turn								//RJS 21Apr98
//DeadCode CSB 01/12/99		FP Turn2;				// turn								//RJS 21Apr98
//DeadCode CSB 01/12/99		FP	time;				//time in csecs	debug only
//DeadCode CSB 01/12/99		// Fiddled instruments....
//DeadCode CSB 01/12/99	
//DeadCode CSB 01/12/99		FP		TempFreeAir;										//RJS 03Apr98
//DeadCode CSB 01/12/99		SLong	TempExhaust;							//RJS 11Feb98
//DeadCode CSB 01/12/99		SLong	Charge;										//RJS 11Feb98
//DeadCode CSB 01/12/99		SLong	GyroCompass;										//RJS 11Feb98
//DeadCode CSB 01/12/99		SLong	HorizStab;										//RJS 11Feb98
//DeadCode CSB 01/12/99		SLong	HydraulicPress;							//RJS 11Feb98
//DeadCode CSB 01/12/99		SLong	CabPress;							//RJS 11Feb98
//DeadCode CSB 01/12/99		SLong	FuelPress;							//RJS 11Feb98
//DeadCode CSB 01/12/99		SLong	FuelContentInt;										//RJS 03Apr98
//DeadCode CSB 01/12/99		SLong	FuelContentTot;										//RJS 14Apr99
//DeadCode CSB 01/12/99		SLong	OxygenPress;										//RJS 01May98
//DeadCode CSB 01/12/99		SWord	ManifoldPressure;							//RJS 02Nov98
//DeadCode CSB 01/12/99		SWord	SuctionGuage;										//RJS 16Feb99
//DeadCode CSB 01/12/99		SWord	CarburettorAirTemp;									//RJS 16Feb99
//DeadCode CSB 01/12/99		SWord	CoolantTemp;										//RJS 16Feb99
//DeadCode CSB 01/12/99		SWord	Power;												//RJS 31Mar99
//DeadCode CSB 01/12/99		SWord	ExhaustTemp;				//RJS 01Apr99
//DeadCode CSB 01/12/99		SWord	Voltage;											//RJS 14Apr99
//DeadCode CSB 01/12/99		SWord	OilContent;											//RJS 26Nov99
//DeadCode CSB 01/12/99		SWord	OilTemp;											//RJS 26Nov99
//DeadCode CSB 01/12/99		SWord	RadiatorTemp;										//RJS 26Nov99
//DeadCode CSB 01/12/99		SWord	Boost;												//RJS 26Nov99
//DeadCode CSB 01/12/99	
//DeadCode CSB 01/12/99	
//DeadCode CSB 01/12/99		UWord	TimerCharge;								//RJS 11Feb98
//DeadCode CSB 01/12/99		UWord	TimerGyro;									//RJS 11Feb98
//DeadCode CSB 01/12/99		UWord	TimerHorizStab;									//RJS 11Feb98
//DeadCode CSB 01/12/99		UWord	TimerExhaust;									//RJS 11Feb98
//DeadCode CSB 01/12/99		UWord	TimerCabPress;									//RJS 11Feb98
//DeadCode CSB 01/12/99		UWord	TimerHydraulicPress;									//RJS 11Feb98
//DeadCode CSB 01/12/99		UWord	TimerFuelPress;									//RJS 11Feb98
//DeadCode CSB 01/12/99		UWord	TimerOxygenPress;									//RJS 01May98
//DeadCode CSB 01/12/99		UWord	TimerManifoldPress;									//RJS 01May98

	UByteP	DialSrcList[MaxDialSrc];							//RJS 16Feb98
	UWord	DialSrcCnt;											//RJS 16Feb98

	DialSpec	DialList[MaxAutoDial];							//RJS 29Jun98
	UWord		DialCnt;

	TimedDialSpec	TimedDialList[MaxAutoDial];					//RJS 29Jun98
	UWord			TimedDialCnt;

	SWord FuelGuageTank [4];
	SLong FuelGuageScale[4];

	void SetInstruments (AirStrucPtr const ControlledAC,PMODEL);

	SLong	SetTimedAnim (SLong&,UWord&,SLong,UWord,UWord);		//RJS 23Jun98
	SLong	EngineDamage(UByteP, int);							//RJS 16Feb98
	void	SetCockpitAnims(ItemPtr,UByteP);					//RJS 20Jul98
	void	UpdateCockpitTimers(SLong);							//RJS 16Feb98
	void	NewDialValue(void*,UByteP,void*,UByteP,int,int,int,UByte,UByte,UWord	restrot = 0);
	void	AddAutoDial(void*,UByteP,void*,SWordP,int,int,int scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,SWordP,void*,SWordP,int,int,int scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,UByteP,void*,ULongP,int,int,int scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,SWordP,void*,ULongP,int,int,int scaler = 0);//RJS 24Apr98

	void	NewDialValue(void*,UByteP,void*,UByteP,FP,FP,FP,UByte,UWord	restrot = 0);
	void	AddAutoDial(void*,UByteP,void*,FP*,FP,FP,FP scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,SWordP,void*,FP*,FP,FP,FP scaler = 0);//RJS 24Apr98

	void	AddAutoDial(void*,UByteP,void*,SLongP,int,int,int scaler = 0);//RJS 24Apr98
	void	AddAutoDial(void*,SWordP,void*,SLongP,int,int,int scaler = 0);//RJS 24Apr98

	void	AddTimedDial(void*,UByteP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,SByteP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,UWordP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,SWordP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,ULongP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98
	void	AddTimedDial(void*,SLongP,int,int,Bool signedSrc=FALSE);//RJS 29Jun98

	void	NewTimedDial(int,int,int,Bool,Bool,UByte);			//RJS 29Jun98

	void	SetFuelGaugeSelector(SWord tank1, ULong scale1, SWord tank2, ULong scale2, SWord tank3, ULong scale3, SWord tank4, ULong scale4);

	void Null ()		
 	{
		I_TrueGroundSpeed = 0;
		I_TrueAirSpeed = 0;
		I_IndicatedAirSpeed = 0;
		I_MachNo = 0;
		I_PitchAngle = 0;
		I_RollAngle = 0;
		I_Heading = 0;
		I_RateOfClimb = 0;
		I_Altitude = 0;
		I_RadioAltitude = 0;
		I_Turn = 0;
		I_Slip = 0;
		I_UndercarraigePosition0 = 0;
		I_UndercarraigePosition1 = 0;
		I_MechanicalUndercarraigeIndicator = 0;
		I_ElevatorTrimTab = 0;
		I_FuelContents = 0;
		I_FuelWarningLamp0 = 0;
		I_FuelWarningLamp1 = 0;
		I_FuelWarningLamp2 = 0;
		I_FuelWarningLamp3 = 0;
		I_FuelPressure = 0;
		I_OilContent = 0;
		I_OilPressure = 0;
		I_OilTemperature = 0;
		I_RadiatorTemperature0 = 0;
		I_RadiatorTemperature1 = 0;
		I_Boost0 = 0;
		I_Boost1 = 0;
		I_EngineRpm0 = 0;
		I_EngineRpm1 = 0;
		I_VoltMeter = 0;
		I_PropPitch0 = 0;
		I_PropPitch1 = 0;
		I_FlapsIndicator = 0;
		I_NormalAcc = 0;

		//BOB CONTROLS
		C_FlapLever = 0;
		C_UndercarraigeLever = 0;
		C_ElevatorTrim = 0;
		C_RudderTrim = 0;
		C_H_Gate = 0;
		C_EmergencyUndercarraige = 0;
		C_Throttle0 = 0;
		C_Throttle1 = 0;
		C_PropPitch0 = 0;
		C_PropPitch1 = 0;
		C_Magnetos0 = 0;
		C_Magnetos1 = 0;
		C_PrimerPump0 = 0;
		C_PrimerPump1 = 0;
		C_FuelCock0 = 0;
		C_FuelCock1 = 0;
		C_StarterButton0 = 0;
		C_StarterButton1 = 0;
		C_BoostControlCutout = 0;
		C_HoodCatch = 0;
		C_FuelGuageSelector = 0;

	
//DeadCode CSB 01/12/99			ActualSpeed = 0.0;
//DeadCode CSB 01/12/99	 		TrueAirSpeed = 0;
//DeadCode CSB 01/12/99	 		IndicatedAirSpeed = 0;
//DeadCode CSB 01/12/99	 		MachNo = 0;
//DeadCode CSB 01/12/99	 		Altitude = 0;
//DeadCode CSB 01/12/99	 		RateOfClimb = 0;
//DeadCode CSB 01/12/99	 		BankAngle = 0;
//DeadCode CSB 01/12/99	 		PitchAngle = 0;
//DeadCode CSB 01/12/99	 		HdgAngle = 0;
//DeadCode CSB 01/12/99			LastHdgAngle = 0;
//DeadCode CSB 01/12/99	 		NormalAcc = 0;
//DeadCode CSB 01/12/99	 		Rpm1 = 0;
//DeadCode CSB 01/12/99	 		Rpm2 = 0;
//DeadCode CSB 01/12/99			Turn = 0;			//rdh
//DeadCode CSB 01/12/99			turn = 0;
//DeadCode CSB 01/12/99			Turn2 = 0;			//rdh
//DeadCode CSB 01/12/99			time = 0;
//DeadCode CSB 01/12/99	 		TempFreeAir = 0;	
//DeadCode CSB 01/12/99	 		TempExhaust = 0;
//DeadCode CSB 01/12/99	 		Charge = 0;
//DeadCode CSB 01/12/99	 		GyroCompass = 0;
//DeadCode CSB 01/12/99	 		HorizStab = 0;
//DeadCode CSB 01/12/99	 		HydraulicPress = 0;
//DeadCode CSB 01/12/99	 		CabPress = 0;
//DeadCode CSB 01/12/99	 		FuelPress = 0;
//DeadCode CSB 01/12/99			FuelContentInt = 0;										//RJS 16Feb99								
//DeadCode CSB 01/12/99			FuelContentTot = 0;										//RJS 16Feb99
//DeadCode CSB 01/12/99	//DeadCode CSB 14/04/99			FuelContentExt = 0;										//RJS 16Feb99
//DeadCode CSB 01/12/99			OxygenPress = 0;										//RJS 16Feb99
//DeadCode CSB 01/12/99			ManifoldPressure = 0;									//RJS 16Feb99
//DeadCode CSB 01/12/99			SuctionGuage = 0;										//RJS 16Feb99
//DeadCode CSB 01/12/99			CarburettorAirTemp = 0;									//RJS 16Feb99
//DeadCode CSB 01/12/99			CoolantTemp = 0;										//RJS 16Feb99
//DeadCode CSB 01/12/99	 
//DeadCode CSB 01/12/99	 		TimerCharge = 0;
//DeadCode CSB 01/12/99	 		TimerGyro = 0;
//DeadCode CSB 01/12/99	 		TimerHorizStab = 0;
//DeadCode CSB 01/12/99	 		TimerExhaust = 0;
//DeadCode CSB 01/12/99	 		TimerCabPress = 0;
//DeadCode CSB 01/12/99	 		TimerHydraulicPress = 0;
//DeadCode CSB 01/12/99	 		TimerFuelPress = 0;
//DeadCode CSB 01/12/99			TimerOxygenPress = 0;									//RJS 16Feb99
//DeadCode CSB 01/12/99			TimerManifoldPress = 0;
//DeadCode CSB 01/12/99	
//DeadCode CSB 01/12/99			DialSrcCnt = 0;
//DeadCode CSB 01/12/99			DialCnt = 0;
//DeadCode CSB 01/12/99	
//DeadCode CSB 01/12/99			TimedDialCnt = 0;
 	}	

}
INSTRUMENTS,
*PINSTRUMENTS;

#endif

