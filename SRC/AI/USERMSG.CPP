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

////////////////////////////////////////////////////////////////////////
//
// Module:      usermsg.cpp
//
// Created:     15/02/99 by RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
//
//Macros defined:
////Use in header file ai.h to inter-ref between modules
//	EXTERNAI(name,type);		
//
////Use at top of defining module
//	DECISIONAI(name,type);			//If it has a decision table
//								
//	OPTIONAI(name,type);			//If it has no decision table
//
////Use in body of file
//	TABLEAI(name,type)				//To define the decision table			
//	{								//Usually preceeds INSTANCEAI()
//		{text,routine,speech}
//	};
//
//	INSTANCEAI(name,type)			//To define the AI actions
//	{
//		//actions
//		return false;
//	}

class DecisionAI *  DecisionAI::optiontable[DecisionAI::OPTIONTABLEMAX]={NULL};
int  DecisionAI::optiontablemax=0;

#include "worldinc.h"
#include "ai.h"
#include "node.h"
#include "rchatter.h"
#include "stub3d.h"
//TEMPCODE JIM 25/02/00 #include "nodebob.h"
//Dead#include	"messengn.h"

DECISIONAI(GroupInfoMsg,ItemPtr);
OPTIONAI(CallIn,ItemPtr);
OPTIONAI(CallPosition,ItemPtr);
OPTIONAI(CallFuel,ItemPtr);
OPTIONAI(CallStatus,ItemPtr);
OPTIONAI(TightLeftTurn,ItemPtr);
OPTIONAI(TightRightTurn,ItemPtr);

DECISIONAI(GroupInfoMsgFolRaf, ItemPtr);
DECISIONAI(GroupInfoMsgFolLuf, ItemPtr);
OPTIONAI(LowFuel, ItemPtr);
OPTIONAI(WhereAreYou, ItemPtr);

DECISIONAI(PreCombatMsg,ItemPtr);
DECISIONAI(PreCombatMsgLuf,ItemPtr);
OPTIONAI(TestGuns, ItemPtr);
OPTIONAI(RealTestGuns, ItemPtr);
OPTIONAI(PatrolRaf, ItemPtr);
OPTIONAI(PatrolLuf, ItemPtr);
OPTIONAI(EAVectorRaf, ItemPtr);
OPTIONAI(EAVectorLuf, ItemPtr);
OPTIONAI(AmAirborneRaf, ItemPtr);
OPTIONAI(AmAirborneLuf, ItemPtr);
OPTIONAI(AutoVectoringOn, ItemPtr);
OPTIONAI(AutoVectoringOff, ItemPtr);

DECISIONAI(CombatMsg,ItemPtr);
DECISIONAI(CombatMsgFolRaf,ItemPtr);
DECISIONAI(CombatMsgFolLuf,ItemPtr);
OPTIONAI(Bandit,ItemPtr);
OPTIONAI(CallBandit,ItemPtr);
OPTIONAI(SightingRequest,ItemPtr);
OPTIONAI(CallBreak,ItemPtr);
OPTIONAI(Covering,ItemPtr);
OPTIONAI(SixClr,ItemPtr);
OPTIONAI(NotClr,ItemPtr);
OPTIONAI(FlakSighted,ItemPtr);											//CSB 2Oct00
OPTIONAI(AttackMyTarget,ItemPtr);

DECISIONAI(PostCombatMsg,ItemPtr);
OPTIONAI(Regroup, ItemPtr);
OPTIONAI(SendEveryoneHome,ItemPtr);

DECISIONAI(TowerMsg,ItemPtr);
OPTIONAI(MayDay,ItemPtr);
OPTIONAI(CallHomeTower,ItemPtr);
OPTIONAI(CallNearestTower,ItemPtr);
OPTIONAI(WindUpdateLow,ItemPtr);
OPTIONAI(WindUpdateHigh,ItemPtr);
OPTIONAI(HomeLandClear,ItemPtr);
OPTIONAI(NearLandClear,ItemPtr);

DECISIONAI(Strike, ItemPtr);
OPTIONAI(BeginRun, ItemPtr);
OPTIONAI(Straffe, ItemPtr);
OPTIONAI(LeaveArea, ItemPtr);

DECISIONAI(QuitContinue, ItemPtr);
OPTIONAI(Continue, ItemPtr);
OPTIONAI(Quit, ItemPtr);
OPTIONAI(SetupQuitContinue, ItemPtr);

DECISIONAI(SecretMessages,ItemPtr);
OPTIONAI(SecretStartTrucks,ItemPtr);

////////////////////////////////////////////////////////////////////////
//
// Function:    GroupInfoMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(GroupInfoMsg,ItemPtr)
{
	{PHRASE_CALLIN,			&CallIn, 			SCRIPT_CALLIN},	
	{PHRASE_CALLPOSN,		&CallPosition,	 	SCRIPT_CALLPOSN},
	{PHRASE_CALLFUEL,		&CallFuel,			SCRIPT_CALLFUEL},
	{PHRASE_CALLSTATUS,		&CallStatus,		SCRIPT_CALLSTATUS},
	{PHRASE_TIGHTLEFTTURN,	&TightLeftTurn,		SCRIPT_TIGHTLEFTTURN},
	{PHRASE_TIGHTRIGHTTURN,	&TightRightTurn,	SCRIPT_TIGHTRIGHTTURN},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(GroupInfoMsg,ItemPtr)	{return false;}

INSTANCEAI(CallIn, ItemPtr)
{		 
	bool buddy = false;	

	for(AirStrucPtr eltlead = caller; eltlead; eltlead = eltlead->fly.nextflight)
		for(AirStrucPtr eltwing = eltlead; eltwing; eltwing = eltwing->Follower())
			if((eltwing != caller) && (!eltwing->Status.deadtime))	// not comms players
			{
				buddy = true;										  //RDH 10/05/99
				_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER, MSG_STATUSRESPONSE_RPT, eltwing, NULL, caller));
			}

	if(!buddy)														  //RDH 10/05/99
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_HIPRIORITY , NULL, NULL, caller)); //RDH 10/05/99//RJS 27Mar00

	return true;

//DEADCODE CSB 23/02/00 	AirStrucPtr leader=callee->GroupLeader();
//DEADCODE CSB 23/02/00 	prioritymessage->caller=leader;
//DEADCODE CSB 23/02/00 	AirStrucPtr	sayto=leader;
//DEADCODE CSB 23/02/00 	if (leader!=callee)
//DEADCODE CSB 23/02/00 		sayto=callee;
//DEADCODE CSB 23/02/00 
//DEADCODE CSB 23/02/00 	bool	buddy = false;											  //RDH 10/05/99
//DEADCODE CSB 23/02/00 	for (AirStrucPtr eltlead=leader;eltlead;eltlead=eltlead->fly.nextflight)
//DEADCODE CSB 23/02/00 		for (AirStrucPtr eltwing=eltlead;eltwing;eltwing=eltwing->Follower())
//DEADCODE CSB 23/02/00 			if ((eltwing!=leader) &&	(!eltwing->Status.deadtime))	// not comms players
//DEADCODE CSB 23/02/00 			{
//DEADCODE CSB 23/02/00 				buddy = true;										  //RDH 10/05/99
//DEADCODE CSB 23/02/00  				if (eltwing!=callee)
//DEADCODE CSB 23/02/00 					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER, MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, sayto));
//DEADCODE CSB 23/02/00 				else
//DEADCODE CSB 23/02/00 					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLER, MSG_STATUSRESPONSE_DELAY_LP_RPT, eltwing, NULL, leader));
//DEADCODE CSB 23/02/00 			}
//DEADCODE CSB 23/02/00 
//DEADCODE CSB 23/02/00 	if (!buddy)														  //RDH 10/05/99
//DEADCODE CSB 23/02/00 		_Radio.TriggerMsg(MESSAGE_STRUC(OLDPHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99
//DEADCODE CSB 23/02/00 
//DEADCODE CSB 23/02/00 	return true;
}


