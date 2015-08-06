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
//Filename       elmt.cpp
//System         
//Author         Andrew McRae
//Date           Thu 24 Apr 1997
//Description    Aircraft Element Module
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
#include "replay.h"

#define	CylinderCD 0.75
//DEADCODE CSB 28/01/00 #define EasyModel (!Save_Data.flightdifficulty[FD_SPINS])
#define EasyModel 0		// FD_SPINS is now used to run the full flight model or arcade flight model	 //CSB 28/01/00
#define IsPlayer  (Manual_Pilot.ControlledAC2 == ControlledAC)

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Process
//Author		Andrew McRae			Craig Beeston
//Date			Fri 17 Oct 1997			Fri 6 Nov 1998
//
//Description	This calculates the forces and moments acting on the wings of the aircraft
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void MainPlane::Process (AirStrucPtr const ControlledAC)
{
	Bool BUFFET_ON = TRUE;

	FILE* fp;

//DeadCode AMM 4Jul00 	if (_Replay.replayframecount==9 && !ControlledAC->fly.pModel->Controlled)
//DeadCode AMM 4Jul00 	{
//DeadCode AMM 4Jul00 		fp=fopen("plop.txt","at");
//DeadCode AMM 4Jul00 	}

	if(!(pModel->FrameCount & EVERY8cs) || (pModel->FirstCycle) )
	{
		if(pCompCd0Curve != NULL) fCd0Mach = pCompCd0Curve->GetValue (pModel->Inst.I_MachNo);
		if(pCompKCurve != NULL)   fKMach   = pCompKCurve->GetValue (pModel->Inst.I_MachNo);
	
//Buffet Boundaries at aircraft mach number
		FP _buffetM0 = buffetM0;
		FP _buffetM1 = buffetM1;
		if(Save_Data.flightdifficulty[FD_POWERBOOST])
		{
			_buffetM0 *= 1.414213562;	// sqrt(2)
			_buffetM1 *= 1.414213562;
		}

//DeadCode AMM 4Jul00 	if (_Replay.replayframecount==9 && !ControlledAC->fly.pModel->Controlled)
//DeadCode AMM 4Jul00 		fprintf(fp,"fCd0Mach=%f fKMach=%f buffetM0=%f buffetM1=%f\n",
//DeadCode AMM 4Jul00 			fCd0Mach,
//DeadCode AMM 4Jul00 			fKMach,
//DeadCode AMM 4Jul00 			buffetM0,
//DeadCode AMM 4Jul00 			buffetM1);

		BuffetAoaMin = pModel->Inst.I_MachNo / _buffetM0;
		BuffetAoaMin = BuffetAoaMin * BuffetAoaMin * BuffetAoaMin * BuffetAoaMin;	// (M/M0)^4
		BuffetAoaMin = buffetAoa0 * (1 - BuffetAoaMin);	// Cl(Min) = Cl0 * (1-(M/M0)^4)
		if(BuffetAoaMin < 0) BuffetAoaMin = 0;
		
		BuffetAoaMax = pModel->Inst.I_MachNo / _buffetM1;
		BuffetAoaMax = BuffetAoaMax * BuffetAoaMax * BuffetAoaMax * BuffetAoaMax;	// (M/M1)^4
		BuffetAoaMax = buffetAoa1 * (1 - BuffetAoaMax);	// Cl(Max) = Cl1 * (1-(M/M1)^4)
		if(BuffetAoaMax < 0) BuffetAoaMax = 0;

//DeadCode AMM 4Jul00 		if (_Replay.replayframecount==9 && !ControlledAC->fly.pModel->Controlled)
//DeadCode AMM 4Jul00 			fprintf(fp,"I_MachNo=%f\n",
//DeadCode AMM 4Jul00 				pModel->Inst.I_MachNo
//DeadCode AMM 4Jul00 				);

	}

////////////////////////////////////////////////////////////////////////////////////////
	for(SWord wing = 0; wing < 2; wing++)						//[0]Stbd,    [1]Port
		for(SWord section = 0; section < 2; section++)			//[0]Inboard, [1]Outboard
		{
			Bool TIP_STALL = FALSE;
			FCRD Vel;			//Movement of wings due to rotation of Aircraft
			FCRD AirVelAc;		//Local air speed in aircraft coordinates
			FCRD AirVelEl;		//Local air speed in wing element coordinates
			FP	 airspeed;		//Total air speed
			FP	 Aoa;			//Angle of attack
			FP	 Cl, Cd, Cmx, Cmy, Cmz;//Coefficients of Lift, Drag, Pitching moment, Yawing moment, Rolling
			FP	 dAoa, dCl, dCd, dCm;	//Increase in Aoa/coefficients due to control surface deflection
			FP	 DynPressSF;	//Local dynamic pressure times area times maskingfactor
			FP	 fMasking;		//Factor to account for wing masked by fuselage
			FP	 lift, drag, momX, momY, momZ;	
			FCRD Lift, Drag, Mom;

			CPrd(Vel, Pos[wing][section], pModel->RotVel);
			SubVec(AirVelAc, pModel->AirVel, Vel);

//DeadCode AMM 4Jul00 			if (_Replay.replayframecount==9 && !ControlledAC->fly.pModel->Controlled)
//DeadCode AMM 4Jul00 				fprintf(fp,"Pos[%d][%d]=%f RotVelX=%f RotVelY=%f RotVelZ=%f\nAirVelX%f AirVelY=%f AirVelZ=%f\n",
//DeadCode AMM 4Jul00 					wing,
//DeadCode AMM 4Jul00 					section,
//DeadCode AMM 4Jul00 					Pos[wing][section],
//DeadCode AMM 4Jul00 					pModel->RotVel.x,
//DeadCode AMM 4Jul00 					pModel->RotVel.y,
//DeadCode AMM 4Jul00 					pModel->RotVel.z,
//DeadCode AMM 4Jul00 					pModel->AirVel.x,
//DeadCode AMM 4Jul00 					pModel->AirVel.y,
//DeadCode AMM 4Jul00 					pModel->AirVel.z
//DeadCode AMM 4Jul00 					);
			FP MomentSlipstream = 0;

			if((IsPlayer) && (Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS]) && (pSlipThrustPoint[wing] != NULL) && (section == 0) )
				if(pSlipThrustPoint[wing]->pEngine->Type == ET_PISTON)
				{
					MomentSlipstream  = 223.4 * 0.5 * pModel->AmbDensity * pSlipThrustPoint[wing]->pEngine->SlipVel * wArea[section];
					MomentSlipstream *= wSpan[section] * pSlipThrustPoint[wing]->pEngine->SlipRot;
					MomentSlipstream *= pSlipThrustPoint[wing]->pEngine->RotateDirection;

					FP slip_fact = pSlipThrustPoint[wing]->pEngine->PropVel / pSlipThrustPoint[wing]->pEngine->SlipVel;
					if(slip_fact < 0)	slip_fact = 1;
					FP slip_area = 0.01 * FP(AmountInSlipstream) * FSqrt(slip_fact);
					if(slip_area > 1)	slip_area = 1;

					MomentSlipstream *= slip_area * slip_area;

					AirVelAc.z = slip_area * -pSlipThrustPoint[wing]->pEngine->SlipVel + (1 - slip_area) * AirVelAc.z;
				}

			TnsAxs(AirVelAc, AirVelEl, Ori[wing][section]);

			airspeed = VecLen  (AirVelEl);
			FP AirVelHori = VecLen2D(AirVelEl.x, AirVelEl.z);
			if(AirVelEl.z > 0) AirVelHori *= -1;
			Aoa		 = AngleSign( CalcAngle(AirVelHori, AirVelEl.y) );	

//DEADCODE CB 01/11/99 			if((IsPlayer) && (!EasyModel))
//DEADCODE CB 01/11/99 				if((section == 1) && ((pModel->Type == AT_MIG15) || (pModel->Type == AT_MIG15BIS)) )
//DEADCODE CB 01/11/99 					if((pModel->Pos.y < 300000) && (pModel->Speed > 285))
//DEADCODE CB 01/11/99 						if(Aoa > aoa[1-wing][1])		//This wing at higher aoa than other wing
//DEADCODE CB 01/11/99 							TIP_STALL = TRUE;

					
			Cl = Cd = Cmx = Cmy = Cmz = 0.0;
			dAoa = dCl = dCd = dCm    = 0.0;

//Flaps etc.
			if(section == 0)
			{
				dAoa = pModel->DeltaAlpha;
				dCl  = pModel->DeltaCl;
				dCd  = pModel->DeltaCd;
				dCm  = pModel->DeltaCm;
			}

//Ailerons
			else if ((pNewCtrls != NULL) && (!TIP_STALL))
				{
					if (wing == 0) pNewCtrls->Process(dAoa, dCl, TRUE);
					if (wing == 1) pNewCtrls->Process(dAoa, dCl, FALSE);
					
					if(Aoa * dAoa < 0)
					{
						FP factor = Aoa;
						if(factor < 0) factor *= -1;

						for(;;)
						{
							if(factor < Degs2Rads(15) )
							{
								factor = 1;
								break;
							}
							if(factor > Degs2Rads(22.5) )
							{
								factor = 0;
								break;
							}
							factor = (factor - Degs2Rads(15) ) / Degs2Rads(22.5 - 15);
							factor = 1 - factor * factor;
							break;
						}
						dAoa *= factor;
						dCl  *= factor;
					}
				}

			if(TIP_STALL)
			{
				dAoa = 0;
				dCl  = 0;
				dCm  = 0;
			}


			if(AirVelEl.z > 0) 
			{
				dAoa *= -1;
				dCl	  =  0;
				dCm	  =  0;
			}
			Aoa += dAoa;

			if(pClCurve != NULL)	Cl = pClCurve->GetValue(Aoa);
			Cl += dCl;

			if((Aoa > AoaMin) && (Aoa < AoaMax))
				Cd = Cdo * fCd0Mach + (k * Cl * Cl) * fKMach;
			else
			{
				if(pCdCurve != NULL)
				{
					Cd = pCdCurve->GetValue(Aoa);
					FP KCl2 = Cd - Cdo;
					Cd = Cdo * fCd0Mach + KCl2 * fKMach;
				}
			}
			Cd += dCd;

			if(pCmCurve != NULL)	Cmx = pCmCurve->GetValue(Aoa);
			Cmx += dCm;
			
			if(TIP_STALL)
			{
				Cl *= 0.8;
				Cd *= 1.1;
			}

			FP AbsAoa = Aoa;
			if(AbsAoa < 0) AbsAoa *= -1;


//Buffet
			FP BuffetIntensity = 0.0;	
		
			if ( (!pModel->bACM) && (BUFFET_ON) )
				if(AbsAoa < BuffetAoaMin)		BuffetIntensity = 0.0;
				else if(AbsAoa > BuffetAoaMax) 	BuffetIntensity = 1.0;
				else 
					BuffetIntensity = (AbsAoa - BuffetAoaMin) / (BuffetAoaMax - BuffetAoaMin);
//DeadCode CSB 26/02/99						PrintVar (12 - (1-2*wing)*(1+section)*5, 24, "%.2f", BuffetIntensity);

			pModel->TotalBuffet += BuffetIntensity;// * BuffetIntensity;




			FCRD ExtraDamping;
			NullVec(ExtraDamping);

			if(IsPlayer)
			{
				if((EasyModel) || (Key_Tests.KeyHeld3d (SPINRECOVERY)))
				{
					ExtraDamping.x += -5.0;
					ExtraDamping.y += -0.5;
					ExtraDamping.z += -0.5;
				}
			}
//DEADCODE CB 01/11/99 			else
//DEADCODE CB 01/11/99 				if((pModel->Type == AT_F51D) || (pModel->Type == AT_YAK9))
//DEADCODE CB 01/11/99 				{
//DEADCODE CB 01/11/99 //DeadCode CSB 29/06/99						ExtraDamping.x += -5.0;
//DEADCODE CB 01/11/99 					ExtraDamping.y += -1;
//DEADCODE CB 01/11/99 //DeadCode CSB 29/06/99						ExtraDamping.z += -0.5;
//DEADCODE CB 01/11/99 				}

			if(airspeed > 0)
			{
				FP One_Over_2v = 1 / (2 * airspeed);
				Cmx += (dCMdq + ExtraDamping.x) * pModel->RotVel.x * Chord * One_Over_2v;	//CSB 09/12/98	Pitch Rate
				Cmy  = (dCMdr + ExtraDamping.y) * pModel->RotVel.y * Span  * One_Over_2v;	//CSB 10/12/98	Roll Rate
				Cmz  = (dCMdp + ExtraDamping.z) * pModel->RotVel.z * Span  * One_Over_2v;	//CSB 10/12/98	Yaw Rate
			}

//Ground Effect		//CSB	//20/8/98
			if(pModel->Pos.y - pModel->GroundHeight < 2000)
			{
				FP HeightAboveGround  =  pModel->Pos.y - pModel->GroundHeight;
				HeightAboveGround *= 0.01;	//metres
				FP GroundEffectFactor =  0.56142 - 0.056142 * HeightAboveGround 
										 + 0.00140355 * HeightAboveGround * HeightAboveGround;
				GroundEffectFactor    /= 2.5 + HeightAboveGround;
				Cl *= 1 + GroundEffectFactor;
			}


			if(section == 0)
				DownWashAng[wing] = 2 * Cl / (FPIE * (FP)Span / (FP)Chord);

//Calculate Forces and Moments

			DynPressSF = 0.5 * pModel->AmbDensity * airspeed * airspeed * wArea[section];// * fMasking;
			lift = Cl * DynPressSF;
			drag = Cd * DynPressSF;
			momX = Cmx * DynPressSF * wChord[section];
			momY = Cmy * DynPressSF * wSpan[section];
			momZ = Cmz * DynPressSF * wSpan[section];
			momZ += MomentSlipstream;


//DEADCODE CB 12/11/99 if((wing == 1) && (section == 1))	PrintVar(60, 10, "CL %.3f ", FP(Cl));
//DEADCODE CB 12/11/99 if((wing == 1) && (section == 0))	PrintVar(60, 11, "CL %.3f ", FP(Cl));
//DEADCODE CB 12/11/99 if((wing == 0) && (section == 0))	PrintVar(60, 12, "CL %.3f ", FP(Cl));
//DEADCODE CB 12/11/99 if((wing == 0) && (section == 1))	PrintVar(60, 13, "CL %.3f ", FP(Cl));

//Implement the effects of damage
			AircraftAnimData*	adptr;
			adptr = (AircraftAnimData *)ControlledAC->Anim;

			FP fDamage;
			if( (wing == 0) && (section == 0) )	fDamage = adptr->RIGHTWINGIN;	//Stbd Inn
			if( (wing == 0) && (section == 1) )	fDamage = adptr->RIGHTWINGOUT;	//Stbd Out
			if( (wing == 1) && (section == 0) )	fDamage = adptr->LEFTWINGIN;	//Port Inn
			if( (wing == 1) && (section == 1) )	fDamage = adptr->LEFTWINGOUT;	//Port Out
	
			if(fDamage == BS_DEAD) 
			{
				lift = 0;
				drag = 0;
				momX = 0;
				momY = 0;
				momZ = 0;
			} 
			else if(fDamage)
			{
				fDamage =  fDamage / 256;
				lift    *= 1 - fDamage;
				drag    *= 1 + fDamage;
				momX    *= 1 - fDamage;
				momY    *= 1 - fDamage;
				momZ    *= 1 - fDamage;
			}

// calc direction of Force & moment

			CPrd(Lift, AirVelAc, Ori[wing][section].y);	//Lift = Line within XZ plane of wing, perpendicular to flow
			CPrd(Lift, Lift, AirVelAc);					//Lift = Perpendicular to flow with components in x and z
			NrmVec(Lift, Lift);

			Lift.x *= lift;
			Lift.y *= lift;
			Lift.z *= lift;
			NrmVec(AirVelAc, Drag);

			Drag.x *= drag;
			Drag.y *= drag;
			Drag.z *= drag;

			AddVec(eForce[wing][section], Lift, Drag);

			Mom.x = momX;
			Mom.y = momY;
			Mom.z = momZ;

			TnsPnt(Mom, eMoment[wing][section], Ori[wing][section]);

			aoa[wing][section] = Aoa;
		}	//Next Section
			//Next Wing

	pModel->Spinning = FALSE;

	if(!EasyModel)
		if(		((aoa[0][0] > 0.3054) && (aoa[1][0] < 0.3054) && (pModel->RotVel.y > 0.0025))
			||	((aoa[0][0] < 0.3054) && (aoa[1][0] > 0.3054) && (pModel->RotVel.y < -0.0025))	)
			pModel->Spinning = TRUE;


