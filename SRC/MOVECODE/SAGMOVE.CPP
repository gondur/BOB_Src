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
// Module:      sagmove.cpp
//
// Created:     01/12/99 by JIM											//MS 28Oct00
//																		//JIM 9Nov00
// Description: Movecodes for SAGs
//		Sags move in a different way than ordinary items
//		There are 2 versions of each movecode based on the type of object:
//		Map screen:	type info_airgrp	Called every 20 second event
//		3d flying:	type AirStruc		frametime is 4 cs. Events every 20sec
//		Keep the 2 versions of each routine together so they can be maintained
//////////////////////////////////////////////////////////////////////
#define IN_SAGMOVE
#include "dosdefs.h"
#include "myerror.h"
#include "worldinc.h"
#include "airstruc.h"
#include "BFNUMBER.h"
#include "persons2.h"
#include "cstring.h"
#include "package.h"
#include	"savegame.h"
#include "missman2.h"
#include "mytime.h"
#define	 sagmove_REQUIRED	SAGAirstruc:AirStruc
#include "sagmove.h"
#define	 sagmove_REQUIRED	SAGairgrp:info_airgrp
#define PARAMS	int p, int s
#include "sagmove.h"  
#include "mymath.h"	  
#include "animdata.h"
#include "shpinstr.h"
#include "savegame.h"
#include "groupitt.h"
#include "3dcom.h"
#include "3dcode.h"
#include "planetyp.h"
#include "airstruc.h"
#include "ai.h"
#include "aaa.h"
#include	"sqddiary.h"
#include "nodebob.h"										//RJS 02Feb00
#include "rchatter.h"										//RJS 02Feb00
#include "replay.h"
#include	"impact.h"											//RJS 05Apr00
#include "shapes.h"
#include "viewsel.h"
#include "model.h"
#include "monotxt.h"
#include	"miles.h"													//RJS 10Oct00

#define MIN_NUM_ACS 240
#define MAX_NUM_ACS 256

extern RequiredBankDataElement 	CombatReqBankData[];
//////////////////////////////////////////////////////////////////////
//
// Function:    OverFrance
// Date:		10/09/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	ItemBase::OverFrance(Coords3D& w)
{
	return (w.X-w.Z>METRES100KM);

}
//////////////////////////////////////////////////////////////////////
//
// Function:    MoveAllSAGs
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::MoveAllSAGs(WorldStuff& world)
{

	for (int i=SagBAND;i!=SagBANDEND;i++)
	{
		SAGAirstruc* as=Persons2::ConvertPtrUID(UniqueID(i));
		if (as)
		{
			UWord	oldsector=0xFFFF;										  //JIM 17/02/99
			if(as->movecode != AUTOSAG_WAITTAKEOFF)
				oldsector=	world.GetSector(as);					  //JIM 17/02/99
//DeadCode JIM 3Aug00 			else
//DeadCode JIM 3Aug00 				oldsector=0xFFFF;

			as->MoveSAG();

//DEADCODE JIM 31/05/00 			if (as->uniqueID.changed && oldsector!=0xFFFF)				  //JIM 17/02/99			if(oldsector!=0xFFFF)				  //JIM 17/02/99
			if(oldsector!=0xFFFF)				  //JIM 17/02/99
			{
				UWord	newsector=	world.GetSector(as);
#ifdef NDEBUG
				if (newsector!=oldsector)
#endif			//By not doing this test in debug mode I can track down problems more quickly.
				{
					world.RemoveFromSector(as,oldsector);
					world.AddToWorld(as);
				}
				as->uniqueID.changed = FALSE;						//RDH 26Jun96
			}
			else
				oldsector = oldsector;
		}
	}

	if ((timeofday & 511) == 0)
		for (i=SagBAND;i!=SagBANDEND;i++)
		{
			SAGAirstruc* as=Persons2::ConvertPtrUID(UniqueID(i));
			if (as)
				as->DecideSAG();
		}

}

void	SAGAirstruc::MoveSAG()
{
	assert(((movecode &-2)!=AUTOSAG_TRACKEXPFOLLOW) == (fly.expandedsag==NULL));
	assert((movecode == AUTOSAG_DESTROYED) || (movecode == AUTOSAG_DEATHGLIDE) || (!Status.deadtime));

	AutoMoveCodeTypeSelect lastmovecode=movecode;
	switch (movecode)
	{
	case	AUTOSAG_WAITTAKEOFF:	SAGMovementWaitTakeOff();		break;	
	case	AUTOSAG_TAKEOFF:		SAGMovementTakeOff();			break;
	case	AUTOSAG_FOLLOWWP:		SAGMovementFollowWP();			break;
	case	AUTOSAG_FOLLOWWPHOME:	SAGMovementFollowWP();			break;
	case	AUTOSAG_LANDING:		SAGMovementLanding();			break;
	case	AUTOSAG_REFUELLING:		SAGMovementLanded();			break;
	case	AUTOSAG_PRECOMBAT:		SAGMovementPreCombat();			break;
	case	AUTOSAG_COMBAT:			SAGMovementCombat();			break;
	case	AUTOSAG_COMBATCIRCLES:	SAGMovementCombatCircles();		break;
	case	AUTOSAG_POSTCOMBAT:		SAGMovementPostCombat();		break;
	case	AUTOSAG_BOMBAPPROACH:	SAGMovementBombingApproach();	break;
	case	AUTOSAG_BOMB:			SAGMovementBombing();			break;
	case	AUTOSAG_DEATHGLIDE:		SAGMovementDeathGlide();		break;
	case	AUTOSAG_TRACKEXPFOLLOW:	SAGMovementTrackExpanded();		break;
	case	AUTOSAG_TRACKEXPCOMBAT:	SAGMovementTrackExpandedCombat();break;
	case	AUTOSAG_DESTROYED:		SAGMovementDestroyed();			break;
	case	AUTOSAG_LAST:			SAGMovementLanded();			break;
	}

#ifndef _NDEBUG
	switch (movecode)
	{
		case	AUTOSAG_TAKEOFF:
		case	AUTOSAG_FOLLOWWP:
		case	AUTOSAG_FOLLOWWPHOME:
		case	AUTOSAG_LANDING:
		case	AUTOSAG_PRECOMBAT:
		case	AUTOSAG_COMBAT:
		case	AUTOSAG_COMBATCIRCLES:
		case	AUTOSAG_POSTCOMBAT:
		case	AUTOSAG_BOMBAPPROACH:
		case	AUTOSAG_BOMB:
			break;
		case	AUTOSAG_TRACKEXPFOLLOW:
		case	AUTOSAG_TRACKEXPCOMBAT:
			assert(fly.expandedsag);
			if(uniqueID.changed == FALSE)
				int DoNothingForABreakpoint = 0;
	}
#endif

	assert(((movecode &-2)!=AUTOSAG_TRACKEXPFOLLOW) == (fly.expandedsag==NULL));
	assert((movecode == AUTOSAG_DESTROYED) || (movecode == AUTOSAG_DEATHGLIDE) || (!Status.deadtime));

	weap.ShootDelay = weap.ShootDelay - Timer_Code.FRAMETIME;
	if(weap.ShootDelay < 0)
		weap.ShootDelay = 0;
}


void	SAGAirstruc::DecideSAG()
{
	assert(((movecode &-2)!=AUTOSAG_TRACKEXPFOLLOW) == (fly.expandedsag==NULL));
	AutoMoveCodeTypeSelect lastmovecode=movecode;

	if(		(movecode != AUTOSAG_TRACKEXPFOLLOW) 
		&&	(movecode != AUTOSAG_TRACKEXPCOMBAT) 
		&&	(movecode != AUTOSAG_DESTROYED)		)
	{
		GroupItterator gi(shape,Anim);	//Check elements are turned on
		gi++;  //skip elt 0.
		int totalac = fly.numinsag;
		int elementson = 0;
		while (totalac--)
		{
			if(!gi.AnimDataMAD().IsInvisible)
				elementson++;
			gi++;
		}

		if(!elementson)
		{
			DestroySag();
//DeadCode CSB 4Aug00 			movecode = AUTOSAG_DESTROYED;
//DeadCode CSB 4Aug00 			SetUnfriendly(NULL);
		}
	}

	switch (movecode)
	{
	case	AUTOSAG_WAITTAKEOFF:	SAGDecisionWaitTakeOff();			break;	
	case	AUTOSAG_TAKEOFF:		SAGDecisionTakeOff();				break;
	case	AUTOSAG_FOLLOWWP:		SAGDecisionFollowWP();				break;
	case	AUTOSAG_FOLLOWWPHOME:	SAGDecisionFollowWP();				break;
	case	AUTOSAG_LANDING:		SAGDecisionLanding();				break;
	case	AUTOSAG_REFUELLING:		SAGDecisionLanded();				break;
	case	AUTOSAG_PRECOMBAT:		SAGDecisionPreCombat();				break;
	case	AUTOSAG_COMBAT:			SAGDecisionCombat();				break;
	case	AUTOSAG_COMBATCIRCLES:	SAGDecisionCombatCircles();			break;
	case	AUTOSAG_POSTCOMBAT:		SAGDecisionPostCombat();			break;
	case	AUTOSAG_BOMBAPPROACH:	SAGDecisionBombingApproach();		break;
	case	AUTOSAG_BOMB:			SAGDecisionBombing();				break;
	case	AUTOSAG_TRACKEXPFOLLOW:	SAGDecisionTrackExpanded();			break;
	case	AUTOSAG_TRACKEXPCOMBAT:	SAGDecisionTrackExpandedCombat();	break;
	case	AUTOSAG_DESTROYED:		SAGDecisionDestroyed();				break;
	case	AUTOSAG_LAST:			SAGDecisionLanded();				break;
	}
	assert(((movecode &-2)!=AUTOSAG_TRACKEXPFOLLOW) == (fly.expandedsag==NULL));
	lastmovecode=movecode;
	
	if(		(movecode != AUTOSAG_REFUELLING)
		&&	(movecode != AUTOSAG_DESTROYED)	
		&&	(movecode != AUTOSAG_DEATHGLIDE)	
		&&	(movecode != AUTOSAG_LAST)	)
		if((movecode == AUTOSAG_COMBAT) || (ai.attacker))
			TryToExpandSag(true);
		else 
			TryToExpandSag(false);

	assert(((movecode &-2)!=AUTOSAG_TRACKEXPFOLLOW) == (fly.expandedsag==NULL));
//DEADCODE AMM 24/02/00 	if (!fly.expandedsag)
//DEADCODE AMM 24/02/00 	{	//consider for expansion
//DEADCODE AMM 24/02/00 		//This current test is very crude
//DEADCODE AMM 24/02/00 		//need much more refined ones
//DEADCODE AMM 24/02/00 		PlaneTypeSelect actype=classtype->planetext;
//DEADCODE AMM 24/02/00 		int factor1=4;	//change this to represent different scenarios 
//DEADCODE AMM 24/02/00 						//eg close to player/bomber/under attack/far from player
//DEADCODE AMM 24/02/00 						//also need to keep a check on total expanded a/c<256
//DEADCODE AMM 24/02/00 		if (	(Persons3::sagexpcounts[actype].numactive)*factor1
//DEADCODE AMM 24/02/00 			<	Persons3::sagexpcounts[actype].numavailable*2)
//DEADCODE AMM 24/02/00 		{	//over 2/3 available aircraft used up excluding this flight
//DEADCODE AMM 24/02/00 			//If this flight is all in formation then we can re-compact it
//DEADCODE AMM 24/02/00 			ExpandSag(false);
//DEADCODE AMM 24/02/00 
//DEADCODE AMM 24/02/00 		}
//DEADCODE AMM 24/02/00 	}
}
//////////////////////////////////////////////////////////////////////
//
// Function:    MergeTypes
// Date:		25/07/00
// Author:		JIM
//
//Description: Merges some planetype slots together
//
//////////////////////////////////////////////////////////////////////
inline PlaneTypeSelect MergeTypes(PlaneTypeSelect pts)
{
	if (pts>PT_GER_NONFLY)
		pts=PT_GER_NONFLY;
	return pts;
}

void AirStruc::TryToExpandSag(bool forced)
{
	if(fly.expandedsag)	//Already expanded																				//CSB 27Jul00
		return;																											//CSB 27Jul00
																														//CSB 27Jul00
	PlaneTypeSelect actype = MergeTypes(classtype->planetext);															//CSB 27Jul00
	if(classtype->planetext > PT_GER_NONFLY)																			//CSB 27Jul00
		actype = PT_GER_NONFLY;																							//CSB 27Jul00
																														//CSB 27Jul00
	FP Range2 = Distance3DSquared(&Persons2::PlayerGhostAC->World);														//CSB 27Jul00
	if(Range2 < FP(2 * VISIBLERANGE) * FP(2 * VISIBLERANGE))
	{
		FP TriggerRange2 = Persons3::sagexpcounts[actype].currenttriggerrange;												//CSB 27Jul00
		TriggerRange2 *= TriggerRange2;																						//CSB 27Jul00

// NOTE: this forced is nothing to do with comms or replay

		if(forced)																											//CSB 27Jul00
			Range2 *= (1.0 / (4.0 * 4.0));																					//CSB 27Jul00
																															//CSB 27Jul00
		if(Range2 < TriggerRange2)																						//CSB 27Jul00
		{																												//CSB 27Jul00
			if(Persons3::sagexpcounts[actype].numavailable - Persons3::sagexpcounts[actype].numactive >= fly.numinsag)	//CSB 27Jul00
			{
				if(Persons3::SagExpansionCounter::totalexpanded >= MAX_NUM_ACS)																//CSB 27Jul00
					for(int i = PT_BRIT_FLYABLE; i <= PT_GER_NONFLY; i++)
					{
						Persons3::sagexpcounts[i].currenttriggerrange *= 0.95;														//CSB 27Jul00
						if(Persons3::sagexpcounts[i].currenttriggerrange < Persons3::sagexpcounts[i].mintriggerrange)				//CSB 27Jul00
							Persons3::sagexpcounts[i].currenttriggerrange = Persons3::sagexpcounts[i].mintriggerrange;				//CSB 27Jul00
					}
				else
					ExpandSag(false);																						//CSB 27Jul00
			}
			else																										//CSB 27Jul00
				Persons3::sagexpcounts[actype].currenttriggerrange = FSqrt(Range2);										//CSB 27Jul00
		}																												//CSB 27Jul00
		else																											//CSB 27Jul00
			if(Persons3::SagExpansionCounter::totalexpanded < MIN_NUM_ACS)														//CSB 27Jul00
				if(Persons3::sagexpcounts[actype].numavailable - Persons3::sagexpcounts[actype].numactive >= fly.numinsag)//CSB 27Jul00
					Persons3::sagexpcounts[actype].currenttriggerrange *= 1.10;											//CSB 27Jul00

		if(Persons3::sagexpcounts[actype].currenttriggerrange < Persons3::sagexpcounts[actype].mintriggerrange)				//CSB 27Jul00
			Persons3::sagexpcounts[actype].currenttriggerrange = Persons3::sagexpcounts[actype].mintriggerrange;			//CSB 27Jul00
		if(Persons3::sagexpcounts[actype].currenttriggerrange > Persons3::sagexpcounts[actype].maxtriggerrange)				//CSB 27Jul00
			Persons3::sagexpcounts[actype].currenttriggerrange = Persons3::sagexpcounts[actype].maxtriggerrange;			//CSB 27Jul00
																															//CSB 27Jul00
		assert((movecode&-2)!=AUTOSAG_TRACKEXPFOLLOW || fly.expandedsag);													//CSB 27Jul00
	}
}





//////////////////////////////////////////////////////////////////////
//
// Function:    PreExpandSags
// Date:		09/10/00
// Author:		CSB
//
// Description: Expands a number of the SAGs before unpausing
//
//////////////////////////////////////////////////////////////////////
void AirStruc::PreExpandSags(int baseSAGshape)
{
	for(int actype = AEROBATIC_HIGH; actype >= AEROBATIC_LOW; actype--)
	{
		if(baseSAGshape >= SAGB7)
			break;

		bool breakout = false;

		for(int i = 0; (i < ArtInt::ACARRAYSIZE) && (!breakout); i++)
			if((ArtInt::ACArray[i]) && (ArtInt::ACArray[i]->classtype->aerobaticfactor == actype))
			{
				AirStrucPtr ac = ArtInt::ACArray[i];
				for(int j = i + 1; j < ArtInt::ACARRAYSIZE; j++)
				{
					if((ArtInt::ACArray[j]) && (ArtInt::ACArray[j]->shape == ac->shape))
					{
						// copy from, to
						SHAPE.CopyGroup(ac->shape, ShapeNum(baseSAGshape));		//CSB 13Nov00

						ac->shape = ShapeNum(baseSAGshape);
//DeadCode MS 15Nov00 	MUST NOT do this. Take-off aircraft will not be formatted correctly!
//DeadCode MS 15Nov00 						PatchGroupAndAnim();
						baseSAGshape = ShapeNum(baseSAGshape + 1);
						if(baseSAGshape >= SAGB7)
							breakout = true;
						break;
					}
				}
			}
	}



	AirStrucPtr	array[ArtInt::ACARRAYSIZE] = {0};
	float		dist2[ArtInt::ACARRAYSIZE] = {0};

	for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
		if(		(ArtInt::ACArray[i]) && (!ArtInt::ACArray[i]->fly.expandedsag)
			&&	(ArtInt::ACArray[i]->movecode != AUTOSAG_LAST)	)
		{
			array[i] = ArtInt::ACArray[i];
			if(array[i])
			{
				dist2[i] = Persons2::PlayerGhostAC->Distance3DSquared(&array[i]->World);
				if(array[i]->classtype->aerobaticfactor == AEROBATIC_LOW)
					dist2[i] *= 4;
				if((array[i]->movecode == AUTO_COMBAT) || (array[i]->ai.attacker))
					dist2[i] /= 16;
			}
			else
				dist2[i] = -1;
			if(dist2[i] > FP(VISIBLERANGE) * FP(VISIBLERANGE))
			{
				array[i] = NULL;
				dist2[i] = -1;
			}
		}
		else
		{
			array[i] = NULL;
			dist2[i] = -1;
		}

	while(Persons3::SagExpansionCounter::totalexpanded < 3 * MAX_NUM_ACS / 4)
	{
		for(int ac = PT_BRIT_FLYABLE; ac <= PT_GER_NONFLY; ac++)
			if(Persons3::sagexpcounts[ac].numavailable - Persons3::sagexpcounts[ac].numactive < 16)
				for(i = 0; i < ArtInt::ACARRAYSIZE; i++)
					if(array[i])
					{
						PlaneTypeSelect actype = MergeTypes(array[i]->classtype->planetext);
						if(array[i]->classtype->planetext > PT_GER_NONFLY)
							actype = PT_GER_NONFLY;
						if(actype == ac)
						{
							array[i] = NULL;
							dist2[i] = -1;
						}
					}

		int closesti = -1;
		for(i = 0; i < ArtInt::ACARRAYSIZE; i++)
			if(array[i])
			{
				if((closesti == -1) || (dist2[i] < dist2[closesti]))
					closesti = i;
			}
		if(closesti == -1)
			break;
		else
		{
			array[closesti]->ExpandSag();
			if(array[closesti]->fly.expandedsag->movecode == AUTO_COMBAT)
				for(AirStrucPtr ld = array[closesti]->fly.expandedsag; ld; ld = ld->fly.nextflight)
					for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
					{
						const COMBATRADIUS = 50000;

						mobileitem::currworld->RemoveFromWorld(ac);		//RJS 27Oct00

						ac->World.X += Math_Lib.rnd(2 * COMBATRADIUS) - COMBATRADIUS;
						ac->World.Y += Math_Lib.rnd(COMBATRADIUS) - COMBATRADIUS / 2;
						ac->World.Z += Math_Lib.rnd(2 * COMBATRADIUS) - COMBATRADIUS;
						ac->pitch = Angles(ANGLES_315Deg + Math_Lib.rnd(ANGLES_90Deg));
						ac->hdg   = Angles(Math_Lib.rnd(ANGLES_359Deg));
						ac->roll  = Angles(Math_Lib.rnd(ANGLES_359Deg));
						if(ac->ai.unfriendly)
						{
							ac->InterceptandRange(AirStrucPtr(ac->ai.unfriendly));
							ac->pitch = ac->PitchIntercept;
							ac->hdg   = ac->HdgIntercept;
						}

						mobileitem::currworld->AddToWorld(ac);			//RJS 27Oct00
					}

			PlaneTypeSelect actype = MergeTypes(array[closesti]->classtype->planetext);
			if(array[closesti]->classtype->planetext > PT_GER_NONFLY)
				actype = PT_GER_NONFLY;
			Persons3::sagexpcounts[actype].currenttriggerrange = FSqrt(dist2[closesti]);
			array[closesti] = NULL;
			dist2[closesti] = -1;
		}
	}
}


void	SAGAirstruc::SAGWPAction()
{
	ai.LastAction()=waypoint->action;

	if(		(classtype->visible == ME109) && (waypoint->wpname == WP_fighterlimit)						//CSB 23Aug00
		&&	(fly.leadflight) && (fly.leadflight->classtype->aerobaticfactor != AEROBATIC_HIGH)		)	//CSB 23Aug00
		fly.leadflight = NULL;																			//CSB 23Aug00

	if (waypoint->range<METRES5000)
		waypoint=waypoint->NextWP(this);
	//landing and attack are over 5km
	information = IF_OUT_POS;
	manoeuvretime = 0;
}

void	Profile::MoveSAGs()
{
	Math_Lib.ResetRndCount();
	SAGairgrp::MoveAllSAGs();
	info_grndgrp::MoveConvoySAGs();
}
void	info_grndgrp::MoveConvoySAGs()
{
	ItemBasePtr p;
	for (int u=BritBoatBAND;u<PowerStationBAND;u++)
		if ((p=Persons2::ConvertPtrUID(UniqueID(u)))!=NULL)
			if (p->Status.size==MOBILESIZE)
			{
				info_grndgrp* g=*p;
				switch (g->movecode.Evaluate())
				{
				case GOT_UNDEFINED_VAL:
				case GROUND_TAXI:
					TargetConvoy* c=Node_Data[UniqueID(u)];
					g->AutoFollowWP(c);
					c->X=g->World.X;
					c->Z=g->World.Z;
				}
			}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    GroundVisible
// Date:		30/10/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
int		NodeData::GroundVisible(item* trg,int* failedspotter)	
{return GroundVisible(trg->World,failedspotter); }
int		NodeData::GroundVisible(Coords3D& trg,int* failedspotter)
{
	int rv=Art_Int.GroundVisible(trg,failedspotter);
	if (rv)
	{
		TargetGroupPtr tg=operator[](UniqueID(rv));
		if (tg)
		{
			if (tg->truestatus>=Target::TS_NEARLYDESTROYED)
			{
				rv=UID_NULL;

			}
		}

	}
	if (!rv)
		if (*failedspotter && *failedspotter!=IllegalBAND)
		{
			UniqueID primary=UniqueID(*failedspotter);
			for (int slot=0;slot<2;slot++)
			{
				UniqueID probreturn=Art_Int.GetSecondarySpotter(trg,primary,slot);
				if (probreturn)
				{
					TargetGroupPtr tg=operator[](UniqueID(probreturn));
					if (tg->truestatus<Target::TS_NEARLYDESTROYED)
						return probreturn;
				}
			}
		}
	return rv;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    GroundDetection
// Date:		10/03/00
// Author:		DAW
//
//Description: 	Prototype baseclass
//				Sets detection level in raid r
//				Launches responses if a new detection
//				returns true if accellevel should be triggered
//
//////////////////////////////////////////////////////////////////////
struct	GroundDetection
{	virtual	bool	SetDetectionLevel(int p,int s,int r,SAGairgrp* as)=0;	};
//////////////////////////////////////////////////////////////////////
//
// Function:    RAFDetectRAF
// Date:		10/03/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
struct RAFDetectRAF:GroundDetection
{	bool	SetDetectionLevel(int p,int s,int re,SAGairgrp* as)
	{	//Assume RAF can always see own aircraft
		bool	rv=false;
		if (Todays_Packages[p][s].numacleft)
		{
			Todays_Packages[p][s].squaddetected=true;
			Todays_Packages[p][s].playercansee=true;
			Todays_Packages[p].raidnumentries[re].detector=Profile::ACCONTACTBASE;
			if (as->target.Evaluate()!=ENABLE_COMPLEX_VAL && as->target.Evaluate()!=0)
			{	//So that the RAF can see the LW that they have engaged...
				int tp,ts,tr;
				if (Todays_Packages.GetACSquadEntry(UniqueID(as->target.Evaluate()),tp,ts))
				{
					rv=true;
					tr=Todays_Packages[tp].GetRaidIndFromSquadEntry(ts);
					Todays_Packages[tp][ts].squaddetected=true;
					Todays_Packages[tp][ts].playercansee=true;
					Todays_Packages[tp].raidnumentries[tr].detector=Profile::ACCONTACTBASE;
				}
			}

		}
		else
		{
			Todays_Packages[p][s].squaddetected=false;
			Todays_Packages[p][s].playercansee=false;
		}
		return rv;
}	};
//////////////////////////////////////////////////////////////////////
//
// Function:    LWDetectRAF
// Date:		10/03/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
struct LWDetectRAF:GroundDetection
{	bool	SetDetectionLevel(int p,int s,int re,SAGairgrp* as)
	{
		bool	rv=false;
		if (Todays_Packages[p][s].numacleft && as->target.Evaluate()!=ENABLE_COMPLEX_VAL && as->target.Evaluate()!=0)
		{
			Todays_Packages[p][s].squaddetected=true;
			Todays_Packages[p][s].playercansee=true;
			if (Todays_Packages[p].raidnumentries[re].raidnum==0)
			   	Todays_Packages[p].raidnumentries[re].raidnum=++Todays_Packages.nextsortienum;		//RDH 12/04/00
			Todays_Packages[p].raidnumentries[re].detector=Profile::ACCONTACTBASE;
//DeadCode JIM 8Oct00 			int tp,ts,tr;
//DeadCode JIM 8Oct00 			if (Todays_Packages.GetACSquadEntry(UniqueID(as->target.Evaluate()),tp,ts))
//DeadCode JIM 8Oct00 			{
//DeadCode JIM 8Oct00 				tr=Todays_Packages[tp].GetRaidIndFromSquadEntry(ts);
//DeadCode JIM 8Oct00 				Todays_Packages[tp][ts].squaddetected=true;
//DeadCode JIM 8Oct00 					Todays_Packages[tp][ts].playercansee=true;
//DeadCode JIM 8Oct00 				Todays_Packages[tp].raidnumentries[tr].detector=Profile::ACCONTACTBASE;
//DeadCode JIM 8Oct00 			}
			rv=true;

		}
		else
		{
			if (Todays_Packages[p].raidnumentries[re].detector==Profile::NOWLOST)
				Todays_Packages[p][s].squaddetected=false;
//DeadCode JIM 12Nov00 			
//DeadCode JIM 12Nov00 				Todays_Packages[p][s].playercansee=false;
		}
		return rv;
}	};
//////////////////////////////////////////////////////////////////////
//
// Function:    LWDetectLW
// Date:		10/03/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
struct LWDetectLW:GroundDetection
{	bool	SetDetectionLevel(int p,int s,int re,SAGairgrp* as)
	{
		if (Todays_Packages[p][s].numacleft==0)
		{
			Todays_Packages[p][s].playercansee=false;
			Todays_Packages[p][s].squaddetected=false;
			return false;
		}

		bool	rv=false;
		Todays_Packages[p].raidnumentries[re].detector=Profile::ACCONTACTBASE;
		int unseen;	//If the radar site didn't see it, were the RAF patrolling it?
		int seen = Node_Data.GroundVisible(as,&unseen);

		if (seen==UID_NULL)
		{	//ACCEL_RECONNSPD,ACCEL_RAIDSPD
//DeadCode JIM 19Oct00 				if (unseen==IllegalBAND)
//DeadCode JIM 19Oct00 					rv=true;
				if (unseen!=UID_NULL)
				{
					TargetRadarPtr tr=Node_Data[UniqueID(unseen)];
					if (tr&& (tr->mobileunit || tr->patroller))
					{
						ItemBasePtr ir=Persons2::ConvertPtrUID(UniqueID(unseen));
						Float maxdist=METRES15KM*METRES15KM;		//If there is a patrol covering the hole, it has 10 mile radius of visibility
						if (tr->mobileunit)
							maxdist=METRES80KM*METRES80KM;			//If there is a mobile radar then get 50 mile radius
						if (Math_Lib.DistanceSquared(ir->World.X-as->World.X,ir->World.Z-as->World.Z)<maxdist)
							seen=unseen;
					}

				}
		}
		if (unseen)
			rv=true;
		
		Todays_Packages[p][s].playercansee=true;
		Todays_Packages[p][s].squaddetected=true;	//thios is so map always shows as active.
		if (as->target.Evaluate()!=ENABLE_COMPLEX_VAL && as->target.Evaluate()!=0)									//JIM 8Oct00
		{	//So that the LW can see the RAF that they have engaged...					//JIM 8Oct00
			int tp,ts,tr;																//JIM 8Oct00
			if (Todays_Packages.GetACSquadEntry(UniqueID(as->target.Evaluate()),tp,ts))	//JIM 8Oct00
			{																			//JIM 8Oct00
				tr=Todays_Packages[tp].GetRaidIndFromSquadEntry(ts);					//JIM 8Oct00
				Todays_Packages[tp][ts].playercansee=true;
				Todays_Packages[tp][ts].squaddetected=true;								//JIM 8Oct00
				Todays_Packages[tp].raidnumentries[tr].detector=Profile::ACCONTACTBASE;	//JIM 8Oct00
			}																			//JIM 8Oct00
		}																				//JIM 8Oct00
		if (seen!=UID_NULL)
		{
			TargetRadarPtr tr=Node_Data[UniqueID(unseen)];
			if (tr!=NULL && tr->patroller)
			{
				ItemBasePtr ir=Persons2::ConvertPtrUID(UniqueID(unseen));		//If there is a patrol on the detector radar site it gets revectored at 30 miles range
				if (Math_Lib.DistanceSquared(ir->World.X-as->World.X,ir->World.Z-as->World.Z)<METRES50KM*METRES50KM)
					SAGairgrp::SendFighterPatrols(UniqueID(unseen),Todays_Packages[p][s].instance,p,s);
			}
			if (Todays_Packages[p].raidnumentries[re].prevpositions[0].Y==-1)						//DAW 21/03/00
			{																						//DAW 21/03/00
				if (Todays_Packages[p].raidnumentries[re].raidnum==0)								//DAW 21/03/00
					Todays_Packages[p].raidnumentries[re].raidnum=++Todays_Packages.nextraidnum;	//DAW 21/03/00
				Todays_Packages[p].raidnumentries[re].prevpositions[0].Y=0;
				Todays_Packages[p].raidnumentries[re].prevpositions[1].Y=0;
				Todays_Packages[p].raidnumentries[re].prevpositions[2].Y=0;

				if (re && Todays_Packages[p].raidnumentries[0].raidnum)
				{		
				
				}//	Node_Data.intel.AddMessage(IntelMsg::HIGH_SPOTTING_WOMAN,SCRIPT_RAIDSPLITS ,Todays_Packages[p][s].instance,Todays_Packages[p][s].instance);
				else
				{
					//ROD: JUST HERE WE WANT TO AUTO-LAUNCH A RESPONSE (First place of 2)
					info_waypointPtr wp=Persons2::ConvertPtrUID(as->wpref);
					if (	(Todays_Packages[p][s].method<Profile::AM_ESCORTTYPES && wp->uid!=-SGR_WPP_BombRendezvous)
						||	(Todays_Packages[p][s].method>=Profile::AM_ESCORTTYPES && wp->uid!=-SGR_WPP_EscRendezvous)	
						)
						if (!Todays_Packages[p].raidnumentries[re].raidintercepted)
							RAFDirectivesResults::SetRAFIntercept(p,re,false);

					//Node_Data.intel.AddMessage(IntelMsg::HIGH_SPOTTING_WOMAN,SCRIPT_NEWRAID ,Todays_Packages[p][s].instance,Todays_Packages[p][s].instance);
				}
			}
		}
//DeadCode JIM 9Nov00 		else
//DeadCode JIM 9Nov00 			Todays_Packages[p][s].squaddetected=false;
//DeadCode JIM 9Nov00 
		return rv;
}	};
//////////////////////////////////////////////////////////////////////
//
// Function:    RAFDetectLW
// Date:		10/03/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
struct RAFDetectLW:GroundDetection
{	bool	SetDetectionLevel(int p,int s,int re,SAGairgrp* as)
	{  
		if (Todays_Packages[p][s].numacleft==0)
		{
			Todays_Packages[p][s].playercansee=false;
			Todays_Packages[p][s].squaddetected=false;
			return false;
		}
		bool rv=false;
		int unseen;	//If the radar site didn't see it, were the RAF patrolling it?
		int seen = Node_Data.GroundVisible(as,&unseen);
		if (seen==UID_NULL)
		{
//DeadCode JIM 19Oct00 				if (unseen==IllegalBAND)
//DeadCode JIM 19Oct00 					rv=true;
				if (unseen!=UID_NULL)
				{
					TargetRadarPtr tr=Node_Data[UniqueID(unseen)];
					if (tr&& (tr->mobileunit || tr->patroller))
					{
						ItemBasePtr ir=Persons2::ConvertPtrUID(UniqueID(unseen));
						Float maxdist=METRES15KM*METRES15KM;		//If there is a patrol covering the hole, it has 10 mile radius of visibility
						if (tr->mobileunit)
							maxdist=METRES80KM*METRES80KM;			//If there is a mobile radar then get 50 mile radius
						if (Math_Lib.DistanceSquared(ir->World.X-as->World.X,ir->World.Z-as->World.Z)<maxdist)
							seen=unseen;
					}

				}
			//raidnumentries[re].detector=Profile::UNDETECTED;
		}
		if (unseen)
			rv=true;
		if (seen)
		{
			Todays_Packages[p][s].playercansee=true;
			Todays_Packages[p][s].squaddetected=true;
			TargetRadarPtr tr=Node_Data[UniqueID(unseen)];
			if (tr!=NULL && tr->patroller)
			{
				ItemBasePtr ir=Persons2::ConvertPtrUID(UniqueID(unseen));		//If there is a patrol on the detector radar site it gets revectored at 30 miles range
				if (Math_Lib.DistanceSquared(ir->World.X-as->World.X,ir->World.Z-as->World.Z)<METRES50KM*METRES50KM)
					SAGairgrp::SendFighterPatrols(UniqueID(unseen),Todays_Packages[p][s].instance,p,s);
			}
			rv=true;
			if (seen==IllegalBAND)
				Todays_Packages[p].raidnumentries[re].detector=Profile::EYE;
			else
			if (seen>CHRadarBAND)
				Todays_Packages[p].raidnumentries[re].detector=seen-CHRadarBAND+Profile::CHBASE;
			else
				Todays_Packages[p].raidnumentries[re].detector=seen-CLRadarBAND+Profile::CHBASE;
		}
		else
		{
//DeadCode JIM 9Nov00 			Todays_Packages[p][s].playercansee=false;
			Todays_Packages[p][s].squaddetected=false;
		}
		if (as->target.Evaluate()!=ENABLE_COMPLEX_VAL && as->target.Evaluate()!=0)
		{
			Todays_Packages[p][s].playercansee=true;
			Todays_Packages[p][s].squaddetected=true;
			Todays_Packages[p].raidnumentries[re].detector=Profile::ACCONTACTBASE;
		}

		if (Todays_Packages[p].raidnumentries[re].detector!=Profile::UNDETECTED)
			if (Todays_Packages[p].raidnumentries[re].prevpositions[0].Y==-1	)
			{
				//needs to be set before SetRAFIntercept
				if (Todays_Packages[p].raidnumentries[re].raidnum==0)
					Todays_Packages[p].raidnumentries[re].raidnum=++Todays_Packages.nextraidnum;	//RDH 12/04/00

				if (	re && Todays_Packages[p].raidnumentries[0].prevpositions[0].Y!=-1
					&&	!ItemBase::OverFrance(Todays_Packages[p].raidnumentries[0].prevpositions[0])
					)
				{
					Node_Data.intel.AddMessage(IntelMsg::HIGH_SPOTTING_LW_WOMAN,AS_RAID_FORMING,SCRIPT_RAIDSPLITS ,Todays_Packages[p][s].instance,Todays_Packages[p][s].instance,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p].CountRaid(s)));
					Todays_Packages.SplitExistingResponsesTo(p,re);
				}
				else
				{
					info_waypointPtr wp=Persons2::ConvertPtrUID(as->wpref);
					if (	(Todays_Packages[p][s].method<Profile::AM_ESCORTTYPES && wp->uid!=-SGR_WPP_BombRendezvous)
						||	(Todays_Packages[p][s].method>=Profile::AM_ESCORTTYPES && wp->uid!=-SGR_WPP_EscRendezvous)	
						)
						if (!Todays_Packages[p].raidnumentries[re].raidintercepted)
							RAFDirectivesResults::SetRAFIntercept(p,re,false);
					if (Todays_Packages[p].squadlist>2)
						Node_Data.intel.AddMessage(IntelMsg::HIGH_SPOTTING_LW_WOMAN,AS_RAID_FORMING,SCRIPT_NEWRAID ,Todays_Packages[p][s].instance,Todays_Packages[p][s].instance,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p].CountRaid(s)));
					else
						Node_Data.intel.AddMessage(IntelMsg::HIGH_SPOTTING_LW_WOMAN,AS_RAID_FORMING,SCRIPT_NEWRAID ,Todays_Packages[p][s].instance,Todays_Packages[p][s].instance,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p].CountRaid(s)));
				}
