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
//Filename       acmai.cpp
//System         
//Author         Andrew McRae
//Date           Mon 17 Mar 1997
//Description    Flight Model ACM
//------------------------------------------------------------------------------
//
//RANGES_Included
//
#define F_GRAFIX											//DAW 05Aug96
#define F_COMMON
#define F_BATTLE

#include <stdio.h>
#include <string.h>


#include "collided.h"										//PD 06Sep96
#include "Dosdefs.h"		
#include "Worldinc.h"

#include "ranges.h"
#include "modvec.h"
#include "model.h"



#include "FlyModel.h"
#include "mymath.h"
#include "enumbits.m"
#include "mytime.h"											//RDH 25Apr96
#include "ranges.h"
#include "missman2.h"										//JIM 22Aug96
#include "movement.h"
#include "transite.h"


#include "ai.h"
#include "miles.h"											//RDH 25Jul96
#include "landscap.h"										//RDH 18Dec96
#include "viewsel.h"										//RDH 25Jul96
#include "3dcom.h"											//RJS 22Aug96
#include "speed.h"											//RDH 01Oct96
#include "persons2.h"

#include "model.h"
#include "monotxt.h"

#include "matrix.h"
#include "winmove.h"
#include "airstruc.h"  
#include "rchatter.h"

//#define PRINT_AI_DATA	//CSB 16/03/99
//MATHABLE	(ANGLES)


static RequiredBankDataElement 	GentleBankData[] =
	{
		{ANGLES_0Deg,		ANGLES_0Deg},
		{ANGLES_30Deg,		ANGLES_60Deg},
		{ANGLES_180BareDeg, ANGLES_60Deg}
//DEADCODE CSB 16/03/00 		{ANGLES_0Deg,		ANGLES_0Deg},
//DEADCODE CSB 16/03/00 		{ANGLES_20Deg,		ANGLES_75_5Deg},
//DEADCODE CSB 16/03/00 		{ANGLES_180BareDeg, ANGLES_75_5Deg}
	};


// ROD don't use STALL_ANGLE
ANGLES const	STALL_ANGLE = ANGLES_15Deg;

ANGLES const	STALL_ANGLE_MINUSONE = STALL_ANGLE - ANGLES_1Deg;
ANGLES const	STALL_ANGLE_MINUSTWO = STALL_ANGLE - ANGLES_2Deg;
ANGLES const	STALL_ANGLE_MINUSTHREE = STALL_ANGLE - ANGLES_3Deg;
//DeadCode RDH 09Jul96 SLong	const	ELEVATOR_DELTA = 160;
SLong	const	ELEVATOR_DELTA = 40;
SLong	const	ELEVATOR_DELTA_DOWN = ELEVATOR_DELTA * 2;
SLong	const	RUDDER_DELTA = 1000;
//SLong	const	MAXAUTOTHRUST = 80;	

ANGLES const	DSLIPFORMAXRUDDER = ANGLES_10Deg;
ANGLES const	DPITCHFORMAXELEVATOR = ANGLES_60Deg;
ANGLES const	DAOAFORMAXELEVATOR = ANGLES_15Deg;
//sensitivity for Diferential control
ANGLES const	DIFFPITCHFORMAXELEVATOR = ANGLES_10Deg;
ANGLES const	DHDGFORMAXAILERON = ANGLES_22Deg;
//DeadCode RDH 02Jul96 SLong const MAXELEVATORFORTIGHTTURN = -30000;
//DeadCode RDH 30Oct96 SLong const MAXELEVATORFORTIGHTTURN = -20000;
SLong const MAXELEVATORFORTIGHTTURN = -25000;
SLong const SLIGHTPULLELEVATOR = -4000;
SLong const MEDIUMPULLELEVATOR = -12000;
SLong const HEAVYPULLELEVATOR = -20352;							//RDH 21Aug96


extern RequiredBankDataElement 	CombatReqBankData[];

void	ACMAirStruc::MoveToThrust (SWord thrust)
{
}

  //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
  //Procedure		MoveToHdg
  //Author		R. Hyde 
  //Date			Wed 13 Dec 1995
  //
  //Description	based on difference between desired and actual hdg, fix aileron
  //				to give a roll, morale and skill will fix maxroll				
  //
  //Inputs		
  //
  //Returns	
  //
  //------------------------------------------------------------------------------
 void	ACMAirStruc::MoveToHdg (ANGLES desiredhdg, ANGLES desiredpitch)
 {
  	ACMMODEL& ACM = *fly.pAcmModel;

	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;

	reqdeltahdg = (SWord)hdg - (SWord)desiredhdg;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

	reqdeltapitch = (SWord)desiredpitch - (SWord)fly.cpitch;
	Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);

	if((reqdeltahdg > ANGLES_10Deg) || (reqdeltahdg < -ANGLES_10Deg))
		TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, ANGLES_0Deg);
	else
	{
		if( ((SWord)roll > ANGLES_45Deg) || ((SWord)roll < -ANGLES_45Deg) )
			;
//DeadCode CSB 19/03/99				ACM.Pitch(0);	
		else
			ACM.VelPitch(desiredpitch);
		SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
		ACM.Roll(reqroll);
	}

	ACM.SetRudder(0);
  }
 

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveToDesiredHdg
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::MoveToDesiredHdg (ANGLES desiredhdg,ANGLES desiredpitch,ANGLES target)

{
	Bool	retval;

	MoveToHdg (desiredhdg, desiredpitch);
	retval = ChkAtDesiredHdg (desiredhdg,target);
	return (retval);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRequiredRoll
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	Find the roll to put trgitem on lift vector of srcitem
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ANGLES GetRequiredRoll(rotitem& srcItem,COORDS3D trg, Float& pitch, Float& hdg)

{
	//const Float _PI=22/7;
 	FPMATRIX fpmMatrix;
	_matrix.generate(-srcItem.hdg,-srcItem.pitch,-srcItem.roll,&fpmMatrix);
	IFShare	x,y,z;
	x.i=trg.X-srcItem.World.X;
	y.i=trg.Y-srcItem.World.Y;
	z.i=trg.Z-srcItem.World.Z;
	_matrix.transform(&fpmMatrix,x,y,z);
	if (z.f<0.) z.f=-z.f;
	x.f/=z.f;
	hdg = x.f;
	y.f/=z.f;
	_asm {
		fld x.f;
		fld y.f;
		fpatan;
		fstp x.f;
	}
	//x.f is required angle in radians
	x.f=Float(32768)*x.f/FPIE;
	pitch = y.f;
	return (Angles)(UWord)x.f;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlyWing
//Author		Craig Beeston 
//Date			Thu 16 Mar 2000
//
//Description	Like AutoFollowWpWing but in combat
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::FlyWing(AirStrucPtr lead, ANGLES relhdg = ANGLES_0Deg, int dist = 2500)
{
	ACMMODEL& ACM = *fly.pAcmModel;

	const SLong aimtime = 250;
	COORDS3D aimworld;
	if(relhdg == ANGLES_0Deg)
		aimworld = *PositionWRTLeader(lead);
	else
	{
		relhdg += lead->hdg;
		Float sin, cos;
		Math_Lib.high_sin_cos(relhdg, sin, cos);
		aimworld.X = lead->World.X + sin * Float(dist);
		aimworld.Y = lead->World.Y;
		aimworld.Z = lead->World.Z + cos * Float(dist);
	}
	if(lead->vel_ < classtype->minvel) 
		aimworld.Y += 15000;

	aimworld.X += (lead->vel_x * aimtime) / 10000;
	aimworld.Y += (lead->vel_y * aimtime) / 10000;
	aimworld.Z += (lead->vel_z * aimtime) / 10000;
	InterceptandRange(&aimworld);
	ACM.VelPitch(PitchIntercept);
	SWord desroll = FindRequiredRoll (hdg - HdgIntercept, CombatReqBankData);
	ACM.FastRoll(desroll);

	SLong desvel = lead->vel_ + (Range - (lead->vel_ * aimtime) / 10000) * 100;	//1 metres -> 1 m/s
	if(desvel < classtype->minvel)
		desvel = classtype->minvel;
	if(vel_ < desvel)
		ACM.Thrust(100);
	else
		ACM.Thrust(0);
}

	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LookAround
//Author		R. Hyde 
//Date			Mon 19 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::LookAround ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			ACM.Thrust(100);
			if(formpos == 0)
				SetManoeuvreTime(3000);
			else
				SetManoeuvreTime(1500);
			ai.desiredroll = - (ANGLES)ANGLES_45Deg + (Angles)(ANGLES_90Deg * Math_Lib.rnd(2)); 
			ai.ManStep = PHASE1;
		}

		case PHASE1:
		{
			if(!formpos)
			{
				AirStrucPtr buddy = fly.leadflight;
				if(!buddy)
					buddy = FindBuddy();;
				if(buddy)
				{
					despos = buddy->World;
//DeadCode CSB 22Jun00 					despos.Y += 15000;
					InterceptandRange(&despos);
					SWord reqdeltahdg = hdg - HdgIntercept;
			 		SWord reqroll = FindRequiredRoll(reqdeltahdg, CombatReqBankData);
					ACM.FastRoll(reqroll);
					ACM.VelPitch(PitchIntercept);
				}
				else
				{
					ACM.FastRoll(ai.desiredroll);
					ACM.VelPitch(BestClimbAngle());
				}
			}
			else
			{
				InterceptandRange(FindFormpos0());
				SWord reqdeltahdg = hdg - HdgIntercept;
			 	SWord reqroll = FindRequiredRoll(reqdeltahdg, CombatReqBankData);
				ACM.FastRoll(reqroll);
				ACM.VelPitch(PitchIntercept);
			}

			if (!ManoeuvreTimeLeft())
			{
		    	ai.ManStep = PHASE0;
				if(formpos == 0)
				{
					if(AllButLdrNotOnCombat ())				//RDH 26Nov96
						ai.manoeuvre = MANOEUVRE_TOPCOVER;		//RDH 26Nov96
					else										//RDH 26Nov96
						ai.manoeuvre = MANOEUVRE_LOOKROUND;		//RDH 26Nov96
				}
				else
					if(FindFormpos0()->ai.manoeuvre == MANOEUVRE_TOPCOVER)
						ai.manoeuvre = MANOEUVRE_TOPCOVER;
					else
						Art_Int.AttackSpareInLeadersGroup(*this);	
 			}

			break;
		}
	}

//DEADCODE CSB 15/03/00 	switch (ai.ManStep)
//DEADCODE CSB 15/03/00 	{
//DEADCODE CSB 15/03/00 		case PHASE0:
//DEADCODE CSB 15/03/00 		{
//DEADCODE CSB 15/03/00 			MOD.Rudder = 0;
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 			ACM.Thrust (ThrustfromFF());
//DEADCODE CSB 15/03/00 			SetManoeuvreTime (2000);
//DEADCODE CSB 15/03/00 //DeadCode CSB 18/03/99	 			ai.desiredroll = -(ANGLES)ANGLES_30Deg +
//DEADCODE CSB 15/03/00 //DeadCode CSB 18/03/99						(Angles)(ANGLES_60Deg * Math_Lib.rnd(2)); 
//DEADCODE CSB 15/03/00  			ai.desiredroll = -(ANGLES)ANGLES_60Deg +	//CSB 18/03/99	
//DEADCODE CSB 15/03/00 					(Angles)(ANGLES_120Deg * Math_Lib.rnd(2));	//CSB 18/03/99	
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 			ai.ManStep = PHASE1;
//DEADCODE CSB 15/03/00 		}
//DEADCODE CSB 15/03/00 		case PHASE1:
//DEADCODE CSB 15/03/00 		{
//DEADCODE CSB 15/03/00 			if(!formpos)
//DEADCODE CSB 15/03/00 			{
//DEADCODE CSB 15/03/00 				ACM.Roll (ai.desiredroll);
//DEADCODE CSB 15/03/00 				ACM.VelPitch (BestClimbAngle());
//DEADCODE CSB 15/03/00 				ACM.MinHeight (FT_2000);
//DEADCODE CSB 15/03/00 			}
//DEADCODE CSB 15/03/00 			else
//DEADCODE CSB 15/03/00 			{
//DEADCODE CSB 15/03/00 				InterceptandRange(FindFormpos0());
//DEADCODE CSB 15/03/00 				SWord reqdeltahdg = hdg - HdgIntercept;
//DEADCODE CSB 15/03/00 			 	SWord reqroll = FindRequiredRoll(reqdeltahdg, CombatReqBankData);
//DEADCODE CSB 15/03/00 				ACM.Roll(reqroll);
//DEADCODE CSB 15/03/00 				ACM.VelPitch(PitchIntercept);
//DEADCODE CSB 15/03/00 			}
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 			if  (!ManoeuvreTimeLeft())
//DEADCODE CSB 15/03/00 			{
//DEADCODE CSB 15/03/00  		    	ai.ManStep = PHASE0;
//DEADCODE CSB 15/03/00  				if (formpos == 0)
//DEADCODE CSB 15/03/00  				{
//DEADCODE CSB 15/03/00  					if (AllButLdrNotOnCombat ())
//DEADCODE CSB 15/03/00  					{
//DEADCODE CSB 15/03/00  						ai.manoeuvre=MANOEUVRE_TOPCOVER;
//DEADCODE CSB 15/03/00  					}else
//DEADCODE CSB 15/03/00  					{
//DEADCODE CSB 15/03/00  						ai.manoeuvre=MANOEUVRE_LOOKROUND;
//DEADCODE CSB 15/03/00  					}
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  				}else
//DEADCODE CSB 15/03/00  				{
//DEADCODE CSB 15/03/00  					ai.manoeuvre=MANOEUVRE_TOPCOVER;
//DEADCODE CSB 15/03/00  				}
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 			}
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 		}
//DEADCODE CSB 15/03/00 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WeldedWingMan
//Author		R. Hyde 
//Date			Mon 2 Mar 1998
//
//Description	Formation flag not set so a/c can spot
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::WeldedWingMan()
{
	
//	stick to the leaders tail, range about 1000ft and weave
//	However for low morale bring wingman closer
//	For very low morale it should appear as if he is trying to stay in formation
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			ai.ManStep = PHASE1;
			ACM.maxdeltaforclosework = 0.0;
			SetManoeuvreTime (3000);


		}
		case PHASE1:
		{
			if (WeldedWingSixOK())
			{
				if (		(fly.leadflight)					
						&&	 (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER)
					)//force manoeuvre to allow disengage
						ai.manoeuvre = MANOEUVRE_SELECT;
				
				if (!leader)
					ai.manoeuvre = MANOEUVRE_SELECT;
				else
				{
	//DEADCODE PD 26/02/99 				FP desiredturn;
					double	desiredturn;

					COORDS3D	target;
					target = leader->World; 									//JIM 02Aug96
					target.Y +=	FT_500;
					InterceptandRange(&target);

					SWord	reqdeltahdg,reqdeltahdg_sign;
					UWord	reqdeltahdg_pos;
					reqdeltahdg = 	hdg - HdgIntercept;
					Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

					SWord	reqdeltapitch,reqdeltapitch_sign;
					UWord	reqdeltapitch_pos;
					reqdeltapitch = (SWord)PitchIntercept - (SWord)fly.cpitch;
					Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);

									
					if  (		(		(reqdeltahdg_pos < ANGLES_40Deg)
						&&	(ACM.maxdeltaforclosework == 0.0)
						)
						||
							(		(reqdeltahdg_pos < ANGLES_45Deg)
								&&	(ACM.maxdeltaforclosework != 0.0)
							)		
						)
					{
				 		SWord reqroll = RollforTurn(reqdeltapitch, reqdeltahdg, desiredturn, target);
						ACM.Roll ((Angles)reqroll);
		
					}else
					{
						ACM.maxdeltaforclosework = 0.0;
						TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, ANGLES_0Deg);
						ACM.SetRudder(0);
					}
					InterceptandRange (&leader->World);
					UWord DesRange = 256 * ai.morale;	// up to 650 metres
					if(DesRange < WEAPONSRANGE) DesRange = WEAPONSRANGE;

					if (Range < DesRange)
						ACM.Thrust (0);
					else
						ACM.Thrust (ThrustfromFF());
				
				}
			}
		}
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BailOut
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
void	ACMAirStruc::BailOut()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(0);	 
//DEADCODE CB 18/11/99 			Trans_Obj.LaunchCanopyEject(this,*mobileitem::currworld);
			ACM.CanopyOpen();
			AirStrucPtr	unfriendly = *ai.unfriendly;
			unfriendly->SetUnfriendly(NULL);							//CSB 1Aug00
//DeadCode CSB 1Aug00 			unfriendly->ai.unfriendly = NULL;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll(ANGLES_180Deg);
			ACM.Pitch(ANGLES_0Deg);
			SWord swroll = roll;
			if((swroll > ANGLES_135Deg) || (-swroll > ANGLES_135Deg))
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime(100);
			}
			break;
		}
		case PHASE2:
		{
			ACM.Roll(ANGLES_180Deg);
			ACM.SetElevator(16384);
			if(!TimeLeft())
			{
				Trans_Obj.LaunchParachute(this,this->World,0,*mobileitem::currworld);//RJS 06Dec99
//DeadCode CSB 14Nov00 				Manual_Pilot.DeathSequenceOverrideDiary(this, AUTO_DEATHSEQUENCE);	//RJS 31Oct00
				
				if((nationality == NAT_RAF) && (!PlayerInGroup()) && (!Math_Lib.rnd(20)))
				{
					AirStrucPtr caller = FindBuddy();
					AirStrucPtr callee = FindGroupLeader();
					if((caller) && (callee) && (caller != callee))
					{
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MAYDAYORBIT, MSG_DESCRIBEFRIEND, caller, *this, callee));
						_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_MAYDAYACKNOWLEDGE, MSG_EJECTREPLY, callee, *this, caller));
					}
				}
			}
			break;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TopCover
//Author		R. Hyde 
//Date			Mon 19 Aug 1996
//
//Description	The followers are supposed to go near to home line or
//				not depending on skill
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::TopCover ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL&    MOD = *fly.pModel;

	if(formpos == 0)
	{
		switch(ai.ManStep)
		{
			case PHASE0:
			{
				ACM.Thrust(90);
				ai.desiredroll = Angles(ANGLES_30Deg - ANGLES_60Deg * Math_Lib.rnd(2));
				SetManoeuvreTime(3000);
				ai.ManStep = PHASE1;
			}
			
			case PHASE1:
			{
				ACM.FastRoll(ai.desiredroll);
				ACM.VelPitch(BestClimbAngle());
				
				if(!TimeLeft())
				{
					if(AllOnTopCover())			
						Art_Int.AllBreakOff(this);
					else						
						SetManoeuvreTime(1500);
				}
			}
		}
	}
	else
	{
		switch(ai.ManStep)
		{
			case PHASE0:
			{
				ai.ManStep = PHASE1;
			}

			case PHASE1:
			{
		  		AirStrucPtr lead = FindGroupLeader();
				if(lead == Persons2::PlayerGhostAC)
					Art_Int.BreakOff(this);
				FlyWing(lead);
			}
		}

	}

//DEADCODE CSB 15/03/00 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE CSB 15/03/00 	MODEL& MOD = *fly.pModel;
//DEADCODE CSB 15/03/00 	UByte	FF = FlyingFactor();
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00    if (formpos == 0)
//DEADCODE CSB 15/03/00    {//leader
//DEADCODE CSB 15/03/00  	switch (ai.ManStep)
//DEADCODE CSB 15/03/00  	{
//DEADCODE CSB 15/03/00  		case PHASE0:
//DEADCODE CSB 15/03/00  		{
//DEADCODE CSB 15/03/00 			MOD.Rudder = 0;
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 			ACM.Thrust (ThrustfromFF());
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00  			SetManoeuvreTime (500);			//rdh 25/6/99
//DEADCODE CSB 15/03/00  			ai.desiredroll = -(ANGLES)ANGLES_60Deg +
//DEADCODE CSB 15/03/00   						(Angles)(ANGLES_120Deg * Math_Lib.rnd(2)); 
//DEADCODE CSB 15/03/00  			ai.ManStep = PHASE1;
//DEADCODE CSB 15/03/00  		}
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  		case PHASE1:
//DEADCODE CSB 15/03/00  		{
//DEADCODE CSB 15/03/00 			ACM.Roll (ai.desiredroll);
//DEADCODE CSB 15/03/00 			ACM.VelPitch (BestClimbAngle());
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00  			if (!ManoeuvreTimeLeft())
//DEADCODE CSB 15/03/00  			{
//DEADCODE CSB 15/03/00  				SetManoeuvreTime (1000);
//DEADCODE CSB 15/03/00  				ai.ManStep = PHASE2;
//DEADCODE CSB 15/03/00   			}
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  			break;
//DEADCODE CSB 15/03/00  		}
//DEADCODE CSB 15/03/00  		case PHASE2:
//DEADCODE CSB 15/03/00  		{
//DEADCODE CSB 15/03/00 			ACM.Roll (ai.desiredroll);
//DEADCODE CSB 15/03/00 			ACM.VelPitch (ANGLES_0Deg);
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  			if (!ManoeuvreTimeLeft())
//DEADCODE CSB 15/03/00  			{
//DEADCODE CSB 15/03/00  				ai.ManStep = PHASE3;
//DEADCODE CSB 15/03/00   			}
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  			break;
//DEADCODE CSB 15/03/00  		}
//DEADCODE CSB 15/03/00  		case PHASE3:
//DEADCODE CSB 15/03/00  		{
//DEADCODE CSB 15/03/00 			ACM.Roll (ai.desiredroll);
//DEADCODE CSB 15/03/00 			ACM.VelPitch (ANGLES_0Deg);
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  			if (AllOnTopCover ())
//DEADCODE CSB 15/03/00  			{
//DEADCODE CSB 15/03/00  				Art_Int.AllBreakOff(this);						//JIM 11Oct96
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00 //##				if (ai.eventlog->stage==EventLog::TAKEOFF)		//JIM 06Dec96
//DEADCODE CSB 15/03/00 //##					if (formpos!=0 || follower || fly.nextflight)
//DEADCODE CSB 15/03/00 //##					 	Persons_2.AddMessage(UserMsg::GOHOME,TEXT_SQUADRONREGROUPED,NULL);
//DEADCODE CSB 15/03/00  			}
//DEADCODE CSB 15/03/00  			else
//DEADCODE CSB 15/03/00  			{
//DEADCODE CSB 15/03/00  		    	ai.ManStep = PHASE1;
//DEADCODE CSB 15/03/00  				SetManoeuvreTime (1000);
//DEADCODE CSB 15/03/00  			}
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  			break;
//DEADCODE CSB 15/03/00  		}
//DEADCODE CSB 15/03/00    	}
//DEADCODE CSB 15/03/00    }else
//DEADCODE CSB 15/03/00    {
//DEADCODE CSB 15/03/00 	   	AirStruc* leader = FindGroupLeader();
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 	   if (leader == Persons2::PlayerGhostAC)
//DEADCODE CSB 15/03/00 	   {
//DEADCODE CSB 15/03/00 			Art_Int.BreakOff(this);
//DEADCODE CSB 15/03/00 	   }else
//DEADCODE CSB 15/03/00 	   {
//DEADCODE CSB 15/03/00  			switch (ai.ManStep)
//DEADCODE CSB 15/03/00  			{
//DEADCODE CSB 15/03/00  				case PHASE0:
//DEADCODE CSB 15/03/00  				{
//DEADCODE CSB 15/03/00 					MOD.Rudder = 0;
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 					ACM.Thrust (ThrustfromFF());
//DEADCODE CSB 15/03/00  					SetManoeuvreTime (500);
//DEADCODE CSB 15/03/00  					ai.desiredroll = -(ANGLES)ANGLES_60Deg +
//DEADCODE CSB 15/03/00   								(Angles)(ANGLES_120Deg * Math_Lib.rnd(2)); 
//DEADCODE CSB 15/03/00  					ai.ManStep = PHASE1;
//DEADCODE CSB 15/03/00  				}
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  				case PHASE1:
//DEADCODE CSB 15/03/00  				{
//DEADCODE CSB 15/03/00 					ACM.Roll (ai.desiredroll);
//DEADCODE CSB 15/03/00 					ACM.VelPitch (BestClimbAngle());
//DEADCODE CSB 15/03/00  					if (!ManoeuvreTimeLeft())
//DEADCODE CSB 15/03/00  					{
//DEADCODE CSB 15/03/00  						SetManoeuvreTime (1000);
//DEADCODE CSB 15/03/00  						ai.ManStep = PHASE2;
//DEADCODE CSB 15/03/00   					}
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00  					break;
//DEADCODE CSB 15/03/00  				}
//DEADCODE CSB 15/03/00  				case PHASE2:
//DEADCODE CSB 15/03/00  				{
//DEADCODE CSB 15/03/00  					if (fly.leadflight->World.Y > World.Y)
//DEADCODE CSB 15/03/00  					{
//DEADCODE CSB 15/03/00 						ACM.Roll (ai.desiredroll);
//DEADCODE CSB 15/03/00 						ACM.VelPitch (ANGLES_0Deg);
//DEADCODE CSB 15/03/00  					}else
//DEADCODE CSB 15/03/00  					{
//DEADCODE CSB 15/03/00 						ACM.Roll (ai.desiredroll);
//DEADCODE CSB 15/03/00 						ACM.VelPitch (ANGLES_5Deg);
//DEADCODE CSB 15/03/00  					}
//DEADCODE CSB 15/03/00  					break;
//DEADCODE CSB 15/03/00  				}
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00    			}
//DEADCODE CSB 15/03/00 	   }
//DEADCODE CSB 15/03/00    }
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ForceTopCover
//Author		Craig Beeston
//Date			Thu 09 Mar 2000
//
//Description	Circle above the coveree without trying to disengage
//				Check to see if coveree needs help every X seconds
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::ForceTopCover()
{
	ai.simpleacm = TRUE;
	SimpleForceTopCover();
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineAbreast
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
void	ACMAirStruc::LineAbreast()
{


	//only followers go line abreast. We don't link flights
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	if (!leader) 
	{//leader, do same as roundabout, get height, dive and then zoom
	 //at end of zoom, choose manoeuvre based on firsttactic
			ai.ManStep = PHASE0;
			ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;			
	}else
	{//follower
		if (Range < DANGERRANGE)
		{
			FireABullet(100);
		}
		else
		{
			switch (ai.ManStep)
			{
				case PHASE0:
				{
					MOD.Rudder = 0;
					ACM.Thrust (ThrustfromFF());
					ai.ManStep = PHASE1;
					ACM.maxdeltaforclosework = 0.0;

				}
				case PHASE1:
				{
					if(		(!leader) || (leader->movecode != AUTO_COMBAT) 
						||	(		(Leader()->ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_ZOOM)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_LINEABREAST)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_COLLISIONAVOIDANCE)	)	)
					{
						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
						ai.firsttactic = TACTIC_NULL;
					}
					else
						FlyWing(Leader(), ANGLES_90Deg, 128 * (formpos & 0xf0));
//DeadCode CSB 20Jun00 					{
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00  						COORDS3D	target;
//DeadCode CSB 20Jun00  						target = leader->World; 
//DeadCode CSB 20Jun00  						InterceptandRange(&target);
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00 						SWord c,s;
//DeadCode CSB 20Jun00 						SWord newhdg;
//DeadCode CSB 20Jun00 						SLong range;
//DeadCode CSB 20Jun00 						newhdg = leader->hdg + ANGLES_90Deg;
//DeadCode CSB 20Jun00 						Math_Lib.high_sin_cos((Angles)newhdg,s,c);
//DeadCode CSB 20Jun00 						range = METRES20;
//DeadCode CSB 20Jun00 						target.X = target.X + MULSHSIN(s, range, ANGLES_SHIFT);
//DeadCode CSB 20Jun00 						target.Y = target.Y;
//DeadCode CSB 20Jun00 						target.Z = target.Z + MULSHSIN(c, range, ANGLES_SHIFT);
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00 						Float fpitch, fhdg;
//DeadCode CSB 20Jun00 						SWord reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DeadCode CSB 20Jun00 						if  (		(	(fpitch < ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 									&&	(fpitch > -ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 									&&	(fhdg < ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 									&&	(fhdg > -ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 									)
//DeadCode CSB 20Jun00 							)
//DeadCode CSB 20Jun00 						{
//DeadCode CSB 20Jun00 							TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode CSB 20Jun00 						}else
//DeadCode CSB 20Jun00 						{
//DeadCode CSB 20Jun00 							ANGLES rroll;
//DeadCode CSB 20Jun00 							rroll = (Angles)(reqroll + roll);
//DeadCode CSB 20Jun00 							ACM.Roll (rroll);
//DeadCode CSB 20Jun00 							ACM.ZeroSpecificPower();
//DeadCode CSB 20Jun00 						}
//DeadCode CSB 20Jun00 					}
				}
			}
		}
	}
}


//
//use leader's unfriendly
//also use leader's phase
//Phase 0: stay out of way until separation say 100-200m
//
//phase 1: highest speed dive down to target + offset to avoid collision
//			AutoShoot() will do firing, all fire with  leader	
//phase 2:	at 200 yards, zoom climb
//				success depends on flyingskill
//				will break out of manoeuvre if attacked, damaged, winchester, bingo
//phase 3: establish circle around target, go to phase 0				



//

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scatter
//Author		R. Hyde 
//Date			Mon 30 Ma 1998
//
//Description	this is for a group of aircraft
//				all aircraft go into break turns
//				then mush around, easy targets
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Scatter()
{

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Pincer
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
void	ACMAirStruc::Pincer()
{

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			AirStrucPtr	unfriendly = *ai.unfriendly;
			SWord	sinbearing,cosbearing;
			SLong	range = METRES1200;
			ANGLES brg;

			brg = (Angles)((SWord)ai.desiredhdg + (SWord)unfriendly->hdg);
			Math_Lib.high_sin_cos(brg,sinbearing,cosbearing);

			despos = unfriendly->World; 			
			despos.X += MULDIVSIN (sinbearing,range,ANGLES_FRACT);
			despos.Z += MULDIVSIN (cosbearing,range,ANGLES_FRACT);
			despos.Y += FT_500;
			InterceptandRange (&despos);


			MoveToDesiredHdg (HdgIntercept,PitchIntercept, ANGLES_5Deg);
			if	(	(		(!ManoeuvreTimeLeft())
						&&	(Range < COMBATRANGE)
					)
					||
					(!SubjectFacingTarget(ANGLES_80Deg))
				 )
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}


//
//split force into 2: right and left
//find rightmost  ac in trg group
//find leftmost  ac in trg group
//set manoeuvretime to allow pass
//
//right unfriendly = rightmost in trg group
//fly to unfriendly beam(use desired hdg to set up which beam)

//exit when manoeuvretime up (something went wrong)
//or targeton tail
//reset unfriedly to one with lowest HdgIntercept 
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MultiWave
//Author		R. Hyde 
//Date			Wed 18 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::MultiWave()
{
 //The second wave gets set to this manoeuvre.
 //Aircraft are set to climb. This should provide separation and an advantage
 //Only exit when time is up and in engage range
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (3000);
			ai.ManStep = PHASE1;
   		}
		case PHASE1:
		{
			MoveToDesiredHdg (HdgIntercept, ANGLES_10Deg, ANGLES_5Deg);
			if  (		(!ManoeuvreTimeLeft())
					&&	(Range < ENGAGERANGE)
				)
					ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}



//	until range to unfriendly is < ENGAGERANGE
//		followleader using formpos to determine distance
//	then slect manoeuvre
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiveAndZoom
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::DiveAndZoom()
{
   	ACMMODEL& ACM = *fly.pAcmModel;

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			if((Range > FT_3000) && (World.Y < ai.unfriendly->World.Y + FT_1000))
			{
				ai.manoeuvre = MANOEUVRE_ZOOM;
				break;
			}
			ACM.Thrust(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord deltahdg = HdgIntercept - hdg;
			SWord desroll = deltahdg;
			MODLIMIT(desroll, ANGLES_75_5Deg);
			ACM.FastRoll(desroll);
			if((deltahdg < -ANGLES_45Deg) && (deltahdg > ANGLES_45Deg))
				ACM.VelPitch(ANGLES_0Deg);
			else
				ACM.VelPitch(SWord(PitchIntercept) / 2);
			if(Range < WEAPONSRANGE)
				ai.ManStep = PHASE2;
			break;
		}
		case PHASE2:
		{
			ACM.Pitch(PitchIntercept);
			SLong desroll = 5 * SLong(SWord(HdgIntercept - hdg));
			MODLIMIT(desroll, ANGLES_75_5Deg);
			ACM.FastRoll(desroll);
			if(Range < WEAPONSRANGE / 5)
			{
				ai.manoeuvre = MANOEUVRE_ZOOM;
				ai.ManStep = PHASE0;
			}
		}
	}

//DeadCode CSB 7Sep00  	SWord	deltapitch_pos,deltapitch_sign;
//DeadCode CSB 7Sep00  	SLong	temp_range;
//DeadCode CSB 7Sep00  	COORDS3D	target;
//DeadCode CSB 7Sep00  	SLong		t,actualrange;
//DeadCode CSB 7Sep00  	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 7Sep00   	SWord		deltaroll;										//RDH 14Mar96
//DeadCode CSB 7Sep00  	SWord		easestickforward;
//DeadCode CSB 7Sep00  	ANGLES		local_PI;
//DeadCode CSB 7Sep00    	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode CSB 7Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode CSB 7Sep00 	SWord	reqdeltahdg,reqdeltahdg_sign;
//DeadCode CSB 7Sep00 	UWord	reqdeltahdg_pos;
//DeadCode CSB 7Sep00 	FP desiredturn;
//DeadCode CSB 7Sep00 	SWord	reqdeltapitch,reqdeltapitch_sign;
//DeadCode CSB 7Sep00 	UWord	reqdeltapitch_pos;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00  
//DeadCode CSB 7Sep00  	local_PI  = PitchIntercept;
//DeadCode CSB 7Sep00 	reqdeltahdg = 	hdg - HdgIntercept;
//DeadCode CSB 7Sep00  	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DeadCode CSB 7Sep00 	reqdeltapitch = PitchIntercept - fly.cpitch;//	fly.cpitch - PitchIntercept;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00  
//DeadCode CSB 7Sep00  	switch (ai.ManStep)
//DeadCode CSB 7Sep00  	{
//DeadCode CSB 7Sep00  		case PHASE0:
//DeadCode CSB 7Sep00  		{
//DeadCode CSB 7Sep00 			MOD.Rudder = 0;
//DeadCode CSB 7Sep00   			MoveToThrust (100);
//DeadCode CSB 7Sep00  			ai.ManStep = PHASE1;
//DeadCode CSB 7Sep00 			SetManoeuvreTime (2000);
//DeadCode CSB 7Sep00  		}
//DeadCode CSB 7Sep00  		case PHASE1:
//DeadCode CSB 7Sep00  		{
//DeadCode CSB 7Sep00   			if  (SubjectOnTargetTail(ANGLES_120Deg))
//DeadCode CSB 7Sep00   			{
//DeadCode CSB 7Sep00   				ai.ManStep = PHASE2;
//DeadCode CSB 7Sep00 				if(		(!PlayerInGroup()) && (!Math_Lib.rnd(10))
//DeadCode CSB 7Sep00 					&&	(follower) && (Follower()->ai.manoeuvre == MANOEUVRE_LINEABREAST)	)
//DeadCode CSB 7Sep00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_ITSSUICIDE, MSG_INITIALCOMBAT, *this, NULL, Follower()));
//DeadCode CSB 7Sep00   			}
//DeadCode CSB 7Sep00 			if (!ManoeuvreTimeLeft())
//DeadCode CSB 7Sep00  			{
//DeadCode CSB 7Sep00  				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 7Sep00  			}
//DeadCode CSB 7Sep00 			target = ai.unfriendly->World;
//DeadCode CSB 7Sep00 			
//DeadCode CSB 7Sep00 			target.X = ai.unfriendly->World.X;
//DeadCode CSB 7Sep00 			target.Y = ai.unfriendly->World.Y + FT_3000;
//DeadCode CSB 7Sep00 			target.Z = ai.unfriendly->World.Z;
//DeadCode CSB 7Sep00 			InterceptandRange (&target);
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode CSB 7Sep00 //DeadCode RDH 16Dec98 			TurnFightSub(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode CSB 7Sep00 //			SWord reqroll;
//DeadCode CSB 7Sep00 //			if (reqdeltahdg > 0)
//DeadCode CSB 7Sep00 //				reqroll = ANGLES_290Deg;
//DeadCode CSB 7Sep00 //			else
//DeadCode CSB 7Sep00 //				reqroll = ANGLES_70Deg;
//DeadCode CSB 7Sep00 //			ACM.Roll ((Angles)reqroll);
//DeadCode CSB 7Sep00 ////DeadCode DAW 25Nov98 			ACM.LiftLimit();
//DeadCode CSB 7Sep00 //			ACM.ZeroSpecificPower();
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00  			break;
//DeadCode CSB 7Sep00  		}
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00  		case PHASE2:
//DeadCode CSB 7Sep00  		{
//DeadCode CSB 7Sep00   			if  (		(ClosureLessThan(MPH50))
//DeadCode CSB 7Sep00 					&&	(SubjectOnTargetTail(ANGLES_45Deg))
//DeadCode CSB 7Sep00 					&&	((World.Y - ai.unfriendly->World.Y) < FT_1000)
//DeadCode CSB 7Sep00 				)
//DeadCode CSB 7Sep00   			{
//DeadCode CSB 7Sep00   				GainSpeed ();									//RDH 05Jan99
//DeadCode CSB 7Sep00   			}else
//DeadCode CSB 7Sep00   			{
//DeadCode CSB 7Sep00   				LeadUnFriendly ();
//DeadCode CSB 7Sep00   			}
//DeadCode CSB 7Sep00   			if  ((Range - (World.Y - ai.unfriendly->World.Y)) < ENGAGERANGE)
//DeadCode CSB 7Sep00  
//DeadCode CSB 7Sep00   			{
//DeadCode CSB 7Sep00  				SetManoeuvreTime (5000);
//DeadCode CSB 7Sep00   				ai.ManStep = PHASE3;
//DeadCode CSB 7Sep00 				ACM.maxdeltaforclosework = 0.3;
//DeadCode CSB 7Sep00 				if(		(!PlayerInGroup()) && (!Math_Lib.rnd(10))
//DeadCode CSB 7Sep00 					&&	(follower) && (Follower()->ai.manoeuvre == MANOEUVRE_LINEABREAST)	)
//DeadCode CSB 7Sep00 					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_FORMATIONFIRING, MSG_INITIALCOMBAT, *this, NULL, Follower()));
//DeadCode CSB 7Sep00   			}
//DeadCode CSB 7Sep00   			if (local_PI << ANGLES_90Deg)
//DeadCode CSB 7Sep00   			{
//DeadCode CSB 7Sep00   				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 7Sep00   			}
//DeadCode CSB 7Sep00  			break;
//DeadCode CSB 7Sep00  		}
//DeadCode CSB 7Sep00  		case PHASE3:
//DeadCode CSB 7Sep00  		{
//DeadCode CSB 7Sep00  			temp_range = Range; 
//DeadCode CSB 7Sep00 			SLong vx, vy, vz;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			target.X = ai.unfriendly->World.X + vx;
//DeadCode CSB 7Sep00 			target.Y = ai.unfriendly->World.Y + vy;
//DeadCode CSB 7Sep00 			target.Z = ai.unfriendly->World.Z + vz;
//DeadCode CSB 7Sep00 			InterceptandRange (&target);
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			Float fpitch, fhdg;
//DeadCode CSB 7Sep00 			SWord reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DeadCode CSB 7Sep00 				if  (	(	(fpitch < ACM.maxdeltaforclosework)
//DeadCode CSB 7Sep00 					&&	(fpitch > -ACM.maxdeltaforclosework)
//DeadCode CSB 7Sep00 					&&	(fhdg < ACM.maxdeltaforclosework)
//DeadCode CSB 7Sep00 					&&	(fhdg > -ACM.maxdeltaforclosework)
//DeadCode CSB 7Sep00 				)
//DeadCode CSB 7Sep00 			)
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00 				TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);
//DeadCode CSB 7Sep00 			}else
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00 				ANGLES rroll;
//DeadCode CSB 7Sep00 				rroll = (Angles)(reqroll + roll);
//DeadCode CSB 7Sep00 				ACM.Roll (rroll);
//DeadCode CSB 7Sep00 				ACM.ZeroSpecificPower();
//DeadCode CSB 7Sep00 			}
//DeadCode CSB 7Sep00 //DeadCode RDH 25Nov98 			ACM.LiftLimit();
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			if  (	(!ManoeuvreTimeLeft())
//DeadCode CSB 7Sep00 					 ||
//DeadCode CSB 7Sep00 					(		(TargetOnSubjectTail(ANGLES_90Deg))
//DeadCode CSB 7Sep00 					&&	((World.Y - ai.unfriendly->World.Y) < FT_1000)
//DeadCode CSB 7Sep00 					)
//DeadCode CSB 7Sep00 				)
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00 			 	ai.ManStep = PHASE0;
//DeadCode CSB 7Sep00 				ai.manoeuvre=MANOEUVRE_ZOOM;
//DeadCode CSB 7Sep00 			}
//DeadCode CSB 7Sep00  			if  (	(ai.combatskill < SKILL_VETERAN)
//DeadCode CSB 7Sep00  			  	&&	(ChkAtDesiredHdg (HdgIntercept,ANGLES_5Deg))
//DeadCode CSB 7Sep00  				)
//DeadCode CSB 7Sep00  				FireABullet(100);
//DeadCode CSB 7Sep00   			
//DeadCode CSB 7Sep00  			break;
//DeadCode CSB 7Sep00  		}
//DeadCode CSB 7Sep00  
//DeadCode CSB 7Sep00  	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PanicTurn
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.63
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::PanicTurn()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	COORDS3D	target;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
 			ai.desiredhdg = hdg + ANGLES_60Deg; 

			SetManoeuvreTime (1500);

			ai.ManStep = PHASE1;
		}
		case PHASE1:
 		{
 			if  (		(!ManoeuvreTimeLeft())
				)
 			{
 				ai.ManStep = PHASE3;
				SetManoeuvreTime (6000);
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg, ANGLES_5Deg, ANGLES_5Deg))
 			{
				if (Math_Lib.rnd(6))
				{
					ai.ManStep = PHASE3;
					SetManoeuvreTime (6000);
				}else
				{
 					ai.ManStep = PHASE2;
 					ai.desiredhdg = hdg - ANGLES_120Deg; 
				}
 			}
 			break;
 		}
 		case PHASE2:
 		{
 			if (	(!ManoeuvreTimeLeft())
 					||	(Range > COMBATRANGE)
 					)
 			{
 				ai.ManStep = PHASE3;
				SetManoeuvreTime (6000);
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg,ANGLES_5Deg))
 			{
				if (Math_Lib.rnd(6))
				{
					ai.ManStep = PHASE3;
					SetManoeuvreTime (6000);
				}else
				{
	 				ai.ManStep = PHASE1;
 					ai.desiredhdg = hdg + ANGLES_120Deg; 
				}
 			}
 			break;
 		}

		case PHASE3:
		{
			ACM.maxdeltaforclosework = 0.1;
//DeadCode RDH 16Dec98 			ai.ManStep = PHASE1;
			target.X = ai.unfriendly->World.X;
			target.Y = ai.unfriendly->World.Y;
			target.Z = ai.unfriendly->World.Z;
			InterceptandRange (&target);
			TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);