INSTANCEAI(CallPosition,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();
	prioritymessage->caller=leader;
	AirStrucPtr	sayto=leader;
	SLong range;

	if (leader!=callee)
		sayto=callee;
	bool	buddy = false;											  //RDH 10/05/99

	for (AirStrucPtr eltlead=leader;eltlead;eltlead=eltlead->fly.nextflight)
		for (AirStrucPtr eltwing=eltlead;eltwing;eltwing=eltwing->Follower())
			if (eltwing!=leader && !eltwing->uniqueID.commsmove)
			{
				buddy = true;										  //RDH 10/05/99
				range = Art_Int.RangeFromTo(leader,eltwing);
				if (eltwing!=callee)
				{
					if (range > MILES01)
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLPOSNREP , MSG_STATUSRESPONSE_RPT, eltwing, eltwing, sayto));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLPOSNREPCLOSE , MSG_STATUSRESPONSE_RPT, eltwing, eltwing, sayto));
				}
				else
				{
					if (range > MILES01)
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLPOSNREP , MSG_STATUSRESPONSE_RPT, eltwing, eltwing, leader));
					else
						_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLPOSNREPCLOSE , MSG_STATUSRESPONSE_RPT, eltwing, eltwing, leader));
				}
			}
	if (!buddy)														  //RDH 10/05/99
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99//RJS 27Mar00
	return true;
}


INSTANCEAI(CallFuel,ItemPtr)
{
	AirStrucPtr leader=callee->GroupLeader();
	prioritymessage->caller=leader;
	AirStrucPtr	sayto=leader;
	if (leader!=callee)
		sayto=callee;

	bool	buddy = false;											  //RDH 10/05/99
	for (AirStrucPtr eltlead=leader;eltlead;eltlead=eltlead->fly.nextflight)
		for (AirStrucPtr eltwing=eltlead;eltwing;eltwing=eltwing->Follower())
			if (eltwing!=leader && !eltwing->uniqueID.commsmove)
			{
				buddy = true;										  //RDH 10/05/99

				if (eltwing!=callee)
					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLFUELREP, MSG_STATUSRESPONSE_RPT, eltwing, NULL, sayto));
				else
					_Radio.TriggerMsg(MESSAGE_STRUC (SCRIPT_CALLFUELREP, MSG_STATUSRESPONSE_RPT, eltwing, NULL, leader));
			}
	if (!buddy)														  //RDH 10/05/99
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99//RJS 27Mar00
	return true;
}


INSTANCEAI(CallStatus,ItemPtr)
{
   	ScriptTables script;
	AirStrucPtr leader=callee->GroupLeader();
	prioritymessage->caller=leader;
	AirStrucPtr	sayto=leader;
	if (leader!=callee)
		sayto=callee;
	bool	buddy = false;											  //RDH 10/05/99
	for (AirStrucPtr eltlead=leader;eltlead;eltlead=eltlead->fly.nextflight)
		for (AirStrucPtr eltwing=eltlead;eltwing;eltwing=eltwing->Follower())
			if (eltwing!=leader && !eltwing->uniqueID.commsmove)
			{
				buddy = true;										  //RDH 10/05/99

				if(eltwing->ai.manoeuvre == MANOEUVRE_WELDEDWINGMAN) 
					script = SCRIPT_STATUSWING; 
				else
				{
					script = SCRIPT_STATUSFREE;
					if((eltwing->ai.unfriendly) && (eltwing->ai.unfriendly->Status.size==AirStrucSize))
					{
						for(;;)
						{
							AirStrucPtr trg = AirStrucPtr(eltwing->ai.unfriendly);
							eltwing->Range = eltwing->Distance3D(&trg->World);

							FP fChasing  = (trg->World.X - eltwing->World.X) * eltwing->vel_x
										 + (trg->World.Y - eltwing->World.Y) * eltwing->vel_y
										 + (trg->World.Z - eltwing->World.Z) * eltwing->vel_z;
							fChasing     /= FP(eltwing->vel_ * eltwing->Range);

							FP fChased   = (eltwing->World.X - trg->World.X) * trg->vel_x
										 + (eltwing->World.Y - trg->World.Y) * trg->vel_y
										 + (eltwing->World.Z - trg->World.Z) * trg->vel_z;
							fChased      /= FP(trg->vel_ * eltwing->Range);

							if((fChasing > 0.5) && (fChased < 0.5))	//60 deg cone
							{
								if((AirStrucPtr(eltwing->ai.unfriendly))->classtype->aerobaticfactor == AEROBATIC_HIGH)
									script = SCRIPT_STATUSCHASEBANDIT;
								else 
									script = SCRIPT_STATUSCHASEINDIAN;

								break;
							}
							if((fChased > 0.5) && (fChasing < 0.5))	//60 deg cone
							{
								script = SCRIPT_STATUSATTACKED;
								break;
							}
							script = SCRIPT_STATUSENGAGED;
							break;
						}
					}
				}

				if (eltwing!=callee)
					_Radio.TriggerMsg(MESSAGE_STRUC (script, MSG_STATUSRESPONSE_RPT, eltwing, NULL, sayto));
				else
					_Radio.TriggerMsg(MESSAGE_STRUC (script, MSG_STATUSRESPONSE_RPT, eltwing, NULL, leader));
			}
	if (!buddy)														  //RDH 10/05/99
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99//RJS 27Mar00
	return true;
}


INSTANCEAI(TightLeftTurn, ItemPtr)
{
	AirStrucPtr leader = callee->FindFormpos0();
	if(((leader->formation & FORMTYPE_WING) == FTW_SCWARM) || ((leader->formation & FORMTYPE_WING) == FTW_BSCRWARM))
	{
		for(AirStrucPtr nf = leader; nf; nf = nf->fly.nextflight)
			for(AirStrucPtr f = nf; f; f = f->Follower())
//DeadCode CSB 31Oct00 				if(f->position())
				{
					if((f->formation & FORMTYPE_WING) == FTW_SCWARM)
						f->formation = (f->formation % FORMTYPE_WING) | FTW_BSCRWARM;
					else
						f->formation = (f->formation % FORMTYPE_WING) | FTW_SCWARM;
					f->information = IF_OUT_POS;
				}
//DeadCode CSB 31Oct00 				else
//DeadCode CSB 31Oct00 					f->formation = (f->formation & FORMTYPE_WING) | FTI_SCWARM_SWAPPING_FLAG;
		return(true);
	}
	return(false);
}


INSTANCEAI(TightRightTurn, ItemPtr)
{
	AirStrucPtr leader = callee->FindFormpos0();
	if(((leader->formation & FORMTYPE_WING) == FTW_SCWARM) || ((leader->formation & FORMTYPE_WING) == FTW_BSCRWARM))
	{
		for(AirStrucPtr nf = leader; nf; nf = nf->fly.nextflight)
			for(AirStrucPtr f = nf; f; f = f->Follower())
//DeadCode CSB 31Oct00 				if(f->position())
				{
					if((f->formation & FORMTYPE_WING) == FTW_SCWARM)
						f->formation = (f->formation % FORMTYPE_WING) | FTW_BSCRWARM;
					else
						f->formation = (f->formation % FORMTYPE_WING) | FTW_SCWARM;
					f->information = IF_OUT_POS;
				}
//DeadCode CSB 31Oct00 				else
//DeadCode CSB 31Oct00 					f->formation = (f->formation & FORMTYPE_WING) | FTI_SCWARM_SWAPPING_FLAG;
		return(true);
	}
	return(false);
}


////////////////////////////////////////////////////////////////////////
//
// Function:    GroupInfoMsgFol
// Date:        11/02/00
// Author:      Craig Beeston
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(GroupInfoMsgFolRaf, ItemPtr)
{
	{PHRASE_LOWFUEL,			&LowFuel,	 		SCRIPT_RAF_LOWFUEL},	
	{PHRASE_WHEREAREYOU,		&WhereAreYou,	 	SCRIPT_WHEREAREYOU},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(GroupInfoMsgFolRaf, ItemPtr)	{return false;}


////////////////////////////////////////////////////////////////////////
//
// Function:    GroupInfoMsgFol
// Date:        11/02/00
// Author:      Craig Beeston
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(GroupInfoMsgFolLuf, ItemPtr)
{
	{PHRASE_LOWFUEL,			&LowFuel,	 		SCRIPT_LW_LOWFUEL},	
	{PHRASE_WHEREAREYOU,		&WhereAreYou,	 	SCRIPT_WHEREAREYOU},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(GroupInfoMsgFolLuf, ItemPtr)	{return false;}


INSTANCEAI(LowFuel, ItemPtr)
{		 
	AirStrucPtr lead = callee->FindFormpos0();
	SLong fuel = 0;
	SLong maxfuel = 0;
	for(SWord i = 0; i < 4; i++)
	{
		fuel	+= lead->fly.fuel_content[i] * 0.001;
		maxfuel	+= lead->classtype->fueltankcap[i];
	}
	if(fuel * 4 < maxfuel)
	{
		lead->AiLeaderBingoInstructions();
		return(true);
	}
	else
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CHECKFUEL, MSG_STATUSRESPONSE_RPT, lead, lead, caller));
		return(false);
	}
}


