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
//Filename       spotted.cpp
//System         
//Author         R. Hyde 
//Date           Tue 3 Mar 1998
//Description    
//
//				These routines called from visiblecheck() in msgai.com
//
//				Note the data structure does not have the concept of elements
//				We have flights.
//				The code must compensate
//
//------------------------------------------------------------------------------
//	Both SpottedUnfriendly and AlertFighters can result in a force splitting (don't confuse with 
//	split manoeuvre)
//
//	The difference is that SpottedUnfirendly will result in leader set going and others remaining
//	and AlertFighter will result in a SendFlight, ie leader staying
//
//
//

//On moving from precombat to visible range need equivalent to SpottedUnfr
//	Check decoy
//	Explore FirstTactics
//	Consider starting BVR
//
//
//Notes on airstruc pointers
//
//for caller:
//	if caller->leader == null caller is element leader
//	if caller->Follower()
//		nex wingman in element
//
//
//
//There are 3 candidates for Group Leader:
//		currac
//		currac->leader
//		currac->fly.leadflight
//
//To find all fighter leaders
//		found = AirStruc::AircraftList
//
//		while found
//		{
//			if (found->formpos == 0)
//				this is a leader
//			found = found->nextmobile;
//		}
//	if leader of group escorting something else 
//		then leadflight points to escortee lead
//	else leadflight  == NULL
//
//can use leadelt() to find leader of next element up
//
//	VisibleCheck code is used for either group leader or any ac not information
//
//
#include	"dosdefs.h"
	#define F_COMMON
	#define F_GRAFIX
	#define F_BATTLE
#include	"files.g"
#include	"worldinc.h"
#include	"ai.h"
#include	"myerror.h"
#include	"mymath.h"
#include	"landscap.h"
#include	"ranges.h"
#include	"planetyp.h"
#include	"mytime.h"
#include	"flymodel.h"
#include	"persons2.h"
#include	"savegame.h"
#include	"miles.h"
//#include	"winmove.h"											//ARM 06Dec96
//TEMPCODE DAW 13/04/00 #include	"textref.h"
#include	"replay.h"
#include	"sqddiary.h"

extern ArtInt	Art_Int;

DECISIONAI(Rendezvous,AirStrucPtr);

DECISIONAI(DecideTopCover, AirStrucPtr);
OPTIONAI(SetUpTopCover, AirStrucPtr);
OPTIONAI(SetUpEngageFormation, AirStrucPtr);

DECISIONAI(SplitForce, AirStrucPtr);
OPTIONAI(SetUpEngageTrg, AirStrucPtr);
OPTIONAI(SetUpMeBombersYouFighters, AirStrucPtr);
OPTIONAI(SetUpMeFightersYouBombers, AirStrucPtr);

DECISIONAI(AttackingManoeuvre,AirStrucPtr);
OPTIONAI(SetupDiveAndZoom,AirStrucPtr)
OPTIONAI(SetupHeadOnAttack,AirStrucPtr)
OPTIONAI(SetupLineAbreast,AirStrucPtr)
OPTIONAI(SetupLineAstern,AirStrucPtr)
OPTIONAI(SetupVic,AirStrucPtr)
OPTIONAI(SetupSelectTarget,AirStrucPtr);

DECISIONAI(DefensiveManoeuvre1, AirStrucPtr);
OPTIONAI(SetupSandwich,AirStrucPtr);
OPTIONAI(SetupSplit,AirStrucPtr);
OPTIONAI(SetupTurnTowards,AirStrucPtr);

DECISIONAI(DefensiveManoeuvre2, AirStrucPtr);
OPTIONAI(SetUpDefensiveSplit, AirStrucPtr);
OPTIONAI(SetUpDefensiveSplitLeftHi, AirStrucPtr);
OPTIONAI(SetUpDefensiveSplitRightHi, AirStrucPtr);
OPTIONAI(SetUpDefensiveSplitBothHi, AirStrucPtr);
OPTIONAI(DoNothing,AirStrucPtr);

DECISIONAI(DefensiveManoeuvre110, AirStrucPtr);
OPTIONAI(SetUpLufberry,AirStrucPtr);

/////////////////////////////////////////////
//DEADCODE CSB 04/05/00 DECISIONAI(UnFriendlyFar, AirStrucPtr);
//DEADCODE CSB 04/05/00 DECISIONAI(PotentialBounce, AirStrucPtr);
//DEADCODE CSB 04/05/00 DECISIONAI(FriendliesUnderAttack, AirStrucPtr);

//DEADCODE CSB 21/01/00 OPTIONAI(SetUpPincerAttack, AirStrucPtr);
//DEADCODE CSB 21/01/00 OPTIONAI(SetUpMultiWave, AirStrucPtr);
//DEADCODE CSB 21/01/00 
//DEADCODE CSB 21/01/00 OPTIONAI(SetUpDefensiveSplit, AirStrucPtr);
//DEADCODE CSB 04/05/00 OPTIONAI(SendFlight, AirStrucPtr);
OPTIONAI(AllGo, AirStrucPtr);
OPTIONAI(RelaySighting, AirStrucPtr);
//DEADCODE CB 18/11/99 OPTIONAI(SetupRoundAbout,AirStrucPtr)


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedUnFriendly
//Author		R. Hyde 
//Date			RDH 20Jan99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::SpottedUnfriendly(AirStruc* caller,AirStruc* trg)
{
	if(caller->ShouldDumpAndRun(true, false, trg))
		caller->DumpAndRun();

//Stop repeated spot messages from bombers
//DeadCode CSB 1Nov00 	if(caller->classtype->aerobaticfactor == AEROBATIC_LOW)																						//CSB 4Aug00
	{																																			//CSB 4Aug00
		AirStrucPtr grouplead = caller;																											//CSB 4Aug00
		while((grouplead->fly.leadflight))// && (grouplead->classtype->aerobaticfactor == grouplead->fly.leadflight->classtype->aerobaticfactor))	//CSB 4Aug00
			grouplead = grouplead->fly.leadflight;																								//CSB 4Aug00
		if((!grouplead->fly.numinsag) && (grouplead->fly.expandedsag))																			//CSB 4Aug00
			grouplead = grouplead->fly.expandedsag;																								//CSB 4Aug00
																																				//CSB 4Aug00
		AirStrucPtr trglead = trg;																												//CSB 4Aug00
		while((trglead->fly.leadflight) && (trglead->classtype->aerobaticfactor == trglead->fly.leadflight->classtype->aerobaticfactor))		//CSB 4Aug00
			trglead = trglead->fly.leadflight;																									//CSB 4Aug00
		if((!trglead->fly.numinsag) && (trglead->fly.expandedsag))																				//CSB 4Aug00
			trglead = trglead->fly.expandedsag;																									//CSB 4Aug00
																																				//CSB 4Aug00
//DeadCode CSB 2Nov00 		if(		(grouplead->ai.spottedunfriendly[0] == trglead) || (grouplead->ai.spottedunfriendly[1] == trglead)								//CSB 4Aug00
//DeadCode CSB 2Nov00 			||	(grouplead->ai.spottedunfriendly[2] == trglead) || (grouplead->ai.spottedunfriendly[3] == trglead)	)							//CSB 4Aug00
//DeadCode CSB 2Nov00 			return(false);																														//CSB 4Aug00
//DeadCode CSB 2Nov00 		else																																	//CSB 4Aug00
		{
			grouplead->ai.spottedunfriendly[3] = grouplead->ai.spottedunfriendly[2];
			grouplead->ai.spottedunfriendly[2] = grouplead->ai.spottedunfriendly[1];
			grouplead->ai.spottedunfriendly[1] = grouplead->ai.spottedunfriendly[0];
			grouplead->ai.spottedunfriendly[0] = trglead;																									//CSB 4Aug00
		}
	}																																			//CSB 4Aug00

	ScriptTables script = ChooseSpottedScript(caller, trg);
	AirStrucPtr lead = caller->FindFormpos0();
	if((lead->fly.leadflight) && (lead->fly.leadflight->classtype->aerobaticfactor == caller->classtype->aerobaticfactor))
	{
		AirStrucPtr leadac = lead->fly.leadflight->GetLeadAc();
		if((leadac->movecode != AUTO_COMBAT) && (leadac->movecode != AUTO_PRECOMBAT) && (leadac->ai.manoeuvre != MANOEUVRE_SCREWYOUGUYSIMGOINGHOME))
			lead = leadac;
	}

	trg = trg->GetLeadAc();

	while((trg->fly.leadflight) && (!trg->fly.leadflight->GetLeadAc()->IsOutNumberedBy(1.0)))
		trg = trg->fly.leadflight->GetLeadAc();

//DeadCode CSB 11Oct00 	if(trg->IsOutNumberedBy(1.0))
//DeadCode CSB 11Oct00 		return(false);

//DeadCode CSB 11Oct00 	if((trg->classtype->aerobaticfactor == AEROBATIC_HIGH) && (trg->fly.leadflight))
//DeadCode CSB 11Oct00 		trg = trg->fly.leadflight->GetLeadAc();	//Find escortee

//DeadCode CSB 11Oct00 	if(trg->IsOutNumberedBy(1.0))
//DeadCode CSB 11Oct00 		return(false);

	_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_SPOT, caller, trg, lead));

	if(caller != lead)
  	{
		if(		(!Save_Data.gamedifficulty[GD_AUTOVECTORING])
			&&	((lead == Persons2::PlayerGhostAC) || (lead == Persons2::PlayerSeenAC))		)
			return(false);

		if((ArtInt::CountSquadronSize(trg) == 1) || (!Math_Lib.rnd(3)))
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_IHAVEIT, MSG_SPOT_REPLY, lead, trg, caller)); 
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_IVE_GOT_THEM, MSG_SPOT_REPLY, lead, trg, caller)); 
		caller = lead;
	}

	bool retval;
//TempCode JIM 28Mar100 	if( ((caller->duty & PACK_AM_MASK) == PACK_AM_LWSTART && caller->duty!=PACK_AM_DECOYPATROL) || (caller->classtype->aerobaticfactor == AEROBATIC_LOW) )//JIM 28Mar100
	if(		(caller->classtype->aerobaticfactor == AEROBATIC_LOW)
//DeadCode CSB 24Aug00 		||	((caller->classtype->aerobaticfactor == AEROBATIC_MEDIUM) && (FindEscort(caller)))	)
		||	((caller->classtype->aerobaticfactor == AEROBATIC_MEDIUM) && (trg->classtype->aerobaticfactor == AEROBATIC_HIGH))	
		||	(caller->GroupShouldGoHome(0.5)) || (caller->ai.manoeuvre == MANOEUVRE_SCREWYOUGUYSIMGOINGHOME)	)
		retval = AlertFighters(caller, trg, caller);
	else
	{
		InterceptRangeFromTo(caller, trg);
		if(		(trg->ai.unfriendly) && (trg->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			&&	(AirStrucPtr(trg->ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW)	)
		{
			AirStrucPtr callee = caller->FindBuddy();
			if(callee)
				if(Math_Lib.rnd(2))
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_CALLEE_LETSHELP, MSG_SPOT_ACTION, caller, trg, callee));
				else
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CALLER_WILLHELP, MSG_SPOT_ACTION, caller, trg, callee));
		}

		int callernum = CountFormationSize(caller);
		if(caller->fly.leadflight)
			callernum -= CountSquadronSize(caller->fly.leadflight);

		UnitSize size;
		AirStrucPtr ic2 = SplitUnit(caller, size);
		if(		((ic2) && (ic2 != caller) && (callernum >= 6) && (callernum >= CountFormationSize(trg)))
			||	((size == UNIT_RAF_WING) || (size == UNIT_LUF_GESCHWADER) || (size == UNIT_LUF_GRUPPEN))	)
		   	retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CLEAR, caller, trg, caller), DecideTopCover);
		else
		   	retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CLEAR, caller, trg, caller), SetUpEngageFormation);
//DEADCODE CSB 08/02/00 			retval = EngageFormation(caller, trg);	

//DEADCODE CSB 21/01/00 		//Find the formation leader or escortee
//DEADCODE CSB 21/01/00 		for(;;)
//DEADCODE CSB 21/01/00 		{
//DEADCODE CSB 21/01/00 			if(		(trg->classtype->aerobaticfactor == AEROBATIC_HIGH)
//DEADCODE CSB 21/01/00 				&&	(trg->fly.leadflight)
//DEADCODE CSB 21/01/00 				&&	(trg->Distance3D(&trg->fly.leadflight->World) < 50000) )
//DEADCODE CSB 21/01/00 					trg = trg->fly.leadflight;
//DEADCODE CSB 21/01/00 			else
//DEADCODE CSB 21/01/00 				break;
//DEADCODE CSB 21/01/00 		}
//DEADCODE CSB 21/01/00 
//DEADCODE CSB 21/01/00 		retval = ChooseManoeuvre(caller, trg, true);
	}
	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseSpottedScript
//Author		R. Hyde 
//Date			RDH 20Jan99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ScriptTables ArtInt::ChooseSpottedScript(AirStrucPtr caller, AirStrucPtr trg)
{
	ScriptTables script = SCRIPT_NULL;
	const SWord RelPosAng = ANGLES_10Deg;
	caller->InterceptandRange(trg);
	SWord dhdg = AbsAngle(caller->HdgIntercept - caller->hdg);

	if(trg->classtype->aerobaticfactor == AEROBATIC_LOW)
		script = SCRIPT_BOMBERS;
	else if(	(trg->movecode == AUTO_COMBAT)
			&&	(trg->ai.unfriendly) && (trg->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			&&	(AirStrucPtr(trg->ai.unfriendly)->FindFormpos0() != caller->FindFormpos0())		)
	{
		AirStrucPtr trgunf = AirStrucPtr(trg->ai.unfriendly);
		if((CountSquadronSize(trgunf) == 1) && (trgunf->World.Y < caller->World.Y))
			script = SCRIPT_INTROUBLE;
		else if(trgunf->classtype->aerobaticfactor == AEROBATIC_LOW)
			script = SCRIPT_BOMBERUNDERATTACK;
		else if(caller->nationality == NAT_RAF)
		{
			if(CountFormationSize(trgunf) < CountFormationSize(trg))
				script = SCRIPT_FIGHTERSNEEDHELP;
			else if(Math_Lib.rnd(2))
				script = SCRIPT_DOGFIGHT;
			else
				script = SCRIPT_FRIENDLIES;
		}
		else
		{
//DeadCode CSB 6Sep00 			if(Math_Lib.rnd(2))
//DeadCode CSB 6Sep00 				script = SCRIPT_DOGFIGHTLW;
//DeadCode CSB 6Sep00 			else
				script = SCRIPT_FRIENDLIES;
		}
	}
	else
	{
		if((caller->movecode == AUTO_PRECOMBAT) || (caller->movecode == AUTO_COMBAT))
		{
			if(caller->Distance3DSquared(&trg->World) < FP(METRES1000) * FP(METRES1000))
				script = SCRIPT_MOREBANDITSEXCITED;
			else if((trg->World.Y > caller->World.Y) && (trg->vel_y < -500000))
				script = SCRIPT_COMINGDOWN;
			else if(Math_Lib.rnd(1))
			{
				if(dhdg < ANGLES_45Deg)	script = SCRIPT_BANDITAHEAD;
				else					script = SCRIPT_BANDIT_POS;
			}
			else 
				script = SCRIPT_MOREBANDITS;
		}
		else
		{
			if(!Math_Lib.rnd(10))
			{
				WorldStuff*	worldptr = mobileitem::currworld;
				FP dotprod =  (trg->World.X - caller->World.X) * (worldptr->sunpos.X - caller->World.X)
							+ (trg->World.Y - caller->World.Y) * (worldptr->sunpos.Y - caller->World.Y)
							+ (trg->World.Z - caller->World.Z) * (worldptr->sunpos.Z - caller->World.Z);
				if(dotprod > 0)
				{
					dotprod = (dotprod * dotprod)
								/ (caller->Distance3DSquared(&worldptr->sunpos) * caller->Distance3DSquared(&trg->World));
					if(dotprod > 0.9)
						if(CountSquadronSize(trg) > 1)
							script = SCRIPT_PLURAL_AIRCRAFT_EXCLAIM_INSUN;
						else
							script = SCRIPT_AIRCRAFTEXCLAIMINSUN;
				}
				if(script == SCRIPT_NULL)
					if(CountSquadronSize(trg) > 1)
						script = SCRIPT_PLURAL_AIRCRAFT_EXCLAIM;
					else
						script = SCRIPT_AIRCRAFTEXCLAIM;
			}
			else if(	(dhdg < RelPosAng) || (dhdg > ANGLES_180Deg - RelPosAng)
					||	((dhdg > ANGLES_90Deg - RelPosAng) && (dhdg < ANGLES_90Deg + RelPosAng))	)
				script = SCRIPT_BANDIT_RELPOS;
			else
				if(dhdg < ANGLES_45Deg)
				{
					if((caller->nationality == NAT_RAF))
						script = SCRIPT_BANDITSAHEADRAF;
					else
						script = SCRIPT_BANDITSAHEADLW;
				}
				else if(dhdg > ANGLES_135Deg)
				{
					if(caller->Distance3DSquared(&trg->World) < FP(METRES1000) * FP(METRES1000))
					{
						if((caller->nationality == NAT_RAF))
							script = SCRIPT_BANDITSBEHINDEXCITEDRAF;
						else
							script = SCRIPT_BANDITSBEHINDEXCITEDLW;
					}
					else if((caller->nationality == NAT_RAF))
						script = SCRIPT_BANDITSBEHINDRAF;
					else
						script = SCRIPT_BANDITSBEHINDLW;
				}
				else
				{
					if(caller->Distance3DSquared(&trg->World) < FP(METRES1000) * FP(METRES1000))
					{
						if((caller->nationality == NAT_RAF))
							script = SCRIPT_BANDITSABEAMEXCITEDRAF;
						else
							script = SCRIPT_BANDITSABEAMEXCITEDLW;
					}
					else if((caller->nationality == NAT_RAF))
						script = SCRIPT_BANDITSABEAMRAF;
					else
						script = SCRIPT_BANDITSABEAMLW;
				}
		}
	}

	return(script);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeaveTopCover
//Author		Craig Beeston
//Date			21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
TABLEAI(DecideTopCover, AirStrucPtr)
{
	{PHRASE_S_TOPCOVER,			&SetUpTopCover,			SCRIPT_NULL},	
	{PHRASE_S_ALLATTACKBOMBERS,	&SetUpEngageFormation,	SCRIPT_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};

INSTANCEAI(DecideTopCover, AirStrucPtr)
{
	bool retval;
	int numenemyfighters = CountFormationSize(trg);
	if(trg->classtype->aerobaticfactor != AEROBATIC_HIGH)
		numenemyfighters -= CountSquadronSize(trg);

	int numourfighters = CountFormationSize(caller);
	AirStrucPtr formlead = caller;
	if(formlead->fly.leadflight)
		formlead = formlead->fly.leadflight;
	if(formlead->classtype->aerobaticfactor != AEROBATIC_HIGH)
		numourfighters -= CountSquadronSize(formlead);

	if(((numenemyfighters) && (!caller->fly.leadflight) && (numourfighters > numenemyfighters))/* || (FindEscort(caller))*/)
		retval = LeaveTopCover(caller, trg);
	else
		retval = EngageFormation(caller, trg);
	return(retval);
}

INSTANCEAI(SetUpTopCover, AirStrucPtr)
{
	return(LeaveTopCover(caller, trg));
}

INSTANCEAI(SetUpEngageFormation, AirStrucPtr)
{
	return(EngageFormation(caller, trg));
}

bool ArtInt::LeaveTopCover(AirStruc* caller, AirStruc* trg)
{
	UnitSize unit;
	ScriptTables script = SCRIPT_NULL;
	AirStrucPtr ldr_topcover = SplitUnit(caller, unit);
	AirStrucPtr ldr_attack	 = caller;

	if(ldr_topcover)
	{
		bool bombers = false;
		if(trg->classtype->aerobaticfactor < AEROBATIC_HIGH)
			bombers = true;
		bool fighters = false;
		if((!bombers) || (FindEscort(trg)))
			fighters = true;

		int attack_duty   = ldr_attack->ai.submethod & ai_info::SM_MASK_A2A;
		int topcover_duty = ldr_topcover->ai.submethod & ai_info::SM_MASK_A2A;

		if(		((bombers) && (fighters)  && (attack_duty != 0/*SM_ANYA2A*/) 	  && (topcover_duty == 0/*SM_ANYA2A*/))
			||	((bombers) && (!fighters) && (attack_duty == 1/*SM_NOTBOMBERS*/)  && (topcover_duty != 1/*SM_NOTBOMBERS*/))
			||	((!bombers) && (fighters) && (attack_duty == 2/*SM_NOTFIGHTERS*/) && (topcover_duty != 2/*SM_NOTFIGHTERS*/))	)
		{
			AirStrucPtr temp = ldr_topcover;
			ldr_topcover = ldr_attack;
			ldr_attack = temp;
		}

		switch(unit)
		{
			case UNIT_RAF_WING:			script = SCRIPT_WINGTOPCOVER;			break;
			case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONTOPCOVER;		break;
			case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTTOPCOVER;			break;
		}
		_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_TOP_COVER, caller, NULL, ldr_topcover)); 
		
		for(bool stoploop = false; (ldr_topcover) && (!stoploop); ldr_topcover = ldr_topcover->fly.nextflight)
			for(AirStrucPtr ac = ldr_topcover; (ac) && (!stoploop); ac = ac->Follower())
			{
				if(ac == ldr_attack)
					stoploop = true;
				else
					SetEngage(ac, trg, MANOEUVRE_FORCETOPCOVER, ANGLES_0Deg, ANGLES_0Deg, false);
			}
	}
	return(EngageFormation(ldr_attack, trg));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EngageFormation
//Author		Craig Beeston 
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::EngageFormation(AirStruc* caller, AirStruc* trg)
{
	bool retval;
	if(trg->classtype->aerobaticfactor == AEROBATIC_HIGH)
		retval = EngageTrg(caller, trg);
	else
	{
		UnitSize size;
		AirStrucPtr ic2 = SplitUnit(caller, size);
		if((ic2) && (ic2 != caller) && (FindEscort(trg)))
		   	retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CLEAR, caller, trg, caller), SplitForce);
		else
			retval = EngageTrg(caller, trg);
	}

	if (caller->nationality == NAT_RAF)								//RJS 09Mar00
		Squad_Diary.ArrivedAtTarget(caller,trg);					//RJS 09Mar00

	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SplitForce
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
TABLEAI(SplitForce, AirStrucPtr)
{
	{PHRASE_S_ALLATTACKBOMBERS,			&SetUpEngageTrg,			SCRIPT_NULL},	
	{PHRASE_S_ATTACKBOMBERSANDFIGHTERS,	&SetUpMeBombersYouFighters,	SCRIPT_NULL},
	{PHRASE_S_ATTACKFIGHTERSANDBOMBERS,	&SetUpMeFightersYouBombers,	SCRIPT_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};

INSTANCEAI(SplitForce, AirStrucPtr)
{
	bool retval;
//DeadCode CSB 22Jun00 	int numbombers  = CountSquadronSize(trg);
//DeadCode CSB 22Jun00 	int numfighters = CountFormationSize(trg) - numbombers;
//DeadCode CSB 22Jun00 	int numcaller	= CountFormationSize(caller);
//DeadCode CSB 22Jun00 
//DeadCode CSB 22Jun00 	if(numfighters > numcaller)
	{
		UnitSize unit;
		AirStrucPtr ldr_fighters = SplitUnit(caller, unit);
		AirStrucPtr ldr_bombers	 = caller;

		int fighters_duty = ldr_fighters->ai.submethod & ai_info::SM_MASK_A2A;
		int bombers_duty  = ldr_bombers->ai.submethod & ai_info::SM_MASK_A2A;

		if(		((fighters_duty == 2/*SM_NOTFIGHTERS*/) && (bombers_duty != 2/*SM_NOTFIGHTERS*/))
			||	((bombers_duty  == 1/*SM_NOTBOMBERS*/) && (fighters_duty != 1/*SM_NOTBOMBERS*/))	)
			retval = MeFightersYouBombers(caller, trg);	
		else	
			retval = MeBombersYouFighters(caller, trg);	
	}
//DeadCode CSB 22Jun00 	else
//DeadCode CSB 22Jun00 		retval = EngageTrg(caller, trg);

	return(retval);
}

INSTANCEAI(SetUpMeBombersYouFighters, AirStrucPtr)
{
	return(MeBombersYouFighters(caller, trg));
}

INSTANCEAI(SetUpMeFightersYouBombers, AirStrucPtr)
{
	return(MeFightersYouBombers(caller, trg));
}


INSTANCEAI(SetUpEngageTrg, AirStrucPtr)
{
	UnitSize unit;
	ScriptTables script = SCRIPT_NULL;
	AirStrucPtr msgcallee = SplitUnit(caller, unit);
	if(msgcallee)
	{
		switch(unit)
		{
			case UNIT_RAF_WING:			script = SCRIPT_WINGALLBOMBERS;			break;
			case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONALLBOMBERS;		break;
			case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTALLBOMBERS;		break;
		}

		_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_INITIALCOMBAT, caller, trg, msgcallee));
	}
	return(EngageTrg(caller, trg));
}


