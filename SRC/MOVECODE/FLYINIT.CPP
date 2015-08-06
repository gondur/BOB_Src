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
//Filename       flyinit.cpp
//System         
//Author         Jim Taylor
//Date           Tue 31 Oct 1995
//Description    Instances of planetypes and dumb planetypes
//------------------------------------------------------------------------------

#define F_GRAFIX												//DAW 05Aug96
#define F_COMMON
#define F_BATTLE
#include "dosdefs.h"
#include "myANGLES.h"
#include "ranges.h"

#include "worldinc.h"											//ARM 29Jan97
#include "modvec.h"												//ARM 29Jan97
#include "model.h"												//ARM 29Jan97

#include "planetyp.h"
#include	"radio.g"											//RJS 10Feb99

#undef	PLANETYP_Included
#include	"planetyp.h"
SLong const ROTATION_CLOCKWISE = 1; 
SLong const ROTATION_ANTICLOCKWISE = -1;



//F86A
/**************************************************************************************************/
/****  SPITFIRE 1  ****  SPITFIRE 1  ****  SPITFIRE 1  ****  SPITFIRE 1  ****  SPITFIRE 1  ********/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_SPITFIRE1) // 29/10/99

	(WeightEmpty)		240000,
	(FuelLoad)			 28900,	

	(FuelTankCap)		16300,
	(FuelTankCap)		12600,
	(FuelTankCap)		0,
	(FuelTankCap)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		SPTSHD,	/*** NOT SET YET ***/			//RJS 14Jan00
	/*(TextRef)*/		PT_SPIT_A,
	/*vis shp*/			SPIT,	SSPIT,	SPIT,					//RJS 12Oct0

	(FuelABoff)			SWord(80 * MAPSCALE),
	(MaxVel)			1640000,
	(MinVel)			500000,

	(CruiseVel)			1450000,
	(BestClimbVel)		900000,
	(Angles)			892,
	(MaxDiveVel)		2100000,			
	(MaxAccel)			8500,//6250,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT1,									//RJS 18Nov99
	/*gunner shapes*/	{{CPT1},								//RJS 11Oct00
	/*gunner shapes*/	{CPT1},								//RJS 11Oct00
	/*gunner shapes*/	{CPT1},								//RJS 11Oct00
	/*gunner shapes*/	{CPT1}},								//RJS 11Oct00
	/*cockpit scale*/	0.19696671,								//RJS 04May00
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_SPITFIRE1A,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_HIGH,
	/*deck*/			ANGLES_11Deg,
						128,
	(MaxRollRate)		ANGLES_180Deg,
	(MaxPitchRate)		ANGLES_35Deg,
	(LandingSpeed)		400000,
	(MaxDiveRpm)		3900,
	(FreeRpm)			500,
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_30000,
	(Abs_Ceiling)		950000,
						0.2618,	//MaxTurnRateAoa @ SL
	(MuzzleVel)			8110000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP1,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_RAF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_RAF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_RAF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_ELECTRIC,				//RJS 08Jun00
	/* number of guns */13,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	144,

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		892	,	//CORRECT
		(BestClimbAng)		1020	,
		(BestClimbAng)		1147	,
		(BestClimbAng)		1275	,
		(BestClimbAng)		1113	,
		(BestClimbAng)		950	,
		(BestClimbAng)		788	,
		(BestClimbAng)		626	,
		(BestClimbAng)		464	,
		(BestClimbAng)		301	,
		(BestClimbAng)		139	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	900000	,	//CORRECT
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	
	},			
				
	{
		(MaxVelSL)			1284000	,	//CORRECT
		(MaxVelSL)			1344000	,
		(MaxVelSL)			1401000	,
		(MaxVelSL)			1462000	,
		(MaxVelSL)			1518000	,
		(MaxVelSL)			1581000	,
		(MaxVelSL)			1635000	,
		(MaxVelSL)			1619000	,
		(MaxVelSL)			1558000	,
		(MaxVelSL)			1460000	,
		(MaxVelSL)			1300000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	
	},
				
	(MaxVelDive_0km)	2100000	,
	(MaxVelDive_11km)	2100000	,
	(MaxVelDive_20km)	2100000	,

	/*version*/		1,
					&SPITFIRE_Setup,											

endinst(PlaneType,Plane_Type_SPITFIRE1);


//F86E
/**************************************************************************************************/
/****  SPITFIRE 2  ****  SPITFIRE 2  ****  SPITFIRE 2  ****  SPITFIRE 2  ****  SPITFIRE 2  ********/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_SPITFIRE2)

	(WeightEmpty)		245500,
	(FuelLoad)			 28900,	

	(FuelTankCap)		16300,
	(FuelTankCap)		12600,
	(FuelTankCap)		0,
	(FuelTankCap)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		SPTSHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_SPIT_B,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			SPIT,SSPIT,	SPIT,						//RJS 12Oct0

	(FuelABoff)			SWord(80 * MAPSCALE),
	(MaxVel)			1580000,
	(MinVel)			500000,

	(CruiseVel)			1420000,
	(BestClimbVel)		900000,
	(Angles)			1657,
	(MaxDiveVel)		2100000,			
	(MaxAccel)			12000,//8250,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT1,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1}},
	/*cockpit scale*/	0.19696671,								//CSB 04May00
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_SPITFIRE1B,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_HIGH,
	/*deck*/			ANGLES_11Deg,
						128,
	(MaxRollRate)		ANGLES_180Deg,
	(MaxPitchRate)		ANGLES_35Deg,
	(LandingSpeed)		400000,
	(MaxDiveRpm)		3900,
	(FreeRpm)			500,
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_30000,
	(Abs_Ceiling)		1000000,
						0.2618,
	(MuzzleVel)			8110000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP1,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_RAF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_RAF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_RAF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_ELECTRIC,				//RJS 08Jun00
	/* number of guns */13,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	144,

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1657	,	//CORRECT
		(BestClimbAng)		1675	,
		(BestClimbAng)		1692	,
		(BestClimbAng)		1709	,
		(BestClimbAng)		1495	,
		(BestClimbAng)		1281	,
		(BestClimbAng)		1066	,
		(BestClimbAng)		852	,
		(BestClimbAng)		637	,
		(BestClimbAng)		423	,
		(BestClimbAng)		209	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	900000	,	//CORRECT
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	
	},			
				
	{
		(MaxVelSL)			1259000	,	//CORRECT
		(MaxVelSL)			1313000	,
		(MaxVelSL)			1370000	,
		(MaxVelSL)			1425000	,
		(MaxVelSL)			1486000	,
		(MaxVelSL)			1536000	,
		(MaxVelSL)			1578000	,
		(MaxVelSL)			1569000	,
		(MaxVelSL)			1520000	,
		(MaxVelSL)			1440000	,
		(MaxVelSL)			1254000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	
	},
				
	(MaxVelDive_0km)	2100000	,
	(MaxVelDive_11km)	2100000	,
	(MaxVelDive_20km)	2100000	,

	/*version*/		2,
					&SPITFIRE_Setup,											