INSTANCEAI(WhereAreYou, ItemPtr)
{		 
	AirStrucPtr lead = caller->Leader();
	if(!lead)
		lead = caller->fly.leadflight;
	if(lead)
	{
		if(lead->Distance3DSquared(&callee->World) < FP(METRES500) * FP(METRES500))
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLPOSNREPCLOSE, MSG_STATUSRESPONSE_RPT, lead, lead, caller));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLPOSNREP, MSG_STATUSRESPONSE_RPT, lead, lead, caller));
		return(true);
	}
	return(false);
}


////////////////////////////////////////////////////////////////////////
//
// Function:    PreCombatMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(PreCombatMsg, ItemPtr)
{
	{PHRASE_TESTGUNS,		&TestGuns, 			SCRIPT_TESTGUNS},	
	{PHRASE_S_PATROL,		&PatrolRaf,			SCRIPT_PATROLRAF},	
	{PHRASE_S_EAVECTOR,		&EAVectorRaf, 		SCRIPT_INTECEPTRAF}, 
	{PHRASE_S_AIRBORNE,		&AmAirborneRaf,		SCRIPT_AIRBORNE},
	{PHRASE_S_GIVEFREEDOM,	&AutoVectoringOn,	SCRIPT_PICKOWNTARGETS},
	{PHRASE_S_TAKESTOPND,	&AutoVectoringOff,	SCRIPT_WAITFORORDER},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(PreCombatMsg, ItemPtr)	{return false;}


TABLEAI(PreCombatMsgLuf, ItemPtr)
{
	{PHRASE_TESTGUNS,		&TestGuns, 			SCRIPT_TESTGUNS},	
	{PHRASE_S_PATROL,		&PatrolLuf,			SCRIPT_ESCORTLWAIR},
	{PHRASE_S_EAVECTOR,		&EAVectorLuf, 		SCRIPT_INTECEPTRAF}, 
	{PHRASE_S_AIRBORNE,		&AmAirborneLuf,		SCRIPT_LWAIRBORNE},
	{PHRASE_S_GIVEFREEDOM,	&AutoVectoringOn,	SCRIPT_PICKOWNTARGETS},
	{PHRASE_S_TAKESTOPND,	&AutoVectoringOff,	SCRIPT_WAITFORORDER},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(PreCombatMsgLuf, ItemPtr)	{return false;}


INSTANCEAI(TestGuns,ItemPtr)
{
	if (caller==Persons2::PlayerGhostAC)
		gunstimer = 500;
	return false;
}


INSTANCEAI(RealTestGuns,ItemPtr)
{
	bool retval = false;

	//All in group test guns
	//never a problem so no more messages needed
	AirStrucPtr grplead = callee->FindGroupLeader();

	for (AirStrucPtr lead = grplead;lead;lead=lead->fly.nextflight)
		for (AirStrucPtr foll=lead;foll;foll=foll->Follower())
			if(foll != Persons2::PlayerGhostAC && !foll->uniqueID.commsmove)
				foll->PublicFireABullet(0,FALSE);			//RJS 27May99
	return retval;
}


INSTANCEAI(PatrolRaf, ItemPtr)
{
	WayPointPtr wp = caller->waypoint->FindWP(WPNAME_PatrolS);
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PATROLRAF_REPLY, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, wp, caller)); 
	return(true);
}


INSTANCEAI(PatrolLuf, ItemPtr)
{
	AirStrucPtr escortee = caller->FindFormpos0()->fly.leadflight;
	if(escortee)
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLPOSNREP, MSG_STATUSRESPONSE_RPT, escortee, escortee, caller)); 
	else
	{
		WayPointPtr wp = caller->waypoint->FindWP(WPNAME_PatrolS);
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_PATROLRAF_REPLY, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, wp, caller));
	}
	return(true);
}


INSTANCEAI(EAVectorRaf, ItemPtr)
{
	if((caller->ai.unfriendly) && (caller->ai.unfriendly->Status.size == AIRSTRUCSIZE))
	{
		AirStrucPtr bandit = AirStrucPtr(caller->ai.unfriendly);
		if(caller->Distance3DSquared(&bandit->World) < FP(MILES02) * FP(MILES02))
			prioritymessage->SetScript(SCRIPT_INTERCEPTRAFCLOSE);		//RJS 15Sep00
		else
			prioritymessage->SetScript(SCRIPT_INTERCEPTRAFCLOSE);		//RJS 15Sep00
		switch(Math_Lib.rnd(3))
		{
			case 0:		
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_VECTORPLUSBANDITS, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, bandit, caller));
				break;
			case 1:		
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_VECTORPLUSBANDITSANDBUSTER, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, bandit, caller));
				break;
			case 2:		
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_VECTOR, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, bandit, caller));
				break;
		}
	}
	else
	{
		AirStrucPtr bandit = NULL;
		prioritymessage->SetScript(SCRIPT_OTHERTRADE);					//RJS 15Sep00

		FP range2 = FP(2 * VISIBLERANGE) * FP(2 * VISIBLERANGE);

		for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
		{
			AirStrucPtr thisac = ArtInt::ACArray[i];
			if(		(thisac) && (thisac->nationality != caller->nationality)// && (thisac->ai.radiosilent)
				&&	(caller->Distance3DSquared(&thisac->World) < range2)	)
			{
				bandit = thisac;
				range2 = caller->Distance3DSquared(&thisac->World);
			}
		}

		if(bandit)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TRADEPLUSVECTOR, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, bandit, caller));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTRADE, MSG_BOGEYCALLDENTIST, VOICE_DENTIST, NULL, caller));
	}

	return(true);
}


INSTANCEAI(EAVectorLuf, ItemPtr)
{
	AirStrucPtr bandit = NULL;
	FP range2 = FP(VISIBLERANGE) * FP(VISIBLERANGE);

	AirStrucPtr buddy = caller->FindBuddy();
	if(!buddy)
		if((caller->formpos) && (caller->fly.leadflight))
			buddy = caller->fly.leadflight;
		else if(caller->fly.nextflight)
			buddy = caller->fly.nextflight;

	if(buddy)
		for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
		{
			AirStrucPtr thisac = ArtInt::ACArray[i];
			if((thisac) && (thisac->nationality != caller->nationality) && (caller->Distance3DSquared(&thisac->World) < range2))
			{
				bandit = thisac;
				range2 = caller->Distance3DSquared(&thisac->World);
			}
		}

	if(bandit)
	{
		prioritymessage->SetScript(SCRIPT_INTERCEPTLWCLOSE);			//RJS 15Sep00
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BANDIT_RELPOS, MSG_BANDITCALL_DELAY_LP_RPT, buddy, bandit, caller)); 
	}
	else
	{
		prioritymessage->SetScript(SCRIPT_INTERCEPTLWGENERAL);			//RJS 15Sep00
		AirStrucPtr bomber = caller->FindFormpos0();
		while((bomber->fly.leadflight) && (bomber->classtype->aerobaticfactor != AEROBATIC_LOW))
			bomber = bomber->fly.leadflight;

		if((bomber) && (bomber->classtype->aerobaticfactor == AEROBATIC_LOW))
		{
			range2 = FP(VISIBLERANGE) * FP(VISIBLERANGE);
			for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
			{
				AirStrucPtr thisac = ArtInt::ACArray[i];
				if((thisac)	&& (thisac->nationality != caller->nationality) && (bomber->Distance3DSquared(&thisac->World) < range2)	)
				{
					bandit = thisac;
					range2 = bomber->Distance3DSquared(&thisac->World);
				}
			}

			if(bandit)
			{
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BOMBERSPOTSBANDITS, MSG_BANDITCALL_DELAY_LP_RPT, VOICE_GROUND, bandit, caller)); 
				return(true);
			}
			else
				_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NORAFACTIVITY, MSG_BANDITCALL_DELAY_LP_RPT, bomber, bandit, caller)); 
		}
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller));//RJS 27Mar00
	}
	return(false);
}


INSTANCEAI(AmAirborneRaf, ItemPtr)
{
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_VECTORPLUSBANDITSANDBUSTER, MSG_DENTISTREPORT_REPEAT, VOICE_DENTIST, caller, caller)); 
	return(true);
}


