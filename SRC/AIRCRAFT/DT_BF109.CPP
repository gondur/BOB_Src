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
//	Filename		DT_BF109.cpp																							
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

																										
void	BF109_Setup	(	AirStrucPtr	const		ControlledAC	,	ULong		Version	)															
{																										
																										
ClassPtr	data	=	ControlledAC		->	classtype	;																			
PMODEL	pModel	=	ControlledAC		->	fly.pModel	;																			
Model&	Model	=	*ControlledAC		->	fly.pModel	;																			
AircraftAnimData*	adptr	=	(AircraftAnimData* )	ControlledAC	->	Anim	;																			
																										
	Model.Type	=	AT_BF109	;																						
FP	CoG	=	-255	;																						
																										
																										
PMAINPLANE	pMainPlane	=	new	MAINPLANE	(	pModel	,	58125	,	197	,	310	,	22663	,	127	,	185	)	;						
	pMainPlane	->	SetPosition		(	120	,	-34	,	-247	-	CoG	,	386	,	-7	,	-246	-	CoG	)	;				
	pMainPlane	->	SetOrientation		(	2.5	,	0	,	6.0	,	2.5	,	0	,	6.0	)	;								
	pMainPlane	->	SetDragPolar		(	0.02933		,	0.070578	)	;																
	pMainPlane	->	SetCurves		(	"Bf109"	,	"Cl"	,	"Cd"	,	""	,	""	,	"Cm"	)	;								
																										
	pMainPlane	->	buffetAoa0		=	Degs2Rads	(	10.0	)	;																
	pMainPlane	->	buffetAoa1		=	Degs2Rads	(	17.5	)	;																
	pMainPlane	->	buffetM0		=	1	;																			
	pMainPlane	->	buffetM1		=	1	;																			
	pMainPlane	->	ACMmaxaoa		=	Degs2Rads	(	15.0	)	;																
																										
																										
PSURFACE	pTailPlane1	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_TAILPLANE	,	13050	,	145	)	;												
	pTailPlane1	->	SetPosition		(	52	,	75	,	-770	-	CoG	)	;												
	pTailPlane1	->	SetOrientation	(	1.25	,	0	,	0	)	;														
	pTailPlane1	->	SetCurves		(	"Bf109"	,	"TailCl"	,	"COMM"	,	"TailCd"	)	;												
																										
PSURFACE	pTailPlane2	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_TAILPLANE	,	13050	,	145	)	;												
	pTailPlane2	->	SetPosition		(	-52	,	75	,	-770	-	CoG	)	;												
	pTailPlane2	->	SetOrientation	(	1.25	,	0	,	0	)	;														
	pTailPlane2	->	SetCurves		(	"Bf109"	,	"TailCl"	,	"COMM"	,	"TailCd"	)	;												
																									
PSURFACE	pFin	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_FIN	,	15000	,	120	)	;
	pFin	->	SetPosition		(	0	,	66	,	-752	-	CoG	)	;												
	pFin	->	SetOrientation	(	0	,	0	,	-90	)	;														
	pFin	->	SetCurves		(	"Bf109"	,	"FinCl"	,	"COMM"	,	"TailCd"	)	;												
																										
																										
PCYLINDER	pCylinder1	=	new	CYLINDER	(	pModel	,	260	,	85	,	108	)	;												
	pCylinder1	->	SetPosition		(	0	,	4	,	-165	-	CoG	)	;												
	pCylinder1	->	SetOrientation		(	0	,	0	,	0	)	;														
																										
PCYLINDER	pCylinder2	=	new	CYLINDER	(	pModel	,	255	,	75	,	128	)	;												
	pCylinder2	->	SetPosition		(	0	,	21	,	-423	-	CoG	)	;												
	pCylinder2	->	SetOrientation		(	0	,	0	,	0	)	;														
																										