endinst(PlaneType,Plane_Type_SPITFIRE2);


//F86F
/**************************************************************************************************/
/****  DEFIANT  ****  DEFIANT  ****  DEFIANT  ****  DEFIANT  ****  DEFIANT  ****  DEFIANT  ********/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_DEFIANT)

	(WeightEmpty)		323700,
	(FuelLoad)			 53600,	

	(FuelTankCap)		17600,
	(FuelTankCap)		17600,
	(FuelTankCap)		9200,
	(FuelTankCap)		9200,
	(FuelTankXpos)		-210,
	(FuelTankXpos)		310,
	(FuelTankXpos)		-310,
	(FuelTankXpos)		210,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		DEFSHD,									//RJS 15Dec99
	/*(TextRef)*/		PT_DEFIANT,//TEXT_P51,
	/*vis shp*/			DEF,	SDEF,	DEF,					//RJS 12Oct0

	(FuelABoff)			SWord(80 * MAPSCALE),
	(MaxVel)			1360000,
	(MinVel)			500000,

	(CruiseVel)			1220000,
	(BestClimbVel)		900000,
	(Angles)			1185,
	(MaxDiveVel)		2000000,			
	(MaxAccel)			6000,//5000,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT1,									//RJS 15Dec99
	/*gunner shapes*/	{{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1}},
	/*cockpit scale*/	0.25,
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_DEFIANT,							//CSB 04May100

	(AerobaticFactor)	AEROBATIC_MEDIUM,
	/*deck*/			ANGLES_11Deg,
						150,
	(MaxRollRate)		ANGLES_90Deg,
	(MaxPitchRate)		ANGLES_20Deg,
	(LandingSpeed)		350000,
	(MaxDiveRpm)		3900,
	(FreeRpm)			500,
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_25000,
	(Abs_Ceiling)		950000,
						0.2618,
	(MuzzleVel)			8110000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP1,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_RAF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_RAF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_RAF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_ELECTRIC,				//RJS 08Jun00
	/* number of guns */6,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	72,

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1185	,
		(BestClimbAng)		1193	,
		(BestClimbAng)		1207	,
		(BestClimbAng)		1227	,
		(BestClimbAng)		1098	,
		(BestClimbAng)		912	,
		(BestClimbAng)		730	,
		(BestClimbAng)		540	,
		(BestClimbAng)		367	,
		(BestClimbAng)		189	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	
	},			
				
	{
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1160000	,
		(MaxVelSL)			1218000	,
		(MaxVelSL)			1274000	,
		(MaxVelSL)			1322000	,
		(MaxVelSL)			1360000	,
		(MaxVelSL)			1360000	,
		(MaxVelSL)			1333000	,
		(MaxVelSL)			1277000	,
		(MaxVelSL)			1182000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	
	},
				
	(MaxVelDive_0km)	1750000	,
	(MaxVelDive_11km)	1750000	,
	(MaxVelDive_20km)	1750000	,

	/*version*/		1,
					&DUMMY_Setup,											

endinst(PlaneType,Plane_Type_DEFIANT);


//F84E
/**************************************************************************************************/
/****  HURRICANE 1  ****  HURRICANE 1  ****  HURRICANE 1  ****  HURRICANE 1  ****  HURRICANE 1  ***/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_HURRICANE1) // 29/10/99

	(WeightEmpty)		254000,
	(FuelLoad)			 32900,	

	(FuelTankCap)		11700,
	(FuelTankCap)		11700,
	(FuelTankCap)		9500,
	(FuelTankCap)		0,
	(FuelTankXpos)		-105,
	(FuelTankXpos)		105,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		HURSHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_HURR_A,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			HURR,	SHURR,	HURR,					//RJS 12Oct0

	(FuelABoff)			SWord(80 * MAPSCALE),
	(MaxVel)			1520000,
	(MinVel)			500000,

	(CruiseVel)			1300000,
	(BestClimbVel)		850000,
	(Angles)			759,
	(MaxDiveVel)		2000000,
	(MaxAccel)			6500,//5250,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT4,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1}},
	/*cockpit scale*/	0.12505,								//RJS 04May00
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_HURRICANE1A,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_HIGH,
	/*deck*/			ANGLES_9Deg,
						149,
	(MaxRollRate)		ANGLES_180Deg,
	(MaxPitchRate)		ANGLES_30Deg,
	(LandingSpeed)		350000,
	(MaxDiveRpm)		3900,
	(FreeRpm)			500,
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_30000,
	(Abs_Ceiling)		950000,
						0.2618,
	(MuzzleVel)			8110000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP1,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_RAF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_RAF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_RAF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_ELECTRIC,				//RJS 08Jun00
	/* number of guns */13,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	144,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		759	,	//CORRECT
		(BestClimbAng)		867	,
		(BestClimbAng)		975	,
		(BestClimbAng)		1084	,
		(BestClimbAng)		946	,
		(BestClimbAng)		808	,
		(BestClimbAng)		670	,
		(BestClimbAng)		532	,
		(BestClimbAng)		394	,
		(BestClimbAng)		256	,
		(BestClimbAng)		118	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	850000	,	//CORRECT
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000
	},			
				
	{
		(MaxVelSL)			1194120	,
		(MaxVelSL)			1249920	,
		(MaxVelSL)			1302930	,
		(MaxVelSL)			1359660	,
		(MaxVelSL)			1411740	,
		(MaxVelSL)			1470330	,
		(MaxVelSL)			1520550	,
		(MaxVelSL)			1505670	,
		(MaxVelSL)			1448940	,
		(MaxVelSL)			1357800	,
		(MaxVelSL)			1209000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	
	},
				
	(MaxVelDive_0km)	2000000	,
	(MaxVelDive_11km)	2000000	,
	(MaxVelDive_20km)	2000000	,

	/*version*/		1,
					&HURRICANE_Setup,											

endinst(PlaneType,Plane_Type_HURRICANE1);


