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
//Filename       smktrls.cpp
//System         
//Author         Robert Slater
//Date           Wed 9 Feb 2000
//Description    
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//				           INCLUDE FILES
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴


	#include	"DOSDefs.h"
	//#include	"MAClib.h"f
#define F_GRAFIX												//DAW 05Aug96
//DeadCode RJS 17Oct96 #define F_SOUNDS
#define F_BATTLE
	#include 	"myerror.h"
	#include 	"Palette.h"
	#include	"myAngles.h"
	#include	"Worldinc.h"

	#include	"3DDefs.h"
	#include	"3DCom.h"	 
#define MATRIX_CODE_REQ
	#include	"Matrix.h"
	#include	"polygon.h"										//RJS 02Dec97
	#include "fastmath.h"

	#include	"mymath.h"										//RJS 25Jul96
	#include	"viewsel.h"										//RJS 30Aug96
	#include "ranges.h"
	#include	"speed.h"										//RJS 01Oct96
	#include	"shpinstr.h"									//RJS 03Jul98
	#include	"modinst.h"										//RJS 03Jul98
	#include	"imagemap.g"
	#include	"imagemap.h"
	#include	"viewsel.h"
	#include	"smktrls.h"

TrailInfo	Smoke_Trails;

void	TrailInfo::SetViewPoint(ViewPoint*	vpnt)
{
	vp = vpnt;
}

void	TrailInfo::SetVisibility(float	fdx, float fdy, float fdz, float linelen)
{
}

void	TrailInfo::CalcCylinder()
{
	flipped = false;

	if (wasLine)
	{
		g_lpLib3d->CylinderOffsets(newco[0],newco[0],radius,xoff1,yoff1,dpbacktrans);

		xoff1 = yoff1 = 0;
		wasLine = false;
	}

	xoff0 = xoff1;
	yoff0 = yoff1;

	dpfronttrans = dpbacktrans;

	g_lpLib3d->CylinderOffsets(dpfronttrans,newco[1],radius,xoff1,yoff1,dpbacktrans);

	if (traillength)
	{
		// Assume 90 degree FoV cos it's better than nothing...
		float	fscr_z = 1./dpfronttrans.getPosZ();
		float	bscr_z = 1./dpbacktrans.getPosZ();
		float	fscr_x = dpfronttrans.getPosX()*fscr_z;
		float	fscr_y = dpfronttrans.getPosY()*fscr_z;
		float	bscr_x = dpbacktrans.getPosX()*bscr_z;
		float	bscr_y = dpbacktrans.getPosY()*bscr_z;
		float	av_z = (fscr_z + bscr_z)*.5;
		float	scaletrail = float(traillength)*av_z;
		float	dsx = fscr_x-bscr_x;
		float	dsy = fscr_y-bscr_y;
 		float	linescale;
 
		linescale = (fastMath.FastSqrt(dsx*dsx+dsy*dsy)*100.0) / scaletrail;

		fastMath.FloatToInt(&visibility,linescale);
		
/*		SLong	cylobscur;
		fastMath.FloatToInt(&cylobscur,radius);

		cylobscur = (traillength<<16)/cylobscur;

		visibility = (visibility*cylobscur)>>16;*/
	}
}

void	TrailInfo::DuffButNecessary()
{
	wasLine = true;
}	

void	TrailInfo::Init()
{
	g_lpLib3d->CylinderOffsets(newco[0],newco[0],radius,xoff1,yoff1,dpbacktrans);
	g_lpLib3d->CylinderOffsets(dpbacktrans,newco[1],radius,xoff1,yoff1,dpfronttrans);

	wasLine = false;
}

void	TrailInfo::CheckNearest()
{
#ifndef _REDO_ME2_
	if (dpbacktrans.getPosZ() > dpfronttrans.getPosZ())
	{						
		flipped = true;
		
		bak_vertex0 = vertex0;
		bak_vertex1 = vertex1;

		bak_WCylStartP=WCylStartP;
		bak_WCylEndP=WCylEndP;

		bak_xoff0=xoff0;
		bak_yoff0=yoff0;

		bak_xoff1=xoff1;
		bak_yoff1=yoff1;

		bak_oldradius=oldradius;
		bak_radius=radius;

		bak_dpfronttrans = dpfronttrans;
		bak_dpbacktrans = dpbacktrans;

		dpfronttrans = dpbacktrans;
		dpbacktrans = bak_dpfronttrans;

		vertex0 = vertex1;								
		vertex1 = bak_vertex0;								

		WCylStartP = WCylEndP;
		WCylEndP = bak_WCylStartP;

		xoff0 = xoff1;
		yoff0 = yoff1;

		xoff1 = bak_xoff0;
		yoff1 = bak_yoff0;

		oldradius = radius;
		radius = bak_oldradius;
	}
#endif
}