PCYLINDER	pCylinder3	=	new	CYLINDER	(	pModel	,	250	,	40	,	73	)	;												
	pCylinder3	->	SetPosition		(	0	,	31	,	-675	-	CoG	)	;												
	pCylinder3	->	SetOrientation		(	0	,	0	,	0	)	;														
																										
																										
new	NEWCTRL		(	pMainPlane	,	&Model.Aileron	,	25	,	0.33	,	0.45	)	;												
new	NEWCTRL		(	pTailPlane1	,	&Model.Elevator	,	40	,	0.27	,	0.33	)	;												
new	NEWCTRL		(	pTailPlane2	,	&Model.Elevator	,	40	,	0.27	,	0.33	)	;												
new	NEWCTRL		(	pFin		,	&Model.Rudder	,	45	,	0.25	,	0.25	)	;												
																										
	pModel	->	SetTrim		(	4096	,	0	,	0	)	;														
	pModel->SlipstreamRudder = 2200;
																										
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_FLAPS, AeroDevice::CT_KEYS, AeroDevice::PT_MANUAL,
				0.2265, 0.03, -0.25, 0.05, 4, 55, FLAPSDOWN, FLAPSUP, 71, &adptr->acflaps,16384, -16384);//RJS 24Mar00
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_GEAR, AeroDevice::CT_KEYS, AeroDevice::PT_HYDRAULIC,
				0, 0.02 , -0.01, 0.00, 2, 80, GEARUPDOWN, GEARUPDOWN, 71, &adptr->acleglowerl, 16384, 0);
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_GEAR, AeroDevice::CT_KEYS, AeroDevice::PT_HYDRAULIC,
				0, 0.02, -0.01, 0.00, 2, 40, NULLKEY, NULLKEY, 71, &adptr->acleglowerr, 16384, 0);
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_CANOPY, AeroDevice::CT_KEYS, AeroDevice::PT_VOID,
				0, 0.02, 0, 0.00, 2, 4096, CANOPYEJECT, NULLKEY, 999, &adptr->accanopy);
																										
new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_SLATS, AeroDevice::CT_AUTO, AeroDevice::PT_VOID,
				0.35, 0.035, 0, 0, 2, 328, NULLKEY, NULLKEY, ANGLES_12Deg, &adptr->acslats);
																								
//DeadCode CSB 22Sep00 new	AERODEVICE(ControlledAC, pModel, AeroDevice::DT_SLATS, AeroDevice::CT_AUTO, AeroDevice::PT_MANUAL,
//DeadCode CSB 22Sep00 				0.2265, 0.01, 0, -0.05, 2, 328, NULLKEY, NULLKEY, 55, &adptr->acslats);
																										
																										
//DEADCODE CSB 28/01/00 	pModel	->	SetMassInertias		(	ControlledAC	,	6604	,	11943	,	8120	)	;												
	pModel	->	SetMassInertias		(	ControlledAC	,	13537	,	19675	,	7716	)	;												
																										
																										