//DEADCODE RDH 14/04/00 				if (Todays_Packages[p].raidnumentries[re].raidnum==0)
//DEADCODE RDH 14/04/00 					Todays_Packages[p].raidnumentries[re].raidnum=++Todays_Packages.nextraidnum;	//RDH 12/04/00
				Todays_Packages[p].raidnumentries[re].prevpositions[0].Y=0;
				Todays_Packages[p].raidnumentries[re].prevpositions[1].Y=0;
				Todays_Packages[p].raidnumentries[re].prevpositions[2].Y=0;
			}

		return rv;

}	};

//////////////////////////////////////////////////////////////////////
//
// Function:    MoveAllSAGs
// Date:		10/03/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
int	DEBUGACPACKNUM=0,DEBUGSQNUM=0;
int	DEBUGMOVECODE;
int	DEBUGCOLUMN=2;
int COMBATSHIFT=0;
void	SAGairgrp::MoveAllSAGs(WorldStuff&)
{
	Campaign::AccelType	reqacceltype=Campaign::ACCEL_NONRAIDSPD	;
	if (Campaign::AnyDialogsOpen())
		reqacceltype=Campaign::ACCEL_DIALOGSPEED;

	GroundDetection	*DetectLW,*DetectRAF;
	RAFDetectRAF	RAFDetectRAFinst;
	RAFDetectLW		RAFDetectLWinst;
	LWDetectRAF		LWDetectRAFinst;
	LWDetectLW		LWDetectLWinst;
	if (Todays_Packages.localplayer==NAT_RAF)
	{
		DetectLW=&RAFDetectLWinst;
		DetectRAF=&RAFDetectRAFinst;
	}
	else
	{
		DetectLW=&LWDetectLWinst;
		DetectRAF=&LWDetectRAFinst;
	}

	{for (int p=0;p<Profile::MAX_PACKS;p++)
		if (Todays_Packages[p].raidnumentries)
			for (int r=0;Todays_Packages[p].raidnumentries[r].squadliststart!=Profile::RNEC_LISTVALISLASTREC;r++)
				if (Todays_Packages[p].raidnumentries[r].detector)
					Todays_Packages[p].raidnumentries[r].detector=Profile::NOWLOST;
	}
	for (int p=0;p<Profile::MAX_PACKS;p++)
	{	DEBUGACPACKNUM=p;
		for (int s=0,ms=Todays_Packages[p].squadlist;s<ms;s++)
			if (Todays_Packages[p][s].instance)
			{
				DEBUGSQNUM=s;
//DEADCODE DAW 10/03/00 				if (p==7)
//DEADCODE DAW 10/03/00 					INT3;
				SAGairgrp* as=Persons2::ConvertPtrUID(Todays_Packages[p][s].instance);
				as->MoveSAG(p,s);
				Todays_Packages[p][s].fuelleft-=as->FuelUse(as->World,as->vel.Evaluate(),SECSPERSAGFRAME);
				if(Todays_Packages[p][s].fuelleft < 0)
					Todays_Packages[p][s].fuelleft = 0;
				as->DecideSAG(p,s);	// So you can take over as soon as the decision is made.
				DEBUGMOVECODE=0x102;

				int re=Todays_Packages[p].GetRaidIndFromSquadEntry(s);
				bool changeaccel;
				if (Todays_Packages[p][s].instance)
				{
					if (Todays_Packages[p].attackmethod>=Profile::AM_LWPACKS)
						changeaccel=DetectLW->SetDetectionLevel(p,s,re,as);
					else
						changeaccel=DetectRAF->SetDetectionLevel(p,s,re,as);
					if (changeaccel) //ACCEL_RECONNSPD,ACCEL_RAIDSPD
						if (Todays_Packages[p].attackmethod<=Profile::AM_RECON)
							if (reqacceltype<Campaign::ACCEL_RECONNSPD)
								reqacceltype=Campaign::ACCEL_RECONNSPD;
							else
							{}
						else
							if (reqacceltype<Campaign::ACCEL_RAIDSPD)
								reqacceltype=Campaign::ACCEL_RAIDSPD;
							else
							{}
				}
			}
			
			DEBUGMOVECODE=0x103;
			if (Todays_Packages[p].raidnumentries && Todays_Packages[p].packagestatus!=Profile::PS_COMPLETE)
				for (int r=0;Todays_Packages[p].raidnumentries[r].squadliststart!=Profile::RNEC_LISTVALISLASTREC;r++)
					if (Todays_Packages[p].raidnumentries[r].detector!=Profile::UNDETECTED
						|| (Todays_Packages[p].attackmethod<Profile::AM_LWPACKS)==(Todays_Packages.localplayer==NAT_RAF)
						)
					{
						int s=Todays_Packages[p].raidnumentries[r].squadliststart;
						SAGairgrp* as=Persons2::ConvertPtrUID(Todays_Packages[p][s].instance);
						Todays_Packages[p].raidnumentries[r].prevpositions[3]=Todays_Packages[p].raidnumentries[r].prevpositions[2];
						Todays_Packages[p].raidnumentries[r].prevpositions[2]=Todays_Packages[p].raidnumentries[r].prevpositions[1];
						Todays_Packages[p].raidnumentries[r].prevpositions[1]=Todays_Packages[p].raidnumentries[r].prevpositions[0];
						Todays_Packages[p].raidnumentries[r].prevpositions[0].X=as->World.X;
						Todays_Packages[p].raidnumentries[r].prevpositions[0].Z=as->World.Z;
						if (Todays_Packages[p].raidnumentries[r].prevpositions[0].Y!=-1)
							Todays_Packages[p].raidnumentries[r].prevpositions[0].Y=MMC.currtime;
						if (Todays_Packages[p].raidnumentries[r].prevpositions[0].Y-Todays_Packages[p].raidnumentries[r].prevpositions[1].Y>15*SECSPERMIN)
						if ((Todays_Packages[p].raidnumentries[r].raidnum&31)==(MMC.currtime/SECSPERSAGFRAME))
							Node_Data.intel.AddMessage(IntelMsg::HIGH_SPOTTING_LW_WOMAN,AS_NOTSWITCH,SCRIPT_RAIDUPDATE   ,Todays_Packages[p][s].instance,Todays_Packages[p][s].instance,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p].CountRaid(s)));

				}
		
	}
	if (MMC.curracceltype>MMC.ACCEL_NORMAL)
	{
		MMC.curracceltype=reqacceltype;
//DeadCode CSB 1Aug00 		if (MMC.curraccelrate>1)
		MMC.curraccelrate=MMC.accelrates[reqacceltype];
	}
#ifndef NDEBUG
//TempCode MS 27Oct00 	{
//TempCode MS 27Oct00 		int row=24,col=0;
//TempCode MS 27Oct00 		for (int pack=Profile::MAX_PACKS-1;pack>=0 && row>=0;pack--)
//TempCode MS 27Oct00 			if (Todays_Packages[pack].packagestatus!=Profile::PS_SPARE)
//TempCode MS 27Oct00 			{
//TempCode MS 27Oct00 				int maxs=Todays_Packages[pack].squadlist;
//TempCode MS 27Oct00 				int col=0;
//TempCode MS 27Oct00 				if (Todays_Packages[pack].attackmethod<Profile::AM_LWPACKS)
//TempCode MS 27Oct00 				{
//TempCode MS 27Oct00 					Mono_Text.PrintAt(0,row,UByteP("                              "));
//TempCode MS 27Oct00 					col=30;
//TempCode MS 27Oct00 				}
//TempCode MS 27Oct00 //DeadCode MS 18Oct00 				ULong	numacoriginal:4,			//Unchanged from launch
//TempCode MS 27Oct00 //DeadCode MS 18Oct00 						numacleft:4,				//Left+ditched=original
//TempCode MS 27Oct00 //DeadCode MS 18Oct00 						numacditched:4,
//TempCode MS 27Oct00 //DeadCode MS 18Oct00 						numacrecoveredlow:4,		//these don't go in ditched or reduce left 
//TempCode MS 27Oct00 //DeadCode MS 18Oct00 						numacrecoveredmed:4,		//recoveredmed+recoveredbad+pilotslost<=ditched
//TempCode MS 27Oct00 //DeadCode MS 18Oct00 						numacrecoveredbad:4,		
//TempCode MS 27Oct00 //DeadCode MS 18Oct00 						numpilotslost:4,
//TempCode MS 27Oct00 //DeadCode MS 18Oct00 						leaderlost:1,
//TempCode MS 27Oct00 				for (int si=0;si<maxs && col<120;si++)
//TempCode MS 27Oct00 				{
//TempCode MS 27Oct00 					Profile::Squad & s=Todays_Packages[pack][si];
//TempCode MS 27Oct00 					UByte printable[12];
//TempCode MS 27Oct00 					if (s.method==Profile::AM_PATROL)
//TempCode MS 27Oct00 						printable[0]='P';
//TempCode MS 27Oct00 					elseif (s.method==Profile::AM_INTERCEPT)
//TempCode MS 27Oct00 						printable[0]='I';
//TempCode MS 27Oct00 					elseif (s.method==Profile::AM_RECON)
//TempCode MS 27Oct00 						printable[0]='R';
//TempCode MS 27Oct00 					elseif (s.method<Profile::AM_DETACHED)
//TempCode MS 27Oct00 						printable[0]='B';
//TempCode MS 27Oct00 					elseif (s.method<Profile::AM_ATTACHED)
//TempCode MS 27Oct00 						printable[0]='D';
//TempCode MS 27Oct00 					elseif (s.method<Profile::AM_RETURNESCORT)
//TempCode MS 27Oct00 						printable[0]='A';
//TempCode MS 27Oct00 					else
//TempCode MS 27Oct00 						printable[0]='R';
//TempCode MS 27Oct00 					printable[1]='a'+s.status-Profile::PS_PLANNED;
//TempCode MS 27Oct00 					printable[2]='0'+s.numacoriginal;
//TempCode MS 27Oct00 					printable[3]='0'+s.numacleft;
//TempCode MS 27Oct00 					printable[4]='0'+s.numacditched;
//TempCode MS 27Oct00 					printable[5]='0'+s.numacrecoveredbad;
//TempCode MS 27Oct00 					printable[6]='0'+s.numacrecoveredmed;
//TempCode MS 27Oct00 					printable[7]='0'+s.numacrecoveredlow;
//TempCode MS 27Oct00 					if (*(int*)&printable[4]==*(int*)"0000")
//TempCode MS 27Oct00 					{
//TempCode MS 27Oct00 						printable[4]=' ';
//TempCode MS 27Oct00 						printable[5]=0;
//TempCode MS 27Oct00 						Mono_Text.PrintAt(col,row,printable);
//TempCode MS 27Oct00 						col+=5;
//TempCode MS 27Oct00 					}
//TempCode MS 27Oct00 					else
//TempCode MS 27Oct00 					{
//TempCode MS 27Oct00 						printable[8]=' ';
//TempCode MS 27Oct00 						printable[9]=' ';
//TempCode MS 27Oct00 						printable[10]=0;
//TempCode MS 27Oct00 						Mono_Text.PrintAt(col,row,printable);
//TempCode MS 27Oct00 						col+=10;
//TempCode MS 27Oct00 					}
//TempCode MS 27Oct00 				}
//TempCode MS 27Oct00 				if (col<79)
//TempCode MS 27Oct00 				{
//TempCode MS 27Oct00 					char buffer[81]="                                                                                ";
//TempCode MS 27Oct00 					buffer[79-col]=0;
//TempCode MS 27Oct00 					Mono_Text.PrintAt(col,row,(UByteP)buffer);
//TempCode MS 27Oct00 				}
//TempCode MS 27Oct00 				row--;
//TempCode MS 27Oct00 			}
//TempCode MS 27Oct00 	}

//TempCode JIM 9Nov00 	{
//TempCode JIM 9Nov00 		DEBUGCOLUMN+=COMBATSHIFT;
//TempCode JIM 9Nov00 		if (DEBUGCOLUMN>=80)
//TempCode JIM 9Nov00 			DEBUGCOLUMN=2;
//TempCode JIM 9Nov00 		COMBATSHIFT=0;
//TempCode JIM 9Nov00 
//TempCode JIM 9Nov00 		for (int i=0;i<24;i++)
//TempCode JIM 9Nov00 		{
//TempCode JIM 9Nov00 			info_airgrpPtr ag=Persons2::ConvertPtrUID(UniqueID(SagBAND+i));
//TempCode JIM 9Nov00 			UByte buff[5]={' ',' ',' ',' ',0};
//TempCode JIM 9Nov00 			Profile::Squad* sq;
//TempCode JIM 9Nov00 			if (ag)
//TempCode JIM 9Nov00 			{
//TempCode JIM 9Nov00 				sq=&ag->package->squadlist[0];
//TempCode JIM 9Nov00 				while(sq->instance!=SagBAND+i)
//TempCode JIM 9Nov00 					sq++;
//TempCode JIM 9Nov00 				buff[0]='0'+sq->numacleft;
//TempCode JIM 9Nov00 			}
//TempCode JIM 9Nov00 			Mono_Text.PrintAt(DEBUGCOLUMN,i,buff);
//TempCode JIM 9Nov00 			if (ag)
//TempCode JIM 9Nov00 			{
//TempCode JIM 9Nov00 				if (ag->package->attackmethod<Profile::AM_LWPACKS)
//TempCode JIM 9Nov00 					buff[0]='A'+i;
//TempCode JIM 9Nov00 				else
//TempCode JIM 9Nov00 					buff[0]='a'+i;
//TempCode JIM 9Nov00 				buff[1]='0'+sq->numacoriginal;
//TempCode JIM 9Nov00 			}
//TempCode JIM 9Nov00 			Mono_Text.PrintAt(0,i,buff);
//TempCode JIM 9Nov00 		}
//TempCode JIM 9Nov00 
//TempCode JIM 9Nov00 	}
#endif

}
void	SAGairgrp::MoveSAG(int p,int s)
{
	if (Todays_Packages[p][s].numacleft > Todays_Packages[p][s].numacoriginal)
		INT3 ;
	DEBUGMOVECODE=movecode.Evaluate();
	switch (movecode.Evaluate())
	{
	case	AUTOSAG_WAITTAKEOFF:	SAGMovementWaitTakeOff(p,s);		break;	
	case	AUTOSAG_TAKEOFF:		SAGMovementTakeOff(p,s);			break;
	case	AUTOSAG_FOLLOWWP:		SAGMovementFollowWP(p,s);			break;
	case	AUTOSAG_FOLLOWWPHOME:	SAGMovementFollowWP(p,s);			break;
	case	AUTOSAG_LANDING:		SAGMovementLanding(p,s);			break;
	case	AUTOSAG_REFUELLING:		SAGMovementLanded(p,s);				break;
	case	AUTOSAG_PRECOMBAT:		SAGMovementPreCombat(p,s);			break;
	case	AUTOSAG_COMBAT:			SAGMovementCombat(p,s);				break;
	case	AUTOSAG_COMBATCIRCLES:	SAGMovementCombatCircles(p,s);		break;
	case	AUTOSAG_POSTCOMBAT:		SAGMovementPostCombat(p,s);			break;
	case	AUTOSAG_BOMBAPPROACH:	SAGMovementBombingApproach(p,s);	break;
	case	AUTOSAG_BOMB:			SAGMovementBombing(p,s);			break;
	case	AUTOSAG_TRACKEXPFOLLOW:	SAGMovementTrackExpanded(p,s);		break;
	case	AUTOSAG_TRACKEXPCOMBAT:	SAGMovementTrackExpandedCombat(p,s);break;
	case	AUTOSAG_DESTROYED:		SAGMovementDestroyed(p,s);			break;
	case	AUTOSAG_LAST:			SAGMovementLanded(p,s);			break;
	}
	DEBUGMOVECODE=0x100;
}
void	SAGairgrp::DecideSAG(int p,int s)
{
	DEBUGMOVECODE=-movecode.Evaluate();
	switch (movecode.Evaluate())
	{
	case	AUTOSAG_WAITTAKEOFF:	SAGDecisionWaitTakeOff(p,s);		break;	
	case	AUTOSAG_TAKEOFF:		SAGDecisionTakeOff(p,s);			break;
	case	AUTOSAG_FOLLOWWP:		SAGDecisionFollowWP(p,s);			break;
	case	AUTOSAG_FOLLOWWPHOME:	SAGDecisionFollowWP(p,s);			break;
	case	AUTOSAG_LANDING:		SAGDecisionLanding(p,s);			break;
	case	AUTOSAG_REFUELLING:		SAGDecisionLanded(p,s);				break;
	case	AUTOSAG_PRECOMBAT:		SAGDecisionPreCombat(p,s);			break;
	case	AUTOSAG_COMBAT:			SAGDecisionCombat(p,s);				break;
	case	AUTOSAG_COMBATCIRCLES:	SAGDecisionCombatCircles(p,s);		break;
	case	AUTOSAG_POSTCOMBAT:		SAGDecisionPostCombat(p,s);			break;
	case	AUTOSAG_BOMBAPPROACH:	SAGDecisionBombingApproach(p,s);	break;
	case	AUTOSAG_BOMB:			SAGDecisionBombing(p,s);			break;
	case	AUTOSAG_TRACKEXPFOLLOW:	SAGDecisionTrackExpanded(p,s);		break;
	case	AUTOSAG_TRACKEXPCOMBAT:	SAGDecisionTrackExpandedCombat(p,s);break;
	case	AUTOSAG_DESTROYED:		SAGDecisionDestroyed(p,s);			break;
	case	AUTOSAG_LAST:			SAGDecisionLanded(p,s);			break;
	}
	DEBUGMOVECODE=0x101;
}


//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementWaitTakeOff
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementWaitTakeOff()
{	//do nothing...
}
void	SAGairgrp::SAGMovementWaitTakeOff(int p,int s)
{	//do nothing...
}
void	SAGAirstruc::SAGDecisionWaitTakeOff()
{
	if (timeofday>=waypoint->ETA)
	{
		movecode=AUTOSAG_TAKEOFF;
		WayPointPtr w=waypoint;
		if (w->skipunder==UID_NULL)
			w=w->next;
		else
		{
			while (w->wpname!=WPNAME_BombRendezvous && w->wpname!=WPNAME_EscRendezvous)
				w=w->next;
			if ((duty&PACK_AM_MASK)==PACK_AM_RETURN)
				while (w->wpname!=WPNAME_EscDisperse)
					w=w->next;
			else
				if (duty>=PACK_AM_ESCORT)
					while (w->wpname!=WPNAME_EscRendezvous)
						w=w->next;
		}
		waypoint=w;
		
	}
}
void	SAGairgrp::SAGDecisionWaitTakeOff(int p,int s)
{	
	int remainingtime=MMC.currtime-Todays_Packages[p][s].takeofftime;
	if (remainingtime>-SECSPERSAGFRAME)
	{
		int a,b;
		SquadNum sq;
		if (Todays_Packages[p][s].Squadron().AcType()!=PT_ME109 && !Todays_Packages[p].CalcFuel(s,-3,UID_NULL,a,b))  //JIM 25Oct00
		{
			sq=Todays_Packages[p][s].squadnum;
// deadcode JON		INT3;
			movecode=AUTOSAG_LAST;
			movecode=AUTOSAG_LAST;
			Todays_Packages[p].SquadComplete(s);
			if (Todays_Packages[p].squadlist.AllMainInStatus(Profile::PS_COMPLETE))
			{
//DeadCode JIM 25Oct00 				sq = Todays_Packages[p][s].squadnum;					//RJS 20Oct00

				if ((Todays_Packages[p].attackmethod<Profile::AM_LWPACKS)==(Todays_Packages.localplayer==NAT_RAF))
					Todays_Packages.MessageBoxFuelWarning(p);
				{for (int s=0,m=Todays_Packages[p].squadlist;s<m;s++)
					if (Todays_Packages[p][s].status!=Profile::PS_COMPLETE)
					{
						//movecode=AUTOSAG_LAST;
						Todays_Packages[p].SquadComplete(s);
				}	}
				Todays_Packages[p].PackageComplete(); //UI can recover package...
			}
		}
		else
		{
			if (Todays_Packages[p].attackmethod>=Profile::AM_LWPACKS)
				Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_LW,AS_TAKEOFF,SCRIPT_LWTAKINGOFF  ,uniqueID.count,UID_NULL,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));
			else
				Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_WOMAN,AS_TAKEOFF,SCRIPT_RAFTAKINGOFF  ,uniqueID.count,UID_NULL,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));
			if (Todays_Packages[p][0].diaryentry == -1)		//RJS 27Jan00
			{
				for (int s=0,max=Todays_Packages[p].squadlist;s<max;s++)
					MMC.thisweekreview.Note(Todays_Packages[p][s].Squadron().AcType(),PeriodReview::SORTIES,Todays_Packages[p][s].numacoriginal);
				Squad_Diary.CreateEntry(Todays_Packages,p);	//RJS 27Jan00
			}

			movecode=AUTOSAG_TAKEOFF;
			Todays_Packages[p].packagestatus=Profile::PS_TAKINGOFF;
			Todays_Packages[p][s].SetStatus(Profile::PS_TAKINGOFF);
		
			World=Persons2::ConvertPtrUID(Todays_Packages[p][s].takeoffwp)->World;
		}
	}
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementTakeOff
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementTakeOff()
{
 	Move().AutoTakeOff();
	if(ai.ManStep == PHASE2)
		ai.ManStep = PHASE3;
	if(PatchAppropriate())
	{
		if (duty>=PACK_AM_ESCORT)
			PatchGroupAndAnim(&TakeOff_FormationWing.formationtype,&TakeOff_FormationSquad.formationtype,4);	
		else
			PatchGroupAndAnim(&TakeOff_FormationWing.formationtype,&TakeOff_FormationSquad.formationtype);	
	}
}
void	SAGairgrp::SAGMovementTakeOff(int p,int s)
{
}
void	SAGAirstruc::SAGDecisionTakeOff()
{
}

void	SAGairgrp::SAGDecisionTakeOff(int p,int s)
{
	int	remainingtime=MMC.currtime-(Todays_Packages[p][s].takeofftime+SECSPERMIN*2);
	if (remainingtime>=0)
	{
		if (Todays_Packages[p].attackmethod < Profile::AM_LWPACKS)
			Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_WOMAN,AS_NOTSWITCH,SCRIPT_GC_AIRBORNE  ,uniqueID.count,UID_NULL,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));
		movecode=AUTOSAG_FOLLOWWP;
//DeadCode JIM 20Oct00 		bool	gottakeoff=false;
		Todays_Packages[p][s].SetStatus(Profile::PS_FORMING);
		if (	!Todays_Packages[p].squadlist.AnyInStatus(Profile::PS_TAKINGOFF)	)
			Todays_Packages[p].packagestatus=Profile::PS_FORMING;

		info_waypoint* wp=Persons2::ConvertPtrUID(Todays_Packages[p][s].takeoffwp);
		UniqueID nextwp=wp->NextWP(s);
		if (Todays_Packages[p][s].method>Profile::AM_DETACHED)
		{
			wp=Persons2::ConvertPtrUID(nextwp);
			nextwp=wp->NextWP(s);
		}
		if (Todays_Packages[p][s].method>Profile::AM_RETURNESCORT)
		{
			do{
				nextwp=wp->NextWP(s);
				wp=Persons2::ConvertPtrUID(nextwp);
			}while (	wp->uid.Evaluate()!=-SGR_WPP_EscDisperse
					&&	wp->uid.Evaluate()!=-SGR_WPP_BombDisperse);
		}
		wpref=nextwp;
		assert (wpref);

		World.Y=METRES200;
		position.MakeAbsWorldPos(World.Y);
		position[0][0]=World.X;
		position[0][2]=World.Z;
//		Todays_Packages[p][s].lastwptime=MMC.currtime;
		SAGMovementFollowWP(p,s,remainingtime);

	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    CruiseToWp
