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
//Filename       modint.cpp
//System         
//Author         Andrew McRae
//Date           Mon 24 Feb 1997
//Description    Flight model interface functions
//------------------------------------------------------------------------------

#define F_GRAFIX												//RJS 09Dec97
#define F_BATTLE												//RJS 09Dec97
#include	<stdio.h>
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
#include "files.g"
#include "miles.h"
#include "replay.h"
#include "persons2.h"
#include "flymodel.h"
#include "3DCom.h"

#define MODLIMIT(val,lim) 	if (val>lim) val=lim; \
							elseif (val<-lim) val=-lim

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetDeltaPos
//Author		Andrew McRae
//Date			Wed 5 Feb 1997
//
//Description	Change Aircraft Position (in cms)
//
//Inputs		AirStrucPtr & a change in position
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ResetDeltaPos (AirStrucPtr const ControlledAC,SLong x, SLong y, SLong z)
{

	Pos.x += x;
	Pos.y += y;
	Pos.z += z;

	SetAirStrucPosition (ControlledAC);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetPosition
//Author		Andrew McRae
//Date			Wed 26 Feb 1997
//
//Description	Change position to ...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ResetPosition (AirStrucPtr const ControlledAC,SLong x, SLong y, SLong z)
{

	Pos.x = x;
	Pos.y = y;
	Pos.z = z;

	SetAirStrucPosition (ControlledAC);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetVelocity
//Author		Andrew McRae
//Date			Wed 26 Feb 1997
//
// Reset aircraft velocity (cms/csec)
// Pass TRUE to reset aircraft orientation to align with new velocity // vector
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ResetVelocity (AirStrucPtr const ControlledAC,SLong x, SLong y, SLong z, Bool Align)
{

	Vel.x = x;
	Vel.y = y;
	Vel.z = z;

	SetAirStrucVelocity (ControlledAC);

	if (Align)
	{
		Ori.z.x = Vel.x;
		Ori.z.y = Vel.y;
		Ori.z.z = Vel.z;

		NrmVec (Ori.z, Ori.z);

		Ori.y.x = 0;
		Ori.y.y = 1;
		Ori.y.z = 0;

		CPrdX (Ori);
		CPrdY (Ori);

		SetAirStrucOrientation (ControlledAC);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetAngles
//Author		Andrew McRae
//Date			Wed 26 Feb 1997
//
// 		Reset aircraft orientation (RowanAngles)
// 		order of rotation is bearing, pitch then roll
// 		positive bearing is clockwise looking down onto the ground
// 		positive pitch is nose up
// 		positive roll is right wing down
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::ResetAngles (AirStrucPtr const ControlledAC,UWord hdg, UWord pitch, UWord roll)
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

	SetOri (Ori, Rowan2Rads(pitch), Rowan2Rads(hdg), Rowan2Rads(roll));

	SetAirStrucOrientation (ControlledAC);

}


//TempCode ARM 27Aug97 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//TempCode ARM 27Aug97 //Procedure		HaveWeLanded
//TempCode ARM 27Aug97 //Author		Andrew McRae
//TempCode ARM 27Aug97 //Date			Mon 24 Feb 1997
//TempCode ARM 27Aug97 //
//TempCode ARM 27Aug97 //Description	
//TempCode ARM 27Aug97 //
//TempCode ARM 27Aug97 //Inputs		
//TempCode ARM 27Aug97 //
//TempCode ARM 27Aug97 //Returns	
//TempCode ARM 27Aug97 //
//TempCode ARM 27Aug97 //------------------------------------------------------------------------------
//TempCode ARM 27Aug97 Collide::Pos Model::HaveWeLanded (AirStruc*ac, ANGLES& pitch, ANGLES& roll)
//TempCode ARM 27Aug97 {
//TempCode ARM 27Aug97 	return _Collide.LANDED_OK;
//TempCode ARM 27Aug97 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateAirStruc
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Updates AirStruc structure with new data
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::UpdateAirStruc (AirStrucPtr const ControlledAC)
{
//DeadCode AMM 24Nov98 	if (_Replay.Playback && ControlledAC==Persons2::PlayerSeenAC)
//DeadCode AMM 24Nov98 		return;

//	if (_Replay.Record || _Replay.Playback)
//		_Replay.Record=_Replay.Record;

	// Velocity
	SetAirStrucVelocity (ControlledAC);
	// Orientation
	SetAirStrucOrientation (ControlledAC);
	// Position
	SetAirStrucPosition (ControlledAC);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAirStrucPosition
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	Cleanly changes AirStuc position in the world
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetAirStrucPosition (AirStrucPtr const ControlledAC)
{

// 	WorldStuff* World = ControlledAC->GetCurrWorld ();
// 	World->RemoveFromWorld (ControlledAC);
	FCRD CoGOffset;
	TnsPnt(ShapeCoG, CoGOffset, Ori);

/* TEST CODE CSB 18/06/99 */	COORDS3D OldWorld = ControlledAC->World;
	
	ControlledAC->World.X = (SLong)(Pos.x + 0.5 - CoGOffset.x);
	ControlledAC->World.Y = (SLong)(Pos.y + 0.5 - CoGOffset.y);
	ControlledAC->World.Z = (SLong)(Pos.z + 0.5 - CoGOffset.z);

//DeadCode CSB 18/06/99	/* TEST CODE CSB 18/06/99 */	if(		(OldWorld.X - ControlledAC->World.X > 1000) || (ControlledAC->World.X - OldWorld.X > 1000) 
//DeadCode CSB 18/06/99	/* TEST CODE CSB 18/06/99 */		||	(OldWorld.Y - ControlledAC->World.Y > 1000) || (ControlledAC->World.Y - OldWorld.Y > 1000) 
//DeadCode CSB 18/06/99	/* TEST CODE CSB 18/06/99 */		||	(OldWorld.Z - ControlledAC->World.Z > 1000) || (ControlledAC->World.Z - OldWorld.Z > 1000) )
//DeadCode CSB 18/06/99	/* TEST CODE CSB 18/06/99 */		int BreakPoint = 0;


	ControlledAC->uniqueID.changed = TRUE;

// 	World->AddToWorld (ControlledAC);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAirStrucOrientation
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetAirStrucOrientation (AirStrucPtr const ControlledAC)
{

	// sheading
	if ((Ori.z.x == 0) && (Ori.z.z == 0))
		fHdg = CalcAngle (Ori.y.z, Ori.y.x);
	else
		fHdg = CalcAngle (Ori.z.z, Ori.z.x);

	// pitch
	fPitch = CalcAngle (VecLen2D (Ori.z.x, Ori.z.z), Ori.z.y);

	// roll
	FCRD vecx;
	FCRD vecz;
	FP sin, cos;

	sin = Ori.z.x;
	cos = Ori.z.z;
	NrmVec2D (sin, cos);
	RotVecYSC (Ori.x, vecx, -sin, cos);
	RotVecYSC (Ori.z, vecz, -sin, cos);

	RotVecXSC (vecx, vecx, vecz.y, vecz.z);

//DeadCode AMM 29Jun99 	OldfRoll = fRoll;
	fRoll = CalcAngle (vecx.x, -vecx.y);

	if(ControlledAC == Persons2::PlayerSeenAC)
	{
		Three_Dee.viewer_oldhdg   = ControlledAC->hdg;
		Three_Dee.viewer_oldpitch = ControlledAC->pitch;
		Three_Dee.viewer_oldroll  = ControlledAC->roll;
	}

	// These are Global Angles
	ControlledAC->hdg	= (Angles)(Rads2Rowan(fHdg));
//	ControlledAC->fly.chdg	= ControlledAC->hdg;
	ControlledAC->pitch	= (Angles)(Rads2Rowan(fPitch));
	ControlledAC->roll	= (Angles)(Rads2Rowan(fRoll));

	FP	velpitch = CalcAngle (VecLen2D(Vel.x, Vel.z), Vel.y);
	velpitch = AngleSign (velpitch);
	ControlledAC->fly.cpitch = (Angles)(Rads2Rowan(velpitch));

//DeadCode AMM 29Jun99 	grndhdg = ControlledAC->hdg;									//RJS 05May98

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetAirStrucVelocity
//Author		Andrew McRae
//Date			Tue 7 Jan 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::SetAirStrucVelocity (AirStrucPtr const ControlledAC)
{
	SLong wx, wy, wz;	
	MissManCampSky().GetWind(Pos.y, wx, wy, wz);

	ControlledAC->vel_x = (SLong)(10000 * Vel.x - wx);
	ControlledAC->vel_y = (SLong)(10000 * Vel.y - wy);
	ControlledAC->vel_z = (SLong)(10000 * Vel.z - wz);

//DEADCODE CSB 08/11/99 	ControlledAC->velhori = (SWord)(VecLen2D(ControlledAC->velx, ControlledAC->velz) );	//CSB 10/06/99
	FCRD temp;
	temp.x = ControlledAC->vel_x;
	temp.y = ControlledAC->vel_y;
	temp.z = ControlledAC->vel_z;
	ControlledAC->vel_ = SLong(VecLen(temp));
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateModel
//Author		Andrew McRae
//Date			Fri 2 May 1997
//
//Description	Sets up Model data from AirStruc
//
//Inputs		none
//
//Returns		none
//
//------------------------------------------------------------------------------
void Model::UpdateModel (AirStrucPtr const ControlledAC)
{
	// Orientation
	Ori.x.x = 1;
	Ori.x.y = 0;
	Ori.x.z = 0;
	Ori.y.x = 0;
	Ori.y.y = 1;
	Ori.y.z = 0;
	Ori.z.x = 0;
	Ori.z.y = 0;
	Ori.z.z = 1;
	if (ControlledAC->pitch==ANGLES_90Deg)
		ControlledAC->pitch=ANGLES_90BareDeg;
	else
	if (ControlledAC->pitch==ANGLES_270Deg)
		ControlledAC->pitch=ANGLES_270BareDeg;
	RotOriYVec (Ori, -Rowan2Rads(ControlledAC->hdg));
	RotOriXVec (Ori, Rowan2Rads(ControlledAC->pitch));
	RotOriZVec (Ori, Rowan2Rads(ControlledAC->roll));

	CPrdX (Ori);
	CPrdY (Ori);

	NrmVec (Ori.x, Ori.x);
	NrmVec (Ori.y, Ori.y);
	NrmVec (Ori.z, Ori.z);

	// Velocity
	Vel.x = Ori.z.x * FP(ControlledAC->vel_) * 0.0001;
	Vel.y = Ori.z.y * FP(ControlledAC->vel_) * 0.0001;
	Vel.z = Ori.z.z * FP(ControlledAC->vel_) * 0.0001;

	if(ControlledAC->vel_ != 0)
	{
		SLong wx, wy, wz;

		MissManCampSky().GetWind(ControlledAC->World.Y, wx, wy, wz);
		Vel.x += wx * 0.0001;
		Vel.y += wy * 0.0001;
		Vel.z += wz * 0.0001;
	}

	NullVec (RotVel);

	// Position
	Coords3D w,c1,c2;
	FCRD CoGOffset;

	SHAPE.GetContactPoint(ControlledAC, CT_GRAVITY, w, c1, c2);
	ShapeCoG.x = c1.X;
	ShapeCoG.y = c1.Y;
	ShapeCoG.z = c1.Z;

	TnsPnt(ShapeCoG, CoGOffset, Ori);

	Pos.x = ControlledAC->World.X + CoGOffset.x;
	Pos.y = ControlledAC->World.Y + CoGOffset.y;
	Pos.z = ControlledAC->World.Z + CoGOffset.z;
}




// SURFACE ANIMATIONS


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModelAnim
//Author		Andrew McRae
//Date			Wed 2 Apr 1997
//
//Description	MA_SUSPENSION
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ModelAnim::ModelAnim (AirStrucPtr const ControlledAC,MODELANIMTYPE type, PGEAR gear, void* pbyte, ULong min, ULong max)
{

	Type = type;

	pModel = gear->pModel;

	pGear = gear;

	pOffset = ControlledAC->Anim.Offset(pbyte);// (ULong)pbyte - (ULong)(ControlledAC->Anim);
	pAnim = NULL;

	Min = min;
	Max = max;

	List.Attach (&gear->pModel->AnimList, this);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModelAnim
//Author		Andrew McRae
//Date			Wed 2 Apr 1997
//
//Description	MA_SURFACE & MA_GENERICFP
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ModelAnim::ModelAnim (	AirStrucPtr		ControlledAC,
						MODELANIMTYPE	type,
						PMODEL			pmodel,
						void*			psrce,
						void*			pbyte,
						SLong			minval,
						SLong			maxval,
						SLong			scale,
						Bool			AnimAC)
{

	Type = type;

	pModel = pmodel;

	pGear = NULL;

	pOffset = ControlledAC->Anim.Offset(pbyte);//(ULong)pbyte - (ULong)(ControlledAC->Anim);
	if (AnimAC)
	{
		pSrcOffset = (UByteP)psrce - (UByteP)ControlledAC;
		pSrce = NULL;
	}
	else
	{
		pSrcOffset = -1;
		pSrce = psrce;
	}

	pAnim = NULL;

	Min = minval;														//RJS 14May98
	Max = maxval;														//RJS 14May98

	Scale = Max - Min;													//RJS 14May98

	List.Attach (&pModel->AnimList, this);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ModelAnim
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
ModelAnim::~ModelAnim ()
{
	List.Detach (this);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcAnimUnity
//Author		Andrew McRae
//Date			Wed 2 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ModelAnim::ProcAnimSuspension ()
{
  	if (!pGear->Touched)
  	{
  		*(UByte*)pAnim = Min;
  		return;
  	}
  
	FP fVal = pGear->LegPos * 255;
  	SLong val = (int)fVal;//(pGear->IntL) * 255;
  	MODMAXMIN(val, Min, Max);
  
  	*(UByte*)pAnim = (UByte)val;
}

//static	int	poop;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcAnimSurface
//Author		Andrew McRae
//Date			Wed 2 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ModelAnim::ProcAnimSurface ()
{
	SLong num = (SLong)*(SWord*)pSrce;
	num = (255 * num) / Scale;

	*(UByte*)pAnim = num;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcAnimGenericFP
//Author		Andrew McRae
//Date			Mon 29 Sep 1997
//
//Description							 drag
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ModelAnim::ProcAnimGenericFP ()
{
	SLong val = (*(SWordP)pSrce);

	if(Scale > 0)
		*(UWord*)pAnim = (255 * val) / Scale;
	else
		*(UWord*)pAnim = 255 + (255 * val) / Scale;

//DEADCODE CSB 29/02/00 	if(Scale > 0)
//DEADCODE CSB 29/02/00 		*(UWord*)pAnim = (val * Scale)>>16;
//DEADCODE CSB 29/02/00 	else
//DEADCODE CSB 29/02/00 		*(UWord*)pAnim = 255 + ((val * Scale)>>16);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Animations
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	animation functions
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Model::Animations (AirStrucPtr const ControlledAC, bool forced)
{
	if (this)														//RJS 24Mar00
		if(		(	(ControlledAC == Persons2::PlayerSeenAC)
				&&	(ControlledAC->classtype->aerobaticfactor != AEROBATIC_LOW)
				&&	(!ControlledAC->Status.deadtime)	)
			||	(	(ControlledAC->movecode == AUTO_COMBAT)
				&&	(!ControlledAC->ai.simpleacm)	)
			||	(ControlledAC->movecode == AUTO_FOLLOWTHELEADER)
			||	(forced)	)
		{
			PMODELANIM pModelAnim = AnimList;

			while (pModelAnim != NULL)
			{
				pModelAnim->pAnim = (void*)&ControlledAC->Anim[(int)pModelAnim->pOffset];//(pModelAnim->pOffset + (ULong)(ControlledAC->Anim));
				switch (pModelAnim->Type)
				{
					case MA_SURFACE:
						pModelAnim->pSrce = (void*)(pModelAnim->pSrcOffset + (ULong)ControlledAC);//RJS 20Jul98

					case MA_AEROSURFACE:											//RJS 20Jul98
						pModelAnim->ProcAnimSurface ();
						break;

					case MA_SUSPENSION:
						pModelAnim->ProcAnimSuspension ();
						break;

					case MA_GENERICFP:
						if(pModelAnim->pSrcOffset >= 0)
							pModelAnim->pSrce = (void*)(pModelAnim->pSrcOffset + (ULong)ControlledAC);//RDH 10Sep98
						pModelAnim->ProcAnimGenericFP ();
						break;
				}
				pModelAnim = pModelAnim->List.NextItem ();
			}


		}

//DeadCode RJS 27Mar00 //#define PRINT_ANIM_VALS
//DeadCode RJS 27Mar00 #ifdef PRINT_ANIM_VALS
//DeadCode RJS 27Mar00 SWord y = 15;
//DeadCode RJS 27Mar00 pModelAnim = AnimList;
//DeadCode RJS 27Mar00 while (pModelAnim != NULL)
//DeadCode RJS 27Mar00 {
//DeadCode RJS 27Mar00 	if((pModelAnim->Type == MA_SURFACE) || (pModelAnim->Type == MA_GENERICFP))
//DeadCode RJS 27Mar00 	{
//DeadCode RJS 27Mar00 		PrintVar(40, y, "%.0f ", FP(*(SWord*)pModelAnim->pSrce));
//DeadCode RJS 27Mar00 		PrintVar(50, y, "%.0f ", FP(*(SWord*)pModelAnim->pAnim));
//DeadCode RJS 27Mar00 		y++;
//DeadCode RJS 27Mar00 	}
//DeadCode RJS 27Mar00 	pModelAnim = pModelAnim->List.NextItem ();
//DeadCode RJS 27Mar00 }
//DeadCode RJS 27Mar00 #endif
//DeadCode RJS 27Mar00 
//DeadCode RJS 27Mar00 	// Gear Up/Down
//DeadCode RJS 27Mar00 
//DeadCode RJS 27Mar00 //Deadcode CSB 13/01/00		if (Gear)
//DeadCode RJS 27Mar00 //Deadcode CSB 13/01/00			SetGearAnimPos(ControlledAC,ANIM_GEAR_AUTO);							//RJS 08Apr98
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGearAnimPos
//Author		Robert Slater
//Date			Wed 8 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Model::SetGearAnimPos(AirStrucPtr const ControlledAC,SWord	val,Bool	killnow)
{
	SWord desval = 0;	//gear down

	if(val == ANIM_GEAR_UP)
		desval = 255;

	if(ControlledAC->fly.numinsag)
	{
	}
	else
	{	
		AircraftAnimData* adptr = (AircraftAnimData*)ControlledAC->Anim;

		adptr->acleglowerb = desval;
		adptr->acleglowerf = desval;
		adptr->acleglowerl = desval;
		adptr->acleglowerr = desval;
	}

#pragma warnmsg("***** SetGearAnimPos	DEADED *****")
//DEADCODE CSB 24/02/00 // not for superairgroups...
//DEADCODE CSB 24/02/00 	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ControlledAC->shape);//RJS 27Jan00
//DEADCODE CSB 24/02/00 	if (SHAPESTUFF.GetShapeScale(sdptr) != SHP_GRP)					//RJS 27Jan00
//DEADCODE CSB 24/02/00 	{
//DEADCODE CSB 24/02/00 		AircraftAnimData* adptr = (AircraftAnimData* )ControlledAC->Anim;
//DEADCODE CSB 24/02/00 		SLong	geardamage = 0;										//RJS 07Sep98
//DEADCODE CSB 24/02/00 
//DEADCODE CSB 24/02/00 		if (killnow==TRUE)											//RJS 07Sep98
//DEADCODE CSB 24/02/00 			adptr->animtoggle = 1;									//RJS 07Sep98
//DEADCODE CSB 24/02/00 		else			
//DEADCODE CSB 24/02/00 			geardamage = (adptr->LEFTWHEEL + adptr->RIGHTWHEEL)>>1;	//RJS 17Nov99
//DEADCODE CSB 24/02/00 	//DeadCode RJS 17/11/99		geardamage = (adptr->LEFTWHEEL + adptr->RIGHTWHEEL + adptr->FRONTWHEEL + adptr->BACKWHEEL)/4;//RJS 07Sep98
//DEADCODE CSB 24/02/00 			geardamage = (adptr->LEFTWHEEL + adptr->RIGHTWHEEL) / 2;//RJS 07Sep98
//DEADCODE CSB 24/02/00 														
//DEADCODE CSB 24/02/00 		if (geardamage < BS_DAMLV2)									//RJS 07Sep98
//DEADCODE CSB 24/02/00 		{
//DEADCODE CSB 24/02/00 	//	_DPlay.NewCollision(NULL,NULL,PIDC_ACTION,ACTION_GEAR);
//DEADCODE CSB 24/02/00 
//DEADCODE CSB 24/02/00 //DeadCode AMM 21Feb100 			if (_Replay.Record || _DPlay.Implemented)
//DEADCODE CSB 24/02/00 //DeadCode AMM 21Feb100 			{
//DEADCODE CSB 24/02/00 //DeadCode AMM 21Feb100 				if (ControlledAC==Persons2::PlayerSeenAC)				  //AMM 23/06/99
//DEADCODE CSB 24/02/00 //DeadCode AMM 21Feb100 					_DPlay.NewGearThingy(val);
//DEADCODE CSB 24/02/00 //DeadCode AMM 21Feb100 			}
//DEADCODE CSB 24/02/00 
//DEADCODE CSB 24/02/00 			if (val < ANIM_GEAR_DOWN)
//DEADCODE CSB 24/02/00 			{
//DEADCODE CSB 24/02/00 				if(ControlledAC == Manual_Pilot.ControlledAC2)
//DEADCODE CSB 24/02/00 				{
//DEADCODE CSB 24/02/00 					if (EngineList->Type == ET_PISTON)
//DEADCODE CSB 24/02/00 						_Miles.PlayOnce(FIL_SFX_GEAR_P51,ControlledAC);		
//DEADCODE CSB 24/02/00 					else
//DEADCODE CSB 24/02/00 						_Miles.PlayOnce(FIL_SFX_GEAR_JET,ControlledAC);		
//DEADCODE CSB 24/02/00 				}
//DEADCODE CSB 24/02/00 
//DEADCODE CSB 24/02/00 				if (adptr->animtoggle)									
//DEADCODE CSB 24/02/00 					adptr->animtoggle = -adptr->animtoggle;				
//DEADCODE CSB 24/02/00 				else													
//DEADCODE CSB 24/02/00 					adptr->animtoggle = 1;								
//DEADCODE CSB 24/02/00 			}
//DEADCODE CSB 24/02/00 			else
//DEADCODE CSB 24/02/00 			{
//DEADCODE CSB 24/02/00 				if (val == ANIM_GEAR_DOWN)
//DEADCODE CSB 24/02/00 					adptr->animtoggle = -1;
//DEADCODE CSB 24/02/00 				else
//DEADCODE CSB 24/02/00 					adptr->animtoggle = 1;
//DEADCODE CSB 24/02/00 
//DEADCODE CSB 24/02/00 				adptr->acleglowerf = val;
//DEADCODE CSB 24/02/00 				adptr->acleglowerl = val;
//DEADCODE CSB 24/02/00 				adptr->acleglowerr = val;
//DEADCODE CSB 24/02/00 				adptr->acleglowerb = val;
//DEADCODE CSB 24/02/00 			}
//DEADCODE CSB 24/02/00 		}
//DEADCODE CSB 24/02/00 	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetInstruments
//Author		Andrew McRae
//Date			Wed 27 Aug 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void INSTRUMENTS::SetInstruments (AirStrucPtr const ControlledAC,PMODEL pModel)
{
	PAERODEVICE pDevice;										//RJS 14Dec99

	FP fuelcont = 255.0 * FP(ControlledAC->fly.fuel_content[FuelGuageTank[C_FuelGuageSelector]]) / FP(FuelGuageScale[C_FuelGuageSelector]);
	MODMAXMIN(fuelcont, 0, 255);
	I_FuelContents = UWord(fuelcont);

	switch(pModel->Type)
	{
		case AT_SPITFIRE:
		{
			I_TrueGroundSpeed = pModel->Speed;	// m/s
			I_TrueAirSpeed = pModel->AirSpeed / 0.44704;	//mph
			I_IndicatedAirSpeed = FSqrt(pModel->AmbDensity / 0.0001225) * I_TrueAirSpeed;
			I_PitchAngle = pModel->fPitch;
			I_RollAngle = pModel->fRoll;
			I_RateOfClimb = pModel->Vel.y * 3.2808 * 60.0;	//ft/min
			SLong TempGroundAlt = 0;
			if(ControlledAC->ai.homebase)
				TempGroundAlt = ControlledAC->ai.homebase->World.Y;
			I_Altitude = 0.032808 * (pModel->Pos.y - TempGroundAlt);	// feet

			I_Turn = (pModel->fHdg * 57.3 - I_Heading) / MODEL_DT * 100.0;	//RJS 14Dec99
			MODLIMIT(I_Turn, 4);//0.349 * 1043038);

			FP temp = 0;
			if(pModel->AirVel.z != 0)	temp = pModel->AirVel.x / pModel->AirVel.z * 57.3;
			MODLIMIT(temp, 20);
			I_Slip = (1.0 * I_Slip + temp) / 2.0;

			I_Heading = pModel->fHdg * 57.3;

			bool GearUp = true;
			bool GearDown = true;
			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_GEAR)
				{
					if(pDevice->Val != 0x0000)	GearUp = false;
					if(pDevice->Val != 0x4000)	GearDown = false;
				}
			I_UndercarraigePosition0 = 0;				//Red OFF,	Green OFF
			if(GearUp)	 I_UndercarraigePosition0 = 1;	//Red ON,	Green OFF
			if(GearDown) I_UndercarraigePosition0 = 2;	//Red OFF,	Green ON

			I_ElevatorTrimTab = 32767.0 * FP(pModel->ElevatorTrim) / FP(pModel->MaxElevatorTrim);

//Some engine instruments to go in here
			I_EngineRpm0 = pModel->EngineList->Speed * 954.93;
			I_Boost0 = pModel->EngineList->ThrottleSetting * I_EngineRpm0 * (6.25 / (90.0 * 3000.0));;

			I_VoltMeter = 12.0;
			if(I_EngineRpm0 > 500)
			{
				if(I_EngineRpm0 > 1000)
					I_VoltMeter = 18.0;
				else
					I_VoltMeter = 12.0 + 6.0 * (I_EngineRpm0 - 500.0) / 500.0;
			}

			I_NormalAcc = pModel->Acc.y / GRAVITY + pModel->Ori.y.y;
			

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_CANOPY)
				{	C_HoodCatch = (pDevice->Val > 0);	break;	}

			if(pModel->EmergencyGearUsed)
				C_EmergencyUndercarraige = 1;
			else
				C_EmergencyUndercarraige = 0;

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_FLAPS)
				{	C_FlapLever = pDevice->ReqVal;	break;	}

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey != NULLKEY))
				{	C_UndercarraigeLever = 1 - pDevice->ReqVal;	break;	}

			C_ElevatorTrim = I_ElevatorTrimTab;
			C_RudderTrim = 32767.0 * pModel->RudderTrim / pModel->MaxRudderTrim;

			C_Throttle0 = pModel->EngineList->ThrottleSetting;	//RJS 01Dec99
			C_PropPitch0 = pModel->EngineList->PropSetting * 100.0;		//RJS 01Dec99

			I_FuelPressure = 100;
			AircraftAnimData* adptr = (AircraftAnimData*) ControlledAC->Anim;
			I_OilPressure = 128 - adptr->ENGINELEFT / 2;
			if(I_EngineRpm0 < 400)
				I_OilPressure = I_OilPressure * I_EngineRpm0 / 400.0;

			I_OilTemperature = pModel->EngineList->Temperature;
			I_RadiatorTemperature0 = pModel->EngineList->Temperature;

			switch(pModel->EngineList->Magnetos)
			{
				case 0:		C_Magnetos0 = 3;	break;
				case 1:		C_Magnetos0 = 2;	break;
				case 2:		C_Magnetos0 = 1;	break;
				case 3:		C_Magnetos0 = 0;	break;
			}

//DeadCode AMM 24Jul00 			switch(pModel->FuelCockPos)
			switch(ControlledAC->fly.FuelCockPos)
			{
				case 0:		C_FuelCock0 = 3;	break;
				case 1:		C_FuelCock0 = 2;	break;
				case 2:		C_FuelCock0 = 1;	break;
				case 3:		C_FuelCock0 = 0;	break;
			}
  
			C_StarterButton0 = SWord(pModel->EngineList->Starting);

			if(ControlledAC == Persons2::PlayerSeenAC)
			{
				if((C_Throttle0 < 25) && (I_UndercarraigePosition0 != 2) && (Save_Data.flightdifficulty[FD_SPINS]))	//Throttled back and gear not down
					_Miles.PlayOnce(FIL_SFX_HORN_THROTTLE, 32);
				else
					_Miles.PlayOnce(FIL_SFX_HORN_THROTTLE, 0);
			}

			break;
		}

		case AT_HURRICANE:
		{
			I_TrueGroundSpeed = pModel->Speed;	// m/s
			I_TrueAirSpeed = ControlledAC->vel_ * (0.0001 / 0.44704);	//mph
			I_IndicatedAirSpeed = FSqrt(pModel->AmbDensity / 0.0001225) * I_TrueAirSpeed;
			I_RateOfClimb = pModel->Vel.y * 3.2808 * 60.0;	//ft/min
			I_PitchAngle = pModel->fPitch;
			I_RollAngle = pModel->fRoll;
			SLong TempGroundAlt = 0;
			if(ControlledAC->ai.homebase)
				TempGroundAlt = ControlledAC->ai.homebase->World.Y;
			I_Altitude = 0.032808 * (pModel->Pos.y - TempGroundAlt);	// feet

			I_Turn = (pModel->fHdg * 57.3 - I_Heading) / MODEL_DT * 100.0;	//RJS 14Dec99
			MODLIMIT(I_Turn, 4);//0.349 * 1043038);

			FP temp = 0;
			if(pModel->AirVel.z != 0)	temp = pModel->AirVel.x / pModel->AirVel.z * 57.3;
			MODLIMIT(temp, 20);
			I_Slip = (1.0 * I_Slip + temp) / 2.0;

			I_Heading = pModel->fHdg * 57.3;

			
			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey != NULLKEY))
					break;

			I_UndercarraigePosition0 = 0;								//Red OFF,	Green OFF
			if(pDevice->Val == 0x0000)	I_UndercarraigePosition0 = 1;	//Red ON,	Green OFF
			if(pDevice->Val == 0x4000)	I_UndercarraigePosition0 = 2;	//Red OFF,	Green ON

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey == NULLKEY))
					break;

			I_UndercarraigePosition1 = 0;								//Red OFF,	Green OFF
			if(pDevice->Val == 0x0000)	I_UndercarraigePosition1 = 1;	//Red ON,	Green OFF
			if(pDevice->Val == 0x4000)	I_UndercarraigePosition1 = 2;	//Red OFF,	Green ON

//Some engine instruments to go in here
			I_EngineRpm0 = pModel->EngineList->Speed * 954.93;
			I_Boost0 = pModel->EngineList->ThrottleSetting * I_EngineRpm0 * (6.25 / (90.0 * 3000.0));;

			I_VoltMeter = 12.0;
			if(I_EngineRpm0 > 500)
			{
				if(I_EngineRpm0 > 1000)
					I_VoltMeter = 18.0;
				else
					I_VoltMeter = 12.0 + 6.0 * (I_EngineRpm0 - 500.0) / 500.0;
			}
			
			I_NormalAcc = pModel->Acc.y / GRAVITY + pModel->Ori.y.y;

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_CANOPY)
				{	C_HoodCatch = (pDevice->Val > 0);	break;	}

			if(pModel->EmergencyGearUsed)
				C_EmergencyUndercarraige = 1;
			else
				C_EmergencyUndercarraige = 0;

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_FLAPS)
				{	
					I_FlapsIndicator = pDevice->Val;
					C_FlapLever = 0;
					if(pDevice->Attractor > pDevice->Val)	C_FlapLever = 1;
					if(pDevice->Attractor < pDevice->Val)	C_FlapLever = -1;
					break;
				}

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey != NULLKEY))
				{	
					C_UndercarraigeLever = 0;
					if(pDevice->Attractor > pDevice->Val)	C_UndercarraigeLever = 1;
					if(pDevice->Attractor < pDevice->Val)	C_UndercarraigeLever = -1;
					break;
				}

			C_H_Gate = 0;
			if(C_FlapLever == -1)			C_H_Gate = 3;
			if(C_FlapLever == 1)			C_H_Gate = 4;
			if(C_UndercarraigeLever == -1)	C_H_Gate = 2;
			if(C_UndercarraigeLever == 1)	C_H_Gate = 1;

			C_ElevatorTrim = 32767.0 * FP(pModel->ElevatorTrim) / FP(pModel->MaxElevatorTrim);
			C_RudderTrim   = 32767.0 * pModel->RudderTrim / pModel->MaxRudderTrim;

			C_Throttle0 = pModel->EngineList->ThrottleSetting;	//RJS 01Dec99
			C_PropPitch0 = pModel->EngineList->PropSetting * 100.0;		//RJS 01Dec99

			I_FuelPressure = 100;
			AircraftAnimData* adptr = (AircraftAnimData*) ControlledAC->Anim;
			I_OilPressure = 128 - adptr->ENGINELEFT / 2;
			if(I_EngineRpm0 < 400)
				I_OilPressure = I_OilPressure * I_EngineRpm0 / 400.0;

			I_OilTemperature = pModel->EngineList->Temperature;
			I_RadiatorTemperature0 = pModel->EngineList->Temperature;

			C_Magnetos0 = 3 - pModel->EngineList->Magnetos;
			C_StarterButton0 = SWord(pModel->EngineList->Starting);
			C_BoostControlCutout = SWord(pModel->BoostCutout);

//DeadCode AMM 24Jul00 			switch(pModel->FuelCockPos)
			switch(ControlledAC->fly.FuelCockPos)
			{
				case 0:		C_FuelCock0 = 0;	break;
				case 1:		C_FuelCock0 = 1;	break;
				case 2:		C_FuelCock0 = 2;	break;
			}

			break;
		}

		case AT_BF109:
		{
			I_TrueGroundSpeed = pModel->Speed;	// m/s
			I_TrueAirSpeed = ControlledAC->vel_ * (0.0001 * 3.6);	//kmph
			I_IndicatedAirSpeed = FSqrt(pModel->AmbDensity / 0.0001225) * I_TrueAirSpeed;
			I_PitchAngle = pModel->fPitch;
			I_RollAngle = pModel->fRoll;
			SLong TempGroundAlt = 0;
			if(ControlledAC->ai.homebase)
				TempGroundAlt = ControlledAC->ai.homebase->World.Y;
			I_Altitude = 0.01 * (pModel->Pos.y - TempGroundAlt);	// metres

			I_Turn = (pModel->fHdg * 57.3 - I_Heading) / MODEL_DT * 100.0;	//RJS 14Dec99
			MODLIMIT(I_Turn, 4);//0.349 * 1043038);

			FP temp = 0;
			if(pModel->AirVel.z != 0)	temp = pModel->AirVel.x / pModel->AirVel.z * 57.3;
			MODLIMIT(temp, 20);
			I_Slip = (1.0 * I_Slip + temp) / 2.0;

			I_Heading = pModel->fHdg * 57.3;

			
			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey != NULLKEY))
					break;

			I_UndercarraigePosition0 = 0;								//Red OFF,	Green OFF
			if(pDevice->Val == 0x0000)	I_UndercarraigePosition0 = 1;	//Red ON,	Green OFF
			if(pDevice->Val == 0x4000)	I_UndercarraigePosition0 = 2;	//Red OFF,	Green ON
			I_MechanicalUndercarraigeIndicator = pDevice->Val / 2;


			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey == NULLKEY))
					break;

			I_UndercarraigePosition1 = 0;								//Red OFF,	Green OFF
			if(pDevice->Val == 0x0000)	I_UndercarraigePosition1 = 1;	//Red ON,	Green OFF
			if(pDevice->Val == 0x4000)	I_UndercarraigePosition1 = 2;	//Red OFF,	Green ON
			I_MechanicalUndercarraigeIndicator += pDevice->Val / 2;


			if(ControlledAC->fly.fuel_content[0] < ControlledAC->classtype->fueltankcap[0] * (1000 / 10))
				I_FuelWarningLamp0 = 1;
			else
				I_FuelWarningLamp0 = 0;

