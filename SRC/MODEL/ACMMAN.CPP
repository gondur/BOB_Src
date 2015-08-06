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
//Filename       acmman.cpp
//System         
//Author         R. Hyde 
//Date           Fri 1 Mar 1996
//Description    ACM manoeuvres - moved from flymodel
//------------------------------------------------------------------------------

//									SCRIPT_NOTCLEAR
//FlightSep, nose to nose: use Shaw to check
//
//
//: fill in
//check out:
//Bool AirStruc::SubjectClosureGreaterThan(SLong dvel)
//
//
//1		Need to try to decide between wanting max turnrate or min turn radius
//2		Ref1.78: not done nosetonose nosetotail differences
//3		check lead or lag pursuit defense, 1.63
//4		Use Immelmann where appropriate
//5		 Need a chance of individual breaking off and trying to take on opposition without help
//6		Need to check that angles v energy fight is covered:
//			if thrust/wt ratio is higher or got more energy choose energy
//			angles:
//				go for corner vel with dive and zoom to stay there
//			energy:
//				stay at sustained turn and wait for other fighter to loose energy
//				then zoom to get advantage
//7		Using circumvent?

//Summary
//
//
//Throughout manoeuvre choice we should be aware of the best thing to do and
//be able to choose worse manoeuvres for poorer pilots
//
//The manoeuvres are aimed to either get an angles or an energy advantage.
//Most of the time, it is advantageous to use introduce a vertical component
//to the manoeuvre
//
//An important decision is to decide whether to aim for the corner speed or the
//maximum sustained turnrate. The corner speed gives the max instantaneous
//turnrate but at the expense of loss of energy and deterioration of performance.
//Sometimes minimum turn radius is the aim (at or less than corner vel).
//
//
//
//The process is as follows
//
//1		if ac wants to and if it is appropriate
//			attempt to disengage
//
//2		if necessary goto GunDefence()
//			may be a special manoeuvre that is appropriate
//				else BreakTurn which goes for corner vel
//
//3		if appropriate go to special manoeuvre
//		else choose lead,pure,lag pursuit at either sustained turn or corner vel
//				BREAKTURN is corner vel manoeuvre
//				SUSTAINEDTURN is sustained turn manoeuvre with either lead or pure pursuit
//4		AutoShoot()
//			Attempt either a tracking or snapshot
//
//
//morale		determines the aggressivenes of the manoeuvre chosen
//					high morale means a highly aggressive manoeuvre wil be chosen
//combat.combatskill	determines the type of manoeuvre chosen
//flying.combatskill	determines how successful the implementation of the manoeuvre is
//
//
//
//LP Jobs
//1		Muzzle vel as f(aircraft or weapon)
//2		Formations in formatn.cpp, revised figures and introduce variation = f(.combatskill)
//			Formation distance will depend on flyingability: lots of stragglers
//3		Attack bombers: multiple directions/waves
//4		evade by going into cloud
//5		Drag sabre down aaa invested vallley
//
//
//References
//
//1		Shaw
//2		Walker
//
//
//Notes
//1		When attacker field is set, it just means that we have set an attacker to attack ac
//			ac does not necessarily know. Ac knows if he unfriendly field is set
//
//2		Morale is dropped in combat by being hit and pulling g
//3		Some of the conditions to choose need fuzzier logic
//4		<= MORALE_MEDIUM for dive and zoom
//5		Range should be considered a 3d distance
//6		gmeter measures lift in air and 1 on ground
//			radial accel = lift/mass - g.cos pitch
//		so unloaded when lift = 0, gmeter = 0
//7		Task overload 1.236
//8		Flat Scissors should not coded as a manoeuvre
//			it should come as a result of beam to beam turn in
//			this will have to be tuned
//			scissors will be used by the inexperienced just to weave about
//
//Russion tactic: attack ,cover, reserve
//
//
//rollbanditplane	this is the roll to put the bandit on the lift vector plane
//gbanditplane		this is g required to keep a/c in the horizontal plane
//					when rolled to put lift vector on bandit
//
//gsustained		for a particular set of conditions, this is the max g that can
//					be sustained 
//
//rollsustained		roll for gsustained
//
//
//
//
//
//

#define F_GRAFIX												//DAW 05Aug96
#define F_COMMON
#define F_BATTLE
#include <stdio.h>
#include <string.h>

#include	"collided.h"										//PD 06Sep96
#include	"Dosdefs.h"
#include	"Worldinc.h"
#include	"FlyModel.h"
#include	"mymath.h"
#include	"enumbits.m"
#include	"time.h"											//RDH 25Apr96
#include	"ranges.h"
#include	"missman2.h"										//JIM 22Aug96
#include	"movement.h"
#include	"transite.h"
#include	"ai.h"
#include	"miles.h"											//RDH 25Jul96
#include	"landscap.h"										//RDH 18Dec96
#include	"viewsel.h"											//RDH 25Jul96
#include	"3dcom.h"											//RJS 22Aug96
#include	"speed.h"											//RDH 01Oct96
#include	"persons2.h"
#include "monotxt.h"
#include "modvec.h"
#include "model.h"
#include "acmmodel.h"
#include	"replay.h"
#include "overlay.h"

//MATHABLE	(ANGLES)

// ROD don't use STALL_ANGLE
//ANGLES const	STALL_ANGLE = ANGLES_15Deg;

struct RequiredElevatorElement
	{
		ANGLESInst pitch; SWord elevator;
	};




static RequiredElevatorElement 	RequiredElevatorData[] =
			{
				{ANGLES_FifthDeg, 1},
				{ANGLES_HalfDeg, 4},
				{ANGLES_1Deg, 6},
				{ANGLES_2Deg, 8},
				{ANGLES_3Deg, 10},
				{ANGLES_4Deg, 12},
				{ANGLES_5Deg, 14},
				{ANGLES_6Deg, 16},
				{ANGLES_10Deg, 20},
				{ANGLES_22Deg, MAXELEVATOR},
				{ANGLES_180Deg, MAXELEVATOR}
			};



struct RequiredAileronElement
	{
		ANGLESInst roll; SWord aileron;
	};



static RequiredAileronElement 	RequiredAileronData[] =
			{
				{ANGLES_FifthDeg, 2},
				{ANGLES_HalfDeg, 3},
				{ANGLES_1Deg, 4},
				{ANGLES_2Deg, 6},
				{ANGLES_3Deg, 10},
				{ANGLES_4Deg, 12},
				{ANGLES_5Deg, 16},
				{ANGLES_6Deg, 20},
				{ANGLES_10Deg, 24},
				{ANGLES_22Deg, 28},
				{ANGLES_90Deg, 60},
				{ANGLES_180Deg, 60}
			};


//DeadCode RDH 01Nov96 static RequiredBankDataElement 	CombatReqBankData[] =
//DeadCode RDH 01Nov96 			{
//DeadCode RDH 01Nov96 				{ANGLES_FifthDeg, ANGLES_0Deg},
//DeadCode RDH 01Nov96 				{ANGLES_HalfDeg, ANGLES_3Deg},
//DeadCode RDH 01Nov96 				{ANGLES_1Deg, ANGLES_4Deg},
//DeadCode RDH 01Nov96 				{ANGLES_2Deg, ANGLES_5Deg},
//DeadCode RDH 01Nov96 				{ANGLES_3Deg, ANGLES_7Deg},
//DeadCode RDH 01Nov96 				{ANGLES_4Deg, ANGLES_9Deg},
//DeadCode RDH 01Nov96 				{ANGLES_5Deg, ANGLES_11Deg},
//DeadCode RDH 01Nov96 				{ANGLES_6Deg, ANGLES_16Deg},
//DeadCode RDH 01Nov96 				{ANGLES_10Deg, ANGLES_30Deg},
//DeadCode RDH 01Nov96 //DeadCode RDH 17Jul96 				{ANGLES_22Deg, ANGLES_60Deg},
//DeadCode RDH 01Nov96 				{ANGLES_30Deg, MAXCOMBATROLL},
//DeadCode RDH 01Nov96 				{ANGLES_180BareDeg, MAXCOMBATROLL}
//DeadCode RDH 01Nov96 			};
//TempCode RDH 17Jul96 			{
//TempCode RDH 17Jul96 				{ANGLES_FifthDeg, ANGLES_0Deg},
//TempCode RDH 17Jul96 				{ANGLES_HalfDeg, ANGLES_3Deg},
//TempCode RDH 17Jul96 				{ANGLES_1Deg, ANGLES_4Deg},
//TempCode RDH 17Jul96 				{ANGLES_2Deg, ANGLES_5Deg},
//TempCode RDH 17Jul96 				{ANGLES_3Deg, ANGLES_7Deg},
//TempCode RDH 17Jul96 				{ANGLES_4Deg, ANGLES_9Deg},
//TempCode RDH 17Jul96 				{ANGLES_5Deg, ANGLES_11Deg},
//TempCode RDH 17Jul96 				{ANGLES_6Deg, ANGLES_16Deg},
//TempCode RDH 17Jul96 				{ANGLES_10Deg, ANGLES_20Deg},
//TempCode RDH 17Jul96 				{ANGLES_22Deg, ANGLES_45Deg},
//TempCode RDH 17Jul96 				{ANGLES_45Deg, MAXCOMBATROLL},
//TempCode RDH 17Jul96 				{ANGLES_180BareDeg, MAXCOMBATROLL}
//TempCode RDH 17Jul96 			};
//TempCode RDH 17Jul96 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TargetOnSubjectTail
//Author		R. Hyde 
//Date			Thu 14 Dec 1995
//
//Description	target is on subject tail
//
//Inputs		HdgIntercept,PitchIntercept and Range setup
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::TargetOnSubjectTail(ANGLES angle)