//DeadCode CSB 5Sep00 		if(		((aoa[1][1] > 0.3054) || (aoa[0][1] > 0.3054))		//17.5 deg
//DeadCode CSB 5Sep00 			&&	((pModel->RotVel.y > 0.0025) || (pModel->RotVel.y < -0.0025))	)																
//DeadCode CSB 5Sep00 			{																
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 				if((Manual_Pilot.ControlledAC2 == ControlledAC) && (pModel->Spinning == FALSE))			  //RDH 01/03/99
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 				{
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 					_Miles.SequenceAudible(FIL_MUSIC_SPIRALLING);	  //RDH 01/03/99
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 PrintString(0, 24, "@@ SPINNING @@");
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 				}
//DeadCode CSB 5Sep00 				pModel->Spinning = TRUE;							  //RDH 01/03/99
//DeadCode CSB 5Sep00 			}
//DeadCode CSB 5Sep00 			else													  //RDH 01/03/99
//DeadCode CSB 5Sep00 			{
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 				if((Manual_Pilot.ControlledAC2 == ControlledAC) && (pModel->Spinning == TRUE))												  //RDH 01/03/99
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 				{
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 					_Miles.SequenceMute(500);						  //RJS 18/06/99
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 PrintString(0, 24, "              ");
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 				}
//DeadCode CSB 5Sep00 //DeadCode CSB 15Aug00 
//DeadCode CSB 5Sep00 				pModel->Spinning = FALSE;							  //RDH 01/03/99
//DeadCode CSB 5Sep00 			}
//DeadCode CSB 5Sep00 
//DeadCode AMM 4Jul00 	if (_Replay.replayframecount==9 && !ControlledAC->fly.pModel->Controlled)
//DeadCode AMM 4Jul00 		fclose(fp);

}


 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSurface
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calculates Force and moment produced by this surface.
//				Force & moment are in aircraft coords
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Surface::Process (AirStrucPtr const ControlledAC)
{
	FCRD Vel;
	FCRD AirVel;
	FCRD AcAirVel;

	FP Cl,Cd;//,Cm;
	FP aoa;

	FCRD Lift;
	FCRD Drag;
 
	// calc element vel relative to aircraft cg
	CPrd (Vel, Pos, pModel->RotVel);

	FCRD localairvec;

	localairvec.x = pModel->AirVel.x;
	localairvec.y = pModel->AirVel.y;
	localairvec.z = pModel->AirVel.z;

//Effect of Downwash on TailPlane
	if(pModel->MainPlaneList != NULL)	//fix this !!!!
	{
		if(Pos.x > 0) localairvec.y += localairvec.z * pModel->MainPlaneList->DownWashAng[0];
		if(Pos.x < 0) localairvec.y += localairvec.z * pModel->MainPlaneList->DownWashAng[1];
	}

	// calc air speed of surface (ac coords)
	SubVec (AcAirVel, localairvec, Vel);

	FP MomentSlipstream = 0;
//Propellor SlipStream
	if( (Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS]) && (pSlipThrustPoint != NULL) )
		for(;;)
		{
			if(pSlipThrustPoint->pEngine->Type != ET_PISTON) break;
			
			FCRD dist;
			FCRD SlipstreamVel;
			FCRD SlipstreamRot;	
	
			SubVec(dist, Pos, pSlipThrustPoint->Pos);	

			SlipstreamRot.x = 0;
			SlipstreamRot.y = 0;
			SlipstreamRot.z = pSlipThrustPoint->pEngine->SlipRot;	
			SlipstreamRot.z *= pSlipThrustPoint->pEngine->RotateDirection;	

			CPrd (SlipstreamVel, dist, SlipstreamRot);
			SlipstreamVel.z = -pSlipThrustPoint->pEngine->SlipVel;

			FP slip_fact = 0;
			if(pSlipThrustPoint->pEngine->SlipVel > 0)
				slip_fact = pSlipThrustPoint->pEngine->PropVel / pSlipThrustPoint->pEngine->SlipVel;
			
			FP slip_area = 0;
			if(slip_fact > 0)
				slip_area = 0.01 * AmountInSlipstream * FSqrt(slip_fact);
			if(slip_area > 1) slip_area = 1;
			
			SlipstreamVel.x *= 1;
			SlipstreamVel.y *= 1;
			AcAirVel.x += slip_area * SlipstreamVel.x;
			AcAirVel.y += slip_area * SlipstreamVel.y;
			AcAirVel.z =  slip_area * SlipstreamVel.z + (1 - slip_area) * AcAirVel.z;

///////////////////////////////////////////////////////////////////////////////////////////////////
			MomentSlipstream  = 149.0 * 0.5 * pModel->AmbDensity * pSlipThrustPoint->pEngine->SlipVel * Area;
			MomentSlipstream *= Span * pSlipThrustPoint->pEngine->SlipRot;
			MomentSlipstream *= pSlipThrustPoint->pEngine->RotateDirection;

			MomentSlipstream *= slip_area * slip_area;

			break;
		}

	// rotate into element coords
	TnsAxs (AcAirVel, AirVel, Ori);

	FCRD LocalRotVel;
	TnsAxs(pModel->RotVel, LocalRotVel, Ori);

	
	// calc airvel & aoa
	FP airspeed; // wrt element shape


	airspeed = VecLen(AirVel);
	FP AirVelHori = VecLen2D(AirVel.z, AirVel.x);
	if(AirVel.z > 0) AirVelHori *= -1;
	aoa = AngleSign( CalcAngle( AirVelHori, AirVel.y) );

	Cl = Cd = 0.0;// Cm = 0.0;

	FP dCl  = 0.0;
	FP dAoa = 0.0;

	if(pNewCtrls != NULL)
		pNewCtrls->Process (dAoa, dCl, FALSE);