PTHRUSTPOINT	pThrust	=	new	THRUSTPOINT	(	pModel	,	TT_PROP	,	0	,	0	,	-25	-	CoG	,	0	,	0	)	;				
																										
																										
PENGINE	pEngine	=	new	ENGINE	(	pModel	,	ET_PISTON	)	;																
	pEngine	->	SetEngine		(	1050	,	2100	,	400	,	30000000	)	;												
	pEngine	->	SetCurves		(	"COMM"	,	"Power0"	,	"COMM"	,	"Power1"	,	"Bf109"	,	"PowerAlt"	)	;								
	pEngine	->	SetPropInertia		(	15000000	,	15000000	,	30000000	)	;														
	pEngine	->	SetPropType		(	PT_VARIABLE	,	35	,	90	)	;														
	pEngine	->	SetPropeller		(	155	,	12013	,	0.477	,	1	)	;												
	pMainPlane	->	SetSlipstream		(	pThrust	,	pThrust	,	32	);//50 / 1.5	)	;																
	pTailPlane1	->	SetSlipstream		(	pThrust	,	95	)	;																
	pTailPlane2	->	SetSlipstream		(	pThrust	,	95	)	;																
	pFin	->	SetSlipstream		(	pThrust	,	100	)	;																

	pEngine->Starter = ES_INERTIA;
	pEngine->MagType = MT_4POSITION;
																										
	pEngine	->	SetThrustPoint		(	pThrust	)	;																		
	pThrust	->	SetEngine		(	pEngine	)	;																		
																										
	pModel->FuelCockType = FC_4POSITION;
	pModel->SetFuelCockTanks(0, false, false, false, false);
	pModel->SetFuelCockTanks(1, true,  false, false, false);
	pModel->SetFuelCockTanks(2, false, false, false, false);
	pModel->SetFuelCockTanks(3, false, false, false, false);
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
//DEADCODE CSB 08/05/00 	pMainPort->SetDimensions (-100, -195, -205-CoG, -100, -165, -205-CoG);
	pMainPort->SetSuspension (31500, 315000);
	pMainPort->SetTyres (0.05, 0.4, 7500);
	
	SHAPE.GetContactPoint(ControlledAC, CT_WHLRIGHT, w, c1, c2);
	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
//DEADCODE CSB 08/05/00 	pMainStbd->SetDimensions (100, -195, -205-CoG, 100, -165, -205-CoG);
	pMainStbd->SetSuspension (31500, 315000);
	pMainStbd->SetTyres (0.05, 0.4, 7500);

	SHAPE.GetContactPoint(ControlledAC, CT_WHLBACK, w, c1, c2);
	PGEAR pTail = new GEAR (pModel, TAIL);
	pTail->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
//DEADCODE CSB 08/05/00 	pTail->SetDimensions (0, -30, -765-CoG, 0, -15, -765-CoG);
	pTail->SetSuspension (11500, 115000);
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
//DeadCode RJS 05May99 	new MODELANIM (ControlledAC,MA_GENERICFP, pModel, &pModel->Inst.Rpm1, &adptr->acrpm, 0, 65536);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pTail, &adptr->aclegsuspb, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainPort, &adptr->aclegsuspl, 0, 255);
	new MODELANIM (ControlledAC,MA_SUSPENSION, pMainStbd, &adptr->aclegsuspr, 0, 255);

	Model.PowerBoost = 1.5;
//DeadCode CSB 6Nov00 	Model.MaxG = 5;

	Model.ContrailDuration = 1.0;

	BF109_SetupAI (ControlledAC, Version);
}


//------------------------------------------------------------------------------
//Author         Craig Beeston
//Date           Wed 27 Nov 1999
//Description    Bf109 AI settings
//------------------------------------------------------------------------------