{
	AirStrucPtr	unfriendly = *ai. unfriendly;
	
	ANGLES delta = HdgIntercept + ANGLES_180Deg + angle - hdg;
	ANGLES anglerange = angle + angle;

	if ((delta) << (anglerange))
	{
//		ANGLES delta = PitchIntercept + ANGLES_180Deg + angle - pitch;
		delta = - PitchIntercept + angle - pitch;
		if ((delta) << (anglerange))
		{
		 	return (TRUE);
		}else
		{
			return (FALSE);
		}
	}else
	{
		return (FALSE);
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubjectOnTargetTail
//Author		R. Hyde 
//Date			Thu 14 Dec 1995
//
//Description	subject is on target tail
//
//Inputs		HdgIntercept,PitchIntercept and Range setup
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	AirStruc::SubjectOnTargetTail(ANGLES angle)

{
//	AirStrucPtr	unfriendly = *ai.unfriendly;
//
//	ANGLES	temp;
//	
//	temp = HdgIntercept + angle - unfriendly->hdg; 
////DeadCode RDH 30Mar98 	if (temp < (2 * angle))
//	if (temp << (angle + angle))
//	{
//		temp = PitchIntercept + angle - unfriendly->pitch;
//		if (temp << (angle + angle))
//		{
//	 		return (TRUE);
//		}else
//		{
//			return (FALSE);
//		}
//	}else
//	{
//		return (FALSE);
//	}

	AirStrucPtr	unfriendly = *ai.unfriendly;
	SWord temp;
	SWord range = angle;
	
	temp = HdgIntercept  - unfriendly->hdg; 
	if  (		(temp < range)
			&&	(temp > -range)
		)
	{
		temp = PitchIntercept - unfriendly->pitch;
		if  (		(temp < range)
				&&	(temp > -range)
			)
		{
	 		return (TRUE);
		}else
		{
			return (FALSE);
		}
	}else
	{
		return (FALSE);
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NoseToTail
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	when beam to beam, the ac are on a pass
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::NoseToTail (ANGLES angle)
{
	AirStrucPtr	unfriendly = *ai.unfriendly;

	if ((hdg + ANGLES_180Deg + angle - unfriendly->hdg) << (angle + angle))//RDH 19Sep97
	{
	 	return (TRUE);
	}else
	{
		return (FALSE);
	}

}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TargetFacingSubject
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
Bool	AirStruc::TargetFacingSubject(ANGLES angle)
{
	AirStrucPtr	unfriendly = *ai.unfriendly;

//DeadCode RDH 30Mar98 	if ((HdgIntercept + ANGLES_180Deg + angle - unfriendly->hdg) < (2 * angle))
	if ((HdgIntercept + ANGLES_180Deg + angle - unfriendly->hdg) << (angle + angle))//RDH 19Sep97
	{
	 	return (TRUE);
	}else
	{
		return (FALSE);
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubjectFacingTarget
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
Bool	AirStruc::SubjectFacingTarget(ANGLES angle)
{
//DeadCode RDH 30Mar98 	if ((HdgIntercept + angle - hdg) < (2* angle))
	if ((HdgIntercept + angle - hdg) << (angle + angle))	//RDH 19Sep97
	{
	 	return (TRUE);
	}else
	{
		return (FALSE);
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AircraftDamaged
//Author		R. Hyde 
//Date			Tue 20 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	if above critical damage return true
//
//------------------------------------------------------------------------------
Bool	AirStruc::AircraftDamaged()
{
	AirStrucPtr ac = this;
	if(ac == Persons2::PlayerGhostAC)
		ac = Persons2::PlayerSeenAC;

	if(!fly.numinsag)
	{
		AircraftAnimData* acanim = (AircraftAnimData*)(ac->Anim);
//DeadCode DAW 26Oct00 		int damage =  acanim->LEFTWINGOUT + acanim->LEFTWINGIN + acanim->RIGHTWINGOUT + acanim->RIGHTWINGIN
//DeadCode DAW 26Oct00 					+ acanim->ENGINELEFT + acanim->ENGINERIGHT + acanim->TAIL + acanim->FINLEFT + acanim->FINRIGHT
//DeadCode DAW 26Oct00 					+ acanim->FRONT + acanim->LEFTWHEEL + acanim->RIGHTWHEEL + acanim->FUELTANK + acanim->CANOPY + acanim->OTHER;
//DeadCode DAW 26Oct00 		if(damage > 255 * 4)
//DeadCode DAW 26Oct00 			return(TRUE);
		if(		(acanim->LEFTWINGOUT	> 63)
			||	(acanim->LEFTWINGIN		> 63)
			||	(acanim->RIGHTWINGOUT	> 63)
			||	(acanim->RIGHTWINGIN	> 63)
			||	(acanim->ENGINELEFT		> 63)
			||	(acanim->ENGINERIGHT	> 63)
			||	(acanim->TAIL			> 127)
			||	(acanim->FINLEFT		> 127)
			||	(acanim->FINRIGHT		> 127)
			||	(acanim->FRONT			> 127)
			||	(acanim->LEFTWHEEL		> 127)
			||	(acanim->RIGHTWHEEL		> 127)
			||	(acanim->FUELTANK		> 127)
			||	(acanim->CANOPY			> 127)
			||	(acanim->OTHER			> 127)	)
			return(TRUE);
	}
	else
	{
		SimpleAircraftAnimData* acanim = (SimpleAircraftAnimData*)(ac->Anim);
//DeadCode DAW 26Oct00 		int damage =  acanim->LEFTWINGOUT + acanim->LEFTWINGIN + acanim->RIGHTWINGOUT + acanim->RIGHTWINGIN
//DeadCode DAW 26Oct00 					+ acanim->ENGINELEFT + acanim->ENGINERIGHT + acanim->OTHER;
//DeadCode DAW 26Oct00 		if(damage > 255 * 2)
//DeadCode DAW 26Oct00 			return(TRUE);
		if(		(acanim->LEFTWINGOUT	> 63)
			||	(acanim->LEFTWINGIN		> 63)
			||	(acanim->RIGHTWINGOUT	> 63)
			||	(acanim->RIGHTWINGIN	> 63)
			||	(acanim->ENGINELEFT		> 63)
			||	(acanim->ENGINERIGHT	> 63)
			||	(acanim->OTHER			> 127)	)
			return(TRUE);
	}

	return(FALSE);

//DeadCode CSB 6Sep00 	if(Anim != NULL)
//DeadCode CSB 6Sep00 	{
//DeadCode CSB 6Sep00 		AircraftAnimData*		acanim  = NULL;
//DeadCode CSB 6Sep00 		SimpleAircraftAnimData*	saganim = NULL;
//DeadCode CSB 6Sep00 		if(fly.numinsag)
//DeadCode CSB 6Sep00 			saganim = (SimpleAircraftAnimData*)Anim;
//DeadCode CSB 6Sep00 		else
//DeadCode CSB 6Sep00 			acanim = (AircraftAnimData*)Anim;
//DeadCode CSB 6Sep00 		
//DeadCode CSB 6Sep00 		SLong totaldamage = 0;
//DeadCode CSB 6Sep00 		if(acanim != NULL)
//DeadCode CSB 6Sep00 			totaldamage = acanim->ENGINELEFT + acanim->LEFTWINGIN + acanim->RIGHTWINGIN;
//DeadCode CSB 6Sep00 		else if(saganim != NULL)
//DeadCode CSB 6Sep00 			totaldamage = saganim->ENGINELEFT + saganim->LEFTWINGIN + saganim->RIGHTWINGIN;
//DeadCode CSB 6Sep00 
//DeadCode CSB 6Sep00 		if(totaldamage > 255)
//DeadCode CSB 6Sep00 			return(TRUE);
//DeadCode CSB 6Sep00 	}
//DeadCode CSB 6Sep00 	return(FALSE);
}


//return a value between 0 and 255 to indicate ability to make the right decisions
UByte	AirStruc::CombatFactor()
{
	UWord retval;
//##temp

//	if	(classtype->visible == MIG15)
//	{
//		ai.combatskill = SKILL_HERO;
//		ai.morale =   MORALE_TOPMORALE;
//		ai.combatskill = SKILL_REGULAR;
//		ai.morale =   MORALE_MEDIUM;
//		ai.combatskill = SKILL_NOVICE;
//		ai.morale =   MORALE_ROCKBOTTOM;
//	}else
//	{
//		ai.combatskill = SKILL_HERO;
//		ai.morale =   MORALE_TOPMORALE;
//		ai.combatskill = SKILL_REGULAR;
//		ai.morale =   MORALE_MEDIUM;
//		ai.combatskill = SKILL_NOVICE;
//		ai.morale =   MORALE_ROCKBOTTOM;
//	}


	retval = (ai.morale)*(64.0/MORALE_TOPMORALE) + (ai.combatskill)*(192.0/SKILL_MAX);
	if (retval > 255)
		retval = 255;
	

	return((UByte)retval);
}
//return a value between 0 and 255 to indicate ability to fly chosen manoeuvre
UByte	AirStruc::FlyingFactor()
{
	UWord retval;
	
//	if	(classtype->visible == MIG15)
//	{
//		ai.flyingskill = SKILL_HERO;
//		ai.morale =   MORALE_TOPMORALE;
//		ai.flyingskill = SKILL_REGULAR;
//		ai.morale =   MORALE_MEDIUM;
//		ai.flyingskill = SKILL_NOVICE;
//		ai.morale =   MORALE_ROCKBOTTOM;
//	}else
//	{
//		ai.flyingskill = SKILL_HERO;
//		ai.morale =   MORALE_TOPMORALE;
//		ai.flyingskill = SKILL_REGULAR;
//		ai.morale =   MORALE_MEDIUM;
//		ai.flyingskill = SKILL_NOVICE;
//		ai.morale =   MORALE_ROCKBOTTOM;
//	}


	retval = (ai.morale)*(64.0/MORALE_TOPMORALE) + (ai.combatskill)*(192.0/SKILL_MAX);
	if (retval > 255)
		retval = 255;
	
	return((UByte)retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectNextDisengageManoeuvre
//Author		R. Hyde 
//Date			Mon 18 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectNextDisengageManoeuvre ()
{
//## if k(combat.combatskill + morale) < combattime
//	try to Disengage
	AirStrucPtr	unfriendly = NULL;										//RJS 10Nov00
	if (ai.unfriendly && ai.unfriendly->Status.size == AIRSTRUCSIZE)	//RJS 10Nov00
		unfriendly = *ai.unfriendly;									//RJS 10Nov00

	if(!unfriendly)
	{
		ai.manoeuvre = MANOEUVRE_DISENGAGED;
		ai.simpleacm = TRUE;
		ai.ManStep = 0;
		return;
	}

	if(Distance3DSquared(&FindFormpos0()->World) > Float(HALFVISIBLERANGE) * Float(HALFVISIBLERANGE))
		if((!ai.unfriendly) || (!TargetFacingSubject(ANGLES_90Deg)))
		{
			SetUnfriendly(NULL);										//CSB 1Aug00
//DeadCode CSB 1Aug00 			if(unfriendly)
//DeadCode CSB 1Aug00 			{
//DeadCode CSB 1Aug00 				ai.unfriendly = NULL;
//DeadCode CSB 1Aug00 				if(unfriendly->ai.attacker == this)
//DeadCode CSB 1Aug00 					unfriendly->ai.attacker = NULL;
//DeadCode CSB 1Aug00 			}
			ai.manoeuvre = MANOEUVRE_REGROUP;
			ai.ManStep = 0;
			return;
		}


	if(!ai.attacker)
	{
		if(ai.unfriendly)
			SetUnfriendly(NULL);
		ai.manoeuvre = MANOEUVRE_DISENGAGED;
		ai.simpleacm = TRUE;
		ai.ManStep = 0;
		return;
	}

	if((unfriendly->classtype->aerobaticfactor > AEROBATIC_MEDIUM) && (classtype->aerobaticfactor == AEROBATIC_MEDIUM))
	{//prop fighter v jet
		if(Range > ENGAGERANGE)
			ai.manoeuvre = MANOEUVRE_EXTENSION;
		else if (AboveGround(FT_1000))
			ai.manoeuvre = MANOEUVRE_DIVINGSPIN;
		else
			ai.manoeuvre = MANOEUVRE_BREAK90;
	}
	else if((Range > ENGAGERANGE) && (AircraftDamaged()))
	{
		if(ai.morale < MORALE_GOOD)
			ai.manoeuvre = MANOEUVRE_DIVEFORHOME;
		else if	(ai.combatskill < SKILL_REGULAR)
			ai.manoeuvre = MANOEUVRE_GOHOME;
		else
			ai.manoeuvre = MANOEUVRE_CLIMBFORHOME;

		AirStrucPtr	u=*ai.unfriendly;
		if(u)
		{
			SetUnfriendly(NULL);										//CSB 1Aug00
//DeadCode CSB 1Aug00 			ai.unfriendly = NULL;
//DeadCode CSB 1Aug00 			if(u->ai.attacker == this)
//DeadCode CSB 1Aug00 				u->ai.attacker = NULL;
		}
	}
	else if(	(!unfriendly)
			||	(Range > BREAKOFFRANGE)		)
//DeadCode CSB 25Aug00 			||	((unfriendly->classtype->aerobaticfactor == AEROBATIC_LOW) && (Range > INSIDEWEAPONSRANGE))	)
//DeadCode CSB 21Jun00 			&& (ai.manoeuvre != MANOEUVRE_GAINHEIGHT))
	{
		ai.manoeuvre = MANOEUVRE_DISENGAGED;
		SetUnfriendly(NULL);										//CSB 1Aug00
		ai.simpleacm = TRUE;
//DeadCode CSB 25Aug00 		ai.manoeuvre = MANOEUVRE_LOOKROUND;
//DeadCode CSB 25Aug00 		unfriendly = *ai.unfriendly;
//DeadCode CSB 1Aug00 		if(unfriendly->ai.attacker == this)
//DeadCode CSB 1Aug00 			unfriendly->ai.attacker = NULL;
//DeadCode CSB 1Aug00 		ai.unfriendly = NULL;
	}
	else
	{
		if(AircraftDamaged())
			if (SubjectFacingTarget(ANGLES_60Deg))
				ai.manoeuvre = MANOEUVRE_MOVEAWAY;
			else
				ai.manoeuvre = MANOEUVRE_EXTENSION;

		if(ai.morale < MORALE_POOR)
		{
			if(ai.combatskill <= SKILL_POOR)
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
			else if (ai.combatskill < SKILL_REGULAR)
				ai.manoeuvre = MANOEUVRE_DIVEFORHOME;
			else
				ai.manoeuvre = MANOEUVRE_EXTENSION;
		}
		else
		{
			if(TargetFacingSubject(ANGLES_60Deg))
				SelectTailToNoseManoeuvre();
			else
			{
				if(SubjectFacingTarget(ANGLES_60Deg))
					ai.manoeuvre = MANOEUVRE_MOVEAWAY;
				else
					ai.manoeuvre = MANOEUVRE_EXTENSION;
			}
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PanicManoeuvres
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
void	ACMAirStruc::PanicManoeuvres()
{
	int startpoint = Math_Lib.rnd(6);
	switch (startpoint)
	{
		case	0:
		{
			if (!(M_SpinOut()))
				ai.manoeuvre=MANOEUVRE_MILDSCISSORS;	  //RDH 12/06/99
			break;
		}
		case	1:
		{
//DEADCODE CSB 24/01/00 						if (		(ai.combatskill < SKILL_REGULAR)
//DEADCODE CSB 24/01/00 								&&	(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 24/01/00 							)
//DEADCODE CSB 24/01/00 							ai.manoeuvre = MANOEUVRE_BAILOUT;
//DEADCODE CSB 24/01/00 						else 
			if (World.Y > FT_3000)
				ai.manoeuvre = MANOEUVRE_DIVEFORHOME;
			else
				ai.manoeuvre= MANOEUVRE_GOHOME;
			break;
		}
		case	2:
		{
			if (World.Y > FT_3000)
				ai.manoeuvre = MANOEUVRE_STRAIGHTDIVE;
			else
				ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
			break;
  		}
  		case	3:
		{
			ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
			break;
		}
		case	4:
		{
			ai.manoeuvre = MANOEUVRE_PANICTURN;
			break;
		}
		case	5:
		{
//DEADCODE CSB 24/01/00 						if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 24/01/00 						ai.manoeuvre = MANOEUVRE_BAILOUT;
//DEADCODE CSB 24/01/00 						else
			ai.manoeuvre = MANOEUVRE_PANICTURN;
			break;
		}

	}

	advantage = FALSE;
	disadvantage = FALSE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BanditHighManoeuvre
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
void	ACMAirStruc::BanditHighManoeuvre()
{
	if(TargetFacingSubject(ANGLES_45Deg))
	{
		if(ai.morale > MORALE_MEDIUM)
			ai.manoeuvre = MANOEUVRE_GAINHEIGHT;
		else
			PanicManoeuvres();
	}
	else
	{
		if(ai.morale > MORALE_MEDIUM)
		{
			if(Math_Lib.rnd(2))
			{
//DEADCODE CSB 24/01/00 				if(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 24/01/00 //DEADCODE RDH 10/05/99 				if	(classtype->visible == MIG15)
//DEADCODE CSB 24/01/00 					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_ZOOM);
//DEADCODE CSB 24/01/00 				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_BREAKTURN);
			}else
			ai.manoeuvre = MANOEUVRE_GAINHEIGHT;
		}else
			ai.manoeuvre = MANOEUVRE_EXTENSION;
	}
}


void	ACMAirStruc::LowAltManoeuvre()
{
}


Bool	ACMAirStruc::TooLow()
{
	Bool retval = FALSE;
	if((vel_y < 0) && (SWord(pitch) < 0) && (World.Y < HIGHESTGROUND))
	{
		FP TimeToRoll =  SWord(roll) * 100.0;
		TimeToRoll    /= classtype->maxrollrate;

		FP fvely = vel_y;
		FP TimeToLevelOut = -FP(SWord(pitch)) / FP(CalcMaxPitchRate() * 0.01);//* 0.055;	// cs	@ 10deg/s
		FP AltLoss        = -fvely * 0.0001 * (TimeToRoll + TimeToLevelOut * 0.55);	//micro-m/cs * cs * 0.5 * 1.1 -> cm
		AltLoss -= 0.0256 * fvely;

		int groundlevel = Land_Scape.GetGroundLevel(this);
		if((ai.simpleacm) && (ai.unfriendly != Persons2::PlayerGhostAC))
			groundlevel += 10000;
		else
			groundlevel += 5000;

		if(groundlevel > World.Y - AltLoss)
			retval = TRUE;
	}

	return (retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BanditLowManoeuvre
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
void	ACMAirStruc::BanditLowManoeuvre()
{
	AirStrucPtr	unfriendly = *ai. unfriendly;

	if(unfriendly->classtype->aerobaticfactor == AEROBATIC_LOW)
		ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
	else if(SubjectFacingTarget(ANGLES_45Deg))
	{
		if((SubjectOnTargetTail(ANGLES_45Deg)) && (ai.combatskill > SKILL_REGULAR))
			ai.manoeuvre = MANOEUVRE_UPANDUNDER;
		else if((ai.morale > MORALE_MEDIUM) || (Math_Lib.rnd(20)))
		{
			if(Math_Lib.rnd(2))//((unfriendly->vel_ - vel_) > MPH50)
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
			else
				ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
		}
		else
			ai.manoeuvre = MANOEUVRE_LAZYTURN;
	}
	else
	{
		MANOEUVRE tempman;
		if(SubjectFacingTarget(ANGLES_90Deg))
			tempman = MANOEUVRE_TURNINGFIGHT;
		else
			tempman = MANOEUVRE_SPLITS;
		if((ai.morale > MORALE_MEDIUM) || (!Math_Lib.rnd(20)))
		{
			if (ai.morale < MORALE_GOOD)	
				ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,tempman);
			else
				ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,tempman,MANOEUVRE_TURNINGFIGHT);
		}
		else
			ai.manoeuvre = MANOEUVRE_LAZYTURN;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseRadioMessage
//Author		R. Hyde 
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ChooseRadioMessage()
{
	ANGLES trgtlead = ActualLead(*ai.unfriendly, *this);

	if  (		(Range	< INSIDEWEAPONSRANGE)
			&&	(TargetHasCorrectLead(trgtlead, ANGLES_3Deg))
		)
	{
		AirStrucPtr	unfriendly = *ai. unfriendly;
		AirStrucPtr	unfbuddy = unfriendly->FindBuddy();
		if (unfbuddy && !unfbuddy->AcIsPlayer())
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SHOOTHIM, MSG_SHOOTHIM, unfbuddy, *this, unfriendly));
	}

 	if	 (		(Range	< DANGERRANGE)
			&&	(Math_Lib.rnd(RndValMAX) < RND10PC)
			&&	(TargetOnSubjectTail(ANGLES_45Deg))
		 )
	{
		SWord	droll = roll - ((AirStruc*)ai.unfriendly)->roll;
		if (droll < 0)
			droll = -droll;
		
		if (		(roll >> ANGLES_60Deg)
				&& 	(roll << ANGLES_300Deg)
				&&	(droll < 6536)
					
		   )
		{
			SWord	dhdg = fly.dhdg;
			if (dhdg < 0)
				dhdg = -dhdg;
			SWord	trgdhdg = ((AirStruc*)ai.unfriendly)->fly.dhdg;
			if (trgdhdg < 0)
				trgdhdg = -trgdhdg;
			SWord delta = trgdhdg - dhdg;
			if (		(delta > 0)
					&&	((dhdg * 100/Timer_Code.FRAMETIME) > ((SWord)ANGLES_5Deg))
					&&	((trgdhdg * 100/Timer_Code.FRAMETIME) > ((SWord)ANGLES_6Deg))
			   )
			{
				AirStruc*	callee = FindBuddy();
				if (callee)
				{
					if(Math_Lib.rnd(2))
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OUTTURN, MSG_OUTTURN, *this, NULL, callee));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TURNINSIDE, MSG_OUTTURN, *this, NULL, callee));
				}
			}
		}
	}



}
void	ACMAirStruc::SetACMType()
{
	if	(
			(
					(ai.unfriendly == Persons2::PlayerGhostAC)
				||	(ai.attacker == Persons2::PlayerGhostAC)
				||	(this == Manual_Pilot.ControlledAC2)
			   	||	(
							(Save_Data.gamedifficulty [GD_AIPILOTSALLTIME])
						||	(ai.unfriendly && ai.unfriendly->uniqueID.commsmove)	//AMM 07May99
						||	(ai.attacker && ai.attacker->uniqueID.commsmove)		//AMM 07May99
					)
			)
			&& (classtype->visible != DEF)						//CSB 17Jan99
			&& (classtype->visible != JU87)						//CSB 17Jan99
//DEADCODE RDH 18/06/99 			&&
//DEADCODE RDH 18/06/99 			(World.Y >= FT_1000)									//RDH 05Jun97 problems with manual acm on takeoff
		)
	{
//DeadCode DAW 12May99 		if(classtype->aerobaticfactor == AEROBATIC_LOW)	//CSB 06/05/99	
//DeadCode DAW 12May99 			INT3;
//DeadCode DAW 12May99 		//TRYING TO RUN FLIGHT MODEL FOR HEAVY BOMBERS
		if(ai.simpleacm)
		{
			Manual_Pilot.InitFlightModelPos(this);
//DeadCode CSB 13/07/99				int Breakpoint = 0;	//CSB 18/06/99	
		}
		ai.simpleacm = FALSE;
	}
	else
		ai.simpleacm = TRUE;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectNextEngageManoeuvre
//Author		Craig Beeston
//Date			Mon 04 September 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SelectNextEngageManoeuvre()
{
  	ai.ManStep = PHASE0;
	SetManoeuvreTime(0);

	SetACMType();
	if((ai.unfriendly == NULL) || (ai.unfriendly->Status.deaded))	//break link with dead unfriendly
	{								
		ai.ManStep = PHASE0;
		if(		((fly.pModel->Type == AT_SPITFIRE) || (fly.pModel->Type == AT_HURRICANE))
			&&	(ai.morale > MORALE_MEDIUM) && (!Math_Lib.rnd(10))	)
			ai.manoeuvre = MANOEUVRE_ROLL360;
		else
		{
			ai.manoeuvre = MANOEUVRE_DISENGAGED;
			ai.simpleacm = TRUE;
		}

		SetUnfriendly(NULL);										//CSB 1Aug00
		return;
	}

	FP gohomefract = 0.5;
	if((ai.unfriendly) && (AirStrucPtr(ai.unfriendly)->ai.manoeuvre == MANOEUVRE_SCREWYOUGUYSIMGOINGHOME))
		gohomefract = 0.25;
	if((!formpos) && (GroupShouldGoHome(gohomefract)))
	{
		if(follower)
   			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_STATUSREPORT, *this, NULL, Follower()));
		else if(fly.nextflight)
   			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_STATUSREPORT, *this, NULL, fly.nextflight));

		for(AirStrucPtr nf = this; nf; nf = nf->fly.nextflight)
			for(AirStrucPtr f = nf; f; f = f->Follower())
			{
				f->waypoint = f->waypoint->FindWP(WPNAME_EscDisperse);
				if((f->movecode != AUTO_COMBAT) || (!f->ai.unfriendly))
				{
					f->SetUnfriendly(NULL);
					f->movecode = AUTO_FOLLOWWP;
					f->information = IF_OUT_POS;
					f->manoeuvretime = 0;
					f->ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
				}
			}
	}
	else
	{
		bool goinghome = false;
		for(AirStrucPtr ld = FindFormpos0(); (ld) && (!goinghome); ld = ld->fly.nextflight)
			for(AirStrucPtr fl = ld; (fl) && (!goinghome); fl = fl->Follower())
				if(fl->ai.manoeuvre == MANOEUVRE_SCREWYOUGUYSIMGOINGHOME)
					goinghome = true;

		if(goinghome)
		{
			ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
			return;
		}
	}

	if(TimeToChangeToDisengage())
	{
		if (AcIsGroupLeader())
		{
			if(follower)
	   			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_REGROUP, MSG_STATUSREPORT, *this, NULL, Follower()));
			else if(fly.nextflight)
	   			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_REGROUP, MSG_STATUSREPORT, *this, NULL, fly.nextflight));
//DeadCode CSB 13Sep00 			if(Math_Lib.rnd(RndValMAX) < RND25PC)
//DeadCode CSB 13Sep00 	   			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_STATUSREPORT, *this, NULL, callee));
		}
		advantage = FALSE;
		disadvantage = FALSE;
		SelectNextDisengageManoeuvre ();
		return;
	}
	ChooseRadioMessage();


	if((ai.combatskill < 30) && (AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor != AEROBATIC_LOW))
	{
		switch(Math_Lib.rnd(5))
		{
			case 0:	ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;	return;
			case 1:	ai.manoeuvre = MANOEUVRE_MOVEAWAY;			return;
			case 2:	ai.manoeuvre = MANOEUVRE_GAINHEIGHT;		return;
			case 3:	ai.manoeuvre = MANOEUVRE_GAINSPEED;			return;
			case 4:	ai.manoeuvre = MANOEUVRE_LAZYTURN;			return;
		}
	}


	enum CombatStatus {CS_THREATENING, CS_HUNTER, CS_NEUTRAL, CS_HUNTED, CS_THREATENED};
	CombatStatus combatstatus = CS_NEUTRAL;

	AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
	FP dist2 = Distance3DSquared(&unf->World);
	if(dist2 < FP(COMBATRANGE) * FP(COMBATRANGE))
	{
		FP MYdotprod  = FP(unf->World.X - World.X) * FP(vel_x) + FP(unf->World.Y - World.Y) * FP(vel_y) + FP(unf->World.Z - World.Z) * FP(vel_z);
		FP UNFdotprod = FP(World.X - unf->World.X) * FP(unf->vel_x) + FP(World.Y - unf->World.Y) * FP(unf->vel_y) + FP(World.Z - unf->World.Z) * FP(unf->vel_z);

		if(MYdotprod > UNFdotprod)
			combatstatus = CS_HUNTER;
		else
			combatstatus = CS_HUNTED;
		
		if(dist2 < FP(WEAPONSRANGE) * FP(WEAPONSRANGE))
		{
			Range = Distance3D(&unf->World);
			MYdotprod  /= FP(Range) * FP(vel_);
			UNFdotprod /= FP(Range) * FP(unf->vel_);

			if(combatstatus == CS_HUNTER)
			{
				if(MYdotprod * MYdotprod + UNFdotprod * UNFdotprod > 1.0)
					combatstatus = CS_THREATENING;
			}
			else
			{
				if(MYdotprod * MYdotprod + UNFdotprod * UNFdotprod > 1.0)
					combatstatus = CS_THREATENED;
			}
		}
	}
	else
	{
		if((classtype->visible == JU87) || (classtype->visible == DEF))
		{
			SetUnfriendly(NULL);
			ai.manoeuvre = MANOEUVRE_DISENGAGED;
			ai.simpleacm = TRUE;
			ai.ManStep = 0;
			SetManoeuvreTime(0);
		}
		else
		{
			movecode = AUTO_PRECOMBAT;
			SetManoeuvreTime(0);
			information = IF_OUT_POS;
		}
		return;
	}

	if((unf->vel_ <= 100000) && (combatstatus <= CS_HUNTED))
	{
		ai.manoeuvre = MANOEUVRE_STRAFFE;
		ai.ManStep = 0;
		return;
	}

	bool choosegood = false;
	bool choosebad  = false;

	int rnd = Math_Lib.rnd(65536);
	int goodval = 65536 - ai.combatskill * ai.combatskill;
	int badval  = (256 - ai.combatskill) * (256 - ai.combatskill);

	if(rnd > goodval)
		choosegood = true;
	else if(rnd < badval)
		choosebad = true;

	if(unf->classtype->aerobaticfactor == AEROBATIC_LOW) 
	{
		switch(combatstatus)
		{
			case CS_THREATENING:
			{
				if((unf != Persons2::PlayerSeenAC) && (Range < 25000) && (!Math_Lib.rnd(5)))
				{
					AircraftAnimData* adptr = (AircraftAnimData*)Anim;
					if((adptr->LEFTWINGIN > 128) || (adptr->RIGHTWINGIN > 128) || (adptr->ENGINELEFT > 128))
					{
						ai.manoeuvre = MANOEUVRE_COLLIDE;
						return;
					}
				}

				if(choosebad)
					ai.manoeuvre = MANOEUVRE_SLASHINGATTACK;
				else
					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				return;
			}
			case CS_HUNTER:
			{
				if(choosebad)
					ai.manoeuvre = MANOEUVRE_TURNTOHDGANDPITCH;
				else
					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				return;
			}
			case CS_HUNTED:
			{
				if(choosegood)
					ai.manoeuvre = MANOEUVRE_TURNTOHDGANDPITCH;
				else if(choosebad)
					ai.manoeuvre = MANOEUVRE_GAINHEIGHT;
				else
					ai.manoeuvre = MANOEUVRE_IMMELMANNTURN;
				return;
			}
			case CS_THREATENED:
			{
				if(choosegood)
					ai.manoeuvre = MANOEUVRE_ZOOM;
				else
					ai.manoeuvre = MANOEUVRE_GAINHEIGHT;
				return;
			}
		}
		return;
	}

	if((fly.pModel->Type == AT_SPITFIRE) || (fly.pModel->Type == AT_HURRICANE))
	{
		switch(combatstatus)
		{
			case CS_THREATENING:
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				return;
			}
			case CS_HUNTER:
			{
				if(choosebad)
					ai.manoeuvre = MANOEUVRE_TURNTOHDGANDPITCH;
				else
					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				return;
			}
			case CS_HUNTED:
			{
				if(choosegood)
					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				else if(choosebad)
					ai.manoeuvre = MANOEUVRE_TURNTOHDGANDPITCH;
				else
					ai.manoeuvre = MANOEUVRE_IMMELMANNTURN;
				return;
			}
			case CS_THREATENED:
			{
				if(choosegood)
					switch(Math_Lib.rnd(5))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_DIVINGSPIN;	return;
						case 1:	ai.manoeuvre = MANOEUVRE_HIGBARRELROLL;	return;
						case 2:	ai.manoeuvre = MANOEUVRE_SPLITS;		return;
						case 3:
						case 4:	ai.manoeuvre = MANOEUVRE_CLIMBTURN;		return;
					}
				else if(choosebad)
					switch(Math_Lib.rnd(4))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_SCISSORS;		return;
						case 1:	ai.manoeuvre = MANOEUVRE_REVERSETURN;	return;
						case 2:	ai.manoeuvre = MANOEUVRE_JINK;			return;
						case 3:	ai.manoeuvre = MANOEUVRE_BREAKTURN;		return;
					}
				else
					switch(Math_Lib.rnd(5))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_BREAKLOW;			return;
						case 1:	ai.manoeuvre = MANOEUVRE_BREAKHIGH;			return;
						case 2:	ai.manoeuvre = MANOEUVRE_BREAK90;			return;
						case 3:	ai.manoeuvre = MANOEUVRE_PANICTURN;			return;
						case 4:	ai.manoeuvre = MANOEUVRE_UNBALANCEDFLIGHT;	return;
					}
				return;
			}
		}
		return;
	}

	if((fly.pModel->Type == AT_BF109) || (fly.pModel->Type == AT_BF110))
	{
		switch(combatstatus)
		{
			case CS_THREATENING:
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				return;
			}
			case CS_HUNTER:
			{
				if(choosegood)
				{
					if(Distance3DSquared(&unf->World) < FP(INSIDEWEAPONSRANGE) * FP(INSIDEWEAPONSRANGE))
						ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
					else if(	(SWord(unf->roll) < ANGLES_15Deg)  && (-SWord(unf->roll) < ANGLES_15Deg)
							&&	(SWord(unf->pitch) < ANGLES_15Deg) && (-SWord(unf->pitch) < ANGLES_15Deg)	)
						ai.manoeuvre = MANOEUVRE_UPANDUNDER;
					else
						if(World.Y < ai.unfriendly->World.Y)
							ai.manoeuvre = MANOEUVRE_INTERCEPTHIGH;
						else
							ai.manoeuvre = MANOEUVRE_INTERCEPTLOW;
				}
				else if(choosebad)
					ai.manoeuvre = MANOEUVRE_TURNTOHDGANDPITCH;
				else
					if(World.Y < ai.unfriendly->World.Y)
						ai.manoeuvre = MANOEUVRE_INTERCEPTHIGH;
					else
						ai.manoeuvre = MANOEUVRE_INTERCEPTLOW;
				return;
			}
			case CS_HUNTED:
			{
				if(choosegood)
				{
					if(Math_Lib.rnd(2))
						ai.manoeuvre = MANOEUVRE_IMMELMANNTURN;
					else
						ai.manoeuvre = MANOEUVRE_INTERCEPTHIGH;
				}
				else if(choosebad)
				{
					if(Math_Lib.rnd(2))
						ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
					else
						ai.manoeuvre = MANOEUVRE_STALLTURN;
				}
				else
					if(World.Y < ai.unfriendly->World.Y)
						ai.manoeuvre = MANOEUVRE_INTERCEPTHIGH;
					else
						ai.manoeuvre = MANOEUVRE_INTERCEPTLOW;
				return;
			}
			case CS_THREATENED:
			{
				if(choosegood)
					switch(Math_Lib.rnd(3))
					{
						case 0:	
						case 1:	if(unf->World.Y > World.Y)		ai.manoeuvre = MANOEUVRE_ZOOM;
								else							ai.manoeuvre = MANOEUVRE_STEEPDIVE;
								return;
						case 2:	ai.manoeuvre = MANOEUVRE_HIGBARRELROLL;	return;
		//DeadCode CSB 5Nov00 				case 2:	return(MANOEUVRE_ZOOM);
		//DeadCode CSB 21Oct00 				case 3:	return(MANOEUVRE_STALLTURN);
					}
//DeadCode CSB 5Nov00 					{
//DeadCode CSB 5Nov00 						case 0:	ai.manoeuvre = MANOEUVRE_STEEPDIVE;		return;
//DeadCode CSB 5Nov00 						case 1:	ai.manoeuvre = MANOEUVRE_HIGBARRELROLL;	return;
//DeadCode CSB 5Nov00 						case 2:	ai.manoeuvre = MANOEUVRE_ZOOM;			return;
//DeadCode CSB 5Nov00 //DeadCode CSB 21Oct00 						case 3:	ai.manoeuvre = MANOEUVRE_STALLTURN;		return;
//DeadCode CSB 5Nov00 					}
				else if(choosebad)
					switch(Math_Lib.rnd(5))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_SCISSORS;		return;
						case 1:	ai.manoeuvre = MANOEUVRE_REVERSETURN;	return;
						case 2:	ai.manoeuvre = MANOEUVRE_JINK;			return;
						case 3:	ai.manoeuvre = MANOEUVRE_BREAKTURN;		return;
						case 4:	ai.manoeuvre = MANOEUVRE_STALLTURN;		return;
					}
				else
					switch(Math_Lib.rnd(5))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_BREAKLOW;			return;
						case 1:	ai.manoeuvre = MANOEUVRE_BREAKHIGH;			return;
						case 2:	ai.manoeuvre = MANOEUVRE_BREAK90;			return;
						case 3:	ai.manoeuvre = MANOEUVRE_PANICTURN;			return;
						case 4:	ai.manoeuvre = MANOEUVRE_UNBALANCEDFLIGHT;	return;
					}
				return;
			}
		}
		return;
	}

	//Two seaters
	{
		switch(combatstatus)
		{
			case CS_THREATENING:
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				return;
			}
			case CS_HUNTER:
			{
				if(choosegood)
				{
					if(Math_Lib.rnd(2))
						ai.manoeuvre = MANOEUVRE_DIVEFORHOME;
					else
						ai.manoeuvre = MANOEUVRE_MAKEFORFRIENDLY;
				}
				else if(choosebad)
				{
					if(Math_Lib.rnd(2))
						ai.manoeuvre = MANOEUVRE_MOVEAWAY;
					else
						ai.manoeuvre = MANOEUVRE_EXTENSION;
				}
				else
				{
					if(Math_Lib.rnd(2))
						ai.manoeuvre = MANOEUVRE_CLIMBFORHOME;
					else
						ai.manoeuvre = MANOEUVRE_GOHOME;
				}
				return;
			}
			case CS_HUNTED:
			{  
				if(choosegood)
					switch(Math_Lib.rnd(3))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_DIVEFORHOME;	return;
						case 1:	ai.manoeuvre = MANOEUVRE_CLIMBFORHOME;	return;
						case 2:	ai.manoeuvre = MANOEUVRE_GOHOME;		return;
					}
				else if(choosebad)
					switch(Math_Lib.rnd(2))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_MAKEFORFRIENDLY;	return;
						case 1:	ai.manoeuvre = MANOEUVRE_LUFBERRY;			return;
					}
				else
					switch(Math_Lib.rnd(3))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_MOVEAWAY;			return;
						case 1:	ai.manoeuvre = MANOEUVRE_STRAIGHTDIVE;		return;
						case 2:	ai.manoeuvre = MANOEUVRE_EXTENSION;			return;
					}
				return;
			}
			case CS_THREATENED:
			{
				if(choosegood)
					switch(Math_Lib.rnd(2))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_DIVEFORHOME;	return;
						case 1:	ai.manoeuvre = MANOEUVRE_STEEPDIVE;		return;
					}
				else if(choosebad)
					switch(Math_Lib.rnd(3))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_LAZYTURN;		return;
						case 1:	ai.manoeuvre = MANOEUVRE_STRAIGHTDIVE;	return;
						case 2:	ai.manoeuvre = MANOEUVRE_BAILOUT;		return;
					}
				else
					switch(Math_Lib.rnd(3))
					{
						case 0:	ai.manoeuvre = MANOEUVRE_MILDSCISSORS;	return;
						case 1:	ai.manoeuvre = MANOEUVRE_STALLTURN;		return;
						case 2:	ai.manoeuvre = MANOEUVRE_REVERSETURN;	return;
					}
				return;
			}
		}
		return;
	}
}