//F80C
/**************************************************************************************************/
/****  HURRICANE 2  ****  HURRICANE 2  ****  HURRICANE 2  ****  HURRICANE 2  ****  HURRICANE 2  ***/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_HURRICANE2) // 29/10/99

	(WeightEmpty)		259500,
	(FuelLoad)			 32900,	

	(FuelTankCap)		11700,
	(FuelTankCap)		11700,
	(FuelTankCap)		9500,
	(FuelTankCap)		0,
	(FuelTankXpos)		-105,
	(FuelTankXpos)		105,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		HURSHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_HURR_B,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			HURR,	SHURR,	HURR,					//RJS 12Oct0

	(FuelABoff)			SWord(80 * MAPSCALE),
	(MaxVel)			1410000,
	(MinVel)			500000,

	(CruiseVel)			1250000,
	(BestClimbVel)		850000,
	(Angles)			1492,
	(MaxDiveVel)		2000000,
	(MaxAccel)			11000,//7500,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT4,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1}},
	/*cockpit scale*/	0.12505,								//CSB 04May00
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_HURRICANE1B,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_HIGH,
	/*deck*/			ANGLES_9Deg,
						149,
	(MaxRollRate)		ANGLES_180Deg,
	(MaxPitchRate)		ANGLES_30Deg,
	(LandingSpeed)		350000,
	(MaxDiveRpm)		3900,
	(FreeRpm)			500,
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_30000,
	(Abs_Ceiling)		1000000,
						0.2618,
	(MuzzleVel)			8110000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP1,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_RAF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_RAF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_RAF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_ELECTRIC,				//RJS 08Jun00
	/* number of guns */13,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	144,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1492	,	//CORRECT
		(BestClimbAng)		1507	,
		(BestClimbAng)		1523	,
		(BestClimbAng)		1538	,
		(BestClimbAng)		1345	,
		(BestClimbAng)		1153	,
		(BestClimbAng)		960	,
		(BestClimbAng)		767	,
		(BestClimbAng)		574	,
		(BestClimbAng)		381	,
		(BestClimbAng)		188	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	850000	,	//CORRECT
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000	,
		(BestClimbSpeed)	850000
	},			
				
	{
		(MaxVelSL)			1170870	,
		(MaxVelSL)			1221090	,
		(MaxVelSL)			1274100	,
		(MaxVelSL)			1325250	,
		(MaxVelSL)			1381980	,
		(MaxVelSL)			1428480	,
		(MaxVelSL)			1467540	,
		(MaxVelSL)			1459170	,
		(MaxVelSL)			1413600	,
		(MaxVelSL)			1339200	,
		(MaxVelSL)			1166220	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	,
		(MaxVelSL)			950000	
	},
				
	(MaxVelDive_0km)	1900000	,
	(MaxVelDive_11km)	1900000	,
	(MaxVelDive_20km)	1900000	,

	/*version*/		2,
					&HURRICANE_Setup,											

endinst(PlaneType,Plane_Type_HURRICANE2);


//P51D
/**************************************************************************************************/
/****  JU87  ****  JU87  ****  JU87  ****  JU87  ****  JU87  ****  JU87  ****  JU87  ****  JU87  **/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_JU87)

	(WeightEmpty)		339000,
	(FuelLoad)			 35900,	

	(FuelTankCap)		17950,
	(FuelTankCap)		17950,
	(FuelTankCap)		0,
	(FuelTankCap)		0,
	(FuelTankXpos)		-100,
	(FuelTankXpos)		100,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		J87SHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_JU87,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			JU87,	SJU87,	CJU87,					//RJS 12Oct0

	(FuelABoff)			SWord(45 * MAPSCALE),
	(MaxVel)			1050000,
	(MinVel)			450000,

	(CruiseVel)			750000,
	(BestClimbVel)		550000,
	(Angles)			1600,
	(MaxDiveVel)		1500000,			
	(MaxAccel)			7000,//8750,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT3,									//RJS 15Dec99
	/*gunner shapes*/	{{CPT3},
	/*gunner shapes*/	{CPT3},
	/*gunner shapes*/	{CPT3},
	/*gunner shapes*/	{CPT3}},
	/*cockpit scale*/	0.25,
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_JU87,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_MEDIUM,
	/*deck*/			ANGLES_11Deg,
						190,
	(MaxRollRate)		ANGLES_60Deg,
	(MaxPitchRate)		ANGLES_20Deg,
	(LandingSpeed)		300000,
	(MaxDiveRpm)		3500,
	(FreeRpm)			400,
	(MaxRpm)			2400,
	(MinRpm)			400,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_25000,
	(Abs_Ceiling)		825000,
						0.2618,
	(MuzzleVel)			7470000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP3,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_LUF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_LUF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_LUF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_INERTIA,				//RJS 08Jun00
	/* number of guns */3,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	36,

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)	1600	,
		(BestClimbAng)	1400	,
		(BestClimbAng)	1200	,
		(BestClimbAng)	1000	,
		(BestClimbAng)	800	,
		(BestClimbAng)	600	,
		(BestClimbAng)	400	,
		(BestClimbAng)	200	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	,
		(BestClimbAng)	0	
	},			
				
	{			
		(BestClimbSpeed)	650000	,	//CORRECT
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	,
		(BestClimbSpeed)	650000	
	},			
				
	{
		(MaxVelSL)			950000	,	//CORRECT
		(MaxVelSL)			975000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1025000	,
		(MaxVelSL)			1050000	,
		(MaxVelSL)			1025000	,
		(MaxVelSL)			975000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	,
		(MaxVelSL)			750000	
	},
				
	(MaxVelDive_0km)	1750000	,
	(MaxVelDive_11km)	1750000	,
	(MaxVelDive_20km)	1750000	,

	/*version*/		1,
					&JU87B_Setup,											

endinst(PlaneType,Plane_Type_JU87);


//F82
/**************************************************************************************************/
/****  BLENHEIM  ****  BLENHEIM  ****  BLENHEIM  ****  BLENHEIM  ****  BLENHEIM  ****  BLENHEIM  **/  
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_BLENHEIM) // 29/10/99	/*** NOT SET YET ***/	

	(WeightEmpty)		450000,
	(FuelLoad)			100000,	

	(FuelTankCap)		100000,
	(FuelTankCap)		0,
	(FuelTankCap)		0,
	(FuelTankCap)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		BSTSHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_BLEN,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			BRISTO,	SBRSTO,	BRISTO,					//RJS 12Oct0

	(FuelABoff)			SWord(200 * MAPSCALE),
	(MaxVel)			1250000,
	(MinVel)			500000,

	(CruiseVel)			1100000,
	(BestClimbVel)		750000,
	(Angles)			1043,
	(MaxDiveVel)		1750000,			
	(MaxAccel)			7000,//5000,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT1,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1},
	/*gunner shapes*/	{CPT1}},
	/*cockpit scale*/	0.25,
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_DEFIANT,	/*** NOT SET YET ***/

	(AerobaticFactor)	AEROBATIC_LOW,
	/*deck*/			ANGLES_11Deg,
						200,
	(MaxRollRate)		ANGLES_45Deg,
	(MaxPitchRate)		ANGLES_10Deg,
	(LandingSpeed)		400000,
	(MaxDiveRpm)		3900,
	(FreeRpm)			500,
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_25000,
	(Abs_Ceiling)		850000,
						0.2618,
	(MuzzleVel)			8110000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP1,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_LUF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_RAF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_RAF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_INERTIA,				//RJS 08Jun00
	/* number of guns */6,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	120,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1043	,	//CORRECT
		(BestClimbAng)		913	,
		(BestClimbAng)		782	,
		(BestClimbAng)		652	,
		(BestClimbAng)		522	,
		(BestClimbAng)		391	,
		(BestClimbAng)		261	,
		(BestClimbAng)		130	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	750000	,	//CORRECT
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	
	},			
				
	{
		(MaxVelSL)			1050000	,	//CORRECT
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1150000	,
		(MaxVelSL)			1200000	,
		(MaxVelSL)			1250000	,
		(MaxVelSL)			1250000	,
		(MaxVelSL)			1200000	,
		(MaxVelSL)			1125000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	
	},
				
	(MaxVelDive_0km)	1600000	,
	(MaxVelDive_11km)	1600000	,
	(MaxVelDive_20km)	1600000	,

	/*version*/		1,
					&DUMMY_Setup,											

