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

//------------------------------------------------------------------------------
//Filename       engine.cpp
//System         
//Author         Andrew McRae
//Date           Thu 24 Apr 1997
//Description    Engines
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "ranges.h"
#include "myangles.h"
#include "planetyp.h"
#include "collided.h"
#include "mytime.h"
#include "myerror.h"
#include "monotxt.h"
#include "savegame.h"

//DeadCode RJS 02Dec97 #include "3dcom.h"



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Engine
//Author		Craig Beeston
//Date			Thu 12 Nov 1998
//
//Description	Jet Engine Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Engine::Engine (PMODEL pmodel,
				ENGINE_TYPE type,
				FP		t100,			// static thrust & sea level (lbf)
				FP		rpm100,			// max RPM
				FP		oneovermoi,		// 1 / Moment of Inertia
				PCURVE	machfact,		// thrust variation with mach number
				PCURVE	thrustrpm,		// thrust variation with engine rpm
				PCURVE	windmilldrag,	// windmill drag variation with true air speed
				PCURVE	windmillrpm)	// idle rpm variation with true air speed
{

//JET_Code CSB 21/09/99		NullThis ();
//JET_Code CSB 21/09/99	
//JET_Code CSB 21/09/99		pModel = pmodel;
//JET_Code CSB 21/09/99		Type = type;
//JET_Code CSB 21/09/99	
//JET_Code CSB 21/09/99		T100		= t100;
//JET_Code CSB 21/09/99		Rpm100		= rpm100;
//JET_Code CSB 21/09/99		OneOverMoI	= oneovermoi;
//JET_Code CSB 21/09/99		MachFact	= machfact;
//JET_Code CSB 21/09/99		ThrustRpm	= thrustrpm;
//JET_Code CSB 21/09/99		WindMillDrag= windmilldrag;
//JET_Code CSB 21/09/99		WindMillRpm = windmillrpm;
//JET_Code CSB 21/09/99	
//JET_Code CSB 21/09/99		EngineOut = FALSE;
//JET_Code CSB 21/09/99	
//JET_Code CSB 21/09/99		List.Attach (&pModel->EngineList, this);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Engine
//Author		Andrew McRae
//Date			Mon 27 Jan 1997
//
//Description	Piston Engine Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Engine::Engine (PMODEL pmodel, ENGINE_TYPE type)
{

	// Initialise

	NullThis ();

	pModel = pmodel;
	Type = type;

	FP ACspeed = VecLen(pModel->Vel);
	if(ACspeed < 10) ACspeed = 10;
	PropVel = ACspeed;				//Speed of airflow through prop			/CSB
	SlipVel = ACspeed;				//Speed of airflow in slipstream		/CSB
	SlipRot = 0;					//Rotation of airflow in slipstream		/CSB
	PropInc = 44;	//CSB 04/06/99	

	Magnetos     = 0;
	Temperature  = 0;
	FuelInPipes  = 0;
	StarterSpeed = 0;
	Priming		 = 0;
	Starting	 = false;

	List.Attach (&pModel->EngineList, this);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NullThis
//Author		Andrew McRae
//Date			Fri 13 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Engine::NullThis ()
{
	ULong n = sizeof(Engine);
	for (UByte* p=(UByte*)this;n;n--,p++) {	*p = 0;	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Engine
//Author		Andrew McRae
//Date			Mon 27 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Engine::~Engine ()
{

	List.Detach (this);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessPistonEngine
//Author		Craig Beeston
//Date			Tue 11 Aug 98
//
//Description	Processes a piston engine
//					Calculates Thrust, Torque, Engine power and Engine speed
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Engine::ProcessPistonEngine (AirStrucPtr const ControlledAC)
{
	AircraftAnimData* adptr = (AircraftAnimData *)ControlledAC->Anim;
	SWord iDamage = 255 - (255 - UWord(adptr->ENGINELEFT)) * (255 - UWord(adptr->FRONT)) / 255;
	if(pThrustPoint->Pos.x > 0)
		iDamage = adptr->ENGINERIGHT;
	
	FP MaxSpeed = 2 * Rpm100 * 0.001047197;	//RPM 2 Rads/cs
	if(iDamage == 254)
		MaxSpeed = 0;
	FP fDamage = 1.0 - FP(iDamage) * (1.0 / 255.0);
		
//DEADCODE CB 04/11/99 	FP MinSpeed =     Rpm0   * 0.001047197;	//RPM 2 Rads/cs

//DEADCODE CB 04/11/99 	if (Speed < MinSpeed) Speed = MinSpeed;	
	if (Speed > MaxSpeed) Speed = MaxSpeed;	

	FP EngRPM    = Speed * 954.9296586;
	FP PropSpeed = Speed * GearRatio;
	FP PropSwirl = SlipRot * 0.5;

	const FP BladeFract = 0.60;

	FCRD Vel;
	CPrd(Vel, pThrustPoint->Pos, pModel->RotVel);
	Vel.z -= pModel->AirVel.z;				//Velocity of air ahead of prop
	
	FP PropAirVel = BladeFract * (PropSpeed - PropSwirl) * BladeRadius;
	FP InflowAng = CalcAngle (PropAirVel, PropVel);

//Automatic prop control for AI aircraft
	if((!Save_Data.flightdifficulty [FD_PROPPITCH]) || (ControlledAC != Persons2::PlayerSeenAC))
	{
		switch(PropType)
		{
			case PT_FIXED:
				break;

			case PT_2PITCH:
				if(EngRPM > 1.15 * Rpm100)
					PropSetting = 0;
				if(EngRPM < 0.7 * Rpm100)
					PropSetting = 1;
				break;

			case PT_VARIABLE:
				PropSetting = 1.0 - 1.15 * ControlledAC->vel_ / ControlledAC->classtype->maxvel;
				MODMAXMIN(PropSetting, 0.01, 1);
				break;

			case PT_CONSTSPEED:
				if(ThrottleSetting <= 75)
					PropSetting = 0;
				else
					PropSetting = (ThrottleSetting - 75.0) / 25.0;
//DEADCODE CSB 31/01/00 				PropSetting = FP(ThrottleSetting) * 0.01;
//DEADCODE CSB 31/01/00 				PropSetting = PropSetting * PropSetting * PropSetting;
				break;
		}
	}

	switch(PropType)
	{
		case PT_FIXED:
		{
			PropInc = PropMaxPitch;
			break;
		}
		case PT_2PITCH:
		{
			FP DesiredInc = PropMaxPitch;
			if(PropSetting > 0.5)
				DesiredInc = PropMinPitch;
			if(DesiredInc > PropInc)
			{
				PropInc += 0.002 * MODEL_ENGINE_DT;					//AMM 24Nov99
				if(PropInc > DesiredInc) PropInc = DesiredInc;
			}
			if(DesiredInc < PropInc)
			{
				PropInc -= 0.002 * MODEL_ENGINE_DT;					//AMM 24Nov99
				if(PropInc < DesiredInc) PropInc = DesiredInc;
			}
			break;
		}
		case PT_VARIABLE:
		{
			FP DesiredInc = PropMaxPitch;
			if(PropSetting > 0)
			{
				FP Ratio = 0.5 * (PropSetting + 1.0);
				DesiredInc = PropMinPitch * Ratio + PropMaxPitch * (1 - Ratio);
			}

			if(DesiredInc > PropInc)
			{
				PropInc += 0.002 * MODEL_ENGINE_DT;					//AMM 24Nov99
				if(PropInc > DesiredInc) PropInc = DesiredInc;
			}
			if(DesiredInc < PropInc)
			{
				PropInc -= 0.002 * MODEL_ENGINE_DT;					//AMM 24Nov99
				if(PropInc < DesiredInc) PropInc = DesiredInc;
			}
			break;
		}
		case PT_CONSTSPEED:
		{
			FP DesiredRpm = Rpm100 * (0.7 + 0.45 * PropSetting);
			FP PropPitchRate = (EngRPM - DesiredRpm) * 0.00001;
			PropInc += PropPitchRate * MODEL_ENGINE_DT;				//AMM 24Nov99
			break;
		}
	}	

	MODMAXMIN(PropInc, PropMinPitch, PropMaxPitch);

	FP BladeSpeed = FSqrt(PropAirVel * PropAirVel + PropVel * PropVel);
	FP BladeQS  =  0.5 * pModel->AmbDensity * BladeSpeed * BladeArea;
	
//DeadCode AMM 29Jun99 	J = PropVel / ((PropSpeed - PropSwirl) * 0.75 * BladeRadius);	//Only Used for Text Screen

	FP BladeL = 4.53 * (PropInc - InflowAng);
	FP BladeD = 0.005 + (0.071 * BladeL * BladeL);	
	MODMAXMIN(BladeL, -1.0, 1.5);

	BladeL *= BladeQS;
	BladeD *= BladeQS;

	Thrust = BladeL * PropAirVel - BladeD * PropVel;
	Torque = BladeD * PropAirVel + BladeL * PropVel;
	Torque *= BladeRadius * 0.5;	//effective overall moment


//Engine Power Output
	Power100 = pPower100->GetValue (EngRPM / Rpm100);
	Power0   = pPower0->GetValue (EngRPM / Rpm100);

	FP fPower  = 0;
	FP dTorque = 0;

	ComplexEngineProcess(ControlledAC, fDamage, fPower, dTorque);

	const FP MinThrottle = 0.125;
	FP PowerFract = MinThrottle + ThrottleSetting * (1 - MinThrottle) * 0.01;

	PowerFract *= fPower;

	FP oldpower = Power;
	Power = Power0 + ((Power100 - Power0) * PowerFract);
	
	if((oldpower <= 0) && (Power > 0))
		Trans_Obj.LaunchEngineStartup((mobileitem*)ControlledAC, *ControlledAC->currworld);

	if((oldpower > 0) && (Power <= 0) && (ControlledAC == Persons2::PlayerSeenAC))
		_Miles.PlayOnce(FIL_SFX_ENGINE_COUGH,Save_Data.vol.engine);		//RJS 27Sep00

	Power *= pPowerAlt->GetValue(pModel->Pos.y * 0.01);
	Power *= p0;


//#define ENGINE_DATA
#ifdef ENGINE_DATA
//DeadCode CSB 27/10/99	/* TEST CODE CSB 27/10/99 */if(pModel->bACM)
/* TEST CODE CSB 27/10/99 */{
//DEADCODE CSB 11/01/00 /* TEST CODE CSB 29/09/99 */	PrintVar(40, 15, "Gravity  %.3f ", FP(pModel->Inst.I_NormalAcc));
//DEADCODE CSB 11/01/00 /* TEST CODE CSB 29/09/99 */	PrintVar(40, 16, "IAS      %.2f ", FP(pModel->Speed * FSqrt (pModel->AmbDensity / 0.0001225)));
//DEADCODE CSB 11/01/00 /* TEST CODE CSB 29/09/99 */	PrintVar(40, 17, "Vel      %.2f ", FP(ControlledAC->vel_ * 0.0001));
//DEADCODE CSB 11/01/00 /* TEST CODE CSB 29/09/99 */	PrintVar(40, 18, "DesRpm   %.2f ", FP(pModel->ModelPropSetting));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 15, "Power    %.0f ", FP(Power / 745.7));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 16, "RPM      %.0f ", FP(EngRPM));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 17, "Prop Inc %.2f ", FP(Rads2Degs(PropInc)));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 18, "Vel      %.2f ", FP(-pModel->AirVel.z));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 19, "PropVel  %.2f ", FP(PropVel));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 20, "SlipVel  %.2f ", FP(SlipVel));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 21, "Alpha    %.2f ", FP(Rads2Degs(PropInc - InflowAng)));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 24, "ROC fpm  %.0f ", FP(pModel->Vel.y * 3.2808 * 60.0));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 22, "Thrust   %.1f ", FP(Thrust));
/* TEST CODE CSB 29/09/99 */	PrintVar(20, 23, "Eff      %.3f ", FP(Thrust * -pModel->AirVel.z / Power));
/* TEST CODE CSB 27/10/99 */}
#endif


	FP EngTorque = 0;
	if(Speed > 0) 
		EngTorque = Power / Speed;
	
	EngTorque += dTorque;

//Slipstream Conditions
	FP OldSlipRot = SlipRot;
	FP SlipInertia = BladeRadius * BladeRadius * BladeRadius * BladeRadius 
		              * 0.5 * FPIE * PropVel * pModel->AmbDensity;
	if(SlipInertia > 0)
		SlipRot	   = (Torque / SlipInertia + OldSlipRot) * 0.5;
	else
		SlipRot = 0;
	if(SlipRot > PropSpeed) SlipRot = PropSpeed;

	FP OldSlipVel = SlipVel;
	FP PropArea = FPIE * BladeRadius * BladeRadius;
	FP TempSlip = 2 * Thrust / (pModel->AmbDensity * PropArea) + Vel.z * Vel.z;
	if (TempSlip < 0) SlipVel = -Vel.z;
	else 
		SlipVel = sqrt(TempSlip);
	SlipVel = (SlipVel + OldSlipVel) * 0.5;
	PropVel = 0.5 * (0.5 * (Vel.z + SlipVel) + PropVel);

// calc engine speed
	FP EngRotAcc = (EngTorque - Torque * GearRatio) / MoI;

//DeadCode CSB 27/10/99		if (!Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL])
//DeadCode CSB 27/10/99			EngRotAcc *= 2;												//Fast Spooling

//DEADCODE AMM 24/11/99 	Speed += pModel->MODEL_DT * EngRotAcc;
	Speed += MODEL_ENGINE_DT * EngRotAcc; //AMM 24/11/99


	if(Speed < 0) Speed = 0;
	
//DEADCODE CB 04/11/99 	if (Speed < MinSpeed) Speed = MinSpeed;		
	if (Speed > MaxSpeed) Speed = MaxSpeed;		
				

	Torque	= -Torque * RotateDirection;//(EngTorque - Torque / GearRatio);				//Reacted into Airframe

	if (Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS])
	{
		FCRD TempRot;
		CopyVec(pModel->RotVel, TempRot);
		TempRot.z += Speed * RotateDirection;

		moment.x = TempRot.x * PropInertia.x;
		moment.y = TempRot.y * PropInertia.y;
		moment.z = TempRot.z * PropInertia.z;
		
		CPrd(moment, moment, TempRot);
		moment.x *= -1;
		moment.y *= -1;
		moment.z *= -1;
	}
	else 
		NullVec(moment);
}	


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ComplexEngineProcess
//Author		Craig Beeston
//Date			Wed 01 Dec 1999
//
//Description	Complex features for the Piston prop engines
//					Magnetos, Fuel cocks, Primer pump, Starter button, Temperature
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Engine::ComplexEngineProcess(AirStrucPtr const ControlledAC, FP fDamage, FP& fPower, FP& dTorque)
{
	FP fuel = 0;														//Check fuel tanks
	for(SWord i = 0; i < 4; i++)
		if((ControlledAC->fly.use_this_tank[i]) && (ControlledAC->fly.fuel_content[i] > 0))
			fuel = 1;

	if((pModel->Type == AT_SPITFIRE) || (pModel->Type == AT_HURRICANE))	//Engines cut-out under negative G
		if(pModel->Inst.I_NormalAcc < 0)
			fuel = 0;

	if(fuel == 0)	FuelInPipes -= 0.010 * MODEL_DT;
	else			FuelInPipes += 0.001 * MODEL_DT;

	MODMAXMIN(FuelInPipes, 0, 1);

	fPower = 1;
	if(FuelInPipes < 0.75)
	{	
		if(FuelInPipes < 0.25)
			fPower = 0;
		else
			if(Math_Lib.rnd(500) > 1000.0 * FuelInPipes - 250.0)
				fPower = 0;
	}

//DeadCode CSB 3Jul00 	fPower *= fDamage;
	if(fDamage < 1.0)
	{
		if(ThrottleSetting > -100.0 + 200.0 * fDamage)
			if(Math_Lib.rnd(200) < ThrottleSetting + 100.0 - 200.0 * fDamage)
				fPower = 0;
	}

	if(ControlledAC != Persons2::PlayerSeenAC)
		return;

	FP MaxSafeThrottle;

	if(Save_Data.flightdifficulty [FD_ENGINEMANAGMENT])
	{
		FP MagFactor = 0.9;
		if(Magnetos == 0)	MagFactor = 0;
		if(Magnetos == 3)	MagFactor = 1;

		fPower *= MagFactor;

		switch(Starter)
		{
			case ES_ELECTRIC:
			{
				if(Starting)
					dTorque += p0 * 0.075;
				break;
			}
			case ES_INERTIA:
			{
				FP DeltaVel = -StarterSpeed;
				if(Starting)
					DeltaVel += 1;
				else
					dTorque += p0 * 0.4 * StarterSpeed;

				StarterSpeed += (DeltaVel * MODEL_ENGINE_DT) / 400.0;
				MODMAXMIN(StarterSpeed, 0, 1);
				break;
			}
		}

		FP frpm = Speed * 954.9296586 / Rpm100;
		if(fPower > 0)
		{
			FP temp = 0.4 - 0.0025 * Temperature;
			if(Priming > 0) 
				temp = 0.15;
//DEADCODE CSB 18/01/00 PrintVar(40, 18, "MinRpm  %.0f ", FP(temp * Rpm100));
			if(frpm < temp)
				fPower = 0;
//DEADCODE CSB 11/01/00 			else
//DEADCODE CSB 11/01/00 				fPower *= 1 - 0.00005 * (100.0 - Temperature) * (100.0 - Temperature);
		}
		Priming -= frpm * MODEL_ENGINE_DT * 0.0075;
		if(Priming < 0)
			Priming = 0;

		FP MaxSafeThrottle = -90.0 + 180.0 * fDamage;
		MODMAXMIN(MaxSafeThrottle, 0, 100);
		FP DesTemp = 100.0 + 2.0 * (ThrottleSetting - MaxSafeThrottle);	//Max Throttle of 90 %
		MODMAXMIN(DesTemp, 100, 150);
		if((Power100 <= 0) || (fPower == 0))	//Engine Stopped
			DesTemp = 0;
		if(Temperature < DesTemp)
			Temperature += (DesTemp - Temperature) * 0.00005 * MODEL_ENGINE_DT;
		else
			Temperature -= Temperature * 0.000025 * MODEL_ENGINE_DT;
	}
	else
	{
		//Automated Stuff
		Magnetos = 3;	//Both ON
		MaxSafeThrottle = -100.0 + 200.0 * fDamage;
		MODMAXMIN(MaxSafeThrottle, 0, 100);
		FP DesTemp = 100.0 + 2.0 * (ThrottleSetting - MaxSafeThrottle);	//Max Throttle of 90 %
		MODMAXMIN(DesTemp, 100, 150);
		if((Power100 <= 0) || (fPower == 0))	//Engine Stopped
			DesTemp = 0;
		if(Temperature < DesTemp)
			Temperature += 0.001 * MODEL_ENGINE_DT;
		else
			Temperature -= 0.001 * MODEL_ENGINE_DT;
	}

	
	AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
	SWord Damage = adptr->ENGINELEFT;
	if(pThrustPoint->Pos.x > 0)
		Damage = adptr->ENGINERIGHT;
	
	if((Damage < 254) && (Temperature > 100) && (Temperature - 100 > Math_Lib.rnd(16384 / MODEL_ENGINE_DT)))
	{
		Damage += 1;
		BitStates BS_Damage = BitStates(Damage);
		if(pThrustPoint->Pos.x > 0)
			SHAPE.ForceDamage(ControlledAC, ControlledAC, &adptr->ENGINERIGHT, BS_Damage);
		else
			SHAPE.ForceDamage(ControlledAC, ControlledAC, &adptr->ENGINELEFT, BS_Damage);

		if(Damage == 254)
			_Miles.PlaySample(FIL_SFX_EXPLOSION_ENGINE);				//RJS 16Oct00
	}

#ifdef ENGINE_DATA																	  
	PrintVar(40, 16, "Primer  %.0f ", FP(pModel->Inst.C_PrimerPump0));
	PrintVar(40, 17, "Priming %.3f ", FP(Priming));
	PrintVar(40, 20, "Temp   %.2f ", FP(Temperature));
	PrintVar(40, 21, "Start  %.3f ", FP(StarterSpeed));
	PrintVar(40, 22, "Fuel   %.3f ", FP(FuelInPipes));
	PrintVar(40, 23, "Power  %.3f ", FP(fPower));
	PrintVar(40, 24, "Damage %.1f ", FP(Damage * 100.0 / 255.0));
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessJetEngine
//Author		Craig Beeston
//Date			Fri 13 Nov 1998
//
//Description	Processes a jet engine
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Engine::ProcessJetEngine (AirStrucPtr const ControlledAC)
{
//JET_Code CSB 22/09/99		if(ControlledAC->weap.centre.int_fuel <= 0)
//JET_Code CSB 22/09/99			EngineOut = TRUE;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		// For turbo jet only.
//JET_Code CSB 22/09/99		PMODEL pModel = ControlledAC->fly.pModel;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		if( (Save_Data.flightdifficulty [FD_JETFLAMEOUT]) && (Manual_Pilot.ControlledAC2 == ControlledAC) )
//JET_Code CSB 22/09/99			if( (pModel->AirSpeed > 15) && (pModel->AirSpeed > -2.0 * pModel->AirVel.z) )	//60 deg cone
//JET_Code CSB 22/09/99	//DeadCode CSB 03/03/99			if ((pModel->AirVel.z > 10) )//&& (pModel->AirSpeed < 20))
//JET_Code CSB 22/09/99				if(!EngineOut)
//JET_Code CSB 22/09/99				{
//JET_Code CSB 22/09/99					AirStrucPtr buddy = ControlledAC->FindBuddy();
//JET_Code CSB 22/09/99					if(buddy)
//JET_Code CSB 22/09/99					{
//JET_Code CSB 22/09/99						if(Math_Lib.rnd(2) == 1)	
//JET_Code CSB 22/09/99							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAMEOUT0, MSG_STATUSRESPONSE_DELAY_LP_RPT, ControlledAC, NULL, buddy));
//JET_Code CSB 22/09/99						else
//JET_Code CSB 22/09/99							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAMEOUT1, MSG_STATUSRESPONSE_DELAY_LP_RPT, ControlledAC, NULL, buddy));
//JET_Code CSB 22/09/99					}
//JET_Code CSB 22/09/99					else
//JET_Code CSB 22/09/99					{
//JET_Code CSB 22/09/99						if(Math_Lib.rnd(2) == 1)	
//JET_Code CSB 22/09/99							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAMEOUT0, MSG_STATUSRESPONSE_DELAY_LP_RPT, ControlledAC, NULL, ControlledAC));
//JET_Code CSB 22/09/99						else
//JET_Code CSB 22/09/99							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FLAMEOUT1, MSG_STATUSRESPONSE_DELAY_LP_RPT, ControlledAC, NULL, ControlledAC));
//JET_Code CSB 22/09/99					}
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99					EngineOut = TRUE;
//JET_Code CSB 22/09/99				}
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		if(EngineOut) ControlledAC->fly.thrustpercent = 0;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		FP Throttle = 0.01 * ControlledAC->fly.thrustpercent;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		FP VeryMinRpm = Rpm100 * WindMillRpm->GetValue(0);
//JET_Code CSB 22/09/99		FP MinVal = 1000;
//JET_Code CSB 22/09/99		if(!EngineOut) MinVal = 0.25 * Rpm100;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		if(VeryMinRpm < MinVal) VeryMinRpm = MinVal;
//JET_Code CSB 22/09/99		if(SpeedRpm < VeryMinRpm) SpeedRpm = VeryMinRpm;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99	//DeadCode CSB 19/11/98		FP RelPres	 = pModel->AmbPres / 10.13;
//JET_Code CSB 22/09/99		FP RelDens	 = pModel->AmbDensity / 0.0001225;
//JET_Code CSB 22/09/99		FP RelTemp	 = pModel->AmbTemp / 288.15;
//JET_Code CSB 22/09/99		
//JET_Code CSB 22/09/99		FP MachFactor =  MachFact->GetValue(pModel->Inst.MachNo);
//JET_Code CSB 22/09/99		Thrust		  =  T100 * ThrustRpm->GetValue(SpeedRpm / (Rpm100 * FSqrt(RelTemp)));
//JET_Code CSB 22/09/99		Thrust  	  *= RelDens * MachFactor;
//JET_Code CSB 22/09/99		if(EngineOut) Thrust = 0;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		FP WindDrag =  T100 * WindMillDrag->GetValue(pModel->AirSpeed);
//JET_Code CSB 22/09/99		Thrust		+= WindDrag;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		AircraftAnimData* adptr = (AircraftAnimData *)ControlledAC->Anim;
//JET_Code CSB 22/09/99		FP fDamage = 1 - adptr->ENGINELEFTIN / 255;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		MaxThrust		 = T100 * RelDens * MachFactor * fDamage;	//Maximum available thrust at present altitude and mach number
//JET_Code CSB 22/09/99		FP DesiredThrust = MaxThrust * Throttle;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		FP ThrottleFactor = 1 - Throttle;
//JET_Code CSB 22/09/99		ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^2
//JET_Code CSB 22/09/99		ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^4
//JET_Code CSB 22/09/99		ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^16
//JET_Code CSB 22/09/99		ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^32
//JET_Code CSB 22/09/99		ThrottleFactor = ThrottleFactor * ThrottleFactor;	//^64
//JET_Code CSB 22/09/99		ThrottleFactor = 1 - ThrottleFactor;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		FP IdleRpm	   = Rpm100 * WindMillRpm->GetValue(pModel->AirSpeed);
//JET_Code CSB 22/09/99		FP DeltaRpm100 = (SpeedRpm / Rpm100) * ThrottleFactor * (DesiredThrust - Thrust);
//JET_Code CSB 22/09/99		FP DeltaRpm0   = (1 - ThrottleFactor) * (IdleRpm - SpeedRpm);
//JET_Code CSB 22/09/99		FP DeltaRpm    = DeltaRpm100 + DeltaRpm0;
//JET_Code CSB 22/09/99		
//JET_Code CSB 22/09/99	//DeadCode CSB 11/12/98		if(Manual_Pilot.ControlledAC2 != ControlledAC)
//JET_Code CSB 22/09/99	//DeadCode CSB 11/12/98		{
//JET_Code CSB 22/09/99	//DeadCode CSB 11/12/98			FP FightingFactor = (FP)ControlledAC->FlyingFactor();
//JET_Code CSB 22/09/99	//DeadCode CSB 11/12/98			FP ThrustInc = (FightingFactor - 128)/256;
//JET_Code CSB 22/09/99	//DeadCode CSB 11/12/98			Thrust *= (1 + ThrustInc);
//JET_Code CSB 22/09/99	//DeadCode CSB 11/12/98		}
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99	//DeadCode CSB 30/11/98		if( (Save_Data.flightdifficulty [FD_POWERBOOST]) && (pModel->Controlled) )
//JET_Code CSB 22/09/99	//DeadCode CSB 30/11/98			Thrust *= pModel->PowerBoost;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		if( (!Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL]) || (Manual_Pilot.ControlledAC2 != ControlledAC) )//(pModel->ACM) )
//JET_Code CSB 22/09/99			DeltaRpm *= 8;//Fast Spooling
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		if((Save_Data.flightdifficulty [FD_THRUSTPOWERCONTROL]) && (Manual_Pilot.ControlledAC2 == ControlledAC))
//JET_Code CSB 22/09/99			if(pModel->Inst.ExhaustTemp > 225)	//Throttle advanced too quickly
//JET_Code CSB 22/09/99			{
//JET_Code CSB 22/09/99				if(pModel->FrameCount & 0x0002)
//JET_Code CSB 22/09/99					DeltaRpm *= -0.5;
//JET_Code CSB 22/09/99				if(Math_Lib.rnd(256) < pModel->Inst.ExhaustTemp - 225) 
//JET_Code CSB 22/09/99					if(adptr->ENGINELEFTIN < 255)
//JET_Code CSB 22/09/99						adptr->ENGINELEFTIN += 1;
//JET_Code CSB 22/09/99	//DeadCode CSB 28/04/99				PrintVar(60, 1, "EGT %.0f ", (FP)pModel->Inst.ExhaustTemp);
//JET_Code CSB 22/09/99	//DeadCode CSB 28/04/99				PrintVar(60, 2, "ENG %.0f ", (FP)adptr->ENGINELEFTIN);
//JET_Code CSB 22/09/99			}
//JET_Code CSB 22/09/99		
//JET_Code CSB 22/09/99		SpeedRpm += T100 * DeltaRpm * pModel->MODEL_DT * OneOverMoI;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99		if( (pModel->Speed < 10) && (Thrust < 0) ) Thrust = 0;
//JET_Code CSB 22/09/99	
//JET_Code CSB 22/09/99	//DeadCode CSB 28/04/99		PrintVar(60, 0, "RPM %.0f ", (FP)SpeedRpm);
}