// Date:		04/02/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
bool	info_grndgrp::GetCruiseToWp(int seconds,bool escortfighter,bool ignorerange,
/*returned values*/					int& travel,info_waypoint* &wp,	WaypointOffsetSub& wos								
									
									)
{
	assert(wpref==0 || wpref>10);
	wp=Persons2::ConvertPtrUID(wpref);

	AirStruc::GenWaypointOffsetSub(FormationTypeIndex(form.Evaluate()),wos,escortfighter);
	despos=wp->World;	//desired position
	despos.Y+=wos.deltavert;
	int	dtime=wos.deltatime;	//positive is early!					//JIM 25Jul00
	InterceptandRange(&despos);			//angle
	AirStruc::ModifyHdgRangeForFormation(wos.deltahori);
	Range-=Math_Lib.AbsSign(SLong(wos.deltahori));
	if (!ignorerange && wp->range.Evaluate()!=ENABLE_COMPLEX_VAL) 
		Range-=wp->range.Evaluate();
//fix to offset secondary flights. 
//This code is functionally equivalent to the code in InterceptandRangeFindDesPosAndVel
	ANGLES reqpi=PitchIntercept;
	int vel=GetCruiseAt(World,PitchIntercept);
	if (wp->etas.Evaluate()!=ENABLE_COMPLEX_VAL)
	{	//the late flights have negative dtime... early flights have positive dtime
		int duration=wp->etas.Evaluate()-(MMC.currtime+dtime/100);
		if (duration>0 && Range>0 )
		{
			int reqvel=Range/duration;	//JIM 25Oct00
			int	maxvel,minvel=GetMinCruiseVel(vel,&maxvel);
				if (reqpi==PitchIntercept)
					if (reqvel<maxvel && reqvel>minvel)	//can't go faster than cruise!
						vel=reqvel;
					else
						if (reqvel<maxvel)
							reqvel=maxvel;
						else
							reqvel=minvel;
				else
					if (reqvel<vel)
					{
						if (reqvel<minvel)
							reqvel=minvel;
						PitchIntercept=Angles(PitchIntercept+(vel-reqvel)/30);
						vel=reqvel;
					}
			
		}
	}
	Range-=Math_Lib.AbsSign((SLong)wos.deltahori);
	if (!attitude.complex)
		attitude=new RotExpr;
	attitude[1]=HdgIntercept;
	attitude[2]=PitchIntercept;
	this->vel=vel;
	this->hdg=HdgIntercept;
	if (reqpi>PitchIntercept)		//if pitch has been clipped
		Range-=(despos.Y-World.Y);
	if (Range<0)
		Range=0; 
	//If you want I could do a pythagorean comparrison
	//delta alt, wos.deltahori, and waypoint->range are all at right angles, 
	//Range does NOT form the hypotenuse, but the unsquared hypotenuse could be subtracted off
	//This just leaves travel?
	travel=seconds*vel;
	return (travel<=Range);
}
int	info_grndgrp::CruiseToWp(int seconds,bool escortfighter,bool ignorerange)
{
	int	travel;
	info_waypoint* wp;
	WaypointOffsetSub wos;
	if (!wpref)
		return 0;
	assert(wpref>10);

	if (!GetCruiseToWp(seconds,escortfighter,ignorerange,	travel,wp,wos))
	{
		int	ptype=type.Evaluate();
		if (ptype>SQ_LW_START)
			NOP;

		World.X=despos.X;
		World.Z=despos.Z;
		seconds-=Range/vel;
		wp=Persons2::ConvertPtrUID(wp->nextwp);
		if (wp && wp->World.Y!=+ENABLE_COMPLEX_VAL)
			InterceptandRange(&wp->World);			//angle
		this->hdg=HdgIntercept;
		double s,c;
		Math_Lib.high_sin_cos(HdgIntercept,s,c);
		World.X+=c* wos.deltahori;
		World.Z-=s* wos.deltahori;
		position.MakeAbsWorldPos(World.Y);
		position[0][0]=World.X;
		position[0][2]=World.Z;
	assert(wpref==0 || wpref>10);
		return seconds;
	}
	else
	{
		Float sh,ch,sp,cp;
		Math_Lib.high_sin_cos(HdgIntercept,sh,ch);
		Math_Lib.high_sin_cos(PitchIntercept,sp,cp);
		World.Y+=travel*sp;
		travel*=cp;
		World.Z+=travel*ch;
		World.X+=travel*sh;
		position.MakeAbsWorldPos(World.Y);
		position[0][0]=World.X;
		position[0][2]=World.Z;
	assert(wpref==0 || wpref>10);
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    GetCruiseAt
// Date:		25/07/00
// Author:		JIM
//
//Description: 	//returns cm per second...
//				Can modify PitchIntercept to account for max climb rate
//
//////////////////////////////////////////////////////////////////////
int	info_grndgrp::GetCruiseAt(Coords3D& pos,ANGLES& pitchintercept)  //returns cm per second...
{
	int	ptype=type.Evaluate();
	if (ptype>SQ_BR_START)
		ptype=Node_Data[SquadNum(ptype)].AcType();
	PlaneInit* pi=Plane_Type_Translate[ptype];
	WheeledType* wi=(WheeledType*)pi;
	DumbPlaneType* dp=(DumbPlaneType*)wi;
	if (&pitchintercept!=NULL && pitchintercept>ANGLES_1Deg)
	{
		pitchintercept=wi->bestclimbpitch;
		pitchintercept = Angles(SWord(FP(pitchintercept) * (1.0 - FP(pos.Y) / FP(dp->abs_ceiling))));
		return	wi->bestclimbvel/VEL_1CMS;
	}
	else
		return wi->cruisevel/VEL_1CMS;
}
int	info_grndgrp::GetMinCruiseVel(int cuisevel,int* getmaxaswell)  //returns cm per second...
{
 	int	ptype=type.Evaluate();
	if (ptype>SQ_BR_START)
		ptype=Node_Data[SquadNum(ptype)].AcType();
	PlaneInit* pi=Plane_Type_Translate[ptype];
	WheeledType* wi=(WheeledType*)pi;
	DumbPlaneType* dp=(DumbPlaneType*)wi;
	if (getmaxaswell)
	{
		*getmaxaswell=(wi->maxvel*2/VEL_1CMS+cuisevel)/3;
	}
	if (ptype==PT_ME109 || ptype==PT_ME110)
		return (wi->minvel*4/VEL_1CMS+cuisevel)/5;
	else
		return (wi->minvel*2/VEL_1CMS+cuisevel)/3;


}
int	info_grndgrp::GetMinVel(int* getmaxaswell)  //returns cm per second...
{
 	int	ptype=type.Evaluate();
	if (ptype>SQ_BR_START)
		ptype=Node_Data[SquadNum(ptype)].AcType();
	PlaneInit* pi=Plane_Type_Translate[ptype];
	WheeledType* wi=(WheeledType*)pi;
	DumbPlaneType* dp=(DumbPlaneType*)wi;
	if (getmaxaswell)
		*getmaxaswell=wi->maxvel/VEL_1CMS;
	return wi->minvel/VEL_1CMS;
}


int	SAGairgrp::FuelUse(Coords3D& pos,int velumcs,int timesecs)
{	//returns in centigrammes	 //vel can be ENABLE_COMPLEX_VAL->0
	int rate = 0;
	switch(movecode)
	{
		case	AUTOSAG_FIRST:			rate = 0;	break;
		case	AUTOSAG_FOLLOWWPHOME:	rate = 75;	break;
		case	AUTOSAG_REFUELLING:		rate = 0;	break;
		case	AUTOSAG_COMBATCIRCLES:	rate = 100;	break;
		case	AUTOSAG_POSTCOMBAT:		rate = 75;	break;
		case	AUTOSAG_BOMBAPPROACH:	rate = 75;	break;
		case	AUTOSAG_DESTROYED:		rate = 0;	break;
		case	AUTOSAG_TRACKEXPFOLLOW:	rate = 0;	break;
		case	AUTOSAG_TRACKEXPCOMBAT:	rate = 0;	break;
		case	AUTOSAG_LAST:			rate = 0;	break;
		case	AUTOSAG_WAITTAKEOFF:   	rate = 0;	break;
		case	AUTOSAG_TAKEOFF:		rate = 90;	break;
		case	AUTOSAG_FOLLOWWP:		rate = 75;	break;
		case	AUTOSAG_LANDING:		rate = 10;	break;
		case	AUTOSAG_PRECOMBAT: 		rate = 100;	break;
		case	AUTOSAG_COMBAT:			rate = 100;	break;
		case	AUTOSAG_BOMB:			rate = 75;	break;
		case	AUTOSAG_DEATHGLIDE:		rate = 0;	break;
	}
	
	int	ptype=type.Evaluate();
	if (ptype>SQ_BR_START)
		ptype=Node_Data[SquadNum(ptype)].AcType();
	PlaneInit* pi=Plane_Type_Translate[ptype];
	WheeledType* wi=(WheeledType*)pi;
	DumbPlaneType* dpt = (DumbPlaneType*)wi;
	PlaneType* pt = (PlaneType*)dpt;

	int usage = wi->fuelaboff * timesecs * rate;

	if(pt->version == 2)
		usage = (usage * 65) / 100;

//DeadCode CSB 13Jul00 	if((&pitchintercept != NULL) && (pitchintercept > ANGLES_1Deg))
//DeadCode CSB 13Jul00 		usage = wi->fuelaboff * timesec * 900;
//DeadCode CSB 13Jul00 	else if((&pitchintercept != NULL) && (-pitchintercept > ANGLES_1Deg))
//DeadCode CSB 13Jul00 		usage = wi->fuelaboff * timesec * 100;

	return(usage);	
//DeadCode CSB 13Jul00 	return 1000;	
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SendFighterPatrols
// Date:		29/06/00
// Author:		JIM
//
//Description: Any fighter patrols on this target should now intercept bombers
//
//////////////////////////////////////////////////////////////////////
bool	SAGairgrp::SendFighterPatrols(UniqueID packtrg,UniqueID instance,int pt,int st)
{
	for (int pp=0;pp<Profile::MAX_PACKS;pp++)
		if (	Todays_Packages[pp].attackmethod==Profile::AM_PATROL 
			&&	Todays_Packages[pp].packagestatus==Profile::PS_TARGETAREA 
			&&	packtrg == (UniqueID)Todays_Packages[pp].packagetarget[0]
			)
		{	//Divert this patrol...
			Todays_Packages[pp].packagestatus=Profile::PS_DETAILRAID;
			Todays_Packages[pp].packagetarget[1]=instance;			//RDH 16Sep00
			for (int sp=0,spmax=Todays_Packages[pp].squadlist;sp<spmax;sp++)
			{	
				Todays_Packages[pp][sp].status=Profile::PS_DETAILRAID;	//RDH 16Sep00
				info_airgrpPtr ag=Persons2::ConvertPtrUID(Todays_Packages[pp][sp].instance);
				ag->movecode=AUTOSAG_PRECOMBAT;
				int ns=-1;
//DeadCode RJS 12Nov00 				if (Todays_Packages[pt][st].status>=Profile::PS_ACTIVE_MAX)
//DeadCode RJS 12Nov00 					for (int st=Todays_Packages[pt].squadlist.Max()-1;st>=0;st--)
//DeadCode RJS 12Nov00 						if (Todays_Packages[pt][st].status<Profile::PS_ACTIVE_MAX && Todays_Packages[pt][st].status>Profile::PS_TAKINGOFF)
//DeadCode RJS 12Nov00 							instance=Todays_Packages[pt][ns=st].instance;
//DeadCode RJS 12Nov00 				if (ns==-1)
//DeadCode JIM 11Nov00 				if (Todays_Packages[pt][st].status>=Profile::PS_ACTIVE_MAX)	
				if (Todays_Packages[pt][st].status>=Profile::PS_ACTIVE_MAX)
					for (st=Todays_Packages[pt].squadlist.Max()-1;st>=0;st--)
						if (Todays_Packages[pt][st].status<Profile::PS_ACTIVE_MAX && Todays_Packages[pt][st].status>Profile::PS_TAKINGOFF)
							instance=Todays_Packages[pt][ns=st].instance;
				if (ns==-1 && st==-1)
				{INT3;}
				else
					ag->target=instance;	//this's UID
			}
//DeadCode JIM 12Sep00 			AccelSwitches as = AS_LARGE_ENGAGEMENT;
//DeadCode JIM 12Sep00 			if (Todays_Packages[pt].squadlist <= 2)
//DeadCode JIM 12Sep00 				as = AS_SMALL_ENGAGEMENT;																	
//DeadCode JIM 12Sep00 			Node_Data.intel.AddMessage(IntelMsg::HIGH_ENGAGEMENT_WOMAN,as,SCRIPT_INTERCEPTING  ,Todays_Packages[pp][0].instance,instance,TargetIndexes(Todays_Packages[pp][0].squadnum,Todays_Packages[pt][st].numacleft));
//DeadCode JIM 12Sep00 			Node_Data.intel.AddMessage(IntelMsg::HIGH_ENGAGEMENT_LW,as,SCRIPT_INTERCEPTED  ,instance,Todays_Packages[pp][0].instance,TargetIndexes(Todays_Packages[pt][st].squadnum,Todays_Packages[pp][0].numacleft));
			return true;
		}
	return false;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementFollowWP
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	info_grndgrp::AutoFollowWP(TargetConvoy* c)
{
	info_waypoint* wp=Persons2::ConvertPtrUID(wpref);
	if (wp->World.Y==+ENABLE_COMPLEX_VAL)
		wp->position.EvalW(wp->World);
	int sparesecs=SECSPERSAGFRAME;
	if ((sparesecs=CruiseToWp(sparesecs,false))!=0)							//RDH 13/03/00
	{
		info_waypoint* wp=Persons2::ConvertPtrUID(wpref);
		wpref=wp->nextwp;
		c->wpnum++;
		if (wpref==UID_NULL)
		{
			movecode=AUTO_NOPPILOT;

//DEADCODE RDH 13/03/00 			break;
		}
	}
	c->X=World.X;
	c->Z=World.Z;

}
void	SAGAirstruc::SAGMovementFollowWP()
{
	Move().AutoFollowWp();
	if(PatchAppropriate())
		PatchGroupAndAnim();
}
void	SAGairgrp::SAGMovementFollowWP(int p,int s)
{
	SAGMovementFollowWP(p,s,SECSPERSAGFRAME);
}

info_airgrp*	SAGairgrp::GetValidEscortee(int p,int s)
{
	info_airgrp* escortee=NULL;
	bool	amwingsquad=false;
	int es=-1;
	//Is there someone I can escort?
	{	
 		UniqueID lu=UID_NULL;
		if (s!=0)
			if (leader.Evaluate()!=ENABLE_COMPLEX_VAL && leader.Evaluate()!=UID_NULL)
			{
				lu=UniqueID(leader.Evaluate());
				if (Todays_Packages[p][s].squadnum==Todays_Packages[p][s-1].squadnum)
					if (!(	(Todays_Packages[p][s].method&Profile::AM_GROUPMASK)==Profile::AM_ATTACHED
						||	(Todays_Packages[p][s].method&Profile::AM_GROUPMASK)==Profile::AM_RETURNESCORT	
						))
						amwingsquad=true;
//DeadCode JIM 13Nov100 					else
//DeadCode JIM 13Nov100 					{NOP;}
//DeadCode JIM 13Nov100 				else
//DeadCode JIM 13Nov100 				{NOP;}
				for (es=0;Todays_Packages[p][es].instance!=lu;es++)
					assert (es!=s,"Escortee must be before escort");
			}
		if (lu)
			escortee=Persons2::ConvertPtrUID(lu);
	}

	//Is it sensible to escort them right now?
	if (escortee && escortee->movecode.Evaluate()!=movecode.Evaluate()	)
		escortee=NULL;
	if (escortee && Todays_Packages[p][es].status!=Todays_Packages[p][s].status	)
		escortee=NULL;
	UniqueID wpu=wpref;
	if (wpu==UID_NULL && escortee!=NULL)
		NOP;
//DeadCode JIM 14Nov00 		wpref=wpu=Todays_Packages[p][s].landingwp;
	assert (wpref==0 || wpref>10);
	if (escortee && wpu!=escortee->wpref && Todays_Packages[p][s].Squadron().AcType()==PT_ME109)
	{	//these are in the order of 'ease of test'
		info_waypoint* wp=Persons2::ConvertPtrUID(wpu);
		if (wp->uid.Evaluate()==-SGR_WPC_FighterLimit)
			escortee=NULL;
	}

	if (escortee)
	forever
	{
		info_waypoint* wp=Persons2::ConvertPtrUID(wpu);
		if (!wp)
		{
			escortee=NULL;
			break;
		}
		else
		if (!amwingsquad)
			if (	(wp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)	//on way home
				||	(wp->applyflight.Evaluate()!=ENABLE_COMPLEX_VAL)	//over target
				||	(wp->uid.Evaluate()==-SGR_WPP_EscRendezvous && (Todays_Packages[p][s].method&Profile::AM_GROUPMASK)!=Profile::AM_LWPACKS)
				||	(wp->uid.Evaluate()==-SGR_WPP_BombRendezvous)	//taking off
				||	(wp->uid.Evaluate()==-SGR_WPC_FighterLimit && Todays_Packages[p][s].Squadron().AcType()==PT_ME109)
				)
			{
				escortee=NULL;
				break;
			}
			else
			{}
		else
			if (	wp->applygroup.Evaluate()!=ENABLE_COMPLEX_VAL
				)

 			{
				escortee=NULL;
				break;
			}

		if (wpu!=escortee->wpref)
		{
			wpu=wp->NextWP(s,Todays_Packages[p][s].WaveNum());
			wp=Persons2::ConvertPtrUID(wpu);
		}
		else
		{
			wpref=wpu;
			assert (wpref || Todays_Packages[p][s].method<Profile::AM_RETURNESCORT);
			break;
		}
	}
	return	escortee;
}
int DEBUGWPACTION;
void	SAGairgrp::SAGExecuteWaypoint(int p,int s)
{	
	info_waypoint* wp=Persons2::ConvertPtrUID(wpref);
	UniqueID nextwpuid=wp->NextWP(s,Todays_Packages[p][s].WaveNum());
	DEBUGWPACTION=-wp->uid.Evaluate();
	switch (wp->uid.Evaluate())
	{
	case -SGR_WPP_BombRendezvous:
	case -SGR_WPP_EscRendezvous:
	{
		Todays_Packages[p][s].SetStatus(Profile::PS_INCOMING);
		if (	Todays_Packages[p].squadlist.AllInStatus(Profile::PS_INCOMING))
			Todays_Packages[p].packagestatus=Profile::PS_INCOMING;
		int	re=Todays_Packages[p].GetRaidIndFromSquadEntry(s);
		if (Todays_Packages[p].attackmethod>=Profile::AM_LWPACKS && Todays_Packages[p][s].squaddetected)
		{
			Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_WOMAN,AS_RAID_FORMING,SCRIPT_RAIDUPDATE  ,Todays_Packages[p][s].instance,Todays_Packages[p][s].instance,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p].CountRaid(s)));
			if (!Todays_Packages[p].raidnumentries[re].raidintercepted)
			{
				RAFDirectivesResults::SetRAFIntercept(p,re,false);
				Todays_Packages[p].raidnumentries[re].raidintercepted=true;
			}

		}
	}
	break;
//DeadCode JIM 24Sep00 	case -SGR_WPP_Target:
//DeadCode JIM 24Sep00 	case -SGR_WPC_Target:
//DeadCode JIM 24Sep00 	{
//DeadCode JIM 24Sep00 		nextwpuid=wpref;
//DeadCode JIM 24Sep00 	}
//DeadCode JIM 24Sep00 	break;
	case -SGR_WPP_IP:
	{

		if (Todays_Packages[p][s].method==Profile::AM_INTERCEPT)
		{
			if ((UniqueID)Todays_Packages[p].packagetarget[0]&(UID_BIT14+UID_BIT15))
			{	//Target has landed. Go home.
				
				while (wp->uid.Evaluate()!=-SGR_WPP_Egress)
				{
					nextwpuid=wp->NextWP(s);
					wp=Persons2::ConvertPtrUID(nextwpuid);
				}
			}
			else
			{
				Squad_Diary.ArrivedAtTarget(Todays_Packages[p][s].diaryentry,&Persons2::ConvertPtrUID(Todays_Packages[p].SquadTarget(s)));	//RJS 4Sep00
				Todays_Packages[p].packagestatus=Profile::PS_DETAILRAID;
				Todays_Packages[p][s].SetStatus(Profile::PS_DETAILRAID);
//DeadCode JIM 12Sep00 				Todays_Packages[p].packagestatus=Profile::PS_ENEMYSIGHTED;
//DeadCode JIM 12Sep00 				Todays_Packages[p][s].SetStatus(Profile::PS_ENEMYSIGHTED);
//DeadCode JIM 12Sep00 				if (Persons2::ConvertPtrUID(Todays_Packages[p].packagetarget[0]))
//DeadCode JIM 12Sep00 				{
//DeadCode JIM 12Sep00 					int pt,st;Todays_Packages.GetACSquadEntry(Todays_Packages[p].packagetarget[0],pt,st);
//DeadCode JIM 12Sep00 					AccelSwitches as = AS_LARGE_ENGAGEMENT;
//DeadCode JIM 12Sep00 					if (Todays_Packages[pt].squadlist <= 2)
//DeadCode JIM 12Sep00 						as = AS_SMALL_ENGAGEMENT;																	
//DeadCode JIM 12Sep00 					Node_Data.intel.AddMessage(IntelMsg::HIGH_ENGAGEMENT_WOMAN,as,SCRIPT_INTERCEPTING  ,uniqueID.count,Todays_Packages[p].packagetarget[0],TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));
//DeadCode JIM 12Sep00 					Node_Data.intel.AddMessage(IntelMsg::HIGH_ENGAGEMENT_LW,as,SCRIPT_INTERCEPTED  ,Todays_Packages[p].packagetarget[0],uniqueID.count,TargetIndexes(Todays_Packages[pt][st].squadnum,Todays_Packages[p][s].numacleft));
//DeadCode JIM 12Sep00 				}
			}
		}
		else 
		if (Todays_Packages[p][s].method==Profile::AM_PATROL)
		{
			Squad_Diary.ArrivedAtTarget(Todays_Packages[p][s].diaryentry,&Persons2::ConvertPtrUID(Todays_Packages[p].SquadTarget(s)));	//RJS 4Sep00
			Todays_Packages[p].packagestatus=Profile::PS_INPOSITION;
			Todays_Packages[p][s].SetStatus(Profile::PS_INPOSITION);
			if (Node_Data[Todays_Packages[p].packagetarget[0]]==Target::TSS_TargetRadar)
				TargetRadarPtr(Node_Data[Todays_Packages[p].packagetarget[0]])->patroller=true;
		}

		else  
		if (Todays_Packages[p][s].method>=Profile::AM_LWPACKS)
		{
			Squad_Diary.ArrivedAtTarget(Todays_Packages[p][s].diaryentry,&Persons2::ConvertPtrUID(Todays_Packages[p].SquadTarget(s)));	//RJS 4Sep00
			Todays_Packages[p].packagestatus=Profile::PS_TARGETAREA;
			//need to id target types
			UniqueID targ=Todays_Packages[p].SquadTarget(s);
			if (Todays_Packages[p][s].status!=Profile::PS_TARGETAREA)
			{
				ScriptTables script=SCRIPT_TARGETCONFIRMED;
				if (Todays_Packages.localplayer	== NAT_RAF)
				{
					switch (Persons2::getbandfromUID(targ))
					{
					case CLRadarBAND:
					case CHRadarBAND:
						script=SCRIPT_RDFUNDERATTACK;	
					break;
					case RAF_FighterAFBAND:
						script=SCRIPT_AIRFIELDUNDERATTACK;
//DEADCODE RDH 31/05/00 							if (Node_Data[targ]==Target::TSS_TargetSectorField)
//DEADCODE RDH 31/05/00 							{
//DEADCODE RDH 31/05/00 								TargetSectorField* t=Node_Data[targ];
//DEADCODE RDH 31/05/00 	#pragma warnmsg ("TINHATS!!!")
//DEADCODE RDH 31/05/00 	//DEADCODE JON 5/9/00 							if (t->primarycontrolcentre && t->secondarycontrolcentre)
//DEADCODE RDH 31/05/00 	//DEADCODE JON 5/9/00 								script=SCRIPT_TINHATS;
//DEADCODE RDH 31/05/00 							}
					break;
					}
				}
				int targnum=Todays_Packages[p][s].targetindex;
				if (targnum>=0 && Todays_Packages[p].attackmethod!=Profile::AM_RECON)
					Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_LW_WOMAN,AS_TARG,script  ,uniqueID.count,Todays_Packages[p].packagetarget[targnum],TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p].CountRaid(s)));
			}
			Todays_Packages[p][s].SetStatus(Profile::PS_TARGETAREA);
			


		}
		Todays_Packages[p].RemakeRaidList(true,true);
	}
	break;
	case -SGR_WPP_Egress:
	{
		Todays_Packages[p][s].SetStatus(Profile::PS_OUTGOING);
		movecode=AUTOSAG_FOLLOWWPHOME;
		if (Todays_Packages[p].squadlist.AllInStatus(Profile::PS_OUTGOING))
			Todays_Packages[p].packagestatus=Profile::PS_OUTGOING;
	}
	break;
	case -SGR_WPP_EscDisperse:
	{
		Squad_Diary.SetDisperseTime(Todays_Packages[p][s].diaryentry);	//use view time

		Todays_Packages[p].RemakeRaidList(false,true);
		UniqueID wpref=UID_NULL;
		if (	Todays_Packages[p][s].method>=Profile::AM_DETACHED	)
			if (Todays_Packages[p][s].method<Profile::AM_RETURNESCORT)
				do{
					wpref=wp->NextWP(s);
					wp=Persons2::ConvertPtrUID(wpref);
				}while (wpref && wp->uid.Evaluate()!=-SGR_WPP_BombDisperse);
			else
			{
				movecode=AUTOSAG_FOLLOWWPHOME;
				Todays_Packages[p][s].status=Profile::PS_OUTGOING;
				if (Todays_Packages[p].squadlist.AllInStatus(Profile::PS_OUTGOING))
					Todays_Packages[p].packagestatus=Profile::PS_OUTGOING;
			}
		if (wpref)
		{
			nextwpuid=wp->NextWP(s);
		}
	}
	break;
	case -SGR_WPP_BombDisperse:
	{
		Squad_Diary.SetDisperseTime(Todays_Packages[p][s].diaryentry);//RJS 01Mar00
	}
	break;
	case -SGR_WPC_PatrolE:
	{
		int trgnum=Todays_Packages[p][s].WaveNum();
		UniqueID nextwpref=wp->NextWP(s,trgnum);
		info_waypoint* nextwp=Persons2::ConvertPtrUID(nextwpref);
		//bootstrap a value in
		if (nextwp->etas.Evaluate()==ENABLE_COMPLEX_VAL)
			nextwp->etas=MMC.currtime+SECSPERHR;

		if (MMC.currtime<nextwp->etas.Evaluate())
		{
			//Find wp before start patrol waypoint!
			UniqueID sp=Todays_Packages[p].route;
			info_waypointPtr test;
			while (sp && (sp!=wpref))									//RJS 16Nov00
			{
				test=Persons2::ConvertPtrUID(sp);
				if (test->uid.Evaluate()==-SGR_WPC_PatrolS)
					nextwpuid=sp;
				sp=test->NextWP(s,trgnum);
			}
		}
		else
		{
			Todays_Packages[p][s].SetStatus(Profile::PS_OUTGOING);
			movecode=AUTOSAG_FOLLOWWPHOME;
		}

	}

	break;
	case -SGR_WPC_FighterLimit:
	{
		if (Todays_Packages[p][s].method>=Profile::AM_ESCORTTYPES)
		if (Todays_Packages[p][s].Squadron().AcType()==PT_ME109)	//RDH 28Jun00
		{	int name;
		Todays_Packages[p][s].submethod=Profile::SubMethod(Todays_Packages[p][s].submethod|Profile::SM_109RETURNING);
			Todays_Packages[p].RemakeRaidList(false,true);
			while (name=wp->uid.Evaluate(),(name!=-SGR_WPP_EscDisperse && name!=-SGR_WPP_BombDisperse))
			{
				nextwpuid=wp->NextWP(s);
				wp=Persons2::ConvertPtrUID(nextwpuid);
			}
			movecode=AUTOSAG_FOLLOWWPHOME;
			Todays_Packages[p][s].SetStatus(Profile::PS_OUTGOING);
			if (leader.Evaluate())
			{
				UniqueID esc=UniqueID(leader.Evaluate());
				if ( !	(	(s>=1 && Todays_Packages[p][s-1].instance==esc && Todays_Packages[p][s-1].squadnum==Todays_Packages[p][s].squadnum)
						||	(s>1 && Todays_Packages[p][s-2].instance==esc && Todays_Packages[p][s-2].squadnum==Todays_Packages[p][s].squadnum)
					)	)
					leader=UID_NULL;
			}
		}
	}
	//INTENTIONAL FALL-THROUGH!

	case -SGR_WPP_DogLeg:
	default:	
	{
		UniqueID wpref2=wp->NextWP(s,SGR_Pack_BlankZero);
		if (wpref2)
		{
			info_waypointPtr	wp2=Persons2::ConvertPtrUID(wpref2);
			if (wp2->uid.Evaluate()==-SGR_WPP_IP && Todays_Packages[p].attackmethod>=Profile::AM_LWPACKS)
			{
				int raidind=Todays_Packages[p].GetRaidIndFromSquadEntry(s);
				Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_WOMAN,AS_COAST,SCRIPT_NEARTARGET   ,uniqueID.count,Todays_Packages[p].packagetarget[0],TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));
				Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_LW,AS_COAST,SCRIPT_LWNEARTARGET   ,uniqueID.count,Todays_Packages[p].packagetarget[0],TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));

				int ti=Todays_Packages[p][s].targetindex;
				if (ti<0)
					ti=0;
				UniqueID packtrg = Todays_Packages[p].packagetarget[ti];//ok... Bombers are approaching target area
				SendFighterPatrols(packtrg,Todays_Packages[p][s].instance,p,s);
				if (!Todays_Packages[p].raidnumentries[raidind].raidintercepted)
				{
					RAFDirectivesResults::SetRAFIntercept(p,raidind,true);
				}
			}
		}
	}

	}
//DEADCODE RDH 29/03/00 			wpu=wp->NextWP(s,Todays_Packages[p][s].WaveNum());
	if (nextwpuid==UID_NULL)
	{
		movecode=AUTOSAG_LANDING;
		if (Todays_Packages[p].attackmethod>=Profile::AM_LWPACKS)
			Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_LW,AS_LAND,SCRIPT_GESCHWADERLANDING  ,uniqueID.count,UID_NULL,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));
		else
			Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_WOMAN,AS_LAND,SCRIPT_RAFLANDING  ,uniqueID.count,UID_NULL,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));

		Todays_Packages[p][s].lastwptime=MMC.currtime;
		Squad_Diary.SetLandingTime(Todays_Packages[p][s].diaryentry);	//use view time
	}
	else
		wpref=nextwpuid;
	assert (wpref || Todays_Packages[p][s].method<Profile::AM_RETURNESCORT);
	DEBUGWPACTION=0x100;

}

void	SAGairgrp::SAGMovementFollowWP(int p,int s,int sparesecs)
{
	//Need to work out whether I am in an escort role and in position
	assert(wpref==0 || wpref>10);
	info_airgrp* escortee=GetValidEscortee(p,s);
	assert(wpref==0 || wpref>10);
//DeadCode JIM 20Oct00 	info_waypoint* wp=Persons2::ConvertPtrUID(wpref);
	assert (wpref || Todays_Packages[p][s].method<Profile::AM_RETURNESCORT);
	if (escortee==NULL)
	{
		int lastmove=movecode.Evaluate();
		bool isescortfighter=((Todays_Packages[p][s].method&Profile::AM_GROUPMASK)==Profile::AM_ATTACHED);
		if ((sparesecs=CruiseToWp(sparesecs,isescortfighter,false))!=0 && movecode.Evaluate()==lastmove)
		{ //IMPORTANT... MUST NOT GO THROUGH 2 WAYPOINTS IN 1 ACTION!!!
	assert(wpref==0 || wpref>10);
			Todays_Packages[p][s].lastwptime=MMC.currtime-sparesecs;
			SAGExecuteWaypoint(p,s);
	assert(wpref==0 || wpref>10);
			sparesecs=CruiseToWp(sparesecs,isescortfighter,true);
	assert(wpref==0 || wpref>10);
			if (sparesecs)
				NOP;
		}
	assert (wpref || Todays_Packages[p][s].method<Profile::AM_RETURNESCORT);
	}
	else
		FlyAsEscort(escortee,p,s);
	assert (wpref || Todays_Packages[p][s].method<Profile::AM_RETURNESCORT);
//DeadCode JIM 24Sep00 	Mono_Text.Print(UByteP(")FWP"));
}

void	SAGairgrp::FlyAsEscort(info_airgrp* escortee,int p,int s)
{	//flying as escort
//		info_waypoint* wp=Persons2::ConvertPtrUID(wpref);
//		despos=wp->World;	//desired position
//		escortee->InterceptandRange(&despos);			//angle
	assert (wpref || Todays_Packages[p][s].method<Profile::AM_RETURNESCORT);
	HdgIntercept=escortee->hdg;
	FormationTypeIndex formationtype=Todays_Packages[p][s].formtype;
	int formationpos = (formationtype&(FORMTYPE_INTERCHILD))>> FORMTYPE_INTERCHILD_SH;
	FormationType* formtype=GetEscortTable(formationtype);
	COORDS3D* np=Formation_xyz(HdgIntercept,formtype,formationpos);
	*np+=escortee->World;
	World=*np;
	position.MakeAbsWorldPos(World.Y);
	position[0][0]=World.X;
	position[0][2]=World.Z;
	this->vel=escortee->vel.Evaluate();
	this->hdg=HdgIntercept;
	assert (wpref || Todays_Packages[p][s].method<Profile::AM_RETURNESCORT);
}



void	SAGAirstruc::SAGDecisionFollowWP()
{
//DeadCode CSB 17Jul00 	PatchGroupAndAnim();	//reset heading! Should arrange to do 1 flight per frame
	switch (ai.LastAction())
	{	//This can include dummy actions to initiate combat
	case	wpacnoactionno:	return;/*no action*/						//CSB 24Jul00
	case	wpatakeoffno:	/*won't happen*/					break;
	case	wpacircleno:	/*doesn't*/							break;
	case	wpalandingno:		SetLanding();					break;//RJS 29Feb00
	case	wpdisperseno:		SetDisperse();					break;	//RJS 29Feb00
	case	wpstartloopno:		SetBreakLoop(false);			break;
	case	wpbreakloop:		SetBreakLoop(false);			break;
	case	wpstoploopchkno:	SetBreakLoop(true);				break;				
	case	wpreccyno:		/*dead?*/							break;
	case	wpartspotno:	/*dead?*/							break;
//DeadCode CSB 7Aug00 	case	wpengagetargetno:		movecode=AUTOSAG_BOMBAPPROACH;		break;
	case	wpengagetargetno:									break;
	case	wpattackconvoyno:		movecode=AUTOSAG_BOMB;		break;
	case	wpballoonbustno:		movecode=AUTOSAG_BOMB;		break;
	case	wpbombno:				movecode=AUTOSAG_BOMB;		break;
	case	wpdivebombstraffeno:	movecode=AUTOSAG_BOMB;		break;
	case	wpsecondaryno:			movecode=AUTOSAG_BOMB;		break;
	case	WP_fighterlimit:		FighterLimitWayPoint();		break;
	default:	INT3;											break;
	}
	ai.ManStep = 0;														//CSB 20Jul00
	manoeuvretime = 0;													//CSB 24Jul00
	information = IF_OUT_POS;
	ai.LastAction()=wpacnoactionno;
}
void	SAGAirstruc::SetBreakLoop(bool isendofloop)	
{
//TempCode CSB 7Aug00 	WayPointPtr el=waypoint;
//TempCode CSB 7Aug00 	if (!isendofloop)
//TempCode CSB 7Aug00 	{
//TempCode CSB 7Aug00 
//TempCode CSB 7Aug00 
//TempCode CSB 7Aug00 	}


}
void	SAGAirstruc::SetLanding()
{
	movecode=AUTOSAG_LANDING;
	ai.ManStep = 0;														//CSB 18Jul00

	Squad_Diary.SetLandingTime(AirStrucPtr(*this)->ai.diaryptr);	//use view time
}

void	SAGAirstruc::SetDisperse()
{

	Squad_Diary.SetDisperseTime(AirStrucPtr(*this)->ai.diaryptr);	//use view time
	if (duty>=PACK_AM_ESCORT && duty<=PACK_AM_RETURN)
		NextWayPoint();

}

void	SAGairgrp::SAGDecisionFollowWP(int p,int s)
{
	assert(wpref==0 || wpref>10);
	if (wpref==NULL)
	{
		movecode=AUTOSAG_LANDING;
		Todays_Packages[p].packagestatus=Profile::PS_LANDING;
		Todays_Packages[p][s].SetStatus(Profile::PS_LANDING);

		Squad_Diary.SetLandingTime(Todays_Packages[p][s].diaryentry);	//use view time
	}
	if (	Todays_Packages[p][s].status==Profile::PS_DETAILRAID
		||	Todays_Packages[p][s].status==Profile::PS_ENEMYSIGHTED	)
	{
		movecode=AUTOSAG_PRECOMBAT;
		//int	targpack,targsquad;
		int ti=Todays_Packages[p][s].targetindex;
		if (ti<0)
			ti=0;
		UniqueID tuid=Todays_Packages[p].packagetarget[ti];
		int pt,ps=0,ns=-1;
		Todays_Packages.GetACSquadEntry(tuid,pt,ps);
		if (Todays_Packages[pt][ps].status>=Profile::PS_ACTIVE_MAX)
			for (int ps=Todays_Packages[pt].squadlist.Max()-1;ps>=0;ps--)
				if (Todays_Packages[pt][ps].status<Profile::PS_ACTIVE_MAX && Todays_Packages[pt][ps].status>Profile::PS_TAKINGOFF)
					tuid=Todays_Packages[pt][ns=ps].instance;
//DeadCode JIM 11Nov00 		if (Todays_Packages[pt][ps].status>=Profile::PS_ACTIVE_MAX)
		if (ns==-1 && ps==-1)
		{INT3;}
		else
			target=tuid;									//Combat vs target
	}
	else
	if (Todays_Packages[p][s].status==Profile::PS_TARGETAREA)
	{
		info_waypointPtr wp=Persons2::ConvertPtrUID(wpref);
		if (wp->wpact.Evaluate()==wpbombno || wp->wpact.Evaluate()==wpreccyno )
		{
			movecode=AUTOSAG_BOMBAPPROACH;
//DeadCode JIM 19Sep00 			UniqueID tuid=Todays_Packages[p].packagetarget[Todays_Packages[p][s].targetindex];
//DeadCode JIM 19Sep00 			target=tuid;
		}
	}
	assert(wpref==0 || wpref>10);
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementLanding
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementLanding()
{
	if(PatchAppropriate())
	{
		if (duty>=PACK_AM_ESCORT)
			PatchGroupAndAnim(&TakeOff_FormationWing.formationtype,&TakeOff_FormationSquad.formationtype,4);	
		else
			PatchGroupAndAnim(&TakeOff_FormationWing.formationtype,&TakeOff_FormationSquad.formationtype);	
	}

	if((ai.ManStep <= 6) || (ai.ManStep >= 14))
	{
		Move().AutoLanding();
		if( (ai.ManStep == 2) && ((AnyoneInPhaseN(3)) || (AnyoneInPhaseN(4))) )
			ai.ManStep = 1;			//Extra gap between landing aircraft groups
	}
	else
	{
		switch(ai.ManStep)
		{
			case 7:
			{
	 			COORDS3D point1, point2;
				GetTakeOffPoint(TP_SQUADRONSTART, point1);
				GetTakeOffPoint(TP_RUNWAYEND, point2);
				InterceptandRange(&point2, &point1);

				SWord deltahdg = HdgIntercept - hdg;
				if((deltahdg < ANGLES_FifthDeg) && (-deltahdg < ANGLES_FifthDeg))
					ai.ManStep = 8;
				else
					hdg += ANGLES_5Deg * Timer_Code.FRAMETIME / 100;
				vel_ = 100000;
				Float sin, cos;
				Math_Lib.high_sin_cos(hdg, sin, cos);
				vel_x = vel_ * sin;
				vel_y = 0;
				vel_z = vel_ * cos;
				NewPosition(false);
				SetFlightParams();
				break;
			}

			case 8:
			{
	 			COORDS3D point1;
				GetTakeOffPoint(TP_SQUADRONSTART, point1);
				InterceptandRange(&point1);

				SWord deltahdg = HdgIntercept - hdg;
				if(deltahdg > ANGLES_90Deg)
					ai.ManStep = 9;
				NewPosition(false);
				SetFlightParams();
				break;
			}

			case 9:
			{
	 			COORDS3D point1, point2;
				GetTakeOffPoint(TP_SQUADRONSTART, point1);
				GetTakeOffPoint(TP_RUNWAYEND, point2);
				InterceptandRange(&point1, &point2);

				vel_ = 100000;
				SWord deltahdg = HdgIntercept - hdg;
				if((deltahdg < ANGLES_FifthDeg) && (-deltahdg < ANGLES_FifthDeg))
				{
					vel_  = 0;
					vel_x = 0;
					vel_y = 0;
					vel_z = 0;
					ai.ManStep = 14;
					SetManoeuvreTime(255);
				}
				else
					hdg += ANGLES_5Deg * Timer_Code.FRAMETIME / 100;
				Float sin, cos;
				Math_Lib.high_sin_cos(hdg, sin, cos);
				vel_x = vel_ * sin;
				vel_y = 0;
				vel_z = vel_ * cos;
				NewPosition(false);
				SetFlightParams();
				break;
			}
		}
	}
}

	
void	SAGairgrp::SAGMovementLanding(int p,int s)
{

}


void	SAGAirstruc::SAGDecisionLanding()
{
//DeadCode CSB 17Jul00 	PatchGroupAndAnim(&TakeOff_FormationWing.formationtype,&TakeOff_FormationSquad.formationtype);	
}


void	SAGairgrp::SAGDecisionLanding(int p,int s)
{
	if (MMC.currtime-Todays_Packages[p][s].lastwptime>=2*SECSPERMIN)
	{
		movecode=AUTOSAG_REFUELLING;									//JIM 1Sep00
		World.Y=0;
		position.MakeAbsWorldPos(0);
		position[0][0]=World.X;
		position[0][2]=World.Z;
		Todays_Packages[p][s].SetStatus(Profile::PS_REFUELLING);
		if (Todays_Packages[p].squadlist.AllInStatus(Profile::PS_REFUELLING))
			Todays_Packages[p].packagestatus=Profile::PS_REFUELLING;
		Todays_Packages[p][s].lastwptime=MMC.currtime+GetRefuellingTime(Todays_Packages[p][s].squadnum);
	}

}
void	SAGAirstruc::SAGMovementLanded()
{
}
void	SAGairgrp::SAGMovementLanded(int p,int s)
{	
}
void	SAGAirstruc::SAGDecisionLanded()
{	//need to take off and patrol, now!

}
void	SAGairgrp::SAGDecisionLanded(int p,int s)
{	//UI can recover package...
	if (Todays_Packages[p][s].status!=Profile::PS_COMPLETE)
		if (MMC.currtime>=Todays_Packages[p][s].lastwptime)
		{
			if (Todays_Packages[p][s].method==Profile::AM_RECON)		//CSB 12Jul00
			{	//if reconn and diary status is MR_RECONCOMPLETED then can set known target status!
				Diary::RaidGroup* rg=Squad_Diary.GetRaidGroup(Squad_Diary.GetDiaryPtr(Todays_Packages[p][s].diaryentry));	
				if (rg->missresult==MR_RECONCOMPLETED)
				{
					Target& t=Node_Data[Todays_Packages[p].SquadTarget(s)];
					t.falsetargtype=t.truetargtype;
					t.falsepriority=t.truepriority;
					t.knownstatus=t.truestatus;
				}
			}
			movecode=AUTOSAG_LAST;
			Todays_Packages[p].SquadComplete(s);
			Todays_Packages.ChangeMessagesUID(Todays_Packages[p][s].instance,UID_BIT14+((p)<<5)+Todays_Packages[p].GetRaidIndFromSquadEntry(s));

			if (Todays_Packages[p].attackmethod>=Profile::AM_LWPACKS)
				Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_LW,AS_NOTSWITCH,SCRIPT_GESCHWADERLANDED  ,uniqueID.count,UID_NULL,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));
			else
				Node_Data.intel.AddMessage(IntelMsg::HIGH_FLIGHT_WOMAN,AS_NOTSWITCH,SCRIPT_RAFLANDED  ,uniqueID.count,UID_NULL,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p][s].numacleft));

			Todays_Packages[p][s].ApplyFlyingLosses(Todays_Packages[p].squadlist.AcBitsSquad(s));
			if (Todays_Packages[p].squadlist.AllInStatus(Profile::PS_COMPLETE))
				Todays_Packages[p].PackageComplete(); //UI can recover package...
		}
		else
		if (MMC.currtime-Todays_Packages[p][s].lastwptime>=SECSPERMIN*5)
		{
			Todays_Packages[p].packagestatus=Profile::PS_REFUELLING;
			Todays_Packages[p][s].SetStatus(Profile::PS_REFUELLING);
		}

}

