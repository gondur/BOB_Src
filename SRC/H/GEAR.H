//------------------------------------------------------------------------------
//Filename       gear.h
//System         
//Author         Andrew McRae
//Date           Thu 27 Feb 1997
//Description    
//------------------------------------------------------------------------------
#include "aerodev.h"

#ifndef	GEAR_Included
#define	GEAR_Included

#define	DEFAULT_GEAR 0

enum UC_STATUS
{
	OFFGROUND,
	TOUCHING,
	BOTTOMEDOUT,
	ALLBOTTOMEDOUT,
	CRASHED,
	UNDEFINED
};

enum GEAR_IDENT
{
	NOSE,
	TAIL,
	PORT,
	STBD
};

// Undercarraige
class Gear {

public:

	GEAR_IDENT Ident;

	PMODEL pModel;
	PAERODEVICE pDevice;

	// suspension
	FP CStiffness;
	FP CDamping;

	// tyres & brakes
	FP RollRes;
	FP CFriction;
	FP CBrake;

	// in ac coords
	FCRD pos0;
	FCRD pos1;
	FP LegLength;
	FCRD LegVec;

	FCRD GroundForce;
	FCRD LegForce;
	FCRD TyreForce;

	FP LegPos;		//[0,1]
	FP OldLegPos;	//[0,1]
	FCRD WheelPos;

//DEADCODE CB 03/11/99 	FCRD IntPos;
	FP IntL;


	Bool Touched;

	void SetDimensions (FP, FP, FP, FP, FP, FP);
	void SetSuspension (FP, FP);
	void SetTyres (FP, FP, FP);
	void SetGearDevice(AeroDevice::DT_TYPE, KeyVal3D);

	Bool CalcIntL (UByte*);
	void CalcIntPos ();


	void CalcLegForce_Reaction(AirStrucPtr const ControlledAC, UByte* Texture);
	void Gear::CalcTyreSideForce (AirStrucPtr const ControlledAC, FP TotalReaction, FP forcex, UByte Texture);
	Gear (PMODEL, GEAR_IDENT);
	~Gear ();

	LINKEDLIST<Gear> List;

};
class Gear;
typedef class Gear  GEAR, *PGEAR, **PPGEAR;

#endif