bool ArtInt::MeFightersYouBombers(AirStruc* caller, AirStruc* trg)
{
	UnitSize unit;
	ScriptTables script = SCRIPT_NULL;
	AirStrucPtr ldr_bomb = SplitUnit(caller, unit);

	switch(unit)
	{
		case UNIT_RAF_WING:			script = SCRIPT_WINGFIGHTERS;		break;
		case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONFIGHTERS;	break;
		case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTFIGHTERS;		break;
	}

	_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_SPLIT_FORCE, caller, trg, ldr_bomb));

	EngageTrg(ldr_bomb, trg);

	return(EngageTrg(caller, FindEscort(trg)));
}


bool ArtInt::MeBombersYouFighters(AirStruc* caller, AirStruc* trg)
{
	UnitSize unit;
	ScriptTables script = SCRIPT_NULL;
	AirStrucPtr ldr_fight = SplitUnit(caller, unit);

	switch(unit)
	{
		case UNIT_RAF_WING:			script = SCRIPT_WINGBOMBERS;		break;
		case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONBOMBERS;	break;
		case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTBOMBERS;		break;
	}

	AirStrucPtr escort = FindEscort(trg);
	_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_SPLIT_FORCE, caller, escort, ldr_fight));

	EngageTrg(ldr_fight, escort);

	return(EngageTrg(caller, trg));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EngageTrg
//Author		Craig Beeston 
//Date			Fri 21 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::EngageTrg(AirStruc* caller, AirStruc* trg)
{
	bool retval;
	bool chosen = false;
	caller->ai.manoeuvre = MANOEUVRE_SELECT;

	if(trg->classtype->aerobaticfactor == AEROBATIC_HIGH)
	{
		SWord cdh = AbsAngle(SWord(caller->HdgIntercept - caller->hdg));
		SWord tdh = AbsAngle(SWord(caller->HdgIntercept + ANGLES_180Deg - trg->hdg));

		if((cdh > ANGLES_90Deg) && (tdh < ANGLES_90Deg))
		{
			if(/*	   ((caller->formation == SQUAD_FINGERFOUR) || (caller->formation == SQUAD_SHWARME))
				&&*/ (	((trg->leader)			&& (trg->Distance3D(&trg->Leader()->World)		 < 10000))
					||	((trg->fly.leadflight)	&& (trg->Distance3D(&trg->fly.leadflight->World) < 10000))
					||	((trg->follower)		&& (trg->Distance3D(&trg->Follower()->World)	 < 10000))
					||	((trg->fly.nextflight)	&& (trg->Distance3D(&trg->fly.nextflight->World) < 10000))	)	)

			   	retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CLEAR, caller, trg, caller), DefensiveManoeuvre1);
			else
			   	retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CLEAR, caller, trg, caller), DefensiveManoeuvre2);
			chosen = true;
		}
	}

	if(!chosen)
	{
		retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CLEAR, caller, trg, caller), AttackingManoeuvre);
		AirStrucPtr callee = caller->FindBuddy();
		if(callee)
		{
			ScriptTables script;
			switch(Math_Lib.rnd(2))
			{
				case 0:		
					if(caller->nationality == NAT_RAF)
						script = SCRIPT_SAFETYCATCHES;
					else
						script = SCRIPT_SAFETYCATCHES_LW;
					break;
				case 1:
					if(CountFormationSize(trg) > 12)	script = SCRIPT_DIRECTION_DOZENS;
					else								script = SCRIPT_GETINTOTHEM;
					break;
//DeadCode CSB 19Sep00 				case 1:		script = SCRIPT_GETINTOTHEM;		break;
//DeadCode CSB 19Sep00 				case 2:		if(CountFormationSize(trg) > 12)	script = SCRIPT_DIRECTION_DOZENS;
//DeadCode CSB 19Sep00 							else								script = SCRIPT_GETINFIRST;
//DeadCode CSB 19Sep00 							break;
			}
			_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_INITIAL_COMBAT, caller, trg, callee));
		}
	}

	//Set rest of group

	return(retval);
}


//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
TABLEAI(AttackingManoeuvre,AirStrucPtr)
{
	{PHRASE_ITSDIVEANDZOOM,			&SetupDiveAndZoom,	SCRIPT_ITSDIVEANDZOOM},	
	{PHRASE_ITSHEADONATT,			&SetupHeadOnAttack,	SCRIPT_ITSHEADONATT},
	{PHRASE_ITSLINEABREAST,			&SetupLineAbreast,	SCRIPT_ITSLINEABREAST},
	{PHRASE_ITSLINEASTERN,			&SetupLineAstern,	SCRIPT_ITSLINEASTERN},
	{PHRASE_ITSAVIC,				&SetupVic,			SCRIPT_ITSAVIC},
	{PHRASE_SELECTYOUROWNTARGETS,	&SetupSelectTarget,	SCRIPT_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};

INSTANCEAI(AttackingManoeuvre,AirStrucPtr)
{
	tGroupLevel group = GroupLevel(caller);
	bool retval = false;
	ScriptTables script, script2;

	if(EngageAppropriate(caller, trg))
	{
		script = (ScriptTables)PHRASE_SELECTYOUROWNTARGETS;
		if (caller->fly.nextflight)
			callee = caller->fly.nextflight;
		else if( (caller->ai.elementtactics != WELDEDWING) && (caller->Follower()) )
			callee = caller->Follower();
		else
			callee = NULL;

		if((trg->classtype->aerobaticfactor != AEROBATIC_LOW) || (caller == Persons2::PlayerGhostAC))
			retval = SendMsgAndCall(MESSAGE_STRUC(script, MSG_ATTACK_METHOD, caller, trg, caller), SetupSelectTarget);	
		else
		{
			if(caller->ai.firsttactic == TACTIC_NULL)
				switch(caller->ai.submethod & ai_info::SM_MASK_FIRST)
				{
					case 8/*SM_DIVEANDZOOM*/:	caller->ai.firsttactic = TACTIC_DIVEANDZOOM;	break;
					case 16/*SM_HEADON*/:		caller->ai.firsttactic = TACTIC_HEADONATTACK;	break;
					case 24/*SM_LINEABREAST*/:	caller->ai.firsttactic = TACTIC_LINEABREAST;	break;
					case 32/*SM_LINEASTERN*/:	caller->ai.firsttactic = TACTIC_LINEASTERN;		break;
					case 40/*SM_VIC*/:			caller->ai.firsttactic = TACTIC_VICATTACK;		break;
					case 48/*SM_INDIVIDUAL*/:	caller->ai.firsttactic = TACTIC_INDIVIDUAL;		break;
				}

			if(caller->ai.firsttactic == TACTIC_DIVEANDZOOM)
				retval = SendMsgAndCall(MESSAGE_STRUC(script, MSG_ATTACK_METHOD, caller, trg, caller), SetupDiveAndZoom);	
			else if(caller->ai.firsttactic == TACTIC_LINEABREAST)
				retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_NULL,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupLineAbreast);	
			else if(caller->ai.firsttactic == TACTIC_LINEASTERN)
				retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_NULL,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupLineAstern);	
			else if(caller->ai.firsttactic == TACTIC_HEADONATTACK)
				retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_NULL,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupHeadOnAttack);	
			else if(caller->ai.firsttactic == TACTIC_VICATTACK)
				retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_NULL,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupVic);	
			else if(caller->ai.firsttactic == TACTIC_INDIVIDUAL)
				retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_NULL,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupSelectTarget);	
			else
			{
				switch(Math_Lib.rnd(5))
				{
					case 0:
					{
						if((trg->classtype->aerobaticfactor == AEROBATIC_LOW) && (CountSquadronSize(caller) > 1) && (CountSquadronSize(trg) > 1))
							retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupHeadOnAttack);	
						else
							retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupSelectTarget);	
						break;
					}
					case 1:	{	retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupDiveAndZoom);	break;	}
					case 2:	{	retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupLineAbreast);	break;	}
					case 3:	{	retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupLineAstern);	break;	}
					case 4:	{	retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_CHOSENMANOEUVRE,caller,trg,caller), SetupVic);			break;	}
				}
			}
		}
#pragma warnmsg ("RadioChat:code commented out")
	}
	else
	{
//DEADCODE RDH 07/12/99 		if (trg->ai.eventlog->stage < EventLog::SEENBYOTHERS)
//DEADCODE RDH 07/12/99 		{
//DEADCODE RDH 07/12/99 		}
//DEADCODE RDH 07/12/99 		   	retval = SendMsgAndCall(MESSAGE_STRUC(OLDPHRASE_IGNOREFORNOW,MSG_SPOTTEDASNEWUNFRIENDLY,caller,trg,caller->Follower()),DoNothing);
//DEADCODE RDH 07/12/99 			if (caller->IsUsingPilotedAcLog())
//DEADCODE RDH 07/12/99 				Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
//DEADCODE RDH 07/12/99 			else
//DEADCODE RDH 07/12/99 				Persons2::UpdateLog(trg,0,EventLog::SEENBYOTHERS);
//DEADCODE RDH 07/12/99 
	}

	return(retval);
}


//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date																  //RDH 24/02/99
//
//Description			   red manoeuvre
//			   	
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupDiveAndZoom,AirStrucPtr)
{
	if(trg->classtype->aerobaticfactor == AEROBATIC_LOW)
		trg = FindTailie(trg);
	caller->SetFollowersTactic(TACTIC_DIVEANDZOOM);
	SetEngage(caller,trg, MANOEUVRE_DIVEANDZOOM,ANGLES_0Deg,ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_DIVEANDZOOM,ANGLES_0Deg,ANGLES_0Deg,FALSE);
 	return(true);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpHeadOnAttack
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupHeadOnAttack, AirStrucPtr)
{
	caller->SetFollowersTactic(TACTIC_HEADONATTACK);
	SetEngage(caller, trg, MANOEUVRE_HEADONATTACK, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller, trg, MANOEUVRE_HEADONATTACK, ANGLES_0Deg, ANGLES_0Deg, FALSE);
 	return(true);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupLineAbreast
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupLineAbreast,AirStrucPtr)
{
	while(trg->fly.nextflight)
		trg = trg->fly.nextflight;

	caller->SetFollowersTactic(TACTIC_LINEABREAST);
	SetEngage(caller, trg, MANOEUVRE_LINEABREAST, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller, trg, MANOEUVRE_LINEABREAST, ANGLES_0Deg, ANGLES_0Deg, FALSE);
 	return(true);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupLineAstern
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupLineAstern,AirStrucPtr)
{
	while(trg->fly.nextflight)
		trg = trg->fly.nextflight;

	caller->SetFollowersTactic(TACTIC_LINEASTERN);
	SetEngage(caller, trg, MANOEUVRE_LINEASTERN, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller, trg, MANOEUVRE_LINEASTERN, ANGLES_0Deg, ANGLES_0Deg, FALSE);
 	return(true);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpVic
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupVic, AirStrucPtr)
{
	while(trg->fly.nextflight)
		trg = trg->fly.nextflight;

	caller->SetFollowersTactic(TACTIC_VICATTACK);
	for(AirStrucPtr	nf = caller; nf; nf = nf->fly.nextflight)
		for(AirStrucPtr f = nf; f; f = f->Follower())
			if(f->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER)
			{
				AirStrucPtr unf = trg;
				if(f->position())
					for(SWord  i = 0; i < f->position(); i++)
						if(unf->follower)
							unf = unf->Follower();

				SetEngage(f, unf, MANOEUVRE_VICATTACK, ANGLES_0Deg, ANGLES_0Deg, FALSE);
			}

	return(true);
}


//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupSelectTarget,AirStrucPtr)
{
	if(Math_Lib.rnd(2))
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SELECTYOUROWNTARGETS, MSG_INITIALCOMBAT, caller, trg, caller));
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_CALLERGROUP_SELECT_TARGET, MSG_INITIALCOMBAT, caller, trg, caller));

	AirStruc* follower = caller->Follower();
	if (	(follower)	&& (caller->ai.elementtactics == WELDEDWING))
 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COVERME, MSG_FOLLOWME, caller, NULL, follower));

	if (caller->IsUsingPilotedAcLog())
		if (!trg->IsUsingPilotedAcLog())
			 Persons2::UpdateLog(trg,0,EventLog::ATTACKED);

	caller->SetFollowersTactic(TACTIC_NULL);
	for(AirStrucPtr nf = caller; (nf) && (nf->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER); nf = nf->fly.nextflight)
		for(AirStrucPtr ac = nf; (ac) && (ac->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER); ac = ac->Follower())
		{
			AirStrucPtr tnf, tac;
			AirStrucPtr mytarget = NULL;
			for(tnf = trg; (tnf) && (!mytarget); tnf = tnf->fly.nextflight)
				for(tac = tnf; (tac) && (!mytarget); tac = tac->Follower())
					if((!tac->ai.attacker) && (!tac->Status.deadtime))
						mytarget = tac;

			if(!mytarget)
				mytarget = trg;

//DeadCode CSB 18Sep00 			SetEngage(ac, mytarget, MANOEUVRE_SELECT, ANGLES_0Deg, ANGLES_0Deg, FALSE);
			SetEngage(ac, mytarget, MANOEUVRE_PEELOFF, ANGLES_0Deg, ANGLES_0Deg, FALSE);
		}
 	return(true);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
TABLEAI(DefensiveManoeuvre1, AirStrucPtr)
{
	{PHRASE_S_SANDWICH,			&SetupSandwich,		SCRIPT_CALLEE_SANDWICH},
	{PHRASE_DEFENSIVESPLIT,		&SetupSplit,		SCRIPT_NULL},
	{PHRASE_S_TURNIN,			&SetupTurnTowards,	SCRIPT_CALLEE_TURNIN},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};

INSTANCEAI(DefensiveManoeuvre1, AirStrucPtr)
{
	bool retval;

	if(EngageAppropriate(caller, trg))
	{
		SWord rnd = Math_Lib.rnd(4);

		if( (rnd == 0) || ((rnd == 3) && (caller->ai.combatskill < SKILL_REGULAR)) )
			retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_DEFENSIVESPLIT, MSG_ATTACK_METHOD, caller, trg, caller), SetupSplit);
		else if( (rnd == 1) || ((rnd == 3) && (caller->ai.combatskill < SKILL_ACE)) )
			retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CLEAR, caller, trg, caller), SetupTurnTowards);
		else
			retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CLEAR, caller, trg, caller), SetupSandwich);
	}
 	else
 	   	retval = SendMsgAndCall(MESSAGE_STRUC(OLDPHRASE_IGNOREFORNOW,MSG_SPOTTEDASNEWUNFRIENDLY,caller,trg,caller),DoNothing);

	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpSandwich
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupSandwich, AirStrucPtr)
{
	SetEngage(caller, trg, MANOEUVRE_BREAK90, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller, trg, MANOEUVRE_TURNINGFIGHT, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	return(false);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetupTurnTowards
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupTurnTowards, AirStrucPtr)
{
	SetEngage(caller, trg, MANOEUVRE_TURNINGFIGHT, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller, trg, MANOEUVRE_TURNINGFIGHT, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	return(true);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpSplit
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetupSplit, AirStrucPtr)
{
	ScriptTables script = SCRIPT_NULL;
	UnitSize unit;
	AirStrucPtr msgcallee = SplitUnit(caller, unit);

	if((caller->nationality == NAT_LUF) || (!Math_Lib.rnd(5)))
		script = SCRIPT_CALLER_GROUP_SPLIT;
	else
		switch(unit)
		{
			case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLIT;			break;
			case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLIT;		break;
			case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLIT;		break;
			case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLIT;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_GRUPPEN:		script = SCRIPT_WINGDEFENSIVESPLIT;			break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_STAFFEL:		script = SCRIPT_SQUADRONDEFENSIVESPLIT;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_SCHWARME:		script = SCRIPT_FLIGHTDEFENSIVESPLIT;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_ROTTE:		script = SCRIPT_SECTIONDEFENSIVESPLIT;		break;
		}

	_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_INITIALCOMBAT, caller, trg, msgcallee));

	DefensiveSplit(caller, trg, ANGLES_0Deg, ANGLES_0Deg);
	return(true);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
TABLEAI(DefensiveManoeuvre2, AirStrucPtr)
{
	{PHRASE_DEFENSIVESPLIT,				&SetUpDefensiveSplit,			PHRASE_NULL},
	{PHRASE_S_DEFENSIVESPLITLEFTHI,		&SetUpDefensiveSplitLeftHi,		PHRASE_NULL},
	{PHRASE_S_DEFENSIVESPLITRIGHTHI,	&SetUpDefensiveSplitRightHi,	PHRASE_NULL},
	{PHRASE_S_DEFENSIVESPLITBOTHHI,		&SetUpDefensiveSplitBothHi,		PHRASE_NULL},
	{PHRASE_S_SELECTOWNTRG,				&SetupSelectTarget,				PHRASE_NULL},
	{PHRASE_NULL,						&DoNothing,						PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};

INSTANCEAI(DefensiveManoeuvre2, AirStrucPtr)
{
	bool retval;

	if(EngageAppropriate(caller, trg))
	{
		UnitSize unit;
		AirStrucPtr ac2 = SplitUnit(caller, unit);
		switch(Math_Lib.rnd(5))
		{
			case 0:
			{	ScriptTables script = SCRIPT_CALLER_GROUP_SPLIT;
				switch(unit)
				{
					case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLIT;			break;
					case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLIT;		break;
					case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLIT;		break;
					case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLIT;		break;
				}
				retval = SendMsgAndCall(MESSAGE_STRUC(script, MSG_CHOSENMANOEUVRE, caller, trg, caller), SetUpDefensiveSplit);
				break;
			}
			case 1:
			{
				ScriptTables script = SCRIPT_CALLER_GROUP_SPLIT_LEFTHI;
				switch(unit)
				{
					case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLITLEFTHI;			break;
					case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLITLEFTHI;		break;
					case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLITLEFTHI;			break;
					case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLITLEFTHI;		break;
				}
				retval = SendMsgAndCall(MESSAGE_STRUC(script, MSG_CHOSENMANOEUVRE, caller, trg, caller), SetUpDefensiveSplitLeftHi);
				break;
			}
			case 2:
			{
				ScriptTables script = SCRIPT_CALLER_GROUP_SPLIT_RIGHTHI;
				switch(unit)
				{
					case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLITRIGHTHI;			break;
					case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLITRIGHTHI;		break;
					case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLITRIGHTHI;		break;
					case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLITRIGHTHI;		break;
				}
				retval = SendMsgAndCall(MESSAGE_STRUC(script, MSG_CHOSENMANOEUVRE, caller, trg, caller), SetUpDefensiveSplitRightHi);
				break;
			}
			case 3:
			{
				ScriptTables script = SCRIPT_CALLER_GROUP_SPLIT_BOTHHI;
				switch(unit)
				{
					case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLITBOTHHI;			break;
					case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLITBOTHHI;		break;
					case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLITBOTHHI;			break;
					case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLITBOTHHI;		break;
				}
				retval = SendMsgAndCall(MESSAGE_STRUC(script, MSG_CHOSENMANOEUVRE, caller, trg, caller), SetUpDefensiveSplitBothHi);
				break;
			}
			case 4:
				retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_SELECTYOUROWNTARGETS, MSG_CHOSENMANOEUVRE, caller, trg, caller), SetupSelectTarget);
				break;
			break;
		}
	}
 	else
 	   	retval = SendMsgAndCall(MESSAGE_STRUC(OLDPHRASE_IGNOREFORNOW,MSG_SPOTTEDASNEWUNFRIENDLY,caller,trg,caller),DoNothing);

	return(retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpDefensiveSplit
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetUpDefensiveSplit, AirStrucPtr)
{
	UnitSize unit;
	ScriptTables script = SCRIPT_NULL;
	AirStrucPtr msgcallee = SplitUnit(caller, unit);

	if((caller->nationality == NAT_LUF) || (!Math_Lib.rnd(5)))
		script = SCRIPT_CALLER_GROUP_SPLIT;
	else
		switch(unit)
		{
			case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLIT;			break;
			case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLIT;		break;
			case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLIT;		break;
			case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLIT;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_GRUPPEN:		script = SCRIPT_WINGDEFENSIVESPLIT;			break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_STAFFEL:		script = SCRIPT_SQUADRONDEFENSIVESPLIT;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_SCHWARME:		script = SCRIPT_FLIGHTDEFENSIVESPLIT;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_ROTTE:		script = SCRIPT_SECTIONDEFENSIVESPLIT;		break;
		}

	if(script)
		_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_INITIALCOMBAT, caller, trg, msgcallee));

	DefensiveSplit(caller, trg, ANGLES_0Deg, ANGLES_0Deg);
//DEADCODE CSB 16/02/00 	SetUpRemainderOfGroupToEngage(caller, trg, MANOEUVRE_SPLITS, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	return(true);
}


//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetUpDefensiveSplitLeftHi, AirStrucPtr)
{
	UnitSize unit;
	ScriptTables script = SCRIPT_NULL;
	AirStrucPtr msgcallee = SplitUnit(caller, unit);

	if((caller->nationality == NAT_LUF) || (!Math_Lib.rnd(5)))
		script = SCRIPT_CALLER_GROUP_SPLIT_LEFTHI;
	else
		switch(unit)
		{
			case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLITLEFTHI;			break;
			case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLITLEFTHI;		break;
			case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLITLEFTHI;			break;
			case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLITLEFTHI;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_GRUPPEN:		script = SCRIPT_WINGDEFENSIVESPLITLEFTHI;			break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_STAFFEL:		script = SCRIPT_SQUADRONDEFENSIVESPLITLEFTHI;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_SCHWARME:		script = SCRIPT_FLIGHTDEFENSIVESPLITLEFTHI;			break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_ROTTE:		script = SCRIPT_SECTIONDEFENSIVESPLITLEFTHI;		break;
		}

	if(script)
		_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_INITIALCOMBAT, caller, trg, msgcallee));

	DefensiveSplit(caller, trg, BESTCLIMBPITCH,ANGLES_0Deg);
	return(true);
}