//DeadCode RDH 16Dec98 			TurnWithPitchChange(HdgIntercept, FALSE,target);
//DeadCode RDH 16Dec98 			if (ai.ManStep == PHASE1)
//DeadCode RDH 16Dec98 				ai.ManStep = PHASE3;
 			if (!ManoeuvreTimeLeft())
 			{
  				ai.manoeuvre = MANOEUVRE_SELECT;
 			}

		}
	}




}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeadPursuit
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.63
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::LeadPursuit()
{
//	ifcombatakill high
//		turn in parallel plane so that target still visible
//
//	calc ideal lead
//		could base calc on maintaining collision course(hdg-hdgintercept?)
//	actual lead depends also on skill
//
// end after x secs or within DANGERRANGE

//DONE IN TURNING FIGHT	
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LagPursuit
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
void	ACMAirStruc::LagPursuit()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	COORDS3D	target;
	SLong		time;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());

			SetManoeuvreTime (2000);
			ai.ManStep = PHASE1;
			ai.desiredroll = unfriendly->roll;
			if (unfriendly->roll << ANGLES_180Deg)
				ai.desiredhdg = ANGLES_270Deg;
			else
				ai.desiredhdg = ANGLES_90Deg;

		}
		case PHASE1:
		{
				SWord c,s;
				SWord newhdg;
				SLong range;
				newhdg = unfriendly->hdg + ai.desiredhdg;
				Math_Lib.high_sin_cos((Angles)newhdg,s,c);
				if (SubjectOnTargetTail(ANGLES_90Deg))
					range = METRES200;
				else
					ai.manoeuvre = MANOEUVRE_SELECT;

				target.X = unfriendly->World.X + MULSHSIN(s, range, ANGLES_SHIFT);
				target.Y = unfriendly->World.Y;
				target.Z = unfriendly->World.Z + MULSHSIN(c, range, ANGLES_SHIFT);
				InterceptandRange (&target);

			TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);
//DeadCode RDH 16Dec98 			TurnFightSub(HdgIntercept, FALSE,ANGLES_0Deg,target);
			if  (		(!ManoeuvreTimeLeft())
					||	(		(ai.desiredroll << ANGLES_180Deg)
							&&	(unfriendly->roll >>ANGLES_180Deg)
						)
					||	(		(ai.desiredroll >> ANGLES_180Deg)
							&&	(unfriendly->roll << ANGLES_180Deg)
						)
				)
				ai.manoeuvre = MANOEUVRE_SELECT;

		}
	}





}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Circumvent
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Circumvent()
{
	//will not be implemented
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecoyActive
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//rdhvoid	ACMAirStruc::DecoyActive()
//{
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecoyPassive
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//rdh void	ACMAirStruc::DecoyPassive()
//{
//}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RoundAbout
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//															  
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::RoundAbout()
{

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;

			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (1500);
 			ai.desiredroll = -(ANGLES)ANGLES_60Deg +
					(Angles)(ANGLES_120Deg * Math_Lib.rnd(2)); 


			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord desroll = ai.desiredroll;
			UWord desroll_pos;
			SWord desroll_sign;
			Math_Lib.Pos (desroll,desroll_pos,desroll_sign);
			if	(SubjectFacingTarget(ANGLES_45Deg))
			//when facing unfriendly unroll to move towards it
				desroll_pos = desroll_pos/2;
			else
				desroll_pos = desroll_pos;
			if (desroll_sign==MathLib::NEGATIVE)
				desroll_pos = -desroll_pos;
			desroll = desroll_pos;
			ACM.Roll ((Angles)desroll);

			ACM.VelPitch (BestClimbAngle());
 			if  (		((Range - (World.Y - ai.unfriendly->World.Y)) < ENGAGERANGE)
					&&	((World.Y - ai.unfriendly->World.Y) > FT_3000)
				)
			{
 		    	ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			}

		}

//DEADCODE RDH 05/04/99 		case PHASE1:
//DEADCODE RDH 05/04/99 		{
//DEADCODE RDH 05/04/99 			ACM.Roll (ai.desiredroll);
//DEADCODE RDH 05/04/99 			ACM.Pitch (BestClimbAngle());
//DEADCODE RDH 05/04/99 			ACM.MinHeight (FT_2000);
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 			if  (!ManoeuvreTimeLeft())
//DEADCODE RDH 05/04/99 			{
//DEADCODE RDH 05/04/99  		    	ai.ManStep = PHASE0;
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 				if (ai.firsttactic == TACTIC_LINEABREAST)
//DEADCODE RDH 05/04/99 					ai.manoeuvre = MANOEUVRE_LINEABREAST;
//DEADCODE RDH 05/04/99 				else if (ai.firsttactic == TACTIC_LINEASTERN)
//DEADCODE RDH 05/04/99 					ai.manoeuvre = MANOEUVRE_LINEASTERN;
//DEADCODE RDH 05/04/99 				else
//DEADCODE RDH 05/04/99 					ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE RDH 05/04/99 			}
//DEADCODE RDH 05/04/99 
//DEADCODE RDH 05/04/99 		}
	}
//	if leader attain the desiredalt
//	else line astern
//	if unfriendly is set
//			fly towards for x secs
//			flyaway and repeat
//	else
//			circle

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SplitManoeuvre
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ResetUnfriendly()
{
//	reset the unfriendlies, so that ac goes after a more appropriate one
//	good to do after a pass or a split manoeuvre
//
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SplitManoeuvre
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SplitManoeuvre()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			if  (		(MoveToDesiredHdg (ai.desiredhdg, ai.desiredpitch, ANGLES_40Deg))
					||	(!ManoeuvreTimeLeft())
				)
			{
				RndVal	rndnum = Math_Lib.rnd();
				if (		(rndnum > RND50PC)
						&&	(ai.morale < MORALE_MEDIUM)
					)
				{
					ai.ManStep = PHASE0;
					ai.manoeuvre = MANOEUVRE_EXTENSION;
				}else
					ai.manoeuvre = MANOEUVRE_SELECT;
			}

		}
	}






}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HeadOn
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Theoretically no offset, 
//				However use a little to avoid collision
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::HeadOn ( )
{
	//just pass to the side
	//poor pilots may turn too early
	//good pilots may turn early
	//on passing pilot skill will dtermine action

		ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	
	COORDS3D	target;
	SWord c,s;
	SWord newhdg;
	UByte	FF = FlyingFactor();

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			SWord dhdg = HdgIntercept - hdg;
			if ((dhdg) > 0)
				ai.desiredhdg = ANGLES_90Deg;
			else
				ai.desiredhdg = ANGLES_270Deg;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca )
				ACM.VelPitch (bca);
			else
				ACM.Pitch (PitchIntercept);

			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((METRES30 * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((METRES30 * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - desiredhdg;
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			ACM.Roll ((Angles)reqroll);


			int decisionpoint = Math_Lib.rnd(2);

			if  (		(Range < (2 * BREAKTURNRADIUS ))
					&&	(FF < 200)
				)
			{//poor pilot might turn too early
				if (decisionpoint)
				{
					if (FF < 90)
					{
						ai.manoeuvre = MANOEUVRE_PANICTURN;
						ai.ManStep = PHASE0;
					}else  
					{
						ai.manoeuvre = MANOEUVRE_BREAKTURN;
						ai.ManStep = PHASE0;
					}
				}else
				{
					ai.ManStep = PHASE2;
				}

			}else if	(		(Range < BREAKTURNRADIUS)
							
						)
			{//good pilot might turn early to get advantage
				if (decisionpoint)
				{
					ai.manoeuvre = MANOEUVRE_BREAKTURN;
					ai.ManStep = PHASE0;
				}else
				{
					ai.desiredhdg = ai.desiredhdg  + ANGLES_180Deg;
					ai.ManStep = PHASE2;
				}
			}

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE2:
		{
			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca )
				ACM.VelPitch (bca);
			else
				ACM.Pitch (PitchIntercept);

			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((METRES30 * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((METRES30 * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - ai.desiredhdg;
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			MODLIMIT(reqroll, ANGLES_45Deg);
			ACM.Roll ((Angles)reqroll);

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			if	(SubjectOnTargetTail(ANGLES_80Deg))
			{
				if	(		(ai.unfriendly == Manual_Pilot.ControlledAC2)
						&&	(((AirStruc*)ai.unfriendly)->Follower())
					)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON, MSG_HEADON, ((AirStruc*)ai.unfriendly)->Follower(), *this, ((AirStruc*)ai.unfriendly)));

				int startpoint = Math_Lib.rnd(2);
				ai.ManStep = PHASE0;
				if (FF < 90)
				{
					if (startpoint)
						ai.manoeuvre = MANOEUVRE_JINK;
					else
						ai.manoeuvre = MANOEUVRE_MILDSCISSORS;
//DeadCode CSB 23Jun00 				}else if (FF < 200)
//DeadCode CSB 23Jun00 				{
//DeadCode CSB 23Jun00 					if (startpoint)
//DeadCode CSB 23Jun00 							ai.manoeuvre = MANOEUVRE_STRAIGHTANDLEVEL;
//DeadCode CSB 23Jun00 					else
//DeadCode CSB 23Jun00 							ai.manoeuvre = MANOEUVRE_EXTENSION;
				}else 
				{
					if (startpoint)
							ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
					else
							ai.manoeuvre = MANOEUVRE_BREAKTURN;
				}
			}
		}
	}
	
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LineAstern
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
void	ACMAirStruc::LineAstern()
{
//only followers go line astern. We don't link flights
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	if (!leader) 
	{//leader, do same as roundabout, get height, dive and then zoom
	 //at end of zoom, choose manoeuvre based on firsttactic
			ai.ManStep = PHASE0;
//DEADCODE CB 18/11/99 			ai.manoeuvre = MANOEUVRE_ROUNDABOUT;			
			ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
	}else
	{//follower
		if (Range < WEAPONSRANGE)
		{
			ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			ai.ManStep = PHASE0;
		}
		else
		{
			switch (ai.ManStep)
			{
				case PHASE0:
				{
					MOD.Rudder = 0;
					ACM.Thrust (ThrustfromFF());
					ai.ManStep = PHASE1;
					ACM.maxdeltaforclosework = 0.0;

				}
				case PHASE1:
				{
					if(		(!leader) || (leader->movecode != AUTO_COMBAT) 
						||	(		(Leader()->ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_LINEABREAST)
								&&	(Leader()->ai.manoeuvre != MANOEUVRE_COLLISIONAVOIDANCE)	)	)
					{
						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
						ai.firsttactic = TACTIC_NULL;
					}
					else
						FlyWing(Leader(), ANGLES_90Deg, 128 * (formpos & 0xf0));
						
//DeadCode CSB 20Jun00 					if (!leader)
//DeadCode CSB 20Jun00 						ai.manoeuvre = MANOEUVRE_SELECT;					//if no leader break manoeuvre
//DeadCode CSB 20Jun00 					else
//DeadCode CSB 20Jun00 					{
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00  						COORDS3D	target;
//DeadCode CSB 20Jun00  						target = leader->World; 
//DeadCode CSB 20Jun00  						InterceptandRange(&target);
//DeadCode CSB 20Jun00 						Float fpitch, fhdg;
//DeadCode CSB 20Jun00 						SWord reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DeadCode CSB 20Jun00 						if  (		(	(fpitch < ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 									&&	(fpitch > -ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 									&&	(fhdg < ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 									&&	(fhdg > -ACM.maxdeltaforclosework)
//DeadCode CSB 20Jun00 									)
//DeadCode CSB 20Jun00 							)
//DeadCode CSB 20Jun00 						{
//DeadCode CSB 20Jun00 							TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode CSB 20Jun00 						}else
//DeadCode CSB 20Jun00 						{
//DeadCode CSB 20Jun00 							ANGLES rroll;
//DeadCode CSB 20Jun00 							rroll = (Angles)(reqroll + roll);
//DeadCode CSB 20Jun00 							ACM.Roll (rroll);
//DeadCode CSB 20Jun00 							ACM.ZeroSpecificPower();
//DeadCode CSB 20Jun00 						}
//DeadCode CSB 20Jun00 						if (Range < METRES200)
//DeadCode CSB 20Jun00  							   ACM.SpeedBrakesOut();
//DeadCode CSB 20Jun00  						else
//DeadCode CSB 20Jun00  							ACM.SpeedBrakesIn();
//DeadCode CSB 20Jun00  						if (Range < METRES400)
//DeadCode CSB 20Jun00  							ACM.Thrust (0);
//DeadCode CSB 20Jun00  						else
//DeadCode CSB 20Jun00  							ACM.Thrust (ThrustfromFF());
//DeadCode CSB 20Jun00 
//DeadCode CSB 20Jun00 					}
				}
			}
		}
	}
}


//
//use leader's unfriendly
//also use leader's phase
//Phase 0: stay out of way until separation exceeds say 400m
//
//phase 1: if leader 
//				highest speed dive down to target
//			else
//				follow using formation data
//phase 2: when leader in DANGERRANGE
//				do highest speed dive down to target
//			AutoShoot() will do firing	(avoid firing at buddy)
//phase 2:	at 200 yards, zoom climb
//				success depends on flyingskill
//				will break out of manoeuvre if attacked, damaged, winchester, bingo
//phase 3: establish circle around target, go to phase 0				
//


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		VicAttack
//Author		Craig Beeston
//Date			Wed 15 Mar 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::VicAttack()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch(ai.ManStep)
	{
		case PHASE0:	//Initialise
		{
			ACM.Thrust(90);
			if(position())
				ai.ManStep = PHASE2;
			else
			{
				ai.ManStep = PHASE1;
				SetManoeuvreTime(250 * formpos);
			}
		}

		case PHASE1:	//Wait a bit
		{
			ACM.VelPitch(ANGLES_0Deg);
			ACM.Roll(ANGLES_0Deg);
			if(!TimeLeft())
				ai.ManStep = PHASE2;
			break;
		}

		case PHASE2:	//Approach Target
		{
			if(position() == 0)
			{
				InterceptandRange(ai.unfriendly);
				ACM.VelPitch(PitchIntercept);
				SWord desroll = FindRequiredRoll (hdg - HdgIntercept, GentleBankData);
				ACM.Roll(desroll);
			}
			else
			{
				AirStrucPtr lead = FindLeadCandidate();
				if((lead) && (lead->ai.manoeuvre == MANOEUVRE_VICATTACK))
					FlyWing(lead);
			}
			
			if(Distance3DSquared(&ai.unfriendly->World) < FP(50000) * FP(50000))
			{
				ACM.Thrust(100);
				ai.ManStep = PHASE3;
			}
			break;
		}

		case PHASE3:	//Aim at own Targets
		{
			InterceptandRange(ai.unfriendly);
			ACM.Pitch(PitchIntercept);
			SWord desroll = FindRequiredRoll (hdg - HdgIntercept, CombatReqBankData);
			ACM.FastRoll(desroll);

			if(Range < 5000)
			{
				ai.ManStep = PHASE4;
				SetManoeuvreTime(500);
			}
			break;
		}

		case PHASE4:	//Hard Dive
		{
			ACM.Pitch(ANGLES_315Deg);
			ACM.Roll(ANGLES_0Deg);
			if(!TimeLeft())
			{
				ai.firsttactic = TACTIC_NULL;
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BarrelRollAttack
//Author		Andrew McRae
//Date			Mon 2 Jun 1997
//
//Description	1.69
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::BarrelRollAttack ( )
{
//roll wings level
//pull up
//slow roll towads enemy to keep him in view
//when upside down and behind, pull down

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (100);
			SetManoeuvreTime (1500);
 			ai.desiredroll = ANGLES_0Deg; 
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			ACM.SetRelAoA(ANGLES_4Deg);

			if  ( !ManoeuvreTimeLeft())
  				ai.manoeuvre = MANOEUVRE_SELECT;
			if (TargetOnSubjectTail(ANGLES_40Deg))
				ai.ManStep = PHASE2;
			break;

		}
		case PHASE2:
		{
			COORDS3D	target;
			Float fpitch,fhdg;
			AirStrucPtr	unfriendly = *ai.unfriendly;
			target = ai.unfriendly->World;

			SWord	reqdeltahdg,reqdeltahdg_sign;
			UWord	reqdeltahdg_pos;
			reqdeltahdg = 	hdg - HdgIntercept;
 			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

			ANGLES reqroll = roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
			ACM.Roll (reqroll);
			ACM.TurnRate(fpitch);

			if((reqdeltahdg_pos < ANGLES_50Deg) || (World.Y < unfriendly->World.Y))
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = PHASE0;
			}
		}
	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Scissors
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Scissors ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
 			ACM.Thrust (70);
			SetManoeuvreTime (1500);
 			ai.ManStep = PHASE1;
 			ai.desiredhdg = hdg - ANGLES_60Deg; 
 		}
 		case PHASE1:
 		{
 			if (!ManoeuvreTimeLeft())
 			{
 				ai.ManStep = PHASE3;
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg, ANGLES_5Deg))
 			{
 				ai.ManStep = PHASE2;
 				ai.desiredhdg = hdg + ANGLES_120Deg; 
 			}
 			break;
 		}
 		case PHASE2:
 		{
 			if (	(!ManoeuvreTimeLeft())
 				||	 (!(TargetFacingSubject(ANGLES_40Deg)))
 					||	(Range > COMBATRANGE)
 					)
 			{
 				ai.ManStep = PHASE3;
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg,ANGLES_5Deg))
 			{
 				ai.ManStep = PHASE1;
 				ai.desiredhdg = hdg - ANGLES_120Deg; 
 			}
 			break;
 		}
 		case PHASE3:
 		{
 
 			ai.manoeuvre = MANOEUVRE_SELECT;
 			break;
 		}
 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MildScissors
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::MildScissors ( )

{
	
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
 			ACM.Thrust (70);
			SetManoeuvreTime (1500);
 			ai.ManStep = PHASE1;
 			ai.desiredhdg = hdg - ANGLES_15Deg; 
 		}
 		case PHASE1:
 		{
 			if (!ManoeuvreTimeLeft())
 			{
 				ai.ManStep = PHASE3;
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg,ANGLES_5Deg))
 			{
 				ai.ManStep = PHASE2;
 				ai.desiredhdg = hdg + ANGLES_30Deg; 
 			}
 			break;
 		}
 		case PHASE2:
 		{
 			if (	(!ManoeuvreTimeLeft())
 				||	 (!(TargetFacingSubject(ANGLES_40Deg)))
 					||	(Range > COMBATRANGE)
 					)
 			{
 				ai.ManStep = PHASE3;
 			}
//DEADCODE RDH 21/02/99  			ACM.Pitch (ANGLES_5Deg);
 			if (MoveToDesiredHdg (ai.desiredhdg,ANGLES_5Deg,ANGLES_5Deg))
 			{
 				ai.ManStep = PHASE1;
 				ai.desiredhdg = hdg - ANGLES_30Deg; 
 			}
 			break;
 		}
 		case PHASE3:
 		{
 
 			ai.manoeuvre = MANOEUVRE_SELECT;
 			break;
 		}
 	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SplitS
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SplitS ()

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
 	SWord 	deltaroll;
 	UWord	deltaroll_pos;
 	SWord	deltaroll_sign;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	Float fpitch, fhdg;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			int groundlevel = Land_Scape.GetGroundLevel(this);
			if(World.Y - groundlevel < 150000)	//5000 ft
			{
				if(Math_Lib.rnd(1))
					ai.manoeuvre = MANOEUVRE_SCISSORS;
				else
 					ai.manoeuvre = MANOEUVRE_BREAKTURN;
				SetManoeuvreTime(0);
			}
			else
			{
				MOD.Rudder = 0;
				ACM.Thrust (ThrustfromFF());
				COORDS3D	target;
				target = unfriendly->World;
				ANGLES reqroll = (roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch,fhdg ));
				if (	(reqroll >> ANGLES_120Deg)
					&&	(reqroll << ANGLES_240Deg)
					)
					ai.desiredroll = reqroll;
				else
					ai.desiredroll = ANGLES_180Deg;
				SetManoeuvreTime (1000);

				ai.ManStep = PHASE1;
			}
		}
		case PHASE1:
		{

			ACM.FastRoll (ai.desiredroll);
			deltaroll = (SWord) (ai.desiredroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if  (		( roll >> ANGLES_90Deg)
					&&	(roll << ANGLES_270Deg)
					&&	(deltaroll_pos <ANGLES_30Deg)
				)
				ACM.LiftLimit();
			else
				ACM.SetElevator(0);

			if (deltaroll_pos <ANGLES_20Deg)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (1500);
			}
			break;
		}
 		case PHASE2:
		{
			MOD.Aileron = 0;
			ACM.LiftLimit();
			if  ( 		(!ManoeuvreTimeLeft())
					||  (		(DesiredPitchChk (ANGLES_315Deg,ANGLES_20Deg))
							&&	(		(roll << ANGLES_90Deg)
									||	(roll >> ANGLES_270Deg)
								)						
						)
				)
	 			{
 					ai.manoeuvre = MANOEUVRE_SELECT;
	 			}
	 			break;
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ZoomandDrop
//Author		R. Hyde 
//Date			Mon 18 Dec 1995
//
//Description	
//Zoom for only a few seconds in hope of gettig other a/c to slip under
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ZoomandDrop ()
{

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

//	ACM.Step = ai.ManStep;

		
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (500);
			MOD.Rudder = 0;
			ACM.Thrust (0);
			ACM.SpeedBrakesOut ();

			ai.ManStep = PHASE1;
		}

		case PHASE1:
		{
			ACM.KeepWingsLevel ();
			ACM.Pitch (ANGLES_40Deg);
			if(!ManoeuvreTimeLeft())
			{
				ACM.Clear ();
				ACM.Thrust (ThrustfromFF());
				ACM.SpeedBrakesIn ();
				SWord	reqdeltahdg,reqdeltahdg_sign;
				UWord	reqdeltahdg_pos;
				reqdeltahdg = 	hdg - HdgIntercept;
	 			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
				if (reqdeltahdg_pos < ANGLES_30Deg)
				{
					ai.ManStep = PHASE0;
					ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
				}
				else
				{
					SetManoeuvreTime (500);
					ai.ManStep = PHASE2;
				}
			}

			break;
		}


		case PHASE2:
		{
			ACM.Pitch (ANGLES_290Deg);
			ACM.KeepWingsLevel ();
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}

	}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StraightandLevel
//Author		Andrew McRae
//Date			Wed 14 May 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::StraightandLevel ()
{
//DEADCODE DAW 25/11/99 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE DAW 25/11/99 
//DEADCODE DAW 25/11/99 	switch (ai.ManStep)
//DEADCODE DAW 25/11/99 	{
//DEADCODE DAW 25/11/99 		case PHASE0:
//DEADCODE DAW 25/11/99 		{
//DEADCODE DAW 25/11/99 			SetManoeuvreTime (3000);
//DEADCODE DAW 25/11/99 			ACM.SetRudder(0);
//DEADCODE DAW 25/11/99 			ACM.Thrust(100);
//DEADCODE DAW 25/11/99 			ai.ManStep = PHASE1;
//DEADCODE DAW 25/11/99 		}
//DEADCODE DAW 25/11/99 		case PHASE1:
//DEADCODE DAW 25/11/99 		{
//DEADCODE DAW 25/11/99 			ACM.VelPitch(0);
//DEADCODE DAW 25/11/99 			ACM.FastRoll(0);
//DEADCODE DAW 25/11/99 			if(!TimeLeft())
//DEADCODE DAW 25/11/99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 25/11/99 			break;
//DEADCODE DAW 25/11/99 		}
//DEADCODE DAW 25/11/99 	}
//DEADCODE DAW 25/11/99 	return;


	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;


	UByte	FF = FlyingFactor();

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime (2000);
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			//this manoeuvre is only done by poor pilots so we can reduce speed so that
			//other can catch up and attack
				FP	Mach = MOD.Inst.I_MachNo;//CSB
			if (Mach < 0.5)
				ACM.Thrust (ThrustfromFF());
			else
				ACM.Thrust (0);

			if (FF > 160)
			{
				if (Mach > 0.9)
					Mach = 0.9;
				if (Mach < 0.3)
					Mach = 0.3;

				ANGLES desiredpitch;
				SWord deltapitch;
				deltapitch = ANGLES_5Deg * ((Mach - 0.3)/0.6);
				desiredpitch = (Angles)((SWord)ANGLES_355Deg + deltapitch);
				ACM.Pitch (desiredpitch);

			}else
				ACM.Pitch (ANGLES_1Deg);
			ACM.KeepWingsLevel ();
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpinOut
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SpinOut ( )

{
	SWord	deltaroll;
	UWord	deltayaw_pos;
	SWord	deltayaw_sign;

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (0);
			ACM.SetElevator(-MAXELEVATOR/2);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if (MOD.RotVel.y > 0)
			{
				MOD.Rudder = MAXRUDDER;
			}else
			{
				MOD.Rudder = -MAXRUDDER;
			}
			ai.ManStep = PHASE2;
			SetManoeuvreTime (2000);
			break;
		}
		case PHASE2:
		{
			ACM.SetElevator(-MAXELEVATOR);
			if (!ManoeuvreTimeLeft())
			{
				ai.ManStep = PHASE0;
				ACM.SetElevator(0);
				MOD.Rudder = 0;
				ai.manoeuvre = MANOEUVRE_SPINRECOVERY;

			}
			break;
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DiveforHome
//Author		Andrew McRae
//Date			Tue 3 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::DiveforHome ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			ACM.Thrust(100);
			ai.ManStep = PHASE1;
			InterceptandRange (&ai.homebase->World);
			ai.desiredhdg = HdgIntercept; 
			SetManoeuvreTime(1500);
		}
		case PHASE1:
		{
			if (World.Y < FT_1000)
				ACM.VelPitch(ANGLES_0Deg);
			else
				ACM.VelPitch(ANGLES_345Deg);
			SWord desroll = FindRequiredRoll(hdg - ai.desiredhdg, CombatReqBankData);
			ACM.FastRoll(desroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

//DeadCode CSB 5Sep00 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode CSB 5Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00  //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
//DeadCode CSB 5Sep00  	SLong	temp_range;
//DeadCode CSB 5Sep00  
//DeadCode CSB 5Sep00  	temp_range = Range; 	
//DeadCode CSB 5Sep00  	switch (ai.ManStep)
//DeadCode CSB 5Sep00  	{
//DeadCode CSB 5Sep00  		case PHASE0:
//DeadCode CSB 5Sep00  		{
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 			MOD.Rudder = 0;
//DeadCode CSB 5Sep00   			MoveToThrust (100);
//DeadCode CSB 5Sep00  			SetManoeuvreTime (2000);
//DeadCode CSB 5Sep00  			ai.ManStep = PHASE1;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 			ACM.Thrust (ThrustfromFF());
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 			if (ai.homebase)
//DeadCode CSB 5Sep00 				InterceptandRange (&ai.homebase->World);
//DeadCode CSB 5Sep00 			else
//DeadCode CSB 5Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00  			ai.desiredhdg = HdgIntercept; 
//DeadCode CSB 5Sep00  		}
//DeadCode CSB 5Sep00  		case PHASE1:
//DeadCode CSB 5Sep00  		{
//DeadCode CSB 5Sep00 //##			if (Range < MILES01)
//DeadCode CSB 5Sep00 //			{//within mile of home
//DeadCode CSB 5Sep00 //				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 //			}
//DeadCode CSB 5Sep00 //			Range = temp_range; 	
//DeadCode CSB 5Sep00 //			if (Range > BREAKOFFRANGE)
//DeadCode CSB 5Sep00 //			{//xx from action, reconsider
//DeadCode CSB 5Sep00 //				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 //			}
//DeadCode CSB 5Sep00 			if (Range < DANGERRANGE)
//DeadCode CSB 5Sep00 			{//xx from action, reconsider
//DeadCode CSB 5Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 			}
//DeadCode CSB 5Sep00 			if  (!ManoeuvreTimeLeft())
//DeadCode CSB 5Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 			ANGLES	desiredpitch;
//DeadCode CSB 5Sep00 			if (MOD.Pos.y < FT_3000)
//DeadCode CSB 5Sep00 				desiredpitch = ANGLES_0Deg;
//DeadCode CSB 5Sep00 			else
//DeadCode CSB 5Sep00 				desiredpitch = ANGLES_340Deg;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 			MoveToHdg (ai.desiredhdg, desiredpitch);
//DeadCode CSB 5Sep00  		}
//DeadCode CSB 5Sep00  	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GoHome
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::GoHome ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
 	SLong	temp_range;
 
 	temp_range = Range; 	
 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			MOD.Rudder = 0;
  			MoveToThrust (100);
 			SetManoeuvreTime (2000);
 			ai.ManStep = PHASE1;

			ACM.Thrust (ThrustfromFF());

			if (ai.homebase)
				InterceptandRange (&ai.homebase->World);
			else
				ai.manoeuvre = MANOEUVRE_SELECT;
 			ai.desiredhdg = HdgIntercept; 
			Range = temp_range;
 			if	(		TargetOnSubjectTail(ANGLES_10Deg)
 					&&	(Range < 2 * WEAPONSRANGE)
 					&&	(ai.combatskill >= SKILL_REGULAR)
 				)
 				ai.desiredhdg = HdgIntercept + ANGLES_20Deg; 

 		}
 		case PHASE1:
 		{
//##			if (Range < MILES01)
//			{//within mile of home
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
			Range = temp_range; 	
//			if (Range > BREAKOFFRANGE)
//			{//xx from action, reconsider
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			}
			if (Range < DANGERRANGE)
			{//xx from action, reconsider
				ai.manoeuvre = MANOEUVRE_SELECT;
			}
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;


				FP	Mach = MOD.Inst.I_MachNo;
				if (Mach > 0.9)
					Mach = 0.9;
				if (Mach < 0.3)
					Mach = 0.3;

				ANGLES desiredpitch;
				SWord deltapitch;
				deltapitch = ANGLES_5Deg * ((Mach - 0.3)/0.6);
				desiredpitch = (Angles)((SWord)ANGLES_355Deg + deltapitch);
//				ACM.Pitch (desiredpitch);

 			MoveToHdg (ai.desiredhdg, desiredpitch);
 		}
 	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeForFriendly
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::MakeForFriendly ( )

{
	
}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MoveAway
//Author		Andrew McRae
//Date			Mon 2 Jun 1997
//
//Description	
//	Not much different from extension. Ant need for both?
//
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::MoveAway ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime(500);
			ai.ManStep = PHASE1;
		}

		case PHASE1:
		{
			ACM.VelPitch(ANGLES_345Deg);
			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept + ANGLES_180Deg, CombatReqBankData);
			ACM.FastRoll(reqroll);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
