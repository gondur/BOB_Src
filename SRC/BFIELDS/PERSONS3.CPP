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

//
//	Persons3.cpp
//	This converts the complex info_ objects into simpler
//	individual item and airstruc elements
//
//
	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
	#include	"dosdefs.h"
	#include	"myerror.h"						   
	#include	"worldinc.h"
	#include	"bfnumber.h"
	#include	"bfcommon.h"											//AMM 5Sep00
	#include	"bfnumber.h"	//intensional double include
	//DON'T WRITE INCLUDE FILES HERE, PUT THEM IN BFCOMMON
	#include	"3dcode.h"
	#include	"flyinit.h"
	#include	"viewsel.h"
	#include	"comms.h"
	#include	"replay.h"
	#include	"3dcom.h"
#include	"model.h"
#include "ai.h"
#include "contlist.h"
#include	"globrefs.h"	
#include "nodebob.h"
#include	"sqddiary.h"
#include	"winmove.h"													//RJS 12Oct00

//#define	 REPLAYWPCHECK
//DeadCode JIM 28Mar96 extern	PlaneType&	camel;										//RDH 23Feb96
//Old_Code PD 27Aug96  	MAKEFIELD	(ShapeNum,ShapeNumMIN,ShapeNumMAX);
//	extern	ULong	GR_FriendlyScoutType00;
//	extern	ULong	GR_GlobalSkillMin;
//	extern	ULong	GR_GlobalSkillMax;
//	extern	ULong	GR_CWP,GR_CPP;
//	extern	ULong	GR_EnemyScoutSquad,
//					GR_FriendlyScoutSquad,
//					GR_EnemyChargeSquad,
//					GR_FriendlyChargeSquad,
//					GR_Pack_PlayerSquad,
//					GR_Pack_PlayerPos

					
	extern	ULong	GR_Pack_Sq_Used[PT_GER_NONFLY+1];	//inc Yak
//DEADCODE JIM 09/12/99 	AirStrucPtr	Persons3::migsq[2];
//Nationality		defaultside=NAT_GREEN;

//ItemBasePtr		*Persons2::pItem;


#define EvalOrDefault(field,type,expr,defaultv)				\
		{													\
			int v1;											\
			if ((v1=I.expr.Evaluate())==ENABLE_COMPLEX_VAL)	\
				field=defaultv;								\
			else			   								\
				field=type(v1);								\
		}