INSTANCEAI(AmAirborneLuf, ItemPtr)
{
	if(Save_Data.flightdifficulty [FD_WINDEFFECTS])
	 	if(Save_Data.flightdifficulty [FD_WINDGUSTS])
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_ALTWIND_BEARINGNO_SPEED_GUSTS, MSG_WIND_HIGH_REPORT, VOICE_TOWER, NULL, caller));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_ALTWIND_BEARINGNO_SPEED, MSG_WIND_HIGH_REPORT, VOICE_TOWER, NULL, caller));
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOWIND, MSG_WIND_HIGH_REPORT, VOICE_TOWER, NULL, caller));

	return(true);
}


INSTANCEAI(AutoVectoringOn,ItemPtr)
{
	Save_Data.gamedifficulty |= GD_AUTOVECTORING;
	SendMsgAndCall(MESSAGE_STRUC(PHRASE_TALLYHO, MSG_CHOSENMANOEUVRE, caller, trg, caller), Bandit);	
	return(true);
}

 
INSTANCEAI(AutoVectoringOff,ItemPtr)
{
	Save_Data.gamedifficulty %= GD_AUTOVECTORING;
	return(true);
}


////////////////////////////////////////////////////////////////////////
//
// Function:    CombatMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(CombatMsg, ItemPtr)
{
	{PHRASE_S_BANDITS,			&Bandit,			PHRASE_TALLYHO},//RJS 13Sep00
	{PHRASE_S_SIGHTREQUEST,		&SightingRequest,	SCRIPT_WHERE},
	{PHRASE_VBREAK,				&CallBreak,			SCRIPT_BREAK},	
	{PHRASE_S_COVERING,			&Covering,			SCRIPT_COVERING},
	{PHRASE_HELPSHORT,			&AttackMyTarget,	PHRASE_HELPSHORT},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(CombatMsg, ItemPtr)	{return	false;}


TABLEAI(CombatMsgFolRaf, ItemPtr)
{
	{PHRASE_S_BANDITS,			&CallBandit,		PHRASE_TALLYHO},//RJS 13Sep00
	{PHRASE_S_SIGHTREQUEST,		&SightingRequest,	SCRIPT_WHERE},
	{PHRASE_VBREAK,				&CallBreak,			SCRIPT_BREAK},	
	{PHRASE_SIXCLR,				&SixClr,			SCRIPT_YOUCLEAR},
	{PHRASE_NOTCLEAR0,			&NotClr,			SCRIPT_NOTCLEAR},
	{PHRASE_ACKACKFIRE,			&FlakSighted,		PHRASE_ACKACKFIRE},
	{PHRASE_HELPSHORT,			&AttackMyTarget,	PHRASE_HELPSHORT},
	{PHRASE_NULL}
};
INSTANCEAI(CombatMsgFolRaf, ItemPtr)	{return	false;}


TABLEAI(CombatMsgFolLuf, ItemPtr)
{
	{PHRASE_S_BANDITS,			&CallBandit,		PHRASE_TALLYHO},//RJS 13Sep00
	{PHRASE_S_SIGHTREQUEST,		&SightingRequest,	SCRIPT_WHERE},
	{PHRASE_VBREAK,				&CallBreak,			SCRIPT_BREAK},	
	{PHRASE_SIXCLR,				&SixClr,			SCRIPT_YOUCLEAR},
	{PHRASE_NOTCLEAR0,			&NotClr,			SCRIPT_NOTCLEAR},
	{PHRASE_HELPSHORT,			&AttackMyTarget,	PHRASE_HELPSHORT},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(CombatMsgFolLuf, ItemPtr)	{return	false;}


INSTANCEAI(Bandit, ItemPtr)
{
	if(_DPlay.Implemented)
		return(false);
	
	SWord spotheadg = -View_Point->hdg;
	SWord spotpitch = -View_Point->pitch;
	const SWord vheadg = ANGLES_15Deg;
	const SWord vpitch = ANGLES_15Deg;
	AirStrucPtr spottrg = NULL;
	FP range2 = 2.0 * FP(VISIBLERANGE) * FP(VISIBLERANGE);

	for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
		if((ArtInt::ACArray[i]) && (ArtInt::ACArray[i]->nationality != caller->nationality))
			for(AirStrucPtr lead = ArtInt::ACArray[i]->GetLeadAc(); lead; lead = lead->fly.nextflight)
				for(AirStrucPtr ac = lead; ac; ac = ac->Follower())
					if(caller->Distance3DSquared(&ac->World) < range2)
					{
						caller->InterceptandRange(ac);
						SWord dheadg = SWord(caller->HdgIntercept)   - SWord(spotheadg);
						SWord dpitch = SWord(caller->PitchIntercept) - SWord(spotpitch);
						if((dheadg < vheadg) && (dheadg > -vheadg) && (dpitch < vpitch) && (dpitch > -vpitch))
						{
							spottrg = ac;
							range2 = caller->Distance3DSquared(&ac->World);
						}
					}

	if(spottrg)
	{
		if(prioritymessage)
		{
			prioritymessage->target = spottrg;						//RJS 13Sep00
			prioritymessage->SetScript(SCRIPT_TALLYHO);						//RJS 15Sep00

			if(caller->nationality == NAT_LUF)
			{
				SWord dhdg = spotheadg - SWord(caller->hdg);
				if((dhdg < ANGLES_90Deg) && (-dhdg < ANGLES_90Deg))
					prioritymessage->SetScript(SCRIPT_BANDITSAHEADLW);		//RJS 15Sep00
				else
					prioritymessage->SetScript(SCRIPT_BANDITSBEHINDLW);		//RJS 15Sep00
			}
//DeadCode RJS 13Sep100 		prioritymessage->target = spottrg;
		}

		SpottedUnfriendly(caller, AirStrucPtr(spottrg));

		return(true);
	}

//DeadCode CSB 1Sep00 	prioritymessage->scriptno = SCRIPT_NULL;
//DeadCode RJS 13Sep100 	prioritymessage->scriptno = PHRASE_THINKING;

	if(caller->follower)
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CANTSEE, MSG_CLEAR_RPT, caller->Follower(), NULL, caller)); 
	else if(caller->fly.nextflight)
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CANTSEE, MSG_CLEAR_RPT, caller->fly.nextflight, NULL, caller)); 

	return(false);
}


INSTANCEAI(CallBandit, ItemPtr)
{
	if(_DPlay.Implemented)
		return(false);
	
	AirStrucPtr lead = caller->FindFormpos0();
	SWord spotheadg = -View_Point->hdg;
	SWord spotpitch = -View_Point->pitch;
	const SWord vheadg = ANGLES_15Deg;
	const SWord vpitch = ANGLES_15Deg;
	AirStrucPtr spottrg = NULL;
	FP range2 = 2.0 * FP(VISIBLERANGE) * FP(VISIBLERANGE);

	for(int i = 0; i < ArtInt::ACARRAYSIZE; i++)
		if((ArtInt::ACArray[i]) && (ArtInt::ACArray[i]->nationality != caller->nationality))
			for(AirStrucPtr lead = ArtInt::ACArray[i]->GetLeadAc(); lead; lead = lead->fly.nextflight)
				for(AirStrucPtr ac = lead; ac; ac = ac->Follower())
					if(caller->Distance3DSquared(&ac->World) < range2)
					{
						caller->InterceptandRange(ac);
						SWord dheadg = SWord(caller->HdgIntercept)   - SWord(spotheadg);
						SWord dpitch = SWord(caller->PitchIntercept) - SWord(spotpitch);
						if((dheadg < vheadg) && (dheadg > -vheadg) && (dpitch < vpitch) && (dpitch > -vpitch))
						{
							spottrg = ac;
							range2 = caller->Distance3DSquared(&ac->World);
						}
					}

	if(spottrg)
	{
		if (prioritymessage)											//RJS 25Oct00
		{
			prioritymessage->target = spottrg;						//RJS 13Sep00
			prioritymessage->SetScript(PHRASE_TALLYHO);						//RJS 15Sep00

			SWord dhdg = spotheadg - SWord(caller->hdg);
			if((dhdg < ANGLES_90Deg) && (-dhdg < ANGLES_90Deg))
			{
				if	(caller->nationality == NAT_RAF)
		 			prioritymessage->SetScript(SCRIPT_BANDITSAHEADRAF);		//RJS 15Sep00
				else
		 			prioritymessage->SetScript(SCRIPT_BANDITSAHEADLW);		//RJS 15Sep00
			}else
			{
				if	(caller->nationality == NAT_RAF)
					prioritymessage->SetScript(SCRIPT_BANDITSBEHINDRAF);	//RJS 15Sep00
				else
					prioritymessage->SetScript(SCRIPT_BANDITSBEHINDLW);		//RJS 15Sep00
			}
		}
//DeadCode RJS 13Sep100 		prioritymessage->target = spottrg;

		SpottedUnfriendly(lead, AirStrucPtr(spottrg));

		return(true);
	}

//DeadCode RJS 13Sep100 	prioritymessage->scriptno = PHRASE_THINKING;
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CANTSEE, MSG_CLEAR_RPT, lead, NULL, caller)); 


	return(false);
}



