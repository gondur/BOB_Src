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
//Filename       landscap.cpp
//System         
//Author         Paul.   
//Date           Mon 6 Nov 1995
//Description    
//------------------------------------------------------------------------------

//#define _NO_UNDERGROUND_FILL

//#define _DOUBLE_SIDED_CLIFFS_

#define _TILE_POSITIONS_IN_MATRIX
#ifndef	NDEBUG
//#define	_NOCLOUDS_
//#define _NO_FLUFFY_CLOUDS_
//#define	_NOLANDSCAPE_
//#define _NOHIREZ 
//#define _NOTILEMAKE
//#define _NO_INFI_STRIP
//#define _RENDER_SIMPLE_TEXTURE
//#define _SUPERQUICKLANDSCAPE_
//#define _QUICKLANDSCAPE_
//#define _QUICKLANDSCAPEFANS_
//#define _NO_TEXTURE_RENDER
#define _ALWAYS_FULL_REZ
#endif

#define CLIFFTWIDTH 128
#define CLIFFTHEIGHT 128

//#define NO_LIGHT	"YES" 
		#include "Dosdefs.h"
		#include "mystack.h"
#define F_GRAFIX												//DAW 05Aug96
#define F_BATTLE
		#include "Worldinc.h"
 
		#include "enumbits.m"									//PD 04Dec95
		#include "Palette.h"
		#include "Files.g"
		#include "3DDefs.h"
		#include "ImageMap.h" 
		#include "BTree.h"
		#include "Polygon.h"
#define MATRIX_CODE_REQ						//RJS 26Jun98
		#include "Matrix.h"
		#include "WorldInc.h"
		#include "World.h"
		#include "3DCode.h"
		#include "3DCom.h"
		#include "HardpASM.h"
		#include	"gameset.h"									//PD 05Oct98
		#include "LandScap.h"
		#include "myMath.h"
		#include "viewsel.h"										//PD 19Mar96
		#include "Collided.h"									//PD 21Mar96
		#include	"keytest.h"									//PD 20May96
		#include	"flymodel.h"								//PD 24Jun96

#include "ImageMap.g"

		#include "migLand.h"						//PD 19Jan98 
		#include "savegame.h"
		#include	"missman2.h"

		#define	INIT_HDATA										//PD 25Nov97
		#include "hdata.h"										//PD 25Nov97

		#include "monotxt.h"
		#include "prof.h"
		#include	"miles.h"
		#include "tilemake.h"
	#include "overlay.h"
	#include "areatype.h"
#include "grid.h" //jon

#include "FastMath.h" // stuff i found was needed - Jon 3-5-200
#include "sky.h"
#include "model.h"
#include "Replay.h" // end of that section of needed stuff
#include "persons2.h" // for the mirror landscape

	class LandScape Land_Scape;
	TileElement* TileResList::theGrid = NULL; // set up an instance



//TempCode JON 13Sep00 typedef struct _MemBlockStruc
//TempCode JON 13Sep00 {
//TempCode JON 13Sep00         _MemBlockStruc*	pBlockHeaderNext;
//TempCode JON 13Sep00 		_MemBlockStruc*	pBlockHeaderPrev;
//TempCode JON 13Sep00 		char*			filename;
//TempCode JON 13Sep00 		ULong			nLine;
//TempCode JON 13Sep00 		ULong			nDataSize;
//TempCode JON 13Sep00 		ULong			nBlockUse;
//TempCode JON 13Sep00 		ULong			lrequest;
//TempCode JON 13Sep00 		UByte			gap[4];
//TempCode JON 13Sep00 		UByte			userdata[8];
//TempCode JON 13Sep00 } _MemBlockStruc;
//TempCode JON 13Sep00 
//TempCode JON 13Sep00 void	DbgMemTest3(void*	ptr)
//TempCode JON 13Sep00 {
//TempCode JON 13Sep00 	if (ptr)
//TempCode JON 13Sep00 	{
//TempCode JON 13Sep00 		_MemBlockStruc*	memblock = (_MemBlockStruc*) (int(ptr)-32);
//TempCode JON 13Sep00 		if (	(memblock->gap[0]!=0xFD)
//TempCode JON 13Sep00 			||	(memblock->gap[1]!=0xFD)
//TempCode JON 13Sep00 			||	(memblock->gap[2]!=0xFD)
//TempCode JON 13Sep00 			||	(memblock->gap[3]!=0xFD)	)
//TempCode JON 13Sep00 		{
//TempCode JON 13Sep00 			INT3;
//TempCode JON 13Sep00 		}
//TempCode JON 13Sep00 
//TempCode JON 13Sep00 		if (	(memblock->gap[4+memblock->nDataSize]!=0xFD)
//TempCode JON 13Sep00 			||	(memblock->gap[5+memblock->nDataSize]!=0xFD)
//TempCode JON 13Sep00 			||	(memblock->gap[6+memblock->nDataSize]!=0xFD)
//TempCode JON 13Sep00 			||	(memblock->gap[7+memblock->nDataSize]!=0xFD)	)
//TempCode JON 13Sep00 		{
//TempCode JON 13Sep00 			INT3;
//TempCode JON 13Sep00 		}
//TempCode JON 13Sep00 
//TempCode JON 13Sep00 		UByte* jon = (UByte*) ptr+memblock->nDataSize;
//TempCode JON 13Sep00 		NOP;
//TempCode JON 13Sep00 	}
//TempCode JON 13Sep00 }

UByte meshDetailLookup[5][9] =											//JON 2Aug00
{ // min
	{ 1, 2, 3, 4, 6, 7, 7, 7, 7 },
 // low
	{ 0, 1, 2, 3, 4, 6, 7, 7, 7 },
 // med
	{ 0, 0, 1, 2, 3, 4, 6, 7, 7 },
 // high
	{ 0, 0, 1, 1, 2, 3, 4, 5, 6 },
 // max
	{ 0, 0, 0, 1, 1, 2, 3, 4, 4 },
};

UWord	Lib3DPoint::copyCount = 0;

int DitherLookUp[32]=
{
	0,  //areatype 0 (and rotations), dither image 1
	0,  //areatype 1, dither image 1
	0,  //areatype 2, dither image 1
	0,  //areatype 3, dither image 1
	0,  //areatype 4, dither image 1
	1,  //areatype 5, dither image 2 ...
	1,	//6
	1,	//7
	1,	//8
	1,	//9
	2,	//10
	2,	
	2,
	2,
	0,
	-1,	//15 - has no dither...
	2,	
	0,
	2,
	0,
	-1, //20 - the sea...
	-1,
	-1,
	-1,
	-1,
	-1,//25
	-1,
	3,//concrete
	4,
	5,
	3,//30
	-1
};

raiseTable RaiseLookUp[]=
{
	{NULLIMAGE,0,0,0,0}, // the first 32 hold the values after scaling for current viewpoint
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0}, 
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0}, 
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},										
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	// these are for the unscaled equivalents...
	{NULLIMAGE,0,0,0,0}, //grass
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0}, // fields
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0}, // spreads
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{WOODNO,1500,1500,1500,1500,1,1,1,1}, // wood
	{NULLIMAGE,0,0,0,0}, // roughs
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0}, //sea
	{NULLIMAGE,0,0,0,0}, //stream
	{NULLIMAGE,0,0,0,0}, //village
	{TOWNANO,600,900,1200,1500,2,3,4,5}, //denseTown //23
	// please note that these point offsets sould start at 2 and go upward in consecutive numbers
	// for the town side stuff - relied upon to get the texture coords
//	{TOWNBNO,600,900,1200,1500}, //sparseTown
	{NULLIMAGE,0,0,0,0},//sparseTown //24
	{CITYANO,1200,1500,2000,2500,6,7,8,9}, //denseCity //25
	{CITYBNO,1200,1500,2000,2500,10,11,12,13}, //sparseCity //26
//TempCode JON 20Sep00 	{CITYBNO,1200,1500,2000,2500,6,7,8,9}, //sparseCity //26
	{NULLIMAGE,0,0,0,0}, //citybase
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0},
	{NULLIMAGE,0,0,0,0} //urban buildup?

}; //index on area type&mask - the second 32 are for the unscaled corresponding values for the 1st 32.

SLong 	_cloudLayerHeight=15000*33;	//1500ft in cm
SLong	lowestgroundpoint;
//DEADCODE PD 03/12/99 		extern void GreyPalette(UByte*,UByte*,UByte*);
//DEADCODE PD 03/12/99 		extern bool mono3d;

struct LandScape::RouteData{
 	UWord type;
	ULong width;
	ULong maxWidth;
	Colour colour;
	LandMapNum plainTexture;
	UWord pX0,pY0,pX1,pY1;
	LandMapNum maskedTexture;
	UWord mX0,mY0,mX1,mY1;
	RouteData() {}
	RouteData(	UWord a, ULong b, ULong bb, Colour c,
				LandMapNum d,UWord ax0,UWord ay0,UWord ax1,UWord ay1,
				LandMapNum e,UWord bx0,UWord by0,UWord bx1,UWord by1)
	{
		type=a;
		width=b;
		maxWidth=bb;
		colour=c;
		plainTexture=d; pX0=ax0; pY0=ay0; pX1=ax1; pY1=ay1;
		maskedTexture=d; mX0=bx0; mY0=by0; mX1=bx1; mY1=by1;
	}
	inline RouteData* find(UWord type){
	 	RouteData* srch=this;
		while (srch->type!=type && srch->type!=0xFFFF) srch++;
		if (srch->type==0xFFFF) return (RouteData*)NULL;
		return srch;
	}
};

void LandScape::ResetItemLog()
{
//	if (Save_Data.fSoftware && softGrid!=NULL)
//	{
//		const SLong length=_wholeAreaSizeMIN*_wholeAreaSizeMIN;
//		UByte *ptr=softGrid;
//		for (SLong i=(length>>2)-1;i>=0;*(ULong*)ptr=ULong(0),ptr+=4,i--);
//		if (length&2L) *(UWord*)ptr=UWord(0),ptr+=2;
//		if (length&1L) *(UByte*)ptr=UByte(0);
//	}
}

bool LandScape::LogItem(ULong vx,ULong vz,COORDS3D& pos)
{
//	if (Save_Data.fSoftware && softGrid!=NULL)
//	{
//		if (pos.Y>HIGHESTGROUND) return false;	//no point logging an item > HIGHESTGROUND
//
//		//generate grid position for this item
//
//		ULong	ox=(vx&~ULong(_blockWidth-1))-_halfAreaSizeMIN*_blockWidth;
//		ox=(pos.X>>17)-ox; if (ox>ULong(_wholeAreaSizeMIN-1)) return false; /* object not on grid */
//
//		ULong	oz=(vz&~ULong(_blockWidth-1))-_halfAreaSizeMIN*_blockWidth;
//		oz=(pos.Z>>17)-oz; if (oz>ULong(_wholeAreaSizeMIN-1)) return false; /* object not on grid */
//
//		*(softGrid+(oz*_wholeAreaSizeMIN)+ox)=0xFF;
//
//		return true; /* stop any further item insertion tests once one has been inserted successfully */
//	}
	/* else */ return true; /* stop attempts to insert any items unless it's the software version */
}

struct BoundingBox
{
	SLong MIN(const SLong a,const SLong b) { return a<b?a:b; }
	SLong MAX(const SLong a,const SLong b) { return a>b?a:b; }

	const SLong ROUND_ERR_FIX;

	SLong	minx,maxx;
	SLong	miny,maxy;
	SLong	minz,maxz;

	BoundingBox() : ROUND_ERR_FIX(0) {}
	BoundingBox(int num,COORDS3D* pts) : ROUND_ERR_FIX(131072>>1)
	{
		minx=maxx=pts->X;
		miny=maxy=pts->Y;
		minz=maxz=pts->Z;
		for (int i=num-1;i>0;i--)
		{
			minx=MIN(minx,pts[i].X);	maxx=MAX(maxx,pts[i].X);
			miny=MIN(miny,pts[i].Y);	maxy=MAX(maxy,pts[i].Y);
			minz=MIN(minz,pts[i].Z);	maxx=MAX(maxz,pts[i].Z);
		}
		minx-=ROUND_ERR_FIX;
		miny-=ROUND_ERR_FIX;
		minz-=ROUND_ERR_FIX;
		maxx+=ROUND_ERR_FIX;
		maxy+=ROUND_ERR_FIX;
		maxz+=ROUND_ERR_FIX;
	}
	BoundingBox(const COORDS3D& ori,const COORDS3D& delta) : ROUND_ERR_FIX(0)
	{
		if (delta.X<0)	maxx=ori.X, minx=maxx+delta.X;
		else			minx=ori.X, maxx=minx+delta.X;
		if (delta.Y<0)	maxy=ori.Y, miny=maxy+delta.Y;
		else			miny=ori.Y, maxy=miny+delta.Y;
		if (delta.Z<0)	maxz=ori.Z, minz=maxz+delta.Z;
		else			minz=ori.Z, maxz=minz+delta.Z;
	}
	bool Overlap(const BoundingBox& box)
	{
		if (minx>box.maxx || maxx<box.minx || miny>box.maxy || maxy<box.miny || minx>box.maxz || maxz<box.minz)	return false;
		return true;
	}
};


const	SLong	MaxSmokeClouds = 48;							//RJS 23May00
const	SLong	MaxTimeSmokeAlive = 60000;								//RJS 24May00
const	int		SmokeAnimSize = 32;										//RJS 24May00


static bool doneUpdateLandscape = false;
static SLong lastMeshDataX = -10000;									//JON 9Nov00
static SLong lastMeshDataZ = -10000;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderLandscape
//Author		Paul.   
//Date			Mon 6 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::RenderLandscape(	CLib3D *lib3d )
//DEADCODE JON 4/6/00 									ViewPoint* vp,
//DEADCODE JON 4/6/00 									FPMATRIX_PTR matrixptr,
//DEADCODE JON 4/6/00 									ULong& wx, ULong& wy, ULong& wz,
//DEADCODE JON 4/6/00 									ANGLES heading)
{
	g_lpLib3d=lib3d;								    

	Bool	old_xprod;
//DeadCode JON 13Jul00 	Bool	otherfade;

	bool notMap=true;
	
	LIGHTINGDESC lightDesc;


	if (View_Point!=NULL)
		notMap=(View_Point->viewnum.viewmode!=VM_Map || (View_Point->viewnum.viewmode==VM_Map && OverLay.fZoomedMap))?true:false;

	if (View_Point->drawmap == FALSE)
	{
		lightDesc.lowRGB=currentLighting.landAmbientCollo.col();
		lightDesc.highRGB=currentLighting.landAmbientColhi.col();
		lightDesc.ambientRGB=currentLighting.sunCol.col();					//JON 5Oct00

		lightDesc.lowDot=0.f;
		g_lpLib3d->GetMaxLandDotProduct(lightDesc.highDot);
	} else
	{
		lightDesc.lowRGB=0x00FFFFFF;
		lightDesc.highRGB=0x00FFFFFF;
		lightDesc.ambientRGB=0x00FFFFFF;

		lightDesc.lowDot=0.f;
		lightDesc.highDot=1.f;
	}
	lightDesc.specularRGB=currentLighting.specularHighlight.col();

	g_lpLib3d->SetAmbientLighting(lightDesc);


	//Initialise variables local to 'LandScape'

//DEADCODE JON 4/6/00 	viewer_hdg = heading;
//DEADCODE JON 4/6/00 	viewer_x = wx;
//DEADCODE JON 4/6/00 	viewer_y = wy;
//DEADCODE JON 4/6/00 	viewer_z = wz;

//DEADCODE JON 4/6/00 	fpviewer_matrix = matrixptr;

	//Set various distance variables up
	View_Ground_Height = SetViewDetail();						//RJS 25Jun98


//DEADCODE JON 4/7/00 	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
//DEADCODE JON 4/7/00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
//DEADCODE JON 4/7/00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
//DEADCODE JON 4/7/00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);
//DEADCODE JON 4/7/00 	if (View_Point->InCockpit())								//RJS 15Mar00
//DEADCODE JON 4/7/00 		g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->eyeHeading);
//DeadCode RJS 15Mar100 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,1,14829100,0);
//DEADCODE JON 4/7/00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,50,view_dist);
//DEADCODE JON 4/7/00 	g_lpLib3d->SetFogColour(0x0090B8E8);

	g_lpLib3d->PushMatrix(MATRIX_OBJECT);
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

	D3DVECTOR viewMods;
	viewMods.x=(D3DVALUE)-viewer_x;
	viewMods.y=(D3DVALUE)-viewer_y;
	viewMods.z=(D3DVALUE)-viewer_z;
	g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

	//Draw horizon in here
	if (View_Point && notMap)		//RJS 10Sep98
	{
		g_lpLib3d->SetGlobal( TOGGLE_TEXTURE_ZBIAS, 2 );

		if (View_Point->drawmap == FALSE)
		{
			InfiniteStrip( View_Point->pitch, View_Point->roll );
			R3DVERTEX fakeVertex;
			fakeVertex.x = 
				fakeVertex.y = 
					fakeVertex.z =
						fakeVertex.nx =
							fakeVertex.nz = 0.0f;
			fakeVertex.ny = 1.0f; // normal sticking up.
			
			g_lpLib3d->GetTransformedLightColour( fakeVertex, LF_LIGHTING );
//			lightDesc.ambientRGB=currentLighting.landAmbientColamb.col(); // now set ambient col for sun
			lightDesc.ambientRGB=fakeVertex.color.all;
			g_lpLib3d->SetAmbientLighting(lightDesc);						//JON 5Oct00

#ifndef	_NOLANDSCAPE_
			DrawHorizon(); 
#endif
		}
		g_lpLib3d->SetGlobal( TOGGLE_TEXTURE_ZBIAS, 2 );

		lowestgroundpoint=0x7FFFFFFF;								//PD 12Dec96
//DeadCode JON 13Jul00 		otherfade=(!Three_Dee.IsPaused())?BadVision():FALSE;
#ifndef	_NOLANDSCAPE_
		GeneratePointData();
#endif
		AutoScaleFrameRate();

		if (lowestgroundpoint==0x07FFFFFFF)							  //JIM 29/03/99
			lowestgroundpoint=0;	//PD 27Sep97

		g_lpLib3d->SetGlobal( TOGGLE_TEXTURE_ZBIAS, 0UL );

		if (View_Point->drawmap == FALSE)
		{
#ifndef	_NOCLOUDS_
			DistDrawClouds(0);
#endif
//deadcode JON 19/06/01				DoRain(View_Point,View_Ground_Height);							//RJS 25Jun98
		}


	}
	g_lpLib3d->PopMatrix(MATRIX_OBJECT);

	doneUpdateLandscape = false;

	//DeadCode JON 21Aug00 	g_lpLib3d->DecGlobal( TOGGLE_TEXTURE_ZBIAS );
//DeadCode JON 21Aug00 	static bool dotest = false;
//DeadCode JON 21Aug00 	if ( dotest )
//DeadCode JON 21Aug00 	{
//DeadCode JON 21Aug00 		g_lpLib3d->SetGlobal( TOGGLE_TEXTURE_ZBIAS, ULong(0) );
//DeadCode JON 21Aug00 		g_lpLib3d->FlushAsBackground();
//DeadCode JON 21Aug00 		RenderMirrorLandscape();
//DeadCode JON 21Aug00 		g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
//DeadCode JON 21Aug00 		g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
//DeadCode JON 21Aug00 		SVertex* jon = g_lpLib3d->BeginPoly( 4 );
//DeadCode JON 21Aug00 		g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,Three_Dee.clipNearZ,2000.f);	
//DeadCode JON 21Aug00 		jon->setPosition( 0, 0, Three_Dee.clipNearZ );
//DeadCode JON 21Aug00 		jon++;
//DeadCode JON 21Aug00 		jon->setPosition( 0, 1.f, Three_Dee.clipNearZ+10.f );
//DeadCode JON 21Aug00 		jon++;
//DeadCode JON 21Aug00 		jon->setPosition( 0.5f, 0.5f, 1000.f );
//DeadCode JON 21Aug00 		jon++;
//DeadCode JON 21Aug00 		jon->setPosition( 1.f, 0, 2000.f );
//DeadCode JON 21Aug00 		g_lpLib3d->EndPoly();
//DeadCode JON 21Aug00 	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    RenderMirrorLandscape

// Date:		04/07/00
// Author:		JON
//
//Description: Renders a low rez landscape using the c/urrent view set up in lib3d
//			   to decide on visibility
//
//////////////////////////////////////////////////////////////////////
void LandScape::RenderMirrorLandscape( void )
{
#ifndef	_NOLANDSCAPE_

//TempCode JON 7Nov00 	R3DCOLOUR fogCol;
//TempCode JON 7Nov00 	fogCol = ( (currentLighting.fogColSun.red()<<16)+(currentLighting.fogColSun.green()<<8)+currentLighting.fogColSun.blue() );
//TempCode JON 7Nov00 	R3DCOLOUR fogColShade;
//TempCode JON 7Nov00 	fogColShade = ( (currentLighting.fogColShade.red()<<16)+(currentLighting.fogColShade.green()<<8)+currentLighting.fogColShade.blue() );
//TempCode JON 7Nov00 	fogCol.interpRGB( fogColShade, sunProportion );
//TempCode JON 7Nov00 
//TempCode JON 7Nov00 	Three_Dee.fogCol=fogCol.all;


//TempCode JON 7Nov00 	g_lpLib3d->Wipe( Three_Dee.fogCol );

//	viewx = Three_Dee.eye_x;
//	viewy = Three_Dee.eye_z;
//	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)(-(int)Persons2::PlayerSeenAC->pitch));
//	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)(-(int)Persons2::PlayerSeenAC->roll));

	LIGHTINGDESC lightDesc;

	lightDesc.lowRGB=currentLighting.landAmbientCollo.col();
	lightDesc.highRGB=currentLighting.landAmbientColhi.col();
	lightDesc.ambientRGB=currentLighting.sunCol.col();					//JON 5Oct00

	lightDesc.lowDot=0.0f;
	lightDesc.highDot=1.0f;
	lightDesc.specularRGB=currentLighting.specularHighlight.col();
	g_lpLib3d->SetAmbientLighting(lightDesc);

	LIGHTFLAG lf = LF_AMBIENT;
	g_lpLib3d->SetObjectLighting( lf );
	ULong old_view_dist = view_dist;
	view_dist = RANGE_FAR_MIRROR;

	InfiniteStrip( Persons2::PlayerSeenAC->pitch, Persons2::PlayerSeenAC->roll ); // hahaha
	lightDesc.ambientRGB=currentLighting.landAmbientColamb.col(); // now set ambient col for landscape
	g_lpLib3d->SetAmbientLighting(lightDesc);

	g_lpLib3d->PushMatrix( MATRIX_OBJECT );
	g_lpLib3d->LoadIdentity( MATRIX_OBJECT );
	D3DVECTOR viewMods;
	viewMods.x=(D3DVALUE)-viewer_x;
	viewMods.y=(D3DVALUE)-(viewer_y+500.f);
	viewMods.z=(D3DVALUE)-viewer_z;
	g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

	DoPointStruc* offPos = horizPoint;

	// note this depends upon the horizon distance as that way I can re-use the points.
	if ( Save_Data.detail_3d[DETAIL3D_HORIZONDIST] )
	{ // HIGH DISTANCE HORIZON

		ULong flags[_horizonPoints*_horizonPoints];

		g_lpLib3d->VisibleCheck(horizPoint,_horizonPoints*_horizonPoints,flags);

		ULong *lowf=flags, *lowf2;
		DoPointStruc* offPos2;

		// reset the copy count
		Lib3DPoint* cornerVert;

		for (int sz=0;sz<_horizonAreaSize;sz++)
		{
			lowf2=lowf;
			lowf+=_horizonPoints;
			offPos2=offPos;
			offPos+=_horizonPoints;

			for (int sx=0;sx<_horizonAreaSize;sx++,lowf2++,offPos2++)
			{
				ULong flag=lowf2[0]&lowf2[1]&lowf2[_horizonPoints]&lowf2[_horizonPoints+1];
				if ( !flag )
				{ // draw this grid

					cornerVert = g_lpLib3d->BeginPoly(HMATERIAL(horizonImg),4);

					cornerVert[0] = offPos2[0];
					cornerVert[1] = offPos2[_horizonPoints];
					cornerVert[2] = offPos2[_horizonPoints+1];
					cornerVert[3] = offPos2[1];
#ifndef	_NO_VERTEX_SHARING_HDR
					cornerVert[0].info.setUnique();
					cornerVert[1].info.setUnique();
					cornerVert[2].info.setUnique();
					cornerVert[3].info.setUnique();
#endif
				
					g_lpLib3d->EndPoly();
				}
			}
		}

	} else
	{ // LOW DISTANCE HORIZON

		int x = viewer_x>>Grid_Base::WORLDSPACEMOD;
		int z = viewer_z>>Grid_Base::WORLDSPACEMOD;

		// do we need to redo the imagemap?
		if ( gridOffs.needColMapUpdate( x, z ) )
		{ // we need to recalculate the imagemap
			UpdateHorizTexture( x, z );
		} // end of update imagemap

		ULong flags[_cornerLengthMIN*_cornerLengthMIN];

		g_lpLib3d->VisibleCheck(horizPoint,_cornerLengthMIN*_cornerLengthMIN,flags);

		ULong *lowf=flags, *lowf2;
		DoPointStruc* offPos2;

		// reset the copy count
		Lib3DPoint* cornerVert;

		for (int sz=0;sz<_wholeAreaSizeMIN;sz++)
		{
			lowf2=lowf;
			lowf+=_cornerLengthMIN;
			offPos2=offPos;
			offPos+=_cornerLengthMIN;
			
			for (int sx=0;sx<_wholeAreaSizeMIN;sx++,lowf2++,offPos2++)
			{

				ULong flag=lowf2[0]&lowf2[1]&lowf2[_cornerLengthMIN]&lowf2[_cornerLengthMIN+1];
				if ( !flag )
				{ // draw this grid

					cornerVert = g_lpLib3d->BeginPoly(HMATERIAL(horizonImg),4);

					cornerVert[0] = offPos2[0];
					cornerVert[1] = offPos2[_cornerLengthMIN];
					cornerVert[2] = offPos2[_cornerLengthMIN+1];
					cornerVert[3] = offPos2[1];
#ifndef	_NO_VERTEX_SHARING_HDR
					cornerVert[0].info.setUnique();
					cornerVert[1].info.setUnique();
					cornerVert[2].info.setUnique();
					cornerVert[3].info.setUnique();
#endif
					g_lpLib3d->EndPoly();

				}
			}
		}

	}

	g_lpLib3d->PopMatrix( MATRIX_OBJECT );
	g_lpLib3d->SetObjectLighting( lf );
#endif
	view_dist = old_view_dist;

}

//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 // assume x down and z goes left to right
//DEADCODE JON 5/3/00 struct vec2d
//DEADCODE JON 5/3/00 {
//DEADCODE JON 5/3/00 	long x,z; // the position
//DEADCODE JON 5/3/00 	long ex; // the other end used to throw out stuff..
//DEADCODE JON 5/3/00 	double dx; // the direction vector
//DEADCODE JON 5/3/00 	double dz;
//DEADCODE JON 5/3/00 	double m; // gradient - how far to move in z for 1 in x - speedup cheat.
//DEADCODE JON 5/3/00 	bool horiz; // is it horizontal
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 	// constructor from 2 points
//DEADCODE JON 5/3/00 	bool buildFromPts( long x1, long z1, long x2, long z2 )
//DEADCODE JON 5/3/00 	{
//DEADCODE JON 5/3/00 		if ( x1 == x2 && z1 == z2 )
//DEADCODE JON 5/3/00 			return false; // not a line
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 		x = x1;
//DEADCODE JON 5/3/00 		z = z1;
//DEADCODE JON 5/3/00 		ex = x2;
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 		dx = double(x2-x1);
//DEADCODE JON 5/3/00 		dz = double(z2-z1);
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 		horiz = false;
//DEADCODE JON 5/3/00 		if ( x1 != x2 )
//DEADCODE JON 5/3/00 			m = dz/dx;
//DEADCODE JON 5/3/00 		else 
//DEADCODE JON 5/3/00 			horiz = true;
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 		// normalize
//DEADCODE JON 5/3/00 //		double nv = fastMath.FastInvSqrt((dx*dx)+(dz*dz)); // seems not to be accurate enough
//DEADCODE JON 5/3/00 		double nv = 1.0/sqrt( (dx*dx)+(dz*dz) );
//DEADCODE JON 5/3/00 		dx*=nv;
//DEADCODE JON 5/3/00 		dz*=nv;
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 		return true;
//DEADCODE JON 5/3/00 	}
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 	// get the angle between lines
//DEADCODE JON 5/3/00 	double getAngleSize( vec2d &t ) 
//DEADCODE JON 5/3/00 	{
//DEADCODE JON 5/3/00 		double V = t.getAngleSizeToVert() - getAngleSizeToVert();
//DEADCODE JON 5/3/00 		if ( V < 0 )
//DEADCODE JON 5/3/00 			return 4.0+V;
//DEADCODE JON 5/3/00 		else 
//DEADCODE JON 5/3/00 			return V;
//DEADCODE JON 5/3/00 	}
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 	// vert pointing down as X increaces...
//DEADCODE JON 5/3/00 	double getAngleSizeToVert()
//DEADCODE JON 5/3/00 	{ // the other direction vector would have dx = 1, dz = 0;
//DEADCODE JON 5/3/00 	  // therefore dx*1 + dz*0 = dx  - dead simple!
//DEADCODE JON 5/3/00 	  // don't bother with doing an inverse cosine on the angle just to be able to compare sizes 
//DEADCODE JON 5/3/00 	  // just return 1-dx which will give the angle's relative size.
//DEADCODE JON 5/3/00 		if ( dz > 0.0 ) // range from 0->2
//DEADCODE JON 5/3/00 			return 1.0-dx;
//DEADCODE JON 5/3/00 		else // oh its over 180 degrees - make the values range from 4 to 2...
//DEADCODE JON 5/3/00 			return 3.0+dx;
//DEADCODE JON 5/3/00 	}
//DEADCODE JON 5/3/00 	// return the z for given x.
//DEADCODE JON 5/3/00 	ULong getz( long tx, bool &inBounds )
//DEADCODE JON 5/3/00 	{
//DEADCODE JON 5/3/00 		if ( tx>>Grid_Base::WORLDSPACEMOD >= x>>Grid_Base::WORLDSPACEMOD
//DEADCODE JON 5/3/00 				&& tx>>Grid_Base::WORLDSPACEMOD <= ex>>Grid_Base::WORLDSPACEMOD 
//DEADCODE JON 5/3/00 				|| tx>>Grid_Base::WORLDSPACEMOD <= x>>Grid_Base::WORLDSPACEMOD 
//DEADCODE JON 5/3/00 				&& tx>>Grid_Base::WORLDSPACEMOD >= ex>>Grid_Base::WORLDSPACEMOD )
//DEADCODE JON 5/3/00 		if ( tx >= x && tx <= ex || tx <= x && tx >= ex )
//DEADCODE JON 5/3/00 			inBounds = true;
//DEADCODE JON 5/3/00 		else
//DEADCODE JON 5/3/00 			inBounds = false;
//DEADCODE JON 5/3/00 
//DEADCODE JON 5/3/00 //		if ( tx > x )
//DEADCODE JON 5/3/00 //			return z+ULong(m*float(tx-x)+.5f);
//DEADCODE JON 5/3/00 //		else 
//DEADCODE JON 5/3/00 //			return z-ULong(m*float(x-tx)-.5f);
//DEADCODE JON 5/3/00 		return z+long(m*float(tx-x)+.5f);
//DEADCODE JON 5/3/00 	}
//DEADCODE JON 5/3/00 };

inline void interceptBase( COORDS3D &below, const COORDS3D &above )
{
	if ( above.Y > 0 && below.Y < 0 )
	{
		float k = float(-above.Y)/float(below.Y-above.Y);
		below.X+=SLong( float( above.X-below.X ) * k );
		below.Y=0;
		below.Z+=SLong( float( above.Z-below.Z ) * k );
	}
}

void LandScape::UpdateHorizTextureIfMoved( const int x, const int z )
{
	// do we need to redo the imagemap?
	if ( gridOffs.hasHorizMoved( x, z ) )
	{ // we need to recalculate the imagemap
		UpdateHorizTexture( x, z );
	} // end of update imagemap
}

void LandScape::UpdateHorizTexture( const int x, const int z )
{
	gridOffs.setColMapCoords( x, z );
	// unload the old one from the card.
	g_lpLib3d->UnloadTexture( horizonImg );

//DEADCODE CSB 25/05/00 	fileblock fb( FIL_4COLGRID, Grid_Base::makeGridAt );
	Grid_Long* colD = (Grid_Long*) Grid_Base::gridfiles[Grid_Base::GF_COLOUR].getdata();

	UByte* t = horizonImg->body;
	for ( int sz = (z<<1)-128; sz < (z<<1)+128; sz++ )
		for ( int sx = (x<<1)-128; sx < (x<<1)+128; sx++ )
		{
			*t++ = colD->getModD( sx, sz );
		}

}

//////////////////////////////////////////////////////////////////////
//
// Function:    UpdateCloseHorizCornerPoints

// Date:		03/08/00
// Author:		JON
//
//Description:  does exactly what it says on the tin....
//
//////////////////////////////////////////////////////////////////////
inline void LandScape::UpdateCloseHorizCornerPoints( const int x, const int z )
{
	// recalc horizon vertex points
	//Generate start position based on the current viewpoint
	ULong px,pz;
	px = (x-_halfAreaSizeMIN)<<Grid_Base::WORLDSPACEMOD;
	pz = (z-_halfAreaSizeMIN)<<Grid_Base::WORLDSPACEMOD;

	DoPointStruc* curPoint=horizPoint;

	// get the grid data 4 min altitudes
//DeadCode JON 9Jun00 			fileblock fb1( FIL_MINALT, Grid_Base::makeGridAt );
//DeadCode JON 9Jun00 			Grid_Base* minAlt = (Grid_Base*) fb1.getdata();
//DeadCode JON 9Aug00 	Grid_Base* minAlt = (Grid_Base*) Grid_Base::gridfiles[Grid_Base::GF_MINALT].getdata();
	Grid_Base* cornerAlt = (Grid_Base*) Grid_Base::gridfiles[Grid_Base::GF_CORNERALT].getdata();


	int imx,imz,rowStart; // image map coords
	imz = (z+(64-_horizonDist) - gridOffs.hz )<<1;
	rowStart = (x+(64-_horizonDist) - gridOffs.hx)<<1;
	
	imz+=( (_horizonDist-_halfAreaSizeMIN)<<1 );
	rowStart+= ( (_horizonDist-_halfAreaSizeMIN)<<1 );

	for (int sz=0;sz<_cornerLengthMIN;sz++,pz+=_blockWidth,imz+=2) // loop tru z
	{
		ULong rowx = px;
		imx = rowStart;
		for ( int sx=0; sx<_cornerLengthMIN; sx++,rowx+=_blockWidth,curPoint++,imx+=2)  // loop x
		{
//DEADCODE JON 5/24/00 					curPoint->y=(minAlt->getMod( x-_halfAreaSizeMIN+sx, z-_halfAreaSizeMIN+sz )-2)<<9;
//DEADCODE JON 5/24/00 					curPoint->x=rowx;
//DEADCODE JON 5/24/00 					curPoint->z=pz;
			curPoint->setPosition( 
					rowx,
					(cornerAlt->getMod( x-_halfAreaSizeMIN+sx, z-_halfAreaSizeMIN+sz ) << _altitudeShift),
//DeadCode JON 9Aug00 					(minAlt->getMod( x-_halfAreaSizeMIN+sx, z-_halfAreaSizeMIN+sz )-2)<<9,
					pz
				);
			curPoint->setIMapCoords( imx, imz ); // maybe needed if no tile imagemap						
		}
	}
}

void LandScape::SetUpVisibleCones(	CLib3D *lib3d,
											ViewPoint* vp,
											ULong& wx, ULong& wy, ULong& wz,
											ANGLES heading, bool doMaxResTiles )
{	
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"SUVC: start ");
	// set up variables local to landscape
	g_lpLib3d=lib3d;
	viewer_hdg = heading;
 	viewer_x = wx;
	viewer_y = wy;
	viewer_z = wz;

	View_Point = vp;
	OverLay.DoPossibleLandscapeRefresh();

	maxResTiles = doMaxResTiles;

	// set up the view
	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);
//DEADCODE RJS 5/9/00 	if (View_Point->InCockpit())								//RJS 15Mar00
//DEADCODE RJS 5/9/00 	{
//DEADCODE RJS 5/9/00 		g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->eyeHeading);
//DEADCODE RJS 5/9/00 		viewer_hdg += View_Point->eyeHeading;
//DEADCODE RJS 5/9/00 	}
//DeadCode RJS 15Mar100 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,1,14829100,0);
	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,10,view_dist,true);
	//DEADCODE JON 4/18/00 	g_lpLib3d->SetFogColour(0x0090B8E8);

	D3DVECTOR viewMods;
	viewMods.x=(D3DVALUE)-viewer_x;
	viewMods.y=(D3DVALUE)-viewer_y;
	viewMods.z=(D3DVALUE)-viewer_z;
	g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

	// calculate the current block position
	int x = viewer_x>>Grid_Base::WORLDSPACEMOD;
	int z = viewer_z>>Grid_Base::WORLDSPACEMOD;


	if ( Save_Data.detail_3d[DETAIL3D_HORIZONDIST] )
	{ // HIGH DISTANCE HORIZON

//DeadCode MS 15Aug00 		Mono_Text.Print((UByte*)"SUVC: high distance horizon ");
		// cheap mem zero - change if _wholeAreaSizeMIN changes.
		long* t = (long*)gridCone;
		for ( int i = 0; i< 72; i++ )
		{
			*t++ = 0;
		}
		gridCone[288] = 0;

		if ( gridOffs.hasMoved( x, z ) ) // have we moved to a new block
		{
			ScrollTileGrid( x - gridOffs.jx, z - gridOffs.jz ); // move the texture tiles about
			gridOffs.set( x, z );

			// do we need to redo the imagemap?
			if ( gridOffs.needColMapUpdate( x, z ) )
			{ // we need to recalculate the imagemap
				UpdateHorizTexture( x, z );
			} // end of update imagemap

			// recalc horizon vertex points
			//Generate start position based on the current viewpoint
			ULong px,pz;
			px = (x-_horizonDist)<<Grid_Base::WORLDSPACEMOD;
			pz = (z-_horizonDist)<<Grid_Base::WORLDSPACEMOD;

			DoPointStruc* curPoint=horizPoint;

			int imx,imz,rowStart; // image map coords
			imz = (z+(64-_horizonDist) - gridOffs.hz )<<1;
			rowStart = (x+(64-_horizonDist) - gridOffs.hx)<<1;

			// get the grid data 4 min altitudes
//			fileblock fb1( FIL_MINALT, Grid_Base::makeGridAt );
//			Grid_Base* minAlt = (Grid_Base*) fb1.getdata();
//			Grid_Base* minAlt = (Grid_Base*) Grid_Base::gridfiles[Grid_Base::GF_MINALT].getdata();
			Grid_Base* cornerAlt = (Grid_Base*) Grid_Base::gridfiles[Grid_Base::GF_CORNERALT].getdata();

			for (int sz=0;sz<_horizonPoints;sz++,pz+=_blockWidth,imz+=2) // loop tru z
			{
				imx = rowStart;
				ULong rowx = px;
				for ( int sx=0; sx<_horizonPoints; sx++,rowx+=_blockWidth,curPoint++,imx+=2)  // loop x
				{
					curPoint->setPosition( 
							rowx,
							(cornerAlt->getMod( x-_horizonDist+sx, z-_horizonDist+sz ) << _altitudeShift),
//							(minAlt->getMod( x-_horizonDist+sx, z-_horizonDist+sz )-2)<<9,
							pz
						);
					curPoint->setIMapCoords( imx, imz );
//TEMPCODE JON 6/1/00 					curPoint->info.setUnique();
//DEADCODE JON 5/24/00 					curPoint->y=(minAlt->getMod( x-_horizonDist+sx, z-_horizonDist+sz )-2)<<9;
//DEADCODE JON 5/24/00 					curPoint->x=rowx;
//DEADCODE JON 5/24/00 					curPoint->z=pz;
//DEADCODE JON 5/24/00 					curPoint->ix = imx;
//DEADCODE JON 5/24/00 					curPoint->iy = imz;
				}
			}

		} // end of update stored stuff 

		ULong flags[_horizonPoints*_horizonPoints];
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"SUVC: visiblecheck ");

		g_lpLib3d->VisibleCheck(horizPoint,_horizonPoints*_horizonPoints,flags);

		ULong *lowf=flags, *lowf2;

		bool *horizConePos = horizCone;

		int hirezGroundRadiusSq = viewer_y>>_blockShift; // using pythagarus
		hirezGroundRadiusSq*=-hirezGroundRadiusSq;
		hirezGroundRadiusSq+=((_wholeAreaSizeMIN)*(_wholeAreaSizeMIN));//(_halfAreaSizeMIN*_halfAreaSizeMIN);

		int hirezGroundRadiusSqMin = viewer_y>>_blockShift; // using pythagarus
		hirezGroundRadiusSqMin++;
		hirezGroundRadiusSqMin*=-hirezGroundRadiusSqMin;
		hirezGroundRadiusSqMin+=((_wholeAreaSizeMIN-1)*(_wholeAreaSizeMIN-1));//(_halfAreaSizeMIN*_halfAreaSizeMIN);
		

//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"SUVC: for sz ");
		for (int sz=0;sz<_horizonAreaSize;sz++)
		{
			lowf2=lowf;
			lowf+=_horizonPoints;
			for (int sx=0;sx<_horizonAreaSize;sx++,lowf2++,horizConePos++)
			{

//				ULong flag=lowf2[0]|lowf2[1]|lowf2[_horizonPoints]|lowf2[_horizonPoints+1];
				ULong flag=lowf2[0]&lowf2[1]&lowf2[_horizonPoints]&lowf2[_horizonPoints+1];
				if ( !flag )
				{ // draw this grid

					SWord dx = (sx<<1) - (_horizonPoints-1); // distance from center
					dx *= dx;
					SWord dz = (sz<<1) - (_horizonPoints-1); // distance from center
					dz *= dz;
					UWord distSq = dx+dz;  // dist from center squared
					
//DeadCode JON 14Sep00 					if ( distSq > ((_wholeAreaSizeMIN)*(_wholeAreaSizeMIN)) )
					if ( distSq > hirezGroundRadiusSq )
					{ // draw in a distant horizon tile at a later point
						*horizConePos = true;
					} else
					{  // set the flag 4 the hirez tile to be drawn

						const int FUDGE_VAL = 110; // enough to ensure an overlap...
//DeadCode JON 14Sep00 						if ( distSq >= ((_wholeAreaSizeMIN-1)*(_wholeAreaSizeMIN-1))-FUDGE_VAL)
						if ( distSq >= (hirezGroundRadiusSq)-FUDGE_VAL)
							*horizConePos = true;
						else
							*horizConePos = false;
						UWord ox = UWord( sx ); // offsets from the top of this grid
						UWord oz = UWord( sz );					
						ox -= ( (_horizonPoints-_wholeAreaSizeMIN) / 2 );
						oz -= ( (_horizonPoints-_wholeAreaSizeMIN) / 2 );
#ifndef NDEBUG
						static int minx = 100;
						static int minz = 100;
						static int maxx = 0;
						static int maxz = 0;
						if ( ox > maxx )
							maxx = ox;
						if ( ox < minx )
							minx = ox;
						if ( oz < minz )
							minz = oz;
						if ( oz > maxz )
							maxz = oz;
						int tmp = (oz*_wholeAreaSizeMIN) + ox;
						if ( (tmp<0) || (tmp >= _wholeAreaSizeMIN*_wholeAreaSizeMIN) )
							INT3; // oops we've gone off the grid.

						gridCone[ tmp ] = 1;
#else
						gridCone[ (oz*_wholeAreaSizeMIN) + ox ] = 1;
#endif
					}
				}
			}
		}
	} else
	{	// LOW DISTANCE HORIZON

//DeadCode MS 15Aug00 		Mono_Text.Print((UByte*)"SUVC: low distance horizon ");
		//  _wholeAreaSizeMIN
		if ( gridOffs.hasMoved( x, z ) ) // have we moved to a new block
		{
			ScrollTileGrid( x - gridOffs.jx, z - gridOffs.jz ); // move the texture tiles about
			gridOffs.set( x, z );

			UpdateCloseHorizCornerPoints( x, z );

		} // end of update stored stuff 


		ULong flags[_cornerLengthMIN*_cornerLengthMIN];

		g_lpLib3d->VisibleCheck(horizPoint,_cornerLengthMIN*_cornerLengthMIN,flags);

		ULong *lowf=flags, *lowf2;

		bool *gridConePos = (bool*)gridCone;

		for (int sz=0;sz<_wholeAreaSizeMIN;sz++)
		{
			lowf2=lowf;
			lowf+=_cornerLengthMIN;
			for (int sx=0;sx<_wholeAreaSizeMIN;sx++,lowf2++,gridConePos++)
			{

				ULong flag=lowf2[0]&lowf2[1]&lowf2[_cornerLengthMIN]&lowf2[_cornerLengthMIN+1];
				if ( !flag )
				{ // draw this grid
					*gridConePos = true;
				} else
				{
					*gridConePos = false;
				}
			}
		}

	}
	// remake any textures needed
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"SUVC: last test ");
	if (Land_Scape.UpdateTexturesWRTViewPos()==false &&
		Land_Scape.UpdateTexturesWRTViewPos()==false &&
		Land_Scape.UpdateTexturesWRTViewPos()==false)
	{
		RefreshLandscape();
		if ( !UpdateTexturesWRTViewPos() )
			assert(false&&"Unrecoverable landscape error");
	}
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"SUVC: stop\n");

	lastMeshDataX = x;
	lastMeshDataZ = z;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawHorizon
//Author		Jon.   
//Date			Thurs 27th Jan 2000
//------------------------------------------------------------------------------
void LandScape::DrawHorizon( void )
{
	if ( Save_Data.detail_3d[DETAIL3D_HORIZONDIST] )
	{ // HIGH DISTANCE HORIZON
		Lib3DPoint* cornerVert;

#ifndef _NO_UNDERGROUND_FILL
		const int NUM_FILL_BANDS = 3;

		const ULong dist = _blockWidth*_horizonDist;

		ULong zLayer = FORCE_TO_BACK_Z;
		g_lpLib3d->SetGlobal( TOGGLE_TEXTURE_ZBIAS, &zLayer );
		
		for ( int i = 1; i<=NUM_FILL_BANDS; i++ )
		{
			g_lpLib3d->SetFarClipPlane( float(_hirezDrawDist)*float(i)/float(NUM_FILL_BANDS) );
//DeadCode JON 3Nov00 			const int baseDepth = -700*100;
//DeadCode JON 3Nov00 			const int edgeDepth = -200*100;
//DeadCode JON 3Nov00 			// quick cheat - draw a plain poly across the base in order to cover up the nasty blue tears
//DeadCode JON 3Nov00 			cornerVert = g_lpLib3d->BeginPoly( HMATERIAL(47), 3 );
//DeadCode JON 3Nov00 			cornerVert[0].setPosition(
//DeadCode JON 3Nov00 				viewer_x-(dist),
//DeadCode JON 3Nov00 				edgeDepth,
//DeadCode JON 3Nov00 				viewer_z+(dist)
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert[1].setPosition(
//DeadCode JON 3Nov00 				viewer_x+(dist),
//DeadCode JON 3Nov00 				edgeDepth,
//DeadCode JON 3Nov00 				viewer_z+(dist)
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert[2].setPosition(
//DeadCode JON 3Nov00 				viewer_x,
//DeadCode JON 3Nov00 				baseDepth,
//DeadCode JON 3Nov00 				viewer_z
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 			g_lpLib3d->EndPoly();
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 3Nov00 			cornerVert[0].setPosition(
//DeadCode JON 3Nov00 				viewer_x+(dist),
//DeadCode JON 3Nov00 				edgeDepth,
//DeadCode JON 3Nov00 				viewer_z+(dist)
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert[1].setPosition(
//DeadCode JON 3Nov00 				viewer_x+(dist),
//DeadCode JON 3Nov00 				edgeDepth,
//DeadCode JON 3Nov00 				viewer_z-(dist)
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert[2].setPosition(
//DeadCode JON 3Nov00 				viewer_x,
//DeadCode JON 3Nov00 				baseDepth,
//DeadCode JON 3Nov00 				viewer_z
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 			g_lpLib3d->EndPoly();
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 3Nov00 			cornerVert[0].setPosition(
//DeadCode JON 3Nov00 				viewer_x+(dist),
//DeadCode JON 3Nov00 				edgeDepth,
//DeadCode JON 3Nov00 				viewer_z-(dist)
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert[1].setPosition(
//DeadCode JON 3Nov00 				viewer_x-(dist),
//DeadCode JON 3Nov00 				edgeDepth,
//DeadCode JON 3Nov00 				viewer_z-(dist)
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert[2].setPosition(
//DeadCode JON 3Nov00 				viewer_x,
//DeadCode JON 3Nov00 				baseDepth,
//DeadCode JON 3Nov00 				viewer_z
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 			g_lpLib3d->EndPoly();
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 3Nov00 			cornerVert[0].setPosition(
//DeadCode JON 3Nov00 				viewer_x-(dist),
//DeadCode JON 3Nov00 				edgeDepth,
//DeadCode JON 3Nov00 				viewer_z-(dist)
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert[1].setPosition(
//DeadCode JON 3Nov00 				viewer_x-(dist),
//DeadCode JON 3Nov00 				edgeDepth,
//DeadCode JON 3Nov00 				viewer_z+(dist)
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 			cornerVert[2].setPosition(
//DeadCode JON 3Nov00 				viewer_x,
//DeadCode JON 3Nov00 				baseDepth,
//DeadCode JON 3Nov00 				viewer_z
//DeadCode JON 3Nov00 			);
//DeadCode JON 3Nov00 			g_lpLib3d->EndPoly();
			
			cornerVert = g_lpLib3d->BeginPoly( HMATERIAL(47), 4 );
			cornerVert[0].setPosition(
				viewer_x-(dist),
				0.0f,
				viewer_z+(dist)
			);

			cornerVert[1].setPosition(
				viewer_x+(dist),
				0.0f,
				viewer_z+(dist)
			);

			cornerVert[2].setPosition(
				viewer_x+(dist),
				0.0f,
				viewer_z-(dist)
			);

			cornerVert[3].setPosition(
				viewer_x-(dist),
				0.0f,
				viewer_z-(dist)
			);

			g_lpLib3d->EndPoly();
			g_lpLib3d->SetNearClipPlane( float(_hirezDrawDist)*float(i)/float(NUM_FILL_BANDS) );
		}

		g_lpLib3d->SetFarClipPlane( dist );
		
		cornerVert = g_lpLib3d->BeginPoly( HMATERIAL(47), 4 );
		cornerVert[0].setPosition(
			viewer_x-(dist),
			0.0f,
			viewer_z+(dist)
		);

		cornerVert[1].setPosition(
			viewer_x+(dist),
			0.0f,
			viewer_z+(dist)
		);

		cornerVert[2].setPosition(
			viewer_x+(dist),
			0.0f,
			viewer_z-(dist)
		);

		cornerVert[3].setPosition(
			viewer_x-(dist),
			0.0f,
			viewer_z-(dist)
		);

		g_lpLib3d->EndPoly();

		// put the z layer back
		g_lpLib3d->SetGlobal( TOGGLE_TEXTURE_ZBIAS, zLayer );
		g_lpLib3d->FlushAsBackground();
#endif
		
		// calculate the current block position
//DeadCode JON 5Jul00 		int x = viewer_x>>Grid_Base::WORLDSPACEMOD;
//DeadCode JON 5Jul00 		int z = viewer_z>>Grid_Base::WORLDSPACEMOD;
		g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,(_hirezDrawDist-(_blockWidth*4)),view_dist,true);	//JON 29Aug00
//DeadCode JON 23Oct00 #ifndef _NO_UNDERGROUND_FILL
//DeadCode JON 23Oct00
//DeadCode JON 23Oct00 		const int baseDepth = -700*100;
//DeadCode JON 23Oct00 		const int edgeDepth = -200*100;
//DeadCode JON 23Oct00 		// quick cheat - draw a plain poly across the base in order to cover up the nasty blue tears
//DeadCode JON 23Oct00 		cornerVert = g_lpLib3d->BeginPoly( HMATERIAL(47), 3 );
//DeadCode JON 23Oct00 		cornerVert[0].setPosition(
//DeadCode JON 23Oct00 			viewer_x-(_blockWidth*_horizonDist),
//DeadCode JON 23Oct00 			edgeDepth,
//DeadCode JON 23Oct00 			viewer_z+(_blockWidth*_horizonDist)
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert[1].setPosition(
//DeadCode JON 23Oct00 			viewer_x+(_blockWidth*_horizonDist),
//DeadCode JON 23Oct00 			edgeDepth,
//DeadCode JON 23Oct00 			viewer_z+(_blockWidth*_horizonDist)
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert[2].setPosition(
//DeadCode JON 23Oct00 			viewer_x,
//DeadCode JON 23Oct00 			baseDepth,
//DeadCode JON 23Oct00 			viewer_z
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 		g_lpLib3d->EndPoly();
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 23Oct00 		cornerVert[0].setPosition(
//DeadCode JON 23Oct00 			viewer_x+(_blockWidth*_horizonDist),
//DeadCode JON 23Oct00 			edgeDepth,
//DeadCode JON 23Oct00 			viewer_z+(_blockWidth*_horizonDist)
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert[1].setPosition(
//DeadCode JON 23Oct00 			viewer_x+(_blockWidth*_horizonDist),
//DeadCode JON 23Oct00 			edgeDepth,
//DeadCode JON 23Oct00 			viewer_z-(_blockWidth*_horizonDist)
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert[2].setPosition(
//DeadCode JON 23Oct00 			viewer_x,
//DeadCode JON 23Oct00 			baseDepth,
//DeadCode JON 23Oct00 			viewer_z
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 		g_lpLib3d->EndPoly();
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 23Oct00 		cornerVert[0].setPosition(
//DeadCode JON 23Oct00 			viewer_x+(_blockWidth*_horizonDist),
//DeadCode JON 23Oct00 			edgeDepth,
//DeadCode JON 23Oct00 			viewer_z-(_blockWidth*_horizonDist)
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert[1].setPosition(
//DeadCode JON 23Oct00 			viewer_x-(_blockWidth*_horizonDist),
//DeadCode JON 23Oct00 			edgeDepth,
//DeadCode JON 23Oct00 			viewer_z-(_blockWidth*_horizonDist)
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert[2].setPosition(
//DeadCode JON 23Oct00 			viewer_x,
//DeadCode JON 23Oct00 			baseDepth,
//DeadCode JON 23Oct00 			viewer_z
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 		g_lpLib3d->EndPoly();
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 23Oct00 		cornerVert[0].setPosition(
//DeadCode JON 23Oct00 			viewer_x-(_blockWidth*_horizonDist),
//DeadCode JON 23Oct00 			edgeDepth,
//DeadCode JON 23Oct00 			viewer_z-(_blockWidth*_horizonDist)
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert[1].setPosition(
//DeadCode JON 23Oct00 			viewer_x-(_blockWidth*_horizonDist),
//DeadCode JON 23Oct00 			edgeDepth,
//DeadCode JON 23Oct00 			viewer_z+(_blockWidth*_horizonDist)
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 
//DeadCode JON 23Oct00 		cornerVert[2].setPosition(
//DeadCode JON 23Oct00 			viewer_x,
//DeadCode JON 23Oct00 			baseDepth,
//DeadCode JON 23Oct00 			viewer_z
//DeadCode JON 23Oct00 		);
//DeadCode JON 23Oct00 		g_lpLib3d->EndPoly();
//DeadCode JON 23Oct00 #endif

//DeadCode JON 21Aug00 		g_lpLib3d->DecGlobal( TOGGLE_TEXTURE_ZBIAS );

		bool *horizConePos = horizCone;
		DoPointStruc *offPos = horizPoint;
		// reset the copy count
		Lib3DPoint::CountAndCopyReset();

		for (int sz=0;sz<_horizonAreaSize;sz++,offPos++)
		{
			for (int sx=0;sx<_horizonAreaSize;sx++,horizConePos++,offPos++)
			{
				if ( *horizConePos )
				{ // draw in a distant horizon tile

//DEADCODE JON 6/1/00 					cornerVert = g_lpLib3d->BeginFan(HMATERIAL(horizonImg),4);
					cornerVert = g_lpLib3d->BeginPoly(HMATERIAL(horizonImg),4);

//DEADCODE JON 6/1/00 					cornerVert[0] = offPos[0];
//DEADCODE JON 6/1/00 					cornerVert[1]=offPos[_horizonPoints];
//DEADCODE JON 6/1/00 					cornerVert[2]=offPos[_horizonPoints+1];
//DEADCODE JON 6/1/00 					cornerVert[3]=offPos[1];
					cornerVert[0].CountAndCopy( offPos[0] );
					cornerVert[1].CountAndCopy( offPos[_horizonPoints] );
					cornerVert[2].CountAndCopy( offPos[_horizonPoints+1] );
					cornerVert[3].CountAndCopy( offPos[1] );
				
					g_lpLib3d->EndPoly();
//DEADCODE JON 6/1/00 					g_lpLib3d->EndFan();

				} 
			}
		}
		g_lpLib3d->FlushAsBackground();
		g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,10,view_dist,true);
//		g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,10,_hirezDrawDist+(_blockWidth*2),true);	//JON 29Aug00
	} else
	{ // close horizon distance
#ifndef _NO_UNDERGROUND_FILL
		const D3DVALUE baseY = 0.0f;
		Lib3DPoint* cornerVert;
		
		const ULong dist = _hirezDrawDist;

		const int NUM_FILL_BANDS = 3;

		ULong zLayer = FORCE_TO_BACK_Z;
		g_lpLib3d->SetGlobal( TOGGLE_TEXTURE_ZBIAS, &zLayer );
		
		for ( int i = 1; i<=NUM_FILL_BANDS; i++ )
		{
			g_lpLib3d->SetFarClipPlane( float(dist)*float(i)/float(NUM_FILL_BANDS) );

//DeadCode JON 3Nov00 		const int baseDepth = -700*100;
//DeadCode JON 3Nov00 		const int edgeDepth = -200*100;
//DeadCode JON 3Nov00 		// quick cheat - draw a plain poly across the base in order to cover up the nasty blue tears
//DeadCode JON 3Nov00 		cornerVert = g_lpLib3d->BeginPoly( HMATERIAL(47), 3 );
//DeadCode JON 3Nov00 		cornerVert[0].setPosition(
//DeadCode JON 3Nov00 			viewer_x-(dist),
//DeadCode JON 3Nov00 			edgeDepth,
//DeadCode JON 3Nov00 			viewer_z+(dist)
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert[1].setPosition(
//DeadCode JON 3Nov00 			viewer_x+(dist),
//DeadCode JON 3Nov00 			edgeDepth,
//DeadCode JON 3Nov00 			viewer_z+(dist)
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert[2].setPosition(
//DeadCode JON 3Nov00 			viewer_x,
//DeadCode JON 3Nov00 			baseDepth,
//DeadCode JON 3Nov00 			viewer_z
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 		g_lpLib3d->EndPoly();
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 3Nov00 		cornerVert[0].setPosition(
//DeadCode JON 3Nov00 			viewer_x+(dist),
//DeadCode JON 3Nov00 			edgeDepth,
//DeadCode JON 3Nov00 			viewer_z+(dist)
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert[1].setPosition(
//DeadCode JON 3Nov00 			viewer_x+(dist),
//DeadCode JON 3Nov00 			edgeDepth,
//DeadCode JON 3Nov00 			viewer_z-(dist)
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert[2].setPosition(
//DeadCode JON 3Nov00 			viewer_x,
//DeadCode JON 3Nov00 			baseDepth,
//DeadCode JON 3Nov00 			viewer_z
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 		g_lpLib3d->EndPoly();
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 3Nov00 		cornerVert[0].setPosition(
//DeadCode JON 3Nov00 			viewer_x+(dist),
//DeadCode JON 3Nov00 			edgeDepth,
//DeadCode JON 3Nov00 			viewer_z-(dist)
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert[1].setPosition(
//DeadCode JON 3Nov00 			viewer_x-(dist),
//DeadCode JON 3Nov00 			edgeDepth,
//DeadCode JON 3Nov00 			viewer_z-(dist)
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert[2].setPosition(
//DeadCode JON 3Nov00 			viewer_x,
//DeadCode JON 3Nov00 			baseDepth,
//DeadCode JON 3Nov00 			viewer_z
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 		g_lpLib3d->EndPoly();
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert = g_lpLib3d->BeginPoly( 3 );
//DeadCode JON 3Nov00 		cornerVert[0].setPosition(
//DeadCode JON 3Nov00 			viewer_x-(dist),
//DeadCode JON 3Nov00 			edgeDepth,
//DeadCode JON 3Nov00 			viewer_z-(dist)
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert[1].setPosition(
//DeadCode JON 3Nov00 			viewer_x-(dist),
//DeadCode JON 3Nov00 			edgeDepth,
//DeadCode JON 3Nov00 			viewer_z+(dist)
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 
//DeadCode JON 3Nov00 		cornerVert[2].setPosition(
//DeadCode JON 3Nov00 			viewer_x,
//DeadCode JON 3Nov00 			baseDepth,
//DeadCode JON 3Nov00 			viewer_z
//DeadCode JON 3Nov00 		);
//DeadCode JON 3Nov00 		g_lpLib3d->EndPoly();
			
			cornerVert = g_lpLib3d->BeginPoly( HMATERIAL(47), 4 );
			cornerVert[0].setPosition(
				viewer_x-(dist),
				baseY,
				viewer_z+(dist)
			);

			cornerVert[1].setPosition(
				viewer_x+(dist),
				baseY,
				viewer_z+(dist)
			);

			cornerVert[2].setPosition(
				viewer_x+(dist),
				baseY,
				viewer_z-(dist)
			);

			cornerVert[3].setPosition(
				viewer_x-(dist),
				baseY,
				viewer_z-(dist)
			);

			g_lpLib3d->EndPoly();

			g_lpLib3d->SetNearClipPlane( float(dist)*float(i)/float(NUM_FILL_BANDS) );
		}

		// put the z layer back
		g_lpLib3d->SetGlobal( TOGGLE_TEXTURE_ZBIAS, zLayer );

		g_lpLib3d->ResetClipDistances();
		g_lpLib3d->FlushAsBackground();
#endif

	}
}

// will actually draw the cloud layer - needs the correct matrices etc set up.
inline void LandScape::DrawCloudLayer( const int hx, const int hz, D3DVECTOR* pos, const bool clockWise )
{
	// calculate the current block position
	const int x = gridOffs.jx;
	const int z = gridOffs.jz;

	ULong flags[_horizonPoints*_horizonPoints];
	
	g_lpLib3d->VisibleCheck(pos,_horizonPoints*_horizonPoints,flags);

	ULong *lowf=flags, *lowf2;
	D3DVECTOR *lowptr = pos, *lowptr2;

	int imx,imz,rowStart; // image map coords

	imz = (((z-(_horizonDist))-hz)+64);
	rowStart = (((x-(_horizonDist))-hx)+64);


	for (int sz=_horizonAreaSize;sz!=0;sz--,imz++)
	{
		lowf2=lowf;
		lowf+=_horizonPoints;
		lowptr2=lowptr; 
		lowptr+=_horizonPoints;
		imx = rowStart; 
		for (int sx=_horizonAreaSize;sx!=0;sx--,lowf2++,lowptr2++,imx++)
		{
			ULong flag=lowf2[0]&lowf2[1]&lowf2[_horizonPoints]&lowf2[_horizonPoints+1];
			if ( !flag )
			{ // draw this grid

				Lib3DPoint* cornerVert = g_lpLib3d->BeginFan(4);
				if ( clockWise )
				{
					cornerVert[0].setPosition(
							lowptr2[0].x,
		 					lowptr2[0].y,
							lowptr2[0].z
						);
					cornerVert[0].setIMapCoords( imx, imz );
					cornerVert[0].setIMapCoords1( 0, 0 );

					cornerVert[1].setPosition(
							lowptr2[_horizonPoints].x,
		 					lowptr2[_horizonPoints].y,
							lowptr2[_horizonPoints].z
						);
					cornerVert[1].setIMapCoords( imx, imz+1 );
					cornerVert[1].setIMapCoords1( 0, 255 );

					cornerVert[2].setPosition(
							lowptr2[_horizonPoints+1].x,
		 					lowptr2[_horizonPoints+1].y,
							lowptr2[_horizonPoints+1].z
						);
					cornerVert[2].setIMapCoords( imx+1, imz+1 );
					cornerVert[2].setIMapCoords1( 255, 255 );

					cornerVert[3].setPosition(
							lowptr2[1].x,
		 					lowptr2[1].y,
							lowptr2[1].z
						);
					cornerVert[3].setIMapCoords( imx+1, imz );
					cornerVert[3].setIMapCoords1( 255, 0 );
				} else
				{
					cornerVert[3].setPosition(
							lowptr2[0].x,
		 					lowptr2[0].y,
							lowptr2[0].z
						);
					cornerVert[3].setIMapCoords( imx, imz );
					cornerVert[3].setIMapCoords1( 0, 0 );

					cornerVert[2].setPosition(
							lowptr2[_horizonPoints].x,
		 					lowptr2[_horizonPoints].y,
							lowptr2[_horizonPoints].z
						);
					cornerVert[2].setIMapCoords( imx, imz+1 );
					cornerVert[2].setIMapCoords1( 0, 255 );

					cornerVert[1].setPosition(
							lowptr2[_horizonPoints+1].x,
		 					lowptr2[_horizonPoints+1].y,
							lowptr2[_horizonPoints+1].z
						);
					cornerVert[1].setIMapCoords( imx+1, imz+1 );
					cornerVert[1].setIMapCoords1( 255, 255 );

					cornerVert[0].setPosition(
							lowptr2[1].x,
		 					lowptr2[1].y,
							lowptr2[1].z
						);
					cornerVert[0].setIMapCoords( imx+1, imz );
					cornerVert[0].setIMapCoords1( 255, 0 );
				}
				g_lpLib3d->EndFan();				
			}
		}
	}
}

void LandScape::DistDrawClouds(SLong layerNumber )
{
	ImageMapDescPtr cloudImg;
	SLong layerAltitude, halfLayerWidth;
	SLong xoff,zoff;
	UByte side;			//0=in, 1=above, 2=below


//TempCode JON 25Sep00 	switch (layerNumber)
//TempCode JON 25Sep00 	{
//TempCode JON 25Sep00 	case 0:
		cloudImg=cloudImg0;
		xoff=zoff=0;
//		layerAltitude=FT_5000;
		layerAltitude =	(MissManCampSky().Layer[0].AltBase + MissManCampSky().Layer[0].AltTop)>>1;
		halfLayerWidth = (MissManCampSky().Layer[0].AltTop - MissManCampSky().Layer[0].AltBase)>>1;
//TempCode JON 25Sep00 		break;
//TempCode JON 25Sep00 	case 1:
//TempCode JON 25Sep00 		cloudImg=cloudImg1;
//TempCode JON 25Sep00 		xoff=zoff=131072*32;
//TempCode JON 25Sep00 		layerAltitude=FT_10000;
//TempCode JON 25Sep00 		break;
//TempCode JON 25Sep00 	case 2:
//TempCode JON 25Sep00 	default:
//TempCode JON 25Sep00 		cloudImg=cloudImg2;
//TempCode JON 25Sep00 		xoff=zoff=-131072*32;
//TempCode JON 25Sep00 		layerAltitude=FT_15000;
//TempCode JON 25Sep00 		break;
//TempCode JON 25Sep00 	}

	if (layerAltitude <=0)
	{
		return;
	}

	// calculate the current block position
	int x = gridOffs.jx;
	int z = gridOffs.jz;

//DeadCode JON 27Sep00 	static int hx = -1;
//DeadCode JON 27Sep00 	static int hz = -1;
//DeadCode JON 27Sep00 	static int jx = -1;
//DeadCode JON 27Sep00 	static int jz = -1;
	static 	D3DVECTOR pos[_horizonPoints*_horizonPoints];

	if ( cloudOffs.hasMoved( x, z ) )
	{
//DeadCode JON 27Sep00 		jx = x;
//DeadCode JON 27Sep00 		jz = z;
		cloudOffs.set( x, z );

		// do we need to redo the imagemap?
//DeadCode JON 27Sep00 		if ( x < hx-4 || x > hx+4 || z<hz-4 || z>hz+4 )
		if ( cloudOffs.needColMapUpdate( x, z ) )
		{ // we need to recalculate the imagemap	
			// unload the old one from the card.
			g_lpLib3d->UnloadTexture( cloudImg );

			Grid_Byte* col = (Grid_Byte*) Grid_Base::gridfiles[Grid_Base::GF_CLOUDLAYER0].getdata();
			UByte* t = cloudImg->alpha;
			for ( int sz = z-64; sz < z+64; sz++ )
				for ( int sx = x-64; sx < x+64; sx++ )
				{
					*t++ = ((col->getMod( sx, sz )));
				}
			cloudOffs.setColMapCoords( x, z );
		}

		// recalc cloudlayer vertex points
		//Generate start position based on the current viewpoint
		SLong px,pz;
		px = (x-_horizonDist)<<Grid_Base::WORLDSPACEMOD;
		pz = (z-_horizonDist)<<Grid_Base::WORLDSPACEMOD;

		D3DVECTOR lpos,mpos,*lowptr;
		SLong lx,lz,mx;
		lowptr=pos;
		lx=px;
		lz=pz;
		lpos.x=lx;
		lpos.z=lz;

		// get the grid data 4 min altitudes
		Grid_Base* minAlt = (Grid_Base*) Grid_Base::gridfiles[Grid_Base::GF_CLOUDLAYER0].getdata();

		for (int sz=0; sz<_horizonPoints;sz++) // loop tru z
		{
			mpos=lpos;
			mx=lx;	
			for (int sx=0;sx<_horizonPoints;sx++) // loop x
			{
				SLong min;
				min = (minAlt->getMod( x-_horizonDist+sx, z-_horizonDist+sz )<<4);
				*lowptr=mpos;
				lowptr->y=min;
				mpos.x+=_blockWidth;
				mx+=_blockWidth;
				lowptr++;
			}
			lpos.z+=_blockWidth;
			lz+=_blockWidth;
		}

	
	}

	const int DOUBLE_SIDED_LAYER_DISTANCE = 10000; //cm

	g_lpLib3d->SetMaterial(HMATERIAL(cloudImg,Image_Map.GetImageMapPtr(CLOUDNO)));
//TempCode JON 26Sep00 	LIGHTFLAG lf = LF_DEPTH;
//TempCode JON 26Sep00 	g_lpLib3d->SetObjectLighting( lf );

	// find out if we are above, below or inside the clouds.
//	if ( (( layerAltitude - viewer_y )&0x7FFFFF) < SLong( pos[(_horizonPoints*_horizonPoints)/2].y ) + halfLayerWidth )
	if (	viewer_y < layerAltitude+(halfLayerWidth+DOUBLE_SIDED_LAYER_DISTANCE) && 
			viewer_y > layerAltitude-(halfLayerWidth+DOUBLE_SIDED_LAYER_DISTANCE) )	
	{ // we're inside the clouds..
	// inside
		// bottom
		// now modify the object matrix to make the transformation for viewer_x,y and z happen... (simple
		// translations) - this is as the object matrix is used before the viewer matrix - makes the clouds be at the right altitude
		g_lpLib3d->PushMatrix( MATRIX_OBJECT );
		g_lpLib3d->LoadIdentity( MATRIX_OBJECT );


		D3DVECTOR viewMods;
		viewMods.x=D3DVALUE(1);
		viewMods.y=D3DVALUE(-1);
		viewMods.z=D3DVALUE(1);
		g_lpLib3d->Scale( MATRIX_OBJECT, viewMods );
		
		viewMods.x=(D3DVALUE)-viewer_x;
		viewMods.y=-(((D3DVALUE)viewer_y)-(D3DVALUE(layerAltitude-halfLayerWidth)));
		viewMods.z=(D3DVALUE)-viewer_z;
		g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

		DrawCloudLayer( cloudOffs.hx, cloudOffs.hz, pos, true );
		if ( viewer_y < layerAltitude )
			DrawCloudLayer( cloudOffs.hx, cloudOffs.hz, pos, false );

		g_lpLib3d->PopMatrix( MATRIX_OBJECT );


		// now modify the object matrix to make the transformation for viewer_x,y and z happen... (simple
		// translations) - this is as the object matrix is used before the viewer matrix - makes the clouds be at the right altitude
		g_lpLib3d->LoadIdentity( MATRIX_OBJECT );

		viewMods.x=(D3DVALUE)-viewer_x;
		viewMods.y=-(((D3DVALUE)viewer_y)-D3DVALUE(layerAltitude+halfLayerWidth));
		viewMods.z=(D3DVALUE)-viewer_z;
		g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

		DrawCloudLayer( cloudOffs.hx, cloudOffs.hz, pos, false );
		if ( viewer_y > layerAltitude )
			DrawCloudLayer( cloudOffs.hx, cloudOffs.hz, pos, true );

		g_lpLib3d->PopMatrix( MATRIX_OBJECT );
	} else if( viewer_y < layerAltitude )
	{
		// below
		// now modify the object matrix to make the transformation for viewer_x,y and z happen... (simple
		// translations) - this is as the object matrix is used before the viewer matrix - makes the clouds be at the right altitude
		g_lpLib3d->PushMatrix( MATRIX_OBJECT );
		g_lpLib3d->LoadIdentity( MATRIX_OBJECT );


		D3DVECTOR viewMods;
		viewMods.x=D3DVALUE(1);
		viewMods.y=D3DVALUE(-1);
		viewMods.z=D3DVALUE(1);
		g_lpLib3d->Scale( MATRIX_OBJECT, viewMods );
		
		viewMods.x=(D3DVALUE)-viewer_x;
		viewMods.y=-(((D3DVALUE)viewer_y)-(D3DVALUE(layerAltitude-halfLayerWidth)));
		viewMods.z=(D3DVALUE)-viewer_z;
		g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

		DrawCloudLayer( cloudOffs.hx, cloudOffs.hz, pos, false );
		g_lpLib3d->PopMatrix( MATRIX_OBJECT );
	} else
	{
		// above
		// now modify the object matrix to make the transformation for viewer_x,y and z happen... (simple
		// translations) - this is as the object matrix is used before the viewer matrix - makes the clouds be at the right altitude
		g_lpLib3d->PushMatrix( MATRIX_OBJECT );
		g_lpLib3d->LoadIdentity( MATRIX_OBJECT );


		D3DVECTOR viewMods;
		viewMods.x=(D3DVALUE)-viewer_x;
		viewMods.y=-(((D3DVALUE)viewer_y)-D3DVALUE(layerAltitude+halfLayerWidth));
		viewMods.z=(D3DVALUE)-viewer_z;
		g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

		DrawCloudLayer( cloudOffs.hx, cloudOffs.hz, pos, true );
		g_lpLib3d->PopMatrix( MATRIX_OBJECT );
	}

//TempCode JON 26Sep00 	g_lpLib3d->SetObjectLighting( lf );

}


//DeadCode JON 31Jul00 void LandScape::DistDrawClouds(SLong layerNumber )
//DeadCode JON 31Jul00 {
//DeadCode JON 31Jul00 	ImageMapDescPtr cloudImg;
//DeadCode JON 31Jul00 	SLong layerAltitude;
//DeadCode JON 31Jul00 	SLong xoff,zoff;
//DeadCode JON 31Jul00 	UByte side;			//0=in, 1=above, 2=below
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	switch (layerNumber)
//DeadCode JON 31Jul00 	{
//DeadCode JON 31Jul00 	case 0:
//DeadCode JON 31Jul00 		cloudImg=cloudImg0;
//DeadCode JON 31Jul00 		xoff=zoff=0;
//DeadCode JON 31Jul00 		layerAltitude=FT_5000;
//DeadCode JON 31Jul00 		break;
//DeadCode JON 31Jul00 	case 1:
//DeadCode JON 31Jul00 		cloudImg=cloudImg1;
//DeadCode JON 31Jul00 		xoff=zoff=131072*32;
//DeadCode JON 31Jul00 		layerAltitude=FT_10000;
//DeadCode JON 31Jul00 		break;
//DeadCode JON 31Jul00 	case 2:
//DeadCode JON 31Jul00 	default:
//DeadCode JON 31Jul00 		cloudImg=cloudImg2;
//DeadCode JON 31Jul00 		xoff=zoff=-131072*32;
//DeadCode JON 31Jul00 		layerAltitude=FT_15000;
//DeadCode JON 31Jul00 		break;
//DeadCode JON 31Jul00 	}
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	if (viewer_y>layerAltitude+FT_500)
//DeadCode JON 31Jul00 	{
//DeadCode JON 31Jul00 		side=1;		//above
//DeadCode JON 31Jul00 	} else if (viewer_y<layerAltitude-FT_500)		
//DeadCode JON 31Jul00 	{
//DeadCode JON 31Jul00 		side=2;		//below
//DeadCode JON 31Jul00 //		g_lpLib3d->SetGlobal( TOGGLE_GLOBALALPHA, 3 );//255-8 ); // make them more seethru when below...
//DeadCode JON 31Jul00 	} else
//DeadCode JON 31Jul00 	{
//DeadCode JON 31Jul00 		side=0;		//in
//DeadCode JON 31Jul00 	}
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	// calculate the current block position
//DeadCode JON 31Jul00 //	int x = viewer_x>>Grid_Base::WORLDSPACEMOD;
//DeadCode JON 31Jul00 //	int z = viewer_z>>Grid_Base::WORLDSPACEMOD;
//DeadCode JON 31Jul00 	int x = gridOffs.jx;
//DeadCode JON 31Jul00 	int z = gridOffs.jz;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	static int hx = -1;
//DeadCode JON 31Jul00 	static int hz = -1;
//DeadCode JON 31Jul00 	static int jx = -1;
//DeadCode JON 31Jul00 	static int jz = -1;
//DeadCode JON 31Jul00 	static 	D3DVECTOR pos[_horizonPoints*_horizonPoints];
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	if ( x != jx || z != jz )
//DeadCode JON 31Jul00 	{
//DeadCode JON 31Jul00 		jx = x;
//DeadCode JON 31Jul00 		jz = z;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 		// do we need to redo the imagemap?
//DeadCode JON 31Jul00 		if ( x < hx-4 || x > hx+4 || z<hz-4 || z>hz+4 )
//DeadCode JON 31Jul00 		{ // we need to recalculate the imagemap	
//DeadCode JON 31Jul00 			// unload the old one from the card.
//DeadCode JON 31Jul00 			g_lpLib3d->UnloadTexture( cloudImg );
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 //DEADCODE JIM 25/05/00 			fileblock fb( FIL_4COLGRID, Grid_Base::makeGridAt );
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 			Grid_Long* colD = (Grid_Long*) Grid_Base::gridfiles[Grid_Base::GF_COLOUR]->getdata();
//DeadCode JON 31Jul00 			Grid_Byte* col = (Grid_Byte*) Grid_Base::gridfiles[Grid_Base::GF_CLOUDLAYER0].getdata();
//DeadCode JON 31Jul00 //DEADCODE JIM 25/05/00 			Grid_Long* colD = (Grid_Long*) fb.getdata();
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 			UByte* t = ((UByte*)cloudImg)+sizeof(*cloudImg);
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 			for ( int sz = (z<<1)-128; sz < (z<<1)+128; sz++ )
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 				for ( int sx = (x<<1)-128; sx < (x<<1)+128; sx++ )
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 				{
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 					*t++ = ((colD->getModD( sx, sz )<<3)|0x07)+8;
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 				}
//DeadCode JON 31Jul00 			UByte* t = ((UByte*)cloudImg)+sizeof(*cloudImg);
//DeadCode JON 31Jul00 			for ( int sz = z-64; sz < z+64; sz++ )
//DeadCode JON 31Jul00 				for ( int sx = x-64; sx < x+64; sx++ )
//DeadCode JON 31Jul00 				{
//DeadCode JON 31Jul00 					*t++ = ((col->getMod( sx, sz )));//<<3)|0x07)+8;
//DeadCode JON 31Jul00 //					*t++ = 128;
//DeadCode JON 31Jul00 //					*t++ = ((col->getMod( sx, sz )<<3)|0x07)+8;
//DeadCode JON 31Jul00 				}
//DeadCode JON 31Jul00 			hx = x;
//DeadCode JON 31Jul00 			hz = z;
//DeadCode JON 31Jul00 		}
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 		// recalc horizon vertex points
//DeadCode JON 31Jul00 		//Generate start position based on the current viewpoint
//DeadCode JON 31Jul00 		SLong px,pz;
//DeadCode JON 31Jul00 		px = (x-_horizonDist)<<Grid_Base::WORLDSPACEMOD;
//DeadCode JON 31Jul00 		pz = (z-_horizonDist)<<Grid_Base::WORLDSPACEMOD;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 		D3DVECTOR lpos,mpos,*lowptr;
//DeadCode JON 31Jul00 		SLong lx,lz,mx;
//DeadCode JON 31Jul00 		lowptr=pos;
//DeadCode JON 31Jul00 		lx=px;
//DeadCode JON 31Jul00 		lz=pz;
//DeadCode JON 31Jul00 		lpos.x=lx;
//DeadCode JON 31Jul00 		lpos.z=lz;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 		// get the grid data 4 min altitudes
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 		fileblock fb1( FIL_MINALT, Grid_Base::makeGridAt );
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 		Grid_Base* minAlt = (Grid_Base*) fb1.getdata();
//DeadCode JON 31Jul00 		Grid_Base* minAlt = (Grid_Base*) Grid_Base::gridfiles[Grid_Base::GF_CLOUDLAYER0].getdata();
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 		for (int sz=0; sz<_horizonPoints;sz++) // loop tru z
//DeadCode JON 31Jul00 		{
//DeadCode JON 31Jul00 			mpos=lpos;
//DeadCode JON 31Jul00 			mx=lx;	
//DeadCode JON 31Jul00 			for (int sx=0;sx<_horizonPoints;sx++) // loop x
//DeadCode JON 31Jul00 			{
//DeadCode JON 31Jul00 				SLong min;
//DeadCode JON 31Jul00 				min = layerAltitude+(minAlt->getMod( x-_horizonDist+sx, z-_horizonDist+sz )<<5);
//DeadCode JON 31Jul00 				*lowptr=mpos;
//DeadCode JON 31Jul00 				lowptr->y=min;
//DeadCode JON 31Jul00 				mpos.x+=_blockWidth;
//DeadCode JON 31Jul00 				mx+=_blockWidth;
//DeadCode JON 31Jul00 				lowptr++;
//DeadCode JON 31Jul00 			}
//DeadCode JON 31Jul00 			lpos.z+=_blockWidth;
//DeadCode JON 31Jul00 			lz+=_blockWidth;
//DeadCode JON 31Jul00 		}
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	
//DeadCode JON 31Jul00 	}
//DeadCode JON 31Jul00 	// right now we need to make a mesh for the distant hills and paste the horizon imagemap down onto it...
//DeadCode JON 31Jul00 	// find out which blocks need to be used to make the hill mesh.
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	const int CLOUD_REDUCTION = 5;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	ULong flags[_horizonPoints*_horizonPoints];
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 //	g_lpLib3d->PushMatrix( MATRIX_PROJECTION );
//DeadCode JON 31Jul00 	g_lpLib3d->SetProjectionMatrix( (Angles)(int)Save_Data.fieldOfView,1,100,_blockWidth*(_horizonDist-CLOUD_REDUCTION),true );
//DeadCode JON 31Jul00 	g_lpLib3d->VisibleCheck(pos,_horizonPoints*_horizonPoints,flags);
//DeadCode JON 31Jul00 	g_lpLib3d->SetProjectionMatrix( (Angles)(int)Save_Data.fieldOfView,1,100,view_dist);
//DeadCode JON 31Jul00 //	g_lpLib3d->PopMatrix( MATRIX_PROJECTION );
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	// now modify the object matrix to make the transformation for viewer_x,y and z happen... (simple
//DeadCode JON 31Jul00 	// translations) - this is as the object matrix is used before the viewer matrix
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 //	const int CLOUDRADIUS = _horizonDist - CLOUD_REDUCTION;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	ULong *lowf=flags, *lowf2;
//DeadCode JON 31Jul00 	D3DVECTOR *lowptr = pos, *lowptr2;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	int imx,imz,rowStart; // image map coords
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 	imz = (((z-(_horizonDist))-hz)+64)<<1;
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 	rowStart = (((x-(_horizonDist))-hx)+64)<<1;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	imz = (((z-(_horizonDist))-hz)+64);
//DeadCode JON 31Jul00 	rowStart = (((x-(_horizonDist))-hx)+64);
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 //TEMPCODE JON 5/3/00 	imz = (((z-(CLOUDRADIUS))-hz)+64)<<1;
//DeadCode JON 31Jul00 //TEMPCODE JON 5/3/00 	rowStart = (((x-(CLOUDRADIUS))-hx)+64)<<1;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 //TEMPCODE JON 5/3/00 	lowptr+=(_horizonPoints*CLOUD_REDUCTION)+CLOUD_REDUCTION;
//DeadCode JON 31Jul00 //TEMPCODE JON 5/3/00 	lowf+=(_horizonPoints*CLOUD_REDUCTION)+CLOUD_REDUCTION;
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 	HMATERIAL cloudMaterial(cloudImg,Image_Map.GetImageMapPtr(CLOUDNO));
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 //TEMPCODE JON 5/3/00 	for (int sz=CLOUDRADIUS*2+1;sz!=0;sz--,imz+=2)
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 	for (int sz=_horizonAreaSize;sz!=0;sz--,imz+=2)
//DeadCode JON 31Jul00 	for (int sz=_horizonAreaSize;sz!=0;sz--,imz++)
//DeadCode JON 31Jul00 	{
//DeadCode JON 31Jul00 		lowf2=lowf;
//DeadCode JON 31Jul00 		lowf+=_horizonPoints;
//DeadCode JON 31Jul00 		lowptr2=lowptr; 
//DeadCode JON 31Jul00 		lowptr+=_horizonPoints;
//DeadCode JON 31Jul00 		imx = rowStart; 
//DeadCode JON 31Jul00 //TEMPCODE JON 5/3/00 		for (int sx=CLOUDRADIUS*2+1;sx!=0;sx--,lowf2++,lowptr2++,imx+=2)
//DeadCode JON 31Jul00 //		for (int sx=_horizonAreaSize;sx!=0;sx--,lowf2++,lowptr2++,imx+=2)
//DeadCode JON 31Jul00 		for (int sx=_horizonAreaSize;sx!=0;sx--,lowf2++,lowptr2++,imx++)
//DeadCode JON 31Jul00 		{
//DeadCode JON 31Jul00 			ULong flag=lowf2[0]&lowf2[1]&lowf2[_horizonPoints]&lowf2[_horizonPoints+1];
//DeadCode JON 31Jul00 			if ( !flag )
//DeadCode JON 31Jul00 			{ // draw this grid
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 				//top
//DeadCode JON 31Jul00 				if (side!=2)
//DeadCode JON 31Jul00 				{
//DeadCode JON 31Jul00 					Lib3DPoint* cornerVert = g_lpLib3d->BeginFan(cloudMaterial,4);
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 					cornerVert[0].setPosition(
//DeadCode JON 31Jul00 							lowptr2[0].x,
//DeadCode JON 31Jul00 		 					lowptr2[0].y,
//DeadCode JON 31Jul00 							lowptr2[0].z
//DeadCode JON 31Jul00 						);
//DeadCode JON 31Jul00 					cornerVert[0].setIMapCoords( imx, imz );
//DeadCode JON 31Jul00 					cornerVert[0].setIMapCoords1( 0, 0 );
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 					cornerVert[1].setPosition(
//DeadCode JON 31Jul00 							lowptr2[_horizonPoints].x,
//DeadCode JON 31Jul00 		 					lowptr2[_horizonPoints].y,
//DeadCode JON 31Jul00 							lowptr2[_horizonPoints].z
//DeadCode JON 31Jul00 						);
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 					cornerVert[1].setIMapCoords( imx, imz+2 );
//DeadCode JON 31Jul00 					cornerVert[1].setIMapCoords( imx, imz+1 );
//DeadCode JON 31Jul00 					cornerVert[1].setIMapCoords1( 0, 255 );
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 					cornerVert[2].setPosition(
//DeadCode JON 31Jul00 							lowptr2[_horizonPoints+1].x,
//DeadCode JON 31Jul00 		 					lowptr2[_horizonPoints+1].y,
//DeadCode JON 31Jul00 							lowptr2[_horizonPoints+1].z
//DeadCode JON 31Jul00 						);
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 					cornerVert[2].setIMapCoords( imx+2, imz+2 );
//DeadCode JON 31Jul00 					cornerVert[2].setIMapCoords( imx+1, imz+1 );
//DeadCode JON 31Jul00 					cornerVert[2].setIMapCoords1( 255, 255 );
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 					cornerVert[3].setPosition(
//DeadCode JON 31Jul00 							lowptr2[1].x,
//DeadCode JON 31Jul00 		 					lowptr2[1].y,
//DeadCode JON 31Jul00 							lowptr2[1].z
//DeadCode JON 31Jul00 						);
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 					cornerVert[3].setIMapCoords( imx+2, imz );
//DeadCode JON 31Jul00 					cornerVert[3].setIMapCoords( imx+1, imz );
//DeadCode JON 31Jul00 					cornerVert[3].setIMapCoords1( 255, 0 );
//DeadCode JON 31Jul00 					g_lpLib3d->EndFan();
//DeadCode JON 31Jul00 				}
//DeadCode JON 31Jul00 				//bottom
//DeadCode JON 31Jul00 				if (side!=1)
//DeadCode JON 31Jul00 				{
//DeadCode JON 31Jul00 					Lib3DPoint* cornerVert = g_lpLib3d->BeginFan(cloudMaterial,4);
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 					cornerVert[3].setPosition(
//DeadCode JON 31Jul00 							lowptr2[0].x,
//DeadCode JON 31Jul00 		 					lowptr2[0].y,
//DeadCode JON 31Jul00 							lowptr2[0].z
//DeadCode JON 31Jul00 						);
//DeadCode JON 31Jul00 					cornerVert[3].setIMapCoords( imx, imz );
//DeadCode JON 31Jul00 					cornerVert[3].setIMapCoords1( 0, 0 );
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 					cornerVert[2].setPosition(
//DeadCode JON 31Jul00 							lowptr2[_horizonPoints].x,
//DeadCode JON 31Jul00 		 					lowptr2[_horizonPoints].y,
//DeadCode JON 31Jul00 							lowptr2[_horizonPoints].z
//DeadCode JON 31Jul00 						);
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 					cornerVert[2].setIMapCoords( imx, imz+2 );
//DeadCode JON 31Jul00 					cornerVert[2].setIMapCoords( imx, imz+1 );
//DeadCode JON 31Jul00 					cornerVert[2].setIMapCoords1( 0, 255 );
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 					cornerVert[1].setPosition(
//DeadCode JON 31Jul00 							lowptr2[_horizonPoints+1].x,
//DeadCode JON 31Jul00 		 					lowptr2[_horizonPoints+1].y,
//DeadCode JON 31Jul00 							lowptr2[_horizonPoints+1].z
//DeadCode JON 31Jul00 						);
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 					cornerVert[1].setIMapCoords( imx+2, imz+2 );
//DeadCode JON 31Jul00 					cornerVert[1].setIMapCoords( imx+1, imz+1 );
//DeadCode JON 31Jul00 					cornerVert[1].setIMapCoords1( 255, 255 );
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 					cornerVert[0].setPosition(
//DeadCode JON 31Jul00 							lowptr2[1].x,
//DeadCode JON 31Jul00 		 					lowptr2[1].y,
//DeadCode JON 31Jul00 							lowptr2[1].z
//DeadCode JON 31Jul00 						);
//DeadCode JON 31Jul00 //DeadCode JON 9Jun00 					cornerVert[0].setIMapCoords( imx+2, imz );
//DeadCode JON 31Jul00 					cornerVert[0].setIMapCoords( imx+1, imz );
//DeadCode JON 31Jul00 					cornerVert[0].setIMapCoords1( 255, 0 );
//DeadCode JON 31Jul00 					g_lpLib3d->EndFan();				}
//DeadCode JON 31Jul00 
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				R3DVERTEX *pRVerts;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				R3DVERTEX2 cornerVert[4];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				R3DVERTEX2 *insertVerts;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[0].bodyx.f=lowptr2[0].x;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 		 		cornerVert[0].bodyy.f=lowptr2[0].y;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[0].bodyz.f=lowptr2[0].z;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[0].ix=imx;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[0].iy=imz;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[0].ix1=
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					cornerVert[0].iy1=0;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[1].bodyx.f=lowptr2[_horizonPoints].x;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[1].bodyy.f=lowptr2[_horizonPoints].y;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[1].bodyz.f=lowptr2[_horizonPoints].z;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[1].ix=imx;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[1].iy=imz+2;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[1].ix1=0;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[1].iy1=255;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[2].bodyx.f=lowptr2[_horizonPoints+1].x;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[2].bodyy.f=lowptr2[_horizonPoints+1].y;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[2].bodyz.f=lowptr2[_horizonPoints+1].z;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[2].ix=imx+2;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[2].iy=imz+2;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[2].ix1=255;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[2].iy1=255;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[3].bodyx.f=lowptr2[1].x;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[3].bodyy.f=lowptr2[1].y;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[3].bodyz.f=lowptr2[1].z;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[3].ix=imx+2;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[3].iy=imz;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[3].ix1=255;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				cornerVert[3].iy1=0;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				//top
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				if (side!=2)
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				{
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					g_lpLib3d->BeginFan(cloudMaterial,4,pRVerts);
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					insertVerts=(R3DVERTEX2*)pRVerts;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					*insertVerts++=cornerVert[0];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					*insertVerts++=cornerVert[1];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					*insertVerts++=cornerVert[2];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					*insertVerts=cornerVert[3];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					g_lpLib3d->EndFan();
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				}
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				//bottom
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				if (side!=1)
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				{
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					g_lpLib3d->BeginFan(cloudMaterial,4,pRVerts);
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					insertVerts=(R3DVERTEX2*)pRVerts;
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					*insertVerts++=cornerVert[3];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					*insertVerts++=cornerVert[2];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					*insertVerts++=cornerVert[1];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					*insertVerts=cornerVert[0];
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 					g_lpLib3d->EndFan();
//DeadCode JON 31Jul00 //DEADCODE JON 5/24/00 				}
//DeadCode JON 31Jul00 			}
//DeadCode JON 31Jul00 		}
//DeadCode JON 31Jul00 	}
//DeadCode JON 31Jul00 	g_lpLib3d->SetGlobal( TOGGLE_GLOBALALPHA, 255 );
//DeadCode JON 31Jul00 //#endif
//DeadCode JON 31Jul00 }

//DEADCODE JON 3/30/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JON 3/30/00 //Procedure		GridCone
//DEADCODE JON 3/30/00 //Author		Paul.   
//DEADCODE JON 3/30/00 //Date			Mon 22 Jun 1998
//DEADCODE JON 3/30/00 //------------------------------------------------------------------------------
//DEADCODE JON 3/30/00 void LandScape::GridCone(const SLong px,const SLong pz)
//DEADCODE JON 3/30/00 {
//DEADCODE JON 3/30/00 	D3DVECTOR pos[_cornerLengthMIN*_cornerLengthMIN*2];
//DEADCODE JON 3/30/00 	ULong flags[_cornerLengthMIN*_cornerLengthMIN*2];
//DEADCODE JON 3/30/00 
//DEADCODE JON 3/30/00 	D3DVECTOR lpos,mpos,*lowptr,*hiptr;
//DEADCODE JON 3/30/00 	SLong lx,lz,mx;
//DEADCODE JON 3/30/00 	lowptr=pos;
//DEADCODE JON 3/30/00 	hiptr=lowptr+_cornerLengthMIN*_cornerLengthMIN;
//DEADCODE JON 3/30/00 	lx=px;
//DEADCODE JON 3/30/00 	lz=pz;
//DEADCODE JON 3/30/00 	lpos.x=lx-viewer_x;
//DEADCODE JON 3/30/00 	lpos.z=lz-viewer_z;
//DEADCODE JON 3/30/00 	// get the grid data 4 min and maximum altitudes
//DEADCODE JON 3/30/00 	fileblock fb( FIL_MAXALT, Grid_Base::makeGridAt );
//DEADCODE JON 3/30/00 	Grid_Base* maxAlt = (Grid_Base*) fb.getdata();
//DEADCODE JON 3/30/00 	fileblock fb1( FIL_MINALT, Grid_Base::makeGridAt );
//DEADCODE JON 3/30/00 	Grid_Base* minAlt = (Grid_Base*) fb1.getdata();
//DEADCODE JON 3/30/00 
//DEADCODE JON 3/30/00 	for (int i=_cornerLengthMIN;i!=0;i--)
//DEADCODE JON 3/30/00 	{
//DEADCODE JON 3/30/00 		mpos=lpos;
//DEADCODE JON 3/30/00 		mx=lx;
//DEADCODE JON 3/30/00 		for (int j=_cornerLengthMIN;j!=0;j--)
//DEADCODE JON 3/30/00 		{
//DEADCODE JON 3/30/00 			SLong min,max;
//DEADCODE JON 3/30/00 //DEADCODE JON 1/27/00 			Three_Dee.pTMake->GetMinMaxAlt(mx,lz,min,max);
//DEADCODE JON 3/30/00 			min = minAlt->getWorld( mx, lz )<<9;
//DEADCODE JON 3/30/00 			max = maxAlt->getWorld( mx, lz )<<9;
//DEADCODE JON 3/30/00 			*lowptr=mpos;
//DEADCODE JON 3/30/00 //DEADCODE JON 1/31/00 			min*=_altitudeScale;
//DEADCODE JON 3/30/00 			*hiptr=mpos;
//DEADCODE JON 3/30/00 //DEADCODE JON 1/31/00 			max*=_altitudeScale;
//DEADCODE JON 3/30/00 			lowptr->y=min-viewer_y;
//DEADCODE JON 3/30/00 			hiptr->y=max-viewer_y;
//DEADCODE JON 3/30/00 			mpos.x+=_blockWidth;
//DEADCODE JON 3/30/00 			mx+=_blockWidth;
//DEADCODE JON 3/30/00 			lowptr++;
//DEADCODE JON 3/30/00 			hiptr++;
//DEADCODE JON 3/30/00 		}
//DEADCODE JON 3/30/00 		lpos.z+=_blockWidth;
//DEADCODE JON 3/30/00 		lz+=_blockWidth;
//DEADCODE JON 3/30/00 	}
//DEADCODE JON 3/30/00 	g_lpLib3d->VisibleCheck(pos,_cornerLengthMIN*_cornerLengthMIN*2,flags);
//DEADCODE JON 3/30/00 
//DEADCODE JON 3/30/00 	ULong *lowf,*hif;
//DEADCODE JON 3/30/00 	lowf=flags;
//DEADCODE JON 3/30/00 	hif=flags+_cornerLengthMIN*_cornerLengthMIN;
//DEADCODE JON 3/30/00 	for (i=_cornerLengthMIN*_cornerLengthMIN;i!=0;*lowf&=*hif,lowf++,hif++,i--);
//DEADCODE JON 3/30/00 	
//DEADCODE JON 3/30/00 	lowf=flags;
//DEADCODE JON 3/30/00 	UByte* res=gridCone;
//DEADCODE JON 3/30/00 
//DEADCODE JON 3/30/00 	for (i=_wholeAreaSizeMIN;i!=0;i--)
//DEADCODE JON 3/30/00 	{
//DEADCODE JON 3/30/00 		ULong *lowf2=lowf;
//DEADCODE JON 3/30/00 		lowf+=_cornerLengthMIN;
//DEADCODE JON 3/30/00 		for (int j=_wholeAreaSizeMIN;j!=0;j--,lowf2++)
//DEADCODE JON 3/30/00 		{
//DEADCODE JON 3/30/00 			ULong flag=lowf2[0]&lowf2[1]&lowf2[_cornerLengthMIN]&lowf2[_cornerLengthMIN+1];
//DEADCODE JON 3/30/00 			*res++=flag?0:1;
//DEADCODE JON 3/30/00 		}
//DEADCODE JON 3/30/00 	}
//DEADCODE JON 3/30/00 }
//Old_Code PD 29Nov99 void LandScape::GridCone(const SLong px,const SLong pz)
//Old_Code PD 29Nov99 {
//Old_Code PD 29Nov99 	const Float _fbw=Float(_blockWidth);
//Old_Code PD 29Nov99 	FPMATRIX& mat=*fpviewer_matrix;
//Old_Code PD 29Nov99 	fpCOORDS3D tbasepos,tdeltawx,tdeltawy,tdeltawz;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	SLong intbaseposX=px;
//Old_Code PD 29Nov99 	SLong intbaseposZ=pz;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	tbasepos.X.i=px-viewer_x;
//Old_Code PD 29Nov99 	tbasepos.Y.i=-viewer_y;
//Old_Code PD 29Nov99 	tbasepos.Z.i=pz-viewer_z;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	_matrix.transform(&mat,tbasepos.X,tbasepos.Y,tbasepos.Z);
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	tdeltawx.X.f=mat.L11*_fbw;
//Old_Code PD 29Nov99 	tdeltawx.Y.f=mat.L21*_fbw;
//Old_Code PD 29Nov99 	tdeltawx.Z.f=mat.L31*_fbw;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	tdeltawy.X.f=mat.L12*Float(_altitudeScale);
//Old_Code PD 29Nov99 	tdeltawy.Y.f=mat.L22*Float(_altitudeScale);
//Old_Code PD 29Nov99 	tdeltawy.Z.f=mat.L32*Float(_altitudeScale);
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	tdeltawz.X.f=mat.L13*_fbw;
//Old_Code PD 29Nov99 	tdeltawz.Y.f=mat.L23*_fbw;
//Old_Code PD 29Nov99 	tdeltawz.Z.f=mat.L33*_fbw;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	UByte* ptr=gridCorners;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	SLong cornerLength,wholeAreaSize;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	cornerLength=_cornerLengthMIN;
//Old_Code PD 29Nov99 	wholeAreaSize=_wholeAreaSizeMIN;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	for (int r=0;r<cornerLength;r++)
//Old_Code PD 29Nov99 	{
//Old_Code PD 29Nov99 		fpCOORDS3D 	tbaseinner=tbasepos;
//Old_Code PD 29Nov99 		SLong intinnerposX=intbaseposX;
//Old_Code PD 29Nov99 		SLong intinnerposZ=intbaseposZ;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 		for (int c=0;c<cornerLength;c++)
//Old_Code PD 29Nov99 		{
//Old_Code PD 29Nov99 			fpCOORDS3D low,high;
//Old_Code PD 29Nov99 			SLong min,max;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 			Three_Dee.pTMake->GetMinMaxAlt(intinnerposX,intinnerposZ,min,max);
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 			low.X.f=tbaseinner.X.f+tdeltawy.X.f*Float(min);
//Old_Code PD 29Nov99 			low.Y.f=tbaseinner.Y.f+tdeltawy.Y.f*Float(min);
//Old_Code PD 29Nov99 			low.Z.f=tbaseinner.Z.f+tdeltawy.Z.f*Float(min);
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 			high.X.f=tbaseinner.X.f+tdeltawy.X.f*Float(max);
//Old_Code PD 29Nov99 			high.Y.f=tbaseinner.Y.f+tdeltawy.Y.f*Float(max);
//Old_Code PD 29Nov99 			high.Z.f=tbaseinner.Z.f+tdeltawy.Z.f*Float(max);
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 			*ptr++=_matrix.GenClipFlags(low)&_matrix.GenClipFlags(high);
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 			intinnerposX+=_blockWidth;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 			tbaseinner.X.f+=tdeltawx.X.f;
//Old_Code PD 29Nov99 			tbaseinner.Y.f+=tdeltawx.Y.f;
//Old_Code PD 29Nov99 			tbaseinner.Z.f+=tdeltawx.Z.f;
//Old_Code PD 29Nov99 		}
//Old_Code PD 29Nov99 		intbaseposZ+=_blockWidth;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 		tbasepos.X.f+=tdeltawz.X.f;
//Old_Code PD 29Nov99 		tbasepos.Y.f+=tdeltawz.Y.f;
//Old_Code PD 29Nov99 		tbasepos.Z.f+=tdeltawz.Z.f;
//Old_Code PD 29Nov99 	}
//Old_Code PD 29Nov99 	ptr=gridCorners;
//Old_Code PD 29Nov99 	UByte* res=gridCone;
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 	for (r=0;r<wholeAreaSize;r++,ptr+=cornerLength)
//Old_Code PD 29Nov99 	{
//Old_Code PD 29Nov99 		UByte* ptr2=ptr;
//Old_Code PD 29Nov99 	 	for (int c=0;c<wholeAreaSize;c++,ptr2++)
//Old_Code PD 29Nov99 		{
//Old_Code PD 29Nov99 			UByte andedFlags=*ptr2;
//Old_Code PD 29Nov99 			andedFlags&=*(ptr2+1);
//Old_Code PD 29Nov99 			andedFlags&=*(ptr2+cornerLength);
//Old_Code PD 29Nov99 			andedFlags&=*(ptr2+cornerLength+1);
//Old_Code PD 29Nov99 
//Old_Code PD 29Nov99 			if (andedFlags!=0)	*res++=0;
//Old_Code PD 29Nov99 			else				*res++=1;
//Old_Code PD 29Nov99 		}
//Old_Code PD 29Nov99 	}
//Old_Code PD 29Nov99 //	if (!Manual_Pilot.ControlledAC2)
//Old_Code PD 29Nov99 //		memset(gridCone,1,wholeAreaSize*wholeAreaSize);
//Old_Code PD 29Nov99 }

//DEADCODE JON 4/27/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JON 4/27/00 //Procedure		ScrollGrid
//DEADCODE JON 4/27/00 //Author		Paul.   
//DEADCODE JON 4/27/00 //Date			Mon 9 Nov 1998
//DEADCODE JON 4/27/00 //------------------------------------------------------------------------------
//DEADCODE JON 4/27/00 void LandScape::ScrollGrid(SLong dx,SLong dz,UByte* pGrid)
//DEADCODE JON 4/27/00 {
//DEADCODE JON 4/27/00 	const SLong wholeAreaSize=_wholeAreaSizeMIN;
//DEADCODE JON 4/27/00 	const SLong GRID_SIZE=wholeAreaSize*wholeAreaSize;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 	while (dx>0)
//DEADCODE JON 4/27/00 	{
//DEADCODE JON 4/27/00 		//scroll data left (west) 'cos we're moving east
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		UByte* ptmp=pGrid;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		for (SLong c=wholeAreaSize;c--;)
//DEADCODE JON 4/27/00 		{
//DEADCODE JON 4/27/00 			for (SLong r=wholeAreaSize-1;r--;)
//DEADCODE JON 4/27/00 			{
//DEADCODE JON 4/27/00 			 	ptmp[0]=ptmp[1];
//DEADCODE JON 4/27/00 				ptmp++;
//DEADCODE JON 4/27/00 			}
//DEADCODE JON 4/27/00 			*ptmp++=0xFF;
//DEADCODE JON 4/27/00 		}
//DEADCODE JON 4/27/00 		dx-=_blockWidth;
//DEADCODE JON 4/27/00 	}
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 	while (dx<0)
//DEADCODE JON 4/27/00 	{
//DEADCODE JON 4/27/00 		//scroll data right (east) 'cos we're moving west
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		UByte* ptmp=pGrid+GRID_SIZE-1;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		for (SLong r=wholeAreaSize;r--;)
//DEADCODE JON 4/27/00 		{
//DEADCODE JON 4/27/00 			for (SLong c=wholeAreaSize-1;c--;)
//DEADCODE JON 4/27/00 			{
//DEADCODE JON 4/27/00 				ptmp[0]=ptmp[-1];
//DEADCODE JON 4/27/00 				ptmp--;
//DEADCODE JON 4/27/00 			}
//DEADCODE JON 4/27/00 			*ptmp--=0xFF;
//DEADCODE JON 4/27/00 		}
//DEADCODE JON 4/27/00 		dx+=_blockWidth;
//DEADCODE JON 4/27/00 	}
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 	while (dz>0)
//DEADCODE JON 4/27/00 	{
//DEADCODE JON 4/27/00 		//scroll data up (south) 'cos we're moving north
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		UByte* ptmp=pGrid;
//DEADCODE JON 4/27/00 		UByte* ptmp2=ptmp+wholeAreaSize;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		SLong r;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		for (r=GRID_SIZE-wholeAreaSize;r--;)
//DEADCODE JON 4/27/00 			*ptmp++=*ptmp2++;
//DEADCODE JON 4/27/00 		for (r=wholeAreaSize;r--;)
//DEADCODE JON 4/27/00 			*ptmp++=0xFF;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		dz-=_blockWidth;
//DEADCODE JON 4/27/00 	}
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 	while (dz<0)
//DEADCODE JON 4/27/00 	{
//DEADCODE JON 4/27/00 		//scroll data down (north) 'cos we're moving south
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		UByte* ptmp=pGrid+GRID_SIZE-1;
//DEADCODE JON 4/27/00 		UByte* ptmp2=ptmp-wholeAreaSize;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		SLong r;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		for (r=GRID_SIZE-wholeAreaSize;r--;)
//DEADCODE JON 4/27/00 			*ptmp--=*ptmp2--;
//DEADCODE JON 4/27/00 		for (r=wholeAreaSize;r--;)
//DEADCODE JON 4/27/00 			*ptmp--=0xFF;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 		dz+=_blockWidth;
//DEADCODE JON 4/27/00 	}
//DEADCODE JON 4/27/00 }
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 void LandScape::ScrollGridDis(SLong dx,SLong dz,HTEXT* pGrid,Dropped* pDiscarded)
//DEADCODE JON 4/27/00 {
//DEADCODE JON 4/27/00 	const SLong wholeAreaSize=_wholeAreaSizeMIN;
//DEADCODE JON 4/27/00 	const SLong GRID_SIZE=wholeAreaSize*wholeAreaSize;
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 	while (dx>0)
//DEADCODE JON 4/27/00 	{
//DEADCODE JON 4/27/00 		//scroll data left (west) 'cos we're moving east
//DEADCODE JON 4/27/00 		HTEXT* ptmp=pGrid;
//DEADCODE JON 4/27/00 		for (SLong c=wholeAreaSize-1;c>=0;c--)
//DEADCODE JON 4/27/00 		{
//DEADCODE JON 4/27/00 			if (ptmp[0]!=HTEXTNULL)	pDiscarded->hText[pDiscarded->num++]=ptmp[0];
//DEADCODE JON 4/27/00 			for (SLong r=wholeAreaSize-1;r;r--,ptmp++) ptmp[0]=ptmp[1];
//DEADCODE JON 4/27/00 			*ptmp++=HTEXTNULL;
//DEADCODE JON 4/27/00 		}
//DEADCODE JON 4/27/00 		dx-=_blockWidth;
//DEADCODE JON 4/27/00 	}
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 	while (dx<0)
//DEADCODE JON 4/27/00 	{
//DEADCODE JON 4/27/00 		//scroll data right (east) 'cos we're moving west
//DEADCODE JON 4/27/00 		HTEXT* ptmp=pGrid+GRID_SIZE-1;
//DEADCODE JON 4/27/00 		for (SLong r=wholeAreaSize-1;r>=0;r--)
//DEADCODE JON 4/27/00 		{
//DEADCODE JON 4/27/00 			if (ptmp[0]!=HTEXTNULL)	pDiscarded->hText[pDiscarded->num++]=ptmp[0];
//DEADCODE JON 4/27/00 			for (SLong c=wholeAreaSize-1;c;c--,ptmp--) ptmp[0]=ptmp[-1];
//DEADCODE JON 4/27/00 			*ptmp--=HTEXTNULL;
//DEADCODE JON 4/27/00 		}
//DEADCODE JON 4/27/00 		dx+=_blockWidth;
//DEADCODE JON 4/27/00 	}
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 	while (dz>0)
//DEADCODE JON 4/27/00 	{
//DEADCODE JON 4/27/00 		//scroll data up (south) 'cos we're moving north
//DEADCODE JON 4/27/00 		HTEXT *ptmp=pGrid,*ptmp2=ptmp+wholeAreaSize;
//DEADCODE JON 4/27/00 		for (SLong r=wholeAreaSize-1;r>=0;r--)	if (ptmp[r]!=HTEXTNULL) pDiscarded->hText[pDiscarded->num++]=ptmp[r];
//DEADCODE JON 4/27/00 		for (r=GRID_SIZE-wholeAreaSize;r--;)	*ptmp++=*ptmp2++;
//DEADCODE JON 4/27/00 		for (r=wholeAreaSize;r--;)				*ptmp++=HTEXTNULL;
//DEADCODE JON 4/27/00 		dz-=_blockWidth;
//DEADCODE JON 4/27/00 	}
//DEADCODE JON 4/27/00 
//DEADCODE JON 4/27/00 	while (dz<0)
//DEADCODE JON 4/27/00 	{
//DEADCODE JON 4/27/00 		//scroll data down (north) 'cos we're moving south
//DEADCODE JON 4/27/00 		HTEXT *ptmp=pGrid+GRID_SIZE-1,*ptmp2=ptmp-wholeAreaSize;
//DEADCODE JON 4/27/00 		for (SLong r=wholeAreaSize-1;r>=0;r--)	if (ptmp[-r]!=HTEXTNULL) pDiscarded->hText[pDiscarded->num++]=ptmp[-r];
//DEADCODE JON 4/27/00 		for (r=GRID_SIZE-wholeAreaSize;r--;)	*ptmp--=*ptmp2--;
//DEADCODE JON 4/27/00 		for (r=wholeAreaSize;r--;)				*ptmp--=HTEXTNULL;
//DEADCODE JON 4/27/00 		dz+=_blockWidth;
//DEADCODE JON 4/27/00 	}
//DEADCODE JON 4/27/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollTileGrid
//Author		Jon   
//Date			4/26/00
//		moves the tile grid thingy about...
//------------------------------------------------------------------------------
void LandScape::ScrollTileGrid(SLong dx,SLong dz)
{
	const SLong wholeAreaSize=_wholeAreaSizeMIN;
	const SLong GRID_SIZE=wholeAreaSize*wholeAreaSize;

	while (dx>0)
	{
		//scroll data left (west) 'cos we're moving east
		TileElement* ptmp=tileCacheGrid;
		for (SLong c=wholeAreaSize-1;c>=0;c--)
		{
			if (ptmp[0].textHandle!=HTEXTNULL)	
				g_lpLib3d->FreeLandscapeTexture( ptmp[0].textHandle.textureHandle );

			for (SLong r=wholeAreaSize-1;r;r--,ptmp++) 
				ptmp[0]=ptmp[1];

			ptmp->reset();
			ptmp++;
		}
		dx--;
	}

	while (dx<0)
	{
		//scroll data right (east) 'cos we're moving west
		TileElement* ptmp=tileCacheGrid+GRID_SIZE-1;
		for (SLong r=wholeAreaSize-1;r>=0;r--)
		{
			if (ptmp[0].textHandle!=HTEXTNULL)
				g_lpLib3d->FreeLandscapeTexture( ptmp[0].textHandle.textureHandle );

			for (SLong c=wholeAreaSize-1;c;c--,ptmp--)
				ptmp[0]=ptmp[-1];

			ptmp->reset();
			ptmp--;
		}
		dx++;
	}

	while (dz>0)
	{
		//scroll data up (south) 'cos we're moving north
//DeadCode JON 18Jul00 		TileElement* ptmp=tileCacheGrid,*ptmp2=ptmp+wholeAreaSize;
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 		for (SLong r=wholeAreaSize-1;r>=0;r--)	
//DeadCode JON 18Jul00 			if (ptmp[r].textHandle!=HTEXTNULL) 
//DeadCode JON 18Jul00 				g_lpLib3d->FreeLandscapeTexture( ptmp[r].textHandle.textureHandle );
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 		for (r=GRID_SIZE-wholeAreaSize;r--;)	
//DeadCode JON 18Jul00 			*ptmp++=*ptmp2++;
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 		for (r=wholeAreaSize;r--;ptmp++)				
//DeadCode JON 18Jul00 			ptmp->reset();
//DeadCode JON 18Jul00 		dz--;
		TileElement* ptmp=tileCacheGrid;
		TileElement* ptmp2=tileCacheGrid;

		for ( int i = wholeAreaSize;i;i--,ptmp2++ )
		{
			if ( ptmp2->textHandle!=HTEXTNULL )
				g_lpLib3d->FreeLandscapeTexture( ptmp2->textHandle.textureHandle );
		}

		for ( i = ((wholeAreaSize-1)*wholeAreaSize);i;i--,ptmp++,ptmp2++ )
			*ptmp=*ptmp2;

		for ( i = wholeAreaSize;i;i--,ptmp++ )
			ptmp->reset();
		dz--;
	}

	while (dz<0)
	{
		//scroll data down (north) 'cos we're moving south
		TileElement* ptmp=tileCacheGrid+GRID_SIZE-1,*ptmp2=ptmp-wholeAreaSize;
		for (SLong r=wholeAreaSize-1;r>=0;r--)	
			if (ptmp[-r].textHandle!=HTEXTNULL) 
				g_lpLib3d->FreeLandscapeTexture( ptmp[-r].textHandle.textureHandle );
		for (r=GRID_SIZE-wholeAreaSize;r--;)
			*ptmp--=*ptmp2--;
		for (r=wholeAreaSize;r--;ptmp--)
			ptmp->reset();
		dz++;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    MakeSpaceInList

// Date:		17/07/00
// Author:		JON
//
//Description:	Makes space for tiles of a certain resolution in a number of ways
//				1st tries to reduce the quality of the tile to that in reducedRez (will itself decreace that value if no space)
//			    2nd it will delete any remaining ones untill the desired number have been freed
//				Will stop when the list to free is empty - numDesired is returned with the number remaining
//
//////////////////////////////////////////////////////////////////////
inline void LandScape::MakeSpaceInList( TileResList* currResList, UWord& numDesired, UWord& listToFree, int& reducedRez )
{
	
	UWord remOffset = listToFree;
	while ( listToFree != NULLTILEOFFSET && 
		currResList->freeTiles < numDesired )
	{

		// rather than delete these offscreen tiles, reduce their quality as it is quick
		TileElement* cTile = tileCacheGrid+remOffset; // the tile to reduce
		remOffset = cTile->nextLink;

		TileResList* reducedResList = &tileResList[reducedRez];
		while ( reducedRez >= 0 && reducedResList->freeTiles <= numDesired )
		{ // find the available offscreen resoultions
			reducedResList = &tileResList[--reducedRez];
		}
		if ( reducedRez >= 0 )
		{ // we can do the reduce
			reducedResList->freeTiles--;
			HTEXT newTH;
			g_lpLib3d->AllocateLandscapeTexture( 7-reducedRez, newTH.textureHandle);

			// now make the lower rez version
#ifndef _NO_TEXTURE_RENDER
			g_lpLib3d->ReduceLandQuality( cTile->textHandle.textureHandle, newTH.textureHandle );
#endif

			g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);					
			cTile->textHandle=newTH;
			cTile->currentRes=reducedRez;
			cTile->nextLink = NULLTILEOFFSET; // shouldn't be needed
			// hmm, this should be good.
//			TileResList::add( tileResList[reducedRez].offScreenRemaining, remOffset );
		} else
		{ // none spare, just delete				
			g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
			cTile->reset();
		}

		currResList->freeTiles++;
		listToFree = remOffset;	
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManageHighLandTextures
//Author		Paul.   
//Date			Fri 6 Nov 1998
//				Re-Written By Jon 4/26/00
//				Calculates which tiles to render to textures and the levels to render them at
//				Handles cache etc.
//------------------------------------------------------------------------------
bool LandScape::ManageHighLandTextures(SLong px,SLong pz)
{	
#pragma warnmsg ( "Optimise here as many frame invariants are re-calculated on a per frame basis" )
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: start ");
	bool allAtReqLevel = true;

	// why is this delay here you may ask
	// this prevents any landscape tiles being rendered in the first frame
	// which makes my geforceIII work as it should.  No other card to date 
	// needs this and if I could find out why the GeForce does I'd fix it.
	// unfortunatly this fix cannot go in lib3d.dll with a cardbase thingy
	// so here it is.
	if ( landscapeDelay )
	{
		landscapeDelay--;
		return true;
	}


//DeadCode JON 2Aug00 	const UWord AGEMASK = 0xFFFF>>1;
	const int WIDTH=_wholeAreaSizeMIN;
//DeadCode JON 31Jul00 	const int MAX_AT_EACH_RES = 7;

	// tile making factors - multiply the values by num of that type of tiles
	// stop making when the cumulative is greater than MAX_WEIGHTED
	// could do something clever with bit fields I guess
	const int MAX_WEIGHTED = 60;//100;
	const int NEW_TILE_WEIGHT = 20;
	const int CHANGED_TILE_WEIGHT = 40;
//	const int OFFSCREEN_TILE_WEIGHT = 50;

//DeadCode JON 2Aug00 	static UWord ageCount = 0x7FFF-1;

	UWord bgList = NULLTILEOFFSET; // the tiles to be done in the background if possible
	int bgCount = 0; // number of tiles to do in the background
	const int MAX_BACKGROUND = 2; // maximum number of background tiles to make per frame.
	const int DO_BACKGROUND_CUTOFF = 20;	// do background tiles before change rez if 
											// bgCount is less than this

//	const int OFF_SCREEN_HIGHEST_REZ = 3;
//TempCode JON 17Jul00 	int numNewTiles = 0;

#ifndef NDEBUG
#define DEBUG_GRID
#endif
#ifdef DEBUG_GRID
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: debug ");
	// right quick test code
	const int dGS = 17*18; // debug grid size
	const int gS = 17*17; // grid size
	static UByte resGrid[dGS*3];
	for ( int i = 0; i< gS; i++ )
		resGrid[i] = tileCacheGrid[i].currentRes;

	for ( ; i< dGS; i++ )
		resGrid[i]=0xAA;

	// count the number of visible tiles at same time..
	int totalVis = 0;
	for ( i = 0; i< gS; i++ )
		if ( gridCone[i]==0 )
			resGrid[i+dGS] = 0xEE;
		else
		{
			resGrid[i+dGS] = tileCacheGrid[i].currentRes;
			totalVis++;
		}

	for ( ; i< dGS; i++ )
		resGrid[i+dGS] = 0xAA;

	for ( i = 0; i< gS; i++ )
		resGrid[ i+(dGS*2) ] = UByte( '?' );

	for ( ; i< dGS; i++ )
		resGrid[i+(dGS*2)] = 0xAA;

	// more test code - check that the same texture isn't being used twice...
	for ( i = WIDTH*WIDTH; i ; i-- )
	{
		if ( tileCacheGrid[i].textHandle == HTEXTNULL )
		{
			continue; // skip
		}
		for ( int j = WIDTH*WIDTH; j ; j-- )
		{
			if ( i !=j && tileCacheGrid[i].textHandle == tileCacheGrid[j].textHandle )
				NOP;
		}
	}
#endif

//DeadCode JON 2Aug00 	if ( ++ageCount < 0x7FFF )
//DeadCode JON 2Aug00 	{
//DeadCode JON 2Aug00 		ageCount = 0x7FFF;
//DeadCode JON 2Aug00 		// now must clear the top bit of all ages
//DeadCode JON 2Aug00 		TileElement* tmp = tileCacheGrid;
//DeadCode JON 2Aug00 		for ( int i = 0; i < WIDTH*WIDTH; i++, tmp++ )
//DeadCode JON 2Aug00 			tmp->age&=AGEMASK;
//DeadCode JON 2Aug00 
//DeadCode JON 2Aug00 		for ( i=0; i<8; i++ )
//DeadCode JON 2Aug00 		{
//DeadCode JON 2Aug00 			tileResList[i].oldestAge&=AGEMASK;
//DeadCode JON 2Aug00 			tileResList[i].nextOldestAge&=AGEMASK;
//DeadCode JON 2Aug00 		}
//DeadCode JON 2Aug00 	}
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: get count ");
	g_lpLib3d->GetLandscapeTextureCount(
		tileResList[7].totalTiles, // num 1024 res
		tileResList[6].totalTiles, // num 512 
		tileResList[5].totalTiles, // num 256 
		tileResList[4].totalTiles, // num 128 
		tileResList[3].totalTiles, // num 64 
		tileResList[2].totalTiles, // num 32 
		tileResList[1].totalTiles, // num 16 
		tileResList[0].totalTiles  // num 8 
	);


//DeadCode JON 31Jul00 	int maxAtRes;
	if ( maxResTiles )
	{
//DeadCode JON 31Jul00 		maxAtRes = 500; // note can't be 256 tiles
		g_lpLib3d->GetLandscapeTextureCount(
				tileResList[7].onScreenMax, // num 1024 res
				tileResList[6].onScreenMax, // num 512 
				tileResList[5].onScreenMax, // num 256 
				tileResList[4].onScreenMax, // num 128 
				tileResList[3].onScreenMax, // num 64 
				tileResList[2].onScreenMax, // num 32 
				tileResList[1].onScreenMax, // num 16 
				tileResList[0].onScreenMax  // num 8 
			);

	} else
	{
//DeadCode JON 31Jul00 		maxAtRes = MAX_AT_EACH_RES;
		g_lpLib3d->GetLandscapeTextureOnScreenMax(
			tileResList[7].onScreenMax, // num 1024 res
			tileResList[6].onScreenMax, // num 512 
			tileResList[5].onScreenMax, // num 256 
			tileResList[4].onScreenMax, // num 128 
			tileResList[3].onScreenMax, // num 64 
			tileResList[2].onScreenMax, // num 32 
			tileResList[1].onScreenMax, // num 16 
			tileResList[0].onScreenMax  // num 8 
		);

	}


//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: reset loop ");
	for ( int j = 0; j < 8; tileResList[j++].reset() ) 
	{/* re initialising the lists*/}

	for ( int currentRes = 7; tileResList[currentRes].totalTiles==0; currentRes-- )
	{ /*search for the highest resolution possible*/ }
	
	int highestPossRes = currentRes;

	meshDetailLevel = meshDetailLookup[ Save_Data.contourDetail ];
	
	int		DX=1,DY=WIDTH;
	int		DDA=0;				 //pointeroffset to move this time.
//	TileElement*	curr=tileCacheGrid+((WIDTH/2))*WIDTH+((WIDTH/2));//Centresquare;
	UWord	curr = ((WIDTH/2))*WIDTH+((WIDTH/2)); // offset to the current tile
	int		counter=1;
	int		R=0;	//radius
	int		R2=0;	//radius/2
	enum	Phase
	{	PH_0,PH_1,PH_2,PH_3,PH_4,			//centre square
		PH_A,PH_B,PH_C,PH_D,PH_E,PH_F,PH_G,PH_H,	//odd radius
		PH_I,PH_J,PH_K,PH_L,				//filler
		PH_M,PH_N,PH_O,PH_P,PH_Q,PH_R,PH_S,PH_T,	//even radius
		PH_U,PH_V,PH_W,PH_X,				//corners
		PH_Y,PH_Z,PH_END				//last 4
	};
	Phase	phase=PH_0;
	
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: while loop ");
	while(phase!=PH_END)	//optimiser should make case statement bypass while statement
	{
//		Process(curr); // curr ptr to current grid loc, process do the work.
//DeadCode JON 31Jul00 		if ( (tileResList[currentRes].desiredTiles == maxAtRes || tileResList[currentRes].desiredTiles == tileResList[currentRes].totalTiles )/*&& currentRes>0*/ )
//DeadCode JON 31Jul00 		{
//DeadCode JON 31Jul00 			currentRes--;
//DeadCode JON 31Jul00 		}

		while ( tileResList[currentRes].desiredTiles == tileResList[currentRes].onScreenMax )
		{
			currentRes--;
#ifndef NDEBUG
//			if ( currentRes < 0 )
//				INT3;
			assert( currentRes>=0 && "run out of texture tiles." );
#endif
		}


		TileElement* cTile = tileCacheGrid+curr;

		// set the meshdetail level
		cTile->meshRes=meshDetailLevel[R];
		cTile->viewRadius = R;
		
		if ( *(gridCone+curr) )
		{ // this tile is visible
//DeadCode JON 2Aug00 			cTile->age = ageCount;
			cTile->desiredRes = currentRes;
		
			tileResList[currentRes].desiredTiles++;		 // one more desired.
			if ( cTile->currentRes < cTile->desiredRes )
			{								// the tile is currently at too low a rez
				TileResList::add(
					tileResList[cTile->desiredRes].underResTile,
					curr );
				tileResList[cTile->currentRes].freeTiles--; // this isn't free.
			} else if ( cTile->currentRes > cTile->desiredRes )
			{		
				if ( cTile->currentRes == OFFSCREENRES )
				{							// the tile has no texture at the moment
					TileResList::add(
						tileResList[cTile->desiredRes].newTile,
						curr );
					tileResList[cTile->desiredRes].numNewTiles++;
//TEMPCODE JON 6/7/00 					numNewTiles++;
				} else
				{							// the tile is currently at too high rez
					TileResList::add(
						tileResList[cTile->desiredRes].overResTile,
						curr );
					tileResList[cTile->currentRes].freeTiles--; // this isn't free.
				}
			} else
			{								// the tile is at the correct res
				tileResList[currentRes].freeTiles--; // it isn't free though
			}
		} else
		{ // this tile is not visible
			if ( cTile->currentRes != OFFSCREENRES )
			{ // needs adding to an oldest tile...
				tileResList[cTile->currentRes].freeTiles--; // this isn't free.

					TileResList::add(
						tileResList[cTile->currentRes].offScreen,
						curr );					

//DeadCode JON 2Aug00 				if ( cTile->age == tileResList[cTile->currentRes].oldestAge )
//DeadCode JON 2Aug00 				{ // add to the oldest age list
//DeadCode JON 2Aug00 					TileResList::add(
//DeadCode JON 2Aug00 						tileResList[cTile->currentRes].offScreenOldest,
//DeadCode JON 2Aug00 						curr );					
//DeadCode JON 2Aug00 				} else 
//DeadCode JON 2Aug00 				{ // add to the remaining offscreen tiles
//DeadCode JON 2Aug00 					TileResList::add(
//DeadCode JON 2Aug00 						tileResList[cTile->currentRes].offScreenRemaining,
//DeadCode JON 2Aug00 						curr );					
//DeadCode JON 2Aug00 					if ( cTile->age < tileResList[cTile->currentRes].nextOldestAge )
//DeadCode JON 2Aug00 						tileResList[cTile->currentRes].nextOldestAge = cTile->age;
//DeadCode JON 2Aug00 				}
			} else
			{ // not visible and not cached
//DEADCODE JON 6/6/00 				if ( bgCount > 0 )
//DEADCODE JON 6/6/00 				{
//DEADCODE JON 6/6/00 					bgCount--;
//DEADCODE JON 6/6/00 					TileResList::add( bgList, curr );
//DEADCODE JON 6/6/00 				}	
				if ( bgCount++ < MAX_BACKGROUND )
				{
					TileResList::add( bgList, curr );
				}
			}
		}

		// the rest of the loop is the iteration to go round the spiral.
		if (--counter!=0)
			curr+=DDA;
		else
		{
			switch(phase)
			{
			case PH_0:		
				phase=PH_1;
				DDA=+DX;		
				R+=1;
				R2+=0;
				counter=2;
				curr+=-DY;
				break;
			case PH_1:		
				phase=PH_2;
				DDA=+DY;		
				R+=0;
				R2+=0;
				counter=2;
				curr+=DDA;
				break;
			case PH_2:		
				phase=PH_3;
				DDA=-DX;		
				R+=0;
				R2+=0;
				counter=2;
				curr+=DDA;
				break;
			case PH_3:		
				phase=PH_4;
				DDA=-DY;		
				R+=0;
				R2+=0;
				counter=2;
				curr+=DDA;
				break;
			case PH_4:		
				phase=PH_A;
				DDA=+DX;		
				R+=1;
				R2+=1;
				counter=2;
				curr+=-DY+DX;
				break;
			case PH_A:
				phase=PH_B;
				DDA=+DX+DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=DDA;
				break;
			case PH_B:		
				phase=PH_C;
				DDA=+DY;		
				R+=0;
				R2+=0;
				counter=R;
				curr+=DDA;
				break;
			case PH_C:
				phase=PH_D;
				DDA=-DX+DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=DDA;
				break;
			case PH_D:
				phase=PH_E;
				DDA=-DX;				
				R+=0;
				R2+=0;
				counter=R;
				curr+=DDA;
				break;
			case PH_E:
				phase=PH_F;
				DDA=-DX-DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=DDA;
				break;
			case PH_F:
				phase=PH_G;
				DDA=-DY;				
				R+=0;
				R2+=0;
				counter=R;
				curr+=DDA;
				break;
			case PH_G:
				phase=PH_H;
				DDA=+DX-DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=DDA;
				break;
			case PH_H:
				if ( R<8 )
				{
					phase=PH_I;
					DDA=+DX+DY;
					R+=0;
					R2+=0;
					counter=R2;
					curr+=(R+1)*DX;
				} else
				{
					phase=PH_W;
					DDA=+DX+DY;
					R+=1;
					R2=13-R;
					counter=13-R;
					curr+=(2*R-9)*DX;
				}
				break;
			case PH_I:
				phase=PH_J;
				DDA=-DX+DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=(R+2)*DY;
				break;
			case PH_J:
				phase=PH_K;
				DDA=-DX-DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=-(R+2)*DX;
				break;
			case PH_K:
				phase=PH_L;
				DDA=+DX-DY;				
				R+=0;
				R2+=0;
				counter=R2;
				curr+=-(R+2)*DY;
				break;
			case PH_L:
				phase=PH_M;
				DDA=+DX;
				R+=1;
				R2+=0;
				counter=R+1;
				curr+=+DX-DY;
				break;

			case PH_M:
				phase=PH_N;
				DDA=+DX+DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=DDA;
				break;
			case PH_N:
				phase=PH_O;
				DDA=+DY;
				R+=0;
				R2+=0;
				counter=R+1;
				curr+=DDA;
				break;
			case PH_O:
				phase=PH_P;
				DDA=-DX+DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=DDA;
				break;
			case PH_P:
				phase=PH_Q;
				DDA=-DX;
				R+=0;
				R2+=0;
				counter=R+1;
				curr+=DDA;
				break;
			case PH_Q:
				phase=PH_R;
				DDA=-DX-DY;
				R+=0;
				R2+=0;
				counter=R2;
				curr+=DDA;
				break;
			case PH_R:
				phase=PH_S;
				DDA=-DY;
				R+=0;
				R2+=0;
				counter=R+1;
				curr+=DDA;
				break;
			case PH_S:
				phase=PH_T;
				DDA=+DX-DY;				
				R+=0;
				R2+=0;
				counter=R2;
				curr+=DDA;
				break;
			case PH_T:
				phase=PH_A;
				DDA=+DX;				
				R+=1;
				R2+=1;
				counter=R;
				curr+=+DX-DY;
				break;

			case PH_W:
				phase=PH_X;
				DDA=-DX+DY;
				R+=0;
				R2+=0;
				counter=13-R;
				curr+=(2*R-8)*DY;
				break;
			case PH_X:
				phase=PH_Y;
				DDA=-DX-DY;
				R+=0;
				R2+=0;
				counter=13-R;
				curr+=-(2*R-8)*DX;
				break;
			case PH_Y:
				phase=PH_Z;
				DDA=+DX-DY;
				R+=0;
				R2+=0;
				counter=13-R;
				curr+=-(2*R-8)*DY;
				break;
			case PH_Z:
				if ( R<12 )
				{
					phase=PH_W;
					DDA=+DX+DY;
					R+=1;
					R2+=1;
					counter=13-R;
					curr+=(2*R-9)*DX;
				} else 
				{
					phase=PH_END;
				}	
				break;
			NODEFAULT;
			}
		}
	} // end of while

//DEADCODE JON 5/12/00 	if ( numNewTiles > 3 )
//DEADCODE JON 5/12/00 		int i=0;

// now we have to go through the lists we have built and render the tile changes that we can.
// step one: shuffle things about so there are enough tiles of each resolution to build the new 
// ones that are wanted...
	int cumWeight = 0; // no not some sick var name- cumulative tile weight
	int rez;

	// ok now first we can reduce the res of anything wanting it as it's virtually free...

//DeadCode JON 17Jul00 	// when lowering resolutions start at the highest res and move on down
//DeadCode JON 17Jul00 	// note - no need to start at the very highest as there will be nothing
//DeadCode JON 17Jul00 	// of higher resolution anyway.
//DeadCode JON 17Jul00 	for ( rez = 6; rez >= 0; rez-- )

	int offScreenRes;// = OFF_SCREEN_HIGHEST_REZ;
	for ( offScreenRes = 0; tileResList[offScreenRes].freeTiles==0; offScreenRes++ )
	{ /*search for the lowest resolution possible with free tiles*/ }
	if ( offScreenRes > 7 )
		offScreenRes = 0; // there are no free tiles...
	else
	{
		offScreenRes = (highestPossRes + offScreenRes)>>1; // start offscreen between the two..
		if ( offScreenRes<3 )
			offScreenRes = 3;
	}

	// when lowering resolutions start at the bottom and work up - should never not be able to lower a 
	// rez because of a lost tile
	// note - no need to start at the very highest as there will be nothing
	// of higher resolution anyway.
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: for res=0 ");
	for ( rez = 0; rez <7; rez++ )
	{
		TileResList* currResList = &tileResList[rez];
		UWord offset = currResList->overResTile;
		while ( offset != NULLTILEOFFSET )
		{
			while ( currResList->freeTiles <= currResList->numNewTiles )
			{ // try to free some tiles

				UWord numReq = 1 + currResList->numNewTiles;
//DeadCode JON 2Aug00 				MakeSpaceInList( currResList, numReq, currResList->offScreenOldest, offScreenRes );
//DeadCode JON 2Aug00 				MakeSpaceInList( currResList, numReq, currResList->offScreenRemaining, offScreenRes );
				MakeSpaceInList( currResList, numReq, currResList->offScreen, offScreenRes );
				if ( currResList->freeTiles < numReq )
					break;

//DeadCode JON 18Jul00 				if ( currResList->offScreenOldest != NULLTILEOFFSET )
//DeadCode JON 18Jul00 				{
//DeadCode JON 18Jul00 					TileElement* delTile = tileCacheGrid+currResList->offScreenOldest;
//DeadCode JON 18Jul00 					g_lpLib3d->FreeLandscapeTexture(delTile->textHandle.textureHandle);
//DeadCode JON 18Jul00 					currResList->offScreenOldest = delTile->nextLink;
//DeadCode JON 18Jul00 					delTile->reset();
//DeadCode JON 18Jul00 					currResList->freeTiles++;
//DeadCode JON 18Jul00 				} else if ( currResList->offScreenRemaining != NULLTILEOFFSET )
//DeadCode JON 18Jul00 				{
//DeadCode JON 18Jul00 					TileElement* delTile = tileCacheGrid+currResList->offScreenRemaining;
//DeadCode JON 18Jul00 					g_lpLib3d->FreeLandscapeTexture(delTile->textHandle.textureHandle);
//DeadCode JON 18Jul00 					currResList->offScreenRemaining = delTile->nextLink;
//DeadCode JON 18Jul00 					delTile->reset();
//DeadCode JON 18Jul00 					currResList->freeTiles++;
//DeadCode JON 18Jul00 				}
//DeadCode JON 18Jul00 //DeadCode JON 18Jul00 				else
//DeadCode JON 18Jul00 //DeadCode JON 18Jul00 					break; // can't make any more space.
			}

			TileElement* cTile = tileCacheGrid+offset;
			if ( currResList->freeTiles <= currResList->numNewTiles )
				break;		// unable to make enough space

#ifndef NDEBUG		//shouldn't be possible for this to happen
			if ( cTile->textHandle == HTEXTNULL )
				INT3;
#endif
			{ // we can do the quick reduce
				tileResList[cTile->currentRes].freeTiles++;
				currResList->freeTiles--;
				HTEXT newTH;
				g_lpLib3d->AllocateLandscapeTexture( 7-rez, newTH.textureHandle);

				// now make the lower rez version
#ifndef _NO_TEXTURE_RENDER
				g_lpLib3d->ReduceLandQuality( cTile->textHandle.textureHandle, newTH.textureHandle );
#endif
				g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);					
				cTile->textHandle=newTH;
				cTile->currentRes=rez;

				currResList->overResTile = cTile->nextLink;
				offset = currResList->overResTile;
				cTile->nextLink = NULLTILEOFFSET; // shouldn't be needed but what the heck...
			} 
//TempCode JON 18Jul00 			else
//TempCode JON 18Jul00 			{ // can't do the quick reduce as we've already killed the source somehow
//TempCode JON 18Jul00 				INT3;
//TempCode JON 18Jul00 				currResList->overResTile = cTile->nextLink;
//TempCode JON 18Jul00 				TileResList::add( currResList->newTile, offset );
//TempCode JON 18Jul00 				offset = currResList->overResTile;
//TempCode JON 18Jul00 				currResList->numNewTiles++;
//TempCode JON 18Jul00 				cumWeight+=CHANGED_TILE_WEIGHT;
//TempCode JON 18Jul00 			}
		}
	}

	// prepare to make any new tiles as needed
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: ror res=7 ");
	for ( rez = 7; rez >= 0; rez-- )
	{
		TileResList* currResList = &tileResList[rez];
		if ( currResList->newTile != NULLTILEOFFSET )
		{ // make some more space if needed
			if ( currResList->freeTiles < currResList->numNewTiles )
			{
				// we need to free up some tiles at this rez to continue.
				// try the oldest first
//DeadCode JON 2Aug00 				MakeSpaceInList( currResList, currResList->numNewTiles, currResList->offScreenOldest, offScreenRes );
//DeadCode JON 2Aug00 				MakeSpaceInList( currResList, currResList->numNewTiles, currResList->offScreenRemaining, offScreenRes );
				MakeSpaceInList( currResList, currResList->numNewTiles, currResList->offScreen, offScreenRes );

//DeadCode JON 18Jul00 				int reducedRez = OFF_SCREEN_HIGHEST_REZ;
//DeadCode JON 18Jul00 				
//DeadCode JON 18Jul00 				UWord remOffset = currResList->offScreenOldest;
//DeadCode JON 18Jul00 				while ( remOffset != NULLTILEOFFSET && 
//DeadCode JON 18Jul00 					currResList->freeTiles < currResList->numNewTiles )
//DeadCode JON 18Jul00 				{
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 					// rather than delete these offscreen tiles, reduce their quality as it is quick
//DeadCode JON 18Jul00 					TileElement* cTile = tileCacheGrid+remOffset; // the tile to reduce
//DeadCode JON 18Jul00 					remOffset = cTile->nextLink;
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 					// we can do some background processing - hurrah.
//DeadCode JON 18Jul00 					TileResList* reducedResList = &tileResList[rez];
//DeadCode JON 18Jul00 //DeadCode JON 17Jul00 					while ( reducedResList->freeTiles <= currResList->numNewTiles )
//DeadCode JON 18Jul00 					while ( reducedRez >= 0 && reducedResList->freeTiles <= reducedResList->numNewTiles )
//DeadCode JON 18Jul00 					{ // find the available offscreen resoultions
//DeadCode JON 18Jul00 						reducedResList = &tileResList[--reducedRez];
//DeadCode JON 18Jul00 					}
//DeadCode JON 18Jul00 					if ( reducedRez >= 0 )
//DeadCode JON 18Jul00 					{ // we can do the reduce
//DeadCode JON 18Jul00 						reducedResList->freeTiles--;
//DeadCode JON 18Jul00 						HTEXT newTH;
//DeadCode JON 18Jul00 						g_lpLib3d->AllocateLandscapeTexture( 7-reducedRez, newTH.textureHandle);
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 						// now make the lower rez version
//DeadCode JON 18Jul00 						g_lpLib3d->ReduceLandQuality( cTile->textHandle.textureHandle, newTH.textureHandle );
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);					
//DeadCode JON 18Jul00 						cTile->textHandle=newTH;
//DeadCode JON 18Jul00 						cTile->currentRes=reducedRez;
//DeadCode JON 18Jul00 						cTile->nextLink = NULLTILEOFFSET; // shouldn't be needed
//DeadCode JON 18Jul00 					} else
//DeadCode JON 18Jul00 					{ // none spare, just delete				
//DeadCode JON 18Jul00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DeadCode JON 18Jul00 						cTile->reset();
//DeadCode JON 18Jul00 					}
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 					currResList->freeTiles++;
//DeadCode JON 18Jul00 					currResList->offScreenOldest = remOffset;	
//DeadCode JON 18Jul00 				}
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 				// try the rest
//DeadCode JON 18Jul00 				remOffset = currResList->offScreenRemaining;
//DeadCode JON 18Jul00 				while ( remOffset != NULLTILEOFFSET && 
//DeadCode JON 18Jul00 					currResList->freeTiles < currResList->numNewTiles )
//DeadCode JON 18Jul00 				{
//DeadCode JON 18Jul00 					// rather than delete these offscreen tiles, reduce their quality as it is quick
//DeadCode JON 18Jul00 					TileElement* cTile = tileCacheGrid+remOffset; // the tile to reduce
//DeadCode JON 18Jul00 					remOffset = cTile->nextLink;
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 					// we can do some background processing - hurrah.
//DeadCode JON 18Jul00 					TileResList* reducedResList = &tileResList[rez];
//DeadCode JON 18Jul00 //DeadCode JON 17Jul00 					while ( reducedResList->freeTiles <= currResList->numNewTiles )
//DeadCode JON 18Jul00 					while ( reducedRez >= 0 && reducedResList->freeTiles <= reducedResList->numNewTiles )
//DeadCode JON 18Jul00 					{ // find the available offscreen resoultions
//DeadCode JON 18Jul00 						reducedResList = &tileResList[--reducedRez];
//DeadCode JON 18Jul00 					}
//DeadCode JON 18Jul00 					if ( reducedRez >= 0 )
//DeadCode JON 18Jul00 					{ // we can do the reduce
//DeadCode JON 18Jul00 						reducedResList->freeTiles--;
//DeadCode JON 18Jul00 						HTEXT newTH;
//DeadCode JON 18Jul00 						g_lpLib3d->AllocateLandscapeTexture( 7-reducedRez, newTH.textureHandle);
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 						// now make the lower rez version
//DeadCode JON 18Jul00 						g_lpLib3d->ReduceLandQuality( cTile->textHandle.textureHandle, newTH.textureHandle );
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);					
//DeadCode JON 18Jul00 						cTile->textHandle=newTH;
//DeadCode JON 18Jul00 						cTile->currentRes=reducedRez;
//DeadCode JON 18Jul00 						cTile->nextLink = NULLTILEOFFSET; // shouldn't be needed
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 					} else
//DeadCode JON 18Jul00 					{ // none spare, just delete				
//DeadCode JON 18Jul00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DeadCode JON 18Jul00 						cTile->reset();
//DeadCode JON 18Jul00 					}
//DeadCode JON 18Jul00 
//DeadCode JON 18Jul00 					currResList->freeTiles++;
//DeadCode JON 18Jul00 					currResList->offScreenOldest = remOffset;	
//DeadCode JON 18Jul00 				}
				if ( currResList->freeTiles < currResList->numNewTiles )
				{
//DeadCode JON 2Aug00 					currResList->offScreenRemaining = NULLTILEOFFSET;
					currResList->offScreen = NULLTILEOFFSET;
					// right now we need to shove any tiles we are unable to do into the next rez list
					allAtReqLevel = false;
					if ( rez > 0 )
					{
						// get to the first one to move ( move the end of the list not the start )
						UWord offset = currResList->newTile;
						UWord tmp;
						if ( currResList->freeTiles > 0 )
						{
							for ( int i = currResList->freeTiles; i>0; i-- )
								offset = (tileCacheGrid+offset)->nextLink;
				
							tmp = offset;
							offset = (tileCacheGrid+offset)->nextLink;
							(tileCacheGrid+tmp)->nextLink = NULLTILEOFFSET;
						} else
						{
							currResList->newTile = NULLTILEOFFSET;
						}

						while( offset != NULLTILEOFFSET )
						{
							currResList->numNewTiles--;
							tileResList[rez-1].numNewTiles++;
							tmp = (tileCacheGrid+offset)->nextLink;

							TileResList::add( tileResList[rez-1].newTile, offset );
							offset = tmp;
						}
					} 
				}

//				if ( currResList->freeTiles < currResList->numNewTiles )
// 				{
// 					INT3; //we've been unable to make the required space in anyway
//				}
			}
		}
		cumWeight += currResList->numNewTiles;
	}
	cumWeight*=NEW_TILE_WEIGHT;

	// now do a pass to make as many changed tiles as we can
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: cumWeight ");
	if ( cumWeight < MAX_WEIGHTED && bgCount > DO_BACKGROUND_CUTOFF )
	{
		// great we can now make some resolution changes
		// only need to raise as we've already lowered for very little cost
		
		// when raising resolutions start at the highest again,
		// but don't bother wiv the lowest
		for ( rez = 7; rez >0; rez-- )
		{
			TileResList* currResList = &tileResList[rez];
			UWord offset = currResList->underResTile;
			while ( offset != NULLTILEOFFSET && cumWeight < MAX_WEIGHTED )
			{
				if ( currResList->freeTiles == currResList->numNewTiles )
				{ // try to free some tiles

//TempCode JON 18Jul00 					UWord numReq = 1 + currResList->numNewTiles;
//TempCode JON 18Jul00 					MakeSpaceInList( currResList, numReq, currResList->offScreenOldest, offScreenRes );
//TempCode JON 18Jul00 					MakeSpaceInList( currResList, numReq, currResList->offScreenRemaining, offScreenRes );
//TempCode JON 18Jul00 					if ( currResList->freeTiles < numReq )
//TempCode JON 18Jul00 						break;
					
//DeadCode JON 2Aug00 					if ( currResList->offScreenOldest != NULLTILEOFFSET )
//DeadCode JON 2Aug00 					{
//DeadCode JON 2Aug00 						TileElement* cTile = tileCacheGrid+currResList->offScreenOldest;
//DeadCode JON 2Aug00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DeadCode JON 2Aug00 						currResList->offScreenOldest = cTile->nextLink;
//DeadCode JON 2Aug00 						cTile->reset();
//DeadCode JON 2Aug00 						currResList->freeTiles++;
//DeadCode JON 2Aug00 					} else if ( currResList->offScreenRemaining != NULLTILEOFFSET )
//DeadCode JON 2Aug00 					{
//DeadCode JON 2Aug00 						TileElement* cTile = tileCacheGrid+currResList->offScreenRemaining;
//DeadCode JON 2Aug00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DeadCode JON 2Aug00 						currResList->offScreenRemaining = cTile->nextLink;
//DeadCode JON 2Aug00 						cTile->reset();
//DeadCode JON 2Aug00 						currResList->freeTiles++;
//DeadCode JON 2Aug00 					} else
//DeadCode JON 2Aug00 					{
//DeadCode JON 2Aug00 						break; // can't make any more space.
//DeadCode JON 2Aug00 					}
					if ( currResList->offScreen != NULLTILEOFFSET )
					{
						TileElement* cTile = tileCacheGrid+currResList->offScreen;
						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
						currResList->offScreen = cTile->nextLink;
						cTile->reset();
						currResList->freeTiles++;
					} else
					{
						break; // can't make any more space.
					}
				}

				TileElement* cTile = tileCacheGrid+offset;
				if ( cTile->textHandle != HTEXTNULL )
				{
					tileResList[cTile->currentRes].freeTiles++;
					g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);					
					cTile->textHandle=HTEXTNULL;
				}
				currResList->underResTile = cTile->nextLink;
				TileResList::add( currResList->newTile, offset );
				offset = currResList->underResTile;
				currResList->numNewTiles++;
				cumWeight+=CHANGED_TILE_WEIGHT;
			}
			if ( offset != NULLTILEOFFSET )
				allAtReqLevel = false;
		}
	}

//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: cumWeight==0 ");
	if ( cumWeight == 0 && offScreenRes>=0 )
	{ // we can do some background processing - hurrah.
		rez = offScreenRes;//OFF_SCREEN_HIGHEST_REZ;
		TileResList* currResList = &tileResList[rez];
		while ( currResList->freeTiles <= currResList->numNewTiles && rez > 0)
		{
			currResList = &tileResList[--rez];
		}
		while( currResList->freeTiles > currResList->numNewTiles && bgList != NULLTILEOFFSET )
		{
			currResList->numNewTiles++;
			TileElement* cTile = (tileCacheGrid+bgList);
			UWord tmp = cTile->nextLink;
//DeadCode JON 2Aug00 			cTile->age = ageCount&AGEMASK;
			TileResList::add( currResList->newTile, bgList );
			bgList = tmp;
		}
	}

//TEMPCODE JON 6/7/00 	int numTilesMade = 0;
	// now actually make the new tiles
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: actually make ");
	for ( rez = 0; rez < 8; rez++ )
	{
		TileResList* currResList = &tileResList[rez];
		UWord offset = currResList->newTile;
		while( offset != NULLTILEOFFSET && currResList->freeTiles > 0)
		{ // render these new tiles.
			TileElement* cTile = (tileCacheGrid+offset);
#ifndef NDEBUG
			if ( cTile->textHandle != HTEXTNULL )
				NOP;
//DeadCode MS 16Aug00 
//DeadCode MS 16Aug00 			//calculate the block number...
//DeadCode MS 16Aug00 			ULong blockX = (px+((offset%_wholeAreaSizeMIN)*_blockWidth)+(_blockWidth>>1)) >> Grid_Base::WORLDSPACEMOD;
//DeadCode MS 16Aug00 			ULong blockY = (pz+((offset/_wholeAreaSizeMIN)*_blockWidth)+(_blockWidth>>1)) >> Grid_Base::WORLDSPACEMOD;
//DeadCode MS 16Aug00 //			char blockStr[7];
//DeadCode MS 16Aug00 			char blockStr[]="Render Block: ?????? ";
//DeadCode MS 16Aug00 			const int stPos = 14;
//DeadCode MS 16Aug00 //			blockStr[stPos+6] = char(0);
//DeadCode MS 16Aug00 			blockStr[stPos+5] = '1'+char(blockY%8);
//DeadCode MS 16Aug00 			blockStr[stPos+3] = '1'+char((blockY/8)%8);
//DeadCode MS 16Aug00 			blockStr[stPos+1] = '1'+char((blockY/64)%8);
//DeadCode MS 16Aug00 			blockStr[stPos+4] = '1'+char(blockX%8);
//DeadCode MS 16Aug00 			blockStr[stPos+2] = '1'+char((blockX/8)%8);
//DeadCode MS 16Aug00 			blockStr[stPos+0] = '1'+char((blockX/64)%8);
//DeadCode MS 16Aug00 		    Mono_Text.Print((UByte*)blockStr);

#endif
			HTEXT newTH;
			g_lpLib3d->AllocateLandscapeTexture( 7-rez, newTH.textureHandle);
			cTile->textHandle = newTH;

			//render the tile colour data to this DD surface
//DeadCode MS 15Aug00 			Mono_Text.Print((UByte*)"MHLT: R2S ");
#ifndef _NO_TEXTURE_RENDER
			if (newTH!=HTEXTNULL)
				Three_Dee.pTMake->Render2Surface(newTH, 7-rez ,offset);
#endif
			//DeadCode MS 16Aug00 			Mono_Text.Print((UByte*)"MHLT: R2SE ");
			currResList->freeTiles--;
			cTile->currentRes = rez;
			offset = cTile->nextLink;
//TEMPCODE JON 6/7/00 			numTilesMade++;
		}
//DeadCode JON 2Aug00 		if ( currResList->offScreenOldest == NULLTILEOFFSET )
//DeadCode JON 2Aug00 			currResList->oldestAge = currResList->nextOldestAge;
	}

#ifdef DEBUG_GRID
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"MHLT: debug2 ");
	for ( i = 0; i< gS; i++ )
		resGrid[i+(2*dGS)] = tileCacheGrid[i].currentRes;

	// more test code - check that the same texture isn't being used twice...
	for ( i = WIDTH*WIDTH; i ; i-- )
	{
		if ( tileCacheGrid[i].textHandle == HTEXTNULL )
		{
			continue; // skip
		}
		for ( int j = WIDTH*WIDTH; j ; j-- )
		{
			if ( i !=j && tileCacheGrid[i].textHandle == tileCacheGrid[j].textHandle )
				NOP;
		}
	}
#endif

//DeadCode MS 16Aug00 	Mono_Text.Print((UByte*)"MHLT: return ");
	return allAtReqLevel;

//TEMPCODE JON 6/7/00 	if ( numTilesMade > numNewTiles && numTilesMade > 3 )
//TEMPCODE JON 6/7/00  		3


// what it was	
//DEADCODE JON 6/7/00 		int cumWeight = 0; // cumulative tile weight
//DEADCODE JON 6/7/00 	int rez;
//DEADCODE JON 6/7/00 	for ( rez = 7; rez >= 0; rez-- )
//DEADCODE JON 6/7/00 	{
//DEADCODE JON 6/7/00 		TileResList* currResList = &tileResList[rez];
//DEADCODE JON 6/7/00 		if ( currResList->newTile != NULLTILEOFFSET )
//DEADCODE JON 6/7/00 		{ // make some more space if needed
//DEADCODE JON 6/7/00 			if ( currResList->freeTiles < currResList->numNewTiles )
//DEADCODE JON 6/7/00 			{
//DEADCODE JON 6/7/00 				// we need to free up some tiles at this rez to continue.
//DEADCODE JON 6/7/00 				UWord remOffset = currResList->offScreenOldest;
//DEADCODE JON 6/7/00 				while ( remOffset != NULLTILEOFFSET && 
//DEADCODE JON 6/7/00 					currResList->freeTiles < currResList->numNewTiles )
//DEADCODE JON 6/7/00 				{
//DEADCODE JON 6/7/00 					TileElement* cTile = tileCacheGrid+remOffset;
//DEADCODE JON 6/7/00 					remOffset = cTile->nextLink;
//DEADCODE JON 6/7/00 					g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DEADCODE JON 6/7/00 					cTile->reset();
//DEADCODE JON 6/7/00 					currResList->freeTiles++;
//DEADCODE JON 6/7/00 					currResList->offScreenOldest = remOffset;
//DEADCODE JON 6/7/00 				}
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 				remOffset = currResList->offScreenRemaining;
//DEADCODE JON 6/7/00 				while ( remOffset != NULLTILEOFFSET && 
//DEADCODE JON 6/7/00 					currResList->freeTiles < currResList->numNewTiles )
//DEADCODE JON 6/7/00 				{
//DEADCODE JON 6/7/00 					TileElement* cTile = tileCacheGrid+remOffset;
//DEADCODE JON 6/7/00 					remOffset = cTile->nextLink;
//DEADCODE JON 6/7/00 					g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DEADCODE JON 6/7/00 					cTile->reset();
//DEADCODE JON 6/7/00 					currResList->freeTiles++;
//DEADCODE JON 6/7/00 					currResList->offScreenRemaining = remOffset;
//DEADCODE JON 6/7/00 				}
//DEADCODE JON 6/7/00 				if ( currResList->freeTiles < currResList->numNewTiles )
//DEADCODE JON 6/7/00 				{
//DEADCODE JON 6/7/00 					currResList->offScreenRemaining = NULLTILEOFFSET;
//DEADCODE JON 6/7/00 					// right now we need to shove any tiles we are unable to do into the next rez list
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 					if ( rez > 0 )
//DEADCODE JON 6/7/00 					{
//DEADCODE JON 6/7/00 						// get to the first one to move ( move the end of the list not the start )
//DEADCODE JON 6/7/00 						UWord offset = currResList->newTile;
//DEADCODE JON 6/7/00 						UWord tmp;
//DEADCODE JON 6/7/00 						if ( currResList->freeTiles > 0 )
//DEADCODE JON 6/7/00 						{
//DEADCODE JON 6/7/00 							for ( int i = currResList->freeTiles; i>0; i-- )
//DEADCODE JON 6/7/00 								offset = (tileCacheGrid+offset)->nextLink;
//DEADCODE JON 6/7/00 				
//DEADCODE JON 6/7/00 							tmp = offset;
//DEADCODE JON 6/7/00 							offset = (tileCacheGrid+offset)->nextLink;
//DEADCODE JON 6/7/00 							(tileCacheGrid+tmp)->nextLink = NULLTILEOFFSET;
//DEADCODE JON 6/7/00 						} else
//DEADCODE JON 6/7/00 						{
//DEADCODE JON 6/7/00 							currResList->newTile = NULLTILEOFFSET;
//DEADCODE JON 6/7/00 						}
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 						while( offset != NULLTILEOFFSET )
//DEADCODE JON 6/7/00 						{
//DEADCODE JON 6/7/00 							currResList->numNewTiles--;
//DEADCODE JON 6/7/00 							tileResList[rez-1].numNewTiles++;
//DEADCODE JON 6/7/00 							tmp = (tileCacheGrid+offset)->nextLink;
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 							TileResList::add( tileResList[rez-1].newTile, offset );
//DEADCODE JON 6/7/00 							offset = tmp;
//DEADCODE JON 6/7/00 						}
//DEADCODE JON 6/7/00 					} 
//DEADCODE JON 6/7/00 				}
//DEADCODE JON 6/7/00 			}
//DEADCODE JON 6/7/00 		}
//DEADCODE JON 6/7/00 		cumWeight += currResList->numNewTiles;
//DEADCODE JON 6/7/00 	}
//DEADCODE JON 6/7/00 	cumWeight*=NEW_TILE_WEIGHT;
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 	// now do a pass to make as many changed tiles as we can
//DEADCODE JON 6/7/00 	if ( cumWeight < MAX_WEIGHTED && bgCount > DO_BACKGROUND_CUTOFF )
//DEADCODE JON 6/7/00 	{
//DEADCODE JON 6/7/00 		// great we can now make some resolution changes
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 		// switch so we alternativley lower then raise resolutions
//DEADCODE JON 6/7/00 		static bool lowerRes = true;
//DEADCODE JON 6/7/00 		lowerRes = !lowerRes; 
//DEADCODE JON 6/7/00 		
//DEADCODE JON 6/7/00 		if ( lowerRes )
//DEADCODE JON 6/7/00 		{
//DEADCODE JON 6/7/00 			// when lowering resolutions start at the highest res and move on down
//DEADCODE JON 6/7/00 			// note - no need to start at the very highest as there will be nothing
//DEADCODE JON 6/7/00 			// of higher resolution anyway.
//DEADCODE JON 6/7/00 			for ( rez = 6; rez >= 0; rez-- )
//DEADCODE JON 6/7/00 			{
//DEADCODE JON 6/7/00 				TileResList* currResList = &tileResList[rez];
//DEADCODE JON 6/7/00 				UWord offset = currResList->overResTile;
//DEADCODE JON 6/7/00 				while ( offset != NULLTILEOFFSET && cumWeight < MAX_WEIGHTED )
//DEADCODE JON 6/7/00 				{
//DEADCODE JON 6/7/00 					if ( currResList->freeTiles == currResList->numNewTiles )
//DEADCODE JON 6/7/00 					{ // try to free some tiles
//DEADCODE JON 6/7/00 						if ( currResList->offScreenOldest != NULLTILEOFFSET )
//DEADCODE JON 6/7/00 						{
//DEADCODE JON 6/7/00 							TileElement* cTile = tileCacheGrid+currResList->offScreenOldest;
//DEADCODE JON 6/7/00 							g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DEADCODE JON 6/7/00 							currResList->offScreenOldest = cTile->nextLink;
//DEADCODE JON 6/7/00 							cTile->reset();
//DEADCODE JON 6/7/00 							currResList->freeTiles++;
//DEADCODE JON 6/7/00 						} else if ( currResList->offScreenRemaining != NULLTILEOFFSET )
//DEADCODE JON 6/7/00 						{
//DEADCODE JON 6/7/00 							TileElement* cTile = tileCacheGrid+currResList->offScreenRemaining;
//DEADCODE JON 6/7/00 							g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DEADCODE JON 6/7/00 							currResList->offScreenRemaining = cTile->nextLink;
//DEADCODE JON 6/7/00 							cTile->reset();
//DEADCODE JON 6/7/00 							currResList->freeTiles++;
//DEADCODE JON 6/7/00 						} else
//DEADCODE JON 6/7/00 							break; // can't make any more space.
//DEADCODE JON 6/7/00 					}
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 					TileElement* cTile = tileCacheGrid+offset;
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 					if ( cTile->textHandle != HTEXTNULL )
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 					{
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 						tileResList[cTile->currentRes].freeTiles++;
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);					
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 						cTile->textHandle=HTEXTNULL;
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 					}
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 					currResList->overResTile = cTile->nextLink;
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 					TileResList::add( currResList->newTile, offset );
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 					offset = currResList->overResTile;
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 					currResList->numNewTiles++;
//DEADCODE JON 6/7/00 //DEADCODE JON 6/7/00 					cumWeight+=CHANGED_TILE_WEIGHT;
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 					if ( cTile->textHandle != HTEXTNULL )
//DEADCODE JON 6/7/00 					{ // we can do the quick reduce
//DEADCODE JON 6/7/00 						tileResList[cTile->currentRes].freeTiles++;
//DEADCODE JON 6/7/00 						currResList->freeTiles--;
//DEADCODE JON 6/7/00 						HTEXT newTH;
//DEADCODE JON 6/7/00 						g_lpLib3d->AllocateLandscapeTexture( 7-rez, newTH.textureHandle);
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 						// now make the lower rez version
//DEADCODE JON 6/7/00 						g_lpLib3d->ReduceLandQuality( cTile->textHandle.textureHandle, newTH.textureHandle );
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);					
//DEADCODE JON 6/7/00 						cTile->textHandle=newTH;
//DEADCODE JON 6/7/00 						cTile->currentRes=rez;
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 						currResList->overResTile = cTile->nextLink;
//DEADCODE JON 6/7/00 						offset = currResList->overResTile;
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 //						cumWeight+=CHANGED_TILE_WEIGHT;
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 					} else
//DEADCODE JON 6/7/00 					{ // can't do the quick reduce as we've already killed the source when reducing other stuff ( i think...)
//DEADCODE JON 6/7/00 						currResList->overResTile = cTile->nextLink;
//DEADCODE JON 6/7/00 						TileResList::add( currResList->newTile, offset );
//DEADCODE JON 6/7/00 						offset = currResList->overResTile;
//DEADCODE JON 6/7/00 						currResList->numNewTiles++;
//DEADCODE JON 6/7/00 						cumWeight+=CHANGED_TILE_WEIGHT;
//DEADCODE JON 6/7/00 					}
//DEADCODE JON 6/7/00 				}
//DEADCODE JON 6/7/00 			}
//DEADCODE JON 6/7/00 			
//DEADCODE JON 6/7/00 		} else
//DEADCODE JON 6/7/00 		{
//DEADCODE JON 6/7/00 			// when raising resolutions start at the highest again,
//DEADCODE JON 6/7/00 			// but don't bother wiv the lowest
//DEADCODE JON 6/7/00 			for ( rez = 7; rez >0; rez-- )
//DEADCODE JON 6/7/00 			{
//DEADCODE JON 6/7/00 				TileResList* currResList = &tileResList[rez];
//DEADCODE JON 6/7/00 				UWord offset = currResList->underResTile;
//DEADCODE JON 6/7/00 				while ( offset != NULLTILEOFFSET && cumWeight < MAX_WEIGHTED )
//DEADCODE JON 6/7/00 				{
//DEADCODE JON 6/7/00 					if ( currResList->freeTiles == currResList->numNewTiles )
//DEADCODE JON 6/7/00 					{ // try to free some tiles
//DEADCODE JON 6/7/00 						if ( currResList->offScreenOldest != NULLTILEOFFSET )
//DEADCODE JON 6/7/00 						{
//DEADCODE JON 6/7/00 							TileElement* cTile = tileCacheGrid+currResList->offScreenOldest;
//DEADCODE JON 6/7/00 							g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DEADCODE JON 6/7/00 							currResList->offScreenOldest = cTile->nextLink;
//DEADCODE JON 6/7/00 							cTile->reset();
//DEADCODE JON 6/7/00 							currResList->freeTiles++;
//DEADCODE JON 6/7/00 						} else if ( currResList->offScreenRemaining != NULLTILEOFFSET )
//DEADCODE JON 6/7/00 						{
//DEADCODE JON 6/7/00 							TileElement* cTile = tileCacheGrid+currResList->offScreenRemaining;
//DEADCODE JON 6/7/00 							g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);
//DEADCODE JON 6/7/00 							currResList->offScreenRemaining = cTile->nextLink;
//DEADCODE JON 6/7/00 							cTile->reset();
//DEADCODE JON 6/7/00 							currResList->freeTiles++;
//DEADCODE JON 6/7/00 						} else
//DEADCODE JON 6/7/00 							break; // can't make any more space.
//DEADCODE JON 6/7/00 					}
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 					TileElement* cTile = tileCacheGrid+offset;
//DEADCODE JON 6/7/00 					if ( cTile->textHandle != HTEXTNULL )
//DEADCODE JON 6/7/00 					{
//DEADCODE JON 6/7/00 						tileResList[cTile->currentRes].freeTiles++;
//DEADCODE JON 6/7/00 						g_lpLib3d->FreeLandscapeTexture(cTile->textHandle.textureHandle);					
//DEADCODE JON 6/7/00 						cTile->textHandle=HTEXTNULL;
//DEADCODE JON 6/7/00 					}
//DEADCODE JON 6/7/00 					currResList->underResTile = cTile->nextLink;
//DEADCODE JON 6/7/00 					TileResList::add( currResList->newTile, offset );
//DEADCODE JON 6/7/00 					offset = currResList->underResTile;
//DEADCODE JON 6/7/00 					currResList->numNewTiles++;
//DEADCODE JON 6/7/00 					cumWeight+=CHANGED_TILE_WEIGHT;
//DEADCODE JON 6/7/00 				}
//DEADCODE JON 6/7/00 			}
//DEADCODE JON 6/7/00 		}
//DEADCODE JON 6/7/00 	}
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 	if ( cumWeight == 0 )
//DEADCODE JON 6/7/00 	{ // we can do some background processing - hurrah.
//DEADCODE JON 6/7/00 		rez = 3;
//DEADCODE JON 6/7/00 		TileResList* currResList = &tileResList[rez];
//DEADCODE JON 6/7/00 		while ( currResList->freeTiles <= currResList->numNewTiles && rez > 0)
//DEADCODE JON 6/7/00 		{
//DEADCODE JON 6/7/00 			currResList = &tileResList[--rez];
//DEADCODE JON 6/7/00 		}
//DEADCODE JON 6/7/00 		while( currResList->freeTiles > currResList->numNewTiles && bgList != NULLTILEOFFSET )
//DEADCODE JON 6/7/00 		{
//DEADCODE JON 6/7/00 			currResList->numNewTiles++;
//DEADCODE JON 6/7/00 			TileElement* cTile = (tileCacheGrid+bgList);
//DEADCODE JON 6/7/00 			UWord tmp = cTile->nextLink;
//DEADCODE JON 6/7/00 			cTile->age = ageCount&AGEMASK;
//DEADCODE JON 6/7/00 			TileResList::add( currResList->newTile, bgList );
//DEADCODE JON 6/7/00 			bgList = tmp;
//DEADCODE JON 6/7/00 		}
//DEADCODE JON 6/7/00 	}
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 //TEMPCODE JON 5/12/00 	int numTilesMade = 0;
//DEADCODE JON 6/7/00 	// now actually make the new tiles
//DEADCODE JON 6/7/00 	for ( rez = 0; rez < 8; rez++ )
//DEADCODE JON 6/7/00 	{
//DEADCODE JON 6/7/00 		TileResList* currResList = &tileResList[rez];
//DEADCODE JON 6/7/00 		UWord offset = currResList->newTile;
//DEADCODE JON 6/7/00 		while( offset != NULLTILEOFFSET && currResList->freeTiles > 0)
//DEADCODE JON 6/7/00 		{ // render these new tiles.
//DEADCODE JON 6/7/00 			TileElement* cTile = (tileCacheGrid+offset);
//DEADCODE JON 6/7/00 			HTEXT newTH;
//DEADCODE JON 6/7/00 			g_lpLib3d->AllocateLandscapeTexture( 7-rez, newTH.textureHandle);
//DEADCODE JON 6/7/00 			cTile->textHandle = newTH;
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 			//render the tile colour data to this DD surface
//DEADCODE JON 6/7/00 			if (newTH!=HTEXTNULL)
//DEADCODE JON 6/7/00 				Three_Dee.pTMake->Render2Surface(newTH, 7-rez ,offset);
//DEADCODE JON 6/7/00 
//DEADCODE JON 6/7/00 			currResList->freeTiles--;
//DEADCODE JON 6/7/00 			cTile->currentRes = rez;
//DEADCODE JON 6/7/00 			offset = cTile->nextLink;
//DEADCODE JON 6/7/00 //TEMPCODE JON 5/12/00 			numTilesMade++;
//DEADCODE JON 6/7/00 		}
//DEADCODE JON 6/7/00 		if ( currResList->offScreenOldest == NULLTILEOFFSET )
//DEADCODE JON 6/7/00 			currResList->oldestAge = currResList->nextOldestAge;
//DEADCODE JON 6/7/00 	}


//DEADCODE JON 4/26/00 	SLong 	NUM_1024_TEXTURES,
//DEADCODE JON 4/26/00 			NUM_512_TEXTURES,
//DEADCODE JON 4/26/00 			NUM_256_TEXTURES,
//DEADCODE JON 4/26/00 			NUM_128_TEXTURES,
//DEADCODE JON 4/26/00 			NUM_64_TEXTURES,
//DEADCODE JON 4/26/00 			NUM_32_TEXTURES,
//DEADCODE JON 4/26/00 			NUM_16_TEXTURES,
//DEADCODE JON 4/26/00 			NUM_8_TEXTURES;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	g_lpLib3d->GetLandscapeTextureCount(NUM_1024_TEXTURES,	NUM_512_TEXTURES,
//DEADCODE JON 4/26/00 										NUM_256_TEXTURES,	NUM_128_TEXTURES,
//DEADCODE JON 4/26/00 										NUM_64_TEXTURES,	NUM_32_TEXTURES,
//DEADCODE JON 4/26/00 										NUM_16_TEXTURES,	NUM_8_TEXTURES);
//DEADCODE JON 3/30/00 	const SLong MAX_TILES_PER_FRAME=8;
//DEADCODE JON 4/26/00 	const SLong wholeAreaSize=_wholeAreaSizeMIN;
//DEADCODE JON 4/26/00 	const SLong GRID_SIZE=wholeAreaSize*wholeAreaSize;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	struct ChangedTile
//DEADCODE JON 4/26/00 	{
//DEADCODE JON 4/26/00 		UWord offset;
//DEADCODE JON 4/26/00 		HTEXT oldHTexture;
//DEADCODE JON 4/26/00 		UByte newRez;
//DEADCODE JON 4/26/00 		UByte pad;
//DEADCODE JON 4/26/00 	};
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	struct NewTile
//DEADCODE JON 4/26/00 	{
//DEADCODE JON 4/26/00 		UWord offset;
//DEADCODE JON 4/26/00 		UByte newRez;
//DEADCODE JON 4/26/00 		UByte pad;
//DEADCODE JON 4/26/00 	};
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	if (pLastGrid==NULL)
//DEADCODE JON 4/26/00 	{
//DEADCODE JON 4/26/00 		pLastGrid=new UByte[GRID_SIZE];
//DEADCODE JON 4/26/00 		pHTextureGrid=new HTEXT[GRID_SIZE];
//DEADCODE JON 4/26/00 	 	memset(pLastGrid,0xFF,GRID_SIZE);
//DEADCODE JON 4/26/00 	 	memset(pHTextureGrid,0xFF,GRID_SIZE*sizeof(HTEXT));
//DEADCODE JON 4/26/00 	}
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	ChangedTile* changedTiles=new ChangedTile[GRID_SIZE];
//DEADCODE JON 4/26/00 	NewTile* newTiles=new NewTile[GRID_SIZE];
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00  	if (lastPx!=px || lastPz!=pz)
//DEADCODE JON 4/26/00  	{
//DEADCODE JON 4/26/00  		if (lastPx!=-1 && lastPz!=-1)
//DEADCODE JON 4/26/00  		{
//DEADCODE JON 4/26/00  			Dropped* droppedTextures=new Dropped;
//DEADCODE JON 4/26/00  			ScrollGrid(px-lastPx,pz-lastPz,pLastGrid);
//DEADCODE JON 4/26/00  			ScrollGridDis(px-lastPx,pz-lastPz,pHTextureGrid,droppedTextures);
//DEADCODE JON 4/26/00  			for (SLong i=droppedTextures->num;i>=0;i--)
//DEADCODE JON 4/26/00 				g_lpLib3d->FreeLandscapeTexture(droppedTextures->hText[i].textureHandle);
//DEADCODE JON 4/26/00  			delete[]droppedTextures;
//DEADCODE JON 4/26/00  		}
//DEADCODE JON 4/26/00  		lastPx=px;
//DEADCODE JON 4/26/00  		lastPz=pz;
//DEADCODE JON 4/26/00  	}
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	UByte* pnewgrid=new UByte[GRID_SIZE];
//DEADCODE JON 4/26/00 	memset(pnewgrid,0xFF,GRID_SIZE);
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	ULong startPos=GRID_SIZE>>1;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	UByte* psrc=gridCone+startPos;
//DEADCODE JON 4/26/00 	UByte* pdst=pnewgrid+startPos;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	SLong h_dda,v_dda;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	UByte dir_state,dir_count,dir_max;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	UByte texture_scale,texture_count,texture_max;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	texture_scale=texture_count=0;
//DEADCODE JON 4/26/00 	texture_max=NUM_1024_TEXTURES;
//DEADCODE JON 4/26/00 	
//DEADCODE JON 4/26/00 	dir_state=dir_count=0;
//DEADCODE JON 4/26/00 	dir_max=1;
//DEADCODE JON 4/26/00 	h_dda=1;
//DEADCODE JON 4/26/00 	v_dda=-wholeAreaSize;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	//check to see whether the very high detail textures have
//DEADCODE JON 4/26/00 	//been disabled!
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	if (texture_max==0)
//DEADCODE JON 4/26/00 		while (texture_max==0)
//DEADCODE JON 4/26/00 		{
//DEADCODE JON 4/26/00 			texture_scale++;
//DEADCODE JON 4/26/00 			if (texture_scale==1)		texture_max=NUM_512_TEXTURES;
//DEADCODE JON 4/26/00 			else if (texture_scale==2)	texture_max=NUM_256_TEXTURES;
//DEADCODE JON 4/26/00 			else if (texture_scale==3)	texture_max=NUM_128_TEXTURES;
//DEADCODE JON 4/26/00 			else if (texture_scale==4)	texture_max=NUM_64_TEXTURES;
//DEADCODE JON 4/26/00 			else if (texture_scale==5)	texture_max=NUM_32_TEXTURES;
//DEADCODE JON 4/26/00 			else if (texture_scale==6)	texture_max=NUM_16_TEXTURES;
//DEADCODE JON 4/26/00 			else if (texture_scale==7)	texture_max=NUM_8_TEXTURES;
//DEADCODE JON 4/26/00 			else assert(false&&"ERROR: Run out of textures(1)");
//DEADCODE JON 4/26/00 		}
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	for (SLong i=GRID_SIZE;i--;)
//DEADCODE JON 4/26/00 	{
//DEADCODE JON 4/26/00 		if (*psrc==1)
//DEADCODE JON 4/26/00 		{
//DEADCODE JON 4/26/00 			*pdst=texture_scale;
//DEADCODE JON 4/26/00 			texture_count++;
//DEADCODE JON 4/26/00 			if (texture_count==texture_max)
//DEADCODE JON 4/26/00 			{
//DEADCODE JON 4/26/00 				texture_scale++;
//DEADCODE JON 4/26/00 				texture_count=0;
//DEADCODE JON 4/26/00 				if (texture_scale==1)		texture_max=NUM_512_TEXTURES;
//DEADCODE JON 4/26/00 				else if (texture_scale==2)	texture_max=NUM_256_TEXTURES;
//DEADCODE JON 4/26/00 				else if (texture_scale==3)	texture_max=NUM_128_TEXTURES;
//DEADCODE JON 4/26/00 				else if (texture_scale==4)	texture_max=NUM_64_TEXTURES;
//DEADCODE JON 4/26/00 				else if (texture_scale==5)	texture_max=NUM_32_TEXTURES;
//DEADCODE JON 4/26/00 				else if (texture_scale==6)	texture_max=NUM_16_TEXTURES;
//DEADCODE JON 4/26/00 				else if (texture_scale==7)	texture_max=NUM_8_TEXTURES;
//DEADCODE JON 4/26/00 				else assert(false&&"ERROR: Run out of textures(2)");
//DEADCODE JON 4/26/00 			}
//DEADCODE JON 4/26/00 		}
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 		if (dir_state==0)
//DEADCODE JON 4/26/00 		{
//DEADCODE JON 4/26/00 			psrc+=h_dda;
//DEADCODE JON 4/26/00 			pdst+=h_dda;
//DEADCODE JON 4/26/00 			dir_count++;
//DEADCODE JON 4/26/00 			if (dir_count==dir_max)
//DEADCODE JON 4/26/00 			{
//DEADCODE JON 4/26/00 				dir_count=0;
//DEADCODE JON 4/26/00 				dir_state++;
//DEADCODE JON 4/26/00 			}
//DEADCODE JON 4/26/00 		}
//DEADCODE JON 4/26/00 		else
//DEADCODE JON 4/26/00 		{
//DEADCODE JON 4/26/00 			psrc+=v_dda;
//DEADCODE JON 4/26/00 			pdst+=v_dda;
//DEADCODE JON 4/26/00 			dir_count++;
//DEADCODE JON 4/26/00 			if (dir_count==dir_max)
//DEADCODE JON 4/26/00 			{
//DEADCODE JON 4/26/00 				h_dda=-h_dda;
//DEADCODE JON 4/26/00 				v_dda=-v_dda;
//DEADCODE JON 4/26/00 				dir_count=0;
//DEADCODE JON 4/26/00 				dir_state=0;
//DEADCODE JON 4/26/00 				dir_max++;
//DEADCODE JON 4/26/00 			}
//DEADCODE JON 4/26/00 		}
//DEADCODE JON 4/26/00 	}
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	//compare the new grid with the old grid to determine
//DEADCODE JON 4/26/00 	//what texture updates are needed
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	psrc=pnewgrid;
//DEADCODE JON 4/26/00 	pdst=pLastGrid;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	SLong new_tiles,changed_tiles;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	new_tiles=changed_tiles=0;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	for (i=GRID_SIZE;i--;psrc++,pdst++)
//DEADCODE JON 4/26/00 		if (*psrc!=*pdst)
//DEADCODE JON 4/26/00 		{
//DEADCODE JON 4/26/00 		 	//found a difference!!
//DEADCODE JON 4/26/00 			UByte srcVal=*psrc;
//DEADCODE JON 4/26/00 			UByte dstVal=*pdst;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 			//test to see if a new tile that wasn't visible on the
//DEADCODE JON 4/26/00 			//last frame has just moved in to view
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 			if (dstVal==0xFF)
//DEADCODE JON 4/26/00 			{
//DEADCODE JON 4/26/00 				newTiles[new_tiles].newRez=srcVal;
//DEADCODE JON 4/26/00 				newTiles[new_tiles++].offset=
//DEADCODE JON 4/26/00 					(UWord)(ULong(pdst)-ULong(pLastGrid));
//DEADCODE JON 4/26/00 				*pdst=*psrc;
//DEADCODE JON 4/26/00 			}
//DEADCODE JON 4/26/00 			//test to see if a tile that was visible on the last frame
//DEADCODE JON 4/26/00 			//has just gone out of view
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 			else if (srcVal==0xFF)
//DEADCODE JON 4/26/00 			{
//DEADCODE JON 4/26/00 				UWord offset=(UWord)(ULong(pdst)-ULong(pLastGrid));
//DEADCODE JON 4/26/00 				g_lpLib3d->FreeLandscapeTexture((pHTextureGrid+offset)->textureHandle);
//DEADCODE JON 4/26/00 				*(pHTextureGrid+offset)=HTEXTNULL;
//DEADCODE JON 4/26/00 				*pdst=*psrc;
//DEADCODE JON 4/26/00 			}
//DEADCODE JON 4/26/00 			//the difference must be due to a tile resolution change
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 			else
//DEADCODE JON 4/26/00 			{
//DEADCODE JON 4/26/00 				UWord offset=(UWord)(ULong(pdst)-ULong(pLastGrid));
//DEADCODE JON 4/26/00 				changedTiles[changed_tiles].oldHTexture=*(pHTextureGrid+offset);
//DEADCODE JON 4/26/00 				g_lpLib3d->FreeLandscapeTexture(changedTiles[changed_tiles].oldHTexture.textureHandle);
//DEADCODE JON 4/26/00 				*(pHTextureGrid+offset)=HTEXTNULL;
//DEADCODE JON 4/26/00 				changedTiles[changed_tiles].newRez=srcVal;
//DEADCODE JON 4/26/00 				changedTiles[changed_tiles++].offset=offset;
//DEADCODE JON 4/26/00 			}
//DEADCODE JON 4/26/00 		}
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	//deal with any tile resolution changes
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	ChangedTile* pct=changedTiles;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	while (changed_tiles--)
//DEADCODE JON 4/26/00 	{
//DEADCODE JON 4/26/00 		//release the old tile
//DEADCODE JON 4/26/00 		UWord offset=pct->offset;
//DEADCODE JON 4/26/00 		*(pLastGrid+offset)=pct->newRez;
//DEADCODE JON 4/26/00 		HTEXT newTH;
//DEADCODE JON 4/26/00 		g_lpLib3d->FreeLandscapeTexture((pHTextureGrid+offset)->textureHandle);
//DEADCODE JON 4/26/00 		g_lpLib3d->AllocateLandscapeTexture(pct->newRez,newTH.textureHandle);
//DEADCODE JON 4/26/00 		*(pHTextureGrid+offset)=newTH;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 		//render the tile colour data to this DD surface
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 		if (newTH!=HTEXTNULL)
//DEADCODE JON 4/26/00 			Three_Dee.pTMake->Render2Surface(newTH,pct->newRez,offset);
//DEADCODE JON 4/26/00 		pct++;
//DEADCODE JON 4/26/00 	}
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	NewTile* pnt=newTiles;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	while (new_tiles--)
//DEADCODE JON 4/26/00 	{
//DEADCODE JON 4/26/00 		UWord offset=pnt->offset;
//DEADCODE JON 4/26/00 		HTEXT newTH;
//DEADCODE JON 4/26/00 		g_lpLib3d->AllocateLandscapeTexture(pnt->newRez,newTH.textureHandle);
//DEADCODE JON 4/26/00 		*(pHTextureGrid+offset)=newTH;
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 		//render the tile colour data to this DD surface
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 		if (newTH!=HTEXTNULL)
//DEADCODE JON 4/26/00 			Three_Dee.pTMake->Render2Surface(newTH,pnt->newRez,offset);
//DEADCODE JON 4/26/00 		pnt++;
//DEADCODE JON 4/26/00 	}
//DEADCODE JON 4/26/00 
//DEADCODE JON 4/26/00 	delete[]pnewgrid;
//DEADCODE JON 4/26/00 	delete[]changedTiles;
//DEADCODE JON 4/26/00 	delete[]newTiles;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FillDataGrid
//Author		Paul.   
//Date			Thu 14 May 1998
//------------------------------------------------------------------------------
bool LandScape::FillDataGrid(SLong ox,SLong oz)
{
	Three_Dee.pMigLand->ResetDecompCount();
	SLong ix;
	UByte* pConeData=gridCone;
	DataRecord* dataBlock=pDataBlocks;
//	UByte* pGroundDetail=groundDetail;

//DeadCode JON 2Aug00 #pragma message( __HERE__ "ground detail levels here" )
//DeadCode JON 2Aug00 	static UByte rezLevels[ _wholeAreaSizeMIN*_wholeAreaSizeMIN ];
//DeadCode JON 2Aug00 	static bool make = true;
//DeadCode JON 2Aug00 	if ( make  ) // make the damn thing
//DeadCode JON 2Aug00 	{
//DeadCode JON 2Aug00 		make = false;
//DeadCode JON 2Aug00 		UByte* cur = rezLevels;
//DeadCode JON 2Aug00 		for( int x = 0; x<_wholeAreaSizeMIN; x++ )
//DeadCode JON 2Aug00 			for ( int y = 0; y<_wholeAreaSizeMIN; y++ )
//DeadCode JON 2Aug00 			{
//DeadCode JON 2Aug00 				int xoff = (_wholeAreaSizeMIN/2)-x;
//DeadCode JON 2Aug00 				int yoff = (_wholeAreaSizeMIN/2)-y;
//DeadCode JON 2Aug00 				int d = sqrt( xoff*xoff + yoff*yoff );
//DeadCode JON 2Aug00 				switch (d)
//DeadCode JON 2Aug00 				{
//DeadCode JON 2Aug00 				case 0:
//DeadCode JON 2Aug00 				case 1:
//DeadCode JON 2Aug00 					*cur++ = 0;
//DeadCode JON 2Aug00 					break;
//DeadCode JON 2Aug00 				case 2:
//DeadCode JON 2Aug00 				case 3:
//DeadCode JON 2Aug00 					*cur++ = 1;
//DeadCode JON 2Aug00 					break;
//DeadCode JON 2Aug00 				case 4:
//DeadCode JON 2Aug00 					*cur++ = 2;
//DeadCode JON 2Aug00 					break;
//DeadCode JON 2Aug00 				case 5:
//DeadCode JON 2Aug00 					*cur++ = 3;
//DeadCode JON 2Aug00 					break;
//DeadCode JON 2Aug00 				case 6:
//DeadCode JON 2Aug00 					*cur++ = 4;
//DeadCode JON 2Aug00 					break;
//DeadCode JON 2Aug00 				case 7:
//DeadCode JON 2Aug00 					*cur++ = 5;
//DeadCode JON 2Aug00 					break;
//DeadCode JON 2Aug00 				case 8:
//DeadCode JON 2Aug00 					*cur++ = 6;
//DeadCode JON 2Aug00 					break;
//DeadCode JON 2Aug00 				default:
//DeadCode JON 2Aug00 					*cur++ = 7;
//DeadCode JON 2Aug00 					break;
//DeadCode JON 2Aug00 				}
//DeadCode JON 2Aug00 			}
//DeadCode JON 2Aug00 	}
//DeadCode JON 2Aug00 	UByte* pGroundDetail=rezLevels;

	TileElement* cTile = tileCacheGrid;
	
	SLong wholeAreaSize=_wholeAreaSizeMIN;

	for (int row=0;row<wholeAreaSize;row++)
	{
		ix=ox;
	 	for (int col=0;col<wholeAreaSize;col++)
		{
			if (*pConeData)
			{
				//Fill in array of land data pointers for later

				DataRecord& dR=*dataBlock;
//DeadCode JON 2Aug00 				UByte gD=*pGroundDetail;
#ifdef _ALWAYS_FULL_REZ
				UByte gD=0;
#else
				UByte gD=cTile->meshRes;
#endif
//DeadCode JON 20Jun00 #pragma warnmsg ( "remove me" )
//DeadCode JON 20Jun00 	if ( ix==28311552 && oz==33685504 )
//DeadCode JON 20Jun00 		NOP;
				dR=Three_Dee.pTMake->GetBlock(ix,oz);
				dR=Three_Dee.pMigLand->GetData(ix,oz,gD,( /*cTile->viewRadius < 2 &&*/ gD< TILE_REZ_LIMIT_ITEM ),dR);
			}
			else
			{
				DataRecord& dR=*dataBlock;
			 	dR.pData=NULL;
				dR.dataLen=0;
			}
			pConeData++;
			dataBlock++;
//DeadCode JON 2Aug00 			pGroundDetail++;
			cTile++;
			ix+=_blockWidth;
		}
		oz+=_blockWidth;
	}

	dataBlock=pDataBlocks;
	for (row=wholeAreaSize*wholeAreaSize;row>0;row--)
	{
		DataRecord& dR=*dataBlock;
		if (dR.pData)
		{
			AltPointsHdr *aph=(AltPointsHdr*)dR.pData;
			if (!aph->CheckChecksum())
				return false;
			//if (aph->vertexCount<4 || 
			//	aph->vertexCount<aph->topEdgePoints+aph->rightEdgePoints+aph->bottomEdgePoints+aph->leftEdgePoints)
			//	return false;
		}
		dataBlock++;
	}
	return true;
}

SLong ibase_x,ibase_z,iscale_factor,itexture;

//DEAD static SLong softwarePolyCount;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GeneratePointData
//Author		Paul.   
//Date			Tue 20 Jan 1998
//------------------------------------------------------------------------------
bool LandScape::UpdateTexturesWRTViewPos()
{
#ifndef	_NOLANDSCAPE_
//DEADCODE JON 4/6/00 	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
//DEADCODE JON 4/6/00 	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
//DEADCODE JON 4/6/00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
//DEADCODE JON 4/6/00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
//DEADCODE JON 4/6/00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);
//DEADCODE JON 4/6/00 	if (View_Point->InCockpit())								//RJS 15Mar00
//DEADCODE JON 4/6/00 		g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->eyeHeading);
//DEADCODE JON 4/6/00 //DeadCode RJS 15Mar100 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,1,14829100,0);
//DEADCODE JON 4/6/00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,50,view_dist);
//DEADCODE JON 4/6/00 	g_lpLib3d->SetFogColour(0x0090B8E8);
//DEADCODE JON 4/6/00 
//DEADCODE JON 4/6/00 	D3DVECTOR viewMods;
//DEADCODE JON 4/6/00 	viewMods.x=(D3DVALUE)-viewer_x;
//DEADCODE JON 4/6/00 	viewMods.y=(D3DVALUE)-viewer_y;
//DEADCODE JON 4/6/00 	viewMods.z=(D3DVALUE)-viewer_z;
//DEADCODE JON 4/6/00 	g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

//DEADCODE JON 4/6/00 	SetUpVisibleCones();

//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: start ");
	SLong gx,gz;
	gx=View_Point->World.X;
	gz=View_Point->World.Z;
	Three_Dee.pMigLand->SetViewpoint(View_Point);
 	Three_Dee.pMigLand->ProcessSeekRequests();
 	Three_Dee.pTMake->ChkUpdate(gx,gz);

	SLong ox,oz;

	//Generate start position based on the current viewpoint

	ox=(gx&~ULong(_blockWidth-1))-((_halfAreaSizeMIN)*_blockWidth);
	oz=(gz&~ULong(_blockWidth-1))-((_halfAreaSizeMIN)*_blockWidth);

//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: check ");
	if (!Three_Dee.pTMake->CheckCache())
	{
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: refresh1 ");
		PossibleTeleport();
//		RefreshLandscape();
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: false ");

		return false;
	}
//DEADCODE JON 3/8/00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,50,_hirezDrawDist);
//DEADCODE JON 3/8/00 	GridCone(ox,oz);
//DEADCODE JON 3/8/00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,50,_blockWidth*_horizonDist);
//DEADCODE JON 3/8/00 	g_lpLib3d->SetFogColour(0x0090B8E8);

//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: manage ");
#ifndef _NOTILEMAKE
	ManageHighLandTextures(ox,oz);
#endif

//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: fill ");
	if (!FillDataGrid(ox,oz))
	{
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: refresh2 ");
		PossibleTeleport();
//		RefreshLandscape();
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: false ");
		return false;
	}
#endif
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"UTWRTVP: true ");
	return true;
}
void LandScape::GeneratePointData()
{
	SLong ox,oz;
	SLong halfAreaSize=_halfAreaSizeMIN;
//DeadCode JON 20Oct00 	SLong wholeAreaSize=_wholeAreaSizeMIN;
	ox=(viewer_x&~ULong(_blockWidth-1))-halfAreaSize*_blockWidth;
	oz=(viewer_z&~ULong(_blockWidth-1))-halfAreaSize*_blockWidth;
	View_Point->isLightShaded=TRUE;
	LIGHTFLAG lf;
	
	if (Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])	lf=	LF_LIGHTING;
	else												lf= LF_AMBIENT;
	LightVec& sunPos=Three_Dee.SunLightVector;
	g_lpLib3d->SetLightVector(R3DVALUE(sunPos.ni.i),
								R3DVALUE(sunPos.nj.i),
								R3DVALUE(sunPos.nk.i));
	g_lpLib3d->SetObjectLighting(lf);
	bAnyLandDrawn=FALSE;
//DeadCode JON 20Sep00 	ProcessLights(ox,oz);
	HighDetailTileRender(ox,oz);
	lf=LF_AMBIENT;
	g_lpLib3d->SetObjectLighting(lf); 
	View_Point->isLightShaded=FALSE;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HorizonTile
//Author		Jon.   													
//Date			Thurs 28Sep00
// draws a tile with horizon info...
// takes x and z cm
//------------------------------------------------------------------------------
inline void LandScape::HorizonTile( const int x, const int z )
{

	SLong ix = x/_blockWidth;//x>>_blockShift);
	SLong oz = z/_blockWidth;//z>>_blockShift;

	LIGHTFLAG lf = LF_AMBIENT;
	g_lpLib3d->SetObjectLighting( lf );
//DeadCode JON 28Sep00 	const int offsetAmount = (((_horizonPoints-_wholeAreaSizeMIN)/2) + 64) - _horizonDist;
	const int offsetAmount = 64;
	float imx = ( ix/*+gridOffs.jx*/ + offsetAmount - gridOffs.hx ) << 1;
	float imz = ( oz/*+gridOffs.jz*/ + offsetAmount - gridOffs.hz ) << 1;

	Lib3DPoint* corners = g_lpLib3d->BeginFan( HMATERIAL(horizonImg), 4 );	

	Grid_Base* cornerAlt = (Grid_Base*) Grid_Base::gridfiles[Grid_Base::GF_CORNERALT].getdata();

	corners[0].setPosition( 
		x, 
		(cornerAlt->getMod( ix, oz ) << _altitudeShift),
		z );
	corners[0].setIMapCoords( imx, imz );

	corners[1].setPosition( 
		x, 
		(cornerAlt->getMod( ix, oz+1 ) << _altitudeShift),
		z+_blockWidth );
	corners[1].setIMapCoords( imx, imz+2 );

	corners[2].setPosition( 
		x+_blockWidth,
		(cornerAlt->getMod( ix+1, oz+1 ) << _altitudeShift),
		z+_blockWidth );
	corners[2].setIMapCoords( imx+2, imz+2 );

	corners[3].setPosition(
		x+_blockWidth,
		(cornerAlt->getMod( ix+1, oz ) << _altitudeShift),
		z );
	corners[3].setIMapCoords( imx+2, imz );

	g_lpLib3d->EndFan();
	g_lpLib3d->SetObjectLighting( lf );
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HighDetailTileRender
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
void LandScape::HighDetailTileRender(SLong ox,SLong oz)
{
	static SLong totTime=0;
	totTime += View_Point->RealDrawFrameTime();// ->DrawFrameTime();

	const UWord seaBase = FIL_SEA1_NUM;
	int framenum = (ULong(totTime/250)%6);
	if ( framenum > 3 )
		framenum = 6-framenum;
	FileNum	seaFile = FileNum(seaBase + framenum );
	LandMapNum seamap=LandMapNum(seaFile);
	ImageMapDescPtr	seaptr = seamap.GetLandMapPtr();

	SWord ddx= SWord( totTime>>6 );							
	ddx&=0xFF;


	const SLong wholeAreaSize=_wholeAreaSizeMIN;

	COORDS3D view;

	UByte* pConeData=gridCone;
	TileElement* currentGridElement = tileCacheGrid;
	DataRecord* dataBlock=pDataBlocks;

	view.Y=-viewer_y;

	//generate a value for 'treeHeight'
	raiseFlag = PreCalcRaise( viewer_y, hedgeHeight );//, cliffHeight );

	int x = ox>>Grid_Base::WORLDSPACEMOD;
	int z = oz>>Grid_Base::WORLDSPACEMOD;

	for (int row=0;row<wholeAreaSize;row++,oz+=_blockWidth)
	{
		view.Z=oz;
		SLong ix=ox;

		const  int tmpFudge = 7;
		const int tmpFudge2 = 64*8-8;
		if ( row+z > tmpFudge && row+z < tmpFudge2 )
		{ //draw
			for (int col=0;col<wholeAreaSize;col++,ix+=_blockWidth)
			{

				view.X=ix;

				if (*pConeData++)
				{
//					HTEXT textureHandle,
					const HTEXT nullHandle;
//DeadCode JON 23Oct00 					ULong dataLen;
//DeadCode JON 22Oct00 					UByte* pDataStream;

//					textureHandle = currentGridElement->textHandle;
					const int tmpFudge = 7;
					const int tmpFudge2 = 64*8-8;
	
#ifndef _NOTILEMAKE
	#ifndef _NO_TEXTURE_RENDER
					if (currentGridElement->textHandle!=nullHandle && ( col+x > tmpFudge && col+x < tmpFudge2 ))
	#else
					if (false)
	#endif
#else
					if ( true )
#endif
					{
//DeadCode JON 23Oct00 						dataLen=dataBlock->dataLen;
//DeadCode JON 20Oct00 						UByte* psavedata=pDataStream=(UByte*)dataBlock->pData;
				
//TempCode JON 23Oct00 						static int poo;
//TempCode JON 23Oct00 						if ( (poo++&1) )
					HiRezTile((UByte*)dataBlock->pData,dataBlock->dataLen,view,*currentGridElement,seaptr,ddx);

	//					if (groundDetail==UByte(_doHighGround))
	//						RenderTrees(psavedata,view);
					} else 
					{ // fake a block using the horizon information
						HorizonTile( ix, oz );
					}
				}
				currentGridElement++;
				dataBlock++;
			}
		} else
		{ // horizon
			for (int col=0;col<wholeAreaSize;col++,ix+=_blockWidth)
			{
				if (*pConeData++)
					HorizonTile( ix, oz );
				currentGridElement++;
				dataBlock++;
			}		
		}
	}
}

inline void LandScape::RenderSheep(const UByte* pDS,ULong sheepCount,const COORDS3D& view, const PointDef* inptDefs)
{

	item sheepItem;
	sheepItem.Anim=CloudAnimP;

	while (sheepCount--)
	{
		switch ( *pDS++ )
		{			
			case ITEM_TYPE_SHEEP:
				sheepItem.shape=SHEEP;
				break;
			case ITEM_TYPE_COW:
				sheepItem.shape=COW;
				break;
			case ITEM_TYPE_HAYSTACK:
				sheepItem.shape=HAYSTK;
				break;
			NODEFAULT;
		}

		UWord itemCount = *((UWord*)pDS);
		const COORDS3D* sheepPos = (COORDS3D*)(pDS+2);
		while ( itemCount-- )
		{
			sheepItem.World = *sheepPos;
//DeadCode JON 25Oct00 			sheepItem.World.X+=view.X;
//DeadCode JON 25Oct00 			sheepItem.World.Z+=view.Z;

			Three_Dee.do_object_dummy(&sheepItem,STATIC_OBJECT);
			sheepPos++;
		}
		pDS = (UByte*)sheepPos;
	}

	// now for the trees
	int treeCount = *pDS++;
	while ( treeCount-- )
	{
		// do a tree...
		float xT, yT, zT;
		SHAPE.newco[*pDS].getPosition( // get the position of the tree...
			xT, yT, zT
		);

		sheepItem.World.X=view.X+SLong(F2UL_Round( xT ));
		sheepItem.World.Y=SLong(F2UL_Round( yT ));
		sheepItem.World.Z=view.Z+SLong(F2UL_Round( zT ));
		sheepItem.shape=ShapeNum(TREE1+((inptDefs[*pDS].alt+ inptDefs[*pDS].z )&1));

		Three_Dee.do_object_dummy(&sheepItem,STATIC_OBJECT);
		*pDS++;
	}

	sheepItem.Anim = ANIM_NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTrees
//Author		Paul
//Date			Fri 14 Aug 1998
//------------------------------------------------------------------------------
//deadcode JON 19/06/01	void LandScape::RenderTrees(UByte* pds,COORDS3D& view)
//deadcode JON 19/06/01	{
/*	if (!((!Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS]) ||
		View_Ground_Height>6*FT_250))
	{
	Float dx,dz;
	dx=Float(view.X-viewer_x);
	dz=Float(view.Z-viewer_z);

	Float dd=dx*dx+dz*dz;

	_asm {fld dd;
	fsqrt;
	fstp dd;
	}

	if (SLong(dd)>24*FT_250) return;

	ShapeNum treeShapes[]={TREE1,TREE2};//DeadCode RJS 15Dec99 ,TREE3,TREE4};

	AltPointsHdr& aph=*(AltPointsHdr*)pds;

	pds+=sizeof(AltPointsHdr)+aph.vertexCount*sizeof(PointDef);

	DrawDataHdr& ddh=*(DrawDataHdr*)pds;

	pds+=sizeof(DrawDataHdr);

	if (ddh.noOfTrees==0) return;

	SLong treeCount=ddh.noOfTrees;

	item dummyItem;

	dummyItem.Anim=CloudAnimP;

	SmallPoint* psp=(SmallPoint*)(ULong(&aph)+ULong(ddh.treeOffset));

	SLong treeRnd=perm(ddh.treeOffset>>3);

	while (treeCount--)
	{
		dummyItem.shape=treeShapes[treeRnd&3];
		dummyItem.World.X=(psp->x<<9)+view.X;
		dummyItem.World.Y=(psp->alt*_altitudeScale);
		dummyItem.World.Z=((256-psp->z)<<9)+view.Z;
		//only add trees to empty sectors. Doesn't take sector
		//wrapping into account
		Three_Dee.do_object_dummy(&dummyItem,STATIC_OBJECT);//RJS 04Feb00
		psp++;
		treeRnd=perm(treeRnd);
	}
	dummyItem.Anim=ANIM_NULL;
	}
	g_lpLib3d->SetAmbientLighting(currentLighting.landAmbientCollo.col(),
								currentLighting.landAmbientColhi.col(),
								currentLighting.landAmbientColamb.col(),1.2f);
	View_Point->isLightShaded=TRUE;

	LIGHTFLAG lf=LF_LIGHTING;
	g_lpLib3d->SetObjectLighting(lf);
	*/
//deadcode JON 19/06/01	}


//DeadCode JON 24Oct00 inline bool IsGrassy(UByte at)
//DeadCode JON 24Oct00 {
//DeadCode JON 24Oct00 	at&=0x1f;
//DeadCode JON 24Oct00 	switch (at)
//DeadCode JON 24Oct00 	{
//DeadCode JON 24Oct00 	case AT_darkGrass:case AT_midGrass: case AT_lightGrass:case AT_garden:
//DeadCode JON 24Oct00 		return true;
//DeadCode JON 24Oct00 	}
//DeadCode JON 24Oct00 	return false;
//DeadCode JON 24Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HiRezTile
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------

//DeadCode JON 20Oct00 #pragma warnmsg ( "what does this do???" )
//DeadCode JON 20Oct00 static UByte atRecs[256];
//DeadCode JON 20Oct00 
//DeadCode JON 20Oct00 void LandScape::MakeATRecs(UByte *pDataStream)
//DeadCode JON 20Oct00 {
//DeadCode JON 20Oct00 	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
//DeadCode JON 20Oct00 	int	vertexCount=aph.vertexCount;
//DeadCode JON 20Oct00 	pDataStream+=sizeof(AltPointsHdr);
//DeadCode JON 20Oct00 	pDataStream+=vertexCount*sizeof(PointDef);
//DeadCode JON 20Oct00 	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
//DeadCode JON 20Oct00 	pDataStream+=sizeof(ddh);
//DeadCode JON 20Oct00 	int	polyCount=ddh.noOfPolys;
//DeadCode JON 20Oct00 //DeadCode JON 20Oct00 	int lineCount=ddh.noOfLines; 
//DeadCode JON 20Oct00 //DeadCode JON 20Oct00 	int totalTriCount=ddh.totalTris;
//DeadCode JON 20Oct00 	memset(atRecs,0,vertexCount);
//DeadCode JON 20Oct00 	ULong edgePointMax=aph.topEdgePoints+aph.rightEdgePoints+aph.bottomEdgePoints+aph.leftEdgePoints+4;
//DeadCode JON 20Oct00 	// start from beggining of poly data.
//DeadCode JON 20Oct00 	while (polyCount--)
//DeadCode JON 20Oct00 	{
//DeadCode JON 20Oct00 		UByte thisAt=*pDataStream++;
//DeadCode JON 20Oct00 		ULong fanCount=*pDataStream++;
//DeadCode JON 20Oct00 		UByte thisFlag;
//DeadCode JON 20Oct00 
//DeadCode JON 20Oct00 		if (IsGrassy(thisAt))		thisFlag=0x01;
//DeadCode JON 20Oct00 //temp		else if (IsBeach(thisAt))	thisFlag=0x02;
//DeadCode JON 20Oct00 //temp		else if (IsWater(thisAt))	thisFlag=0x04;
//DeadCode JON 20Oct00 		else						thisFlag=0x00;
//DeadCode JON 20Oct00 
//DeadCode JON 20Oct00 		if (thisFlag)
//DeadCode JON 20Oct00 		{
//DeadCode JON 20Oct00 			while (fanCount--)
//DeadCode JON 20Oct00 			{
//DeadCode JON 20Oct00 				ULong triCount=(*pDataStream++)+2;
//DeadCode JON 20Oct00 				while (triCount--) 
//DeadCode JON 20Oct00 				{
//DeadCode JON 20Oct00 					ULong thisIndex=*pDataStream++;
//DeadCode JON 20Oct00 					if (thisIndex>=edgePointMax)
//DeadCode JON 20Oct00 						atRecs[thisIndex]|=thisFlag;
//DeadCode JON 20Oct00 				}
//DeadCode JON 20Oct00 			}
//DeadCode JON 20Oct00 		}
//DeadCode JON 20Oct00 		else while (fanCount--) pDataStream+=ULong(*pDataStream++)+2;
//DeadCode JON 20Oct00 	}
//DeadCode JON 20Oct00 }

// Simple bounds checking array in debug - should compile to standary array in release.
class UByteA	//JON 22Sep00
{
//	UByte* data;
	UByte* data;
#ifndef NDEBUG
	int size;
#endif
	public:
//	UByteA() {INT3;}
	UByteA( const int newSize ) // constructor
	{
#ifndef NDEBUG
		if ( newSize < 0 )
			INT3; // silly sized array, -ve.
		size = newSize;
#endif
		data = new UByte[ newSize ];
	}
	UByteA( const int newSize, const UByte startVal ) // constructor with starting values
	{
#ifndef NDEBUG
		if ( newSize < 0 )
			INT3; // silly sized array, -ve.
		size = newSize;
#endif
		data = new UByte[ newSize ];
		UByte* tmp = data;
		for ( int i = 0; i<newSize; i++ )
			*tmp++ = startVal;
	}

	~UByteA()
	{
		delete[]data;
	}

	UByte& operator[] (const int index) const
	{
#ifndef NDEBUG
		if ( index < 0 )
			INT3; // don't try to access -ve array values.
		if ( index >= size )
			INT3; // oops looking too far through the array.
#endif
		return data[index];
	}

	operator UByte*() const // warning, no bounds checking on this now...
	{
		return data;
	}
};

class AltPointIndexer
{
private:
	enum { 
		NUM_POSS_OFFSETS = 14,
		MAX_TILE_POINTS = 256,
		CLIFF_OFFSET = 0, // just a note really! == sea offset
		NUMBER_OF_NONE_SPLIT = 1,	// number of offsets before the split town ones
		SIDE_TEXTURE_HEIGHT = 128,
		NULL_OUTLEVEL=255
	};
//DeadCode JON 22Sep00 	UByte outLevel[NUM_POSS_OFFSETS*MAX_TILE_POINTS];
//DeadCode JON 22Sep00 	UByte alreadyUsed[MAX_TILE_POINTS]; // the number of slots already used...
	UByteA outLevel;//(NUM_POSS_OFFSETS*MAX_TILE_POINTS);
	UByteA alreadyUsed;
public:
	AltPointIndexer( void ) // constructor - make null;
	:	outLevel(NUM_POSS_OFFSETS*MAX_TILE_POINTS, NULL_OUTLEVEL)
	,	alreadyUsed(MAX_TILE_POINTS, 0 )
	{
//		memset( outLevel, NULL_OUTLEVEL, NUM_POSS_OFFSETS*MAX_TILE_POINTS ); 	
//		memset( alreadyUsed, 0, MAX_TILE_POINTS ); 	
	}
	int getPointIndex( const int origPoint, const UByte ptOffset, const float raiseHeight ) // MAKES THE POINT POSITION TOO
	{
//TempCode JON 20Sep00 #pragma	warnmsg ( "remove me" )
//TempCode JON 20Sep00 		if ( origPoint == 60 )
//TempCode JON 20Sep00 			NOP;
		int pos = origPoint + ( MAX_TILE_POINTS * ptOffset );
		if ( outLevel[ pos ] != NULL_OUTLEVEL )
		{
			return origPoint+( outLevel[pos] * MAX_TILE_POINTS );
		} else
		{
#ifndef NDEBUG		//point 0 can be defined at ground level and then shunted to 4 heights 
				//point 0 can be overwritten by the 4th hiking.
//			assert( alreadyUsed[ origPoint ] < 5 && "too many moved points" );	//JIM 27Jun00
#endif
			outLevel[ pos ] = ++alreadyUsed[ origPoint ];

			// not sure about this
			outLevel[pos]&=3;

			int newPos = origPoint+( outLevel[pos] * MAX_TILE_POINTS );
			SHAPE.newco[ newPos ] = SHAPE.newco[ origPoint ];	// copy over point...
			SHAPE.newco[ newPos ].incPosY( raiseHeight );		// raise it up
			// now make the texture coords 4 the thing..
			if (ptOffset <=NUMBER_OF_NONE_SPLIT)
			{
				SHAPE.newco[ newPos ].setIMapCoords( 0, 0 );
			} else
			{
				int t = ptOffset;
				t-=(NUMBER_OF_NONE_SPLIT+1);
				t&=3; // mod 4...
				t++;
				t*=SIDE_TEXTURE_HEIGHT;
				t>>=2; // divide by 4
				SHAPE.newco[ newPos ].setIMapCoords( 0, SIDE_TEXTURE_HEIGHT-t );
			}
			return newPos;
		}
	}

	int getPosCliffBaseIndex( const int origPoint, const bool* isPointCliff ) // note cliff pass MUST come first
	{
		if ( !isPointCliff[origPoint] )
		{
			return origPoint;
		} else
		{ // right it is a cliff point
			if ( outLevel[ origPoint ] == 1 ) // this is why cliff/sea pass must come first!
			{	// we've already made this
				return origPoint+( MAX_TILE_POINTS );
			} else
			{
				outLevel[ origPoint ] = ++alreadyUsed[ origPoint ];
				int newPos = origPoint + MAX_TILE_POINTS;
				SHAPE.newco[ newPos ] = SHAPE.newco[ origPoint ];	// copy over point...
				SHAPE.newco[ newPos ].setPosY( 0.f );		// dropItDown
				return newPos;
			}
		}
	}

	
	int getSeaIndex( const int origPoint, SWord ddx )
	{
		if ( outLevel[ origPoint ] == 1 ) // this is why cliff/sea pass must come first!
		{	// we've already made this
			return origPoint+( MAX_TILE_POINTS );
		} else
		{
			outLevel[ origPoint ] = ++alreadyUsed[ origPoint ];
			int newPos = origPoint + MAX_TILE_POINTS;
			SHAPE.newco[ newPos ] = SHAPE.newco[ origPoint ];	// copy over point...
			SHAPE.newco[ newPos ].setIMapCoords1(
					(SHAPE.newco[ newPos ].getIMapX()<<3)+ddx,
					(SHAPE.newco[ newPos ].getIMapY()<<3)
				);
			return newPos;
		}

	}

	int getPosSeaCliffBaseIndex( const int origPoint, const bool* isPointCliff, SWord ddx ) // note cliff pass MUST come first
	{
		if ( outLevel[ origPoint ] == 1 ) // this is why cliff pass must come first!
		{	// we've already made this
			return origPoint+( MAX_TILE_POINTS );
		} else
		{
			outLevel[ origPoint ] = ++alreadyUsed[ origPoint ];
			int newPos = origPoint + MAX_TILE_POINTS;
			SHAPE.newco[ newPos ] = SHAPE.newco[ origPoint ];	// copy over point...
			SHAPE.newco[ newPos ].setIMapCoords1(
					(SHAPE.newco[ newPos ].getIMapX()<<3)+ddx,
					(SHAPE.newco[ newPos ].getIMapY()<<3)
				);


			if ( isPointCliff[origPoint] )
			{ // right it is a cliff point
				SHAPE.newco[ newPos ].setPosY( 0.f );		// dropItDown
			}
			return newPos;
		}
	}

	int getCliffBaseIndexNoMake( const int origPoint ) const
	{
		return origPoint+MAX_TILE_POINTS;
	}

	int getPointIndexNoMake( const int origPoint, const UByte ptOffset ) const 
	{
		int pos = origPoint + ( MAX_TILE_POINTS * ptOffset );
//		UByte* tmp = outLevel;
//		if ( outLevel[pos] != 1 )
//			NOP;
		return origPoint+( outLevel[pos] * MAX_TILE_POINTS );
	}
	
};

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawCliffFace
//Author		Jon.   
//Date			Fri 24 Mar 1998
//------------------------------------------------------------------------------
inline void LandScape::DrawCliffFace( const int& startPoint, const int& endPoint, const AltPointIndexer& pointOffsets )
{
//DeadCode JON 28Sep00 	g_lpLib3d->IncGlobal( TOGGLE_TEXTURE_ZBIAS );

	DoPointStruc *pPoints = SHAPE.newco;
	Lib3DPoint *pRVerts;
	HMATERIAL CliffImg = HMATERIAL(Image_Map.GetImageMapPtr(CLIFFNO));
												// calc the tiling coords
	float dx = pPoints[startPoint].getPosX() - pPoints[endPoint].getPosX();
	float dz = pPoints[startPoint].getPosZ() - pPoints[endPoint].getPosZ();
	short dist = short ( fastMath.FastSqrt( (dx*dx) + (dz*dz) ) * (1.0/80.0) );
	dist-=dist%CLIFFTWIDTH; 
	dist+=CLIFFTWIDTH;

	pRVerts = g_lpLib3d->BeginPoly(CliffImg,4);

	*pRVerts=pPoints[startPoint];						// top left point
	pRVerts->setIMapCoords( 0, 0 );

	*(++pRVerts)=pPoints[endPoint];						// top right point
	pRVerts->setIMapCoords( dist, 0 );

//DEADCODE JON 5/31/00 	*(++pRVerts)=pPoints[endPoint];						// bottom right point
//DEADCODE JON 5/31/00 	pRVerts->setPosY( 0.f );							// make sea level
	*(++pRVerts)=pPoints[ pointOffsets.getCliffBaseIndexNoMake( endPoint ) ];
	pRVerts->setIMapCoords( dist, CLIFFTHEIGHT );


//DEADCODE JON 5/31/00 	*(++pRVerts)=pPoints[startPoint];					// bottom left point
//DEADCODE JON 5/31/00 	pRVerts->setPosY( 0.f );							// make sea level
	*(++pRVerts)=pPoints[ pointOffsets.getCliffBaseIndexNoMake( startPoint ) ];
	pRVerts->setIMapCoords( 0, CLIFFTHEIGHT );
	
	g_lpLib3d->EndPoly();
//DeadCode JON 28Sep00 	g_lpLib3d->DecGlobal( TOGGLE_TEXTURE_ZBIAS );

}

void LandScape::LoRezTile(UByte* &pDS,ULong& dataLen,COORDS3D& view,const HTEXT& hTexture)
{
#ifdef _NOHIREZ
	return;
#endif
	Lib3DPoint *pRVerts;
	UWord thisMaterial;
	thisMaterial = hTexture.textureHandle;

	UWord flag;

	UByte* pDataStream=pDS;

	//Now render this texture over the whole tile...
//DeadCode JON 20Oct00 	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
//DeadCode JON 20Oct00 	int	vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pPointDefs=(PointDef*)pDataStream;
//DeadCode JON 20Oct00 	COORDS3D* pCoordData=tileCoords;
	DoPointStruc* pPoints =SHAPE.newco;
	
//DeadCode JON 20Oct00 	UWord clipTest=0;
	{
		for (int t=0;t<4;t++)
		{
			//3d coordinate buffer will do for storing
			//this load of vertex information
			PointDef& apd=*pPointDefs++;
			DoPointStruc& dp=*pPoints++;

			dp.setPosition(
							((apd.x<<9)+view.X),
							(apd.alt*_altitudeScale),
							(((256-apd.z)<<9)+view.Z)
							);
			dp.setNormal( Three_Dee.normalDataPtr[apd.shadeVal] );
			dp.setIMapCoords( apd.x, apd.z );
		}

		pPoints = SHAPE.newco;

		g_lpLib3d->SetMaterial(thisMaterial);
		pRVerts=g_lpLib3d->BeginFan( 4 );
		pRVerts[0] = pPoints[0];
		pRVerts[1] = pPoints[1];
		pRVerts[2] = pPoints[2];
		pRVerts[3] = pPoints[3];
		g_lpLib3d->EndFan();

		return;
	}

} 

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		HiRezTile
//Author		Paul.   
//Date			Tue 10 Nov 1998
//------------------------------------------------------------------------------
const Float sRaise = 5; // the smallest raise to be drawn in cm...
void LandScape::HiRezTile(
						  const UByte* pDS,
						  const ULong dataLen,
						  const COORDS3D& view,
						  const TileElement& gridElement,
						  const ImageMapDescPtr seaptr,
						  SWord seaAnimOffset
						  )
{
#ifdef _NOHIREZ
	return;
#endif
	const bool doSheep = ( gridElement.viewRadius < 2 && gridElement.meshRes < TILE_REZ_LIMIT_ITEM );

	// quick inlining code...
	ULong flag = (ULong( doSheep)<<3) | (ULong(Save_Data.filtering==3)<<2) | (ULong (Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS])<<1) | (ULong (Save_Data.textureQuality==4) );
	switch ( flag )
	{
	case 0:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			false, false, false,
			seaptr,seaAnimOffset, false );
		break;
	case 1:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			false, false, true,
			seaptr,seaAnimOffset, false );
		break;
	case 2:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			false, true, false,
			seaptr,seaAnimOffset, false );
		break;
	case 3:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			false, true, true,
			seaptr,seaAnimOffset, false );
		break;
	case 4:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			true, false, false,
			seaptr,seaAnimOffset, false );
		break;
	case 5:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			true, false, true,
			seaptr,seaAnimOffset, false );
		break;
	case 6:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			true, true, false,
			seaptr,seaAnimOffset, false );
		break;
	case 7:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			true, true, true,
			seaptr,seaAnimOffset, false );
		break;
	case 8:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			false, false, false,
			seaptr,seaAnimOffset, true );
		break;
	case 9:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			false, false, true,
			seaptr,seaAnimOffset, true );
		break;
	case 10:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			false, true, false,
			seaptr,seaAnimOffset, true );
		break;
	case 11:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			false, true, true,
			seaptr,seaAnimOffset, true );
		break;
	case 12:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			true, false, false,
			seaptr,seaAnimOffset, true );
		break;
	case 13:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			true, false, true,
			seaptr,seaAnimOffset, true );
		break;
	case 14:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			true, true, false,
			seaptr,seaAnimOffset, true );
		break;
	case 15:
		_HiRezTile( pDS, dataLen, view, gridElement.textHandle, 
			true, true, true,
			seaptr,seaAnimOffset, true );
		break;
		NODEFAULT;
	}

//DeadCode JON 8Aug00 	_HiRezTile( pDS, dataLen, view, hTexture, Save_Data.filtering==3, (Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS]), Save_Data.textureQuality==4,seaptr,seaAnimOffset );
}

inline void LandScape::_HiRezTile(
								  const UByte* pDS,
								  const ULong dataLen,
								  const COORDS3D& view,
								  const HTEXT& hTexture,
								  const bool doDither,
								  const bool doRaises,
								  const bool doHirez,
								  const ImageMapDescPtr seaptr,
								  const SWord seaAnimOffset,
								  const bool doItems)
{
#ifdef _NO_TEXTURE_RENDER
	g_lpLib3d->SetMaterial( 12, Three_Dee.pTMake->GetImageFromArea(9) );
#endif
	LIGHTFLAG lf = LF_AMBIENT;

	Lib3DPoint *pRVerts;
	UWord thisMaterial;
	thisMaterial = hTexture.textureHandle;
//DeadCode JON 8Aug00 //	FileNum	seaFile = FileNum(seaBase + (ULong(totTime/25)&0x03) );
//DeadCode JON 8Aug00 
//DeadCode JON 8Aug00 	FileNum seaFile = FileNum(seaBase);
//DeadCode JON 8Aug00 	LandMapNum seamap=LandMapNum(seaFile);
//DeadCode JON 8Aug00 	ImageMapDescPtr	seaptr = seamap.GetLandMapPtr();
//DeadCode JON 8Aug00 
//DeadCode JON 8Aug00 	static bool spthjfkkkkkf= true;
//DeadCode JON 8Aug00 	if ( spthjfkkkkkf )
//DeadCode JON 8Aug00 	{
//DeadCode JON 8Aug00 		spthjfkkkkkf = false;
//DeadCode JON 8Aug00 
//DeadCode JON 8Aug00 		g_lpLib3d->UploadAsDitherTexture( seaptr );
//DeadCode JON 8Aug00 	
//DeadCode JON 8Aug00 		seaFile = FileNum(seaBase+1);
//DeadCode JON 8Aug00 		seamap=LandMapNum(seaFile);
//DeadCode JON 8Aug00 		ImageMapDescPtr seamipptr = seamap.GetLandMapPtr();
//DeadCode JON 8Aug00 		g_lpLib3d->UploadAsMipMapLevel( seaptr, seamipptr, 1 );
//DeadCode JON 8Aug00 
//DeadCode JON 8Aug00 		seaFile = FileNum(seaBase+2);
//DeadCode JON 8Aug00 		seamap=LandMapNum(seaFile);
//DeadCode JON 8Aug00 		seamipptr = seamap.GetLandMapPtr();
//DeadCode JON 8Aug00 		g_lpLib3d->UploadAsMipMapLevel( seaptr, seamipptr, 2 );
//DeadCode JON 8Aug00 
//DeadCode JON 8Aug00 		seaFile = FileNum(seaBase+3);
//DeadCode JON 8Aug00 		seamap=LandMapNum(seaFile);
//DeadCode JON 8Aug00 		seamipptr = seamap.GetLandMapPtr();
//DeadCode JON 8Aug00 		g_lpLib3d->UploadAsMipMapLevel( seaptr, seamipptr, 3 );
//DeadCode JON 8Aug00 
//DeadCode JON 8Aug00 	}
//DeadCode JON 8Aug00 


//DeadCode JON 15Aug00 	ImageMapDescPtr dithImg;
//DeadCode JON 15Aug00 	if ( doDither )
//DeadCode JON 15Aug00 	{
//DeadCode JON 15Aug00 		FileNum	dithFile = FileNum( FIL_DITHER1_NUM);
//DeadCode JON 15Aug00 		LandMapNum dithMap=LandMapNum(dithFile);
//DeadCode JON 15Aug00 		dithImg = dithMap.GetLandMapPtr();
//DeadCode JON 15Aug00 //DeadCode JON 10Aug00 		dithImg = Image_Map.GetImageMapPtr(DITHER1NO);
//DeadCode JON 15Aug00 //DeadCode JON 10Aug00 		g_lpLib3d->UploadAsDitherTexture( dithImg );
//DeadCode JON 15Aug00 	}

	const UByte* pDataStream=pDS;

	//Now render this texture over the whole tile...
	AltPointsHdr& aph=*(AltPointsHdr*)pDataStream;
	int	vertexCount=aph.vertexCount;
	pDataStream+=sizeof(AltPointsHdr);
	PointDef* pPointDefs=(PointDef*)pDataStream;
//DeadCode JON 20Oct00 	COORDS3D* pCoordData=tileCoords;
	DoPointStruc* pPoints =SHAPE.newco;
	
//DeadCode JON 20Oct00 	UWord clipTest=0;

	PointDef* inptDefs = pPointDefs;

//TempCode JON 20Sep00 #pragma warnmsg ( "remove me" )
//TempCode JON 20Sep00 	if (aph.checksum==0x7788BC73 )
//TempCode JON 20Sep00 		NOP;
#ifndef _TILE_POSITIONS_IN_MATRIX
	for (int t=0;t<vertexCount;t++)
	{
		//3d coordinate buffer will do for storing
		//this load of vertex information
		PointDef& apd=*pPointDefs++;
		DoPointStruc& dp=*pPoints++;

		dp.setPosition(
						((apd.x<<9)+view.X),
						(apd.alt*_altitudeScale),
						(((256-apd.z)<<9)+view.Z)
						);
		dp.setNormal( Three_Dee.normalDataPtr[apd.shadeVal] );
		dp.setIMapCoords( apd.x, apd.z );
		if ( doDither )
		{
			dp.setIMapCoords1( apd.x<<5, apd.z<<5 ); // for the extra dithering 
		}
	}
#else
	g_lpLib3d->PushMatrix( MATRIX_OBJECT );
	g_lpLib3d->LoadIdentity( MATRIX_OBJECT );

	D3DVECTOR viewMods;
	viewMods.x=D3DVALUE(view.X-viewer_x);
	viewMods.y=D3DVALUE(-viewer_y);
	viewMods.z=D3DVALUE(view.Z-viewer_z);
	g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );

	for (int t=0;t<vertexCount;t++)
	{
		//3d coordinate buffer will do for storing
		//this load of vertex information
		PointDef& apd=*pPointDefs++;
		DoPointStruc& dp=*pPoints++;

		dp.setPosition(
						((apd.x<<9)),
						(apd.alt*_altitudeScale),
						(((256-apd.z)<<9))
						);
		dp.setNormal( Three_Dee.normalDataPtr[apd.shadeVal] );
		dp.setIMapCoords( apd.x, apd.z );
		if ( doDither )
		{
			dp.setIMapCoords1( apd.x<<5, apd.z<<5 ); // for the extra dithering 
		}
	}
#endif
	pPoints = SHAPE.newco;

//TempCode JON 19Sep00 	g_lpLib3d->SetMaterial(thisMaterial);
//TempCode JON 19Sep00 	pRVerts=g_lpLib3d->BeginFan( 4 );
//TempCode JON 19Sep00 	pRVerts[0] = pPoints[0];
//TempCode JON 19Sep00 	pRVerts[1] = pPoints[1];
//TempCode JON 19Sep00 	pRVerts[2] = pPoints[2];
//TempCode JON 19Sep00 	pRVerts[3] = pPoints[3];
//TempCode JON 19Sep00 	g_lpLib3d->EndFan();
//TempCode JON 19Sep00 	
//TempCode JON 19Sep00 	return;

	pDataStream=(UByte*)pPointDefs;

	DrawDataHdr& ddh=*(DrawDataHdr*)pDataStream;
	pDataStream+=sizeof(ddh);
 
	int	polyCount=ddh.noOfPolys;
	int lineCount=ddh.noOfLines; 

	// build an array of offsets for the things.
	AltPointIndexer pointOffsets; // will build the whole thing.

	const UByte* isPointCliff = pDS+ddh.cliffOffset;
	const UByte* saveDS=pDataStream;

	if ( !doRaises || raiseFlag == NORAISE )
	{
		// *************************   non raised landscape
//DeadCode JON 15Aug00 		if ( doDither )
//DeadCode JON 15Aug00 			g_lpLib3d->SetMaterial(thisMaterial, dithImg );
//DeadCode JON 15Aug00 		else
//DeadCode JON 15Aug00 			g_lpLib3d->SetMaterial(thisMaterial);
		if ( !doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
			g_lpLib3d->SetMaterial(thisMaterial);
#else
			g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)) ) );
#endif

		// PASS1 the lowres stuff
		if ( *isPointCliff++ ) // there is cliff data
		{
			while (polyCount--)									// loop through all poly's
			{
				UByte at=*pDataStream++;
				int fanCount=*pDataStream++;

				if ( IsCliffBottom( at ) )
				{  // arrgh there is a possiblilty of a cliff bottom...
					if ((at&AT_MASK)!=AT_sea)
					{						// normal draw method
						if ( doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
							g_lpLib3d->SetMaterial(thisMaterial, GetDitherTexture( at ) );
#else
							g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), GetDitherTexture( at ) ) );
#endif

						while(fanCount--)
						{
							int triCount=(*pDataStream++)+2;
							pRVerts = g_lpLib3d->BeginFan(triCount);
							while (triCount--)
							{
								*pRVerts++=pPoints[ pointOffsets.getPosCliffBaseIndex(*pDataStream++, (bool*)isPointCliff)]; // a point per triangle
							}
							g_lpLib3d->EndFan();		
						} // end of loop thru fans
					} else
					{											// draw sea wiv animation
#ifndef _RENDER_SIMPLE_TEXTURE
						g_lpLib3d->SetMaterial(thisMaterial, seaptr );
#else
						g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), seaptr ) );
#endif

						while(fanCount--)						// loop all fans
						{
							int triCount=(*pDataStream++)+2;
							pRVerts = g_lpLib3d->BeginFan(triCount);
							while (triCount--)
							{
								*pRVerts++=pPoints[ pointOffsets.getPosSeaCliffBaseIndex(*pDataStream++, (bool*)isPointCliff, seaAnimOffset ) ]; // a point per triangle
							}
							g_lpLib3d->EndFan();		
						}						// end of loop fans		
//DeadCode JON 15Aug00 						if ( doDither )
//DeadCode JON 15Aug00 							g_lpLib3d->SetMaterial(thisMaterial, dithImg );
//DeadCode JON 15Aug00 						else
//DeadCode JON 15Aug00 							g_lpLib3d->SetMaterial(thisMaterial);
						if ( !doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
							g_lpLib3d->SetMaterial(thisMaterial );
#else
							g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)) ) );
#endif
					}
				} else											// ahah it's not a cliff bottom
				{
					if ( !doHirez || !IsHirez( at ) )
					{
						if ( doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
							g_lpLib3d->SetMaterial(thisMaterial, GetDitherTexture( at ) );
#else
							g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), GetDitherTexture( at ) ) );
#endif

						// normal draw method
						while(fanCount--)
						{
							int triCount=(*pDataStream++);
							pRVerts = g_lpLib3d->BeginFan(triCount+2);
							*pRVerts++=pPoints[*pDataStream++]; // mutual vertex
							*pRVerts++=pPoints[*pDataStream++]; // first vertex

							while (triCount--)
							{
								*pRVerts++=pPoints[*pDataStream++]; // a point per triangle
							}
							g_lpLib3d->EndFan();
						} // end of loop thru fans
					} else
					{
						while(fanCount--) // skip the area - hirez done in own pass
						{
							int triCount=(*pDataStream++)+2;
							pDataStream+=triCount;
						}		
					}
				}
			}
		} else
		{	// no cliffs
			//draw in the ground 
			while (polyCount--)									// loop through all poly's
			{
				UByte at=*pDataStream++;
				int fanCount=*pDataStream++;

				if ( !doHirez || !IsHirez( at ) )
				{											// not a hirez area
					if ((at&AT_MASK)!=AT_sea)
					{
															// normal draw method
						if ( doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
							g_lpLib3d->SetMaterial(thisMaterial, GetDitherTexture( at ) );
#else
							g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), GetDitherTexture( at ) ) );
#endif

						while(fanCount--)
						{
							int triCount=(*pDataStream++);
							pRVerts = g_lpLib3d->BeginFan(triCount+2);
							*pRVerts++=pPoints[*pDataStream++]; // mutual vertex
							*pRVerts++=pPoints[*pDataStream++]; // first vertex

							while (triCount--)
							{
								*pRVerts++=pPoints[*pDataStream++]; // a point per triangle
							}
							g_lpLib3d->EndFan();


						} // end of loop thru fans
					} else
					{											// draw sea wiv animation
#ifndef _RENDER_SIMPLE_TEXTURE
						g_lpLib3d->SetMaterial(thisMaterial, seaptr );
#else
						g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), seaptr ) );
#endif

						while(fanCount--)						// loop all fans
						{
							int triCount=(*pDataStream++)+2;
							pRVerts = g_lpLib3d->BeginFan(triCount);
							while (triCount--)
							{
								*pRVerts++=pPoints[ pointOffsets.getSeaIndex(*pDataStream++, seaAnimOffset ) ]; // a point per triangle
							}
							g_lpLib3d->EndFan();		

						}						// end of loop fans
//DeadCode JON 15Aug00 						if ( doDither )
//DeadCode JON 15Aug00 							g_lpLib3d->SetMaterial(thisMaterial, dithImg );
//DeadCode JON 15Aug00 						else
//DeadCode JON 15Aug00 							g_lpLib3d->SetMaterial(thisMaterial);
						if ( !doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
							g_lpLib3d->SetMaterial(thisMaterial);
#else
							g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)) ) );
#endif
					}
				} else 
				{												// a hirez area
					while(fanCount--) // skip the area
					{
						int triCount=(*pDataStream++)+2;
						pDataStream+=triCount;
					}
				}											// end of hirez or not 
			}													// end of loop all poly's
		} // end of is there cliffs to worry about...

		// PASS 2 - draw in the hirez areas...
		if ( doHirez )
		{
			polyCount=ddh.noOfPolys;
			pDataStream=saveDS; // start from beggining of poly data.
			while (polyCount--)									// loop through all poly's
			{
				UByte at=*pDataStream++;
				int fanCount=*pDataStream++;

				if ( !IsHirez( at ) )
				{											// not a hirez area
					while(fanCount--) // skip the area
					{
						int triCount=(*pDataStream++)+2;
						pDataStream+=triCount;
					}		
				} else 
				{											// a hirez area
					HMATERIAL sM(Three_Dee.pTMake->GetImageFromArea(at));
//TempCode JON 5Oct00 					HMATERIAL sM(127); //RED
					sM.isMasked = MSK_NONE;
					while(fanCount--) // skip the area
					{

						int triCount=(*pDataStream++)+2;
						pRVerts = g_lpLib3d->BeginFan( sM, triCount);

						while (triCount--)
						{
							*pRVerts=pPoints[ *pDataStream ];
							pRVerts->setIMapCoords(
								SWord(inptDefs[ *pDataStream ].x)<<1,
								SWord(inptDefs[ *pDataStream ].z)<<1
								);
							pRVerts++;
							*pDataStream++;
						}
						g_lpLib3d->EndFan();
					} // end of loop thru fans
				}											// end of hirez or not 
			}												// end of loop all poly's
		}

	} else  // ******************************************* DO THE RAISES
	{

		if ( doItems )
			RenderSheep( (pDS+ddh.sheepOffset), ddh.noOfSheep, view, inptDefs ); // only do if raisd landscape...

//DeadCode JON 28Sep00 		g_lpLib3d->IncGlobal( TOGGLE_TEXTURE_ZBIAS );

// PASS 1 - draw all of the ground level, lowres stuff.
//DeadCode JON 15Aug00 		if ( doDither )
//DeadCode JON 15Aug00 			g_lpLib3d->SetMaterial(thisMaterial, dithImg );
//DeadCode JON 15Aug00 		else
//DeadCode JON 15Aug00 			g_lpLib3d->SetMaterial(thisMaterial);
		if ( !doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
			g_lpLib3d->SetMaterial(thisMaterial);
#else
			g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)) ) );
#endif

		if ( *isPointCliff++ ) // there is cliff data
		{
			//draw in the ground - pay attention 2 raised area types & cliffs
			while (polyCount--)									// loop through all poly's
			{
				UByte at=*pDataStream++;
				int fanCount=*pDataStream++;

				Float raiseHeight = Float(GetRaiseHeight(at));
				if ( raiseHeight <= sRaise ) 
				{												// this area doesn't need raising.
					if ( IsCliffBottom( at ) )
					{  // arrgh there is a possiblilty of a cliff bottom...
						if ((at&AT_MASK)!=AT_sea)
						{
																// normal draw method
							if ( doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
								g_lpLib3d->SetMaterial(thisMaterial, GetDitherTexture( at ));
#else
								g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), GetDitherTexture( at ) ) );
#endif

							while(fanCount--)
							{
								int triCount=(*pDataStream++)+2;
								pRVerts = g_lpLib3d->BeginFan(triCount);
								while (triCount--)
								{
									*pRVerts++=pPoints[ pointOffsets.getPosCliffBaseIndex(*pDataStream++, (bool*)isPointCliff)]; // a point per triangle
								}
								g_lpLib3d->EndFan();		
							} // end of loop thru fans
						} else
						{											// draw sea wiv animation
#ifndef _RENDER_SIMPLE_TEXTURE
							g_lpLib3d->SetMaterial(thisMaterial, seaptr);
#else
							g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), seaptr ) );
#endif
							
							while(fanCount--)						// loop all fans
							{
								int triCount=(*pDataStream++)+2;
								pRVerts = g_lpLib3d->BeginFan(triCount);
								while (triCount--)
								{
									*pRVerts++=pPoints[ pointOffsets.getPosSeaCliffBaseIndex(*pDataStream++, (bool*)isPointCliff, seaAnimOffset ) ]; // a point per triangle
								}
								g_lpLib3d->EndFan();		
							}						// end of loop fans		
//DeadCode JON 15Aug00 							if ( doDither )
//DeadCode JON 15Aug00 								g_lpLib3d->SetMaterial(thisMaterial, dithImg );
//DeadCode JON 15Aug00 							else
//DeadCode JON 15Aug00 								g_lpLib3d->SetMaterial(thisMaterial);
							if ( !doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
								g_lpLib3d->SetMaterial(thisMaterial);
#else
								g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)) ) );
#endif

						}
					} else											// ahah it's not a cliff bottom
					{
						if ( !doHirez || !IsHirez( at ) )
						{
							if ( doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
								g_lpLib3d->SetMaterial(thisMaterial, GetDitherTexture( at ));
#else
								g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), GetDitherTexture( at ) ) );
#endif

							// normal draw method
							while(fanCount--)
							{
								int triCount=(*pDataStream++);
								pRVerts = g_lpLib3d->BeginFan(triCount+2);
								*pRVerts++=pPoints[*pDataStream++]; // mutual vertex
								*pRVerts++=pPoints[*pDataStream++]; // first vertex

								while (triCount--)
								{
									*pRVerts++=pPoints[*pDataStream++]; // a point per triangle
								}
								g_lpLib3d->EndFan();
							} // end of loop thru fans
						} else
						{
							while(fanCount--) // skip the area - hirez done in own pass
							{
								int triCount=(*pDataStream++)+2;
								pDataStream+=triCount;
							}		
						}
					}
				} else 
				{												// its raised
					while(fanCount--) // skip the area
					{
						int triCount=(*pDataStream++)+2;
						pDataStream+=triCount;
					}		
				}												// end of raised or not
			}													// end of loop all poly's

		}  else
		{			// no cliff data to worry about
			//draw in the ground - pay attention 2 raised area types
			while (polyCount--)									// loop through all poly's
			{
				UByte at=*pDataStream++;
				int fanCount=*pDataStream++;

				Float raiseHeight = Float(GetRaiseHeight(at));
				if ( raiseHeight <= sRaise ) 
				{												// this area doesn't need raising.
					if ( !doHirez || !IsHirez( at ) )
					{											// not a hirez area
						if ((at&AT_MASK)!=AT_sea)
						{
																// normal draw method
							if ( doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
								g_lpLib3d->SetMaterial(thisMaterial, GetDitherTexture( at ));
#else
								g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), GetDitherTexture( at ) ) );
#endif


							while(fanCount--)
							{
								int triCount=(*pDataStream++);
								pRVerts = g_lpLib3d->BeginFan(triCount+2);
								*pRVerts++=pPoints[*pDataStream++]; // mutual vertex
								*pRVerts++=pPoints[*pDataStream++]; // first vertex

								while (triCount--)
								{
									*pRVerts++=pPoints[*pDataStream++]; // a point per triangle
								}
								g_lpLib3d->EndFan();


							} // end of loop thru fans
						} else
						{											// draw sea wiv animation
#ifndef _RENDER_SIMPLE_TEXTURE
							g_lpLib3d->SetMaterial(thisMaterial, seaptr);
#else
							g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), seaptr ) );
#endif
							while(fanCount--)						// loop all fans
							{
								int triCount=(*pDataStream++)+2;
								pRVerts = g_lpLib3d->BeginFan(triCount);
								while (triCount--)
								{
									*pRVerts++=pPoints[ pointOffsets.getSeaIndex(*pDataStream++, seaAnimOffset ) ]; // a point per triangle
								}
								g_lpLib3d->EndFan();		

							}						// end of loop fans
//DeadCode JON 15Aug00 							if ( doDither )
//DeadCode JON 15Aug00 								g_lpLib3d->SetMaterial(thisMaterial, dithImg );
//DeadCode JON 15Aug00 							else
//DeadCode JON 15Aug00 								g_lpLib3d->SetMaterial(thisMaterial);
							if ( !doDither )
#ifndef _RENDER_SIMPLE_TEXTURE
								g_lpLib3d->SetMaterial(thisMaterial);
#else
								g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)) ) );
#endif
						}
					} else 
					{												// a hirez area
						while(fanCount--) // skip the area
						{
							int triCount=(*pDataStream++)+2;
							pDataStream+=triCount;
						}
					}											// end of hirez or not 
				} else 
				{												// its raised
					while(fanCount--) // skip the area
					{
						int triCount=(*pDataStream++)+2;
						pDataStream+=triCount;
					}		
				}												// end of raised or not
			}													// end of loop all poly's
		} // end of is there cliff data or not

		// PASS 2
		// now go through and draw all the edges for raised views.
		g_lpLib3d->SetObjectLighting( lf );
		pDataStream=pDS+ddh.edgeOffset; 
		UByte rows=*pDataStream++;
		while (rows--)
		{
			UByte sideType=*pDataStream++;
#ifndef NDEBUG
					if ( sideType >= NUM_SIDE_TYPES )
						INT3;
#endif
			UByte lineC=*pDataStream++;
			UByte topAt = SideLookUp[sideType].higherAT;
			UByte botAt = SideLookUp[sideType].lowerAT;
			Float topHt = Float(GetRaiseHeight(topAt));
//TempCode JON 22Sep00 #pragma warnmsg ( "remove me" )
//TempCode JON 22Sep00 			if ( topAt == 90 )
//TempCode JON 22Sep00 				NOP;

			if ( topHt > sRaise ) // only draw if the raise is greater
			{	
				float botHt;
				int botOffset;
				int topOffset = GetRaisePtOffset( topAt );
				if ( IsRaised( botAt ) )
				{
					GetRaiseInfo( botAt, botOffset );
					botHt = float( GetRaiseInfo( botAt, botOffset ) );
				}

				HMATERIAL sideIm( Image_Map.GetImageMapPtr( GetSideImage( topAt ) ) );
				sideIm.isMasked = MSK_NONE;
				short lastTileCoord = 0;

				DoPointStruc* bStartPtr;
				DoPointStruc* bEndPtr;
				DoPointStruc* tStartPtr;
				DoPointStruc* tEndPtr;
				
				UByte startP,endP;
				startP=endP=PT_NULL;
				while (lineC--)
				{
					startP=*pDataStream++;
#ifndef NDEBUG
					if ( startP >= vertexCount )
						INT3;
#endif

					endP=*pDataStream++;

					if ( IsRaised( botAt ) )
					{
						bStartPtr	= &pPoints[ pointOffsets.getPointIndex( startP, botOffset, botHt ) ]; 
						bEndPtr		= &pPoints[ pointOffsets.getPointIndex( endP, botOffset, botHt ) ]; 
					} else
					{
						bStartPtr	=	&pPoints[ startP ];
						bStartPtr->setIMapCoords( 0, 128 );
						bEndPtr		=	&pPoints[ endP ];
						bEndPtr->setIMapCoords( 0, 128 );
					}

					tStartPtr	= &pPoints[ pointOffsets.getPointIndex( startP, topOffset, topHt ) ]; 
					tEndPtr		= &pPoints[ pointOffsets.getPointIndex( endP, topOffset, topHt ) ]; 

					//work out texture tiling coords
					float dx = bStartPtr->getPosX() - bEndPtr->getPosX();
					float dz = bStartPtr->getPosZ() - bEndPtr->getPosZ();
					float dist = fastMath.FastSqrt( (dx*dx) + (dz*dz) );

					bEndPtr->setIMapCoords( lastTileCoord, bEndPtr->getIMapY() );
					tEndPtr->setIMapCoords( lastTileCoord, tEndPtr->getIMapY() );

					lastTileCoord +=short( dist*(1.0/40.0) );
					bStartPtr->setIMapCoords( lastTileCoord, bStartPtr->getIMapY() );
					tStartPtr->setIMapCoords( lastTileCoord, tStartPtr->getIMapY() );


					// draw in side of raised platform
					pRVerts = g_lpLib3d->BeginPoly(sideIm,4);
					*pRVerts++ = *tEndPtr;
					*pRVerts++ = *tStartPtr;
					*pRVerts++ = *bStartPtr;
					*pRVerts++ = *bEndPtr;
					g_lpLib3d->EndPoly();
				}
			} else
			{ // skip this poly, it's not raised
				pDataStream+=(lineC<<1);
			}
		} // end of draw the sides of raised platforms

		g_lpLib3d->SetObjectLighting( lf );

		// PASS 3 - draw in the tops of raised areas and hirez areas...
		g_lpLib3d->DecGlobal( TOGGLE_TEXTURE_ZBIAS );
		polyCount=ddh.noOfPolys;
		pDataStream=saveDS; // start from beggining of poly data.
		while (polyCount--)									// loop through all poly's
		{
			UByte at=*pDataStream++;
			int fanCount=*pDataStream++;

			Float raiseHeight = Float(GetRaiseHeight(at));
			if ( raiseHeight <= sRaise ) 
			{												// this area doesn't need raising.
				if ( !doHirez || !IsHirez( at ) )
				{											// not a hirez area
					while(fanCount--) // skip the area
					{
						int triCount=(*pDataStream++)+2;
						pDataStream+=triCount;
					}		
				} else 
				{											// a hirez area
					HMATERIAL sM(Three_Dee.pTMake->GetImageFromArea(at));
//TempCode JON 5Oct00 					HMATERIAL sM(144); //BLUE
					sM.isMasked = MSK_NONE;
					while(fanCount--) // skip the area
					{

						int triCount=(*pDataStream++)+2;
						pRVerts = g_lpLib3d->BeginFan( sM, triCount);

						while (triCount--)
						{
							*pRVerts=pPoints[ *pDataStream ];
							pRVerts->setIMapCoords(
								SWord(inptDefs[ *pDataStream ].x)<<1,
								SWord(inptDefs[ *pDataStream ].z)<<1
								);
							pRVerts++;
							*pDataStream++;
						}
						g_lpLib3d->EndFan();
					} // end of loop thru fans
				}											// end of hirez or not 
			} else
			{											
															// area is raised
				int raiseOffset = GetRaisePtOffset( at ); 
				if ( !doHirez || !IsHirez( at ) )
				{											// not a hirez area
															// normal draw method
//DeadCode JON 15Aug00 					if ( doDither )
//DeadCode JON 15Aug00 						g_lpLib3d->SetMaterial(thisMaterial, dithImg );
//DeadCode JON 15Aug00 					else
//DeadCode JON 15Aug00 						g_lpLib3d->SetMaterial(thisMaterial);
					if ( doDither )
					{
#ifndef _RENDER_SIMPLE_TEXTURE
						g_lpLib3d->SetMaterial(thisMaterial, GetDitherTexture( at ));
#else
						g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)), GetDitherTexture( at ) ) );
#endif
					} else
					{
#ifndef _RENDER_SIMPLE_TEXTURE
						g_lpLib3d->SetMaterial(thisMaterial);
#else
						g_lpLib3d->SetMaterial(HMATERIAL( (Three_Dee.pTMake->GetImageFromArea(12)) ) );
#endif
					}

					while(fanCount--)
					{
						int triCount=(*pDataStream++)+2;
						pRVerts = g_lpLib3d->BeginFan(triCount);

						while (triCount--)
						{
							*pRVerts=pPoints[ pointOffsets.getPointIndex( *pDataStream, raiseOffset, raiseHeight ) ];
							pRVerts->setIMapCoords(
								inptDefs[ *pDataStream ].x,
								inptDefs[ *pDataStream ].z
								);
							if ( doDither )
								pRVerts->setIMapCoords1( pRVerts->getIMapX()<<6, pRVerts->getIMapY()<<6 );
							pRVerts++;
							*pDataStream++;
						}
						g_lpLib3d->EndFan();
					} // end of loop thru fans

				} else 
				{											// a hirez area
					HMATERIAL sM(Three_Dee.pTMake->GetImageFromArea(at));
//TempCode JON 5Oct00 					HMATERIAL sM(104); //YELLOW
					sM.isMasked = MSK_NONE;

					while(fanCount--)
					{
						int triCount=(*pDataStream++)+2;

						pRVerts = g_lpLib3d->BeginFan( sM, triCount);

						while (triCount--)
						{
							*pRVerts=pPoints[ pointOffsets.getPointIndex( *pDataStream, raiseOffset, raiseHeight ) ];
							pRVerts->setIMapCoords(
								SWord(inptDefs[ *pDataStream ].x)<<1,
								SWord(inptDefs[ *pDataStream ].z)<<1
								);
							pRVerts++;
							*pDataStream++;
						}
						g_lpLib3d->EndFan();


					} // end of loop thru fans
//DeadCode JON 15Aug00 					if ( doDither )
//DeadCode JON 15Aug00 						g_lpLib3d->SetMaterial(thisMaterial, dithImg );
//DeadCode JON 15Aug00 					else
//DeadCode JON 15Aug00 						g_lpLib3d->SetMaterial(thisMaterial);
				}											// end of hirez or not
			}												// end of raised or not
		}													// end of loop all poly's
		g_lpLib3d->IncGlobal( TOGGLE_TEXTURE_ZBIAS );
	}

	// now we want to draw in hedges.. - go through lines database, find any hedges and draw in doublesided poly
	// to represent them.
	// also draw in cliff faces...
	lf = LF_AMBIENT;
	g_lpLib3d->SetObjectLighting( lf );
//DeadCode JON 28Sep00 	g_lpLib3d->DecGlobal( TOGGLE_TEXTURE_ZBIAS );

	if ( doRaises && hedgeHeight > sRaise ) // only do when closeup
	{
//DeadCode JON 7Nov00 		item treeItem;
//DeadCode JON 7Nov00 		treeItem.Anim=CloudAnimP;	

		pDataStream = pDS+ddh.lineOffset;
		Float ddy;
		ddy=hedgeHeight;		
		lineCount=ddh.noOfLines; 
		short lastTileCoord = 0;

		while ( lineCount-- )
		{
			UByte rt =*pDataStream++;
			int secCount = (*pDataStream++)-1;
			switch( rt )
			{
			case RT_HedgerowThick: case RT_HedgerowThin:
				{														// this is a hedge, draw it in.
					g_lpLib3d->DecGlobal( TOGGLE_TEXTURE_ZBIAS );

					DoPointStruc bottom[2];
					DoPointStruc top[2];
					DoPointStruc* bStartPtr = &bottom[0];
					DoPointStruc* bEndPtr = &bottom[1];
					DoPointStruc* tStartPtr = &top[0];
					DoPointStruc* tEndPtr = &top[1];
					
					UByte startP,endP;
					endP = *pDataStream++;

					*tEndPtr = pPoints[endP];
					tEndPtr->incPosY( ddy );
					*bEndPtr = pPoints[endP];

//DeadCode JON 7Nov00 					// do a tree...
//DeadCode JON 7Nov00 					if ( doItems )
//DeadCode JON 7Nov00 					{
//DeadCode JON 7Nov00 						float xT, yT, zT;
//DeadCode JON 7Nov00 						bEndPtr->getPosition(
//DeadCode JON 7Nov00 							xT, yT, zT
//DeadCode JON 7Nov00 						);
//DeadCode JON 7Nov00 
//DeadCode JON 7Nov00 						treeItem.World.X=view.X+SLong(F2UL_Round( xT ));
//DeadCode JON 7Nov00 						treeItem.World.Y=SLong(F2UL_Round( yT ));
//DeadCode JON 7Nov00 						treeItem.World.Z=view.Z+SLong(F2UL_Round( zT ));
//DeadCode JON 7Nov00 						treeItem.shape=ShapeNum(TREE1+((inptDefs[endP].alt+ inptDefs[endP].z )&1));
//DeadCode JON 7Nov00 
//DeadCode JON 7Nov00 						Three_Dee.do_object_dummy(&treeItem,STATIC_OBJECT);
//DeadCode JON 7Nov00 					}

					while (secCount--)
					{
						// iterate
						DoPointStruc *t = bStartPtr;
						bStartPtr = bEndPtr;
						bEndPtr = t;
						t = tStartPtr;
						tStartPtr = tEndPtr;
						tEndPtr = t;

						endP=*pDataStream++;
						*tEndPtr = pPoints[endP];
						tEndPtr->incPosY( ddy );

						*bEndPtr = pPoints[endP];
						// end of iterate

//DeadCode JON 7Nov00 						// do a tree...
//DeadCode JON 7Nov00 						if ( doItems )
//DeadCode JON 7Nov00 						{
//DeadCode JON 7Nov00 							float xT, yT, zT;
//DeadCode JON 7Nov00 							bEndPtr->getPosition(
//DeadCode JON 7Nov00 								xT, yT, zT
//DeadCode JON 7Nov00 							);
//DeadCode JON 7Nov00 
//DeadCode JON 7Nov00 							treeItem.World.X=view.X+SLong(F2UL_Round( xT ));
//DeadCode JON 7Nov00 							treeItem.World.Y=SLong(F2UL_Round( yT ));
//DeadCode JON 7Nov00 							treeItem.World.Z=view.Z+SLong(F2UL_Round( zT ));
//DeadCode JON 7Nov00 							treeItem.shape=ShapeNum(TREE1+((inptDefs[endP].alt+ inptDefs[endP].z )&1));
//DeadCode JON 7Nov00 
//DeadCode JON 7Nov00 							Three_Dee.do_object_dummy(&treeItem,STATIC_OBJECT);
//DeadCode JON 7Nov00 						}


						//work out texture tiling coords
						float dx = bStartPtr->getPosX() - bEndPtr->getPosX();
						float dz = bStartPtr->getPosZ() - bEndPtr->getPosZ();
						float dist = fastMath.FastSqrt( (dx*dx) + (dz*dz) );

//DeadCode JON 31Aug00 						bEndPtr->setIMapCoords( lastTileCoord, 128 );
//DeadCode JON 31Aug00 						tEndPtr->setIMapCoords( lastTileCoord, 0 );
						bEndPtr->setIMapCoords( lastTileCoord, 129 );
						tEndPtr->setIMapCoords( lastTileCoord, 1 );

						lastTileCoord +=short( dist*(1.0/48.0) );

//DeadCode JON 31Aug00 						bStartPtr->setIMapCoords( lastTileCoord, 128 );
//DeadCode JON 31Aug00 						tStartPtr->setIMapCoords( lastTileCoord, 0 );
						bStartPtr->setIMapCoords( lastTileCoord, 129 );
						tStartPtr->setIMapCoords( lastTileCoord, 1 );

						// draw tree line

						// first side
						pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(TREELINENO)),4);
						*pRVerts++ = *tEndPtr;
						*pRVerts++ = *tStartPtr;
						*pRVerts++ = *bStartPtr;
						*pRVerts++ = *bEndPtr;
						g_lpLib3d->EndPoly();

						//second side
						pRVerts = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(TREELINENO)),4);
						*pRVerts++ = *tStartPtr;
						*pRVerts++ = *tEndPtr;
						*pRVerts++ = *bEndPtr;
						*pRVerts++ = *bStartPtr;
						g_lpLib3d->EndPoly();

					} // end of loop through line sections

					g_lpLib3d->IncGlobal( TOGGLE_TEXTURE_ZBIAS );

				} 
				break;
				case RT_Cliff:										// it's a cliff - draw in...
				{
					int startP,endP;
					endP = *pDataStream++;

					while (secCount--)
					{
						startP=endP;
						endP=*pDataStream++;
						// end of iterate

							DrawCliffFace( startP, endP, pointOffsets );
#ifdef _DOUBLE_SIDED_CLIFFS_
						DrawCliffFace( endP, startP, pointOffsets );
#endif
					}		// end of iterate sections 
				}
				break;
				case RT_CliffRot:									// it's a cliff - draw in...
				{
					int startP,endP;
					endP = *pDataStream++;

					while (secCount--)
					{
						startP=endP;
						endP=*pDataStream++;
						// end of iterate

#ifdef _DOUBLE_SIDED_CLIFFS_
							DrawCliffFace( startP, endP, pointOffsets );
#endif
						DrawCliffFace( endP, startP, pointOffsets );
				}		// end of iterate sections 
				}
				break;
				default:											// it's not a hedge, don't do anything
				{
					pDataStream+=(++secCount);
				}
				break;
			}  // end of switch route type
		} // end of loop through lines
//DeadCode JON 7Nov00 		treeItem.Anim = ANIM_NULL;
	} else 
	{															// don't draw hedges
		pDataStream = pDS+ddh.lineOffset;
		lineCount=ddh.noOfLines; 

		while ( lineCount-- )
		{
			UByte rt =*pDataStream++;
			int secCount = (*pDataStream++)-1;
			switch( rt )
			{
				case RT_Cliff:										// it's a cliff - draw in...
				{
					int startP,endP;
					endP = *pDataStream++;

					while (secCount--)
					{
						startP=endP;
						endP=*pDataStream++;
						// end of iterate

							DrawCliffFace( startP, endP, pointOffsets );
#ifdef _DOUBLE_SIDED_CLIFFS_
							DrawCliffFace( endP, startP, pointOffsets );
#endif
					}		// end of iterate sections 
				}
				break;
				case RT_CliffRot:									// it's a cliff - draw in...
				{
					int startP,endP;
					endP = *pDataStream++;

					while (secCount--)
					{
						startP=endP;
						endP=*pDataStream++;
						// end of iterate

#ifdef _DOUBLE_SIDED_CLIFFS_
							DrawCliffFace( startP, endP, pointOffsets );
#endif
							DrawCliffFace( endP, startP, pointOffsets );

					}		// end of iterate sections 
				}
				break;
				default:											// it's not a hedge, don't do anything
				{
					pDataStream+=(++secCount);
				}
				break;
			}  // end of switch route type
		} // end of loop through lines
	} // end of draw line sides

	g_lpLib3d->SetObjectLighting( lf );

#ifdef _TILE_POSITIONS_IN_MATRIX
	g_lpLib3d->PopMatrix( MATRIX_OBJECT );
#endif
//TempCode JON 4Sep00 
//TempCode JON 4Sep00 	// draw a border round the grid...
//TempCode JON 4Sep00 	pRVerts = g_lpLib3d->BeginFan( HMATERIAL( 250 ), 4 );
//TempCode JON 4Sep00 	*pRVerts++ = pPoints[0];
//TempCode JON 4Sep00 	*pRVerts++ = pPoints[1];
//TempCode JON 4Sep00 	*pRVerts = pPoints[1];
//TempCode JON 4Sep00 	pRVerts->incPosY( 60.f );
//TempCode JON 4Sep00 	pRVerts++;
//TempCode JON 4Sep00 	*pRVerts = pPoints[0];
//TempCode JON 4Sep00 	pRVerts->incPosY( 60.f );
//TempCode JON 4Sep00 	g_lpLib3d->EndFan();
//TempCode JON 4Sep00 
//TempCode JON 4Sep00 	pRVerts = g_lpLib3d->BeginFan( HMATERIAL( 250 ), 4 );
//TempCode JON 4Sep00 	*pRVerts++ = pPoints[1];
//TempCode JON 4Sep00 	*pRVerts++ = pPoints[2];
//TempCode JON 4Sep00 	*pRVerts = pPoints[2];
//TempCode JON 4Sep00 	pRVerts->incPosY( 60.f );
//TempCode JON 4Sep00 	pRVerts++;
//TempCode JON 4Sep00 	*pRVerts = pPoints[1];
//TempCode JON 4Sep00 	pRVerts->incPosY( 60.f );
//TempCode JON 4Sep00 	g_lpLib3d->EndFan();
//TempCode JON 4Sep00 
//TempCode JON 4Sep00 	pRVerts = g_lpLib3d->BeginFan( HMATERIAL( 250 ), 4 );
//TempCode JON 4Sep00 	*pRVerts++ = pPoints[1];
//TempCode JON 4Sep00 	*pRVerts++ = pPoints[0];
//TempCode JON 4Sep00 	*pRVerts = pPoints[0];
//TempCode JON 4Sep00 	pRVerts->incPosY( 60.f );
//TempCode JON 4Sep00 	pRVerts++;
//TempCode JON 4Sep00 	*pRVerts = pPoints[1];
//TempCode JON 4Sep00 	pRVerts->incPosY( 60.f );
//TempCode JON 4Sep00 	g_lpLib3d->EndFan();
//TempCode JON 4Sep00 
//TempCode JON 4Sep00 	pRVerts = g_lpLib3d->BeginFan( HMATERIAL( 250 ), 4 );
//TempCode JON 4Sep00 	*pRVerts++ = pPoints[2];
//TempCode JON 4Sep00 	*pRVerts++ = pPoints[1];
//TempCode JON 4Sep00 	*pRVerts = pPoints[1];
//TempCode JON 4Sep00 	pRVerts->incPosY( 60.f );
//TempCode JON 4Sep00 	pRVerts++;
//TempCode JON 4Sep00 	*pRVerts = pPoints[2];
//TempCode JON 4Sep00 	pRVerts->incPosY( 60.f );
//TempCode JON 4Sep00 	g_lpLib3d->EndFan();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SoftTile
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddTileSub
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SubdivisionNeeded
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Split
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PerspectivePoly
//Author		Paul.   
//Date			Fri 25 Jun 1999
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetClipFlags
//Author		Paul.   
//Date			Mon 27 Jul 1998
//
//Returns		0x00=visible
//				or some combination of...
//				0x01=off left
//				0x02=off right
//				0x04=off top
//				0x08=off bottom
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToTop
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToBottom
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToLeft
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClipToRight
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Macro			DoClip
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TriClipper
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClippedTile
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetCloudLevel
//Author		Paul.   
//Date			Mon 16 Sep 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetCloudLevel(COORDS3D& world)
{
	return _cloudLayerHeight;	//CEILING_ALT;	//_Collide.CloudAltitude(world);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroundLevel
//Author		Paul.   
//Date			Thu 2 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetGroundLevel(ItemBasePtr src,UByte* pAreaType,bool fReallyGetData)			//RDH 17Jun96
{
	return(GetGroundLevel(src->World,pAreaType,fReallyGetData));
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetGroundLevel
//LastModified:	PD 19Dec95
//Author		Paul.   
//Date			Mon 6 Nov 1995
//
//Description	Need int return rather than modifying coords
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetGroundLevel(COORDS3D& world,UByte* pAreaType,bool fReallyGetData)
{
	return _Collide.GroundAltitude(world,pAreaType,fReallyGetData);
}

////////////////////////////////////////////////////////////////////////////////
//
//							GENERAL ROUTINES
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LandScape
//LastModified:	PD 20May96
//Author		Paul.   
//Date			Mon 6 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
LandScape::LandScape()
{
	// build the sidelookup table... - initialise the RaiseLookup wiv full raises (and copy the offsets)
	{
		hedgeHeight = HEDGE_HEIGHT;
//DeadCode JON 4Oct00 		cliffHeight = CLIFF_HEIGHT;
		for ( int i=0; i<FULLHTOFFSET; i++ )
			RaiseLookUp[i]=RaiseLookUp[i+FULLHTOFFSET];	
	}

	
//DeadCode JON 21Sep00 #pragma warnmsg ( "check why the extra buffer is needed - something is stomping" )
	// jon - precalc the side lookup table (only done once)
	SideLookUp = new raiseSide[NUM_SIDE_TYPES+1]; //extra one for the one being tested...
	int t = 0;
	for ( UByte i = 0; i < 32*4; i++ )
	{
		for ( UByte j = 0; j < 32*4; j++ )
		{
//TempCode JON 20Sep00 			if ( GetRaisePtOffset(i) < GetRaisePtOffset(j) )
			if ( GetUnscaledRaiseHt(i) < GetUnscaledRaiseHt(j) )
			{
				SideLookUp[t].lowerAT=i;
				SideLookUp[t].higherAT=j;
				for ( int k = 0; k< t; k++ )
					if ( SideLookUp[k] == SideLookUp[t] )
						break;
				if ( k == t ) // got all the way through, keep
					t++;
			}
		}
	}
	// t now contains the number of different side types - should be equal to NUM_SIDE_TYPES
	if ( t != NUM_SIDE_TYPES )
		INT3; // make it so
	
//Data for producing roads etc
//type,width(cm),colour,plain texture,x0,y0,x1,y1,masked texture,x0,y0,x1,y1

const LandMapNum coastMap(FIL_ROUTE2_NUM,DIR_LANDMAP2);
const LandMapNum woodMap(FIL_ROUTE1_NUM,DIR_LANDMAP2);
const LandMapNum lakeMap(FIL_ROUTE2_NUM,DIR_LANDMAP2);
const LandMapNum riverMap(FIL_ROUTE3_NUM,DIR_LANDMAP2);
const LandMapNum railMap(FIL_ROUTE1_NUM,DIR_LANDMAP2);
const LandMapNum roadMap(FIL_ROUTE1_NUM,DIR_LANDMAP2);

const LandMapNum coastMsk(FIL_ROUTE2_NUM,DIR_LANDMAP2);
const LandMapNum woodMsk(FIL_ROUTE1_NUM,DIR_LANDMAP2);
const LandMapNum lakeMsk(FIL_ROUTE2_NUM,DIR_LANDMAP2);
const LandMapNum riverMsk(FIL_ROUTE3_NUM,DIR_LANDMAP2);
const LandMapNum railMsk(FIL_ROUTE1_NUM,DIR_LANDMAP2);
const LandMapNum roadMsk(FIL_ROUTE1_NUM,DIR_LANDMAP2);

const RouteData coastRoute(_coast,1000,2000,ARTWORKMASK,coastMap,64,0,127,127,coastMsk,64,0,127,127);
const RouteData woodRoute(_wood,2000,2000,BLACK,woodMap,0,0,63,127,woodMsk,0,0,63,127);
const RouteData lakeRoute(_lake,800,800,ARTWORKMASK,lakeMap,0,0,63,127,lakeMsk,0,0,63,127);
const RouteData riverRoute(_river,4000,8000,Colour(196),riverMap,0,0,63,127,riverMsk,0,0,63,127);
const RouteData railRoute(_rail,3000,3000,Colour(179),railMap,0,0,63,127,railMsk,0,0,63,127);
const RouteData roadRoute(_road,3000,3000,Colour(181),roadMap,64,0,127,127,roadMsk,64,0,127,127);
const RouteData trackRoute(_track,1500,1500,Colour(181),roadMap,64,0,127,127,roadMsk,64,0,127,127);
const RouteData NULLRoute(0xFFFF,2000,2000,BLACK,roadMap,0,0,63,127,roadMsk,0,0,63,127);

	static RouteData routeData[]={
		/* coastRoute,	woodRoute,lakeRoute,*/ 	riverRoute,
		railRoute,	roadRoute, NULLRoute
	};
	pRouteData=routeData;

	cloud_base=CloudsAt10000ft;									//PD 11Oct96
//DEADCODE PD 02/12/99 	currscreen=NULL;
	cloudset.X = 0;
	cloudset.Y = 0;
	cloudset.Z = 0;

//DeadCode JON 12Sep00 	gridCorners=NULL;
	gridCone=NULL;
	horizCone=NULL;
//DeadCode JON 5Sep00 	softGrid=NULL;
//DeadCode JON 12Sep00 	lightCone=NULL;
//DEADCODE JON 4/26/00 	pLastGrid=NULL;
	tileCacheGrid=NULL;
	TileResList::theGrid = NULL;
//DEADCODE JON 4/27/00 	pHTextureGrid=NULL;
//DeadCode JON 12Sep00 	routeDetail=NULL;
//DeadCode JON 3Aug00 	groundDetail=NULL;
//DeadCode JON 12Sep00 	landRnd=NULL;
	tileCoords=NULL;
	pDataBlocks=NULL;
	mistenabled=false;
	FilSkyStrip = FIL_NULL;
	pointList=NULL;
	polyList=NULL;
	meshCreated=false;
	topColor=HORIZON;	//color for top of horizon dome
	midColor=HORIZON;	//color for top of horizon texture strip
	botColor=HORIZON;	//color for horizon fade
	topR=topG=topB=0;
	midR=midG=midB=0;
	imageVTile=1;
	theHorizonStrip=FileNum(NULL);
//DeadCode JON 3Aug00 	highco=NULL;

	CloudAnimP = new UByte[8];									//RJS 21Apr99
	if (CloudAnimP != NULL)										//RJS 21Apr99
	{
		CloudAnimP = (AnimSizeField)sizeof(MinAnimData);		//RJS 01Dec99
		CloudAnimP = (AnimFlagField) (1<<MINANIM);				//RJS 01Dec99

		MinAnimData*	mad = (MinAnimData*) CloudAnimP;
		mad->itemstate = ALIVE;
		mad->nolaunchers = 0;
	}

 	#define P(p1) ((( UWord(p1*(255.f/100.f)) )<<8)+0xFF)	// give the value as a percent
	#define B(p1) (((p1)<<8)+0xFF)							// give the value from 0-255 (as a byte)

	static SLightingRGB dawnLighting=
	{
	//	RED			GREEN		BLUE			-- enter values as % of full strength
	//	
		{P(30),		P(30),		P(30)},	//		-- LANDSCAPE LOWEST
		{P(60),		P(60),		P(60)},//		-- LANDSCAPE HIGHEST
		{P(50),		P(50),		P(40)},	//		-- LANDSCAPE AMBIENT
		{P(45),		P(45),		P(45)},	//		-- SHADED OBJECTS LOWEST
		{B(244),	B(243),		B(190)},//		-- SHADED OBJECTS HIGHEST
		{B(213),	B(245),		B(245)},	//		-- SHADED OBJECTS AMBIENT
		{P(80),		P(00),		P(00)},	//		-- NON SHADED OBJECTS ?? LOWEST
		{P(60),		P(60),		P(60)},//		-- NON SHADED OBJECTS ?? HIGHEST
		{P(90),		P(90),		P(90)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS AMBIENT

		{B(101),	B(111),		B(135)},	//		-- deepestSkyCol	//AM 14Sep00
		{B(164),	B(187),		B(196)},	//		-- otherSkyCol - towards sun	//AM 14Sep00
		{B(198),	B(216),		B(237)},	//		-- cloudCol - towards sun	//AM 14Sep00	//AM 14Sep00
		{B(245),	B(234),		B(159)},	//		-- horizonCol - towards sun	//AM 14Sep00	//AM 14Sep00
		{B(228),	B(216),		B(166)},	//		-- fogCol - towards sun	//AM 14Sep00

		{B(109),	B(126),		B(165)},	//		-- otherSkyCol -away from sun
		{B(147),	B(171),		B(195)},	//		-- cloudCol -away from sun	//AM 14Sep00
		{B(148),	B(171),		B(194)},	//		-- horizonCol -away from sun	//AM 14Sep00
		{B(114),	B(147),		B(184)},	//		-- fogCol -away from sun	//AM 14Sep00

		{B(244),	B(243),		B(194)},	//		-- The colour to shade the sun... 
		
//		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 	//AM 14Sep00
		{B(253),	B(236),		B(189)}	//		-- The maximum specular highlight colour 
	};

	static SLightingRGB dayLighting=
	{
	//	RED			GREEN		BLUE			-- enter values as % of full strength
	//	
		{P(50),		P(50),		P(50)},	//		-- LANDSCAPE LOWEST
		{P(100),	P(100),		P(100)},//		-- LANDSCAPE HIGHEST
		{P(90),		P(90),		P(90)},	//		-- LANDSCAPE AMBIENT
		{P(45),		P(45),		P(45)},	//		-- SHADED OBJECTS LOWEST
		{B(255),	B(255),		B(255)},//		-- SHADED OBJECTS HIGHEST
		{B(213),	B(245),		B(245)},	//		-- SHADED OBJECTS AMBIENT
		{P(80),		P(00),		P(00)},	//		-- NON SHADED OBJECTS ?? LOWEST
		{P(100),	P(100),		P(100)},//		-- NON SHADED OBJECTS ?? HIGHEST
		{P(90),		P(90),		P(90)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS AMBIENT
		{B(1),		B(77),		B(215)},	//		-- deepestSkyCol	//AM 14Sep00
		{B(144),	B(184),		B(232)},	//		-- otherSkyCol - towards sun	//AM 14Sep00
		{B(198),	B(216),		B(237)},	//		-- cloudCol - towards sun	//AM 14Sep00	//AM 14Sep00
		{B(162),	B(195),		B(236)},	//		-- horizonCol - towards sun	//AM 14Sep00	//AM 14Sep00
		{B(144),	B(184),		B(232)},	//		-- fogCol - towards sun	//AM 14Sep00

		{B(112),	B(165),		B(224)},	//		-- otherSkyCol -away from sun
		{B(198),	B(216),		B(237)},	//		-- cloudCol -away from sun	//AM 14Sep00
		{B(162),	B(195),		B(236)},	//		-- horizonCol -away from sun	//AM 14Sep00
		{B(144),	B(184),		B(232)},	//		-- fogCol -away from sun	//AM 14Sep00

		{B(255),	B(255),		B(255)},	//		-- The colour to shade the sun... 
		
//		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 	//AM 14Sep00
		{B(255),	B(255),		B(255)}	//		-- The maximum specular highlight colour 
	};

	static SLightingRGB duskLighting=		  //actually a sunset now.	//AM 17Oct00
	{
	//	RED			GREEN		BLUE			-- enter values as % of full strength if P or byte vals if B
	//	

		{P(50),		P(50),		P(50)},	//		-- LANDSCAPE LOWEST
		{B(255),	B(163),		B(43)},//		-- LANDSCAPE HIGHEST
		{P(90),		P(90),		P(90)},	//		-- LANDSCAPE AMBIENT
		{B(134),	B(98),		B(0)},	//		-- SHADED OBJECTS LOWEST
		{B(255),	B(214),		B(115)},//		-- SHADED OBJECTS HIGHEST
		{B(213),	B(245),		B(245)},	//		-- SHADED OBJECTS AMBIENT
		{P(80),		P(00),		P(00)},	//		-- NON SHADED OBJECTS ?? LOWEST
		{B(255),	B(163),		B(43)},	//		-- NON SHADED OBJECTS ?? HIGHEST
		{P(50),		P(50),		P(50)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS AMBIENT
		{B(243),	B(130),		B(69)},		//		-- deepestSkyCol	//AM 14Sep00
		{B(214),	B(179),		B(94)},	//		-- otherSkyCol - towards sun	//AM 14Sep00
		{B(228),	B(215),		B(156)},	//		-- cloudCol - towards sun	//AM 14Sep00	//AM 14Sep00
		{B(255),	B(201),		B(15)},		//		-- horizonCol - towards sun	//AM 14Sep00	//AM 14Sep00
		{B(255),	B(179),		B(15)},		//		-- fogCol - towards sun	//AM 14Sep00

		{B(147),	B(171),		B(195)},	//		-- otherSkyCol -away from sun
		{B(214),	B(195),		B(219)},	//		-- cloudCol -away from sun	//AM 14Sep00
		{B(173),	B(184),		B(197)},	//		-- horizonCol -away from sun	//AM 14Sep00
		{B(207),	B(189),		B(149)},	//		-- fogCol -away from sun	//AM 14Sep00

		{B(255),	B(252),		B(183)},	//		-- The colour to shade the sun... 
		
//		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 	//AM 14Sep00
		{B(251),	B(229),		B(139)}	//		-- The maximum specular highlight colour 

	};

	static SLightingRGB niteLighting=
	{
	//	RED			GREEN		BLUE			-- enter values as % of full strength
	//	
		{P(5),		P(5),		P(5)},	//		-- LANDSCAPE LOWEST
		{P(15),		P(15),		P(15)},	//		-- LANDSCAPE HIGHEST
		{P(10),		P(10),		P(10)},	//		-- LANDSCAPE AMBIENT
		{P(5),		P(5),		P(5)},	//		-- SHADED OBJECTS LOWEST
		{P(15),		P(15),		P(15)},	//		-- SHADED OBJECTS HIGHEST
		{P(10),		P(10),		P(10)},	//		-- SHADED OBJECTS AMBIENT
		{P(5),		P(5),		P(5)},	//		-- NON SHADED OBJECTS ?? LOWEST
		{P(15),		P(15),		P(15)},	//		-- NON SHADED OBJECTS ?? HIGHEST
		{P(10),		P(10),		P(10)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//		-- EFFECTS LOWEST	//AM 14Jul00
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//		-- EFFECTS HIGHEST	//AM 14Jul00
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//		-- EFFECTS AMBIENT	//AM 14Jul00
		{B(0),		B(0),		B(0)},	//		-- deepestSkyCol
		{B(5),		B(5),		B(5)},	//		-- otherSkyCol - towards sun
		{B(10),		B(10),		B(10)},	//		-- cloudCol - towards sun
		{B(0),		B(0),		B(0)},	//		-- horizonCol - towards sun
		{B(0),		B(0),		B(5)},	//		-- fogCol - towards sun

		{B(5),		B(5),		B(5)},	//		-- otherSkyCol -away from sun
		{B(10),		B(10),		B(10)},	//		-- cloudCol -away from sun
		{B(0),		B(0),		B(0)},	//		-- horizonCol -away from sun
		{B(0),		B(0),		B(5)},	//		-- fogCol -away from sun

		{B(0),		B(0),		B(0)},	//		-- The colour to shade the sun... 

//DeadCode JON 2Oct00 		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 
		{B(87),		B(88),		B(143)}	//		-- The maximum specular highlight colour 

	};

//DeadCode JON 2Nov00 	static SLightingRGB badWLighting=
//DeadCode JON 2Nov00 	{
//DeadCode JON 2Nov00 	//	RED			GREEN		BLUE			-- enter values as % of full strength
//DeadCode JON 2Nov00 	//	
//DeadCode JON 2Nov00 		{P(40),		P(40),		P(40)},	//		-- LANDSCAPE LOWEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},//		-- LANDSCAPE HIGHEST
//DeadCode JON 2Nov00 		{P(70),		P(70),		P(70)},	//		-- LANDSCAPE AMBIENT
//DeadCode JON 2Nov00 		{P(40),		P(40),		P(40)},	//		-- SHADED OBJECTS LOWEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},//		-- SHADED OBJECTS HIGHEST
//DeadCode JON 2Nov00 		{P(70),		P(70),		P(70)},	//		-- SHADED OBJECTS AMBIENT
//DeadCode JON 2Nov00 		{P(40),		P(40),		P(40)},	//		-- NON SHADED OBJECTS ?? LOWEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},//		-- NON SHADED OBJECTS ?? HIGHEST
//DeadCode JON 2Nov00 		{P(70),		P(70),		P(70)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode JON 2Nov00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS AMBIENT	};
//DeadCode JON 2Nov00 		{B(0x44),	B(0x44),	B(0xFF)},	//		-- deepestSkyCol 
//DeadCode JON 2Nov00 		{B(0xAA),	B(0xAA),	B(0xFF)},	//		-- otherSkyCol - towards sun
//DeadCode JON 2Nov00 		{B(0xFF),	B(0xFF),	B(0xFF)},	//		-- cloudCol - towards sun
//DeadCode JON 2Nov00 		{B(0x90),	B(0xB8),	B(0xE8)},	//		-- horizonCol - towards sun
//DeadCode JON 2Nov00 		{B(0x70),	B(0x98),	B(0xC8)},	//		-- fogCol - towards sun
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		{B(0xAA),	B(0xAA),	B(0xFF)},	//		-- otherSkyCol -away from sun
//DeadCode JON 2Nov00 		{B(0xFF),	B(0xFF),	B(0xFF)},	//		-- cloudCol -away from sun
//DeadCode JON 2Nov00 		{B(0x90),	B(0xB8),	B(0xE8)},	//		-- horizonCol -away from sun
//DeadCode JON 2Nov00 		{B(0x70),	B(0x98),	B(0xC8)},	//		-- fogCol -away from sun
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		{B(240),	B(240),		B(240)}, //		-- The colour to shade the sun... 
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 	};


//DeadCode JON 2Nov00 	static SLightingRGB mapLighting= // do i need this?????
//DeadCode JON 2Nov00 	{
//DeadCode JON 2Nov00 	//	RED			GREEN		BLUE			-- enter values as % of full strength
//DeadCode JON 2Nov00 	//	
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- LANDSCAPE LOWEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- LANDSCAPE HIGHEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- LANDSCAPE AMBIENT
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- SHADED OBJECTS LOWEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- SHADED OBJECTS HIGHEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- SHADED OBJECTS AMBIENT
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- NON SHADED OBJECTS ?? LOWEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- NON SHADED OBJECTS ?? HIGHEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- COCKPIT LOWEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- COCKPIT HIGHEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- COCKPIT AMBIENT
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- EFFECTS LOWEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- EFFECTS HIGHEST
//DeadCode JON 2Nov00 		{P(100),	P(100),		P(100)},	//	-- EFFECTS AMBIENT
//DeadCode JON 2Nov00 		{B(0x44),	B(0x44),	B(0xFF)},	//		-- deepestSkyCol 
//DeadCode JON 2Nov00 		{B(0xAA),	B(0xAA),	B(0xFF)},	//		-- otherSkyCol - towards sun
//DeadCode JON 2Nov00 		{B(0xFF),	B(0xFF),	B(0xFF)},	//		-- cloudCol - towards sun
//DeadCode JON 2Nov00 		{B(0x90),	B(0xB8),	B(0xE8)},	//		-- horizonCol - towards sun
//DeadCode JON 2Nov00 		{B(0x70),	B(0x98),	B(0xC8)},	//		-- fogCol - towards sun
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		{B(0xAA),	B(0xAA),	B(0xFF)},	//		-- otherSkyCol -away from sun
//DeadCode JON 2Nov00 		{B(0xFF),	B(0xFF),	B(0xFF)},	//		-- cloudCol -away from sun
//DeadCode JON 2Nov00 		{B(0x90),	B(0xB8),	B(0xE8)},	//		-- horizonCol -away from sun
//DeadCode JON 2Nov00 		{B(0x70),	B(0x98),	B(0xC8)},	//		-- fogCol -away from sun
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		{B(240),	B(240),		B(240)}, //		-- The colour to shade the sun... 
//DeadCode JON 2Nov00 		
//DeadCode JON 2Nov00 		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 	};

//DeadCode CSB 19Oct100 	static SLightingRGB dawnLighting=
//DeadCode CSB 19Oct100 	{
//DeadCode CSB 19Oct100 	//	RED			GREEN		BLUE			-- enter values as % of full strength
//DeadCode CSB 19Oct100 	//	
//DeadCode CSB 19Oct100 		{P(20),		P(20),		P(20)},	//		-- LANDSCAPE LOWEST
//DeadCode CSB 19Oct100 		{P(40),		P(40),		P(40)},//		-- LANDSCAPE HIGHEST
//DeadCode CSB 19Oct100 		{P(50),		P(50),		P(50)},	//		-- LANDSCAPE AMBIENT
//DeadCode CSB 19Oct100 		{P(45),		P(45),		P(45)},	//		-- SHADED OBJECTS LOWEST
//DeadCode CSB 19Oct100 		{B(255),	B(255),		B(255)},//		-- SHADED OBJECTS HIGHEST
//DeadCode CSB 19Oct100 		{B(247),	B(246),		B(177)},	//		-- SHADED OBJECTS AMBIENT
//DeadCode CSB 19Oct100 		{P(20),		P(20),		P(20)},	//		-- NON SHADED OBJECTS ?? LOWEST
//DeadCode CSB 19Oct100 		{P(40),		P(40),		P(40)},//		-- NON SHADED OBJECTS ?? HIGHEST
//DeadCode CSB 19Oct100 		{P(50),		P(50),		P(50)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS AMBIENT
//DeadCode CSB 19Oct100 		{B(7),		B(76),		B(141)},	//		-- deepestSkyCol	//AM 14Sep00	//AM 15Sep00
//DeadCode CSB 19Oct100 		{B(174),	B(192),		B(192)},	//		-- otherSkyCol - towards sun	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(244),	B(228),		B(152)},	//		-- cloudCol - towards sun	//AM 14Sep00	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(251),	B(242),		B(201)},	//		-- horizonCol - towards sun	//AM 14Sep00	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(245),	B(246),		B(128)},	//		-- fogCol - towards sun	//AM 14Sep00
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(122),	B(127),		B(150)},	//		-- otherSkyCol -away from sun
//DeadCode CSB 19Oct100 		{B(182),	B(168),		B(102)},	//		-- cloudCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(163),	B(153),		B(107)},	//		-- horizonCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(121),	B(121),		B(81)},		//		-- fogCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 	
//DeadCode CSB 19Oct100 		{B(255),	B(122),		B(57)},	//		-- The colour to shade the sun... 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 //		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(251),	B(242),		B(201)}	//		-- The maximum specular highlight colour 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 //DeadCode JON 11Sep00 		{B(0),		B(0),		B(155)},	//		-- deepestSkyCol
//DeadCode CSB 19Oct100 //DeadCode JON 11Sep00 		{B(84),		B(100),		B(144)},	//		-- otherSkyCol		//AM 14Jul00
//DeadCode CSB 19Oct100 //DeadCode JON 11Sep00 		{B(86),		B(129),		B(130)},	//		-- cloudCol			//AM 14Jul00
//DeadCode CSB 19Oct100 //DeadCode JON 11Sep00 		{B(245),	B(222),		B(141)},	//		-- horizonCol		//AM 14Jul00
//DeadCode CSB 19Oct100 //DeadCode JON 11Sep00 		{B(254),	B(191),		B(40)}		//		-- fogCol			//AM 14Jul00
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	};
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 	static SLightingRGB dayLighting=
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 	{
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 	//	RED			GREEN		BLUE			-- enter values as % of full strength
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 	//	
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(80),		P(80),		P(80)},	//		-- LANDSCAPE LOWEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(100),	P(100),		P(100)},//		-- LANDSCAPE HIGHEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(90),		P(90),		P(90)},	//		-- LANDSCAPE AMBIENT
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(80),		P(80),		P(80)},	//		-- SHADED OBJECTS LOWEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(100),	P(100),		P(100)},//		-- SHADED OBJECTS HIGHEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(90),		P(90),		P(90)},	//		-- SHADED OBJECTS AMBIENT
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(80),		P(80),		P(80)},	//		-- NON SHADED OBJECTS ?? LOWEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(100),	P(100),		P(100)},//		-- NON SHADED OBJECTS ?? HIGHEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(90),		P(90),		P(90)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 		{P(0),		P(0),		P(0)}	//		-- EFFECTS AMBIENT
//DeadCode CSB 19Oct100 //TEMPCODE JON 4/19/00 	};
//DeadCode CSB 19Oct100 	static SLightingRGB dayLighting=
//DeadCode CSB 19Oct100 	{
//DeadCode CSB 19Oct100 	//	RED			GREEN		BLUE			-- enter values as % of full strength
//DeadCode CSB 19Oct100 	//	
//DeadCode CSB 19Oct100 		{P(50),		P(50),		P(50)},	//		-- LANDSCAPE LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},//		-- LANDSCAPE HIGHEST
//DeadCode CSB 19Oct100 		{P(90),		P(90),		P(90)},	//		-- LANDSCAPE AMBIENT
//DeadCode CSB 19Oct100 		{P(45),		P(45),		P(45)},	//		-- SHADED OBJECTS LOWEST
//DeadCode CSB 19Oct100 		{B(255),	B(255),		B(255)},//		-- SHADED OBJECTS HIGHEST
//DeadCode CSB 19Oct100 		{B(213),	B(245),		B(245)},	//		-- SHADED OBJECTS AMBIENT
//DeadCode CSB 19Oct100 		{P(80),		P(00),		P(00)},	//		-- NON SHADED OBJECTS ?? LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},//		-- NON SHADED OBJECTS ?? HIGHEST
//DeadCode CSB 19Oct100 		{P(90),		P(90),		P(90)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS AMBIENT
//DeadCode CSB 19Oct100 		{B(1),		B(77),		B(215)},	//		-- deepestSkyCol	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(144),	B(184),		B(232)},	//		-- otherSkyCol - towards sun	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(198),	B(216),		B(237)},	//		-- cloudCol - towards sun	//AM 14Sep00	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(162),	B(195),		B(236)},	//		-- horizonCol - towards sun	//AM 14Sep00	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(144),	B(184),		B(232)},	//		-- fogCol - towards sun	//AM 14Sep00
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(112),	B(165),		B(224)},	//		-- otherSkyCol -away from sun
//DeadCode CSB 19Oct100 		{B(198),	B(216),		B(237)},	//		-- cloudCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(162),	B(195),		B(236)},	//		-- horizonCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(144),	B(184),		B(232)},	//		-- fogCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(255),	B(255),		B(255)},	//		-- The colour to shade the sun... 
//DeadCode CSB 19Oct100 		
//DeadCode CSB 19Oct100 //		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(255),	B(255),		B(255)}	//		-- The maximum specular highlight colour 
//DeadCode CSB 19Oct100 	};
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	static SLightingRGB duskLighting=
//DeadCode CSB 19Oct100 	{
//DeadCode CSB 19Oct100 	//	RED			GREEN		BLUE			-- enter values as % of full strength if P or byte vals if B
//DeadCode CSB 19Oct100 	//	
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{P(20),		P(20),		P(20)},	//		-- LANDSCAPE LOWEST		//AM 15Sep00
//DeadCode CSB 19Oct100 		{P(45),		P(50),		P(30)},//		-- LANDSCAPE HIGHEST	//AM 15Sep00
//DeadCode CSB 19Oct100 		{P(30),		P(30),		P(30)},	//		-- LANDSCAPE AMBIENT	//AM 15Sep00
//DeadCode CSB 19Oct100 		{P(45),		P(45),		P(45)},	//		-- SHADED OBJECTS LOWEST	//AM 15Sep00
//DeadCode CSB 19Oct100 		{B(255),	B(255),		B(255)},//		-- SHADED OBJECTS HIGHEST	//AM 15Sep00
//DeadCode CSB 19Oct100 		{B(213),	B(245),		B(245)},	//		-- SHADED OBJECTS AMBIENT	//AM 15Sep00
//DeadCode CSB 19Oct100 		{P(80),		P(00),		P(00)},	//		-- NON SHADED OBJECTS ?? LOWEST	//AM 15Sep00
//DeadCode CSB 19Oct100 		{P(40),		P(40),		P(50)},//		-- NON SHADED OBJECTS ?? HIGHEST	//AM 15Sep00
//DeadCode CSB 19Oct100 		{P(20),		P(20),		P(20)},	//		-- NON SHADED OBJECTS ?? AMBIENT	//AM 15Sep00
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS AMBIENT
//DeadCode CSB 19Oct100 		{B(85),		B(114),		B(161)},	//		-- deepestSkyCol	//AM 14Sep00	//AM 15Sep00
//DeadCode CSB 19Oct100 		{B(139),	B(143),		B(159)},	//		-- otherSkyCol - towards sun	//AM 14Sep00	//AM 15Sep00
//DeadCode CSB 19Oct100 		{B(140),	B(140),		B(140)},	//		-- cloudCol - towards sun	//AM 14Sep00	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(164),	B(163),		B(116)},	//		-- horizonCol - towards sun	//AM 14Sep00	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(151),	B(167),		B(131)},	//		-- fogCol - towards sun	//AM 14Sep00
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(117),	B(122),		B(141)},	//		-- otherSkyCol -away from sun
//DeadCode CSB 19Oct100 		{B(120),	B(120),		B(120)},	//		-- cloudCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(120),	B(120),		B(80)},	//		-- horizonCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(133),	B(148),		B(112)},	//		-- fogCol -away from sun	//AM 14Sep00
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(255),	B(122),		B(57)},	//		-- The colour to shade the sun... 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 //		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 	//AM 14Sep00
//DeadCode CSB 19Oct100 		{B(175),	B(177),		B(111)}	//		-- The maximum specular highlight colour 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	};
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	static SLightingRGB niteLighting=
//DeadCode CSB 19Oct100 	{
//DeadCode CSB 19Oct100 	//	RED			GREEN		BLUE			-- enter values as % of full strength
//DeadCode CSB 19Oct100 	//	
//DeadCode CSB 19Oct100 		{P(5),		P(5),		P(5)},	//		-- LANDSCAPE LOWEST
//DeadCode CSB 19Oct100 		{P(15),		P(15),		P(15)},	//		-- LANDSCAPE HIGHEST
//DeadCode CSB 19Oct100 		{P(10),		P(10),		P(10)},	//		-- LANDSCAPE AMBIENT
//DeadCode CSB 19Oct100 		{P(5),		P(5),		P(5)},	//		-- SHADED OBJECTS LOWEST
//DeadCode CSB 19Oct100 		{P(15),		P(15),		P(15)},	//		-- SHADED OBJECTS HIGHEST
//DeadCode CSB 19Oct100 		{P(10),		P(10),		P(10)},	//		-- SHADED OBJECTS AMBIENT
//DeadCode CSB 19Oct100 		{P(5),		P(5),		P(5)},	//		-- NON SHADED OBJECTS ?? LOWEST
//DeadCode CSB 19Oct100 		{P(15),		P(15),		P(15)},	//		-- NON SHADED OBJECTS ?? HIGHEST
//DeadCode CSB 19Oct100 		{P(10),		P(10),		P(10)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//		-- EFFECTS LOWEST	//AM 14Jul00
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//		-- EFFECTS HIGHEST	//AM 14Jul00
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//		-- EFFECTS AMBIENT	//AM 14Jul00
//DeadCode CSB 19Oct100 		{B(0),		B(0),		B(0)},	//		-- deepestSkyCol
//DeadCode CSB 19Oct100 		{B(5),		B(5),		B(5)},	//		-- otherSkyCol - towards sun
//DeadCode CSB 19Oct100 		{B(10),		B(10),		B(10)},	//		-- cloudCol - towards sun
//DeadCode CSB 19Oct100 		{B(0),		B(0),		B(0)},	//		-- horizonCol - towards sun
//DeadCode CSB 19Oct100 		{B(0),		B(0),		B(5)},	//		-- fogCol - towards sun
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(5),		B(5),		B(5)},	//		-- otherSkyCol -away from sun
//DeadCode CSB 19Oct100 		{B(10),		B(10),		B(10)},	//		-- cloudCol -away from sun
//DeadCode CSB 19Oct100 		{B(0),		B(0),		B(0)},	//		-- horizonCol -away from sun
//DeadCode CSB 19Oct100 		{B(0),		B(0),		B(5)},	//		-- fogCol -away from sun
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(0),		B(0),		B(0)},	//		-- The colour to shade the sun... 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 //DeadCode JON 2Oct00 		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 
//DeadCode CSB 19Oct100 		{B(87),		B(88),		B(143)}	//		-- The maximum specular highlight colour 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	};
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	static SLightingRGB badWLighting=
//DeadCode CSB 19Oct100 	{
//DeadCode CSB 19Oct100 	//	RED			GREEN		BLUE			-- enter values as % of full strength
//DeadCode CSB 19Oct100 	//	
//DeadCode CSB 19Oct100 		{P(40),		P(40),		P(40)},	//		-- LANDSCAPE LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},//		-- LANDSCAPE HIGHEST
//DeadCode CSB 19Oct100 		{P(70),		P(70),		P(70)},	//		-- LANDSCAPE AMBIENT
//DeadCode CSB 19Oct100 		{P(40),		P(40),		P(40)},	//		-- SHADED OBJECTS LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},//		-- SHADED OBJECTS HIGHEST
//DeadCode CSB 19Oct100 		{P(70),		P(70),		P(70)},	//		-- SHADED OBJECTS AMBIENT
//DeadCode CSB 19Oct100 		{P(40),		P(40),		P(40)},	//		-- NON SHADED OBJECTS ?? LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},//		-- NON SHADED OBJECTS ?? HIGHEST
//DeadCode CSB 19Oct100 		{P(70),		P(70),		P(70)},	//		-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- COCKPIT AMBIENT
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS LOWEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS HIGHEST
//DeadCode CSB 19Oct100 		{P(0),		P(0),		P(0)},	//		-- EFFECTS AMBIENT	};
//DeadCode CSB 19Oct100 		{B(0x44),	B(0x44),	B(0xFF)},	//		-- deepestSkyCol 
//DeadCode CSB 19Oct100 		{B(0xAA),	B(0xAA),	B(0xFF)},	//		-- otherSkyCol - towards sun
//DeadCode CSB 19Oct100 		{B(0xFF),	B(0xFF),	B(0xFF)},	//		-- cloudCol - towards sun
//DeadCode CSB 19Oct100 		{B(0x90),	B(0xB8),	B(0xE8)},	//		-- horizonCol - towards sun
//DeadCode CSB 19Oct100 		{B(0x70),	B(0x98),	B(0xC8)},	//		-- fogCol - towards sun
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(0xAA),	B(0xAA),	B(0xFF)},	//		-- otherSkyCol -away from sun
//DeadCode CSB 19Oct100 		{B(0xFF),	B(0xFF),	B(0xFF)},	//		-- cloudCol -away from sun
//DeadCode CSB 19Oct100 		{B(0x90),	B(0xB8),	B(0xE8)},	//		-- horizonCol -away from sun
//DeadCode CSB 19Oct100 		{B(0x70),	B(0x98),	B(0xC8)},	//		-- fogCol -away from sun
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(240),	B(240),		B(240)}, //		-- The colour to shade the sun... 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	};
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	static SLightingRGB mapLighting= // do i need this?????
//DeadCode CSB 19Oct100 	{
//DeadCode CSB 19Oct100 	//	RED			GREEN		BLUE			-- enter values as % of full strength
//DeadCode CSB 19Oct100 	//	
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- LANDSCAPE LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- LANDSCAPE HIGHEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- LANDSCAPE AMBIENT
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- SHADED OBJECTS LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- SHADED OBJECTS HIGHEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- SHADED OBJECTS AMBIENT
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- NON SHADED OBJECTS ?? LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- NON SHADED OBJECTS ?? HIGHEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- NON SHADED OBJECTS ?? AMBIENT
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- COCKPIT LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- COCKPIT HIGHEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- COCKPIT AMBIENT
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- EFFECTS LOWEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- EFFECTS HIGHEST
//DeadCode CSB 19Oct100 		{P(100),	P(100),		P(100)},	//	-- EFFECTS AMBIENT
//DeadCode CSB 19Oct100 		{B(0x44),	B(0x44),	B(0xFF)},	//		-- deepestSkyCol 
//DeadCode CSB 19Oct100 		{B(0xAA),	B(0xAA),	B(0xFF)},	//		-- otherSkyCol - towards sun
//DeadCode CSB 19Oct100 		{B(0xFF),	B(0xFF),	B(0xFF)},	//		-- cloudCol - towards sun
//DeadCode CSB 19Oct100 		{B(0x90),	B(0xB8),	B(0xE8)},	//		-- horizonCol - towards sun
//DeadCode CSB 19Oct100 		{B(0x70),	B(0x98),	B(0xC8)},	//		-- fogCol - towards sun
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(0xAA),	B(0xAA),	B(0xFF)},	//		-- otherSkyCol -away from sun
//DeadCode CSB 19Oct100 		{B(0xFF),	B(0xFF),	B(0xFF)},	//		-- cloudCol -away from sun
//DeadCode CSB 19Oct100 		{B(0x90),	B(0xB8),	B(0xE8)},	//		-- horizonCol -away from sun
//DeadCode CSB 19Oct100 		{B(0x70),	B(0x98),	B(0xC8)},	//		-- fogCol -away from sun
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 		{B(240),	B(240),		B(240)}, //		-- The colour to shade the sun... 
//DeadCode CSB 19Oct100 		
//DeadCode CSB 19Oct100 		{B(255),	B(224),		B(192)}	//		-- The maximum specular highlight colour 
//DeadCode CSB 19Oct100 
//DeadCode CSB 19Oct100 	};
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	static SLightingRGB dawnLighting=
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	{
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(105), B(84), B(46)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(158), B(158), B(109)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(174), B(174), B(94)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(162), B(165), B(129)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(252), B(207), B(190)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(198), B(199), B(223)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(77), B(59), B(50)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(206), B(179), B(132)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(105), B(84), B(46)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(128),B(128),B(128)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255), B(255), B(255)}
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	};
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	static SLightingRGB dayLighting=
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	{
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(142), B(166), B(200)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(208), B(228), B(240)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(216), B(232), B(248)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255), B(255), B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(159), B(181), B(222)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(102), B(138), B(201)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255), B(255), B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(248), B(254), B(203)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255), B(255), B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255), B(255), B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255), B(255), B(255)}
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	};
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	static SLightingRGB duskLighting=
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	{
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(72), B(77), B(100)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(199), B(158), B(84)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(233), B(105), B(50)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(214), B(113), B(69)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(149), B(162), B(166)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(24), B(38), B(63)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(41), B(55), B(68)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(236), B(122), B(47)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(61), B(84), B(112)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(128),B(128),B(128)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255), B(255), B(255)}
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	};
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	static SLightingRGB niteLighting=
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	{
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(60), B(82), B(89)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(94), B(129), B(140)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(61), B(56), B(116)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(45), B(43), B(64)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(82), B(79), B(123)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(7), B(9), B(30)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(17), B(23), B(28)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(60), B(60), B(70)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(34), B(51), B(71)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(128),B(128),B(128)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255), B(255), B(255)}
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	};
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	static SLightingRGB badWLighting=
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	{
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//horizon base
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//top of hrzn strip														
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//under clouds														
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//at clouds														
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//above clouds														
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//ceiling colour							
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//land ambient														
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//l-shade ambient														
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff},		//other ambient
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{0x3fff,0x3fff,0x3fff}
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	};
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	static SLightingRGB mapLighting=
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	{
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)},
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 		{B(255),B(255),B(255)}
//DeadCode CSB 19Oct100 //DEADCODE JON 3/30/00 	};

	pDawn=&dawnLighting;
	pDay=&dayLighting;
	pDusk=&duskLighting;
	pNite=&niteLighting;
//DeadCode JON 2Nov00 	pBadW=&badWLighting;
//DeadCode JON 2Nov00 	pMapL=&mapLighting;

	currentLighting=dayLighting;	//safe default...

	smkList = new SmkCloudDesc[MaxSmokeClouds];
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DecDetailLevel
//Author		Paul.   
//Date			Thu 12 Sep 1996
//
//Description	Turns down the detail level by one step
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::DecDetailLevel()
{
//		gridOffs.reInit();

	if (Save_Data.contourDetail==4)								Save_Data.contourDetail--;
	else if (Save_Data.contourDetail==3)						Save_Data.contourDetail--;
	else if (Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES])		Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
	else if (Save_Data.detail_3d[DETAIL3D_HORIZONDIST])			{ Save_Data.detail_3d%=DETAIL3D_HORIZONDIST; UpdateCloseHorizCornerPoints( gridOffs.hx, gridOffs.hz ); } // never gets swithced back on mind...
	else if (Save_Data.detail_3d[DETAIL3D_ROUTES])				Save_Data.detail_3d%=DETAIL3D_ROUTES;
	else if (Save_Data.contourDetail==2)						Save_Data.contourDetail--;
	else if (Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS])	Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
	else if (Save_Data.contourDetail==1)						Save_Data.contourDetail--;
	else if (Save_Data.detail_3d[DETAIL3D_AIRCRAFTSHADOWS])		Save_Data.detail_3d%=DETAIL3D_AIRCRAFTSHADOWS;
//DeadCode JON 22Sep00 	else if (Save_Data.detail_3d[DETAIL3D_ITEMSHADING])			Save_Data.detail_3d%=DETAIL3D_ITEMSHADING;
	else if (Save_Data.itemShading)								
	{
		Save_Data.itemShading--;
		// set the master lightshading
		LIGHTFLAG lf = LIGHTFLAG( LF_AMBIENT+Save_Data.itemShading );
		g_lpLib3d->SetMasterShading( lf );
	}
	else if (Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])			Save_Data.detail_3d%=DETAIL3D_ITEMSHADOWS;
	else if (Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])		Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;

//DeadCode JON 3Aug00 	if (Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES])		Save_Data.cockpit3Ddetail%=COCK3D_SKYIMAGES;
//DeadCode JON 3Aug00 	else if (Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS])Save_Data.detail_3d%=DETAIL3D_INCONSEQUENTIALS;
//DeadCode JON 3Aug00 	else if (Save_Data.detail_3d[DETAIL3D_AIRCRAFTSHADOWS])	Save_Data.detail_3d%=DETAIL3D_AIRCRAFTSHADOWS;
//DeadCode JON 3Aug00 	else if (!Save_Data.detail_3d[DETAIL3D_HORIZONFADE])	Save_Data.detail_3d|=DETAIL3D_HORIZONFADE;
//DeadCode JON 3Aug00 	else if (Save_Data.detail_3d[DETAIL3D_ITEMSHADING])		Save_Data.detail_3d%=DETAIL3D_ITEMSHADING;
//DeadCode JON 3Aug00 	else if (Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])		Save_Data.detail_3d%=DETAIL3D_ITEMSHADOWS;
//DeadCode JON 3Aug00 	else if (Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])	Save_Data.detail_3d%=DETAIL3D_GROUNDSHADING;
//DeadCode JON 3Aug00 	else if (Save_Data.detail_3d[DETAIL3D_ROUTES])			Save_Data.detail_3d%=DETAIL3D_ROUTES;
//DeadCode JON 3Aug00 	else if (Save_Data.detail_3d[DETAIL3D_CONTOURDETAIL])	Save_Data.detail_3d%=DETAIL3D_CONTOURDETAIL;

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IncDetailLevel
//Author		Paul.   
//Date			Thu 12 Sep 1996
//
//Description	Turns up the detail level by one step
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void LandScape::IncDetailLevel()
{ // note opposite order to dec detail level..

	if (Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])			Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
	else if (Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])			Save_Data.detail_3d|=DETAIL3D_ITEMSHADOWS;
//DeadCode JON 22Sep00 	else if (Save_Data.detail_3d[DETAIL3D_ITEMSHADING])			Save_Data.detail_3d|=DETAIL3D_ITEMSHADING;
	else if (Save_Data.itemShading<2)							
	{
		Save_Data.itemShading++;
		// set the master lightshading
		LIGHTFLAG lf = LIGHTFLAG( LF_AMBIENT+Save_Data.itemShading );
		g_lpLib3d->SetMasterShading( lf );
	}
	else if (Save_Data.detail_3d[DETAIL3D_AIRCRAFTSHADOWS])		Save_Data.detail_3d|=DETAIL3D_AIRCRAFTSHADOWS;
	else if (Save_Data.contourDetail==0)						Save_Data.contourDetail++;
	else if (Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS])	Save_Data.detail_3d|=DETAIL3D_INCONSEQUENTIALS;
	else if (Save_Data.contourDetail==1)						Save_Data.contourDetail++;
	else if (Save_Data.detail_3d[DETAIL3D_ROUTES])				Save_Data.detail_3d|=DETAIL3D_ROUTES;
	else if (Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES])		Save_Data.cockpit3Ddetail|=COCK3D_SKYIMAGES;
	else if (Save_Data.contourDetail==2)						Save_Data.contourDetail++;
	else if (Save_Data.contourDetail==3)						Save_Data.contourDetail++;
	

//DeadCode JON 3Aug00 	if (!Save_Data.detail_3d[DETAIL3D_CONTOURDETAIL])		Save_Data.detail_3d|=DETAIL3D_CONTOURDETAIL;
//DeadCode JON 3Aug00 	else if (!Save_Data.detail_3d[DETAIL3D_ROUTES])			Save_Data.detail_3d|=DETAIL3D_ROUTES;
//DeadCode JON 3Aug00 	else if (!Save_Data.detail_3d[DETAIL3D_GROUNDSHADING])	Save_Data.detail_3d|=DETAIL3D_GROUNDSHADING;
//DeadCode JON 3Aug00 	else if (!Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])	Save_Data.detail_3d|=DETAIL3D_ITEMSHADOWS;
//DeadCode JON 3Aug00 	else if (!Save_Data.detail_3d[DETAIL3D_ITEMSHADING])	Save_Data.detail_3d|=DETAIL3D_ITEMSHADING;
//DeadCode JON 3Aug00 	else if (Save_Data.detail_3d[DETAIL3D_HORIZONFADE])		Save_Data.detail_3d%=DETAIL3D_HORIZONFADE;
//DeadCode JON 3Aug00 	else if (!Save_Data.detail_3d[DETAIL3D_AIRCRAFTSHADOWS])Save_Data.detail_3d|=DETAIL3D_AIRCRAFTSHADOWS;
//DeadCode JON 3Aug00 	else if (!Save_Data.detail_3d[DETAIL3D_INCONSEQUENTIALS])Save_Data.detail_3d|=DETAIL3D_INCONSEQUENTIALS;
//DeadCode JON 3Aug00 	else if (!Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES])	Save_Data.cockpit3Ddetail|=COCK3D_SKYIMAGES;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LandScape
//Author		Paul.   
//Date			Mon 6 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
LandScape::~LandScape()
{
	delete []SideLookUp;											
	delete []smkList;											//RJS 23May00
	smkList = NULL;

	CloudAnimP.Delete();
}

////////////////////////////////////////////////////////////////////////////////
//
//							HORIZON ROUTINES
//
////////////////////////////////////////////////////////////////////////////////

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoRain
//Author		Robert Slater
//Date			Thu 16 Apr 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//deadcode JON 19/06/01	void	LandScape::DoRain(ViewPoint	*vp,SLong	gheight)
//deadcode JON 19/06/01	{
//deadcode JON 19/06/01	
//deadcode JON 19/06/01	
//deadcode JON 19/06/01		// if it is raining and below cloud layer....
//DEADCODE RDH 5/19/00 	if (Save_Data.gamedifficulty[GD_WEATHEREFFECTS] &&
//DEADCODE RDH 5/19/00 		Manual_Pilot.ControlledAC2 &&
//DEADCODE RDH 5/19/00 		MissManCampSky().Conditions==1)			//raining!
//DEADCODE RDH 5/19/00 	{
//DEADCODE RDH 5/19/00 		int			i;
//DEADCODE RDH 5/19/00 		SWord		XSeed;
//DEADCODE RDH 5/19/00 		SWord		YSeed;
//DEADCODE RDH 5/19/00 		SWord		ZSeed;
//DEADCODE RDH 5/19/00 		DoPointStruc dp0,dp1;
//DEADCODE RDH 5/19/00 		LINETYPE	ltLine;
//DEADCODE RDH 5/19/00 		struct		vertex	startVertex,endVertex;
//DEADCODE RDH 5/19/00 		Float		z0,z1;
//DEADCODE RDH 5/19/00 		FPMATRIX		nmat;
//DEADCODE RDH 5/19/00 		FPMATRIX_PTR	nmatp = &nmat;
//DEADCODE RDH 5/19/00 		ANGLES			hdg, pitch, roll;
//DEADCODE RDH 5/19/00 //DEADCODE CSB 08/11/99 		SLong			theVel = Manual_Pilot.ControlledAC2->velhori;
//DEADCODE RDH 5/19/00 		SLong			theVel = Manual_Pilot.ControlledAC2->vel_; //CSB 08/11/99
//DEADCODE RDH 5/19/00 		SWord			RainHeight = 5;
//DEADCODE RDH 5/19/00 		SLong			distfromground = gheight;	//vp->World.Y - gheight;
//DEADCODE RDH 5/19/00 		SLong			theVol;
//DEADCODE RDH 5/19/00 		UWord			andedFlags;
//DEADCODE RDH 5/19/00 		Bool			inCockpit = FALSE;
//DEADCODE RDH 5/19/00 		Bool			drawit;
//DEADCODE RDH 5/19/00 		Colour			base_colour = (Colour)24;				//RJS 03Jun99
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 		if (vp->PolyPitEnabled())
//DEADCODE RDH 5/19/00 			inCockpit = TRUE;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 		if (theVel >= 1000)
//DEADCODE RDH 5/19/00 			theVel = ANGLES_90Deg;
//DEADCODE RDH 5/19/00 		else
//DEADCODE RDH 5/19/00 			theVel = (theVel * ANGLES_90Deg)/1000;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 		hdg = Manual_Pilot.ControlledAC2->hdg;
//DEADCODE RDH 5/19/00 		pitch = (Angles) -theVel;
//DEADCODE RDH 5/19/00 		roll = ANGLES_0Deg;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 		g_lpLib3d->PushMatrix(MATRIX_OBJECT);
//DEADCODE RDH 5/19/00 		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_ROLL,(Angles)(int)roll);
//DEADCODE RDH 5/19/00 		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_PITCH,(Angles)(int)pitch);
//DEADCODE RDH 5/19/00 		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_HEADING,(Angles)(int)hdg);
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 		theVol = 128 - ((distfromground * 128)/10000);
//DEADCODE RDH 5/19/00 //		if (theVol > 0)
//DEADCODE RDH 5/19/00 //			_Miles.PlayLooped(FIL_SFX_RAIN_LOOP,NULL,theVol);
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 		if (Three_Dee.IsPaused())
//DEADCODE RDH 5/19/00 		{
//DEADCODE RDH 5/19/00 			for (i=0; i < 96; i++)
//DEADCODE RDH 5/19/00 			{
//DEADCODE RDH 5/19/00 				XSeed = (SByte) SHAPE.Noise(vp->World.X+i,vp->World.Y+i,vp->World.Z+i);
//DEADCODE RDH 5/19/00 				YSeed = (SByte) SHAPE.Noise(XSeed+i,vp->World.Y+i,vp->World.Z+i);
//DEADCODE RDH 5/19/00 				ZSeed = (SByte) SHAPE.Noise(vp->World.X+i,YSeed+i,vp->World.Z+i);
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 				XSeed <<= 4;
//DEADCODE RDH 5/19/00 				YSeed <<= 4;
//DEADCODE RDH 5/19/00 				ZSeed <<= 4;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 				drawit = TRUE;
//DEADCODE RDH 5/19/00 				if (inCockpit)
//DEADCODE RDH 5/19/00 				{
//DEADCODE RDH 5/19/00 					if (	((XSeed > -800) && (XSeed < 800))
//DEADCODE RDH 5/19/00 						&&	((YSeed > -800) && (YSeed < 800))
//DEADCODE RDH 5/19/00 						&&	((ZSeed > -800) && (ZSeed < 800))	)
//DEADCODE RDH 5/19/00 						drawit = FALSE;
//DEADCODE RDH 5/19/00 				}
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 				if (drawit)
//DEADCODE RDH 5/19/00 				{
//DEADCODE RDH 5/19/00 					dp0.bodyx.f = XSeed;
//DEADCODE RDH 5/19/00 					dp0.bodyy.f = YSeed;
//DEADCODE RDH 5/19/00 					dp0.bodyz.f = ZSeed;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 					dp1.bodyx.f = XSeed;
//DEADCODE RDH 5/19/00 					dp1.bodyy.f = YSeed + RainHeight;
//DEADCODE RDH 5/19/00 					dp1.bodyz.f = ZSeed;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 //deadcode					if (andedFlags == 0 && dp0.bodyz.f>5*100 && dp1.bodyz.f>5*100)
//DEADCODE RDH 5/19/00 //deadcode					{
//DEADCODE RDH 5/19/00 						g_lpLib3d->DrawLine(HMATERIAL(base_colour),dp0,dp1);
//DEADCODE RDH 5/19/00 //deadcode					}
//DEADCODE RDH 5/19/00 				}
//DEADCODE RDH 5/19/00 			}
//DEADCODE RDH 5/19/00 		}
//DEADCODE RDH 5/19/00 		else
//DEADCODE RDH 5/19/00 		{
//DEADCODE RDH 5/19/00 			RainHeight = 40;
//DEADCODE RDH 5/19/00 			for (i=0; i < 96; i++)
//DEADCODE RDH 5/19/00 			{
//DEADCODE RDH 5/19/00 				XSeed = Math_Lib.rnd();
//DEADCODE RDH 5/19/00 				YSeed = Math_Lib.rnd();
//DEADCODE RDH 5/19/00 				ZSeed = Math_Lib.rnd();
//DEADCODE RDH 5/19/00 	
//DEADCODE RDH 5/19/00 				XSeed >>= 4;
//DEADCODE RDH 5/19/00 				YSeed >>= 4;
//DEADCODE RDH 5/19/00 				ZSeed >>= 4;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 				drawit = TRUE;
//DEADCODE RDH 5/19/00 				if (inCockpit)
//DEADCODE RDH 5/19/00 				{
//DEADCODE RDH 5/19/00 					if (	((XSeed > -600) && (XSeed < 600))
//DEADCODE RDH 5/19/00 						&&	((YSeed > -400) && (YSeed < 400))
//DEADCODE RDH 5/19/00 						&&	((ZSeed > -600) && (ZSeed < 600))	)
//DEADCODE RDH 5/19/00 						drawit = FALSE;
//DEADCODE RDH 5/19/00 				}
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 				if (drawit)
//DEADCODE RDH 5/19/00 				{
//DEADCODE RDH 5/19/00 					dp0.bodyx.f = XSeed;
//DEADCODE RDH 5/19/00 					dp0.bodyy.f = YSeed;
//DEADCODE RDH 5/19/00 					dp0.bodyz.f = ZSeed;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 					dp1.bodyx.f = XSeed;
//DEADCODE RDH 5/19/00 					dp1.bodyy.f = YSeed + RainHeight;
//DEADCODE RDH 5/19/00 					dp1.bodyz.f = ZSeed;
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 //deadcode					if (andedFlags == 0 && dp0.bodyz.f>5*100 && dp1.bodyz.f>5*100)
//DEADCODE RDH 5/19/00 //deadcode					{
//DEADCODE RDH 5/19/00 
//DEADCODE RDH 5/19/00 						g_lpLib3d->DrawLine(HMATERIAL(base_colour),dp0,dp1);
//DEADCODE RDH 5/19/00 //deadcode					}
//DEADCODE RDH 5/19/00 				}
//DEADCODE RDH 5/19/00 			}
//DEADCODE RDH 5/19/00 		}
//DEADCODE RDH 5/19/00 		g_lpLib3d->PopMatrix(MATRIX_OBJECT);
//DEADCODE RDH 5/19/00 	}
//deadcode JON 19/06/01	}
static UByte scaledToCeil=0;
static int hStep;

#include "hdata2.h"

inline void fpTan(ANGLES ang,Float& tanAng)
{
	int iang=ang;
	_asm
	{
	mov eax,iang;
	mov edx,tanAng;
	and eax,0x0000FFFF;
	fldpi;
	push eax;
	fild dword ptr ss:[esp];
	fmulp st(1),st;
	mov dword ptr ss:[esp],32768;
	fild dword ptr ss:[esp];
	fdivp st(1),st;
	fsincos;
	fdivp st(1),st;
	fstp qword ptr ds:[edx];
	add esp,4;
	}
}

//DEADCODE JON 5/24/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JON 5/24/00 //Procedure		GStrip
//DEADCODE JON 5/24/00 //Author		Paul.   
//DEADCODE JON 5/24/00 //Date			Tue 19 Jan 1999
//DEADCODE JON 5/24/00 //------------------------------------------------------------------------------
//DEADCODE JON 5/24/00 void LandScape::GStrip(	DoPointStruc** pp,
//DEADCODE JON 5/24/00 						UByte br,UByte bg,UByte bb,
//DEADCODE JON 5/24/00 						UByte tr,UByte tg,UByte tb)
//DEADCODE JON 5/24/00 {
//DEADCODE JON 5/24/00 //deadcode	if (!(	pp[0]->clipFlags&
//DEADCODE JON 5/24/00 //deadcode			pp[1]->clipFlags&
//DEADCODE JON 5/24/00 //deadcode			pp[2]->clipFlags&
//DEADCODE JON 5/24/00 //deadcode			pp[3]->clipFlags))
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		R3DVERTEX *pRVerts;
//DEADCODE JON 5/24/00 		g_lpLib3d->BeginPoly(HMATERIAL(UByte(0)),4,pRVerts);
//DEADCODE JON 5/24/00 		*pRVerts++=*pp[3];
//DEADCODE JON 5/24/00 		*pRVerts++=*pp[0];
//DEADCODE JON 5/24/00 		*pRVerts++=*pp[1];
//DEADCODE JON 5/24/00 		*pRVerts++=*pp[2];
//DEADCODE JON 5/24/00 		g_lpLib3d->EndPoly();
//DEADCODE JON 5/24/00 //deadcode		POLYGON.createpoly(POLYTYPE::PT_GColour);
//DEADCODE JON 5/24/00 //deadcode		POLYGON.createvert(*pp[3],br,bg,bb,0xFF);
//DEADCODE JON 5/24/00 //deadcode		POLYGON.createvert(*pp[0],br,bg,bb,0xFF);
//DEADCODE JON 5/24/00 //deadcode		POLYGON.createvert(*pp[1],tr,tg,tb,0xFF);
//DEADCODE JON 5/24/00 //deadcode		POLYGON.createvert(*pp[2],tr,tg,tb,0xFF);
//DEADCODE JON 5/24/00 //deadcode		POLYGON.drawpoly();
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateStrip
//Author		Paul.   
//Date			Tue 23 Mar 1999
//------------------------------------------------------------------------------
void LandScape::InfiniteStrip( const ANGLES pitch, const ANGLES roll)
{

#ifdef _NO_INFI_STRIP
	return;
#endif
//DeadCode JON 2Nov00 	SLong layerAltitude =	(MissManCampSky().Layer[0].AltBase + MissManCampSky().Layer[0].AltTop)>>1;

	const SLong layerAltitudeTop = MissManCampSky().Layer[0].AltTop;
	const SLong layerAltitudeBottom = MissManCampSky().Layer[0].AltBase;
//	SLong layerAltitude = MissManCampSky().Layer[0].AltTop;

//DeadCode JON 2Nov00 	const double cloud_height=double(layerAltitude)/double(CEILING_ALT);
	const double cloud_height_top=double(layerAltitudeTop)/double(CEILING_ALT);
	const double cloud_height_bottom=double(layerAltitudeBottom)/double(CEILING_ALT);
	const double BELOW_GROUND=-1.0;//00.0;///double(CEILING_ALT);

	double fvy=double(viewer_y)/double(CEILING_ALT);
//DeadCode JON 20Oct00 	double fvy2=fvy*fvy;

	DoPointStruc* ptr=Shape.newco;

	double fvr=double(view_dist*0.999999);
//DeadCode JON 5Oct00 	{
//DeadCode JON 5Oct00 		D3DVECTOR scaleVec={fvr,fvr,0.f};
//DeadCode JON 5Oct00 		D3DVECTOR trnsVec={0,0,fvr};
//DeadCode JON 5Oct00 
//DeadCode JON 5Oct00 		g_lpLib3d->PushMatrix(MATRIX_OBJECT);
//DeadCode JON 5Oct00 		g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
//DeadCode JON 5Oct00 
//DeadCode JON 5Oct00 		g_lpLib3d->PushMatrix(MATRIX_VIEWER);
//DeadCode JON 5Oct00 		g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
//DeadCode JON 5Oct00 		g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
//DeadCode JON 5Oct00 		g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);
//DeadCode JON 5Oct00 		g_lpLib3d->Scale(MATRIX_VIEWER,scaleVec);
//DeadCode JON 5Oct00 		g_lpLib3d->Translate(MATRIX_VIEWER,trnsVec);
//DeadCode JON 5Oct00 		trnsVec.y=-fvy;
//DeadCode JON 5Oct00 		trnsVec.z=0;
//DeadCode JON 5Oct00 		g_lpLib3d->Translate(MATRIX_OBJECT,trnsVec);
//DeadCode JON 5Oct00 		g_lpLib3d->EnableFogging( false );
//DeadCode JON 5Oct00 	}

	LIGHTFLAG lf = LF_VERTEX;
	g_lpLib3d->SetObjectLighting( lf );

	const D3DVALUE LAND_Z = 1.0f;
	const D3DVALUE SKY_Z = 1.0f;

	SLong over_sun_count;												//JON 5Oct00

	// right - try to do directional sky lighting...
	LightVec& sunPos=Three_Dee.SunLightVector;
	double viewx, viewy;
	viewx = Three_Dee.eye_x;
	viewy = Three_Dee.eye_z;
	
	double sunx, suny;
	suny = fastMath.FastInvSqrt( double(sunPos.ni.i)*double(sunPos.ni.i) + double(sunPos.nk.i)*double(sunPos.nk.i) );
	sunx = sunPos.ni.i * suny;
	suny *= sunPos.nk.i;

	double sunProportion = (1.0 - (sunx*viewx + suny*viewy) )*0.5;

	R3DCOLOUR skyBase; // always used
	skyBase= (currentLighting.otherSkyColSun.red()<<16)+(currentLighting.otherSkyColSun.green()<<8)+currentLighting.otherSkyColSun.blue();
	R3DCOLOUR skyBaseShade;
	skyBaseShade= (currentLighting.otherSkyColShade.red()<<16)+(currentLighting.otherSkyColShade.green()<<8)+currentLighting.otherSkyColShade.blue();

	skyBase.interpRGB( skyBaseShade, sunProportion );

	R3DCOLOUR fogCol;
	fogCol = ( (currentLighting.fogColSun.red()<<16)+(currentLighting.fogColSun.green()<<8)+currentLighting.fogColSun.blue() );
	R3DCOLOUR fogColShade;
	fogColShade = ( (currentLighting.fogColShade.red()<<16)+(currentLighting.fogColShade.green()<<8)+currentLighting.fogColShade.blue() );
	fogCol.interpRGB( fogColShade, sunProportion );

	Three_Dee.fogCol=fogCol.all;


	g_lpLib3d->SetFogColour(fogCol.all );
	g_lpLib3d->Wipe( fogCol.all );

	double toTopY;
	if ( layerAltitudeBottom <= 0  || viewer_y<layerAltitudeBottom )
	{ // view below cloud layer
		// draw in 3 bands: 
		//- cloud level up go skycol -> deeper skycol
		//- from eyelevel to cloud level fog->white
		//- from ground level to eyelevel all in fogcolour

		R3DCOLOUR grHorizCol;
		grHorizCol = ( (currentLighting.horizonColSun.red()<<16)+(currentLighting.horizonColSun.green()<<8)+currentLighting.horizonColSun.blue() );
		R3DCOLOUR grHorizColShade;
		grHorizColShade = ( (currentLighting.horizonColShade.red()<<16)+(currentLighting.horizonColShade.green()<<8)+currentLighting.horizonColShade.blue() );

		grHorizCol.interpRGB( grHorizColShade, sunProportion );

		R3DCOLOUR midCol;
//DeadCode JON 2Nov00 		midCol =	(((currentLighting.fogColSun.red() + currentLighting.horizonColSun.red())&~1)<<15) +
//DeadCode JON 2Nov00 						(((currentLighting.fogColSun.green() + currentLighting.horizonColSun.green())&~1)<<7) +
//DeadCode JON 2Nov00 						((currentLighting.fogColSun.blue() + currentLighting.horizonColSun.blue())>>1);
//DeadCode JON 2Nov00 		R3DCOLOUR midColShade;
//DeadCode JON 2Nov00 		midColShade =	(((currentLighting.fogColShade.red() + currentLighting.horizonColShade.red())&~1)<<15) +
//DeadCode JON 2Nov00 						(((currentLighting.fogColShade.green() + currentLighting.horizonColShade.green())&~1)<<7) +
//DeadCode JON 2Nov00 						((currentLighting.fogColShade.blue() + currentLighting.horizonColShade.blue())>>1);
//DeadCode JON 2Nov00 		midCol.interpRGB( midColShade, sunProportion );

		midCol = grHorizCol;
		midCol.interpRGB( fogCol, 0.5 );


		R3DCOLOUR cloudCol;
		cloudCol= (currentLighting.cloudColSun.red()<<16)+(currentLighting.cloudColSun.green()<<8)+currentLighting.cloudColSun.blue();
		R3DCOLOUR cloudColShade;
		cloudColShade= (currentLighting.cloudColShade.red()<<16)+(currentLighting.cloudColShade.green()<<8)+currentLighting.cloudColShade.blue();

		cloudCol.interpRGB( cloudColShade, sunProportion );

		//- 0  Draw in a patch below horizon to cover any possible tears
		ptr->setPosition( -1.f, BELOW_GROUND/*-0.4f*/, LAND_Z );
		ptr->setVertexCol( fogCol );
		ptr++;
		ptr->setPosition( 1.f, BELOW_GROUND/*-0.4f*/, LAND_Z );
		ptr->setVertexCol( fogCol );
		ptr++;

		//- 1 generate vertices 4 ground level 
		ptr->setPosition( -1.f, -0.f, LAND_Z );
		ptr->setVertexCol( fogCol );
		ptr++;

		ptr->setPosition( 1.f, -0.f, LAND_Z );
		ptr->setVertexCol( fogCol );
		ptr++;


//- 2 generate vertices 4 half way horizon / eye level.
		ptr->setPosition( -1.f, fvy*0.5f, LAND_Z );
		ptr->setVertexCol( midCol );
		ptr++;

		ptr->setPosition( 1.f, fvy*0.5f, LAND_Z );
		ptr->setVertexCol( midCol );
		ptr++;

//TempCode JON 2Nov00 //- 2 generate vertices 4 just below horizon / eye level.
//TempCode JON 2Nov00 		ptr->setPosition( -1.f, fvy*0.99f, LAND_Z );
//TempCode JON 2Nov00 		ptr->setVertexCol( midCol );
//TempCode JON 2Nov00 		ptr++;
//TempCode JON 2Nov00 
//TempCode JON 2Nov00 		ptr->setPosition( 1.f, fvy*0.99f, LAND_Z );
//TempCode JON 2Nov00 		ptr->setVertexCol( midCol );
//TempCode JON 2Nov00 		ptr++;

		//- 2 generate vertices 4 on horizon / eye level.
		ptr->setPosition( -1.f, fvy*0.95f, LAND_Z );
		ptr->setVertexCol( grHorizCol );
		ptr++;

		ptr->setPosition( 1.f, fvy*0.95f, LAND_Z );
		ptr->setVertexCol( grHorizCol );
		ptr++;

		over_sun_count=(SLong(ptr-SHAPE.newco))>>1;

		if (layerAltitudeBottom > 0)
		{	
			// now go to white for the clouds
			ptr->setPosition( -1.f, cloud_height_bottom, SKY_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;
	
			ptr->setPosition( 1.f, cloud_height_bottom, SKY_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;

			// fill the cloud layer
			ptr->setPosition( -1.f, cloud_height_top, SKY_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;
	
			ptr->setPosition( 1.f, cloud_height_top, SKY_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;
		
			// now go back up to blue 4 the sky
			ptr->setPosition( -1.f, cloud_height_top*1.05f, SKY_Z );
			ptr->setVertexCol( skyBase );
			ptr++;

			ptr->setPosition( 1.f, cloud_height_top*1.05f, SKY_Z );
			ptr->setVertexCol( skyBase );
			ptr++;

			toTopY = cloud_height_top*1.05;
		} else
		{
			// now go back up to blue 4 the sky
			ptr->setPosition( -1.f, fvy*1.05f, SKY_Z );
			ptr->setVertexCol( skyBase );
			ptr++;

			ptr->setPosition( 1.f, fvy*1.05f, SKY_Z );
			ptr->setVertexCol( skyBase );
			ptr++;

			toTopY = fvy*1.05;
		}

	} else 
	{ // view above cloud layer
		// draw in 3 bands: 
		//- cloud level up go skycol -> deeper skycol
		//- from ground level to cloudlevl groundfogcol->white

		R3DCOLOUR cloudCol;
		cloudCol= (currentLighting.cloudColSun.red()<<16)+(currentLighting.cloudColSun.green()<<8)+currentLighting.cloudColSun.blue();
		R3DCOLOUR cloudColShade;
		cloudColShade= (currentLighting.cloudColShade.red()<<16)+(currentLighting.cloudColShade.green()<<8)+currentLighting.cloudColShade.blue();

		cloudCol.interpRGB( cloudColShade, sunProportion );
				
		//- 0  Draw in a patch below horizon to cover any possible tears
		ptr->setPosition( -1.f, BELOW_GROUND, LAND_Z );
		ptr->setVertexCol( fogCol );
		ptr++;

		ptr->setPosition( 1.f, BELOW_GROUND, LAND_Z );
		ptr->setVertexCol( fogCol );
		ptr++;

		//- 1 generate vertices 4 ground level 
		ptr->setPosition( -1.f, 0.f, LAND_Z );
		ptr->setVertexCol( fogCol );
		ptr++;

		ptr->setPosition( 1.f, 0.f, LAND_Z );
		ptr->setVertexCol( fogCol );
		ptr++;

		if ( viewer_y<layerAltitudeTop )
		{ // we're inside the cloudlayer 

			// now go to white for the clouds
			ptr->setPosition( -1.f, cloud_height_bottom, SKY_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;
	
			ptr->setPosition( 1.f, cloud_height_bottom, SKY_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;

			// fill the cloud layer
			ptr->setPosition( -1.f, cloud_height_top, SKY_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;
	
			ptr->setPosition( 1.f, cloud_height_top, SKY_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;
		
			// now go back up to blue 4 the sky
			ptr->setPosition( -1.f, cloud_height_top*1.05f, SKY_Z );
			ptr->setVertexCol( skyBase );
			ptr++;

			ptr->setPosition( 1.f, cloud_height_top*1.05f, SKY_Z );
			ptr->setVertexCol( skyBase );
			ptr++;

			toTopY = cloud_height_top*1.05;

		} else
		{
		
			// now go to fog col??? for the clouds
			ptr->setPosition( -1.f, cloud_height_top, LAND_Z );
			ptr->setVertexCol( fogCol );
			ptr++;

			ptr->setPosition( 1.f, cloud_height_top, LAND_Z );
			ptr->setVertexCol( fogCol );
			ptr++;

			//- generate vertices 4 on horizon / eye level.
			ptr->setPosition( -1.f, fvy*0.95f, LAND_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;

			ptr->setPosition( 1.f, fvy*0.95f, LAND_Z );
			ptr->setVertexCol( cloudCol );
			ptr++;

			// now go back up to blue 4 the sky
			ptr->setPosition( -1.f, fvy*1.05f, LAND_Z );
			ptr->setVertexCol( skyBase );
			ptr++;

			ptr->setPosition( 1.f, fvy*1.05f, LAND_Z );
			ptr->setVertexCol( skyBase );
			ptr++;

			toTopY = fvy*1.05;
		}

		over_sun_count=(SLong(ptr-SHAPE.newco))>>1;

	}
	int i;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 /* 	Generate vertex data for
//DEADCODE JON 4/18/00  *	infinite strip along the
//DEADCODE JON 4/18/00  *	ground
//DEADCODE JON 4/18/00  */

//DEADCODE JON 4/20/00 	ULong col = 0xFF;
//DEADCODE JON 4/20/00 	ULong rgCol = 0xAAAA00;
//DEADCODE JON 4/20/00 //TEMPCODE JON 4/18/00 	ULong rgStep = 0x0A0A00;
//DEADCODE JON 4/20/00 	ULong rgStep = 0x0F0F00;

//DEADCODE JON 4/18/00 	
//DEADCODE JON 4/18/00 	for (int i=0;i<SubDivideLevel+1;i++) 
//DEADCODE JON 4/18/00 	{
//DEADCODE JON 4/18/00 		R3DVALUE this_range=R3DVALUE(i)*Max_Range/4.;
//DEADCODE JON 4/18/00 		this_range=this_range*this_range-fvy2;
//DEADCODE JON 4/18/00 		if (this_range<0.f) this_range=0.f;
//DEADCODE JON 4/18/00 		else
//DEADCODE JON 4/18/00 		{
//DEADCODE JON 4/18/00 			this_range=fastMath.FastSqrt(this_range);
//DEADCODE JON 4/18/00 			this_range=fvy*(this_range-1.f)/this_range;
//DEADCODE JON 4/18/00 		}
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		if (this_range>cloud_height)
//DEADCODE JON 4/18/00 			break;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		ptr->bodyx.f=-1.f;
//DEADCODE JON 4/18/00 		ptr->bodyy.f=this_range;
//DEADCODE JON 4/18/00 		ptr->bodyz.f=1.f;
//DEADCODE JON 4/18/00 		ptr->vertexCol=0x0090B8E8;//col+rgCol;
//DEADCODE JON 4/18/00 		ptr++;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		ptr->bodyx.f=1.f;	
//DEADCODE JON 4/18/00 		ptr->bodyy.f=this_range;
//DEADCODE JON 4/18/00 		ptr->bodyz.f=1.f;
//DEADCODE JON 4/18/00 		ptr->vertexCol=0x0090B8E8;//col+rgCol;
//DEADCODE JON 4/18/00 //TEMPCODE JON 4/18/00 		rgCol-=rgStep;
//DEADCODE JON 4/18/00 		ptr++;
//DEADCODE JON 4/18/00 	}
//DEADCODE JON 4/18/00 	rgCol-=rgStep;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 	// where is this one??
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 	for (i=1;i<SubDivideLevel+1;i++)
//DEADCODE JON 4/18/00 	{
//DEADCODE JON 4/18/00 		R3DVALUE this_range=R3DVALUE(i)*Max_Range/4.;
//DEADCODE JON 4/18/00 		this_range=this_range*this_range-fvy2;
//DEADCODE JON 4/18/00 		if (this_range<0.f) this_range=0.f;
//DEADCODE JON 4/18/00 		else
//DEADCODE JON 4/18/00 		{
//DEADCODE JON 4/18/00 			this_range=fastMath.FastSqrt(this_range);
//DEADCODE JON 4/18/00 			this_range=fvy*(this_range-1.f)/this_range;
//DEADCODE JON 4/18/00 		}
//DEADCODE JON 4/18/00 		if (this_range>cloud_height)
//DEADCODE JON 4/18/00 			break;
//DEADCODE JON 4/18/00 		ptr->bodyx.f=-1.f;
//DEADCODE JON 4/18/00 		ptr->bodyy.f=this_range;
//DEADCODE JON 4/18/00 		ptr->bodyz.f=1.f;
//DEADCODE JON 4/18/00 		ptr->vertexCol=0x00FF00;//col+rgCol;
//DEADCODE JON 4/18/00 		ptr++;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		ptr->bodyx.f=1.f;
//DEADCODE JON 4/18/00 		ptr->bodyy.f=this_range;
//DEADCODE JON 4/18/00 		ptr->bodyz.f=1.f;
//DEADCODE JON 4/18/00 		ptr->vertexCol=0x00FF00;//col+rgCol;
//DEADCODE JON 4/18/00 //TEMPCODE JON 4/18/00 		rgCol-=rgStep;
//DEADCODE JON 4/18/00 		ptr++;
//DEADCODE JON 4/18/00 	}
//DEADCODE JON 4/18/00 	rgCol-=rgStep;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 	double cvy=cloud_height-fvy;
//DEADCODE JON 4/18/00 	if (cvy<0) cvy=-cvy;
//DEADCODE JON 4/18/00 	fvy2=cvy*cvy;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 /* 	Generate vertex data for
//DEADCODE JON 4/18/00  *	infinite strip under the
//DEADCODE JON 4/18/00  *	cloud layer
//DEADCODE JON 4/18/00  */
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 	for (i=SubDivideLevel+1;--i>=0;)
//DEADCODE JON 4/18/00 	{
//DEADCODE JON 4/18/00 		R3DVALUE this_range=R3DVALUE(i)*Max_Range/4.;
//DEADCODE JON 4/18/00 		this_range=this_range*this_range-fvy2;
//DEADCODE JON 4/18/00 		if (this_range<0.f) this_range=0.f;
//DEADCODE JON 4/18/00 		else
//DEADCODE JON 4/18/00 		{
//DEADCODE JON 4/18/00 			this_range=fastMath.FastSqrt(this_range);
//DEADCODE JON 4/18/00 			this_range=cvy*(this_range-1.f)/this_range;
//DEADCODE JON 4/18/00 		}
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		this_range=cloud_height-this_range;
//DEADCODE JON 4/18/00 		if (this_range>cloud_height)
//DEADCODE JON 4/18/00 			this_range=cloud_height;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		ptr->bodyx.f=-1.f;
//DEADCODE JON 4/18/00 		ptr->bodyy.f=this_range;
//DEADCODE JON 4/18/00 		ptr->bodyz.f=1.f;
//DEADCODE JON 4/18/00 		ptr->vertexCol=0xFFFF00;//col+rgCol;
//DEADCODE JON 4/18/00 		ptr++;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		ptr->bodyx.f=1.f;
//DEADCODE JON 4/18/00 		ptr->bodyy.f=this_range;
//DEADCODE JON 4/18/00 		ptr->bodyz.f=1.f;
//DEADCODE JON 4/18/00 		ptr->vertexCol=0xFFFF00;//col+rgCol;
//DEADCODE JON 4/18/00 //TEMPCODE JON 4/18/00 		rgCol-=rgStep;
//DEADCODE JON 4/18/00 		ptr++;
//DEADCODE JON 4/18/00 	}
//DEADCODE JON 4/18/00 	rgCol-=rgStep;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 	fvy2=cvy*cvy;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 /* 	Generate vertex data for
//DEADCODE JON 4/18/00  *	infinite strip above the
//DEADCODE JON 4/18/00  *	cloud layer
//DEADCODE JON 4/18/00  */
//DEADCODE JON 4/18/00 	// actually do the stuff above the top layer
//DEADCODE JON 4/18/00 	for (i=0;i<SubDivideLevel+1;i++)
//DEADCODE JON 4/18/00 	{
//DEADCODE JON 4/18/00 		R3DVALUE this_range=R3DVALUE(i)*Max_Range/4.;
//DEADCODE JON 4/18/00 		this_range=this_range*this_range-fvy2;
//DEADCODE JON 4/18/00 		if (this_range<0.f) this_range=0.f;
//DEADCODE JON 4/18/00 		else
//DEADCODE JON 4/18/00 		{
//DEADCODE JON 4/18/00 			this_range=fastMath.FastSqrt(this_range);
//DEADCODE JON 4/18/00 			this_range=cvy*(this_range-1.f)/this_range;
//DEADCODE JON 4/18/00 		}
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		this_range=cloud_height+this_range;
//DEADCODE JON 4/18/00 		if (this_range<cloud_height) 
//DEADCODE JON 4/18/00 		{
//DEADCODE JON 4/18/00 			this_range=cloud_height;
//DEADCODE JON 4/18/00 		}
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		ptr->bodyx.f=-1.f;	
//DEADCODE JON 4/18/00 		ptr->bodyy.f=this_range;
//DEADCODE JON 4/18/00 		ptr->bodyz.f=1.f;
//DEADCODE JON 4/18/00 		ptr->vertexCol=0xFF00FF;//col+rgCol;
//DEADCODE JON 4/18/00 
//DEADCODE JON 4/18/00 		ptr++;
//DEADCODE JON 4/18/00 		ptr->bodyx.f=1.f;
//DEADCODE JON 4/18/00 		ptr->bodyy.f=this_range;
//DEADCODE JON 4/18/00 		ptr->bodyz.f=1.f;
//DEADCODE JON 4/18/00 		ptr->vertexCol=0xFF00FF;//col+rgCol;
//DEADCODE JON 4/18/00 //TEMPCODE JON 4/18/00 		rgCol-=rgStep;
//DEADCODE JON 4/18/00 		ptr++;
//DEADCODE JON 4/18/00 	}
//DEADCODE JON 4/18/00 	rgCol-=rgStep;
//DEADCODE JON 4/18/00 

	// draw in the top dome type bits...
//	const double totop_z[]={1.0,.75,.5,.25,0};
	const double totop_z[]={1.0, .9, .8, .7, .6, .5, .4, .3, .2, .1 ,0};
	const SLong steps=sizeof(totop_z)/sizeof(double);

//DeadCode JON 2Nov00 	const double fromtop_z[]={-.25,	-.5,	-.75,	-1.0,	-1.0,	-1.0};
//DeadCode JON 2Nov00 	const double fromtop_y[]={1.0,	1.0,	1.0,	0.9,	0.8,	0.7};
//DeadCode JON 2Nov00 	const SLong steps2=sizeof(fromtop_z)/sizeof(double);

	//	SLayerRGB	deepestSkyCol,otherSkyCol,cloudCol,horizonCol,fogCol;	//JON 4/20/00
	
//	ULong curCol = (currentLighting.otherSkyCol.red()<<16)+(currentLighting.otherSkyCol.green()<<8)+currentLighting.otherSkyCol.blue();;
//	ULong endCol = (currentLighting.deepestSkyCol.red()<<16)+(currentLighting.deepestSkyCol.green()<<8)+currentLighting.deepestSkyCol.blue();
//	ULong colStep = (endCol-curCol)/(steps+steps2);

//DeadCode JON 11Sep00 	SLong curR = currentLighting.otherSkyCol.red()<<16;
//DeadCode JON 11Sep00 	SLong curG = currentLighting.otherSkyCol.green()<<16;
//DeadCode JON 11Sep00 	SLong curB = currentLighting.otherSkyCol.blue()<<16;

	const int gradientSteps = 7;

	SLong curR = SLong(skyBase.red)<<16;
	SLong curG = SLong(skyBase.green)<<16;
	SLong curB = SLong(skyBase.blue)<<16;


	R3DCOLOUR deepestSkyCol;
	deepestSkyCol.red = currentLighting.deepestSkyCol.red();
	deepestSkyCol.green = currentLighting.deepestSkyCol.green();
	deepestSkyCol.blue = currentLighting.deepestSkyCol.blue();
	deepestSkyCol.interpRGB( skyBase, 0.5 );

	SLong endR = SLong(deepestSkyCol.red)<<16;
	SLong endG = SLong(deepestSkyCol.green)<<16;
	SLong endB = SLong(deepestSkyCol.blue)<<16;

	SLong stepR = (endR-curR)/(gradientSteps+1);
	SLong stepG = (endG-curG)/(gradientSteps+1);
	SLong stepB = (endB-curB)/(gradientSteps+1);

	curR+=stepR;
	curG+=stepG;
	curB+=stepB;

	double topYinc = (1.0-toTopY)/steps;

	for (i=0;i<gradientSteps;i++) // draws up to the back...
	{
		double this_z=totop_z[i];
		ptr->setPosition( -1.f, toTopY, this_z );
		ptr->setVertexCol( RGBMake(UByte(curR>>16),UByte(curG>>16),UByte(curB>>16)) );
		ptr++;

		ptr->setPosition( 1.f, toTopY, this_z );
		ptr->setVertexCol( (ptr-1)->getVertexCol() );

		curR+=stepR;
		curG+=stepG;
		curB+=stepB;
		ptr++;

		toTopY+=topYinc;
	}

	for (;i<steps;i++) // draws up to the back...
	{
		double this_z=totop_z[i];
		ptr->setPosition( -1.f, toTopY, this_z );
		ptr->setVertexCol( deepestSkyCol );
		ptr++;

		ptr->setPosition( 1.f, toTopY, this_z );
		ptr->setVertexCol( deepestSkyCol );

		ptr++;

		toTopY+=topYinc;
	}

	// now draw down to the other side...
	ptr->setPosition( -1.f, 0.7f, -1.0f );
	ptr->setVertexCol( deepestSkyCol );
	ptr++;

	ptr->setPosition( 1.f, 0.7f, -1.0f );
	ptr->setVertexCol( deepestSkyCol );

	ptr++;


//DeadCode JON 2Nov00 	for (i=0;i<steps2;i++) // draw across the top - sort of...
//DeadCode JON 2Nov00 	{
//DeadCode JON 2Nov00 		double this_z=fromtop_z[i];
//DeadCode JON 2Nov00 		double this_y=fromtop_y[i];
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		ptr->setPosition( -1.f, this_y, this_z );
//DeadCode JON 2Nov00 		ptr->setVertexCol( deepestSkyCol );
//DeadCode JON 2Nov00 		ptr++;
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		ptr->setPosition( 1.f, this_y, this_z );
//DeadCode JON 2Nov00 		ptr->setVertexCol( deepestSkyCol );
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		ptr++;
//DeadCode JON 2Nov00 	}


//DeadCode JON 2Nov00 	for (i=0;i<steps;i++) // draws up to the back...
//DeadCode JON 2Nov00 	{
//DeadCode JON 2Nov00 		double this_z=totop_z[i];
//DeadCode JON 2Nov00 //DeadCode JON 2Nov00 		double this_y=1.;
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyx.f=-1.f;	
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyy.f=this_y;	
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyz.f=this_z;	
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 //DEADCODE JON 4/20/00 		ptr->vertexCol=col+rgCol;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->vertexCol=RGBMake(UByte(curR>>16),UByte(curG>>16),UByte(curB>>16));
//DeadCode JON 2Nov00 		ptr->setPosition( -1.f, toTopY, this_z );
//DeadCode JON 2Nov00 //		if ( i < 7 )
//DeadCode JON 2Nov00 			ptr->setVertexCol( RGBMake(UByte(curR>>16),UByte(curG>>16),UByte(curB>>16)) );
//DeadCode JON 2Nov00 //		else
//DeadCode JON 2Nov00 //			ptr->setVertexCol( 0x00FF0000 );
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		ptr++;
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyx.f=1.f;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyy.f=this_y;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyz.f=this_z;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 //DEADCODE JON 4/20/00 		ptr->vertexCol=col+rgCol;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 //DEADCODE JON 4/20/00 		rgCol-=rgStep;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->vertexCol=(ptr-1)->vertexCol;
//DeadCode JON 2Nov00 		ptr->setPosition( 1.f, toTopY, this_z );
//DeadCode JON 2Nov00 		ptr->setVertexCol( (ptr-1)->getVertexCol() );
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		curR+=stepR;
//DeadCode JON 2Nov00 		curG+=stepG;
//DeadCode JON 2Nov00 		curB+=stepB;
//DeadCode JON 2Nov00 		ptr++;
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		toTopY+=topYinc;
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 	}
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 	for (i=0;i<steps2;i++) // draw across the top - sort of...
//DeadCode JON 2Nov00 	{
//DeadCode JON 2Nov00 		double this_z=fromtop_z[i];
//DeadCode JON 2Nov00 		double this_y=fromtop_y[i];
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyx.f=-1.f;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyy.f=this_y;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyz.f=this_z;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 //DEADCODE JON 4/20/00 		ptr->vertexCol=col+rgCol;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->vertexCol=RGBMake(UByte(curR>>16),UByte(curG>>16),UByte(curB>>16));
//DeadCode JON 2Nov00 		ptr->setPosition( -1.f, this_y, this_z );
//DeadCode JON 2Nov00 		ptr->setVertexCol( RGBMake(UByte(curR>>16),UByte(curG>>16),UByte(curB>>16)) );
//DeadCode JON 2Nov00 		ptr++;
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyx.f=1.f;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyy.f=this_y;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->bodyz.f=this_z;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 //DEADCODE JON 4/20/00 		ptr->vertexCol=col+rgCol;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 //DEADCODE JON 4/20/00  		rgCol-=rgStep;
//DeadCode JON 2Nov00 //DEADCODE JON 5/24/00 		ptr->vertexCol=(ptr-1)->vertexCol;
//DeadCode JON 2Nov00 		ptr->setPosition( 1.f, this_y, this_z );
//DeadCode JON 2Nov00 		ptr->setVertexCol( (ptr-1)->getVertexCol() );
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		curR+=stepR;
//DeadCode JON 2Nov00 		curG+=stepG;
//DeadCode JON 2Nov00 		curB+=stepB;
//DeadCode JON 2Nov00 		ptr++;
//DeadCode JON 2Nov00 	}

/*	Calculate the number of
 *	polygons required to
 *	render the horizon
 */

//DeadCode JON 5Oct00 	Float dummy;
//DeadCode JON 5Oct00 	Bool oldZState;

	const int fudge = 1;  //eh, why have I got thids in the wrong place???
	over_sun_count-= fudge;
	SLong behind_sun_count=((SLong(ptr-SHAPE.newco)-2)>>1) - over_sun_count;
	ptr=SHAPE.newco;

	{
		D3DVECTOR scaleVec={fvr,fvr,0.f};
		D3DVECTOR trnsVec={0,0,fvr};

		g_lpLib3d->PushMatrix(MATRIX_OBJECT);
		g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

		g_lpLib3d->PushMatrix(MATRIX_VIEWER);
		g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
		g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)pitch);
		g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)roll);
		g_lpLib3d->Scale(MATRIX_VIEWER,scaleVec);
		g_lpLib3d->Translate(MATRIX_VIEWER,trnsVec);
		g_lpLib3d->Scale(MATRIX_VIEWER, 0.05f );
		trnsVec.y=-fvy;
		trnsVec.z=0;
		g_lpLib3d->Translate(MATRIX_OBJECT,trnsVec);
		g_lpLib3d->EnableFogging( false );
	}
	
	for (i=0;i<over_sun_count;i++)
	{
		{
			Lib3DPoint* pRVerts = g_lpLib3d->BeginPoly(NULL_MATERIAL,4);
			*pRVerts++=ptr[1];
			*pRVerts++=ptr[0];
			*pRVerts++=ptr[2];
			*pRVerts++=ptr[3];
			g_lpLib3d->EndPoly();
		}
		ptr+=2;
	}

	g_lpLib3d->Scale(MATRIX_VIEWER, 20.0f );
	// make the two horiz points re-transform.
#ifndef _NO_VERTEX_SHARING_HDR
	ptr[0].info.setInvalidWorld();
	ptr[1].info.setInvalidWorld();
#endif

	for (i=0;i<behind_sun_count;i++)
	{
		{
			Lib3DPoint* pRVerts = g_lpLib3d->BeginPoly(NULL_MATERIAL,4);
			*pRVerts++=ptr[1];
			*pRVerts++=ptr[0];
			*pRVerts++=ptr[2];
			*pRVerts++=ptr[3];
			g_lpLib3d->EndPoly();
		}
		ptr+=2;
	}


/*	Generate values for fogging
 *	range variables
 */

//DEADCODE JON 2/1/00 	UByte 	fr=currentLighting.horizonBase.red(),
//DEADCODE JON 2/1/00 			fg=currentLighting.horizonBase.green(),
//DEADCODE JON 2/1/00 			fb=currentLighting.horizonBase.blue();

//deadcode	currscreen->DoGammaCorr(fr,fg,fb);
//deadcode	GreyPalette(&fr,&fg,&fb);
//deadcode	currscreen->DoSetHorizonColour(fr,fg,fb);
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 	SLong fogdist,fogbegin;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 //DEADCODE JON 2/1/00 	double frsq=double(viewer_y)*double(viewer_y)+double(view_range)*double(view_range);
//DEADCODE JON 4/19/00 	double frsq=double(viewer_y)*double(viewer_y)+double(_blockWidth*_horizonDist)*double(_blockWidth*_horizonDist);
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 	_asm{
//DEADCODE JON 4/19/00 	fld frsq;
//DEADCODE JON 4/19/00 	fsqrt;
//DEADCODE JON 4/19/00 	fstp frsq;
//DEADCODE JON 4/19/00 	}
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 	if (frsq>MissManCampSky().Visibility) frsq=MissManCampSky().Visibility;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 	fogdist=SLong(frsq);
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 	if (!Save_Data.detail_3d[DETAIL3D_HORIZONFADE])	fogbegin=fogdist>>1;
//DEADCODE JON 4/19/00 	else											fogbegin=fogdist-(fogdist>>3);
//DEADCODE JON 4/19/00 	groundFogBegin=fogbegin;
//DEADCODE JON 4/19/00 	groundFogEnd=fogdist;
//DEADCODE JON 4/19/00 	SetFogMode(fogbegin,fogdist);
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 	cloud_base=Cloud_Layer_Height=_cloudLayerHeight;

	g_lpLib3d->PopMatrix(MATRIX_VIEWER);

	// now draw in the sun...
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

//	sunPos: pos
//	SUNMAPNO: imagemap
//  0->63: coords
	DoPointStruc sunCenter;
	sunCenter.setPosition( sunPos.ni.i, sunPos.nj.i, sunPos.nk.i );

	// make the sun bigger as it approaches the horizon
	const int SCALE_SUN_HT = 300000;
	D3DVALUE sunRad = 10667.f;
	if ( sunPos.nj.i < SCALE_SUN_HT )
	{
		sunRad*= 1.0f + D3DVALUE(SCALE_SUN_HT - sunPos.nj.i )/D3DVALUE(SCALE_SUN_HT*2.0);
	}
	g_lpLib3d->DrawSphere( 
		HMATERIAL(Image_Map.GetImageMapPtr(SUNMAPNO)),
		sunCenter, sunRad, ANGLES_0Deg, 0, 0, 63, 63 );
	
	g_lpLib3d->PopMatrix(MATRIX_OBJECT);

	g_lpLib3d->FlushAsBackground();
	SetFogBand();
	g_lpLib3d->SetObjectLighting( lf );
	g_lpLib3d->EnableFogging( true );

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StripHorizon
//Author		Paul.   
//Date			Fri 9 Oct 1998
//------------------------------------------------------------------------------
//DEADCODE JON 2/1/00 void LandScape::StripHorizon()
//DEADCODE JON 2/1/00 {
//DEADCODE JON 2/1/00 	struct SHCoords	{Float X,Y,Z;} HStripPts[]=
//DEADCODE JON 2/1/00 	{
//DEADCODE JON 2/1/00 	{-1,0,1}, 		{1,0,1},
//DEADCODE JON 2/1/00 	{-1,.125,1},	{1,.125,1},
//DEADCODE JON 2/1/00 	{-1,.2-.0125,1},{1,.2-.0125,1},
//DEADCODE JON 2/1/00 	{-1,.2,1},		{1,.2,1},		//cloud layer
//DEADCODE JON 2/1/00 	{-1,.2125,1},	{1,.2125,1},
//DEADCODE JON 2/1/00 	{-1,.4,1},		{1,.4,1},
//DEADCODE JON 2/1/00 	{-1,.6,1},		{1,.6,1},
//DEADCODE JON 2/1/00 	{-1,.8,1},		{1,.8,1},
//DEADCODE JON 2/1/00 	{-1,1,.75},		{1,1,.75},
//DEADCODE JON 2/1/00 	{-1,1,.5},		{1,1,.5},
//DEADCODE JON 2/1/00 	{-1,1,.25},		{1,1,.25},
//DEADCODE JON 2/1/00 	{-1,1,0},		{1,1,0},		//point directly over head
//DEADCODE JON 2/1/00 	{-1,1,-.25},	{1,1,-.25},
//DEADCODE JON 2/1/00 	{-1,1,-.5},		{1,1,-.5},
//DEADCODE JON 2/1/00 	{-1,1,-.75},	{1,1,-.75},
//DEADCODE JON 2/1/00 	{-1,.8,-1},		{1,.8,-1}
//DEADCODE JON 2/1/00 	};
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	
//DEADCODE JON 2/1/00 	struct SStripPoly {SLong v[4];}	HStripPoly[]=
//DEADCODE JON 2/1/00 	{
//DEADCODE JON 2/1/00 	{0,2,3,1},
//DEADCODE JON 2/1/00 	{2,4,5,3},
//DEADCODE JON 2/1/00 	{4,6,7,5},
//DEADCODE JON 2/1/00 	{6,8,9,7},
//DEADCODE JON 2/1/00 	{8,10,11,9},
//DEADCODE JON 2/1/00 	{10,12,13,11},
//DEADCODE JON 2/1/00 	{12,14,15,13},
//DEADCODE JON 2/1/00 	{14,16,17,15},
//DEADCODE JON 2/1/00 	{16,18,19,17},
//DEADCODE JON 2/1/00 	{18,20,21,19},
//DEADCODE JON 2/1/00 	{20,22,23,21},
//DEADCODE JON 2/1/00 	{22,24,25,23},
//DEADCODE JON 2/1/00 	{24,26,27,25},
//DEADCODE JON 2/1/00 	{26,28,29,27},
//DEADCODE JON 2/1/00 	{28,30,31,29}
//DEADCODE JON 2/1/00 	};
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	const SLong _stripPoints=sizeof(HStripPts)/sizeof(fpCOORDS3D);
//DEADCODE JON 2/1/00 	const SLong _stripPolys=sizeof(HStripPoly)/sizeof(SStripPoly);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	const SLong _topOfTheWorld=10;
//DEADCODE JON 2/1/00 	SLong curIndex=0;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	_cloudLayerHeight=HStripPts[6].Y*Float(CEILING_ALT);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	FPMATRIX 	mat,scale;
//DEADCODE JON 2/1/00 	Bool 		oldZState;
//DEADCODE JON 2/1/00 	Float 		dummy=0.;
//DEADCODE JON 2/1/00 	UByte 		br,bg,bb;
//DEADCODE JON 2/1/00 	UByte 		tr,tg,tb;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	br=currentLighting.horizonBase.red();
//DEADCODE JON 2/1/00 	bg=currentLighting.horizonBase.green();
//DEADCODE JON 2/1/00 	bb=currentLighting.horizonBase.blue();
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	tr=currentLighting.horizonMid.red();
//DEADCODE JON 2/1/00 	tg=currentLighting.horizonMid.green();
//DEADCODE JON 2/1/00 	tb=currentLighting.horizonMid.blue();
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 //DEADCODE PD 03/12/99 	GreyPalette(&br,&bg,&bb);
//DEADCODE JON 2/1/00 //DEADCODE PD 03/12/99 	GreyPalette(&tr,&tg,&tb);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 //TempCode PD 01Dec99 	currscreen->DoSetHorizonColour(br,bg,bb);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//calculate horizontal scaling factor for the
//DEADCODE JON 2/1/00 	//horizon object based on the view cone
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	Float fvr=Float(view_range);
//DEADCODE JON 2/1/00 	Float fvy=Float(viewer_y)/Float(CEILING_ALT);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//false horizon test code
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 //	Float hy=fvy*99./100.;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 //	HStripPts[2].Y=HStripPts[3].Y=hy;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	Float 	*m=(Float*)&mat,
//DEADCODE JON 2/1/00 			*s=(Float*)&scale;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	_matrix.Generate(ANGLES_0Deg,View_Point->pitch,View_Point->roll,&mat);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	s[0]=s[8]=fvr;
//DEADCODE JON 2/1/00 	s[4]=Float(CEILING_ALT);
//DEADCODE JON 2/1/00 	s[1]=s[2]=s[3]=s[5]=s[6]=s[7]=0;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	_matrix.multiply(&scale,&mat);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//transform all the points using this matrix
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	DoPointStruc* pdp=SHAPE.newco;
//DEADCODE JON 2/1/00 	SHCoords* psp=HStripPts;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	for (SLong i=_stripPoints;i--;)
//DEADCODE JON 2/1/00 	{
//DEADCODE JON 2/1/00 		Float py=psp->Y-fvy;
//DEADCODE JON 2/1/00 		pdp->bodyx.f=s[0]*psp->X+s[1]*py+s[2]*psp->Z;
//DEADCODE JON 2/1/00 		pdp->bodyy.f=s[3]*psp->X+s[4]*py+s[5]*psp->Z;
//DEADCODE JON 2/1/00 		pdp->bodyz.f=s[6]*psp->X+s[7]*py+s[8]*psp->Z;
//DEADCODE JON 2/1/00 		pdp++;
//DEADCODE JON 2/1/00 		psp++;
//DEADCODE JON 2/1/00 	}
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//render the polys
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	DoPointStruc* pp[4];
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//draw the strip along the edge of the horizon first
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
//DEADCODE JON 2/1/00 	pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
//DEADCODE JON 2/1/00 	pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
//DEADCODE JON 2/1/00 	pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
//DEADCODE JON 2/1/00 	GStrip(pp,br,bg,bb,tr,tg,tb);
//DEADCODE JON 2/1/00 	curIndex++;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//next, draw the strip between the last one and the one under
//DEADCODE JON 2/1/00 	//the base of the cloud layer
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	br=tr;
//DEADCODE JON 2/1/00 	bg=tg;
//DEADCODE JON 2/1/00 	bb=tb;
//DEADCODE JON 2/1/00 //	#pragma message(__HERE__ "PUT THIS BACK AFTER THE RUNNING DEMO")
//DEADCODE JON 2/1/00  	tr=currentLighting.horizonUnderClouds.red();
//DEADCODE JON 2/1/00 	tg=currentLighting.horizonUnderClouds.green();
//DEADCODE JON 2/1/00  	tb=currentLighting.horizonUnderClouds.blue();
//DEADCODE JON 2/1/00 //	currscreen->DoGammaCorr(tr,tg,tb);
//DEADCODE JON 2/1/00 //DEADCODE PD 03/12/99 	GreyPalette(&tr,&tg,&tb);
//DEADCODE JON 2/1/00 	pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
//DEADCODE JON 2/1/00 	pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
//DEADCODE JON 2/1/00 	pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
//DEADCODE JON 2/1/00 	pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
//DEADCODE JON 2/1/00 	GStrip(pp,br,bg,bb,tr,tg,tb);
//DEADCODE JON 2/1/00 	curIndex++;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//next, draw the strip under the base of the cloud layer
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	br=tr;
//DEADCODE JON 2/1/00 	bg=tg;
//DEADCODE JON 2/1/00 	bb=tb;
//DEADCODE JON 2/1/00 	tr=currentLighting.horizonAtClouds.red();
//DEADCODE JON 2/1/00 	tg=currentLighting.horizonAtClouds.green();
//DEADCODE JON 2/1/00 	tb=currentLighting.horizonAtClouds.blue();
//DEADCODE JON 2/1/00 //	currscreen->DoGammaCorr(tr,tg,tb);
//DEADCODE JON 2/1/00 //DEADCODE PD 03/12/99 	GreyPalette(&tr,&tg,&tb);
//DEADCODE JON 2/1/00 	pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
//DEADCODE JON 2/1/00 	pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
//DEADCODE JON 2/1/00 	pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
//DEADCODE JON 2/1/00 	pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
//DEADCODE JON 2/1/00 	GStrip(pp,br,bg,bb,tr,tg,tb);
//DEADCODE JON 2/1/00 	curIndex++;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//next, draw the strip above the top of the cloud layer
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	br=tr;
//DEADCODE JON 2/1/00 	bg=tg;
//DEADCODE JON 2/1/00 	bb=tb;
//DEADCODE JON 2/1/00 	tr=currentLighting.horizonAboveClouds.red();
//DEADCODE JON 2/1/00 	tg=currentLighting.horizonAboveClouds.green();
//DEADCODE JON 2/1/00 	tb=currentLighting.horizonAboveClouds.blue();
//DEADCODE JON 2/1/00 //	currscreen->DoGammaCorr(tr,tg,tb);
//DEADCODE JON 2/1/00 //DEADCODE PD 03/12/99 	GreyPalette(&tr,&tg,&tb);
//DEADCODE JON 2/1/00 	pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
//DEADCODE JON 2/1/00 	pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
//DEADCODE JON 2/1/00 	pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
//DEADCODE JON 2/1/00 	pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
//DEADCODE JON 2/1/00 	GStrip(pp,br,bg,bb,tr,tg,tb);
//DEADCODE JON 2/1/00 	curIndex++;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//next, draw all the strips between here and the top of the world
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	SLong rval,gval,bval;
//DEADCODE JON 2/1/00 	SLong rdda,gdda,bdda;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	br=tr;
//DEADCODE JON 2/1/00 	bg=tg;
//DEADCODE JON 2/1/00 	bb=tb;
//DEADCODE JON 2/1/00 	rval=SLong(br)<<8;
//DEADCODE JON 2/1/00 	gval=SLong(bg)<<8;
//DEADCODE JON 2/1/00 	bval=SLong(bb)<<8;
//DEADCODE JON 2/1/00 	tr=currentLighting.horizonTop.red();
//DEADCODE JON 2/1/00 	tg=currentLighting.horizonTop.green();
//DEADCODE JON 2/1/00 	tb=currentLighting.horizonTop.blue();
//DEADCODE JON 2/1/00 //	currscreen->DoGammaCorr(tr,tg,tb);
//DEADCODE JON 2/1/00 //DEADCODE PD 03/12/99 	GreyPalette(&tr,&tg,&tb);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 //	#pragma message(__HERE__ "PUT THIS BACK AFTER THE RUNNING DEMO")
//DEADCODE JON 2/1/00  	rdda=((SLong(tr)<<8)-rval)/(1+_topOfTheWorld-curIndex);
//DEADCODE JON 2/1/00  	gdda=((SLong(tg)<<8)-gval)/(1+_topOfTheWorld-curIndex);
//DEADCODE JON 2/1/00  	bdda=((SLong(tb)<<8)-bval)/(1+_topOfTheWorld-curIndex);
//DEADCODE JON 2/1/00 	rdda=gdda=bdda=0;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	for (;curIndex<=_topOfTheWorld;curIndex++)
//DEADCODE JON 2/1/00 	{
//DEADCODE JON 2/1/00 		pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
//DEADCODE JON 2/1/00 		pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
//DEADCODE JON 2/1/00 		pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
//DEADCODE JON 2/1/00 		pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
//DEADCODE JON 2/1/00 		rval+=rdda;
//DEADCODE JON 2/1/00 		gval+=gdda;
//DEADCODE JON 2/1/00 		bval+=bdda;
//DEADCODE JON 2/1/00 		tr=UByte(rval>>8);
//DEADCODE JON 2/1/00 		tg=UByte(gval>>8);
//DEADCODE JON 2/1/00 		tb=UByte(bval>>8);
//DEADCODE JON 2/1/00 		GStrip(pp,br,bg,bb,tr,tg,tb);
//DEADCODE JON 2/1/00 		br=tr;
//DEADCODE JON 2/1/00 		bg=tg;
//DEADCODE JON 2/1/00 		bb=tb;
//DEADCODE JON 2/1/00 	}
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	for (;curIndex<_stripPolys;curIndex++)
//DEADCODE JON 2/1/00 	{
//DEADCODE JON 2/1/00 		pp[0]=SHAPE.newco+HStripPoly[curIndex].v[0];
//DEADCODE JON 2/1/00 		pp[1]=SHAPE.newco+HStripPoly[curIndex].v[1];
//DEADCODE JON 2/1/00 		pp[2]=SHAPE.newco+HStripPoly[curIndex].v[2];
//DEADCODE JON 2/1/00 		pp[3]=SHAPE.newco+HStripPoly[curIndex].v[3];
//DEADCODE JON 2/1/00 		GStrip(pp,br,bg,bb,br,bg,bb);
//DEADCODE JON 2/1/00 	}
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	SLong fogdist,fogbegin;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	Float frsq=Float(viewer_y)*Float(viewer_y)+fvr*fvr;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	_asm
//DEADCODE JON 2/1/00 	{
//DEADCODE JON 2/1/00 		fld frsq;
//DEADCODE JON 2/1/00 		fsqrt;
//DEADCODE JON 2/1/00 		fstp frsq;
//DEADCODE JON 2/1/00 	}
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//force fog to match visibility settings
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	if (frsq>MMC.Sky.Visibility) frsq=MMC.Sky.Visibility;
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	//test code... Set visibility to 1km
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	fogdist=SLong(frsq);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	if (!Save_Data.detail_3d[DETAIL3D_HORIZONFADE])	fogbegin=fogdist>>1;
//DEADCODE JON 2/1/00 	else											fogbegin=fogdist-(fogdist>>2);
//DEADCODE JON 2/1/00 
//DEADCODE JON 2/1/00 	groundFogBegin=fogbegin;
//DEADCODE JON 2/1/00 	groundFogEnd=fogdist;
//DEADCODE JON 2/1/00 	SetFogMode(fogbegin,fogdist);
//DEADCODE JON 2/1/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GenerateGroundPoints
//LastModified:	PD 22May96
//Author		Paul.   
//Date			Fri 5 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void LandScape::GenerateGroundPoints(	SLong range, SLong width,
										SLong& wx1, SLong& wz1, SLong& wx2, SLong& wz2)
{
	SWord	sin_theta,cos_theta;

	SWord	scale;
	SWord	wscale;
	SWord	rsign;

	ANGLES	heading = (ANGLES )(-viewer_hdg);					//PD 12Mar96

	//Scale the range value to prevent o'flows

	if (range<0)
	{
		range= -range;
		rsign= -1;
	}
	else
	{
		rsign= 1;
	}

	for(scale=0;range>0x07FFF;range>>=1,scale++);

	if (rsign==-1)	range= -range;								//PD 22May96

	for(wscale=0;width>0x07FFF;width>>=1,wscale++);				//PD 22May96

	wscale++;							//PD 15Apr97

	Math_Lib.high_sin_cos(heading,sin_theta,cos_theta);			//PD 23Feb96

	SLong	wx_mid,wz_mid;

	wx_mid = (range * (SLong )sin_theta)/ANGLES_FRACT;			//PD 12Mar96
	
	wx_mid <<= scale;											//PD 12Mar96

	wz_mid = (range * (SLong )cos_theta)/ANGLES_FRACT;			//PD 12Mar96
	
	wz_mid <<= scale;											//PD 12Mar96

	SLong	wx_delta,wz_delta;

	wx_delta = (width * (SLong )cos_theta)/ANGLES_FRACT;		//PD 22May96
	
	wx_delta <<= wscale;										//PD 22May96

	wz_delta = (width * (SLong )sin_theta)/ANGLES_FRACT;		//PD 22May96
	
	wz_delta <<= wscale;										//PD 22May96

	wx1 = viewer_x + wx_mid - wx_delta;

	wz1 = viewer_z + wz_mid + wz_delta;

	wx2 = viewer_x + wx_mid + wx_delta;

	wz2 = viewer_z + wz_mid - wz_delta;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IntenseFromRange
//LastModified:	PD 07Jun96
//Author		Paul.   
//Date			Thu 11 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord LandScape::IntensFromRange(SLong range)
{
	SWord	retval;
	SLong	rangedelta,fadedelta;

	if (range>fade_band_end)	return(255);

	rangedelta = fade_band_end - fade_band_start;

	if (range<fade_band_start-rangedelta)
		return(-255);

	if (range>=fade_band_start)
	{
		fadedelta = range - fade_band_start;

		if (fadedelta<0x7FFFFF)
			retval = (fadedelta<<8)/rangedelta;
		else
			retval = (fadedelta/(rangedelta>>8));
	}
	else
	{
		fadedelta = fade_band_start - range;

		if (fadedelta<0x7FFFFF)
			retval = (fadedelta<<8)/rangedelta;
		else
			retval = (fadedelta/(rangedelta>>8));

		retval =- retval;
	}

	//Clip to max and min.										//PD 26Nov96

	if (retval<-0xFF)	retval=-0xFF;							//PD 27Nov96
	if (retval>0xFF)	retval=0xFF;							//PD 27Nov96

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetViewDetail
//LastModified:	PD 25Mar98
//Author		Paul.   
//Date			Tue 12 Mar 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::SetViewDetail()
{
	//Height is the actual height above the current piece of ground data
	SLong height;
	height=viewer_y-GetGroundLevel(*View_Point);				//PD 20Aug98

	SLong viewer_range;
	
 	viewer_range=(0x1F1CDA>>1);

	gnd_band_start=0x160000;//0x5A828;

	if (Key_Tests.KeyPress3d(DETAILUP)) IncDetailLevel();
	else if (Key_Tests.KeyPress3d(DETAILDN)) DecDetailLevel();

	shape_band_start=viewer_range-(viewer_range>>2);

//DEADCODE JON 2/1/00 	view_range=viewer_range;
//DEADCODE JON 2/1/00 	CalcVisibleRanges(view_range,viewer_y);
//DEADCODE JON 4/19/00 	CalcVisibleRanges(_blockWidth*_horizonDist,viewer_y);
	CalcVisibleRanges(view_dist,viewer_y);

//DEADCODE PD 02/12/99 	_matrix.SetViewParams(currscreen,Save_Data.fieldOfView,gvisrange);

	gnd_band_end 	= gvisrange;
	sky_band_end 	= cvisrange;
	fade_band_start = gnd_band_start;
	fade_band_end 	= gnd_band_end;

//DeadCode JON 20Oct00 	SLong fogstart=gnd_band_start;
//DeadCode JON 20Oct00 	SLong fogend=gvisrange;
	gnd_band_end=sky_band_end=viewer_range;
//DEADCODE PD 02/12/99 	currscreen->DoSetFogState(TRUE);
//DEADCODE PD 02/12/99 	currscreen->DoSetMatrices(gvisrange,viewconeangle);
//	g_lpLib3d->SetProjectionMatrix(Angles(Save_Data.fieldOfView>>1),1,1,gvisrange);
//DEADCODE PD 01/12/99 	currscreen->HCls(FALSE);
//DEADCODE PD 01/12/99 	POLYGON.setpolyscrn(currscreen,gvisrange,viewconeangle);

	return(height);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CalcVisibleRanges
//Author		Paul.   
//Date			Thu 14 Nov 1996
//
//Description	Caclulates visible ranges for ground and cloud tiles - takes
//				account of the aircrafts altitude
//
//Inputs		flat visible distance
//				viewer_y
//
//Returns		visible ranges for;
//						ground tiles		-	gvisrange
//						cloud tiles			-	cvisrange
//
//------------------------------------------------------------------------------
void LandScape::CalcVisibleRanges(SLong flatd,SLong alt)
{
	//Ground tile distance first

	SLong	dx = (flatd>=0)?flatd:-flatd;
	SLong	dy = (alt>=0)?alt:-alt;								//PD 12Dec96

	if (dy>dx)	{int tmp=dx;dx=dy;dy=tmp;}						//PD 19Aug97

	gvisrange = dx;
	dy >>= 2;
	gvisrange += dy;
	dy >>= 2;
	gvisrange += dy;
	dy >>= 1;
	gvisrange += dy;

	//Under cloud distance next

	dx = (flatd>=0)?flatd:-flatd;								//PD 27Sep97

	dy = (Cloud_Layer_Height - alt);

	dy = (dy>=0)?dy:-dy;

	if (dy>dx)	{int tmp=dx;dx=dy;dy=tmp;}						//PD 02Oct97

	cvisrange = dx;
	dy >>= 2;
	cvisrange += dy;
	dy >>= 2;
	cvisrange += dy;
	dy >>= 1;
	cvisrange += dy;

	//Modify fade ranges based on the viewers altitude for
 	//hardware version ONLY

	dx = gnd_band_start;
	dy = (alt<0)?-alt:alt;
	if (dy>dx) {int tmp=dx;dx=dy;dy=tmp;}
	dy>>=2;
	dx+= dy;
	dy>>=2;
	dx+=dy;
	dy>>=1;
	dx+=dy;

	if (dx<gnd_band_end)
		gnd_band_start=dx;
	else
		gnd_band_start=gnd_band_end;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BadVision
//Author		Paul.   
//Date			Thu 20 Jun 1996
//
//Description	Sets blackout stuff going
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool LandScape::BadVision()
{
	if (!Save_Data.hardwareconfig[HW_GEFFECTS] &&
		!Save_Data.hardwareconfig[HW_INJURYEFFECTS] &&
		!Save_Data.hardwareconfig[HW_WHITEOUT])
		return FALSE;

	TDFadeType	tdftFadeType;									//PD 05Jun97

	Bool retval;
	Bool	forceredfade=FALSE;									//RJS 21Oct97

	const SLong	fademax = 255;

	AirStruc*	acptr = Manual_Pilot.ControlledAC2;
	if (acptr)
	{
// dont have blackouts in replay playback or in comms sync phase
		if(		_Replay.Playback										//RJS 27Jul00
			||	(_DPlay.Implemented && !_DPlay.synched)					//RJS 27Jul00
			|| (Manual_Pilot.controlmode==ManualPilot::PILOTDEAD)		//RJS 27Jul00
			||	acptr->weap.Ejected									)	//RJS 27Jul00
		{
			blackingout = 0;
			redingout   = 0;
		}
		else
		{
			if (Save_Data.hardwareconfig[HW_GEFFECTS])
			{
				FP Blood = acptr->fly.pModel->Blood;	//CSB 09/06/99	
				FP Blackout, Redout;
				for(;;)
				{
					if(Blood < 0.3333)
					{	Redout = 0;		Blackout = 1;				break;	}

					if(Blood < 0.6667)
					{	Redout = 0;		Blackout = 2 - 3 * Blood; 	break;	}

					if(Blood < 1.1667)
					{	Redout = 0;		Blackout = 0;				break;	}
					
					if(Blood < 1.3333)
					{	Blackout = 0;	Redout = 6 * Blood - 7;		break;	}

					Redout	 = 1;
					Blackout = 0;
					break;
				}

				blackingout = UWord(fademax * Blackout);
				redingout   = UWord(fademax * Redout);
				if((redingout) || (Blood == 1)) forceredfade = TRUE;			//CSB 09/06/99	
			}

			ULong injuryredout = 0;
			if(Save_Data.hardwareconfig[HW_INJURYEFFECTS])
			{
				if (gunnerDead)											//RJS 24Oct00
				{
					redingout = 100;
					forceredfade = TRUE;
				}
				else
				{
					if (acptr->classtype->aerobaticfactor != AEROBATIC_LOW)	//RJS 24Oct00
					{
						AircraftAnimData *adptr = (AircraftAnimData*)acptr->Anim;
						if(adptr->CANOPY != 255)
							injuryredout = adptr->CANOPY * 32;
						if(injuryredout > 127)
							injuryredout = 127;
						if((injuryredout > redingout) && (injuryredout > blackingout))
						{	
							redingout = injuryredout;
							forceredfade = TRUE;
						}
					}
				}
			}
		}

	}

	if ( forceredfade )
	{
		g_lpLib3d->DoFade( 0x952424, redingout );
	} else if ( blackingout )
	{
		g_lpLib3d->DoFade( 0, blackingout );
	}
//DeadCode RJS 20Apr00 	return TRUE;
 	if (!blackingout)											//RJS 21Oct97
 	{
 		//White out test here
  		if (Save_Data.hardwareconfig[HW_WHITEOUT])				//RJS 21Oct97
  		{
 			if (SHAPE.SunInVision)
 			{
 				whitingout++;
 				if (whitingout>fademax)									//RJS 12Jun98
 					whitingout = fademax;								//RJS 12Jun98
 			}
 			else
 			{
 				whitingout--;
 				if (whitingout<0)
 					whitingout = 0;
 			}

			g_lpLib3d->DoWhiteOut( 0xFFFFFF, whitingout, sun_screen_x, sun_screen_y, sun_glare );//RJS 20Apr00
  		}
 		else
		{
			if (whitingout)
				g_lpLib3d->DoWhiteOut( 0xFFFFFF, 0, 0, 0, 0 );		//RJS 20Apr00

  			whitingout = 0;										//RJS 21Oct97
		}
 	}
	return TRUE;

//DEADCODE JON 4/11/00 	if (blackingout || forceredfade || whitingout)
//DEADCODE JON 4/11/00 	{
//DEADCODE JON 4/11/00 		//There will only be 1 fade at a time.
//DEADCODE JON 4/11/00 		//The priorities are as follows...
//DEADCODE JON 4/11/00 		//red should come first, cos that means you're dead.
//DEADCODE JON 4/11/00 		//Redout > Blackout > Whiteout
//DEADCODE JON 4/11/00 
//DEADCODE JON 4/11/00 		GREY3DTYPE	gtdt;
//DEADCODE JON 4/11/00 
//DEADCODE JON 4/11/00 		Bool	fading=FALSE;
//DEADCODE JON 4/11/00 
//DEADCODE JON 4/11/00 		if (forceredfade)										//RJS 21Oct97
//DEADCODE JON 4/11/00 		{
//DEADCODE JON 4/11/00 			gtdt = (GREY3DTYPE )redingout;						//RJS 21Oct97
//DEADCODE JON 4/11/00 			tdftFadeType = _BLACKOUT;							//PD 05Jun97
//DEADCODE JON 4/11/00 			fading=TRUE;										//PD 27Nov96
//DEADCODE JON 4/11/00 		}
//DEADCODE JON 4/11/00 		else
//DEADCODE JON 4/11/00 		{
//DEADCODE JON 4/11/00 			if (blackingout)									//RJS 21Oct97
//DEADCODE JON 4/11/00 			{										
//DEADCODE JON 4/11/00 				gtdt = (GREY3DTYPE )blackingout;				//RJS 21Oct97
//DEADCODE JON 4/11/00 				tdftFadeType = _REDOUT;							//PD 05Jun97
//DEADCODE JON 4/11/00 				fading=TRUE;									//PD 27Nov96
//DEADCODE JON 4/11/00 			}
//DEADCODE JON 4/11/00 			else
//DEADCODE JON 4/11/00 			{
//DEADCODE JON 4/11/00 				if (whitingout)									//RJS 21Oct97
//DEADCODE JON 4/11/00 				{
//DEADCODE JON 4/11/00 					gtdt = (GREY3DTYPE )whitingout;
//DEADCODE JON 4/11/00 					tdftFadeType = _WHITEOUT;					//PD 05Jun97
//DEADCODE JON 4/11/00 					fading=TRUE;								//PD 27Nov96
//DEADCODE JON 4/11/00 				}
//DEADCODE JON 4/11/00 			}
//DEADCODE JON 4/11/00 		}
//DEADCODE JON 4/11/00 
//DEADCODE JON 4/11/00 		if (fading)												//PD 27Nov96
//DEADCODE JON 4/11/00 		{														//PD 09Sep96
//DEADCODE JON 4/11/00 			TWODEFFECT tde=TDE_UNIFORM;
//DEADCODE JON 4/11/00 
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 			if (!Save_Data.fSoftware)
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 			{
//DEADCODE JON 4/11/00 				Colour	tCol;
//DEADCODE JON 4/11/00 				switch (tdftFadeType)
//DEADCODE JON 4/11/00 				{
//DEADCODE JON 4/11/00 					case _WHITEOUT:	tCol = WHITE; tde = TDE_INSIDE2OUT; break;
//DEADCODE JON 4/11/00 					case _BLACKOUT:	tCol = RED; tde = TDE_OUTSIDE2IN; break;
//DEADCODE JON 4/11/00 					case _REDOUT:	tCol = BLACK; tde = TDE_OUTSIDE2IN; break;
//DEADCODE JON 4/11/00 				}
//DEADCODE JON 4/11/00 
//DEADCODE JON 4/11/00 //DEADCODE PD 02/12/99 				currscreen->DoSetFade(tCol,((SLong)gtdt)>>1,tde);//RJS 12Jun98
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 			}
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 			else
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 			{
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 				switch (tdftFadeType)
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 				{
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 				case _WHITEOUT: POLYGON.SetSoftwareFades(2,UWord(gtdt)>>1); break;
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 				case _BLACKOUT: POLYGON.SetSoftwareFades(1,UWord(gtdt)>>1); break;
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 				case _REDOUT: POLYGON.SetSoftwareFades(0,UWord(gtdt)>>1); break;
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 				}
//DEADCODE JON 4/11/00 //DEADCODE PD 01/12/99 			}
//DEADCODE JON 4/11/00 		}														//PD 09Sep96
//DEADCODE JON 4/11/00 
//DEADCODE JON 4/11/00 		retval = TRUE;
//DEADCODE JON 4/11/00 	}
//DEADCODE JON 4/11/00 	else
//DEADCODE JON 4/11/00 	{
//DEADCODE JON 4/11/00 		retval = FALSE;
//DEADCODE JON 4/11/00 	}
//DEADCODE JON 4/11/00 
//DEADCODE JON 4/11/00 	return (retval);
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFadeStart
//Author		Martin Alderton
//Date			Thu 9 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetFadeStart()
{
	SLong	retval = shape_band_start; //fade_band_start;		//RDH 17Dec96
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetFadeEnd
//Author		Martin Alderton
//Date			Thu 9 May 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong LandScape::GetFadeEnd()
{
	SLong	retval = fade_band_end;
	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		CloudLayer
//Author		Paul.   
//Date			Thu 5 Dec 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//DEADCODE JIM 12/06/00 int	Cloud_Flag=2;
void LandScape::CloudLayer(ViewPoint* vp)
{
#ifndef _NOCLOUDS_
#ifndef _NO_FLUFFY_CLOUDS_

	if (Save_Data.hardwareconfig[HW_FLUFFYCLOUDS])
//DEADCODE JIM 12/06/00 	if (Cloud_Flag==0)
//DEADCODE JIM 12/06/00 		return;

	if (Save_Data.hardwareconfig[HW_FLUFFYCLOUDS])						//RJS 26Jun00
	{
  		SLong sectorshift=20;
		SLong sectorsize=1<<sectorshift;
//DeadCode JON 20Oct00 		SLong sectormask=sectorsize-1;
//DeadCode JON 20Oct00 		SLong	sectorsizehalf = sectorsize >> 1;
		SLong	sectorstep;
  
		// All cloud shapes MUST have same anim data...
  		static	ShapeNum	cloudshapes[8]=
  							{
  								CLOUD1,CLOUD2,
  								CLOUD3,CLOUD1,
  								CLOUD1,CLOUD4,
  								CLOUD2,CLOUD2
  							};
  
  		//Insert some clouds in the sky around the viewpoint
  		SLong	oldfaderange=fade_band_end;
		fade_band_end=0x7FFFFFFF;
  
  		item	dummyitem;
  
  		COORDS3D curpos;
  
//DeadCode JON 23Oct00   		int		cloudselect=0,
		int		cloudindex;
  
//DeadCode JON 20Oct00   		int		altselect=0xFF;
//DeadCode JON 20Oct00 		int realalt;
  		COORDS3D corner = vp->World;

		UWord	sector_x, sector_z;
		SLong	newX, newZ, newY;
		SLong	wx,wy,wz;
		SLong	RootX;
		int	j,k;

		// For each sector... 4 * 4 clouds...
		// Also fill each neighbouring sector

		sector_x = corner.X >> sectorshift;
		sector_z = corner.Z >> sectorshift;

		corner.X = sector_x << sectorshift;
  		corner.Z = sector_z << sectorshift;
		corner.X -= sectorsize;
		corner.Z -= sectorsize;

//TempCode PD 20Aug98 		sectorstep = sectorsize / 4;
		sectorstep = sectorsize / 2;

 		// corner(X,Y,Z) is start position
		//Init dummy item anim data...
		dummyitem.Anim = CloudAnimP;								//RJS 10Jul98
		RootX = corner.X;

		for (sector_z = 0; sector_z < 3; sector_z++)
		{
			corner.X = RootX;
			for (sector_x = 0; sector_x < 3; sector_x++)
			{
				wy = 0;
				curpos=corner;
  				for (k=0;k<2;k++)
  				{
  					curpos.X = corner.X;
  					for (j=0;j<2;j++)
					{
						wx = corner.X;
						wz = corner.Z;

						newX = curpos.X + ((SHAPE.Noise(wx++,wy++,wz++)-128) << 10);
						newZ = curpos.Z + ((SHAPE.Noise(wx++,wy++,wz++)-128) << 10);
						newY = SHAPE.Noise(newX,wy++,newZ) << 10;

						cloudindex = (7*SHAPE.Noise(newX,newY,newZ))/255;
  
  						dummyitem.World.X = newX;
  						dummyitem.World.Z = newZ;
  						dummyitem.World.Y = FT_8000 + newY;
  						dummyitem.shape = cloudshapes[cloudindex];
//DEADCODE JIM 12/06/00   				  		if (Cloud_Flag>1)
	  						Three_Dee.do_object_dummy(&dummyitem,STATIC_OBJECT);//RJS 04Feb00
  
  						curpos.X += sectorstep;
  					}
  					curpos.Z += sectorstep;
  				}
				corner.X += sectorsize;
			}
			corner.Z += sectorsize;
		}
  		fade_band_end=oldfaderange;

		dummyitem.Anim = ANIM_NULL;
	}

#endif
#endif
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
//	LandScape - first frame setup routines
//				also used while inside cloud layer to make sure the ground is
//				avaliable when the viewer comes out of the clouds
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//DeadCode JON 23Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 23Oct00 //Procedure		SetFogMode
//DeadCode JON 23Oct00 //Author		Paul.   
//DeadCode JON 23Oct00 //Date			Wed 28 May 1997
//DeadCode JON 23Oct00 //
//DeadCode JON 23Oct00 //Description	
//DeadCode JON 23Oct00 //
//DeadCode JON 23Oct00 //Inputs		
//DeadCode JON 23Oct00 //
//DeadCode JON 23Oct00 //Returns	
//DeadCode JON 23Oct00 //
//DeadCode JON 23Oct00 //------------------------------------------------------------------------------
//DeadCode JON 23Oct00 void LandScape::SetFogMode(SLong start,SLong end)
//DeadCode JON 23Oct00 {
//DeadCode JON 23Oct00 //deadcode	Colour	fogcolour;
//DeadCode JON 23Oct00 //deadcode	UByte hr,hg,hb;
//DeadCode JON 23Oct00 //deadcode
//DeadCode JON 23Oct00 //deadcode	if (incloudlayer==TRUE)							
//DeadCode JON 23Oct00 //deadcode	{
//DeadCode JON 23Oct00 //deadcode		start;
//DeadCode JON 23Oct00 //deadcode		end <<= 3;
//DeadCode JON 23Oct00 //deadcode		fogcolour = WHITE;
//DeadCode JON 23Oct00 //deadcode		hr=hg=hb=0xFF;
//DeadCode JON 23Oct00 //deadcode	}
//DeadCode JON 23Oct00 //deadcode	else
//DeadCode JON 23Oct00 //deadcode	{
//DeadCode JON 23Oct00 //deadcode		fogcolour = (Colour)0x00;	//currscreen->DoGetHorizonColour();
//DeadCode JON 23Oct00 //deadcode		hr=currentLighting.horizonBase.red();
//DeadCode JON 23Oct00 //deadcode		hg=currentLighting.horizonBase.green();
//DeadCode JON 23Oct00 //deadcode		hb=currentLighting.horizonBase.blue();
//DeadCode JON 23Oct00 //deadcode	}
//DeadCode JON 23Oct00 //DEADCODE PD 01/12/99 	currscreen->DoGammaCorr(hr,hg,hb);
//DeadCode JON 23Oct00 //DEADCODE PD 03/12/99 	GreyPalette(&hr,&hg,&hb);
//DeadCode JON 23Oct00 //DEADCODE PD 01/12/99 	currscreen->DoSetFog(hr,hg,hb,start,end);
//DeadCode JON 23Oct00 //DEADCODE PD 01/12/99 	currscreen->DoSetHorizonColour(hr,hg,hb);
//DeadCode JON 23Oct00 }

void LandScape::SetSkyMap(FileNum	theFile)
{
	FilSkyStrip = theFile;
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScaleInsideHorizon
//Author		Paul.   
//Date			Tue 5 May 1998
//------------------------------------------------------------------------------
void LandScape::ScaleInsideHorizon(COORDS3D& pos)
{
	pos.X=gvisrange+viewer_x;
	pos.Y=gvisrange;
	pos.Z=viewer_z;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLVector
//Author		Paul.   
//Date			Mon 11 May 1998
//------------------------------------------------------------------------------
void LandScape::SetLVector(COORDS3D& sunPos)
{
	Three_Dee.pMigLand->SetLVector(sunPos.X,sunPos.Y,sunPos.Z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AutoScaleFrameRate
//Author		Paul.   
//Date			Wed 18 Nov 1998
//------------------------------------------------------------------------------
void LandScape::AutoScaleFrameRate()
{
	if (!Save_Data.detail_3d[DETAIL3D_AUTODETAIL])						//JON 3Aug00
		return;														

	static UByte testingtime=0;
	testingtime++;
	if (testingtime)
		return;
//DeadCode JON 3Aug00 #define FRAMES_RECORDED 20
//DeadCode JON 3Aug00 	static SWord framerec[FRAMES_RECORDED]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//DeadCode JON 3Aug00 	static SWord findex=0;
//DeadCode JON 3Aug00 	if (View_Point && !View_Point->Accel())
//DeadCode JON 3Aug00 	{
//DeadCode JON 3Aug00 		framerec[findex++]=View_Point->RealFrameTime();
//DeadCode JON 3Aug00 		if (findex==FRAMES_RECORDED) findex=0;
//DeadCode JON 3Aug00 	}
//DeadCode JON 3Aug00 	SWord averageFramesPerSec;
//DeadCode JON 3Aug00 	
//DeadCode JON 3Aug00 	if (framerec[FRAMES_RECORDED-1])
//DeadCode JON 3Aug00 	{
//DeadCode JON 3Aug00 		SWord tot=framerec[0];
//DeadCode JON 3Aug00 		for (int i=19;i>0;i--) tot+=framerec[i];
//DeadCode JON 3Aug00 		averageFramesPerSec=(100*FRAMES_RECORDED)/tot;
//DeadCode JON 3Aug00 	}
//DeadCode JON 3Aug00 	else averageFramesPerSec=Save_Data.desiredfps;
// there's nothing wrong with the above code - however this is better, and now I understand it...

	const int RECORDED_FRAMES = 20;
	static int frameIndex=0;
	static int frameRecord[RECORDED_FRAMES]={
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps,
		1000/Save_Data.desiredfps };
	static int cumFrameRec = (1000*RECORDED_FRAMES)/Save_Data.desiredfps;// cumulative frame record total...

	if (View_Point && !View_Point->Accel())
	{
		int curFrameTime = View_Point->getFrameTimeMSecs();
		cumFrameRec-=frameRecord[frameIndex];
		cumFrameRec+=curFrameTime;
		frameRecord[frameIndex++]=curFrameTime;
		frameIndex%=RECORDED_FRAMES;
	}
	int averageFramesPerSec=(1000*RECORDED_FRAMES)/cumFrameRec;	

#ifdef SHOW_FRAMERATE
	UByte debStr[64];
	sprintf((char*)debStr,"FT: %04d",averageFramesPerSec);
	Mono_Text.PrintAt(0,0,debStr);
#endif

	if (averageFramesPerSec>(Save_Data.desiredfps+5))
	{
		IncDetailLevel();
	}
	else if (averageFramesPerSec<Save_Data.desiredfps)
	{
		DecDetailLevel();
	}

	// the logic behind the (mig) code below was that even if autoscale framerate wasn't
	// set then the mesh detail can be altered...  This is no longer the case for bob...

//DeadCode JON 3Aug00 	bool alterDetail;
//DeadCode JON 3Aug00 	SLong wholeAreaSize,halfAreaSize;
//DeadCode JON 3Aug00 	
//DeadCode JON 3Aug00 	wholeAreaSize=_wholeAreaSizeMIN;
//DeadCode JON 3Aug00 
//DeadCode JON 3Aug00 	halfAreaSize=wholeAreaSize>>1;
//DeadCode JON 3Aug00 
//DeadCode JON 3Aug00 	alterDetail=false;
//DeadCode JON 3Aug00 
//DeadCode JON 3Aug00 	if (!Save_Data.detail_3d[DETAIL3D_AUTODETAIL])
//DeadCode JON 3Aug00 	{
//DeadCode JON 3Aug00 		if (!Save_Data.detail_3d[DETAIL3D_CONTOURDETAIL])
//DeadCode JON 3Aug00 		{
//DeadCode JON 3Aug00 			if (land_min_detail!=2)
//DeadCode JON 3Aug00 			{
//DeadCode JON 3Aug00 				land_min_detail=2;
//DeadCode JON 3Aug00 				alterDetail=true;
//DeadCode JON 3Aug00 			}
//DeadCode JON 3Aug00 		}
//DeadCode JON 3Aug00 		else
//DeadCode JON 3Aug00 		{
//DeadCode JON 3Aug00 			if (land_min_detail!=halfAreaSize)
//DeadCode JON 3Aug00 			{
//DeadCode JON 3Aug00 				land_min_detail=halfAreaSize;
//DeadCode JON 3Aug00 				alterDetail=true;
//DeadCode JON 3Aug00 			}
//DeadCode JON 3Aug00 		}
//DeadCode JON 3Aug00 
//DeadCode JON 3Aug00 	}
//DeadCode JON 3Aug00 	else if (averageFramesPerSec>(Save_Data.desiredfps+5))
//DeadCode JON 3Aug00 	{
//DeadCode JON 3Aug00 		land_min_detail++;
//DeadCode JON 3Aug00 		if (land_min_detail>halfAreaSize)
//DeadCode JON 3Aug00 			land_min_detail=halfAreaSize;
//DeadCode JON 3Aug00 		else
//DeadCode JON 3Aug00 			alterDetail=true;
//DeadCode JON 3Aug00 		IncDetailLevel();
//DeadCode JON 3Aug00 	}
//DeadCode JON 3Aug00 	else if (averageFramesPerSec<Save_Data.desiredfps)
//DeadCode JON 3Aug00 	{
//DeadCode JON 3Aug00 		land_min_detail--;
//DeadCode JON 3Aug00 		if (land_min_detail<2)
//DeadCode JON 3Aug00 			land_min_detail=2;
//DeadCode JON 3Aug00 		else
//DeadCode JON 3Aug00 			alterDetail=true;
//DeadCode JON 3Aug00 		DecDetailLevel();
//DeadCode JON 3Aug00 	}
//DeadCode JON 3Aug00 
//DeadCode JON 3Aug00 	if (alterDetail)
//DeadCode JON 3Aug00 	{
//DeadCode JON 3Aug00 		UByte* pResG=groundDetail;
//DeadCode JON 3Aug00 
//DeadCode JON 3Aug00 		UByte min_val;
//DeadCode JON 3Aug00 //DEADCODE PD 01/12/99 		if (Save_Data.fSoftware)	min_val=2;
//DeadCode JON 3Aug00 		min_val=0;
//DeadCode JON 3Aug00 		for (SLong x=0;x<wholeAreaSize;x++)
//DeadCode JON 3Aug00 		{
//DeadCode JON 3Aug00 			SLong tx=x-halfAreaSize;
//DeadCode JON 3Aug00 			tx*=tx;
//DeadCode JON 3Aug00 			for (SLong y=0;y<wholeAreaSize;y++)
//DeadCode JON 3Aug00 			{
//DeadCode JON 3Aug00 				SLong ty=y-halfAreaSize;
//DeadCode JON 3Aug00 				ty=ty*ty+tx;
//DeadCode JON 3Aug00 				double fp_dist;
//DeadCode JON 3Aug00 				_asm
//DeadCode JON 3Aug00 				{
//DeadCode JON 3Aug00 					fild ty;
//DeadCode JON 3Aug00 					fsqrt;
//DeadCode JON 3Aug00 					fstp fp_dist;
//DeadCode JON 3Aug00 				}
//DeadCode JON 3Aug00 				ty=SLong(fp_dist+.5);
//DeadCode JON 3Aug00 				if (ty<=land_min_detail)	*pResG++=min_val;
//DeadCode JON 3Aug00 				else						*pResG++=254;
//DeadCode JON 3Aug00 			}
//DeadCode JON 3Aug00 		}
//DeadCode JON 3Aug00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init
//Author		Paul.   
//Date			Thu 14 May 1998
//------------------------------------------------------------------------------
void LandScape::Init(CLib3D *lib3d)
{
//DEADCODE PD 01/12/99 	if (Save_Data.fSoftware)	land_min_detail=4;
	lastMeshDataX = -10000;									//JON 9Nov00
	lastMeshDataZ = -10000;

	g_lpLib3d=lib3d;
	land_min_detail=2;

//DeadCode JON 20Oct00 	SLong cornerBufferSize=_cornerBufferSizeMIN;
	SLong wholeAreaSize=_wholeAreaSizeMIN;
//DeadCode JON 20Oct00 	SLong halfAreaSize=_halfAreaSizeMIN;

//DeadCode JON 12Sep00 	if (!gridCorners) gridCorners=new UByte[cornerBufferSize];
//DeadCode JON 5Sep00 	if (!softGrid) softGrid=new UByte[wholeAreaSize*wholeAreaSize];
	if (!gridCone) gridCone=new UByte[wholeAreaSize*wholeAreaSize];
	if (!horizCone) horizCone=new bool[_horizonAreaSize*_horizonAreaSize];
//DeadCode JON 12Sep00 	if (!lightCone) lightCone=new UByte[wholeAreaSize*wholeAreaSize];
//DeadCode JON 12Sep00 	if (!routeDetail) routeDetail=new UByte[wholeAreaSize*wholeAreaSize];
//DeadCode JON 3Aug00 	if (!groundDetail) groundDetail=new UByte[wholeAreaSize*wholeAreaSize];
//DeadCode JON 12Sep00 	if (!landRnd) landRnd=new UByte[256];
//DeadCode JON 12Sep00 #pragma warnmsg ( "remove me" )
//DeadCode JON 12Sep00 	DbgMemTest3( landRnd );

	if (!tileCoords) tileCoords=new COORDS3D[256];
	if (!pDataBlocks) pDataBlocks=new DataRecord[wholeAreaSize*wholeAreaSize];
	if (!tileCacheGrid) tileCacheGrid=new TileElement[_wholeAreaSizeMIN*_wholeAreaSizeMIN];
	TileResList::theGrid = tileCacheGrid;

	// now clear the tile cache grid.
	for ( int j = 0; j < _wholeAreaSizeMIN*_wholeAreaSizeMIN; j++ )
	{
		tileCacheGrid[j].reset();
	}
//DEADCODE JON 4/27/00 	pHTextureGrid=new HTEXT[_wholeAreaSizeMIN*_wholeAreaSizeMIN];
//DEADCODE JON 4/27/00  	memset(pHTextureGrid,0xFF,_wholeAreaSizeMIN*_wholeAreaSizeMIN*sizeof(HTEXT));
	
	//DEADCODE JON 4/27/00 	memset(tileCacheGrid,0,sizeof(TileElement)*_wholeAreaSizeMIN*_wholeAreaSizeMIN);


	//Setup random table...
//DeadCode JON 12Sep00 	for (int x=0;x<256;landRnd[x++]=Math_Lib.rnd(SLong(0xFF)));

	//Setup route detail table
//DeadCode JON 12Sep00 	UByte* pResR=routeDetail;
//DeadCode JON 12Sep00 //DeadCode JON 3Aug00 	UByte* pResG=groundDetail;
//DeadCode JON 12Sep00 	for (x=0;x<wholeAreaSize;x++){
//DeadCode JON 12Sep00 		int tx=x-halfAreaSize;
//DeadCode JON 12Sep00 		Float dx=Float(tx); dx*=dx*Float(_blockWidth)*Float(_blockWidth);
//DeadCode JON 12Sep00 	 	for (int y=0;y<wholeAreaSize;y++){
//DeadCode JON 12Sep00 			int ty=y-halfAreaSize;
//DeadCode JON 12Sep00 			Float dy=Float(ty);
//DeadCode JON 12Sep00 			dy*=dy*Float(_blockWidth)*Float(_blockWidth);
//DeadCode JON 12Sep00 			dy+=dx;
//DeadCode JON 12Sep00 			_asm {
//DeadCode JON 12Sep00 			fld dy;
//DeadCode JON 12Sep00 			fsqrt;
//DeadCode JON 12Sep00 			fstp dy;
//DeadCode JON 12Sep00 			}
//DeadCode JON 12Sep00 			ty=int(dy);
//DeadCode JON 12Sep00 			//Fill in route detail grid
//DeadCode JON 12Sep00 			if (ty<_routeMPolySize) *pResR++=UByte(_doMPoly);
//DeadCode JON 12Sep00 			else if (ty<_routePolySize) *pResR++=UByte(_doPoly);
//DeadCode JON 12Sep00 			else if (ty<_routeLineSize) *pResR++=UByte(_doLine);
//DeadCode JON 12Sep00 			else *pResR++=UByte(_doNowt);
//DeadCode JON 12Sep00 			//Fill in land detali grid
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 			if (ty<_groundHighSize)
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 				*pResG++=UByte(_doHighGround);
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 			else if (ty<_groundMedSize)
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 			{
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 				ty-=_groundHighSize;
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 				ty<<=4;
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 				ty/=(_groundMedSize-_groundHighSize);
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 				ty++;
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 				if (ty>3) ty=254;	//overkill to make sure that the tiles
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 									//are reduced as much as possible
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 				else ty=0;
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 				*pResG++=UByte(ty);
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 			}
//DeadCode JON 12Sep00 //DeadCode JON 4Aug00 			else *pResG++=UByte(254);
//DeadCode JON 12Sep00 		}
//DeadCode JON 12Sep00 	}
//DeadCode JON 3Aug00 	highco=new DoPointStruc[256];
	blackingout=0;
	redingout=0;
	whitingout=0;
//DEADCODE PD 02/12/99 	currscreen=NULL;
	lastPx=lastPz=-1;
//deadcode JON 19/06/01		ResetLights();

	sun_screen_x = sun_screen_y = sun_glare = 0;				//RJS 20Apr00

	SHAPE.newprobecnt= 0;		//RJS 01Apr99

	InitialiseCloudTables();

	craterCnt = 0;												//RJS 18Nov99
	stompMapCnt = 0;											//RJS 30Nov99

	SetFogBand();

	gridOffs.reInit();
	cloudOffs.reInit();

	horizonImg = ImageMapDesc::init( 256, 256 );
	horizonImg->paletteindex = 2;

//DeadCode JON 9Jun00 	cloudImg0 = ImageMapDesc::init( 256, 256, false);
//DeadCode JON 9Jun00 	cloudImg1 = ImageMapDesc::init( 256, 256, false);
//DeadCode JON 9Jun00 	cloudImg2 = ImageMapDesc::init( 256, 256, false);

	cloudImg0 = ImageMapDesc::init( 128, 128 );
	cloudImg0->alpha = cloudImg0->body;
	cloudImg0->body = NULL;

//TempCode JON 26Sep00 	// now do the ace re-init for colour stuff... haha.
//TempCode JON 26Sep00 	float furthestTileSqMod;
//TempCode JON 26Sep00 	if ( Save_Data.detail_3d[DETAIL3D_HORIZONDIST] )
//TempCode JON 26Sep00 	{ // HIGH DISTANCE HORIZON
//TempCode JON 26Sep00 		furthestTileSqMod = 256.f/float((_horizonDist-1)*(_horizonDist-1));
//TempCode JON 26Sep00 	} else
//TempCode JON 26Sep00 	{
//TempCode JON 26Sep00 		furthestTileSqMod = 256.f/float((_halfAreaSizeMIN-1)*(_halfAreaSizeMIN-1));
//TempCode JON 26Sep00 	}
//TempCode JON 26Sep00 	UByte* col = cloudImg0->body;
//TempCode JON 26Sep00 	for ( int x = -64; x < 64; x++ )
//TempCode JON 26Sep00 		for ( int y = -64; y < 64; y++ )
//TempCode JON 26Sep00 		{
//TempCode JON 26Sep00 			float distSq = float(x*x + y*y);
//TempCode JON 26Sep00 			*col=F2UB_Clip( distSq*furthestTileSqMod );	
//TempCode JON 26Sep00 			col++;
//TempCode JON 26Sep00 		}

//DeadCode JON 26Sep00 	cloudImg1 = ImageMapDesc::init( 128, 128, false);
//DeadCode JON 26Sep00 	cloudImg2 = ImageMapDesc::init( 128, 128, false);

	for (int smkindex=0; smkindex < MaxSmokeClouds; smkindex++)
	{
		smkList[smkindex].active = 0;
		smkList[smkindex].weight = -1;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Exit
//Author		Paul.   
//Date			Thu 14 May 1998
//------------------------------------------------------------------------------
void LandScape::Exit()
{
//DeadCode JON 12Sep00 	if (gridCorners) delete[]gridCorners,gridCorners=NULL;
	if (gridCone) 
	{
		delete[]gridCone;
		gridCone=NULL;
	}
	if (horizCone) 
	{
		delete[]horizCone;
		horizCone=NULL;
	}
//DeadCode JON 12Sep00 	if (lightCone) delete[]lightCone,lightCone=NULL;
//DeadCode JON 12Sep00 	if (routeDetail) delete[]routeDetail,routeDetail=NULL;
//DeadCode JON 3Aug00 	if (groundDetail) delete[]groundDetail,groundDetail=NULL;
//DeadCode JON 12Sep00 	if (landRnd) 
//DeadCode JON 12Sep00 	{
//DeadCode JON 12Sep00 #pragma warnmsg ( "remove me" )
//DeadCode JON 12Sep00 		DbgMemTest3( landRnd );
//DeadCode JON 12Sep00 		delete[]landRnd;
//DeadCode JON 12Sep00 		landRnd=NULL;
//DeadCode JON 12Sep00 	}

	if (tileCoords) 
	{
		delete[]tileCoords;
		tileCoords=NULL;
	}
	if (pDataBlocks)
	{
		delete[]pDataBlocks;
		pDataBlocks=NULL;
	}
	if (polyList) 
	{
		delete[]polyList;
		polyList=NULL;
	}
	if (pointList)
	{
		delete[]pointList;
		pointList=NULL;
	}
//DEADCODE JON 4/26/00 	if (pLastGrid) delete[]pLastGrid,pLastGrid=NULL;
	if (tileCacheGrid) 
	{
		delete[]tileCacheGrid;
		tileCacheGrid=NULL;
		TileResList::theGrid=NULL;
	}
//DEADCODE JON 4/27/00 	if (pHTextureGrid) delete[]pHTextureGrid,pHTextureGrid=NULL;
//DeadCode JON 3Aug00 	if (highco) delete[]highco,highco=NULL;
//DeadCode JON 5Sep00 	if (softGrid) delete[]softGrid,softGrid=NULL;

	Three_Dee.nomorereallygetdata=false;

	delete [](UByteP)horizonImg;
	delete [](UByteP)cloudImg0;
//DeadCode JON 26Sep00 	delete [](UByteP)cloudImg1;
//DeadCode JON 26Sep00 	delete [](UByteP)cloudImg2;
	horizonImg = NULL;
	cloudImg0 = NULL;
//DeadCode JON 26Sep00 	cloudImg1 = NULL;
//DeadCode JON 26Sep00 	cloudImg2 = NULL;
}

void LandScape::SetFogBand()
{
	if ( Save_Data.detail_3d[DETAIL3D_HORIZONDIST] )
	{ // HIGH DISTANCE
		view_dist=_blockWidth*_horizonDist;
//		static float fudge = 0.9373f;
		g_lpLib3d->SetFogValues( 0.00002f, 0.9373f );//0.9973f );//0.88f );//0.25f );
	} else
	{ // LOW DISTANCE
		view_dist=_hirezDrawDist;
		g_lpLib3d->SetFogValues( 0.3f, 1.0f );//0.9f );
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetMist
//Author		Paul.   
//Date			Tue 9 Jun 1998
//------------------------------------------------------------------------------
//deadcode JON 19/06/01	void LandScape::SetMist(DoPointStruc& dp)
//deadcode JON 19/06/01	{
//DEADCODE PD 01/12/99 	//dp is untransformed point
//DEADCODE PD 01/12/99 	if (dp.bodyy.i<=_snowLine){
//DEADCODE PD 01/12/99 		dp.mist=0;
//DEADCODE PD 01/12/99 		if (dp.bodyy.i<=_mistTop){
//DEADCODE PD 01/12/99 			SLong temp=((dp.bodyy.i-_mistTop)<<8)/_mistTop;
//DEADCODE PD 01/12/99 			if (temp>0xFF) temp=0xFF;
//DEADCODE PD 01/12/99 			else if (temp<0) temp=0;
//DEADCODE PD 01/12/99 			temp=0xFF-temp;
//DEADCODE PD 01/12/99 			dp.snow=UByte(temp);
//DEADCODE PD 01/12/99 		}
//DEADCODE PD 01/12/99 		else dp.snow=0;
//DEADCODE PD 01/12/99 	}
//DEADCODE PD 01/12/99 	else if (dp.bodyy.i>=_snowLine+10000)	dp.mist=255;
//DEADCODE PD 01/12/99 	else
//DEADCODE PD 01/12/99 	{
//DEADCODE PD 01/12/99 	 	SLong temp=((dp.bodyy.i-_snowLine)<<8)/10000;
//DEADCODE PD 01/12/99 		if (temp>0xFF)		temp=0xFF;
//DEADCODE PD 01/12/99 		else if (temp<0)	temp=0;
//DEADCODE PD 01/12/99 		dp.mist=UByte(temp);
//DEADCODE PD 01/12/99 	}
//deadcode JON 19/06/01	}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PrintDebugs
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
void LandScape::PrintDebugs()
{/*
	UByte block[128];
	block[4]=UByte(0);
	SLong xof=(viewer_x&0x1FFFFF)>>10;	//0..2048
	SLong val=viewer_x>>(17+4);
	block[2]=UByte(val&0x7)+'1';		//x (lo)
	val>>=3;
	block[0]=UByte(val)+'1';			//x (hi)
	SLong zof=2047-((viewer_z&0x1FFFFF)>>10);
	val=viewer_z>>(17+4);
	block[3]=UByte(val&0x7)+'1';		//z (lo)
	val>>=3;
	block[1]=UByte(val)+'1';			//z (hi)
	Mono_Text.PrintAt(0,0,block);		//print block number
	sprintf((char*)block,"xoff %d ",xof);
	Mono_Text.PrintAt(0,1,block);
	sprintf((char*)block,"zoff %d ",zof);
	Mono_Text.PrintAt(0,2,block);
	val=viewer_hdg;
	val=((val&0xFFFF)*90)>>14;
	sprintf((char*)block,"hdg %3d",val);
	Mono_Text.PrintAt(0,3,block);		//print viewer heading
	sprintf((char*)block,"alt %dm ",(viewer_y/100));
	Mono_Text.PrintAt(0,4,block);		//print viewer altitude (meters)
*/}

inline void fpSinCos(ANGLES ang,Float& sinAng,Float& cosAng)
{
	int iang=ang;
	_asm
	{
	mov eax,iang;
	and eax,0x0000FFFF;
	fldpi;
	push eax;
	fild dword ptr ss:[esp];
	fmulp st(1),st;
	mov dword ptr ss:[esp],32768;
	fild dword ptr ss:[esp];
	fdivp st(1),st;
	fsincos;
	mov edx,cosAng;
	fstp qword ptr ds:[edx];
	mov edx,sinAng;
	fstp qword ptr ds:[edx];
	add esp,4;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoCloudLayer
//Author		Paul.   
//Date			Fri 23 Oct 1998
//------------------------------------------------------------------------------
//deadcode JON 19/06/01	void LandScape::DoCloudLayer()
//deadcode JON 19/06/01	{
/*	const Float CLOUD_DELTA=.002;
	struct SHCoords
	{
		Float X,Y,Z;	
		SLong flag;
	}
	HStripPtsA[]=
	{
		//outer edge points
		{-1,.202+CLOUD_DELTA,1,0},
		{0,.202+CLOUD_DELTA,1,0},
		{1,.202+CLOUD_DELTA,1,0},
		{1,.202+CLOUD_DELTA,0,0},
		{1,.202+CLOUD_DELTA,-1,0},
		{0,.202+CLOUD_DELTA,-1,0},
		{-1,.202+CLOUD_DELTA,-1,0},
		{-1,.202+CLOUD_DELTA,0,0},

		//end of solid area
		{0,.202,.5,1},
		{.3536,.202,.3536,1},
		{.5,.202,0,1},
		{.3536,.202,-.3536,1},
		{0,.202,-.5,1},
		{-.3536,.202,-.3536,1},
		{-.5,.202,0,1},
		{-.3536,.202,.3536,1},

		//end of transparent area
		{0,.202,.25,2},
		{.1768,.202,.1768,2},
		{.25,.202,0,2},
		{.1768,.202,-.1768,2},
		{0,.202,-.25,2},
		{-.1768,.202,-.1768,2},
		{-.25,.202,0,2},
		{-.1768,.202,.1768,2}
	},
	HStripPtsB[]=
	{
		//outer edge points
		{-1,.202-CLOUD_DELTA,1,0},
		{0,.202-CLOUD_DELTA,1,0},
		{1,.202-CLOUD_DELTA,1,0},
		{1,.202-CLOUD_DELTA,0,0},
		{1,.202-CLOUD_DELTA,-1,0},
		{0,.202-CLOUD_DELTA,-1,0},
		{-1,.202-CLOUD_DELTA,-1,0},
		{-1,.202-CLOUD_DELTA,0,0},

		//end of solid area
		{0,.202,.5,1},
		{.3536,.202,.3536,1},
		{.5,.202,0,1},
		{.3536,.202,-.3536,1},
		{0,.202,-.5,1},
		{-.3536,.202,-.3536,1},
		{-.5,.202,0,1},
		{-.3536,.202,.3536,1},

		//end of transparent area
		{0,.202,.25,2},
		{.1768,.202,.1768,2},
		{.25,.202,0,2},
		{.1768,.202,-.1768,2},
		{0,.202,-.25,2},
		{-.1768,.202,-.1768,2},
		{-.25,.202,0,2},
		{-.1768,.202,.1768,2}
	};

	struct SStripPoly
	{
		SLong v[3];
	}
	SolidPolys[]=
	{
//solid section polys
		{0,1,15},
		{15,1,8},
		{9,8,1},
		{2,9,1},
		{3,9,2},
		{3,10,9},
		{11,10,3},
		{4,11,3},
		{5,11,4},
		{12,11,5},
		{13,12,5},
		{6,13,5},
		{7,13,6},
		{14,13,7},
		{15,14,7},
		{0,15,7}
	},
	TransPolys[]=
	{
//transparent section polys
		{17,16,8},
		{9,17,8},
		{10,17,9},
		{18,17,10},
		{19,18,10},
		{11,19,10},
		{12,19,11},
		{20,19,12},
		{21,20,12},
		{13,21,12},
		{14,21,13},
		{22,21,14},
		{23,22,14},
		{15,23,14},
		{8,23,15},
		{16,23,8}
	};
		
	const SLong _stripPoints=sizeof(HStripPtsA)/sizeof(fpCOORDS3D);
	const SLong _solidPolys=sizeof(SolidPolys)/sizeof(SStripPoly);
	const SLong _transPolys=sizeof(TransPolys)/sizeof(SStripPoly);

	Float fvr=Float(view_range);
	Float fvy=Float(viewer_y)/Float(CEILING_ALT);

	//texture coordinate transformation matrix

	Float iMat[4];
	Float fSinHdg,fCosHdg;

	fpSinCos(-viewer_hdg,fSinHdg,fCosHdg);
	iMat[0]=iMat[3]=fCosHdg;
	iMat[1]=fSinHdg;
	iMat[2]=-fSinHdg;
		
	FPMATRIX 	mat,scale;
	Float 		*m=(Float*)&mat,
				*s=(Float*)&scale;

	_matrix.Generate(ANGLES_0Deg,View_Point->pitch,View_Point->roll,&mat);

	s[0]=fvr;
	s[1]=0;
	s[2]=0;

	s[3]=0;
	s[4]=Float(CEILING_ALT);
	s[5]=0;

	s[6]=0;
	s[7]=0;
	s[8]=fvr;

	_matrix.multiply(&scale,&mat);

	DoPointStruc* pdp=SHAPE.newco;
	SHCoords* psp=HStripPtsA;
	SWord ss=1024;

	Float ix=(viewer_x>>10)&SLong(ss-1),
			iy=(viewer_z>>10)&SLong(ss-1);

	for (SLong i=_stripPoints;i--;)
	{
		Float tu,tv,ttu,ttv;
		tu=(psp->X*ss);	//1 cloud texel per 81.92m
		tv=(psp->Z*ss);

		//2D rotate on texture coordinates
		ttu=tu*iMat[0]+tv*iMat[1];
		ttv=tu*iMat[2]+tv*iMat[3];

		Float py=psp->Y-fvy;
		pdp->bodyx.f=s[0]*psp->X+s[1]*py+s[2]*psp->Z;
		pdp->bodyy.f=s[3]*psp->X+s[4]*py+s[5]*psp->Z;
		pdp->bodyz.f=s[6]*psp->X+s[7]*py+s[8]*psp->Z;
		pdp->ix=SWord(ttu+ix);
		pdp->iy=SWord(ttv+iy);
		pdp->specular=-1;
		_matrix.SetClipFlags(*pdp);
		pdp->clipFlags&=~CF3D_PASTFARZ;
		pdp++;
		psp++;
	}

	psp=HStripPtsB;
	DoPointStruc* other_newco=pdp;
	for (i=_stripPoints;i--;)
	{
		Float tu,tv,ttu,ttv;
		tu=(psp->X*ss);	//1 cloud texel per 81.92m
		tv=(psp->Z*ss);

		//2D rotate on texture coordinates
		ttu=tu*iMat[0]+tv*iMat[1];
		ttv=tu*iMat[2]+tv*iMat[3];

		Float py=psp->Y-fvy;
		pdp->bodyx.f=s[0]*psp->X+s[1]*py+s[2]*psp->Z;
		pdp->bodyy.f=s[3]*psp->X+s[4]*py+s[5]*psp->Z;
		pdp->bodyz.f=s[6]*psp->X+s[7]*py+s[8]*psp->Z;
		pdp->ix=SWord(ttu+ix);
		pdp->iy=SWord(ttv+iy);
		pdp->specular=-1;
		_matrix.SetClipFlags(*pdp);
		pdp->clipFlags&=~CF3D_PASTFARZ;
		pdp++;
		psp++;
	}*/

/*	skyFogBegin=SLong(SHAPE.newco[8].bodyz.f);	//DEAD groundFogBegin;
	skyFogEnd=SLong(SHAPE.newco[0].bodyz.f);
	UByte saveR,saveG,saveB;
	SLong dummy;

	currscreen->DoGetFog(saveR,saveG,saveB,dummy,dummy);

	UByte fR,fG,fB;
	bool polysFlipped=viewer_y>_cloudLayerHeight?false:true;
	fR=currentLighting.horizonAtClouds.red();
	fG=currentLighting.horizonAtClouds.green();
	fB=currentLighting.horizonAtClouds.blue();
	currscreen->DoGammaCorr(fR,fG,fB);
	GreyPalette(&fR,&fG,&fB);
	currscreen->DoSetFog(saveR,saveG,saveB,skyFogBegin,skyFogEnd);
	currscreen->DoSetFog(fR,fG,fB);*/

	//solid section of cloud layer

/*	ImageMapDesc* pcloudno=Image_Map.GetImageMapPtr(CLOUDNO);

	for (i=0;i<_solidPolys;i++)
	{
		UWord andedFlags=SHAPE.newco[SolidPolys[i].v[0]].clipFlags&
						SHAPE.newco[SolidPolys[i].v[1]].clipFlags&
						SHAPE.newco[SolidPolys[i].v[2]].clipFlags;

		if (andedFlags==0)
		{
			DoPointStruc *p0,*p1,*p2;
			SWord	i0=HStripPtsA[SolidPolys[i].v[0]].flag==0?0xFF:0x00,
					i1=HStripPtsA[SolidPolys[i].v[1]].flag==0?0xFF:0x00,
					i2=HStripPtsA[SolidPolys[i].v[2]].flag==0?0xFF:0x00;
			p0=SHAPE.newco+SolidPolys[i].v[0];
			p1=SHAPE.newco+SolidPolys[i].v[1];
			p2=SHAPE.newco+SolidPolys[i].v[2];
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else						POLYGON.createpoly(pcloudno,IMAPPED_C);
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			POLYGON.drawpoly();
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else						POLYGON.createpoly(pcloudno,IMAPPED_C);
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			POLYGON.drawpoly();

			//and the other side of the cloud layer...
			p0=other_newco+SolidPolys[i].v[0];
			p1=other_newco+SolidPolys[i].v[1];
			p2=other_newco+SolidPolys[i].v[2];
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else						POLYGON.createpoly(pcloudno,IMAPPED_C);
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			POLYGON.drawpoly();
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else						POLYGON.createpoly(pcloudno,IMAPPED_C);
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			POLYGON.drawpoly();
		}
	}*/
	//transparent section of cloud layer

/*	currscreen->DoSetTranspFade(true);

	for (i=0;i<_transPolys;i++)
	{
		UWord andedFlags=SHAPE.newco[TransPolys[i].v[0]].clipFlags&
						SHAPE.newco[TransPolys[i].v[1]].clipFlags&
						SHAPE.newco[TransPolys[i].v[2]].clipFlags;

		if (andedFlags==0)
		{
			DoPointStruc *p0,*p1,*p2;
			SWord	i0=HStripPtsA[TransPolys[i].v[0]].flag==1?0xFF:0x00,
					i1=HStripPtsA[TransPolys[i].v[1]].flag==1?0xFF:0x00,
					i2=HStripPtsA[TransPolys[i].v[2]].flag==1?0xFF:0x00;
			p0=SHAPE.newco+TransPolys[i].v[0];
			p1=SHAPE.newco+TransPolys[i].v[1];
			p2=SHAPE.newco+TransPolys[i].v[2];
			if (!Save_Data.fSoftware)	POLYGON.createpoly(CLOUDNO);
			else
			{
				ImageMapDescPtr pmap=Image_Map.GetImageMapPtr(CLOUDNO);
				POLYGON.createpoly(pmap,IMAPPED_TF);
			}
			POLYGON.createvert(*p0,p0->ix,p0->iy,i0);
			if (polysFlipped)
			{
				POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
				POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
			}
			else
			{
				POLYGON.createvert(*p1,p1->ix,p1->iy,i1);
				POLYGON.createvert(*p2,p2->ix,p2->iy,i2);
			}
			POLYGON.drawpoly();
		}
	}
	currscreen->DoSetTranspFade(false);
	currscreen->DoSetFog(saveR,saveG,saveB,groundFogBegin,groundFogEnd);
	currscreen->DoSetFog(saveR,saveG,saveB);*/
//deadcode JON 19/06/01	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void LandScape::GetMinMaxAlt(AirStrucPtr ac,SLong& min,SLong& max)
{
	if (Three_Dee.pTMake==NULL) min=max=256000;
	else
	{
		ANGLES ac_hdg=ac->hdg;
		ac_hdg+=ANGLES_45Deg;
		ac_hdg=(Angles)((int)ac_hdg&0xC000);

		SWord dir;

		if (ac_hdg==ANGLES_0Deg)		dir=0;
		else if (ac_hdg==ANGLES_90Deg)	dir=1;
		else if (ac_hdg==ANGLES_180Deg)	dir=2;
		else							dir=3;

		Three_Dee.pTMake->GetMinMaxAlt(ac->World.X,ac->World.Z,dir,min,max);

		min*=_altitudeScale;
		max*=_altitudeScale;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InterpSLightRGB
//Author		Paul.   
//Date			Mon 18 Jan 1999
//------------------------------------------------------------------------------
void LandScape::InterpSLightRGB(	SLayerRGB& lowRgb,
									SLayerRGB& hiRgb,
									SLayerRGB& outRgb,
									ULong scale)
{
	ULong val;
	Float fs,omfs;
	fs=scale/65536.;
	omfs=1.-fs;
	val=ULong(Float(lowRgb.r)*fs+Float(hiRgb.r)*omfs);
	outRgb.r=(val>0xFFFF)?0xFFFF:val;
	val=ULong(Float(lowRgb.g)*fs+Float(hiRgb.g)*omfs);
	outRgb.g=(val>0xFFFF)?0xFFFF:val;
	val=ULong(Float(lowRgb.b)*fs+Float(hiRgb.b)*omfs);
	outRgb.b=(val>0xFFFF)?0xFFFF:val;
}

#define InterpLight(p1)\
InterpSLightRGB(pLowLight->##p1,pHighLight->##p1,\
currentLighting.##p1,scaleFactor);

//////////////////////////////////////////////////////////////////////
//
// Function:    

// Date:		10/9/00
// Author:		JON
//
//Description: Handles a possible teleport across the landscape (for u comms/replay chaps)
//
//////////////////////////////////////////////////////////////////////
void LandScape::PossibleTeleport()
{
	// right set up the center position
//TempCode JON 9Oct00 	Three_Dee.pMigLand->SetViewpoint(View_Point);
//TempCode JON 9Oct00 	Three_Dee.pMigLand->BigRebuild();
	ULong x = View_Point->World.X >> Grid_Base::WORLDSPACEMOD;
	ULong z = View_Point->World.Z >> Grid_Base::WORLDSPACEMOD;
#ifndef NDEBUG
	char blockStr[7];
	blockStr[6] = char(0);
	blockStr[5] = '1'+char(z%8);
	blockStr[3] = '1'+char((z/8)%8);
	blockStr[1] = '1'+char((z/64)%8);
	blockStr[4] = '1'+char(x%8);
	blockStr[2] = '1'+char((x/8)%8);
	blockStr[0] = '1'+char((x/64)%8);
#endif

	if (
			( abs( lastMeshDataX - x ) > 1 ) ||
			( abs( lastMeshDataZ - z ) > 1 )
		)
	{
		Three_Dee.pMigLand->BigInit(View_Point);
		Three_Dee.pTMake->Reinit(View_Point->World.X,View_Point->World.Z,g_lpLib3d);
		doneUpdateLandscape = true;
	}

}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RefreshLandscape
//Author		Paul.   
//Date			Tue 16 Feb 1999
//------------------------------------------------------------------------------
void LandScape::RefreshLandscape()
{
//DEADCODE JON 4/26/00 	if (pLastGrid) delete[]pLastGrid,pLastGrid=NULL;
	
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"RefreshLandscape: entry ");

	if (tileCacheGrid)
	{

		for ( int j = 0; j < _wholeAreaSizeMIN*_wholeAreaSizeMIN; j++ )
		{
			g_lpLib3d->FreeLandscapeTexture( tileCacheGrid[j].textHandle.textureHandle );
			tileCacheGrid[j].reset();
		}

//DeadCode MS 15Aug00 		Mono_Text.Print((UByte*)"RefreshLandscape: definatley clear land texts ");

//DeadCode MS 16Aug00 #pragma warnmsg ("don't put me in the version" )
//DeadCode MS 16Aug00 		for ( j = 0; j <256; j++ )
//DeadCode MS 16Aug00 			g_lpLib3d->FreeLandscapeTexture( j );

//DEADCODE JO  4/27/00 		memset(tileCacheGrid,0,sizeof(TileElement)*_wholeAreaSizeMIN*_wholeAreaSizeMIN);
	}
//DEADCODE JON 4/27/00 	if (pHTextureGrid) delete[]pHTextureGrid,pHTextureGrid=NULL;
//DeadCode MS 15Aug00  	Mono_Text.Print((UByte*)"RefreshLandscape: biginit ");

	Three_Dee.pMigLand->BigInit(View_Point);
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"RefreshLandscape: reinit ");

	Three_Dee.pTMake->Reinit(View_Point->World.X,View_Point->World.Z,g_lpLib3d);
//DEADCODE PD 01/12/99 	if (!Save_Data.fSoftware)	currscreen->DoFreeTextures();
//DEADCODE PD 01/12/99 	else						Three_Dee.pTMake->DoFreeTextures();	
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"RefreshLandscape: force horiz image update ");
 
//DeadCode JON 6Oct00 	g_lpLib3d->UnloadTexture( horizonImg );
//DeadCode MS 15Aug00 	Mono_Text.Print((UByte*)"RefreshLandscape: exit ");
	doneUpdateLandscape = true;		

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLighting
//Author		Paul.   
//Date			Mon 18 Jan 1999
//------------------------------------------------------------------------------
Bool LandScape::SetLighting(SLong curTime)			//RJS 15Jun99
{
	//curTime=current time in seconds
	
	const SLong fadeTime=3600;	//in seconds

	SLightingRGB *pLowLight,
				 *pHighLight;

	SLightingRGB preBadW;

	ULong scaleFactor;
	Bool	lightson = FALSE;									//RJS 15Jun99

	strongSun = false;													//RJS 31Aug00
	haveSunGlare = false;												//RJS 19Sep00

	if (View_Point && View_Point->viewnum.viewmode==VM_Map)
	{
//DeadCode JON 2Nov00 		currentLighting=*pMapL;
		return FALSE;											//RJS 15Jun99
	}

	if (curTime<MissManDawnTime()-fadeTime)		//it's night time
	{
		pLowLight=
		pHighLight=pNite;
		scaleFactor=0;
		lightson = TRUE;										//RJS 15Jun99
	}
	else if (curTime<=MissManDawnTime())			//it's morning
	{
		//current lighting is a combination of night/dawn
		pLowLight=pNite;
		pHighLight=pDawn;
		scaleFactor=((MissManDawnTime()-curTime)<<16)/fadeTime;
		lightson = TRUE;										//RJS 15Jun99
	}
	else if (curTime<MissManDawnTime()+fadeTime)
	{
		//current lighting is a combination of dawn/day
		pLowLight=pDawn;
		pHighLight=pDay;
//		scaleFactor=65536-(((MMC.dawntime+fadeTime-curTime)<<16)/fadeTime);
		scaleFactor=(((MissManDawnTime()+fadeTime-curTime)<<16)/fadeTime);

		strongSun = true;
		if (scaleFactor < 16384)	haveSunGlare = true;				//RJS 19Sep00
	}
	else if (curTime<MissManDuskTime()-fadeTime)
	{
	 	pLowLight=
		pHighLight=pDay;
		scaleFactor=0;

		strongSun = true;												//RJS 31Aug00
		haveSunGlare = true;											//RJS 19Sep00
	}
	else if (curTime<=MissManDuskTime())
	{
		//current lighting is a combination of day/dusk
		pLowLight=pDay;
		pHighLight=pDusk;
		scaleFactor=((MissManDuskTime()-curTime)<<16)/fadeTime;

		strongSun = true;												//RJS 19Sep00
		if (scaleFactor > 32768)	haveSunGlare = true;				//RJS 19Sep00
	}
	else if (curTime<=MissManDuskTime()+fadeTime)
	{
		//current lighting is a combination of dusk/night
		pLowLight=pDusk;
		pHighLight=pNite;
//		scaleFactor=65536-(((MMC.dusktime+fadeTime-curTime)<<16)/fadeTime);
		scaleFactor=(((MissManDuskTime()+fadeTime-curTime)<<16)/fadeTime);
		lightson = TRUE;										//RJS 15Jun99
	}
	else
	{
		pLowLight=
		pHighLight=pNite;
		scaleFactor=0;
		lightson = TRUE;										//RJS 15Jun99
	}

	if (scaleFactor==0)
	{
		currentLighting=*pHighLight;
//DEADCODE JON 4/11/00 		currentLighting=*pLowLight;
	}
	else
	{
//deadcode		InterpLight(horizonBase);
//deadcode		InterpLight(horizonMid);
//deadcode		InterpLight(horizonUnderClouds);
//deadcode		InterpLight(horizonAtClouds);
//deadcode		InterpLight(horizonAboveClouds);
//deadcode		InterpLight(horizonTop);
		InterpLight(landAmbientCollo);		InterpLight(landAmbientColhi);		InterpLight(landAmbientColamb);
		InterpLight(shadedAmbientCollo);	InterpLight(shadedAmbientColhi);	InterpLight(shadedAmbientColamb);
		InterpLight(staticAmbientCollo);	InterpLight(staticAmbientColhi);	InterpLight(staticAmbientColamb);
//DeadCode JON 2Nov00 		InterpLight(cockpitAmbientCollo);	InterpLight(cockpitAmbientColhi);	InterpLight(cockpitAmbientColamb);
//DeadCode JON 2Nov00 		InterpLight(effectsAmbientCollo);	InterpLight(effectsAmbientColhi);	InterpLight(effectsAmbientColamb);

		// and the back horizon fill stuff								//JON 4/20/00
		InterpLight(deepestSkyCol);
		InterpLight(otherSkyColSun);
		InterpLight(otherSkyColShade);
		InterpLight(cloudColSun);
		InterpLight(cloudColShade);
		InterpLight(horizonColSun);
		InterpLight(horizonColShade);
		InterpLight(fogColSun);
		InterpLight(fogColShade);

		InterpLight(sunCol);

		InterpLight(specularHighlight);

	}

	//account for bad weather here...

//DeadCode JON 2Nov00 	if (Save_Data.gamedifficulty[GD_WEATHEREFFECTS] && MissManCampSky().Conditions==1)
//DeadCode JON 2Nov00   	{
//DeadCode JON 2Nov00 		preBadW=currentLighting;
//DeadCode JON 2Nov00 		pLowLight=&preBadW;
//DeadCode JON 2Nov00 		pHighLight=pBadW;
//DeadCode JON 2Nov00 #pragma warnmsg( "look at weather lighting here - JON" )		
//DeadCode JON 2Nov00 		scaleFactor=32768;	//how bad 0==very bad 65536=clear weather
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 //deadcode		InterpLight(horizonBase);
//DeadCode JON 2Nov00 //deadcode		InterpLight(horizonMid);
//DeadCode JON 2Nov00 //deadcode		InterpLight(horizonUnderClouds);
//DeadCode JON 2Nov00 //deadcode		InterpLight(horizonAtClouds);
//DeadCode JON 2Nov00 //deadcode		InterpLight(horizonAboveClouds);
//DeadCode JON 2Nov00 //deadcode		InterpLight(horizonTop);
//DeadCode JON 2Nov00 		InterpLight(landAmbientCollo);		InterpLight(landAmbientColhi);		InterpLight(landAmbientColamb);
//DeadCode JON 2Nov00 		InterpLight(shadedAmbientCollo);	InterpLight(shadedAmbientColhi);	InterpLight(shadedAmbientColamb);
//DeadCode JON 2Nov00 		InterpLight(staticAmbientCollo);	InterpLight(staticAmbientColhi);	InterpLight(staticAmbientColamb);
//DeadCode JON 2Nov00 //DeadCode JON 2Nov00 		InterpLight(cockpitAmbientCollo);	InterpLight(cockpitAmbientColhi);	InterpLight(cockpitAmbientColamb);
//DeadCode JON 2Nov00 //DeadCode JON 2Nov00 		InterpLight(effectsAmbientCollo);	InterpLight(effectsAmbientColhi);	InterpLight(effectsAmbientColamb);
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 		// and the back horizon fill stuff								//JON 4/20/00
//DeadCode JON 2Nov00 		InterpLight(deepestSkyCol);
//DeadCode JON 2Nov00 		InterpLight(otherSkyColSun);
//DeadCode JON 2Nov00 		InterpLight(otherSkyColShade);
//DeadCode JON 2Nov00 		InterpLight(cloudColSun);
//DeadCode JON 2Nov00 		InterpLight(cloudColShade);
//DeadCode JON 2Nov00 		InterpLight(horizonColSun);
//DeadCode JON 2Nov00 		InterpLight(horizonColShade);
//DeadCode JON 2Nov00 		InterpLight(fogColSun);
//DeadCode JON 2Nov00 		InterpLight(fogColShade);
//DeadCode JON 2Nov00 		InterpLight(specularHighlight);
//DeadCode JON 2Nov00 
//DeadCode JON 2Nov00 	}
	//currentLighting contains the lighting info 
	//for the correct time of day and weather type

	// set the fog colour now... - actually set it in infinite strip - relative to the direction
//DeadCode JON 11Sep00 	Three_Dee.fogCol = (currentLighting.fogCol.red()<<16)+(currentLighting.fogCol.green()<<8)+currentLighting.fogCol.blue();

//DEADCODE PD 03/12/99 	if (mono3d)
//DEADCODE PD 03/12/99 	{
//DEADCODE PD 03/12/99 		currentLighting.landAmbientCol.g=
//DEADCODE PD 03/12/99 			currentLighting.landAmbientCol.b=
//DEADCODE PD 03/12/99 			currentLighting.landAmbientCol.r;
//DEADCODE PD 03/12/99 		currentLighting.shadedAmbientCol.g=
//DEADCODE PD 03/12/99 			currentLighting.shadedAmbientCol.b=
//DEADCODE PD 03/12/99 			currentLighting.shadedAmbientCol.r;
//DEADCODE PD 03/12/99 		currentLighting.staticAmbientCol.g=
//DEADCODE PD 03/12/99 			currentLighting.staticAmbientCol.b=
//DEADCODE PD 03/12/99 			currentLighting.staticAmbientCol.r;
//DEADCODE PD 03/12/99 		currentLighting.cockpitAmbientCol.g=
//DEADCODE PD 03/12/99 			currentLighting.cockpitAmbientCol.b=
//DEADCODE PD 03/12/99 			currentLighting.cockpitAmbientCol.r;
//DEADCODE PD 03/12/99 		currentLighting.effectsAmbientCol.g=
//DEADCODE PD 03/12/99 			currentLighting.effectsAmbientCol.b=
//DEADCODE PD 03/12/99 			currentLighting.effectsAmbientCol.r;
//DEADCODE PD 03/12/99 	}
	return lightson;												//RJS 15Jun99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetLights
//Author		Paul.   
//Date			Mon 1 Mar 1999
//------------------------------------------------------------------------------
//deadcode JON 19/06/01	void LandScape::ResetLights()
//deadcode JON 19/06/01	{
//DeadCode JON 20Sep00 	for (SLong i=0;i<_MaxLights;lightList[i++].timer=0){}
//deadcode JON 19/06/01	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddLight
//Author		Paul.   
//Date			Mon 1 Mar 1999
//------------------------------------------------------------------------------
//deadcode JON 19/06/01	void LandScape::AddLight(SLandLight* newlight)
//deadcode JON 19/06/01	{
//DeadCode JON 20Sep00 	for (SLong i=0;i<_MaxLights;i++)
//DeadCode JON 20Sep00 		if (lightList[i].timer==0)
//DeadCode JON 20Sep00 			break;
//DeadCode JON 20Sep00 	if (i<_MaxLights)
//DeadCode JON 20Sep00 		lightList[i]=*newlight;
//deadcode JON 19/06/01	}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessLights
//Author		Paul.   
//Date			Mon 1 Mar 1999
//------------------------------------------------------------------------------
//DeadCode JON 20Sep00 void LandScape::ProcessLights(SLong ox,SLong oz)
//DeadCode JON 20Sep00 {
//DeadCode JON 20Sep00 #pragma warnmsg ( "ProcessLights" )
//DeadCode JON 21Aug00 	return;
//DeadCode JON 21Aug00 	SLong wholeAreaSize;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	SLong thisTime=View_Point->FrameTime();
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	UByte actTbl[_MaxLights];
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	UWord addTo=0;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	UByte *pGridCone,*pLightCone;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	lightsActive=0;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	for (SLong i=0;i<_MaxLights;i++)
//DeadCode JON 21Aug00 	{
//DeadCode JON 21Aug00 		if (lightList[i].timer!=0 &&
//DeadCode JON 21Aug00 			(lightList[i].timer-=thisTime)>0)
//DeadCode JON 21Aug00 			actTbl[lightsActive++]=UByte(i);
//DeadCode JON 21Aug00 		else
//DeadCode JON 21Aug00 			if (lightList[i].timer!=0) lightList[i].timer=0;
//DeadCode JON 21Aug00 	}
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	if (lightsActive==0) return;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	for (i=0;i<_wholeAreaSizeMAX;lightTable[i++].numLights=0){}
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 //	wholeAreaSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?_wholeAreaSizeMAX:_wholeAreaSizeMIN;
//DeadCode JON 21Aug00 	wholeAreaSize=_wholeAreaSizeMIN;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	pGridCone=gridCone;
//DeadCode JON 21Aug00 	pLightCone=lightCone;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 	for (SLong row=0;row<wholeAreaSize;row++)
//DeadCode JON 21Aug00 	{
//DeadCode JON 21Aug00 		SLong ix=ox;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 		for (SLong col=0;col<wholeAreaSize;col++)
//DeadCode JON 21Aug00 		{
//DeadCode JON 21Aug00 			if (*pGridCone)
//DeadCode JON 21Aug00 			{
//DeadCode JON 21Aug00 				//check this cell against active light list
//DeadCode JON 21Aug00 				SLong cx0,cx1,cz0,cz1;
//DeadCode JON 21Aug00 				SLong lx0,lx1,lz0,lz1;
//DeadCode JON 21Aug00 				SLong lrange;
//DeadCode JON 21Aug00 				bool anyAdded=false;
//DeadCode JON 21Aug00 					
//DeadCode JON 21Aug00 				for (SLong lights=0;lights<lightsActive;lights++)
//DeadCode JON 21Aug00 				{
//DeadCode JON 21Aug00 					SLong index=actTbl[lights];
//DeadCode JON 21Aug00 					lrange=lightList[index].range;
//DeadCode JON 21Aug00 					SLong dx=lightList[index].pos.X-ix-_halfBlockWidth;
//DeadCode JON 21Aug00 					if (dx<0) dx=-dx;
//DeadCode JON 21Aug00 					if (dx<_blockWidth)
//DeadCode JON 21Aug00 					{
//DeadCode JON 21Aug00 						SLong dz=lightList[index].pos.Z-oz-_halfBlockWidth;
//DeadCode JON 21Aug00 						if (dz<0) dz=-dz;
//DeadCode JON 21Aug00 						if (dz<_blockWidth)
//DeadCode JON 21Aug00 						{
//DeadCode JON 21Aug00 							bool lightIn=false;
//DeadCode JON 21Aug00 							lx0=lx1=lightList[index].pos.X;
//DeadCode JON 21Aug00 							lz0=lz1=lightList[index].pos.Z;
//DeadCode JON 21Aug00 							lx0-=lrange;
//DeadCode JON 21Aug00 							lz0-=lrange;
//DeadCode JON 21Aug00 							lx1+=lrange;
//DeadCode JON 21Aug00 							lz1+=lrange;
//DeadCode JON 21Aug00 							cx0=ix;
//DeadCode JON 21Aug00 							cx1=ix+_blockWidth;
//DeadCode JON 21Aug00 							cz0=oz;
//DeadCode JON 21Aug00 							cz1=oz+_blockWidth;
//DeadCode JON 21Aug00 							if (lrange>_blockWidth)
//DeadCode JON 21Aug00 							{
//DeadCode JON 21Aug00 								//check to see if this tile lies inside the
//DeadCode JON 21Aug00 								//area covered by the light
//DeadCode JON 21Aug00 								if (cx0>=lx0 && cx0<=lx1 && cz0>=lz0 && cz0<=lz1) lightIn=true;
//DeadCode JON 21Aug00 								if (!lightIn && cx1>=lx0 && cx1<=lx1 && cz0>=lz0 && cz0<=lz1) lightIn=true;
//DeadCode JON 21Aug00 								if (!lightIn && cx1>=lx0 && cx1<=lx1 && cz1>=lz0 && cz1<=lz1) lightIn=true;
//DeadCode JON 21Aug00 								if (!lightIn && cx0>=lx0 && cx0<=lx1 && cz1>=lz0 && cz1<=lz1) lightIn=true;
//DeadCode JON 21Aug00 							}
//DeadCode JON 21Aug00 							else
//DeadCode JON 21Aug00 							{
//DeadCode JON 21Aug00 								//check to see if this light lies inside the
//DeadCode JON 21Aug00 								//area covered by the tile
//DeadCode JON 21Aug00 								if (lx0>=cx0 && lx0<=cx1 && lz0>=cz0 && lz0<=cz1) lightIn=true;
//DeadCode JON 21Aug00 								if (!lightIn && lx1>=cx0 && lx1<=cx1 && lz0>=cz0 && lz0<=cz1) lightIn=true;
//DeadCode JON 21Aug00 								if (!lightIn && lx1>=cx0 && lx1<=cx1 && lz1>=cz0 && lz1<=cz1) lightIn=true;
//DeadCode JON 21Aug00 								if (!lightIn && lx0>=cx0 && lx0<=cx1 && lz1>=cz0 && lz1<=cz1) lightIn=true;
//DeadCode JON 21Aug00 							}
//DeadCode JON 21Aug00 							if (lightIn)
//DeadCode JON 21Aug00 							{
//DeadCode JON 21Aug00 								//find a spare light table entry to use
//DeadCode JON 21Aug00 								UWord thisOne=lightTable[addTo].numLights;
//DeadCode JON 21Aug00 								lightTable[addTo].lightIndices[thisOne++]=index;
//DeadCode JON 21Aug00 								lightTable[addTo].numLights=thisOne;
//DeadCode JON 21Aug00 								anyAdded=true;
//DeadCode JON 21Aug00 							}
//DeadCode JON 21Aug00 						}
//DeadCode JON 21Aug00 					}
//DeadCode JON 21Aug00 				}
//DeadCode JON 21Aug00 				if (anyAdded)
//DeadCode JON 21Aug00 				{
//DeadCode JON 21Aug00 					*pLightCone=UByte(addTo);
//DeadCode JON 21Aug00 					addTo++;
//DeadCode JON 21Aug00 					if (addTo==_wholeAreaSizeMAX)
//DeadCode JON 21Aug00 						return;
//DeadCode JON 21Aug00 				}
//DeadCode JON 21Aug00 			}
//DeadCode JON 21Aug00 			else *pLightCone=0xFF;
//DeadCode JON 21Aug00 
//DeadCode JON 21Aug00 			pGridCone++;
//DeadCode JON 21Aug00 			pLightCone++;
//DeadCode JON 21Aug00 			ix+=_blockWidth;
//DeadCode JON 21Aug00 		}
//DeadCode JON 21Aug00 		oz+=_blockWidth;
//DeadCode JON 21Aug00 	}	
//DeadCode JON 20Sep00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GroundHuggingAltitude
//Author		Paul.   
//Date			Wed 3 Mar 1999
//------------------------------------------------------------------------------
SLong LandScape::GroundHuggingAltitude(MobileItem* itemPtr)
{
	if (itemPtr->World.Y>HIGHESTGROUND) return 0;

	SLong x=(itemPtr->World.X&~ULong(_blockWidth-1))+(_blockWidth>>1);
	SLong y=itemPtr->World.Y;
	SLong z=(itemPtr->World.Z&~ULong(_blockWidth-1))+(_blockWidth>>1);

	SLong maxAlt,thisAlt;

	//always test central tile
	maxAlt=_Collide.RoughGroundAltitude(x,y,z);

	if (y+FT_2000>maxAlt) return 0;

	UWord heading=itemPtr->hdg;

	if (heading<=UWord(ANGLES_45Deg) ||
		heading>UWord(-ANGLES_45Deg))
	{
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
	}
	else if (heading>UWord(ANGLES_45Deg) &&
			heading<=UWord(ANGLES_90Deg)+UWord(ANGLES_45Deg))
	{
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
	}
	else if (heading>UWord(ANGLES_90Deg)+UWord(ANGLES_45Deg) &&
			heading<=UWord(ANGLES_180Deg)-UWord(ANGLES_45Deg))
	{
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x+_blockWidth,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
	}
	else
	{
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z+_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
		thisAlt=_Collide.RoughGroundAltitude(x-_blockWidth,y,z-_blockWidth);
		if (thisAlt>maxAlt) maxAlt=thisAlt;
	}
	return maxAlt;
}


//
// (wx,wz) are world coordinates (in cm) for top left corner of the tile
// TILE_WH gives the dimensions of the sample area
//
R3DVALUE LandScape::layer00table[512];	//normal
R3DVALUE LandScape::layer01table[512];	//normal
R3DVALUE LandScape::layer02table[512];	//normal
R3DVALUE LandScape::layer10table[512];	//inverted
R3DVALUE LandScape::layer11table[512];	//inverted
R3DVALUE LandScape::layer12table[512];	//inverted
LandScape::LOCALVERT LandScape::vert[TILE_WH<<1];

inline UByte Noise2(UByte a,UByte b) {return shape::RandTable[0xFF&(shape::RandTable[a]+b)];}
inline UWord Noise1(UByte a) {return shape::RandTable[a];}
//
//oriPts is a 2x2 grid of the original point set.
//newPtr is a 3x3 grid that will contain new points
//
void LandScape::Zoom00(UWord *oriPts,UWord *newPts,UWord scale)
{
	UWord newVal;
	//copy over original points
	newPts[NEW_TL]=oriPts[OLD_TL];
	newPts[NEW_TR]=oriPts[OLD_TR];
	newPts[NEW_BL]=oriPts[OLD_BL];
	newPts[NEW_BR]=oriPts[OLD_BR];
	//center point is average of corner points + random value
	newVal=oriPts[OLD_TL]+oriPts[OLD_TR]+oriPts[OLD_BL]+oriPts[OLD_BR];
	newPts[NEW_MM]=(newVal>>2)+(Noise1(newVal)>>scale);
	//top edge point is average of original top edge points + random value
	newVal=oriPts[OLD_TL]+oriPts[OLD_TR];
	newPts[NEW_TM]=(newVal>>1)+(Noise1(newVal)>>scale);
	//bottom edge point is average of original bottom edge points + random value
	newVal=oriPts[OLD_BL]+oriPts[OLD_BR];
	newPts[NEW_BM]=(newVal>>1)+(Noise1(newVal)>>scale);
	//left edge point is average of original left edge points + random value
	newVal=oriPts[OLD_TL]+oriPts[OLD_BL];
	newPts[NEW_ML]=(newVal>>1)+(Noise1(newVal)>>scale);
	//right edge point is average of original right edge points + random value
	newVal=oriPts[OLD_TR]+oriPts[OLD_BR];
	newPts[NEW_MR]=(newVal>>1)+(Noise1(newVal)>>scale);
}
//
// same as Zoom00 but lhs edge is not built
//
void LandScape::Zoom01(UWord *oriPts,UWord *newPts,UWord scale)
{
	UWord newVal;
	//copy over original points
	newPts[NEW_TR]=oriPts[OLD_TR];
	newPts[NEW_BR]=oriPts[OLD_BR];
	//center point is average of corner points + random value
	newVal=oriPts[OLD_TL]+oriPts[OLD_TR]+oriPts[OLD_BL]+oriPts[OLD_BR];
	newPts[NEW_MM]=(newVal>>2)+(Noise1(newVal)>>scale);
	//top edge point is average of original top edge points + random value
	newVal=oriPts[OLD_TL]+oriPts[OLD_TR];
	newPts[NEW_TM]=(newVal>>1)+(Noise1(newVal)>>scale);
	//bottom edge point is average of original bottom edge points + random value
	newVal=oriPts[OLD_BL]+oriPts[OLD_BR];
	newPts[NEW_BM]=(newVal>>1)+(Noise1(newVal)>>scale);
	//right edge point is average of original right edge points + random value
	newVal=oriPts[OLD_TR]+oriPts[OLD_BR];
	newPts[NEW_MR]=(newVal>>1)+(Noise1(newVal)>>scale);
}
//
// Same as Zoom00 but top edge is not built
//
void LandScape::Zoom02(UWord *oriPts,UWord *newPts,UWord scale)
{
	UWord newVal;
	//copy over original points
	newPts[NEW_BL]=oriPts[OLD_BL];
	newPts[NEW_BR]=oriPts[OLD_BR];
	//center point is average of corner points + random value
	newVal=oriPts[OLD_TL]+oriPts[OLD_TR]+oriPts[OLD_BL]+oriPts[OLD_BR];
	newPts[NEW_MM]=(newVal>>2)+(Noise1(newVal)>>scale);
	//bottom edge point is average of original bottom edge points + random value
	newVal=oriPts[OLD_BL]+oriPts[OLD_BR];
	newPts[NEW_BM]=(newVal>>1)+(Noise1(newVal)>>scale);
	//left edge point is average of original left edge points + random value
	newVal=oriPts[OLD_TL]+oriPts[OLD_BL];
	newPts[NEW_ML]=(newVal>>1)+(Noise1(newVal)>>scale);
	//right edge point is average of original right edge points + random value
	newVal=oriPts[OLD_TR]+oriPts[OLD_BR];
	newPts[NEW_MR]=(newVal>>1)+(Noise1(newVal)>>scale);
}
//
// Same as Zoom00 but top & lhs edges are not built
//
void LandScape::Zoom03(UWord *oriPts,UWord *newPts,UWord scale)
{
	UWord newVal;
	//copy over original points
	newPts[NEW_BR]=oriPts[OLD_BR];
	//center point is average of corner points + random value
	newVal=oriPts[OLD_TL]+oriPts[OLD_TR]+oriPts[OLD_BL]+oriPts[OLD_BR];
	newPts[NEW_MM]=(newVal>>2)+(Noise1(newVal)>>scale);
	//bottom edge point is average of original bottom edge points + random value
	newVal=oriPts[OLD_BL]+oriPts[OLD_BR];
	newPts[NEW_BM]=(newVal>>1)+(Noise1(newVal)>>scale);
	//right edge point is average of original right edge points + random value
	newVal=oriPts[OLD_TR]+oriPts[OLD_BR];
	newPts[NEW_MR]=(newVal>>1)+(Noise1(newVal)>>scale);
}
//
// Double the resolution of a set of height data for clouds
//
void LandScape::DoubleRez(UWord *oriPts,UWord scale,UWord*& newPts)
{
	if (!newPts) newPts=new UWord[TILE_WH*TILE_WH];
	Zoom00(oriPts,newPts,scale);
	for (int i=2;i<TILE_WH-1;i+=2)
		Zoom01(oriPts+(i>>1),newPts+i,scale);
	for (i=2;i<TILE_WH-1;i+=2)
	{
		Zoom02(oriPts+(i>>1)*TILE_WH,newPts+i*TILE_WH,scale);
		for (int j=2;j<TILE_WH-1;j+=2)
			Zoom03(oriPts+(i>>1)*TILE_WH+(j>>1),newPts+i*TILE_WH+j,scale);
	}
}
//
// Generate top level point data (no interpolation
//
void LandScape::MakeTopLevel(SLong wx,SLong wz,UWord*& newPts)
{
	UWord *ptr;
	//original samlples are every 1.3km
	wx>>=17;
	wz>>=17;
	if (!newPts) newPts=new UWord[TILE_WH*TILE_WH];
	ptr=newPts;
	for (SLong i=TILE_WH;i>0;i--,wz++)
		for (SLong j=TILE_WH,wx2=wx;j>0;j--,wx2++)
			*ptr++=Noise2(wz,wx2);
}
//
// Generate all levels of data for the cloud layer
//
//void LandScape::MakeAllLevels(SLong wx,SLong wz,UWord**ppData)
//{
//	MakeTopLevel(wx,wz,ppData[0]);
//	for (UWord scale=1;scale<7;scale++)
//		DoubleRez(ppData[scale-1]+TILE_OFFX+TILE_OFFZ,scale,ppData[scale]);
//}
//
// Initialise lookup tables used for cloud layers
//
void LandScape::InitialiseCloudTables()
{
	for (SLong i=0;i<512;i++)
	{
		R3DVALUE v=R3DVALUE(i)*100;
//		R3DVALUE v=R3DVALUE(i-50<0?0:i-50);
		layer10table[i]=-(layer00table[i]=ALT_SCALE00*v);
		layer11table[i]=-(layer01table[i]=ALT_SCALE01*v);
		layer12table[i]=-(layer02table[i]=ALT_SCALE02*v);
	}
	pLevels[0]=
		pLevels[1]=
		pLevels[2]=
		pLevels[3]=
		pLevels[4]=
		pLevels[5]=
		pLevels[6]=
		pLevels[7]=NULL;
	scaleBase[0].X=
		scaleBase[1].X=
		scaleBase[2].X=
		scaleBase[3].X=
		scaleBase[4].X=
		scaleBase[5].X=
		scaleBase[6].X=
		scaleBase[7].X=0x7FFFFFFF;
}
//
// Render a single level of the data
//
//DEADCODE JON 5/24/00 void LandScape::RenderLevel00(const COORDS3D& base,UWord *pntArray,UWord scale,R3DVALUE *vals)
//DEADCODE JON 5/24/00 {
//DEADCODE JON 5/24/00 #ifndef _REDO_ME1_
//DEADCODE JON 5/24/00 	R3DVERTEX *pRVert,*pListA,*pListB;
//DEADCODE JON 5/24/00 	UWord *pPntsA,*pPntsB;
//DEADCODE JON 5/24/00 	COORDS3D crdsA,crdsB;
//DEADCODE JON 5/24/00 	ImageMapDesc *pImg;
//DEADCODE JON 5/24/00 	SLong step;
//DEADCODE JON 5/24/00 	SWord halfMapWidth,halfMapHeight;
//DEADCODE JON 5/24/00 	SWord widthMask,heightMask;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	step=((4096<<5)>>scale);
//DEADCODE JON 5/24/00 	pImg=Image_Map.GetImageMapPtr(CLOUDNO);
//DEADCODE JON 5/24/00 	halfMapWidth=pImg->w>>1;
//DEADCODE JON 5/24/00 	halfMapHeight=pImg->h>>1;
//DEADCODE JON 5/24/00 	widthMask=(pImg->w)-1;
//DEADCODE JON 5/24/00 	heightMask=(pImg->h)-1;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	g_lpLib3d->PushMatrix(MATRIX_OBJECT);
//DEADCODE JON 5/24/00 	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	pRVert=new R3DVERTEX[TILE_WH*TILE_WH];
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	pListA=pRVert;
//DEADCODE JON 5/24/00 	pPntsA=pntArray;
//DEADCODE JON 5/24/00 	crdsA.X=base.X;
//DEADCODE JON 5/24/00 	crdsA.Y=base.Y;
//DEADCODE JON 5/24/00 	crdsA.Z=base.Z;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	pListB=pRVert+TILE_WH*(TILE_WH-1);
//DEADCODE JON 5/24/00 	pPntsB=pntArray+TILE_WH*(TILE_WH-1);
//DEADCODE JON 5/24/00 	crdsB.X=base.X;
//DEADCODE JON 5/24/00 	crdsB.Y=base.Y;
//DEADCODE JON 5/24/00 	crdsB.Z=base.Z+(TILE_WH-1)*step;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	pListA[0].x=crdsA.X;
//DEADCODE JON 5/24/00 	pListA[0].y=crdsA.Y+pPntsA[0];
//DEADCODE JON 5/24/00 	pListA[0].z=crdsA.Z;
//DEADCODE JON 5/24/00 	pListA[0].ix=0;
//DEADCODE JON 5/24/00 	pListA[0].iy=0;
//DEADCODE JON 5/24/00 	pListB[0].x=crdsB.X;
//DEADCODE JON 5/24/00 	pListB[0].y=crdsB.Y+pPntsB[0];
//DEADCODE JON 5/24/00 	pListB[0].z=crdsB.Z;
//DEADCODE JON 5/24/00 	pListB[0].ix=0;
//DEADCODE JON 5/24/00 	pListB[0].iy=0;
//DEADCODE JON 5/24/00 	for (int i=2;i<TILE_WH;i+=2)
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		crdsA.X+=step;
//DEADCODE JON 5/24/00 		pListA[i-1].x=crdsA.X;
//DEADCODE JON 5/24/00 		pListA[i-1].z=crdsA.Z;
//DEADCODE JON 5/24/00 		pListA[i-1].ix=(pListA[i-2].ix+halfMapWidth)&widthMask;
//DEADCODE JON 5/24/00 		pListA[i-1].iy=pListA[i-2].iy;
//DEADCODE JON 5/24/00 		crdsA.X+=step;
//DEADCODE JON 5/24/00 		pListA[i].x=crdsA.X;
//DEADCODE JON 5/24/00 		pListA[i].y=crdsA.Y+pPntsA[i];
//DEADCODE JON 5/24/00 		pListA[i].z=crdsA.Z;
//DEADCODE JON 5/24/00 		pListA[i].ix=(pListA[i-1].ix+halfMapWidth)&widthMask;
//DEADCODE JON 5/24/00 		pListA[i].iy=pListA[i-1].iy;
//DEADCODE JON 5/24/00 		pListA[i-1].y=.5f*(pListA[i].y+pListA[i-2].y);
//DEADCODE JON 5/24/00 		crdsB.X+=step;
//DEADCODE JON 5/24/00 		pListB[i-1].x=crdsB.X;
//DEADCODE JON 5/24/00 		pListB[i-1].z=crdsB.Z;
//DEADCODE JON 5/24/00 		pListB[i-1].ix=(pListB[i-2].ix+halfMapWidth)&widthMask;
//DEADCODE JON 5/24/00 		pListB[i-1].iy=pListB[i-2].iy;
//DEADCODE JON 5/24/00 		crdsB.X+=step;
//DEADCODE JON 5/24/00 		pListB[i].x=crdsB.X;
//DEADCODE JON 5/24/00 		pListB[i].y=crdsB.Y+pPntsB[i];
//DEADCODE JON 5/24/00 		pListB[i].z=crdsB.Z;
//DEADCODE JON 5/24/00 		pListB[i].ix=(pListB[i-1].ix+halfMapWidth)&widthMask;
//DEADCODE JON 5/24/00 		pListB[i].iy=pListB[i-1].iy;
//DEADCODE JON 5/24/00 		pListB[i-1].y=.5f*(pListB[i].y+pListB[i-2].y);
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	crdsA.X=base.X;
//DEADCODE JON 5/24/00 	crdsA.Y=base.Y;
//DEADCODE JON 5/24/00 	crdsA.Z=base.Z;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	pListB=pRVert+(TILE_WH-1);
//DEADCODE JON 5/24/00 	pPntsB=pntArray+(TILE_WH-1);
//DEADCODE JON 5/24/00 	crdsB.X=base.X+step*(TILE_WH-1);
//DEADCODE JON 5/24/00 	crdsB.Y=base.Y;
//DEADCODE JON 5/24/00 	crdsB.Z=base.Z;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	int index=TILE_WH*2;
//DEADCODE JON 5/24/00 	for (i=2;i<TILE_WH;i+=2,index+=TILE_WH)
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		int iprev=index-TILE_WH;
//DEADCODE JON 5/24/00 		int iprev2=iprev-TILE_WH;
//DEADCODE JON 5/24/00 		crdsA.Z+=step;
//DEADCODE JON 5/24/00 		pListA[iprev].x=crdsA.X;
//DEADCODE JON 5/24/00 		pListA[iprev].z=crdsA.Z;
//DEADCODE JON 5/24/00 		pListA[iprev].ix=pListA[iprev2].ix;
//DEADCODE JON 5/24/00 		pListA[iprev].iy=(pListA[iprev2].iy+halfMapHeight)&heightMask;
//DEADCODE JON 5/24/00 		crdsA.Z+=step;
//DEADCODE JON 5/24/00 		pListA[index].x=crdsA.X;
//DEADCODE JON 5/24/00 		pListA[index].y=crdsA.Y+pPntsA[index];
//DEADCODE JON 5/24/00 		pListA[index].z=crdsA.Z;
//DEADCODE JON 5/24/00 		pListA[index].ix=pListA[iprev].ix;
//DEADCODE JON 5/24/00 		pListA[index].iy=(pListA[iprev].iy+halfMapHeight)&heightMask;
//DEADCODE JON 5/24/00 		pListA[iprev].y=.5f*(pListA[index].y+pListA[iprev2].y);
//DEADCODE JON 5/24/00 		crdsB.Z+=step;
//DEADCODE JON 5/24/00 		pListB[iprev].x=crdsB.X;
//DEADCODE JON 5/24/00 		pListB[iprev].z=crdsB.Z;
//DEADCODE JON 5/24/00 		pListB[iprev].ix=pListB[iprev2].ix;
//DEADCODE JON 5/24/00 		pListB[iprev].iy=(pListB[iprev2].iy+halfMapHeight)&heightMask;
//DEADCODE JON 5/24/00 		crdsB.Z+=step;
//DEADCODE JON 5/24/00 		pListB[index].x=crdsB.X;
//DEADCODE JON 5/24/00 		pListB[index].y=crdsB.Y+pPntsB[index];
//DEADCODE JON 5/24/00 		pListB[index].z=crdsB.Z;
//DEADCODE JON 5/24/00 		pListB[index].ix=pListB[iprev].ix;
//DEADCODE JON 5/24/00 		pListB[index].iy=(pListB[iprev].iy+halfMapHeight)&heightMask;
//DEADCODE JON 5/24/00 		pListB[iprev].y=.5f*(pListB[index].y+pListB[iprev2].y);
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	crdsA.X=base.X+step;
//DEADCODE JON 5/24/00 	crdsA.Y=base.Y;
//DEADCODE JON 5/24/00 	crdsA.Z=base.Z+step;
//DEADCODE JON 5/24/00 	crdsB=crdsA;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	for (i=1;i<TILE_WH-1;i++)
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		int index=i*TILE_WH;
//DEADCODE JON 5/24/00 		crdsA=crdsB;
//DEADCODE JON 5/24/00 		crdsB.Z+=step;
//DEADCODE JON 5/24/00 		for (int j=1;j<TILE_WH-1;j++)
//DEADCODE JON 5/24/00 		{
//DEADCODE JON 5/24/00 			pListA[index+j].x=crdsA.X;
//DEADCODE JON 5/24/00 			pListA[index+j].y=crdsA.Y+pPntsA[index+j];
//DEADCODE JON 5/24/00 			pListA[index+j].z=crdsA.Z;
//DEADCODE JON 5/24/00 			pListA[index+j].ix=(pListA[index+j-1].ix+halfMapWidth)&widthMask;
//DEADCODE JON 5/24/00 			pListA[index+j].iy=(pListA[index+j-TILE_WH].iy+halfMapHeight)&heightMask;
//DEADCODE JON 5/24/00 			crdsA.X+=step;			
//DEADCODE JON 5/24/00 		}
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	for (i=0;i<TILE_WH-1;i++)
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		int index=i*TILE_WH;
//DEADCODE JON 5/24/00 		for (int j=index;j<index+TILE_WH-1;j++)
//DEADCODE JON 5/24/00 		{
//DEADCODE JON 5/24/00 			R3DVERTEX *pVB;
//DEADCODE JON 5/24/00 			g_lpLib3d->BeginPoly(HMATERIAL(pImg),3,pVB);
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j];
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j+1];
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j+TILE_WH+1];
//DEADCODE JON 5/24/00 			g_lpLib3d->EndPoly();
//DEADCODE JON 5/24/00 			g_lpLib3d->BeginPoly(HMATERIAL(pImg),3,pVB);
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j];
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j+TILE_WH+1];
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j+TILE_WH];
//DEADCODE JON 5/24/00 			g_lpLib3d->EndPoly();
//DEADCODE JON 5/24/00 			g_lpLib3d->BeginPoly(HMATERIAL(pImg),3,pVB);
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j];
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j+TILE_WH+1];
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j+1];
//DEADCODE JON 5/24/00 			g_lpLib3d->EndPoly();
//DEADCODE JON 5/24/00 			g_lpLib3d->BeginPoly(HMATERIAL(pImg),3,pVB);
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j];
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j+TILE_WH];
//DEADCODE JON 5/24/00 			*pVB++=pRVert[j+TILE_WH+1];
//DEADCODE JON 5/24/00 			g_lpLib3d->EndPoly();
//DEADCODE JON 5/24/00 		}
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 	delete[]pRVert;
//DEADCODE JON 5/24/00 	g_lpLib3d->PopMatrix(MATRIX_OBJECT);
//DEADCODE JON 5/24/00 #endif
//DEADCODE JON 5/24/00 }

//DEADCODE JON 5/24/00 void LandScape::RenderACloudLayer(const COORDS3D& viewerPos,const UWord whichLayer)
//DEADCODE JON 5/24/00 {
//DEADCODE JON 5/24/00 	COORDS3D viewFrustrum[8];
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	g_lpLib3d->BackProjectViewCone(viewFrustrum);
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	BoundingBox boundingBox(8,viewFrustrum);
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	g_lpLib3d->SetFogColour(0x00FFFFFF);
//DEADCODE JON 5/24/00 	SLong scaleMask=-(1<<18);
//DEADCODE JON 5/24/00 	for (SLong scale=0;scale<7;scale++,scaleMask>>=1)
//DEADCODE JON 5/24/00 		if ((viewerPos.X&scaleMask)!=(scaleBase[scale].X&scaleMask) ||
//DEADCODE JON 5/24/00 			(viewerPos.Z&scaleMask)!=(scaleBase[scale].Z&scaleMask))
//DEADCODE JON 5/24/00 			break;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	for (;scale<7;scale++,scaleMask>>=1)
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		scaleBase[scale].X=viewerPos.X;
//DEADCODE JON 5/24/00 		scaleBase[scale].Z=viewerPos.Z;
//DEADCODE JON 5/24/00 		if (!scale)
//DEADCODE JON 5/24/00 			MakeTopLevel(scaleBase[0].X&scaleMask,scaleBase[0].Z&scaleMask,pLevels[0]);
//DEADCODE JON 5/24/00 		else
//DEADCODE JON 5/24/00 		{
//DEADCODE JON 5/24/00 			SLong dx=(scaleBase[scale].X>>(18-scale))&0x01;
//DEADCODE JON 5/24/00 			SLong dz=(scaleBase[scale].Z>>(18-scale))&0x01;
//DEADCODE JON 5/24/00 			UWord *samplePos=pLevels[scale-1]+TILE_OFFX+TILE_OFFZ;
//DEADCODE JON 5/24/00 			samplePos+=dz*TILE_WH+dx;
//DEADCODE JON 5/24/00 			DoubleRez(samplePos,scale,pLevels[scale]);
//DEADCODE JON 5/24/00 		}
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 	COORDS3D tileOffset;
//DEADCODE JON 5/24/00 	scale=0;
//DEADCODE JON 5/24/00 	SLong dxz=((4096<<5)>>scale)*(TILE_WH>>1);
//DEADCODE JON 5/24/00 	scaleMask=(-(1<<18))>>scale;
//DEADCODE JON 5/24/00 	tileOffset.X=(scaleBase[scale].X&scaleMask)-dxz-viewerPos.X;
//DEADCODE JON 5/24/00 	tileOffset.Z=(scaleBase[scale].Z&scaleMask)-dxz-viewerPos.Z;
//DEADCODE JON 5/24/00 
//DEADCODE JON 5/24/00 	if (whichLayer&WL_LOWER)
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		tileOffset.Y=FT_8000-viewerPos.Y;
//DEADCODE JON 5/24/00 		RenderLevel00(tileOffset,pLevels[scale],scale,layer00table);
//DEADCODE JON 5/24/00 		RenderLevel00(tileOffset,pLevels[scale],scale,layer10table);
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 	if (whichLayer&WL_MIDDLE)
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		tileOffset.Y=FT_10000-viewerPos.Y;
//DEADCODE JON 5/24/00 		RenderLevel00(tileOffset,pLevels[scale],scale,layer01table);
//DEADCODE JON 5/24/00 		RenderLevel00(tileOffset,pLevels[scale],scale,layer11table);
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 	if (whichLayer&WL_TOP)
//DEADCODE JON 5/24/00 	{
//DEADCODE JON 5/24/00 		tileOffset.Y=FT_15000-viewerPos.Y;
//DEADCODE JON 5/24/00 		RenderLevel00(tileOffset,pLevels[scale],scale,layer02table);
//DEADCODE JON 5/24/00 		RenderLevel00(tileOffset,pLevels[scale],scale,layer12table);
//DEADCODE JON 5/24/00 	}
//DEADCODE JON 5/24/00 	g_lpLib3d->SetFogColour(0x0090B8E8);
//DEADCODE JON 5/24/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmokeyCockpit
//Author		Paul.   
//Date			Fri 3 Dec 1999
//
//------------------------------------------------------------------------------
//deadcode JON 19/06/01	void LandScape::SmokeyCockpit()
//deadcode JON 19/06/01	{
//DEADCODE JON 5/24/00 #ifndef _REDO_ME1_
//DEADCODE JON 5/24/00 	static UWord height=0;
//DEADCODE JON 5/24/00 	ImageMapNumber SmokeyImage;
//DEADCODE JON 5/24/00 	ImageMapDesc *pSmokeyImage;
//DEADCODE JON 5/24/00 	HMATERIAL hMaterial;
//DEADCODE JON 5/24/00 	ROWANSURFACEDESC rsd;
//DEADCODE JON 5/24/00 	R3DTLVERTEX *pRTLVert;
//DEADCODE JON 5/24/00 	SmokeyImage=CLOUDNO;
//DEADCODE JON 5/24/00 	pSmokeyImage=Image_Map.GetImageMapPtr(SmokeyImage);
//DEADCODE JON 5/24/00 	hMaterial=HMATERIAL(pSmokeyImage);
//DEADCODE JON 5/24/00 	height+=View_Point->RealFrameTime();
//DEADCODE JON 5/24/00 	rsd.dwSize=sizeof(ROWANSURFACEDESC);
//DEADCODE JON 5/24/00 	g_lpLib3d->GetSurfaceDesc(&rsd);
//DEADCODE JON 5/24/00 	g_lpLib3d->BeginPoly(hMaterial,4,pRTLVert);
//DEADCODE JON 5/24/00 	pRTLVert[0].sx=0;
//DEADCODE JON 5/24/00 	pRTLVert[0].sy=0;
//DEADCODE JON 5/24/00 	pRTLVert[0].ix=0;
//DEADCODE JON 5/24/00 	pRTLVert[0].iy=0+(height>>7);
//DEADCODE JON 5/24/00 	pRTLVert[1].sx=rsd.dwWidth-1;
//DEADCODE JON 5/24/00 	pRTLVert[1].sy=0;
//DEADCODE JON 5/24/00 	pRTLVert[1].ix=pSmokeyImage->w;
//DEADCODE JON 5/24/00 	pRTLVert[1].iy=0+(height>>7);
//DEADCODE JON 5/24/00 	pRTLVert[2].sx=rsd.dwWidth-1;
//DEADCODE JON 5/24/00 	pRTLVert[2].sy=rsd.dwHeight-1;
//DEADCODE JON 5/24/00 	pRTLVert[2].ix=pSmokeyImage->w;
//DEADCODE JON 5/24/00 	pRTLVert[2].iy=pSmokeyImage->h+(height>>7);
//DEADCODE JON 5/24/00 	pRTLVert[3].sx=0;
//DEADCODE JON 5/24/00 	pRTLVert[3].sy=rsd.dwHeight-1;
//DEADCODE JON 5/24/00 	pRTLVert[3].ix=0;
//DEADCODE JON 5/24/00 	pRTLVert[3].iy=pSmokeyImage->h+(height>>7);
//DEADCODE JON 5/24/00 	g_lpLib3d->EndPoly();
//DEADCODE JON 5/24/00 #endif _REDO_ME1_
//deadcode JON 19/06/01	}

//
//axis aligned BSP tree rendering class
//
/*typedef void BSPAXISCALLBACK (SLong,void*);
typedef BSPAXISCALLBACK *LPBSPAXISCALLBACK;

class BSPTreeAxis
{
	struct NType
	{
		enum NodeType {NT_NODE,NT_LEAF};
		NodeType nt;
		bool IsNode() {return bool(nt==NT_NODE);}
		NType(NodeType ty=NT_NODE) {nt=ty;}
	};

	struct BSPLeaf : NType
	{
		SLong data;
		BSPLeaf() : NType(NodeType::NT_LEAF) {}
	};

	struct BSPNode : NType
	{
		enum Orientation {AXIS_X=0,AXIS_Y,AXIS_Z};

		union 
		{
			BSPNode *pos;
			BSPLeaf *lpos;
		};
		union
		{
			BSPNode *neg;
			BSPLeaf *lneg;
		};
		Orientation ori;

		SLong d;

		BSPNode() {pos=neg=NULL;}
	};

	enum {RX=0,RZ,RW,RH};

	BSPNode *pHead;
	LPBSPAXISCALLBACK pCallback;
	void *pContext;

	BSPNode *BuildRecurse(SLong rect[4],SLong recurseDepth,BSPNode::Orientation ori);
	BSPLeaf *AddLeaf(SLong xpos,SLong zpos,BSPNode *pnode);
	void RenderRecurse(SLong ori[3],SLong dir[3],BSPNode *pnode);
	void ReleaseRecurse(BSPNode *pnode);

	public:

	BSPTreeAxis() {pHead=NULL;}
	~BSPTreeAxis() {ReleaseRecurse(pHead);}

	void BuildBSPTree(SLong minCloudY,SLong maxCloudY,SLong wxzStep,SLong gridWH);
	void RenderTree(ViewPoint *vp,COORDS3D *base);
};
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildRecurse
//Author		Paul.   
//Date			Mon 17 Jan 2000
//
//------------------------------------------------------------------------------
BSPTreeAxis::BSPNode *BSPTreeAxis::BuildRecurse(SLong rect[4],SLong recurseDepth,
												BSPNode::Orientation ori)
{
	if (recurseDepth==0) return NULL;

	recurseDepth--;

	SLong r0[4],r1[4];

	BSPNode *pnode=new BSPNode;
	pnode->ori=ori;

	if (ori==BSPNode::AXIS_X)
	{
		r1[RZ]=r0[RZ]=rect[RZ];
		r1[RH]=r0[RH]=rect[RH];
		pnode->d=-(r1[RX]=(r0[RX]=rect[RX])+(r1[RW]=r0[RW]=(rect[RW]>>1)));
		pnode->pos=BuildRecurse(r1,recurseDepth,BSPNode::AXIS_Z);
		pnode->neg=BuildRecurse(r0,recurseDepth,BSPNode::AXIS_Z);
	}
	else //ori==BSPNode::AXIS_Z
	{
		r1[RX]=r0[RX]=rect[RX];
		r1[RW]=r0[RW]=rect[RW];
		pnode->d=-(r1[RZ]=(r0[RZ]=rect[RZ])+(r1[RH]=r0[RH]=(rect[RH]>>1)));
		pnode->pos=BuildRecurse(r1,recurseDepth,BSPNode::AXIS_X);
		pnode->neg=BuildRecurse(r0,recurseDepth,BSPNode::AXIS_X);
	}
	return pnode;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddLeaf
//Author		Paul.   
//Date			Mon 17 Jan 2000
//
//------------------------------------------------------------------------------
BSPTreeAxis::BSPLeaf *BSPTreeAxis::AddLeaf(SLong xpos,SLong zpos,BSPNode *pnode)
{
	BSPLeaf *pleaf;

	SLong dir=(pnode->ori==BSPNode::AXIS_X)?xpos+pnode->d:zpos+pnode->d;

	if (dir>=0)	pleaf=(pnode->pos)?AddLeaf(xpos,zpos,pnode->pos):(pnode->lpos=new BSPLeaf);
	else		pleaf=(pnode->neg)?AddLeaf(xpos,zpos,pnode->neg):(pnode->lneg=new BSPLeaf);

	return pleaf;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		BuildBSPTree
//Author		Paul.   
//Date			Mon 17 Jan 2000
//
//------------------------------------------------------------------------------
void BSPTreeAxis::BuildBSPTree(SLong minCloudY,SLong maxCloudY,SLong wxzStep,SLong gridWH)
{
	if (pHead) ReleaseRecurse(pHead);

	//first two planes in the bsp tree enclose the entire
	//cloud layer in the y direction

	BSPNode *pnext;
	SLong rect[4];
	SLong recurseDepth;

	pHead=new BSPNode;
	pHead->ori=BSPNode::AXIS_Y;
	pHead->d=-minCloudY;
	pnext=new BSPNode;
	pHead->pos=pnext;
	pnext->ori=BSPNode::AXIS_Y;
	pnext->d=-maxCloudY;

	recurseDepth=gridWH&0xFFFFFFFE;
	rect[RX]=-((wxzStep>>1)+(gridWH>>1)*wxzStep);
	rect[RZ]=(wxzStep>>1)-(gridWH>>1)*wxzStep;
	rect[RW]=rect[RH]=recurseDepth*wxzStep;

	pnext->neg=BuildRecurse(rect,recurseDepth,BSPNode::AXIS_Z);
	pnext=pnext->neg;

	SLong rz,cx;
	cx=rect[RX]+(wxzStep>>1);
	rz=rect[RZ]-(wxzStep>>1);
	recurseDepth=0;
	for (SLong i=gridWH;i>0;i--)
	{
		SLong rx=cx;
		for (SLong j=gridWH;j>0;j--)
		{
			AddLeaf(rx,rz,pnext)->data=recurseDepth++;
			rx+=wxzStep;
		}
		rz+=wxzStep;
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseRecurse
//Author		Paul.   
//Date			Mon 17 Jan 2000
//
//------------------------------------------------------------------------------
void BSPTreeAxis::ReleaseRecurse(BSPNode *pnode)
{
	if (pnode->IsNode())
	{
		if (pnode->pos!=NULL)	ReleaseRecurse(pnode->pos);
		if (pnode->neg!=NULL)	ReleaseRecurse(pnode->neg);
		delete pnode;
	}
	else delete (BSPLeaf*)pnode;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderRecurse
//Author		Paul.   
//Date			Mon 17 Jan 2000
//
//------------------------------------------------------------------------------
void BSPTreeAxis::RenderRecurse(SLong ori[3],SLong dir[3],BSPNode *pnode)
{
	if (pnode->IsNode())
	{
		SLong o,d;
		d=pnode->ori;
		o=ori[d];
		d=dir[d];
		if (o+pnode->d>=0)	
		{
			RenderRecurse(ori,dir,pnode->pos);
			RenderRecurse(ori,dir,pnode->neg);
		}
		else
		{
			RenderRecurse(ori,dir,pnode->neg);
			RenderRecurse(ori,dir,pnode->pos);
		}
	}
	else (*pCallback)(((BSPLeaf*)pnode)->data,pContext);
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTree
//Author		Paul.   
//Date			Mon 17 Jan 2000
//
//------------------------------------------------------------------------------
void BSPTreeAxis::RenderTree(ViewPoint *vp,COORDS3D *base)
{
	SLong dir[3],ori[3],dirmag;
	R3DVALUE tmp,tmp2;
	SWord sinhdg,coshdg,sinpitch,cospitch;
	Math_Lib.high_sin_cos(vp->hdg,sinhdg,coshdg);
	Math_Lib.high_sin_cos(vp->pitch,sinpitch,cospitch);
	dir[0]=(cospitch*sinhdg)/ANGLES_FRACT;
	dir[1]=sinpitch;
	dir[2]=(cospitch*coshdg)/ANGLES_FRACT;
	tmp2=R3DVALUE(dir[0]);
	tmp=tmp2*tmp2;
	tmp2=R3DVALUE(dir[1]);
	tmp+=tmp2*tmp2;
	tmp2=R3DVALUE(dir[2]);
	tmp+=tmp2*tmp2;
	dirmag=SLong(fastMath.FastSqrt(tmp));
	dir[0]=(dir[0]<<16)/dirmag;
	dir[1]=(dir[1]<<16)/dirmag;
	dir[2]=(dir[2]<<16)/dirmag;
	ori[0]=vp->World.X-base->X;
	ori[1]=vp->World.Y-base->Y;
	ori[2]=vp->World.Z-base->Z;
	RenderRecurse(ori,dir,pHead);
}
*/
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LogCrater
//Author		Robert Slater
//Date			Thu 18 Nov 1999
//
//Description	
//
//Inputs		size is 0 - 63, where 63 is maximum strength explosion
//
//Returns	
//
//------------------------------------------------------------------------------
void	LandScape::LogCrater(Coords3D&	worldcoord, SLong size)
{
	if (craterCnt >= MAX_CRATERS)
		craterCnt = 0;

	craterLog[craterCnt].pos = worldcoord;
	craterLog[craterCnt++].size = size;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StompImageMap
//Author		Robert Slater
//Date			Tue 30 Nov 1999
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	LandScape::StompImageMap(SWord	mapnumber, SWord splodge)
{
	if (stompMapCnt < MAX_STOMPERS)
	{
		stompMap[stompMapCnt].imagemap = mapnumber;
		stompMap[stompMapCnt].splodge = splodge;
		stompMapCnt++;
	}
}

// New smoke cloud stuff...


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SmkCloudDesc
//Author		Robert Slater
//Date			Thu 25 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------

SmkCloudDesc::SmkCloudDesc()
{
	animdata = new UByte[SmokeAnimSize];
	animdata = AnimSizeField(SmokeAnimSize);
	animdata = AnimFlagField(1<<MINANIM);

	Refresh();
}

SmkCloudDesc::~SmkCloudDesc()
{
	animdata.Delete();
	animdata = ANIM_NULL;
}

void	SmkCloudDesc::Refresh()
{
	UByteP	tmpptr = &animdata;

	for (int i=0; i < SmokeAnimSize; i++)	tmpptr[i] = 0;

	active = false;
	weight = -1;
	timealive = 0;
	hdg = 0;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddSmokeCloud
//Author		Robert Slater
//Date			Tue 23 May 2000
//
//Description	Checks this smoke blob coord with known coords,
//				if within certain radius (100m) (i.e. max radius of a smokey cloud)
//				and adds it if it is...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	LandScape::AddSmokeCloud(Coords3D&	pos, const SWord& initialWeight)
{
	const	float	smkRadSqrd = 100*100;
	const	SLong	NoHitsInNSecs = 500 / Timer_Code.FRAMETIME;

	SLong			index,emptyindex;
	float			xsqrd,zsqrd,rsqrd;
	SmkCloudDesc*	smkptr = smkList;
	SLong			oldest = 600;		//6 secs
	SLong			oldIndex = -1;

	emptyindex = MaxSmokeClouds;

	for (index=0; index < MaxSmokeClouds; index++)
	{
		if (smkptr->weight > -1)			// has this one expired?
		{
			xsqrd = pos.X - smkptr->pos.X;
			xsqrd *= xsqrd;

			zsqrd = pos.Z - smkptr->pos.Z;
			zsqrd *= zsqrd;

			rsqrd = xsqrd+zsqrd;
			if (rsqrd <= smkRadSqrd)		// are we part of this cloud?
			{
				smkptr->weight += initialWeight;
				if (smkptr->weight >= NoHitsInNSecs)		
				{
					if (!smkptr->active)
						smkptr->active = true;
					else
					{
						if (smkptr->weight > 16384)
							smkptr->weight = 16384;
					}
				}
				else
				{
					smkptr->pos.X = (pos.X + smkptr->pos.X)>>1;
					smkptr->pos.Y = (pos.Y + smkptr->pos.Y)>>1;
					smkptr->pos.Z = (pos.Z + smkptr->pos.Z)>>1;
				}

				break;
			}
			else
			{
				if (smkptr->timealive > oldest)
				{
					oldest = smkptr->timealive;
					oldIndex = index;
				}
			}
		}
		else
		 	emptyindex = index;

		smkptr++;
	}

// If no match was found, add new one...
	if (index == MaxSmokeClouds)
	{
		if (emptyindex != MaxSmokeClouds)
		{
			smkptr = &smkList[emptyindex];
			smkptr->Refresh();
			smkptr->pos = pos;
			smkptr->weight = initialWeight;
		}
		else
		{
			if (oldIndex > -1)
			{
				smkptr = &smkList[oldIndex];
				smkptr->Refresh();
				smkptr->pos = pos;
				smkptr->weight = initialWeight;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawSmokeClouds
//Author		Robert Slater
//Date			Tue 23 May 2000
//
//Description	Draws the smoke clouds in the list,
//				and the fog bank (if there is one)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	LandScape::DrawSmokeClouds()
{
	if (Save_Data.detail_3d[DETAIL3D_TRANSSMOKE] != 0)					//RJS 9Aug00
	{
		SLong			index;
		SmkCloudDesc*	smkptr = smkList;
		hdgitem			smokeitem;

// Smoke Clouds...

		for (index=0; index < MaxSmokeClouds; index++)
		{
			if (smkptr->active)
			{
				smokeitem.World = smkptr->pos;
  				smokeitem.shape = SBANKM;
				smokeitem.Anim = smkptr->animdata;
				smokeitem.hdg = Angles(smkptr->hdg);
  						
  				Three_Dee.do_object_dummy(&smokeitem,MOBILE_OBJECT);
			}
			smkptr++;
		}

		smokeitem.Anim = ANIM_NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ManageSmokeClouds
//Author		Robert Slater
//Date			Wed 24 May 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	LandScape::ManageSmokeClouds()
{
	SmkCloudDesc*	smkptr = smkList;

	for (SLong index=0; index < MaxSmokeClouds; index++)
	{
		if (smkptr->weight > -1)
		{
			smkptr->hdg += ANGLES_ThirdDeg;
			smkptr->timealive += Timer_Code.FRAMETIME;
			if (	(smkptr->timealive > MaxTimeSmokeAlive)	//too old
				|| 	(	!smkptr->active
					 &&	(smkptr->timealive > 600)	)	)	//too weak
			{
				smkptr->weight = -1;		//kill
				smkptr->active = false;
			}
		}

		smkptr++;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SaveSmokeClouds
//Author		Robert Slater
//Date			Mon 10 Jul 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	LandScape::SaveSmokeClouds()
{
	SmkCloudDesc*	smkptr = smkList;
	SLong num=0,index;

	for (index=0; index < MaxSmokeClouds; index++)
	{
		if (smkptr->active)
		{
			num++;
		}
		smkptr++;
	}

	if (!_Replay.ReplayWrite((UByte*)&num,sizeof(SLong)))
		return false;

	smkptr = smkList;

	for (index=0; index < MaxSmokeClouds; index++)
	{
		if (smkptr->active)
		{
// Save	index, timealive, pos

			REPLAYSMOKECLOUD rsc;

			rsc.index=index;
			rsc.timealive=smkptr->timealive;
			rsc.pos=smkptr->pos;

			if (!_Replay.ReplayWrite((UByte*)&rsc,sizeof(REPLAYSMOKECLOUD)))
				return false;


		}
		smkptr++;
	}

	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		LoadSmokeClouds
//Author		Robert Slater
//Date			Mon 10 Jul 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	LandScape::LoadSmokeClouds(bool dummy)
{
	SmkCloudDesc*	smkptr = smkList;
	SLong num=0,i;

	if (!_Replay.CloudRead((UByte*)&num,sizeof(SLong)))
		return false;

	for (i=0;i<num;i++)
	{
// Load	index, timealive, pos... set weight to 16384
// set active to true

		REPLAYSMOKECLOUD rsc;

		if (!_Replay.CloudRead((UByte*)&rsc,sizeof(REPLAYSMOKECLOUD)))
			return false;

		if (!dummy)
		{
			smkptr[rsc.index].pos=rsc.pos;
			smkptr[rsc.index].weight=16384;
			smkptr[rsc.index].timealive=rsc.timealive;
			smkptr[rsc.index].active=true;
		}
	}
	return true;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WipeSmokeClouds
//Author		Robert Slater
//Date			Thu 27 Jul 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	LandScape::WipeSmokeClouds()
{
	SmkCloudDesc*	smkptr = smkList;

	for (SLong index=0; index < MaxSmokeClouds; index++)
	{
		smkptr->Refresh();
		smkptr++;
	}
}

//////////////////////////////////////////////////////////////////////
//
// Function:    InitTextures

// Date:		09/08/00
// Author:		JON
//
//Description:	Initialises the landscape textures for the user - is done on entry to 3d
//
//////////////////////////////////////////////////////////////////////
void	LandScape::InitTextures( CLib3D *lib3d )
{
	g_lpLib3d = lib3d;

	// set up this...
	landscapeDelay = 1;

	// ensure this is clean
	g_lpLib3d->UnloadTexture( horizonImg );
	g_lpLib3d->UnloadTexture( cloudImg0 );

	gridOffs.reInit();
	cloudOffs.reInit();

	// fudge the map icons to have no mipmaps...
	{
		g_lpLib3d->GiveHint( HINT_BILINEAR ); // don't do no mipmaps for this	
		g_lpLib3d->SetMaterial( HMATERIAL(Image_Map.GetImageMapPtr(MAPCHAPNO)) );// force upload
		g_lpLib3d->GiveHint( HINT_TRILINEAR ); //note won't go above max do  
	}
	// avail the sea and dither stuff... 
	// only affects the tri-linear and all stuff..
	if ( Save_Data.filtering>=2 )
	{
		FileNum	theFile;
		LandMapNum theMap;
		ImageMapDescPtr	topPtr;
		ImageMapDescPtr theMip;

//TempCode JON 11Aug00 		theFile= FileNum( FIL_SEA1_NUM );				
//TempCode JON 11Aug00 		theMap=LandMapNum(theFile);								
//TempCode JON 11Aug00 		topPtr = theMap.GetLandMapPtr();						
//TempCode JON 11Aug00 		g_lpLib3d->UploadAsDitherTexture( topPtr );				
//TempCode JON 11Aug00 																
//TempCode JON 11Aug00 		theFile = FileNum( FIL_SEA1_1_NUM );			
//TempCode JON 11Aug00 		theMap=LandMapNum(theFile);								
//TempCode JON 11Aug00 		theMip = theMap.GetLandMapPtr();						
//TempCode JON 11Aug00 		g_lpLib3d->UploadAsMipMapLevel( topPtr, theMip, 1 );	
//TempCode JON 11Aug00 																
//TempCode JON 11Aug00 		theFile = FileNum( FIL_SEA1_2_NUM );			
//TempCode JON 11Aug00 		theMap=LandMapNum(theFile);								
//TempCode JON 11Aug00 		theMip = theMap.GetLandMapPtr();						
//TempCode JON 11Aug00 		g_lpLib3d->UploadAsMipMapLevel( topPtr, theMip, 2 );	
//TempCode JON 11Aug00 																
//TempCode JON 11Aug00 		theFile = FileNum( FIL_SEA1_3_NUM );			
//TempCode JON 11Aug00 		theMap=LandMapNum(theFile);								
//TempCode JON 11Aug00 		theMip = theMap.GetLandMapPtr();						
//TempCode JON 11Aug00 		g_lpLib3d->UploadAsMipMapLevel( topPtr, theMip, 3 );	
//TempCode JON 11Aug00 																
//TempCode JON 11Aug00 		theFile = FileNum( FIL_SEA1_4_NUM );			
//TempCode JON 11Aug00 		theMap=LandMapNum(theFile);								
//TempCode JON 11Aug00 		theMip = theMap.GetLandMapPtr();						
//TempCode JON 11Aug00 		g_lpLib3d->UploadAsMipMapLevel( topPtr, theMip, 4 );


	#define LOAD_MIPS( baseName )								\
		theFile= FileNum( FIL_##baseName##_NUM );				\
		theMap=LandMapNum(theFile);								\
		topPtr = theMap.GetLandMapPtr();						\
		g_lpLib3d->UploadAsDitherTexture( topPtr );				\
																\
		theFile = FileNum( FIL_##baseName##_1_NUM );			\
		theMap=LandMapNum(theFile);								\
		theMip = theMap.GetLandMapPtr();						\
		g_lpLib3d->UploadAsMipMapLevel( topPtr, theMip, 1 );	\
																\
		theFile = FileNum( FIL_##baseName##_2_NUM );			\
		theMap=LandMapNum(theFile);								\
		theMip = theMap.GetLandMapPtr();						\
		g_lpLib3d->UploadAsMipMapLevel( topPtr, theMip, 2 );	\
																\
		theFile = FileNum( FIL_##baseName##_3_NUM );			\
		theMap=LandMapNum(theFile);								\
		theMip = theMap.GetLandMapPtr();						\
		g_lpLib3d->UploadAsMipMapLevel( topPtr, theMip, 3 );	\
																\
		theFile = FileNum( FIL_##baseName##_4_NUM );			\
		theMap=LandMapNum(theFile);								\
		theMip = theMap.GetLandMapPtr();						\
		g_lpLib3d->UploadAsMipMapLevel( topPtr, theMip, 4 )	

		LOAD_MIPS( SEA1 );
		LOAD_MIPS( SEA2 );
		LOAD_MIPS( SEA3 );
		LOAD_MIPS( SEA4 );
		LOAD_MIPS( DITHER2 );
		int dim = theMip->w;
		// now some fiddles for the plain stuff.
		theFile = FileNum( FIL_DITHER1_4_NUM );	
		theMap=LandMapNum(theFile);				
		theMip = theMap.GetLandMapPtr();
		theMip->w=theMip->h = dim;

		LOAD_MIPS( DITHER1 );
		LOAD_MIPS( DITHER3 );
		LOAD_MIPS( DITHER4 );
		LOAD_MIPS( DITHER5 );
		LOAD_MIPS( DITHER6 );

		// now the rest of the fiddles for the plain stuff.
		theFile = FileNum( FIL_DITHER1_4_NUM );	
		theMap=LandMapNum(theFile);				
		theMip = theMap.GetLandMapPtr();
		g_lpLib3d->SetMaterial( HMATERIAL( theMip ) );// force an upload of the thing before fiddling its size... 

		theMip->w=theMip->h = dim<<4;
	}
}

inline ImageMapDescPtr LandScape::GetDitherTexture( int areatype )
{
	FileNum	theFile;
	LandMapNum theMap;
	ImageMapDescPtr theText;

	int offset;
	if ( IsWidened( areatype ) )
		offset = 3;
	else
		offset = DitherLookUp[areatype&31];

	if ( offset==-1 )
	{ // get a plain dither map that will make no difference....
		theFile = FileNum( FIL_DITHER1_4_NUM );
	} else
	{
		theFile = FileNum( FIL_DITHER1_NUM+offset );
	}
	theMap=LandMapNum(theFile);	
	theText = theMap.GetLandMapPtr();
	return theText;
}

//////////////////////////////////////////////////////////////////////
//
// Function:    DrawWayPointIcon

// Date:		11/8/00
// Author:		JON
//
//Description:	Draws a waypoint icon at the pos specified, with viewer_y of value given
//				This is actually for the map but there u go
//
//////////////////////////////////////////////////////////////////////
void LandScape::DrawWayPointIcon( const COORDS3D& pos, const ULong viewerx, const ULong viewery, const ULong viewerz, const int type )
{
	// first get the imagemap..
	const HMATERIAL texture(Image_Map.GetImageMapPtr(MAPCHAPNO));
	const float depth = -float(viewery);
	const float tokensize = (float(viewery))/50.f;// cover 1/30th of the map

	SWord tlx, tly;
	switch( type )
	{
		case 4: // targetpt
			tlx = 32;
			tly = 32;
		break;
		case 3: // homept selected
			tlx = 48;
			tly = 16;
		break;
		case 2: // waypoint selected
			tlx = 32;
			tly = 16;
		break;
		case 1: // homept
			tlx = 48;
			tly = 0;
		break;
		case 0: // waypoint
			tlx = 32;
			tly = 0;
		break;
		NODEFAULT;
	}

	g_lpLib3d->PushMatrix( MATRIX_OBJECT );
	g_lpLib3d->LoadIdentity( MATRIX_OBJECT );
	g_lpLib3d->Scale( MATRIX_OBJECT, 1.f/25.f );
	Lib3DPoint* vert = g_lpLib3d->BeginPoly( texture, 4 );
	vert[0].setPosition(
		float(SLong(pos.X-viewerx))-tokensize,
		depth,
		float(SLong(pos.Z-viewerz))+tokensize
	);		
	vert[0].setIMapCoords( tlx, tly );

	vert[1].setPosition(
		float(SLong(pos.X-viewerx))+tokensize,
		depth,
		float(SLong(pos.Z-viewerz))+tokensize
	);		
	vert[1].setIMapCoords( tlx+16, tly );

	vert[2].setPosition(
		float(SLong(pos.X-viewerx))+tokensize,
		depth,
		float(SLong(pos.Z-viewerz))-tokensize
	);		
	vert[2].setIMapCoords( tlx+16, tly+16 );

	vert[3].setPosition(
		float(SLong(pos.X-viewerx))-tokensize,
		depth,
		float(SLong(pos.Z-viewerz))-tokensize
	);		
	vert[3].setIMapCoords( tlx, tly+16 );
	g_lpLib3d->EndPoly();
	g_lpLib3d->PopMatrix(MATRIX_OBJECT);
}
