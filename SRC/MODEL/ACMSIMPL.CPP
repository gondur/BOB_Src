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



#define F_GRAFIX											//DAW 05Aug96
#define F_COMMON
#define F_BATTLE



#include "collided.h"										//PD 06Sep96
#include "Dosdefs.h"		
#include "Worldinc.h"


#include "modvec.h"
#include "model.h"
#include "acmmodel.h"



#include "FlyModel.h"
#include "mymath.h"
#include "enumbits.m"
#include "mytime.h"											//RDH 25Apr96
#include "ranges.h"
#include "missman2.h"										//JIM 22Aug96
#include "movement.h"
#include "transite.h"
#include "SHAPES.H"


#include "ai.h"
#include "miles.h"											//RDH 25Jul96
#include "landscap.h"										//RDH 18Dec96
#include "viewsel.h"										//RDH 25Jul96
#include "3dcom.h"											//RJS 22Aug96
#include "speed.h"											//RDH 01Oct96
#include "persons2.h"

#include "model.h"




SLong	const	MAXAUTOTHRUST = 100;	
//static 
RequiredBankDataElement 	CombatReqBankData[] =
			{
				{ANGLES_FifthDeg, ANGLES_10Deg},
				{ANGLES_2Deg, ANGLES_20Deg},
				{ANGLES_10Deg, ANGLES_45Deg},
				{ANGLES_45Deg, MAXCOMBATROLL},
				{ANGLES_180BareDeg, MAXCOMBATROLL}
//DeadCode CSB 28/03/99					{ANGLES_FifthDeg, ANGLES_0Deg},
//DeadCode CSB 28/03/99					{ANGLES_HalfDeg, ANGLES_3Deg},
//DeadCode CSB 28/03/99					{ANGLES_1Deg, ANGLES_4Deg},
//DeadCode CSB 28/03/99					{ANGLES_2Deg, ANGLES_5Deg},
//DeadCode CSB 28/03/99					{ANGLES_3Deg, ANGLES_10Deg},
//DeadCode CSB 28/03/99					{ANGLES_4Deg, ANGLES_15Deg},
//DeadCode CSB 28/03/99					{ANGLES_5Deg, ANGLES_22Deg},
//DeadCode CSB 28/03/99					{ANGLES_6Deg, ANGLES_30Deg},
//DeadCode CSB 28/03/99					{ANGLES_10Deg, ANGLES_45Deg},
//DeadCode CSB 28/03/99	//DeadCode RDH 17Jul96 				{ANGLES_22Deg, ANGLES_60Deg},
//DeadCode CSB 28/03/99					{ANGLES_30Deg, MAXCOMBATROLL},
//DeadCode CSB 28/03/99					{ANGLES_180BareDeg, MAXCOMBATROLL}
			};
extern enum ACM_COMMAND;

