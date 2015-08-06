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
//Filename       sky.cpp
//System         
//Author         Andrew McRae
//Date           Mon 10 Mar 1997
//Description    Atmosphere Class
//------------------------------------------------------------------------------
//	Jobs
//	
//	Use savegame variables instead of WIND and GUSTS
//	SetContrails sets the centre of the contrail band. This needs is a variable that we need to vary
//	Use SetConditions, Wind and Gust to set things up for each day
//
//	Notes
//	SetConditions allows us to set up temp and press using fraction of allowable range as input
//	SetWind allows us to set the low and high wind speeds
//	SetGusts allows us to set up wind gusts
//
#include <stdio.h>
#include <string.h>

#include "dosdefs.h"
#include "worldinc.h"
#include "modvec.h"
#include "model.h"
#include "monotxt.h"
#include "mytime.h"
#include "grid.h"


void Atmosphere::SetMissionWind (SWord month)
{

	FP pie;
	pie = 3.14159265359;
	FP delta;
	delta = month - 6;
	if (delta < 0)
		delta = - delta;
	if (delta < 3)
	{//Summer
		wind0 = Math_Lib.rnd (6);
		dir0 = 135 + Math_Lib.rnd (45);
		windalt = 80 + Math_Lib.rnd (45);
		diralt = 45 + Math_Lib.rnd (90);

	}else
	{
		wind0 = Math_Lib.rnd (10);
		dir0 = 225 + Math_Lib.rnd (90);
		windalt = 100 + Math_Lib.rnd (75);
		diralt = 270 + Math_Lib.rnd (45);
	}

//calc wind as vector
//wind0 and windalt are in knots, the x,yz vectors are in m/s
	FP dir = (180 + dir0) * pie * 2 / 360;
	FP cos = FCos(dir);
	FP sin = FSin(dir);
	Wind0.x = wind0 * sin * 0.514;									  //RDH 02/05/99
	Wind0.y = 0;
	Wind0.z = wind0 * cos * 0.514;									  //RDH 02/05/99

	dir = (180 + diralt) * pie * 2 / 360;
	cos = FCos(dir);
	sin = FSin(dir);
	WindAlt.x = windalt * sin * 0.514;								  //RDH 02/05/99
	WindAlt.y = 0;
	WindAlt.z = windalt * cos * 0.514;								  //RDH 02/05/99

	WindAltHeight = WIND_DIRECTION_CHANGE;		//always as 35,000ft for MA

//##calc as f(date)
	delta = TempVar;
	if (delta < 0)
		delta = -delta;

	//DeadCode CSB 28/10/99		Frequency = 65535 - 26 * delta;		// 0 = always, 65535 = very infrequent
	Frequency = 0;	//CSB 28/10/99	

	MaxMagnitude = delta;
	MinMagnitude = 0;				// 1 = 1 m/s
	MaxDuration  = 500;
	MinDuration  = 250;		// csecs

}



void Atmosphere::SetMissionDensity()	//CSB 27/10/98
{
	Density0 = 10.1325 * Press0 * 0.001 / (287 * Temp0);
}


