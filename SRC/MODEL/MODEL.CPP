/*
	 Battle of Britain
	 Copyright (C) 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at bob@rowansoftware.com a
better place to ask is http://www.simhq.com/ or even :-
http://www.simhq.com/cgi-bin/boards/cgi-bin/forumdisplay.cgi?action=topics&forum=Battle+of+Britain&number=40&DaysPrune=20&LastLogin=
*/

//////////////////////////////////////////////////////////////////////
//
// Module:	Model.cpp
//------------------------------------------------------------------------------
//Filename       model.cpp
//System         
//Author         Andrew McRae
//Date           Tue 7 Jan 1997
//Description    Mig Alley Flight Model
//------------------------------------------------------------------------------
//
//To get calib data define following inmodel.h
//		#define EMIT_HM_DATA
//		#define EMIT_DOGHOUSE_DATA
//		#define PS_CALCS

#ifndef	NDEBUG
//#define	_NOFLIGHTMODEL_
//#define	_LOCKTOGROUND_
#endif

#include <stdio.h>
#include <string.h>

#include "dosdefs.h"
#include "monotxt.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "ranges.h"
#include "myangles.h"
#include "planetyp.h"
#include "collided.h"
#include "mytime.h"
#include "myerror.h"
#include "savegame.h"
#include "3dinstr.h"												//RJS 02Dec97
#include "miles.h"
#include "replay.h"
#include "persons2.h"
#include "flymodel.h"
#include "stdio.h"
#include "aerodev.h"
#include	"fastmath.h"							//RJS 22Feb00
#include	"sqddiary.h"												//RJS 30Oct00
#include	"grid.h"

extern Replay _Replay;

//#define LOGVALS

#ifdef DISPLAY_MONO_DATA
#pragma message(__HERE__ "Mono fm output enabled!!!!!!!!!!!")
#else
#pragma message(__HERE__ "Mono fm output disabled")
#endif

static FCRD AveRotVel;

extern WayPoint WP_PATROL_BASE0;
extern WayPoint WP_PATROL_BASE1;

// **********************************************************
//
// Notes:
//
// Units								
//
// Displacement			UNITY = 0.01 Metres
// Force				UNITY = 1 Newton
// Mass					UNITY = 0.01 Kilogrammes
// Time					UNITY = 0.01 Seconds
// Temperature			UNITY = 1 Kelvin
// Angle				UNITY = UNITY
//
// Parameter units								SI equiv
//
// Position				1 = 1cm					= 1e-2 M				
// Velocity				1 = 1cm / 1csec			= 1e+0 M/s
// Acceleration			1 = 1cm / 1csec^2		= 1e+2 M/s^2
// Angle				1 = 1radian				= 1e+0 1
// Angular Velocity		1 = 1rad / 1csec		= 1e+2 1/s 
// Angular Accel		1 = 1rad / 1csec^2		= 1e+4 1/s^2
// Torque				1 = 1N * 1cm			= 1e-2 N.M
// Moment of inertia	1 = 0.01kg * 1cm^2		= 1e-6 kg.M^2
// Density				1 = 0.01kg / 1cm^3		= 1e+4 kg/M^3
// Pressure				1 = 1N / 1cm^2			= 1e+4 pascals
// Area					1 = 1cm^2				= 1e-4 M^2
// Temperature			1 = 1K					= 1e+0 K
// Stiffness			1 = 1N / 1cm			= 1e+2 N/M
// Linear Damping		1 = 1N * 1csec / 1cm	= 1e+0 Ns/M
// Power				1 = 1N * 1cm / 1csec	= 1e+0 Watts
// Energy				1 = 1N * 1cm			= 1e-2 Joules
// Specific Heat		1 = (1N*1cm)/(K*0.01kg)	= 1e+0 Joules/(Kelvin.Kg)
//
// **********************************************************

//ATMOSPHERE Sky;

PMODEL ModelList = NULL;