INSTANCEAI(SightingRequest, ItemPtr)
{
	AirStrucPtr buddy = caller->FindAcInGroup();
	AirStrucPtr bandit = NULL;
	if(prioritymessage) 
	{
		if(caller->nationality == NAT_LUF)
			prioritymessage->SetScript(SCRIPT_WHEREISINDIAN);			//RJS 15Sep00
		else
			prioritymessage->SetScript(SCRIPT_WHEREISBANDIT);			//RJS 15Sep00

		if(buddy)
			prioritymessage->callee = buddy;		//null if no buddy
	}	

	if (buddy)
	{
		if((caller->ai.unfriendly) && (caller->ai.unfriendly->Status.size == AIRSTRUCSIZE))
			bandit = AirStrucPtr(caller->ai.unfriendly);
		int  count = -1;
			
		if (!bandit)
			bandit = caller->FindBandit(count);
		if((!bandit) || (caller->Distance3DSquared(&bandit->World) > FP(VISIBLERANGE) * FP(VISIBLERANGE)))
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_DONTKNOW, MSG_NOBANDITCALL_DELAY_LP_RPT, buddy , NULL, caller));	
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BANDIT_RELPOS, MSG_BANDITCALL_DELAY_LP_RPT, buddy, bandit, caller));
	}
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller)); //RDH 10/05/99//RJS 27Mar00

	return(true);
}


INSTANCEAI(CallBreak, ItemPtr)
{
	AirStrucPtr breaker = NULL;
	for(AirStrucPtr nf = caller->FindFormpos0(); nf; nf = nf->fly.nextflight)
		for(AirStrucPtr f = nf; f; f = f->Follower())
			if((f != caller) && (f->movecode == AUTO_COMBAT))
			{
				f->ai.ManStep = 0;
				f->SetManoeuvreTime(0);
				switch(Math_Lib.rnd(3))
				{
					case 0:	f->ai.manoeuvre = MANOEUVRE_BREAKTURN;	break;
					case 1:	f->ai.manoeuvre = MANOEUVRE_BREAKHIGH;	break;
					case 2:	f->ai.manoeuvre = MANOEUVRE_BREAK90;	break;
				}
				breaker = f;
			}

	if(breaker)
		return(false);

	for(nf = caller->FindFormpos0(); (nf) && (!breaker); nf = nf->fly.nextflight)
		for(AirStrucPtr f = nf; (f) && (!breaker); f = f->Follower())
			if(		(f != caller)
				&&	(caller->Distance3DSquared(&f->World) < FP(REDUCEDVISIBILITY) * FP(REDUCEDVISIBILITY))
				&&	(f->ai.attacker)
				&&	(f->Distance3DSquared(&f->ai.attacker->World) < FP(WEAPONSRANGE) * FP(WEAPONSRANGE))
				&&	(	FP(f->vel_x) * FP(f->World.X - f->ai.attacker->World.X)
						+ FP(f->vel_y) * FP(f->World.Y - f->ai.attacker->World.Y)
						+ FP(f->vel_z) * FP(f->World.Z - f->ai.attacker->World.Z) > 0)
				&&	(	FP(f->ai.attacker->vel_x) * FP(f->World.X - f->ai.attacker->World.X)
						+ FP(f->ai.attacker->vel_y) * FP(f->World.Y - f->ai.attacker->World.Y)
						+ FP(f->ai.attacker->vel_z) * FP(f->World.Z - f->ai.attacker->World.Z) > 0)	)
				breaker = f;
	
	if(breaker)
	{
		caller->BreakCallReaction(breaker, breaker->ai.attacker);
		return(true);
	}
	else
	{
		AirStrucPtr buddy = caller->FindBuddy();
		if(buddy)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WOLF, MSG_BREAKCALL_REPLY_DELAY, buddy, NULL, prioritymessage->caller));
		return(false);
	}
}


INSTANCEAI(FlakSighted, ItemPtr)
{
	AirStrucPtr lead = caller->FindFormpos0();
	AirStrucPtr flaktrg = NULL;
	FP range2 = FP(VISIBLERANGE) * FP(VISIBLERANGE);

	AaaMainList::AaaSubList* list = Three_Dee.livelist->aaalist;
	AaaMainList::AaaSubList* lstart = list;
	for(;;)
	{
		for(int i = 0; i < AaaMainList::SUBLISTSIZE; i++)
		{
			ItemPtr weapitem = list->aaaitem[i];
			if(weapitem)
			{
				Coords3D	weapoff;
				int			weapnum=0;
				ULong		mvel;
				UWord		mdelay;
				UWord		mburst;
				WeapAnimData* weapanim = SHAPE.GetWeaponLauncher(weapitem,weapnum,weapoff.X,weapoff.Y,weapoff.Z,mvel,mdelay,mburst,LT_MOVEGUN);
				if((weapanim) && (weapanim->target))
				{
					ItemPtr	trg = *MobileItem::currworld->ConvertPtrUID((UniqueID)weapanim->target);
					if((trg->Status.size == AIRSTRUCSIZE) && (AirStrucPtr(trg)->nationality != lead->nationality))
						if(lead->Distance3DSquared(&trg->World) < range2)
						{
							flaktrg = AirStrucPtr(trg);
							range2 = lead->Distance3DSquared(&trg->World);
						}
				}
			}
		}
		list = list->next;
		if(list == lstart)
			break;
	}

	if(flaktrg)
	{
		prioritymessage->target = flaktrg;
		prioritymessage->SetScript(SCRIPT_ACKACKFIRE);
//DeadCode CSB 2Oct00 		if(!lead->ai.unfriendly)
			SpottedUnfriendly(lead, AirStrucPtr(flaktrg));
//DeadCode CSB 2Oct00 		else
//DeadCode CSB 2Oct00 			SpottedNewUnfriendly(lead, AirStrucPtr(flaktrg));
		return(true);
	}
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CANTSEE, MSG_CLEAR_RPT, lead, NULL, caller)); 
	return(false);
}


INSTANCEAI(Covering, ItemPtr)
{
	AirStrucPtr buddy = NULL;
	FP range2 = FP(HALFVISIBLERANGE) * FP(HALFVISIBLERANGE);
	for(AirStrucPtr ld = caller->FindFormpos0(); ld; ld = ld->fly.nextflight)
		for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
			if(ac != caller)
			{
				FP r2 = ac->Distance3DSquared(&caller->World);
				if(r2 < range2)
				{
					buddy = ac;
					range2 = r2;
				}
			}

	if((buddy) && (caller->Distance3DSquared(&buddy->World) < FP(DANGERRANGE) * FP(DANGERRANGE)))
	{
		AirStrucPtr bandit = caller->FindBanditOnTail();				  //RDH 12/06/99

		if (bandit)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTCLEAR, MSG_CLEAR_RPT, buddy, NULL, caller));
		else
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_YOUCLEAR, MSG_CLEAR_RPT, buddy, NULL, caller));
			return(false);
		}
	}
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller));//RJS 27Mar00

	return(false);
}


INSTANCEAI(SixClr, ItemPtr)
{
	return(true);
}


INSTANCEAI(NotClr, ItemPtr)
{
	if(AirStrucPtr buddy = caller->FindBuddy())
	{
		if(AirStrucPtr bandit = buddy->FindBanditOnTail())
		{
			if (buddy->ai.unfriendly != bandit)
			{
				SetEngage(buddy, bandit, MANOEUVRE_SELECT, ANGLES_0Deg, ANGLES_0Deg, FALSE);
				return(true);
			}
		}
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_WHERE, MSG_NOTCLEAR_RPT_DELAY, buddy, NULL, prioritymessage->caller));
	}
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , NULL, NULL, caller));//RJS 27Mar00

	return(false);
}


