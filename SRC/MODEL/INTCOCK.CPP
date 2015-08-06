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
//Filename       intcock.cpp
//System         
//Author         Robert Slater
//Date           Fri 19 Nov 1999
//Description    
//------------------------------------------------------------------------------

#include	"dosdefs.h"
#include	"keymaps.h"
#include	"keytest.h"
#include	"intcock.h"
#include	"..\mfc\resource.h"


InteractiveCockpit	_Interactive;


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InteractiveCockpit
//Author		Robert Slater
//Date			Fri 19 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
InteractiveCockpit::InteractiveCockpit()
{
// Just instruments...

	Add(INST_ALT,			IDS_ALTMETER);
	Add(INST_CLOCK,			IDS_CLOCK);
	Add(INST_AIRSPEED,		IDS_AIRSPEED);
	Add(INST_ARTHORIZ,		IDS_ARTHORIZ);
	Add(INST_CLIMB,			IDS_CLIMB);
	Add(INST_RADIOALT,		IDS_RADIOALT);
	Add(INST_DIRECTION,		IDS_DIRECTION);
	Add(INST_TURN,			IDS_TURN);			//Slip & Turn
	Add(INST_MECHUC,		IDS_MECHUC);
	Add(INST_FUELCONTENT,	IDS_FUELCONTENT);
	Add(INST_FUELPRESSURE,	IDS_FUELPRESSURE);
	Add(INST_OILCONTENT,	IDS_OILCONTENT);
	Add(INST_OILPRESSURE,	IDS_OILPRESSURE);
	Add(INST_OILTEMP,		IDS_OILTEMP);
	Add(INST_RADIATORTEMP,	IDS_RADIATORTEMP);
	Add(INST_BOOST,			IDS_BOOST);
	Add(INST_VOLTMETER,		IDS_VOLTMETER);
	Add(INST_COMPASS,		IDS_COMPASS);
	Add(INST_PITCH,			IDS_PITCH);
	Add(INST_FLAPINDICATOR,	IDS_FLAPINDICATOR);
	Add(INST_GUNAMMO,		IDS_GUNAMMO);
	Add(INST_CANNONAMMO,	IDS_CANNONAMMO);
	Add(INST_ENGINESPEED,	IDS_ENGINESPEED);	//Engine RPM
	Add(INST_ELEVDIAL,		IDS_IELEVATOR);		//Elevator Trim
	Add(INST_UCINDICATOR,	IDS_UNDERCARRIAGE);	//Undercarriage status
	Add(INST_PPITCHDIAL,	IDS_IPROPPITCH);
	Add(INST_DIVEPRESETIND,	IDS_DIVEPRESETINDICATOR);

// Interactive instruments...

	Add(INST_RUDDER,		FK_RUDDERTRIM,		ICT_SLIDE,		IDS_IRUDDER,		INSTDIR_LEFTRIGHT);
	Add(INST_ELEVATOR,		FK_ELEVATORTRIM,	ICT_SLIDE,		IDS_IELEVATOR,		INSTDIR_UPDOWN);
	Add(INST_ARMED,			FK_ARMED,			ICT_SWITCH,		IDS_ARMED,			FIL_SFX_NO_AMMO_CLICK);
	Add(INST_FLAPSUP,		FLAPSUP,			ICT_SWITCH,		IDS_FLAPSUP,		FIL_SFX_CPT_HANDLE);
	Add(INST_FLAPSDOWN,		FLAPSDOWN,			ICT_SWITCH,		IDS_FLAPSDOWN,		FIL_SFX_CPT_HANDLE);
	Add(INST_UNDERCARRIAGE,	GEARUPDOWN,			ICT_SWITCH,		IDS_UNDERCARRIAGE,	FIL_SFX_CPT_HANDLE);
	Add(INST_EMERGENCYUC,	EMERGENCYGEAR,		ICT_SWITCH,		IDS_EMERGENCYUC,	FIL_SFX_CPT_HANDLE);
	Add(INST_THROTTLE,		FK_THROTTLE0,		ICT_SLIDE,		IDS_ITHROTTLE,		INSTDIR_UPDOWN);
	Add(INST_PROPPITCH,		FK_PROPPITCH0,		ICT_SLIDE,		IDS_IPROPPITCH,		INSTDIR_UPDOWN);
	Add(INST_LANDING,		FK_LANDING,			ICT_SWITCH,		IDS_ILANDING,		FIL_SFX_NO_AMMO_CLICK);
	Add(INST_GUNCAM,		RECORDTOGGLE,		ICT_SWITCH,		IDS_GUNCAM,			FIL_SFX_NO_AMMO_CLICK);
	Add(INST_HOODCATCH,		CANOPYEJECT,		ICT_SWITCH,		IDS_HOODCATCH,		FIL_SFX_CPT_CANOPY_CATCH);
	Add(INST_PRIMER,		FK_PRIMER0,			ICT_HOLDDOWN,	IDS_PRIMER,			FIL_SFX_CPT_PUMP);
	Add(INST_FUELCOCKMAIN,	FK_FUELCOCK1,		ICT_SWITCH,		IDS_FUELCOCK,		FIL_SFX_CPT_SWITCH_SELECT);
	Add(INST_FUELCOCKRESERVE,FK_FUELCOCK2,		ICT_SWITCH,		IDS_FUELCOCK,		FIL_SFX_CPT_SWITCH_SELECT);
	Add(INST_ENGINESTARTER,	FK_ENGINESTARTER0,	ICT_HOLDDOWN,	IDS_ENGINESTARTER,	FIL_SFX_CPT_SWITCH_MECH);
	Add(INST_ENGINESTARTER1,FK_ENGINESTARTER1,	ICT_HOLDDOWN,	IDS_ENGINESTARTER,	FIL_SFX_CPT_SWITCH_MECH);
	Add(INST_BOOSTCUTOUT,	FK_BOOSTCUTOUT,		ICT_SWITCH,		IDS_BOOSTCUTOUT,	FIL_SFX_CPT_SWITCH_MECH);
	Add(INST_FUELTANKSELECT,FUELGUAGESELECTOR,	ICT_SWITCH,		IDS_FUELTANKSELECT,	FIL_SFX_CPT_SWITCH_SELECT);
	Add(INST_MAGNETO1,		FK_MAG01,			ICT_SWITCH,		IDS_MAGNETO,		FIL_SFX_CPT_SWITCH_BRASS);
	Add(INST_MAGNETO2,		FK_MAG02,			ICT_SWITCH,		IDS_MAGNETO,		FIL_SFX_CPT_SWITCH_BRASS);
	Add(INST_MAGSLIDE1,		FK_MAGS1,			ICT_SLIDE,		IDS_MAGNETO,		INSTDIR_UPDOWN);
	Add(INST_MAGSLIDE2,		FK_MAGS2,			ICT_SLIDE,		IDS_MAGNETO,		INSTDIR_UPDOWN);
	Add(INST_DIVEBRAKES,	SPEEDBRAKE,			ICT_SWITCH,		IDS_DIVEBRAKES,		FIL_SFX_CPT_HANDLE);

	Add(INST_THROTTLE1,		FK_THROTTLE1,		ICT_SLIDE,		IDS_ITHROTTLE,		INSTDIR_UPDOWN);	//RJS 24May00
	Add(INST_PROPPITCH1,	FK_PROPPITCH1,		ICT_SLIDE,		IDS_IPROPPITCH,		INSTDIR_UPDOWN);	//RJS 24May00
	Add(INST_PRIMER1,		FK_PRIMER1,			ICT_HOLDDOWN,	IDS_PRIMER,			FIL_SFX_CPT_PUMP);	//RJS 24May00

//DeadCode CSB 02/12/99		Add(INST_HOODJETTISON,	FK_HOODJETTISON,	ICT_SWITCH,	IDS_HOODJETTISON);

// Shortcuts..

	Add(INST_RADIO,		RADIOCOMMS,			ICT_SWITCH,		IDS_USERADIO,	FIL_SFX_NO_AMMO_CLICK);	//RJS 11May00
	Add(INST_MAP,		GOTOMAPKEY,			ICT_SWITCH,		IDS_GOTOMAP,	FIL_SFX_OFFICE_PAPERSLIDE);	//RJS 11May00

	Clear();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Clear
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	InteractiveCockpit::Clear()
{
	lastWasValid = false;
	lastMousePressed = false;
	lastControl = ICT_NULL;
	lastKeyPress = (KeyVal3D)0;
	lastString = 0;
	lastDirection = INSTDIR_NULL;
	lastIndex = INST_NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearCollide
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	InteractiveCockpit::ClearCollide(bool	mousepressed)
{
	if((mousepressed) && (lastControl == ICT_SLIDE))
		ProcessSlider();
	else if((mousepressed) && (lastControl == ICT_HOLDDOWN))
		ProcessHoldDown();
	else
	{
		if((lastKeyPress) && (lastControl == ICT_HOLDDOWN))
			Key_Tests.KeyFake3d(lastKeyPress, FALSE, FALSE);

		lastString = 0;
		lastWasValid = false;
		lastControl = ICT_NULL;
		lastKeyPress = (KeyVal3D)0;
		lastDirection = INSTDIR_NULL;
		lastIndex = INST_NULL;
	}

	lastMousePressed = mousepressed;

//DEADCODE CSB 25/01/00 	if(mousepressed && lastWasValid)
//DEADCODE CSB 25/01/00 	{
//DEADCODE CSB 25/01/00 		if (lastControl == ICT_SLIDE)
//DEADCODE CSB 25/01/00 			ProcessSlider();
//DEADCODE CSB 25/01/00 		else if (lastControl == ICT_HOLDDOWN)
//DEADCODE CSB 25/01/00 			ProcessHoldDown();
//DEADCODE CSB 25/01/00 		else
//DEADCODE CSB 25/01/00 		{
//DEADCODE CSB 25/01/00 			//this is meaningless
//DEADCODE CSB 25/01/00 			lastControl = ICT_NULL;
//DEADCODE CSB 25/01/00 			lastString = 0;
//DEADCODE CSB 25/01/00 		}
//DEADCODE CSB 25/01/00 	}
//DEADCODE CSB 25/01/00 	else
//DEADCODE CSB 25/01/00 	{
//DEADCODE CSB 25/01/00 		lastWasValid = false;
//DEADCODE CSB 25/01/00 		lastControl = ICT_NULL;
//DEADCODE CSB 25/01/00 		lastString = 0;
//DEADCODE CSB 25/01/00 	}
//DEADCODE CSB 25/01/00 
//DEADCODE CSB 25/01/00 	lastMousePressed = mousepressed;
}	

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Collide
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	InteractiveCockpit::Collide(InstrumentKey	theKey, bool mousepressed)
{
	if((mousepressed) && (lastControl == ICT_SLIDE))
		ProcessSlider();
	else if((mousepressed) && (lastControl == ICT_HOLDDOWN))
		ProcessHoldDown();
	else if((mousepressed) && (!lastMousePressed))
	{
		keytocontrol[lastIndex].Set(false);
		keytocontrol[theKey].Set(false);

		lastWasValid = true;
		lastControl = keytocontrol[theKey].control;
		lastKeyPress = keytocontrol[theKey].keyenum;
		lastDirection = keytocontrol[theKey].direction;
		lastIndex = theKey;

		lastString = 0;
		hitMouseX = lastMouseX;
		hitMouseY = lastMouseY;
	
		if(keytocontrol[theKey].sfxfile != FIL_NULL)
			_Miles.PlayAnyDelayed(keytocontrol[theKey].sfxfile,NULL);	//RJS 16Oct00
	}
	else
	{
		if((lastKeyPress) && (lastControl == ICT_HOLDDOWN))
			Key_Tests.KeyFake3d(lastKeyPress, FALSE, FALSE);

		lastString = keytocontrol[theKey].resourcestring;
		lastFontColour = keytocontrol[theKey].fontColour;
		lastWasValid = false;
		lastControl = ICT_NULL;
		lastKeyPress = (KeyVal3D)0;
		lastDirection = INSTDIR_NULL;
		lastIndex = INST_NULL;
	}

	lastMousePressed = mousepressed;

//DEADCODE CSB 25/01/00 	if (lastControl == ICT_SLIDE)
//DEADCODE CSB 25/01/00 	{
//DEADCODE CSB 25/01/00 		if (mousepressed)
//DEADCODE CSB 25/01/00 			ProcessSlider();
//DEADCODE CSB 25/01/00 		else
//DEADCODE CSB 25/01/00 		{
//DEADCODE CSB 25/01/00 			lastWasValid = false;
//DEADCODE CSB 25/01/00 			lastControl = ICT_NULL;
//DEADCODE CSB 25/01/00 			lastString = 0;
//DEADCODE CSB 25/01/00 		}
//DEADCODE CSB 25/01/00 	}
//DEADCODE CSB 25/01/00 	else if (lastControl == ICT_HOLDDOWN)
//DEADCODE CSB 25/01/00 	{
//DEADCODE CSB 25/01/00 		if (mousepressed)
//DEADCODE CSB 25/01/00 			ProcessHoldDown();
//DEADCODE CSB 25/01/00 		else
//DEADCODE CSB 25/01/00 		{
//DEADCODE CSB 25/01/00 			lastWasValid = false;
//DEADCODE CSB 25/01/00 			lastControl = ICT_NULL;
//DEADCODE CSB 25/01/00 			lastString = 0;
//DEADCODE CSB 25/01/00 		}
//DEADCODE CSB 25/01/00 	}
//DEADCODE CSB 25/01/00 	else
//DEADCODE CSB 25/01/00 	{
//DEADCODE CSB 25/01/00 		if (!lastWasValid)
//DEADCODE CSB 25/01/00 		{
//DEADCODE CSB 25/01/00 			if (mousepressed)
//DEADCODE CSB 25/01/00 			{
//DEADCODE CSB 25/01/00 				keytocontrol[lastIndex].Set(false);
//DEADCODE CSB 25/01/00 				keytocontrol[theKey].Set(false);
//DEADCODE CSB 25/01/00 
//DEADCODE CSB 25/01/00 				lastWasValid = true;
//DEADCODE CSB 25/01/00 				lastControl = keytocontrol[theKey].control;
//DEADCODE CSB 25/01/00 				lastKeyPress = keytocontrol[theKey].keyenum;
//DEADCODE CSB 25/01/00 				lastDirection = keytocontrol[theKey].direction;
//DEADCODE CSB 25/01/00 				lastIndex = theKey;
//DEADCODE CSB 25/01/00 
//DEADCODE CSB 25/01/00 				lastString = 0;
//DEADCODE CSB 25/01/00 				hitMouseX = lastMouseX;
//DEADCODE CSB 25/01/00 				hitMouseY = lastMouseY;
//DEADCODE CSB 25/01/00 			}
//DEADCODE CSB 25/01/00 			else
//DEADCODE CSB 25/01/00 			{
//DEADCODE CSB 25/01/00 				lastString = keytocontrol[theKey].resourcestring;
//DEADCODE CSB 25/01/00 				lastControl = ICT_NULL;
//DEADCODE CSB 25/01/00 				lastWasValid = false;
//DEADCODE CSB 25/01/00 			}
//DEADCODE CSB 25/01/00 		}
//DEADCODE CSB 25/01/00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LogMousePos
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	InteractiveCockpit::LogMousePos(SWord mouseX, SWord mouseY,SLong swidth,SLong sheight)
{
	lastMouseX = mouseX;
	lastMouseY = mouseY;

	screenWidth = swidth;
	screenHeight = sheight;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Process
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	InteractiveCockpit::Process()
{
	if((lastControl == ICT_SWITCH) || (lastControl == ICT_SLIDE))
		Key_Tests.KeyFake3d(lastKeyPress,FALSE,TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessSlider
//Author		Robert Slater
//Date			Tue 23 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	InteractiveCockpit::ProcessSlider()
{
	if (lastDirection)
	{
		SLong	delta = 0;
		SLong	scaler;

		if (lastDirection == INSTDIR_LEFTRIGHT)
		{
			delta = lastMouseX - hitMouseX;
			scaler = screenWidth / 4;
		}
		else
		{
			delta = hitMouseY - lastMouseY;
			scaler = screenHeight / 4;
		}

		// delta ranges from -128 to +128

		delta <<= 7 ;
		delta /= scaler;

		if (delta > 128)
			delta = 128;
		else
			if (delta < -128)
				delta = -128;

		keytocontrol[lastIndex].theDelta = delta;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessHoldDown
//Author		Craig Beeston
//Date			Tue 25 Jan 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	InteractiveCockpit::ProcessHoldDown()
{
	if(lastControl)
		Key_Tests.KeyFake3d(lastKeyPress, TRUE, FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDelta
//Author		Robert Slater
//Date			Wed 24 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	InteractiveCockpit::GetDelta(InstrumentKey	theKey, SLong&	currentval)
{
	if (keytocontrol[theKey].control == ICT_SLIDE)
	{
		if (keytocontrol[theKey].IsSet())
			currentval = keytocontrol[theKey].theVal;
		else
		{
			keytocontrol[theKey].Set(true);
			keytocontrol[theKey].theVal = currentval;
		}

		return keytocontrol[theKey].theDelta;
	}

	return 0;
}

ULong	InteractiveCockpit::GetStringResource(ULong&	theCol)
{
	theCol = lastFontColour;

	return lastString;
}