//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetUpDefensiveSplitRightHi, AirStrucPtr)
{
	UnitSize unit;
	ScriptTables script = SCRIPT_NULL;
	AirStrucPtr msgcallee = SplitUnit(caller, unit);

	if((caller->nationality == NAT_LUF) || (!Math_Lib.rnd(5)))
		script = SCRIPT_CALLER_GROUP_SPLIT_RIGHTHI;
	else
		switch(unit)
		{
			case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLITRIGHTHI;			break;
			case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLITRIGHTHI;		break;
			case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLITRIGHTHI;		break;
			case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLITRIGHTHI;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_GRUPPEN:		script = SCRIPT_WINGDEFENSIVESPLITRIGHTHI;			break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_STAFFEL:		script = SCRIPT_SQUADRONDEFENSIVESPLITRIGHTHI;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_SCHWARME:		script = SCRIPT_FLIGHTDEFENSIVESPLITRIGHTHI;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_ROTTE:		script = SCRIPT_SECTIONDEFENSIVESPLITRIGHTHI;		break;
		}

	if(script)
		_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_INITIALCOMBAT, caller, trg, msgcallee));

	DefensiveSplit(caller, trg, ANGLES_0Deg,BESTCLIMBPITCH);
	return(true);
}


//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(SetUpDefensiveSplitBothHi, AirStrucPtr)
{
	UnitSize unit;
	ScriptTables script = SCRIPT_NULL;
	AirStrucPtr msgcallee = SplitUnit(caller, unit);

	if((caller->nationality == NAT_LUF) || (!Math_Lib.rnd(5)))
		script = SCRIPT_CALLER_GROUP_SPLIT_BOTHHI;
	else
		switch(unit)
		{
			case UNIT_RAF_WING:			script = SCRIPT_WINGDEFENSIVESPLITBOTHHI;			break;
			case UNIT_RAF_SQUADRON:		script = SCRIPT_SQUADRONDEFENSIVESPLITBOTHHI;		break;
			case UNIT_RAF_FLIGHT:		script = SCRIPT_FLIGHTDEFENSIVESPLITBOTHHI;			break;
			case UNIT_RAF_SECTION:		script = SCRIPT_SECTIONDEFENSIVESPLITBOTHHI;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_GRUPPEN:		script = SCRIPT_WINGDEFENSIVESPLITBOTHHI;			break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_STAFFEL:		script = SCRIPT_SQUADRONDEFENSIVESPLITBOTHHI;		break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_SCHWARME:		script = SCRIPT_FLIGHTDEFENSIVESPLITBOTHHI;			break;
//DEADCODE CSB 18/02/00 			case UNIT_LUF_ROTTE:		script = SCRIPT_SECTIONDEFENSIVESPLITBOTHHI;		break;
		}

	if(script)
		_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_INITIALCOMBAT, caller, trg, msgcallee));

	DefensiveSplit(caller, trg, BESTCLIMBPITCH, BESTCLIMBPITCH);
	return(true);
}


//------------------------------------------------------------------------------
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description	
//			   	
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
INSTANCEAI(DoNothing,AirStrucPtr)
{
	if((caller->fly.leadflight) && (caller->fly.leadflight->classtype->aerobaticfactor == AEROBATIC_LOW))
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STAYWITHBOMBERS, MSG_INITIALCOMBAT, caller, trg, callee));
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_LETGO, MSG_INITIALCOMBAT, caller, trg, callee));

	return(false);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DefensiveSplit
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
void	ArtInt::DefensiveSplit(AirStruc* caller,AirStruc* trg, ANGLES leftpitch,ANGLES rightpitch)
{
	tGroupLevel group;
	AirStruc* caller2;
	FindGroupAndLeader2(caller, caller2, group);
	if (!caller2)
	{
		SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg, ANGLES_0Deg,  FALSE);
	}else
	{
		caller2->information=IF_OUT_POS;
		SwitchCallerToLeft(caller, caller2);


		tGroupLevel trggroup;
		AirStruc* trg2;
		trg = trg->FindGroupLeaderClose();								  //RDH 23/06/99
		FindGroupAndLeader2(trg, trg2, trggroup);			//trg on the left
		if (!trg2)
			trg2 = trg;
		SwitchCallerToLeft(trg,trg2);


		Angles desiredhdg = (Angles)((SWord)ANGLES_195Deg + caller->hdg);
	   //set first half
		SetEngage(caller,trg,MANOEUVRE_SPLITMANOEUVRE, desiredhdg,leftpitch,true);
		SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_SPLITMANOEUVRE, desiredhdg,leftpitch,true);
 		if (	(caller->Follower())	&& (caller->ai.elementtactics == WELDEDWING))
 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STAYCLOSE, MSG_FOLLOWME, caller, NULL, caller->Follower()));
		
		//find caller's second half
		desiredhdg = (Angles)((SWord)ANGLES_170Deg + caller2->hdg);

		SetEngage(caller2,trg2,MANOEUVRE_SPLITMANOEUVRE, desiredhdg,rightpitch,true); //RDH 27/06/99
		SetUpRemainderOfGroupToEngage(caller2,trg,MANOEUVRE_SPLITMANOEUVRE, desiredhdg, rightpitch,true);
 		if (	(caller2->Follower())	&& (caller2->ai.elementtactics == WELDEDWING))
 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_COVERME, MSG_FOLLOWME, caller2, NULL, caller2->Follower()));
	}	
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		Craig Beeston
//Date			Tue 15 Feb 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
TABLEAI(DefensiveManoeuvre110, AirStrucPtr)
{
	{PHRASE_DEFENSIVESPLIT,				&SetUpDefensiveSplit,			PHRASE_NULL},
	{PHRASE_S_DEFENSIVESPLITLEFTHI,		&SetUpDefensiveSplitLeftHi,		PHRASE_NULL},
	{PHRASE_S_DEFENSIVESPLITRIGHTHI,	&SetUpDefensiveSplitRightHi,	PHRASE_NULL},
	{PHRASE_S_DEFENSIVESPLITBOTHHI,		&SetUpDefensiveSplitBothHi,		PHRASE_NULL},
	{PHRASE_S_SELECTOWNTRG,				&SetupSelectTarget,				PHRASE_NULL},
	{PHRASE_DEFENSIVECIRCLE,			&SetUpLufberry,					SCRIPT_CALLER_GROUP_CIRCLE},
	{PHRASE_NULL,						&DoNothing,						PHRASE_NULL},
	{PHRASE_NULL}
};

INSTANCEAI(DefensiveManoeuvre110, AirStrucPtr)
{
	bool retval;
	if((caller->classtype->visible == ME110) && (CountSquadronSize(caller) > 4))
		retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CHOSENMANOEUVRE, caller, trg, caller), SetUpLufberry);
	else
		retval = SendMsgAndCall(MESSAGE_STRUC(SCRIPT_NULL, MSG_CHOSENMANOEUVRE, caller, trg, caller), DefensiveManoeuvre2);
	return(retval);
}

INSTANCEAI(SetUpLufberry, AirStrucPtr)
{
	SetEngage(caller, trg, MANOEUVRE_LUFBERRY, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	SetUpRemainderOfGroupToEngage(caller, trg, MANOEUVRE_LUFBERRY, ANGLES_0Deg, ANGLES_0Deg, FALSE);
	return(true);
}


//DEADCODE CSB 24/01/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE CSB 24/01/00 //Procedure		SpottedUnknown
//DEADCODE CSB 24/01/00 //Author		R. Hyde 
//DEADCODE CSB 24/01/00 //Date			Fri 27 Feb 1998
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //Description	Do we want a closer look?
//DEADCODE CSB 24/01/00 //			   	Only if threatlevel >=BANDITANYWHERE
//DEADCODE CSB 24/01/00 //				and aggressionlevel >=AL_DEFENSIVE
//DEADCODE CSB 24/01/00 //Inputs		
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //Returns	
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 24/01/00 bool	ArtInt::SpottedUnknown(AirStruc* caller,AirStruc* trg)
//DEADCODE CSB 24/01/00 {
//DEADCODE CSB 24/01/00 //no autovectoring
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 	RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	
//DEADCODE CSB 24/01/00 	InterceptRangeFromTo(caller,trg);
//DEADCODE CSB 24/01/00 	AirStruc* trgldr = trg->FindGroupLeader();
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 	if (		(caller->nationality==trg->nationality)		
//DEADCODE CSB 24/01/00 			||	(		(caller->formpos != 0)								//only leaders can respond
//DEADCODE CSB 24/01/00 					&&	(caller->information)
//DEADCODE CSB 24/01/00 				)
//DEADCODE CSB 24/01/00 			||	(caller->ai.unfriendly!=NULL)
//DEADCODE CSB 24/01/00 			||	(		(trg->formpos != 0)								//only respond to leaders
//DEADCODE CSB 24/01/00 					&&	(		(trg->information)
//DEADCODE CSB 24/01/00 							||	(AircraftAreClose(trg, trgldr))
//DEADCODE CSB 24/01/00 						)
//DEADCODE CSB 24/01/00 				)
//DEADCODE CSB 24/01/00 	   )
//DEADCODE CSB 24/01/00 		return false; 
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 	if (caller->nationality == Manual_Pilot.ControlledAC2->nationality)
//DEADCODE CSB 24/01/00 	{
//DEADCODE CSB 24/01/00 		if (caller->IsUsingPilotedAcLog())
//DEADCODE CSB 24/01/00 		{
//DEADCODE CSB 24/01/00 			if (		(!trg->ai.attacker)
//DEADCODE CSB 24/01/00 					&&	(!trg->IsUsingPilotedAcLog())
//DEADCODE CSB 24/01/00 			   )
//DEADCODE CSB 24/01/00 			{
//DEADCODE CSB 24/01/00 				caller->PlayerSequenceAudible(FIL_MUSIC_SPOTTED_UNKNOWN);
//DEADCODE CSB 24/01/00 				Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 				if ((TargetOnCallerTail(caller, trg, ANGLES_10Deg)	&&	(rndpc >RND50PC)))
//DEADCODE CSB 24/01/00  					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BOGEY_SIX, MSG_BOGEYCALL, caller, trg, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 24/01/00  				else if ((CallerFacingTarget(caller, trg, ANGLES_20Deg)&&	(rndpc >RND50PC)))
//DEADCODE CSB 24/01/00  					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BOGEY_AHEAD, MSG_BOGEYCALL, caller, trg, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 24/01/00  				else
//DEADCODE CSB 24/01/00  					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BOGEY, MSG_BOGEYCALL, caller, trg, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 			}
//DEADCODE CSB 24/01/00 		}elseif (!trg->IsUsingPilotedAcLog())
//DEADCODE CSB 24/01/00 		{
//DEADCODE CSB 24/01/00 			if (!trg->ai.attacker)
//DEADCODE CSB 24/01/00 			{
//DEADCODE CSB 24/01/00 				if (trg->ai.eventlog->stage < EventLog::SEENBYOTHERS)
//DEADCODE CSB 24/01/00 				{
//DEADCODE CSB 24/01/00 					int range = RangeFromTo(trg, Persons2::PlayerGhostAC);
//DEADCODE CSB 24/01/00 					InterceptRangeFromTo(Manual_Pilot.ControlledAC2,trg);
//DEADCODE CSB 24/01/00 					if (range < VISIBLERANGE)
//DEADCODE CSB 24/01/00 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_TRACES_CLOSE, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, trg, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 24/01/00 					else
//DEADCODE CSB 24/01/00 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DENTIST_TRACES_FAR, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, trg, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 24/01/00 					Persons2::UpdateLog(trg,0,EventLog::SEENBYOTHERS);
//DEADCODE CSB 24/01/00 				}				
//DEADCODE CSB 24/01/00 			}
//DEADCODE CSB 24/01/00 		}
//DEADCODE CSB 24/01/00 	}
//DEADCODE CSB 24/01/00 	if  (			((caller->duty&ACTIONCODE)==DA_CAP)
//DEADCODE CSB 24/01/00 				&&	(caller->classtype->aerobaticfactor != AEROBATIC_LOW) //RDH 21/06/99
//DEADCODE CSB 24/01/00 				&&	(caller->ai.unfriendly==NULL)
//DEADCODE CSB 24/01/00 		)
//DEADCODE CSB 24/01/00 	{
//DEADCODE CSB 24/01/00 		
//DEADCODE CSB 24/01/00 		AirStruc*	buddy = caller->FindABuddyWithPlayerGivenPriority();
//DEADCODE CSB 24/01/00 		if (buddy)
//DEADCODE CSB 24/01/00 		{
//DEADCODE CSB 24/01/00 			if  (	(caller->ai.threatlevel >=BANDITANYWHERE)
//DEADCODE CSB 24/01/00 					&&	caller->movecode < AUTO_TRACKINGBOGIE
//DEADCODE CSB 24/01/00 					&&	caller->ai.aggressionlevel >= AL_DEFENSIVE
//DEADCODE CSB 24/01/00 				)
//DEADCODE CSB 24/01/00 			{
//DEADCODE CSB 24/01/00 					AllChangeMovecode(caller, trg, AUTO_TRACKINGBOGIE);
//DEADCODE CSB 24/01/00 					trg->ai.attacker = caller;
//DEADCODE CSB 24/01/00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CLOSERLOOK, MSG_BOGEYCALL, caller, trg, buddy));
//DEADCODE CSB 24/01/00 			}else
//DEADCODE CSB 24/01/00 			{
//DEADCODE CSB 24/01/00 				if (Escorting(caller) && 	(rndpc >RND50PC))
//DEADCODE CSB 24/01/00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_STAYWITHBOMBERS, MSG_BOGEYCALL, caller, trg, buddy));
//DEADCODE CSB 24/01/00 				else
//DEADCODE CSB 24/01/00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_LETGO, MSG_BOGEYCALL, caller, trg, buddy));
//DEADCODE CSB 24/01/00 			}
//DEADCODE CSB 24/01/00 		}
//DEADCODE CSB 24/01/00 	}
//DEADCODE CSB 24/01/00 	return(true);
//DEADCODE CSB 24/01/00 }
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 24/01/00 //Procedure		
//DEADCODE CSB 24/01/00 //Author		R. Hyde 
//DEADCODE CSB 24/01/00 //Date																  //RDH 24/02/99
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //Description			   red manoeuvre
//DEADCODE CSB 24/01/00 //			   	
//DEADCODE CSB 24/01/00 //				
//DEADCODE CSB 24/01/00 //Inputs		
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //Returns	
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //------------------------------------------------------------------------------
//DEADCODE CB 18/11/99 INSTANCEAI(SetupRoundAbout,AirStrucPtr)
//DEADCODE CB 18/11/99 {
//DEADCODE CB 18/11/99 
//DEADCODE CB 18/11/99 	SetEngage(caller,trg, MANOEUVRE_ROUNDABOUT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
//DEADCODE CB 18/11/99 	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_ROUNDABOUT,ANGLES_0Deg,ANGLES_0Deg,FALSE);
//DEADCODE CB 18/11/99  	return(true);
//DEADCODE CB 18/11/99 }
//DEADCODE CSB 21/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 21/01/00 //Procedure		
//DEADCODE CSB 21/01/00 //Author		R. Hyde 
//DEADCODE CSB 21/01/00 //Date			21 Jan 1999
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //Description	
//DEADCODE CSB 21/01/00 //			   	
//DEADCODE CSB 21/01/00 //				
//DEADCODE CSB 21/01/00 //Inputs		
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //Returns	
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 21/01/00 INSTANCEAI(SetUpPincerAttack, AirStrucPtr)
//DEADCODE CSB 21/01/00 {
//DEADCODE CSB 21/01/00 	AirStruc* callee2;
//DEADCODE CSB 21/01/00 	tGroupLevel group;
//DEADCODE CSB 21/01/00 	FindGroupAndLeader2(caller, callee2, group);
//DEADCODE CSB 21/01/00 	if (!callee2)
//DEADCODE CSB 21/01/00 	{
//DEADCODE CSB 21/01/00 		SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg, ANGLES_0Deg,  FALSE);
//DEADCODE CSB 21/01/00 	}else
//DEADCODE CSB 21/01/00 	{
//DEADCODE CSB 21/01/00 				
//DEADCODE CSB 21/01/00 		if (prioritymessage)
//DEADCODE CSB 21/01/00 		{																  //RDH 23/02/99
//DEADCODE CSB 21/01/00 			callee = callee2;
//DEADCODE CSB 21/01/00 			prioritymessage->callee = callee;
//DEADCODE CSB 21/01/00 			prioritymessage->scriptno = SCRIPT_PINCER_LEAD2_RIGHT;		//RJS 09Mar99
//DEADCODE CSB 21/01/00 			if (CallerOnRight(caller,callee))
//DEADCODE CSB 21/01/00 				prioritymessage->scriptno = SCRIPT_PINCER_LEAD2_LEFT;	//RJS 09Mar99
//DEADCODE CSB 21/01/00 		}
//DEADCODE CSB 21/01/00 		callee->information=IF_OUT_POS;
//DEADCODE CSB 21/01/00 		SwitchCallerToLeft(caller, callee);
//DEADCODE CSB 21/01/00 
//DEADCODE CSB 21/01/00 		
//DEADCODE CSB 21/01/00 		
//DEADCODE CSB 21/01/00 		tGroupLevel trggroup;
//DEADCODE CSB 21/01/00 		AirStruc* trg2;
//DEADCODE CSB 21/01/00 		trg = trg->FindGroupLeaderClose();								  //RDH 23/06/99
//DEADCODE CSB 21/01/00 		FindGroupAndLeader2(trg, trg2, trggroup);			//trg on the left
//DEADCODE CSB 21/01/00 		if (!trg2)
//DEADCODE CSB 21/01/00 			trg2 = trg;
//DEADCODE CSB 21/01/00 		SwitchCallerToLeft(trg,trg2);
//DEADCODE CSB 21/01/00 
//DEADCODE CSB 21/01/00 		if (!trg2) 														  //rdh 23/04/99
//DEADCODE CSB 21/01/00 			trg2 = trg;													  //rdh 23/04/99
//DEADCODE CSB 21/01/00 		SWord deltahdg = (SWord)caller->hdg - (SWord)trg->hdg;
//DEADCODE CSB 21/01/00 		if (deltahdg < 0)
//DEADCODE CSB 21/01/00 		   deltahdg = -deltahdg;
//DEADCODE CSB 21/01/00 		 if (deltahdg > (SWord)ANGLES_90Deg)
//DEADCODE CSB 21/01/00 		 {//if trg is facing caller then reverse
//DEADCODE CSB 21/01/00 			AirStruc* tmp = trg;
//DEADCODE CSB 21/01/00 			trg = trg2;
//DEADCODE CSB 21/01/00 			trg2 = tmp;
//DEADCODE CSB 21/01/00 		 }
//DEADCODE CSB 21/01/00 			
//DEADCODE CSB 21/01/00 	   //set first half
//DEADCODE CSB 21/01/00 
//DEADCODE CSB 21/01/00 		SetEngage(caller,trg,MANOEUVRE_PINCER, ANGLES_320Deg, ANGLES_0Deg,FALSE);
//DEADCODE CSB 21/01/00 		SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_PINCER, ANGLES_260Deg, ANGLES_0Deg,FALSE);
//DEADCODE CSB 21/01/00 		//find caller's second half
//DEADCODE CSB 21/01/00 		SetEngage(callee,trg2,MANOEUVRE_PINCER, ANGLES_40Deg, ANGLES_0Deg,FALSE);
//DEADCODE CSB 21/01/00 		SetUpRemainderOfGroupToEngage(callee,trg2,MANOEUVRE_PINCER, ANGLES_100Deg, ANGLES_0Deg,FALSE);
//DEADCODE CSB 21/01/00 	}
//DEADCODE CSB 21/01/00  	return(true);
//DEADCODE CSB 21/01/00 }

//DEADCODE CSB 21/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 21/01/00 //Procedure		
//DEADCODE CSB 21/01/00 //Author		R. Hyde 
//DEADCODE CSB 21/01/00 //Date			21 Jan 1999
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //Description	
//DEADCODE CSB 21/01/00 //			   	
//DEADCODE CSB 21/01/00 //				
//DEADCODE CSB 21/01/00 //Inputs		
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //Returns	
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 21/01/00 INSTANCEAI(SetUpMultiWave, AirStrucPtr)
//DEADCODE CSB 21/01/00 {
//DEADCODE CSB 21/01/00 //DEADCODE RDH 12/06/99 		if (prioritymessage)
//DEADCODE CSB 21/01/00 	{																  //RDH 23/02/99
//DEADCODE CSB 21/01/00 		tGroupLevel group;
//DEADCODE CSB 21/01/00 		FindGroupAndLeader2(caller, callee, group);
//DEADCODE CSB 21/01/00 	}
//DEADCODE CSB 21/01/00 	if (!callee)
//DEADCODE CSB 21/01/00 	{
//DEADCODE CSB 21/01/00 		SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg, ANGLES_0Deg,  FALSE);
//DEADCODE CSB 21/01/00 	}else
//DEADCODE CSB 21/01/00 	{
//DEADCODE CSB 21/01/00  		MANOEUVRE manoeuvre = MANOEUVRE_SELECT;
//DEADCODE CSB 21/01/00 		if  (		CallerFacingTarget(caller, trg, ANGLES_45Deg)
//DEADCODE CSB 21/01/00 				&&	TargetFacingCaller(caller, trg, ANGLES_45Deg)
//DEADCODE CSB 21/01/00 			)
//DEADCODE CSB 21/01/00 			manoeuvre = MANOEUVRE_HEADON;
//DEADCODE CSB 21/01/00 
//DEADCODE CSB 21/01/00 		callee->information=IF_OUT_POS;
//DEADCODE CSB 21/01/00 		
//DEADCODE CSB 21/01/00 		SetEngage(caller,trg,manoeuvre, ANGLES_0Deg, ANGLES_0Deg,FALSE);
//DEADCODE CSB 21/01/00 		SetUpRemainderOfGroupToEngage(caller,trg,manoeuvre, ANGLES_0Deg, ANGLES_0Deg,FALSE);
//DEADCODE CSB 21/01/00 		
//DEADCODE CSB 21/01/00 
//DEADCODE CSB 21/01/00 		SetEngage(callee,trg,MANOEUVRE_MULTIWAVE, ANGLES_0Deg, ANGLES_0Deg,FALSE);
//DEADCODE CSB 21/01/00 		SetUpRemainderOfGroupToEngage(callee,trg,MANOEUVRE_MULTIWAVE, ANGLES_0Deg, ANGLES_0Deg,FALSE);
//DEADCODE CSB 21/01/00 	}
//DEADCODE CSB 21/01/00  	return(true);
//DEADCODE CSB 21/01/00 }

//DEADCODE CSB 21/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 21/01/00 //Procedure		
//DEADCODE CSB 21/01/00 //Author		R. Hyde 
//DEADCODE CSB 21/01/00 //Date			21 Jan 1999
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //Description	
//DEADCODE CSB 21/01/00 //			   	
//DEADCODE CSB 21/01/00 //				
//DEADCODE CSB 21/01/00 //Inputs		
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //Returns	
//DEADCODE CSB 21/01/00 //
//DEADCODE CSB 21/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 21/01/00 INSTANCEAI(SetUpDefensiveSplit, AirStrucPtr)
//DEADCODE CSB 21/01/00 {
//DEADCODE CSB 21/01/00    	DefensiveSplit(caller,trg, ANGLES_0Deg,ANGLES_0Deg);
//DEADCODE CSB 21/01/00 	return(true);
//DEADCODE CSB 21/01/00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		R. Hyde 
//Date			21 Jan 1999
//
//Description		   callee is lowest flight free in caller's group
//						if there isn't a free flight then redirect lowest which is attacking a/c in same flight that eader is attacking		   	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 INSTANCEAI(SendFlight, AirStrucPtr)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 	bool retval;
//DEADCODE CSB 04/05/00 	if (prioritymessage)
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	
//DEADCODE CSB 04/05/00  		prioritymessage->callee = callee;
//DEADCODE CSB 04/05/00  		if 	((trg->nationality == NAT_RED) && (rndpc >RND50PC))
//DEADCODE CSB 04/05/00  			prioritymessage->scriptno = OLDSCRIPT_TAKEFLIGHTTOMIGS;
//DEADCODE CSB 04/05/00  		else
//DEADCODE CSB 04/05/00  			prioritymessage->scriptno = OLDSCRIPT_TAKEFLIGHTTOBANDITS;
//DEADCODE CSB 04/05/00 	}
//DEADCODE CSB 04/05/00 	//better to send msg to 2nd element leader
//DEADCODE CSB 04/05/00 	AirStruc* buddy = caller->Follower();
//DEADCODE CSB 04/05/00 	if (caller->ai.elementtactics == WELDEDWING)
//DEADCODE CSB 04/05/00 		buddy = caller->fly.nextflight;
//DEADCODE CSB 04/05/00 	if (buddy)
//DEADCODE CSB 04/05/00 		retval = SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_ENGAGE,MSG_ATTACK,callee,trg,buddy), SetupSelectTarget);
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 	return(retval);
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 };
//DEADCODE CSB 24/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 24/01/00 //Procedure		
//DEADCODE CSB 24/01/00 //Author		R. Hyde 
//DEADCODE CSB 24/01/00 //Date			21 Jan 1999
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //Description	
//DEADCODE CSB 24/01/00 //			   	
//DEADCODE CSB 24/01/00 //				
//DEADCODE CSB 24/01/00 //Inputs		
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //Returns	
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 24/01/00 INSTANCEAI(AllGo, AirStrucPtr)
//DEADCODE CSB 24/01/00 {
//DEADCODE CSB 24/01/00 	//use selecttarget instead
//DEADCODE CSB 24/01/00 //DEADCODE RDH 20/06/99  	if (	(caller->Follower())	&& (caller->ai.elementtactics == WELDEDWING))
//DEADCODE CSB 24/01/00 //DEADCODE RDH 20/06/99  		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_CALLEE_FOLLOWME, MSG_FOLLOWME, caller, NULL, caller->Follower()));
//DEADCODE CSB 24/01/00 //DEADCODE RDH 20/06/99 	SetEngage(caller,trg, MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg, FALSE);
//DEADCODE CSB 24/01/00 //DEADCODE RDH 20/06/99 	SetUpRemainderOfGroupToEngage(caller,trg,MANOEUVRE_SELECT,ANGLES_0Deg,ANGLES_0Deg,FALSE);
//DEADCODE CSB 24/01/00 	return(true);
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 };
//DEADCODE CSB 24/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 24/01/00 //Procedure		
//DEADCODE CSB 24/01/00 //Author		R. Hyde 
//DEADCODE CSB 24/01/00 //Date			21 Jan 1999
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //Description	
//DEADCODE CSB 24/01/00 //			   	
//DEADCODE CSB 24/01/00 //				
//DEADCODE CSB 24/01/00 //Inputs		
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //Returns	
//DEADCODE CSB 24/01/00 //
//DEADCODE CSB 24/01/00 //------------------------------------------------------------------------------
//DEADCODE CSB 24/01/00 INSTANCEAI(RelaySighting, AirStrucPtr)
//DEADCODE CSB 24/01/00 {
//DEADCODE CSB 24/01/00 	bool retval;
//DEADCODE CSB 24/01/00 	retval = AlertFighters(caller,trg,callee);
//DEADCODE CSB 24/01/00 	return(retval);
//DEADCODE CSB 24/01/00 };
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 04/05/00 //------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 //Procedure		
//DEADCODE CSB 04/05/00 //Author		R. Hyde 
//DEADCODE CSB 04/05/00 //Date			21 Jan 1999
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Description	
//DEADCODE CSB 04/05/00 //			   	
//DEADCODE CSB 04/05/00 //				
//DEADCODE CSB 04/05/00 //Inputs		
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Returns	
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 TABLEAI(UnFriendlyFar, AirStrucPtr)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 	{PHRASE_NULL,		&SetupSelectTarget,	OLDSCRIPT_ALLGO},	
//DEADCODE CSB 04/05/00 	{PHRASE_NULL,		&SendFlight,	PHRASE_NULL},	//this is a dummy, it gets changed by SendFlight //RDH 28/02/99
//DEADCODE CSB 04/05/00 	{PHRASE_NULL,		&DoNothing,		PHRASE_NULL},
//DEADCODE CSB 04/05/00 	{PHRASE_NULL},
//DEADCODE CSB 04/05/00 	{PHRASE_NULL}
//DEADCODE CSB 04/05/00 };
//DEADCODE CSB 04/05/00 INSTANCEAI(UnFriendlyFar, AirStrucPtr)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 	caller = callee;
//DEADCODE CSB 04/05/00 	bool retval = false;
//DEADCODE CSB 04/05/00 	ScriptTables script;
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 //remove chance of recurse
//DEADCODE CSB 04/05/00 //DEADCODE DAW 19/05/99 	if	(		(caller->ai.unfriendly != NULL)
//DEADCODE CSB 04/05/00 //DEADCODE DAW 19/05/99 			&&	( RangeFromTo(caller,trg) > RangeFromTo(caller,(AirStruc*)caller->ai.unfriendly))
//DEADCODE CSB 04/05/00 //DEADCODE DAW 19/05/99 		)	
//DEADCODE CSB 04/05/00 //DEADCODE DAW 19/05/99 	{
//DEADCODE CSB 04/05/00 //DEADCODE DAW 19/05/99 		retval = AlertFighters(caller,trg);
//DEADCODE CSB 04/05/00 //DEADCODE DAW 19/05/99 	}else 
//DEADCODE CSB 04/05/00 	if(		TrgIsVulnerable(caller, trg)
//DEADCODE CSB 04/05/00 			)
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 		callee = FindFreeFlight(caller);						//RDH 12Apr99
//DEADCODE CSB 04/05/00 		if (callee)											//RDH 12Apr99
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			if 	((trg->nationality == NAT_RED) && (rndpc >  RND50PC))
//DEADCODE CSB 04/05/00 				script = OLDSCRIPT_TAKEFLIGHTTOMIGS;
//DEADCODE CSB 04/05/00 			else
//DEADCODE CSB 04/05/00 				script = OLDSCRIPT_TAKEFLIGHTTOBANDITS;
//DEADCODE CSB 04/05/00 			retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_SENDTOINVESTIGATE,caller,trg,callee),SendFlight);
//DEADCODE CSB 04/05/00 		}else
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			callee = FreeUpAFlight(caller, trg);
//DEADCODE CSB 04/05/00 			if (callee)
//DEADCODE CSB 04/05/00 			{
//DEADCODE CSB 04/05/00 				if ((trg->nationality == NAT_RED) && (rndpc >  RND50PC))
//DEADCODE CSB 04/05/00 					script = OLDSCRIPT_GOFORNEARERMIG;
//DEADCODE CSB 04/05/00 				else
//DEADCODE CSB 04/05/00 					script = OLDSCRIPT_GOFORNEARERBANDITS;
//DEADCODE CSB 04/05/00 				retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_SENDTOINVESTIGATE,caller,trg,callee),SendFlight);
//DEADCODE CSB 04/05/00 			}else
//DEADCODE CSB 04/05/00 				retval = SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_ALLGOREDIRECT,MSG_ATTACK, caller,trg,caller),SetupSelectTarget);
//DEADCODE CSB 04/05/00 		}
//DEADCODE CSB 04/05/00 	}else
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		if (caller->ai.unfriendly == NULL)
//DEADCODE CSB 04/05/00 			retval = SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_ALLGO,MSG_ATTACK, caller,trg,caller),SetupSelectTarget);
//DEADCODE CSB 04/05/00 		else
//DEADCODE CSB 04/05/00 			retval = SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_ALLGOREDIRECT,MSG_ATTACK, caller,trg,caller), SetupSelectTarget);
//DEADCODE CSB 04/05/00 	}
//DEADCODE CSB 04/05/00 	return(retval);
//DEADCODE CSB 04/05/00 }	
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 	
//DEADCODE CSB 04/05/00 //------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 //Procedure		
//DEADCODE CSB 04/05/00 //Author		R. Hyde 
//DEADCODE CSB 04/05/00 //Date			21 Jan 1999
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Description	
//DEADCODE CSB 04/05/00 //			   	
//DEADCODE CSB 04/05/00 //				
//DEADCODE CSB 04/05/00 //Inputs		
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Returns	
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 TABLEAI(PotentialBounce, AirStrucPtr)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 	{PHRASE_NULL,	&SetupSelectTarget,	OLDSCRIPT_ALLGO},	
//DEADCODE CSB 04/05/00 	{PHRASE_NULL,	&SendFlight,		PHRASE_NULL},	//this is a dummy, it gets changed by SendFlight //RDH 28/02/99
//DEADCODE CSB 04/05/00 	{PHRASE_NULL,	&DoNothing,			PHRASE_NULL},
//DEADCODE CSB 04/05/00 	{PHRASE_NULL},
//DEADCODE CSB 04/05/00 	{PHRASE_NULL}
//DEADCODE CSB 04/05/00 };
//DEADCODE CSB 04/05/00 INSTANCEAI(PotentialBounce, AirStrucPtr)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 	caller = callee;
//DEADCODE CSB 04/05/00 	bool retval = false;
//DEADCODE CSB 04/05/00 	ScriptTables script;
//DEADCODE CSB 04/05/00 	if (RangeFromTo(caller, trg) < ENGAGERANGE)
//DEADCODE CSB 04/05/00  	{
//DEADCODE CSB 04/05/00  		   	retval = SendMsgAndCall(MESSAGE_STRUC(OLDPHRASE_IGNOREFORNOW,MSG_SPOTTEDASNEWUNFRIENDLY,caller,trg,caller->Follower()),DoNothing);
//DEADCODE CSB 04/05/00  	}else
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		if(		TrgIsVulnerable(caller, trg)
//DEADCODE CSB 04/05/00 				)
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 			callee = FindFreeFlight(caller);						//RDH 12Apr99
//DEADCODE CSB 04/05/00 			if (callee)											//RDH 12Apr99
//DEADCODE CSB 04/05/00 			{
//DEADCODE CSB 04/05/00 				if 	((trg->nationality == NAT_RED) && (rndpc >  RND50PC))
//DEADCODE CSB 04/05/00 					script = OLDSCRIPT_TAKEFLIGHTTOMIGS;
//DEADCODE CSB 04/05/00 				else
//DEADCODE CSB 04/05/00 					script = OLDSCRIPT_TAKEFLIGHTTOBANDITS;
//DEADCODE CSB 04/05/00 				retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_SENDTOINVESTIGATE,caller,trg,callee),SendFlight);
//DEADCODE CSB 04/05/00 			}else
//DEADCODE CSB 04/05/00 			{
//DEADCODE CSB 04/05/00 				callee = FreeUpAFlight(caller, trg);
//DEADCODE CSB 04/05/00 				if (callee)
//DEADCODE CSB 04/05/00 				{
//DEADCODE CSB 04/05/00 					if ((trg->nationality == NAT_RED) && (rndpc >  RND50PC))
//DEADCODE CSB 04/05/00 						script = OLDSCRIPT_GOFORNEARERMIG;
//DEADCODE CSB 04/05/00 					else
//DEADCODE CSB 04/05/00 						script = OLDSCRIPT_GOFORNEARERBANDITS;
//DEADCODE CSB 04/05/00 					retval = SendMsgAndCall(MESSAGE_STRUC(script,MSG_SENDTOINVESTIGATE,caller,trg,callee),SendFlight);
//DEADCODE CSB 04/05/00 				}else
//DEADCODE CSB 04/05/00 					retval = SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_ALLGOREDIRECT,MSG_ATTACK, caller,trg,caller),SetupSelectTarget);
//DEADCODE CSB 04/05/00 			}
//DEADCODE CSB 04/05/00 		}else
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			if (caller->ai.unfriendly == NULL)
//DEADCODE CSB 04/05/00 				retval = SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_ALLGO,MSG_ATTACK, caller,trg,caller),SetupSelectTarget);
//DEADCODE CSB 04/05/00 			else
//DEADCODE CSB 04/05/00 				retval = SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_ALLGOREDIRECT,MSG_ATTACK, caller,trg,caller), SetupSelectTarget);
//DEADCODE CSB 04/05/00 		}
//DEADCODE CSB 04/05/00 	}
//DEADCODE CSB 04/05/00 	return(retval);
//DEADCODE CSB 04/05/00 }		


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AlertFighters
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
bool	ArtInt::AlertFighters(AirStruc* caller,AirStruc* trg, AirStruc* friendlythatneedshelp)
{
//DeadCode CSB 31Jul00 	if(trg->FindFormpos0()->ai.attacker)
//DeadCode CSB 31Jul00 		return(false);
//DeadCode CSB 31Jul00 
//DeadCode CSB 31Jul00 	if((trg->fly.expandedsag) && (!trg->fly.numinsag) && (trg->fly.expandedsag->ai.attacker))
//DeadCode CSB 31Jul00 		return(false);

	AirStrucPtr helpee = friendlythatneedshelp->FindFormpos0();
	AirStrucPtr helper = FindEscort(helpee);

	FP helperrange2 = FP(MILES100) * FP(MILES100);
	if(helper)
		if((helper->ai.unfriendly == NULL) && (!helper->GroupShouldGoHome(0.5)))
			helperrange2 = helper->Distance3DSquared(&helpee->World);
		else
			helper = NULL;

	if(helper == NULL)
	{
		for(AirStrucPtr ac = AirStrucPtr(AirStruc::ACList); ac; ac = AirStrucPtr(ac->nextmobile))
			if(		(!ac->formpos)
				&&	(!ac->Status.deadtime)
				&&	(!ac->Status.deadtime)	
				&&	(ac->nationality == helpee->nationality)
				&&	(ac->classtype->aerobaticfactor == AEROBATIC_HIGH)
				&&	(CanAttackType(ac, trg))
				&&	(ac != helpee)
				&&	(ac->ai.unfriendly == NULL)
				&&	(ac->Distance3DSquared(&helpee->World) < helperrange2)
				&&	(!ac->GroupShouldGoHome(0.5))
				&&	(ac->ai.manoeuvre != MANOEUVRE_SCREWYOUGUYSIMGOINGHOME)	)
			{
				helper = ac;
				helperrange2 = ac->Distance3DSquared(&helpee->World);
			}
	}

	if((helper) && (helperrange2 < FP(VISIBLERANGE) * FP(VISIBLERANGE)))
	{
		if((helper == Persons2::PlayerGhostAC) || (helper == Persons2::PlayerSeenAC))
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BOMBERUNDERATTACK, MSG_SPOTTEDBYOTHERS, caller, trg, helper));
			return(true);
		}
		else
			return(SendMsgAndCall(MESSAGE_STRUC(SCRIPT_BOMBERUNDERATTACK, MSG_SPOTTEDBYOTHERS, helper, trg, helper), DecideTopCover));
	}

	return(false);
}

