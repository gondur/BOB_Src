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

//Filename       flymodel.cpp
//System         
//Author         R. Hyde 
//Date           Mon 11 Sep 1995
//Description    THIS IS THE OLD INTEGER BASED FLIGHT MODEL, OR REMNANTS OF IT!
//------------------------------------------------------------------------------

//#define		_NOFLIGHTMODEL_

#include	"dosdefs.h"
#define F_GRAFIX
#define F_COMMON
#include	"files.g"
#include	"worldinc.h"
#include	"planetyp.h"
#include	"myangles.h"
#include	"enumbits.m"
#include	"mytime.h"											//RDH 25Apr96
//MATHABLE	(ANGLES)
#include	"flymodel.h"
#include	"mymath.h"
#include	"vertex.h"
#include	"matrix.h"											//RDH 23May96
//TEMPCODE DAW 13/04/00 #include	"textref.h"
#include	"viewsel.h"											//PD 19Feb96
#include	"hardpasm.h"										//RDH 14Mar96
#include	"3dcom.h"											//PD 16Apr96
#include	"landscap.h"									//PD 15Mar96
#include	"missman2.h"										//JIM 22Aug96
#include	"savegame.h"
#include	"miles.h"											//DAW 04Jul96
#include	"world.h"											//DAW 04Jul96
#include	"transite.h"										//RDH 26Jul96
#include	"collided.h"										//PD 06Sep96
#include	"speed.h"
#include "persons2.h"											//RDH 24Jul96
#include	"ranges.h"
#include	"winmove.h"											//ARM 10Oct96
#include	"modvec.h"											//ARM 08Jan97
#include	"model.h"											//ARM 07Jan97
#include	"shapes.h"
#include	"replay.h"
#include	"sqddiary.h"
#include	"boxcol.h"													//AMM 4Jul00

//extern	ULong	GR_Quit3DNow;
extern DPlay _DPlay;

										//ARM 06Nov96
//-----------------------------------------------------------------------------------------
//1	Permanent notes on the flight model	
//
//
//	1	Units
//			 	vel,i_a_s			10 cm/s
//				vel_cm  			cm/s
//				vel_mm  			cm/s
//				WorldX,Y,Z			cm
//				forces				N
//				airdensity			g/m^3
//				sos					m/s
//				angles				all use full word
//				trig functions		signed word, 7fff = 1.0, 8000 = -1	
//
//	2	In the model, y is reversed:
//
//			cposy = -ControlledAC->World.Y; 		world y postion of ac
//			
//	3	Angles 					
//			    roll right wing down = +ve
//				hdg change to right  = +ve
//				pitch up			 = +ve
//				
//		When the ac is pointing above the velocity vector, then aoa = +ve
//		When the ac has a bigger heading than velocity vector, then slip = -ve
//
//
//
//DeadCode RDH 26Mar98 //	4	Defining an aircraft
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		See separate notes
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	5	Use of Rudder:
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			Oppose torque of engine
//DeadCode RDH 26Mar98 //			to produce side slip
//DeadCode RDH 26Mar98 //			keep level near stall (ailerons use lead to spin?)
//DeadCode RDH 26Mar98 //			balance adverse drag
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			In old model 1,3,4 absent 
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			When rudder is applied, aircraft skids. Side slip angle
//DeadCode RDH 26Mar98 //			angle and dihedral work to produce roll
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			When aircraft is rolled with ailerons, slip is produced
//DeadCode RDH 26Mar98 //			Slip and weathercocking effect of tail give heading change of
//DeadCode RDH 26Mar98 //			aircraft.Dihedral also has effect of unrolling
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	7	Aileron effects
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //			On applying aileron, drag on wings in changed in opposite 
//DeadCode RDH 26Mar98 //			directions. This can produce an adverse yaw
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	8	Moments
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	8.1	Pitch
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	8.2	Roll
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		+ve slip gives -roll
//DeadCode RDH 26Mar98 //				effect increased by dihedral
//DeadCode RDH 26Mar98 //				effect caused by dihedral gving bigger aoa for one wing
//DeadCode RDH 26Mar98 //				and reduced lift on wing in shadow of body		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		torque on prop (and rotary engines)
//DeadCode RDH 26Mar98 //					opposite and equal, is it rate of change of torque or magnitude
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		ailerons
//DeadCode RDH 26Mar98 //				increase aoa on upper wing	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		roll of aircraft (lateral damping)
//DeadCode RDH 26Mar98 //				relative wind on down wing produce higher aoa, hence increases lift
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		overbanking tendency
//DeadCode RDH 26Mar98 //				slip gives yaw which means one wing is travelling faster
//DeadCode RDH 26Mar98 //				which gives roll
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	8.3 Yaw
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		rudder
//DeadCode RDH 26Mar98 //		slipstream
//DeadCode RDH 26Mar98 //		precedence
//DeadCode RDH 26Mar98 //			prop turning clockwise from pilot seat
//DeadCode RDH 26Mar98 //			right turn gives downward force
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		p effect
//DeadCode RDH 26Mar98 //		
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		adverse yaw
//DeadCode RDH 26Mar98 //			rolling wing means lift difference which means drag difference	
//DeadCode RDH 26Mar98 //		weather cocking
//DeadCode RDH 26Mar98 //			tail moves ac into relative wind
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	9	Forces
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //		For lift, consider effect on body lift (important for knife-edge)
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //


