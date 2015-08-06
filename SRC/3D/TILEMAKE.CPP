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
//Filename       tilemake.cpp
//System         
//Author         Paul.   
//Date           Wed 15 Jul 1998
//Description    
//------------------------------------------------------------------------------

//#define _REDO_ME3_

#define F_GRAFIX
#define F_SOUNDS
#define F_BATTLE

#include "dosdefs.h"
#include "fileman.h"
#include "files.g"
#include "ImageMap.h"
#include "ImageMap.g"
#include "MigLand.h"
#include "display.h"
#include "worldinc.h"
#include "3dcode.h"
#include "mymath.h"
#include "TileMake.h"
#include "gameset.h"
#include "world.h"
#include "shapes.h"
#include "shpinstr.h"
#include "savegame.h"
#include "areatype.h"
#include "overlay.h"
#include "shapenum.g"
#include "fastmath.h"
//DEADCODE MS 02/02/00 #include <initguid.h>
#include "..\lib3d\lib3d.h"

const	SWord	SHIFT_StartIndex		=	4;
const	SWord	SHIFT_MultIndex			=	8;

const R3DVALUE DIV_SCALE = D3DVALUE(1.f/256.f);

#define MAKE_SHIFT(p1) SWord(SHIFT_StartIndex+((p1)*(SHIFT_MultIndex+SHIFT_StartIndex)))

const	SWord	SHIFT_MajorRiver		=	MAKE_SHIFT ( 1 );
const	SWord	SHIFT_MinorRiver		=	MAKE_SHIFT ( 1 );
const	SWord	SHIFT_Tributary			=	MAKE_SHIFT ( 1 );
const	SWord	SHIFT_MinorRoad			=	MAKE_SHIFT ( 2 );
const	SWord	SHIFT_FootPath			=	MAKE_SHIFT ( 2 );
const	SWord	SHIFT_MajorRail			=	MAKE_SHIFT ( 3 );
const	SWord	SHIFT_MinorRail			=	MAKE_SHIFT ( 3 );
const	SWord	SHIFT_ARoad				=	MAKE_SHIFT ( 4 );
const	SWord	SHIFT_BRoad				=	MAKE_SHIFT ( 4 );
const	SWord	SHIFT_AirFieldRT		=	MAKE_SHIFT ( 9 );
const	SWord	SHIFT_BlendGrassOther	=	MAKE_SHIFT ( 5 );
const	SWord	SHIFT_BlendSeaLand		=	MAKE_SHIFT ( 6 );
const	SWord	SHIFT_BlendSeaBeach		=	MAKE_SHIFT ( 7 );
//DEADCODE JON 5/15/00 const	SWord	SHIFT_BlendBeachLand	=	MAKE_SHIFT ( 8 );
const	SWord	SHIFT_CliffTopBaseBlend	=	MAKE_SHIFT ( 8 );

TMake* tMake=NULL;													  //JIM 29/03/99
//DeadCode JON 18Oct00 UByte* landPalette=NULL;

//DeadCode JON 18Oct00 static ULong blockNumber=0;