//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementPreCombat
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementPreCombat()
{	//Fly towards unfriendly
	if(PatchAppropriate())	
		PatchGroupAndAnim();	

	if(!ai.unfriendly)
		movecode = AUTOSAG_FOLLOWWP;
	else
	{
		InterceptandRange(ai.unfriendly);
		SWord bestpitch = CalcBestClimbPitch();
		if(PitchIntercept > bestpitch)
			PitchIntercept = Angles(bestpitch);
		AutoCalcPitch();
		CalcHdgRoll();
		CalcVelAlt();
		CalcXYZVel();

		if(Range < COMBATRANGE)
			movecode = AUTOSAG_COMBAT;

		if(((fly.pModel->FrameCount & 0x1fff) == 0) && (FuelShort(5 * 60 * 100)))
		{
			movecode = AUTOSAG_FOLLOWWP;
			ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
			waypoint = waypoint->FindWP(WPNAME_EscDisperse);
		}
	}

	NewPosition();
	SetFlightParams();
}

//DeadCode CSB 2Nov00 	if(PatchAppropriate())	
//DeadCode CSB 2Nov00 		PatchGroupAndAnim();	
//DeadCode CSB 2Nov00 
//DeadCode CSB 2Nov00 	if(!ai.unfriendly)
//DeadCode CSB 2Nov00 		Art_Int.BreakOff(this);
//DeadCode CSB 2Nov00 	else
//DeadCode CSB 2Nov00 	{
//DeadCode CSB 2Nov00 		InterceptandRange(ai.unfriendly);
//DeadCode CSB 2Nov00 		SWord bestpitch = CalcBestClimbPitch();
//DeadCode CSB 2Nov00 		if(PitchIntercept > bestpitch)
//DeadCode CSB 2Nov00 			PitchIntercept = Angles(bestpitch);
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 		if(PitchIntercept < ANGLES_0Deg)
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 			PitchIntercept = ANGLES_0Deg;
//DeadCode CSB 2Nov00 
//DeadCode CSB 2Nov00 		AutoCalcPitch();
//DeadCode CSB 2Nov00 		CalcHdgRoll();
//DeadCode CSB 2Nov00 		CalcVelAlt();
//DeadCode CSB 2Nov00 		CalcXYZVel();
//DeadCode CSB 2Nov00 		
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 		SLong delta = ai.unfriendly->World.Y - World.Y;
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 		if(delta > 0)
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 			Range -= delta;
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 		else
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 			Range -= -delta;
//DeadCode CSB 2Nov00 		
//DeadCode CSB 2Nov00 		if(Range < COMBATRANGE)
//DeadCode CSB 2Nov00 			movecode = AUTOSAG_COMBAT;
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 		{
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 			AirStrucPtr unf = *ai.unfriendly;
//DeadCode CSB 2Nov00 //DeadCode CSB 1Aug00 			if((unf->fly.numinsag) && (unf->fly.expandedsag))
//DeadCode CSB 2Nov00 //DeadCode CSB 1Aug00 				ai.unfriendly = unf->fly.expandedsag;
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 			Art_Int.SetEngage(this, unf, MANOEUVRE_TURNINGFIGHT, ANGLES_0Deg, ANGLES_0Deg, FALSE);
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 		}
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 		if((Range < RECOGNISERANGE) && (nationality == AirStrucPtr(ai.unfriendly)->nationality))
//DeadCode CSB 2Nov00 //DeadCode CSB 2Nov00 			Art_Int.BreakOff(this);
//DeadCode CSB 2Nov00 	}
//DeadCode CSB 2Nov00 
//DeadCode CSB 2Nov00 	NewPosition ();
//DeadCode CSB 2Nov00 	SetFlightParams ();
//DeadCode CSB 2Nov00 
//DeadCode CSB 2Nov00 //	Move().AutoPreCombat();
//DeadCode CSB 2Nov00 }


void	SAGairgrp::SAGMovementPreCombat(int p,int s)
{	//need to cruise to target
	if (target.Evaluate()<0||target.Evaluate()>IllegalBAND)	
		INT3;
	info_airgrpPtr a=Persons2::ConvertPtrUID(UniqueID(target.Evaluate()));
	if(a)
	{
		InterceptandRange(&a->World);
		if (	Todays_Packages[p].packagestatus!=Profile::PS_DETAILRAID
			||	Range>METRES10KM)
		{  
			int	deltaalt=a->World.Y-World.Y;
			if (Range>METRES5000 || deltaalt<FT_2000)
			{
				int vel=GetCruiseAt(World,PitchIntercept)*1.3;
				if (!attitude.complex)
					attitude=new RotExpr;
				attitude[1]=HdgIntercept;
				attitude[2]=PitchIntercept;
				hdg=HdgIntercept;
				int	travel=SECSPERSAGFRAME*vel;
			
				Float sh,ch,sp,cp;
				Math_Lib.high_sin_cos(HdgIntercept,sh,ch);
				Math_Lib.high_sin_cos(PitchIntercept,sp,cp);
				World.Y+=travel*sp;
				travel*=cp;
				World.Z+=travel*ch;
				World.X+=travel*sh;
				position.MakeAbsWorldPos(World.Y);
				position[0][0]=World.X;
				position[0][2]=World.Z;
			}
			else
			{
				World.Y+=FT_800;	  //This is Craigs estimate for 20 secs of climb for a fighter.
			}
		}
	}
	
}
void	SAGAirstruc::SAGDecisionPreCombat()
{
//DeadCode CSB 17Jul00 	PatchGroupAndAnim();	//reset heading! Should arrange to do 1 flight per frame
}

UniqueID	SAGairgrp::SelectUnfriendly(int trgpack,int trgraid,int submethod,int& livesqs)
{
	livesqs=0;
	UniqueID target=UID_NULL;
	int sqmin=Todays_Packages[trgpack].RaidNumEntriesMinSq(trgraid);
	int sqmax=Todays_Packages[trgpack].RaidNumEntriesMaxSq(trgraid);
	enum	{O_ESC_U,O_ESC_W,O_ESC_E,O_BMB_U,O_BMB_W,O_BMB_E,O_MAX,
			O_U=0,O_W,O_E,O_M,
			};
	UniqueID options[O_MAX]={UID_NULL};
	UniqueID	sparesq=UID_NULL,escortsq=UID_NULL;
	for (;sqmin<=sqmax;sqmax--)
	{
		info_airgrpPtr p=Persons2::ConvertPtrUID(Todays_Packages[trgpack][sqmax].instance);
		if (	Todays_Packages[trgpack][sqmax].status<Profile::PS_ACTIVE_MAX 
			&&	Todays_Packages[trgpack][sqmax].status>Profile::PS_TAKINGOFF
			&&	Todays_Packages[trgpack][sqmax].numacleft)	//MS 3Jul00
		{
			int option=O_ESC_U;
			if (Todays_Packages[trgpack][sqmax].method<Profile::AM_DETACHED)												//MS 3Jul00
				option=O_BMB_U;
			info_airgrpPtr iag=(Persons2::ConvertPtrUID(Todays_Packages[trgpack][sqmax].instance));
			if (!iag->OverFrance())
			{
				livesqs++;
				if (iag->target.Evaluate()!=ENABLE_COMPLEX_VAL && iag->target.Evaluate()!=0)
				{
					if (options[option+O_E]==UID_NULL || Math_Lib.rnd()>RND33PC)
						options[option+O_E]=Todays_Packages[trgpack][sqmax].instance;
				}
				else
				if (Todays_Packages[trgpack][sqmax].numacleft!=Todays_Packages[trgpack][sqmax].numacoriginal)	//MS 3Jul00
				{
					if (options[option+O_W]==UID_NULL || Math_Lib.rnd()>RND33PC)
						options[option+O_W]=Todays_Packages[trgpack][sqmax].instance;
				}
				else
					if (options[option]==UID_NULL || Math_Lib.rnd()>RND33PC)
						options[option]=Todays_Packages[trgpack][sqmax].instance;
			}
		}
		int possdetachedsurprise=Math_Lib.rnd(Todays_Packages[trgpack].squadlist.Max());
		if (	(Todays_Packages[trgpack][possdetachedsurprise].method&Profile::AM_GROUPMASK)==Profile::AM_DETACHED
			&&	(Todays_Packages[trgpack][possdetachedsurprise].submethod&Profile::SM_109RETURNING)==0
			&&  Todays_Packages[trgpack][possdetachedsurprise].status>Profile::PS_TAKINGOFF		//RDH 15Nov00
			&&	Todays_Packages[trgpack][possdetachedsurprise].status<Profile::PS_ACTIVE_MAX	//RDH 15Nov00
			)
		{
 			info_airgrpPtr iag=(Persons2::ConvertPtrUID(Todays_Packages[trgpack][possdetachedsurprise].instance));
			if (iag->target.Evaluate()==ENABLE_COMPLEX_VAL || iag->target.Evaluate()==0)
			{	//So we randomly picked an aircraft and it is a detached escort not in combat... pretty good!
				iag->movecode=AUTOSAG_PRECOMBAT;
				Todays_Packages[trgpack][possdetachedsurprise].SetStatus(Profile::PS_ENEMYSIGHTED);
				iag->target=uniqueID.count;
			}
		}
	}
	if (livesqs)
	{
		int prim=O_ESC_U;
		int	sec=O_BMB_U;
		if (	(submethod&Profile::SM_NOTFIGHTERS)!=0
			||	((submethod&Profile::SM_NOTBOMBERS)==0 && Math_Lib.rnd()>RND33PC)	//MS 25Oct00
			)
		{	//I.E. 	DON'T go for fighters or not DO go for fighters*rnd50%
			prim=O_BMB_U;
			sec=O_ESC_U;
		}
		{for (int i=prim+O_M-1;i>=prim;i--)
			if (options[i])
				target=options[i];
		}
		if (target==UID_NULL)
		{for (int i=sec+O_M-1;i>=sec;i--)
			if (options[i])
				target=options[i];
		}
	}
	return target;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    RunOutOfFightTime
// Date:		27/10/00
// Author:		MS
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
static bool	RunOutOfFightTime(int diaryentry,int enemydiary)
{	//USe diary to decide wether we have any bullets left...
	SquadronBase* diary=Squad_Diary.GetDiaryPtr(diaryentry);
	int time=0;
	ULong *timeref=NULL;
	int killcount;
	if (diary->squadnum<SQ_LW_START)
	{
		timeref=&Squad_Diary.GetIntercept(diary)->intercepttime;
		UByte* kills=((Diary::Squadron*)(diary))->kills;
		killcount=kills[0]+kills[1]+kills[2]+kills[3]+kills[4]+kills[5];
	}
	else
	{
		timeref=&Squad_Diary.GetIntercept(Squad_Diary.GetDiaryPtr(enemydiary))->intercepttime;	//MS 25Oct00

		UByte* kills=((Diary::Gruppen*)(diary))->kills;
		killcount=kills[0]+kills[1]+kills[2];
		killcount/=3;	//There are usually 3 squads per Grupp. Modify this for a tuning RAF/LW factor
	}

	if (timeref)	//always set presently...
		if (*timeref)
			time=(MMC.currtime-*timeref);
		else
			*timeref=time=MMC.currtime;
	time+=killcount*30;	
	if (time<10*SECSPERMIN)			//THIS SHOULD BE LOWER	//THERE MUST NOT BE MORE THAN 5 MINS DIFFERENCE BETWEEN THESE 2
		return false;									
	else if (time>15*SECSPERMIN)	//THIS SHOULD BE HIGHER
		return true;
	else 
	{
		int v=Math_Lib.rnd();	 //240=4 mins.
		v=(v&(v>>8)&255);	//high values are improbable
		if (time+v>15*SECSPERMIN)	//THIS SHOULD BE THE HIGHER VALUE
			return true;
		else											//MARK: COMMENT OUT DOWN TO HERE IF MY MATHS IS SCREWED UP
			return false;								
	}
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGDecisionPreCombat
// Date:		25/10/00
// Author:		MS
//
//Description: This code copes with 3 possible states
//				1) Package status == PS_DETAILRAID
//					This package has not yet found it's target group (RAF)
//				2) Squad status = PS_DETAILRAID
//						This squad knows the raid but has not chosen a member
//				3) Squad status = PS_ENEMYSIGHTED
//						This squad has a selected enemy but is too far away!
//
//////////////////////////////////////////////////////////////////////
void	SAGairgrp::SAGDecisionPreCombat(int p,int s)
{
	if (target.Evaluate()<0||target.Evaluate()>IllegalBAND)	
		INT3;
	int	livesqs=0;
	info_airgrpPtr a=Persons2::ConvertPtrUID(UniqueID(target.Evaluate()));
	if (type<SQ_LW_START && ItemBase::OverFrance(World))//World.Z-World.X<-METRES100KM)
		a=NULL;
	if (a)
	{
		if (a->type>SQ_LW_START && a->OverFrance())
		{	//Find another in the package to chase who isn't
 			int tp,ts;
			Todays_Packages.GetACSquadEntry(UniqueID(target.Evaluate()),tp,ts);
			int te=Todays_Packages[tp].GetRaidIndFromSquadEntry(ts);
			te=Todays_Packages[tp].RaidNumEntriesMaxSq(te);
			for (;ts<=te;ts++)
			{
				a=Persons2::ConvertPtrUID(Todays_Packages[tp][ts].instance);
				if (a&&!a->OverFrance())
					break;
			}
			if (ts>te)		//All of raid has scarpered. Go home!
				a=NULL;
		}
	}
	if (a)
	{
		InterceptandRange(&a->World);
		if (	Todays_Packages[p].packagestatus==Profile::PS_DETAILRAID
			&&	Range<METRES15KM 
			&& s==0)	 //probability calc takes in to account our force size already!
		{	//OK... we are close enough to see the unfriendly
			//Check the weather and the range and the pilot skill to decide if a spot will occur.
			int tp,ts;
			Todays_Packages.GetACSquadEntry(UniqueID(target.Evaluate()),tp,ts);
			
			int testrange=METRES15KM;
			if (MMC.Sky.Press0<960)
				testrange*=0.1;
			elseif (MMC.Sky.Press0<950+64)	 //anything above 1010 is pretty fine
				testrange=testrange*(MMC.Sky.Press0-950 /*10..64*/)/64;
			if (Todays_Packages[p].squadlist.Max()!=1)
				testrange=testrange*(1+Todays_Packages[p].squadlist.Max());
			else
				if (Todays_Packages[p].squadlist[0].numacleft>=3)
					testrange=testrange*(6+Todays_Packages[p].squadlist[0].numacleft)/8;

			if (Todays_Packages[tp].squadlist.Max()==1)
				testrange=testrange*(1+Todays_Packages[tp].squadlist[0].numacleft)/30;//29;	//1 full squad has 1/2 chance of spot
			elseif (Todays_Packages[tp].squadlist.Max()<5)
				testrange=testrange*(3+Todays_Packages[tp].squadlist.Max())/8;	//5 should be equal chance
			else
				testrange=testrange*Todays_Packages[tp].squadlist.Max()/5	;	//Over 5 squads is easier to spot.
			testrange=testrange*(Todays_Packages[p][s].Squadron().leaderskill+50)/256;
			//Range<15km=1500000 squared= 220 000 00 000 00 =
			if (Range<testrange || Math_Lib.rnd((Range*0.0000001)*Range)<int((testrange*0.0000001)*testrange))
			{
				Todays_Packages[p].packagestatus=Profile::PS_ENEMYSIGHTED;
//DeadCode MS 25Oct00 				Todays_Packages[p][s].SetStatus(Profile::PS_ENEMYSIGHTED);
				AccelSwitches as = AS_LARGE_ENGAGEMENT;
				if (Todays_Packages[tp].squadlist <= 2)
					as = AS_SMALL_ENGAGEMENT;		
				
				Squad_Diary.ArrivedAtTarget(Todays_Packages[p][s].diaryentry,&Persons2::ConvertPtrUID(UniqueID(target.Evaluate())));	//RJS 5Oct00
				//Ok... at this point the RAF have spotted the LW.
				//If they are unescorted they may turn now.
				bool gotescort=false;
				bool fighterbomber=false;
				for (int ti=0,tim=Todays_Packages[tp].squadlist.Max();ti<tim;ti++)
					if (Todays_Packages[tp][ti].method>Profile::AM_ESCORTTYPES)
						gotescort=true;
					else
						if (	Todays_Packages[tp][ti].method>Profile::AM_LWPACKS
							&&	Todays_Packages[tp][ti].Squadron().AcType()<=PT_JU87	)
							fighterbomber=true;
				if (fighterbomber&&!gotescort)
					if (Math_Lib.rnd()>RND10PC)
					{
						for (int ti=0,tim=Todays_Packages[tp].squadlist.Max();ti<tim;ti++)
							Todays_Packages[tp].StopFighting(ti,Persons2::ConvertPtrUID(Todays_Packages[tp][ti].instance),true);
					}


				//Send some messages about the impending combat...
				Node_Data.intel.AddMessage(IntelMsg::HIGH_ENGAGEMENT_WOMAN,as,SCRIPT_INTERCEPTING  ,Todays_Packages[p][s].instance,Todays_Packages[tp][ts].instance,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[tp][ts].numacleft));
				Node_Data.intel.AddMessage(IntelMsg::HIGH_ENGAGEMENT_LW,as,SCRIPT_INTERCEPTED  ,Todays_Packages[tp][ts].instance,Todays_Packages[p][s].instance,TargetIndexes(Todays_Packages[tp][ts].squadnum,Todays_Packages[p][s].numacleft));
			}
			else
			{
				int tp,ts;
				Todays_Packages.GetACSquadEntry(UniqueID(target.Evaluate()),tp,ts);
//DeadCode JIM 11Sep00 				AccelSwitches as = AS_LARGE_ENGAGEMENT;
//DeadCode JIM 11Sep00 				if (Todays_Packages[tp].squadlist <= 2)
//DeadCode JIM 11Sep00 					as = AS_SMALL_ENGAGEMENT;
//#pragma warnmsg("ROB:  enable SCRIPT_CANTFINDBANDITS2D")
				int re=Todays_Packages[p].GetRaidIndFromSquadEntry(s);
				if (Todays_Packages[p].raidnumentries[re].cantfindsaid)
					Todays_Packages[p].raidnumentries[re].cantfindsaid--;
				else
				{
	 				Node_Data.intel.AddMessage(IntelMsg::HIGH_ENGAGEMENT_WOMAN,AS_NOTSWITCH,SCRIPT_CANTFINDBANDITS2D  ,Todays_Packages[p][s].instance,Todays_Packages[tp][ts].instance,TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[tp][ts].numacleft));
					Todays_Packages[p].raidnumentries[re].cantfindsaid=15;
				}
			}



		}

		int vel=GetCruiseAt(World)*1.3;
		int	travel=SECSPERSAGFRAME*vel;
		livesqs = 1;
		if (Todays_Packages[p].packagestatus!=Profile::PS_DETAILRAID && Range<METRES5000)
		{
			//About to go into combat. Oh dear, I have no fuel or weapons!
			int	deltaalt=a->World.Y-World.Y;
			Coords3D p0,p1;
			p0=World;
			p1=Persons2::ConvertPtrUID(Todays_Packages[p][s].Squadron().homeairfield)->World;
			PlaneTypeSelect pt=Todays_Packages[p][s].Squadron().AcType();
			int tp,ts;
			Todays_Packages.GetACSquadEntry(UniqueID(target.Evaluate()),tp,ts);
			if (	Todays_Packages[p].CalcFuel(&p0,&p1,pt,pt,0)+1000000>Todays_Packages[p][s].fuelleft
				||	Todays_Packages[p][s].fightperiods>17	//RunOutOfFightTime(Todays_Packages[p][s].diaryentry,Todays_Packages[tp][ts].diaryentry)
				) 
			{
				livesqs=0;
			}
			else
			{
				if (Todays_Packages[p][s].status==Profile::PS_DETAILRAID)
				{	//select actual unfriendly group
					int tr=Todays_Packages[tp].GetRaidIndFromSquadEntry(ts);
					target=SelectUnfriendly(tp,tr,Todays_Packages[p][s].submethod,livesqs);
					Todays_Packages[p][s].status=Profile::PS_ENEMYSIGHTED;
				}
				if (Range<METRES2500 && deltaalt<FT_2000)
				{	//Go into combat
					movecode=AUTOSAG_COMBAT;
					if (target.Evaluate()<0||target.Evaluate()>IllegalBAND)	
						INT3;
				}
			}
		}
	}																	//JIM 17Jul00
	if (livesqs==0)														//JIM 17Jul00
		if (Todays_Packages[p].StopFighting(s,this,true))
		{
			Todays_Packages.ChangeMessagesUID(Todays_Packages[p][s].instance,UID_BIT14+((p)<<5)+Todays_Packages[p].GetRaidIndFromSquadEntry(s));

			Todays_Packages[p][s].ApplyFlyingLosses(Todays_Packages[p].squadlist.AcBitsSquad(s));
			if (Todays_Packages[p].squadlist.AllInStatus(Profile::PS_COMPLETE))
				Todays_Packages[p].PackageComplete(); //UI can recover package...
		}
}