//DEADCODE CSB 10/02/00 	bool retval = false;
//DEADCODE CSB 10/02/00 
//DEADCODE CSB 10/02/00 	AirStruc* callee = NULL;
//DEADCODE CSB 10/02/00 	AirStruc* currac = (AirStruc*) AirStruc::ACList;
//DEADCODE CSB 10/02/00 	SLong callertrgrange = RangeFromTo(caller, trg);
//DEADCODE CSB 10/02/00 	SLong	curractrgrange;
//DEADCODE CSB 10/02/00 	SLong	range = MILES200;
//DEADCODE CSB 10/02/00 	AirStruc* callerldr = caller->FindGroupLeader();
//DEADCODE CSB 10/02/00 	AirStruc* friendlythatneedshelpldr = friendlythatneedshelp->FindGroupLeader();
//DEADCODE CSB 10/02/00 
//DEADCODE CSB 10/02/00 	if  (		(!trg->ai.attacker)
//DEADCODE CSB 10/02/00 			&&	(		(trg->formpos == 0)
//DEADCODE CSB 10/02/00 					||	(		(!trg->information)
//DEADCODE CSB 10/02/00 							&&	(trg->fly.leadflight)
//DEADCODE CSB 10/02/00 							&&	(!AircraftAreClose(trg, trg->fly.leadflight))
//DEADCODE CSB 10/02/00 
//DEADCODE CSB 10/02/00 						)
//DEADCODE CSB 10/02/00 				)
//DEADCODE CSB 10/02/00 		)
//DEADCODE CSB 10/02/00 	{//only concerned with leaders not under attack
//DEADCODE CSB 10/02/00 		while (	(currac))
//DEADCODE CSB 10/02/00 		{
//DEADCODE CSB 10/02/00 //DEADCODE RDH 19/06/99 			if (currac ==  Persons2::PlayerGhostAC)
//DEADCODE CSB 10/02/00 //DEADCODE RDH 19/06/99 				INT3;
//DEADCODE CSB 10/02/00 			if  (	((currac->duty&ACTIONCODE)==DA_CAP)
//DEADCODE CSB 10/02/00 					&&	(currac->classtype->aerobaticfactor != AEROBATIC_LOW) //RDH 21/06/99
//DEADCODE CSB 10/02/00 					&&	(currac->formpos == 0)
//DEADCODE CSB 10/02/00 					&&	(		(!currac->ai.unfriendly)						//not busy
//DEADCODE CSB 10/02/00 							||	(currac->movecode == AUTO_TRACKINGBOGIE)		//busy but just tracking bogies
//DEADCODE CSB 10/02/00 							||	(		(currac == Persons2::PlayerGhostAC) 		//player busy but just tracking bogies
//DEADCODE CSB 10/02/00 									&&	 (Persons2::PlayerSeenAC->movecode == AUTO_TRACKINGBOGIE)
//DEADCODE CSB 10/02/00 								)
//DEADCODE CSB 10/02/00 						)
//DEADCODE CSB 10/02/00 					&&	(currac->nationality == caller->nationality)
//DEADCODE CSB 10/02/00 					&&	(currac != caller)
//DEADCODE CSB 10/02/00 				)
//DEADCODE CSB 10/02/00 			{//this is a cap or escort leader
//DEADCODE CSB 10/02/00 				
//DEADCODE CSB 10/02/00 				 if  (friendlythatneedshelpldr == currac->fly.leadflight)
//DEADCODE CSB 10/02/00 				 {//this fighter leader is in same wave as one that needs help
//DEADCODE CSB 10/02/00 					callee = currac;
//DEADCODE CSB 10/02/00 					curractrgrange = RangeFromTo(currac, trg);
//DEADCODE CSB 10/02/00 					break;
//DEADCODE CSB 10/02/00 				 }else
//DEADCODE CSB 10/02/00 				 {
//DEADCODE CSB 10/02/00 					curractrgrange = RangeFromTo(currac, trg);
//DEADCODE CSB 10/02/00 					if  (		//##idea was to allow steady moving of message down line
//DEADCODE CSB 10/02/00 								//but it gets stuck when close to (curractrgrange > callertrgrange)
//DEADCODE CSB 10/02/00 							//&&
//DEADCODE CSB 10/02/00 									(curractrgrange < range)
//DEADCODE CSB 10/02/00 						)
//DEADCODE CSB 10/02/00 					{
//DEADCODE CSB 10/02/00 						callee = currac;
//DEADCODE CSB 10/02/00 						range = curractrgrange;
//DEADCODE CSB 10/02/00 					}
//DEADCODE CSB 10/02/00 				 }
//DEADCODE CSB 10/02/00 			}
//DEADCODE CSB 10/02/00 			currac = (AirStruc*)currac->nextmobile;
//DEADCODE CSB 10/02/00 		}
//DEADCODE CSB 10/02/00 		if (callee)
//DEADCODE CSB 10/02/00 		{
//DEADCODE CSB 10/02/00 			if 	(curractrgrange < VISIBLERANGE)
//DEADCODE CSB 10/02/00  				retval = SendMsgAndCall(ChooseBanditRelMsg(MSG_SPOTTEDBYOTHERS,callee,trg, callee,true),AttackingManoeuvre);
//DEADCODE CSB 10/02/00  			else
//DEADCODE CSB 10/02/00 				retval = SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_DENTIST_LOC_ENEMY,MSG_SPOTTEDBYOTHERS, VOICE_DENTIST,trg,callee), UnFriendlyFar);
//DEADCODE CSB 10/02/00 		}else
//DEADCODE CSB 10/02/00 		{//no CAP to go and help
//DEADCODE CSB 10/02/00 			if (		(friendlythatneedshelpldr->classtype->aerobaticfactor != AEROBATIC_LOW)	  //RDH 01/06/99
//DEADCODE CSB 10/02/00 					&&	((friendlythatneedshelpldr->duty&ACTIONCODE)!=DA_CAP)
//DEADCODE CSB 10/02/00 				)
//DEADCODE CSB 10/02/00 			{// friendly that needs help is not a medium bomber and not CAP, ie is a fighter bomber that should defend
//DEADCODE CSB 10/02/00 				if (trg->ai.eventlog->stage < EventLog::SEENBYOTHERS)
//DEADCODE CSB 10/02/00 				{
//DEADCODE CSB 10/02/00 					retval = SendMsgAndCall(ChooseBanditRelMsg(MSG_SPOTTEDBYOTHERS,callerldr,trg, friendlythatneedshelpldr,true), PotentialBounce);
//DEADCODE CSB 10/02/00 					if (callerldr->IsUsingPilotedAcLog())
//DEADCODE CSB 10/02/00 						Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
//DEADCODE CSB 10/02/00 					else
//DEADCODE CSB 10/02/00 						Persons2::UpdateLog(trg,0,EventLog::SEENBYOTHERS);
//DEADCODE CSB 10/02/00 				}
//DEADCODE CSB 10/02/00 			}
//DEADCODE CSB 10/02/00 		}
//DEADCODE CSB 10/02/00 	}
//DEADCODE CSB 10/02/00 	return(retval);
//DEADCODE CSB 10/02/00 
//DEADCODE CSB 10/02/00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedNewUnfriendly
//Author		Jim Taylor
//Date			Tue 22 Oct 1996
//
//Description	
//
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 bool	ArtInt::SpottedNewUnfriendly(AirStruc* caller,AirStruc* trg)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	ScriptTables script = ChooseSpottedScript(caller, trg);
//DeadCode AMM 20Oct100 	AirStrucPtr callee = caller->FindBuddy();
//DeadCode AMM 20Oct100 	if(callee)	
//DeadCode AMM 20Oct100 		_Radio.TriggerMsg(MESSAGE_STRUC(script, MSG_SPOT, caller, trg, callee));
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 	bool retval = FALSE;
//DeadCode AMM 20Oct100 	
//DeadCode AMM 20Oct100 	AirStruc* trggrplead = trg->FindGroupLeader();
//DeadCode AMM 20Oct100 	AirStruc* unfgrplead = NULL;
//DeadCode AMM 20Oct100 	if (		(caller->ai.unfriendly)
//DeadCode AMM 20Oct100 			&&	(caller->ai.unfriendly->Status.size==AIRSTRUCSIZE)
//DeadCode AMM 20Oct100 	   )
//DeadCode AMM 20Oct100 	{
//DeadCode AMM 20Oct100 		unfgrplead = ((AirStruc*)caller->ai.unfriendly)->FindGroupLeader();
//DeadCode AMM 20Oct100 	
//DeadCode AMM 20Oct100 		if (trggrplead != unfgrplead)
//DeadCode AMM 20Oct100 		{
//DeadCode AMM 20Oct100 			InterceptRangeFromTo(caller,trg);
//DeadCode AMM 20Oct100 			if 	(caller->Range  < ENGAGERANGE)
//DeadCode AMM 20Oct100 				if (caller->leader==NULL)
//DeadCode AMM 20Oct100 					if (trg->ai.attacker==NULL)
//DeadCode AMM 20Oct100 					{
//DeadCode AMM 20Oct100 						if (caller->IsUsingPilotedAcLog())
//DeadCode AMM 20Oct100 							if (!unfgrplead->IsUsingPilotedAcLog())
//DeadCode AMM 20Oct100 								Persons2::UpdateLog(unfgrplead,0,EventLog::APPROACHED);
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 						retval = ChooseManoeuvre(caller,trg,FALSE);
//DeadCode AMM 20Oct100 					}
//DeadCode AMM 20Oct100 		}
//DeadCode AMM 20Oct100 	}
//DeadCode AMM 20Oct100 	return(retval);
//DeadCode AMM 20Oct100 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseManoeuvre
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
bool	ArtInt::ChooseManoeuvre(AirStruc* caller,AirStruc* trg, bool newspot)
{
	bool retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_NULL,MSG_SPOTTEDASNEWUNFRIENDLY,caller,trg,caller), DecideTopCover);	
	return(retval);
}
//DEADCODE CSB 24/01/00 	bool retval;
//DEADCODE CSB 24/01/00 	tGroupLevel group = GroupLevel(caller);
//DEADCODE CSB 24/01/00 	if (group == GROUP_LONER)
//DEADCODE CSB 24/01/00 	{
//DEADCODE CSB 24/01/00 		retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_ENGAGE,MSG_CHOSENMANOEUVRE,caller,trg,NULL), SetupSelectTarget);	
//DEADCODE CSB 24/01/00 	}else
//DEADCODE CSB 24/01/00 	{
//DEADCODE CSB 24/01/00 		RndVal	rndnum = ((RndVal)Math_Lib.rnd(2));
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 		trg = trg->FindGroupLeaderInFormation();
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 		if  (		TargetOnCallerTail(caller, trg, ANGLES_80Deg)
//DEADCODE CSB 24/01/00 				&&	TargetFacingCaller(caller, trg, ANGLES_80Deg)
//DEADCODE CSB 24/01/00 				&&	((caller->World.Y - trg->World.Y) < FT_2000)
//DEADCODE CSB 24/01/00 			)
//DEADCODE CSB 24/01/00 		{//attacked from rear and no height advantage
//DEADCODE CSB 24/01/00 			if (EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
//DEADCODE CSB 24/01/00 			{
//DEADCODE CSB 24/01/00 				if (caller->Range > DANGERRANGE)
//DEADCODE CSB 24/01/00 					_Miles.SequenceAudible(MOOD_TROUBLED);
//DEADCODE CSB 24/01/00 				else
//DEADCODE CSB 24/01/00 					_Miles.SequenceAudible(MOOD_DOOMED);
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 			}
//DEADCODE CSB 24/01/00 			retval = SendMsgAndCall(ChooseBanditOnTailMsg(MSG_SPOTTED,caller,trg, caller,newspot),DefensiveManoeuvre1);
//DEADCODE CSB 24/01/00 		}
//DEADCODE CSB 24/01/00 		else
//DEADCODE CSB 24/01/00 		{
//DEADCODE CSB 24/01/00 			if((CallerFacingTarget(caller, trg, ANGLES_45Deg)) && (TargetFacingCaller(caller, trg, ANGLES_45Deg)))
//DEADCODE CSB 24/01/00 			{//head on
//DEADCODE CSB 24/01/00 				if (EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
//DEADCODE CSB 24/01/00 					_Miles.SequenceAudible(MOOD_TENSE);
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 				retval = SendMsgAndCall(ChooseBanditHeadOnMsg(MSG_SPOTTED,caller,trg, caller,newspot),AttackingManoeuvre);
//DEADCODE CSB 24/01/00 			}else
//DEADCODE CSB 24/01/00 			{
//DEADCODE CSB 24/01/00 				if (EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
//DEADCODE CSB 24/01/00 				{
//DEADCODE CSB 24/01/00 					if (		CallerOnTargetTail(caller, trg, ANGLES_45Deg)
//DEADCODE CSB 24/01/00 							&&	CallerFacingTarget(caller, trg, ANGLES_45Deg)
//DEADCODE CSB 24/01/00 						)
//DEADCODE CSB 24/01/00 						_Miles.SequenceAudible(MOOD_HOPEFUL);
//DEADCODE CSB 24/01/00 					else
//DEADCODE CSB 24/01/00 						_Miles.SequenceAudible(MOOD_NEUTRAL);
//DEADCODE CSB 24/01/00 
//DEADCODE CSB 24/01/00 				}
//DEADCODE CSB 24/01/00 				retval = SendMsgAndCall(ChooseBanditRelMsg(MSG_SPOTTED,caller,trg, caller,newspot),AttackingManoeuvre);
//DEADCODE CSB 24/01/00 			}
//DEADCODE CSB 24/01/00 		}
//DEADCODE CSB 24/01/00 	}
//DEADCODE CSB 24/01/00 	return ((bool)retval);
//DEADCODE CSB 24/01/00 }	


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseBanditRelMsg
//Author		R. Hyde 
//Date			Wed 20 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_STRUC	ArtInt::ChooseBanditRelMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot)
{
	ScriptTables script;

	if (newspot)
	{
			script = SCRIPT_BANDIT_RELPOS;
	}else
	{
		if (caller->Range < DANGERRANGE)
			script = SCRIPT_MOREBANDITSEXCITED;
		else
			script = SCRIPT_MOREBANDITS;
	}
	return(MESSAGE_STRUC(script, mtype,caller,trg, callee));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseBanditOnTailMsg
//Author		R. Hyde 
//Date			Wed 20 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_STRUC	ArtInt::ChooseBanditOnTailMsg(MsgType mtype, AirStruc* caller,AirStruc* trg, AirStruc* callee, bool newspot)
{
	ScriptTables script;

	if (newspot)
	{
		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
		if (rndpc >  RND50PC)
		{
				if(caller->nationality == NAT_RAF)
				{
					if (caller->Range < DANGERRANGE)
						script = SCRIPT_BANDITSBEHINDEXCITEDRAF;
					else
						script = SCRIPT_BANDITSBEHINDRAF;
				}else
				{
					if (caller->Range < DANGERRANGE)
						script = SCRIPT_BANDITSBEHINDEXCITEDLW;
					else
						script = SCRIPT_BANDITSBEHINDLW;
				}
		}else
			script = SCRIPT_BANDIT_RELPOS;
	}else
	{
		if (caller->Range < DANGERRANGE)
			script = SCRIPT_MOREBANDITSEXCITED;
		else
			script = SCRIPT_MOREBANDITS;
	}
	return(MESSAGE_STRUC(script, mtype,caller,trg, callee));
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChooseBanditHeadOnMsg
//Author		R. Hyde 
//Date			Wed 20 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
MESSAGE_STRUC	ArtInt::ChooseBanditHeadOnMsg(MsgType mtype, AirStruc* caller,AirStruc* trg,AirStruc*  callee, bool newspot)
{
	ScriptTables script;

	if (newspot)
	{
		RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);
		if (rndpc >  RND50PC)
		{
			if(caller->nationality == NAT_RAF)
				script = SCRIPT_BANDITSAHEADRAF;
			else
				script = SCRIPT_BANDITSAHEADLW;
		}
		else
			script = SCRIPT_BANDIT_RELPOS;
	}else
	{
		if (caller->Range < DANGERRANGE)
			script = SCRIPT_MOREBANDITSEXCITED;
		else
			script = SCRIPT_MOREBANDITS;
	}
	return(MESSAGE_STRUC(script, mtype,caller,trg, callee));
}


//DEADCODE CSB 04/05/00 //------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 //Procedure		
//DEADCODE CSB 04/05/00 //Author		R. Hyde 
//DEADCODE CSB 04/05/00 //Date			21 Jan 1999
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Description	
//DEADCODE CSB 04/05/00 //			   	
//DEADCODE CSB 04/05/00 //				
//DEADCODE CSB 04/05/00 //Inputs		
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Returns	
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 TABLEAI(FriendliesUnderAttack, AirStrucPtr)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 	{PHRASE_NULL,	&SetupSelectTarget,	PHRASE_NULL},	  //RDH 24/05/99
//DEADCODE CSB 04/05/00 	{PHRASE_NULL,	&DoNothing,			PHRASE_NULL},
//DEADCODE CSB 04/05/00 	{PHRASE_NULL},
//DEADCODE CSB 04/05/00 	{PHRASE_NULL}
//DEADCODE CSB 04/05/00 };
//DEADCODE CSB 04/05/00 INSTANCEAI(FriendliesUnderAttack, AirStrucPtr)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 	bool retval = false;
//DEADCODE CSB 04/05/00 	if (caller->ai.morale >= MORALE_GOOD)
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		AirStruc*	recipient = caller;
//DEADCODE CSB 04/05/00 		if 	(		(trg->ai.unfriendly)
//DEADCODE CSB 04/05/00 				&&	(trg->ai.unfriendly->Status.size==AIRSTRUCSIZE)
//DEADCODE CSB 04/05/00 			)
//DEADCODE CSB 04/05/00 			  recipient = (AirStruc*)trg->ai.unfriendly;
//DEADCODE CSB 04/05/00 		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_OUTNUMBEREDREPLY, MSG_MIGREPORTED_REPLY, caller, trg, recipient));
//DEADCODE CSB 04/05/00 		retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_SELECTYOUROWNTARGETS, MSG_ASSISTFRIENDLIESUNDERATTACK,caller, trg, caller),SetupSelectTarget);
//DEADCODE CSB 04/05/00 	}
//DEADCODE CSB 04/05/00 	return(retval);
//DEADCODE CSB 04/05/00 }


//DEADCODE CSB 04/05/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE CSB 04/05/00 //Procedure		DoesFriendNeedHelp
//DEADCODE CSB 04/05/00 //Author		R. Hyde 
//DEADCODE CSB 04/05/00 //Date			Fri 27 Feb 1998
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Description	Assess whether friendly needs helping out
//DEADCODE CSB 04/05/00 //				caller and trg are same nationality
//DEADCODE CSB 04/05/00 //Inputs		
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //Returns	
//DEADCODE CSB 04/05/00 //
//DEADCODE CSB 04/05/00 //------------------------------------------------------------------------------
//DEADCODE CSB 04/05/00 bool	ArtInt::DoesFriendNeedHelp(AirStruc* caller, AirStruc* trg)
//DEADCODE CSB 04/05/00 {
//DEADCODE CSB 04/05/00 	SLong	RangeEyeTrg = caller->Range;
//DEADCODE CSB 04/05/00 	bool retval = FALSE;
//DEADCODE CSB 04/05/00 	if( ((trg->duty & PACK_AM_MASK) == PACK_AM_LWSTART && trg->duty!=PACK_AM_DECOYPATROL) || (trg->classtype->aerobaticfactor == AEROBATIC_LOW) )
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		if (	(trg->ai.attacker)
//DEADCODE CSB 04/05/00 			&&	(trg->ai.attacker->Status.size==AIRSTRUCSIZE)
//DEADCODE CSB 04/05/00 			&&	(!trg->ai.attacker->ai.attacker)
//DEADCODE CSB 04/05/00 			&&	(trg->Range < VISIBLERANGE)
//DEADCODE CSB 04/05/00 			)
//DEADCODE CSB 04/05/00 		{
//DEADCODE CSB 04/05/00 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BANDIT_RELPOS, MSG_BOGEYCALL, caller, trg->ai.attacker,trg));
//DEADCODE CSB 04/05/00 		}
//DEADCODE CSB 04/05/00 	}
//DEADCODE CSB 04/05/00 	else
//DEADCODE CSB 04/05/00 	if( ((caller->duty & PACK_AM_MASK) == PACK_AM_LWSTART && caller->duty!=PACK_AM_DECOYPATROL) || (caller->classtype->aerobaticfactor == AEROBATIC_LOW) )
//DEADCODE CSB 04/05/00 	{//non CAP a/c including bombers cannot consider helping
//DEADCODE CSB 04/05/00 		if (	trg->ai.attacker
//DEADCODE CSB 04/05/00 			&&	trg->ai.attacker->Status.size==AIRSTRUCSIZE
//DEADCODE CSB 04/05/00 			)
//DEADCODE CSB 04/05/00 		{//trg has attacker that is an aircraft
//DEADCODE CSB 04/05/00 			caller->InterceptandRange(&trg->ai.attacker->World);
//DEADCODE CSB 04/05/00 			if (		(!caller->ai.unfriendly)
//DEADCODE CSB 04/05/00 					||	(((AirStruc*)caller->ai.unfriendly)->nationality == caller->nationality)
//DEADCODE CSB 04/05/00 					||	((RangeEyeTrg - caller->Range) > MILES01)
//DEADCODE CSB 04/05/00 					||	(caller->movecode == AUTO_TRACKINGBOGIE)		//busy but just tracking bogies
//DEADCODE CSB 04/05/00 					||	((caller == Persons2::PlayerGhostAC) && (Persons2::PlayerSeenAC->movecode == AUTO_TRACKINGBOGIE))
//DEADCODE CSB 04/05/00 				)
//DEADCODE CSB 04/05/00 			{//caller doesn't have unf or unf is really on caller's side or this attacker closer
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 				if 	(!((AirStruc*)*trg->ai.attacker)->ai.attacker)
//DEADCODE CSB 04/05/00 				{//trg attacker is not under attack
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 					if (trg->classtype->aerobaticfactor == AEROBATIC_LOW)
//DEADCODE CSB 04/05/00 						SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_UNPROTECTEDBOMBERUNDERATTACK,MSG_FRIENDLIESUNDERATTACK,caller,(AirStruc*)*trg->ai.attacker,caller),FriendliesUnderAttack);
//DEADCODE CSB 04/05/00 					else
//DEADCODE CSB 04/05/00 						SendMsgAndCall(MESSAGE_STRUC(SCRIPT_FIGHTERSNEEDHELP,MSG_FRIENDLIESUNDERATTACK,caller,(AirStruc*)*trg->ai.attacker,caller),FriendliesUnderAttack);
//DEADCODE CSB 04/05/00 				}else
//DEADCODE CSB 04/05/00 				{
//DEADCODE CSB 04/05/00 					if (trg->classtype->aerobaticfactor == AEROBATIC_LOW)
//DEADCODE CSB 04/05/00 						SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_PROTECTEDBOMBERUNDERATTACK,MSG_FRIENDLIESUNDERATTACK,caller,(AirStruc*)*trg->ai.attacker,caller),FriendliesUnderAttack);
//DEADCODE CSB 04/05/00 					else
//DEADCODE CSB 04/05/00 					{
//DEADCODE CSB 04/05/00 						if (EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
//DEADCODE CSB 04/05/00 						{
//DEADCODE CSB 04/05/00 							if (trg->ai.eventlog->stage < EventLog::SPOTTEDDOGFIGHT)
//DEADCODE CSB 04/05/00 							{
//DEADCODE CSB 04/05/00 								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DOGFIGHT, MSG_FRIENDLIESUNDERATTACK, caller, trg, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 04/05/00 								Persons2::UpdateLog(trg,0,EventLog::SPOTTEDDOGFIGHT);
//DEADCODE CSB 04/05/00 							}
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 						}
//DEADCODE CSB 04/05/00 					}
//DEADCODE CSB 04/05/00 				}
//DEADCODE CSB 04/05/00 			}else
//DEADCODE CSB 04/05/00 			{//friendly needs help but we are busy
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 				AlertFighters(caller,trg->ai.attacker,trg);
//DEADCODE CSB 04/05/00 			}
//DEADCODE CSB 04/05/00 		}else
//DEADCODE CSB 04/05/00 		{//seen friendly not under attack
//DEADCODE CSB 04/05/00 				if  (		(Manual_Pilot.ControlledAC2->fly.pModel)
//DEADCODE CSB 04/05/00 				&&	(!Manual_Pilot.ControlledAC2->fly.pModel->GearTouched)
//DEADCODE CSB 04/05/00 				)
//DEADCODE CSB 04/05/00 				if (trg->Range<RECOGNISERANGE-METRES500)
//DEADCODE CSB 04/05/00 				if	(		(EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
//DEADCODE CSB 04/05/00 						&&	(trg->movecode != AUTO_FAC)			//don't want to be told about fac
//DEADCODE CSB 04/05/00 						&&	(!caller->InSameWave(trg))
//DEADCODE CSB 04/05/00 						&&	(!caller->formpos)					//only let group leaders through
//DEADCODE CSB 04/05/00 					)
//DEADCODE CSB 04/05/00 					{
//DEADCODE CSB 04/05/00 						if (trg->ai.eventlog->stage < EventLog::SEENBYPLAYERS)
//DEADCODE CSB 04/05/00 						{
//DEADCODE CSB 04/05/00 	 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FRIENDLIES, MSG_FRIENDLIESNOTUNDERATTACK, caller, trg, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 04/05/00 							caller->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);
//DEADCODE CSB 04/05/00 						}
//DEADCODE CSB 04/05/00 						Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
//DEADCODE CSB 04/05/00 					}
//DEADCODE CSB 04/05/00 		}
//DEADCODE CSB 04/05/00 
//DEADCODE CSB 04/05/00 	//	caller->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);		
//DEADCODE CSB 04/05/00 	//	caller->PlayerSequenceAudible(FIL_MUSIC_SNEAKING_AWAY);		
//DEADCODE CSB 04/05/00 	}else
//DEADCODE CSB 04/05/00 	{
//DEADCODE CSB 04/05/00 		if  (		(Manual_Pilot.ControlledAC2->fly.pModel)
//DEADCODE CSB 04/05/00 		&&	(!Manual_Pilot.ControlledAC2->fly.pModel->GearTouched)
//DEADCODE CSB 04/05/00 		)
//DEADCODE CSB 04/05/00 		if (trg->Range<RECOGNISERANGE-METRES500)
//DEADCODE CSB 04/05/00 		if	(		(EyeIsAndTrgIsNotInPlayersGroup(caller, trg))
//DEADCODE CSB 04/05/00 				&&	(trg->movecode != AUTO_FAC)			//don't want to be told about fac
//DEADCODE CSB 04/05/00 				&&	(!caller->InSameWave(trg))
//DEADCODE CSB 04/05/00 				&&	(!caller->formpos)					//only let group leaders through
//DEADCODE CSB 04/05/00 			)
//DEADCODE CSB 04/05/00 			{
//DEADCODE CSB 04/05/00 				if (trg->ai.eventlog->stage < EventLog::SEENBYPLAYERS)
//DEADCODE CSB 04/05/00 				{
//DEADCODE CSB 04/05/00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FRIENDLIES, MSG_FRIENDLIESNOTUNDERATTACK, caller, trg, Manual_Pilot.ControlledAC2));
//DEADCODE CSB 04/05/00 					caller->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);
//DEADCODE CSB 04/05/00 				}
//DEADCODE CSB 04/05/00 				Persons2::UpdateLog(trg,0,EventLog::SEENBYPLAYERS);
//DEADCODE CSB 04/05/00 			}
//DEADCODE CSB 04/05/00 	}
//DEADCODE CSB 04/05/00 	caller->Range = RangeEyeTrg;
//DEADCODE CSB 04/05/00 	return(retval);
//DEADCODE CSB 04/05/00 }		

			
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IfEyeIsAndTrgIsNotUsingPilotedAcLog
//Author		R. Hyde 
//Date			Wed 20 Jan 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 bool	ArtInt::EyeIsAndTrgIsNotInPlayersGroup(AirStruc* caller,AirStruc* trg)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	if  (		(caller->PlayerInGroup())
//DeadCode AMM 20Oct100 			&&	(!trg->PlayerInGroup())
//DeadCode AMM 20Oct100 		)
//DeadCode AMM 20Oct100 	   	return(true);
//DeadCode AMM 20Oct100 	else
//DeadCode AMM 20Oct100 		return(false);
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 //DEADCODE RDH 22/06/99  	if 	(		(caller->IsUsingPilotedAcLog())
//DeadCode AMM 20Oct100 //DEADCODE RDH 22/06/99  			&& (!trg->IsUsingPilotedAcLog())
//DeadCode AMM 20Oct100 //DEADCODE RDH 22/06/99  		)
//DeadCode AMM 20Oct100 //DEADCODE RDH 22/06/99  			return(true);
//DeadCode AMM 20Oct100 //DEADCODE RDH 22/06/99  		else
//DeadCode AMM 20Oct100 //DEADCODE RDH 22/06/99  			return(false);
//DeadCode AMM 20Oct100 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		EngageAppropriate()
//Author		R. Hyde 
//Date			29/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::EngageAppropriate(AirStruc* caller,AirStruc* trg)
{
	bool retval = true;
	for(AirStrucPtr ld = caller; (ld) && (retval); ld = ld->fly.nextflight)
		for(AirStrucPtr ac = ld; (ac) && (retval); ac = ac->Follower())
			if(ac->ai.manoeuvre == MANOEUVRE_SCREWYOUGUYSIMGOINGHOME)
				retval = false;

	if((retval) && (caller->GroupShouldGoHome(0.5)))
		retval = false;

	return(retval);
}

//DeadCode CSB 14Sep00 	bool retval;
//DeadCode CSB 14Sep00 	if (	(caller->ai.threatlevel > BANDITFIRING)
//DeadCode CSB 14Sep00 		||	((caller->Range < WEAPONSRANGE) &&	(caller->ai.threatlevel >= BANDITINWEAPONSRANGE))
//DeadCode CSB 14Sep00 		||	((caller->Range < DANGERRANGE) &&	(caller->ai.threatlevel >= BANDITINDANGERRANGE))
//DeadCode CSB 14Sep00 		||	((caller->Range < ENGAGERANGE) &&	(caller->ai.threatlevel >= BANDITINENGAGERANGE))
//DeadCode CSB 14Sep00 		||	((caller->Range < COMBATRANGE) &&	(caller->ai.threatlevel >= BANDITINCOMBATRANGE))
//DeadCode CSB 14Sep00 		||	(caller->ai.threatlevel >= BANDITANYWHERE)
//DeadCode CSB 14Sep00 		||	(		(caller->ai.threatlevel == BANDITINENGAGERANGEOFFRIENDLY)
//DeadCode CSB 14Sep00 				&& 	(trg->ai.unfriendly)
//DeadCode CSB 14Sep00 				&& 	(RangeFromTo(trg, (AirStruc*)trg->ai.unfriendly) < ENGAGERANGE)
//DeadCode CSB 14Sep00 			)
//DeadCode CSB 14Sep00 	   )
//DeadCode CSB 14Sep00 	{//according to threat level it is ok for caller to respond 
//DeadCode CSB 14Sep00 
//DeadCode CSB 14Sep00 //DEADCODE RDH 08/03/99 		if 	(!DecoysInGroup(caller))
//DeadCode CSB 14Sep00 //DEADCODE RDH 08/03/99 		{
//DeadCode CSB 14Sep00 			if (!(	(caller->Range > DANGERRANGE)
//DeadCode CSB 14Sep00 					&&
//DeadCode CSB 14Sep00 					(		(caller->ai.aggressionlevel == AL_TRAINING)
//DeadCode CSB 14Sep00 						||	(		(caller->ai.aggressionlevel == AL_DEFENSIVE) 
//DeadCode CSB 14Sep00 								&&	(		((trg->nationality == NAT_RED) && (!AcHasBombs(trg)))
//DeadCode CSB 14Sep00 										||	((trg->nationality == NAT_BLUE) && ((caller->World.Y - trg->World.Y) > FT_3000)))
//DeadCode CSB 14Sep00 									)
//DeadCode CSB 14Sep00 						||	((caller->ai.aggressionlevel == AL_ATTACKBOMBERSONLY) && (trg->classtype->aerobaticfactor >= AEROBATIC_FIGHTER))
//DeadCode CSB 14Sep00 						||	((caller->ai.aggressionlevel == AL_SPLITFORCE) && (!ForceHasBombers(trg)))
//DeadCode CSB 14Sep00 						||	(		(caller->ai.aggressionlevel == AL_ATTACKWEAKNESSES) 
//DeadCode CSB 14Sep00 								&&	(		!BingoFuel(trg)
//DeadCode CSB 14Sep00 										&&	!trg->AircraftDamaged()
//DeadCode CSB 14Sep00 										&&	!Winchester(trg)
//DeadCode CSB 14Sep00 									)
//DeadCode CSB 14Sep00 							)															
//DeadCode CSB 14Sep00 						 ||	(		(caller->nationality == NAT_BLUE) //RDH 30/06/99
//DeadCode CSB 14Sep00 								&&	(trg->World.Y >= FT_45000)		  //RDH 30/06/99
//DeadCode CSB 14Sep00 
//DeadCode CSB 14Sep00 							)
//DeadCode CSB 14Sep00 					)
//DeadCode CSB 14Sep00 				))
//DeadCode CSB 14Sep00 			{
//DeadCode CSB 14Sep00 					retval = true;
//DeadCode CSB 14Sep00 			}else
//DeadCode CSB 14Sep00 				retval = false;
//DeadCode CSB 14Sep00 //DEADCODE RDH 08/03/99 		}else
//DeadCode CSB 14Sep00 //DEADCODE RDH 08/03/99 			retval = false;
//DeadCode CSB 14Sep00 	}else
//DeadCode CSB 14Sep00 		//## wait for threatlevel is setup, change to false then 
//DeadCode CSB 14Sep00 		retval = true;
//DeadCode CSB 14Sep00 	return(retval);
//DeadCode CSB 14Sep00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindGroupLeaderInFormation()
//Author		R. Hyde 
//Date			29/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStruc* AirStruc::FindGroupLeaderInFormation()
{
	AirStruc* grplead;
	grplead = this;
	//find the leader to go for
	//Always go for leader of target's flight
	if (grplead->information && grplead->leader)
		grplead=*grplead->leader;
	//go for their group leader
	if (grplead->formpos && grplead->fly.leadflight && grplead->information)
		grplead=grplead->fly.leadflight->GetLeadAc();

	return(grplead);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindGroupLeaderClose()
//Author		R. Hyde 
//Date			29/1/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStruc* AirStruc::FindGroupLeaderClose()
{
	AirStruc* grplead;
	grplead = this;
	//find the leader to go for
	//Always go for leader of target's flight
	if (grplead->leader && Art_Int.AircraftAreClose(grplead, (AirStruc*)grplead->leader))
		grplead=*grplead->leader;
	//go for their group leader
	if (grplead->formpos && grplead->fly.leadflight && Art_Int.AircraftAreClose(grplead, grplead->fly.leadflight))
		grplead=grplead->fly.leadflight->GetLeadAc();

	return(grplead);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindGroupLeader()
//Author		R. Hyde 
//Date			 //RDH 18/02/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStruc* AirStruc::FindGroupLeader()
{
	AirStruc* grplead;
	grplead = this;
	//find the leader to go for
	if(grplead->leader)
		grplead = grplead->Leader();
	//go for their group leader
	if((grplead->formpos) && (grplead->fly.leadflight))
		grplead = grplead->fly.leadflight->GetLeadAc();

	return(grplead);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		
//Author		R. Hyde 
//Date			 //RDH 18/02/99
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 bool ArtInt::Escorting(AirStruc* ac)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	AirStruc* grplead = ac->FindGroupLeader();
//DeadCode AMM 20Oct100 	if (grplead->fly.leadflight)
//DeadCode AMM 20Oct100 		return (true);
//DeadCode AMM 20Oct100 	else
//DeadCode AMM 20Oct100 		return(false);
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroupLevel
//Author		R. Hyde 
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ArtInt::tGroupLevel ArtInt::GroupLevel(AirStruc* caller)
{
	if (		(caller->leader)
	   		&&  (caller->leader->information)
		)
		caller = (AirStruc*)caller->leader;

	if (		(caller->fly.leadflight)
	   		&&  (caller->fly.leadflight->information)
		)
		caller = (AirStruc*)caller->fly.leadflight;

	if 	(		(caller->fly.nextflight)
	   		&&  (caller->fly.nextflight->information)
		)
	{
		if 	(		(caller->fly.nextflight->fly.nextflight)
		   		&&  (caller->fly.nextflight->fly.nextflight->information)
			)
			return(GROUP_SQUADRON);
		else
			return(GROUP_FLIGHT);

//DEADCODE RDH 23/02/99 		 AirStruc*	currac = caller->fly.nextflight;
//DEADCODE RDH 23/02/99 		 int count = 1;
//DEADCODE RDH 23/02/99 		 while  (		(currac->fly.nextflight)
//DEADCODE RDH 23/02/99 					&&	(currac->fly.nextflight->information)
//DEADCODE RDH 23/02/99 				)
//DEADCODE RDH 23/02/99 		 {
//DEADCODE RDH 23/02/99 			currac = currac->fly.nextflight;
//DEADCODE RDH 23/02/99 			count++;
//DEADCODE RDH 23/02/99 		 }
//DEADCODE RDH 23/02/99 		if (count >= 6)
//DEADCODE RDH 23/02/99 			//squadron is 6 or more "elements" or flights in internal naming
//DEADCODE RDH 23/02/99 			return(GROUP_SQUADRON);
//DEADCODE RDH 23/02/99 		else
//DEADCODE RDH 23/02/99 			return(GROUP_FLIGHT);

	}else
	{
		if  (	(caller->Follower())
	   		&&  (caller->Follower()->information)
			)
			return(GROUP_ELEMENT);
		else
			return(GROUP_LONER);
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroupLevelNotInFormation
//Author		R. Hyde 
//Date			Mon 16 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ArtInt::tGroupLevel ArtInt::GroupLevelNotInFormation(AirStruc* caller)
{
	if (caller->leader)
		caller = (AirStruc*)caller->leader;

	if (caller->fly.leadflight)
		caller = (AirStruc*)caller->fly.leadflight;

	if 	(		(caller->fly.nextflight)
		)
	{
		if 	(		(caller->fly.nextflight->fly.nextflight)
			)
			return(GROUP_SQUADRON);
		else
			return(GROUP_FLIGHT);

	}else
	{
		if  (	(caller->Follower())
			)
			return(GROUP_ELEMENT);
		else
			return(GROUP_LONER);
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptandRange
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description		
//
//Inputs		
//
//Returns	"Global" Range, HdgIntercept and PitchIntercept
//
//------------------------------------------------------------------------------
void ArtInt::InterceptRangeFromTo(AirStruc* from, AirStruc* to)

{


	SLong deltax = to->World.X - from->World.X;
	SLong deltay = to->World.Y - from->World.Y;
	SLong deltaz = to->World.Z - from->World.Z;
	Math_Lib.Intercept (deltax,deltay,deltaz,from->Range,from->HdgIntercept,from->PitchIntercept);
}
SLong ArtInt::RangeFromTo(AirStruc* from, AirStruc* to)
{
	ANGLES	oldhdgint, oldpitchint;
	SLong	oldrange;
	SLong range;
	
	oldhdgint = from->HdgIntercept;
	oldpitchint = from->PitchIntercept;
	oldrange  = from->Range;

	InterceptRangeFromTo(from, to);
	range = from->Range;

	from->PitchIntercept = oldpitchint;
	from->HdgIntercept = oldhdgint;
	from->Range = oldrange;


	return (range);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcHasBombs
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 bool ArtInt::AcHasBombs(AirStruc* trg)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	return(true);
//DeadCode AMM 20Oct100 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceHasBombers(trg)
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 bool ArtInt::ForceHasBombers(AirStruc* trg)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	return(true);
//DeadCode AMM 20Oct100 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BingoFuel
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 bool ArtInt::BingoFuel(AirStruc* trg)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	return(true);
//DeadCode AMM 20Oct100 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Winchester
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 bool ArtInt::Winchester(AirStruc* trg)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	return(true);
//DeadCode AMM 20Oct100 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetUpRemainderOfGroupToEngage
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
void	ArtInt::SetUpRemainderOfGroupToEngage(AirStruc* caller,AirStruc* trg,MANOEUVRE manoeuvre,ANGLES desiredhdg,ANGLES  desiredpitch, bool surprised)
{
	for(AirStrucPtr ldr = caller; ldr; ldr = ldr->fly.nextflight)
		for(AirStrucPtr ac = ldr; ac; ac = ac->Follower())
			if((ac != caller) && (!ac->ai.unfriendly) && (ac->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER))
			{
				AirStrucPtr newtrg = NULL;
				AirStrucPtr starttrg = trg->FindFormpos0();
				if(starttrg->classtype->aerobaticfactor == AEROBATIC_LOW)
					while(starttrg->fly.nextflight)
						starttrg = starttrg->fly.nextflight;

				for(AirStrucPtr trgldr = starttrg; (trgldr) && (!newtrg); trgldr = trgldr->fly.nextflight)
					for(AirStrucPtr trgac = trgldr; (trgac) && (!newtrg); trgac = trgac->Follower())
						if((!trgac->ai.attacker) && (!trgac->Status.deadtime))
							newtrg = trgac;

				if(!newtrg) 
					newtrg = starttrg;
			 	SetEngage(ac, newtrg, manoeuvre, desiredhdg, desiredpitch, surprised);
			}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrepareForCombat
//Author		 //RDH 04/03/99
//Date			
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::PrepareForCombat(AirStrucPtr caller)
{
//DEADCODE CSB 14/02/00 	if (		(caller->nationality == Manual_Pilot.ControlledAC2->nationality)
//DEADCODE CSB 14/02/00 			&&	(caller->AcIsGroupLeader()) 
//DEADCODE CSB 14/02/00 			&& (!caller->AcIsPlayer())
//DEADCODE CSB 14/02/00 			&&	(!caller->weap.FuelDumped)
//DEADCODE CSB 14/02/00 		)
//DEADCODE CSB 14/02/00 	{
//DEADCODE CSB 14/02/00 		AirStruc*	callee = caller->FindABuddyWithPlayerGivenPriority();
//DEADCODE CSB 14/02/00 		if (!callee)
//DEADCODE CSB 14/02/00 			//if there is no buddy pilot talks to himself
//DEADCODE CSB 14/02/00 			callee = caller;
//DEADCODE CSB 14/02/00 //DEADCODE CSB 14/02/00  		SendMsgAndCall(MESSAGE_STRUC(OLDSCRIPT_JETTISONTANK, MSG_STATUSREQUEST, caller, NULL, callee), JettisonTanks);	
//DEADCODE CSB 14/02/00  
//DEADCODE CSB 10/01/00   		if	(		(caller->classtype->visible != F86)
//DEADCODE CSB 10/01/00 				&&	(caller->classtype->phrasename != PHRASE_MIGS)
//DEADCODE CSB 10/01/00 //DEADCODE RDH 10/05/99   				&&	(caller->classtype->visible != MIG15)
//DEADCODE CSB 10/01/00  				&&	(!caller->weap.StoresDumped)
//DEADCODE CSB 10/01/00   			)
//DEADCODE CSB 10/01/00   			SendMsgAndCall(MESSAGE_STRUC(SCRIPT_JETTISONSTORES, MSG_STATUSREQUEST, caller, NULL, callee), JettisonStores);	
//DEADCODE CSB 14/02/00 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetEngage
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
void	ArtInt::SetEngage(AirStrucPtr caller,AirStrucPtr trg,MANOEUVRE manoeuvre,ANGLES   desiredhdg,ANGLES   desiredpitch, bool surprised)
{
#ifndef	NDEBUG
 	if(caller->classtype->aerobaticfactor == AEROBATIC_LOW)
 		INT3;				 	//TRYING TO PUT A HEAVY BOMBER INTO COMBAT
	if(trg == caller)
		INT3;					//TRYING TO GO INTO COMBAT WITH SELF
	if((caller) && (trg) && (trg->nationality == caller->nationality))
		INT3;					//TRYING TO ATTACK A FRIENDLY
	if((caller->fly.numinsag) && (caller->fly.expandedsag))				//CSB 31Jul00
		INT3;															//CSB 31Jul00
	if((!caller->fly.numinsag) && (trg->fly.numinsag) && (trg->fly.expandedsag))					//CSB 31Jul00
		INT3;															//CSB 31Jul00
	if((caller->Status.deadtime && !caller->uniqueID.commsmove) || (trg->Status.deadtime && !trg->uniqueID.commsmove))
		INT3;
	if(trg->IsOutNumberedBy(2.0))
		int DoNothingForABreakPoint = 0;
	caller->DoAllSAGChecks();													//CSB 1Aug00
	if(caller->ai.manoeuvre == MANOEUVRE_DISENGAGED)
		int DoNothingForABreakpoint = 0;
#endif

	if((caller->fly.numinsag) && (caller->fly.expandedsag))				//CSB 31Jul00
		caller = caller->fly.expandedsag;								//CSB 31Jul00
	
	if((trg->fly.numinsag) && (trg->fly.expandedsag))					//CSB 31Jul00
		trg = trg->fly.expandedsag;										//CSB 31Jul00

	if((caller->fly.numinsag) && (!caller->fly.expandedsag) && (!trg->fly.numinsag))	//CSB 1Aug00
		trg = trg->fly.expandedsag;														//CSB 1Aug00

	if (caller->IsUsingPilotedAcLog() || (trg && trg->IsUsingPilotedAcLog()))//JIM 03Jun99
		OverLay.CancelAccel();									//JIM 03Jun99

	caller->ai.desiredrange = 0;										//CSB 26Jun00

	if (caller==Persons2::PlayerSeenAC)							//AMM 28Aug98
		caller=Persons2::PlayerGhostAC;							//AMM 28Aug98

//I don't know why we did this, it messes up links 
//DEADCODE RDH 13/06/99 	if (	caller->ai.unfriendly
//DEADCODE RDH 13/06/99 		&&	caller->ai.unfriendly->Status.size==AIRSTRUCSIZE
//DEADCODE RDH 13/06/99 		&& ((AirStrucPtr)*caller->ai.unfriendly)->ai.attacker==caller
//DEADCODE RDH 13/06/99 		)
//DEADCODE RDH 13/06/99 		((AirStrucPtr)*caller->ai.unfriendly)->ai.attacker=NULL;
	if(caller->movecode == AUTO_BOMB)									//CSB 16Aug00
	{
		caller->movecode = AUTO_FOLLOWWP;								//CSB 16Aug00
		caller->information = IF_OUT_POS;					//CSB 22Aug00
		caller->ai.unfriendly = NULL;
	}


	if (trg)
	{
		if (Manual_Pilot.ControlledAC2 == trg)
		{
			trg = Persons2::PlayerGhostAC;
		}
//DeadCode AMM 28Aug98 		if (!_Replay.Playback && caller==Persons2::PlayerGhostAC)
//DeadCode AMM 28Aug98 		{
//DeadCode AMM 28Aug98 	//		Manual_Pilot.AutoToggle(Manual_Pilot.AUTO);
//DeadCode AMM 28Aug98 //			Manual_Pilot.AutoToggle(Manual_Pilot.AUTO);
//DeadCode AMM 28Aug98 			caller= Manual_Pilot.ControlledAC2;
//DeadCode AMM 28Aug98 		}

//DEADCODE CSB 07/03/00 		if  (		(caller->ai.unfriendly==trg)
//DEADCODE CSB 07/03/00 				&&	(caller->movecode != AUTO_TRACKINGBOGIE)
//DEADCODE CSB 07/03/00 			)
//DEADCODE CSB 07/03/00 		{	//informational
//DEADCODE CSB 07/03/00 			//usually set up already 
//DEADCODE CSB 07/03/00 			//if coming from precombat we need to switch to combat
//DEADCODE CSB 07/03/00 				if (		(caller->Range  < COMBATRANGE)
//DEADCODE CSB 07/03/00 						&&	(caller->movecode==AUTO_PRECOMBAT)
//DEADCODE CSB 07/03/00 					)
//DEADCODE CSB 07/03/00 				{
//DEADCODE CSB 07/03/00 					caller->information=IF_OUT_POS;
//DEADCODE CSB 07/03/00 					caller->manoeuvretime=0;
//DEADCODE CSB 07/03/00 					caller->movecode=AUTO_COMBAT;
//DEADCODE CSB 07/03/00 //DEADCODE RDH 06/04/99 					caller->ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE CSB 07/03/00 
//DEADCODE CSB 07/03/00 				}else if (caller->movecode != AUTO_COMBAT)
//DEADCODE CSB 07/03/00 				{
//DEADCODE CSB 07/03/00 					caller->movecode=AUTO_PRECOMBAT;
//DEADCODE CSB 07/03/00 				}
		if(caller->ai.unfriendly == trg)								//CSB 07/03/00
		{																//CSB 07/03/00
			caller->information = IF_OUT_POS;							//CSB 07/03/00
			caller->movecode = AUTO_COMBAT;							//CSB 07/03/00
			caller->ai.manoeuvre = manoeuvre;							//CSB 07/03/00
			caller->ai.ManStep = PHASE0;								//CSB 07/03/00
			caller->manoeuvretime = 0;									//CSB 07/03/00
		}
		else
		{//new engage

			PrepareForCombat(caller);
			caller->ai.ManStep = PHASERESET;
			if (manoeuvre != MANOEUVRE_SELECT)
			{
				caller->ai.manoeuvre = manoeuvre;
				caller->ai.desiredhdg = desiredhdg;
				caller->ai.desiredpitch = desiredpitch;
			}else
			{
				caller->ai.desiredhdg = ANGLES_0Deg;
				caller->ai.desiredpitch = ANGLES_0Deg;
			
//DEADCODE RDH 24/02/99 				if (caller->ai.firsttactic == TACTIC_LINEASTERN)
//DEADCODE RDH 24/02/99 					caller->ai.manoeuvre = MANOEUVRE_LINEASTERN;
//DEADCODE RDH 24/02/99 				else if (caller->ai.firsttactic == TACTIC_LINEABREAST)
//DEADCODE RDH 24/02/99 					caller->ai.manoeuvre = MANOEUVRE_LINEABREAST;
//DEADCODE RDH 24/02/99 				else if (caller->ai.firsttactic == TACTIC_DIVEANDZOOM)
//DEADCODE RDH 24/02/99 					caller->ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
//DEADCODE RDH 24/02/99 				else if (caller->ai.firsttactic == TACTIC_SCATTER)
//DEADCODE RDH 24/02/99 					caller->ai.manoeuvre = MANOEUVRE_LEADPURSUIT;
//DEADCODE RDH 05/04/99 				if (	(caller->ai.firsttactic == TACTIC_ROUNDABOUT)
//DEADCODE RDH 05/04/99 							&&		(caller->ai.threatlevel != BANDITFIRING)	
//DEADCODE RDH 05/04/99 							&&		(caller->ai.threatlevel != BANDITINENGAGERANGEOFFRIENDLY)
//DEADCODE RDH 05/04/99 						)
//DEADCODE RDH 05/04/99 					SetRoundAboutAc(caller);
//DEADCODE RDH 05/04/99 				else
					caller->ai.manoeuvre=MANOEUVRE_SELECT;
			}
//DeadCode CSB 1Aug00 			if (trg)
//DeadCode CSB 1Aug00 			{
//DeadCode CSB 1Aug00 
//DeadCode CSB 1Aug00 				if (	!trg->ai.attacker
//DeadCode CSB 1Aug00 					||	AirStrucPtr(*trg->ai.attacker)->ai.unfriendly!=trg
//DeadCode CSB 1Aug00 					)
//DeadCode CSB 1Aug00 				{
//DeadCode CSB 1Aug00 					if (	caller->ai.unfriendly
//DeadCode CSB 1Aug00 							&&	caller->ai.unfriendly->Status.size==AIRSTRUCSIZE
//DeadCode CSB 1Aug00 							&& ((AirStrucPtr)*caller->ai.unfriendly)->ai.attacker==caller
//DeadCode CSB 1Aug00 						)//reset old link
//DeadCode CSB 1Aug00 						((AirStrucPtr)*caller->ai.unfriendly)->ai.attacker=NULL;
//DeadCode CSB 1Aug00 
//DeadCode CSB 1Aug00 					trg->ai.attacker=caller;
//DeadCode CSB 1Aug00 				}
//DeadCode CSB 1Aug00 			}
//DeadCode CSB 1Aug00 			caller->ai.unfriendly=trg;
			caller->SetUnfriendly(trg);									//CSB 1Aug00

			caller->manoeuvretime=0;	//CSB 24/06/99	

			caller->information = IF_OUT_POS;

//DeadCode CSB 6Sep00 			if((caller->Distance3DSquared(&trg->World) > FP(COMBATRANGE) * FP(COMBATRANGE))	&& (manoeuvre == MANOEUVRE_SELECT))
			if((caller->Distance3DSquared(&trg->World) > FP(COMBATRANGE) * FP(COMBATRANGE))	&& (manoeuvre == MANOEUVRE_SELECT))
			{
				caller->movecode = AUTO_PRECOMBAT;
				caller->SetManoeuvreTime(0);
				caller->information = IF_OUT_POS;
			}
			else
			{
//DeadCode CSB 24/06/99					caller->manoeuvretime=0;
				caller->movecode = AUTO_COMBAT;
			}
//DEADCODE RDH 19/05/99 			if (caller->Range < INSIDEWEAPONSRANGE)
//DEADCODE RDH 19/05/99 				caller->ai.manoeuvre=MANOEUVRE_SELECT;			//surprised so no preplanning
//##rdh test purposes
			if (caller==Persons2::PlayerGhostAC)
			{
				caller= Manual_Pilot.ControlledAC2;
				caller->SetUnfriendly(trg);
//DeadCode CSB 1Aug00 				caller->ai.unfriendly=trg;
				caller->information=IF_OUT_POS;
//DeadCode CSB 24/06/99					caller->manoeuvretime=0;
				caller->movecode=AUTO_COMBAT;
				caller->ai.manoeuvre=MANOEUVRE_SELECT;

			}

			_DPlay.OwnerChangeDecision(caller,trg);				//AMM 27Nov98

			//##	if (surprised)
			//##modify morale based on range
		}
	}else
	{//assume that if we get here with no target then weldedwing was required
		//Just follow leader...
		if	(		(caller->leader)
				&&	(((AirStrucPtr)caller->leader)->ai.unfriendly)
				&& (((AirStrucPtr)caller->leader)->ai.unfriendly->Status.size == AIRSTRUCSIZE)
			)
			//20Apr99
			caller->SetUnfriendly(AirStrucPtr(caller->Leader()->ai.unfriendly));		//CSB 1Aug00
//DeadCode CSB 1Aug00 			caller->ai.unfriendly = ((AirStrucPtr)caller->leader)->ai.unfriendly;		//RJS 08Apr99
		else
			caller->SetUnfriendly(NULL);		//CSB 1Aug00
//DeadCode CSB 1Aug00 			caller->ai.unfriendly = NULL;

		caller->ai.ManStep = PHASERESET;
//DEADCODE CSB 05/01/00 		caller->information = IF_ALLGOOD;
		caller->information = IF_OUT_POS;							  //CSB 05/01/00
		caller->ai.desiredhdg = ANGLES_0Deg;
		caller->ai.desiredpitch = ANGLES_0Deg;
		caller->ai.manoeuvre = MANOEUVRE_WELDEDWINGMAN; 
		if(caller->Range > COMBATRANGE)
		{
			caller->movecode = AUTO_PRECOMBAT;
			caller->SetManoeuvreTime(0);
			caller->information = IF_OUT_POS;
		}
		else
		{
			caller->manoeuvretime = 0;
			caller->movecode = AUTO_COMBAT;
		}
	}

	caller->DoAllSAGChecks();													//CSB 1Aug00
}		

	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedNeutral
//Author		R. Hyde 
//Date			Fri 6 Mar 1998
//
//Description	Not needed for MiG Alley
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 bool	ArtInt::SpottedNeutral(AirStruc* caller,AirStruc* trg)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	return(false);
//DeadCode AMM 20Oct100 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeForceToRespond
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
//DeadCode AMM 20Oct100 bool ArtInt::MakeForceToRespond (AirStruc* caller, AirStruc* trg, tGroupLevel group, bool& splitmanappropriate)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 //Confusion is possible here because we are considering two splits:
//DeadCode AMM 20Oct100 //		split force to respond from rest of force
//DeadCode AMM 20Oct100 //		split force that is responding into 2 for tactical advantage
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 	int trgnum = GuessFormationSize(caller, trg);
//DeadCode AMM 20Oct100 	int callernum = CountFormationSize(caller);
//DeadCode AMM 20Oct100 	splitmanappropriate = false;
//DeadCode AMM 20Oct100 	int	respondnum;
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 	if  (	(		(caller->ai.morale < MORALE_MEDIUM) && (callernum < trgnum*2)
//DeadCode AMM 20Oct100 				||	(caller->ai.morale < MORALE_GOOD) && (callernum < trgnum)
//DeadCode AMM 20Oct100 			)
//DeadCode AMM 20Oct100 			&&	(callernum > 1)		//singleton get stuck in just to make it interesting //RDH 18/06/99
//DeadCode AMM 20Oct100 		)
//DeadCode AMM 20Oct100 		{
//DeadCode AMM 20Oct100 			return(false);
//DeadCode AMM 20Oct100 		}else
//DeadCode AMM 20Oct100 		{
//DeadCode AMM 20Oct100 			if (caller->ai.morale < MORALE_MEDIUM)
//DeadCode AMM 20Oct100 				respondnum = 2*trgnum;
//DeadCode AMM 20Oct100 			else
//DeadCode AMM 20Oct100 				respondnum = trgnum;
//DeadCode AMM 20Oct100 			//respondnum is the number of ac we want to respond with
//DeadCode AMM 20Oct100 			if (respondnum < callernum)
//DeadCode AMM 20Oct100 			{// 	consider split manoeuvre
//DeadCode AMM 20Oct100 				int minacnum = 2 * respondnum;
//DeadCode AMM 20Oct100 				
//DeadCode AMM 20Oct100 //DEADCODE RDH 23/02/99 				int minacnum;
//DeadCode AMM 20Oct100 //DEADCODE RDH 23/02/99 				 if  (group == GROUP_ELEMENT)
//DeadCode AMM 20Oct100 //DEADCODE RDH 23/02/99 					 minacnum = 2;
//DeadCode AMM 20Oct100 //DEADCODE RDH 23/02/99 				else  if (group == GROUP_FLIGHT)
//DeadCode AMM 20Oct100 //DEADCODE RDH 23/02/99 					 minacnum = 4;
//DeadCode AMM 20Oct100 //DEADCODE RDH 23/02/99 				else if (group == GROUP_SQUADRON)
//DeadCode AMM 20Oct100 //DEADCODE RDH 23/02/99 					 minacnum = 8;
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 				if (minacnum <= callernum )
//DeadCode AMM 20Oct100 				{//can split force into 2 for tactical advantage
//DeadCode AMM 20Oct100 					respondnum = minacnum;
//DeadCode AMM 20Oct100 					splitmanappropriate = true;
//DeadCode AMM 20Oct100 //DEADCODE DAW 13/05/99 					else
//DeadCode AMM 20Oct100 //DEADCODE DAW 13/05/99 						splitmanappropriate = false;		
//DeadCode AMM 20Oct100 				}
//DeadCode AMM 20Oct100 // 	consider split force
//DeadCode AMM 20Oct100 				int	count = 1;
//DeadCode AMM 20Oct100 				AirStruc*	foll = caller;
//DeadCode AMM 20Oct100 				while (foll->Follower() !=NULL)
//DeadCode AMM 20Oct100 				{
//DeadCode AMM 20Oct100 					count++;
//DeadCode AMM 20Oct100 					foll =(AirStruc*)foll->Follower();
//DeadCode AMM 20Oct100 				}
//DeadCode AMM 20Oct100 				int	respondingelements = respondnum/count;
//DeadCode AMM 20Oct100 				count = 0;
//DeadCode AMM 20Oct100 				AirStruc*	lead2 = caller;
//DeadCode AMM 20Oct100 				while (	(lead2->fly.nextflight != NULL) &&	(count < respondingelements))
//DeadCode AMM 20Oct100 				{
//DeadCode AMM 20Oct100 					lead2 = lead2->fly.nextflight;		
//DeadCode AMM 20Oct100 					count++;
//DeadCode AMM 20Oct100 				}
//DeadCode AMM 20Oct100 				if (	(lead2 != NULL)	&&	(count >= respondingelements) )
//DeadCode AMM 20Oct100 					//break the link with the remaining forces
//DeadCode AMM 20Oct100 					lead2->information=IF_OUT_POS;
//DeadCode AMM 20Oct100 			}
//DeadCode AMM 20Oct100 			return(true);
//DeadCode AMM 20Oct100 		}	
//DeadCode AMM 20Oct100 }


//DeadCode AMM 20Oct100 bool	ArtInt::CallerFacingTarget(AirStruc*  caller, AirStruc*  trg, ANGLES angle)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	ANGLES delta = caller->HdgIntercept + angle - caller->hdg;		  //RDH 12/06/99
//DeadCode AMM 20Oct100 	ANGLES anglerange = angle + angle;								  //RDH 12/06/99
//DeadCode AMM 20Oct100 	if (delta << anglerange)										  //RDH 12/06/99
//DeadCode AMM 20Oct100 	 	return(true);
//DeadCode AMM 20Oct100 	else
//DeadCode AMM 20Oct100 		return(false);
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 }
bool	ArtInt::TargetFacingCaller(AirStruc*  caller, AirStruc*  trg,ANGLES angle)
{
	ANGLES delta = trg->HdgIntercept + ANGLES_180Deg + angle - trg->hdg;		  //RDH 12/06/99
	ANGLES anglerange = angle + angle;								  //RDH 12/06/99
	if (delta << anglerange)										  //RDH 12/06/99
	 	return(true);
	else
		return(false);

}
bool	ArtInt::TargetOnCallerTail(AirStruc*  caller, AirStruc*  trg, ANGLES angle)
{
	ANGLES delta = caller->HdgIntercept + ANGLES_180Deg + angle - caller->hdg; //RDH 12/06/99
	ANGLES anglerange = angle + angle;								  //RDH 12/06/99
	if (delta << anglerange)										  //RDH 12/06/99
	 	return(true);
	else
		return(false);

}
//DeadCode AMM 20Oct100 bool	ArtInt::CallerOnTargetTail(AirStruc*  caller, AirStruc*  trg, ANGLES angle)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	ANGLES delta = caller->HdgIntercept + angle - caller->hdg;		  //RDH 12/06/99
//DeadCode AMM 20Oct100 	ANGLES anglerange = angle + angle;								  //RDH 12/06/99
//DeadCode AMM 20Oct100 	if (delta << anglerange)										  //RDH 12/06/99
//DeadCode AMM 20Oct100 	 	return(true);
//DeadCode AMM 20Oct100 	else
//DeadCode AMM 20Oct100 		return(false);
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 }
//DEADCODE RDH 08/03/99 bool	ArtInt::DecoysInGroup(AirStruc*  caller)
//DEADCODE RDH 08/03/99 {
//DEADCODE RDH 08/03/99 
//DEADCODE RDH 08/03/99 		AirStrucPtr	currfol=caller;
//DEADCODE RDH 08/03/99 
//DEADCODE RDH 08/03/99 		
//DEADCODE RDH 08/03/99 		if (caller->leader==NULL)
//DEADCODE RDH 08/03/99 		{
//DEADCODE RDH 08/03/99 			while 	(		((currfol=currfol->fly.nextflight)!=NULL)
//DEADCODE RDH 08/03/99 							&&	(currfol->information)
//DEADCODE RDH 08/03/99 					)
//DEADCODE RDH 08/03/99 			{
//DEADCODE RDH 08/03/99 				if	(	(currfol->ai.firsttactic == TACTIC_DECOYACTIVE)
//DEADCODE RDH 08/03/99 					||	(currfol->ai.firsttactic == TACTIC_DECOYPASSIVE)
//DEADCODE RDH 08/03/99 					)
//DEADCODE RDH 08/03/99 					{
//DEADCODE RDH 08/03/99 						SetDecoysInGroup(currfol);
//DEADCODE RDH 08/03/99 						return(true);
//DEADCODE RDH 08/03/99 					}
//DEADCODE RDH 08/03/99 			}
//DEADCODE RDH 08/03/99 		}
//DEADCODE RDH 08/03/99 		return(false);
//DEADCODE RDH 08/03/99 }
//------------------------------------------------------------------------------
AirStrucPtr	ArtInt::SetFlightWhoCanEngage(AirStrucPtr caller,AirStrucPtr trg)
{
	AirStrucPtr	tmpt=trg;
	if (tmpt==NULL)	return(tmpt);
	switch (caller->ai.flighttactics)
	{
		case TOPCOVER:
		case SWORDANDSHIELD:
		case WELDEDWING:
		{	
			tmpt=NULL;
			break;
		}
		case LOOSEDEUCE:
		{		 
			tmpt=nextfl(trg,true);								//JIM 19Sep97
			if (!tmpt)
				//can't find a next flight so go down the followers
				tmpt=nextfol(trg,true);
				if (!tmpt)
				{
 					if (trg->fly.leadflight)
					{	
						if (trg->information)
 							tmpt=trg->fly.leadflight;
						else
						{
							SLong	oldrange = trg->Range;
						   trg->InterceptandRange(&trg->fly.leadflight->World);
						   if (trg->Range < RECOGNISERANGE)
								tmpt = trg->fly.leadflight;			  //RDH 23/06/99
					   		trg->Range = oldrange; 
						}
					}
				}

			break;
		}

	}
	return (tmpt);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFollowerWhoCanEngage
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
AirStrucPtr	ArtInt::SetFollowerWhoCanEngage(AirStrucPtr caller,AirStrucPtr trg)
{
	AirStrucPtr	tmpt=trg;
	if (tmpt==NULL)	return(tmpt);
	switch (caller->ai.elementtactics)
	{
		case TOPCOVER:
		case SWORDANDSHIELD:
		case WELDEDWING:
		{	
			tmpt=NULL;
			break;
		}
		case LOOSEDEUCE:
		{
			tmpt=nextfol(trg,true);								//JIM 19Sep97
			if (!tmpt)
			{
				//can't find a follower so try next flight
				if (trg->leader)
					trg = trg->Leader();
				tmpt=nextfl(trg,true);								  //RDH 12/05/99
				if (!tmpt)
				{
 					if (trg->fly.leadflight)
					{	
						if (trg->information)
 							tmpt=trg->fly.leadflight;
						else
						{
							SLong	oldrange = trg->Range;
						   trg->InterceptandRange(&trg->fly.leadflight->World);
						   if (trg->Range < RECOGNISERANGE)
								tmpt = trg->fly.leadflight;
					   		trg->Range = oldrange; 
						}
					}
				}

			}

			break;
		}
		default:
			tmpt=NULL;
			break;


	}
	return (tmpt);
}


//------------------------------------------------------------------------------
//DeadCode AMM 20Oct100 AirStrucPtr	ArtInt::SetFlightEngage(AirStrucPtr caller,AirStrucPtr trg,MANOEUVRE  manoeuvre,ANGLES desiredhdg, ANGLES desiredpitch, bool surprised)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	caller->information=IF_OUT_POS;
//DeadCode AMM 20Oct100 	AirStrucPtr	tmpt=trg;
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 	if (caller->movecode<AUTO_COMBAT)
//DeadCode AMM 20Oct100 	{
//DeadCode AMM 20Oct100 		tmpt=SetFlightWhoCanEngage(caller,trg);
//DeadCode AMM 20Oct100 		//null means not found or not allowed
//DeadCode AMM 20Oct100 //DEADCODE RDH 12/05/99 		if (!tmpt)
//DeadCode AMM 20Oct100 //DEADCODE RDH 12/05/99 		{
//DeadCode AMM 20Oct100 //DEADCODE RDH 12/05/99 			if (caller->ai.flighttactics == LOOSEDEUCE)
//DeadCode AMM 20Oct100 //DEADCODE RDH 12/05/99 				 tmpt = trg;
//DeadCode AMM 20Oct100 //DEADCODE RDH 12/05/99 		}
//DeadCode AMM 20Oct100 //DEADCODE RDH 12/05/99 		if ((tmpt) && !(tmpt->information))
//DeadCode AMM 20Oct100 //DEADCODE RDH 12/05/99 			tmpt = trg;
//DeadCode AMM 20Oct100 		if (tmpt)	trg=tmpt;
//DeadCode AMM 20Oct100 		//assign a/c from tmpt to flight
//DeadCode AMM 20Oct100 		if (!caller->AircraftDamaged() && caller->classtype->aerobaticfactor!=AEROBATIC_LOW)								//JIM 29Aug96
//DeadCode AMM 20Oct100 			SetEngage(caller,tmpt, manoeuvre,desiredhdg, desiredpitch,  surprised);
//DeadCode AMM 20Oct100 		AirStrucPtr	currtrg=tmpt;
//DeadCode AMM 20Oct100 		AirStrucPtr	currfol=caller;
//DeadCode AMM 20Oct100 		while ((currfol=*currfol->Follower())!=NULL)
//DeadCode AMM 20Oct100 			currtrg=SetFollowerEngage(currfol,currtrg, manoeuvre,desiredhdg, desiredpitch,  surprised);
//DeadCode AMM 20Oct100 	}
//DeadCode AMM 20Oct100 	RETURN	(trg);
//DeadCode AMM 20Oct100 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFollowerEngage
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
AirStrucPtr	ArtInt::SetFollowerEngage(AirStrucPtr caller,AirStrucPtr trg, MANOEUVRE  manoeuvre,ANGLES desiredhdg, ANGLES desiredpitch, bool surprised)
{
	caller->information=IF_OUT_POS;
	AirStrucPtr	tmpt=trg;
	if (!caller->AircraftDamaged() && caller->classtype->aerobaticfactor!=AEROBATIC_LOW)								//JIM 29Aug96
	if (caller->movecode < AUTO_COMBAT)
	{
		if (		(manoeuvre == MANOEUVRE_LINEASTERN)
				||	(manoeuvre == MANOEUVRE_LINEABREAST)
		   )
		{//all followers go after the same as the lead in these manoeuvres
			tmpt = trg;
		}else
		{
			tmpt = SetFollowerWhoCanEngage(caller,trg);			
			//null means not found or not allowed
			if (!tmpt)
			{
				if (caller->ai.elementtactics == LOOSEDEUCE)
					 tmpt = trg;
			}
//DEADCODE RDH 12/05/99 			if ((tmpt) && !(tmpt->information))
//DEADCODE RDH 12/05/99 				tmpt = trg;
		}
		SetEngage(caller,tmpt, manoeuvre,desiredhdg, desiredpitch, surprised);
		if (tmpt)
			trg=tmpt;
	}
	return(trg);
}
bool ArtInt::CallerOnRight(AirStruc* ac,AirStruc* trg)
{
	ANGLES	relhdg;
	relhdg =  HdgIntFromTo(ac,trg) - ac->hdg;
	if 	(relhdg << ANGLES_180Deg)
		return (false);
	else
		return(true);
	
}
void	ArtInt::FindGroupAndLeader2(AirStruc*& caller, AirStruc*& caller2,tGroupLevel& group)
{
	group = GroupLevelNotInFormation(caller);						  //RDH 23/06/99
	caller2 = NULL;													  //RDH 02/06/99
	int count = 0;
	if  (group == GROUP_ELEMENT)
	{
		caller2 = caller;
		do
		{
			count++;
			caller2 = ((AirStruc *)caller2->Follower());
		}while (caller2);
		count = count/2;
		int  i = 0;
		caller2 = caller;
		while (i < count)
		{
			i++;
			caller2 = ((AirStruc *)caller2->Follower());
		}
		
	}
	else if (group == GROUP_FLIGHT)
		caller2 =  caller->fly.nextflight;
	else if (group == GROUP_SQUADRON)
	{
		//GROUP_SQUADRON means bigger than a flight
		//should never be more tha 3 flights, so split at end of first flight
		if (caller->fly.nextflight)
			caller2 =  caller->fly.nextflight->fly.nextflight;

//DEADCODE RDH 23/02/99 		int count = 1;
//DEADCODE RDH 23/02/99 		caller2 = caller->fly.nextflight;
//DEADCODE RDH 23/02/99 		while ((count < 6) && (caller2->fly.nextflight != NULL))
//DEADCODE RDH 23/02/99 		{
//DEADCODE RDH 23/02/99 			caller2 = caller2->fly.nextflight;
//DEADCODE RDH 23/02/99 			count++;
//DEADCODE RDH 23/02/99 		}
//DEADCODE RDH 23/02/99 		if (count < 6)
//DEADCODE RDH 23/02/99 			caller2 =  caller->fly.nextflight;

	}else
		caller2 = NULL;


}
void	ArtInt::SwitchCallerToLeft(AirStruc*& caller, AirStruc*& callee)
{
	if (callee)
	{
		//we want caller on the left for standard move
		//can invert later if we want them to cross
		if (CallerOnRight(caller,callee))
		{
			AirStruc* tmp = callee;
			callee = caller;
			caller = tmp;
		}
	}

}

//DeadCode AMM 20Oct100 void	ArtInt::SetRoundAboutAc(AirStruc*  ac)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	AirStrucPtr	currldr, lastldr;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	AirStrucPtr	squadldr = ac->fly.leadflight;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	int	countelement = 0;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	int thiselement = 0;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		if (squadldr != NULL)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		{
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 			currldr = squadldr;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 			while 	(		((currldr=currldr->fly.nextflight)!=NULL)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 							&&	(currldr->information)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 					)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 			{
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 				if	(currldr->fly.position() == FLIGHTLEADER)		  //JIM 20/01/99
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 					countelement++;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 				if  (		(currldr == ac)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 						||	(currldr == ac->fly.leadflight)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 					)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 					thiselement = countelement;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 			}
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		}
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	if (countelement <= 1)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	{//not sufficient aircraft to do roundabout
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		ac->ai.threatlevel = BANDITANYWHERE;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		ac->ai.manoeuvre=MANOEUVRE_SELECT;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	}else
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	{
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		ac->ai.manoeuvre = MANOEUVRE_ROUNDABOUT;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		if (countelement == thiselement)
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		{
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 			ac->ai.threatlevel = BANDITFIRING;	
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		}else
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		{
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 			ac->ai.threatlevel = BANDITINENGAGERANGEOFFRIENDLY;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		}
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 		ac->ai.desiredalt = ac->World.Y - FT_2000 + (countelement - thiselement) * FT_2000;
//DeadCode AMM 20Oct100 //DEADCODE RDH 03/03/99 	}
//DeadCode AMM 20Oct100 }
//DEADCODE RDH 08/03/99 void	ArtInt::SetDecoysInGroup(AirStruc*  ac)
//DEADCODE RDH 08/03/99 {
//DEADCODE RDH 08/03/99 	ac->information = FALSE;
//DEADCODE RDH 08/03/99 	AirStrucPtr	currfol=ac;
//DEADCODE RDH 08/03/99 	do
//DEADCODE RDH 08/03/99 	{
//DEADCODE RDH 08/03/99 			currfol->movecode = AUTO_FOLLOWWP;
//DEADCODE RDH 08/03/99 			currfol->ai.threatlevel = BANDITINWEAPONSRANGE;
//DEADCODE RDH 08/03/99 			if (currfol->ai.firsttactic == TACTIC_DECOYACTIVE)
//DEADCODE RDH 08/03/99 				currfol->NextWayPoint ();
//DEADCODE RDH 08/03/99 			currfol=currfol->fly.nextflight;
//DEADCODE RDH 08/03/99 	}
//DEADCODE RDH 08/03/99 	while 	(		(currfol!=NULL)
//DEADCODE RDH 08/03/99 				&&	(currfol->information)
//DEADCODE RDH 08/03/99 			);
//DEADCODE RDH 08/03/99 	
//DEADCODE RDH 08/03/99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		nextfl
//Author		Jim Taylor
//Date			Wed 26 Jun 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
AirStrucPtr	ArtInt::nextfl(AirStrucPtr trg,bool unassigned)
{
//DEADCODE RDH 12/05/99 	AirStrucPtr	t2=trg;
//DEADCODE RDH 12/05/99 	if (trg)
//DEADCODE RDH 12/05/99 		repeat
//DEADCODE RDH 12/05/99 		{
//DEADCODE RDH 12/05/99 			if (	(trg->fly.nextflight)	&&	(trg->fly.nextflight->information))
//DEADCODE RDH 12/05/99 				trg=trg->fly.nextflight;
//DEADCODE RDH 12/05/99 			else
//DEADCODE RDH 12/05/99 				if (	(trg->fly.leadflight)	&&	(trg->information))
//DEADCODE RDH 12/05/99 					trg=trg->fly.leadflight;
//DEADCODE RDH 12/05/99 				else
//DEADCODE RDH 12/05/99 					return(NULL);
//DEADCODE RDH 12/05/99 ////			if (!!trg->ai.attacker <=unassigned)
//DEADCODE RDH 12/05/99 			if (!trg->ai.attacker || unassigned)
//DEADCODE RDH 12/05/99 				return(trg);
//DEADCODE RDH 12/05/99 		}	while (t2!=trg);
//DEADCODE RDH 12/05/99 	return(NULL);

	SLong	oldrange = trg->Range;
 	AirStrucPtr	t2=NULL;
	
	if (trg->fly.nextflight)
	{
		if (trg->fly.nextflight->information)
			t2 = trg->fly.nextflight;
		else
		{
		   trg->InterceptandRange(&trg->fly.nextflight->World);
			   if (trg->Range < RECOGNISERANGE)
					t2 = trg->fly.nextflight;				
		}
	}


	trg->Range = oldrange; 
	return(t2);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		nextfol
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
bool	ArtInt::AircraftAreClose(AirStrucPtr trg, AirStrucPtr foll)
{

	
//DEADCODE RDH 23/06/99 	SLong	oldrange = trg->Range;
//DEADCODE RDH 23/06/99  	AirStrucPtr	t2=NULL;

//DEADCODE RDH 23/06/99    trg->InterceptandRange(&foll->World);
	SLong deltax = trg->World.X - foll->World.X;
	if (deltax < 0)
		deltax = -deltax;
	SLong deltaz = trg->World.Z - foll->World.Z;
	if (deltaz < 0)
		deltaz = -deltaz;

  if (		(deltax < RECOGNISERANGE)
		&&	(deltaz < RECOGNISERANGE)
	 )
	return(true);
  else
	return(false);


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		nextfol
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
AirStrucPtr	ArtInt::nextfol(AirStrucPtr trg,bool unassigned)
{
//DEADCODE RDH 12/05/99 	AirStrucPtr	t2=trg;
//DEADCODE RDH 12/05/99 	if (trg)
//DEADCODE RDH 12/05/99 		repeat
//DEADCODE RDH 12/05/99 		{
//DEADCODE RDH 12/05/99 			if (		(trg->Follower())	&&	(trg->Follower()->information))
//DEADCODE RDH 12/05/99 				trg=*trg->Follower();
//DEADCODE RDH 12/05/99 			else
//DEADCODE RDH 12/05/99 				if ((	trg->leader)	&&	(trg->information))
//DEADCODE RDH 12/05/99 					trg=*trg->leader;
//DEADCODE RDH 12/05/99 //				else
//DEADCODE RDH 12/05/99   //					return(NULL);
//DEADCODE RDH 12/05/99 ////			if (!!trg->ai.attacker <=unassigned)
//DEADCODE RDH 12/05/99 			if (!trg->ai.attacker || unassigned)
//DEADCODE RDH 12/05/99 				return(trg);
//DEADCODE RDH 12/05/99 		}	while (t2!=trg);
//DEADCODE RDH 12/05/99 	return(NULL);

	SLong	oldrange = trg->Range;
 	AirStrucPtr	t2=NULL;

	if (trg->Follower())
	{
		if	(trg->Follower()->information)	
			t2 = trg->Follower();
		else
		{
		   trg->InterceptandRange(&trg->Follower()->World);
		   if (trg->Range < RECOGNISERANGE)
				t2 = trg->Follower();				
		}
	}

 	trg->Range = oldrange; 
	return(t2);

}
ANGLES ArtInt::HdgIntFromTo(AirStruc* ac,AirStruc* trg)
{
	ANGLES	oldhdgint, oldpitchint;
	SLong	oldrange;
	ANGLES	hdgint;
	oldhdgint = ac->HdgIntercept;
	oldpitchint = ac->PitchIntercept;
	oldrange  = ac->Range;

	InterceptRangeFromTo(ac, trg);
	hdgint = ac->HdgIntercept;

	ac->PitchIntercept = oldpitchint;
	ac->HdgIntercept = oldhdgint;
	ac->Range = oldrange;
	return(hdgint);

}
//DeadCode AMM 20Oct100 bool ArtInt::TrgIsVulnerable(AirStruc* caller, AirStruc* trg)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	int trgnum = GuessFormationSize(caller, trg);
//DeadCode AMM 20Oct100 	int callernum = CountFormationSize(caller);
//DeadCode AMM 20Oct100 	if ((trgnum <= 4) && (callernum >=4))
//DeadCode AMM 20Oct100 		return (true);
//DeadCode AMM 20Oct100 	else
//DeadCode AMM 20Oct100 		return (false);
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 }
//DeadCode AMM 20Oct100 AirStruc* ArtInt::FreeUpAFlight(AirStruc* caller, AirStruc*  currtrg)
//DeadCode AMM 20Oct100 {//if there isn't a free flight then redirect lowest 
//DeadCode AMM 20Oct100 	//which is attacking a/c in same flight that leader is attacking
//DeadCode AMM 20Oct100 	//but don't redirect if currtrgldr is same as foller leader
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 	AirStruc* leader;
//DeadCode AMM 20Oct100 	leader = caller->FindGroupLeaderInFormation();
//DeadCode AMM 20Oct100 	currtrg = currtrg->FindGroupLeader();
//DeadCode AMM 20Oct100 	AirStruc* callee =  leader;
//DeadCode AMM 20Oct100 	int count = 0;
//DeadCode AMM 20Oct100 	while (callee->fly.nextflight != NULL)
//DeadCode AMM 20Oct100 	  {//find last element
//DeadCode AMM 20Oct100 		callee = callee->fly.nextflight;		
//DeadCode AMM 20Oct100 		count++;
//DeadCode AMM 20Oct100 	  }
//DeadCode AMM 20Oct100 	if ((count % 2) == 1)
//DeadCode AMM 20Oct100 		count--;			//find last flight
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100 	ItemBase* ldrtrg = 	(AirStrucPtr(*leader)->ai.unfriendly);
//DeadCode AMM 20Oct100 	if (		(!ldrtrg)
//DeadCode AMM 20Oct100 			||	(ldrtrg->Status.size!=AIRSTRUCSIZE)
//DeadCode AMM 20Oct100 //DEADCODE RDH 06/06/99 			||	(AirStrucPtr(*ldrtrg)->ai.unfriendly->Status.size!=AIRSTRUCSIZE)
//DeadCode AMM 20Oct100 	   )
//DeadCode AMM 20Oct100 	{
//DeadCode AMM 20Oct100 		callee = leader;
//DeadCode AMM 20Oct100 	}else
//DeadCode AMM 20Oct100 	{
//DeadCode AMM 20Oct100 		ldrtrg = AirStrucPtr(*ldrtrg)->FindGroupLeader();	
//DeadCode AMM 20Oct100 		AirStruc* folltrg; 
//DeadCode AMM 20Oct100 									 
//DeadCode AMM 20Oct100 		do
//DeadCode AMM 20Oct100 		{
//DeadCode AMM 20Oct100 			int i = 0;
//DeadCode AMM 20Oct100 			callee= leader;
//DeadCode AMM 20Oct100 			while (i < count)
//DeadCode AMM 20Oct100 			{
//DeadCode AMM 20Oct100 				callee = callee->fly.nextflight;
//DeadCode AMM 20Oct100 				i++;
//DeadCode AMM 20Oct100 			}
//DeadCode AMM 20Oct100 			count = count - 2;
//DeadCode AMM 20Oct100 			folltrg = (AirStruc*)((AirStruc*)callee->ai.unfriendly);
//DeadCode AMM 20Oct100 			if (folltrg->Status.size == AIRSTRUCSIZE)
//DeadCode AMM 20Oct100 				folltrg = folltrg->FindGroupLeader();				  //RDH 06/06/99
//DeadCode AMM 20Oct100 		}while (	(count >= 0)	&&	(folltrg != ldrtrg)&&	(currtrg != folltrg));
//DeadCode AMM 20Oct100 		if (leader == callee)
//DeadCode AMM 20Oct100 			callee = NULL;
//DeadCode AMM 20Oct100 	}	
//DeadCode AMM 20Oct100 	return(callee); 
//DeadCode AMM 20Oct100 }


//DeadCode AMM 20Oct100 AirStruc* ArtInt::FindFreeFlight(AirStruc* caller)
//DeadCode AMM 20Oct100 {
//DeadCode AMM 20Oct100 	AirStruc* leader = caller->FindGroupLeaderInFormation();
//DeadCode AMM 20Oct100 	AirStruc* callee =  leader;
//DeadCode AMM 20Oct100 	int count = 0;
//DeadCode AMM 20Oct100 	while (callee->fly.nextflight != NULL)
//DeadCode AMM 20Oct100 	  {//find last element
//DeadCode AMM 20Oct100 		callee = callee->fly.nextflight;		
//DeadCode AMM 20Oct100 		count++;
//DeadCode AMM 20Oct100 	  }
//DeadCode AMM 20Oct100 	if ((count % 2) == 1)
//DeadCode AMM 20Oct100 		count--;			//find last flight
//DeadCode AMM 20Oct100 	int flight = count;
//DeadCode AMM 20Oct100 	int i;
//DeadCode AMM 20Oct100 	do
//DeadCode AMM 20Oct100 	{
//DeadCode AMM 20Oct100 		i = 0;
//DeadCode AMM 20Oct100 		callee =  leader;
//DeadCode AMM 20Oct100 		while (i < count)
//DeadCode AMM 20Oct100 		{
//DeadCode AMM 20Oct100 			callee = callee->fly.nextflight;
//DeadCode AMM 20Oct100 			i++;
//DeadCode AMM 20Oct100 		}
//DeadCode AMM 20Oct100 		count = count - 2;
//DeadCode AMM 20Oct100 	}
//DeadCode AMM 20Oct100 	while (	(count >= 0)	&&	(callee->ai.unfriendly !=NULL));
//DeadCode AMM 20Oct100 
//DeadCode AMM 20Oct100   	if (callee->ai.unfriendly != NULL)
//DeadCode AMM 20Oct100 		callee = NULL;
//DeadCode AMM 20Oct100 	if (leader == callee)
//DeadCode AMM 20Oct100 		callee = NULL;
//DeadCode AMM 20Oct100 	return(callee);
//DeadCode AMM 20Oct100 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FindEscort
//Author		Craig Beeston
//Date			Fri 21 Jan 2000
//
//Description	Finds a SAG which is escorting
// 	
//Inputs		
//
//Returns	
//------------------------------------------------------------------------------
AirStruc* ArtInt::FindEscort(AirStruc* caller)
{
	AirStrucPtr leader = caller->GetLeadAc();
	AirStrucPtr escort = NULL;

	for(int i = 0; (i < ACARRAYSIZE) && (!escort); i++)
		if(ACArray[i])
		{
			AirStrucPtr as = ACArray[i]->GetLeadAc();

			if(		(as->classtype->aerobaticfactor == AEROBATIC_HIGH) && (as->fly.leadflight)
				&&	(as->fly.leadflight->GetLeadAc() == leader)
				&&	(as->fly.leadflight->movecode != AUTO_COMBAT) && (as->fly.leadflight->movecode != AUTO_PRECOMBAT)
				&&	(as->Distance3DSquared(&leader->World) < FP(HALFVISIBLERANGE) * FP(HALFVISIBLERANGE))	)
				escort = as;
		}

	return(escort);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakCall
//Author		R. Hyde 
//Date			Thu 4 Mar 1999
//
//Description	Worst call first, try to assess skill and morale and then choose
// 				returns the desired script
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ScriptTables ArtInt::BreakCall(AirStrucPtr caller, AirStrucPtr callee, AirStrucPtr agg)		  //CSB 08/02/00
{
	ScriptTables script = SCRIPT_LOOKOUT;
	
	if(Math_Lib.rnd(100) < 10)
		switch(Math_Lib.rnd(3))
		{
			case 0:		script = SCRIPT_AIRCRAFTEXCLAIM;	break;
			case 1:		script = SCRIPT_BANDITINCIRCUIT;	break;
			case 2:		script = SCRIPT_LOOKANOTHER;		break;
		}
	else if(caller == FindTailie(caller))// is weaver)
		script = SCRIPT_WEAVERCALLBANDIT;
	else if(caller->ai.morale > 205 + Math_Lib.rnd(50))
		script = SCRIPT_BREAKHELL;
	else if(caller->ai.morale < Math_Lib.rnd(50))
		script = SCRIPT_LOOKOUTLEADER;
	else
	{
		SWord rand = Math_Lib.rnd(30);
		if(rand >= 26)
			rand = (21 * caller->ai.combatskill) / 255 + rand - 25;

		bool breakleft = true;
		if(FP(agg->World.X - callee->World.X) * FP(callee->vel_z) - FP(agg->World.Z - callee->World.Z) * FP(callee->vel_x) > 0)
			breakleft = false;

		switch(rand)
		{
			case 0:		script = SCRIPT_LOOKOUT;	break;
			case 1:		script = SCRIPT_BEHIND;		break;
			case 2:		script = SCRIPT_BEHIND_BEHIND;	break;
			case 3:		script = SCRIPT_LOOKBEHIND;	break;
			case 4:		script = SCRIPT_LOOKBEHINDYOU;	break;
			case 5:		script = SCRIPT_BANDITSONTAIL;	break;
			case 6:		script = SCRIPT_BANDITSONSIX;	break;
			case 7:		script = SCRIPT_LOOKBLIGHTER;	break;
			case 8:		if(breakleft)	script = SCRIPT_BREAKLEFT;
						else			script = SCRIPT_BREAKRIGHT;
						break;
			case 9:		if(breakleft)	script = SCRIPT_BANDITBREAKLEFT;
						else			script = SCRIPT_BANDITBREAKRIGHT;
						break;
			case 10:	script = SCRIPT_CALLEE_BEHIND_BEHIND;	break;
			case 11:	script = SCRIPT_BEHIND_CALLEE_BEHIND;	break;
			case 12:	script = SCRIPT_BEHIND_CALLEE_ONTAIL;	break;
			case 13:	script = SCRIPT_CALLEE_LOOKBEHIND;	break;
			case 14:	script = SCRIPT_OHNO_CALLEE_LOOKBEHIND;	break;
			case 15:	script = SCRIPT_CALLEE_LOOKBEHINDYOU;	break;
			case 16:	script = SCRIPT_CALLEE_BANDITSONTAIL;	break;
			case 17:	script = SCRIPT_CALLEE_BANDITSONSIX;	break;
			case 18:	script = SCRIPT_CALLEE_LOOKBLIGHTER;	break;
			case 19:	if(breakleft)	script = SCRIPT_CALLEE_BEHIND_ONLEFT;
						else			script = SCRIPT_CALLEE_BEHIND_ONRIGHT;
						break;
			case 20:	if(breakleft)	script = SCRIPT_BEHIND_CALLEE_ONLEFT;
						else			script = SCRIPT_BEHIND_CALLEE_ONRIGHT;
						break;
			case 21:	if(breakleft)	script = SCRIPT_CALLEE_LOOKBEHIND_ONLEFT;
						else			script = SCRIPT_CALLEE_LOOKBEHIND_ONRIGHT;
						break;
			case 22:	if(breakleft)	script = SCRIPT_CALLEE_LOOKBEHINDYOU_ONLEFT;
						else			script = SCRIPT_CALLEE_LOOKBEHINDYOU_ONRIGHT;
						break;
			case 23:	if(breakleft)	script = SCRIPT_CALLEE_BANDITSONTAILBREAKLEFT;
						else			script = SCRIPT_CALLEE_BANDITSONTAILBREAKRIGHT;
						break;
			case 24:	if(breakleft)	script = SCRIPT_CALLEE_BANDITSONSIXBREAKLEFT;
						else			script = SCRIPT_CALLEE_BANDITSONSIXBREAKRIGHT;
						break;
			case 25:	if(breakleft)	script = SCRIPT_CALLEE_BANDITBREAKLEFT;
						else			script = SCRIPT_CALLEE_BANDITBREAKRIGHT;
						break;
		}
	}

	return script;
}

//DEADCODE CSB 08/02/00 ScriptTables leftset[] = {
//DEADCODE CSB 08/02/00 							OLDSCRIPT_BRKLEFT_BRKPANIC,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_BRKLEFT_BRKBAD,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_BRKLEFT_BRK,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_BRKBAD,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_RAND_ALERT,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_RAND_ALERT_L,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_BRKLEFT_BRKPANIC,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_BRKLEFT_BRKBAD,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_BRKLEFT_BRK,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_BRKLEFT
//DEADCODE CSB 08/02/00 						};	
//DEADCODE CSB 08/02/00 ScriptTables rightset[] = {
//DEADCODE CSB 08/02/00 							OLDSCRIPT_BRKRIGHT_BRKPANIC,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_BRKRIGHT_BRKBAD,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_BRKRIGHT_BRK,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_BRKBAD,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_RAND_ALERT,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_RAND_ALERT_L,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLE_BRKRIGHT_BRKPANIC,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLE_BRKRIGHT_BRKBAD,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_BRKRIGHT_BRK,
//DEADCODE CSB 08/02/00 							OLDSCRIPT_CALLEE_BRKRIGHT
//DEADCODE CSB 08/02/00 						};
//DEADCODE CSB 08/02/00 
//DEADCODE CSB 08/02/00 	ScriptTables	script;
//DEADCODE CSB 08/02/00 	int max = 3+(caller->ai.combatskill/(SKILL_MAX/7));	//equivalent too!		 * 10)/SKILL_MAX
//DEADCODE CSB 08/02/00 	int range = Math_Lib.rnd(3);
//DEADCODE CSB 08/02/00 	int index = max - range;
//DEADCODE CSB 08/02/00 	if (index > 9)
//DEADCODE CSB 08/02/00 		index = 9;
//DEADCODE CSB 08/02/00 	if (index < 0)
//DEADCODE CSB 08/02/00 		index = 0;
//DEADCODE CSB 08/02/00 	if (onright)
//DEADCODE CSB 08/02/00 		script = rightset[index];
//DEADCODE CSB 08/02/00 	else
//DEADCODE CSB 08/02/00 		script = leftset[index];
//DEADCODE CSB 08/02/00 
//DEADCODE CSB 08/02/00 	if  (caller->classtype->phrasename != OLDPHRASE_MIGS)
//DEADCODE CSB 08/02/00 	{//there is a MiG option we can use
//DEADCODE CSB 08/02/00 	if (index == 4) 
//DEADCODE CSB 08/02/00 		script = OLDSCRIPT_CALLEE_RAND_ALERT_MIGS;	
//DEADCODE CSB 08/02/00 	if (index == 5)
//DEADCODE CSB 08/02/00 		script = OLDSCRIPT_RAND_ALERT_L_MIGS;		
//DEADCODE CSB 08/02/00 	}
//DEADCODE CSB 08/02/00 	return script;
//DEADCODE CSB 08/02/00 
//DEADCODE CSB 08/02/00 }

//////////////////////////////////////////////////////////////////////
//
// Function:    Rendezvous
// Date:		04/04/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
TABLEAI(Rendezvous,AirStrucPtr)
{	{PHRASE_NULL}
};

INSTANCEAI(Rendezvous,AirStrucPtr)
{
	return false;
}

/*
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedUnknown
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	Do we want a closer look?
//			   	Only if threatlevel >=BANDITANYWHERE
//				and aggressionlevel >=AL_DEFENSIVE
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SpottedUnknown(AirStruc* caller,AirStruc* trg)
{
//rdh 19/1/99	if (caller->ai.unfriendly==NULL)
//rdh 19/1/99	{
//rdh 19/1/99//DEADCODE JIM 21/12/98 			caller->ai.unfriendly=trg;
//rdh 19/1/99
//rdh 19/1/99//##temp rdh			if  (	(caller->ai.threatlevel >=BANDITANYWHERE)
//rdh 19/1/99//				&&	caller->movecode < AUTO_TRACKINGBOGIE
//rdh 19/1/99//				&&	caller->ai.aggressionlevel >= AL_DEFENSIVE
//rdh 19/1/99//				)
//rdh 19/1/99//DEADCODE JIM 21/12/98 				caller->movecode = AUTO_TRACKINGBOGIE;
//rdh 19/1/99
//rdh 19/1/99}

	if (caller->IsUsingPilotedAcLog())
	{
		if (!trg->IsUsingPilotedAcLog())
		{
//TempCode RDH 27Mar98 			Persons_2.AddMESSAGE_STRUC(UserMsg::SIGHTED,TEXT_UNKNOWNSIGHTED,caller);
			caller->PlayerSequenceAudible(FIL_MUSIC_SPOTTED_UNKNOWN);
			Persons2::UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYPLAYERS);
		}
	}
	elseif (!trg->IsUsingPilotedAcLog())
	{
		Persons2::UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYOTHERS);
	}
	if (caller->ai.unfriendly==NULL)
	{
//DEADCODE JIM 21/12/98 			caller->ai.unfriendly=trg;

//##temp rdh			if  (	(caller->ai.threatlevel >=BANDITANYWHERE)
//				&&	caller->movecode < AUTO_TRACKINGBOGIE
//				&&	caller->ai.aggressionlevel >= AL_DEFENSIVE
//				)
//DEADCODE JIM 21/12/98 				caller->movecode = AUTO_TRACKINGBOGIE;

	}
	return(true);


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedContrails
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::SpottedContrails(AirStruc* caller,AirStruc* trg)
{
//like spotted unknown
//given higher priority?
//do we know who has set contrails, if we could track it easily if required
}	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedOldContrails
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ArtInt::SpottedOldContrails(AirStruc* caller,AirStruc* trg)
{
//like spotted unknown
//given lower priority?
//do we know who has set contrails, if we could track it easily if required
}	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoesFriendNeedHelp
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	Assess whether friendly needs helping out
//				caller and trg are same nationality
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::DoesFriendNeedHelp(AirStruc* caller,AirStruc* trg)
{
	SLong	RangeEyeTrg = caller->Range;
	
	if (	trg->ai.attacker
		&&	trg->ai.attacker->Status.size==AIRSTRUCSIZE
		&&	!((AirStruc*)*trg->ai.attacker)->ai.attacker
		)
	{//trg has attacker that is an aircraft that is not under attack
		caller->InterceptandRange(&trg->ai.attacker->World);

		if (	(	(!caller->ai.unfriendly)
				||	(	((AirStruc*)caller->ai.unfriendly)->nationality == caller->nationality)
				||	((RangeEyeTrg - caller->Range) > MILES01)
				)
				&& (caller->ai.morale > MORALE_MEDIUM)
			)
		{//caller doesn't have unf or unf is really on caller's side or this attacker closer
		 //and morale high 
			return(SpottedUnfriendly(caller,*trg->ai.attacker));
		}else
			return(false);
//TempCode RDH 27Mar98 		if (trg->ai.eventlog->stage!=EventLog::TAKEOFF) //player flight
//TempCode RDH 27Mar98 			//##message to differentiate between bomber,fb and fighter
//TempCode RDH 27Mar98 			Persons_2.AddMessageIfPlayerSq(caller,UserMsg::SIGHTED,TEXT_DOGFIGHTSIGHTED,trg);
		
	}else
	{
		return(false);
		if (trg->Range>RECOGNISERANGE-METRES500)
			if (caller->ai.eventlog->stage==EventLog::TAKEOFF)	//player flight
			if (trg->ai.eventlog->stage!=EventLog::TAKEOFF)	//non-player flight
			{
 				Persons_2.UpdateLog(trg->ai.eventlog,0,EventLog::SEENBYPLAYERS);
				caller->PlayerSequenceAudible(FIL_MUSIC_FRIENDLY_SEEN);
			}
	}

	caller->Range = RangeEyeTrg;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpottedNewUnfriendly
//Author		Jim Taylor
//Date			Tue 22 Oct 1996
//
//Description	
//				if caller is leader
//					if trg has no attacker
//						if range < DANGER THEN attack
//						if range < ENGAGE
//							if caller has no unfriendly or is a friendly THEN attack
//							if range to caller->unf > ENGAGERANGE THEN attack
//
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ArtInt::SpottedNewUnfriendly(AirStruc* caller,AirStruc* trg)
{
	if (caller->leader==NULL)
		if (trg->ai.attacker==NULL)
		{
			int	newrange=trg->Range;
			if (newrange<ENGAGERANGE)
				return(SpottedUnfriendly(caller,trg));
			if (newrange<COMBATRANGE)
			{
				if (	(caller->ai.unfriendly==NULL)
//##					||	(caller->ai.unfriendly->nationality == caller->nationality)
					)
					return(SpottedUnfriendly(caller,trg));
				caller->InterceptandRange(caller->ai.unfriendly);
				if (caller->Range>COMBATRANGE)
					return(SpottedUnfriendly(caller,trg));
			}
		}
	return(false);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptandRange
//Author		R. Hyde 
//Date			Tue 28 Nov 1995
//
//Description		
//
//Inputs		
//
//Returns	"Global" Range, HdgIntercept and PitchIntercept
//
//------------------------------------------------------------------------------
void ArtInt::InterceptRangeFromTo(AirStruc* from, AirStruc* to)

{


	SLong deltax = to->World.X - from->World.X;
	SLong deltay = to->World.Y - from->World.Y;
	SLong deltaz = to->World.Z - from->World.Z;
	Math_Lib.Intercept (deltax,deltay,deltaz,from->Range,from->HdgIntercept,from->PitchIntercept);
	
	
	

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AcHasBombs
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::AcHasBombs(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceHasBombers(trg)
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::ForceHasBombers(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BingoFuel
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::BingoFuel(AirStruc* trg)
{
	return(true);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Winchester
//Author		R. Hyde 
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool ArtInt::Winchester(AirStruc* trg)
{
	return(true);
}
*/
