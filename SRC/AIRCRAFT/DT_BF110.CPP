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

//	--------------------																									
//	Filename		DT_BF110.cpp																							
//	System																									
//	Author		Craig Beeston																							
//	Date		Mon 20 Sep 1999																							
//	Description																									
//	--------------------																									
																										
#include	"dosdefs.h"																									
#include	"worldinc.h"																									
#include	"3DCom.h"																									
#include	"modvec.h"																									
#include	"model.h"																									
#include	"curves.h"

																										
void	BF110_Setup	(	AirStrucPtr	const		ControlledAC	,	ULong		Version	)															
{																										
																										
ClassPtr	data	=	ControlledAC		->	classtype	;																			
PMODEL	pModel	=	ControlledAC		->	fly.pModel	;																			
Model&	Model	=	*ControlledAC		->	fly.pModel	;																			
AircraftAnimData*	adptr	=	(AircraftAnimData* )	ControlledAC	->	Anim	;																			
																										
	Model.Type	=	AT_BF110	;																						
FP	CoG	=	-365	;																						
																										
																										
PMAINPLANE	pMainPlane	=	new	MAINPLANE	(	pModel	,	135375	,	302	,	475	,	56100	,	182	,	330	)	;						
	pMainPlane	->	SetPosition		(	179	,	-9	,	-351	-	CoG	,	596	,	30	,	-368	-	CoG	)	;				
	pMainPlane	->	SetOrientation		(	2.0	,	0	,	5.0	,	2.0	,	0	,	5.0	)	;								
	pMainPlane	->	SetDragPolar		(	0.022	,	0.061718	)	;																
	pMainPlane	->	SetCurves		(	"Bf110"	,	"Cl"	,	"Cd"	,	""	,	""	,	"Cm"	)	;								
																										
	pMainPlane	->	buffetAoa0		=	Degs2Rads	(	10.0	)	;																
	pMainPlane	->	buffetAoa1		=	Degs2Rads	(	17.5	)	;																
	pMainPlane	->	buffetM0		=	1	;																			
	pMainPlane	->	buffetM1		=	1	;																			
	pMainPlane	->	ACMmaxaoa		=	Degs2Rads	(	15.0	)	;																
																										
																										
PSURFACE	pTailPlane1	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_TAILPLANE	,	32200	,	230	)	;												
	pTailPlane1	->	SetPosition		(	107	,	70	,	-1090	-	CoG	)	;												
	pTailPlane1	->	SetOrientation		(	1.0	,	0	,	0	)	;														
	pTailPlane1	->	SetCurves		(	"Bf110"	,	"TailCl"	,	"COMM"	,	"TailCd"	)	;												
																										
PSURFACE	pTailPlane2	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_TAILPLANE	,	32200	,	230	)	;												
	pTailPlane2	->	SetPosition		(	-107	,	70	,	-1090	-	CoG	)	;												
	pTailPlane2	->	SetOrientation		(	1.0	,	0	,	0	)	;														
	pTailPlane2	->	SetCurves		(	"Bf110"	,	"TailCl"	,	"COMM"	,	"TailCd"	)	;												
																										
PSURFACE	pFin1	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_FIN	,	15525	,	135	)	;												
	pFin1	->	SetPosition		(	230	,	66	,	-1092	-	CoG	)	;												
	pFin1	->	SetOrientation		(	0	,	0	,	-90	)	;														
	pFin1	->	SetCurves		(	"Bf110"	,	"FinCl"	,	"COMM"	,	"TailCd"	)	;												
																										
PSURFACE	pFin2	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_FIN	,	15525	,	135	)	;
	pFin2	->	SetPosition		(	-230	,	66	,	-1092	-	CoG	)	;												
	pFin2	->	SetOrientation		(	0	,	0	,	-90	)	;														
	pFin2	->	SetCurves		(	"Bf110"	,	"FinCl"	,	"COMM"	,	"TailCd"	)	;												
																										
																										