//Some engine instruments to go in here
			I_EngineRpm0 = pModel->EngineList->Speed * 954.93;
			I_Boost0 = 1 + pModel->EngineList->ThrottleSetting * I_EngineRpm0 * (0.4 / (90.0 * 2400.0));;
//DeadCode RJS 10Jul00 			I_PropPitch0 = pModel->EngineList->PropInc - pModel->EngineList->PropMinPitch;
//DeadCode RJS 10Jul00 			I_PropPitch0 /= pModel->EngineList->PropMaxPitch - pModel->EngineList->PropMinPitch;
			
			I_NormalAcc = pModel->Acc.y / GRAVITY + pModel->Ori.y.y;

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_CANOPY)
				{	C_HoodCatch = pDevice->ReqVal;	break;	}

			if(pModel->EmergencyGearUsed)
				C_EmergencyUndercarraige = 1;
			else
				C_EmergencyUndercarraige = 0;

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_FLAPS)
				{	C_FlapLever = pDevice->Val;		break;	}

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey != NULLKEY))
				{
					C_UndercarraigeLever = pDevice->ReqVal;
					I_MechanicalUndercarraigeIndicator = (pDevice->Val + pDevice->List.NextItem()->Val) / 256;
					break;
				}

			C_ElevatorTrim = 32767.0 * FP(pModel->ElevatorTrim) / FP(pModel->MaxElevatorTrim);

			C_Throttle0 = pModel->EngineList->ThrottleSetting;	//RJS 01Dec99
			C_PropPitch0 = pModel->EngineList->PropSetting * 100.0;		//RJS 01Dec99

			I_PropPitch0 = pModel->EngineList->PropInc * 57.3 - 35.0;

			I_FuelPressure = 100;
			AircraftAnimData* adptr = (AircraftAnimData*) ControlledAC->Anim;
			I_OilPressure = 128 - adptr->ENGINELEFT / 2;
			if(I_EngineRpm0 < 400)
				I_OilPressure = I_OilPressure * I_EngineRpm0 / 400.0;

			I_OilTemperature = pModel->EngineList->Temperature;
			I_RadiatorTemperature0 = pModel->EngineList->Temperature;

			C_Magnetos0 = pModel->EngineList->Magnetos;
			C_StarterButton0 = SWord(pModel->EngineList->Starting);
			C_BoostControlCutout = SWord(pModel->BoostCutout);