//-----------------------------------------------------------------------------------------
//2	Notes on relationship with rest of code
//
//
//	1	We calculate the position of a point on the aircraft. There are a number of
//		significant points:
//					pilot eye
//					centre around which aircraft turns
//					centre of drawn shape
//		At present we don't distinguish between two
//
//	2	Changing from auto to manual has changed, I will probably need to know
//		so that trim can be allowed
//
//	3	
// 
//DeadCode RDH 26Mar98 //	4	SetFlags, WayPointUpdate and FuelLeft is commented out	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	5	The thrust routine needs to be accessed indirectly
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	6	damage lights needed for effect on thrust, aileron and elevator
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//	8	
//	 	if (ControlledAC2 == ControlledAC)
//				true for manual pilot
//
//DeadCode RDH 26Mar98 //	9	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	10	
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //	12	I've introduced a 1cm/sec velocty field for the flight model, vel_cms.
//DeadCode RDH 26Mar98 //		ControlledAC->vel is still in 10cm/s units. vel_cms in not used
//DeadCode RDH 26Mar98 //		in other equations
//DeadCode RDH 26Mar98 //		Also introduced mm/s to reduce rounding error
//DeadCode RDH 26Mar98 //
//DeadCode RDH 26Mar98 //-----------------------------------------------------------------------------------------
//DeadCode RDH 26Mar98 //Static data
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //elevator deflection constant,  see taillift and Theory of Flight p502
//DeadCode RDH 26Mar98 //increments in 5 deg deviation steps
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96 static UWord 	ElevatorDeflection_Data[] =
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  			{
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  						0,20,40,65,
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  						90,120,
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  //30
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  					155,
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  					190,225,
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  //45
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  					280
//DeadCode RDH 26Mar98 //DeadCode RDH 17Jun96  			};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 static UWord 	ElevatorDeflection_Data[] =
//DeadCode RDH 26Mar98  			{
//DeadCode RDH 26Mar98  						0,15,30,50,
//DeadCode RDH 26Mar98  						80,100,
//DeadCode RDH 26Mar98  //30
//DeadCode RDH 26Mar98  					120,
//DeadCode RDH 26Mar98  					140,160,
//DeadCode RDH 26Mar98  //45
//DeadCode RDH 26Mar98  //DeadCode RDH 07Dec96 					175
//DeadCode RDH 26Mar98  					190											//RDH 07Dec96
//DeadCode RDH 26Mar98  			};
 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //increments in 1000m steps
//DeadCode RDH 26Mar98 //mach in m/s
//DeadCode RDH 26Mar98 static UWord 	Mach_Data[] =
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 				340,
//DeadCode RDH 26Mar98 				337,
//DeadCode RDH 26Mar98 				333,
//DeadCode RDH 26Mar98 				329,
//DeadCode RDH 26Mar98 				325,
//DeadCode RDH 26Mar98 				321,
//DeadCode RDH 26Mar98 				317,
//DeadCode RDH 26Mar98 				313,
//DeadCode RDH 26Mar98 				308,
//DeadCode RDH 26Mar98 				304,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				295,
//DeadCode RDH 26Mar98 				297,
//DeadCode RDH 26Mar98 				298,
//DeadCode RDH 26Mar98 				299
//DeadCode RDH 26Mar98 			};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //increments in 1000m steps
//DeadCode RDH 26Mar98 //density in g/m^3
//DeadCode RDH 26Mar98 static UWord AirDensity_Data[] = 
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				1225,
//DeadCode RDH 26Mar98 				1112,
//DeadCode RDH 26Mar98 				1007,
//DeadCode RDH 26Mar98 				909,
//DeadCode RDH 26Mar98 				819,
//DeadCode RDH 26Mar98 				736,
//DeadCode RDH 26Mar98 				660,
//DeadCode RDH 26Mar98 				590,
//DeadCode RDH 26Mar98 				526,
//DeadCode RDH 26Mar98 				467,
//DeadCode RDH 26Mar98 				414,
//DeadCode RDH 26Mar98 				365,
//DeadCode RDH 26Mar98 				312,
//DeadCode RDH 26Mar98 				267,
//DeadCode RDH 26Mar98 				228,
//DeadCode RDH 26Mar98 				195,
//DeadCode RDH 26Mar98 				195,
//DeadCode RDH 26Mar98 				166,
//DeadCode RDH 26Mar98 				142,
//DeadCode RDH 26Mar98 				122,
//DeadCode RDH 26Mar98 				104,
//DeadCode RDH 26Mar98 				89,
//DeadCode RDH 26Mar98 				76,
//DeadCode RDH 26Mar98 				65
//DeadCode RDH 26Mar98 			};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //Table of SQR(DensityRatio) * 65536
//DeadCode RDH 26Mar98 //DensityRatio is ratio of air density at altitude to air density at sea level 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 static UWord AirDensity_Ratio[] =
//DeadCode RDH 26Mar98 			{
//DeadCode RDH 26Mar98 				65535,
//DeadCode RDH 26Mar98 				63250,
//DeadCode RDH 26Mar98 				61250,
//DeadCode RDH 26Mar98 				59375,
//DeadCode RDH 26Mar98 				57500,
//DeadCode RDH 26Mar98 				55625,
//DeadCode RDH 26Mar98 				53625,
//DeadCode RDH 26Mar98 				51750,
//DeadCode RDH 26Mar98 				49875,
//DeadCode RDH 26Mar98 				48250,
//DeadCode RDH 26Mar98 				46500,
//DeadCode RDH 26Mar98 				44875,
//DeadCode RDH 26Mar98 				43250,
//DeadCode RDH 26Mar98 				41625,
//DeadCode RDH 26Mar98 				40000,
//DeadCode RDH 26Mar98 				38500,
//DeadCode RDH 26Mar98 				37000,
//DeadCode RDH 26Mar98 				35375,
//DeadCode RDH 26Mar98 				33625,
//DeadCode RDH 26Mar98 				31875,
//DeadCode RDH 26Mar98 				30250,
//DeadCode RDH 26Mar98 				28500,
//DeadCode RDH 26Mar98 				27125,
//DeadCode RDH 26Mar98 				25750
//DeadCode RDH 26Mar98 	};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 static UWord ManualPilot::airdensityratiosquareroot[] =
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 			{
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				65535,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				64383,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				63357,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				62280,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				61387,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				60377,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				59282,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				58236,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				57172,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				56233,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				55203,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				54230,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				53239,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				52230,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				51200,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				50231,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				49243,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				48149,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				46943,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				45705,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				44525,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				43218,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				42162,
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 				41080
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 	};
//DeadCode RDH 26Mar98 //DeadCode RDH 25Jun96 
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 static UWord Shok_Data[] = 
//DeadCode RDH 26Mar98 	{
//DeadCode RDH 26Mar98 		0,
//DeadCode RDH 26Mar98 		0,
//DeadCode RDH 26Mar98 	     0,
//DeadCode RDH 26Mar98 	     0,
//DeadCode RDH 26Mar98 	     1,
//DeadCode RDH 26Mar98 	     5,
//DeadCode RDH 26Mar98 	     10,
//DeadCode RDH 26Mar98 	     120,
//DeadCode RDH 26Mar98 		600,
//DeadCode RDH 26Mar98 		1000,
//DeadCode RDH 26Mar98 		1000,
//DeadCode RDH 26Mar98 		1000,
//DeadCode RDH 26Mar98 		1000,
//DeadCode RDH 26Mar98 		1130,
//DeadCode RDH 26Mar98 		1190,
//DeadCode RDH 26Mar98 		1250,
//DeadCode RDH 26Mar98 		1300,
//DeadCode RDH 26Mar98 		1350,
//DeadCode RDH 26Mar98 		1400,
//DeadCode RDH 26Mar98 		1470,
//DeadCode RDH 26Mar98 		1490,
//DeadCode RDH 26Mar98 		1500
//DeadCode RDH 26Mar98 	};
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 //flight model equates
//DeadCode RDH 26Mar98 SLong const 	SHORTGRASSCOEFF 	=	30;						//RDH 22Oct96
//DeadCode RDH 26Mar98 SLong const 	LONGGRASSCOEFF 		=	40;
//DeadCode RDH 26Mar98 SLong const 	ANGLE2DIV 	=	2 * 65536/360;
//DeadCode RDH 26Mar98 SLong const 	ROT_X_DAMP 	=	80;
//DeadCode RDH 26Mar98 SLong const 	ROT_Y_DAMP 	=	80;
//DeadCode RDH 26Mar98 SLong const 	ROT_Z_DAMP 	=	80;
//DeadCode RDH 26Mar98 SLong const 	MAXALTITUDE_CM 	=	2200000;
//DeadCode RDH 26Mar98 SLong const 	WORD_FRACT   	=	65536;
//DeadCode RDH 26Mar98 SLong const 	LIFTCONST   	=	100 * 65536 / 360;
//DeadCode RDH 26Mar98 SLong const 	ROWANS_PER_RAD  =	10430;		//65536 / 2PI;
//DeadCode RDH 26Mar98 SLong const 	PITCHCOEFF   	=	104;		//PITCHCOEFF = 	WORD_FRACT / TWOPI100			
//DeadCode RDH 26Mar98 SLong const 	GROUNDEFFECT 	=	1000;		//cms
//DeadCode RDH 26Mar98 SLong const 	K_MACH  	 	=	21500;
//DeadCode RDH 26Mar98 SLong const 	LIMOLDPITCH     =	0x1200;
//DeadCode RDH 26Mar98 SLong const 	FLAP_A_SHIFT 	=	28;
//DeadCode RDH 26Mar98 SLong const 	GEFF_CL_ADJUST  =	15;
//DeadCode RDH 26Mar98 SLong const 	FLAP_CL_ADJUST  =	44;            // (2*FLAP_A_SHIFT) * 80 /100
//DeadCode RDH 26Mar98 SLong const 	FLAP_CMO_ADJUST =	13;
//DeadCode RDH 26Mar98 SLong const 	FLAP_CMO_2 		=	2;
//DeadCode RDH 26Mar98 SLong const 	FLAP_DRAG 		=	3;
//DeadCode RDH 26Mar98 SLong const 	RUDDERVEL		=	1250;
//DeadCode RDH 26Mar98 SLong const 	RUDDERVELP2		=	(RUDDERVEL * RUDDERVEL) / 256;
//DeadCode RDH 26Mar98 SLong const 	ELEVPLUS1		=	1;
//DeadCode RDH 26Mar98 SLong const 	HALFPI100		=	157;
//DeadCode RDH 26Mar98 SLong const 	PI100			=	314;
//DeadCode RDH 26Mar98 SLong const 	TWOPI100		=	628;
//DeadCode RDH 26Mar98 SLong const		ROLLEDCLIMBFACTOR = 4000;
//DeadCode RDH 26Mar98 //DeadCode RDH 29Aug96 SLong const		MINVELO			=	20;
//DeadCode RDH 26Mar98 SLong const		MINVELO			=	4;							//RDH 29Aug96
//DeadCode RDH 26Mar98 SLong const		KRITVEL			=	100;						//RDH 23May96
//DeadCode RDH 26Mar98 SLong const		VELMIN 			= 700;
//DeadCode RDH 26Mar98 SLong const		VELMAX 			= 2400;
//DeadCode RDH 26Mar98 SLong const		VELRANGE 		= 3*(VELMAX-VELMIN)/2;
//DeadCode RDH 26Mar98 SLong const		VEL_MAXSLIPSTREAM = 1790;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 SLong const		POWER_MAXSLIPSTREAM = 65000;
//DeadCode RDH 26Mar98 SLong const		POWER_MAXSLIPSTREAM = 100;
//DeadCode RDH 26Mar98 //DeadCode RDH 03Dec96 SLong const		AOA_MAXSLIPSTREAM = 2000;
//DeadCode RDH 26Mar98 SLong const		AOA_MAXSLIPSTREAM = 600;
//DeadCode RDH 26Mar98 //DeadCode RDH 23Jul96 SLong const		FLIGHTMODEL_TIMEFRAME = 2;						//RDH 25Apr96
//DeadCode RDH 26Mar98 SLong const		FLIGHTMODEL_TIMEFRAME = TimerCode::FIXEDFRAMETIME;						//RDH 25Apr96
//DeadCode RDH 26Mar98 
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//INSTANCE		Manual_Pilot
//Author		Jim Taylor
//Date			Tue 31 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ManualPilot	Manual_Pilot;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManualPilot	CONSTRUCTOR
//Author		R. Hyde 
//Date			Thu 26 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
	ManualPilot::ManualPilot()
{
	View_Point=NULL;
//DeadCode RDH 26Mar98 	elevatordeflectiondata = ElevatorDeflection_Data;
// 	machdata=Mach_Data;
//	airdensitydata=AirDensity_Data;
//	airdensityratio=AirDensity_Ratio;
//DeadCode RDH 03Jun96 	airdensityratiosquareroot=AirDensity_Ratio_SquareRoot;
//	shokdata=Shok_Data;
	ControlledAC2=NULL;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Associate
//Author		Jim Taylor
//Date			Tue 31 Oct 1995
//
//Description	Associates specific 3d item to manual movecode.
//				May also be used to flag auto/manual switch,
//				so put any trim init code here!
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::Associate	(
			AirStruc*	manualas,				//item to move
			CONTROLMODE		inmanual)		//TRUE	//flag for man/auto/auto accel
{
	if  (inmanual!=controlmode || ControlledAC2!=manualas)
	{
		controlmode=inmanual?MANUAL:AUTO;
		ControlledAC2=manualas;
		InitManualPilot(ControlledAC2);
	}
}
//JIM 15Oct96

void	ManualPilot::AutoToggle(CONTROLMODE dead)
{
	if (dead==PILOTDEAD)
		controlmode=PILOTDEAD;
	else
		if (controlmode!=PILOTDEAD)								//JIM 11Oct96
		{														//JIM 11Oct96
			ControlledAC2->information=IF_ALLBAD;
			ControlledAC2->slowdownleader=FALSE;
			if (dead==TOGGLE)									//JIM 11Oct96
			{
				dead=controlmode==AUTO?MANUAL:AUTO;
				Associate(ControlledAC2,dead);
			}
			else AutoToggleAircraft(ControlledAC2,dead);					//rdh 6/4/98
		}														//JIM 11Oct96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		R. Hyde 
//Date		Wed 30 Aug 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::MainManualPilot()
{
//TempCode PD 3Nov97 
//	return;
//TempCode PD 3Nov97 

//Add timing thing here	//CSB 02/03/99
	
	if (ControlledAC2)
	{
		WorldStuff &world = mobileitem::GetWorld();
		UWord	oldsector=	world.GetSector(ControlledAC2);

//DeadCode AMM 12Jul00 		_DPlay.CheckSeen();

///////////////////////////////////////////
//tmp fix should not be running acm on player ac in final version//RDH 20Aug96
		if(controlmode == MANUAL)
		{
			if((Persons2::PlayerGhostAC->timeofday & 0x07ff == 0) && (Persons2::PlayerGhostAC->slowdownleader))
			{
				Persons2::PlayerGhostAC->slowdownleader = FALSE;		  //JIM 22/03/99
				AirStrucPtr found = NULL;
				for(AirStrucPtr l = Persons2::PlayerGhostAC; (l) && (!found); l = l->fly.nextflight)
					for(AirStrucPtr w = l; (w) && (!found); w = w->Follower())
						if((w->movecode == AUTO_FOLLOWWP) && (w->information == IF_OUT_POS) && (Persons2::PlayerGhostAC->vel_ > w->vel_))
						{
							found = w;
							_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_TOOFAST, MSG_FORMATIONFLYING_RPT, found, NULL, Persons2::PlayerGhostAC));
						}
			}

			GetKeyCommon (ControlledAC2);				//RDH 15Dec95

//DeadCode AMM 01Dec98 		}
//DeadCode AMM 01Dec98 //DeadCode CSB 15/09/98		 	ControlledAC2->FuelLeft ();								//RDH 03Jun96
//DeadCode AMM 01Dec98 
//DeadCode AMM 01Dec98 		if (controlmode == MANUAL)
//DeadCode AMM 01Dec98 		{
			if (!_Replay.Playback)
			{
				_DPlay.CheckSeen();
				_DPlay.AddDeltas(Persons2::PlayerSeenAC,FALSE,1); 				
#ifndef	_NOFLIGHTMODEL_
 				FlightModelFixedTime(Persons2::PlayerSeenAC);
#endif
 				Persons2::PlayerSeenAC->SetManualFlightParams ();

				_DPlay.AddDeltas(Persons2::PlayerSeenAC,TRUE,1);				
				_DPlay.BackupSeen();
			}


			SHAPE.RipStores(ControlledAC2);						//RJS 03Jun98

//			ControlledAC2->CheckManualCourse();					//JIM 03Dec96
//being done by macca.
//DEADCODE JIM 22/03/99 			Persons2::PlayerGhostAC->CheckManualCourse();
		}
		else if (controlmode==AUTOACCEL_WAYPT || controlmode==AUTOACCEL_FWD ||
				controlmode==AUTOACCEL_MSG || controlmode==AUTOACCEL_MISS ||
				controlmode==AUTOACCEL_HOME)
		{
			_DPlay.CheckSeen();
			_DPlay.AddDeltas(Persons2::PlayerSeenAC,FALSE,2); 				//AMM 10Mar99
			AutoMoveCodeTypeSelect bupMoveCode=ControlledAC2->movecode;
			ControlledAC2->movecode=AUTO_ACCELERATE;
			mobileitem::MoveItem((MobileItemPtr)ControlledAC2,world);
			ControlledAC2->movecode=bupMoveCode;
			_DPlay.AddDeltas(Persons2::PlayerSeenAC,TRUE,2);				//AMM 10Mar99
			_DPlay.BackupSeen();
		}
		else
		{
//			if (controlmode == MANUAL)								//RDH 20Aug96
//				GetStickKeys(ControlledAC2);

//DeadCode AMM 16Jun98 			if(_DPlay.Implemented)								//AMM 15Apr97
			if (!_Replay.Playback)
			{													
// this moves players ac if player is not in control i.e autospiral, autores etc
																
//				WorldStuff &world = mobileitem::GetWorld();		
									
				_DPlay.CheckSeen();
				_DPlay.AddDeltas(ControlledAC2,FALSE,3);			
				mobileitem::MoveItem((MobileItemPtr)(ControlledAC2),world);
				_DPlay.AddDeltas(ControlledAC2,TRUE,3);
				_DPlay.BackupSeen();

// update info line
				if (_DPlay.Implemented)
		 			OverLay.SetInfoLineVals(Persons2::PlayerSeenAC->vel_ * 0.001, 0, Persons2::PlayerSeenAC->World.Y * (3.2808 / 100), Persons2::PlayerSeenAC->hdg / 182, Persons2::PlayerSeenAC->fly.thrustpercent); 
			}
			else												//AMM 31Aug98
			{													//AMM 31Aug98
// shouldnt ever get in here?
				INT3;
//DeadCode AMM 07Oct98 				_DPlay.PredictMove(Persons2::PlayerSeenAC);		//AMM 31Aug98
//DeadCode AMM 07Oct98 				Persons2::PlayerSeenAC->fly.pModel->Base (Persons2::PlayerSeenAC);

 			}													//AMM 31Aug98


//			View_Object->right_aoa = ControlledAC2->fly.aoa;
//			View_Object->left_aoa = ControlledAC2->fly.aoa;
		}

///////////////////////////////////////////

		if (ControlledAC2->uniqueID.changed)
		{
			UWord	newsector=	world.GetSector(ControlledAC2);
			if (newsector!=oldsector)
			{
				world.RemoveFromSector(ControlledAC2,oldsector);
				world.AddToWorld(ControlledAC2);
			}
			ControlledAC2->uniqueID.changed = FALSE;						//RDH 26Jun96
		}

//DeadCode AMM 12Jul00 		_DPlay.BackupSeen();
 	}
//Add timing thing here	//CSB 02/03/99

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeathSequenceOverride
//Author		Robert Slater
//Date			Wed 15 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DeadCode AMM 26Jan99 Bool	ManualPilot::DeathSequenceOverride(ItemPtr	itm, int	newmovecode)//DAW 03Sep98
Bool	ManualPilot::DeathSequenceOverride(ItemPtr	itm, int	newmovecode,bool commscalled)//AMM 26Jan99
{
//DeadCode CSB 14Aug00 #ifndef NDEBUG															//CSB 14Aug00
//DeadCode CSB 14Aug00 	if(itm->Status.size == AIRSTRUCSIZE)								//CSB 14Aug00
//DeadCode CSB 14Aug00 		AirStrucPtr(itm)->DoAllSAGChecks();								//CSB 14Aug00
//DeadCode CSB 14Aug00 #endif																	//CSB 14Aug00

	Bool	wasset = FALSE;										//DAW 03Sep98
	if (itm->Status.size == AIRSTRUCSIZE)						//RJS 25Nov99
	{
		AirStrucPtr		acptr = (AirStrucPtr) itm;

		if((acptr->movecode == AUTO_SPAREAC) || (acptr->movecode == AUTOSAG_DESTROYED))
		{
			INT3;
			return(TRUE);
		}

		if (!acptr->fly.numinsag)								//MS 20Jun00
		{
			acptr->ai.ManStep = 0;								//RJS 03Nov00

			MinAnimData*	mad = (MinAnimData*) acptr->Anim;

			if (	(acptr->movecode != newmovecode)
				&&	(acptr->movecode != AUTO_NOPPILOT)					//RJS 27Aug98
				&&	(acptr->movecode != AUTO_DEATHSEQUENCE)
				&&	(acptr->movecode != AUTO_HITWATER)					//RJS 27Aug98
				&&	(acptr->movecode != AUTO_CRASHSKID)					//RJS 27Aug98
				&&	(acptr->movecode != AUTO_CRASHROLL)					//RJS 27Aug98
				&&	(acptr->movecode != AUTO_CRASHONEWHEEL)			  //CSB 18/02/00
				&&	(acptr->movecode != AUTO_CRASHNOSE)				  //CSB 18/02/00
				&&	(acptr->movecode != AUTO_CRASHFLIP)				  //CSB 18/02/00
				&&	(acptr->movecode != AUTO_CRASHTUMBLE)			  //CSB 18/02/00
				&&	(acptr->movecode != AUTO_SPIRAL2GROUND)	)		//DAW 03Sep98
			{
				if (itm == Persons2::PlayerSeenAC)						//RJS 30Oct98
				{
					Squad_Diary.UpdatePlayerLog(EFS_KIA);	//RJS 18Feb00

					controlmode=PILOTDEAD;
//Dead					acptr->Status.deadtime = 1000;//Just to make sure...

					if (_Replay.Record)									//RJS 30Oct98
					{
						UByte	effect = RDEATH_NULL;

						switch (newmovecode)
						{
							case AUTO_HITWATER:
							case AUTO_CRASHSKID:
								effect = RDEATH_SKID;
								break;
							case AUTO_CRASHROLL:
								effect = RDEATH_ROLL;
								break;
							case AUTO_SPIRAL2GROUND:
							case AUTO_DEATHSEQUENCE:
								effect = RDEATH_DIVE;
								break;
						}

		 				_DPlay.NewSpecial(DPlay::PIDC_DEATHMOVEEFFECT,effect);
					}
				}

				acptr->movecode = (AutoMoveCodeTypeSelect) newmovecode;
				wasset = TRUE;										//DAW 03Sep98

				if (!acptr->Status.deadtime)						//RJS 17May99
				{
// Must only come in here once...
					ItemPtr	lasthitter = acptr;
					if (acptr->lasthitter.count)
					{
						lasthitter = (ItemPtr)Persons2::ConvertPtrUID((UniqueID)acptr->lasthitter.count);
						if (!lasthitter)  		//checks to see if it's an airstruc within ScoreSimpleItemKilled
							lasthitter = acptr;
					}

					Squad_Diary.AddKill(lasthitter,acptr);		//RJS 21Feb00

//DeadCode RJS 15Aug00 					if (_DPlay.Implemented)						//RJS 03Jun99
//DeadCode RJS 15Aug00 //DeadCode AMM 16Nov99 						if (_DPlay.GameType<COMMSQUICKMISSION)	//RJS 03Jun99
//DeadCode RJS 15Aug00 							_DPlay.SetScore(acptr,lasthitter);	//RJS 03Jun99
//DeadCode RJS 15Aug00 //DeadCode AMM 16Nov99 						else
//DeadCode RJS 15Aug00 //DeadCode AMM 16Nov99 						{
//DeadCode RJS 15Aug00 //DeadCode AMM 16Nov99 							if (_DPlay.GameType>TEAMPLAY)
//DeadCode RJS 15Aug00 //DeadCode AMM 16Nov99 								_DPlay.NewScoreClaim(lasthitter,acptr->uniqueID.count);
//DeadCode RJS 15Aug00 //DeadCode AMM 16Nov99 						}
//DeadCode RJS 15Aug00 					}
//DeadCode RJS 15Aug00 // want to score all time even in comms
//DeadCode RJS 15Aug00 //DeadCode AMM 5Jul00 					else
//DeadCode RJS 15Aug00 					{
//DeadCode RJS 15Aug00 						if (lasthitter->Status.size == AIRSTRUCSIZE)	//RJS 03Jun99
//DeadCode RJS 15Aug00 							itm->ScoreSimpleItemKilled(true,(AirStrucPtr)lasthitter);//RJS 25May99
//DeadCode RJS 15Aug00 					}

					acptr->SetUnfriendly(NULL);
					acptr->BreakForm();								//RJS 17May99
				}
			}
			else
			{
				//It's ok to say you can't move anymore,
				//but not ok to say you can...
				if (newmovecode == AUTO_NOPPILOT)
					acptr->movecode = (AutoMoveCodeTypeSelect) newmovecode;
			}

			//Make sure it is dead!								
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(acptr->shape);	//RJS 17May99
			acptr->Status.deadtime = sdptr->DeadTime;						//RJS 17May99
			acptr->Status.deadscale = sdptr->DeadScale;						//RJS 17May99
	 		acptr->Status.deaded = TRUE;									//RJS 17May99
			if (acptr == Persons2::PlayerSeenAC)				//RJS 09Jul99
			{
				Persons2::PlayerGhostAC->Status.deadtime = sdptr->DeadTime;
				Persons2::PlayerGhostAC->Status.deadscale = sdptr->DeadScale;
				Persons2::PlayerGhostAC->Status.deaded = TRUE;
				Persons2::PlayerGhostAC->overview_movecode=acptr->overview_movecode;
			}
			
			mad->itemstate = DEAD;								//RJS 23May99

			if (sdptr->AnimDataSize == AIRCRAFTANIM)
			{
				AircraftAnimData* adptr = (AircraftAnimData*)acptr->Anim;//DAW 09Jun99
				adptr->gunshooting = 0;									//RJS 25Aug00
				adptr->cannonshooting = 0;									//RJS 25Aug00
			}

			if(		(acptr->leader) || (acptr->follower) || (acptr->fly.leadflight) || (acptr->fly.nextflight)	//CSB 8Aug00
				||	(acptr->fly.expandedsag) || (acptr->ai.unfriendly) || (acptr->ai.attacker)	)				//CSB 8Aug00
				acptr->BreakForm();																				//CSB 8Aug00

		}
		if (	(acptr->movecode == AUTO_NOPPILOT)							//RJS 22Jun00
			&&	(	!(_Replay.Record || _Replay.Playback || _DPlay.Implemented)
				||	!BoxCol::GetTestState()	))			
			acptr->vel_x = acptr->vel_y = acptr->vel_z = acptr->vel_ = 0;	//RJS 22Jun00
	}

#ifndef NDEBUG															//CSB 14Aug00
	if(itm->Status.size == AIRSTRUCSIZE)								//CSB 14Aug00
		AirStrucPtr(itm)->DoAllSAGChecks();								//CSB 14Aug00
#endif																	//CSB 14Aug00

	AirStrucPtr player = Persons2::PlayerGhostAC;
	if((itm->Status.size == AIRSTRUCSIZE) && (AirStrucPtr(itm)->nationality != player->nationality))
		if(!player->fly.expandedsag)
		{
			bool enemyleft = false;
			for(AirStrucPtr ac = AirStrucPtr(mobileitem.ACList); (ac) && (!enemyleft); ac = AirStrucPtr(ac->nextmobile))
				if((ac->nationality != player->nationality) && (!ac->Status.deadtime))
					if(player->Distance3DSquared(&ac->World) < FP(2 * VISIBLERANGE) * FP(2 * VISIBLERANGE))
						enemyleft = true;

			if(!enemyleft)
				Art_Int.SendMsgAndCall(MESSAGE_STRUC(PHRASE_THINKING, MSG_CLEAR, player, player, player), SetupQuitContinue);
		}

	return(wasset);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FlightModelFixedTime
//Author		R. Hyde 
//Date			Sun 7 Apr 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::FlightModelFixedTime(AirStrucPtr const ControlledAC2)
{
	UWord	loopcount;
	ANGLES	test;

//Old_Code RDH 21Oct96 	groundlevel = Land_Scape.GetGroundLevel(ControlledAC2);
	groundlevel = _Collide.LowestSafeAlt(ControlledAC2,
											ControlledAC2->pitch,
											ControlledAC2->roll);//RDH 21Oct96
//DeadCode RDH 25Nov96 //to allow for small changes in ground level add 2 cm
//DeadCode RDH 25Nov96 	groundlevel +=2;											//RDH 23Nov96

//to allow for small changes in ground level add 2 cm			//RDH 29Nov96
	groundlevel +=2;											//RDH 29Nov96

		ControlledAC2->fly.pModel->Base (ControlledAC2);							//ARM 07Jan97

//DeadCode RDH 07Oct96 	//groundlevel for manual pilot
//DeadCode RDH 07Oct96 	if (ControlledAC2 == ControlledAC)							//RDH 07Oct96
//DeadCode RDH 07Oct96 				 groundlevel_mp = groundlevel;					//RDH 07Oct96

//DeadCode RDH 26Mar98 	loopcount = (UWord) (Timer_Code.FRAMETIME+ cycletimeres);	//DAW 31Jul96

//DeadCode RDH 26Mar98 	cycletimeres = (UWord) (loopcount%FLIGHTMODEL_TIMEFRAME);


//DeadCode RDH 26Mar98 	loopcount = (UWord) (loopcount/FLIGHTMODEL_TIMEFRAME);
//need a test here for dead aircraft +++
//DeadCode RDH 26Mar98 	while (loopcount > 0)
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 	  		SubManualPilot (ControlledAC2);
//DeadCode RDH 26Mar98 			loopcount--;
//DeadCode RDH 26Mar98 		}


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		R. Hyde 
//Date		Wed 30 Aug 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::ACMManualPilot(AirStrucPtr const ControlledAC2)
{
	if (ControlledAC2)
	{
		keyboardcontrol = FALSE;
//DeadCode RDH 31Jul98   		ModifyControlInput (ControlledAC2);		//RDH 31Jul98

// All of the next bit is done in the flight model
//DeadCode CSB 15/09/98			if(!(ControlledAC2->fly.pModel->FrameCount & EVERY256cs))	//This will do the following commands for each aircraft
//DeadCode CSB 15/09/98			{											//once every n operations.
//DeadCode CSB 15/09/98				MMC.Sky.Ambient (ControlledAC2->fly.pModel->Pos.y, 
//DeadCode CSB 15/09/98				 				 ControlledAC2->fly.pModel->AmbDensity,
//DeadCode CSB 15/09/98								 ControlledAC2->fly.pModel->AmbTemp,
//DeadCode CSB 15/09/98								 ControlledAC2->fly.pModel->AmbPres);
//DeadCode CSB 15/09/98				ControlledAC->FuelLeft(CalcFuelRate(ControlledAC));	
//DeadCode CSB 15/09/98			}
//DeadCode CSB 15/09/98			ControlledAC2->fly.pModel->FrameCount++;
//DeadCode CSB 15/09/98		 	ControlledAC2->FuelLeft ();								//RDH 03Jun96

//DeadCode RDH 31Jul98  			ControlledAC2->ai.currentbuffet = 0;				//RDH 14Jun96
//DeadCode RDH 31Jul98  			ControlledAC2->ai.JinkTime = 0;						//RDH 14Jun96
		//Calculating the fuel used will now be done within the flight model	CSB
		FlightModelFixedTime(ControlledAC2);
		ControlledAC2->SetManualFlightParams ();				//DAW 04Jul96
 	}
}

//DeadCode RDH 31Jul98//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RDH 31Jul98//Procedure		ModifyControlInput
//DeadCode RDH 31Jul98//Author		R. Hyde 
//DeadCode RDH 31Jul98//Date			Mon 1 Apr 1996
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//Description	The control input is modified by the velocity.
//DeadCode RDH 31Jul98//				In reality the pilot can feel more "pressure" on the stick
//DeadCode RDH 31Jul98//				at high velocity. At some stage the pilot is not strong enough
//DeadCode RDH 31Jul98//				to pull full deflection on the stick
//DeadCode RDH 31Jul98//				Also at high velocity, smaller stick deflection are required
//DeadCode RDH 31Jul98//				for the same effect
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//				We don't have feedback and so we have introduced this empirical
//DeadCode RDH 31Jul98//				routine.
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//				Similar effects at high g were tried but were not successful
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//Inputs		
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//Returns	
//DeadCode RDH 31Jul98//
//DeadCode RDH 31Jul98//------------------------------------------------------------------------------
//DeadCode RDH 31Jul98void	ManualPilot::ModifyControlInput(AirStrucPtr const ControlledAC)
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98{
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98	SLong	elevator,aileron,rudder;
//DeadCode RDH 31Jul98	SWord	sinroll,cosroll;
//DeadCode RDH 31Jul98//Old_Code PD 24Jun96 	SWord	elevator_pos,elevator_sign,maxelevator_pos;
//DeadCode RDH 31Jul98	SWord	elevator_sign,maxelevator_pos;						//PD 24Jun96
//DeadCode RDH 31Jul98	UWord	elevator_pos;										//PD 24Jun96
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98	AircraftAnimData*	adptr;
//DeadCode RDH 31Jul98	adptr = (AircraftAnimData *)ControlledAC->Anim;
//DeadCode RDH 31Jul98 	ULong	damflagstate;										//RJS 29Oct96
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	ULong	*dflagptr;											//RJS 29Oct96
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	dflagptr = (ULong*) &(adptr->dammageflags);
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = (*dflagptr)>>BF_Pilot;						//RJS 29Oct96
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = damflagstate & BS_DEAD;
//DeadCode RDH 31Jul98	damflagstate = adptr->PILOTLEFT;								//RJS 21Feb97
//DeadCode RDH 31Jul98	if (damflagstate == BS_DEAD)								//RJS 21Feb97
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98//TempCode ARM 09Jan97 			ControlledAC->fly.elevator = 0;
//DeadCode RDH 31Jul98//TempCode ARM 09Jan97 			ControlledAC->fly.aileron = 0;
//DeadCode RDH 31Jul98//TempCode ARM 09Jan97 			ControlledAC->fly.rudder = 0;
//DeadCode RDH 31Jul98	}
//DeadCode RDH 31Jul98//these reductions in control are annoying in game play			//RDH 05Dec96
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 	}elseif ((damflagstate) != BS_ALIVE)
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 	{
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 			if (damflagstate > 2)
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 				damflagstate = 2;
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 			if (!(keyboardcontrol))
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 			{
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 				ControlledAC->fly.elevator = ControlledAC->fly.elevator * ((4- (SWord)damflagstate))/4;
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 				ControlledAC->fly.aileron = ControlledAC->fly.aileron * ((4 - (SWord)damflagstate))/4;
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 				ControlledAC->fly.rudder = ControlledAC->fly.rudder * ((4 - (SWord)damflagstate))/4;
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 			}
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 		
//DeadCode RDH 31Jul98//DeadCode RDH 05Dec96 	}
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = (*dflagptr)>>BF_Engine;
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = damflagstate & BS_DEAD;
//DeadCode RDH 31Jul98	damflagstate = adptr->ENGINELEFTIN;								//RJS 21Feb97
//DeadCode RDH 31Jul98	if (damflagstate == BS_DEAD)								//RJS 21Feb97
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98			ControlledAC->fly.thrustpercent = 0;
//DeadCode RDH 31Jul98	}else
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98		// Scale to 80% max thrust loss....
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98		damflagstate *= 5;										//RJS 21Feb97
//DeadCode RDH 31Jul98		damflagstate >>= 4;										//RJS 21Feb97
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98		if (ControlledAC->fly.thrustpercent > (100 - damflagstate))//RJS 21Feb97
//DeadCode RDH 31Jul98		{
//DeadCode RDH 31Jul98			ControlledAC->fly.thrustpercent = 100 - damflagstate;//RJS 21Feb97
//DeadCode RDH 31Jul98		}
//DeadCode RDH 31Jul98	}
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = (*dflagptr)>>BF_Nose;						//RJS 31Oct96
//DeadCode RDH 31Jul98//DeadCode RJS 21Feb97 	damflagstate = damflagstate & BS_DEAD;
//DeadCode RDH 31Jul98	damflagstate = adptr->PROPLEFTIN;									//RJS 21Feb97
//DeadCode RDH 31Jul98	if (damflagstate == BS_DEAD)								//RJS 21Feb97
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98//TempCode ARM 09Jan97 			ControlledAC->fly.thrustpercent = 0;
//DeadCode RDH 31Jul98	}else
//DeadCode RDH 31Jul98	{
//DeadCode RDH 31Jul98		// Scale to 50% max thrust loss....
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98		damflagstate *= 3;										//RJS 21Feb97
//DeadCode RDH 31Jul98		damflagstate /= 15;										//RJS 21Feb97
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98		if (ControlledAC->fly.thrustpercent > (100 - damflagstate))//RJS 21Feb97
//DeadCode RDH 31Jul98		{
//DeadCode RDH 31Jul98			ControlledAC->fly.thrustpercent = 100 - damflagstate;//RJS 21Feb97
//DeadCode RDH 31Jul98		}
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98	}
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98
//DeadCode RDH 31Jul98}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Author		R. Hyde 
//Date		Wed 30 Aug 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::SubManualPilot(AirStrucPtr const ControlledAC)
{
//DeadCode RDH 26Mar98     	ControlledAC->fly.cposy = -ControlledAC->World.Y;			//RDH 28Feb96
    
//DeadCode RDH 26Mar98     	MachDensity (ControlledAC);
//DeadCode RDH 26Mar98    //TempCode RDH 26Oct95 	classtype->ModelPatch_Thrust ();
//DeadCode RDH 26Mar98     	WW2Thrust(ControlledAC);
//DeadCode RDH 26Mar98     	CalcLift (ControlledAC);
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98 		AircraftAnimData*	adptr;
//DeadCode RDH 26Mar98 		adptr = (AircraftAnimData *)ControlledAC->Anim;
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 		UWord	lcldamflag;
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 		lcldamflag = adptr->dammageflags;
//DeadCode RDH 26Mar98 //DeadCode RJS 21Feb97 		if (((lcldamflag>>BF_Tail) & BS_DEAD) != BS_DEAD)
//DeadCode RDH 26Mar98 		if (adptr->TAIL != BS_DEAD)								//RJS 21Feb97
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 	    	CalcTailLift (ControlledAC);
//DeadCode RDH 26Mar98     		CalcTailDrag (ControlledAC);
//DeadCode RDH 26Mar98 	    	CalcRudderLift (ControlledAC);
//DeadCode RDH 26Mar98 	    	CalcRudderDrag (ControlledAC);
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 
//DeadCode RDH 26Mar98     	CalcSideForce (ControlledAC);
//DeadCode RDH 26Mar98     	CalcDrag (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96    		if (keyboardcontrol)
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96    		{
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96    	 		CalcTrim (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96    		}else
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 		{
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 			trim =0;
//DeadCode RDH 26Mar98 //DeadCode RDH 06Nov96 		}
//DeadCode RDH 26Mar98    		if (keyboardcontrol)
//DeadCode RDH 26Mar98    		{
//DeadCode RDH 26Mar98    	 		CalcTrim (ControlledAC);
//DeadCode RDH 26Mar98    		}else
//DeadCode RDH 26Mar98 		{
//DeadCode RDH 26Mar98 			trim =0;
//DeadCode RDH 26Mar98 		}
//DeadCode RDH 26Mar98 //TempCode ARM 09Jan97     	CalcRotas (ControlledAC);
//DeadCode RDH 26Mar98 //TempCode ARM 07Jan97     	CalcDeltas (ControlledAC);	// does angles
//DeadCode RDH 26Mar98 //TempCode ARM 09Jan97     	CalcVel (ControlledAC);
//DeadCode RDH 26Mar98 //DeadCode DAW 06Jun96 		ControlledAC->fly.acroll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //DeadCode DAW 06Jun96 		ControlledAC->fly.croll = ANGLES_0Deg;
//DeadCode RDH 26Mar98 //TempCode ARM 07Jan97     	VcoAlfaBeta (ControlledAC);	// does velx,y,z
//DeadCode RDH 26Mar98 //TempCode ARM 07Jan97     	DataTrans (ControlledAC);	// vely & roll only
//DeadCode RDH 26Mar98 //TempCode ARM 07Jan97     	CalcPosition (ControlledAC); // does position
//DeadCode RDH 26Mar98    //**  	SetFlags (ControlledAC);

//DeadCode RDH 26Mar98 		ControlledAC->fly.pModel->Base ();							//ARM 07Jan97

//TempCode ARM 27Aug97 		ANGLES a,b;
//TempCode ARM 27Aug97 		ControlledAC->fly.pModel->HaveWeLanded (ControlledAC, a,b);

}



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitManualPilot
//Author		Paul.   
//Date			Thu 2 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::InitManualPilot(AirStrucPtr const ControlledAC)

{

	InitManualPilotSub(ControlledAC);


	//Do this whenever you switch auto/man/auto

	ControlledAC->ai.ManStep = PHASE0;							//RDH 10Sep96
	ControlledAC->ai.manoeuvre = MANOEUVRE_SELECT;				//JIM 05Aug96
	ControlledAC->manoeuvretime = 0;							//JIM 05Aug96
//	ControlledAC->ai.JinkTime = 0;							//JIM 05Aug96

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitManualPilot
//Author		Paul.   
//Date			Thu 2 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::InitManualPilotSub(AirStrucPtr const ControlledAC)

{

		InitSimpleAc(ControlledAC);
///		Save_Data.keysensitivity = 2;											//RDH 12Mar96
		trim =0;													//RDH 15Nov96
		lastmsgtime = 0;

//this does a big initialise									//rdh
		if (ControlledAC2 == ControlledAC)							//ARM 01May97
		{// Player's Aircraft
			ControlledAC->fly.pModel->Initialise (ControlledAC,TRUE);			//ARM 01May97
		}else														//ARM 01May97
		{// ACM Aircraft
			ControlledAC->fly.pModel->Initialise (ControlledAC,FALSE);			//ARM 01May97
		}
}

void ManualPilot::InitSimpleAc(AirStrucPtr const ControlledAC)
{
//	ControlledAC->fly.rpm_lastcycle = ControlledAC->fly.thrustpercent;
//	ControlledAC->fly.rpmtrimtime = 0;
//DeadCode RDH 20Nov96 	ControlledAC->fly.comefrommap = FALSE;
//DEADCODE RDH 13/05/99 	ControlledAC->fly.alreadylanded = FALSE;					//RDH 25Nov96

//the following need to be set on moving to manual
	if (ControlledAC->vel_ > 0)
		ControlledAC->fly.cpitch = ControlledAC->pitch;			//RDH 10Apr96
//DEADCODE JIM 10/12/99 	ControlledAC->fly.i_a_s = ControlledAC->vel_;				//RDH 19Oct96
//DEADCODE JIM 10/12/99 	ControlledAC->fly.vel_cms = 	ControlledAC->vel_ / 100;	//RDH 19Oct96 //CSB 08/11/99
//	ControlledAC->fly.turnrate = ANGLES_0Deg;					//RDH 19Oct96
	ControlledAC->fly.redeffect = 0;							//RJS 13Nov96
	ControlledAC->ai.moraleinc = 0;
	ControlledAC->ai.deltapitchsum = 0;		//rdh
}
void ManualPilot::AutoToggleAircraft(AirStrucPtr const ControlledAC, CONTROLMODE mode)
{
//DeadCode PD 03Mar99 	if  (	((mode) && (controlmode == AUTO))			//rdh 6/4/98
//DeadCode PD 03Mar99 	  ||	((!(mode)) && (controlmode == MANUAL))
//DeadCode PD 03Mar99 		)
	if (mode!=controlmode)
	{
		if (mode==MANUAL)	ControlledAC->fly.pModel->Controlled = TRUE;
		else				ControlledAC->fly.pModel->Controlled = FALSE;
		controlmode=mode;
		InitFlightModelPos(ControlledAC);
		ControlledAC->ai.ManStep = PHASE0;							//RDH 10Sep96
		ControlledAC->ai.manoeuvre = MANOEUVRE_SELECT;				//JIM 05Aug96
		ControlledAC->manoeuvretime = 0;							//JIM 05Aug96
		ControlledAC->information=IF_ALLBAD;							  //JIM 16/04/99
//		ControlledAC->ai.JinkTime = 0;							//JIM 05Aug96
	}
//DEADCODE AMM 19/01/00 	if((ControlledAC == Persons2::PlayerSeenAC) || (ControlledAC == Persons2::PlayerGhostAC))
//DEADCODE AMM 19/01/00 	{
//DEADCODE AMM 19/01/00 		ControlledAC->fly.elevator = 0;
//DEADCODE AMM 19/01/00 		ControlledAC->fly.aileron  = 0;
//DEADCODE AMM 19/01/00 		ControlledAC->fly.rudder   = 0;
//DEADCODE AMM 19/01/00 		ControlledAC->fly.pModel->Elevator = 0;
//DEADCODE AMM 19/01/00 		ControlledAC->fly.pModel->Aileron  = 0;
//DEADCODE AMM 19/01/00 		ControlledAC->fly.pModel->Rudder   = 0;
//DEADCODE AMM 19/01/00 	}
}

void ManualPilot::InitFlightModelPos(AirStrucPtr const ControlledAC)
{
	InitSimpleAc(ControlledAC);
//init aoa for first frame where it may be used before it is set
		
	ControlledAC->fly.elevator = 0;
	ControlledAC->fly.aileron  = 0;
	ControlledAC->fly.rudder   = 0;
	ControlledAC->fly.pModel->Elevator = 0;
	ControlledAC->fly.pModel->Aileron  = 0;
	ControlledAC->fly.pModel->Rudder   = 0;

	PMAINPLANE pMainPlane = ControlledAC->fly.pModel->MainPlaneList;
	while(pMainPlane)
	{
		pMainPlane->aoa[0][0] = 0;
		pMainPlane->aoa[0][1] = 0;
		pMainPlane->aoa[1][0] = 0;
		pMainPlane->aoa[1][1] = 0;
		pMainPlane = pMainPlane->List.NextItem();
	}

	ControlledAC->fly.pModel->InitialiseEngines(ControlledAC);
//DeadCode CSB 10/11/98		ControlledAC->fly.pModel->MainPlaneList->BuffTime[0][0] = 0;
//DeadCode CSB 10/11/98		ControlledAC->fly.pModel->MainPlaneList->BuffTime[0][1] = 0;
//DeadCode CSB 10/11/98		ControlledAC->fly.pModel->MainPlaneList->BuffTime[1][0] = 0;
//DeadCode CSB 10/11/98		ControlledAC->fly.pModel->MainPlaneList->BuffTime[1][1] = 0;
	ControlledAC->fly.pModel->UpdateModel (ControlledAC);
}

UByte	DUMMY;
UByte&	item::AnimByte(Animfieldref)
{
	return(DUMMY=0);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeathSequenceOverrideDiary
//Author		Robert Slater
//Date			Tue 31 Oct 2000
//
//Description	This is a top-level death sequence override function,
//				with diary wrapper...
//				(it must not be embedded deep within damage or other death code)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ManualPilot::DeathSequenceOverrideDiary(ItemPtr	itm, int	newmovecode,bool commscalled)
{
	bool	retval;

	Squad_Diary.SetAC(itm,itm->Anim);

	retval = DeathSequenceOverride(itm,newmovecode,commscalled);
	if (retval && (newmovecode != AUTO_NOPPILOT)	)					//RJS 16Nov00
	{
// we don't want to block out transient dead aircraft if we are still flying!
		AirStrucPtr	ac = AirStrucPtr(itm);
		if (	ac->fly.pModel
			&&	(ac->World.Y > (ac->fly.pModel->GroundHeight + 10000)	)
			&&	(ac->Anim != NULL)	)
		{
			MinAnimData*	mad = (MinAnimData*)ac->Anim;
			mad->itemstate = DYING;
		}
	}

	Squad_Diary.UpdateACDamage();

	return retval;
}