endinst(PlaneType,Plane_Type_BLENHEIM);


//B26
/**************************************************************************************************/
/****  JU88  ****  JU88  ****  JU88  ****  JU88  ****  JU88  ****  JU88  ****  JU88  ****  JU88  **/  
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_JU88) // 29/10/99	/*** NOT SET YET ***/	

	(WeightEmpty)		1000000,
	(FuelLoad)			130000,	

	(FuelTankCap)		50000,
	(FuelTankCap)		50000,
	(FuelTankCap)		30000,
	(FuelTankCap)		30000,
	(FuelTankXpos)		150,
	(FuelTankXpos)		-150,
	(FuelTankXpos)		450,
	(FuelTankXpos)		-450,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		J88SHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_JU88,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			JU88,	SJU88,	JU88,					//RJS 12Oct0

	(FuelABoff)			SWord(58 * MAPSCALE),
	(MaxVel)			1250000,
	(MinVel)			500000,

	(CruiseVel)			1100000,
	(BestClimbVel)		750000,
	(Angles)			1182,
	(MaxDiveVel)		2000000,			
	(MaxAccel)			5000,//5000,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		JUGUNF,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{JUGUNF,ANGLES_0Deg,ANGLES_0Deg},
	/*gunner shapes*/	{JUGUND,ANGLES_180Deg,ANGLES_20Deg},	
	/*gunner shapes*/	{JUGUNV,ANGLES_180Deg,ANGLES_0Deg},		//RJS 29Oct00
	/*gunner shapes*/	{JUGUNF,ANGLES_0Deg,ANGLES_0Deg}},									//AMM 28Feb00
	/*cockpit scale*/	0.125,									//RJS 04May00
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		1684,		//9.25 deg						  //CSB 17/12/99
	/*fin l hdg min*/	32676,		//180 - 0.5 deg					  //CSB 17/12/99
	/*fin l hdg max*/	32858,		//180 - 0.5 deg					  //CSB 17/12/99
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_JU88,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_LOW,
	/*deck*/			ANGLES_13Deg,
						190,
	(MaxRollRate)		ANGLES_30Deg,
	(MaxPitchRate)		ANGLES_10Deg,
	(LandingSpeed)		450000,
	(MaxDiveRpm)		3600,
	(FreeRpm)			400,
	(MaxRpm)			2400,
	(MinRpm)			400,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_25000,
	(Abs_Ceiling)		825000,
						0.2618,
	(MuzzleVel)			7470000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_TURRET,		//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_BOMBER_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_BOMBER_INT,				//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_INERTIA,				//RJS 08Jun00
	/* number of guns */1,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	120,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1182	,	//CORRECT
		(BestClimbAng)		1043	,
		(BestClimbAng)		904	,
		(BestClimbAng)		765	,
		(BestClimbAng)		626	,
		(BestClimbAng)		487	,
		(BestClimbAng)		348	,
		(BestClimbAng)		209	,
		(BestClimbAng)		70	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	750000	,	//CORRECT
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	
	},			
				
	{
		(MaxVelSL)			1100000	,	//CORRECT
		(MaxVelSL)			1150000	,
		(MaxVelSL)			1200000	,
		(MaxVelSL)			1250000	,
		(MaxVelSL)			1290000	,
		(MaxVelSL)			1300000	,
		(MaxVelSL)			1275000	,
		(MaxVelSL)			1225000	,
		(MaxVelSL)			1125000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	
	},
				
	(MaxVelDive_0km)	1750000	,
	(MaxVelDive_11km)	1750000	,
	(MaxVelDive_20km)	1750000	,

	/*version*/		1,
					&DUMMY_Setup,											

endinst(PlaneType,Plane_Type_JU88);


//B29
/**************************************************************************************************/
/****  DO17  ****  DO17  ****  DO17  ****  DO17  ****  DO17  ****  DO17  ****  DO17  ****  DO17  **/  
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_DO17) // 29/10/99	/*** NOT SET YET ***/	

	(WeightEmpty)		550000,
	(FuelLoad)			171500,	

	(FuelTankCap)		52500,
	(FuelTankCap)		52500,
	(FuelTankCap)		66500,
	(FuelTankCap)		0,
	(FuelTankXpos)		175,
	(FuelTankXpos)		-175,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		D17SHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_DO17,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			DO17,	SDO17,	DO17,					//RJS 12Oct0

	(FuelABoff)			SWord(145 * MAPSCALE),
	(MaxVel)			1100000,
	(MinVel)			500000,

	(CruiseVel)			1000000,
	(BestClimbVel)		750000,
	(Angles)			1113,
	(MaxDiveVel)		2000000,			
	(MaxAccel)			7000,//5000,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		DOGUNF,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{DOGUNF,ANGLES_0Deg,ANGLES_0Deg},									//AMM 28Feb00
	/*gunner shapes*/	{DOGUND,ANGLES_180Deg,ANGLES_20Deg},										//RJS 08May00
	/*gunner shapes*/	{DOGUNV,ANGLES_180Deg,ANGLES_0Deg},		//RJS 29Oct00
	/*gunner shapes*/	{DOGUNF,ANGLES_0Deg,ANGLES_0Deg}},									//AMM 28Feb00									//AMM 28Feb00
	/*cockpit scale*/	0.125,
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		1229,		//6.75 deg						  //CSB 17/12/99
	/*fin l hdg min*/	29764,		//180 - 16.5 deg				  //CSB 17/12/99
	/*fin l hdg max*/	30219,		//180 - 14 deg					  //CSB 17/12/99
	/*fin r hdg min*/	35316,
	/*fin r hdg max*/	35771,
	/*phrase name*/		PHRASE_DO17,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_LOW,
	/*deck*/			ANGLES_11Deg,
						200,
	(MaxRollRate)		ANGLES_30Deg,
	(MaxPitchRate)		ANGLES_10Deg,
	(LandingSpeed)		450000,
	(MaxDiveRpm)		3600,
	(FreeRpm)			400,
	(MaxRpm)			2400,
	(MinRpm)			400,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_25000,
	(Abs_Ceiling)		825000,
						0.2618,
	(MuzzleVel)			7470000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_TURRET,		//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_BOMBER_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_BOMBER_INT,				//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_INERTIA,				//RJS 08Jun00
	/* number of guns */1,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	120,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1113	,	//CORRECT
		(BestClimbAng)		973	,
		(BestClimbAng)		834	,
		(BestClimbAng)		695	,
		(BestClimbAng)		556	,
		(BestClimbAng)		417	,
		(BestClimbAng)		278	,
		(BestClimbAng)		139	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	750000	,	//CORRECT
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	,
		(BestClimbSpeed)	750000	
	},			
				
	{
		(MaxVelSL)			1000000	,	//CORRECT
		(MaxVelSL)			1050000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1150000	,
		(MaxVelSL)			1190000	,
		(MaxVelSL)			1200000	,
		(MaxVelSL)			1175000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	,
		(MaxVelSL)			900000	
	},
				
	(MaxVelDive_0km)	1550000	,
	(MaxVelDive_11km)	1550000	,
	(MaxVelDive_20km)	1550000	,

	/*version*/		1,
					&DUMMY_Setup,											

