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

//------------------------------------------------------------------------------	//CSB 19/04/00
//Filename       keyfly.cpp
//System         
//Author         R. Hyde && A. McRae from Jan 97
//Date           Mon 30 Oct 1995
//Description    
//------------------------------------------------------------------------------
#define F_GRAFIX												//DAW 05Aug96
#define F_COMMON
#define F_BATTLE
#include	"dosdefs.h"
#include	"worldinc.h"
#include	"planetyp.h"
#include	"flymodel.h"
#include	"keytest.h"
#include	"mymath.h"											//RDH 30Nov95
#include	"analogue.h"										//RDH 17Apr96
#include	"missman2.h"											//RDH 17Jul96
#include	"miles.h"											//RDH 17Jul96
#include	"ranges.h"											//RDH 17Jul96
#include	"winmove.h"											//ARM 29Nov96
#include	"modvec.h"											//ARM 05Feb97
#include	"model.h"											//ARM 05Feb97
#include	"savegame.h"
#include	"replay.h"
#include	"overlay.h"
#include	"intcock.h"											//RJS 14Dec99
#include	"comms.h"

extern DPlay _DPlay;
//DeadCode JIM 29Oct96 #pragma	dump_object_model	AirStruc

//DeadCode JIM 29Oct96 #pragma	dump_object_model PolyPitAnimData

//	1	devices not coded
//
//
//
//
//
//
//
//
//
	enum	{													//JIM 03Apr96
		 	MAXKEY_COUNT 	=	1,//4,	//CSB 29/01/99
		 	MINSENSITIVITY	=	1,//0,	//CSB 29/01/99
		 	MAXSENSITIVITY	=	4,//3,	//CSB 29/01/99
//DeadCode RDH 19Dec95 ULong const 	MAXRUDDER 		=	64;							//RDH 19Dec95
		 	RUDDER_STEP 		=	5 * RUDDERFACTOR,
		 	NEGATIVE		=	0,
		 	ABRPM	=	2000,
		 	MINRPM	=	1000,
			};