PCYLINDER	pCylinder1	=	new	CYLINDER	(	pModel	,	365	,	85	,	120	)	;												
	pCylinder1	->	SetPosition		(	0	,	23	,	-183	-	CoG	)	;												
	pCylinder1	->	SetOrientation		(	0	,	0	,	0	)	;														
																										
PCYLINDER	pCylinder2	=	new	CYLINDER	(	pModel	,	360	,	80	,	133	)	;												
	pCylinder2	->	SetPosition		(	0	,	31	,	-545	-	CoG	)	;												
	pCylinder2	->	SetOrientation		(	0	,	0	,	0	)	;														
																										
PCYLINDER	pCylinder3	=	new	CYLINDER	(	pModel	,	365	,	50	,	83	)	;												
	pCylinder3	->	SetPosition		(	0	,	29	,	-908	-	CoG	)	;												
	pCylinder3	->	SetOrientation		(	0	,	0	,	0	)	;														
																										
																										
new	NEWCTRL		(	pMainPlane	,	&Model.Aileron	,	22.5	,	0.33	,	0.45	)	;												
new	NEWCTRL		(	pTailPlane1	,	&Model.Elevator	,	37.5	,	0.27	,	0.33	)	;												
new	NEWCTRL		(	pTailPlane2	,	&Model.Elevator	,	37.5	,	0.27	,	0.33	)	;												
new	NEWCTRL		(	pFin1		,	&Model.Rudder	,	37.5	,	0.25	,	0.25	)	;												
new	NEWCTRL		(	pFin2		,	&Model.Rudder	,	37.5	,	0.25	,	0.25	)	;												
																										
	pModel	->	SetTrim		(	4096	,	0	,	4096	)	;														
	pModel->SlipstreamRudder = 2500;

	
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_FLAPS, AeroDevice::CT_KEYS, AeroDevice::PT_HYDRAULIC,
				0.2265, 0.03, 0.0, 0.05, 4, 55, FLAPSDOWN, FLAPSUP, 71, &adptr->acflaps,16384, -16384);//RJS 24Mar00
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_GEAR, AeroDevice::CT_KEYS, AeroDevice::PT_HYDRAULIC,
				0, 0.02, -0.01, 0.00, 2, 80, GEARUPDOWN, GEARUPDOWN, 71, &adptr->acleglowerl, 16384, 0);
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_GEAR, AeroDevice::CT_KEYS, AeroDevice::PT_HYDRAULIC,			
				0, 0.02, -0.01, 0.00, 2, 40, NULLKEY, NULLKEY, 71, &adptr->acleglowerr, 16384, 0);
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_CANOPY, AeroDevice::CT_KEYS, AeroDevice::PT_VOID,
				0, 0.02, 0, 0.00, 2, 4096, CANOPYEJECT, NULLKEY, 999, &adptr->accanopy);
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_SLATS, AeroDevice::CT_AUTO, AeroDevice::PT_VOID,
				0.35, 0.035, 0, 0, 2, 328, NULLKEY, NULLKEY, ANGLES_12Deg, &adptr->acslats);
																										
//DeadCode CSB 22Sep00 new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_SLATS, AeroDevice::CT_AUTO, AeroDevice::PT_MANUAL,
//DeadCode CSB 22Sep00 				0.2265, 0.01, 0, -0.05, 2, 328, NULLKEY, NULLKEY, 55, &adptr->acslats);
																										
																										
//DEADCODE CSB 28/01/00 	pModel	->	SetMassInertias		(	ControlledAC	,	26883	,	75112	,	69956	)	;												
//DEADCODE CSB 31/01/00 	pModel	->	SetMassInertias		(	ControlledAC	,	6973	,	94351	,	89379	)	;												
	pModel	->	SetMassInertias		(	ControlledAC	,	57396	,	103055	,	46481	)	;												

																									