endinst(PlaneType,Plane_Type_DO17);


//T6
/**************************************************************************************************/
/****  HE111  ****  HE111  ****  HE111  ****  HE111  ****  HE111  ****  HE111  ****  HE111  *******/  
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_HE111) // 29/10/99	/*** NOT SET YET ***/	

	(WeightEmpty)		875000,
	(FuelLoad)			254200,	

	(FuelTankCap)		74800,
	(FuelTankCap)		74800,
	(FuelTankCap)		52300,
	(FuelTankCap)		52300,
	(FuelTankXpos)		150,
	(FuelTankXpos)		-150,
	(FuelTankXpos)		425,
	(FuelTankXpos)		-425,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		H11SHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_HE111,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			HE11,	SHE11,	HE11,					//RJS 12Oct0

	(FuelABoff)			SWord(125 * MAPSCALE),	/*** NOT SET YET ***/
	(MaxVel)			1100000,
	(MinVel)			500000,

	(CruiseVel)			950000,
	(BestClimbVel)		700000,
	(Angles)			1113,
	(MaxDiveVel)		2000000,			
	(MaxAccel)			6000,//5000,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		HEGUNF,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{HEGUNF,ANGLES_0Deg,ANGLES_0Deg},									//AMM 28Feb00
	/*gunner shapes*/	{HEGUND,ANGLES_180Deg,ANGLES_20Deg},										//AMM 28Feb00
	/*gunner shapes*/	{HEGUNV,ANGLES_180Deg,ANGLES_0Deg},		//RJS 29Oct00
	/*gunner shapes*/	{HEGUNF,ANGLES_0Deg,ANGLES_0Deg}},									//AMM 28Feb00									//AMM 28Feb00
	/*cockpit scale*/	0.125,									//RJS 04May99
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		1729,		//9.5 deg						  //CSB 17/12/99
	/*fin l hdg min*/	32658,		//180 - 0.6 deg					  //CSB 17/12/99
	/*fin l hdg max*/	32876,										  //CSB 17/12/99
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_HE111,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_LOW,
	/*deck*/			ANGLES_10Deg,
						200,
	(MaxRollRate)		ANGLES_30Deg,
	(MaxPitchRate)		ANGLES_10Deg,
	(LandingSpeed)		450000,
	(MaxDiveRpm)		3600,
	(FreeRpm)			400,
	(MaxRpm)			2400,
	(MinRpm)			400,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_25000,
	(Abs_Ceiling)		825000,
						0.2618,
	(MuzzleVel)			7470000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_TURRET,		//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_BOMBER_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_BOMBER_INT,				//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_INERTIA,				//RJS 08Jun00
	/* number of guns */1,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	120,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1113	,	//CORRECT
		(BestClimbAng)		973	,
		(BestClimbAng)		834	,
		(BestClimbAng)		695	,
		(BestClimbAng)		556	,
		(BestClimbAng)		417	,
		(BestClimbAng)		278	,
		(BestClimbAng)		139	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	700000	,	//CORRECT
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000	,
		(BestClimbSpeed)	700000
	},			
				
	{
		(MaxVelSL)			900000	,	//CORRECT
		(MaxVelSL)			950000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1050000	,
		(MaxVelSL)			1090000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1075000	,
		(MaxVelSL)			975000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	,
		(MaxVelSL)			800000	
	},
				
	(MaxVelDive_0km)	1450000	,
	(MaxVelDive_11km)	1450000	,
	(MaxVelDive_20km)	1450000	,

	/*version*/		1,
					&DUMMY_Setup,											

endinst(PlaneType,Plane_Type_HE111);


//F4U5
/**************************************************************************************************/
/****  HE59  ****  HE59  ****  HE59  ****  HE59  ****  HE59  ****  HE59  ****  HE59  ****  HE59  **/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_HE59) // 29/10/99	/*** NOT SET YET ***/

	(WeightEmpty)		150000,
	(FuelLoad)			 25000,	

	(FuelTankCap)		12500,
	(FuelTankCap)		12500,
	(FuelTankCap)		0,
	(FuelTankCap)		0,
	(FuelTankXpos)		-100,
	(FuelTankXpos)		100,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		SPTSHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_HE59,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			SPIT,	SSPIT,	SPIT,					//RJS 12Oct0

	(FuelABoff)			SWord(100 * MAPSCALE),
	(MaxVel)			1640000,
	(MinVel)			500000,

	(CruiseVel)			1000000,
	(BestClimbVel)		750000,
	(Angles)			1043,
	(MaxDiveVel)		1500000,			
	(MaxAccel)			6000,//5000,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT2,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2}},									//AMM 28Feb00
	/*cockpit scale*/	0.25,
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_SPITFIRE1A,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_LOW,
	/*deck*/			ANGLES_5Deg,
						150,	 /*** NOT SET YET ***/
	(MaxRollRate)		ANGLES_45Deg,
	(MaxPitchRate)		ANGLES_15Deg,
	(LandingSpeed)		350000,
	(MaxDiveRpm)		3900,
	(FreeRpm)			500,
	(MaxRpm)			3000,
	(MinRpm)			500,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_10000,
	(Abs_Ceiling)		350000,
						0.2618,
	(MuzzleVel)			7470000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_TURRET,		//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_LUF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_LUF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_ELECTRIC,				//RJS 08Jun00
	/* number of guns */8,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	120,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1043	,
		(BestClimbAng)		782	,
		(BestClimbAng)		522	,
		(BestClimbAng)		261	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	,
		(BestClimbSpeed)	400000	
	},			
				
	{
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	,
		(MaxVelSL)			600000	
	},
				
	(MaxVelDive_0km)	1000000	,
	(MaxVelDive_11km)	1000000	,
	(MaxVelDive_20km)	1000000	,

	/*version*/		1,
					&DUMMY_Setup,											

endinst(PlaneType,Plane_Type_HE59);