//DEADCODE CSB 18/01/00 	if(aoa * dAoa < 0)
//DEADCODE CSB 18/01/00 	{
//DEADCODE CSB 18/01/00 		FP factor = aoa;
//DEADCODE CSB 18/01/00 		if(factor < 0) factor *= -1;
//DEADCODE CSB 18/01/00 
//DEADCODE CSB 18/01/00 		for(;;)
//DEADCODE CSB 18/01/00 		{
//DEADCODE CSB 18/01/00 			if(factor < Degs2Rads(15) )
//DEADCODE CSB 18/01/00 			{
//DEADCODE CSB 18/01/00 				factor = 1;
//DEADCODE CSB 18/01/00 				break;
//DEADCODE CSB 18/01/00 			}
//DEADCODE CSB 18/01/00 			if(factor > Degs2Rads(22.5) )
//DEADCODE CSB 18/01/00 			{
//DEADCODE CSB 18/01/00 				factor = 0;
//DEADCODE CSB 18/01/00 				break;
//DEADCODE CSB 18/01/00 			}
//DEADCODE CSB 18/01/00 			factor = (factor - Degs2Rads(15) ) / Degs2Rads(22.5 - 15);
//DEADCODE CSB 18/01/00 			factor = 1 - factor * factor;
//DEADCODE CSB 18/01/00 			break;
//DEADCODE CSB 18/01/00 		}
//DEADCODE CSB 18/01/00 		dAoa *= factor;
//DEADCODE CSB 18/01/00 		dCl  *= factor;
//DEADCODE CSB 18/01/00 	}
					

	if(AirVel.z > 0) 
	{
		dAoa *= -1;
		dCl   =  0;
	}

	aoa += dAoa;

