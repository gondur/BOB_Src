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
//Filename       aerodev.cpp
//System         
//Author         Andrew McRae
//Date           Wed 13 Aug 1997
//Description    
//------------------------------------------------------------------------------

#ifndef	NDEBUG
#define	_HARDGEAR_
#endif

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "ranges.h"
#include "myangles.h"
#include "monotxt.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AeroDevice
//Author		Andrew McRae
//Date			Wed 17 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AeroDevice::AeroDevice (
				AirStrucPtr const controlledAC,
				PMODEL pmodel,		// parent flight model class
				DT_TYPE type,		// DT_xxxxx
				CONTROL_TYPE controltype,
				POWER_TYPE powertype,
				FP dcl,	  			// delta CL
				FP dcd,				// delta CD
				FP dcm,				// delta CM
				FP dalpha,			// delta Alpha
				SWord stages,
				SWord rate,			// movement rate
				KeyVal3D upkey,		// control key (0 if none)
				KeyVal3D downkey,
				SWord buffetvel,
				UByte* pAnimByte,	// anim byte address
				SLong	minval,
				SLong	maxval,
				SLong	Scale)		// anim scale

{
	ControlledAC = controlledAC;
	pModel = pmodel;
	Type = type;
	ControlType = controltype;
	PowerType = powertype;

	dCl = dcl;
	dCd = dcd;
	dCm = dcm;
	dAlpha = dalpha;

	Stages = stages;
	Rate = rate;
	UpKey = upkey;
	DownKey = downkey;
	BuffetVel = buffetvel;
	Broken = FALSE;

	Val = 0x0000;
 	Attractor = 0x0000;
	OldAttractor=0x0000;
	ReqVal = 0x0000;

//	Dir = STATIONARY;

	List.Attach (&pModel->DeviceList, this);

	if (pAnimByte != NULL)
	{
		// Attach an MA_SURFACE
		//this is for an animation
		if(type == DT_GEAR)
			new MODELANIM (ControlledAC, MA_GENERICFP, pModel, &Val, pAnimByte, minval, maxval, Scale, FALSE);//RJS 20Jul98	//CSB 29/02/00
		else
			new MODELANIM (ControlledAC, MA_AEROSURFACE, pModel, &Val, pAnimByte, minval, maxval, Scale, FALSE);//RJS 20Jul98	//CSB 29/02/00
	}

//DEADCODE CSB 21/02/00 	if (Type == DT_GEAR)
//DEADCODE CSB 21/02/00 	{
//DEADCODE CSB 21/02/00 // 		Val = 0;
//DEADCODE CSB 21/02/00 //		OldAttractor = Attractor = 0;
//DEADCODE CSB 21/02/00 
//DEADCODE CSB 21/02/00  		Val = 0x4000;
//DEADCODE CSB 21/02/00 		OldAttractor = Attractor = 0x4000;
//DEADCODE CSB 21/02/00 		ReqVal = Stages - 1;
//DEADCODE CSB 21/02/00 
//DEADCODE CSB 21/02/00 
//DEADCODE CSB 21/02/00 		AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
//DEADCODE CSB 21/02/00  		if (adptr)							//rdh
//DEADCODE CSB 21/02/00  			adptr->animtoggle = 255;
//DEADCODE CSB 21/02/00 
//DEADCODE CSB 21/02/00 	}

	// Aero dev should have unique count for comms
	DeviceID = ControlledAC->fly.AeroDeviceCnt++;				//RJS 18Sep98
//DeadCode AMM 29Jun99 	pModel->UniqueID = ControlledAC->uniqueID.count;			//RJS 18Sep98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AeroDevice
//Author		Andrew McRae
//Date			Wed 17 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AeroDevice::~AeroDevice ()
{
	List.Detach (this);
}

void AeroDevice::GearUp ()
{
	if (Type == DT_GEAR)
	{
 		Val = 0;
		OldAttractor = Attractor = 0;
		ReqVal = 0;
	}

}

void AeroDevice::GearDown ()
{
	if (Type == DT_GEAR)
	{
 		Val = 16384;
		OldAttractor = Attractor = 16384;
		ReqVal = Stages - 1;

	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Process
//Author		Andrew McRae
//Date			Tue 12 Aug 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AeroDevice::Process ()
{
	FP frac;

	if (Val)
	{
		frac = (FP)Val * 0.000061035;

		pModel->DeltaCl += (frac * dCl);
		pModel->DeltaCd += (frac * dCd);
		pModel->DeltaCm += (frac * dCm);
		pModel->DeltaAlpha += (frac * dAlpha);

		FP ias2 = pModel->AirVel.z * pModel->AirVel.z * pModel->AmbDensity;
		FP maxvel2 = BuffetVel * BuffetVel * 0.0001225;

		if((Val > 4096) && (ias2 > maxvel2))
		{
			pModel->TotalBuffet = 2;
			FP f = 10 * (ias2 / maxvel2 - 1);
			if(f < 1)
				pModel->TotalBuffet *= 1;
		}
#ifndef	_HARDGEAR_
		if((!Broken) && (Val > 0x1000) && (ControlType == CT_KEYS) && (ias2 > 2 * maxvel2))
		{
			Attractor = Val;
			OldAttractor = Attractor;
			Broken = TRUE;
 			if(pModel->Controlled)							
				_Miles.PlayOnce(FIL_SFX_METAL_SNAP);		
		}
#endif
	}

	if((Type == DT_CANOPY) && (DownKey != NULLKEY) && (Save_Data.gamedifficulty[GD_AUTOCANOPY]))
		if((!Key_Tests.KeyHeld3d(HEADOUTVIEWL)) && (!Key_Tests.KeyHeld3d(HEADOUTVIEWR)))
			if((pModel->Speed < 65.0) && (Attractor == 0))
				Key_Tests.KeyFake3d(UpKey, FALSE, TRUE);
			else if((pModel->Speed > 70.0) && (Attractor != 0))
				Key_Tests.KeyFake3d(DownKey, FALSE, TRUE);
}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Action
//Author		Andrew McRae
//Date			Wed 13 Aug 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AeroDevice::Action (AirStrucPtr const ControlledAC, CONTROL_TYPE ctrl_type, Bool sendpacket)
{
	AircraftAnimData *adptr = (AircraftAnimData*)(ControlledAC->Anim);
	if(ControlType == CT_AUTO)
	{
		if(!ControlledAC->fly.pModel->FirstCycle)
		{
//DeadCode CSB 22Sep00 			FP ias2 = pModel->AirVel.z * pModel->AirVel.z * pModel->AmbDensity;
//DeadCode CSB 22Sep00 
//DeadCode CSB 22Sep00 			FP maxvel2 = BuffetVel * BuffetVel * 0.0001225;
//DeadCode CSB 22Sep00 			
//DeadCode CSB 22Sep00 			if(ias2 < maxvel2)

			//Slats get opened when Angle of Attack exceeds 12 Deg
			if((pModel->MainPlaneList->aoa[0][0] + pModel->MainPlaneList->aoa[1][0]) / 2 > Rowan2Rads(BuffetVel))
				ReqVal = 1;
			else
				ReqVal = 0;

			Attractor = ReqVal * 0x4000;
		}
	}
	else if (ctrl_type == CT_KEYS)
	{
		if(!((Type == DT_GEAR) && (pModel->GearTouched)))	//Can't toggle gear on the ground
		{
			if((ReqVal < (Stages - 1)) && (Key_Tests.KeyPress3d(UpKey)))
				ReqVal++;
			else if((ReqVal > 0) && (Key_Tests.KeyPress3d(DownKey)))
				ReqVal--;
		}
		Key_Tests.KeyPress3d(UpKey);	//Clear Keyboard inputs
		Key_Tests.KeyPress3d(DownKey);
			
		if(!Broken)
		{
			SLong TempVal = (ReqVal * 0x4000) / (Stages - 1);
			Attractor = TempVal;
			if((Type == DT_GEAR) && (List.NextItem()) && (List.NextItem()->Type == DT_GEAR))
				List.NextItem()->ReqVal = ReqVal;
			
			if((Type == DT_DIVEBRAKES) && (Attractor != OldAttractor))
			{
				if(ReqVal == 1)
					pModel->BombingPhase = 1;
				else
					pModel->BombingPhase = 0;
			}
		}
	}

	{
		if (OldAttractor != Attractor)
		{
			//Hydraulic sound effect...
 			if(pModel->Controlled)								//AMM 26Apr99
			{
				switch(PowerType)
				{
					case PT_VOID:
						break;
					case PT_MANUAL:
					{	
						_Miles.PlayOnce(FIL_SFX_CPT_CANOPY_SLIDE);
						break;
					}
					case PT_ELECTRIC:
					{	
						_Miles.PlayOnce(FIL_SFX_CANOPY_OPEN);
						break;
					}
					case PT_HYDRAULIC:
					{	
						_Miles.PlayOnce(FIL_SFX_FLAPS);
						break;
					}
					case PT_PNEUMATIC:
					{	
						_Miles.PlayOnce(FIL_SFX_CANOPY_BLOW);
						if(Type == DT_CANOPY)
						{

						}
						break;
					}
				}
			}

			OldAttractor = Attractor;

			// Can we send, and is it the piloted AC?
			if (sendpacket && (pModel->Controlled == TRUE))
//DEADCODE CB 29/10/99 				_DPlay.NewAeroDevAction(DeviceID,Attractor);
				_DPlay.NewAeroDevAction(DeviceID,Attractor);
			// Log UniqueID (14 bits), DeviceID (8 bits)
		}

		FP damage = 0;

		switch(Type)
		{
			case DT_GEAR:
			{
				if(Save_Data.flightdifficulty[FD_SPINS])
				{
					if(UpKey == NULLKEY)
						damage = adptr->RIGHTWHEEL;
					else
						damage = adptr->LEFTWHEEL;
				}
				else
					damage = adptr->RIGHTWHEEL / 2 + adptr->LEFTWHEEL / 2;
				break;
			}
			case DT_FLAPS:
			case DT_DIVEBRAKES:
			{
				damage = adptr->LEFTWINGIN / 2 + adptr->RIGHTWINGIN / 2;
				break;
			}
			case DT_SLATS:
			{
				damage = adptr->LEFTWINGOUT / 2 + adptr->RIGHTWINGOUT / 2;
				break;
			}
			case DT_SPEEDBRAKES:
			{
				damage = adptr->OTHER;
				break;
			}
			case DT_CANOPY:
			{
				damage = adptr->CANOPY;
				break;
			}
		}

		if((Type != DT_GEAR) || (!pModel->EmergencyGearUsed))
			if((PowerType == PT_HYDRAULIC) || (PowerType == PT_PNEUMATIC))
			{
				FP engine = adptr->ENGINELEFT;
				if(pModel->EngineList->List.NextItem())
					if(adptr->ENGINERIGHT < engine)
						engine = adptr->ENGINERIGHT;
				damage += engine;
			}
		if(damage > 255) damage = 255;
		if(damage > BS_DAMLV2)
			Broken = TRUE;

		FP delta = Rate * MODEL_DT * (255.0 - damage) / 255.0;
		if (Val < Attractor)
		{
//DeadCode AMM 24Nov99 			Val += Rate * pModel->MODEL_DT;
			Val += delta;
			if (Val > Attractor) Val = Attractor;
		}

		if (Val > Attractor)
		{
//DeadCode AMM 24Nov99 			Val -= Rate * pModel->MODEL_DT;
			Val -= delta;
			if (Val < Attractor) Val = Attractor;
		}
	}

	if((Type == DT_CANOPY) && (DownKey == NULLKEY) && (Attractor > 0))
		Trans_Obj.LaunchBlowCanopy(*ControlledAC, *(ControlledAC->currworld));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowerFlaps
//Author		Craig Beeston
//Date			Wed 21 Apr 1999
//
//Description	Lower the flaps
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::FlapsDown(AirStrucPtr const ControlledAC)
{
	PAERODEVICE pDevice = DeviceList;
	while (pDevice != NULL)
	{
		if( (pDevice->Type == AeroDevice::DT_FLAPS) && (pDevice->Val < 16384) )
		{
			pDevice->Val += pDevice->Rate;
			if(pDevice->Val > 16384) pDevice->Val = 16384;
		
			PMODELANIM pModelAnim = AnimList;

 			if (ControlledAC)														//RJS 27May98
			{
 				while (pModelAnim != NULL)
 				{
//DEADCODE DAW 26/04/99 					pModelAnim->pAnim = (void*)(pModelAnim->pOffset + (ULong)(ControlledAC->Anim));
					pModelAnim->pAnim = (void*)&ControlledAC->Anim[(int)pModelAnim->pOffset]; //DAW 26/04/99
 					if(pModelAnim->Type == MA_AEROSURFACE)
 						pModelAnim->ProcAnimSurface ();

 					pModelAnim = pModelAnim->List.NextItem ();
 				}
			}
		}
		pDevice = pDevice->List.NextItem ();
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoOpenCanopy
//Author		Craig Beeston
//Date			Thu 02 Dec 1999
//
//Description	Opens the canopy if the AUTOCANOPY preference is set
//
//Inputs		
//
//Returns		TRUE if Canopy is opened, FALSE if Canopy stays shut
//
//------------------------------------------------------------------------------
bool Model::AutoOpenCanopy()
{
	bool retval = false;

	for(PAERODEVICE pDevice = DeviceList; pDevice; pDevice = pDevice->List.NextItem())
		if(pDevice->Type == AeroDevice::DT_CANOPY)
		{
			if((Save_Data.gamedifficulty[GD_AUTOCANOPY]) && (pDevice->ReqVal == 0))
				Key_Tests.KeyFake3d(CANOPYEJECT, FALSE, TRUE);
			if(pDevice->Val > 0x2000)
				retval = true;
			break;
		}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CanopyOpen
//Author		Robert Slater
//Date			Mon 28 Aug 2000
//
//Description	Tests to see if the canopy device is open
//
//Inputs		
//
//Returns		TRUE if Canopy is opened, FALSE if Canopy stays shut
//
//------------------------------------------------------------------------------
bool	Model::CanopyOpen()
{
	bool	retval = false;

	for(PAERODEVICE pDevice = DeviceList; pDevice; pDevice = pDevice->List.NextItem())
		if(pDevice->Type == AeroDevice::DT_CANOPY)
		{
			if(pDevice->Val > 0x2000)
				retval = true;

			break;
		}

	return retval;
}