//MiG15
/**************************************************************************************************/
/****  BF109  ****  BF109  ****  BF109  ****  BF109  ****  BF109  ****  BF109  ****  BF109  *******/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_BF109) // 29/10/99

	(WeightEmpty)		236600,
	(FuelLoad)			 29900,	

	(FuelTankCap)		29900,
	(FuelTankCap)		0,
	(FuelTankCap)		0,
	(FuelTankCap)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankXpos)		0,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		M19SHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_ME109,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			ME109,	SME109,	ME109,					//RJS 12Oct0

	(FuelABoff)			SWord(67 * MAPSCALE),
	(MaxVel)			1560000,
	(MinVel)			500000,

	(CruiseVel)			1450000,
	(BestClimbVel)		900000,
	(Angles)			1912,
	(MaxDiveVel)		2000000,			
	(MaxAccel)			9500,//6750,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT2,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2}},									//AMM 28Feb00
	/*cockpit scale*/	0.25,
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_BF109,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_HIGH,
	/*deck*/			ANGLES_14Deg,
						105,	 /*** NOT SET YET ***/
	(MaxRollRate)		ANGLES_135Deg,
	(MaxPitchRate)		ANGLES_30Deg,
	(LandingSpeed)		450000,
	(MaxDiveRpm)		3600,
	(FreeRpm)			400,
	(MaxRpm)			2400,
	(MinRpm)			400,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_35000,
	(Abs_Ceiling)		1100000,
						0.2618,
	(MuzzleVel)			5490000,//7470000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP3,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_LUF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_LUF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_LUF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_INERTIA,				//RJS 08Jun00
	/* number of guns */3,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	120,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1912	,
		(BestClimbAng)		1738	,
		(BestClimbAng)		1565	,
		(BestClimbAng)		1391	,
		(BestClimbAng)		1217	,
		(BestClimbAng)		1043	,
		(BestClimbAng)		869	,
		(BestClimbAng)		695	,
		(BestClimbAng)		522	,
		(BestClimbAng)		348	,
		(BestClimbAng)		174	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	900000	,	//CORRECT
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000
	},			
				
	{
		(MaxVelSL)			1300000	,	//CORRECT
		(MaxVelSL)			1375000	,
		(MaxVelSL)			1440000	,
		(MaxVelSL)			1500000	,
		(MaxVelSL)			1550000	,
		(MaxVelSL)			1550000	,
		(MaxVelSL)			1510000	,
		(MaxVelSL)			1460000	,
		(MaxVelSL)			1400000	,
		(MaxVelSL)			1325000	,
		(MaxVelSL)			1200000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	,
		(MaxVelSL)			1000000	
	},
				
	(MaxVelDive_0km)	2000000	,
	(MaxVelDive_11km)	2000000	,
	(MaxVelDive_20km)	2000000	,

	/*version*/		1,
					&BF109_Setup,											

endinst(PlaneType,Plane_Type_BF109);


//MiG15bis
/**************************************************************************************************/
/****  BF110  ****  BF110  ****  BF110  ****  BF110  ****  BF110  ****  BF110  ****  BF110  *******/
/**************************************************************************************************/
startinst(PlaneType,Plane_Type_BF110) // 29/10/99	/*** NOT SET YET ***/

	(WeightEmpty)		530000,
	(FuelLoad)			 95000,	

	(FuelTankCap)		28000,
	(FuelTankCap)		28000,
	(FuelTankCap)		19500,
	(FuelTankCap)		19500,
	(FuelTankXpos)		-120,
	(FuelTankXpos)		120,
	(FuelTankXpos)		-120,
	(FuelTankXpos)		120,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,
	(FuelTankType)		FT_FIXED,

	/*shad shp*/		M11SHD,	/*** NOT SET YET ***/			//RJS 15Dec99
	/*(TextRef)*/		PT_ME110,//TEXT_P51,	/*** NOT SET YET ***/
	/*vis shp*/			ME110,	SME110,	ME110,					//RJS 12Oct0

	(FuelABoff)			SWord(170 * MAPSCALE),
	(MaxVel)			1640000,
	(MinVel)			500000,

	(CruiseVel)			1450000,
	(BestClimbVel)		900000,
	(Angles)			1275,
	(MaxDiveVel)		2000000,			
	(MaxAccel)			10500,//7750,
	/*truck Turn rate*/	ANGLES_0Deg,METRES00,
	/*pit1 shp*/		CPT5,	/*** NOT SET YET ***/
	/*gunner shapes*/	{{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2},									//AMM 28Feb00
	/*gunner shapes*/	{CPT2}},									//AMM 28Feb00
	/*cockpit scale*/	0.125,									//RJS 04May00
	/*gunner hdg fov*/	ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch max*/ANGLES_45Deg,							//RJS 03Dec99
	/*gunner pitch min*/ANGLES_45Deg,							//RJS 03Dec99
	/*fin pitch*/		0,
	/*fin l hdg min*/	0,
	/*fin l hdg max*/	0,
	/*fin r hdg min*/	0,
	/*fin r hdg max*/	0,
	/*phrase name*/		PHRASE_BF110,						//RJS 14Jan00

	(AerobaticFactor)	AEROBATIC_HIGH,
	/*deck*/			ANGLES_11Deg,
						130,	 /*** NOT SET YET ***/
	(MaxRollRate)		ANGLES_135Deg,
	(MaxPitchRate)		ANGLES_30Deg,
	(LandingSpeed)		450000,
	(MaxDiveRpm)		3500,
	(FreeRpm)			400,
	(MaxRpm)			2400,
	(MinRpm)			400,
	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
	(Damage)			0x2222,	/*** NOT SET YET ***/
	(FightCeiling)		FT_30000,
	(Abs_Ceiling)		1000000,
						0.2618,
	(MuzzleVel)			5490000,//7470000,

	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP3,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,				//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP4,				//RJS 09Jun00
	(FileNum)			INVALIDFILENUM,							//RJS 09Jun00
	(FileNum)			FIL_SFX_MACHINE_GUN_BURST_FRONT_LUF,	//RJS 28Aug00
	(FileNum)			FIL_SFX_ENGINE_LUF_BASS_INT,			//RJS 09Jun00
	(FileNum)			FIL_SFX_ENGINE_LUF_INT,					//RJS 09Jun00
	(FileNum)			FIL_SFX_STARTER_INERTIA,				//RJS 08Jun00
	/* number of guns */6,	/*** NOT SET YET ***/
	/* gun sfx delay */	24,	/*** NOT SET YET ***/
	/* gun FF freq */	120,	/*** NOT SET YET ***/

	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/

	{			
		(BestClimbAng)		1275	,	//CORRECT
		(BestClimbAng)		1275	,
		(BestClimbAng)		1275	,
		(BestClimbAng)		1275	,
		(BestClimbAng)		1217	,
		(BestClimbAng)		1043	,
		(BestClimbAng)		869	,
		(BestClimbAng)		695	,
		(BestClimbAng)		522	,
		(BestClimbAng)		348	,
		(BestClimbAng)		174	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	,
		(BestClimbAng)		0	
	},			
				
	{			
		(BestClimbSpeed)	900000	,	//CORRECT
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000	,
		(BestClimbSpeed)	900000
	},			
				
	{
		(MaxVelSL)			1300000	,
		(MaxVelSL)			1350000	,
		(MaxVelSL)			1400000	,
		(MaxVelSL)			1440000	,
		(MaxVelSL)			1480000	,
		(MaxVelSL)			1510000	,
		(MaxVelSL)			1525000	,
		(MaxVelSL)			1525000	,
		(MaxVelSL)			1470500	,
		(MaxVelSL)			1375000	,
		(MaxVelSL)			1250000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	,
		(MaxVelSL)			1100000	
	},
				
	(MaxVelDive_0km)	2000000	,
	(MaxVelDive_11km)	2000000	,
	(MaxVelDive_20km)	2000000	,

	/*version*/		1,
					&BF110_Setup,											