//DeadCode AMM 24Jul00 			C_FuelCock0 = SWord(pModel->FuelCockPos);
			C_FuelCock0 = SWord(ControlledAC->fly.FuelCockPos);

			break;
		}

		case AT_BF110:
		{
			I_TrueGroundSpeed = pModel->Speed;	// m/s
			I_TrueAirSpeed = ControlledAC->vel_ * (0.0001 * 3.6);	//kmph
			I_IndicatedAirSpeed = FSqrt(pModel->AmbDensity / 0.0001225) * I_TrueAirSpeed;
			I_RateOfClimb = pModel->Vel.y * 60.0;	//m/min
			I_PitchAngle = pModel->fPitch;
			I_RollAngle = pModel->fRoll;
			SLong TempGroundAlt = 0;
			if(ControlledAC->ai.homebase)
				TempGroundAlt = ControlledAC->ai.homebase->World.Y;
			I_Altitude = 0.01 * (pModel->Pos.y - TempGroundAlt);	// metres

			I_Turn = (pModel->fHdg * 57.3 - I_Heading) / MODEL_DT * 100.0;	//RJS 14Dec99
			MODLIMIT(I_Turn, 4);//0.349 * 1043038);

			FP temp = 0;
			if(pModel->AirVel.z != 0)	temp = pModel->AirVel.x / pModel->AirVel.z * 57.3;
			MODLIMIT(temp, 20);
			I_Slip = (1.0 * I_Slip + temp) / 2.0;

			I_Heading = pModel->fHdg * 57.3;
			
			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey != NULLKEY))
					break;

			I_UndercarraigePosition0 = 0;								//Red OFF,	Green OFF
			if(pDevice->Val == 0x0000)	I_UndercarraigePosition0 = 1;	//Red ON,	Green OFF
			if(pDevice->Val == 0x4000)	I_UndercarraigePosition0 = 2;	//Red OFF,	Green ON

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey == NULLKEY))
					break;

			I_UndercarraigePosition1 = 0;								//Red OFF,	Green OFF
			if(pDevice->Val == 0x0000)	I_UndercarraigePosition1 = 1;	//Red ON,	Green OFF
			if(pDevice->Val == 0x4000)	I_UndercarraigePosition1 = 2;	//Red OFF,	Green ON

			if(ControlledAC->fly.fuel_content[0] < ControlledAC->classtype->fueltankcap[0] * (1000 / 10))
				I_FuelWarningLamp0 = 1;
			else
				I_FuelWarningLamp0 = 0;
			if(ControlledAC->fly.fuel_content[1] < ControlledAC->classtype->fueltankcap[1] * (1000 / 10))
				I_FuelWarningLamp1 = 1;
			else
				I_FuelWarningLamp1 = 0;
			if(ControlledAC->fly.fuel_content[2] < ControlledAC->classtype->fueltankcap[2] * (1000 / 10))
				I_FuelWarningLamp2 = 1;
			else
				I_FuelWarningLamp2 = 0;
			if(ControlledAC->fly.fuel_content[3] < ControlledAC->classtype->fueltankcap[3] * (1000 / 10))
				I_FuelWarningLamp3 = 1;
			else
				I_FuelWarningLamp3 = 0;

			I_NormalAcc = pModel->Acc.y / GRAVITY + pModel->Ori.y.y;

