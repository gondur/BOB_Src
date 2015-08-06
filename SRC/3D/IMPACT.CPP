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
//Filename       impact.cpp
//System         
//Author         Robert Slater
//Date           Thu 25 Nov 1999
//Description    Special collision for SAGS & BALLOONS
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#include	"worldinc.h"
#include	"shapes.h"
#include	"3dcom.h"
#include	"mymath.h"
#include	"impact.h"


Impact	Fake_Damage;											//RJS 05/04/00



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDamageLoc
//Author		Robert Slater
//Date			Thu 25 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong Impact::GetDamageLoc(ShapeNum theShape, animptr&	animdata)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
	SLong			firstDamageByte = sdptr->DamageOffset;				//CSB 3Nov00
	
	if (firstDamageByte)												//CSB 3Nov00
	{
// Unfortunately we can only guarantee the 1st 5 damage elements will exist within the shape!
		SLong	lastDamageByte = firstDamageByte + 5;//SHAPE.GetAnimDataSize(theShape);		//CSB 3Nov00
		UByteP	adptr = &animdata;
		SLong	damindex = 0;

		int totaldamage=0;
	
		for (int k=firstDamageByte;k<lastDamageByte;k++)						//CSB 3Nov00
			totaldamage+=adptr[k];

		int damageto=Math_Lib.rnd(totaldamage);
	
		totaldamage= adptr[firstDamageByte];							//CSB 3Nov00

		for (k=firstDamageByte;k<lastDamageByte-1;k++)							//CSB 3Nov00
		{
			if (totaldamage<damageto)
			{
				damindex = k;
				break;
			}		
			totaldamage+= adptr[k+1];
		}

		if (!damindex)	damindex = firstDamageByte + Math_Lib.rnd(lastDamageByte-firstDamageByte);	//CSB 06/06/00

		return damindex;
	}

	return -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HitGroupElement