endinst(PlaneType,Plane_Type_BF110);


//DEADCODE JIM 08/12/99 //YAK9
//DEADCODE JIM 08/12/99 /**************************************************************************************************/
//DEADCODE JIM 08/12/99 /****  DUMMY  ****  DUMMY  ****  DUMMY  ****  DUMMY  ****  DUMMY  ****  DUMMY  ****  DUMMY  *******/
//DEADCODE JIM 08/12/99 /**************************************************************************************************/
//DEADCODE JIM 08/12/99 startinst(PlaneType,Plane_Type_DUMMY) // 29/10/99	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	(WeightEmpty)		240000,
//DEADCODE JIM 08/12/99 	(FuelLoad)			 28900,	
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	(FuelTankCap)		28000,
//DEADCODE JIM 08/12/99 	(FuelTankCap)		28000,
//DEADCODE JIM 08/12/99 	(FuelTankCap)		19500,
//DEADCODE JIM 08/12/99 	(FuelTankCap)		19500,
//DEADCODE JIM 08/12/99 	(FuelTankXpos)		-120,
//DEADCODE JIM 08/12/99 	(FuelTankXpos)		120,
//DEADCODE JIM 08/12/99 	(FuelTankXpos)		-120,
//DEADCODE JIM 08/12/99 	(FuelTankXpos)		120,
//DEADCODE JIM 08/12/99 	(FuelTankType)		FT_FIXED,
//DEADCODE JIM 08/12/99 	(FuelTankType)		FT_FIXED,
//DEADCODE JIM 08/12/99 	(FuelTankType)		FT_FIXED,
//DEADCODE JIM 08/12/99 	(FuelTankType)		FT_FIXED,
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	/*shad shp*/		F51SHD,	/*** NOT SET YET ***/	
//DEADCODE JIM 08/12/99 	/*(TextRef)*/		0,//TEXT_P51,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/*vis shp*/			SPIT,	
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	(FuelABoff)			215,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(MaxVel)			1640,
//DEADCODE JIM 08/12/99 	(MinVel)			500,
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	(CruiseVel)			1450,
//DEADCODE JIM 08/12/99 	(BestClimbVel)		900,
//DEADCODE JIM 08/12/99 	(Angles)			1450,
//DEADCODE JIM 08/12/99 	(MaxDiveVel)		2000,			
//DEADCODE JIM 08/12/99 	(MaxAccel)			10000,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/*pit1 shp*/		CPTF51,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/*pit2 shp*/		CPTF51,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/*msk1 shp*/		SHCKWV,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/*msk2 shp*/		SHCKWV,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/*cockpit scale*/	0.214395,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/*phrase name*/		PHRASE_F51S,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	(AerobaticFactor)	AEROBATIC_HIGH,
//DEADCODE JIM 08/12/99 	(Angles)			ANGLES_12Deg,
//DEADCODE JIM 08/12/99 	(MaxRollRate)		ANGLES_60Deg,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(MaxPitchRate)		ANGLES_15Deg,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(LandingSpeed)		4500,
//DEADCODE JIM 08/12/99 	(MaxDiveRpm)		3900,
//DEADCODE JIM 08/12/99 	(FreeRpm)			500,
//DEADCODE JIM 08/12/99 	(MaxRpm)			3000,
//DEADCODE JIM 08/12/99 	(MinRpm)			500,
//DEADCODE JIM 08/12/99 	(MovableFireZoneType)	-1,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(Damage)			0x2222,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(FightCeiling)		FT_30000,
//DEADCODE JIM 08/12/99 	(Abs_Ceiling)		1036300,
//DEADCODE JIM 08/12/99 						0.2723,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(MuzzleVel)			8110,
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	(FileNum)			FIL_SFX_MACHINE_GUN_LOOP2,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(FileNum)			INVALIDFILENUM,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(FileNum)			FIL_SFX_P51_INT_LOOP,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/* number of guns */8,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/* gun sfx delay */	24,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	/* gun FF freq */	120,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	(InstType)			lightinstrumtypes,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(ACFlags)			HUDINACTIVE,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	{			
//DEADCODE JIM 08/12/99 		(BestClimbAng)	1112	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	1209	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	1296	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	1254	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	1064	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	1030	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	1091	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	1013	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	788	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	550	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	344	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	137	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbAng)	0		/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	},			
//DEADCODE JIM 08/12/99 				
//DEADCODE JIM 08/12/99 	{			
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(BestClimbSpeed)	900		/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	},			
//DEADCODE JIM 08/12/99 				
//DEADCODE JIM 08/12/99 	{
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500	,	/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 		(MaxVelSL)			1500		/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	},
//DEADCODE JIM 08/12/99 				
//DEADCODE JIM 08/12/99 	(MaxVelDive_0km)	2000	,		/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(MaxVelDive_11km)	2000	,		/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 	(MaxVelDive_20km)	2000	,		/*** NOT SET YET ***/
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 	/*version*/		1,
//DEADCODE JIM 08/12/99 					&DUMMY_Setup,											
//DEADCODE JIM 08/12/99 
//DEADCODE JIM 08/12/99 endinst(PlaneType,Plane_Type_DUMMY);


//////////////////////////////////////////////////////////////////////
//
// Function:    WheeledType
// Date:		24/01/00
// Author:		JIM
//
//Description: Troop,Tank,Truck,Train,TransportShip
//
//////////////////////////////////////////////////////////////////////
startinst(WheeledType,ATransportShip)
	(WeightEmpty)		5539,
	(FuelLoad)			130000000,
	(FuelTankCap)		FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,
	(FuelTankXpos)		FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,
	(FuelTankType)		FT_FIXED,FT_FIXED,FT_FIXED,FT_FIXED,
	/*shad shp*/		SHCKWV,
	/*(TextRef)*/		PT_ATransportShip,//TEXT_DAY,
	/*vis shp*/			SHCKWV,	SHCKWV,SHCKWV,							//JIM 28Mar96
	(FuelABoff)			SWord(180 * MAPSCALE),

	/*Max/Min/CrVel*/	VEL_1MPH*15,VEL_1MPH*1,VEL_1MPH*10,
	/*ClimbVel/Pitch*/	VEL_1MPH*15,ANGLES_1Deg,
	/*MaxDiveVel*/		VEL_1MPH*15,
	(MaxAccel)			1000,
	/*Turn rate*/		ANGLES_HalfDeg,METRES600,