//Some engine instruments to go in here
			PENGINE pEngine = pModel->EngineList;
			I_EngineRpm0 = pEngine->Speed * 954.93;
			I_Boost0 = 1 + pEngine->ThrottleSetting * I_EngineRpm0 * (0.4 / (90.0 * 2400.0));;
			I_PropPitch0 = pEngine->PropInc * 57.3 - 35.0;
//DeadCode RJS 10Jul00 			I_PropPitch0 = pEngine->PropInc - pEngine->PropMinPitch;
//DeadCode RJS 10Jul00 			I_PropPitch0 /= pEngine->PropMaxPitch - pEngine->PropMinPitch;
			C_Throttle0 = pEngine->ThrottleSetting;
			C_PropPitch0 = pEngine->PropSetting * 100.0;	
			I_RadiatorTemperature0 = pEngine->Temperature;
			C_Magnetos0 = pEngine->Magnetos;
			C_StarterButton0 = SWord(pEngine->Starting);

			pEngine = pModel->EngineList->List.NextItem();
			I_EngineRpm1 = pEngine->Speed * 954.93;
			I_Boost1 = 1 + pEngine->ThrottleSetting * I_EngineRpm1 * (0.4 / (90.0 * 2400.0));;//RJS 05Jul00
			I_PropPitch1 = pEngine->PropInc * 57.3 - 35.0;