//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementCombat
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void SAGAirstruc::SAGMovementCombat()
{
	if(PatchAppropriate())
		PatchGroupAndAnim();	
	
	if(!((ai.unfriendly) && (ai.unfriendly->Status.size == AIRSTRUCSIZE)))
	{
		hdg += Angles(ACMAS().CalcHdg ());
		CalcXYZVel();
		NewPosition();
		SetFlightParams();
		movecode = AUTOSAG_FOLLOWWP;
		return;
	}

	AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
	if(!unf->fly.numinsag)
	{
		INT3;															//CSB 1Aug00
		SetUnfriendly(unf->fly.expandedsag);							//CSB 1Aug00
//DeadCode CSB 1Aug00 		if(unf->ai.attacker == this)
//DeadCode CSB 1Aug00 			unf->ai.attacker = NULL;
//DeadCode CSB 1Aug00 		unf = unf->fly.expandedsag;
//DeadCode CSB 1Aug00 		ai.unfriendly = unf;
//DeadCode CSB 1Aug00 		if(!unf->ai.attacker)
//DeadCode CSB 1Aug00 			unf->ai.attacker = this;
	}

	InterceptandRange(unf);

	if((ai.manoeuvre != MANOEUVRE_TURNINGFIGHT) && (ai.manoeuvre != MANOEUVRE_GAINSPEED) && (ai.manoeuvre != MANOEUVRE_GAINSPEED))
	{
		ai.desiredrange = 0;
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		SetManoeuvreTime(1500);
	}

	ai.desiredrange += Timer_Code.FRAMETIME;

	switch(ai.manoeuvre)
	{
		case MANOEUVRE_TURNINGFIGHT:
		{
			SWord MaxRoll = ANGLES_75_5Deg;
			AutoCalcPitch();
			
			SWord reqdeltahdg = hdg - HdgIntercept;
		 	SWord reqroll = FindRequiredRoll(reqdeltahdg, CombatReqBankData);
			if(SWord(reqroll) >  MaxRoll)	reqroll =  MaxRoll;
			if(SWord(reqroll) < -MaxRoll)	reqroll = -MaxRoll;
			SimpleMoveToRoll(reqroll);
			break;
		}

		case MANOEUVRE_LOWALT:
		{
			PitchIntercept = Angles(CalcBestClimbPitch());
			SWord MaxRoll = ANGLES_30Deg;
			AutoCalcPitch();
			SWord reqdeltahdg = hdg - HdgIntercept;
		 	SWord reqroll = FindRequiredRoll(reqdeltahdg, CombatReqBankData);
			if(SWord(reqroll) >  MaxRoll)	reqroll =  MaxRoll;
			if(SWord(reqroll) < -MaxRoll)	reqroll = -MaxRoll;
			SimpleMoveToRoll(reqroll);
			break;
		}

		case MANOEUVRE_GAINSPEED:
		{
			PitchIntercept = ANGLES_350Deg;
			SWord MaxRoll = ANGLES_45Deg;
			AutoCalcPitch();
			SWord reqdeltahdg = hdg - HdgIntercept;
		 	SWord reqroll = FindRequiredRoll(reqdeltahdg, CombatReqBankData);
			if(SWord(reqroll) >  MaxRoll)	reqroll =  MaxRoll;
			if(SWord(reqroll) < -MaxRoll)	reqroll = -MaxRoll;
			SimpleMoveToRoll(reqroll);
			break;
		}

		break;
	}

	hdg += Angles(ACMAS().CalcHdg ());

	ACMAS().SimpleMoveToThrust(100);
	FP fvel = FP(ANGLES_90Deg - SWord(pitch)) / FP(ANGLES_180Deg);
	SLong desvel = classtype->minvel + FP(classtype->maxdivevel - classtype->minvel) * fvel;
	if(vel_ < desvel) 	vel_ += 100 * Timer_Code.FRAMETIME;
	if(vel_ > desvel)	vel_ -= 100 * Timer_Code.FRAMETIME;
	CalcXYZVel();
	NewPosition ();
	SetFlightParams();

	if(!TimeLeft())
	{
		if(World.Y < HIGHESTGROUND)
			ai.manoeuvre = MANOEUVRE_LOWALT;
		else if(2 * vel_ < 3 * classtype->minvel)
			ai.manoeuvre = MANOEUVRE_GAINSPEED;
		else
			ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;

		bool damagethem = false;
		bool damageus   = false;
		if(unf->classtype->aerobaticfactor == AEROBATIC_LOW)
		{
			if((Range < 100000) && (ai.manoeuvre == MANOEUVRE_TURNINGFIGHT))
			{
	  			FP reqval = 4500.0 * FP(Art_Int.CountSquadronSize(this)) * (256.0 + FP(ai.combatskill)) / (FP(Art_Int.CountSquadronSize(unf)) * (256.0 + FP(unf->ai.combatskill)));
				if(Math_Lib.rnd() < reqval)	
					damagethem = true;

//DeadCode CSB 3Nov00 				if(!unf->fly.expandedsag)
				{
					FP reqval = 1500.0 * FP(Art_Int.CountSquadronSize(unf)) * (256.0 + FP(unf->ai.combatskill)) / (FP(Art_Int.CountSquadronSize(this)) * (256.0 + FP(ai.combatskill)));
					if(Math_Lib.rnd() < reqval)
						damageus = true;
				}
			}
		}
		else
		{
			FP acstrengthus	  = 0.75;
			FP acstrengththem = 0.75;
			switch(classtype->visible)
			{
				case SPIT:	acstrengthus = 1.00;	break;
				case HURR:	acstrengthus = 0.90;	break;
				case DEF:	acstrengthus = 0.60;	break;
				case ME109:	acstrengthus = 0.95;	break;
				case ME110:	acstrengthus = 0.85;	break;
				case JU87:	acstrengthus = 0.50;	break;
			}
			switch(unf->classtype->visible)
			{
				case SPIT:	acstrengththem = 1.00;	break;
				case HURR:	acstrengththem = 0.90;	break;
				case DEF:	acstrengththem = 0.60;	break;
				case ME109:	acstrengththem = 0.95;	break;
				case ME110:	acstrengththem = 0.85;	break;
				case JU87:	acstrengththem = 0.50;	break;
			}

			if((Range < 100000) && (ai.manoeuvre == MANOEUVRE_TURNINGFIGHT))
			{
	  			FP reqval = 4000.0 * acstrengthus * FP(Art_Int.CountSquadronSize(this)) * (256.0 + FP(ai.combatskill))
								/ (acstrengththem * FP(Art_Int.CountSquadronSize(unf)) * (256.0 + FP(unf->ai.combatskill)));
				if(Math_Lib.rnd() < reqval)	
					damagethem = true;
			}
		}

		bool gohome = false;

		if(damagethem)
		{
			UWord damage = 255;
//DeadCode CSB 3Nov00 			if(unf->classtype->aerobaticfactor == AEROBATIC_MEDIUM)		damage = 96;
//DeadCode CSB 3Nov00 			else if(unf->classtype->aerobaticfactor == AEROBATIC_HIGH)	damage = 48;
			if(unf->IsUnexpandedSAG())
			{
				Fake_Damage.HitGroup(ai.unfriendly, ItemPtr(this), damage);//, 16, DMT_BULLET);	//Should be about half a kill//RJS 05Apr00
				if(!Art_Int.CountSquadronSize(unf))
					unf->DestroySag();
				if(unf->Status.deadtime)
					unf->DestroySag();
			}
			else
			{
				AirStrucPtr victim = Art_Int.FindTailie(unf);
				Fake_Damage.HitAircraft(victim, this, damage);			//CSB 30/05/00
			}
		}

		if(damageus)
		{
 			Fake_Damage.HitGroup(ItemPtr(this), ai.unfriendly, 255);//, 16, DMT_BULLET);	//Should be about half a kill//RJS 05Apr100
			if(!Art_Int.CountSquadronSize(this))
			{
				DestroySag();
				return;
			}
		}

		if((ai.desiredrange > (10 * 60 * 100)) || (FuelShort(5 * 60 * 100)))
			gohome = true;

		if(gohome)
		{
			ai.ManStep = 0;
			manoeuvretime = 0;
			movecode = AUTOSAG_FOLLOWWP;
			information = IF_OUT_POS;
			SetUnfriendly(NULL);
			ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
			waypoint = waypoint->FindWP(WPNAME_EscDisperse);
		}

		SetManoeuvreTime(1500);
	}

	if(Range > COMBATRANGE)
		movecode = AUTO_PRECOMBAT;

//DeadCode CSB 2Nov00 		if((Range < 50000) && (ai.manoeuvre == MANOEUVRE_TURNINGFIGHT))
//DeadCode CSB 2Nov00 		{
//DeadCode CSB 2Nov00 			FP reqval = (16384.0 * FP(Art_Int.CountSquadronSize(this)) * FP(ai.combatskill)) / (FP(Art_Int.CountSquadronSize(unf)) * FP(unf->ai.combatskill));
//DeadCode CSB 2Nov00 			if(Math_Lib.rnd() < reqval)
//DeadCode CSB 2Nov00 			{	/*****	Kill/Damage one aircraft in enemy SAG	*****/
//DeadCode CSB 2Nov00 				if(AirStrucPtr(ai.unfriendly)->IsUnexpandedSAG())
//DeadCode CSB 2Nov00 				{
//DeadCode CSB 2Nov00 					Fake_Damage.HitGroup(ItemPtr(unf), ItemPtr(this), 64);//, 16, DMT_BULLET);	//Should be about half a kill//RJS 05Apr00
//DeadCode CSB 2Nov00 					if(!Art_Int.CountSquadronSize(unf))
//DeadCode CSB 2Nov00 						unf->DestroySag();
//DeadCode CSB 2Nov00 					if(unf->Status.deadtime)
//DeadCode CSB 2Nov00 						unf->DestroySag();
//DeadCode CSB 2Nov00 //DeadCode CSB 4Aug00 						unf->movecode = AUTOSAG_DESTROYED;
//DeadCode CSB 2Nov00 				}
//DeadCode CSB 2Nov00 				else
//DeadCode CSB 2Nov00 				{
//DeadCode CSB 2Nov00 					AirStrucPtr victim = Art_Int.FindTailie(AirStrucPtr(ai.unfriendly));
//DeadCode CSB 2Nov00 //DEADCODE CSB 30/05/00 					AircraftAnimData* adptr = (AircraftAnimData*)victim->Anim;
//DeadCode CSB 2Nov00 //DEADCODE CSB 30/05/00 					switch(Math_Lib.rnd(3))
//DeadCode CSB 2Nov00 //DEADCODE CSB 30/05/00 					{	
//DeadCode CSB 2Nov00 //DEADCODE CSB 30/05/00 						case 0:	SHAPE.ForceDamage(victim, this, &adptr->LEFTWINGIN, BS_DEAD);	break;
//DeadCode CSB 2Nov00 //DEADCODE CSB 30/05/00 						case 1:	SHAPE.ForceDamage(victim, this, &adptr->RIGHTWINGIN, BS_DEAD);	break;
//DeadCode CSB 2Nov00 //DEADCODE CSB 30/05/00 						case 2:	SHAPE.ForceDamage(victim, this, &adptr->ENGINELEFT, BS_DEAD);	break;
//DeadCode CSB 2Nov00 //DEADCODE CSB 30/05/00 					}
//DeadCode CSB 2Nov00 					Fake_Damage.HitAircraft(victim,this,64);			//CSB 30/05/00
//DeadCode CSB 2Nov00 				}
//DeadCode CSB 2Nov00 			}
//DeadCode CSB 2Nov00 		}
//DeadCode CSB 2Nov00 
//DeadCode CSB 2Nov00 		if(!((ai.unfriendly) && (ai.unfriendly->Status.size == AIRSTRUCSIZE)))
//DeadCode CSB 2Nov00 		{
//DeadCode CSB 2Nov00 //DeadCode CSB 7Aug00 			hdg += Angles(ACMAS().CalcHdg ());
//DeadCode CSB 2Nov00 //DeadCode CSB 7Aug00 			CalcXYZVel();
//DeadCode CSB 2Nov00 //DeadCode CSB 7Aug00 			NewPosition();
//DeadCode CSB 2Nov00 			movecode = AUTOSAG_FOLLOWWP;
//DeadCode CSB 2Nov00 			return;
//DeadCode CSB 2Nov00 		}
//DeadCode CSB 2Nov00 
//DeadCode CSB 2Nov00 		if((Range < 25000) && (AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW) && (AirStrucPtr(ai.unfriendly)->fly.numinsag))
//DeadCode CSB 2Nov00 		{
//DeadCode CSB 2Nov00 			FP reqval = (Art_Int.CountSquadronSize(unf) * unf->ai.combatskill) / (Art_Int.CountSquadronSize(this) * ai.combatskill);
//DeadCode CSB 2Nov00 			if(Math_Lib.rnd() < 8192.0 * reqval)
//DeadCode CSB 2Nov00 			{	/*****	Bomber gunners Kill/Damage one aircraft in this SAG	*****/
//DeadCode CSB 2Nov00  				Fake_Damage.HitGroup(ItemPtr(this), ItemPtr(unf), 64);//, 16, DMT_BULLET);	//Should be about half a kill//RJS 05Apr100
//DeadCode CSB 2Nov00 				if(!Art_Int.CountSquadronSize(this))
//DeadCode CSB 2Nov00 				{
//DeadCode CSB 2Nov00 					DestroySag();
//DeadCode CSB 2Nov00 					return;
//DeadCode CSB 2Nov00 				}
//DeadCode CSB 2Nov00 //DeadCode CSB 4Aug00 					movecode = AUTOSAG_DESTROYED;
//DeadCode CSB 2Nov00 			}
//DeadCode CSB 2Nov00 		}
//DeadCode CSB 2Nov00 
//DeadCode CSB 2Nov00 		if(GroupShouldGoHome(0.5))
//DeadCode CSB 2Nov00 		{
//DeadCode CSB 2Nov00 			ai.ManStep = 0;
//DeadCode CSB 2Nov00 			manoeuvretime = 0;
//DeadCode CSB 2Nov00 			movecode = AUTOSAG_FOLLOWWP;
//DeadCode CSB 2Nov00 			information = IF_OUT_POS;
//DeadCode CSB 2Nov00 			SetUnfriendly(NULL);
//DeadCode CSB 2Nov00 			ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
//DeadCode CSB 2Nov00 			waypoint = waypoint->FindWP(WPNAME_EscDisperse);
//DeadCode CSB 2Nov00 		}
//DeadCode CSB 2Nov00 		else if(	(	(Art_Int.CountSquadronSize(this) * 2 < Art_Int.CountSquadronSize(unf))
//DeadCode CSB 2Nov00 					&&	(unf->classtype->aerobaticfactor >= classtype->aerobaticfactor)	)
//DeadCode CSB 2Nov00 				||	(FuelShort(10 * 60 * 100))	)
//DeadCode CSB 2Nov00 		{
//DeadCode CSB 2Nov00 			ai.ManStep = 0;
//DeadCode CSB 2Nov00 			manoeuvretime = 0;
//DeadCode CSB 2Nov00 			movecode = AUTOSAG_FOLLOWWP;
//DeadCode CSB 2Nov00 			information = IF_OUT_POS;
//DeadCode CSB 2Nov00 			SetUnfriendly(NULL);
//DeadCode CSB 2Nov00 			fly.leadflight = NULL;
//DeadCode CSB 2Nov00 			ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
//DeadCode CSB 2Nov00 		}
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 		else if(	(fly.leadflight) && (fly.leadflight->classtype->aerobaticfactor == AEROBATIC_LOW)
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 				&&	(Distance3DSquared(&fly.leadflight->World) > FP(VISIBLERANGE) * FP(VISIBLERANGE))	)	
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 		{
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 			ai.ManStep = 0;
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 			manoeuvretime = 0;
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 			movecode = AUTOSAG_FOLLOWWP;
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 			information = IF_OUT_POS;
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 			SetUnfriendly(NULL);
//DeadCode CSB 2Nov00 //DeadCode CSB 17Oct00 		}
//DeadCode CSB 2Nov00 //DeadCode CSB 29Aug00 				Art_Int.BreakOff(this);				//Loosing fight so run away
//DeadCode CSB 2Nov00 		else
//DeadCode CSB 2Nov00 		{
//DeadCode CSB 2Nov00 		}
//DeadCode CSB 2Nov00 	}
}


void	SAGAirstruc::SAGDecisionCombat()
{
	if((!ai.unfriendly) || (AirStrucPtr(ai.unfriendly)->movecode == AUTOSAG_DESTROYED))
		movecode = AUTOSAG_FOLLOWWP;

	 
//DeadCode CSB 17Jul00 	PatchGroupAndAnim();	//reset heading! Should arrange to do 1 flight per frame
	if (ai.LastAction()==wpengagetargetno)
	{

//DeadCode CSB 2Aug00 		Persons2::PlayerGhostAC->InterceptandRange(&World);
//DeadCode CSB 2Aug00 //	SagExpansionCounter::totalexpanded=0;
//DeadCode CSB 2Aug00 //	SagExpansionCounter::highdemandrange=METRES2000;					//DAW 15/02/00
//DeadCode CSB 2Aug00 		Range*=1.5;	  //prefer to see combat a/c expanded
//DeadCode CSB 2Aug00 
//DeadCode CSB 2Aug00 		PlaneTypeSelect actype=classtype->planetext;
//DeadCode CSB 2Aug00 		assert (actype<PT_GER_NONFLY);
//DeadCode CSB 2Aug00 		if (Range<Persons3::SagExpansionCounter::highdemandrange)
//DeadCode CSB 2Aug00 			if (Persons3::SagExpansionCounter::totalexpanded<250)
//DeadCode CSB 2Aug00 			{
//DeadCode CSB 2Aug00 				if (	(Persons3::sagexpcounts[actype].numactive+fly.numinsag)
//DeadCode CSB 2Aug00 					<=	Persons3::sagexpcounts[actype].numavailable
//DeadCode CSB 2Aug00 					)
//DeadCode CSB 2Aug00 //DeadCode CSB 28Jun00 #pragma warnmsg("************************************")
//DeadCode CSB 2Aug00 //DeadCode CSB 28Jun00 #pragma warnmsg("**** DANGER - SAGS DON'T EXPAND **** //CSB 21/03/00")
//DeadCode CSB 2Aug00 //DeadCode CSB 28Jun00 #pragma warnmsg("************************************")
//DeadCode CSB 2Aug00 //DeadCode CSB 28Jun00 /*
//DeadCode CSB 2Aug00 					ExpandSag();
//DeadCode CSB 2Aug00 //DeadCode CSB 28Jun00 */;
//DeadCode CSB 2Aug00 			}
//DeadCode CSB 2Aug00 
//DeadCode CSB 2Aug00 
	}
	ai.LastAction()=wpacnoactionno;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SAGairgrp::SAGMovementCombat
// Date:		05/07/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGairgrp::SAGMovementCombat(int p,int s)
{
	if (target.Evaluate()<0||target.Evaluate()>IllegalBAND)	
		INT3;
	info_airgrpPtr a=Persons2::ConvertPtrUID(UniqueID(target.Evaluate()));
	if (a && Math_Lib.DistanceSquared(a->World.X-World.X,a->World.Y-World.Y,a->World.Z-World.Z)>METRES3000*METRES3000)
	{
		if (Todays_Packages[p].attackmethod>=Profile::AM_LWPACKS)
		{
			World.Z=a->World.Z-METRES2000+METRES100*(p%16);
			World.X=a->World.X+METRES2000-METRES200*(s%8);
			World.Y=a->World.Y;
		}
		else
		{
			World.Z=a->World.Z+METRES2000-METRES100*(p%16);
			World.X=a->World.X-METRES2000+METRES200*(s%8);
			World.Y=a->World.Y;
		}

		InterceptandRange(&a->World);
		if (!attitude.complex)
			attitude=new RotExpr;
		attitude[1]=HdgIntercept;
		attitude[2]=PitchIntercept;
		hdg=HdgIntercept;
	}
	position.MakeAbsWorldPos(World.Y);
	position[0][0]=World.X;
	position[0][2]=World.Z;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGDecisionCombat
// Date:		06/10/00
// Author:		JIM
//
//Description: 	a=attacker
//				d=defender
//////////////////////////////////////////////////////////////////////
//TempCode MS 23Oct00 enum	{STDKILLLEVEL=10,LOWKILLLEVEL=5};
//enum	{FIRSTKILLLEVEL=30,FIRSTSKILLDIFFMUL=2,STDKILLLEVEL=10,LOWKILLLEVEL=5};
//enum	{FIRSTKILLLEVEL=12,FIRSTSKILLDIFFMUL=1,STDKILLLEVEL=10,LOWKILLLEVEL=5};
enum	{FIRSTKILLLEVEL=15,FIRSTSKILLDIFFMUL=1,STDKILLLEVEL=10,LOWKILLLEVEL=5};

static int CalcSkillDiff(info_airgrpPtr aa,int pa,int sa,info_airgrpPtr ad,int pd,int sd)
{
//	float	skilldiff=0;
	float	skilldiff=
		2*(	Node_Data[Todays_Packages[pd][sd].squadnum].averageskill
				-	Node_Data[Todays_Packages[pa][sa].squadnum].averageskill	)	;
	skilldiff/=SKILL_STAGE;

//DeadCode MS 31Oct00 	if (skilldiff>4)			skilldiff=4;
//DeadCode MS 31Oct00 	elseif (skilldiff<-4)		skilldiff=-4;

//	if defender is a bomber or stuka then it gets a penalty 			//MS 27Oct00
	if (Todays_Packages[pd][sd].Squadron().AcType()>PT_ME110)
		skilldiff-=4;	//was 4									//MS 15Nov00
	if (Todays_Packages[pd][sd].Squadron().AcType()==PT_ME110)
		skilldiff-=2;
//  if defender is a spit or 109 it gets a bonus in defence
//DeadCode MS 16Nov00   	if (Todays_Packages[pd][sd].Squadron().AcType()==PT_ME109)
//DeadCode MS 16Nov00 		skilldiff+=1;
//DeadCode MS 16Nov00 	if (Todays_Packages[pd][sd].Squadron().AcType()==PT_SPIT_A)
//DeadCode MS 16Nov00 		skilldiff+=1;
//DeadCode MS 16Nov00 	if (Todays_Packages[pd][sd].Squadron().AcType()==PT_SPIT_B)
//DeadCode MS 16Nov00 		skilldiff+=1;

//DeadCode MS 16Nov00 //	if attacker is a 110 or Ju87 then it gets a penalty					//MS 27Oct00
//DeadCode MS 16Nov00 	if (Todays_Packages[pa][sa].Squadron().AcType()>PT_ME109)
//DeadCode MS 16Nov00 		skilldiff+=2*(Todays_Packages[pa][sa].Squadron().AcType()-PT_ME109);
//DeadCode MS 16Nov00 //	if attacker is a spit or 109 then it gets a bonus					//MS 27Oct00
//DeadCode MS 16Nov00 	if (Todays_Packages[pa][sa].Squadron().AcType()==PT_ME109)
//DeadCode MS 16Nov00 		skilldiff-=1;
//DeadCode MS 16Nov00 	if (Todays_Packages[pa][sa].Squadron().AcType()==PT_SPIT_A)
//DeadCode MS 16Nov00 		skilldiff-=1;
//DeadCode MS 16Nov00 	if (Todays_Packages[pa][sa].Squadron().AcType()==PT_SPIT_B)
//DeadCode MS 16Nov00 		skilldiff-=1;

	if (Todays_Packages[pa][sa].Squadron().AcType() > PT_ME110)
		skilldiff += 4;	//was 4									//MS 15Nov00
	if (Todays_Packages[pa][sa].Squadron().AcType()==PT_ME110)
		skilldiff += 2;

	if (skilldiff < 0)
		skilldiff=skilldiff*2;

	int acdiff=Todays_Packages[pd][sd].numacleft-Todays_Packages[pa][sa].numacleft;
	skilldiff+=acdiff*0.5;

//	if (skilldiff >= 10)
//		skilldiff = 9;

return skilldiff;

}
//DeadCode MS 28Oct00 static bool	RunOutOfFightTime(int diaryentry)
//DeadCode MS 28Oct00 {	//USe diary to decide wether we have any bullets left...
//DeadCode MS 28Oct00 	SquadronBase* diary=Squad_Diary.GetDiaryPtr(diaryentry);
//DeadCode MS 28Oct00 	int time=0;
//DeadCode MS 28Oct00 	int killcount=0;
//DeadCode MS 28Oct00 	if (diary->squadnum<SQ_LW_START)
//DeadCode MS 28Oct00 	{
//DeadCode MS 28Oct00 		time=Squad_Diary.GetIntercept(diary)->intercepttime;
//DeadCode MS 28Oct00 		UByte* kills=((Diary::Squadron*)(diary))->kills;
//DeadCode MS 28Oct00 		killcount=kills[0]+kills[1]+kills[2]+kills[3]+kills[4]+kills[5];
//DeadCode MS 28Oct00 	}
//DeadCode MS 28Oct00 	else
//DeadCode MS 28Oct00 	{
//DeadCode MS 28Oct00 		Diary::Intercept* di=Squad_Diary.GetFirstIntercept(Squad_Diary.GetRaidGroup(diary));
//DeadCode MS 28Oct00 		if (di)
//DeadCode MS 28Oct00 			time=Squad_Diary.GetFirstIntercept(Squad_Diary.GetRaidGroup(diary))->intercepttime;
//DeadCode MS 28Oct00 		else
//DeadCode MS 28Oct00 			time=MMC.currtime+5*SECSPERMIN;
//DeadCode MS 28Oct00 		UByte* kills=((Diary::Gruppen*)(diary))->kills;
//DeadCode MS 28Oct00 		killcount=kills[0]+kills[1]+kills[2];
//DeadCode MS 28Oct00 		killcount/=3;	//There are usually 3 squads per Grupp. Modify this for a tuning RAF/LW factor
//DeadCode MS 28Oct00 	}
//DeadCode MS 28Oct00 	time=(MMC.currtime-time);
//DeadCode MS 28Oct00 	time+=killcount*30;	
//DeadCode MS 28Oct00 	if (time<14*SECSPERMIN)			
//DeadCode MS 28Oct00 		return false;									
//DeadCode MS 28Oct00 	else if (time>20*SECSPERMIN)	
//DeadCode MS 28Oct00 		return true;
//DeadCode MS 28Oct00 	else 
//DeadCode MS 28Oct00 	{
//DeadCode MS 28Oct00 		int v=Math_Lib.rnd();	 //240=4 mins.
//DeadCode MS 28Oct00 		v=(v&(v>>8)&255);	//high values are improbable
//DeadCode MS 28Oct00 		if (time+v>20*SECSPERMIN)
//DeadCode MS 28Oct00 			return true;
//DeadCode MS 28Oct00 		else						
//DeadCode MS 28Oct00 			return false;								
//DeadCode MS 28Oct00 	}
//DeadCode MS 28Oct00 }

void	Profile::Squad::SendHome()
{
	submethod=SubMethod(submethod|SM_109RETURNING);
	info_airgrpPtr a=Persons2::ConvertPtrUID(instance);
	assert (a->wpref);
	a->movecode=AUTOSAG_FOLLOWWPHOME;
	a->target=ENABLE_COMPLEX_VAL;
	SetStatus(Profile::PS_OUTGOING);
	UniqueID currwp=a->wpref;
	while (currwp)
	{
		info_waypointPtr wp=Persons2::ConvertPtrUID(currwp);
		breakif (wp->wpact.Evaluate()==wpdisperseno);				//JIM 5Jul00
		currwp=wp->NextWP(-1);
	}
	if (currwp)
		a->wpref=currwp;
	assert (a->wpref);
}

void	SAGairgrp::SAGDecisionCombat(int p,int s)
{

	Todays_Packages[p][s].fightperiods++;
	bool	forcetobreak=false;
	movecode=AUTOSAG_COMBATCIRCLES;										//JIM 17Jul00
	bool	iftargetstopfightingforcegohome=false;
	bool	attackergohome=false;
	if (target.Evaluate()<0||target.Evaluate()>IllegalBAND)
		INT3;
	info_airgrpPtr a=Persons2::ConvertPtrUID(UniqueID(target.Evaluate()));
	if (ItemBase::OverFrance(World))//.Z-World.X<-METRES100KM)						//JIM 10Sep00
		forcetobreak=true;
	if (((p+s)&0x03)==((MMC.currtime/40)&0x03))
	{	//Fuel check
		Coords3D p0,p1;
		p0=World;
		p1=Persons2::ConvertPtrUID(Todays_Packages[p][s].Squadron().homeairfield)->World;
		PlaneTypeSelect pt=Todays_Packages[p][s].Squadron().AcType();
		if (Todays_Packages[p].CalcFuel(&p0,&p1,pt,pt,0)+1000000>Todays_Packages[p][s].fuelleft) 
		{
			forcetobreak=true;attackergohome=true;
			Todays_Packages[p][s].submethod=Profile::SubMethod(Todays_Packages[p][s].submethod|Profile::SM_109RETURNING);
		}
	}
	if (a==NULL)
	{
			if (Todays_Packages[p].StopFighting(s,this,true))
			{
				Todays_Packages.ChangeMessagesUID(Todays_Packages[p][s].instance,UID_BIT14+((p)<<5)+Todays_Packages[p].GetRaidIndFromSquadEntry(s));
				Todays_Packages[p][s].ApplyFlyingLosses(Todays_Packages[p].squadlist.AcBitsSquad(s));
				if (Todays_Packages[p].squadlist.AllInStatus(Profile::PS_COMPLETE))
					Todays_Packages[p].PackageComplete(); //UI can recover package...
			}
			return;

	}
	int tp,ts;
	Todays_Packages.GetACSquadEntry(UniqueID(target.Evaluate()),tp,ts);

	if (Todays_Packages[tp][ts].status>Profile::PS_ACTIVE_MAX)
	{
		if (Todays_Packages[p].StopFighting(s,this))
		{
			Todays_Packages.ChangeMessagesUID(Todays_Packages[p][s].instance,UID_BIT14+((p)<<5)+Todays_Packages[p].GetRaidIndFromSquadEntry(s));
			Todays_Packages[p][s].ApplyFlyingLosses(Todays_Packages[p].squadlist.AcBitsSquad(s));
			if (Todays_Packages[p].squadlist.AllInStatus(Profile::PS_COMPLETE))
				Todays_Packages[p].PackageComplete(); //UI can recover package...
		}
		return;
	}

	if (a->target.Evaluate()==GOT_UNDEFINED_VAL || a->target.Evaluate()==0)
	{	//surprise
		int	killthem=FIRSTKILLLEVEL;
		int	skilldiff=CalcSkillDiff(this,p,s,a,tp,ts);
		Todays_Packages[tp][ts].KillSome(killthem-skilldiff*FIRSTSKILLDIFFMUL,Todays_Packages[p][s]);


		//depending what they are they could fight back...
		if (	(Todays_Packages[tp][ts].method&Profile::AM_GROUPMASK)!=Profile::AM_LWPACKS
			||	Todays_Packages[tp][ts].method==Profile::AM_DECOYPATROL
			)
		{
			Coords3D p0,p1;
			p0=a->World;
			p1=Persons2::ConvertPtrUID(Todays_Packages[tp][ts].Squadron().homeairfield)->World;
			PlaneTypeSelect pt=Todays_Packages[tp][ts].Squadron().AcType();
			if (!(Todays_Packages[tp][ts].submethod&Profile::SM_109RETURNING))
				if (Todays_Packages[tp].CalcFuel(&p0,&p1,pt,pt,0)+1000000<Todays_Packages[tp][ts].fuelleft)	//MS 26Oct00
				{
					a->movecode=AUTOSAG_COMBAT;
					Todays_Packages[tp][ts].SetStatus(Profile::PS_ENEMYSIGHTED);

					a->target=Todays_Packages[p][s].instance;
					if (a->target.Evaluate()<0||a->target.Evaluate()>IllegalBAND)
						INT3;	
				}
				else
				{
					Todays_Packages[tp][ts].SendHome();					//MS 26Oct00
	//DeadCode JIM 9Oct00 				INT3;	//Target has run out of fuel so can't respond!
				}
		}
		else
		{	//Find an escort and bring that in to respond
			//first: If attacker already being handled, then change it to the attackee
			iftargetstopfightingforcegohome=true;
			info_airgrpPtr ptr=NULL;
			int	defenderline=0;
			if (Math_Lib.rnd(3)==0)										//MS 28Oct00
				Todays_Packages[p][s].KillSome(1,Todays_Packages[tp][ts]);

			int re=Todays_Packages[tp].GetRaidIndFromSquadEntry(ts);
			int sqmin=Todays_Packages[tp].RaidNumEntriesMinSq(re);
			{	//find out if already being handled....
				int sqmax=Todays_Packages[tp].RaidNumEntriesMaxSq(re);
				UniqueID ouruid=Todays_Packages[p][s].instance;
				for (;sqmin<sqmax;sqmax--)
				{
						ptr=Persons2::ConvertPtrUID(Todays_Packages[tp][sqmax].instance);
						if (ptr && ptr->target.Evaluate()==ouruid)
						{
							defenderline=sqmax;
							break;
						}
				}

			}			
			if (defenderline)
			{
				if (ptr->movecode==AUTOSAG_COMBAT|| ptr->movecode==AUTOSAG_COMBATCIRCLES)
					if (Math_Lib.rnd(Todays_Packages[p][s].numacoriginal*3)>=Todays_Packages[p][s].numacleft)
						target=Todays_Packages[tp][defenderline].instance;
			}
			else
			{
//DeadCode CSB 17Aug00 				int re=Todays_Packages[tp].GetRaidIndFromSquadEntry(ts);
//DeadCode CSB 17Aug00 				int sqmin=Todays_Packages[tp].RaidNumEntriesMinSq(re);
				int sqmax=Todays_Packages[tp].RaidNumEntriesMaxSq(re);
				int	sparesq=-1,escortsq=-1;
				for (;sqmin<=sqmax;sqmax--)
					if (	Todays_Packages[tp][sqmax].method>=Profile::AM_DETACHED 
						&&	Todays_Packages[tp][sqmax].status<Profile::PS_ACTIVE_MAX
						&&	Todays_Packages[tp][sqmax].status>Profile::PS_TAKINGOFF
						&&	!(Todays_Packages[tp][sqmax].submethod&Profile::SM_109RETURNING)
						)
					{	//Is there any available escort?
						info_airgrpPtr p=Persons2::ConvertPtrUID(Todays_Packages[tp][sqmax].instance);
						if (p)
							if (p->target.Evaluate()==ENABLE_COMPLEX_VAL || p->target.Evaluate()==0)
							{
								if (Math_Lib.DistanceSquared(p->World.X-World.X,p->World.Z-World.Z)<METRES20KM*METRES20KM)
									if (Math_Lib.DistanceSquared(p->World.X-World.X,p->World.Z-World.Z)<METRES10KM*METRES10KM)
										if (p->leader.Evaluate()==Todays_Packages[tp][ts].instance
											&& (	Todays_Packages[tp][sqmax].method<=Profile::AM_RETURNESCORT 
												||	p->movecode!=AUTOSAG_FOLLOWWP
											)	)
											escortsq=sqmax;
										else
											sparesq=sqmax;
									else
										if (sparesq==-1)
											sparesq=sqmax;
							}
					}
				NOP;
				if (escortsq!=-1)
					sparesq=escortsq;
//DeadCode MS 26Oct00 				else	if (Todays_Packages[tp][ts].numacleft)		//If no close escort LW get a second bash!
//DeadCode MS 26Oct00 						Todays_Packages[tp][ts].KillSome(FIRSTKILLLEVEL-skilldiff,Todays_Packages[p][s]);
				if (sparesq==-1)
				{	//look at detached escorts
					for (sqmin=0,sqmax=Todays_Packages[tp].squadlist-1;sqmin<=sqmax;sqmax--)
						if (	Todays_Packages[tp][sqmax].method>=Profile::AM_DETACHED 
 							&&	Todays_Packages[tp][sqmax].status<Profile::PS_TAKINGOFF
 							&&	Todays_Packages[tp][sqmax].status>Profile::PS_ACTIVE_MAX
							&&	!(Todays_Packages[tp][sqmax].submethod&Profile::SM_109RETURNING)
							)
						{	//Is there any available escort?
							info_airgrpPtr p=Persons2::ConvertPtrUID(Todays_Packages[tp][sqmax].instance);
							if (p && p->target.Evaluate()==ENABLE_COMPLEX_VAL)
								if (Math_Lib.DistanceSquared(p->World.X-World.X,p->World.Z-World.Z)<METRES10KM*METRES10KM)
									if (p->leader.Evaluate()==Todays_Packages[tp][ts].instance)
										escortsq=sqmax;
									else
										if (escortsq==-1 && Todays_Packages[tp][sqmax].method<Profile::AM_ATTACHED)
											escortsq=sqmax;
										else
											sparesq=sqmax;
								else
									if (sparesq==-1)
										sparesq=sqmax;
						}
					if (escortsq!=-1)
						sparesq=escortsq;
					escortsq=-1;	//I want to say 'if not the close escort then do precombat'
				}

				if (sparesq!=-1)
				{
					info_airgrpPtr ap=Persons2::ConvertPtrUID(Todays_Packages[tp][sparesq].instance);
					if (escortsq!=-1)	//If not close escort go to precombat first...
					{
						ap->movecode=AUTOSAG_COMBAT;
						Todays_Packages[tp][sparesq].SetStatus(Profile::PS_ENEMYSIGHTED);
					}
					else
					{
						ap->movecode=AUTOSAG_PRECOMBAT;
						Todays_Packages[tp][sparesq].SetStatus(Profile::PS_ENEMYSIGHTED);
					}

					ap->target=Todays_Packages[p][s].instance;				//RDH 17/05/00
					if (ap->target.Evaluate()<0||ap->target.Evaluate()>IllegalBAND)	
						INT3;

				}
				else
					if (Todays_Packages[tp][ts].Squadron().AcType()==PT_JU87)
					{	//JU87's can fight if no escort! But must dump bombs - so go home.
						a->movecode=AUTOSAG_COMBAT;
						Todays_Packages[tp][ts].SetStatus(Profile::PS_ENEMYSIGHTED);
						a->target=Todays_Packages[p][s].instance;
 						UniqueID currwp=a->wpref;
						while (currwp)
						{
							info_waypointPtr wp=Persons2::ConvertPtrUID(currwp);
							breakif (wp->wpact.Evaluate()==wpdisperseno);				//JIM 5Jul00
							currwp=wp->NextWP(ts);
						}
						if (currwp)
							a->wpref=currwp;
				    	assert (wpref);

						if (a->target.Evaluate()<0||a->target.Evaluate()>IllegalBAND)	
							INT3;

					}
			}
		}
	}
	else
	{	//even fight			(between fighters (or unescorted JU87s))
		//kill some of them
		if (a->target!=Todays_Packages[p][s].instance)
		{	//2 onto 1
			int currtrgsq;
#ifndef NDEBUG
			if (	!Todays_Packages[p].GetACSquadEntry(UniqueID(a->target.Evaluate()),currtrgsq)
				||	 (Todays_Packages[p][currtrgsq].method&Profile::AM_GROUPMASK)!=Profile::AM_LWPACKS
				)
				NOP;
#endif
			currtrgsq=Todays_Packages[p][s].instance;
			if (Math_Lib.rnd(Todays_Packages[p][s].numacoriginal*3)>=Todays_Packages[p][s].numacleft)
			{	//That's not fair... I'm getting the gang 'round!
				int sparesq=-1,escortsq=-1;
				int sharedleader=a->leader;
				UniqueID myinst;
				if (sharedleader==ENABLE_COMPLEX_VAL || sharedleader==0)
					sharedleader=-2;

				for (int sqmin=0,sqmax=Todays_Packages[tp].squadlist-1;sqmin<=sqmax;sqmax--)
					if (	Todays_Packages[tp][sqmax].method>=Profile::AM_DETACHED 
 						&&	Todays_Packages[tp][sqmax].status<Profile::PS_ACTIVE_MAX
						&&	Todays_Packages[tp][sqmax].status>Profile::PS_TAKINGOFF
						&&	!(Todays_Packages[tp][sqmax].submethod&Profile::SM_109RETURNING)
						)
					{	//Is there any available escort?
						myinst=Todays_Packages[tp][sqmax].instance;
						info_airgrpPtr p=Persons2::ConvertPtrUID(myinst);
							if (p)
								if (p->target.Evaluate()==ENABLE_COMPLEX_VAL)
								{
									if (Math_Lib.DistanceSquared(p->World.X-World.X,p->World.Z-World.Z)<METRES10KM*METRES10KM)
										if (	p->leader==Todays_Packages[tp][ts].instance
											||	p->leader==sharedleader
											||	myinst==sharedleader
											)
											escortsq=sqmax;
										else
											if (escortsq==-1 && Todays_Packages[tp][sqmax].method<Profile::AM_ATTACHED)
												escortsq=sqmax;
											else
												sparesq=sqmax;
									else
										if (sparesq==-1)
											sparesq=sqmax;
								}
								else
									if (p->target.Evaluate()==currtrgsq)	  //Someone already assigned!
									{	//Already dealt with
										escortsq=-2;
										break;
									}
					}
				NOP;
				if (escortsq!=-1)	 sparesq=escortsq;
				if (sparesq!=-2)
					if (sparesq!=-1)
					{
						info_airgrpPtr ap=Persons2::ConvertPtrUID(Todays_Packages[tp][sparesq].instance);
						ap->movecode=AUTOSAG_PRECOMBAT;
						ap->target=currtrgsq;
						Todays_Packages[tp][sparesq].SetStatus(Profile::PS_ENEMYSIGHTED);
					}
					else
						a->target=Todays_Packages[p][s].instance;
			}
			else
			if (Math_Lib.rnd(Todays_Packages[p][s].numacoriginal*3)>=Todays_Packages[p][s].numacleft)
			{
				a->target=Todays_Packages[p][s].instance;
			}

		}

		int	killthem=STDKILLLEVEL;
		int	skilldiff=CalcSkillDiff(this,p,s,a,tp,ts);
		if(Todays_Packages[p][s].Squadron().AcType()!=PT_JU87)
			if (Todays_Packages[tp][ts].KillSome(killthem-skilldiff,Todays_Packages[p][s]))
				if (Todays_Packages[tp][ts].Squadron().AcType()==PT_JU87 && Math_Lib.rnd()>0x5000)
					forcetobreak=true;
//DeadCode JIM 20Oct00 		SquadronBase*	squaddiary=Squad_Diary.GetDiaryPtr(Todays_Packages[tp][ts].diaryentry);



		//kill some of us
//		if (a->target==Todays_Packages[p][s].instance && skilldiff>-LOWKILLLEVEL)
//		{
//			killthem=LOWKILLLEVEL+skilldiff;
//DeadCode MS 18Oct00 		if (killthem>Todays_Packages[p][s].numacleft)
//DeadCode MS 18Oct00 			killthem=Todays_Packages[p][s].numacleft+1;
//		killthem=Math_Lib.rnd(killthem);
//			Todays_Packages[p][s].KillSome(killthem,Todays_Packages[tp][ts]);						//RDH 16/05/00
//		}
	}
	//Code to handle running out of aircraft

	if (Todays_Packages[p][s].numacleft<Todays_Packages[p][s].numacoriginal)
	{
		if (	Todays_Packages[p][s].numacleft<3
			||	Todays_Packages[p][s].numacleft*300+Todays_Packages[p][s].Squadron().averagemorale<Todays_Packages[p][s].numacoriginal*200
			)
			forcetobreak=true;

	}
	if (Todays_Packages[tp][ts].numacleft<Todays_Packages[tp][ts].numacoriginal)
		if (	Todays_Packages[tp][ts].numacleft<3
			||	Todays_Packages[tp][ts].numacleft*300+Todays_Packages[tp][ts].Squadron().averagemorale<Todays_Packages[tp][ts].numacoriginal*200
			)
			forcetobreak=true;

//DeadCode MS 28Oct00 	//Mark wants me to use the diary to tell if they have run out of bullets!
//DeadCode MS 28Oct00 	if (RunOutOfFightTime(Todays_Packages[p][s].diaryentry))
//DeadCode MS 28Oct00 	{
//DeadCode MS 28Oct00 		forcetobreak=true;
//DeadCode MS 28Oct00 		attackergohome=true;
//DeadCode MS 28Oct00 	}

	//Mark wants me to use the diary to tell if they have run out of bullets!
	if (Todays_Packages[p][s].fightperiods+Math_Lib.rnd(5)>20)	// RunOutOfFightTime(Todays_Packages[p][s].diaryentry,Todays_Packages[tp][ts].diaryentry))
	{	//20 periods=20x40 seconds = 800 seconds = 12 minutes.
		forcetobreak=true;
		attackergohome=true;
	}

	if (	forcetobreak	)
	{
		if (Todays_Packages[p].StopFighting(s,this,attackergohome))
		{
			Todays_Packages.ChangeMessagesUID(Todays_Packages[p][s].instance,UID_BIT14+((p)<<5)+Todays_Packages[p].GetRaidIndFromSquadEntry(s));
			Todays_Packages[p][s].ApplyFlyingLosses(Todays_Packages[p].squadlist.AcBitsSquad(s));
			if (Todays_Packages[p].squadlist.AllInStatus(Profile::PS_COMPLETE))
				Todays_Packages[p].PackageComplete(); //UI can recover package...
		}		
		if (Todays_Packages[tp].StopFighting(ts,a,iftargetstopfightingforcegohome))
		{
			Todays_Packages.ChangeMessagesUID(Todays_Packages[tp][ts].instance,UID_BIT14+((tp)<<5)+Todays_Packages[tp].GetRaidIndFromSquadEntry(ts));
			Todays_Packages[tp][ts].ApplyFlyingLosses(Todays_Packages[tp].squadlist.AcBitsSquad(ts));
			if (Todays_Packages[tp].squadlist.AllInStatus(Profile::PS_COMPLETE))
				Todays_Packages[tp].PackageComplete(); //UI can recover package...
		}
	}

}
//////////////////////////////////////////////////////////////////////
//
// Function:    StopFighting
// Date:		22/10/00
// Author:		JIM
//
//Description: 	 squad.
//
//////////////////////////////////////////////////////////////////////
bool	Profile::StopFighting(int sl,info_airgrpPtr a,bool forcegohome)
{
	Squad& squad=squadlist[sl];
	if (squad.numacleft==0)
	{	//dead - remove squad
		//allow detection of removal when others land
		//allow package removal if this is last one
		if (squad.method>Profile::AM_LWPACKS)
		{
			Diary::RaidGroup* rg=Squad_Diary.GetRaidGroup(Squad_Diary.GetDiaryPtr(squad.diaryentry));		//JIM 5Jul00
			if (rg->missresult>MR_LOSTAPPRTARG)
				rg->missresult=MR_LOSTLEAVETARG;
			else
				rg->missresult=MR_LOSTAPPRTARG;
		}

		a->movecode=AUTOSAG_DESTROYED;
		a->target=ENABLE_COMPLEX_VAL;
		SquadComplete(sl);

		return true;
	}
	elseif 	(	!forcegohome 
			&&	squad.numacleft*2>squad.numacoriginal	)
	{	//stop this fight but can fight again	- but only if in combat!!!
		if (a->movecode==AUTOSAG_COMBAT || a->movecode==AUTOSAG_COMBATCIRCLES)
			if (squad.method<Profile::AM_LWPACKS)
			{
				a->movecode=AUTOSAG_PRECOMBAT;	//should bring it round again
				squad.SetStatus(Profile::PS_DETAILRAID);				//MS 25Oct00
			}
			else
			{
//DeadCode MS 7Sep00 				a->movecode=AUTOSAG_FOLLOWWP;
//DeadCode MS 7Sep00 				SetStatus(Profile::PS_OUTGOING);
				//find the other package
				UniqueID trg=UniqueID(a->target.Evaluate());
				int	p,sq;
				Todays_Packages.GetACSquadEntry(trg,p,sq);
				Diary::RaidGroup* rg=Squad_Diary.GetRaidGroup(Squad_Diary.GetDiaryPtr(squad.diaryentry));		//JIM 5Jul00
				if (rg->missresult<=MR_ABORTEDTARG)
					if (Todays_Packages[p][sq].numacditched*2>squad.numacditched*3)
						if (Todays_Packages[p][sq].numacditched*3>squad.numacditched*2)
							rg->missresult=MR_ENGAGEDGOODRES;
						else
							rg->missresult=MR_ENGAGEDMEDRES;
					else
							rg->missresult=MR_ENGAGEDBADRES;
				if (	squadlist.AnyMainInStatus(Profile::PS_INCOMING)
					||	squadlist.AnyMainInStatus(Profile::PS_TARGETAREA) )
				{
					a->movecode=AUTOSAG_FOLLOWWP;							//MS 7Sep00
					squad.SetStatus(Profile::PS_INCOMING);						//MS 7Sep00
				}
				else
				{
					a->movecode=AUTOSAG_FOLLOWWPHOME;							//MS 7Sep00
					squad.SetStatus(Profile::PS_OUTGOING);						//MS 7Sep00
					UniqueID wpref=a->wpref;
		 			while (wpref)
					{
						info_waypointPtr wp=Persons2::ConvertPtrUID(wpref);
						int name=wp->uid.Evaluate();
						breakif (name==-SGR_WPP_EscDisperse || name==-SGR_WPP_BombDisperse);
						wpref=wp->NextWP(sl);
					}
					if (wpref)
						a->wpref=wpref;
					assert(a->wpref);
				}

				a->target=ENABLE_COMPLEX_VAL;							//MS 7Sep00

			}
		return false;
	}
	else
	{	//can return home
		squad.SendHome();
		//If it is a LW bomber we can send the whole Grupp home...
		if (squad.method>Profile::AM_LWPACKS && squad.method<Profile::AM_ESCORTTYPES)
			if (Math_Lib.rnd()>RND50PC)
			{	//Ok.. I want to send the whole squad home
				if (sl>=1 && squadlist[sl-1].squadnum==squad.squadnum)
					{
						squadlist[sl-1].SendHome();
						if (sl>=2 &&  squadlist[sl-2].squadnum==squad.squadnum)
						{
							squadlist[sl-2].SendHome();
							if (sl>=3 &&  squadlist[sl-3].squadnum==squad.squadnum)
								squadlist[sl-3].SendHome();
						}
					}
				int max=squadlist;
				if (sl+1<max && squadlist[sl+1].squadnum==squad.squadnum)
					{
						squadlist[sl+1].SendHome();
						if (sl+2<max &&  squadlist[sl+2].squadnum==squad.squadnum)
						{
							squadlist[sl+2].SendHome();
							if (sl+3<max &&  squadlist[sl+3].squadnum==squad.squadnum)
								squadlist[sl+3].SendHome();
						}
					}
			}


		if (squad.method>Profile::AM_LWPACKS)
		{
			Diary::RaidGroup* rg=Squad_Diary.GetRaidGroup(Squad_Diary.GetDiaryPtr(squad.diaryentry));		//JIM 5Jul00
			if (rg->missresult<MR_ABORTEDTARG)
				rg->missresult=MR_ABORTEDTARG;
		}
		return false;
	}

}

//////////////////////////////////////////////////////////////////////
//
// Function:    KillSome
// Date:		20/06/00
// Author:		JIM
//
//Description: The how many figure is 'far too high' for 1 40 second period
//				Craig wants less than 1 aircraft to die, rather than my max=4
//			Returns how many were killed (0 or 1)
//////////////////////////////////////////////////////////////////////
int	Profile::Squad::KillSome(int howmanytokill,Profile::Squad& killer)
{
	assert ((method<AM_LWPACKS)!=(killer.method<AM_LWPACKS));
	enum	
	{	//Input chance is 2 to 14 per 20 or 40 second period for fighters, and 1 for bombers
		PER_FR_FACTOR=75	//90												//JIM 30Sep00	//MS 16Nov00
	};
//TempCode MS 22Oct00 		enum	{	KILL_LOW=0x5000,KILL_MED=0x9000,KILL_HIGH=0xB000,
//TempCode MS 22Oct00 					KILL_LOSS=0xD000,KILL_PILOT=0xE000,KILL_LEADER=0xFF00};
//TempCode MS 22Oct00 		enum	{	KILL_LOW=0x5000,KILL_MED=0x0B00,KILL_HIGH=0xC000,
//TempCode MS 22Oct00 					KILL_LOSS=0xD000,KILL_PILOT=0xE000,KILL_LEADER=0xFF00};
//TempCode MS 23Oct00 		enum	{	KILL_LOW=0x5000,KILL_MED=0x0A000,KILL_HIGH=0xC800,
//TempCode MS 23Oct00 					KILL_LOSS=0xD000,KILL_PILOT=0xE000,KILL_LEADER=0xFF00};
//		enum	{	KILL_LOW=0x7000,KILL_MED=0x0A000,KILL_HIGH=0xC800,
//					KILL_LOSS=0xD000,KILL_PILOT=0xE000,KILL_LEADER=0xFF00};
//		enum	{	KILL_LOW=0x5000,KILL_MED=0x08800,KILL_HIGH=0xB000,
//					KILL_LOSS=0xC000,KILL_PILOT=0xE000,KILL_LEADER=0xFF00};
		enum	{	KILL_LOW=0x2000,KILL_MED=0x05000,KILL_HIGH=0x9000,
					KILL_LOSS=0xA000,KILL_PILOT=0xD000,KILL_LEADER=0xFF00};



// Squad:
//	ULong	numacoriginal:8,			//Unchanged from launch
//			numacleft:4,				//Left+ditched=original
//			numacditched:4,
//			numacrecoveredlow:4,		//recoveredlow<left - only if ditched 
//			numacrecoveredmed:4,		//recoveredmed+recoveredbad+pilotsleft<ditched
//			numacrecoveredbad:4,		
//			numpilotslost:4;
// Diary:
//	UByte		numlosses;	// filled in when ac in this squadron is killed
//	UByte		numacdamaged;	// filled in when ac in this squadron is damaged
//	UByte		numpilotslost;	// if killed ac, not ejected
//	LeadKilled	leaderkilled;	// if killed is leader, LK_1ST (formpos==0) or LK_OTHER (formpos!=0)
//	UByte		noaclaunched;
	SquadronBase*	squaddiary=Squad_Diary.GetDiaryPtr(diaryentry);
	SquadronBase*	killersquaddiary=Squad_Diary.GetDiaryPtr(killer.diaryentry);

	bool dokill=Math_Lib.rnd(PER_FR_FACTOR)<howmanytokill;
	//With this logic, 0 will always fail because rnd(THOUS_PER_KILL) is always < THOUS_PER_KILL
	//All other values have equally sized windows
	int rv=0;
	COMBATSHIFT=3;
	UByte buff[3]={'A'+instance-SagBAND,0,0};
	if (howmanytokill>15)
		buff[2]='+';
	if (howmanytokill>25)
		buff[2]='#';


	if (dokill)
	{	//If value is below KILL_LOW then AC is not killed or damaged
		//If value is below KILL_HIGH then AC is damaged (low or medium) low carry on fighting
		//If value is below KILL_PILOT then AC is lost (write-off or destroyed)
		//If LW AC is over England then ditance determines increased chance of pilot lost
		howmanytokill=1;
		if (numacleft)
		for (int i=0;i<howmanytokill;i++)
		{

			int level=Math_Lib.rnd();
			if (level>KILL_LOSS)
			{	
				rv+=1;
				if (Math_Lib.rnd(numacleft)<numacrecoveredlow)
				{
					numacrecoveredlow--;
					assert(squaddiary->numacdamaged);
					squaddiary->numacdamaged--;
				}
				numacleft--;
				numacditched++;
				squaddiary->numlosses++;
				killersquaddiary->CreditClaim(Squadron().AcType(),1);
//DeadCode RJS 12Nov00 				MMC.thisweekreview.Note(killer.Squadron().AcType(),Squadron().AcType(),1);
				Coords3D& w=Persons2::ConvertPtrUID(instance)->World;
				if (method>=AM_LWPACKS && !ItemBase::OverFrance(w))
					level+=(w.Z-w.X+METRES100KM)/METRES10;
					

				if (level>KILL_PILOT)
				{
					numpilotslost++;
					squaddiary->numpilotslost++;
					if (Squadron().AcType()>=PT_ME110)
						squaddiary->numpilotslost++;
					if (Squadron().AcType()>=PT_GER_NONFLY)
						squaddiary->numpilotslost+=3;

					if (level>KILL_LEADER)
					{
						squaddiary->leaderkilled=LK_1ST;
						leaderlost=true;
					}
				}

			}
			else
				if (level>KILL_LOW)
				{
					if (level>KILL_MED)
					{
						if (Math_Lib.rnd(numacleft)<numacrecoveredlow)
							numacrecoveredlow--;
						else
							squaddiary->numacdamaged++;
						numacleft--;
						numacditched++;
						if (level>KILL_HIGH)
							numacrecoveredbad++;
						else
							numacrecoveredmed++;
						killersquaddiary->CreditClaim(Squadron().AcType(),1);
//DeadCode RJS 12Nov00 						MMC.thisweekreview.Note(killer.Squadron().AcType(),Squadron().AcType(),1);
					}
					else
						if ((numacleft-numacrecoveredlow)>0)
						{
							numacrecoveredlow++;
							squaddiary->numacdamaged++;
						}
				}
				//else none get killed
				else
					buff[0]+=32;


		}

	}
	else
		buff[0]+=32;
	if (howmanytokill<7 || howmanytokill>15)
		Mono_Text.PrintAt(DEBUGCOLUMN+1,killer.instance-SagBAND,buff);
	else
		Mono_Text.PrintAt(DEBUGCOLUMN+2,killer.instance-SagBAND,buff);
	return rv;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementCombatCircles
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementCombatCircles()
{
	movecode = AUTOSAG_COMBAT;
	SAGMovementCombat();
}


void	SAGairgrp::SAGMovementCombatCircles(int p,int s)
{
}

void	SAGAirstruc::SAGDecisionCombatCircles()
{
//DeadCode CSB 17Jul00 	PatchGroupAndAnim();	//reset heading! Should arrange to do 1 flight per frame
}

void	SAGairgrp::SAGDecisionCombatCircles(int p,int s)
{
		movecode=AUTOSAG_COMBAT;

}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementPostCombat
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementPostCombat()
{
	movecode = AUTOSAG_FOLLOWWP;
	SAGMovementFollowWP();

	if(PatchAppropriate())
		PatchGroupAndAnim();	
	
	int DoNothingForABreakpoint = 0;
}

void	SAGairgrp::SAGMovementPostCombat(int p,int s)
{
}
void	SAGAirstruc::SAGDecisionPostCombat()
{
//DeadCode CSB 17Jul00 	PatchGroupAndAnim();	//reset heading! Should arrange to do 1 flight per frame
}

void	SAGairgrp::SAGDecisionPostCombat(int p,int s)
{
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementBombingApproach
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementBombingApproach()
{
	movecode = AUTOSAG_FOLLOWWP;
	ai.unfriendly = NULL;

	if(PatchAppropriate())
		PatchGroupAndAnim();	
	
	Move().AutoFollowWp();
}


void	SAGairgrp::SAGMovementBombingApproach(int p,int s)
{
	info_airgrp* escortee=GetValidEscortee(p,s);
	if (!escortee)
		if (Todays_Packages[p][s].Squadron().AcType()<=PT_JU87)
			CruiseToWp(SECSPERSAGFRAME/2,false,true);
		else
			CruiseToWp(SECSPERSAGFRAME,false,true);
	else
		FlyAsEscort(escortee,p,s);

}
void	SAGAirstruc::SAGDecisionBombingApproach()
{
//DeadCode CSB 17Jul00 	PatchGroupAndAnim();	//reset heading! Should arrange to do 1 flight per frame
}

void	SAGairgrp::SAGDecisionBombingApproach(int p,int s)
{
	int travel;
	info_waypoint* wp;
	WaypointOffsetSub wos;								
	if (!GetCruiseToWp(5,false,true,	travel,wp,wos))								
		movecode=AUTOSAG_BOMB;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementBombing
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementBombing()
{
	if(PatchAppropriate())
		PatchGroupAndAnim();	
	
	Move().AutoBomb();
}


void	SAGairgrp::SAGMovementBombing(int p,int s)
{
	info_waypointPtr wp=Persons2::ConvertPtrUID(wpref);

//DeadCode JIM 29Oct00 	World=wp->World;
}
void	SAGAirstruc::SAGDecisionBombing()
{
//DeadCode CSB 17Jul00 		PatchGroupAndAnim();	//reset heading! Should arrange to do 1 flight per frame
}

void	SAGairgrp::SAGDecisionBombing(int p,int s)
{
	//damage the target	
	//I think the waypoint has already moved on.
	Todays_Packages[p][s].SetStatus(Profile::PS_OUTGOING);
	Diary::RaidGroup* rg=Squad_Diary.GetRaidGroup(Squad_Diary.GetDiaryPtr(Todays_Packages[p][s].diaryentry));	
	if (Todays_Packages[p][s].method==Profile::AM_RECON)
	{
		rg->missresult=MR_RECONCOMPLETED;
	}
	else
		if (	MMC.Sky.Press0+(Todays_Packages[p][s].Squadron().averageskill/3)<1010
			&&	World.Y>METRES2000	)
		{
			rg->missresult=MR_ABORTEDTARG;
			Node_Data.intel.AddMessage(IntelMsg::HIGH_SPOTTING_LW,AS_TARG,SCRIPT_RAIDFAILHITTARGET ,Todays_Packages[p][s].instance,Todays_Packages[p].SquadTarget(s),TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p].CountRaid(s)));
			Node_Data.intel.AddMessage(IntelMsg::HIGH_SPOTTING_WOMAN,AS_TARG,SCRIPT_RAIDTURNEDAWAY ,Todays_Packages[p][s].instance,Todays_Packages[p].SquadTarget(s),TargetIndexes(Todays_Packages[p][s].squadnum,Todays_Packages[p].CountRaid(s)));
		}
		else
		{
			int newlevel=0;
			if (Todays_Packages[p][s].method<Profile::AM_ESCORTTYPES)
			{
				if (Todays_Packages[p].squadlist.AnyMainInStatus(Profile::PS_TARGETAREA))
					newlevel=FakeDamage(Todays_Packages[p].SquadTarget(s),Todays_Packages[p][s].numacleft,Todays_Packages[p][s].Squadron().AcType(),UID_NULL);	//JIM 14Sep00
				else
					newlevel=FakeDamage(Todays_Packages[p].SquadTarget(s),Todays_Packages[p][s].numacleft,Todays_Packages[p][s].Squadron().AcType(),Todays_Packages[p][s].instance);	//JIM 14Sep00
				if (newlevel<Target::TS_LIGHTDAMAGE)
					rg->missresult=MR_ATTACKNODAMAGE;
				else 
					if (newlevel<Target::TS_BADDAMAGE)
						rg->missresult=MR_ATTACKSLIGHTDAMAGE;
					else
						rg->missresult=MR_ATTACKSUCCESS;
			}
		}
	movecode=AUTOSAG_FOLLOWWPHOME;
}


//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementDeathGlide
// Date:		15/08/00
// Author:		Craig Beeston
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementDeathGlide()
{
	if(PatchAppropriate())
		PatchGroupAndAnim();	
	
	Move().AutoDeathGlide();
}


//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementTrackExpanded
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementTrackExpanded()
{
	AirStrucPtr	xl=fly.expandedsag;
	assert(xl);
	World=xl->World;
	roll=xl->roll;
	hdg=xl->hdg;
	pitch=xl->pitch;
	waypoint=xl->waypoint;

	vel_ = xl->vel_;													//CSB 25Jul00
	vel_x = xl->vel_x;													//CSB 25Jul00
	vel_y = xl->vel_y;													//CSB 25Jul00
	vel_z = xl->vel_z;													//CSB 25Jul00
	ai.ManStep <<= xl->ai.ManStep;										//CSB 25Jul00
	ai.manoeuvre <<= xl->ai.manoeuvre;									//CSB 25Jul00
	information = xl->information;										//CSB 21Aug00
	if(xl->ai.unfriendly)// && (classtype->aerobaticfactor != AEROBATIC_LOW))					//CSB 1Aug00
	{																							//CSB 1Aug00
		if(xl->ai.unfriendly->Status.size == AIRSTRUCSIZE)										//CSB 1Aug00
		{																						//CSB 1Aug00
			AirStrucPtr unf = AirStrucPtr(xl->ai.unfriendly);									//CSB 1Aug00
			if((unf->fly.expandedsag) && (!unf->fly.numinsag))									//CSB 7Aug00
			{																					//CSB 7Aug00
				if(ai.unfriendly != unf->fly.expandedsag)										//CSB 1Aug00
					SetUnfriendly(unf->fly.expandedsag);										//CSB 1Aug00
			}																					//CSB 7Aug00
			else if(ai.unfriendly != unf)														//CSB 1Aug00
				SetUnfriendly(unf);																//CSB 1Aug00
			if((xl->movecode == AUTO_COMBAT) || (xl->movecode == AUTO_PRECOMBAT))				//CSB 4Aug00
				movecode = AUTOSAG_TRACKEXPCOMBAT;												//CSB 4Aug00
		}																						//CSB 1Aug00
		else																					//CSB 1Aug00
			ai.unfriendly = xl->ai.unfriendly;									//CSB 31Jul00	//CSB 1Aug00
	}																							//CSB 1Aug00
	else																						//CSB 1Aug00
		if(		(xl->movecode != AUTO_COMBAT)
			&&	(xl->movecode != AUTO_PRECOMBAT)	)
		{
			movecode = AUTOSAG_TRACKEXPFOLLOW;
			if((ai.unfriendly) && (xl->movecode != AUTO_BOMB))
			{
				if((ai.unfriendly->Status.size == AIRSTRUCSIZE) && (AirStrucPtr(ai.unfriendly)->ai.attacker == this))
					AirStrucPtr(ai.unfriendly)->ai.attacker = NULL;
				ai.unfriendly = NULL;
			}
		}

	uniqueID.changed = TRUE;									//CSB 24/05/00
}


void	SAGairgrp::SAGMovementTrackExpanded(int p,int s)
{	//Never happens
}


void	SAGAirstruc::SAGDecisionTrackExpanded()
{
	if(fly.expandedsag->PlayerInGroup())								//CSB 27Jul00
		return;															//CSB 27Jul00

	PlaneTypeSelect actype = MergeTypes(classtype->planetext);															//CSB 27Jul00
	if(classtype->planetext > PT_GER_NONFLY)																			//CSB 27Jul00
		actype = PT_GER_NONFLY;																							//CSB 27Jul00
																														//CSB 27Jul00
	FP Range2 = Distance3DSquared(&Persons2::PlayerGhostAC->World);														//CSB 27Jul00
	if(Range2 < FP(2 * VISIBLERANGE) * FP(2 * VISIBLERANGE))
	{
		for(AirStrucPtr ld = fly.expandedsag; ld; ld = ld->fly.nextflight)
			for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
			{
				FP range2 = ac->Distance3DSquared(&Persons2::PlayerGhostAC->World);
				if(range2 < Range2)
					Range2 = range2;
			}

		FP TriggerRange2 = Persons3::sagexpcounts[actype].currenttriggerrange;												//CSB 27Jul00
		TriggerRange2 *= TriggerRange2;																						//CSB 27Jul00
		if((movecode == AUTOSAG_TRACKEXPCOMBAT)	|| (ai.attacker))															//CSB 27Jul00
			Range2 *= (1.0 / (4.0 * 4.0));																					//CSB 27Jul00
																														
		if(Range2 > TriggerRange2)
		{
			if(Range2 > 4 * TriggerRange2)
				ContractSag(false);
			else
			{
				bool inform = true;
				for(AirStrucPtr l = fly.expandedsag; l; l = l->fly.nextflight)
					for(AirStrucPtr w = l; w; w = w->Follower())
						if(!w->information)
							inform = false;
				if(inform)
					ContractSag(false);	
			}
		}
	}
	else
		ContractSag(false);

	assert((movecode&-2)!=AUTOSAG_TRACKEXPFOLLOW || fly.expandedsag);
}
//DeadCode CSB 27Jul00 	//May decide to close up.
//DeadCode CSB 27Jul00 	Persons2::PlayerGhostAC->InterceptandRange(&World);
//DeadCode CSB 27Jul00 	PlaneTypeSelect actype = classtype->planetext;
//DeadCode CSB 27Jul00 		
//DeadCode CSB 27Jul00 	if(classtype->planetext > PT_GER_NONFLY)
//DeadCode CSB 27Jul00 	{
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 		Range *= 4;													//CSB 14Jul00	//CSB 14Jul00
//DeadCode CSB 27Jul00 		actype = PT_GER_NONFLY;
//DeadCode CSB 27Jul00 	}
//DeadCode CSB 27Jul00 	if(movecode == AUTOSAG_TRACKEXPCOMBAT)
//DeadCode CSB 27Jul00 		Range /= 2;													//CSB 14Jul00
//DeadCode CSB 27Jul00 
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 	if (Range < Persons3::SagExpansionCounter::highdemandrange)
//DeadCode CSB 27Jul00 	if(Range < Persons3::sagexpcounts[actype].currenttriggerrange)		//CSB 27Jul00
//DeadCode CSB 27Jul00 	{
//DeadCode CSB 27Jul00 		if (Persons3::SagExpansionCounter::totalexpanded > 200)
//DeadCode CSB 27Jul00 		{	//in range, but too many expanded
//DeadCode CSB 27Jul00 			Persons3::sagexpcounts[actype].currenttriggerrange *= 0.95;												//CSB 27Jul00
//DeadCode CSB 27Jul00 			if(Persons3::sagexpcounts[actype].currenttriggerrange < Persons3::sagexpcounts[actype].mintriggerrange)	//CSB 27Jul00
//DeadCode CSB 27Jul00 				Persons3::sagexpcounts[actype].currenttriggerrange = Persons3::sagexpcounts[actype].mintriggerrange;	//CSB 27Jul00
//DeadCode CSB 27Jul00 		}
//DeadCode CSB 27Jul00 	}
//DeadCode CSB 27Jul00 	else
//DeadCode CSB 27Jul00 		if(Range > VISIBLERANGE)
//DeadCode CSB 27Jul00 			ContractSag(true);
//DeadCode CSB 27Jul00 		else
//DeadCode CSB 27Jul00 		{
//DeadCode CSB 27Jul00 			if(Persons3::SagExpansionCounter::totalexpanded < 150)
//DeadCode CSB 27Jul00 			{
//DeadCode CSB 27Jul00 				Persons3::sagexpcounts[actype].currenttriggerrange *= 1.05;	//CSB 27Jul00
//DeadCode CSB 27Jul00 				if(Persons3::sagexpcounts[actype].currenttriggerrange > Persons3::sagexpcounts[actype].maxtriggerrange)	//CSB 27Jul00
//DeadCode CSB 27Jul00 					Persons3::sagexpcounts[actype].currenttriggerrange = Persons3::sagexpcounts[actype].maxtriggerrange;	//CSB 27Jul00
//DeadCode CSB 27Jul00 			}
//DeadCode CSB 27Jul00 			else
//DeadCode CSB 27Jul00 			{
//DeadCode CSB 27Jul00 				bool inform = true;
//DeadCode CSB 27Jul00 				for(AirStrucPtr l = fly.expandedsag; l; l = l->fly.nextflight)
//DeadCode CSB 27Jul00 					for(AirStrucPtr w = l; w; w = w->Follower())
//DeadCode CSB 27Jul00 						if(!w->information || w == Persons2::PlayerGhostAC)
//DeadCode CSB 27Jul00 							inform = false;
//DeadCode CSB 27Jul00 				if(inform)
//DeadCode CSB 27Jul00 					ContractSag(false);	
//DeadCode CSB 27Jul00 			}
//DeadCode CSB 27Jul00 		}
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 		if(		(Persons3::SagExpansionCounter::totalexpanded < 150)
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 			&&	(Range < VISIBLERANGE)	)	//CSB 14Jul00
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 		{
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 			Persons3::sagexpcounts[actype].currenttriggerrange *= 1.05;	//CSB 27Jul00
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 			if(Persons3::sagexpcounts[actype].currenttriggerrange > Persons3::sagexpcounts[actype].maxtriggerrange)	//CSB 27Jul00
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 				Persons3::sagexpcounts[actype].currenttriggerrange = Persons3::sagexpcounts[actype].maxtriggerrange;	//CSB 27Jul00
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 		}
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 		else
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 		{
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 			if(Range < VISIBLERANGE)
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 			{
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 				bool	inform=true;
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 				for (AirStrucPtr l=fly.expandedsag;l;l=l->fly.nextflight)
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 					for (AirStrucPtr w=l;w;w=w->Follower())
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 						if (!w->information || w==Persons2::PlayerGhostAC)
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 							inform=false;
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 				if (inform)
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 					ContractSag(false);	
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 			}
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 			else
//DeadCode CSB 27Jul00 //DeadCode CSB 27Jul00 		}
//DeadCode CSB 3Aug00 
//DeadCode CSB 3Aug00 	assert((movecode&-2)!=AUTOSAG_TRACKEXPFOLLOW || fly.expandedsag);
//DeadCode CSB 3Aug00 }


void	SAGairgrp::SAGDecisionTrackExpanded(int p,int s)
{	//Never happens
}


//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementTrackExpandedCombat
// Date:		03/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementTrackExpandedCombat()
{
	SAGMovementTrackExpanded();
}


void	SAGairgrp::SAGMovementTrackExpandedCombat(int p,int s)
{	//Never happens
}


void	SAGAirstruc::SAGDecisionTrackExpandedCombat()
{	
	SAGDecisionTrackExpanded();
}


void	SAGairgrp::SAGDecisionTrackExpandedCombat(int p,int s)
{	//Never happens
}
//////////////////////////////////////////////////////////////////////
//
// Function:    SAGMovementDestroyed
// Date:		03/12/99
// Author:		JIM
//
//Description: 	All members dead. Now what?
//
//////////////////////////////////////////////////////////////////////
void	SAGAirstruc::SAGMovementDestroyed()
{

}
void	SAGairgrp::SAGMovementDestroyed(int p,int s)
{
}
void	SAGAirstruc::SAGDecisionDestroyed()
{
}
void	SAGairgrp::SAGDecisionDestroyed(int p,int s)
{
}


//////////////////////////////////////////////////////////////////////
//
// Function:    DestroySag
// Date:		04/08/00
// Author:		Craig Beeston
//
// Description:	
//
//////////////////////////////////////////////////////////////////////
void AirStruc::DestroySag()
{
//DeadCode CSB 7Aug00 	DoAllSAGChecks();
	
	if((fly.expandedsag) && (!fly.expandedsag->Status.deadtime))
		INT3;

	int num = Art_Int.CountSquadronSize(this);
	if(num > 1)
		INT3;

	SAGDeathSequenceOverride(AUTOSAG_DESTROYED);

	animptr	adptr = Anim;												//RJS 21Sep00
	GroupItterator gi(shape,Anim);
	while(gi)
	{
		Squad_Diary.SetAC(this,adptr);				//RJS 21Sep00

		gi.AnimDataMAD().IsInvisible = 1;
		gi.AnimDataMAD().itemstate = DEAD;

		adptr += SHAPE.GetElementAnimOffset(ShapeNum(gi.GetGroupElt()->shapenum));

		gi++;

		Squad_Diary.UpdateACDamage();					//RJS 21Sep00
	}

//DeadCode CSB 4Aug00 	SetUnfriendly(NULL);
	DoAllSAGChecks();
}

//////////////////////////////////////////////////////////////////////
//
// Function:    SAGDeathSequenceOverride
// Date:		15/08/00
// Author:		Craig Beeston
//
// Description:	
//
//////////////////////////////////////////////////////////////////////
Bool AirStruc::SAGDeathSequenceOverride(AutoMoveCodeTypeSelect newmovecode)
{
	SAGBreakForm();

	movecode = newmovecode;
	Status.deadtime = 1;

	return(TRUE);
}


//////////////////////////////////////////////////////////////////////
//
// Function:    RecycleAC
// Date:		10/08/00
// Author:		Craig Beeston
//
// Description:	Set movecode to AUTO_NOPPILOT and make airstruc available
//
//////////////////////////////////////////////////////////////////////
void AirStruc::RecycleAC()
{
	if(fly.numinsag)
		INT3;

	if(movecode == AUTO_SPAREAC)
		return;
	
	if(		(leader) || (follower) || (ai.unfriendly) || (ai.attacker)
		||	(fly.leadflight) || (fly.nextflight) || (fly.expandedsag)	)
		BreakForm();
	
	if(currworld->vp->trackeditem2 == this)
		currworld->vp->trackeditem2 = NULL;

	PlaneTypeSelect actype = classtype->planetext;						//CSB 10Aug00
	if(actype > PT_GER_NONFLY)											//CSB 10Aug00
		actype = PT_GER_NONFLY;											//CSB 10Aug00
	Persons3::sagexpcounts[actype].numactive--;							//CSB 10Aug00
	Persons3::SagExpansionCounter::totalexpanded--;						//CSB 10Aug00
	movecode = AUTO_SPAREAC;											//CSB 10Aug00
																		//CSB 10Aug00
	MinAnimData* animdata = (MinAnimData*)Anim;							//CSB 10Aug00
	animdata->IsInvisible = 1;											//CSB 10Aug00
	animdata->itemstate = DEAD;											//CSB 10Aug00
																		//CSB 10Aug00
	SHAPE.DetatchAllVapourStreams(this);

	currworld->RemoveFromWorld(this);									//CSB 10Aug00
	World.X = 0;														//CSB 10Aug00
	World.Y = 0;														//CSB 10Aug00
	World.Z = 0;														//CSB 10Aug00
	currworld->AddToWorld(this);										//CSB 10Aug00
	uniqueID.changed = FALSE;											//CSB 10Aug00
																		//CSB 10Aug00
#ifdef _OLDWORLD														//CSB 10Aug00
	OldWorld = World;													//CSB 10Aug00
	OldSector = currworld->GetSector(this);								//CSB 10Aug00
#endif																	//CSB 10Aug00
	DoAllSAGChecks();													//CSB 10Aug00

	_Miles.StopItemSamples(this);									//RJS 10Oct00

	if (this->fly.pModel)												//RJS 10Oct00
		this->fly.pModel->CrashTime = 0;								//RJS 10Oct00
}


//////////////////////////////////////////////////////////////////////
//
// Function:    PatchGroupAndAnim
// Date:		17/07/00
// Author:		Craig Beeston
//
// Description:	Decides whether the positions in a Contracted sag should be recalculated
//
//////////////////////////////////////////////////////////////////////
bool SAGAirstruc::PatchAppropriate()
{
	if(Distance3DSquared(&Persons2::PlayerGhostAC->World) > FP(VISIBLERANGE) * FP(VISIBLERANGE) * 3.0)
		return(false);
		
	bool retval = false;

	switch(movecode)
	{
		case AUTOSAG_WAITTAKEOFF:
		case AUTOSAG_REFUELLING:
		case AUTOSAG_TRACKEXPFOLLOW:
		case AUTOSAG_TRACKEXPCOMBAT:
		case AUTOSAG_DESTROYED:
		case AUTOSAG_LAST:
			if((timeofday & 2047) == 0)
				retval = true;
			break;
			
		case AUTOSAG_TAKEOFF:
		case AUTOSAG_FOLLOWWP:
		case AUTOSAG_FOLLOWWPHOME:
		case AUTOSAG_LANDING:
		case AUTOSAG_PRECOMBAT:	
		case AUTOSAG_COMBAT:	
		case AUTOSAG_COMBATCIRCLES:
		case AUTOSAG_POSTCOMBAT:
		case AUTOSAG_BOMBAPPROACH:
		case AUTOSAG_BOMB:
		case AUTOSAG_DEATHGLIDE:
			if(SWord(roll) == 0)
			{
				if(Distance3DSquared(&Persons2::PlayerGhostAC->World) < FP(VISIBLERANGE) * FP(VISIBLERANGE) * (1.0 / 4.0))
				{
					if((timeofday & 127) == 0)
						retval = true;
				}
				else
					if((timeofday & 1023) == 0)
						retval = true;
				break;
			}
			else
				if(Distance3DSquared(&Persons2::PlayerGhostAC->World) < FP(VISIBLERANGE) * FP(VISIBLERANGE) * (1.0 / 4.0))
					retval = true;
				else
					if((timeofday & 31) == 0)
						retval = true;
	}
	return(retval);
}


//////////////////////////////////////////////////////////////////////
//
// Function:    PatchGroupAndAnim
// Date:		23/02/00
// Author:		JIM
//
//Description: 	The group anim contains 1 more element than there are real aircraft.
//				This first element owns the bombs, and should always be invisible.
//
//////////////////////////////////////////////////////////////////////
void	AirStruc::PatchGroupAndAnim(ShapeNum newshape,int numactoenable)
{	
//DeadCode CSB 22Aug00 	if (numactoenable)
	{	//initialise anim data
		fly.numinsag=numactoenable;

		GroupItterator(shape).GetGroupElt()->shapenum=newshape;
		SHAPE.SetAnimData(this);
		for (GroupItterator gi(shape,Anim);gi++;)
		{
			gi.GetGroupElt()->shapenum=newshape;
			if (numactoenable-->0)
				gi.AnimDataMAD().IsInvisible=0;
			else
				gi.AnimDataMAD().IsInvisible=1;
		}

	}
	PatchGroupAndAnim();
}

void	AirStruc::PatchGroupAndAnim(FormationTypeIndex formation)
{
	SingleFormation	
		wingmanpos=Aircraft_Formations[(formation&FORMTYPE_WING)>>FORMTYPE_WING_SH],
		leaderpos=Squadron_Formations[(formation&(FORMTYPE_WING+FORMTYPE_SQUAD))>>FORMTYPE_WING_SH];
	PatchGroupAndAnim(wingmanpos,leaderpos);
}
void	AirStruc::PatchGroupAndAnim(SingleFormation wingmanpos,SingleFormation leaderpos)
{
	//now to arrange the members:

//DeadCode JIM 7Jul00 	int perfl=wingmanpos->numentries;
	int totalac=fly.numinsag;
	int perfl=wingmanpos->GetPerFl(totalac);
	PatchGroupAndAnim(wingmanpos,leaderpos,perfl);
}

void	AirStruc::PatchGroupAndAnim(SingleFormation wingmanpos,SingleFormation leaderpos,int perfl)
{
//Do the check uid stuff here
	ShapeDescPtr sdptr = SHAPESTUFF.GetShapePtr(shape);
	UniqueID shapeuid = UniqueID(sdptr->InteractiveOffset);
	if((shapeuid) && (shapeuid != uniqueID.count) && (shapeuid >= SagBAND) && (shapeuid < SagBANDEND))
	{
		AirStrucPtr setter = AirStrucPtr(Persons2::ConvertPtrUID(shapeuid));
		if(		(!setter)	
			||	(setter->shape != shape)
			||	(setter->fly.expandedsag)
			||	((setter->movecode != AUTO_FOLLOWWP) && (movecode == AUTO_FOLLOWWP))
			)
			sdptr->InteractiveOffset = uniqueID.count;
		else
			return;
	}
	else
		sdptr->InteractiveOffset = uniqueID.count;

//DeadCode CSB 7Nov00 	if((fly.leadflight) && (fly.leadflight->shape == shape) && (fly.leadflight->fly.expandedsag == NULL))
//DeadCode CSB 7Nov00 		return;	//we share the leader's sag so there is no point us recalculating position.
//DeadCode CSB 7Nov00 	
//DeadCode CSB 7Nov00 	if((fly.leadflight) && (fly.leadflight->shape == shape))
//DeadCode CSB 7Nov00 		for(int i = 0; i < Art_Int.ACARRAYSIZE; i++)
//DeadCode CSB 7Nov00 		{
//DeadCode CSB 7Nov00 			AirStrucPtr ac = Art_Int.ACArray[i];
//DeadCode CSB 7Nov00 			if(ac == this)
//DeadCode CSB 7Nov00 				break;
//DeadCode CSB 7Nov00 
//DeadCode CSB 7Nov00 			if(ac)
//DeadCode CSB 7Nov00 				if(ac->shape == shape)
//DeadCode CSB 7Nov00 					if(ac->fly.leadflight == fly.leadflight)
//DeadCode CSB 7Nov00 						if(ac->fly.expandedsag == NULL)
//DeadCode CSB 7Nov00 							return;
//DeadCode CSB 7Nov00 		}

	int totalac=fly.numinsag;
	COORDS3D boxsize={0,0,0};int highestrange=0;
	//now to arrange the members:

//DeadCode JIM 7Jul00 	if (perfl>=10)
//DeadCode JIM 7Jul00 	{
//DeadCode JIM 7Jul00 		UWord fl2=perfl;
//DeadCode JIM 7Jul00 		while (fl2>0)													//CSB 14/03/00
//DeadCode JIM 7Jul00 		{
//DeadCode JIM 7Jul00 			perfl=fl2%10;
//DeadCode JIM 7Jul00 			breakif (totalac%perfl==0);
//DeadCode JIM 7Jul00 			fl2/=10;
//DeadCode JIM 7Jul00 		}
//DeadCode JIM 7Jul00 	}
	int wingnum=0,flightnum=0;
	ANGLES h;
	Float sh,ch;
	GroupItterator gi(shape,Anim);
	gi.AnimDataMAD().IsInvisible=1;										//DAW 31/05/00
	int eltsize=SHAPESTUFF.GetShapePtr(gi.shape)->Size;
	gi++;
	while (totalac--)
	{
		Coords3D	totaloffset={0,0,0};
		int	totalrange=0;
//DeadCode CSB 7Nov00 		if (!gi.AnimDataMAD().IsInvisible)
			if (wingnum)
			{
				totalrange=wingmanpos->wingpos[wingnum-1].range;
				h=hdg+wingmanpos->wingpos[wingnum-1].bearing;
				Math_Lib.high_sin_cos(h,sh,ch);
				totaloffset.X+=totalrange*sh;
				totaloffset.Z+=totalrange*ch;
				totaloffset.Y+=wingmanpos->wingpos[wingnum-1].delta_alt;
			}
			if (flightnum)
			{
				int range2=leaderpos->wingpos[flightnum-1].range;
				totalrange+=range2;
				h=hdg+leaderpos->wingpos[flightnum-1].bearing;
				Math_Lib.high_sin_cos(h,sh,ch);
				totaloffset.X+=range2*sh;
				totaloffset.Z+=range2*ch;
				totaloffset.Y+=leaderpos->wingpos[flightnum-1].delta_alt;
			}
		//store offset
		DOGROUP_PTR	grpelt=gi.GetGroupElt();
		grpelt->xoffset=totaloffset.X;
		grpelt->yoffset=totaloffset.Y;
		grpelt->zoffset=totaloffset.Z;

		if (totaloffset.X>boxsize.X)									//DAW 02/06/00
			boxsize.X=totaloffset.X;
		elseif (-totaloffset.X>boxsize.X)
			boxsize.X=-totaloffset.X;
		if (totaloffset.Y>boxsize.Y)
			boxsize.Y=totaloffset.Y;
		elseif (-totaloffset.Y>boxsize.Y)
			boxsize.Y=-totaloffset.Y;
		if (totaloffset.Z>boxsize.Z)
			boxsize.Z=totaloffset.Z;
		elseif (-totaloffset.Z>boxsize.Z)
			boxsize.Z=-totaloffset.Z;
		if (totalrange>highestrange)
			highestrange+=totalrange;

		gi++;
		wingnum+=1;
		if (wingnum==perfl)
		{
			wingnum=0;
			flightnum++;
		}

	}
//DeadCode CSB 7Nov00 	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(shape);
	sdptr->sx=(boxsize.X>>4)+eltsize;
	sdptr->sy=(boxsize.Y>>4)+eltsize;
	sdptr->sz=(boxsize.Z>>4)+eltsize;
	sdptr->Size=((highestrange+boxsize.Y)>>4)+eltsize;


}
//////////////////////////////////////////////////////////////////////
//
// Function:    ContractSag
// Date:		14/02/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	AirStruc::ContractSag(bool forcedcontract)
{	//for each aircraft I need to vape (if one has been made):
	//the leadflight/nextflight link 
	//the unfriendly/attacker link
	
	//I DON'T KNOW WHAT THIS CODE WILL DO IF ASKED TO CONTRACT ELEMENT ORGANISED FLIGHTS

// sag expansion/contraction now based on distance from ghostAC not on
// whether a sag is being viewed or not

//DeadCode AMM 7Sep00 	if (_Replay.Record && !forcedcontract)
//DeadCode AMM 7Sep00 	{
//DeadCode AMM 7Sep00 		if (!sentcontracted)
//DeadCode AMM 7Sep00 		{
//DeadCode AMM 7Sep00 			_DPlay.SendContractSAGMessage(this->uniqueID.count);
//DeadCode AMM 7Sep00 			sentcontracted=TRUE;
//DeadCode AMM 7Sep00 		}
//DeadCode AMM 7Sep00 		return;
//DeadCode AMM 7Sep00 	}

	DoSAGChecks();
	DoAllSAGChecks();													//CSB 1Aug00
#ifndef NDEBUG
	int sagsize = Art_Int.CountSquadronSize(this);
#endif

//CHECK ALL MEMBER POINTERS AGAINST ACLIST
	//UNFRIENDLY,	ATTACKER,	NEXTFLIGHT, LEADFLIGHT
	
//DeadCode CSB 10Aug00 	while(fly.expandedsag->movecode == AUTO_NOPPILOT)					//CSB 1Aug00
//DeadCode CSB 10Aug00 		fly.expandedsag->BreakForm();									//CSB 1Aug00

	MobileItemPtr thissag = MobileItemPtr(this);
	for(AirStrucPtr thislead = fly.expandedsag; thislead; thislead = thislead->fly.nextflight)
		for(AirStrucPtr thisfoll = thislead; thisfoll; thisfoll = thisfoll->Follower())
			for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
				if((ArtInt::ACArray[i]) && (ArtInt::ACArray[i] != this))
				{
					AirStrucPtr sag = ArtInt::ACArray[i]; 
					MobileItemPtr acmob = MobileItemPtr(thisfoll);
					if(sag->ai.unfriendly  == acmob)	INT3;//sag->ai.unfriendly = thissag;
					if(sag->ai.attacker    == thisfoll)	INT3;//sag->ai.attacker   = this;
					if(sag->fly.leadflight == thisfoll)	sag->fly.leadflight= this;
					if(sag->fly.nextflight == thisfoll)	sag->fly.nextflight= this;
					
					for(AirStrucPtr lac = sag->fly.expandedsag; lac; lac = lac->fly.nextflight)
						for(AirStrucPtr fac = lac; fac; fac = fac->Follower())
						{
							if(fac->ai.unfriendly  == acmob)	fac->ai.unfriendly = thissag;
							if(fac->ai.attacker    == thisfoll)
							{
								fac->ai.attacker   = NULL;
								if((ai.unfriendly == sag) && (!sag->ai.attacker))
									sag->ai.attacker = this;
							}
							if(fac->fly.leadflight == thisfoll)	fac->fly.leadflight= this;
							if(fac->fly.nextflight == thisfoll)	fac->fly.nextflight= this;
						}
				}

	sentcontracted=FALSE;

//DeadCode CSB 16Aug00 	int	grouplpos=fly.originalformpos&InFormMAX, groupwpos=999;
	SingleFormation	wingmanpos=Aircraft_Formations[(formation&FORMTYPE_WING)>>FORMTYPE_WING_SH];
	int totalac=fly.numinsag;
	int perfl=wingmanpos->GetPerFl(totalac);						//JIM 7Jul00
	PlaneTypeSelect actype=classtype->planetext;
	if (actype>PT_GER_NONFLY)
		actype=PT_GER_NONFLY;
	ClassPtr	classtype=this->classtype;
	Persons3::SagExpansionCounter* secp=&Persons3::sagexpcounts[actype];
//DeadCode JIM 7Jul00 	if (perfl>=10)
//DeadCode JIM 7Jul00 	{
//DeadCode JIM 7Jul00 		UWord fl2=perfl;
//DeadCode JIM 7Jul00 		while (fl2>=0)
//DeadCode JIM 7Jul00 		{
//DeadCode JIM 7Jul00 			perfl=fl2%10;
//DeadCode JIM 7Jul00 			breakif (totalac%perfl==0);
//DeadCode JIM 7Jul00 			fl2/=10;
//DeadCode JIM 7Jul00 		}
//DeadCode JIM 7Jul00 	}

	//copy info from leader to SAG:
	AutoMoveCodeTypeSelect separatemovecode;

	switch (fly.expandedsag->movecode)
	{
		case	AUTO_WAIT4TIME	:		separatemovecode=AUTOSAG_WAITTAKEOFF;	break;	//CSB 27Jul00
		case	AUTO_TAKEOFF	:		separatemovecode=AUTOSAG_TAKEOFF;	break;
		case	AUTO_FOLLOWWP	:		separatemovecode=AUTOSAG_FOLLOWWP;	break;
		//case	AUTO_FOLLOWWP	:	separatemovecode=AUTOSAG_FOLLOWWPHOME;	break;
		case	AUTO_LANDING	:		separatemovecode=AUTOSAG_LANDING;	break;
		case	AUTO_PRECOMBAT	:		separatemovecode=AUTOSAG_PRECOMBAT;	break;
		case	AUTO_COMBAT	:			separatemovecode=AUTOSAG_COMBAT;	break;
//DEADCODE JIM 14/02/00 		case		AUTOSAG_COMBATCIRCLES:	separatemovecode=AUTO_COMBAT;	break;
//DEADCODE JIM 14/02/00 		case		AUTOSAG_POSTCOMBAT:		separatemovecode=AUTO_COMBAT;	break;
		case	AUTO_BOMB	:	separatemovecode=AUTOSAG_BOMBAPPROACH;	break;
//DEADCODE JIM 14/02/00 		case		AUTOSAG_BOMB:			separatemovecode=AUTO_BOMB;	break;
		case	AUTO_DEATHGLIDE	:	separatemovecode = AUTOSAG_DEATHGLIDE;	break;
		default:
		case		AUTOSAG_TRACKEXPFOLLOW:	
		case		AUTOSAG_TRACKEXPCOMBAT:	
		case		AUTOSAG_DESTROYED:		
		case		AUTOSAG_LAST:			INT3;	break;
	}
	movecode=separatemovecode;
	if((movecode == AUTOSAG_PRECOMBAT) || (movecode == AUTOSAG_COMBAT))
		if(!ai.unfriendly)
			movecode = AUTOSAG_FOLLOWWP;

	ai.manoeuvre <<= fly.expandedsag->ai.manoeuvre;							//CSB 20Jul00
	ai.ManStep   <<= fly.expandedsag->ai.ManStep;								//CSB 20Jul00
	manoeuvretime = fly.expandedsag->manoeuvretime;						//CSB 24Jul00
	information = fly.expandedsag->information;							//CSB 21Aug00
	Status = fly.expandedsag->Status;
	//COPY FUEL from leader to SAG

	for(SWord i = 0; i < 4; i++)
		fly.fuel_content[i] = fly.expandedsag->fly.fuel_content[i];


	//Copy details from followers
	GroupItterator gi(shape,Anim);
	gi++;  //skip elt 0.

	int flnum = 0;														//CSB 16Aug00
	int acnum = 0;														//CSB 16Aug00

	for (AirStrucPtr l=fly.expandedsag,l2;l;l=l2)
	{
//DeadCode CSB 16Aug00 		while (grouplpos<(l->fly.originalformpos&InFormMAX))
//DeadCode CSB 16Aug00 		{
//DeadCode CSB 16Aug00 			while (groupwpos<perfl)
//DeadCode CSB 16Aug00 			{
//DeadCode CSB 16Aug00 				gi++;
//DeadCode CSB 16Aug00 				groupwpos++;
//DeadCode CSB 16Aug00 //DEADCODE JIM 14/02/00 				totalac--;
//DeadCode CSB 16Aug00 			}
//DeadCode CSB 16Aug00 			grouplpos++;
//DeadCode CSB 16Aug00 			groupwpos=0;
//DeadCode CSB 16Aug00 		}
		while(l->formpos != acnum + flnum)								//CSB 16Aug00
		{																//CSB 16Aug00
			gi++;														//CSB 16Aug00
			acnum += 0x10;												//CSB 16Aug00
			if(acnum >= perfl * 0x10)									//CSB 16Aug00
			{															//CSB 16Aug00
				flnum += 0x01;											//CSB 16Aug00
				acnum = 0;												//CSB 16Aug00
			}															//CSB 16Aug00
		}																//CSB 16Aug00

		l2=l->fly.nextflight;
		for (AirStrucPtr w=l,w2;w;w=w2)
		{
			while(w->formpos != acnum + flnum)							//CSB 16Aug00
			{															//CSB 16Aug00
				gi++;													//CSB 16Aug00
				acnum += 0x10;											//CSB 16Aug00
				if(acnum >= perfl * 0x10)								//CSB 16Aug00
				{														//CSB 16Aug00
					flnum += 0x01;										//CSB 16Aug00
					acnum = 0;											//CSB 16Aug00
				}														//CSB 16Aug00
			}															//CSB 16Aug00
			
			w2=w->Follower();
//DEADCODE JIM 14/02/00 			totalac--;
			//COPY anim data to gi
			gi.AnimDataMAD().IsInvisible = 0;
			SHAPE.ACtoSAG(w, gi.GetAnimData());

			//make aircraft generically reusable and remove
			secp->numactive--;

			SHAPE.DetatchAllVapourStreams(w);

			w->currworld->RemoveFromWorld(w);							//CSB 9Aug00
			Persons3::Reset3dAC(w,classtype->planetext);
			w->currworld->AddToWorld(w);								//CSB 9Aug00

			Persons3::SagExpansionCounter::totalexpanded--;
			
#ifdef _OLDWORLD															//CSB 7Aug00
			w->OldWorld = w->World;											//CSB 7Aug00
			w->OldSector = w->currworld->GetSector(w);						//CSB 8Aug00
#endif																		//CSB 7Aug00
			MinAnimData* animdata = (MinAnimData*)w->Anim;				//CSB 9Aug00
			animdata->IsInvisible = 1;									//CSB 9Aug00
			animdata->itemstate = DEAD;									//CSB 9Aug00

			if(currworld->vp->trackeditem2 == w)
				currworld->vp->trackeditem2 = this;

			//Anim Data Too;
			gi++;
			acnum += 0x10;												//CSB 16Aug00
			if(acnum >= perfl * 0x10)									//CSB 16Aug00
			{															//CSB 16Aug00
				flnum += 0x01;											//CSB 16Aug00
				acnum = 0;												//CSB 16Aug00
			}															//CSB 16Aug00
		}
	}
	Persons3::sagexpcounts[actype].SAGsexpanded--;
//DEADCODE JIM 14/02/00 	while (totalac)		  //This does nothing. These A/C are already dead!
//DEADCODE JIM 14/02/00 	{
//DEADCODE JIM 14/02/00 		while (groupwpos<perfl)
//DEADCODE JIM 14/02/00 		{
//DEADCODE JIM 14/02/00 			gi++;
//DEADCODE JIM 14/02/00 			groupwpos++;
//DEADCODE JIM 14/02/00 			totalac--;
//DEADCODE JIM 14/02/00 		}
//DEADCODE JIM 14/02/00 		grouplpos++;
//DEADCODE JIM 14/02/00 		groupwpos=0;
//DEADCODE JIM 14/02/00 	}
	fly.expandedsag = NULL;												//CSB 26/05/00
	PatchGroupAndAnim();

#ifndef NDEBUG
	if(sagsize != Art_Int.CountSquadronSize(this))
		INT3;
#endif
	DoSAGChecks();
	DoAllSAGChecks();													//CSB 1Aug00
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ExpandSag
// Date:		14/02/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
AirStrucPtr	AirStruc::ExpandSag(bool forcedexpand)
{

	//I DON'T THINK THIS CODE WILL EVER EXPAND FLIGHTS IN AN ELEMENT ORGANISATION

	DoSAGChecks();
	DoAllSAGChecks();													//CSB 1Aug00
#ifndef NDEBUG
	int sagsize = Art_Int.CountSquadronSize(this);
#endif

// sag expansion/contraction now based on distance from ghost AC not whether
// sag is being viewed or not

//DeadCode AMM 7Sep00 	if (_Replay.Record && !forcedexpand)
//DeadCode AMM 7Sep00 	{
//DeadCode AMM 7Sep00 		if (!sentexpanded)
//DeadCode AMM 7Sep00 		{
//DeadCode AMM 7Sep00 			_DPlay.SendExpandSAGMessage(this->uniqueID.count);
//DeadCode AMM 7Sep00 			sentexpanded=TRUE;
//DeadCode AMM 7Sep00 		}
//DeadCode AMM 7Sep00 
//DeadCode AMM 7Sep00 		return NULL;
//DeadCode AMM 7Sep00 	}

//DeadCode CSB 1Aug00 	for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
//DeadCode CSB 1Aug00 		if((ArtInt::ACArray[i]) && (AirStrucPtr(ArtInt::ACArray[i]) != this))
//DeadCode CSB 1Aug00 			for(AirStrucPtr lac = AirStrucPtr(ArtInt::ACArray[i])->fly.expandedsag; lac; lac = lac->fly.nextflight)
//DeadCode CSB 1Aug00 				for(AirStrucPtr fac = lac; fac; fac = fac->Follower())
//DeadCode CSB 1Aug00 					if(fac->ai.attacker == this)	fac->ai.attacker = NULL;

	sentexpanded=FALSE;
	PlaneTypeSelect actype=MergeTypes(classtype->planetext);			//JIM 25Jul00
	if (Persons3::sagexpcounts[actype].numavailable-Persons3::sagexpcounts[actype].numactive>=fly.numinsag)
	{
		Persons3::sagexpcounts[actype].SAGsexpanded++;
		int wingnum=0, flightnum=0,
			groupnum=fly.originalformpos&InFormMAX;
//DeadCode JIM 20Oct00 		int	numused=0;
		SingleFormation	
			wingmanpos=Aircraft_Formations[(formation&FORMTYPE_WING)>>FORMTYPE_WING_SH];
		int totalac=fly.numinsag;
		int perfl=wingmanpos->GetPerFl(totalac);					//JIM 7Jul00
//DeadCode JIM 7Jul00 		if (perfl>=10)
//DeadCode JIM 7Jul00 		{
//DeadCode JIM 7Jul00 			UWord fl2=perfl;
//DeadCode JIM 7Jul00 			while (fl2>=0)
//DeadCode JIM 7Jul00 			{
//DeadCode JIM 7Jul00 				perfl=fl2%10;
//DeadCode JIM 7Jul00 				breakif (totalac%perfl==0);
//DeadCode JIM 7Jul00 				fl2/=10;
//DeadCode JIM 7Jul00 			}
//DeadCode JIM 7Jul00 		}
		int	lettering=ai.Lettering();
		if (fly.leadflight)
		{
			AirStrucPtr grplead=fly.leadflight;
			if (grplead->fly.numinsag==0)
				grplead=grplead->fly.expandedsag;
			
//DEADCODE DAW 13/03/00 			if (grplead->classtype==classtype)
//DEADCODE DAW 13/03/00 			{
//DEADCODE DAW 13/03/00 
//DEADCODE DAW 13/03/00 				callnumbase=(grplead->fly.numinsag+perfl-1)/perfl;	//callsigns per squadron
//DEADCODE DAW 13/03/00 				if ((formation&FORMTYPE_INTER)==FTI_ABREST && callnumbase==2)
//DEADCODE DAW 13/03/00 					callnumbase=callnumbase
//DEADCODE DAW 13/03/00 								*(1+2*((formation&FORMTYPE_INTERCHILD)>>FORMTYPE_INTERCHILD_SH));
//DEADCODE DAW 13/03/00 			}
		}

		AutoMoveCodeTypeSelect separatemovecode=AUTO_FOLLOWWP;
		switch (movecode)
		{
			case	AUTOSAG_WAITTAKEOFF:	separatemovecode=AUTO_WAIT4TIME;	break;	
			case	AUTOSAG_TAKEOFF:		separatemovecode=AUTO_TAKEOFF;	break;
			case	AUTOSAG_FOLLOWWP:		separatemovecode=AUTO_FOLLOWWP;	break;
			case	AUTOSAG_FOLLOWWPHOME:	separatemovecode=AUTO_FOLLOWWP;	break;
			case	AUTOSAG_LANDING:		separatemovecode=AUTO_LANDING;	break;
			case	AUTOSAG_REFUELLING:		separatemovecode=AUTO_LANDING;	break;
			case	AUTOSAG_PRECOMBAT:		separatemovecode=AUTO_PRECOMBAT;	break;
			case	AUTOSAG_COMBAT:			separatemovecode=AUTO_COMBAT;	break;
			case	AUTOSAG_COMBATCIRCLES:	separatemovecode=AUTO_COMBAT;	break;
			case	AUTOSAG_POSTCOMBAT:		separatemovecode=AUTO_COMBAT;	break;
			case	AUTOSAG_BOMBAPPROACH:	separatemovecode=AUTO_BOMB;	break;
			case	AUTOSAG_BOMB:			separatemovecode=AUTO_BOMB;	break;
			case	AUTOSAG_DEATHGLIDE:		separatemovecode = AUTO_DEATHGLIDE;	break;
			case	AUTOSAG_TRACKEXPFOLLOW:	
			case	AUTOSAG_TRACKEXPCOMBAT:	
			case	AUTOSAG_DESTROYED:		
			case	AUTOSAG_LAST:			INT3;	break;
		}
		
		switch (movecode)
		{
			case	AUTOSAG_WAITTAKEOFF:		
			case	AUTOSAG_TAKEOFF:		
			case	AUTOSAG_FOLLOWWP:		
			case	AUTOSAG_FOLLOWWPHOME:	
			case	AUTOSAG_LANDING:		movecode=AUTOSAG_TRACKEXPFOLLOW;	break;
			case	AUTOSAG_REFUELLING:		movecode=AUTOSAG_TRACKEXPFOLLOW;	break;
			case	AUTOSAG_PRECOMBAT:		
			case	AUTOSAG_COMBAT:			
			case	AUTOSAG_COMBATCIRCLES:	
			case	AUTOSAG_POSTCOMBAT:		movecode=AUTOSAG_TRACKEXPCOMBAT;	break;
			case	AUTOSAG_BOMBAPPROACH:	
			case	AUTOSAG_BOMB:			movecode=AUTOSAG_TRACKEXPFOLLOW;	break;
			case	AUTOSAG_DEATHGLIDE:		movecode=AUTOSAG_TRACKEXPFOLLOW;	break;
			case	AUTOSAG_TRACKEXPFOLLOW:	
			case	AUTOSAG_TRACKEXPCOMBAT:	
			case	AUTOSAG_DESTROYED:		
			case	AUTOSAG_LAST:			INT3;	break;
		}


		GroupItterator gi(shape,Anim);
		gi++;  //skip elt 0.
		AirStrucPtr	escortee=fly.leadflight,grpleader=NULL,flightleader=NULL,last=NULL;
		while (totalac--)
		{
			if (!gi.AnimDataMAD().IsInvisible)
			{
				gi.AnimDataMAD().IsInvisible=true;
				AirStrucPtr p=ActivateACFromSag(gi);
				assert(p,"oops! not got an aircraft to expand to!");
				Persons3::sagexpcounts[actype].numactive++;
				p->fly.originalformpos=(InWing)wingnum+(InForm)groupnum;
				p->formpos=(InWing)wingnum+(InForm)flightnum;
				p->follower=NULL;p->fly.nextflight=NULL;
				if (!grpleader)
				{
//DEADCODE CSB 02/06/00 					p->fly.expandedsag=this;
					fly.expandedsag=p;
					p->leader=NULL;p->fly.leadflight=escortee;
					flightleader=grpleader=p;
					p->formpos=FormationIndexMIN;
				}
				else
				if (!flightleader)
				{
					p->leader=NULL;p->fly.leadflight=grpleader;
					last->fly.nextflight=p;
					flightleader=p;
					p->formpos=*(InForm)flightnum;		//TAKE JIM'S				//CSB 26Jul00
//DeadCode MS 09Oct00 					p->World=*p->PositionWRTLeader();	//TAKE JIM'S				//CSB 26Jul00
				}
				else
				{
					p->leader=flightleader;p->fly.leadflight=grpleader;
					last->follower=p;
				}
				p->World=World;
				p->World+=gi.delta;
				if(p->fly.pModel)
				{	p->fly.pModel->Pos.x = p->World.X;	p->fly.pModel->Pos.y = p->World.Y;	p->fly.pModel->Pos.z = p->World.Z;	}
				p->ai.submethod<<=ai.submethod;

				p->Status = Status;										//CSB 8Aug00
				p->fly.expandedsag=this;								//CSB 02/06/00
				p->fly.callname=fly.callname;	  
				p->fly.callnum=(groupnum)*5+wingnum;
				p->SetLettering(lettering+0x10000*(flightnum*perfl+wingnum));
				p->ai.pilotnum<<=ai.pilotnum;
				p->movecode=separatemovecode;
				p->ai.diaryptr = ai.diaryptr;							//CSB 31/05/00
				p->ai.homebase = ai.homebase;
				p->ai.manoeuvre <<= ai.manoeuvre;							//CSB 20Jul00
				p->ai.ManStep  <<= ai.ManStep;							//CSB 20Jul00
				p->manoeuvretime = manoeuvretime;						//CSB 24Jul00
				p->ai.unfriendly = NULL;
//DeadCode CSB 22Aug00 				if(!p->formpos)											//CSB 21Aug00
//DeadCode CSB 22Aug00 					p->information = information;						//CSB 21Aug00
//DeadCode CSB 22Aug00 				else													//CSB 21Aug00
//DeadCode CSB 22Aug00 					p->information = IF_IN_POS;							//CSB 21Aug00
				p->information = IF_OUT_POS;

				if((ai.unfriendly) && (ai.unfriendly->Status.size == AIRSTRUCSIZE))
				{
					AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
					if((unf->fly.numinsag) && (unf->fly.expandedsag))
					{
						bool stoploop = false;
						for(AirStrucPtr l = unf->fly.expandedsag; (l) && (!stoploop); l = l->fly.nextflight)
							for(AirStrucPtr f = l; (f) && (!stoploop); f = f->Follower())
								if((!f->ai.attacker) && (!f->Status.deadtime))
								{
									p->ai.unfriendly = f;
									f->ai.attacker = p;
									stoploop = true;
								}
						if(!stoploop)
							p->ai.unfriendly = unf->fly.expandedsag;
					}
					else
						p->ai.unfriendly = ai.unfriendly;
				}

				AircraftAnimData* adptr = (AircraftAnimData*)(p->Anim);
				if(		(p->movecode == AUTO_WAIT4TIME)
					||	((p->movecode == AUTO_TAKEOFF) && (p->ai.ManStep < 5))
					||	((p->movecode == AUTO_LANDING) && (p->ai.ManStep > 1))	)
				{
					p->fly.pModel->GearDown(p);
					if(p->movecode == AUTO_LANDING)
						adptr->acflaps = 255;
					else
						adptr->acflaps = 0;

					if(p->vel_ < p->classtype->landingspeed)
					{
//DeadCode CSB 23Oct00 						p->fly.pModel->GroundHeight = _Collide.GroundAltitude(p->World);
						p->fly.pModel->GroundHeight = p->ai.homebase->World.Y;
						p->World.Y = p->fly.pModel->GroundHeight + p->classtype->deckshunt;
						p->pitch = p->classtype->deckangle;
					}
				}
				else
				{
					adptr->acleglowerl = 255;
					adptr->acleglowerr = 255;
					adptr->acflaps	   = 0;
				}
				SHAPE.BombBayDoors(p, ANIM_BOMBDOORS_CLOSE, true);

//DEADCODE JIM 12/12/99 				p->World=*p->PositionWRTLeader();
				currworld->AddToWorld(p);
#ifdef _OLDWORLD															//CSB 7Aug00
				p->OldWorld = p->World;										//CSB 7Aug00
				p->OldSector = currworld->GetSector(p);							//CSB 8Aug00
#endif																		//CSB 7Aug00
				last=p;
			}
			else
				NOP;
			gi++;
			wingnum+=1;
			if (wingnum==perfl)
			{
				if (flightleader)
				{
					last=flightleader;
					flightleader=NULL;
				}
				else
				{
					last = grpleader;
					while(last->fly.nextflight)							//CSB 15Aug00
						last = last->fly.nextflight;					//CSB 15Aug00
				}
				wingnum=0;
				flightnum++;
				groupnum++;
			}
		}

		for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
			if((ArtInt::ACArray[i]) && (ArtInt::ACArray[i] != this))
				for(AirStrucPtr lac = ArtInt::ACArray[i]->fly.expandedsag; lac; lac = lac->fly.nextflight)
					for(AirStrucPtr fac = lac; fac; fac = fac->Follower())
						if(fac->ai.unfriendly == this)
						{
							bool stoploop = false;
							for(AirStrucPtr l = fly.expandedsag; (l) && (!stoploop); l = l->fly.nextflight)
								for(AirStrucPtr f = l; (f) && (!stoploop); f = f->Follower())
									if((!f->Status.deadtime) && (!f->ai.attacker))
									{
										fac->ai.unfriendly = f;
										f->ai.attacker = fac;
										stoploop = true;
									}
							if(!stoploop)
								fac->ai.unfriendly = fly.expandedsag;
						}

		Status.deadtime = 0;	

#ifndef NDEBUG
		int newsize = Art_Int.CountSquadronSize(this);
		if(newsize != sagsize)
			INT3;
#endif
		DoSAGChecks();
		DoAllSAGChecks();													//CSB 1Aug00

		return grpleader;
	}

#ifndef NDEBUG
	if(sagsize != Art_Int.CountSquadronSize(this))
		INT3;
#endif
	DoSAGChecks();
	DoAllSAGChecks();													//CSB 1Aug00

	return NULL;
}

AirStrucPtr AirStruc::ActivateACFromSag(GroupItterator& gi)
{
	//first, I have to find one...

	AirStrucPtr currac=NULL;

	PlaneTypeSelect actype=classtype->planetext;
	if (actype>PT_GER_NONFLY)
		actype=PT_GER_NONFLY;
	ClassPtr	classtype=this->classtype;
	Persons3::SagExpansionCounter* secp=&Persons3::sagexpcounts[actype];
	//4 chances to find a spare aircraft:
	//	1)	basenum+numactive .. basenum+numavailable
	//	2)	basenum .. basenum+numactive
	//	3)	SagBAND .. basenum
	//	4)	basenum+numactive .. SagBANDEND
	if (actype<PT_GER_NONFLY)
	{
		if (currac==NULL)
			for (int d=secp->numavailable-secp->numactive,i=secp->basenum+secp->numactive;d--;i++)
			{
				AirStrucPtr p=Persons2::ConvertPtrUID(UniqueID(i));
				if (p && p->movecode==AUTO_SPAREAC && p->classtype==classtype)
				{	currac=p;break;	}
			}
		if (currac==NULL)
			for (int d=secp->numactive,i=secp->basenum;d--;i++)
			{
				AirStrucPtr p=Persons2::ConvertPtrUID(UniqueID(i));
				if (p && p->movecode==AUTO_SPAREAC && p->classtype==classtype)
				{	currac=p;break;	}
			}
		if (currac==NULL)
			for (int d=secp->basenum-SagBAND,i=SagBAND;d--;i++)
			{
				AirStrucPtr p=Persons2::ConvertPtrUID(UniqueID(i));
				if (p && p->movecode==AUTO_SPAREAC && p->classtype==classtype)
				{	currac=p;break;	}
			}
		if (currac==NULL)
			for (int d=SagBANDEND-(secp->basenum+secp->numavailable),i=secp->basenum+secp->numavailable;d--;i++)
			{
				AirStrucPtr p=Persons2::ConvertPtrUID(UniqueID(i));
				if (p && p->movecode==AUTO_SPAREAC && p->classtype==classtype)
				{	currac=p;break;	}
			}
	}
	else
	{
		if (currac==NULL)
			for (int d=secp->numavailable-secp->numactive,i=secp->basenum+secp->numactive;d--;i++)
			{
				AirStrucPtr p=Persons2::ConvertPtrUID(UniqueID(i));
				if (p && p->movecode==AUTO_SPAREAC && p->classtype->planetext>=PT_GER_NONFLY)
				{	currac=p;break;	}
			}
		if (currac==NULL)
			for (int d=secp->numactive,i=secp->basenum;d--;i++)
			{
				AirStrucPtr p=Persons2::ConvertPtrUID(UniqueID(i));
				if (p && p->movecode==AUTO_SPAREAC && p->classtype->planetext>=PT_GER_NONFLY)
				{	currac=p;break;	}
			}
		if (currac==NULL)
			for (int d=secp->basenum-SagBAND,i=SagBAND;d--;i++)
			{
				AirStrucPtr p=Persons2::ConvertPtrUID(UniqueID(i));
				if (p && p->movecode==AUTO_SPAREAC && p->classtype->planetext>=PT_GER_NONFLY)
				{	currac=p;break;	}
			}
		if (currac==NULL)
			for (int d=SagBANDEND-(secp->basenum+secp->numavailable),i=secp->basenum+secp->numavailable;d--;i++)
			{
				AirStrucPtr p=Persons2::ConvertPtrUID(UniqueID(i));
				if (p && p->movecode==AUTO_SPAREAC && p->classtype->planetext>=PT_GER_NONFLY)
				{	currac=p;break;	}
			}
	}

#ifndef NDEBUG																				//CSB 10Aug00
	if((currac->uniqueID.count < RealAcBAND) || (currac->uniqueID.count >= RealAcBANDEND))	//CSB 10Aug00
		INT3;																				//CSB 10Aug00
#endif																						//CSB 10Aug00

	//GOT AN AIRCRAFT  //ok...	let's fill the thing in:
	if (currac)
	{
		currworld->RemoveFromWorld(currac);							//CSB 9Aug00
		Persons3::SagExpansionCounter::totalexpanded++;
		currac->classtype=classtype;
		currac->shape=currac->classtype->visible;
		//NEED TO FIX FLIGHT MODEL if german bomber

		currac->follower=
			currac->fly.nextflight=NULL;
		currac->leader=
			currac->fly.leadflight=NULL;
		currac->formpos=FormationIndexMIN;
		currac->ai.unfriendly=NULL;
		for(int n = 0; n < 4; n++)
			currac->ai.spottedunfriendly[n] = NULL;
		currac->ai.attacker=NULL;
		currac->ai.homebase=NULL;
		currac->duty<<=duty;
		currac->fly.numinsag=0;
		currac->fly.expandedsag=NULL;
		for(SWord i = 0; i < 4; i++)
			currac->fly.fuel_content[i] = fly.fuel_content[i];

		currac->sentexpanded=FALSE;
		currac->sentcontracted=FALSE;
		currac->nationality=(Nationality)nationality;
		currac->waypoint=waypoint;
		currac->information = IF_ALLBAD;		
		currac->vel_=vel_;
		currac->vel_x =vel_x;					
		currac->vel_y =vel_y;					
		currac->vel_z =vel_z;
	//DEADCODE JIM 10/12/99 	currac->fly.vel_cms = 	fly.vel_cms;
		currac->fly.cpitch = fly.cpitch;		
		currac->fly.aileron = fly.aileron;						
		currac->fly.elevator = fly.elevator;					
		currac->fly.rudder = fly.rudder;						
		currac->weap.ShootDelay=0;
		currac->fly.callname=fly.callname;	  
		currac->fly.callnum=fly.callnum;
		currac->ai.pilotnum<<=ai.pilotnum;
		currac->roll=roll;
		currac->hdg=hdg;
		currac->pitch=pitch;
  		currac->fly.rpm = fly.rpm;									//JIM 21Oct96
		currac->fly.thrustpercent = fly.thrustpercent;							//JIM 21Oct96
		currac->ai.manoeuvre=MANOEUVRE_SELECT;
		currac->manoeuvretime=0;									//JIM 11Sep96
		currac->ai.ManStep=PHASE0;								//JIM 11Sep96
		currac->slowdownleader=FALSE;
//DEADCODE CSB 05/01/00 		currac->information=IF_ALLBAD;
		currac->formation=formation;
		currac->CommsOwner=UID_NULL;							//AMM 27Nov98
		currac->ai.morale=ai.morale;
		currac->ai.radiosilent<<=ai.radiosilent;
		currac->ai.elementtactics = ai.elementtactics;
		currac->ai.squadrontactics = ai.squadrontactics;
		currac->ai.flighttactics = ai.flighttactics;
		currac->ai.combatskill=ai.combatskill;
		currac->ai.eventlog=ai.eventlog;
		currac->World.X=World.X;
		currac->World.Y=World.Y;
		currac->World.Z=World.Z;

		//NEED TO TRANSFER THE ANIM DATA FROM gi parameter
// .... should use real weappack num here, instead of 0!
		SHAPE.ResetAnimData_NewShape(currac,currac->shape,0,false);		//RJS 29Aug00
		SHAPE.SAGtoAC(gi.GetAnimData(), currac->Anim);

//DeadCode RJS 29Aug00 		MinAnimData* animdata = (MinAnimData*)currac->Anim;				//CSB 9Aug00
//DeadCode RJS 29Aug00 		animdata->IsInvisible = 0;										//CSB 9Aug00
//DeadCode RJS 29Aug00 		animdata->itemstate = ALIVE;									//CSB 9Aug00

		if (Three_Dee.livelist)
			if((*Three_Dee.livelist).sleeplist -= currac)
				*Three_Dee.livelist += currac;
	}
	return currac;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    FakeDamage
// Date:		02/06/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
int SAGairgrp::FakeDamage(UniqueID target,int numattacks,PlaneTypeSelect attackertype,UniqueID reportsuccess)
{	//	ac					0	1	2	3	4	5	6	7	8	9	10	11	12
	//root(ac*4)->att		0	2	2	3	4	4   4   5   5   6			6
	//root(ac*5)->att		0	2	3	3	4	5   5   5   6   6			7
	numattacks=MathLib::SquareRoot(5*numattacks*(attackertype+1)*(attackertype+1)/(PT_JU87*PT_JU87));
//DeadCode JIM 24Sep00 		if (attackertype>=PT_LW_BOMBERS)
//DeadCode JIM 28Sep00 			numattacks=numattacks*((attackertype+1)/PT_JU87);	//ju87=8
//DeadCode JIM 24Sep00 		else
//DeadCode JIM 24Sep00 			numattacks=0;
	TargetGroupPtr tg;
	if ((tg=Node_Data[target])!=NULL)	//numattacks && 				//JIM 24Sep00
	{
		tg->SetDamage(tg->truestatus+numattacks,false,reportsuccess);
		return tg->PlayerStatus();
	}
	return 50;
}

//Refuelling rules:
//
//If the fuel store is destroyed, then the RAF are grounded to the end of the day,
//so are vulnerable indefinitely.
//Otherwise the first squadron will park for 15 mins after landing to refuel.
//If another squadron lands while the first is refuelling then their refuelling 
//may be delayed while the first squad is finished, if:
//		The airfield is satelite and number refuelling is greater than 1-1xdamagepc
//Or	The airfield is large and number refuelling is greater than 3-3xdamagepc
//There will be a bowser/mechanic animation sequence which will be triggered

// Cost/benefit of repair teams on satellite airfields
//
//Repair will be split into 3 levels:
//	Very light damage can be repaired on satellite airfields if repair facility is live
//	Light damage can be repaired at main airfield if that's repair facility is live.
//		The aircraft will remain a member of the satellite airfield, and will take 
//		longer to repair than if it was on the main airfield.
//	Heavy damage will lose the aircraft, but depending on the exact level 
//	(can we do this?), we would up aircraft production fractionally to account 
//	for the extra spare parts availability.
//All repairs will be faster if 2 squads of same a/c type at same airfield and only 1 is damaged.
	
int	SAGairgrp::GetRefuellingTime(SquadNum sq)
{
	if (sq>SQ_LW_START)
		return	15*SECSPERMIN;
	UniqueID myhome=Node_Data[sq].homeairfield;
	TargetFighterField* tff=Node_Data[myhome];
	int	numlanding=1;
	for (BritSquadron*	bsp=Node_Data.squadron;bsp->squadron;bsp++)
		if (	bsp->squadron!=sq
			&&	bsp->homeairfield==myhome
			&&	bsp->totestatus==Profile::PS_REFUELLING
			)
			numlanding++;
	int	maxsquads=tff->maxsquads-1;	//we can't refuel them all simultaniously
	if (maxsquads)
		maxsquads=maxsquads-maxsquads*tff->subdamagelevels[tff->SDL_FUEL]/100;
	//ok..	maxsquads is the max that can be refuelled quickly.
	//		numlanding is the number of squads trying to refuel
	if (maxsquads)
		if (maxsquads>=numlanding)
			return	15*SECSPERMIN;
		else
			return ((numlanding/maxsquads+1)*15*SECSPERMIN);
	else
		return	60*SECSPERMIN;	//no bowsers available!

}


void	Profile::ApplyDiaryLosses()
{
	if (squadlist[0].diaryentry!=0xffffffff)
		for (int s=0,max=squadlist,delta;s<max;s+=delta)
		{
	//DeadCode JIM 20Oct00 		int	s2=s+1;
			delta=1;
			while (s+delta<max && squadlist[s].squadnum==squadlist[s+delta].squadnum)
				delta++;
			squadlist[s].ApplyDiaryLosses(delta);
		}
	else
		assert(packagestatus==PS_COMPLETE && squadlist[0].instance==UID_NULL);

}

//Diary:		//max 40
//	UByte		numlosses;	// filled in when ac in this squadron is killed
//	UByte		numacdamaged;	// filled in when ac in this squadron is damaged
//	UByte		numpilotslost;	// if killed ac, not ejected
//	LeadKilled	leaderkilled;	// if killed is leader, LK_1ST (formpos==0) or LK_OTHER (formpos!=0)
//	UByte		noaclaunched;
//
//Squad:		//max 15
//				ULong	numacoriginal:4,			//Unchanged from launch
//						numacleft:4,				//Left+ditched=original
//						numacditched:4,
//						numacrecoveredlow:4,		//recoveredlow<left - only if ditched 
//						numacrecoveredmed:4,		//recoveredmed+recoveredbad+pilotsleft<ditched
//						numacrecoveredbad:4,		
//						numpilotslost:4,
//						leaderlost:1,
//						other:3;
//

void	Profile::Squad::ApplyDiaryLosses(int moreslots)
{	//Apply on return from 3d
	SquadronBase*	squaddiary=Squad_Diary.GetDiaryPtr(diaryentry);
	int	sdlosses=squaddiary->numlosses;
	int	sdpilotlosses=squaddiary->numpilotslost;
	if (Squadron().AcType()>=PT_GER_NONFLY)
		sdpilotlosses*=0.2;
	else
	if (Squadron().AcType()>=PT_ME110)
		sdpilotlosses*=0.5;
	int	sddamage=squaddiary->numacdamaged;
	for (int sl=0;sl<moreslots;sl++)
	{
		sdpilotlosses-=this[sl].numpilotslost;
		sddamage-=this[sl].numacrecoveredlow+this[sl].numacrecoveredmed+this[sl].numacrecoveredbad;
		sdlosses-=this[sl].numacditched-(this[sl].numacrecoveredmed+this[sl].numacrecoveredbad);
	}
	if (squaddiary->leaderkilled==LK_1ST)
		this[0].leaderlost=1;
	int	stopcounter=15;
	while (sdlosses>0)
	{
		int	slot=Math_Lib.rnd(moreslots);
		if (this[slot].numacleft)
		{
			this[slot].numacleft--;
			this[slot].numacditched++;
			if (sdpilotlosses>0)
				if (Math_Lib.rnd(sdlosses)<sdpilotlosses)
				{
					this[slot].numpilotslost++;
					sdpilotlosses--;
				}
			sdlosses--;
			stopcounter=15;
		}
		else
			if (this[slot].numacrecoveredbad>0)
			{
				this[slot].numacrecoveredbad--;
				sdlosses--;
				sddamage++;
				stopcounter=15;

			}
			else
				if (this[slot].numacrecoveredmed>0)
				{
					this[slot].numacrecoveredmed--;
					sdlosses--;
					sddamage++;
					stopcounter=15;
				}
		if (stopcounter--==0)
		{
			INT3;
			break;
		}
	}
	stopcounter=15;
	while (sdpilotlosses>0)		  //this can happen because a squadron is wiped out.
	{
		int	slot=Math_Lib.rnd(moreslots);
		if (this[slot].numacditched-(this[slot].numacrecoveredbad+this[slot].numacrecoveredmed)>0)
		{
			this[slot].numpilotslost++;
			sdpilotlosses--;
			stopcounter=15;
		}
		if (stopcounter--==0)
		{
			INT3;
			break;
		}
	}

	while (sddamage>0)
	{
		int	slot=Math_Lib.rnd(moreslots);
		if (this[slot].numacleft-this[slot].numacrecoveredlow>0)
		{
			if (Math_Lib.rnd(this[slot].numacleft)>this[slot].numacditched)
			{
				this[slot].numacleft--;
				this[slot].numacditched++;
				if (Math_Lib.rnd()>0xC000)
					this[slot].numacrecoveredbad++;
				else
					this[slot].numacrecoveredmed++;
			}
			else
				this[slot].numacrecoveredlow++;
			sddamage--;
			stopcounter=15;
		}
		if (stopcounter--==0)
		{
			INT3;
			break;
		}
	}
}

//Squad:		//max 15
//				ULong	numacoriginal:4,			//Unchanged from launch
//						numacleft:4,				//Left+ditched=original
//						numacditched:4,
//						numacrecoveredlow:4,		//recoveredlow<left - only if ditched 
//						numacrecoveredmed:4,		//recoveredmed+recoveredbad+pilotsleft<ditched
//						numacrecoveredbad:4,		
//						numpilotslost:4,
//						leaderlost:1,
//						other:3;
//
//Squadron:		//max 40
//	UByte	pilotsavail;											  //JIM 07/01/00
//	UByte	acavail;												  //JIM 07/01/00
//	UByte	acquickrepairable;										  //JIM 07/01/00
//	UByte	acslowrepairable;
//	UWord	pilotlosses;
void	Profile::ApplyFlyingLossesDiary()
{
	for (int s=0,max=squadlist;s<max;s++)
		if (squadlist[s].diaryentry != 0xffffffff)
		{
			int diaryentry=squadlist[s].diaryentry;
			::Squadron& squadron=squadlist[s].Squadron();

			SquadronBase*	squaddiary=Squad_Diary.GetDiaryPtr(diaryentry);
			if (squaddiary->squadnum >= SQ_LW_START)							//RJS 13Nov00
			{
				Diary::Gruppen*	gptr = (Diary::Gruppen*)squaddiary;
				
				MMC.thisweekreview.Note(squadron.AcType(),PT_SPIT_A,gptr->kills[0]);
				MMC.thisweekreview.Note(squadron.AcType(),PT_HURR_A,gptr->kills[1]);
			}
			else
			{
				Diary::Squadron*	sptr = (Diary::Squadron*)squaddiary;

				MMC.thisweekreview.Note(squadron.AcType(),PT_ME109,sptr->kills[0]);
				MMC.thisweekreview.Note(squadron.AcType(),PT_ME110,sptr->kills[1]);
				MMC.thisweekreview.Note(squadron.AcType(),PT_JU87,sptr->kills[2]);
				MMC.thisweekreview.Note(squadron.AcType(),PT_DO17,sptr->kills[3]);
				MMC.thisweekreview.Note(squadron.AcType(),PT_JU88,sptr->kills[4]);
				MMC.thisweekreview.Note(squadron.AcType(),PT_HE111,sptr->kills[5]);
			}
			if (squaddiary->squadnum<SQ_LW_START)
			{
				Diary::Intercept*	squadintercept=Squad_Diary.GetIntercept(squaddiary);
				Diary::RaidGroup* raidgroup=Squad_Diary.GetRaidGroup(squadintercept);
				if (Squad_Diary.GetFirstSquadron(raidgroup))	   //If undiverted patrol then not set
					squadron.periodstatus=squadron.GOT_ACTION;	  
			}
			else
			{
				Diary::RaidGroup* raidgroup=Squad_Diary.GetRaidGroup(squaddiary);
				if (Squad_Diary.GetFirstIntercept(raidgroup))
					squadron.periodstatus=squadron.GOT_ACTION;	  
			}
			int kills=0,losses=0,pilotlosses=0;
			Diary::Squadron* squaddiarydetail=(Diary::Squadron*)squaddiary;
			losses=squaddiary->numlosses;
			squadron.ModifyMoraleAcCombat(squadron.GOT_LOSSES,losses);
			int acleft=(squaddiary->noaclaunched-losses);
			if (acleft)
			{
				if (squaddiary->squadnum<SQ_LW_START)
					kills=	squaddiarydetail->kills[0]
						+	squaddiarydetail->kills[1]
						+	squaddiarydetail->kills[2]
						+	squaddiarydetail->kills[3]
						+	squaddiarydetail->kills[4]
						+	squaddiarydetail->kills[5];
				else
					kills=	squaddiarydetail->kills[0]
						+	squaddiarydetail->kills[1]
						+	squaddiarydetail->kills[2];
				if (kills>acleft)
					kills=acleft;
   				squadron.ModifyMoraleAcCombat(squadron.OTHER_GOTKILL,kills);
			}
			if (squaddiary->leaderkilled==LK_1ST)
				squadron.ModifyMoraleAcCombat(squadron.LEAD_KILLED);
			else
				if (Math_Lib.rnd(30)<kills)
					squadron.ModifyMoraleAcCombat(squadron.LEAD_GOTKILL);


			for (int s2=s;s2<max;s2++)
				if (diaryentry==squadlist[s2].diaryentry)
					squadlist[s2].diaryentry=0;
		}
}

void	Profile::Squad::ApplyFlyingLosses(int acbitslaunched)
{

// this is the killer... here we sort out the claims..
	::Squadron& squadron=Squadron();


	MMC.thisweekreview.Note(squadron.AcType(),PeriodReview::DESTROY,numacditched-numacrecoveredmed);
	MMC.thisweekreview.Note(squadron.AcType(),PeriodReview::DAMAGE,numacrecoveredlow+numacrecoveredmed);
	squadron.acavail-=numacditched+numacrecoveredlow;					//JIM 6Sep00
	squadron.acquickrepairable+=numacrecoveredlow;
	squadron.acslowrepairable+=numacrecoveredmed;
	if (squadron.squadron<SQ_LW_START)
		if (squadron.AcType()==PT_SPIT_A || squadron.AcType()==PT_SPIT_B)
			Node_Data.production[PT_SPIT_A].scrappedaircraft+=numacrecoveredbad;
		else
			Node_Data.production[PT_HURR_A].scrappedaircraft+=numacrecoveredbad;
	if (squadron.pilotsavail>=numpilotslost)							//MS 17Nov00
		squadron.pilotsavail-=numpilotslost;							//MS 17Nov00
	else																//MS 17Nov00
		squadron.pilotsavail=0;											//MS 17Nov00
	squadron.pilotlosses+=numpilotslost;
	if (squadnum>SQ_LW_START)
	{
		Gruppen* gr=squadron;
		if (gr->AcType()<PT_JU87)
		{
			if (numacditched>4 || numacrecoveredlow+numacrecoveredmed>8)
				gr->periodsuntilready-=1;
		}
		else
		{
			if (numacditched>2 || numacrecoveredlow+numacrecoveredmed>3)
				gr->periodsuntilready-=1;
		}
	}
	else
	{
		BritSquadron* sq=squadron;
		sq->usedacbits&=~acbitslaunched;
	}

	//
	// Use the diary to decide whether we have been incombat:
	//
//DeadCode RJS 12Nov00 	SquadronBase*	squaddiary=Squad_Diary.GetDiaryPtr(diaryentry);
//DeadCode JIM 1Nov00 	if (leaderlost)
//DeadCode JIM 1Nov00 		squadron.periodstatus=squadron.LEAD_KILLED;
}


//////////////////////////////////////////////////////////////////////
//
// Function:    SAGCountSquadronSize
// Date:		Mon 20 Mar 2000
// Author:		Craig Beeston
//
// Description: Count the number of visible elements in an unexpanded SAG
//
//////////////////////////////////////////////////////////////////////
int AirStruc::SAGCountSquadronSize()
{
	GroupItterator gi(shape,Anim);
	gi++;
	int numac = 0;
	while(gi)
	{
		if(!gi.AnimDataMAD().IsInvisible)
			numac++;
		gi++;
	}
	return(numac);
}


//////////////////////////////////////////////////////////////////////
//
// Function:    DoSAGChecks
// Date:		Fri 26 May 2000
// Author:		Craig Beeston
//
// Description: For Debugging - Hopefully trap some silly errors
//
//////////////////////////////////////////////////////////////////////
void AirStruc::DoSAGChecks()
{
#ifndef _NDEBUG
	if(fly.numinsag)	//A SAG not an aircraft
	{
		if(fly.expandedsag)	//It is expanded
		{
			switch(movecode)	//Check Appropriate movecode
			{
				case AUTOSAG_TRACKEXPFOLLOW:
				case AUTOSAG_TRACKEXPCOMBAT:
					break;
				default:
					INT3;
			}

			GroupItterator gi(shape,Anim);	//Check elements are turned off
			gi++;  //skip elt 0.
			int totalac = fly.numinsag;
			while (totalac--)
			{
				if(!gi.AnimDataMAD().IsInvisible)
					INT3;
				gi++;
			}
		}
		else
		{					//Not expanded
			switch(movecode)
			{
				case AUTOSAG_TRACKEXPFOLLOW:
				case AUTOSAG_TRACKEXPCOMBAT:
//DeadCode CSB 28Jul00 				case AUTOSAG_DESTROYED:
				case AUTO_DEATHSEQUENCE:
				case AUTO_SPIRAL2GROUND:
				case AUTOSAG_LAST:
					INT3;
			}

			GroupItterator gi(shape,Anim);	//Check elements are turned on
			gi++;  //skip elt 0.
			int totalac = fly.numinsag;
			int elementson = 0;
			while (totalac--)
			{
				if(!gi.AnimDataMAD().IsInvisible)
					elementson++;
				gi++;
			}
			if((movecode != AUTOSAG_DESTROYED) && (!elementson))
				INT3;
			if((movecode == AUTOSAG_DESTROYED) && (elementson))
				INT3;
		}
	}
#endif	
}


//////////////////////////////////////////////////////////////////////
//
// Function:    DoAllSAGChecks
// Date:		Tue 1 Aug 2000
// Author:		Craig Beeston
//
// Description: For Debugging - Hopefully trap some silly errors
//
//////////////////////////////////////////////////////////////////////
void AirStruc::DoAllSAGChecks()
{
#ifndef _NDEBUG

//#define _DOALLSAGCHECKS
#ifdef _DOALLSAGCHECKS

	DoSAGChecks();

	for(AirStrucPtr sag = AirStrucPtr(SAGList); sag; sag = AirStrucPtr(sag->nextmobile))
	{
		AirStrucPtr Leader     = sag->Leader();
		AirStrucPtr Follower   = sag->Follower();
		AirStrucPtr LeadFlight = sag->fly.leadflight;
		AirStrucPtr NextFlight = sag->fly.nextflight;
		AirStrucPtr Unfriendly = NULL;
		if((sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size == AIRSTRUCSIZE))
			Unfriendly = AirStrucPtr(sag->ai.unfriendly);
		AirStrucPtr Attacker   = sag->ai.attacker;
		AirStrucPtr ExpandedSag = sag->fly.expandedsag;
		int NumInSag = sag->fly.numinsag;

		if(		(sag->fly.numinsag) && (!sag->fly.expandedsag) && (sag->Status.deadtime)
			&&	(Art_Int.CountSquadronSize(sag)) && (sag->movecode != AUTOSAG_DEATHGLIDE)	)
			INT3;

		if((sag->fly.numinsag) && (!sag->fly.expandedsag) && (!sag->Status.deadtime) && (!Art_Int.CountSquadronSize(sag)))
			INT3;

		if((sag->Status.deadtime) && (sag->fly.numinsag) && (sag->movecode != AUTOSAG_DESTROYED) && (sag->movecode != AUTOSAG_DEATHGLIDE))
			INT3;

		if(		(sag->Status.deadtime) && (!sag->fly.numinsag) 
			&&	(sag->movecode != AUTO_SPAREAC)
			&&	(sag->movecode != AUTO_NOPPILOT)
			&&	(sag->movecode != AUTO_SPIRAL2GROUND)
			&&	(sag->movecode != AUTO_DEATHSEQUENCE)
			&&	(sag->movecode != AUTO_DEATHGLIDE)
			&&	(sag->movecode != AUTO_HITWATER)
			&&	(sag->movecode != AUTO_CRASHSKID)
			&&	(sag->movecode != AUTO_CRASHROLL)
			&&	(sag->movecode != AUTO_CRASHONEWHEEL)
			&&	(sag->movecode != AUTO_CRASHNOSE)
			&&	(sag->movecode != AUTO_CRASHFLIP)
			&&	(sag->movecode != AUTO_CRASHTUMBLE)		)	
			INT3;

		if(		(sag->fly.numinsag) && (!sag->ai.unfriendly)
			&&	((sag->movecode == AUTO_COMBAT))	)// || (sag->movecode == AUTOSAG_TRACKEXPCOMBAT))	)
			INT3;

		if((sag->ai.attacker) && (sag->ai.attacker->ai.unfriendly != sag))
			INT3;
		
		if(		(sag->fly.numinsag) && (sag->fly.expandedsag)
			&&	((sag->movecode != AUTOSAG_TRACKEXPFOLLOW) && (sag->movecode != AUTOSAG_TRACKEXPCOMBAT))	)
			INT3;

		if(		((!sag->fly.numinsag) || (!sag->fly.expandedsag))
			&&	((sag->movecode == AUTOSAG_TRACKEXPFOLLOW) || (sag->movecode == AUTOSAG_TRACKEXPCOMBAT))	)
			INT3;

		if((!sag->fly.numinsag) && (sag->ai.attacker) && (sag->ai.attacker->fly.numinsag))
			INT3;

		if((sag->fly.numinsag) && (sag->fly.expandedsag) && (sag->ai.attacker) && (!sag->ai.attacker->fly.numinsag))
			INT3;

		if(		(!sag->fly.numinsag)
			&&	(sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			&&	(AirStrucPtr(sag->ai.unfriendly)->fly.numinsag) && (AirStrucPtr(sag->ai.unfriendly)->fly.expandedsag)	)
			INT3;

		if(		(sag->fly.numinsag) && (sag->classtype->aerobaticfactor != AEROBATIC_LOW)
			&&	(sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			&&	(!AirStrucPtr(sag->ai.unfriendly)->fly.numinsag)	)
			INT3;

		if(		(!sag->fly.numinsag) && (sag->fly.expandedsag) && (!sag->Status.deadtime)
			&&	(sag->FindFormpos0() != sag->fly.expandedsag->fly.expandedsag)	)
			INT3;


		if(		(!sag->fly.expandedsag) && (sag->Status.deadtime)
			&&	(	(sag->leader) || (sag->follower) || (sag->fly.leadflight) || (sag->fly.nextflight)
				||	(sag->ai.unfriendly) || (sag->ai.attacker)	)	)
			INT3;

		if(		((sag->leader)         && (!sag->Leader()->fly.expandedsag)       && (sag->Leader()->Status.deadtime))
			||	((sag->follower)       && (!sag->Follower()->fly.expandedsag)     && (sag->Follower()->Status.deadtime))
			||	((sag->fly.leadflight) && (!sag->fly.leadflight->fly.expandedsag) && (sag->fly.leadflight->Status.deadtime))
			||	((sag->fly.nextflight) && (!sag->fly.nextflight->fly.expandedsag) && (sag->fly.nextflight->Status.deadtime))	
			||	((sag->ai.attacker)    && (!sag->ai.attacker->fly.expandedsag)    && (sag->ai.attacker->Status.deadtime))	)
			INT3;

		if(		(sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			&&	(!AirStrucPtr(sag->ai.unfriendly)->fly.expandedsag) && (AirStrucPtr(sag->ai.unfriendly)->Status.deadtime)	)
			INT3;

		if((sag->movecode == AUTO_BOMB) && (sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size == AIRSTRUCSIZE))
			INT3;

		if((sag->movecode == AUTO_BOMB) && (sag->nationality == NAT_RAF))
			INT3;

		if((sag->fly.expandedsag) && (sag->movecode == AUTO_NOPPILOT))
			INT3;

		if((sag->ai.attacker) && (sag->ai.attacker->classtype->aerobaticfactor == AEROBATIC_LOW))
			INT3;

		if((sag->classtype->aerobaticfactor == AEROBATIC_LOW) && (sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size == AIRSTRUCSIZE))
			INT3;

		if(		(sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size == AIRSTRUCSIZE) 
			&&	(AirStrucPtr(sag->ai.unfriendly)->nationality == sag->nationality)		)
			INT3;

		if(sag->fly.numinsag)
		{
			GroupItterator gi(sag->shape, sag->Anim);	//Check 1st element not turned on
			if(!gi.AnimDataMAD().IsInvisible)
				INT3;
		}

		if(sag->fly.numinsag)
			SimpleAircraftAnimData* adptr = (SimpleAircraftAnimData*)sag->Anim;
			
		if(!sag->fly.numinsag)
			AircraftAnimData* adptr = (AircraftAnimData*)sag->Anim;
			
		if((!sag->fly.numinsag) && (sag->fly.expandedsag) && (sag != Persons2::PlayerSeenAC))
		{
			bool foundme = false;
			for(AirStrucPtr ld = sag->fly.expandedsag->fly.expandedsag; ld; ld = ld->fly.nextflight)
				for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
					if(ac == sag)
						foundme = true;
			if(!foundme)
				INT3;
		}

		if((sag->movecode == AUTOSAG_DESTROYED) && (sag->SAGCountSquadronSize()))
			INT3;

		if(		(sag != this) && (sag->fly.expandedsag != this)
			&&	(sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			&&	(sag->movecode != AUTO_COMBAT) && (sag->movecode != AUTO_PRECOMBAT)
			&&	(sag->movecode != AUTOSAG_COMBATCIRCLES)
			&&	(sag->movecode != AUTOSAG_TRACKEXPCOMBAT) && (sag->movecode != AUTOSAG_TRACKEXPFOLLOW)	)
			INT3;

		if(		(sag->ai.unfriendly) && (sag->ai.unfriendly->Status.size != AIRSTRUCSIZE)
			&&	(		(sag->movecode != AUTO_BOMB) && (sag->movecode != AUTOSAG_BOMBAPPROACH)
					&&	(!((sag->fly.expandedsag) && (sag->fly.expandedsag->movecode == AUTO_BOMB))))	)
			INT3;

//DeadCode CSB 23Aug00 		if((sag->information == IF_IN_POS) && (sag->movecode != AUTO_FOLLOWWP) && (sag->movecode != AUTOSAG_TRACKEXPFOLLOW))
//DeadCode CSB 23Aug00 		{
//DeadCode CSB 23Aug00 			AirStrucPtr lead = sag->fly.leadflight;
//DeadCode CSB 23Aug00 			if(sag->leader)
//DeadCode CSB 23Aug00 				lead = sag->Leader();
//DeadCode CSB 23Aug00 			if(lead)
//DeadCode CSB 23Aug00 			{
//DeadCode CSB 23Aug00 				FP dist = sag->Distance3D(sag->PositionWRTLeader(lead));
//DeadCode CSB 23Aug00 				if(dist > 1000)
//DeadCode CSB 23Aug00 					INT3;
//DeadCode CSB 23Aug00 			}
//DeadCode CSB 23Aug00 		}

//////////////////////////////////////////////////////////////////////////////////////////////////		
		if((sag->fly.numinsag) && (!sag->nextmobile))
			sag = AirStrucPtr(ACList);
	}

	if((Persons2::PlayerSeenAC) && (Persons2::PlayerSeenAC->fly.expandedsag))
	{
		int totalactive = 0;
		for(int i = PT_BRIT_FLYABLE; i <= PT_GER_NONFLY; i++)
		{
			int numactive = 0;
			for(AirStrucPtr ac = AirStrucPtr(ACList); ac; ac = AirStrucPtr(ac->nextmobile))
				if((ac->movecode != AUTO_SPAREAC) && (ac != Persons2::PlayerGhostAC))
				{
					PlaneTypeSelect actype = ac->classtype->planetext;	
					if(actype > PT_GER_NONFLY)	
						actype = PT_GER_NONFLY;	
					if(actype == i)
						numactive++;	
				}

			if(numactive != Persons3::sagexpcounts[i].numactive)
				INT3;

			totalactive += numactive;
		}
		if(totalactive != Persons3::SagExpansionCounter::totalexpanded)
			INT3;
	}

#endif

#endif	
}


//////////////////////////////////////////////////////////////////////
//
// Function:    ClearUpAI
// Date:		Wed 23 Aug 2000
// Author:		Craig Beeston
//
// Description: Make sure there are no wrong AI links
//
//////////////////////////////////////////////////////////////////////
void AirStruc::ClearUpAI()
{
	for(AirStrucPtr ac = AirStrucPtr(ACList); ac; ac = AirStrucPtr(ac->nextmobile))
	{
		if(		(ac->ai.unfriendly) && (ac->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			&&	(ac->movecode != AUTO_COMBAT) && (ac->movecode != AUTO_PRECOMBAT) && (ac->movecode != AUTOSAG_COMBATCIRCLES) && (ac->movecode != AUTOSAG_TRACKEXPCOMBAT)	)
		{
			if(AirStrucPtr(ac->ai.unfriendly)->ai.attacker == ac)
				AirStrucPtr(ac->ai.unfriendly)->ai.attacker = NULL;
			ac->ai.unfriendly = NULL;
		}

		if(		(ac->ai.unfriendly) && (ac->ai.unfriendly->Status.size != AIRSTRUCSIZE)
			&&	((ac->movecode != AUTO_BOMB) && (!((ac->fly.expandedsag) && (ac->fly.expandedsag->movecode == AUTO_BOMB))))	)
			ac->ai.unfriendly = NULL;
	
//////////////////////////////////////////////////////////////////////////
		if((!ac->fly.numinsag) && (!ac->nextmobile) && (SAGList))
			ac = AirStrucPtr(SAGList);
	}
	DoAllSAGChecks();
}