PTHRUSTPOINT	pThrust1	=	new	THRUSTPOINT	(	pModel	,	TT_PROP	,	-235	,	0	,	-120	-	CoG	,	0	,	0	)	;				
PTHRUSTPOINT	pThrust2	=	new	THRUSTPOINT	(	pModel	,	TT_PROP	,	235	,	0	,	-120	-	CoG	,	0	,	0	)	;				
																										
																										
PENGINE	pEngine1	=	new	ENGINE	(	pModel	,	ET_PISTON	)	;																
	pEngine1	->	SetEngine		(	1050	,	2100	,	400	,	30000000	)	;												
	pEngine1	->	SetCurves		(	"COMM"	,	"Power0"	,	"COMM"	,	"Power1"	,	"Bf109"	,	"PowerAlt"	)	;								
	pEngine1	->	SetPropeller		(	155	,	12013	,	0.477	,	1	)	;												
	pEngine1	->	SetPropInertia		(	15000000	,	15000000	,	30000000	)	;														
	pEngine1	->	SetPropType		(	PT_VARIABLE	,	35	,	90	)	;														
	pTailPlane1	->	SetSlipstream	(	pThrust1	,	35	)	;																
	pFin1	->	SetSlipstream		(	pThrust1	,	100	)	;																

	pEngine1->Starter = ES_INERTIA;
	pEngine1->MagType = MT_4POSITION;
																										
	pEngine1	->	SetThrustPoint	(	pThrust1	)	;																		
	pThrust1	->	SetEngine		(	pEngine1	)	;																		
																										
PENGINE	pEngine2	=	new	ENGINE	(	pModel	,	ET_PISTON	)	;																
	pEngine2	->	SetEngine		(	1050	,	2100	,	400	,	30000000	)	;												
	pEngine2	->	SetCurves		(	"COMM"	,	"Power0"	,	"COMM"	,	"Power1"	,	"Bf109"	,	"PowerAlt"	)	;								
	pEngine2	->	SetPropeller		(	155	,	12013	,	0.477	,	1	)	;												
	pEngine2	->	SetPropInertia		(	15000000	,	15000000	,	30000000	)	;														
	pEngine2	->	SetPropType		(	PT_VARIABLE	,	35	,	90	)	;														
	pTailPlane2	->	SetSlipstream	(	pThrust2	,	35	)	;																
	pFin2	->	SetSlipstream		(	pThrust2	,	100	)	;																

	pEngine2->Starter = ES_INERTIA;
	pEngine2->MagType = MT_4POSITION;
	
	pEngine2	->	SetThrustPoint	(	pThrust2	)	;																		
	pThrust2	->	SetEngine		(	pEngine2	)	;																		
																										
	pMainPlane	->	SetSlipstream	(	pThrust1	,	pThrust2	,	0	)	;																

	pModel->FuelCockType = FC_2LEVERS;
	pModel->SetFuelCockTanks(0, false, false, false, false);
	pModel->SetFuelCockTanks(1, true,  true,  false, false);
	pModel->SetFuelCockTanks(2, false, false, true,  true );
	pModel->SetFuelCockTanks(3, true,  true,  true,  true );
/////////////////////////																										
	
	Coords3D w,c1,c2;
	FCRD CG;	//Relative to the centre of the shape

	CG.x = Model.ShapeCoG.x;
	CG.y = Model.ShapeCoG.y;
	CG.z = Model.ShapeCoG.z;

	SHAPE.GetContactPoint(ControlledAC, CT_EYE, w, c1, c2);
	Model.PilotEyePos.x = c1.X - CG.x;
	Model.PilotEyePos.y = c1.Y - CG.y;
	Model.PilotEyePos.z = c1.Z - CG.z;

	SHAPE.GetContactPoint(ControlledAC, CT_WHLLEFT, w, c1, c2);
	PGEAR pMainPort = new GEAR (pModel, PORT);
	pMainPort->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
//DEADCODE CSB 08/05/00 	pMainPort->SetDimensions (-240, -220, -315-CoG, -240, -190, -315-CoG);
	pMainPort->SetSuspension (75000, 750000);
	pMainPort->SetTyres (0.05, 0.4, 10000);
	
	SHAPE.GetContactPoint(ControlledAC, CT_WHLRIGHT, w, c1, c2);
	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