//DeadCode RJS 10Jul00 			I_PropPitch1 = pEngine->PropInc - pEngine->PropMinPitch;
//DeadCode RJS 10Jul00 			I_PropPitch1 /= pEngine->PropMaxPitch - pEngine->PropMinPitch;
			C_Throttle1 = pEngine->ThrottleSetting;
			C_PropPitch1 = pEngine->PropSetting * 100.0;	
			I_RadiatorTemperature1 = pEngine->Temperature;
			C_Magnetos1 = pEngine->Magnetos;
			C_StarterButton1 = SWord(pEngine->Starting);

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_CANOPY)
				{	C_HoodCatch = pDevice->ReqVal;	break;	}

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if((pDevice->Type == AeroDevice::DT_GEAR) && (pDevice->UpKey != NULLKEY))
				{	
					if(pModel->EmergencyGearUsed)
					{
						C_UndercarraigeLever = 0;
						if(pDevice->Attractor > pDevice->Val)	C_EmergencyUndercarraige = 1;
						if(pDevice->Attractor < pDevice->Val)	C_EmergencyUndercarraige = 2;
					}
					else
					{
						C_UndercarraigeLever = 0;
						if(pDevice->Attractor > pDevice->Val)	C_UndercarraigeLever = 1;
						if(pDevice->Attractor < pDevice->Val)	C_UndercarraigeLever = 2;
					}
					break;
				}

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_FLAPS)
					{
						C_FlapLever = 0;
						if(pDevice->Attractor > pDevice->Val)	C_FlapLever = 1;
						if(pDevice->Attractor < pDevice->Val)	C_FlapLever = 2;
						break;
					}

			C_ElevatorTrim = 32767.0 * FP(pModel->ElevatorTrim) / FP(pModel->MaxElevatorTrim);
			C_RudderTrim   = 32767.0 * FP(pModel->RudderTrim)   / FP(pModel->MaxRudderTrim);