INSTANCEAI(AttackMyTarget, ItemPtr)
{
	if(_DPlay.Implemented)
		return(false);
	
	AirStrucPtr buddy = caller->FindBuddy();
	AirStrucPtr replyto = AirStrucPtr(caller);
	if(!buddy)
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_NOBANDITCALL_X, buddy, NULL, replyto));
		return(false);
	}

	AirStrucPtr trackee = NULL;
	if(		(Trans_Obj.View_Object->trackeditem2)
		&&	(Trans_Obj.View_Object->trackeditem2->Status.size == AIRSTRUCSIZE)
		&&	(AirStrucPtr(Trans_Obj.View_Object->trackeditem2)->nationality != caller->nationality)	)
		trackee = AirStrucPtr(Trans_Obj.View_Object->trackeditem2);

	if(trackee)
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ENGAGEBANDIT, MSG_NOBANDITCALL_X, buddy, NULL, replyto));
		SetEngage(buddy, trackee, MANOEUVRE_SELECT, ANGLES_0Deg, ANGLES_0Deg, FALSE);
		return(true);
	}
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TARGETNOTIDENTIFIED, MSG_NOBANDITCALL_X, buddy, NULL, replyto));

	return(false);
}


TABLEAI(PostCombatMsg,ItemPtr)
{
	{PHRASE_REGROUP,		&Regroup,			SCRIPT_REGROUP},
	{PHRASE_S_SENDALLHOME,	&SendEveryoneHome,	SCRIPT_ALLGOHOME},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(PostCombatMsg,ItemPtr)	{return false;}


INSTANCEAI(Regroup, ItemPtr)
{
	caller->SetUnfriendly(NULL);

	for(AirStrucPtr nf = caller; nf; nf = nf->fly.nextflight)
		for(AirStrucPtr f = nf; f; f = f->Follower())
			if((f->movecode != AUTO_COMBAT) || (!f->ai.unfriendly))
			{
				f->SetUnfriendly(NULL);
				f->movecode = AUTO_FOLLOWWP;
				f->information = IF_OUT_POS;
				f->manoeuvretime = 0;
				f->ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
			}
	
//DeadCode CSB 13Sep00 	DisEngageAll(caller, prioritymessage);
	return(true);
}


INSTANCEAI(SendEveryoneHome, ItemPtr)
{
	if((caller->fly.leadflight) && (caller->fly.leadflight->classtype->aerobaticfactor == AEROBATIC_LOW) && (Math_Lib.rnd(2)))
	{
		SLong maxfuel = 0;
		SLong totfuel = 0;
		for(SWord i = 0; i < 4; i++)
		{
			maxfuel += caller->classtype->fueltankcap[i];
			totfuel += caller->fly.fuel_content[i] * 0.001;
		}
		if(4 * totfuel < maxfuel)
			prioritymessage->SetScript(SCRIPT_LOWFUELRTBFORGETBOMBERS);	//RJS 15Sep00
	}
	else
		switch(Math_Lib.rnd(4))
		{
			case 0:	prioritymessage->SetScript(SCRIPT_HOMEWELLDONE);	break;	//RJS 15Sep00
			case 1:	prioritymessage->SetScript(SCRIPT_ALLGOHOME);		break;	//RJS 15Sep00
			case 2:	prioritymessage->SetScript(SCRIPT_SENDEVERYBODY);	break;	//RJS 15Sep00
			case 3:	prioritymessage->SetScript(SCRIPT_ALLGOHOME);		break;	//RJS 15Sep00
		}

	caller->SetUnfriendly(NULL);

	for(AirStrucPtr nf = caller; nf; nf = nf->fly.nextflight)
		for(AirStrucPtr f = nf; f; f = f->Follower())
			if((f->movecode != AUTO_WAIT4TIME) && (f->movecode != AUTO_TAKEOFF) && (f->movecode != AUTO_LANDING))
			{
				f->waypoint = f->waypoint->FindWP(WPNAME_Landing);
				if((f->movecode != AUTO_COMBAT) || (!f->ai.unfriendly))
				{
					f->SetUnfriendly(NULL);
					f->movecode = AUTO_FOLLOWWP;
					f->information = IF_OUT_POS;
					f->manoeuvretime = 0;
					f->ai.manoeuvre = MANOEUVRE_SCREWYOUGUYSIMGOINGHOME;
				}
			}

	return(true);
}


////////////////////////////////////////////////////////////////////////
//
// Function:    TowerMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(TowerMsg,ItemPtr)
{
	{PHRASE_MAYDAY,				&MayDay,			SCRIPT_MAYDAY},
	{PHRASE_S_HOMETOWER,		&CallHomeTower,		SCRIPT_GIMMEAVECTOR},
	{PHRASE_S_NEARESTTOWER,		&CallNearestTower,	SCRIPT_GIMMEAVECTOR},
	{PHRASE_S_SURFACEWIND,		&WindUpdateLow,		SCRIPT_SURFACEWINDREQUEST}, 
	{PHRASE_S_ALTWIND,			&WindUpdateHigh,	SCRIPT_ALTWINDREQUEST}, 
	{PHRASE_S_HOMELANDCLEARANCE,	&HomeLandClear,		SCRIPT_LANDCLEARANCE}, 
	{PHRASE_S_NEARLANDCLEARANCE,	&NearLandClear,		SCRIPT_LANDCLEARANCE},
	{PHRASE_NULL}, 
	{PHRASE_NULL} 
};
INSTANCEAI(TowerMsg,ItemPtr)   {return false;}


INSTANCEAI(MayDay,ItemPtr)
{
	Persons2::PlayerSeenAC->BreakForm();

	ItemPtr af = NULL;
	FP range2 = FP(MILES50) * FP(MILES50);
	
	int	start=RAF_FighterAFBAND,stop=CLRadarBAND;
	if (caller->nationality==NAT_BLUE)
		start=LUF_FighterLF2BAND,stop=LUF_BomberBANDEND;

	for(int i=start;i<stop;i++)
	{
		ItemPtr thisaf = Persons2::ConvertPtrUID(UniqueID(i));
		if((thisaf) && (caller->Distance3DSquared(&thisaf->World) < range2))
		{
			range2 = caller->Distance3DSquared(&thisaf->World);
			af = thisaf;
		}
	}
		
	if(af)
	{
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_NEARESTAIRFIELD, MSG_MEDHIPRIORITY, VOICE_TOWER, af, caller));
		return(true);
	}
	
	_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , caller, NULL, caller));//RJS 27Mar00
	return(false);
}


INSTANCEAI(CallHomeTower,ItemPtr)
{
	bool retval = false;
	//for home field
	itemptr HomeAF = caller->ai.homebase;
	_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_STEER_RANGE, MSG_MEDHIPRIORITY, VOICE_TOWER, HomeAF, caller));

	return retval;
}


INSTANCEAI(CallNearestTower,ItemPtr)
{
	ItemPtr af = NULL;
	FP range2 = FP(MILES50) * FP(MILES50);
	
	int	start=RAF_FighterAFBAND,stop=CLRadarBAND;
	if (caller->nationality==NAT_BLUE)
		start=LUF_FighterLF2BAND,stop=LUF_BomberBANDEND;

	for(int i=start;i<stop;i++)
	{
		ItemPtr thisaf = Persons2::ConvertPtrUID(UniqueID(i));
		if((thisaf) && (caller->Distance3DSquared(&thisaf->World) < range2))
		{
			range2 = caller->Distance3DSquared(&thisaf->World);
			af = thisaf;
		}
	}
		
	if(af)
	{
		Persons2::PlayerSeenAC->BreakForm();
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_STEER_RANGE, MSG_MEDHIPRIORITY, VOICE_TOWER, af, caller));
		return(true);
	}
	
	_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , caller, NULL, caller));//RJS 27Mar00
	return(false);
}


INSTANCEAI(WindUpdateLow,ItemPtr)
{
	bool retval = false;
	if(Save_Data.flightdifficulty [FD_WINDEFFECTS])
		if(Save_Data.flightdifficulty [FD_WINDGUSTS])
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED_GUSTS, MSG_WIND_LOW_REPORT_RPT, VOICE_TOWER, NULL, caller));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_SURFACEWIND_BEARINGNO_SPEED, MSG_WIND_LOW_REPORT_RPT, VOICE_TOWER, NULL, caller));
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOWIND, MSG_WIND_LOW_REPORT_RPT, VOICE_TOWER, NULL, caller));

	return retval;
}


INSTANCEAI(WindUpdateHigh,ItemPtr)
{
	bool retval = false;
	if(Save_Data.flightdifficulty [FD_WINDEFFECTS])
	 	if(Save_Data.flightdifficulty [FD_WINDGUSTS])
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_ALTWIND_BEARINGNO_SPEED_GUSTS, MSG_WIND_HIGH_REPORT_RPT, VOICE_TOWER, NULL, caller));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_ALTWIND_BEARINGNO_SPEED, MSG_WIND_HIGH_REPORT_RPT, VOICE_TOWER, NULL, caller));
	else
		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOWIND, MSG_WIND_HIGH_REPORT_RPT, VOICE_TOWER, NULL, caller));

	return retval;
}