void	TrailInfo::Restore()
{
	if (flipped)
	{
		vertex0 = bak_vertex0;
		vertex1 = bak_vertex1;

		WCylStartP = bak_WCylStartP;
		WCylEndP = bak_WCylEndP;

		xoff0 = bak_xoff0;
		yoff0 = bak_yoff0;

		xoff1 = bak_xoff1;
		yoff1 = bak_yoff1;

		oldradius = bak_oldradius;
		radius = bak_radius;

		dpfronttrans = bak_dpfronttrans;
		dpbacktrans = bak_dpbacktrans;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleStreamImapd
//Author		Robert Slater
//Date			Thu 4 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TrailInfo::ParticleStreamImapd()
{
#ifndef _REDO_ME2_
	DoPointStruc dopointRoot;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	SWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius;
	ImageMapNumber imapno = (ImageMapNumber) imagemap0;				
	SWord	maxx, maxy;
	SLong	MaxRadius;											
	SLong	wXStep, wYStep, wZStep;								
	SLong	wXStart, wYStart, wZStart;							
	SLong	MaxDist, Dist;
	SLong	RadStep;
	ULong	thetime = 0;
	SLong	depth;
	SLong	StartRadius = oldradius;
	SLong	EndRadius = radius;
	DoPointStruc sphco;
const	int	shiftFactor = 8;												//RJS 30Jun00
	
	MaxRadius = StartRadius<<shiftFactor;									//RJS 30Jun00

	wXStart = WCylStartP->gx;									
	wYStart = WCylStartP->gy;									
	wZStart = WCylStartP->gz;

	dopointRoot = dpfronttrans;								

	RelX = dpbacktrans.getPosX() - dpfronttrans.getPosX();
	RelY = dpbacktrans.getPosY() - dpfronttrans.getPosY();
	RelZ = dpbacktrans.getPosZ() - dpfronttrans.getPosZ();

	if (traillength)
	{
		SLong	avradius = (StartRadius + EndRadius)>>1;

		avradius++;												

		// max depth...
		depth = traillength / avradius;							
		depth <<= 7;											
		depth /= distance;									
		if (depth <= 0)	depth = 1;								

		RadStep = ((EndRadius - StartRadius)<<shiftFactor)/depth;		//RJS 30Jun00

		wXStep = (WCylEndP->gx - wXStart) / depth;					
		wYStep = (WCylEndP->gy - wYStart) / depth;					
		wZStep = (WCylEndP->gz - wZStart) / depth;					

		if (vp)		thetime = vp->TimeOfDay();

		wXStart += thetime;									
		wYStart += thetime;									
		wZStart += thetime;

		XoffGap = (xoff1 - xoff0)/depth;
		YoffGap = (yoff1 - yoff0)/depth;

		RelX /= depth;
		RelY /= depth;
		RelZ /= depth;

		xDelta = xoff0;
		yDelta = yoff0;

		for (counter = 0; counter < depth; counter++)
		{
			RSeed = SHAPE.Noise(wXStart,wYStart,wZStart);

			RandxDelta = RSeed*xDelta;
			RandxDelta >>= 7;
			RandxDelta -= xDelta;
			RandxDelta >>= 2;

			RandyDelta = RSeed*yDelta;
			RandyDelta >>= 7;
			RandyDelta -= yDelta;
			RandyDelta >>= 2;

			sphco = dopointRoot;
//DEADCODE JON 5/22/00 			sphco.incPosX( RandxDelta ); 
//DEADCODE JON 5/22/00 			sphco.incPosY( RandyDelta );
			sphco.incPos( RandxDelta, RandyDelta, 0.0 );

			RSeed -= 128;
			RSeed = (RSeed<0)?-RSeed:RSeed;
			RSeed = 128 - RSeed;

			Radius = MaxRadius * RSeed;
			Radius >>= 8;
			Radius += (MaxRadius >> 1);
			Radius >>= shiftFactor;

//Draw a sphere...
			g_lpLib3d->DrawTransformedSphere(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),sphco,Radius,ANGLES_0Deg,minix0,miniy0,maxix0,maxiy0);//RJS 20Mar00

//DEADCODE JON 5/22/00 			dopointRoot.bodyx.f += RelX;
//DEADCODE JON 5/22/00 			dopointRoot.bodyy.f += RelY;
//DEADCODE JON 5/22/00   			dopointRoot.bodyz.f += RelZ;
			dopointRoot.incPos( RelX, RelY, RelZ );

			xDelta += XoffGap;
			yDelta += YoffGap;

			wXStart += wXStep;
			wYStart += wYStep;
			wZStart += wZStep;

			MaxRadius += RadStep;
		}

		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ParticleCylinderImapd
//Author		Robert Slater
//Date			Thu 4 Dec 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TrailInfo::ParticleCylinderImapd()
{
#ifndef _REDO_ME2_
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,dopointRoot,dptmp1,dptmp2;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	UWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius, Radius3d;
	ImageMapNumber imapno = (ImageMapNumber) imagemap0;				
	SWord	maxx, maxy;
	SLong	MaxRadius = maxradius;
	SWord	HalfRadius = MaxRadius>>1;							
	SLong	wXStep, wYStep, wZStep;								
	SLong	wXStart, wYStart, wZStart;							
	SLong	MaxDist, Dist;										
	SLong	depth;												
	DoPointStruc	sphco;

	wXStart = WCylStartP->gx;									
	wYStart = WCylStartP->gy;									
	wZStart = WCylStartP->gz;									

	dopointRoot = dpfronttrans;									//RJS 20Mar00
	dopoint2 = dpbacktrans;										//RJS 20Mar00

	RelX = dopoint2.getPosX() - dopointRoot.getPosX();
	RelY = dopoint2.getPosY() - dopointRoot.getPosY();
	RelZ = dopoint2.getPosZ() - dopointRoot.getPosZ();

	if (traillength)
	{
		Float	fDepth;

		depth = (traillength*pixpercyl) / HalfRadius;
		depth >>= 15;
		if (depth <= 0)	depth = 1;

		fDepth = 1. / Float(depth);

		wXStep = (WCylEndP->gx - wXStart) / depth;
		wYStep = (WCylEndP->gy - wYStart) / depth;
		wZStep = (WCylEndP->gz - wZStart) / depth;

		XoffGap = (xoff1 - xoff0)/depth;
		YoffGap = (yoff1 - yoff0)/depth;

		RelX *= fDepth;
		RelY *= fDepth;
		RelZ *= fDepth;

		xDelta = xoff0;
		yDelta = yoff0;

		for (counter = 0; counter < depth; counter++)
		{
			xDeltCap = xDelta << 1;
			yDeltCap = yDelta << 1;

			RSeed = SHAPE.Noise(wXStart,wYStart,wZStart);

			RandxDelta = RSeed * xDeltCap;
			RandxDelta >>= 8;
			RandxDelta -= xDelta;

			RandyDelta = RSeed * yDeltCap;
			RandyDelta >>= 8;
			RandyDelta -= yDelta;

			sphco = dopointRoot;
//DEADCODE JON 5/22/00 			sphco.bodyx.f += RandxDelta;
//DEADCODE JON 5/22/00 			sphco.bodyy.f += RandyDelta;
			sphco.incPos( RandxDelta, RandyDelta, 0.0 );				//RJS 6Jun00


			xDeltCap >>= 1;
			yDeltCap >>= 1;
			xDeltCap = (xDeltCap<0)?-xDeltCap:xDeltCap;
			yDeltCap = (yDeltCap<0)?-yDeltCap:yDeltCap;

			if (xDeltCap || yDeltCap)
			{
				if (xDeltCap > yDeltCap)
				{
					MaxDist = xDeltCap;
					Dist = (RandxDelta<0)?-RandxDelta:RandxDelta;
				}
				else
				{
					MaxDist = yDeltCap;
					Dist = (RandyDelta<0)?-RandyDelta:RandyDelta;
				}

				Dist = MaxDist - Dist;

				Radius = 2 + ((Dist*MaxRadius)/MaxDist);
	
				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,(Radius*255)/MaxRadius);
				g_lpLib3d->DrawTransformedSphere(HMATERIAL(Image_Map.GetImageMapPtr(imapno)),sphco,Radius,ANGLES_0Deg,minix0,miniy0,maxix0,maxiy0);
			}


//DEADCODE JON 5/22/00 			dopointRoot.bodyx.f += RelX;
//DEADCODE JON 5/22/00 			dopointRoot.bodyy.f += RelY;
//DEADCODE JON 5/22/00   			dopointRoot.bodyz.f += RelZ;
			dopointRoot.incPos( RelX, RelY, RelZ );


			xDelta += XoffGap;
			yDelta += YoffGap;

			wXStart += wXStep;										//RJS 12Nov97
			wYStart += wYStep;										//RJS 12Nov97
			wZStart += wZStep;										//RJS 12Nov97
		}

		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		imaptrailcylWrapped
//Author		Robert Slater
//Date			Tue 17 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void TrailInfo::imaptrailcylWrapped()
{
#ifndef _REDO_ME2_
	ULong	thewidth, theheight;
	DoPointStruc dopoint0,dopoint1,dopoint2,dopoint3,oldpoint,sphco;
//DeadCode RJS 20Oct00  	Float	xdelt1 = (Float) xoff0;
//DeadCode RJS 20Oct00  	Float	ydelt1 = (Float) yoff0;
//DeadCode RJS 20Oct00  	Float	xdelt2 = (Float) xoff1;
//DeadCode RJS 20Oct00  	Float	ydelt2 = (Float) yoff1;
 	Bool	oldcross;
	SLong	nopixels;
	SLong	dx,dy,dz;
	Bool	dosphere = FALSE;
	Bool	nocyl = FALSE;

  	ImageMapDescPtr imptr = Image_Map.GetImageMapPtr((ImageMapNumber)imagemap0);
	minix0 = 0;
	maxix0 = imptr->w;
 
   	dopoint0 = dopoint1 = dpfronttrans;							//RJS 20Mar00
   	oldpoint = dopoint2 = dopoint3 = dpbacktrans;				//RJS 20Mar00

	if (traillength)
	{
		dx = dopoint0.getPosX() - dopoint2.getPosX();
		dy = dopoint0.getPosY() - dopoint2.getPosY();
		dz = dopoint0.getPosZ() - dopoint2.getPosZ();

		// Assume 1 pixel is 8 cm...

		nopixels = traillength >> 3;
		nopixels = nopixels / maxix0;
		if (nopixels)
			maxix0 = maxix0 * nopixels;

		if (visibility > 4)				//4% visible
		{
			if (visibility < 75)			//75%
				dosphere = TRUE;
		}
		else
		{
			nocyl = TRUE;
			dosphere = TRUE;
		}

		if (!nocyl)
			g_lpLib3d->DrawTransformedCylinder(HMATERIAL(imptr),dpfronttrans,dpbacktrans,xoff0,yoff0,xoff1,yoff1,minix0,miniy0,maxix0,maxiy0);

		if (dosphere && imagemap1)
		{
//DeadCode RJS 20Oct00 			SLong	pooradius = 0.75*radius;
/*			if (pooradius)
			{
				int		nospheres = 1 + ((pixpercyl * visibility)>>8);
				int	i;
				Float	dxpoo,dypoo,dzpoo;

				dxpoo = Float(dx);
				dypoo = Float(dy);
				dzpoo = Float(dz);

				if (nospheres > 8)
					nospheres = 8;
				
				dxpoo /= nospheres;
				dypoo /= nospheres;
				dzpoo /= nospheres;

				sphco = oldpoint;

				for (i=0; i < nospheres; i++)
				{
					g_lpLib3d->DrawSphere(HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber)imagemap1)),sphco,radius,ANGLES_0Deg,minix1,miniy1,maxix1,maxiy1);

					sphco.bodyx.f += dxpoo;
					sphco.bodyy.f += dypoo;
					sphco.bodyz.f += dzpoo;
				}
			}*/

			g_lpLib3d->DrawTransformedSphere(HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber)imagemap1)),dpbacktrans,radius,ANGLES_0Deg,minix1,miniy1,maxix1,maxiy1);//RJS 20Mar00
		}
	}
	else
	{
		if (imagemap1)
		{
			sphco = oldpoint;

//DEADCODE JON 5/22/00 			sphco.bodyx.f = (dopoint0.bodyx.f + dopoint2.bodyx.f)/2;
//DEADCODE JON 5/22/00 			sphco.bodyy.f = (dopoint0.bodyy.f + dopoint2.bodyy.f)/2;
//DEADCODE JON 5/22/00 			sphco.bodyz.f = (dopoint0.bodyz.f + dopoint2.bodyz.f)/2;
//			D3DVALUE tx, ty, tz;
//			tx = ( dopoint0.getPosX() + dopoint2.getPosX() )/2;
//			ty = ( dopoint0.getPosY() + dopoint2.getPosY() )/2;
//			tz = ( dopoint0.getPosZ() + dopoint2.getPosZ() )/2;
			sphco.setPosition( 
				( dopoint0.getPosX() + dopoint2.getPosX() )/2,//tx, 
				( dopoint0.getPosY() + dopoint2.getPosY() )/2,//ty, 
				( dopoint0.getPosZ() + dopoint2.getPosZ() )/2//tz 
				);

			g_lpLib3d->DrawTransformedSphere(HMATERIAL(Image_Map.GetImageMapPtr((ImageMapNumber)imagemap1)),sphco,radius,ANGLES_0Deg,minix1,miniy1,maxix1,maxiy1);
		}
	}
#endif
}

Bool	shape::ClipSphereRatio(	DoPointStruc	&dp0,
								DoPointStruc	&dp1,
								DoPointStruc	&dp2,
								DoPointStruc	&dp3,
								SLong			Radius,
								SWord			wx,
								SWord			wy,
								bool			ispivoted	)
{
	return FALSE;
/*
	Bool	Clipped = TRUE;
	Float	Radx = Float(Radius);
	Float	Rady;
	SLong	ratio = (wy << 16)/wx;
	SLong	rady;


	rady = (Radius * ratio);

	Radx *= SphereXScale;
	if (ispivoted)
	{
		rady >>= 15;
		Rady = Float(rady);
		Rady *= SphereYScale;

//DeadCode RJS 26May99 		if (vp->PolyPitEnabled() || (vp->viewnum.viewmode == VM_InsideCheat))
		if (vp->roll)									//RJS 26May99
		{
			SWord 	sinAng,cosAng;
			SLong	x0,x1,x2,x3;
			SLong	y0,y1,y2,y3;
			SLong 	m[4];
			SLong	nx,ny;
			SWord	angle = vp->roll;


			x0 = -Radx;
			y0 = Rady;

			x1 = Radx;
			y1 = Rady;

			x2 = Radx;
			y2 = 0;

			x3 = -Radx;
			y3 = 0;

			Math_Lib.high_sin_cos((Angles)angle,sinAng,cosAng);

			m[0]=m[3]=SLong(cosAng);
			m[1]=SLong(sinAng);
			m[2]=-SLong(sinAng);

			nx=(m[0]*x0)/ANGLES_FRACT+(m[1]*y0)/ANGLES_FRACT;
			ny=(m[2]*x0)/ANGLES_FRACT+(m[3]*y0)/ANGLES_FRACT;

			x0 = nx;
			y0 = ny;

			nx=(m[0]*x1)/ANGLES_FRACT+(m[1]*y1)/ANGLES_FRACT;
			ny=(m[2]*x1)/ANGLES_FRACT+(m[3]*y1)/ANGLES_FRACT;

			x1 = nx;
			y1 = ny;

			nx=(m[0]*x2)/ANGLES_FRACT+(m[1]*y2)/ANGLES_FRACT;
			ny=(m[2]*x2)/ANGLES_FRACT+(m[3]*y2)/ANGLES_FRACT;

			x2 = nx;
			y2 = ny;

			nx=(m[0]*x3)/ANGLES_FRACT+(m[1]*y3)/ANGLES_FRACT;
			ny=(m[2]*x3)/ANGLES_FRACT+(m[3]*y3)/ANGLES_FRACT;

			x3 = nx;
			y3 = ny;

			dp0.bodyx.f += Float(x0);	
			dp0.bodyy.f += Float(y0);	
								
			dp1.bodyx.f += Float(x1);	
			dp1.bodyy.f += Float(y1);	
								
			dp2.bodyx.f += Float(x2);	
			dp2.bodyy.f += Float(y2);	
								
			dp3.bodyx.f += Float(x3);	
			dp3.bodyy.f += Float(y3);
		}
		else
		{
			dp0.bodyx.f -= Radx;						
			dp0.bodyy.f += Rady;						
																
			dp1.bodyx.f += Radx;						
			dp1.bodyy.f += Rady;						
																
			dp2.bodyx.f += Radx;						

			dp3.bodyx.f -= Radx;	
		}
	}
	else
	{
		rady >>= 16;
		Rady = Float(rady);
		Rady *= SphereYScale;

		dp0.bodyx.f -= Radx;						
		dp0.bodyy.f += Rady;						
																
		dp1.bodyx.f += Radx;						
		dp1.bodyy.f += Rady;						
																
		dp2.bodyx.f += Radx;						
		dp2.bodyy.f -= Rady;						

		dp3.bodyx.f -= Radx;						
		dp3.bodyy.f -= Rady;						
	}
																
	_matrix.SetClipFlags(dp0);
	_matrix.SetClipFlags(dp1);
	_matrix.SetClipFlags(dp2);
	_matrix.SetClipFlags(dp3);

	andedFlags=CF3D_ALL;
	andedFlags&=dp0.clipFlags;
	andedFlags&=dp1.clipFlags;
	andedFlags&=dp2.clipFlags;
	andedFlags&=dp3.clipFlags;
	if (andedFlags==0)
	{
		Clipped = FALSE;
		if (!doingHW3D)
		{
			_matrix.body2screen(dp0);
			_matrix.body2screen(dp1);
			_matrix.body2screen(dp2);
			_matrix.body2screen(dp3);
		}
	}

	return(Clipped);
	*/
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DblParticleCylinderImapd
//Author		Robert Slater
//Date			Mon 20 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TrailInfo::DblParticleCylinderImapd()
{
#ifndef _REDO_ME2_
	DoPointStruc dopoint2,dopointRoot;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	UWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius, Radius3d;
	ImageMapNumber imapdefaultno = (ImageMapNumber) imagemap0;
	ImageMapNumber imap2no = FIREFAD1NO;
	ImageMapNumber imapno;
	SWord	maxx, maxy;
	SWord	HalfRadius = maxradius*.5;
	SLong	wXStep, wYStep, wZStep;	  
	SLong	wXStart, wYStart, wZStart;
	SLong	MaxDist, Dist;			  
	SLong	depth;					  
	SWord	minx = minix0;
	SWord	miny = miniy0;
	DoPointStruc	sphco;

	maxx = maxix0;
	maxy = maxiy0;

	wXStart = WCylStartP->gx;
	wYStart = WCylStartP->gy;
	wZStart = WCylStartP->gz;

	dopointRoot = dpfronttrans;										
   	dopoint2 = dpbacktrans;

	SLong	subcounter;
	SLong	subincrement;
	SLong	subframe;

	RelX = dopoint2.getPosX() - dopointRoot.getPosX();
	RelY = dopoint2.getPosY() - dopointRoot.getPosY();
	RelZ = dopoint2.getPosZ() - dopointRoot.getPosZ();

	if (traillength)
	{
		SLong	subdepth;
		ImageMapDescPtr	imptr = Image_Map.GetImageMapPtr(imap2no);
		SLong	nofx = imptr->w / maxix1;
		SLong	stepy,stepx;
		SWord	text_minx[17];
		SWord	text_miny[17];
		SWord	text_maxx[17];
		SWord	text_maxy[17];

		for (int tmpframe=0; tmpframe < 16; tmpframe++)
		{
			stepy = tmpframe / nofx;
			stepx = tmpframe - (stepy*nofx);

			text_minx[tmpframe] = minix1 + (stepx*maxix1);
			text_miny[tmpframe] = miniy1 + (stepy*maxiy1);
			text_maxx[tmpframe] = text_minx[tmpframe] + maxix1;
			text_maxy[tmpframe] = text_miny[tmpframe] + maxiy1;
		}

		text_minx[16] = minx;
		text_miny[16] = miny;
		text_maxx[16] = maxx;
		text_maxy[16] = maxy;

		depth = (traillength*pixpercyl) / HalfRadius;
		depth >>= 15;							   
		if (depth <= 0)	depth = 1;				   

		subdepth = depth/3;
		if (flipped)
		{
			subcounter = depth;
			subincrement = -1;
		}
		else
		{
			subcounter = 0;
			subincrement = 1;
		}

		wXStep = (WCylEndP->gx - wXStart) / depth;
		wYStep = (WCylEndP->gy - wYStart) / depth;
		wZStep = (WCylEndP->gz - wZStart) / depth;

		XoffGap = (xoff1 - xoff0)/depth;
		YoffGap = (yoff1 - yoff0)/depth;

		Float	tmpdepth = 1. / Float(depth);
		RelX *= tmpdepth;
		RelY *= tmpdepth;
		RelZ *= tmpdepth;

		xDelta = xoff0;
		yDelta = yoff0;

		for (counter = 0; counter < depth; counter++)
		{
			xDeltCap = xDelta << 1;
			yDeltCap = yDelta << 1;

			RSeed = SHAPE.Noise(wXStart,wYStart,wZStart);
			
			RandxDelta = RSeed * xDeltCap;
			RandxDelta >>= 8;
			RandxDelta -= xDelta;

			RandyDelta = RSeed * yDeltCap;
			RandyDelta >>= 8;
			RandyDelta -= yDelta;

			sphco = dopointRoot;
//DEADCODE JON 5/22/00 			sphco.bodyx.f += RandxDelta;
//DEADCODE JON 5/22/00 			sphco.bodyy.f += RandyDelta;
			sphco.incPos( RandxDelta, RandyDelta, 0.0 );

			xDeltCap >>= 1;
			yDeltCap >>= 1;
			xDeltCap = (xDeltCap<0)?-xDeltCap:xDeltCap;
			yDeltCap = (yDeltCap<0)?-yDeltCap:yDeltCap;

			if (xDeltCap || yDeltCap)
			{
				if (xDeltCap > yDeltCap)
				{
					MaxDist = xDeltCap;
					Dist = (RandxDelta<0)?-RandxDelta:RandxDelta;
				}
				else
				{
					MaxDist = yDeltCap;
					Dist = (RandyDelta<0)?-RandyDelta:RandyDelta;
				}

				Dist = MaxDist - Dist;

				Radius = 2 + ((Dist*maxradius)/MaxDist);
	
				imapno = imapdefaultno;
				subframe = 16;
				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,(Radius*255)/maxradius);
				if (subcounter < subdepth)
				{
					RSeed = 255 - RSeed;
					RSeed *= subcounter;
					RSeed /= subdepth;

					if (RSeed < 32)
					{
						RSeed = SHAPE.Noise(wXStart+subcounter,wYStart+subcounter,wZStart+subcounter);
						RSeed = (RSeed*2)>>8;

						subframe = (12*subcounter)/subdepth;
						subframe += RSeed;
						imapno = imap2no;
					}
				}

				g_lpLib3d->DrawTransformedSphere(	HMATERIAL(Image_Map.GetImageMapPtr(imapno)),
										sphco,
										Radius,
										ANGLES_0Deg,
										text_minx[subframe],
										text_miny[subframe],
										text_maxx[subframe],
										text_maxy[subframe]	);
			}

//DEADCODE JON 5/22/00 			dopointRoot.bodyx.f += RelX;
//DEADCODE JON 5/22/00 			dopointRoot.bodyy.f += RelY;
//DEADCODE JON 5/22/00   			dopointRoot.bodyz.f += RelZ;

			dopointRoot.incPos( RelX, RelY, RelZ );


			xDelta += XoffGap;
			yDelta += YoffGap;

			wXStart += wXStep;
			wYStart += wYStep;
			wZStart += wZStep;

			subcounter += subincrement;
		}

		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FadeParticleCylinderImapd
//Author		Robert Slater
//Date			Mon 20 Dec 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	TrailInfo::FadeParticleCylinderImapd()
{
#ifndef _REDO_ME2_
	DoPointStruc sphco,dopoint2,dopointRoot;
 	Bool	oldcross;
	Float	RelX, RelY, RelZ;
	UWord	counter;
	SLong	xDelta,yDelta;
	SLong	RandxDelta,RandyDelta;
	SLong	xDeltCap,yDeltCap;
	UWord	RSeed;
	SLong	XoffGap;
	SLong	YoffGap;
	SLong	Radius, Radius3d;
	ImageMapNumber imapno = (ImageMapNumber)imagemap0;
	SWord	maxx, maxy;
	SWord	HalfRadius = maxradius*.5;
	SLong	wXStep, wYStep, wZStep;	  
	SLong	wXStart, wYStart, wZStart;
	SLong	MaxDist, Dist;			  
	SLong	depth;					  

	wXStart = WCylStartP->gx;
	wYStart = WCylStartP->gy;
	wZStart = WCylStartP->gz;

	dopointRoot = dpfronttrans;										
   	dopoint2 = dpbacktrans;

	SLong	subcounter;
	SLong	subincrement;

	RelX = dopoint2.getPosX() - dopointRoot.getPosX();
	RelY = dopoint2.getPosY() - dopointRoot.getPosY();
	RelZ = dopoint2.getPosZ() - dopointRoot.getPosZ();


	if (traillength)
	{
		SLong	realFade;

		depth = (traillength*pixpercyl) / HalfRadius;
		depth >>= 15;							   
		if (depth <= 0)	depth = 1;				   

		if (flipped)
		{
			subcounter = depth;
			subincrement = -1;
		}
		else
		{
			subcounter = 0;
			subincrement = 1;
		}

		wXStep = (WCylEndP->gx - wXStart) / depth;
		wYStep = (WCylEndP->gy - wYStart) / depth;
		wZStep = (WCylEndP->gz - wZStart) / depth;

		XoffGap = (xoff1 - xoff0)/depth;
		YoffGap = (yoff1 - yoff0)/depth;

		Float	tmpdepth = 1. / Float(depth);
		RelX *= tmpdepth;
		RelY *= tmpdepth;
		RelZ *= tmpdepth;

		xDelta = xoff0;
		yDelta = yoff0;

		for (counter = 0; counter < depth; counter++)
		{
			xDeltCap = xDelta << 1;
			yDeltCap = yDelta << 1;

			RSeed = SHAPE.Noise(wXStart,wYStart,wZStart);
			
			RandxDelta = RSeed * xDeltCap;
			RandxDelta >>= 8;
			RandxDelta -= xDelta;

			RandyDelta = RSeed * yDeltCap;
			RandyDelta >>= 8;
			RandyDelta -= yDelta;

			sphco = dopointRoot;
//DEADCODE JON 5/22/00 			sphco.bodyx.f += RandxDelta;
//DEADCODE JON 5/22/00 			sphco.bodyy.f += RandyDelta;
			sphco.incPos( RandxDelta, RandyDelta, 0.0 );

			xDeltCap >>= 1;
			yDeltCap >>= 1;
			xDeltCap = (xDeltCap<0)?-xDeltCap:xDeltCap;
			yDeltCap = (yDeltCap<0)?-yDeltCap:yDeltCap;

			if (xDeltCap || yDeltCap)
			{
				if (xDeltCap > yDeltCap)
				{
					MaxDist = xDeltCap;
					Dist = (RandxDelta<0)?-RandxDelta:RandxDelta;
				}
				else
				{
					MaxDist = yDeltCap;
					Dist = (RandyDelta<0)?-RandyDelta:RandyDelta;
				}

				Dist = MaxDist - Dist;

				Radius = 2 + ((Dist*maxradius)/MaxDist);
	
				realFade = (Radius*255)/maxradius;
				realFade = (realFade*subcounter)/depth;

				g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,realFade);
				g_lpLib3d->DrawTransformedSphere(	HMATERIAL(Image_Map.GetImageMapPtr(imapno)),
										sphco,
										Radius,
										ANGLES_0Deg,
										minix0,
										miniy0,
										maxix0,
										maxiy0	);
			}

//DEADCODE JON 5/22/00 			dopointRoot.bodyx.f += RelX;
//DEADCODE JON 5/22/00 			dopointRoot.bodyy.f += RelY;
//DEADCODE JON 5/22/00   			dopointRoot.bodyz.f += RelZ;

			dopointRoot.incPos( RelX, RelY, RelZ );

			xDelta += XoffGap;
			yDelta += YoffGap;

			wXStart += wXStep;
			wYStart += wYStep;
			wZStart += wZStep;

			subcounter += subincrement;
		}

		g_lpLib3d->SetGlobal(TOGGLE_GLOBALALPHA,SMOKED_OFF);
	}
#endif
}

