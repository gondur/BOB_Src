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
//	Filename		DT_JU87B.cpp																			
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
	
																						
void	JU87B_Setup	(	AirStrucPtr	const		ControlledAC	,	ULong		Version	)											
{																						
																						
ClassPtr	data	=	ControlledAC		->	classtype	;															
PMODEL	pModel	=	ControlledAC		->	fly.pModel	;															
Model&	Model	=	*ControlledAC		->	fly.pModel	;															
AircraftAnimData*	adptr	=	(AircraftAnimData* )	ControlledAC	->	Anim	;															
																						
	Model.Type	=	AT_JU87B	;																		
FP	CoG	=	-335	;																		
																						
																						
PMAINPLANE	pMainPlane	=	new	MAINPLANE	(	pModel	,	119000	,	293	,	425	,	40950	,	182.3015873	,	260	)	;		
	pMainPlane	->	SetPosition		(	167	,	-42	,	-348	-	CoG	,	503	,	-8	,	-342	-	CoG	)	;
	pMainPlane	->	SetOrientation		(	4.25	,	0	,	5.0	,	4.25	,	0	,	10.0	)	;				
	pMainPlane	->	SetDragPolar		(	0.040856	,	0.061718	)	;												
	pMainPlane	->	SetCurves		(	"JU87B"	,	"Cl"	,	"Cd"	,	""	,	""	,	"Cm"	)	;				
																						
	pMainPlane	->	buffetAoa0		=	Degs2Rads	(	10.0	)	;																
	pMainPlane	->	buffetAoa1		=	Degs2Rads	(	17.5	)	;																
	pMainPlane	->	buffetM0		=	1	;																			
	pMainPlane	->	buffetM1		=	1	;																			
	pMainPlane	->	ACMmaxaoa		=	Degs2Rads	(	15.0	)	;																
																						
																						
PSURFACE	pTailPlane1	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_TAILPLANE	,	25725	,	245	)	;								
	pTailPlane1	->	SetPosition		(	123	,	60	,	-966	-	CoG	)	;								
	pTailPlane1	->	SetOrientation		(	1.0	,	0	,	0	)	;										
	pTailPlane1	->	SetCurves		(	"JU87B"	,	"TailCl"	,	"COMM"	,	"TailCd"	)	;								
																						
PSURFACE	pTailPlane2	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_TAILPLANE	,	25725	,	245	)	;								
	pTailPlane2	->	SetPosition		(	-123	,	60	,	-966	-	CoG	)	;								
	pTailPlane2	->	SetOrientation		(	1.0	,	0	,	0	)	;										
	pTailPlane2	->	SetCurves		(	"JU87B"	,	"TailCl"	,	"COMM"	,	"TailCd"	)	;								
																						
PSURFACE	pFin	=	new	SURFACE	(	pModel	,	ST_PLANE	,	SD_FIN	,	33300	,	185	)	;								
	pFin	->	SetPosition		(	0	,	64	,	-961	-	CoG	)	;								
	pFin	->	SetOrientation		(	0	,	0	,	-90	)	;										
	pFin	->	SetCurves		(	"JU87B"	,	"FinCl"	,	"COMM"	,	"TailCd"	)	;								
																						
																						
PCYLINDER	pCylinder1	=	new	CYLINDER	(	pModel	,	270	,	95	,	118	)	;								
	pCylinder1	->	SetPosition		(	0	,	4	,	-200	-	CoG	)	;								
	pCylinder1	->	SetOrientation		(	0	,	0	,	0	)	;										
																						
PCYLINDER	pCylinder2	=	new	CYLINDER	(	pModel	,	240	,	95	,	165	)	;								
	pCylinder2	->	SetPosition		(	0	,	28	,	-455	-	CoG	)	;								
	pCylinder2	->	SetOrientation		(	0	,	0	,	0	)	;										
																						
PCYLINDER	pCylinder3	=	new	CYLINDER	(	pModel	,	470	,	55	,	85	)	;								
	pCylinder3	->	SetPosition		(	0	,	0	,	-810	-	CoG	)	;								
	pCylinder3	->	SetOrientation		(	0	,	0	,	0	)	;										
																						
																						
