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
//Filename       gear.cpp
//System         
//Author         Andrew McRae
//Date           Thu 27 Feb 1997
//Description    
//------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

#include "dosdefs.h"
#define	F_BATTLE
#include	"fileman.h"
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
#include "aerodev.h"
#include "rchatter.h"
#include "overlay.h" 
#include "3dcom.h"
#include "Areatype.h"
#include "miles.h"
#include "persons2.h"
#include "node.h"

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Gear
//Author		Andrew McRae
//Date			Mon 10 Mar 1997
//
//Description	Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Gear::Gear (PMODEL pmodel, GEAR_IDENT id)
{

	pModel = pmodel;

	Ident = id;
	pDevice = NULL;

	LegPos = 0;
	OldLegPos = 0;
	NullVec (LegForce);
	NullVec (GroundForce);
	NullVec (TyreForce);

	List.Attach (&pModel->GearList, this);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Gear
//Author		Andrew McRae
//Date			Mon 10 Mar 1997
//
//Description	Destructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Gear::~Gear ()
{

	List.Detach (this);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Initialise
//Author		Andrew McRae
//Date			Thu 30 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Gear::SetDimensions (FP x0, FP y0, FP z0, FP x1, FP y1, FP z1)
{

	pos0.x = x0;
	pos0.y = y0;
	pos0.z = z0;

	pos1.x = x1;
	pos1.y = y1;
	pos1.z = z1;

	SubVec (LegVec, pos1, pos0);
	LegLength = VecLen (LegVec);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetParams
//Author		Andrew McRae
//Date			Tue 4 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Gear::SetSuspension (FP Cstiffness, FP Cdamping)
{
	CStiffness = Cstiffness;
	CDamping   = Cdamping;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTyres
//Author		Andrew McRae
//Date			Tue 1 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Gear::SetTyres (FP rollres, FP friction, FP brakepower)
{

	RollRes   = rollres;
	CFriction = friction;
	CBrake    = brakepower;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGearDevice
//Author		Craig Beeston
//Date			Wed 3 Nov 1999
//
//Description	Sets the device to check for gear extension
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Gear::SetGearDevice(AeroDevice::DT_TYPE dt_type, KeyVal3D key)
{
	pDevice = NULL;
	if(dt_type == AeroDevice::DT_VOID)
		return;

	for(PAERODEVICE pAeroDevice = pModel->DeviceList; pAeroDevice; pAeroDevice = pAeroDevice->List.NextItem())
		if((pAeroDevice->Type == dt_type) && (pAeroDevice->UpKey == key))
		{
			pDevice = pAeroDevice;
			break;
		}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcIntPos
//Author		Andrew McRae
//Date			Thu 27 Feb 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Gear::CalcIntL (UByte* pTexture)
{

	// calc position of intersect between leg vector and ground
	// calc actual position in ac coords
	// and leg length parametric value

	// see notes section 2, page 37.

	FCRD wpos0, wpos1;	//CSB 12/01/99
	FCRDlong WPos0, WPos1;

	// calc w0
	TnsPnt (pos0, wpos0, pModel->Ori);
	
	WPos0.x = wpos0.x;
	WPos0.y = wpos0.y;
	WPos0.z = wpos0.z;

	AddVec (WPos0, WPos0, pModel->Pos);

	// calc g0
	COORDS3D iwpos0;
	iwpos0.X = WPos0.x;
	iwpos0.Y = WPos0.y;
	if(iwpos0.Y > 5000)	iwpos0.Y -= 5000;
	else				iwpos0.Y =  0;
	iwpos0.Z = WPos0.z;

	FP delta = 0;
//DeadCode CSB 2Nov00 	if(pModel->Speed < 50)
	{
		SWord px = iwpos0.X * 16;
		SWord pz = iwpos0.Z * 16;
		Float sx, cx, sz, cz;
		Math_Lib.high_sin_cos(Angles(px), sx, cx);
		Math_Lib.high_sin_cos(Angles(pz), sz, cz);
		delta = 4.0 * FP(sx) * FP(sz);/// (32768.0 * 32678.0);
//DeadCode CSB 2Nov00 		delta *= 1.0 * (1.0 - pModel->Speed * (1.0 / 50.0));
	}

	FP g0 = _Collide.GroundAltitude (iwpos0, pTexture);	//CSB 12/01/99
	g0 += delta;

//#define PRINT_GEAR_DATA
#ifdef PRINT_GEAR_DATA
	switch(Ident)
	{
		case NOSE:
			PrintVar(50, 13, "GH %.2f ", (FP)(g0 / 100.0));
			break;
		case PORT:
			PrintVar(45, 15, "GH %.2f ", (FP)(g0 / 100.0));
			break;
		case STBD:
			PrintVar(55, 15, "GH %.2f ", (FP)(g0 / 100.0));
			break;
		case TAIL:
			PrintVar(50, 17, "GH %.2f ", (FP)(g0 / 100.0));
			break;
	}
#endif

	// calc w1
	TnsPnt (pos1, wpos1, pModel->Ori);

	WPos1.x = wpos1.x;
	WPos1.y = wpos1.y;
	WPos1.z = wpos1.z;

	AddVec (WPos1, WPos1, pModel->Pos);

	// calc g1
	COORDS3D iwpos1;
	iwpos1.X = WPos1.x;
	iwpos1.Y = WPos1.y;
	if(iwpos1.Y > 5000)	iwpos1.Y -= 5000;
	else				iwpos1.Y =  0;
	iwpos1.Z = WPos1.z;
	FP g1 = _Collide.GroundAltitude (iwpos1);
	g1 += delta;

//DeadCode CSB 03/12/99		FP div = (g1 - g0 - WPos1.y + WPos0.y);
	FP div = (WPos1.y - WPos0.y);

	if (div == 0) return FALSE;

	if (WPos1.y <= WPos0.y) return FALSE;

//DeadCode CSB 03/12/99		IntL = (WPos0.y - g0) / div;
	IntL = (g0 - WPos0.y) / div;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcIntPos
//Author		Andrew McRae
//Date			Wed 5 Mar 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Gear::CalcIntPos ()
{
//DEADCODE CB 03/11/99 
//DEADCODE CB 03/11/99 	FP le = IntL;
//DEADCODE CB 03/11/99 
//DEADCODE CB 03/11/99 	if (le > 1) le = 1;
//DEADCODE CB 03/11/99 
//DEADCODE CB 03/11/99 	IntPos.x = (le * LegVec.x) + pos0.x;
//DEADCODE CB 03/11/99 	IntPos.y = (le * LegVec.y) + pos0.y;
//DEADCODE CB 03/11/99 	IntPos.z = (le * LegVec.z) + pos0.z;

}




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessGears
//Author		Craig Beeston
//Date			Mon 11 Jan 1999
//
//Description	Calculates the forces on the undercarriage of the aircraft
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ProcessGears (AirStrucPtr const ControlledAC, FP forcex, FP forcey, FP forcez, FP momenty)
{
	static bool HandBrakeOn = FALSE;
	static bool Takenoff    = FALSE;
	static bool Landed      = FALSE;
	static bool Exitted     = FALSE;

	if(GearList == NULL) return;
	PGEAR pGear;

	if(FirstCycle)
	{
//DeadCode CSB 26Jun00 		UByte temp;
//DeadCode CSB 26Jun00 		PGEAR gf = NULL, gb = NULL, gl = NULL, gr = NULL;
//DeadCode CSB 26Jun00 		for(pGear = GearList; pGear; pGear = pGear->List.NextItem())
//DeadCode CSB 26Jun00 		{
//DeadCode CSB 26Jun00 			pGear->CalcIntL(&temp);
//DeadCode CSB 26Jun00 			if(pGear->Ident == NOSE)	gf = pGear;
//DeadCode CSB 26Jun00 			if(pGear->Ident == TAIL)	gb = pGear;
//DeadCode CSB 26Jun00 			if(pGear->Ident == PORT)	gl = pGear;
//DeadCode CSB 26Jun00 			if(pGear->Ident == STBD)	gr = pGear;
//DeadCode CSB 26Jun00 		}
//DeadCode CSB 26Jun00 
//DeadCode CSB 26Jun00 //DeadCode CSB 26Jun00 		SWord newroll  = Rads2Rowan(CalcAngle(gl->LegVec * gl->IntL - gr->LegVec * gr->IntL, gr->pos0.x - gl->pos0.x));
//DeadCode CSB 26Jun00 
//DeadCode CSB 26Jun00 		ResetAngles(ControlledAC, -ControlledAC->hdg, newpitch, 0);

		COORDS3D AcPos;
		AcPos.X = ControlledAC->World.X;
		if(ControlledAC->World.Y > 5000)
			AcPos.Y = ControlledAC->World.Y - 5000;
		else AcPos.Y = 0;
		AcPos.Z = ControlledAC->World.Z;
		GroundHeight = _Collide.GroundAltitude(AcPos);

		if((AcPos.Y - GroundHeight) < MAXAIRCRAFTSIZE)
		{
			HandBrakeOn = TRUE;
			Takenoff    = FALSE;
			Landed      = FALSE;
			Exitted     = FALSE;

			Bool NoseWheel = FALSE;

			pGear = GearList;
			while (pGear != NULL)
			{
				if(pGear->Ident == NOSE) NoseWheel = TRUE; 
				pGear->LegPos = 0.333;
				pGear->OldLegPos = 0.333;
				pGear = pGear->List.NextItem();
			}

			FP z1 = 0, y1 = 0;
			FP z2 = 0, y2 = 0;

			pGear = GearList;
			while (pGear != NULL)
			{
				if(NoseWheel)
				{
					if(pGear->Ident == NOSE)
					{
						z1 = (pGear->pos0.z + pGear->pos0.z + pGear->pos1.z) / 3.0; 
						y1 = (pGear->pos0.y + pGear->pos0.y + pGear->pos1.y) / 3.0; 
					}
					if(pGear->Ident == PORT)
					{
						z2 = (pGear->pos0.z + pGear->pos0.z + pGear->pos1.z) / 3.0; 
						y2 = (pGear->pos0.y + pGear->pos0.y + pGear->pos1.y) / 3.0; 
					}
				}
				else
				{
					if(pGear->Ident == PORT)
					{
						z1 = (pGear->pos0.z + pGear->pos0.z + pGear->pos1.z) / 3.0; 
						y1 = (pGear->pos0.y + pGear->pos0.y + pGear->pos1.y) / 3.0; 
					}
					if(pGear->Ident == TAIL)
					{
						z2 = (pGear->pos0.z + pGear->pos0.z + pGear->pos1.z) / 3.0; 
						y2 = (pGear->pos0.y + pGear->pos0.y + pGear->pos1.y) / 3.0; 
					}
				}
				pGear = pGear->List.NextItem();
			}
			FP fnewpitch = CalcAngle(z1 - z2, y2 - y1);
			UWord newpitch = UWord(Rads2Rowan(fnewpitch));
			ResetAngles(ControlledAC, -ControlledAC->hdg, newpitch, 0);
			
			FP newalt = -y1 * FCos(fnewpitch) - z1 * FSin(fnewpitch);
			Pos.y = GroundHeight + newalt + 3;
		}
	}


	if((Pos.y > HIGHESTGROUND) || ((Pos.y - GroundHeight) > MAXAIRCRAFTSIZE))
	{
		pGear = GearList;
		while (pGear != NULL)
		{
			pGear->LegPos = 0;
			pGear->OldLegPos = 0;
			NullVec(pGear->LegForce);
			NullVec(pGear->TyreForce);
			pGear = pGear->List.NextItem();
		}
		return;
	}


	if((LeftWheelBrake > 0) || (RightWheelBrake > 0))
		HandBrakeOn = FALSE;
	
	if(HandBrakeOn)
		LeftWheelBrake = RightWheelBrake = 0x4000;
	
	pGear = GearList;
	UByte Texture = 0;

	Bool nose_tail_touching = FALSE;
	while (pGear != NULL)
	{
		if((pGear->pDevice) && (pGear->pDevice->Val < 0x3000))
		{
			pGear->LegPos = 0;
			pGear->OldLegPos = 0;
			NullVec(pGear->LegForce);
			NullVec(pGear->TyreForce);
		}
		else
		{
			pGear->CalcLegForce_Reaction(ControlledAC, &Texture);
			pGear->WheelPos.x = pGear->pos0.x + pGear->LegPos * pGear->LegVec.x;
			pGear->WheelPos.y = pGear->pos0.y + pGear->LegPos * pGear->LegVec.y;
			pGear->WheelPos.z = pGear->pos0.z + pGear->LegPos * pGear->LegVec.z;
		}
		pGear = pGear->List.NextItem();
	}

//#define PRINT_GEAR_DATA
#ifdef PRINT_GEAR_DATA
	for(pGear = GearList; pGear; pGear = pGear->List.NextItem())
		switch(pGear->Ident)
		{
			case NOSE:
				PrintVar(10, 13, "GP: %.2f ", pGear->LegPos);
	//DEADCODE CB 02/11/99 			PrintVar(10, 14, "G V: %.2f ", WheelVel.x);
				break;
			case PORT:
				PrintVar( 5, 15, "GP: %.2f ", pGear->LegPos);
	//DEADCODE CB 02/11/99 			PrintVar( 5, 16, "G V: %.2f ", WheelVel.x);
				break;
			case STBD:
				PrintVar(15, 15, "GP: %.2f ", pGear->LegPos);
	//DEADCODE CB 02/11/99 			PrintVar(15, 16, "G V: %.2f ", WheelVel.x);
				break;
			case TAIL:
				PrintVar(10, 17, "GP: %.2f ", pGear->LegPos);
	//DEADCODE CB 02/11/99 			PrintVar(10, 18, "G V: %.2f ", WheelVel.x);
				break;
		}
#endif


	FP TotalReaction = 0;
	pGear = GearList;
	while (pGear != NULL)	//Calc total reaction force
	{
		TotalReaction += pGear->GroundForce.y;
		pGear = pGear->List.NextItem();
	}

//DEADCODE CB 02/11/99 	pGear = GearList;
//DEADCODE CB 02/11/99 	while (pGear != NULL)
//DEADCODE CB 02/11/99 	{
//DEADCODE CB 02/11/99 		pGear->CalcTyreSideForce(ControlledAC, TotalReaction, forcex, Texture);
//DEADCODE CB 02/11/99 		pGear = pGear->List.NextItem();
//DEADCODE CB 02/11/99 	}

	PGEAR pNose = NULL;
	PGEAR pTail = NULL;
	PGEAR pPort = NULL;
	PGEAR pStbd = NULL;

	for(pGear = GearList; pGear; pGear = pGear->List.NextItem())
		switch(pGear->Ident)
		{
			case NOSE:	pNose = pGear;	break;
			case TAIL:	pTail = pGear;	break;
			case PORT:	pPort = pGear;	break;
			case STBD:	pStbd = pGear;	break;
			break;
		}
	
	Bool NoseWheel = FALSE;
	for(pGear = GearList; pGear; pGear = pGear->List.NextItem())
	{
		NullVec(pGear->TyreForce);
		if(pGear->Ident == NOSE) NoseWheel = TRUE;
	}


	if(NoseWheel)
	{
		for(pGear = GearList; pGear; pGear = pGear->List.NextItem())
			pGear->CalcTyreSideForce(ControlledAC, TotalReaction, forcex, Texture);
	}
	else
	{
		if((!pTail->LegPos) && (!pPort->LegPos) && (!pStbd->LegPos))
			return;

		FCRD GroundVel;
		GroundVel.x = Vel.x;
		GroundVel.y = Vel.y;
		GroundVel.z = Vel.z;

		RotateVec2D(GroundVel.x, GroundVel.z, fHdg);
//DEADCODE CB 12/11/99 PrintVar(10, 11, "VX %.2f ", FP(GroundVel.x));
//DEADCODE CB 12/11/99 PrintVar(10, 12, "VZ %.2f ", FP(GroundVel.z));

		FP ReqForceX = -GroundVel.x * Mass / 10 - forcex;
		if(!pTail->LegPos)
		{
			pPort->TyreForce.x = ReqForceX * pPort->LegPos / (pPort->LegPos + pStbd->LegPos);
			pStbd->TyreForce.x = ReqForceX - pPort->TyreForce.x;

			pPort->TyreForce.z = pPort->GroundForce.y * pPort->RollRes;
			pStbd->TyreForce.z = pStbd->GroundForce.y * pStbd->RollRes;
			if(LeftWheelBrake)
				pPort->TyreForce.z += pPort->CBrake;
			if(RightWheelBrake)
				pStbd->TyreForce.z += pStbd->CBrake;

			if(GroundVel.z > 0)
			{
				pPort->TyreForce.z *= -1;
				pStbd->TyreForce.z *= -1;
			}
			FCRD tempfcrd = pPort->TyreForce;
			MODLIMIT(pPort->TyreForce.x, pPort->GroundForce.y * pPort->CFriction);
			MODLIMIT(pPort->TyreForce.z, pPort->GroundForce.y * pPort->CFriction);
			if((tempfcrd.x != pPort->TyreForce.x) || (tempfcrd.z != pPort->TyreForce.z))
				GearSkid = TRUE;
			tempfcrd = pStbd->TyreForce;
			MODLIMIT(pStbd->TyreForce.x, pStbd->GroundForce.y * pStbd->CFriction);
			MODLIMIT(pStbd->TyreForce.z, pStbd->GroundForce.y * pStbd->CFriction);
			if((tempfcrd.x != pStbd->TyreForce.x) || (tempfcrd.z != pStbd->TyreForce.z))
				GearSkid = TRUE;
		}
		else if((!pPort->LegPos) && (!pStbd->LegPos))
		{
			pTail->TyreForce.x = ReqForceX;
			FP FSteering = Rudder;
			if(Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS])
				FSteering -= SlipstreamRudder;
			FSteering *= -GroundVel.z * 0.025;
			pTail->TyreForce.x += FSteering;
			MODLIMIT(pTail->TyreForce.x, pTail->GroundForce.y * pTail->CFriction);
		}
		else 
		{
			FP ReqMomentY = -RotVel.y * RotInertia.y / 25/*MODEL_DT*/ - momenty;
			pTail->TyreForce.x = (ReqMomentY + ReqForceX * pPort->pos0.z) / (pPort->pos0.z - pTail->pos0.z);
			FP FSteering = Rudder;
			if(Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS])
				FSteering -= SlipstreamRudder;
			FSteering *= -GroundVel.z * 0.025;
			pTail->TyreForce.x += FSteering;

			FP MainForce = ReqForceX - pTail->TyreForce.x;
			pPort->TyreForce.x = MainForce * pPort->LegPos / (pPort->LegPos + pStbd->LegPos);
			pStbd->TyreForce.x = MainForce * pStbd->LegPos / (pPort->LegPos + pStbd->LegPos);
			pPort->TyreForce.z = pPort->GroundForce.y * pPort->RollRes;
			pStbd->TyreForce.z = pStbd->GroundForce.y * pStbd->RollRes;
			if(LeftWheelBrake)
				pPort->TyreForce.z += pPort->CBrake;
			if(RightWheelBrake)
				pStbd->TyreForce.z += pStbd->CBrake;

			if(GroundVel.z > 0)
			{
				pPort->TyreForce.z *= -1;
				pStbd->TyreForce.z *= -1;
			}
			MODLIMIT(pPort->TyreForce.x, pPort->GroundForce.y * pPort->CFriction);
			MODLIMIT(pPort->TyreForce.z, pPort->GroundForce.y * pPort->CFriction);
			MODLIMIT(pStbd->TyreForce.x, pStbd->GroundForce.y * pStbd->CFriction);
			MODLIMIT(pStbd->TyreForce.z, pStbd->GroundForce.y * pStbd->CFriction);
			MODLIMIT(pTail->TyreForce.x, pTail->GroundForce.y * pTail->CFriction);
			MODLIMIT(pTail->TyreForce.z, pTail->GroundForce.y * pTail->CFriction);

			FP deltaforce = (pPort->TyreForce.z + pStbd->TyreForce.z + pTail->TyreForce.z);
			deltaforce /= (-Mass * GroundVel.z / MODEL_DT - forcez);
			
			if(deltaforce > 1.0)
			{
				deltaforce = 1.0 / deltaforce;
				pPort->TyreForce.z *= deltaforce;
				pStbd->TyreForce.z *= deltaforce;
				pTail->TyreForce.z *= deltaforce;
			}
		}

		for(pGear = GearList; pGear; pGear = pGear->List.NextItem())
		{
			RotateVec2D(pGear->TyreForce.x, pGear->TyreForce.z, -fHdg);
			pGear->TyreForce.y += pGear->GroundForce.y;
//DEADCODE CB 02/11/99 			AddVec(pGear->TyreForce, pGear->TyreForce, pGear->GroundForce);
			TnsAxs(pGear->TyreForce, pGear->TyreForce, Ori);
			pGear->TyreForce.y = pGear->LegForce.y;
		}
	}


	if((!Takenoff) && (TotalReaction <= 0) && (Speed > 40))	
	{
		HandBrakeOn = FALSE;
		Takenoff	= TRUE;	
		Landed		= FALSE;
		Exitted		= FALSE;
		return;
	}

	if((!Landed) && (Takenoff) && (Speed < 10))
	{
		itemptr NearestAF;// = caller->ai.homebase;
		int AFRange = -1;

		int EnemyColour = NAT_ALIGN;
		if (ControlledAC->nationality==NAT_BLUE) EnemyColour = NAT_RED;
		if (ControlledAC->nationality==NAT_RED)  EnemyColour = NAT_BLUE;

		SWord i = 0;
//DEADCODE JIM 16/11/99 		while (SupplyTree::airfieldinfo[i].nationality != NAT_ALIGN)
//DEADCODE JIM 16/11/99 		{
//DEADCODE JIM 16/11/99 			if(SupplyTree::airfieldinfo[i].nationality != EnemyColour)
//DEADCODE JIM 16/11/99 			{
//DEADCODE JIM 16/11/99 				itemptr	ThisAF = *Persons2::ConvertPtrUID(SupplyTree::airfieldinfo[i].airfield);
//DEADCODE JIM 16/11/99 				ControlledAC->InterceptandRange(ThisAF);
//DEADCODE JIM 16/11/99 				if((AFRange == -1) || (ControlledAC->Range < AFRange))
//DEADCODE JIM 16/11/99 				{
//DEADCODE JIM 16/11/99 					NearestAF = ThisAF;			
//DEADCODE JIM 16/11/99 					AFRange = ControlledAC->Range;
//DEADCODE JIM 16/11/99 				}
//DEADCODE JIM 16/11/99 			}
//DEADCODE JIM 16/11/99 			i++;
//DEADCODE JIM 16/11/99 		}
		
//DEADCODE CSB 04/05/00 		if(AFRange != -1)
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			if(AFRange < MILES01)
//DEADCODE CSB 04/05/00 			{
//DEADCODE CSB 04/05/00 				_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_CALLEE_TAXITOHOLD, MSG_STATUSRESPONSE_DELAY_LP_RPT, VOICE_TOWER, NULL, ControlledAC));
//DEADCODE CSB 04/05/00 		
//DEADCODE CSB 04/05/00 //DEADCODE DAW 08/03/00 				if(NearestAF = ControlledAC->ai.homebase)
//DEADCODE CSB 04/05/00 //DEADCODE DAW 08/03/00 					Persons2::UpdatePlayerLog(ControlledAC, EventLog::LANDOKATHOME);
//DEADCODE CSB 04/05/00 //DEADCODE DAW 08/03/00 				else
//DEADCODE CSB 04/05/00 //DEADCODE DAW 08/03/00 					Persons2::UpdatePlayerLog(ControlledAC, EventLog::LANDOK);
//DEADCODE CSB 04/05/00 			}
//DEADCODE CSB 04/05/00 //DEADCODE DAW 08/03/00 			else
//DEADCODE CSB 04/05/00 //DEADCODE DAW 08/03/00 				Persons2::UpdatePlayerLog(ControlledAC, EventLog::CRASHLAND);
//DEADCODE CSB 04/05/00 		}

		Landed   = TRUE;
		Takenoff = FALSE;	
	}
	
//DeadCode  11Oct00 	if((!Exitted) && (Landed) && (Speed <= 0.1) && (TotalReaction > 0) && (ControlledAC->fly.thrustpercent <= 10))
//DeadCode  11Oct00 	{
//DeadCode  11Oct00 		if (_DPlay.Implemented && _DPlay.GameType<DPlay::COMMSQUICKMISSION)
//DeadCode  11Oct00 		{
//DeadCode  11Oct00 // if in comms begin resurrect phase 
//DeadCode  11Oct00 
//DeadCode  11Oct00 			if (ControlledAC==Persons2::PlayerSeenAC)
//DeadCode  11Oct00 			{
//DeadCode  11Oct00 // in resurrectme flight model is initialised which can cause slight rounding
//DeadCode  11Oct00 // errors in deltas
//DeadCode  11Oct00 
//DeadCode  11Oct00 				_DPlay.CheckSeen();
//DeadCode  11Oct00 				_DPlay.AddDeltas(Persons2::PlayerSeenAC,FALSE,5); //AMM 14/02/00
//DeadCode  11Oct00 				_DPlay.ResurrectMe(Persons2::PlayerSeenAC,true);//AMM 23/06/99
//DeadCode  11Oct00 				_DPlay.AddDeltas(Persons2::PlayerSeenAC,TRUE,5); //AMM 14/02/00
//DeadCode  11Oct00 				_DPlay.BackupSeen();
//DeadCode  11Oct00 
//DeadCode  11Oct00 				Takenoff = TRUE;
//DeadCode  11Oct00 				Landed = FALSE;
//DeadCode  11Oct00 			}
//DeadCode  11Oct00 		}
//DeadCode  11Oct00 //DEADCODE CB 02/11/99 		else
//DeadCode  11Oct00 //DEADCODE CB 02/11/99 		{
//DeadCode  11Oct00 //DEADCODE CB 02/11/99 			OverLay.quit3d=1;
//DeadCode  11Oct00 //DEADCODE CB 02/11/99 			Exitted = TRUE;
//DeadCode  11Oct00 //DEADCODE CB 02/11/99 		}
//DeadCode  11Oct00 	}
//Exit the game!!!!!


}

void	Model::ResetGearPos(bool	gearBlocked)
{
	if (this)													//DAW 30Jun99
	{
		//Reset all aero devices!
		for (PAERODEVICE p=DeviceList;p;p=p->List.NextItem())
		{
			if (!gearBlocked || (p->Type != AeroDevice::DT_GEAR))//DAW 30Jun99
			{
				p->Val = 0;									//RJS 10Jun99
				p->Attractor = 0;								//RJS 10Jun99
				p->OldAttractor = 0;							//RJS 10Jun99
				p->ReqVal = 0;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheckGearPos
//Author		Craig Beeston
//Date			Tue 12 Jan 1999
//
//Description	Checks that the gears are all on or above the ground
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::CheckGearPos (AirStrucPtr const ControlledAC)
{
	if(GearList == NULL) return;
	if(!GearTouched) return;

	PGEAR pGear = GearList;

	while (pGear != NULL)
	{
		FCRD wpos1;
		FCRDlong WPos1;
		TnsPnt (pGear->pos1, wpos1, Ori);
		WPos1.x = wpos1.x;
		WPos1.y = wpos1.y;
		WPos1.z = wpos1.z;

		AddVec (WPos1, WPos1, Pos);

		COORDS3D iwpos1;
		iwpos1.X = WPos1.x;
		iwpos1.Y = WPos1.y;
		if(iwpos1.Y > 5000)	iwpos1.Y -= 5000;
		else				iwpos1.Y =  0;
		iwpos1.Z = WPos1.z;

		FP g1 = _Collide.GroundAltitude (iwpos1);
		if(g1 > WPos1.y)
		{
			Pos.y += (g1 - WPos1.y);
//DeadCode CSB 13/01/99				Vel.y += (g1 - wpos1.y) / MODEL_DT;
		}

		pGear = pGear->List.NextItem();
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Gear::CalcLegForce_Reaction
//Author		Craig Beeston
//Date			Mon 11 Jan 1999
//
//Description	Calculates the forces on each undercarriage leg and the ground reaction on the tyre
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Gear::CalcLegForce_Reaction (AirStrucPtr const ControlledAC, UByte* Texture)
{
	AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
	if(		((Ident == PORT) && (adptr->LEFTWHEEL	== BS_DEAD))		//RJS 17Nov99	
		||	((Ident == STBD) && (adptr->RIGHTWHEEL	== BS_DEAD)) )		//RJS 17Nov99
	{
		Touched = FALSE;
		LegPos = 0;
		OldLegPos = 0;
		NullVec(LegForce);
		NullVec(TyreForce);
		NullVec(GroundForce);
		return;
	}
	if(CalcIntL(Texture) )
	{
		OldLegPos = LegPos;
		LegPos = IntL;

//jon	if((*Texture == AT_washShore) || (*Texture == AT_sea) || (*Texture == AT_river))
		if ( IsWater(*Texture) )
			LegPos = 0;	//Assume still in the air

		if((LegPos > 0) && (Save_Data.gamedifficulty[GD_GROUNDCOLLISIONS]) && (IsRaised(*Texture)))
		{
			Manual_Pilot.DeathSequenceOverrideDiary(ControlledAC, AUTO_CRASHTUMBLE);	//RJS 31Oct00
			Trans_Obj.View_Object->SetToDeathView(DEATH_SKID);
		}

		if(LegPos <= 0)	//Still In Air
		{
			Touched = FALSE;
			LegPos = 0;
			OldLegPos = 0;
			NullVec(LegForce);
			NullVec(TyreForce);
			NullVec(GroundForce);
			return;
		}

		if( ((LegPos > 0) && (LegPos < 1)) || (OldLegPos == 1) ) //Touching but not bottomed out
		{
			FP Force = CStiffness * LegPos + CDamping * (LegPos - OldLegPos) / MODEL_DT;
			if(Force < 0)
			{
				Touched = FALSE;
				LegPos = OldLegPos * CDamping / (CDamping + CStiffness * MODEL_DT);
				NullVec(LegForce);
				NullVec(GroundForce);
				return;
			}
			else
			{
				Touched = TRUE;
				pModel->GearTouched = TRUE;

				LegForce.x = Force * LegVec.x / LegLength;
				LegForce.y = Force * LegVec.y / LegLength;
				LegForce.z = Force * LegVec.z / LegLength;

				TnsPnt(LegForce, GroundForce, pModel->Ori);
				return;
			}
		}

		if( (LegPos >= 1) /*&& (OldLegPos < 1)*/ )	//Bottomed Out
		{
			_Miles.PlaySample(FIL_SFX_DROP_BOMB);						//RJS 16Oct00
			Touched = TRUE;
			pModel->GearTouched = TRUE;
			LegPos = 1;
			OldLegPos = 1;

			FCRD GearRotVel;
			FCRD GearVel;
			
			CPrd(GearRotVel, pos1, pModel->RotVel);
			TnsPnt(GearRotVel, GearRotVel, pModel->Ori);
			AddVec(GearVel, pModel->Vel, GearRotVel);

			if(GearVel.y < 0)
			{
//DeadCode AMM 24Nov99 				FP ReqAcc = -GearVel.y / pModel->MODEL_DT;
				FP ReqAcc = -GearVel.y / MODEL_DT;				//AMM 24Nov99

				GroundForce.x = 0;
				GroundForce.y = 1;
				GroundForce.z = 0;
				TnsAxs(GroundForce, LegForce, pModel->Ori);
				
				FCRD moment, acRotAcc, LocalAcc;
				CPrd(moment, LegForce, pos1);
				acRotAcc.x = moment.x / pModel->RotInertia.x;
				acRotAcc.y = moment.y / pModel->RotInertia.y;
				acRotAcc.z = moment.z / pModel->RotInertia.z;
	
				CPrd(LocalAcc, pos1, acRotAcc);
				
				LocalAcc.x += LegForce.x / pModel->Mass;
				LocalAcc.y += LegForce.y / pModel->Mass;
				LocalAcc.z += LegForce.z / pModel->Mass;
	
				TnsPnt(LocalAcc, LocalAcc, pModel->Ori);
	
				FP ForceFactor = ReqAcc / LocalAcc.y;
				GroundForce.y = 0;
	
//DeadCode AMM 24Nov99 				pModel->Vel.y += ForceFactor / pModel->Mass * pModel->MODEL_DT;
				pModel->Vel.y += ForceFactor / pModel->Mass * MODEL_DT;//AMM 24Nov99
	
//DeadCode AMM 24Nov99 				pModel->RotVel.x += ForceFactor * acRotAcc.x * pModel->MODEL_DT;
				pModel->RotVel.x += ForceFactor * acRotAcc.x * MODEL_DT;//AMM 24Nov99
//DeadCode AMM 24Nov99 				pModel->RotVel.y += ForceFactor * acRotAcc.y * pModel->MODEL_DT;
				pModel->RotVel.y += ForceFactor * acRotAcc.y * MODEL_DT;//AMM 24Nov99
//DeadCode AMM 24Nov99 				pModel->RotVel.z += ForceFactor * acRotAcc.z * pModel->MODEL_DT;
				pModel->RotVel.z += ForceFactor * acRotAcc.z * MODEL_DT;//AMM 24Nov99
	
				CPrd(GearRotVel, pos1, pModel->RotVel);
				TnsPnt(GearRotVel, GearRotVel, pModel->Ori);
				AddVec(GearVel, pModel->Vel, GearRotVel);
			}
			
			NullVec(GroundForce);

			AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;

#define DamageRollRes 2

			if(RollRes < DamageRollRes)
				if(		((Ident == PORT) && (adptr->LEFTWHEEL > BS_DAMLV2))
					||	((Ident == STBD) && (adptr->RIGHTWHEEL > BS_DAMLV2)) )
				{
					RollRes		= DamageRollRes;
					CFriction	= 1000;
//DeadCode CSB 20/05/99						CStiffness	/= 10;
//DeadCode CSB 20/05/99						CDamping	*= 10;
					_Miles.PlayOnce(FIL_SFX_METAL_SNAP,ControlledAC);					
				}

			return;
		}
	}

	else
	{
		LegPos = 0;
		NullVec(LegForce);
		NullVec(TyreForce);
		NullVec(GroundForce);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Gear::CalcTyreSideForce
//Author		Craig Beeston
//Date			Mon 12 Jan 1999
//
//Description	Calculates the forces due to friction of each undercarriage tyre
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Gear::CalcTyreSideForce (AirStrucPtr const ControlledAC, FP TotalReaction, FP forcex, UByte Texture)
{
	if(GroundForce.y <= 0)
	{
		NullVec(GroundForce);
		NullVec(TyreForce);
		return;
	}

	FP MaxSideForce = GroundForce.y * CFriction;

	FCRD WheelVel;
	CPrd(WheelVel, WheelPos, pModel->RotVel);

	TnsPnt(WheelVel, WheelVel, pModel->Ori);

	AddVec(WheelVel, WheelVel, pModel->Vel);

	FP angle = ControlledAC->fly.pModel->fHdg;
//DeadCode CSB 22/06/99		FP angle = CalcAngle(pModel->Ori.z.z, pModel->Ori.z.x);
	
	//Steering
	SWord FSteering = pModel->Rudder;
	if(Save_Data.flightdifficulty[FD_SLIPSTREAMEFFECTS])
		FSteering -= pModel->SlipstreamRudder;
	if (Ident == NOSE) angle += FSteering * pModel->ACMModel.SteerRatio;
	if (Ident == TAIL) angle -= FSteering * pModel->ACMModel.SteerRatio;

	RotateVec2D (WheelVel.x, WheelVel.z, angle);


	//Brakes
	FP brake = 0;
	if( ((pModel->LeftWheelBrake)  && (Ident == PORT)) || ((pModel->RightWheelBrake) && (Ident == STBD)) )
		brake = CBrake;

	if( ((Ident == NOSE) || (Ident == TAIL)) && (pModel->LeftWheelBrake != pModel->RightWheelBrake) )
	{
		if(WheelVel.x > 0) 
		{
			WheelVel.x -= 0.0875 * WheelVel.z;	//5 deg castoring
			if(WheelVel.x < 0) WheelVel.x = 0;
		}
		else
		{
			WheelVel.x += 0.0875 * WheelVel.z;	//5 deg castoring
			if(WheelVel.x > 0) WheelVel.x = 0;
		}
	}

//DeadCode AMM 24Nov99 	FP xReqAcc	= -WheelVel.x / pModel->MODEL_DT - forcex / pModel->Mass;
	FP xReqAcc	= -WheelVel.x / MODEL_DT - forcex / pModel->Mass;//AMM 24Nov99
	FP xAcc1	= 1 / pModel->Mass;						//Effect of +1 Newton side force
	FP yRotAcc	= WheelPos.z / pModel->RotInertia.y;
	FP zRotAcc	= WheelPos.y / pModel->RotInertia.z;
	FP xAcc		= WheelPos.y * zRotAcc + WheelPos.z * yRotAcc + xAcc1;
	
	GroundForce.x = xReqAcc / xAcc * GroundForce.y / TotalReaction;

//DeadCode CSB 09/02/99		GroundForce.x -= 1.0 * (pModel->Mass * WheelVel.x / pModel->MODEL_DT - forcex) * (GroundForce.y / TotalReaction);
	
//	if(WheelVel.z > 0) WheelVel.z += 5;	//To keep aircraft still on ground
//	if(WheelVel.z < 0) WheelVel.z -= 5;

//	GroundForce.z = -WheelVel.z * brake;
	if(WheelVel.z > 0)	GroundForce.z = -RollRes * GroundForce.y - brake;
	else				GroundForce.z =  RollRes * GroundForce.y + brake;

//DeadCode AMM 24Nov99 	FP DeltaV = TotalReaction / GroundForce.y * GroundForce.z / pModel->Mass * pModel->MODEL_DT;	//Approx
	FP DeltaV = TotalReaction / GroundForce.y * GroundForce.z / pModel->Mass * MODEL_DT;	//Approx//AMM 24Nov99
	if( (WheelVel.z > 0) && (-DeltaV > WheelVel.z) )
		GroundForce.z *= -WheelVel.z / DeltaV;			//Just enough force to stop aircraft rolling
	if( (WheelVel.z < 0) && (DeltaV > -WheelVel.z) )
		GroundForce.z *= -WheelVel.z / DeltaV;			//Just enough force to stop aircraft rolling

	TyreForce.x = GroundForce.x;
	TyreForce.y = GroundForce.y;
	TyreForce.z = GroundForce.z;

//Check for skidding
//DeadCode CSB 14/06/99		FP OldTyreForce = TyreForce.x;
//DeadCode CSB 14/06/99		MODLIMIT(TyreForce.x, MaxSideForce);
//DeadCode CSB 14/06/99		if(TyreForce.x != OldTyreForce) pModel->GearSkid = TRUE;
//DeadCode CSB 14/06/99		OldTyreForce = TyreForce.z;
//DeadCode CSB 14/06/99		MODLIMIT(TyreForce.z, MaxSideForce);
//DeadCode CSB 14/06/99		if(TyreForce.z != OldTyreForce) pModel->GearSkid = TRUE;
	FP OldForceX = TyreForce.x;
	FP OldForceZ = TyreForce.z;

//DeadCode CSB 03/12/99		if(TyreForce.x > MaxSideForce)
//DeadCode CSB 03/12/99			TyreForce.x = GroundForce.y * 0.5;
//DeadCode CSB 03/12/99		if(TyreForce.x < -MaxSideForce)
//DeadCode CSB 03/12/99			TyreForce.x = -GroundForce.y * 0.5;
//DeadCode CSB 03/12/99		if(TyreForce.z > MaxSideForce)
//DeadCode CSB 03/12/99			TyreForce.z = GroundForce.y * 0.5;
//DeadCode CSB 03/12/99		if(TyreForce.z < -MaxSideForce)
//DeadCode CSB 03/12/99			TyreForce.z = -GroundForce.y * 0.5;
	MODLIMIT(TyreForce.x, MaxSideForce);
	MODLIMIT(TyreForce.z, MaxSideForce);

	if((TyreForce.x != OldForceX) || (TyreForce.z != OldForceZ))
		pModel->GearSkid = TRUE;

//DeadCode CSB 21/06/99		RotateVec2D (TyreForce.x, TyreForce.z, -angle);
//DeadCode CSB 21/06/99	
//DeadCode CSB 21/06/99		TnsAxs(TyreForce, TyreForce, pModel->Ori);

	FCRD temp = TyreForce;
	FP sinang = FSin(pModel->fRoll);
	FP cosang = FCos(pModel->fRoll);
	
	TyreForce.x = temp.x * cosang - temp.y * sinang;
	TyreForce.y = temp.y * cosang + temp.x * sinang;
	TyreForce.z = temp.z;

	temp = TyreForce;
	sinang = FSin(pModel->fPitch);
	cosang = FCos(pModel->fPitch);

	TyreForce.x = temp.x;
	TyreForce.y = temp.y * cosang - temp.z * sinang;
	TyreForce.z = temp.z * cosang + temp.y * sinang;

	if(Save_Data.gamedifficulty[GD_GROUNDCOLLISIONS])
	{
		FP AbsVelx = WheelVel.x;
		if(AbsVelx < 0) AbsVelx *= -1;
		FP AbsVelz = WheelVel.z;
		if(AbsVelz < 0) AbsVelz *= -1;
		if(AbsVelz > AbsVelx) AbsVelx = AbsVelz;

		FP MaxVelY = 10;

		FP MaxVel = 0;
		// note is there any way to land on roads?
		switch(Texture & AT_MASK)
		{
//jon		case AT_snow:	//Concrete
//jon		case AT_spare2:	//Steel planking
//jon		case AT_spare3:	//Steel planking
		case AT_darkGrass:
		case AT_midGrass:
		case AT_lightGrass:
		case AT_garden:
		case AT_golfCourse:
		case AT_spread1:
		case AT_spread2:
		case AT_spread3:
		case AT_spread4:
		case AT_spread5:
		{							//Good Runway
			MaxVel = 150;
			break;
		}
//jon	case AT_soil:
		case AT_field1:
		case AT_field2:
		case AT_field3:
		case AT_field4:
		case AT_field5:
		{				//Rough Runway
			MaxVel = 75;
			break;
		}
//jon		case AT_softRock:
//jon		case AT_vSoftRock:
//jon		case AT_hardRock:
//jon		case AT_sandyRock:
//jon		case AT_roughSoil:
//jon		case AT_softEarth:
//jon		case AT_roughEarth:
//jon		case AT_highRock:
//jon		case AT_lowRock:
//jon		case AT_snowyRock:
//jon		case AT_mossyRock:
//jon		case AT_rockySnow:
		case AT_rough:
		case AT_roughGrass:
		case AT_patchyGrass:
		case AT_sand:
		{				//Emergency landing
			MaxVel = 50;
			break;
		}
		break;
		}

		AircraftAnimData*	adptr = (AircraftAnimData*) ControlledAC->Anim;
		switch(Ident)
		{
//DEADCODE CSB 22/11/99 			case NOSE:
//DEADCODE CSB 22/11/99 			{
//DEADCODE CSB 22/11/99 	//DeadCode CSB 20/05/99				PrintVar(40, 10, "Text %.0f ", FP(Texture & AT_MASK));
//DEADCODE CSB 22/11/99 				MaxVel *= 1 - (FP)adptr->FRONTWHEEL / (FP)BS_DEAD;
//DEADCODE CSB 22/11/99 				MaxVelY *= 1 - (FP)adptr->FRONTWHEEL / (FP)BS_DEAD;
//DEADCODE CSB 22/11/99 				break;
//DEADCODE CSB 22/11/99 			}
//DEADCODE CSB 22/11/99 			case TAIL:
//DEADCODE CSB 22/11/99 			{
//DEADCODE CSB 22/11/99 	//DeadCode CSB 20/05/99				PrintVar(40, 20, "Text %.0f ", FP(Texture & AT_MASK));
//DEADCODE CSB 22/11/99 				MaxVel *= 1 - (FP)adptr->BACKWHEEL / (FP)BS_DEAD;
//DEADCODE CSB 22/11/99 				MaxVelY *= 1 - (FP)adptr->BACKWHEEL / (FP)BS_DEAD;
//DEADCODE CSB 22/11/99 				break;
//DEADCODE CSB 22/11/99 			}
			case PORT:
			{
	//DeadCode CSB 20/05/99				PrintVar(30, 15, "Text %.0f ", FP(Texture & AT_MASK));
				MaxVel *= 1 - (FP)adptr->LEFTWHEEL / (FP)BS_DEAD;
				MaxVelY *= 1 - (FP)adptr->LEFTWHEEL / (FP)BS_DEAD;
				break;
			}
			case STBD:
			{
	//DeadCode CSB 20/05/99				PrintVar(50, 15, "Text %.0f ", FP(Texture & AT_MASK));
				MaxVel *= 1 - (FP)adptr->RIGHTWHEEL / (FP)BS_DEAD;
				MaxVelY *= 1 - (FP)adptr->RIGHTWHEEL / (FP)BS_DEAD;
				break;
			}
		}

		if( (RollRes < DamageRollRes) && ((AbsVelx > MaxVel) || (-WheelVel.y > MaxVelY)) )
		{
			RollRes		= DamageRollRes;
			CFriction	= 1000;
	//DeadCode CSB 20/05/99			CStiffness	/= 10;
	//DeadCode CSB 20/05/99			CDamping	*= 10;
			_Miles.PlayOnce(FIL_SFX_METAL_SNAP,ControlledAC);					
		}
	}

//#define PRINT_GEAR_FORCES
#ifdef PRINT_GEAR_FORCES
	switch(Ident)
	{
		case NOSE:
			PrintVar(20,  2, "Pos:    %.3f ", LegPos);
			PrintVar(20,  3, "Vel_X   %.2f ", WheelVel.x);
			PrintVar(20,  4, "Vel_Z   %.2f ", WheelVel.z);
			PrintVar(20,  5, "Force_X %.0f ", TyreForce.x);
			PrintVar(20,  6, "Force_Y %.0f ", TyreForce.y);
			PrintVar(20,  7, "Force_Z %.0f ", TyreForce.z);
			break;		   

		case PORT:
			PrintVar(10,  9, "Pos:    %.3f ", LegPos);
			PrintVar(10, 10, "Vel_X   %.2f ", WheelVel.x);
			PrintVar(10, 11, "Vel_Z   %.2f ", WheelVel.z);
			PrintVar(10, 12, "Force_X %.0f ", TyreForce.x);
			PrintVar(10, 13, "Force_Y %.0f ", TyreForce.y);
			PrintVar(10, 14, "Force_Z %.0f ", TyreForce.z);
			break;

		case STBD:
			PrintVar(30,  9, "Pos:    %.3f ", LegPos);
			PrintVar(30, 10, "Vel_X   %.2f ", WheelVel.x);
			PrintVar(30, 11, "Vel_Z   %.2f ", WheelVel.z);
			PrintVar(30, 12, "Force_X %.0f ", TyreForce.x);
			PrintVar(30, 13, "Force_Y %.0f ", TyreForce.y);
			PrintVar(30, 14, "Force_Z %.0f ", TyreForce.z);
			break;

		case TAIL:
			PrintVar(20, 16, "Pos:    %.3f ", LegPos);
			PrintVar(20, 17, "Vel_X   %.2f ", WheelVel.x);
			PrintVar(20, 18, "Vel_Z   %.2f ", WheelVel.z);
			PrintVar(20, 19, "Force_X %.0f ", TyreForce.x);
			PrintVar(20, 20, "Force_Y %.0f ", TyreForce.y);
			PrintVar(20, 21, "Force_Z %.0f ", TyreForce.z);
			break;
	}
#endif

}