SWord Model::stretchyNeck;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewModel
//Author		Andrew McRae
//Date			Thu 1 May 1997
//
//Description	Creates a Model (for Airstruc Constructor)
//
//Inputs		AirStrucPtr
//
//Returns		Bool
//
//------------------------------------------------------------------------------
Bool NewModel (AirStrucPtr const ControlledAC)
{

	static ULong Count = 0;

	ControlledAC->fly.AeroDeviceCnt = 0;//RJS 18Sep98
	ControlledAC->fly.pModel = NULL;
	ControlledAC->fly.pModel = new Model ();
	if (ControlledAC->fly.pModel == NULL)
		return FALSE;

	ControlledAC->fly.pModel->Ident = Count;
	Count ++;

	ControlledAC->fly.pModel->FrameCount = ControlledAC->uniqueID.count;//->fly.pModel->Ident;	

	ControlledAC->fly.pAcmModel = &ControlledAC->fly.pModel->ACMModel;
	ControlledAC->fly.pInst = &ControlledAC->fly.pModel->Inst;
	ControlledAC->World.X = 0;
	ControlledAC->World.Y = 0;
	ControlledAC->World.Z = 0;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteModel
//Author		Andrew McRae
//Date			Thu 1 May 1997
//
//Description	Deletes a Model (for AirStruc Destructor)
//
//Inputs		AirStrucPtr
//
//Returns	
//
//------------------------------------------------------------------------------
void DeleteModel (AirStrucPtr const ControlledAC)
{
	if (ControlledAC->fly.pModel != NULL)
	{
		delete ControlledAC->fly.pModel;
		ControlledAC->fly.pModel = NULL;
	}
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Model
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Model Class Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Model::Model ()
{
	NullVec (Pos);
	NullOri (Ori);

	NullVec (Vel);
	NullVec (ShapeCoG);

	EngineList = NULL;
	GearList = NULL;
	AnimList = NULL;
	ThrustList = NULL;
	SurfaceList = NULL;
	MainPlaneList = NULL;
	CylinderList = NULL;
	DeviceList = NULL;

	ControlLossV0 = 150;
	ControlLossV1 = 180;
	
	ControlForce = 100;			// Relative amount of force feedback
	BuffetForce  = 100; 

	List.Attach (&ModelList, this);

	CrashTime = 0;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Model
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Destructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Model::~Model ()
{
	ClearLists ();
	List.Detach (this);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearLists
//Author		Andrew McRae
//Date			Fri 21 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ClearLists ()
{
	while (EngineList != NULL) delete EngineList;
	while (GearList != NULL) delete GearList;
 	while (AnimList != NULL) delete AnimList;

	while (ThrustList != NULL) delete ThrustList;
	while (SurfaceList != NULL) delete SurfaceList;
	while (MainPlaneList != NULL) delete MainPlaneList;
	while (CylinderList != NULL) delete CylinderList;
	while (DeviceList != NULL) delete DeviceList;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Initialise
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Set up model params
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Initialise (AirStrucPtr const ControlledAC, Bool status)
{
	FirstCycle = TRUE;
	Type = AT_VOID;
//DEADCODE AMM 24/11/99 	MODEL_DT = 2;

	Spinning = FALSE;												  //RDH 01/03/99

	ACMModel.Clear ();;//AcmMode &= 0;

	Controlled = status;
	bACM = FALSE;
	RestartEngine = FALSE;

	ACMModel.Null ();

	NullVec(Vel);
	NullVec(RotVel);
	NullVec(AveRotVel);

	NullVec (Acc);
	NullVec (RotAcc);
	NullVec (NettForce);
	NullVec (NettMoment);

	NullVec (StoresForce);
	NullVec (StoresMoment);
	TotalBuffet = 0.0;

	AmbDensity = 0.0001225;
	AmbTemp = 288.15;
	AmbPres = 10.3215;
	NullVec (AirVel);
	AirSpeed = 0;
	DynamicPressure = 0;
	CheatAcc.x = 32767;
	CheatAcc.y = 32767;
	CheatAcc.z = 32767;
	Blood = 1;

	EmergencyGearUsed = FALSE;
	GearTouched = FALSE;
	GearSkid = FALSE;
//DeadCode CSB 9Nov00 	if(!GroundHeight)
//DeadCode CSB 9Nov00 		GroundHeight = _Collide.GroundAltitude(ControlledAC->World);
	if(ControlledAC->ai.homebase)
		GroundHeight = ControlledAC->ai.homebase->World.Y;
	else
		GroundHeight = 0;

	Mass = 0;
	NullVec (RotInertia);
	NullVec (InertiaMoment);

	fRoll = 0;
	fPitch = 0;
	fHdg = 0;

	Inst.Null ();


	Elevator = 0;
	Aileron = 0;
	Rudder = 0;
	ElevatorTrim = 0;
	AileronTrim = 0;
	RudderTrim = 0;
	BombingPhase = 0;

	ModelThrottle = 100;
	ModelPropSetting = 100;
	BoostCutout = false;
	LeftWheelBrake = 0;
	RightWheelBrake = 0;
//DEADCODE CSB 02/12/99 	SlatOutPressure = 0;
//DEADCODE CSB 02/12/99 	SlatInPressure = 0;

	PowerBoost = 1;
	MaxG = 9;
	MinG = -4;
	FuelCockType = FC_VOID;
//DeadCode AMM 24Jul00 	FuelCockPos = 0;

	ContrailDuration = 0;										//D 02Apr98

	SlipstreamRudder = 0;	//CSB 28/10/99	

#ifdef RESET_AC_POS
	// Temporary
	if (Controlled)
	{
		if (ControlledAC->World.X == 0)
		{
			ControlledAC->World.X = 0x1215242;
			ControlledAC->World.Y = FT_15000;
			ControlledAC->World.Y = FT_2000;
			ControlledAC->World.Z = 0x194049c;
		}
	}
	if (!Controlled)
	{
		if (ControlledAC->World.X == 0)
		{
			ControlledAC->World.X = 0x1215242;
			ControlledAC->World.Y = FT_15000;
			ControlledAC->World.Y = FT_2000;
			ControlledAC->World.Z = 0x194049c;
		}
		ControlledAC->World.Y = FT_15000;
		ControlledAC->World.Y = FT_2000;
	}

//	if (!Controlled)
	{
		ControlledAC->vel *= 8;
	}

#endif

//	ControlledAC->World.Y = FT_20000;		//temp rdh
	UpdateModel (ControlledAC);
	SetupAircraft (ControlledAC);
	UpdateAirStruc (ControlledAC);

	if(		(	(ControlledAC->movecode == AUTO_WAIT4TIME)
			||	(ControlledAC->movecode == AUTO_TAKEOFF)
			||	(ControlledAC->movecode == AUTO_TRAININGTAKEOFF)
			||	(ControlledAC->movecode == AUTO_LANDING)
			||	(ControlledAC->movecode == AUTO_TRAININGLANDING)	)
		&&	(ControlledAC->vel_ < ControlledAC->classtype->minvel)	)
		GearDown(ControlledAC);
	else
		GearUp (ControlledAC);

	SHAPE.BombBayDoors(ControlledAC, ANIM_BOMBDOORS_CLOSE, true);

	ControlledAC->ai.desiredturn = 0;

// Crappy weapon init fix.....								//RJS 10Jun97
//DeadCode RJS 21Jun00 	ControlledAC->weap.weapontype = LT_BULLET;					//RJS 11May98
	fixgunsight = true;	//CSB 09/06/99	


	if (Controlled)
	{
		switch(Type)
		{
			case AT_SPITFIRE:
			{	
				Inst.SetFuelGaugeSelector(0, 11700000, 1, 9500000, -1, -1, -1, -1);
				break;
			}
			case AT_HURRICANE:
			{	
				Inst.SetFuelGaugeSelector(0, 11700000, 2, 9500000, 1, 11700000, -1, -1);
				break;
			}
			case AT_BF109:
			{	
				Inst.SetFuelGaugeSelector(0, 30000000, -1, -1, -1, -1, -1, -1);
				break;
			}
			case AT_BF110:
			{	
				Inst.SetFuelGaugeSelector(2, 30000000, 0, 30000000, 1, 30000000, 3, 30000000);
				break;
			}
			case AT_JU87B:
			{	
				Inst.SetFuelGaugeSelector(0, 19500000, 1, 19500000, -1, -1, -1, -1);
				break;
			}
		}

		animptr	oldadptr	= ControlledAC->Anim;				//AMM 28Apr99

		Inst.DialCnt = 0;										//AMM 28Apr99
		Inst.DialSrcCnt = 0;									//RJS 01Dec99
		Inst.TimedDialCnt = 0;										  //CSB 04/01/00

		ControlledAC->Anim = (AnimSizeField)sizeof(AircraftAnimData);
		ControlledAC->Anim = (AnimFlagField)((1<<MINANIM) + (1<<AIRCRAFTANIM) + (1<<POLYPITANIM));
		PolyPitAnimData*	adptr = (PolyPitAnimData*) ControlledAC->Anim;

		switch(Type)
		{
			case AT_SPITFIRE:
			{
				Inst.AddAutoDial(adptr,&adptr->acairspeed,&Inst,&Inst.I_IndicatedAirSpeed, 50.0, 400.0, 1.55);
				Inst.AddAutoDial(adptr,&adptr->acclimb,&Inst,&Inst.I_RateOfClimb, -4000.0, 4000.0);
				Inst.AddAutoDial(adptr,&adptr->acaltitude,&Inst,&Inst.I_Altitude, 0.0, 100000.0);
				Inst.AddAutoDial(adptr,&adptr->acalt10,&Inst,&Inst.I_Altitude, 0.0, 100000.0, 10);
				Inst.AddAutoDial(adptr,&adptr->acalt100,&Inst,&Inst.I_Altitude, 0.0, 100000.0, 100);
				Inst.AddAutoDial(adptr,&adptr->acturn,&Inst,&Inst.I_Turn, -4.0, 4.0);
				Inst.AddAutoDial(adptr,&adptr->acslip,&Inst,&Inst.I_Slip, -20.0, 20.0);
				Inst.AddAutoDial(adptr,&adptr->acelevatortrim,&Inst,&Inst.I_ElevatorTrimTab, -32767, 32767);
				Inst.AddAutoDial(adptr,&adptr->acfuelcontent,&Inst,&Inst.I_FuelContents, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->acenginespeed,&Inst,&Inst.I_EngineRpm0, 0.0, 10000.0);
				Inst.AddAutoDial(adptr,&adptr->acboost,&Inst,&Inst.I_Boost0, 0.0, 13.0);
				Inst.AddAutoDial(adptr,&adptr->acvoltmeter,&Inst,&Inst.I_VoltMeter, 0.0, 24.0);

				Inst.AddAutoDial(adptr,&adptr->acfuelpressure,&Inst,&Inst.I_FuelPressure, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acoilpressure,&Inst,&Inst.I_OilPressure, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acoiltemp,&Inst,&Inst.I_OilTemperature, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acradiatortemp,&Inst,&Inst.I_RadiatorTemperature0, 0, 150);

				Inst.AddAutoDial(adptr,&adptr->accompass,&Inst,&Inst.I_Heading, 0, 360);
				Inst.AddAutoDial(adptr,&adptr->acdirection,&Inst,&Inst.I_Heading, 0, 360);

				Inst.AddAutoDial(adptr,&adptr->acundercarriage, &Inst,&Inst.I_UndercarraigePosition0, 0, 255);	//auto scale 0-2

				Inst.AddAutoDial(adptr,&adptr->i_throttle, &Inst,&Inst.C_Throttle0, 0.0, 100.0);
				Inst.AddAutoDial(adptr,&adptr->i_proppitch, &Inst,&Inst.C_PropPitch0, 0.0, 100.0);
				Inst.AddAutoDial(adptr,&adptr->i_flaps,&Inst,&Inst.C_FlapLever, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_undercarriage,&Inst,&Inst.C_UndercarraigeLever, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_emergencyunder,&Inst,&Inst.C_EmergencyUndercarraige, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_hoodcatch,&Inst,&Inst.C_HoodCatch, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_magnetos,&Inst,&Inst.C_Magnetos0, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_fuelcock,&Inst,&Inst.C_FuelCock0, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_enginestarter,&Inst,&Inst.C_StarterButton0, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_elevator,&Inst,&Inst.C_ElevatorTrim, -32767.0, 32767.0);
				Inst.AddAutoDial(adptr,&adptr->i_rudder,&Inst,&Inst.C_RudderTrim, -32767.0, 32767.0);
				Inst.AddAutoDial(adptr,&adptr->i_primer,&Inst,&Inst.C_PrimerPump0, 0, 256);//RJS 09May00
				Inst.AddAutoDial(adptr,&adptr->acgyrocompass,&Inst,&Inst.I_Heading, 0, 360);//RJS 02Oct00

				Inst.AddAutoDial(adptr,&adptr->i_fueltankselect,&Inst,&Inst.C_FuelGuageSelector, 0, 2);//RJS 18Oct00

				break;
			}

			case AT_HURRICANE:
			{
				Inst.AddAutoDial(adptr,&adptr->acairspeed,&Inst,&Inst.I_IndicatedAirSpeed, 50.0, 400.0, 1.55);//AMM 06Jul00
				Inst.AddAutoDial(adptr,&adptr->acclimb,&Inst,&Inst.I_RateOfClimb, -4000.0, 4000.0);
				Inst.AddAutoDial(adptr,&adptr->acaltitude,&Inst,&Inst.I_Altitude, 0, 100000);
				Inst.AddAutoDial(adptr,&adptr->acalt10,&Inst,&Inst.I_Altitude, 0, 100000, 10);
				Inst.AddAutoDial(adptr,&adptr->acalt100,&Inst,&Inst.I_Altitude, 0, 100000, 100);
				Inst.AddAutoDial(adptr,&adptr->acturn,&Inst,&Inst.I_Turn, -4.0, 4.0);
				Inst.AddAutoDial(adptr,&adptr->acslip,&Inst,&Inst.I_Slip, -20.0, 20.0);
				Inst.AddAutoDial(adptr,&adptr->acfuelcontent,&Inst,&Inst.I_FuelContents, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->acenginespeed,&Inst,&Inst.I_EngineRpm0, 0.0, 10000.0);
				Inst.AddAutoDial(adptr,&adptr->acboost,&Inst,&Inst.I_Boost0, 0.0, 13.5);//AMM 06Jul00
				Inst.AddAutoDial(adptr,&adptr->acvoltmeter,&Inst,&Inst.I_VoltMeter, 0.0, 24.0);
				Inst.AddAutoDial(adptr,&adptr->acflapindicator,&Inst,&Inst.I_FlapsIndicator, 0, 16384);

				Inst.AddAutoDial(adptr,&adptr->acfuelpressure,&Inst,&Inst.I_FuelPressure, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acoilpressure,&Inst,&Inst.I_OilPressure, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acoiltemp,&Inst,&Inst.I_OilTemperature, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acradiatortemp,&Inst,&Inst.I_RadiatorTemperature0, 0, 150);

				Inst.AddAutoDial(adptr,&adptr->accompass,&Inst,&Inst.I_Heading, 0, 360);
				Inst.AddAutoDial(adptr,&adptr->acdirection,&Inst,&Inst.I_Heading, 0, 360);

				Inst.AddAutoDial(adptr,&adptr->acundercarriage, &Inst,&Inst.I_UndercarraigePosition0, 0, 255);	//auto scale 0-2
				Inst.AddAutoDial(adptr,&adptr->acundercarriage2, &Inst,&Inst.I_UndercarraigePosition1, 0, 255);	//auto scale 0-2

				Inst.AddAutoDial(adptr,&adptr->i_throttle, &Inst,&Inst.C_Throttle0, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_proppitch, &Inst,&Inst.C_PropPitch0, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_flaps,&Inst,&Inst.C_FlapLever, -1, 1);
				Inst.AddAutoDial(adptr,&adptr->i_undercarriage,&Inst,&Inst.C_UndercarraigeLever, -1, 1);
				Inst.AddAutoDial(adptr,&adptr->i_emergencyunder,&Inst,&Inst.C_EmergencyUndercarraige, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_hoodcatch,&Inst,&Inst.C_HoodCatch, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_magnetos,&Inst,&Inst.C_Magnetos0, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_fuelcock,&Inst,&Inst.C_FuelCock0, 0, 2);
				Inst.AddAutoDial(adptr,&adptr->i_enginestarter,&Inst,&Inst.C_StarterButton0, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_boostcutout,&Inst,&Inst.C_BoostControlCutout, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_fueltankselect,&Inst,&Inst.C_FuelGuageSelector, 0, 2);
				Inst.AddAutoDial(adptr,&adptr->i_primer,&Inst,&Inst.C_PrimerPump0, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->i_elevator,&Inst,&Inst.C_ElevatorTrim, -32767, 32767);
				Inst.AddAutoDial(adptr,&adptr->i_rudder,&Inst,&Inst.C_RudderTrim, -32767, 32767);

				Inst.AddAutoDial(adptr,&adptr->acunderflap,&Inst,&Inst.C_H_Gate,0,4);	//RJS 19May00

				Inst.AddAutoDial(adptr,&adptr->acgyrocompass,&Inst,&Inst.I_Heading, 0, 360);//RJS 02Oct00
				break;
			}

			case AT_BF109:
			{
				Inst.AddAutoDial(adptr,&adptr->acairspeed,&Inst,&Inst.I_IndicatedAirSpeed, 100.0, 750.0);//AMM 06Jul00
				Inst.AddAutoDial(adptr,&adptr->acaltitude,&Inst,&Inst.I_Altitude, 0., 100000.);
				Inst.AddAutoDial(adptr,&adptr->acalt10,&Inst,&Inst.I_Altitude, 0., 100000., 10.);
				Inst.AddAutoDial(adptr,&adptr->acalt100,&Inst,&Inst.I_Altitude, 0., 100000., 100.);
				Inst.AddAutoDial(adptr,&adptr->acturn,&Inst,&Inst.I_Turn, -4.0, 4.0);
				Inst.AddAutoDial(adptr,&adptr->acslip,&Inst,&Inst.I_Slip, -20.0, 20.0);
				Inst.AddAutoDial(adptr,&adptr->acfuelcontent,&Inst,&Inst.I_FuelContents, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->acenginespeed,&Inst,&Inst.I_EngineRpm0, 300.0, 3800.0);
				Inst.AddAutoDial(adptr,&adptr->acboost,&Inst,&Inst.I_Boost0, 1.0, 2.0);

				Inst.AddAutoDial(adptr,&adptr->acfuelpressure,&Inst,&Inst.I_FuelPressure, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acoilpressure,&Inst,&Inst.I_OilPressure, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acoiltemp,&Inst,&Inst.I_OilTemperature, 0, 120);
				Inst.AddAutoDial(adptr,&adptr->acradiatortemp,&Inst,&Inst.I_RadiatorTemperature0, 0, 120);
				Inst.AddAutoDial(adptr,&adptr->acproppitch01,&Inst,&Inst.I_PropPitch0, 0.0, 120.0);//, 0.1);
				Inst.AddAutoDial(adptr,&adptr->acproppitch02,&Inst,&Inst.I_PropPitch0, 0.0, 100.0, 10.0);//, 0.01);
				Inst.AddAutoDial(adptr,&adptr->acgearindicator, &Inst,&Inst.I_MechanicalUndercarraigeIndicator, 0, 127);

				Inst.AddAutoDial(adptr,&adptr->acundercarriage, &Inst,&Inst.I_UndercarraigePosition0, 0, 255);	//auto scale 0-2
				Inst.AddAutoDial(adptr,&adptr->acundercarriage2, &Inst,&Inst.I_UndercarraigePosition1, 0, 255);

				Inst.AddAutoDial(adptr,&adptr->accompass,&Inst,&Inst.I_Heading, 0, 360);
				Inst.AddAutoDial(adptr,&adptr->acdirection,&Inst,&Inst.I_Heading, 0, 360);

				Inst.AddAutoDial(adptr,&adptr->i_throttle, &Inst,&Inst.C_Throttle0, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_proppitch, &Inst,&Inst.C_PropPitch0, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_flaps,&Inst,&Inst.C_FlapLever, 0, 16384);
				Inst.AddAutoDial(adptr,&adptr->i_undercarriage,&Inst,&Inst.C_UndercarraigeLever, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_emergencyunder,&Inst,&Inst.C_EmergencyUndercarraige, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_hoodcatch,&Inst,&Inst.C_HoodCatch, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_magnetos,&Inst,&Inst.C_Magnetos0, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_fuelcock,&Inst,&Inst.C_FuelCock0, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_enginestarter,&Inst,&Inst.C_StarterButton0, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_primer,&Inst,&Inst.C_PrimerPump0, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->i_elevator,&Inst,&Inst.C_ElevatorTrim, -32767, 32767);
				break;
			}

			case AT_BF110:
			{
				Inst.AddAutoDial(adptr,&adptr->acairspeed,&Inst,&Inst.I_IndicatedAirSpeed, 100.0, 750.0);//AMM 06Jul00
				Inst.AddAutoDial(adptr,&adptr->acaltitude,&Inst,&Inst.I_Altitude, 0., 100000.);
				Inst.AddAutoDial(adptr,&adptr->acalt10,&Inst,&Inst.I_Altitude, 0., 100000., 10.);
				Inst.AddAutoDial(adptr,&adptr->acalt100,&Inst,&Inst.I_Altitude, 0., 100000., 100.);
				Inst.AddAutoDial(adptr,&adptr->acclimb,&Inst,&Inst.I_RateOfClimb, -2000.0, 2000.0);
				Inst.AddAutoDial(adptr,&adptr->acturn,&Inst,&Inst.I_Turn, -4.0, 4.0);
				Inst.AddAutoDial(adptr,&adptr->acslip,&Inst,&Inst.I_Slip, -20.0, 20.0);
				Inst.AddAutoDial(adptr,&adptr->acfuelcontent,&Inst,&Inst.I_FuelContents, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->acenginespeed,&Inst,&Inst.I_EngineRpm0, 300.0, 3800.0);
				Inst.AddAutoDial(adptr,&adptr->acengine2speed,&Inst,&Inst.I_EngineRpm1, 300.0, 3800.0);
				Inst.AddAutoDial(adptr,&adptr->acboost,&Inst,&Inst.I_Boost0, 0.6, 1.8);
				Inst.AddAutoDial(adptr,&adptr->acboost2,&Inst,&Inst.I_Boost1, 0.6, 1.8);

				Inst.AddAutoDial(adptr,&adptr->acradiatortemp,&Inst,&Inst.I_RadiatorTemperature0, 0, 120);
				Inst.AddAutoDial(adptr,&adptr->acradiatortemp2,&Inst,&Inst.I_RadiatorTemperature1, 0, 120);
				Inst.AddAutoDial(adptr,&adptr->acproppitch01,&Inst,&Inst.I_PropPitch0, 0.0, 120.0);
				Inst.AddAutoDial(adptr,&adptr->acproppitch02,&Inst,&Inst.I_PropPitch0, 0.0, 100.0, 10.0);
				Inst.AddAutoDial(adptr,&adptr->acproppitch11,&Inst,&Inst.I_PropPitch1, 0.0, 120.0);
				Inst.AddAutoDial(adptr,&adptr->acproppitch12,&Inst,&Inst.I_PropPitch1, 0.0, 100.0, 10.0);

				Inst.AddAutoDial(adptr,&adptr->accompass,&Inst,&Inst.I_Heading, 0, 360);
				Inst.AddAutoDial(adptr,&adptr->acdirection,&Inst,&Inst.I_Heading, 0, 360);

				Inst.AddAutoDial(adptr,&adptr->acundercarriage, &Inst,&Inst.I_UndercarraigePosition0, 0, 255);	//auto scale 0-2
				Inst.AddAutoDial(adptr,&adptr->acundercarriage2, &Inst,&Inst.I_UndercarraigePosition1, 0, 255);	//auto scale 0-2

				Inst.AddAutoDial(adptr,&adptr->i_throttle, &Inst,&Inst.C_Throttle0, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_throttle2, &Inst,&Inst.C_Throttle1, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_proppitch, &Inst,&Inst.C_PropPitch0, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_proppitch2, &Inst,&Inst.C_PropPitch1, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_flaps,&Inst,&Inst.C_FlapLever, 0, 2);
				Inst.AddAutoDial(adptr,&adptr->i_undercarriage,&Inst,&Inst.C_UndercarraigeLever, 0, 2);
				Inst.AddAutoDial(adptr,&adptr->i_emergencyunder,&Inst,&Inst.C_EmergencyUndercarraige, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_hoodcatch,&Inst,&Inst.C_HoodCatch, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_magnetos,&Inst,&Inst.C_Magnetos0, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_magnetos2,&Inst,&Inst.C_Magnetos1, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_fuelcock,&Inst,&Inst.C_FuelCock0, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_fuelcock2,&Inst,&Inst.C_FuelCock1, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_enginestarter,&Inst,&Inst.C_StarterButton0, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_enginestarter2,&Inst,&Inst.C_StarterButton1, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_primer,&Inst,&Inst.C_PrimerPump0, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->i_primer2,&Inst,&Inst.C_PrimerPump1, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->i_fueltankselect,&Inst,&Inst.C_FuelGuageSelector, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_elevator,&Inst,&Inst.C_ElevatorTrim, -32767, 32767);
				Inst.AddAutoDial(adptr,&adptr->i_rudder,&Inst,&Inst.C_RudderTrim, -32767, 32767);

		 		Inst.AddAutoDial(adptr,&adptr->acgyrocompass,&Inst,&Inst.I_Heading,0.0,360.0,-182.04);//RJS 20Mar00
				Inst.AddTimedDial(adptr,&adptr->acgyrocompass,ARC_1SEC,ARC_1SEC<<1);//RJS 20Mar00

				break;
			}

			case AT_JU87B:
			{
				Inst.AddAutoDial(adptr,&adptr->acaltitude,&Inst,&Inst.I_Altitude, 0.0, 100000.0);
				Inst.AddAutoDial(adptr,&adptr->acalt10,&Inst,&Inst.I_Altitude, 0.0, 100000.0, 10);
				Inst.AddAutoDial(adptr,&adptr->acalt100,&Inst,&Inst.I_Altitude, 0.0, 100000.0, 100);
				Inst.AddAutoDial(adptr,&adptr->acaltradio,&Inst,&Inst.I_RadioAltitude, 0.0, 10000.0);
				Inst.AddAutoDial(adptr,&adptr->acaltradio10,&Inst,&Inst.I_RadioAltitude, 0.0, 10000.0, 10);
 				Inst.AddAutoDial(adptr,&adptr->acdirection,&Inst,&Inst.I_Heading, 0, 360);
				Inst.AddAutoDial(adptr,&adptr->acturn,&Inst,&Inst.I_Turn, -4.0, 4.0);
				Inst.AddAutoDial(adptr,&adptr->acslip,&Inst,&Inst.I_Slip, -20.0, 20.0);
				Inst.AddAutoDial(adptr,&adptr->acairspeed,&Inst,&Inst.I_IndicatedAirSpeed, 100.0, 750.0);//AMM 06Jul00
				Inst.AddAutoDial(adptr,&adptr->acclimb,&Inst,&Inst.I_RateOfClimb, -16.0, 16.0);

				Inst.AddAutoDial(adptr,&adptr->acenginespeed,&Inst,&Inst.I_EngineRpm0, 600.0, 3600.0);
				Inst.AddAutoDial(adptr,&adptr->acboost,&Inst,&Inst.I_Boost0, 0.6, 1.8);

				Inst.AddAutoDial(adptr,&adptr->acfuelcontent,&Inst,&Inst.I_FuelContents, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->acradiatortemp,&Inst,&Inst.I_RadiatorTemperature0, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acoiltemp,&Inst,&Inst.I_OilTemperature, 0, 150);
				Inst.AddAutoDial(adptr,&adptr->acoilcontent,&Inst,&Inst.I_OilContent, 0, 150);
				
				Inst.AddAutoDial(adptr,&adptr->acfuelpressure,&Inst,&Inst.I_FuelPressure, -30, 30);
				Inst.AddAutoDial(adptr,&adptr->accompass,&Inst,&Inst.I_Heading, 0, 360);

				Inst.AddAutoDial(adptr,&adptr->acgyrocompass,&Inst,&Inst.I_Heading,0.0,360.0,-182.04);//RJS 06Apr00
				Inst.AddTimedDial(adptr,&adptr->acgyrocompass,ARC_1SEC,ARC_1SEC<<1);//RJS 06Apr00
				
				//Dive Preset Indicator

				Inst.AddAutoDial(adptr,&adptr->i_throttle, &Inst,&Inst.C_Throttle0, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_proppitch, &Inst,&Inst.C_PropPitch0, 0, 100);
				Inst.AddAutoDial(adptr,&adptr->i_elevator,&Inst,&Inst.C_ElevatorTrim, -32767, 32767);

				Inst.AddAutoDial(adptr,&adptr->i_flaps,&Inst,&Inst.C_FlapLever, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_divebrakes,&Inst,&Inst.C_DiveBrakeLever, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_hoodcatch,&Inst,&Inst.C_HoodCatch, 0, 1);

				Inst.AddAutoDial(adptr,&adptr->i_magnetos,&Inst,&Inst.C_Magnetos0, 0, 3);
				Inst.AddAutoDial(adptr,&adptr->i_enginestarter,&Inst,&Inst.C_StarterButton0, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_primer,&Inst,&Inst.C_PrimerPump0, 0, 255);
				Inst.AddAutoDial(adptr,&adptr->i_fuelcock,&Inst,&Inst.C_FuelCock0, 0, 1);
				Inst.AddAutoDial(adptr,&adptr->i_fuelcock2,&Inst,&Inst.C_FuelCock1, 0, 1);
				break;
			}
		}

		_Miles.SetEngine();
		ControlledAC->Anim = oldadptr;							//AMM 28Apr99
	}

	subGunSet = false;

	stretchyNeck = 0;												//RJS 27Mar00
	if(ControlledAC->vel_ > 500000)
		ControlledAC->fly.thrustpercent = ModelThrottle = 75;
	else
		ControlledAC->fly.thrustpercent = ModelThrottle = 0;

	SLong AltHome = 0;
	if(ControlledAC->ai.homebase)
		AltHome = ControlledAC->ai.homebase->World.Y;
	FP Altitude = (ControlledAC->World.Y - AltHome) * 0.032808;
		
	if (Controlled)
		OverLay.SetInfoLineVals(ControlledAC->vel_ / 1000, 0, Altitude, Inst.I_Heading, ControlledAC->fly.thrustpercent); 
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupAircraft
//Author		Andrew McRae
//Date			Fri 31 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetupAircraft (AirStrucPtr const ControlledAC)
{
	ClearLists ();
	ACMModel.BrakePower = 1;
	ACMModel.SteerRatio = 8e-6;

	ControlledAC->classtype->pSetupFunction (ControlledAC, ControlledAC->classtype->version);
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Base
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Flight Model Main Function,	called every movecode loop.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Base (AirStrucPtr const ControlledAC)
{

#ifdef WRITE_MODEL_LOG
	WriteModelLog ();
#endif


	for (ULong n = 0; n < 1; n++)
	{
		SubBase (ControlledAC);
	}

#ifdef DISPLAY_MONO_DATA

	PMODEL pModel = ModelList;
	ULong x = 25;
	ULong c = 0;

	while (pModel != NULL)
	{
		if(this == pModel)
		{
 			if(pModel->Controlled)	PrintModelData (ControlledAC,this,0,0);
			else if(x <= 50)		PrintModelData (ControlledAC,this,x,0);
		}
		if(!pModel->Controlled) x += 25;

		pModel = pModel->List.NextItem ();
		c++;
	}


#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubBase
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Flight Model Main Function,	called !!!TWICE!!! every movecode loop.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SubBase (AirStrucPtr const ControlledAC)
{

	ControlledAC->fly.gforce = 0;

#ifdef COPY_ACM_INTO_PLAYER_AC
	static COORDS3D acPos = { 0,0,0 };

	static ANGLES acHdg = ANGLES_0Deg;
	static ANGLES acPitch = ANGLES_0Deg;
	static ANGLES acRoll = ANGLES_0Deg;
#endif

	bACM = FALSE;

	if (!Controlled)
		bACM = TRUE;

#ifdef COPY_ACM_INTO_PLAYER_AC
	if (Controlled)
	{

		ControlledAC->World.X = acPos.X;
		ControlledAC->World.Y = acPos.Y + 743;
		ControlledAC->World.Z = acPos.Z - FT_75;

		ControlledAC->hdg = ANGLES_0Deg;
		ControlledAC->pitch = ANGLES_342Deg;
		ControlledAC->roll = ANGLES_0Deg;

		return;
	}
#endif

	// if (you don't want the model to do anything miss this out)
	// If not deathmovecode, do this

	if(bACM)
		ACMBase (ControlledAC);							//DAW 15Jun98
	else
	{
		if(FirstCycle)
		{
			if(!Save_Data.flightdifficulty[FD_SPINS])
			{
				Save_Data.flightdifficulty %= FD_ENGINEMANAGMENT;
				Save_Data.flightdifficulty %= FD_PROPPITCH;
			}
			else 
				if(Save_Data.flightdifficulty[FD_ENGINEMANAGMENT])
					Save_Data.flightdifficulty |= FD_PROPPITCH;
		}

		if(Save_Data.flightdifficulty[FD_SPINS])
			RealBase(ControlledAC);						//DAW 15Jun98
		else
			ArcadeBase(ControlledAC);
	}

#ifdef COPY_ACM_INTO_PLAYER_AC
	if (!Controlled)
	{
		acPos.X = ControlledAC->World.X;
		acPos.Y = ControlledAC->World.Y;
		acPos.Z = ControlledAC->World.Z;

		acHdg = ControlledAC->hdg;
		acPitch = ControlledAC->pitch;
		acRoll = ControlledAC->roll;
	}
#endif

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RealBase
//Author		Andrew McRae
//Date			Thu 8 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RealBase (AirStrucPtr const ControlledAC)
{
//**********************************************
//********  TEST CODE	//CSB 07/05/99	********
//**********************************************
//DeadCode CSB 21Sep00 	if(ControlledAC->fly.leadflight)
//DeadCode CSB 21Sep00 	{
//DeadCode CSB 21Sep00 		ControlledAC->World = ControlledAC->fly.leadflight->World;
//DeadCode CSB 21Sep00 		ControlledAC->hdg   = ControlledAC->fly.leadflight->hdg;
//DeadCode CSB 21Sep00 		ControlledAC->pitch = ControlledAC->fly.leadflight->pitch;
//DeadCode CSB 21Sep00 		ControlledAC->roll  = ControlledAC->fly.leadflight->roll;
//DeadCode CSB 21Sep00 		ControlledAC->vel_  = ControlledAC->fly.leadflight->vel_;
//DeadCode CSB 21Sep00 		ControlledAC->vel_x = ControlledAC->fly.leadflight->vel_x;
//DeadCode CSB 21Sep00 		ControlledAC->vel_y = ControlledAC->fly.leadflight->vel_y;
//DeadCode CSB 21Sep00 		ControlledAC->vel_z = ControlledAC->fly.leadflight->vel_z;
//DeadCode CSB 21Sep00 
//DeadCode CSB 21Sep00 		static FP distbehind = 10000.0;
//DeadCode CSB 21Sep00 		static FP distabove  = 0.0;
//DeadCode CSB 21Sep00 
//DeadCode CSB 21Sep00 		ControlledAC->World.X -= distbehind * FP(ControlledAC->vel_x) / FP(ControlledAC->vel_);
//DeadCode CSB 21Sep00 		ControlledAC->World.Y -= distbehind * FP(ControlledAC->vel_y) / FP(ControlledAC->vel_) - distabove;
//DeadCode CSB 21Sep00 		ControlledAC->World.Z -= distbehind * FP(ControlledAC->vel_z) / FP(ControlledAC->vel_);
//DeadCode CSB 21Sep00 		ControlledAC->uniqueID.changed = TRUE;
//DeadCode CSB 21Sep00 
//DeadCode CSB 21Sep00 		UpdateModel(ControlledAC);
//DeadCode CSB 21Sep00 		FrameCount++;
//DeadCode CSB 21Sep00 
//DeadCode CSB 21Sep00 		return;
//DeadCode CSB 21Sep00 	}

//DeadCode CSB 11Sep00 	if(ControlledAC->fly.leadflight)
//DeadCode CSB 11Sep00 	{
//DeadCode CSB 11Sep00 		ControlledAC->World = ControlledAC->fly.leadflight->World;
//DeadCode CSB 11Sep00 		ControlledAC->World.Y += 2500;
//DeadCode CSB 11Sep00 		ControlledAC->hdg   = ControlledAC->fly.leadflight->hdg;
//DeadCode CSB 11Sep00 		ControlledAC->pitch = ControlledAC->fly.leadflight->pitch;
//DeadCode CSB 11Sep00 		ControlledAC->roll  = ControlledAC->fly.leadflight->roll;
//DeadCode CSB 11Sep00 		ControlledAC->vel_  = ControlledAC->fly.leadflight->vel_;
//DeadCode CSB 11Sep00 		ControlledAC->vel_x = ControlledAC->fly.leadflight->vel_x;
//DeadCode CSB 11Sep00 		ControlledAC->vel_y = ControlledAC->fly.leadflight->vel_y;
//DeadCode CSB 11Sep00 		ControlledAC->vel_z = ControlledAC->fly.leadflight->vel_z;
//DeadCode CSB 11Sep00 		ControlledAC->uniqueID.changed = TRUE;
//DeadCode CSB 11Sep00 
//DeadCode CSB 11Sep00 		Pos.x = ControlledAC->World.X;
//DeadCode CSB 11Sep00 		Pos.y = ControlledAC->World.Y;
//DeadCode CSB 11Sep00 		Pos.z = ControlledAC->World.Z;
//DeadCode CSB 11Sep00 		FrameCount++;
//DeadCode CSB 11Sep00 
//DeadCode CSB 11Sep00 static FP dist = 0;
//DeadCode CSB 11Sep00 dist += 0.04 * FP(ControlledAC->vel_) * 0.0001;
//DeadCode CSB 11Sep00 if(!(FrameCount & 0x0f))
//DeadCode CSB 11Sep00 {
//DeadCode CSB 11Sep00 	PrintVar(60, 10, " %.0f ", FP(Pos.y * 0.03808));
//DeadCode CSB 11Sep00 	if(ControlledAC->fly.leadflight->waypoint)
//DeadCode CSB 11Sep00 		if(ControlledAC->fly.leadflight->waypoint->target)
//DeadCode CSB 11Sep00 			PrintVar(60, 11, " %.0f ", FP(FP(ControlledAC->fly.leadflight->waypoint->World.Y + ControlledAC->fly.leadflight->waypoint->target->World.Y) * 0.03808));
//DeadCode CSB 11Sep00 		else
//DeadCode CSB 11Sep00 			PrintVar(60, 11, " %.0f ", FP(FP(ControlledAC->fly.leadflight->waypoint->World.Y) * 0.03808));
//DeadCode CSB 11Sep00 
//DeadCode CSB 11Sep00 	PrintVar(70, 10, " %.0f ", FP(dist * 0.001));
//DeadCode CSB 11Sep00 }
//DeadCode CSB 11Sep00 		return;
//DeadCode CSB 11Sep00 	}

#ifdef	_LOCKTOGROUND_
	COORDS3D AcPos;
	AcPos.X = ControlledAC->World.X;
	if(ControlledAC->World.Y > 5000)
		AcPos.Y = ControlledAC->World.Y - 5000;
	else AcPos.Y = 0;
	AcPos.Z = ControlledAC->World.Z;
	GroundHeight = _Collide.GroundAltitude(AcPos);
	Pos.y = GroundHeight + 180;
	UpdateAirStruc(ControlledAC);
#endif	
/*
	if(!(FrameCount & EVERY64cs))
	{
		for(SWord y = 0; y < 25; y++)
			PrintString(40, y, "                                   ");
		y = 0;
		for(AirStrucPtr lead = Persons2::PlayerGhostAC->FindFormpos0(); lead; lead = lead->fly.nextflight)
			for(AirStrucPtr ac = lead; ac; ac = ac->Follower())
			{
				PrintVar(40, y, "%.0f ", FP(y));
				if(ac->movecode != AUTO_COMBAT)
				{
					PrintVar(43, y, "%.0f  ", FP(ac->movecode));
					PrintVar(47, y, "%.1f ", FP(ac->vel_ * 0.0001));
					PrintString(55, y, "-------------------------");
					if((ac->movecode == AUTO_FOLLOWWP) && (ac->FindLeadCandidate()))
						PrintVar(65, y, "%.0f ", FP(ac->Distance3D(&ac->FindLeadCandidate()->World) * 0.01));
				}
				else
				{
					PrintString(43, y, "COM ");
					if((!ac->ai.unfriendly) || (ac->ai.unfriendly->Status.size != AirStrucSize))
						PrintString(47, y, "None ");
					else
					{
						switch(AirStrucPtr(ac->ai.unfriendly)->classtype->visible)
						{
							case SPIT:		PrintString(47, y, "SPIT ");	break;
							case HURR:		PrintString(47, y, "HURR ");	break;
							case ME109:		PrintString(47, y, "M109 ");	break;
							case ME110:		PrintString(47, y, "M110 ");	break;
							case JU87:		PrintString(47, y, "JU87 ");	break;
							case DEF:		PrintString(47, y, "DEFI ");	break;
							case BRISTO:	PrintString(47, y, "BLEN ");	break;
							case JU88:		PrintString(47, y, "JU88 ");	break;
							case HE11:		PrintString(47, y, "H111 ");	break;
							case DO17:		PrintString(47, y, "DO17 ");	break;
							case JU52:		PrintString(47, y, "HE59 ");	break;
						}
					
						PrintVar(52, y, "%.0f ", FP(AirStrucPtr(ac->ai.unfriendly)->formpos));
					}

					switch(ac->ai.manoeuvre)
					{
						case MANOEUVRE_SELECT:				PrintString(55, y, "SELECT ");				break;
						case MANOEUVRE_LOOKROUND:			PrintString(55, y, "LOOKROUND ");			break;
						case MANOEUVRE_WELDEDWINGMAN:		PrintString(55, y, "WELDEDWINGMAN ");		break;
						case MANOEUVRE_BAILOUT:				PrintString(55, y, "BAILOUT ");				break;
						case MANOEUVRE_TOPCOVER:			PrintString(55, y, "TOPCOVER ");			break;
						case MANOEUVRE_FORCETOPCOVER:		PrintString(55, y, "FORCETOPCOVER ");		break;
						case MANOEUVRE_LINEABREAST:			PrintString(55, y, "LINEABREAST ");			break;
						case MANOEUVRE_PINCER:				PrintString(55, y, "PINCER ");				break;
						case MANOEUVRE_MULTIWAVE:			PrintString(55, y, "MULTIWAVE ");			break;
						case MANOEUVRE_DIVEANDZOOM:			PrintString(55, y, "DIVEANDZOOM ");			break;
						case MANOEUVRE_LEADPURSUIT:			PrintString(55, y, "LEADPURSUIT ");			break;
						case MANOEUVRE_LAGPURSUIT:			PrintString(55, y, "LAGPURSUIT ");			break;
						case MANOEUVRE_SPLITMANOEUVRE:		PrintString(55, y, "SPLITMANOEUVRE ");		break;
						case MANOEUVRE_HEADON:				PrintString(55, y, "HEADON ");				break;
						case MANOEUVRE_LINEASTERN:			PrintString(55, y, "LINEASTERN ");			break;
						case MANOEUVRE_VICATTACK:			PrintString(55, y, "VICATTACK ");			break;
						case MANOEUVRE_BARRELROLLATTACK:	PrintString(55, y, "BARRELROLLATTACK ");	break;
						case MANOEUVRE_SCISSORS:			PrintString(55, y, "SCISSORS ");			break;
						case MANOEUVRE_MILDSCISSORS:		PrintString(55, y, "MILDSCISSORS ");		break;
						case MANOEUVRE_TURNINGFIGHT:		PrintString(55, y, "TURNINGFIGHT ");		break;
						case MANOEUVRE_SPLITS:				PrintString(55, y, "SPLITS ");				break;
						case MANOEUVRE_ZOOMANDDROP:			PrintString(55, y, "ZOOMANDDROP ");			break;
						case MANOEUVRE_STRAIGHTANDLEVEL:	PrintString(55, y, "STRAIGHTANDLEVEL ");	break;
						case MANOEUVRE_SPINOUT:				PrintString(55, y, "SPINOUT ");				break;
						case MANOEUVRE_DIVEFORHOME:			PrintString(55, y, "DIVEFORHOME ");			break;
						case MANOEUVRE_GOHOME:				PrintString(55, y, "GOHOME ");				break;
						case MANOEUVRE_MAKEFORFRIENDLY:		PrintString(55, y, "MAKEFORFRIENDLY ");		break;
						case MANOEUVRE_MOVEAWAY:			PrintString(55, y, "MOVEAWAY ");			break;
						case MANOEUVRE_ACCIDENTALSPINOUT:	PrintString(55, y, "ACCIDENTALSPINOUT ");	break;
						case MANOEUVRE_VERTICALLOOP:		PrintString(55, y, "VERTICALLOOP ");		break;
						case MANOEUVRE_IMMELMANNTURN:		PrintString(55, y, "IMMELMANNTURN ");		break;
						case MANOEUVRE_IMMELMANN:			PrintString(55, y, "IMMELMANN ");			break;
						case MANOEUVRE_STAYWITHPREY:		PrintString(55, y, "STAYWITHPREY ");		break;
						case MANOEUVRE_CLIMBFORHOME:		PrintString(55, y, "CLIMBFORHOME ");		break;
						case MANOEUVRE_STRAIGHTDIVE:		PrintString(55, y, "STRAIGHTDIVE ");		break;
						case MANOEUVRE_STANDONTAIL:			PrintString(55, y, "STANDONTAIL ");			break;
						case MANOEUVRE_SHOOTTOFRIGHTEN:		PrintString(55, y, "SHOOTTOFRIGHTEN ");		break;
						case MANOEUVRE_SHOOTTOOEARLY:		PrintString(55, y, "SHOOTTOOEARLY ");		break;
						case MANOEUVRE_GAINHEIGHT:			PrintString(55, y, "GAINHEIGHT ");			break;
						case MANOEUVRE_LAGROLL:				PrintString(55, y, "LAGROLL ");				break;
						case MANOEUVRE_EXTENSION:			PrintString(55, y, "EXTENSION ");			break;
						case MANOEUVRE_DIVINGSPIN:			PrintString(55, y, "DIVINGSPIN ");			break;
						case MANOEUVRE_REVERSETURN:			PrintString(55, y, "REVERSETURN ");			break;
						case MANOEUVRE_SELFASBAIT:			PrintString(55, y, "SELFASBAIT ");			break;
						case MANOEUVRE_JINK:				PrintString(55, y, "JINK ");				break;
						case MANOEUVRE_BREAKTURN:			PrintString(55, y, "BREAKTURN ");			break;
						case MANOEUVRE_LAZYTURN:			PrintString(55, y, "LAZYTURN ");			break;
						case MANOEUVRE_BREAKLOW:			PrintString(55, y, "BREAKLOW ");			break;
						case MANOEUVRE_BREAKHIGH:			PrintString(55, y, "BREAKHIGH ");			break;
						case MANOEUVRE_BREAK90:				PrintString(55, y, "BREAK90 ");				break;
						case MANOEUVRE_HIGBARRELROLL:		PrintString(55, y, "HIGBARRELROLL ");		break;
						case MANOEUVRE_PANICTURN:			PrintString(55, y, "PANICTURN ");			break;
						case MANOEUVRE_UNBALANCEDFLIGHT:	PrintString(55, y, "UNBALANCEDFLIGHT ");	break;
						case MANOEUVRE_LOWALT:				PrintString(55, y, "LOWALT ");				break;
						case MANOEUVRE_TURNTOHDGANDPITCH:	PrintString(55, y, "TURNTOHDGANDPITCH ");	break;
						case MANOEUVRE_HIGHYOYO:			PrintString(55, y, "HIGHYOYO ");			break;
						case MANOEUVRE_ZOOM:				PrintString(55, y, "ZOOM ");				break;
						case MANOEUVRE_LOWYOYO:				PrintString(55, y, "LOWYOYO ");				break;
						case MANOEUVRE_INTERCEPTHIGH:		PrintString(55, y, "INTERCEPTHIGH ");		break;
						case MANOEUVRE_GAINSPEED:			PrintString(55, y, "GAINSPEED ");			break;
						case MANOEUVRE_HEADONATTACK:		PrintString(55, y, "HEADONATTACK ");		break;
						case MANOEUVRE_LUFBERRY:			PrintString(55, y, "LUFBERRY ");			break;
						case MANOEUVRE_STEEPDIVE:			PrintString(55, y, "STEEPDIVE ");			break;
						case MANOEUVRE_UPANDUNDER:			PrintString(55, y, "UPANDUNDER ");			break;
						case MANOEUVRE_STALLTURN:			PrintString(55, y, "STALLTURN ");			break;
						case MANOEUVRE_SLASHINGATTACK:		PrintString(55, y, "SLASHINGATTACK ");		break;
						case MANOEUVRE_CLIMBTURN:			PrintString(55, y, "CLIMBTURN ");			break;
						case MANOEUVRE_ROLL360:				PrintString(55, y, "ROLL360 ");				break;
						case MANOEUVRE_STRAFFE:				PrintString(55, y, "STRAFFE ");				break;
						case MANOEUVRE_FLYTHROUGHCLOUD:		PrintString(55, y, "FLYTHROUGHCLOUD ");		break;
						case MANOEUVRE_SPINRECOVERY:		PrintString(55, y, "SPINRECOVERY ");		break;
						case MANOEUVRE_COLLISIONAVOIDANCE:	PrintString(55, y, "COLLISIONAVOIDANCE ");	break;
						case MANOEUVRE_COLLIDE:				PrintString(55, y, "COLLIDE ");				break;
					}
				}

				if((ac->ai.attacker) && (ac->ai.attacker->Status.size == AIRSTRUCSIZE))
				{
					switch(AirStrucPtr(ac->ai.attacker)->fly.pModel->Type)
					{
						case AT_SPITFIRE:	PrintString(70, y, "SPIT ");	break;
						case AT_HURRICANE:	PrintString(70, y, "HURR ");	break;
						case AT_BF109:		PrintString(70, y, "M109 ");	break;
						case AT_BF110:		PrintString(70, y, "M110 ");	break;
						case AT_JU87B:		PrintString(70, y, "JU87 ");	break;
						case AT_DEFIANT:	PrintString(70, y, "DEFI ");	break;
						case AT_BLENHIEM:	PrintString(70, y, "BLEN ");	break;
						case AT_JU88:		PrintString(70, y, "JU88 ");	break;
						case AT_HE111:		PrintString(70, y, "H111 ");	break;
						case AT_DO17:		PrintString(70, y, "DO17 ");	break;
						case AT_HE59:		PrintString(70, y, "HE59 ");	break;
					}

					PrintVar(75, y, "%.0f ", FP(AirStrucPtr(ac->ai.attacker)->formpos));
				}

				if(ac->information == IF_IN_POS)
					PrintString(78, y, "I");
				if(ac->information == IF_NEAR_POS)
					PrintString(78, y, "N");
				if(ac->information == IF_OUT_POS)
					PrintString(78, y, "O");

				if(ac == Persons2::PlayerGhostAC)
					PrintString(40, y, "*ME*");
				y++;
			}
	}
*/
//DEADCODE CSB 01/03/00 if(Key_Tests.KeyPress3d(RPM_10))
//DEADCODE CSB 01/03/00 	FP Breakpoint = 0;
//DEADCODE CSB 01/03/00 
//DEADCODE CSB 25/02/00 PrintVar(40, 10, "pitch %.0f ", FP(SWord(ControlledAC->pitch)));
//DEADCODE CSB 25/02/00 PrintVar(40, 11, "shunt %.0f ", FP(ControlledAC->World.Y - GroundHeight));
//DEADCODE CSB 25/02/00 
//DEADCODE CSB 25/02/00 {
//DEADCODE CSB 25/02/00 for(PGEAR pGear = GearList; pGear; pGear = pGear->List.NextItem())
//DEADCODE CSB 25/02/00 {
//DEADCODE CSB 25/02/00 	if(pGear->Ident == PORT)	PrintVar(40, 13, "%.2f ", FP(pGear->LegPos));
//DEADCODE CSB 25/02/00 	if(pGear->Ident == STBD)	PrintVar(45, 13, "%.2f ", FP(pGear->LegPos));
//DEADCODE CSB 25/02/00 	if(pGear->Ident == NOSE)	PrintVar(42, 12, "%.2f ", FP(pGear->LegPos));
//DEADCODE CSB 25/02/00 	if(pGear->Ident == TAIL)	PrintVar(42, 14, "%.2f ", FP(pGear->LegPos));
//DEADCODE CSB 25/02/00 }
//DEADCODE CSB 25/02/00 }
//DEADCODE CSB 01/03/00 if(Key_Tests.KeyPress3d(RPM_20))
//DEADCODE CSB 01/03/00 {
//DEADCODE CSB 01/03/00 	Pos.y = 500;
//DEADCODE CSB 01/03/00 	Vel.x = 0;
//DEADCODE CSB 01/03/00 	Vel.y = 0;
//DEADCODE CSB 01/03/00 	Vel.z = 50;
//DEADCODE CSB 01/03/00 	Ori.x.x = 1;
//DEADCODE CSB 01/03/00 	Ori.x.y = 0;
//DEADCODE CSB 01/03/00 	Ori.x.z = 0;
//DEADCODE CSB 01/03/00 	Ori.y.x = 0;
//DEADCODE CSB 01/03/00 	Ori.y.y = 1;
//DEADCODE CSB 01/03/00 	Ori.y.z = 0;
//DEADCODE CSB 01/03/00 	Ori.z.x = 0;
//DEADCODE CSB 01/03/00 	Ori.z.y = 0;
//DEADCODE CSB 01/03/00 	Ori.z.z = 1;
//DEADCODE CSB 01/03/00 }
//DEADCODE CSB 01/03/00 {
//DEADCODE CSB 01/03/00 	AircraftAnimData* adptr = (AircraftAnimData*)ControlledAC->Anim;
//DEADCODE CSB 01/03/00 	PrintVar(40,  5, "LEFT_LEG  %.0f ", FP(adptr->acleglowerl));
//DEADCODE CSB 01/03/00 	PrintVar(40,  6, "RIGHT_LEG %.0f ", FP(adptr->acleglowerr));
//DEADCODE CSB 01/03/00 	PrintVar(40,  7, "LEFT_SUS  %.0f ", FP(adptr->aclegsuspl));
//DEADCODE CSB 01/03/00 	PrintVar(40,  8, "RIGHT_SUS %.0f ", FP(adptr->aclegsuspr));
//DEADCODE CSB 01/03/00 	PrintVar(40,  9, "FLAPS     %.0f ", FP(adptr->acflaps));
//DEADCODE CSB 01/03/00 	PrintVar(40, 10, "CANOPY    %.0f ", FP(adptr->accanopy));
//DEADCODE CSB 01/03/00 	PrintVar(40, 11, "ELEVATOR  %.0f ", FP(adptr->acelevator));
//DEADCODE CSB 01/03/00 	PrintVar(40, 12, "AILERON   %.0f ", FP(adptr->acaileronl));
//DEADCODE CSB 01/03/00 	PrintVar(40, 13, "RUDDER    %.0f ", FP(adptr->acrudder));
//DEADCODE CSB 01/03/00 	PrintVar(40, 14, "RPM       %.0f ", FP(adptr->acrpm));
//DEADCODE CSB 01/03/00 }
//DEADCODE CSB 14/02/00 PrintVar(60, 13, "VEL  %.1f ", FP(-AirVel.z));
//DEADCODE CSB 14/02/00 PrintVar(60, 15, "MAcc %.3f ", FP(Acc.z * 100.0));
//DEADCODE CSB 14/02/00 PrintVar(60, 17, "AAcc %.3f ", FP(ControlledAC->CalcAccel(10000000) * 0.001));
//DEADCODE CSB 14/02/00 PrintVar(60, 18, "ADec %.3f ", FP(ControlledAC->CalcAccel(0) * 0.001));
//DEADCODE CSB 14/02/00 PrintVar(60, 20, "MaxA %.0f ", FP(FP(ControlledAC->classtype->maxaccel) * FP(Acc.z) / FP(ControlledAC->CalcAccel(10000000)) * 100000.0));

//**********************************************
//********  TEST CODE	//CSB 07/05/99	********
//**********************************************

#ifdef	_NOFLIGHTMODEL_
ControlledAC->vel_x = 0;
ControlledAC->vel_y = 0;
ControlledAC->vel_z = 0;
ControlledAC->vel_ = 0;
Blood=1;
return;
#endif

	if((FirstCycle) || !(FrameCount & EVERY256cs))	//This will do the following commands for each aircraft
	{								//once every n operations.
		MissManCampSky().Ambient (Pos.y, AmbDensity, AmbTemp, AmbPres);
		FP FuelUsageRate = CalcFuelRate(ControlledAC);
		SetFuelTank(ControlledAC, true);
		ControlledAC->FuelLeft(FuelUsageRate);

		UpdateMassInertias(ControlledAC);
		Persons2::PlayerGhostAC->weap.right=ControlledAC->weap.right;
		Persons2::PlayerGhostAC->weap.left=ControlledAC->weap.left;
		Persons2::PlayerGhostAC->weap.centre=ControlledAC->weap.centre;
		for(SWord i = 0; i < 4; i++)
			Persons2::PlayerGhostAC->fly.fuel_content[i] = ControlledAC->fly.fuel_content[i];
		//Calculates the rate of fuel burn and subtacts it from the fuel and total mass

	}
	FrameCount++;

#ifdef CALIBRATION_CODE
	CalibrationInputs ();
#endif

	GearTouched = FALSE;
	GearSkid = FALSE;

	if((FirstCycle) && (ControlledAC->vel_ > 100000))
	{
		TrimAircraft(ControlledAC);
		SetFuelTank(ControlledAC, false);
	}


	CalcAirVel (ControlledAC);

	TotalBuffet = 0.0;

	if(!(FrameCount & EVERY8cs) || (FirstCycle) )
		ProcessEngines (ControlledAC);
	ProcessDevices ();
	ProcessMainElements (ControlledAC);

	FCRD force;
	FCRD moment;

	NullVec (force);
	NullVec (moment);
	CalcNettForceMoment (force, moment);

	if( (Save_Data.flightdifficulty [FD_EXCESSIVEACCELDAMAGE]) && (!(FrameCount & EVERY8cs)) )
		WingDamage(ControlledAC, force.y);
		
	force.z += ControlledAC->weap.weapforce;

	ProcessGears(ControlledAC, force.x, force.y, force.z, moment.y);

	PTHRUSTPOINT pThrust = ThrustList;
	while (pThrust != NULL)
	{
		if((Save_Data.flightdifficulty [FD_POWERBOOST]) && (!GearTouched))
		{
			pThrust->Force.x *= PowerBoost;
			pThrust->Force.y *= PowerBoost;
			pThrust->Force.z *= PowerBoost;
		}
		FCRD dmoment;
		AddVec (force, force, pThrust->Force);
		AddVec (moment, moment, pThrust->Moment);
		CPrd (dmoment, pThrust->Force, pThrust->Pos);
		AddVec (moment, moment, dmoment);
		pThrust = pThrust->List.NextItem ();
	}

	// Gear
	PGEAR pGear = GearList;
	while( (pGear != NULL) && (GearTouched) )
	{
		if(pGear->Touched)
		{
			FCRD dmoment;
			AddVec(force, force, pGear->TyreForce);
			CPrd (dmoment, pGear->TyreForce, pGear->WheelPos);
			AddVec (moment, moment, dmoment);
		}
		pGear = pGear->List.NextItem ();
	}

	CopyVec (force, NettForce);
	CopyVec (moment, NettMoment);

	CalcAcc ();
	CalcRotAcc ();
	MovePilotEye();
  

#ifdef LOCK_X_Z_POS
	FP posx = Pos.x;
	FP posy = Pos.y;
	FP posz = Pos.z;
	TransInt (ALL);
	Pos.x = posx;
	Pos.y = posy;
	Pos.z = posz;
	RotInt (ALL);
#else
	RotInt (ALL);	
	TransInt (ALL, 1);	
#endif

	CheckGearPos(ControlledAC);
	SetPlayerMoving(ControlledAC);

	Instruments (ControlledAC);
//DEADCODE CSB 24/03/00		Animations (ControlledAC);
	Ground (ControlledAC);

	AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;

	PENGINE pEngine = EngineList;
	if(pEngine)
	{
		static EngineInfo	left_engine;								//RJS 13Jan00
		static EngineInfo	right_engine;
		float	cockdam = adptr->CANOPY*adptr->CANOPY;				//RJS 22Feb00
		float	cockopen = adptr->accanopy*adptr->accanopy;
		SLong	cocknobble;

		fastMath.FloatToInt(&cocknobble,fastMath.FastSqrt(cockdam+cockopen));
		if (cocknobble > 255)	cocknobble=255;

		left_engine.rpm_engine = Inst.I_EngineRpm0;
		FP power = 238.0 * pEngine->Power / pEngine->p0;
		MODMAXMIN(power, 0, 255);
		left_engine.power = power;									//RJS 14Jan100
		left_engine.rpm_starter = 0;
		if((pEngine->Starting) && (power == 0))
		{
			if(pEngine->Starter == ES_ELECTRIC)
				left_engine.rpm_starter = left_engine.rpm_engine;
			else if(pEngine->Starter == ES_INERTIA)
				left_engine.rpm_starter = pEngine->StarterSpeed;
		}
		left_engine.rattle = adptr->ENGINELEFT;			
		left_engine.cockpitnobble = cocknobble;
		left_engine.velocity = ControlledAC->vel_;				//RJS 9Jun00
		left_engine.xoffset = pEngine->pThrustPoint->Pos.x;

		pEngine = pEngine->List.NextItem();
		if(pEngine)
		{
			right_engine.rpm_engine = Inst.I_EngineRpm0;
			FP power = 238.0 * pEngine->Power / pEngine->p0;
			MODMAXMIN(power, 0, 255);
			right_engine.power = power;									//RJS 14Jan100
			right_engine.rpm_starter = 0;
			if((pEngine->Starting) && (power == 0))
			{
				if(pEngine->Starter == ES_ELECTRIC)
					right_engine.rpm_starter = right_engine.rpm_engine;
				else if(pEngine->Starter == ES_INERTIA)
					right_engine.rpm_starter = pEngine->StarterSpeed;
			}
			right_engine.rattle = adptr->ENGINERIGHT;			
			right_engine.cockpitnobble = cocknobble;
			right_engine.velocity = ControlledAC->vel_;			//RJS 9Jun00
			right_engine.xoffset = pEngine->pThrustPoint->Pos.x;
		}
		else
			right_engine = left_engine;

		_Miles.PlayEngine(ControlledAC,left_engine,right_engine);		//RJS 13Jan00

//JET_Code CSB 22/09/99			if (EngineList->Type == ET_JET)
//JET_Code CSB 22/09/99			{
//JET_Code CSB 22/09/99				ThrustVol = (170 * EngineList->Thrust) / EngineList->T100;			//RJS 14Jan99
//JET_Code CSB 22/09/99				
//JET_Code CSB 22/09/99				if(Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL])
//JET_Code CSB 22/09/99					if(Inst.ExhaustTemp > 225)	//Throttle advanced too quickly
//JET_Code CSB 22/09/99						if(FrameCount & 0x0002)
//JET_Code CSB 22/09/99							ThrustVol = (ThrustVol * (255 - Inst.ExhaustTemp)) / (255 - 225);
//JET_Code CSB 22/09/99			}
//DeadCode RJS 13Jan00		_Miles.PlayEngine(adptr->CANOPY,ControlledAC,Inst.I_EngineRpm0,ControlledAC->vel_, ThrustVol);//RJS 06Oct98
	}

	_Miles.PlayWindyMiller(ControlledAC);										//RJS 21May99
	
//	Force Feedback Stuff		//CSB		21/8/98
	if (_Analogue.FFdevice)
		CalcStickForceFeedback();	//fix this !!!!

	if(FirstCycle)
		NullVec(AveRotVel);

	const fSmooth = 75;
	AveRotVel.x = ((fSmooth - 1) * AveRotVel.x + RotVel.x) / fSmooth;//AMM 25Jun99
	AveRotVel.y = ((fSmooth - 1) * AveRotVel.y + RotVel.y) / fSmooth;//AMM 25Jun99
	AveRotVel.z = ((fSmooth - 1) * AveRotVel.z + RotVel.z) / fSmooth;//AMM 25Jun99

	if(ControlledAC->movecode == AUTO_TRAININGTAKEOFF) 
		TrainingTakeoff(ControlledAC);
	else if(ControlledAC->movecode == AUTO_TRAININGLANDING)
		TrainingLanding(ControlledAC);
		
	static SByte landed2;
	if(FirstCycle)
		landed2 = -1;
	if((landed2 != 1) && (Pos.y > ControlledAC->ai.homebase->World.Y + FT_500))
		landed2 = 0;

	FirstCycle = FALSE;
	UpdateAirStruc (ControlledAC);

	CommsChecks(ControlledAC);

	if((landed2 == 0) && (Speed < 10) && (GearTouched))
	{
		if(ControlledAC->Distance3DSquared(&ControlledAC->ai.homebase->World) < FP(100000) * FP(100000))
			Squad_Diary.UpdatePlayerLog(EFS_LandedOK);
		else if(OnAnAirfield(ControlledAC))
			Squad_Diary.UpdatePlayerLog(EFS_LandedOtherAF);
		else
			Squad_Diary.UpdatePlayerLog(EFS_LandedField);

		landed2 = 1;
		Art_Int.exittimer = 1000;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ACMBase
//Author		Andrew McRae
//Date			Thu 8 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ACMBase (AirStrucPtr const ControlledAC)
{
//**********************************************
//********  TEST CODE	//CSB 07/05/99	********
//**********************************************

/*
	if (Key_Tests.KeyPress3d (SENS_UP))
	{
		AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
		SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->LEFTWINGIN, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->RIGHTWINGIN, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->LEFTWINGOUT, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->RIGHTWINGOUT, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->TAIL, BS_DEAD);
//DeadCode CSB 07/05/99			SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->PILOTLEFT, BS_DEAD);
	}
*/

//DeadCode CSB 01/06/99		PrintVar(20, 2, "Range  %.0f ", (FP)(ControlledAC->Range / 100.0));
//DeadCode CSB 01/06/99		PrintVar(20, 3, "Vel    %.1f ", (FP)(ControlledAC->vel / 10.0));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99		PrintVar(20, 5, "Accel  %.4f ", (FP)(ControlledAC->CalcAccel(32000) / 2560.0));
//DeadCode CSB 01/06/99		PrintVar(20, 6, "Deccel %.4f ", (FP)(ControlledAC->CalcAccel(0)     / 2560.0));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99		PrintVar(20, 8, "Acc.z  %.4f ", (FP)(Acc.z * 100.0));
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99	
//DeadCode CSB 01/06/99		
//DeadCode CSB 01/06/99		PrintVar(20, 10, "Thrust %.0f ", (FP)ControlledAC->fly.thrustpercent);

//DEADCODE DAW 25/11/99 	if(Key_Tests.KeyHeld3d(RPM_30))
//DEADCODE DAW 25/11/99 		MainPlaneList->Cdo -= 0.00001;
//DEADCODE DAW 25/11/99 	if(Key_Tests.KeyHeld3d(RPM_40))
//DEADCODE DAW 25/11/99 		MainPlaneList->Cdo += 0.00001;
//DEADCODE DAW 25/11/99 
//DEADCODE DAW 25/11/99 	PrintVar(40, 15, "Alt %.0f ", FP(Pos.y * 0.032808));
//DEADCODE DAW 25/11/99 	PrintVar(40, 16, "Vel %.1f ", FP(Speed * 2.236936));
//DEADCODE DAW 25/11/99 	PrintVar(40, 17, "CD0 %.6f ", FP(MainPlaneList->Cdo));
	
//**********************************************
//********  TEST CODE	//CSB 07/05/99	********
//**********************************************

	FP dist2 =	  (Pos.x - FP(ControlledAC->World.X)) * (Pos.x - FP(ControlledAC->World.X))
				+ (Pos.y - FP(ControlledAC->World.Y)) * (Pos.y - FP(ControlledAC->World.Y))
				+ (Pos.z - FP(ControlledAC->World.Z)) * (Pos.z - FP(ControlledAC->World.Z));
	if(dist2 > 250.0 * 250.0)
	{
		INT3;
		UpdateModel(ControlledAC);
	}

	if((FirstCycle) || !(FrameCount & EVERY256cs))		//This will do the following commands for each aircraft
	{								//once every n operations.
		MissManCampSky().Ambient (Pos.y, AmbDensity, AmbTemp, AmbPres);
		FP FuelUsageRate = CalcFuelRate(ControlledAC);
		SetFuelTank(ControlledAC, false);
		ControlledAC->FuelLeft(FuelUsageRate);
	}
	FrameCount++;
//DEADCODE AMM 24/11/99 	MODEL_DT = 4;

	if(FirstCycle) TrimAircraft(ControlledAC);

	CalcAirVel (ControlledAC);

	if (!Controlled) ACMModel.Pilot (ControlledAC);


	{
		GearTouched = FALSE;
		GearSkid = FALSE;

		if(!(FrameCount & EVERY8cs) || (FirstCycle) )
			ProcessEngines (ControlledAC);
//DEADCODE AMM 24/11/99 		{
//DEADCODE AMM 24/11/99 #pragma warnmsg("MODEL_DT is now const - what should happen here?")
//DEADCODE AMM 24/11/99 //DeadCode AMM 24Nov99 			MODEL_DT *= 4;
//DEADCODE AMM 24/11/99 //DeadCode AMM 24Nov99 			MODEL_DT /= 4;
//DEADCODE AMM 24/11/99 		}

		ProcessDevices ();

		TotalBuffet = 0;

//DEADCODE CSB 18/01/00 		SWord temprudder = Rudder;
//DEADCODE CSB 18/01/00 		if((Rudder < 1638) && (Rudder > -1638))
//DEADCODE CSB 18/01/00 			Rudder -= RotVel.y / AirVel.z * 200000000;
//DEADCODE CSB 18/01/00 		MODLIMIT(Rudder, 32767);
		ProcessMainElements (ControlledAC);
//DEADCODE CSB 18/01/00 		Rudder = temprudder;

		FCRD force;
		FCRD moment;

		NullVec (force);
		NullVec (moment);

		CalcNettForceMoment (force, moment);

//DeadCode AMM 3Jul00 		if (_Replay.replayframecount==9)
//DeadCode AMM 3Jul00 		{
//DeadCode AMM 3Jul00 			FILE*fp=fopen("plop.txt","at");
//DeadCode AMM 3Jul00 			fprintf(fp,"forcex=%f forcey=%f forcez=%f\n",
//DeadCode AMM 3Jul00 				force.x,
//DeadCode AMM 3Jul00 				force.y,
//DeadCode AMM 3Jul00 				force.x);
//DeadCode AMM 3Jul00 			fprintf(fp,"momx=%f momy=%f momz=%f\n",
//DeadCode AMM 3Jul00 				moment.x,
//DeadCode AMM 3Jul00 				moment.y,
//DeadCode AMM 3Jul00 				moment.x);
//DeadCode AMM 3Jul00 			fclose(fp);
//DeadCode AMM 3Jul00 		}

		force.z += ControlledAC->weap.weapforce;
		
		// ThrustPoints
		PTHRUSTPOINT pThrust = ThrustList;
		while (pThrust != NULL)
		{
			FCRD dmoment;
			AddVec (force, force, pThrust->Force);
			AddVec (moment, moment, pThrust->Moment);
			CPrd (dmoment, pThrust->Force, pThrust->Pos);
			AddVec (moment, moment, dmoment);
			pThrust = pThrust->List.NextItem ();
		}


		CopyVec (force, NettForce);
		CopyVec (moment, NettMoment);

		CalcAcc ();
	   
		CalcRotAcc ();

		
		if( (CheatAcc.x != 32767) || (CheatAcc.y != 32767) || (CheatAcc.z != 32767) )
		{
			FCRD OldAcc;
			OldAcc.x = NettForce.x / Mass;
			OldAcc.y = NettForce.y / Mass;
			OldAcc.z = NettForce.z / Mass;
			ModifyAcc(OldAcc, CheatAcc);
		}

#ifdef LOCK_X_Z_POS
		FP posx = Pos.x;
		FP posz = Pos.z;
		TransInt (ALL);
		Pos.x = posx;
		Pos.z = posz;
		RotInt (ALL);
#else
		RotInt (ALL);
		TransInt (ALL, 1.0);
#endif

	}

	CheatAcc.x = 32767;
	CheatAcc.y = 32767;
	CheatAcc.z = 32767;

	UpdateAirStruc (ControlledAC);


	ACMInstruments (ControlledAC);

//DEADCODE CSB 24/03/00		Animations (ControlledAC);
	Ground (ControlledAC);

	FirstCycle = FALSE;

//#define ACM_PILOT_DATA
//Testing ACM Manoeuvres !!!!!!!!!!!!!!!
#ifdef ACM_PILOT_DATA
	PrintVar( 0,  2, "Alt  %.0f ", (FP)Pos.y / 100);
	PrintVar( 0,  3, "Vel  %.1f ", AirSpeed   );
	PrintVar( 0,  4, "Mach %.2f ", Inst.I_MachNo);

	PrintVar(15,  2, "Pitch %.1f ", FP(AngleSign(Inst.I_PitchAngle) * 57.3));
	PrintVar(15,  3, "Roll  %.1f ", FP(AngleSign(Inst.I_RollAngle ) * 57.3));
	PrintVar(15,  4, "Headg %.1f ", Inst.I_Heading);

	PrintVar(30,  2, "AirVel.x %.1f ", -AirVel.x);
	PrintVar(30,  3, "AirVel.y %.1f ", -AirVel.y);
	PrintVar(30,  4, "AirVel.z %.1f ", -AirVel.z);

	PrintVar(45,  2, "Elevator %.0f ", (FP)(Elevator / 327.67));
	PrintVar(45,  3, "Aileron  %.0f ", (FP)(Aileron  / 327.67));
	PrintVar(45,  4, "Rudder   %.0f ", (FP)(Rudder   / 327.67));
	PrintVar(45,  5, "Throttle %.0f ", (FP)(ControlledAC->fly.thrustpercent));

	PMAINPLANE pMainPlane = MainPlaneList;
	PrintVar( 0,  8, "Aoa  %.1f ", (FP)(57.3 * pMainPlane->aoa[1][1]) );
	PrintVar(15,  8, " %.1f " 	 , (FP)(57.3 * pMainPlane->aoa[1][0]) );
	PrintVar(25,  8, " %.1f "	 , (FP)(57.3 * pMainPlane->aoa[0][0]) );
	PrintVar(35,  8, " %.1f "	 , (FP)(57.3 * pMainPlane->aoa[0][1]) );

	PrintVar(0,  10, "T Pitch %.1f ", (FP)( (ControlledAC->PitchIntercept - ControlledAC->pitch) / 182.04) );
	PrintVar(0,  11, "T Headg %.1f ", (FP)( (ControlledAC->HdgIntercept - ControlledAC->hdg)  / 182.04) );
	PrintVar(0,  12, "T Range %.0f ", (FP)(ControlledAC->Range / 100) );

	PrintVar(20,  10, "C Pitch %.0f ", (FP)( (ControlledAC->PitchIntercept) / 182.04) );
	PrintVar(20,  11, "C Roll  %.0f ", (FP)( (ACMModel.CtrlRoll           ) / 182.04) );
	PrintVar(20,  12, "C Headg %.0f ", (FP)( (ControlledAC->HdgIntercept  ) / 182.04) );


	switch (Type)
	{
		case AT_SPITFIRE:	{ PrintString(0, 23, "AT_SPIT		");    break; }
		case AT_HURRICANE:	{ PrintString(0, 23, "AT_HURR		");    break; }
		case AT_BF109:		{ PrintString(0, 23, "AT_BF109		");    break; }
		case AT_BF110:		{ PrintString(0, 23, "AT_BF110		");    break; }
	}
	
	switch (ControlledAC->ai.manoeuvre)
	{
		case MANOEUVRE_SELECT:						{ PrintString(0,  24, "MANOEUVRE_SELECT						");    break; }
		case MANOEUVRE_LOOKROUND:					{ PrintString(0,  24, "MANOEUVRE_LOOKROUND					");    break; }
		case MANOEUVRE_WELDEDWINGMAN:				{ PrintString(0,  24, "MANOEUVRE_WELDEDWINGMAN				");    break; }
		case MANOEUVRE_BAILOUT:						{ PrintString(0,  24, "MANOEUVRE_BAILOUT					");    break; }
		case MANOEUVRE_TOPCOVER:					{ PrintString(0,  24, "MANOEUVRE_TOPCOVER					");    break; }
		case MANOEUVRE_LINEABREAST:					{ PrintString(0,  24, "MANOEUVRE_LINEABREAST				");    break; }
		case MANOEUVRE_PINCER:						{ PrintString(0,  24, "MANOEUVRE_PINCER						");    break; }
		case MANOEUVRE_MULTIWAVE:					{ PrintString(0,  24, "MANOEUVRE_MULTIWAVE					");    break; }
		case MANOEUVRE_DIVEANDZOOM:					{ PrintString(0,  24, "MANOEUVRE_DIVEANDZOOM				");    break; }
		case MANOEUVRE_LEADPURSUIT:					{ PrintString(0,  24, "MANOEUVRE_LEADPURSUIT				");    break; }
		case MANOEUVRE_LAGPURSUIT:					{ PrintString(0,  24, "MANOEUVRE_LAGPURSUIT					");    break; }
		case MANOEUVRE_SPLITMANOEUVRE:				{ PrintString(0,  24, "MANOEUVRE_SPLITMANOEUVRE				");    break; }
		case MANOEUVRE_HEADON:						{ PrintString(0,  24, "MANOEUVRE_HEADON						");    break; }
		case MANOEUVRE_LINEASTERN:					{ PrintString(0,  24, "MANOEUVRE_LINEASTERN					");    break; }
		case MANOEUVRE_BARRELROLLATTACK:			{ PrintString(0,  24, "MANOEUVRE_BARRELROLLATTACK			");    break; }
		case MANOEUVRE_SCISSORS:					{ PrintString(0,  24, "MANOEUVRE_SCISSORS					");    break; }
		case MANOEUVRE_MILDSCISSORS:				{ PrintString(0,  24, "MANOEUVRE_MILDSCISSORS				");    break; }
		case MANOEUVRE_TURNINGFIGHT:				{ PrintString(0,  24, "MANOEUVRE_TURNINGFIGHT				");    break; }
		case MANOEUVRE_SPLITS:						{ PrintString(0,  24, "MANOEUVRE_SPLITS						");    break; }
		case MANOEUVRE_ZOOMANDDROP:					{ PrintString(0,  24, "MANOEUVRE_ZOOMANDDROP				");    break; }
		case MANOEUVRE_STRAIGHTANDLEVEL:			{ PrintString(0,  24, "MANOEUVRE_STRAIGHTANDLEVEL			");    break; }
		case MANOEUVRE_SPINOUT:						{ PrintString(0,  24, "MANOEUVRE_SPINOUT					");    break; }
		case MANOEUVRE_DIVEFORHOME:					{ PrintString(0,  24, "MANOEUVRE_DIVEFORHOME				");    break; }
		case MANOEUVRE_GOHOME:						{ PrintString(0,  24, "MANOEUVRE_GOHOME						");    break; }
		case MANOEUVRE_MAKEFORFRIENDLY:				{ PrintString(0,  24, "MANOEUVRE_MAKEFORFRIENDLY			");    break; }
		case MANOEUVRE_MOVEAWAY:					{ PrintString(0,  24, "MANOEUVRE_MOVEAWAY					");    break; }
		case MANOEUVRE_ACCIDENTALSPINOUT:			{ PrintString(0,  24, "MANOEUVRE_ACCIDENTALSPINOUT			");    break; }
		case MANOEUVRE_VERTICALLOOP:				{ PrintString(0,  24, "MANOEUVRE_VERTICALLOOP				");    break; }
		case MANOEUVRE_IMMELMANNTURN:				{ PrintString(0,  24, "MANOEUVRE_IMMELMANNTURN				");    break; }
		case MANOEUVRE_IMMELMANN:					{ PrintString(0,  24, "MANOEUVRE_IMMELMANN					");    break; }
		case MANOEUVRE_STAYWITHPREY:				{ PrintString(0,  24, "MANOEUVRE_STAYWITHPREY				");    break; }
		case MANOEUVRE_CLIMBFORHOME:				{ PrintString(0,  24, "MANOEUVRE_CLIMBFORHOME				");    break; }
		case MANOEUVRE_STRAIGHTDIVE:				{ PrintString(0,  24, "MANOEUVRE_STRAIGHTDIVE				");    break; }
		case MANOEUVRE_STANDONTAIL:					{ PrintString(0,  24, "MANOEUVRE_STANDONTAIL				");    break; }
		case MANOEUVRE_SHOOTTOFRIGHTEN:				{ PrintString(0,  24, "MANOEUVRE_SHOOTTOFRIGHTEN			");    break; }
		case MANOEUVRE_SHOOTTOOEARLY:				{ PrintString(0,  24, "MANOEUVRE_SHOOTTOOEARLY				");    break; }
		case MANOEUVRE_GAINHEIGHT:					{ PrintString(0,  24, "MANOEUVRE_GAINHEIGHT					");    break; }
		case MANOEUVRE_LAGROLL:						{ PrintString(0,  24, "MANOEUVRE_LAGROLL					");    break; }
		case MANOEUVRE_EXTENSION:					{ PrintString(0,  24, "MANOEUVRE_EXTENSION					");    break; }
		case MANOEUVRE_DIVINGSPIN:					{ PrintString(0,  24, "MANOEUVRE_DIVINGSPIN					");    break; }
		case MANOEUVRE_REVERSETURN:					{ PrintString(0,  24, "MANOEUVRE_REVERSETURN				");    break; }
		case MANOEUVRE_SELFASBAIT:					{ PrintString(0,  24, "MANOEUVRE_SELFASBAIT					");    break; }
		case MANOEUVRE_JINK:						{ PrintString(0,  24, "MANOEUVRE_JINK						");    break; }
		case MANOEUVRE_BREAKTURN:					{ PrintString(0,  24, "MANOEUVRE_BREAKTURN					");    break; }
		case MANOEUVRE_LAZYTURN:					{ PrintString(0,  24, "MANOEUVRE_LAZYTURN					");    break; }
		case MANOEUVRE_BREAKLOW:					{ PrintString(0,  24, "MANOEUVRE_BREAKLOW					");    break; }
		case MANOEUVRE_BREAKHIGH:					{ PrintString(0,  24, "MANOEUVRE_BREAKHIGH					");    break; }
		case MANOEUVRE_BREAK90:						{ PrintString(0,  24, "MANOEUVRE_BREAK90					");    break; }
		case MANOEUVRE_HIGBARRELROLL:				{ PrintString(0,  24, "MANOEUVRE_HIGBARRELROLL				");    break; }
		case MANOEUVRE_PANICTURN:					{ PrintString(0,  24, "MANOEUVRE_PANICTURN					");    break; }
		case MANOEUVRE_UNBALANCEDFLIGHT:			{ PrintString(0,  24, "MANOEUVRE_UNBALANCEDFLIGHT			");    break; }
		case MANOEUVRE_LOWALT:						{ PrintString(0,  24, "MANOEUVRE_LOWALT						");    break; }
		case MANOEUVRE_TURNTOHDGANDPITCH:			{ PrintString(0,  24, "MANOEUVRE_TURNTOHDGANDPITCH			");    break; }
		case MANOEUVRE_HIGHYOYO:					{ PrintString(0,  24, "MANOEUVRE_HIGHYOYO					");    break; }
		case MANOEUVRE_ZOOM:						{ PrintString(0,  24, "MANOEUVRE_ZOOM						");    break; }
		case MANOEUVRE_LOWYOYO:						{ PrintString(0,  24, "MANOEUVRE_LOWYOYO					");    break; }
		case MANOEUVRE_INTERCEPTHIGH:				{ PrintString(0,  24, "MANOEUVRE_INTERCEPTHIGH				");    break; }
		case MANOEUVRE_GAINSPEED:					{ PrintString(0,  24, "MANOEUVRE_GAINSPEED					");    break; }
		case MANOEUVRE_SPINRECOVERY:				{ PrintString(0,  24, "MANOEUVRE_SPINRECOVERY				");    break; }
		case MANOEUVRE_HEADONATTACK:				{ PrintString(0,  24, "MANOEUVRE_HEADONATTACK				");    break; }
		case MANOEUVRE_LUFBERRY:					{ PrintString(0,  24, "MANOEUVRE_LUFBERRY					");    break; }
		case MANOEUVRE_STEEPDIVE:					{ PrintString(0,  24, "MANOEUVRE_STEEPDIVE					");    break; }
		case MANOEUVRE_UPANDUNDER:					{ PrintString(0,  24, "MANOEUVRE_UPANDUNDER					");    break; }
		case MANOEUVRE_STALLTURN:					{ PrintString(0,  24, "MANOEUVRE_STALLTURN					");    break; }
		case MANOEUVRE_SLASHINGATTACK:				{ PrintString(0,  24, "MANOEUVRE_SLASHINGATTACK				");    break; }
		case MANOEUVRE_CLIMBTURN:					{ PrintString(0,  24, "MANOEUVRE_CLIMBTURN					");    break; }
		case MANOEUVRE_ROLL360:						{ PrintString(0,  24, "MANOEUVRE_ROLL360					");    break; }
		case MANOEUVRE_STRAFFE:						{ PrintString(0,  24, "MANOEUVRE_STRAFFE					");    break; }
	}

	PrintVar(30, 24, "Phase %.0f ", (FP)ControlledAC->ai.ManStep);
	PrintVar(40, 24, "Time %.0f ", (FP)ControlledAC->manoeuvretime);
	PrintVar(70, 21, "Thr %.0f ", FP(EngineList->ThrottleSetting));
	PrintVar(70, 22, "RPM %.0f ", FP(EngineList->Speed * 954.9));
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcAirVel
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calcs Air velocity in local coords relative to aircraft cg
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcAirVel (AirStrucPtr const ControlledAC)
{
//	Sky.SetGusts (Save_Data.flightdifficulty [FD_WINDGUSTS]);

	FCRD wind;
	NullVec(wind);

	if((Save_Data.flightdifficulty [FD_WINDEFFECTS]) || (Save_Data.flightdifficulty [FD_WINDGUSTS]))
		MissManCampSky().GetWind (ControlledAC, wind, Pos.y);

//DeadCode CSB 03/12/98		if (!_Replay.Record && _Replay.Playback)
//DeadCode CSB 03/12/98		{
//DeadCode CSB 03/12/98			MMC.Sky.GetWind (ControlledAC,wind, Pos.y);									//D 02Apr98
//DeadCode CSB 03/12/98		}
//DeadCode CSB 03/12/98		else
//DeadCode CSB 03/12/98		{
//DeadCode CSB 03/12/98			wind.x=0;
//DeadCode CSB 03/12/98			wind.y=0;
//DeadCode CSB 03/12/98			wind.z=0;
//DeadCode CSB 03/12/98		}

	Speed = VecLen (Vel);

	// Botch to prevent aircraft rotating into					
	// wind when on ground and not moving.						
	FP wind_frac = 1;											
//DeadCode CSB 09/02/99		if (GearTouched && (Speed < 10)) wind_frac = Speed * 0.1;	


	AirVel.x = (wind_frac * wind.x) - Vel.x;
	AirVel.y = (wind_frac * wind.y) - Vel.y;
	AirVel.z = (wind_frac * wind.z) - Vel.z;

	TnsAxs (AirVel, AirVel, Ori);

//@	OldAirSpeed = AirSpeed;
	AirSpeed = VecLen (AirVel);

	// Instrument Version of AirVel - without above botch
//DEADCODE CSB 23/12/99 	InstAirVel.x = wind.x - Vel.x;								
//DEADCODE CSB 23/12/99 	InstAirVel.y = wind.y - Vel.y;								
//DEADCODE CSB 23/12/99 	InstAirVel.z = wind.z - Vel.z;								
//DEADCODE CSB 23/12/99 	TnsAxs (InstAirVel, InstAirVel, Ori);						

	DynamicPressure = 0.5 * AmbDensity * AirSpeed * AirSpeed;

	Inst.I_MachNo = AirSpeed / FSqrt (402.7 * AmbTemp);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrimAircraft
//Author		Craig Beeston
//Date			Thu 26 Nov 1998
//
//Description	When a model is processed for the first time, the pitch is set to achieve 
//				1 g flight
//				Assumes only one Wing
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::TrimAircraft(AirStrucPtr const ControlledAC)
{
	UByte Texture;
	GroundHeight = _Collide.GroundAltitude(ControlledAC->World, &Texture);

	MissManCampSky().Ambient (Pos.y, AmbDensity, AmbTemp, AmbPres);
//DEADCODE CB 18/11/99 	long wx, wy, wz;
//DEADCODE CB 18/11/99 	MMC.Sky.GetWind(Pos.y, wx, wy, wz);
//DEADCODE CB 18/11/99 	Vel.x += wx * 0.0001;
//DEADCODE CB 18/11/99 	Vel.y += wy * 0.0001;
//DEADCODE CB 18/11/99 	Vel.z += wz * 0.0001;

	CalcAirVel(ControlledAC);
	ProcessDevices();
	UWord n = 0;

	FP OldAirVely = AirVel.y;

	for(;;)
	{
		FCRD NettForce, NettMoment;
		NullVec(NettForce);
		NullVec(NettMoment);

		ProcessMainElements(ControlledAC);
		CalcNettForceMoment(NettForce, NettMoment);

		FP NormG  = NettForce.y / (Mass * GRAVITY);
		
		FP GError = NormG - 1.0;
		if( (GError > -0.001) && (GError < 0.001) ) break;
		AirVel.y += AirVel.z * GError * 0.02;
		n += 1;
		if(n > 100) return;
	}


	FCRD DeltaVel;
	DeltaVel.x = 0;
	DeltaVel.y = OldAirVely - AirVel.y ;
	DeltaVel.z = 0;

	TnsPnt(DeltaVel, DeltaVel, Ori);

	AddVec(Vel, Vel, DeltaVel);
	CalcAirVel(ControlledAC);

	Elevator = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLocalGust
//Author		Craig Beeston
//Date			Mon 18 Jan 1999
//
//Description	Used to set the gust for an individual aircraft due to an explosion in the area
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetLocalGust(COORDS3D AcPos, COORDS3D HitPos, SWord Strength)
{
	FCRD DirVec;
	DirVec.x = AcPos.X - HitPos.X;
	DirVec.y = AcPos.Y - HitPos.Y;
	DirVec.z = AcPos.Z - HitPos.Z;

	NrmVec(DirVec, DirVec);

	Gust.ACTIVE = TRUE;
	
	Gust.Vec.x = DirVec.x * (FP)Strength;
	Gust.Vec.y = DirVec.y * (FP)Strength;
	Gust.Vec.z = DirVec.z * (FP)Strength;

	Gust.Time = 100;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitialiseEngines
//Author		Craig Beeston
//Date			Tue 24 Nov 1998
//
//Description	Processes all aircraft engines so that they start at approx the right speed
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::InitialiseEngines (AirStrucPtr const ControlledAC)
{
	EngineSelected = ES_BOTH;
	ModelThrottle = ControlledAC->fly.thrustpercent;

	PENGINE pEngine = EngineList;
	PGEAR   pGear   = GearList;

	if(Speed < 50)
		GearTouched = TRUE;

	while(pEngine != NULL)
	{
		pEngine->ThrottleSetting = ModelThrottle;

		switch (pEngine->Type)
		{
			case ET_VOID:
			break;
				
			case ET_PISTON:
			{
				if(ControlledAC->vel_ < 100000)
				{
					if(		(ControlledAC == Persons2::PlayerSeenAC) && (!Persons2::PlayerGhostAC->fly.expandedsag)
						&&	(Save_Data.flightdifficulty[FD_ENGINEMANAGMENT])	)
						
					{
						pEngine->Speed = 0;
						pEngine->PropInc = pEngine->PropMinPitch;
						pEngine->SlipRot = 0;
						pEngine->SlipVel = 0;
						pEngine->PropVel = 0;
						pEngine->PropSetting = 1.0;
						pEngine->ThrottleSetting = 0;
						pEngine->FuelInPipes = 0;
						pEngine->Temperature = 0;
						pEngine->Magnetos = 0;
					}
					else
					{
						pEngine->Speed = (15.0 + 0.85 * pEngine->ThrottleSetting) * pEngine->Rpm100 * 0.001047197 * 0.01;
						pEngine->PropInc = pEngine->PropMinPitch;
						pEngine->SlipRot = 0;
						pEngine->SlipVel = 15.0 + 0.55 * pEngine->ThrottleSetting;
						pEngine->PropVel = pEngine->SlipVel / 2.0;
						pEngine->PropSetting = 0;
						pEngine->ThrottleSetting = 0;
						pEngine->FuelInPipes = 1;
						pEngine->Temperature = 100;
						pEngine->Magnetos = 3;
					}
				}
				else
				{
					pEngine->ThrottleSetting = 75;
					pEngine->Speed = pEngine->Rpm100 * 0.75 * 0.001047197;
					switch (pEngine->PropType)
					{
						case PT_FIXED:
							pEngine->PropSetting = 1.0;
							break;
						case PT_2PITCH:
							pEngine->PropSetting = 0.0;
							break;
						case PT_VARIABLE:
							pEngine->PropSetting = 0.01;
							break;
						case PT_CONSTSPEED:
							pEngine->PropSetting = 0.67;
							break;
						break;
					}

					pEngine->PropInc = 60;
					pEngine->SlipVel = Speed;
					pEngine->PropVel = Speed;
					pEngine->SlipRot = 0;

					pEngine->FuelInPipes = 1;
					pEngine->Temperature = 100;
					pEngine->Magnetos = 3;
				}

				ModelThrottle = SWord(pEngine->ThrottleSetting);
				ControlledAC->fly.thrustpercent = ModelThrottle;

				ModelPropSetting = SWord(pEngine->PropSetting * 100.0);
				ControlledAC->fly.propsetting = ModelPropSetting;

				break;
			}
		
//JET_Code CSB 22/09/99				case ET_JET:
//JET_Code CSB 22/09/99				{
//JET_Code CSB 22/09/99					FP RootTempRatio = FSqrt(AmbTemp / 288.15);
//JET_Code CSB 22/09/99					FP ThrustRatio = 0.01 * ControlledAC->fly.thrustpercent;
//JET_Code CSB 22/09/99					pEngine->ThrustRpm->GetIndex(ThrustRatio, pEngine->SpeedRpm);
//JET_Code CSB 22/09/99					pEngine->SpeedRpm *= pEngine->Rpm100;
//JET_Code CSB 22/09/99					pEngine->SpeedRpm *= RootTempRatio;
//JET_Code CSB 22/09/99					break;
//JET_Code CSB 22/09/99				}
		}
		pEngine = pEngine->List.NextItem();
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessEngines
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Process all aircraft engines
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessEngines (AirStrucPtr const ControlledAC)
{
	if(FirstCycle) 
		InitialiseEngines(ControlledAC);	//CSB 24/11/98

	for(SWord i = 0; i < 4; i++)
		ControlledAC->fly.use_this_tank[i] = FuelCockTanks[ControlledAC->fly.FuelCockPos][i];


	for(PENGINE pEngine = EngineList; pEngine; pEngine = pEngine->List.NextItem())
	{
		switch (pEngine->Type)
		{
			case ET_VOID:
				break;

			case ET_PISTON:
				pEngine->ProcessPistonEngine (ControlledAC);
				break;

//JET_Code CSB 29/10/99				case ET_JET:
//JET_Code CSB 29/10/99					pEngine->ProcessJetEngine (ControlledAC);
//JET_Code CSB 29/10/99					break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RestartEngines
//Author		Craig Beeston
//Date			Tue 25 Nov 1998
//
//Description	Restarts all aircraft jet engines
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RestartEngines (AirStrucPtr const ControlledAC)
{
//JET_Code CSB 22/09/99		PENGINE pEngine = EngineList;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		while (pEngine != NULL)
//JET_Code CSB 22/09/99		{
//JET_Code CSB 22/09/99			if( (pEngine->Type == ET_JET) && (pEngine->EngineOut) )
//JET_Code CSB 22/09/99			{
//JET_Code CSB 22/09/99				_Miles.PlaySample(FIL_SFX_NO_AMMO_CLICK, 8191);//5120);
//JET_Code CSB 22/09/99	//DeadCode CSB 03/03/99				_Miles.PlaySample(FIL_SFX_OFFICE_DRAWER2, 5120);
//JET_Code CSB 22/09/99				_Miles.PlaySample(FIL_SFX_GUN_TANK2, 32767);
//JET_Code CSB 22/09/99				if( (ControlledAC->fly.thrustpercent <= 25) )
//JET_Code CSB 22/09/99	//DeadCode CSB 03/03/99					(ControlledAC->fly.thrustpercent <= 50) )
//JET_Code CSB 22/09/99					pEngine->EngineOut = FALSE;
//JET_Code CSB 22/09/99			}
//JET_Code CSB 22/09/99			pEngine = pEngine->List.NextItem ();
//JET_Code CSB 22/09/99		}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcFuelRate
//Author		Craig Beeston
//Date			Tue 15 Sep 1998
//
//Description	Calculates the total rate of fuel usage for all engines as a fraction
//				of the maximum fuel rate per engine.  i.e. 1 engine at < max thrust- usage < 1
//														   1 engine at max thrust  - usage = 1
//														   2 engines at max thrust - usage = 1
//
//Inputs		
//
//Returns		The rate of fuel usage for whole aircraft
//
//------------------------------------------------------------------------------
FP Model::CalcFuelRate (AirStrucPtr const ControlledAC)
{
	FP usage = 0;
	UWord NoEngines = 0;
	PENGINE pEngine = EngineList;

	while(pEngine != NULL)
	{
		FP RateTemp;
//JETCODE CSB 29/10/99 		if(pEngine->Type == ET_JET)
//JETCODE CSB 29/10/99 			RateTemp = pEngine->Thrust / pEngine->T100;// * (1 + 0.45 * Inst.MachNo);
//JETCODE CSB 29/10/99 		else
		{
			RateTemp = pEngine->ThrottleSetting * 0.01;
			if(RateTemp < 0.1)	RateTemp = 0.1;
			RateTemp *=	pEngine->Speed * 945.93 / pEngine->Rpm100;
		}
		if(pEngine->FuelInPipes)
			usage += RateTemp;
		NoEngines++;
		pEngine = pEngine->List.NextItem ();
	}

	if(NoEngines)
		usage /= NoEngines;

	return(usage);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFuelTank
//Author		Craig Beeston
//Date			Fri 5 Nov 1999
//
//Description	Sets the appropriate fuel tanks to use
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetFuelTank(AirStrucPtr const ControlledAC, bool player)
{
	if((!player) || (!Save_Data.flightdifficulty[FD_ENGINEMANAGMENT]))
	{
		bool usingdroptanks = false;
		SLong maxfuel  = 0;
		SLong bestcock = 0;
		
		for(SWord cock = 0; cock < 4; cock++)	//Find best fuel cock setting using droptanks
		{
			SLong totfuel = 0;
			for(SWord tank = 0; tank < 4; tank++)
				if((ControlledAC->classtype->fueltanktype[tank] == FT_DROPTANK) && (FuelCockTanks[cock][tank]))
					totfuel += ControlledAC->fly.fuel_content[tank];
			if(totfuel > maxfuel)
			{
				bestcock = cock;
				maxfuel  = totfuel;
			}
		}
		
		if(maxfuel == 0)			//Find best fuel cock setting using fixed tanks
		{

			for(SWord cock = 0; cock < 4; cock++)
			{
				SLong totfuel = 0;
				SLong biggesttank = 0;
				for(SWord tank = 0; tank < 4; tank++)
					if((FuelCockTanks[cock][tank]) && (ControlledAC->fly.fuel_content[tank]))
						if(ControlledAC->classtype->fueltankcap[tank] > biggesttank)
							biggesttank = ControlledAC->classtype->fueltankcap[tank];

				if(biggesttank > 0)
				{
					for(tank = 0; tank < 4; tank++)
						if(FuelCockTanks[cock][tank])
						{
							totfuel -= 1;
							if((ControlledAC->classtype->fueltankcap[tank] == biggesttank) && (ControlledAC->fly.fuel_content[tank]))
								totfuel += ControlledAC->classtype->fueltankcap[tank];
						}
					
					if(totfuel > maxfuel)
					{
						bestcock = cock;
						maxfuel = totfuel;
					}
				}
			}
		}
		
		for(SWord i = 0; i < 4; i++)
			ControlledAC->fly.use_this_tank[i] = FuelCockTanks[bestcock][i];

		ControlledAC->fly.FuelCockPos = bestcock;
	}
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessDevices
//Author		Andrew McRae
//Date			Tue 12 Aug 1997
//
//Description	Flaps, slats, speed brakes, etc.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessDevices ()
{

	DeltaCl = 0;
	DeltaCd = 0;
	DeltaCm = 0;
	DeltaAlpha = 0;

	PAERODEVICE pDevice = DeviceList;

	while (pDevice != NULL)
	{
		pDevice->Process ();
		pDevice = pDevice->List.NextItem ();
	}

}

void Model::GearUp (AirStrucPtr const ControlledAC)
{

	PAERODEVICE pDevice = DeviceList;

	while (pDevice != NULL)
	{
		pDevice->GearUp ();
		pDevice = pDevice->List.NextItem ();
	}
	SetGearAnimPos(ControlledAC,ANIM_GEAR_UP);
	SHAPE.NavigationLightsActive(ControlledAC, FALSE);
}

void Model::GearDown (AirStrucPtr const ControlledAC)
{

	PAERODEVICE pDevice = DeviceList;

	while (pDevice != NULL)
	{
		pDevice->GearDown ();
		pDevice = pDevice->List.NextItem ();
	}
//DEADCODE CSB 29/02/00 	SetGearAnimPos(ControlledAC,ANIM_GEAR_DOWN);
	Animations(ControlledAC, true);											//CSB 29/02/00
	SHAPE.NavigationLightsActive(ControlledAC, TRUE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessMainElements
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Processes all aircraft elements
//
//Inputs		
//																	   MControlPower
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessMainElements (AirStrucPtr const ControlledAC)
{
	if(AirSpeed < ControlLossV0)
		FControlLoss = 1;
	else
	{
		if(AirSpeed < ControlLossV1)
			FControlLoss = 1.0 - 0.8 * (AirSpeed - ControlLossV0) / (ControlLossV1 - ControlLossV0);
		else
			FControlLoss = 0.2;

		if(ControlledAC == Persons2::PlayerSeenAC)
		{
			SLong temp1 = (Elevator * Elevator) >> 15;
			SLong temp2 = (Aileron  * Aileron ) >> 15;
			if(temp2 > temp1)	temp1 = temp2;
			temp2 = (Rudder * Rudder) >> 15;
			if(temp2 > temp1)	temp1 = temp2;
			if(Math_Lib.rnd(32768) < (0.01 * temp1 / FControlLoss))
				_Miles.PlayOnce(FIL_SFX_OUT_OF_BREATH1, 128);
		}
	}

	// MainPlane
	PMAINPLANE pMainPlane = MainPlaneList;
	while (pMainPlane != NULL)
	{
		pMainPlane->Process (ControlledAC);
		pMainPlane = pMainPlane->List.NextItem ();
	}


	// Surfaces
	PSURFACE pSurface = SurfaceList;
	while (pSurface != NULL)
	{
		if (pSurface->Type != ST_MAINPLANE)
			pSurface->Process (ControlledAC);
		pSurface = pSurface->List.NextItem ();
	}


	// Cylinder	//CSB 05/11/98
	PCYLINDER pCylinder = CylinderList;
	while (pCylinder != NULL)
	{
		pCylinder->Process (ControlledAC);
		pCylinder = pCylinder->List.NextItem ();
	}


	// ThrustPoints
	PTHRUSTPOINT pThrust = ThrustList;
	while (pThrust != NULL)
	{
		pThrust->Process ();
		pThrust = pThrust->List.NextItem ();
	}

	
//DEADCODE CSB 06/03/00 	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])		//CSB	//03 Sep 98
		ProcessStoresDrag(ControlledAC);

//CSB  11/09/98
//Calculate the Moment which acts of the aircraft do to rotation about two or more axis at once

	FCRD TempFCRD;
	TempFCRD.x = RotVel.x * RotInertia.x;
	TempFCRD.y = RotVel.y * RotInertia.y;
	TempFCRD.z = RotVel.z * RotInertia.z;

	CPrd(InertiaMoment, TempFCRD, RotVel);
	
	InertiaMoment.x *= -1;
	InertiaMoment.y *= -1;
	InertiaMoment.z *= -1;
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessStoresDrag
//Author		Craig Beeston
//Date			Thu 03 Sep 1998
//
//Description	Calculated the drag and yawing moment on the aircraft due to the 
//				weapons/drop tanks.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessStoresDrag (AirStrucPtr const ControlledAC)
{
	StoresForce.x = 0.0;
	StoresForce.y = 0.0;
	StoresForce.z = -( ControlledAC->weap.left.drag + ControlledAC->weap.centre.drag 
						+ ControlledAC->weap.right.drag );
	StoresForce.z *= DynamicPressure;

	FP Pos = ControlledAC->fly.pModel->MainPlaneList->Pos[0][1].x;
	StoresMoment.x = 0.0;
	StoresMoment.y =  ControlledAC->weap.right.drag - ControlledAC->weap.left.drag;
	StoresMoment.y *= DynamicPressure * Pos;
	StoresMoment.z = 0.0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcNettForceMoment
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calculates total force and moment on the aircraft
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcNettForceMoment (FCRD& Force, FCRD& Moment)
{
	FCRD dmoment;

	FILE* fp;

//DeadCode AMM 3Jul00 	if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 	{
//DeadCode AMM 3Jul00 		fp=fopen("plop.txt","at");
//DeadCode AMM 3Jul00 		fprintf(fp,"mainplane\n");
//DeadCode AMM 3Jul00 	}
	// MainPlane
	PMAINPLANE pMainPlane = MainPlaneList;
	while (pMainPlane != NULL)
	{
		for(SWord wing = 0; wing < 2; wing++)
			for(SWord section = 0; section < 2; section++)
			{
				AddVec (Force,  Force,  pMainPlane->eForce[wing][section]);
				AddVec (Moment, Moment, pMainPlane->eMoment[wing][section]);
		
				CPrd (dmoment, pMainPlane->eForce[wing][section], pMainPlane->Pos[wing][section]);
				AddVec (Moment, Moment, dmoment);

//DeadCode AMM 3Jul00 				if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 				{
//DeadCode AMM 3Jul00 					fprintf(fp,"posx=%f posy=%f posz=%f\n",
//DeadCode AMM 3Jul00 						pMainPlane->Pos[wing][section].x,
//DeadCode AMM 3Jul00 						pMainPlane->Pos[wing][section].y,
//DeadCode AMM 3Jul00 						pMainPlane->Pos[wing][section].z);
//DeadCode AMM 3Jul00 					fprintf(fp,"efx=%f efy=%f efz=%f\n",
//DeadCode AMM 3Jul00 						pMainPlane->eForce[wing][section].x,
//DeadCode AMM 3Jul00 						pMainPlane->eForce[wing][section].y,
//DeadCode AMM 3Jul00 						pMainPlane->eForce[wing][section].z);
//DeadCode AMM 3Jul00 					fprintf(fp,"emx=%f emy=%f emz=%f\n",
//DeadCode AMM 3Jul00 						pMainPlane->eMoment[wing][section].x,
//DeadCode AMM 3Jul00 						pMainPlane->eMoment[wing][section].y,
//DeadCode AMM 3Jul00 						pMainPlane->eMoment[wing][section].z);
//DeadCode AMM 3Jul00 					fprintf(fp,"forcex=%f forcey=%f forcez=%f\n",
//DeadCode AMM 3Jul00 						Force.x,
//DeadCode AMM 3Jul00 						Force.y,
//DeadCode AMM 3Jul00 						Force.x);
//DeadCode AMM 3Jul00 					fprintf(fp,"mx=%f my=%f mz=%f\n",
//DeadCode AMM 3Jul00 						Moment.x,
//DeadCode AMM 3Jul00 						Moment.y,
//DeadCode AMM 3Jul00 						Moment.x);
//DeadCode AMM 3Jul00 				}
			}
		pMainPlane = pMainPlane->List.NextItem ();
	}

//DeadCode AMM 3Jul00 	if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 	{
//DeadCode AMM 3Jul00 		fprintf(fp,"surfaces\n");
//DeadCode AMM 3Jul00 	}
	// Surfaces
	PSURFACE pSurface = SurfaceList;
	while (pSurface != NULL)
	{
		AddVec (Force, Force, pSurface->Force);
		AddVec (Moment, Moment, pSurface->Moment);

		CPrd (dmoment, pSurface->Force, pSurface->Pos);
		AddVec (Moment, Moment, dmoment);

		pSurface = pSurface->List.NextItem ();

//DeadCode AMM 3Jul00 		if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 		{
//DeadCode AMM 3Jul00 			fprintf(fp,"forcex=%f forcey=%f forcez=%f\n",
//DeadCode AMM 3Jul00 				Force.x,
//DeadCode AMM 3Jul00 				Force.y,
//DeadCode AMM 3Jul00 				Force.x);
//DeadCode AMM 3Jul00 			fprintf(fp,"mx=%f my=%f mz=%f\n",
//DeadCode AMM 3Jul00 				Moment.x,
//DeadCode AMM 3Jul00 				Moment.y,
//DeadCode AMM 3Jul00 				Moment.x);
//DeadCode AMM 3Jul00 		}
	}


//DeadCode AMM 3Jul00 	if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 	{
//DeadCode AMM 3Jul00 		fprintf(fp,"cylinders\n");
//DeadCode AMM 3Jul00 	}

// Cylinders	//CSB 05/11/98
	PCYLINDER pCylinder = CylinderList;
	while (pCylinder != NULL)
	{
		AddVec (Force, Force, pCylinder->Force);

		CPrd (dmoment, pCylinder->Force, pCylinder->Pos);
		AddVec (Moment, Moment, dmoment);

		pCylinder = pCylinder->List.NextItem ();

//DeadCode AMM 3Jul00 		if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 		{
//DeadCode AMM 3Jul00 			fprintf(fp,"forcex=%f forcey=%f forcez=%f\n",
//DeadCode AMM 3Jul00 				Force.x,
//DeadCode AMM 3Jul00 				Force.y,
//DeadCode AMM 3Jul00 				Force.x);
//DeadCode AMM 3Jul00 			fprintf(fp,"mx=%f my=%f mz=%f\n",
//DeadCode AMM 3Jul00 				Moment.x,
//DeadCode AMM 3Jul00 				Moment.y,
//DeadCode AMM 3Jul00 				Moment.x);
//DeadCode AMM 3Jul00 		}
	}

//DeadCode AMM 3Jul00 	if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 	{
//DeadCode AMM 3Jul00 		fprintf(fp,"stores\n");
//DeadCode AMM 3Jul00 	}

	// StoresDrag	//CSB	03 Sep 98
//DEADCODE CSB 06/03/00 	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
	{
		AddVec (Force, Force, StoresForce);
		AddVec (Moment, Moment, StoresMoment);
	}

//DeadCode AMM 3Jul00 	if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 	{
//DeadCode AMM 3Jul00 		fprintf(fp,"forcex=%f forcey=%f forcez=%f\n",
//DeadCode AMM 3Jul00 			Force.x,
//DeadCode AMM 3Jul00 			Force.y,
//DeadCode AMM 3Jul00 			Force.x);
//DeadCode AMM 3Jul00 		fprintf(fp,"mx=%f my=%f mz=%f\n",
//DeadCode AMM 3Jul00 			Moment.x,
//DeadCode AMM 3Jul00 			Moment.y,
//DeadCode AMM 3Jul00 			Moment.x);
//DeadCode AMM 3Jul00 
//DeadCode AMM 3Jul00 		fprintf(fp,"complex rot\n");
//DeadCode AMM 3Jul00 	}
	// Moment due to complex rotation
	AddVec (Moment, Moment, InertiaMoment);

//DeadCode AMM 3Jul00 	if (_Replay.replayframecount==9 && !this->Controlled)
//DeadCode AMM 3Jul00 	{
//DeadCode AMM 3Jul00 		fprintf(fp,"mx=%f my=%f mz=%f\n",
//DeadCode AMM 3Jul00 			Moment.x,
//DeadCode AMM 3Jul00 			Moment.y,
//DeadCode AMM 3Jul00 			Moment.x);
//DeadCode AMM 3Jul00 
//DeadCode AMM 3Jul00 		fclose(fp);
//DeadCode AMM 3Jul00 	}
	// Limit forces and moments to sensible limits

#ifdef CALC_FORCE_MOMENT_LIMITS

	static FCRD MaxForce = {0,0,0};
	static FCRD MinForce = {0,0,0};

	static FCRD MaxMoment = {0,0,0};
	static FCRD MinMoment = {0,0,0};

	if (Force.x > MaxForce.x) MaxForce.x = Force.x;
	if (Force.y > MaxForce.y) MaxForce.y = Force.y;
	if (Force.z > MaxForce.z) MaxForce.z = Force.z;

	if (Force.x < MinForce.x) MinForce.x = Force.x;
	if (Force.y < MinForce.y) MinForce.y = Force.y;
	if (Force.z < MinForce.z) MinForce.z = Force.z;

	if (Moment.x > MaxMoment.x) MaxMoment.x = Moment.x;
	if (Moment.y > MaxMoment.y) MaxMoment.y = Moment.y;
	if (Moment.z > MaxMoment.z) MaxMoment.z = Moment.z;

	if (Moment.x < MinMoment.x) MinMoment.x = Moment.x;
	if (Moment.y < MinMoment.y) MinMoment.y = Moment.y;
	if (Moment.z < MinMoment.z) MinMoment.z = Moment.z;

	#define XFORCELIMIT 600000
	#define YFORCELIMIT 2500000
	#define ZFORCELIMIT 600000

	#define XMOMENTLIMIT 250000000
	#define YMOMENTLIMIT 250000000
	#define ZMOMENTLIMIT 250000000

	UWord bits = 0;

	if (Force.x > XFORCELIMIT)
	{
		Force.x = XFORCELIMIT;
		bits |= 0x4000;
	}
	if (Force.x < -XFORCELIMIT)
	{
		Force.x = -XFORCELIMIT;
		bits |= 0x400;
	}
	if (Force.y > YFORCELIMIT)
	{
		Force.y = YFORCELIMIT;
		bits |= 0x2000;
	}
	if (Force.y < -YFORCELIMIT)
	{
		Force.y = -YFORCELIMIT;
		bits |= 0x200;
	}
	if (Force.z > ZFORCELIMIT)
	{
		Force.z = ZFORCELIMIT;
		bits |= 0x1000;
	}
	if (Force.z < -ZFORCELIMIT)
	{
		Force.z = -ZFORCELIMIT;
		bits |= 0x100;
	}

	if (Moment.x > XMOMENTLIMIT)
	{
		Moment.x = XMOMENTLIMIT;
		bits |= 0x40;
	}
	if (Moment.x < -XMOMENTLIMIT)
	{
		Moment.x = -XMOMENTLIMIT;
		bits |= 0x4;
	}
	if (Moment.y > YMOMENTLIMIT)
	{
		Moment.y = YMOMENTLIMIT;
		bits |= 0x20;
	}
	if (Moment.y < -YMOMENTLIMIT)
	{
		Moment.y = -YMOMENTLIMIT;
		bits |= 0x2;
	}
	if (Moment.z > ZMOMENTLIMIT)
	{
		Moment.z = ZMOMENTLIMIT;
		bits |= 0x10;
	}
	if (Moment.z < -ZMOMENTLIMIT)
	{
		Moment.z = -ZMOMENTLIMIT;
		bits |= 0x1;
	}

#endif


}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WingDamage
//Author		Craig Beeston
//Date			Fri 22 Jan 1999
//
//Description	Check to see in the aircraft is pulling V high G 
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::WingDamage (AirStrucPtr const ControlledAC, FP forcey)
{
	FP NumG = forcey / (Mass * GRAVITY);
	if( (NumG > MinG) && (NumG < MaxG) ) return;

	FP StressLevel = 0;

	if(NumG > MaxG) StressLevel = NumG / MaxG;
	if(NumG < MinG) StressLevel = NumG / MinG;

	if(StressLevel < 1.5)
		_Miles.PlayOnce(FIL_SFX_CREAK7, (int)(128.0 * (StressLevel - 0.5)));//RJS 20May99
	else
	{
		if(Math_Lib.rnd() <= 6554 * Timer_Code.FRAMETIME)	// 1 second	//CSB 17/05/99	
		{
			AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
			if(Type == AT_BF109)
				SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->TAIL, BS_DEAD);
			else
			{
				SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->LEFTWINGOUT, BS_DEAD);
				SHAPE.ForceDamage(ControlledAC,ControlledAC, &adptr->RIGHTWINGOUT, BS_DEAD);
			}
	//DeadCode AMM 26Apr99 		_Miles.PlaySample(FIL_SFX_EXPLOSION_ENGINE, 128);	//fix this !!!!
//DEADCODE CSB 24/01/00 			_Miles.PlayOnce(FIL_SFX_METAL_SNAP,ControlledAC);					//RJS 26Apr99
//DeadCode CSB 1Nov00 			if(Trans_Obj.View_Object && (ControlledAC == Manual_Pilot.ControlledAC2))
//DeadCode CSB 1Nov00 				Trans_Obj.View_Object->SetToDeathView(DEATH_NORMAL);
		}
		else
			_Miles.PlayOnce(FIL_SFX_CREAK7);					//RJS 20May99
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcAcc
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calculates acceleration on the aircraft, in local coords
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcAcc ()
{
//DeadCode CSB 10/06/99		FCRD GroundVel;
//DeadCode CSB 10/06/99		TnsAxs(Vel, GroundVel, Ori);

	Acc.x = NettForce.x / Mass - GRAVITY * Ori.x.y;// + RotVel.y * GroundVel.z - RotVel.z * GroundVel.y;
	Acc.y = NettForce.y / Mass - GRAVITY * Ori.y.y;// + RotVel.z * GroundVel.x - RotVel.x * GroundVel.z;
	Acc.z = NettForce.z / Mass - GRAVITY * Ori.z.y;// + RotVel.x * GroundVel.y - RotVel.y * GroundVel.x;

	TnsPnt(NettForce, wAcc, Ori);	//Calc acc in world coords
	
	wAcc.x /= Mass;
	wAcc.y /= Mass;
	wAcc.z /= Mass;

	wAcc.y -= GRAVITY;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcRotAcc
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	calculates rotation acceleration on ac, in local coords
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcRotAcc ()
{
	RotAcc.x = (NettMoment.x / RotInertia.x);
	RotAcc.y = (NettMoment.y / RotInertia.y);
	RotAcc.z = (NettMoment.z / RotInertia.z);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MovePilotEye
//Author		Craig Beeston
//Date			Fri 30 Oct 1998
//
//Description	Moves the eye position to model an elastic neck
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::MovePilotEye ()
{
	CockpitBuf EyePos;
	CockpitBuf* pEyePos = &EyePos;

	FCRD NumG;
	FCRD DeltaEye;
	FP Scale = 1024.0;

	if(Trans_Obj.View_Object->trackeditem2)
	{
		DeltaEye.x = 0;	
		DeltaEye.y = 0;
		DeltaEye.z = 0;	
	}
	else
	{
		FP OneOverMass = 1 / Mass;
		FP OneOverG	   = 1 / GRAVITY;

		if((PilotEyePos.x == 0) && (PilotEyePos.y == 0) && (PilotEyePos.z == 0))
		{
			PilotEyePos.x = 0;
			PilotEyePos.y = 65;
			PilotEyePos.z = -150;
		}

		CPrd(NumG, PilotEyePos, RotAcc);

		NumG.x += NettForce.x * OneOverMass;
		NumG.y += NettForce.y * OneOverMass;
		NumG.z += NettForce.z * OneOverMass;

		NumG.x *= OneOverG;
		NumG.y *= OneOverG;
		NumG.z *= OneOverG;

		DeltaEye.x = -NumG.x * Scale * 4.0;	
		DeltaEye.y = -(NumG.y - 1.0) * Scale * 1.0;
		DeltaEye.z = -NumG.z * Scale * 4.0;	
		
		MODLIMIT(DeltaEye.x, 4.0 * Scale);
		MODLIMIT(DeltaEye.y, 4.0 * Scale);
		MODLIMIT(DeltaEye.z, 4.0 * Scale);
	}
//DeadCode RJS 27Mar00 	EyePos.hdg   = 0;
//DeadCode RJS 27Mar00 	EyePos.pitch = 0;
//DeadCode RJS 27Mar00 	EyePos.roll  = 0;

	if( (TotalBuffet) && (!GearTouched) )
	{	
		if(FrameCount & 0x0001)
			DeltaEye.y += 0.075 * Scale * TotalBuffet;//0.125
		else
			DeltaEye.y -= 0.075 * Scale * TotalBuffet;//0.125;

		if(FrameCount & 0x0002)
			DeltaEye.x += 0.025 * Scale * TotalBuffet;//0.125;
		else
			DeltaEye.x -= 0.025 * Scale * TotalBuffet;//0.125;

//DeadCode RJS 30Aug00 		_Miles.PlayBuffet(SLong(64.0 * TotalBuffet));//RJS 29Jan99
	}

	_Miles.PlayBuffet(SLong(64.0 * TotalBuffet));						//RJS 30Aug00

	fastMath.FloatToInt(&EyePos.delta.X,DeltaEye.x);		//RJS 27Mar00
	fastMath.FloatToInt(&EyePos.delta.Y,DeltaEye.y);		//RJS 27Mar00
	fastMath.FloatToInt(&EyePos.delta.Z,DeltaEye.z);		//RJS 27Mar00
	
	EyePos.delta.X += (stretchyNeck<<10);

//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	static SWord HeadX = 0;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	SWord MaxHeadX = 125;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	for(PAERODEVICE pDevice = DeviceList; pDevice; pDevice = pDevice->List.NextItem())
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		if((pDevice->Type == AeroDevice::DT_CANOPY) && (pDevice->Val < 0x4000))
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */			MaxHeadX = 25;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	const SWord HeadRate = 10 * MODEL_DT;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	if(HeadX <= 0)
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	{
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		if(Key_Tests.KeyHeld3d(HEADOUTVIEWL))
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		{
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */			if(HeadX > -MaxHeadX)
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */				HeadX -= HeadRate;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		}
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		else
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */			if(HeadX < 0)
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */				HeadX += HeadRate;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	}
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	if(HeadX >= 0)
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	{
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		if(Key_Tests.KeyHeld3d(HEADOUTVIEWR))
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		{
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */			if(HeadX < MaxHeadX)
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */				HeadX += HeadRate;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		}
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */		else
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */			if(HeadX > 0)
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */				HeadX -= HeadRate;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	}
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	EyePos.delta.X -= HeadX;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	EyePos.pitch = (1820.0 / 125.0) * HeadX;
//DEADCODE CSB 06/03/00 /* TEST CODE CSB 25/08/99 */	if(SWord(EyePos.pitch) < 0)	EyePos.pitch *= -1;

//DeadCode CSB 24/03/99		EyePos.delta.X = 0;
//DeadCode CSB 24/03/99		EyePos.delta.Y = 0;
//DeadCode CSB 24/03/99		EyePos.delta.Z = 0;
//DeadCode CSB 24/03/99	
//DeadCode CSB 24/03/99		EyePos.hdg   = 0;
//DeadCode CSB 24/03/99		EyePos.pitch = 0;
//DeadCode CSB 24/03/99		EyePos.roll  = 0;
					
	SHAPE.SetCockpitBuffet(pEyePos);							//RJS 27Mar00

	if(Save_Data.hardwareconfig[HW_GEFFECTS])
	{
		FP gBlack = 4.5;
		FP gRed   = -1.5;
		if (Save_Data.flightdifficulty[FD_POWERBOOST])
		{  gBlack *= 1.25;	gRed   *= 1.25;	}

		FP G = Inst.I_NormalAcc;
		if(Blood <= 1)
		{
			FP OldBlood = Blood;	
			FP BloodFlow = (gBlack - G) * 0.00025;
			if(	   ((BloodFlow > 0) && (Blood < 1))
				|| ((BloodFlow < 0) && (Blood > 0)) )
				Blood += BloodFlow * MODEL_DT;
			if(    ((OldBlood > 0.6667) && (Blood < 0.6667))
				|| ((OldBlood > 0.5)    && (Blood < 0.5)) )
				_Miles.PlayOnce(FIL_SFX_OUT_OF_BREATH2,128);		//RJS 21May99	//CSB 09/06/99	

		}
		else
		{
			FP BloodFlow = (gRed - G) * 0.00025;
			if(	   ((BloodFlow > 0) && (Blood < 1.5))
				|| ((BloodFlow < 0) && (Blood > 1)) )
				Blood += BloodFlow * MODEL_DT;
		}
	}
	else
		Blood = 1;
}

void	Model::HandleHead(SLong	flags, SLong frameTime, SWord& eyeDeltaX)	//RJS 12Oct00
{
	SWord MaxHeadX = 25;												//CSB 15Jun00
	switch(Type)
	{
		case AT_SPITFIRE:	MaxHeadX = 25;	break;
		case AT_HURRICANE:	MaxHeadX = 30;	break;
		case AT_BF109:		MaxHeadX = 30;	break;
		case AT_BF110:		MaxHeadX = 40;	break;
		case AT_JU87B:		MaxHeadX = 40;	break;
	}

	if(!AutoOpenCanopy())												//CSB 15Jun00
		MaxHeadX /= 3;												//CSB 15Jun00

	SWord desdelta = 0;
	if(flags == ZR_HeadLeft)
		desdelta = -MaxHeadX;
	else if(flags == ZR_HeadRight)
		desdelta = MaxHeadX;

	stretchyNeck = (stretchyNeck + desdelta) / 2;
	eyeDeltaX = stretchyNeck;

//DeadCode CSB 15Jun00 	if(stretchyNeck <= 0)										//JON 27Mar00
//DeadCode CSB 15Jun00 	{
//DeadCode CSB 15Jun00 		if(flags == ZR_HeadLeft)
//DeadCode CSB 15Jun00 		{
//DeadCode CSB 15Jun00 			if(stretchyNeck > -MaxHeadX)
//DeadCode CSB 15Jun00 				stretchyNeck -= HeadRate;
//DeadCode CSB 15Jun00 		}
//DeadCode CSB 15Jun00 		else
//DeadCode CSB 15Jun00 		{
//DeadCode CSB 15Jun00 			if(stretchyNeck < 0)
//DeadCode CSB 15Jun00 			{
//DeadCode CSB 15Jun00 				stretchyNeck += HeadRate;
//DeadCode CSB 15Jun00 				if (stretchyNeck > 0)
//DeadCode CSB 15Jun00 					stretchyNeck = 0;
//DeadCode CSB 15Jun00 			}
//DeadCode CSB 15Jun00 		}
//DeadCode CSB 15Jun00 	}
//DeadCode CSB 15Jun00 
//DeadCode CSB 15Jun00 	if(stretchyNeck >= 0)										//JON 27Mar00
//DeadCode CSB 15Jun00 	{
//DeadCode CSB 15Jun00 		if(flags == ZR_HeadRight)
//DeadCode CSB 15Jun00 		{
//DeadCode CSB 15Jun00 			if(stretchyNeck < MaxHeadX)
//DeadCode CSB 15Jun00 				stretchyNeck += HeadRate;
//DeadCode CSB 15Jun00 		}
//DeadCode CSB 15Jun00 		else
//DeadCode CSB 15Jun00 		{
//DeadCode CSB 15Jun00 			if(stretchyNeck > 0)
//DeadCode CSB 15Jun00 			{
//DeadCode CSB 15Jun00 				stretchyNeck -= HeadRate;
//DeadCode CSB 15Jun00 				if (stretchyNeck < 0)
//DeadCode CSB 15Jun00 					stretchyNeck = 0;
//DeadCode CSB 15Jun00 			}
//DeadCode CSB 15Jun00 		}
//DeadCode CSB 15Jun00 	}

//DeadCode CSB 15Jun00 	eyeDeltaX = stretchyNeck;
//DeadCode CSB 15Jun00 	eyePitch = (1820 * stretchyNeck)/20;
//DeadCode CSB 15Jun00 	if (eyePitch < 0)
//DeadCode CSB 15Jun00 		eyePitch *= -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSpeed
//Author		Craig Beeston
//Date			Wed 12 Dec 1998
//
//Description	Overwrites the acceleration in the z direction in order to keep the target aircraft the 
//				correct distance in front of the player
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetSpeed(AirStrucPtr const ControlledAC, FP desiredspeed)
{
	FP DesiredSpeed = 0.0001 * desiredspeed;
	PENGINE pEngine = EngineList;
	FP TotalThrust = 0;

	while (pEngine != NULL)
	{
		if(pEngine->Type == ET_JET) TotalThrust += pEngine->MaxThrust;
		pEngine = pEngine->List.NextItem ();
	}
	
	FP MaxAccel = 0;
	if(TotalThrust > 0) MaxAccel = TotalThrust / Mass;
	else MaxAccel = 0.1;	//Quite generous

	MaxAccel *= 4.0;
	if(Save_Data.flightdifficulty [FD_POWERBOOST])
		MaxAccel *= 1.5;
	
	FCRD GroundVel;
	TnsAxs(Vel, GroundVel, Ori);

	FP RequiredAcc = (DesiredSpeed - GroundVel.z) / MODEL_DT;

	FP AbsReqAcc = RequiredAcc;
	if(AbsReqAcc < 0) AbsReqAcc *= -1;
	if(AbsReqAcc > MaxAccel) CheatAcc.z = MaxAccel;
	else
		CheatAcc.z = AbsReqAcc;

	if(RequiredAcc < 0) CheatAcc.z *= -1;


	CheatAcc.z = CheatAcc.z - RotVel.x * GroundVel.y + RotVel.y * GroundVel.x;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetSpeed
//Author		Craig Beeston
//Date			Mon 1 Mar 1999
//
//Description	Replaces the existing acceleration (Global) with the given acc (Local) in any of the three axes
//
//Inputs		Old and Desired acceleration in ac local axes
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ModifyAcc(FCRD OldAcc, FCRD NewAcc)
{
	FCRD DeltaAcc;
	NullVec(DeltaAcc);
	if(NewAcc.x != 32767)	DeltaAcc.x = NewAcc.x - OldAcc.x;
	if(NewAcc.y != 32767)	DeltaAcc.y = NewAcc.y - OldAcc.y;
	if(NewAcc.z != 32767)	DeltaAcc.z = NewAcc.z - OldAcc.z;

	TnsPnt(DeltaAcc, DeltaAcc, Ori);
	AddVec(wAcc, wAcc, DeltaAcc);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChangeDirection
//Author		Craig Beeston
//Date			Mon 14 Dec 1998
//
//Description	Overwrites the rotational acceleration of the aircraft so that 
//				in one model loop the directions will change by the specified amounts
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ChangeDirection(AirStrucPtr const ControlledAC, FP DeltaPitch, FP DeltaYaw, FP DeltaRoll)
{
	FCRD GroundVel;	//Aircraft ground velocity in aircraft coordinates
	TnsAxs(Vel, GroundVel, Ori);

	MODMAXMIN(DeltaPitch, -0.00250 * MODEL_DT, 0.00500 * MODEL_DT);
	MODMAXMIN(DeltaYaw  , -0.00125 * MODEL_DT, 0.00125 * MODEL_DT);
	MODMAXMIN(DeltaRoll , -0.02500 * MODEL_DT, 0.02500 * MODEL_DT);

	RotOriXVec(Ori, DeltaPitch);	
	RotOriYVec(Ori, DeltaYaw);	
	RotOriZVec(Ori, DeltaRoll);	

	NrmVec(Ori.y, Ori.y);
	NrmVec(Ori.z, Ori.z);

	CPrdX(Ori);
	NrmVec(Ori.x, Ori.x);
	TnsPnt(GroundVel, Vel, Ori);

	NullVec(RotVel);

	UpdateAirStruc (ControlledAC);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TransInt
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Integrates in translation to get new velocity and position
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::TransInt (ITERATION_MASK mask, FP TimeFactor)
{
	FP dT = MODEL_DT * TimeFactor;

	switch (mask)
	{
		case ALL:
			Vel.x += wAcc.x * dT;
			Vel.y += wAcc.y * dT;
			Vel.z += wAcc.z * dT;

			MODLIMIT(Vel.x, 500);	//Mach 1.5
			MODLIMIT(Vel.y, 500);
			MODLIMIT(Vel.z, 500);

			
			Pos.x += Vel.x * dT;
			Pos.y += Vel.y * dT;
			Pos.z += Vel.z * dT;

			break;

		case YZ_ONLY:

			Vel.y += wAcc.y * dT;
			Vel.z += wAcc.z * dT;

			Pos.y += Vel.y * dT;
			Pos.z += Vel.z * dT;

			break;

		case Y_ONLY:

			Vel.y += wAcc.y * dT;

			Pos.y += Vel.y * dT;

			break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotInt
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Integrates in rotation to get new rot velocity and orientation
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RotInt (ITERATION_MASK mask)
{
	if (mask == XZ_ONLY)
	{
		RotVel.x += RotAcc.x * MODEL_DT;
		RotVel.z += RotAcc.z * MODEL_DT;

		RotOriXVec (Ori, RotVel.x * MODEL_DT);
		RotOriZVec (Ori, RotVel.z * MODEL_DT);
	}

	if (mask == ALL)
	{
		RotVel.x += RotAcc.x * MODEL_DT;
		RotVel.y += RotAcc.y * MODEL_DT;
		RotVel.z += RotAcc.z * MODEL_DT;

		MODLIMIT(RotVel.x, F2PIE * 0.01);	//360 per second
		MODLIMIT(RotVel.y, F2PIE * 0.01);
		MODLIMIT(RotVel.z, F2PIE * 0.01);

		RotVelInt ();
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RotVelInt
//Author		Andrew McRae
//Date			Fri 18 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RotVelInt ()
{
	RotOriZVec (Ori, RotVel.z * MODEL_DT * 0.5);
	RotOriYVec (Ori, RotVel.y * MODEL_DT * 0.5);
	RotOriXVec (Ori, RotVel.x * MODEL_DT);// * 0.5);
	RotOriYVec (Ori, RotVel.y * MODEL_DT * 0.5);
	RotOriZVec (Ori, RotVel.z * MODEL_DT * 0.5);

	CPrdX (Ori);
	CPrdZ (Ori);

	NrmVec (Ori.x, Ori.x);
	NrmVec (Ori.y, Ori.y);
	NrmVec (Ori.z, Ori.z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RemoveStore
//Author		rdh
//Date			
//
//Description	
//				pos < 0   ... left store,
//				pos > 0   ... right store,
//				pos = 0   ... centre store
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::RemoveStore(weap_info *weapptr,SLong pos,int mass, int drag, Bool fueltank)
{
	// Mass points stuff needs to be updated to cater for		//RJS 13May98
	// separate left and right store mass reduction....			//RJS 13May98
																//RJS 13May98
	if(pos > 0) pos = MainPlaneList->Pos[0][1].x;
	if(pos < 0) pos = MainPlaneList->Pos[1][1].x;
																//RJS 13May98
	if (weapptr->mass < mass)									//RJS 13May98
		mass = weapptr->mass; 									//RJS 13May98
																//RJS 13May98
	weapptr->mass -= mass;										//RJS 13May98
	weapptr->drag -= drag;										//RJS 13May98
	if (weapptr->drag < 0)										//RJS 13May98
		weapptr->drag = 0;										//RJS 13May98
	if (fueltank)												//RJS 13May98
	{															//RJS 13May98
//DeadCode RJS 26Nov99		weapptr->ext_fuel = 0;									//RJS 13May98
		// Craig, what do we do here?
	}

}

//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//Procedure		RemoveMass
//Author		Craig Beeston
//Date			Tue 08 Sep 1998
//
//Description	Given a mass and its location, this is removed from the total aircraft mass
//				and the contribution to the 3 rotational inertias are removed.
//
//Inputs		Mass (0.01 ), X,Y,Z (cm)
//
//Returns		-
//--------------------------------------------------------------------------------------------

void Model::RemoveMass(FP amount,FP massX, FP massY, FP massZ)
{
	Mass -= amount;

	FP distance;
	distance     =  VecLen2D (massY, massZ);
	RotInertia.x -= amount * distance * distance;	
	
	distance     =  VecLen2D (massX, massZ);
	RotInertia.y -= amount* distance * distance;	
	
	distance     =  VecLen2D (massX, massY);
	RotInertia.z -= amount * distance * distance;

	if(Mass < 1) Mass = 1;								//fix this to empty mass
	if(RotInertia.x < InertiaEmpty.x) RotInertia.x = InertiaEmpty.x;
	if(RotInertia.y < InertiaEmpty.y) RotInertia.y = InertiaEmpty.y;
	if(RotInertia.z < InertiaEmpty.z) RotInertia.z = InertiaEmpty.z;
}



//AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
//Procedure		AddMass
//Author		Craig Beeston
//Date			Tue 08 Sep 1998
//
//Description	Given a mass and its location, this is added onto the total aircraft mass
//				and the contribution to the 3 rotational inertias are added.
//
//Inputs		Mass (cg), X,Y,Z (cm)
//
//Returns		-
//--------------------------------------------------------------------------------------------

void Model::AddMass(FP amount,FP massX, FP massY, FP massZ)
{
	Mass += amount;
	
	FP distance;
	distance     =  VecLen2D (massY, massZ);
	RotInertia.x += amount * distance * distance;	
	
	distance     =  VecLen2D (massX, massZ);
	RotInertia.y += amount * distance * distance;	
	
	distance     =  VecLen2D (massX, massY);
	RotInertia.z += amount * distance * distance;	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupMassInertias
//Author		Craig Beeston
//Date			Tue 08 Sep 1998
//
//Description	Sets up the inertia of the aircraft empty, and adds the 
//				mass of fuel and mass and inertia of stores.
//
//Inputs		Aircraft mass, 3 inertias
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetMassInertias (AirStrucPtr const ControlledAC, FP EmptyIxx, FP EmptyIyy, FP EmptyIzz)
{
//for scramble factor is 2 for normal missions factor is 1
	int	fuelfactor = 2;
	
//DEADCODE CSB 28/01/00 	InertiaEmpty.x = EmptyIxx * 1355827;		//slug ft2 -> 0.01 kg cm2
//DEADCODE CSB 28/01/00 	InertiaEmpty.y = EmptyIyy * 1355827;
//DEADCODE CSB 28/01/00 	InertiaEmpty.z = EmptyIzz * 1355827;

	InertiaEmpty.x = EmptyIxx * 1000000;		//kg m2 -> 0.01 kg cm2
	InertiaEmpty.y = EmptyIyy * 1000000;
	InertiaEmpty.z = EmptyIzz * 1000000;

//DEADCODE CSB 24/02/00 	for(SWord i = 0; i < 4; i++)
//DEADCODE CSB 24/02/00 	{
//DEADCODE CSB 24/02/00 		FP fuelmass = ControlledAC->classtype->fueltankcap[i] * 1000 / fuelfactor;
//DEADCODE CSB 24/02/00 		if((Type == AT_BF109) && (Save_Data.flightdifficulty[FD_109FUEL]))
//DEADCODE CSB 24/02/00 			fuelmass *= 1.75;
//DEADCODE CSB 24/02/00 		ControlledAC->fly.fuel_content[i] = fuelmass;
//DEADCODE CSB 24/02/00 		if(fuelmass)	ControlledAC->fly.use_this_tank[i] = true;
//DEADCODE CSB 24/02/00 		else			ControlledAC->fly.use_this_tank[i] = false;
//DEADCODE CSB 24/02/00 	}

	UpdateMassInertias(ControlledAC);
	
//DEADCODE CB 05/11/99 //for scramble factor is 2 for normal missions factor is 1
//DEADCODE CB 05/11/99 	int	fuelfactor = 2;
//DEADCODE CB 05/11/99 	
//DEADCODE CB 05/11/99 	Mass     = ControlledAC->classtype->weightempty;
//DEADCODE CB 05/11/99 	int fuel = ControlledAC->classtype->maxintfuel/fuelfactor;	// 0.01 kg
//DEADCODE CB 05/11/99 	Mass += fuel;												// 0.01 kg
//DEADCODE CB 05/11/99 	ControlledAC->weap.centre.int_fuel = 500 * fuel;			// 0.01 g	Robs Stuff//RJS 25Mar99
//DEADCODE CB 05/11/99 	ControlledAC->weap.left.int_fuel = 250 * fuel;			// 0.01 g	Robs Stuff//RJS 25Mar99
//DEADCODE CB 05/11/99 	ControlledAC->weap.right.int_fuel = 250 * fuel;			// 0.01 g	Robs Stuff//RJS 25Mar99
//DEADCODE CB 05/11/99 	
//DEADCODE CB 05/11/99 	InertiaEmpty.x = EmptyIxx * 1355827;		//slug ft2 -> 0.01 kg cm2
//DEADCODE CB 05/11/99 	InertiaEmpty.y = EmptyIyy * 1355827;
//DEADCODE CB 05/11/99 	InertiaEmpty.z = EmptyIzz * 1355827;
//DEADCODE CB 05/11/99 
//DEADCODE CB 05/11/99 	RotInertia = InertiaEmpty;
//DEADCODE CB 05/11/99 
//DEADCODE CB 05/11/99 	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])		//CSB	//03 Sep 98
//DEADCODE CB 05/11/99 	{	
//DEADCODE CB 05/11/99 		AddMass(ControlledAC->weap.right.mass * 0.001,      MainPlaneList->Pos[0][0].x, 0, 0);			//0.01 kg, cm
//DEADCODE CB 05/11/99 		AddMass(ControlledAC->weap.right.ext_fuel * 0.001,  MainPlaneList->Pos[0][0].x, 0, 0);
//DEADCODE CB 05/11/99 		AddMass(ControlledAC->weap.centre.mass * 0.001,		0,		  0, 0);
//DEADCODE CB 05/11/99 		AddMass(ControlledAC->weap.centre.ext_fuel * 0.001, 0,        0, 0);
//DEADCODE CB 05/11/99 		AddMass(ControlledAC->weap.left.mass * 0.001,	    MainPlaneList->Pos[1][0].x, 0, 0);	
//DEADCODE CB 05/11/99 		AddMass(ControlledAC->weap.left.ext_fuel * 0.001,   MainPlaneList->Pos[1][0].x, 0, 0);
//DEADCODE CB 05/11/99 	}
//DEADCODE CB 05/11/99 
//DEADCODE CB 05/11/99 	if(	   (ControlledAC->weap.right.ext_fuel != 0)
//DEADCODE CB 05/11/99 		|| (ControlledAC->weap.centre.ext_fuel != 0)
//DEADCODE CB 05/11/99 		|| (ControlledAC->weap.left.ext_fuel != 0)
//DEADCODE CB 05/11/99 	   )
//DEADCODE CB 05/11/99 			ControlledAC->weap.UseIntFuel = FALSE;
}
	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTrim
//Author		Craig Beeston
//Date			Mon 27 Sep 1999
//
//Description	Sets up the range of trim for the aircraft
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetTrim (SWord elevtrim, SWord ailtrim, SWord rudtrim)
{
	MaxElevatorTrim = elevtrim;
	MaxAileronTrim  = ailtrim;
	MaxRudderTrim   = rudtrim;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFuelCockTanks
//Author		Craig Beeston
//Date			Thu 02 Dec 1999
//
//Description	Sets up the fuel tank combimation for the fuel cock
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetFuelCockTanks(SWord index, bool b0, bool b1, bool b2, bool b3)
{
	FuelCockTanks[index][0] = b0;
	FuelCockTanks[index][1] = b1;
	FuelCockTanks[index][2] = b2;
	FuelCockTanks[index][3] = b3;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateMassInertias
//Author		Craig Beeston
//Date			Fri 18 Jun 1999
//
//Description	calculates the total mass and iniertias of an aircraft
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::UpdateMassInertias (AirStrucPtr const ControlledAC)
{
	Mass	   = ControlledAC->classtype->weightempty;
	RotInertia = InertiaEmpty;

	if((_DPlay.Implemented) && (_DPlay.GameType != DPlay::COMMSQUICKMISSION))
		return;

	for(SWord i = 0; i < 4; i++)
//DEADCODE CSB 06/03/00 		if((ControlledAC->classtype->fueltanktype[i] == FT_FIXED) || (Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])) 
		{
			FP mass = ControlledAC->fly.fuel_content[i] * 0.001;
			FP dist = ControlledAC->classtype->fueltankxpos[i];
			Mass += mass;
			RotInertia.y += mass * dist * dist;
			RotInertia.z += mass * dist * dist;
		}

//DEADCODE CSB 06/03/00 	if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
	{
		FP dist = 0;
		if(MainPlaneList)
			dist = MainPlaneList->Pos[0][0].x;

		FP mass = ControlledAC->weap.centre.mass * 0.001;
		Mass += mass;
		mass = (ControlledAC->weap.left.mass + ControlledAC->weap.right.mass) * 0.001;
		Mass += mass;
		RotInertia.y += mass * dist * dist;
		RotInertia.z += mass * dist * dist;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Instruments
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calcs instrument settings
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Instruments (AirStrucPtr const ControlledAC)
{
	Inst.SetInstruments (ControlledAC,this);

	//rdh 30nov98
	if (Controlled)
	{
		SLong AltHome = 0;
		if(ControlledAC->ai.homebase)
			AltHome = ControlledAC->ai.homebase->World.Y;
		FP Altitude = (ControlledAC->World.Y - AltHome) * 0.032808;
		
//DeadCode RJS 5Oct00 		WeapAnimData*	weapon;
//DeadCode RJS 5Oct00 		SLong			xpos, ypos, zpos;							
//DeadCode RJS 5Oct00 		ULong			mvel;										
//DeadCode RJS 5Oct00 		UWord			index, mdelay, mburst;								
//DeadCode RJS 5Oct00 		int	totalammo = 0;
//DeadCode RJS 5Oct00 		for(index = 0; index < 6; index++)	
//DeadCode RJS 5Oct00 		{
//DeadCode RJS 5Oct00 			weapon = SHAPE.GetWeaponLauncher(ControlledAC,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET);
//DeadCode RJS 5Oct00 			if((weapon)	&& (weapon->LoadedStores > 0))
//DeadCode RJS 5Oct00 				totalammo += weapon->LoadedStores;						
//DeadCode RJS 5Oct00 			weapon = SHAPE.GetWeaponLauncher(ControlledAC,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_CANNON);
//DeadCode RJS 5Oct00 			if((weapon)	&& (weapon->LoadedStores > 0))
//DeadCode RJS 5Oct00 				totalammo += weapon->LoadedStores;						
//DeadCode RJS 5Oct00 		}											

		PolyPitAnimData*	ppadptr = (PolyPitAnimData*)ControlledAC->Anim;
		int		totalammo = ppadptr->actotalammoleft;

 		OverLay.SetInfoLineVals(10 * Speed, totalammo, Altitude, Inst.I_Heading, ControlledAC->fly.thrustpercent); 
		if (ControlledAC->ai.unfriendly)
		{
			ControlledAC->InterceptandRange (&ControlledAC->ai.unfriendly->World);
	 		SWord HI = (SWord) (ControlledAC->HdgIntercept - ControlledAC->hdg);
			HI = Rowan2Degs(HI);
		}
	}


#ifdef PRINTINSTRUMENTS
	PrintInstruments (this);

	PrintVar (0,9,"thrust lbf %.0f  ", EngineList->Thrust * 0.224769611);

#endif

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ACMInstruments
//Author		Craig Beeston
//Date			Wed 23 Feb 2000
//
//Description	Calcs instrument settings for basics only (needed by ACM)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ACMInstruments (AirStrucPtr const ControlledAC)
{
	Inst.I_TrueGroundSpeed = 0;
//DEADCODE CSB 23/02/00 	Inst.I_MachNo
	if(EngineList)
		Inst.I_EngineRpm0 = EngineList->Speed * 954.93;
	else
		Inst.I_EngineRpm0 = 0;

	if(EngineList->List.NextItem())
		Inst.I_EngineRpm1 = EngineList->List.NextItem()->Speed * 954.93;
	else
		Inst.I_EngineRpm1 = 0;

	Inst.I_NormalAcc = Acc.y / GRAVITY + Ori.y.y;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Ground_Collide_Sounds
//Author		Andrew McRae				CSB
//Date			Mon 27 Jan 1997				14/1/99
//
//Description	Ground Collision Interaction		//Checks for parts of aircraft touching ground and plays sounds
//				Not Undercarriage Suspension or Brakes
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Ground (AirStrucPtr const ControlledAC)
{
	Grid_Base* cornerAlt = (Grid_Base*)Grid_Base::gridfiles[Grid_Base::GF_CORNERALT].getdata();
	int Y = cornerAlt->getWorld(Pos.x, Pos.z);

	if(Pos.y > Y + FT_1000)
	{
		if(!(FrameCount & 0xff))
			GroundHeight = _Collide.GroundAltitude(ControlledAC->World);
		return;
	}

	Collide::Pos landed = _Collide.LANDED_OK;					//AMM 29Jun99
	//Tidied by Rob												//RJS 07May99
//DeadCode AMM 29Jun99 	landed = _Collide.HaveWeLanded (ControlledAC,grndpitch,grndroll);
	ANGLES Temp1, Temp2;										//AMM 29Jun99
	landed = _Collide.HaveWeLanded (ControlledAC, Temp1, Temp2);//AMM 29Jun99
	if(landed == _Collide.NOTTOUCHED)
	{
		if (SHAPESTUFF.GetShapePtr(ControlledAC->shape)->AnimDataSize == AIRCRAFTANIM)	//RJS 29Jun00
		{
			AircraftAnimData	*adptr = (AircraftAnimData*) ControlledAC->Anim;

			if ((ControlledAC == Persons2::PlayerSeenAC) && adptr->justlanded)	//RJS 30Aug00
				_Miles.StopSample(FIL_SFX_LANDING_GRASS_LOOP,ControlledAC);	//RJS 30Aug00

			adptr->hasdust = FALSE;
			adptr->justlanded = FALSE;
		}
	}
	else
	{
		if ((Manual_Pilot.ControlledAC2 == ControlledAC) && GearTouched)		//RJS 20May99
			_Miles.PlayLanded(ControlledAC, (int)(Speed * 100), GearSkid);		//fix this !!!!

		if (landed != _Collide.LANDED_OK)										//RJS 20May99
			Trans_Obj.LandedEffect(ControlledAC,landed);						//RJS 20May99
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeathSequenceOverride
//Author		Robert Slater
//Date			Tue 10 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::DeathSequenceOverride(int	newmovecode)
{
//DeadCode RJS 14Apr98 	Controlled = FALSE;
//
//	IsDead = TRUE;
//	ControlledAC->movecode = (AutoMoveCodeTypeSelect) newmovecode;
//	Manual_Pilot.controlmode=ManualPilot::PILOTDEAD;
}

void	Model::ProcessAeroPacket(AirStrucPtr const ControlledAC, UByte DeviceID, SWord Att)
{
	UByte		devcnt = 0;
	PAERODEVICE pAeroDevice = DeviceList;
	while (pAeroDevice != NULL)
	{
		if (devcnt == DeviceID)
		{
//DeadCode AMM 22Sep00 			if (pAeroDevice->OldAttractor)
//DeadCode AMM 22Sep00 				pAeroDevice->Attractor = 0x0000;
//DeadCode AMM 22Sep00 			else
//DeadCode AMM 22Sep00 				pAeroDevice->Attractor = 0x4000;

			pAeroDevice->OldAttractor=Att;
			pAeroDevice->Attractor=Att;

			pAeroDevice->Action (ControlledAC, AeroDevice::CT_AUTO,FALSE);
			break;
		}
		else
		{
			pAeroDevice = pAeroDevice->List.NextItem ();
			devcnt++;
		}
	}
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcStickForceFeedback
//Author		Craig Beeston
//Date			Thu 20 Aug 98
//
//Description	Calculates the Stiffness's, Forces and Sine Waves to be sent 
//				to Force Feedbank JoyStick Forces
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CalcStickForceFeedback()
{
	const int _Damping	= 0;
	const int _StiffX	= 1;
	const int _StiffZ	= 2;
	const int _WaveX	= 3;

	SWord WhatThisFrame = _Damping;
	WhatThisFrame = FrameCount & 0x03;
	
	switch(WhatThisFrame)
	{
		case _Damping:
		{
			FP damp = 1000;
//DeadCode AMM 21Feb100 			if(Save_Data.flightdifficulty[FD_FF_AERODYNAMIC])
			if(_Analogue.FF_aerodynamic)
			{
				damp = 0.5 * AmbDensity * AirSpeed * (FP)ControlForce * (100000.0 * 0.01) / FControlLoss;
				damp = (damp * _Analogue.FF_aerodynamic) / 5;
				MODLIMIT(damp, 10000);
//DEADCODE RDH 23/05/99 				PrintVar(40, 11, "Damping %.0f ", damp);
			}
			_Analogue.FFdamp.Set(damp, damp);
			break;
		}

		case _StiffX:
		{
			FP Stiffx = 5000;
//DeadCode AMM 21Feb100 			if(Save_Data.flightdifficulty[FD_FF_AERODYNAMIC])
			if(_Analogue.FF_aerodynamic)
			{
				Stiffx = 0.5 * AmbDensity * AirSpeed * (FP)ControlForce * (1000000.0 * 0.01) / FControlLoss;	//Aileron
				Stiffx = (Stiffx * _Analogue.FF_aerodynamic) / 5;
				MODLIMIT(Stiffx, 10000);
			}
			_Analogue.FFstiff.SetX(0, Stiffx);
//DeadCode CSB 25/05/99				PrintVar(0, 5, "Stiff X  %.0f ", Stiffx);
			break;
		}

		case _StiffZ:
		{
			FP Stiffz = 5000;
//DeadCode AMM 21Feb100 			if(Save_Data.flightdifficulty[FD_FF_AERODYNAMIC])
			if(_Analogue.FF_aerodynamic)
			{
				FP DynPress = 0.5 * AmbDensity * AirSpeed;
				PENGINE pEngine = EngineList;
				if(pEngine->Type == ET_PISTON)			//Prop Aircraft
					DynPress = 0.5 * AmbDensity * pEngine->SlipVel;// * pEngine->SlipVel;

				Stiffz = DynPress * (FP)ControlForce * (1000000.0 * 0.01) / FControlLoss;	//Elevator
				Stiffz = (Stiffz * _Analogue.FF_aerodynamic) / 5;
				MODLIMIT(Stiffz, 10000);
			}
			_Analogue.FFstiff.SetZ(0, Stiffz);
//DeadCode CSB 25/05/99				PrintVar(0, 6, "Stiff Z  %.0f ", Stiffz);
			break;
		}

		case _WaveX:
		{
			FP FwaveX = 0, MwaveX = 0; 
			Bool SetForce = FALSE;
			if((!Key_Tests.KeyHeld3d(SHOOT)) || (!_Analogue.FF_gun))
			{
				if(_Analogue.FF_airframe)
				{
					if(GearTouched)
					{
						FwaveX = Speed;
						MwaveX = Speed * 100.0;
						MwaveX = (MwaveX * _Analogue.FF_airframe) / 5;
						MODMAXMIN(MwaveX, 0, 10000);
						SetForce = TRUE;
					}
//DeadCode CSB 17Aug00 					if(!GearTouched)
//DeadCode CSB 17Aug00 						for(PAERODEVICE pDevice = DeviceList; pDevice; pDevice = pDevice->List.NextItem())
//DeadCode CSB 17Aug00 							if(pDevice->Val != pDevice->Attractor)
//DeadCode CSB 17Aug00 							{
//DeadCode CSB 17Aug00 								FwaveX = 20;
//DeadCode CSB 17Aug00 								MwaveX = (5000 * _Analogue.FF_airframe) / 5;
//DeadCode CSB 17Aug00 								MODMAXMIN(MwaveX, 0, 10000);
//DeadCode CSB 17Aug00 								SetForce = TRUE;
//DeadCode CSB 17Aug00 							}
				}
				if((_Analogue.FF_buffet) && (!SetForce))
				{
//DeadCode CSB 27Oct00 					if(TotalBuffet > 0)
					{
						FwaveX = 10;
						MwaveX = 2500.0 * TotalBuffet * 0.01 * (FP)BuffetForce;
						MwaveX = (MwaveX * _Analogue.FF_buffet) / 5;
						SetForce = TRUE;
					}
				}
				if(SetForce)
				{
					MODLIMIT(MwaveX, 10000);
					_Analogue.FFshake.SetX(MwaveX, FwaveX, FALSE);
				}
				break;
			}
		}

/*		case _WaveZ:
		{
			if(!Save_Data.flightdifficulty[FD_FF_AIRFRAME])
				break;
			
			PENGINE pEngine = EngineList;
			if(pEngine->Type != ET_PISTON)			//Prop Aircraft
				break;

			FP FwaveZ = 0, MwaveZ = 0; 
			FwaveZ = pEngine->Speed * 16;								//Engine Frequency
			MwaveZ = (pEngine->Power + 4000) * 1 * 0.01 * BuffetForce;

			MODLIMIT(MwaveZ, 32767);
			_Analogue.FFshake.SetZ(MwaveZ, FwaveZ, FALSE);
			break;
		}

		case _ForceY:
		case _StiffY:
		case _WaveY:
			break;
*/
		break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGunOri
//Author		Robert Slater
//Date			Mon 13 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::SetGunOri(Float	vx, Float vy, Float vz)
{
	subGunSet = true;

	subGun_x = vx;
	subGun_y = vy;
	subGun_z = vz;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGunOri
//Author		Robert Slater
//Date			Mon 13 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	Model::GetGunOri(Float&	vx, Float& vy, Float& vz)
{
	vx=subGun_x;
	vy=subGun_y;
	vz=subGun_z;

	return subGunSet;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcLauncherVel
//Author		R. Hyde 
//Date			Mon 30 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::CalcLauncherVel(SLong mvel, SLong &vx, SLong &vy, SLong &vz, SLong gunposx, SLong gunposy, SLong gunposz)
{
	SLong wx, wy, wz;													//RJS 26Sep00

#define BULLETSCONVERGE
#ifdef  BULLETSCONVERGE
	if(		gunposx														//RJS 21Aug00
		&& (this == Persons2::PlayerSeenAC->fly.pModel)					//RJS 21Aug00
		&&	!SHAPE.UsingRearGunner()	)	//RJS 21Aug00
	{
		const Float CONVERGENCE = 22500;	//250 yards		45000;	//500 yards
		FP velx = FP(mvel) * ((Pos.x + CONVERGENCE * Ori.z.x + 100.0 * Ori.y.x) - FP(gunposx)) / CONVERGENCE + 10000.0 * Vel.x;
		FP vely = FP(mvel) * ((Pos.y + CONVERGENCE * Ori.z.y + 100.0 * Ori.y.y) - FP(gunposy)) / CONVERGENCE + 10000.0 * Vel.y;
		FP velz = FP(mvel) * ((Pos.z + CONVERGENCE * Ori.z.z + 100.0 * Ori.y.z) - FP(gunposz)) / CONVERGENCE + 10000.0 * Vel.z;

		fastMath.FloatToInt(&vx,float(velx));							//RJS 26Sep00
		fastMath.FloatToInt(&vy,float(vely));							//RJS 26Sep00
		fastMath.FloatToInt(&vz,float(velz));							//RJS 26Sep00

		MissManCampSky().GetWind(Pos.y, wx, wy, wz);

		vx += wx;														//RJS 26Sep00
		vy += wy;														//RJS 26Sep00
		vz += wz;														//RJS 26Sep00

		return;
	}
#endif
	
	float	muzvel = float(mvel)*0.0001;//10000);		//to ms
	float	vvx;
	float	vvy;
	float	vvz;

	if (subGunSet)
	{
// Get gun unit-vector
		float	fx = subGun_x;
		float	fy = subGun_y;
		float	fz = subGun_z;

// Transform by ac ori
		vvx = (GunOri.x.x * fx)+(GunOri.y.x * fy)+(GunOri.z.x * fz);
		vvy = (GunOri.x.y * fx)+(GunOri.y.y * fy)+(GunOri.z.y * fz);
		vvz = (GunOri.x.z * fx)+(GunOri.y.z * fy)+(GunOri.z.z * fz);

		float	rmag = fastMath.FastInvSqrt(vvx*vvx+vvy*vvy+vvz*vvz);
		vvx *= rmag;
		vvy *= rmag;
		vvz *= rmag;

		subGunSet = false;
	}
	else
	{
		vvx = GunOri.z.x;
		vvy = GunOri.z.y;
		vvz = GunOri.z.z;
	}

	vvx *= muzvel;
	vvy *= muzvel;
	vvz *= muzvel;

 	vvx += GunVel.x;
 	vvy += GunVel.y;
 	vvz += GunVel.z;

	vvx *= 10000.0;
	vvy *= 10000.0;
	vvz *= 10000.0;

	// Velocity
	fastMath.FloatToInt(&vx,vvx);										//RJS 26Sep00
	fastMath.FloatToInt(&vy,vvy);										//RJS 26Sep00
	fastMath.FloatToInt(&vz,vvz);										//RJS 26Sep00

	MissManCampSky().GetWind(Pos.y, wx, wy, wz);

	vx += wx;														//RJS 26Sep00
	vy += wy;														//RJS 26Sep00
	vz += wz;														//RJS 26Sep00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BackupForGunsight
//Author		Robert Slater
//Date			Fri 25 Jun 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::BackupForGunsight()
{
	BakRotVel = AveRotVel;
	BakOri = Ori;
}
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcGunsightPos
//Author		Craig Beeston
//Date			Thu 03 Jun 1999
//
//Description	Calculates the position of the gunsight for a GYROSCOPIC LEAD COMPUTING OPTICAL SIGHT
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::CalcGunsightPos(SLong range, SWord gunvel, SLong& dx, SLong& dy, SLong& dz)
{
	if(fixgunsight)
	{
		FP VerticalOffset = 0;//679;	//3 deg 53 mins
		FCRD delta;
		delta.x = 10000 * BakOri.z.x;							//AMM 25Jun99
		delta.y = 10000 * BakOri.z.y - VerticalOffset * BakOri.y.y;//AMM 25Jun99
		delta.z = 10000 * BakOri.z.z;							//AMM 25Jun99

		dx = (SLong)delta.x;
		dy = (SLong)delta.y;
		dz = (SLong)delta.z;

		return;
	}

	FP fgunvel = FP(gunvel * 0.1);
	FP frange  = FP(range * 0.01);
	FP ftime   = frange / fgunvel;
	FCRD sightoffset;

	FCRD gBulletVel;
	gBulletVel.x = fgunvel * BakOri.z.x;						//AMM 25Jun99
	gBulletVel.y = fgunvel * BakOri.z.y;						//AMM 25Jun99
	gBulletVel.z = fgunvel * BakOri.z.z;						//AMM 25Jun99

	sightoffset.x = gBulletVel.x * ftime;
	sightoffset.y = gBulletVel.y * ftime;
	sightoffset.z = gBulletVel.z * ftime;

	FCRD gRotVel;
	TnsPnt(BakRotVel, gRotVel, BakOri);							//AMM 25Jun99
	gRotVel.x *= 100.0;
	gRotVel.y *= 100.0;
	gRotVel.z *= 100.0;

	FCRD targvel;
	CPrd(targvel, sightoffset, gRotVel);
	
	sightoffset.x -= targvel.x * ftime;
	sightoffset.y -= targvel.y * ftime;
	sightoffset.z -= targvel.z * ftime;

	sightoffset.y -= 0.5 * 9.8065 * ftime * ftime;

	sightoffset.x *= 100.0;										//DAW 28Jun99
	sightoffset.y *= 100.0;										//DAW 28Jun99
	sightoffset.z *= 100.0;										//DAW 28Jun99
																//DAW 28Jun99
	dx = SLong(sightoffset.x);									//DAW 28Jun99
	dy = SLong(sightoffset.y);									//DAW 28Jun99
	dz = SLong(sightoffset.z);									//DAW 28Jun99
}


void	Model::CalcLauncherPos(SLong&	posx, SLong& posy, SLong& posz)
{
	if (_Replay.Playback)
	{
		Ori.x.x = 1;
		Ori.x.y = 0;
		Ori.x.z = 0;
		Ori.y.x = 0;
		Ori.y.y = 1;
		Ori.y.z = 0;
		Ori.z.x = 0;
		Ori.z.y = 0;
		Ori.z.z = 1;

		SetOri (Ori, Rowan2Rads(replay_pitch), Rowan2Rads(replay_hdg), Rowan2Rads(replay_roll));
	}

	Float	posx2, posy2, posz2;
  	Float	fx, fy, fz;

	fx = Float(posx);
	fy = Float(posy);
	fz = Float(posz);

	posx2 = (Ori.x.x * fx);
	posx2 += (Ori.y.x * fy);
	posx2 += (Ori.z.x * fz);

	posy2 = (Ori.x.y * fx);
	posy2 += (Ori.y.y * fy);
	posy2 += (Ori.z.y * fz);

	posz2 = (Ori.x.z * fx);
	posz2 += (Ori.y.z * fy);
	posz2 += (Ori.z.z * fz);

	posx = SLong(posx2);
	posy = SLong(posy2);
	posz = SLong(posz2);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RememberForGunSight
//Author		R. Hyde 
//Date			Mon 30 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::RememberForGunSight(bool fixsight, AirStrucPtr	ac)
{
	if (ac->classtype->aerobaticfactor == AEROBATIC_LOW)
	{
		GunOri.x.x = 1;
		GunOri.x.y = 0;
		GunOri.x.z = 0;
		GunOri.y.x = 0;
		GunOri.y.y = 1;
		GunOri.y.z = 0;
		GunOri.z.x = 0;
		GunOri.z.y = 0;
		GunOri.z.z = 1;

		SetOri (GunOri, Rowan2Rads(ac->pitch), -Rowan2Rads(ac->hdg), Rowan2Rads(ac->roll));

		GunVel.x = 0.0001 * Float(ac->vel_x);
		GunVel.y = 0.0001 * Float(ac->vel_y);
		GunVel.z = 0.0001 * Float(ac->vel_z);
	}
	else
	{
		GunOri = Ori;
		GunVel = Vel;
	}

	fixgunsight = fixsight;										//CSB 09Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPlayerMoving
//Author		Craig Beeston 
//Date			Thu 11 Feb 1999
//
//Description	Checks the players speed and uses it to set flag to allow flight to take off
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::SetPlayerMoving(AirStrucPtr const ControlledAC)
{
//DEADCODE CSB 04/05/00 	static Bool WindUp = FALSE;
//DEADCODE CSB 04/05/00 	static Bool Wait   = FALSE;
//DEADCODE CSB 04/05/00 	if(AirStruc::playermoving) return;
//DEADCODE CSB 04/05/00 	
//DEADCODE CSB 04/05/00 	if(ControlledAC->fly.thrustpercent > 75)
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		if(!WindUp)
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			WindUp = TRUE;
//DEADCODE CSB 04/05/00 			if(ControlledAC->Follower())
//DEADCODE CSB 04/05/00 				_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_RUNUP0, MSG_TAKEOFFRUNUP, ControlledAC, NULL, ControlledAC->Follower()));
//DEADCODE CSB 04/05/00 			else
//DEADCODE CSB 04/05/00 				_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_RUNUP0, MSG_TAKEOFFRUNUP, ControlledAC->Leader(), NULL, ControlledAC));
//DEADCODE CSB 04/05/00 		}
//DEADCODE CSB 04/05/00 		if( (Speed > 1) && (!LeftWheelBrake) && (!RightWheelBrake))
//DEADCODE CSB 04/05/00  		{
//DEADCODE CSB 04/05/00 			if (_DPlay.Implemented || _Replay.Record)			//AMM 22Jun99
//DEADCODE CSB 04/05/00 			{													//AMM 22Jun99
//DEADCODE CSB 04/05/00 				_DPlay.NewPlayerMoving();					//AMM 22Jun99
//DEADCODE CSB 04/05/00 			}													//AMM 22Jun99
//DEADCODE CSB 04/05/00 			else												//AMM 22Jun99
//DEADCODE CSB 04/05/00 				AirStruc::playermoving = true;
//DEADCODE CSB 04/05/00 			if(ControlledAC->Follower())
//DEADCODE CSB 04/05/00 				_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_ROLLING, MSG_TAKEOFFROLLING, ControlledAC, NULL, ControlledAC->Follower()));
//DEADCODE CSB 04/05/00 			else
//DEADCODE CSB 04/05/00 				_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_ROLLING, MSG_TAKEOFFROLLING, ControlledAC->Leader(), NULL, ControlledAC));
//DEADCODE CSB 04/05/00 		}
//DEADCODE CSB 04/05/00 	}
//DEADCODE CSB 04/05/00 	
//DEADCODE CSB 04/05/00 	if(!Wait)
//DEADCODE CSB 04/05/00 		if((!LeftWheelBrake) && (!RightWheelBrake) && (ControlledAC->fly.thrustpercent < 75))
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			Wait = TRUE;
//DEADCODE CSB 04/05/00 			_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_WAITFOR, MSG_TAKEOFFBRAKEMSG, ControlledAC->FindBuddy(), NULL, ControlledAC));
//DEADCODE CSB 04/05/00 		}
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 	if((ControlledAC->vel_ > 100000) && (!AirStruc::playermoving))	//jim 01Jul99
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		if (_DPlay.Implemented || _Replay.Record)				//AMM 22Jun99
//DEADCODE CSB 04/05/00 		{														//AMM 22Jun99
//DEADCODE CSB 04/05/00 			_DPlay.NewPlayerMoving();						//AMM 22Jun99
//DEADCODE CSB 04/05/00 		}														//AMM 22Jun99
//DEADCODE CSB 04/05/00 		else													//AMM 22Jun99
//DEADCODE CSB 04/05/00 			AirStruc::playermoving = true;
//DEADCODE CSB 04/05/00 		if(ControlledAC == ControlledAC->Leader())
//DEADCODE CSB 04/05/00 			_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_ROLLING, MSG_TAKEOFFROLLING, ControlledAC, NULL, ControlledAC->Follower()));
//DEADCODE CSB 04/05/00 		else
//DEADCODE CSB 04/05/00 			_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_ROLLING, MSG_TAKEOFFROLLING, ControlledAC->Leader(), NULL, ControlledAC));
//DEADCODE CSB 04/05/00 	}
}

///////////////////////////////////////////////////////////////////////////////	

#ifdef DISPLAY_MONO_DATA

void PrintModelData (AirStrucPtr const ControlledAC,Model* mod, ULong x, ULong y)
{

	Bool Pos		 = FALSE;
	Bool Instruments = FALSE;//TRUE;//
	Bool Interactive = FALSE;//TRUE;//
	Bool Engine		 = FALSE;//TRUE;//
	Bool Controls	 = FALSE;//TRUE;//
	Bool Aoas		 = FALSE;
	Bool Atmosphere	 = FALSE;//TRUE;//
	Bool Mass		 = FALSE;//TRUE;
	Bool Anims		 = FALSE;
	Bool Gear		 = FALSE;//TRUE;//
	Bool Acm		 = FALSE;
	Bool AnglesForces= FALSE;//TRUE;//
	Bool Fin		 = FALSE;//TRUE;//	//CSB 07/05/99	
	Bool Tune		 = FALSE;//TRUE;//	//CSB 13/05/99	

	ULong n;


	if (Pos)
	{
		y++;
		// POSITION

		PrintVar(x, y++, "X: %.0f  ", (FP)mod->Pos.x);
		PrintVar(x, y++, "Z: %.0f  ", (FP)mod->Pos.z);
	}


	if (Instruments)
	{
//		y++;
		PrintVar(x, y++, "I_TrueGroundSpeed        %.0f  ", FP(mod->Inst.I_TrueGroundSpeed));
		PrintVar(x, y++, "I_TrueAirSpeed           %.0f  ", FP(mod->Inst.I_TrueAirSpeed));
		PrintVar(x, y++, "I_IndicatedAirSpeed      %.0f  ", FP(mod->Inst.I_IndicatedAirSpeed));
		PrintVar(x, y++, "I_MachNo                 %.2f  ", FP(mod->Inst.I_MachNo));
		PrintVar(x, y++, "I_PitchAngle             %.1f  ", FP(mod->Inst.I_PitchAngle));
		PrintVar(x, y++, "I_RollAngle              %.1f  ", FP(mod->Inst.I_RollAngle));
		PrintVar(x, y++, "I_Heading                %.0f  ", FP(mod->Inst.I_Heading));
		PrintVar(x, y++, "I_RateOfClimb            %.0f  ", FP(mod->Inst.I_RateOfClimb));
		PrintVar(x, y++, "I_Altitude               %.0f  ", FP(mod->Inst.I_Altitude));
		PrintVar(x, y++, "I_RadioAltitude          %.0f  ", FP(mod->Inst.I_RadioAltitude));
		PrintVar(x, y++, "I_Turn                   %.1f  ", FP(mod->Inst.I_Turn));
		PrintVar(x, y++, "I_Slip                   %.1f  ", FP(mod->Inst.I_Slip));
		PrintVar(x, y++, "I_UndercarraigePosition0 %.0f  ", FP(mod->Inst.I_UndercarraigePosition0));
		PrintVar(x, y++, "I_UndercarraigePosition1 %.0f  ", FP(mod->Inst.I_UndercarraigePosition1));
		PrintVar(x, y++, "I_MechanicalUndercgeIndi %.0f  ", FP(mod->Inst.I_MechanicalUndercarraigeIndicator));
		PrintVar(x, y++, "I_ElevatorTrimTab        %.0f  ", FP(mod->Inst.I_ElevatorTrimTab));
		PrintVar(x, y++, "I_FuelContents           %.0f  ", FP(mod->Inst.I_FuelContents));
		PrintVar(x, y++, "I_FuelWarningLamp0       %.0f  ", FP(mod->Inst.I_FuelWarningLamp0));
		PrintVar(x, y++, "I_FuelWarningLamp1       %.0f  ", FP(mod->Inst.I_FuelWarningLamp1));
		PrintVar(x, y++, "I_FuelWarningLamp2       %.0f  ", FP(mod->Inst.I_FuelWarningLamp2));
		PrintVar(x, y++, "I_FuelWarningLamp3       %.0f  ", FP(mod->Inst.I_FuelWarningLamp3));
		PrintVar(x, y++, "I_FuelPressure           %.0f  ", FP(mod->Inst.I_FuelPressure));
		PrintVar(x, y++, "I_OilContent             %.0f  ", FP(mod->Inst.I_OilContent));
		PrintVar(x, y++, "I_OilPressure            %.0f  ", FP(mod->Inst.I_OilPressure));
		PrintVar(x, y++, "I_OilTemperature         %.1f  ", FP(mod->Inst.I_OilTemperature));

		x = 40;
		y = -1;

		PrintVar(x, y++, "I_RadiatorTemperature0   %.1f  ", FP(mod->Inst.I_RadiatorTemperature0));
		PrintVar(x, y++, "I_Boost0                 %.2f  ", FP(mod->Inst.I_Boost0));
		PrintVar(x, y++, "I_EngineRpm0             %.0f  ", FP(mod->Inst.I_EngineRpm0));
		PrintVar(x, y++, "I_VoltMeter              %.0f  ", FP(mod->Inst.I_VoltMeter));
		PrintVar(x, y++, "I_PropPitch0             %.0f  ", FP(mod->Inst.I_PropPitch0));
		PrintVar(x, y++, "I_FlapsIndicator         %.0f  ", FP(mod->Inst.I_FlapsIndicator));
		PrintVar(x, y++, "I_NormalAcc              %.2f  ", FP(mod->Inst.I_NormalAcc));
	}

	if(Interactive)
	{
		y++;
		PrintVar(x, y++, "C_FlapLever              %.0f  ", FP(mod->Inst.C_FlapLever));
		PrintVar(x, y++, "C_UndercarraigeLever     %.0f  ", FP(mod->Inst.C_UndercarraigeLever));
		PrintVar(x, y++, "C_H_Gate                 %.0f  ", FP(mod->Inst.C_H_Gate));
		PrintVar(x, y++, "C_EmergencyUndercarraige %.0f  ", FP(mod->Inst.C_EmergencyUndercarraige));
		PrintVar(x, y++, "C_DiveBrakeLever         %.0f  ", FP(mod->Inst.C_DiveBrakeLever));
		PrintVar(x, y++, "C_ElevatorTrim           %.0f  ", FP(mod->Inst.C_ElevatorTrim));
		PrintVar(x, y++, "C_RudderTrim             %.0f  ", FP(mod->Inst.C_RudderTrim));
		PrintVar(x, y++, "C_Throttle0              %.0f  ", FP(mod->Inst.C_Throttle0));
		PrintVar(x, y++, "C_PropPitch0             %.0f  ", FP(mod->Inst.C_PropPitch0));
		PrintVar(x, y++, "C_Magnetos0              %.0f  ", FP(mod->Inst.C_Magnetos0));
		PrintVar(x, y++, "C_PrimerPump0            %.0f  ", FP(mod->Inst.C_PrimerPump0));
		PrintVar(x, y++, "C_FuelCock0              %.0f  ", FP(mod->Inst.C_FuelCock0));
		PrintVar(x, y++, "C_StarterButton0         %.0f  ", FP(mod->Inst.C_StarterButton0));
		PrintVar(x, y++, "C_BoostControlCutout     %.0f  ", FP(mod->Inst.C_BoostControlCutout));
		PrintVar(x, y++, "C_HoodCatch              %.0f  ", FP(mod->Inst.C_HoodCatch));
		PrintVar(x, y++, "C_FuelGuageSelector      %.0f  ", FP(mod->Inst.C_FuelGuageSelector));
	}

/*
	if (Engine)
	{

		y++;

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "Rpm1 %.0f ",mod->Inst.Rpm1);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "Thrust (lbf) %.0f ",mod->EngineList->Thrust * 0.224769611);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		if (mod->EngineList->Type == ET_PISTON)
		{

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "bhp %.0f ",mod->EngineList->Power);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

//			for (n=0; n<32; n++) strg[n] = 0;
//			sprintf (strg, "p100 %.0f ",mod->EngineList->Power100);
//			if (strg[31] == 0)
//				Mono_Text.PrintAt (x,y++,(UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "p0 %.0f ",mod->EngineList->Power0);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "PropInc %.2f ",mod->EngineList->PropInc);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "Swirl %.2f ",mod->EngineList->SlipRot * 100);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

			for (n=0; n<32; n++) strg[n] = 0;
			sprintf (strg, "Slipstream %.2f ",mod->EngineList->SlipVel);
			if (strg[31] == 0)
				Mono_Text.PrintAt (x,y++,(UByte*)strg);

//			for (n=0; n<32; n++) strg[n] = 0;
//			sprintf (strg, "eff %.2f ",mod->EngineList->eff);
//			if (strg[31] == 0)
//				Mono_Text.PrintAt (x,y++,(UByte*)strg);

		}

	}	


	if (Controls)
	{
//		y++;

		// CONTROLS
	
		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "Aileron  %d    ",ControlledAC->fly.aileron);
		sprintf (strg, "Aileron  %d    ",mod->Aileron);
//		sprintf (strg, "Aileron  %d    ",ControlledAC->fly.pAcmModel->CtrlAileron);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "Elevator  %d    ",ControlledAC->fly.elevator);
		sprintf (strg, "Elevator  %d    ",mod->Elevator - mod->ElevatorTrim);
//		sprintf (strg, "Elevator  %d    ",ControlledAC->fly.pAcmModel->CtrlElevator);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "ElevTrim  %d    ",mod->ElevatorTrim);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
//		sprintf (strg, "Rudder  %d    ",ControlledAC->fly.rudder);
		sprintf (strg, "Rudder  %d    ",mod->Rudder);
//		sprintf (strg, "Rudder  %d    ",ControlledAC->fly.pAcmModel->CtrlRudder);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
		sprintf (strg, "Throttle  %d  ",ControlledAC->fly.thrustpercent);
		if (strg[31] == 0)
			Mono_Text.PrintAt (x,y++,(UByte*)strg);

		
		

	}

	if (Atmosphere)
	{

		y++;

		// ATMOSPHERE

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "kg/m^2  %.3f  ", mod->AmbDensity*10000);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "Celcius %.0f  ", mod->AmbTemp-273.15);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (x,y++,(UByte*)strg);

		for (n=0; n<32; n++) strg[n] = 0;
 		sprintf (strg, "mBars   %.0f  ", mod->AmbPres*100);
		if (strg[31] == 0)
	 		Mono_Text.PrintAt (x,y++,(UByte*)strg);

//		if (MMC.Sky.GUSTS)
//		{
//			PrintString (x,y++,"GUSTS");
//			if (MMC.Sky.Gust.ACTIVE)
//			{
//				PrintVar (x, y++, "time %ld     ", MMC.Sky.Gust.Time);
//				PrintVar (x, y++, "g.x %ld     ", MMC.Sky.Gust.Vec.x);
//				PrintVar (x, y++, "g.y %ld     ", MMC.Sky.Gust.Vec.y);
//				PrintVar (x, y++, "g.z %ld     ", MMC.Sky.Gust.Vec.z);
//			}
//		}
//		else
//			PrintString (x,y++,"NO GUSTS");

	}

	if (Mass)
	{

		y++;

		PrintVar (x,y++, "Mass (Kg) %.3f", mod->Mass / 100);
		PrintVar (x,y++, "Ixx (Slug.ft^2) %.0f ", mod->RotInertia.x / 1355827);
		PrintVar (x,y++, "Iyy (Slug.ft^2) %.0f ", mod->RotInertia.y / 1355827);
		PrintVar (x,y++, "Izz (Slug.ft^2) %.0f ", mod->RotInertia.z / 1355827);
//		PrintVar (x,y++, "Cg.x (cm) %.2f", mod->CGPos.x);
//		PrintVar (x,y++, "Cg.y (cm) %.2f", mod->CGPos.y);
//		PrintVar (x,y++, "Cg.z (cm) %.2f", mod->CGPos.z);
	}

	if (Anims)
	{

		y++;

		PMODELANIM pAnim = mod->AnimList;

		while (pAnim != NULL)
		{
			PrintVar (x, y++, "%d   ", *(UByte*)(pAnim->pAnim));
			pAnim = pAnim->List.NextItem ();
		}
	}
*/
	if (Gear)
	{
		PrintVar( 0, 3, "Vel.Z %.2f ", FP(-mod->AirVel.z));
		PrintVar( 0, 4, "Vel.X %.2f ", FP(-mod->AirVel.x));
		PrintVar( 0, 5, "Roll  %.4f ", FP(mod->fRoll * 57.3));
		PrintVar( 0, 6, "Pitch %.4f ", FP(mod->fPitch * 57.3));

		PGEAR pGear = mod->GearList;

		while (pGear != NULL)
		{
			FCRD GlobForce;
			TnsPnt(pGear->TyreForce, GlobForce, mod->Ori);

			switch(pGear->Ident)
			{
				case NOSE:
				{
					PrintVar(30,  5, "LegPos  %.4f ", FP(pGear->LegPos));
					PrintVar(30,  6, "Force.X %.0f ", FP(GlobForce.x));
					PrintVar(30,  7, "Force.Y %.0f ", FP(GlobForce.y));
					PrintVar(30,  8, "Force.Z %.0f ", FP(GlobForce.z));
					break;
				}
				case PORT:
				{
					PrintVar( 0, 10, "LegPos  %.4f ", FP(pGear->LegPos));
					PrintVar( 0, 11, "Force.X %.0f ", FP(GlobForce.x));
					PrintVar( 0, 12, "Force.Y %.0f ", FP(GlobForce.y));
					PrintVar( 0, 13, "Force.Z %.0f ", FP(GlobForce.z));
					break;
				}
				case STBD:
				{
					PrintVar(60, 10, "LegPos  %.4f ", FP(pGear->LegPos));
					PrintVar(60, 11, "Force.X %.0f ", FP(GlobForce.x));
					PrintVar(60, 12, "Force.Y %.0f ", FP(GlobForce.y));
					PrintVar(60, 13, "Force.Z %.0f ", FP(GlobForce.z));
					break;
				}
				case TAIL:
				{
					PrintVar(30, 15, "LegPos  %.4f ", FP(pGear->LegPos));
					PrintVar(30, 16, "Force.X %.0f ", FP(GlobForce.x));
					PrintVar(30, 17, "Force.Y %.0f ", FP(GlobForce.y));
					PrintVar(30, 18, "Force.Z %.0f ", FP(GlobForce.z));
					break;
				}
			}
			pGear = pGear->List.NextItem ();
		}
	}
//DeadCode PD 13Nov97 #undef VOID


	if (Acm && !mod->Controlled)
	{
		y++;
		PrintVar (x,y++, "ACM  %.8x   ", (ULong)ControlledAC->ai.manoeuvre);
		PrintVar (x,y++, "Phase %ld   ", ControlledAC->ai.ManStep);
	}	

//*****************************************************************************	
	if( (AnglesForces) && (!mod->bACM) )	//CSB 07/12/98
	{
		x = 35;
		y = 0;

//Conditions
		PrintVar(x+0 , y, "Alt: %.2f ", (FP)mod->Pos.y / 100);
		PrintVar(x+13, y, "Rho: %.3f ", (FP)mod->AmbDensity * 10000);
		PrintVar(x+25, y, "IAS: %.1f ", (FP)mod->Inst.I_IndicatedAirSpeed);

		PrintVar(x+33, y, "M: %.2f ", (FP)(mod->Mass * 0.01));
//Controls
		y++;
		PrintVar(x+0, y++, "Ail: %.0f ", (FP)mod->Aileron);
		PrintVar(x+0, y++, "Ele: %.0f ", (FP)mod->Elevator);
		PrintVar(x+0, y++, "Rud: %.0f ", (FP)mod->Rudder);

//Gusts
//DeadCode CSB 30/04/99			x = 50;
//DeadCode CSB 30/04/99			y = 1;
//DeadCode CSB 30/04/99	
//DeadCode CSB 30/04/99			PrintVar(x+0, y++, "Gust.x: %.2f ", (FP)mod->Gust.Vec.x);
//DeadCode CSB 30/04/99			PrintVar(x+0, y++, "Gust.y: %.2f ", (FP)mod->Gust.Vec.y);
//DeadCode CSB 30/04/99			PrintVar(x+0, y++, "Gust.z: %.2f ", (FP)mod->Gust.Vec.z);

//Angles
		x = 50;
		y = 1;

		PrintVar(x+0, y++, "Pitch: %.2f ", (FP)(mod->fPitch * 57.3));
		PrintVar(x+0, y++, "Hdg:   %.2f ", (FP)(mod->fHdg * 57.3));
		PrintVar(x+0, y++, "Roll   %.2f ", (FP)(mod->fRoll * 57.3));

		
//Velocities
		x = 0;
		y = 0;

		PrintVar(0 , y, "V :x %.1f ", (FP)-mod->AirVel.x);
		PrintVar(12, y, "V :y %.1f ", (FP)-mod->AirVel.y);
		PrintVar(20, y, "V :z %.1f ", (FP)-mod->AirVel.z);

//Acceleration
		y++;
 		PrintVar(0 , y, "A :x %.1f ", FP(100*mod->Acc.x));
 		PrintVar(12 , y,   "y %.1f ", FP(100*mod->Acc.y));
 		PrintVar(20 , y,   "z %.1f ", FP(100*mod->Acc.z));

//Rotational Velocities
		y++;
		PrintVar(0 , y, "RV:x %.2f ", FP(100*mod->RotVel.x));
 		PrintVar(12, y,    "y %.2f ", FP(100*mod->RotVel.y));
		PrintVar(20 ,y,    "z %.2f ", FP(100*mod->RotVel.z));

//Rotational Acceleration
		y++;
		PrintVar(0 , y, "RA:x %.2f ", FP(10000*mod->RotAcc.x));
		PrintVar(12, y,    "y %.2f ", FP(10000*mod->RotAcc.y));
		PrintVar(20, y,    "z %.2f ", FP(10000*mod->RotAcc.z));

//Wings
		y++;
		SWord yy = 0;

		PMAINPLANE pMainPlane = mod->MainPlaneList;
		while (pMainPlane != NULL)
		{
			y++;

			for(SWord wing = 0; wing < 2; wing++)
				for(SWord section = 0; section < 2; section++)
				{
//DEADCODE CSB 31/01/00 					x = 39 + (40 * pMainPlane->Pos[wing][section].x) / 500 - 5;
					x = 15 + 35 * (1 - wing) + 15 * section * (1 - 2 * wing);
					yy = y;

					PrintVar(x , yy++, "W Aa: %.2f ", FP(180/FPIE * pMainPlane->aoa[wing][section]));
					PrintVar(x , yy++, "W Fx: %.0f ", FP(pMainPlane->eForce[wing][section].x));
					PrintVar(x , yy++, "W Fy: %.0f ", FP(pMainPlane->eForce[wing][section].y));
					PrintVar(x , yy++, "W Fz: %.0f ", FP(pMainPlane->eForce[wing][section].z));
					PrintVar(x , yy++, "W Mx: %.0f ", FP(pMainPlane->eMoment[wing][section].x));
					PrintVar(x , yy++, "W My: %.0f ", FP(pMainPlane->eMoment[wing][section].y));
					PrintVar(x , yy++, "W Mz: %.0f ", FP(pMainPlane->eMoment[wing][section].z));
				}
			pMainPlane = pMainPlane->List.NextItem ();
			if(yy>20)
				FP BreakPoint0 = 0.0;
		}

		PrintVar(60, 15, "Buffet %.1f ", FP(mod->TotalBuffet));

		PrintVar(50, 13, "DownWash S %.1f ", FP(mod->MainPlaneList->DownWashAng[0] * 57.3));
		PrintVar(50, 14, "DownWash P %.1f ", FP(mod->MainPlaneList->DownWashAng[1] * 57.3));
		

		PCYLINDER Cylinder = mod->CylinderList;
		while (Cylinder != NULL)
		{
			x = 39 + (40 * Cylinder->Pos.x) / 500 - 5;
			y++;

			PrintVar(x, y++, "C Fx: %.0f ", FP(Cylinder->Force.x));
			PrintVar(x, y++, "C Fy: %.0f ", FP(Cylinder->Force.y));
			PrintVar(x, y++, "C Fz: %.0f ", FP(Cylinder->Force.z));

			Cylinder = Cylinder->List.NextItem ();
		}
	
		y++;
		y++;

		PSURFACE Surface = mod->SurfaceList;
		while (Surface != NULL)
		{
			x = 39 + (40 * Surface->Pos.x) / 150 - 5;
			yy = y;

			PrintVar(x, yy++, "S Fx: %.0f ", FP(Surface->Force.x));
			PrintVar(x, yy++, "S Fy: %.0f ", FP(Surface->Force.y));
			PrintVar(x, yy++, "S Fz: %.0f ", FP(Surface->Force.z));
	
			Surface = Surface->List.NextItem ();
		}

		y = yy;

		PTHRUSTPOINT ThrustPoint = mod->ThrustList;
		while (ThrustPoint != NULL)
		{
			x = 39 + (40 * ThrustPoint->Pos.x) / 500 - 5;
			y = 23;

			PrintVar(x, y, "T Fz: %.0f ", FP(ThrustPoint->Force.z));
			PrintVar(x, y+1, "E Rpm: %.0f ", FP(ThrustPoint->pEngine->Speed * 954.9296586));

			ThrustPoint = ThrustPoint->List.NextItem ();
		}

		PGEAR Gear = mod->GearList;
		while(Gear != NULL)
		{
			switch(Gear->Ident)
			{
				case NOSE:
	 				PrintVar(10, 13, "G y: %.4f ", FP(Gear->LegPos));
	 				PrintVar(10, 14, "G F: %.0f ", FP(Gear->TyreForce.y));
					break;
				case PORT:
	 				PrintVar( 0, 15, "G y: %.4f ", FP(Gear->LegPos));
	 				PrintVar( 0, 16, "G F: %.0f ", FP(Gear->TyreForce.y));
					break;
				case STBD:
	 				PrintVar(20, 15, "G y: %.4f ", FP(Gear->LegPos));
	 				PrintVar(20, 16, "G F: %.0f ", FP(Gear->TyreForce.y));
					break;
				case TAIL:
	 				PrintVar(10, 17, "G y: %.4f ", FP(Gear->LegPos));
	 				PrintVar(10, 18, "G F: %.0f ", FP(Gear->TyreForce.y));
					break;
			}
			Gear = Gear->List.NextItem();
		}
	}
/*	
	if(Fin)
	{
		PSURFACE Surface = mod->SurfaceList;
		while (Surface != NULL)
		{
			if(Surface->Pos.x == 0)
			{
//DEADCODE RDH 30/06/99 				PrintVar(60, 15, "Aoa     %.2f ", FP(180/FPIE * AngleSign(Surface->aoa)) );
				PrintVar(60, 16, "Vel 0   %.2f ", FP(-mod->AirVel.z));
				PrintVar(60, 17, "Vel 1   %.2f ", FP(Surface->pSlipThrustPoint->pEngine->SlipVel));
				PrintVar(60, 18, "ForceX  %.0f ", FP(Surface->Force.x));
				PrintVar(60, 19, "ForceZ  %.0f ", FP(Surface->Force.z));
			}
			Surface = Surface->List.NextItem ();
		}
	}

	if(Tune)
	{
		FP d      = mod->AmbDensity * 10000;
		FP AltISA = 802729 * d*d*d*d*d*d - 3358891 * d*d*d*d*d + 5531629 * d*d*d*d - 4561006 * d*d*d + 2002783 * d*d - 508295 * d + 98238;
		PrintVar( 0,  5, "Alt     %.0f ", FP(mod->Pos.y / 100));
		PrintVar( 0,  6, "ROC     %.2f ", FP(mod->Vel.y));
		PrintVar( 0,  7, "Pitch   %.2f ", FP(-mod->Vel.y / mod->AirVel.z * 57.3));
		PrintVar( 0,  8, "Density %.3f ", FP(d));
		PrintVar( 0,  9, "Vel     %.2f ", FP(-mod->AirVel.z));
		PrintVar( 0, 10, "Accel   %.2f ", FP(100 * mod->Acc.z));
		PrintVar( 0, 11, "AltISA  %.0f ", FP(AltISA));
		PrintVar( 0, 13, "Elev    %.0f ", FP(mod->Elevator));
	}
*/
}

#endif

//DEADCODE CSB 01/12/99 #ifndef NO_MONO_DATA
//DEADCODE CSB 01/12/99 #define NO_MONO_DATA
//DEADCODE CSB 01/12/99 #endif

void PrintVar (ULong x, ULong y, char* text, ULong var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, SLong var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, FP var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, SWord var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, UWord var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, UByte var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintVar (ULong x, ULong y, char* text, SByte var)
{
#ifdef NO_MONO_DATA
	return;
#endif
	char strg [128];
	sprintf (strg, text, var);
	Mono_Text.PrintAt (x,y,(UByte*)strg);
}
void PrintString (ULong x, ULong y, char* text)
{
#ifdef NO_MONO_DATA
	return;
#endif
	Mono_Text.PrintAt (x,y,(UByte*)text);
}

void PrintHLine (ULong x, ULong y, ULong size, char* c)
{
#ifdef NO_MONO_DATA
	return;
#endif
	for (ULong p=x;p<x+size;p++) Mono_Text.PrintAt (p,y,(UByte*)c);
}
void PrintVLine (ULong x, ULong y, ULong size, char* c)
{
#ifdef NO_MONO_DATA
	return;
#endif
	for (ULong p=y;p<y+size;p++) Mono_Text.PrintAt (x,p,(UByte*)c);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcCanopyVel
//Author		Robert Slater
//Date			Tue 23 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::CalcParachuteVel(SLong &vvx,
								SLong &vvy,
								SLong &vvz,
								SWord thehdg,
								SWord thepitch,
								SWord theroll,
								SLong vel,
								SLong pushvel,
								SLong Alt)	//CSB 13/06/99	
{
	Float	vx;
	Float	vy;
	Float	vz;

	if ((!Controlled && !bACM) || _Replay.Playback)
	{
		Ori.x.x = 1;
		Ori.x.y = 0;
		Ori.x.z = 0;
		Ori.y.x = 0;
		Ori.y.y = 1;
		Ori.y.z = 0;
		Ori.z.x = 0;
		Ori.z.y = 0;
		Ori.z.z = 1;

		SetOri (Ori, Rowan2Rads(thepitch), Rowan2Rads(thehdg), Rowan2Rads(theroll));

		Vel.x = Float(vel) * Ori.z.x;
		Vel.y = Float(vel) * Ori.z.y;
		Vel.z = Float(vel) * Ori.z.z;

		SLong wx, wy, wz;					//CSB 13/06/99	
		MissManCampSky().GetWind(Alt, wx, wy, wz);	//CSB 13/06/99	
											//CSB 13/06/99	
		Vel.x += wx * 0.0001;					//CSB 13/06/99	
		Vel.y += wy * 0.0001;					//CSB 13/06/99	
		Vel.z += wz * 0.0001;					//CSB 13/06/99	
	}

	vx = Ori.y.x;
	vy = Ori.y.y;
	vz = Ori.y.z;

	vx *= Float(pushvel);				//RJS 10May99
	vy *= Float(pushvel);				//RJS 10May99
	vz *= Float(pushvel);				//RJS 10May99

	vx += Vel.x;
	vy += Vel.y;
	vz += Vel.z;

	vvx = SLong(vx*10000);
	vvy = SLong(vy*10000);
	vvz = SLong(vz*10000);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrashModelData
//Author		Craig Beeston
//Date			Tue 26 Oct 1999
//
//Description	Resets all the flight model variables to rubbish values.
//				This can be used to prove that record / replay is storing all necessary values.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::TrashModelData(AirStrucPtr const ControlledAC)
{
	FrameCount = 1;
	FirstCycle = TRUE;

	Spinning = TRUE;

	NullVec(Pos);

	NullOri(Ori);
	NullOri(GunOri);
	NullOri(BakOri);
	NullVec(BakRotVel);
																
	NullVec(Vel);
	NullVec(GunVel);
	Speed = 0;
	NullVec(CheatAcc);

	Gust.ACTIVE = TRUE;	
	Gust.Time   = 10000;
	NullVec(Gust.Vec);
//DEADCODE AMM 18/01/00 	GUST Gust;													//Zero

// for replay purposes when model is not maintained these values are used

	replay_roll  = ANGLES_180Deg;
	replay_pitch = ANGLES_180Deg;
	replay_hdg   = ANGLES_180Deg;

	// Aircraft Coords

	NullVec(RotVel);

	NullVec(AirVel);
//DEADCODE CSB 23/12/99 	NullVec(InstAirVel);
	AirSpeed = 0;
	DynamicPressure = 0;

	NullVec(Acc);
	NullVec(wAcc);
	NullVec(RotAcc);

	NullVec(NettForce);
	NullVec(NettMoment);

	NullVec(StoresForce);
	NullVec(StoresMoment);

	// Devices
	DeltaCl = 100;
	DeltaCd = 100;
	DeltaCm = 100;
	DeltaAlpha = 100;

	GearTouched = TRUE;
	GearSkid = TRUE;
	RestartEngine = TRUE;
	GroundHeight = 65535;

	Mass = 0;
	NullVec(RotInertia);

	NullVec(InertiaMoment);

	fHdg   = 0;
	fPitch = 0;
	fRoll  = 0;

	Elevator = 32767;
//DEADCODE AMM 18/01/00 	Aileron  = 32767;
//DEADCODE AMM 18/01/00 	Rudder   = 32767;

	ModelThrottle  = 0;
	ModelPropSetting = 0;
	LeftWheelBrake  = 32767;
	RightWheelBrake = 32767;

	FControlLoss = 0;

	Gear = TRUE;

	// Atmosphere
	AmbDensity = 0;
	AmbTemp    = 0;
	AmbPres    = 0;

	CrashTime = 0;

	Blood = 10;

	ControlledAC->fly.use_this_tank[0] = false;
	ControlledAC->fly.use_this_tank[1] = false;
	ControlledAC->fly.use_this_tank[2] = false;
	ControlledAC->fly.use_this_tank[3] = false;

	for(PMAINPLANE pMainPlane = MainPlaneList; pMainPlane; pMainPlane = pMainPlane->List.NextItem())
	{
		pMainPlane->aoa[0][0] = -1;
		pMainPlane->aoa[0][1] = -1;
		pMainPlane->aoa[1][0] = -1;
		pMainPlane->aoa[1][1] = -1;

		pMainPlane->fCd0Mach = -1;
		pMainPlane->fKMach   = -1;

		pMainPlane->DownWashAng[0] = -1;
		pMainPlane->DownWashAng[1] = -1;

		pMainPlane->BuffetAoaMin = 0;
		pMainPlane->BuffetAoaMax = 0;

		NullVec(pMainPlane->eForce[0][0]);
		NullVec(pMainPlane->eForce[0][1]);
		NullVec(pMainPlane->eForce[1][0]);
		NullVec(pMainPlane->eForce[1][1]);
		
		NullVec(pMainPlane->eMoment[0][0]);
		NullVec(pMainPlane->eMoment[0][1]);
		NullVec(pMainPlane->eMoment[1][0]);
		NullVec(pMainPlane->eMoment[1][1]);
	}

	for(PSURFACE pSurface = SurfaceList; pSurface; pSurface = pSurface->List.NextItem())
	{
		NullVec(pSurface->Force);
		NullVec(pSurface->Moment);
	}

	for(PTHRUSTPOINT pThrust = ThrustList; pThrust; pThrust = pThrust->List.NextItem())
	{
		NullVec(pThrust->Force);
		NullVec(pThrust->Moment);
	}

	for(PCYLINDER pCylinder = CylinderList; pCylinder; pCylinder = pCylinder->List.NextItem())
	{
		NullVec(pCylinder->Force);
	}
  
	for(PAERODEVICE pDevice = DeviceList; pDevice; pDevice = pDevice->List.NextItem())
	{
		pDevice->Val		  = 32767;
		pDevice->Attractor	  = 32767;
		pDevice->OldAttractor = 32767;
		pDevice->ReqVal		  = 32767;
		pDevice->Broken		  = TRUE;
	}

	for(PENGINE pEngine = EngineList; pEngine; pEngine = pEngine->List.NextItem())
	{
	   	pEngine->Speed     = -1;
		pEngine->SpeedRpm  = -1;
		pEngine->Power0    = -1;
		pEngine->Power100  = -1;
		pEngine->Power     = -1;
		pEngine->MaxThrust = -1;
		pEngine->Thrust    = -1;
		pEngine->Torque    = -1;
		NullVec(pEngine->moment);
		pEngine->PropInc = -1;
		pEngine->PropVel = -1;
		pEngine->SlipVel = -1;
 		pEngine->SlipRot = -100;
 		pEngine->FuelInPipes = -1;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ArcadeBase
//Author		Craig Beeston
//Date			Mon 13 Sep 1999
//
//Description	Simple flight model which models aircraft performance accurately
//				but no dynamic or ideosyncratic effects
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ArcadeBase (AirStrucPtr const ControlledAC)
{
	if(!(FrameCount & EVERY256cs))	//This will do the following commands for each aircraft
	{								//once every n operations.
		MissManCampSky().Ambient (Pos.y, AmbDensity, AmbTemp, AmbPres);
		FP FuelUsageRate = CalcFuelRate(ControlledAC);
		SetFuelTank(ControlledAC, true);
		ControlledAC->FuelLeft(FuelUsageRate);
		UpdateMassInertias(ControlledAC);
		Persons2::PlayerGhostAC->weap.right=ControlledAC->weap.right;
		Persons2::PlayerGhostAC->weap.left=ControlledAC->weap.left;
		Persons2::PlayerGhostAC->weap.centre=ControlledAC->weap.centre;
		//Calculates the rate of fuel burn and subtacts it from the fuel and total mass
	}

	FrameCount++;

	CalcAirVel (ControlledAC);
	if(Speed <= 0) Speed = 0.01;
	FP airspeed  = -AirVel.z;

	if(AirSpeed < ControlLossV0)
		FControlLoss = 1;
	else if(AirSpeed < ControlLossV1)
			FControlLoss = 1.0 - 0.8 * (AirSpeed - ControlLossV0) / (ControlLossV1 - ControlLossV0);
		else
			FControlLoss = 0.2;
//DeadCode AMM 24Nov99 	MODEL_DT = 4;
	AircraftAnimData* adptr = (AircraftAnimData *)ControlledAC->Anim;

	int totalfuel =		ControlledAC->fly.fuel_content[0] + ControlledAC->fly.fuel_content[1]
					+	ControlledAC->fly.fuel_content[2] + ControlledAC->fly.fuel_content[3];
			
	FP Throttle = FP(ControlledAC->fly.thrustpercent) * 0.01;

	if(totalfuel <= 0)
		Throttle = 0;
	
	if((Type == AT_SPITFIRE) || (Type == AT_HURRICANE))
		if(Inst.I_NormalAcc < 0)
			Throttle = 0;

	PENGINE pEngine = EngineList;
	while(pEngine != NULL)
	{
		if(adptr->ENGINELEFT >= 254)
		{
			pEngine->Speed  = 0;
			pEngine->Power  = 0;
			pEngine->Thrust = 0;
			pEngine->SlipVel = AirSpeed;
		}
		else
		{
			FP NewVel = airspeed;
			if(NewVel < 100)
			{
				NewVel = (1.0 - airspeed / 100.0);
				NewVel = airspeed + 33.0 * NewVel * NewVel;
			}
			pEngine->Power =  pEngine->pPower100->GetValue(pEngine->Speed * 954.93 / pEngine->Rpm100);
			pEngine->Power *= pEngine->pPowerAlt->GetValue(Pos.y * 0.01);
			pEngine->Power *= pEngine->p0;

			pEngine->Thrust = Throttle * pEngine->Power / NewVel + (1 - Throttle) * -0.2 * airspeed * airspeed;
			pEngine->Thrust *= 0.91;

			FP speed1 = 1.15 * pEngine->Rpm100;
			if(pEngine->pThrustPoint->Pos.x <= 0)
			{
				speed1 *= 1.0 - adptr->ENGINELEFT / 255.0;
				speed1 *= 1.0 - adptr->FRONT / 255.0;
			}
			else
				speed1 *= 1.0 - adptr->ENGINERIGHT / 255.0;
			FP factor = FP(ControlledAC->vel_) / FP(ControlledAC->CalcMaxVelSL());
			FP speed0 = speed1 * factor / 2;
			pEngine->PropSetting = factor;
			pEngine->PropInc = factor * pEngine->PropMaxPitch + (1 - factor) * pEngine->PropMinPitch;
			if(totalfuel > 0)
				MODMAXMIN(speed0, pEngine->Rpm0, speed1);

			FP speed = speed0 * (1 - Throttle) + (speed1) * Throttle;
			if(speed < 0.1 * speed1)
				speed = 0;
			speed *= 0.001047197;

			pEngine->Speed += (speed - pEngine->Speed) * MODEL_DT / 50; 
			pEngine->SlipVel = AirSpeed;
			if(Throttle)
				pEngine->FuelInPipes = 1;
			else
				pEngine->FuelInPipes = 0;
		}
		pEngine = pEngine->List.NextItem();
	}

	FP Thrust = 0;
	PTHRUSTPOINT pThrust = ThrustList;
	while (pThrust != NULL)
	{
		pThrust->Process ();
		Thrust += pThrust->Force.z;
		pThrust = pThrust->List.NextItem ();
	}
	if((Save_Data.flightdifficulty [FD_POWERBOOST]))// && (!GearTouched))
		Thrust *= PowerBoost;


	FP CLmax, CLmin, dCL, Area, AreaFrac;
	FP Alpha, CL, CD, Lift, Drag;
	FP PitchRate, RollRate, YawRate;
	const Angles MaxAoa = ANGLES_15Deg;

	ProcessDevices ();

//WARNING - This code does not handle multi-wing aircraft at present (Biplane - Triplane)
	PMAINPLANE pMainPlane = MainPlaneList;
	{
		Area  = (pMainPlane->wArea[0] + pMainPlane->wArea[1]) * 2;
		AreaFrac = 2 * pMainPlane->wArea[0] / Area;
		dCL	  = DeltaCl * AreaFrac;
		CLmax = pMainPlane->pClCurve->GetValue( Rowan2Rads(MaxAoa)) + dCL;
		CLmin = pMainPlane->pClCurve->GetValue(-Rowan2Rads(MaxAoa)) + dCL;
	}

	Area *= (1.0 - (FP(adptr->RIGHTWINGIN) + FP(adptr->RIGHTWINGOUT) + FP(adptr->LEFTWINGIN) + FP(adptr->LEFTWINGOUT)) * (1.0 / (4.0 * 255.0)));

	FP qS = 0.5 * AmbDensity * airspeed * airspeed * Area;
	
	GearTouched = FALSE;
	FP GroundAlt;
	int geary = 0;
	bool lwheeldown = false;
	bool rwheeldown = false;
	if(ControlledAC->World.Y < HIGHESTGROUND)
	{
		UByte Texture;
		GroundAlt = _Collide.GroundAltitude(ControlledAC->World, &Texture);
		if(ControlledAC->World.Y < GroundAlt + MAXAIRCRAFTSIZE)
		{
			if(!IsWater(Texture))
			{
				FCRD wpos0, wpos1;	//CSB 12/01/99
				TnsPnt(GearList->pos0, wpos0, Ori);
				TnsPnt(GearList->List.NextItem()->pos0, wpos1, Ori);
				geary = -wpos0.y;
				if(wpos1.y < wpos0.y)
					geary = -wpos1.y;

				if(Pos.y < GroundAlt + geary + 5)
				{
					for(PAERODEVICE pDevice = DeviceList; pDevice; pDevice = pDevice->List.NextItem())
						if( (pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->Val == 16384) )
						{
							GearTouched = TRUE;
							if(pDevice->UpKey != NULLKEY)
								lwheeldown = true;
							else
								rwheeldown = true;
						}

					if(Type == AT_JU87B)
						GearTouched = TRUE;
					if((GearTouched) && (Save_Data.gamedifficulty[GD_GROUNDCOLLISIONS]) && (IsRaised(Texture)))
					{
						Manual_Pilot.DeathSequenceOverrideDiary(ControlledAC, AUTO_CRASHTUMBLE);//RJS 31Oct00
						Trans_Obj.View_Object->SetToDeathView(DEATH_SKID);
					}
				}
			}
			Ground(ControlledAC);
		}
	}

	if(GearTouched)
	{
		Pos.y = GroundAlt + geary;

		Vel.y = 0;
		Alpha = Ori.z.y * 10430.4;
		pMainPlane->aoa[0][0] = Rowan2Rads(Alpha);
		pMainPlane->aoa[1][0] = pMainPlane->aoa[0][0];
		CL = CLmin + (Alpha + MaxAoa) / (2 * MaxAoa) * (CLmax - CLmin);
		CD = pMainPlane->Cdo + pMainPlane->k * CL * CL + DeltaCd * AreaFrac;
		Lift = CL * qS;
		Drag = CD * qS;

		if(Lift > Mass * GRAVITY)
		{
			Alpha -= 91.0;	//0.5 deg
			Pos.y += 5;
		}
		
		PitchRate = 0.002;
		RollRate  = 0;
		if(-ControlledAC->roll > ANGLES_1Deg)	RollRate += 0.001;
		if( ControlledAC->roll > ANGLES_1Deg)	RollRate -= 0.001;

		PitchRate -= airspeed * FP(Elevator) * 0.000000005;
		if(PitchRate > 0)
		{
			if(ControlledAC->pitch > ControlledAC->classtype->deckangle)
				PitchRate -= 0.002;
			FP maxpitchrate = SWord(ANGLES(ControlledAC->classtype->deckangle)) - SWord(ControlledAC->pitch);
			maxpitchrate *= (1.0 / (182.04 * 57.3 * MODEL_DT));
			if(PitchRate > maxpitchrate)
				PitchRate = maxpitchrate;
		}
		YawRate = Speed * FP(Rudder) * 0.000000005;
	}
	else
	{
		FP CL_1g = 0;
		if(qS > 0)	CL_1g = Mass * GRAVITY / qS;
		MODMAXMIN(CL_1g, CLmin, CLmax);

		if(Elevator <= 0)	CL = CL_1g - FP(Elevator) / 32767.0 * (CLmax - CL_1g);
		else				CL = CL_1g + FP(Elevator) / 32767.0 * (CLmin - CL_1g);

		FP desalpha = (-1.0 + 2.0 * (CL - CLmin) / (CLmax - CLmin)) * FP(MaxAoa);
		FP maxdelta = 200.0;
		FP oldalpha = Rads2Rowan(pMainPlane->aoa[0][0]);
		if((desalpha >= oldalpha - maxdelta) && (desalpha <= oldalpha + maxdelta))
			Alpha = desalpha;
		else 
			if(desalpha < oldalpha - maxdelta)
				Alpha = oldalpha - maxdelta;
			else
				Alpha = oldalpha + maxdelta;
		CL = CLmin + (CLmax - CLmin) * (Alpha + MaxAoa) / (2 * MaxAoa);

		CD = pMainPlane->Cdo + pMainPlane->k * CL * CL + DeltaCd * AreaFrac;
		Lift = CL * qS;
		Drag = CD * qS;
		
		Float SinR, CosR;
		Math_Lib.high_sin_cos(ControlledAC->roll, SinR, CosR);

		Float SinP, CosP;
		Math_Lib.high_sin_cos(ControlledAC->pitch, SinP, CosP);

		PitchRate = (Lift - Mass * GRAVITY * Ori.y.y) / (Mass * Speed);
		YawRate   = GRAVITY * SinR * CosP / Speed;
		FP RollReq = FP(Aileron) * (1.0 - (FP(adptr->RIGHTWINGOUT) + FP(adptr->LEFTWINGOUT)) / 512.0);
		RollReq += (2.0 * FP(adptr->RIGHTWINGOUT) + FP(adptr->RIGHTWINGIN) - 2.0 * FP(adptr->LEFTWINGOUT) - FP(adptr->LEFTWINGIN)) * 32.0;
		MODLIMIT(RollReq, 32767.0);

		RollRate =  RollReq * Rowan2Rads(FP(ControlledAC->classtype->maxrollrate)) * (1.0 / 32768.0 / 100.0);
		YawRate  += FP(Rudder)  * 0.25 * (1.0 / 32768.0 / 100.0);
		FP alpharad = Rowan2Rads(Alpha);
		if(alpharad > FPIE)
			alpharad -= F2PIE;
		PitchRate += (alpharad - pMainPlane->aoa[0][0]) / MODEL_DT;
		pMainPlane->aoa[0][0] = alpharad;
		pMainPlane->aoa[1][0] = alpharad;
		if(alpharad < pMainPlane->buffetAoa0) 
			alpharad = pMainPlane->buffetAoa0;
		TotalBuffet = 4.0 * (alpharad - pMainPlane->buffetAoa0) / (pMainPlane->buffetAoa1 - pMainPlane->buffetAoa0);
	}

	Float SinA, CosA;
	Math_Lib.high_sin_cos(Angles(SWord(Alpha)), SinA, CosA);

	
	FP acc = (Thrust * CosA - Drag) / Mass - GRAVITY * Vel.y / Speed;
	if(GearTouched)
	{
		acc -= 0.002;
		if(Key_Tests.KeyHeld3d(LEFTWHEELBRAKE))
			if((Type == AT_JU87B) || (lwheeldown))
			{
				acc -= 0.02;
				YawRate -= Speed * 0.00025;
			}
		if(Key_Tests.KeyHeld3d(RIGHTWHEELBRAKE))
			if((Type == AT_JU87B) || (rwheeldown))
			{
				acc -= 0.02;
				YawRate += Speed * 0.00025;
			}
	}
	Speed += acc * MODEL_DT;
	if(Speed < 0)
		Speed = 0;

	FCRD LocalVel;
	LocalVel.x = 0;
	LocalVel.y = -Speed * SinA;
	LocalVel.z =  Speed * CosA;

	
	TnsPnt(LocalVel, Vel, Ori);
	
	SLong wx = 0;
	SLong wy = 0;
	SLong wz = 0;
	if(!GearTouched)
		MissManCampSky().GetWind(ControlledAC->World.Y, wx, wy, wz);

	Pos.x += (Vel.x + wx * 0.0001) * MODEL_DT;
	Pos.y += (Vel.y + wy * 0.0001) * MODEL_DT;
	Pos.z += (Vel.z + wz * 0.0001) * MODEL_DT;

	RotVel.x = PitchRate;
	RotVel.y = -YawRate;
	RotVel.z = RollRate;
	
	RotVelInt();

	NettForce.x = (-RotVel.y * Speed + GRAVITY * Ori.x.y) * Mass;
	if(GearTouched)
		NettForce.y = Mass * GRAVITY * CosA;
	else
		NettForce.y = Lift;
	NettForce.z	= Thrust - Drag;
		
	CalcAcc();

//#define ARCADE_MODEL_DATA
#ifdef ARCADE_MODEL_DATA

/* TEST CODE CSB 14/09/99 */	PrintVar(0, 3, "Elevator %.0f     ", FP(Elevator));
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 4, "Aileron  %.0f     ", FP(Aileron));
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 5, "Rudder   %.0f     ", FP(Rudder));
/* TEST CODE CSB 14/09/99 */
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 7, "Mass     %.0f     ", FP(Mass * 0.01));
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 8, "Vel      %.2f     ", FP(Speed));
/* TEST CODE CSB 14/09/99 */
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 11, "PitchRate    %.4f ", FP(PitchRate    * 100.0 * 57.3));
/* TEST CODE CSB 14/09/99 */
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 15, "RollRate %.4f ", FP(RollRate * 100.0 * 57.3));
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 16, "YawRate  %.4f ", FP(YawRate  * 100.0 * 57.3));
/* TEST CODE CSB 14/09/99 */
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 20, "CLmin  %.4f ", FP(CLmin));
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 21, "CL     %.4f ", FP(CL));
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 22, "CLmax  %.4f ", FP(CLmax));
/* TEST CODE CSB 14/09/99 */
/* TEST CODE CSB 14/09/99 */	PrintVar(0, 24, "Alpha  %.4f ", FP(Alpha / 182.04));
/* TEST CODE CSB 14/09/99 */
/* TEST CODE CSB 14/09/99 */	PrintVar(30, 5, "Thrust  %.0f ", FP(Thrust));
/* TEST CODE CSB 14/09/99 */	PrintVar(30, 6, "Drag    %.0f ", FP(Drag));
/* TEST CODE CSB 14/09/99 */	PrintVar(30, 7, "Acc     %.4f ", FP(Acc * 100.0));
#endif
	
	Instruments (ControlledAC);
	MovePilotEye();

//DEADCODE RJS 3/24/00 	Animations (ControlledAC);
//	Ground (ControlledAC);

	if(EngineList)
	{
		static	EngineInfo	left_engine;
		static	EngineInfo	right_engine;
		float	cockdam = adptr->CANOPY*adptr->CANOPY;				//RJS 22Feb00
		float	cockopen = adptr->accanopy*adptr->accanopy;
		SLong	cocknobble;

		fastMath.FloatToInt(&cocknobble,fastMath.FastSqrt(cockdam+cockopen));
		if (cocknobble > 255)	cocknobble=255;

		if (EngineList->Type == ET_PISTON)
		{
			FP power = 238.0 * EngineList->Power / EngineList->p0;
			MODMAXMIN(power, 0, 255);
			left_engine.power = power;
		}

//JET_Code CSB 22/09/99			if (EngineList->Type == ET_JET)
//JET_Code CSB 22/09/99			{
//JET_Code CSB 22/09/99				ThrustVol = (170 * EngineList->Thrust) / EngineList->T100;			//RJS 14Jan99
//JET_Code CSB 22/09/99				
//JET_Code CSB 22/09/99				if(Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL])
//JET_Code CSB 22/09/99					if(Inst.ExhaustTemp > 225)	//Throttle advanced too quickly
//JET_Code CSB 22/09/99						if(FrameCount & 0x0002)
//JET_Code CSB 22/09/99							ThrustVol = (ThrustVol * (255 - Inst.ExhaustTemp)) / (255 - 225);
//JET_Code CSB 22/09/99			}
//DeadCode RJS 13Jan00		_Miles.PlayEngine(adptr->CANOPY,ControlledAC,Inst.I_EngineRpm0,ControlledAC->vel_, ThrustVol);//RJS 17Nov99

		left_engine.rpm_starter = 0;
		left_engine.rattle = 0;										//RJS 13Jan00
		left_engine.cockpitnobble = cocknobble;						//RJS 22Feb00
		left_engine.rpm_engine = Inst.I_EngineRpm0;
		left_engine.velocity = ControlledAC->vel_;

//DeadCode RJS 9Jun00 		right_engine = left_engine;

		_Miles.PlayEngine(ControlledAC,left_engine,left_engine);	//RJS 13Jan00
	}

	_Miles.PlayWindyMiller(ControlledAC);										//RJS 21May99

	if (_Analogue.FFdevice)
		CalcStickForceFeedback();	//fix this !!!!

	if(ControlledAC->movecode == AUTO_TRAININGTAKEOFF) 
		TrainingTakeoff(ControlledAC);
	else if(ControlledAC->movecode == AUTO_TRAININGLANDING)
		TrainingLanding(ControlledAC);
		
	static SByte landed;
	if(FirstCycle)
		landed = -1;
	if((landed != 1) && (Pos.y > ControlledAC->ai.homebase->World.Y + FT_500))
		landed = 0;

	FirstCycle = FALSE;
	UpdateAirStruc (ControlledAC);

	CommsChecks(ControlledAC);

	if((landed == 0) && (Speed < 10) && (GearTouched))
	{
		if(ControlledAC->Distance3DSquared(&ControlledAC->ai.homebase->World) < FP(100000) * FP(100000))
			Squad_Diary.UpdatePlayerLog(EFS_LandedOK);
		else if(OnAnAirfield(ControlledAC))
			Squad_Diary.UpdatePlayerLog(EFS_LandedOtherAF);
		else
			Squad_Diary.UpdatePlayerLog(EFS_LandedField);

		landed = 1;
		Art_Int.exittimer = 1000;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DamageGear
//Author		Robert Slater
//Date			Fri 17 Dec 1999
//
//Description	Damage hydraulics and force a wheel to lower....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::DamageGear(Coords3D&	hitpos)
{
	if (Math_Lib.rnd() < 4096)		//1 in 16 chance of lowering...
	{
		for(PAERODEVICE pDevice = DeviceList; pDevice; pDevice = pDevice->List.NextItem())
			if(pDevice->Type == AeroDevice::DT_GEAR)
			{
				pDevice->Attractor = Math_Lib.rnd(0x4000);
				pDevice->OldAttractor = pDevice->Attractor;		//No device sound effects
			}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrainingTakeoff
//Author		Craig Beeston
//Date			Wed 16 Feb 2000
//
//Description	Triggers radio messages and keep score
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::TrainingTakeoff(AirStrucPtr ControlledAC)
{
	static bool finished;
	static bool stalled;
	static bool wingdrop;
	static bool liftedoff;
	static bool bounced;
	static SLong takeofftime;

	const SWord wingdropang = ANGLES_10Deg;
	const FP    badbuffet   = 1.0;
	const ULong goodtakeofftime = 40 * SECS100;
	const ULong oktakeofftime   = 50 * SECS100;
	const ULong badtakeofftime  = 60 * SECS100;

	if(FirstCycle)
	{
		AirStrucPtr callee = ControlledAC->FindFormpos0();
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TO_TRAINING, MSG_CLEAR_RPT, VOICE_TOWER, NULL, callee));

		if(!ControlledAC->formpos)
		{
			ScriptTables windrep = SCRIPT_NOWIND;
			if(Save_Data.flightdifficulty [FD_WINDEFFECTS])
				if(Save_Data.flightdifficulty [FD_WINDGUSTS])
					windrep = SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED_GUSTS;
				else
					windrep = SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED;
						
			_Radio.TriggerMsg(MESSAGE_STRUC(windrep, MSG_WIND_LOW_REPORT, VOICE_TOWER, NULL, callee));
		}
		finished	= false;
		stalled		= false;
		wingdrop	= false;
		liftedoff	= false;
		bounced		= false;
		takeofftime = 0;
	}

	if(finished)
		return;

	SWord absroll = AbsAngle(SWord(ControlledAC->roll));
	if(absroll > wingdropang)
		wingdrop = true;

	if((liftedoff) && (TotalBuffet > badbuffet))
		stalled = true;

	bool offground = true;
	if(this->GearTouched)
		offground = false;

	if(offground)
		liftedoff = true;
	else
		if(liftedoff)
			bounced = true;

	takeofftime += MODEL_DT;

	if(ControlledAC->World.Y - ControlledAC->ai.homebase->World.Y > FT_50)
	{
		int	theScript = SCRIPT_NULL;									//RJS 30Oct00

//DeadCode RJS 30Oct00 		if((!stalled) && (!wingdrop) && (!bounced))
//DeadCode RJS 30Oct00 		{
//DeadCode RJS 30Oct00 			if(takeofftime < goodtakeofftime) 
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WELLDONE_TO, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 			else if(takeofftime < oktakeofftime) 
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NICE_TO, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 			else if(takeofftime < badtakeofftime) 
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TOOSLOW, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 			else
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MINCEMEAT, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 		}
//DeadCode RJS 30Oct00 		else
//DeadCode RJS 30Oct00 		{
//DeadCode RJS 30Oct00 			if(takeofftime < goodtakeofftime) 
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_QUICKUNTIDY, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 			else if(takeofftime < badtakeofftime) 
//DeadCode RJS 30Oct00 			{
//DeadCode RJS 30Oct00 				if(takeofftime < oktakeofftime) 
//DeadCode RJS 30Oct00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SLOWUNTIDY, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 				else
//DeadCode RJS 30Oct00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TOOSLOW, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 				if(wingdrop)
//DeadCode RJS 30Oct00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WATCHWING, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 				else
//DeadCode RJS 30Oct00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TREATGENTLEY, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 			}
//DeadCode RJS 30Oct00 			else
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MINCEMEAT, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 		}

		if((!stalled) && (!wingdrop) && (!bounced))
		{
			if(takeofftime < goodtakeofftime) 
				theScript = SCRIPT_WELLDONE_TO;
			else if(takeofftime < oktakeofftime) 
				theScript = SCRIPT_NICE_TO;
			else if(takeofftime < badtakeofftime) 
				theScript = SCRIPT_TOOSLOW;
			else
				theScript = SCRIPT_MINCEMEAT;
		}
		else
		{
			if(takeofftime < goodtakeofftime) 
				theScript = SCRIPT_QUICKUNTIDY;
			else if(takeofftime < badtakeofftime) 
			{
				if(takeofftime < oktakeofftime) 
					theScript = SCRIPT_SLOWUNTIDY;
				else
					theScript = SCRIPT_TOOSLOW;
				if(wingdrop)
					theScript = SCRIPT_WATCHWING;
				else
					theScript = SCRIPT_TREATGENTLEY;
			}
			else
				theScript = SCRIPT_MINCEMEAT;
		}

		_Radio.TriggerMsg(MESSAGE_STRUC(theScript, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));	//RJS 30Oct00
		Squad_Diary.AddTrainingReport(theScript);						//RJS 30Oct00

		finished = true;
		Art_Int.exittimer = 1000;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrainingLanding
//Author		Craig Beeston
//Date			Wed 16 Feb 2000
//
//Description	Triggers radio messages and keep score
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::TrainingLanding(AirStrucPtr ControlledAC)
{
	static bool finished;
	static bool startdamaged;
	static bool startbadlydamaged;
	static bool enddamaged;
	static bool toucheddown;
	static bool bounced;

	if(FirstCycle)
	{
		AirStrucPtr callee = ControlledAC->FindFormpos0();
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOLAND, MSG_CLEAR_RPT, VOICE_TOWER, callee, callee));//RJS 11Apr00
		ScriptTables windrep = SCRIPT_NOWIND;
		if(Save_Data.flightdifficulty [FD_WINDEFFECTS])
			if(Save_Data.flightdifficulty [FD_WINDGUSTS])
				windrep = SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED_GUSTS;
			else
				windrep = SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED;
					
		_Radio.TriggerMsg(MESSAGE_STRUC(windrep, MSG_WIND_LOW_REPORT, VOICE_TOWER, NULL, callee));
		finished	= false;
		enddamaged	= false;
		toucheddown = false;
		bounced		= false;

		AircraftAnimData* adptr = (AircraftAnimData*)ControlledAC->Anim;
		SLong damage = adptr->ENGINELEFT + adptr->LEFTWINGIN + adptr->RIGHTWINGIN;

		if(damage > BS_DAMLV1)	startdamaged = true;
		else				  	startdamaged = false;

		if(damage > BS_DEAD)	startbadlydamaged = true;
		else					startbadlydamaged = false;
	}

	if(finished)
		return;

	bool offground = true;
	if(GearTouched)
	{
		offground = false;
		for(PGEAR pGear = GearList; pGear; pGear = pGear->List.NextItem())
			if(pGear->LegPos == 1)
				enddamaged = true;
	}

	if(offground)
	{
		if((toucheddown) && (ControlledAC->World.Y > GroundHeight + (3 * ControlledAC->classtype->deckshunt) / 2))
			bounced = true;
	}
	else
		toucheddown = true;


	if((toucheddown) && (Speed < ControlledAC->classtype->landingspeed / 20000))
	{
		for(PAERODEVICE pDevice = DeviceList; pDevice; pDevice = pDevice->List.NextItem())
			if(pDevice->Broken)
				enddamaged = true;

		int	theScript = SCRIPT_NULL;									//RJS 30Oct00

//DeadCode RJS 30Oct00 		if(!enddamaged)
//DeadCode RJS 30Oct00 		{
//DeadCode RJS 30Oct00 			if(!bounced)
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_GOODLANDING, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 			else
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BADLANDING, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 
//DeadCode RJS 30Oct00 			if(startbadlydamaged)
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_LANDEDBADLYDAMAGEDAC, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 			else if(startdamaged)
//DeadCode RJS 30Oct00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_LANDEDDAMAGEDAC, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
//DeadCode RJS 30Oct00 		}
//DeadCode RJS 30Oct00 		else
//DeadCode RJS 30Oct00 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DAMAGEONLANDING, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));
		if(!enddamaged)													//RJS 30Oct00
		{
			if((!bounced) && (ControlledAC->Distance3DSquared(&ControlledAC->ai.homebase->World) < FP(100000) * FP(100000)))
				theScript = SCRIPT_GOODLANDING;
			else
				theScript = SCRIPT_BADLANDING;

			if(startbadlydamaged)
				theScript = SCRIPT_LANDEDBADLYDAMAGEDAC;
			else if(startdamaged)
				theScript = SCRIPT_LANDEDDAMAGEDAC;
		}
		else
			theScript = SCRIPT_DAMAGEONLANDING;

		_Radio.TriggerMsg(MESSAGE_STRUC(theScript, MSG_STATUS, VOICE_TOWER, NULL, ControlledAC));	//RJS 30Oct00
		Squad_Diary.AddTrainingReport(theScript);						//RJS 30Oct00

		finished = true;
		Art_Int.exittimer = 1000;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CommsChecks
//Author		Craig Beeston
//Date			Wed 11 Oct 2000
//
//Description	When you've landed counts up a timer and will rearm, refuel, repair.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CommsChecks(AirStrucPtr ControlledAC)
{
	if((!_DPlay.Implemented) || (_DPlay.GameType == DPlay::COMMSQUICKMISSION))
		return;

	if((GearTouched) && (Speed < 1.0))
	{
		ControlledAC->ai.desiredalt += MODEL_DT;
		if(!(ControlledAC->ai.desiredalt & 0x64))
			_Miles.PlaySample(FIL_SFX_GUN_RELOADING4);
		if(ControlledAC->ai.desiredalt >= 1000)
		{
			_Miles.PlaySample(FIL_SFX_CANOPY_BLOW);
			Manual_Pilot.controlmode = ManualPilot::PILOTDEAD;
			ControlledAC->movecode = AUTO_NOPPILOT;
			ControlledAC->ai.desiredalt = 0;
		}
	}
	else
		ControlledAC->ai.desiredalt = 0;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OnAnAirfield
//Author		Craig Beeston
//Date			Tue 07 Nov 2000
//
//Description	Is the aircraft position within 1 km of a friendly airfield
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool Model::OnAnAirfield(AirStrucPtr ControlledAC)
{
	int	start = RAF_FighterAFBAND, stop = CLRadarBAND;
	if(ControlledAC->nationality == NAT_BLUE)
		start = LUF_FighterLF2BAND, stop = LUF_BomberBANDEND;

	for(int i = start; i < stop; i++)
	{
		ItemPtr thisaf = Persons2::ConvertPtrUID(UniqueID(i));
		if((thisaf) && (ControlledAC->Distance3DSquared(&thisaf->World) < FP(100000) * FP(100000)))
			return(true);
	}

	return(false);
}