new	NEWCTRL		(	pMainPlane	,	&Model.Aileron	,	20	,	0.33	,	0.45	)	;								
new	NEWCTRL		(	pTailPlane1	,	&Model.Elevator	,	25	,	0.40	,	0.50	)	;								
new	NEWCTRL		(	pTailPlane2	,	&Model.Elevator	,	25	,	0.40	,	0.50	)	;								
new	NEWCTRL		(	pFin		,	&Model.Rudder	,	40	,	0.25	,	0.25	)	;								
																						
	pModel	->	SetTrim		(	4096	,	0	,	0	)	;										
	pModel->SlipstreamRudder = 3400;	
	pModel->ControlLossV0 = 175;
	pModel->ControlLossV1 = 200;
	
new	AERODEVICE		(	ControlledAC	,	pModel	,	AeroDevice	::	DT_FLAPS	,	AeroDevice	::	CT_KEYS	,	AeroDevice	::	PT_HYDRAULIC	,			
				0.5	,	0.25	,	-0.25	,	0.1	,	4	,	55	,	FLAPSDOWN	,FLAPSUP	,		63	,	&adptr->acflaps,16384, -16384);//RJS 24Mar00
																						
new	AERODEVICE		(	ControlledAC	,	pModel	,	AeroDevice	::	DT_CANOPY	,	AeroDevice	::	CT_KEYS	,	AeroDevice	::	PT_MANUAL	,			
				0	,	0.02	,	0	,	0.00	,	2	,	120	,	CANOPYEJECT	,	CANOPYEJECT	,	999	,	&adptr->accanopy	)	;
																						
new	AERODEVICE		(	ControlledAC	,	pModel	,	AeroDevice	::	DT_DIVEBRAKES	,	AeroDevice	::	CT_KEYS	,	AeroDevice	::	PT_HYDRAULIC	,			
				-0.1	,	0.015	,	0.075	,	0.00	,	2	,	164	,	SPEEDBRAKE	,	SPEEDBRAKE	,	250	,	&adptr->acbreak	)	;
																						
																						
//DEADCODE CSB 28/01/00 	pModel	->	SetMassInertias		(	ControlledAC	,	13961	,	27747	,	20568	)	;								
	pModel	->	SetMassInertias		(	ControlledAC	,	30953	,	51023	,	21874	)	;								
																						
																						
PTHRUSTPOINT	pThrust	=	new	THRUSTPOINT	(	pModel	,	TT_PROP	,	0	,	0	,	-45	-	CoG	,	0	,	0	)	;
																						
																						
PENGINE	pEngine	=	new	ENGINE	(	pModel	,	ET_PISTON	)	;												
	pEngine	->	SetEngine		(	1140	,	2100	,	400	,	30000000	)	;								
	pEngine	->	SetCurves		(	"COMM"	,	"Power0"	,	"COMM"	,	"Power1"	,	"JU87B"	,	"PowerAlt"	)	;				
	pEngine	->	SetPropeller		(	165	,	13613	,	0.477	,	1	)	;								
	pEngine	->	SetPropInertia		(	15000000	,	15000000	,	30000000	)	;										
	pEngine	->	SetPropType		(	PT_2PITCH	,	40	,	50	)	;										
	pMainPlane	->	SetSlipstream		(	pThrust	,	pThrust	,	0	);//35 / 2	)	;
	pTailPlane1	->	SetSlipstream		(	pThrust	,	45	)	;												
	pTailPlane2	->	SetSlipstream		(	pThrust	,	45	)	;												
	pFin	->	SetSlipstream		(	pThrust	,	95	)	;												

	pEngine->Starter = ES_INERTIA;
	pEngine->MagType = MT_2SWITCHES;
	
	pEngine	->	SetThrustPoint		(	pThrust	)	;														
	pThrust	->	SetEngine		(	pEngine	)	;														
																						
	pModel->FuelCockType = FC_2LEVERS;
	pModel->SetFuelCockTanks(0, false, false, false, false);
	pModel->SetFuelCockTanks(1, true,  false, false, false);
	pModel->SetFuelCockTanks(2, false, true,  false, false);
	pModel->SetFuelCockTanks(3, true,  true,  false, false);
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
//DeadCode CSB 27Jun00 	pMainPort->SetDimensions (-150, -250, -275-CoG, -150, -230, -275-CoG);
	pMainPort->SetSuspension (45000, 450000);
	pMainPort->SetTyres (0.05, 0.4, 5000);
	
	SHAPE.GetContactPoint(ControlledAC, CT_WHLRIGHT, w, c1, c2);
	PGEAR pMainStbd = new GEAR (pModel, STBD);
	pMainStbd->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