//DEADCODE CSB 08/05/00 	pMainStbd->SetDimensions (240, -220, -315-CoG, 240, -190, -315-CoG);
	pMainStbd->SetSuspension (75000, 750000);
	pMainStbd->SetTyres (0.05, 0.4, 10000);

	SHAPE.GetContactPoint(ControlledAC, CT_WHLBACK, w, c1, c2);
	PGEAR pTail = new GEAR (pModel, TAIL);
	pTail->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
//DEADCODE CSB 08/05/00 	pTail->SetDimensions (0, -90, -1115-CoG, 0, -75, -1115-CoG);
	pTail->SetSuspension (15000, 150000);
	pTail->SetTyres (0.05, 0.4, 0);

	pMainPort->SetGearDevice(AeroDevice::DT_GEAR, GEARUPDOWN);
	pMainStbd->SetGearDevice(AeroDevice::DT_GEAR, NULLKEY);
	pTail    ->SetGearDevice(AeroDevice::DT_VOID, NULLKEY);

	
	Model.ControlForce = 100;			// Relative amount of force feedback
	Model.BuffetForce  = 100; 

	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronr);
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.aileron, &adptr->acaileronl,32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.elevator, &adptr->acelevator,32767,-32768);//RJS 14May98
	new MODELANIM (ControlledAC,MA_SURFACE, pModel, &ControlledAC->fly.rudder, &adptr->acrudder);
	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &ControlledAC->fly.rpm, &adptr->acrpm, 0, (255 * 5) / 3);
	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &ControlledAC->fly.rpm1, &adptr->acrpm1, 0, (255 * 5) / 3);	//RJS 21Jun00
	new MODELANIM (ControlledAC,MA_SUSPENSION, pTail, &adptr->aclegsuspb, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);

	Model.PowerBoost = 1.5;

	Model.ContrailDuration = 1.0;

	BF110_SetupAI (ControlledAC, Version);
}


//------------------------------------------------------------------------------
//Author         Craig Beeston
//Date           Wed 27 Nov 1999
//Description    Bf110 AI settings
//------------------------------------------------------------------------------

void BF110_SetupAI (AirStrucPtr const ControlledAC, ULong Version)
{
	ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;

	ACM.pitchmodifier			= 1e5;
	ACM.turnmodifier			= 1e5;
	ACM.aoamodifier				= 1e6;
	ACM.MaxElevatorForTightTurn = 32767;

	ACM.rollmodifier			= 5e4;
	ACM.MaxAileron				= 32767;

	ACM.yawmodifier				= 1e9;
	
//DEADCODE CSB 19/01/00 	ACM.BrakePower = 14;
//DEADCODE CSB 19/01/00 	ACM.SteerRatio = 8e-6;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.MaxAileron = 32767;
//DEADCODE CSB 19/01/00 	ACM.MaxElevatorForTightTurn	= 21300;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.aoamodifier = 1500;//1200;
//DEADCODE CSB 19/01/00 	ACM.DeltaPitchForMaxElevator = 0.5;//	= 1.0472;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.pitchmodifier = 1.0;
//DEADCODE CSB 19/01/00 	ACM.pitchintmodifier = 0;
//DEADCODE CSB 19/01/00 	ACM.IntPitchForMaxElevator	= 0.1;//1000;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.rollmodifier = 1.5;	
//DEADCODE CSB 19/01/00 	ACM.rollintmodifier = 0;
//DEADCODE CSB 19/01/00 	ACM.IntRollForMaxAileron = 100;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.yawmodifier = 5;//6;
//DEADCODE CSB 19/01/00 	ACM.yawintmodifier = 0;//3;	
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.turnmodifier = 1.5;//1.2;
//DEADCODE CSB 19/01/00 	ACM.turnintmodifier = 0.02;//12;
//DEADCODE CSB 19/01/00 	ACM.liftmodifier = 1000;//1200;

	ACM.maxdeltaforclosework = 0.1;
	ACM.lastdeltapitch = 0;

	ACM.deltapitchsum = 0;
	ACM.deltarollsum = 0;
	ACM.deltayawsum = 0;
}


//------------------------------------------------------------------------------
//Author         Craig Beeston
//Date           Wed 22 Sep 1999
//Description    Bf110 Flight Model Curve Data
//------------------------------------------------------------------------------