INSTANCEAI(HomeLandClear,ItemPtr)
{
	bool retval = false;
	itemptr HomeAF = caller->ai.homebase;
	callee->InterceptandRange(HomeAF);
	if(callee->PlayerInGroup())
	{
		if(callee->Range < MILES05)
		{
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOLAND, MSG_MEDHIPRIORITY, VOICE_TOWER, caller, caller));//, TRUE));
			
			if(!caller->formpos)
				for(AirStrucPtr nf = caller; nf; nf = nf->fly.nextflight)
					for(AirStrucPtr f = nf; f; f = f->Follower())
						f->waypoint = f->waypoint->FindWP(WPNAME_Landing);
		}
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TOWER_NOTSEEN_STEER_RANGE, MSG_MEDHIPRIORITY, VOICE_TOWER, HomeAF, caller));//, TRUE));
	}
	return retval;
}


INSTANCEAI(NearLandClear,ItemPtr)
{
	ItemPtr af = NULL;
	FP range2 = FP(MILES50) * FP(MILES50);
	
	int	start=RAF_FighterAFBAND,stop=CLRadarBAND;
	if (caller->nationality==NAT_BLUE)
		start=LUF_FighterLF2BAND,stop=LUF_BomberBANDEND;

	for(int i=start;i<stop;i++)
	{
		ItemPtr thisaf = Persons2::ConvertPtrUID(UniqueID(i));
		if((thisaf) && (caller->Distance3DSquared(&thisaf->World) < range2))
		{
			range2 = caller->Distance3DSquared(&thisaf->World);
			af = thisaf;
		}
	}
		
	if(af)
	{
		Persons2::PlayerSeenAC->BreakForm();
		if(range2 < FP(MILES05) * FP(MILES05))
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_CLEARTOLAND, MSG_MEDHIPRIORITY, VOICE_TOWER, af, caller));
		else
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TOWER_NOTSEEN_STEER_RANGE, MSG_MEDHIPRIORITY, VOICE_TOWER, af, caller));
		return(true);
	}
	
	_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR_RPT , caller, NULL, caller));//RJS 27Mar00
	return(false);
}


////////////////////////////////////////////////////////////////////////
//
// Function:    Strike
// Date:        11/02/00
// Author:      Craig Beeston
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
TABLEAI(Strike, ItemPtr)
{
	{PHRASE_BEGINYOURRUN,		&BeginRun,		SCRIPT_STARTINGTRGTRUN},
	{PHRASE_STRAFTARGET,		&Straffe,		SCRIPT_STRAFTARGET},
	{PHRASE_S_LEAVEAREA,		&LeaveArea,		SCRIPT_CLEARINGAREA},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(Strike, ItemPtr)	{return false;}


INSTANCEAI(BeginRun, ItemPtr)
{
	AirStrucPtr replier = caller->Follower();
	if(!replier)
		replier = caller->fly.nextflight;
	if(caller->movecode != AUTO_BOMB)
	{
		if(replier)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TARGETNOTIDENTIFIED, MSG_CLEAR_RPT, replier, NULL, caller));
		return(false);
	}
	else
	{
//DEADCODE MS 28/04/00 		if(replier)
//DEADCODE MS 28/04/00 			_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_OK, MSG_CLEAR_RPT, replier, NULL, caller));
		caller->ai.ManStep = PHASE3;
		for(AirStrucPtr nf = caller; nf; nf = nf->fly.nextflight)
			for(AirStrucPtr f = nf; f; f = f->Follower())
			{
				f->movecode = AUTO_BOMB;
				f->ai.ManStep = PHASE1;
			}
		return(true);
	}
}


INSTANCEAI(Straffe, ItemPtr)
{
	AirStrucPtr replier = caller->Follower();
	if(!replier)
		replier = caller->fly.nextflight;
	if(caller->movecode != AUTO_BOMB)
	{
		if(replier)
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TARGETNOTIDENTIFIED, MSG_CLEAR_RPT, replier, NULL, caller));
		return(false);
	}
	else
	{
		if(replier)
			_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_UNDERSTOOD, MSG_CLEAR_RPT, replier, NULL, caller));
		caller->ai.ManStep = 3;
		for(AirStrucPtr nf = caller; nf; nf = nf->fly.nextflight)
			for(AirStrucPtr f = nf; f; f = f->Follower())
			{
				f->movecode = AUTO_BOMB;
				f->ai.ManStep = 1;
			}
		return(true);
	}
}


INSTANCEAI(LeaveArea, ItemPtr)
{
	AirStrucPtr replier = caller->Follower();
	if(!replier)
		replier = caller->fly.nextflight;
	if(replier)
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_UNDERSTOOD, MSG_CLEAR_RPT, replier, NULL, caller));

	Trans_Obj.RaidEnd(caller->ai.unfriendly);				//RJS 09Mar00

	for(AirStrucPtr nf = caller; nf; nf = nf->fly.nextflight)
		for(AirStrucPtr f = nf; f; f = f->Follower())
		{
			f->SetUnfriendly(NULL);		//CSB 1Aug00
//DeadCode CSB 1Aug00 			f->ai.unfriendly = NULL;						//RJS 09Mar00
			f->movecode = AUTO_FOLLOWWP;					//RJS 09Mar00
			f->information = IF_OUT_POS;					//CSB 22Aug00
			f->manoeuvretime = 0;
//DeadCode RJS 09Mar00			f->ai.ManStep = 15;
		}
	return(true);
}


////////////////////////////////////////////////////////////////////////
//
// Function:    QuitContinue
// Date:        18/09/00
// Author:      Craig Beeston
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
//DeadCode JON 31Oct00 TABLEAI(QuitContinue, ItemPtr)
//DeadCode JON 31Oct00 {
//DeadCode JON 31Oct00 	{PhraseTables(PHRASE_TEXT_CONTINUE),	&Continue,		PHRASE_NULL},
//DeadCode JON 31Oct00 	{PhraseTables(PHRASE_TEXT_QUIT),		&Quit,			PHRASE_NULL},
//DeadCode JON 31Oct00 	{PHRASE_NULL},
//DeadCode JON 31Oct00 	{PHRASE_NULL},
//DeadCode JON 31Oct00 	{PHRASE_NULL},
//DeadCode JON 31Oct00 	{PHRASE_NULL},
//DeadCode JON 31Oct00 	{PHRASE_NULL},
//DeadCode JON 31Oct00 	{PHRASE_NULL}
//DeadCode JON 31Oct00 };
//DeadCode JON 31Oct00 INSTANCEAI(QuitContinue, ItemPtr)
//DeadCode JON 31Oct00 {
//DeadCode JON 31Oct00 	return(false);
//DeadCode JON 31Oct00 }
//DeadCode JON 31Oct00 
//DeadCode JON 31Oct00 
//DeadCode JON 31Oct00 INSTANCEAI(Continue, ItemPtr)
//DeadCode JON 31Oct00 {
//DeadCode JON 31Oct00 	return(false);
//DeadCode JON 31Oct00 }
//DeadCode JON 31Oct00 
//DeadCode JON 31Oct00 INSTANCEAI(Quit, ItemPtr)
//DeadCode JON 31Oct00 {
//DeadCode JON 31Oct00 	_DPlay.SimulateExitKey = TRUE;
//DeadCode JON 31Oct00 	return(true);
//DeadCode JON 31Oct00 }

				
INSTANCEAI(SetupQuitContinue, ItemPtr)
{
//DeadCode JON 31Oct00 	bool autovectoringon = Save_Data.gamedifficulty[GD_AUTOVECTORING];
//DeadCode JON 31Oct00 	Save_Data.gamedifficulty %= GD_AUTOVECTORING;
//DeadCode JON 31Oct00 	bool retval = SendMsgAndCall(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR, caller, caller, caller), QuitContinue);
//DeadCode JON 31Oct00 	if(autovectoringon)
//DeadCode JON 31Oct00 		Save_Data.gamedifficulty |= GD_AUTOVECTORING;
//DeadCode JON 31Oct00 	return(retval);
	OverLay.SetToContinueQuitScr();
	return false;
}


				
//////////////////////////////////////////////////////////////////////
//
// Function:    SecretMessages
// Date:		10/06/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
TABLEAI(SecretMessages,ItemPtr)
{
//DEADCODE DAW 23/02/99 	{PHRASE_INITIATECONTACT,	&InitiateContact, SCRIPT_MAKECONTACTWITHFAC},	
	{PHRASE_NULL,	&SecretStartTrucks,		PHRASE_NULL},
	{PHRASE_NULL},
	{PHRASE_NULL}
};
INSTANCEAI(SecretMessages,ItemPtr)	{return false;}


