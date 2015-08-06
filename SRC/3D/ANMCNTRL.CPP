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
//Filename       anmcntrl.cpp
//System         
//Author         Ruport Splinter
//Date           Wed 21 Oct 1998
//Description    
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#include	"worldinc.h"
#include	"viewsel.h"
#include	"animmove.h"
#include	"3dcom.h"

AnimControl Anim_Control;

void	ANIMCONTROLSTRUC::SetAnim(AnimMoves pre, AnimMoves trans, AnimMoves post, SWord tokumtime)
{
	if (acnt < MAXANIMSCRIPT)
	{
		from[acnt] = pre;
		to[acnt] = post;
		mid[acnt] = trans;

		acnt++;
	}
}

void	ANIMCONTROLSTRUC::SetAnim(AnimMoves pre, AnimMoves post, SWord tokumtime)
{
	if (acnt < MAXANIMSCRIPT)
	{
		from[acnt] = pre;
		to[acnt] = post;
		mid[acnt] = BLOKE_NULL;

		acnt++;
	}
}

void	ANIMCONTROLSTRUC::SetAnim(AnimMoves post, SWord tokumtime)
{
	if (acnt < MAXANIMSCRIPT)
	{
		from[acnt] = BLOKE_NULL;
		to[acnt] = post;
		mid[acnt] = BLOKE_NULL;

		acnt++;
	}
}

ANIMCONTROLSTRUC*	AnimControl::GetAnimControl(tAnimation animtype) 
{
	return (&animlist[animtype]);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AnimControl
//Author		Robert Slater
//Date			Wed 21 Oct 1998
//
//Description	CONSTRUCTOR
//------------------------------------------------------------------------------
AnimControl::AnimControl()
{
	View_Point = NULL;

	if (animlist)
	{
		ANIMCONTROLSTRUC*	animP;

		animP = GetAnimControl(ANIMATION_STAND);
		animP->SetAnim(BLOKE_STAND);

 		animP = GetAnimControl(ANIMATION_WALK);
 		animP->SetAnim(BLOKE_WALK);

//DeadCode RJS 22Dec99 		animP = GetAnimControl(ANIMATION_JOG);
//DeadCode RJS 22Dec99   		animP->SetAnim(BLOKE_JOG);
 		
  		animP = GetAnimControl(ANIMATION_RUN);					//RJS 22Dec99
  		animP->SetAnim(BLOKE_RUN);

		animP = GetAnimControl(ANIMATION_DIVE);
  		animP->SetAnim(BLOKE_DIVE);

		animP = GetAnimControl(ANIMATION_PULL_CHUTE);
  		animP->SetAnim(BLOKE_PULLCHUTE);

		animP = GetAnimControl(ANIMATION_GOOD_CHUTE);
  		animP->SetAnim(BLOKE_GOODCHUTE);

		animP = GetAnimControl(ANIMATION_AARGH);
  		animP->SetAnim(BLOKE_WAAAH);

		animP = GetAnimControl(ANIMATION_LAND_GOOD);
  		animP->SetAnim(BLOKE_LANDGOOD);

		animP = GetAnimControl(ANIMATION_LAND_SPLAT);
  		animP->SetAnim(BLOKE_LANDSPLAT);

		animP = GetAnimControl(ANIMATION_RUNCHICKEN);
  		animP->SetAnim(BLOKE_RUNCHICKEN);

/*		animP = GetAnimControl(ANIMATION_DIVE_FOR_COVER);
  		animP->SetAnim(BLOKE_DIVEFORCOVER);*/

		animP = GetAnimControl(ANIMATION_BORED);
		animP->SetAnim(BLOKE_STAND);	//bias on doing nothing
		animP->SetAnim(BLOKE_STAND);
		animP->SetAnim(BLOKE_STAND);
		animP->SetAnim(BLOKE_STAND);
  		animP->SetAnim(BLOKE_BORED1);
  		animP->SetAnim(BLOKE_BORED2);
  		animP->SetAnim(BLOKE_BORED3);
  		animP->SetAnim(BLOKE_BORED4);

		animP = GetAnimControl(ANIMATION_TALK);
		animP->SetAnim(BLOKE_STAND);
		animP->SetAnim(BLOKE_STAND);
		animP->SetAnim(BLOKE_STAND);
		animP->SetAnim(BLOKE_BORED4);
  		animP->SetAnim(BLOKE_TALK1);
  		animP->SetAnim(BLOKE_TALK2);
  		animP->SetAnim(BLOKE_TALK1);									//RJS 30Oct00
  		animP->SetAnim(BLOKE_TALK2);									//RJS 30Oct00
//DeadCode RJS 30Oct00 		animP->SetAnim(BLOKE_TALK3);
//DeadCode RJS 30Oct00   		animP->SetAnim(BLOKE_TALK4);

/*		animP = GetAnimControl(ANIMATION_SHOT);
  		animP->SetAnim(BLOKE_SHOT);*/



	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AnimControl
//Author		Robert Slater
//Date			Wed 21 Oct 1998
//
//Description	DESTRUCTOR
//------------------------------------------------------------------------------
AnimControl::~AnimControl()
{
}



//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewPoint
//Author		Robert Slater
//Date			Thu 22 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AnimControl::SetViewPoint(ViewPoint*	vp)
{
	View_Point = vp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetAnimMove
//Author		Robert Slater
//Date			Thu 22 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AnimMoves	AnimControl::GetAnimMove(tAnimation	theAnim,AnimMoves	prevAnim,AnimMoves&	transAnim)
{
	AnimMoves animmove = animlist[theAnim].GetAnimMove(prevAnim,transAnim) ;
	if (animmove != BLOKE_NULL)
		return animmove;
	return BLOKE_STAND ; // default
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetPlayerAnim
//Author		James Woodworth
//Date			Tue 6 Jul 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	AnimControl::SetPlayerAnim(ItemPtr	item, UWord	newanim)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(item->shape);

	if (sdptr->AnimDataSize == TROOPANIM)						//RJS 30Nov99
	{
		TroopAnimData* adptr = (TroopAnimData*) item->Anim;		//RJS 30Nov99

		if (	(adptr->animCtrl_new != newanim)
			||	(animlist[newanim].acnt > 1)		)
		{
//DeadCode RJS 20Oct00 			AnimMoves		transAnim = BLOKE_NULL;

			adptr->animCtrl_prev = adptr->animCtrl_new;
			adptr->animCtrl_new = newanim;

			adptr->newanimpose = animlist[newanim].GetAnimMove();
			adptr->animCtrl_prev = adptr->animCtrl_new;
		}

		return true;
	}

	return false;
}

bool	AnimControl::Finished(ItemPtr	item, const tAnimation&	theAnim)
{
	TroopAnimData* adptr = (TroopAnimData*) item->Anim;
	if (	(adptr->animCtrl_current == theAnim)
		&&	(adptr->swapnow)					)
		return true;

	return false;
}

AnimMoves	ANIMCONTROLSTRUC::GetAnimMove()
{
	if (acnt)
		return to[Math_Lib.rnd(acnt)];

	return(BLOKE_STAND);
}

bool	AnimControl::NeverStarted(ItemPtr	item, const tAnimation&	theAnim)
{
	TroopAnimData* adptr = (TroopAnimData*) item->Anim;
	if (adptr->animCtrl_current != theAnim)
		return true;

	return false;
}