SLong	const BIGTHRUSTSTEP =10;
SLong	const SMALLTHRUSTSTEP =1;


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetKeyCommon
//Author		R. Hyde 
//Date			Tue 31 Oct 1995
//
//Description	f
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::GetKeyCommon(AirStrucPtr const ControlledAC)
{
	PMODEL pModel = ControlledAC->fly.pModel;

//#define PRINT_STICK_RUDDER
#ifdef PRINT_STICK_RUDDER
SWord temp;
temp = 39 + ControlledAC->fly.aileron / 1000;
PrintString(temp, 0, "      ");
temp = 39 + ControlledAC->fly.rudder / 1000;
PrintString(temp, 23, "      ");
temp = 12 + ControlledAC->fly.elevator / 2700;
PrintString(66, temp, "      ");

temp = 39 + pModel->Aileron / 1000;
PrintString(temp, 1, "      ");
temp = 39 + pModel->Rudder / 1000;
PrintString(temp, 24, "      ");
temp = 12 + pModel->Elevator / 2700;
PrintString(73, temp, "      ");
#endif

	GetStickKeys (ControlledAC2);							//RDH 04Mar96

//Set control values in Model including Central deadzone and end clipping

//#define PRINT_INPUT_DATA
#ifdef PRINT_INPUT_DATA
PrintVar(40, 15, "Raw Elev %.0f  ", (FP)ControlledAC->fly.elevator);
PrintVar(40, 16, "Raw Ailn %.0f  ", (FP)ControlledAC->fly.aileron);
PrintVar(40, 17, "Raw Rudd %.0f  ", (FP)ControlledAC->fly.rudder);
#endif

	if(_Analogue.tune[AU_ELEVATOR].mode == AM_REALISTIC)	
		ApplyDeadZone (ControlledAC, ControlledAC->fly.elevator, pModel->Elevator, _Analogue.tune[AU_ELEVATOR].deadzones);
	else
		ApplyDeadZone2(ControlledAC, ControlledAC->fly.elevator, pModel->Elevator, _Analogue.tune[AU_ELEVATOR].deadzones);

	if(_Analogue.tune[AU_AILERON].mode == AM_REALISTIC)	
		ApplyDeadZone (ControlledAC, ControlledAC->fly.aileron,  pModel->Aileron,  _Analogue.tune[AU_AILERON].deadzones);
	else
		ApplyDeadZone2(ControlledAC, ControlledAC->fly.aileron,  pModel->Aileron,  _Analogue.tune[AU_AILERON].deadzones);

	if(_Analogue.tune[AU_RUDDER].mode == AM_REALISTIC)	
		ApplyDeadZone (ControlledAC, ControlledAC->fly.rudder,   pModel->Rudder,   _Analogue.tune[AU_RUDDER].deadzones);
	else
		ApplyDeadZone2(ControlledAC, ControlledAC->fly.rudder,   pModel->Rudder,   _Analogue.tune[AU_RUDDER].deadzones);

	FP temp = 1.0 - pModel->Speed / pModel->ControlLossV1;
	if(temp < 0.0)	temp = 0.0;
	ControlledAC->fly.rudder = temp * ControlledAC->fly.rudder;
	pModel->Rudder = temp * pModel->Rudder;

	SecondaryControls (ControlledAC2);
	
	if(Save_Data.flightdifficulty[FD_SPINS])
	{
		if(pModel->BombingPhase == 1)
			pModel->ElevatorTrim = 8192;

		if(pModel->BombingPhase == 2)
		{
			pModel->ElevatorTrim = 0;

			if(pModel->Elevator < -30000)
				pModel->Elevator = pModel->Elevator + 30000;
			else
				pModel->Elevator = 0;
		}

		pModel->Elevator += pModel->ElevatorTrim;
		pModel->Aileron  += pModel->AileronTrim;
		pModel->Rudder   += pModel->RudderTrim;

		if(Save_Data.flightdifficulty [FD_SLIPSTREAMEFFECTS])
			pModel->Rudder += pModel->SlipstreamRudder;
	}

	MODLIMIT(pModel->Elevator, 32767);
	MODLIMIT(pModel->Aileron,  32767);
	MODLIMIT(pModel->Rudder,   32767);

#ifdef PRINT_INPUT_DATA
PrintVar(60, 15, "Mod Elev %.0f  ", (FP)pModel->Elevator);
PrintVar(60, 16, "Mod Ailn %.0f  ", (FP)pModel->Aileron);
PrintVar(60, 17, "Mod Rudd %.0f  ", (FP)pModel->Rudder);
#endif

#ifdef PRINT_STICK_RUDDER
temp = 39 + ControlledAC->fly.aileron / 1000;
PrintVar(temp, 0, "%.0f", FP(ControlledAC->fly.aileron));
temp = 39 + ControlledAC->fly.rudder / 1000;
PrintVar(temp, 23, "%.0f", FP(ControlledAC->fly.rudder));
temp = 12 + ControlledAC->fly.elevator / 2700;
PrintVar(66, temp, "%.0f", FP(ControlledAC->fly.elevator));

temp = 39 + pModel->Aileron / 1000;
PrintVar(temp, 1, "%.0f", FP(pModel->Aileron));
temp = 39 + pModel->Rudder / 1000;
PrintVar(temp, 24, "%.0f", FP(pModel->Rudder));
temp = 12 + pModel->Elevator / 2700;
PrintVar(73, temp, "%.0f", FP(pModel->Elevator));
#endif

	bool ThrottleSettingChanged = FALSE;
	bool PropSettingChanged = FALSE;

	PENGINE pEngine0 = pModel->EngineList;
	PENGINE pEngine1 = pModel->EngineList->List.NextItem();

	if(pEngine0)
	{
		if(Key_Tests.KeyPress3d(FK_THROTTLE0))
		{
			SLong	tmpacthrust = pEngine0->ThrottleSetting;
			SLong	delta = _Interactive.GetDelta(INST_THROTTLE, tmpacthrust);

			tmpacthrust += (delta*100)>>7;
			MODMAXMIN(tmpacthrust,0,100);

			pEngine0->ThrottleSetting		= tmpacthrust;
			pModel->ModelThrottle			= tmpacthrust;
			ControlledAC->fly.thrustpercent = tmpacthrust;
		}
		if(Key_Tests.KeyPress3d(FK_PROPPITCH0))
		{
			SLong	tmpacprop = 100.0 * pEngine0->PropSetting;
			SLong	delta = _Interactive.GetDelta(INST_PROPPITCH, tmpacprop);

			tmpacprop += (delta*100)>>7;
			MODMAXMIN(tmpacprop,0,100);

			pEngine0->PropSetting			= 0.01 * tmpacprop;
			pModel->ModelPropSetting		= tmpacprop;
			ControlledAC->fly.propsetting	= tmpacprop;
		}
	}

	if(pEngine1)
	{
		if(Key_Tests.KeyPress3d(FK_THROTTLE1))
		{
			SLong	tmpacthrust = pEngine1->ThrottleSetting;
			SLong	delta = _Interactive.GetDelta(INST_THROTTLE1, tmpacthrust);

			tmpacthrust += (delta*100)>>7;
			MODMAXMIN(tmpacthrust,0,100);

			pEngine1->ThrottleSetting		= tmpacthrust;
			pModel->ModelThrottle			= tmpacthrust;
			ControlledAC->fly.thrustpercent = tmpacthrust;
		}
		if(Key_Tests.KeyPress3d(FK_PROPPITCH1))
		{
			SLong	tmpacprop = 100.0 * pEngine1->PropSetting;
			SLong	delta = _Interactive.GetDelta(INST_PROPPITCH1, tmpacprop);

			tmpacprop += (delta*100)>>7;
			MODMAXMIN(tmpacprop,0,100);

			pEngine1->PropSetting			= 0.01 * tmpacprop;
			pModel->ModelPropSetting		= tmpacprop;
			ControlledAC->fly.propsetting	= tmpacprop;
		}
	}

	SWord DeltaThrustpercent = ControlledAC->fly.thrustpercent - pModel->ModelThrottle;
	if((DeltaThrustpercent > 1) || (DeltaThrustpercent < -1)) 
	{
		ThrottleSettingChanged = TRUE;
		pModel->ModelThrottle = ControlledAC->fly.thrustpercent;
	}

	FP DeltaPropSetting = ControlledAC->fly.propsetting - pModel->ModelPropSetting;
	if((DeltaPropSetting >= 1) || (DeltaPropSetting < -1)) 
	{
		PropSettingChanged = TRUE;
		pModel->ModelPropSetting = ControlledAC->fly.propsetting;
	}


	if((Save_Data.flightdifficulty[FD_SPINS]) &&(!pModel->BoostCutout))
	{
		const int MAXSAFETHROTTLE = 90;
		if(ControlledAC->fly.thrustpercent > MAXSAFETHROTTLE)	ControlledAC->fly.thrustpercent = MAXSAFETHROTTLE;
		if(pModel->ModelThrottle > MAXSAFETHROTTLE)				pModel->ModelThrottle = MAXSAFETHROTTLE;
		for(PENGINE pEngine = pModel->EngineList; pEngine; pEngine = pEngine->List.NextItem() )
			if(pEngine->ThrottleSetting > MAXSAFETHROTTLE)		pEngine->ThrottleSetting = MAXSAFETHROTTLE;
	}


	for(PENGINE pEngine = pModel->EngineList; pEngine; pEngine = pEngine->List.NextItem() )
		if(		((pModel->EngineSelected == ES_PORT) && (pEngine->pThrustPoint->Pos.x > 0))
			||	((pModel->EngineSelected == ES_STBD) && (pEngine->pThrustPoint->Pos.x < 0)) )
		{
			if(pEngine->ThrottleSetting < 0)
				pEngine->ThrottleSetting += 101;
			if(pEngine->PropSetting < 0)
				pEngine->PropSetting += 101;
		}
		else
		{
			if(pEngine->ThrottleSetting < 0)
				pEngine->ThrottleSetting += 101;
			else
				if(ThrottleSettingChanged)	
					pEngine->ThrottleSetting = pModel->ModelThrottle;

			if(pEngine->PropSetting < 0)
				pEngine->PropSetting += 101;
			else
				if(PropSettingChanged)
					pEngine->PropSetting = FP(pModel->ModelPropSetting) * 0.01;
//DEADCODE CB 12/11/99 
//DEADCODE CB 12/11/99 			PrintVar(65+pEngine->pThrustPoint->Pos.x / 50, 22, "ET %.0f ", FP(pEngine->ThrottleSetting));
//DEADCODE CB 12/11/99 			PrintVar(65+pEngine->pThrustPoint->Pos.x / 50, 23, "EP %.2f ", FP(pEngine->PropSetting));
//DEADCODE CB 12/11/99 			PrintVar(65+pEngine->pThrustPoint->Pos.x / 50, 24, "%.0f ",    FP(pEngine->Speed * 954.9));
		}
	
//DEADCODE CB 12/11/99 	PrintVar(60, 20, "AT %.0f ", FP(ControlledAC->fly.thrustpercent));
//DEADCODE CB 12/11/99 	PrintVar(70, 20, "MT %.0f ", FP(pModel->ModelThrottle));
//DEADCODE CB 12/11/99 	PrintVar(60, 21, "AP %.0f ", FP(ControlledAC->fly.propsetting));
//DEADCODE CB 12/11/99 	PrintVar(70, 21, "MP %.0f ", FP(pModel->ModelPropSetting));
	
	if(Save_Data.flightdifficulty[FD_ENGINEMANAGMENT])
		GetComplexEngineKeys(ControlledAC);
#ifdef PRINT_STICK_RUDDER
PrintVar(65, 5, "%.0f ", FP(ControlledAC->fly.thrustpercent));
PrintVar(60, 7, "%.0f ", FP(ControlledAC->fly.pModel->EngineList->ThrottleSetting));
if(ControlledAC->fly.pModel->EngineList->List.pNextItem)
	PrintVar(70, 7, "%.0f ", FP(ControlledAC->fly.pModel->EngineList->List.NextItem()->ThrottleSetting));
#endif
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetComplexEngineKeys
//Author		Craig Beeston													
//Date			Thu 02 Dec 1999
//																		
//Description	Processes the fake keypresses generated by the interactive cockpit
//																		
//Inputs																
//																		
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::GetComplexEngineKeys(AirStrucPtr const ControlledAC)
{
	PMODEL pModel = ControlledAC->fly.pModel;

	if(Key_Tests.KeyPress3d(FK_BOOSTCUTOUT))
	{
		if(pModel->BoostCutout)
			pModel->BoostCutout = false;
		else
			pModel->BoostCutout = true;
	}

	switch(pModel->FuelCockType)
	{
		case FC_2LEVERS:
		{
			SWord val = ControlledAC->fly.FuelCockPos;
			if(Key_Tests.KeyPress3d(FK_FUELCOCK1))
			{
				ControlledAC->fly.FuelCockPos = (val & 0x02) + (0x01 - (val & 0x01));
				for(SWord i = 0; i < 4; i++)
					ControlledAC->fly.use_this_tank[i] = pModel->FuelCockTanks[ControlledAC->fly.FuelCockPos][i];
			}

			if(Key_Tests.KeyPress3d(FK_FUELCOCK2))
			{
				ControlledAC->fly.FuelCockPos = (val & 0x01) + (0x02 - (val & 0x02));
				for(SWord i = 0; i < 4; i++)
					ControlledAC->fly.use_this_tank[i] = pModel->FuelCockTanks[ControlledAC->fly.FuelCockPos][i];
			}

			break;
		}
		case FC_4POSITION:
		{
			if(Key_Tests.KeyPress3d(FK_FUELCOCK1))
			{
				ControlledAC->fly.FuelCockPos++;
				if(ControlledAC->fly.FuelCockPos > 3)
					ControlledAC->fly.FuelCockPos--;
				else
				{
					bool reset = true;
					for(SWord i = 0; i < 4; i++)
						if(pModel->FuelCockTanks[ControlledAC->fly.FuelCockPos][i] == true)
							reset = false;
					if(reset)
						ControlledAC->fly.FuelCockPos--;
				}
				for(SWord i = 0; i < 4; i++)
					ControlledAC->fly.use_this_tank[i] = pModel->FuelCockTanks[ControlledAC->fly.FuelCockPos][i];
			}

			if(Key_Tests.KeyPress3d(FK_FUELCOCK2))
			{
				if(ControlledAC->fly.FuelCockPos > 0)
					ControlledAC->fly.FuelCockPos--;

				for(SWord i = 0; i < 4; i++)
					ControlledAC->fly.use_this_tank[i] = pModel->FuelCockTanks[ControlledAC->fly.FuelCockPos][i];
			}
			break;
		}
		break;
	}

	PENGINE pEngine0 = pModel->EngineList;
	PENGINE pEngine1 = NULL;

	if(pEngine0)
		pEngine1 = pEngine0->List.NextItem();

	if(pEngine0)
	{
		switch(pEngine0->MagType)
		{
			case MT_2SWITCHES:
			{
				if(Key_Tests.KeyPress3d(FK_MAG01))
					pEngine0->Magnetos = (pEngine0->Magnetos & 0x02) + (0x01 - (pEngine0->Magnetos & 0x01));
				if(Key_Tests.KeyPress3d(FK_MAG02))
					pEngine0->Magnetos = (pEngine0->Magnetos & 0x01) + (0x02 - (pEngine0->Magnetos & 0x02));
				break;
			}
			case MT_4POSITION:
			{
				if(Key_Tests.KeyPress3d(FK_MAGS1))
				{
					SLong tmp = pEngine0->PropSetting;
					SLong delta = _Interactive.GetDelta(INST_MAGSLIDE1, tmp);
					tmp += (delta*4)>>7;
					MODMAXMIN(tmp, 0, 3);
					pEngine0->Magnetos = tmp;
				}
				break;
			}
			break;
		}

		if((Key_Tests.KeyHeld3d(FK_PRIMER0)) && (pModel->Inst.C_PrimerPump0 & 0x01))
		{
			pModel->Inst.C_PrimerPump0 -= 5 * MODEL_DT;
			if(pModel->Inst.C_PrimerPump0 < 0)
				pModel->Inst.C_PrimerPump0 = 0;
		}
		else  if((Key_Tests.KeyHeld3d(FK_PRIMER0)) || (pModel->Inst.C_PrimerPump0 < 255))
		{
			pModel->Inst.C_PrimerPump0 += 2.5 * MODEL_DT;
			if(pModel->Inst.C_PrimerPump0 > 255)
				pModel->Inst.C_PrimerPump0 = 255;

			if((pEngine0->FuelInPipes > 0.5) && (pEngine0->Priming < 1))
				pEngine0->Priming += 0.0032 * MODEL_DT;
		}


		if(Key_Tests.KeyHeld3d(FK_ENGINESTARTER0))
		{
			if (!pEngine0->Starting)
				_Miles.PlayRestart(ControlledAC->classtype->enginestartsnd,ItemPtr(NULL));

			pEngine0->Starting = true;
		}
		else
		{
			pEngine0->Starting = false;
		}
	}

	if(pEngine1)
	{
		switch(pEngine1->MagType)
		{
			case MT_2SWITCHES:
			{
				if(Key_Tests.KeyPress3d(FK_MAG01))
					pEngine1->Magnetos = (pEngine1->Magnetos & 0x02) + (0x01 - (pEngine1->Magnetos & 0x01));
				if(Key_Tests.KeyPress3d(FK_MAG02))
					pEngine1->Magnetos = (pEngine1->Magnetos & 0x01) + (0x02 - (pEngine1->Magnetos & 0x02));
				break;
			}
			case MT_4POSITION:
			{
				if(Key_Tests.KeyPress3d(FK_MAGS2))
				{
					SLong tmp = pEngine1->PropSetting;
					SLong delta = _Interactive.GetDelta(INST_MAGSLIDE2, tmp);
					tmp += (delta*4)>>7;
					MODMAXMIN(tmp, 0, 3);
					pEngine1->Magnetos = tmp;
				}
				break;
			}
		}

		if((Key_Tests.KeyHeld3d(FK_PRIMER1)) && (pModel->Inst.C_PrimerPump1 & 0x01))
		{
			pModel->Inst.C_PrimerPump1 -= 5 * MODEL_DT;
			if(pModel->Inst.C_PrimerPump1 < 0)
				pModel->Inst.C_PrimerPump1 = 0;
		}
		else  if((Key_Tests.KeyHeld3d(FK_PRIMER1)) || (pModel->Inst.C_PrimerPump1 < 255))
		{
			pModel->Inst.C_PrimerPump1 += 2.5 * MODEL_DT;
			if(pModel->Inst.C_PrimerPump1 > 255)
				pModel->Inst.C_PrimerPump1 = 255;

			if((pEngine1->FuelInPipes > 0.5) && (pEngine1->Priming < 1))
				pEngine1->Priming += 0.0032 * MODEL_DT;
		}

		if(Key_Tests.KeyHeld3d(FK_ENGINESTARTER1))
			pEngine1->Starting = true;
		else
			pEngine1->Starting = false;
	}
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyDeadZone															 
//Author		Craig Beeston														     _
//Date			Wed 16 Dec 1998													   |    /
//																				   |   /
//Description	Linear with dead zone clipping at top and bottom of scale		  _|_,/
//																			    /` |
//Inputs																	   /   |
//																			 _/    |
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::ApplyDeadZone(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone)
{
	FP val  = SrcVal;
	FP sign = 1;
	if(SrcVal < 0) 
	{	val *= -1;	sign *= -1;	}

	FP smooth = val / DeadZone - 0.5;
	if((smooth > 0) && (smooth < 1))
	{
		smooth = smooth * smooth;
		val = 1.5 * DeadZone;
	}
	else
		smooth = 1.0;

	val = sign * (val - DeadZone) / (32768.0 - 2.0 * DeadZone) * 32767.0 * smooth;
	MODLIMIT(val, 32767);
	
	const fDamping = 1;
	val = (DstVal * (fDamping - 1) + val) / fDamping;
	DstVal = SWord(val);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyDeadZone2
//Author		Craig Beeston												    _
//Date			Tue 6 Apr 1999											  |	   |
//																		  |   /
//Description	Quadratic with dead zone clipping at top and bottom		 _|_,/
//				Damping added										   /` |
//Inputs															  /   |
//																	_|    |
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::ApplyDeadZone2(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone)
{
	Float val  = SrcVal;
	Float sign = 1;
	if(SrcVal < 0)
	{	val *= -1;	sign *= -1;	}

	val = (val - DeadZone) / (32768.0 - 2.0 * DeadZone);
	MODMAXMIN(val, 0, 1);
	val = val * val * 32767.0 * sign;

	const fDamping = 1;
	val = (DstVal * (fDamping - 1) + val) / fDamping;
	DstVal = SWord(val);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ApplyDeadZone3
//Author		Craig Beeston
//Date			Wed 19 May 1999
//
//Description	Central deadzone, Then linear for bottom 2/3 giving 1/3 output, then steep curve towards limits
//				See "Craig\\C:\CSB\Joystick_Filter.xls"
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::ApplyDeadZone3(AirStrucPtr const ControlledAC, SWord SrcVal, int& DstVal, SWord DeadZone)
{
	UWord StartCurve1 = DeadZone;
	UWord StartLinear = 5 * DeadZone;
	UWord LinearBase  = 3 * DeadZone;
	UWord StartCurve2 = 21845;	//	2/3 * 32768
	UWord EndCurve2	  = 32767 - DeadZone; 

	SWord SrcSign, SrcAbs;
	if(SrcVal >= 0)	{SrcAbs =  SrcVal;	SrcSign =  1;}
	else			{SrcAbs = -SrcVal;	SrcSign = -1;}

	if(SrcAbs < StartCurve1)	//Centre Dead Region
	{
		DstVal = 0;
		return;
	}

	if(SrcAbs >= EndCurve2)		//Top End Dead Region
	{	
		DstVal = 32767 * SrcSign;
		return;
	}

	if(SrcAbs > StartLinear)	//Linear Section
	{
		DstVal = (32767 / 2 * (SrcAbs - LinearBase)) / (EndCurve2 - LinearBase);
		if(SrcAbs <= StartCurve2)
		{
			DstVal *= SrcSign;
			return;
		}
		else					//Steep curve
		{
			FP temp = ((FP)SrcAbs - (FP)StartCurve2) / ((FP)EndCurve2 - (FP)StartCurve2);
			temp = temp * temp;
			temp = (FP)DstVal * (1 - temp) + 32767.0 * temp;
			DstVal = temp * SrcSign;
			return;
		}
	}

	FP temp = ((FP)SrcAbs - (FP)StartCurve1) / ((FP)StartLinear - (FP)StartCurve1);
	DstVal = (32767 / 2 * (StartLinear - LinearBase)) / (EndCurve2 - LinearBase);
	DstVal = temp * temp * (FP)DstVal * (FP)SrcSign;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetRPMABKeys
//Author		R. Hyde 
//Date			Tue 31 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::GetRPMABKeys(AirStrucPtr const ControlledAC)

{

// Called from GetStickKeys, at end						//ARM 11Apr97

//rdh needed to know whether on internal or external here
//DEADCODE CSB 05/11/99  	if	(ControlledAC->weap.centre.int_fuel >0)
 	{
		if (Key_Tests.KeyPress3d (RPM_BIG_UP))
 			ControlledAC->fly.thrustpercent += BIGTHRUSTSTEP;

		if (Key_Tests.KeyPress3d (RPM_BIG_DOWN))
 			ControlledAC->fly.thrustpercent -= BIGTHRUSTSTEP;
 
 		if((Key_Tests.KeyPress3d(RPM_UP)) || ((Key_Tests.KeyHeld3d(RPM_UP)) && (!(ControlledAC->fly.pModel->FrameCount & 0x07))))
			ControlledAC->fly.thrustpercent += SMALLTHRUSTSTEP;

		if((Key_Tests.KeyPress3d(RPM_DOWN)) || ((Key_Tests.KeyHeld3d(RPM_DOWN)) && (!(ControlledAC->fly.pModel->FrameCount & 0x07))))
 			ControlledAC->fly.thrustpercent -= SMALLTHRUSTSTEP;

		MODMAXMIN(ControlledAC->fly.thrustpercent, 0, 100);

		if (!OverLay.pCurScr)
		{
			if (Key_Tests.KeyPress3d (RPM_ZERO))
 				ControlledAC->fly.thrustpercent = 0;

			if (Key_Tests.KeyPress3d (RPM_10))
 				ControlledAC->fly.thrustpercent = 10;

			if (Key_Tests.KeyPress3d (RPM_20))
	 			ControlledAC->fly.thrustpercent = 20;

			if (Key_Tests.KeyPress3d (RPM_30))
 				ControlledAC->fly.thrustpercent = 30;

			if (Key_Tests.KeyPress3d (RPM_40))
	 			ControlledAC->fly.thrustpercent = 40;

			if (Key_Tests.KeyPress3d (RPM_50))
 				ControlledAC->fly.thrustpercent = 50;
 
			if (Key_Tests.KeyPress3d (RPM_60))
 				ControlledAC->fly.thrustpercent = 60;
 
			if (Key_Tests.KeyPress3d (RPM_70))
 				ControlledAC->fly.thrustpercent = 70;
 
			if (Key_Tests.KeyPress3d (RPM_80))
 				ControlledAC->fly.thrustpercent = 80;

			if (Key_Tests.KeyPress3d (RPM_90))
 				ControlledAC->fly.thrustpercent = 90;
 
			if (Key_Tests.KeyPress3d (RPM_00))
			{
				ControlledAC->fly.thrustpercent = 100;
				ControlledAC->fly.pModel->BoostCutout = true;
			}
		}
 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SensitivityMsg
//Author		R. Hyde 
//Date			Tue 3 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::SensitivityMsg(AirStrucPtr const ControlledAC)
{
//DeadCode  10Aug00 		switch (Save_Data.keysensitivity)
//DeadCode  10Aug00 		{
//DeadCode  10Aug00 			case	0:
//DeadCode  10Aug00 			{
//DeadCode  10Aug00 //TEMP			 	Persons_2.AddMessage(UserMsg::TIME,TEXT_SENSITIVITY0,NULL);//RDH 03Dec96
//DeadCode  10Aug00 				break;
//DeadCode  10Aug00 			}
//DeadCode  10Aug00 			case	1:
//DeadCode  10Aug00 			{
//DeadCode  10Aug00 //TEMP			 	Persons_2.AddMessage(UserMsg::TIME,TEXT_SENSITIVITY1,NULL);//RDH 03Dec96
//DeadCode  10Aug00 				break;
//DeadCode  10Aug00 			}
//DeadCode  10Aug00 			case	2:
//DeadCode  10Aug00 			{
//DeadCode  10Aug00 //TEMP			 	Persons_2.AddMessage(UserMsg::TIME,TEXT_SENSITIVITY2,NULL);//RDH 03Dec96
//DeadCode  10Aug00 				break;
//DeadCode  10Aug00 			}
//DeadCode  10Aug00 			case	3:
//DeadCode  10Aug00 			{
//DeadCode  10Aug00 //TEMP			 	Persons_2.AddMessage(UserMsg::TIME,TEXT_SENSITIVITY3,NULL);//RDH 03Dec96
//DeadCode  10Aug00 				break;
//DeadCode  10Aug00 			}
//DeadCode  10Aug00 		}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetStickKeys
//Author		R. Hyde 
//Date			Mon 30 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ManualPilot::GetStickKeys (AirStrucPtr const ControlledAC)

{
	{
		if (Key_Tests.KeyPress3d (CHEATLIFTKEY))					//RDH 21Jul96
		{															//RDH 21Jul96
//DEADCODE AMM 26/11/99 			if (!_DPlay.Implemented || (_DPlay.Implemented && _DPlay.liftcheat))
#ifdef NDEBUG
 			if (!_DPlay.Implemented)
#endif
			{
				if (ControlledAC->World.Y < FT_30000)					//CSB 18Jul00
					if (ControlledAC->fly.pModel->Controlled)			//ARM 15May97
					{


						_DPlay.CheckSeen();								//AMM 12Jul00
						_DPlay.AddDeltas(ControlledAC,FALSE,0);			//AMM 12Jul00
						ControlledAC->fly.pModel->ResetDeltaPos (ControlledAC,0,FT_1000,0);//DAW 15Jun98
						_DPlay.AddDeltas(ControlledAC,TRUE,0);			//AMM 12Jul00
						_DPlay.BackupSeen();							//AMM 12Jul00

//DeadCode AMM 12Jul00 						if (!_Replay.Playback)
//DeadCode AMM 12Jul00 						{
//DeadCode AMM 12Jul00 							_DPlay.Deltas.lastpos.Y+=FT_1000;
//DeadCode AMM 12Jul00 						}
					}
			}
		}															//RDH 21Jul96
	}

	PMODEL pMod = ControlledAC->fly.pModel;


	if (Key_Tests.KeyPress3d (SENS_UP))
	{
		if (Save_Data.keysensitivity < MAXSENSITIVITY)
		{
			_Miles.PlaySample (FIL_SFX_GUN_RELOADING4);					//RJS 16Oct00
			Save_Data.keysensitivity++;
			SensitivityMsg(ControlledAC);										//RDH 03Dec96

		}else
		{
			_Miles.PlaySample (FIL_SFX_GUN_CLICK1);						//RJS 16Oct00

		}
		OverLay.TriggerMessage(COverlay::SENSMESS,Save_Data.keysensitivity);
	}
	if (Key_Tests.KeyPress3d (SENS_DOWN))
	{
		if (Save_Data.keysensitivity > MINSENSITIVITY)
		{
			_Miles.PlaySample (FIL_SFX_GUN_RELOADING4);					//RJS 16Oct00
			Save_Data.keysensitivity--;
			SensitivityMsg(ControlledAC);										//RDH 03Dec96
		}else
		{
			_Miles.PlaySample (FIL_SFX_GUN_CLICK1);						//RJS 16Oct00

		}
		OverLay.TriggerMessage(COverlay::SENSMESS,Save_Data.keysensitivity);
	}

//DeadCode AMM 24Nov99 		FP fDelta = 32767 * Save_Data.keysensitivity / MAXSENSITIVITY * ControlledAC->fly.pModel->MODEL_DT / 100;
		FP fDelta = 32767 * Save_Data.keysensitivity / MAXSENSITIVITY * MODEL_DT / 100;//AMM 24Nov99
		SWord Delta1 = (int)fDelta;
		SWord Delta2 = (int)(2 * fDelta);
		UWord LimitVal = 32767 * Save_Data.keysensitivity / MAXSENSITIVITY;
		Bool KeyPressed = FALSE;

		if (Key_Tests.KeyHeld3d (ELEVATOR_BACK))
		{
			cntstick_b = 1;
			if(ControlledAC->fly.elevator > 0)
				ControlledAC->fly.elevator = 0;
			if(ControlledAC->fly.elevator > -32767 + Delta1)
				ControlledAC->fly.elevator -= Delta1;	//CSB 29/01/99
			KeyPressed = TRUE;
		}
		else
		{
			if (Key_Tests.KeyHeld3d (ELEVATOR_FORWARD))
			{
				cntstick_f = 1;
				if(ControlledAC->fly.elevator < 0)
					ControlledAC->fly.elevator = 0;
				if(ControlledAC->fly.elevator < 32767 - Delta1)
					ControlledAC->fly.elevator += Delta1;	//CSB 29/01/99
				KeyPressed = TRUE;
			}
			elseif( (cntstick_b != 0) || (cntstick_f != 0) )	//No key pressed but still effects of previous key press
			{
				if( (ControlledAC->fly.elevator >= -Delta1) && (ControlledAC->fly.elevator <= Delta1) )
				{
					ControlledAC->fly.elevator = 0;
					cntstick_f = 0;
					cntstick_b = 0;
				}
				elseif (ControlledAC->fly.elevator < -Delta1) 
					ControlledAC->fly.elevator += Delta1;

				elseif(ControlledAC->fly.elevator > Delta1)
					ControlledAC->fly.elevator -= Delta1; 
			}
		}
		if(KeyPressed)
			MODLIMIT(ControlledAC->fly.elevator, LimitVal);

//////////////////////////////////////////////
		KeyPressed = FALSE;

		if (Key_Tests.KeyHeld3d (AILERON_LEFT))
		{
			cntstick_l = 1;
			if(ControlledAC->fly.aileron > 0)
				ControlledAC->fly.aileron = 0;
			if(ControlledAC->fly.aileron > -32767 + Delta2)
				ControlledAC->fly.aileron -= Delta2;	//CSB 29/01/99
			KeyPressed = TRUE;
		}
		else
		{
			if (Key_Tests.KeyHeld3d (AILERON_RIGHT))
			{
				cntstick_r = 1;
				if(ControlledAC->fly.aileron < 0)
					ControlledAC->fly.aileron = 0;
				if(ControlledAC->fly.aileron < 32767 - Delta2)
					ControlledAC->fly.aileron += Delta2;	//CSB 29/01/99
				KeyPressed = TRUE;
			}
			elseif( (cntstick_l != 0) || (cntstick_r != 0) )	//No key pressed but still effects of previous key press
			{
				if( (ControlledAC->fly.aileron >= -Delta2) && (ControlledAC->fly.aileron <= Delta2) )
				{
					ControlledAC->fly.aileron = 0;
					cntstick_l = 0;
					cntstick_r = 0;
				}
				elseif (ControlledAC->fly.aileron < -Delta2) 
					ControlledAC->fly.aileron += Delta2;

				elseif(ControlledAC->fly.aileron > Delta2)
					ControlledAC->fly.aileron -= Delta2; 
			}
		}
		if(KeyPressed)
			MODLIMIT(ControlledAC->fly.aileron, LimitVal);

//////////////////////////////////////////////
		KeyPressed = FALSE;

		if (Key_Tests.KeyHeld3d (RUDDER_LEFT))
		{
			cntrudder_l = 1;
			if(ControlledAC->fly.rudder > 0)
				ControlledAC->fly.rudder = 0;
			if(ControlledAC->fly.rudder > -32767 + Delta2)
				ControlledAC->fly.rudder -= Delta2;	//CSB 29/01/99
			KeyPressed = TRUE;
		}
		else
		{
			if (Key_Tests.KeyHeld3d (RUDDER_RIGHT))
			{
				cntrudder_r = 1;
				if(ControlledAC->fly.rudder < 0)
					ControlledAC->fly.rudder = 0;
				if(ControlledAC->fly.rudder < 32767 - Delta2)
					ControlledAC->fly.rudder += Delta2;	//CSB 29/01/99
				KeyPressed = TRUE;
			}
			elseif( (cntrudder_l != 0) || (cntrudder_r != 0) )	//No key pressed but still effects of previous key press
			{
				if( (ControlledAC->fly.rudder >= -Delta2) && (ControlledAC->fly.rudder <= Delta2) )
				{
					ControlledAC->fly.rudder = 0;
					cntrudder_l = 0;
					cntrudder_r = 0;
				}
				elseif (ControlledAC->fly.rudder < -Delta2) 
					ControlledAC->fly.rudder += Delta2;

				elseif(ControlledAC->fly.rudder > Delta2)
					ControlledAC->fly.rudder -= Delta2; 
			}
		}
		if(KeyPressed)
			MODLIMIT(ControlledAC->fly.rudder, LimitVal);


//joystick control

		keyboardcontrol = TRUE;
		_Analogue.PollPosition();
		SWord	ail  =_Analogue.ReadPosition(AU_AILERON);
		SWord	elev =_Analogue.ReadPosition(AU_ELEVATOR);
		SWord	rudd =_Analogue.ReadPosition(AU_RUDDER);
		SWord	thro =_Analogue.ReadPosition(AU_THROTTLE);
		SWord	thro2=_Analogue.ReadPosition(AU_THROTTLE2);
		SWord	prop =_Analogue.ReadPosition(AU_PROPPITCH);
		SWord	prop2=_Analogue.ReadPosition(AU_PROPPITCH2);
		UWord	xy3_pos;
		SWord	xy3_sign;
		SLong	aileron,elevator,rudder;

		flight_ctl* Fly = &ControlledAC->fly;
		SLong delta, fsmooth;

//DeadCode MS 3Oct00 		const dEle  = 4000;		const sEle1	= 4;		const sEle2	= 1;
//DeadCode MS 3Oct00 		const dAil  = 1;		const sAil1 = 1;		const sAil2	= 1;
//DeadCode MS 3Oct00 		const dRud  = 4;		const sRud1	= 4;		const sRud2	= 1;
	
		const dEle  = 4000;		const sEle1	= 4;		const sEle2	= 1;
		const dAil  = 1;		const sAil1 = 1;		const sAil2	= 1;
		const dRud  = 1;		const sRud1	= 1;		const sRud2	= 1;
	

		if ((ail!=-0x8000) && (cntstick_r == 0)&& (cntstick_l == 0))
		{
			keyboardcontrol = FALSE;
			aileron = MAXAILERON * ail/ 32768;
			delta = aileron - Fly->aileron;
			if((delta > -dAil) && (delta < dAil))	fsmooth = sAil1;
			else								 	fsmooth = sAil2;
			Fly->aileron = ((fsmooth - 1) * Fly->aileron + aileron) / fsmooth;
		}
		if ((elev!=-0x8000) && (cntstick_f == 0)&& (cntstick_b == 0))
		{
			keyboardcontrol = FALSE;
			elevator = - MAXELEVATOR * elev/ 32768;
			delta = elevator - Fly->elevator;
			if((delta > -dEle) && (delta < dEle))	fsmooth = sEle1;
			else								 	fsmooth = sEle2;
			Fly->elevator = ((fsmooth - 1) * Fly->elevator + elevator) / fsmooth;
		}
		if ((rudd!=-0x8000) && (cntrudder_l == 0) && (cntrudder_r == 0) )
		{
			rudder = MAXRUDDER * rudd/ 32768;
			ControlledAC->fly.rudder = (SWord) rudder;
			delta = rudder - Fly->rudder;
			if((delta > -dRud) && (delta < dRud))	fsmooth = sRud1;
			else								 	fsmooth = sRud2;
			Fly->rudder = ((fsmooth - 1) * Fly->rudder + rudder) / fsmooth;
		}

		if(thro != -0x8000)
		{
			Math_Lib.Pos (thro,xy3_pos,xy3_sign);
			SLong TempThrust = xy3_pos;

			int DeadZone = _Analogue.tune[AU_THROTTLE].deadzones;//2048;//1024;
			if(TempThrust < DeadZone) TempThrust = 0;
			else if(TempThrust >= 32768 - DeadZone) TempThrust = 100;
			else TempThrust = (100 * (TempThrust - DeadZone)) / (32768 - 2 * DeadZone);

			ControlledAC->fly.thrustpercent = TempThrust;

			if (thro2 != -0x8000)
			{
				Math_Lib.Pos(thro2,xy3_pos,xy3_sign);
				SLong TempThrust = xy3_pos;

				int DeadZone = _Analogue.tune[AU_THROTTLE2].deadzones;//2048;//1024;
				if(TempThrust < DeadZone) TempThrust = 0;
				else if(TempThrust >= 32768 - DeadZone) TempThrust = 100;
				else TempThrust = (100 * (TempThrust - DeadZone)) / (32768 - 2 * DeadZone);

				PMODEL pMod = ControlledAC->fly.pModel;
				if((pMod) && (pMod->EngineList) && (pMod->EngineList->List.pNextItem))
					pMod->EngineList->List.NextItem()->ThrottleSetting = TempThrust - 101;
			}

			if (Key_Tests.KeyPress3d (RPM_00))
				ControlledAC->fly.pModel->BoostCutout = true;
		}
		else
			GetRPMABKeys(ControlledAC);

		if(prop != -0x8000)
		{
			Math_Lib.Pos (prop,xy3_pos,xy3_sign);
			SLong TempProp = xy3_pos;

			int DeadZone = _Analogue.tune[AU_PROPPITCH].deadzones;//2048;//1024;
			if(TempProp < DeadZone) TempProp = 0;
			else if(TempProp >= 32768 - DeadZone) TempProp = 100;
			else TempProp = (100 * (TempProp - DeadZone)) / (32768 - 2 * DeadZone);

			ControlledAC->fly.propsetting = TempProp;

			if (prop2 != -0x8000)
			{
				Math_Lib.Pos(prop2,xy3_pos,xy3_sign);
				SLong TempProp = xy3_pos;

				int DeadZone = _Analogue.tune[AU_PROPPITCH2].deadzones;//2048;//1024;
				if(TempProp < DeadZone) TempProp = 0;
				else if(TempProp >= 32768 - DeadZone) TempProp = 100;
				else TempProp = (100 * (TempProp - DeadZone)) / (32768 - 2 * DeadZone);

				PMODEL pMod = ControlledAC->fly.pModel;
				if((pMod) && (pMod->EngineList) && (pMod->EngineList->List.pNextItem))
					pMod->EngineList->List.NextItem()->PropSetting = TempProp - 101;
			}
		}
		else
		{
			if (Key_Tests.KeyPress3d (MAXPROPPITCH))
				ControlledAC->fly.propsetting = 0;

			if (Key_Tests.KeyPress3d (MINPROPPITCH))
				ControlledAC->fly.propsetting = 100;
			
			if((Key_Tests.KeyHeld3d(PROPPITCHDOWN)) && (!(ControlledAC->fly.pModel->FrameCount & 0x01)))
				ControlledAC->fly.propsetting++;
			
			if((Key_Tests.KeyHeld3d(PROPPITCHUP)) && (!(ControlledAC->fly.pModel->FrameCount & 0x01)))
				ControlledAC->fly.propsetting--;

			MODMAXMIN(ControlledAC->fly.propsetting, 0, 100);
		}

}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SecondaryControls
//Author		Andrew McRae
//Date			Tue 12 Aug 1997
//
//Description	Flaps, slats, gear etc.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ManualPilot::SecondaryControls (AirStrucPtr const ControlledAC2)
{

	PMODEL pModel = ControlledAC2->fly.pModel;
	MODEL& Mod = *ControlledAC2->fly.pModel;

	// Wheel Brakes

	if (Key_Tests.KeyHeld3d (LEFTWHEELBRAKE))
		pModel->LeftWheelBrake = 0x4000;
	else
		pModel->LeftWheelBrake = 0x0000;

	if (Key_Tests.KeyHeld3d (RIGHTWHEELBRAKE))
		pModel->RightWheelBrake = 0x4000;
	else
		pModel->RightWheelBrake = 0x0000;


	// Flaps, Speed Brakes, Slats, Gear up/down

	PAERODEVICE pAeroDevice = pModel->DeviceList;
	while (pAeroDevice != NULL)
	{
		pAeroDevice->Action (ControlledAC2, AeroDevice::CT_KEYS);
		pAeroDevice = pAeroDevice->List.NextItem ();
	}
	
	if( (Key_Tests.KeyPress3d (EMERGENCYGEAR)) && (!pModel->EmergencyGearUsed) )
	{
		for(pAeroDevice = pModel->DeviceList; pAeroDevice; pAeroDevice = pAeroDevice->List.NextItem())
		{
			if(pAeroDevice->Type == AERODEVICE::DT_GEAR)
			{
				pModel->EmergencyGearUsed = TRUE;
				_Miles.PlaySample (FIL_SFX_COMPRESSED_AIR);

				AircraftAnimData*	adptr;
				adptr = (AircraftAnimData *)ControlledAC2->Anim;

				if(		(pAeroDevice->UpKey != NULLKEY) && (Math_Lib.rnd(256) > adptr->LEFTWHEEL)
					||	(pAeroDevice->UpKey == NULLKEY) && (Math_Lib.rnd(256) > adptr->RIGHTWHEEL) )
					pAeroDevice->Attractor = 0x4000;
				else
					pAeroDevice->Attractor = (pAeroDevice->Attractor + 0x4000) / 2;
				pAeroDevice->Broken = TRUE;
			}
		}
	}

	// Elevator Trim
	if (Key_Tests.KeyHeld3d (ELEVTRIMUP))
		if (pModel->ElevatorTrim < pModel->MaxElevatorTrim)
			pModel->ElevatorTrim += 16;

	if (Key_Tests.KeyHeld3d (ELEVTRIMDOWN))
		if (pModel->ElevatorTrim > -pModel->MaxElevatorTrim)
			pModel->ElevatorTrim -= 16;

	// Aileron Trim
	if (Key_Tests.KeyHeld3d (AILTRIMUP))
		if (pModel->AileronTrim < pModel->MaxAileronTrim)
			pModel->AileronTrim += 16;

	if (Key_Tests.KeyHeld3d (AILTRIMDOWN))
		if (pModel->AileronTrim > -pModel->MaxAileronTrim)
			pModel->AileronTrim -= 16;

	// Rudder Trim
	if (Key_Tests.KeyHeld3d (RUDTRIMUP))
		if (pModel->RudderTrim < pModel->MaxRudderTrim)
			pModel->RudderTrim += 16;

	if (Key_Tests.KeyHeld3d (RUDTRIMDOWN))
		if (pModel->RudderTrim > -pModel->MaxRudderTrim)
			pModel->RudderTrim -= 16;

	if(Key_Tests.KeyPress3d(RESETALLTRIM))
	{
		pModel->ElevatorTrim = 0;
		pModel->AileronTrim  = 0;
		pModel->RudderTrim   = 0;
	}

	if((Key_Tests.KeyPress3d(FK_ELEVATORTRIM)) && (pModel->MaxElevatorTrim > 0))
	{
		SLong temptrim = pModel->ElevatorTrim;
		SLong delta = _Interactive.GetDelta(INST_ELEVATOR, temptrim);

		temptrim += (delta * pModel->MaxElevatorTrim)>>7;
		MODLIMIT(temptrim, pModel->MaxElevatorTrim);

		pModel->ElevatorTrim = temptrim;
	}

//DeadCode CSB 03/12/99		if((Key_Tests.KeyPress3d(FK_AILERONTRIM)) && (pModel->MaxAileronTrim > 0))
//DeadCode CSB 03/12/99		{
//DeadCode CSB 03/12/99			SLong temptrim = pModel->MaxAileronTrim;
//DeadCode CSB 03/12/99			SLong delta = _Interactive.GetDelta(INST_AILERON, temptrim);
//DeadCode CSB 03/12/99	
//DeadCode CSB 03/12/99			temptrim += (delta * pModel->MaxAileronTrim)>>7;
//DeadCode CSB 03/12/99			MODLIMIT(temptrim, pModel->MaxAileronTrim);
//DeadCode CSB 03/12/99	
//DeadCode CSB 03/12/99			pModel->MaxAileronTrim = temptrim;
//DeadCode CSB 03/12/99		}

	if((Key_Tests.KeyPress3d(FK_RUDDERTRIM)) && (pModel->MaxRudderTrim > 0))
	{
		SLong temptrim = pModel->RudderTrim;
		SLong delta = _Interactive.GetDelta(INST_RUDDER, temptrim);

		temptrim += (delta * pModel->MaxRudderTrim)>>7;
		MODLIMIT(temptrim, pModel->MaxRudderTrim);

		pModel->RudderTrim = temptrim;
	}

	if( (Key_Tests.KeyPress3d (CYCLEENGINES)) && (pModel->EngineList->List.NextItem()) )
	{
		switch(pModel->EngineSelected)
		{
			case ES_PORT:
				pModel->EngineSelected = ES_STBD; 
//DEADCODE CSB 02/03/00 				PrintString(75, 24, "STBD");
				_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_STARBOARD, MSG_HIPRIORITY,Manual_Pilot.ControlledAC2,NULL,NULL));
				break;
			case ES_STBD:
				pModel->EngineSelected = ES_BOTH; 
//DEADCODE CSB 02/03/00 				PrintString(75, 24, "BOTH");
				_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_BOTH, MSG_HIPRIORITY,Manual_Pilot.ControlledAC2,NULL,NULL));
				break;
			case ES_BOTH:
				pModel->EngineSelected = ES_PORT; 
//DEADCODE CSB 02/03/00 				PrintString(75, 24, "PORT");
				_Radio.TriggerMsg(MESSAGE_STRUC(PHRASE_PORT, MSG_HIPRIORITY,Manual_Pilot.ControlledAC2,NULL,NULL));
				break;
		}
	}

	if(Key_Tests.KeyPress3d(FUELGUAGESELECTOR))
	{
		pModel->Inst.C_FuelGuageSelector++;
		if((pModel->Inst.C_FuelGuageSelector == 4) || (pModel->Inst.FuelGuageTank[pModel->Inst.C_FuelGuageSelector] == -1))
			pModel->Inst.C_FuelGuageSelector = 0;
	}
}