//DeadCode CSB 4Sep00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode CSB 4Sep00 //Procedure		SelectNextEngageManoeuvre
//DeadCode CSB 4Sep00 //Author		R. Hyde 
//DeadCode CSB 4Sep00 //Date			Tue 12 Mar 1996
//DeadCode CSB 4Sep00 //
//DeadCode CSB 4Sep00 //Description	
//DeadCode CSB 4Sep00 //
//DeadCode CSB 4Sep00 //Inputs		PitchIntercept, HdgIntercept and Range set 
//DeadCode CSB 4Sep00 //
//DeadCode CSB 4Sep00 //Returns	
//DeadCode CSB 4Sep00 //
//DeadCode CSB 4Sep00 //------------------------------------------------------------------------------
//DeadCode CSB 4Sep00 void	ACMAirStruc::SelectNextEngageManoeuvre ()
//DeadCode CSB 4Sep00 {
//DeadCode CSB 4Sep00   	SWord	startpoint;
//DeadCode CSB 4Sep00 	Bool	oldadvantage, olddisadvantage;
//DeadCode CSB 4Sep00 	MANOEUVRE	oldmanoeuvre = ai.manoeuvre;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 	SetACMType();
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 	oldadvantage = advantage;
//DeadCode CSB 4Sep00 	olddisadvantage = disadvantage;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 	if((ai.unfriendly == NULL) || (ai.unfriendly->Status.deaded))
//DeadCode CSB 4Sep00 	{//break link with dead unfriendly
//DeadCode CSB 4Sep00 		ai.ManStep = PHASE0;
//DeadCode CSB 4Sep00 		if(		((fly.pModel->Type == AT_SPITFIRE) || (fly.pModel->Type == AT_HURRICANE))
//DeadCode CSB 4Sep00 			&&	(ai.morale > MORALE_MEDIUM) && (!Math_Lib.rnd(10))	)
//DeadCode CSB 4Sep00 			ai.manoeuvre = MANOEUVRE_ROLL360;
//DeadCode CSB 4Sep00 		else
//DeadCode CSB 4Sep00 //DeadCode CSB 25Aug00 			ai.manoeuvre = MANOEUVRE_LOOKROUND;						//JIM 18Oct96
//DeadCode CSB 4Sep00 			ai.manoeuvre = MANOEUVRE_DISENGAGED;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 		SetUnfriendly(NULL);										//CSB 1Aug00
//DeadCode CSB 4Sep00 //DeadCode CSB 1Aug00 		if((ai.unfriendly) && (((AirStrucPtr)*ai.unfriendly)->ai.attacker == this))
//DeadCode CSB 4Sep00 //DeadCode CSB 1Aug00 			((AirStrucPtr)*ai.unfriendly)->ai.attacker = NULL;
//DeadCode CSB 4Sep00 //DeadCode CSB 1Aug00 		ai.unfriendly = NULL;
//DeadCode CSB 4Sep00 		return;
//DeadCode CSB 4Sep00 	}
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00   	ai.ManStep = PHASE0;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 	if(TimeToChangeToDisengage())
//DeadCode CSB 4Sep00 	{
//DeadCode CSB 4Sep00 		if (AcIsGroupLeader())
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			AirStruc*	callee = FindABuddyWithPlayerGivenPriority();
//DeadCode CSB 4Sep00 			if	(Math_Lib.rnd(RndValMAX) < RND25PC)
//DeadCode CSB 4Sep00 	   			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_REGROUP, MSG_STATUSREPORT, *this, NULL, callee));
//DeadCode CSB 4Sep00 			if	(Math_Lib.rnd(RndValMAX) < RND25PC)
//DeadCode CSB 4Sep00 	   			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_STATUSREPORT, *this, NULL, callee));
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 		advantage = FALSE;
//DeadCode CSB 4Sep00 		disadvantage = FALSE;
//DeadCode CSB 4Sep00 		SelectNextDisengageManoeuvre ();
//DeadCode CSB 4Sep00 		return;
//DeadCode CSB 4Sep00 	}
//DeadCode CSB 4Sep00 	ChooseRadioMessage();
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 	if(		(classtype->aerobaticfactor < AEROBATIC_HIGH) && (ai.morale < MORALE_GOOD) 
//DeadCode CSB 4Sep00 		&&	(Art_Int.CountSquadronSize(this) >= 6)	)
//DeadCode CSB 4Sep00 		ai.manoeuvre = MANOEUVRE_LUFBERRY;
//DeadCode CSB 4Sep00 	else if(World.Y - ai.unfriendly->World.Y > FT_3000)
//DeadCode CSB 4Sep00 	{
//DeadCode CSB 4Sep00  		BanditLowManoeuvre();
//DeadCode CSB 4Sep00 	}
//DeadCode CSB 4Sep00 	else if(World.Y - ai.unfriendly->World.Y < -FT_3000)
//DeadCode CSB 4Sep00 	{
//DeadCode CSB 4Sep00  		BanditHighManoeuvre();
//DeadCode CSB 4Sep00 	}
//DeadCode CSB 4Sep00 //DeadCode RDH 30Nov98   	elseif ((ai.morale < MORALE_VERYPOOR) || (ai.combatskill  < SKILL_POOR))
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00   	elseif (			(ai.combatskill  <= SKILL_POOR)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 				   &&	(classtype->phrasename == OLDPHRASE_MIGS)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 			)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00   	{
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 		advantage = FALSE;
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 		disadvantage = FALSE;
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 		RndVal	rndnum = Math_Lib.rnd();
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 		if (		(classtype->phrasename == OLDPHRASE_MIGS)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 //DEADCODE RDH 10/05/99 		if	(		(classtype->visible == MIG15)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 				&&	(rndnum > RND99PC)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 				&&	(Range	< INSIDEWEAPONSRANGE)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 				&&	TargetFacingSubject(ANGLES_45Deg)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 			)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 			ai.manoeuvre = MANOEUVRE_BAILOUT;
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 		else 
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 		{
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 			if (ai.combatskill  < SKILL_POOR)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 	  			ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 			else
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 	  	 		ai.manoeuvre = MANOEUVRE_LAZYTURN;
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 		}
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00  	}else if (		(ai.morale <= MORALE_POOR)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 			   &&	(classtype->phrasename == OLDPHRASE_MIGS)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 			)
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00 	{
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00  		PanicManoeuvres();
//DeadCode CSB 4Sep00 //DEADCODE CSB 24/01/00		}
//DeadCode CSB 4Sep00 	elseif	(SubjectFacingTarget(ANGLES_45Deg))
//DeadCode CSB 4Sep00 	{
//DeadCode CSB 4Sep00 		if (LooseDeuceSituation())
//DeadCode CSB 4Sep00 		   TakeLooseDeuceOption();
//DeadCode CSB 4Sep00 		else if (TargetFacingSubject(ANGLES_45Deg))
//DeadCode CSB 4Sep00 			SelectNoseToNoseManoeuvre();
//DeadCode CSB 4Sep00 		else if (SubjectOnTargetTail(ANGLES_45Deg))
//DeadCode CSB 4Sep00 			SelectNoseToTailManoeuvre();
//DeadCode CSB 4Sep00 		else
//DeadCode CSB 4Sep00 			SelectNoseToBeamManoeuvre();
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 		advantage = TRUE;
//DeadCode CSB 4Sep00 		disadvantage = FALSE;
//DeadCode CSB 4Sep00   		
//DeadCode CSB 4Sep00 	}elseif (TargetOnSubjectTail(ANGLES_45Deg))
//DeadCode CSB 4Sep00 	{
//DeadCode CSB 4Sep00 		if (TargetFacingSubject(ANGLES_45Deg))
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			AirStruc* callee = FindABuddyWithPlayerGivenPriority();
//DeadCode CSB 4Sep00 			if(callee)
//DeadCode CSB 4Sep00 			{
//DeadCode CSB 4Sep00 				RndVal rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
//DeadCode CSB 4Sep00 				if(rndpc > RND90PC)
//DeadCode CSB 4Sep00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OUTTURN, MSG_OUTTURN, *this, NULL, callee));
//DeadCode CSB 4Sep00 				else if(rndpc > RND75PC)
//DeadCode CSB 4Sep00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TURNINSIDE, MSG_OUTTURN, *this, NULL, callee));
//DeadCode CSB 4Sep00 			}
//DeadCode CSB 4Sep00 			
//DeadCode CSB 4Sep00 			SelectTailToNoseManoeuvre();
//DeadCode CSB 4Sep00 			advantage = FALSE;
//DeadCode CSB 4Sep00 			disadvantage = TRUE;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 		}else if (SubjectOnTargetTail(ANGLES_45Deg))
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			SelectTailToTailManoeuvre();
//DeadCode CSB 4Sep00 			advantage = FALSE;
//DeadCode CSB 4Sep00 			disadvantage = FALSE;
//DeadCode CSB 4Sep00 		}else	
//DeadCode CSB 4Sep00 		{// target on subject tail and subject on target beam
//DeadCode CSB 4Sep00 			SelectTailToBeamManoeuvre();
//DeadCode CSB 4Sep00 			advantage = FALSE;
//DeadCode CSB 4Sep00 			disadvantage = FALSE;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 	}else
//DeadCode CSB 4Sep00 	{	if (LooseDeuceSituation())
//DeadCode CSB 4Sep00 			TakeLooseDeuceOption();
//DeadCode CSB 4Sep00 		else if (TargetFacingSubject(ANGLES_45Deg))
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			SelectBeamToNoseManoeuvre();
//DeadCode CSB 4Sep00 			advantage = FALSE;
//DeadCode CSB 4Sep00 			disadvantage = TRUE;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 		}else if (SubjectOnTargetTail(ANGLES_45Deg))
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			SelectBeamToTailManoeuvre();
//DeadCode CSB 4Sep00 			advantage = FALSE;
//DeadCode CSB 4Sep00 			disadvantage = FALSE;
//DeadCode CSB 4Sep00 		}else
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			SelectBeamToBeamManoeuvre();
//DeadCode CSB 4Sep00 			advantage = FALSE;
//DeadCode CSB 4Sep00 			disadvantage = FALSE;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 	}
//DeadCode CSB 4Sep00 	if (oldmanoeuvre != ai.manoeuvre)
//DeadCode CSB 4Sep00 	{
//DeadCode CSB 4Sep00 //DeadCode CSB 09/03/99			fly.pAcmModel->ZeroIntControl();	//CSB 09/03/99
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 		if (_DPlay.Implemented)
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			if (this->CommsOwner==Persons2::PlayerSeenAC->uniqueID.count)	//AMM 11Jan99
//DeadCode CSB 4Sep00 			{												//AMM 11Jan99
//DeadCode CSB 4Sep00 				_DPlay.AddAIACToPositionList(this);			//AMM 11Jan99
//DeadCode CSB 4Sep00 			}												//AMM 11Jan99
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 	}
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 	MoraleMod();
//DeadCode CSB 4Sep00 }


//------------------------------------------------------------------------------
void	ACMAirStruc::MoraleMod()

{
	return;	//CSB 07/07/99	

//DeadCode CSB 07/07/99			SWord	inc = 0;
//DeadCode CSB 07/07/99			SWord	incsum = 0;
//DeadCode CSB 07/07/99			if (Range < COLLISIONRANGE)
//DeadCode CSB 07/07/99				inc = 20;
//DeadCode CSB 07/07/99			else if (Range < WEAPONSRANGE)
//DeadCode CSB 07/07/99				inc = 10;
//DeadCode CSB 07/07/99			else if (Range < DANGERRANGE)
//DeadCode CSB 07/07/99				inc = 5;
//DeadCode CSB 07/07/99			else if (Range < ENGAGERANGE)
//DeadCode CSB 07/07/99				inc = 2;
//DeadCode CSB 07/07/99			if (advantage == TRUE)
//DeadCode CSB 07/07/99			{
//DeadCode CSB 07/07/99				incsum = ai.moraleinc +	inc; 
//DeadCode CSB 07/07/99				if (incsum > 127)
//DeadCode CSB 07/07/99					incsum = 127;
//DeadCode CSB 07/07/99				ai.moraleinc = incsum;
//DeadCode CSB 07/07/99			}
//DeadCode CSB 07/07/99			if  (		(disadvantage == TRUE)
//DeadCode CSB 07/07/99					&&	(ai.morale <= MORALE_GOOD)
//DeadCode CSB 07/07/99				)
//DeadCode CSB 07/07/99			{
//DeadCode CSB 07/07/99				incsum = ai.moraleinc -	inc; 
//DeadCode CSB 07/07/99				if (incsum < -127)
//DeadCode CSB 07/07/99					incsum = -127;
//DeadCode CSB 07/07/99				ai.moraleinc = incsum;
//DeadCode CSB 07/07/99			}
//DeadCode CSB 07/07/99			if (ai.manoeuvre == MANOEUVRE_BREAKTURN)
//DeadCode CSB 07/07/99				ai.moraleinc -=	4;
//DeadCode CSB 07/07/99	
//DeadCode CSB 07/07/99			if (ai.moraleinc > MORALEINC_STEP)
//DeadCode CSB 07/07/99			{
//DeadCode CSB 07/07/99				ai.moraleinc = 0;
//DeadCode CSB 07/07/99				if (	(MORALE_TOPMORALE - ai.morale) > MORALE_STAGE)
//DeadCode CSB 07/07/99					ai.morale = ai.morale + MORALE_STAGE;
//DeadCode CSB 07/07/99				else
//DeadCode CSB 07/07/99					ai.morale = MORALE_TOPMORALE;
//DeadCode CSB 07/07/99	
//DeadCode CSB 07/07/99			}else if (ai.moraleinc < -MORALEINC_STEP)
//DeadCode CSB 07/07/99			{
//DeadCode CSB 07/07/99				ai.moraleinc = 0;
//DeadCode CSB 07/07/99				if (ai.morale > MORALE_STAGE)
//DeadCode CSB 07/07/99					ai.morale = ai.morale - MORALE_STAGE;
//DeadCode CSB 07/07/99				else
//DeadCode CSB 07/07/99					ai.morale = MORALE_ROCKBOTTOM;
//DeadCode CSB 07/07/99			}
//DeadCode CSB 07/07/99	
//DeadCode CSB 07/07/99		if (this==Manual_Pilot.ControlledAC2)						//RJS 18Jun99
//DeadCode CSB 07/07/99			_Miles.SequenceAudible((MoraleType)ai.morale,100,500);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LooseDeuceSituation
//Author		R. Hyde 
//Date			Fri 20 Mar 1998
//
//Description	if not leader and on loose deuce and on same unfriendly as
//				leader take the option
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::LooseDeuceSituation()
{
	AirStrucPtr	unfriendly = *ai. unfriendly;

	if (	(leader)
		&&	(ai.elementtactics == LOOSEDEUCE)
		&&	(unfriendly == ((AirStrucPtr)leader)->ai.unfriendly)
		)
	{
		return (TRUE);
	}else
		return(FALSE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TakeLooseDeuceOption
//Author		R. Hyde 
//Date			Fri 20 Mar 1998
//
//Description	either take the shot or gets some distance for a better shot
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::TakeLooseDeuceOption()
{
	if	(		(SubjectFacingTarget(ANGLES_45Deg))
			&&	(Range < DANGERRANGE)
		)
	{
  	 	ai.manoeuvre = 	MANOEUVRE_LEADPURSUIT;
	}else if(		((ai.combatskill < SKILL_REGULAR)	&& (vel_ < CornerSpeed()))
				||	((ai.combatskill > SKILL_REGULAR)	&& (vel_ < SustainedTurnSpeed()))
			)
	{
//DEADCODE CB 18/11/99 		if (ai.combatskill < SKILL_REGULAR)	
	  	 	ai.manoeuvre = 	MANOEUVRE_GAINHEIGHT;
//DEADCODE CB 18/11/99 		else
//DEADCODE CB 18/11/99 	  	 	ai.manoeuvre = 	MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED;
	}
	else	
//DEADCODE CB 18/11/99 		ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_IMMELMANN,MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED);
		ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_IMMELMANN,MANOEUVRE_GAINHEIGHT); //CB 18/11/99
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TimeToChangeToDisengage
//Author		R. Hyde 
//Date			Thu 14 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::TimeToChangeToDisengage ()
{
	WeapAnimData*	weapon;										//RJS 29Aug96
	SLong			xpos, ypos, zpos;							//RJS 29Aug96
	UWord			index;										//RJS 03Sep96
	AirStrucPtr	unfriendly = *ai. unfriendly;
	ULong			mvel;										//RJS 12Nov99
	UWord			mdelay,mburst;								//RJS 12Nov99

	SWord combatfactor = CombatFactor() * 50;

//DeadCode CSB 5Sep00 	if((unfriendly->classtype->aerobaticfactor > AEROBATIC_MEDIUM) && (classtype->aerobaticfactor == AEROBATIC_MEDIUM))
//DeadCode CSB 5Sep00 	//prop fighter v jet
//DeadCode CSB 5Sep00 		return (TRUE);											//RDH 20Mar98

	FP gohomefract = 0.5;
	if((ai.unfriendly) && (AirStrucPtr(ai.unfriendly)->ai.manoeuvre == MANOEUVRE_SCREWYOUGUYSIMGOINGHOME))
		gohomefract = 0.25;
	if((!formpos) && (GroupShouldGoHome(gohomefract)))
		return(TRUE);

	if(Range > VISIBLERANGE)									//JIM 21Oct96
		return (TRUE);											//JIM 21Oct96

//DeadCode CSB 17Oct00 	if(		(!formpos) && (fly.leadflight) && (fly.leadflight->classtype->aerobaticfactor == AEROBATIC_LOW) 
//DeadCode CSB 17Oct00 		&&	(Distance3DSquared(&fly.leadflight->World) > FP(VISIBLERANGE) * FP(VISIBLERANGE))	)
//DeadCode CSB 17Oct00 		return(TRUE);

//	if((you are chasing him) and (he is running away) and (he is going faster than you) and (range > f(breakoffrange, morale)))
	if(unfriendly->vel_ > vel_)
		if(Range > BREAKOFFRANGE * (1.0 + 2.0 * FP(ai.morale) / FP(MORALE_TOPMORALE)))
		{
			FP chasing = (  FP(unfriendly->World.X - World.X) * FP(vel_x)
						  + FP(unfriendly->World.Y - World.Y) * FP(vel_y)
						  + FP(unfriendly->World.Z - World.Z) * FP(vel_z)	) / Range;
			FP runaway = (  FP(unfriendly->World.X - World.X) * FP(unfriendly->vel_x)
						  + FP(unfriendly->World.Y - World.Y) * FP(unfriendly->vel_y)
						  + FP(unfriendly->World.Z - World.Z) * FP(unfriendly->vel_z)	) / Range;

			if((chasing > 0.75) && (runaway > 0.75))
				return(TRUE);
		}

	if((formpos) && (Distance3DSquared(&FindFormpos0()->World) > FP(HALFVISIBLERANGE) * FP(HALFVISIBLERANGE)))
		return(TRUE);
	
	//maintain the globals

	SLong		oldrange;											  //DAW 01/04/99
	ANGLES		oldHI, oldPI;
	oldrange = Range;
	oldHI = HdgIntercept;
	oldPI = PitchIntercept;
	Bool bingofuel = FuelShort(10 * 60 * 100);
	Range			= oldrange;
	HdgIntercept	= oldHI;
	PitchIntercept	= oldPI;										  //DAW 01/04/99

	if (bingofuel)
		return (TRUE);												  //RDH 24/03/99

	if (AircraftDamaged())
		return (TRUE);

	bool gotammo = false;
	for (index = 0; index < 6; index++)							//RDH 31Jul98
	{
		weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET);//RDH 31Jul98
		if((weapon)	&& (weapon->LoadedStores > 0))					  //CB 12/11/99
			gotammo = true;											  //CB 12/11/99
	}																  //CB 12/11/99
 	if(!gotammo)													  //CB 12/11/99
		return(TRUE);												  //CB 12/11/99

	if(fly.leadflight)											//ARM 18Sep96
		if(fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
			return(TRUE);

	if( (ai.morale < MORALE_MEDIUM) && (Range > (2 * WEAPONSRANGE)) && (TargetOnSubjectTail(ANGLES_30Deg)) )				//JIM 07Oct96
		return (TRUE);

	switch (ai.aggressionlevel)
	{
		case	AL_TRAINING:
		case	AL_DEFENSIVE:
			return(TRUE);
		case	AL_ATTACKBOMBERSONLY:
			if (unfriendly->classtype->aerobaticfactor == AEROBATIC_HIGHEST)
		 		return(DisengageAppropriate());
		case	AL_SPLITFORCE:
		case	AL_ATTACKWEAKNESSES:
		{
			if (unfriendly->classtype->aerobaticfactor < AEROBATIC_HIGHEST)
			{
		 		return (FALSE);
			}else if (WeHaveNumbersAdvantage ())
		 	{
		 		return (FALSE);
		 	}else
		 		return(DisengageAppropriate());
		}
		case	AL_ATTACKANYTHING:
				return (FALSE);

 	}
	return (FALSE);

}
 

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShouldDisengage
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
Bool ACMAirStruc::ShouldDisengage()
{

	return(FALSE);
} 


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeHaveNumbersAdvantage
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
Bool	ACMAirStruc::WeHaveNumbersAdvantage ()
{
	SWord	unfriendlycount = 0;
	SWord	friendlycount = 1;

	if (ai.unfriendly !=NULL)
	{
		unfriendlycount = Art_Int.CountFormationSize (*ai.unfriendly);
		friendlycount = Art_Int.CountFormationSize (this);
		if (unfriendlycount > friendlycount)
		{
			return (FALSE);
		}else
		{
			return (TRUE);
		}
	}else
	{
			return (TRUE);

	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DisengageAppropriate
//Author		R. Hyde 
//Date			Thu 14 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::DisengageAppropriate ()
{
	if(		(		(SubjectOnTargetTail(ANGLES_60Deg))
				&&	(TargetOnSubjectTail(ANGLES_60Deg))
//DEADCODE CSB 24/01/00 				&&	(!SubjectFacingTarget(ANGLES_60Deg))
//DEADCODE CSB 24/01/00 				&&	(!TargetFacingSubject(ANGLES_60Deg))
				&&	(Range > (ENGAGERANGE))
			)
		||	 (Range > COMBATRANGE)
	)
		return (TRUE);
	else
		return (FALSE);
}


void	ACMAirStruc::FrightenBogie()
{
	if (		(ai. unfriendly)
			&&	(ai. unfriendly->Status.size==AIRSTRUCSIZE)
		)	
	{
    		AirStrucPtr	unfriendly = *ai. unfriendly;
		InterceptandRange (&ai.unfriendly->World);
		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	

		if (		(rndpc < RND25PC)
				&&	(SubjectOnTargetTail(ANGLES_45Deg))
				&&	(SubjectFacingTarget(ANGLES_45Deg))
		   )
		{
			if (unfriendly->ai.morale <= MORALE_MEDIUM)
			{
				if	(		(Range > WEAPONSRANGE)
						&&	(Range < ENGAGERANGE)
					)
				{
		  			unfriendly->ai.ManStep = PHASE0;
					unfriendly->ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
				}
			}else if (unfriendly->ai.morale <= MORALE_VERYGOOD)
			{
				if	(		(Range > WEAPONSRANGE)
						&&	(Range < DANGERRANGE)
					)
				{
		  			unfriendly->ai.ManStep = PHASE0;
					unfriendly->ai.manoeuvre = MANOEUVRE_SCISSORS;
				}
			}
		}
	}
}

//DEADCODE CSB 04/05/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE CSB 04/05/00 //Procedure		InformOfDanger
//DEADCODE CSB 04/05/00 //Author		R. Hyde 
//DEADCODE CSB 04/05/00 //Date			RDH 04/03/99
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Description	
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Inputs		
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Returns	
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 void	AirStruc::InformOfDanger(AirStruc* caller, AirStruc* callee)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 	//NOTE: the caller is the unfriendly of this
//DEADCODE CSB 04/05/00 	//		HdgIntercept etc is f(caller wrt this)
//DEADCODE CSB 04/05/00 	//		Standard rel hdg routines can be used
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 	RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	
//DEADCODE CSB 04/05/00 	
//DEADCODE CSB 04/05/00 	//comingin msg are for MiGs only
//DEADCODE CSB 04/05/00 	if  (		(SubjectOnTargetTail(ANGLES_20Deg))
//DEADCODE CSB 04/05/00 			&&	(rndpc > RND50PC)
//DEADCODE CSB 04/05/00 			&&	(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 			&&	SubjectFacingTarget(ANGLES_50Deg)
//DEADCODE CSB 04/05/00 		)
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COMINGINBEHIND, MSG_INITIALCOMBAT, caller, *this, callee));
//DEADCODE CSB 04/05/00 	}else if (		(SubjectFacingTarget(ANGLES_30Deg))
//DEADCODE CSB 04/05/00 				&&	(TargetFacingSubject(ANGLES_60Deg))
//DEADCODE CSB 04/05/00 				&&	(rndpc > RND50PC)
//DEADCODE CSB 04/05/00 				&&	(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 			 )
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COMINGINAHEAD, MSG_INITIALCOMBAT, caller, *this, callee));
//DEADCODE CSB 04/05/00 	}else if (SubjectFacingTarget(ANGLES_40Deg))
//DEADCODE CSB 04/05/00 	{	
//DEADCODE CSB 04/05/00 		if (caller->formpos == 0) 
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_INITALCOMBATLDR, MSG_INITIALCOMBAT, caller, *this, callee));
//DEADCODE CSB 04/05/00 		}else
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 #pragma warnmsg("CRAIG:  OLDPHRASE_MIGS is garbage!")
//DEADCODE CSB 04/05/00 //DEADCODE RJS 5/3/00 			if (		(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RJS 5/3/00 					||	(classtype->phrasename == OLDPHRASE_YAK9S)
//DEADCODE CSB 04/05/00 //DEADCODE RJS 5/3/00 			   )
//DEADCODE CSB 04/05/00 //DEADCODE RJS 5/3/00 				_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_INITALCOMBATWING, MSG_INITIALCOMBAT, caller, *this, callee));
//DEADCODE CSB 04/05/00 //DEADCODE RJS 5/3/00 			else
//DEADCODE CSB 04/05/00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_INITALCOMBATWING_MIGS, MSG_INITIALCOMBAT, caller, *this, callee));
//DEADCODE CSB 04/05/00 		}
//DEADCODE CSB 04/05/00 	}else if (		(rndpc > RND50PC)
//DEADCODE CSB 04/05/00 				&&	(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 				&&	SubjectFacingTarget(ANGLES_90Deg)
//DEADCODE CSB 04/05/00 			 )	
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COMINGINABEAM, MSG_INITIALCOMBAT, caller, *this, callee));
//DEADCODE CSB 04/05/00 	}
//DEADCODE CSB 04/05/00 }  


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		OutNumbered
//Author		R. Hyde 
//Date			RDH 04/03/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	AirStruc::OutNumbered(AirStruc* trg)
{

	if((trg->nationality == Persons2::PlayerGhostAC->nationality) && (!trg->PlayerInGroup()))
	{
		//see if the target is outnumbered
		AirStruc* caller = FindGroupLeaderInFormation();
		int count = 0;
		while (caller->fly.nextflight)
		{
			AirStruc* agg = caller;
			while (agg)
			{
				if (agg->ai.unfriendly == trg)
					count++;
				agg = (AirStruc*)agg->follower;
			}
			caller = caller->fly.nextflight;		
		}
		if (count > 2)
		{
//DEADCODE CSB 10/02/00 			ScriptTables script = SCRIPT_OUTNUMBERED;
//DEADCODE CSB 10/02/00 			if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 10/02/00 				script = OLDSCRIPT_OUTNUMBERED_MIGS;
//DEADCODE CSB 10/02/00 			_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_INITIALCOMBAT, trg, NULL, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 10/02/00 			_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_OUTNUMBEREDINFO, MSG_INITIALCOMBATINFO_DELAY, VOICE_DENTIST , trg, Manual_Pilot.ControlledAC2)); //RDH 05/07/99
			AirStrucPtr callee = FindBuddy();
			if((callee) && (trg->nationality == NAT_RAF))
			{
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OUTNUMBERED, MSG_INITIALCOMBAT, trg, NULL, callee));
			
				AirStrucPtr backup = AirStrucPtr(trg->ai.unfriendly)->ai.attacker;
				if((backup) && (backup != trg))
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OUTNUMBEREDREPLY, MSG_INITIALCOMBAT, backup, NULL, trg));
			}
			return true;
		}else
			return false;
	}else
		return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FirstTimeInCombatMsg
