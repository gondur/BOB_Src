//------------------------------------------------------------------------------
//Filename       engine.h
//System         
//Author         Andrew McRae
//Date           Thu 24 Apr 1997
//Description    
//------------------------------------------------------------------------------

#ifndef	ENGINE_Included
#define	ENGINE_Included


enum ENGINE_TYPE
{
	ET_VOID,
	ET_PISTON,
	ET_JET
};

enum PROP_TYPE
{
	PT_VOID,
	PT_FIXED,
	PT_2PITCH,
	PT_VARIABLE,
	PT_CONSTSPEED
};

enum STARTER_TYPE
{
	ES_VOID,
	ES_ELECTRIC,
	ES_INERTIA
};

enum MAGNETO_TYPE
{
	MT_VOID,
	MT_2SWITCHES,
	MT_4POSITION
};


class Engine {

public:

	ENGINE_TYPE Type;

	PMODEL pModel;

//JET_Code CSB 21/09/99		// Jet stuff
//JET_Code CSB 21/09/99		FP T100;
//JET_Code CSB 21/09/99		FP Rpm100;
//JET_Code CSB 21/09/99		FP OneOverMoI;
//JET_Code CSB 21/09/99		PCURVE MachFact;
//JET_Code CSB 21/09/99		PCURVE ThrustRpm;
//JET_Code CSB 21/09/99		PCURVE WindMillDrag;
//JET_Code CSB 21/09/99		PCURVE WindMillRpm;
//JET_Code CSB 21/09/99		Bool EngineOut;

	
//CONSTANTS	
	FP p0;
	FP Rpm100, Rpm0;
	FP MoI;
	PCURVE pPower100;
	PCURVE pPower0;
	PCURVE pPowerAlt;

	FP BladeRadius;
	FP BladeArea;
	FP RotateDirection;
	FP GearRatio;
	FCRD PropInertia;
	PROP_TYPE PropType;
	FP PropMinPitch;
	FP PropMaxPitch;

//COMPLEX CONSTANTS
	STARTER_TYPE Starter;
	MAGNETO_TYPE MagType;

//VARIABLES
	PTHRUSTPOINT pThrustPoint;
	
	FP Speed, SpeedRpm;	//save
	FP Power0, Power100, Power;
	FP MaxThrust, Thrust, Torque;
	FCRD moment;
	FP PropInc;				  //save
	FP PropVel, SlipVel, SlipRot;	//save
	SWord ThrottleSetting;		// save							//AMM 24Jul00
	FP PropSetting;				// save							//AMM 24Jul00

//COMPLEX VARIABLES
	SWord Magnetos;	// = [ 0, 1, 2, 1+2 ]
	FP Temperature;
	FP FuelInPipes;
	FP StarterSpeed;
	FP Priming;
	bool Starting;


	void ProcessPistonEngine (AirStrucPtr const ControlledAC);
	void ComplexEngineProcess (AirStrucPtr const ControlledAC, FP fDamage, FP& fPower, FP& dTorque);
	void ProcessJetEngine (AirStrucPtr const ControlledAC);

	Engine (PMODEL, ENGINE_TYPE, FP, FP, FP, PCURVE, PCURVE, PCURVE, PCURVE);	// Jet
	Engine (PMODEL, ENGINE_TYPE);	// Piston
	~Engine ();

	void SetEngine(FP horsepower, FP maxrpm, FP minrpm, FP inertia)
	{
		p0 = horsepower * 745.7;
		Rpm100  = maxrpm;
		Rpm0    = minrpm;
		MoI     = inertia;
	}

	void SetCurves(char* acp0, char* p0, char* acp1, char* p1, char* acpa, char* pa)
	{
		if ((*acp0 != 0) && (*p0 != 0))
			pPower0 = _CurveRsc.FindCurve (acp0, p0);
		else pPower0 = NULL;

		if ((*acp1 != 0) && (*p1!= 0))
			pPower100 = _CurveRsc.FindCurve (acp1, p1);
		else pPower100 = NULL;

		if ((*acpa != 0) && (*pa != 0))
			pPowerAlt = _CurveRsc.FindCurve (acpa, pa);
		else pPowerAlt = NULL;
	}

	void SetPropeller(FP radius, FP area, FP ratio, FP dir)
	{
		BladeRadius = radius;
		BladeArea 	= area;
		GearRatio   = ratio;
		RotateDirection = dir;
	}

	void SetPropInertia(FP ixx, FP iyy, FP izz)
	{
		PropInertia.x = ixx;
		PropInertia.y =	iyy;
		PropInertia.z =	izz;
	}

	void SetPropType(PROP_TYPE proptype, FP minpitch, FP maxpitch)
	{
		PropType     = proptype;
		PropMinPitch = Degs2Rads(minpitch);
		PropMaxPitch = Degs2Rads(maxpitch);
	}

	void NullThis ();

	LINKEDLIST<Engine> List;

	void SetThrustPoint (PTHRUSTPOINT thrust) { pThrustPoint = thrust; }

};
class  Engine;
typedef class  Engine ENGINE, *PENGINE, **PPENGINE;

#endif