namespace TileMake
{

//DeadCode JON 18Oct00 const SLong SOFT_256_TEXTURES=8;
//DeadCode JON 18Oct00 const SLong SOFT_128_TEXTURES=16;
//DeadCode JON 18Oct00 const SLong SOFT_64_TEXTURES=32;
//DeadCode JON 18Oct00 const SLong SOFT_32_TEXTURES=32;
//DeadCode JON 18Oct00 const SLong SOFT_16_TEXTURES=32;
//DeadCode JON 18Oct00 const SLong SOFT_8_TEXTURES=64;
//DeadCode JON 18Oct00 ROWANSURFACEDESC** sysram256maps=NULL;
//DeadCode JON 18Oct00 ROWANSURFACEDESC** sysram128maps=NULL;
//DeadCode JON 18Oct00 ROWANSURFACEDESC** sysram64maps=NULL;
//DeadCode JON 18Oct00 ROWANSURFACEDESC** sysram32maps=NULL;
//DeadCode JON 18Oct00 ROWANSURFACEDESC** sysram16maps=NULL;
//DeadCode JON 18Oct00 ROWANSURFACEDESC** sysram8maps=NULL;
//DeadCode JON 18Oct00 UByte landTextureUsage[256];

const SLong _wholeAreaSizeMAX=33;
const SLong _wholeAreaSizeMIN=17;
const SLong _cornerLengthMAX=_wholeAreaSizeMAX+1;
const SLong _cornerLengthMIN=_wholeAreaSizeMIN+1;
const SLong _areaBufferSizeMAX=_wholeAreaSizeMAX*_wholeAreaSizeMAX;
const SLong _areaBufferSizeMIN=_wholeAreaSizeMIN*_wholeAreaSizeMIN;
const SLong _cornerBufferSizeMAX=_cornerLengthMAX*_cornerLengthMAX;
const SLong _cornerBufferSizeMIN=_cornerLengthMIN*_cornerLengthMIN;

const SLong Grid_Width=131072;
const ULong Grid_Mask=~ULong(Grid_Width-1);

const SLong DataGridSizeMAX=33;
const SLong DataGridSizeMIN=17;

const SLong Max_TextureLevelsMAX=6;
const SLong Max_TextureLevelsMIN=5;

const SLong Max_Edges=256;
const SLong Indexable_Edges=Max_Edges;
const SLong Real_Max_Edges=Max_Edges+2048;	//1024;

const SLong Max_Textures=32;
const SLong Max_Scales=4;

const FileNum BaseTexture=FIL_IMG0000;
//DEAD const FileNum LoRezBase=FIL_IMG20000;

const SLong TextureWidth=256;
const SWord SpanMin=0;
const SWord SSpanMax=SWord(TextureWidth-1);
const SWord ESpanMax=SWord(TextureWidth);

const UByte cf_null=0;
const UByte cf_top=1;
const UByte cf_bot=2;
const UByte cf_lft=4;
const UByte cf_rgt=8;
const UByte cf_all=cf_top+cf_bot+cf_lft+cf_rgt;

const UWord _offleft=0x0001;
const UWord _offright=0x0002;
const UWord _offtop=0x0004;
const UWord _offbottom=0x0008;

static ShapeNum noShadowShapes[]=
{
//DeadCode RJS 15Dec99 TREES,
TREE1,
TREE2,
//DeadCode RJS 15Dec99 TREE3,
//DeadCode RJS 15Dec99 TREE4,
SHCKWV,
EMPTY,
EMPTY2,
CTRPTC,
CRKPTC
};

static ShapeNum noShadowGroups[]=
{
// Stuff tall&thin groups here...
//DeadCode RJS 15Dec99 FOREST1,
//DeadCode RJS 15Dec99 FOREST2,
//DeadCode RJS 15Dec99 WOOD1,
//DeadCode RJS 15Dec99 WOOD2,
//DeadCode RJS 15Dec99 WOOD3,
R_CL_1,	// radar sites
R_CL_2,
R_CL_3,
R_CHL_1,
R_CHL_2,
R_CHL_3,
EMPTY
};

const SLong noShadowShapeEntries=sizeof(noShadowShapes)/sizeof(ShapeNum);
const SLong noShadowGroupEntries=sizeof(noShadowGroups)/sizeof(ShapeNum);

inline bool groupHasShadow(ShapeNum grp)
{
 	for (int i=noShadowGroupEntries-1;i>=0;i--)
		if (noShadowGroups[i]==grp)
			return false;
	return true;
}

inline bool shapeHasShadow(ShapeNum shp)
{
 	for (int i=noShadowShapeEntries-1;i>=0;i--)
		if (noShadowShapes[i]==shp)
			return false;
	return true;
}

//DeadCode JON 18Oct00 template<class t> inline void Swap(t& a,t& b) 
//DeadCode JON 18Oct00 							{a^=b;b^=a;a^=b;}
template<class t> inline t Min(const t a,const t b) 
							{return (a<b)?a:b;}
template<class t> inline t Max(const t a,const t b) 
							{return (a>b)?a:b;}
template<class t> inline t Abs(const t a) 
							{return (a>t(0))?a:-a;}
template<class t> inline t Clamp(const t a,const t min,const t max)
							{return (a<min)?min:(a>max)?max:a;}
template<class t> inline t Absolute(const t i,const t j,t& k)
							{return ((i-j)*(k=((i-j)<0?-1:1)));}

template<class t>
inline
void ClipResult(const t x,const t z,const Rect& r,UWord& flags,UWord& edges)
{
	if (x<r.l) 		flags=_offleft;
	else if (x>r.r) flags=_offright;
	else 			flags=0;

	if (z<r.t) 		flags+=_offtop;
	else if (z>r.b) flags+=_offbottom;

	if (x==r.l) 		edges=_offleft;
	else if (x==r.r)	edges=_offright;
	else				edges=0;
		
	if (z==r.t)			edges+=_offtop;
	else if (z==r.b)	edges+=_offbottom;
}

typedef struct EdgeTag
{
	SLong 	ymin,
			ymax;
	SLong 	xi,
			dxi;
}
Edge,*EdgePtr;

typedef struct EdgeTag2
{
	Edge	tri;
	Edge	texture;
}
Edge2,Edge2Ptr;
	
typedef struct VDataTag
{
	SWord v;
	SWord x;
	SWord y;
}
VData,*VDataPtr;

typedef struct VTriTag
{
	VData v1,v2,v3;
}
VTri,*VTriPtr;



typedef struct XDataTag : VData
{
	UByte cf;
}
XData,*XDataPtr;

typedef struct BoxTag
{
	SLong left,top,right,bottom;
}
Box,*BoxPtr;

//DeadCode JON 18Oct00 UByte		edgeRecord[Max_Edges*Max_Edges];
//DeadCode JON 18Oct00 UByte		clipRecord[Max_Edges];
//DeadCode JON 18Oct00 Edge		EdgeList[Real_Max_Edges];
//DEAD fileblock*	fileData[Max_Textures];	//*Max_Scales];
//DEAD fileblock*	fileData2[Max_Textures];	//*Max_Scales];
UByte* 		imageData[Max_Textures]; //*Max_Scales];
ImageMapDesc* imagePtrs[Max_Textures];
//DEAD UByte* 		imageData2[Max_Textures]; //*Max_Scales];
//DeadCode JON 18Oct00 UByte*		imagePalette;
PointDef* 	pointdef;
//DeadCode JON 18Oct00 SWord 		tile_scale;
//DeadCode JON 18Oct00 bool		ispalettised;
//DeadCode JON 18Oct00 UWord*		palLookup;
//DeadCode JON 18Oct00 SWord		byteScale;
//SWord		byteMask;
//DeadCode JON 18Oct00 SWord		physWidth;
//DeadCode JON 18Oct00 SWord		pixelSkip;
//DeadCode JON 18Oct00 SLong*		land_x;
//DeadCode JON 18Oct00 SLong*		land_z;
//DeadCode JON 18Oct00 bool*		update_req;
//DeadCode JON 18Oct00 SWord		detail_min;
//DeadCode JON 18Oct00 UByte		tileRnd[256];

//DeadCode JON 18Oct00 UWord		currentRouteColor16=0xFFFF;
//DeadCode JON 18Oct00 UByte		currentRouteColor8=0xFF;

//DeadCode JON 18Oct00 Box			targetBox;

SLong gridRecordBase_x;
SLong gridRecordBase_z;

//DeadCode JON 18Oct00 struct ShadowStruc
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong world_x,world_z;
//DeadCode JON 18Oct00 };

DataRecord*	gridRecords;
//DeadCode JON 18Oct00 ShadowStruc* shadowRecords;
//DeadCode JON 18Oct00 ShadowStruc currentShadowRec;

//DeadCode JON 18Oct00 SLong clipRectCnt;
//DeadCode JON 18Oct00 Rect*  clipRects;

//DEADCODE JON 4/14/00 UByte* gridClipper;

struct vector2d
{
	float x;
	float z;
};

WorldStuff* worldPtr;
//DEADCODE JON 4/14/00 SLong numShadows;
//DEADCODE JON 4/14/00 ULong curSec;
//DEADCODE JON 4/14/00 UWord shadowSectors[9];
static SLong shadowDX,shadowDZ;
static float shadowDXf,shadowDZf;

//DeadCode JON 18Oct00 static SLong	recordsUsed=Max_Edges;
//DeadCode JON 18Oct00 static SLong	clipRecsUsed=Max_Edges;
//DeadCode JON 18Oct00 static EdgePtr	curEdge=EdgeList;
//DeadCode JON 18Oct00 static UByte*	pdsttxt=NULL;
//DeadCode JON 18Oct00 static UByte*	psrctxt=NULL;
//DeadCode JON 18Oct00 static SWord 	xoffset=0;
//DeadCode JON 18Oct00 static SWord 	yoffset=0;
//DeadCode JON 18Oct00 static SWord  uoffset=0;
//DeadCode JON 18Oct00 static SWord  voffset=0;
//DeadCode JON 18Oct00 static bool 	hardwareVersion=true;
static bool 	loadedTextures=false;
static CLib3D*	g_lpLib3d=NULL;
//DeadCode JON 18Oct00 static bool		aliasingEdges=true;
//DeadCode JON 18Oct00 inline UByte permb(const UByte x) {return tileRnd[x];}
//DeadCode JON 18Oct00 inline SLong perm(const SLong x) {return tileRnd[x&0xFF];}
//DeadCode JON 18Oct00 inline UByte index2d(const SLong x,const SLong y) {return UByte(perm(x+perm(y)));}
//DeadCode JON 18Oct00 inline UByte index3d(const SLong x,const SLong y,const SLong z) {return UByte(perm(x+perm(y+perm(z))));}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 void DDSymLine(ROWANSURFACEDESC*,SLong,SLong,SLong,SLong);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		Swap<VData>
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 template<> inline void Swap<VData>(VData& a,VData& b)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	assert(3*sizeof(UWord)==sizeof(VData)&&"Swap<VData> struct size has altered");
//DeadCode JON 18Oct00  	*(ULong*)&a.v^=*(ULong*)&b.v;
//DeadCode JON 18Oct00  	*(ULong*)&b.v^=*(ULong*)&a.v;
//DeadCode JON 18Oct00  	*(ULong*)&a.v^=*(ULong*)&b.v;
//DeadCode JON 18Oct00  	*(UWord*)&a.y^=*(UWord*)&b.y;
//DeadCode JON 18Oct00  	*(UWord*)&b.y^=*(UWord*)&a.y;
//DeadCode JON 18Oct00  	*(UWord*)&a.y^=*(UWord*)&b.y;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		Swap<Edge>
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 6 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 template<> inline void Swap<Edge>(Edge& a,Edge& b)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	Swap(a.ymin,b.ymin);
//DeadCode JON 18Oct00 	Swap(a.ymax,b.ymax);
//DeadCode JON 18Oct00 	Swap(a.xi,b.xi);
//DeadCode JON 18Oct00 	Swap(a.dxi,b.dxi);
//DeadCode JON 18Oct00 }


const	float	SHAD_CUT_OFF = 18. / float(SUNELEVDIST);

const	float	shadNearMin = 110;
const	float	shadNearMax = 128;
const	ULong	shadColour = 0x101010;

static	ULong	shadNearAlpha = shadNearMin;
static	ULong	shadFarAlpha = shadNearMin;
static	ULong	shadColourNear = shadColour;
static	ULong	shadColourFar = shadColour;


//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SetClipFlags
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline UByte SetClipFlags(const SWord v)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	UByte r;
//DeadCode JON 18Oct00 	if (0xFF!=clipRecord[v])
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		r=clipRecord[v];
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		SWord x,y;
//DeadCode JON 18Oct00 		r=cf_null;
//DeadCode JON 18Oct00 		x=xoffset+(pointdef[v].x>>tile_scale);
//DeadCode JON 18Oct00 		y=yoffset+((256-pointdef[v].z)>>tile_scale);
//DeadCode JON 18Oct00 		if (x<targetBox.left) 			r+=cf_lft;
//DeadCode JON 18Oct00 		else if (x>targetBox.right)		r+=cf_rgt;
//DeadCode JON 18Oct00 		if (y<targetBox.top)			r+=cf_top;
//DeadCode JON 18Oct00 		else if (y>targetBox.bottom) 	r+=cf_bot;
//DeadCode JON 18Oct00 		clipRecord[v]=r;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	return r;
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 typedef void (*plotpixelfn) (SLong,SLong);
//DeadCode JON 18Oct00 typedef void (*ddpixelfn) (ROWANSURFACEDESC*,SLong,SLong);

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DrawSpan8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void DrawSpan8(const SWord x1,const SWord x2,UByte* p,UByte* t)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SWord x=Clamp(x1,SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	SWord xx=Clamp(x2,SpanMin,ESpanMax);
//DeadCode JON 18Oct00 	t+=(uoffset+(x<<byteScale))&0xFF;
//DeadCode JON 18Oct00 	UByte* bp=p+x+xoffset;
//DeadCode JON 18Oct00 	for (;x<xx;*bp++=*t,t+=pixelSkip,x++) {}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DarkSpan8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 22 Oct 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void DarkSpan8(const SWord x1,const SWord x2,UByte* p)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SWord x=Clamp(x1,SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	SWord xx=Clamp(x2,SpanMin,ESpanMax);
//DeadCode JON 18Oct00 	UByte* bp=p+x;
//DeadCode JON 18Oct00 	for (;x<xx;*bp++=0,x++) {}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DrawSpan16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 16 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void DrawSpan16(const SWord x1,const SWord x2,UWord* p,UByte* t)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SWord x=Clamp(x1,SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	SWord xx=Clamp(x2,SpanMin,ESpanMax);
//DeadCode JON 18Oct00 	t+=(uoffset+(x<<byteScale))&0xFF;
//DeadCode JON 18Oct00  	UWord* bp=p+x+xoffset;
//DeadCode JON 18Oct00 	for (;x<xx;*bp++=palLookup[*t],t+=pixelSkip,x++) {}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DarkSpan16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 22 Oct 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void DarkSpan16(const SWord x1,const SWord x2,UWord* p)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SWord x=Clamp(x1,SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	SWord xx=Clamp(x2,SpanMin,ESpanMax);
//DeadCode JON 18Oct00 	UWord* bp=p+x;
//DeadCode JON 18Oct00 	for (;x<xx;x++) *bp++=((*bp)>>2)&~UWord(0x0618);
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		EdgeScan
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline SLong EdgeScan(EdgePtr e)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00  	const SLong x=e->xi>>16;
//DeadCode JON 18Oct00 	e->xi+=e->dxi;
//DeadCode JON 18Oct00 	return x;
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 inline EdgePtr EdgeSetup(const VData*,const VData*);
//DeadCode JON 18Oct00 inline EdgePtr EdgeSetup2(const VData&,const VData&);

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SetDestTexturePtr
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void SetDestTexturePtr(const SWord index)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 	if (hardwareVersion)
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 	{
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 		pdsttxt=(UByte*)win->DoGetLandBufferPtr(index);
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 	}
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 	else
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 		pdsttxt=NULL;	//fix software version if we want one
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		GetPalLookup
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 21 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void GetPalLookup()
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 	if (hardwareVersion && !ispalettised)
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 		palLookup=(UWord*)win->DoGetLandPalLookup();
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SetPalLookup
//DeadCode JON 18Oct00 //Author		PAul
//DeadCode JON 18Oct00 //Date			Mon 16 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void SetPalLookup()
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 //TempCode PD 03Dec99  	if (hardwareVersion && imagePalette!=NULL)
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 		win->DoSetLandPalLookup(imagePalette);
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		CreateLandTBuffer
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Sat 17 Apr 1999
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline ROWANSURFACEDESC* CreateLandTBuffer(SLong size)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00  	void* ptr=(void*)new UByte[sizeof(ROWANSURFACEDESC)+size*size];
//DeadCode JON 18Oct00 	if (ptr)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ROWANSURFACEDESC* rsd=(ROWANSURFACEDESC*)ptr;
//DeadCode JON 18Oct00 		rsd->dwWidth=rsd->dwHeight=size;
//DeadCode JON 18Oct00 		rsd->lPitch=size;
//DeadCode JON 18Oct00 		rsd->ddpfPixelFormat.dwRGBBitCount=8;
//DeadCode JON 18Oct00 		rsd->lpSurface=(void*)(ULong(ptr)+sizeof(ROWANSURFACEDESC));
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	return (ROWANSURFACEDESC*)ptr;
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 void DoGetTextureScales(SLong& num256,SLong& num128,SLong& num64,SLong& num32,SLong& num16,SLong& num8)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	num256=SOFT_256_TEXTURES;
//DeadCode JON 18Oct00 	num128=SOFT_128_TEXTURES;
//DeadCode JON 18Oct00 	num64=SOFT_64_TEXTURES;
//DeadCode JON 18Oct00 	num32=SOFT_32_TEXTURES;
//DeadCode JON 18Oct00 	num16=SOFT_16_TEXTURES;
//DeadCode JON 18Oct00 	num8=SOFT_8_TEXTURES;
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DoFreeLandTextureBuffers
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Sat 17 Apr 1999
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DoFreeLandTextureBuffers()
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	const SLong NUM_256_TEXTURES=SOFT_256_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_128_TEXTURES=SOFT_128_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_64_TEXTURES=SOFT_64_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_32_TEXTURES=SOFT_32_TEXTURES;
//DeadCode JON 18Oct00 	const SLong NUM_16_TEXTURES=SOFT_16_TEXTURES;
//DeadCode JON 18Oct00 	const SLong NUM_8_TEXTURES=SOFT_8_TEXTURES;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (sysram256maps)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		for (int i=NUM_256_TEXTURES-1;i>=0;i--)	delete[](UByte*)sysram256maps[i];
//DeadCode JON 18Oct00 		delete[]sysram256maps,sysram256maps=NULL;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	if (sysram128maps)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		for (int i=NUM_128_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram128maps[i];
//DeadCode JON 18Oct00 		delete[]sysram128maps,sysram128maps=NULL;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	if (sysram64maps)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		for (int i=NUM_64_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram64maps[i];
//DeadCode JON 18Oct00 		delete[]sysram64maps,sysram64maps=NULL;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	if (sysram32maps)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		for (int i=NUM_32_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram32maps[i];
//DeadCode JON 18Oct00 		delete[]sysram32maps,sysram32maps=NULL;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	if (sysram16maps)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		for (int i=NUM_16_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram16maps[i];
//DeadCode JON 18Oct00 		delete[]sysram16maps,sysram16maps=NULL;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	if (sysram8maps)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		for (int i=NUM_8_TEXTURES-1;i>=0;i--)		delete[](UByte*)sysram8maps[i];
//DeadCode JON 18Oct00 		delete[]sysram8maps,sysram8maps=NULL;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 void DoFreeTexture(const HTEXT& hText)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	if (hText!=HTEXTNULL) landTextureUsage[hText()]=0x00;
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoFreeTextures
//Author		Paul.   
//Date			Sat 17 Apr 1999
//------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DoFreeTextures()
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	for (int i=255;i>=0;i--) landTextureUsage[i]=0;
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoAllocateTexture
//Author		Paul.   
//Date			Sat 17 Apr 1999
//------------------------------------------------------------------------------
//DeadCode JON 18Oct00 HTEXT DoAllocateTexture(UByte textRez)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	const SLong NUM_256_TEXTURES=SOFT_256_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_128_TEXTURES=SOFT_128_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_64_TEXTURES=SOFT_64_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_32_TEXTURES=SOFT_32_TEXTURES;
//DeadCode JON 18Oct00 	const SLong NUM_16_TEXTURES=SOFT_16_TEXTURES;
//DeadCode JON 18Oct00 	const SLong NUM_8_TEXTURES=SOFT_8_TEXTURES;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	UByte *pmin,*pmax;
//DeadCode JON 18Oct00 	switch (textRez)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	case 0:
//DeadCode JON 18Oct00 	pmin=landTextureUsage;
//DeadCode JON 18Oct00 	pmax=landTextureUsage+NUM_256_TEXTURES;
//DeadCode JON 18Oct00 	break;
//DeadCode JON 18Oct00 	case 1:
//DeadCode JON 18Oct00 	pmin=landTextureUsage+NUM_256_TEXTURES;
//DeadCode JON 18Oct00 	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES;
//DeadCode JON 18Oct00 	break;
//DeadCode JON 18Oct00 	case 2:
//DeadCode JON 18Oct00 	pmin=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES;
//DeadCode JON 18Oct00 	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES;
//DeadCode JON 18Oct00 	break;
//DeadCode JON 18Oct00 	case 3:
//DeadCode JON 18Oct00 	pmin=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES;
//DeadCode JON 18Oct00 	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES;
//DeadCode JON 18Oct00 	break;
//DeadCode JON 18Oct00 	case 4:
//DeadCode JON 18Oct00 	pmin=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES;
//DeadCode JON 18Oct00 	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES;
//DeadCode JON 18Oct00 	break;
//DeadCode JON 18Oct00 	case 5:
//DeadCode JON 18Oct00 	pmin=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES;
//DeadCode JON 18Oct00 	pmax=landTextureUsage+NUM_256_TEXTURES+NUM_128_TEXTURES+NUM_64_TEXTURES+NUM_32_TEXTURES+NUM_16_TEXTURES+NUM_8_TEXTURES;
//DeadCode JON 18Oct00 	break;
//DeadCode JON 18Oct00 	default:
//DeadCode JON 18Oct00 	assert(false&&"Bad texture resolution requestsed");
//DeadCode JON 18Oct00 	break;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	while (ULong(pmin)!=ULong(pmax))
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		if (*pmin==0x00)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			HTEXT retVal=HTEXT((ULong(pmin)-ULong(landTextureUsage)));
//DeadCode JON 18Oct00 			*pmin=0xFF;
//DeadCode JON 18Oct00 			return retVal;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 		pmin++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	return HTEXTNULL;
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DoCreateLandTBuffers
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Sat 17 Apr 1999
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DoCreateLandTBuffers()
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	const SLong NUM_256_TEXTURES=SOFT_256_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_128_TEXTURES=SOFT_128_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_64_TEXTURES=SOFT_64_TEXTURES;
//DeadCode JON 18Oct00 	const SLong	NUM_32_TEXTURES=SOFT_32_TEXTURES;
//DeadCode JON 18Oct00 	const SLong NUM_16_TEXTURES=SOFT_16_TEXTURES;
//DeadCode JON 18Oct00 	const SLong NUM_8_TEXTURES=SOFT_8_TEXTURES;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	typedef ROWANSURFACEDESC* LPROWANSURFACEDESC;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	sysram256maps=new LPROWANSURFACEDESC[NUM_256_TEXTURES];
//DeadCode JON 18Oct00 	sysram128maps=new LPROWANSURFACEDESC[NUM_128_TEXTURES];
//DeadCode JON 18Oct00 	sysram64maps=new LPROWANSURFACEDESC[NUM_64_TEXTURES];
//DeadCode JON 18Oct00 	sysram32maps=new LPROWANSURFACEDESC[NUM_32_TEXTURES];
//DeadCode JON 18Oct00 	sysram16maps=new LPROWANSURFACEDESC[NUM_16_TEXTURES];
//DeadCode JON 18Oct00 	sysram8maps=new LPROWANSURFACEDESC[NUM_8_TEXTURES];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (!sysram256maps ||
//DeadCode JON 18Oct00 		!sysram128maps ||
//DeadCode JON 18Oct00 		!sysram64maps ||
//DeadCode JON 18Oct00 		!sysram32maps ||
//DeadCode JON 18Oct00 		!sysram16maps ||
//DeadCode JON 18Oct00 		!sysram8maps)
//DeadCode JON 18Oct00 		_Error.EmitSysErr("Failed to create software landscape textures");
//DeadCode JON 18Oct00 	for (int i=NUM_256_TEXTURES-1;i>=0;i--)	sysram256maps[i]=CreateLandTBuffer(256);
//DeadCode JON 18Oct00 	for (i=NUM_128_TEXTURES-1;i>=0;i--)		sysram128maps[i]=CreateLandTBuffer(128);
//DeadCode JON 18Oct00 	for (i=NUM_64_TEXTURES-1;i>=0;i--)		sysram64maps[i]=CreateLandTBuffer(64);
//DeadCode JON 18Oct00 	for (i=NUM_32_TEXTURES-1;i>=0;i--)		sysram32maps[i]=CreateLandTBuffer(32);
//DeadCode JON 18Oct00 	for (i=NUM_16_TEXTURES-1;i>=0;i--)		sysram16maps[i]=CreateLandTBuffer(16);
//DeadCode JON 18Oct00 	for (i=NUM_8_TEXTURES-1;i>=0;i--)		sysram8maps[i]=CreateLandTBuffer(8);
//DeadCode JON 18Oct00 	DoFreeTextures();
//DeadCode JON 18Oct00 }
inline void ClearTexturePointers();
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetTexturePointers
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
void SetTexturePointers()
{
	SWord fileNumOffset;
	SWord i,j;
	FileNum fn;
	fileblockptr fbp;

	if (loadedTextures) ClearTexturePointers();		

//DeadCode JON 18Oct00 	hardwareVersion=hardVer;
	loadedTextures=true;

	fileNumOffset=SWord(FIL_IMG0000H-FIL_IMG0000);

//DeadCode JON 18Oct00 	landPalette=imagePalette=new UByte[3*256*Max_Textures];

	for (j=0;j<Max_Textures;j++)
	{
		fn=FileNum(j+BaseTexture+fileNumOffset);
		fileblock fb(fn);
		imagePtrs[j]=new ImageMapDesc;
		imagePtrs[j]->FixLbmImageMap(&fb);
		imagePtrs[j]->hTextureMap=0;
#pragma warnmsg ( "rob - why do I need this???" )
		imagePtrs[j]->isMasked=0; // dunno why this should be needed...
		imageData[j]=imagePtrs[j]->body;

//DeadCode JON 18Oct00 		if (imagePtrs[j]->palette)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			for (int k=0;k<3*256;k++)
//DeadCode JON 18Oct00 				imagePalette[k+(j*3*256)]=imagePtrs[j]->palette[k];
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 		else 
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			for (int k=0;k<3*256;k++)
//DeadCode JON 18Oct00 				imagePalette[k+(j*3*256)]=0;
//DeadCode JON 18Oct00 		}
	}
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetImageFromArea
//Author		Paul.   
//Date			Fri 28 Jan 2000
//
//------------------------------------------------------------------------------
ImageMapDescPtr GetImageFromArea(UByte at)
{
 	ImageMapDescPtr imgp;
	imgp=imagePtrs[(at&0x1F)];
	return imgp;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearTexturePointers
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
inline void ClearTexturePointers()
{
	SWord i;

	if (loadedTextures)
	{
		for (i=0;i<Max_Textures;i++) delete imagePtrs[i],imagePtrs[i]=NULL;
		loadedTextures=false;
	}
//DeadCode JON 18Oct00 	delete[]landPalette;
//DeadCode JON 18Oct00 	landPalette=NULL;
}

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		ResetMem
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void ResetMem(void* pp,ULong ll)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	_asm{
//DeadCode JON 18Oct00 	xor	eax,eax;
//DeadCode JON 18Oct00 	dec	eax;
//DeadCode JON 18Oct00 	mov edi,pp;
//DeadCode JON 18Oct00 	mov ebx,ll;
//DeadCode JON 18Oct00 	mov	ecx,4;
//DeadCode JON 18Oct00 	sub	ecx,edi;
//DeadCode JON 18Oct00 	and	ecx,3;
//DeadCode JON 18Oct00 	sub	ebx,ecx;
//DeadCode JON 18Oct00 	rep	stosb;
//DeadCode JON 18Oct00 	mov	ecx,ebx;
//DeadCode JON 18Oct00 	shr	ecx,2;
//DeadCode JON 18Oct00 	rep	stosd;
//DeadCode JON 18Oct00 	and	ebx,3;
//DeadCode JON 18Oct00 	mov	ecx,ebx;
//DeadCode JON 18Oct00 	rep	stosb;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ClearRecords
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void ClearRecords(const UByte count)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	ULong dlen=recordsUsed*recordsUsed;
//DeadCode JON 18Oct00 	void* dstart=(void*)edgeRecord;
//DeadCode JON 18Oct00 	ResetMem(dstart,dlen);
//DeadCode JON 18Oct00 	if (0!=clipRecsUsed)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		dlen=clipRecsUsed;
//DeadCode JON 18Oct00 		dstart=(void*)clipRecord;
//DeadCode JON 18Oct00 		ResetMem(dstart,dlen);
//DeadCode JON 18Oct00 		clipRecsUsed=0;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	recordsUsed=count;
//DeadCode JON 18Oct00 	curEdge=EdgeList;
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		MakeRecIndex
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 template<class t> inline t MakeRecIndex(const t a,const t b)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	return (a>=b)?b*recordsUsed+a:a*recordsUsed+b;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 //DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		EdgeSetup
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline EdgePtr EdgeSetup(const VData* va,const VData* vb)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	const ULong _indexableLimit=ULong(EdgeList+Indexable_Edges);
//DeadCode JON 18Oct00 	const ULong _realEdgeLimit=ULong(EdgeList+Real_Max_Edges);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//check whether we have already created the data for this edge
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SWord ri=MakeRecIndex(va->v,vb->v);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	EdgePtr e=curEdge++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (ULong(e)<_indexableLimit &&	0xFF!=edgeRecord[ri])
//DeadCode JON 18Oct00 		return EdgeList+edgeRecord[ri];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ULong ei=e-EdgeList;
//DeadCode JON 18Oct00 	edgeRecord[ri]=ei;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	assert(ULong(e)<_realEdgeLimit&&"Edge record o'flow");
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong sf,dx=vb->x-va->x,dy=vb->y-va->y;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	e->ymin=va->y;
//DeadCode JON 18Oct00 	e->ymax=vb->y;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dy)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		e->xi=va->x<<16;
//DeadCode JON 18Oct00 		e->dxi=(dx<<16)/dy;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	return e;
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		EdgeSetup
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 10 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline EdgePtr EdgeSetup(const VData* va,const VData* vb,SWord scale)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	const ULong _indexableLimit=ULong(EdgeList+Indexable_Edges);
//DeadCode JON 18Oct00 	const ULong _realEdgeLimit=ULong(EdgeList+Real_Max_Edges);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//check whether we have already created the data for this edge
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SWord ri=MakeRecIndex(va->v,vb->v);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	EdgePtr e=curEdge++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (ULong(e)<_indexableLimit &&	0xFF!=edgeRecord[ri])
//DeadCode JON 18Oct00 		return EdgeList+edgeRecord[ri];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ULong ei=e-EdgeList;
//DeadCode JON 18Oct00 	edgeRecord[ri]=ei;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	assert(ULong(e)<_realEdgeLimit&&"Edge record o'flow");
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong sf,dx=vb->x-va->x,dy=vb->y-va->y;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	e->ymin=va->y;
//DeadCode JON 18Oct00 	e->ymax=vb->y;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dy)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		e->xi=va->x<<16;
//DeadCode JON 18Oct00 		e->dxi=(dx<<(16+scale))/dy;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	return e;
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		EdgeSetup2
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 16 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline EdgePtr EdgeSetup2(const VData& va,const VData& vb)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	const ULong _realEdgeLimit=ULong(EdgeList+Real_Max_Edges);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	EdgePtr e=curEdge++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	assert(ULong(e)<_realEdgeLimit&&"Edge record o'flow");
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong sf,dx=vb.x-va.x,dy=vb.y-va.y;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	e->ymin=va.y;
//DeadCode JON 18Oct00 	e->ymax=vb.y;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dy)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		e->xi=va.x<<16;
//DeadCode JON 18Oct00 		e->dxi=(dx<<16)/dy;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	return e;
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScaledTextureWidth
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void ScaledTextureWidth(const SWord scale)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	if (scale<3) 
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		physWidth=256>>scale;
//DeadCode JON 18Oct00 		pixelSkip=1<<scale;
//DeadCode JON 18Oct00 		byteScale=scale;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else 
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		physWidth=256>>scale;
//DeadCode JON 18Oct00 		pixelSkip=1<<(scale-3);
//DeadCode JON 18Oct00 		byteScale=scale-3;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		BoxClipTest
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline SWord BoxClipTest(const SWord x,const SWord y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	//return 0 if the box is completely off the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (x+physWidth<0 || y+physWidth<0 ||
//DeadCode JON 18Oct00 		x>TextureWidth || y>TextureWidth)
//DeadCode JON 18Oct00 		return SWord(0);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//return 1 if the box is completely contained within
//DeadCode JON 18Oct00 	//the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (x>=0 && x+physWidth<=TextureWidth &&
//DeadCode JON 18Oct00 		y>=0 && y+physWidth<=TextureWidth)
//DeadCode JON 18Oct00 		return SWord(1);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//return -1 if some overlap is detected
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	return SWord(-1);
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 void SortedTriangle8(VData*);
//DeadCode JON 18Oct00 void SortedTriangle16(VData*);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 void SortedTriangle28(VData,VData,VData);
//DeadCode JON 18Oct00 void SortedTriangle216(VData,VData,VData);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 void ShadowTriangle8(VData,VData,VData);
//DeadCode JON 18Oct00 void ShadowTriangle16(VData,VData,VData);

//DEADCODE JON 4/12/00 void DDShadowTriangle8(ROWANSURFACEDESC*,VData,VData,VData,SWord);
//DEADCODE JON 4/12/00 void DDShadowTriangle16(ROWANSURFACEDESC*,VData,VData,VData,SWord);

//DeadCode JON 18Oct00 void DrawShadowTriangle( CLib3D* lib3d,									//JON 4/12/00
//DeadCode JON 18Oct00 						VData v0,VData v1,VData v2,
//DeadCode JON 18Oct00 						SWord scale);

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		Triangle
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void Triangle(SWord v1,SWord v2,SWord v3)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	VData v[3];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	v[0].x=pointdef[v1].x>>tile_scale;
//DeadCode JON 18Oct00 	v[0].y=(256-pointdef[v1].z)>>tile_scale;
//DeadCode JON 18Oct00 	v[0].v=v1;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	v[1].x=pointdef[v2].x>>tile_scale;
//DeadCode JON 18Oct00 	v[1].y=(256-pointdef[v2].z)>>tile_scale;
//DeadCode JON 18Oct00 	v[1].v=v2;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	v[2].x=pointdef[v3].x>>tile_scale;
//DeadCode JON 18Oct00 	v[2].y=(256-pointdef[v3].z)>>tile_scale;
//DeadCode JON 18Oct00 	v[2].v=v3;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (v[0].y>v[1].y) Swap(v[0],v[1]);
//DeadCode JON 18Oct00 	if (v[0].y>v[2].y) Swap(v[0],v[2]);
//DeadCode JON 18Oct00 	if (v[1].y>v[2].y) Swap(v[1],v[2]);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (ispalettised)	SortedTriangle8(v);
//DeadCode JON 18Oct00 	else				SortedTriangle16(v);
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 typedef void (*clipfn) (const XData*,const XData*,XData*);

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		ClipToTop
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void ClipToTop(const XData* vin,const XData* vout,XData* vclip)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong dx=vout->x-vin->x;
//DeadCode JON 18Oct00 	SLong dy=vout->y-vin->y;
//DeadCode JON 18Oct00 	SLong ndy=targetBox.top-vin->y;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dy==0)
//DeadCode JON 18Oct00 		*vclip=*vin;
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		vclip->y=targetBox.top;
//DeadCode JON 18Oct00 		vclip->x=vin->x+((dx)?dx*ndy/dy:dx);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//fill in clip codes for the clipped point
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (vclip->x<targetBox.left)			vclip->cf=cf_lft;
//DeadCode JON 18Oct00 	else if (vclip->x>targetBox.right)		vclip->cf=cf_rgt;
//DeadCode JON 18Oct00 	else									vclip->cf=cf_null;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		ClipToBot
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void ClipToBot(const XData* vin,const XData* vout,XData* vclip)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong dx=vout->x-vin->x;
//DeadCode JON 18Oct00 	SLong dy=vout->y-vin->y;
//DeadCode JON 18Oct00 	SLong ndy=targetBox.bottom-vin->y;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dy==0)
//DeadCode JON 18Oct00 		*vclip=*vin;
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		vclip->y=targetBox.bottom;
//DeadCode JON 18Oct00 		vclip->x=vin->x+((dx)?dx*ndy/dy:dx);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//fill in clip codes for the clipped point
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (vclip->x<targetBox.left)			vclip->cf=cf_lft;
//DeadCode JON 18Oct00 	else if (vclip->x>targetBox.right)		vclip->cf=cf_rgt;
//DeadCode JON 18Oct00 	else									vclip->cf=cf_null;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		ClipToLft
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void ClipToLft(const XData* vin,const XData* vout,XData* vclip)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong dy=vout->y-vin->y;
//DeadCode JON 18Oct00 	SLong dx=vout->x-vin->x;
//DeadCode JON 18Oct00 	SLong ndx=targetBox.left-vin->x;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dx==0)
//DeadCode JON 18Oct00 		*vclip=*vin;
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		vclip->x=targetBox.left;
//DeadCode JON 18Oct00 		vclip->y=vin->y+((dy)?dy*ndx/dx:dy);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	vclip->cf=cf_null;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		ClipToRgt
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void ClipToRgt(const XData* vin,const XData* vout,XData* vclip)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong dy=vout->y-vin->y;
//DeadCode JON 18Oct00 	SLong dx=vout->x-vin->x;
//DeadCode JON 18Oct00 	SLong ndx=targetBox.right-vin->x;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dx==0)
//DeadCode JON 18Oct00 		*vclip=*vin;
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		vclip->x=targetBox.right;
//DeadCode JON 18Oct00 		vclip->y=vin->y+((dy)?dy*ndx/dx:dy);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	vclip->cf=cf_null;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		Clip
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 16 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void Clip(	const 		clipfn crtn,
//DeadCode JON 18Oct00 					const 		UByte f,
//DeadCode JON 18Oct00 					XDataPtr* 	spoly,
//DeadCode JON 18Oct00 					SWord 		si,
//DeadCode JON 18Oct00 					SWord 		ni,
//DeadCode JON 18Oct00 					XDataPtr*	dpoly,
//DeadCode JON 18Oct00 					SWord& 		di,
//DeadCode JON 18Oct00 					XData*&		allocv)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	if (0==(spoly[si]->cf&f)){
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		dpoly[di++]=spoly[si];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (0!=(spoly[ni]->cf&f)){
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		 	(*crtn)(spoly[si],spoly[ni],allocv);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			dpoly[di++]=allocv++;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else if (0==(spoly[ni]->cf&f)){
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		(*crtn)(spoly[ni],spoly[si],allocv);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		dpoly[di++]=allocv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 //DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DoClip
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 SWord DoClip(const SWord v1,const SWord v2,const SWord v3,XDataPtr*& np)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	static XData vc[16];
//DeadCode JON 18Oct00 	static XDataPtr polydef[16];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	XDataPtr newv=vc+3;
//DeadCode JON 18Oct00 	XDataPtr newdef[16];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SWord pntcnt,limit;
//DeadCode JON 18Oct00 	SWord newpc;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	np=polydef;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	vc[0].x=xoffset+(pointdef[v1].x>>tile_scale);
//DeadCode JON 18Oct00 	vc[0].y=yoffset+((256-pointdef[v1].z)>>tile_scale);
//DeadCode JON 18Oct00 	vc[0].cf=clipRecord[v1];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	vc[1].x=xoffset+(pointdef[v2].x>>tile_scale);
//DeadCode JON 18Oct00 	vc[1].y=yoffset+((256-pointdef[v2].z)>>tile_scale);
//DeadCode JON 18Oct00 	vc[1].cf=clipRecord[v2];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	vc[2].x=xoffset+(pointdef[v3].x>>tile_scale);
//DeadCode JON 18Oct00 	vc[2].y=yoffset+((256-pointdef[v3].z)>>tile_scale);
//DeadCode JON 18Oct00 	vc[2].cf=clipRecord[v3];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	polydef[0]=vc;
//DeadCode JON 18Oct00 	polydef[1]=vc+1;
//DeadCode JON 18Oct00 	polydef[2]=vc+2;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	pntcnt=3;
//DeadCode JON 18Oct00 	limit=pntcnt-1;
//DeadCode JON 18Oct00 	newpc=0;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//clip against the top of the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (SWord i=0,j=1;i<limit;i++,j++)
//DeadCode JON 18Oct00 		Clip(ClipToTop,cf_top,polydef,i,j,newdef,newpc,newv);
//DeadCode JON 18Oct00 	Clip(ClipToTop,cf_top,polydef,i,0,newdef,newpc,newv);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (3>(pntcnt=newpc)) return pntcnt;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	limit=pntcnt-1;
//DeadCode JON 18Oct00 	newpc=0;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//clip against the base of the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (i=0,j=1;i<limit;i++,j++)
//DeadCode JON 18Oct00 	 	Clip(ClipToBot,cf_bot,newdef,i,j,polydef,newpc,newv);
//DeadCode JON 18Oct00  	Clip(ClipToBot,cf_bot,newdef,i,0,polydef,newpc,newv);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (3>(pntcnt=newpc)) return pntcnt;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	limit=pntcnt-1;
//DeadCode JON 18Oct00 	newpc=0;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//clip against the left of the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (i=0,j=1;i<limit;i++,j++)
//DeadCode JON 18Oct00 	 	Clip(ClipToLft,cf_lft,polydef,i,j,newdef,newpc,newv);
//DeadCode JON 18Oct00  	Clip(ClipToLft,cf_lft,polydef,i,0,newdef,newpc,newv);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (3>(pntcnt=newpc)) return pntcnt;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	limit=pntcnt-1;
//DeadCode JON 18Oct00 	newpc=0;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//clip against the right of the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (i=0,j=1;i<limit;i++,j++)
//DeadCode JON 18Oct00 	 	Clip(ClipToRgt,cf_rgt,newdef,i,j,polydef,newpc,newv);
//DeadCode JON 18Oct00  	Clip(ClipToRgt,cf_rgt,newdef,i,0,polydef,newpc,newv);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	return newpc;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		Triangle2
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 16 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void Triangle2(VData v1,VData v2,VData v3)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	if (v1.y>v2.y) Swap(v1,v2);
//DeadCode JON 18Oct00 	if (v1.y>v3.y) Swap(v1,v3);
//DeadCode JON 18Oct00 	if (v2.y>v3.y) Swap(v2,v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (ispalettised)	SortedTriangle28(v1,v2,v3);
//DeadCode JON 18Oct00 	else				SortedTriangle216(v1,v2,v3);
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		ClippedTriangle
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 15 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void ClippedTriangle(SWord v1,SWord v2,SWord v3)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	XDataPtr* cpp;
//DeadCode JON 18Oct00 	XDataPtr cp;
//DeadCode JON 18Oct00 	VData poly[3];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SWord pntCnt;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	pntCnt=DoClip(v1,v2,v3,cpp);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (pntCnt>=3)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		cp=*cpp++;
//DeadCode JON 18Oct00 		poly[0].x=cp->x-xoffset;
//DeadCode JON 18Oct00 		poly[0].y=cp->y-yoffset;
//DeadCode JON 18Oct00 		cp=*cpp++;
//DeadCode JON 18Oct00 		poly[2].x=cp->x-xoffset;
//DeadCode JON 18Oct00 		poly[2].y=cp->y-yoffset;
//DeadCode JON 18Oct00 		cp=*cpp++;
//DeadCode JON 18Oct00 		pntCnt-=2;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		while (pntCnt--)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 		 	poly[1]=poly[2];
//DeadCode JON 18Oct00 			poly[2].x=cp->x-xoffset;
//DeadCode JON 18Oct00 			poly[2].y=cp->y-yoffset;
//DeadCode JON 18Oct00 			cp=*cpp++;
//DeadCode JON 18Oct00 			Triangle2(poly[0],poly[1],poly[2]);
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 void PolyOutline(UByte*);
//DeadCode JON 18Oct00 void DoLine(const SWord,const SWord);
//DeadCode JON 18Oct00 void DoLClip(const SWord,const SWord);

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Render2Map
//Author		Paul.   
//Date			Wed 15 Jul 1998
//------------------------------------------------------------------------------
//DEADCODE JON 4/14/00 void Render2Map(UByte* p,const SWord xo,const SWord yo,const SWord scale)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 	AltPointsHdr* a;
//DEADCODE JON 4/14/00 	DrawDataHdr* d;
//DEADCODE JON 4/14/00 	UByte** pt;
//DEADCODE JON 4/14/00 	SWord clipFlag;
//DEADCODE JON 4/14/00 	SWord primCount;
//DEADCODE JON 4/14/00 	UByte lineCol;
//DEADCODE JON 4/14/00 	UByte sectionCount;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	tile_scale=scale;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	SetDestTexturePtr(tile_scale);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	a=(AltPointsHdr*)p;
//DEADCODE JON 4/14/00 	p+=sizeof(AltPointsHdr);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	//clear records of generated edges
//DEADCODE JON 4/14/00 	ClearRecords(a->vertexCount);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	pointdef=(PointDef*)p;
//DEADCODE JON 4/14/00 	p+=sizeof(PointDef)*a->vertexCount;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	d=(DrawDataHdr*)p;
//DEADCODE JON 4/14/00 	p+=sizeof(DrawDataHdr);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	ScaledTextureWidth(scale);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	//Initialise pointer to texture data
//DEADCODE JON 4/14/00 	pt=/*(scale<3)?*/imageData;		//DEAD :imageData2;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	xoffset=xo;
//DEADCODE JON 4/14/00 	yoffset=yo;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	clipFlag=BoxClipTest(xo,yo);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	if (!clipFlag) return;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	if (1==clipFlag)
//DEADCODE JON 4/14/00 	{
//DEADCODE JON 4/14/00 		//no clipping is needed
//DEADCODE JON 4/14/00 		primCount=d->noOfPolys;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		while (primCount--)
//DEADCODE JON 4/14/00 		{
//DEADCODE JON 4/14/00 			//get pointer to source texture
//DEADCODE JON 4/14/00 			psrctxt=pt[(*p&0x1F)];
//DEADCODE JON 4/14/00 			p++;
//DEADCODE JON 4/14/00 			UByte triCount=*p++;
//DEADCODE JON 4/14/00 			while (triCount--)
//DEADCODE JON 4/14/00 			{
//DEADCODE JON 4/14/00 				UByte fanCount=*p++;
//DEADCODE JON 4/14/00 				SWord v1=*p++;
//DEADCODE JON 4/14/00 				SWord v3=*p++;
//DEADCODE JON 4/14/00 				while (fanCount--)
//DEADCODE JON 4/14/00 				{
//DEADCODE JON 4/14/00 					SWord v2=v3;
//DEADCODE JON 4/14/00 					v3=*p++;
//DEADCODE JON 4/14/00 					Triangle(v1,v2,v3);
//DEADCODE JON 4/14/00 				}
//DEADCODE JON 4/14/00 			}
//DEADCODE JON 4/14/00 		}
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		//add roads, railways and rivers
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		if (Save_Data.detail_3d[DETAIL3D_ROUTES] && scale<4 && d->noOfLines!=0) 
//DEADCODE JON 4/14/00 		{
//DEADCODE JON 4/14/00 			primCount=d->noOfLines;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			while (primCount--) 
//DEADCODE JON 4/14/00 			{
//DEADCODE JON 4/14/00 				lineCol=*p++;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				//check line color against route types
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				switch (lineCol)
//DEADCODE JON 4/14/00 				{
//DEADCODE JON 4/14/00 				case RT_AirField:
//DEADCODE JON 4/14/00 					lineCol=249;		//??
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_HedgerowThick:
//DEADCODE JON 4/14/00 					lineCol=71;			//11,35,11
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_HedgerowThin:
//DEADCODE JON 4/14/00 					lineCol=77;			//11,35,11
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MajorRiver:
//DEADCODE JON 4/14/00 					lineCol=39;			//32,40,72
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MinorRiver:
//DEADCODE JON 4/14/00 					lineCol=36;			//42,49,79
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_Tributary:
//DEADCODE JON 4/14/00 					lineCol=36;			//42,49,79
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MinorRoad:
//DEADCODE JON 4/14/00 					lineCol=251;		//71,60,44
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_Footpath:
//DEADCODE JON 4/14/00 					lineCol=203;		//106,89,65
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MajorRail:
//DEADCODE JON 4/14/00 					lineCol=0;			//22,22,22
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MinorRail:
//DEADCODE JON 4/14/00 					lineCol=2;			//30,30,30
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_ARoad:
//DEADCODE JON 4/14/00 					lineCol=249;		//55,58,55
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_BRoad:
//DEADCODE JON 4/14/00 					lineCol=250;		//68,74,68
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 //				case RT_magic:
//DEADCODE JON 4/14/00 //					lineCol=111;
//DEADCODE JON 4/14/00 //					break;
//DEADCODE JON 4/14/00 				default:
//DEADCODE JON 4/14/00 					lineCol=ARTWORKMASK;
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				}
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				if (lineCol!=ARTWORKMASK)
//DEADCODE JON 4/14/00 				{
//DEADCODE JON 4/14/00 					if (ispalettised)	currentRouteColor8=lineCol;
//DEADCODE JON 4/14/00 				 	else	currentRouteColor16=palLookup[lineCol];
//DEADCODE JON 4/14/00 				}
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				sectionCount=*p++;
//DEADCODE JON 4/14/00 				SWord v2=*p++;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				while (--sectionCount!=0) 
//DEADCODE JON 4/14/00 				{
//DEADCODE JON 4/14/00 					SWord v1=v2;
//DEADCODE JON 4/14/00 					v2=*p++;
//DEADCODE JON 4/14/00 					if (lineCol!=ARTWORKMASK) DoLine(v1,v2);
//DEADCODE JON 4/14/00 				}
//DEADCODE JON 4/14/00 			}
//DEADCODE JON 4/14/00 		}
//DEADCODE JON 4/14/00 	}
//DEADCODE JON 4/14/00 	else
//DEADCODE JON 4/14/00 	{
//DEADCODE JON 4/14/00 		//some clipping is needed
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		clipRecsUsed=a->vertexCount;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		primCount=d->noOfPolys;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		while (primCount--)
//DEADCODE JON 4/14/00 		{
//DEADCODE JON 4/14/00 			//get pointer to source texture
//DEADCODE JON 4/14/00 			psrctxt=pt[(*p&0x1F)];
//DEADCODE JON 4/14/00 			p++;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			UByte triCount=*p++;
//DEADCODE JON 4/14/00 			while (triCount--)
//DEADCODE JON 4/14/00 			{
//DEADCODE JON 4/14/00 				UByte fanCount=*p++;
//DEADCODE JON 4/14/00 				SWord v1=*p++;
//DEADCODE JON 4/14/00 				SWord v3=*p++;
//DEADCODE JON 4/14/00 				UByte c1,c3;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				c1=SetClipFlags(v1);
//DEADCODE JON 4/14/00 				c3=SetClipFlags(v3);
//DEADCODE JON 4/14/00 				while (fanCount--)
//DEADCODE JON 4/14/00 				{
//DEADCODE JON 4/14/00 					SWord v2=v3;
//DEADCODE JON 4/14/00 					UByte c2=c3;
//DEADCODE JON 4/14/00 					v3=*p++;
//DEADCODE JON 4/14/00 					c3=SetClipFlags(v3);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 					if ((c1|c2|c3)==cf_null)
//DEADCODE JON 4/14/00 						Triangle(v1,v2,v3);
//DEADCODE JON 4/14/00 					else if ((c1&c2&c3)==cf_null)
//DEADCODE JON 4/14/00 					     	ClippedTriangle(v1,v2,v3);
//DEADCODE JON 4/14/00 				}
//DEADCODE JON 4/14/00 			}
//DEADCODE JON 4/14/00 		}
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		//add roads, railways and rivers
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		if (scale<4 && d->noOfLines!=0) 
//DEADCODE JON 4/14/00 		{
//DEADCODE JON 4/14/00 			primCount=d->noOfLines;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			while (primCount--) 
//DEADCODE JON 4/14/00 			{
//DEADCODE JON 4/14/00 				lineCol=*p++;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				//check line color against route types
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				switch (lineCol)
//DEADCODE JON 4/14/00 				{
//DEADCODE JON 4/14/00 				case RT_AirField:
//DEADCODE JON 4/14/00 					lineCol=249;		//??
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_HedgerowThick:
//DEADCODE JON 4/14/00 					lineCol=71;			//11,35,11
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_HedgerowThin:
//DEADCODE JON 4/14/00 					lineCol=77;			//11,35,11
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MajorRiver:
//DEADCODE JON 4/14/00 					lineCol=39;			//32,40,72
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MinorRiver:
//DEADCODE JON 4/14/00 					lineCol=36;			//42,49,79
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_Tributary:
//DEADCODE JON 4/14/00 					lineCol=36;			//42,49,79
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MinorRoad:
//DEADCODE JON 4/14/00 					lineCol=251;		//71,60,44
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_Footpath:
//DEADCODE JON 4/14/00 					lineCol=203;		//106,89,65
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MajorRail:
//DEADCODE JON 4/14/00 					lineCol=0;			//22,22,22
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_MinorRail:
//DEADCODE JON 4/14/00 					lineCol=2;			//30,30,30
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_ARoad:
//DEADCODE JON 4/14/00 					lineCol=249;		//55,58,55
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				case RT_BRoad:
//DEADCODE JON 4/14/00 					lineCol=250;		//68,74,68
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 //				case RT_magic:
//DEADCODE JON 4/14/00 //					lineCol=111;
//DEADCODE JON 4/14/00 //					break;
//DEADCODE JON 4/14/00 				default:
//DEADCODE JON 4/14/00 					lineCol=ARTWORKMASK;
//DEADCODE JON 4/14/00 					break;
//DEADCODE JON 4/14/00 				}
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				if (lineCol!=ARTWORKMASK)
//DEADCODE JON 4/14/00 				{
//DEADCODE JON 4/14/00 					if (ispalettised)	currentRouteColor8=lineCol;
//DEADCODE JON 4/14/00 				 	else	currentRouteColor16=palLookup[lineCol];
//DEADCODE JON 4/14/00 				}
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				sectionCount=*p++;
//DEADCODE JON 4/14/00 				SWord v2=*p++;
//DEADCODE JON 4/14/00 				UByte c2=SetClipFlags(v2);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 				while (--sectionCount!=0) 
//DEADCODE JON 4/14/00 				{
//DEADCODE JON 4/14/00 					SWord v1=v2;
//DEADCODE JON 4/14/00 					v2=*p++;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 					if (lineCol!=ARTWORKMASK)
//DEADCODE JON 4/14/00 					{
//DEADCODE JON 4/14/00 						UByte c1=c2;
//DEADCODE JON 4/14/00 						c2=SetClipFlags(v2);
//DEADCODE JON 4/14/00 						if ((c1|c2)==cf_null)	DoLine(v1,v2);
//DEADCODE JON 4/14/00 						else if ((c1&c2)==cf_null)	DoLClip(v1,v2);
//DEADCODE JON 4/14/00 					}
//DEADCODE JON 4/14/00 				}
//DEADCODE JON 4/14/00 			}
//DEADCODE JON 4/14/00 		}
//DEADCODE JON 4/14/00 	}
//DEADCODE JON 4/14/00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SetInitialLandTextureCoordinates
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 17 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SetInitialLandTextureCoordinates(const SLong x,const SLong z)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	//set initial coordinates for landscape update tests
//DeadCode JON 18Oct00 	//the inner level (0) will cover a 1.3km square area
//DeadCode JON 18Oct00 	//and will be updated after every 80m of travel.
//DeadCode JON 18Oct00 	//Subsequent squares will cover 4 times the area and
//DeadCode JON 18Oct00 	//will require updates at half the rate of the previous
//DeadCode JON 18Oct00 	//level.
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong	update_size,
//DeadCode JON 18Oct00 			square_halfsize;
//DeadCode JON 18Oct00 	ULong	update_mask;
//DeadCode JON 18Oct00 	SLong	maxTextureLevels;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//DeadCode JON 18Oct00 //						Max_TextureLevelsMAX:Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 	maxTextureLevels=Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 	
//DeadCode JON 18Oct00 	update_size=Grid_Width>>3;
//DeadCode JON 18Oct00 	square_halfsize=Grid_Width>>1;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (int i=0;i<maxTextureLevels;i++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		update_mask=~ULong(update_size-1);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		land_x[i]=(x&update_mask)-square_halfsize;
//DeadCode JON 18Oct00 		land_z[i]=(z&update_mask)-square_halfsize;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		//signal that all the blocks 
//DeadCode JON 18Oct00 		//need to be regenerated
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		update_req[i]=true;
//DeadCode JON 18Oct00 		update_size+=update_size;
//DeadCode JON 18Oct00 		square_halfsize+=square_halfsize;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		CheckForLandUpdate
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 17 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 bool CheckForLandUpdate(const SLong x,const SLong z)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	//check each landscape detail level to 
//DeadCode JON 18Oct00 	//see if any update is required
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	bool retval=false;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ULong	mask_value;
//DeadCode JON 18Oct00 	SLong	update_size;
//DeadCode JON 18Oct00 	SLong	square_halfsize;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong 	level_basex,
//DeadCode JON 18Oct00 			level_basez;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong	maxTextureLevels;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 ///	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//DeadCode JON 18Oct00 //						Max_TextureLevelsMAX:Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 	maxTextureLevels=Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	update_size=Grid_Width>>3;
//DeadCode JON 18Oct00 	square_halfsize=Grid_Width>>1;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (int i=0;i<maxTextureLevels;i++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		mask_value=~ULong(update_size-1);
//DeadCode JON 18Oct00 		level_basex=(x&mask_value)-square_halfsize;
//DeadCode JON 18Oct00 		level_basez=(z&mask_value)-square_halfsize;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (Abs(land_x[i]-level_basex)>=update_size ||
//DeadCode JON 18Oct00 			Abs(land_z[i]-level_basez)>=update_size)
//DeadCode JON 18Oct00 			update_req[i]=retval=true;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		update_size+=update_size;
//DeadCode JON 18Oct00 		square_halfsize+=square_halfsize;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	return retval;
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetLandBaseDetail
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void SetLandBaseDetail(const SWord dl)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 //	assert(dl>=0&&dl<Max_TextureLevels&&"Bad landscape detail level");
//DeadCode JON 18Oct00 //DeadCode JON 18Oct00 	detail_min=dl;
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ScrollTexture
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
//DEADCODE PD 03/12/99 inline void ScrollTexture(const SLong lvl,const Box& src,const Box& dst)
//DEADCODE PD 03/12/99 {
//DEADCODE PD 03/12/99 	if (hardwareVersion)
//DEADCODE PD 03/12/99 	{
//DEADCODE PD 03/12/99 		//for cards that support async video-video blits I can get the
//DEADCODE PD 03/12/99 		//data shift started here and it should be complete by the time
//DEADCODE PD 03/12/99 		//the new data has been generated for the rest of the texture.
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 		win->DoBeginTextureScroll(lvl,(void*)&src,(void*)&dst);
//DEADCODE PD 03/12/99 	}
//DEADCODE PD 03/12/99 	else assert(false&&"code needed for software version here");
//DEADCODE PD 03/12/99 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		WaitForTextureScrollComplete
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
//DEADCODE PD 03/12/99 inline void WaitForTextureScrollComplete(const SLong lvl)
//DEADCODE PD 03/12/99 {
//DEADCODE PD 03/12/99 	//If using the hardware version then wait for any blits that
//DEADCODE PD 03/12/99 	//are still in progress to complete
//DEADCODE PD 03/12/99 
//DEADCODE PD 03/12/99 	if (hardwareVersion)
//DEADCODE PD 03/12/99 		win->DoWaitTextureScrollComplete(lvl);
//DEADCODE PD 03/12/99 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		PartialTextureUpload
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 17 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void PartialTextureUpload(const Box& src,const Box& dst,const SWord lvl)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 	if (hardwareVersion)
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 		win->DoPartialTextureUpload(lvl,(void*)&src,(void*)&dst);
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 	else
//DeadCode JON 18Oct00 //TempCode PD 03Dec99 		assert(false);
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SetTargetClip
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 17 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline void SetTargetClip(const Box& b) {targetBox=b;}

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		MakeDataGridIndex
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Mon 20 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 inline SLong MakeDataGridIndex(const SLong x,const SLong z)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 //	SLong dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//DeadCode JON 18Oct00 //						DataGridSizeMAX:DataGridSizeMIN;
//DeadCode JON 18Oct00 	SLong dataGridSize=DataGridSizeMIN;
//DeadCode JON 18Oct00  	SLong xi=(x-gridRecordBase_x)/Grid_Width;
//DeadCode JON 18Oct00 	if (xi<0 || xi>dataGridSize-1) return -1;
//DeadCode JON 18Oct00 	SLong zi=(z-gridRecordBase_z)/Grid_Width;
//DeadCode JON 18Oct00 	if (zi<0 || zi>dataGridSize-1) return -1;
//DeadCode JON 18Oct00 	return (zi*dataGridSize)+xi;
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		MakeDataGridIndex
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
inline SLong MakeDataGridIndex(const UWord offset)
{
	return (SLong)offset;
}

//DeadCode JON 25Aug00 void RenderShadow(ROWANSURFACEDESC*,ShapeDescPtr,SLong,SLong,SLong);
//DeadCode JON 25Aug00 void RenderShadowRotated(ROWANSURFACEDESC*,ShapeDescPtr,SLong,SLong,SLong,SLong);

//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderRotatedShad
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Tue 23 Feb 1999
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderRotatedShad(CLib3D* lib3d,SLong* x,SLong* z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	VData vertex[8];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<8;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].v=i;
//DeadCode JON 25Aug00 		vertex[i].x=x[i]<0?0:x[i]>255?255:x[i];
//DeadCode JON 25Aug00 		vertex[i].y=z[i]<0?0:z[i]>255?255:z[i];
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d,vertex[4],vertex[5],vertex[6],lvl);
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d,vertex[4],vertex[6],vertex[7],lvl);
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d,vertex[4],vertex[6],vertex[7],lvl);
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d,vertex[3],vertex[4],vertex[7],lvl);
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d,vertex[1],vertex[5],vertex[2],lvl);
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d,vertex[2],vertex[5],vertex[6],lvl);
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[4],vertex[5],vertex[6],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[4],vertex[6],vertex[7],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[4],vertex[6],vertex[7],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[3],vertex[4],vertex[7],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[1],vertex[5],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[2],vertex[5],vertex[6],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[4],vertex[5],vertex[6],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[4],vertex[6],vertex[7],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[4],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[3],vertex[4],vertex[7],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[1],vertex[5],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[2],vertex[5],vertex[6],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderShadow
//Author		Jon   
//Date			Fri 14 Apr 2000
//
//						
//------------------------------------------------------------------------------
inline void RenderShadow(CLib3D* lib3d, vector2d* corners, float& shapeDX, float& shapeDZ )
{

	for ( int i = 0; i<4; i++ )
	{
		if ( corners[i].x < 1 || corners[i].z < 1 ||
			 corners[i].x > 254 || corners[i].z > 254 )
		{
			NOP;
			return;
		}

	}
	
//DEADCODE JON 5/23/00 	R3DVERTEX* verts;
	Lib3DPoint* verts = lib3d->BeginPoly( NULL_MATERIAL, 6 );
//DEADCODE JON 5/23/00 	lib3d->BeginPoly( HMATERIAL( UByte(120) ), 6, verts );

	verts[0].setPosition( corners[3].x,			corners[3].z, 0.f );
	verts[1].setPosition( corners[0].x,			corners[0].z, 0.f );
	verts[2].setPosition( corners[1].x,			corners[1].z, 0.f );
	verts[3].setPosition( corners[1].x-shapeDX,	corners[1].z-shapeDZ, 0.f );
	verts[4].setPosition( corners[2].x-shapeDX,	corners[2].z-shapeDZ, 0.f );
	verts[5].setPosition( corners[3].x-shapeDX,	corners[3].z-shapeDZ, 0.f );

// Set colour and alpha for shadow...

	verts[0].setVertexCol(D3DCOLOR(shadColourNear));			//RJS 19Oct00
	verts[1].setVertexCol(D3DCOLOR(shadColourNear));
	verts[2].setVertexCol(D3DCOLOR(shadColourNear));
	verts[3].setVertexCol(D3DCOLOR(shadColourFar));
	verts[4].setVertexCol(D3DCOLOR(shadColourFar));
	verts[5].setVertexCol(D3DCOLOR(shadColourFar));

//DeadCode JON 25Aug00 	if ( shapeDX > 0.f )
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		if (shapeDZ < 0.f )
//DeadCode JON 25Aug00 		{
//DeadCode JON 25Aug00 			//SE
//DeadCode JON 25Aug00 			verts[0].setPosition( corners[1].x,			corners[1].z, 0.f );
//DeadCode JON 25Aug00 			verts[1].setPosition( corners[2].x,			corners[2].z, 0.f );
//DeadCode JON 25Aug00 			verts[2].setPosition( corners[3].x,			corners[3].z, 0.f );
//DeadCode JON 25Aug00 			verts[3].setPosition( corners[3].x-shapeDX,	corners[3].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 			verts[4].setPosition( corners[0].x-shapeDX,	corners[0].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 			verts[5].setPosition( corners[1].x-shapeDX,	corners[1].z-shapeDZ, 0.f );
		
//DEADCODE JON 5/23/00 			verts[0].bodyx.f = corners[1].x;
//DEADCODE JON 5/23/00 			verts[0].bodyy.f = corners[1].z;
//DEADCODE JON 5/23/00 		
//DEADCODE JON 5/23/00 			verts[1].bodyx.f = corners[2].x;
//DEADCODE JON 5/23/00 			verts[1].bodyy.f = corners[2].z;
//DEADCODE JON 5/23/00 
//DEADCODE JON 5/23/00 			verts[2].bodyx.f = corners[3].x;
//DEADCODE JON 5/23/00 			verts[2].bodyy.f = corners[3].z;
//DEADCODE JON 5/23/00 
//DEADCODE JON 5/23/00 			verts[3].bodyx.f = corners[3].x-shapeDX;
//DEADCODE JON 5/23/00 			verts[3].bodyy.f = corners[3].z-shapeDZ;
//DEADCODE JON 5/23/00 
//DEADCODE JON 5/23/00 			verts[4].bodyx.f = corners[0].x-shapeDX;
//DEADCODE JON 5/23/00 			verts[4].bodyy.f = corners[0].z-shapeDZ;
//DEADCODE JON 5/23/00 
//DEADCODE JON 5/23/00 			verts[5].bodyx.f = corners[1].x-shapeDX;
//DEADCODE JON 5/23/00 			verts[5].bodyy.f = corners[1].z-shapeDZ;
//DeadCode JON 25Aug00 		} else
//DeadCode JON 25Aug00 		{
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 			//NE
//DeadCode JON 25Aug00 			verts[0].setPosition( corners[0].x,			corners[0].z, 0.f );
//DeadCode JON 25Aug00 			verts[1].setPosition( corners[1].x,			corners[1].z, 0.f );
//DeadCode JON 25Aug00 			verts[2].setPosition( corners[2].x,			corners[2].z, 0.f );
//DeadCode JON 25Aug00 			verts[3].setPosition( corners[2].x-shapeDX,	corners[2].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 			verts[4].setPosition( corners[3].x-shapeDX,	corners[3].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 			verts[5].setPosition( corners[0].x-shapeDX,	corners[0].z-shapeDZ, 0.f);
//DeadCode JON 25Aug00 			
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[0].bodyx.f = corners[0].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[0].bodyy.f = corners[0].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 		
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[1].bodyx.f = corners[1].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[1].bodyy.f = corners[1].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[2].bodyx.f = corners[2].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[2].bodyy.f = corners[2].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[3].bodyx.f = corners[2].x-shapeDX;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[3].bodyy.f = corners[2].z-shapeDZ;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[4].bodyx.f = corners[3].x-shapeDX;/*+shapeDX;*/
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[4].bodyy.f = corners[3].z-shapeDZ;/*+shapeDZ;*/
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[5].bodyx.f = corners[0].x-shapeDX;/*+shapeDX;*/
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[5].bodyy.f = corners[0].z-shapeDZ;/*+shapeDZ;*/
//DeadCode JON 25Aug00 		}
//DeadCode JON 25Aug00 	} else
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		if (shapeDZ < 0.f )
//DeadCode JON 25Aug00 		{
//DeadCode JON 25Aug00 			//SW
//DeadCode JON 25Aug00 			verts[0].setPosition( corners[2].x,			corners[2].z, 0.f );
//DeadCode JON 25Aug00 			verts[1].setPosition( corners[3].x,			corners[3].z, 0.f );
//DeadCode JON 25Aug00 			verts[2].setPosition( corners[0].x,			corners[0].z, 0.f );
//DeadCode JON 25Aug00 			verts[3].setPosition( corners[0].x-shapeDX,	corners[0].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 			verts[4].setPosition( corners[1].x-shapeDX,	corners[1].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 			verts[5].setPosition( corners[2].x-shapeDX,	corners[2].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[0].bodyx.f = corners[2].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[0].bodyy.f = corners[2].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 		
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[1].bodyx.f = corners[3].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[1].bodyy.f = corners[3].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[2].bodyx.f = corners[0].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[2].bodyy.f = corners[0].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[3].bodyx.f = corners[0].x-shapeDX;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[3].bodyy.f = corners[0].z-shapeDZ;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[4].bodyx.f = corners[1].x-shapeDX;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[4].bodyy.f = corners[1].z-shapeDZ;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[5].bodyx.f = corners[2].x-shapeDX;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[5].bodyy.f = corners[2].z-shapeDZ;
//DeadCode JON 25Aug00 		} else
//DeadCode JON 25Aug00 		{
//DeadCode JON 25Aug00 			//NW
//DeadCode JON 25Aug00 			verts[0].setPosition( corners[3].x,			corners[3].z, 0.f );
//DeadCode JON 25Aug00 			verts[1].setPosition( corners[0].x,			corners[0].z, 0.f );
//DeadCode JON 25Aug00 			verts[2].setPosition( corners[1].x,			corners[1].z, 0.f );
//DeadCode JON 25Aug00 			verts[3].setPosition( corners[1].x-shapeDX,	corners[1].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 			verts[4].setPosition( corners[2].x-shapeDX,	corners[2].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 			verts[5].setPosition( corners[3].x-shapeDX,	corners[3].z-shapeDZ, 0.f );
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 			
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[0].bodyx.f = corners[3].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[0].bodyy.f = corners[3].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 		
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[1].bodyx.f = corners[0].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[1].bodyy.f = corners[0].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[2].bodyx.f = corners[1].x;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[2].bodyy.f = corners[1].z;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[3].bodyx.f = corners[1].x-shapeDX;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[3].bodyy.f = corners[1].z-shapeDZ;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[4].bodyx.f = corners[2].x-shapeDX;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[4].bodyy.f = corners[2].z-shapeDZ;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[5].bodyx.f = corners[3].x-shapeDX;
//DeadCode JON 25Aug00 //DEADCODE JON 5/23/00 			verts[5].bodyy.f = corners[3].z-shapeDZ;
//DeadCode JON 25Aug00 		}
//DeadCode JON 25Aug00 	}

	lib3d->EndPoly();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderObjectShadow
//Author		Jon   
//Date			Fri 14 Apr 2000
//
//						
//------------------------------------------------------------------------------
inline void RenderObjectShadow(CLib3D* lib3d,ShapeDescPtr sdp,SLong& x,SLong& z, SWord& hdg)
{
	if ( sdp->sy>>5 <1 )
		return;
	const float SHAPESCALE = 1.f/float( 1<<5 );
	float shapeRadx = sdp->sx*SHAPESCALE;
	float shapeHeight = sdp->sy*(SHAPESCALE*2);
	float shapeRadz = sdp->sz*SHAPESCALE;
	float shapeDX = shapeHeight*shadowDXf;
	float shapeDZ = shapeHeight*shadowDZf;						//RJS 05May00

	vector2d corners[8];

	if ( hdg == 0 )
	{
		corners[0].x = -shapeRadx;
		corners[0].z = +shapeRadz;
		corners[1].x = +shapeRadx;
		corners[1].z = +shapeRadz;
		corners[2].x = +shapeRadx;
		corners[2].z = -shapeRadz;
		corners[3].x = -shapeRadx;
		corners[3].z = -shapeRadz;

		
//DeadCode JON 25Aug00 		corners[0].x = x-shapeRadx;
//DeadCode JON 25Aug00 		corners[0].z = z+shapeRadz;
//DeadCode JON 25Aug00 		corners[1].x = x+shapeRadx;
//DeadCode JON 25Aug00 		corners[1].z = z+shapeRadz;
//DeadCode JON 25Aug00 		corners[2].x = x+shapeRadx;
//DeadCode JON 25Aug00 		corners[2].z = z-shapeRadz;
//DeadCode JON 25Aug00 		corners[3].x = x-shapeRadx;
//DeadCode JON 25Aug00 		corners[3].z = z-shapeRadz;

//DeadCode JON 25Aug00 		RenderShadow( lib3d, corners, shapeDX, shapeDZ );
	}
	else
	{
		double sinAng,cosAng;

		ANGLES hdgAng=(Angles)hdg;

		Math_Lib.high_sin_cos(hdgAng,sinAng,cosAng);

		float rotMat[4];
		rotMat[0]=rotMat[3]=cosAng;
		rotMat[1]=sinAng;
		rotMat[2]=-rotMat[1];
		
		corners[0].x = (-shapeRadx*rotMat[0])+(shapeRadz*rotMat[1]);
		corners[0].z = (-shapeRadx*rotMat[2])+(shapeRadz*rotMat[3]);
		corners[1].x = (shapeRadx*rotMat[0])+(shapeRadz*rotMat[1]);
		corners[1].z = (shapeRadx*rotMat[2])+(shapeRadz*rotMat[3]);
		corners[2].x = (shapeRadx*rotMat[0])+(-shapeRadz*rotMat[1]);
		corners[2].z = (shapeRadx*rotMat[2])+(-shapeRadz*rotMat[3]);
		corners[3].x = (-shapeRadx*rotMat[0])+(-shapeRadz*rotMat[1]);
		corners[3].z = (-shapeRadx*rotMat[2])+(-shapeRadz*rotMat[3]);


		
//DeadCode JON 25Aug00 		vector2d tmp[4];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 		tmp[0].x = (-shapeRadx*rotMat[0])+(shapeRadz*rotMat[1]);
//DeadCode JON 25Aug00 		tmp[0].z = (-shapeRadx*rotMat[2])+(shapeRadz*rotMat[3]);
//DeadCode JON 25Aug00 		tmp[1].x = (shapeRadx*rotMat[0])+(shapeRadz*rotMat[1]);
//DeadCode JON 25Aug00 		tmp[1].z = (shapeRadx*rotMat[2])+(shapeRadz*rotMat[3]);
//DeadCode JON 25Aug00 		tmp[2].x = (shapeRadx*rotMat[0])+(-shapeRadz*rotMat[1]);
//DeadCode JON 25Aug00 		tmp[2].z = (shapeRadx*rotMat[2])+(-shapeRadz*rotMat[3]);
//DeadCode JON 25Aug00 		tmp[3].x = (-shapeRadx*rotMat[0])+(-shapeRadz*rotMat[1]);
//DeadCode JON 25Aug00 		tmp[3].z = (-shapeRadx*rotMat[2])+(-shapeRadz*rotMat[3]);
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 		vector2d corners[4];
//DeadCode JON 25Aug00 		for ( int i=0; i<4; i++ )
//DeadCode JON 25Aug00 		{
//DeadCode JON 25Aug00 			if ( tmp[i].x < 0.f )
//DeadCode JON 25Aug00 			{
//DeadCode JON 25Aug00 				if ( tmp[i].z < 0.f )
//DeadCode JON 25Aug00 				{	// x-ve z-ve
//DeadCode JON 25Aug00 					corners[3].x=tmp[i].x+x;
//DeadCode JON 25Aug00 					corners[3].z=tmp[i].z+z;
//DeadCode JON 25Aug00 				} else
//DeadCode JON 25Aug00 				{	// x-ve z+ve
//DeadCode JON 25Aug00 					corners[0].x=tmp[i].x+x;
//DeadCode JON 25Aug00 					corners[0].z=tmp[i].z+z;
//DeadCode JON 25Aug00 				}
//DeadCode JON 25Aug00 			} else
//DeadCode JON 25Aug00 			{
//DeadCode JON 25Aug00 				if ( tmp[i].z < 0.f )
//DeadCode JON 25Aug00 				{	// x+ve z-ve
//DeadCode JON 25Aug00 					corners[2].x=tmp[i].x+x;
//DeadCode JON 25Aug00 					corners[2].z=tmp[i].z+z;
//DeadCode JON 25Aug00 				} else
//DeadCode JON 25Aug00 				{	// x+ve z+ve
//DeadCode JON 25Aug00 					corners[1].x=tmp[i].x+x;
//DeadCode JON 25Aug00 					corners[1].z=tmp[i].z+z;
//DeadCode JON 25Aug00 				}
//DeadCode JON 25Aug00 			}	
//DeadCode JON 25Aug00 		}
//DeadCode JON 25Aug00 		RenderShadow( lib3d, corners, shapeDX, shapeDZ );
	}

	// find biggest dot product ( closest point to direction of shadow)
	float max = 0.0;
	int index, maxI;
	for ( index = 0; index < 4; index++ )
	{
		float cur = corners[index].x*shapeDX + corners[index].z*shapeDZ;
		if ( cur > max )
		{
			max = cur;
			maxI = index;
		}
		corners[index].x+=x;
		corners[index].z+=z;
	}
	memcpy( corners+4, corners, sizeof( corners[0] ) *4 );
	RenderShadow( lib3d, corners+maxI, shapeDX, shapeDZ );
}

//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadOctant0
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Mon 26 Oct 1998
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderShadOctant0(CLib3D* lib3d,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	//shadow is North facing 4 points & 2 polys required
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	VData vertex[4];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shape2Pix=5;	//lvl+5;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 		return;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[0].v=0;
//DeadCode JON 25Aug00 	vertex[0].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[0].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[1].v=1;
//DeadCode JON 25Aug00 	vertex[1].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[1].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[2].v=2;
//DeadCode JON 25Aug00 	vertex[2].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[2].y=z+sdz-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[3].v=3;
//DeadCode JON 25Aug00 	vertex[3].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[3].y=z+sdz-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<4;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
//DeadCode JON 25Aug00 		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[1],vertex[2],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[2],vertex[3],lvl );
//DeadCode JON 25Aug00 	//DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadOctant1
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Mon 26 Oct 1998
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderShadOctant1(CLib3D* lib3d,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	//shadow is NE facing 6 points & 4 polys required
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	VData vertex[6];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shape2Pix=5;	//lvl+5;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 		return;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[0].v=0;
//DeadCode JON 25Aug00 	vertex[0].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[0].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[1].v=1;
//DeadCode JON 25Aug00 	vertex[1].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[1].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[2].v=2;
//DeadCode JON 25Aug00 	vertex[2].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[2].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[3].v=3;
//DeadCode JON 25Aug00 	vertex[3].x=x-shapeSx+sdx;
//DeadCode JON 25Aug00 	vertex[3].y=z+shapeSz-sdz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[4].v=4;
//DeadCode JON 25Aug00 	vertex[4].x=x+shapeSx+sdx;
//DeadCode JON 25Aug00 	vertex[4].y=z+shapeSz-sdz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[5].v=5;
//DeadCode JON 25Aug00 	vertex[5].x=x+shapeSx+sdx;
//DeadCode JON 25Aug00 	vertex[5].y=z-shapeSz-sdz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<6;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
//DeadCode JON 25Aug00 		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[1],vertex[2],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[2],vertex[5],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[2],vertex[3],vertex[5],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[3],vertex[4],vertex[5],lvl );
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[2],vertex[3],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[3],vertex[4],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[2],vertex[3],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[3],vertex[4],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadOctant2
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Mon 26 Oct 1998
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderShadOctant2(CLib3D* lib3d,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	//shadow is E facing 4 points & 2 polys required
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	VData vertex[4];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shape2Pix=5;	//lvl+5;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 		return;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[0].v=0;
//DeadCode JON 25Aug00 	vertex[0].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[0].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[1].v=1;
//DeadCode JON 25Aug00 	vertex[1].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[1].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[2].v=2;
//DeadCode JON 25Aug00 	vertex[2].x=x+shapeSx+sdx;
//DeadCode JON 25Aug00 	vertex[2].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[3].v=3;
//DeadCode JON 25Aug00 	vertex[3].x=x+shapeSx+sdx;
//DeadCode JON 25Aug00 	vertex[3].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<4;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
//DeadCode JON 25Aug00 		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[1],vertex[2],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[2],vertex[3],lvl );
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadOctant3
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Mon 26 Oct 1998
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderShadOctant3(CLib3D* lib3d,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	//shadow is SE facing 6 points & 4 polys required
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	VData vertex[6];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shape2Pix=5;	//lvl+5;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 		return;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[0].v=0;
//DeadCode JON 25Aug00 	vertex[0].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[0].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[1].v=1;
//DeadCode JON 25Aug00 	vertex[1].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[1].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[2].v=2;
//DeadCode JON 25Aug00 	vertex[2].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[2].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[3].v=3;
//DeadCode JON 25Aug00 	vertex[3].x=x+sdx+shapeSx;
//DeadCode JON 25Aug00 	vertex[3].y=z-sdz-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[4].v=4;
//DeadCode JON 25Aug00 	vertex[4].x=x+sdx+shapeSx;
//DeadCode JON 25Aug00 	vertex[4].y=z-sdz+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[5].v=5;
//DeadCode JON 25Aug00 	vertex[5].x=x+sdx-shapeSx;
//DeadCode JON 25Aug00 	vertex[5].y=z-sdz+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<6;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
//DeadCode JON 25Aug00 		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[1],vertex[2],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[2],vertex[3],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[3],vertex[5],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[3],vertex[4],vertex[5],lvl );
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[3],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[3],vertex[4],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[3],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[3],vertex[4],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadOctant4
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Mon 26 Oct 1998
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderShadOctant4(CLib3D* lib3d,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	//shadow is S facing 4 points & 2 polys required
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	VData vertex[4];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shape2Pix=5;	//lvl+5;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 		return;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[0].v=0;
//DeadCode JON 25Aug00 	vertex[0].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[0].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[1].v=1;
//DeadCode JON 25Aug00 	vertex[1].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[1].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[2].v=2;
//DeadCode JON 25Aug00 	vertex[2].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[2].y=z+shadowDZ+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[3].v=3;
//DeadCode JON 25Aug00 	vertex[3].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[3].y=z+shadowDZ+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<4;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
//DeadCode JON 25Aug00 		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[1],vertex[2],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[2],vertex[3],lvl );
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadOctant5
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Mon 26 Oct 1998
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderShadOctant5(CLib3D* lib3d,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	//shadow is SW facing 6 points & 4 polys required
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	VData vertex[6];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shape2Pix=5;	//lvl+5;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 		return;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[0].v=0;
//DeadCode JON 25Aug00 	vertex[0].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[0].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[1].v=1;
//DeadCode JON 25Aug00 	vertex[1].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[1].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[2].v=2;
//DeadCode JON 25Aug00 	vertex[2].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[2].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[3].v=3;
//DeadCode JON 25Aug00 	vertex[3].x=x+shadowDX+shapeSx;
//DeadCode JON 25Aug00 	vertex[3].y=z+shadowDZ+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[4].v=4;
//DeadCode JON 25Aug00 	vertex[4].x=x+shadowDX-shapeSx;
//DeadCode JON 25Aug00 	vertex[4].y=z+shadowDZ+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[5].v=5;
//DeadCode JON 25Aug00 	vertex[5].x=x+shadowDX-shapeSx;
//DeadCode JON 25Aug00 	vertex[5].y=z+shadowDZ-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<6;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
//DeadCode JON 25Aug00 		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[1],vertex[2],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[2],vertex[3],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[3],vertex[5],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[3],vertex[4],vertex[5],lvl );
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[3],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[3],vertex[4],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[3],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[3],vertex[4],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadOctant6
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Mon 26 Oct 1998
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderShadOctant6(CLib3D* lib3d,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	//shadow is W facing 4 points & 2 polys required
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	VData vertex[4];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shape2Pix=5;	//lvl+5;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 		return;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[0].v=0;
//DeadCode JON 25Aug00 	vertex[0].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[0].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[1].v=1;
//DeadCode JON 25Aug00 	vertex[1].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[1].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[2].v=2;
//DeadCode JON 25Aug00 	vertex[2].x=x+shadowDX-shapeSx;
//DeadCode JON 25Aug00 	vertex[2].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[3].v=3;
//DeadCode JON 25Aug00 	vertex[3].x=x+shadowDX-shapeSx;
//DeadCode JON 25Aug00 	vertex[3].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<4;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
//DeadCode JON 25Aug00 		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[1],vertex[2],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[2],vertex[3],lvl );
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[3],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadOctant7
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Mon 26 Oct 1998
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 inline void RenderShadOctant7(CLib3D* lib3d,ShapeDescPtr sdp,SLong x,SLong z,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 	//shadow is NW facing 6 points & 4 polys required
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	VData vertex[6];
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shape2Pix=5;	//lvl+5;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 		return;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[0].v=0;
//DeadCode JON 25Aug00 	vertex[0].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[0].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[1].v=1;
//DeadCode JON 25Aug00 	vertex[1].x=x-shapeSx;
//DeadCode JON 25Aug00 	vertex[1].y=z+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[2].v=2;
//DeadCode JON 25Aug00 	vertex[2].x=x+shadowDX-shapeSx;
//DeadCode JON 25Aug00 	vertex[2].y=z+shadowDZ+shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[3].v=3;
//DeadCode JON 25Aug00 	vertex[3].x=x+shadowDX-shapeSx;
//DeadCode JON 25Aug00 	vertex[3].y=z+shadowDZ-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[4].v=4;
//DeadCode JON 25Aug00 	vertex[4].x=x+shadowDX+shapeSx;
//DeadCode JON 25Aug00 	vertex[4].y=z+shadowDZ-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	vertex[5].v=5;
//DeadCode JON 25Aug00 	vertex[5].x=x+shapeSx;
//DeadCode JON 25Aug00 	vertex[5].y=z-shapeSz;
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	for (SLong i=0;i<6;i++)
//DeadCode JON 25Aug00 	{
//DeadCode JON 25Aug00 		vertex[i].x=(vertex[i].x<0)?0:(vertex[i].x>255)?255:vertex[i].x;
//DeadCode JON 25Aug00 		vertex[i].y=(vertex[i].y<0)?0:(vertex[i].y>255)?255:vertex[i].y;
//DeadCode JON 25Aug00 	}
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[1],vertex[2],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[0],vertex[2],vertex[5],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[2],vertex[3],vertex[4],lvl );
//DeadCode JON 25Aug00 	DrawShadowTriangle( lib3d, vertex[2],vertex[4],vertex[5],lvl );
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	if (ispalettised)
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[0],vertex[2],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[2],vertex[3],vertex[4],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle8(prsd,vertex[2],vertex[4],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	else
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[1],vertex[2],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[0],vertex[2],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[2],vertex[3],vertex[4],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 		DDShadowTriangle16(prsd,vertex[2],vertex[4],vertex[5],lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/12/00 	}
//DeadCode JON 25Aug00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 	
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	ClearRecords(UByte(6));
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	if (shadowDX==0)
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		if (shadowDZ>0)					RenderShadOctant0(lib3d,sdp,x,z,lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		else if (shadowDZ<0)			RenderShadOctant4(lib3d,sdp,x,z,lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	else if (shadowDZ==0)
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		if (shadowDX>0)					RenderShadOctant2(lib3d,sdp,x,z,lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		else if (shadowDX<0)			RenderShadOctant6(lib3d,sdp,x,z,lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	else if (shadowDX>0 && shadowDZ>0)	RenderShadOctant1(lib3d,sdp,x,z,lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	else if (shadowDX>0 && shadowDZ<0)	RenderShadOctant3(lib3d,sdp,x,z,lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	else if (shadowDX<0 && shadowDZ<0)	RenderShadOctant5(lib3d,sdp,x,z,lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	else if (shadowDX<0 && shadowDZ>0)	RenderShadOctant7(lib3d,sdp,x,z,lvl);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 }
//DeadCode JON 25Aug00 
//DeadCode JON 25Aug00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 25Aug00 //Procedure		RenderShadowRotated
//DeadCode JON 25Aug00 //Author		Paul.   
//DeadCode JON 25Aug00 //Date			Tue 23 Feb 1999
//DeadCode JON 25Aug00 //------------------------------------------------------------------------------
//DeadCode JON 25Aug00 void RenderShadowRotated(	CLib3D* lib3d,ShapeDescPtr sdp,
//DeadCode JON 25Aug00 							SLong ix,SLong iz,
//DeadCode JON 25Aug00 							SLong hdg,SLong lvl)
//DeadCode JON 25Aug00 {
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong shape2Pix=5;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	if ((sdp->Size>>shape2Pix)==0)
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		return;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong shapeSx=sdp->sx>>shape2Pix;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong shapeSy=sdp->sy>>shape2Pix;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong shapeSz=sdp->sz>>shape2Pix;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	if (shapeSy==0) return;	//shapeSy=1;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	if (shapeSx==0) return; //shapeSx=1;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	if (shapeSz==0) return; //shapeSz=1;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	//scale shadow DX,DZ based on the shapes height
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong sdz=(shadowDZ*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong sdx=(shadowDX*shapeSy)/ANGLES_FRACT;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00  	SWord sinAng,cosAng;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	ANGLES hdgAng=(Angles)hdg;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	Math_Lib.high_sin_cos(hdgAng,sinAng,cosAng);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong m[4];
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong x[8];
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	SLong z[8];
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	//generate 2D rotation matrix
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	m[0]=m[3]=SLong(cosAng);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	m[1]=SLong(sinAng);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	m[2]=-SLong(sinAng);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	x[0]=x[1]=shapeSx;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	x[2]=x[3]=-shapeSx;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	z[0]=z[3]=shapeSz;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	z[1]=z[2]=-shapeSz;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	for (int i=0;i<4;i++)
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	{
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	 	SLong tx=ix+((m[0]*x[i])/ANGLES_FRACT+(m[1]*z[i])/ANGLES_FRACT);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	 	SLong tz=iz+((m[2]*x[i])/ANGLES_FRACT+(m[3]*z[i])/ANGLES_FRACT);
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		x[i]=tx;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		x[i+4]=tx+sdx;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		z[i]=tz;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 		z[i+4]=tz-sdz;
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	}
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	ClearRecords(UByte(8));
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 
//DeadCode JON 25Aug00 //DEADCODE JON 4/14/00 	RenderRotatedShad(lib3d,x,z,lvl);
//DeadCode JON 25Aug00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PatchColorData
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
//DEADCODE JON 4/14/00 void PatchColorData(const SLong x,const SLong z,const SLong lvl,const Box& b)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 	//set target texture clipping values to match 'b' and
//DEADCODE JON 4/14/00 	//then decompress color data to the area of the target
//DEADCODE JON 4/14/00 	//texture that needs an update
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	SLong xoff,yoff,ixoff;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	SetTargetClip(b);
//DEADCODE JON 4/14/00 	SetDestTexturePtr(lvl);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	const SLong gridSx=x&Grid_Mask;
//DEADCODE JON 4/14/00 	const SLong gridSz=z&Grid_Mask;
//DEADCODE JON 4/14/00 	const SLong gridEx=(x+(Grid_Width<<lvl))&Grid_Mask;
//DEADCODE JON 4/14/00 	const SLong gridEz=(z+(Grid_Width<<lvl))&Grid_Mask;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	//Find out how many tiles are needed to cover this area
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	const SLong block_width=Grid_Width<<lvl;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	xoff=(gridSx-x)>>(9+lvl);
//DEADCODE JON 4/14/00 	yoff=(gridSz-z)>>(9+lvl);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	SWord duv;
//DEADCODE JON 4/14/00 	SWord resetu;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	if (lvl<3) 
//DEADCODE JON 4/14/00 	{
//DEADCODE JON 4/14/00 		resetu=duv=uoffset=voffset=0;
//DEADCODE JON 4/14/00 	}
//DEADCODE JON 4/14/00 	else 
//DEADCODE JON 4/14/00 	{
//DEADCODE JON 4/14/00 		resetu=uoffset=((gridSx>>17)&7)<<5;
//DEADCODE JON 4/14/00 		voffset=((gridSz>>17)&7)<<5;
//DEADCODE JON 4/14/00 		duv=32;
//DEADCODE JON 4/14/00 	}
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	for (int i=gridSz;i<=gridEz;i+=Grid_Width)
//DEADCODE JON 4/14/00 	{
//DEADCODE JON 4/14/00 		ixoff=xoff;
//DEADCODE JON 4/14/00 		uoffset=resetu;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 		for (int j=gridSx;j<=gridEx;j+=Grid_Width)
//DEADCODE JON 4/14/00 		{
//DEADCODE JON 4/14/00 			//make an index into the data record table
//DEADCODE JON 4/14/00 			//for the coordinate (j,i)
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			SLong dgi=MakeDataGridIndex(j,i);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			if (dgi!=-1 && yoff<256 && ixoff<256)
//DEADCODE JON 4/14/00   			{
//DEADCODE JON 4/14/00 				UByte* pdata=Three_Dee.pMigLand->MakeIData(gridRecords[dgi],lvl>>1);
//DEADCODE JON 4/14/00 	  
//DEADCODE JON 4/14/00 				Render2Map(pdata,ixoff,yoff,lvl);
//DEADCODE JON 4/14/00 		  	}
//DEADCODE JON 4/14/00 		  	ixoff+=physWidth;
//DEADCODE JON 4/14/00 			uoffset+=duv;
//DEADCODE JON 4/14/00 		}
//DEADCODE JON 4/14/00 		yoff+=physWidth;
//DEADCODE JON 4/14/00 		voffset+=duv;
//DEADCODE JON 4/14/00 	}
//DEADCODE JON 4/14/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateColorData
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
//DEADCODE JON 4/14/00 void UpdateColorData(const SLong x,const SLong z,const SLong lvl)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 	Box src_rect,dst_rect;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	//first find out how much of the current set of data can be
//DEADCODE JON 4/14/00 	//retained
//DEADCODE JON 4/14/00 	
//DEADCODE JON 4/14/00 	const SLong nx=x;
//DEADCODE JON 4/14/00 	const SLong nz=z;
//DEADCODE JON 4/14/00 	const SLong TextureFin=TextureWidth;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	//if there is no change or the change is
//DEADCODE JON 4/14/00 	//greater than the area covered by this tile
//DEADCODE JON 4/14/00 	//then update the whole area
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	//if we get here then the full tile needs rebuilding
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	src_rect.left=src_rect.top=0;
//DEADCODE JON 4/14/00 	src_rect.right=src_rect.bottom=TextureFin;
//DEADCODE JON 4/14/00 	dst_rect=src_rect;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	PatchColorData(nx,nz,lvl,src_rect);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	//upload the full tile
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	PartialTextureUpload(src_rect,dst_rect,lvl);
//DEADCODE JON 4/14/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UpdateGridRecords
//Author		Paul.   
//Date			Mon 20 Jul 1998
//------------------------------------------------------------------------------
inline void UpdateGridRecords(const SLong x,const SLong z)
{
	DataRecord* pdr=gridRecords;
//DeadCode JON 18Oct00 	ShadowStruc* psr=shadowRecords;
	SLong ox,oz,ix;
	SLong dataGridSize;

	dataGridSize=DataGridSizeMIN;

	ox=(x&Grid_Mask)-((dataGridSize>>1)*Grid_Width);
	oz=(z&Grid_Mask)-((dataGridSize>>1)*Grid_Width);

	SLong dx=Abs(gridRecordBase_x-ox);
	SLong dz=Abs(gridRecordBase_z-oz);

	if (dx!=0 || dz!=0)
	{
		gridRecordBase_x=ox;
		gridRecordBase_z=oz;

		for (int j=0;j<dataGridSize;j++)
		{
			ix=ox;
			for (int k=0;k<dataGridSize;k++)
			{
				*pdr++=Three_Dee.pMigLand->GetData(ix,oz);
//DeadCode JON 18Oct00 #pragma warnmsg ( "**** REMOVE THESE UNNEEDED THINGS - JON *****" )
//DeadCode JON 18Oct00 				psr->world_x=ix;
//DeadCode JON 18Oct00 				psr->world_z=oz;
//DeadCode JON 18Oct00 				psr++;
				ix+=Grid_Width;
			}
			oz+=Grid_Width;
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitGridRecords
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 inline ULong whichBlock(SLong x,SLong z)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	ULong retval;
//DeadCode JON 18Oct00 	x>>=17;
//DeadCode JON 18Oct00 	z>>=17;
//DeadCode JON 18Oct00 	retval=(z&0x7)+1;
//DeadCode JON 18Oct00 	retval+=((x&0x7)+1)<<4;
//DeadCode JON 18Oct00 	x>>=3;
//DeadCode JON 18Oct00 	z>>=3;
//DeadCode JON 18Oct00 	retval+=((z&0x7)+1)<<8;
//DeadCode JON 18Oct00 	retval+=((x&0x7)+1)<<12;
//DeadCode JON 18Oct00 	x>>=3;
//DeadCode JON 18Oct00 	z>>=3;
//DeadCode JON 18Oct00 	retval+=((z&0x7)+1)<<16;
//DeadCode JON 18Oct00 	retval+=((x&0x7)+1)<<20;
//DeadCode JON 18Oct00 	return retval;
//DeadCode JON 18Oct00 }

void InitGridRecords(const SLong x,const SLong z)
{
	SLong ox,oz,ix;
	SLong dataGridSize;
	DataRecord* pdr;
//DeadCode JON 18Oct00 	ShadowStruc* psr=shadowRecords;

//	dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//					DataGridSizeMAX:DataGridSizeMIN;
	dataGridSize=DataGridSizeMIN;

	pdr=gridRecords;
	ox=(x&Grid_Mask)-((dataGridSize>>1)*Grid_Width);
	oz=(z&Grid_Mask)-((dataGridSize>>1)*Grid_Width);

	gridRecordBase_x=ox;
	gridRecordBase_z=oz;

	for (int j=0;j<dataGridSize;j++)
	{
		ix=ox;
		for (int k=0;k<dataGridSize;k++)
		{
//DeadCode JON 18Oct00 			blockNumber=whichBlock(ix,oz);
			*pdr++=Three_Dee.pMigLand->GetData(ix,oz);
//DeadCode JON 18Oct00 			psr->world_x=ix;
//DeadCode JON 18Oct00 			psr->world_z=oz;
//DeadCode JON 18Oct00 			psr++;
			ix+=Grid_Width;
		}
		oz+=Grid_Width;
	} 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ProcessLandUpdateRequests
//Author		Paul.   
//Date			Fri 17 Jul 1998
//------------------------------------------------------------------------------
//DEADCODE JON 4/14/00 void ProcessLandUpdateRequests(const SLong x,const SLong z,bool firstTime=false)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 	SLong	update_size;
//DEADCODE JON 4/14/00 	SLong	square_halfsize;
//DEADCODE JON 4/14/00 	ULong	update_mask;
//DEADCODE JON 4/14/00 	SLong	maxTextureLevels;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 //	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//DEADCODE JON 4/14/00 //					Max_TextureLevelsMAX:Max_TextureLevelsMIN;
//DEADCODE JON 4/14/00 	maxTextureLevels=Max_TextureLevelsMIN;
//DEADCODE JON 4/14/00 #pragma message ( __HERE__ "horizon range look here - jon" )
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	update_size=(Grid_Width>>3)<<detail_min;
//DEADCODE JON 4/14/00 	square_halfsize=(Grid_Width>>1)<<detail_min;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	for (int i=detail_min;i<maxTextureLevels;i++)
//DEADCODE JON 4/14/00 	{
//DEADCODE JON 4/14/00 		if (update_req[i])
//DEADCODE JON 4/14/00 		{
//DEADCODE JON 4/14/00 			update_req[i]=false;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			update_mask=~ULong(update_size-1);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			land_x[i]=(x&update_mask)-square_halfsize;
//DEADCODE JON 4/14/00 			land_z[i]=(z&update_mask)-square_halfsize;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			UpdateColorData(land_x[i],land_z[i],i);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 			//allow for complete update on first frame of 3D
//DEADCODE JON 4/14/00 			if (!firstTime)
//DEADCODE JON 4/14/00 				return;
//DEADCODE JON 4/14/00 		}
//DEADCODE JON 4/14/00 		square_halfsize+=square_halfsize;
//DEADCODE JON 4/14/00 		update_size+=update_size;
//DEADCODE JON 4/14/00 	}
//DEADCODE JON 4/14/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBlock
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
inline DataRecord GetBlock(const SLong x,const SLong z)
{
//	SLong dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?DataGridSizeMAX:DataGridSizeMIN;
	SLong dataGridSize=DataGridSizeMIN;
	SLong ix=(x&Grid_Mask)-gridRecordBase_x;
	SLong iz=(z&Grid_Mask)-gridRecordBase_z;
	ix/=Grid_Width;
	iz/=Grid_Width;
	return gridRecords[(iz*dataGridSize)+ix];
}

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		GetSquares
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 22 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void GetSquares(Rect* squares)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong square_size=131072;
//DeadCode JON 18Oct00 	SLong maxTextureLevels;
//DeadCode JON 18Oct00 //	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?Max_TextureLevelsMAX:Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 	maxTextureLevels=Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 	for (int i=0;i<maxTextureLevels;i++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		Rect& r=squares[i];
//DeadCode JON 18Oct00 		r.t=land_z[i];
//DeadCode JON 18Oct00 		r.l=land_x[i];
//DeadCode JON 18Oct00 		r.b=r.t+square_size;
//DeadCode JON 18Oct00 		r.r=r.l+square_size;
//DeadCode JON 18Oct00 		square_size+=square_size;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		MakeClipRects
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Mon 27 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void MakeClipRects()
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 //	Rect squares[Max_TextureLevels];
//DeadCode JON 18Oct00 //	SLong maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//DeadCode JON 18Oct00 //							Max_TextureLevelsMAX:Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 	SLong maxTextureLevels=Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Rect* squares=new Rect[maxTextureLevels];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Rect* pcr=clipRects;
//DeadCode JON 18Oct00 	bool splitlr=true;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	GetSquares(squares);
//DeadCode JON 18Oct00 	clipRectCnt=0;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (int i=maxTextureLevels-1;i>0;i--)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		int j=i-1;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		Rect& outer=squares[i];
//DeadCode JON 18Oct00 		Rect& inner=squares[j];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		*pcr++=outer;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (splitlr)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			pcr->l=outer.l;
//DeadCode JON 18Oct00 			pcr->r=inner.l;
//DeadCode JON 18Oct00 			pcr->t=outer.t;
//DeadCode JON 18Oct00 			pcr->b=outer.b;
//DeadCode JON 18Oct00 			pcr++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			pcr->l=inner.l;
//DeadCode JON 18Oct00 			pcr->r=inner.r;
//DeadCode JON 18Oct00 			pcr->t=outer.t;
//DeadCode JON 18Oct00 			pcr->b=inner.t;
//DeadCode JON 18Oct00 			pcr++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			pcr->l=inner.r;
//DeadCode JON 18Oct00 			pcr->r=outer.r;
//DeadCode JON 18Oct00 			pcr->t=outer.t;
//DeadCode JON 18Oct00 			pcr->b=outer.b;
//DeadCode JON 18Oct00 			pcr++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			pcr->l=inner.l;
//DeadCode JON 18Oct00 			pcr->r=inner.r;
//DeadCode JON 18Oct00 			pcr->t=inner.b;
//DeadCode JON 18Oct00 			pcr->b=outer.b;
//DeadCode JON 18Oct00 			pcr++;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 		else
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			pcr->l=outer.l;
//DeadCode JON 18Oct00 			pcr->r=inner.l;
//DeadCode JON 18Oct00 			pcr->t=inner.t;
//DeadCode JON 18Oct00 			pcr->b=inner.b;
//DeadCode JON 18Oct00 			pcr++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			pcr->l=outer.l;
//DeadCode JON 18Oct00 			pcr->r=outer.r;
//DeadCode JON 18Oct00 			pcr->t=outer.t;
//DeadCode JON 18Oct00 			pcr->b=inner.t;
//DeadCode JON 18Oct00 			pcr++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			pcr->l=inner.r;
//DeadCode JON 18Oct00 			pcr->r=outer.r;
//DeadCode JON 18Oct00 			pcr->t=inner.t;
//DeadCode JON 18Oct00 			pcr->b=inner.b;
//DeadCode JON 18Oct00 			pcr++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			pcr->l=outer.l;
//DeadCode JON 18Oct00 			pcr->r=outer.r;
//DeadCode JON 18Oct00 			pcr->t=inner.b;
//DeadCode JON 18Oct00 			pcr->b=outer.b;
//DeadCode JON 18Oct00 			pcr++;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 		splitlr=splitlr?false:true;
//DeadCode JON 18Oct00 		clipRectCnt+=5;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	*pcr++=squares[0];
//DeadCode JON 18Oct00 	clipRectCnt++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	delete[]squares;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		GetClipRegion
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Mon 27 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void GetClipRegion(const UByte index,Rect& clip)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	clip=clipRects[index];
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 const SLong _tl=0;
//DeadCode JON 18Oct00 const SLong _tr=1;
//DeadCode JON 18Oct00 const SLong _bl=2;
//DeadCode JON 18Oct00 const SLong _br=3;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 SquareClips* wholeAreaClips;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		clip_recurse
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 29 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void clip_recurse(SLong* xvals,SLong* zvals,SLong level,SquareClips* psqc)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong maxTextureLevels;
//DeadCode JON 18Oct00 	SLong levelBase=5*level;
//DeadCode JON 18Oct00 	SLong levelNext=levelBase+5;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	UWord clipFlags[4];
//DeadCode JON 18Oct00 	UWord edgeFlags[4];
//DeadCode JON 18Oct00 	UWord andedFlags;
//DeadCode JON 18Oct00 	UWord oredFlags;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //	maxTextureLevels=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//DeadCode JON 18Oct00 //						Max_TextureLevelsMAX:Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 	maxTextureLevels=Max_TextureLevelsMIN;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Rect& out=clipRects[levelBase];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//handle very last area check as a special case
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (level==maxTextureLevels-1)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		//if any other clipping has already been added then
//DeadCode JON 18Oct00 		//all we need to do is add this clip area to the
//DeadCode JON 18Oct00 		//current list and return
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (psqc->count!=0)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 	  		ClipInfo& ci=psqc->clipInfo[psqc->count++];
//DeadCode JON 18Oct00 			ci.level=maxTextureLevels-1-level;
//DeadCode JON 18Oct00 			ci.clipRecIndex=levelBase;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 		return;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Rect& in=clipRects[levelNext];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//generate clip flags based on the inner tile
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	andedFlags=_offleft+_offright+_offtop+_offbottom;
//DeadCode JON 18Oct00 	oredFlags=0;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (int t=0;t<4;t++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		//Make sure that points on an edge have no influence
//DeadCode JON 18Oct00 		//on inside/outside tests
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		ClipResult(xvals[t],zvals[t],in,clipFlags[t],edgeFlags[t]);
//DeadCode JON 18Oct00 		andedFlags&=clipFlags[t]|edgeFlags[t];
//DeadCode JON 18Oct00 		oredFlags|=clipFlags[t];
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//oredFlags==0 if all of the points in the 
//DeadCode JON 18Oct00 	//	tile currently being considered are inside the
//DeadCode JON 18Oct00 	//	inner area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (oredFlags==0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		level++;
//DeadCode JON 18Oct00 		clip_recurse(xvals,zvals,level,psqc);
//DeadCode JON 18Oct00 		return;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//andedFlags!=0 if all of the points in the
//DeadCode JON 18Oct00 	//	tile currently being considered are outside the
//DeadCode JON 18Oct00 	//	inner area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (andedFlags!=0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		//if psqc->count==0 then no clipping has been
//DeadCode JON 18Oct00 		//set for this tile yet. This means that it is
//DeadCode JON 18Oct00 		//safe to say that no clipping is needed at all
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (psqc->count==0)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			//just fill in the correct texture level index
//DeadCode JON 18Oct00 			//and return
//DeadCode JON 18Oct00 			psqc->clipInfo[0].level=maxTextureLevels-1-level;
//DeadCode JON 18Oct00 			return;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 		else
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			//some clipping data has already been generated for 
//DeadCode JON 18Oct00 			//this tile so I need to add some more for this
//DeadCode JON 18Oct00 			//level
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			//first stage is to check whether this tile is contained
//DeadCode JON 18Oct00 			//entirely within one of the 4 cliping regions surrounding
//DeadCode JON 18Oct00 			//the central area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			for (int s=1;s<5;s++)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 			 	Rect& cr=clipRects[levelBase+s];
//DeadCode JON 18Oct00 				oredFlags=0;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 				for (t=0;t<4;t++)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					//points on edges have no influence on the inside
//DeadCode JON 18Oct00 					//outside tests done later
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 					ClipResult(xvals[t],zvals[t],cr,clipFlags[t],edgeFlags[t]);
//DeadCode JON 18Oct00 					oredFlags|=clipFlags[t];
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 				//if oredFlags==0 then the tile is completly inside
//DeadCode JON 18Oct00 				//the current region under test
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 				if (oredFlags==0)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 			  		ClipInfo& ci=psqc->clipInfo[psqc->count++];
//DeadCode JON 18Oct00 					ci.level=maxTextureLevels-1-level;
//DeadCode JON 18Oct00 					ci.clipRecIndex=levelBase+s;
//DeadCode JON 18Oct00 					return;
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			//if we get here then this tile must span multiple
//DeadCode JON 18Oct00 			//clip regions at this level so just add all clip 
//DeadCode JON 18Oct00 			//regions that contain a point to our list
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			for (s=1;s<5;s++)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				Rect& cr=clipRects[levelBase+s];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 				andedFlags=_offleft+_offright+_offtop+_offbottom;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 				for (t=0;t<4;t++)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					//points on edges have no influence on the inside
//DeadCode JON 18Oct00 					//outside tests done later
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 					ClipResult(xvals[t],zvals[t],cr,clipFlags[t],edgeFlags[t]);
//DeadCode JON 18Oct00 					andedFlags&=clipFlags[t]|edgeFlags[t];
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 				//if andedFlags==0 then at least one of the tiles
//DeadCode JON 18Oct00 				//points was inside the current clipregion so add
//DeadCode JON 18Oct00 				//it to the list
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 				if (andedFlags==0)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 			  		ClipInfo& ci=psqc->clipInfo[psqc->count++];
//DeadCode JON 18Oct00 					ci.level=maxTextureLevels-1-level;
//DeadCode JON 18Oct00 					ci.clipRecIndex=levelBase+s;
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			return;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//some part of the current tile is in this level and some is in the
//DeadCode JON 18Oct00 	//next. Add the clip areas to be used for the current level. Clip the
//DeadCode JON 18Oct00 	//tile to the central section and recurse
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong newxvals[4],newzvals[4];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	newxvals[_tl]=(clipFlags[_tl]&_offleft)?in.l:xvals[_tl];
//DeadCode JON 18Oct00 	newxvals[_bl]=(clipFlags[_bl]&_offleft)?in.l:xvals[_bl];
//DeadCode JON 18Oct00 	newxvals[_tr]=(clipFlags[_tr]&_offright)?in.r:xvals[_tr];
//DeadCode JON 18Oct00 	newxvals[_br]=(clipFlags[_br]&_offright)?in.r:xvals[_br];
//DeadCode JON 18Oct00 	newzvals[_tl]=(clipFlags[_tl]&_offtop)?in.t:zvals[_tl];
//DeadCode JON 18Oct00 	newzvals[_tr]=(clipFlags[_tr]&_offtop)?in.t:zvals[_tr];
//DeadCode JON 18Oct00 	newzvals[_bl]=(clipFlags[_bl]&_offtop)?in.b:zvals[_bl];
//DeadCode JON 18Oct00 	newzvals[_br]=(clipFlags[_br]&_offtop)?in.b:zvals[_br];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (int s=1;s<5;s++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		Rect& cr=clipRects[levelBase+s];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		andedFlags=_offleft+_offright+_offtop+_offbottom;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		for (t=0;t<4;t++)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			//points on edges have no influence on the inside
//DeadCode JON 18Oct00 			//outside tests done later
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			ClipResult(xvals[t],zvals[t],cr,clipFlags[t],edgeFlags[t]);
//DeadCode JON 18Oct00 			andedFlags&=clipFlags[t]|edgeFlags[t];
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		//if andedFlags==0 then at least one of the tiles
//DeadCode JON 18Oct00 		//points was inside the current clipregion so add
//DeadCode JON 18Oct00 		//it to the list
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (andedFlags==0)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 	  		ClipInfo& ci=psqc->clipInfo[psqc->count++];
//DeadCode JON 18Oct00 			ci.level=maxTextureLevels-1-level;
//DeadCode JON 18Oct00 			ci.clipRecIndex=levelBase+s;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	level++;
//DeadCode JON 18Oct00 	clip_recurse(newxvals,newzvals,level,psqc);
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		TileClipCone
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 29 Jul 1998
//DeadCode JON 18Oct00 //Description	This routine needs to examine each tile based on the CD grid 
//DeadCode JON 18Oct00 //				block system and determine (a) whether the tile needs to be
//DeadCode JON 18Oct00 //				clipped against any of the previously generated clip regions
//DeadCode JON 18Oct00 //				and (b) which level of the texture based grid should be used
//DeadCode JON 18Oct00 //				when the tile is rendered.
//DeadCode JON 18Oct00 //				if the tile crosses the boundary between levels on the texture
//DeadCode JON 18Oct00 //				grid then 
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void TileClipCone(const SLong wx,const SLong wz)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SquareClips* pSquareClips;
//DeadCode JON 18Oct00 	SLong ox,oz,ix;
//DeadCode JON 18Oct00 	SLong dataGridSize;
//DeadCode JON 18Oct00 	SLong wholeAreaSize;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //	dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//DeadCode JON 18Oct00 //					DataGridSizeMAX:DataGridSizeMIN;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //	wholeAreaSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?
//DeadCode JON 18Oct00 //					_wholeAreaSizeMAX:_wholeAreaSizeMIN;
//DeadCode JON 18Oct00 	dataGridSize=DataGridSizeMIN;
//DeadCode JON 18Oct00 	wholeAreaSize=_wholeAreaSizeMIN;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ox=(wx&Grid_Mask)-((dataGridSize>>1)*Grid_Width);
//DeadCode JON 18Oct00 	oz=(wz&Grid_Mask)-((dataGridSize>>1)*Grid_Width);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	pSquareClips=wholeAreaClips;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (int r=0;r<wholeAreaSize;r++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ix=ox;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	 	for (int c=0;c<wholeAreaSize;c++)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			SLong xvals[4],zvals[4];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			//set up world coordinates for the corner points of the
//DeadCode JON 18Oct00 			//tile currently under consideration
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			xvals[_tl]=ix;
//DeadCode JON 18Oct00 			zvals[_tl]=oz;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			xvals[_tr]=ix+Grid_Width;
//DeadCode JON 18Oct00 			zvals[_tr]=oz;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			xvals[_bl]=ix;
//DeadCode JON 18Oct00 			zvals[_bl]=oz+Grid_Width;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			xvals[_br]=ix+Grid_Width;
//DeadCode JON 18Oct00 			zvals[_br]=oz+Grid_Width;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			pSquareClips->count=0;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			clip_recurse(xvals,zvals,0,pSquareClips);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 			pSquareClips++;
//DeadCode JON 18Oct00 			ix+=Grid_Width;
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 		oz+=Grid_Width;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		GetTileClipData
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 30 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void GetTileClipData(SquareClips*& psc)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	psc=wholeAreaClips;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		PrepareNoiseFn
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 7 Aug 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void PrepareNoiseFn()
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	for (int x=0;x<256;x++) tileRnd[x]=Math_Lib.rnd(SLong(0xFF));
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		AliasPixel8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 7 Aug 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SAliasPixel8(SLong x,SLong y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	x=Clamp(SWord(x),SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	y=Clamp(SWord(y),SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	UByte* ptxtadr=((UByte*)pdsttxt)+(x<<8)+y;
//DeadCode JON 18Oct00 	*ptxtadr=currentRouteColor8;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		AliasPixel8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 7 Aug 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void NAliasPixel8(SLong x,SLong y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	x=Clamp(SWord(x),SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	y=Clamp(SWord(y),SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	UByte* ptxtadr=((UByte*)pdsttxt)+(y<<8)+x;
//DeadCode JON 18Oct00 	*ptxtadr=currentRouteColor8;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		AliasPixel16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 7 Aug 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SAliasPixel16(SLong x,SLong y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	x=Clamp(SWord(x),SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	y=Clamp(SWord(y),SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	UWord* ptxtadr=((UWord*)pdsttxt)+(x<<8)+y;
//DeadCode JON 18Oct00 	*ptxtadr=currentRouteColor16;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		AliasPixel16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 7 Aug 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void NAliasPixel16(SLong x,SLong y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	x=Clamp(SWord(x),SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	y=Clamp(SWord(y),SpanMin,SSpanMax);
//DeadCode JON 18Oct00 	UWord* ptxtadr=((UWord*)pdsttxt)+(y<<8)+x;
//DeadCode JON 18Oct00 	*ptxtadr=currentRouteColor16;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SDDAliasPixel8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 11 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SDDAliasPixel8(ROWANSURFACEDESC* prsd,SLong x,SLong y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	UByte* ptxtadr=((UByte*)prsd->lpSurface)+(x*prsd->lPitch)+y;
//DeadCode JON 18Oct00 	*ptxtadr=currentRouteColor8;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		NDDAliasPixel8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 11 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void NDDAliasPixel8(ROWANSURFACEDESC* prsd,SLong x,SLong y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	UByte* ptxtadr=((UByte*)prsd->lpSurface)+(y*prsd->lPitch)+x;
//DeadCode JON 18Oct00 	*ptxtadr=currentRouteColor8;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SDDAliasPixel16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 11 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SDDAliasPixel16(ROWANSURFACEDESC* prsd,SLong x,SLong y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	UWord* ptxtadr=((UWord*)(SLong(prsd->lpSurface)+x*prsd->lPitch))+y;
//DeadCode JON 18Oct00 	*ptxtadr=currentRouteColor16;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		NDDAliasPixel16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 11 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void NDDAliasPixel16(ROWANSURFACEDESC* prsd,SLong x,SLong y)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	UWord* ptxtadr=((UWord*)(SLong(prsd->lpSurface)+y*prsd->lPitch))+x;
//DeadCode JON 18Oct00 	*ptxtadr=currentRouteColor16;
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 void SymLine(SLong,SLong,SLong,SLong);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 void DoLClip(const SWord v1,const SWord v2)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	static XData vc[16];
//DeadCode JON 18Oct00 	static XDataPtr linedef[2];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	XDataPtr newv;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	vc[0].x=xoffset+(pointdef[v1].x>>tile_scale);
//DeadCode JON 18Oct00 	vc[0].y=yoffset+((256-pointdef[v1].z)>>tile_scale);
//DeadCode JON 18Oct00 	vc[0].cf=clipRecord[v1];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	vc[1].x=xoffset+(pointdef[v2].x>>tile_scale);
//DeadCode JON 18Oct00 	vc[1].y=yoffset+((256-pointdef[v2].z)>>tile_scale);
//DeadCode JON 18Oct00 	vc[1].cf=clipRecord[v2];
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	linedef[0]=vc;
//DeadCode JON 18Oct00 	linedef[1]=vc+1;
//DeadCode JON 18Oct00 	newv=vc+2;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//clip against the top of the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (linedef[0]->cf&cf_top) 
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ClipToTop(linedef[1],linedef[0],newv);
//DeadCode JON 18Oct00 		linedef[0]=newv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else if (linedef[1]->cf&cf_top)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ClipToTop(linedef[0],linedef[1],newv);
//DeadCode JON 18Oct00 		linedef[1]=newv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//clip against the bottom of the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (linedef[0]->cf&cf_bot) 
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ClipToBot(linedef[1],linedef[0],newv);
//DeadCode JON 18Oct00 		linedef[0]=newv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else if (linedef[1]->cf&cf_bot)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ClipToBot(linedef[0],linedef[1],newv);
//DeadCode JON 18Oct00 		linedef[1]=newv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//clip against the left of the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (linedef[0]->cf&cf_lft) 
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ClipToLft(linedef[1],linedef[0],newv);
//DeadCode JON 18Oct00 		linedef[0]=newv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else if (linedef[1]->cf&cf_lft)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ClipToLft(linedef[0],linedef[1],newv);
//DeadCode JON 18Oct00 		linedef[1]=newv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//clip against the right of the target area
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (linedef[0]->cf&cf_rgt) 
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ClipToRgt(linedef[1],linedef[0],newv);
//DeadCode JON 18Oct00 		linedef[0]=newv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else if (linedef[1]->cf&cf_rgt)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		ClipToRgt(linedef[0],linedef[1],newv);
//DeadCode JON 18Oct00 		linedef[1]=newv++;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	//draw what's left of the line
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SymLine(linedef[0]->x,linedef[0]->y,linedef[1]->x,linedef[1]->y);
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DoLine
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 13 Aug 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DoLine(const SWord v1,const SWord v2)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong x1,x2,y1,y2;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	x1=xoffset+(pointdef[v1].x>>tile_scale);
//DeadCode JON 18Oct00 	y1=yoffset+((256-pointdef[v1].z)>>tile_scale);
//DeadCode JON 18Oct00 	x2=xoffset+(pointdef[v2].x>>tile_scale);
//DeadCode JON 18Oct00 	y2=yoffset+((256-pointdef[v2].z)>>tile_scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SymLine(x1,y1,x2,y2);
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SymLine
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 7 Aug 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SymLine(SLong a1, SLong b1, SLong a2, SLong b2)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	plotpixelfn ppf;
//DeadCode JON 18Oct00 	SLong dx,dy,incr1,incr2,D,x,y,xend,c,pixels_left;
//DeadCode JON 18Oct00 	SLong x1,y1;
//DeadCode JON 18Oct00 	SLong sign_x,sign_y,step,i;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	dx=Absolute(a2,a1,sign_x);
//DeadCode JON 18Oct00 	dy=Absolute(b2,b1,sign_y);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (sign_x==sign_y)	step=1;
//DeadCode JON 18Oct00 	else				step=-1;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dy>dx)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		Swap(a1,b1);
//DeadCode JON 18Oct00 		Swap(a2,b2);
//DeadCode JON 18Oct00 		Swap(dx,dy);
//DeadCode JON 18Oct00 		ppf=ispalettised?SAliasPixel8:SAliasPixel16;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else ppf=ispalettised?NAliasPixel8:NAliasPixel16;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (a1>a2)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		x=a2;
//DeadCode JON 18Oct00 		y=b2;
//DeadCode JON 18Oct00 		x1=a1;
//DeadCode JON 18Oct00 		y1=b1;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		x=a1;
//DeadCode JON 18Oct00 		y=b1;
//DeadCode JON 18Oct00 		x1=a2;
//DeadCode JON 18Oct00 		y1=b2;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	xend=(dx-1)/4;
//DeadCode JON 18Oct00 	pixels_left=(dx-1)%4;	
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	(*ppf)(x,y);
//DeadCode JON 18Oct00 	(*ppf)(x1,y1);	
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	incr2=4*dy-2*dx;
//DeadCode JON 18Oct00 	if (incr2<0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		c=2*dy;
//DeadCode JON 18Oct00 		incr1=2*c;
//DeadCode JON 18Oct00 		D=incr1-dx;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		for(i=0;i<xend;i++)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			++x;
//DeadCode JON 18Oct00 			--x1;
//DeadCode JON 18Oct00 			if (D<0)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				(*ppf)(x,y);
//DeadCode JON 18Oct00 				(*ppf)(++x,y);
//DeadCode JON 18Oct00 				(*ppf)(x1,y1);
//DeadCode JON 18Oct00 				(*ppf)(--x1,y1);
//DeadCode JON 18Oct00 				D+=incr1;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			else
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				if (D<c)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(x,y);
//DeadCode JON 18Oct00 					(*ppf)(++x,y+=step);
//DeadCode JON 18Oct00 					(*ppf)(x1,y1);
//DeadCode JON 18Oct00 					(*ppf)(--x1,y1-=step);	
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				else
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(x,y+=step);
//DeadCode JON 18Oct00 					(*ppf)(++x,y);
//DeadCode JON 18Oct00 					(*ppf)(x1,y1-=step);
//DeadCode JON 18Oct00 					(*ppf)(--x1,y1);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				D+=incr2;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (pixels_left)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			if (D<0)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				(*ppf)(++x,y);
//DeadCode JON 18Oct00 				if (pixels_left>1)	(*ppf)(++x,y);
//DeadCode JON 18Oct00 				if (pixels_left>2)	(*ppf)(--x1,y1);
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			else
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				if (D<c)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(++x,y);
//DeadCode JON 18Oct00 					if (pixels_left>1)	(*ppf)(++x,y+=step);
//DeadCode JON 18Oct00 					if (pixels_left>2)	(*ppf)(--x1,y1);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				else
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(++x,y+=step);
//DeadCode JON 18Oct00 					if(pixels_left>1)	(*ppf)(++x,y);
//DeadCode JON 18Oct00 					if(pixels_left>2)	(*ppf)(--x1,y1-=step);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		c=2*(dy-dx);
//DeadCode JON 18Oct00 		incr1=2*c;
//DeadCode JON 18Oct00 		D=incr1+dx;
//DeadCode JON 18Oct00 		for (i=0;i<xend;i++)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			++x;
//DeadCode JON 18Oct00 			--x1;
//DeadCode JON 18Oct00 			if (D>0)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				(*ppf)(x,y+=step);
//DeadCode JON 18Oct00 				(*ppf)(++x,y+=step);
//DeadCode JON 18Oct00 				(*ppf)(x1,y1-=step);
//DeadCode JON 18Oct00 				(*ppf)(--x1,y1-=step);
//DeadCode JON 18Oct00 				D+=incr1;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			else
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				if (D<c)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(x,y);
//DeadCode JON 18Oct00 					(*ppf)(++x,y+=step);
//DeadCode JON 18Oct00 					(*ppf)(x1,y1);
//DeadCode JON 18Oct00 					(*ppf)(--x1,y1-=step);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				else
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(x,y+=step);
//DeadCode JON 18Oct00 					(*ppf)(++x,y);
//DeadCode JON 18Oct00 					(*ppf)(x1,y1-=step);
//DeadCode JON 18Oct00 					(*ppf)(--x1,y1);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				D+=incr2;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (pixels_left)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			if (D>0)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				(*ppf)(++x,y+=step);	
//DeadCode JON 18Oct00 				if (pixels_left>1)	(*ppf)(++x,y+=step);
//DeadCode JON 18Oct00 				if (pixels_left>2)	(*ppf)(--x1,y1-=step);
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			else
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				if (D<c)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(++x,y);	
//DeadCode JON 18Oct00 					if (pixels_left>1)	(*ppf)(++x,y+=step);
//DeadCode JON 18Oct00 					if (pixels_left>2)	(*ppf)(--x1,y1);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				else
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(++x,y+=step);
//DeadCode JON 18Oct00 					if (pixels_left>1)	(*ppf)(++x,y);
//DeadCode JON 18Oct00 					if (pixels_left>2)
//DeadCode JON 18Oct00 					{
//DeadCode JON 18Oct00 						if (D>c)		(*ppf)(--x1,y1-=step);
//DeadCode JON 18Oct00 						else			(*ppf)(--x1,y1);
//DeadCode JON 18Oct00                     }
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DDSymLine
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Wed 11 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DDSymLine(ROWANSURFACEDESC* prsd,SLong a1, SLong b1, SLong a2, SLong b2)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	ddpixelfn ppf;
//DeadCode JON 18Oct00 	SLong dx,dy,incr1,incr2,D,x,y,xend,c,pixels_left;
//DeadCode JON 18Oct00 	SLong x1,y1;
//DeadCode JON 18Oct00 	SLong sign_x,sign_y,step,i;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	dx=Absolute(a2,a1,sign_x);
//DeadCode JON 18Oct00 	dy=Absolute(b2,b1,sign_y);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (sign_x==sign_y)	step=1;
//DeadCode JON 18Oct00 	else				step=-1;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (dy>dx)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		Swap(a1,b1);
//DeadCode JON 18Oct00 		Swap(a2,b2);
//DeadCode JON 18Oct00 		Swap(dx,dy);
//DeadCode JON 18Oct00 		ppf=ispalettised?SDDAliasPixel8:SDDAliasPixel16;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else ppf=ispalettised?NDDAliasPixel8:NDDAliasPixel16;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (a1>a2)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		x=a2;
//DeadCode JON 18Oct00 		y=b2;
//DeadCode JON 18Oct00 		x1=a1;
//DeadCode JON 18Oct00 		y1=b1;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		x=a1;
//DeadCode JON 18Oct00 		y=b1;
//DeadCode JON 18Oct00 		x1=a2;
//DeadCode JON 18Oct00 		y1=b2;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	xend=(dx-1)/4;
//DeadCode JON 18Oct00 	pixels_left=(dx-1)%4;	
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	(*ppf)(prsd,x,y);
//DeadCode JON 18Oct00 	(*ppf)(prsd,x1,y1);	
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	incr2=4*dy-2*dx;
//DeadCode JON 18Oct00 	if (incr2<0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		c=2*dy;
//DeadCode JON 18Oct00 		incr1=2*c;
//DeadCode JON 18Oct00 		D=incr1-dx;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		for(i=0;i<xend;i++)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			++x;
//DeadCode JON 18Oct00 			--x1;
//DeadCode JON 18Oct00 			if (D<0)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				(*ppf)(prsd,x,y);
//DeadCode JON 18Oct00 				(*ppf)(prsd,++x,y);
//DeadCode JON 18Oct00 				(*ppf)(prsd,x1,y1);
//DeadCode JON 18Oct00 				(*ppf)(prsd,--x1,y1);
//DeadCode JON 18Oct00 				D+=incr1;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			else
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				if (D<c)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(prsd,x,y);
//DeadCode JON 18Oct00 					(*ppf)(prsd,++x,y+=step);
//DeadCode JON 18Oct00 					(*ppf)(prsd,x1,y1);
//DeadCode JON 18Oct00 					(*ppf)(prsd,--x1,y1-=step);	
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				else
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(prsd,x,y+=step);
//DeadCode JON 18Oct00 					(*ppf)(prsd,++x,y);
//DeadCode JON 18Oct00 					(*ppf)(prsd,x1,y1-=step);
//DeadCode JON 18Oct00 					(*ppf)(prsd,--x1,y1);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				D+=incr2;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (pixels_left)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			if (D<0)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				(*ppf)(prsd,++x,y);
//DeadCode JON 18Oct00 				if (pixels_left>1)	(*ppf)(prsd,++x,y);
//DeadCode JON 18Oct00 				if (pixels_left>2)	(*ppf)(prsd,--x1,y1);
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			else
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				if (D<c)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(prsd,++x,y);
//DeadCode JON 18Oct00 					if (pixels_left>1)	(*ppf)(prsd,++x,y+=step);
//DeadCode JON 18Oct00 					if (pixels_left>2)	(*ppf)(prsd,--x1,y1);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				else
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(prsd,++x,y+=step);
//DeadCode JON 18Oct00 					if(pixels_left>1)	(*ppf)(prsd,++x,y);
//DeadCode JON 18Oct00 					if(pixels_left>2)	(*ppf)(prsd,--x1,y1-=step);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		c=2*(dy-dx);
//DeadCode JON 18Oct00 		incr1=2*c;
//DeadCode JON 18Oct00 		D=incr1+dx;
//DeadCode JON 18Oct00 		for (i=0;i<xend;i++)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			++x;
//DeadCode JON 18Oct00 			--x1;
//DeadCode JON 18Oct00 			if (D>0)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				(*ppf)(prsd,x,y+=step);
//DeadCode JON 18Oct00 				(*ppf)(prsd,++x,y+=step);
//DeadCode JON 18Oct00 				(*ppf)(prsd,x1,y1-=step);
//DeadCode JON 18Oct00 				(*ppf)(prsd,--x1,y1-=step);
//DeadCode JON 18Oct00 				D+=incr1;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			else
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				if (D<c)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(prsd,x,y);
//DeadCode JON 18Oct00 					(*ppf)(prsd,++x,y+=step);
//DeadCode JON 18Oct00 					(*ppf)(prsd,x1,y1);
//DeadCode JON 18Oct00 					(*ppf)(prsd,--x1,y1-=step);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				else
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(prsd,x,y+=step);
//DeadCode JON 18Oct00 					(*ppf)(prsd,++x,y);
//DeadCode JON 18Oct00 					(*ppf)(prsd,x1,y1-=step);
//DeadCode JON 18Oct00 					(*ppf)(prsd,--x1,y1);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				D+=incr2;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		if (pixels_left)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			if (D>0)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				(*ppf)(prsd,++x,y+=step);	
//DeadCode JON 18Oct00 				if (pixels_left>1)	(*ppf)(prsd,++x,y+=step);
//DeadCode JON 18Oct00 				if (pixels_left>2)	(*ppf)(prsd,--x1,y1-=step);
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 			else
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				if (D<c)
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(prsd,++x,y);	
//DeadCode JON 18Oct00 					if (pixels_left>1)	(*ppf)(prsd,++x,y+=step);
//DeadCode JON 18Oct00 					if (pixels_left>2)	(*ppf)(prsd,--x1,y1);
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 				else
//DeadCode JON 18Oct00 				{
//DeadCode JON 18Oct00 					(*ppf)(prsd,++x,y+=step);
//DeadCode JON 18Oct00 					if (pixels_left>1)	(*ppf)(prsd,++x,y);
//DeadCode JON 18Oct00 					if (pixels_left>2)
//DeadCode JON 18Oct00 					{
//DeadCode JON 18Oct00 						if (D>c)		(*ppf)(prsd,--x1,y1-=step);
//DeadCode JON 18Oct00 						else			(*ppf)(prsd,--x1,y1);
//DeadCode JON 18Oct00                     }
//DeadCode JON 18Oct00 				}
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		PolyOutline
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 7 Aug 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void PolyOutline(UByte* p)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong xs,ys,xe,ye;
//DeadCode JON 18Oct00 	SWord vs,ve;
//DeadCode JON 18Oct00 	UByte polyCount;
//DeadCode JON 18Oct00 	UByte edgeCount;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	polyCount=*p++;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	while (polyCount--)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		edgeCount=*p++;
//DeadCode JON 18Oct00 		vs=ve=*p++;
//DeadCode JON 18Oct00 		xe=(pointdef[ve].x>>tile_scale)+xoffset;
//DeadCode JON 18Oct00 		ye=((256-pointdef[ve].z)>>tile_scale)+yoffset;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		while (edgeCount--)
//DeadCode JON 18Oct00 		{
//DeadCode JON 18Oct00 			xs=xe;
//DeadCode JON 18Oct00 			ys=ye;
//DeadCode JON 18Oct00 			ve=*p++;
//DeadCode JON 18Oct00 			xe=(pointdef[ve].x>>tile_scale)+xoffset;
//DeadCode JON 18Oct00 			ye=((256-pointdef[ve].z)>>tile_scale)+yoffset;
//DeadCode JON 18Oct00 			SymLine(xs,ys,xe,ye);
//DeadCode JON 18Oct00 		}
//DeadCode JON 18Oct00 		//and the last section
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xs=(pointdef[vs].x>>tile_scale)+xoffset;
//DeadCode JON 18Oct00 		ys=((256-pointdef[vs].z)>>tile_scale)+yoffset;
//DeadCode JON 18Oct00 		SymLine(xs,ys,xe,ye);
//DeadCode JON 18Oct00 	}	
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AllocateBuffers
//Author		Paul.   
//Date			Tue 6 Oct 1998
//------------------------------------------------------------------------------
void AllocateBuffers()
{
//	if (Save_Data.detail_3d[DETAIL3D_HORIZONDIST])
//	{
		//full horizon

//		land_x=new SLong[Max_TextureLevelsMAX];
//		land_z=new SLong[Max_TextureLevelsMAX];
//		update_req=new bool[Max_TextureLevelsMAX];
 //		gridRecords=new DataRecord[DataGridSizeMAX*DataGridSizeMAX];
//		shadowRecords=new ShadowStruc[DataGridSizeMAX*DataGridSizeMAX];
//		clipRects=new Rect[5*(Max_TextureLevelsMAX-1)+1];
//		gridClipper=new UByte[_areaBufferSizeMAX];
//		wholeAreaClips=new SquareClips[_areaBufferSizeMAX];
//	}
//	else
	{
		//reduced horizon

//DeadCode JON 18Oct00 		land_x=new SLong[Max_TextureLevelsMIN];
//DeadCode JON 18Oct00 		land_z=new SLong[Max_TextureLevelsMIN];
//DeadCode JON 18Oct00 		update_req=new bool[Max_TextureLevelsMIN];
  		gridRecords=new DataRecord[DataGridSizeMIN*DataGridSizeMIN];
//DeadCode JON 18Oct00 		shadowRecords=new ShadowStruc[DataGridSizeMIN*DataGridSizeMIN];
//DeadCode JON 18Oct00 		clipRects=new Rect[5*(Max_TextureLevelsMIN-1)+1];
//DEADCODE JON 4/14/00 		gridClipper=new UByte[_areaBufferSizeMIN];
//DeadCode JON 18Oct00 		wholeAreaClips=new SquareClips[_areaBufferSizeMIN];
	}

//DEADCODE JON 4/14/00 	numShadows=0;
//DEADCODE JON 4/14/00 	curSec=-1L;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ReleaseBuffers
//Author		Paul.   
//Date			Tue 6 Oct 1998
//------------------------------------------------------------------------------
inline void ReleaseBuffers()
{
//DeadCode JON 18Oct00 	delete[]land_x,land_x=NULL;
//DeadCode JON 18Oct00 	delete[]land_z,land_z=NULL;
//DeadCode JON 18Oct00 	delete[]update_req,update_req=NULL;
	delete[]gridRecords,gridRecords=NULL;
//DeadCode JON 18Oct00 	delete[]shadowRecords,shadowRecords=NULL;
//DeadCode JON 18Oct00 	delete[]clipRects,clipRects=NULL;
//DEADCODE JON 4/14/00 	delete[]gridClipper,gridClipper=NULL;
//DeadCode JON 18Oct00 	delete[]wholeAreaClips,wholeAreaClips=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FrameInit
//Author		Jon
//Date			Fri 14 Apr	2000
//------------------------------------------------------------------------------
inline void FrameInit(WorldStuff *wP,LightVec& sunLight)
{
	float	zStretch = SHAD_CUT_OFF;									//RJS 19Oct00
	worldPtr=wP;

	if (sunLight.nj.i > 0.f)									//RJS 19Oct00
	{
		zStretch = 1.f/float(sunLight.nj.i);		//MS 05May00
		if (zStretch > SHAD_CUT_OFF)	zStretch = SHAD_CUT_OFF;
	}

	float	shadScale = zStretch / SHAD_CUT_OFF;

	shadNearAlpha = shadNearMin + (shadScale * (shadNearMax-shadNearMin));
	shadFarAlpha = shadNearAlpha - ((shadNearAlpha * shadScale));

	if ( zStretch < 0 )
		zStretch = -zStretch;

	// generate the shadow dx and sz's.
	shadowDXf = float(sunLight.ni.i)*zStretch;
	shadowDZf = float(sunLight.nk.i)*zStretch;

//TempCode JON 25Sep00 	const float MAX_SHADOW_MULT = 1000.f;
//TempCode JON 25Sep00 	if ( shadowDXf > MAX_SHADOW_MULT )
//TempCode JON 25Sep00 		shadowDXf = MAX_SHADOW_MULT;
//TempCode JON 25Sep00 	else if ( shadowDXf < -MAX_SHADOW_MULT )
//TempCode JON 25Sep00 		shadowDXf = -MAX_SHADOW_MULT;
//TempCode JON 25Sep00 
//TempCode JON 25Sep00 	if ( shadowDZf > MAX_SHADOW_MULT )
//TempCode JON 25Sep00 		shadowDZf = MAX_SHADOW_MULT;
//TempCode JON 25Sep00 	else if ( shadowDZf < -MAX_SHADOW_MULT )
//TempCode JON 25Sep00 		shadowDZf = -MAX_SHADOW_MULT;

}

//DEADCODE JON 4/14/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JON 4/14/00 //Procedure		BuildShadowList
//DEADCODE JON 4/14/00 //Author		Paul.   
//DEADCODE JON 4/14/00 //Date			Thu 22 Oct 1998
//DEADCODE JON 4/14/00 //------------------------------------------------------------------------------
//DEADCODE JON 4/14/00 void BuildShadowList(WorldStuff *wP,itemptr itemp)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	worldPtr=wP;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	//generate a shadow template shape
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00  	SWord sinAng,cosAng;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	ANGLES hdgAng=Math_Lib.HighArcTan(worldPtr->sunpos.X,worldPtr->sunpos.Z);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	Math_Lib.high_sin_cos(hdgAng,sinAng,cosAng);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	SLong m[4];
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	m[0]=m[3]=SLong(cosAng);
//DEADCODE JON 4/14/00 	m[1]=SLong(sinAng);
//DEADCODE JON 4/14/00 	m[2]=-SLong(sinAng);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	const SLong dx=0x00000;
//DEADCODE JON 4/14/00 	const SLong dz=0x10000>>1;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	shadowDX=(m[0]*dx)/ANGLES_FRACT+(m[1]*dz)/ANGLES_FRACT;
//DEADCODE JON 4/14/00 	shadowDZ=(m[2]*dx)/ANGLES_FRACT+(m[3]*dz)/ANGLES_FRACT;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	UWord sec_x,sec_y;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	worldPtr->getsectornos(itemp,sec_x,sec_y);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	ULong new_sec=worldPtr->makeindex(sec_x,sec_y);
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	if (new_sec==curSec) return;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	curSec=new_sec;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00  	numShadows=0;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	SLong sec_cnt=12;
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 	for (UWord cs_x=sec_x-1;sec_cnt;cs_x++)
//DEADCODE JON 4/14/00 		for (UWord cs_y=sec_y-1;--sec_cnt&3;cs_y++)
//DEADCODE JON 4/14/00 			shadowSectors[numShadows++]=worldPtr->makeindex(cs_x,cs_y);
//DEADCODE JON 4/14/00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SortedTriangle8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 27 Oct 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SortedTriangle8(VData* v)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong det;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	UByte* p;
//DeadCode JON 18Oct00 	UByte* t;
//DeadCode JON 18Oct00 	
//DeadCode JON 18Oct00 	det=(v[1].y-v[0].y)*(v[2].x-v[0].x)-(v[1].x-v[0].x)*(v[2].y-v[0].y);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det<0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	left=*EdgeSetup(v,v+2);
//DeadCode JON 18Oct00 		right=*EdgeSetup(v,v+1);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	right=*EdgeSetup(v,v+2);
//DeadCode JON 18Oct00 		left=*EdgeSetup(v,v+1);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	p=(UByte*)pdsttxt+(yi+yoffset)*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	UWord texture_inc=(voffset+(yi<<byteScale))<<8;
//DeadCode JON 18Oct00 	UWord texture_dda=1<<(byteScale+8);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		t=psrctxt+texture_inc;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DrawSpan8(xmin,xmax,p,t);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det>=0)	left=*EdgeSetup(v+1,v+2);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup(v+1,v+2);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 	p=(UByte*)pdsttxt+(yi+yoffset)*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	texture_inc=(voffset+(yi<<byteScale))<<8;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<left.ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		t=psrctxt+texture_inc;
//DeadCode JON 18Oct00 	 	xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DrawSpan8(xmin,xmax,p,t);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SortedTriangle16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 27 Oct 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SortedTriangle16(VData* v)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong det;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	UWord* p;
//DeadCode JON 18Oct00 	UByte* t;
//DeadCode JON 18Oct00 	
//DeadCode JON 18Oct00 	det=(v[1].y-v[0].y)*(v[2].x-v[0].x)-(v[1].x-v[0].x)*(v[2].y-v[0].y);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det<0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	left=*EdgeSetup(v,v+2);
//DeadCode JON 18Oct00 		right=*EdgeSetup(v,v+1);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	right=*EdgeSetup(v,v+2);
//DeadCode JON 18Oct00 		left=*EdgeSetup(v,v+1);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	p=((UWord*)pdsttxt)+(yi+yoffset)*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	UWord texture_inc=(voffset+(yi<<byteScale))<<8;
//DeadCode JON 18Oct00 	UWord texture_dda=1<<(byteScale+8);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	for (;yi<ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00  		t=psrctxt+texture_inc;
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DrawSpan16(xmin,xmax,p,t);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det>=0)	left=*EdgeSetup(v+1,v+2);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup(v+1,v+2);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 	p=((UWord*)pdsttxt)+(yi+yoffset)*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	texture_inc=(voffset+(yi<<byteScale))<<8;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	for (;yi<left.ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00  		t=psrctxt+texture_inc;
//DeadCode JON 18Oct00 	 	xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DrawSpan16(xmin,xmax,p,t);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		ShadowTriangle8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 27 Oct 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void ShadowTriangle8(VData v1,VData v2,VData v3)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	if (v1.y>v2.y) Swap(v1,v2);
//DeadCode JON 18Oct00 	if (v1.y>v3.y) Swap(v1,v3);
//DeadCode JON 18Oct00 	if (v2.y>v3.y) Swap(v2,v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong det;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	UByte* p;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	det=(v2.y-v1.y)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.y-v1.y);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det<0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	left=*EdgeSetup2(v1,v3);
//DeadCode JON 18Oct00 		right=*EdgeSetup2(v1,v2);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	right=*EdgeSetup2(v1,v3);
//DeadCode JON 18Oct00 		left=*EdgeSetup2(v1,v2);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin;
//DeadCode JON 18Oct00 	p=(UByte*)pdsttxt+yi*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++,p+=TextureWidth)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DarkSpan8(xmin,xmax,p);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det>=0)	left=*EdgeSetup2(v2,v3);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup2(v2,v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 	p=(UByte*)pdsttxt+yi*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<left.ymax;yi++,p+=TextureWidth)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DarkSpan8(xmin,xmax,p);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		ShadowTriangle16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 27 Oct 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void ShadowTriangle16(VData v1,VData v2,VData v3)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	if (v1.y>v2.y) Swap(v1,v2);
//DeadCode JON 18Oct00 	if (v1.y>v3.y) Swap(v1,v3);
//DeadCode JON 18Oct00 	if (v2.y>v3.y) Swap(v2,v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	SLong det;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	UWord* p;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	det=(v2.y-v1.y)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.y-v1.y);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det<0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	left=*EdgeSetup2(v1,v3);
//DeadCode JON 18Oct00 		right=*EdgeSetup2(v1,v2);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	right=*EdgeSetup2(v1,v3);
//DeadCode JON 18Oct00 		left=*EdgeSetup2(v1,v2);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin;
//DeadCode JON 18Oct00 	p=((UWord*)pdsttxt)+yi*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++,p+=TextureWidth)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DarkSpan16(xmin,xmax,p);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det>=0)	left=*EdgeSetup2(v2,v3);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup2(v2,v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 	p=((UWord*)pdsttxt)+yi*TextureWidth;
//DeadCode JON 18Oct00 	for (;yi<left.ymax;yi++,p+=TextureWidth)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DarkSpan16(xmin,xmax,p);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SortedTriangle28
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 27 Oct 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SortedTriangle28(VData v1,VData v2,VData v3)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong det;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	UByte* p;
//DeadCode JON 18Oct00 	UByte* t;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	det=(v2.y-v1.y)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.y-v1.y);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det<0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	left=*EdgeSetup2(v1,v3);
//DeadCode JON 18Oct00 		right=*EdgeSetup2(v1,v2);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	right=*EdgeSetup2(v1,v3);
//DeadCode JON 18Oct00 		left=*EdgeSetup2(v1,v2);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	p=(UByte*)pdsttxt+(yi+yoffset)*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	UWord texture_inc=(voffset+(yi<<byteScale))<<8;
//DeadCode JON 18Oct00 	UWord texture_dda=1<<(byteScale+8);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		t=psrctxt+texture_inc;
//DeadCode JON 18Oct00 	 	xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DrawSpan8(xmin,xmax,p,t);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det>=0)	left=*EdgeSetup2(v2,v3);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup2(v2,v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 	p=(UByte*)pdsttxt+(yi+yoffset)*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	texture_inc=(voffset+(yi<<byteScale))<<8;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<left.ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		t=psrctxt+texture_inc;
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DrawSpan8(xmin,xmax,p,t);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		SortedTriangle216
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 27 Oct 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void SortedTriangle216(VData v1,VData v2,VData v3)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	SLong det;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	UWord* p;
//DeadCode JON 18Oct00 	UByte* t;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	det=(v2.y-v1.y)*(v3.x-v1.x)-(v2.x-v1.x)*(v3.y-v1.y);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det<0)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	left=*EdgeSetup2(v1,v3);
//DeadCode JON 18Oct00 		right=*EdgeSetup2(v1,v2);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 	else
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 	 	right=*EdgeSetup2(v1,v3);
//DeadCode JON 18Oct00 		left=*EdgeSetup2(v1,v2);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin;
//DeadCode JON 18Oct00 	p=((UWord*)pdsttxt)+(yi+yoffset)*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	UWord texture_inc=(voffset+(yi<<byteScale))<<8;
//DeadCode JON 18Oct00 	UWord texture_dda=1<<(byteScale+8);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		t=psrctxt+texture_inc;
//DeadCode JON 18Oct00 	 	xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DrawSpan16(xmin,xmax,p,t);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det>=0)	left=*EdgeSetup2(v2,v3);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup2(v2,v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 	p=((UWord*)pdsttxt)+(yi+yoffset)*TextureWidth;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00  	texture_inc=(voffset+(yi<<byteScale))<<8;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<left.ymax;yi++,p+=TextureWidth,texture_inc+=texture_dda)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		t=psrctxt+texture_inc;
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 		DrawSpan16(xmin,xmax,p,t);
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DDSortedTriangle8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 6 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DDSortedTriangle8(	VTriPtr sTri,
//DeadCode JON 18Oct00 						ROWANSURFACEDESC* prsd,
//DeadCode JON 18Oct00 						UByte* ptxt,SWord scale)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	const SLong XMIN=0;
//DeadCode JON 18Oct00 	const SLong XMAX=255;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Edge *left,*right,edge1,edge2;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	SLong src_dx,src_dy;
//DeadCode JON 18Oct00 	UByte* pdst;
//DeadCode JON 18Oct00 	UByte* psrc;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	bool det=((sTri->v2.y-sTri->v1.y)*(sTri->v3.x-sTri->v1.x)-
//DeadCode JON 18Oct00 				(sTri->v2.x-sTri->v1.x)*(sTri->v3.y-sTri->v1.y)<0)?true:false;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	edge1=*EdgeSetup(&sTri->v1,&sTri->v3,scale);
//DeadCode JON 18Oct00 	edge2=*EdgeSetup(&sTri->v1,&sTri->v2,scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (det)	{left=&edge1;right=&edge2;}
//DeadCode JON 18Oct00 	else		{right=&edge1;left=&edge2;}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left->ymin>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	src_dx=1<<scale;
//DeadCode JON 18Oct00 	src_dy=TextureWidth<<scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	pdst=(UByte*)prsd->lpSurface+(yi*prsd->lPitch);
//DeadCode JON 18Oct00 	psrc=ptxt+(left->ymin<<8);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left->ymax,right->ymax)>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=Clamp(xmin,XMIN,XMAX);
//DeadCode JON 18Oct00 		xmax=Clamp(xmax,XMIN,XMAX);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		UByte* psrc2=psrc+xmin;	//texture data ptr
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin>>=scale;
//DeadCode JON 18Oct00 		xmax>>=scale;
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		UByte* pdst2=pdst+xmin;	//DD surface ptr
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		if (xmin<=xmax)
//DeadCode JON 18Oct00 			for (xmax-=(xmin-1);xmax--;)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				*pdst2++=*psrc2;
//DeadCode JON 18Oct00 				psrc2+=src_dx;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		pdst+=prsd->lPitch;
//DeadCode JON 18Oct00 		psrc+=src_dy;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (!det)	*left=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
//DeadCode JON 18Oct00 	else		*right=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left->ymin,right->ymin);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	psrc=ptxt+(yi<<8);
//DeadCode JON 18Oct00 	yi>>=scale;
//DeadCode JON 18Oct00 	pdst=(UByte*)prsd->lpSurface+(yi*prsd->lPitch);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=left->ymax>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=Clamp(xmin,XMIN,XMAX);
//DeadCode JON 18Oct00 		xmax=Clamp(xmax,XMIN,XMAX);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		UByte* psrc2=psrc+xmin;	//texture data ptr
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin>>=scale;
//DeadCode JON 18Oct00 		xmax>>=scale;
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		UByte* pdst2=pdst+xmin;	//DD surface ptr
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		if (xmin<=xmax)
//DeadCode JON 18Oct00 			for (xmax-=(xmin-1);xmax--;)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				*pdst2++=*psrc2;
//DeadCode JON 18Oct00 				psrc2+=src_dx;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		pdst+=prsd->lPitch;
//DeadCode JON 18Oct00 		psrc+=src_dy;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DDSortedTriangle16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Fri 6 Nov 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DDSortedTriangle16(VTriPtr sTri,
//DeadCode JON 18Oct00 						ROWANSURFACEDESC* prsd,
//DeadCode JON 18Oct00 						UByte* ptxt,SWord scale)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	const SLong XMIN=0;
//DeadCode JON 18Oct00 	const SLong XMAX=255;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	SLong src_dx,src_dy;
//DeadCode JON 18Oct00 	UWord* pdst;
//DeadCode JON 18Oct00 	UByte* psrc;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	bool det=((sTri->v2.y-sTri->v1.y)*(sTri->v3.x-sTri->v1.x)-
//DeadCode JON 18Oct00 				(sTri->v2.x-sTri->v1.x)*(sTri->v3.y-sTri->v1.y)<0)?true:false;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	left=*EdgeSetup(&sTri->v1,&sTri->v3,scale);
//DeadCode JON 18Oct00 	right=*EdgeSetup(&sTri->v1,&sTri->v2,scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (!det) Swap(left,right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	src_dx=1<<scale;
//DeadCode JON 18Oct00 	src_dy=TextureWidth<<scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	pdst=(UWord*)(ULong(prsd->lpSurface)+ULong(yi*prsd->lPitch));
//DeadCode JON 18Oct00 	psrc=ptxt+(left.ymin<<8);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax)>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=Clamp(xmin,XMIN,XMAX);
//DeadCode JON 18Oct00 		xmax=Clamp(xmax,XMIN,XMAX);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		UByte* psrc2=psrc+xmin;	//texture data ptr
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin>>=scale;
//DeadCode JON 18Oct00 		xmax>>=scale;
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		UWord* pdst2=pdst+xmin;	//DD surface ptr
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		if (xmin<=xmax)
//DeadCode JON 18Oct00 			for (xmax-=(xmin-1);xmax--;)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				*pdst2++=palLookup[*psrc2];
//DeadCode JON 18Oct00 				psrc2+=src_dx;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		pdst=(UWord*)(ULong(pdst)+ULong(prsd->lPitch));
//DeadCode JON 18Oct00 		psrc+=src_dy;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (!det)	left=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	psrc=ptxt+(yi<<8);
//DeadCode JON 18Oct00 	yi>>=scale;
//DeadCode JON 18Oct00 	pdst=(UWord*)(ULong(prsd->lpSurface)+ULong(yi*prsd->lPitch));
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=left.ymax>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=Clamp(xmin,XMIN,XMAX);
//DeadCode JON 18Oct00 		xmax=Clamp(xmax,XMIN,XMAX);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		UByte* psrc2=psrc+xmin;	//texture data ptr
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin>>=scale;
//DeadCode JON 18Oct00 		xmax>>=scale;
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		UWord* pdst2=pdst+xmin;	//DD surface ptr
//DeadCode JON 18Oct00 	
//DeadCode JON 18Oct00 		if (xmin<=xmax)
//DeadCode JON 18Oct00 			for (xmax-=(xmin-1);xmax--;)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				*pdst2++=palLookup[*psrc2];
//DeadCode JON 18Oct00 				psrc2+=src_dx;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		pdst=(UWord*)(ULong(pdst)+ULong(prsd->lPitch));
//DeadCode JON 18Oct00 		psrc+=src_dy;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DrawShadowTriangle
//DeadCode JON 18Oct00 //Author		Jon
//DeadCode JON 18Oct00 //Date			Wed 13th Apr 2000
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DrawShadowTriangle( CLib3D* lib3d,
//DeadCode JON 18Oct00 						VData v0,VData v1,VData v2,
//DeadCode JON 18Oct00 						SWord scale)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Lib3DPoint* vert = lib3d->BeginPoly( NULL_MATERIAL, 3 );
//DeadCode JON 18Oct00 	vert[0].setPosition( v0.x, v0.y );
//DeadCode JON 18Oct00 	vert[1].setPosition( v1.x, v1.y );
//DeadCode JON 18Oct00 	vert[2].setPosition( v2.x, v2.y );
//DeadCode JON 18Oct00 	lib3d->EndPoly();
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	R3DVERTEX* vert;
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	lib3d->BeginPoly( HMATERIAL( UByte(120) ), 3, vert );
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	vert[0].bodyx.f=v0.x;//*DIV_SCALE;//<<scale;
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	vert[0].bodyy.f=v0.y;//*DIV_SCALE;//<<scale;
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	vert[1].bodyx.f=v1.x;//*DIV_SCALE;//<<scale;
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	vert[1].bodyy.f=v1.y;//*DIV_SCALE;//<<scale;
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	vert[2].bodyx.f=v2.x;//*DIV_SCALE;//<<scale;
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	vert[2].bodyy.f=v2.y;//*DIV_SCALE;//<<scale;
//DeadCode JON 18Oct00 //DEADCODE JON 5/23/00 	lib3d->EndPoly();
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DDShadowTriangle8
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 1 Dec 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DDShadowTriangle8(	ROWANSURFACEDESC* prsd,
//DeadCode JON 18Oct00 						VData v0,VData v1,VData v2,
//DeadCode JON 18Oct00 						SWord scale)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	VTri xTri,*sTri=&xTri;
//DeadCode JON 18Oct00 	xTri.v1=v0;
//DeadCode JON 18Oct00 	xTri.v2=v1;
//DeadCode JON 18Oct00 	xTri.v3=v2;
//DeadCode JON 18Oct00 	if (xTri.v1.y>xTri.v2.y)	Swap(xTri.v1,xTri.v2);
//DeadCode JON 18Oct00 	if (xTri.v1.y>xTri.v3.y)	Swap(xTri.v1,xTri.v3);
//DeadCode JON 18Oct00 	if (xTri.v2.y>xTri.v3.y)	Swap(xTri.v2,xTri.v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	const SLong XMIN=0;
//DeadCode JON 18Oct00 	const SLong XMAX=255;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	UByte* pdst;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	bool det=((sTri->v2.y-sTri->v1.y)*(sTri->v3.x-sTri->v1.x)-
//DeadCode JON 18Oct00 				(sTri->v2.x-sTri->v1.x)*(sTri->v3.y-sTri->v1.y)<0)?true:false;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	left=*EdgeSetup(&sTri->v1,&sTri->v3,scale);
//DeadCode JON 18Oct00 	right=*EdgeSetup(&sTri->v1,&sTri->v2,scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (!det) Swap(left,right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	pdst=(UByte*)prsd->lpSurface+(yi*prsd->lPitch);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax)>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=Clamp(xmin,XMIN,XMAX);
//DeadCode JON 18Oct00 		xmax=Clamp(xmax,XMIN,XMAX);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin>>=scale;
//DeadCode JON 18Oct00 		xmax>>=scale;
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		UByte* pdst2=pdst+xmin;	//DD surface ptr
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		if (xmin<=xmax)
//DeadCode JON 18Oct00 			for (xmax-=(xmin-1);xmax--;)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				*pdst2++=8;	//CHANGE HERE TO ALTER SHADOW COLOUR
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		pdst+=prsd->lPitch;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (!det)	left=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi>>=scale;
//DeadCode JON 18Oct00 	pdst=(UByte*)prsd->lpSurface+(yi*prsd->lPitch);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=left.ymax>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=Clamp(xmin,XMIN,XMAX);
//DeadCode JON 18Oct00 		xmax=Clamp(xmax,XMIN,XMAX);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin>>=scale;
//DeadCode JON 18Oct00 		xmax>>=scale;
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		UByte* pdst2=pdst+xmin;	//DD surface ptr
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		if (xmin<=xmax)
//DeadCode JON 18Oct00 			for (xmax-=(xmin-1);xmax--;)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				*pdst2++=8;	//CHANGE HERE TO ALTER SHADOW COLOUR
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		pdst+=prsd->lPitch;
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		DDShadowTriangle16
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Tue 1 Dec 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void DDShadowTriangle16(ROWANSURFACEDESC* prsd,
//DeadCode JON 18Oct00 						VData v0,VData v1,VData v2,
//DeadCode JON 18Oct00 						SWord scale)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	VTri xTri,*sTri=&xTri;
//DeadCode JON 18Oct00 	xTri.v1=v0;
//DeadCode JON 18Oct00 	xTri.v2=v1;
//DeadCode JON 18Oct00 	xTri.v3=v2;
//DeadCode JON 18Oct00 	if (xTri.v1.y>xTri.v2.y)	Swap(xTri.v1,xTri.v2);
//DeadCode JON 18Oct00 	if (xTri.v1.y>xTri.v3.y)	Swap(xTri.v1,xTri.v3);
//DeadCode JON 18Oct00 	if (xTri.v2.y>xTri.v3.y)	Swap(xTri.v2,xTri.v3);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	const SLong XMIN=0;
//DeadCode JON 18Oct00 	const SLong XMAX=255;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	Edge left,right;
//DeadCode JON 18Oct00 	SLong yi,xmin,xmax,ymax;
//DeadCode JON 18Oct00 	UWord* pdst;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	bool det=((sTri->v2.y-sTri->v1.y)*(sTri->v3.x-sTri->v1.x)-
//DeadCode JON 18Oct00 				(sTri->v2.x-sTri->v1.x)*(sTri->v3.y-sTri->v1.y)<0)?true:false;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	left=*EdgeSetup(&sTri->v1,&sTri->v3,scale);
//DeadCode JON 18Oct00 	right=*EdgeSetup(&sTri->v1,&sTri->v2,scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (!det) Swap(left,right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=left.ymin>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	pdst=(UWord*)(ULong(prsd->lpSurface)+ULong(yi*prsd->lPitch));
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=Min(left.ymax,right.ymax)>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=Clamp(xmin,XMIN,XMAX);
//DeadCode JON 18Oct00 		xmax=Clamp(xmax,XMIN,XMAX);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin>>=scale;
//DeadCode JON 18Oct00 		xmax>>=scale;
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		UWord* pdst2=pdst+xmin;	//DD surface ptr
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		if (xmin<=xmax)
//DeadCode JON 18Oct00 			for (xmax-=(xmin-1);xmax--;)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				*pdst2++=0;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		pdst=(UWord*)(ULong(pdst)+ULong(prsd->lPitch));
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	if (!det)	left=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
//DeadCode JON 18Oct00 	else		right=*EdgeSetup(&sTri->v2,&sTri->v3,scale);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi=Max(left.ymin,right.ymin);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	yi>>=scale;
//DeadCode JON 18Oct00 	pdst=(UWord*)(ULong(prsd->lpSurface)+ULong(yi*prsd->lPitch));
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	ymax=left.ymax>>scale;
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 	for (;yi<ymax;yi++)
//DeadCode JON 18Oct00 	{
//DeadCode JON 18Oct00 		xmin=EdgeScan(&left);
//DeadCode JON 18Oct00 		xmax=EdgeScan(&right);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin=Clamp(xmin,XMIN,XMAX);
//DeadCode JON 18Oct00 		xmax=Clamp(xmax,XMIN,XMAX);
//DeadCode JON 18Oct00 
//DeadCode JON 18Oct00 		xmin>>=scale;
//DeadCode JON 18Oct00 		xmax>>=scale;
//DeadCode JON 18Oct00 		
//DeadCode JON 18Oct00 		UWord* pdst2=pdst+xmin;	//DD surface ptr
//DeadCode JON 18Oct00 	
//DeadCode JON 18Oct00 		if (xmin<=xmax)
//DeadCode JON 18Oct00 			for (xmax-=(xmin-1);xmax--;)
//DeadCode JON 18Oct00 			{
//DeadCode JON 18Oct00 				*pdst2++=0;
//DeadCode JON 18Oct00 			}
//DeadCode JON 18Oct00 		pdst=(UWord*)(ULong(pdst)+ULong(prsd->lPitch));
//DeadCode JON 18Oct00 	}
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderTile2Surface
//Author		Paul.   
//Date			Fri 6 Nov 1998
//------------------------------------------------------------------------------
//DEADCODE JON 4/12/00 void RenderTile2Surface(UByte* pdata,ROWANSURFACEDESC* prsd)
//DEADCODE JON 4/12/00 {
//DEADCODE JON 4/12/00 	UWord *bupPal=palLookup;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	VTri vTri,sTri;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	AltPointsHdr*	aph;
//DEADCODE JON 4/12/00 	DrawDataHdr*	ddh;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	aph=(AltPointsHdr*)pdata;
//DEADCODE JON 4/12/00 	pdata+=sizeof(AltPointsHdr);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	ClearRecords(aph->vertexCount);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	pointdef=(PointDef*)pdata;
//DEADCODE JON 4/12/00 	pdata+=aph->vertexCount*sizeof(PointDef);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	ddh=(DrawDataHdr*)pdata;
//DEADCODE JON 4/12/00 	pdata+=sizeof(DrawDataHdr);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	SWord primCount=ddh->noOfPolys;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	SWord scale=3;													  //JIM 29/03/99
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	if (prsd->dwWidth==256)			scale=0;
//DEADCODE JON 4/12/00 	else if (prsd->dwWidth==128)	scale=1;
//DEADCODE JON 4/12/00 	else if (prsd->dwWidth==64)		scale=2;
//DEADCODE JON 4/12/00 	else if (prsd->dwWidth==32)		scale=3;
//DEADCODE JON 4/12/00 	else if (prsd->dwWidth==16)		scale=4;
//DEADCODE JON 4/12/00 	else if (prsd->dwWidth==8)		scale=5;
//DEADCODE JON 4/12/00 	else assert(false&&"ERROR:Silly scale factor");
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	while (primCount--)
//DEADCODE JON 4/12/00 	{
//DEADCODE JON 4/12/00 	 	UByte* ptxt=imageData[*pdata&0x1F];
//DEADCODE JON 4/12/00 		palLookup=bupPal+(*pdata&0x1F)*256;
//DEADCODE JON 4/12/00 		pdata++;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		UByte fanCount=*pdata++;
//DEADCODE JON 4/12/00 		
//DEADCODE JON 4/12/00 		while (fanCount--)
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 			UByte triCount=*pdata++;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 			SWord v=*pdata++;
//DEADCODE JON 4/12/00 			vTri.v1.x=pointdef[v].x;
//DEADCODE JON 4/12/00 			vTri.v1.y=(256-pointdef[v].z);
//DEADCODE JON 4/12/00 			vTri.v1.v=v;
//DEADCODE JON 4/12/00 			v=*pdata++;
//DEADCODE JON 4/12/00 			vTri.v3.x=pointdef[v].x;
//DEADCODE JON 4/12/00 			vTri.v3.y=(256-pointdef[v].z);
//DEADCODE JON 4/12/00 			vTri.v3.v=v;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 			while (triCount--)
//DEADCODE JON 4/12/00 			{
//DEADCODE JON 4/12/00 			 	vTri.v2=vTri.v3;
//DEADCODE JON 4/12/00 				v=*pdata++;
//DEADCODE JON 4/12/00 				vTri.v3.x=pointdef[v].x;
//DEADCODE JON 4/12/00 				vTri.v3.y=(256-pointdef[v].z);
//DEADCODE JON 4/12/00 				vTri.v3.v=v;
//DEADCODE JON 4/12/00 				sTri=vTri;
//DEADCODE JON 4/12/00 				if (sTri.v1.y>sTri.v2.y)	Swap(sTri.v1,sTri.v2);
//DEADCODE JON 4/12/00 				if (sTri.v1.y>sTri.v3.y)	Swap(sTri.v1,sTri.v3);
//DEADCODE JON 4/12/00 				if (sTri.v2.y>sTri.v3.y)	Swap(sTri.v2,sTri.v3);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 				//sTri contains the triangle vertex coordinates unscaled
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 				if (prsd->ddpfPixelFormat.dwRGBBitCount==8)
//DEADCODE JON 4/12/00 					DDSortedTriangle8(&sTri,prsd,ptxt,scale);
//DEADCODE JON 4/12/00 				else if (prsd->ddpfPixelFormat.dwRGBBitCount==16)
//DEADCODE JON 4/12/00 					DDSortedTriangle16(&sTri,prsd,ptxt,scale);
//DEADCODE JON 4/12/00 			}
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 	}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	palLookup=bupPal;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	primCount=((scale<2) && Save_Data.detail_3d[DETAIL3D_ROUTES])?
//DEADCODE JON 4/12/00 				ddh->noOfLines:0;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	while (primCount--)
//DEADCODE JON 4/12/00 	{
//DEADCODE JON 4/12/00 		UByte lineCol;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		switch (*pdata++)
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 		case RT_AirField:
//DEADCODE JON 4/12/00 			lineCol=249;		//??
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_HedgerowThick:
//DEADCODE JON 4/12/00 			lineCol=71;			//11,35,11
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_HedgerowThin:
//DEADCODE JON 4/12/00 			lineCol=77;			//11,35,11
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_MajorRiver:
//DEADCODE JON 4/12/00 			lineCol=39;			//32,40,72
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_MinorRiver:
//DEADCODE JON 4/12/00 			lineCol=36;			//42,49,79
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_Tributary:
//DEADCODE JON 4/12/00 			lineCol=36;			//42,49,79
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_MinorRoad:
//DEADCODE JON 4/12/00 			lineCol=251;		//71,60,44
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_Footpath:
//DEADCODE JON 4/12/00 			lineCol=203;		//106,89,65
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_MajorRail:
//DEADCODE JON 4/12/00 			lineCol=0;			//22,22,22
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_MinorRail:
//DEADCODE JON 4/12/00 			lineCol=2;			//30,30,30
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_ARoad:
//DEADCODE JON 4/12/00 			lineCol=249;		//55,58,55
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		case RT_BRoad:
//DEADCODE JON 4/12/00 			lineCol=250;		//68,74,68
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 //				case RT_magic:
//DEADCODE JON 4/12/00 //					lineCol=111;
//DEADCODE JON 4/12/00 //					break;
//DEADCODE JON 4/12/00 		default:
//DEADCODE JON 4/12/00 			lineCol=ARTWORKMASK;
//DEADCODE JON 4/12/00 			break;
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		if (prsd->ddpfPixelFormat.dwRGBBitCount==8)
//DEADCODE JON 4/12/00 			currentRouteColor8=lineCol;
//DEADCODE JON 4/12/00 	 	else
//DEADCODE JON 4/12/00 			currentRouteColor16=palLookup[lineCol];
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		UByte sectionCount=*pdata++;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		if (lineCol==ARTWORKMASK)
//DEADCODE JON 4/12/00 			pdata+=sectionCount;
//DEADCODE JON 4/12/00 		else
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 			SWord v=*pdata++;
//DEADCODE JON 4/12/00 			SLong x2,y2;
//DEADCODE JON 4/12/00 			x2=pointdef[v].x;
//DEADCODE JON 4/12/00 			y2=256-pointdef[v].z;
//DEADCODE JON 4/12/00 			x2=x2<0?0:x2>255?255>>scale:x2>>scale;
//DEADCODE JON 4/12/00 			y2=y2<0?0:y2>255?255>>scale:y2>>scale;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 			while (--sectionCount!=0)
//DEADCODE JON 4/12/00 			{
//DEADCODE JON 4/12/00 				SLong x1,y1;
//DEADCODE JON 4/12/00 				x1=x2;
//DEADCODE JON 4/12/00 				y1=y2;
//DEADCODE JON 4/12/00 				v=*pdata++;
//DEADCODE JON 4/12/00 				x2=pointdef[v].x;
//DEADCODE JON 4/12/00 				y2=256-pointdef[v].z;
//DEADCODE JON 4/12/00 				x2=x2<0?0:x2>255?255>>scale:x2>>scale;
//DEADCODE JON 4/12/00 				y2=y2<0?0:y2>255?255>>scale:y2>>scale;
//DEADCODE JON 4/12/00 				DDSymLine(prsd,x1,y1,x2,y2);
//DEADCODE JON 4/12/00 			}
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 	}
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 	//check for shadow rendering to this tile
//DEADCODE JON 4/12/00 	if (scale<2 && Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])
//DEADCODE JON 4/12/00 	{
//DEADCODE JON 4/12/00 		//currentShadowRec contains world coordinates for sector search
//DEADCODE JON 4/12/00 		item dummyItem,*itemPtr;
//DEADCODE JON 4/12/00 		UWord sec_x,sec_y;
//DEADCODE JON 4/12/00 		dummyItem.World.X=currentShadowRec.world_x+(Grid_Width>>1);
//DEADCODE JON 4/12/00 		dummyItem.World.Z=currentShadowRec.world_z+(Grid_Width>>1);
//DEADCODE JON 4/12/00 		worldPtr->getsectornos(&dummyItem,sec_x,sec_y);
//DEADCODE JON 4/12/00 		ULong sec_index=worldPtr->makeindex(sec_x,sec_y);
//DEADCODE JON 4/12/00 		itemPtr=worldPtr->getfirstitem(sec_index);
//DEADCODE JON 4/12/00 		while (itemPtr)
//DEADCODE JON 4/12/00 		{
//DEADCODE JON 4/12/00 			const SLong gridSx=currentShadowRec.world_x;
//DEADCODE JON 4/12/00 			const SLong gridSz=currentShadowRec.world_z;
//DEADCODE JON 4/12/00 			const SLong gridEx=gridSx+Grid_Width;
//DEADCODE JON 4/12/00 			const SLong gridEz=gridSz+Grid_Width;
//DEADCODE JON 4/12/00 			const SLong world2Pix=9;	//+scale;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 		 	if (itemPtr->Status.size<=RotatedSize)
//DEADCODE JON 4/12/00 			{
//DEADCODE JON 4/12/00 				ShapeDescPtr shapePtr=SHAPESTUFF.GetShapePtr(itemPtr->shape);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 				if (SHAPESTUFF.GetShapeScale(shapePtr)==SHP_GRP)
//DEADCODE JON 4/12/00 				{
//DEADCODE JON 4/12/00 					if (groupHasShadow(itemPtr->shape))
//DEADCODE JON 4/12/00 					{
//DEADCODE JON 4/12/00 						UByte* inst_ptr=(UByte*)shapePtr+shapePtr->liveshpref;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 						for (SWord inst=*inst_ptr++;inst==dogroupno;inst=*inst_ptr++)
//DEADCODE JON 4/12/00 						{
//DEADCODE JON 4/12/00 							DOGROUP_PTR gptr=(DOGROUP_PTR)inst_ptr;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 							SLong cx=itemPtr->World.X+gptr->xoffset;
//DEADCODE JON 4/12/00 							SLong cz=itemPtr->World.Z+gptr->zoffset;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 							if (cx>gridSx && cx<gridEx && cz>gridSz && cz<gridEz && shapeHasShadow((ShapeNum)gptr->shapenum))
//DEADCODE JON 4/12/00 							{
//DEADCODE JON 4/12/00 								SWord hdg=gptr->angle;
//DEADCODE JON 4/12/00 								cx=(cx-gridSx)>>world2Pix;
//DEADCODE JON 4/12/00 								cz=(cz-gridSz)>>world2Pix;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 								ShapeDescPtr groupPtr=SHAPESTUFF.GetShapePtr((ShapeNum)gptr->shapenum);
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 								if (hdg==0)	RenderShadow(prsd,groupPtr,cx,cz,scale);
//DEADCODE JON 4/12/00 								else   		RenderShadowRotated(prsd,groupPtr,cx,cz,hdg,scale);
//DEADCODE JON 4/12/00 							}
//DEADCODE JON 4/12/00 							inst_ptr+=sizeof(DOGROUP);
//DEADCODE JON 4/12/00 						}
//DEADCODE JON 4/12/00 					}
//DEADCODE JON 4/12/00 				}
//DEADCODE JON 4/12/00 				else if (	itemPtr->World.X>gridSx &&
//DEADCODE JON 4/12/00 							itemPtr->World.X<gridEx &&
//DEADCODE JON 4/12/00 							itemPtr->World.Z>gridSz &&
//DEADCODE JON 4/12/00 							itemPtr->World.Z<gridEz &&
//DEADCODE JON 4/12/00 							shapeHasShadow(itemPtr->shape))
//DEADCODE JON 4/12/00 				{
//DEADCODE JON 4/12/00 					SWord hdg;
//DEADCODE JON 4/12/00 					SLong tx,tz;
//DEADCODE JON 4/12/00 					hdg=itemPtr->Status.size<HdgSize?0:((hdgitem*)itemPtr)->hdg;
//DEADCODE JON 4/12/00 
//DEADCODE JON 4/12/00 					tx=(itemPtr->World.X-gridSx)>>world2Pix;
//DEADCODE JON 4/12/00 					tz=(itemPtr->World.Z-gridSz)>>world2Pix;
//DEADCODE JON 4/12/00 					if (hdg==0)	RenderShadow(prsd,shapePtr,tx,tz,scale);
//DEADCODE JON 4/12/00 					else		RenderShadowRotated(prsd,shapePtr,tx,tz,hdg,scale);
//DEADCODE JON 4/12/00 				}
//DEADCODE JON 4/12/00 			}
//DEADCODE JON 4/12/00 			itemPtr=itemPtr->Next;
//DEADCODE JON 4/12/00 		}
//DEADCODE JON 4/12/00 	}
//DEADCODE JON 4/12/00 }

//DEADCODE JON 4/14/00 void DoRenderTileToRowanSurface(UByte* pTileData,const HTEXT& hTexture)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 	//Select correct Rowan surface from hTexture
//DEADCODE JON 4/14/00 	ROWANSURFACEDESC* rsd;
//DEADCODE JON 4/14/00 	ULong ht=hTexture();
//DEADCODE JON 4/14/00 	if (ht<SOFT_256_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram256maps[ht];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram128maps[ht-SOFT_256_TEXTURES];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram64maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram32maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES+SOFT_16_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram16maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES-SOFT_32_TEXTURES];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES+SOFT_16_TEXTURES+SOFT_8_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram8maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES-SOFT_32_TEXTURES-SOFT_16_TEXTURES];
//DEADCODE JON 4/14/00 	else 
//DEADCODE JON 4/14/00 		assert(false&&"Bad Texture handle");
//DEADCODE JON 4/14/00 	Three_Dee.pTMake->RenderTile2Surface(pTileData,rsd);
//DEADCODE JON 4/14/00 }
//DEADCODE JON 4/14/00 
//DEADCODE JON 4/14/00 ROWANSURFACEDESC* GetRSD(const HTEXT& hTexture)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 	ROWANSURFACEDESC* rsd;
//DEADCODE JON 4/14/00 	ULong ht=hTexture();
//DEADCODE JON 4/14/00 	if (ht<SOFT_256_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram256maps[ht];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram128maps[ht-SOFT_256_TEXTURES];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram64maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram32maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES+SOFT_16_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram16maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES-SOFT_32_TEXTURES];
//DEADCODE JON 4/14/00 	else if (ht<SOFT_256_TEXTURES+SOFT_128_TEXTURES+SOFT_64_TEXTURES+SOFT_32_TEXTURES+SOFT_16_TEXTURES+SOFT_8_TEXTURES)
//DEADCODE JON 4/14/00 		rsd=sysram8maps[ht-SOFT_256_TEXTURES-SOFT_128_TEXTURES-SOFT_64_TEXTURES-SOFT_32_TEXTURES-SOFT_16_TEXTURES];
//DEADCODE JON 4/14/00 	else assert(false&&"Bad Texture handle");
//DEADCODE JON 4/14/00 	return rsd;
//DEADCODE JON 4/14/00 }


inline SWord RenderEdgeStrip(SWord x1,SWord y1,SWord x2,SWord y2,SWord right_ix,SWord shift)
{ 
	SWord xx[4],yy[4];
	SWord dx,dy;
	SWord left_ix;
	dy=(y2-y1);
	dx=(x2-x1);
	SWord len=fastMath.FastLen(dx,dy);
	if (len)
	{
		SWord tmp=dx;
		dx=-(dy<<2)/len;
		dy=(tmp<<2)/len;
		xx[0]=x1+dx;
		yy[0]=y1+dy;
		xx[1]=x2+dx;
		yy[1]=y2+dy;
		xx[2]=x2-dx;
		yy[2]=y2-dy;
		xx[3]=x1-dx;
		yy[3]=y1-dy;
		left_ix=right_ix&0xFF;
		right_ix=left_ix+len;

//		return right_ix;


//DeadCode JON 4Sep00 		for (int i=3;i>=0;i--)
//DeadCode JON 4Sep00 		{
//DeadCode JON 4Sep00 			if (xx[i]<0)		xx[i]=0;
//DeadCode JON 4Sep00 			else if (xx[i]>256)	xx[i]=256;
//DeadCode JON 4Sep00 			if (yy[i]<0)		yy[i]=0;
//DeadCode JON 4Sep00 			else if (yy[i]>256)	yy[i]=256;
//DeadCode JON 4Sep00 		}

		Lib3DPoint *pRVert = g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(BLENDMAPNO)),4);

		pRVert->setPosition( xx[0], yy[0], 0.f );
		pRVert->setIMapCoords( left_ix, shift );
		pRVert++;

		pRVert->setPosition( xx[1], yy[1], 0.f );
		pRVert->setIMapCoords( right_ix, shift );
		pRVert++;

		pRVert->setPosition( xx[2], yy[2], 0.f );
		pRVert->setIMapCoords( right_ix, 8+shift );
		pRVert++;

		pRVert->setPosition( xx[3], yy[3], 0.f );
		pRVert->setIMapCoords( left_ix, 8+shift );

		g_lpLib3d->EndPoly();
		
//DEADCODE JON 5/23/00 		R3DVERTEX *pRVert;
//DEADCODE JON 5/23/00 		g_lpLib3d->BeginPoly(HMATERIAL(Image_Map.GetImageMapPtr(BLENDMAPNO)),4,pRVert);
//DEADCODE JON 5/23/00 		pRVert->ix=left_ix;
//DEADCODE JON 5/23/00 		pRVert->iy=shift;
//DEADCODE JON 5/23/00 		pRVert->bodyx.f=R3DVALUE(xx[0]);//*DIV_SCALE;
//DEADCODE JON 5/23/00 		pRVert->bodyy.f=R3DVALUE(yy[0]);//*DIV_SCALE;
//DEADCODE JON 5/23/00 //DEADCODE JON 4/13/00 		pRVert->bodyz.f=1;
//DEADCODE JON 5/23/00 		pRVert++;
//DEADCODE JON 5/23/00 		pRVert->ix=right_ix;
//DEADCODE JON 5/23/00 		pRVert->iy=shift;
//DEADCODE JON 5/23/00 		pRVert->bodyx.f=R3DVALUE(xx[1]);//*DIV_SCALE;
//DEADCODE JON 5/23/00 		pRVert->bodyy.f=R3DVALUE(yy[1]);//*DIV_SCALE;
//DEADCODE JON 5/23/00 //DEADCODE JON 4/13/00 		pRVert->bodyz.f=1;
//DEADCODE JON 5/23/00 		pRVert++;
//DEADCODE JON 5/23/00 		pRVert->ix=right_ix;
//DEADCODE JON 5/23/00 		pRVert->iy=8+shift;
//DEADCODE JON 5/23/00 		pRVert->bodyx.f=R3DVALUE(xx[2]);//*DIV_SCALE;
//DEADCODE JON 5/23/00 		pRVert->bodyy.f=R3DVALUE(yy[2]);//*DIV_SCALE;
//DEADCODE JON 5/23/00 //DEADCODE JON 4/13/00 		pRVert->bodyz.f=1;
//DEADCODE JON 5/23/00 		pRVert++;
//DEADCODE JON 5/23/00 		pRVert->ix=left_ix;
//DEADCODE JON 5/23/00 		pRVert->iy=8+shift;
//DEADCODE JON 5/23/00 		pRVert->bodyx.f=R3DVALUE(xx[3]);//*DIV_SCALE;
//DEADCODE JON 5/23/00 		pRVert->bodyy.f=R3DVALUE(yy[3]);//*DIV_SCALE;
//DEADCODE JON 5/23/00 //DEADCODE JON 4/13/00 		pRVert->bodyz.f=1;
//DEADCODE JON 5/23/00 		g_lpLib3d->EndPoly();
	}
	return right_ix;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Render2Surface
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------

static ULong DebugRecs[256*256];


inline bool HasSheep(UByte at)
{
	if ( at<RT_Lowest )
	{
		ULong at_shift = 1UL<<(at&AT_MASK);
		const ULong at_shift_mask =
					(1UL<<(AT_spread1)) |
					(1UL<<(AT_spread2)) |
					(1UL<<(AT_spread3)) |
					(1UL<<(AT_spread4)) |
					(1UL<<(AT_spread5)) |
					(1UL<<(AT_rough)) |
					(1UL<<(AT_roughGrass)) |
					(1UL<<(AT_patchyGrass));
		return ( (at_shift&at_shift_mask) != 0 );
	} else return false;
}
inline bool HasCows(UByte at)
{
	if ( at<RT_Lowest )
	{
		ULong at_shift = 1UL<<(at&AT_MASK);
		const ULong at_shift_mask =
//DeadCode JON 24Oct00 					(1UL<<(AT_golfCourse)) |
//DeadCode JON 24Oct00 					(1UL<<(AT_garden)) |
					(1UL<<(AT_midGrass)) |
					(1UL<<(AT_darkGrass));
		return ( (at_shift&at_shift_mask) != 0 );
	} else return false;

}
inline bool HasHayStacks(UByte at)
{
	if ( at<RT_Lowest )
	{
		ULong at_shift = 1UL<<(at&AT_MASK);
		const ULong at_shift_mask =
					(1UL<<(AT_field1)) |
					(1UL<<(AT_field2));
		return ( (at_shift&at_shift_mask) != 0 );
	} else return false;
}

//#pragma warnmsg ( "inline me" )
inline void Render2Surface(const HTEXT& hTexture,UByte rezTexture,UWord offset)
{
	
	SLong dgi=MakeDataGridIndex(offset);

	DataRecord& currentData=gridRecords[dgi];
	UByte* pdata=Three_Dee.pMigLand->MakeIData(currentData,0);//rezTexture>>1);	
//DeadCode JON 18Oct00 	UByte* pdata=Three_Dee.pMigLand->MakeIData(gridRecords[dgi],0);//rezTexture>>1);	
//DeadCode JON 18Oct00 	currentShadowRec=shadowRecords[dgi];

//	D3DVECTOR tv={-.1f,-.1f,0.f};
//	D3DVECTOR preTrans={.5f,.5f,0.f };
	static D3DVECTOR preTrans={-0.49f,0.49f,0.f };
//	static D3DVECTOR preScale={(255.f/256.f),(255.f/256.f),1.f};
	D3DVECTOR tv={-.5f,-.5f,0.f};
	D3DVECTOR sf={2.f,2.f,1.f};

	g_lpLib3d->BeginScene( HRENDERTARGET( RENDERTARGET_LANDSCAPE, UWord(hTexture.textureHandle) ) );
//	g_lpLib3d->PushMatrix(MATRIX_OBJECT);
//	g_lpLib3d->PushMatrix(MATRIX_VIEWER);
//	g_lpLib3d->PushMatrix(MATRIX_PROJECTION);
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

//	g_lpLib3d->Scale(MATRIX_OBJECT,preScale);
	g_lpLib3d->Translate(MATRIX_OBJECT,preTrans);
	g_lpLib3d->Scale(MATRIX_OBJECT,(DIV_SCALE));  // this could be optimised to make a constant matrix
	g_lpLib3d->Translate(MATRIX_OBJECT,tv);		// to be set to....
	g_lpLib3d->Scale(MATRIX_OBJECT,sf);

	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
	g_lpLib3d->LoadIdentity(MATRIX_PROJECTION); 

	g_lpLib3d->GiveHint( HINT_2DRENDER );

	g_lpLib3d->SetGlobal( TOGGLE_GLOBAL2DZDEPTH, 5 );
	
	AltPointsHdr*	aph;
	DrawDataHdr*	ddh;

	aph=(AltPointsHdr*)pdata;

	if (rezTexture<4)
	{
		SLong vc=aph->vertexCount-1;
		for (SLong h=vc;h>=0;h--)
			for (SLong w=vc,hi=h<<8;w>=0;w--) DebugRecs[hi++]=0UL;
	}

	SWord edge_points=aph->leftEdgePoints+aph->rightEdgePoints+aph->topEdgePoints+aph->bottomEdgePoints+4;

	pdata+=sizeof(AltPointsHdr);

	pointdef=(PointDef*)pdata;

//TEMPCODE JON 5/26/00 	// right copy the pointdefs into the point buffer					//JON 5/26/00
//TEMPCODE JON 5/26/00 	DoPointStruc* pPoint = SHAPE.newco;
//TEMPCODE JON 5/26/00 	for ( int i=vertexCoint; i!=0; i-- )
//TEMPCODE JON 5/26/00 	{
//TEMPCODE JON 5/26/00 		*pPoint->setPosition( pointdef->x, 256-pointdef->z );
//TEMPCODE JON 5/26/00 		pPoint++;
//TEMPCODE JON 5/26/00 		pointdef++;
//TEMPCODE JON 5/26/00 	}
//TEMPCODE JON 5/26/00 	pPoint = SHAPE.newco;
//TEMPCODE JON 5/26/00 	pointdef=(PointDef*)pdata;

	pdata+=aph->vertexCount*sizeof(PointDef);

	ddh=(DrawDataHdr*)pdata;
	pdata+=sizeof(DrawDataHdr);

	SWord primCount=ddh->noOfPolys;

	UByte *savedata=pdata;

//#define DO_TEST_TILE
#ifdef DO_TEST_TILE
	Lib3DPoint *pRVert = g_lpLib3d->BeginFan( HMATERIAL(imagePtrs[2]),4);
	for ( int v = 0; v<4; v++ )
	{
		pRVert->setIMapCoords( pointdef[v].x, 256-pointdef[v].z );
		pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
		pRVert++;

	}
	g_lpLib3d->EndFan();
#else
	while (primCount--)
	{
		ULong at,atMask;
		int rotation;
		at=*pdata;
		HMATERIAL hMat;
//TempCode JON 25Oct00 		rotation = AT_ROT0;
//TempCode JON 25Oct00 		if ( HasSheep(at) )
//TempCode JON 25Oct00 		{
//TempCode JON 25Oct00 			at&=AT_MASK;
//TempCode JON 25Oct00 			hMat = HMATERIAL( 120 );//red
//TempCode JON 25Oct00 		} else if ( HasCows( at ) )
//TempCode JON 25Oct00 		{
//TempCode JON 25Oct00 			at&=AT_MASK;
//TempCode JON 25Oct00 			hMat = HMATERIAL( 191 );//green
//TempCode JON 25Oct00 		} else if ( HasHayStacks( at ) )
//TempCode JON 25Oct00 		{
//TempCode JON 25Oct00 			at&=AT_MASK;
//TempCode JON 25Oct00 			hMat = HMATERIAL( 144 );//blue
//TempCode JON 25Oct00 		} else 
//TempCode JON 25Oct00 		{
//TempCode JON 25Oct00 			at&=AT_MASK;
//TempCode JON 25Oct00 			hMat = HMATERIAL( 159 );//white
//TempCode JON 25Oct00 		}
		// now check to see if the areatype 4 this is one of the widened routes types
		if ( at<RT_Lowest )
		{ // it isn't
			rotation = (at|AT_MASK);
			at&=AT_MASK;
			hMat=HMATERIAL(imagePtrs[at]);
		} else {
			UByte ra = at - RT_Lowest;
			ra&=AT_ROT0;
			rotation = AT_ROT0;
			switch ( ra )
			{
				// road types
				case RA_AROAD:
				case RA_BROAD:
				case RA_ROADJUNCTION:
				case RA_CROSSING3:
				case RA_RIVAROADJUNCT:
				case RA_RIVBROADJUNCT:
					g_lpLib3d->SetFontColour( 0x424242 ); //grey
					hMat=HMATERIAL( 8 ); // grey
				break;
				// rail types
				case RA_MAJORRAIL:
				case RA_MINORRAIL:
				case RA_RAILJUNCTION:
				case RA_MAJRAILROADJUNCT:
				case RA_MINRAILROADJUNCT:
				case RA_CROSSING1:
				case RA_CROSSING2:
				case RA_CROSSING4:
				case RA_RIVMINRAILJUNCT:
				case RA_RIVMAJRAILJUNCT:
					g_lpLib3d->SetFontColour( 0x3C3C2C );
					hMat=HMATERIAL( 47 ); // GREY/BROWN
				break;
				//river types
				case RA_MAJORRIVER:
				case RA_MINORRIVER:
					g_lpLib3d->SetFontColour( 0x192942 );
					hMat=HMATERIAL( 131 ); // grey/blue
				break;
				default:
//					g_lpLib3d->SetFontColour( 0xFF0000 );
//					hMat=HMATERIAL( 120 ); // red
					at = AT_midGrass;
					hMat=HMATERIAL(imagePtrs[at]);
				break;
			}
			at=AT_cityBase;
		}
		atMask=1<<at;
		pdata++;

		UByte fanCount=*pdata++;

		hMat.isMasked = MSK_NONE;  // shouldn't be needed but city types seem to want...

//		rotation = AT_ROT0;
		switch (rotation)
		{
		case AT_ROT0:
			while (fanCount--)
			{
				ULong triCount=2+*pdata++;
				Lib3DPoint *pRVert = g_lpLib3d->BeginFan(hMat,triCount);

				SWord v,last_v,first_v;
				v=first_v=*pdata++;
				triCount--;

				pRVert->setIMapCoords( pointdef[v].x, 256-pointdef[v].z );
				if ( IsHirez(at) )
					pRVert->setIMapCoords( pRVert->getIMapX()<<1, pRVert->getIMapY()<<1 );
				pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
				pRVert++;
				while (triCount--)
				{
					last_v=v;
					v=*pdata++;
					if (v>=edge_points || last_v>=edge_points)
					{
						DebugRecs[(v<<8)+last_v]|=atMask;
						DebugRecs[(last_v<<8)+v]|=atMask;
					}

					pRVert->setIMapCoords( pointdef[v].x, 256-pointdef[v].z );
					if ( IsHirez(at) )
						pRVert->setIMapCoords( pRVert->getIMapX()<<1, pRVert->getIMapY()<<1 );
					pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
					pRVert++;
				}

				g_lpLib3d->EndFan();

				if (v>=edge_points || first_v>=edge_points)
				{
					DebugRecs[(v<<8)+first_v]|=atMask;
					DebugRecs[(first_v<<8)+v]|=atMask;
				}
			}
			break;
		case AT_ROT1:
			while (fanCount--)
			{
				ULong triCount=2+*pdata++;
				Lib3DPoint *pRVert = g_lpLib3d->BeginFan(hMat,triCount);

				SWord v,last_v,first_v;
				v=first_v=*pdata++;
				triCount--;
				pRVert->setIMapCoords( 256-pointdef[v].z, 256-pointdef[v].x );
				if ( IsHirez(at) )
					pRVert->setIMapCoords( pRVert->getIMapX()<<1, pRVert->getIMapY()<<1 );
				pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
				pRVert++;
				while (triCount--)
				{
					last_v=v;
					v=*pdata++;
					if (v>=edge_points || last_v>=edge_points)
					{
						DebugRecs[(v<<8)+last_v]|=atMask;
						DebugRecs[(last_v<<8)+v]|=atMask;
					}
					pRVert->setIMapCoords( 256-pointdef[v].z, 256-pointdef[v].x );
					if ( IsHirez(at) )
						pRVert->setIMapCoords( pRVert->getIMapX()<<1, pRVert->getIMapY()<<1 );
					pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
					pRVert++;
				}
				g_lpLib3d->EndFan();
				if (v>=edge_points || first_v>=edge_points)
				{
					DebugRecs[(v<<8)+first_v]|=atMask;
					DebugRecs[(first_v<<8)+v]|=atMask;
				}
			}
			break;
		case AT_ROT2:
			while (fanCount--)
			{
				ULong triCount=2+*pdata++;
				Lib3DPoint *pRVert = g_lpLib3d->BeginFan(hMat,triCount);

				SWord v,last_v,first_v;
				v=first_v=*pdata++;
				triCount--;
				pRVert->setIMapCoords( 256-pointdef[v].x, pointdef[v].z );
				if ( IsHirez(at) )
					pRVert->setIMapCoords( pRVert->getIMapX()<<1, pRVert->getIMapY()<<1 );
				pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
				pRVert++;
				while (triCount--)
				{
					last_v=v;
					v=*pdata++;
					if (v>=edge_points || last_v>=edge_points)
					{
						DebugRecs[(v<<8)+last_v]|=atMask;
						DebugRecs[(last_v<<8)+v]|=atMask;
					}
					pRVert->setIMapCoords( 256-pointdef[v].x, pointdef[v].z );
					if ( IsHirez(at) )
						pRVert->setIMapCoords( pRVert->getIMapX()<<1, pRVert->getIMapY()<<1 );
					pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
					pRVert++;
				}
				g_lpLib3d->EndFan();

				if (v>=edge_points || first_v>=edge_points)
				{
					DebugRecs[(v<<8)+first_v]|=atMask;
					DebugRecs[(first_v<<8)+v]|=atMask;
				}
			}
			break;
		case AT_ROT3:
			while (fanCount--)
			{
				ULong triCount=2+*pdata++;
				Lib3DPoint *pRVert = g_lpLib3d->BeginFan(hMat,triCount);

				SWord v,last_v,first_v;
				v=first_v=*pdata++;
				triCount--;
				pRVert->setIMapCoords( pointdef[v].x, pointdef[v].z );
				if ( IsHirez(at) )
					pRVert->setIMapCoords( pRVert->getIMapX()<<1, pRVert->getIMapY()<<1 );
				pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
				pRVert++;
				while (triCount--)
				{
					last_v=v;
					v=*pdata++;
					if (v>=edge_points || last_v>=edge_points)
					{
						DebugRecs[(v<<8)+last_v]|=atMask;
						DebugRecs[(last_v<<8)+v]|=atMask;
					}
					pRVert->setIMapCoords( pointdef[v].x, pointdef[v].z );
					if ( IsHirez(at) )
						pRVert->setIMapCoords( pRVert->getIMapX()<<1, pRVert->getIMapY()<<1 );
					pRVert->setPosition( pointdef[v].x, 256-pointdef[v].z, 0.f );
					pRVert++;
				}
				g_lpLib3d->EndFan();
				if (v>=edge_points || first_v>=edge_points)
				{
					DebugRecs[(v<<8)+first_v]|=atMask;
					DebugRecs[(first_v<<8)+v]|=atMask;
				}
			}
			break;
			NODEFAULT;
		}

//DEADCODE JON 5/23/00 		switch (rotation)
//DEADCODE JON 5/23/00 		{
//DEADCODE JON 5/23/00 		case AT_ROT0:
//DEADCODE JON 5/23/00 			while (fanCount--)
//DEADCODE JON 5/23/00 			{
//DEADCODE JON 5/23/00 				R3DVERTEX *pRVert;
//DEADCODE JON 5/23/00 				ULong triCount=2+*pdata++;
//DEADCODE JON 5/23/00 				g_lpLib3d->BeginFan(hMat,triCount,pRVert);
//DEADCODE JON 5/23/00 
//DEADCODE JON 5/23/00 				SWord v,last_v,first_v;
//DEADCODE JON 5/23/00 				v=first_v=*pdata++;
//DEADCODE JON 5/23/00 				triCount--;
//DEADCODE JON 5/23/00 				pRVert->ix=pointdef[v].x;
//DEADCODE JON 5/23/00 				pRVert->iy=256-pointdef[v].z;
//DEADCODE JON 5/23/00 				pRVert->bodyx.f=R3DVALUE(pRVert->ix);
//DEADCODE JON 5/23/00 				pRVert->bodyy.f=R3DVALUE(pRVert->iy);
//DEADCODE JON 5/23/00 				pRVert++;
//DEADCODE JON 5/23/00 				while (triCount--)
//DEADCODE JON 5/23/00 				{
//DEADCODE JON 5/23/00 					last_v=v;
//DEADCODE JON 5/23/00 					v=*pdata++;
//DEADCODE JON 5/23/00 					if (v>=edge_points || last_v>=edge_points)
//DEADCODE JON 5/23/00 					{
//DEADCODE JON 5/23/00 						DebugRecs[(v<<8)+last_v]|=atMask;
//DEADCODE JON 5/23/00 						DebugRecs[(last_v<<8)+v]|=atMask;
//DEADCODE JON 5/23/00 					}
//DEADCODE JON 5/23/00 					pRVert->ix=pointdef[v].x;
//DEADCODE JON 5/23/00 					pRVert->iy=256-pointdef[v].z;
//DEADCODE JON 5/23/00 					pRVert->bodyx.f=R3DVALUE(pRVert->ix);
//DEADCODE JON 5/23/00 					pRVert->bodyy.f=R3DVALUE(pRVert->iy);
//DEADCODE JON 5/23/00 					pRVert++;
//DEADCODE JON 5/23/00 				}
//DEADCODE JON 5/23/00 				if (v>=edge_points || first_v>=edge_points)
//DEADCODE JON 5/23/00 				{
//DEADCODE JON 5/23/00 					DebugRecs[(v<<8)+first_v]|=atMask;
//DEADCODE JON 5/23/00 					DebugRecs[(first_v<<8)+v]|=atMask;
//DEADCODE JON 5/23/00 				}
//DEADCODE JON 5/23/00 				g_lpLib3d->EndFan();
//DEADCODE JON 5/23/00 			}
//DEADCODE JON 5/23/00 			break;
//DEADCODE JON 5/23/00 		case AT_ROT1:
//DEADCODE JON 5/23/00 			while (fanCount--)
//DEADCODE JON 5/23/00 			{
//DEADCODE JON 5/23/00 				R3DVERTEX *pRVert;
//DEADCODE JON 5/23/00 				ULong triCount=2+*pdata++;
//DEADCODE JON 5/23/00 				g_lpLib3d->BeginFan(hMat,triCount,pRVert);
//DEADCODE JON 5/23/00 
//DEADCODE JON 5/23/00 				SWord v,last_v,first_v;
//DEADCODE JON 5/23/00 				v=first_v=*pdata++;
//DEADCODE JON 5/23/00 				triCount--;
//DEADCODE JON 5/23/00 				pRVert->ix=256-pointdef[v].z;
//DEADCODE JON 5/23/00 				pRVert->iy=256-pointdef[v].x;
//DEADCODE JON 5/23/00 				pRVert->bodyx.f=R3DVALUE(pointdef[v].x);
//DEADCODE JON 5/23/00 				pRVert->bodyy.f=R3DVALUE(256-pointdef[v].z);
//DEADCODE JON 5/23/00 				pRVert++;
//DEADCODE JON 5/23/00 				while (triCount--)
//DEADCODE JON 5/23/00 				{
//DEADCODE JON 5/23/00 					last_v=v;
//DEADCODE JON 5/23/00 					v=*pdata++;
//DEADCODE JON 5/23/00 					if (v>=edge_points || last_v>=edge_points)
//DEADCODE JON 5/23/00 					{
//DEADCODE JON 5/23/00 						DebugRecs[(v<<8)+last_v]|=atMask;
//DEADCODE JON 5/23/00 						DebugRecs[(last_v<<8)+v]|=atMask;
//DEADCODE JON 5/23/00 					}
//DEADCODE JON 5/23/00 					pRVert->ix=256-pointdef[v].z;
//DEADCODE JON 5/23/00 					pRVert->iy=256-pointdef[v].x;
//DEADCODE JON 5/23/00 					pRVert->bodyx.f=R3DVALUE(pointdef[v].x);
//DEADCODE JON 5/23/00 					pRVert->bodyy.f=R3DVALUE(256-pointdef[v].z);
//DEADCODE JON 5/23/00 					pRVert++;
//DEADCODE JON 5/23/00 				}
//DEADCODE JON 5/23/00 				if (v>=edge_points || first_v>=edge_points)
//DEADCODE JON 5/23/00 				{
//DEADCODE JON 5/23/00 					DebugRecs[(v<<8)+first_v]|=atMask;
//DEADCODE JON 5/23/00 					DebugRecs[(first_v<<8)+v]|=atMask;
//DEADCODE JON 5/23/00 				}
//DEADCODE JON 5/23/00 				g_lpLib3d->EndFan();
//DEADCODE JON 5/23/00 			}
//DEADCODE JON 5/23/00 			break;
//DEADCODE JON 5/23/00 		case AT_ROT2:
//DEADCODE JON 5/23/00 			while (fanCount--)
//DEADCODE JON 5/23/00 			{
//DEADCODE JON 5/23/00 				R3DVERTEX *pRVert;
//DEADCODE JON 5/23/00 				ULong triCount=2+*pdata++;
//DEADCODE JON 5/23/00 				g_lpLib3d->BeginFan(hMat,triCount,pRVert);
//DEADCODE JON 5/23/00 
//DEADCODE JON 5/23/00 				SWord v,last_v,first_v;
//DEADCODE JON 5/23/00 				v=first_v=*pdata++;
//DEADCODE JON 5/23/00 				triCount--;
//DEADCODE JON 5/23/00 				pRVert->ix=256-pointdef[v].x;
//DEADCODE JON 5/23/00 				pRVert->iy=pointdef[v].z;
//DEADCODE JON 5/23/00 				pRVert->bodyx.f=R3DVALUE(pointdef[v].x);
//DEADCODE JON 5/23/00 				pRVert->bodyy.f=R3DVALUE(256-pointdef[v].z);
//DEADCODE JON 5/23/00 				pRVert++;
//DEADCODE JON 5/23/00 				while (triCount--)
//DEADCODE JON 5/23/00 				{
//DEADCODE JON 5/23/00 					last_v=v;
//DEADCODE JON 5/23/00 					v=*pdata++;
//DEADCODE JON 5/23/00 					if (v>=edge_points || last_v>=edge_points)
//DEADCODE JON 5/23/00 					{
//DEADCODE JON 5/23/00 						DebugRecs[(v<<8)+last_v]|=atMask;
//DEADCODE JON 5/23/00 						DebugRecs[(last_v<<8)+v]|=atMask;
//DEADCODE JON 5/23/00 					}
//DEADCODE JON 5/23/00 					pRVert->ix=256-pointdef[v].x;
//DEADCODE JON 5/23/00 					pRVert->iy=pointdef[v].z;
//DEADCODE JON 5/23/00 					pRVert->bodyx.f=R3DVALUE(pointdef[v].x);
//DEADCODE JON 5/23/00 					pRVert->bodyy.f=R3DVALUE(256-pointdef[v].z);
//DEADCODE JON 5/23/00 					pRVert++;
//DEADCODE JON 5/23/00 				}
//DEADCODE JON 5/23/00 				if (v>=edge_points || first_v>=edge_points)
//DEADCODE JON 5/23/00 				{
//DEADCODE JON 5/23/00 					DebugRecs[(v<<8)+first_v]|=atMask;
//DEADCODE JON 5/23/00 					DebugRecs[(first_v<<8)+v]|=atMask;
//DEADCODE JON 5/23/00 				}
//DEADCODE JON 5/23/00 				g_lpLib3d->EndFan();
//DEADCODE JON 5/23/00 			}
//DEADCODE JON 5/23/00 			break;
//DEADCODE JON 5/23/00 		case AT_ROT3:
//DEADCODE JON 5/23/00 			while (fanCount--)
//DEADCODE JON 5/23/00 			{
//DEADCODE JON 5/23/00 				R3DVERTEX *pRVert;
//DEADCODE JON 5/23/00 				ULong triCount=2+*pdata++;
//DEADCODE JON 5/23/00 				g_lpLib3d->BeginFan(hMat,triCount,pRVert);
//DEADCODE JON 5/23/00 
//DEADCODE JON 5/23/00 				SWord v,last_v,first_v;
//DEADCODE JON 5/23/00 				v=first_v=*pdata++;
//DEADCODE JON 5/23/00 				triCount--;
//DEADCODE JON 5/23/00 				pRVert->ix=pointdef[v].z;
//DEADCODE JON 5/23/00 				pRVert->iy=pointdef[v].x;
//DEADCODE JON 5/23/00 				pRVert->bodyx.f=R3DVALUE(pointdef[v].x);
//DEADCODE JON 5/23/00 				pRVert->bodyy.f=R3DVALUE(256-pointdef[v].z);
//DEADCODE JON 5/23/00 				pRVert++;
//DEADCODE JON 5/23/00 				while (triCount--)
//DEADCODE JON 5/23/00 				{
//DEADCODE JON 5/23/00 					last_v=v;
//DEADCODE JON 5/23/00 					v=*pdata++;
//DEADCODE JON 5/23/00 					if (v>=edge_points || last_v>=edge_points)
//DEADCODE JON 5/23/00 					{
//DEADCODE JON 5/23/00 						DebugRecs[(v<<8)+last_v]|=atMask;
//DEADCODE JON 5/23/00 						DebugRecs[(last_v<<8)+v]|=atMask;
//DEADCODE JON 5/23/00 					}
//DEADCODE JON 5/23/00 					pRVert->ix=pointdef[v].z;
//DEADCODE JON 5/23/00 					pRVert->iy=pointdef[v].x;
//DEADCODE JON 5/23/00 					pRVert->bodyx.f=R3DVALUE(pointdef[v].x);
//DEADCODE JON 5/23/00 					pRVert->bodyy.f=R3DVALUE(256-pointdef[v].z);
//DEADCODE JON 5/23/00 					pRVert++;
//DEADCODE JON 5/23/00 				}
//DEADCODE JON 5/23/00 				if (v>=edge_points || first_v>=edge_points)
//DEADCODE JON 5/23/00 				{
//DEADCODE JON 5/23/00 					DebugRecs[(v<<8)+first_v]|=atMask;
//DEADCODE JON 5/23/00 					DebugRecs[(first_v<<8)+v]|=atMask;
//DEADCODE JON 5/23/00 				}
//DEADCODE JON 5/23/00 				g_lpLib3d->EndFan();
//DEADCODE JON 5/23/00 			}
//DEADCODE JON 5/23/00 			break;
//DEADCODE JON 5/23/00 		default:
//DEADCODE JON 5/23/00 			INT3;
//DEADCODE JON 5/23/00 			break;
//DEADCODE JON 5/23/00 		}
	}

	g_lpLib3d->SetGlobal( TOGGLE_GLOBAL2DZDEPTH, 4 );

	// draw in routes
//TempCode JON 25Aug00 	g_lpLib3d->GiveHint( HINT_CLIPPING_ON );						//JON 25Aug00

	primCount=(rezTexture<4 && Save_Data.detail_3d[DETAIL3D_ROUTES])?ddh->noOfLines:0;

//	g_lpLib3d->ClearTargetZ();
	while (primCount--)
	{
		UByte lineCol(0);
		SWord shift;

		switch (*pdata++)
		{
		case RT_Cliff:
			shift=SHIFT_CliffTopBaseBlend;
			break;
		case RT_AirField:
			shift=SHIFT_AirFieldRT;
			break;
		case RT_MajorRiver:
			shift=SHIFT_MajorRiver;
			break;
		case RT_MinorRiver:
			shift=SHIFT_MinorRiver;
			break;
		case RT_Tributary:
			shift=SHIFT_Tributary;
			break;
		case RT_MinorRoad:
			shift=SHIFT_MinorRoad;
			break;
		case RT_Footpath:
			shift=SHIFT_FootPath;
			break;
		case RT_MajorRail:
			shift=SHIFT_MajorRail;
			break;
		case RT_MinorRail:
			shift=SHIFT_MinorRail;
			break;
		case RT_ARoad:
			shift=SHIFT_ARoad;
			break;
		case RT_BRoad:
			shift=SHIFT_BRoad;
			break;
		case RT_HedgerowThick:
		case RT_HedgerowThin:
			shift=SHIFT_BlendGrassOther;
			break;
		default:
			{
				lineCol=ARTWORKMASK;
				UByte sectionCount=*pdata++;
				pdata+=sectionCount;
				continue;
			}
			break;
		}

		UByte sectionCount=*pdata++;

//DeadCode JON 2Oct00 		if (lineCol==ARTWORKMASK)
//DeadCode JON 2Oct00 			pdata+=sectionCount;
//DeadCode JON 2Oct00 		else
		{
			SWord v,last_v;
			SWord right_ix=0;
			v=*pdata++;
			SLong x2,y2;
			x2=pointdef[v].x;
			y2=256-pointdef[v].z;
			while (--sectionCount!=0)
			{
				SLong x1,y1;
				x1=x2;
				y1=y2;
				last_v=v;
				v=*pdata++;
				DebugRecs[(v<<8)+last_v]=
				DebugRecs[(last_v<<8)+v]=0UL;
				x2=pointdef[v].x;
				y2=256-pointdef[v].z;
				right_ix=RenderEdgeStrip(x1,y1,x2,y2,right_ix,shift);
			}
		}
	}


	g_lpLib3d->SetGlobal( TOGGLE_GLOBAL2DZDEPTH, 3 );

	// draw in the edge anitaliasing
	primCount=rezTexture<4?ddh->noOfPolys:0;
	const ULong grassyMask=	
							(1<<AT_darkGrass)+
							(1<<AT_midGrass)+
							(1<<AT_lightGrass)+
							(1<<AT_garden)+
							(1<<AT_golfCourse)+
							(1<<AT_field1)+
							(1<<AT_field2)+
							(1<<AT_field3)+
							(1<<AT_field4)+
							(1<<AT_field5)+
							(1<<AT_spread1)+
							(1<<AT_spread2)+
							(1<<AT_spread3)+
							(1<<AT_spread4)+
							(1<<AT_spread5)+
							(1<<AT_swamp)+
							(1<<AT_rough)+
							(1<<AT_roughGrass)+
							(1<<AT_patchyGrass);	
	const ULong grassMask=
							(1<<AT_darkGrass)+
							(1<<AT_midGrass)+
							(1<<AT_lightGrass)+
							(1<<AT_garden)+
							(1<<AT_golfCourse);							//JON 2Oct00
	
	while (primCount--)
	{
		ULong at,atMask;
		at=*savedata;
		if ( at<RT_Lowest )
		{
			at&=0x1F;
		} else
		{
			at=AT_cityBase;
		}
		atMask=1<<at;
		savedata++;
		UByte fanCount=*savedata++;

		SWord right_ix=0;
		
		while (fanCount--)
		{
			R3DVERTEX *pRVert;
			ULong triCount=2+*savedata++;
			
			for (int this_i=0;this_i<triCount;this_i++)
			{
				int next_i=this_i+1;
				if (next_i==triCount) next_i=0;

				int last_v=savedata[this_i];
				int next_v=savedata[next_i];

				ULong mask=DebugRecs[(next_v<<8)+last_v];

				//only consider edge if both of the points are connected to something other than the
				//current material
				//also don't consider the edge if a route is already running along the edge
				if (mask!=0)
				{
					SWord shift=0;

/*					if ( IsPointCliff[last_v] && isPointCliff[next_v] && IsCliffBottom( at )  )
					{ // cliff antialising here

					} else */ if (at==AT_sea)
					{
						if ((mask&(1<<AT_sand))!=0)
							shift=SHIFT_BlendSeaBeach;
						else if ((mask&~(1<<AT_sea))!=0)
							shift=SHIFT_BlendSeaLand;
					}
					else if ((grassyMask&atMask)!=0)
					{
						if (
							 (((mask&~atMask)&grassyMask)!=0) && // are they of different types?
							 ((mask&(~grassMask)) || (atMask&(~grassMask)) ) //one of them isn't plain grass(for airfields, ta guys) 
							)
							shift=SHIFT_BlendGrassOther;
					}
					if (shift)
					{
						DebugRecs[(next_v<<8)+last_v]=
							DebugRecs[(last_v<<8)+next_v]=0UL;
						SLong x2,y2;
						x2=pointdef[last_v].x;
						y2=256-pointdef[last_v].z;
						SLong x1,y1;
						x1=x2;
						y1=y2;
						x2=pointdef[next_v].x;
						y2=256-pointdef[next_v].z;
						right_ix=RenderEdgeStrip(x1,y1,x2,y2,right_ix,shift);
					}
				}
			}
			savedata+=triCount;
		}
	}

	//check for shadow rendering to this tile
	if (rezTexture<3 && Save_Data.detail_3d[DETAIL3D_ITEMSHADOWS])
	{
		g_lpLib3d->SetGlobal( TOGGLE_GLOBAL2DZDEPTH, 2 );
 		g_lpLib3d->SetGlobal( TOGGLE_GLOBALALPHA, 100 );
//DeadCode CSB 19Oct00 		g_lpLib3d->SetFontColour( 0x101010 );

// Set up shadow info...

		LIGHTFLAG	useLightFlag = LF_VERTEX;							//RJS 19Oct00
		g_lpLib3d->SetObjectLighting(useLightFlag);

		shadColourNear = (shadColour & 0xFFFFFF) | (shadNearAlpha << 24);
		shadColourFar = (shadColour & 0xFFFFFF) | (shadFarAlpha << 24);

		//currentData contains world coordinates for sector search
		item dummyItem,*itemPtr;
		UWord sec_x,sec_y;
		dummyItem.World.X=currentData.x+(Grid_Width>>1);
		dummyItem.World.Z=currentData.z+(Grid_Width>>1);
//DeadCode JON 18Oct00 		dummyItem.World.X=currentShadowRec.world_x+(Grid_Width>>1);
//DeadCode JON 18Oct00 		dummyItem.World.Z=currentShadowRec.world_z+(Grid_Width>>1);
		worldPtr->getsectornos(&dummyItem,sec_x,sec_y);
		ULong sec_index=worldPtr->makeindex(sec_x,sec_y);
		itemPtr=worldPtr->getfirstitem(sec_index);

		while (itemPtr)
		{
			const SLong gridSx=currentData.x;
			const SLong gridSz=currentData.z;
//DeadCode JON 18Oct00 			const SLong gridSx=currentShadowRec.world_x;
//DeadCode JON 18Oct00 			const SLong gridSz=currentShadowRec.world_z;
			const SLong gridEx=gridSx+Grid_Width;
			const SLong gridEz=gridSz+Grid_Width;
			const SLong world2Pix=9;	//+scale;

		 	if (itemPtr->Status.size<=RotatedSize)
			{
				ShapeDescPtr shapePtr=SHAPESTUFF.GetShapePtr(itemPtr->shape);

				if (SHAPESTUFF.GetShapeScale(shapePtr)==SHP_GRP)
				{
					if (groupHasShadow(itemPtr->shape))
					{
						UByte* inst_ptr=(UByte*)shapePtr+shapePtr->liveshpref;

						for (SWord inst=*inst_ptr++;inst==dogroupno;inst=*inst_ptr++)
						{
							DOGROUP_PTR gptr=(DOGROUP_PTR)inst_ptr;

							SLong cx=itemPtr->World.X+gptr->xoffset;
							SLong cz=itemPtr->World.Z+gptr->zoffset;

							if (cx>gridSx && cx<gridEx && cz>gridSz && cz<gridEz && shapeHasShadow((ShapeNum)gptr->shapenum))
							{
								SWord hdg=gptr->angle;
								cx=(cx-gridSx)>>world2Pix;
								cz=(cz-gridSz)>>world2Pix;

								ShapeDescPtr groupPtr=SHAPESTUFF.GetShapePtr((ShapeNum)gptr->shapenum);

//DEADCODE JON 4/14/00 								if (hdg==0)	RenderShadow(g_lpLib3d,groupPtr,cx,cz,rezTexture);
//DEADCODE JON 4/14/00 								else   		RenderShadowRotated(g_lpLib3d,groupPtr,cx,cz,hdg,rezTexture);
								RenderObjectShadow(g_lpLib3d,groupPtr,cx,cz,hdg);
							}
							inst_ptr+=sizeof(DOGROUP);
						}
					}
				}
				else if (	itemPtr->World.X>gridSx &&
							itemPtr->World.X<gridEx &&
							itemPtr->World.Z>gridSz &&
							itemPtr->World.Z<gridEz &&
							shapeHasShadow(itemPtr->shape))
				{
					SWord hdg;
					SLong tx,tz;
					hdg=itemPtr->Status.size<HdgSize?0:((hdgitem*)itemPtr)->hdg;

					tx=(itemPtr->World.X-gridSx)>>world2Pix;
					tz=(itemPtr->World.Z-gridSz)>>world2Pix;
//DEADCODE JON 4/14/00 					if (hdg==0)	RenderShadow(g_lpLib3d,shapePtr,tx,tz,rezTexture);
//DEADCODE JON 4/14/00 					else		RenderShadowRotated(g_lpLib3d,shapePtr,tx,tz,hdg,rezTexture);
					RenderObjectShadow(g_lpLib3d,shapePtr,tx,tz,hdg);

				}
			}
			itemPtr=itemPtr->Next;
		}

		g_lpLib3d->SetObjectLighting(useLightFlag);							//RJS 19Oct00
	}
#endif
//	g_lpLib3d->PopMatrix(MATRIX_PROJECTION);
//	g_lpLib3d->PopMatrix(MATRIX_VIEWER);
//	g_lpLib3d->PopMatrix(MATRIX_OBJECT);
	g_lpLib3d->EndScene();
//DeadCode JON 17Sep00 	UWord ht=hTexture.textureHandle;
//DeadCode JON 17Sep00 	g_lpLib3d->UploadTexture(ht);
	g_lpLib3d->UploadTexture();
}

bool CheckCache()
{
	for (int i=DataGridSizeMIN*DataGridSizeMIN-1;i>=0;i--)
	{
//DeadCode JON 9Oct00 		if ( gridRecords[i].isValid() )
//DeadCode JON 9Oct00 		{
		AltPointsHdr *aph=(AltPointsHdr*)gridRecords[i].pData;
		if (!aph->CheckChecksum())
			return false;
//DeadCode JON 9Oct00 		} else
//DeadCode JON 9Oct00 			return false;
	}
	return true;
}
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void GetMinMaxAlt(const SLong x,const SLong z,const SWord dir,SLong& min,SLong& max)
{
	SLong dataGridSize=DataGridSizeMIN;
	SLong ix=(x&Grid_Mask)-gridRecordBase_x;
	SLong iz=(z&Grid_Mask)-gridRecordBase_z;
	ix/=Grid_Width;
	iz/=Grid_Width;

	DataRecord* dr=&gridRecords[(iz*dataGridSize)+ix];
	AltPointsHdr* aph=(AltPointsHdr*)dr->pData;

	min=aph->minAlt;
	max=aph->maxAlt;

	if (dir==0)			iz++;
	else if (dir==1)	ix++;
	else if (dir==2)	iz--;
	else if (dir==3)	ix--;

	dr=&gridRecords[(iz*dataGridSize)+ix];
	aph=(AltPointsHdr*)dr->pData;

	if (aph->minAlt<min) min=aph->minAlt;
	if (aph->maxAlt>max) max=aph->maxAlt;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void GetMinMaxAlt(const SLong x,const SLong z,SLong& min,SLong& max)
{
//	SLong dataGridSize=Save_Data.detail_3d[DETAIL3D_HORIZONDIST]?DataGridSizeMAX:DataGridSizeMIN;
	SLong dataGridSize=DataGridSizeMIN;
	SLong ix=(x&Grid_Mask)-gridRecordBase_x;
	SLong iz=(z&Grid_Mask)-gridRecordBase_z;
	ix/=Grid_Width;
	iz/=Grid_Width;
	if (ix<0 || iz<0 || ix>=dataGridSize || iz>=dataGridSize)
	{
		min=0;
		max=257000/_altitudeScale;
	}
	else
	{
		DataRecord* dr=&gridRecords[(iz*dataGridSize)+ix];
		AltPointsHdr* aph=(AltPointsHdr*)dr->pData;
		min=aph->minAlt;
		max=aph->maxAlt;
	}
}

}

using namespace TileMake;

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------

void TMake::Reinit(const SLong x,const SLong z,CLib3D* lib3d) const
{
	g_lpLib3d=lib3d;
//DeadCode JON 18Oct00 	ClearRecords(UByte(0));
//DeadCode JON 18Oct00 	SetLandBaseDetail(0);
	InitGridRecords(x,z);
//DeadCode JON 18Oct00 	SetInitialLandTextureCoordinates(x,z);
}

void TMake::Init(const SLong x,const SLong z,CLib3D* lib3d) const
{
	OverLay.LoaderScreen((1<<8)+96);
	g_lpLib3d=lib3d;
	SetTexturePointers();
	OverLay.LoaderScreen((1<<8)+128);
//DeadCode JON 18Oct00 	ClearRecords(UByte(0));
//DeadCode JON 18Oct00 	SetLandBaseDetail(0);
	OverLay.LoaderScreen((1<<8)+128+32);
	InitGridRecords(x,z);
	OverLay.LoaderScreen((1<<8)+128+64);
//DeadCode JON 18Oct00 	SetInitialLandTextureCoordinates(x,z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Exit
//Author		Paul.   
//Date			Thu 16 Jul 1998
//------------------------------------------------------------------------------
void TMake::Exit() const
{
	ClearTexturePointers();
	g_lpLib3d=NULL;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ChkUpdate
//Author		Paul.   
//Date			Mon 20 Jul 1998
//------------------------------------------------------------------------------
void TMake::ChkUpdate(const SLong x,const SLong z) const
{
//DeadCode JON 18Oct00 	GetPalLookup();
	UpdateGridRecords(x,z);
}

//DEADCODE JON 4/14/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JON 4/14/00 //Procedure		BuildShadowList
//DEADCODE JON 4/14/00 //Author		Paul.   
//DEADCODE JON 4/14/00 //Date			Thu 22 Oct 1998
//DEADCODE JON 4/14/00 //------------------------------------------------------------------------------
//DEADCODE JON 4/14/00 void TMake::BuildShadowList(WorldStuff *worldPtr,itemptr itemp)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 	TileMake::BuildShadowList(worldPtr,itemp);
//DEADCODE JON 4/14/00 }


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FrameInit
//Author		Jon   
//Date			Fri 14 Apr 2000
//------------------------------------------------------------------------------
void TMake::FrameInit(WorldStuff* wp, LightVec& sunLight)
{
	TileMake::FrameInit( wp, sunLight );
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetBlock
//Author		Paul.   
//Date			Wed 22 Jul 1998
//------------------------------------------------------------------------------
DataRecord TMake::GetBlock(const SLong x,const SLong z) const
{
	return TileMake::GetBlock(x,z);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSquares
//Author		Paul.   
//Date			Wed 22 Jul 1998
//
//Description	Debug code that returns a series of boxes showing the area
//				of the view covered by each texture map level
//
//------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void TMake::GetSquares(Rect* squares) const
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	TileMake::GetSquares(squares);
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetClipRegion
//Author		Paul.   
//Date			Mon 27 Jul 1998
//------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void TMake::GetClipRegion(const UByte index,Rect& clip) const
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	TileMake::GetClipRegion(index,clip);
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 18Oct00 //Procedure		GetTileClipData
//DeadCode JON 18Oct00 //Author		Paul.   
//DeadCode JON 18Oct00 //Date			Thu 30 Jul 1998
//DeadCode JON 18Oct00 //------------------------------------------------------------------------------
//DeadCode JON 18Oct00 void TMake::GetTileClipData(SquareClips*& psc)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	TileMake::GetTileClipData(psc);
//DeadCode JON 18Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TMake
//Author		Paul.   
//Date			Thu 6 Aug 1998
//------------------------------------------------------------------------------
TMake::TMake()
{
//DeadCode JON 18Oct00 	PrepareNoiseFn();
	AllocateBuffers();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		TMake
//Author		Paul.   
//Date			Tue 6 Oct 1998
//------------------------------------------------------------------------------
TMake::~TMake()
{
 	ReleaseBuffers();
}

//DEADCODE JON 4/14/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JON 4/14/00 //Procedure		RenderTile2Surface
//DEADCODE JON 4/14/00 //Author		Paul.   
//DEADCODE JON 4/14/00 //Date			Fri 6 Nov 1998
//DEADCODE JON 4/14/00 //------------------------------------------------------------------------------
//DEADCODE JON 4/14/00 void TMake::RenderTile2Surface(UByte* pdata,ROWANSURFACEDESC* prsd)
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/12/00 	TileMake::RenderTile2Surface(pdata,prsd);
//DEADCODE JON 4/14/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Render2Surface
//Author		Paul.   
//Date			Mon 9 Nov 1998
//------------------------------------------------------------------------------
void TMake::Render2Surface(const HTEXT& hTexture,UByte rezTexture,UWord offset)
{
	TileMake::Render2Surface(hTexture,rezTexture,offset);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
//DEADCODE JON 1/27/00 void TMake::GetMinMaxAlt(const SLong x,const SLong z,SLong& min,SLong& max)
//DEADCODE JON 1/27/00 {
//DEADCODE JON 1/27/00 	TileMake::GetMinMaxAlt(x,z,min,max);
//DEADCODE JON 1/27/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMinMaxAlt
//Author		Paul.   
//Date			Wed 16 Dec 1998
//------------------------------------------------------------------------------
void TMake::GetMinMaxAlt(const SLong x,const SLong z,const SWord dir,SLong& min,SLong& max)
{
	TileMake::GetMinMaxAlt(x,z,dir,min,max);
}

//DeadCode JON 18Oct00 void TMake::DoGetTextureScales(SLong& num256,SLong& num128,SLong& num64,SLong& num32,SLong& num16,SLong& num8)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	TileMake::DoGetTextureScales(num256,num128,num64,num32,num16,num8);
//DeadCode JON 18Oct00 }

//DEADCODE JON 4/14/00 ROWANSURFACEDESC* TMake::GetRSD(const HTEXT& ht) const
//DEADCODE JON 4/14/00 {
//DEADCODE JON 4/14/00 	return TileMake::GetRSD(ht);
//DEADCODE JON 4/14/00 }

//DeadCode JON 18Oct00 void TMake::DoFreeTextures()
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	TileMake::DoFreeTextures();
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 void TMake::DoFreeTexture(const HTEXT& ht) const
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	TileMake::DoFreeTexture(ht);
//DeadCode JON 18Oct00 }

//DeadCode JON 18Oct00 HTEXT TMake::DoAllocateTexture(UByte textRez)
//DeadCode JON 18Oct00 {
//DeadCode JON 18Oct00 	return TileMake::DoAllocateTexture(textRez);
//DeadCode JON 18Oct00 }

bool TMake::CheckCache()
{
	return TileMake::CheckCache();
}
ImageMapDescPtr TMake::GetImageFromArea(UByte at)
{
	return TileMake::GetImageFromArea(at);
}