//DEADCODE CSB 15/03/00 	switch (ai.ManStep)
//DEADCODE CSB 15/03/00 	{
//DEADCODE CSB 15/03/00 		case PHASE0:
//DEADCODE CSB 15/03/00 		{
//DEADCODE CSB 15/03/00 			MOD.Rudder = 0;
//DEADCODE CSB 15/03/00 			ACM.Thrust (ThrustfromFF());
//DEADCODE CSB 15/03/00 			SetManoeuvreTime (2000);
//DEADCODE CSB 15/03/00 			ai.ManStep = PHASE1;
//DEADCODE CSB 15/03/00 			break;
//DEADCODE CSB 15/03/00 		}
//DEADCODE CSB 15/03/00 		case PHASE1:
//DEADCODE CSB 15/03/00 		{
//DEADCODE CSB 15/03/00 //DEADCODE CSB 19/01/00 			ACM.MinHeight (FT_1000);
//DEADCODE CSB 15/03/00 //			ACM.Pitch (ANGLES_5Deg);
//DEADCODE CSB 15/03/00 			MoveToHdg (HdgIntercept + ANGLES_180Deg, ANGLES_5Deg);
//DEADCODE CSB 15/03/00  
//DEADCODE CSB 15/03/00 			if (!ManoeuvreTimeLeft())
//DEADCODE CSB 15/03/00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE CSB 15/03/00 			break;
//DEADCODE CSB 15/03/00 		}
//DEADCODE CSB 15/03/00 	}
//DEADCODE CSB 15/03/00 
}	


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HeadOnOffset
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::HeadOnOffset ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	
	COORDS3D	target;
	SWord c,s;
	SWord newhdg;
	UByte	FF; 
	SWord	reqdeltahdg;


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (2000);
			SWord dhdg = HdgIntercept - hdg;
			if ((dhdg) > 0)
				ai.desiredhdg = ANGLES_90Deg;
			else
				ai.desiredhdg = ANGLES_270Deg;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