INSTANCEAI(SecretStartTrucks,ItemPtr)
{
	GR_TruckMoveCode=GROUND_TAXI;
	return false;
};


////////////////////////////////////////////////////////////////////////
//
// Function:    CommsPlayerMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
//TempCode RDH 22Feb99 TABLEAI(CommsPlyrMsg,ItemPtr)
//TempCode RDH 22Feb99 {
//Display the names of the comms players that can be chatted to
//There are a max of 8 comms players. Exclude the player from the list.
//Add:	send to all and send to my side
//TempCode RDH 22Feb99 };
//TempCode RDH 22Feb99 INSTANCEAI(CommsPlyrMsg,ItemPtr)	{return false;}

////////////////////////////////////////////////////////////////////////
//
// Function:    CommsMsgMsg
// Date:        15/02/99
// Author:      RDH
//
// Description: 
//
////////////////////////////////////////////////////////////////////////
//TempCode RDH 22Feb99 TABLEAI(CommsMsgMsg,ItemPtr)
//TempCode RDH 22Feb99 {
	//TempCode RDH 22Feb99 {},
	//TempCode RDH 22Feb99 {}
//display the list of user messages that can be sent
//These will be longer than other menus. Perhaps we need to be able to //change the size of the smoked glass panel

//TempCode RDH 22Feb99 };
//TempCode RDH 22Feb99 INSTANCEAI(CommsMsgMsg,ItemPtr)	{return false;}

void	AirStruc::SetGroupWP(WayPoint*	newwp)
{
	AirStruc*	currac = FindGroupLeader();
	while (currac)
	{
		AirStruc*	ac = currac;
		while (ac)
		{
			ac->waypoint = newwp;
			ac=(AirStruc*)ac->follower;
		}
		currac=currac->fly.nextflight;
	}

}
AirStruc*	AirStruc::AcShouldGoHome()
{
	AirStruc*	currac = FindGroupLeader();
	while (currac)
	{
		AirStruc*	ac = currac;
		while (ac)
		{
			if (ac->AircraftDamaged())
				return (ac);
			ac=(AirStruc*)ac->follower;
		}
		currac=currac->fly.nextflight;
	}
	return (NULL);
}


void ArtInt::DisEngageAll(AirStruc* caller, MESSAGE_STRUC* prioritymessage)
{
	if(caller==Persons2::PlayerSeenAC)								  //RDH 16/05/99
		caller=Persons2::PlayerGhostAC;								  //RDH 16/05/99

	Save_Data.gamedifficulty %= GD_AUTOVECTORING;

	AirStruc* leader = caller->FindGroupLeader();
	AirStruc* callee = caller->FindBuddy();
	if(callee)
	{
//DEADCODE CSB 14/02/00 		if (leader->fly.leadflight)
//DEADCODE CSB 14/02/00 			leader = leader->fly.leadflight;
		
		if(leader->movecode == AUTO_COMBAT)
		{
			leader->ai.manoeuvre = MANOEUVRE_TOPCOVER;		//this ensure everybody tries to disengage	
			leader->SetUnfriendly(NULL);								//CSB 1Aug00
//DeadCode CSB 1Aug00 			if(		(leader->ai.unfriendly)
//DeadCode CSB 1Aug00 				&&	(leader->ai.unfriendly->Status.size == AIRSTRUCSIZE)
//DeadCode CSB 1Aug00 				&&	(AirStrucPtr(leader->ai.unfriendly)->ai.attacker == leader)	)
//DeadCode CSB 1Aug00 				((AirStrucPtr)leader->ai.unfriendly)->ai.attacker = NULL;
//DeadCode CSB 1Aug00 			leader->ai.unfriendly = NULL;
		}
		else if(leader->movecode == AUTO_PRECOMBAT)
			AllBreakOff(leader);


		if (prioritymessage)
		{
			prioritymessage->caller = leader;
			prioritymessage->callee = callee;
		}

		_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_BREAK_ORBITREPLY, MSG_DISENGAGE_DELAY_LP_RPT, callee, NULL, leader));
//DEADCODE CSB 13/03/00 		for(AirStrucPtr lead = leader; lead; lead = lead->fly.nextflight)
//DEADCODE CSB 13/03/00 			for(AirStrucPtr foll = lead; foll; foll = foll->Follower())
//DEADCODE CSB 13/03/00 				if((foll->fly.callnum % 4) == 0)
//DEADCODE CSB 13/03/00 					if((foll != leader) && (foll->movecode == AUTO_COMBAT))
//DEADCODE CSB 13/03/00 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLEE_BREAK_ORBITREPLY, (MsgType)(MSG_DISENGAGE_DELAY_LP_RPT+MSG_BLOCKCHATTER), foll, NULL, caller));//RJS 06Jul99

//DEADCODE CSB 14/02/00 				{
//DEADCODE CSB 14/02/00 					if(foll != leader)
//DEADCODE CSB 14/02/00 					{
//DEADCODE CSB 14/02/00 						if (	(foll->movecode == AUTO_COMBAT)	||	(foll->movecode == AUTO_PRECOMBAT))
//DEADCODE CSB 14/02/00 						{
//DEADCODE CSB 14/02/00 	//DEADCODE RDH 17/05/99 						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_CALLER_DISENGAGING, MSG_DISENGAGE_DELAY_LP_RPT , foll, NULL, caller));
//DEADCODE CSB 14/02/00 	//we don't have disengaging in the other script so it is silent.
//DEADCODE CSB 14/02/00 	//solution is to say: roger
//DEADCODE CSB 14/02/00 							_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_CALLER_ROGER, (MsgType)(MSG_DISENGAGE_DELAY_LP_RPT+MSG_BLOCKCHATTER) , foll, NULL, caller));//RJS 06Jul99
//DEADCODE CSB 14/02/00 						}else
//DEADCODE CSB 14/02/00 							_Radio.TriggerMsg(MESSAGE_STRUC(OLDSCRIPT_CALLER_ROGER, (MsgType)(MSG_DISENGAGE_DELAY_LP_RPT+MSG_BLOCKCHATTER) , foll, NULL, caller));//RJS 06Jul99
//DEADCODE CSB 14/02/00 					}
//DEADCODE CSB 14/02/00 				}
	}else
		_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_THINKING, (MsgType)(MSG_CLEAR_RPT+MSG_BLOCKCHATTER) , NULL, NULL, leader));//RJS 27Mar00

}


WayPointPtr WayPoint::FindWP(WPNames name)
{
	if((!this) || (wpname == name))
		return(this);

	for(WayPointPtr newwp = this; newwp; newwp = newwp->next)
		if(newwp->wpname == name)
			return(newwp);

	for(newwp = this; newwp; newwp = newwp->prev)
		if(newwp->wpname == name)
			return(newwp);

//DeadCode AMM 21Sep00 	INT3;	//Can't find the desired waypoint !!!!
	return(this);

//DeadCode CSB 12Sep00 	WayPointPtr newwp = this;
//DeadCode CSB 12Sep00 	if (!this)
//DeadCode CSB 12Sep00 		return this;
//DeadCode CSB 12Sep00 	if (newwp->wpname >= name)
//DeadCode CSB 12Sep00 	{
//DeadCode CSB 12Sep00 		while (	(newwp) && (newwp->wpnum != 0 || newwp->wpname != name))
//DeadCode CSB 12Sep00 			newwp = newwp->prev;
//DeadCode CSB 12Sep00 		if (newwp)
//DeadCode CSB 12Sep00 			return (newwp);
//DeadCode CSB 12Sep00 		else
//DeadCode CSB 12Sep00 			return (this);
//DeadCode CSB 12Sep00 	}else 
//DeadCode CSB 12Sep00 	{
//DeadCode CSB 12Sep00 		while (	(newwp) && (newwp->wpnum != 0 || newwp->wpname != name))
//DeadCode CSB 12Sep00 			newwp = newwp->next;
//DeadCode CSB 12Sep00 		if (newwp)
//DeadCode CSB 12Sep00 			return (newwp);
//DeadCode CSB 12Sep00 		else
//DeadCode CSB 12Sep00 			return (this);
//DeadCode CSB 12Sep00 
//DeadCode CSB 12Sep00 	}
}