//Author		Robert Slater
//Date			Thu 25 Nov 1999
//
//Description	We want type and amount of damage passed in....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Impact::HitGroupElement(ItemPtr	theItem, ItemPtr	theShooter, SLong index, SLong amount, SLong damagetype)
{
	ShapeNum	newShape = theItem->shape;
	animptr		adptr = theItem->Anim;
	int			damageloc;
	Coords3D	grppos;

	SHAPE.SimpleGroupItemAnim(adptr,newShape,index,grppos);

	MinAnimData*	mad = (MinAnimData*)adptr;
	if (!mad->IsInvisible)
	{
		damageloc = GetDamageLoc(newShape,adptr);
		if (damageloc > -1)												//CSB 3Nov00
		{
//DEADCODE RJS 5/10/00 			UByte	oldamount = adptr[damageloc];
//DEADCODE RJS 5/10/00 			SLong	newdamage = SLong(oldamount) + amount;
//DEADCODE RJS 5/10/00 
//DEADCODE RJS 5/10/00 			if (newdamage > BS_DEAD)
//DEADCODE RJS 5/10/00 				newdamage = BS_DEAD;

			SHAPE.ForceWeaponDamage(theItem,theShooter,newShape,adptr,index,damageloc,damagetype,amount,&grppos);//RJS 10May00
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CollideAircraft
//Author		Robert Slater
//Date			Fri 26 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Impact::CollideAircraft(AirStrucPtr	ac1, AirStrucPtr ac2)
{
	WorldStuff*	worldptr = mobileitem::currworld;

	if (ac1 == Persons2::PlayerGhostAC)									//RJS 2Oct00
		ac1 = Persons2::PlayerSeenAC;									//RJS 2Oct00

	if (ac2 == Persons2::PlayerGhostAC)									//RJS 2Oct00
		ac2 = Persons2::PlayerSeenAC;									//RJS 2Oct00

	Trans_Obj.KillLauncher(ac1,ac2,*worldptr,-1,NULL);
	Trans_Obj.KillLauncher(ac2,ac1,*worldptr,-1,NULL);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HitGroup
//Author		Robert Slater
//Date			Mon 20 Dec 1999
//
//Description	May cause a problem for REPLAY
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool Impact::HitGroup(ItemPtr	theItem, ItemPtr	theShooter, SLong amount, SLong damagetype)
{
	ShapeNum	newShape = theItem->shape;
	animptr		adptr = theItem->Anim;
	int			damageloc,index;
	Coords3D	grppos;
	bool		retval = false;

	index = SHAPE.MostDamagedGroupItemAnim(adptr,newShape,grppos);
	if (index > -1)
	{
		damageloc = GetDamageLoc(newShape,adptr);
		if (damageloc > -1)												//CSB 3Nov00
		{
//DEADCODE RJS 5/10/00 			UByte	oldamount = adptr[damageloc];
//DEADCODE RJS 5/10/00 			SLong	newdamage = SLong(oldamount) + amount;
//DEADCODE RJS 5/10/00 
//DEADCODE RJS 5/10/00 			if (newdamage > BS_DEAD)
//DEADCODE RJS 5/10/00 				newdamage = BS_DEAD;

			SHAPE.ForceWeaponDamage(theItem,theShooter,newShape,adptr,index,damageloc,damagetype,amount,&grppos);//RJS 10May00

			retval = true;
		}
	}

	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HitAircraft
//Author		Robert Slater
//Date			Tue 30 May 2000
//
//Description	May cause a problem for REPLAY
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Impact::HitAircraft(ItemPtr	theItem, ItemPtr	theShooter, SLong amount, SLong damagetype)
{
	if (theItem == Persons2::PlayerGhostAC)								//RJS 2Oct00
		theItem = Persons2::PlayerSeenAC;								//RJS 2Oct00

	animptr		adptr = theItem->Anim;
	int			damageloc;
	Coords3D	grppos;

	MinAnimData*	mad = (MinAnimData*)adptr;
	if (!mad->IsInvisible)
	{
		if (	(theItem != Manual_Pilot.ControlledAC2)
			||	Save_Data.gamedifficulty[GD_VULNERABLE]	)
		{
			damageloc = GetDamageLoc(theItem->shape,adptr);
			if (damageloc > -1)											//CSB 3Nov00
				SHAPE.ForceWeaponDamage(theItem,theShooter,theItem->shape,adptr,-1,damageloc,damagetype,amount);
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TestForBalloon
//Author		Robert Slater
//Date			Tue 12 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Impact::TestForBalloon(ItemPtr	theItem)
{
	ItemPtr	ac = theItem;

	while (theItem)
	{
		if (	(theItem->shape == BALGRP)
			&&	CheapCol(ac,theItem)		)
		{
			ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(ac->shape);
			UByteP				damptr = NULL;							//RJS 20Oct00

			if (sdptr->AnimDataSize == AIRCRAFTANIM)
			{
				AircraftAnimData*	adptr = (AircraftAnimData*)ac->Anim;
				damptr = &adptr->RIGHTWINGIN;
			}
			else
			{
				if (sdptr->AnimDataSize == SIMPLEAIRCRAFTANIM)	
				{
					SimpleAircraftAnimData*	adptr = (SimpleAircraftAnimData*)ac->Anim;
					damptr = &adptr->RIGHTWINGIN;
				}
			}

			if (damptr)													//RJS 20Oct00
				SHAPE.ForceDamage(ac,theItem,damptr,BS_DEAD);			//RJS 20Oct00
		}
		
		theItem = theItem->Next;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CheapCol
//Author		Robert Slater
//Date			Tue 12 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	Impact::CheapCol(ItemPtr	trg, ItemPtr hitter)
{
	if (trg->World.Y < hitter->World.Y)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(BALGRP);
		SLong			sizex = sdptr->sx << 4;
		SLong			sizez = sdptr->sz << 4;

		if (	trg->World.X-hitter->World.X>sizex
			||	trg->World.X-hitter->World.X<-sizex
			)
			return false;

		if (	trg->World.Z-hitter->World.Z>sizez
			||	trg->World.Z-hitter->World.Z<-sizez
			)
			return false;

		if (Math_Lib.rnd() > 2048)
			return false;

		return true;
	}

	return false;
}