//DEADCODE RDH 06/04/99 //			ANGLES bca = BestClimbAngle();
//DEADCODE RDH 06/04/99 //			if (PitchIntercept >> bca )
//DEADCODE RDH 06/04/99 //				ACM.Pitch (bca);
//DEADCODE RDH 06/04/99 //			else
//DEADCODE RDH 06/04/99 //			if (PitchIntercept >> pitch)
//DEADCODE RDH 06/04/99 			if  (	(		(PitchIntercept >> ANGLES_180Deg)
//DEADCODE RDH 06/04/99 						&&	(MOD.Elevator <= 0)
//DEADCODE RDH 06/04/99 					)
//DEADCODE RDH 06/04/99 					||
//DEADCODE RDH 06/04/99 					(
//DEADCODE RDH 06/04/99 							(PitchIntercept << ANGLES_180Deg)
//DEADCODE RDH 06/04/99 						&&	(MOD.Elevator > 0)
//DEADCODE RDH 06/04/99 					)
//DEADCODE RDH 06/04/99 					||		(		(roll >> ANGLES_40Deg)
//DEADCODE RDH 06/04/99 								&&	(roll << ANGLES_320Deg)
//DEADCODE RDH 06/04/99 							)
//DEADCODE RDH 06/04/99 				)
//DEADCODE RDH 06/04/99 			{
//DEADCODE RDH 06/04/99 				ACM.SetElevator(0);
//DEADCODE RDH 06/04/99 			}else
//DEADCODE RDH 06/04/99 				ACM.Pitch (PitchIntercept);
//DEADCODE RDH 06/04/99 //			else
//DEADCODE RDH 06/04/99 //				ACM.Pitch (pitch + ANGLES_3Deg);

			ANGLES bca = BestClimbAngle();
			if (PitchIntercept > bca )
				ACM.VelPitch (bca);
			else
				ACM.Pitch (PitchIntercept);




			ANGLES desiredhdg = ai.desiredhdg;
			ANGLES unfHdgIntercept = HdgIntercept;
			SLong	unfRange = Range;
			newhdg = unfriendly->hdg + ai.desiredhdg;

			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((BREAKTURNRADIUS * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((BREAKTURNRADIUS * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - desiredhdg;
		 	ANGLES reqroll = (Angles)FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			if  (		(reqroll >> ANGLES_30Deg)
					&&	(reqroll << ANGLES_180Deg)
				)
				reqroll = ANGLES_30Deg;
			if  (		(reqroll << ANGLES_330Deg)
					&&	(reqroll >> ANGLES_180Deg)
				)	
				reqroll = ANGLES_330Deg;

			ACM.Roll (reqroll);

			if (unfRange < Range)
				Range = unfRange;
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			if	(		(SubjectOnTargetTail(ANGLES_85Deg))
					||	(TargetOnSubjectTail(ANGLES_85Deg))
				)
			{
		  		ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						
			}else if (Range < (BREAKTURNRADIUS))
			{
				FF = Math_Lib.rnd(4);
				if (		(FF  < 2)
						&&	(		(unfriendly->roll >> ANGLES_30Deg)
								&&	(unfriendly->roll << ANGLES_330Deg)
							)
					)
				{//turn in
					reqdeltahdg = 	hdg - unfHdgIntercept;
					if (reqdeltahdg < 0)
					{
						ai.desiredroll = ANGLES_85Deg;
						ai.desiredhdg = ANGLES_90Deg + hdg;
					}else
					{
						ai.desiredhdg = ANGLES_270Deg + hdg;
						ai.desiredroll = ANGLES_275Deg;
					}
					ai.ManStep = PHASE2;
				}else
				{//wait
					ai.ManStep = PHASE3;
				}
			}
			break;
		}
		case PHASE2:
		{
			ACM.Roll (ai.desiredroll);
			ACM.ZeroSpecificPower();
//DeadCode RDH 25Nov98 			ACM.LiftLimit();
			if (ChkAtDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
			{
		  		ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						
			}
			break;
		}
		case PHASE3:
		{
//			if (PitchIntercept >> pitch)
				ACM.Pitch (PitchIntercept);
//			else
//				ACM.Pitch (pitch + ANGLES_3Deg);
			ANGLES desiredhdg = ai.desiredhdg;

			newhdg = unfriendly->hdg + ai.desiredhdg;
			Math_Lib.high_sin_cos((Angles)newhdg,s,c);
			target.X = unfriendly->World.X + ((BREAKTURNRADIUS * s) >> ANGLES_SHIFT);
			target.Y = unfriendly->World.Y;
			target.Z = unfriendly->World.Z + ((BREAKTURNRADIUS * c) >> ANGLES_SHIFT);
			InterceptandRange (&target);
			desiredhdg = HdgIntercept;

			SWord	reqdeltahdg = hdg - desiredhdg;
		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
			if  (		(reqroll >> ANGLES_30Deg)
					&&	(reqroll << ANGLES_180Deg)
				)
				reqroll = ANGLES_30Deg;
			if  (		(reqroll << ANGLES_330Deg)
					&&	(reqroll >> ANGLES_180Deg)
				)	
				reqroll = ANGLES_330Deg;

			ACM.Roll ((Angles)reqroll);

			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			else if	(		(SubjectOnTargetTail(ANGLES_80Deg))
					||	(TargetOnSubjectTail(ANGLES_80Deg))
				)
			{
				if  (		(unfriendly->roll << ANGLES_30Deg)
						||	(unfriendly->roll >> ANGLES_330Deg)
					)
				{
			  		ai.ManStep = PHASE0;
					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						

				}else 
				{
					if (		(roll >> ANGLES_30Deg)
							&&	(roll << ANGLES_180Deg)
						)
					{
						ai.desiredroll = ANGLES_85Deg;
						ai.desiredhdg = ANGLES_90Deg + hdg;
					}else if (	(roll << ANGLES_330Deg)
								&&	(roll >> ANGLES_180Deg)
							 )
					{
						ai.desiredhdg = ANGLES_270Deg + hdg;
						ai.desiredroll = ANGLES_275Deg;
					}else if ((hdg - HdgIntercept) < 0)
					{
						ai.desiredroll = ANGLES_85Deg;
						ai.desiredhdg = ANGLES_90Deg + hdg;
					}else
					{
						ai.desiredhdg = ANGLES_270Deg + hdg;
						ai.desiredroll = ANGLES_275Deg;
					}
					
//					if  (		(Math_Lib.rnd(3) == 0)
//						||	(Range > BREAKTURNRADIUS/2)
//					)
//					{
//						if  (		(unfriendly->roll << ANGLES_180Deg)
//								||	(roll >> ANGLES_20Deg)
//							)
//						{
//							ai.desiredroll = ANGLES_85Deg;
//							ai.desiredhdg = ANGLES_90Deg + hdg;
//						}else
//						{
//							ai.desiredhdg = ANGLES_270Deg + hdg;
//							ai.desiredroll = ANGLES_275Deg;
//						}
//					}else
//					{
//						if (	(unfriendly->roll >> ANGLES_180Deg)
//							||	(roll << ANGLES_340Deg)	
//							)
//						{
//							ai.desiredroll = ANGLES_85Deg;
//							ai.desiredhdg = ANGLES_90Deg + hdg;
//						}else
//						{
//							ai.desiredhdg = ANGLES_270Deg + hdg;
//							ai.desiredroll = ANGLES_275Deg;
//						}
//					}
			  		ai.ManStep = PHASE4;
				}
			}		
			break;

		}
		case PHASE4:
		{
			ACM.Roll (ai.desiredroll);
			ACM.ZeroSpecificPower();
//DeadCode RDH 25Nov98 			ACM.LiftLimit();
			if (ChkAtDesiredHdg (ai.desiredhdg,ANGLES_5Deg))
			{
		  		ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;						
			}

		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StayWithPrey
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	As target looses alt, stay until explosion or hits ground or alt <???
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::StayWithPrey ( )

{
	
//DeadCode RDH 26Mar98 	SWord	acroll_sign,reqroll;
//DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 26Mar98 	UWord	acroll_pos;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			if  (		(!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 					||	(World.Y < FT_700)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			TightTurn (FT_500);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 	}
//DeadCode RDH 26Mar98 

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Immelmann
//Author		R. Hyde 
//Date			Wed 13 Dec 1995
//
//Description	not used and so not coded for Flying Corps
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Immelmann ( )

{
	AirStrucPtr	unfriendly = *ai.unfriendly;

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

//	ACM.Step = ai.ManStep;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (100);
			SetManoeuvreTime (2000);
			if (		(MOD.Inst.I_MachNo != 0)		//really just for test purposes, first time in mchno is not set
					&&	(MOD.Inst.I_MachNo < 0.55)
				)
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
			}else
				ai.ManStep = PHASE1;
			break;
		}
		case PHASE1:
		{
			ACM.Pitch (ANGLES_355Deg);
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			if (MOD.Inst.I_MachNo > 0.6)
			{
				ai.desiredroll = ANGLES_0Deg;
				SetManoeuvreTime (1000);
				ai.ManStep = PHASE2;
			}
			break;
		}
		case PHASE2:
		{
			SWord 	deltaroll;
			UWord	deltaroll_pos;
		 	SWord	deltaroll_sign;
			ACM.Roll (ai.desiredroll);
 			deltaroll = (SWord) (ai.desiredroll - roll);
 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
 			if (deltaroll_pos <ANGLES_5Deg)
			{
				ai.ManStep = PHASE3;
				SetManoeuvreTime (1000);
				ai.desiredhdg = hdg;
			}
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE3:
		{
			ACM.LiftLimit();
			ACM.Roll (ANGLES_0Deg);
 			if  (	(roll >> ANGLES_90Deg)
				&&	(roll << ANGLES_270Deg)
				)
			{
				ai.ManStep = PHASE4;
				SetManoeuvreTime (1000);
			}
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE4:
		{
			SWord 	deltaroll;
			UWord	deltaroll_pos;
		 	SWord	deltaroll_sign;
			Float fpitch,fhdg;
			COORDS3D	target;
			target = ai.unfriendly->World;

			ANGLES reqroll = roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
			ACM.Roll (reqroll);

//DeadCode AMM 24Nov99 			int ele = MOD.Elevator + MOD.MODEL_DT * 3000;
			int ele = MOD.Elevator + MODEL_DT * 3000;			//AMM 24Nov99
			if (ele >0)
				ele = 0;
			ACM.SetElevator(ele);
			
			deltaroll = (SWord) (reqroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_5Deg)
			{
				ai.ManStep = PHASE5;
				SetManoeuvreTime (1000);
			}
			if (!ManoeuvreTimeLeft ())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE5:
		{
			ACM.KeepWingsLevel ();
			ACM.LiftLimit();
			if   (	(DesiredPitchChk (ANGLES_0Deg, ANGLES_10Deg))
				 ||	(!ManoeuvreTimeLeft ())
				 )
				ai.manoeuvre = MANOEUVRE_SELECT;

		}
	}



}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ImmelmannTurn
//Author		Craig Beeston
//Date			Mon 04 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::ImmelmannTurn()
{
	ACMMODEL& ACM = *fly.pAcmModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(100);
			ACM.SetRudder(0);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Pitch(ANGLES_90Deg);
			ACM.FastRoll(ANGLES_0Deg);
			if(pitch > ANGLES_60Deg)
				ai.ManStep = PHASE2;
			break;
		}
		case PHASE2:
		{
			ACM.Pitch(ANGLES_90Deg);
			
			SWord desroll = ANGLES_180Deg + SWord(hdg) - SWord(HdgIntercept);
			SWord deltaroll = desroll - roll;

			SWord deltahdg = HdgIntercept - hdg;
			if(deltaroll > 0)
				ACM.SetAileron(32767);
			else
				ACM.SetAileron(-32767);

			if((-deltaroll < ANGLES_10Deg) && (deltaroll < ANGLES_10Deg))
			{
				ai.ManStep = PHASE3;
				SetManoeuvreTime(256);
			}
			break;
		}
		case PHASE3:
		{
			ACM.FastRoll(ANGLES_180Deg);
			ACM.LiftLimit();
			if(SWord(pitch) < ANGLES_45Deg)
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = 0;
			}
			break;
		}
//DeadCode CSB 7Sep00 			ai.ManStep = PHASE4;
//DeadCode CSB 7Sep00 			break;
//DeadCode CSB 7Sep00 		}
//DeadCode CSB 7Sep00 		case PHASE4:
//DeadCode CSB 7Sep00 		{
//DeadCode CSB 7Sep00 			SWord deltahdg = HdgIntercept - hdg;
//DeadCode CSB 7Sep00 			if(deltahdg > 0)
//DeadCode CSB 7Sep00 				ACM.FastRoll(ANGLES_90Deg);
//DeadCode CSB 7Sep00 			else
//DeadCode CSB 7Sep00 				ACM.FastRoll(-ANGLES_90Deg);
//DeadCode CSB 7Sep00 			
//DeadCode CSB 7Sep00 			ACM.Pitch(PitchIntercept);
//DeadCode CSB 7Sep00 			SWord deltapitch = PitchIntercept - pitch;
//DeadCode CSB 7Sep00 			if((-deltapitch < ANGLES_5Deg) && (deltapitch < ANGLES_5Deg))
//DeadCode CSB 7Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 7Sep00 			break;
//DeadCode CSB 7Sep00 		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbforHome
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ClimbforHome ( )
{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch (ai.ManStep)
	{
		case PHASE0:
		{
 			ACM.Thrust(100);
			ai.ManStep = PHASE1;
			InterceptandRange (&ai.homebase->World);
			ai.desiredhdg = HdgIntercept; 
			SetManoeuvreTime(1500);
		}
		case PHASE1:
		{
			if(vel_ < classtype->bestclimbvel)
				ACM.VelPitch(ANGLES_0Deg);
			else
				ACM.VelPitch(ANGLES_15Deg);
			SWord desroll = FindRequiredRoll(hdg - ai.desiredhdg, CombatReqBankData);
			ACM.FastRoll(desroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

//DeadCode CSB 5Sep00 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode CSB 5Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00  //DeadCode RDH 20Aug96 	WayPointPtr	lastwaypoint;
//DeadCode CSB 5Sep00  	SLong	temp_range;
//DeadCode CSB 5Sep00  
//DeadCode CSB 5Sep00  	temp_range = Range; 	
//DeadCode CSB 5Sep00  	switch (ai.ManStep)
//DeadCode CSB 5Sep00  	{
//DeadCode CSB 5Sep00  		case PHASE0:
//DeadCode CSB 5Sep00  		{
//DeadCode CSB 5Sep00 			MOD.Rudder = 0;
//DeadCode CSB 5Sep00   			MoveToThrust (100);
//DeadCode CSB 5Sep00  			SetManoeuvreTime (2000);
//DeadCode CSB 5Sep00  			ai.ManStep = PHASE1;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 			ACM.Thrust (ThrustfromFF());
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00  			InterceptandRange (&ai.homebase->World);
//DeadCode CSB 5Sep00  			ai.desiredhdg = HdgIntercept; 
//DeadCode CSB 5Sep00  		}
//DeadCode CSB 5Sep00  		case PHASE1:
//DeadCode CSB 5Sep00  		{
//DeadCode CSB 5Sep00 //##			if (Range < MILES01)
//DeadCode CSB 5Sep00 //			{//within mile of home
//DeadCode CSB 5Sep00 //				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 //			}
//DeadCode CSB 5Sep00 			Range = temp_range; 	
//DeadCode CSB 5Sep00 //			if (Range > BREAKOFFRANGE)
//DeadCode CSB 5Sep00 //			{//xx from action, reconsider
//DeadCode CSB 5Sep00 //				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 //			}
//DeadCode CSB 5Sep00 			if (Range < DANGERRANGE)
//DeadCode CSB 5Sep00 			{//xx from action, reconsider
//DeadCode CSB 5Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 			}
//DeadCode CSB 5Sep00 			if  (!ManoeuvreTimeLeft())
//DeadCode CSB 5Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 
//DeadCode CSB 5Sep00 //			ACM.Pitch (BestClimbAngle());
//DeadCode CSB 5Sep00  			MoveToHdg (ai.desiredhdg, BestClimbAngle());
//DeadCode CSB 5Sep00  		}
//DeadCode CSB 5Sep00  	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StraightDive
//Author		Andrew McRae
//Date			Tue 3 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::StraightDive ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			SetManoeuvreTime (2000);
			ACM.Thrust (ThrustfromFF());

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.FastRoll (ANGLES_0Deg);
			ACM.Pitch (ANGLES_330Deg);
			if (MOD.Pos.y < FT_2000)
				ai.manoeuvre = MANOEUVRE_SELECT;
			if  (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}


}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StandOnTail
//Author		
//Date			Mon 8 Sep 1997
//
//Description	
//Zoom until low speed, then roll 180 and pull level
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::StandOnTail ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			SetManoeuvreTime (2000);	//800
			ACM.Thrust (100);

			ACM.ClimbRate (0);
			ACM.KeepWingsLevel ();
			ai.ManStep = PHASE1;
			break;
		}

		case PHASE1:
		{
			if (MOD.Speed > 200)
			{

				ACM.Clear ();
				ACM.Thrust (100);
//				ACM.StayVertical ();

				ai.ManStep = PHASE2;
			}
			break;
		}

		case PHASE2:
		{
 			if (!ManoeuvreTimeLeft())
 				ai.manoeuvre = MANOEUVRE_SELECT;

// 			if (ACM.pModel->Vel.y <= 0)
//				ai.manoeuvre = MANOEUVRE_SELECT;

			break;
		}
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShootToFrighten
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ShootToFrighten ( )

{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Clear ();
			SetManoeuvreTime (1000);
			ACM.maxdeltaforclosework = 0.0;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord	reqdeltahdg,reqdeltahdg_sign;
			UWord	reqdeltahdg_pos;
			COORDS3D	target;
			SLong		time;
			MODEL& MOD = *fly.pModel;
			AirStrucPtr	unfriendly = *ai.unfriendly;
		//DeadCode AMM 01Jul98 	MODEL& UNFMOD = *(unfriendly->fly).pModel;	


			reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

			if (		(Range < METRES400)
					&&	(reqdeltahdg_pos < (SWord)ANGLES_30Deg)
				)		
			{
				//this method just extrapolates position
				//to get turn:
				//get distance travelled and turn in time to work out offset
				time = Range / classtype->muzzlevel;		//MUZZELVEL;
				//calc lead position using this time
				target.X = ai.unfriendly->World.X + (unfriendly->vel_x * time ) / 1000;
				target.Y = ai.unfriendly->World.Y + (unfriendly->vel_y * time ) / 1000;
				target.Z = ai.unfriendly->World.Z + (unfriendly->vel_z * time ) / 1000;
				InterceptandRange (&target);
			}else
				target = ai.unfriendly->World;

			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
		//DeadCode RDH 16Dec98 	TurnFightSub(HdgIntercept, TRUE, ANGLES_5Deg,target);
			if (		(Range < ENGAGERANGE)
					&&	((unfriendly->vel_ - vel_) > 0)
					&&	(		(unfriendly->roll << ANGLES_10Deg)
							||	(unfriendly->roll >> ANGLES_350Deg)
						)
				)	
			{
						FireABullet(100);
						if	(	(		(unfriendly->ai.morale < MORALE_GOOD)
									||	(unfriendly->ai.combatskill < SKILL_VETERAN)
								)
								&&
								(ai.unfriendly != Persons2::PlayerGhostAC)
							)
						{
							unfriendly->ai.manoeuvre = MANOEUVRE_PANICTURN;
							unfriendly->ai.ManStep = PHASE0;
						}
			}


		}
	}



}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ShootTooEarly
//Author		R. Hyde 
//Date			Mon 30 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ShootTooEarly()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Clear ();
			SetManoeuvreTime (1000);
			ACM.maxdeltaforclosework = 0.0;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord	reqdeltahdg,reqdeltahdg_sign;
			UWord	reqdeltahdg_pos;
			COORDS3D	target;
			SLong		time;
			MODEL& MOD = *fly.pModel;
			AirStrucPtr	unfriendly = *ai.unfriendly;
		//DeadCode AMM 01Jul98 	MODEL& UNFMOD = *(unfriendly->fly).pModel;	

			target = ai.unfriendly->World;

			reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

			if((Range < METRES400) && (reqdeltahdg_pos < (SWord)ANGLES_30Deg))		
			{
				//this method just extrapolates position
				//to get turn:
				//get distance travelled and turn in time to work out offset
				time = (10000 * Range) / classtype->muzzlevel;		//MUZZELVEL;cs
				//calc lead position using this time
				target.X = ai.unfriendly->World.X + (unfriendly->vel_x * time ) / 10000;
				target.Y = ai.unfriendly->World.Y + (unfriendly->vel_y * time ) / 10000;
				target.Z = ai.unfriendly->World.Z + (unfriendly->vel_z * time ) / 10000;
				InterceptandRange (&target);
			}else
				target = ai.unfriendly->World;

			if((Range < ENGAGERANGE) && (vel_ > unfriendly->vel_))	
				FireABullet(100);

			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
		//DeadCode RDH 16Dec98 	TurnFightSub(HdgIntercept, TRUE, ANGLES_5Deg,target);
		}
	}

}

ANGLES	AirStruc::BestClimbAngle()
{
	SWord LocalBestClimbPitch = CalcBestClimbPitch();
	return(Angles(LocalBestClimbPitch));
//DEADCODE CB 16/11/99 	return(classtype->bestclimbpitch);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GainHeight
//Author		R. Hyde 
//Date			Tue 12 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::GainHeight ( )

{
	
	// ##Select Max power
	// and maintain best climb speed
	// fly flat if < bestclimb speed
	

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			SWord reqdeltahdg = 	hdg - HdgIntercept;
			ACM.Thrust (ThrustfromFF());
			SetManoeuvreTime (1500);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{

//##should attempt to get to side
			SWord reqpitch = CalcBestClimbPitch();
			SLong climbvel = CalcBestClimbSpeed();
			SLong deltapitch = (vel_ - climbvel) * 2.0 / 1000.0;
			MODLIMIT(deltapitch, reqpitch);
			reqpitch += deltapitch;
			ACM.VelPitch(reqpitch);

//DEADCODE CB 16/11/99 			ACM.Pitch (BestClimbAngle());
			InterceptandRange(ai.unfriendly);
			SWord	reqdeltahdg = HdgIntercept - hdg;
//DeadCode CSB 9Nov00 		 	SWord reqroll = FindRequiredRoll (reqdeltahdg,CombatReqBankData);
//DeadCode CSB 9Nov00 			//##skill factor
//DeadCode CSB 9Nov00 			if (reqroll > ANGLES_30Deg)
//DeadCode CSB 9Nov00 				reqroll = ANGLES_30Deg;
//DeadCode CSB 9Nov00 			if (reqroll < ANGLES_330Deg)
//DeadCode CSB 9Nov00 				reqroll = ANGLES_330Deg;
			if(reqdeltahdg > 0)
				ACM.FastRoll(ANGLES_30Deg);
			else
				ACM.FastRoll(ANGLES_330Deg);

			if  (		(!ManoeuvreTimeLeft())
//DeadCode CSB 9Nov00 					||	(		(Range < ENGAGERANGE)
//DeadCode CSB 9Nov00 							&&	SubjectFacingTarget(ANGLES_45Deg)
//DeadCode CSB 9Nov00 						)	
				)
				ai.manoeuvre = MANOEUVRE_SELECT;
			
			
			
			break;	
			
			
			
			
			
//			MOD.Rudder = 0;
//			SetManoeuvreTime (2000);
//			ACM.GearUp ();
//			UByte	FF = FlyingFactor();
//			SWord thrust = 85 + (FF * 15)/256;	
//			if (thrust > 95)
//				thrust = 100;
//			ACM.Thrust (thrust);
//			if (ai.combatskill > SKILL_REGULAR)
//			{
//				SWord	reqdeltahdg;
//				reqdeltahdg = 	hdg - HdgIntercept;
//				if (reqdeltahdg > 0)
//					ai.desiredhdg = HdgIntercept + ANGLES_20Deg;
//				else
//					ai.desiredhdg = HdgIntercept - ANGLES_20Deg;
//
//			}
//			else
//				ai.desiredhdg = HdgIntercept;
//
////			ACM.ClimbRate (-1500);
//			ai.ManStep = PHASE1;
		}
//		case PHASE1:
//		{
 //			MoveToHdg (ai.desiredhdg);
//			ACM.Pitch (BestClimbAngle());
////			if (MOD.Inst.MachNo < 0.4)
//			if (vel <= SustainedTurnSpeed())
//				ACM.Pitch (ANGLES_355Deg);
//			else
//				ACM.Pitch (ANGLES_5Deg);


//			if (!ManoeuvreTimeLeft())
//				ai.manoeuvre = MANOEUVRE_SELECT;
//			break;
//		}
	}

//DeadCode RDH 26Mar98 	AirStrucPtr		unfriendly;	
//DeadCode RDH 26Mar98 	SWord 	deltaroll;
//DeadCode RDH 26Mar98 	UWord	deltaroll_pos;
//DeadCode RDH 26Mar98 	SWord	deltaroll_sign,desiredaoa;
//DeadCode RDH 26Mar98 	
//DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			unfriendly = *ai.unfriendly;
//DeadCode RDH 26Mar98 			if (	(unfriendly->ai.attacker == this)
//DeadCode RDH 26Mar98 				||	(World.Y > classtype->fightceiling)
//DeadCode RDH 26Mar98 				)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre=MANOEUVRE_SUSTAINEDTURN;
//DeadCode RDH 26Mar98 				TurningFight ();
//DeadCode RDH 26Mar98 				break;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			SetManoeuvreTime (2000);
//DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 26Mar98 			if ((SWord) fly.turnrate > 0)
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 		 		ai.desiredroll = ANGLES_20Deg;
//DeadCode RDH 26Mar98 			}else
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 		 		ai.desiredroll = ANGLES_340Deg;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 13Jul96 			desiredaoa = ANGLES_7Deg;
//DeadCode RDH 26Mar98 //DeadCode RDH 13Jul96 			if (desiredaoa > (SWord)(STALL_ANGLE_MINUSONE - (fly.highest_aoa - fly.aoa)))
//DeadCode RDH 26Mar98 //DeadCode RDH 13Jul96 				desiredaoa = STALL_ANGLE_MINUSONE - (fly.highest_aoa - fly.aoa);
//DeadCode RDH 26Mar98 //DeadCode RDH 13Jul96 			MoveToAoA ((ANGLES) desiredaoa);
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_10Deg,6);
//DeadCode RDH 26Mar98 			MoveToRoll (ai.desiredroll,1);							//RDH 14May96
//DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 26Mar98 			}
//DeadCode RDH 26Mar98 			break;
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LagRoll
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Ref1.67..	
//				manoeuvre incorporates barrel roll attack(1.69..)
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::LagRoll()
{
//maintain throttle
//roll towards unfriendly for 10-20deg hdg (f(AOT))
//go upside down
//climb to loose speed to corner speed
//exit manoeuvre when unfriendly goes behind or time out

//treat the same as lagroll
	HighYoYo();

//DEADCODE DAW 31/03/99 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE DAW 31/03/99 	MODEL& MOD = *fly.pModel;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 	switch (ai.ManStep)
//DEADCODE DAW 31/03/99 	{
//DEADCODE DAW 31/03/99 		case PHASE0:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			ACM.Thrust (100);
//DEADCODE DAW 31/03/99 			SetManoeuvreTime (1500);
//DEADCODE DAW 31/03/99  			ai.desiredroll = ANGLES_0Deg; 
//DEADCODE DAW 31/03/99 			ai.ManStep = PHASE1;
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 		case PHASE1:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			ACM.Roll (ai.desiredroll);
//DEADCODE DAW 31/03/99 			ACM.SetRelAoA(ANGLES_4Deg);
//DEADCODE DAW 31/03/99 //			ACM.MinHeight (FT_2000);
//DEADCODE DAW 31/03/99 			if (TooLow())
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			if  (!ManoeuvreTimeLeft())
//DEADCODE DAW 31/03/99   				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 31/03/99 			if (TargetOnSubjectTail(ANGLES_90Deg))
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE2;
//DEADCODE DAW 31/03/99 			break;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 		case PHASE2:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			COORDS3D	target;
//DEADCODE DAW 31/03/99 			Float fpitch,fhdg;
//DEADCODE DAW 31/03/99 			AirStrucPtr	unfriendly = *ai.unfriendly;
//DEADCODE DAW 31/03/99 			target = ai.unfriendly->World;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			SWord	reqdeltahdg,reqdeltahdg_sign;
//DEADCODE DAW 31/03/99 			UWord	reqdeltahdg_pos;
//DEADCODE DAW 31/03/99 			reqdeltahdg = 	hdg - HdgIntercept;
//DEADCODE DAW 31/03/99  			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			ANGLES reqroll = roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
//DEADCODE DAW 31/03/99 			ACM.Roll (reqroll);
//DEADCODE DAW 31/03/99 			ACM.TurnRate(fpitch);
//DEADCODE DAW 31/03/99 			if (TooLow())
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_LOWALT;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 			if  (		(reqdeltahdg_pos < ANGLES_50Deg)
//DEADCODE DAW 31/03/99 					||	(World.Y < unfriendly->World.Y)
//DEADCODE DAW 31/03/99 				)
//DEADCODE DAW 31/03/99 			{
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
//DEADCODE DAW 31/03/99 				ai.ManStep = PHASE0;
//DEADCODE DAW 31/03/99 			}
//DEADCODE DAW 31/03/99 //			ACM.MinHeight (FT_2000);
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 	}
//DEADCODE DAW 31/03/99 

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExtensionManoeuvre
//Author		R. Hyde 
//Date			Thu 5 Mar 1998
//
//Description	1.23
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ExtensionManoeuvre()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL&    MOD = *fly.pModel;

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust(100);
			ai.desiredroll = roll;
			ai.desiredpitch = -PitchIntercept;
			SetManoeuvreTime(500);
			ai.ManStep = PHASE1;
		}

		case PHASE1:
		{
			SLong desroll = (ai.desiredroll * manoeuvretime) / 500;
			ACM.FastRoll(desroll);
			ACM.VelPitch(ai.desiredpitch);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

//DEADCODE CSB 15/03/00 //attempt to get to extend range to ENGAGERANGE safely
//DEADCODE CSB 15/03/00 //this is to try to escape
//DEADCODE CSB 15/03/00 //or get distance to try again
//DEADCODE CSB 15/03/00 //if at same level
//DEADCODE CSB 15/03/00 //	good mig pilots should go up
//DEADCODE CSB 15/03/00 //	good us pilots should go down
//DEADCODE CSB 15/03/00 //if higher than bogey
//DEADCODE CSB 15/03/00 //	
//DEADCODE CSB 15/03/00 //
//DEADCODE CSB 15/03/00 //ref1.70
//DEADCODE CSB 15/03/00 //## if turning good pilots will initially unload and
//DEADCODE CSB 15/03/00 //retain roll to disguise manoeuvre 
//DEADCODE CSB 15/03/00 //
//DEADCODE CSB 15/03/00 //initially aircraft could be closing
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE CSB 15/03/00 	MODEL& MOD = *fly.pModel;
//DEADCODE CSB 15/03/00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 	switch (ai.ManStep)
//DEADCODE CSB 15/03/00 	{
//DEADCODE CSB 15/03/00 		case PHASE0:
//DEADCODE CSB 15/03/00 		{
//DEADCODE CSB 15/03/00 			MOD.Rudder = 0;
//DEADCODE CSB 15/03/00 			ACM.Thrust (ThrustfromFF());
//DEADCODE CSB 15/03/00 			if ( (World.Y - ai.unfriendly->World.Y) > FT_1000)
//DEADCODE CSB 15/03/00 			{//above him
//DEADCODE CSB 15/03/00 				ai.desiredpitch = ANGLES_0Deg;
//DEADCODE CSB 15/03/00 			}else if ( (ai.unfriendly->World.Y - World.Y) > FT_1000)
//DEADCODE CSB 15/03/00 			{//below him
//DEADCODE CSB 15/03/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 15/03/00 //DEADCODE RDH 10/05/99 				if (classtype->visible == MIG15)
//DEADCODE CSB 15/03/00 					ai.desiredpitch = ANGLES_0Deg;
//DEADCODE CSB 15/03/00 				else
//DEADCODE CSB 15/03/00 					ai.desiredpitch = ANGLES_350Deg;
//DEADCODE CSB 15/03/00 			}else
//DEADCODE CSB 15/03/00 			{
//DEADCODE CSB 15/03/00 				if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 15/03/00 //DEADCODE RDH 10/05/99 				if (classtype->visible == MIG15)
//DEADCODE CSB 15/03/00 					ai.desiredpitch = ANGLES_10Deg;
//DEADCODE CSB 15/03/00 				else
//DEADCODE CSB 15/03/00 					ai.desiredpitch = ANGLES_350Deg;
//DEADCODE CSB 15/03/00 			}
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 			SetManoeuvreTime (2000);
//DEADCODE CSB 15/03/00 			ai.ManStep = PHASE1;
//DEADCODE CSB 15/03/00 			break;
//DEADCODE CSB 15/03/00 		}
//DEADCODE CSB 15/03/00 		case PHASE1:
//DEADCODE CSB 15/03/00 		{
//DEADCODE CSB 15/03/00 			ACM.MinHeight (FT_1000);
//DEADCODE CSB 15/03/00 			MoveToHdg (HdgIntercept + ANGLES_180Deg,ai.desiredpitch);
//DEADCODE CSB 15/03/00  			if  (		(Range > ENGAGERANGE)
//DEADCODE CSB 15/03/00 					||	(!ManoeuvreTimeLeft())
//DEADCODE CSB 15/03/00 				)
//DEADCODE CSB 15/03/00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE CSB 15/03/00 			break;
//DEADCODE CSB 15/03/00 		}
//DEADCODE CSB 15/03/00 	}
//DEADCODE CSB 15/03/00 
//DEADCODE CSB 15/03/00 
}


void	ACMAirStruc::DivingSpin()
{
	ACMMODEL& ACM = *fly.pAcmModel;

	switch(ai.ManStep)
	{
		case 0:
		{
			ACM.Thrust(100);
			ACM.SetRudder(0);
			ai.ManStep = 1;
			SetManoeuvreTime(1000);
		}
		case 1:
		{
			SWord deltapitch = pitch - ANGLES_345Deg;
			SWord desroll = ANGLES_90Deg - deltapitch;
			if(SWord(roll) < 0)
				desroll *= -1;
			ACM.FastRoll(desroll);
			ACM.LiftLimit();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
	
//DeadCode CSB 4Sep00 		ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode CSB 4Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode CSB 4Sep00  	SWord 	deltaroll;
//DeadCode CSB 4Sep00  	UWord	deltaroll_pos;
//DeadCode CSB 4Sep00  	SWord	deltaroll_sign;
//DeadCode CSB 4Sep00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 4Sep00 	Float fpitch, fhdg;
//DeadCode CSB 4Sep00 	UByte	FF = FlyingFactor();
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 	switch (ai.ManStep)
//DeadCode CSB 4Sep00 	{
//DeadCode CSB 4Sep00 		case PHASE0:
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			MOD.Rudder = 0;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			
//DeadCode CSB 4Sep00 			ACM.Thrust (ThrustfromFF());
//DeadCode CSB 4Sep00 			COORDS3D	target;
//DeadCode CSB 4Sep00 			target = unfriendly->World;
//DeadCode CSB 4Sep00 			ANGLES reqroll = (roll + GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch,fhdg ));
//DeadCode CSB 4Sep00 			if (	(reqroll >> ANGLES_120Deg)
//DeadCode CSB 4Sep00 				&&	(reqroll << ANGLES_240Deg)
//DeadCode CSB 4Sep00 				)
//DeadCode CSB 4Sep00 				ai.desiredroll = reqroll;
//DeadCode CSB 4Sep00 			else
//DeadCode CSB 4Sep00 				ai.desiredroll = ANGLES_180Deg;
//DeadCode CSB 4Sep00 			SetManoeuvreTime (1000);
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 		case PHASE1:
//DeadCode CSB 4Sep00 		{ //get upside down or therabouts
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			ACM.FastRoll (ai.desiredroll);
//DeadCode CSB 4Sep00 			deltaroll = (SWord) (ai.desiredroll - roll);
//DeadCode CSB 4Sep00 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode CSB 4Sep00 			if  (		( roll >> ANGLES_90Deg)
//DeadCode CSB 4Sep00 					&&	(roll << ANGLES_270Deg)
//DeadCode CSB 4Sep00 					&&	(deltaroll_pos <ANGLES_30Deg)
//DeadCode CSB 4Sep00 				)
//DeadCode CSB 4Sep00 				ACM.LiftLimit();
//DeadCode CSB 4Sep00 			else
//DeadCode CSB 4Sep00 				ACM.Pitch (ANGLES_0Deg);
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			if (deltaroll_pos <ANGLES_20Deg)
//DeadCode CSB 4Sep00 			{
//DeadCode CSB 4Sep00 				if (deltaroll >= 0 )
//DeadCode CSB 4Sep00 					ai.desiredroll = (Angles)1;
//DeadCode CSB 4Sep00 				else
//DeadCode CSB 4Sep00 					ai.desiredroll = (Angles)-1;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 				ai.ManStep = PHASE2;
//DeadCode CSB 4Sep00 				SetManoeuvreTime (1000);
//DeadCode CSB 4Sep00 			}
//DeadCode CSB 4Sep00 			break;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00  		case PHASE2:
//DeadCode CSB 4Sep00 		{// pull and roll until pointing down
//DeadCode CSB 4Sep00 			ACM.LiftLimit();
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			if ((SWord)ai.desiredroll >= 0)
//DeadCode CSB 4Sep00 				ACM.SetAileron(ACM.MaxAileron * FP(FF) / 256.0);		//deg/cs gets converted to rad/cs
//DeadCode CSB 4Sep00 //DEADCODE CSB 26/01/00 				ACM.RollRate (400 * FF/256);		//deg/cs gets converted to rad/cs
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			else
//DeadCode CSB 4Sep00 				ACM.SetAileron(-ACM.MaxAileron * FP(FF) / 256.0);		//deg/cs gets converted to rad/cs
//DeadCode CSB 4Sep00 //DEADCODE CSB 26/01/00 				ACM.RollRate (-400 * FF/256);
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			if( (!ManoeuvreTimeLeft()) || (DesiredPitchChk (ANGLES_270Deg,ANGLES_45Deg)) )
//DeadCode CSB 4Sep00 	 			{
//DeadCode CSB 4Sep00 					SetManoeuvreTime (1000);
//DeadCode CSB 4Sep00 					ai.ManStep = PHASE3;
//DeadCode CSB 4Sep00  	 			}
//DeadCode CSB 4Sep00 	 			break;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00  		case PHASE3:
//DeadCode CSB 4Sep00 		{//pull and roll until clear or time up
//DeadCode CSB 4Sep00 			ACM.LiftLimit();
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			if ((SWord)ai.desiredroll >= 0)
//DeadCode CSB 4Sep00 				ACM.SetAileron(ACM.MaxAileron * FP(FF) / 256.0);		//deg/cs gets converted to rad/cs
//DeadCode CSB 4Sep00 //DEADCODE CSB 26/01/00 				ACM.RollRate (400 * FF/256);		//rad/cs
//DeadCode CSB 4Sep00 			else
//DeadCode CSB 4Sep00 				ACM.SetAileron(-ACM.MaxAileron * FP(FF) / 256.0);		//deg/cs gets converted to rad/cs
//DeadCode CSB 4Sep00 //DEADCODE CSB 26/01/00 				ACM.RollRate (-400 * FF/256);
//DeadCode CSB 4Sep00 			
//DeadCode CSB 4Sep00 			if((!ManoeuvreTimeLeft()) || (Range > ENGAGERANGE))
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00  			break;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 	}
//DeadCode CSB 4Sep00 
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReverseTurn
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
void	ACMAirStruc::ReverseTurn()
{
//	DesiredRoll = opposite of existing
//	Move to desired and hold for 3 secs
//	if (good)
//		out of plane
//	Close brakes if open at end of manoeuvre(used in selfasbait())
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust(100);
			ACM.SetElevator(0);

			ai.desiredroll = ANGLES_85Deg;
			if(roll > 0)
				ai.desiredroll = -ai.desiredroll; 

			ai.ManStep = PHASE1;
			SetManoeuvreTime(500);
		}
		case PHASE1:
		{
			ACM.FastRoll (ai.desiredroll);
			SWord dRoll = SWord(roll) - SWord(ai.desiredroll);
			if((dRoll < ANGLES_10Deg) && (-dRoll < ANGLES_10Deg))
				ACM.LiftLimit();

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SelfAsBait
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	Ref19
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SelfAsBait()
{
//
//this could be where bandit is on your tail, wait for him to get close 
//before turning
//keep buddy in combat spread so that you can sandwich him

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	SWord	reqdeltahdg;
	reqdeltahdg = 	hdg - HdgIntercept;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (50);
			SetManoeuvreTime (1500);
			if (roll << ANGLES_90Deg)
				ai.desiredroll = ANGLES_30Deg;
			else
				ai.desiredroll = ANGLES_330Deg;

			ai.ManStep = PHASE1;

		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			if (ChkAtDesiredRoll(ai.desiredroll, ANGLES_5Deg))
				ACM.Pitch (ANGLES_10Deg);
			ACM.MinHeight (FT_2000);

			if  (		(Range < WEAPONSRANGE)
					||	(!ManoeuvreTimeLeft())
				)
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = PHASE0;
			}


		}
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Jink
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
void	ACMAirStruc::Jink()
{
//
//fast 90 deg roll
//hard push or pull on stick
//hold for 2-3 secs
//
//flyingability determines rollrate and stick push pull
//combatablity determines length of manoeuvre
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
 			SetManoeuvreTime (500);
 			ai.desiredhdg = (Angles)(1 + Math_Lib.rnd(2));
 			ai.ManStep = PHASE1;
 			if (MOD.Aileron >= 0)
			{
				ai.desiredroll = ANGLES_90Deg;
				ACM.SetAileron(32767);
			}
			else
			{
				ai.desiredroll = ANGLES_270Deg;
 				ACM.SetAileron(-32767);
			}
 		}
 		case PHASE1:
 		{
			SWord 	deltaroll;
			UWord	deltaroll_pos;
		 	SWord	deltaroll_sign;

			deltaroll = (SWord) (ai.desiredroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_10Deg)
				ACM.LiftLimit();
//DeadCode CSB 21/03/99				ACM.Roll(ai.desiredroll);
			ACM.FastRoll(ai.desiredroll);	//CSB 21/03/99	
 			if (!ManoeuvreTimeLeft())
 			{
				ai.desiredhdg--;
				if (((SWord)ai.desiredhdg) <0)
 					ai.manoeuvre = MANOEUVRE_SELECT;
				else
				{
					if (Math_Lib.rnd(2) == 0)
						ai.desiredroll = (Angles)(ANGLES_50Deg + Math_Lib.rnd((SWord)(ANGLES_45Deg)));
					else	
						ai.desiredroll = (Angles)(ANGLES_260Deg+ Math_Lib.rnd((SWord)(ANGLES_45Deg)));
		 			SetManoeuvreTime (200 + Math_Lib.rnd(300));
				}
 			}
 			break;
 		}
 	}


}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakTurn
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	
//				Maximum performance turn towards unfriendly
//				Aim for corner speed (see summary at top of acmman.cpp)
//				When quoted as IAS, corner speed is practically a constant
//				cornerspeed should be part of the planetype
//				corner speed occurs at max g allowed for ac
//				max g should be part of the planetype 
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::BreakTurn()
{
//	roll = cos -1 (1/maxg)
//ability to reach roll = f(flyingskill)
//ability to hold corner vel = f(flyingskill)
//	option to nose down to keep speed up and nose up to reduce speed
//hold for 4-5 secs
//
//low morale gives a very lazy turn
//
	SWord	reqdeltahdg;
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	reqdeltahdg = 	hdg - HdgIntercept;


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());

			SetManoeuvreTime (200);
			RndVal	rndnum = Math_Lib.rnd();
			if (FlyingFactor() > 120)
			{
				if (reqdeltahdg < 0)
					ai.desiredroll = ANGLES_85Deg;
				else
					ai.desiredroll = ANGLES_275Deg;
			}else
			{
				if (rndnum > RND50PC)
					ai.desiredroll = ANGLES_60Deg;
				else
					ai.desiredroll = ANGLES_300Deg;
			}
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{

			ACM.FastRoll (ai.desiredroll);

		 	SWord 	deltaroll;
		 	UWord	deltaroll_pos;
		 	SWord	deltaroll_sign;
 			deltaroll = (SWord) (ai.desiredroll - roll);
 			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
 			if (deltaroll_pos <ANGLES_5Deg)
				ACM.LiftLimit();

			if(!ManoeuvreTimeLeft())
//DEADCODE RJS 5/3/00 				if((classtype->phrasename == OLDPHRASE_MIGS) && (fly.cpitch >> ANGLES_180Deg))
//DEADCODE RJS 5/3/00 				{
//DEADCODE RJS 5/3/00 					ai.ManStep = PHASE2;
//DEADCODE RJS 5/3/00 					SetManoeuvreTime (600);
//DEADCODE RJS 5/3/00 				}
//DEADCODE RJS 5/3/00 				else
					ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}

		case PHASE2:
		{
			COORDS3D	target = ai.unfriendly->World;
			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
			if  (		(!ManoeuvreTimeLeft())
				)
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LazyTurn
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
void	ACMAirStruc::LazyTurn()
{
//
//	Choose a roll 10-40deg
//		= f(morale)
//	continue on turn for 20s
//	if (ai.morale > MORALE_GOOD)
//		if (Range < WEAPONS)
//			end manoeuvre
//
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (80);

			SetManoeuvreTime (2000);
   			RndVal	rndnum = Math_Lib.rnd();
			if (rndnum > RND50PC)
				ai.desiredroll = ANGLES_60Deg;
			else
				ai.desiredroll = ANGLES_300Deg;

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			SWord pitch = PitchIntercept;
			if (pitch > ANGLES_10Deg)
				pitch = ANGLES_10Deg;
			if (pitch < ANGLES_2Deg)
				pitch = ANGLES_2Deg;
			ACM.Pitch (pitch);
			ACM.MinHeight (FT_2000);
			if((!ManoeuvreTimeLeft()) || ((Range < WEAPONSRANGE) && (ai.morale > MORALE_GOOD)) )
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Break180
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.26
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Break180()
{
//roll 180
//pull hard until pitch 45 deg down
//slowly unroll for x secs
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
 	SWord 	deltaroll;
 	UWord	deltaroll_pos;
 	SWord	deltaroll_sign;
	AirStrucPtr	unfriendly = *ai.unfriendly;


	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			ACM.Thrust (ThrustfromFF());
			ai.desiredroll = ANGLES_180Deg;
			SetManoeuvreTime (1000);

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{

			ACM.FastRoll (ai.desiredroll);
			deltaroll = (SWord) (ai.desiredroll - roll);
			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
			if (deltaroll_pos <ANGLES_10Deg)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime (1500);
			}
			break;
		}
 		case PHASE2:
		{
			MOD.Aileron = 0;
			ACM.LiftLimit();
			if  ( 		(!ManoeuvreTimeLeft())
					||  (		(DesiredPitchChk (ANGLES_270Deg,ANGLES_10Deg))
						)
				)
	 			{
 					ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
					ai.ManStep = PHASE0;
	 			}
	 			break;
		}
	}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakLow
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
void	ACMAirStruc::BreakLow()
{
	ACMMODEL& ACM = *fly.pAcmModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			ACM.SetRudder(0);
 			MoveToThrust(100);
			if(SWord(HdgIntercept - hdg) > 0)
				ai.desiredroll = ANGLES_135Deg;
			else
				ai.desiredroll = ANGLES_225Deg;
			ai.ManStep = PHASE1;
			SetManoeuvreTime(500);
 			break;	
 		}
 		case PHASE1:
 		{	
			ACM.FastRoll(ai.desiredroll);
 			ACM.LiftLimit();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
//DeadCode CSB 4Sep00 //decide which way to roll to go down
//DeadCode CSB 4Sep00 //roll 90
//DeadCode CSB 4Sep00 //pull hard until pitch 45 deg down
//DeadCode CSB 4Sep00  	SWord 	deltaroll;
//DeadCode CSB 4Sep00  	UWord	deltaroll_pos;
//DeadCode CSB 4Sep00  	SWord	deltaroll_sign;
//DeadCode CSB 4Sep00  	MODEL& MOD = *fly.pModel;
//DeadCode CSB 4Sep00 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode CSB 4Sep00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00  	switch (ai.ManStep)
//DeadCode CSB 4Sep00  	{
//DeadCode CSB 4Sep00  		case PHASE0:
//DeadCode CSB 4Sep00  		{
//DeadCode CSB 4Sep00 			MOD.Rudder = 0;
//DeadCode CSB 4Sep00  			MoveToThrust (100);
//DeadCode CSB 4Sep00 			if ((hdg - HdgIntercept) > 0)
//DeadCode CSB 4Sep00 					ai.desiredroll = ANGLES_225Deg;
//DeadCode CSB 4Sep00 				else
//DeadCode CSB 4Sep00 					ai.desiredroll = ANGLES_135Deg;
//DeadCode CSB 4Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 4Sep00  			break;	
//DeadCode CSB 4Sep00  		}
//DeadCode CSB 4Sep00  		case PHASE1:
//DeadCode CSB 4Sep00  		{	
//DeadCode CSB 4Sep00 			ACM.FastRoll (ai.desiredroll);
//DeadCode CSB 4Sep00  			ACM.LiftLimit();
//DeadCode CSB 4Sep00 			UByte	FF = FlyingFactor();
//DeadCode CSB 4Sep00 			FP aoa0 = AngleSign (MOD.MainPlaneList->aoa[0][0]) + AngleSign (MOD.MainPlaneList->aoa[0][1]);
//DeadCode CSB 4Sep00 			FP aoa1 = AngleSign (MOD.MainPlaneList->aoa[1][0]) + AngleSign (MOD.MainPlaneList->aoa[1][1]);
//DeadCode CSB 4Sep00 			aoa0 *= 0.5;
//DeadCode CSB 4Sep00 			aoa1 *= 0.5;
//DeadCode CSB 4Sep00 			FP maxaoa = MOD.MainPlaneList->AoaMax - 	((256 - FF) * 0.174)/256;	//* 10 degs
//DeadCode CSB 4Sep00 			if (	(aoa0 > maxaoa)
//DeadCode CSB 4Sep00 				||	(aoa1 > maxaoa)
//DeadCode CSB 4Sep00 				)
//DeadCode CSB 4Sep00  				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00  			deltaroll = (SWord) (ai.desiredroll - roll);
//DeadCode CSB 4Sep00  			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode CSB 4Sep00  			if (deltaroll_pos <ANGLES_5Deg)
//DeadCode CSB 4Sep00 			{
//DeadCode CSB 4Sep00 				ai.ManStep = PHASE2;
//DeadCode CSB 4Sep00 				SetManoeuvreTime (1000);
//DeadCode CSB 4Sep00 			}
//DeadCode CSB 4Sep00 			break;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 		case PHASE2:
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			ACM.LiftLimit();
//DeadCode CSB 4Sep00  			if  (	(	(roll >> ANGLES_90Deg)
//DeadCode CSB 4Sep00 					&&	(roll << ANGLES_270Deg)
//DeadCode CSB 4Sep00 					)
//DeadCode CSB 4Sep00 //DeadCode CSB 01/12/99						||
//DeadCode CSB 4Sep00 //DeadCode CSB 01/12/99						(MOD.Inst.MachNo < 0.35)
//DeadCode CSB 4Sep00 				)
//DeadCode CSB 4Sep00 			{
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00 			}
//DeadCode CSB 4Sep00 			if (!ManoeuvreTimeLeft ())
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			break;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00  	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakHigh
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
void	ACMAirStruc::BreakHigh()
{
	ACMMODEL& ACM = *fly.pAcmModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			ACM.SetRudder(0);
 			MoveToThrust(100);
			if(SWord(HdgIntercept - hdg) > 0)
				ai.desiredroll = ANGLES_45Deg;
			else
				ai.desiredroll = ANGLES_315Deg;
			ai.ManStep = PHASE1;
			SetManoeuvreTime(500);
 			break;	
 		}
 		case PHASE1:
 		{	
			ACM.FastRoll(ai.desiredroll);
 			ACM.LiftLimit();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
	 
//DeadCode CSB 4Sep00 //decide which way to roll to go up
//DeadCode CSB 4Sep00 //roll 90
//DeadCode CSB 4Sep00 //pull hard until pitch 45 deg up
//DeadCode CSB 4Sep00  	SWord 	deltaroll;
//DeadCode CSB 4Sep00  	UWord	deltaroll_pos;
//DeadCode CSB 4Sep00  	SWord	deltaroll_sign;
//DeadCode CSB 4Sep00  	MODEL& MOD = *fly.pModel;
//DeadCode CSB 4Sep00 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode CSB 4Sep00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00  	switch (ai.ManStep)
//DeadCode CSB 4Sep00  	{
//DeadCode CSB 4Sep00  		case PHASE0:
//DeadCode CSB 4Sep00  		{
//DeadCode CSB 4Sep00 			MOD.Rudder = 0;
//DeadCode CSB 4Sep00  			MoveToThrust (100);
//DeadCode CSB 4Sep00 			if ((hdg - HdgIntercept) > 0)
//DeadCode CSB 4Sep00 					ai.desiredroll = ANGLES_315Deg;
//DeadCode CSB 4Sep00 				else
//DeadCode CSB 4Sep00 					ai.desiredroll = ANGLES_45Deg;
//DeadCode CSB 4Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 4Sep00  			break;	
//DeadCode CSB 4Sep00  		}
//DeadCode CSB 4Sep00  		case PHASE1:
//DeadCode CSB 4Sep00  		{	
//DeadCode CSB 4Sep00 			ACM.FastRoll (ai.desiredroll);
//DeadCode CSB 4Sep00  			ACM.LiftLimit();
//DeadCode CSB 4Sep00 			UByte	FF = FlyingFactor();
//DeadCode CSB 4Sep00 			FP aoa0 = AngleSign (MOD.MainPlaneList->aoa[0][0]) + AngleSign (MOD.MainPlaneList->aoa[0][1]);
//DeadCode CSB 4Sep00 			FP aoa1 = AngleSign (MOD.MainPlaneList->aoa[1][0]) + AngleSign (MOD.MainPlaneList->aoa[1][1]);
//DeadCode CSB 4Sep00 			aoa0 *= 0.5;
//DeadCode CSB 4Sep00 			aoa1 *= 0.5;
//DeadCode CSB 4Sep00 			FP maxaoa = MOD.MainPlaneList->AoaMax - 	((256 - FF) * 0.174)/256;	//* 10 degs
//DeadCode CSB 4Sep00 			if (	(aoa0 > maxaoa)
//DeadCode CSB 4Sep00 				||	(aoa1 > maxaoa)
//DeadCode CSB 4Sep00 				)
//DeadCode CSB 4Sep00  				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00  			deltaroll = (SWord) (ai.desiredroll - roll);
//DeadCode CSB 4Sep00  			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
//DeadCode CSB 4Sep00  			if (deltaroll_pos <ANGLES_5Deg)
//DeadCode CSB 4Sep00 			{
//DeadCode CSB 4Sep00 				ai.ManStep = PHASE2;
//DeadCode CSB 4Sep00 				SetManoeuvreTime (1000);
//DeadCode CSB 4Sep00 			}
//DeadCode CSB 4Sep00 			break;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 		case PHASE2:
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			ACM.LiftLimit();
//DeadCode CSB 4Sep00  			if  (	(	(roll >> ANGLES_90Deg)
//DeadCode CSB 4Sep00 					&&	(roll << ANGLES_270Deg)
//DeadCode CSB 4Sep00 					)
//DeadCode CSB 4Sep00 					||
//DeadCode CSB 4Sep00 					(MOD.Inst.I_MachNo < 0.35)
//DeadCode CSB 4Sep00 				)
//DeadCode CSB 4Sep00 			{
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00 			}
//DeadCode CSB 4Sep00 			if (!ManoeuvreTimeLeft ())
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			break;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00  	}
//DeadCode CSB 4Sep00 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Break90
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.27
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Break90()
{
	ACMMODEL& ACM = *fly.pAcmModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
			ACM.SetRudder(0);
 			MoveToThrust(100);
			if(SWord(HdgIntercept - hdg) > 0)
				ai.desiredroll = ANGLES_90Deg;
			else
				ai.desiredroll = ANGLES_270Deg;
			ai.ManStep = PHASE1;
			SetManoeuvreTime(500);
 			break;	
 		}
 		case PHASE1:
 		{	
			ACM.FastRoll(ai.desiredroll);
 			ACM.LiftLimit();
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
	 
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 //DEADCODE CSB 04/05/00 	if (classtype->phrasename == OLDPHRASE_MIGS)
//DeadCode CSB 4Sep00 //DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 	if (classtype->visible == MIG15)
//DeadCode CSB 4Sep00 //DEADCODE CSB 04/05/00 		BreakHigh();
//DeadCode CSB 4Sep00 //DEADCODE CSB 04/05/00 	else 
//DeadCode CSB 4Sep00 		if (	(ai.morale > MORALE_MEDIUM)
//DeadCode CSB 4Sep00 			&&	(ClosureLessThan(MPH50))
//DeadCode CSB 4Sep00 			)
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_BREAKHIGH;
//DeadCode CSB 4Sep00 				BreakHigh();
//DeadCode CSB 4Sep00 		}else
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_BREAKLOW;
//DeadCode CSB 4Sep00 				BreakLow();
//DeadCode CSB 4Sep00 		}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HiGBarrelRoll
//Author		R. Hyde 
//Date			Mon 9 Mar 1998
//
//Description	1.30	
//				Defensive manoeuvre, used when attacker has high overtake and
//				is close range
//				Method is to pull max g and roll rapidly
//				Supposed to inscribe circle around attacker's flight path
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::HiGBarrelRoll()
{
//max g, roll in one direction
//nose low or high
//unbalanced flight, power reduction, increased drag for better pilots
//
//
//treat the same as lagroll

	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	UByte	FF = FlyingFactor();

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			SWord thrust = 100 - FF / 3;
			ACM.Thrust(thrust);
			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
			break;
		}
		case PHASE1:
		{
			SWord desroll = ANGLES_60Deg;
			SWord swroll = roll;
			if(swroll < 0)
				desroll *= -1;
			
			ACM.Pitch(0);
			ACM.FastRoll(desroll);
			if((swroll - desroll < ANGLES_5Deg) && (desroll - swroll < ANGLES_5Deg))
			{
				ai.ManStep = PHASE2;
				if(swroll < 0)
					ACM.SetAileron(16384);
				else
					ACM.SetAileron(-16384);
			}
			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE2:
		{
			ACM.LiftLimit();
			if(MOD.Aileron > 0) 
				ACM.SetAileron(16384);
			else
				ACM.SetAileron(-16384);
			SWord swroll = roll;
			if((swroll > ANGLES_90Deg) || (-swroll > ANGLES_90Deg))
				ai.ManStep = PHASE3;

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
		case PHASE3:
		{
			ACM.LiftLimit();
			if(MOD.Aileron > 0) 
				ACM.SetAileron(16384);
			else
				ACM.SetAileron(-16384);

			SWord desroll = ANGLES_60Deg;
			if(MOD.Aileron > 0) 
				desroll *= -1;

			SWord swroll = roll;
			if((swroll - desroll < ANGLES_5Deg) && (desroll - swroll < ANGLES_5Deg))
				ai.manoeuvre = MANOEUVRE_SELECT;

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}

//DEADCODE DAW 31/03/99 	ACMMODEL& ACM = *fly.pAcmModel;
//DEADCODE DAW 31/03/99 	MODEL& MOD = *fly.pModel;
//DEADCODE DAW 31/03/99 
//DEADCODE DAW 31/03/99 	static FP dRoll = 0;
//DEADCODE DAW 31/03/99 	UByte	FF = FlyingFactor();
//DEADCODE DAW 31/03/99 	switch (ai.ManStep)
//DEADCODE DAW 31/03/99 	{
//DEADCODE DAW 31/03/99 		case PHASE0:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			MOD.Rudder = 0;
//DEADCODE DAW 31/03/99 	
//DEADCODE DAW 31/03/99 			SWord thrust = 100 - (FF * 50)/256;	
//DEADCODE DAW 31/03/99 			if (thrust > 95)
//DEADCODE DAW 31/03/99 				thrust = 100;
//DEADCODE DAW 31/03/99 			ACM.Thrust (thrust);
//DEADCODE DAW 31/03/99 			if  ( roll << ANGLES_180Deg)
//DEADCODE DAW 31/03/99 				ai.desiredroll = (Angles)1;
//DEADCODE DAW 31/03/99 			else
//DEADCODE DAW 31/03/99 				ai.desiredroll = (Angles)-1;
//DEADCODE DAW 31/03/99 			SetManoeuvreTime (1000);	// 400
//DEADCODE DAW 31/03/99 			ai.ManStep = PHASE1;
//DEADCODE DAW 31/03/99 			break;
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 		case PHASE1:
//DEADCODE DAW 31/03/99 		{
//DEADCODE DAW 31/03/99 			ACM.LiftLimit();
//DEADCODE DAW 31/03/99 			if ((SWord)ai.desiredroll >= 0)
//DEADCODE DAW 31/03/99 				ACM.RollRate (400 * FF/256);		//deg/cs gets converted to rad/cs
//DEADCODE DAW 31/03/99 			else
//DEADCODE DAW 31/03/99 				ACM.RollRate (-400 * FF/256);
//DEADCODE DAW 31/03/99 			if (!ManoeuvreTimeLeft())
//DEADCODE DAW 31/03/99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 31/03/99 			break;
//DEADCODE DAW 31/03/99 		}
//DEADCODE DAW 31/03/99 	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UnBalancedFlight
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
void	ACMAirStruc::UnBalancedFlight()
{
//skid and slip while making turns
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

 	switch (ai.ManStep)
 	{
 		case PHASE0:
 		{
 			SetManoeuvreTime (200);
			if  (roll << ANGLES_20Deg)
				ai.desiredhdg = hdg + ANGLES_60Deg;
			else if  (roll >> ANGLES_340Deg)
				ai.desiredhdg = hdg - ANGLES_60Deg;
			else if ( roll == ANGLES_0Deg)
			{
				RndVal	rndnum = Math_Lib.rnd();
				if (rndnum > RND50PC)
					ai.desiredhdg = hdg + ANGLES_60Deg;
				else
					ai.desiredhdg = hdg - ANGLES_60Deg;
			}else
 				ai.desiredhdg = hdg;
			ai.desiredroll = (Angles)(2 + Math_Lib.rnd(2));
 			ai.ManStep = PHASE1;
 			if (MOD.Aileron >= 0)
 			{
 				ACM.SetRudder(MAXRUDDER);
 			}else
 			{
 				ACM.SetRudder(-MAXRUDDER);
 			}
			RndVal	rndnum = Math_Lib.rnd();
			if (rndnum > RND50PC)
				ai.desiredpitch = ANGLES_5Deg;
			else
				ai.desiredpitch = ANGLES_355Deg;
 			
 		}
 		case PHASE1:
 		{
// 			ACM.Pitch(ai.desiredpitch);
 			SWord TempCtrlRudder = ACM.CtrlRudder;
			MoveToHdg (ai.desiredhdg, ai.desiredpitch);
			ACM.CtrlRudder = TempCtrlRudder;
 			if (!ManoeuvreTimeLeft())
 			{
				ai.desiredroll--;
				if (((SWord)ai.desiredroll) < 0)
				{
	 				MOD.Rudder = 0;
					ACM.CtrlRudder = 0;
					ai.manoeuvre = MANOEUVRE_SELECT;
 
				}else
				{
					if (MOD.Rudder > 0)
		 				ACM.SetRudder(-MAXRUDDER);
 					else
		 				ACM.SetRudder(MAXRUDDER);
					RndVal	rndnum = Math_Lib.rnd();
					if (rndnum > RND50PC)
						ai.desiredpitch = ANGLES_5Deg;
					else
						ai.desiredpitch = ANGLES_355Deg;
		 			SetManoeuvreTime (200);
				}
 			}
 			break;
 		}
 	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TrackingShot
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
void	ACMAirStruc::LowAlt()
{
 	ACMMODEL& ACM = *fly.pAcmModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(100);

			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			FP despitch = FP(CalcBestClimbPitch()) * FP(vel_) / FP(CalcBestClimbSpeed());
			if((ai.unfriendly) && (TargetFacingSubject(ANGLES_45Deg)))
				despitch *= 0.5;
			ACM.VelPitch(despitch);

			FP desroll = FindRequiredRoll (hdg - HdgIntercept, GentleBankData);
			desroll = desroll * (1000.0 - manoeuvretime) / 1000.0;
			ACM.FastRoll(desroll);

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SnapShot
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
void	ACMAirStruc::SnapShot()
{
//
//similar to turningfight 21/5/98
// but don't slow down
//
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	COORDS3D	target;
	SLong		time;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

	if (		(Range < DANGERRANGE)
			&&	(reqdeltahdg_pos < (SWord)ANGLES_30Deg)
		)		
	{
		//this method just extrapolates position
		//to get turn:
		//get distance travelled and turn in time to work out offset
		time = Range / classtype->muzzlevel;		//MUZZELVEL;
		//calc lead position using this time
		target.X = ai.unfriendly->World.X + (unfriendly->vel_x * time ) / 1000;
		target.Y = ai.unfriendly->World.Y + (unfriendly->vel_y * time ) / 1000;
		target.Z = ai.unfriendly->World.Z + (unfriendly->vel_z * time ) / 1000;
		InterceptandRange (&target);
	}else
		target = ai.unfriendly->World;

	if (Range < THRUST_0_RANGE)
	{
		ai.ManStep = PHASE0;
		ai.manoeuvre=MANOEUVRE_ZOOM;
	}
	else
//DeadCode RDH 16Dec98 		TurnFightSub(HdgIntercept, FALSE, ANGLES_5Deg, target);
		TurnFightPhase1(HdgIntercept, FALSE, ANGLES_0Deg, target);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StayOnTail
//Author		R. Hyde 
//Date			Fri 20 Mar 1998
//
//Description	This is not a good idea, very aggressive
//				Stay at corner speed or less
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::StayOnTail()
{
//	if necessary shed energy:
//		turn
//		brakes
//		throttle
//	to stay on tail
//
//same as turningfight 21/5/98
//
	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	COORDS3D	target;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	SLong vx = 0, vy = 0, vz = 0;

	reqdeltahdg = 	hdg - HdgIntercept;
	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

	if (	(reqdeltahdg_pos < (SWord)ANGLES_90Deg)
		)		
	{
		CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);

		target.X = ai.unfriendly->World.X + vx;
		target.Y = ai.unfriendly->World.Y + vy;
		target.Z = ai.unfriendly->World.Z + vz;
		InterceptandRange (&target);
	}else
		target = ai.unfriendly->World;

	TurnWithPitchChange(HdgIntercept, TRUE, target);

//DEADCODE RDH 28/03/99 	SWord	reqdeltahdg,reqdeltahdg_sign;
//DEADCODE RDH 28/03/99 	UWord	reqdeltahdg_pos;
//DEADCODE RDH 28/03/99 	COORDS3D	target;
//DEADCODE RDH 28/03/99 	SLong		time;
//DEADCODE RDH 28/03/99 	MODEL& MOD = *fly.pModel;
//DEADCODE RDH 28/03/99 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DEADCODE RDH 28/03/99 
//DEADCODE RDH 28/03/99 	reqdeltahdg = 	Rads2Rowan(MOD.fHdg) - HdgIntercept;
//DEADCODE RDH 28/03/99 	Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);
//DEADCODE RDH 28/03/99 
//DEADCODE RDH 28/03/99 	if (		(Range < DANGERRANGE)
//DEADCODE RDH 28/03/99 			&&	(reqdeltahdg_pos < (SWord)ANGLES_30Deg)
//DEADCODE RDH 28/03/99 		)		
//DEADCODE RDH 28/03/99 	{
//DEADCODE RDH 28/03/99 		//this method just extrapolates position
//DEADCODE RDH 28/03/99 		//to get turn:
//DEADCODE RDH 28/03/99 		//get distance travelled and turn in time to work out offset
//DEADCODE RDH 28/03/99 		time = Range / classtype->muzzlevel;		//MUZZELVEL;
//DEADCODE RDH 28/03/99 		//calc lead position using this time
//DEADCODE RDH 28/03/99 		target.X = ai.unfriendly->World.X + (unfriendly->velx * time );
//DEADCODE RDH 28/03/99 		target.Y = ai.unfriendly->World.Y + (unfriendly->vely * time );
//DEADCODE RDH 28/03/99 		target.Z = ai.unfriendly->World.Z + (unfriendly->velz * time );
//DEADCODE RDH 28/03/99 		InterceptandRange (&target);
//DEADCODE RDH 28/03/99 	}else
//DEADCODE RDH 28/03/99 		target = ai.unfriendly->World;
//DEADCODE RDH 28/03/99 
//DEADCODE RDH 28/03/99 	TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DEADCODE RDH 28/03/99 //DeadCode RDH 16Dec98 	TurnFightSub(HdgIntercept, TRUE, ANGLES_5Deg, target);

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HeadOnAttack
//Author		Craig Beeston
//Date			Thu 24 Nov 1999
//
//Description	Leader flies ahead of bombers, followers in line astern
//				Leader dives and attacks lead bomber head on, followers attack bomber followers
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::HeadOnAttack()
{
	ACMMODEL& ACM = *fly.pAcmModel;

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			if(World.Y < ai.unfriendly->World.Y)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
				return;
			}
			if(formpos == 0)			//Find leader of bomber group
			{
				AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
				AirStrucPtr target = unf->GetLeadAc();
//DeadCode CSB 17Aug00 				for(AirStrucPtr t = unf; t; t = t->fly.leadflight)
//DeadCode CSB 17Aug00 					for(AirStrucPtr l = t; l; l = l->Leader())
//DeadCode CSB 17Aug00 						if(l->formpos == 0)
//DeadCode CSB 17Aug00 							target = l;

				if(target != unf)
				{
					SetUnfriendly(target);
//DeadCode CSB 1Aug00 					if(unf->ai.attacker == this)
//DeadCode CSB 1Aug00 						unf->ai.attacker = NULL;
//DeadCode CSB 1Aug00 
//DeadCode CSB 1Aug00 					ai.unfriendly = target;
//DeadCode CSB 1Aug00 					if(target->ai.attacker == NULL)
//DeadCode CSB 1Aug00 						target->ai.attacker = this;
				}
			}
			ACM.SetRudder(0);
			ACM.Thrust(90);
			SetManoeuvreTime(6000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			if(formpos == 0)
			{
				COORDS3D despos = ai.unfriendly->World;
				Float sin, cos;
				Math_Lib.high_sin_cos(AirStrucPtr(ai.unfriendly)->hdg, sin, cos);
				despos.X += sin * 200000.0;	//2 km
				despos.Y += 75000;
				despos.Z += cos * 200000.0;	//2 km
				Range = Distance3D(&despos, &World);
				AirStrucPtr unf = AirStrucPtr(ai.unfriendly);

				FP deltaTX = (10000.0 * FP(despos.X - World.X)) / FP(vel_x - unf->vel_x);
				FP deltaTZ = (10000.0 * FP(despos.Z - World.Z)) / FP(vel_z - unf->vel_z);

				MODMAXMIN(deltaTX, 0, 6000);
				MODMAXMIN(deltaTZ, 0, 6000);

				despos.X += unf->vel_x * (deltaTX + deltaTZ) * 0.5 * 0.0001;
				despos.Z += unf->vel_z * (deltaTX + deltaTZ) * 0.5 * 0.0001;

				InterceptandRange(&despos);
				
				ACM.VelPitch(PitchIntercept);
				SWord desroll = FindRequiredRoll (hdg - HdgIntercept, GentleBankData);
				ACM.FastRoll(desroll);
				if(Range < 5000)
					ai.ManStep = PHASE2;
				if(!TimeLeft())
					ai.manoeuvre = MANOEUVRE_SELECT;
				break;
			}
			else
			{
				AirStrucPtr lf = FindGroupLeader();

				despos = *PositionWRTLeader(lf);
				despos.X -= (lf->vel_x * Timer_Code.FRAMETIME) / 10000;
				despos.Y -= (lf->vel_y * Timer_Code.FRAMETIME) / 10000;
				despos.Z -= (lf->vel_z * Timer_Code.FRAMETIME) / 10000;

				FP leadrange = 25000;
				despos.X += FP(lf->vel_x) * leadrange / FP(lf->vel_);
				despos.Y += FP(lf->vel_y) * leadrange / FP(lf->vel_);
				despos.Z += FP(lf->vel_z) * leadrange / FP(lf->vel_);
				InterceptandRange(&despos);
				FP desroll = FindRequiredRoll(SWord(hdg) - SWord(HdgIntercept), CombatReqBankData);
				ACM.FastRoll(desroll);
				ACM.VelPitch(PitchIntercept);

				FP range	 = FP(despos.X - World.X) * FP(lf->vel_x) + FP((despos.Z - World.Z)) * FP(lf->vel_z);
				range       /= FP(lf->vel_);
				FP desvel	 = lf->vel_ + 10 * (range - leadrange);

				if(vel_ < desvel)
					ACM.Thrust(100);
				else
					ACM.Thrust(50);

				if(lf->ai.ManStep == PHASE2)
				{
					AirStrucPtr leadbomber = AirStrucPtr(lf->ai.unfriendly);
					AirStrucPtr target     = leadbomber;
					for(AirStrucPtr t = leadbomber; t; t = t->Follower())
						if( (t->position()) && ((position() & 0x01) == (t->position() & 0x01)) )
						{
							target = t;
							break;
						}

					SetUnfriendly(target);								//CSB 1Aug00
//DeadCode CSB 1Aug00 					AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
//DeadCode CSB 1Aug00 					if(unf->ai.attacker == this)
//DeadCode CSB 1Aug00 						unf->ai.attacker = NULL;
//DeadCode CSB 1Aug00 
//DeadCode CSB 1Aug00 					ai.unfriendly = target;
//DeadCode CSB 1Aug00 					if((AirStrucPtr(ai.unfriendly))->ai.attacker == NULL)
//DeadCode CSB 1Aug00 						(AirStrucPtr(ai.unfriendly))->ai.attacker = this;

					ai.ManStep = PHASE2;
				}
				break;
			}
		}
		case PHASE2:
		{
			ACM.SetElevator(0);
			ACM.SetRudder(0);
			ACM.FastRoll(ANGLES_180Deg);
			SWord swroll = roll;
			if((swroll > ANGLES_170Deg) || (-swroll > ANGLES_170Deg))
				ai.ManStep = PHASE3;
			break;
		}
		case PHASE3:
		{
			ACM.SetAileron(0);
			ACM.LiftLimit();
			SWord swroll = roll;
			if((swroll < ANGLES_90Deg) && (-swroll < ANGLES_90Deg))
			{
				ai.ManStep = PHASE4;
				SetManoeuvreTime(1000);
			}
			break;
		}
		case PHASE4:
		{
			AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
			COORDS3D targ = unf->World;
			InterceptandRange(ai.unfriendly);
			SWord dhdg   = SWord(hdg)   - SWord(HdgIntercept);
			SWord dpitch = SWord(pitch) - SWord(PitchIntercept);

			SWord swpitch = PitchIntercept;
			SWord deltahdg = unf->hdg - ANGLES_180Deg - HdgIntercept;
			HdgIntercept -= deltahdg;	//Aim for a head to head

			SWord swhdg = SWord(hdg) - SWord(HdgIntercept);
			if(-SWord(pitch) > ANGLES_45Deg)
			{
				ACM.LiftLimit();
				ACM.FastRoll(-2.0 * swhdg);
				fly.pModel->Rudder = 0;//ACM.SetRudder(0);
			}
			else
			{
				ACM.Pitch(2.0 * swpitch);
				SWord desroll = -2.0 * swhdg;
				ACM.FastRoll(desroll);
				fly.pModel->Rudder = 0;//ACM.SetRudder(0);
			}

			if(Range < 2 * INSIDEWEAPONSRANGE)
			{
//DEADCODE CSB 27/01/00 				PrintVar(70, 20, "h %.2f ", FP(dhdg   / 182.04));
//DEADCODE CSB 27/01/00 				PrintVar(70, 21, "p %.2f ", FP(dpitch / 182.04));
				if(dhdg   < 0)	dhdg   *= -1;
				if(dpitch < 0)	dpitch *= -1;
				if(dpitch < dhdg) dpitch = dhdg;
				if((Range < WEAPONSRANGE) && (FP(Range) * FP(dpitch) * 0.0001 < 1000))
					FireABullet(100);

//DEADCODE CSB 27/01/00 				PrintVar(70, 22, "R %.0f ", FP(FP(Range) * FP(dpitch) * 0.0001));
			}

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;			

			if(Range < 35000)
			{	
				ai.ManStep = PHASE5;
				SetManoeuvreTime(200);
			}
			break;
		}
		case PHASE5:
		{
			ACM.FastRoll(0);
			ACM.SetElevator(16384 + SWord(pitch) * 2);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
//DEADCODE DAW 29/11/99 	}
//DEADCODE DAW 29/11/99 	else	//a follower
//DEADCODE DAW 29/11/99 	{		
//DEADCODE DAW 29/11/99 		AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
//DEADCODE DAW 29/11/99 	
//DEADCODE DAW 29/11/99 		switch(ai.ManStep)
//DEADCODE DAW 29/11/99 		{
//DEADCODE DAW 29/11/99 			case PHASE0:
//DEADCODE DAW 29/11/99 			{
//DEADCODE DAW 29/11/99 				AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
//DEADCODE DAW 29/11/99 				AirStrucPtr leadac = FindGroupLeader();
//DEADCODE DAW 29/11/99 				AirStrucPtr target = leadac;
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 				for(AirStrucPtr nf = leadac; nf; nf = nf->fly.nextflight)
//DEADCODE DAW 29/11/99 					if(nf->fly.nextflight == this)
//DEADCODE DAW 29/11/99 						for(AirStrucPtr f = nf; f; f = f->Follower())
//DEADCODE DAW 29/11/99 							target = f;
//DEADCODE DAW 29/11/99 					else
//DEADCODE DAW 29/11/99 						for(AirStrucPtr f = nf; f; f = f->Follower())
//DEADCODE DAW 29/11/99 							if(f->follower == this)
//DEADCODE DAW 29/11/99 								target = f;
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 				if((unf != target) && (unf != NULL) && (unf->ai.attacker == this))
//DEADCODE DAW 29/11/99 					unf->ai.attacker = NULL;
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 				ai.unfriendly = target;
//DEADCODE DAW 29/11/99 							
//DEADCODE DAW 29/11/99 				ACM.SetRudder(0);
//DEADCODE DAW 29/11/99 				ACM.Thrust(100);
//DEADCODE DAW 29/11/99 				ai.ManStep = PHASE1;
//DEADCODE DAW 29/11/99 			}
//DEADCODE DAW 29/11/99 			
//DEADCODE DAW 29/11/99 			case PHASE1:
//DEADCODE DAW 29/11/99 			{
//DEADCODE DAW 29/11/99 				AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
//DEADCODE DAW 29/11/99 				if(unf->ai.manoeuvre != MANOEUVRE_HEADONATTACK)
//DEADCODE DAW 29/11/99 				{
//DEADCODE DAW 29/11/99 					ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 29/11/99 					return;
//DEADCODE DAW 29/11/99 				}
//DEADCODE DAW 29/11/99 				
//DEADCODE DAW 29/11/99 				InterceptandRange(unf);
//DEADCODE DAW 29/11/99 //DEADCODE CSB 26/11/99 				FP despitch  = FP(SWord(unf->pitch)) + FP(SWord(PitchIntercept)) * 0.5;
//DEADCODE DAW 29/11/99 				SWord deshdg = SWord(HdgIntercept) - SWord(unf->hdg);
//DEADCODE DAW 29/11/99 				deshdg = unf->hdg + deshdg / 8;
//DEADCODE DAW 29/11/99 				SWord dhdg   = SWord(hdg) - SWord(deshdg);
//DEADCODE DAW 29/11/99 				FP desroll   = FindRequiredRoll (dhdg, GentleBankData);
//DEADCODE DAW 29/11/99 //DEADCODE DAW 26/11/99 				desroll      = FP(SWord(unf->roll)) + desroll;
//DEADCODE DAW 29/11/99 				FP range	 = FP(unf->World.X - World.X) * FP(unf->vel_x) + FP((unf->World.Z - World.Z)) * FP(unf->vel_z);
//DEADCODE DAW 29/11/99 				range       /= FP(unf->vel_);
//DEADCODE DAW 29/11/99 				FP desvel	 = unf->vel_ + 10 * (range - 5000);
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 				SWord despitch = SWord(PitchIntercept) - SWord(unf->pitch);
//DEADCODE DAW 29/11/99 				despitch = unf->pitch + despitch / 8;
//DEADCODE DAW 29/11/99 				ACM.Pitch(despitch);
//DEADCODE DAW 29/11/99 				ACM.FastRoll(desroll);
//DEADCODE DAW 29/11/99 				if(vel_ < desvel)
//DEADCODE DAW 29/11/99 					ACM.Thrust(100);
//DEADCODE DAW 29/11/99 				else
//DEADCODE DAW 29/11/99 					ACM.Thrust(50);
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 				if(unf->ai.ManStep == PHASE3)
//DEADCODE DAW 29/11/99 				{
//DEADCODE DAW 29/11/99 					ai.ManStep = PHASE2;
//DEADCODE DAW 29/11/99 					SetManoeuvreTime(50);
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 					//Choose a target bomber
//DEADCODE DAW 29/11/99 					AirStrucPtr ac       = FindGroupLeader();
//DEADCODE DAW 29/11/99 					AirStrucPtr leadtarg = AirStrucPtr(ac->ai.unfriendly);
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 					AirStrucPtr targ = leadtarg;
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 					for(;;)
//DEADCODE DAW 29/11/99 					{
//DEADCODE DAW 29/11/99 						if(ac == this)
//DEADCODE DAW 29/11/99 						{
//DEADCODE DAW 29/11/99 							ai.unfriendly = targ;
//DEADCODE DAW 29/11/99 							if(targ->ai.attacker == NULL)
//DEADCODE DAW 29/11/99 								targ->ai.attacker = this;
//DEADCODE DAW 29/11/99 							break;
//DEADCODE DAW 29/11/99 						}
//DEADCODE DAW 29/11/99 						if(ac->follower)
//DEADCODE DAW 29/11/99 							ac = ac->Follower();
//DEADCODE DAW 29/11/99 						else if(ac->fly.nextflight)
//DEADCODE DAW 29/11/99 							ac = ac->fly.nextflight;
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 						if(targ->follower)
//DEADCODE DAW 29/11/99 							targ = targ->Follower();
//DEADCODE DAW 29/11/99 						else
//DEADCODE DAW 29/11/99 						{
//DEADCODE DAW 29/11/99 							if(targ->fly.nextflight)
//DEADCODE DAW 29/11/99 								targ = targ->fly.nextflight;
//DEADCODE DAW 29/11/99 							else
//DEADCODE DAW 29/11/99 								targ = leadtarg;
//DEADCODE DAW 29/11/99 						}
//DEADCODE DAW 29/11/99 					}
//DEADCODE DAW 29/11/99 				}
//DEADCODE DAW 29/11/99 				break;
//DEADCODE DAW 29/11/99 			}
//DEADCODE DAW 29/11/99 
//DEADCODE DAW 29/11/99 			case PHASE2:
//DEADCODE DAW 29/11/99 			{
//DEADCODE DAW 29/11/99 				ACM.SetElevator(0);
//DEADCODE DAW 29/11/99 				ACM.SetAileron(0);
//DEADCODE DAW 29/11/99 				ACM.SetRudder(0);
//DEADCODE DAW 29/11/99 				ACM.Thrust(90);
//DEADCODE DAW 29/11/99 				if(!TimeLeft())
//DEADCODE DAW 29/11/99 					ai.ManStep = PHASE3;
//DEADCODE DAW 29/11/99 				break;
//DEADCODE DAW 29/11/99 			}
//DEADCODE DAW 29/11/99 		}
//DEADCODE DAW 29/11/99 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Lufberry
//Author		Craig Beeston
//Date			Thu 18 Nov 1999
//
//Description	Aircraft for a defensive circle (Used by Bf 110)
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Lufberry()
{
	if((!leader) && (!follower))
	{
		ai.manoeuvre = MANOEUVRE_SELECT;
		return;
	}

	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime(3000);
			ACM.SetRudder(0);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord no_ac = 0;
			FP x = 0;
			FP y = 0;
			FP z = 0;
			for(AirStrucPtr ac = FindGroupLeader(); ac; ac = ac->fly.nextflight)
				for(AirStrucPtr f = ac; f; f = f->Follower())
				{
					no_ac++;
					x += f->World.X;
					y += f->World.Y;
					z += f->World.Z;
				}

			x /= no_ac;
			y /= no_ac;
			z /= no_ac;

			COORDS3D targ;
			targ.X = x;
			targ.Y = y;
			targ.Z = z;

			AirStrucPtr target = NULL;
			if(formpos == 0)	//This is lead aircraft and therefore must chase last aircraft
			{
				for(AirStrucPtr nf = this; nf; nf = nf->fly.nextflight)
					if(nf->fly.nextflight == NULL)
						for(AirStrucPtr f = nf; f; f = f->Follower())
							target = f;
			}
			else
			{
				AirStrucPtr leadac = FindGroupLeader();

				for(AirStrucPtr nf = leadac; nf; nf = nf->fly.nextflight)
				{
					if(nf->fly.nextflight == this)
						for(AirStrucPtr f = nf; f; f = f->Follower())
							target = f;
					else
						for(AirStrucPtr f = nf; f; f = f->Follower())
							if(f->follower == this)
								target = f;
				}
			}
			

			InterceptandRange(&targ);
			FP desrange = 4400 * no_ac;
			FP rangesq = Distance3DSquared(&(target->World));
			if(rangesq > (50000.0 * 50000.0))
				ACM.Thrust(100);
			else
				ACM.Thrust(50);

//DEADCODE DAW 29/11/99 			FP deltarange = (25000 - range) / 10;
//DEADCODE DAW 29/11/99 			MODLIMIT(deltarange, 1000);
//DEADCODE DAW 29/11/99 			desrange += deltarange;

			SWord deshdg;
			if(Range > 3 * desrange)
				deshdg = HdgIntercept;
			else
				deshdg = HdgIntercept + ANGLES_90Deg * (3 - Range / desrange) * 0.5;

			SWord deltahdg = SWord(hdg) - SWord(deshdg);
			SWord desroll = FindRequiredRoll(deltahdg, CombatReqBankData);
			ACM.FastRoll(desroll);
			SWord despitch = SWord(PitchIntercept) / 2;
			ACM.VelPitch(despitch);
			
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}

//DEADCODE DAW 29/11/99 			InterceptandRange(target);
//DEADCODE DAW 29/11/99 			PitchIntercept += PitchIntercept;
//DEADCODE DAW 29/11/99 			ACM.VelPitch(SWord(PitchIntercept) / 2);
//DEADCODE DAW 29/11/99 			SWord deltahdg = SWord(hdg) - SWord(HdgIntercept);
//DEADCODE DAW 29/11/99 			SWord desroll = FindRequiredRoll(deltahdg, CombatReqBankData);
//DEADCODE DAW 29/11/99 			if((deltahdg < ANGLES_45Deg) && (-deltahdg < ANGLES_45Deg))
//DEADCODE DAW 29/11/99 				desroll += target->roll;
//DEADCODE DAW 29/11/99 			MODLIMIT(desroll, ANGLES_90Deg);
//DEADCODE DAW 29/11/99 			ACM.FastRoll(desroll);
//DEADCODE DAW 29/11/99 			
//DEADCODE DAW 29/11/99 			FP throttle = 75 + 25 * (Range - 50000) / 10000;
//DEADCODE DAW 29/11/99 			MODMAXMIN(throttle, 50, 100);
//DEADCODE DAW 29/11/99 			ACM.Thrust(throttle);
//DEADCODE DAW 29/11/99 			if(!TimeLeft())
//DEADCODE DAW 29/11/99 				ai.manoeuvre = MANOEUVRE_SELECT;
//DEADCODE DAW 29/11/99 			break;
//DEADCODE DAW 29/11/99 		}
//DEADCODE DAW 29/11/99 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SteepDive
//Author		Craig Beeston
//Date			Thu 18 Nov 1999
//
//Description	Used by Bf 109 to escape RAF fighter (Negative G)
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SteepDive()
{
 	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.SetRudder(0);
			ACM.Thrust(100);
			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			SWord swroll = roll;
			if((swroll < ANGLES_90Deg) && (-swroll < ANGLES_90Deg))
				ACM.FastRoll(ANGLES_0Deg);
			else
				ACM.FastRoll(ANGLES_180Deg);
			ACM.Pitch(ANGLES_300Deg);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpAndUnder
//Author		Craig Beeston
//Date			Thu 18 Nov 1999
//
//Description	Dive below target from astern and attack from blind spot
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::UpAndUnder()
{
	if(ai.unfriendly == NULL)
	{
		ai.manoeuvre = MANOEUVRE_SELECT;
		return;
	}

 	ACMMODEL& ACM = *fly.pAcmModel;
	PMODEL pModel = fly.pModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.SetRudder(0);
			ACM.Thrust(100);
			ai.ManStep = PHASE1;
			SetManoeuvreTime(3000);
		}
		case PHASE1:
		{
			const Float desrange = 30000;
			const Float deltaalt = 10000;

			AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
			COORDS3D target = unf->World;
			Float sin, cos;
			Math_Lib.high_sin_cos(unf->hdg, sin, cos);
			target.X -= desrange * sin;
			target.Y -= deltaalt;
			target.Z -= desrange * cos;
			InterceptandRange(&target);
			ACM.VelPitch(PitchIntercept);
		
			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			ACM.FastRoll(reqroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			if(Range < 1000)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime(3000);
			}
			break;
		}
		case PHASE2:
		{
			COORDS3D target = ai.unfriendly->World;
			SLong dx, dy, dz;
			CalcLead(this, AirStrucPtr(ai.unfriendly), dx, dy, dz, FALSE);
			target.X += dx;
			target.Y += dy;
			target.Z += dz;

			InterceptandRange(&target);
			ACM.Pitch(PitchIntercept);

			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			ACM.FastRoll(reqroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			if(Range < 20000)
			{
				ai.manoeuvre=MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = PHASE0;
				SetManoeuvreTime(1500);
			}
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StallTurn
//Author		Craig Beeston
//Date			Thu 18 Nov 1999
//
//Description	(Used by Bf 110)
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::StallTurn()
{
 	ACMMODEL& ACM = *fly.pAcmModel;
	PMODEL pModel = fly.pModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.SetRudder(0);
			ACM.Thrust(0);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Pitch(ANGLES_60Deg);
			ACM.FastRoll(0);
			if(vel_ < 1.5 * classtype->minvel)
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime(1000);
			}
			break;
		}
		case PHASE2:
		{
			if(SWord(roll) > ANGLES_0Deg)
				ACM.SetRudder(32767);
			else
				ACM.SetRudder(-32767);
			ACM.SetAileron(-pModel->Rudder);
			ACM.SetElevator(-16384);
			if((!TimeLeft()) || (-SWord(pitch) > ANGLES_60Deg) || (vel_ > 1.5 * classtype->minvel))
			{
				ai.ManStep = PHASE3;
				ACM.Thrust(100);
				ACM.SetAileron(pModel->Rudder);
				SetManoeuvreTime(250);
			}
			break;
		}
		case PHASE3:
		{
			ACM.SetAileron(0);
			ACM.SetRudder(0);
			ACM.SetElevator(0);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SlashingAttack
//Author		Craig Beeston
//Date			Thu 18 Nov 1999
//
//Description	Like a poor mans dive and zoom.
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SlashingAttack()
{
	if(ai.unfriendly == NULL)
	{
		ai.manoeuvre = MANOEUVRE_SELECT;
		return;
	}

	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(100);
			ACM.SetRudder(0);
			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			InterceptandRange(ai.unfriendly);
			ACM.VelPitch(PitchIntercept);

			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			ACM.FastRoll(reqroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;

			if(Range < INSIDEWEAPONSRANGE)
			{
				SWord deltahdg   = SWord(hdg)   - SWord(HdgIntercept);
				SWord deltapitch = SWord(pitch) - SWord(PitchIntercept);
				if(deltahdg   < 0)	deltahdg   *= -1;
				if(deltapitch < 0)	deltapitch *= -1;
				if((deltahdg < ANGLES_30Deg) && (deltapitch < ANGLES_30Deg))
				{
					ai.ManStep = PHASE2;
					SetManoeuvreTime(2000);
				}
			}
			break;
		}
		case PHASE2:
		{
			COORDS3D target = ai.unfriendly->World;
			SLong	 dx, dy, dz;
			CalcLead(this, AirStrucPtr(ai.unfriendly), dx, dy, dz, FALSE);
			target.X += dx;
			target.Y += dy;
			target.Z += dz;
			InterceptandRange(&target);

			SWord deshdg = ANGLES_30Deg;
			deshdg *= (55000.0 - FP(Range)) / 30000.0;
			if(SWord(roll) < 0)
				deshdg *= -1;
			deshdg += HdgIntercept;
			
			SWord deltahdg = deshdg - SWord(hdg);
			SWord desroll = ANGLES_60Deg;
			
			if(deltahdg < 0)
			{
				desroll  *= -1;
				deltahdg *= -1;
			}
			SWord deltaroll = desroll - SWord(roll);
			if((deltaroll < ANGLES_20Deg) && (-deltaroll < ANGLES_20Deg))
			{
				ACM.LiftLimit();
				ACM.SetRudder(0);
				if(desroll > 0)
					desroll += 5 * (SWord(pitch) - SWord(PitchIntercept));
				else
					desroll -= 5 * (SWord(pitch) - SWord(PitchIntercept));
			}
			else
				ACM.Pitch(PitchIntercept);

			ACM.FastRoll(desroll);

			if((!TimeLeft()) || (Range < 10000))
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbTurn
//Author		Craig Beeston
//Date			Thu 18 Nov 1999
//
//Description	Used by Spitfires in defence
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::ClimbTurn()
{
 	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(100);
			ACM.SetRudder(0);
			SetManoeuvreTime(2000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Pitch(ANGLES_30Deg);
			SWord desroll = ANGLES_45Deg;
			if(SWord(roll) < ANGLES_0Deg)
				desroll *= -1;
			ACM.FastRoll(desroll);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Roll360
//Author		Craig Beeston
//Date			Thu 18 Nov 1999
//
//Description	For looking around
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Roll360()
{
 	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(100);
			ACM.SetRudder(0);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.FastRoll(ANGLES_0Deg);
			ACM.Pitch(ANGLES_30Deg);
			SWord swroll  = roll;
			SWord swpitch = pitch;
			if((swroll < ANGLES_5Deg) && (-swroll < ANGLES_5Deg) && (swpitch > ANGLES_25Deg) && (swpitch < ANGLES_35Deg))
			{				
				ai.ManStep = PHASE2;
				SetManoeuvreTime(1000);
			}
			break;
		}
		case PHASE2:
		{
			ACM.Pitch(ANGLES_30Deg);
			FP desroll = TimeLeft();
			if(!desroll)
				ai.manoeuvre = MANOEUVRE_SELECT;
			desroll *= 65.536;
			ACM.FastRoll(SWord(desroll));
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Straffe
//Author		Craig Beeston
//Date			Thu 18 Nov 1999
//
//Description	Shooting at aircraft on the ground
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Straffe()
{
	if((ai.unfriendly != NULL) && (ai.unfriendly->Status.size == AIRSTRUCSIZE) && ((AirStrucPtr(ai.unfriendly))->vel_ < 100000))	//10 m/s
	{
		//Do Nothing 
	}
	else
	{
		ai.manoeuvre = MANOEUVRE_SELECT;
		return;
	}

	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(100);
			ACM.SetRudder(0);
			SetManoeuvreTime(1000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
//DeadCode CSB 10Nov00 			COORDS3D target = ai.unfriendly->World;
//DeadCode CSB 10Nov00 			target.Y += 25000;
//DeadCode CSB 10Nov00 			InterceptandRange(&target);
//DeadCode CSB 10Nov00 			SWord deltahdg = SWord(HdgIntercept) - SWord(hdg);
//DeadCode CSB 10Nov00 			SWord reqroll = FindRequiredRoll(-deltahdg, CombatReqBankData);
//DeadCode CSB 10Nov00 			if(deltahdg < 0)
//DeadCode CSB 10Nov00 			{
//DeadCode CSB 10Nov00 				reqroll += 5 * (SWord(PitchIntercept) - SWord(pitch));
//DeadCode CSB 10Nov00 				deltahdg *= -1;
//DeadCode CSB 10Nov00 			}
//DeadCode CSB 10Nov00 			else
//DeadCode CSB 10Nov00 				reqroll -= 5 * (SWord(PitchIntercept) - SWord(pitch));
//DeadCode CSB 10Nov00 			ACM.FastRoll(reqroll);
//DeadCode CSB 10Nov00 			ACM.LiftLimit();

			COORDS3D target = ai.unfriendly->World;
			InterceptandRange(&target);
			SWord deltahdg = SWord(HdgIntercept - hdg);
			SLong reqroll = 10 * deltahdg;
			MODLIMIT(reqroll, ANGLES_75_5Deg);
			if(Range < 75000)
			{
				reqroll = 0;
				ai.ManStep = 3;
				SetManoeuvreTime(2000);
			}
			ACM.FastRoll(reqroll);
			ACM.VelPitch(0);//LiftLimit();
			if((deltahdg < ANGLES_10Deg) && (-deltahdg < ANGLES_10Deg) && (Range < 500000))
				ai.ManStep = PHASE2;
			break;
		}
		case PHASE2:
		{
			InterceptandRange(ai.unfriendly);
			ACM.Pitch(PitchIntercept);
			SWord deltahdg   = SWord(HdgIntercept   - hdg) ;
			SWord deltapitch = SWord(PitchIntercept - pitch) ;
			SLong reqroll = 10 * deltahdg;
			MODLIMIT(reqroll, ANGLES_75_5Deg);
			ACM.FastRoll(reqroll);

			if(deltahdg   < 0)	deltahdg   *= -1;
			if(deltapitch < 0)	deltapitch *= -1;
			if(deltapitch < deltahdg) deltapitch = deltahdg;
			if((Range < WEAPONSRANGE) && (FP(Range) * FP(deltapitch) * 0.0001 < 1000))
				FireABullet(100);

			if(Range < 20000)
			{
				ai.ManStep = PHASE3;
				SetManoeuvreTime(1500);
			}
			break;
		}
		case PHASE3:
		{
			ACM.FastRoll(0);
			ACM.VelPitch(ANGLES_20Deg);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PeelOff
//Author		Craig Beeston
//Date			Mon 18 Sep 2000
//
//Description	
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::PeelOff()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(100);
			ai.ManStep = PHASE1;
			if(SWord(HdgIntercept - hdg) > 0)
				ai.desiredroll = ANGLES_90Deg;
			else
				ai.desiredroll = ANGLES_270Deg;
			int numac = 0;
			for(AirStrucPtr ld = FindFormpos0(); ld; ld = ld->fly.nextflight)
				for(AirStrucPtr ac = ld; ac; ac = ac->Follower())
					if(ac != this)
					{
						FP dotprod = FP(vel_z) * FP(ac->World.X - World.X) - FP(vel_x) * FP(ac->World.Z - World.Z);
						dotprod /= FP(vel_) * FSqrt(FP(ac->World.X - World.X) * FP(ac->World.X - World.X) + FP(ac->World.Z - World.Z) * FP(ac->World.Z - World.Z));
						if((dotprod > 0) == (ai.desiredroll == ANGLES_90Deg))
							numac++;
					}
			SetManoeuvreTime(50 * numac);
		}
		case PHASE1:
		{
			ACM.FastRoll(ANGLES_0Deg);
			ACM.Pitch(ANGLES_0Deg);
			if(!TimeLeft())
			{
				ai.ManStep = PHASE2;
				SetManoeuvreTime(100);
				ai.desiredpitch = ANGLES_0Deg;
				InterceptandRange(Persons2::PlayerGhostAC);
				SWord dhdg = HdgIntercept - hdg;
				if(ai.desiredroll < 0)	dhdg = -dhdg;
				if((Range < 2500) && (dhdg > ANGLES_45Deg) && (dhdg < ANGLES_135Deg))
					if(SWord(PitchIntercept) < 0)
						ai.desiredpitch = ANGLES_45Deg;
					else
						ai.desiredpitch = ANGLES_135Deg;
			}
			break;
		}
		case PHASE2:
		{
			ACM.FastRoll(ai.desiredroll);
			ACM.Pitch(ai.desiredpitch);
			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlyThroughCloud
//Author		Craig Beeston
//Date			Mon 10 Jan 2000
//
//Description	Follows enemy into cloud and then guesses where enemy will reappear
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::FlyThroughCloud()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	if(ai.ManStep == 0)
	{
		AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
		if(unf)
		{
			FP dt = 1000;
			if(MissManCampSky().CloudLayerCover(&World) > 0)
				dt = 3000;
			Coords3D targ = unf->World;
			targ.X += unf->vel_x * dt / 10000;
			targ.Y += unf->vel_y * dt / 10000;
			targ.Z += unf->vel_z * dt / 10000;
			InterceptandRange(&targ);
			ai.desiredhdg   = HdgIntercept;
			ai.desiredpitch = PitchIntercept;
		}
		else
		{
			ai.desiredpitch = pitch;
			ai.desiredhdg   = hdg;
		}

		SetUnfriendly(NULL);											//CSB 1Aug00
//DeadCode CSB 1Aug00 		ai.unfriendly = NULL;
		SetManoeuvreTime(300);
		ai.ManStep = PHASE1;
	}

	SWord deltahdg = SWord(ai.desiredhdg) - SWord(hdg);
	ai.desiredroll = Angles(FindRequiredRoll(-deltahdg, CombatReqBankData));
	ACM.VelPitch(ai.desiredpitch);
	ACM.FastRoll(ai.desiredroll);
	if(!TimeLeft())
	{
		if((ai.unfriendly) || (ai.ManStep >= 10))
			ai.manoeuvre = MANOEUVRE_SELECT;
		else
		{
			ai.ManStep = SWord(ai.ManStep) + 1;
			SetManoeuvreTime(300);
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Regroup
//Author		Craig Beeston
//Date			Tue 20 Jun 2000
//
//Description	Fly towards squadron leader for a bit
//				
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::Regroup()
{
	if(ai.unfriendly)
		SetUnfriendly(NULL);

	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case PHASE0:
		{
			MoveToThrust(100);
			SetManoeuvreTime(3000);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			AirStrucPtr lead = FindFormpos0();
			despos = lead->World;
			if(despos.Y < fly.pModel->GroundHeight + FT_500)
				despos.Y = fly.pModel->GroundHeight + FT_500;

			InterceptandRange(&despos);

			ACM.Pitch(SWord(PitchIntercept));
			SWord reqroll = FindRequiredRoll(hdg - HdgIntercept, CombatReqBankData);
			ACM.FastRoll(reqroll);

			if(!TimeLeft())
//DeadCode CSB 25Aug00 				ai.manoeuvre = MANOEUVRE_LOOKROUND;
				if(Range < HALFVISIBLERANGE)
				{
					if(!Art_Int.AttackSpareInLeadersGroup(this))
					{
						ai.manoeuvre = MANOEUVRE_DISENGAGED;
						ai.simpleacm = TRUE;
					}
				}
				else
					ai.ManStep = PHASE0;
		}
	}
}

			
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnToHdgAndPitch
//Author		R. Hyde 
//Date			Tue 17 Mar 1998
//
//Description	move to within 5 deg of desiredpitch and desiredhdg 
//				break or sustained turn depending on circumstances
//				if break then nose down if <corner vel
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 21Sep00 Bool	ACMAirStruc::TurnToHdgAndPitch()
//DeadCode AMM 21Sep00 {
//DeadCode AMM 21Sep00 	//return true on success
//DeadCode AMM 21Sep00 	return(TRUE);
//DeadCode AMM 21Sep00 }


//DeadCode AMM 21Sep00 void		ACMAirStruc::CalcDesiredPitchRate(SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos)
//DeadCode AMM 21Sep00 {
//DeadCode AMM 21Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode AMM 21Sep00 	SWord dpitch;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 	ai.desiredpitchrate = AngleSign (Rowan2Rads(PitchIntercept - (SWord)ai.oldoldoldpitchI));
//DeadCode AMM 21Sep00 //DeadCode AMM 24Nov99 	ai.desiredpitchrate = ai.desiredpitchrate /(3 * MOD.MODEL_DT);
//DeadCode AMM 21Sep00 	ai.desiredpitchrate = ai.desiredpitchrate /(3 * MODEL_DT);	//AMM 24Nov99
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 	FP pitchleadmodifier = 0.0025;
//DeadCode AMM 21Sep00 	if (reqdeltapitch_sign >= 0 )
//DeadCode AMM 21Sep00 		pitchleadmodifier = 0.1;
//DeadCode AMM 21Sep00 	if (reqdeltapitch_pos > ANGLES_70Deg)
//DeadCode AMM 21Sep00 		dpitch = ANGLES_70Deg;
//DeadCode AMM 21Sep00 	else
//DeadCode AMM 21Sep00 		dpitch = reqdeltapitch_pos;
//DeadCode AMM 21Sep00 	if (reqdeltapitch_sign < 0)
//DeadCode AMM 21Sep00 		dpitch = - dpitch;
//DeadCode AMM 21Sep00 	ai.deltapitchsum += dpitch;
//DeadCode AMM 21Sep00 	SLong IntPitchForMaxDP = 5000000;
//DeadCode AMM 21Sep00 	if (ai.deltapitchsum > IntPitchForMaxDP)
//DeadCode AMM 21Sep00 		ai.deltapitchsum = IntPitchForMaxDP;
//DeadCode AMM 21Sep00 	else if (ai.deltapitchsum < -IntPitchForMaxDP)
//DeadCode AMM 21Sep00 		ai.deltapitchsum = - IntPitchForMaxDP;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 	ai.desiredpitchrate = ai.desiredpitchrate + (pitchleadmodifier * dpitch/ANGLES_70Deg);
//DeadCode AMM 21Sep00  	ai.desiredpitchrate = ai.desiredpitchrate + pitchleadmodifier * ai.deltapitchsum / (4*IntPitchForMaxDP); 
//DeadCode AMM 21Sep00 }



FP	ACMAirStruc::FineRollAdjust(SWord reqdeltapitch,SWord deltahdg,FP rroll, FP fpitch, FP fhdg)
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;
	SWord	reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;
	FP altmod;
	FP deltahdgmod = 0.0005;
	SWord	deltahdg_sign, dhdg, dpitch;
	UWord	deltahdg_pos;
	FP	desiredturn;
	
	ACM.maxdeltaforclosework = 0.2;


//DeadCode CSB 09/03/99		Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
//DeadCode CSB 09/03/99		Math_Lib.Pos (deltahdg,deltahdg_pos,deltahdg_sign);
//DeadCode CSB 08/03/99	//find desired turn based on hdg change of target
//DeadCode CSB 08/03/99		desiredturn = AngleSign (Rowan2Rads(HdgIntercept - (SWord)ai.oldoldoldhdgI));
//DeadCode CSB 08/03/99		desiredturn = desiredturn /(3 * MOD.MODEL_DT);
//DeadCode CSB 08/03/99	
//DeadCode CSB 08/03/99		desiredturn = (ai.desiredturn + desiredturn)/2;
//DeadCode CSB 08/03/99		ai.desiredturn = desiredturn;
//DeadCode CSB 08/03/99	
//DeadCode CSB 08/03/99	//modify desired turn to "point" at target. Lead account for by input dhdg
//DeadCode CSB 08/03/99		FP leadmodifier = 0.005;
//DeadCode CSB 08/03/99		if (deltahdg_pos > ANGLES_70Deg)
//DeadCode CSB 08/03/99			dhdg = ANGLES_70Deg;
//DeadCode CSB 08/03/99		else
//DeadCode CSB 08/03/99			dhdg = deltahdg_pos;
//DeadCode CSB 08/03/99		if (deltahdg_sign < 0)
//DeadCode CSB 08/03/99			dhdg = - dhdg;
//DeadCode CSB 08/03/99		if  (		((desiredturn >= 0) && (dhdg < 0))
//DeadCode CSB 08/03/99				||
//DeadCode CSB 08/03/99					((desiredturn < 0) && (dhdg >= 0))
//DeadCode CSB 08/03/99				||
//DeadCode CSB 08/03/99					(	(desiredturn < 0.0001)			//if desired turn < 0.5 deg/s 
//DeadCode CSB 08/03/99						&&
//DeadCode CSB 08/03/99						(desiredturn > -0.0001)
//DeadCode CSB 08/03/99					)
//DeadCode CSB 08/03/99			)
//DeadCode CSB 08/03/99		desiredturn = desiredturn - (leadmodifier * dhdg/ANGLES_70Deg); 

//DeadCode CSB 08/03/99		desiredturn = 0;
//DeadCode CSB 09/03/99		CalcDesiredPitchRate(reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos);	//needed for pushing stick forwards

//Global axis
	{
//DeadCode CSB 10/03/99			SWord sinpitch, cospitch;
//DeadCode CSB 10/03/99			Math_Lib.high_sin_cos(pitch, sinpitch, cospitch);
		
//DeadCode AMM 24Nov99 		FP AveHeadgRate = AngleSign (Rowan2Rads(HdgIntercept   - (SWord)ai.oldoldoldhdgI  )) / (3 * MOD.MODEL_DT);
//DeadCode AMM 24Nov99 		FP AvePitchRate = AngleSign (Rowan2Rads(PitchIntercept - (SWord)ai.oldoldoldpitchI)) / (3 * MOD.MODEL_DT);
		FP AveHeadgRate = AngleSign (Rowan2Rads(HdgIntercept   - (SWord)ai.oldoldoldhdgI  )) / (3 * MODEL_DT);//AMM 24Nov99
		FP AvePitchRate = AngleSign (Rowan2Rads(PitchIntercept - (SWord)ai.oldoldoldpitchI)) / (3 * MODEL_DT);//AMM 24Nov99
		rroll			= FPATan(MOD.Speed * AveHeadgRate, (MOD.Speed * AvePitchRate + GRAVITY));// * cospitch / 32768);
		FP DeltaRroll = 0;
		if(MOD.RotVel.x > 0)
			DeltaRroll = 0.01 * fhdg / MOD.RotVel.x;			
		MODLIMIT(DeltaRroll, 0.25);
			rroll += DeltaRroll;
	}
	rroll = AngleSign(rroll);
#ifdef PRINT_AI_DATA
	PrintVar(50, 18, "Rroll     %.1f ", (FP)(57.3 * rroll));	
	PrintVar(50, 19, "RPitch    %.1f ", (FP)(57.3 * fpitch));	
#endif
//DeadCode CSB 09/03/99	
//DeadCode CSB 09/03/99	PrintVar(50, 17, "Rroll     %.1f ", (FP)(57.3 * rroll));	
//DeadCode CSB 09/03/99		if(rollfactor < 1)
//DeadCode CSB 09/03/99		{
//DeadCode CSB 09/03/99			if(fpitch < 0) rroll = AngleSign(FPIE - rroll);
//DeadCode CSB 09/03/99			rroll *= rollfactor;
//DeadCode CSB 09/03/99		}
//DeadCode CSB 09/03/99		if((fpitch > - 0.025) && (fpitch < 0.025) && (fhdg > -0.025) && (fhdg < 0.025)) rroll = deltahdg;	//CSB 08/03/99
//DeadCode CSB 09/03/99	
//DeadCode CSB 09/03/99							PrintString(50, 18, "              ");
//DeadCode CSB 09/03/99	if(rroll == deltahdg)	PrintString(50, 18, "ROLL = HEADING");
//DeadCode CSB 09/03/99	
//DeadCode CSB 09/03/99		if(fpitch < 0)
//DeadCode CSB 09/03/99			rroll = 0;	//when pushing stick, keep roll as is
//DeadCode CSB 09/03/99		rroll = MOD.fRoll + rroll;

//DeadCode CSB 09/03/99		rroll = AngleSign(rroll);
//DeadCode CSB 09/03/99		if (	fpitch < 0
//DeadCode CSB 09/03/99			)
//DeadCode CSB 09/03/99		{
//DeadCode CSB 09/03/99			FP x;
//DeadCode CSB 09/03/99			FP pitchaccel = 0;
//DeadCode CSB 09/03/99			if  (		(roll >> ANGLES_20Deg)
//DeadCode CSB 09/03/99	   				&&	(roll << ANGLES_340Deg)
//DeadCode CSB 09/03/99				)	
//DeadCode CSB 09/03/99				pitchaccel = ai.desiredpitchrate * MOD.Speed;
//DeadCode CSB 09/03/99			if (	(-pitchaccel) < GRAVITY)
//DeadCode CSB 09/03/99			{
//DeadCode CSB 09/03/99				x = 	desiredturn * MOD.Speed / (GRAVITY + pitchaccel);
//DeadCode CSB 09/03/99				rroll = FPATan (x,1);
//DeadCode CSB 09/03/99				rroll = AngleSign(rroll);
//DeadCode CSB 09/03/99			}else
//DeadCode CSB 09/03/99			{
//DeadCode CSB 09/03/99				if (desiredturn > 0)
//DeadCode CSB 09/03/99					rroll = 1.57;
//DeadCode CSB 09/03/99				else
//DeadCode CSB 09/03/99					rroll = -1.57;
//DeadCode CSB 09/03/99			}
//DeadCode CSB 09/03/99		}


//DeadCode CSB 08/03/99		FP DeltaRoll = Rowan2Rads(unfriendly->roll - roll);
//DeadCode CSB 08/03/99		DeltaRoll =  AngleSign(DeltaRoll);		
//DeadCode CSB 08/03/99		FP DeltaRollPos;
//DeadCode CSB 08/03/99		if(DeltaRoll >= 0) DeltaRollPos =  DeltaRoll;
//DeadCode CSB 08/03/99		else			   DeltaRollPos = -DeltaRoll;

//DeadCode CSB 05/03/99		if (				(fpitch <  0.05)
//DeadCode CSB 05/03/99						&&	(fpitch > -0.05)
//DeadCode CSB 05/03/99						&&	(fhdg <  0.05)
//DeadCode CSB 05/03/99						&&	(fhdg > -0.05)
//DeadCode CSB 05/03/99						&&	(DeltaRollPos < F1PIE2 * (256 + FlyingFactor()) / 512)
//DeadCode CSB 05/03/99					)
//DeadCode CSB 05/03/99		{
//DeadCode CSB 05/03/99			MOD.Rudder = 0;
//DeadCode CSB 05/03/99			MOD.Aileron = (SWord)( (FP)(unfriendly->roll - roll) * ACM.rollmodifier );
//DeadCode CSB 05/03/99			MOD.Elevator = 0;
//DeadCode CSB 05/03/99			DeltaRoll *= ACM.rollmodifier * 0.25;
//DeadCode CSB 05/03/99			fly.pModel->ChangeDirection(this,fpitch,-fhdg,DeltaRoll);
//DeadCode CSB 05/03/99	PrintString(0, 21, "LOCKED");
//DeadCode CSB 05/03/99		}
//DeadCode CSB 05/03/99		else
	{
#ifdef PRINT_AI_DATA
	PrintString(0, 20, "FINE ROLL ADJUST");
#endif

		ACM.TurnRate(fpitch);
//DeadCode CSB 12/03/99			ACM.YawRate(fhdg);
//DeadCode CSB 11/03/99			fly.pModel->ChangeDirection(this, fpitch, -fhdg, 0);
	}

	return(rroll);
}


//DeadCode RDH 11Dec98 	MODEL& MOD = *fly.pModel;
//DeadCode RDH 11Dec98 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 	ACM.maxdeltaforclosework = 0.4;
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 	FP	absfpitch = fpitch;
//DeadCode RDH 11Dec98 	if (absfpitch < 0)
//DeadCode RDH 11Dec98 		absfpitch = fpitch;
//DeadCode RDH 11Dec98 	FP	aroll = AngleSign(MOD.fRoll);
//DeadCode RDH 11Dec98 	if (aroll < 0)
//DeadCode RDH 11Dec98 		aroll = -aroll;
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 	//if pointing at target and right way up
//DeadCode RDH 11Dec98 	//then invert excessive roll requests
//DeadCode RDH 11Dec98 //	if  (		(absfpitch < 0.2)
//DeadCode RDH 11Dec98 //			&&	(		(aroll < F1PIE2)
//DeadCode RDH 11Dec98 //				)
//DeadCode RDH 11Dec98 //		)
//DeadCode RDH 11Dec98 //	{
//DeadCode RDH 11Dec98 //		if (rroll > F1PIE2)
//DeadCode RDH 11Dec98 //			rroll = rroll - FPIE;
//DeadCode RDH 11Dec98 //		if (rroll < -F1PIE2)
//DeadCode RDH 11Dec98 //			rroll = rroll + FPIE;
//DeadCode RDH 11Dec98 //	}
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 //	if (		(absfpitch < 0.2)
//DeadCode RDH 11Dec98 //			&&	(absfpitch > -0.2)
//DeadCode RDH 11Dec98 //		)
//DeadCode RDH 11Dec98 //	{
//DeadCode RDH 11Dec98 //		rroll = rroll * (absfpitch)/0.2;
//DeadCode RDH 11Dec98 //	}
//DeadCode RDH 11Dec98 //				if (		(rroll < 0.2)
//DeadCode RDH 11Dec98 //						&&	(rroll > -0.2)
//DeadCode RDH 11Dec98 //					)
//DeadCode RDH 11Dec98 
//DeadCode RDH 11Dec98 		rroll =  MOD.fRoll + rroll;
//DeadCode RDH 11Dec98 		ACM.YawRate(fhdg);
//DeadCode RDH 11Dec98 		return(rroll);
//}


FP	ACMAirStruc::CoarseRollAdjust(FP rroll, FP fpitch)
{
#ifdef PRINT_AI_DATA
	PrintString(0, 19, "Coarse Roll Adjust");
#endif

	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;

	ACM.maxdeltaforclosework = 0.1;
	MOD.Rudder = 0;//MOD.Rudder/2;
	ACM.deltayawsum = 0;//ACM.deltayawsum/2;

	if((fpitch > 0) && (ACM.deltapitchsum < 0)) ACM.deltapitchsum = 0;
	if((fpitch < 0) && (ACM.deltapitchsum > 0)) ACM.deltapitchsum = 0;

	rroll = AngleSign(rroll);

//DeadCode CSB 11/03/99		ACM.deltapitchsum = 0;	//CSB 09/03/99
	FP AbsRroll;
	if(rroll > 0)	AbsRroll =  rroll;
	else			AbsRroll = -rroll;

	if((AbsRroll < FPIE / 6) || (AbsRroll > (1 - 1/6) * FPIE))	ACM.TurnRate(fpitch);	//CSB 09/03/99
	else ACM.TurnRate(0);

	rroll += Rowan2Rads(roll);
	rroll = AngleSign(rroll);

	return(rroll);
}


//DeadCode AMM 21Sep00 Bool	ACMAirStruc::UnfriendlyOnSameRoll()
//DeadCode AMM 21Sep00 {
//DeadCode AMM 21Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode AMM 21Sep00 	if (	(		(roll << ANGLES_180Deg)
//DeadCode AMM 21Sep00 				&&	(unfriendly->roll << ANGLES_180Deg)			
//DeadCode AMM 21Sep00 			)
//DeadCode AMM 21Sep00 			||
//DeadCode AMM 21Sep00 			(		(roll >> ANGLES_180Deg)
//DeadCode AMM 21Sep00 				&&	(unfriendly->roll >> ANGLES_180Deg)			
//DeadCode AMM 21Sep00 			)
//DeadCode AMM 21Sep00 		)
//DeadCode AMM 21Sep00 		return (TRUE);
//DeadCode AMM 21Sep00 	else
//DeadCode AMM 21Sep00 		return(FALSE);
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 }


SWord	ACMAirStruc::RollforTurn(SWord reqdeltapitch,SWord deltahdg, Float& desiredturn,COORDS3D	target)
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
		
		if(ACM.maxdeltaforclosework < 0.1)
		ACM.maxdeltaforclosework = 0.1;
#ifdef PRINT_AI_DATA
	PrintVar(15, 20, "MaxDelta %.1f ", ACM.maxdeltaforclosework);
#endif

//find roll which would put target on lift line
	FP rroll;
	Float fpitch,fhdg;
//DeadCode CSB 08/03/99		ANGLES reqroll = GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );

	FP gdpitch =  AngleSign( Rowan2Rads(reqdeltapitch) );
	FP gdhdg   = -AngleSign( Rowan2Rads(deltahdg) );
	Float sinroll, cosroll;
	Math_Lib.high_sin_cos(roll, sinroll, cosroll);
	fpitch = gdpitch * cosroll + gdhdg   * sinroll;
	fhdg   = gdhdg   * cosroll - gdpitch * sinroll;
	fpitch = AngleSign(fpitch);
	fhdg   = AngleSign(fhdg);
	ANGLES reqroll = Angles(Rads2Rowan(FPATan(fhdg, fpitch) ) );
	
#ifdef PRINT_AI_DATA
	PrintVar(35, 10, "ReqDPitch %.2f ", (FP)(fpitch * 57.3) );
	PrintVar(35, 11, "ReqDRoll  %.2f ", (FP)(reqroll / 182.04) );
	PrintVar(35, 12, "ReqDHeadg %.2f ", (FP)(fhdg * 57.3) );
	PrintVar(35, 13, "Range     %.2f ", (FP)(Range * 0.01) );
#endif

		FP rr = Rowan2Rads(reqroll);
		rroll =  AngleSign(rr);

	if(//(UnfriendlyOnSameRoll())
		//&&	
			(fpitch < ACM.maxdeltaforclosework)
		&&	(fpitch > -ACM.maxdeltaforclosework)
		&&	(fhdg < ACM.maxdeltaforclosework)
		&&	(fhdg > -ACM.maxdeltaforclosework)	)
	{
		rroll = FineRollAdjust(reqdeltapitch, deltahdg, rroll, fpitch, fhdg);
	}
	else
//DeadCode CSB 12/03/99			fly.pModel->ChangeDirection(this, fpitch, -fhdg, 0);
		rroll = CoarseRollAdjust(rroll, fpitch);

	return(Rads2Rowan (rroll));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
SWord	ACMAirStruc::ThrustfromFF()
{
//simple thrust modified in CalcSimpleAccel
//complex model: instead of modifying thrust we rely on drag effect via reduced lift
//DEADCODE RDH 06/05/99 	SWord thrust;
//DEADCODE RDH 06/05/99 	UByte	FF = FlyingFactor();
//DEADCODE RDH 06/05/99 	thrust = 85 + (FF * FF * 15)/65536;
//DEADCODE RDH 06/05/99 	if (thrust > 96)
//DEADCODE RDH 06/05/99 		thrust = 100;
 	return(100);
//DEADCODE RDH 06/05/99 	return (thrust);												  //RDH 06/05/99
}

//DeadCode AMM 21Sep00 void	ACMAirStruc::SpeedUp(FP velc)
//DeadCode AMM 21Sep00 {
//DeadCode AMM 21Sep00 	//Enter with velc negaticve, ie need to speed up
//DeadCode AMM 21Sep00 		FP time;
//DeadCode AMM 21Sep00 		MODEL& MOD = *fly.pModel;
//DeadCode AMM 21Sep00    	SWord thrust;
//DeadCode AMM 21Sep00    	SWord maxthrust = ThrustfromFF();
//DeadCode AMM 21Sep00 	thrust = maxthrust;
//DeadCode AMM 21Sep00 		ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 	velc = -velc;
//DeadCode AMM 21Sep00 	time = (Range - IDEALCOMBATRANGE)/velc;				//cs
//DeadCode AMM 21Sep00 	if (time > 0)
//DeadCode AMM 21Sep00 	{
//DeadCode AMM 21Sep00 		FP accell = velc/time;							//cm/cs/cs
//DeadCode AMM 21Sep00 			//Told - Dold  = m* accelold
//DeadCode AMM 21Sep00 		//Tnew -Dnew = m * accelnew + m* accelold
//DeadCode AMM 21Sep00 		//assume Dold and Dnew are same
//DeadCode AMM 21Sep00 		//Tn = To + m(an)
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 //DEADCODE CSB 05/11/99 		FP fMass = weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel;
//DeadCode AMM 21Sep00 		FP fMass = 0;
//DeadCode AMM 21Sep00 		for(SWord i = 0; i < 4; i++)
//DeadCode AMM 21Sep00 //DEADCODE CSB 06/03/00 			if((classtype->fueltanktype[i] = FT_FIXED) || (Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG]))
//DeadCode AMM 21Sep00 				fMass += fly.fuel_content[i];
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 //DEADCODE CSB 06/03/00 		if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
//DeadCode AMM 21Sep00 			fMass += weap.left.mass     + weap.centre.mass     + weap.right.mass;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 		fMass = fMass * 0.001 + classtype->weightempty;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 //DeadCode AMM 29Jun99 		FP deltaforce = (accell) * MOD.Mass;//N
//DeadCode AMM 21Sep00 		FP deltaforce = (accell) * fMass;//N	//CSB 29Jun99
//DeadCode AMM 21Sep00 		FP Tn = MOD.EngineList->Thrust + deltaforce;
//DeadCode AMM 21Sep00 		thrust = 100 * Tn/MOD.EngineList->MaxThrust;
//DeadCode AMM 21Sep00 		if (thrust < 0)
//DeadCode AMM 21Sep00 		{
//DeadCode AMM 21Sep00 			if (thrust < - 300)
//DeadCode AMM 21Sep00 			{
//DeadCode AMM 21Sep00 				thrust = maxthrust;
//DeadCode AMM 21Sep00 				ACM.SpeedBrakesIn();
//DeadCode AMM 21Sep00 				if (Range < METRES150)
//DeadCode AMM 21Sep00 				{
//DeadCode AMM 21Sep00 					ai.ManStep = PHASE0;
//DeadCode AMM 21Sep00 					if (SubjectLeadingTarget())
//DeadCode AMM 21Sep00 						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGROLL, MANOEUVRE_TURNINGFIGHT);
//DeadCode AMM 21Sep00 					else
//DeadCode AMM 21Sep00 						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_TURNINGFIGHT);
//DeadCode AMM 21Sep00 				}
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			}else
//DeadCode AMM 21Sep00 			{
//DeadCode AMM 21Sep00 				thrust = 0;
//DeadCode AMM 21Sep00 				ACM.SpeedBrakesOut();
//DeadCode AMM 21Sep00 			}
//DeadCode AMM 21Sep00 		}else
//DeadCode AMM 21Sep00 			ACM.SpeedBrakesIn();
//DeadCode AMM 21Sep00 		if (thrust > maxthrust)
//DeadCode AMM 21Sep00 			thrust = maxthrust;
//DeadCode AMM 21Sep00 	}
//DeadCode AMM 21Sep00 	else
//DeadCode AMM 21Sep00 	{	//stay as you are if inside min range
//DeadCode AMM 21Sep00 		thrust = 100 * MOD.EngineList->Thrust/MOD.EngineList->MaxThrust;
//DeadCode AMM 21Sep00 	}
//DeadCode AMM 21Sep00 	ACM.Thrust (thrust);
//DeadCode AMM 21Sep00 }

void	ACMAirStruc::SlowDown(FP velc)
{
	//Enter with velc positive, need to slow down
		FP time;
			MODEL& MOD = *fly.pModel;
		SWord thrust;
  	SWord maxthrust = ThrustfromFF();
		ACMMODEL& ACM = *fly.pAcmModel;
	thrust = maxthrust;


	if (velc != 0)
		time = (Range - IDEALCOMBATRANGE)/velc;				//cs
	else
		time = 100;
	if (time < 0)
	{//inside min range and need to low down
				if (Range < METRES150)
				{
					thrust = maxthrust;
					ACM.SpeedBrakesIn();
					ai.ManStep = PHASE0;
					if (SubjectLeadingTarget())
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGROLL, MANOEUVRE_ZOOM);
					else
						ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_ZOOM);
				}else
				{
					thrust = 0;
					ACM.SpeedBrakesOut();
				}
	}
	else
	{
		FP decell = -velc/time;							//cm/cs/cs
			//Told - Dold  = m* accelold
		//Tnew -Dnew = m * accelnew
		//assume Dold and Dnew are same
		//Tn = To + m(an-ao)
//DEADCODE DAW 01/04/99 		FP deltaforce = (decell - MOD.Acc.z) * MOD.Mass;//N

//DEADCODE CSB 05/11/99 		FP fMass = weap.left.int_fuel + weap.centre.int_fuel + weap.right.int_fuel;
		FP fMass = 0;
		for(SWord i = 0; i < 4; i++)
//DEADCODE CSB 06/03/00 			if((classtype->fueltanktype[i] = FT_FIXED) || (Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG]))
				fMass += fly.fuel_content[i];

//DEADCODE CSB 06/03/00 		if(Save_Data.flightdifficulty [FD_STORESWEIGHTDRAG])
			fMass += weap.left.mass     + weap.centre.mass     + weap.right.mass;

		fMass = fMass * 0.001 + classtype->weightempty;

//DeadCode AMM 29Jun99 		FP deltaforce = (decell) * MOD.Mass;//N
		FP deltaforce = (decell) * fMass;//N	   //CSB 29Jun99
		FP Tn = MOD.EngineList->Thrust + deltaforce;
		thrust = 100 * Tn/MOD.EngineList->MaxThrust;
		if (thrust < 0)
		{
			if  (	(thrust < - 300)
				&&	(Range < METRES150)
				)
			{
				thrust = maxthrust;
				ACM.SpeedBrakesIn();
				ai.ManStep = PHASE0;
				if (SubjectLeadingTarget())
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_TURNINGFIGHT);
				else
					ai.manoeuvre=ManoeuvreBasedOnSkill(SKILL_REGULAR, MANOEUVRE_LAGPURSUIT, MANOEUVRE_TURNINGFIGHT);
			}else
			{
				thrust = 0;
				ACM.SpeedBrakesOut();
			}
		}else
			ACM.SpeedBrakesIn();
		if (thrust > maxthrust)
			thrust = maxthrust;
	}
	ACM.Thrust (thrust);
}



void	ACMAirStruc::SlowDownCheck(UWord reqdeltahdg_pos)
{
	SWord thrust = 100;
	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

//DeadCode CSB 14/04/99			SLong ReqVel = 0;
//DeadCode CSB 14/04/99		SWord MaxAcc = -CalcAccel(0);	//Ensure requesting decel not accel
//DeadCode CSB 14/04/99		SLong velfactor = unfriendly->vel * unfriendly->vel;
//DeadCode CSB 14/04/99		velfactor += (MaxAcc * (Range - IDEALCOMBATRANGE)) * (2.0 / 2560.0);
//DeadCode CSB 14/04/99		if (velfactor > 0)
//DeadCode CSB 14/04/99			ReqVel = FSqrt(	velfactor);
//DeadCode CSB 14/04/99		else
//DeadCode CSB 14/04/99			ReqVel = unfriendly->vel;

 	if((!SubjectFacingTarget(ANGLES_45Deg)) || (!SubjectOnTargetTail(ANGLES_45Deg)))
		thrust = ThrustfromFF();
	else
	{
		SLong ReqVel = 0;
		SLong MaxAcc = 0;
		Bool TooClose = FALSE;
		if(Range < IDEALCOMBATRANGE) TooClose = TRUE;

		if(TooClose)
			MaxAcc = -CalcAccel(2000000000);
		else
			MaxAcc = -CalcAccel(0);	//Ensure requesting decel not accel
 		MaxAcc = MaxAcc / 2;

		if(MaxAcc == 0)
		{
			if(TooClose)
				thrust = 0;
			else
				thrust = ThrustfromFF();
		}
		else
		{
			FP velfactor = ((FP)MaxAcc * ((FP)Range - (FP)IDEALCOMBATRANGE)) * (2.0 * 1000.0);
			if (velfactor > 0)
			{
				if(Range > IDEALCOMBATRANGE)
					ReqVel = unfriendly->vel_ + FSqrt(velfactor);
				else
					ReqVel = unfriendly->vel_ - FSqrt(velfactor);
			}
			else
				ReqVel = unfriendly->vel_;

//DeadCode CSB 01/06/99	PrintVar(40, 3, "Req Vel %.1f ", (FP)(ReqVel * 0.1));

#ifdef PRINT_AI_DATA
PrintVar(40, 2, "Unf Vel %.1f ", (FP)(unfriendly->vel_ * 0.0001));
PrintVar(40, 3, "Req Vel %.1f ", (FP)(ReqVel * 0.0001));
PrintVar(40, 4, "Act Vel %.1f ", (FP)(vel_ * 0.0001));
PrintVar(40, 5, "Throttl %.0f ", (FP)(fly.thrustpercent));
#endif

			if(ReqVel > vel_)						//CSB 27/05/99	
			{
				thrust = ThrustfromFF();	//CSB 27/05/99	
				if(TooClose) 
		 		   ACM.SpeedBrakesIn();
			}
			else									//CSB 27/05/99	
			{
				thrust = 0;				//CSB 27/05/99	
				if(Range < IDEALCOMBATRANGE / 2) 
		 		   ACM.SpeedBrakesOut();
			}
		}
	}

	ACM.Thrust (thrust);

//DeadCode CSB 27/05/99			FP	velc = (vel - unfriendly->vel)/10.0;
//DeadCode CSB 27/05/99			if	(	(vel > ReqVel)
//DeadCode CSB 27/05/99				)
//DeadCode CSB 27/05/99				SlowDown(velc/2);
//DeadCode CSB 27/05/99			else
//DeadCode CSB 27/05/99				SpeedUp(velc/2);
}

		
void	ACMAirStruc::TurnFightTargetNotOnNose(SWord	reqdeltahdg, SWord	reqdeltapitch, SWord	reqdeltapitch_sign, UWord	reqdeltapitch_pos, ANGLES	deltapitch)
{


//roll = arccos (1/(g * cos pitch)
//arccos x = arctan (sqr(1-x^2)/x^2)

 	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	SWord delta;
	SWord dpitch;

//	if (reqdeltahdg > 0)
//		reqroll = -1;
//	else
//		reqroll = 1;

//DEADCODE RDH 23/02/99 	SWord PI = PitchIntercept;
//DeadCode RDH 03Dec98 	if  (		(PI < 0)
//DeadCode RDH 03Dec98 			&&	(Range > WEAPONSRANGE)
//DeadCode RDH 03Dec98 		)
//DeadCode RDH 03Dec98 		PI = 0;
//DEADCODE RDH 23/02/99 	delta = PI + deltapitch;
//DeadCode RDH 03Dec98 	if  (		(delta < ANGLES_0Deg)
//DeadCode RDH 03Dec98 			&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
//DeadCode RDH 03Dec98 			&&	(deltapitch << ANGLES_180Deg)				//if he really wants to go down then let him
//DeadCode RDH 03Dec98 			&&	(		(Range > WEAPONSRANGE)
//DeadCode RDH 03Dec98 					||	(classtype->visible == MIG15)
//DeadCode RDH 03Dec98 						
//DeadCode RDH 03Dec98 				)
//DeadCode RDH 03Dec98 		)	
//DeadCode RDH 03Dec98 		delta = ANGLES_0Deg;
//DEADCODE RDH 23/02/99 	reqdeltapitch = 	delta - fly.cpitch;
//DEADCODE RDH 23/02/99 	Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);
	if (reqdeltapitch_pos > ANGLES_10Deg)
		dpitch = ANGLES_10Deg;
	else
		dpitch = reqdeltapitch_pos;
	if (reqdeltapitch_sign < 0)
		dpitch = - dpitch;
	RollAndPull(reqdeltahdg,dpitch);
}


void	ACMAirStruc::RollAndPull(SWord	reqdeltahdg, SWord dpitch)
{
	MODEL& MOD = *fly.pModel;
	ACMMODEL& ACM = *fly.pAcmModel;
	
	SWord reqroll;

	if (reqdeltahdg > 0)
		reqroll = -1;
	else
		reqroll = 1;

	SWord c,s;
	Math_Lib.high_sin_cos(fly.cpitch,s,c);
	FP x, r;
	FP g = MOD.Inst.I_NormalAcc;
	if (g < 1)
		g = 1;
	FP	gmodifier = dpitch;
		gmodifier = 1 + gmodifier/ANGLES_10Deg;
	x = gmodifier/(g * c / 32768);
	if (x > 1)
		x = 1;
	if (x < -1)
		x = -1;
	x = FSqrt((1-x*x)/(x*x));
	r = FPATan (x,1);
	if (r < 0.5)
		r = 0.5;

	if (reqroll > 0)
		reqroll = Rads2Rowan(r);
	else
		reqroll = -Rads2Rowan(r);

#ifdef PRINT_AI_DATA
	PrintVar(60, 11, "R Roll %.1f", (FP)(reqroll/182.04));
#endif

 	if (		(ai.manoeuvre != MANOEUVRE_SPLITMANOEUVRE)
			&&	(BanditOnColdSide())
		)
	//smart fighter realises that bandit has gone cold side in a turning fight: Don't reverse
 		if (	(Range < DANGERRANGE)	&& (ai.combatskill > SKILL_REGULAR))
 				reqroll = -reqroll;

	ACM.FastRoll ((Angles)reqroll);
	ACM.ZeroSpecificPower();
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnFightSub
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::TurnFightSub(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target)
{
	ACMMODEL& ACM = *fly.pAcmModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Clear ();
			SetManoeuvreTime (1000);
			ACM.maxdeltaforclosework = 0.0;
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			TurnFightPhase1(HdgIntercept, sitbehindtarget, deltapitch, target);
		}
	}

}

void	ACMAirStruc::TurnFightPhase1(ANGLES	HdgIntercept, Bool sitbehindtarget, ANGLES	deltapitch,COORDS3D	target)
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	AirStrucPtr	unfriendly = *ai.unfriendly;

	SLong temp_range;
	temp_range = Range; 	

	SWord	reqdeltahdg,reqdeltahdg_sign;
	UWord	reqdeltahdg_pos;
	SWord	reqdeltapitch,reqdeltapitch_sign;
	UWord	reqdeltapitch_pos;
	Float desiredturn;
	SLong		time;

		reqdeltahdg = 	hdg - HdgIntercept;		//Are You Sure ????	//CSB

//			ACM.MinHeight (FT_2000);
 			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

//DeadCode CSB 10/03/99				reqdeltapitch = PitchIntercept - fly.cpitch;
			reqdeltapitch = PitchIntercept - pitch;
			Math_Lib.Pos (reqdeltapitch,reqdeltapitch_pos,reqdeltapitch_sign);

			ANGLES delta = unfriendly->hdg + ANGLES_180Deg + ANGLES_30Deg - hdg;

			if	(SubjectFacingTarget(ANGLES_45Deg))
			{
				if	(	(delta << ANGLES_60Deg)
						&&	(Range > DANGERRANGE)
						&&	(reqdeltapitch_pos << ANGLES_15Deg)
						&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
					)
				{
//DEADCODE CB 18/11/99 						if  (		(FlyingFactor() < 160)
//DEADCODE CB 18/11/99 								||	(classtype->aerobaticfactor < AEROBATIC_FIGHTER)
//DEADCODE CB 18/11/99 							)
							ai.manoeuvre = MANOEUVRE_HEADON;
//DEADCODE CB 18/11/99 						else
//DEADCODE CB 18/11/99 							ai.manoeuvre = MANOEUVRE_HEADONOFFSET;
						ai.ManStep = PHASE0;
				}
//DEADCODE CSB 25/01/00 				if	(		( Range > WEAPONSRANGE)
//DEADCODE CSB 25/01/00 						&&	(ai.manoeuvre !=  MANOEUVRE_LOWYOYO)
//DEADCODE CSB 25/01/00 						&&  (ai.combatskill >= SKILL_VETERAN)
//DEADCODE CSB 25/01/00 						&&	(ClosureLessThan(MPH15))
//DEADCODE CSB 25/01/00 						&&	(SubjectOnTargetTail(ANGLES_45Deg))
//DEADCODE CSB 25/01/00 						&&	(AboveGround(FT_1000))
//DEADCODE CSB 25/01/00 						&&	((World.Y - ai.unfriendly->World.Y) < FT_100)
//DEADCODE CSB 25/01/00 						&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
//DEADCODE CSB 25/01/00 					)
//DEADCODE CSB 25/01/00 				{
//DEADCODE CSB 25/01/00 					ai.ManStep = PHASE0;
//DEADCODE CSB 25/01/00 					ai.manoeuvre = MANOEUVRE_LOWYOYO;
//DEADCODE CSB 25/01/00 				}
			}
			if  (		(PitchIntercept >> ANGLES_180Deg)
					&&	(PitchIntercept << ANGLES_340Deg)
					&&	((World.Y - ai.unfriendly->World.Y) > FT_3000)
					&&	(ai.manoeuvre != MANOEUVRE_DIVEANDZOOM)
				)
			{
				ai.ManStep = PHASE0;
				ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
			}

#ifdef PRINT_AI_DATA
PrintString(0, 18, "                    ");	//CSB 05/03/99
PrintString(0, 19, "                    ");	//CSB 05/03/99
PrintString(0, 20, "                    ");	//CSB 05/03/99
PrintString(0, 21, "                    ");	//CSB 05/03/99
#endif

			{
				if (sitbehindtarget)
					SlowDownCheck(reqdeltahdg_pos);
				else
					ACM.Thrust(100);
	
				if(unfriendly->classtype->aerobaticfactor > AEROBATIC_LOW)
				{
					if(		((reqdeltahdg_pos < ANGLES_40Deg) && (ACM.maxdeltaforclosework == 0.0))
						||	((reqdeltahdg_pos < ANGLES_45Deg) && (ACM.maxdeltaforclosework != 0.0))		)
					{
	#ifdef PRINT_AI_DATA
		PrintString(0, 18, "Lift Line Calc");
	#endif
						SWord reqroll = RollforTurn(reqdeltapitch, reqdeltahdg, desiredturn, target);
//DEADCODE CSB 07/03/00 					ai.flatturn = FALSE;
						ACM.FastRoll ((Angles)reqroll);
					}
					else
					{
						ACM.maxdeltaforclosework = 0.0;
						SWord rollpos = roll;
						if (rollpos < 0)
							rollpos = -rollpos;

						TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, deltapitch);
						
//					FP	factor = 0.2 + 0.0000916 * (ANGLES_60Deg - rollpos);	//0.75 / ANGLES_60Deg
//DEADCODE CSB 07/03/00 					{
//DEADCODE CSB 07/03/00 						if (!ai.flatturn) 
//DEADCODE CSB 07/03/00 							fly.pAcmModel->ZeroIntControl();
//DEADCODE CSB 07/03/00 						ai.flatturn = TRUE;
//DEADCODE CSB 07/03/00 						TurnFightTargetNotOnNose(reqdeltahdg, reqdeltapitch, reqdeltapitch_sign, reqdeltapitch_pos, deltapitch);
//DEADCODE CSB 07/03/00 						ACM.SetRudder(0);
//DEADCODE CSB 07/03/00 					}
					}
				}
				else
				{
					ACM.Pitch(SWord(PitchIntercept));
					SLong desroll = -5 * reqdeltahdg;
					MODLIMIT(desroll, ANGLES_60Deg);
					ACM.FastRoll(desroll);
				}

				if(!ManoeuvreTimeLeft())
				{
					ai.ManStep = PHASE0;
					if((Range > ENGAGERANGE) &&	(ai.firsttactic == TACTIC_LINEABREAST))
						ai.manoeuvre = MANOEUVRE_LINEABREAST;
					else if((Range > ENGAGERANGE) &&	(ai.firsttactic == TACTIC_LINEASTERN))
						ai.manoeuvre = MANOEUVRE_LINEASTERN;
					else
					{
						SWord absdhdg   = AbsAngle(SWord(HdgIntercept)   - SWord(hdg));
						SWord absdpitch = AbsAngle(SWord(PitchIntercept) - SWord(pitch));
						if((absdhdg < ANGLES_30Deg) && (absdpitch < ANGLES_30Deg))
						{
							if((fly.leadflight) && (fly.leadflight->ai.manoeuvre == MANOEUVRE_TOPCOVER))
								ai.manoeuvre = MANOEUVRE_SELECT;		//force manoeuvre to allow disengage
							else
							{//on tail of target so keep in manoeuvre and up morale
								AirStruc* unf		= (AirStruc*)ai.unfriendly;
								AirStruc* unfbuddy	= unf->FindBuddy();
								if (		(unfbuddy)
										&&	(unf == Persons2::PlayerGhostAC)
										&&	(Range > DANGERRANGE)
										&&	(Range < ENGAGERANGE)
									)
								{
								 	RndVal	rndpc = (RndVal)Math_Lib.rnd(RndValMAX);	
									if	((rndpc > RND50PC)	&&	(Range < VISIBLERANGE))
										_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_BANDIT_RELPOS, MSG_MIGSCOMING_RPT, unfbuddy, *this, unf));
								}
								advantage = TRUE;
								disadvantage = FALSE;
								MoraleMod();
								SetManoeuvreTime (1000);
							}
						}
						else 
							ai.manoeuvre = MANOEUVRE_SELECT;
					}
				}
			}
}


Float	AirStruc::Model_InstTurnRate(AirStrucPtr subject)
{//return tr in rads per cs, dhdg in rowans
	FP tr, tr2;


	if (!subject)
		return 0.0;

	tr = subject->fly.dhdg * 0.00009587	/ Timer_Code.FRAMETIME;					

//	if (subject == Persons2::PlayerGhostAC)
//		subject = Manual_Pilot.ControlledAC2;
 //	tr = ((((SWord)subject->hdg)* 0.00009587) - 
 //				AngleSign (subject->fly.LastfHdg)) / Timer_Code.FRAMETIME;
//	FP test;
//	test = tr - tr2;
//	if (abs(test) > 0.0001)
//		test = -test ;

	return(tr);
}


void	ACMAirStruc::CalcLead(AirStrucPtr  subject, AirStrucPtr target, SLong& deltax,SLong& deltay,SLong& deltaz, Bool cutcorner)
{
	if(Range > 2 * WEAPONSRANGE)
	{
		deltax = deltay = deltaz = 0;
		return;
	}

	FP targetvelx = target->vel_x;
	FP targetvely = target->vel_y;
	FP targetvelz = target->vel_z;

	FP VelComp = (subject->vel_x * targetvelx + subject->vel_y * targetvely + subject->vel_z * targetvelz) / subject->vel_;

	FP range = Range;
	range -= 0.0001 * subject->vel_ * Timer_Code.FRAMETIME;
	if(!target->ai.moved)
		range += 0.0001 * target->vel_ * Timer_Code.FRAMETIME;
		
	FP shoottime = FP(range) / ((FP)subject->vel_ - VelComp + (FP)subject->classtype->muzzlevel);	//CSB 05/03/99 //centi-seconds
//DeadCode CSB 25Aug00 	shoottime *= 1.25;

	deltax = targetvelx * shoottime;// * 0.0001;
	deltay = targetvely * shoottime;// * 0.0001;
	deltaz = targetvelz * shoottime;// * 0.0001;

	deltay += 5000000.0 * shoottime * shoottime;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TurnFight
//Author		R. Hyde 
//Date			Fri 13 Mar 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::TurningFight()
{
	if((ai.unfriendly) && (AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW))
	{
		TurningFightBomber();
		return;
	}

	switch(ai.ManStep)
	{
		case 0:
		{
			ai.ManStep = 1;
			SetManoeuvreTime(1500);
		}
		case 1:
		{
			SWord	reqdeltahdg,reqdeltahdg_sign;
			UWord	reqdeltahdg_pos;
			COORDS3D	target;
			MODEL& MOD = *fly.pModel;
			AirStrucPtr	unfriendly = *ai.unfriendly;
			SLong vx = 0, vy = 0, vz = 0;

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 			{
//DeadCode CSB 5Sep00 				if(TimeToChangeToDisengage())
//DeadCode CSB 5Sep00 					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 5Sep00 				SetManoeuvreTime(1500);
//DeadCode CSB 5Sep00 			}

			reqdeltahdg = 	hdg - HdgIntercept;
			Math_Lib.Pos (reqdeltahdg,reqdeltahdg_pos,reqdeltahdg_sign);

		#ifdef PRINT_AI_DATA
			PrintString(0, 15, "Target Tracking");
			PrintString(0, 16, "               ");
		#endif

			if(reqdeltahdg_pos < SWord(ANGLES_90Deg))		
			{
		#ifdef PRINT_AI_DATA
			PrintString(0, 15, "               ");
			PrintString(0, 16, "Lead Tracking  ");
		#endif

				target.X = ai.unfriendly->World.X;
				target.Y = ai.unfriendly->World.Y;
				target.Z = ai.unfriendly->World.Z;
				InterceptandRange (&target);

				CalcLead(*this, *ai.unfriendly,vx,vy,vz, TRUE);

				target.X += vx;
				target.Y += vy;
				target.Z += vz;
				InterceptandRange (&target);

			}
			else
				target = ai.unfriendly->World;

		//DEADCODE CSB 25/01/00 	TurnWithPitchChange(HdgIntercept, TRUE, target);
			if(AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW)
				TurnFightSub(HdgIntercept, FALSE, ANGLES_0Deg, target);
			else
				TurnFightSub(HdgIntercept, TRUE, ANGLES_0Deg, target);
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TunringFightBomber
//Author		Craig Beeston
//Date			Tue 10 Oct 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ACMAirStruc::TurningFightBomber()
{
	switch(ai.ManStep)
	{
		case 0:
		{
			SetManoeuvreTime(1500);
			ai.ManStep = 1;
		}
		case 1:
		{
			AirStrucPtr	unf = AirStrucPtr(ai.unfriendly);
			if(!unf)
			{
				ai.manoeuvre = MANOEUVRE_SELECT;
				return;
			}

			ACMMODEL& ACM = *fly.pAcmModel;
			ACM.Thrust(100);

			if(Distance3DSquared(&unf->World) < FP(INSIDEWEAPONSRANGE) * FP(INSIDEWEAPONSRANGE))
			{
				SLong dx, dy, dz;
				CalcLead(this, unf, dx, dy, dz, FALSE);
				despos.X = unf->World.X + dx;
				despos.Y = unf->World.Y + dy;
				despos.Z = unf->World.Z + dz;
			}
			else
			{
				FP deltas = FP(unf->vel_x) * FP(unf->World.X - World.X) + FP(unf->vel_y) * FP(unf->World.Y - World.Y) + FP(unf->vel_z) * FP(unf->World.Z - World.Z);
				deltas /= FP(unf->vel_);
				FP deltav = FP(vel_x) * FP(unf->vel_x) + FP(vel_y) * FP(unf->vel_y) + FP(vel_z) * FP(unf->vel_z);
				deltav = deltav / FP(unf->vel_) - FP(unf->vel_);
				FP time = 1.25 * deltas / deltav;
				if(deltav < 0)
					time = 0;
				else
					MODMAXMIN(time, 0, 100); 
				despos = unf->World;
				despos.X = FP(despos.X) + time * FP(unf->vel_x);
				despos.Y = FP(despos.Y) + time * FP(unf->vel_y);
				despos.Z = FP(despos.Z) + time * FP(unf->vel_z);
			}
			
			InterceptandRange(&despos);

//DeadCode CSB 12Oct00 			if(Range < INSIDEWEAPONSRANGE)
//DeadCode CSB 12Oct00 			{
//DeadCode CSB 12Oct00 				PitchIntercept -= SByte(timeofday * 2);
//DeadCode CSB 12Oct00 				HdgIntercept   += SByte(timeofday);
//DeadCode CSB 12Oct00 			}
			PitchIntercept += ai.combatskill / 2;
			ACM.Pitch(PitchIntercept);
			SLong desroll = 5 * SWord(HdgIntercept - hdg);
			MODLIMIT(desroll, ANGLES_75_5Deg);
			ACM.FastRoll(desroll);

			if(!TimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}
	
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
void	ACMAirStruc::TurnWithPitchChange(ANGLES	HdgIntercept, Bool sitbehindtarget,COORDS3D	target)
{
//DEADCODE CSB 25/01/00 	if (CombatFactor() > 200)
//DEADCODE CSB 25/01/00 	{
//DEADCODE CSB 25/01/00 		if (classtype->phrasename == PHRASE_MIGS)
//DEADCODE CSB 25/01/00 //DEADCODE RDH 10/05/99 		if (classtype->visible == MIG15)
//DEADCODE CSB 25/01/00 //			TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_5Deg, target);	
//DEADCODE CSB 25/01/00 			TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	
//DEADCODE CSB 25/01/00 		else 
//DEADCODE CSB 25/01/00 		if (World.Y > FT_10000)
//DEADCODE CSB 25/01/00 			TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	
//DEADCODE CSB 25/01/00 		else
//DEADCODE CSB 25/01/00 			TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);	
//DEADCODE CSB 25/01/00 
//DEADCODE CSB 25/01/00 	}else
		TurnFightSub(HdgIntercept, sitbehindtarget, ANGLES_0Deg, target);
}


Bool	ACMAirStruc::BanditOnColdSide()
{
	SWord reqdeltahdg = hdg - HdgIntercept;

	if	(		(reqdeltahdg < ANGLES_90Deg)
			||	(reqdeltahdg > ANGLES_270Deg)
		)	
	{
		return (FALSE);
	}

	if	(	(		(reqdeltahdg > 0)
				&&	(roll << ANGLES_90Deg)
			)
			||
			(		(reqdeltahdg < 0)
				&&	(roll >> ANGLES_270Deg)
			)
		)
		return(TRUE);
	else
		return(FALSE);

}


//DeadCode AMM 21Sep00 Bool	ACMAirStruc::BanditHasLead()
//DeadCode AMM 21Sep00 {
//DeadCode AMM 21Sep00 	return(TRUE);
//DeadCode AMM 21Sep00 }
//
//DeadCode RDH 07Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 07Jan99 //Procedure		SustainedTurn
//DeadCode RDH 07Jan99 //Author		R. Hyde 
//DeadCode RDH 07Jan99 //Date			Fri 13 Mar 1998
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Description	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Inputs		
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //Returns	
//DeadCode RDH 07Jan99 //
//DeadCode RDH 07Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 07Jan99 void	ACMAirStruc::SustainedTurn()
//DeadCode RDH 07Jan99 {
//DeadCode RDH 07Jan99 //done in turning fight
//DeadCode RDH 07Jan99 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HighYoYo
//Author		R. Hyde 
//Date			Wed 11 Mar 1998
//
//Description	Ref1.70
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::HighYoYo()
{
//approach from 30-60 AOT, cospeed
//
//roll wings level
//pull up
//when in rear hemisphere (say near 6 o'clock), closure 0
//	roll towards target then lead or lag pursuit
//
	TurningFight();													  //CB 12/11/99
	return;															  //CB 12/11/99

/*
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (100);
			SetManoeuvreTime (1500);
 			ai.desiredroll = ANGLES_0Deg; 
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.Roll (ai.desiredroll);
			ACM.Pitch (ANGLES_20Deg);

			if  ( !ManoeuvreTimeLeft())
  				ai.manoeuvre = MANOEUVRE_SELECT;

		 	SWord 	deltaroll;
		 	UWord	deltaroll_pos;
 			SWord	deltaroll_sign;

			deltaroll = (SWord) (ai.desiredroll - roll);
  			Math_Lib.Pos (deltaroll,deltaroll_pos,deltaroll_sign);
  			if (		(deltaroll_pos <ANGLES_5Deg)
					&&	((World.Y - ai.unfriendly->World.Y) > FT_100)
				)
 				ai.ManStep = PHASE2;

			break;

		}
		case PHASE2:
		{
			COORDS3D	target;
			Float fpitch,fhdg;
			AirStrucPtr	unfriendly = *ai.unfriendly;
			target = ai.unfriendly->World;


			ANGLES reqroll = roll +  GetRequiredRoll(*(rotitem*)this, (COORDS3D)target, fpitch, fhdg );
			ACM.Roll (reqroll);
			ACM.Pitch (ANGLES_20Deg);

			if (TargetOnSubjectTail(ANGLES_85Deg))
			{
				ai.manoeuvre = MANOEUVRE_TURNINGFIGHT;
				ai.ManStep = PHASE0;
			}
		}
	}
*/

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Zoom
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
void ACMAirStruc::Zoom()
{
	ACMMODEL& ACM = *fly.pAcmModel;

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			SetManoeuvreTime(1500);
			ACM.Thrust(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.VelPitch(ANGLES_45Deg);
			SWord desroll = 0;
			if(ai.unfriendly)
				desroll = SWord(HdgIntercept - hdg);
			MODLIMIT(desroll, ANGLES_45Deg);
			ACM.FastRoll(desroll);

			if(		(!TimeLeft())
				||	((ai.unfriendly) && (World.Y > ai.unfriendly->World.Y + FT_1000))
				||	(vel_ < (3 * classtype->minvel) / 2)	)
			{
				if(ShouldGoHome())
				{
					ai.manoeuvre = MANOEUVRE_SELECT;
					ai.firsttactic = TACTIC_NULL;
					return;
				}

				if(ai.firsttactic == TACTIC_LINEABREAST)
 					ai.manoeuvre = MANOEUVRE_LINEABREAST;
 				else if(ai.firsttactic == TACTIC_LINEASTERN)
 					ai.manoeuvre = MANOEUVRE_LINEASTERN;
 				else if(ai.firsttactic == TACTIC_DIVEANDZOOM)
 					ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
				else
					ai.manoeuvre = MANOEUVRE_SELECT;
			}
		}
	}

//DeadCode CSB 7Sep00 //roll wings nearly level
//DeadCode CSB 7Sep00 //pull up then zoom climb for x secs or near stall
//DeadCode CSB 7Sep00 //roll 180 and pull level
//DeadCode CSB 7Sep00 //
//DeadCode CSB 7Sep00 //
//DeadCode CSB 7Sep00 		ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode CSB 7Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 //	ACM.Step = ai.ManStep;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 	switch (ai.ManStep)
//DeadCode CSB 7Sep00 	{
//DeadCode CSB 7Sep00 		case PHASE0:
//DeadCode CSB 7Sep00 		{
//DeadCode CSB 7Sep00 			SetManoeuvreTime (2000);
//DeadCode CSB 7Sep00 			MOD.Rudder = 0;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			ACM.Thrust (100);			//rdh
//DeadCode CSB 7Sep00 //			ACM.ClimbRate (0);
//DeadCode CSB 7Sep00 //			ACM.KeepWingsLevel ();
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 7Sep00 			break;
//DeadCode CSB 7Sep00 		}
//DeadCode CSB 7Sep00 		case PHASE1:
//DeadCode CSB 7Sep00 		{
//DeadCode CSB 7Sep00 				ACM.FastRoll (ANGLES_0Deg);
//DeadCode CSB 7Sep00 				ACM.Pitch (ANGLES_40Deg);
//DeadCode CSB 7Sep00 			
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 			if  (		(!ManoeuvreTimeLeft ())
//DeadCode CSB 7Sep00 					||
//DeadCode CSB 7Sep00 						(vel_ <= CornerSpeed())
//DeadCode CSB 7Sep00 				)
//DeadCode CSB 7Sep00 			{
//DeadCode CSB 7Sep00 //DEADCODE CB 18/11/99  				if (ai.firsttactic == TACTIC_ROUNDABOUT)
//DeadCode CSB 7Sep00 //DEADCODE CB 18/11/99  					ai.manoeuvre = MANOEUVRE_ROUNDABOUT;
//DeadCode CSB 7Sep00 //DEADCODE CB 18/11/99  				else 
//DeadCode CSB 7Sep00 				if (ai.firsttactic == TACTIC_LINEABREAST)
//DeadCode CSB 7Sep00  					ai.manoeuvre = MANOEUVRE_LINEABREAST;
//DeadCode CSB 7Sep00  				else if (ai.firsttactic == TACTIC_LINEASTERN)
//DeadCode CSB 7Sep00  					ai.manoeuvre = MANOEUVRE_LINEASTERN;
//DeadCode CSB 7Sep00  				else if (ai.firsttactic == TACTIC_DIVEANDZOOM)
//DeadCode CSB 7Sep00 					ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;					
//DeadCode CSB 7Sep00 				else
//DeadCode CSB 7Sep00 					ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 7Sep00 
//DeadCode CSB 7Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 7Sep00 			}
//DeadCode CSB 7Sep00 			break;
//DeadCode CSB 7Sep00 		}
//DeadCode CSB 7Sep00 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LowYoYo
//Author		R. Hyde 
//Date			Tue 3 Mar 1998
//
//Description	Ref1.73	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 21Sep00 void	ACMAirStruc::LowYoYo ( )
//DeadCode AMM 21Sep00 {
//DeadCode AMM 21Sep00 //used when closure is insufficient
//DeadCode AMM 21Sep00 //
//DeadCode AMM 21Sep00 //in turning fight, attacker increases horizontal component of turn rate by nose down
//DeadCode AMM 21Sep00 //lead target
//DeadCode AMM 21Sep00 //level wings and pull up
//DeadCode AMM 21Sep00 //
//DeadCode AMM 21Sep00 //Note may have to write so that the ac doesn't try to get advantage in one 
//DeadCode AMM 21Sep00 //manoeuvre (see btm 1.73)
//DeadCode AMM 21Sep00 //
//DeadCode AMM 21Sep00 //
//DeadCode AMM 21Sep00 //
//DeadCode AMM 21Sep00 //Note can also be used when in tailchase to pick up speed to get just inside gun range
//DeadCode AMM 21Sep00 //
//DeadCode AMM 21Sep00 //
//DeadCode AMM 21Sep00 	TurningFight();													  //CB 12/11/99
//DeadCode AMM 21Sep00 	return;															  //CB 12/11/99
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 /*
//DeadCode AMM 21Sep00 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode AMM 21Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode AMM 21Sep00 	SWord	reqdeltahdg,reqdeltahdg_sign;
//DeadCode AMM 21Sep00 	UWord	reqdeltahdg_pos;
//DeadCode AMM 21Sep00 	COORDS3D	target;
//DeadCode AMM 21Sep00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode AMM 21Sep00 	SLong		time;
//DeadCode AMM 21Sep00 	SWord	reqdeltapitch,reqdeltapitch_sign;
//DeadCode AMM 21Sep00 	UWord	reqdeltapitch_pos;
//DeadCode AMM 21Sep00 	SLong dx;
//DeadCode AMM 21Sep00 	SLong dy;
//DeadCode AMM 21Sep00 	SLong dz;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 	switch (ai.ManStep)
//DeadCode AMM 21Sep00 	{
//DeadCode AMM 21Sep00 		case PHASE0:
//DeadCode AMM 21Sep00 		{
//DeadCode AMM 21Sep00 			MOD.Rudder = 0;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			ACM.Thrust (ThrustfromFF());
//DeadCode AMM 21Sep00 			SetManoeuvreTime (1500);
//DeadCode AMM 21Sep00 			ai.ManStep = PHASE1;
//DeadCode AMM 21Sep00 		}
//DeadCode AMM 21Sep00 		case PHASE1:
//DeadCode AMM 21Sep00 		{
//DeadCode AMM 21Sep00 			CalcLead(*this, *ai.unfriendly,dx,dy,dz, TRUE);
//DeadCode AMM 21Sep00 		
//DeadCode AMM 21Sep00 			target.X = ai.unfriendly->World.X + dx;
//DeadCode AMM 21Sep00 			target.Y = ai.unfriendly->World.Y + dy;
//DeadCode AMM 21Sep00 			target.Z = ai.unfriendly->World.Z + dz;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			SWord c,s;
//DeadCode AMM 21Sep00 			ANGLES	depression = ANGLES_340Deg;
//DeadCode AMM 21Sep00 			Math_Lib.high_sin_cos(depression,s,c);
//DeadCode AMM 21Sep00 			SLong deltay = MULSHSIN(s, Range,ANGLES_SHIFT);
//DeadCode AMM 21Sep00 			SLong range = Range - WEAPONSRANGE;
//DeadCode AMM 21Sep00 			if (range < 0)
//DeadCode AMM 21Sep00 				range = 0;
//DeadCode AMM 21Sep00 			if (range > ENGAGERANGE)
//DeadCode AMM 21Sep00 				range = ENGAGERANGE;
//DeadCode AMM 21Sep00 			deltay = deltay * range /ENGAGERANGE;
//DeadCode AMM 21Sep00 			target.Y += deltay;
//DeadCode AMM 21Sep00 //			depression = ANGLES_0Deg;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			InterceptandRange (&target);
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 //DeadCode RDH 16Dec98 			TurnFightSub(HdgIntercept, TRUE, ANGLES_0Deg, target);	
//DeadCode AMM 21Sep00 			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 //			ACM.MinHeight (FT_2000);
//DeadCode AMM 21Sep00 //DEADCODE RDH 27/05/99 			if (TooLow())
//DeadCode AMM 21Sep00 //DEADCODE RDH 27/05/99 				{
//DeadCode AMM 21Sep00 //DEADCODE RDH 27/05/99 					ai.ManStep = PHASE0;
//DeadCode AMM 21Sep00 //DEADCODE RDH 27/05/99 					ai.manoeuvre = MANOEUVRE_LOWALT;
//DeadCode AMM 21Sep00 //DEADCODE RDH 27/05/99 				}
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			if  (!ManoeuvreTimeLeft())
//DeadCode AMM 21Sep00 			{
//DeadCode AMM 21Sep00 				if (Range > INSIDEWEAPONSRANGE)
//DeadCode AMM 21Sep00 				{
//DeadCode AMM 21Sep00 					if (		(Math_Lib.rnd(2))
//DeadCode AMM 21Sep00 							&&	(vel_ > unfriendly->vel_)
//DeadCode AMM 21Sep00 						)
//DeadCode AMM 21Sep00 						ai.ManStep = PHASE0;
//DeadCode AMM 21Sep00 					else
//DeadCode AMM 21Sep00 						ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode AMM 21Sep00 				}else
//DeadCode AMM 21Sep00 				{
//DeadCode AMM 21Sep00 					 ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode AMM 21Sep00 				}
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			}
//DeadCode AMM 21Sep00 		}
//DeadCode AMM 21Sep00 	}
//DeadCode AMM 21Sep00 */
//DeadCode AMM 21Sep00 }
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptHigh
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
void ACMAirStruc::InterceptHigh()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case 0:
		{
			ACM.Thrust(100);
			SetManoeuvreTime(1500);
			ai.ManStep = 1;
		}
		case 1:
		{
//DeadCode CSB 3Nov00 			despos = ai.unfriendly->World;
//DeadCode CSB 3Nov00 			despos.Y += FT_500;
//DeadCode CSB 3Nov00 			InterceptandRange(&despos);
			SWord dhdg = HdgIntercept - hdg;
			if(dhdg < 0)	dhdg = -dhdg;
			PitchIntercept += Angles(dhdg / 4);
			
			ACM.Pitch(PitchIntercept);

			FP desroll = FindRequiredRoll (hdg - HdgIntercept, CombatReqBankData);
//DeadCode CSB 3Nov00 			MODLIMIT(desroll, ANGLES_60Deg);
			ACM.FastRoll(desroll);

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}

//DeadCode CSB 4Sep00 //intercept but stay at alt
//DeadCode CSB 4Sep00 //
//DeadCode CSB 4Sep00 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode CSB 4Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode CSB 4Sep00 	SWord	reqdeltahdg,reqdeltahdg_sign;
//DeadCode CSB 4Sep00 	UWord	reqdeltahdg_pos;
//DeadCode CSB 4Sep00 	COORDS3D	target;
//DeadCode CSB 4Sep00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 4Sep00 	SLong		time;
//DeadCode CSB 4Sep00 	SWord	reqdeltapitch,reqdeltapitch_sign;
//DeadCode CSB 4Sep00 	UWord	reqdeltapitch_pos;
//DeadCode CSB 4Sep00 	SLong dx;
//DeadCode CSB 4Sep00 	SLong dy;
//DeadCode CSB 4Sep00 	SLong dz;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 	switch (ai.ManStep)
//DeadCode CSB 4Sep00 	{
//DeadCode CSB 4Sep00 		case PHASE0:
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			MOD.Rudder = 0;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			ACM.Thrust (ThrustfromFF());
//DeadCode CSB 4Sep00 			SetManoeuvreTime (15000);
//DeadCode CSB 4Sep00 			ai.ManStep = PHASE1;
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 		case PHASE1:
//DeadCode CSB 4Sep00 		{
//DeadCode CSB 4Sep00 			CalcLead(*this, *ai.unfriendly,dx,dy,dz, TRUE);
//DeadCode CSB 4Sep00 		
//DeadCode CSB 4Sep00 			target.X = ai.unfriendly->World.X + dx;
//DeadCode CSB 4Sep00 			target.Y = World.Y;
//DeadCode CSB 4Sep00 			target.Z = ai.unfriendly->World.Z + dz;
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			InterceptandRange (&target);
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			SLong deltaalt = World.Y - ai.unfriendly->World.Y;
//DeadCode CSB 4Sep00 			if (deltaalt < 0)
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00 			if  (!ManoeuvreTimeLeft())
//DeadCode CSB 4Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode CSB 4Sep00 	
//DeadCode CSB 4Sep00 			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 			if  (		((Range - deltaalt ) < DANGERRANGE)
//DeadCode CSB 4Sep00 					&&	 (SubjectOnTargetTail(ANGLES_45Deg))
//DeadCode CSB 4Sep00 					&&	(SubjectFacingTarget(ANGLES_45Deg))
//DeadCode CSB 4Sep00 				)
//DeadCode CSB 4Sep00 			{
//DeadCode CSB 4Sep00 				 ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
//DeadCode CSB 4Sep00 			}
//DeadCode CSB 4Sep00 
//DeadCode CSB 4Sep00 		}
//DeadCode CSB 4Sep00 	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterceptLow
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
void ACMAirStruc::InterceptLow()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	switch(ai.ManStep)
	{
		case 0:
		{
			ACM.Thrust(100);
			SetManoeuvreTime(1500);
			ai.ManStep = 1;
		}
		case 1:
		{
//DeadCode CSB 3Nov00 			despos = ai.unfriendly->World;
//DeadCode CSB 3Nov00 			despos.Y -= FT_500;
//DeadCode CSB 3Nov00 			InterceptandRange(&despos);
			SWord dhdg = HdgIntercept - hdg;
			if(dhdg < 0)	dhdg = -dhdg;
			PitchIntercept += Angles(dhdg / 4);

			ACM.Pitch(PitchIntercept);

			FP desroll = FindRequiredRoll (hdg - HdgIntercept, CombatReqBankData);
//DeadCode CSB 3Nov00 			MODLIMIT(desroll, ANGLES_60Deg);
			ACM.FastRoll(desroll);

			if(!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbAtSustainedTurnSpeed
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
//DeadCode AMM 21Sep00 void	ACMAirStruc::ClimbAtSustainedTurnSpeed()
//DeadCode AMM 21Sep00 {
//DeadCode AMM 21Sep00 //climb but don't go below sustained turn speed
//DeadCode AMM 21Sep00 //aim towards unfriendly plus offset = f(desiredrange,desiredhdg)
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 //very similar to gainheight at present
//DeadCode AMM 21Sep00 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode AMM 21Sep00 	MODEL& MOD = *fly.pModel;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 	switch (ai.ManStep)
//DeadCode AMM 21Sep00 	{
//DeadCode AMM 21Sep00 		case PHASE0:
//DeadCode AMM 21Sep00 		{
//DeadCode AMM 21Sep00 			MOD.Rudder = 0;
//DeadCode AMM 21Sep00 			SetManoeuvreTime (2000);
//DeadCode AMM 21Sep00 			ACM.GearUp ();
//DeadCode AMM 21Sep00 			ACM.Thrust (ThrustfromFF());
//DeadCode AMM 21Sep00 			if (ai.combatskill > SKILL_REGULAR)
//DeadCode AMM 21Sep00 			{
//DeadCode AMM 21Sep00 				SWord	reqdeltahdg;
//DeadCode AMM 21Sep00 				reqdeltahdg = 	hdg - HdgIntercept;
//DeadCode AMM 21Sep00 				if (reqdeltahdg > 0)
//DeadCode AMM 21Sep00 					ai.desiredhdg = HdgIntercept + ANGLES_20Deg;
//DeadCode AMM 21Sep00 				else
//DeadCode AMM 21Sep00 					ai.desiredhdg = HdgIntercept - ANGLES_20Deg;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			}
//DeadCode AMM 21Sep00 			else
//DeadCode AMM 21Sep00 				ai.desiredhdg = HdgIntercept;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 //			ACM.ClimbRate (-1500);
//DeadCode AMM 21Sep00 			ai.ManStep = PHASE1;
//DeadCode AMM 21Sep00 		}
//DeadCode AMM 21Sep00 		case PHASE1:
//DeadCode AMM 21Sep00 		{
//DeadCode AMM 21Sep00 //			ACM.SpeedWithElevators(0.61);
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			ACM.Roll (ANGLES_0Deg);
//DeadCode AMM 21Sep00 	
//DeadCode AMM 21Sep00 //			MoveToHdg (ai.desiredhdg);
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			if (MOD.Inst.I_MachNo > 0.55)
//DeadCode AMM 21Sep00 				ACM.VelPitch (BestClimbAngle());
//DeadCode AMM 21Sep00 			else
//DeadCode AMM 21Sep00 				ACM.Pitch (ANGLES_355Deg);
//DeadCode AMM 21Sep00 //			if (MOD.Inst.MachNo < 0.4)
//DeadCode AMM 21Sep00 //			if (vel <= SustainedTurnSpeed())
//DeadCode AMM 21Sep00 //				ACM.Pitch (ANGLES_355Deg);
//DeadCode AMM 21Sep00 //			else
//DeadCode AMM 21Sep00 //				ACM.Pitch (ANGLES_5Deg);
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			if (!ManoeuvreTimeLeft())
//DeadCode AMM 21Sep00 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode AMM 21Sep00 			break;
//DeadCode AMM 21Sep00 		}
//DeadCode AMM 21Sep00 	}
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SpinRecovery
//Author		R. Hyde 
//Date			Wed 21 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::SpinRecovery ()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;
	FP rotvelymod;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust (100);

			SetManoeuvreTime (200);

			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			MOD.Elevator = 0;
			MOD.Aileron = 0;
			if (MOD.RotVel.y > 0)
			{
				MOD.Rudder = +MAXRUDDER;
			}else
			{
				MOD.Rudder = -MAXRUDDER;
			}

			MOD.RotVel.y = 0.95 * MOD.RotVel.y;
			rotvelymod =  MOD.RotVel.y;
			if (rotvelymod < 0)
				rotvelymod = - rotvelymod;

			if  (rotvelymod < 0.0005)
				ai.ManStep = PHASE2;
			break;
				
		}
		case PHASE2:
		{
			MOD.Rudder = 0;
			MOD.RotVel.y = MOD.RotVel.y/2;		//at this stage we want spin to definitely stop
			rotvelymod =  MOD.RotVel.y;
			if (rotvelymod < 0)
				rotvelymod = - rotvelymod;
			if  (rotvelymod > 0.0005)
				ai.ManStep = PHASE1;
			ACM.FastRoll (ANGLES_0Deg);
			ACM.Pitch (ANGLES_5Deg + pitch);
			if (	(pitch >> ANGLES_340Deg)
					||
					(pitch << ANGLES_90Deg)
				)
				ai.manoeuvre = MANOEUVRE_SELECT;
		}
	}
}

//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		BounceFollower
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Tue 10 Sep 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void	ACMAirStruc::BounceFollower()
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	COORDS3D	target;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	switch (ai.ManStep)
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	{
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		case PHASE0:
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		{
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98  			MoveToThrust (100);
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			SetManoeuvreTime (1500);
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			ai.ManStep = PHASE1;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			break;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		}
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		case PHASE1:
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		{
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			if (!ManoeuvreTimeLeft())
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			{
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 				ai.manoeuvre = MANOEUVRE_SELECT;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			}
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			target.X = follower->World.X;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			target.Y = follower->World.Y;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			target.Z = follower->World.Z;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			TightTurnSub (FT_1000,target);
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 			break;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		}
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	}
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GainSpeed()
//Author		R. Hyde 
//Date			Tue 10 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::GainSpeed()
{
	ACMMODEL& ACM = *fly.pAcmModel;
	MODEL& MOD = *fly.pModel;

//	ACM.Step = ai.ManStep;

	switch (ai.ManStep)
	{
		case PHASE0:
		{
			MOD.Rudder = 0;
			SWord reqdeltahdg = 	hdg - HdgIntercept;
			ACM.Thrust (ThrustfromFF());
			if (reqdeltahdg > 0)
				ai.desiredroll = ANGLES_330Deg;
			else
				ai.desiredroll = ANGLES_30Deg;

			SetManoeuvreTime (500);
			ACM.GearUp ();
			ACM.Thrust (ThrustfromFF());
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
//DEADCODE CSB 04/05/00 			if (classtype->phrasename == OLDPHRASE_MIGS)
//DEADCODE CSB 04/05/00 //DEADCODE RDH 10/05/99 			if (classtype->visible == MIG15)
//DEADCODE CSB 04/05/00 				ACM.Pitch (ANGLES_3Deg);
//DEADCODE CSB 04/05/00 			else
				ACM.Pitch (ANGLES_355Deg);
			ACM.FastRoll (ai.desiredroll);

			if (!ManoeuvreTimeLeft())
				ai.manoeuvre = MANOEUVRE_SELECT;
			break;
		}
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LeadUnFriendly
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
//DeadCode AMM 21Sep00 void	ACMAirStruc::LeadUnFriendly ()
//DeadCode AMM 21Sep00 {
//DeadCode AMM 21Sep00 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00  	COORDS3D	target;
//DeadCode AMM 21Sep00  	SLong		t,actualrange;
//DeadCode AMM 21Sep00  	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode AMM 21Sep00  
//DeadCode AMM 21Sep00  //			target.X = ai.unfriendly->World.X;
//DeadCode AMM 21Sep00  //			target.Y = ai.unfriendly->World.Y;
//DeadCode AMM 21Sep00  //			target.Z = ai.unfriendly->World.Z;
//DeadCode AMM 21Sep00  //			InterceptandRange (&target);
//DeadCode AMM 21Sep00  			actualrange = Range;
//DeadCode AMM 21Sep00  
//DeadCode AMM 21Sep00  			//clofg velocity
//DeadCode AMM 21Sep00  			SLong deltax = vel_x - unfriendly->vel_x;
//DeadCode AMM 21Sep00  			SLong deltay = vel_y - unfriendly->vel_y;
//DeadCode AMM 21Sep00  			SLong deltaz = vel_z - unfriendly->vel_z;
//DeadCode AMM 21Sep00  			Math_Lib.Intercept (deltax,deltay,deltaz,Range,HdgIntercept,PitchIntercept);
//DeadCode AMM 21Sep00  			//Range is a velocity in 1/10000m/s
//DeadCode AMM 21Sep00  			if (Range != 0)
//DeadCode AMM 21Sep00  			{
//DeadCode AMM 21Sep00  				t = actualrange / (Range * 10000);
//DeadCode AMM 21Sep00  			}else
//DeadCode AMM 21Sep00  			{
//DeadCode AMM 21Sep00  				t = 0;
//DeadCode AMM 21Sep00  			}
//DeadCode AMM 21Sep00  			//when a long way off don't attempt to lead
//DeadCode AMM 21Sep00  			if (t >20000)
//DeadCode AMM 21Sep00  			t = 0;
//DeadCode AMM 21Sep00  
//DeadCode AMM 21Sep00  			target.X = ai.unfriendly->World.X + (unfriendly->vel_x * t / 10000);
//DeadCode AMM 21Sep00  			target.Y = ai.unfriendly->World.Y + (unfriendly->vel_y * t / 10000);
//DeadCode AMM 21Sep00  			target.Z = ai.unfriendly->World.Z + (unfriendly->vel_z * t / 10000);
//DeadCode AMM 21Sep00  			InterceptandRange (&target);
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			TurnFightPhase1(HdgIntercept, TRUE, ANGLES_0Deg, target);
//DeadCode AMM 21Sep00 
//DeadCode AMM 21Sep00 			Range = actualrange;
//DeadCode AMM 21Sep00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CollisionAvoidance
//Author		Craig Beeston
//Date			Thu 03 Feb 2000
//
//Description	Moves to desired heading and pitch for 1 sec to avoid a collision
//				Then returns to previous unfriendly
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::CollisionAvoidance()
{
	ACMMODEL& ACM = *fly.pAcmModel;

	switch(ai.ManStep)
	{
		case PHASE0:
		{
			ACM.Thrust(100);
			ai.ManStep = PHASE1;
		}
		case PHASE1:
		{
			ACM.VelPitch(ai.desiredpitch);

			SWord deltapitch = SWord(ai.desiredpitch - pitch);
			if(deltapitch < 0) deltapitch *= -1;

			SWord reqroll = FindRequiredRoll(hdg - ai.desiredhdg, CombatReqBankData);
			SWord maxroll = ANGLES_90Deg - 2 * deltapitch;

			MODLIMIT(reqroll, maxroll);
			ACM.FastRoll(reqroll);

			if(!TimeLeft())
			{
				if(ShouldGoHome())
					ai.manoeuvre = MANOEUVRE_DISENGAGED;
				else if(ai.firsttactic == TACTIC_DIVEANDZOOM)
					ai.manoeuvre = MANOEUVRE_DIVEANDZOOM;
				else if(ai.firsttactic == TACTIC_HEADONATTACK)
					ai.manoeuvre = MANOEUVRE_HEADONATTACK;
				else if(ai.firsttactic == TACTIC_LINEABREAST)
					ai.manoeuvre = MANOEUVRE_LINEABREAST;
				else if(ai.firsttactic == TACTIC_LINEASTERN)
					ai.manoeuvre = MANOEUVRE_LINEASTERN;
				else if(ai.firsttactic == TACTIC_VICATTACK)
					ai.manoeuvre = MANOEUVRE_VICATTACK;
				else
					ai.manoeuvre = MANOEUVRE_SELECT;
			}
		}
	}
}


//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		GatherSpeed
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Fri 15 Mar 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void	ACMAirStruc::GatherSpeed ()
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 	ACMMODEL& ACM = *fly.pAcmModel;
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99  	COORDS3D	target;
//DeadCode RDH 05Jan99  
//DeadCode RDH 05Jan99 // 		target.X = ai.unfriendly->World.X;
//DeadCode RDH 05Jan99  //		target.Y = ai.unfriendly->World.Y;
//DeadCode RDH 05Jan99  //		target.Z = ai.unfriendly->World.Z;
//DeadCode RDH 05Jan99  //		InterceptandRange (&target);
//DeadCode RDH 05Jan99  		ACM.Pitch (ANGLES_340Deg);
//DeadCode RDH 05Jan99   		MoveToHdg (HdgIntercept);
//DeadCode RDH 05Jan99 }
//DeadCode RDH 05Jan99 



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllButLdrNotOnCombat
//Author		R. Hyde 
//Date			Mon 11 Nov 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::AllButLdrNotOnCombat ()

{
	AirStrucPtr		ac,leadac;	
	if (formpos == 0)
	{//leader
		ac = *this;
	}else
	{
		ac = fly.leadflight;
	}
	leadac =ac;
	do
	{
		do
		{
			if  (	(ac->movecode==AUTO_COMBAT)
				&&  (	(ac->ai.manoeuvre != MANOEUVRE_TOPCOVER)
					&&	(ac->ai.manoeuvre != MANOEUVRE_LOOKROUND)
					&&	(ac->ai.manoeuvre != MANOEUVRE_DIVEFORHOME)	
					&&	(ac->ai.manoeuvre != MANOEUVRE_CLIMBFORHOME)
					&&	(ac->ai.manoeuvre != MANOEUVRE_STRAIGHTDIVE)
					&&	(ac->ai.manoeuvre != MANOEUVRE_GOHOME )		
					&&	(ac->ai.manoeuvre != MANOEUVRE_WELDEDWINGMAN )		//rdh 25/6/99
					)
				&&
					(formpos != 0)
				)
				return (FALSE);
			ac = *ac->Follower();
		}
		while (ac);
	leadac = *leadac->fly.nextflight;
	ac = leadac;
	}
	while (leadac);
	return (TRUE);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllOnTopCover
//Author		R. Hyde 
//Date			Mon 19 Aug 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ACMAirStruc::AllOnTopCover ()

{
	AirStrucPtr		ac,leadac;	
	if (formpos == 0)
	{//leader
		ac = *this;
	}else
	{
		ac = fly.leadflight;
	}
	leadac =ac;

	do
	{
		do
		{
			if (	ac->movecode==AUTO_COMBAT
				&&	ac->ai.manoeuvre != MANOEUVRE_TOPCOVER
				&&  (InterceptandRange(ac),Range<METRES4000)
				)
				return (FALSE);
			ac = *ac->Follower();
		}
		while (ac);
	leadac = *leadac->fly.nextflight;
	ac = leadac;
	}
	while (leadac);
	return (TRUE);

}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClimbAtBestSpeed
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
void	ACMAirStruc::ClimbAtBestSpeed ()
{
//DeadCode RDH 26Mar98 			MoveToPitch (ANGLES_10Deg,2);

}

//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		TightClimbingTurn
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Sat 30 Mar 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void	ACMAirStruc::TightClimbingTurn (ANGLES desiredpitch)
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 	SWord	deltapitch;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		deltapitch = desiredpitch - fly.cpitch;
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		PitchIntercept = desiredpitch; 
//DeadCode RDH 05Jan99 //DeadCode RDH 26Mar98 		TightTurnSubSub (deltapitch);
//DeadCode RDH 05Jan99 
//DeadCode RDH 05Jan99 }
//DeadCode RDH 05Jan99 


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoShoot
//Author		R. Hyde 
//Date			Fri 12 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ACMAirStruc::AutoShoot (Bool manual)
{
	if((ai.unfriendly == NULL) || (AirStrucPtr(ai.unfriendly)->nationality == nationality))
		return;

	AirStrucPtr unf = AirStrucPtr(ai.unfriendly);
	FP velx = vel_x;
	FP vely = vel_y;
	FP velz = vel_z;

	COORDS3D trg = unf->World;
	FP dotprod = velx * FP(trg.X - World.X) + vely * FP(trg.Y - World.Y) + velz * FP(trg.Z - World.Z);
	if(dotprod < 0)		// 90 degree cone
		return;

	FP range = Distance3D(&World, &trg);
	int maxrange = WEAPONSRANGE;
//DeadCode CSB 17Aug00 	if(unf->movecode == AUTO_COMBAT)
//DeadCode CSB 17Aug00 		maxrange = INSIDEWEAPONSRANGE;	
	if(range > maxrange)
		return;

	if(dotprod < 0.9 * FP(vel_) * range)
		return;			// 26 degree cone

//DeadCode CSB 14Aug00 	FP muzvel = classtype->muzzlevel;
//DeadCode CSB 14Aug00 	FP dt = range / (FP(vel_ - unf->vel_) + muzvel);
//DeadCode CSB 14Aug00 	trg.X += FP(unf->vel_x) * dt;
//DeadCode CSB 14Aug00 	trg.Y += FP(unf->vel_y) * dt;
//DeadCode CSB 14Aug00 	trg.Z += FP(unf->vel_z) * dt;
	SLong dx, dy, dz;
	Range = range;
	CalcLead(this, unf, dx, dy, dz, FALSE);
	trg.X += dx;
	trg.Y += dy;
	trg.Z += dz;

//DeadCode CSB 7Nov00 	FP targsize = 500;
//DeadCode CSB 7Nov00 	if(unf->classtype->aerobaticfactor == AEROBATIC_MEDIUM)
//DeadCode CSB 7Nov00 		targsize = 750;
//DeadCode CSB 7Nov00 	if(unf->classtype->aerobaticfactor == AEROBATIC_LOW)
//DeadCode CSB 7Nov00 		targsize = 1000;

//DeadCode CSB 25Aug00 	targsize *= 1.25;
	FP targsize = 1000;

	InterceptandRange(&trg);
	FP perror = (SWord(PitchIntercept) - SWord(pitch));
	if(perror < 0)	perror *= -1;
	FP herror = (SWord(HdgIntercept) - SWord(hdg));
	if(herror < 0)	herror *= -1;
	if(herror > perror)	perror = herror;
	perror = perror * Range / 10431.0;

	if(perror < targsize)
		FireABullet(128);			
	else
		if((follower) && (!Math_Lib.rnd(100)))
			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SHOOTHIM, MSG_SHOOTHIM, Follower(), NULL, this));

	if(		(unf->movecode == AUTO_COMBAT) && (unf != Persons2::PlayerGhostAC)
		&&	(Math_Lib.rnd() < 2 * unf->ai.combatskill) && (unf->ai.unfriendly != this)	)
	{
		if(unf->fly.numinsag)
			unf->SetUnfriendly(fly.expandedsag);
		else
			unf->SetUnfriendly(this);
		unf->ai.manoeuvre = MANOEUVRE_SELECT;
		unf->ai.ManStep = 0;
	}

//DeadCode CSB 14Aug00 	COORDS3D bullet = World;
//DeadCode CSB 14Aug00 	
//DeadCode CSB 14Aug00 	Float sinh, cosh, sinp, cosp;
//DeadCode CSB 14Aug00 	Math_Lib.high_sin_cos(hdg, sinh, cosh);
//DeadCode CSB 14Aug00 	Math_Lib.high_sin_cos(pitch, sinp, cosp);
//DeadCode CSB 14Aug00 
//DeadCode CSB 14Aug00 	bullet.X += (velx + muzvel * cosp * sinh) * dt;
//DeadCode CSB 14Aug00 	bullet.Y += (vely + muzvel * sinp		) * dt;
//DeadCode CSB 14Aug00 	bullet.Z += (velz + muzvel * cosp * cosh) * dt;
//DeadCode CSB 14Aug00 
//DeadCode CSB 14Aug00 	FP range2 =		FP(bullet.X - trg.X) * FP(bullet.X - trg.X)
//DeadCode CSB 14Aug00 				+	FP(bullet.Y - trg.Y) * FP(bullet.Y - trg.Y)
//DeadCode CSB 14Aug00 				+	FP(bullet.Z - trg.Z) * FP(bullet.Z - trg.Z);
//DeadCode CSB 14Aug00 
//DeadCode CSB 14Aug00 	if(range2 < targsize * targsize)
//DeadCode CSB 14Aug00 		FireABullet(128);			
//DeadCode CSB 14Aug00 	else
//DeadCode CSB 14Aug00 		if(follower)
//DeadCode CSB 14Aug00 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SHOOTHIM, MSG_SHOOTHIM, Follower(), NULL, this));
//DeadCode CSB 14Aug00 
//DeadCode CSB 14Aug00 PrintVar(40, 10, "Delta %.0f ", FP(FSqrt(range2)));
//DeadCode CSB 14Aug00 	InterceptandRange(&trg);
//DeadCode CSB 14Aug00 	FP perror = (SWord(PitchIntercept) - SWord(pitch));
//DeadCode CSB 14Aug00 	if(perror < 0)	perror *= -1;
//DeadCode CSB 14Aug00 	FP herror = (SWord(HdgIntercept) - SWord(hdg));
//DeadCode CSB 14Aug00 	if(herror < 0)	herror *= -1;
//DeadCode CSB 14Aug00 	if(herror > perror)	perror = herror;
//DeadCode CSB 14Aug00 	herror = herror * range / 10431.0;
//DeadCode CSB 14Aug00 PrintVar(40, 12, "Error %.0f ", FP(herror));

//DeadCode CSB 11Aug00 	SWord FighterRadius = 500;
//DeadCode CSB 11Aug00 	SWord BomberRadius  = 1000;
//DeadCode CSB 11Aug00 	int TARGETSIZE = FighterRadius;
//DeadCode CSB 11Aug00 	if(AirStrucPtr(ai.unfriendly)->classtype->aerobaticfactor == AEROBATIC_LOW)
//DeadCode CSB 11Aug00 		TARGETSIZE = BomberRadius;
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	COORDS3D	target;
//DeadCode CSB 11Aug00 	Float		time;
//DeadCode CSB 11Aug00 	SWord	reqdeltahdg,reqdeltahdg_sign;
//DeadCode CSB 11Aug00 	UWord	reqdeltahdg_pos;
//DeadCode CSB 11Aug00  	SWord	reqdeltapitch;
//DeadCode CSB 11Aug00 	UWord	reqdeltapitch_pos;
//DeadCode CSB 11Aug00 	SWord	reqdeltapitch_sign;
//DeadCode CSB 11Aug00 	AirStrucPtr	unfriendly = *ai.unfriendly;
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 #ifdef PRINT_AI_DATA
//DeadCode CSB 11Aug00 PrintString(60, 0, "   +   ");
//DeadCode CSB 11Aug00 PrintString(60, 1, "-+ o +-");
//DeadCode CSB 11Aug00 PrintString(60, 2, "   +   ");
//DeadCode CSB 11Aug00 #endif
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	target.X = ai.unfriendly->World.X;
//DeadCode CSB 11Aug00 	target.Y = ai.unfriendly->World.Y;
//DeadCode CSB 11Aug00 	target.Z = ai.unfriendly->World.Z;
//DeadCode CSB 11Aug00 	InterceptandRange (&target);
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	int maxrange = WEAPONSRANGE;
//DeadCode CSB 11Aug00 	if(unfriendly->movecode == AUTO_COMBAT)
//DeadCode CSB 11Aug00 		maxrange = INSIDEWEAPONSRANGE;	
//DeadCode CSB 11Aug00 	if(Range > maxrange)
//DeadCode CSB 11Aug00 		return;
//DeadCode CSB 11Aug00 //DeadCode CSB 11Aug00 	else 
//DeadCode CSB 11Aug00 //DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 //DeadCode CSB 11Aug00 		if (ai.unfriendly == Persons2::PlayerGhostAC)
//DeadCode CSB 11Aug00 //DeadCode CSB 11Aug00 			_Miles.SequenceAudible(MOOD_TENSE);
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	SWord MAX_FIRING_CONE = (TARGETSIZE * 10430) / Range;
//DeadCode CSB 11Aug00 		
//DeadCode CSB 11Aug00 	reqdeltahdg = hdg - HdgIntercept;
//DeadCode CSB 11Aug00 	Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);
//DeadCode CSB 11Aug00 	if(reqdeltahdg_pos > 2 * MAX_FIRING_CONE)
//DeadCode CSB 11Aug00 		return;
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	reqdeltapitch = pitch - PitchIntercept;
//DeadCode CSB 11Aug00 	Math_Lib.Pos(reqdeltapitch, reqdeltapitch_pos, reqdeltapitch_sign);
//DeadCode CSB 11Aug00 	if(reqdeltapitch_pos > 2 * MAX_FIRING_CONE)
//DeadCode CSB 11Aug00 		return;
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 //#ifndef PRINT_AI_DATA
//DeadCode CSB 11Aug00 //#define PRINT_AI_DATA
//DeadCode CSB 11Aug00 //#endif
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 #ifdef PRINT_AI_DATA
//DeadCode CSB 11Aug00 PrintString(60, 0, "*Might*");
//DeadCode CSB 11Aug00 PrintString(60, 2, "*Fire!*");
//DeadCode CSB 11Aug00 #endif
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	SLong vx;
//DeadCode CSB 11Aug00 	SLong vy;
//DeadCode CSB 11Aug00 	SLong vz;
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	CalcLead(*this, *ai.unfriendly,vx,vy,vz, FALSE);
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	target.X = ai.unfriendly->World.X + vx;
//DeadCode CSB 11Aug00 	target.Y = ai.unfriendly->World.Y + vy;
//DeadCode CSB 11Aug00 	target.Z = ai.unfriendly->World.Z + vz;
//DeadCode CSB 11Aug00 	InterceptandRange (&target);
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 #ifdef PRINT_AI_DATA
//DeadCode CSB 11Aug00 	PrintVar(0,  3, "T Pitch %.1f ", (FP)(AngleSign(PitchIntercept - pitch) / 182.04) );
//DeadCode CSB 11Aug00 	PrintVar(0,  4, "T Headg %.1f ", (FP)(AngleSign(HdgIntercept - hdg)  / 182.04) );
//DeadCode CSB 11Aug00 	PrintVar(0,  5, "T Range %.1f ", (FP)(Range * 0.01) );
//DeadCode CSB 11Aug00 #endif
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	reqdeltahdg = hdg - HdgIntercept;
//DeadCode CSB 11Aug00 	Math_Lib.Pos(reqdeltahdg, reqdeltahdg_pos, reqdeltahdg_sign);
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	reqdeltapitch = pitch - PitchIntercept;
//DeadCode CSB 11Aug00 	Math_Lib.Pos(reqdeltapitch, reqdeltapitch_pos, reqdeltapitch_sign);
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	SWord AngError = reqdeltahdg_pos;
//DeadCode CSB 11Aug00 	if (reqdeltahdg_pos  < reqdeltapitch_pos)
//DeadCode CSB 11Aug00 	AngError = reqdeltapitch_pos;
//DeadCode CSB 11Aug00 	
//DeadCode CSB 11Aug00 	Float delta = (Range * AngError) / 10431;	//CSB 04/06/99	
//DeadCode CSB 11Aug00 #ifdef PRINT_AI_DATA
//DeadCode CSB 11Aug00 	PrintVar(0, 7, "T Delta %.2f ", (FP)(delta / 100));
//DeadCode CSB 11Aug00 #endif
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 	if(delta < TARGETSIZE)
//DeadCode CSB 11Aug00 	{
//DeadCode CSB 11Aug00 //#pragma warnmsg("*** AUTOSHOOT DISABLED *** //CSB")
//DeadCode CSB 11Aug00 		FireABullet(128);			
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 		if (ai.unfriendly == Persons2::PlayerGhostAC)
//DeadCode CSB 11Aug00 			 _Miles.SequenceAudible(MOOD_DOOMED);
//DeadCode CSB 11Aug00 #ifdef PRINT_AI_DATA
//DeadCode CSB 11Aug00 PrintString(60, 0, "*******");
//DeadCode CSB 11Aug00 PrintString(60, 1, "FIRING!");
//DeadCode CSB 11Aug00 PrintString(60, 2, "*******");
//DeadCode CSB 11Aug00 #endif
//DeadCode CSB 11Aug00 	}
//DeadCode CSB 11Aug00 	else
//DeadCode CSB 11Aug00 	{
//DeadCode CSB 11Aug00 		if (follower)
//DeadCode CSB 11Aug00 			_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_SHOOTHIM, MSG_SHOOTHIM, Follower(), NULL, this));
//DeadCode CSB 11Aug00 
//DeadCode CSB 11Aug00 		if (ai.unfriendly == Persons2::PlayerGhostAC)
//DeadCode CSB 11Aug00 			 _Miles.SequenceAudible(MOOD_DESPERATE);
//DeadCode CSB 11Aug00 	}
//DeadCode CSB 11Aug00 	
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PublicFireABullet
//Author		Craig Beeston 
//Date			Sat 3 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::PublicFireABullet(SWord delaybetweenbursts, Bool isArmed)
{
	FireABullet(delaybetweenbursts,isArmed);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FireABullet
//Author		R. Hyde 
//Date			Sat 13 Jul 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::FireABullet(SWord delaybetweenbursts, Bool isArmed)
{
	//	SWord	timeleft;
	WeapAnimData*	weapon;										//RJS 29Aug96
	SLong			xpos, ypos, zpos;							//RJS 29Aug96
	UWord			index;										//RJS 03Sep96
	ULong			mvel;										//RJS 12Nov99
	UWord			mdelay,mburst;								//RJS 12Nov99
	UWord			theShape;									//RDH 31Jul98

//	timeleft = weap.ShootDelay-Timer_Code.FRAMETIME;//DAW 31Jul96
//DeadCode DAW 24Jun99 	Mono_Text.PrintHexAt(60,15,weap.ShootDelay,4);
//	if (timeleft<0)
	if (weap.ShootDelay <=0)
	{
//done by Robert		Art_Int.PersonalThreat(*ai.unfriendly,this);				//RDH 17Oct96
		WorldStuff*	worldptr = mobileitem::currworld;
		SLong			highestammo = 0;						//RJS 08Sep98
		UWord			indexlist[6];							//RJS 08Sep98
		UWord			indexcnt;								//RJS 08Sep98
		WeapAnimData*	useweapon = NULL;								//RJS 08Sep98
		SLong			usexpos, useypos, usezpos;				//RJS 08Sep98
		ULong			usemvel;								//RJS 12Nov99
		UWord			useindex;								//RJS 08Sep98
		UWord			usemdelay;								//RJS 08Sep98
		UWord			usemburst;								//RJS 08Sep98
		UWord			useShape;								//RJS 08Sep98

//DeadCode RJS 07Jul99  		weap.ShootDelay = delaybetweenbursts;			//rdh

		if(Distance3DSquared(&Persons2::PlayerGhostAC->World) < 10000.0 * 10000.0)	//CSB 20/04/00
			Trans_Obj.PlayGunSound((mobileitem* )this,*worldptr);//RDH 12Jul96

		theShape = BULLET;										//RJS 20Nov98

		SByte bullettype = LT_BULLET;
		indexcnt = 0;

		if((classtype->visible == ME109) || (classtype->visible == ME110))
		{
// digadigadiga (alternate fire)
			bullettype = LT_CANNON;
			for (index = 0; index < 6; index++)						//RJS 16Jun98
			{
				weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,bullettype,&theShape);//RDH 31Jul98
				if (weapon)
				{
					indexlist[indexcnt++] = index;
					if (weapon->LoadedStores > highestammo)
					{
				 		highestammo = weapon->LoadedStores;
						useweapon = weapon;
						usexpos = xpos;
						useypos = ypos;
						usezpos = zpos;
						useindex = index;
						usemdelay = mdelay;
						usemburst = mburst;
						useShape = theShape;
						usemvel = mvel;
					}



						if (this==Persons2::PlayerSeenAC)
						{
							_DPlay.NewBullet(mburst,index);					//RDH 31Jul98
						}
				}
			}
		}

		if(!useweapon)
		{
			bullettype = LT_BULLET;
			for (index = 0; index < 6; index++)						//RJS 16Jun98
			{
				weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,bullettype,&theShape);//RDH 31Jul98
				if (weapon)
				{
					indexlist[indexcnt++] = index;
					if (weapon->LoadedStores > highestammo)
					{
				 		highestammo = weapon->LoadedStores;
						useweapon = weapon;
						usexpos = xpos;
						useypos = ypos;
						usezpos = zpos;
						useindex = index;
						usemdelay = mdelay;
						usemburst = mburst;
						useShape = theShape;
						usemvel = mvel;
					}



						if (this==Persons2::PlayerSeenAC)
						{
							_DPlay.NewBullet(mburst,index);					//RDH 31Jul98
						}
				}
			}
		}

		if (useweapon)
		{
			SLong	i;
			SLong	otherindex = useindex;
			for (i=0; i < indexcnt; i++)
			{
				if (indexlist[i] != useindex)
				{
					otherindex = indexlist[i];
					break;
				}
			}
//DeadCode DAW 24Jun99 #ifdef PRINT_AI_DATA
//DeadCode DAW 24Jun99 	PrintVar(20, 14, "Muz Vel %.1f ", (FP)(usemvel / 10) );
//DeadCode DAW 24Jun99 #endif

//We don't want to shorten the fixed delay time (delaybetweenburst),
// but we might want to extend with respect to the number of transient bullets being launched...
 			SLong	mydelaybetweenbursts = usemburst * usemdelay;		//CSB 20Jun00
 			if (mydelaybetweenbursts > delaybetweenbursts)				//CSB 20Jun00
 				delaybetweenbursts = mydelaybetweenbursts;				//CSB 20Jun00

//DeadCode CSB 20Jun00 			ULong numrealbullets = usemburst / classtype->noGuns;		//CSB 20/04/00
			ULong	numrealbullets = usemburst;							//CSB 20Jun00
			Trans_Obj.LaunchManyGunBullets(	(mobileitem* )this,
		 									usemvel,
		 									numrealbullets,				//CSB 20/04/00
		 									usemdelay,		// delay between each bullet//DAW 29Jul98
		 									useindex,		// left  /  right
		 									otherindex,		// right /  left
		 									(ShapeNum)useShape,	//RJS 08Sep98
		 									usexpos,
		 									useypos,
		 									usezpos,
		 									*worldptr,
		 									ANGLES_0Deg,
											bullettype,
											isArmed);	//RJS 27May99
		 
			//Real number of bullets launched = burst count * faked bullets
			useweapon->LoadedStores -= classtype->noGuns;	//CSB 20Jun00

		 	// store num bullets and index of launcher

			if (this==Persons2::PlayerSeenAC)					//AMM 17Nov98
			{
			 	_DPlay.NewBullet(usemburst,useindex);				//RJS 08Sep98
			}
		}

		weap.ShootDelay = delaybetweenbursts;							//CSB 20Jun00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FireARocket
//Author		Craig Beeston
//Date			Thu 25 Mar 1999
//
//Description	Just Like Fire a Bullet but for rockets
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	AirStruc::FireARocket(SWord delaybetweenbursts,Bool isArmed)	//RJS 27May99
{
	WeapAnimData*	weapon;										//RJS 29Aug96
	SLong			xpos, ypos, zpos;							//RJS 29Aug96
	UWord			index;										//RJS 03Sep96
	ULong			mvel;										//RJS 12Nov99
	UWord			mdelay,mburst;								//RJS 12Nov99
	UWord			theShape;									//RDH 31Jul98

//DeadCode CSB 16Oct00 	Mono_Text.PrintHexAt(60,15,weap.ShootDelay,4);
	if (weap.ShootDelay <=0)
	{
		WorldStuff*	worldptr = mobileitem::currworld;
		SLong			highestammo = 0;						//RJS 08Sep98
		UWord			indexlist[6];							//RJS 08Sep98
		UWord			indexcnt;								//RJS 08Sep98
		WeapAnimData*	useweapon = 0;								//RJS 08Sep98
		SLong			usexpos, useypos, usezpos;				//RJS 08Sep98
		ULong			usemvel;								//RJS 12Nov99
		UWord			useindex;								//RJS 08Sep98
		UWord			usemdelay;								//RJS 08Sep98
		UWord			usemburst;								//RJS 08Sep98
		UWord			useShape;								//RJS 08Sep98

//DeadCode CSB 25/03/99	 		Trans_Obj.PlayGunSound((mobileitem* )this,*worldptr);//RDH 12Jul96
//DeadCode RJS 15Dec99		theShape = ROCKET;										//RJS 20Nov98

		indexcnt = 0;

		// digadigadiga (alternate fire)
		for (index = 0; index < 6; index++)						//RJS 16Jun98
		{
			weapon = SHAPE.GetWeaponLauncher(this,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_ROCKET,&theShape);//RDH 31Jul98	//CSB 25/03/99	
			if (weapon)
			{
				indexlist[indexcnt++] = index;
				if (weapon->LoadedStores > highestammo)
				{
				 	highestammo = weapon->LoadedStores;
					useweapon = weapon;
					usexpos = xpos;
					useypos = ypos;
					usezpos = zpos;
					useindex = index;
					usemdelay = mdelay;
					usemburst = mburst;
					useShape = theShape;
					usemvel = mvel;
				}



					if (this==Persons2::PlayerSeenAC)
					{
						_DPlay.NewBullet(mburst,index);					//RDH 31Jul98
					}
			}
		}

		if (useweapon)
		{
			SLong	i;
			SLong	otherindex = useindex;
			for (i=0; i < indexcnt; i++)
			{
				if (indexlist[i] != useindex)
				{
					otherindex = indexlist[i];
					break;
				}
			}
#ifdef PRINT_AI_DATA
	PrintVar(20, 14, "Muz Vel %.1f ", (FP)(usemvel / 10) );
#endif

			WorldStuff*	worldptr = mobileitem::currworld;
			Trans_Obj.LaunchRocket( (mobileitem*)this,
									(ShapeNum)useShape,
									usexpos, 
									useypos,
									usezpos,			  
									*worldptr);
		 	
//DeadCode CSB 25/03/99				Trans_Obj.LaunchManyGunBullets(	(mobileitem* )this,
//DeadCode CSB 25/03/99			 									usemvel,
//DeadCode CSB 25/03/99			 									usemburst,				// no bullets//RDH 31Jul98
//DeadCode CSB 25/03/99			 									usemdelay,		// delay between each bullet//DAW 29Jul98
//DeadCode CSB 25/03/99			 									useindex,		// left  /  right
//DeadCode CSB 25/03/99			 									otherindex,		// right /  left
//DeadCode CSB 25/03/99			 									(ShapeNum)useShape,	//RJS 08Sep98
//DeadCode CSB 25/03/99			 									usexpos,
//DeadCode CSB 25/03/99			 									useypos,
//DeadCode CSB 25/03/99			 									usezpos,
//DeadCode CSB 25/03/99			 									*worldptr,
//DeadCode CSB 25/03/99			 									ANGLES_0Deg);	//RJS 16Jun98
		 
			useweapon->LoadedStores--;
			weap.ShootDelay = usemdelay;
			

			if (this==Persons2::PlayerSeenAC)					//AMM 17Nov98
			{
			 	_DPlay.NewBullet(usemburst,useindex);				//RJS 08Sep98
			}
		}
	}
//	weap.ShootDelay = timeleft;

}
	
//DeadCode RDH 05Jan99 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 05Jan99 //Procedure		TightTurn
//DeadCode RDH 05Jan99 //Author		R. Hyde 
//DeadCode RDH 05Jan99 //Date			Fri 12 Jul 1996
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Description	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Inputs		
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //Returns	
//DeadCode RDH 05Jan99 //
//DeadCode RDH 05Jan99 //------------------------------------------------------------------------------
//DeadCode RDH 05Jan99 void	ACMAirStruc::TightTurn (SLong recovery_alt)
//DeadCode RDH 05Jan99 {
//DeadCode RDH 05Jan99 }




//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManoeuvreTimeLeft
//Author		R. Hyde 
//Date			Tue 19 Dec 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord	ACMAirStruc::ManoeuvreTimeLeft ()

{
	return(TimeLeft());

}

//------------------------------------------------------------------------------
 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakCallNecessary
//Author		R. Hyde 
//Date			Tue 19 Dec 1995
//
//Description	
//					Horrible code to retain the globals
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ACMAirStruc::WeldedWingSixOK()
{
	bool sixok = true;
	int range = ENGAGERANGE;
	if  ( !ManoeuvreTimeLeft())
	{
		if (ai.attacker)
		{
			if (BreakCallNecessary(this, ai.attacker, range))
			{
				sixok = false;
				MANOEUVRE manoeuvre;
				RndVal	rndnum = Math_Lib.rnd();
				if	(rndnum < RND50PC)
					manoeuvre = MANOEUVRE_BREAKTURN;
				else
					manoeuvre = MANOEUVRE_SPLITS;						  //RDH 15/06/99 //RDH 20/06/99

				Art_Int.SetEngage(this,ai.attacker,manoeuvre,ANGLES_0Deg,ANGLES_0Deg, FALSE);
				if (leader)
					_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_NOTCLEAR, MSG_CLEAR_RPT, *this, NULL, ((AirStrucPtr)leader)));
			}

		}
		if (	(leader)	&&	(((AirStrucPtr)leader)->ai.attacker))
		{
			if (BreakCallNecessary(((AirStrucPtr)leader), ((AirStrucPtr)leader)->ai.attacker, range))
			{
				sixok = false;
//DEADCODE DAW 05/07/99 			   BreakCallandReaction(this, ((AirStrucPtr)leader)->ai.attacker, ((AirStrucPtr)leader));
			   BreakCallandReaction(this, ((AirStrucPtr)leader), ((AirStrucPtr)leader)->ai.attacker); //DAW 05/07/99


			}
		}
		if(sixok)
		{
			int drange = range - DANGERRANGE;
			if (drange < 0)
				drange = 0;
			int time = 200 + drange/100;
			SetManoeuvreTime (time);
		}else
			SetManoeuvreTime (200);
	}
	return(sixok);

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BreakCallNecessary
//Author		R. Hyde 
//Date			Tue 19 Dec 1995
//
//Description	
//					Horrible code to retain the globals
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ACMAirStruc::BreakCallNecessary(AirStrucPtr currac,AirStrucPtr unf, int range)
{
	bool Break = false;
	if (		(currac->ai.unfriendly != unf)
			||	(currac->AcIsPlayer())
		)
	{
  		ANGLES	oldhdgint, oldpitchint;
		SLong	oldrange;
		ANGLES	hdgint;
		oldhdgint = HdgIntercept;
		oldpitchint = PitchIntercept;
		oldrange  = Range;

		Art_Int.InterceptRangeFromTo(currac, unf);
		range = Range;
		if (Range < ENGAGERANGE)		//rdh 13/7(DANGERRANGE+ METRES200)) 
		{
			ANGLES delta = HdgIntercept + ANGLES_180Deg + ANGLES_45Deg - currac->hdg;
			if ((delta) << (ANGLES_90Deg))
				Break = true;
		}
		PitchIntercept = oldpitchint;
		HdgIntercept = oldhdgint;
		Range = oldrange;
	}

	return(Break);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFollowerTactic
//Author		Craig Beeston 
//Date			Mon 5 Jul 1999
//
//Description	Sets the ai.FirstTactic for the whole group
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void AirStruc::SetFollowersTactic(tFirstEncounterTactics TACTIC)
{
	AirStrucPtr Lead, Foll;
	for(Lead = FindGroupLeader(); Lead; Lead = Lead->fly.nextflight)
		for(Foll = Lead; Foll; Foll = Foll->Follower())
			if(Foll->ai.manoeuvre != MANOEUVRE_FORCETOPCOVER)
				Foll->ai.firsttactic = TACTIC;
}