//DeadCode AMM 24Jul00 			switch(pModel->FuelCockPos)
			switch(ControlledAC->fly.FuelCockPos)
			{
				case 0:		C_FuelCock0 = 0;	C_FuelCock1 = 0;	break;
				case 1:		C_FuelCock0 = 1;	C_FuelCock1 = 0;	break;
				case 2:		C_FuelCock0 = 0;	C_FuelCock1 = 1;	break;
				case 3:		C_FuelCock0 = 1;	C_FuelCock1 = 1;	break;
			}
			break;
		}

		case AT_JU87B:
		{
			SLong TempGroundAlt = 0;
			if(ControlledAC->ai.homebase)
				TempGroundAlt = ControlledAC->ai.homebase->World.Y;
			I_Altitude = 0.01 * (pModel->Pos.y - TempGroundAlt);	// feet

			COORDS3D AcPos;
			AcPos.X = ControlledAC->World.X;
			if(ControlledAC->World.Y > 5000)
				AcPos.Y = ControlledAC->World.Y - 5000;
			else AcPos.Y = 0;
			AcPos.Z = ControlledAC->World.Z;
			TempGroundAlt = _Collide.GroundAltitude(AcPos);
			I_RadioAltitude = 0.01 * (pModel->Pos.y - TempGroundAlt);

			I_Turn = (pModel->fHdg * 57.3 - I_Heading) / MODEL_DT * 100.0;	//RJS 14Dec99
			MODLIMIT(I_Turn, 4);//0.349 * 1043038);

			FP temp = 0;
			if(pModel->AirVel.z != 0)	temp = pModel->AirVel.x / pModel->AirVel.z * 57.3;
			MODLIMIT(temp, 20);
			I_Slip = (1.0 * I_Slip + temp) / 2.0;

			I_Heading = pModel->fHdg * 57.3;
			I_PitchAngle = pModel->fPitch;
			I_RollAngle = pModel->fRoll;
			
			I_TrueGroundSpeed = pModel->Speed;	// m/s
			I_TrueAirSpeed = ControlledAC->vel_ * (0.0001 * 3.6);	//kmph
			I_IndicatedAirSpeed = FSqrt(pModel->AmbDensity / 0.0001225) * I_TrueAirSpeed;
			I_RateOfClimb = pModel->Vel.y;	//m/s

			I_EngineRpm0 = pModel->EngineList->Speed * 954.93;
			I_Boost0 = 1 + pModel->EngineList->ThrottleSetting * I_EngineRpm0 * (0.3 / (90.0 * 2400.0));;

			if(ControlledAC->fly.fuel_content[0] < ControlledAC->classtype->fueltankcap[0] * (1000 / 10))
				I_FuelWarningLamp0 = 1;
			else
				I_FuelWarningLamp0 = 0;
			if(ControlledAC->fly.fuel_content[1] < ControlledAC->classtype->fueltankcap[1] * (1000 / 10))
				I_FuelWarningLamp1 = 1;
			else
				I_FuelWarningLamp1 = 0;

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_FLAPS)
				{	C_FlapLever = 3 - pDevice->ReqVal;	break;	}

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_CANOPY)
				{	C_HoodCatch = (pDevice->Val > 0);	break;	}

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_DIVEBRAKES)
				{
					C_DiveBrakeLever = 1 - pDevice->ReqVal;
//DeadCode CSB 19Sep00 					if((pDevice->ReqVal > 0) && (I_RadioAltitude > 2300) && (I_RadioAltitude < 4300))
					if (ControlledAC == Persons2::PlayerSeenAC)			//RJS 25Oct00
					{
						if((pDevice->ReqVal > 0) && (I_RadioAltitude > 700) && (I_RadioAltitude < 1300))
							_Miles.PlayOnce(FIL_SFX_HORN_ALTITUDE, 255);
						else
							_Miles.PlayOnce(FIL_SFX_HORN_ALTITUDE, 0);

						if(pDevice->ReqVal == 1)							//RJS 25Oct00
							_Miles.diveBrakesOn = true;						//RJS 25Oct00
						else												//RJS 25Oct00
							_Miles.diveBrakesOn = false;					//RJS 25Oct00
					}
//DeadCode RJS 25Oct00 
//DeadCode RJS 25Oct00 					if(pDevice->ReqVal == 1)
//DeadCode RJS 25Oct00 						_Miles.PlayOnce(FIL_SFX_SIREN_JERICHO, 255);
//DeadCode RJS 25Oct00 					else
//DeadCode RJS 25Oct00 						_Miles.PlayOnce(FIL_SFX_SIREN_JERICHO, 0);
				}

			I_NormalAcc = pModel->Acc.y / GRAVITY + pModel->Ori.y.y;

			for(pDevice = pModel->DeviceList; pDevice; pDevice = pDevice->List.NextItem())
				if(pDevice->Type == AeroDevice::DT_CANOPY)
				{	C_HoodCatch = pDevice->ReqVal;	break;	}

			C_ElevatorTrim = 32767.0 * pModel->ElevatorTrim / pModel->MaxElevatorTrim;

			C_Throttle0 = pModel->EngineList->ThrottleSetting;	//RJS 01Dec99
			C_PropPitch0 = pModel->EngineList->PropSetting * 100.0;		//RJS 01Dec99

			I_FuelPressure = 0;
//DEADCODE CSB 13/01/00 			I_DivePresetIndicator = 0;

			I_RadiatorTemperature0 = pModel->EngineList->Temperature;
			I_OilTemperature = pModel->EngineList->Temperature;
			AircraftAnimData* adptr = (AircraftAnimData*) ControlledAC->Anim;
			I_OilContent = 128 - adptr->ENGINELEFT / 2;

			C_Magnetos0 = 3 - pModel->EngineList->Magnetos;
//DeadCode AMM 24Jul00 			C_FuelCock0	= pModel->FuelCockPos & 0x01;
//DeadCode AMM 24Jul00 			C_FuelCock1 = pModel->FuelCockPos & 0x02;
			C_FuelCock0	= ControlledAC->fly.FuelCockPos & 0x01;
			C_FuelCock1 = ControlledAC->fly.FuelCockPos & 0x02;
			C_StarterButton0 = SWord(pModel->EngineList->Starting);
			C_BoostControlCutout = SWord(pModel->BoostCutout);

			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EngineDamage