void Atmosphere::SetMissionClouds(	SLong base0, SLong top0, UByte cover0,	//CSB 10/01/00
									SLong base1, SLong top1, UByte cover1,	//CSB 10/01/00
									SLong base2, SLong top2, UByte cover2,	//CSB 10/01/00
									SLong baseF, SLong topF, UByte coverF)	//CSB 10/01/00
{
	if(base0 > -1)
	{
		Layer[0].NullCloud();
		Layer[1].NullCloud();
		Layer[2].NullCloud();
		FluffyCloud.NullCloud();

		if((top0 > base0) && (cover0 > 0))
			Layer[0].SetCloud(base0, top0, cover0);
		
		if((base1 > -1) && (top1 > base1) && (base1 > top0) && (cover1 > 0))
			Layer[1].SetCloud(base1, top1, cover1);
		
		if((base2 > -1) && (top2 > base2) && (base2 > top1) && (cover2 > 0))
			Layer[2].SetCloud(base2, top2, cover2);
		
		if((baseF > -1) && (topF > baseF) && (coverF > 0))
			FluffyCloud.SetCloud(baseF, topF, coverF);
	}
	else
	{
		//Set cloud layers automatically based on the atmospheric pressure
		FP f = (1000.0 - Press0) / 50.0;		// -1 = V high pressure -> Clear	+1 = V low pressure -> Overcast
		if(f <= 0)
		{
			Layer[0].SetCloud(0, 0, 0);
			Layer[1].SetCloud(0, 0, 0);
		
			if(f <= -0.5)
				Layer[2].SetCloud(0, 0, 0);
			else
				Layer[2].SetCloud(FT_25000 - FT_250, FT_25000 + FT_250, 128);
	
			if(f <= -1)
				FluffyCloud.SetCloud(0, 0, 0);
			else
				FluffyCloud.SetCloud(FT_5000, FT_6000, 128 * (f + 1));
		}
		else if(f < 1)
		{
			Layer[0].SetCloud(FT_5000 - FT_250, FT_5000 + FT_250, 128 + 128 * f);
			
			if(f < 0.5)
				Layer[1].SetCloud(0, 0, 0);
			else
				Layer[1].SetCloud(FT_6000 - FT_250, FT_6000 + FT_250, 256 * f);
			
			Layer[2].SetCloud(FT_25000 - FT_250, FT_25000 + FT_250, 128 + 128 * f);
			FluffyCloud.SetCloud(FT_5000 - FT_2500 * f, FT_6000 + FT_5000 * f, 128 * f);
		}
		else
		{
			Layer[0].SetCloud   ( FT_2500 - FT_250,  FT_2500 + FT_250, 255);
			Layer[1].SetCloud   ( FT_7500 - FT_250,  FT_7500 + FT_250, 255);
			Layer[2].SetCloud   (FT_25000 - FT_250, FT_25000 + FT_250, 255);
			FluffyCloud.SetCloud( FT_7500 + FT_250, FT_11000,          255);
		}
	}

	// now we need to set up the grids that will be used for ground spotting and in the 3d...
	for ( int i = 0; i<3; i++ )											//JON 28Jul00
	{
		Grid_Base::SetCloudGrid( i, Layer[i].Cover );
	}
}


UByte Atmosphere::CloudLayerCover(Coords3D* pos)
{
	for(SWord i = 0; i < 3; i++)
		if((pos->Y > Layer[0].AltBase) && (pos->Y < Layer[0].AltTop))
			return(Layer[0].Cover);

	if((Layer[0].Cover == 255) && (Layer[1].Cover == 255))
		if((pos->Y > Layer[0].AltBase) && (pos->Y < Layer[1].AltTop))
			return(255);

	return(0);
}