#define FormOrDefault(field,type,expr,defaultv)				\
		{													\
			int v1;											\
			if ((v1=I.expr.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)	\
				field=defaultv;								\
			else			   								\
				field=type(v1);								\
		}


CON	Persons3::Persons3(WorldStuff* world,ViewPoint* vp,Inst3d* inst):
	Persons2(world,vp)
{
	inst3d=inst;
	gotgrpnum=1;
//DEADCODE JIM 09/12/99 	migsq[0]=migsq[1]=NULL;
	baseSAGshape=ShapeNum(SAG00-1);
	pilotedaircraft=NULL;
	for (int i=0;i<PT_VEHICLES;	i++)
		instancesSAG[i]=instancesAC[i]=formationleaderflights[i]=0;
	GR_lastroutefirstwaypoint=NULL;
}


Persons3::SagExpansionCounter		Persons3::sagexpcounts[PT_VEHICLES]=
{				 //min, max range
	/*spit A*/	{1, METRES10KM},								//CSB 27Jul00
	/*spit B*/	{1, METRES10KM},								//CSB 27Jul00
	/*hurr A*/	{1, METRES10KM},								//CSB 27Jul00
	/*hurr B*/	{1, METRES10KM},								//CSB 27Jul00
	/*defiant*/	{1, METRES10KM},								//CSB 27Jul00
	/*blen*/	{1, METRES10KM},								//CSB 27Jul00
	/*me 109*/	{1, METRES10KM},								//CSB 27Jul00
	/*me 110*/	{1, METRES10KM},								//CSB 27Jul00
	/*ju 87*/	{1, METRES10KM},								//CSB 27Jul00
	/*bombers*/	{1, METRES5000}									//CSB 27Jul00
	
};
int  Persons3::SagExpansionCounter::highdemandrange;
int  Persons3::SagExpansionCounter::totalexpanded;	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	THESE make_ routines make the actual items in the world
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//Pseudocode time:
//
//Switch (takeoffstate)
//TOS_SIMPLE:
//Simple scenario - works as before
//TOS_INAIR:
//{		//place in approximate location
//		if (can't make ETA to first waypoint + 1 min for takeoff seq)
//			place proportionally on route to first waypoint 
//		else
//		if (is wave leader)
//			try each waypoint in turn until time used up
//			if past engage waypoint
//				dice roll encounter with target
//			if past last waypoint, 
//				place 1 mile north of last waypoint
//			else
//				place proportionally between waypoints
//		else
//			place in formation with leader
//}
//TOS_HOLDING:
//{		//place as far back as possible
//		calc position as TAXI2..TAXI1 * 40m *(20-timemod/15)
//		place on pause until modulo time		(PHASE 0 then PHASE 2, turn, PHASE 5)
//}
//TOS_TAXIING:
//{		//place closer
//		calc position as TAXI1..TAXI2 * 40m *((time-GR)/15)
//		place on "immediate" pause - delayed until player ready	(PHASE 1 then PHASE 2, turn, PHASE 5)
//}
//TOS_TAKENOFF:
//{		//place close to airfield
//		place in formation at altitude between RUNWAY1..RUNWAY0 *100m*(GR-time)/15)
//			pointing towards first waypoint	
//}
//TOS_TAKINGOFF:
//{		//place some just in front 
//		place (GR-time)/15 flights in formation at altitude on RUNWAY1
//			pointing towards first waypoint
//		place 1 flight on TAKEOFFL/TAKEOFFW - should be player's flight
//		place other flights at TAXI0..TAXI1 * 40m *(time-GR)/15 - delay UPR (PHASE 3, PHASE 4 then move to position PHASE 6 common)
//}

//Phases:
//TOS_HOLDING
//0		Hold until time
//TOS_TAXIING
//1		Hold until player gone
//2		Move towards TAXI1 at 40m every 15 seconds On reaching TAXI1, phase 5
//TOS_NEXTFLIGHTS
//3		Hold until player gone
//4		Move towards TAXI0 at 40m every 15 seconds. On reaching TAXI0, phase 6 
//
//5		Move all way to TAXI0 over ?15? seconds. On time up, phase 6
//
//6		Hold for 5 seconds
//		Within 5 seconds
//			1st Elt moves forward to LAUNCHL
//			2nd Elt moves forward to LAUNCHW
//7		Within 5 seconds
//			Both turn and move forward until leader at RUNWAY0 then PHASE 9
//TOS_RUNWAY
//8		Hold until player gone
//9		Take off acceleration up runway towards RUNWAY1
//
//10	Climb straight forward for fixed time
//
//11	Slow turn in formation
////////////////////////////////////////////////////////////////////////
//
// Function:    setpositionMIG
// Date:        21/01/99
// Author:      JIM
//
// Description: LIMITED TO RANGES LESS THAN 640M
//
////////////////////////////////////////////////////////////////////////
inline void	ModifyPosn(Coords3D& c,int range,ANGLES h,ANGLES p)
{
 		SWord	sin_theta,cos_theta;
		SWord	sin_hdg, cos_hdg;

		Math_Lib.high_sin_cos (p,sin_theta,cos_theta);

		int vely = MULSHSIN(range,sin_theta,ANGLES_SHIFT);

		int velhori = MULSHSIN(range,cos_theta,ANGLES_SHIFT);


		Math_Lib.high_sin_cos (h, sin_hdg, cos_hdg);
		int velx =  MULSHSIN(velhori,sin_hdg,ANGLES_SHIFT);
		int velz =   MULSHSIN(velhori,cos_hdg,ANGLES_SHIFT);
		c.X+=velx;
		c.Y+=vely;
		c.Z+=velz;


}

inline ANGLES GetTakeOffOffset(AirStrucPtr currac,Coords3D& startpos,Coords3D& run0)
{
	int position=currac->position();
	Coords3D	posn1,posn2;
	if (!currac->GetTakeOffPos(UniqueID(RunwayEBAND),posn1))
	{	//JAPAN CLUDGE!!! If no takeoff sequence then must be jap rv point so place at altitude
		run0=currac->ai.homebase->World;
		run0.Y=METRES1000;
		startpos.Z=startpos.Y=0;
		startpos.X=-METRES30*position;
		return ANGLES_0Deg;			
	}
	else
	{
		ANGLES h,p;
		SLong range,range2;
		startpos.X=startpos.Y=startpos.Z=0;
		currac->GetTakeOffPos(UniqueID(RunwaySBAND),run0);

		if (position>=2)
		{
			{
				startpos.X=startpos.Y=0;
				startpos.Z=-position*METRES30;
			}
		}
		Math_Lib.Intercept(posn1.X-run0.X,posn1.Y-run0.Y,posn1.Z-run0.Z,range,h,p);
		if (position&1)
		{
			ModifyPosn(startpos,METRES20,h-ANGLES_90Deg,ANGLES_0Deg);
		}
		return h;
	}
}


//////////////////////////////////////////////////////////////////////
//
// Function:    Make3dAC
// Date:		09/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
UniqueID	Persons3::Make3dAC(PlaneTypeSelect type)
{
	AirStruc*	currac=new AirStruc;
	UniqueID rv;
	currac->uniqueID.count=
		rv=
			assignuid(RealAcBAND);
	Persons3::Reset3dAC(currac,type);
	//ColourRulePlayerSquadron
	SHAPE.SetAnimData(currac);
//DEADCODE JIM 15/03/00 	AircraftAnimData*	anim=(AircraftAnimData*)currac->Anim;
//DEADCODE JIM 15/03/00 	anim->imagemapacid1 = 1;							//RJS 11Mar99
//DEADCODE JIM 15/03/00 	anim->imagemapacid2 = 2;							//RJS 11Mar99
//DEADCODE JIM 15/03/00 	anim->imagemapacid3 = 3;							//RJS 11Mar99
	Manual_Pilot.InitManualPilotSub(currac);
	logUID(currac);
	currac->AddToList();
	return rv;
}

void	Persons3::Reset3dAC(AirStruc*	currac,PlaneTypeSelect type)
{
	currac->classtype=Plane_Type_Translate[type][0];
	currac->shape=currac->classtype->visible;
	currac->follower=
		currac->fly.nextflight=NULL;
	currac->leader=
		currac->fly.leadflight=NULL;
	currac->formpos=FormationIndexMIN;
	currac->ai.unfriendly=NULL;
	currac->ai.attacker=NULL;
	currac->ai.homebase=NULL;

//DeadCode CSB 21Aug00 	for (int n=0;n<3;n++)												//AMM 23/02/00
//DeadCode CSB 21Aug00 		currac->ai.secondunfriendly[n]=NULL;							//AMM 23/02/00
	for(int n = 0; n < 4; n++)
		currac->ai.spottedunfriendly[n] = NULL;								//CSB 21Aug00

	currac->duty=PACK_AM_ESCORT;
	currac->ai.submethod=currac->ai.SM_ANYA2A;
	currac->fly.numinsag=0;			 //at this stage it is not a SAG
	currac->fly.expandedsag=NULL;

	currac->sentexpanded=FALSE;									//RJS 15Mar100
	currac->sentcontracted=FALSE;								//RJS 15Mar100

	if (type<PT_GER_FLYABLE)
		currac->nationality=NAT_RED;
	else
		currac->nationality=NAT_BLUE;
	currac->waypoint=NULL;
	currac->information = IF_OUT_POS;								  //CSB 05/01/00
	currac->vel_=0;
	currac->vel_x =0;					
	currac->vel_y =0;					
	currac->vel_z =0;
//DEADCODE JIM 10/12/99 	currac->fly.vel_cms = 	0;
	currac->fly.cpitch = ANGLES_0Deg;		
	currac->fly.aileron = 0;						
	currac->fly.elevator = 0;					
	currac->fly.rudder = 0;						
	currac->weap.ShootDelay=0;
	currac->fly.callname=0;
	currac->fly.callnum=0;
	currac->ai.pilotnum=0;
	currac->roll=
		currac->hdg=
			currac->pitch=
				ANGLES_0Deg;
  	currac->fly.rpm = currac->classtype->maxrpm;									//JIM 21Oct96	//CSB 23/02/00
	currac->fly.thrustpercent = 0;							//JIM 21Oct96	//CSB 23/02/00
	for(SWord i = 0; i < 4; i++)
//DeadCode JIM 24Jul00 		if((currac->classtype->visible == ME109) && (Save_Data.flightdifficulty[FD_109FUEL]))
//DeadCode JIM 24Jul00 			currac->fly.fuel_content[i] = currac->classtype->fueltankcap[i] * 1750;
//DeadCode JIM 24Jul00 		else
			currac->fly.fuel_content[i] = currac->classtype->fueltankcap[i] * 1000;

	currac->ai.manoeuvre=MANOEUVRE_SELECT;
	currac->manoeuvretime=0;									//JIM 11Sep96
	currac->ai.ManStep=PHASE0;								//JIM 11Sep96
	currac->slowdownleader=FALSE;
	currac->information=IF_OUT_POS;									  //CSB 05/01/00

	currac->CommsOwner=UID_NULL;							//AMM 27Nov98
	currac->movecode=AUTO_SPAREAC;										//CSB 14Aug00
	currac->ai.morale=MORALE_MEDIUM;
	currac->ai.radiosilent=FALSE;
	currac->ai.elementtactics = LOOSEDEUCE;
	currac->ai.squadrontactics = LOOSEDEUCE;
	currac->ai.flighttactics = LOOSEDEUCE;
	currac->ai.firsttactic     = TACTIC_NULL;					//CSB 20Jun00

	currac->ai.combatskill=SKILL_MAX;
	currac->ai.eventlog=NULL;
	currac->ai.beenseen = FALSE;
	currac->World.X=0;
	currac->World.Y=0;
	currac->World.Z=0;
	currac->Status.deadtime = 0;										//CSB 8Aug00
	currac->Status.deaded = FALSE;										//CSB 8Aug00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_airgrp
//LastModified:	JIM 29Jul97
//Author		Jim Taylor
//Date			Mon 16 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JIM 09/12/99 static	SByte	Skill_Per_Period[]=
//DEADCODE JIM 09/12/99 //		day0	day1	day2	day3	day4	day5	day6	day7	day8	
//DEADCODE JIM 09/12/99 {22,	0,1,2,	2,3,3,	4,4,4,	5,5,5,	5,4,4,	3,3,2,	2,1,1,	0,0,0};

void	Persons3::make_airgrp(info_airgrp& I)
{

	if (justscanning)
	{
		if (I.uid.Evaluate()>=0)
			 UsedFixedUID=TRUE;
		return;
	}
	UByte		cols[COLS_ALL]={0};
	AirStruc	*firstac=NULL;
	AirStruc	*flleadac=NULL;
	AirStruc	*fllastac=NULL;
//DEADCODE RJS 16/02/00 	int& GR_WaveNum=(int&)::GR_WaveNum;
//DEADCODE JIM 14/01/00 	int		offsetinformationleaderflights;

//DeadCode JIM 20Oct00 	int sqnum=I.squadname.Evaluate();
	Squadron*	squadrec=NULL;
//DEADCODE RJS 15/02/00 	if (sqnum==ENABLE_COMPLEX_VAL)
//DEADCODE RJS 15/02/00 	{
//DEADCODE RJS 15/02/00 		if (I.shape.Evaluate()==ENABLE_COMPLEX_VAL)
//DEADCODE RJS 15/02/00 			if (GR_WaveNum<0)
//DEADCODE RJS 15/02/00 			{
//DEADCODE RJS 15/02/00 				sqnum=-int(GR_WaveNum--);
//DEADCODE RJS 15/02/00 			}
//DEADCODE RJS 15/02/00 			else
//DEADCODE RJS 15/02/00 			{
//DEADCODE RJS 15/02/00 				int grpnum=gotgrpnum;
//DEADCODE RJS 15/02/00 				sqnum=(GR_Scram_Squad[GR_WaveNum-1]>>(grpnum*8))&255;
//DEADCODE RJS 15/02/00 				if (sqnum==0)
//DEADCODE RJS 15/02/00 					sqnum=(GR_Scram_Squad[GR_WaveNum-1])&255;
//DEADCODE RJS 15/02/00 				sqnum++;
//DEADCODE RJS 15/02/00 				sqnum&=127;
//DEADCODE RJS 15/02/00 			}
//DEADCODE RJS 15/02/00 		else
//DEADCODE RJS 15/02/00 			sqnum=0;
//DEADCODE RJS 15/02/00 	}
	int v1;
	if ((v1=I.type.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE RJS 15/02/00 		if (v1>SQ_BR_START)
			squadrec=Node_Data[SquadNum(v1)];

	FormationIndex estformpos=FormationIndexMIN;
//DeadCode JIM 20Oct00 	int	wingcount=0;
	int wingac=I.inwing.Evaluate();
	int	formac=ENABLE_COMPLEX_VAL;
//DEADCODE JIM 06/12/99 	if (wingac==ENABLE_COMPLEX_VAL)
//DEADCODE JIM 06/12/99 	{
//DEADCODE JIM 06/12/99 		_Error.EmitSysErr("Old system for denoting piloted A/C has been binned");
//DEADCODE JIM 06/12/99 	}
//DEADCODE JIM 06/12/99 	else
	{
		formac=I.inform.Evaluate();
	}
	if (wingac==ENABLE_COMPLEX_VAL)
	{	//get wingac from formation
		int	formation=I.form.Evaluate();
		assert(formation!=ENABLE_COMPLEX_VAL && formac !=ENABLE_COMPLEX_VAL);
		formation=(formation&FORMTYPE_WING)>>FORMTYPE_WING_SH;
		int entries=Aircraft_Formations [formation]->GetPerFl(formac);//numentries;
		wingac=entries;
//DeadCode JIM 22Sep00 		while (entries%100>=10)
//DeadCode JIM 22Sep00 		{
//DeadCode JIM 22Sep00 			wingac=entries%10;
//DeadCode JIM 22Sep00 			breakif(formac%wingac==0);
//DeadCode JIM 22Sep00 			entries/=10;
//DeadCode JIM 22Sep00 		}
//DeadCode JIM 22Sep00 		if (wingac==4)
//DeadCode JIM 22Sep00 			wingac=2;
	}

	int	realformac=formac;

//DeadCode JIM 20Oct00 	int	takeofftime=GR_TakeOffTime;
	TakeOffState	takeoffstate=TOS_SIMPLE;
	//This time they are either in the air or on the ground
	if (I.movecode.Evaluate()!=ENABLE_COMPLEX_VAL
		&&	(	I.movecode.Evaluate()==AUTO_TAKEOFF
			||	I.movecode.Evaluate()==AUTOSAG_TAKEOFF
			||	I.movecode.Evaluate()==AUTOSAG_WAITTAKEOFF
			||	I.movecode.Evaluate()==AUTO_TRAININGTAKEOFF				//CSB 06/03/00
		)	)
		takeoffstate=TOS_TAKINGOFF;
	else
		takeoffstate=TOS_INAIR;

	//Damage
	//Damage is one value or a list of damage values...
	//Any table containing 0xffff is undefined
	UWord	damagetable[QMD_TOTAL_ALL_LOCATIONS];
	{
		for (int i=0;i<QMD_TOTAL_ALL_LOCATIONS;i++)
			damagetable[i]=0xffff;

		int	maxind=0;
		if (I.damage.Evaluate()!=ENABLE_COMPLEX_VAL)
			maxind=1;
		if (I.damage.complex && I.damage.complex->type==Expr::EXPR_FORM)
			maxind=I.damage.Arguments();
		for (int index=0;index<maxind;index++)
		{
			int loc=I.damage.Evaluate(index);
			int location=loc&QMD_LOCATIONS_MASK;
			loc=loc-location;
			if (location==0)
			do{
				location=Math_Lib.rnd(QMD_TOTAL_DAMAGE_LOCATIONS);
			}while (damagetable[location]!=0xffff);
			if (location<QMD_TOTAL_DAMAGE_LOCATIONS && (loc&QMD_RANDOMLEVEL))
				if (loc==QMD_RANDOMLEVEL)
					location=Math_Lib.rnd()&QMD_DEAD;
				else
					location=Math_Lib.rnd(256)<<QMD_LOCSHIFT;
			damagetable[location]=loc>>QMD_LOCSHIFT;
		}
	}


	int	inwingcount=wingac;

	if (!formac)
	{	//No aircraft launched. Communication between waypoints and aircraft distracted
		gotgrpnum=-1;

	}
	else
	{
		do	/////// MAIN LOOP FOR CREATING AIRCRAFT
		{

			int v1,v2,v3;
			AirStruc*	currac=new AirStruc;


			currac->follower=
				currac->fly.nextflight=NULL;
			if ((v1=I.nat.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)//AMM 30Jul98
				currac->nationality=NAT_RED;					//AMM 30Jul98
			else												//AMM 30Jul98
				currac->nationality=Nationality(v1);			//AMM 30Jul98

			//Nationality
			if (	(v1=I.uid.Evaluate(estformpos))<0)
			{
				if ((v2=I.band.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
					currac->uniqueID.count=assignuid(RealAcBAND);
				else
					currac->uniqueID.count=assignuid((UniqueIDBand)v2);
				currac->fly.pModel->FrameCount = currac->uniqueID.count;	//CSB 14Nov00
			}
			else
				if (ConvertPtrUID(UniqueID(v1)))
					currac->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
				else
					currac->uniqueID.count=UniqueID(v1);

			bool	isSGT=false;
			if (currac->uniqueID.count<RealAcBAND)
				isSGT=true;
			
			if ((v1=I.homebase.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
			{
				if (firstac && firstac!=currac)
					currac->ai.homebase=firstac->ai.homebase;
				else
					if (squadrec)
						setpointer((ItemBase**)&currac->ai.homebase,squadrec->homeairfield);
					else
						INT3;
			}
			else
				setpointer((ItemBase**)&currac->ai.homebase,UniqueID(v1));

			if((currac->ai.homebase) && (currac->ai.homebase->World.Y == 0))								//CSB 5Oct00
			{																								//CSB 5Oct00
				UByte areatype;																				//CSB 5Oct00
				currac->ai.homebase->World.Y = _Collide.GroundAltitude(currac->ai.homebase->World, &areatype, true);	//CSB 5Oct00
			}																								//CSB 5Oct00

			EvalOrDefault(currac->formation,FormationTypeIndex,form,FTW_LWVIC);

			if ((v1=I.type.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				v1=GR_FriendlyScoutType00;
			int squadnum=v1;

			v2=(squadnum);	  //TextRef
			if (v2>SQ_BR_START)
				v2=squadrec->AcType();

			if (estformpos==0)
			{
				if (isSGT)
				{
					if (prevSAGsquadron !=squadrec)
					{
						baseSAGshape=ShapeNum(baseSAGshape+1);
						int v1=I.paintrules[0].Evaluate();
						if (v1==ENABLE_COMPLEX_VAL)
							offsetinformationleaderflights=0;
						else
						{
							offsetinformationleaderflights=v1;
							//may want to use this info for player position as well somehow...

						}
//DeadCode JIM 20Sep00 						offsetinformationleaderflights=0;
					}
					else
						offsetinformationleaderflights+=4;	//worst case... LW 3s of bombers
					prevSAGsquadron =squadrec;
					currac->shape=baseSAGshape;
					//element count is set later using realformac

					formac=1;
				}
				else
				{
					
					if ((formationleaderflights[v2]&0xff)>12)
					{
						formationleaderflights[v2]=(formationleaderflights[v2]&0xff00)+0x100;
					}
					if (formationleaderflights[v2]>=0x100)
					{  
						squadrec=&Node_Data[SquadNum(squadrec->squadron+(formationleaderflights[v2]>>8))];
//DeadCode RJS 10Nov00 						squadrec+=(formationleaderflights[v2]>>8);
						v1=squadnum=squadrec->squadron;
						setpointer((ItemBase**)&currac->ai.homebase,squadrec->homeairfield);
					}
					offsetinformationleaderflights=formationleaderflights[v2]&0x0ff;
					if (v2<PT_ME109)
						formationleaderflights[v2]+=realformac/3;
					else
						formationleaderflights[v2]+=4;
				}
				int grpnum=gotgrpnum;
				gotgrpnum++;	//simpler than MiG
				//waypoints use this a/c as group leader
				if (I.wpref)
					GR_lastroutefirstwaypoint=I.wpref;

				if (I.wpnum.Evaluate()!=ENABLE_COMPLEX_VAL)
				{
					WayPointPtr w=Persons2::ConvertPtrUID(UniqueID(GR_lastroutefirstwaypoint));
					for (int i=I.wpnum.Evaluate();i;i--)
					{
						w=w->next;
					}
					currac->waypoint=w;
					I.wpref=w->uniqueID.count;

				}

				if (I.leader.Evaluate()!=ENABLE_COMPLEX_VAL)
				{	
					if (I.leader.Evaluate()==0)
					{
						//flleadac=NULL;		//already is...	
						if (!isSGT)
							firstac=*ConvertPtrUID(prevflightleader);
						else
							firstac=NULL;
					}
					else
					{
						firstac=*ConvertPtrUID((UniqueID)I.leader.Evaluate());
						if (firstac==NULL)
							_Error.EmitSysErr("Leader not loaded before used");
				 		prevflightleader=currac->uniqueID.count;
					}

					if (!I.wpref)
					{
						I.wpref=firstac->waypoint->uniqueID.count;
					}
				}
				else
				{
				 	prevflightleader=currac->uniqueID.count;
				}
				int wavenum=I.applywave.Evaluate();
				FixUpWaypointsToGroup(grpnum,wavenum,UniqueID(GR_lastroutefirstwaypoint),currac->uniqueID.count,formac,currac);	//RJS 10Nov00
			}


			if (I.wpref)
				setpointer((ItemBasePtr*)&currac->waypoint,I.wpref);		//JIM 05Aug96
			else if (estformpos==0)
			{
				assert	(takeoffstate==TOS_SECRET);
				currac->waypoint=NULL;
			}
			else
				currac->waypoint=firstac->waypoint;

			currac->information = IF_OUT_POS;						  //CSB 05/01/00
			currac->vel_x =0;					
			currac->vel_y =0;					
			currac->vel_z =0;					
			currac->fly.cpitch = ANGLES_0Deg;		
			currac->fly.aileron = 0;						
			currac->fly.elevator = 0;					
			currac->fly.rudder = 0;						
			currac->fly.numinsag = 0;								  //CSB 24/01/00
			 
			currac->weap.ShootDelay=0;


			currac->fly.leadflight=firstac;						  //JIM 01/03/99
			if (flleadac==NULL)
			{
				currac->formpos=FormationIndexMIN;
				currac->fly.originalformpos=currac->formpos+(InForm)offsetinformationleaderflights;	//JIM 21Sep00
				firstac=
					flleadac=
						fllastac=currac;

			}
			else
			{
				if (fllastac==NULL)
				{
					flleadac->fly.nextflight=currac;
					currac->leader=NULL;
					if (wingac==2 && (flleadac->formpos&InWingMAX)==0)
					{
						currac->formpos=flleadac->formpos+(InWing)2;
						currac->fly.originalformpos=flleadac->fly.originalformpos+(InWing)2;
					}
					else
					{
						currac->formpos=flleadac->formpos+(InForm)1;
						currac->fly.originalformpos=flleadac->fly.originalformpos+(InForm)1;
					}
					flleadac=
						fllastac=currac;
				}
				else
				{
					currac->leader=flleadac;
					fllastac->follower=currac;

					currac->formpos=fllastac->formpos+(InWing)1;
					currac->fly.originalformpos=fllastac->fly.originalformpos+(InWing)1;
					fllastac=currac;
				}
			}

			currac->follower=
				currac->fly.nextflight=NULL;

			currac->fly.callname=squadrec->squadron;
			currac->fly.callnum=(currac->formpos&InWingMAX)+(currac->fly.originalformpos&InFormMAX)*5;

			if (_DPlay.Implemented)
			{
				for (ULong n=0;n<MAXPLAYERS;n++)
				{
					if (_DPlay.GameType<DPlay::COMMSQUICKMISSION)//AMM 17Jan00
					{
						if (!_DPlay.AllocPacket[n])
						{
							_DPlay.AllocPacket[n]=currac->uniqueID.count;
							currac->uniqueID.commsmove=TRUE;
							break;
						}
					}
				}
			}
				
			{
				currac->ai.pilotnum=ai_info::PROPER_PILOT_MAX+v1;

//DeadCode AMM 5Sep00 				if (currac->nationality==NAT_RAF)
//DeadCode AMM 5Sep00 				{
//DeadCode AMM 5Sep00 					FILE* fp=fopen("acpltnum.txt","at");
//DeadCode AMM 5Sep00 					UWord uid=currac->uniqueID.count;
//DeadCode AMM 5Sep00 					UByte pos=currac->fly.originalformpos;
//DeadCode AMM 5Sep00 					UWord pltnum=currac->ai.pilotnum;
//DeadCode AMM 5Sep00 					UWord colmask=(currac->fly.originalformpos & InFormMAX)+1;
//DeadCode AMM 5Sep00 					UWord nummask=(currac->fly.originalformpos & InWingMAX)+1;
//DeadCode AMM 5Sep00 					UWord callname=currac->fly.callname;
//DeadCode AMM 5Sep00 					UWord callnum=currac->fly.callnum;
//DeadCode AMM 5Sep00 					fprintf(fp,"AC %x ofp %d pltnum %d sqcol %d sqnum %d callname %d callnum %d\n",uid,pos,pltnum,colmask,nummask,callname,callnum);
//DeadCode AMM 5Sep00 					fclose(fp);
//DeadCode AMM 5Sep00 				}
			}

			currac->classtype=Plane_Type_Translate[v2][0];
			if (v1==Pack_PlayerSquad)
			{
				if (isSGT)
				{
					if (realformac<=Pack_PlayerPos)
						Pack_PlayerPos-=realformac;
					else
						if (pilotedaircraft==NULL)
							pilotedaircraft=currac;


				}
				else
				{
					Pack_PlayerPos--;
					if ((int)Pack_PlayerPos==-1)
						pilotedaircraft=currac;
				}

			}
			currac->fly.expandedsag=NULL;

			for(SWord i = 0; i < 4; i++)
			{
//DeadCode JIM 24Jul00 				if((currac->classtype->visible == ME109) && (Save_Data.flightdifficulty[FD_109FUEL]))
//DeadCode JIM 24Jul00 					currac->fly.fuel_content[i] = currac->classtype->fueltankcap[i] * 1750;
//DeadCode JIM 24Jul00 				else
					currac->fly.fuel_content[i] = currac->classtype->fueltankcap[i] * 1000;
			}

			currac->sentexpanded=FALSE;
			currac->sentcontracted=FALSE;
	

			if (isSGT)
			{
				instancesSAG[v2]+=realformac;
			}
			else
			{
				instancesAC[v2]++;
			}	

			HP	hp;
			if (!I.attitude.EvalA(hp))
			{
				currac->hdg=hp.H;
				currac->pitch=hp.P;
				if (currac->pitch+ANGLES_30Deg >>ANGLES_60Deg)
					currac->pitch=ANGLES_0Deg;
			}
			else
				currac->pitch=ANGLES_180Deg;

			if ((v1=I.shape.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				if (!isSGT)
					currac->shape=currac->GetDrawShape();				//RJS 12Oct00
//DeadCode RJS 12Oct00 					currac->shape=currac->classtype->visible;
				else
				{}	
			else
				currac->shape=(ShapeNum)v1;

			currac->roll=ANGLES_0Deg;										//JIM 21Oct96
  			currac->fly.rpm = currac->classtype->maxrpm;									//JIM 21Oct96	//CSB 23/02/00
			currac->fly.thrustpercent = 0;							//JIM 21Oct96	//CSB 23/02/00


			currac->ai.manoeuvre=MANOEUVRE_SELECT;
			currac->manoeuvretime=0;									//JIM 11Sep96
			currac->ai.ManStep=PHASE0;								//JIM 11Sep96
			currac->slowdownleader=FALSE;
			currac->ai.LastAction()=wpacnoactionno;
			currac->information=IF_OUT_POS;							  //CSB 05/01/00

			currac->CommsOwner=UID_NULL;							//AMM 27Nov98

			if ((v1=I.movecode.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				currac->movecode=AUTO_FOLLOWWP;
			else
				if (v1>AUTO_COMBAT)
				{
					currac->movecode=AUTO_COMBAT;
					currac->ai.manoeuvre=MANOEUVRE(v1-AUTO_COMBAT);
				}
				else
					currac->movecode=AutoMoveCodeTypeSelect(v1);

			ULong drec,usedval;
			FormOrDefault(drec,int,squadname,-1);
			if (drec == 0xFFFFFFFF)								//RJS 24Feb00
			{
				usedval = currac->classtype->planetext;
				if (usedval >= PT_GER_FLYABLE)
				{
					usedval -= PT_GER_FLYABLE;
					usedval |= GRUPPENMASK;
				}
				else
					usedval -= PT_BRIT_FLYABLE;
			}
			else
				usedval = drec;
			
			currac->ai.diaryptr = Squad_Diary.GetDiaryPtr(usedval);
			if (drec == 0xFFFFFFFF)
				currac->ai.diaryptr->noaclaunched++;

			FormOrDefault(currac->ai.morale,MoraleType,morale,squadrec->averagemorale);
			FormOrDefault(currac->ai.radiosilent,Bool,radiosilence,FALSE);
//temp for flight model tuning, rdh
//auto ac
//rdh 25nov			currac->ai.morale = MORALE_GOOD;		//MORALE_POOR;
//			currac->ai.morale 	= MORALE_TOPMORALE;		
			
//RDH 18/02/99
			if (currac->nationality == NAT_RED)
			{
				currac->ai.elementtactics = LOOSEDEUCE;
			}else
			{
				currac->ai.elementtactics = WELDEDWING;
			}
			currac->ai.squadrontactics = LOOSEDEUCE;
			currac->ai.flighttactics = LOOSEDEUCE;
			currac->ai.firsttactic     = TACTIC_NULL;					//CSB 20Jun00
			for(int n = 0; n < 4; n++)
				currac->ai.spottedunfriendly[n] = NULL;

			int combskill,flyskill;
			FormOrDefault(combskill,int,skill,squadrec->averageskill);

			currac->ai.combatskill=SkillType(	((GR_GlobalSkillMax-GR_GlobalSkillMin)*combskill)/SKILL_MAX
												+GR_GlobalSkillMin
											);

//DEADCODE DAW 22/03/00 			FormOrDefault((UWord&)cols[COLS_DAMAGE],int,damage,0);
			FormOrDefault((UWord&)cols[COLS_BOMBS],int,bombs,0);


			if ((v1=I.target.Evaluate(estformpos))==ENABLE_COMPLEX_VAL || v1==0)
				currac->ai.unfriendly=NULL;
			else
				if (v1!=0)
					setpointer((ItemBase**)&currac->ai.unfriendly,UniqueID(v1));
				else
					currac->ai.unfriendly=NULL;

			if ((v1=I.attacker.Evaluate(estformpos))==ENABLE_COMPLEX_VAL || estformpos==0)
				currac->ai.attacker=NULL;
			else
				if (v1!=0)
					setpointer((ItemBase**)&currac->ai.attacker,UniqueID(v1));
				else
					currac->ai.attacker=NULL;

//DEADCODE JIM 14/01/00 ONLY IF A/C is injected while 3d is already running
//DEADCODE JIM 14/01/00 			if (Three_Dee.livelist)
//DEADCODE JIM 14/01/00 			{
//DEADCODE JIM 14/01/00 				DOLAUNCHER_PTR d=(DOLAUNCHER_PTR)SHAPE.GetLauncherPos(currac->shape,0);
//DEADCODE JIM 14/01/00 				if ( d && (d->lnchrtype & LT_MASK) == LT_MOVEGUN )
//DEADCODE JIM 14/01/00 					*Three_Dee.livelist+=currac;
//DEADCODE JIM 14/01/00 			}
//DEADCODE JIM 14/01/00 

			if (firstobject==IllegalSepID)
				firstobject=currac->uniqueID.count;

//DEADCODE DAW 22/03/00 			int dutyval=0,dvplus1=0,dvplus2=0;						  //JIM 25/03/99
			int dutyval;
			EvalOrDefault(dutyval,int,duty,PACK_AM_ESCORT);				  //JIM 25/03/99
			currac->duty=dutyval&PACK_AM_MAINMETHOD_MASK;
			currac->ai.submethod=ai_info::SubMethod(dutyval>>PACK_AM_SUBMETHOD_SHIFT);
			if (I.applywave.Evaluate()==-3)
				currac->ai.submethod=ai_info::SubMethod(currac->ai.submethod|ai_info::SM_RETURN_ESCORT);

//DEADCODE DAW 22/03/00 			currac->duty=DutyType(dutyval+dvplus1);					  //RDH 23/05/99
			int	pattern;
			EvalOrDefault(pattern,int,pattern,0);				  //JIM 25/03/99

//DEADCODE JIM 08/12/99 			EvalOrDefault(currac->formation,FormationTypeIndex,form,SQUAD_STACKEDV);

			FormOrDefault(currac->vel_,int,vel,currac->classtype->cruisevel);		//rdh
//DEADCODE JIM 14/01/00 			GearState	onground;
//DEADCODE JIM 17/01/00 			if (isSGT)
//DEADCODE JIM 17/01/00 			{
//DEADCODE JIM 17/01/00 				setposition(currac,I.position,TRUE);
//DEADCODE JIM 17/01/00 
//DEADCODE JIM 17/01/00 			}
//DEADCODE JIM 17/01/00 			else
			if (estformpos==0)
			{
				EventVal* pos=&I.position;

				if (takeoffstate==TOS_TAKINGOFF)
				{
#ifdef REPLAYWPCHECK
					FILE* fp;
					if (_Replay.Record)
						fp=fopen("wptrgchr.txt","at");
					else
						fp=fopen("wptrgchp.txt","at");

					UWord uid=currac->uniqueID.count;
					UWord wid;
					UWord trg;
					
					if (currac->waypoint)
					{
						wid=currac->waypoint->uniqueID.count;

						if (currac->waypoint->target)
							trg=currac->waypoint->target->uniqueID.count;
						else
							trg=0;
					}
					else
					{
						wid=0;
						trg=0;
					}

					fprintf(fp,"AC:%x WP:%x WPT:%x\n",uid,wid,trg);
					fclose(fp);

					if (uid==0xf11)
					{
						int bp=0;
					}
#endif
//					WayPointPtr mywp=*Persons2::ConvertPtrUID(UniqueID(0x1dc));

					currac->World=currac->waypoint->target->World;
					currac->fly.pModel->GroundHeight = currac->ai.homebase->World.Y;
					if (currac->World.Y==0)
						currac->World.Y=currac->ai.homebase->World.Y;

					currac->World.Y = currac->fly.pModel->GroundHeight + currac->classtype->deckshunt;
					AddToWorld(currac);
					UniqueID hb=currac->ai.homebase->uniqueID.count;
					if (	currac->waypoint->target->SGT!=hb
						&&	currac->waypoint->target!=currac->ai.homebase)
					{
						INT3;
						if (currac->waypoint->target->SGT)
							hb=currac->waypoint->target->SGT;
						else
							hb=currac->waypoint->target->uniqueID.count;
					}
//DeadCode MS 26Sep00 					assert(currac->waypoint->target->SGT==hb || currac->waypoint->target==currac->ai.homebase);
					for (int i=RunwayEBAND;i<BlokeBAND;i++)
					{
						ItemPtr p=ConvertPtrUID(UniqueID(i));
						if (p && p->SGT==hb)
						{
							currac->InterceptandRange(&p->World);
							currac->hdg	= currac->HdgIntercept;
							currac->pitch= ANGLES_0Deg;
						}
					}
					if (I.movecode.Evaluate()!=AUTOSAG_WAITTAKEOFF)
					{
					//move next waypoint forward 1 for main force & 2 for escort
						I.wpref=UID_NULL;	
						WayPointPtr w=currac->waypoint;
						if (w->skipunder==UID_NULL)
							w=w->next;
						else
						{
							while (w->wpname!=WPNAME_BombRendezvous && w->wpname!=WPNAME_EscRendezvous)
								w=w->next;
							if (I.applywave.Evaluate()==-3)
								while (w->wpname!=WPNAME_EscDisperse)
									w=w->next;
							else
								if ((currac->formation&FORMTYPE_COURSESEL)>FTC_RAF)
									while (w->wpname!=WPNAME_EscRendezvous)
										w=w->next;
						}
						currac->waypoint=w;
					}

					currac->vel_ = currac->vel_x = currac->vel_y = currac->vel_z = 0;
					currac->pitch = currac->classtype->deckangle;
					currac->fly.thrustpercent = 0;
//DEADCODE JON 6/6/00 #pragma message ( __HERE__ "ground take off here" )
//DEADCODE JON 6/6/00 					{
//DEADCODE JON 6/6/00 						ULong x = currac->ai.homebase->World.X >> 17;
//DEADCODE JON 6/6/00 						ULong z = currac->ai.homebase->World.Z >> 17;
//DEADCODE JON 6/6/00 						char blockStr[7];
//DEADCODE JON 6/6/00 						blockStr[6] = char(0);
//DEADCODE JON 6/6/00 						blockStr[5] = '1'+char(z%8);
//DEADCODE JON 6/6/00 						blockStr[3] = '1'+char((z/8)%8);
//DEADCODE JON 6/6/00 						blockStr[1] = '1'+char((z/64)%8);
//DEADCODE JON 6/6/00 						blockStr[4] = '1'+char(x%8);
//DEADCODE JON 6/6/00 						blockStr[2] = '1'+char((x/8)%8);
//DEADCODE JON 6/6/00 						blockStr[0] = '1'+char((x/64)%8);
//DEADCODE JON 6/6/00 						::AfxTrace("Currac homebase block position: %s\n", blockStr );
//DEADCODE JON 6/6/00 					}
//DEADCODE JON 6/6/00 
//DeadCode CSB 26Jun00 					currac->World.Y=Land_Scape.GetGroundLevel(currac->ai.homebase,NULL,true)+currac->classtype->deckshunt;
//DeadCode CSB 18Oct00 					currac->World.Y=Land_Scape.GetGroundLevel(currac->World,NULL,true)+currac->classtype->deckshunt;	//CSB 26Jun00
					currac->fly.pModel->GroundHeight = currac->ai.homebase->World.Y;
					currac->World.Y = currac->fly.pModel->GroundHeight + currac->classtype->deckshunt;	//CSB 18Oct00
					currac->roll = ANGLES_0Deg;

//DeadCode CSB 12Jul00 					AircraftAnimData*		acanim  = NULL;
//DeadCode CSB 12Jul00 					SimpleAircraftAnimData*	saganim = NULL;
//DeadCode CSB 12Jul00 					if(currac->fly.numinsag)
//DeadCode CSB 12Jul00 					{
//DeadCode CSB 12Jul00 						saganim = (SimpleAircraftAnimData*)currac->Anim;
//DeadCode CSB 12Jul00 						saganim->acrpm  = 0;
//DeadCode CSB 12Jul00 					}
//DeadCode CSB 12Jul00 					else
//DeadCode CSB 12Jul00 					{
//DeadCode CSB 12Jul00 						acanim = (AircraftAnimData*)currac->Anim;
//DeadCode CSB 12Jul00 						acanim->acrpm  = 0;
//DeadCode CSB 12Jul00 						acanim->acrpm1 = 0;
//DeadCode CSB 12Jul00 						acanim->acleglowerl = 0;
//DeadCode CSB 12Jul00 						acanim->acleglowerr = 0;
//DeadCode CSB 12Jul00 						if((currac->fly.pModel->Type == AT_SPITFIRE) || (currac->fly.pModel->Type == AT_HURRICANE) || (currac->fly.pModel->Type == AT_JU87B))
//DeadCode CSB 12Jul00 							acanim->accanopy = 255;
//DeadCode CSB 12Jul00 					}
				}
				else
				{
					if (pos->complex)
						setposition(currac,*pos,TRUE);
					else
						setfollowerposition(currac);
				}
				make_events(I.events,currac);
			}
			else
			{
				if(		(firstac->movecode==AUTO_WAIT4TIME) 
					||	(firstac->movecode==AUTO_TAKEOFF) 
					||	(firstac->movecode==AUTO_TRAININGTAKEOFF)	)	//CSB 06/03/00
				{
					currac->vel_ = currac->vel_x = currac->vel_y = currac->vel_z = 0;
//					currac->movecode=AUTO_TAKEOFF;
					currac->pitch = firstac->pitch;
					currac->hdg = firstac->hdg;
					currac->roll = ANGLES_0Deg;
					currac->fly.pModel->GroundHeight = firstac->fly.pModel->GroundHeight;
					currac->World.Y = firstac->World.Y;
					currac->fly.thrustpercent = 0;
				}
			}

//DEADCODE JIM 09/12/99 			currac->fly.comefrommap = FALSE;								//RDH 20Nov96

 			if (currac->pitch == ANGLES_180Deg)						//RDH 16Apr96
 				SetAngles (currac);									//RDH 16Apr96

			if (isSGT)
			{
				//This was only being done for non-SAGs!
				Float fuelchange=1.0;
				if (damagetable[QMD_FUELKILOS]!=0xffff)
				{
					int loadedfuel=currac->fly.fuel_content[0]+currac->fly.fuel_content[1]+currac->fly.fuel_content[2]+currac->fly.fuel_content[3];
					fuelchange=damagetable[QMD_FUELKILOS]*100000.0/loadedfuel;
				}
				if (damagetable[QMD_FUELPERCENT]!=0xffff)
					fuelchange=damagetable[QMD_FUELPERCENT]/100.0;
				if (fuelchange!=1.0)
				{
					currac->fly.fuel_content[0]*=fuelchange;
					currac->fly.fuel_content[1]*=fuelchange;
					currac->fly.fuel_content[2]*=fuelchange;
					currac->fly.fuel_content[3]*=fuelchange;
				}
				currac->PatchGroupAndAnim(currac->classtype->SAGsubshape,realformac);
				if((takeoffstate == TOS_TAKINGOFF) || (currac->movecode == AUTOSAG_LAST))	//CSB 11Aug00
				{
					if (currac->duty>=PACK_AM_ESCORT)
						currac->PatchGroupAndAnim(&TakeOff_FormationWing.formationtype,&TakeOff_FormationSquad.formationtype,4);
					else
						currac->PatchGroupAndAnim(&TakeOff_FormationWing.formationtype,&TakeOff_FormationSquad.formationtype);
					currac->vel_ = currac->vel_x = currac->vel_y = currac->vel_z = 0;	//CSB 11Aug00
				}
			}
//DEADCODE DAW 08/03/00 			currac->ai.eventlog=eventloglist;
			if(estformpos)
			{
				setfollowerposition(currac);
				if(currac->vel_ == 0)
				{
					currac->World.Y = firstac->World.Y;
					currac->fly.pModel->GroundHeight = firstac->fly.pModel->GroundHeight;
				}
			}
			else
			{
//DEADCODE DAW 08/03/00 				if (eventloglist->nat!=NAT_AMBER)
//DEADCODE DAW 08/03/00 					if (I.follower.Evaluate()==ENABLE_COMPLEX_VAL
//DEADCODE DAW 08/03/00 					&&	I.leader.Evaluate()==ENABLE_COMPLEX_VAL)
//DEADCODE DAW 08/03/00 						currac->ai.eventlog=
//DEADCODE DAW 08/03/00 							eventloglist=
//DEADCODE DAW 08/03/00 								new EventLog (eventloglist);
//DEADCODE DAW 08/03/00 				
//DEADCODE DAW 08/03/00 				eventloglist->nat=currac->nationality;			//JIM 30Sep96
//DEADCODE DAW 08/03/00 				if (I.leader.Evaluate()==ENABLE_COMPLEX_VAL)
//DEADCODE DAW 08/03/00 				{
//DEADCODE DAW 08/03/00 					eventloglist->targetuid=currac->uniqueID.count;
//DEADCODE DAW 08/03/00 					if (eventloglist->stage!=EventLog::TAKEOFF)
//DEADCODE DAW 08/03/00 					{
//DEADCODE DAW 08/03/00 						eventloglist->encounteredtype=PlaneTypeSelect(v2);
//DEADCODE DAW 08/03/00 						eventloglist->launchtime=takeofftime*SECS100;
//DEADCODE DAW 08/03/00 //TEMPCODE RJS 16/11/99 						if (eventloglist->homebase==UID_Japan)
//DEADCODE DAW 08/03/00 //TEMPCODE RJS 16/11/99 							eventloglist->launchtime-=30*60*SECS100;
//DEADCODE DAW 08/03/00 					}
//DEADCODE DAW 08/03/00 				}
//DEADCODE DAW 08/03/00 				else
//DEADCODE DAW 08/03/00 					if (eventloglist->stage!=EventLog::TAKEOFF)
//DEADCODE DAW 08/03/00 						eventloglist->escorttype=PlaneTypeSelect(v2);


//				if (formac==ENABLE_COMPLEX_VAL)
//				{
//					UpdateLog(eventloglist,0,EventLog::TAKEOFF);//RDH 02Oct96
//				}
//				else
//DEADCODE DAW 08/03/00 				{
//DEADCODE DAW 08/03/00 					if (takeoffstate!=TOS_SECRET)
//DEADCODE DAW 08/03/00 					{
//DEADCODE DAW 08/03/00 //DEADCODE DAW 08/03/00 						if (isSGT)
//DEADCODE DAW 08/03/00 							eventloglist->encsize += I.inform.Evaluate();			//RDH 02Oct96
//DEADCODE DAW 08/03/00 						else
//DEADCODE DAW 08/03/00 							eventloglist->encsize += formac;			//RDH 02Oct96
//DEADCODE DAW 08/03/00 						if (/*currac->nationality==NAT_RED &&*/ eventloglist->stage!=EventLog::TAKEOFF)
//DEADCODE DAW 08/03/00 						{
//DEADCODE DAW 08/03/00 							UpdateLog(eventloglist,0,EventLog::UNSEEN);//RDH 02Oct96
//DEADCODE DAW 08/03/00 							eventloglist->launchtime=takeofftime*SECS100;
//TEMPCODE RJS 16/11/99 							if (eventloglist->homebase==UID_Japan)
//TEMPCODE RJS 16/11/99 								eventloglist->launchtime-=30*60*SECS100;
//DEADCODE DAW 08/03/00 						}
//DEADCODE DAW 08/03/00 					}
//DEADCODE DAW 08/03/00 				}

//DEADCODE DAW 08/03/00 				if (	eventloglist->homebase==UID_NULL
//DEADCODE DAW 08/03/00 					&& currac->ai.homebase
//DEADCODE DAW 08/03/00 					&& (int)currac->ai.homebase!=-1
//DEADCODE DAW 08/03/00 //					&& (currac->movecode==AUTO_TAKEOFF)		//RDH 13Nov96
//DEADCODE DAW 08/03/00 					)
//DEADCODE DAW 08/03/00 				{
//DEADCODE DAW 08/03/00 					eventloglist->homebase=currac->ai.homebase->uniqueID.count;
//DEADCODE DAW 08/03/00 //TEMPCODE RJS 16/11/99 					if (eventloglist->homebase==UID_Japan)
//DEADCODE DAW 08/03/00 //TEMPCODE RJS 16/11/99 						eventloglist->launchtime-=30*60*SECS100;
//DEADCODE DAW 08/03/00 				}
			}

			//Everybody goes through colourruleplayersquadron now!!!!!
			int	pilotmarking=squadrec->markingscheme
						+0x10000*( (currac->fly.originalformpos&InWingMAX)+ (currac->fly.originalformpos&InFormMAX)*wingac);
			if (squadrec->markingscheme<64000)
//DeadCode JIM 12Oct00 				if (offsetinformationleaderflights==12)
//DeadCode JIM 12Oct00 				{
//DeadCode JIM 12Oct00 //DeadCode CSB 4Oct00 					int staffelnum=(pilotmarking/1600)%40;	//H,M,R
//DeadCode JIM 12Oct00 					pilotmarking=squadrec->markingscheme
//DeadCode JIM 12Oct00 							+0x10000*((currac->formpos&InWingMAX)+ (currac->formpos&InFormMAX)*wingac);
//DeadCode JIM 12Oct00 //DeadCode CSB 4Oct00 					if (staffelnum=='H'-'A')
//DeadCode JIM 12Oct00 //DeadCode CSB 4Oct00 						pilotmarking+=('U'-'H')*1600;
//DeadCode JIM 12Oct00 //DeadCode CSB 4Oct00 					elseif (staffelnum=='M'-'A')
//DeadCode JIM 12Oct00 //DeadCode CSB 4Oct00 						pilotmarking+=('V'-'M')*1600;
//DeadCode JIM 12Oct00 //DeadCode CSB 4Oct00 					else
//DeadCode JIM 12Oct00 //DeadCode CSB 4Oct00 						pilotmarking+=('W'-'R')*1600;
//DeadCode JIM 12Oct00 
//DeadCode JIM 12Oct00 
//DeadCode JIM 12Oct00 
//DeadCode JIM 12Oct00 				}
//DeadCode JIM 12Oct00 				else
					pilotmarking=squadrec->markingscheme
							+0x10000*((currac->formpos&InWingMAX)+ (currac->formpos&InFormMAX)*wingac)
							+1600*(	offsetinformationleaderflights/4 );
			if (!isSGT)
			{
				ColourRulePlayerSquadron(currac,currac->formpos,cols,pilotmarking,damagetable);			//RDH 16Apr96
//DeadCode DAW 09Jul99 			if (takeoffstate>TOS_TAKENOFF)
				if (takeoffstate==TOS_TAKINGOFF)
//DEADCODE CSB 06/03/00 				{
					currac->fly.pModel->GearDown(currac);
//DEADCODE CSB 06/03/00 					SHAPE.NavigationLightsActive(currac, TRUE);
//DEADCODE CSB 06/03/00 				}
				else													//CSB 06/03/00
					currac->fly.pModel->GearUp(currac);					//CSB 06/03/00

				SHAPE.BombBayDoors(currac, ANIM_BOMBDOORS_CLOSE, true);
			}
			else
				currac->ai.Lettering()=pilotmarking;
			logUID(currac);
			if (I.uid.Evaluate() !=ENABLE_COMPLEX_VAL && I.uid.Evaluate()<0)
			{
					SetLoc(-I.uid.Evaluate(),currac->uniqueID.count); //also need to fix references
					useUID(currac,UniqueID(I.uid.Evaluate()));
			}
			
			currac->AddToList();

			//set up for next in squadron

			--formac;
			if (--inwingcount==0)
			{
		 		inwingcount=wingac;
		 		fllastac=NULL;
				if (wingac==2 && (formac&2))
					estformpos+=(InWing)1;
				else
				{
			 		estformpos+=(InForm)1;
//DEADCODE JIM 14/01/00 					if (takeoffstate>TOS_TAKENOFF)
//DEADCODE JIM 14/01/00 						takeofftime+=TIME_TAKEOFF_FLIGHT;
//DEADCODE JIM 14/01/00 					if (takeoffstate==TOS_RUNWAY)
//DEADCODE JIM 14/01/00 						takeoffstate=TOS_NEXTFLIGHTS;
//DEADCODE JIM 14/01/00 					else
//DEADCODE JIM 14/01/00 					if (takeoffstate==TOS_TAKINGOFF)
//DEADCODE JIM 14/01/00 						if (takeofftime>=GR_TakeOffTime)
//DEADCODE JIM 14/01/00 							takeoffstate=TOS_RUNWAY;	//next flight is player!!
				}
			}
			else
				estformpos+=(InWing)1;

		} while (formac);

		if (I.follower.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			AirStrucPtr f=*ConvertPtrUID((UniqueID)I.follower.Evaluate());
			if (f==NULL)
				_Error.EmitSysErr("Follower not yet defined!");
			f->fly.leadflight=firstac;
		}
		fixupengagements(firstac);
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		fixupengagements
//Author		Jim Taylor
//Date			Mon 19 Aug 1996
//
//Description	Fixes to squadron engagement logic for forward references
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::fixupengagements(AirStrucPtr	firstac)
{
	AirStrucPtr attacker=firstac->ai.attacker;
	if (	firstac->ai.unfriendly
		&&	(int) firstac->ai.unfriendly !=-1
		&& 	firstac->ai.unfriendly->Status.size==AIRSTRUCSIZE	)
	{
		AirStrucPtr	eye=firstac;
		AirStrucPtr trg=*firstac->ai.unfriendly;
		fixupengagements(eye,trg);
		if (	trg->ai.unfriendly==eye
			&&	attacker!=trg	)
		{
			AirStrucPtr	eye=trg;
			AirStrucPtr trg=firstac;
			fixupengagements(eye,trg);
		}
	}
	if (	attacker
		&&	(int)attacker!=-1	)
	{
			AirStrucPtr	eye=attacker;
			AirStrucPtr trg=firstac;
			fixupengagements(eye,trg);
	}
}

void	Persons3::fixupengagements(AirStrucPtr	eyeF,AirStrucPtr trg)
{
	//movecodes and manoeuvres already done
	//leader goes for leader... already done
	trg->ai.attacker=eyeF;
	AirStrucPtr	trgF=trg;
	forever
	{
		AirStrucPtr eye=*eyeF->follower;
		while (eye)
		{
			AirStrucPtr trgE=Art_Int.SetFollowerWhoCanEngage(eye,trgF);
			if (trg)
				trgF=trgE;
			eye->ai.unfriendly=trgE;

// set up commsowner if this ac is attacking a player initially

			if (trgE && trgE->uniqueID.commsmove)						//AMM 27Nov98
				eye->CommsOwner<<=trgE->uniqueID.count;			//AMM 27Nov98

			if (trgE && trgE->ai.attacker!=NULL)
				trgE->ai.attacker=eye;
			eye=*eye->follower;
		}

		eyeF=eyeF->fly.nextflight;
		breakif (eyeF==NULL);
		AirStrucPtr trgF=Art_Int.SetFlightWhoCanEngage(eyeF,trg);
		if (trgF)
			trg=trgF;
		eyeF->ai.unfriendly=trgF;

// set up commsowner if this ac is attacking a player initially

		if (trgF && trgF->uniqueID.commsmove)							//AMM 27Nov98
			eyeF->CommsOwner<<=trgF->uniqueID.count;				//AMM 27Nov98

		if (trgF && trgF->ai.attacker!=NULL)
			trgF->ai.attacker=eyeF;
	};
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_waypoint
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		if I.useexistingWP then evaluate that to get UID to link in!
//				no other vars will be filled in.
//
//Returns	
//
//------------------------------------------------------------------------------
enum	{WP_SKIP_BASE=UID_BIT14,WP_SKIP_GROUP=64,WP_SKIP_WAVE_BASE=UID_BIT15};
UniqueID	Persons3::make_waypoint(info_waypoint& I)
{
	if(gotgrpnum)
	{
		FixWavesToLastRoute();

		gotgrpnum=0;
		gotgrpflags=0xffff0000;
//DEADCODE RJS 15/02/00 		if ((int)GR_WaveNum>=0)
//DEADCODE RJS 15/02/00 			GR_WaveNum++;
		nextwpname=WPNAME_None;
		nextwpnum=1;
		GR_lastroutefirstwaypoint=UID_NULL;
	}

	if (justscanning)
	{

		if (I.uid.Evaluate()>=0)
			 UsedFixedUID=TRUE;
		return (UID_Null);
	}
	int v1;
	if ((v1=I.useexistingWP.Evaluate())!=ENABLE_COMPLEX_VAL)
	{
		if (I.prevwp!=IllegalSepID)
		{
			WayPointPtr p,n;
			p=*ConvertPtrUID(I.prevwp);
			n=*ConvertPtrUID(UniqueID(v1));
			if (p==NULL || n==NULL)
				_Error.EmitSysErr("Can't link together unloaded waypoints");
			p->next=n;
			n->prev=p;
		}
		return UniqueID(v1);
	}
	else
	{
		WayPointPtr	newwaypoint=new WayPoint;
		if (I.events!=NULL)
		{
//DeadCode AMM 10Jun98 			newwaypoint->uniqueID.deaded=TRUE;
//DeadCode AMM 30Nov98 			newwaypoint->uniqueID.commsmove=TRUE;				//AMM 10Jun98
			newwaypoint->Status.deaded=TRUE;					//AMM 30Nov98
			make_events(I.events,newwaypoint);
		}
//DeadCode AMM 10Jun98  		newwaypoint->uniqueID.deaded=FALSE;
//DeadCode AMM 30Nov98  		newwaypoint->uniqueID.commsmove=FALSE;					//AMM 10Jun98
 		newwaypoint->Status.deaded=FALSE;						//AMM 30Nov98
 ////		newwaypoint->bfieldindex=1;
		newwaypoint->ETA = 0;										//RDH 19Feb96
		if ((v1=I.etas.Evaluate())!=ENABLE_COMPLEX_VAL)
			newwaypoint->ETA += v1*100;										//RDH 19Feb96
		if ((v1=I.etam.Evaluate())!=ENABLE_COMPLEX_VAL)
			newwaypoint->ETA += v1*60*100;										//RDH 19Feb96
		if ((v1=I.etah.Evaluate())!=ENABLE_COMPLEX_VAL)
			newwaypoint->ETA += v1*60*60*100;										//RDH 19Feb96
		if ((v1=I.uid.Evaluate())<0)
		{
			newwaypoint->uniqueID.count=assignuid(WayPointBAND);
			if (-v1>=SGR_WPP_TakeOff && -v1<=SGR_WPP_Landing)
			{
				nextwpname=WPNames(-v1-SGR_WPP_TakeOff+WPNAME_TakeOff);
				nextwpnum=0;
			}
			else
			if (-v1>=SGR_WPP_Msg0 && -v1<=SGR_WPP_Msg9)
			{
				nextwpname=WPNames(-v1-SGR_WPP_Msg0+WPNAME_Msg0);
				nextwpnum=0;
			}
			else
			switch (-v1)
			{
				case	SGR_WPC_TakeOff:	nextwpname=WPNAME_TakeOff;	break;	
				case	SGR_WPC_Target:		nextwpname=WPNAME_Target;	break;
				case	SGR_WPC_PatrolS:	nextwpname=WPNAME_PatrolS;	break;
				case	SGR_WPC_PatrolE:	nextwpname=WPNAME_PatrolE;	break;
				case	SGR_WPC_Landing:	nextwpname=WPNAME_Landing;	break;
				case	SGR_WPC_FighterLimit:nextwpname=WPNAME_109Break;break;
			}
		}
		else
		{
			newwaypoint->uniqueID.count=UniqueID(v1);
		}
		if (GR_lastroutefirstwaypoint==UID_NULL)
			GR_lastroutefirstwaypoint=newwaypoint->uniqueID.count;

		newwaypoint->wpname=nextwpname;
		newwaypoint->wpnum=nextwpnum++;
		EvalOrDefault(newwaypoint->_vel,int,vel,0);

		if (I.position.complex)
			setposition(newwaypoint,I.position,FALSE);
		else
			newwaypoint->World.X=
				newwaypoint->World.Y=
					newwaypoint->World.Z=
						0;

		WayPointPtr	tmpwp=NULL;
		if (I.prevwp!=IllegalSepID)
		{
			tmpwp=ConvertPtrUID(I.prevwp);
			assert((tmpwp)&&("nested route must exist"));
		}

		if ((v1=I.target.Evaluate())==ENABLE_COMPLEX_VAL)
			newwaypoint->target=NULL;
		else
		{
			if (v1<0x4000)													//JIM 17Jul00
				setpointer((ItemBase**)&newwaypoint->target,UniqueID(v1));	//JIM 17Jul00
			else															//JIM 17Jul00
				newwaypoint->target=(Item*)tmpwp;	//DIRTY CLUDGE!!!				//JIM 17Jul00
			
			if ((int)newwaypoint->target==-1)
				NOP;
			if((int)newwaypoint->target!=-1 && newwaypoint->target->World.Y == 0)															//CSB 5Oct00
			{																								//CSB 5Oct00
				UByte areatype;																				//CSB 5Oct00
				newwaypoint->target->World.Y = _Collide.GroundAltitude(newwaypoint->target->World, &areatype, true);	//CSB 5Oct00
			}																								//CSB 5Oct00
		}

#ifdef REPLAYWPCHECK
		FILE* fp;

		if (_Replay.Record)
			fp=fopen("wptrgr.txt","at");
		else
			fp=fopen("wptrgp.txt","at");

		UWord trg,uid;
		uid=newwaypoint->uniqueID.count;
		if (newwaypoint->target)
			trg=newwaypoint->target->uniqueID.count;
		else
			trg=0;
		fprintf(fp,"WP: %x trg: %x\n",uid,trg);
		fclose(fp);

		if (uid==322)
		{
			int bp=0;
		}
#endif
		if ((v1=I.range.Evaluate())!=ENABLE_COMPLEX_VAL)
			if (I.rangeispercent)
			{
				assert(tmpwp&&"RangePC but no prev");
				SLong r;
				ANGLES b,a;
				Math_Lib.HighIntercept(	tmpwp->World.X-newwaypoint->World.X,
									tmpwp->World.Y-newwaypoint->World.Y,
									tmpwp->World.Z-newwaypoint->World.Z,
									r,b,a);
				if (r>1000000)
					r=(r/100)*v1;
				else
					r=(r*v1)/100;
				newwaypoint->range=r;
			}
			else
				newwaypoint->range=v1;
		else
			newwaypoint->range=0;

		if (I.applygroup.Evaluate()!=ENABLE_COMPLEX_VAL)
		{
			gotgrpflags|=1<<I.applygroup.Evaluate();
			//I put dummy values into skipunder and skipover which later get fixed up.
			newwaypoint->skipunder=UniqueID((WP_SKIP_BASE)+(I.applygroup.Evaluate()*WP_SKIP_GROUP));
			newwaypoint->skipover=UniqueID(newwaypoint->skipunder+63);	//this will get trimmed when fixed up
			if (I.applyflight.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				newwaypoint->skipunder=UniqueID(newwaypoint->skipunder+I.applyflight.Evaluate()*4);
				newwaypoint->skipover=UniqueID(newwaypoint->skipunder+3);
			}
			if (I.applyelt.Evaluate()!=ENABLE_COMPLEX_VAL)
			{
				newwaypoint->skipunder=UniqueID(newwaypoint->skipunder+I.applyelt.Evaluate()*2);
				newwaypoint->skipover=UniqueID(newwaypoint->skipunder+1);
			}
		}
		int aw=I.applywave.Evaluate();
		if (aw!=ENABLE_COMPLEX_VAL)
		{
			if (aw<0)
			{
				newwaypoint->skipunder=UniqueID(WP_SKIP_WAVE_BASE-aw);
				newwaypoint->skipover=UniqueID(WP_SKIP_WAVE_BASE);	//this will get trimmed when fixed up
			}
			else
			{
				newwaypoint->skipunder=UniqueID(WP_SKIP_WAVE_BASE+aw);
				newwaypoint->skipover=UniqueID(WP_SKIP_WAVE_BASE+1);	//this will get trimmed when fixed up
			}
		}


		EvalOrDefault(newwaypoint->action,BFieldWaypointActions,wpact,wpacnoactionno);
		logUID(newwaypoint);
		if (I.uid.Evaluate() !=ENABLE_COMPLEX_VAL && I.uid.Evaluate()<0)
		{
				SetLoc(-I.uid.Evaluate(),newwaypoint->uniqueID.count); //also need to fix references
				useUID(newwaypoint,UniqueID(I.uid.Evaluate()));
		}
		if (tmpwp)
		{
			tmpwp->next=newwaypoint;
			newwaypoint->prev=tmpwp;
		}
		else
			newwaypoint->prev=NULL;
		newwaypoint->next=NULL;
		return(newwaypoint->uniqueID.count);
	}
}

void	Persons3::FixWavesToLastRoute()
{
	if (GR_lastroutefirstwaypoint)
	{
		for (WayPoint* wp=ConvertPtrUID(UniqueID(GR_lastroutefirstwaypoint));wp;wp=wp->next)
		{
			if (wp->World.Y==0x80000000 || wp->World.Y==0x40000000)
				NOP;
			if (wp->skipover==WP_SKIP_WAVE_BASE)
			{
				if (lastroutenegwaveacs[wp->skipunder-WP_SKIP_WAVE_BASE][1])
				{
					wp->skipover=	lastroutenegwaveacs[wp->skipunder-WP_SKIP_WAVE_BASE][1];
					wp->skipunder=	lastroutenegwaveacs[wp->skipunder-WP_SKIP_WAVE_BASE][0];
				}
				else
				{
					wp->skipover=IllegalSepID;
					wp->skipunder=IllegalSepID;
				}
			}
			elseif (wp->skipover==WP_SKIP_WAVE_BASE+1)
			{
				if (lastrouteposwaveacs[wp->skipunder-WP_SKIP_WAVE_BASE][1])
				{
					wp->skipover=	lastrouteposwaveacs[wp->skipunder-WP_SKIP_WAVE_BASE][1];
					wp->skipunder=	lastrouteposwaveacs[wp->skipunder-WP_SKIP_WAVE_BASE][0];
				}
				else
				{
					wp->skipover=IllegalSepID;
					wp->skipunder=IllegalSepID;
				}
			}
		}
	}
	GR_lastroutefirstwaypoint=NULL;
	{for (int i=0;i<10;i++)
		lastrouteposwaveacs[i][0]=lastrouteposwaveacs[i][1]=UID_NULL;
	}
	{for (int i=0;i<4;i++)
		lastroutenegwaveacs[i][0]=lastroutenegwaveacs[i][1]=UID_NULL;
	}
}
//////////////////////////////////////////////////////////////////////
//
// Function:    FixUpWaypointsToGroup
// Date:		23/03/00
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	Persons3::FixUpWaypointsToGroup(int grpnum,int wavenum,UniqueID route,UniqueID leader,int numinflight, AirStrucPtr leaderptr)	//RJS 10Nov00
{		//tromp down the route. Any waypoint keyed to this group gets a UID based on leader uid.
	if (wavenum!=ENABLE_COMPLEX_VAL)
	{
		PairUID* table=lastrouteposwaveacs;
		if (wavenum<0)
		{
			table=lastroutenegwaveacs;
			wavenum=-wavenum;
		}
		if (table[wavenum][0]==0)
		{
			table[wavenum][0]=UniqueID(leader-(numinflight-1));
			table[wavenum][1]=leader;
		}
		else
		if (leader<table[wavenum][0])
		{
			assert(leader+1==table[wavenum][0]);
			table[wavenum][0]=UniqueID(leader-(numinflight-1));
		}
		else
		{
//DeadCode JIM 7Nov00 			assert(leader==table[wavenum][1]+1 && numinflight==1);
			table[wavenum][1]=leader;
		}
	}

	grpnum=(WP_SKIP_BASE)+(grpnum*WP_SKIP_GROUP);
	int grpnumupper=grpnum+numinflight-1;
	int grpnummax=grpnum+WP_SKIP_GROUP-1;
	ItemPtr airfieldalias=NULL;
	for(WayPointPtr w=*ConvertPtrUID(route);w;w=w->next)
	{
		bool	forthisac=false;
		if (w->skipunder==UID_NULL)
			forthisac=true;
		else
		if (	w->skipunder>=grpnum		//this is bottom of current grp range
			&&	w->skipunder<=grpnummax)	//this is a debug helper-max possible value
			if (w->skipunder<=grpnumupper)	//this is real top of current grp range
			{
				forthisac=true;
				w->skipunder=UniqueID(w->skipunder-grpnum+leader);
				if (w->skipover<=grpnumupper)	//if range goes over clip
					w->skipover=UniqueID(w->skipover-grpnum+leader);
				else
					w->skipover=UniqueID(leader+numinflight-1);
			}
		if (forthisac)
			if (w->action==wpatakeoffno || w->action==wpalandingno)
			{
				if (airfieldalias==NULL)	   //Use same point for takeoff and landing...
				{
					airfieldalias=w->target;
					if (!airfieldalias)		   //QM don't know home-base...
					{
						AirStrucPtr a=leaderptr;//ConvertPtrUID(leader);	//RJS 10Nov00
						if (a)
							airfieldalias=a->ai.homebase;
					}
					else
					{
// Don't want to fix-up the waypoint again!
						if (airfieldalias->SGT)					//RJS 09Nov00
							airfieldalias = NULL;
					}

					if (airfieldalias)
					{
						UniqueID SGT=airfieldalias->uniqueID.count;
						ItemPtr q=airfieldalias;
						for (int i=RunwaySBAND;i<RunwayEBAND;i++)
						{
							ItemPtr p=Persons2::ConvertPtrUID(UniqueID(i));
							if (p && p->SGT==SGT)
								if (!p->Status.deaded)
								{
									p->Status.deaded=TRUE;
									airfieldalias=p;
									break;
								}
								else
									q=p;
						}
						if (i==RunwayEBAND)
							airfieldalias=q;
					}
				}

				if (airfieldalias)								//RJS 09Nov00
				{
					w->target=airfieldalias;
					w->World.X=0;
					w->World.Z=0;
				}
			}

	}//for
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_itemS
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
int	Persons3::make_itemgroupcount(EventVal& E)
{
	return E.Evaluate();
}

void	Persons3::make_itemS(info_itemS& I,bool enabled)
{
	if (!enabled)
		return;
	if (justscanning)
	{
		if (I.uid.Evaluate()>=0)
			 UsedFixedUID=TRUE;
		return;
	}
//DEADCODE JON 07/03/00 	if (I.band.Evaluate()==BritAAASiteBAND && Math_Lib.rnd()>GR_AAALevel64K)
//DEADCODE JON 07/03/00 		return;	//Discard some AAA sites if low activity!!!!
//DEADCODE JON 07/03/00 
//DEADCODE JIM 16/11/99 	if (I.band.Evaluate()==RedAAALargeBAND)
//DEADCODE JIM 16/11/99 	{	//this may be quite painful!
//DEADCODE JIM 16/11/99 		assert (I.SGT);
//DEADCODE JIM 16/11/99 		if (SupplyTree::FindSupplyNodeForNodeItem(I.SGT)->status!=BEHINDREDLINES)
//DEADCODE JIM 16/11/99 			return;
//DEADCODE JIM 16/11/99 	}

	if (_DPlay.PlayerCreated && _DPlay.GameType<DPlay::COMMSQUICKMISSION)	// 13Oct00
	{
// dont want barrage balloons in deathmatchs as they are unnecessary and
// may slow game down

		if (I.band.Evaluate()==BarrageBalloonBAND || I.shape.Evaluate()==BALGRP)	// 13Oct00
			return;														// 13Oct00
	}

	itemptr	tmpitem = new item;
	tmpitem->SGT=I.SGT;
	make_events(I.events,tmpitem);
	if (I.uid.Evaluate()<0)
		if (I.band.Evaluate()==ENABLE_COMPLEX_VAL)
			tmpitem->uniqueID.count=assignuid(NeutMiscBAND);
		else
			tmpitem->uniqueID.count=assignuid(UniqueIDBand(I.band.Evaluate()));
	else
		tmpitem->uniqueID.count=UniqueID(I.uid.Evaluate());
	int sh=I.shape.Evaluate();
	if (sh==ENABLE_COMPLEX_VAL)
		_Error.EmitSysErr("Shape not set in item");
	*shapefield|=
		(tmpitem->shape=(ShapeNum)I.shape.Evaluate());
//DeadCode RJS 11Sep00 	if (I.attitude.Evaluate() != ENABLE_COMPLEX_VAL)
//DeadCode RJS 11Sep00 	{
//DeadCode RJS 11Sep00 		// Set anim for bridge shape....
//DeadCode RJS 11Sep00 		// ... and fill it in for animation
//DeadCode RJS 11Sep00 
//DeadCode RJS 11Sep00 		if (SHAPE.SetAnimData(tmpitem,0) == sizeof(ExplodeAnimData))
//DeadCode RJS 11Sep00 		{
//DeadCode RJS 11Sep00 			ExplodeAnimData*	adptr = (ExplodeAnimData*) tmpitem->Anim;
//DeadCode RJS 11Sep00 			adptr->frameno = I.attitude.Evaluate();
//DeadCode RJS 11Sep00 		}
//DeadCode RJS 11Sep00 	}

// Set anim data for balloon groups...
	if (tmpitem->shape == BALGRP)
		SHAPE.InitialiseBalloonGroup(tmpitem);

	setposition(tmpitem,I.position,TRUE);
	logUID(tmpitem);
	if (I.uid.Evaluate() !=ENABLE_COMPLEX_VAL && I.uid.Evaluate()<0)
	{
		SetLoc(-I.uid.Evaluate(),tmpitem->uniqueID.count); //also need to fix references
		useUID(tmpitem,UniqueID(I.uid.Evaluate()));
	}
	if (firstobject==IllegalSepID)
		firstobject=tmpitem->uniqueID.count;

//DeadCode JIM 08Jan96 		AddToWorld(tmpitem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_gndgrp
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::make_gndgrp(info_grndgrp& I)
{
	if (justscanning)
	{

		if (I.uid.Evaluate()>=0)
			 UsedFixedUID=TRUE;

		return;
	}
	int inform=I.inform.Evaluate();
	if (inform==ENABLE_COMPLEX_VAL)
		inform=1;
	if (inform<=-1)
	{
		inform=GR_FormSize00/-inform;
		if (inform<4)
		{
			inform=8;
			if (inform>GR_FormSize00)
				inform=GR_FormSize00;
			GR_FormSize00-=inform;
			if (GR_FormSize00!=0 && GR_FormSize00<inform)
			{
				GR_FormSize00+=inform;
				inform=GR_FormSize00/2;
				GR_FormSize00-=inform;
			}
		}
	}

	gotgrpnum=-1;
	if (inform)
	{
FormationItemPtr
		leadtruck=NULL,
		prevtruck=NULL,
		currtruck=NULL;
		FormationIndex	estformpos=FormationIndexMIN;
		int v1,v2;
		if ((v1=I.leader.Evaluate())!=ENABLE_COMPLEX_VAL)
		{
			prevtruck=
				leadtruck=*ConvertPtrUID((UniqueID)v1);
			if (leadtruck==NULL)
				_Error.EmitSysErr("Specified Lead truck not yet defined.");
		}
		bool	gotGRoverride=false;
		while (inform--)
		{
			currtruck=new	FormationItem;
			currtruck->SGT=I.SGT;
			if (leadtruck==NULL)
			{
				leadtruck=currtruck;
				currtruck->leader=NULL;
				currtruck->formpos=FormationIndexMIN;
			}
			else
			{
				currtruck->leader=leadtruck;
				prevtruck->follower=currtruck;
				currtruck->formpos=prevtruck->formpos+(InWing)1;
			}
			currtruck->follower=NULL;


			FormOrDefault(currtruck->nationality,Nationality,nat,NAT_RED);	//defaultside);
			EvalOrDefault(currtruck->formation,FormationTypeIndex,form,FTW_LWVIC);
			if ((v1=I.uid.Evaluate(estformpos))<0)
				if ((v2=I.band.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
//					if (currtruck->nationality==NAT_RED)
//						currtruck->uniqueID.count=assignuid(RedCombatVehicleBAND);
//					else
						currtruck->uniqueID.count=assignuid(BritMobileBAND);
				else
					currtruck->uniqueID.count=assignuid((UniqueIDBand)v2);
			else
				if (ConvertPtrUID(UniqueID(v1)))
				{
					currtruck->uniqueID.count=assignuid(getbandfromUID(UniqueID(v1)));
					if (I.SGT==UID_NULL)
						currtruck->SGT=UniqueID(v1);
				}
				else
				{
					currtruck->uniqueID.count=UniqueID(v1);
					if (v1==GR_ItemInfoOverride)
					{
						gotGRoverride=true;
						if (GR_redstrength>=100)
							inform=1;
						else
							inform=1+( inform*(101-GR_redstrength) )/100;
					}
				}

			if ((v1=I.type.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				currtruck->classtype=Plane_Type_Translate[PT_ATruck]_;
			else
				currtruck->classtype=Plane_Type_Translate[(v1)]_;

			if ((v1=I.shape.Evaluate(estformpos))==ENABLE_COMPLEX_VAL)
				currtruck->shape=currtruck->classtype->visible;
			else
				currtruck->shape=(ShapeNum)v1;


			EvalOrDefault(currtruck->movecode,AutoMoveCodeTypeSelect,movecode,AutoMoveCodeTypeSelect(GR_TruckMoveCode));
			currtruck->manoeuvretime=0;
			currtruck->slowdownleader=FALSE;					//JIM 18Jun97
			currtruck->information=IF_OUT_POS;							//JIM 18Jun97 //CSB 05/01/00
			currtruck->vel_x =0;												//RDH 26Feb96
			currtruck->vel_y =0;												//RDH 26Feb96
			currtruck->vel_z =0;												//RDH 26Feb96
//DEADCODE CSB 08/11/99 			currtruck->velhori =0;												//RDH 26Feb96

			FormOrDefault(currtruck->vel_,int,vel,VEL_10KT);//5 m/s or 10mph
			
			setpointer((ItemBasePtr*)&currtruck->waypoint,I.wpref);
			currtruck->roll=ANGLES_0Deg;										//JIM 21Oct96
			currtruck->pitch=ANGLES_180Deg;										//JIM 21Oct96
			if (gotGRoverride)
			{
				for (int wpcount=GR_ItemWpOverride;wpcount;wpcount--)
					if (currtruck->waypoint->next)
						currtruck->waypoint=currtruck->waypoint->next;
					else
					{
						currtruck->movecode=AUTO_NOPPILOT;
						currtruck->pitch=ANGLES_0Deg;
						currtruck->HdgIntercept=ANGLES_90Deg;
						if (currtruck->waypoint->prev)
							currtruck->InterceptandRange(&currtruck->waypoint->prev->World,&currtruck->waypoint->World);
						currtruck->hdg=currtruck->HdgIntercept;

					}
			}


			if (currtruck->formpos==0)
				if (gotGRoverride)
				{
					if (I.position.EvalW(currtruck->World))
					{
						currtruck->World.Y=0;
					}
					currtruck->World.X=GR_ItemXOverride;
					currtruck->World.Z=GR_ItemZOverride;
					AddToWorld(currtruck);
				}
				else
					setposition(currtruck,I.position,TRUE);			
			else
				setfollowerposition(currtruck);
			HP	hp;
			if (!I.attitude.EvalA(hp))
			{
				currtruck->hdg=hp.H;
				currtruck->pitch=hp.P;
			}
			else
			{
				if ( currtruck->pitch == ANGLES_180Deg )
					SetAngles (currtruck);						
			}
			logUID(currtruck);
			if (I.uid.Evaluate() !=ENABLE_COMPLEX_VAL && I.uid.Evaluate()<0)
			{
					SetLoc(I.uid.Evaluate(),currtruck->uniqueID.count); //also need to fix references
					useUID(currtruck,UniqueID(I.uid.Evaluate()));
			}
			currtruck->AddToList();
				
			estformpos+=(InForm)1;
			prevtruck=currtruck;
		}
		make_events(I.events,leadtruck);
		if (firstobject==IllegalSepID)
			firstobject=leadtruck->uniqueID.count;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_events
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::make_events(info_event_ptr&	I,ItemBasePtr P)
{
//DEADCODE JIM 17/03/99 	if (justscanning)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		return;
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 	info_event_ptr J=I;
//DEADCODE JIM 17/03/99 	I=NULL;
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 		info_event_ptr I=J;
//DEADCODE JIM 17/03/99 	while (I)
//DEADCODE JIM 17/03/99 	{
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		EventRecPtr	newevent;
//DEADCODE JIM 17/03/99 		int count=10;
//DEADCODE JIM 17/03/99 		int bfnum;
//DEADCODE JIM 17/03/99 		do
//DEADCODE JIM 17/03/99 		{
//DEADCODE JIM 17/03/99 			bfnum=I->bfields.Evaluate();
//DEADCODE JIM 17/03/99 			breakif (bfnum==ENABLE_COMPLEX_VAL);
//DEADCODE JIM 17/03/99 			if (BITTEST(usedevents,bfnum&255))
//DEADCODE JIM 17/03/99 				bfnum=ENABLE_COMPLEX_VAL;
//DEADCODE JIM 17/03/99 			else
//DEADCODE JIM 17/03/99 			{	//more complex: load the battlefield and
//DEADCODE JIM 17/03/99 				//test for used fixed UID flag
//DEADCODE JIM 17/03/99 				UsedFixedUID=FALSE;
//DEADCODE JIM 17/03/99 				{
//DEADCODE JIM 17/03/99 					WorldStuff* wpbackup=myworld;
//DEADCODE JIM 17/03/99 ////					justscanning=SCANNAMES;
//DEADCODE JIM 17/03/99 					{
//DEADCODE JIM 17/03/99 						LoadSubPiece(NULL,(FileNum)bfnum,(int)Persons2::LOADEDBFS-1,SCANNAMES);
//DEADCODE JIM 17/03/99 					}
//DEADCODE JIM 17/03/99 					myworld=wpbackup;
//DEADCODE JIM 17/03/99 	////				justscanning=LOAD;
//DEADCODE JIM 17/03/99 				}
//DEADCODE JIM 17/03/99 				if (UsedFixedUID)
//DEADCODE JIM 17/03/99 					BITSET(usedevents,bfnum&255);
//DEADCODE JIM 17/03/99 			}
//DEADCODE JIM 17/03/99 		} while (bfnum==ENABLE_COMPLEX_VAL && count--);
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		int i=I->usedsetvals;
//DEADCODE JIM 17/03/99 		if (bfnum!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 		{
//DEADCODE JIM 17/03/99 			newevent=new EventRec (P,i+1);
//DEADCODE JIM 17/03/99 			newevent->eventlist[i].Index=EventSet::GV_EVENT_EVENT;
//DEADCODE JIM 17/03/99 			newevent->eventlist[i].Value=bfnum;
//DEADCODE JIM 17/03/99 		}
//DEADCODE JIM 17/03/99 		else
//DEADCODE JIM 17/03/99 			newevent=new EventRec (P,i);
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		int v1;
//DEADCODE JIM 17/03/99 		newevent->eventwstart=
//DEADCODE JIM 17/03/99 			newevent->eventwend=0;
//DEADCODE JIM 17/03/99 		if ((v1=I->starts.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwstart+=v1*100;
//DEADCODE JIM 17/03/99 		if ((v1=I->startm.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwstart+=v1*60*100;
//DEADCODE JIM 17/03/99 		if ((v1=I->starth.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwstart+=v1*60*60*100;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		if ((v1=I->wins.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwend+=v1*100;
//DEADCODE JIM 17/03/99 		if ((v1=I->winm.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwend+=v1*60*100;
//DEADCODE JIM 17/03/99 		if ((v1=I->winh.Evaluate())!=ENABLE_COMPLEX_VAL)
//DEADCODE JIM 17/03/99 			newevent->eventwend+=v1*60*60*100;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 	
//DEADCODE JIM 17/03/99 		while (--i>=0)
//DEADCODE JIM 17/03/99 		{
//DEADCODE JIM 17/03/99 			newevent->eventlist[i].Index=I->setvals[i].index;
//DEADCODE JIM 17/03/99 			newevent->eventlist[i].Value=I->setvals[i].Evaluate();
//DEADCODE JIM 17/03/99 		}
//DEADCODE JIM 17/03/99 		if (newevent->eventwend)								//JIM 04Nov96
//DEADCODE JIM 17/03/99 			newevent->eventwend+=newevent->eventwstart+Timer_Code.realtime;
//DEADCODE JIM 17/03/99 		if (newevent->eventwstart)								//JIM 14Aug96
//DEADCODE JIM 17/03/99 			newevent->eventwstart+=Timer_Code.realtime;
//DEADCODE JIM 17/03/99 
//DEADCODE JIM 17/03/99 		I=(info_event_ptr)I->next;
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 	}
//DEADCODE JIM 17/03/99 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_setval
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::make_setval(EventVar& es)
{
	if (justscanning)
	{
		return;
	}
	SetLoc(es.index,es.Evaluate());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		make_string
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Inputs		t is one of:
//						T_comment	
//						T_name
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JIM 25/03/99 extern	MissionType CustomMission;
//DEADCODE JIM 25/03/99 extern	char	CustomMissionDesc[];
//DEADCODE JIM 25/03/99 extern	char	CustomMissionNews[];
//DEADCODE JIM 25/03/99 extern	char	CustomMissionTitle[];


void	Persons3::make_string(string src,int len,TokenCode t)
{
//DEADCODE JIM 25/03/99 	MissionType*	M=&CustomMission;

	if (justscanning)
	{
		switch (t)
		{
			case T_comment:
//DEADCODE JIM 25/03/99 				if ((UWord&)CustomMissionDesc[0])
//DEADCODE JIM 25/03/99 				{
//DEADCODE JIM 25/03/99 					if (!(UWord&)CustomMissionNews[0])
//DEADCODE JIM 25/03/99 					{
//DEADCODE JIM 25/03/99 						CustomMissionNews[1]=1;
//DEADCODE JIM 25/03/99 						strncpy(CustomMissionNews,src,len);
//DEADCODE JIM 25/03/99 						CustomMissionNews[len]=0;
//DEADCODE JIM 25/03/99 					}
//DEADCODE JIM 25/03/99 				}
//DEADCODE JIM 25/03/99 				else
//DEADCODE JIM 25/03/99 				{
//DEADCODE JIM 25/03/99 					CustomMissionDesc[1]=1;
//DEADCODE JIM 25/03/99 					strncpy(CustomMissionDesc,src,len);
//DEADCODE JIM 25/03/99 					CustomMissionDesc[len]=0;
//DEADCODE JIM 25/03/99 				}
			break;
			case T_name:
//DEADCODE JIM 25/03/99 				strncpy(CustomMissionTitle,src,len);
//DEADCODE JIM 25/03/99 				CustomMissionTitle[len]=0;
			break;
			case T_family:
			{
//DEADCODE JIM 25/03/99 				char dummyc;
//DEADCODE JIM 25/03/99 				int	dummyi;
//DEADCODE JIM 25/03/99 				sscanf(src,
//DEADCODE JIM 25/03/99 					"%i %i "
//DEADCODE JIM 25/03/99 					"%hi %hi "
//DEADCODE JIM 25/03/99 					"%c %c "
//DEADCODE JIM 25/03/99 					"%hi %hi %hi "
//DEADCODE JIM 25/03/99 					"%hi %hi %hi "
//DEADCODE JIM 25/03/99 					"%hi %hi "
//DEADCODE JIM 25/03/99 					"%hi %hi "
//DEADCODE JIM 25/03/99 					"%hi %hi %hi"
//DEADCODE JIM 25/03/99 					,
//DEADCODE JIM 25/03/99 					&M->missiondate,&M->timeofday,
//DEADCODE JIM 25/03/99 					&M->numofsquadronac,&M->numofflightac,
//DEADCODE JIM 25/03/99 					&dummyc/*M->PlayerNationality*/,&M->formationtypeindex,
//DEADCODE JIM 25/03/99 					&M->weathernum,&M->windspeed,&M->winddirection,
//DEADCODE JIM 25/03/99 					&dummyi,&dummyi,&dummyi,	//&M->era,&M->region,&M->PlayerAcType,
//DEADCODE JIM 25/03/99 					&dummyi,&dummyi,			//&M->PlayerHomeBase,&M->EnemyHomeBase,
//DEADCODE JIM 25/03/99 					&M->wplist->wpset[0]->mainobjective,&M->wplist->wpset[0]->subobjective,
//DEADCODE JIM 25/03/99 					&M->wplist->wpset[0]->wp1,&M->wplist->wpset[0]->wp2,&M->wplist->wpset[0]->wp3
//DEADCODE JIM 25/03/99 					);
//DEADCODE JIM 25/03/99 				//M->PlayerNationality&=31;
//DEADCODE JIM 25/03/99 				M->formationtypeindex=FormationTypeIndex(M->formationtypeindex&31);
			}
			break;
		}
	}
}
Bool	Persons3::make_eventname(string src,int len,info_event&)
{
	return TRUE;
}
Bool	Persons3::make_agname(string src,int len,info_airgrp&)
{
	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		used_globref
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::used_globref(int index)
{

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	EXTRA ROUTINES ONLY USED BY make_ routines
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Position modifiers
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setangles
//Author		R. Hyde 
//Date			Mon 26 Feb 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons3::SetAngles (FormationItemPtr	newmob)
{

	if (newmob->formpos == 0)
		if ((int)newmob->waypoint!=-1)
			if ((int)newmob->waypoint->target!=-1 && !(newmob->waypoint->World.Y&0x40000000))
			{
				newmob->InterceptandRange (newmob->FindDesPos ());
				newmob->pitch= newmob->PitchIntercept;
				newmob->hdg	= newmob->HdgIntercept;
				if (newmob->roll == ANGLES_180Deg)
					newmob->roll = ANGLES_0Deg;
			}
			else
				logsetangles(newmob,newmob->waypoint->uniqueID.count);
		else
			logsetangles(newmob,newmob->uniqueID.count);
	else
		if (newmob->leader->pitch!=ANGLES_180Deg)
		{
			newmob->pitch = newmob->leader->pitch;
			newmob->hdg = newmob->leader->hdg;
			if (newmob->roll == ANGLES_180Deg)
				newmob->roll = ANGLES_0Deg;
		}
		else
			logsetangles(newmob,newmob->leader->uniqueID.count);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setangles
//Author		R. Hyde 
//Date			Mon 26 Feb 1996
//
//Description
//
//Inputs
//
//Returns
//
//------------------------------------------------------------------------------
void	Persons3::SetAngles (AirStrucPtr	newac)
{

	if (newac->formpos == 0)
		if ((int)newac->waypoint!=-1)
			if ((int)newac->waypoint->target!=-1 && !(newac->waypoint->World.Y&0x40000000))
			{
				newac->InterceptandRange (newac->FindDesPos ());
				if (newac->PitchIntercept+ANGLES_10Deg>>ANGLES_20Deg)
					newac->pitch=ANGLES_0Deg;
				else
					newac->pitch= newac->PitchIntercept;
				newac->hdg	= newac->HdgIntercept;
				if (newac->roll == ANGLES_180Deg)
					newac->roll = ANGLES_0Deg;
			}
			else
				logsetangles(newac,newac->waypoint->uniqueID.count);
		else
			logsetangles(newac,newac->uniqueID.count);
	else
		if (newac->fly.leadflight->roll!=ANGLES_180Deg)
		{
			newac->pitch = newac->fly.leadflight->pitch;
			newac->hdg = newac->fly.leadflight->hdg;
			if (newac->roll == ANGLES_180Deg)
				newac->roll = ANGLES_0Deg;
		}
		else
			logsetangles(newac,newac->fly.leadflight->uniqueID.count);

	if (newac->vel_ == 0)											//RDH 04Sep96
	{															//RDH 04Sep96
		newac->fly.cpitch = ANGLES_0Deg;						//RDH 04Sep96
	}else
	{															//RDH 04Sep96
		newac->fly.cpitch = newac->pitch;
	}															//RDH 04Sep96
//	newac->fly.chdg = newac->hdg;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setfolloweroffset
//Author		Jim Taylor
//Date			Mon 22 Jan 1996
//
//Description	Set the offset position for a follower.
//
//Inputs		newac->formpos
//				If wing pos is non-zero then realive to leader
//				If wing pos is zero then relative to leadflight
//				newac->formation
//
//
//Returns		newac->world modified
//
//------------------------------------------------------------------------------
COORDS3D*	Persons3::setfolloweroffset(FormationItemPtr	newmob)
{
	newmob->HdgIntercept=newmob->hdg;							//AMM 19Aug97

	if (newmob->formpos != 0)
	{
		newmob->GetFollower_xyz ( newmob->formation);					//RDH 17Jun96

//		if (newmob->formation==FORM_EXPLODE					//AMM 19Aug97
//		|| newmob->formation==FORM_IMPLODE					//AMM 19Aug97
//		|| newmob->formation==FORM_RANDOM)					//AMM 19Aug97
			if (newmob->HdgIntercept!=newmob->hdg)					//AMM 19Aug97
			{													//AMM 19Aug97
			 	newmob->pitch=ANGLES_0Deg;						//AMM 19Aug97
				newmob->hdg=newmob->HdgIntercept;					//AMM 19Aug97
			}													//AMM 19Aug97

		return (&newmob->despos);
	}else
	{
		return (NULL);
	}


}

COORDS3D*	Persons3::setfolloweroffset(AirStrucPtr	newac)
{
	COORDS3D	*despos;

//DeadCode RDH 27Feb96 	if (newac->pitch == ANGLES_180Deg)
//DeadCode RDH 27Feb96 		SetAngles (newac);
	newac->HdgIntercept=newac->hdg;
	if (newac->formpos != 0)
	{
		if (	((newac->leader) && ((newac->leader->movecode == AUTO_TAKEOFF) || (newac->leader->movecode == AUTO_TRAININGTAKEOFF)))	//CSB 06/03/00
			||	((newac->fly.leadflight) && ((newac->fly.leadflight->movecode == AUTO_TAKEOFF) || (newac->fly.leadflight->movecode == AUTO_TRAININGTAKEOFF)))	)	//CSB 06/03/00
		{
			newac->pitch = newac->classtype->deckangle;			//JIM 04Dec96
//DeadCode JIM 27Nov96 			newac->pitch=ANGLES_5Deg;
			newac->movecode=AUTO_TAKEOFF;
			newac->vel_ = 0;										//RDH 30Sep96
//DEADCODE JIM 10/12/99 			newac->fly.vel_cms = 	0;							//RDH 30Sep96
//			newac->fly.vel_mms = 	0;							//RDH 30Sep96
			return (newac->PositionTakeOffWRTLeader ());
		}else
		{
			despos=newac->PositionWRTLeader();					//AMM 19Aug97

//			if (newac->formation==FORM_EXPLODE					//AMM 19Aug97
//			|| newac->formation==FORM_IMPLODE					//AMM 19Aug97
//			|| newac->formation==FORM_RANDOM)					//AMM 19Aug97
				if (newac->hdg!=newac->HdgIntercept)
				{
					newac->hdg=newac->HdgIntercept;
					newac->pitch=ANGLES_0Deg;
				}
			return despos;										//AMM 19Aug97
//DeadCode AMM 20Aug97 			return (newac->PositionWRTLeader ());
		}
	}else
	{
		if((newac->movecode==AUTO_TAKEOFF) || (newac->movecode==AUTO_TRAININGTAKEOFF))	//CSB 06/03/00
		{
//rdh			newac->hdg = MMC.wind.direction;				//RDH 02Aug96
			newac->pitch = newac->classtype->deckangle;			//JIM 04Dec96
			newac->roll = ANGLES_0Deg;
			newac->vel_ = 0;										//RDH 30Sep96
//DEADCODE JIM 10/12/99 			newac->fly.vel_cms = 	0;							//RDH 30Sep96
//			newac->fly.vel_mms = 	0;							//RDH 30Sep96
			return NULL;
		}	
		else
		if (newac->fly.leadflight)
			return	newac->PositionWRTLeader();
		else
			return (NULL);											//RDH 17Jun96
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	UID forward reference fixup 
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setposition
//Author		Jim Taylor
//Date			Tue 17 Jun 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void Persons3::setfollowerposition(AirStrucPtr it)
{
	if (it->fly.leadflight && it->fly.leadflight->pitch==ANGLES_180Deg)
	{
	 	logsetangles(it,it->fly.leadflight->uniqueID.count,followaccopy);
		return;
	}
	Coords3D* dp=setfolloweroffset(it);
	assert (dp);
	it->World=*dp;	//*setfolloweroffset(it);						  //JIM 25/04/99
	assert(it->fly.leadflight);
	if (it->fly.leadflight->World.Y&0x40000000)
		logworldcopy(it,it->fly.leadflight->uniqueID.count,TRUE);
	else
	 	AddToWorld(*it);
}
void Persons3::setfollowerposition(FormationItemPtr it)
{
	if (it->leader && it->leader->pitch==ANGLES_180Deg)
	{
	 	logsetangles(it,it->leader->uniqueID.count,followmobcopy);
		return;
	}
	it->World=*setfolloweroffset(it);
	assert(it->leader);
	if (it->leader->World.Y&0x40000000)
		logworldcopy(it,it->leader->uniqueID.count,TRUE);
	else
	 	AddToWorld(*it);
}

Bool Persons3::setposition( ItemBase* it, EventVal& pos, Bool addtoworld)
{
	UniqueID	rv=pos.EvalW(it->World);
	if ((rv) && (rv != IllegalSepID))
		logworldcopy(it,rv,pos,addtoworld);
	else
	{
		if (addtoworld)
			if (it->Status.size!=WayPointSize)
	 			AddToWorld(*it);
		int dy;
		if ((dy=it->World.Y) < 0)								//RDH 17Jun96
		{														//RDH 17Jun96
			it->World.Y =  Land_Scape.GetGroundLevel(it)	//RDH 17Jun96
										- it->World.Y;		//RDH 17Jun96
		//PAUL'S NEW ROUTINE RETURNS DELTA TO GROUND
		//	This is delta from given alt to ground level
		//  given is N below sea level
		//	I want abs above sea = ground + |given| = ground -given
		// this is paul's returned value!!! (Ok, so I'm lazy! :-)
		//	position.pos.Y =
		//		tmpitem->World.Y = -Land_Scape.GetGroundDelta(tmpitem);
			if (dy<-600)
				return(FALSE);
			else
				return(TRUE);
		}
	}
	return (FALSE);

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		setpointer
//Author		Jim Taylor
//Date			Fri 12 Jan 1996
//
//Description	Set the pointer to the item with the uid.
//				If the item does not yet exist then the 
//				pointer is noted until the UID is available.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void		Persons3::setpointer(ItemBasePtr	*targitemptr,UniqueID	srcuid)
{
	if ((*targitemptr=ConvertPtrUID(srcuid))==0)
		logpointercopy(targitemptr,srcuid);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		searchtree
//Author		Robert Slater
//Date			Tue 13 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UnresolvedUidNode**	Persons2::searchtree(UniqueID srcuid,UnresolvedUidNode **nextnode)
{
	UnresolvedUidNode		*currentnode,
							**currnodeptr=nextnode;

		while(*nextnode)
		{
			currnodeptr=nextnode;
			currentnode = *nextnode;

			if (srcuid == currentnode->uidattack)
				return(nextnode);

			if (srcuid < currentnode->uidattack)
				nextnode = &currentnode->less;
			else
				nextnode = &currentnode->more;

		}

		return(currnodeptr);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		adduidrequest
//Author		Robert Slater
//Date			Tue 13 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::adduidrequest(ItemBasePtr *trgitemptr,UniqueID srcuid)
{
	UnresolvedUidNode		*newnode = new UnresolvedUidNode;

	newnode->uidattack = srcuid;
	newnode->attackerptr = trgitemptr;
	newnode->request = ptrcopy;
	newnode->less = NULL;
	newnode->more = NULL;
	adduidrequest(newnode,srcuid);

}
void	Persons3::adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,EventVal& pos,UILogType request)
{
	UnresolvedUidNode		*newnode = new UnresolvedUidNode;
	newnode->posexpr = pos;
	newnode->uidattack = srcuid;
	newnode->posptr = trgitemptr;
	newnode->request = request;
	newnode->less = NULL;
	newnode->more = NULL;
	adduidrequest(newnode,srcuid);


}
void	Persons3::adduidrequest(ItemBasePtr trgitemptr,UniqueID srcuid,UILogType request)
{
	UnresolvedUidNode		*newnode = new UnresolvedUidNode;

	newnode->uidattack = srcuid;
	newnode->posptr = trgitemptr;
	newnode->request = request;
	newnode->less = NULL;
	newnode->more = NULL;
	adduidrequest(newnode,srcuid);
}
extern int 	debugmaxcount;
void	Persons3::adduidrequest(UnresolvedUidNode *newnode,UniqueID srcuid)
{
	UnresolvedUidNode	  **foundnode, *thenode;
	assert (srcuid);
	assert (srcuid==newnode->uidattack);
	assert (srcuid<debugmaxcount || srcuid>SagBANDEND || srcuid<WayPointBANDEND);

	if (rootuidnode == NULL)
	{
		rootuidnode = newnode;
	}
	else
	{
		// Search down the tree to correct node...

		foundnode = searchtree(srcuid);
		thenode = *foundnode;

		// Select branch...

		if (srcuid == thenode->uidattack)
		{
			//add to end of similar requests
			while (thenode->more && thenode->more->uidattack==srcuid)
				thenode=thenode->more;
			// Add to the greater node, and shuffle if it is occupied
			newnode->more = thenode->more;
			thenode->more = newnode;
			
		}
		else
		{
			// Must be less than or greater than, so no problem

			if (srcuid < thenode->uidattack)
				thenode->less = newnode;
			else
				thenode->more = newnode;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		logpointercopy
//Author		Jim Taylor
//Date			Fri 12 Jan 1996
//
//Description	Logs that the given item pointer needs fixing up when the
//				given unique id item is loaded.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::logpointercopy(ItemBasePtr *trgitemptr,UniqueID srcuid)
{
//DeadCode JIM 20Oct00 	UILogType	request = ptrcopy;
   
	adduidrequest(trgitemptr,srcuid);

	*trgitemptr=(ItemBasePtr)-1;

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		logworldcopy
//Author		Jim Taylor
//Date			Mon 8 Jan 1996
//
//Description	Logs data transfer to happen when source item is loaded
//				If 'addwhenfilled' is set then item is added to world when data
//				transfer is complete.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::logworldcopy(ItemBasePtr targitem,UniqueID srcUID,Bool	addwhenfilled)
{
	targitem->World.Y|=0x40000000;
	EventVal	tmp;
	UILogType	request = worldcopy;

	if (addwhenfilled)
		request = addworldcopy;
	if (srcUID==0)
		_Error.EmitSysErr("Asked for zero UID source");
	adduidrequest(targitem,srcUID,request);
}
void	Persons3::logworldcopy(ItemBasePtr targitem,UniqueID srcUID,EventVal& pos,Bool	addwhenfilled)
{
	targitem->World.Y|=0x40000000;
	UILogType	request = worldcopy;

	if (addwhenfilled)
		request = addworldcopy;
	if (srcUID==0)
		_Error.EmitSysErr("Asked for zero UID source");

	adduidrequest(targitem,srcUID,pos,request);
}

void	Persons3::logsetangles(AirStrucPtr targitem,UniqueID srcUID)
{
	logsetangles(targitem,srcUID,anglesaccopy);
}

void	Persons3::logsetangles(FormationItemPtr targitem,UniqueID srcUID,UILogType request)
{
	adduidrequest(targitem,srcUID,request);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		logUID
//Author		Jim Taylor
//Date			Wed 18 Jun 1997
//
//Description	puts item in uid lookup and sets pointers
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::logUID(ItemBasePtr	selecteditem)
{
	UniqueID		theuid;

//DeadCode JIM 20Oct00 	if (selecteditem->uniqueID.count==0x012e)
//DeadCode JIM 20Oct00 	{
//DeadCode JIM 20Oct00 		int bp=0;
//DeadCode JIM 20Oct00 
//DeadCode JIM 20Oct00 	}

	theuid = selecteditem->uniqueID.count;

	assert(pItem[theuid]==NULL&&"UID already used!");
	assert(pItem[theuid]==0&&"Reused!");
	pItem[theuid] = selecteditem;
}

Bool	Persons3::useUID(ItemBasePtr	selecteditem)
{
	return useUID(selecteditem,selecteditem->uniqueID.count);
}

Bool	Persons3::useUID(ItemBasePtr	selecteditem,UniqueID theuid)
{

	UnresolvedUidNode			*swapnode, **foundnode, *thenode, *nextnode, **rightmostnode;
	Bool			finished = FALSE;
	ItemBasePtr		*attackerptr;
	UILogType	 	request;
	Bool	retval=FALSE;
	bool redodirect;
	while(!finished)
	{
		finished = TRUE;
		foundnode = searchtree(theuid);
		redodirect=false;
		thenode = *foundnode;
		Bool	skippedone;
		do{
			skippedone=FALSE;
			if (	thenode	&&	thenode->uidattack==theuid	)
			{
				if ( 	(	thenode->request==worldcopy
						||	thenode->request==addworldcopy
						)
					&&	(	selecteditem->World.Y&0x40000000
						||	(	selecteditem->Status.size==WAYPOINTSIZE
							&&	(int)((WayPoint*)*selecteditem)->target==-1
					)	)	)
				{
					if (theuid<0)
					{
						redodirect=true;
					}
					else
					{
						foundnode=&foundnode[0]->more;
						thenode = *foundnode;
						skippedone=TRUE;
					}
				}
				else											//JIM 22Oct97
				if	(	thenode->request==anglesaccopy
					||	thenode->request==anglesmobcopy
					||	thenode->request==followaccopy
					||	thenode->request==followmobcopy
					)
					if (	(	selecteditem==thenode->posptr
							&&	(int)((FormationItem*)*selecteditem)->waypoint==-1
							)
						|| 	(	selecteditem!=thenode->posptr
							&&	(	(	selecteditem->Status.size==WAYPOINTSIZE
									&& 	(	(selecteditem->World.Y&0x40000000)
										||	(int)(((WayPoint*)*selecteditem)->target)==-1
									)	)
								||	(	(selecteditem->Status.size==ITEMSIZE)
									&&	(selecteditem->World.Y&0x40000000)
									)
								||	(	(selecteditem->Status.size>=MOBILESIZE)
									&& (((MobileItem*)*selecteditem)->pitch==ANGLES_180Deg)
						)	)	)	)
					{
						if (theuid<0)
						{
							redodirect=true;
						}
						else
						{
							foundnode=&foundnode[0]->more;
							thenode = *foundnode;
							skippedone=TRUE;
						}
					}
			}
		}while (skippedone);

		if (thenode)
			if (thenode->uidattack == theuid)
			{
				finished = FALSE;

				if (redodirect)												  //JIM 15/12/99
				{															  //JIM 15/12/99
 					UnresolvedUidNode		*newnode = new UnresolvedUidNode; //JIM 15/12/99
					newnode->UnresolvedNodeData::operator=(*thenode);		  //JIM 15/12/99
					newnode->uidattack = UniqueID(GetLoc(-theuid));			  //JIM 15/12/99
					adduidrequest(newnode,newnode->uidattack);				  //JIM 15/12/99
				}															  //JIM 15/12/99
				else
				{
					// Extract data...

					retval=TRUE;
					request = thenode->request;

					switch (request)
					{
					case ptrcopy :
					{
						attackerptr = thenode->attackerptr;
						*attackerptr = selecteditem;
					}
					break;
					case followaccopy:
					{
						setfollowerposition((AirStrucPtr)*thenode->posptr);
					}
					break;
					case followmobcopy:
					{
						setfollowerposition((FormationItemPtr)*thenode->posptr);
					}
					break;
					case anglesaccopy:
					{
						SetAngles((AirStrucPtr)*thenode->posptr);
					}
					break;
					case anglesmobcopy:
					{
						SetAngles((FormationItem*)*thenode->posptr);
					}
					break;
					case worldcopy :
					case addworldcopy :
					{
						Coords3D	t;

						UniqueID rv=UID_Null;
						if (thenode->posexpr.complex)
							rv=thenode->posexpr.EvalW(t);
						else
							t=selecteditem->World;
						if (rv)
						{	//need to put this expression back into to-do list!
							//but can take old one out...
							if (rv==thenode->uidattack)
								_Error.EmitSysErr("Forward reference fixup gone recursive!");
							if (rv<0)
								NOP;
							adduidrequest(thenode->posptr,rv,thenode->posexpr,request);
						}
						else
						{
							thenode->posptr->World.Y &=~0x40000000;
							thenode->posptr->World.X =
								thenode->posptr->World.X + t.X;
							thenode->posptr->World.Y =
								thenode->posptr->World.Y + t.Y;
							thenode->posptr->World.Z =
								thenode->posptr->World.Z + t.Z;

							if (request == addworldcopy)
								AddToWorld(*thenode->posptr);
						}
					}
					break;
					}
				}
			
				// Tidy tree...

				nextnode = thenode->more;

				if (thenode->less)
				{
					swapnode = thenode->less;

					rightmostnode = searchtree(theuid,&swapnode);

					(*rightmostnode)->more = nextnode;
				}
				else
				{
					swapnode = thenode->more;
				}

				*foundnode = swapnode;

				delete thenode;

			}
	}
	return retval;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		anyoutstanding
//Author		Robert Slater
//Date			Thu 15 Feb 1996
//
//Description	Checks if any outstanding UIDs on the tree.
//				If there are, we try to fix them up properly.
//
//				If there are still some left 
//				then return TRUE so the caller can raise an error code
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

Bool	Persons3::recurseanyoutstanding(UnresolvedUidNode* node)
{
	UniqueID	nextatt=node->uidattack;
	ItemBasePtr	B=ConvertPtrUID(nextatt);
	if (B)
		if (useUID(B,nextatt))
			return TRUE;
	if (node->less)
		if (recurseanyoutstanding(node->less))
			return TRUE;
	if (node->more)
		if (recurseanyoutstanding(node->more))
			return TRUE;
	return FALSE;
}

void	Persons3::RecurseDeRefGlobRefs(UnresolvedUidNode* node)
{
	node->posexpr.DeRefGlobRefs();
	if (node->less)
		RecurseDeRefGlobRefs(node->less);
	if (node->more)
		RecurseDeRefGlobRefs(node->more);
}

Bool	Persons3::anyoutstanding()
{
	if (rootuidnode!=NULL)
		RecurseDeRefGlobRefs(rootuidnode);

	while (rootuidnode!=NULL)
		if (!recurseanyoutstanding(rootuidnode))
			return TRUE;										//JIM 10Sep97
	return FALSE;												//JIM 10Sep97
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	UID/World interface
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

void Persons3::InitGamePiece()
{
//DEADCODE DAW 12/05/99 	File_Man.DiscardDirList(FIL_RUNTIMEPACK0);
	for (int i=0;i<LOADEDBFS;i++)
		loadedBF[i]=FIL_NULL;

	if (_Replay.Playback)
	{
		Pack_PlayerSquad=_Replay.PlayerSquad;
		Pack_PlayerPos=_Replay.PlayerPos;
		MMC.playersquadron=_Replay.PlayerSquad;					//AMM 17Nov98
		MMC.playeracnum=_Replay.PlayerPos;						//AMM 17Nov98
	}
	else
	{
		Pack_PlayerSquad=MMC.playersquadron;
		Pack_PlayerPos=MMC.playeracnum;
	}

	for (i=0;i<MAXCALLNAMES;i++)
		callsignnamecount[i]=1;
    ClearGlobrefStaticVars();
//DEADCODE DAW 08/03/00 	while (eventloglist)
//DEADCODE DAW 08/03/00 	{
//DEADCODE DAW 08/03/00 		EventLogPtr	tmp=eventloglist;
//DEADCODE DAW 08/03/00 		eventloglist=tmp->next;
//DEADCODE DAW 08/03/00 		delete tmp;
//DEADCODE DAW 08/03/00 	}

//	ClrMessage(UserMsg::NOMSG);									//JIM 23Oct96

	for (i=0;i<32;i++)
		usedevents[i]=0;
	mobileitem::MobileList=NULL;
	mobileitem::ACList=NULL;
	mobileitem::SAGList=NULL;											//CSB 19Jul00
	TransientItem::TransientList=NULL;							//PD 11May96
	Art_Int.CleanUp();
	Manual_Pilot.ControlledAC2=NULL;
	pilotedaircraft=NULL;
//	GR_EnemyScoutSquad=											//RDH 15Sep97
//		GR_FriendlyScoutSquad=
//			GR_EnemyChargeSquad=
//				GR_FriendlyChargeSquad=JastaAnon;
			
}
void	Persons3::InitSubPiece()
{
	offsetinformationleaderflights=0;
	if (!justscanning)
	{
		prevSAGsquadron=NULL;
		firstobject=IllegalSepID;
//DEADCODE DAW 08/03/00 		eventloglist=new EventLog(eventloglist);
//DEADCODE DAW 08/03/00 	   if (inst3d)
//DEADCODE DAW 08/03/00 		eventloglist->launchtime=inst3d->timeofday;
///		eventloglist->launchtime=Timer_Code.realtime;
		shapefield=new ShapeNumField;
		*shapefield=0;
	}
}
void Persons3::EndSubPiece()
{
	if (!justscanning)
	{
		FixWavesToLastRoute();

		AddPreLoadFXShapes();									//RJS 02Apr99

		SHAPESTUFF.AddShapesToGlobList(shapefield);
		delete shapefield;
		shapefield=NULL;
	}
}
  
void Persons3::FinishSetPiece()
{
	_Replay.DumpData("finish.txt");

	GR_TruckMoveCode=GROUND_TOGLOBREF;

	for (int p=0;p<Profile::MAX_PACKS;p++)
		Todays_Packages.ClearPack(p);
	Todays_Packages.hiwp=UID_NULL;

//DeadCode AMM 21Feb100 	SLong len;
//DeadCode AMM 21Feb100 	UWord oldsector;

	//get airfield altitudes loaded. This causes too much grief otherwise
//DEADCODE JIM 16/11/99 	for (int afnum=0;SupplyTree::airfieldinfo[afnum].nationality!=NAT_ALIGN;afnum++)
//DEADCODE JIM 16/11/99 	{
//DEADCODE JIM 16/11/99 		ItemPtr I=*ConvertPtrUID(SupplyTree::airfieldinfo[afnum].airfield);
//DEADCODE JIM 16/11/99 		if (I->World.Y==0)
//DEADCODE JIM 16/11/99 			I->World.Y=Land_Scape.GetGroundLevel(I,NULL,true);
//DEADCODE JIM 16/11/99 	}


//DeadCode CSB 20Jun00 	AirStrucPtr ac=*Persons2::ConvertPtrUID((UniqueID)0x10a7);

	if (_DPlay.Implemented)
	{
		if (_DPlay.Host)
		{
			_DPlay.SendBFieldsToPlayers(false);
			_DPlay.CommsStage[DPlay::STAGE_BFIELDS][0]=true;
		}

		if (_DPlay.GameType==DPlay::COMMSQUICKMISSION)
		{
			if (_DPlay.Joining)
			{
				_DPlay.SendIDRequest();
			}

			_DPlay.WaitForPlayersUniqueIDs();
		}
	}

//DeadCode AMM 17Nov98 //	if (_Replay.Record)
//DeadCode AMM 17Nov98 		_Replay.AddFileAndGlobRefsToList(FIL_NULL);

	if (!_Replay.Playback)
		SENT_REQ=FALSE;
	if (anyoutstanding())
		_Error.EmitSysErr("Unresolved UIDS! One is: %x",rootuidnode->uidattack);

//DeadCode CSB 20Jun00 	ac=*Persons2::ConvertPtrUID((UniqueID)0x10a7);

	SagExpansionCounter::totalexpanded=0;
	SagExpansionCounter::highdemandrange=METRES2000;					//DAW 15/02/00
	ExpandPilotedFlights();
//	if(Miss_Man.camp.playerbfield!=FIL_NULL)
//	{
		if (!Manual_Pilot.ControlledAC2)							//JIM 04Sep97
			_Error.EmitSysErr("No player A/C set up on entering 3d!");//JIM 04Sep97
//	}

// create extra instance of Airstruc, if one does not already exist.

// GhostAC is one used by AI. 
// SeenAC is one seen and moved by player.

// Deltas sent are difference between predictor and actual movement

//	WorldStuff &world = mobileitem::GetWorld();

	if(Persons2::PlayerGhostAC==Persons2::PlayerSeenAC)								//JIM 12Sep97
	{
		AirStrucPtr newac=new AirStruc;

		if (newac==NULL)
			_Error.SayAndQuit("could not create newac");

		DeleteModel(newac);				//newac->fly.pModel;
		newac->fly.pModel=NULL;				   // DeleteModel

		Persons2::PlayerSeenAC=newac;
		newac=NULL;
		
	}

//DeadCode AMM 23Jul98 	if (_Replay.Playback)
//DeadCode AMM 23Jul98 	{
//DeadCode AMM 23Jul98 		Manual_Pilot.controlmode==ManualPilot::AUTO;
//DeadCode AMM 23Jul98 	}

	Persons2::PlayerGhostAC=Manual_Pilot.ControlledAC2;

// both AC start off the same

//DeadCode AMM 16Nov99 	_DPlay.CopyBuffer((char*)Persons2::PlayerSeenAC,(char*)Persons2::PlayerGhostAC,sizeof(AirStruc));
 	memcpy((char*)Persons2::PlayerSeenAC,(char*)Persons2::PlayerGhostAC,sizeof(AirStruc));

	Manual_Pilot.ControlledAC2=Persons2::PlayerSeenAC;

	Persons2::PlayerGhostAC->fly.pModel=NULL;

	Persons2::PlayerGhostAC->Anim=ANIM_NULL;

	Persons2::PlayerSeenAC->AddToList();
	
	if(		(!Persons2::PlayerSeenAC->formpos)
		&&	(!Persons2::PlayerSeenAC->fly.expandedsag) 
		&&	(!Art_Int.Remove(Persons2::PlayerSeenAC))		) //CSB 04/02/00
		_Error.SayAndQuit("Cant remove seenac");

// remove ghost from sectorlist and add seen

	myworld->RemoveFromWorld(Persons2::PlayerGhostAC);
	myworld->AddToWorld(Persons2::PlayerSeenAC);

// need to remove ghostac from aclist 

	AirStrucPtr Me = *AirStruc::ACList;

	if (Me==Persons2::PlayerGhostAC)
	{
		AirStruc::ACList=*Me->nextmobile;
	}
	else
	{
		while (Me && Me->nextmobile!=Persons2::PlayerGhostAC)
		{
			Me=*Me->nextmobile;
		}

		if (Me)
		{
			Me->nextmobile=Me->nextmobile->nextmobile;
		}
		else
			_Error.SayAndQuit("cant remove ac from aclist");
	}
	
// nobble UID pointer!							 

	pItem[Persons2::PlayerGhostAC->uniqueID.count]=NULL;

	logUID(Persons2::PlayerSeenAC);
	Squad_Diary.CreatePlayer(Persons2::PlayerSeenAC->ai.diaryptr);					//RJS 27Jan00

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToWorld
//Author		Jim Taylor
//Date			Mon 8 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void		Persons3::AddToWorld(ItemPtr	tmpitem)
{
	myworld->AddToWorld(tmpitem);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Event run-time stuff
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Colour schemes: also sets up piloted A/C
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//typedef void (*ha)(AirStrucPtr,FormationIndex,UByte* colours);
//ha	Persons3::Colour_Rule_List[]
//		={
//			&Persons3::ColourRulePlayerSquadron,
//			&Persons3::ColourRulePlayerAuto,
//			&Persons3::ColourRulePaintShop,
//			&Persons3::ColourRuleAllRandom,
//			&Persons3::ColourRuleDefined,
//		};
  //
	//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ColourRules
//Author		Jim
//Date			Sun 7 Apr 1996
//
//Description	Various coded methods for colouring squadrons.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////
//
// Function:    SetLettering
// Date:		13/03/00
// Author:		DAW
//
//Description: 
// THE MAIN CODE GENERATES
//		HIJK MNOP RSTU
//I want to skip vowels:
//		HKLV MNPW RSTX
//////////////////////////////////////////////////////////////////////
static char LW_letters[]=
{	/*A*/	 'A'-'A',
	/*B*/	 'B'-'A',
	/*C*/	 'C'-'A',
	/*D*/	 'D'-'A',
	/*E*/	 'E'-'A',
	/*F*/	 'F'-'A',
	/*G*/	 'G'-'A',

	/*H*/	 'H'-'A',
	/*I*/	 'K'-'A',
	/*J*/	 'L'-'A',
	/*K*/	 'V'-'A',

	/*L*/	 'L'-'A',

	/*M*/	 'M'-'A',
	/*N*/	 'N'-'A',
	/*O*/	 'P'-'A',
	/*P*/	 'W'-'A',

	/*Q*/	 'Q'-'A',

	/*R*/	 'R'-'A',
	/*S*/	 'S'-'A',
	/*T*/	 'T'-'A',
	/*U*/	 'X'-'A',

	/*V*/	 'V'-'A',
	/*W*/	 'W'-'A',
	/*X*/	 'X'-'A',
	/*Y*/	 'Y'-'A',
	/*Z*/	 'Z'-'A',

};
void	AirStruc::SetLettering(int lettering)
{
	int l1,l2,l3,l4;
	int	pilotnum=lettering>>16;
	lettering&=0xffff;
	if (lettering>=64000)
		if (lettering>=64000+40*26)
		{	//LW FIGHTER - ALWAYS IN 12s
			l1=lettering%40;
			l2=((lettering/40)%40)+10;	//assumes #35 is '9' and #36 is blank

			int flnum=pilotnum/4;
			int stnum=flnum/4;
			flnum=flnum%4;
			pilotnum=pilotnum%4;
			pilotnum=pilotnum+flnum*4+stnum*3*4+1;
			l3=pilotnum/10;
			if (l3==0)
				l3=36;
			else
				l3+=26;
			l4=(pilotnum%10)+26;
		}
		else
		{	//RAF fighter //Should be DW = 3, 22 for spit A
			l1=lettering%40;
			l2=((lettering/40)%40);
			l3=pilotnum;
			l4=0;
		}
	else
	{	//LW bomber
		l1=lettering%40;
		l2=((lettering/40)%40);
		l4=LW_letters[((lettering/1600)%40)];
		l3=pilotnum;
	}
	AircraftAnimData*	anim=Anim;
	anim->imagemapacid1 = l1;							//RJS 11Mar99
	anim->imagemapacid2 = l2;							//RJS 11Mar99
	anim->imagemapacid3 = l3;							//RJS 11Mar99
	anim->imagemapacid4 = l4;							//RJS 11Mar99
}
//////////////////////////////////////////////////////////////////////
//
// Function:    ColourRulePlayerSquadron
// Date:		13/03/00
// Author:		DAW
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
void	Persons3::ColourRulePlayerSquadron(AirStrucPtr	newac,FormationIndex formpos,UByte* s,int pilotmarking,UWord* damagetable)
{	//EVERYTHING COMES HERE NOW!!!!!
	newac->weap.Weapons=s[COLS_BOMBS];									//AMM 07Apr99
	{
		if (SHAPE.SetAnimData(newac,s[COLS_BOMBS])!=sizeof(AircraftAnimData))	//DAW 12May98... 0 is weapon pack
			_Error.EmitSysErr("Animation not aircraft");
		AircraftAnimData*	anim=(AircraftAnimData*)newac->Anim;
		for (int i=0;i<QMD_OTHER-QMD_LEFTWINGOUT;i++)
			if (damagetable[QMD_OTHER-i]!=0xffff)
				*(&anim->OTHER-i)=damagetable[QMD_OTHER-i];
		int inwingpos,outwingpos;
		newac->SetLettering(pilotmarking);

	}
	if ((int)Pack_PlayerPos==-1)			//RDH 27Aug96
	{															//PD 26Jun96
		Manual_Pilot.Associate(newac,ManualPilot::MANUAL);						//RDH 17Jun96

		if (_DPlay.Implemented && _DPlay.GameType==DPlay::COMMSQUICKMISSION)
		{
			_DPlay.SendMyUniqueID((UWord)(newac->uniqueID.count));
			_DPlay.AllocPacket[_DPlay.mySlot]=(UWord)(newac->uniqueID.count);
			newac->uniqueID.commsmove=TRUE;
		}

//		viewpoint->SetToPiloted(newac);							//PD 26Jun96
		SHAPE.SetPilotedAcAnim(newac);							//PD 26Jun96
		Pack_PlayerPos--;
		if((newac->movecode==AUTO_TAKEOFF))// || (newac->movecode==AUTO_TRAININGTAKEOFF))
		{
			newac->movecode=AUTO_FOLLOWWP;
//DeadCode AMM 29Aug00 			newac->playermoving=false;
		}
//DeadCode AMM 29Aug00 		else
//DeadCode AMM 29Aug00 			newac->playermoving=true;
//DeadCode AMM 29Aug00 		newac->playernotmovingheldac=NULL;
		UpdateLog(newac,0,EventLog::TAKEOFF);
	}
	else
		Manual_Pilot.InitManualPilotSub(newac);			//rdh 9/6 
	Float	fuelchange=1.0;
	if (damagetable[QMD_FUELKILOS]!=0xffff)
	{
		int loadedfuel=newac->fly.fuel_content[0]+newac->fly.fuel_content[1]+newac->fly.fuel_content[2]+newac->fly.fuel_content[3];
		fuelchange=damagetable[QMD_FUELKILOS]*100000.0/loadedfuel;
	}
	if (damagetable[QMD_FUELPERCENT]!=0xffff)
		fuelchange=damagetable[QMD_FUELPERCENT]/100.0;
	if (fuelchange!=1.0)
	{
		newac->fly.fuel_content[0]*=fuelchange;
		newac->fly.fuel_content[1]*=fuelchange;
		newac->fly.fuel_content[2]*=fuelchange;
		newac->fly.fuel_content[3]*=fuelchange;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Maintaining lists of allocated waypoints so they can be freed in the endgame
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


void	Persons3::AddRoute(UniqueID	firstwp)
{
	RouteHdr	*tmp=new RouteHdr;
	tmp->next=myworld->routelist;
	myworld->routelist=tmp;
	tmp->waypoint=firstwp;
	tmp->numusers=0;
}


void	Persons3::FreeRoutes()
{
	RouteHdr*	tmphdr=myworld->routelist;
	myworld->routelist=NULL;
	while(tmphdr)
	{
		WayPointPtr	tmpwp=*ConvertPtrUID(tmphdr->waypoint);
		while(tmpwp)
		{
		 	WayPointPtr	tmpwp2=tmpwp->next;
			delete(tmpwp);
			tmpwp=tmpwp2;
		}
		RouteHdr*	tmphdr2=tmphdr->next;
		delete tmphdr;
		tmphdr=tmphdr2;
	}	
	ContourList::FreeList();

}


void	Persons3::FreeEvents()
{
//DEADCODE JIM 17/03/99 	while (EventRec::eventbase)	delete EventRec::eventbase;

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//	Runtime/endgame routines to getting info on items
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


//
//
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PreScanBF
//Author		R. Hyde 
//Date			Tue 12 Aug 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::PreScanBF(FileNum f)
{
//DEADCODE JIM 25/03/99 	(UWord&)CustomMissionDesc[0]=0;
//DEADCODE JIM 25/03/99 	(UWord&)CustomMissionNews[0]=0;
//	justscanning=SCANNAMES;
	LoadSubPiece(NULL,f,(int)LOADEDBFS-1,SCANNAMES);
//DEADCODE JIM 25/03/99 	CustomMission.playerbf=f;
  //	justscanning=LOAD;
}
//
//


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddPreLoadFXShapes
//Author		Robert Slater
//Date			Fri 2 Apr 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	Persons3::AddPreLoadFXShapes()
{
 	*shapefield|=SMOKE;
 	*shapefield|=EXPLO;
 	*shapefield|=BULLET;		//bullet
 	*shapefield|=BSMKE;
 	*shapefield|=SMLFIR;
 	*shapefield|=FIRE;
 	*shapefield|=BEXP;
 	*shapefield|=RSMOKE;
 	*shapefield|=SDUST;
 	*shapefield|=BDUST;
 	*shapefield|=CANNON;		//mig cannon blob
 	*shapefield|=SWAVE;			//explosion shockwave	//RJS 15Dec99
 	*shapefield|=SMKBIG;								//RJS 15Dec99
 	*shapefield|=PLUME1;
 	*shapefield|=BULGND;
 	*shapefield|=BULWAT;
 	*shapefield|=DRTYX;
 	*shapefield|=MUSHY;
 	*shapefield|=SPLASH;
 	*shapefield|=GNDEXP;
 	*shapefield|=FIREB;
 	*shapefield|=PLUME2;
 	*shapefield|=FLASH;
 	*shapefield|=SMKSHP;

// New ones...															//RJS 25Sep00
 	*shapefield|=SPARKY;
 	*shapefield|=SHCKWV;
 	*shapefield|=SMFLSH;
 	*shapefield|=ACBTS0;
 	*shapefield|=ACBTS1;
 	*shapefield|=ACBTS2;
 	*shapefield|=ACBTS3;
 	*shapefield|=DRTSHK;
 	*shapefield|=DEB5;
 	*shapefield|=VSFSMK;
 	*shapefield|=SBANKM;
 	*shapefield|=SMKMED;
 	*shapefield|=SMKDRK;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    ExpandPilotedFlights
// Date:		09/12/99
// Author:		JIM
//
//Description: 
//
//////////////////////////////////////////////////////////////////////
static float weights[]= {	 1.0,1.0,1.0,1.0,1.0,1.0,	0.5,0.6,0.3,	0.1	};	
void	Persons3::ExpandPilotedFlights()
{
	{for (int i=0;i<=PT_GER_NONFLY;i++)
		sagexpcounts[i].currenttriggerrange=(sagexpcounts[i].maxtriggerrange+sagexpcounts[i].mintriggerrange)/2;
	}
	//Need to work out how many of each type of real aircraft to launch...
//	The rules, here, are:
//1) Up to 44	A/C reserved for medium bombers if any. All bombers then forgotten. (leaves 340)
//2) 24	A/C reserved for each A/C type with > 24 instances. These instances then forgotten.
//3) Else less	A/C reserved for each A/C type with < 24 instances. That type then forgotten
//4) Up to 24	more A/C reserved for player's aircraft type, and those aircraft then forgotten
//5) Else 24	more A/C distributed and reserved for any aircraft type engaged by the player, those A/C then forgotten
//6) The remaining aircraft 384 -44 -24*n -24 -24 are weighted by type.
//	Stuka	30%
//	ME109	50%
//	ME110	60%
//	Spit	100%
//	Hurr	100%
//Any A/C type that has less instances left than we want to add gets it's number of instances 
//7) Repeat (6) until no types less than required outstanding
//8) Apply remainder to aircraft that are left using same weighting.
	MobileItem::currworld=myworld;
	int availablerealaircraft=384;
	int	i;
	for (i=0;i<PT_VEHICLES;i++)		availablerealaircraft-=instancesAC[i];
	instancesSAG[PT_GER_NONFLY]=instancesSAG[PT_DO17]+ instancesSAG[PT_JU88]+ instancesSAG[PT_HE111];
	for (i=0;i<=PT_GER_NONFLY;i++)
		sagexpcounts[i].SAGsoftype=instancesSAG[i];

	sagexpcounts[PT_GER_NONFLY].numavailable=44;
	for (i=0;i<PT_GER_NONFLY;i++)
		sagexpcounts[i].numavailable=24;

	if (pilotedaircraft && pilotedaircraft->uniqueID.count<SagBANDEND)
	{
		sagexpcounts[pilotedaircraft->classtype->planetext].numavailable+=24;	
		//need to get some allocated to other combatants...
	}
	for (i=0;i<=PT_GER_NONFLY;i++)
	{
		int is=instancesSAG[i]-sagexpcounts[i].numavailable;
		if (is<0)
		{
			sagexpcounts[i].numavailable+=is;	//add a negative value
			instancesSAG[i]=0;
		}
		else
			instancesSAG[i]=is;
	}
	for (i=0;i<=PT_GER_NONFLY;i++)
		availablerealaircraft-=sagexpcounts[i].numavailable;	
	bool donesome;
	forever
	{
		float	stilltoallocate=0;
		for (i=0;i<PT_GER_NONFLY;i++)
			stilltoallocate+=instancesSAG[i]*weights[i];
	breakif(!stilltoallocate);
		donesome=false;
		float	rate=availablerealaircraft/stilltoallocate;
 		for (i=0;i<=PT_GER_NONFLY;i++)
		{
			int replace=instancesSAG[i]*weights[i]*rate+0.1;
			if (replace>availablerealaircraft)
				replace=availablerealaircraft;
			if (replace>instancesSAG[i])
				replace=instancesSAG[i];
			if (replace>0)
			{
				instancesSAG[i]-=replace;
				availablerealaircraft-=replace;
				sagexpcounts[i].numavailable+=replace;
				donesome++;
			}
		}
	breakif(!donesome);
	}
	//Ok.. so now I know how many I want of each type... lets allocate them:
	for (i=0;i<=PT_GER_NONFLY;i++)
	{
		sagexpcounts[i].numactive=0;
		if (sagexpcounts[i].numavailable)
		{
			sagexpcounts[i].basenum=Make3dAC(PlaneTypeSelect(i));
			AirStrucPtr currac=ConvertPtrUID(sagexpcounts[i].basenum);	//CSB 9Aug00
			currac->currworld->AddToWorld(currac);							//CSB 9Aug00
			sagexpcounts[i].reservedactive=0;
			for (int j=sagexpcounts[i].numavailable;--j;)
			{
				UniqueID newacuid=Make3dAC(PlaneTypeSelect(i));
				AirStrucPtr currac=ConvertPtrUID(newacuid);				//CSB 9Aug00
				currac->currworld->AddToWorld(currac);							//CSB 9Aug00

			}
		}
	}

//DeadCode CSB 10Oct00 	for(AirStrucPtr sag = AirStrucPtr(MobileItem::SAGList); sag; sag = AirStrucPtr(sag->nextmobile))
//DeadCode CSB 10Oct00 		sag->PatchGroupAndAnim();

	AirStrucPtr(MobileItem::ACList)->ClearUpAI();

	//Now need to launch some for the player, and for any other 'interesting' squadrons:
	if (pilotedaircraft && pilotedaircraft->uniqueID.count<SagBANDEND)
	{
		AirStrucPtr leader = pilotedaircraft->ExpandSag(true);
		if(pilotedaircraft->fly.expandedsag->movecode == AUTO_COMBAT)
			for(AirStrucPtr ld = pilotedaircraft->fly.expandedsag; ld; ld = ld->fly.nextflight)
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

					mobileitem::currworld->AddToWorld(ac);		//RJS 27Oct00
				}

		while (Pack_PlayerPos--)
		{
			if (leader->follower)
				leader=leader->Follower();
			else
				leader=leader->Leader()->fly.nextflight;
		}

		//need to find n'th aircraft...	 and assign it to player:

		Manual_Pilot.Associate(leader,ManualPilot::MANUAL);						//RDH 17Jun96
		SHAPE.SetPilotedAcAnim(leader);							//PD 26Jun96
		UpdateLog(leader,0,EventLog::TAKEOFF);
//DEADCODE DAW 08/03/00 		if (leader->ai.homebase)
//DEADCODE DAW 08/03/00 			leader->ai.eventlog->homebase=leader->ai.homebase->uniqueID.count;


	}
}

inline ShapeNum&	AirStruc::GetDrawShape()
{
	if (_DPlay.PlayerCreated && _DPlay.GameType < DPlay::COMMSQUICKMISSION)
		return classtype->commsVisible;

	return classtype->visible;
}

ShapeNum&	AirStruc::_GetDrawShape()
{
	return GetDrawShape();
}