void BF109_SetupAI (AirStrucPtr const ControlledAC, ULong Version)
{
	ACMMODEL& ACM = ControlledAC->fly.pModel->ACMModel;

	ACM.pitchmodifier			= 1e5;
	ACM.turnmodifier			= 4e5;
	ACM.aoamodifier				= 2e6;
	ACM.MaxElevatorForTightTurn = 22500;

	ACM.rollmodifier			= 5e4;
	ACM.MaxAileron				= 32767;

	ACM.yawmodifier				= 1e10;
	
//DEADCODE CSB 19/01/00 	ACM.BrakePower = 14;
//DEADCODE CSB 19/01/00 	ACM.SteerRatio = 8e-6;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.MaxAileron = 32767;
//DEADCODE CSB 19/01/00 	ACM.MaxElevatorForTightTurn	= 16384;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.aoamodifier = 1500;//1200;
//DEADCODE CSB 19/01/00 	ACM.DeltaPitchForMaxElevator = 0.5;//	= 1.0472;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.pitchmodifier = 2.5;
//DEADCODE CSB 19/01/00 	ACM.pitchintmodifier = 0;
//DEADCODE CSB 19/01/00 	ACM.IntPitchForMaxElevator	= 0.1;//1000;
//DEADCODE CSB 19/01/00 
//DEADCODE CSB 19/01/00 	ACM.rollmodifier = 2.0;	
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
//Description    Bf109 Flight Model Curve Data
//------------------------------------------------------------------------------

void LoadCurvesBF109()
{

// ****  Bf109  Cl  **** //

CURVEPNT Bf109_Cl [18] = {				
	0.1745	,	0.7395	,
	0.2182	,	0.8971	,
	0.2618	,	1.0000	,
	0.3054	,	0.9000	,
	0.4363	,	0.7000	,
	0.6109	,	0.7000	,
	0.9599	,	0.6000	,
	1.5708	,	0.0000	,
	2.8798	,	0.7395	,
	3.4034	,	-0.7395	,
	4.7124	,	0.0000	,
	5.3233	,	-0.6000	,
	5.6723	,	-0.7000	,
	5.8469	,	-0.7000	,
	5.9778	,	-0.9000	,
	6.0214	,	-1.0000	,
	6.0650	,	-0.8971	,
	6.1087	,	-0.7395	
};				
new CURVE ("Bf109", "Cl", 18, 0.0, 6.2832, 1, Bf109_Cl);


// ****  Bf109  Cd  **** //

CURVEPNT Bf109_Cd [19] = {
	0.1745	,	0.0679	,
	0.2182	,	0.0897	,
	0.2618	,	0.1162	,
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
	6.0214	,	0.1162	,
	6.0650	,	0.0897	,
	6.1087	,	0.0679	
};
new CURVE ("Bf109", "Cd", 19, 0.0, 6.2832, 1, Bf109_Cd);


// ****  Bf109  Cm  **** //

CURVEPNT Bf109_Cm [12] = {
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
new CURVE ("Bf109", "Cm", 12, 0.0, 6.2832, 1, Bf109_Cm);


// ****  Bf109  TailCl  **** //

CURVEPNT Bf109_TailCl [14] = {
	0.1745	,	0.5494	,
	0.2618	,	0.7494	,
	0.3491	,	0.8000	,
	0.6109	,	0.7000	,
	0.9599	,	0.6000	,
	1.5708	,	0.0000	,
	2.8798	,	0.5494	,
	3.4034	,	-0.5494	,
	4.7124	,	0.0000	,
	5.3233	,	-0.6000	,
	5.6723	,	-0.7000	,
	5.9341	,	-0.8000	,
	6.0214	,	-0.7494	,
	6.1087	,	-0.5494	
};
new CURVE ("Bf109", "TailCl", 14, 0.0, 6.2832, 1, Bf109_TailCl);
	

// ****  Bf109  FinCl  **** //

CURVEPNT Bf109_FinCl [14] = {
	0.1745	,	0.3801	,
	0.2618	,	0.5551	,
	0.3491	,	0.7000	,
	0.6109	,	0.7000	,
	0.9599	,	0.6000	,
	1.5708	,	0.0000	,
	2.8798	,	0.3801	,
	3.4034	,	-0.3801	,
	4.7124	,	0.0000	,
	5.3233	,	-0.6000	,
	5.6723	,	-0.7000	,
	5.9341	,	-0.7000	,
	6.0214	,	-0.5551	,
	6.1087	,	-0.3801	
};
new CURVE ("Bf109", "FinCl", 14, 0.0, 6.2832, 1, Bf109_FinCl);
	

// ****  Bf109  PowerAlt  **** //

CURVEPNT Bf109_PowerAlt[7] = {
	0		,	0.93	,
	3500	,	1.00	,
	4500	,	1.00	,
	7000	,	0.70	,
	9500	,	0.47	,
	12000	,	0.27	,
	20000	,	0.00	
};				
new CURVE ("Bf109", "PowerAlt", 7, 0.0, 20000.0, 2, Bf109_PowerAlt);




}
// End.