//Author		R. Hyde 
//Date			RDH 04/03/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::FirstTimeInCombatMsg()
{
	if((formpos != 0) || (!ai.unfriendly))
		return;

	AirStrucPtr callee = Follower();
	if(!callee)
		callee = fly.nextflight;
	if(!callee)
		return;

	AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
	if((unf->ai.unfriendly) && (unf->ai.unfriendly->Status.size == AIRSTRUCSIZE))
	{
		if(AirStrucPtr(unf->ai.unfriendly)->FindFormpos0() == this)
		{
			if(Math_Lib.rnd(2))
			{
				if((unf->World.Y > World.Y) && (unf->vel_y < -500000))
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BANDITSCOMING, MSG_INITIALCOMBAT, *this, unf, callee));
				else
					if(FP(vel_x) * FP(World.X - unf->World.X) + FP(vel_z) * FP(World.Z - unf->World.Z))
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COMINGINBEHIND, MSG_INITIALCOMBAT, *this, unf, callee));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COMINGINAHEAD, MSG_INITIALCOMBAT, *this, unf, callee));
			}
			else
			{
				ScriptTables sc;
				switch(Math_Lib.rnd(3))
				{
					case 0:		sc = SCRIPT_INITALCOMBATWING_MIGS;		break;
					case 1:		sc = SCRIPT_COMINGINABEAM;				break; 
					case 2:		sc = SCRIPT_INITALCOMBATLDR;			break;
				}			
				_Radio.TriggerMsg(MESSAGE_STRUC(sc, MSG_INITIALCOMBAT, *this, unf, callee));
			}
		}
		else
		{
			if((World.Y > unf->World.Y + FT_500) && (!Math_Lib.rnd(3)))
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_JOINFIGHT, MSG_INITIALCOMBAT, *this, unf, callee));
			else if((nationality == NAT_RAF) && (!Math_Lib.rnd(3)))
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HELPONWAY, MSG_INITIALCOMBAT, VOICE_DENTIST, *this, AirStrucPtr(unf->ai.unfriendly)));
		}
	}
	else
		if(follower)
		{
			ScriptTables sc;
			if(ai.elementtactics == WELDEDWING)
			{
				switch(Math_Lib.rnd(3))
				{
					case 0:		sc = SCRIPT_COVERME_RAND;	break;
					case 1:		sc = SCRIPT_COVERME;		break;
					case 2:		sc = SCRIPT_STAYCLOSE;		break;
				}
			}
			else 
				if(!Math_Lib.rnd(5))
					sc = SCRIPT_CALLEE_KEEPINSIGHT;
				else if(!Math_Lib.rnd(4))
					sc = SCRIPT_SPREADOUT;

			_Radio.TriggerMsg(MESSAGE_STRUC(sc, MSG_ATTACK, *this, NULL, Follower()));
		}
}

//DEADCODE CSB 10/02/00 	AirStruc*	trg = (AirStruc*)ai.unfriendly;
//DEADCODE CSB 10/02/00 	if (trg)
//DEADCODE CSB 10/02/00 	{
//DEADCODE CSB 10/02/00 		if (nationality != Persons2::PlayerGhostAC->nationality)
//DEADCODE CSB 10/02/00 		{//player's enemy entering combat
//DEADCODE CSB 10/02/00 			if (	(trg)	&&	(trg->ai.unfriendly))	// and trg knows of this //RDH 27/06/99
//DEADCODE CSB 10/02/00 			{
//DEADCODE CSB 10/02/00 				if (!formpos)				//only the group leader should provide a message
//DEADCODE CSB 10/02/00 				{
//DEADCODE CSB 10/02/00 					if (!OutNumbered(trg))
//DEADCODE CSB 10/02/00 					{
//DEADCODE CSB 10/02/00 						AirStruc* buddy = trg;
//DEADCODE CSB 10/02/00 						buddy = trg->FindABuddyWithPlayerGivenPriority();
//DEADCODE CSB 10/02/00 
//DEADCODE CSB 10/02/00 						if (TargetFacingSubject(ANGLES_80Deg))
//DEADCODE CSB 10/02/00 						{
//DEADCODE CSB 10/02/00 							if ( (buddy) &&	(!trg->AcIsPlayer()))
//DEADCODE CSB 10/02/00 							if	(		((World.Y - trg->World.Y) > FT_3000)
//DEADCODE CSB 10/02/00 									&&	(Math_Lib.rnd(RndValMAX) < RND50PC)
//DEADCODE CSB 10/02/00 									&&	(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 10/02/00 //DEADCODE RDH 10/05/99 									&&	(classtype->visible == MIG15)
//DEADCODE CSB 10/02/00 								)
//DEADCODE CSB 10/02/00 							{
//DEADCODE CSB 10/02/00 								_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_MIGSCOMING, MSG_MIGSCOMING, trg, this, buddy));
//DEADCODE CSB 10/02/00 							}else
//DEADCODE CSB 10/02/00 							{
//DEADCODE CSB 10/02/00 								if (trg->follower)
//DEADCODE CSB 10/02/00 								{
//DEADCODE CSB 10/02/00 									if	(		(ai.morale 	> 	MORALE_GOOD)
//DEADCODE CSB 10/02/00 											&& 	(ai.combatskill < SKILL_REGULAR)
//DEADCODE CSB 10/02/00 											&&	(Math_Lib.rnd(RndValMAX) < RND10PC)
//DEADCODE CSB 10/02/00 											&&	(!trg->AcIsPlayer())
//DEADCODE CSB 10/02/00 										)	
//DEADCODE CSB 10/02/00 									{
//DEADCODE CSB 10/02/00 										_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_FEELING, MSG_INITIALCOMBAT, buddy, NULL, trg));
//DEADCODE CSB 10/02/00 										_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_FEELINGREPLY, MSG_INITIALCOMBATREPLY, trg, NULL, buddy));
//DEADCODE CSB 10/02/00 									}
//DEADCODE CSB 10/02/00 								}
//DEADCODE CSB 10/02/00 								InformOfDanger(trg, buddy);
//DEADCODE CSB 10/02/00 							}
//DEADCODE CSB 10/02/00 						}else
//DEADCODE CSB 10/02/00 						{//standard bandit call
//DEADCODE CSB 10/02/00 							if ((buddy)	&&	(Range < VISIBLERANGE))		//RJS 09May99
//DEADCODE CSB 10/02/00 								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BANDIT_RELPOS, MSG_MIGSCOMING, trg, this, buddy));
//DEADCODE CSB 10/02/00 						}
//DEADCODE CSB 10/02/00 					}
//DEADCODE CSB 10/02/00 				}
//DEADCODE CSB 10/02/00 			}
//DEADCODE CSB 10/02/00 		}else
//DEADCODE CSB 10/02/00 		{
//DEADCODE CSB 10/02/00 			AirStruc* ldr = FindGroupLeader();
//DEADCODE CSB 10/02/00 
//DEADCODE CSB 10/02/00 			
//DEADCODE CSB 10/02/00 			if  (		(ldr->AcIsPlayer())
//DEADCODE CSB 10/02/00 					&&	 (Art_Int.AircraftAreClose(this,ldr))
//DEADCODE CSB 10/02/00 					&&	(!weap.FuelDumped)
//DEADCODE CSB 10/02/00 					
//DEADCODE CSB 10/02/00 				)													  //RDH 10/05/99
//DEADCODE CSB 10/02/00 				_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_JETTISONREQUEST, MSG_STATUSREPORT, this, NULL, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 10/02/00 
//DEADCODE CSB 10/02/00 			if  (		(trg->ai.unfriendly) 
//DEADCODE CSB 10/02/00 					&& (trg->ai.unfriendly->Status.size == AIRSTRUCSIZE)
//DEADCODE CSB 10/02/00 					&&	(trg->ai.unfriendly != this)				  //RDH 18/06/99
//DEADCODE CSB 10/02/00 				)
//DEADCODE CSB 10/02/00 			{
//DEADCODE CSB 10/02/00 					if  (		(!leader)
//DEADCODE CSB 10/02/00 							||	(		(follower)
//DEADCODE CSB 10/02/00 									&&	(ai.elementtactics != WELDEDWING)
//DEADCODE CSB 10/02/00 								)
//DEADCODE CSB 10/02/00 						)
//DEADCODE CSB 10/02/00 						
//DEADCODE CSB 10/02/00 					{
//DEADCODE CSB 10/02/00 							InterceptandRange (&trg->World, &trg->ai.unfriendly->World);
//DEADCODE CSB 10/02/00 							if (Art_Int.CallerOnTargetTail(this, trg, ANGLES_45Deg))
//DEADCODE CSB 10/02/00 							{
//DEADCODE CSB 10/02/00 								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ENGAGETAIL, MSG_STATUSREPORT, this, NULL, trg->ai.Unfriendly()));
//DEADCODE CSB 10/02/00 									if	(	(Math_Lib.rnd(RndValMAX) < RND25PC)	&& (Range < DANGERRANGE))	
//DEADCODE CSB 10/02/00 										_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ENGAGETAIL_REPLY, MSG_STATUSREPORT_REPLY_DELAY, trg->ai.Unfriendly(), NULL, this));
//DEADCODE CSB 10/02/00 							}else
//DEADCODE CSB 10/02/00 								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ENGAGEBANDIT, MSG_STATUSREPORT, this, NULL, trg->ai.Unfriendly()));
//DEADCODE CSB 10/02/00 							InterceptandRange (&ai.unfriendly->World);
//DEADCODE CSB 10/02/00 					}
//DEADCODE CSB 10/02/00 			}
//DEADCODE CSB 10/02/00 			if  (		(!leader)
//DEADCODE CSB 10/02/00 					&&	(follower)
//DEADCODE CSB 10/02/00 					&&	(ai.elementtactics == WELDEDWING)
//DEADCODE CSB 10/02/00 				)		
//DEADCODE CSB 10/02/00 			{
//DEADCODE CSB 10/02/00 				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COVERME_RAND, MSG_COVERME, this, trg, Follower()));
//DEADCODE CSB 10/02/00 				if (Math_Lib.rnd(RndValMAX) < RND50PC)	
//DEADCODE CSB 10/02/00 					_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_ROGER, (MsgType)(MSG_COVERMEREPLYDELAY+MSG_BLOCKCHATTER), Follower(),NULL,this));//RJS 06Jul99
//DEADCODE CSB 10/02/00 			}
//DEADCODE CSB 10/02/00 		}
//DEADCODE CSB 10/02/00 	}
//DEADCODE CSB 10/02/00 }

	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ACM