void LoadCurvesBF110()
{

// ****  Bf110  Cl  **** //

CURVEPNT Bf110_Cl [18] = {
	0.1745	,	0.7660	,
	0.2182	,	0.9203	,
	0.2618	,	1.0000	,
	0.3054	,	0.8000	,
	0.4363	,	0.7000	,
	0.6109	,	0.7000	,
	0.9599	,	0.6000	,
	1.5708	,	0.0000	,
	2.8798	,	0.7660	,
	3.4034	,	-0.7660	,
	4.7124	,	0.0000	,
	5.3233	,	-0.6000	,
	5.6723	,	-0.7000	,
	5.8469	,	-0.7000	,
	5.9778	,	-0.8000	,
	6.0214	,	-1.0000	,
	6.0650	,	-0.9203	,
	6.1087	,	-0.7660	
};				
new CURVE ("Bf110", "Cl", 18, 0.0, 6.2832, 1, Bf110_Cl);


// ****  Bf110  Cd  **** //

CURVEPNT Bf110_Cd [19] = {
	0.1745	,	0.0582	,
	0.2182	,	0.0786	,
	0.2618	,	0.1035	,
	0.3054	,	0.3007	,
	0.6981	,	0.6428	,
	1.0472	,	0.8660	,
	1.5708	,	1.0000	,
	2.0944	,	0.8660	,
	2.9671	,	0.1736	,
	3.1416	,	0.1000	,
	3.3161	,	0.1736	,
	4.1888	,	0.8660	,
	4.7124	,	1.0000	,
	5.2360	,	0.8660	,
	5.5851	,	0.6428	,
	5.9778	,	0.3007	,
	6.0214	,	0.1035	,
	6.0650	,	0.0786	,
	6.1087	,	0.0582	
};
new CURVE ("Bf110", "Cd", 19, 0.0, 6.2832, 1, Bf110_Cd);


// ****  Bf110  Cm  **** //

CURVEPNT Bf110_Cm [12] = {
	0.1745	,	0.00	,
	0.2182	,	-0.01	,
	0.3054	,	-0.09	,
	0.3491	,	-0.10	,
	2.7925	,	-0.10	,
	2.9671	,	0.00	,
	3.3161	,	0.00	,
	3.4907	,	0.10	,
	5.9341	,	0.10	,
	5.9778	,	0.09	,
	6.0650	,	0.01	,
	6.1087	,	0.00	
};
new CURVE ("Bf110", "Cm", 12, 0.0, 6.2832, 1, Bf110_Cm);


// ****  Bf110  TailCl  **** //

CURVEPNT Bf110_TailCl [14] = {
	0.1745	,	0.6039	,
	0.2618	,	0.8289	,
	0.3491	,	0.9000	,
	0.6109	,	0.7000	,
	0.9599	,	0.6000	,
	1.5708	,	0.0000	,
	2.8798	,	0.6039	,
	3.4034	,	-0.6039	,
	4.7124	,	0.0000	,
	5.3233	,	-0.6000	,
	5.6723	,	-0.7000	,
	5.9341	,	-0.9000	,
	6.0214	,	-0.8289	,
	6.1087	,	-0.6039	
};
new CURVE ("Bf110", "TailCl", 14, 0.0, 6.2832, 1, Bf110_TailCl);
	

// ****  Bf110  FinCl  **** //

CURVEPNT Bf110_FinCl [14] = {
	0.1745	,	0.3478	,
	0.2618	,	0.5228	,
	0.3491	,	0.7000	,
	0.6109	,	0.7000	,
	0.9599	,	0.6000	,
	1.5708	,	0.0000	,
	2.8798	,	0.3478	,
	3.4034	,	-0.3478	,
	4.7124	,	0.0000	,
	5.3233	,	-0.6000	,
	5.6723	,	-0.7000	,
	5.9341	,	-0.7000	,
	6.0214	,	-0.5228	,
	6.1087	,	-0.3478	
};
new CURVE ("Bf110", "FinCl", 14, 0.0, 6.2832, 1, Bf110_FinCl);
	



}
// End.