//DEADCODE DAW 29/01/00 //////////////////////////////////////////////////////////////////////
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 // Function:    SetMissionConditions 
//DEADCODE DAW 29/01/00 // Date:		29/01/00
//DEADCODE DAW 29/01/00 // Author:		DAW
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 //Description: 
//DEADCODE DAW 29/01/00 //
//DEADCODE DAW 29/01/00 //////////////////////////////////////////////////////////////////////
//DEADCODE DAW 29/01/00 void Atmosphere::SetMissionPress (SWord month)
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	FP delta;
//DEADCODE DAW 29/01/00 	delta = month - 6;
//DEADCODE DAW 29/01/00 	if (delta < 0)
//DEADCODE DAW 29/01/00 		delta = - delta;
//DEADCODE DAW 29/01/00 	if (delta < 3)
//DEADCODE DAW 29/01/00 	{//Summer
//DEADCODE DAW 29/01/00 		Press0 = 1001 + TempVar;
//DEADCODE DAW 29/01/00 	}else
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		Press0 = 999 - TempVar;
//DEADCODE DAW 29/01/00 	}
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	ContrailBandCentre = FEET2CM(32000);		//CSB 10/06/99	
//DEADCODE DAW 29/01/00 	ContrailBandWidth = FEET2CM(4000);	//CSB 10/06/99	
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	FP ChanceBad = 0.5 + 0.5 * FCos(month * 6.2831853 / 12.0);		//CSB 02/07/99	
//DEADCODE DAW 29/01/00 	ChanceBad = 819.2 + 8192.0 * ChanceBad;						//CSB 02/07/99	
//DEADCODE DAW 29/01/00 	if(Math_Lib.rnd() > ChanceBad)									//CSB 02/07/99	
//DEADCODE DAW 29/01/00 //DeadCode CSB 02/07/99		if (Press0 > 1000)
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		Conditions = 0;
//DEADCODE DAW 29/01/00 		Visibility = 4000000;
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	}
//DEADCODE DAW 29/01/00 	else
//DEADCODE DAW 29/01/00 	{
//DEADCODE DAW 29/01/00 		Visibility = 4000000;			//##lower vis possible here
//DEADCODE DAW 29/01/00 		if (Temp0 < 273)
//DEADCODE DAW 29/01/00 			Conditions = 2;
//DEADCODE DAW 29/01/00 		else
//DEADCODE DAW 29/01/00 			Conditions = 1;
//DEADCODE DAW 29/01/00 	}
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	if (		(Press0 < 980)
//DEADCODE DAW 29/01/00 			&&	(MMC.currtime <  HR09)
//DEADCODE DAW 29/01/00 		)
//DEADCODE DAW 29/01/00 		MistInValley = true;
//DEADCODE DAW 29/01/00 	else
//DEADCODE DAW 29/01/00 		MistInValley = false;
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 //this will be a function of temp and press
//DEADCODE DAW 29/01/00 	CloudLayer = 457200;
//DEADCODE DAW 29/01/00 }
//DEADCODE DAW 29/01/00 void Atmosphere::SetMissionConditions ()
//DEADCODE DAW 29/01/00 {
//DEADCODE DAW 29/01/00 	FCRD wind_at_zero, wind_at_alt;
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00   	SWord	month = 0;
//DEADCODE DAW 29/01/00 	SWord	day = 0,year = 0;
//DEADCODE DAW 29/01/00 	Math_Lib.DateFromSecs (MMC.currdate, day,month,year);
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	SetMissionTemp (month);
//DEADCODE DAW 29/01/00 	SetMissionPress (month);
//DEADCODE DAW 29/01/00 	SetMissionDensity();
//DEADCODE DAW 29/01/00 	SetMissionClouds();
//DEADCODE DAW 29/01/00 
//DEADCODE DAW 29/01/00 	SetMissionWind(month);
//DEADCODE DAW 29/01/00  
//DEADCODE DAW 29/01/00 	SWord Latitude = 38;
//DEADCODE DAW 29/01/00 	SetMissionDawnDusk(Latitude, MMC.currdate, MMC.dawntime, MMC.dusktime);
//DEADCODE DAW 29/01/00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Ambient
//Author		Andrew McRae
//Date			Mon 13 Jan 1997
//
//Description	Calculates atmospheric density, temperature and pressure at 
//				an altitude
//
//Inputs		height above sea level
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Atmosphere::Ambient (FP ypos, FP& density, FP& temp, FP& pres)
{
	if (ypos < 0) ypos = 0;

	FP TempRatio = 1 - 0.00000023064 * ypos;
	if(ypos < 1100000) 	temp = TempRatio * 288.15;
	else				temp = 216.61;

	temp += (Temp0 - 288.15);

	density = Density0 * pow(TempRatio, 4.14);

	pres = density * 287 * temp;

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWindDirVel
//Author		Craig Beeston
//Date			Thu 10 Jun 1999
//
//Description	Returns the wind speed and direction at a given altitude
//
//Inputs		Alt
//
//Returns		Wind Heading and Speed
//
//------------------------------------------------------------------------------
Bool Atmosphere::GetWindDirVel (SLong alt, SWord& hdg, SLong& speed)
{
	if(!Save_Data.flightdifficulty [FD_WINDEFFECTS])
	{
		hdg = 0;
		speed = 0;
		return(TRUE);
	}

	if(alt > 914400)	// 30,000 ft
	{
		hdg	  = SWord(diralt * 182.04);
//DeadCode RJS 16Dec99		speed = (51 * windalt) / 10;
		speed = SLong(5148. * windalt);					//RJS 16Dec99
		return(TRUE);
	}

//DeadCode RJS 16Dec99	SWord Dir0   = SWord(182.04 * dir0);
//DeadCode RJS 16Dec99	SWord DirAlt = SWord(182.04 * diralt);
//DeadCode RJS 16Dec99
//DeadCode RJS 16Dec99	SWord DeltaDir = DirAlt - Dir0;
	FP Dir0   = 182.04 * dir0;							//RJS 16Dec99
	FP DirAlt = 182.04 * diralt;						//RJS 16Dec99

	FP DeltaDir = DirAlt - Dir0;						//RJS 16Dec99
	FP Fract = FP(alt) / 914411.0;
	FP fdir   = Dir0 + Fract * DeltaDir;
	FP fspeed = ((1. - Fract) * wind0 + Fract * windalt) * 5148.;//RJS 16Dec99

	hdg   = SWord(fdir);
	speed = SLong(fspeed);
	
	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWindDirVel
//Author		Robert Slater
//Date			Thu 16 Dec 1999
//
//Description	Returns the wind speed and direction at a given altitude
//
//Inputs		Alt
//
//Returns		Wind Heading and Speed
//
//------------------------------------------------------------------------------
void Atmosphere::GetWindDirVel (SLong alt, SWord& hdg, FP& speed)
{
	if(!Save_Data.flightdifficulty [FD_WINDEFFECTS])
	{
		hdg = 0;
		speed = 0;
	}
	else
	{
		if(alt > 914400)	// 30,000 ft
		{
			hdg	  = SWord(diralt * 182.04);
			speed = 5148. * windalt;	//from knotts... to vel*1000
		}
		else
		{
			FP Dir0   = 182.04 * dir0;
			FP DirAlt = 182.04 * diralt;
			FP DeltaDir = DirAlt - Dir0;
			FP Fract = FP(alt) / 914411.0;
			FP fdir   = Dir0 + Fract * DeltaDir;
			
			speed = ((1. - Fract) * wind0 + Fract * windalt) * 5148.;
			hdg   = SWord(fdir);
		}
	}
}
//DEADCODE CB 29/10/99 {
//DEADCODE CB 29/10/99 	if(!Save_Data.flightdifficulty [FD_WINDEFFECTS])
//DEADCODE CB 29/10/99 	{
//DEADCODE CB 29/10/99 		hdg = 0;
//DEADCODE CB 29/10/99 		speed = 0;
//DEADCODE CB 29/10/99 		return(TRUE);
//DEADCODE CB 29/10/99 	}
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	if(alt < 1036300)	// 34,000 ft 
//DEADCODE CB 29/10/99 	{
//DEADCODE CB 29/10/99 		hdg	  = SWord(dir0 * 182.04);
//DEADCODE CB 29/10/99 		speed = 0;//wind0;
//DEADCODE CB 29/10/99 		return(TRUE);
//DEADCODE CB 29/10/99 	}
//DEADCODE CB 29/10/99 	
//DEADCODE CB 29/10/99 	if(alt > 1066800)	// 35,000 ft
//DEADCODE CB 29/10/99 	{
//DEADCODE CB 29/10/99 		hdg	  = SWord(diralt * 182.04);
//DEADCODE CB 29/10/99 		speed = (51 * windalt) / 10;
//DEADCODE CB 29/10/99 		return(TRUE);
//DEADCODE CB 29/10/99 	}
//DEADCODE CB 29/10/99 	
//DEADCODE CB 29/10/99 	SWord Dir0   = SWord(182.04 * dir0);
//DEADCODE CB 29/10/99 	SWord DirAlt = SWord(182.04 * diralt);
//DEADCODE CB 29/10/99 
//DEADCODE CB 29/10/99 	SWord DeltaDir = DirAlt - Dir0;
//DEADCODE CB 29/10/99 	FP Fract = (alt - 1036300.0) / (1066800.0 - 1036300.0);
//DEADCODE CB 29/10/99 	FP fdir   = Dir0 + Fract * DeltaDir;
//DEADCODE CB 29/10/99 	FP fspeed = Fract * windalt * 5.1;
//DEADCODE CB 29/10/99 	hdg   = SWord(fdir);
//DEADCODE CB 29/10/99 	speed = SWord(fspeed);
//DEADCODE CB 29/10/99 	
//DEADCODE CB 29/10/99 	return(TRUE);
//DEADCODE CB 29/10/99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWind
//Author		Andrew McRae
//Date			Thu 10 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

// for contrails
FP Atmosphere::GetWind (SLong height, SLong& x, SLong& y, SLong& z)
{
	if (Save_Data.flightdifficulty [FD_WINDEFFECTS])
	{
		SWord	dir;
		FP		vel;												//RJS 16Dec99
		GetWindDirVel(height, dir, vel);
		if(!vel)
		{
			x = y = z = 0;
		}
		else
		{
			Float sin, cos;
	
			Math_Lib.high_sin_cos((Angles)dir, sin, cos);
			x = -vel * sin;
			y = 0;
			z = -vel * cos;

			return vel;
		}
	}
	else
	{
		x = 0;
		y = 0;
		z = 0;
	}
	return 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetWind
//Author		Andrew McRae   
//Date			Thu 2 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Atmosphere::GetWind (AirStrucPtr const ControlledAC, FCRD& wind, FP height)
{
	PMODEL pModel = ControlledAC->fly.pModel;

	if (Save_Data.flightdifficulty [FD_WINDEFFECTS])
	{
		SLong wx, wy ,wz;
		GetWind(pModel->Pos.y, wx, wy, wz);	//CSB 10/06/99	
		wind.x = wx * 0.0001;
		wind.y = wy * 0.0001;
		wind.z = wz * 0.0001;
	}
	else
	{
		NullVec(wind);
		NullVec(pModel->Gust.Vec);
		pModel->Gust.ACTIVE = FALSE;
	}

	if (Save_Data.flightdifficulty [FD_WINDGUSTS])
	{
		if (pModel->Gust.ACTIVE)
		{
			wind.x += pModel->Gust.Vec.x;		
			wind.y += pModel->Gust.Vec.y;		
			wind.z += pModel->Gust.Vec.z;

			// terminate ??
			pModel->Gust.Time -= (SWord)Timer_Code.FRAMETIME;
			if (pModel->Gust.Time <= 0)
			{
				pModel->Gust.ACTIVE = FALSE;
				pModel->Gust.Time = 0;
				NullVec(pModel->Gust.Vec);

				// Restore default gust...						//RJS 08Apr98
//??				MMC.Sky.SetGusts (25, 125, 3, 7, 56000);			//RJS 08Apr98
			}
		}
		else
		{
		// start a new gust ??
			if ((UWord)Math_Lib.rnd () >= Frequency)
			{
				// make new gust
				// magnitude and direction
				FP magscale = ((FP)(UWord)Math_Lib.rnd() / 65536);
				FP mag = MinMagnitude + ((MaxMagnitude - MinMagnitude) * magscale);
				pModel->Gust.Vec.x = mag * ((FP)Math_Lib.rnd() - 32768) / 32768;	//CSB 23/12/98
				pModel->Gust.Vec.y = mag * ((FP)Math_Lib.rnd() - 32768) / 32768;	//CSB 23/12/98
				pModel->Gust.Vec.z = mag * ((FP)Math_Lib.rnd() - 32768) / 32768;	//CSB 23/12/98
				// duration
				pModel->Gust.Time = MinDuration +
					(SWord)(((ULong)(MaxDuration - MinDuration) * (ULong)Math_Lib.rnd()) >> 16);
				// set active
				pModel->Gust.ACTIVE = TRUE;
			}
		}
	}
	else 
		NullVec(pModel->Gust.Vec);

	return TRUE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetGusts
//Author		Andrew McRae
//Date			Thu 10 Apr 1997
//
//Description	Initialise Atmosphere Gusts
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------ 
void Atmosphere::SetGusts (SWord mindur, SWord maxdur, FP minmag, FP maxmag, UWord freq)
{
	MinDuration = mindur;
	MaxDuration = maxdur;
	MinMagnitude = minmag;
	MaxMagnitude = maxmag;
	Frequency = freq;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMissionDawnDusk
//Author		Craig Beeston
//Date			Tue 15 Dec 1998
//
//Description	Sets the dawn and dusk times based on the lattitude and the date
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------ 
void Atmosphere::SetMissionDawnDusk (SWord Latitude, ULong Date, SLong& Dawn, SLong& Dusk)
{
	ULong SecsPerDay = 24 * 60 * 60;
	UWord Hours6 = SecsPerDay / 4;

	ULong SecsPerYear = 365 * SecsPerDay;
	while(Date > SecsPerYear) Date -= SecsPerYear;

	FP DeltaTime = 2 * FPIE * ((float)Date + 9.5 * (float)SecsPerDay) / (float)SecsPerYear;
	DeltaTime  = FCos(DeltaTime);
	DeltaTime *= (90 - 23);
	DeltaTime /= 90;
	DeltaTime *= FSin(Degs2Rads(Latitude));
	DeltaTime /= FCos(Degs2Rads(Latitude));
	DeltaTime *= FSin(Degs2Rads(23));
	DeltaTime *= Hours6;
	DeltaTime += Hours6;

	FP fDawn = DeltaTime;
	FP fDusk = SecsPerDay - fDawn;

	if(fDawn < 0)
	{
		fDawn = 0;
		fDusk = SecsPerDay;
	}

	if(fDusk > SecsPerDay)
	{
		fDawn = SecsPerDay / 2;
		fDusk = SecsPerDay / 2;
	}
	Dawn = (int)fDawn;
	Dusk = (int)fDusk;

#pragma warnmsg("***** DAWN AND DUSK FAKED **** //CSB 20/04/00")
//DeadCode JON 29Sep00 	Dawn = 18000;	//5 am
//DeadCode JON 29Sep00 	Dusk = 79200;	//10 pm
	Dawn = 7*60*60; // 7am
	Dusk = (10+12)*60*60; // 10pm

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Contrails
//Author		Andrew McRae
//Date			Thu 2 Apr 1998
//
//Description	duration in csecs
//				The centre of the contrail layer is set for all aircraft using SetContrails

//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool Atmosphere::Contrails (AirStrucPtr ac, ULong& duration)
{
	Bool	isactive = FALSE;

	duration = 0;

	if (ac && (ac->Status.size == AirStrucSize))								//RJS 08Apr98
	{
		PMODEL pModel = ac->fly.pModel;
		if (pModel)
		{
			FP deviation = (pModel->AmbTemp - 220) * 1500;
			deviation = 0;	//CSB 11/06/99	

			FP MinHeight = ContrailBandCentre - (ContrailBandWidth * 0.5) + deviation;//DAW 28Apr98
			FP MaxHeight = ContrailBandCentre + (ContrailBandWidth * 0.5) - deviation;//DAW 28Apr98


			if	((ac->World.Y <= MaxHeight) && (ac->World.Y >= MinHeight))
			{
				FP time =  (ac->World.Y - MinHeight) * (MaxHeight - ac->World.Y);
				time 	*= 0.000002691 * pModel->ContrailDuration;

				if (time > MAXIMUM_CONTRAIL_DURATION)
					time = MAXIMUM_CONTRAIL_DURATION;

				duration = (ULong)time;
				isactive = TRUE;
			}
		}
	}

	return isactive;
}


void Cloud::NullCloud()
{
	AltBase = 0;
	AltTop  = 0;
	Cover   = 0;
}


void Cloud::SetCloud(SLong base, SLong top, UByte cover)
{
	if((cover == 0) || (top <= base))
		NullCloud();
	else
	{
		AltBase = base;
		AltTop  = top;
		Cover   = cover;
	}
}