//Author		R. Hyde 
//Date			Fri 8 Mar 1996				
//
//Description	ACM movement routine
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::AirCombat()
{

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	UWord EveryXcs;	
	if((ai.simpleacm) && (AirStrucPtr(ai.unfriendly) != Persons2::PlayerGhostAC))
		EveryXcs = EVERY256cs;
	else
		EveryXcs = EVERY64cs;
	if(!(MOD.FrameCount & EveryXcs))	//This will do the following commands for each aircraft
	{								//once every n operations.
		if ( (ACMAS().TooLow())	&& (ai.manoeuvre != MANOEUVRE_LOWALT) && (ai.manoeuvre != MANOEUVRE_STRAFFE))
		{
			ai.ManStep = PHASE0;
			ai.manoeuvre = MANOEUVRE_LOWALT;
		}
		else
		{
			if((ai.unfriendly) && ((MissManCampSky().CloudLayerCover(&World) > 0) || (0 /* In a Fluffy Cloud */)) )
			{
				FP hunter = vel_x * (ai.unfriendly->World.X - World.X) + vel_y * (ai.unfriendly->World.Y - World.Y) + vel_z * (ai.unfriendly->World.Z - World.Z);
				if(hunter > 0)
				{
					ai.ManStep = PHASE0;
					ai.manoeuvre = MANOEUVRE_FLYTHROUGHCLOUD;
				}
				else	//hunted
				{
					ai.ManStep = PHASE0;
					if(Math_Lib.rnd(256) < FlyingFactor() )
					{	
						SWord rnd = Math_Lib.rnd(3);
						switch(rnd)
						{
							case 0:		ai.manoeuvre = MANOEUVRE_BREAKHIGH;		break;
							case 1:		ai.manoeuvre = MANOEUVRE_BREAKLOW;		break;
							case 2:		ai.manoeuvre = MANOEUVRE_BREAK90;		break;
						}
					}
					else
						ai.manoeuvre = MANOEUVRE_FLYTHROUGHCLOUD;
				}
			}
		}
	}
	EveryXcs = EVERY512cs;


//DeadCode CSB 25Aug00 //rdh 21/10/99
//DeadCode CSB 25Aug00 //Ever so often, if skill > regular and not on player'side
//DeadCode CSB 25Aug00 //mmm, don't know if this is right
//DeadCode CSB 25Aug00 //I thought we were attempt to put in more break calls
//DeadCode CSB 25Aug00 //but logic looks iffy, not had time to explore
//DeadCode CSB 25Aug00 	if  (			!(MOD.FrameCount & EveryXcs)
//DeadCode CSB 25Aug00 //				&&	(ai.unfriendly != Persons2::PlayerGhostAC)
//DeadCode CSB 25Aug00 				&&	(ai.combatskill >= SKILL_REGULAR)
//DeadCode CSB 25Aug00 				&&	(nationality != Persons2::PlayerGhostAC->nationality)
//DeadCode CSB 25Aug00 		)
//DeadCode CSB 25Aug00 	{
//DeadCode CSB 25Aug00 		InterceptandRange (&Persons2::PlayerGhostAC->World);
//DeadCode CSB 25Aug00 		int spotrange = METRES400 + (ai.combatskill - SKILL_REGULAR) * (METRES50/SKILL_SUBSTAGE);
//DeadCode CSB 25Aug00 		if (		(TargetOnSubjectTail(ANGLES_45Deg))
//DeadCode CSB 25Aug00 				&&	(Range < spotrange)
//DeadCode CSB 25Aug00 				&&	((HdgIntercept + ANGLES_180Deg + ANGLES_15Deg - Persons2::PlayerGhostAC->hdg) << (ANGLES_30Deg))
//DeadCode CSB 25Aug00 			)
//DeadCode CSB 25Aug00 		{
//DeadCode CSB 25Aug00 			AirStruc* buddy = FindBuddy();
//DeadCode CSB 25Aug00 			if(buddy)
//DeadCode CSB 25Aug00 			{//unfriendly is attacked by aircraft 
//DeadCode CSB 25Aug00 			   BreakCallandReaction(buddy, this, Persons2::PlayerGhostAC);
//DeadCode CSB 25Aug00 			}
//DeadCode CSB 25Aug00 
//DeadCode CSB 25Aug00 		}
//DeadCode CSB 25Aug00 	}

//#pragma warnmsg("Paul: need test for accel")
//DeadCode AMM 13Apr99 	if (currworld->vp->Accel())	//Timer_Code.accel)
//DeadCode CSB 23Oct00 	if (currworld->vp && currworld->vp->Accel())				//AMM 13Apr99
//DeadCode CSB 23Oct00 	{//if in accel, break combat if manoeuvre does not involve unfriendly
//DeadCode CSB 23Oct00 		if (ai.manoeuvre<=MANOEUVRE_TOPCOVER)
//DeadCode CSB 23Oct00 		{
//DeadCode CSB 23Oct00 			MOD.Rudder = 0;
//DeadCode CSB 23Oct00 			Art_Int.BreakOff(this);
//DeadCode CSB 23Oct00 		}
//DeadCode CSB 23Oct00 	}
//DeadCode CSB 23Oct00 	else

	if((!formpos) && ((MOD.FrameCount & 0x1fff) == 0))	//every 82 secs
	{
		FP gohomefract = 0.5;
		if((ai.unfriendly) && (AirStrucPtr(ai.unfriendly)->ai.manoeuvre == MANOEUVRE_SCREWYOUGUYSIMGOINGHOME))
			gohomefract = 0.25;
		if(GroupShouldGoHome(gohomefract))
		{
			if(follower)
   				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_STATUSREPORT, *this, NULL, Follower()));
			else if(fly.nextflight)
   				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ALLGOHOME, MSG_STATUSREPORT, *this, NULL, fly.nextflight));
			{
				SetUnfriendly(NULL);
				movecode = AUTO_FOLLOWWP;
				information = IF_OUT_POS;
				manoeuvretime = 0;
				ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
			}

			for(AirStrucPtr nf = this; nf; nf = nf->fly.nextflight)
				for(AirStrucPtr f = nf; f; f = f->Follower())
				{
					f->waypoint = f->waypoint->FindWP(WPNAME_EscDisperse);
					if((f->movecode != AUTO_COMBAT) || (!f->ai.unfriendly))
					{
						f->SetUnfriendly(NULL);
						f->movecode = AUTO_FOLLOWWP;
						f->information = IF_OUT_POS;
						f->manoeuvretime = 0;
						f->ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
					}
				}
		}
	}
	
	{
		if( 	(!ai.simpleacm)				//don't need to attempt to recover from simple model
			&&	(MOD.Spinning)
			&&	(ai.manoeuvre != MANOEUVRE_SPINOUT)
 			&&	(ai.manoeuvre != MANOEUVRE_ACCIDENTALSPINOUT)
 			&&	(ai.manoeuvre != MANOEUVRE_STALLTURN)
 			&&	(ai.manoeuvre != MANOEUVRE_SPINRECOVERY)
 			&&	(ai.manoeuvre != MANOEUVRE_LOWALT)	)
		{
			ai.ManStep = PHASE0;
			ai.manoeuvre=MANOEUVRE_SPINRECOVERY;
		}
		else if (ai.unfriendly==NULL)
		{
			if(		(ai.manoeuvre != MANOEUVRE_TOPCOVER)			//JIM 21Aug96
				&&	(ai.manoeuvre != MANOEUVRE_LOOKROUND)			//JIM 21Aug96
				&&	(ai.manoeuvre != MANOEUVRE_DIVEFORHOME)			//JIM 15Oct96
				&&	(ai.manoeuvre != MANOEUVRE_CLIMBFORHOME)		//JIM 15Oct96
				&&	(ai.manoeuvre != MANOEUVRE_STRAIGHTDIVE)		//JIM 15Oct96
				&&	(ai.manoeuvre != MANOEUVRE_GOHOME )				//JIM 15Oct96
				&&	(ai.manoeuvre != MANOEUVRE_SPINRECOVERY )				//JIM 15Oct96
				&&	(ai.manoeuvre != MANOEUVRE_STRAIGHTANDLEVEL)		//rdh 5/1/99
				&&	(ai.manoeuvre != MANOEUVRE_WELDEDWINGMAN)	  //RDH 21/02/99
				&&	(ai.manoeuvre != MANOEUVRE_REGROUP)		
				&&	(ai.manoeuvre != MANOEUVRE_DISENGAGED)	
				&&	(ai.manoeuvre != MANOEUVRE_SCREWYOUGUYSIMGOINGHOME)	
				&&	(ai.manoeuvre != MANOEUVRE_COLLISIONAVOIDANCE)		
				&&	(ai.manoeuvre != MANOEUVRE_FORCETOPCOVER)	
				&&	(ai.manoeuvre != MANOEUVRE_LOWALT)	
				&&	(ai.manoeuvre != MANOEUVRE_GAINSPEED)		)
			{
				MOD.Rudder = 0;
		  		ai.ManStep = PHASE0;
//DeadCode CSB 25Aug00 				ai.manoeuvre=MANOEUVRE_LOOKROUND;
				ai.manoeuvre = MANOEUVRE_DISENGAGED;
				ai.simpleacm = TRUE;
			}
		}
		else
			 InterceptandRange (&ai.unfriendly->World);

		if((ai.ManStep == PHASERESET) || (ai.manoeuvre == MANOEUVRE_SELECT))
		{//the first time in either ai.ManStep must be equal to PHASERESET
		 //or ai.manoeuvre = MANOEUVRE_SELECT 
//DEADCODE CSB 10/02/00 			FirstTimeInCombatMsg();
			Manual_Pilot.InitFlightModelPos(this);
			//drop bombs
			WorldStuff*	worldptr = mobileitem::currworld;
			
//DeadCode CSB 25Aug00 			AirStruc* leader = FindGroupLeader();
//DeadCode CSB 25Aug00 			if (leader != Persons2::PlayerGhostAC)	//only drop stores if leader is not player
			if(CheckForWeapon(LT_BOMB))
			{
				Trans_Obj.DropAllStores((mobileitem*)this, *worldptr);
				waypoint = waypoint->FindWP(WPNAME_EscDisperse);
			}
			ai.ManStep = PHASE0;
			ACMAS().SetACMType();
		}

		if(ai.manoeuvre == MANOEUVRE_SELECT)
		{
			if(ai.unfriendly)
			{
				AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
				if((unf->fly.numinsag) && (unf->fly.expandedsag))
				{
					SetUnfriendly(unf->fly.expandedsag->FindFreeAcInGroup());	//CSB 1Aug00
//DeadCode CSB 1Aug00 					if(unf->ai.attacker == this)
//DeadCode CSB 1Aug00 						unf->ai.attacker = NULL;
//DeadCode CSB 1Aug00 					ai.unfriendly = unf->fly.expandedsag->FindFreeAcInGroup();
				}
			}
			ACMAS().SelectNextEngageManoeuvre ();
		}
		if((movecode == AUTO_COMBAT) && (ai.manoeuvre == MANOEUVRE_SELECT))
		{
			//##
//			SelectNextEngageManoeuvre ();
			Art_Int.BreakOff(this);									//JIM 16Jul96
			MoveItem(this,*currworld);								//JIM 16Jul96
		}
		else
		{
#ifndef NDEBUG
if((ai.unfriendly) && (ai.unfriendly->Status.deadtime) && !_DPlay.Implemented)
	INT3;
#endif

// Block ManualACM for dudes that have not had ai.simpleacm set yet!
			if (	(classtype->visible != SPIT)				//RJS 14Nov00
				&&	(classtype->visible != HURR)
				&&	(classtype->visible != ME109)
				&&	(classtype->visible != ME110)	)
				ai.simpleacm = TRUE;

			if (ai.simpleacm)
				ACMAS().SimpleACM ();
			else
//DeadCode CSB 11Sep00 				ACMAS().SimpleACM ();
				ACMAS().ManualACM ();
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SimpleACM
//Author		R. Hyde 
//Date			Fri 11 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SimpleACM ()
{
//DeadCode CSB 28/04/99		PrintString(0, 22, "SimpleACM ");

//DEADCODE CSB 14/01/00 /* TEST CODE CSB 18/06/99 */	if (Key_Tests.KeyPress3d (RPM_50))	//CSB 18/3/99	
//DEADCODE CSB 14/01/00 /* TEST CODE CSB 18/06/99 */	{
//DEADCODE CSB 14/01/00 /* TEST CODE CSB 18/06/99 */		ai.manoeuvre = MANOEUVRE_BAILOUT;	//CSB 18/03/99	
//DEADCODE CSB 14/01/00 /* TEST CODE CSB 18/06/99 */		ai.ManStep   = 0;
//DEADCODE CSB 14/01/00 /* TEST CODE CSB 18/06/99 */		SetManoeuvreTime (1500);
//DEADCODE CSB 14/01/00 /* TEST CODE CSB 18/06/99 */	}
	
	SWord oldpitch = pitch;

	switch (ai.manoeuvre)
		{
			case MANOEUVRE_LOOKROUND:
			{						  
 				SimpleLookAround ();		  
				break;				  
			}			
			case MANOEUVRE_WELDEDWINGMAN:										//RDH 03Mar98
			{
				SimpleWeldedWingMan();
				break;
			}
			case MANOEUVRE_BAILOUT:										//RDH 03Mar98
			{
				SimpleBailOut();
				break;
			}
			case MANOEUVRE_TOPCOVER:
			{						  
				SimpleTopCover ();		  
				break;				  
			}			
			case MANOEUVRE_FORCETOPCOVER:
			{						  
				SimpleForceTopCover ();		  
				break;				  
			}			
			case MANOEUVRE_LINEABREAST:										//RDH 27Mar98
			{
 				SimpleLineAbreast();
				break;
			}
			case MANOEUVRE_PINCER:											//RDH 27Mar98
			{
 				SimplePincer();
				break;
			}
			case MANOEUVRE_MULTIWAVE:										//RDH 27Mar98
			{
 				SimpleMultiWave();
				break;
			}
			case MANOEUVRE_DIVEANDZOOM:
			{
 				SimpleDiveAndZoom();
				break;
			}
			case MANOEUVRE_LEADPURSUIT:
			{
				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_LAGPURSUIT:
			{
				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_SPLITMANOEUVRE:									//RDH 27Mar98
			{
				SimpleSplitManoeuvre();
				break;
			}
			case MANOEUVRE_HEADON:
			{
				SimpleHeadOn();
				break;
			}
			case MANOEUVRE_LINEASTERN:										//RDH 27Mar98
			{
				SimpleLineAstern();
				break;
			}
			case MANOEUVRE_VICATTACK:
			{
				SimpleVicAttack();
				break;
			}
			case MANOEUVRE_BARRELROLLATTACK:							
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_SCISSORS:							
			{													
				SimpleScissors ();									
				break;											
			}													
			case MANOEUVRE_MILDSCISSORS:						
			{													
				SimpleMildScissors ();								
				break;											
			}													
			case MANOEUVRE_SPLITS:								
			{													
				SimpleSplitS ();										
				break;											
			}													
			case MANOEUVRE_ZOOMANDDROP:							
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_STRAIGHTANDLEVEL :					
			{													
				SimpleStraightandLevel ( );							
				break;											
			}													
			case MANOEUVRE_SPINOUT :							
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_DIVEFORHOME :						
			{													
				SimpleDiveforHome ( );								
				break;											
			}													
			case MANOEUVRE_GOHOME :								
			{													
				SimpleGoHome ( );										
				break;											
			}													
			case MANOEUVRE_MAKEFORFRIENDLY :							
			{													
				SimpleRegroup();
				break;											
			}													
			case MANOEUVRE_MOVEAWAY :							
			{													
				SimpleMoveAway ( );									
				break;											
			}													
			case MANOEUVRE_ACCIDENTALSPINOUT :					
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_VERTICALLOOP :						
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_IMMELMANNTURN :						
			{													
				SimpleImmelmannTurn();
//DeadCode CSB 4Sep00 				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_IMMELMANN :						
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_STAYWITHPREY :						
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_CLIMBFORHOME :						
			{													
				SimpleClimbforHome ( );								
				break;											
			}													
			case MANOEUVRE_STRAIGHTDIVE:						
			{													
				SimpleStraightDive ( );								
				break;											
			}													
			case MANOEUVRE_STANDONTAIL:							
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_SHOOTTOFRIGHTEN:						
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_SHOOTTOOEARLY:						
			{													
				SimpleTurningFight();
				break;											
			}													
			case MANOEUVRE_GAINHEIGHT:							
			{													
	 			SimpleGainHeight ( );									
				break;											
			}													
			case MANOEUVRE_LAGROLL:											//RDH 30Mar98
			{
				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_EXTENSION:								//RDH 30Mar98
			{
				SimpleMoveAway ( );									  //RDH 16/05/99

				break;
			}
			case MANOEUVRE_DIVINGSPIN:
			{
				SimpleDivingSpin();
//DeadCode CSB 4Sep00 				SimpleSplitS();
				break;
			}
			case MANOEUVRE_REVERSETURN:										//RDH 30Mar98
			{
				SimpleBreak90();
//DeadCode CSB 8Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_SELFASBAIT:										//RDH 30Mar98
			{
				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_JINK:												//RDH 30Mar98
			{
				SimpleScissors();
//DeadCode CSB 8Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_BREAKTURN:										//RDH 30Mar98
			{
				SimpleBreak90();
//DeadCode CSB 8Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_LAZYTURN:											//RDH 30Mar98
			{
				SimpleMildScissors();
//DeadCode CSB 8Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_BREAKLOW:											//RDH 30Mar98
			{
				SimpleBreakLow();
//DeadCode CSB 4Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_BREAKHIGH:										//RDH 30Mar98
			{
				SimpleBreakHigh();
//DeadCode CSB 4Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_BREAK90:											//RDH 30Mar98
			{
				SimpleBreak90();
//DeadCode CSB 4Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_HIGBARRELROLL:									//RDH 30Mar98
			{
				SimpleHiGBarrelRoll();
				break;
			}
			case MANOEUVRE_PANICTURN:									//RDH 30Mar98
			{
				SimpleBreak90();
//DeadCode CSB 8Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_UNBALANCEDFLIGHT:									//RDH 30Mar98
			{
				SimpleScissors();
//DeadCode CSB 8Sep00 				SimpleTurningFight();
				break;
			}
			case MANOEUVRE_LOWALT:									//RDH 30Mar98
			{
				SimpleLowAlt();
				break;
			}
			case MANOEUVRE_TURNTOHDGANDPITCH:								//RDH 30Mar98
			{
				SimpleTurnToHdgAndPitch();
				break;
			}
			case MANOEUVRE_TURNINGFIGHT:										//RDH 30Mar98
			{
				SimpleTurningFight();
				break;
			}
//DeadCode CSB 7Sep00 			case MANOEUVRE_HIGHYOYO:											//RDH 30Mar98
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00 				SimpleTurningFight();
//DeadCode CSB 7Sep00 				break;
//DeadCode CSB 7Sep00 			}
			case MANOEUVRE_ZOOM:											//RDH 30Mar98
			{
 				SimpleZoom();
				break;
			}
//DeadCode CSB 7Sep00 			case MANOEUVRE_LOWYOYO:											//RDH 30Mar98
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00 				SimpleTurningFight();
//DeadCode CSB 7Sep00 				break;
//DeadCode CSB 7Sep00 			}
			case MANOEUVRE_INTERCEPTHIGH:									//RDH 30Mar98
			{
				SimpleInterceptHigh();
//DeadCode CSB 4Sep00 				TurningFight();
				break;
			}
			case MANOEUVRE_INTERCEPTLOW:									//RDH 30Mar98
			{
				SimpleInterceptLow();
//DeadCode CSB 4Sep00 				TurningFight();
				break;
			}
			case MANOEUVRE_GAINSPEED:						
			{													
				SimpleGainSpeed ( );								
				break;											
			}													
			case MANOEUVRE_HEADONATTACK:
			{													
				SimpleHeadOnAttack();	
				break;
			}
			case MANOEUVRE_LUFBERRY:						
			{													
				SimpleLufberry();	
				break;
			}
			case MANOEUVRE_STEEPDIVE:
			{													
				SimpleSteepDive();
				break;
			}
			case MANOEUVRE_UPANDUNDER:
			{													
				SimpleUpAndUnder();
				break;
			}
			case MANOEUVRE_STALLTURN:
			{													
				SimpleStallTurn();
				break;
			}
			case MANOEUVRE_SLASHINGATTACK:
			{													
				SimpleSlashingAttack();
				break;
			}
			case MANOEUVRE_CLIMBTURN:
			{													
				SimpleClimbTurn();
				break;
			}
			case MANOEUVRE_ROLL360:						
			{													
				SimpleRoll360();
				break;
			}
			case MANOEUVRE_STRAFFE:						
			{													
				SimpleStraffe();
				break;
			}													
			case MANOEUVRE_PEELOFF:
			{													
				SimplePeelOff();
				break;
			}													
			case MANOEUVRE_FLYTHROUGHCLOUD:						
			{													
				SimpleFlyThroughCloud();
				break;
			}													
			case MANOEUVRE_REGROUP:						
			{													
				SimpleRegroup();
				break;
			}													
			case MANOEUVRE_DISENGAGED:						
			{													
				SimpleDisengaged();
				break;
			}													
			case MANOEUVRE_SCREWYOUGUYSIMGOINGHOME:						
			{													
				SimpleImGoingHome();
				break;
			}													
			case MANOEUVRE_SPINRECOVERY:						
			{													
				SimpleTurningFight();
				break;											
			}	
			case MANOEUVRE_COLLISIONAVOIDANCE:						
			{													
				SimpleCollisionAvoidance();
				break;											
			}	
			case MANOEUVRE_COLLIDE:						
			{													
//DeadCode CSB 12Oct00 				ai.manoeuvre = MANOEUVRE_SELECT;
				SimpleCollide();
				break;											
			}	
		}

	hdg += (Angles) CalcHdg ();

	SWord oldthrust = fly.thrustpercent;
	if((classtype->visible == SPIT) || (classtype->visible == HURR) || (classtype->visible == DEF))
	{		//Engine cuts out under negative G
		FP pitchrate = FP(SWord(pitch) - oldpitch);
		FP upright = SWord(roll);
		if((upright > -16384) && (upright < 16384))
			upright = 1;
		else
			upright = -1;
		if(upright * pitchrate < 0)
			fly.thrustpercent = 0;
	}

	SimpleCalcVel (); 
	CalcXYZVel();
	NewPosition ();
	SetFlightParams ();
	fly.thrustpercent = oldthrust;

	if((vel_ < classtype->minvel) && (ai.manoeuvre != MANOEUVRE_SPINRECOVERY) && (ai.manoeuvre != MANOEUVRE_STALLTURN))
	{
		if(ai.manoeuvre != MANOEUVRE_GAINSPEED)
			ai.ManStep = 0;
		ai.manoeuvre = MANOEUVRE_GAINSPEED;
	}

	if(vel_ < 100000)
	{
		if(ai.manoeuvre != MANOEUVRE_STEEPDIVE)
			ai.ManStep = 0;
		ai.manoeuvre = MANOEUVRE_STEEPDIVE;
	}


	if((ai.unfriendly!=NULL) && (ai.manoeuvre != MANOEUVRE_WELDEDWINGMAN))
		AutoShoot(TRUE);

//DeadCode CSB 1Sep00 	weap.ShootDelay = weap.ShootDelay-Timer_Code.FRAMETIME;
//DeadCode CSB 1Sep00 	if (weap.ShootDelay < 0)
//DeadCode CSB 1Sep00 		weap.ShootDelay = 0;

//DeadCode CSB 20/01/99		#ifdef DISPLAY_MONO_DATA
//DeadCode CSB 20/01/99	//test print out		
//DeadCode CSB 20/01/99			UWord y = 0;
//DeadCode CSB 20/01/99			if (ai.unfriendly)
//DeadCode CSB 20/01/99				InterceptandRange (&ai.unfriendly->World);
//DeadCode CSB 20/01/99			else
//DeadCode CSB 20/01/99			{
//DeadCode CSB 20/01/99				HdgIntercept=ANGLES_0Deg;
//DeadCode CSB 20/01/99				Range=-1;
//DeadCode CSB 20/01/99	
//DeadCode CSB 20/01/99			}
//DeadCode CSB 20/01/99			if (classtype->visible == MIG15)
//DeadCode CSB 20/01/99					y = 4;
//DeadCode CSB 20/01/99			char strg [32];
//DeadCode CSB 20/01/99	 		SWord HI = (SWord) (HdgIntercept - hdg);
//DeadCode CSB 20/01/99	 		for (UWord n=0; n<32; n++) strg[n] = 0;
//DeadCode CSB 20/01/99	 		sprintf (strg, "DHdgIntercept  %d ",HI);
//DeadCode CSB 20/01/99	 		if (strg[31] == 0)
//DeadCode CSB 20/01/99	 			Mono_Text.PrintAt (40,y,(UByte*)strg);
//DeadCode CSB 20/01/99	 
//DeadCode CSB 20/01/99	 		for (n=0; n<32; n++) strg[n] = 0;
//DeadCode CSB 20/01/99	 		sprintf (strg, "Range,m  %d ",Range/100);
//DeadCode CSB 20/01/99	 		if (strg[31] == 0)
//DeadCode CSB 20/01/99	 			Mono_Text.PrintAt (40,y+1,(UByte*)strg);
//DeadCode CSB 20/01/99	
//DeadCode CSB 20/01/99	//		for (n=0; n<32; n++) strg[n] = 0;
//DeadCode CSB 20/01/99	//		sprintf (strg, "ReqRoll  %d ",reqroll);
//DeadCode CSB 20/01/99	//		if (strg[31] == 0)
//DeadCode CSB 20/01/99	//			Mono_Text.PrintAt (40,y+2,(UByte*)strg);
//DeadCode CSB 20/01/99	//
//DeadCode CSB 20/01/99	
//DeadCode CSB 20/01/99	#endif
//DeadCode CSB 20/01/99	//test print out end

//DeadCode CSB 2Oct00 	if (ai.manoeuvre == MANOEUVRE_SELECT)
//DeadCode CSB 2Oct00 	{
//DeadCode CSB 2Oct00 		if (ai.unfriendly==NULL)
//DeadCode CSB 2Oct00 		{
//DeadCode CSB 2Oct00 			if(	(ai.manoeuvre != MANOEUVRE_TOPCOVER)			//JIM 21Aug96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_LOOKROUND)			//JIM 21Aug96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_DIVEFORHOME)			//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_CLIMBFORHOME)		//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_STRAIGHTDIVE)		//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_GOHOME )				//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_SPINRECOVERY )				//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_REGROUP)				//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_DISENGAGED )				//JIM 15Oct96
//DeadCode CSB 2Oct00 				)
//DeadCode CSB 2Oct00 			{
//DeadCode CSB 2Oct00 		  		ai.ManStep = PHASE0;
//DeadCode CSB 2Oct00 //DeadCode CSB 25Aug00 				ai.manoeuvre=MANOEUVRE_LOOKROUND;
//DeadCode CSB 2Oct00 				ai.manoeuvre = MANOEUVRE_DISENGAGED;
//DeadCode CSB 2Oct00 				ai.simpleacm = TRUE;
//DeadCode CSB 2Oct00 			}
//DeadCode CSB 2Oct00 		}else
//DeadCode CSB 2Oct00 		{
//DeadCode CSB 2Oct00 			InterceptandRange (&ai.unfriendly->World);
//DeadCode CSB 2Oct00 			SelectNextEngageManoeuvre ();
//DeadCode CSB 2Oct00 		  		ai.ManStep = PHASE0;
//DeadCode CSB 2Oct00 //DEADCODE RDH 16/05/99 			if (ai.manoeuvre != MANOEUVRE_SELECT)
//DeadCode CSB 2Oct00 //DEADCODE RDH 16/05/99 				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						
//DeadCode CSB 2Oct00 		}
//DeadCode CSB 2Oct00 	}
//DeadCode CSB 2Oct00 	if((ai.manoeuvre == MANOEUVRE_SELECT) && (movecode == AUTO_COMBAT))
//DeadCode CSB 2Oct00 	{
//DeadCode CSB 2Oct00 		ai.manoeuvre = MANOEUVRE_DISENGAGED;
//DeadCode CSB 2Oct00 		ai.simpleacm = TRUE;
//DeadCode CSB 2Oct00 		ai.ManStep = 0;
//DeadCode CSB 2Oct00 		SetManoeuvreTime(0);
//DeadCode CSB 2Oct00 		SetUnfriendly(NULL);
//DeadCode CSB 2Oct00 	}
//DeadCode CSB 2Oct00 //DeadCode CSB 30Aug00 		movecode=AUTO_FOLLOWWP;
//DeadCode CSB 2Oct00 //DeadCode CSB 30Aug00 		information = IF_OUT_POS;					//CSB 22Aug00
//DeadCode CSB 2Oct00 //DeadCode CSB 30Aug00 		manoeuvretime = 0;
//DeadCode CSB 2Oct00 //DeadCode CSB 30Aug00 
//DeadCode CSB 2Oct00 //DeadCode CSB 30Aug00 		if((!formpos) && (!PlayerInGroup()) && (!Math_Lib.rnd(20)))
//DeadCode CSB 2Oct00 //DeadCode CSB 30Aug00 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_RETURNING, MSG_STATUS, *this, ai.homebase, Persons2::PlayerGhostAC));
//DeadCode CSB 2Oct00 //DeadCode CSB 5Sep00 	}
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 //temp	if (ai.unfriendly!=NULL)
//DeadCode CSB 2Oct00 //	{
//DeadCode CSB 2Oct00 //		AutoShoot(FALSE);
//DeadCode CSB 2Oct00 //DeadCode RDH 25Oct96 		if ((Range <METRES70) && (fly.thrustpercent == 100))
//DeadCode CSB 2Oct00 //DeadCode RDH 25Oct96  			MoveToThrust (0);									//RDH 01Oct96
//DeadCode CSB 2Oct00 //DeadCode RDH 25Oct96 		else
//DeadCode CSB 2Oct00 //DeadCode RDH 25Oct96  			MoveToThrust (100);									//RDH 01Oct96
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 //	}
//DeadCode CSB 2Oct00 //DeadCode CSB 06/04/99	#ifndef ACM_PILOT_DATA
//DeadCode CSB 2Oct00 //DeadCode CSB 06/04/99		#define ACM_PILOT_DATA
//DeadCode CSB 2Oct00 //DeadCode CSB 06/04/99	#endif
//DeadCode CSB 2Oct00 #ifdef ACM_PILOT_DATA
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 	PrintVar(0,  10, "T Pitch %.1f ", (FP)( (PitchIntercept - pitch) / 182.04) );
//DeadCode CSB 2Oct00 	PrintVar(0,  11, "T Headg %.1f ", (FP)( (HdgIntercept - hdg)  / 182.04) );
//DeadCode CSB 2Oct00 	PrintVar(0,  12, "T Range %.0f ", (FP)(Range / 100) );
//DeadCode CSB 2Oct00 	PrintVar(0,  13, "D Headg %.1f ", (FP)(ai.desiredhdg / 182.04) );
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 	PrintVar(20,   9, "C Vel   %.1f ", (FP)( (vel) / 10) );
//DeadCode CSB 2Oct00 	PrintVar(20,  10, "C Pitch %.1f ", (FP)( (pitch) / 182.04) );
//DeadCode CSB 2Oct00 	PrintVar(20,  11, "C Roll  %.1f ", (FP)( (roll) / 182.04) );
//DeadCode CSB 2Oct00 	PrintVar(20,  12, "C Headg %.1f ", (FP)( (hdg) / 182.04) );
//DeadCode CSB 2Oct00 	PrintVar(20,  13, "C Alt   %.0f ", (FP)( (World.Y) / 100.0) );
//DeadCode CSB 2Oct00 	PrintVar(20,  14, "C Thrst %.0f ", (FP)( (fly.thrustpercent) ) );
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 	
//DeadCode CSB 2Oct00 	switch (ai.manoeuvre)
//DeadCode CSB 2Oct00 	{
//DeadCode CSB 2Oct00 		case MANOEUVRE_SELECT:						{ PrintString(0,  24, "MANOEUVRE_SELECT						");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LOOKROUND:					{ PrintString(0,  24, "MANOEUVRE_LOOKROUND					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_WELDEDWINGMAN:				{ PrintString(0,  24, "MANOEUVRE_WELDEDWINGMAN				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_BAILOUT:						{ PrintString(0,  24, "MANOEUVRE_BAILOUT					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_TOPCOVER:					{ PrintString(0,  24, "MANOEUVRE_TOPCOVER					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LINEABREAST:					{ PrintString(0,  24, "MANOEUVRE_LINEABREAST				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SCATTER:						{ PrintString(0,  24, "MANOEUVRE_SCATTER					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_PINCER:						{ PrintString(0,  24, "MANOEUVRE_PINCER						");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_MULTIWAVE:					{ PrintString(0,  24, "MANOEUVRE_MULTIWAVE					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_DIVEANDZOOM:					{ PrintString(0,  24, "MANOEUVRE_DIVEANDZOOM				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LEADPURSUIT:					{ PrintString(0,  24, "MANOEUVRE_LEADPURSUIT				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LAGPURSUIT:					{ PrintString(0,  24, "MANOEUVRE_LAGPURSUIT					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_CIRCUMVENT:					{ PrintString(0,  24, "MANOEUVRE_CIRCUMVENT					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_ROUNDABOUT:					{ PrintString(0,  24, "MANOEUVRE_ROUNDABOUT					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SPLITMANOEUVRE:				{ PrintString(0,  24, "MANOEUVRE_SPLITMANOEUVRE				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_HEADON:						{ PrintString(0,  24, "MANOEUVRE_HEADON						");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LINEASTERN:					{ PrintString(0,  24, "MANOEUVRE_LINEASTERN					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_BARRELROLLATTACK:			{ PrintString(0,  24, "MANOEUVRE_BARRELROLLATTACK			");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SCISSORS:					{ PrintString(0,  24, "MANOEUVRE_SCISSORS					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_MILDSCISSORS:				{ PrintString(0,  24, "MANOEUVRE_MILDSCISSORS				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_TURNINGFIGHT:				{ PrintString(0,  24, "MANOEUVRE_TURNINGFIGHT				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SPLITS:						{ PrintString(0,  24, "MANOEUVRE_SPLITS						");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_ZOOMANDDROP:					{ PrintString(0,  24, "MANOEUVRE_ZOOMANDDROP				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_STRAIGHTANDLEVEL:			{ PrintString(0,  24, "MANOEUVRE_STRAIGHTANDLEVEL			");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SPINOUT:						{ PrintString(0,  24, "MANOEUVRE_SPINOUT					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_DIVEFORHOME:					{ PrintString(0,  24, "MANOEUVRE_DIVEFORHOME				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_GOHOME:						{ PrintString(0,  24, "MANOEUVRE_GOHOME						");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_MAKEFORFRIENDLY:				{ PrintString(0,  24, "MANOEUVRE_MAKEFORFRIENDLY			");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_MOVEAWAY:					{ PrintString(0,  24, "MANOEUVRE_MOVEAWAY					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_ACCIDENTALSPINOUT:			{ PrintString(0,  24, "MANOEUVRE_ACCIDENTALSPINOUT			");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_VERTICALLOOP:				{ PrintString(0,  24, "MANOEUVRE_VERTICALLOOP				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_IMMELMANNTURN:				{ PrintString(0,  24, "MANOEUVRE_IMMELMANNTURN				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_HEADONOFFSET:				{ PrintString(0,  24, "MANOEUVRE_HEADONOFFSET				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_IMMELMANN:					{ PrintString(0,  24, "MANOEUVRE_IMMELMANN					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_STAYWITHPREY:				{ PrintString(0,  24, "MANOEUVRE_STAYWITHPREY				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_CLIMBFORHOME:				{ PrintString(0,  24, "MANOEUVRE_CLIMBFORHOME				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_STRAIGHTDIVE:				{ PrintString(0,  24, "MANOEUVRE_STRAIGHTDIVE				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_STANDONTAIL:					{ PrintString(0,  24, "MANOEUVRE_STANDONTAIL				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SHOOTTOFRIGHTEN:				{ PrintString(0,  24, "MANOEUVRE_SHOOTTOFRIGHTEN			");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SHOOTTOOEARLY:				{ PrintString(0,  24, "MANOEUVRE_SHOOTTOOEARLY				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_GAINHEIGHT:					{ PrintString(0,  24, "MANOEUVRE_GAINHEIGHT					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LAGROLL:						{ PrintString(0,  24, "MANOEUVRE_LAGROLL					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_EXTENSION:					{ PrintString(0,  24, "MANOEUVRE_EXTENSION					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_DIVINGSPIN:					{ PrintString(0,  24, "MANOEUVRE_DIVINGSPIN					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_REVERSETURN:					{ PrintString(0,  24, "MANOEUVRE_REVERSETURN				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SELFASBAIT:					{ PrintString(0,  24, "MANOEUVRE_SELFASBAIT					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_JINK:						{ PrintString(0,  24, "MANOEUVRE_JINK						");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_BREAKTURN:					{ PrintString(0,  24, "MANOEUVRE_BREAKTURN					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LAZYTURN:					{ PrintString(0,  24, "MANOEUVRE_LAZYTURN					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_BREAK180:					{ PrintString(0,  24, "MANOEUVRE_BREAK180					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_BREAKLOW:					{ PrintString(0,  24, "MANOEUVRE_BREAKLOW					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_BREAKHIGH:					{ PrintString(0,  24, "MANOEUVRE_BREAKHIGH					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_BREAK90:						{ PrintString(0,  24, "MANOEUVRE_BREAK90					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_HIGBARRELROLL:				{ PrintString(0,  24, "MANOEUVRE_HIGBARRELROLL				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_PANICTURN:					{ PrintString(0,  24, "MANOEUVRE_PANICTURN					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_UNBALANCEDFLIGHT:			{ PrintString(0,  24, "MANOEUVRE_UNBALANCEDFLIGHT			");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LOWALT:						{ PrintString(0,  24, "MANOEUVRE_LOWALT						");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SNAPSHOT:					{ PrintString(0,  24, "MANOEUVRE_SNAPSHOT					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_STAYONTAIL:					{ PrintString(0,  24, "MANOEUVRE_STAYONTAIL					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_TURNTOHDGANDPITCH:			{ PrintString(0,  24, "MANOEUVRE_TURNTOHDGANDPITCH			");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_HOTSIDELAGPURSUITFIGHT:		{ PrintString(0,  24, "MANOEUVRE_HOTSIDELAGPURSUITFIGHT		");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SANDWICHMANOEUVRES:			{ PrintString(0,  24, "MANOEUVRE_SANDWICHMANOEUVRES			");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SUSTAINEDTURN:				{ PrintString(0,  24, "MANOEUVRE_SUSTAINEDTURN				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_HIGHYOYO:					{ PrintString(0,  24, "MANOEUVRE_HIGHYOYO					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_ZOOM:						{ PrintString(0,  24, "MANOEUVRE_ZOOM						");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_LOWYOYO:						{ PrintString(0,  24, "MANOEUVRE_LOWYOYO					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_INTERCEPTHIGH:				{ PrintString(0,  24, "MANOEUVRE_INTERCEPTHIGH				");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED:	{ PrintString(0,  24, "MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED	");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_GAINSPEED:					{ PrintString(0,  24, "MANOEUVRE_GAINSPEED					");    break; }
//DeadCode CSB 2Oct00 		case MANOEUVRE_SPINRECOVERY:				{ PrintString(0,  24, "MANOEUVRE_SPINRECOVERY				");    break; }
//DeadCode CSB 2Oct00 	}
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 	PrintVar(30, 24, "Phase %.0f ", (FP)ai.ManStep);
//DeadCode CSB 2Oct00 	PrintVar(40, 24, "Time %.0f ", (FP)manoeuvretime);
//DeadCode CSB 2Oct00 #endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NewDeadPosition
//Author		Robert Slater
//Date			Mon 23 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::NewDeadPosition()
{
	SLong	deltax,deltay,deltaz;	
	SLong	timedelta = Timer_Code.FRAMETIME; //CSB 08/11/99
										
	deltax =  (vel_x * timedelta) / 10000;	 //CSB 08/11/99
	deltay =  (vel_y * timedelta) / 10000;	 //CSB 08/11/99
	deltaz =  (vel_z * timedelta) / 10000;	 //CSB 08/11/99
			  								
	CalcNewPos (deltax,deltay,deltaz);		
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubjectClosureGreaterThan
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description  
// 			
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong ACMAirStruc::SubjectClosure()
{
	SLong sx, sy, sz, svx, svy, svz;
	SLong tx, ty, tz, tvx, tvy, tvz;

	sx = World.X;
	sy = World.Y;
	sz = World.Z;
	svx = vel_x;
	svy = vel_y;
	svz = vel_z;

	tx = ai.unfriendly->World.X;
	ty = ai.unfriendly->World.Y;
	tz = ai.unfriendly->World.Z;
	tvx = AirStrucPtr(ai.unfriendly)->vel_x;
	tvy = AirStrucPtr(ai.unfriendly)->vel_y;
	tvz = AirStrucPtr(ai.unfriendly)->vel_z;
	Range = Distance3D(&World, &ai.unfriendly->World);

	SLong closure = ((tx - sx) * (svx - tvx) + (ty - sy) * (svy - tvy) +  (tz - sz) * (svz - tvz)) / Range;
	return(closure);
//DEADCODE CSB 08/11/99 	ANGLES	brg;
//DEADCODE CSB 08/11/99 	SWord	sinbearing,cosbearing;
//DEADCODE CSB 08/11/99 	AirStrucPtr	unfriendly = *ai. unfriendly;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	brg = HdgIntercept - hdg;
//DEADCODE CSB 08/11/99 	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
//DEADCODE CSB 08/11/99 	if (cosbearing < 0)
//DEADCODE CSB 08/11/99 		return(FALSE);
//DEADCODE CSB 08/11/99 	//cal the subject velocity along the hdg intercept (ie horizontal plane)
//DEADCODE CSB 08/11/99 	SLong vel_s_hi_hori = velhori * cosbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 //	brg = PitchIntercept - fly.cpitch;
//DEADCODE CSB 08/11/99 	Math_Lib.high_sin_cos(PitchIntercept,sinbearing,cosbearing);
//DEADCODE CSB 08/11/99 	//cal the subject hori velocity along the pitch intercept
//DEADCODE CSB 08/11/99 	SLong vel_s_pi_hori = vel_s_hi_hori * cosbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 	
//DEADCODE CSB 08/11/99 	
//DEADCODE CSB 08/11/99 	SLong vel_s_pi_vert = vely * sinbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	brg = HdgIntercept - unfriendly->hdg;
//DEADCODE CSB 08/11/99 	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
//DEADCODE CSB 08/11/99 	SLong vel_t_hi_hori = unfriendly->velhori * cosbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 //	brg = PitchIntercept - unfriendly->fly.cpitch;
//DEADCODE CSB 08/11/99 	Math_Lib.high_sin_cos(PitchIntercept,sinbearing,cosbearing);
//DEADCODE CSB 08/11/99 	//cal the subject hori velocity along the pitch intercept
//DEADCODE CSB 08/11/99 	SLong vel_t_pi_hori = vel_t_hi_hori * cosbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 	
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	SLong vel_t_pi_vert = unfriendly->vely * sinbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 	
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	SLong	closure = (vel_s_pi_hori + vel_s_pi_vert) - (vel_t_pi_hori + vel_t_pi_vert); 
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	return (closure);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubjectClosureGreaterThan
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description  
// 			
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ACMAirStruc::SubjectClosureGreaterThan(SLong dvel)
{
	SLong	closure;
	

	closure = SubjectClosure();
	if (closure > dvel)
		return(TRUE);
	else
		return(FALSE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubjectLeadingTarget
//Author		R. Hyde 
//Date			Tue 10 Mar 1998
//
//Description	This is a simple method. A better one may be needed
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::SubjectLeadingTarget()
{
	AirStrucPtr	unfriendly = *ai. unfriendly;
	SWord beta = unfriendly->hdg - HdgIntercept;
	SWord alpha = hdg - HdgIntercept;
	if (beta > 0)
		if (alpha > 0)
			return (TRUE);
		else
			return (FALSE);
	else
		if (alpha < 0)
			return (TRUE);
		else
			return (FALSE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TargetClosureGreaterThan
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description  
// 			
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool ACMAirStruc::TargetClosureGreaterThan(SLong dvel)
{
	SLong sx, sy, sz, svx, svy, svz;
	SLong tx, ty, tz, tvx, tvy, tvz;

	sx = World.X;
	sy = World.Y;
	sz = World.Z;
	svx = vel_x;
	svy = vel_y;
	svz = vel_z;

	tx = ai.unfriendly->World.X;
	ty = ai.unfriendly->World.Y;
	tz = ai.unfriendly->World.Z;
	tvx = AirStrucPtr(ai.unfriendly)->vel_x;
	tvy = AirStrucPtr(ai.unfriendly)->vel_y;
	tvz = AirStrucPtr(ai.unfriendly)->vel_z;
	
	SLong closure = ((sx - tx) * (tvx - svx) + (sy - ty) * (tvy - svy) +  (sz - tz) * (tvz - svz)) / Range;

//DEADCODE CSB 08/11/99 	SLong	closure;
//DEADCODE CSB 08/11/99 	ANGLES	brg;
//DEADCODE CSB 08/11/99 	SWord	sinbearing,cosbearing;
//DEADCODE CSB 08/11/99 	AirStrucPtr	unfriendly = *ai. unfriendly;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	brg = ANGLES_180Deg + HdgIntercept - hdg;
//DEADCODE CSB 08/11/99 	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
//DEADCODE CSB 08/11/99 	if (cosbearing < 0)
//DEADCODE CSB 08/11/99 		return(FALSE);
//DEADCODE CSB 08/11/99 	//cal the subject velocity along the hdg intercept (ie horizontal plane)
//DEADCODE CSB 08/11/99 	SLong vel_s_hi_hori = velhori * cosbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	brg = (- PitchIntercept) - fly.cpitch;
//DEADCODE CSB 08/11/99 	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
//DEADCODE CSB 08/11/99 	//cal the subject hori velocity along the pitch intercept
//DEADCODE CSB 08/11/99 	SLong vel_s_pi_hori = vel_s_hi_hori * cosbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 	
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	SLong vel_s_pi_vert = vely * sinbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	brg = ANGLES_180Deg + HdgIntercept - unfriendly->hdg;
//DEADCODE CSB 08/11/99 	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
//DEADCODE CSB 08/11/99 	SLong vel_t_hi_hori = unfriendly->velhori * cosbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	brg = ( - PitchIntercept) - unfriendly->fly.cpitch;
//DEADCODE CSB 08/11/99 	Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);
//DEADCODE CSB 08/11/99 	//cal the subject hori velocity along the pitch intercept
//DEADCODE CSB 08/11/99 	SLong vel_t_pi_hori = vel_t_hi_hori * cosbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 	
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	SLong vel_t_pi_vert = unfriendly->vely * sinbearing/ANGLES_FRACT;
//DEADCODE CSB 08/11/99 	
//DEADCODE CSB 08/11/99 
//DEADCODE CSB 08/11/99 	closure = (vel_t_pi_hori + vel_t_pi_vert) - (vel_s_pi_hori + vel_s_pi_vert); 
//DEADCODE CSB 08/11/99 

	if (closure > dvel)
		return(TRUE);
	else
		return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClosureLessThan
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
Bool ACMAirStruc::ClosureLessThan(SLong dvel)
{
	SLong	closure;

	closure = SubjectClosure();

	if (closure < dvel)
		return(TRUE);
	else
		return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_LagRoll
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
Bool ACMAirStruc::M_LagRoll()
{
			if (SubjectClosureGreaterThan(MPH50))
			{
				ai.manoeuvre = MANOEUVRE_LAGROLL;
				return(TRUE);
			}else
				return(FALSE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_FlightSeparation
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
Bool 	ACMAirStruc::M_FlightSeparation()
{
	AirStrucPtr	unfriendly = *ai. unfriendly;

	SWord combatfactor = CombatFactor();
	if  (		(PitchIntercept >> ANGLES_180Deg)
			&&	(PitchIntercept << ANGLES_350Deg)
		)
		combatfactor += 10;
//DEADCODE CSB 08/11/99 	if	( velhori > unfriendly->velhori)
//DEADCODE CSB 08/11/99 		combatfactor += (velhori - unfriendly->velhori)/10;
	if(vel_ > unfriendly->vel_)
		combatfactor += (vel_ - unfriendly->vel_)/10000;
//DEADCODE CB 18/11/99 	if  (	(combatfactor < 160)
//DEADCODE CB 18/11/99 		||	( classtype->aerobaticfactor < AEROBATIC_FIGHTER)
//DEADCODE CB 18/11/99 		)
		ai.manoeuvre = MANOEUVRE_HEADON;
//DEADCODE CB 18/11/99 	else
//DEADCODE CB 18/11/99 		ai.manoeuvre = MANOEUVRE_HEADONOFFSET;
	return(TRUE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AboveGround
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
bool ACMAirStruc::AboveGround(SLong height)
{
	SLong lowestsafealt = Land_Scape.GroundHuggingAltitude(this);

	if (World.Y > (height + lowestsafealt))
		return(TRUE);
	else
		return(FALSE);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		R. Hyde 
//Date			Tue 10 Mar 1998
//
//Description	nosetotail or nosetobeam range > danger
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ManoeuvreBasedOnClosure()
{
	AirStrucPtr	unfriendly = *ai. unfriendly;

//##check allaspects for this
		if (SubjectClosureGreaterThan(MPH100))
		{
			if (	(ai.morale 	> 	MORALE_MEDIUM)
				)
			{
				if (SubjectLeadingTarget())
				{//turning fight changes to to lag roll if appropriate
						ai.manoeuvre= MANOEUVRE_TURNINGFIGHT;
				}
//					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGROLL, MANOEUVRE_TURNINGFIGHT);
					//ref1.68
				else
				{	
					if ((vel_ - unfriendly->vel_) > MPH50)
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_TURNINGFIGHT);
					else
						ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				}
			}else if (ai.morale 	== 	MORALE_MEDIUM)
				ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_ZOOM, MANOEUVRE_EXTENSION);
			else
				ai.manoeuvre = MANOEUVRE_EXTENSION;

		}else if(		(ai.combatskill >= SKILL_VETERAN)
					&&  (AboveGround(FT_1000))
//rdh					&&	SubjectOnTargetTail(ANGLES_20Deg)
					&&	( Range > WEAPONSRANGE)
					&&	(ClosureLessThan(MPH15))
				)
			ai.manoeuvre = MANOEUVRE_INTERCEPTLOW;
//DeadCode CSB 7Sep00 			ai.manoeuvre = MANOEUVRE_LOWYOYO;
		else if (SubjectLeadingTarget())
		{
			if (SubjectClosureGreaterThan(MPH50))
			{
				if (SubjectOnTargetTail(ANGLES_30Deg))
					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				else	
					ai.manoeuvre = MANOEUVRE_INTERCEPTHIGH;
//DeadCode CSB 7Sep00 					ai.manoeuvre = MANOEUVRE_HIGHYOYO;
			}
			else if (Range > WEAPONSRANGE)
			{
				ai.manoeuvre = MANOEUVRE_LEADPURSUIT;
			}else
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		}
		else if (SubjectOnTargetTail(ANGLES_30Deg))
			ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		else	
			ai.manoeuvre = MANOEUVRE_INTERCEPTHIGH;
//DeadCode CSB 7Sep00 			ai.manoeuvre = MANOEUVRE_HIGHYOYO;
		
}	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_BarrelRoll
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
Bool 	ACMAirStruc::M_BarrelRoll()
{

	if  (	(!AircraftDamaged())
		&&	(	(fly.cpitch << ANGLES_50Deg)	||	(fly.cpitch >> ANGLES_310Deg))
		&&  (AboveGround(FT_500))
		)
	{
		ai.manoeuvre = MANOEUVRE_BARRELROLLATTACK;
		return (TRUE);
	}else
		return(FALSE);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_ZoomAndDrop
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
Bool 	ACMAirStruc::M_ZoomAndDrop()
{
	if  (	(fly.cpitch < ANGLES_10Deg)
		&&	(	(roll << ANGLES_20Deg)
			|| 	(roll >> ANGLES_340Deg)
			)
		&&	(ai.morale 	> 	MORALE_GOOD)
		&& 	(ai.combatskill < SKILL_REGULAR)

		)
	{
		ai.manoeuvre = MANOEUVRE_ZOOMANDDROP;
		return (TRUE);
	}else
		return(FALSE);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_SpinOut
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
Bool 	ACMAirStruc::M_SpinOut()
{
	RndVal	rndnum = Math_Lib.rnd();
	if(		((AircraftDamaged()) && (AboveGround(FT_20000)) && (rndnum > RND75PC))
		||	((ai.combatskill < SKILL_REGULAR) && (AboveGround(FT_10000)) && (rndnum > RND50PC)) )
	{
		ai.manoeuvre = MANOEUVRE_SPINOUT;
		return (TRUE);
	}
	else
		return(FALSE);
}


//DeadCode RDH 07Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 07Jan99 //Procedure		M_SideSlip
//DeadCode RDH 07Jan99 //Author		R. Hyde 
//DeadCode RDH 07Jan99 //Date			Thu 5 Mar 1998
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Description	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Inputs		
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Returns	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 07Jan99 Bool 	ACMAirStruc::M_SideSlip()
//DeadCode RDH 07Jan99 {
//DeadCode RDH 07Jan99 	if	(	(TargetOnSubjectTail(ANGLES_10Deg))
//DeadCode RDH 07Jan99 		&&	(TargetFacingSubject(ANGLES_5Deg))
//DeadCode RDH 07Jan99 		)
//DeadCode RDH 07Jan99 	{
//DeadCode RDH 07Jan99 		ai.manoeuvre = MANOEUVRE_UNBALANCEDFLIGHT;
//DeadCode RDH 07Jan99 		return (TRUE);
//DeadCode RDH 07Jan99 	}else
//DeadCode RDH 07Jan99 		return(FALSE);
//DeadCode RDH 07Jan99 
//DeadCode RDH 07Jan99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_SelfAsBait
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.19
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool 	ACMAirStruc::M_SelfAsBait()
{
	return(FALSE);													  //CSB 24/01/00

//DEADCODE CSB 24/01/00 	if (	(		(classtype->phrasename != OLDPHRASE_MIGS)
//DEADCODE CSB 24/01/00 //DEADCODE RDH 10/05/99 	if (	(		(classtype->visible != MIG15)
//DEADCODE CSB 24/01/00 				&&	(ai.combatskill > SKILL_VETERAN)
//DEADCODE CSB 24/01/00 				&&	(ai.morale 	> 	MORALE_MEDIUM)
//DEADCODE CSB 24/01/00 				&&  (Range > DANGERRANGE)
//DEADCODE CSB 24/01/00 			)
//DEADCODE CSB 24/01/00 			||
//DEADCODE CSB 24/01/00 			(		(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 24/01/00 //DEADCODE RDH 10/05/99 			(		(classtype->visible == MIG15)
//DEADCODE CSB 24/01/00 				&&	(ai.aggressionlevel == AL_ATTACKANYTHING)
//DEADCODE CSB 24/01/00 				&&  (Range > DANGERRANGE)
//DEADCODE CSB 24/01/00 			)
//DEADCODE CSB 24/01/00 		)
//DEADCODE CSB 24/01/00 	{
//DEADCODE CSB 24/01/00 			ai.manoeuvre = MANOEUVRE_SELFASBAIT;
//DEADCODE CSB 24/01/00 			return (TRUE);
//DEADCODE CSB 24/01/00 	}
//DEADCODE CSB 24/01/00 	else
//DEADCODE CSB 24/01/00 			return(FALSE);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TargetHasLead
//Author		R. Hyde 
//Date			Thu 12 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::TargetHasCorrectLead(ANGLES lead, ANGLES maxlead)
{
	ANGLES delta = lead + maxlead;
	ANGLES anglerange = maxlead + maxlead;
	if ((delta) << (anglerange))
	{
	 	return (TRUE);
	}else
	{
		return (FALSE);
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ActualLead
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	degrees from perfect lead, positive is excess lead
//
//------------------------------------------------------------------------------
ANGLES ACMAirStruc::ActualLead(AirStrucPtr  subjt, AirStrucPtr trgt)
{
	COORDS3D	target;
	COORDS3D	subject;
	SLong		t,actualrange, oldrange;
	ANGLES		HItoTarget, oldHI, oldPI;


	oldrange = Range;
	oldHI = HdgIntercept;
	oldPI = PitchIntercept;

	subject.X = subjt->World.X;
	subject.Y = subjt->World.Y;
	subject.Z = subjt->World.Z;

	target.X = trgt->World.X;
	target.Y = trgt->World.Y;
	target.Z = trgt->World.Z;
	InterceptandRange (&subject, &target);
	HItoTarget = HdgIntercept;

	SLong	vx,vy,vz;

	CalcLead(subjt,trgt, vx,vy,vz, FALSE);
	target.X = trgt->World.X + vx;
	target.Y = trgt->World.Y + vy;
	target.Z = trgt->World.Z + vz;

	InterceptandRange (&subject, &target);
	ANGLES Lead;
	Lead = HdgIntercept - subjt->hdg;
	if (HdgIntercept >> HItoTarget)
		Lead = -Lead;

	Range			= oldrange;
	HdgIntercept	= oldHI;
	PitchIntercept	= oldPI;


	return (Lead);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManoeuvreBasedOn.combatskill
//Author		Rod Hyde
//Date			Thu 12 Mar 1998
//
//Description	it is best to come out true
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MANOEUVRE	ACMAirStruc::ManoeuvreBasedOnSkill(SkillType combatskill, MANOEUVRE goodman, MANOEUVRE badman)
{
	int acskill  = int(ai.combatskill);
	int cutoff   = int(combatskill);
	int maxskill = int(SKILL_MAX);

	ULong reqval;
	if(acskill < cutoff)
		reqval = (32768 * acskill * acskill) / (cutoff * cutoff);
	else
		reqval = 65535 - (32768 * (maxskill - acskill) * (maxskill - acskill)) / ((maxskill - cutoff) * (maxskill - cutoff));

	if(Math_Lib.rnd(65536) < reqval)
		return(goodman);
	else
		return(badman);
}

//DEADCODE CSB 17/02/00 	if (ai.combatskill < combatskill)
//DEADCODE CSB 17/02/00 	{
//DEADCODE CSB 17/02/00 		return (badman);
//DEADCODE CSB 17/02/00 	}else
//DEADCODE CSB 17/02/00 	{
//DEADCODE CSB 17/02/00 		int	rndnum = Math_Lib.rnd((int) ai.combatskill);
//DEADCODE CSB 17/02/00 		if (rndnum < (int)combatskill)
//DEADCODE CSB 17/02/00 		{
//DEADCODE CSB 17/02/00 			return (badman);
//DEADCODE CSB 17/02/00 		}
//DEADCODE CSB 17/02/00 		else
//DEADCODE CSB 17/02/00 		{
//DEADCODE CSB 17/02/00 			return (goodman);
//DEADCODE CSB 17/02/00 		}
//DEADCODE CSB 17/02/00 	}
//DEADCODE CSB 17/02/00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubjectHasEnergyAdvantage
//Author		Rod Hyde
//Date			Thu 12 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::SubjectHasEnergyAdvantage()
{
// PE or speed advantage
// or if not much in it, which has greater T/W ratio
	AirStrucPtr	unfriendly = *ai. unfriendly;

	if (		(DeltaAltitude() > FT_2000)
			||	((vel_ - unfriendly->vel_) > MPH100)
//DEADCODE CSB 04/05/00 			||	(		(DeltaAltitude() > -FT_1000)
//DEADCODE CSB 04/05/00 					&&	((vel_ - unfriendly->vel_) > -MPH50)
//DEADCODE CSB 04/05/00 					&&	(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 					&&	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 				)
		)
		return (TRUE);
	else
		return(FALSE);


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_GunDefence
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.23..
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool 	ACMAirStruc::M_GunDefence(ANGLES lead)
{
	MODEL& MOD = *fly.pModel;
	
	if (!TargetHasCorrectLead(lead, ANGLES_3Deg))
	{
		return(FALSE);
	}else
	{

		if (	(ai.combatskill < SKILL_REGULAR)
			&&	(ai.morale > MORALE_GOOD)
			)
		{	//close quarter, self as bait
			if (Range < WEAPONSRANGE)
				ai.manoeuvre = MANOEUVRE_BREAKTURN;
			else
				ai.manoeuvre = MANOEUVRE_LAZYTURN;
		}else
		{
			SWord combatfactor = CombatFactor();
			int rnd = Math_Lib.rnd((int)ai.morale);
			RndVal	rndnum = Math_Lib.rnd();
			if ( rnd <= (int)MORALE_POOR)
				 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_SCISSORS,MANOEUVRE_MILDSCISSORS);
			else if	(		(rndnum < RND25PC)
						&&	(MOD.Inst.I_MachNo > 0.6)
					)
				ai.manoeuvre= MANOEUVRE_ZOOM;
			else if (!M_SplitS())
			{
				if (	(TargetFacingSubject(ANGLES_5Deg))
					&&	(TargetOnSubjectTail(ANGLES_5Deg))
					&&	(TargetClosureGreaterThan(MPH50))
					)
				{
						ai.manoeuvre = MANOEUVRE_HIGBARRELROLL;

				}else if(		(roll << ANGLES_20Deg)
							|| 	(roll >> ANGLES_340Deg)
						)
				{
					RndVal	rndnum = Math_Lib.rnd();
					if	(rndnum < RND25PC)
						ai.manoeuvre = MANOEUVRE_JINK;
					else if	(rndnum < RND50PC)
						ai.manoeuvre = MANOEUVRE_UNBALANCEDFLIGHT;
					else
						ai.manoeuvre = MANOEUVRE_BREAKTURN;
				}else
				{
					if	(rndnum < RND25PC)
						ai.manoeuvre = MANOEUVRE_JINK;
					else if	(rndnum < RND50PC)
					{
						if (!AboveGround(FT_1000))
							ai.manoeuvre = MANOEUVRE_JINK;
						else
							ai.manoeuvre = MANOEUVRE_BREAK90;
					}
					else
					{
						if (!AboveGround(FT_3000))
							ai.manoeuvre = MANOEUVRE_JINK;
						else
//DEADCODE CB 18/11/99 							ai.manoeuvre = MANOEUVRE_BREAK180;
							ai.manoeuvre = MANOEUVRE_BREAK90;		  //CB 18/11/99
					}

				}
			}
	//rdh 6/1/99			if (rndnum < RND90PC)
//rdh 6/1/99			{
//rdh 6/1/99				if (combatfactor < 100)
//rdh 6/1/99					ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
//rdh 6/1/99				else if (combatfactor < 150)
//rdh 6/1/99					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						
//rdh 6/1/99			}
		}
		return(TRUE);
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_UnSighted
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
Bool 	ACMAirStruc::M_UnSighted()
{
//if unsighted:
//	good move is to slip out of plane
//	bad move is to reverse
//
	if  (	(roll <<  ANGLES_45Deg)
		||	(roll >>  ANGLES_315Deg)
		||	(	(PitchIntercept >> ANGLES_30Deg)
			&&	(PitchIntercept << ANGLES_330Deg)
			)
		)
	{
		return (FALSE);
	}else
	{
		SWord	brg = HdgIntercept - hdg;
		if	(	(		((roll >>  ANGLES_45Deg)	&&	(brg < 0))
					||	((roll >>  ANGLES_45Deg)	&&	(brg < 0))
				)
			&&
				(	(ai.morale < MORALE_MEDIUM)
				||	(ai.combatskill < SKILL_REGULAR)
				)
			)
			{//ref1.66 poor manoeuvre when unsighted
				ai.manoeuvre = MANOEUVRE_BREAKTURN;
				return (TRUE);

			}else
			{
				return (FALSE);
			}
	}			

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_DiveForHome
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
Bool 	ACMAirStruc::M_DiveForHome()
{

	if	(	(		(AircraftDamaged())
			&&	(ai.combatskill < SKILL_REGULAR)
			)
		||	(
					(ai.combatskill < SKILL_REGULAR)
				&&	(ai.combatskill > SKILL_POOR)
				&&	(ai.morale 	< 	MORALE_MEDIUM)
			)

		)
		{
			ai.manoeuvre = MANOEUVRE_DIVEFORHOME;
			return (TRUE);
		}else
			return(FALSE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_SplitS
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
Bool 	ACMAirStruc::M_SplitS()
{
	RndVal	rndnum = Math_Lib.rnd();
	if	(	(	(roll >> ANGLES_10Deg)
			|| 	(roll << (ANGLES_350Deg))
			)
			&&  (AboveGround(FT_10000))
			&&	(!AircraftDamaged())
		)
		{
			if	(rndnum < RND25PC)
//DEADCODE CB 18/11/99 				ai.manoeuvre = MANOEUVRE_BREAK180;
				ai.manoeuvre = MANOEUVRE_BREAK90;					  //CB 18/11/99
			else if	(rndnum < RND50PC)
			{
//DEADCODE CSB 10/01/00 				if(classtype->visible == F86)				//CSB 08/07/99	
//DEADCODE CSB 10/01/00 					ai.manoeuvre = MANOEUVRE_DIVINGSPIN;	//CSB 08/07/99	
//DEADCODE CSB 10/01/00 				else										//CSB 08/07/99	
					ai.manoeuvre = MANOEUVRE_BREAKLOW;
			}
			else
				ai.manoeuvre = MANOEUVRE_SPLITS;
			return (TRUE);
		}else if	(	(	(roll >> ANGLES_10Deg)
			|| 	(roll << (ANGLES_350Deg))
			)
			&&  (AboveGround(FT_5000))
		)
		{
			if	(rndnum < RND25PC)
//DEADCODE CB 18/11/99 				ai.manoeuvre = MANOEUVRE_BREAK180;
				ai.manoeuvre = MANOEUVRE_BREAK90;
			else if	(rndnum < RND50PC)
				ai.manoeuvre = MANOEUVRE_BREAKLOW;
			else
				ai.manoeuvre = MANOEUVRE_BREAKHIGH;
			return (TRUE);
		}else
			return(FALSE);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_Scissors
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
Bool 	ACMAirStruc::M_Scissors(ANGLES lead)
{
	if  (	(	(lead << ANGLES_90Deg)
				||
				(lead >> ANGLES_358Deg)
			)
			&&	(	(roll >> ANGLES_30Deg)
				&& 	(roll << ANGLES_330Deg)
				)
		)
	{//ie the lead is too much or just enough for target to get in a shot
		if	(	(	(ai.combatskill >= SKILL_VETERAN))
				&&	(lead << ANGLES_90Deg)
				)
		{
			ai.manoeuvre = MANOEUVRE_REVERSETURN;
			return (TRUE);
		}else
		{
			RndVal	rndnum = Math_Lib.rnd();
			if	(rndnum < RND50PC)
			{
			 	if (ai.combatskill >= SKILL_REGULAR)
					ai.manoeuvre = MANOEUVRE_SCISSORS;
				else
					ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
				return (TRUE);
			}else
				return(FALSE);	
		}
	}else
		return(FALSE);	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_ShootTooEarly
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
Bool	ACMAirStruc::M_ShootTooEarly()
{

	if	(		SubjectFacingTarget(ANGLES_10Deg)
			&&	(SubjectOnTargetTail(ANGLES_20Deg))
			&&	(ai.combatskill < SKILL_REGULAR)
//rdh 6/1/99			&&	(ai.morale < MORALE_GOOD)
		)
		{
			ai.manoeuvre = MANOEUVRE_SHOOTTOOEARLY;
	 		return (TRUE);
 	}else
 		return(FALSE);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DefenceManoeuvre
//Author		R. Hyde 
//Date			Thu 12 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::DefenceManoeuvre()
{
	if(Math_Lib.rnd(255) < ai.combatskill)
		for(SWord i = 0; i <= 3; i++)
		{
			PCLOUD cloud = &MissManCampSky().Layer[i];
			if(cloud->Cover >= 128)
			{
				if((World.Y < cloud->AltBase) && (World.Y > cloud->AltBase - METRES100))
				{
					ai.manoeuvre = MANOEUVRE_GAINHEIGHT;
					return;
				}
				else if((World.Y > cloud->AltTop) && (World.Y < cloud->AltTop + METRES100))
				{
					ai.manoeuvre = MANOEUVRE_STRAIGHTDIVE;
					return;
				}
			}
		}

	if(ai.morale > MORALE_GOOD)
	{
		if(TargetClosureGreaterThan(MPH50))
			switch(Math_Lib.rnd(2))
			{
				case 0:		ai.manoeuvre = MANOEUVRE_HIGBARRELROLL;		break;
				case 1:		ai.manoeuvre = MANOEUVRE_ZOOMANDDROP;		break;
			}
		else
			switch(Math_Lib.rnd(15))
			{
				case 0:		ai.manoeuvre = MANOEUVRE_SPLITS;			break;
				case 1:		ai.manoeuvre = MANOEUVRE_SCISSORS;			break;
				case 2:		ai.manoeuvre = MANOEUVRE_STRAIGHTDIVE;		break;
				case 3:		ai.manoeuvre = MANOEUVRE_BREAKLOW;			break;
				case 4:		ai.manoeuvre = MANOEUVRE_BREAKHIGH;			break;
				case 5:		ai.manoeuvre = MANOEUVRE_BREAK90;			break;
				case 6:		ai.manoeuvre = MANOEUVRE_BREAKTURN;			break;
				case 7:		ai.manoeuvre = MANOEUVRE_REVERSETURN;		break;
				case 8:		ai.manoeuvre = MANOEUVRE_JINK;				break;
				case 9:		ai.manoeuvre = MANOEUVRE_DIVINGSPIN;		break;
				case 10:	ai.manoeuvre = MANOEUVRE_UNBALANCEDFLIGHT;	break;
				case 11:
				case 12:
				case 13:
				case 14:
				{
					ai.manoeuvre = MANOEUVRE_SCISSORS;
					switch(fly.pModel->Type)
					{
						case AT_SPITFIRE:
						case AT_HURRICANE:
							ai.manoeuvre = MANOEUVRE_CLIMBTURN;		break;
						case AT_BF109:
						{
//DeadCode CSB 8Aug00 							if(World.Y > 250000)
							if(Math_Lib.rnd(2))
								ai.manoeuvre = MANOEUVRE_STEEPDIVE;
							else
								ai.manoeuvre = MANOEUVRE_ZOOM;
							break;
						}
						case AT_BF110:
							ai.manoeuvre = MANOEUVRE_STALLTURN;		break;
					}
				}
			}
	}
	else
	{
		if(Math_Lib.rnd(5120) < 128 - ai.morale)
			ai.manoeuvre = MANOEUVRE_BAILOUT;
		else
			switch(Math_Lib.rnd(4))
			{
				case 0:		ai.manoeuvre = MANOEUVRE_PANICTURN;			break;
				case 1:		ai.manoeuvre = MANOEUVRE_MILDSCISSORS;		break;
				case 2:		ai.manoeuvre = MANOEUVRE_MAKEFORFRIENDLY;	break;
				case 3:		ai.manoeuvre = MANOEUVRE_SPINOUT;			break;
			}
	}
}

//DEADCODE CSB 24/01/00 		{
//DEADCODE CSB 24/01/00 			if (SubjectHasEnergyAdvantage())
//DEADCODE CSB 24/01/00 				 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT, MANOEUVRE_BREAKTURN);
//DEADCODE CSB 24/01/00 			else
//DEADCODE CSB 24/01/00 				 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_BREAKTURN, MANOEUVRE_TURNINGFIGHT);
//DEADCODE CSB 24/01/00 		}
//DEADCODE CSB 24/01/00 		else
//DEADCODE CSB 24/01/00 			ai.manoeuvre = MANOEUVRE_EXTENSION;
//DEADCODE CSB 24/01/00 	}
//DEADCODE CSB 24/01/00 	else if(ai.morale > MORALE_POOR)
//DEADCODE CSB 24/01/00 	{
//DEADCODE CSB 24/01/00 		if (SubjectHasEnergyAdvantage())
//DEADCODE CSB 24/01/00 			 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_HIGBARRELROLL);
//DEADCODE CSB 24/01/00 		else
//DEADCODE CSB 24/01/00 			 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_HIGBARRELROLL,MANOEUVRE_TURNINGFIGHT);	////lag roll defense ref1.71
//DEADCODE CSB 24/01/00 	}
//DEADCODE CSB 24/01/00 	else
//DEADCODE CSB 24/01/00 		ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
//DEADCODE CSB 24/01/00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		M_ShootToFrighten
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
Bool	ACMAirStruc::M_ShootToFrighten()
{
	if	(		SubjectFacingTarget(ANGLES_10Deg)
			&&	(SubjectOnTargetTail(ANGLES_20Deg))
			&&	(ClosureLessThan(MPH00))
			&&	(ai.combatskill > SKILL_VETERAN)
		)
	{
		ai.manoeuvre = MANOEUVRE_SHOOTTOFRIGHTEN;
		return (TRUE);
 	}else
 		return(FALSE);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeltaAltitude
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
SLong		ACMAirStruc::DeltaAltitude()
{
	return (World.Y - ai.unfriendly->World.Y);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AggressivePassmanoeuvre
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
void	ACMAirStruc::AggressivePassManoeuvre()
{
//DEADCODE CSB 04/05/00 	RndVal	rndnum = Math_Lib.rnd();
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 	if (	(	(classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 	if (	(	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 			&&	(rndnum < RND25PC)
//DEADCODE CSB 04/05/00 			)
//DEADCODE CSB 04/05/00 //DEADCODE CSB 10/01/00 			||
//DEADCODE CSB 04/05/00 //DEADCODE CSB 10/01/00 			(	(classtype->visible == F86)
//DEADCODE CSB 04/05/00 //DEADCODE CSB 10/01/00 			&&	(rndnum > RND25PC)
//DEADCODE CSB 04/05/00 //DEADCODE CSB 10/01/00 			)
//DEADCODE CSB 04/05/00 		)
//DEADCODE CSB 04/05/00 		ai.manoeuvre = MANOEUVRE_BREAKTURN;
//DEADCODE CSB 04/05/00 	else
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DefensivePassManoeuvre
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
void	ACMAirStruc::DefensivePassManoeuvre()
{
	RndVal	rndnum = Math_Lib.rnd();
	 if (rndnum < RND25PC)
		ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
	 else if (rndnum < RND50PC)
		ai.manoeuvre = MANOEUVRE_EXTENSION;
	else
		ai.manoeuvre = MANOEUVRE_ZOOM;


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectNoseToNoseManoeuvre
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectNoseToNoseManoeuvre()
{
	if (Range > ENGAGERANGE)
	{
		if (DeltaAltitude() > FT_2000)
			ai.manoeuvre = MANOEUVRE_INTERCEPTHIGH;
		else if (DeltaAltitude() < FT_2000)
			ai.manoeuvre = MANOEUVRE_GAINHEIGHT;
		else
			M_FlightSeparation();
	}else
	{
		if  (DeltaAltitude() > FT_2000)
			ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
		else 
			M_FlightSeparation();
	}

	if(!Math_Lib.rnd(10))
	{
		if(AirStrucPtr buddy = FindBuddy())
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON, MSG_INITIALCOMBAT, *this, AirStrucPtr(ai.unfriendly), buddy));
	}

//	if (Range > ENGAGERANGE)
//	{
//		if (DeltaAltitude() > FT_2000)
//			ai.manoeuvre = MANOEUVRE_INTERCEPTHIGH;
//		else if (DeltaAltitude() < FT_2000)
//			ai.manoeuvre = MANOEUVRE_GAINHEIGHT;
//		else
//			M_FlightSeparation();
//	}else if (Range > 3 * BREAKTURNRADIUS)
//	{
//		M_FlightSeparation();
//	}else
//	{
//		RndVal	rndnum = Math_Lib.rnd();
//		if (DeltaAltitude() > FT_2000)
//		{
//			if (ai.morale >= MORALE_VERYGOOD)
//				AggressivePassManoeuvre();
//			else
//				DefensivePassManoeuvre();
//		}else if  (Range < DANGERRANGE)
//		{
//			if (ai.morale >= MORALE_VERYGOOD)
//				AggressivePassManoeuvre();
//
//			else if	(TargetFacingSubject(ANGLES_5Deg))
//			{
//				if (ai.morale < MORALE_MEDIUM)
//					ai.manoeuvre = MANOEUVRE_BREAKTURN;		//panic
//				else if (ai.morale < MORALE_VERYGOOD)
//				{
//					if (ai.combatskill > SKILL_REGULAR)
//						ai.manoeuvre = MANOEUVRE_JINK;
//					else
//						ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
//				}
//			}else
//				ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
//				
//		}else
//		{
//			if (ai.morale >= MORALE_VERYGOOD)
//			{
//				if ((	(ai.combatskill < SKILL_REGULAR)
//					)
//					||
//					(	(ai.combatskill > SKILL_VETERAN)
//					 		&&	(Range < BREAKTURNRADIUS)
//					)
//				   )
//						ai.manoeuvre = MANOEUVRE_BREAKTURN;
//					else
//						M_FlightSeparation();
//			}else
//				M_FlightSeparation();
//				
//		}
//	}

//	if alt advantage
//		dive and zoom	
//	
//	ai.manoeuvre = MANOEUVRE_HEADONOFFSET;
//	
//	
//	
//	
//##	lead turn 77
//	nose to nose 78
//	nose to tail 79
//	in horizontal and vertical planes
//if (morale high and aggressionlevel == attack)
//	try Headonattack
//if (under headonattack and morale == low)
//	panic and scatter
//
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectNoseToTailManoeuvre
//Author		R. Hyde 
//Date			Mon 18 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectNoseToTailManoeuvre()
{ 
	if (Range > DANGERRANGE)
	{
//DEADCODE CSB 24/01/00 		if(		(ai.combatskill >= SKILL_VETERAN)
//DEADCODE CSB 24/01/00 			&&  (AboveGround(FT_1000))
//DEADCODE CSB 24/01/00 			&&	( Range > WEAPONSRANGE)
//DEADCODE CSB 24/01/00 			&&	(ClosureLessThan(MPH15))
//DEADCODE CSB 24/01/00 		)
//DEADCODE CSB 24/01/00 			ai.manoeuvre = MANOEUVRE_LOWYOYO;
//DEADCODE CSB 24/01/00 		else
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
	}
	else
	{
		if (follower)
		{
			if	(Math_Lib.rnd(RndValMAX) < RND50PC)
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COVERME, MSG_STATUSREPORT, *this, NULL, Follower()));
			else
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STAYCLOSE, MSG_STATUSREPORT , *this, NULL,Follower()));
		}	

		AirStruc* unf		= (AirStruc*)ai.unfriendly;
		AirStruc* unfbuddy	= this;
		if((classtype->visible != ME110) && (classtype->visible != JU87) && (classtype->visible != DEF))
			unfbuddy = unf->FindBuddy();
		
		if  (unfbuddy)
		{//unfriendly is attacked by aircraft 
		   BreakCallandReaction(unfbuddy, unf, this);
		}
		if (Range > WEAPONSRANGE)
		{
			if (ai.combatskill > SKILL_REGULAR)
			{
				if (!M_ShootToFrighten())
					ManoeuvreBasedOnClosure();
			}
			else
			{
				if (!M_ShootTooEarly())
					ManoeuvreBasedOnClosure();
			}
		}
		else
		{
			if(		(AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW) 
				&&	(ai.combatskill < SKILL_REGULAR)
				&&	(Math_Lib.rnd(2))
			)
				ai.manoeuvre = MANOEUVRE_SLASHINGATTACK;
			else
				ManoeuvreBasedOnClosure();
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectNoseToBeamManoeuvre
//Author		R. Hyde 
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::SelectNoseToBeamManoeuvre()
{
	if (Range > ENGAGERANGE)
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
	else if (Range > DANGERRANGE)
		ManoeuvreBasedOnClosure();
	else
	{
		if (Range > WEAPONSRANGE)
		{
			if (ai.combatskill > SKILL_REGULAR)
			{
				if (!M_ShootToFrighten())
					ManoeuvreBasedOnClosure();
			}else
			{
				if (!M_ShootTooEarly())
					ManoeuvreBasedOnClosure();
			}
		}
		else
			ManoeuvreBasedOnClosure();
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectBeamToNoseManoeuvre
//Author		R. Hyde 
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectBeamToNoseManoeuvre()
{
	if(AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW)
	{
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		return;
	}

	if (Range > COMBATRANGE)
	{
		SelectNextDisengageManoeuvre ();
	}else if (Range > ENGAGERANGE)
	{
		if	(ai.morale 	> 	MORALE_MEDIUM)
		{
			if (SubjectHasEnergyAdvantage())
			{
//DEADCODE CSB 04/05/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 				if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_BREAKTURN);
//DEADCODE CSB 04/05/00 				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
			}else
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		}
	}else if (Range > DANGERRANGE)									  //rdh 31/03/99
	{
		if (!M_UnSighted())
			ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
	}else 
	{
		ANGLES trgtlead = ActualLead(*ai.unfriendly, *this);
		if (!M_GunDefence(trgtlead))
			if	(!M_Scissors(trgtlead))
				DefenceManoeuvre();
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectBeamToTailManoeuvre
//Author		R. Hyde 
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectBeamToTailManoeuvre()
{
	if	(ai.morale 	> 	MORALE_GOOD)
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
	else if (Range > COMBATRANGE)
	{
		if	(ai.morale 	< 	MORALE_MEDIUM)
			SelectNextDisengageManoeuvre ();
		else
		{
			if (SubjectHasEnergyAdvantage())
			{
//DEADCODE CSB 04/05/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 				if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_BREAKTURN);
//DEADCODE CSB 04/05/00 				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
			}else
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		}
	}else if (Range > ENGAGERANGE)
	{
		if	(ai.morale 	> 	MORALE_MEDIUM)
		{
			if (SubjectHasEnergyAdvantage())
			{
//DEADCODE CSB 04/05/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 				if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_BREAKTURN);
//DEADCODE CSB 04/05/00 				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
			}else
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		}else
			ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
	}else
	{
		if (ai.morale >= MORALE_MEDIUM)
		//##	if (ai.combatskill > SKILL_REGULAR)
				//##speedbrakes
			ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
		else
			ai.manoeuvre = MANOEUVRE_EXTENSION;

	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectBeamToBeamManoeuvre
//Author		R. Hyde 
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectBeamToBeamManoeuvre()
{
	if	(ai.morale 	> 	MORALE_GOOD)
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
	else if (Range > COMBATRANGE)
	{
		if	(ai.morale 	< 	MORALE_MEDIUM)
			SelectNextDisengageManoeuvre ();
		else
		{
			if (SubjectHasEnergyAdvantage())
			{
//DEADCODE CSB 04/05/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 				if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_BREAKTURN);
//DEADCODE CSB 04/05/00 				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
			}else
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		}
	}else if (Range > 2 * BREAKTURNRADIUS)
	{
		if	(ai.morale 	> 	MORALE_MEDIUM)
		{
			if (SubjectHasEnergyAdvantage())
			{
				MANOEUVRE tempman;
//DEADCODE CSB 04/05/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 				if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 				{
//DEADCODE CSB 04/05/00 					if (DeltaAltitude() > FT_2000)
//DEADCODE CSB 04/05/00 						tempman = MANOEUVRE_TURNINGFIGHT;
//DEADCODE CSB 04/05/00 					else
//DEADCODE CSB 04/05/00 						tempman = MANOEUVRE_GAINHEIGHT; 
//DEADCODE CSB 04/05/00 					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_BREAKTURN);
//DEADCODE CSB 04/05/00 				}else
				{
					if (DeltaAltitude() > FT_2000)
						tempman = MANOEUVRE_BREAKTURN;
					else
						tempman = MANOEUVRE_ZOOM; 
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
				}
			}else
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		}else
			SelectNextDisengageManoeuvre ();

	}else
	{
		if (NoseToTail(ANGLES_45Deg))
		{
			if (ai.morale >= MORALE_VERYGOOD)
				AggressivePassManoeuvre();
			else
				DefensivePassManoeuvre();
		}else
		{
			//if (ai.combatskill > SKILL_REGULAR)
				//##speedbrakes
			ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectTailToTailManoeuvre
//Author		R. Hyde 
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectTailToTailManoeuvre()
{

	if (Range > COMBATRANGE)
	{
		if	(ai.morale 	< 	MORALE_MEDIUM)
			SelectNextDisengageManoeuvre ();
		else
		{
			SLong d_alt = World.Y - ai.unfriendly->World.Y;
			if (d_alt > FT_3000)
				ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_INTERCEPTHIGH,MANOEUVRE_SPLITS);
			else if (d_alt < -FT_3000)
				ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_IMMELMANN);
			else if (SubjectHasEnergyAdvantage())
			{
//DEADCODE CSB 04/05/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 				if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_ZOOM);
//DEADCODE CSB 04/05/00 				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_BREAKTURN);
			}else
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		}
	}else 
	{
		if	(ai.morale 	> 	MORALE_MEDIUM)
		{
//DEADCODE CSB 04/05/00 			if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 			if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 				ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_GAINHEIGHT);
//DEADCODE CSB 04/05/00 			else
				ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_BREAKTURN);
		}else
//			ai.manoeuvre = MANOEUVRE_LAZYTURN;
			ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectTailToBeamManoeuvre
//Author		R. Hyde 
//Date			Wed 4 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectTailToBeamManoeuvre()
{
	if	(ai.morale 	> 	MORALE_GOOD)
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
	else if (Range > COMBATRANGE)
	{
		if	(ai.morale 	< 	MORALE_MEDIUM)
			SelectNextDisengageManoeuvre ();
		else
		{
			if (SubjectHasEnergyAdvantage())
			{
//DEADCODE CSB 04/05/00 					if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 					if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_BREAKTURN);
//DEADCODE CSB 04/05/00 					else
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
			}else
				 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
		}
	}else if (Range > ENGAGERANGE)
	{
		if	(ai.morale 	> 	MORALE_MEDIUM)
		{
			if (SubjectHasEnergyAdvantage())

			{
//DEADCODE CSB 04/05/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 				if	(classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_GAINHEIGHT,MANOEUVRE_BREAKTURN);
//DEADCODE CSB 04/05/00 				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
			}else
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		} else
			 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
	}else
	{
		if (ai.combatskill < SKILL_REGULAR)
		{
			ai.manoeuvre = MANOEUVRE_REVERSETURN;
		}else
		{
			if (SubjectHasEnergyAdvantage())
				 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_ZOOM,MANOEUVRE_TURNINGFIGHT);
			else
				 ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR,MANOEUVRE_TURNINGFIGHT,MANOEUVRE_ZOOM);
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelectTailToNoseManoeuvre
//Author		R. Hyde 
//Date			Mon 18 Mar 1996
//
//Description	ChooseRearDefenseManoeuvre
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelectTailToNoseManoeuvre()
{
	if(AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW)
	{
		ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
		return;
	}

	if (!M_SelfAsBait())
	{
		if (!M_DiveForHome())
		{
			if (Range > (METRES600 + COMBATRANGE))
			{
				ai.manoeuvre= MANOEUVRE_TURNINGFIGHT;
			}else if (Range > ENGAGERANGE)
			{
				if (vel_ > MINIMUMCOMBATSPEED)
					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				else			
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_GAINHEIGHT, MANOEUVRE_GAINSPEED);

			}else if (Range > DANGERRANGE)
			{
				if  (!M_UnSighted())
				{
					if (vel_ < MINIMUMCOMBATSPEED)
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_GAINSPEED, MANOEUVRE_TURNINGFIGHT);
					else			
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_TURNINGFIGHT, MANOEUVRE_GAINHEIGHT);
				}

			}else
			{
				ANGLES trgtlead = ActualLead(*ai.unfriendly, *this);
				if (!M_GunDefence(trgtlead))
					if (!M_UnSighted())
						if	(!M_Scissors(trgtlead))
							if (!M_ZoomAndDrop())
								DefenceManoeuvre();
			}
		}	
	}
	
	if((ai.morale < MORALE_MEDIUM) && (!Math_Lib.rnd(10)))
	{
		AirStrucPtr buddy = FindBuddy();
		if(buddy)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HELP, MSG_PERSONALTHREAT, *this, NULL, buddy));
	}			
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CornerSpeed
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
SLong ACMAirStruc::CornerSpeed()
{
	SLong retval = CORNERSPEED;
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SustainedTurn
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
SLong ACMAirStruc::SustainedTurnSpeed()
{

		SLong retval = SUSTAINEDTURNSPEED;
		return(retval);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetDesiredVel()
//Author		R. Hyde 
//Date			9/12/98
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SetDesiredVel()
{
	//the range will be from 0 to OUTERCOMBATRANGE
#define IDEALCOMBATRANGE2 30000
	Float rangefactor;
	Float velfactor = 0.05;
	AirStrucPtr	unfriendly = *ai. unfriendly;

	Float v;
	rangefactor = Range - IDEALCOMBATRANGE2;
	if (rangefactor < -METRES100)
		rangefactor = -METRES100;
	rangefactor = rangefactor * velfactor / IDEALCOMBATRANGE2;
	v = unfriendly->vel_ * (1 - rangefactor);
	fly.pModel->SetSpeed(this,v);

	if (Range  < COLLISIONRANGE)
		_Miles.SequenceAudible(MOOD_HERO);	  //RDH 01/03/99
	else if (Range  < DANGERRANGE)
		_Miles.SequenceAudible(MOOD_CONFIDENT);	  //RDH 01/03/99
	else
		_Miles.SequenceAudible(MOOD_HOPEFUL);	  //RDH 01/03/99

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManualACM
//Author		R. Hyde 
//Date			Fri 11 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ManualACM ()
{
//DeadCode CSB 28/04/99		PrintString(0, 22, "ManualACM ");
	
//DEADCODE DAW 26/11/99 	if(Key_Tests.KeyPress3d (RPM_50))	//CSB 18/3/99	
//DEADCODE CSB 18/01/00 	if(ai.manoeuvre != MANOEUVRE_HEADONATTACK)
//DEADCODE CSB 18/01/00 	{
//DEADCODE CSB 18/01/00 		ai.manoeuvre = MANOEUVRE_HEADONATTACK;	//CSB 18/03/99	
//DEADCODE CSB 18/01/00 		ai.ManStep   = 0;
//DEADCODE CSB 18/01/00 		SetManoeuvreTime (1500);
//DEADCODE CSB 18/01/00 	}

		switch (ai.manoeuvre)
		{
			case MANOEUVRE_LOOKROUND:
			{						  
 				LookAround ();		  
				break;				  
			}			
			case MANOEUVRE_WELDEDWINGMAN:										//RDH 03Mar98
			{
				WeldedWingMan();
				break;
			}
			case MANOEUVRE_BAILOUT:										//RDH 03Mar98
			{
 				BailOut();
				break;
			}
			case MANOEUVRE_TOPCOVER:
			{						  
				TopCover ();		  
				break;				  
			}			
			case MANOEUVRE_FORCETOPCOVER:
			{						  
				ForceTopCover ();		  
				break;				  
			}			
			case MANOEUVRE_LINEABREAST:										//RDH 27Mar98
			{
 				LineAbreast();
				break;
			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_SCATTER:											//RDH 27Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99 //DeadCode RDH 27Apr98 no such manoeuvre 				Scatter();	  //RDH 24/02/99
//DEADCODE CB 18/11/99 				TurningFight();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
			case MANOEUVRE_PINCER:											//RDH 27Mar98
			{
 				Pincer();
				break;
			}
			case MANOEUVRE_MULTIWAVE:										//RDH 27Mar98
			{
 				MultiWave();
				break;
			}
			case MANOEUVRE_DIVEANDZOOM:
			{
 				DiveAndZoom();
				break;
			}
			case MANOEUVRE_LEADPURSUIT:
			{
//done in TurningFight 				LeadPursuit();
				TurningFight();
				break;
			}
			case MANOEUVRE_LAGPURSUIT:
			{
 				LagPursuit();
				break;
			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_CIRCUMVENT:										//RDH 27Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99 //will not be implemented				Circumvent();
//DEADCODE CB 18/11/99 				TurningFight();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_ROUNDABOUT:										//RDH 27Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99  				RoundAbout();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
			case MANOEUVRE_SPLITMANOEUVRE:									//RDH 27Mar98
			{
 				SplitManoeuvre();									  //RDH 21/02/99
				break;
			}
			case MANOEUVRE_HEADON:
			{
  				HeadOn();
				break;
			}
			case MANOEUVRE_LINEASTERN:										//RDH 27Mar98
			{
				LineAstern();
				break;
			}
			case MANOEUVRE_VICATTACK:
			{
				VicAttack();
				break;
			}
			case MANOEUVRE_BARRELROLLATTACK:							
			{													
				BarrelRollAttack ();									
				break;											
			}													
			case MANOEUVRE_SCISSORS:							
			{													
 				Scissors ();									
				break;											
			}													
			case MANOEUVRE_MILDSCISSORS:						
			{													
 				MildScissors ();								
				break;											
			}													
			case MANOEUVRE_SPLITS:								
			{													
 				SplitS ();										
				break;											
			}													
			case MANOEUVRE_ZOOMANDDROP:							
			{													
 				ZoomandDrop ();									
				break;											
			}													
			case MANOEUVRE_STRAIGHTANDLEVEL :					
			{													
 				StraightandLevel ( );							
				break;											
			}													
			case MANOEUVRE_SPINOUT :							
			{													
 				SpinOut ( );									
				break;											
			}													
			case MANOEUVRE_DIVEFORHOME :						
			{													
				DiveforHome ( );								
				break;											
			}													
			case MANOEUVRE_GOHOME :								
			{													
 				GoHome ( );										
				break;											
			}													
			case MANOEUVRE_MAKEFORFRIENDLY :							
			{													
				Regroup();
//DeadCode RDH 27Apr98 				MakeForFriendly ( );									
//DeadCode CSB 5Sep00 				TurningFight();
				break;											
			}													
			case MANOEUVRE_MOVEAWAY :							
			{													
 				MoveAway ( );									
				break;											
			}													
			case MANOEUVRE_ACCIDENTALSPINOUT :					
			{//no difference from standard spin													
				SpinOut ( );							
				break;											
			}													
			case MANOEUVRE_VERTICALLOOP :						
			{	
//will not be used				VerticalLoop ( );								
				TurningFight();
				break;											
			}													
			case MANOEUVRE_IMMELMANNTURN :						
			{													
				ImmelmannTurn();								
//DeadCode CSB 4Sep00 				TurningFight();
				break;											
			}													
//DEADCODE CB 18/11/99 			case MANOEUVRE_HEADONOFFSET :						
//DEADCODE CB 18/11/99 			{													
//DEADCODE CB 18/11/99   				HeadOnOffset ( );								
//DEADCODE CB 18/11/99 				break;											
//DEADCODE CB 18/11/99 			}													
			case MANOEUVRE_IMMELMANN :						
			{													
 				Immelmann ( );								
				break;											
			}													
			case MANOEUVRE_STAYWITHPREY :						
			{													
//will not implement 				StayWithPrey ( );								
				TurningFight();
				break;											
			}													
			case MANOEUVRE_CLIMBFORHOME :						
			{													
 				ClimbforHome ( );								
				break;											
			}													
			case MANOEUVRE_STRAIGHTDIVE:						
			{													
				StraightDive ( );								
//DeadCode CSB 19/03/99					TurningFight();
				break;											
			}													
			case MANOEUVRE_STANDONTAIL:							
			{													
//will not be used
				TurningFight();
				break;											
			}													
			case MANOEUVRE_SHOOTTOFRIGHTEN:						
			{													
 				ShootToFrighten ( );							
				break;											
			}													
			case MANOEUVRE_SHOOTTOOEARLY:						
			{													
 				ShootTooEarly ( );							
				break;											
			}													
			case MANOEUVRE_GAINHEIGHT:							
			{													
				GainHeight ( );									
				break;											
			}													
			case MANOEUVRE_LAGROLL:											//RDH 30Mar98
			{
				LagRoll();
				break;
			}
			case MANOEUVRE_EXTENSION:								//RDH 30Mar98
			{
 				ExtensionManoeuvre();
				break;
			}
			case MANOEUVRE_DIVINGSPIN:
			{
 				DivingSpin();
				break;
			}
			case MANOEUVRE_REVERSETURN:										//RDH 30Mar98
			{
 				ReverseTurn();
				break;
			}
			case MANOEUVRE_SELFASBAIT:										//RDH 30Mar98
			{
 				SelfAsBait();
				break;
			}
			case MANOEUVRE_JINK:												//RDH 30Mar98
			{
 				Jink();
				break;
			}
			case MANOEUVRE_BREAKTURN:										//RDH 30Mar98
			{
				BreakTurn();
				break;
			}
			case MANOEUVRE_LAZYTURN:											//RDH 30Mar98
			{
				LazyTurn();
				break;
			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_BREAK180:											//RDH 30Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99  				Break180();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
			case MANOEUVRE_BREAKLOW:											//RDH 30Mar98
			{
 				BreakLow();
				break;
			}
			case MANOEUVRE_BREAKHIGH:										//RDH 30Mar98
			{
 				BreakHigh();
				break;
			}
			case MANOEUVRE_BREAK90:											//RDH 30Mar98
			{
 				Break90();
				break;
			}
			case MANOEUVRE_HIGBARRELROLL:									//RDH 30Mar98
			{
 				HiGBarrelRoll();
				break;
			}
			case MANOEUVRE_PANICTURN:									//RDH 30Mar98
			{
				PanicTurn();
				break;
			}
			case MANOEUVRE_UNBALANCEDFLIGHT:									//RDH 30Mar98
			{
 				UnBalancedFlight();
				break;
			}
			case MANOEUVRE_LOWALT:
			{
 				LowAlt();
				break;
			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_SNAPSHOT:											//RDH 30Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99 //will not be used	SnapShot();
//DEADCODE CB 18/11/99 				TurningFight();
//DEADCODE CB 18/11/99  				
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_STAYONTAIL:										//RDH 30Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99 //will not be used 				StayOnTail();
//DEADCODE CB 18/11/99 				TurningFight();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
			case MANOEUVRE_TURNTOHDGANDPITCH:								//RDH 30Mar98
			{
//DeadCode RDH 27Apr98 				TurnToHdgAndPitch();
				TurningFight();
				break;
			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_HOTSIDELAGPURSUITFIGHT:							//RDH 30Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99 //will not be used  				HotSideLagPursuitFight();
//DEADCODE CB 18/11/99 				TurningFight();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_SANDWICHMANOEUVRES:								//RDH 30Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99 //DeadCode RDH 27Apr98 				SandwichManoeuvres();
//DEADCODE CB 18/11/99 				TurningFight();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
			case MANOEUVRE_TURNINGFIGHT:									//RDH 30Mar98
			{
				TurningFight();
				break;
			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_SUSTAINEDTURN:									//RDH 30Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99 //will not use, covered in turningfight = f(skill)				SustainedTurn();
//DEADCODE CB 18/11/99  				TurningFight();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
//DeadCode CSB 7Sep00 			case MANOEUVRE_HIGHYOYO:											//RDH 30Mar98
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00  				HighYoYo();
//DeadCode CSB 7Sep00 				break;
//DeadCode CSB 7Sep00 			}
			case MANOEUVRE_ZOOM:											//RDH 30Mar98
			{
 				Zoom();
				break;
			}
//DeadCode CSB 7Sep00 			case MANOEUVRE_LOWYOYO:											//RDH 30Mar98
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00  				LowYoYo();
//DeadCode CSB 7Sep00 				break;
//DeadCode CSB 7Sep00 			}
			case MANOEUVRE_INTERCEPTHIGH:									//RDH 30Mar98
			{
				InterceptHigh();
				break;
			}
			case MANOEUVRE_INTERCEPTLOW:									//RDH 30Mar98
			{
				InterceptLow();
				break;
			}
//DEADCODE CB 18/11/99 			case MANOEUVRE_CLIMBATSUSTAINEDTURNSPEED:						//RDH 30Mar98
//DEADCODE CB 18/11/99 			{
//DEADCODE CB 18/11/99 				ClimbAtSustainedTurnSpeed();
//DEADCODE CB 18/11/99 				break;
//DEADCODE CB 18/11/99 			}
			case MANOEUVRE_GAINSPEED:						
			{													
//DeadCode RDH 03Dec98 				GainSpeed();
				if (ai.unfriendly)
					TurningFight();
				else
					GainSpeed();
				break;											
			}													
			case MANOEUVRE_HEADONATTACK:
			{													
				HeadOnAttack();	
				break;
			}
			case MANOEUVRE_LUFBERRY:						
			{													
				Lufberry();	
				break;
			}
			case MANOEUVRE_STEEPDIVE:
			{													
				SteepDive();
				break;
			}
			case MANOEUVRE_UPANDUNDER:
			{													
				UpAndUnder();
				break;
			}
			case MANOEUVRE_STALLTURN:
			{													
				StallTurn();
				break;
			}
			case MANOEUVRE_SLASHINGATTACK:
			{													
				SlashingAttack();
				break;
			}
			case MANOEUVRE_CLIMBTURN:
			{													
				ClimbTurn();
				break;
			}
			case MANOEUVRE_ROLL360:						
			{													
				Roll360();
				break;
			}
			case MANOEUVRE_STRAFFE:						
			{													
				Straffe();
				break;
			}													
			case MANOEUVRE_PEELOFF:						
			{													
				PeelOff();
				break;
			}													
			case MANOEUVRE_FLYTHROUGHCLOUD:						
			{													
				FlyThroughCloud();
				break;
			}													
			case MANOEUVRE_REGROUP:						
			{													
				Regroup();
				break;
			}													
			case MANOEUVRE_DISENGAGED:						
			{													
				ai.simpleacm = TRUE;
				break;
			}													
			case MANOEUVRE_SCREWYOUGUYSIMGOINGHOME:						
			{													
				ai.simpleacm = TRUE;
				break;
			}													
			case MANOEUVRE_SPINRECOVERY:						
			{													
 				SpinRecovery ( );								
				break;											
			}
			case MANOEUVRE_COLLISIONAVOIDANCE:						
			{													
 				CollisionAvoidance();								
				break;											
			}
			case MANOEUVRE_COLLIDE:						
			{													
//DeadCode CSB 12Oct00 				ai.manoeuvre = MANOEUVRE_SELECT;
				ai.simpleacm = TRUE;
				SimpleCollide();
				break;											
			}	
		}

//DeadCode CSB 1Sep00 		weap.ShootDelay = weap.ShootDelay-Timer_Code.FRAMETIME;
//DeadCode CSB 1Sep00 		if (weap.ShootDelay < 0)
//DeadCode CSB 1Sep00 			weap.ShootDelay = 0;
		
		
		ai.oldoldoldhdgI = ai.oldoldhdgI;
		ai.oldoldhdgI = ai.oldhdgI;
		ai.oldhdgI = HdgIntercept;

		ai.oldoldoldpitchI = ai.oldoldpitchI; //overloaded in SAGs by Lettering()
		ai.oldoldpitchI = ai.oldpitchI;
		ai.oldpitchI = PitchIntercept;

//DEADCODE CSB 24/11/99 	if (	(ai.unfriendly )
//DEADCODE CSB 24/11/99 		&&	(Save_Data.flightdifficulty [FD_AUTOTHROTTLE])	//THIS NO LONGER EXISTS //CSB 24/11/99
//DEADCODE CSB 24/11/99 		&&	((ai.unfriendly == Persons2::PlayerGhostAC)
//DEADCODE CSB 24/11/99 			|| (ai.unfriendly->uniqueID.commsmove))
//DEADCODE CSB 24/11/99 		&&	(Range  < OUTERCOMBATRANGE)
//DEADCODE CSB 24/11/99 		&&	(TargetFacingSubject(ANGLES_45Deg))
//DEADCODE CSB 24/11/99 		&&	(TargetOnSubjectTail(ANGLES_45Deg))
//DEADCODE CSB 24/11/99 		)
//DEADCODE CSB 24/11/99 		SetDesiredVel();
	
	Manual_Pilot.ACMManualPilot(this);	

		if(ai.unfriendly!=NULL)
			AutoShoot(TRUE);

//DeadCode CSB 2Oct00 	if (ai.manoeuvre == MANOEUVRE_SELECT)
//DeadCode CSB 2Oct00 	{
//DeadCode CSB 2Oct00 		if (ai.unfriendly==NULL)
//DeadCode CSB 2Oct00 		{
//DeadCode CSB 2Oct00 			if (	(ai.manoeuvre != MANOEUVRE_TOPCOVER)			//JIM 21Aug96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_LOOKROUND)			//JIM 21Aug96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_DIVEFORHOME)			//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_CLIMBFORHOME)		//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_STRAIGHTDIVE)		//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_GOHOME )				//JIM 15Oct96
//DeadCode CSB 2Oct00 				&&	(ai.manoeuvre != MANOEUVRE_SPINRECOVERY )				//JIM 15Oct96
//DeadCode CSB 2Oct00 				)
//DeadCode CSB 2Oct00 			{
//DeadCode CSB 2Oct00 		  		ai.ManStep = PHASE0;
//DeadCode CSB 2Oct00 //DeadCode CSB 25Aug00 				ai.manoeuvre=MANOEUVRE_LOOKROUND;
//DeadCode CSB 2Oct00 				ai.manoeuvre = MANOEUVRE_DISENGAGED;
//DeadCode CSB 2Oct00 				ai.simpleacm = TRUE;
//DeadCode CSB 2Oct00 			}
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 		}else
//DeadCode CSB 2Oct00 		{
//DeadCode CSB 2Oct00 			InterceptandRange (&ai.unfriendly->World);
//DeadCode CSB 2Oct00 			SelectNextEngageManoeuvre ();
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 			if (		(ai.manoeuvre != MANOEUVRE_TURNINGFIGHT)
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 					&&	(ai.manoeuvre != MANOEUVRE_GAINHEIGHT)
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 					&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 				)
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 			{
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 				MANOEUVRE manoeuvre = ai.manoeuvre;
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 				SelectNextEngageManoeuvre ();
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 				ai.manoeuvre = manoeuvre;
//DeadCode CSB 2Oct00 //DEADCODE DAW 01/04/99 			}
//DeadCode CSB 2Oct00 	  		ai.ManStep = PHASE0;
//DeadCode CSB 2Oct00 
//DeadCode CSB 2Oct00 		}
//DeadCode CSB 2Oct00 	}
//DeadCode CSB 2Oct00 //DEADCODE RDH 06/04/99 	if  (Key_Tests.KeyPress3d(CHEATLIFTKEY))
//DeadCode CSB 2Oct00 //DEADCODE RDH 06/04/99 	{
//DeadCode CSB 2Oct00 //DEADCODE RDH 06/04/99 		  		ai.ManStep = PHASE0;
//DeadCode CSB 2Oct00 //DEADCODE RDH 06/04/99 				ai.manoeuvre= MANOEUVRE_HIGHYOYO;
//DeadCode CSB 2Oct00 //DEADCODE RDH 06/04/99 	}
//DeadCode CSB 2Oct00 	if((ai.manoeuvre == MANOEUVRE_SELECT) && (movecode == AUTO_COMBAT))
//DeadCode CSB 2Oct00 	{
//DeadCode CSB 2Oct00 		ai.manoeuvre = MANOEUVRE_DISENGAGED;
//DeadCode CSB 2Oct00 		ai.simpleacm = TRUE;
//DeadCode CSB 2Oct00 		ai.ManStep = 0;
//DeadCode CSB 2Oct00 		SetManoeuvreTime(0);
//DeadCode CSB 2Oct00 		SetUnfriendly(NULL);
//DeadCode CSB 2Oct00 //DeadCode CSB 5Sep00 		movecode=AUTO_FOLLOWWP;
//DeadCode CSB 2Oct00 //DeadCode CSB 5Sep00 		information = IF_OUT_POS;					//CSB 22Aug00
//DeadCode CSB 2Oct00 //DeadCode CSB 5Sep00 		manoeuvretime = 0;
//DeadCode CSB 2Oct00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakCallandReaction
//Author		R. Hyde 
//Date			 //RDH 13/06/99
//
//Description	
//					HdgIntercept assumed
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::BreakCallandReaction(AirStrucPtr buddy,AirStrucPtr currac,AirStrucPtr unf)
{
	if(currac->classtype->aerobaticfactor != AEROBATIC_LOW)
	{
		SWord dhdg = unf->hdg - HdgIntercept;
		if(buddy == currac)
		{
			if(currac->ai.morale > MORALE_MEDIUM)
				_Radio.TriggerMsg(MESSAGE_STRUC(Art_Int.BreakCall(buddy, currac, unf), MSG_TOLDTOBREAK, currac, unf, currac).SetVoice(VOICE_REST));
			else
				_Radio.TriggerMsg(MESSAGE_STRUC(Art_Int.BreakCall(buddy, currac, unf), MSG_TOLDTOBREAK, currac, unf, currac).SetVoice(VOICE_XREST));
		}
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(Art_Int.BreakCall(buddy, currac, unf), MSG_TOLDTOBREAK, buddy, unf, currac));

		BreakCallReaction(currac, unf);
	}
}
			
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakCallReaction
//Author		R. Hyde 
//Date			 //RDH 13/06/99
//
//Description	
//					HdgIntercept assumed
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::BreakCallReaction(AirStrucPtr currac,AirStrucPtr unf)
{
	if(		(currac->classtype->aerobaticfactor == AEROBATIC_LOW) 		//CSB 13Jul00
		||	(currac->vel_ < currac->classtype->minvel)	)				//CSB 13Jul00
		return;															//CSB 13Jul00
		
		MANOEUVRE manoeuvre = MANOEUVRE_SELECT;
		MANOEUVRE goodmanoeuvre = MANOEUVRE_SELECT;
		if 	(currac->ai.combatskill >= SKILL_VETERAN)
			 goodmanoeuvre = MANOEUVRE_SPLITS;

		if 	(currac->ai.combatskill >= SKILL_REGULAR)
		{
//DEADCODE CSB 10/01/00 			if((currac->classtype->visible == F86) && (!Math_Lib.rnd(4)))	//CSB 08/07/99	
//DEADCODE CSB 10/01/00 				manoeuvre = MANOEUVRE_DIVINGSPIN;							//CSB 08/07/99	
//DEADCODE CSB 10/01/00 			else															//CSB 08/07/99	
			{
				RndVal	rndnum = Math_Lib.rnd();
				if	(rndnum < RND33PC)	//CSB 29/06/99	
					manoeuvre = MANOEUVRE_SCISSORS;
				else if	(rndnum < RND67PC)	//CSB 29/06/99	
					manoeuvre = MANOEUVRE_BREAKTURN;
				else
					manoeuvre = goodmanoeuvre;						  //RDH 15/06/99 //RDH 20/06/99
			}
		}
		Art_Int.SetEngage(currac,unf,manoeuvre,ANGLES_0Deg,ANGLES_0Deg, FALSE);

}
			

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindFreeAcInGroup
//Author		Craig Beeston
//Date			Tue 21 Mar 2000
//
//Description	Finds a member of the group who doesn't have an attacker
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStrucPtr AirStruc::FindFreeAcInGroup()
{
	AirStrucPtr backup;
	for(AirStrucPtr leadac = FindFormpos0(); leadac; leadac = leadac->fly.nextflight)
		for(AirStrucPtr ac = leadac; ac; ac = ac->Follower())
			if(!ac->Status.deadtime)
			{
				if(!ac->ai.attacker)
					return(ac);
				backup = ac;
			}
	return(backup);
}