Float	ACMAirStruc::CalcSimpleAccel ()
{
	if((classtype->aerobaticfactor == AEROBATIC_LOW) || (fly.numinsag))
	{
		INT3;
		return(0);
	}

	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
//	extern enum ACM_COMMAND;
	Float Thrust, Drag, Lift;
	Float mass;		//kg		
	Float accel;
	Float fvel = vel_ * 0.0001;	//m/s
	Float sinroll, cosroll;
	Float N;
//DeadCode CSB 24/09/98		Float	aoa;
//DeadCode CSB 24/09/98		Float	Ps;			//m/s
//DeadCode CSB 24/09/98		Float	area;		//m^2
//DeadCode CSB 24/09/98		Float	CD;
//DeadCode CSB 24/09/98		Float	accel, accelh;
//DeadCode CSB 24/09/98		SWord	sinroll, cosroll, c, s;

//***************************************************************************************
	//CSB 24/09/98
	mass = classtype->weightempty * 0.01;	// -> kg
	for(SWord i = 0; i < 4; i++)	mass += fly.fuel_content[i] * 0.00001;

	PMAINPLANE pMainPlane = MOD.MainPlaneList;

	FP qS = 0.5 * MOD.AmbDensity * /* 10000 * */ fvel * fvel * pMainPlane->Area; //* 0.0001;

	Lift = Model_InstTurnRate(this) * fvel * 100;
	if(Lift < 0)	Lift *= -1;
	MODMAXMIN(Lift, 9.8, (9.0 * 9.8));
	Lift *= mass;
	
//DEADCODE CSB 22/05/00 	Math_Lib.high_sin_cos(roll, sinroll, cosroll);
//DEADCODE CSB 22/05/00 	if(cosroll == 0) 
//DEADCODE CSB 22/05/00 		Lift = mass * 9 * 9.8065;
//DEADCODE CSB 22/05/00 	else
//DEADCODE CSB 22/05/00 		Lift = mass / cosroll * 9.8065;
//DEADCODE CSB 22/05/00 	if(Lift < 0) Lift *= -1;

	if(Lift > 1.0 * qS) Lift = 1.0 * qS;

	Drag = pMainPlane->Cdo * qS + pMainPlane->k * Lift * Lift / qS;

	PENGINE pEngine = MOD.EngineList;

	UByte	FF = FlyingFactor();
//DeadCode CSB 03/06/99		fly.thrustpercent = 70 + (FF * FF * 30)/65536;
	AircraftAnimData*	adptr = (AircraftAnimData *)Anim;

	Float ThrustPercent = -25.0 + 1.25 * fly.thrustpercent;
//DeadCode CSB 25Oct00 	ThrustPercent       *= (255.0 - Float(adptr->ENGINELEFT)) / 255.0;
																							//	  |___
	FP supercharger = 2.0 * (classtype->abs_ceiling - World.Y) / classtype->abs_ceiling;	//	HP|	  \ 
	MODMAXMIN(supercharger, 0, 1);															//	  |_____\___Alt

//JET_Code CSB 21/09/99		if(pEngine->Type == ET_JET)
//JET_Code CSB 21/09/99			Thrust = pEngine->T100 * ThrustPercent * MOD.AmbDensity / 0.0001225 * 0.01;
//JET_Code CSB 21/09/99		else
	if(pEngine)
	{
		FP Power = (255.0 - FP(adptr->ENGINELEFT)) / 255.0 * pEngine->p0;
		if(pEngine->List.NextItem())	Power += (255.0 - FP(adptr->ENGINERIGHT)) / 255.0 * pEngine->List.NextItem()->p0;
		Thrust = Power * ThrustPercent * supercharger / vel_ * (1.05 * 0.01 * 10000.0);
	}
	else
		Thrust = 7457000000 / vel_;	 //1000 HorsePower

	Drag *= (1024 + adptr->LEFTWINGOUT + adptr->LEFTWINGIN + adptr->RIGHTWINGIN + adptr->RIGHTWINGOUT);
	Drag /= 1024;

//DEADCODE CSB 22/05/00 	Drag *= (512.0 - FP(FF)) / 256.0;

//DeadCode CSB 29/04/99		if(!fly.thrustpercent)
//DeadCode CSB 29/04/99			Drag += fvel * fvel;	//AirBrakes
	
	accel = (Thrust - Drag)/mass;
	if(fvel != 0)
		accel -= 9.8065 * 0.0001 * vel_y/fvel ; 

	return(accel);


//***************************************************************************************
	
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcMaxPitchRate
//Author		Craig Beeston 
//Date			Tue 1 June 1999
//
//Description	Calculates the maximum pitch rate for a simple movecode
//				Limited by G and stall limit
//
//Inputs		
//
//Returns		Max Pitch rate in Rowans per second
//
//------------------------------------------------------------------------------
UWord AirStruc::CalcMaxPitchRate()
{
	if(classtype->aerobaticfactor == AEROBATIC_LOW)
		return(classtype->maxpitchrate);

	FP ff = 0.5 + FlyingFactor() / 512.0;
	ULong pitchrateMG = (1023000000.0 * 7.0 * ff) / FP(vel_);	//rowans/sec for max g

	SWord maxrotrate = ANGLES_45Deg;
	switch(classtype->visible)
	{
		case SPIT:	maxrotrate = 46 * 182;	break;
		case HURR:	maxrotrate = 39 * 182;	break;
		case DEF:	maxrotrate = 29 * 182;	break;
		case ME109:	maxrotrate = 41 * 182;	break;	//Slots Open		//CSB 22Sep00	
		case ME110:	maxrotrate = 40 * 182;	break;	//Slots Open		//CSB 22Sep00
//DeadCode CSB 22Sep00 		case ME109:	maxrotrate = 33 * 182;	break;
//DeadCode CSB 22Sep00 		case ME110:	maxrotrate = 32 * 182;	break;
		case JU87:	maxrotrate = 28 * 182;	break;
	}

 	FP maxpitchrate = ff * maxrotrate * vel_ * fly.pModel->AmbDensity / (0.0001225 * classtype->maxvel);
	//Pretty good figure for all Bob Aircraft	//CSB 20/01/00

	if(maxpitchrate > pitchrateMG) 
		maxpitchrate = pitchrateMG;

	if(!fly.numinsag)
	{
		AircraftAnimData* adptr = (AircraftAnimData*) Anim;
		FP damage = FP(adptr->LEFTWINGOUT + adptr->LEFTWINGIN + adptr->RIGHTWINGIN + adptr->RIGHTWINGOUT) * (1.0 / 1024.0);
		maxpitchrate *= (1.0 - damage);
	}
//DeadCode CSB 7Sep00 	if(classtype->aerobaticfactor == AEROBATIC_MEDIUM)					//CSB 1Aug00
//DeadCode CSB 7Sep00 		maxpitchrate *= 0.5;											//CSB 1Aug00

	return((UWord)maxpitchrate);
}


//DeadCode CSB 29/03/99	//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 29/03/99	//Procedure		TurnFight
//DeadCode CSB 29/03/99	//Author		R. Hyde 
//DeadCode CSB 29/03/99	//Date			Fri 13 Mar 1998
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Description	
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Inputs		
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//Returns	
//DeadCode CSB 29/03/99	//
//DeadCode CSB 29/03/99	//------------------------------------------------------------------------------
//DeadCode CSB 29/03/99	void	AirStruc::SimpleTurningFight()
//DeadCode CSB 29/03/99	{
//DeadCode CSB 29/03/99		SWord	reqdeltahdg,reqdeltahdg_sign;
//DeadCode CSB 29/03/99		UWord	reqdeltahdg_pos;
//DeadCode CSB 29/03/99		COORDS3D	target;
//DeadCode CSB 29/03/99		MODEL& MOD = *fly.pModel;
//DeadCode CSB 29/03/99		AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 29/03/99		SLong vx, vy, vz;
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		reqdeltahdg = 	hdg - HdgIntercept;
//DeadCode CSB 29/03/99		Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		if (!ai.unfriendly)			//AMM13nov98
//DeadCode CSB 29/03/99			return;			//AMM13nov98
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		if (	(reqdeltahdg_pos < (SWord)ANGLES_90Deg)
//DeadCode CSB 29/03/99			)		
//DeadCode CSB 29/03/99		{
//DeadCode CSB 29/03/99			CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99			target.X = ai.unfriendly->World.X + vx;
//DeadCode CSB 29/03/99			target.Y = ai.unfriendly->World.Y + vy;
//DeadCode CSB 29/03/99			target.Z = ai.unfriendly->World.Z + vz;
//DeadCode CSB 29/03/99			InterceptandRange (&target);
//DeadCode CSB 29/03/99		}else
//DeadCode CSB 29/03/99			target = ai.unfriendly->World;
//DeadCode CSB 29/03/99		if (		(classtype->visible == MIG15)
//DeadCode CSB 29/03/99				&&	(		(ai.combatskill >= SKILL_ACE)
//DeadCode CSB 29/03/99						||	(ai.morale < MORALE_GOOD)
//DeadCode CSB 29/03/99					)
//DeadCode CSB 29/03/99			)
//DeadCode CSB 29/03/99			SimpleTurnWithPitchChange(HdgIntercept, FALSE, target);
//DeadCode CSB 29/03/99		else
//DeadCode CSB 29/03/99			SimpleTurnWithPitchChange(HdgIntercept, TRUE, target);
//DeadCode CSB 29/03/99	}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnFight
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleTurningFight()
{
	if((ai.unfriendly) && (AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW))
	{
		SimpleTurningFightBomber();
		return;
	}

	switch(ai.ManStep)
	{
		case 0:
		{
			SetManoeuvreTime(1500);
			ai.ManStep = 1;
		}
		case 1:
		{
			COORDS3D	target;
			MODEL& MOD = *fly.pModel;
			ACMMODEL& ACM = *fly.pAcmModel;
			AirStrucPtr	unfriendly = *ai.unfriendly;
			SLong vx, vy, vz;
			SWord	reqdeltahdg,reqdeltahdg_sign;
			UWord	reqdeltahdg_pos;
			SWord	reqdeltapitch,reqdeltapitch_sign;
			UWord	reqdeltapitch_pos;
			
			if (!ai.unfriendly)		
				return;			

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 			{
//DeadCode CSB 5Sep00 				if(TimeToChangeToDisengage())
//DeadCode CSB 5Sep00 					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 				SetManoeuvreTime(1500);
//DeadCode CSB 5Sep00 			}

			AirStrucPtr unf = AirStrucPtr(ai.unfriendly);

			target.X = ai.unfriendly->World.X;
			target.Y = ai.unfriendly->World.Y;
			target.Z = ai.unfriendly->World.Z;
			InterceptandRange (&target);

			reqdeltahdg   =	HdgIntercept - hdg;
			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
			SimpleMoveToThrust (ThrustfromFF());							  //RDH 06/05/99

		//DeadCode CSB 03/06/99		if((reqdeltahdg_pos < ANGLES_90Deg) && (Range < ENGAGERANGE))
			if((reqdeltahdg_pos < ANGLES_45Deg) && (Range < WEAPONSRANGE))
			{
		//DEADCODE CSB 04/05/00 		if (	(classtype->phrasename == OLDPHRASE_MIGS)
		//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 		if( (classtype->visible == MIG15)
		//DEADCODE CSB 04/05/00 			&& ((ai.combatskill >= SKILL_ACE) || (ai.morale < MORALE_GOOD)) )
		//DEADCODE CSB 04/05/00 			if(reqdeltahdg_pos < ANGLES_90Deg)
		//DEADCODE CSB 04/05/00 			{
		//DEADCODE CSB 04/05/00 				if	(		(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)			  //RDH 04/07/99
		//DEADCODE CSB 04/05/00 						&&	(unfriendly->classtype->aerobaticfactor != AEROBATIC_LOW)						
		//DEADCODE CSB 04/05/00 					)
		//DEADCODE CSB 04/05/00 				{
		//DEADCODE CSB 04/05/00 					if(Range < WEAPONSRANGE)
		//DEADCODE CSB 04/05/00 						SimpleMoveToThrust(0);
		//DEADCODE CSB 04/05/00 					else
		//DEADCODE CSB 04/05/00 						SimpleMoveToThrust (ThrustfromFF());
		//DEADCODE CSB 04/05/00 					if(Range < 0.5 * WEAPONSRANGE)
		//DEADCODE CSB 04/05/00 						ACM.SpeedBrakesOut();
		//DEADCODE CSB 04/05/00 					else
		//DEADCODE CSB 04/05/00 						ACM.SpeedBrakesIn();
		//DEADCODE CSB 04/05/00 				}
		//DEADCODE CSB 04/05/00 			}

				CalcLead(*this, *ai.unfriendly,vx,vy,vz, FALSE);
				target.X = ai.unfriendly->World.X + vx;
				target.Y = ai.unfriendly->World.Y + vy;
				target.Z = ai.unfriendly->World.Z + vz;
				InterceptandRange (&target);

				if(unf->classtype->aerobaticfactor > AEROBATIC_LOW)
				{
					reqdeltahdg   =	HdgIntercept - hdg;
					reqdeltapitch =	PitchIntercept - pitch;
					Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
					Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
			//DeadCode CSB 06/04/99	PrintVar(60, 5, "DeltaPitch %.0f ", (FP)( (PitchIntercept - pitch) / 182.04) );
			//DeadCode CSB 06/04/99	PrintVar(60, 6, "DeltaHeadg %.0f ", (FP)( (HdgIntercept - hdg) / 182.04) );
			//DeadCode CSB 06/04/99	PrintVar(60, 7, "Targ Range %.0f ", (FP)( (Range) / 100.0) );
				
					if(reqdeltapitch != 0)
					{
						SWord DesRoll = Math_Lib.arctan(reqdeltahdg, reqdeltapitch);
						SimpleMoveToRoll(DesRoll);
					}

					SWord sin_roll, cos_roll;
					Math_Lib.high_sin_cos(roll, sin_roll, cos_roll);
			//DeadCode CSB 01/06/99			FP MaxDeltaPitch = (FP)classtype->maxpitchrate * (FP)Timer_Code.FRAMETIME / 100.0 / 32768.0;
					FP MaxDeltaPitch = (FP)CalcMaxPitchRate() * (FP)Timer_Code.FRAMETIME / (100.0 * 32768.0);
					FP MaxDeltaYaw   = MaxDeltaPitch * sin_roll;
					MaxDeltaPitch	 = MaxDeltaPitch * cos_roll;

					SWord	maxdeltapitch_sign, maxdeltayaw_sign;
					UWord	maxdeltapitch_pos,  maxdeltayaw_pos;
					Math_Lib.Pos((SWord)MaxDeltaPitch, maxdeltapitch_pos, maxdeltapitch_sign);
					Math_Lib.Pos((SWord)MaxDeltaYaw  , maxdeltayaw_pos,   maxdeltayaw_sign);
					FP factor1 = 1, factor2 = 1;
					if(maxdeltapitch_pos > reqdeltapitch_pos) factor1 = reqdeltapitch_pos / maxdeltapitch_pos;
					if(maxdeltayaw_pos   > reqdeltahdg_pos)   factor2 = reqdeltahdg_pos / maxdeltayaw_pos;
					if(factor1 > factor2) factor1 = factor2;
					pitch += SWord((FP)MaxDeltaPitch * (FP)factor1);
					hdg   += SWord((FP)MaxDeltaYaw   * (FP)factor1);
					fly.cpitch = pitch;

					hdg -= (Angles) CalcHdg ();	//This means that all the heading change is done inside this routine
				}
				else
				{
					PitchIntercept -= SByte(timeofday * 2);
					HdgIntercept   += SByte(timeofday);
					AutoCalcPitch();
					SLong desroll = 5 * SWord(HdgIntercept - hdg);
					MODLIMIT(desroll, ANGLES_60Deg);
					SimpleMoveToRoll(desroll);
				}
			}
			else
			{
					AutoCalcPitch();
					SLong desroll = 10 * SWord(HdgIntercept - hdg);
					MODLIMIT(desroll, ANGLES_75_5Deg);
					SimpleMoveToRoll(desroll);
		//DeadCode CSB 21Jun00 		if((roll > ANGLES_90Deg) || (roll < ANGLES_270Deg))
		//DeadCode CSB 21Jun00 			SimpleMoveToRoll(0);
		//DeadCode CSB 21Jun00 		else
		//DeadCode CSB 21Jun00 			SimpleMoveToHdg (HdgIntercept);	
		//DeadCode CSB 21Jun00 		AutoCalcPitch();
			}
			
			if	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)			  //RDH 04/07/99
			{
				if((reqdeltahdg_pos < ANGLES_10Deg) && (reqdeltapitch_pos < ANGLES_10Deg))
				{
					advantage = TRUE;
					disadvantage = FALSE;
					MoraleMod();
					SetManoeuvreTime (1000);
				}

				if (		(fly.leadflight)					
						&&	 (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
					)//force manoeuvre to allow disengage
						ai.manoeuvre = MANOEUVRE_SELECT;

				if(!TimeLeft())
				{
					if(    (World.Y < FT_1000)
						|| (Range > ENGAGERANGE)
						|| (pitch > ANGLES_30Deg)
						|| (pitch < ANGLES_330Deg) )
						ai.manoeuvre = MANOEUVRE_SELECT;
				}
				if((unf->classtype->aerobaticfactor != AEROBATIC_LOW) && (Math_Lib.rnd(65536) < (256 - FlyingFactor()) / 16))	//Poor skill -> every 20 secs
					ai.manoeuvre = MANOEUVRE_SCISSORS;
			}
		}
	}
}				

//DeadCode CSB 29/03/99		reqdeltahdg = 	hdg - HdgIntercept;
//DeadCode CSB 29/03/99		Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		if (!ai.unfriendly)			//AMM13nov98
//DeadCode CSB 29/03/99			return;			//AMM13nov98
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99		if (	(reqdeltahdg_pos < (SWord)ANGLES_90Deg)
//DeadCode CSB 29/03/99			)		
//DeadCode CSB 29/03/99		{
//DeadCode CSB 29/03/99			CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);
//DeadCode CSB 29/03/99	
//DeadCode CSB 29/03/99			target.X = ai.unfriendly->World.X + vx;
//DeadCode CSB 29/03/99			target.Y = ai.unfriendly->World.Y + vy;
//DeadCode CSB 29/03/99			target.Z = ai.unfriendly->World.Z + vz;
//DeadCode CSB 29/03/99			InterceptandRange (&target);
//DeadCode CSB 29/03/99		if (		(classtype->visible == MIG15)
//DeadCode CSB 29/03/99				&&	(		(ai.combatskill >= SKILL_ACE)
//DeadCode CSB 29/03/99						||	(ai.morale < MORALE_GOOD)
//DeadCode CSB 29/03/99					)
//DeadCode CSB 29/03/99			)
//DeadCode CSB 29/03/99			SimpleTurnWithPitchChange(HdgIntercept, FALSE, target);
//DeadCode CSB 29/03/99		else
//DeadCode CSB 29/03/99			SimpleTurnWithPitchChange(HdgIntercept, TRUE, target);
//DeadCode CSB 29/03/99	}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleTurningFightBomber
//Author		Craig Beeston
//Date			Tue 10 Oct 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleTurningFightBomber()
{
	switch(ai.ManStep)
	{
		case 0:
		{
			SetManoeuvreTime(1500);
			ai.ManStep = 1;
		}
		case 1:
		{
			AirStrucPtr	unf = AirStrucPtr(ai.unfriendly);
			if(!unf)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
				return;
			}

			SimpleMoveToThrust(100);

			if(Distance3DSquared(&unf->World) < FP(INSIDEWEAPONSRANGE) * FP(INSIDEWEAPONSRANGE))
			{
				SLong dx, dy, dz;
				CalcLead(this, unf, dx, dy, dz, FALSE);
				despos.X = unf->World.X + dx;
				despos.Y = unf->World.Y + dy;
				despos.Z = unf->World.Z + dz;
			}
			else
			{
				FP deltas = FP(unf->vel_x) * FP(unf->World.X - World.X) + FP(unf->vel_y) * FP(unf->World.Y - World.Y) + FP(unf->vel_z) * FP(unf->World.Z - World.Z);
				deltas /= FP(unf->vel_);
				FP deltav = FP(vel_x) * FP(unf->vel_x) + FP(vel_y) * FP(unf->vel_y) + FP(vel_z) * FP(unf->vel_z);
				deltav = deltav / FP(unf->vel_) - FP(unf->vel_);
				FP time = 1.25 * deltas / deltav;
				if(deltav < 0)
					time = 0;
				else
					MODMAXMIN(time, 0, 100); 
				despos = unf->World;
				despos.X = FP(despos.X) + time * FP(unf->vel_x);
				despos.Y = FP(despos.Y) + time * FP(unf->vel_y);
				despos.Z = FP(despos.Z) + time * FP(unf->vel_z);
			}
			
			InterceptandRange(&despos);

			if(Range < INSIDEWEAPONSRANGE)
			{
				FP delta = (448.0 - ai.combatskill) * SByte(timeofday * 2) / 128.0;
				PitchIntercept += delta;
				delta = (448.0 - ai.combatskill) * SByte(timeofday) / 128.0;
				HdgIntercept += delta;
			}
			AutoCalcPitch();
			SLong desroll = 5 * SWord(HdgIntercept - hdg);
			MODLIMIT(desroll, ANGLES_75_5Deg);
			SimpleMoveToRoll(desroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}				


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
void	ACMAirStruc::SimpleTurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target)
{
//DEADCODE CSB 22/05/00 	if (CombatFactor() > 200)
//DEADCODE CSB 22/05/00 	{
//DEADCODE CSB 04/05/00 		if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 		if (classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 			SimpleTurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_5Deg, target);	
//DEADCODE CSB 04/05/00 		else 
//DEADCODE CSB 22/05/00 		if (World.Y > FT_10000)
//DEADCODE CSB 22/05/00 			SimpleTurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	
//DEADCODE CSB 22/05/00 		else
//DEADCODE CSB 22/05/00 			SimpleTurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	
//DEADCODE CSB 22/05/00 
//DEADCODE CSB 22/05/00 	}else
		SimpleTurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnFightSub
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleTurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target)
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	

	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;
	FP desiredturn;
	SLong		time;

	reqdeltahdg = 	hdg - HdgIntercept;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (1000);
			ACM.maxdeltaforclosework = 0.0;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.MinHeight (FT_2000);
 			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
			reqdeltapitch = PitchIntercept - fly.cpitch;//	fly.cpitch - PitchIntercept;		//CHECK THIS !!!!
			Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);

			ANGLES delta = unfriendly->hdg + ANGLES_180Deg + ANGLES_30Deg - hdg;

			{
				if (sitbehindtarget)
					SlowDown(reqdeltahdg_pos);
	
				SimpleTurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, deltapitch);

				if  (		(!ManoeuvreTimeLeft())
					)
				{
					if	(ACM.maxdeltaforclosework <= 0.1)
						ai.manoeuvre = MANOEUVRE_SELECT;
					else
					{
						if (		(fly.leadflight)					
								&&	 (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
							)//force manoeuvre to allow disengage
						{
								ai.manoeuvre = MANOEUVRE_SELECT;
						}else
						{//on tail of target so keep in manoeuvre and up morale
							advantage = TRUE;
							disadvantage = FALSE;
							MoraleMod();
							SetManoeuvreTime (1000);
						}
					}
				}
			}
		}
	}

}
void	ACMAirStruc::SimpleTurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos, ANGLES	deltapitch)
{

	SWord delta;
	SWord reqroll;
	SWord dpitch;

	SWord PI = PitchIntercept;
	if  (		(PI < 0)
			&&	(Range > WEAPONSRANGE)
		)
		PI = 0;
	delta = PI + deltapitch;
	if  (		(delta < ANGLES_0Deg)
			&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
			&&	(deltapitch << ANGLES_180Deg)				//if he really wants to go down then let him
			&&	(		(Range > WEAPONSRANGE)
//DEADCODE CSB 04/05/00 					||	(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE RDH 10/05/99 					||	(classtype->visible == MIG15)
						
				)
		)	
		delta = ANGLES_0Deg;
	reqdeltapitch = 	delta - fly.cpitch;
	Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
	if (reqdeltapitch_pos > ANGLES_40Deg)
		dpitch = ANGLES_40Deg;
	else
		dpitch = reqdeltapitch_pos;
	if (reqdeltapitch_sign < 0)
		dpitch = - dpitch;

	
	SimpleMoveToHdg (HdgIntercept);	
	PitchIntercept = (Angles) dpitch;
	AutoCalcPitch();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChkAtDesiredHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::ChkAtDesiredHdg (ANGLES desiredhdg,ANGLES target)

{
	SWord deltahdg;
	UWord	deltahdg_pos;
	SWord	deltahdg_sign;

	deltahdg = desiredhdg -	hdg;
	Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
	if (deltahdg_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChkAtDesiredHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::ChkAtDesiredRoll (ANGLES desiredroll,ANGLES target)

{
	SWord deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;

	deltaroll = desiredroll -	roll;
	Math_Lib.Pos (((SWord)deltaroll),deltaroll_pos,deltaroll_sign);
	if (deltaroll_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}
}
 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DesiredPitchChk
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	ACMAirStruc::DesiredPitchChk (ANGLES desiredpitch,ANGLES target)

{
	SWord deltapitch;
	UWord	deltapitch_pos;
	SWord	deltapitch_sign;

	deltapitch = desiredpitch -	fly.cpitch;
	Math_Lib.Pos (((SWord)deltapitch),deltapitch_pos,deltapitch_sign);
	if (deltapitch_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DesiredAcPitchChk
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	ACMAirStruc::DesiredAcPitchChk (ANGLES desiredpitch,ANGLES target)

{
	SWord deltapitch;
	UWord	deltapitch_pos;
	SWord	deltapitch_sign;

	deltapitch = desiredpitch -	pitch;
	Math_Lib.Pos (((SWord)deltapitch),deltapitch_pos,deltapitch_sign);
	if (deltapitch_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChkAtDesiredAcHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::ChkAtDesiredAcHdg (ANGLES desiredhdg,ANGLES target)

{
	SWord deltahdg;
	UWord	deltahdg_pos;
	SWord	deltahdg_sign;

	deltahdg = desiredhdg -	hdg;
	Math_Lib.Pos (((SWord)deltahdg),deltahdg_pos,deltahdg_sign);
	if (deltahdg_pos < target)
	{
		return (TRUE);
	}else
	{
		return (FALSE);
	}
}

void  ACMAirStruc::SimpleMakeForFriendly()
{
}
void  ACMAirStruc::SimpleImmelmann()
{
}

void  ACMAirStruc::SimpleGainSpeed()
{
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (500);
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToRoll (ANGLES_0Deg);
			if (World.Y < FT_1000)
				PitchIntercept =  ANGLES_0Deg;
			else
				PitchIntercept =  ANGLES_350Deg;
			AutoCalcPitch();

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeadUnFriendly
//Author		R. Hyde 
//Date			Fri 15 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLeadUnFriendly ()
{

	COORDS3D	target;
	SLong		t,actualrange;
	AirStrucPtr	unfriendly = *ai.unfriendly;

			target.X = ai.unfriendly->World.X;
			target.Y = ai.unfriendly->World.Y;
			target.Z = ai.unfriendly->World.Z;
			InterceptandRange (&target);
			actualrange = Range;

			//closing velocity
 			SLong deltax = vel_x - unfriendly->vel_x;
 			SLong deltay = vel_y - unfriendly->vel_y;
 			SLong deltaz = vel_z - unfriendly->vel_z;
 			Math_Lib.Intercept (deltax,deltay,deltaz,Range,HdgIntercept,PitchIntercept);
 			//Range is a velocity in 1/10000m/s
 			if (Range != 0)
 			{
 				t = actualrange / (Range * 10000);
 			}else
 			{
 				t = 0;
 			}
 			//when a long way off don't attempt to lead
 			if (t >20000)
 			t = 0;
 
 			target.X = ai.unfriendly->World.X + (unfriendly->vel_x * t / 10000);
 			target.Y = ai.unfriendly->World.Y + (unfriendly->vel_y * t / 10000);
 			target.Z = ai.unfriendly->World.Z + (unfriendly->vel_z * t / 10000);
			InterceptandRange (&target);
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GatherSpeed
//Author		R. Hyde 
//Date			Fri 15 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleGatherSpeed ()

{
	COORDS3D	target;

		target.X = ai.unfriendly->World.X;
		target.Y = ai.unfriendly->World.Y;
		target.Z = ai.unfriendly->World.Z;
		InterceptandRange (&target);
		PitchIntercept = ANGLES_330Deg;
		AutoCalcPitch();
 		SimpleMoveToHdg (HdgIntercept);
}



//Simple acm routines											//RDH 11Oct96

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleTopCover
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	The followers are supposed to go near to home line or
//				not depending on skill
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleTopCover ()
{
	if(formpos == 0)
	{
		switch(ai.ManStep)
		{
			case PHASE0:
			{
				SimpleMoveToThrust(90);
				ai.desiredroll = Angles(ANGLES_30Deg - ANGLES_60Deg * Math_Lib.rnd(2));
				SetManoeuvreTime(3000);
				ai.ManStep = PHASE1;
			}
			
			case PHASE1:
			{
				SimpleMoveToRoll(ai.desiredroll);
				PitchIntercept = BestClimbAngle();
				AutoCalcPitch();
				
				if(!TimeLeft())
				{
					if(AllOnTopCover())			
						Art_Int.AllBreakOff(this);
					else						
						SetManoeuvreTime(1500);
				}
			}
		}
	}
	else
	{
		switch(ai.ManStep)
		{
			case PHASE0:
			{
				ai.ManStep = PHASE1;
			}

			case PHASE1:
			{
		  		AirStrucPtr lead = FindGroupLeader();
				if(lead == Persons2::PlayerGhostAC)
					Art_Int.BreakOff(this);

				lead = FindLeadCandidate();
				SimpleFlyWing(lead);
			}
		}

	}






//DEADCODE CSB 13/03/00 	if (formpos == 0)
//DEADCODE CSB 13/03/00 	{//leader
//DEADCODE CSB 13/03/00 		switch (ai.ManStep)
//DEADCODE CSB 13/03/00 		{
//DEADCODE CSB 13/03/00 			case PHASE0:
//DEADCODE CSB 13/03/00 			{
//DEADCODE CSB 13/03/00  				SimpleMoveToThrust (100);
//DEADCODE CSB 13/03/00 				SetManoeuvreTime (500);
//DEADCODE CSB 13/03/00 				ai.desiredroll = - (ANGLES)ANGLES_30Deg +
//DEADCODE CSB 13/03/00  							(Angles)(ANGLES_60Deg * Math_Lib.rnd(2)); 
//DEADCODE CSB 13/03/00 				ai.ManStep = PHASE1;
//DEADCODE CSB 13/03/00 			}
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 			case PHASE1:
//DEADCODE CSB 13/03/00 			{
//DEADCODE CSB 13/03/00 				SimpleTightClimbingTurn (ANGLES_5Deg);
//DEADCODE CSB 13/03/00 				if(!ManoeuvreTimeLeft())
//DEADCODE CSB 13/03/00 				{
//DEADCODE CSB 13/03/00 					SetManoeuvreTime (500);
//DEADCODE CSB 13/03/00 					ai.ManStep = PHASE2;
//DEADCODE CSB 13/03/00  				}
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 				break;
//DEADCODE CSB 13/03/00 			}
//DEADCODE CSB 13/03/00 			case PHASE2:
//DEADCODE CSB 13/03/00 			{
//DEADCODE CSB 13/03/00 				SimpleTightClimbingTurn (ANGLES_0Deg);
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 				if (!ManoeuvreTimeLeft())
//DEADCODE CSB 13/03/00 				{
//DEADCODE CSB 13/03/00 					ai.ManStep = PHASE3;
//DEADCODE CSB 13/03/00  				}
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 				break;
//DEADCODE CSB 13/03/00 			}
//DEADCODE CSB 13/03/00 			case PHASE3:
//DEADCODE CSB 13/03/00 			{
//DEADCODE CSB 13/03/00 				SimpleTightClimbingTurn (ANGLES_0Deg);
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 				if(AllOnTopCover())									//JIM 25Nov96
//DEADCODE CSB 13/03/00 					Art_Int.AllBreakOff(this);	//fly.leadflight);	//JIM 25Nov96
//DEADCODE CSB 13/03/00 				else												//JIM 25Nov96
//DEADCODE CSB 13/03/00 				{
//DEADCODE CSB 13/03/00 		    		ai.ManStep = PHASE1;
//DEADCODE CSB 13/03/00 					SetManoeuvreTime (1000);
//DEADCODE CSB 13/03/00 				}
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 				break;
//DEADCODE CSB 13/03/00 			}
//DEADCODE CSB 13/03/00   		}
//DEADCODE CSB 13/03/00 	}else
//DEADCODE CSB 13/03/00 	{
//DEADCODE CSB 13/03/00   		AirStruc* leader = FindGroupLeader();
//DEADCODE CSB 13/03/00 		if (leader == Persons2::PlayerGhostAC)
//DEADCODE CSB 13/03/00 			Art_Int.BreakOff(this);
//DEADCODE CSB 13/03/00 		else
//DEADCODE CSB 13/03/00 		{
//DEADCODE CSB 13/03/00 			switch (ai.ManStep)
//DEADCODE CSB 13/03/00 			{
//DEADCODE CSB 13/03/00 				case PHASE0:
//DEADCODE CSB 13/03/00 				{
//DEADCODE CSB 13/03/00  					SimpleMoveToThrust (100);
//DEADCODE CSB 13/03/00 					SetManoeuvreTime (500);
//DEADCODE CSB 13/03/00 					ai.desiredroll = -(ANGLES)ANGLES_30Deg +
//DEADCODE CSB 13/03/00  								(Angles)(ANGLES_60Deg * Math_Lib.rnd(2)); 
//DEADCODE CSB 13/03/00 					ai.ManStep = PHASE1;
//DEADCODE CSB 13/03/00 				}
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 				case PHASE1:
//DEADCODE CSB 13/03/00 				{
//DEADCODE CSB 13/03/00 		//DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_10Deg);
//DEADCODE CSB 13/03/00 					SimpleTightClimbingTurn (ANGLES_5Deg);				//RDH 13Dec96
//DEADCODE CSB 13/03/00 					if (!ManoeuvreTimeLeft())
//DEADCODE CSB 13/03/00 					{
//DEADCODE CSB 13/03/00 						SetManoeuvreTime (1000);
//DEADCODE CSB 13/03/00 						ai.ManStep = PHASE2;
//DEADCODE CSB 13/03/00  					}
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 					break;
//DEADCODE CSB 13/03/00 				}
//DEADCODE CSB 13/03/00 				case PHASE2:
//DEADCODE CSB 13/03/00 				{
//DEADCODE CSB 13/03/00 					if (fly.leadflight->World.Y > World.Y)
//DEADCODE CSB 13/03/00 						SimpleTightClimbingTurn (ANGLES_0Deg);
//DEADCODE CSB 13/03/00 					else
//DEADCODE CSB 13/03/00 						SimpleTightClimbingTurn (ANGLES_5Deg);
//DEADCODE CSB 13/03/00 					break;
//DEADCODE CSB 13/03/00 				}
//DEADCODE CSB 13/03/00   			}
//DEADCODE CSB 13/03/00 		}
//DEADCODE CSB 13/03/00 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleForceTopCover
//Author		Craig Beeston
//Date			Thu 09 Mar 2000
//
//Description	Real top cover without trying to disengage
//				Circles above "coveree" and checks if they need help every X secs
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleForceTopCover()
{
	//Find me somebody to follow
	AirStrucPtr lead = Leader();
	if(formpos)
		for(AirStrucPtr ld = fly.leadflight; (ld) && (!lead); ld = ld->fly.nextflight)
			if(ld->ai.manoeuvre == MANOEUVRE_FORCETOPCOVER)
				lead = ld;

	if((lead) && (lead->ai.manoeuvre == MANOEUVRE_FORCETOPCOVER))
	{
		SimpleFlyWing(lead);
		return;
	}

	//Find me somebody to cover
	AirStrucPtr coveree = NULL;
	for(lead = FindFormpos0(); (lead) && (!coveree); lead = lead->fly.nextflight)
		if(lead->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER)
			coveree = lead;

	if(!formpos)
	{
		if(fly.leadflight)
		{
			lead = fly.leadflight->GetLeadAc();
			if((lead->movecode == AUTO_COMBAT) || (lead->movecode == AUTO_PRECOMBAT))
				if(lead->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER)
					coveree = lead;
		}
			
		if(!coveree)
		{
			lead = Art_Int.FindEscort(this);
			if(lead)
			{
				lead = lead->GetLeadAc();
				if((lead->movecode == AUTO_COMBAT) || (lead->movecode == AUTO_PRECOMBAT))
					if(lead->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER)
						coveree = lead;
			}
		}
	}

	if(!coveree)
	{
		if(follower)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_DISENGAGE_DELAY_LP_RPT, *this, NULL, Follower()));

		for(AirStrucPtr nf = this; nf; nf = nf->fly.nextflight)
			for(AirStrucPtr ac = nf; ac; ac = ac->Follower())
			{
				ac->SetUnfriendly(NULL);
//DeadCode CSB 1Aug00 				if((ac->ai.unfriendly) && (ac->ai.unfriendly->Status.size == AIRSTRUCSIZE) && (AirStrucPtr(ac->ai.unfriendly)->ai.attacker == ac))
//DeadCode CSB 1Aug00 					AirStrucPtr(ac->ai.unfriendly)->ai.attacker = NULL;
//DeadCode CSB 1Aug00 				ac->ai.unfriendly = NULL;
				ac->movecode = AUTO_FOLLOWWP;
				ac->information = IF_OUT_POS;					//CSB 22Aug00
				ac->manoeuvretime = 0;
				ac->ai.manoeuvre = MANOEUVRE_SELECT;
			}
		return;
	}

	if(coveree->ai.manoeuvre == MANOEUVRE_TOPCOVER)
		ai.manoeuvre = MANOEUVRE_SELECT;

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			fly.thrustpercent = 90;
			ai.desiredalt = coveree->World.Y + FT_2500;
			ai.ManStep = PHASE1;
			SetManoeuvreTime(3000);
		}

		case PHASE1:
		{
//DEADCODE CSB 10/03/00 			Move().AutoOrbit(coveree->World, METRES500);
			InterceptandRange(coveree);

			SimpleMoveToHdg(HdgIntercept);
			if(SWord(roll) > ANGLES_60Deg)
				roll = Angles(ANGLES_60Deg);
			if(SWord(-roll) > ANGLES_60Deg)
				roll = Angles(-ANGLES_60Deg);

			FP fpitch = FP(ai.desiredalt - World.Y) / FP(FT_100);
			MODLIMIT(fpitch, FP(vel_) / FP(classtype->bestclimbvel));
			PitchIntercept = Angles(SWord(FP(CalcBestClimbPitch()) * fpitch));
			AutoCalcPitch();

//DEADCODE CSB 10/03/00 			hdg -= Angles(CalcHdg());	//This means that all the heading change is done inside this routine

			if(!TimeLeft())
			{
				if(coveree->movecode == AUTO_FOLLOWWP)
				{
					if(follower)
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_DISENGAGE_DELAY_LP_RPT, *this, NULL, Follower()));

					for(AirStrucPtr nf = this; nf; nf = nf->fly.nextflight)
						for(AirStrucPtr ac = nf; ac; ac = ac->Follower())
						{
							ac->SetUnfriendly(NULL);					//CSB 1Aug00
//DeadCode CSB 1Aug00 							if((ac->ai.unfriendly) && (ac->ai.unfriendly->Status.size == AIRSTRUCSIZE) && (AirStrucPtr(ac->ai.unfriendly)->ai.attacker == ac))
//DeadCode CSB 1Aug00 								AirStrucPtr(ac->ai.unfriendly)->ai.attacker = NULL;
//DeadCode CSB 1Aug00 							ac->ai.unfriendly = NULL;
							ac->movecode = AUTO_FOLLOWWP;
							ac->information = IF_OUT_POS;					//CSB 22Aug00
							ac->manoeuvretime = 0;
						}
					return;
				}

//DeadCode CSB 7Sep00 				SWord attacking = 0;
//DeadCode CSB 7Sep00 				for(AirStrucPtr nf = coveree; (nf) && (nf->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER); nf = nf->fly.nextflight)
//DeadCode CSB 7Sep00 					for(AirStrucPtr ac = nf; (ac) && (ac->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER); ac = ac->Follower())
//DeadCode CSB 7Sep00 					{
//DeadCode CSB 7Sep00 						if((ac->ai.attacker) && (ac->ai.unfriendly == NULL))
//DeadCode CSB 7Sep00 							attacking--;
//DeadCode CSB 7Sep00 						else if((ac->ai.attacker == NULL) && (ac->ai.unfriendly))
//DeadCode CSB 7Sep00 							attacking++;
//DeadCode CSB 7Sep00 						else
//DeadCode CSB 7Sep00 							if((ac->ai.unfriendly) && (ac->ai.attacker))
//DeadCode CSB 7Sep00 							{
//DeadCode CSB 7Sep00 								FP threatened  =  FP(ac->ai.attacker->vel_x) * FP(ac->World.X - ac->ai.attacker->World.X)
//DeadCode CSB 7Sep00 												+ FP(ac->ai.attacker->vel_y) * FP(ac->World.Y - ac->ai.attacker->World.Y)
//DeadCode CSB 7Sep00 												+ FP(ac->ai.attacker->vel_z) * FP(ac->World.Z - ac->ai.attacker->World.Z);
//DeadCode CSB 7Sep00 								FP threatening =  FP(ac->vel_x) * FP(ac->ai.unfriendly->World.X - ac->World.X)
//DeadCode CSB 7Sep00 												+ FP(ac->vel_y) * FP(ac->ai.unfriendly->World.Y - ac->World.Y)
//DeadCode CSB 7Sep00 												+ FP(ac->vel_z) * FP(ac->ai.unfriendly->World.Z - ac->World.Z);
//DeadCode CSB 7Sep00 								if((threatened > 0) && (threatening < 0))
//DeadCode CSB 7Sep00 									attacking--;
//DeadCode CSB 7Sep00 								else if((threatened < 0) && (threatening > 0))
//DeadCode CSB 7Sep00 									attacking++;
//DeadCode CSB 7Sep00 							}
//DeadCode CSB 7Sep00 					}
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 				if(attacking < 0)

				int numusfighting = 0;
				for(AirStrucPtr ld = coveree; ld; ld = ld->fly.nextflight)
					for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
						if(		((ac->movecode == AUTO_PRECOMBAT) || (ac->movecode == AUTO_COMBAT))
							&&	(ac->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER) && (ac->ai.manoeuvre != MANOEUVRE_DISENGAGED)	)
							numusfighting++;

				int numthemfighting = 0;
				if(coveree->ai.attacker)
				for(ld = coveree->ai.attacker->GetLeadAc(); ld; ld = ld->fly.nextflight)
					for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
						if(		((ac->movecode == AUTO_PRECOMBAT) || (ac->movecode == AUTO_COMBAT))
							&&	(ac->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER) && (ac->ai.manoeuvre != MANOEUVRE_DISENGAGED)	)
							numthemfighting++;

				if(		(coveree->ai.unfriendly) && (coveree->ai.unfriendly->Status.size == AIRSTRUCSIZE)
					&&	((!coveree->ai.attacker) || (AirStrucPtr(coveree->ai.unfriendly)->GetLeadAc() != coveree->ai.attacker->GetLeadAc()))	)
					for(ld = AirStrucPtr(coveree->ai.unfriendly)->GetLeadAc(); ld; ld = ld->fly.nextflight)
						for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
							if(		((ac->movecode == AUTO_PRECOMBAT) || (ac->movecode == AUTO_COMBAT))
								&&	(ac->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER) && (ac->ai.manoeuvre != MANOEUVRE_DISENGAGED)	)
								numthemfighting++;

				if(3 * numthemfighting > 4 * numusfighting)
//DeadCode CSB 8Sep00 				if(coveree->IsOutNumberedBy(1.0))
				{
					AirStrucPtr trg = NULL;
					for(AirStrucPtr nf = coveree; (nf) && (!trg); nf = nf->fly.nextflight)
						for(AirStrucPtr ac = nf; (ac) && (!trg); ac = ac->Follower())
							if((ac->ai.attacker) && (ac->ai.attacker->Status.size == AIRSTRUCSIZE))
								trg = AirStrucPtr(ac->ai.attacker);
					if(!trg)
						for(AirStrucPtr nf = coveree; (nf) && (!trg); nf = nf->fly.nextflight)
							for(AirStrucPtr ac = nf; (ac) && (!trg); ac = ac->Follower())
								if((ac->ai.unfriendly) && (ac->ai.unfriendly->Status.size == AIRSTRUCSIZE))
									trg = AirStrucPtr(ac->ai.unfriendly);

					if(trg)
					{	
						if((nationality == NAT_RAF) && (follower))
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FIGHTERSNEEDHELP, MSG_ADVISEATTACK, *this, trg, Follower()));
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ENGAGEBANDIT, MSG_STATUSREPORT, *this, trg, coveree));
				
						for(AirStrucPtr nf = this; nf; nf = nf->fly.nextflight)
							for(AirStrucPtr ac = nf; ac; ac = ac->Follower())
							{
								AirStrucPtr cnf, cac;
								AirStrucPtr mytarget = NULL;
								for(cnf = coveree; (cnf) && (!mytarget); cnf = cnf->fly.nextflight)
									for(cac = cnf; (cac) && (!mytarget); cac = cac->Follower())
										if((cac->ai.attacker) && (cac->ai.attacker->Status.size == AIRSTRUCSIZE) && (!AirStrucPtr(cac->ai.attacker)->ai.attacker))
											mytarget = AirStrucPtr(cac->ai.attacker);

								for(cnf = coveree; (cnf) && (!mytarget); cnf = cnf->fly.nextflight)
									for(cac = cnf; (cac) && (!mytarget); cac = cac->Follower())
										if((cac->ai.attacker) && (cac->ai.attacker->Status.size == AIRSTRUCSIZE))
											mytarget = AirStrucPtr(cac->ai.attacker);

								if(!mytarget)
									mytarget = trg;

//DeadCode CSB 1Aug00 								if((ac->ai.unfriendly) && (ac->ai.unfriendly->Status.size == AIRSTRUCSIZE) && (AirStrucPtr(ac->ai.unfriendly)->ai.attacker == ac))
//DeadCode CSB 1Aug00 									AirStrucPtr(ac->ai.unfriendly)->ai.attacker = NULL;
//DeadCode CSB 1Aug00 								if(!mytarget->ai.attacker)
//DeadCode CSB 1Aug00 									mytarget->ai.attacker = ac;
//DeadCode CSB 1Aug00 								ac->ai.unfriendly = mytarget;
								ac->SetUnfriendly(mytarget);			//CSB 1Aug00
								ac->ai.manoeuvre = MANOEUVRE_SELECT;
								ac->ai.ManStep = PHASE0;
							}
					}
				}
				else
					ai.ManStep = PHASE0;
			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleTightClimbingTurn
//Author		R. Hyde 
//Date			Sat 30 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleTightClimbingTurn (ANGLES desiredpitch)
{
 
 	SWord	deltapitch;
 
 	deltapitch = desiredpitch - fly.cpitch;
 	PitchIntercept = desiredpitch; 
 	SimpleTightTurnSubSub (deltapitch);
 
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleLookAround
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleLookAround ()
{
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			if(formpos == 0)
				SetManoeuvreTime(3000);
			else
				SetManoeuvreTime(1500);
			ai.desiredroll = - (ANGLES)ANGLES_45Deg + (Angles)(ANGLES_90Deg * Math_Lib.rnd(2)); 
			ai.ManStep = PHASE1;
		}

		case PHASE1:
		{
			if(!formpos)
			{
				AirStrucPtr buddy = fly.leadflight;
				if(!buddy)
					buddy = FindBuddy();;
				if(buddy)
				{
					despos = buddy->World;
//DeadCode CSB 22Jun00 					despos.Y += 15000;
					InterceptandRange(&despos);
					SWord reqdeltahdg = hdg - HdgIntercept;
			 		SWord reqroll = FindRequiredRoll(reqdeltahdg, CombatReqBankData);
					MODLIMIT(reqroll, ANGLES_45Deg);
					SimpleMoveToRoll(reqroll);
					AutoCalcPitch();
				}
				else
				{
					SimpleMoveToRoll(ai.desiredroll);
					PitchIntercept = BestClimbAngle();
					AutoCalcPitch();
				}
			}
			else
			{
				despos = FindFormpos0()->World;
//DeadCode CSB 22Jun00 				despos.Y += 15000;
				InterceptandRange(&despos);
				SWord reqdeltahdg = hdg - HdgIntercept;
			 	SWord reqroll = FindRequiredRoll(reqdeltahdg, CombatReqBankData);
				MODLIMIT(reqroll, ANGLES_45Deg);
				SimpleMoveToRoll(reqroll);
				AutoCalcPitch();
			}

			if (!ManoeuvreTimeLeft())
			{
		    	ai.ManStep = PHASE0;
				if(formpos == 0)
				{
					if(AllButLdrNotOnCombat ())				//RDH 26Nov96
						ai.manoeuvre = MANOEUVRE_TOPCOVER;		//RDH 26Nov96
					else										//RDH 26Nov96
						ai.manoeuvre = MANOEUVRE_LOOKROUND;		//RDH 26Nov96
				}
				else
					if(FindFormpos0()->ai.manoeuvre == MANOEUVRE_TOPCOVER)
						ai.manoeuvre = MANOEUVRE_TOPCOVER;
					else
						Art_Int.AttackSpareInLeadersGroup(*this);	
 			}

			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BarrelRoll
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleBarrelRollAttack ( )

{
	SimpleScissors ( );
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scissors
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleScissors ( )

{
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
			ai.desiredhdg = hdg + ANGLES_120Deg; 
		}
		case PHASE1:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
			}
			PitchIntercept = ANGLES_2Deg;
			AutoCalcPitch();
			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_100Deg))
			{
				ai.ManStep = PHASE2;
				ai.desiredhdg = hdg - ANGLES_240Deg; 
			}
			break;
		}
		case PHASE2:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
			}
			PitchIntercept = ANGLES_2Deg;
			AutoCalcPitch();
			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_100Deg))
			{
				ai.ManStep = PHASE1;
				ai.desiredhdg = hdg + ANGLES_240Deg; 
			}
			break;
		}
		case PHASE3:
		{

			ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MildScissors
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleMildScissors ( )

{
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
			ai.desiredhdg = hdg - ANGLES_15Deg; 
		}
		case PHASE1:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
			}
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
			{
				ai.ManStep = PHASE2;
				ai.desiredhdg = hdg + ANGLES_30Deg; 
			}
			break;
		}
		case PHASE2:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE3;
			}
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			if (SimpleMoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
			{
				ai.ManStep = PHASE1;
				ai.desiredhdg = hdg - ANGLES_30Deg; 
			}
			break;
		}
		case PHASE3:
		{

			ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveToDesiredHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::SimpleMoveToDesiredHdg (ANGLES desiredhdg,ANGLES target)

{
	Bool	retval;

	SimpleMoveToHdg (desiredhdg);
	retval = ChkAtDesiredHdg (desiredhdg,target);
	return (retval);
}

 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
 //Procedure		MoveToHdg
 //Author		R. Hyde 
 //Date			Wed 13 Dec 1995
 //
 //Description	based on difference between desired and actual hdg, fix aileron
 //				to give a roll, morale and skill will fix maxroll				
 //
 //Inputs		
 //
 //Returns	
 //
 //------------------------------------------------------------------------------
void	ACMAirStruc::SimpleMoveToHdg (ANGLES desiredhdg)
 
{
 	SWord	reqdeltahdg, reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
 	SWord	reqroll,deltaroll;
 
 	reqdeltahdg = 	hdg - desiredhdg;
 	Math_Lib.Pos ((SWord) reqdeltahdg, reqdeltahdg_pos,reqdeltahdg_sign);
 	reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
 
//DeadCode RDH 30Mar96  	deltaroll = (SWord) (reqroll - fly.acroll);
	ai.desiredroll = (Angles) reqroll;
	SimpleMoveToRoll (reqroll);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveToRoll
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::SimpleMoveToRoll (SWord desiredroll)

{	//RequiredDRollSub: parameter is desired roll, return val is delta roll

	roll += (Angles) (RequiredDRollSub (desiredroll));
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveToDesiredPitch
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	ACMAirStruc::SimpleMoveToDesiredPitch (ANGLES desiredpitch,ANGLES target)

{
	SWord	retval;


	PitchIntercept = desiredpitch;
	AutoCalcPitch();
	retval = DesiredPitchChk (desiredpitch,target);
	return (retval);


}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleFlyWing
//Author		Craig Beeston
//Date			Wed 15 Mar 2000
//
//Description	Like AutoFollowWpWing but in combat
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleFlyWing(AirStrucPtr lead, ANGLES relhdg, int dist)
{
	const SLong aimtime = 250;
	COORDS3D aimworld;
	if(relhdg == ANGLES_0Deg)
		aimworld = *PositionWRTLeader(lead);
	else
	{
		relhdg += lead->hdg;
		Float sin, cos;
		Math_Lib.high_sin_cos(relhdg, sin, cos);
		aimworld.X = lead->World.X + sin * Float(dist);
		aimworld.Y = lead->World.Y;
		aimworld.Z = lead->World.Z + cos * Float(dist);
	}
	if(lead->vel_ < classtype->minvel) 
		aimworld.Y += 15000;

	aimworld.X += (lead->vel_x * aimtime) / 10000;
	aimworld.Y += (lead->vel_y * aimtime) / 10000;
	aimworld.Z += (lead->vel_z * aimtime) / 10000;
	InterceptandRange(&aimworld);
	AutoCalcPitch();
	SWord desroll = FindRequiredRoll (hdg - HdgIntercept, CombatReqBankData);
	SimpleMoveToRoll(desroll);

	SLong desvel = lead->vel_ + (Range - (lead->vel_ * aimtime) / 10000) * 100;	//1 metres -> 1 m/s
	if(desvel < classtype->minvel)
		desvel = classtype->minvel;
	if(vel_ < desvel)
		SimpleMoveToThrust(100);
	else
		SimpleMoveToThrust(0);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StraightandLevel
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleStraightandLevel ( )

{
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);
//DEADCODE RDH 20/06/99  			SimpleMoveToThrust (80);
			ai.ManStep = PHASE1;
	 		ai.desiredroll = ANGLES_0Deg;
		}
		case PHASE1:
		{
			//this manoeuvre is only done by poor pilots so we can reduce speed so that
			//other can catch up and attack							  //RDH 20/06/99
			if (vel_ < MPH250)
				SimpleMoveToThrust (80);
			else
				SimpleMoveToThrust (0);

			if (World.Y < FT_1000)
				PitchIntercept = ANGLES_4Deg;
			else
				PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();

			deltaroll = (SWord) (ai.desiredroll - roll);
			SimpleMoveToRoll (ai.desiredroll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_2Deg)
			{
				ai.ManStep = PHASE2;
			}

			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;

		}
		case PHASE2:
		{
			//this manoeuvre is only done by poor pilots so we can reduce speed so that
			//other can catch up and attack							  //RDH 20/06/99
			if (vel_ < MPH250)
				SimpleMoveToThrust (80);
			else
				SimpleMoveToThrust (0);

			if (World.Y < FT_1000)
				PitchIntercept = ANGLES_10Deg;
			else
				PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SimpleMoveToRoll (ai.desiredroll);
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;

		}

	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcmSideSlip
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleAcmSideSlip ( )

{
	
	SimpleSustainedTurn ();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpinRecovery
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleSpinRecovery ()
{
	SimpleSustainedTurn ();

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpinOut
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleSpinOut ( )

{
	SWord	deltaroll;
	UWord	deltayaw_pos;
	SWord	deltayaw_sign;


	
	SLong groundlevel = _Collide.LowestSafeAlt(this,			//RDH 16Dec96
											this->pitch,		//RDH 16Dec96
											this->roll);		//RDH 16Dec96


	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (1);
			ai.ManStep = PHASE1;
			SetManoeuvreTime (600);
			ai.desiredroll = ANGLES_45Deg;
		}
		case PHASE1:
		{
			if ((World.Y - groundlevel) < FT_1000)				//RDH 16Dec96
				PitchIntercept =  ANGLES_8Deg;					//RDH 16Dec96
			else												//RDH 16Dec96
				PitchIntercept =  ANGLES_305Deg;

			AutoCalcPitch();
			SimpleMoveToRoll (ai.desiredroll);
			if (!ManoeuvreTimeLeft())
			{
				ai.desiredroll = ANGLES_0Deg;
				ai.ManStep = PHASE2;
				SetManoeuvreTime (400);
			}

			break;
		}
		case PHASE2:
		{
			if ((World.Y - groundlevel) < FT_1000)				//RDH 16Dec96
				PitchIntercept =  ANGLES_8Deg;					//RDH 16Dec96
			else												//RDH 16Dec96
			PitchIntercept =  ANGLES_340Deg;
			AutoCalcPitch();
			SimpleMoveToRoll (ai.desiredroll);
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
	 			SimpleMoveToThrust (100);

			}else
			{
				
			}
			break;
		}

	}
		SetControlSurfaces ();

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiveforHome
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleDiveforHome ( )
{
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
			InterceptandRange (&ai.homebase->World);
			ai.desiredhdg = HdgIntercept; 
			SetManoeuvreTime(1500);
		}
		case PHASE1:
		{
			if (World.Y < FT_1000)
				PitchIntercept = ANGLES_0Deg;
			else
				PitchIntercept = ANGLES_345Deg;
			AutoCalcPitch();
			SWord desroll = FindRequiredRoll(hdg - ai.desiredhdg, CombatReqBankData);
			SimpleMoveToRoll(desroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

//DeadCode CSB 5Sep00 	SLong	temp_range;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 	temp_range = Range; 	
//DeadCode CSB 5Sep00 	switch (ai.ManStep)
//DeadCode CSB 5Sep00 	{
//DeadCode CSB 5Sep00 		case PHASE0:
//DeadCode CSB 5Sep00 		{
//DeadCode CSB 5Sep00  			SimpleMoveToThrust (100);
//DeadCode CSB 5Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 5Sep00 			InterceptandRange (&ai.homebase->World);
//DeadCode CSB 5Sep00 			ai.desiredhdg = HdgIntercept; 
//DeadCode CSB 5Sep00 			SetManoeuvreTime(0);
//DeadCode CSB 5Sep00 		}
//DeadCode CSB 5Sep00 		case PHASE1:
//DeadCode CSB 5Sep00 		{
//DeadCode CSB 5Sep00 			if(!TimeLeft())
//DeadCode CSB 5Sep00 			{
//DeadCode CSB 5Sep00 				Range = temp_range; 	
//DeadCode CSB 5Sep00 				if (Range < DANGERRANGE)
//DeadCode CSB 5Sep00 				{
//DeadCode CSB 5Sep00 					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 				}
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 				if (World.Y < FT_1000)
//DeadCode CSB 5Sep00 					PitchIntercept = ANGLES_0Deg;
//DeadCode CSB 5Sep00 				else
//DeadCode CSB 5Sep00 					PitchIntercept = ANGLES_10Deg;
//DeadCode CSB 5Sep00 				Bool level = SimpleMoveToDesiredHdg (ai.desiredhdg, ANGLES_1Deg);
//DeadCode CSB 5Sep00 				if((AutoCalcPitch()) && (level))
//DeadCode CSB 5Sep00 					SetManoeuvreTime (1000);
//DeadCode CSB 5Sep00 				Range = temp_range; 	
//DeadCode CSB 5Sep00 				if (Range > ENGAGERANGE)
//DeadCode CSB 5Sep00 				{
//DeadCode CSB 5Sep00 					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 				}
//DeadCode CSB 5Sep00 			}
//DeadCode CSB 5Sep00 		}
//DeadCode CSB 5Sep00 	}
}


//DeadCode CSB 28/03/99	{
//DeadCode CSB 28/03/99		SLong	temp_range;
//DeadCode CSB 28/03/99		temp_range = Range; 	
//DeadCode CSB 28/03/99	
//DeadCode CSB 28/03/99		switch (ai.ManStep)
//DeadCode CSB 28/03/99		{
//DeadCode CSB 28/03/99			case PHASE0:
//DeadCode CSB 28/03/99			{
//DeadCode CSB 28/03/99				if (World.Y < FT_1000)
//DeadCode CSB 28/03/99				{
//DeadCode CSB 28/03/99					PitchIntercept =  ANGLES_0Deg;
//DeadCode CSB 28/03/99					AutoCalcPitch();
//DeadCode CSB 28/03/99				}else
//DeadCode CSB 28/03/99				{
//DeadCode CSB 28/03/99					PitchIntercept =  ANGLES_340Deg;
//DeadCode CSB 28/03/99					AutoCalcPitch();
//DeadCode CSB 28/03/99					InterceptandRange (&ai.homebase->World);
//DeadCode CSB 28/03/99					SimpleMoveToHdg (HdgIntercept);
//DeadCode CSB 28/03/99				}
//DeadCode CSB 28/03/99				if (Range < MILES01)
//DeadCode CSB 28/03/99				{//within mile of home
//DeadCode CSB 28/03/99					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 28/03/99				}
//DeadCode CSB 28/03/99				Range = temp_range; 	
//DeadCode CSB 28/03/99				if (Range > MILES01)
//DeadCode CSB 28/03/99				{//mile from action, reconsider
//DeadCode CSB 28/03/99					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 28/03/99				}
//DeadCode CSB 28/03/99			}
//DeadCode CSB 28/03/99		}
//DeadCode CSB 28/03/99	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbforHome
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleClimbforHome ( )
{
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
			InterceptandRange (&ai.homebase->World);
			ai.desiredhdg = HdgIntercept; 
			SetManoeuvreTime(1500);
		}
		case PHASE1:
		{
			if(vel_ < classtype->bestclimbvel)
				PitchIntercept = ANGLES_0Deg;
			else
				PitchIntercept = ANGLES_15Deg;
			AutoCalcPitch();
			SWord desroll = FindRequiredRoll(hdg - ai.desiredhdg, CombatReqBankData);
			SimpleMoveToRoll(desroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

//DeadCode CSB 5Sep00 	SLong	temp_range;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 	temp_range = Range; 	
//DeadCode CSB 5Sep00 	switch (ai.ManStep)
//DeadCode CSB 5Sep00 	{
//DeadCode CSB 5Sep00 		case PHASE0:
//DeadCode CSB 5Sep00 		{
//DeadCode CSB 5Sep00  			SimpleMoveToThrust (100);
//DeadCode CSB 5Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 5Sep00 			InterceptandRange (&ai.homebase->World);
//DeadCode CSB 5Sep00 			ai.desiredhdg = HdgIntercept; 
//DeadCode CSB 5Sep00 			SetManoeuvreTime(0);
//DeadCode CSB 5Sep00 		}
//DeadCode CSB 5Sep00 		case PHASE1:
//DeadCode CSB 5Sep00 		{
//DeadCode CSB 5Sep00 			if(!TimeLeft())
//DeadCode CSB 5Sep00 			{
//DeadCode CSB 5Sep00 				Range = temp_range; 	
//DeadCode CSB 5Sep00 				if (Range < DANGERRANGE)
//DeadCode CSB 5Sep00 				{
//DeadCode CSB 5Sep00 					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 				}
//DeadCode CSB 5Sep00 				PitchIntercept =  ANGLES_10Deg;
//DeadCode CSB 5Sep00 				Bool level = SimpleMoveToDesiredHdg (ai.desiredhdg, ANGLES_1Deg);
//DeadCode CSB 5Sep00 				if((AutoCalcPitch()) && (level))
//DeadCode CSB 5Sep00 					SetManoeuvreTime (1000);
//DeadCode CSB 5Sep00 				Range = temp_range; 	
//DeadCode CSB 5Sep00 				if (Range > ENGAGERANGE)
//DeadCode CSB 5Sep00 				{
//DeadCode CSB 5Sep00 					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 				}
//DeadCode CSB 5Sep00 			}
//DeadCode CSB 5Sep00 		}
//DeadCode CSB 5Sep00 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StraightDive
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleStraightDive ( )

{
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);
 			SimpleMoveToThrust (90);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToRoll (ANGLES_0Deg);
			PitchIntercept =  ANGLES_340Deg;
			AutoCalcPitch();
			if (World.Y < FT_1000)
				ai.manoeuvre = MANOEUVRE_SELECT;
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			break;
		}
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StandOnTail
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleStandOnTail ( )

{
	COORDS3D	target;
	SLong		time;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (800);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			target.X = ai.unfriendly->World.X;
			target.Y = ai.unfriendly->World.Y;
			target.Z = ai.unfriendly->World.Z;
			InterceptandRange (&target);

			//time for bullets to arrive at current unfriendly position
			time = (10000 * Range) / MUZZELVEL;
			//calc lead position using this time
			target.X = ai.unfriendly->World.X + (unfriendly->vel_x * time ) / 10000;
			target.Y = ai.unfriendly->World.Y + (unfriendly->vel_y * time ) / 10000;
			target.Z = ai.unfriendly->World.Z + (unfriendly->vel_z * time ) / 10000;
			InterceptandRange (&target);


			SimpleMoveToHdg (HdgIntercept);
			if (vel_ < MPH55)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}else
			{
				if ((SWord) fly.cpitch < (SWord) PitchIntercept)
				{
					AutoCalcPitch();
				}else
				{
					AutoCalcPitch();
					FireABullet(100);
				}
			}
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}

	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShootToFrighten
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleShootToFrighten ( )

{
	AirStrucPtr	unfriendly = *ai.unfriendly;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (200);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if (!ManoeuvreTimeLeft())
			{
			   	ai.ManStep = PHASE0;
//DEADCODE CB 18/11/99 				ai.manoeuvre=MANOEUVRE_SUSTAINEDTURN;
				ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;				  //CB 18/11/99
			}
			SimpleTightTurn (FT_1000);
			FireABullet(100);
			break;
		}
	}
}





//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GoHome
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleGoHome ( )

{
	
//DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
	SLong	temp_range;

	temp_range = Range; 	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (1000);
			ai.ManStep = PHASE1;
			InterceptandRange (&ai.homebase->World);
			ai.desiredhdg = HdgIntercept; 
			Range = temp_range;
//jink a bit possibly
			if	(		TargetOnSubjectTail(ANGLES_10Deg)
					&&	(Range < 4 * WEAPONSRANGE)
					&&	(ai.combatskill >= SKILL_REGULAR)
				)
				ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 
		}
		case PHASE1:
		{
			if (!ManoeuvreTimeLeft())
			{
				SetManoeuvreTime (500);
				ai.ManStep = PHASE2;
				InterceptandRange (&ai.homebase->World);
				ai.desiredhdg = HdgIntercept; 
				Range = temp_range;
				if	(		TargetOnSubjectTail(ANGLES_10Deg)
						&&	(Range < 4 * WEAPONSRANGE)
						&&	(ai.combatskill >= SKILL_REGULAR)
					)
					ai.desiredhdg = HdgIntercept + ANGLES_340Deg; 
			}
			if (Range < WEAPONSRANGE)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			PitchIntercept =  ANGLES_0Deg;
			AutoCalcPitch();
			SimpleMoveToHdg (ai.desiredhdg);
			if (Range > COMBATRANGE +METRES1400)
//DeadCode RDH 25Oct96 			if (Range > COMBATRANGE + METRES1400)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
		case PHASE2:
		{
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE1;
				SetManoeuvreTime (500);
				InterceptandRange (&ai.homebase->World);


				ai.desiredhdg = HdgIntercept; 
				Range = temp_range;
				if	(		TargetOnSubjectTail(ANGLES_10Deg)
						&&	(Range < 4 * WEAPONSRANGE)
						&&	(ai.combatskill >= SKILL_REGULAR)
					)
					ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 
			}
			if (Range < WEAPONSRANGE)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			PitchIntercept =  ANGLES_0Deg;
			AutoCalcPitch();
			SimpleMoveToHdg (ai.desiredhdg);
//DeadCode RDH 25Oct96 			if (Range > COMBATRANGE + METRES1400)
			if (Range > COMBATRANGE+METRES1400)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveAway
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleMoveAway ( )
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(100);
			SetManoeuvreTime(500);
			ai.ManStep = PHASE1;
		}

		case PHASE1:
		{
			PitchIntercept = ANGLES_345Deg;
			AutoCalcPitch();
			SimpleMoveToHdg(HdgIntercept + ANGLES_180Deg);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

//DEADCODE CSB 13/03/00 	UWord	roll_pos;
//DEADCODE CSB 13/03/00 	SWord	roll_sign;
//DEADCODE CSB 13/03/00 	SWord	desiredaoa;
//DEADCODE CSB 13/03/00 	SWord deltahdg;
//DEADCODE CSB 13/03/00 	UWord	deltahdg_pos;
//DEADCODE CSB 13/03/00 	SWord	deltahdg_sign;
//DEADCODE CSB 13/03/00 	UWord	elevator_pos;
//DEADCODE CSB 13/03/00 	SWord	elevator_sign;
//DEADCODE CSB 13/03/00 	
//DEADCODE CSB 13/03/00 	switch (ai.ManStep)
//DEADCODE CSB 13/03/00 	{
//DEADCODE CSB 13/03/00 		case PHASE0:
//DEADCODE CSB 13/03/00 		{
//DEADCODE CSB 13/03/00  			SimpleMoveToThrust(100);
//DEADCODE CSB 13/03/00 			SetManoeuvreTime(2000);
//DEADCODE CSB 13/03/00 			ai.ManStep = PHASE1;
//DEADCODE CSB 13/03/00 			break;
//DEADCODE CSB 13/03/00 		}
//DEADCODE CSB 13/03/00 		case PHASE1:
//DEADCODE CSB 13/03/00 		{
//DEADCODE CSB 13/03/00 			if(!ManoeuvreTimeLeft())
//DEADCODE CSB 13/03/00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 			PitchIntercept = ANGLES_0Deg;
//DEADCODE CSB 13/03/00 			AutoCalcPitch();
//DEADCODE CSB 13/03/00 			SimpleMoveToHdg (HdgIntercept + ANGLES_180Deg);	//get aidesiredroll
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 			deltahdg = hdg - (HdgIntercept + ANGLES_180Deg);
//DEADCODE CSB 13/03/00 			Math_Lib.Pos(((SWord)deltahdg), deltahdg_pos, deltahdg_sign);
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 			if(deltahdg_pos < ANGLES_5Deg)
//DEADCODE CSB 13/03/00 			{
//DEADCODE CSB 13/03/00 				ai.ManStep = PHASE2;
//DEADCODE CSB 13/03/00 				SetManoeuvreTime (1500);
//DEADCODE CSB 13/03/00 			}
//DEADCODE CSB 13/03/00 			break;
//DEADCODE CSB 13/03/00 		}
//DEADCODE CSB 13/03/00 
//DEADCODE CSB 13/03/00 		case PHASE2:
//DEADCODE CSB 13/03/00 		{
//DEADCODE CSB 13/03/00 			SimpleMoveToHdg (HdgIntercept+ANGLES_180Deg);	//get aidesiredroll
//DEADCODE CSB 13/03/00 			PitchIntercept =  ANGLES_4Deg;
//DEADCODE CSB 13/03/00 			AutoCalcPitch();
//DEADCODE CSB 13/03/00 			if (!ManoeuvreTimeLeft())
//DEADCODE CSB 13/03/00 			{
//DEADCODE CSB 13/03/00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE CSB 13/03/00 			}
//DEADCODE CSB 13/03/00 			break;
//DEADCODE CSB 13/03/00 		}
//DEADCODE CSB 13/03/00 	}
//DEADCODE CSB 13/03/00 
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AccidentalSpinOut
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	similar to SpinOut, but longer recovery
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleAccidentalSpinOut ( )

{
	SimpleSpinOut ( );
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurningFight
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	attempt to lead, find Hdgintercept and delta, set roll
//				roll should not give alt lose
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void AirStruc::SimpleTurningFight ()
//
//{
//	SWord	deltapitch;
//	COORDS3D	target;
//	SLong		time;
//	AirStrucPtr	unfriendly = *ai.unfriendly;
//	UWord	acroll_pos,aoa_pos;
//	SWord	acroll_sign,reqroll,aoa_sign;
//	
//	switch (ai.ManStep)
//	{
//		case PHASE0:
//		{
//			SimpleMoveToThrust (100);
//			SetManoeuvreTime (1500);
//			ai.ManStep = PHASE1;
//			break;
//		}
//		case PHASE1:
//		{
//			if (!ManoeuvreTimeLeft())
//			{
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
//			if (	(TargetFacingSubject(ANGLES_10Deg))
//				&&	SubjectFacingTarget(ANGLES_10Deg)
//				&&	(Range < METRES150)
//				)
//				{
//					HdgIntercept = HdgIntercept + ANGLES_90Deg;
//					PitchIntercept = PitchIntercept + ANGLES_10Deg;
//				}
//			SimpleTightTurn (FT_1000);
//			break;
//
//		}
//	}
//
//}		
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowGYoYo
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleLowGYoYo ( )

{
	UWord	dhdg_pos;
	SWord	dhdg_sign;
	SWord dhdg;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (1000);
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			dhdg = (SWord) (hdg - HdgIntercept);
			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
			if (dhdg_pos < ANGLES_45Deg)
			{
				dhdg_pos = 5*dhdg_pos/4;  
			}
			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);

		 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
			SimpleMoveToRoll (ai.desiredroll);
			if (	(SimpleMoveToDesiredPitch (ANGLES_340Deg,ANGLES_15Deg))
				||	(!ManoeuvreTimeLeft())
				)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (500);

			}
			break;
		}
		case PHASE2:
		{
			dhdg = (SWord) (hdg - HdgIntercept);
			Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
			if (dhdg_pos < ANGLES_45Deg)
			{
				dhdg_pos = 5*dhdg_pos/4;  
			}
			dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);

		 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
			SimpleMoveToRoll (ai.desiredroll);
			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VerticalLoop
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleVerticalLoop ( )

{

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (1000);
 			SimpleMoveToThrust (100);
			ai.desiredroll = - (ANGLES)ANGLES_45Deg +
 						(Angles)(ANGLES_90Deg * Math_Lib.rnd(2)); 
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
//DeadCode RDH 13Dec96 			SimpleTightClimbingTurn (ANGLES_15Deg);
			SimpleTightClimbingTurn (ANGLES_7Deg);				//RDH 13Dec96
			if  (!ManoeuvreTimeLeft())
			{
 				ai.manoeuvre = MANOEUVRE_SELECT;

			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ImmelmannTurn
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleImmelmannTurn ( )
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToRoll(ANGLES_0Deg);
			PitchIntercept = ANGLES_90Deg;
			if(AutoCalcPitch())
			{
				roll += ANGLES_180Deg;
				hdg  += ANGLES_180Deg;
				ai.ManStep = PHASE2;
			}
			break;
		}
		case PHASE2:
		{
			SimpleMoveToRoll(ANGLES_180Deg);
			SWord deltahdg = HdgIntercept - hdg;
			if(deltahdg > 0)
			{
				hdg += (classtype->maxrollrate * Timer_Code.FRAMETIME) / 100;
				deltahdg = HdgIntercept - hdg;
				if(deltahdg < 0)
					ai.ManStep = PHASE3;
			}
			else
			{
				hdg -= (classtype->maxrollrate * Timer_Code.FRAMETIME) / 100;
				deltahdg = HdgIntercept - hdg;
				if(deltahdg > 0)
					ai.ManStep = PHASE3;
			}
			break;
		}
		case PHASE3:
		{
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
//DeadCode CSB 11Sep00 			SWord deltahdg = HdgIntercept - hdg;
//DeadCode CSB 11Sep00 			if(deltahdg > 0)
//DeadCode CSB 11Sep00 				SimpleMoveToRoll(ANGLES_90Deg);
//DeadCode CSB 11Sep00 			else
//DeadCode CSB 11Sep00 				SimpleMoveToRoll(-ANGLES_90Deg);
			if(SWord(pitch) < ANGLES_45Deg)
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = 0;
			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HeadOnOffset
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleHeadOnOffset ( )

{
	SimpleTurningFight();
	return;

//DEADCODE CSB 03/12/99 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 	SLong temp_range;
//DEADCODE CSB 03/12/99 	temp_range = Range; 	
//DEADCODE CSB 03/12/99 	COORDS3D	target;
//DEADCODE CSB 03/12/99 	SWord c,s;
//DEADCODE CSB 03/12/99 	SWord newhdg;
//DEADCODE CSB 03/12/99 	UByte	FF = FlyingFactor();
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 	switch (ai.ManStep)
//DEADCODE CSB 03/12/99 	{
//DEADCODE CSB 03/12/99 		case PHASE0:
//DEADCODE CSB 03/12/99 		{
//DEADCODE CSB 03/12/99 			InterceptandRange(ai.unfriendly);
//DEADCODE CSB 03/12/99 			SimpleMoveToThrust (ThrustfromFF());
//DEADCODE CSB 03/12/99 			SetManoeuvreTime (2000);
//DEADCODE CSB 03/12/99 			SWord dhdg = HdgIntercept - hdg;
//DEADCODE CSB 03/12/99 			if ((dhdg) > 0)
//DEADCODE CSB 03/12/99 				ai.desiredhdg = ANGLES_90Deg;
//DEADCODE CSB 03/12/99 			else
//DEADCODE CSB 03/12/99 				ai.desiredhdg = ANGLES_270Deg;
//DEADCODE CSB 03/12/99 			ai.ManStep = PHASE1;
//DEADCODE CSB 03/12/99 		}
//DEADCODE CSB 03/12/99 		case PHASE1:
//DEADCODE CSB 03/12/99 		{
//DEADCODE CSB 03/12/99 			InterceptandRange(ai.unfriendly);
//DEADCODE CSB 03/12/99 			ANGLES bca = BestClimbAngle();
//DEADCODE CSB 03/12/99 			if (PitchIntercept > bca) PitchIntercept = bca;
//DEADCODE CSB 03/12/99 			AutoCalcPitch();
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			ANGLES desiredhdg = ai.desiredhdg;
//DEADCODE CSB 03/12/99 			ANGLES unfHdgIntercept = HdgIntercept;
//DEADCODE CSB 03/12/99 			SLong	unfRange = Range;
//DEADCODE CSB 03/12/99 			newhdg = unfriendly->hdg + ai.desiredhdg;
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
//DEADCODE CSB 03/12/99 			target.X = unfriendly->World.X + ((BREAKTURNRADIUS * s) >> ANGLES_SHIFT);
//DEADCODE CSB 03/12/99 			target.Y = unfriendly->World.Y;
//DEADCODE CSB 03/12/99 			target.Z = unfriendly->World.Z + ((BREAKTURNRADIUS * c) >> ANGLES_SHIFT);
//DEADCODE CSB 03/12/99 			InterceptandRange (&target);
//DEADCODE CSB 03/12/99 			desiredhdg = HdgIntercept;
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			SWord	reqdeltahdg = hdg - desiredhdg;
//DEADCODE CSB 03/12/99 		 	ANGLES reqroll = (Angles)FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			int decisionpoint = Math_Lib.rnd(2);
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			if  (		(Range < (2 * BREAKTURNRADIUS ))
//DEADCODE CSB 03/12/99 					&&	(FF < 200)
//DEADCODE CSB 03/12/99 				)
//DEADCODE CSB 03/12/99 			{
//DEADCODE CSB 03/12/99 				if (decisionpoint)
//DEADCODE CSB 03/12/99 				{
//DEADCODE CSB 03/12/99 					if (FF < 90)
//DEADCODE CSB 03/12/99 					{
//DEADCODE CSB 03/12/99 						ai.manoeuvre = MANOEUVRE_PANICTURN;
//DEADCODE CSB 03/12/99 						ai.ManStep = PHASE0;
//DEADCODE CSB 03/12/99 					}else  
//DEADCODE CSB 03/12/99 					{
//DEADCODE CSB 03/12/99 						ai.manoeuvre = MANOEUVRE_BREAKTURN;
//DEADCODE CSB 03/12/99 						ai.ManStep = PHASE0;
//DEADCODE CSB 03/12/99 					}
//DEADCODE CSB 03/12/99 				}else
//DEADCODE CSB 03/12/99 				{
//DEADCODE CSB 03/12/99 					ai.ManStep = PHASE2;
//DEADCODE CSB 03/12/99 				}
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			}else if	(		(Range < BREAKTURNRADIUS)
//DEADCODE CSB 03/12/99 							
//DEADCODE CSB 03/12/99 						)
//DEADCODE CSB 03/12/99 			{
//DEADCODE CSB 03/12/99 				if (decisionpoint)
//DEADCODE CSB 03/12/99 				{
//DEADCODE CSB 03/12/99 					ai.manoeuvre = MANOEUVRE_BREAKTURN;
//DEADCODE CSB 03/12/99 					ai.ManStep = PHASE0;
//DEADCODE CSB 03/12/99 				}else
//DEADCODE CSB 03/12/99 				{
//DEADCODE CSB 03/12/99 					ai.desiredhdg = ai.desiredhdg  + ANGLES_180Deg;
//DEADCODE CSB 03/12/99 					ai.ManStep = PHASE2;
//DEADCODE CSB 03/12/99 				}
//DEADCODE CSB 03/12/99 			}
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			if  (!ManoeuvreTimeLeft())
//DEADCODE CSB 03/12/99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE CSB 03/12/99 			break;
//DEADCODE CSB 03/12/99 		}
//DEADCODE CSB 03/12/99 		case PHASE2:
//DEADCODE CSB 03/12/99 		{
//DEADCODE CSB 03/12/99 			InterceptandRange(ai.unfriendly);
//DEADCODE CSB 03/12/99 			ANGLES bca = BestClimbAngle();
//DEADCODE CSB 03/12/99 			if (PitchIntercept > bca ) PitchIntercept = bca;
//DEADCODE CSB 03/12/99 			AutoCalcPitch();
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			ANGLES desiredhdg = ai.desiredhdg;
//DEADCODE CSB 03/12/99 			ANGLES unfHdgIntercept = HdgIntercept;
//DEADCODE CSB 03/12/99 			SLong	unfRange = Range;
//DEADCODE CSB 03/12/99 			newhdg = unfriendly->hdg + ai.desiredhdg;
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
//DEADCODE CSB 03/12/99 			target.X = unfriendly->World.X + ((METRES30 * s) >> ANGLES_SHIFT);
//DEADCODE CSB 03/12/99 			target.Y = unfriendly->World.Y;
//DEADCODE CSB 03/12/99 			target.Z = unfriendly->World.Z + ((METRES30 * c) >> ANGLES_SHIFT);
//DEADCODE CSB 03/12/99 			InterceptandRange (&target);
//DEADCODE CSB 03/12/99 			desiredhdg = HdgIntercept;
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			SWord	reqdeltahdg = hdg - ai.desiredhdg;
//DEADCODE CSB 03/12/99 		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DEADCODE CSB 03/12/99 			SimpleMoveToRoll((Angles)reqroll);
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			if  (!ManoeuvreTimeLeft())
//DEADCODE CSB 03/12/99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE CSB 03/12/99 			if	(SubjectOnTargetTail(ANGLES_80Deg))
//DEADCODE CSB 03/12/99 			{
//DEADCODE CSB 03/12/99 				if	(		(ai.unfriendly == Manual_Pilot.ControlledAC2)
//DEADCODE CSB 03/12/99 						&&	(((AirStruc*)ai.unfriendly)->Follower())
//DEADCODE CSB 03/12/99 					)
//DEADCODE CSB 03/12/99 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON, MSG_HEADON, ((AirStruc*)ai.unfriendly)->Follower(), this, ((AirStruc*)ai.unfriendly)));
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 				int startpoint = Math_Lib.rnd(2);
//DEADCODE CSB 03/12/99 				ai.ManStep = PHASE0;
//DEADCODE CSB 03/12/99 				if (FF < 90)
//DEADCODE CSB 03/12/99 				{
//DEADCODE CSB 03/12/99 					if (startpoint)
//DEADCODE CSB 03/12/99 						ai.manoeuvre = MANOEUVRE_JINK;
//DEADCODE CSB 03/12/99 					else
//DEADCODE CSB 03/12/99 						ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
//DEADCODE CSB 03/12/99 				}else if (FF < 200)
//DEADCODE CSB 03/12/99 				{
//DEADCODE CSB 03/12/99 					if (startpoint)
//DEADCODE CSB 03/12/99 							ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
//DEADCODE CSB 03/12/99 					else
//DEADCODE CSB 03/12/99 							ai.manoeuvre = MANOEUVRE_EXTENSION;
//DEADCODE CSB 03/12/99 				}else 
//DEADCODE CSB 03/12/99 				{
//DEADCODE CSB 03/12/99 					if (startpoint)
//DEADCODE CSB 03/12/99 							ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
//DEADCODE CSB 03/12/99 					else
//DEADCODE CSB 03/12/99 							ai.manoeuvre = MANOEUVRE_BREAKTURN;
//DEADCODE CSB 03/12/99 				}
//DEADCODE CSB 03/12/99 			}
//DEADCODE CSB 03/12/99 		}
//DEADCODE CSB 03/12/99 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StayWithPrey
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	As target looses alt, stay until explosion or hits ground or alt <???
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleStayWithPrey ( )

{
	
	SWord	acroll_sign,reqroll;
	SWord	deltapitch;
	UWord	acroll_pos;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			SimpleMoveToThrust (100);
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if  (		(!ManoeuvreTimeLeft())
					||	(World.Y < FT_700)
				)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			SimpleTightTurn (FT_500);


		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GainHeight
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleGainHeight ( )

{
	
	AirStrucPtr		unfriendly;	
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign,desiredaoa;
	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			unfriendly = *ai.unfriendly;
			if (	(unfriendly->ai.attacker == this)
				||	(World.Y > classtype->fightceiling)
				)
			{
//DEADCODE CB 18/11/99 				ai.manoeuvre=MANOEUVRE_SUSTAINEDTURN;
//DEADCODE CB 18/11/99 				SimpleSustainedTurn ();
				ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
				SimpleTurningFight();
				break;
			}
			SetManoeuvreTime (2000);
 			SimpleMoveToThrust (100);
			ai.ManStep = PHASE1;
//##			if ((SWord) fly.turnrate > 0)
//			{
//		 		ai.desiredroll = ANGLES_20Deg;
//			}else
//			{
//		 		ai.desiredroll = ANGLES_340Deg;
//			}
		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_10Deg;
			AutoCalcPitch();

			InterceptandRange(ai.unfriendly);
			SWord reqdeltahdg = HdgIntercept - hdg;
			if(reqdeltahdg > 0)
				SimpleMoveToRoll(ANGLES_30Deg);
			else
				SimpleMoveToRoll(ANGLES_330Deg);

			if (!ManoeuvreTimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;

		}

	}

}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SplitS
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleSplitS ()

{
	SWord 	deltaroll;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			int groundlevel = Land_Scape.GetGroundLevel(this);
			if(World.Y - groundlevel < 150000)	//5000 ft
			{
				if(Math_Lib.rnd(1))
					ai.manoeuvre = MANOEUVRE_SCISSORS;
				else
 					ai.manoeuvre = MANOEUVRE_BREAKTURN;
				SetManoeuvreTime(0);
			}
			else
			{
				ai.desiredroll = ANGLES_180Deg;
 				SimpleMoveToThrust (100);
				ai.ManStep = PHASE1;
				if((this != Persons2::PlayerSeenAC) && (this != Persons2::PlayerGhostAC))
					fly.elevator = 0;
			}
		}
		case PHASE1:
		{
			deltaroll = (SWord) (ai.desiredroll - roll);
			SimpleMoveToRoll (ai.desiredroll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_10Deg)
			{
				ai.ManStep = PHASE2;
	 			SimpleMoveToThrust (0);
//rdh				ai.lastdeltapitch = ANGLES_0Deg;
				SetManoeuvreTime (1500);

			}
			break;
		}

		case PHASE2:
		{

			PitchIntercept = ANGLES_280Deg;
			AutoCalcPitch();
			if ( 		(!ManoeuvreTimeLeft())
					|| (    DesiredPitchChk (ANGLES_270Deg,ANGLES_20Deg)
						)										//RDH 24Jul96
				)
			{
	 			SimpleMoveToThrust (100);
				ai.manoeuvre = MANOEUVRE_SELECT;
			}


			break;
		}


	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ZoomandDrop
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleZoomandDrop ()

{
	SWord phase;
	SWord deltaroll = 0;
	UWord	deltaroll_pos;
	SWord	deltaroll_sign;

	phase = (SWord) ai.ManStep;
	switch (phase)
	{
		case PHASE0:
		{
			ai.desiredroll = ANGLES_0Deg;
 			SimpleMoveToThrust (0);
			SetManoeuvreTime (500);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToRoll (ai.desiredroll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_20Deg)
			{
				SetManoeuvreTime (500);
				ai.ManStep = PHASE2;
			}
			break;
		}
		case PHASE2:
		{
			PitchIntercept = ANGLES_70Deg;
			AutoCalcPitch();
			if (	(SimpleMoveToDesiredPitch (ANGLES_70Deg,ANGLES_10Deg))
				||	(!ManoeuvreTimeLeft())
				)
			{
				ai.ManStep = PHASE3;
 				SimpleMoveToThrust (100);
			}
		break;
		}

		case PHASE3:
		{
			if (SimpleMoveToDesiredPitch (ANGLES_315Deg,ANGLES_10Deg))
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}


	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiveAndZoom
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleDiveAndZoom ()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			if((Range > FT_3000) && (World.Y < ai.unfriendly->World.Y + FT_1000))
			{
				ai.manoeuvre = MANOEUVRE_ZOOM;
				break;
			}
			SimpleMoveToThrust(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord deltahdg = HdgIntercept - hdg;
			SLong desroll = 5 * SLong(deltahdg);
			MODLIMIT(desroll, ANGLES_75_5Deg);
			SimpleMoveToRoll(desroll);
			if((deltahdg < -ANGLES_45Deg) && (deltahdg > ANGLES_45Deg))
				PitchIntercept = ANGLES_0Deg;
			else
				PitchIntercept = Angles(SWord(PitchIntercept) / 2);
			AutoCalcPitch();
			if(Range < WEAPONSRANGE)
				ai.ManStep = PHASE2;
			break;
		}
		case PHASE2:
		{
			AutoCalcPitch();
			SLong desroll = 5 * SLong(SWord(HdgIntercept - hdg));
			MODLIMIT(desroll, ANGLES_75_5Deg);
			SimpleMoveToRoll(desroll);
			if(Range < WEAPONSRANGE / 5)
			{
				ai.manoeuvre = MANOEUVRE_ZOOM;
				ai.ManStep = PHASE0;
			}
		}
	}

//DeadCode CSB 7Sep00 	SWord	deltapitch_pos,deltapitch_sign;
//DeadCode CSB 7Sep00 	SLong	temp_range;
//DeadCode CSB 7Sep00 	COORDS3D	target;
//DeadCode CSB 7Sep00 	SLong		t,actualrange;
//DeadCode CSB 7Sep00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 7Sep00  	SWord		deltaroll;										//RDH 14Mar96
//DeadCode CSB 7Sep00 	SWord		easestickforward;
//DeadCode CSB 7Sep00 	ANGLES		local_PI;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 	local_PI  = PitchIntercept;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 	switch (ai.ManStep)
//DeadCode CSB 7Sep00 	{
//DeadCode CSB 7Sep00 		case PHASE0:
//DeadCode CSB 7Sep00 		{
//DeadCode CSB 7Sep00  			SimpleMoveToThrust (100);
//DeadCode CSB 7Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 7Sep00 			SetManoeuvreTime (12000);
//DeadCode CSB 7Sep00 		}
//DeadCode CSB 7Sep00 		case PHASE1:
//DeadCode CSB 7Sep00 		{
//DeadCode CSB 7Sep00  			if  (	(		(!ManoeuvreTimeLeft())
//DeadCode CSB 7Sep00 						||	((Range - (World.Y - ai.unfriendly->World.Y)) < ENGAGERANGE)
//DeadCode CSB 7Sep00 					)
//DeadCode CSB 7Sep00 					&&
//DeadCode CSB 7Sep00 					(SubjectFacingTarget(ANGLES_45Deg))
//DeadCode CSB 7Sep00 				 )
//DeadCode CSB 7Sep00   			{
//DeadCode CSB 7Sep00   				ai.ManStep = PHASE2;
//DeadCode CSB 7Sep00 				SetManoeuvreTime (5000);
//DeadCode CSB 7Sep00   			}
//DeadCode CSB 7Sep00    			if (local_PI << ANGLES_90Deg)
//DeadCode CSB 7Sep00   			{
//DeadCode CSB 7Sep00   				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 7Sep00   			}
//DeadCode CSB 7Sep00  
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			PitchIntercept = ANGLES_5Deg;
//DeadCode CSB 7Sep00 			AutoCalcPitch();
//DeadCode CSB 7Sep00 			SimpleMoveToHdg (HdgIntercept);
//DeadCode CSB 7Sep00 			break;
//DeadCode CSB 7Sep00 		}
//DeadCode CSB 7Sep00 		case PHASE2:
//DeadCode CSB 7Sep00 		{
//DeadCode CSB 7Sep00 			SimpleTurningFight();
//DeadCode CSB 7Sep00 			if  (			(!ManoeuvreTimeLeft())
//DeadCode CSB 7Sep00 					 ||
//DeadCode CSB 7Sep00 							(TargetOnSubjectTail(ANGLES_90Deg))
//DeadCode CSB 7Sep00 					 ||	
//DeadCode CSB 7Sep00 							(Range < METRES200)
//DeadCode CSB 7Sep00 				)
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00 			 	ai.ManStep = PHASE0;
//DeadCode CSB 7Sep00 				ai.manoeuvre=MANOEUVRE_ZOOM;
//DeadCode CSB 7Sep00 			}
//DeadCode CSB 7Sep00  	
//DeadCode CSB 7Sep00 			break;
//DeadCode CSB 7Sep00 		}
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 	}
}


//DeadCode RDH 06Aug98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 06Aug98 //Procedure		TightTurn
//DeadCode RDH 06Aug98 //Author		R. Hyde 
//DeadCode RDH 06Aug98 //Date			//RDH 11Oct96
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Description	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Inputs		
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Returns	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //------------------------------------------------------------------------------
void ACMAirStruc::SimpleTightTurn (SLong recovery_alt)
{
}
//DeadCode RDH 06Aug98 {
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	SWord	sinturn,costurn;
//DeadCode RDH 06Aug98 	SWord	turn;
//DeadCode RDH 06Aug98 	SLong	desiredroll,deltax,deltaz,delta; 
//DeadCode RDH 06Aug98 	SWord	deltapitch;
//DeadCode RDH 06Aug98 	COORDS3D	target;
//DeadCode RDH 06Aug98 	SLong		time;
//DeadCode RDH 06Aug98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 06Aug98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos;
//DeadCode RDH 06Aug98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 06Aug98 	SWord dhdg;
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	target.X = ai.unfriendly->World.X;
//DeadCode RDH 06Aug98 	target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 06Aug98 	target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 06Aug98 	InterceptandRange (&target);
//DeadCode RDH 06Aug98 	SimpleTightTurnSub (recovery_alt,target);
//DeadCode RDH 06Aug98 }
//DeadCode RDH 06Aug98 

//DeadCode RDH 06Aug98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 06Aug98 //Procedure		TightTurnSub
//DeadCode RDH 06Aug98 //Author		R. Hyde 
//DeadCode RDH 06Aug98 //Date			//RDH 11Oct96
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Description	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Inputs		
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Returns	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //------------------------------------------------------------------------------
//DeadCode RDH 06Aug98 void AirStruc::SimpleTightTurnSub (SLong recovery_alt,COORDS3D	target)
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 {
//DeadCode RDH 06Aug98 	SLong		time;
//DeadCode RDH 06Aug98 	SWord	sinturn,costurn;
//DeadCode RDH 06Aug98 	SWord	turn;
//DeadCode RDH 06Aug98 	SLong	desiredroll,deltax,deltaz,delta; 
//DeadCode RDH 06Aug98 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode RDH 06Aug98 	SWord	deltapitch,maxroll,minroll;
//DeadCode RDH 06Aug98 	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos,targetroll,olddesiredroll_pos;
//DeadCode RDH 06Aug98 	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
//DeadCode RDH 06Aug98 	SWord dhdg;
//DeadCode RDH 06Aug98 	dhdg = (SWord) (hdg - HdgIntercept);
//DeadCode RDH 06Aug98 	Math_Lib.Pos (dhdg,dhdg_pos,dhdg_sign);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		if (	(TargetFacingSubject(ANGLES_70Deg))
//DeadCode RDH 06Aug98 			&& 	(((SWord) PitchIntercept) > 0)
//DeadCode RDH 06Aug98 				)
//DeadCode RDH 06Aug98 		{
//DeadCode RDH 06Aug98 			PitchIntercept = ANGLES_0Deg;
//DeadCode RDH 06Aug98 		}	
//DeadCode RDH 06Aug98 		deltapitch = PitchIntercept - fly.cpitch;
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	if	(	(SubjectOnTargetTail(ANGLES_50Deg))
//DeadCode RDH 06Aug98 		&&	(SubjectFacingTarget(ANGLES_70Deg))
//DeadCode RDH 06Aug98 		&&	(Range < (WEAPONSRANGE-METRES20))
//DeadCode RDH 06Aug98 		)
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 		time = dhdg_pos /400;
//DeadCode RDH 06Aug98 		if (time > 20)
//DeadCode RDH 06Aug98 			time =20;
//DeadCode RDH 06Aug98 //##		turn = time * unfriendly->fly.turnrate/10;	//in s
//DeadCode RDH 06Aug98 //		turn = unfriendly->hdg + turn;
//DeadCode RDH 06Aug98 		delta = unfriendly->vel * time;		//cm/s
//DeadCode RDH 06Aug98 		Math_Lib.high_sin_cos((Angles)turn,sinturn,costurn);
//DeadCode RDH 06Aug98 		deltax = MULSHSIN(sinturn,delta,ANGLES_SHIFT);
//DeadCode RDH 06Aug98 		deltaz = MULSHSIN(costurn,delta,ANGLES_SHIFT);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		//calc lead position using this time
//DeadCode RDH 06Aug98 		target.X = ai.unfriendly->World.X + deltax;
//DeadCode RDH 06Aug98 		target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DeadCode RDH 06Aug98 		target.Z = ai.unfriendly->World.Z + deltaz;
//DeadCode RDH 06Aug98 		InterceptandRange (&target);
//DeadCode RDH 06Aug98 		dhdg = (SWord) (hdg - HdgIntercept);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		Math_Lib.Pos ((SWord)ai. desiredroll,olddesiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	}else
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		Math_Lib.Pos ((SWord)ai. desiredroll,olddesiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 		dhdg = Math_Lib.UseSign (dhdg_pos,dhdg_sign);
//DeadCode RDH 06Aug98 	 	ai.desiredroll = (Angles) FindRequiredRoll (dhdg,CombatReqBankData);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	}
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	if (	(deltapitch > ANGLES_2Deg)
//DeadCode RDH 06Aug98 		&&	(!(TargetFacingSubject(ANGLES_20Deg)))
//DeadCode RDH 06Aug98 			)
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 		if (olddesiredroll_pos <= desiredroll_pos)
//DeadCode RDH 06Aug98 		{
//DeadCode RDH 06Aug98 			desiredroll_pos = olddesiredroll_pos - 64;
//DeadCode RDH 06Aug98 			if (desiredroll_pos > ANGLES_20Deg)
//DeadCode RDH 06Aug98 				ai.desiredroll = (Angles) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 		}
//DeadCode RDH 06Aug98 	}
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	Math_Lib.Pos ((SWord)ai. desiredroll,desiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 	if (	(deltapitch < ((SWord)ANGLES_350Deg))
//DeadCode RDH 06Aug98 		&& (desiredroll_pos >= MAXCOMBATROLL)
//DeadCode RDH 06Aug98 			)
//DeadCode RDH 06Aug98 			{
//DeadCode RDH 06Aug98 				desiredroll_pos = ANGLES_180Deg - (ANGLES)MAXCOMBATROLL;
//DeadCode RDH 06Aug98 				ai.desiredroll = (Angles) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
//DeadCode RDH 06Aug98 			}
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 	if ( target.Y >= recovery_alt)
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 		deltapitch = PitchIntercept - fly.cpitch;
//DeadCode RDH 06Aug98 		SimpleTightTurnSubSub(deltapitch);
//DeadCode RDH 06Aug98 	}else
//DeadCode RDH 06Aug98 	{
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		SLong groundlevel = _Collide.LowestSafeAlt(this,
//DeadCode RDH 06Aug98 											this->pitch,
//DeadCode RDH 06Aug98 											this->roll);//RDH 21Oct96
//DeadCode RDH 06Aug98 		if ((World.Y - groundlevel) < FT_100)
//DeadCode RDH 06Aug98 		{
//DeadCode RDH 06Aug98 			//## attempt to disengage
//DeadCode RDH 06Aug98 			SimpleMoveToThrust (100);
//DeadCode RDH 06Aug98 			PitchIntercept = ANGLES_5Deg;
//DeadCode RDH 06Aug98 			AutoCalcPitch();
//DeadCode RDH 06Aug98 			SimpleMoveToRoll (ANGLES_0Deg);
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 		}
//DeadCode RDH 06Aug98 	}
//DeadCode RDH 06Aug98 }
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 
//DeadCode RDH 06Aug98 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 06Aug98 //Procedure		SimpleTightTurnSubSub
//DeadCode RDH 06Aug98 //Author		R. Hyde 
//DeadCode RDH 06Aug98 //Date			//RDH 11Oct96
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Description	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Inputs		
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //Returns	
//DeadCode RDH 06Aug98 //
//DeadCode RDH 06Aug98 //------------------------------------------------------------------------------
void ACMAirStruc::SimpleTightTurnSubSub (SWord deltapitch)
{
	SLong	desiredroll; 
	UWord	acroll_pos,aoa_pos,dhdg_pos,desiredroll_pos;
	SWord	acroll_sign,reqroll,aoa_sign,dhdg_sign,desiredroll_sign;
		//now do pitch
		PitchIntercept = (Angles)deltapitch + fly.cpitch;
		{
			if (	(deltapitch > 0)
				&&	((SWord) fly.cpitch < ANGLES_15Deg)	//sustainable max climbrate
				)
			{
				AutoCalcPitch();
		
			}else
			{
				if (	(deltapitch <= 0)
					)
				{//can push down
					AutoCalcPitch();
				}else
				{
					PitchIntercept = ANGLES_0Deg;
					AutoCalcPitch();
				}
			}
			Math_Lib.Pos ((SWord)ai.desiredroll,desiredroll_pos,desiredroll_sign);
			
			if (	(fly.cpitch > ANGLES_5Deg)
				&& (desiredroll_pos > ANGLES_20Deg)
				&& (deltapitch > 0)
					)
			
			{
				if (fly.cpitch > ANGLES_15Deg)
				{
						desiredroll_pos = ANGLES_20Deg;
				}else
				{
					desiredroll = ANGLES_20Deg +  (desiredroll_pos - ANGLES_20Deg) *
								(ANGLES_15Deg - fly.cpitch) / ANGLES_15Deg;
					desiredroll_pos = (Angles) desiredroll;
				}
				ai.desiredroll = (Angles) Math_Lib.UseSign (desiredroll_pos,desiredroll_sign);
			}
			SimpleMoveToRoll (ai.desiredroll);
		}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleCalcVel
//Author		R. Hyde 
//Date			Fri 25 Oct 1996
//
//Description	rewritten to use the accel calculated via Ps 3/9/98
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleCalcVel ()
{
	FP accel = CalcSimpleAccel();
	vel_ += FP(Timer_Code.FRAMETIME) * accel * 100.0;
	
	
//DEADCODE CSB 08/11/99 		Float	accel, fvel;
//DEADCODE CSB 08/11/99 		bool positive = true;
//DEADCODE CSB 08/11/99 		SWord		tvel;
//DEADCODE CSB 08/11/99 		accel = CalcSimpleAccel ();
//DEADCODE CSB 08/11/99 		fvel	=  accel * Timer_Code.FRAMETIME * 0.1;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 		
//DEADCODE CSB 08/11/99 		if (fvel < 0)
//DEADCODE CSB 08/11/99 		{
//DEADCODE CSB 08/11/99 			positive = false;
//DEADCODE CSB 08/11/99 			fvel = -fvel;
//DEADCODE CSB 08/11/99 		}
//DEADCODE CSB 08/11/99 		tvel = fvel;
//DEADCODE CSB 08/11/99 		fvel = 65536 * (fvel - tvel);
//DEADCODE CSB 08/11/99 		int rnd = Math_Lib.rnd();
//DEADCODE CSB 08/11/99 		if (fvel > rnd)
//DEADCODE CSB 08/11/99 			tvel++;
//DEADCODE CSB 08/11/99 		if (!positive)
//DEADCODE CSB 08/11/99 			tvel = -tvel;
//DEADCODE CSB 08/11/99 		vel = vel + tvel;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleMoveToThrust
//Author		R. Hyde 
//Date			//RDH 11Oct96
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleMoveToThrust (SWord thrust)

{
	fly.thrustpercent =  thrust * thrust / 100;;

//FC code:
//	SLong	reqvel;
//	SLong	accel;
//	SWord	deltavel,deltavel_sign;	
//	UWord	deltavel_pos;
//	SLong	climb_vel;
//
//	if  (thrust == -100)
//	{
//		if (fly.thrustpercent ==0)
//			fly.thrustpercent =  MAXAUTOTHRUST;
//	}
//	elseif  (thrust == -1)
//	{
//		if (fly.thrustpercent ==MAXAUTOTHRUST)
//			fly.thrustpercent =  0;
//	}
//	else
//		fly.thrustpercent =  thrust;
//	if (fly.thrustpercent > MAXAUTOTHRUST)
//		fly.thrustpercent = MAXAUTOTHRUST;	

}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeldedWingMan
//Author		R. Hyde							Craig Beeston
//Date			Mon 2 Mar 1998					Tue 27 Apr 1999
//
//Description	Formation flag not set so a/c can spot
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleWeldedWingMan()
{
	
//	stick to the leaders tail, range about 1000ft and weave
//	However for low morale bring wingman closer
//	For very low morale it should appear as if he is trying to stay in formation

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			fly.thrustpercent = ThrustfromFF();
			ai.ManStep = PHASE1;
			SetManoeuvreTime (3000);

		}
		case PHASE1:
		{
			if (WeldedWingSixOK())
			{
				if (		(fly.leadflight)					
						&&	 (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
					)//force manoeuvre to allow disengage
						ai.manoeuvre = MANOEUVRE_SELECT;
				else if (!leader)
					ai.manoeuvre = MANOEUVRE_SELECT;
				else
				{
					Bool PullHard = FALSE;
					COORDS3D	target;
					SWord	reqdeltahdg,reqdeltahdg_sign;
					UWord	reqdeltahdg_pos;
					SWord	reqdeltapitch,reqdeltapitch_sign;
					UWord	reqdeltapitch_pos;

					target = leader->World; 									//JIM 02Aug96
					target.Y +=	60 * ai.morale;//FT_500;		Top Moral gives 500 ft

					InterceptandRange(&target);


					reqdeltahdg   =	HdgIntercept - hdg;
					reqdeltapitch =	PitchIntercept - pitch;
					Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
					Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
					
					SWord DesRoll	= 0;
					SWord IdealRoll = 0;
					if(reqdeltapitch != 0)
						IdealRoll = Math_Lib.arctan(reqdeltahdg, reqdeltapitch);
					else
					{
						if(reqdeltahdg > 0) IdealRoll += ANGLES_90Deg;
						if(reqdeltahdg < 0) IdealRoll -= ANGLES_90Deg;
					}

					if((reqdeltahdg_pos > ANGLES_10Deg) || (reqdeltapitch_pos > ANGLES_10Deg))
					{
						DesRoll = IdealRoll;
						PullHard = TRUE;
					}
					else
					{
						if((leader->roll > MAXCOMBATROLL) || (-leader->roll > MAXCOMBATROLL))
						{
							DesRoll = IdealRoll;
							PullHard = TRUE;
						}
						else
						{
							DesRoll = leader->roll;
							DesRoll += 4 * reqdeltahdg;
							MODLIMIT(DesRoll, ANGLES_90Deg);
							PullHard = FALSE;
						}
					}
					SimpleMoveToRoll(DesRoll);

					if(PullHard)
					{
						SWord RollError = (SWord)roll - IdealRoll;
						if((RollError < ANGLES_90Deg) && (-RollError < ANGLES_90Deg))
						{
							SWord sin_roll, cos_roll;
							Math_Lib.high_sin_cos(roll, sin_roll, cos_roll);
	//DeadCode CSB 01/06/99							FP MaxDeltaPitch = (FP)classtype->maxpitchrate * (FP)Timer_Code.FRAMETIME / 100.0 / 32768.0;
							FP MaxDeltaPitch = (FP)CalcMaxPitchRate() * (FP)Timer_Code.FRAMETIME / (100.0 * 32768.0);
							FP MaxDeltaYaw   = MaxDeltaPitch * sin_roll;
							MaxDeltaPitch	 = MaxDeltaPitch * cos_roll;

							SWord	maxdeltapitch_sign, maxdeltayaw_sign;
							UWord	maxdeltapitch_pos,  maxdeltayaw_pos;
							Math_Lib.Pos((SWord)MaxDeltaPitch, maxdeltapitch_pos, maxdeltapitch_sign);
							Math_Lib.Pos((SWord)MaxDeltaYaw  , maxdeltayaw_pos,   maxdeltayaw_sign);
							FP factor1 = 1, factor2 = 1;
							if(maxdeltapitch_pos > reqdeltapitch_pos) factor1 = (FP)reqdeltapitch_pos / (FP)maxdeltapitch_pos;
							if(maxdeltayaw_pos   > reqdeltahdg_pos)   factor2 = (FP)reqdeltahdg_pos / (FP)maxdeltayaw_pos;
							if(factor1 > factor2) factor1 = factor2;
							pitch += SWord((FP)MaxDeltaPitch * (FP)factor1);
							hdg   += SWord((FP)MaxDeltaYaw   * (FP)factor1);
						}
						fly.cpitch = pitch;

						hdg -= (Angles) CalcHdg ();	//This means that all the heading change is done inside this routine
					}
					else
						AutoCalcPitch();

					UWord DesRange = 256 * ai.morale;	// up to 650 metres
					if(DesRange < WEAPONSRANGE) DesRange = WEAPONSRANGE;

					FP DeltaVel = (Range - DesRange) * 25.0;
					MODLIMIT(DeltaVel, 200000);
					SLong DesVel = leader->vel_ + DeltaVel;
					if(vel_ > DesVel)
					{
						fly.thrustpercent = 0;
						if(vel_ > leader->vel_ + 200000) vel_ = leader->vel_ + 200000;
					}
					else
					{
						fly.thrustpercent = 200;
						if(vel_ < leader->vel_ - 200000) vel_ = leader->vel_ - 200000;
					}
					
	//#define PRINT_WWM_DATA
	#ifdef PRINT_WWM_DATA
	PrintVar(0, 1, "D_Range %.1f ", (FP)(DesRange / 100.0));
	PrintVar(0, 2, "Range   %.1f ", (FP)(Range / 100.0));
	PrintVar(0, 3, "Pitch   %.1f ", (FP)((SWord)pitch / 182.04));
	PrintVar(0, 4, "Pitch_I %.1f ", (FP)((SWord)PitchIntercept / 182.04));
	PrintVar(0, 5, "Headg   %.1f ", (FP)((SWord)hdg / 182.04));
	PrintVar(0, 6, "Headg_I %.1f ", (FP)((SWord)HdgIntercept / 182.04));
	PrintVar(0, 8, "D_Pitch %.1f ", (FP)(reqdeltapitch / 182.04));
	PrintVar(0, 9, "D_Headg %.1f ", (FP)(reqdeltahdg / 182.04));
	PrintVar(0,10, "DesRoll %.1f ", (FP)(DesRoll / 182.04));

	if(PullHard) PrintString(0, 12, "PULL HARD");
	else		 PrintString(0, 12, "         ");

	PrintVar(0,14, "L_Vel   %.1f ", (FP)(leader->vel / 10));
	PrintVar(0,15, "DesVel  %.1f ", (FP)(DesVel / 10));
	PrintVar(0,16, "Vel     %.1f ", (FP)(vel / 10));

	#endif
				}
			}
		}
	}
	
}				
/*	switch (ai.ManStep)
	{
		case PHASE0:
		{
			fly.thrustpercent = ThrustfromFF();
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if (!leader)
				ai.manoeuvre = MANOEUVRE_SELECT;
			else
			{
				COORDS3D target;
				target = leader->World; 									//JIM 02Aug96
				target.Y +=	FT_500;
				InterceptandRange(&target);

				SWord reqdeltahdg, reqdeltahdg_sign;
				UWord reqdeltahdg_pos;
				reqdeltahdg = HdgIntercept - hdg;
				Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);

				SWord reqdeltapitch, reqdeltapitch_sign;
				UWord reqdeltapitch_pos;
				reqdeltapitch = (SWord)PitchIntercept - (SWord)pitch;
				Math_Lib.Pos (reqdeltapitch, reqdeltapitch_pos, reqdeltapitch_sign);

				
				hdg -= (Angles) CalcHdg ();

				if((reqdeltahdg_pos < ANGLES_1Deg) && (reqdeltapitch_pos < ANGLES_1Deg))
					SimpleMoveToRoll(ANGLES_0Deg);
				else
				{
					if(reqdeltahdg_pos < ANGLES_180Deg)
					{
						SWord DesRoll = 0;
						if(reqdeltapitch != 0)
							DesRoll = Math_Lib.arctan(reqdeltahdg, reqdeltapitch);
						else
						{
							if(reqdeltahdg > 0) DesRoll += ANGLES_90Deg;
							if(reqdeltahdg < 0) DesRoll -= ANGLES_90Deg;
						}
						SimpleMoveToRoll(DesRoll);

#define PRINT_WWM_DATA
#ifdef PRINT_WWM_DATA
PrintVar(0, 2, "Range   %.0f ", (FP)(Range / 100.0));
PrintVar(0, 3, "Pitch   %.0f ", (FP)((SWord)pitch / 182.04));
PrintVar(0, 4, "Pitch_I %.0f ", (FP)((SWord)PitchIntercept / 182.04));
PrintVar(0, 5, "Headg   %.0f ", (FP)((SWord)hdg / 182.04));
PrintVar(0, 6, "Headg_I %.0f ", (FP)((SWord)HdgIntercept / 182.04));
PrintVar(0, 8, "D_Pitch %.0f ", (FP)(reqdeltapitch / 182.04));
PrintVar(0, 9, "D_Headg %.0f ", (FP)(reqdeltahdg / 182.04));
PrintVar(0,10, "DesRoll %.0f ", (FP)(DesRoll / 182.04));
#endif
						SWord rollerror = DesRoll - (SWord)roll;
						if((rollerror < ANGLES_45Deg) && (-rollerror < ANGLES_45Deg))
						{
							SWord sin_roll, cos_roll;
							Math_Lib.high_sin_cos(roll, sin_roll, cos_roll);
							FP MaxDeltaPitch = (FP)classtype->maxpitchrate * (FP)Timer_Code.FRAMETIME / 100.0 / 32768.0;
							FP MaxDeltaYaw   = MaxDeltaPitch * sin_roll;
							MaxDeltaPitch	 = MaxDeltaPitch * cos_roll;

	//DeadCode CSB 28/04/99							SWord	maxdeltapitch_sign, maxdeltayaw_sign;
	//DeadCode CSB 28/04/99							UWord	maxdeltapitch_pos,  maxdeltayaw_pos;
	//DeadCode CSB 28/04/99							Math_Lib.Pos((SWord)MaxDeltaPitch, maxdeltapitch_pos, maxdeltapitch_sign);
	//DeadCode CSB 28/04/99							Math_Lib.Pos((SWord)MaxDeltaYaw  , maxdeltayaw_pos,   maxdeltayaw_sign);
							FP factor1 = 1, factor2 = 1;
	//DeadCode CSB 28/04/99							if(maxdeltapitch_pos > reqdeltapitch_pos) factor1 = reqdeltapitch_pos / maxdeltapitch_pos;
	//DeadCode CSB 28/04/99							if(maxdeltayaw_pos   > reqdeltahdg_pos)   factor2 = reqdeltahdg_pos / maxdeltayaw_pos;
	//DeadCode CSB 28/04/99							if(factor1 > factor2) factor1 = factor2;
							pitch += SWord((FP)MaxDeltaPitch * (FP)factor1);
							hdg   += SWord((FP)MaxDeltaYaw   * (FP)factor1);
							fly.cpitch = pitch;
						}
					}
					else 
					{
						AutoCalcPitch();				
						SimpleMoveToHdg(HdgIntercept);
					}
				}				
//DeadCode CSB 28/04/99					InterceptandRange (&leader->World);
				vel = leader->vel;
				if (Range < DANGERRANGE)
					vel -= 100;//CalcVelAlt(0);
				else
					vel += 100;//CalcVelAlt(32000);
			}

		}
	}


}
*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BailOut				
//Author		R. Hyde 			CSB
//Date			Tue 3 Mar 1998		Sun 28 Mar 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleBailOut()
{
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(0);	 
			Trans_Obj.LaunchCanopyEject(this,*mobileitem::currworld);
			AirStrucPtr	unfriendly = *ai.unfriendly;
			unfriendly->SetUnfriendly(NULL);							//CSB 1Aug00
//DeadCode CSB 1Aug00 			unfriendly->ai.unfriendly = NULL;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SimpleMoveToRoll(ANGLES_180Deg);
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SWord swroll = roll;
			if((swroll > ANGLES_135Deg) || (-swroll > ANGLES_135Deg))
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime(100);
			}
			break;
		}
		case PHASE2:
		{
			SimpleMoveToRoll(ANGLES_180Deg);
			PitchIntercept = ANGLES_30Deg;
			AutoCalcPitch();
			if(!TimeLeft())
			{
				Trans_Obj.LaunchParachute(this,this->World,0,*mobileitem::currworld);//RJS 06Dec99
//DeadCode CSB 14Nov00 				Manual_Pilot.DeathSequenceOverrideDiary(this, AUTO_DEATHSEQUENCE);	//RJS 31Oct00

				if((nationality == NAT_RAF) && (!PlayerInGroup()) && (!Math_Lib.rnd(20)))
				{
					AirStrucPtr caller = FindBuddy();
					AirStrucPtr callee = FindGroupLeader();
					if((caller) && (callee) && (caller != callee))
					{
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MAYDAYORBIT, MSG_DESCRIBEFRIEND, caller, *this, callee));
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MAYDAYACKNOWLEDGE, MSG_EJECTREPLY, callee, *this, caller));
					}
				}
			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineAbreast
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLineAbreast()
{
	//only followers go line abreast. We don't link flights

	if (!leader) 
	{//leader, do same as roundabout, get height, dive and then zoom
	 //at end of zoom, choose manoeuvre based on firsttactic
			ai.ManStep = PHASE0;
			ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;			
	}else
	{//follower
		if (		(Range < WEAPONSRANGE)
				&&	(information)
			)
		{
			FireABullet(100);
		}
		{
			switch (ai.ManStep)
			{
				case PHASE0:
				{
		 			SimpleMoveToThrust (100);
					ai.ManStep = PHASE1;
				}
				case PHASE1:
				{
					if(		(!leader) || (leader->movecode != AUTO_COMBAT) 
						||	(		(Leader()->ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_ZOOM)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_LINEABREAST)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_COLLISIONAVOIDANCE)	)	)
					{
						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
						ai.firsttactic = TACTIC_NULL;
					}
					else
						SimpleFlyWing(Leader(), ANGLES_90Deg, 128 * (formpos & 0xf0));
//DeadCode CSB 20Jun00 						Move().AutoFollowWpWing();
				}
			}
		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scatter
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleScatter()
{
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Pincer
//Author		R. Hyde 
//Date			Thu 5 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimplePincer()
{
  	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			AirStrucPtr	unfriendly = *ai.unfriendly;
			SWord	sinbearing,cosbearing;
			SLong	range = METRES1200;
			ANGLES brg;

			brg = (Angles)((SWord)ai.desiredhdg + (SWord)unfriendly->hdg);
			Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);

			despos = unfriendly->World; 			
			despos.X += MULDIVSIN (sinbearing,range,ANGLES_FRACT);
			despos.Z += MULDIVSIN (cosbearing,range,ANGLES_FRACT);
			despos.Y += FT_500;
			InterceptandRange (&despos);

			PitchIntercept = PitchIntercept;
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept);

			if	(	(		(!ManoeuvreTimeLeft())
						&&	(Range < COMBATRANGE)
					)
					||
					(!SubjectFacingTarget(ANGLES_80Deg))
				 )

			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MultiWave
//Author		R. Hyde 
//Date			Wed 18 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleMultiWave()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (3000);
			ai.ManStep = PHASE1;
   		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_10Deg;
			AutoCalcPitch();
			SimpleMoveToHdg (HdgIntercept);

			if  (		(!ManoeuvreTimeLeft())
					&&	(Range < ENGAGERANGE)
				)
					ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeadPursuit
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.63
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLeadPursuit()
{
//	ifcombatakill high
//		turn in parallel plane so that target still visible
//
//	calc ideal lead
//		could base calc on maintaining collision course(hdg-hdgintercept?)
//	actual lead depends also on skill
//
// end after x secs or within DANGERRANGE
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LagPursuit
//Author		R. Hyde 
//Date			Tue 10 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLagPursuit()
{
//
//aim for a point off target's tail
//
//
//	acutal lag depends also on skill
//
//
//
// end after x secs or when go behind traget's tail
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Circumvent
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleCircumvent()
{
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecoyActive
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//rdhvoid	AirStruc::SimpleDecoyActive()
//{
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecoyPassive
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//rdhvoid	AirStruc::SimpleDecoyPassive()
//{
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RoundAbout
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleRoundAbout()
{
	SimpleTurningFight();
	return;

//DEADCODE CSB 03/12/99 	switch (ai.ManStep)
//DEADCODE CSB 03/12/99 	{
//DEADCODE CSB 03/12/99 		case PHASE0:
//DEADCODE CSB 03/12/99 		{
//DEADCODE CSB 03/12/99 			SimpleMoveToThrust(ThrustfromFF());
//DEADCODE CSB 03/12/99 			SetManoeuvreTime (1500);
//DEADCODE CSB 03/12/99  			ai.desiredroll = -(ANGLES)ANGLES_60Deg +
//DEADCODE CSB 03/12/99 					(Angles)(ANGLES_120Deg * Math_Lib.rnd(2)); 
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			ai.ManStep = PHASE1;
//DEADCODE CSB 03/12/99 		}
//DEADCODE CSB 03/12/99 		case PHASE1:
//DEADCODE CSB 03/12/99 		{
//DEADCODE CSB 03/12/99 			SWord desroll = ai.desiredroll;
//DEADCODE CSB 03/12/99 			UWord desroll_pos;
//DEADCODE CSB 03/12/99 			SWord desroll_sign;
//DEADCODE CSB 03/12/99 			Math_Lib.Pos (desroll,desroll_pos,desroll_sign);
//DEADCODE CSB 03/12/99 			if	(SubjectFacingTarget(ANGLES_45Deg))
//DEADCODE CSB 03/12/99 			//when facing unfriendly unroll to move towards it
//DEADCODE CSB 03/12/99 				desroll_pos = desroll_pos/2;
//DEADCODE CSB 03/12/99 			else
//DEADCODE CSB 03/12/99 				desroll_pos = desroll_pos;
//DEADCODE CSB 03/12/99 			if (desroll_sign==MathLib::NEGATIVE)
//DEADCODE CSB 03/12/99 				desroll_pos = -desroll_pos;
//DEADCODE CSB 03/12/99 			desroll = desroll_pos;
//DEADCODE CSB 03/12/99 			SimpleMoveToRoll ((Angles)desroll);
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 			PitchIntercept = BestClimbAngle();
//DEADCODE CSB 03/12/99 			AutoCalcPitch ();
//DEADCODE CSB 03/12/99  			if  (		((Range - (World.Y - ai.unfriendly->World.Y)) < ENGAGERANGE)
//DEADCODE CSB 03/12/99 					&&	((World.Y - ai.unfriendly->World.Y) > FT_3000)
//DEADCODE CSB 03/12/99 				)
//DEADCODE CSB 03/12/99 			{
//DEADCODE CSB 03/12/99  		    	ai.ManStep = PHASE0;
//DEADCODE CSB 03/12/99 				ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
//DEADCODE CSB 03/12/99 			}
//DEADCODE CSB 03/12/99 
//DEADCODE CSB 03/12/99 		}
//DEADCODE CSB 03/12/99 	}
//DEADCODE CSB 03/12/99 
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SplitManoeuvre
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleSplitManoeuvre()
{


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			PitchIntercept = ai.desiredpitch;
			AutoCalcPitch();
			SimpleMoveToHdg (ai.desiredhdg);
			if  (		(ChkAtDesiredHdg (ai.desiredhdg,ANGLES_40Deg))
					||	(!ManoeuvreTimeLeft())
				)
			{
				RndVal	rndnum = Math_Lib.rnd();
				if (		(rndnum > RND50PC)
						&&	(ai.morale < MORALE_MEDIUM)
					)
				{
					ai.ManStep = PHASE0;
					ai.manoeuvre = MANOEUVRE_EXTENSION;
				}else
					ai.manoeuvre = MANOEUVRE_SELECT;
			}

		}
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HeadOn
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Theoretically no offset, 
//				However use a little to avoid collision
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleHeadOn ( )
{
//use desiredpitch and desiredhdg to determine offset
// distance = 2 WINGSPANS
	//just pass to the side
	//poor pilots may turn too early
	//good pilots may turn early
	//on passing pilot skill will dtermine action

	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	
	COORDS3D	target;
	SWord c,s;
	SWord newhdg;
	UByte	FF = FlyingFactor();

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			InterceptandRange(ai.unfriendly);
			SimpleMoveToThrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			SWord dhdg = HdgIntercept - hdg;
			if ((dhdg) > 0)
				ai.desiredhdg = ANGLES_90Deg;
			else
				ai.desiredhdg = ANGLES_270Deg;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			InterceptandRange(ai.unfriendly);
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca) PitchIntercept = bca;
			AutoCalcPitch();

			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((METRES30 * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((METRES30 * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - desiredhdg;
		 	ANGLES reqroll = (Angles)FindRequiredRoll (reqdeltahdg,CombatReqBankData);

			int decisionpoint = Math_Lib.rnd(2);

			if  (		(Range < (2 * BREAKTURNRADIUS ))
					&&	(FF < 200)
				)
			{
				if (decisionpoint)
				{
					if (FF < 90)
					{
						ai.manoeuvre = MANOEUVRE_PANICTURN;
						ai.ManStep = PHASE0;
					}else  
					{
						ai.manoeuvre = MANOEUVRE_BREAKTURN;
						ai.ManStep = PHASE0;
					}
				}else
				{
					ai.ManStep = PHASE2;
				}

			}else if	(		(Range < BREAKTURNRADIUS)
							
						)
			{
				if (decisionpoint)
				{
					ai.manoeuvre = MANOEUVRE_BREAKTURN;
					ai.ManStep = PHASE0;
				}else
				{
					ai.desiredhdg = ai.desiredhdg  + ANGLES_180Deg;
					ai.ManStep = PHASE2;
				}
			}

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE2:
		{
			InterceptandRange(ai.unfriendly);
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca ) PitchIntercept = bca;
			AutoCalcPitch();

			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((METRES30 * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((METRES30 * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - ai.desiredhdg;
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			SimpleMoveToRoll((Angles)reqroll);

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			if	(SubjectOnTargetTail(ANGLES_80Deg))
			{
				if	(		(ai.unfriendly == Manual_Pilot.ControlledAC2)
						&&	(((AirStruc*)ai.unfriendly)->Follower())
					)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON, MSG_HEADON, ((AirStruc*)ai.unfriendly)->Follower(), *this, ((AirStruc*)ai.unfriendly)));

				int startpoint = Math_Lib.rnd(2);
				ai.ManStep = PHASE0;
				if (FF < 90)
				{
					if (startpoint)
						ai.manoeuvre = MANOEUVRE_JINK;
					else
						ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
				}else if (FF < 200)
				{
					if (startpoint)
							ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
					else
							ai.manoeuvre = MANOEUVRE_EXTENSION;
				}else 
				{
					if (startpoint)
							ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
					else
							ai.manoeuvre = MANOEUVRE_BREAKTURN;
				}
			}
		}
	}
	
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineAstern
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLineAstern()
{
//
//use leader's unfriendly
//also use leader's phase
//Phase 0: stay out of way until separation exceeds say 400m
//
//phase 1: if leader 
//				highest speed dive down to target
//			else
//				follow using formation data
//phase 2: when leader in DANGERRANGE
//				do highest speed dive down to target
//			AutoShoot() will do firing	(avoid firing at buddy)
//phase 2:	at 200 yards, zoom climb
//				success depends on flyingskill
//				will break out of manoeuvre if attacked, damaged, winchester, bingo
//phase 3: establish circle around target, go to phase 0				
//
	if (!leader) 
	{//leader, do same as roundabout, get height, dive and then zoom
	 //at end of zoom, choose manoeuvre based on firsttactic
			ai.ManStep = PHASE0;
//DEADCODE CB 18/11/99 			ai.manoeuvre = MANOEUVRE_ROUNDABOUT;			
			ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
			ai.firsttactic = TACTIC_NULL;
	}else
	{//follower
		if (Range < 2 * WEAPONSRANGE)
		{
			ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			ai.ManStep = PHASE0;
			ai.firsttactic = TACTIC_NULL;
		}
		else
		{
			switch (ai.ManStep)
			{
				case PHASE0:
				{
//DeadCode CSB 05/07/99						MOD.Rudder = 0;
					SimpleMoveToThrust (ThrustfromFF());
					ai.ManStep = PHASE1;
//DeadCode CSB 05/07/99						ACM.maxdeltaforclosework = 0.0;
				}
				case PHASE1:
				{
					if(		(!leader) || (leader->movecode != AUTO_COMBAT) 
						||	(		(Leader()->ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_LINEASTERN)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_COLLISIONAVOIDANCE)	)	)
					{
						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
						ai.firsttactic = TACTIC_NULL;
					}
					else
						SimpleFlyWing(Leader(), ANGLES_180Deg, 128 * (formpos & 0xf0));

//DeadCode CSB 20Jun00 					if (!leader)
//DeadCode CSB 20Jun00 					{
//DeadCode CSB 20Jun00 						ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 20Jun00 						ai.firsttactic = TACTIC_NULL;
//DeadCode CSB 20Jun00 					}
//DeadCode CSB 20Jun00 					else
//DeadCode CSB 20Jun00 					{
//DeadCode CSB 20Jun00 						COORDS3D	target;
//DeadCode CSB 20Jun00 						AirStrucPtr MyLeader = Leader();
//DeadCode CSB 20Jun00 						for(;;)
//DeadCode CSB 20Jun00 						{
//DeadCode CSB 20Jun00 							AirStrucPtr Foll = MyLeader->Follower();
//DeadCode CSB 20Jun00 							if(Foll == this)
//DeadCode CSB 20Jun00 								break;			 
//DeadCode CSB 20Jun00 							MyLeader = Foll;
//DeadCode CSB 20Jun00 						}
//DeadCode CSB 20Jun00  						target = MyLeader->World; 
//DeadCode CSB 20Jun00 						target.X += MyLeader->vel_x / 100 ;
//DeadCode CSB 20Jun00 						target.Y += MyLeader->vel_y / 100;
//DeadCode CSB 20Jun00 						target.Z += MyLeader->vel_z / 100;
//DeadCode CSB 20Jun00  						InterceptandRange(&target);
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00 						AutoCalcPitch();
//DeadCode CSB 20Jun00 						SWord DeltaHdg = HdgIntercept - hdg;
//DeadCode CSB 20Jun00 						if((DeltaHdg > ANGLES_0Deg) && (DeltaHdg < ANGLES_HalfDeg))
//DeadCode CSB 20Jun00 							HdgIntercept = hdg + ANGLES_HalfDeg;
//DeadCode CSB 20Jun00 						if((-DeltaHdg > ANGLES_0Deg) && (-DeltaHdg < ANGLES_HalfDeg))
//DeadCode CSB 20Jun00 							HdgIntercept = hdg - ANGLES_HalfDeg;
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00 						CalcHdgRoll();
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							if( roll > ANGLES_60Deg) roll = ANGLES_60Deg;
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							if(-roll > ANGLES_60Deg) {roll = ANGLES_60Deg; roll = -roll;}
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							Float fpitch, fhdg;
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							SWord reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							if  (		(	(fpitch < ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99										&&	(fpitch > -ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99										&&	(fhdg < ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99										&&	(fhdg > -ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99										)
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99								)
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							{
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99								TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							}else
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							{
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99								ANGLES rroll;
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99								rroll = (Angles)(reqroll + roll);
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99								ACM.Roll (rroll);
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99								ACM.ZeroSpecificPower();
//DeadCode CSB 20Jun00 //DeadCode CSB 05/07/99							}
//DeadCode CSB 20Jun00 						SLong DesVel = MyLeader->vel_;
//DeadCode CSB 20Jun00 						Range -= MyLeader->vel_ / 100;
//DeadCode CSB 20Jun00 						if (Range < METRES200)
//DeadCode CSB 20Jun00 							DesVel -= 100000;
//DeadCode CSB 20Jun00  						else
//DeadCode CSB 20Jun00 						{
//DeadCode CSB 20Jun00 							SLong DeltaVel = (Range - METRES400) * 100;
//DeadCode CSB 20Jun00 							MODLIMIT(DeltaVel, 10000);
//DeadCode CSB 20Jun00 							DesVel += DeltaVel;
//DeadCode CSB 20Jun00 						}
//DeadCode CSB 20Jun00 						if(DesVel > vel_) SimpleMoveToThrust(200);
//DeadCode CSB 20Jun00 						else			 SimpleMoveToThrust(0);	
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00 					}
				}
			}
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleVicAttack
//Author		Craig Beeston
//Date			Wed 15 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleVicAttack()
{
	switch(ai.ManStep)
	{
		case PHASE0:	//Initialise
		{
			SimpleMoveToThrust(90);
			if(position())
				ai.ManStep = PHASE2;
			else
			{
				ai.ManStep = PHASE1;
				SetManoeuvreTime(250 * formpos);
			}
		}

		case PHASE1:	//Wait a bit
		{
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SimpleMoveToRoll(ANGLES_0Deg);
			if(!TimeLeft())
				ai.ManStep = PHASE2;
			break;
		}

		case PHASE2:	//Approach Target
		{
			if(position() == 0)
			{
				InterceptandRange(ai.unfriendly);
				AutoCalcPitch();
				SWord desroll = FindRequiredRoll (hdg - HdgIntercept, GentleBankData);
				SimpleMoveToRoll(desroll);
			}
			else
			{
				AirStrucPtr lead = FindLeadCandidate();
				if((lead) && (lead->ai.manoeuvre == MANOEUVRE_VICATTACK))
					SimpleFlyWing(lead);
			}
			
			if(Distance3DSquared(&ai.unfriendly->World) < FP(50000) * FP(50000))
			{
				SimpleMoveToThrust(100);
				ai.ManStep = PHASE3;
			}
			break;
		}

		case PHASE3:	//Aim at own Targets
		{
			InterceptandRange(ai.unfriendly);
			AutoCalcPitch();
			SWord desroll = FindRequiredRoll (hdg - HdgIntercept, CombatReqBankData);
			SimpleMoveToRoll(desroll);

			if(Range < 5000)
			{
				ai.ManStep = PHASE4;
				SetManoeuvreTime(500);
			}
			break;
		}

		case PHASE4:	//Hard Dive
		{
			PitchIntercept = ANGLES_315Deg;
			AutoCalcPitch();
			SimpleMoveToRoll(ANGLES_0Deg);
			if(!TimeLeft())
			{
				ai.firsttactic = TACTIC_NULL;
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShootTooEarly
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleShootTooEarly()
{
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LagRoll
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Ref1.67..	
//				manoeuvre incorporates barrel roll attack(1.69..)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLagRoll()
{
//maintain throttle
//roll towards unfriendly for 10-20deg hdg (f(AOT))
//go upside down
//climb to loose speed to corner speed
//exit manoeuvre when unfriendly goes behind or time out

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExtensionManoeuvre
//Author		R. Hyde 
//Date			Thu 5 Mar 1998
//
//Description	1.23
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleExtensionManoeuvre()
{
//attempt to get to extend range to ENGAGERANGE safely
//this is to try to escape
//or get distance to try again
//if at same level
//	good mig pilots should go up
//	good us pilots should go down
//if higher than bogey
//	
//
//ref1.70
//if turning good pilots will initially unload and
//retain roll to disguise manoeuvre 
//
//initially aircraft could be closing

}


void ACMAirStruc::SimpleDivingSpin()
{
	switch(ai.ManStep)
	{
		case 0:
		{
			SimpleMoveToThrust(100);
			ai.ManStep = 1;
			SetManoeuvreTime(1000);
		}
		case 1:
		{
			SWord deltapitch = pitch - ANGLES_345Deg;
			SWord desroll = ANGLES_90Deg - deltapitch;
			if(SWord(roll) < 0)
				desroll *= -1;
			SimpleMoveToRoll(desroll);
			PitchIntercept = ANGLES_345Deg;
			AutoCalcPitch();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReverseTurn
//Author		R. Hyde 
//Date			Thu 5 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleReverseTurn()
{
//	DesiredRoll = opposite of existing
//	Move to desired and hold for 3 secs
//	if (good)
//		out of plane
//	Close brakes if open at end of manoeuvre(used in selfasbait())
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelfAsBait
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	Ref19
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleSelfAsBait()
{
//
//let bandit out turn you
//just as he get lead, pop brakes
//goto RevereTurn
//
//this could be where bandit is on your tail, wait for him to get close 
//before turning
//keep buddy in combat spread so that you can sandwich him
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Jink
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleJink()
{
//
//fast 90 deg roll
//hard push or pull on stick
//hold for 2-3 secs
//
//flyingability determines rollrate and stick push pull
//combatablity determines length of manoeuvre
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakTurn
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//				Maximum performance turn towards unfriendly
//				Aim for corner speed (see summary at top of acmman.cpp)
//				When quoted as IAS, corner speed is practically a constant
//				cornerspeed should be part of the planetype
//				corner speed occurs at max g allowed for ac
//				max g should be part of the planetype 
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleBreakTurn()
{
//	roll = cos -1 (1/maxg)
//ability to reach roll = f(flyingskill)
//ability to hold corner vel = f(flyingskill)
//	option to nose down to keep speed up and nose up to reduce speed
//hold for 4-5 secs
//
//low morale gives a very lazy turn
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LazyTurn
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLazyTurn()
{
//
//	Choose a roll 10-40deg
//		= f(morale)
//	continue on turn for 10s
//	if (ai.morale > MORALE_GOOD)
//		if (Range < WEAPONS)
//			end manoeuvre
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Break180
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.26
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleBreak180()
{
//roll 180
//pull hard until pitch 45 deg down
//slowly unroll for x secs
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakLow
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleBreakLow()
{
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
 			SimpleMoveToThrust(100);
			if(SWord(HdgIntercept - hdg) > 0)
				ai.desiredroll = ANGLES_135Deg;
			else
				ai.desiredroll = ANGLES_225Deg;
			ai.ManStep = PHASE1;
			SetManoeuvreTime(500);
 			break;	
 		}
 		case PHASE1:
 		{	
			SimpleMoveToRoll(ai.desiredroll);
 			PitchIntercept = ANGLES_45Deg;
			PitchIntercept = -PitchIntercept;
			AutoCalcPitch();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
//decide which way to roll to go down
//roll 90
//pull hard until pitch 45 deg down
//slowly unroll for x secs
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakHigh
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleBreakHigh()
{
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
 			SimpleMoveToThrust(100);
			if(SWord(HdgIntercept - hdg) > 0)
				ai.desiredroll = ANGLES_45Deg;
			else
				ai.desiredroll = ANGLES_315Deg;
			ai.ManStep = PHASE1;
			SetManoeuvreTime(500);
 			break;	
 		}
 		case PHASE1:
 		{	
			SimpleMoveToRoll(ai.desiredroll);
 			PitchIntercept = ANGLES_45Deg;
			AutoCalcPitch();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Break90
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.27
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleBreak90()
{
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
 			SimpleMoveToThrust(100);
			if(SWord(HdgIntercept - hdg) > 0)
				ai.desiredroll = ANGLES_90Deg;
			else
				ai.desiredroll = ANGLES_270Deg;
			ai.ManStep = PHASE1;
			SetManoeuvreTime(500);
 			break;	
 		}
 		case PHASE1:
 		{	
			SimpleMoveToRoll(ai.desiredroll);
 			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

//	if (classtype->aerobaticfactor == AEROBATIC_MIG)
//		BreakHigh();
//	else if (	(ai.morale > MORALE_MEDIUM)
//			&&	(ClosureLessThan(MPH50))
//			)
//				BreakHigh();
//			else
//				BreakLow();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HiGBarrelRoll
//Author		R. Hyde						Craig Beeston
//Date			Mon 9 Mar 1998				Sun 13 Jun 1999
//
//Description	1.30	
//				Defensive manoeuvre
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleHiGBarrelRoll()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(0);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SWord DesRoll = ANGLES_45Deg;	DesRoll = -DesRoll;
			SimpleMoveToRoll(DesRoll);

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
				ai.ManStep = PHASE2;
		
			break;
		}
		case PHASE2:
		{
			PitchIntercept = ANGLES_45Deg;
			AutoCalcPitch();
			SWord DesRoll = 2 * SWord(pitch);
			SimpleMoveToRoll(DesRoll);

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
				ai.ManStep = PHASE3;
		
			break;
		}
		case PHASE3:
		{
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SWord DesRoll = ANGLES_180Deg - 2 * SWord(pitch);
			SimpleMoveToRoll(DesRoll);

			SWord dHdg = CalcHdg();
			hdg -= 2 * dHdg;

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
				ai.ManStep = PHASE4;
		
			break;
		}
		case PHASE4:
		{
			PitchIntercept = ANGLES_45Deg;	PitchIntercept = -PitchIntercept;
			AutoCalcPitch();
			SWord DesRoll =  -2 * SWord(pitch) - ANGLES_180Deg;
			SimpleMoveToRoll(DesRoll);

			SWord dHdg = CalcHdg();
			hdg -= 2 * dHdg;

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
				ai.ManStep = PHASE5;
		
			break;
		}
		case PHASE5:
		{
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			SWord DesRoll =  2 * SWord(pitch);
			SimpleMoveToRoll(DesRoll);

			if(((SWord)pitch == (SWord)PitchIntercept) && ((SWord)roll == DesRoll))
			{
				SimpleMoveToThrust(ThrustfromFF());
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
		
			break;
		}
	}
		
//DeadCode CSB 13/06/99			case PHASE1:
//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99				SimpleMoveToRoll(-ANGLES_45Deg);
//DeadCode CSB 13/06/99				PitchIntercept = ANGLES_0Deg;
//DeadCode CSB 13/06/99				AutoCalcPitch();
//DeadCode CSB 13/06/99				if(-(SWord)roll == ANGLES_45Deg)
//DeadCode CSB 13/06/99					ai.ManStep = PHASE2;
//DeadCode CSB 13/06/99				break;
//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99			case PHASE2:
//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99				SimpleMoveToRoll(roll + ANGLES_90Deg);
//DeadCode CSB 13/06/99				SWord sin, cos;
//DeadCode CSB 13/06/99				Math_Lib.high_sin_cos(roll, sin, cos);
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99				PitchIntercept = (Angles)(sin / 2);
//DeadCode CSB 13/06/99	 			AutoCalcPitch();
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99				if(-(SWord)roll > ANGLES_90Deg)
//DeadCode CSB 13/06/99					ai.ManStep = PHASE3;
//DeadCode CSB 13/06/99				break;
//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99			case PHASE3:
//DeadCode CSB 13/06/99			{
//DeadCode CSB 13/06/99				SimpleMoveToRoll(roll + ANGLES_90Deg);
//DeadCode CSB 13/06/99				SWord sin, cos;
//DeadCode CSB 13/06/99				Math_Lib.high_sin_cos(roll, sin, cos);
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99				PitchIntercept = (Angles)(sin / 2);
//DeadCode CSB 13/06/99	  			AutoCalcPitch();
//DeadCode CSB 13/06/99	
//DeadCode CSB 13/06/99				if((SWord)roll > ANGLES_0Deg)
//DeadCode CSB 13/06/99				{
//DeadCode CSB 13/06/99					SimpleMoveToThrust(ThrustfromFF());
//DeadCode CSB 13/06/99					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 13/06/99				}
//DeadCode CSB 13/06/99				break;
//DeadCode CSB 13/06/99			}
//DeadCode CSB 13/06/99		}
	
//max g, roll in one direction
//nose low or high
//unbalanced flight, power reduction, increased drag for better pilots
//
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PanicTurn
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.30
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimplePanicTurn()
{
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnBalancedFlight
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleUnBalancedFlight()
{
//skid and slip while making turns
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrackingShot
//Author		R. Hyde 
//Date			Tue 10 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleTrackingShot()
{
//aim for gun solution
//actually modify pitch and heading within limits on top of changes produced by manoeuvre
//just enough lead
//modify speed(rpm and airbrakes) to stay on tail
//
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SnapShot
//Author		R. Hyde 
//Date			Tue 10 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleSnapShot()
{
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StayOnTail
//Author		R. Hyde 
//Date			Fri 20 Mar 1998
//
//Description	This is not a good idea, very aggressive
//				Stay at corner speed or less
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleStayOnTail()
{
//	if necessayr shed energy:
//		turn
//		brakes
//		throttle
//	to stay on tail

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleHeadOnAttack
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleHeadOnAttack()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			if(World.Y < ai.unfriendly->World.Y)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
				ai.firsttactic = TACTIC_NULL;
				return;
			}
			if(formpos == 0)			//Find leader of bomber group
			{
				AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
				AirStrucPtr target = unf->GetLeadAc();
//DeadCode CSB 17Aug00 				for(AirStrucPtr t = unf; t; t = t->fly.leadflight)
//DeadCode CSB 17Aug00 					for(AirStrucPtr l = t; l; l = l->Leader())
//DeadCode CSB 17Aug00 						if(l->formpos == 0)
//DeadCode CSB 17Aug00 							target = l;

				if(target != unf)
				{
					SetUnfriendly(target);								//CSB 1Aug00
//DeadCode CSB 1Aug00 					if(unf->ai.attacker == this)
//DeadCode CSB 1Aug00 						unf->ai.attacker = NULL;
//DeadCode CSB 1Aug00 
//DeadCode CSB 1Aug00 					ai.unfriendly = target;
//DeadCode CSB 1Aug00 					if(target->ai.attacker == NULL)
//DeadCode CSB 1Aug00 						target->ai.attacker = this;
				}
			}
			SimpleMoveToThrust(90);
			SetManoeuvreTime(6000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if(formpos == 0)
			{
				COORDS3D despos = ai.unfriendly->World;
				Float sin, cos;
				Math_Lib.high_sin_cos(AirStrucPtr(ai.unfriendly)->hdg, sin, cos);
				despos.X += sin * 200000.0;	//2 km
				despos.Y += 75000;
				despos.Z += cos * 200000.0;	//2 km
				Range = Distance3D(&despos, &World);
				AirStrucPtr unf = AirStrucPtr(ai.unfriendly);

				FP deltaTX = (10000.0 * FP(despos.X - World.X)) / FP(vel_x - unf->vel_x);
				FP deltaTZ = (10000.0 * FP(despos.Z - World.Z)) / FP(vel_z - unf->vel_z);

				MODMAXMIN(deltaTX, 0, 6000);
				MODMAXMIN(deltaTZ, 0, 6000);

				despos.X += unf->vel_x * (deltaTX + deltaTZ) * 0.5 * 0.0001;
				despos.Z += unf->vel_z * (deltaTX + deltaTZ) * 0.5 * 0.0001;

				InterceptandRange(&despos);
				
				AutoCalcPitch();
				SWord desroll = FindRequiredRoll (hdg - HdgIntercept, GentleBankData);
				SimpleMoveToRoll(desroll);
				if(Range < 5000)
					ai.ManStep = PHASE2;
//DEADCODE DAW 26/11/99 				if(!TimeLeft())
//DEADCODE DAW 26/11/99 					ai.manoeuvre = MANOEUVRE_SELECT;
				break;
			}
			else
			{
				AirStrucPtr lf = FindGroupLeader();
				SetManoeuvreTime(0);
//DEADCODE DAW 30/11/99 				AutoFollowWpWing(lf);
				despos = *PositionWRTLeader(lf);
				despos.X -= (lf->vel_x * Timer_Code.FRAMETIME) / 10000;
				despos.Y -= (lf->vel_y * Timer_Code.FRAMETIME) / 10000;
				despos.Z -= (lf->vel_z * Timer_Code.FRAMETIME) / 10000;

				FP leadrange = 25000;
				despos.X += FP(lf->vel_x) * leadrange / FP(lf->vel_);
				despos.Y += FP(lf->vel_y) * leadrange / FP(lf->vel_);
				despos.Z += FP(lf->vel_z) * leadrange / FP(lf->vel_);
				InterceptandRange(&despos);
				FP desroll = FindRequiredRoll(SWord(hdg) - SWord(HdgIntercept), CombatReqBankData);
				if((Range - leadrange > -5000) && (Range - leadrange < 5000))
					desroll += SWord(lf->roll);
				MODLIMIT(desroll, ANGLES_90Deg);
				SimpleMoveToRoll(desroll);
				AutoCalcPitch();

				FP range	 = FP(despos.X - World.X) * FP(lf->vel_x) + FP((despos.Z - World.Z)) * FP(lf->vel_z);
				range       /= FP(lf->vel_);
				FP desvel	 = lf->vel_ + 10 * (range - leadrange);
				CalcVelAlt(desvel);

				if(lf->ai.ManStep == PHASE2)
				{
					AirStrucPtr leadbomber = AirStrucPtr(lf->ai.unfriendly);
					AirStrucPtr target     = leadbomber;
					for(AirStrucPtr t = leadbomber; t; t = t->Follower())
						if( (t->position()) && ((position() & 0x01) == (t->position() & 0x01)) )
						{
							target = t;
							break;
						}
					
//DeadCode CSB 1Aug00 					AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
//DeadCode CSB 1Aug00 					if(unf->ai.attacker == this)
//DeadCode CSB 1Aug00 						unf->ai.attacker = NULL;
//DeadCode CSB 1Aug00 
//DeadCode CSB 1Aug00 					ai.unfriendly = target;
//DeadCode CSB 1Aug00 					if((AirStrucPtr(ai.unfriendly))->ai.attacker == NULL)
//DeadCode CSB 1Aug00 						(AirStrucPtr(ai.unfriendly))->ai.attacker = this;
					SetUnfriendly(target);

					ai.ManStep = PHASE2;
				}
				break;
			}
		}
		case PHASE2:
		{
			SimpleMoveToRoll(ANGLES_180Deg);
			SWord swroll = roll;
			hdg -= Angles(CalcHdg());

			if((swroll > ANGLES_170Deg) || (-swroll > ANGLES_170Deg))
				ai.ManStep = PHASE3;
			break;
		}
		case PHASE3:
		{
			PitchIntercept = ANGLES_270Deg;
			AutoCalcPitch();
			hdg -= Angles(CalcHdg());

			if(SWord(pitch) == (ANGLES_270Deg - 65536))
			{
				hdg  += ANGLES_180Deg;
				pitch = Angles(-32767 - SWord(pitch));
				roll += ANGLES_180Deg;
				ai.ManStep = PHASE4;
				SetManoeuvreTime(1000);
			}
			break;
		}
		case PHASE4:
		{
			AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
			COORDS3D targ = unf->World;
			InterceptandRange(ai.unfriendly);
			SWord dhdg   = SWord(hdg)   - SWord(HdgIntercept);
			SWord dpitch = SWord(pitch) - SWord(PitchIntercept);

			SWord swpitch = PitchIntercept;
			SWord deltahdg = unf->hdg - ANGLES_180Deg - HdgIntercept;
			HdgIntercept -= deltahdg;	//Aim for a head to head

			SWord swhdg = SWord(hdg) - SWord(HdgIntercept);

			PitchIntercept = Angles(2 * SWord(PitchIntercept));
			AutoCalcPitch();
			SWord desroll = -2.0 * swhdg;
			SimpleMoveToRoll(desroll);
		
			if(Range < 2 * INSIDEWEAPONSRANGE)
			{
//DEADCODE CSB 27/01/00 				PrintVar(70, 20, "h %.2f ", FP(dhdg   / 182.04));
//DEADCODE CSB 27/01/00 				PrintVar(70, 21, "p %.2f ", FP(dpitch / 182.04));
				if(dhdg   < 0)	dhdg   *= -1;
				if(dpitch < 0)	dpitch *= -1;
				if(dpitch < dhdg) dpitch = dhdg;
				if((Range < WEAPONSRANGE) && (FP(Range) * FP(dpitch) * 0.0001 < 1000))
					FireABullet(100);

//DEADCODE CSB 27/01/00 				PrintVar(70, 22, "R %.0f ", FP(FP(Range) * FP(dpitch) * 0.0001));
			}

			if(!TimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;			
				ai.firsttactic = TACTIC_NULL;
			}

			if(Range < 20000)
			{	
				ai.ManStep = PHASE5;
				SetManoeuvreTime(200);
			}
			break;
		}
		case PHASE5:
		{
			SimpleMoveToRoll(0);
			PitchIntercept = ANGLES_315Deg;
			AutoCalcPitch();
			if(!TimeLeft())
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
				ai.firsttactic = TACTIC_NULL;
			}

			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleLufberry
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleLufberry()
{
	if((!leader) && (!follower))
	{
		ai.manoeuvre = MANOEUVRE_SELECT;
		return;
	}

	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime(3000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord no_ac = 0;
			FP x = 0;
			FP y = 0;
			FP z = 0;
			for(AirStrucPtr ac = FindGroupLeader(); ac; ac = ac->fly.nextflight)
				for(AirStrucPtr f = ac; f; f = f->Follower())
				{
					no_ac++;
					x += f->World.X;
					y += f->World.Y;
					z += f->World.Z;
				}

			x /= no_ac;
			y /= no_ac;
			z /= no_ac;

			COORDS3D targ;
			targ.X = x;
			targ.Y = y;
			targ.Z = z;

			AirStrucPtr target = NULL;
			if(formpos == 0)	//This is lead aircraft and therefore must chase last aircraft
			{
				for(AirStrucPtr nf = this; nf; nf = nf->fly.nextflight)
					if(nf->fly.nextflight == NULL)
						for(AirStrucPtr f = nf; f; f = f->Follower())
							target = f;
			}
			else
			{
				AirStrucPtr leadac = FindGroupLeader();

				for(AirStrucPtr nf = leadac; nf; nf = nf->fly.nextflight)
				{
					if(nf->fly.nextflight == this)
						for(AirStrucPtr f = nf; f; f = f->Follower())
							target = f;
					else
						for(AirStrucPtr f = nf; f; f = f->Follower())
							if(f->follower == this)
								target = f;
				}
			}
			

			InterceptandRange(&targ);
			FP desrange = 4400 * no_ac;
			FP rangesq = Distance3DSquared(&(target->World));
			FP desvel;
			if(rangesq > (50000.0 * 50000.0))
				fly.thrustpercent = 100;
			else
				fly.thrustpercent = 50;

//DEADCODE DAW 29/11/99 			FP deltarange = (25000 - range) / 10;
//DEADCODE DAW 29/11/99 			MODLIMIT(deltarange, 1000);
//DEADCODE DAW 29/11/99 			desrange += deltarange;

			SWord deshdg;
			if(Range > 3 * desrange)
				deshdg = HdgIntercept;
			else
				deshdg = HdgIntercept + ANGLES_90Deg * (3 - Range / desrange) * 0.5;

			SWord deltahdg = SWord(hdg) - SWord(deshdg);
			SWord desroll = FindRequiredRoll(deltahdg, CombatReqBankData);
			SimpleMoveToRoll(desroll);
			PitchIntercept = Angles(SWord(PitchIntercept) / 2);
			AutoCalcPitch();
			
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleSteepDive
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleSteepDive()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord swroll = roll;
			if((swroll < ANGLES_90Deg) && (-swroll < ANGLES_90Deg))
				SimpleMoveToRoll(ANGLES_0Deg);
			else
				SimpleMoveToRoll(ANGLES_180Deg);
			
			PitchIntercept = Angles(SWord(ANGLES_300Deg));

			AutoCalcPitch();

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleUpAndUnder
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleUpAndUnder()
{
	if(ai.unfriendly == NULL)
	{
		ai.manoeuvre = MANOEUVRE_SELECT;
		return;
	}

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ai.ManStep = PHASE1;
			SetManoeuvreTime(3000);
		}
		case PHASE1:
		{
			const Float desrange = 30000;
			const Float deltaalt = 10000;

			AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
			COORDS3D target = unf->World;
			Float sin, cos;
			Math_Lib.high_sin_cos(unf->hdg, sin, cos);
			target.X -= desrange * sin;
			target.Y -= deltaalt;
			target.Z -= desrange * cos;
			InterceptandRange(&target);
			AutoCalcPitch();
		
			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			SimpleMoveToRoll(reqroll);

//			CalcVelAlt();

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			if(Range < 1000)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime(3000);
			}
			break;
		}
		case PHASE2:
		{
			COORDS3D target = ai.unfriendly->World;
			SLong dx, dy, dz;
			CalcLead(this, AirStrucPtr(ai.unfriendly), dx, dy, dz, FALSE);
			target.X += dx;
			target.Y += dy;
			target.Z += dz;

			InterceptandRange(&target);
			AutoCalcPitch();
//			CalcVelAlt();

			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			SimpleMoveToRoll(reqroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			if(Range < 20000)
			{
				ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = PHASE0;
				SetManoeuvreTime(1500);
			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleStallTurn
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleStallTurn()
{
	switch(ai.ManStep)
	{
		case 0:
		{
			SimpleMoveToThrust(0);
			ai.ManStep = 1;
			SetManoeuvreTime(2000);
		}
		case 1:
		{
			PitchIntercept = ANGLES_60Deg;
			AutoCalcPitch();
			SimpleMoveToRoll(ANGLES_0Deg);
			if(vel_ < classtype->minvel / 2)
			{
				ai.ManStep = 2;
				if(SWord(HdgIntercept - hdg) > 0)
					ai.desiredroll = ANGLES_45Deg;
				else
					ai.desiredroll = ANGLES_315Deg;
				ai.desiredhdg = HdgIntercept;
			}
			break;
		}
		case 2:
		{
			SWord desroll = 0;
			if(SWord(pitch) > 0)
				desroll = ai.desiredroll;
			if(SWord(roll) < desroll)
				roll += (ANGLES_45Deg * Timer_Code.FRAMETIME) / 200;
			else
				roll -= (ANGLES_45Deg * Timer_Code.FRAMETIME) / 200;
			SWord deltaang = (ANGLES_30Deg * Timer_Code.FRAMETIME) / 100;
			pitch -= deltaang;
			hdg += (2 * SWord(roll) * Timer_Code.FRAMETIME) / 100;
			if(SWord(pitch) < SWord(ANGLES_315Deg))
			{
				ai.ManStep = 3;
				SimpleMoveToThrust(100);
			}
			break;
		}
		case 3:
		{
			AutoCalcPitch();
			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			SimpleMoveToRoll(reqroll);
			if(vel_ > classtype->minvel)
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleSlashingAttack
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleSlashingAttack()
{
	if(ai.unfriendly == NULL)
	{
		ai.manoeuvre = MANOEUVRE_SELECT;
		return;
	}

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			fly.thrustpercent = 100;
			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			InterceptandRange(ai.unfriendly);
			AutoCalcPitch();

			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			SimpleMoveToRoll(reqroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			if(Range < WEAPONSRANGE)
			{
				SWord deltahdg   = SWord(hdg)   - SWord(HdgIntercept);
				SWord deltapitch = SWord(pitch) - SWord(PitchIntercept);
				if(deltahdg   < 0)	deltahdg   *= -1;
				if(deltapitch < 0)	deltapitch *= -1;
				if((deltahdg < ANGLES_30Deg) && (deltapitch < ANGLES_30Deg))
				{
					ai.ManStep = PHASE2;
					SetManoeuvreTime(2000);
				}
			}
			break;
		}
		case PHASE2:
		{
			COORDS3D target = ai.unfriendly->World;
			SLong	 dx, dy, dz;
			CalcLead(this, AirStrucPtr(ai.unfriendly), dx, dy, dz, FALSE);
			target.X += dx;
			target.Y += dy;
			target.Z += dz;
			InterceptandRange(&target);

			SWord deshdg = ANGLES_30Deg;
			deshdg *= (55000.0 - FP(Range)) / 30000.0;
			if(SWord(roll) < 0)
				deshdg *= -1;
			deshdg += HdgIntercept;
			
			SWord deltahdg = deshdg - SWord(hdg);
			SWord desroll = ANGLES_60Deg;
			
			if(deltahdg < 0)
			{
				desroll  *= -1;
				deltahdg *= -1;
			}
//DEADCODE DAW 30/11/99 			SWord deltaroll = desroll - SWord(roll);
//DEADCODE DAW 30/11/99 			if((deltaroll < ANGLES_20Deg) && (-deltaroll < ANGLES_20Deg))
//DEADCODE DAW 30/11/99 			{
//DEADCODE DAW 30/11/99 				ACM.LiftLimit();
//DEADCODE DAW 30/11/99 				ACM.SetRudder(0);
//DEADCODE DAW 30/11/99 				if(desroll > 0)
//DEADCODE DAW 30/11/99 					desroll += 5 * (SWord(pitch) - SWord(PitchIntercept));
//DEADCODE DAW 30/11/99 				else
//DEADCODE DAW 30/11/99 					desroll -= 5 * (SWord(pitch) - SWord(PitchIntercept));
//DEADCODE DAW 30/11/99 			}
//DEADCODE DAW 30/11/99 			else
//DEADCODE DAW 30/11/99 				ACM.Pitch(PitchIntercept);
			AutoCalcPitch();

			SimpleMoveToRoll(desroll);

			if((!TimeLeft()) || (Range < 10000))
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleClimbTurn
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleClimbTurn()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(100);
			SetManoeuvreTime(2000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_30Deg;
			AutoCalcPitch();
			SWord desroll = ANGLES_45Deg;
			if(SWord(roll) < ANGLES_0Deg)
				desroll *= -1;
			SimpleMoveToRoll(desroll);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleRoll360
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleRoll360()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_30Deg;
			AutoCalcPitch();
			SimpleMoveToRoll(ANGLES_0Deg);
			hdg -= (Angles) CalcHdg ();

			SWord swroll  = roll;
			SWord swpitch = pitch;
			if((swroll < ANGLES_5Deg) && (-swroll < ANGLES_5Deg) && (swpitch > ANGLES_25Deg) && (swpitch < ANGLES_35Deg))
			{				
				ai.ManStep = PHASE2;
				SetManoeuvreTime(1000);
			}
			break;
		}
		case PHASE2:
		{
			PitchIntercept = ANGLES_30Deg;
			AutoCalcPitch();
			FP desroll = TimeLeft();
			if(!desroll)
				ai.manoeuvre = MANOEUVRE_SELECT;
			desroll *= 65.536;
			SimpleMoveToRoll(SWord(desroll));
			hdg -= (Angles) CalcHdg ();
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleStraffe
//Author		Craig Beeston
//Date			Mon 29 Nov 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleStraffe()
{
	if((ai.unfriendly != NULL) && (ai.unfriendly->Status.size == AIRSTRUCSIZE) && ((AirStrucPtr(ai.unfriendly))->vel_ < 100000))	//10 m/s
	{
		//Do Nothing 
	}
	else
	{
		ai.manoeuvre = MANOEUVRE_SELECT;
		return;
	}

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(100);
			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			COORDS3D target = ai.unfriendly->World;
			InterceptandRange(&target);
			SWord deltahdg = SWord(HdgIntercept - hdg);
			SLong reqroll = 10 * deltahdg;
			MODLIMIT(reqroll, ANGLES_75_5Deg);
			if(Range < 75000)
			{
				reqroll = 0;
				ai.ManStep = 3;
				SetManoeuvreTime(2000);
			}
			SimpleMoveToRoll(reqroll);
			PitchIntercept = ANGLES_0Deg;//Angles(SWord(PitchIntercept) / 2);
			AutoCalcPitch();

			if( ((deltahdg < ANGLES_10Deg) && (-deltahdg < ANGLES_10Deg)) && (Range < 500000))
				ai.ManStep = PHASE2;

			break;
		}
		case PHASE2:
		{
			InterceptandRange(ai.unfriendly);
			AutoCalcPitch();
			SWord deltahdg   = SWord(HdgIntercept   - hdg) ;
			SWord deltapitch = SWord(PitchIntercept - pitch) ;
			SLong reqroll = 10 * deltahdg;
			MODLIMIT(reqroll, ANGLES_75_5Deg);
			SimpleMoveToRoll(reqroll);

			if(deltahdg   < 0)	deltahdg   *= -1;
			if(deltapitch < 0)	deltapitch *= -1;
			if(deltapitch < deltahdg) deltapitch = deltahdg;
			if((Range < WEAPONSRANGE) && (FP(Range) * FP(deltapitch) * 0.0001 < 1000))
				FireABullet(100);

			if(Range < 20000)
			{
				ai.ManStep = PHASE3;
				SetManoeuvreTime(1500);
			}
			break;
		}
		case PHASE3:
		{
			SimpleMoveToRoll(0);
			PitchIntercept = ANGLES_20Deg;
			AutoCalcPitch();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimplePeelOff
//Author		Craig Beeston
//Date			Mon 18 Sep 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimplePeelOff()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust(100);
			ai.ManStep = PHASE1;
			if(SWord(HdgIntercept - hdg) > 0)
				ai.desiredroll = ANGLES_90Deg;
			else
				ai.desiredroll = ANGLES_270Deg;
			int numac = 0;
			for(AirStrucPtr ld = FindFormpos0(); ld; ld = ld->fly.nextflight)
				for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
					if(ac != this)
					{
						FP dotprod = FP(vel_z) * FP(ac->World.X - World.X) - FP(vel_x) * FP(ac->World.Z - World.Z);
						dotprod /= FP(vel_) * FSqrt(FP(ac->World.X - World.X) * FP(ac->World.X - World.X) + FP(ac->World.Z - World.Z) * FP(ac->World.Z - World.Z));
						if((dotprod > 0) == (ai.desiredroll == ANGLES_90Deg))
							numac++;
					}
			SetManoeuvreTime(50 * numac);
		}
		case PHASE1:
		{
			SimpleMoveToRoll(ANGLES_0Deg);
			PitchIntercept = ANGLES_0Deg;
			AutoCalcPitch();
			if(!TimeLeft())
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime(100);
				ai.desiredpitch = ANGLES_0Deg;
				InterceptandRange(Persons2::PlayerGhostAC);
				SWord dhdg = HdgIntercept - hdg;
				if(ai.desiredroll < 0)	dhdg = -dhdg;
				if((Range < 2500) && (dhdg > ANGLES_45Deg) && (dhdg < ANGLES_135Deg))
					if(SWord(PitchIntercept) < 0)
						ai.desiredpitch = ANGLES_45Deg;
					else
						ai.desiredpitch = ANGLES_135Deg;
			}
			break;
		}
		case PHASE2:
		{
			SimpleMoveToRoll(ai.desiredroll);
			PitchIntercept = ai.desiredpitch;
			AutoCalcPitch();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}

		
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleFlyThroughCloud
//Author		Craig Beeston
//Date			Mon 10 Jan 2000
//
//Description	Follows enemy into cloud and predicts where he will re-emerge
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleFlyThroughCloud()
{
	if(ai.ManStep == 0)
	{
		AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
		if(unf)
		{
			FP dt = 1000;
			if(MissManCampSky().CloudLayerCover(&World) > 0)
				dt = 3000;
			Coords3D targ = unf->World;
			targ.X += unf->vel_x * dt / 10000;
			targ.Y += unf->vel_y * dt / 10000;
			targ.Z += unf->vel_z * dt / 10000;
			InterceptandRange(&targ);
			ai.desiredhdg   = HdgIntercept;
			ai.desiredpitch = PitchIntercept;
//DeadCode CSB 1Aug00 			if(unf->ai.attacker == this)
//DeadCode CSB 1Aug00 				unf->ai.attacker = NULL;
		}
		else
		{
			ai.desiredpitch = pitch;
			ai.desiredhdg   = hdg;
		}

//DeadCode CSB 1Aug00 		ai.unfriendly = NULL;
		SetUnfriendly(NULL);											//CSB 1Aug00
		SetManoeuvreTime(300);
		ai.ManStep = PHASE1;
	}

	PitchIntercept = ai.desiredpitch;
	AutoCalcPitch();
	SWord reqroll = FindRequiredRoll(hdg - ai.desiredhdg, CombatReqBankData);
	SimpleMoveToRoll(reqroll);
	if(!TimeLeft())
	{
		if((ai.unfriendly) || (ai.ManStep >= 10))
			ai.manoeuvre = MANOEUVRE_SELECT;
		else
		{
			ai.ManStep = SWord(ai.ManStep) + 1;
			SetManoeuvreTime(300);
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleRegroup
//Author		Craig Beeston
//Date			Tue 20 Jun 2000
//
//Description	Fly towards squadron leader for a bit
//			
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleRegroup()
{
	if(ai.unfriendly)
		SetUnfriendly(NULL);

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			MoveToThrust(100);
			SetManoeuvreTime(3000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			AirStrucPtr lead = FindFormpos0();
			despos = lead->World;
			if(despos.Y < fly.pModel->GroundHeight + FT_500)
				despos.Y = fly.pModel->GroundHeight + FT_500;

			InterceptandRange(&despos);

			AutoCalcPitch();
			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			SimpleMoveToRoll(reqroll);

			if(!TimeLeft())
//DeadCode CSB 25Aug00 				ai.manoeuvre = MANOEUVRE_LOOKROUND;
				if(Range < HALFVISIBLERANGE)
				{
					if(!Art_Int.AttackSpareInLeadersGroup(this))
					{
						ai.manoeuvre = MANOEUVRE_DISENGAGED;
						ai.simpleacm = TRUE;
					}
				}
				else
					ai.ManStep = PHASE0;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleDisengaged
//Author		Craig Beeston
//Date			Fri 25 Aug 2000
//
//Description	
//			
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleDisengaged()
{
	if(ai.unfriendly)
		SetUnfriendly(NULL);

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			MoveToThrust(90);
			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			AirStrucPtr lead = NULL;
			for(AirStrucPtr ld = FindFormpos0(); (ld) && (!lead); ld = ld->fly.nextflight)
				for(AirStrucPtr ac = ld; (ac) && (!lead); ac = ac->Follower())
					if((ac != this) && (ac->World.Y > fly.pModel->GroundHeight + FT_500))
						lead = ac;

//DeadCode CSB 10Nov00 			if(!lead)
//DeadCode CSB 10Nov00 			{
//DeadCode CSB 10Nov00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 10Nov00 				return;
//DeadCode CSB 10Nov00 			}
//DeadCode CSB 10Nov00 
//DeadCode CSB 10Nov00 			AirStrucPtr lead = FindFormpos0();
//DeadCode CSB 10Nov00 			if(!formpos)
//DeadCode CSB 10Nov00 				lead = Art_Int.FindTailie(this);

			if(!lead)
				manoeuvretime = 0;
			else
			{
				InterceptandRange(lead);
				SWord pi = PitchIntercept;
				MODLIMIT(pi, ANGLES_10Deg);
				PitchIntercept = Angles(pi);
				AutoCalcPitch();
				SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
				MODLIMIT(reqroll, ANGLES_60Deg);
				SimpleMoveToRoll(reqroll);
			}
			
			if(!TimeLeft())
			{
				ai.ManStep = PHASE0;
				if(!formpos)
				{
					if(GroupShouldGoHome(0.5))
					{
						if(follower)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_DISENGAGE_DELAY_LP_RPT, this, NULL, Follower()));
						else if(fly.nextflight)
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_DISENGAGE_DELAY_LP_RPT, this, NULL, fly.nextflight));

						SetUnfriendly(NULL);
						fly.leadflight = NULL;
						for(AirStrucPtr ld = this; ld; ld = ld->fly.nextflight)
							for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
							{
								ac->waypoint = ac->waypoint->FindWP(WPNAME_EscDisperse);
								if((ac->movecode != AUTO_COMBAT) || (!ac->ai.unfriendly))
								{
									ac->movecode = AUTO_FOLLOWWP;
									ac->information = IF_OUT_POS;
									ac->manoeuvretime = 0;
									ac->ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
								}
							}
					}
					else
						if(!Art_Int.AttackSpareInLeadersGroup(this))
						{
							if(follower)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_REGROUP, MSG_DISENGAGE_DELAY_LP_RPT, this, NULL, Follower()));
							else if(fly.nextflight)
								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_REGROUP, MSG_DISENGAGE_DELAY_LP_RPT, this, NULL, fly.nextflight));

							for(AirStrucPtr ld = this; ld; ld = ld->fly.nextflight)
								for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
								{
									ac->movecode = AUTO_FOLLOWWP;
									ac->information = IF_OUT_POS;
									ac->manoeuvretime = 0;
								}
						}
				}
				else
					if(!ShouldGoHome())
						if(!Art_Int.AttackSpareInLeadersGroup(this))
							if(FindFormpos0()->movecode == AUTO_FOLLOWWP)
							{
								SetUnfriendly(NULL);
								movecode = AUTO_FOLLOWWP;
								information = IF_OUT_POS;
								manoeuvretime = 0;
								waypoint = FindFormpos0()->waypoint;
							}
			}
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleImGoingHome
//Author		Craig Beeston
//Date			Wed 13 Sep 2000
//
//Description	
//			
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleImGoingHome()
{
	switch(ai.ManStep)
	{
		case 0:
		{
			if(ai.unfriendly)
				SetUnfriendly(NULL);
			SimpleMoveToThrust(100);
			SetManoeuvreTime(3000);
			ai.ManStep = 1;
		}
		case 1:
		{
			InterceptandRange(&ai.homebase->World);
			SLong desalt = FT_5000;
			if((classtype->visible == ME109) || (classtype->visible == ME110))
				desalt = FT_25000;
			if(World.Y > desalt)
				PitchIntercept = ANGLES_315Deg;
			else
			{
				if(vel_ > classtype->bestclimbvel)
					PitchIntercept = ANGLES_30Deg;
				else
					PitchIntercept = ANGLES_0Deg;
			}
			AutoCalcPitch();
	
			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			MODLIMIT(reqroll, ANGLES_45Deg);
			SimpleMoveToRoll(reqroll);
			if(!TimeLeft())
			{
				movecode = AUTO_FOLLOWWP;
				waypoint = waypoint->FindWP(WPNAME_EscDisperse);
				information = IF_OUT_POS;
				manoeuvretime = 0;
			}
			break;
		}
	}
}

		
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleCollisionAvoidance
//Author		Craig Beeston
//Date			Thu 03 Feb 2000
//
//Description	Moves to desired heading and pitch for 1 sec to avoid a collision
//				Then returns to previous unfriendly
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleCollisionAvoidance()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			MoveToThrust(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			PitchIntercept = ai.desiredpitch;
			AutoCalcPitch();
			SWord deltapitch = SWord(PitchIntercept - pitch);
			if(deltapitch < 0) deltapitch *= -1;

			SWord reqroll = FindRequiredRoll(hdg - ai.desiredhdg, CombatReqBankData);
			SWord maxroll = ANGLES_90Deg - 2 * deltapitch;
				MODLIMIT(reqroll, maxroll);
			SimpleMoveToRoll(reqroll);

			if(!TimeLeft())
			{
				if(ShouldGoHome())
					ai.manoeuvre = MANOEUVRE_DISENGAGED;
				else if(ai.firsttactic == TACTIC_DIVEANDZOOM)
					ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
				else if(ai.firsttactic == TACTIC_HEADONATTACK)
					ai.manoeuvre = MANOEUVRE_HEADONATTACK;
				else if(ai.firsttactic == TACTIC_LINEABREAST)
					ai.manoeuvre = MANOEUVRE_LINEABREAST;
				else if(ai.firsttactic == TACTIC_LINEASTERN)
					ai.manoeuvre = MANOEUVRE_LINEASTERN;
				else if(ai.firsttactic == TACTIC_VICATTACK)
					ai.manoeuvre = MANOEUVRE_VICATTACK;
				else
					ai.manoeuvre = MANOEUVRE_SELECT;
			}
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleCollide
//Author		Craig Beeston
//Date			Wed 22 Dec 1999
//
//Description	Crashes into unfriendly and destroys both aircraft
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleCollide()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			MoveToThrust(100);
			ai.ManStep = PHASE1;
		}

		case PHASE1:
		{
			AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
			InterceptandRange(unf);

			if(Range < 1000)
				ai.ManStep = PHASE2;

			FP closerate = FP(unf->World.X - World.X) * FP(vel_x - unf->vel_x)
						 + FP(unf->World.Y - World.Y) * FP(vel_y - unf->vel_y)
						 + FP(unf->World.Z - World.Z) * FP(vel_z - unf->vel_z);
			closerate /= Range;

			despos = unf->World;
			if(closerate > 100000)
			{
				FP dt = Range / closerate;		// 1e-4 cs
				despos.X += unf->vel_x * dt;
				despos.Y += unf->vel_y * dt;
				despos.Z += unf->vel_z * dt;
				InterceptandRange(&despos);
			}
			SimpleMoveToThrust(100);
			AutoCalcPitch();
			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			SimpleMoveToRoll(reqroll);
			break;
		}

		case PHASE2:
		{
			AircraftAnimData* adptr = (AircraftAnimData*)Anim;
			AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
			AircraftAnimData* unfadptr = (AircraftAnimData*)(unf->Anim);
			InterceptandRange(unf);
			FP closerate = FP(unf->World.X - World.X) * FP(vel_x - unf->vel_x)
						 + FP(unf->World.Y - World.Y) * FP(vel_y - unf->vel_y)
						 + FP(unf->World.Z - World.Z) * FP(vel_z - unf->vel_z);
			closerate /= Range;

			if(closerate > 500000)	//Explode both aircraft
			{
				SHAPE.ForceDamage(*this, *unf, &adptr->LEFTWINGIN,  BS_DEAD);
				SHAPE.ForceDamage(*this, *unf, &adptr->RIGHTWINGIN, BS_DEAD);
				SHAPE.ForceDamage(*unf, *this, &unfadptr->LEFTWINGIN,  BS_DEAD);
				SHAPE.ForceDamage(*unf, *this, &unfadptr->RIGHTWINGIN, BS_DEAD);
			}
			else
			{
				SWord dhdg = HdgIntercept - hdg;
				if((dhdg < ANGLES_45Deg) && (-dhdg < ANGLES_45Deg))
				{
					SHAPE.ForceDamage(*this, *unf, &adptr->FRONT,       BS_DEAD);
					SHAPE.ForceDamage(*this, *unf, &adptr->ENGINELEFT,  BS_DEAD);
					SHAPE.ForceDamage(*this, *unf, &adptr->ENGINERIGHT, BS_DEAD);
				}
				else
				{
					if((dhdg > ANGLES_135Deg) || (-dhdg > ANGLES_135Deg))
					{
						SHAPE.ForceDamage(*this, *unf, &adptr->TAIL,     BS_DEAD);
						SHAPE.ForceDamage(*this, *unf, &adptr->FINLEFT,  BS_DEAD);
						SHAPE.ForceDamage(*this, *unf, &adptr->FINRIGHT, BS_DEAD);
					}
					else
					{
						if(dhdg > ANGLES_0Deg)
							SHAPE.ForceDamage(*this, *unf, &adptr->RIGHTWINGIN, BS_DEAD);
						else
							SHAPE.ForceDamage(*this, *unf, &adptr->LEFTWINGIN,  BS_DEAD);
					}
				}

				dhdg = HdgIntercept + ANGLES_180Deg - unf->hdg;
				if((dhdg < ANGLES_45Deg) && (-dhdg < ANGLES_45Deg))
				{
					SHAPE.ForceDamage(*unf, *this, &unfadptr->FRONT,       BS_DEAD);
					SHAPE.ForceDamage(*unf, *this, &unfadptr->ENGINELEFT,  BS_DEAD);
					SHAPE.ForceDamage(*unf, *this, &unfadptr->ENGINERIGHT, BS_DEAD);
				}
				else
				{
					if((dhdg > ANGLES_135Deg) || (-dhdg > ANGLES_135Deg))
					{
						SHAPE.ForceDamage(*unf, *this, &unfadptr->TAIL,     BS_DEAD);
						SHAPE.ForceDamage(*unf, *this, &unfadptr->FINLEFT,  BS_DEAD);
						SHAPE.ForceDamage(*unf, *this, &unfadptr->FINRIGHT, BS_DEAD);
					}
					else
					{
						if(dhdg > ANGLES_0Deg)
							SHAPE.ForceDamage(*unf, *this, &unfadptr->RIGHTWINGIN, BS_DEAD);
						else
							SHAPE.ForceDamage(*unf, *this, &unfadptr->LEFTWINGIN,  BS_DEAD);
					}
				}
			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnToHdgAndPitch
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	move to within 5 deg of desiredpitch and desiredhdg 
//				break or sustained turn depending on circumstances
//				if break then nose down if <corner vel
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ACMAirStruc::SimpleTurnToHdgAndPitch()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime(1500);
			SimpleMoveToThrust(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			AutoCalcPitch();
			SLong reqroll = 5 * SLong(SWord(HdgIntercept - hdg));
			MODLIMIT(reqroll, ANGLES_60Deg);
			SimpleMoveToRoll(reqroll);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
	return(FALSE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LagFight
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleHotSideLagPursuitFight()
{
//1	trgItem is behind target
//	TurningFightSub()
}

//------------------------------------------------------------------------------
Bool	ACMAirStruc::SimpleSandwichManoeuvres()
{
	return(TRUE);
}
//void	AirStruc::SimpleTurningFight()
//{
//}
//void	AirStruc::SimpleTightTurnSubtSub(ANGLES	HdgIntercept)
//{
//}
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SustainedTurn
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleSustainedTurn()
{
//1	GetRequiredRoll(srcItem,trgItem)
//2	pull on elevators so that Drag = Thrust 
//			this is the max sustainable turn, in-plane
//turn to minimise the difference between hdgintercept and hdg, go shortest way
//
//
//	roll = f(morale, flyingskill)
//	drag = f(combatskill)
//
//
//	if (skill high)
//			check lead/lag to avoid turning into target
//
//	turn at best sustained turnrate  (how near = f(skill), maintain altitude if possible
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HighYoYo
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	Ref1.70
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleHighYoYo()
{
//approach from 30-60 AOT, cospeed
//
//roll wings level
//pull up
//when in rear hemisphere (say near 6 o'clock)
//	roll towards target then lead or lag pursuit
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Zoom
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleZoom()
{
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime(1500);
			SimpleMoveToThrust(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			PitchIntercept = ANGLES_45Deg;
			AutoCalcPitch();
			SWord desroll = 0;
			if(ai.unfriendly)
				desroll = SWord(HdgIntercept - hdg);
			MODLIMIT(desroll, ANGLES_45Deg);
			SimpleMoveToRoll(desroll);

			if(		(!TimeLeft())
				||	((ai.unfriendly) && (World.Y > ai.unfriendly->World.Y + FT_1000))
				||	(vel_ < (3 * classtype->minvel) / 2)	)
			{
				if(ShouldGoHome())
				{
					ai.manoeuvre = MANOEUVRE_SELECT;
					ai.firsttactic = TACTIC_NULL;
					return;
				}

				if(ai.firsttactic == TACTIC_LINEABREAST)
 					ai.manoeuvre = MANOEUVRE_LINEABREAST;
 				else if(ai.firsttactic == TACTIC_LINEASTERN)
 					ai.manoeuvre = MANOEUVRE_LINEASTERN;
 				else if(ai.firsttactic == TACTIC_DIVEANDZOOM)
 					ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
				else
					ai.manoeuvre = MANOEUVRE_SELECT;
			}
		}
	}

//DeadCode CSB 7Sep00 //roll wings nearly level
//DeadCode CSB 7Sep00 //pull up then zoom climb for x secs or near stall
//DeadCode CSB 7Sep00 //roll 180 and pull level
//DeadCode CSB 7Sep00 //
//DeadCode CSB 7Sep00 //
//DeadCode CSB 7Sep00 //	ACM.Step = ai.ManStep;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 	switch (ai.ManStep)
//DeadCode CSB 7Sep00 	{
//DeadCode CSB 7Sep00 		case PHASE0:
//DeadCode CSB 7Sep00 		{
//DeadCode CSB 7Sep00 			SetManoeuvreTime (2000);
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			SimpleMoveToThrust (100);			//rdh
//DeadCode CSB 7Sep00 //			ACM.ClimbRate (0);
//DeadCode CSB 7Sep00 //			ACM.KeepWingsLevel ();
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 7Sep00 			break;
//DeadCode CSB 7Sep00 		}
//DeadCode CSB 7Sep00 		case PHASE1:
//DeadCode CSB 7Sep00 		{
//DeadCode CSB 7Sep00 				SimpleMoveToRoll (ANGLES_0Deg);
//DeadCode CSB 7Sep00 				PitchIntercept = ANGLES_40Deg;
//DeadCode CSB 7Sep00 				AutoCalcPitch ();
//DeadCode CSB 7Sep00 			
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			if  (		(!ManoeuvreTimeLeft ())
//DeadCode CSB 7Sep00 					||
//DeadCode CSB 7Sep00 						(vel_ <= CornerSpeed())
//DeadCode CSB 7Sep00 					||
//DeadCode CSB 7Sep00 						((World.Y - ai.unfriendly->World.Y)	>	FT_4000)
//DeadCode CSB 7Sep00 				)
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00 //DEADCODE CB 18/11/99  				if (ai.firsttactic == TACTIC_ROUNDABOUT)
//DeadCode CSB 7Sep00 //DEADCODE CB 18/11/99  					ai.manoeuvre = MANOEUVRE_ROUNDABOUT;
//DeadCode CSB 7Sep00 //DEADCODE CB 18/11/99  				else 
//DeadCode CSB 7Sep00 				if (ai.firsttactic == TACTIC_LINEABREAST)
//DeadCode CSB 7Sep00  					ai.manoeuvre = MANOEUVRE_LINEABREAST;
//DeadCode CSB 7Sep00  				else if (ai.firsttactic == TACTIC_LINEASTERN)
//DeadCode CSB 7Sep00  					ai.manoeuvre = MANOEUVRE_LINEASTERN;
//DeadCode CSB 7Sep00  				else if (ai.firsttactic == TACTIC_DIVEANDZOOM)
//DeadCode CSB 7Sep00  					ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
//DeadCode CSB 7Sep00 				else
//DeadCode CSB 7Sep00 					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			}
//DeadCode CSB 7Sep00 			break;
//DeadCode CSB 7Sep00 		}
//DeadCode CSB 7Sep00 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowYoYo
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Ref1.73	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLowYoYo ( )
{
//used when closure is insufficient
//
//in turning fight, attacker increases horizontal component of turn rate by nose down
//lead target
//level wings and pull up
//
//Note may have to write so that the ac doesn't try to get advantage in one 
//manoeuvre (see btm 1.73)
//
//
//
//Note can also be used when in tailchase to pick up speed to get just inside gun range
//
//
}	 


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptHigh
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleInterceptHigh()
{
	switch(ai.ManStep)
	{
		case 0:
		{
			SimpleMoveToThrust(100);
			SetManoeuvreTime(1500);
			ai.ManStep = 1;
		}
		case 1:
		{
//DeadCode CSB 3Nov00 			despos = ai.unfriendly->World;
//DeadCode CSB 3Nov00 			despos.Y += FT_500;
//DeadCode CSB 3Nov00 			InterceptandRange(&despos);
//DeadCode CSB 3Nov00 			PitchIntercept += PitchIntercept;
			SWord dhdg = HdgIntercept - hdg;
			if(dhdg < 0)	dhdg = -dhdg;
			PitchIntercept += Angles(dhdg / 4);

			AutoCalcPitch();

			FP desroll = FindRequiredRoll (hdg - HdgIntercept, CombatReqBankData);
//DeadCode CSB 3Nov00 			MODLIMIT(desroll, ANGLES_60Deg);
			SimpleMoveToRoll(desroll);

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptLow
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SimpleInterceptLow()
{
	switch(ai.ManStep)
	{
		case 0:
		{
			SimpleMoveToThrust(100);
			SetManoeuvreTime(1500);
			ai.ManStep = 1;
		}
		case 1:
		{
//DeadCode CSB 3Nov00 			despos = ai.unfriendly->World;
//DeadCode CSB 3Nov00 			despos.Y -= FT_500;
//DeadCode CSB 3Nov00 			InterceptandRange(&despos);
//DeadCode CSB 3Nov00 			PitchIntercept += PitchIntercept;
			SWord dhdg = HdgIntercept - hdg;
			if(dhdg < 0)	dhdg = -dhdg;
			PitchIntercept -= Angles(dhdg / 4);

			AutoCalcPitch();

			FP desroll = FindRequiredRoll (hdg - HdgIntercept, CombatReqBankData);
//DeadCode CSB 3Nov00 			MODLIMIT(desroll, ANGLES_60Deg);
			SimpleMoveToRoll(desroll);

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbAtSustainedTurnSpeed
//Author		R. Hyde 
//Date			Fri 20 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleClimbAtSustainedTurnSpeed()
{
//climb but don't go below sustained turn speed
//aim towards unfriendly plus offset = f(desiredrange,desiredhdg)

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		R. Hyde 
//Date			 //RDH 25/05/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleLowAlt()
{
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SimpleMoveToThrust (ThrustfromFF());

			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			FP despitch = FP(CalcBestClimbPitch()) * FP(vel_) / FP(CalcBestClimbSpeed());
			if((ai.unfriendly) && (TargetFacingSubject(ANGLES_45Deg)))
				despitch *= 0.5;
			PitchIntercept = Angles(SWord(despitch));
			AutoCalcPitch();

			FP desroll = FindRequiredRoll (hdg - HdgIntercept, GentleBankData);
			desroll = desroll * (1000.0 - manoeuvretime) / 1000.0;
			SimpleMoveToRoll(desroll);

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}