endinst(WheeledType,ATransportShip);

startinst(WheeledType,ATrain)
	(WeightEmpty)		5539,
	(FuelLoad)			130000000,
	(FuelTankCap)		FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,
	(FuelTankXpos)		FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,
	(FuelTankType)		FT_FIXED,FT_FIXED,FT_FIXED,FT_FIXED,
	/*shad shp*/		SHCKWV,
	/*(TextRef)*/		PT_ATrain,//TEXT_DAY,
	/*vis shp*/			SHCKWV,	SHCKWV,SHCKWV,					//RJS 12Oct0
	(FuelABoff)			SWord(180 * MAPSCALE),

	/*Max/Min/CrVel*/	VEL_1MPH*90,VEL_1MPH*15,VEL_1MPH*60,
	/*ClimbVel/Pitch*/	VEL_1MPH*30,ANGLES_20Deg,
	/*MaxDiveVel*/		VEL_1MPH*100,
	(MaxAccel)			1000,
	/*Turn rate*/		ANGLES_60Deg,METRES1000,
endinst(WheeledType,ATrain);

startinst(WheeledType,ATruck)
	(WeightEmpty)		5539,
	(FuelLoad)			130000000,
	(FuelTankCap)		FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,
	(FuelTankXpos)		FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,
	(FuelTankType)		FT_FIXED,FT_FIXED,FT_FIXED,FT_FIXED,
	/*shad shp*/		SHCKWV,
	/*(TextRef)*/		PT_ATruck,//TEXT_DAY,
	/*vis shp*/			SHCKWV,	SHCKWV,SHCKWV,					//RJS 12Oct0
	(FuelABoff)			SWord(1000 * MAPSCALE),

	/*Max/Min/CrVel*/	VEL_1MPH*50,VEL_1MPH*5,VEL_1MPH*40,
	/*ClimbVel/Pitch*/	VEL_1MPH*20,ANGLES_45Deg,
	/*MaxDiveVel*/		VEL_1MPH*60,
	(MaxAccel)			1000,
	/*Turn rate*/		ANGLES_60Deg,METRES10,
endinst(WheeledType,ATruck);

startinst(WheeledType,ATank)
	(WeightEmpty)		5539,
	(FuelLoad)			130000000,
	(FuelTankCap)		FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,
	(FuelTankXpos)		FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,
	(FuelTankType)		FT_FIXED,FT_FIXED,FT_FIXED,FT_FIXED,
	/*shad shp*/		SHCKWV,
	/*(TextRef)*/		PT_ATank,//TEXT_DAY,
	/*vis shp*/			SHCKWV,	SHCKWV,SHCKWV,					//RJS 12Oct0
	(FuelABoff)			SWord(1000 * MAPSCALE),

	/*Max/Min/CrVel*/	VEL_1MPH*15,VEL_1MPH*1,VEL_1MPH*7,
	/*ClimbVel/Pitch*/	VEL_1MPH*5,ANGLES_30Deg,
	/*MaxDiveVel*/		VEL_1MPH*15,
	(MaxAccel)			1000,
	/*Turn rate*/		ANGLES_50Deg,METRES10,
endinst(WheeledType,ATank);

startinst(WheeledType,ATroop)
	(WeightEmpty)		5539,
	(FuelLoad)			130000000,
	(FuelTankCap)		FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,FuelTankCapMAX,
	(FuelTankXpos)		FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,FuelTankXposMIN,
	(FuelTankType)		FT_FIXED,FT_FIXED,FT_FIXED,FT_FIXED,
	/*shad shp*/		SHCKWV,
	/*(TextRef)*/		PT_ATroop,//TEXT_DAY,
	/*vis shp*/			SHCKWV,	SHCKWV,SHCKWV,					//RJS 12Oct0
	(FuelABoff)			SWord(180 * MAPSCALE),

	/*Max/Min/CrVel*/	VEL_1MPH*8,VEL_1MPH/3,VEL_1MPH*3,
	/*ClimbVel/Pitch*/	VEL_1MPH,ANGLES_60Deg,
	/*MaxDiveVel*/		VEL_1MPH*10,
	(MaxAccel)			1000,
	/*Turn rate*/		ANGLES_135Deg,METRES01,
endinst(WheeledType,ATroop);



PlaneInit*	Plane_Type_Translate[]	=							//JIM 30Nov99
//PLEASE DO NOT CHANGE THIS TABLE DIRECTLY ANY MORE!!!!!!!		//JIM 30Nov99
			{	&Plane_Type_SPITFIRE1,							//JIM 30Nov99
				&Plane_Type_SPITFIRE2,							//JIM 30Nov99
				&Plane_Type_HURRICANE1,							//JIM 30Nov99
				&Plane_Type_HURRICANE2,							//JIM 30Nov99
																//JIM 30Nov99
				&Plane_Type_DEFIANT,							//JIM 30Nov99
				&Plane_Type_BLENHEIM,							//JIM 30Nov99
																//JIM 30Nov99
				&Plane_Type_BF109,								//JIM 30Nov99
				&Plane_Type_BF110,								//JIM 30Nov99
				&Plane_Type_JU87,								//JIM 30Nov99
																//JIM 30Nov99
				&Plane_Type_DO17,								//JIM 30Nov99
				&Plane_Type_JU88,								//JIM 30Nov99
				&Plane_Type_HE111,								//JIM 30Nov99
				&Plane_Type_HE59,								//JIM 30Nov99
																//JIM 30Nov99
				&ATruck,										//JIM 30Nov99
				&ATank,											//JIM 30Nov99
				&ATroop,
				&ATrain,
				&ATransportShip
			};													//JIM 30Nov99
//DeadCode RJS 14Dec99 			{	&Plane_Type_HURRICANE1,
//DeadCode RJS 14Dec99 				&Plane_Type_HURRICANE2,
//DeadCode RJS 14Dec99 				&Plane_Type_DEFIANT,
//DeadCode RJS 14Dec99 				&Plane_Type_SPITFIRE1,
//DeadCode RJS 14Dec99 				&Plane_Type_SPITFIRE2,
//DeadCode RJS 14Dec99 				&Plane_Type_JU87,
//DeadCode RJS 14Dec99 				&Plane_Type_BLENHEIM,
//DeadCode RJS 14Dec99 				&Plane_Type_JU88,
//DeadCode RJS 14Dec99 				&Plane_Type_DO17,
//DeadCode RJS 14Dec99 				&Plane_Type_HE111,
//DeadCode RJS 14Dec99 				&Plane_Type_HE59,
//DeadCode RJS 14Dec99 				&Plane_Type_BF109,
//DeadCode RJS 14Dec99 				&Plane_Type_BF110,
//DeadCode RJS 14Dec99 				&Plane_Type_DUMMY,
//DeadCode RJS 14Dec99 				&ATruck,
//DeadCode RJS 14Dec99 				&ATank
//DeadCode RJS 14Dec99 			};