//DeadCode CSB 27Jun00 	pMainStbd->SetDimensions (150, -250, -275-CoG, 150, -230, -275-CoG);
	pMainStbd->SetSuspension (45000, 450000);
	pMainStbd->SetTyres (0.05, 0.4, 5000);

	SHAPE.GetContactPoint(ControlledAC, CT_WHLBACK, w, c1, c2);
	PGEAR pTail = new GEAR (pModel, TAIL);
	pTail->SetDimensions (c1.X - CG.x, c1.Y - CG.y, c1.Z - CG.z, c2.X - CG.x, c2.Y - CG.y, c2.Z - CG.z);
//DeadCode CSB 27Jun00 	pTail->SetDimensions (0, -90, -1025-CoG, 0, -75, -1025-CoG);
	pTail->SetSuspension (12500, 125000);
	pTail->SetTyres (0.05, 0.4, 0);

	pMainPort->SetGearDevice(AeroDevice::DT_VOID, NULLKEY);
	pMainStbd->SetGearDevice(AeroDevice::DT_VOID, NULLKEY);
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

	Model.ContrailDuration = 1.0;

//DeadCode CSB 27/10/99		F51D_SetupAI (ControlledAC, Version);
}


//------------------------------------------------------------------------------
//Author         Craig Beeston
//Date           Wed 22 Sep 1999
//Description    Stuka Flight Model Curve Data
//------------------------------------------------------------------------------

void LoadCurvesJU87()
{
// ****  JU87B  Cl  **** //

CURVEPNT JU87B_Cl [18] = {				
	0.1745	,	0.7297	,
	0.2182	,	0.8885	,
	0.2618	,	1.0000	,
	0.3054	,	0.8000	,
	0.4363	,	0.7000	,
	0.6109	,	0.7000	,
	0.9599	,	0.6000	,
	1.5708	,	0.0000	,
	2.8798	,	0.7297	,
	3.4034	,	-0.7297	,
	4.7124	,	0.0000	,
	5.3233	,	-0.6000	,
	5.6723	,	-0.7000	,
	5.8469	,	-0.7000	,
	5.9778	,	-0.8000	,
	6.0214	,	-1.0000	,
	6.0650	,	-0.8885	,
	6.1087	,	-0.7297	
};				
new CURVE ("JU87B", "Cl", 18, 0.0, 6.2832, 1, JU87B_Cl);


// ****  JU87B  Cd  **** //

CURVEPNT JU87B_Cd [19] = {
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
new CURVE ("JU87B", "Cd", 19, 0.0, 6.2832, 1, JU87B_Cd);


// ****  JU87B  Cm  **** //

CURVEPNT JU87B_Cm [12] = {
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
new CURVE ("JU87B", "Cm", 12, 0.0, 6.2832, 1, JU87B_Cm);


// ****  JU87B  TailCl  **** //

CURVEPNT JU87B_TailCl [14] = {
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
new CURVE ("JU87B", "TailCl", 14, 0.0, 6.2832, 1, JU87B_TailCl);
	

// ****  JU87B  FinCl  **** //

CURVEPNT JU87B_FinCl [14] = {
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
new CURVE ("JU87B", "FinCl", 14, 0.0, 6.2832, 1, JU87B_FinCl);
	

// ****  JU87B  PowerAlt  **** //

CURVEPNT JU87B_PowerAlt[6] = {
	0	,	0.95	,
	1500	,	1.00	,
	2500	,	0.88	,
	4000	,	0.93	,
	11200	,	0.00	,
	20000	,	0.00	
};				
new CURVE ("JU87B", "PowerAlt", 6, 0.0, 20000.0, 2, JU87B_PowerAlt);
}
// End.