//Author		Robert Slater
//Date			Fri 13 Feb 1998
//
//Description	
//
//Inputs		Animation Data ptr,  number of engines
//
//Returns		Total engine damage 0 - 255 (DEAD)
//
//------------------------------------------------------------------------------
SLong	INSTRUMENTS::EngineDamage(UByteP	animptr, int  noengines)
{
	PolyPitAnimData*	adptr = (PolyPitAnimData*) animptr;
	SLong				total = 0;

	total += adptr->ENGINELEFT;									//RJS 17Nov99
	total += adptr->ENGINERIGHT;								//RJS 17Nov99

	total /= noengines;

	return(total);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTimedAnim
//Author		Robert Slater
//Date			Fri 13 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong INSTRUMENTS::SetTimedAnim (SLong	&SrcVal, UWord  &TimerCount, SLong Desired, UWord timeup, UWord timedown)
{
	SLong	scaled;
	SLong	gap;

	gap = Desired - SrcVal;
	if (gap)
	{
		if (gap > 0)
		{
			scaled = (TimerCount * gap) / timeup;
			if (scaled > gap)
			{
				scaled = 0;
				SrcVal = Desired;
			}
		}
		else
		{
			scaled = (TimerCount * gap) / timedown;
			if (scaled < gap)
			{
				scaled = 0;
				SrcVal = Desired;
			}
		}
	}
	else
	{
		TimerCount = 0;
		scaled = 0;
		SrcVal = Desired;
	}

	return(scaled);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetCockpitAnims
//Author		Robert Slater
//Date			Mon 16 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::SetCockpitAnims(ItemPtr	itm, UByteP	animptr)
{
	PolyPitAnimData*	adptr = (PolyPitAnimData*) animptr;
	SLong				scaled, scaled2, TotalEngineDamage, animstep;
	SLong				index;

	for (index = 0; index < DialCnt; index++)
		DialList[index].SetDialValue(itm, animptr,(UByteP*)DialSrcList);

	//Red OFF,	Green OFF	0
	//Red ON,	Green OFF	1
	//Red OFF,	Green ON	2

//DEADCODE RJS 4/18/00 	adptr->acundercarriage  = I_UndercarraigePosition0 & 0x01;
//DEADCODE RJS 4/18/00 	adptr->acundercarriage2 = (I_UndercarraigePosition0 & 0x02) / 2;
//DEADCODE RJS 4/18/00 
//DEADCODE RJS 4/18/00 	adptr->acundercarriage3 = I_UndercarraigePosition1 & 0x01;
//DEADCODE RJS 4/18/00 	adptr->acundercarriage4 = (I_UndercarraigePosition1 & 0x02) / 2;

//DEADCODE CSB 14/01/00 	adptr->acfuelwarning  = I_FuelWarningLamp0;
//DEADCODE CSB 14/01/00 	adptr->acfuelwarning2 = I_FuelWarningLamp1;
//DEADCODE CSB 14/01/00 	adptr->acfuelwarning3 = I_FuelWarningLamp2;
//DEADCODE CSB 14/01/00 	adptr->acfuelwarning4 = I_FuelWarningLamp3;

	// Faked dials....

	TotalEngineDamage = EngineDamage((UByteP)adptr,1);   // 1 is number of engines

//DEADCODE CSB 14/01/00  	if (adptr->acvoltmeter < 64)								//RJS 26Nov99
//DEADCODE CSB 14/01/00  	{															//RJS 26Nov99
//DEADCODE CSB 14/01/00  		adptr->acpitch = 255;									//RJS 26Nov99
//DEADCODE CSB 14/01/00  		adptr->acfuelpressure = 0;								//RJS 26Nov99
//DEADCODE CSB 14/01/00  		adptr->acoilpressure = 0;								//RJS 26Nov99
//DEADCODE CSB 14/01/00  	}															//RJS 26Nov99
//DEADCODE CSB 14/01/00  	else														//RJS 26Nov99
//DEADCODE CSB 14/01/00  	{															//RJS 26Nov99
//DEADCODE CSB 14/01/00  		adptr->acoilpressure = (75*(255-adptr->ENGINELEFT))/100;	//RJS 26Nov99
//DEADCODE CSB 14/01/00  		adptr->acfuelpressure = (55*(255-adptr->ENGINELEFT))/100;	//RJS 26Nov99
//DEADCODE CSB 14/01/00  	}															//RJS 26Nov99
																//RJS 26Nov99
	// Now scale to timer...									//RJS 26Nov99
	for (index = 0; index < TimedDialCnt; index++)				//RJS 26Nov99
		TimedDialList[index].SetTimedAnim(animptr);				//RJS 26Nov99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateCockpitTimers
//Author		Robert Slater
//Date			Mon 16 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::UpdateCockpitTimers(SLong	theframetime)
{
	int	index;
	for (index=0; index < TimedDialCnt; index++)
		TimedDialList[index].theTimer += theframetime;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDialValue
//Author		Robert Slater
//Date			Mon 16 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	DialSpec::SetDialValue(ItemPtr	itm, UByteP	adptr,UByteP	*SrcListPtr)
{
	UByteP	SrcValPtr;
	SLong	theValue;

	switch (btype)
	{
	case SBASE_DEFAULT:
		SrcValPtr = SrcListPtr[SrcValStructIndex];
		SrcValPtr += SrcValOffset;
		 break;
	case SBASE_AC:
		SrcValPtr = (UByteP)itm;
		SrcValPtr += SrcValOffset;
		break;
	case SBASE_ANIM:
		SrcValPtr = (UByteP)&itm->Anim[0];
		SrcValPtr += SrcValOffset;
		break;
	}

	adptr += DestValOffset;

	if (useint)
	{
		switch (shiftsrc)
		{
		case 8:
			theValue = *SrcValPtr;
			break;
		case 15:
			theValue = *((SWord*)SrcValPtr);
			break;
		case 31:
			theValue = *((SLong*)SrcValPtr);
			break;
		}

		if (theValue < minIntval)
			theValue = minIntval;

		theValue -= minIntval;

//DeadCode RJS 01Dec99		if (theValue >= maxIntval)
//DeadCode RJS 01Dec99			theValue = maxIntval-1;
//DeadCode RJS 01Dec99
//DeadCode RJS 01Dec99		theValue <<= shiftdest;
//DeadCode RJS 01Dec99		theValue /= Intvalscale;

		if (theValue >= maxIntval)
		{
			theValue = maxIntval;
			theValue <<= shiftdest;
			theValue--;
		}
		else
			theValue <<= shiftdest;

		theValue /= Intvalscale;
	}
	else
	{
		FP theValue2 = *((FP*)SrcValPtr);

		if (theValue2 < minval)
			theValue2 = minval;

		theValue2 -= minval;

		if (theValue2 > maxval)
			theValue2 = maxval;

		theValue2 *= ValScale;
		theValue = theValue2;
	}

	if (shiftdest == 8)
		*adptr = theValue;
	else
		*((SWord*)adptr) = theValue;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDialValue
//Author		Robert Slater
//Date			Mon 16 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::NewDialValue(	void*	animptr,
									UByteP	animdestptr,
									void*	vstrucptr,
									UByteP	srcptr,
									int		minval,
									int		maxval,
									int		scaler,
									UByte	shiftsrc,
									UByte	shiftdest,
									UWord	restrot		)
{
	if (DialCnt < MaxAutoDial)									//RJS 29Jun98
	{
		int	i;
		DialSpec	*DPtr = &DialList[DialCnt];
		UByteP		adptr = (UByteP) animptr;
		UByteP		strucptr = (UByteP) vstrucptr;

		DPtr->useint = 1;
		DPtr->DestValOffset = animdestptr - adptr;
		DPtr->btype = SBASE_DEFAULT;

		if (vstrucptr != (void*)this)
		{
			if (vstrucptr == (void*)Manual_Pilot.ControlledAC2)
				DPtr->btype = SBASE_AC;
			else
			{
				if (vstrucptr == (void*)&Manual_Pilot.ControlledAC2->Anim[0])
					DPtr->btype = SBASE_ANIM;
			}
		}

		if (DPtr->btype == SBASE_DEFAULT)
		{
			for (i=0; i < DialSrcCnt; i++)
			{
				if (DialSrcList[i] == strucptr)
					break;
			}

			if (i == DialSrcCnt)
			{
				if (DialSrcCnt < MaxDialSrc)
					DialSrcList[DialSrcCnt++] = strucptr;
			}

			DPtr->SrcValStructIndex = i;
		}
		else
			DPtr->SrcValStructIndex = 0;

		DPtr->SrcValOffset = srcptr - strucptr;
		DPtr->minIntval = minval;
		DPtr->maxIntval = maxval - minval;
		if (scaler == 0)										//RJS 24Apr98
			DPtr->Intvalscale = DPtr->maxIntval;				//RJS 24Apr98
		else													//RJS 24Apr98
			DPtr->Intvalscale = scaler;							//RJS 24Apr98

		DPtr->shiftsrc = shiftsrc;
		DPtr->shiftdest = shiftdest;
		DPtr->torestval = restrot;

		if (	(DPtr->DestValOffset < 0)
			||	(DPtr->SrcValOffset < 0)	)
		{
			_Error.EmitSysErr(__FILE__":Dial Offset Wrong!");
		}

		DialCnt++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDialValue
//Author		Robert Slater
//Date			Mon 16 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::NewDialValue(	void*	animptr,
									UByteP	animdestptr,
									void*	vstrucptr,
									UByteP	srcptr,
									FP		minval,
									FP		maxval,
									FP		scaler,
									UByte	shiftdest,
									UWord	restrot		)
{
	if (DialCnt < MaxAutoDial)									//RJS 29Jun98
	{
		int	i;
		DialSpec	*DPtr = &DialList[DialCnt];
		UByteP		adptr = (UByteP) animptr;
		UByteP		strucptr = (UByteP) vstrucptr;

		DPtr->useint = 0;
		DPtr->DestValOffset = animdestptr - adptr;
		DPtr->btype = SBASE_DEFAULT;

		if (vstrucptr != (void*)this)
		{
			if (vstrucptr == (void*)Manual_Pilot.ControlledAC2)
				DPtr->btype = SBASE_AC;
			else
			{
				if (vstrucptr == (void*)&Manual_Pilot.ControlledAC2->Anim[0])
					DPtr->btype = SBASE_ANIM;
			}
		}

		if (DPtr->btype == SBASE_DEFAULT)
		{
			for (i=0; i < DialSrcCnt; i++)
			{
				if (DialSrcList[i] == strucptr)
					break;
			}

			if (i == DialSrcCnt)
			{
				if (DialSrcCnt < MaxDialSrc)
					DialSrcList[DialSrcCnt++] = strucptr;
			}

			DPtr->SrcValStructIndex = i;
		}
		else
			DPtr->SrcValStructIndex = 0;

		DPtr->SrcValOffset = srcptr - strucptr;
		DPtr->minval = minval;
		DPtr->maxval = maxval - minval;
		if (scaler == 0)										//RJS 24Apr98
		{
			switch (shiftdest)									//RJS 24Apr98
			{													//RJS 24Apr98
			case 8:												//RJS 24Apr98
				DPtr->ValScale = 255.0 / DPtr->maxval;			//RJS 24Apr98
				break;											//RJS 24Apr98
			case 15:											//RJS 24Apr98
				DPtr->ValScale = 65535.0 / DPtr->maxval;		//RJS 24Apr98
				break;											//RJS 24Apr98
			}
		}														//RJS 24Apr98
		else													//RJS 24Apr98
		{
			switch (shiftdest)					
			{													
			case 8:												
				DPtr->ValScale = 255.0 * (scaler / DPtr->maxval);			
				break;										
			case 15:											
				DPtr->ValScale = 65535.0 * (scaler / DPtr->maxval);	
				break;											
			}
//			DPtr->ValScale = scaler;							//RJS 24Apr98
		}

		DPtr->shiftdest = shiftdest;
		DPtr->torestval = restrot;

		if (	(DPtr->DestValOffset < 0)
			||	(DPtr->SrcValOffset < 0)	)
		{
			_Error.EmitSysErr(__FILE__":Dial Offset Wrong!");
		}

		DialCnt++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAutoDial
//Author		Robert Slater
//Date			Wed 18 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddAutoDial(	void*	animptr,
									UByteP	animdestptr,
									void*	strucptr,
									FP*		srcptr,
									FP		minval,
									FP		maxval,
									FP		scaler	)
{
	NewDialValue(animptr,animdestptr,strucptr,(UByteP)srcptr,minval,maxval,scaler,8);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAutoDial
//Author		Robert Slater
//Date			Wed 18 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddAutoDial(	void*	animptr,
									SWordP	animdestptr,
									void*	strucptr,
									FP*		srcptr,
									FP		minval,
									FP		maxval,
									FP		scaler	)
{
	NewDialValue(animptr,(UByteP)animdestptr,strucptr,(UByteP)srcptr,minval,maxval,scaler,15);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAutoDial
//Author		Robert Slater
//Date			Wed 18 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddAutoDial(	void*	animptr,
									UByteP	animdestptr,
									void*	strucptr,
									SWordP	srcptr,
									int		minval,
									int		maxval,
									int		scaler	)
{
	NewDialValue(animptr,animdestptr,strucptr,(UByteP)srcptr,minval,maxval,scaler,15,8);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAutoDial
//Author		Robert Slater
//Date			Wed 18 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddAutoDial(	void*	animptr,
									SWordP	animdestptr,
									void*	strucptr,
									SWordP	srcptr,
									int		minval,
									int		maxval,
									int		scaler	)
{
	NewDialValue(animptr,(UByteP)animdestptr,strucptr,(UByteP)srcptr,minval,maxval,scaler,15,15);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAutoDial
//Author		Robert Slater
//Date			Wed 18 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddAutoDial(	void*	animptr,
									UByteP	animdestptr,
									void*	strucptr,
									ULongP	srcptr,
									int		minval,
									int		maxval,
									int		scaler	)
{
	NewDialValue(animptr,animdestptr,strucptr,(UByteP)srcptr,minval,maxval,scaler,31,8);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAutoDial
//Author		Robert Slater
//Date			Wed 18 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddAutoDial(	void*	animptr,
									SWordP	animdestptr,
									void*	strucptr,
									ULongP	srcptr,
									int		minval,
									int		maxval,
									int		scaler	)
{
	NewDialValue(animptr,(UByteP)animdestptr,strucptr,(UByteP)srcptr,minval,maxval,scaler,31,15);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAutoDial
//Author		Robert Slater
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddAutoDial(	void*	animptr,
									UByteP	animdestptr,
									void*	strucptr,
									SLongP	srcptr,
									int		minval,
									int		maxval,
									int		scaler	)
{
	NewDialValue(animptr,(UByteP)animdestptr,strucptr,(UByteP)srcptr,minval,maxval,scaler,31,8);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddAutoDial
//Author		Robert Slater
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddAutoDial(	void*	animptr,
									SWordP	animdestptr,
									void*	strucptr,
									SLongP	srcptr,
									int		minval,
									int		maxval,
									int		scaler	)
{
	NewDialValue(animptr,(UByteP)animdestptr,strucptr,(UByteP)srcptr,minval,maxval,scaler,31,15);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTimedDial
//Author		Robert Slater
//Date			Mon 29 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::AddTimedDial(	void*	adptr,
									UByteP	animdp,
									int		timeUp,
									int		timeDown,
									Bool	signedSrc	)
{
	int	doffset = ((UByteP)animdp) - ((UByteP)adptr);

	NewTimedDial(doffset,timeUp,timeDown,signedSrc,FALSE,8);
}

void	INSTRUMENTS::AddTimedDial(	void*	adptr,
									SByteP	animdp,
									int		timeUp,
									int		timeDown,
									Bool	signedSrc	)
{
	int	doffset = ((UByteP)animdp) - ((UByteP)adptr);

	NewTimedDial(doffset,timeUp,timeDown,signedSrc,TRUE,8);
}

void	INSTRUMENTS::AddTimedDial(	void*	adptr,
									UWordP	animdp,
									int		timeUp,
									int		timeDown,
									Bool	signedSrc	)
{
	int	doffset = ((UByteP)animdp) - ((UByteP)adptr);

	NewTimedDial(doffset,timeUp,timeDown,signedSrc,FALSE,16);
}

void	INSTRUMENTS::AddTimedDial(	void*	adptr,
									SWordP	animdp,
									int		timeUp,
									int		timeDown,
									Bool	signedSrc	)
{
	int	doffset = ((UByteP)animdp) - ((UByteP)adptr);

	NewTimedDial(doffset,timeUp,timeDown,signedSrc,TRUE,16);
}

void	INSTRUMENTS::AddTimedDial(	void*	adptr,
									ULongP	animdp,
									int		timeUp,
									int		timeDown,
									Bool	signedSrc	)
{
	int	doffset = ((UByteP)animdp) - ((UByteP)adptr);

	NewTimedDial(doffset,timeUp,timeDown,signedSrc,FALSE,32);
}

void	INSTRUMENTS::AddTimedDial(	void*	adptr,
									SLongP	animdp,
									int		timeUp,
									int		timeDown,
									Bool	signedSrc	)
{
	int	doffset = ((UByteP)animdp) - ((UByteP)adptr);

	NewTimedDial(doffset,timeUp,timeDown,signedSrc,TRUE,32);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewTimedDial
//Author		Robert Slater
//Date			Mon 29 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	INSTRUMENTS::NewTimedDial(	int		doffset,
									int		tup,
									int		tdown,
									Bool	signedSrc,
									Bool	signedDest,
									UByte	nobits	)
{
	if (TimedDialCnt < MaxAutoDial)
	{
		TimedDialList[TimedDialCnt].OldVal = 0;
		TimedDialList[TimedDialCnt].OldGap = 0;
		TimedDialList[TimedDialCnt].theTimer = 0;
		TimedDialList[TimedDialCnt].SrcVal = 0;
		TimedDialList[TimedDialCnt].destOffset = doffset;
		TimedDialList[TimedDialCnt].timeUp = tup;
		TimedDialList[TimedDialCnt].timeDown = tdown;
//		TimedDialList[TimedDialCnt].signedSrc = signedSrc;
		TimedDialList[TimedDialCnt].signedDest = signedDest;
		TimedDialList[TimedDialCnt++].nobitsDest = nobits;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTimedAnim
//Author		Robert Slater
//Date			Mon 29 Jun 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TimedDialSpec::SetTimedAnim(void*	adptr)
{
	SLong	scaled=0;
	SLong	gap;
	SLong	Desired = 0;
	UByteP	animp = ((UByteP)adptr) + destOffset;
	SLong	dist = 255;
	SLong	ROld;

	if (!signedDest)
	{
		switch (nobitsDest)
		{
		case 8:
			Desired = *animp;
			break;
		case 16:
			Desired = *((UWordP)animp);
			dist = 65535;
			break;
		}
	}
	else
	{
		switch (nobitsDest)
		{
		case 8:
			Desired = *((SByteP)animp);
			break;
		case 16:
			Desired = *((SWordP)animp);
			dist = 65535;
			break;
		}
	}

	ROld = Desired - OldVal;
	gap = Desired - SrcVal;

	if (gap)
	{
		if (gap > 0)
		{
			if (ROld <= 0)
			{
				theTimer = 0;
				SrcVal = OldVal;
			}
			else
			{
				scaled = (theTimer * dist) / timeUp;
				if (scaled > gap)
				{
					scaled = 0;
					SrcVal = Desired;
				}
			}
		}
		else
		{
			if (ROld >= 0)
			{
				theTimer = 0;
				SrcVal = OldVal;
			}
			else
			{
				scaled = (theTimer * -dist) / timeDown;
				if (scaled < gap)
				{
					scaled = 0;
					SrcVal = Desired;
				}
			}
		}

		scaled += SrcVal;
		switch (nobitsDest)
		{
		case 8:
			*((UByteP)animp) = scaled;
			break;
		case 16:
			*((UWordP)animp) = scaled;
			break;
		case 32:
			*((ULongP)animp) = scaled;
			break;
		}

		OldVal = scaled;
		OldGap = gap;
	}
	else
	{
		theTimer = 0;
		if (ROld)
		{
			SrcVal = OldVal;
			OldGap = -OldGap;
		}
		else
		{
			SrcVal = Desired;
			OldVal = SrcVal;
			OldGap = 0;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFuelGaugeSelector
//Author		Craig Beeston
//Date			Fri 02 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void INSTRUMENTS::SetFuelGaugeSelector(SWord tank1, ULong scale1, SWord tank2, ULong scale2, SWord tank3, ULong scale3, SWord tank4, ULong scale4)
{
	FuelGuageTank[0] = tank1;
	FuelGuageTank[1] = tank2;
	FuelGuageTank[2] = tank3;
	FuelGuageTank[3] = tank4;
	
	FuelGuageScale[0] = scale1;
	FuelGuageScale[1] = scale2;
	FuelGuageScale[2] = scale3;
	FuelGuageScale[3] = scale4;
}