// calc Cl, Cd & Cm
	if (pClCurve != NULL)  Cl = pClCurve->GetValue (aoa);

	Cl += dCl;

	if (pCdCurve != NULL)  Cd = pCdCurve->GetValue (aoa);

	FP fMasking = 1.0;
	if(MaskAngle != 0.0)
	{
		FP sideslip = CalcAngle(-AirVel.z, -AirVel.x);
		sideslip = AngleSign(sideslip);
		fMasking = sideslip / MaskAngle;
		MODMAXMIN(fMasking, 0, 1);
		if(fMasking > 0)
			fMasking = 1 - MaskArea * 0.01 * fMasking;
		else fMasking = 1.0;
	}


	// calc lift, drag & moment
	FP dynpres = 0.5 * pModel->AmbDensity * airspeed * airspeed;// * fMasking;

	FP lift   = Cl * dynpres * Area;// * fTurbulence;
	FP drag   = Cd * dynpres * Area;// * fTurbulence;

// calc direction of Force & moment

	//implement damage 
	AircraftAnimData*	adptr;
	adptr = (AircraftAnimData *)ControlledAC->Anim;

	FP fDamage;
	if((Desc == SD_FIN)	&& (Pos.x > 0))	fDamage = adptr->FINRIGHT;
	else if (Desc == SD_FIN)				fDamage = adptr->FINLEFT;
	if(Desc == SD_TAILPLANE)			fDamage = adptr->TAIL;

	if(fDamage == BS_DEAD) 
	{
		lift = 0;
		drag = 0;
	} 
	else if(fDamage)
	{
		fDamage =  fDamage / 512;
		lift    *= 1 - fDamage;
		drag    *= 1 + fDamage;
	}

	CPrd(Lift, AcAirVel, Ori.y);	//Lift = Line within XZ plane of wing, perpendicular to flow
	CPrd(Lift, Lift, AcAirVel);		//Lift = Perpendicular to flow with components in x and z
	NrmVec(Lift, Lift);

	Lift.x *= lift;
	Lift.y *= lift;
	Lift.z *= lift;

	NrmVec (AcAirVel, Drag);	//CSB 10/12/98
	Drag.x *= drag;
	Drag.y *= drag;
	Drag.z *= drag;
	

	Force.x = Lift.x + Drag.x;
	Force.y = Lift.y + Drag.y;
	Force.z = Lift.z + Drag.z;

	Moment.x = 0;
	Moment.y = 0;
	Moment.z = MomentSlipstream;

	TnsPnt(Moment, Moment, Ori);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessCylinder
//Author		Craig Beeston
//Date			Thu 05 Nov 1998
//
//Description	Calculates Force produced by this cylinder.
//				Force & moment are in aircraft coords
//				//Note - Cylinders are always along the z-axis of the aircraft. (Fuselages)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Cylinder::Process (AirStrucPtr const ControlledAC)
{
	FCRD Vel;
	CPrd(Vel, Pos, pModel->RotVel);
	FCRD AirVelAC, AirVelEl;
	SubVec (AirVelAC, pModel->AirVel, Vel);

	TnsAxs(AirVelAC, AirVelEl, Ori);

	FP airspeed = VecLen (AirVelEl);
	
	FP HalfRhoLCd = 0.5 * pModel->AmbDensity * Length * CylinderCD * airspeed; 

	Force.x = HalfRhoLCd * DiameterY * AirVelEl.x;

	Force.y = HalfRhoLCd * DiameterX * AirVelEl.y;
	
	Force.z = 0;

	TnsPnt(Force, Force, Ori);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessThrust
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Actions a thrust force into the model
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThrustPoint::Process ()
{
	switch (Type)
	{
		case TT_JET:
			Force.x = Vec.x * pEngine->Thrust;
			Force.y = Vec.y * pEngine->Thrust;
			Force.z = Vec.z * pEngine->Thrust;
			NullVec (Moment);
			break;

		case TT_PROP:
			Force.x = Vec.x * pEngine->Thrust;
			Force.y = Vec.y * pEngine->Thrust;
			Force.z = Vec.z * pEngine->Thrust;
			if( (Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS]) && (pEngine->Type == ET_PISTON) )
			{
				Moment.x = Vec.x * pEngine->Torque;
				Moment.y = Vec.y * pEngine->Torque;
				Moment.z = Vec.z * pEngine->Torque;

				AddVec(Moment, Moment, pEngine->moment);
			}
 			else
				NullVec (Moment);
			break;
	}
}


