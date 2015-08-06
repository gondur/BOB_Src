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
//Filename       3dcode.cpp
//System         
//Author         Paul.   
//Date           Tue 22 Aug 1995
//Description    
//------------------------------------------------------------------------------

#ifndef	NDEBUG
//#define	_NO_LENSFLARE_
#define	_SHAPE_DEBUG_
//#define _NO_SHAPES_
//#define	_ONLYPILOTED_
//#define	_MARKCHEAT_
#define	_NO_MAP_ART_
//#define _ONLY_PLAYER_SHAPE	
//#define _NOT_PLAYER_SHAPE
//#define	_BTREEFULL_
//#define _NO_MIRROR
//#define	_HEIGHTCHECK_
//#define	_TYRES_
//#define	_BULLETS_
#endif
#define	_NO_MAP_ART_	
//#define	_NO_LENSFLARE_

	#include	"DOSDefs.h"	
#define F_GRAFIX												
#define F_BATTLE
	#include 	"myerror.h"
	#include	"World.h"
	#include 	"aaa.h"
	#include	"AnimData.h"									

	#include	"3DCom.h"
	#include	"Matrix.H"

	#include	"btree.h"
	#include	"tilemake.h"
	#include	"migLand.h"										
	#include	"3DCode.h"

	#include	"transite.h"										
	#include	"savegame.h"									
	#include	"winmove.h"										
	#include	"shpinstr.h"									

	#include	"FileMan.h"
	#include	"mymath.h"
	#include	"Polygon.h"
	#include	"LandScap.h"									//PD 06Nov95
	#include	"ViewSel.h"										//PD 20Feb96
	#include	"Shapes.H"										//PD 08Mar96
	#include	"flymodel.h"									//PD 12Apr96
	#include	"Mytime.h"										//JIM 03Jun96
	#include	"ai.h"											//JIM 03Jun96
//Deaded	#include	"mouse.h"
	#include	"collided.h"									//PD 08Oct96

//DEADCODE JIM 07/02/00 	#include	"package.h"									//RJS 23Oct96
	#include	"missman2.h"									//RJS 23Oct96
	#include	"Persons2.h"									//PD 10Dec96

	#include	"lghtshad.h"									//RJS 02Sep97
	#include	"miles.h"										//RJS 26Feb98

	#include "worldinc.h" // To check some #defines
	#include "modvec.h" // To check some #defines
	#include "Model.h" // To check some #defines
	#include	<stdio.h>
	#include	"monotxt.h"

	#include "overlay.h"
	#include "prof.h"
	#include "fastmath.h"
	#include	"intcock.h"										//RJS 29Nov99
	#include	"smktrls.h"
#include	"animmove.h"
#include	"cstring.h"
#include	"grid.h"													//JON 6Jul00

//DEADCODE JIM 07/02/00 	#include	"sqddiary.h"									//RJS 27Jan99

	class	ThreeDee	Three_Dee;
	
	extern	class	matrix 	_matrix;
	extern 	class	Wrapper _Wrapper;
	extern  Replay _Replay;

#include "replay.h"

	#if	DEBUGGING												//PD 23Jan96
	SLong	polygon_count;										//PD 23Jan96
	#endif														//PD 23Jan96

//#pragma warnmsg("!! JON -  These clip values need fixing when you've done you're projection/clip fix !!")
const	D3DVALUE	COCKPIT_NEARZ = 10.;//200.;								//RJS 31Jul00
const	D3DVALUE	NON_COCKPIT_NEARZ = 200.;//100.;								//RJS 31Jul00
const	ULong	RAM_DERESTHRESHOLD = 16777216;					//RJS 24Mar00
const	SLong	MIRROR_RANGE=100000;
const	SLong	PERIPHBLOB_RANGE=400000;								//RJS 6Sep00
const	float	BALLOON_WIRE_RANGE_SQD = 15000.f*15000.f;				//RJS 8Nov00

#ifdef	_SHAPE_DEBUG_
static	char	shpdebugline[256];
static	int	playerPolys;
static	int	noShapesVisible;
static	int	noShapes;
static	Float	viewDist;
static	int	totalPolys;
#endif
/*class SolidTexture
{
public:
//	enum Dims {width=128,height=128,depth=128,yshift=7,zshift=7,rsquared=3*64*64};
	enum Dims {width=64,height=64,depth=64,yshift=6,zshift=6,rsquared=32*32};
protected:
	static UByte noisedata[256];
	static SLong squares[width];
	ULong *data;
	static SLong refcnt;
	void set(const SLong x,const SLong y,const SLong z)
	{
 		ULong *p=data;
		ULong bitindex=(((z<<zshift)+y)<<yshift)+x;
		p+=(bitindex>>5);
		*p|=ULong(1<<(bitindex&0x1F));
	}
	void clear()
	{
		int i;
		ULong *p=data;
		for (i=(width*height*depth)>>5;i--;*p++=0UL){}
	}

	void test(SLong px,SLong py,SLong pz,SLong *pv)
	{
		if (px>=0 && px<width && py>=0 && py<height && pz>=0 && pz<depth)
		{
			ULong *p=data; 
			ULong bitindex=((((pz)<<zshift)+(py))<<yshift)+(px);
			p+=(bitindex>>5);
			if (*p&ULong(1<<(bitindex&0x1F))) (*pv)++;
		}
	}

	SLong noise(const SLong x) const {return noisedata[x];}
	UByte noise(const SLong x,const SLong y,const SLong z) const {return noise((z+noise((y+noise(x&0xFF))&0xFF))&0xFF);}
	void generate();
//	inline SLong Line3D(SLong x,SLong y,SLong z,SLong dx,SLong dy,SLong dz);
	inline SLong Line3D(SLong x,SLong y,SLong z,SLong exy,SLong exz,SLong ezy,SLong bx,SLong by,SLong bz,SLong n);
public:
	SolidTexture()
	{
		if (!refcnt)
		{
			for (int i=255;i>=0;noisedata[i--]=UByte(Math_Lib.rnd()));
			for (i=width-1;i>=0;i--) {SLong tmp=i-(width>>1); squares[i]=tmp*tmp;}
		}
		data=new ULong[(width*height*depth)>>5];
		if (data)
		{
			clear();
			generate();
		}
		refcnt++;
	}
	~SolidTexture()
	{
		if (data) delete[]data;
		--refcnt;
	}
	void project(ANGLES,ANGLES,ANGLES,ROWANSURFACEDESC*);
};

SolidTexture fluffyball;

void SolidTexture::generate()
{
	//inside of sphere ... x*x+y*y+z*z<=r*r
	for (SLong dd=(depth>>1)-1;dd>=0;dd--)
	{
		SLong tmp=squares[dd];
		for (SLong hh=height-1;hh>=0;hh--)
		{
			SLong tmp2=squares[hh]+tmp;
			for (SLong ww=width-1;ww>=0;ww--)
			{
				SLong tmp3=squares[ww]+tmp2-rsquared;
				if (tmp3>-8 && tmp3<8)	//tmp3<rsquared && (noise(ww,hh,dd)&1))
					set(ww,hh,dd);
			}
		}
	}
}

//SLong SolidTexture::Line3D(SLong x,SLong y,SLong z,SLong dx,SLong dy,SLong dz)
SLong SolidTexture::Line3D(SLong x,SLong y,SLong z,
						   SLong exy,SLong exz,SLong ezy,
						   SLong bx,SLong by,SLong bz,
						   SLong n)
{
//	SLong n;
	SLong nx,ny,nz;
//	SLong exy,exz,ezy;
//	SLong ax,ay,az;
//	SLong bx,by,bz;
	SLong in(0);

//	ax=dx<0?-dx:dx; bx=ax<<1;
//	ay=dy<0?-dy:dy; by=ay<<1;
//	az=dz<0?-dz:dz; bz=az<<1;
//	exy=ay-ax; exz=az-ax; ezy=ay-az;
//	n=ax+ay+az;

	test(x,y,z,&in);
	nx=x; ny=y; nz=z;
	while (n--)
	{
		if (exy<0)
		{
			if (exz<0)	x++, nx--, exy+=by, exz+=bz;
			else		z++, nz--, exz-=bx, ezy+=by;
		}
		else
		{
			if (ezy<0)	z++, nz--, exz-=bx, ezy+=by;
			else		y++, ny--, exy-=bx, ezy-=bz;
		}
		test(x,y,z,&in);
		if (in<15) test(nx,ny,nz,&in);
		if (in==15) break;
	}
	return in;
}

void SolidTexture::project(ANGLES h,ANGLES p,ANGLES r,ROWANSURFACEDESC *psurf)
{
	FPMATRIX mat;
	_matrix.GenerateV(h,p,r,&mat);
	SLong DXt[3],DYt[3];	//,DZt[3];
	DXt[0]=SLong(mat.L11*0x7FFF)>>1;DXt[1]=SLong(mat.L21*0x7FFF)>>1;DXt[2]=SLong(mat.L31*0x7FFF)>>1;
	DYt[0]=SLong(mat.L12*0x7FFF)>>1;DYt[1]=SLong(mat.L22*0x7FFF)>>1;DYt[2]=SLong(mat.L32*0x7FFF)>>1;
//	DZt[0]=SLong(mat.L13*(width>>1));	DZt[1]=SLong(mat.L23*(width>>1));	DZt[2]=SLong(mat.L33*(width>>1));

	SLong exy,exz,ezy;
	SLong bx=SLong(mat.L13*width);
	SLong by=SLong(mat.L23*width);
	SLong bz=SLong(mat.L33*width);
	if (bx<0) bx=-bx;
	if (by<0) by=-by;
	if (bz<0) bz=-bz;
	exy=(by-bx)>>1;
	exz=(bz-bx)>>1;
	ezy=(by-bz)>>1;

	UByte *ppic=(UByte*)psurf->lpSurface;
	SLong PosT[3];
	SLong tmp2=-SLong(psurf->dwHeight)>>1;
	PosT[0]=(width<<14)+tmp2*DYt[0];
	PosT[1]=(width<<14)+tmp2*DYt[1];
	PosT[2]=(width<<14)+tmp2*DYt[2];
	for (SLong y=-tmp2<<1;--y>=0;)
	{
		SLong PosC[3];
		SLong tmp=-SLong(psurf->dwWidth)>>1;
		PosT[0]+=DYt[0]; PosT[1]+=DYt[1]; PosT[2]+=DYt[2];
		PosC[0]=PosT[0]+tmp*DXt[0];
		PosC[1]=PosT[1]+tmp*DXt[1];
		PosC[2]=PosT[2]+tmp*DXt[2];
		for (SLong x=-tmp<<1;--x>=0;)
		{
			PosC[0]+=DXt[0]; PosC[1]+=DXt[1]; PosC[2]+=DXt[2];
			*ppic++=UByte(Line3D(	PosC[0]/ANGLES_FRACT,
									PosC[1]/ANGLES_FRACT,
									PosC[2]/ANGLES_FRACT,
									exy,exz,ezy,
									bx,by,bz,
									width));
		}
	}
}


SLong SolidTexture::refcnt=0;
UByte SolidTexture::noisedata[256];
SLong SolidTexture::squares[SolidTexture::width];
*/

#ifndef	NDEBUG
static int	global_cheatbitsoff;
#endif

#ifndef	NDEBUG

#define AFX_CDECL __cdecl
typedef char CHAR;
#define CONST               const
typedef CONST CHAR *LPCSTR, *PCSTR;
typedef LPCSTR LPCTSTR;
void AFX_CDECL AfxTrace(LPCTSTR lpszFormat, ...);

//#define	_PROCDEBUG_

#endif

class	Bollox2
{
public:
	Bollox2(const char*	theName)
	{
//DeadCode RJS 15Aug00 		static	int	theWindow = AllocConsole();
	}

	~Bollox2()
	{
	}
};





//#define	_NOGRIDOPTIMISE_



//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ThreeDee
//Author		Robert Slater
//Date			Tue 24 Feb 1998
//
//Description	Constructor
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
CON	ThreeDee::ThreeDee()
{
	mirrorSeen = false;													//JON 3Jul00
//	fogCol = 0x0090B8E8;												//JON 4/18/00
	fogCol = 0x007098C8;
	b3DRunning=FALSE;
	MasterPalettePtr = NULL;
	NewPalettePtr = new RGBINFO[256*8];

	sunanimptr = new UByte[sizeof(SunAnimData)];
	sunanimptr = (AnimSizeField) sizeof(SunAnimData);			//RJS 01Dec99
	sunanimptr = (AnimFlagField) (1<<MINANIM) + (1<<SUNANIM);	//RJS 01Dec99
	pMigLand=NULL;
	pTMake=NULL;

	normalDataPtr=NULL;
//deadcode	pNormalLookup=NULL;

	View_Point=NULL;
	nomorereallygetdata=false;

#ifndef	NDEBUG													//RJS 23Mar00
//Cheat anim data should cover all cases...
	UByteP	newcheatptr = new UByte[1024];
	for (int i=0; i < 1024; i++)
		newcheatptr[i] = 0;

	CheatAnim = newcheatptr;
	CheatAnim = (AnimSizeField)1024;
	CheatAnim = (AnimFlagField)0xFFFFFFFF;

	global_cheatbitsoff = -1;
#endif

	lensflareanim = new UByte[sizeof(FlareAnimData)];
	lensflareanim = AnimSizeField(sizeof(FlareAnimData));			//RJS 03May00
	lensflareanim = AnimFlagField((1<<MINANIM) + (1<<FLAREANIM));	//RJS 03May00

	UByteP dummyanim = new UByte[64];
	for (int j=0; j < 64; j++)
		dummyanim[j] = 0;

	DummyAnimP = dummyanim;
	DummyAnimP = AnimSizeField(64);
	DummyAnimP = AnimFlagField(1<<MINANIM);

	mistHeight = 0;
	mistDensity = 0;

	sunItemP = new item;												//RJS 30May00
  	sunItemP->shape=SUN;												//RJS 30May00
 	sunItemP->Anim = sunanimptr;										//RJS 30May00

//DeadCode JON 31Aug00 	clipNearZ = DEFAULT_NEARZ;											//RJS 31Jul00

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ThreeDee
//Author		Robert Slater
//Date			Tue 24 Feb 1998
//
//Description	Destructor...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
DES	ThreeDee::~ThreeDee()
{
	delete []NewPalettePtr;
//DeadCode RJS 21Apr99 	delete []sunanimptr;
	if (normalDataPtr!=NULL) delete[]normalDataPtr,normalDataPtr=NULL;
//deadcode	if (pNormalLookup!=NULL) delete[]pNormalLookup,pNormalLookup=NULL;

	delete sunItemP;													//RJS 30May00
//DeadCode RJS 30May00 	sunanimptr.Delete();										//RJS 21Apr99

#ifndef	NDEBUG													//RJS 23Mar00
	CheatAnimSave = ANIM_NULL;
	CheatAnim.Delete();
#endif

	lensflareanim.Delete();										//RJS 03May00

	DummyAnimP.Delete();


}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Init3D
//Author		Paul.   
//Date			Tue 17 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Init3D(CLib3D *lib3d,ViewPoint*	vp)				
{
	g_lpLib3d=lib3d;

	Save_Data.fieldOfView=ANGLES_45Deg;

	CockpitBuf	buffetData;
 	buffetData.hdg=
 		buffetData.pitch=
 		buffetData.roll=ANGLES_0Deg;
 
 	buffetData.delta.X=
 		buffetData.delta.Y=
 		buffetData.delta.Z=0;

	SHAPE.SetCockpitBuffet(&buffetData);


	View_Point=vp;
	
	b3DRunning=TRUE;
	bt = new btree(LandTreeSize,ObjectTreeSize);

	drawDescText = false;												//JON 17Oct00
	shapecheat = FALSE;											//RJS 18Sep96
	oldtime = -1;												//RJS 24Oct96
	time_minutes = -1;											//RJS 23Apr98
	whereinpal = -1;												//RJS 22Oct96
	whichpal = PAL_DAY;											//RJS 02Sep97
	newpalettes = NULL;											//RJS 22Oct96
	SHAPE.SunInVision = FALSE;									//RJS 26Nov96
	if (Manual_Pilot.ControlledAC2)
		((AirStrucPtr)Manual_Pilot.ControlledAC2)->fly.gforce = 0;	//RJS 12May97
//	current_screen->DoInitLand();

	Trans_Obj.CloudTotal = 0;									//RJS 09Jul97
	Trans_Obj.CloudTimer = 0;									//RJS 09Jul97

	Trans_Obj.GScatterTimer = 0;								//RJS 21Oct97
	Trans_Obj.GScatterCnt = 0;									//RJS 21Oct97
	if (vp)
	{
		View_Point->isMagic = FALSE;									//RJS 12Aug97
		View_Point->MagicCode = 0;									//RJS 12Aug97
	}

	if (pMigLand==NULL)	
	{
		pMigLand=new CMigLand;
		pTMake=new TMake;
	}
	PaletteBlender(View_Point->TimeOfDay());
	pMigLand->BigInit(View_Point);

	pTMake->Init(vp->World.X,vp->World.Z,lib3d);
	OverLay.LoaderScreen((2<<8)+128+96);
	MaxShapeCount = FILEMAN.filesindir(DIR_SHAPES) - 1;
	MaxShape2Count = 255 + FILEMAN.filesindir(DIR_MOBSHPS);
	MaxGroupCount = 511 + FILEMAN.filesindir(DIR_GROUPS);
	MaxGroup2Count = 767 + FILEMAN.filesindir(DIR_MOBGROUPS);	//RJS 13Dec99

	CheatStart[0] = 1;
	CheatStart[1] = 257;
	CheatStart[2] = 513;
	CheatStart[3] = 769;										//RJS 13Dec99

	CheatEnd[0] = MaxShapeCount;
	CheatEnd[1] = MaxShape2Count;
	CheatEnd[2] = MaxGroupCount;
	CheatEnd[3] = MaxGroup2Count;

	if ((CheatEnd[0] - CheatStart[0]) < 0)
	{
		CheatStart[0] = 0;
		CheatEnd[0] = 0;
	}

	if ((CheatEnd[1] - CheatStart[1]) < 0)
	{
		CheatStart[1] = 0;
		CheatEnd[1] = 0;
	}

	if ((CheatEnd[2] - CheatStart[2]) < 0)
	{
		CheatStart[2] = 0;
		CheatEnd[2] = 0;
	}

	if ((CheatEnd[3] - CheatStart[3]) < 0)						//RJS 13Dec99
	{															//RJS 13Dec99
		CheatStart[3] = 0;										//RJS 13Dec99
		CheatEnd[3] = 0;										//RJS 13Dec99
	}															//RJS 13Dec99


 	SHAPE.ClearRadar();											//RJS 25Jun98

	SunAnimData*	adptr = (SunAnimData*) sunanimptr;		//RJS 02Jul98
	adptr->frameno = 0;										//RJS 02Jul98
	adptr->nolaunchers = 0;									//RJS 02Jul98


	if (normalDataPtr==NULL)
		normalDataPtr=new NormalData[256];
//deadcode	if (pNormalLookup==NULL)
//deadcode		pNormalLookup=new UByte[256];
	lastSunPos.X=lastSunPos.Y=lastSunPos.Z=0;

	ConstructNormalData();

	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(MAPZ);

	mapdistz = sdptr->sx << 6; // cos map is 4cm
	mapoffx = mapoffy = 0;

//DEADCODE RJS 3/21/00 	SHAPE.SetDistScale();//RJS 02Nov98

	OverLay.LoaderScreen((2<<8)+128+96+16);

	radarOn = FALSE;											//RJS 06Nov98
	groundlockOn = FALSE;										//RJS 04Jun99

	supercheatitem = NULL;

	SHAPE.SphereXScale = 1;										//RJS 02Dec98
	SHAPE.SphereYScale = 1;										//RJS 02Dec98

	if (Save_Data.gamedifficulty[GD_PERFECTRADARASSISTEDGUNSIGHT])	//RJS 09Dec98
		radarOn = TRUE;												//RJS 09Dec98

	if (Save_Data.gamedifficulty[GD_REALISTICRADARASSISTEDGUNSIGHT])//RJS 04Jun99
	{
		radarOn = TRUE;
		groundlockOn = TRUE;									//RJS 04Jun99
	}

	havematrix = false;				//RJS 10Dec98

	OverLay.InitInfoTexts();

	OverLay.LoaderScreen((2<<8)+255);

//DeadCode JON 17Oct00 	InitMirror();

//DeadCode RJS 28Feb00	SHAPE.SwitchToPilot(true);									//RJS 10Dec99

	Land_Scape.smokePlaneOn = false;							//RJS 15Feb00

//DeadCode RJS 24Mar00 //???	Squad_Diary.CreatePlayer(Todays_Packages);					//RJS 27Jan00

	vp->move_time_ms = timeGetTime();									//CSB 02/03/00
	view_dt = 0;														//CSB 02/03/00
	draw_time = 0;														//CSB 02/03/00
	last_time = vp->move_time_ms;										//CSB 02/03/00
	viewer_oldhdg   = ANGLES_0Deg;
	viewer_oldpitch = ANGLES_0Deg;
	viewer_oldroll  = ANGLES_0Deg;

// Set up cockpit visibility prefs...

	ULong	textureRAM;											//RJS 24Mar00
	g_lpLib3d->GetTextureRAM(textureRAM);						//RJS 24Mar00

	cockpitPrefs = 0xFFFFFFFF;
	if (textureRAM < RAM_DERESTHRESHOLD)
		cockpitPrefs &= ~COCK3D_INTERACTIVEON;

	ULong	tmpdrawtime = Timer_Code.FRAMETIME*10;
	vp->SetDrawFrameTime(tmpdrawtime);							//RJS 05Apr00

// Force near horizon if Z-Buffer depth is crap
//DEADCODE RJS 5/8/00 	ULong	theZBufferDepth;
	g_lpLib3d->GetZDepth(theZBufferDepth);

	if (theZBufferDepth < 24)									//RJS 03May00
		Save_Data.detail_3d %= DETAIL3D_HORIZONDIST;			//RJS 03May00

	mistHeight = 0;														//RJS 26May00
	mistDensity = 0;													//RJS 26May00

	cockScale = 1;														//RJS 30May00

	SHAPE.FixUpCollision = FALSE;										//AMM 4Jul00

//DeadCode JON 31Aug00 	clipNearZ = DEFAULT_NEARZ;											//RJS 31Jul00

	includeClippedObjects = true;										//RJS 23Aug00
	hasBeenMirror = false;												//RJS 30Aug00

	if (View_Point->trackeditem)
	{
		viewer_x = View_Point->trackeditem->World.X;
		viewer_y = View_Point->trackeditem->World.Y;
		viewer_z = View_Point->trackeditem->World.Z;
	}

	Trans_Obj.realFPS = 25;										//RJS 21Sep00
	SHAPE.LogMousePos(0,0,0,0,false);

	Land_Scape.gunnerDead = false;										//RJS 24Oct00
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Done3D
//Author		Paul.   
//Date			Tue 17 Oct 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Done3D()
{
//DeadCode CSB 11Sep00 	Mono_Text.PrintAt(40,20,(UByte*)"Done 3D");
#ifndef	NDEBUG													//RJS 23Mar00
//Quick restore...												//RJS 23Mar00
	if (shapecheat)												//RJS 23Mar00
		Persons2::PlayerSeenAC->Anim = CheatAnimSave;			//RJS 23Mar00
#endif															//RJS 23Mar00
//TempCode PD 23Nov98 	Save_Data.gameSettings=gameSettings;
	b3DRunning=FALSE;											//PD 10Jun97
//DeadCode RJS 20Oct00 	GREY3DTYPE	gtdt = NOGREY3D;								//PD 29Sep96
//DEAD	POLYGON.SetGrey3DType(gtdt);								//PD 29Sep96
	if (pMigLand!=NULL)	delete pMigLand,pMigLand=NULL;		//PD 18Jan98
	if (pTMake!=NULL)
	{
		pTMake->Exit();
		delete pTMake;
		pTMake=NULL;
	}

	DeleteFor2D();												//RJS 08Sep00

//DeadCode RJS 8Sep00 	delete(bt);

//TempCode PD 04Feb99 	delete aircraft_tree;										//PD 28Oct98
	aircraft_tree=NULL;											//PD 28Oct98
//DeadCode RJS 8Sep00 	bt=NULL;													//JIM 06Oct96
	Land_Scape.Exit();											//PD 18Oct96

	if (normalDataPtr!=NULL) delete[]normalDataPtr,normalDataPtr=NULL;
//deadcode	if (pNormalLookup!=NULL) delete[]pNormalLookup,pNormalLookup=NULL;

//DeadCode RJS 8Sep00 	OverLay.ReleaseInfoTexts();

	SHAPE.DeleteAllSmokeTrails();								//RJS 18Feb99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteFor2D
//Author		Robert Slater
//Date			Fri 8 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::DeleteFor2D()
{
	delete bt;
	bt = NULL;

	OverLay.ReleaseInfoTexts();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		FreeLandscapeTextures
//Author		Robert Slater
//Date			Fri 8 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::FreeLandscapeTextures()
{
	if (pMigLand)
		pMigLand->FreeTextures();
}

static char	fnum=0;
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		render
//------------------------------------------------------------------------------
//Author		Paul.   
//Date			Tue 22 Aug 1995
//Modified	
//
//Description	renders a 3D scene in a viewport from a given viewpoint
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

inline	ShapeNum operator++ (ShapeNum& s,int) {return (ShapeNum)((*(UWord*)&s)++);}
inline	ShapeNum operator-- (ShapeNum& s,int) {return (ShapeNum)((*(UWord*)&s)--);}
__declspec(dllimport)
int
__stdcall
QueryPerformanceCounter(
    LARGE_INTEGER *lpPerformanceCount
    );
__declspec(dllimport)
int
__stdcall
QueryPerformanceFrequency(
    LARGE_INTEGER *lpPerformanceCount
    );


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		render3d
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::render3d(ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{ 
#ifdef	_PROCDEBUG_
	Bollox2("render");
#endif
	View_Point=vp;
	bt->SetupBTree(g_lpLib3d,vp);
	nomorereallygetdata=true;
	SHAPE.SetView(vp,g_lpLib3d);

//Get screen definition...
			
	ROWANSURFACEDESC	sdesc;
	sdesc.dwSize = sizeof(ROWANSURFACEDESC);
	if (g_lpLib3d->GetSurfaceDesc(&sdesc) == S_OK)
	{
		SHAPE.vd_hoD = 1.;
		SHAPE.vd_originy = sdesc.dwHeight>>1;
		SHAPE.vd_originx = sdesc.dwWidth>>1;
		SHAPE.vd_width = sdesc.dwWidth;
		SHAPE.vd_height = sdesc.dwHeight;
	}

	if (!shapecheat)
	{
		if (Key_Tests.KeyHeld3d(NEXTSHAPEDN))
			Save_Data.fieldOfView+=ANGLES_2Deg;
		else if (Key_Tests.KeyHeld3d(NEXTSHAPEUP))
			Save_Data.fieldOfView-=ANGLES_2Deg;

		if (Save_Data.fieldOfView<ANGLES_45Deg)
			Save_Data.fieldOfView=ANGLES_45Deg;
		else if (Save_Data.fieldOfView>ANGLES_60Deg)
			Save_Data.fieldOfView=ANGLES_60Deg;
	}

	SHAPE.SetDistScale();
	fnum++;

// 0. If min frametime forced by video then wait.
//TempCode JON 19Sep00 	DWORD time;
	while( (/*time=*/timeGetTime())-last_time<OverLay.screenshot.minframetime)
		Sleep(1);


//	1.	Block movecode
	View_Point->BlockTick(TRUE);

//**********************************************************************
//	Frame Timer Used For Position Predicter
//**********************************************************************
	
	SetFrameTime();													//RJS 19Sep00

//**********************************************************************
//	Frame Timer Used For Position Predicter	(END)
//**********************************************************************

//	2.	Set view type
	View_Point->SelectView();									//PD 19Feb96


//DEADCODE JON 4/6/00 	if (Land_Scape.UpdateTexturesWRTViewPos()==false &&
//DEADCODE JON 4/6/00 		Land_Scape.UpdateTexturesWRTViewPos()==false &&
//DEADCODE JON 4/6/00 		Land_Scape.UpdateTexturesWRTViewPos()==false)
//DEADCODE JON 4/6/00 		assert(false&&"Unrecoverable landscape error");

//TEMPCODE	RenderMirror(View_Point->World,0,0,1,ANGLES_45Deg);
	Bool	drawpolypit = View_Point->PolyPitEnabled();					//RJS 10Mar00
//DeadCode RJS 20Oct00 	bool	inCockpit = View_Point->InCockpit();

//Dead	Bool	drawpolypit = View_Point->PolyPitEnabled();					

#ifndef NDEBUG													//DAW 20Dec96
	SLong			index;
	if (shapecheat)
	{
		MinAnimData*	adptr;
		SLong			ThisShape = Manual_Pilot.ControlledAC2->shape;//RJS 20May98

		if (Key_Tests.KeyPress3d(NEXTSHAPEUP))
		{
			global_cheatbitsoff = -1;
			// Clear the rest of the anim-data...
			for (int i=1; i < 1024; i++)
				CheatAnim[i] = 0;

			adptr = (MinAnimData*) Manual_Pilot.ControlledAC2->Anim;
			if (View_Point->deathview == TRUE)
				adptr->itemstate = DEAD;
			else
				adptr->itemstate = ALIVE;

			ThisShape++;
			if (ThisShape > CheatEnd[CheatPos])
			{
				CheatPos++;
				if (CheatPos > 3)								//RJS 13Dec99
					CheatPos = 0;

				if (CheatStart[CheatPos] == 0)
				{
					CheatPos++;
					if (CheatPos > 3)							//RJS 13Dec99
						CheatPos = 0;
					else
					{
						if (CheatStart[CheatPos] == 0)
						{
							CheatPos++;
							if (CheatPos > 3)					//RJS 13Dec99
								CheatPos = 0;
							else
							{
								if (CheatStart[CheatPos] == 0)	//RJS 13Dec99
								{								//RJS 13Dec99
									CheatPos++;					//RJS 13Dec99
									if (CheatPos > 3)			//RJS 13Dec99
										CheatPos = 0;			//RJS 13Dec99
								}								//RJS 13Dec99
							}
						}
					}
				}

				ThisShape = CheatStart[CheatPos];
			}

			Manual_Pilot.ControlledAC2->shape = (ShapeNum) ThisShape;//RJS 20May98
		}

		if (Key_Tests.KeyPress3d(NEXTSHAPEDN))
		{
			global_cheatbitsoff = -1;
			// Clear the rest of the anim-data...
			for (int i=1; i < 1024; i++)
				CheatAnim[i] = 0;

			adptr = (MinAnimData*) Manual_Pilot.ControlledAC2->Anim;
			if (View_Point->deathview == TRUE)
				adptr->itemstate = DEAD;
			else
				adptr->itemstate = ALIVE;

			ThisShape--;
			if (ThisShape < CheatStart[CheatPos])
			{
				CheatPos--;
				if (CheatPos < 0)
					CheatPos = 3;

				if (CheatStart[CheatPos] == 0)
				{
					CheatPos--;
					if (CheatPos < 0)
						CheatPos = 3;
					else
					{
						if (CheatStart[CheatPos] == 0)
						{
							CheatPos--;
							if (CheatPos < 0)
								CheatPos = 3;
						}
					}
				}

				ThisShape = CheatEnd[CheatPos];
			}

			Manual_Pilot.ControlledAC2->shape = (ShapeNum) ThisShape;//RJS 20May98
		}

		if (Key_Tests.KeyPress3d(DROPBOMB))
		{
			adptr = (MinAnimData*) Manual_Pilot.ControlledAC2->Anim;
//DeadCode RJS 02Feb100 			adptr->itemstate++;
			if (adptr->itemstate == DEAD)						//RJS 02Feb100
			{
				if (adptr->repair)
				{
					adptr->repair = 0;
					adptr->itemstate++;
				}
				else
				{
					adptr->repair = 1;
					adptr->itemstate = DYING;
				}
			}
			else
				adptr->itemstate++;
		}

		if (Key_Tests.KeyPress3d(SHOOT))
		{
			int					damend = SHAPE.GetAnimDataSize(Manual_Pilot.ControlledAC2->shape);
			ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(Manual_Pilot.ControlledAC2->shape);
			int					damindex = sdptr->DamageOffset;

			if (sdptr->DamageOffset && (sdptr->DamageOffset < damend))
			{
				while (CheatAnim[damindex] != 0)
				{
					if (damindex >= damend)
						break;

					damindex++;
				}

				if (damindex < damend)
				{
					global_cheatbitsoff = damindex - sdptr->DamageOffset;
					CheatAnim[damindex] = 255;		
				}
			}

			Anim_Control.SetPlayerAnim(Manual_Pilot.ControlledAC2,ANIMATION_WALK);
		}

		if (global_cheatbitsoff > -1)
		{
			ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(Manual_Pilot.ControlledAC2->shape);
			int					damindex = sdptr->DamageOffset + global_cheatbitsoff;

			if (Key_Tests.KeyPress3d(RPM_10))
				CheatAnim[damindex] = 0;

			if (Key_Tests.KeyPress3d(RPM_20))
				CheatAnim[damindex] = 64;

			if (Key_Tests.KeyPress3d(RPM_30))
				CheatAnim[damindex] = 128;

			if (Key_Tests.KeyPress3d(RPM_40))
				CheatAnim[damindex] = 192;

			if (Key_Tests.KeyPress3d(RPM_50))
				CheatAnim[damindex] = 255;	
		}
	}

	SuperShapeCheat();

	if (Key_Tests.KeyPress3d(SHAPECHEATTOG))
	{
		global_cheatbitsoff = -1;
		if (shapecheat)
		{
			Manual_Pilot.ControlledAC2->Anim = CheatAnimSave;	//RJS 23Mar00
			Manual_Pilot.ControlledAC2->shape = CheatSave;
			shapecheat = FALSE;
		}
		else
		{
			CheatAnimSave = Manual_Pilot.ControlledAC2->Anim;	//RJS 23Mar00
			CheatSave = Manual_Pilot.ControlledAC2->shape;
			Manual_Pilot.ControlledAC2->Anim = CheatAnim;		//RJS 23Mar00
// Copy item state (1st byte)									//RJS 23Mar00
			CheatAnim[0] = CheatAnimSave[0];					//RJS 23Mar00
// Clear the rest of the anim-data...							//RJS 23Mar00
			for (int i=1; i < 1024; i++)						//RJS 23Mar00
				CheatAnim[i] = 0;								//RJS 23Mar00

			for (index = 0; index < 4; index++)
			{
				if (	(CheatSave >= CheatStart[index])
					&&	(CheatSave <= CheatEnd[index])	)
				{
					CheatPos = index;
					break;
				}
			}

			shapecheat = TRUE;
		}
	}
#endif

	static SLong	time24hr = 0;
	static SLong	theHours = 0;

	time24hr = View_Point->TimeOfDay()%8640000;
	theHours = time24hr / (100*60*60);
	if (theHours < 8)	//8 a.m.
	{
		// scale to 4 a.m.
		mistHeight = 5000 - ((5000 * (time24hr - 1440000))/1440000);
		mistDensity = (mistHeight * 245)/5000;
		if (mistDensity < 100)
			mistHeight = SLong(0x80000000);
	}
	else
		mistHeight = SLong(0x80000000);

//	drawpolypit = View_Point->PolyPitEnabled();					
	_matrix.SetZScale();							
	OverLay.SetViewpoint(View_Point);
	OverLay.SetScreen(g_lpLib3d);
	OverLay.SetInteractiveMode();										//RJS 23Aug00

 	init_scene(world, vp);

//DEADCODE JON 4/14/00 	pTMake->BuildShadowList(world,vp);							//PD 22Oct98
 	pTMake->FrameInit(world,Three_Dee.SunLightVector);

 	// set up the landcape local variables
 	// decide on visible tiles
 	// render any new landscape tiles that may now be required (so MUST come b4 the main render begin scene)
 	// update horizon point and colour grids if required
 	Land_Scape.SetUpVisibleCones(	g_lpLib3d,
 									View_Point,								
 									viewer_x,viewer_y,viewer_z,		
 									vp->hdg);

	g_lpLib3d->BeginScene(RENDERTARGET_PRIMARY);
	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);

	// Get vector for eye...
	R3DMATRIX	vmat;
	g_lpLib3d->GetMatrix(MATRIX_VIEWER,vmat);
	eye_x = vmat._13;
	eye_y = vmat._23;
	eye_z = vmat._33;

	_Miles.SetUpListener(View_Point->trackeditem,viewer_x,viewer_y,viewer_z,eye_x,eye_y,eye_z,View_Point->hdg,View_Point->pitch);	//RJS 15Sep00

//DeadCode JON 7Nov00 	if (SLong(viewer_y) < mistHeight)									//RJS 30May00
//DeadCode JON 7Nov00 	{
//DeadCode JON 7Nov00 		g_lpLib3d->SetFogValues( .8f, 0.8f );
//DeadCode JON 7Nov00 		g_lpLib3d->SetFogColour(0x00AAAAAA);
//DeadCode JON 7Nov00 	}
//DeadCode JON 7Nov00 	else
//DeadCode JON 7Nov00 		g_lpLib3d->SetFogColour(fogCol);
//DeadCode JON 29Aug00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,clipNearZ,Land_Scape.view_dist);	//RJS 31Jul00

	ANGLES h,p,r;												
	if(drawpolypit)												
	{															
		g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,COCKPIT_NEARZ,Land_Scape.view_dist);	
		g_lpLib3d->SetNearClipPlane( NON_COCKPIT_NEARZ );
		//Get gunsight stuff here, during blocktick!
		if (Manual_Pilot.ControlledAC2)					//RJS 25Jun99
		{
/*			WeapAnimData*	weapon;
			SLong			index = 0;
			SLong	xpos, ypos, zpos;
			SLong	wpcnt = 0;
			ULong	mvel;
			UWord	mdelay,mburst;

			SHAPE.gunsightX = 0;
			SHAPE.gunsightY = 0;
			SHAPE.gunsightZ = 0;
			SHAPE.gunsightmvel = 9000;
			while (index < 3)
			{
				weapon = SHAPE.GetWeaponLauncher(Manual_Pilot.ControlledAC2,index,xpos,ypos,zpos,mvel,mdelay,mburst,LT_BULLET);
				if (weapon)
				{
					SHAPE.gunsightX += xpos;
					SHAPE.gunsightY += ypos;
					SHAPE.gunsightZ += zpos;

					SHAPE.gunsightmvel = mvel;

					wpcnt++;
 				}
				index++;
 			}

			if (wpcnt)
			{
				SHAPE.gunsightX /= wpcnt;
				SHAPE.gunsightY /= wpcnt;
				SHAPE.gunsightZ /= wpcnt;
			}*/

			Manual_Pilot.ControlledAC2->fly.pModel->BackupForGunsight();//RJS 25Jun99
		}

		View_Point->GetPolyPitAngles(h,p,r);
		_Miles.SetCockpit(TRUE);
	}
	else
	{
		g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,NON_COCKPIT_NEARZ,Land_Scape.view_dist);	

		_Interactive.Clear();									//RJS 29Nov99

		if (View_Point->viewnum.viewmode == VM_InsideCheat)			//RJS 16Jun99
			_Miles.SetCockpit(TRUE);
		else
			_Miles.SetCockpit(FALSE);
	}

	Smoke_Trails.SetViewPoint(vp);								//RJS 11Feb00

	SHAPE.ResetRadar(Manual_Pilot.ControlledAC2,viewer_x,viewer_y,viewer_z);//RJS 09Nov98
	PaletteBlender(View_Point->TimeOfDay());				//RJS 26May00
//DEADCODE JON 4/13/00 	pTMake->BuildShadowList(world,vp);							//PD 22Oct98
//TEMPCODE JIM 07/06/00 	if (ProbeTime  a0(0,"make tree"))
	if (Manual_Pilot.ControlledAC2)
	{
		//if player is MiG15 then change shape to complex MiG
		ShapeNum manualPilotShape=Manual_Pilot.ControlledAC2->shape;
//DeadCode RJS 15Dec99		if (manualPilotShape==CMIG15) Manual_Pilot.ControlledAC2->shape=MIG15;
//DEADCODE PD 07/12/99 		do_objects();		

//3.	Put items into binary tree
		GetVisibleObjects(world);

		Manual_Pilot.ControlledAC2->shape=manualPilotShape;
	}
	else do_ui_objects();

	OverLay.SetupCheatBox();

// 4.	Restart movecode

	View_Point->BlockTick(FALSE);								//RJS 04Feb00

//DEADCODE JIM 09/12/99 	SHAPE.SetRadar();											//RJS 06Nov98
	
//	5.	Render landscape
//TEMPCODE JIM 07/06/00 	if (ProbeTime  a12(12,"Landscape"))
	Land_Scape.RenderLandscape(	g_lpLib3d );
//DEADCODE JON 4/6/00 								,View_Point,							
//DEADCODE JON 4/6/00 								fpviewer_matrix,					
//DEADCODE JON 4/6/00 								viewer_x,viewer_y,viewer_z,		
//DEADCODE JON 4/6/00 								vp->hdg);
//DeadCode RJS 04Feb00 	View_Point->BlockTick(FALSE);

	Land_Scape.gunnerDead = false;										//RJS 24Oct00

//DeadCode JON 5Oct00 	OverLay.SetupCheatBox();

	// Do not call possmove cycle before do_objects();			//ARM 26Jul96
	SHAPE.InitCloudFade();									//RJS 15Jul98

//5.5	Misty Stuff...

	SHAPE.MistyMoistyMorning(mistHeight,mistDensity);					//RJS 26May00

//	6.	Draws what's in the binary tree
//TEMPCODE JIM 07/06/00 	if (ProbeTime  a24(24,"Draw vis"))
	DrawVisibleObjects();		//render_scene();				//RJS 07Feb00

	SHAPE.SetCloudFade();										//RJS 15Jul98

//DEADCODE PD 01/12/99 	Land_Scape.TidyUp();

	OverLay.doInteractiveCockpit = false;
	bool	ZBufferFudge = false;							//RJS 08May00
#ifndef _NO_SHAPES_
	if(drawpolypit)
	{
		//RenderMirror();

		if (theZBufferDepth < 24)							//RJS 08May00
		{
			ZBufferFudge = true;
 			g_lpLib3d->FlushAsBackground();					//RJS 08May00
		}

//	7.	Draws the cockpit
//TEMPCODE JIM 07/06/00 	if (ProbeTime  a36(36,"Cockpit"))
		add_cockpit(*vp,UNMASKED,h,p,r);					//JIM 10Aug96
	}															//PD 20Feb96
#endif
//DEADCODE JON 4/19/00 	g_lpLib3d->End3DScene(); // this does nothing so why call it???

#ifndef _NO_SHAPES_
//	8.	Info panel stuff...
#ifdef	_PROCDEBUG_
::AfxTrace("r1\n");
#endif
	OverLay.RenderInfoPanel();

#ifdef	_PROCDEBUG_
::AfxTrace("r2\n");
#endif
//DeadCode RJS 1Sep00 	Add_PeripheralVision();
#endif
//	9.	Stop movecode again....
#ifdef	_PROCDEBUG_
::AfxTrace("r3\n");
#endif
	View_Point->BlockTick(TRUE);
#ifdef	_PROCDEBUG_
::AfxTrace("r4\n");
#endif
#ifndef _NO_SHAPES_
	if (Manual_Pilot.ControlledAC2 &&
		!Manual_Pilot.ControlledAC2->Status.deadtime)
	{
		if (Key_Tests.KeyPress3d(INFOPANEL))			OverLay.StepInfoBarUp();
		if (Key_Tests.KeyPress3d(TOGGLEMESSAGES))
		{
			if (Save_Data.gamedifficulty[GD_DISPLAYMESSAGES])
				Save_Data.gamedifficulty%=GD_DISPLAYMESSAGES;
			else
				Save_Data.gamedifficulty|=GD_DISPLAYMESSAGES;
		}

//DEADCODE AMM 10/12/99 		if (Key_Tests.KeyPress3d(ASCII_h))
//DEADCODE AMM 10/12/99 			INT3;
//DEADCODE AMM 10/12/99 
//DEADCODE AMM 10/12/99 		if (Key_Tests.KeyPress3d(ASCII_H))
//DEADCODE AMM 10/12/99 			INT3;
//#pragma message(__HERE__"Test code for comms message dialog")

		if(		(Persons2::PlayerSeenAC->classtype->aerobaticfactor != AEROBATIC_LOW)	)	//CSB 21Jun00
//DeadCode CSB 18Sep00 			&&	(	((Persons2::PlayerSeenAC->movecode != AUTO_TRAININGTAKEOFF) && (Persons2::PlayerSeenAC->movecode != AUTO_TRAININGLANDING))
//DeadCode CSB 18Sep00 				||	(Art_Int.CountFormationSize(Persons2::PlayerSeenAC) > 1)	)	)
		{
			if(Key_Tests.KeyPress3d(RADIOCOMMS))
	//			OverLay.SetToCommsChatScr();
				OverLay.SetToRadioScreen();
			else if (Key_Tests.KeyPress3d(GROUPINFOMSG))	OverLay.HotKeyTriggerMenu(SEL_1);
			else if (Key_Tests.KeyPress3d(PRECOMBATMSG))	OverLay.HotKeyTriggerMenu(SEL_2);
			else if (Key_Tests.KeyPress3d(COMBATMSG))		OverLay.HotKeyTriggerMenu(SEL_3);
			else if (Key_Tests.KeyPress3d(POSTCOMBATMSG))	OverLay.HotKeyTriggerMenu(SEL_4);
			else if (Key_Tests.KeyPress3d(TOWERMSG))		OverLay.HotKeyTriggerMenu(SEL_5);
			else if (Key_Tests.KeyPress3d(FACMSG))			OverLay.HotKeyTriggerMenu(SEL_6);
			if (Key_Tests.KeyPress3d(ANYBANDITS))			OverLay.HotKeyTriggerMessage(SEL_3,SEL_3);
			if (Key_Tests.KeyPress3d(BREAK))				OverLay.HotKeyTriggerMessage(SEL_3,SEL_4);
			if (Key_Tests.KeyPress3d(CLEAR))				
			{
				if (Manual_Pilot.ControlledAC2->Leader()!=NULL)
				{
					OverLay.HotKeyTriggerMessage(SEL_3,SEL_6);
				}
				else
				{
					OverLay.HotKeyTriggerMessage(SEL_3,SEL_5);
				}
			}
		}
	}

//DEADCODE JON 4/6/00 	g_lpLib3d->End3DScene();

// Radio message and mouse process...
	OverLay.ProcessUIScreen();
#ifdef	_PROCDEBUG_
::AfxTrace("r5\n");
#endif
#endif
// Restart movecode...
	View_Point->BlockTick(FALSE);
#ifdef	_PROCDEBUG_
::AfxTrace("r6\n");
#endif
	g_lpLib3d->EndScene();
#ifdef	_PROCDEBUG_
::AfxTrace("r7\n");
#endif
	if (ZBufferFudge)											//RJS 08May00
		Land_Scape.SetFogBand();								//RJS 08May00

//deadcode JON 19/06/01		Land_Scape.ProcessStompMap();								//RJS 30Nov99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	init_scene
//LastModified:	PD 20Dec95
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	
//
//Description	Sets up variables/data required to render the world from a 
//			selected viewpoint.
//
//Inputs		viewpoint containing coordinate and angular info. required
//			to generate the view.	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::init_scene(WorldStuff *worldptr, ViewPoint* viewpoint)//PD 22Apr96
{
//DEAD 	POLYGON.MakeAliasTable();									//PD 25Mar96
//DEAD 	POLYGON.MakeLumTable();										//RJS 19Jan98

	current_world = worldptr;

 	viewer_x = viewpoint->World.X;
 	viewer_y = viewpoint->World.Y;
 	viewer_z = viewpoint->World.Z;

//DEADCODE RJS 3/31/00 	generate_matrix(*viewpoint);									//PD 20Dec95

	bt->Clear3DArea();
//TempCode PD 04Feb99 	aircraft_tree->Clear3DArea();								//PD 28Oct98

	SHAPE.UpdateGlobalFlags(viewpoint->DrawFrameTime());									//PD 08Mar96

	COORDS3D posn;
	GetSunPos(posn);

//DEADCODE JON 4/19/00 	Land_Scape.SetLVector(posn);

 	SunLightVector.ni.i = worldptr->sunpos.X;	
 	SunLightVector.nj.i = worldptr->sunpos.Y;	
 	SunLightVector.nk.i = worldptr->sunpos.Z;	
 
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		add_cockpit
//LastModified:	PD 20Jun96
//Author		Paul.   
//Date			Fri 26 Jan 1996
//
//Description	Inserts polygon cockpit at current viewer position
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::add_cockpit(rotitem& viewpoint,PitTypes pittype,ANGLES h,ANGLES p,ANGLES r)	//PD 20Jun96
{
	rotitem	tempitem,*tempitemptr=&tempitem;

	ShapeNum shape;

	ClassPtr clstyp=Manual_Pilot.ControlledAC2->classtype;
	Coords3D	eyepos;

//DeadCode RJS 28Feb00	if (View_Point->viewnum.viewmode!=VM_InPadlock)	shape=clstyp->cockpit1;
//DeadCode RJS 28Feb00	else 											shape=clstyp->cockpit2;
	shape = SHAPE.GetCockpitShape(eyepos);								//RJS 28Feb00

//DeadCode RJS 23Oct00 	Obj3D obj3d,*obj3dptr=&obj3d;
	Obj3D obj3d;													//RJS 23Oct00

	D3DVECTOR	eyeoff;

	cockScale = clstyp->cockscale;										//RJS 30May00

	eyeoff.x = D3DVALUE(-eyepos.X) * 0.0009765625;	// scale down by 1024
	eyeoff.y = D3DVALUE(-eyepos.Y) * 0.0009765625;
	eyeoff.z = D3DVALUE(-eyepos.Z) * 0.0009765625;

	tempitem.shape=shape;
	tempitem.World=viewpoint.World;
	tempitem.hdg=h;
	tempitem.pitch=p;
	tempitem.roll=r;
	animptr	adptr=Manual_Pilot.ControlledAC2->Anim;
//DeadCode RJS 20Oct00 	PolyPitAnimData* ppitanim=(PolyPitAnimData*)adptr;
	resetpit=FALSE;

	g_lpLib3d->PushMatrix(MATRIX_OBJECT);
	g_lpLib3d->PushMatrix(MATRIX_PROJECTION);
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
	if (theZBufferDepth < 24)
	{
//DeadCode JON 22Aug00 		g_lpLib3d->SetFogValues( 2.f, 2.f );
		g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,COCKPIT_NEARZ,3000,true);
		g_lpLib3d->EnableFogging( false );
	}
	else
	{
		g_lpLib3d->SetNearClipPlane( COCKPIT_NEARZ );
//DeadCode JON 29Aug00 		g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,10,Land_Scape.view_dist,true);
	}
//DeadCode JON 22Aug00 	g_lpLib3d->SetFogColour(fogCol);

//DeadCode RJS 07Feb00	obj3d.lptr=NULL;
//DeadCode RJS 07Feb00	obj3d.rptr=NULL;
	obj3d.realbz.f = 0;									//RJS 31Mar00
	obj3d.ItemPtr=Manual_Pilot.ControlledAC2;
	obj3d.AnimPtr=adptr;
	obj3d.Shape=tempitemptr->shape;
	obj3d.Body.X.f=0;//eyeoff.x;
	obj3d.Body.Y.f=0;//eyeoff.y;
	obj3d.Body.Z.f=0;//eyeoff.z;
 	obj3d.copySize=tempitemptr->Status.size;							//RJS 26May00
	obj3d.AngR=((rotitem*)tempitemptr)->roll;
	obj3d.AngC=((hpitem*)tempitemptr)->pitch;
	obj3d.AngH=((hdgitem *)tempitemptr)->hdg;
	obj3d.objtype=MOBILE_OBJECT;
	SHAPE.animate_shape(&obj3d,tempitemptr->World);
//DeadCode RJS 20Oct00 	ShapeDescPtr sdptr=SHAPESTUFF.GetShapePtr(shape);

	g_lpLib3d->Scale(MATRIX_OBJECT,cockScale);							//RJS 30May00
	g_lpLib3d->Translate(MATRIX_OBJECT,eyeoff);
	g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_ROLL,(Angles)-(int)obj3d.AngR);
	g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_PITCH,(Angles)-(int)obj3d.AngC);
	g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_HEADING,(Angles)(int)obj3d.AngH);

	SHAPE.process_shape(g_lpLib3d,View_Point,&obj3d,NULL,FALSE,NULL);

	tempitemptr->Status.Drawn=TRUE;

	SHAPE.TestInteractive((ShapeNum)obj3d.Shape,obj3d.AnimPtr);	//RJS 17Feb00

	g_lpLib3d->PopMatrix(MATRIX_OBJECT);
	g_lpLib3d->PopMatrix(MATRIX_PROJECTION);

	bt->Clear3DArea();

	tempitem.Anim=ANIM_NULL;	//This stops the item delete code from freeing animation//PD 16Apr96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Add_PeripheralVision
//Author		Paul.   
//Date			Tue 22 Jul 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Add_PeripheralVision(const ItemPtr	ac, const D3DVECTOR& pos)
{
	if (ac && !_Replay.Playback)										//RJS 14Sep00
	{
		R3DVERTEX	vertex;
		D3DVALUE	sx, sy, sz;

		vertex.x=pos.x;
		vertex.y=pos.y;
		vertex.z=pos.z;
		
		g_lpLib3d->BodyToScreen(vertex,sx,sy,sz);
		if (	(sz > 1.)										//RJS 19Sep00
			&&	(	(sx <= 1.)									//RJS 19Sep00
				||	(sx >= float(SHAPE.vd_width))						//RJS 13Oct00
				||	(sy <= 1.)									//RJS 19Sep00
				||	(sy >= float(SHAPE.vd_height))	))					//RJS 13Oct00
		{
			bool		isLW;											//RJS 6Sep00
			if (_DPlay.Implemented && _DPlay.GameType==DPlay::TEAMPLAY)
			{
				switch (AirStrucPtr(ac)->classtype->planetext)
				{
				case PT_SPIT_A:
				case PT_SPIT_B:
				case PT_HURR_A:
				case PT_HURR_B:
					isLW=false;
					break;
				case PT_ME109:
				case PT_ME110:
				case PT_JU87:
					isLW=true;
					break;
				}
			}
			else
			{
				if (AirStrucPtr(ac)->nationality != NAT_RAF)				//RJS 6Sep00
					isLW = true;											//RJS 6Sep00
				else														//RJS 6Sep00
					isLW = false;											//RJS 6Sep00
			}

			OverLay.AddPeripheralBlob(sx,sy,isLW);						//RJS 6Sep00
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Add_Sun
//Author		Paul.   
//Date			Mon 22 Apr 1996
//
//Description	Places sun based on delta in x,y given by earth's rotation.
//				Doesn't take into account axial tilt and sun goes overhead.
//				Are these the same problem? Modify dZ by season/latitude to fix? 
//				We only need to update the sun position about every 20 secs
//				as this gives 2000 updates /12 hours
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Add_Sun(rotitem* vp,WorldStuff *worldptr)
{
 	Coords3D	sunpos=vp->World;
 	SLong		xdist, ydist, zdist;						//RJS 16Jul97
 	vector		SunPos;										//RJS 16Jul97
	SunAnimData*	adptr = (SunAnimData*) sunanimptr;		//RJS 02Jul98

 	sunpos.X += worldptr->sunpos.X;								//RJS 23Mar98
 	sunpos.Y += worldptr->sunpos.Y;								//RJS 23Mar98
 	sunpos.Z += worldptr->sunpos.Z;								//RJS 23Mar98
	//scale sun distance so that it is always drawn infront of
	//the horizon polygons...
	//Land_Scape.ScaleInsideHorizon(sunpos);
 
// move to init scene
//DEADCODE JON 4/14/00  	SunLightVector.ni.i = worldptr->sunpos.X;	//sunpos.X;
//DEADCODE JON 4/14/00  	SunLightVector.nj.i = worldptr->sunpos.Y;	//sunpos.Y;
//DEADCODE JON 4/14/00  	SunLightVector.nk.i = worldptr->sunpos.Z;	//sunpos.Z;
 
 	//This assumes the sun goes directly overhead
 
 	SHAPE.SunInVision = FALSE;								//PD 27Nov96
 
//DeadCode RJS 30May00  	itemptr	sunitemp = new item;
//DeadCode RJS 30May00   	sunitemp->shape=SUN;							//RJS 29Sep97
  	sunItemP->World = sunpos;											//RJS 30May00

 	//PD 27Nov96 - fix to stop sun not being drawn 'cos
 	//it's too far away
 	SLong	oldfaderange=Land_Scape.fade_band_end;		//PD 27Nov96
 	Land_Scape.fade_band_end=0x7FFFFFFF;				//PD 27Nov96

	if (sunpos.Y > (-354<<4))											//RJS 4Oct00
	{
		// Sun starts to fade below 30degrees.
		SLong	horizfade = worldptr->sunrot;
		if (horizfade < 0)
			horizfade = -horizfade;

		if (horizfade < ANGLES_30Deg)
			horizfade = (255 * horizfade)/ANGLES_30Deg;
		else
			horizfade = 255;

// Do we want to see a moon?
		if (!lightson)
			adptr->itemstate = ALIVE;
		else
			adptr->itemstate = DEAD;

		adptr->fader = horizfade;

 		do_object_dummy(sunItemP,STATIC_OBJECT,sunItemP);					//RJS 30May00
	}

 	Land_Scape.fade_band_end=oldfaderange;				//PD 27Nov96
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		Add_Shadow
//Author		Robert Slater
//Date			Thu 24 Apr 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::Add_Shadow(AirStrucPtr	ac, bool dopiloted)
{
	if (!Save_Data.detail_3d[DETAIL3D_AIRCRAFTSHADOWS])
		return;

	if (dopiloted || (ac != Manual_Pilot.ControlledAC2))		//RJS 13Jul98
	{
		//Fix for supermigs & pdeaths...
		if (	(ac->classtype->visible == ac->shape)					//RJS 11Aug00
			&&	(ac->World.Y > -50)		)		//are we under the sea?	//RJS 11Aug00
		{
			MinAnimData*	mad = (MinAnimData*) ac->Anim;
			if (mad->itemstate != DEAD)
			{
				rotitem*		shaditem;
				ANGLES			newhdg,newpitch,newroll;
				rotitem	myshaditem;
				shaditem = &myshaditem;//new rotitem;
				if (shaditem)
				{
					Coords3D	shadpos;
					Coords3D	acworld = ac->World;					//CSB 02/03/00

					SLong	vdx,vdy,vdz;

					fastMath.FloatToInt(&vdx,velCorrect_x);//float(Float(ac->vel_x + wind_x)*fView_dt_frac));//RJS 31Mar00
					fastMath.FloatToInt(&vdy,velCorrect_y);//float(Float(ac->vel_y + wind_y)*fView_dt_frac));//RJS 31Mar00
					fastMath.FloatToInt(&vdz,velCorrect_z);//float(Float(ac->vel_z + wind_z)*fView_dt_frac));//RJS 31Mar00

					acworld.X += vdx;
					acworld.Y += vdy;
					acworld.Z += vdz;

					if (mobileitem::currworld->sunpos.Y > (acworld.Y+5000))	//RJS 20Sep00
					{
						SLong	heightOffGround = acworld.Y - ac->fly.pModel->GroundHeight;
						float	scale = float(heightOffGround) / float(mobileitem::currworld->sunpos.Y);
						float	xoffset;
						float	zoffset;

						shadpos.Y = ac->fly.pModel->GroundHeight;

// Linear scale down (once under 10m) so shadow is always under the aircraft when landed
						if (heightOffGround < 1000)
						{
// Set 2m to clip value...
							if (heightOffGround < 200)
								scale = 0;
							else
								scale = scale * (float(heightOffGround-200)/800.f);
						}

						xoffset = scale * float(-mobileitem::currworld->sunpos.X);
						zoffset = scale * float(-mobileitem::currworld->sunpos.Z);

						fastMath.FloatToInt(&vdx,xoffset);
						fastMath.FloatToInt(&vdz,zoffset);

						shadpos.X = acworld.X + vdx;
						shadpos.Z = acworld.Z + vdz;

//DeadCode RJS 20Sep00 						shadpos.X = acworld.X + scale * FP(-mobileitem::currworld->sunpos.X);
//DeadCode RJS 20Sep00 						shadpos.Y = ac->fly.pModel->GroundHeight;
//DeadCode RJS 20Sep00 						shadpos.Z = acworld.Z + scale * FP(- mobileitem::currworld->sunpos.Z);
//DeadCode RJS 20Sep00 
//DeadCode RJS 20Sep00 						if(		(shadpos.X - acworld.X > -100000) && (shadpos.X - acworld.X < 100000) 
//DeadCode RJS 20Sep00 							&&	(shadpos.Z - acworld.Z > -100000) && (shadpos.Z - acworld.Z < 100000)	)
						if ((xoffset*xoffset+zoffset*zoffset)<(150000.*150000.))
						{
							shaditem->shape = ac->classtype->shadowshpno;
							shaditem->World = shadpos;

							newhdg = ac->hdg;

							pMigLand->GetShadowAngles(shaditem->World,newhdg,newpitch,newroll);

							shaditem->World.Y += 16;
							shaditem->hdg = newhdg;
							shaditem->pitch = newpitch;
							shaditem->roll = newroll;
							shaditem->Anim = ac->Anim;

							do_object_shad(shaditem,ac);
						}
					}
					
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99  					shaditem->shape = ac->classtype->shadowshpno;
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					shaditem->World = ac->World;
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 //#pragma warnmsg("Paul: timerFudgeFactor is garbage!")
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 ////TEMPCODE JIM 08/04/99 				shaditem->World.X += (View_Point->timerFudgeFactor * ac->velx)/100;//PD 19Sep97
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 ////TEMPCODE JIM 08/04/99 				shaditem->World.Z += (View_Point->timerFudgeFactor * ac->velz)/100;//PD 19Sep97
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 ////TEMPCODE JIM 08/04/99 
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					newhdg = ac->hdg;
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					pMigLand->GetShadowAngles(shaditem->World,newhdg,newpitch,newroll);
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					shaditem->hdg = newhdg;
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					shaditem->pitch = newpitch;
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					shaditem->roll = newroll;
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					shaditem->Anim = ac->Anim;
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					do_object_shad(shaditem,ac);
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					shaditem->Anim = NULL;
//DeadCode CSB 1Sep00 //DeadCode DAW 30Jun99 					delete (shaditem);
//DeadCode CSB 1Sep00 					Coords3D	shadpos=View_Point->World;
//DeadCode CSB 1Sep00 					Coords3D	acworld = ac->World;					//CSB 02/03/00
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 					SLong	vdx,vdy,vdz;
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 					fastMath.FloatToInt(&vdx,float(Float(ac->vel_x)*fView_dt_frac));//RJS 31Mar00
//DeadCode CSB 1Sep00 					fastMath.FloatToInt(&vdy,float(Float(ac->vel_y)*fView_dt_frac));//RJS 31Mar00
//DeadCode CSB 1Sep00 					fastMath.FloatToInt(&vdz,float(Float(ac->vel_z)*fView_dt_frac));//RJS 31Mar00
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 					acworld.X += vdx;
//DeadCode CSB 1Sep00 					acworld.Y += vdy;
//DeadCode CSB 1Sep00 					acworld.Z += vdz;
//DeadCode CSB 1Sep00 //DEADCODE RJS 3/31/00 					acworld.X += SLong(ac->vel_x * view_dt) / 1e5;		//CSB 02/03/00
//DeadCode CSB 1Sep00 //DEADCODE RJS 3/31/00 					acworld.Y += SLong(ac->vel_y * view_dt) / 1e5;		//CSB 02/03/00
//DeadCode CSB 1Sep00 //DEADCODE RJS 3/31/00 					acworld.Z += SLong(ac->vel_z * view_dt) / 1e5;		//CSB 02/03/00
//DeadCode CSB 1Sep00  
//DeadCode CSB 1Sep00 					shadpos.X += mobileitem::currworld->sunpos.X;								
//DeadCode CSB 1Sep00  					shadpos.Y += mobileitem::currworld->sunpos.Y;
//DeadCode CSB 1Sep00  					shadpos.Z += mobileitem::currworld->sunpos.Z;
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 					if (shadpos.Y > acworld.Y)							//RJS 9Aug00
//DeadCode CSB 1Sep00 					{
//DeadCode CSB 1Sep00  						shaditem->shape = ac->classtype->shadowshpno;
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 						SLong	glevel;
//DeadCode CSB 1Sep00 						if (ac->fly.pModel->GroundHeight)	//crap fix
//DeadCode CSB 1Sep00 							glevel = ac->fly.pModel->GroundHeight;
//DeadCode CSB 1Sep00 						else
//DeadCode CSB 1Sep00 							glevel = acworld.Y - 200;		//crap fix		//CSB 02/03/00
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 						SLong	ixpos,izpos;
//DeadCode CSB 1Sep00 						Float	xpos, zpos;
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 						SLong	heightsun = shadpos.Y - glevel;
//DeadCode CSB 1Sep00 						if (heightsun > 5000)
//DeadCode CSB 1Sep00 						{
//DeadCode CSB 1Sep00 							SLong	heightac = ac->World.Y - glevel;
//DeadCode CSB 1Sep00 //DeadCode RJS 22Aug00 							SLong	ixpos,izpos;
//DeadCode CSB 1Sep00 //DeadCode RJS 22Aug00 							Float	xpos, zpos;
//DeadCode CSB 1Sep00 							Float	heightscale = Float(heightac);
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							heightscale *= 0.2;
//DeadCode CSB 1Sep00 							heightscale /= Float(heightsun);
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							ixpos = acworld.X - shadpos.X;					//CSB 02/03/00
//DeadCode CSB 1Sep00 							izpos = acworld.Z - shadpos.Z;					//CSB 02/03/00
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							xpos = Float(ixpos);
//DeadCode CSB 1Sep00 							zpos = Float(izpos);
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							xpos *= heightscale;
//DeadCode CSB 1Sep00 							zpos *= heightscale;
//DeadCode CSB 1Sep00 						}
//DeadCode CSB 1Sep00 						else
//DeadCode CSB 1Sep00 							xpos = zpos = 0;
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 //DeadCode RJS 9Aug00 							ixpos = SLong(xpos);			
//DeadCode CSB 1Sep00 //DeadCode RJS 9Aug00 							izpos = SLong(zpos);			
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 						if (	((xpos < 100000.) && (xpos > -100000.))
//DeadCode CSB 1Sep00 							&&	((zpos < 100000.) && (zpos > -100000.))	)
//DeadCode CSB 1Sep00 						{
//DeadCode CSB 1Sep00 							ixpos = SLong(xpos);					//RJS 9Aug00
//DeadCode CSB 1Sep00 							izpos = SLong(zpos);					//RJS 9Aug00
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							shaditem->World.X = acworld.X + ixpos;		//CSB 02/03/00
//DeadCode CSB 1Sep00 							shaditem->World.Z = acworld.Z + izpos;		//CSB 02/03/00
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							newhdg = ac->hdg;
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							pMigLand->GetShadowAngles(shaditem->World,newhdg,newpitch,newroll);
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							shaditem->World.Y += 16;
//DeadCode CSB 1Sep00 							shaditem->hdg = newhdg;
//DeadCode CSB 1Sep00 							shaditem->pitch = newpitch;
//DeadCode CSB 1Sep00 							shaditem->roll = newroll;
//DeadCode CSB 1Sep00 							shaditem->Anim = ac->Anim;
//DeadCode CSB 1Sep00 
//DeadCode CSB 1Sep00 							do_object_shad(shaditem,ac);
//DeadCode CSB 1Sep00 						}
//DeadCode CSB 1Sep00 					}

					shaditem->Anim = ANIM_NULL;
					//delete (shaditem);
				}
			}
		}
	}															//RJS 13Jul98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddLensObject
//Author		Robert Slater
//Date			Thu 15 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::AddLensObject(DoPointStruc	*dopointP, ShapeNum	shpno, int	frameno,int fader)
{
#ifndef	_NO_LENSFLARE_
		itemptr			tempitemptr = new item;
		FlareAnimData	*adptr;
		int				noObjects;
		D3DVECTOR		pos;

		pos.x = dopointP->getPosX();
		pos.y = dopointP->getPosY();
		pos.z = dopointP->getPosZ();

		tempitemptr->shape = shpno;
		tempitemptr->World = View_Point->World;
		tempitemptr->Anim = lensflareanim;							//RJS 03May00

		Obj3DPtr	obj3dptr = (Obj3DPtr)StuffIntoVisibleList(tempitemptr,10,pos,STATIC_OBJECT);
		obj3dptr->ItemPtr = NULL;

		adptr = (FlareAnimData*) lensflareanim;
		adptr->colstep = frameno;
		adptr->depth = fader;											//RJS 23Jun00
//DeadCode JON 23Jun00 		adptr->depth = 64 + ((fader*191)/255);							//RJS 20Jun00

		tempitemptr->Anim = ANIM_NULL;								//RJS 07Dec99

		delete tempitemptr;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddVapourObject
//Author		Robert Slater
//Date			Mon 8 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong ThreeDee::AddVapourObject(ShapeNum	shape,
								UByteP		apoint1,
								UByteP		prevobj3d,
								UByteP		&thisobj3d,
								UWord		failedcnt)
{
	SLong		distz;
	rotitem*	VapItemP = new rotitem;
	if (VapItemP)
	{
		SLong		wx, wy, wz;
		Coords3DList*	currpoint = (Coords3DList*) apoint1;	//RJS 21Apr99
		ULongP		lastobjptr = (ULongP) &VapItemP->hdg;			//RJS 17Sep97

		wx = currpoint->trailpoint.gx;								//RJS 17Sep97
		wy = currpoint->trailpoint.gy;								//RJS 17Sep97
		wz = currpoint->trailpoint.gz;								//RJS 17Sep97

		VapItemP->shape = shape;
 		VapItemP->World.X = wx;
 		VapItemP->World.Y = wy;
 		VapItemP->World.Z = wz;
		*lastobjptr = (ULong) prevobj3d;							//RJS 17Sep97
 		VapItemP->roll = ANGLES_0Deg;								//RJS 17Sep97
		VapItemP->Anim = apoint1;									//RJS 17Sep97
		VapItemP->Anim = (AnimFlagField)(1<<MINANIM);				//RJS 21Apr99

		distz = do_object_vapour(VapItemP,thisobj3d,failedcnt);		//RJS 17Sep97

 		VapItemP->Anim = ANIM_NULL;

		delete (VapItemP);
	}
	else
	{
		distz = 0;
		thisobj3d = NULL;
	}

	return(distz);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	render_scene
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	
//
//Description	Draws objects in the order contained in the binary tree.
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::render_scene()
{
//DeadCode RJS 07Feb00	bt->draw_object(g_lpLib3d,View_Point);							//PD 20Dec95
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	exit_3D
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	
//
//Description	Deallocate buffers and tidy up
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::exit_3D()
{
	havematrix = false;				//RJS 10Dec98
	delete fpviewer_matrix;
	delete fpinverse_matrix;

//DeadCode RJS 19Sep00 	SLong	rfps = View_Point->RealDrawFrameTime();		//RJS 05Apr00
//DeadCode RJS 19Sep00 	if (rfps)											//RJS 28May99
//DeadCode RJS 19Sep00 		Trans_Obj.realFrameTime = 100 / rfps;			//RJS 28May99
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	generate_matrix
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	
//
//Description	
//
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::generate_matrix(rotitem& viewpoint)
{

	fpviewer_matrix = new FPMATRIX;
	fpinverse_matrix = new FPMATRIX;

	viewer_hdg=viewpoint.hdg;
	viewer_pitch=viewpoint.pitch;
	viewer_roll=viewpoint.roll;

	_matrix.Generate(viewer_hdg,viewer_pitch,viewer_roll,fpviewer_matrix);
	_matrix.inverse(viewer_hdg,viewer_pitch,viewer_roll,fpinverse_matrix);

	_matrix.GenerateXY(SHAPE.SphereXScale,SHAPE.SphereYScale);	//RJS 02Dec98

	havematrix = true;			//RJS 10Dec98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetDistance
//Author		Martin Alderton
//Date			Tue 14 Nov 1995
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ULong ThreeDee::GetDistance(Obj3DPtr thisobj3d)					//PD 13Mar96
{
	ULong dist = 0;
	if (thisobj3d->ItemPtr)										//RJS 15Nov00
	{
		SLong dx,dy,dz;

		dx= viewer_x - thisobj3d->ItemPtr->World.X;
		dy= viewer_y - thisobj3d->ItemPtr->World.Y;
		dz= viewer_z - thisobj3d->ItemPtr->World.Z;

	 	dist = Math_Lib.distance3d(dx,dy,dz);						//PD 29Nov95
	}

	return(dist);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		zClipLine
//Author		Martin Alderton
//Date			Mon 20 Nov 1995
//
//Description	takes in two dopointstrucs works out where (if anywhere) they
//				cross the zclipping planes and adjusts the bodyx and bodyy
//				coordinates of each point as required. Hey Presto a line
//				clipped in the z plane ready to go to ClipLine function
//
//Inputs		2* dopointstruc
//
//Returns		2 * adjusted DoPointStruc	
//
//------------------------------------------------------------------------------
Bool ThreeDee::zclipline(Bool draw,DoPointStruc /*start_vertex*/,DoPointStruc /*end_vertex*/)//PD 15Jan96
{
	return(draw);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IntensFromRange
//Author		Paul.   
//Date			Tue 9 Jan 1996
//
//Description	Returns an intensity value in the range 0..255 based
//				on position within start and end ranges
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SWord ThreeDee::IntensFromRange(SLong& range,
								SLong& fade_band_start,
								SLong& fade_band_end)
{
	if (range<=fade_band_start)	return (0);

	if (range>=fade_band_end)	return (255);

	SLong	rangedelta,fadedelta;

	SWord	retval;

	fadedelta = range - fade_band_start;

	rangedelta = fade_band_end - fade_band_start;				//PD 18Dec96

	if (fadedelta<0x7FFFFF)
		retval = (fadedelta<<8)/rangedelta;
	else
		retval = (fadedelta/(rangedelta>>8));

	//Clip to max and min.

	if (retval<0)		retval=0x00;
	if (retval>0xFF)	retval=0xFF;

	return(retval);
}

inline SLong D3Distance(SLong a,SLong b,SLong c)
{
//DEADCODE RJS 5/8/00 	SLong	max,med,min,temp;
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	max = a<0?-a:a; med = b<0?-b:b; min = c<0?-c:c;
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	if (max < med )
//DEADCODE RJS 5/8/00 	{
//DEADCODE RJS 5/8/00 		temp = max; max = med; med = temp;
//DEADCODE RJS 5/8/00 	}
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	if (max < min)
//DEADCODE RJS 5/8/00 	{
//DEADCODE RJS 5/8/00 		temp = max; max = min; min = max;
//DEADCODE RJS 5/8/00 	}
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	if (med < min)
//DEADCODE RJS 5/8/00 	{
//DEADCODE RJS 5/8/00 		temp = med; med = min; min = temp;
//DEADCODE RJS 5/8/00 	}
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	// Now max > med > min
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	temp = med >> 2;	//	1/4 med
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	med = temp;
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	temp >>= 2;			//	1/16 med
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	med += temp;
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	temp >>= 1;			//	1/32 med
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	med += temp;
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	min	>>= 2;			//	1/4 min
//DEADCODE RJS 5/8/00 
//DEADCODE RJS 5/8/00 	return max + med + min;
	float	dx = float(a);
	float	dy = float(b);
	float	dz = float(c);
	ULong	dist;

	dist = fastMath.DoubleToULong(Float(fastMath.FastSqrt(dx*dx+dy*dy+dz*dz)));

	return SLong(dist);
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure	do_objects
//LastModified:	PD 14Jun96
//------------------------------------------------------------------------------
//Author		Paul.   
//Date		Tue 22 Aug 1995
//Modified	Simplified nesting...	//JIM 12Aug96
//
//Description	Scans the world area around the viewpoint and sorts objects
//			into a binary tree (same as old engine).
//			Ignores items in different world wrap				//JIM 12Aug96
//			Ignores piloted A/C if inside view					//JIM 12Aug96
//Inputs	
//
//Returns	
//
//Externals
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ThreeDee::do_objects()
{
//Old_Code RJS 04Feb00 	Land_Scape.ResetItemLog(); /* for software landscape sorting */
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	ShapeDescPtr	sdp;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	int		i,j;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	item 	tempitem,
//Old_Code RJS 04Feb00 			*tempitemptr,
//Old_Code RJS 04Feb00 			*previtmptr;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	UWord	sector_x,
//Old_Code RJS 04Feb00 			sector_y,
//Old_Code RJS 04Feb00 			current_sector_x,
//Old_Code RJS 04Feb00 			current_sector_y,
//Old_Code RJS 04Feb00 			this_sector;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	Bool	dopilotedshad = FALSE;
//Old_Code RJS 04Feb00 	Bool	isPiloted = FALSE;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	if (!View_Point->PolyPitEnabled() && (View_Point->viewnum.viewmode!=VM_InsideCheat && View_Point->viewnum.viewmode!=VM_Inside))
//Old_Code RJS 04Feb00 		dopilotedshad = TRUE;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	tempitem.World.X = viewer_x;
//Old_Code RJS 04Feb00 	tempitem.World.Y = viewer_y;
//Old_Code RJS 04Feb00 	tempitem.World.Z = viewer_z;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	tempitemptr = &tempitem;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	current_world->getsectornos(tempitemptr,sector_x,sector_y);
//Old_Code RJS 04Feb00 	ResetPosRec();
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	//Draw a 3x3 grid of sectors around the viewer
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	int	sectorcount = 12;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	// Ensure smoke trail points are all sampled once if paused....
//Old_Code RJS 04Feb00 	if (!IsPaused())														//RJS 16Apr98
//Old_Code RJS 04Feb00 		SHAPE.SamplePntTime = TRUE;											//RJS 16Apr98
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	previtmptr=NULL;
//Old_Code RJS 04Feb00 	for(current_sector_x = sector_x-1;sectorcount;current_sector_x++)
//Old_Code RJS 04Feb00 	{
//Old_Code RJS 04Feb00 		//sc test&dec occurs 4 times per yloop of 3 times
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 		for(current_sector_y = sector_y-1;--sectorcount&3;current_sector_y++)
//Old_Code RJS 04Feb00 		{
//Old_Code RJS 04Feb00 			bool itemLogged=false;	/* for software landscape sort */
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 			this_sector =
//Old_Code RJS 04Feb00 				current_world->makeindex(current_sector_x,current_sector_y);
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 			tempitemptr =
//Old_Code RJS 04Feb00 				current_world->getfirstitem(this_sector);
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 			while (tempitemptr)
//Old_Code RJS 04Feb00 			{
//Old_Code RJS 04Feb00 				Bool  itemdisabled=FALSE;
//Old_Code RJS 04Feb00 		
//Old_Code RJS 04Feb00 				if (current_world->SameSector(tempitemptr,*View_Point) &&
//Old_Code RJS 04Feb00 					!itemdisabled)
//Old_Code RJS 04Feb00 				{
//Old_Code RJS 04Feb00 					sdp = SHAPESTUFF.GetShapePtr(tempitemptr->shape);
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 					SLong rangemax = sdp->MaxDrawRange;		//RJS 22Jan99
//Old_Code RJS 04Feb00 					SLong rng=D3Distance(	tempitemptr->World.X-View_Point->World.X,
//Old_Code RJS 04Feb00 											tempitemptr->World.Y-View_Point->World.Y,
//Old_Code RJS 04Feb00 											tempitemptr->World.Z-View_Point->World.Z);
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 					if (tempitemptr->Status.size==AirStrucSize)	//RJS 04Jun98
//Old_Code RJS 04Feb00 					{
//Old_Code RJS 04Feb00 						StoreAcPos(tempitemptr);
//Old_Code RJS 04Feb00 						rangemax = RANGE_AIRCRAFT_FLASH;		//RJS 04Jun98
//Old_Code RJS 04Feb00 						isPiloted = TRUE;									//RJS 08Sep98
//Old_Code RJS 04Feb00 						if (rng < RANGE_SHADOW)					//RJS 13Jul98
//Old_Code RJS 04Feb00 							Add_Shadow(objectRec,(AirStrucPtr)tempitemptr,dopilotedshad);//RJS 13Jul98
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 						if (	(tempitemptr != Persons2::PlayerGhostAC)	//RJS 07Sep98
//Old_Code RJS 04Feb00 							&&	(tempitemptr != Persons2::PlayerSeenAC)	)	//RJS 07Sep98
//Old_Code RJS 04Feb00 						{									
//Old_Code RJS 04Feb00 							isPiloted = FALSE;								//RJS 08Sep98
//Old_Code RJS 04Feb00 							if (rng < RANGE_FLYBYFAST)		
//Old_Code RJS 04Feb00 								DoFlyBySound((AirStrucPtr)tempitemptr,rng);
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 							if (radarOn && View_Point->PolyPitEnabled())//RJS 09Nov98
//Old_Code RJS 04Feb00 								SHAPE.GetRadarItem(tempitemptr,rng);//RJS 09Nov98
//Old_Code RJS 04Feb00 						}										//RJS 07Sep98
//Old_Code RJS 04Feb00 					}
//Old_Code RJS 04Feb00 					else										//RJS 04Jun98
//Old_Code RJS 04Feb00 					{
//Old_Code RJS 04Feb00 						if (	groundlockOn									//RJS 10Jun99
//Old_Code RJS 04Feb00 							&&	(tempitemptr->Status.size != TRANSIENTSIZE)		//RJS 10Jun99
//Old_Code RJS 04Feb00 							&&	View_Point->PolyPitEnabled()	)				//RJS 10Jun99
//Old_Code RJS 04Feb00 							SHAPE.GetRadarItem(tempitemptr,rng);//RJS 04Jun99
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 						isPiloted = FALSE;
//Old_Code RJS 04Feb00 					}
//Old_Code RJS 04Feb00 																//RJS 04Jun98
//Old_Code RJS 04Feb00 					if (rng<=rangemax)							//RJS 04Jun98
//Old_Code RJS 04Feb00 					{
//Old_Code RJS 04Feb00 						SLong	oldfaderange=Land_Scape.fade_band_end;//PD 19Dec96
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 						if (rangemax==RANGE_AIRCRAFT_FLASH)		//RJS 04Jun98
//Old_Code RJS 04Feb00 							Land_Scape.fade_band_end=0x7FFFFFFF;//RJS 04Jun98
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 						/* for software landscape sorting */
//Old_Code RJS 04Feb00 						if (!itemLogged) 
//Old_Code RJS 04Feb00 							itemLogged=Land_Scape.LogItem(viewer_x,viewer_z,tempitemptr->World);
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 						switch(SHAPESTUFF.GetShapeScale(sdp))
//Old_Code RJS 04Feb00 						{
//Old_Code RJS 04Feb00 							case SHP_GRP:
//Old_Code RJS 04Feb00  								do_object_grp(tempitemptr);
//Old_Code RJS 04Feb00 								break;
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 							case SHP_1CM:
//Old_Code RJS 04Feb00 							case SHP_4CM:
//Old_Code RJS 04Feb00 							case SHP_16CM:
//Old_Code RJS 04Feb00 								if (dopilotedshad)//RJS 02Sep98
//Old_Code RJS 04Feb00 								{
//Old_Code RJS 04Feb00 #ifndef NDEBUG
//Old_Code RJS 04Feb00 // dont delete these lines!!!! I use them often for testing
//Old_Code RJS 04Feb00 									if (_DPlay.SpookyGhostMode)
//Old_Code RJS 04Feb00 									{
//Old_Code RJS 04Feb00 										if (tempitemptr==Persons2::PlayerSeenAC)
//Old_Code RJS 04Feb00 										{
//Old_Code RJS 04Feb00 											do_object(Persons2::PlayerGhostAC);
//Old_Code RJS 04Feb00 										}
//Old_Code RJS 04Feb00 									}
//Old_Code RJS 04Feb00 #endif
//Old_Code RJS 04Feb00 										do_object(tempitemptr);
//Old_Code RJS 04Feb00 								}
//Old_Code RJS 04Feb00 								else if (isPiloted == FALSE)
//Old_Code RJS 04Feb00 									do_object(tempitemptr);
//Old_Code RJS 04Feb00 								break;
//Old_Code RJS 04Feb00 						}
//Old_Code RJS 04Feb00 						Land_Scape.fade_band_end=oldfaderange;	//PD 19Dec96
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 					}
//Old_Code RJS 04Feb00 				}
//Old_Code RJS 04Feb00 				previtmptr = tempitemptr;		//RJS 27Apr99
//Old_Code RJS 04Feb00 			 	tempitemptr = tempitemptr->Next;
//Old_Code RJS 04Feb00 			}
//Old_Code RJS 04Feb00 		}
//Old_Code RJS 04Feb00 	}
//Old_Code RJS 04Feb00 
//Old_Code RJS 04Feb00 	// Lock smoke trail point sampling....
//Old_Code RJS 04Feb00 	if (IsPaused())															//RJS 16Apr98
//Old_Code RJS 04Feb00 		SHAPE.SamplePntTime = FALSE;										//RJS 16Apr98
//Old_Code RJS 04Feb00 	else
//Old_Code RJS 04Feb00 		SHAPE.SamplePntTime = TRUE;								//RJS 23Nov98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_ui_objects
//Author		Robert Slater
//Date			Mon 12 Jun 2000
//
//Description	Don't care if they are within range, just draw them...
//				(Photo Screen)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_ui_objects()
{
	ShapeDescPtr		sdp;
	float				drelx,drely,drelz,fDist;
	SLong				rng;
	ITEM_STATUS 		copySize;
	itemptr 			tempitemptr = itemptr(current_world->pMapItemHead);
	btree::ObjectRec	*objectRec;
	
	objectRec=&bt->objectRec;
	objectRec->numItems=0;

	velCorrect_x = velCorrect_y = velCorrect_z = 0;						//RJS 25Sep00

	while (tempitemptr)
	{
		copySize = tempitemptr->Status;									//RJS 7Nov00
		if (	(copySize.size >= ITEMSIZE)									//RJS 7Nov00
			&&	(copySize.size < TRANSIENTSIZE)	)							//RJS 7Nov00
		{
			sdp=SHAPESTUFF.GetShapePtr(tempitemptr->shape);
				
			tempitemptr->Status.size=ITEMSIZE;

			if (!tempitemptr->World.Y)	tempitemptr->World.Y=_Collide.AccurateGroundAltitude(tempitemptr->World);

			drelx = float(tempitemptr->World.X) - float(viewer_x);
			drely = float(tempitemptr->World.Y) - float(viewer_y);
			drelz = float(tempitemptr->World.Z) - float(viewer_z);
			fDist = drelx*drelx + drely*drely + drelz*drelz;
			fastMath.FloatToInt(&rng,fastMath.FastSqrt(fDist));

			switch(SHAPESTUFF.GetShapeScale(sdp))
			{
			case SHP_GRP:
				ExpandPhotoGroup(objectRec,tempitemptr,rng);
				break;
			case SHP_1CM:
			case SHP_4CM:
			case SHP_16CM:
				AddToObjectRec(objectRec,tempitemptr,sdp->Size<<4,rng);
				tempitemptr->Status = copySize;
				break;
			}

			tempitemptr->Status = copySize;
		}
		tempitemptr = tempitemptr->Next;
	}

//Set visible flags...
	somethingvisible=false;												//RJS 23Aug00

	if (objectRec->numItems > 0)
	{
		g_lpLib3d->PushMatrix(MATRIX_OBJECT);
		g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

		g_lpLib3d->VisibleCheck(objectRec->pos,objectRec->rad,objectRec->numItems,objectRec->itemFlag);

		for (int i=0; i < objectRec->numItems; i++)						//RJS 25Sep00
		{
//DeadCode RJS 25Sep00 			sdp = SHAPESTUFF.GetShapePtr(objectRec->obj3d[i].Shape);
//DeadCode RJS 25Sep00 			tempitemptr=objectRec->obj3d[i].ItemPtr;
			if (0L==objectRec->itemFlag[i])
			{
				somethingvisible = true;
				SetObjectAngles(&objectRec->obj3d[i]);

//DeadCode RJS 25Sep00 				if (tempitemptr)
//DeadCode RJS 25Sep00 				{
//DeadCode RJS 25Sep00 					tempitemptr->Status.Drawn = TRUE;
//DeadCode RJS 25Sep00 
//TempCode RJS 12Jun00 					SHAPE.animate_shape(&objectRec->obj3d[i],tempitemptr->World);
//DeadCode RJS 25Sep00 				}
			}
		}
		
		g_lpLib3d->PopMatrix(MATRIX_OBJECT);
	}

	objectRec->somethingvisible = somethingvisible;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object
//Author		Paul.   
//Date			Fri 8 Mar 1996
//
//Description	Transform and insert a simple shape
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_object(itemptr tempitemptr)
{
//DeadCode RJS 07Feb00 	if (tempitemptr->Anim==NULL)								//RJS 21Apr99
//DeadCode RJS 07Feb00 		SHAPE.SetAnimData(tempitemptr,0);						//RDH 23Sep96
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	//New test to see if we want to draw or not...
//DeadCode RJS 07Feb00 	MinAnimData*	mad = (MinAnimData*)tempitemptr->Anim;
//DeadCode RJS 07Feb00 	if (!mad->IsInvisible)										//RJS 17Nov98
//DeadCode RJS 07Feb00 	{
//DeadCode RJS 07Feb00 		Obj3DPtr	obj3dptr;										//PD 13Mar96
//DeadCode RJS 07Feb00 		IFShare		wx,wy,wz;
//DeadCode RJS 07Feb00 		btree*		which_tree;
//DeadCode RJS 07Feb00 		bool		beenfixed = false;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			which_tree=bt;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		IFShare			bzoffset;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		ShapeDescPtr	sdptr;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		if(tempitemptr->World.Y==0)
//DeadCode RJS 07Feb00 		{
//DeadCode RJS 07Feb00 			tempitemptr->World.Y = _Collide.AccurateGroundAltitude(tempitemptr->World);//PD 08Oct96
//DeadCode RJS 07Feb00 			beenfixed = true;
//DeadCode RJS 07Feb00 		}
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		wx.i = tempitemptr->World.X - viewer_x;
//DeadCode RJS 07Feb00 		wy.i = tempitemptr->World.Y - viewer_y;
//DeadCode RJS 07Feb00 		wz.i = tempitemptr->World.Z - viewer_z;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		_matrix.transform(fpviewer_matrix,wx,wy,wz);
//DeadCode RJS 07Feb00 		if (tempitemptr->Status.size == TRANSIENTSIZE)			//RJS 27Nov98
//DeadCode RJS 07Feb00 		{
//DeadCode RJS 07Feb00 			UWord	offset = ((TransientItem*)tempitemptr)->DrawOffset;
//DeadCode RJS 07Feb00 			if (offset)
//DeadCode RJS 07Feb00 			{
//DeadCode RJS 07Feb00 				// scale the 3d coords so the object is drawn closer...
//DeadCode RJS 07Feb00 				Float	newz = wz.f - Float(offset);
//DeadCode RJS 07Feb00 				Float	dscale = newz / wz.f;
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 				wx.f *= dscale;
//DeadCode RJS 07Feb00 				wy.f *= dscale;
//DeadCode RJS 07Feb00 				wz.f = newz;
//DeadCode RJS 07Feb00 			}
//DeadCode RJS 07Feb00 		}
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		sdptr = SHAPESTUFF.GetShapePtr(tempitemptr->shape);		//RJS 29May97
//DeadCode RJS 07Feb00 		int	shpsize = sdptr->Size<<4;								//RJS 20Aug98
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 		if(RoughCone(wx,wy,wz,shpsize))								//RJS 15Dec99
//DeadCode RJS 07Feb00 		{															//RJS 09Jul98
//DeadCode RJS 07Feb00  			if (!sdptr->Type.DrawPriority)							//RJS 09Jul98
//DeadCode RJS 07Feb00 				bzoffset.f = (Float)shpsize;						//RJS 09Jul98
//DeadCode RJS 07Feb00  			else													//RJS 09Jul98
//DeadCode RJS 07Feb00  				bzoffset.f = 12325.0;								//RJS 09Jul98
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			obj3dptr = (Obj3DPtr )which_tree->Get3DArea(STATIC_OBJECT);
//DeadCode RJS 07Feb00 			SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			obj3dptr->AnimPtr = tempitemptr->Anim;				//DAW 23Apr99
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			which_tree->insert_object(obj3dptr);							//RJS 17Sep97
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			SHAPE.animate_shape(obj3dptr,tempitemptr->World);	//RJS 01Dec99
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 			tempitemptr->Status.Drawn = TRUE;//RJS 05Oct98
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 	#ifndef NDEBUG					
//DeadCode RJS 07Feb00 			if (supercheatitem && (beenfixed==true))			
//DeadCode RJS 07Feb00 				tempitemptr->World.Y = 0;
//DeadCode RJS 07Feb00 	#endif
//DeadCode RJS 07Feb00 		}															//RJS 10Nov98
//DeadCode RJS 07Feb00 		else
//DeadCode RJS 07Feb00 			SHAPE.dummy_animate_shape(tempitemptr,(UByteP)sdptr);//RJS 06Apr99
//DeadCode RJS 07Feb00 
//DeadCode RJS 07Feb00 //DeadCode RJS 04Feb00		SHAPE.sfx_shape(tempitemptr,wx,wy,wz);						//RJS 20Apr98
//DeadCode RJS 07Feb00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object_shad
//Author		Robert Slater
//Date			Thu 19 Jun 1997
//
//Description	Places a shadow on the slope of the landscape in the draw list.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_object_shad(rotitem* tempitemptr, itemptr	owner)
{
#ifndef	_ONLYPILOTED_
	btree::ObjectRec*	objectRec = &bt->objectRec;
	ShapeDescPtr		sdptr = SHAPESTUFF.GetShapePtr(tempitemptr->shape);
	SLong				dx,dy,dz;

	dx = tempitemptr->World.X - SLong(viewer_x);
	dy = tempitemptr->World.Y - SLong(viewer_y);
	dz = tempitemptr->World.Z - SLong(viewer_z);

	MinAnimData*	mad = (MinAnimData*)tempitemptr->Anim;
	if (!mad->IsInvisible)
	{
		SLong	theRange = D3Distance(dx,dy,dz);						//RJS 23Aug00
		if (theRange < RANGE_DEFAULT)									//RJS 23Aug00
		{
			objectRec->pos[objectRec->numItems].x=dx;
			objectRec->pos[objectRec->numItems].y=dy;
			objectRec->pos[objectRec->numItems].z=dz;
			objectRec->rad[objectRec->numItems]=sdptr->Size<<4;
			objectRec->range[objectRec->numItems]=theRange;

			if (ConeCheck(objectRec->pos[objectRec->numItems],theRange,objectRec->rad[objectRec->numItems]))
			{
// simulate old SetObj3D

				Obj3D*	smpoptr = &objectRec->obj3d[objectRec->numItems];

				smpoptr->Body.X.f = objectRec->pos[objectRec->numItems].x;
				smpoptr->Body.Y.f = objectRec->pos[objectRec->numItems].y;
				smpoptr->Body.Z.f = objectRec->pos[objectRec->numItems].z;
				smpoptr->ItemPtr = owner;
				smpoptr->Shape = tempitemptr->shape;
				smpoptr->AngH=tempitemptr->hdg;									//RJS 26May00
				smpoptr->AngC=tempitemptr->pitch;								//RJS 26May00
				smpoptr->AngR=tempitemptr->roll;								//RJS 26May00
 				smpoptr->copySize=0;					//cludge
				smpoptr->AnimPtr=tempitemptr->Anim;
				smpoptr->objtype = SHADOW_OBJECT;
				smpoptr->realbz.f = Float(objectRec->range[objectRec->numItems]);

				if (objectRec->numItems < btree::ObjectRec::MAX_OBJECTS-1)
					objectRec->numItems++;
#ifdef	_BTREEFULL_
 				else
 					INT3;
#endif
			}
		}
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object_vapour
//Author		Robert Slater
//Date			Mon 8 Sep 1997
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong ThreeDee::do_object_vapour(rotitem* tempitemptr, UByteP&	thisobj, UWord failedyet)
{
//DeadCode RJS 04Feb00 	Obj3DPtr	obj3dptr;										
//DeadCode RJS 04Feb00 	IFShare		wx,wy,wz;
//DeadCode RJS 04Feb00 	IFShare		bzoffset;
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 	bzoffset.f = 96*4;											//RJS 17Sep97
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 //DeadCode RJS 21Apr99 	UByteP	adptr=(UByteP )tempitemptr->Anim;
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 	wx.i = tempitemptr->World.X - viewer_x;
//DeadCode RJS 04Feb00 	wy.i = tempitemptr->World.Y - viewer_y;
//DeadCode RJS 04Feb00 	wz.i = tempitemptr->World.Z - viewer_z;
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 	_matrix.transform(fpviewer_matrix,wx,wy,wz);
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 	if(RoughCone(wx,wy,wz,0) || !failedyet)					//RJS 20Aug98
//DeadCode RJS 04Feb00 	{
//DeadCode RJS 04Feb00 		obj3dptr = (Obj3DPtr )bt->Get3DArea(SMOKE_OBJECT);		//DAW 18Aug99
//DeadCode RJS 04Feb00 		if (obj3dptr)
//DeadCode RJS 04Feb00 		{
//DeadCode RJS 04Feb00 			SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 			obj3dptr->ItemPtr = NULL;								//RJS 11Nov98
//DeadCode RJS 04Feb00 			obj3dptr->objtype = SMOKE_OBJECT;
//DeadCode RJS 04Feb00 			obj3dptr->AnimPtr = tempitemptr->Anim;								//RJS 21Apr99
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 			bt->insert_object(obj3dptr);
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 			tempitemptr->Status.Drawn = TRUE;//RJS 05Oct98
//DeadCode RJS 04Feb00 		}
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 		thisobj = (UByteP) obj3dptr;
//DeadCode RJS 04Feb00 	}
//DeadCode RJS 04Feb00 	else
//DeadCode RJS 04Feb00 		thisobj = NULL;
//DeadCode RJS 04Feb00 
//DeadCode RJS 04Feb00 	return(wz.f);

	D3DVECTOR 		pos;
	ULong 			clipcode;
	SLong			dx,dy,dz;
	SLong			range;

	dx = tempitemptr->World.X-SLong(viewer_x);
	dy = tempitemptr->World.Y-SLong(viewer_y);
	dz = tempitemptr->World.Z-SLong(viewer_z);

	range = D3Distance(dx,dy,dz);

	pos.x=dx;
	pos.y=dy;
	pos.z=dz;

	g_lpLib3d->PushMatrix(MATRIX_OBJECT);
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
	g_lpLib3d->VisibleCheck(&pos,1,&clipcode);
	g_lpLib3d->PopMatrix(MATRIX_OBJECT);

	thisobj = NULL;
	if ((clipcode==0) || !failedyet)
	{
		Obj3DPtr	obj3dptr;

		thisobj = StuffIntoVisibleList(tempitemptr,range,pos,SMOKE_OBJECT);
		
		obj3dptr = (Obj3DPtr)thisobj;
		obj3dptr->ItemPtr = NULL;
	}

	return range;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object_grp
//LastModified:	PD 25Jul96
//Author		Paul.   
//Date			Fri 8 Mar 1996
//
//Description	Transform and insert a group of shapes
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_object_grp(itemptr tempitemptr)
{
}


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitPalette
//Author		Jon Booth
//Date			Tue 15 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::InitPalette( CLib3D* lib3d )
{
	if (newpalettes == NULL)							
	{													
		LandMapNum lmn=LandMapNum(FIL_PALCLUSTMAP_NUM);	
											  			
		newpalettes = lmn.GetLandMapPtr();
		if (newpalettes)
		{
			ImageMapNumber	imapno;
			RGBINFO_PTR		src,paloffset;
			SWord			count;

			MasterPalettePtr = newpalettes->palette;

			//Use daytime palette!
			src = (RGBINFO_PTR) MasterPalettePtr;
			paloffset = NewPalettePtr;			

			int	bigcount;														
			for (bigcount = 0; bigcount < 8; bigcount++)
			{
				count = 0;											
				while (count < 256)
				{
					paloffset->rval = src->gval;							
					paloffset->gval = src->bval;
					paloffset->bval = src->rval;

					src++;
					paloffset++;
					count++;
				}

				// Next palette...
				src += 768;
			}
			lib3d->SetPaletteTable((UByteP)NewPalettePtr);
		}
	}
	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		PaletteBlender
//Author		Robert Slater
//Date			Tue 22 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::PaletteBlender(SLong time)
{
	SLong			newtime_minutes;

	time /= 100;						
	newtime_minutes = time/60;			
	if (newtime_minutes != time_minutes)
	{
		time_minutes = newtime_minutes;	

		lightson = Land_Scape.SetLighting(time);

		if (newpalettes == NULL)							
		{													
			LandMapNum lmn=LandMapNum(FIL_PALCLUSTMAP_NUM);	
											  				
			newpalettes = lmn.GetLandMapPtr();
			if (newpalettes)
			{
				ImageMapNumber	imapno;
				RGBINFO_PTR		src,paloffset;
				SWord			count;

				MasterPalettePtr = newpalettes->palette;

				//Use daytime palette!
				src = (RGBINFO_PTR) MasterPalettePtr;
				paloffset = NewPalettePtr;			

				int	bigcount;														
				for (bigcount = 0; bigcount < 8; bigcount++)
				{
					count = 0;											
					while (count < 256)
					{
						paloffset->rval = src->gval;							
						paloffset->gval = src->bval;
						paloffset->bval = src->rval;

						src++;
						paloffset++;
						count++;
					}

					// Next palette...
					src += 768;
				}
				g_lpLib3d->SetPaletteTable((UByteP)NewPalettePtr);
			}
		}
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetPalette
//Author		Robert Slater
//Date			Thu 24 Oct 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::ResetPalette(Bool	forceday)
{
	if (forceday)
		oldtime = -2;
	else
		oldtime = -1;

	whereinpal = -1;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ResetCompass
//Author		Robert Slater
//Date			Thu 21 Nov 1996
//
//Description	Sets the old compass heading to the new one instantaneously
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::ResetCompass()
{
	resetpit = TRUE;
}

//DEADCODE JIM 07/02/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE JIM 07/02/00 //Procedure		CalcLightsOn
//DEADCODE JIM 07/02/00 //Author		Robert Slater
//DEADCODE JIM 07/02/00 //Date			Mon 16 Dec 1996
//DEADCODE JIM 07/02/00 //
//DEADCODE JIM 07/02/00 //Description	
//DEADCODE JIM 07/02/00 //
//DEADCODE JIM 07/02/00 //Inputs		
//DEADCODE JIM 07/02/00 //
//DEADCODE JIM 07/02/00 //Returns	
//DEADCODE JIM 07/02/00 //
//DEADCODE JIM 07/02/00 //------------------------------------------------------------------------------
//DEADCODE JIM 07/02/00 void ThreeDee::CalcLightsOn(SLong	time)
//DEADCODE JIM 07/02/00 {
//DEADCODE JIM 07/02/00 	SLong			timedif,palpos;
//DEADCODE JIM 07/02/00 	Bool			timetochange;
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 	time /= 100;							// To seconds
//DEADCODE JIM 07/02/00 	lightson = TRUE;
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 	timedif = time - Miss_Man.camp.dawntime;		
//DEADCODE JIM 07/02/00 	if ((timedif >= -1800) && (timedif <= 1800))
//DEADCODE JIM 07/02/00 	{
//DEADCODE JIM 07/02/00 		palpos = 0;
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 		if (timedif < 0)
//DEADCODE JIM 07/02/00 		{
//DEADCODE JIM 07/02/00 			whichpal = PAL_NIGHT;								//RJS 02Sep97
//DEADCODE JIM 07/02/00 			palpos = 16;
//DEADCODE JIM 07/02/00 		}
//DEADCODE JIM 07/02/00 		else
//DEADCODE JIM 07/02/00 			whichpal = PAL_DAWN;								//RJS 02Sep97
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 		palpos += ((timedif<<4) / 1800);
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 		if (palpos != whereinpal)
//DEADCODE JIM 07/02/00 		{
//DEADCODE JIM 07/02/00 			whereinpal = palpos;
//DEADCODE JIM 07/02/00 			timetochange = TRUE;
//DEADCODE JIM 07/02/00 			if ((whereinpal > 8) && (whichpal == PAL_DAWN))		//RJS 02Sep97
//DEADCODE JIM 07/02/00 				lightson = FALSE;
//DEADCODE JIM 07/02/00 		}
//DEADCODE JIM 07/02/00 	}
//DEADCODE JIM 07/02/00 	else
//DEADCODE JIM 07/02/00 	{
//DEADCODE JIM 07/02/00 		lightson = FALSE;
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 		timedif = time - Miss_Man.camp.dusktime;
//DEADCODE JIM 07/02/00 		if ((timedif >= -1800) && (timedif <= 1800))
//DEADCODE JIM 07/02/00 		{
//DEADCODE JIM 07/02/00 			palpos = 0;
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 			if (timedif < 0)
//DEADCODE JIM 07/02/00 			{
//DEADCODE JIM 07/02/00 				whichpal = PAL_DAY;								//RJS 02Sep97
//DEADCODE JIM 07/02/00 				palpos = 16;
//DEADCODE JIM 07/02/00 			}
//DEADCODE JIM 07/02/00 			else
//DEADCODE JIM 07/02/00 				whichpal = PAL_DUSK;							//RJS 02Sep97
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 			palpos += ((timedif<<4) / 1800);
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 			if (palpos != whereinpal)
//DEADCODE JIM 07/02/00 			{
//DEADCODE JIM 07/02/00 				whereinpal = palpos;
//DEADCODE JIM 07/02/00 				if ((whereinpal > 7) && (whichpal == PAL_DUSK))	//RJS 02Sep97
//DEADCODE JIM 07/02/00 					lightson = TRUE;
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 				timetochange = TRUE;
//DEADCODE JIM 07/02/00 			}
//DEADCODE JIM 07/02/00 		}
//DEADCODE JIM 07/02/00 	}
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 	if (!timetochange)
//DEADCODE JIM 07/02/00 	{
//DEADCODE JIM 07/02/00 		SLong	daytimelow,daytimehigh;
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 		daytimelow = Miss_Man.camp.dawntime + 1800;
//DEADCODE JIM 07/02/00 		daytimehigh = Miss_Man.camp.dusktime - 1800;
//DEADCODE JIM 07/02/00 		whereinpal = 0;
//DEADCODE JIM 07/02/00 		timetochange = TRUE;
//DEADCODE JIM 07/02/00 
//DEADCODE JIM 07/02/00 		if ((time > daytimelow) && (time < daytimehigh))
//DEADCODE JIM 07/02/00 		{
//DEADCODE JIM 07/02/00 			whichpal = PAL_DAY;									//RJS 02Sep97
//DEADCODE JIM 07/02/00 			lightson = FALSE;
//DEADCODE JIM 07/02/00 		}
//DEADCODE JIM 07/02/00 		else
//DEADCODE JIM 07/02/00 		{
//DEADCODE JIM 07/02/00 			whichpal = PAL_NIGHT;								//RJS 02Sep97
//DEADCODE JIM 07/02/00 			lightson = TRUE;
//DEADCODE JIM 07/02/00 		}
//DEADCODE JIM 07/02/00 	}
//DEADCODE JIM 07/02/00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		InitialiseCache
//Author		Paul.   
//Date			Mon 19 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::InitialiseCache()
{
//	PaletteBlender(0);
	if (pMigLand==NULL) pMigLand=new CMigLand(/*NULL*/);
	if (pTMake==NULL) pTMake=new TMake;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DeleteCache
//Author		Paul.   
//Date			Mon 19 Jan 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::DeleteCache()
{
	if (pMigLand!=NULL)	delete pMigLand,pMigLand=NULL;
	if (pTMake)
	{
		pTMake->Exit();
		delete pTMake;
		pTMake=NULL;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsPaused
//Author		Robert Slater
//Date			Fri 27 Feb 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
Bool	ThreeDee::IsPaused()
{
 	if (View_Point->FrameTime())
		return(FALSE);

	return(TRUE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ConstructNormalData
//Author		Paul.   
//Date			Tue 18 Aug 1998
//Description	Generates a table of normals used to build a lookup table
//				to light shade the landscape
//------------------------------------------------------------------------------
void ThreeDee::ConstructNormalData()
{
	NormalData* pNormal=normalDataPtr;
	double PI;

	_asm
	{
	fldpi;
	fstp PI; 
	}

	int x,y;

	double TOP=(3.5/360)*2*PI;
	const double STEP=(6.2/360)*2*PI;
	const int headingbands[15]={1,7,13,19,25,30,35,40,44,20,12,10,10,10,10};
	int pitchindex=0;
	double pitch,heading,nextheading,nextpitch,headingstep;
	int currentpoint=1; // 0 is reserved for the horizontal plane
	
	// first fill the flat area...

	pNormal->dvX=pNormal->dvZ=0.f;
	pNormal->dvY=1.f;
	pNormal++;

	for (pitch=TOP,nextpitch=TOP;pitch<PI/2;pitch=nextpitch)
	{
		nextpitch+=STEP;
		pitchindex++;
		headingstep=(2*PI)/headingbands[pitchindex];
		if (pitchindex>10) nextpitch+=STEP;
		if (pitchindex>11) nextpitch+=STEP;
		for (heading=0,nextheading=0;heading<(2*PI)-0.01;heading=nextheading)
		{
			NormalData norm;
			nextheading+=headingstep;

			double 	ave_heading,ave_pitch;
			double 	sin_pitch,cos_pitch,
					sin_heading,cos_heading;

			ave_pitch=(pitch+nextpitch)/2;
			ave_heading=(heading+nextheading)/2;

			_asm
			{
			fld ave_pitch;
			fsincos;
			fstp cos_pitch;
			fstp sin_pitch;
			fld ave_heading;
			fsincos;
			fstp cos_heading;
			fstp sin_heading;
			}

			norm.dvY=cos_pitch;
			norm.dvX=-sin_pitch*cos_heading;
			norm.dvZ=-sin_pitch*sin_heading;

			if (currentpoint<256)
			{
				currentpoint++;

				double mag=1/(norm.dvX*norm.dvX+norm.dvY*norm.dvY+norm.dvZ*norm.dvZ);
				_asm
				{
				fld mag;
				fsqrt;
				fstp mag;
				}
				norm.dvX*=mag;
				norm.dvY*=mag;
				norm.dvZ*=-mag;								//JON 13Sep00 changed the sign for bob
				*pNormal++=norm;
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetSunPos
//Author		Paul.   
//Date			Tue 21 Jul 1998
//------------------------------------------------------------------------------
inline void ThreeDee::GetSunPos(COORDS3D& pos)
{
	current_world->MakeSunPos(View_Point);
	pos=current_world->sunpos;

//DEADCODE JON 4/19/00 	//re-make the landscape normal lookup table if the sun position
//DEADCODE JON 4/19/00 	//has changed
//DEADCODE JON 4/19/00 	if (lastSunPos.X!=pos.X||lastSunPos.Y!=pos.Y||lastSunPos.Z!=pos.Z)
//DEADCODE JON 4/19/00 	{
//DEADCODE JON 4/19/00 		lastSunPos.X=pos.X;
//DEADCODE JON 4/19/00 		lastSunPos.Y=pos.Y;
//DEADCODE JON 4/19/00 		lastSunPos.Z=pos.Z;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 		double 	li=double(pos.X),
//DEADCODE JON 4/19/00 				lj=double(pos.Y>>1),
//DEADCODE JON 4/19/00 				lk=double(pos.Z),
//DEADCODE JON 4/19/00 				mag=li*li+lj*lj+lk*lk;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 		_asm {	fld mag; 
//DEADCODE JON 4/19/00 				fsqrt; 
//DEADCODE JON 4/19/00 				fstp mag; 
//DEADCODE JON 4/19/00 			}
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 		li/=mag;
//DEADCODE JON 4/19/00 		lj/=mag;
//DEADCODE JON 4/19/00 		lk/=mag;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 		NormalData* pNormal=normalDataPtr;
//DEADCODE JON 4/19/00 //deadcode		UByte*		pnlu=pNormalLookup;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 		//add scaling so that level ground always gets
//DEADCODE JON 4/19/00 		//full intensity regardless of the sun position
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 /*		const double darkest_value=.3;	//min=0, max=1
//DEADCODE JON 4/19/00 		const double level_i=pNormal->i*li+pNormal->j*lj+pNormal->k*lk;
//DEADCODE JON 4/19/00 		const double min_i=0.;
//DEADCODE JON 4/19/00 		const double add_factor=255*darkest_value;
//DEADCODE JON 4/19/00 		const double mul_factor=255-add_factor;
//DEADCODE JON 4/19/00 		const SLong low_clip=SLong(add_factor);
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 		for (SLong i=0;i<256;i++)
//DEADCODE JON 4/19/00 		{
//DEADCODE JON 4/19/00 			//take dot product of sun light vector and landscape vector
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			NormalData& n=*pNormal;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			double dot=li*n.i+lj*n.j+lk*n.k;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			if (dot<min_i)			dot=min_i;
//DEADCODE JON 4/19/00 			else if (dot>level_i)	dot=level_i;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			//dot is in the range min_i<=dot<=level_i
//DEADCODE JON 4/19/00 			//convert to the range add_factor<=dot<=255
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			dot-=min_i;
//DEADCODE JON 4/19/00 			dot/=(level_i-min_i);
//DEADCODE JON 4/19/00 			dot=add_factor+mul_factor*dot;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			SLong dotVal=SLong(dot);
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			if (dotVal>255)				dotVal=255;
//DEADCODE JON 4/19/00 			else if (dotVal<low_clip)	dotVal=low_clip;
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			*pnlu++=UByte(dotVal);
//DEADCODE JON 4/19/00 
//DEADCODE JON 4/19/00 			pNormal++;
//DEADCODE JON 4/19/00 		}
//DEADCODE JON 4/19/00 	*/
//DEADCODE JON 4/19/00 	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetLandType
//Author		Robert Slater
//Date			Mon 24 Aug 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
SLong	ThreeDee::GetLandType()
{
	return(pMigLand->GetAreaType());
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DoFlyBySound
//Author		Robert Slater
//Date			Fri 4 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::DoFlyBySound(AirStrucPtr	ac,SLong	distance)
{
	if (!IsPaused())
	{
//DeadCode RJS 10May99 		SLong	ann,bnn,cnn;
//DeadCode RJS 10May99 		SLong	dvx,dvy,dvz;
//DeadCode RJS 10May99 		SLong	magVelAC;//RJS 06Oct98
//DeadCode RJS 10May99 
//DeadCode RJS 10May99 		ann = ac->velx;
//DeadCode RJS 10May99 		bnn = ac->vely;
//DeadCode RJS 10May99 		cnn = ac->velz;
//DeadCode RJS 10May99 		magVelAC = (ann*ann) + (bnn*bnn) + (cnn*cnn);
		if (ac->vel_ && !ac->Status.deadtime)		//Other AC must not be at standstill
		{
			SLong	dvx,dvy,dvz;
			SLong	eyevx, eyevy, eyevz, eyevel;
//DeadCode RJS 11Oct00 //DeadCode RJS 11Oct00 			bool	isyou = false;		//are we in flyby view?
//DeadCode RJS 11Oct00 
//DeadCode RJS 11Oct00 			if (isyou)
//DeadCode RJS 11Oct00 			{
//DeadCode RJS 11Oct00 				eyevx = 0;
//DeadCode RJS 11Oct00 				eyevy = 0;
//DeadCode RJS 11Oct00 				eyevz = 0;
//DeadCode RJS 11Oct00 				eyevel = 0;
//DeadCode RJS 11Oct00 			}
//DeadCode RJS 11Oct00 			else
//DeadCode RJS 11Oct00 			{
				eyevx = Manual_Pilot.ControlledAC2->vel_x/1000;
				eyevy = Manual_Pilot.ControlledAC2->vel_y/1000;
				eyevz = Manual_Pilot.ControlledAC2->vel_z/1000;
				eyevel = Manual_Pilot.ControlledAC2->vel_/1000;
//DeadCode RJS 11Oct00 			}

			if (ac->Anim != NULL)
			{
				MinAnimData*	mad = (MinAnimData*)ac->Anim;
				if (mad->IsInvisible)
					return;
			}

			dvx = eyevx - ac->vel_x/1000;
			dvy = eyevy - ac->vel_y/1000;
			dvz = eyevz - ac->vel_z/1000;

			SLong	acvel = ac->vel_ / 1000;					//RJS 18Nov99
			if (acvel==0) 												//MS 07/03/00
				return;													//MS 07/03/00
			ULong magVelTot = Math_Lib.distance3d(dvx,dvy,dvz);
			if (magVelTot > 1500)								//RJS 18Nov99
			{
				ULong	timetoreach = distance / magVelTot;
				if (timetoreach < 65)				//6.5 secs
				{
					ULong	maxVel = eyevel + acvel;			//RJS 18Nov99
					magVelTot = (magVelTot << 16)/maxVel;
					if (eyevel)
					{
						SLong	vxa,vya,vza;
						SLong	vxb,vyb,vzb;
						SLong	intensity;

						vxa = (eyevx << 8)/eyevel;
						vya = (eyevy << 8)/eyevel;
						vza = (eyevz << 8)/eyevel;

						vxb = (ac->vel_x << 8)/acvel;			//RJS 18Nov99
						vyb = (ac->vel_y << 8)/acvel;			//RJS 18Nov99
						vzb = (ac->vel_z << 8)/acvel;			//RJS 18Nov99
						
						intensity = -((vxa*vxb)+(vya*vyb)+(vza*vzb));

						magVelTot *= intensity;
						magVelTot >>= 16;

						if ((intensity > 60000) && (distance < 2000))			//RJS 24May99
						{
							if (ac->nationality != Manual_Pilot.ControlledAC2->nationality)
							{
//DeadCode RJS 20Oct00 								AirStrucPtr	buddy = Manual_Pilot.ControlledAC2->FindBuddy();

								{}//DEADCODE RDH 07/12/99 								_Radio.TriggerMsg(MESSAGE_STRUC(SCRIPT_HEADON,MSG_BOGEYCALL,buddy,ac,Manual_Pilot.ControlledAC2));
							}
						}
					}

					if (magVelTot > 24000)
					{
						FileNum	fastSound, slowSound;

						if (ac->classtype->aerobaticfactor == AEROBATIC_LOW)
						{
							fastSound = FIL_SFX_FLYBY_FAST_BOMBER;
							slowSound = FIL_SFX_FLYBY_SLOW_BOMBER;
						}
						else
						{
							if (ac->nationality == NAT_RAF)
							{
								fastSound = FIL_SFX_FLYBY_FAST_RAF;
								slowSound = FIL_SFX_FLYBY_SLOW_RAF;
							}
							else
							{
								fastSound = FIL_SFX_FLYBY_FAST_LUF;
								slowSound = FIL_SFX_FLYBY_SLOW_LUF;
							}
						}

						if (timetoreach < 20)
							_Miles.PlayDelayed(fastSound,ac,128,FALSE,FIL_SFX_FLYBY_SLOW_RAF,FIL_SFX_FLYBY_FAST_BOMBER);	//RJS 8Jun00
						else
							_Miles.PlayDelayed(slowSound,ac,128,FALSE,FIL_SFX_FLYBY_SLOW_RAF,FIL_SFX_FLYBY_FAST_BOMBER);	//RJS 8Jun00
					}
				}
			}
		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		add_map
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::add_map(rotitem& viewpoint,Bool	isZoomed)
{
//DeadCode RJS 19Apr00 	item	tempitem,
//DeadCode RJS 19Apr00 			*tempitemptr;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	ShapeNum shape;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	SLong	zoffset,yoffset;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	zoffset = yoffset = 0;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	tempitemptr = &tempitem;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	Obj3DPtr	obj3dptr;										
//DeadCode RJS 19Apr00 	IFShare		wx,wy,wz;
//DeadCode RJS 19Apr00 	IFShare		bzoffset;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	ShapeDescPtr	sdptr;
//DeadCode RJS 19Apr00 	
//DeadCode RJS 19Apr00 	tempitem.World.X = viewpoint.World.X;
//DeadCode RJS 19Apr00 	tempitem.World.Y = viewpoint.World.Y;
//DeadCode RJS 19Apr00 	tempitem.World.Z = viewpoint.World.Z;
//DeadCode RJS 19Apr00 	tempitemptr->Anim = Manual_Pilot.ControlledAC2->Anim;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  	if (isZoomed == FALSE)
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99   	{
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		sdptr = SHAPESTUFF.GetShapePtr(MAPZ);
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		SLong	properdistz = (sdptr->sx << 4)*4;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		SLong	minzoom = properdistz >> 2;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		tempitem.shape = MAP;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		if (Key_Tests.KeyPress3d(ZOOMIN) || Key_Tests.KeyHeld3d(ZOOMIN))
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		{
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  			if (mapdistz < properdistz)
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  			{
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  				mapdistz = properdistz;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  				mapoffx = mapoffy = 0;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  			}
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		}
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		if (Key_Tests.KeyPress3d(ZOOMOUT) || Key_Tests.KeyHeld3d(ZOOMOUT))
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		{
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  			if (mapdistz > (minzoom+16))
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  				mapdistz -= 16;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		}
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		SLong	zoomoffset = (properdistz - mapdistz)>>1;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		SLong	yoffset;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		SLong	distgap = properdistz - minzoom;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		wx.f = mapoffx + zoomoffset;								
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		wy.f = mapoffy;													
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		wz.f = mapdistz;										
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		bzoffset.f=0;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		tempitemptr->Anim = Manual_Pilot.ControlledAC2->Anim;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		obj3dptr->objtype = STATIC_OBJECT;
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		obj3dptr->AnimPtr= (UByteP) Manual_Pilot.ControlledAC2->Anim;								
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  		bt->insert_object2(obj3dptr);
//DeadCode RJS 19Apr00 //TempCode PD 07Apr99  	}
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	sdptr = SHAPESTUFF.GetShapePtr(MAPZ);
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	tempitem.shape = MAPZ;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	wx.f = 0;											
//DeadCode RJS 19Apr00 	wy.f = 0;														
//DeadCode RJS 19Apr00 	wz.f = 20<<4;	//(sdptr->sx << 4);											
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	bzoffset.f=0;
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	obj3dptr->objtype = STATIC_OBJECT;
//DeadCode RJS 19Apr00 	obj3dptr->AnimPtr= Manual_Pilot.ControlledAC2->Anim;								//RJS 21Apr99
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	bt->insert_object2(obj3dptr);
//DeadCode RJS 19Apr00 
//DeadCode RJS 19Apr00 	tempitem.Anim=ANIM_NULL;

#ifndef	_NO_MAP_ART_	
	btree::ObjectRec *objectRec;

	objectRec=&bt->objectRec;

	item	tempitem,
			*tempitemptr;
	ShapeDescPtr	sdp = SHAPESTUFF.GetShapePtr(MAPZ);

	tempitemptr = &tempitem;
	tempitem.World.X = viewpoint.World.X;
	tempitem.World.Y = viewpoint.World.Y-320;
	tempitem.World.Z = viewpoint.World.Z;
	tempitem.shape = MAPZ;
	tempitem.Anim = CheatAnim;

	AddToObjectRec(objectRec,tempitemptr,sdp->Size<<4,0,STATIC_OBJECT);

	objectRec->obj3d[0].ItemPtr = NULL;
	objectRec->itemFlag[0]=0;

	tempitem.Anim = ANIM_NULL;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		render
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::render(CLib3D *lib3d, ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
	g_lpLib3d=lib3d;

	mirrorSeen = false;													//JON 11Aug00
	
//DeadCode JON 31Aug00 	if (View_Point && View_Point->PolyPitEnabled())
//DeadCode JON 31Aug00 		clipNearZ = COCKPIT_NEARZ;
//DeadCode JON 31Aug00 	else
//DeadCode JON 31Aug00 		clipNearZ = DEFAULT_NEARZ;

//DeadCode AMM 14Apr99 	SHAPE.safeTrail = FALSE;
	if (vp->drawSpecialFlags)
	{
		_Interactive.Clear();								//RJS 29Nov99

		if (vp->drawSpecialFlags & VIEW_SPECIAL_REPLAY)
			renderreplay(vp,world);
		else
		{
			if (OverLay.fZoomedMap)		renderzoomedmap(vp,world);
			else						rendermap(vp,world);
		}
	}
	else
#pragma warnmsg("**** RENDER TIME MONOTEXT REMOVED **** //CSB")
//DeadCode CSB 29Jun00 		if (ProbeTime a48(48,"Render"))
			render3d(vp,world);

	exit_3D();

static SWord curTime=0;
	curTime-=(SWord)View_Point->FrameTime();
	if (curTime<0)
	{
		curTime=8;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		rendermap
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::rendermap(ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
	ANGLES	oldfov = Save_Data.fieldOfView;
	Save_Data.fieldOfView = ANGLES_90Deg;

	// Similar to add cockpit... just render 1 shape in the world
	// Blobs represent shapes (ac and target?)
	// A shape without 3d transforms .. a MAP_OBJECT

	View_Point=vp;
	SHAPE.SetView(vp,g_lpLib3d);

	fnum++;
	
	ROWANSURFACEDESC	sdesc;
	sdesc.dwSize = sizeof(ROWANSURFACEDESC);
	if (g_lpLib3d->GetSurfaceDesc(&sdesc) == S_OK)
	{
		SHAPE.vd_hoD = 1.;
		SHAPE.vd_originy = sdesc.dwHeight>>1;
		SHAPE.vd_originx = sdesc.dwWidth>>1;
		SHAPE.vd_width = sdesc.dwWidth;
		SHAPE.vd_height = sdesc.dwHeight;
	}

	View_Point->BlockTick(TRUE);
	SetFrameTime();
	View_Point->SelectView();									//PD 19Feb96

	

	OverLay.SetViewpoint(View_Point);
	OverLay.SetScreen(g_lpLib3d);

// In this view we are 64*blockwidth high...
// (far map = 256*256 imagemap, where 1 pixel == .25 block)
//DeadCode JON 8Nov00 	const int worldY = 64*LandScape::_blockWidth;
	const int horizDistToCorner = 64*LandScape::_blockWidth;
	static int fudge = 10;
	const int worldY = horizDistToCorner-(fudge*LandScape::_blockWidth);
	View_Point->World.Y = worldY;

	init_scene(world, vp);

	PaletteBlender((MissManDawnTime() + 2000)*100);						//daytime?

//DeadCode RJS 19Apr00 	View_Point->BlockTick(FALSE);

//DEADCODE RJS 4/25/00 	g_lpLib3d->PushMatrix( MATRIX_OBJECT );
//DEADCODE RJS 4/25/00 	g_lpLib3d->PushMatrix( MATRIX_VIEWER );

	int x = viewer_x>>Grid_Base::WORLDSPACEMOD;
	int z = viewer_z>>Grid_Base::WORLDSPACEMOD;


	// turn off map accel mode if we are on the edge of the playable area...
	if ( x <= LandScape::_halfAreaSizeMIN+7 || z <= LandScape::_halfAreaSizeMIN+7 || z >= 511-(LandScape::_halfAreaSizeMIN+7) || x >= 511-(LandScape::_halfAreaSizeMIN+7) )
		OverLay.CancelAccel();


	// clamp the map to being visible if the aircraft is of the 3d area...
	

	Land_Scape.UpdateHorizTextureIfMoved( x, z );

	g_lpLib3d->BeginScene(RENDERTARGET_PRIMARY);
	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

//DeadCode JON 22Aug00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,1,Land_Scape.view_dist);
//DeadCode JON 22Aug00 	g_lpLib3d->SetFogColour(0x0090B8E8);

	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);

// Set up binary tree...
	btree::ObjectRec *objectRec;

	objectRec=&bt->objectRec;
	objectRec->numItems=0;

 	GetVisibleMapObjects();										//RJS 27Apr00

	add_map(*vp);

	View_Point->BlockTick(FALSE);
	
	// new map rendering stuff

	// now render the map at the furthest distance possible - first turn off fogging
//	g_lpLib3d->SetFogValues( 2.0, 2.0 );
	g_lpLib3d->EnableFogging( false );
	g_lpLib3d->SetProjectionMatrix( (Angles)(int)Save_Data.fieldOfView,NON_COCKPIT_NEARZ, Land_Scape.view_dist,true);
	LIGHTFLAG lf = LF_LIGHTSOURCE;
	g_lpLib3d->SetObjectLighting( lf );

//	g_lpLib3d->Wipe( 0x000000 );
	// now draw the stuff onto the background 
	Lib3DPoint *cornerVert = g_lpLib3d->BeginFan(HMATERIAL(Land_Scape.horizonImg),4 );

//	const int horizDistToCorner = worldY;
#pragma warnmsg ( "should be modulo arithmetic" )
	// or even better a mask - WORLDSPACEMOD is 17...
	int xOff = viewer_x-(x<<Grid_Base::WORLDSPACEMOD);
	int zOff = viewer_z-(z<<Grid_Base::WORLDSPACEMOD);
	zOff = LandScape::_blockWidth - zOff;
	xOff = LandScape::_blockWidth - xOff;

	g_lpLib3d->Scale( MATRIX_OBJECT, 1.f/16.f );

#define MAP_SCALE( arg ) ( (arg)/*/16.f*/ )

	cornerVert->setPosition(
		MAP_SCALE( -(horizDistToCorner)+xOff ),
		MAP_SCALE( -worldY ),
		MAP_SCALE( horizDistToCorner+zOff )
	);
	cornerVert->setIMapCoords( 0, 256 );
	cornerVert++;

	cornerVert->setPosition(
		MAP_SCALE( horizDistToCorner+xOff ),
		MAP_SCALE( -worldY ),
		MAP_SCALE( horizDistToCorner+zOff )
	);
	cornerVert->setIMapCoords( 256, 256 );
	cornerVert++;

	cornerVert->setPosition(
		MAP_SCALE( horizDistToCorner+xOff ),
		MAP_SCALE( -worldY ),
		MAP_SCALE( -(horizDistToCorner)+zOff )
	);

	cornerVert->setIMapCoords( 256, 0 );
	cornerVert++;

	cornerVert->setPosition(
		MAP_SCALE( -(horizDistToCorner)+xOff ),
		MAP_SCALE( -worldY ),
		MAP_SCALE( -(horizDistToCorner)+zOff )
	);
	cornerVert->setIMapCoords( 0, 0 );

	g_lpLib3d->EndFan();

//DeadCode JON 8Nov00 	g_lpLib3d->LoadIdentity( MATRIX_OBJECT );
//DeadCode JON 8Nov00 	D3DVECTOR viewMods;
//DeadCode JON 8Nov00 	viewMods.x=(D3DVALUE)-viewer_x;
//DeadCode JON 8Nov00 	viewMods.y=(D3DVALUE)0.0f;
//DeadCode JON 8Nov00 	viewMods.z=(D3DVALUE)-viewer_z;
//DeadCode JON 8Nov00 	g_lpLib3d->Translate( MATRIX_OBJECT, viewMods );
//DeadCode JON 8Nov00 	g_lpLib3d->Scale( MATRIX_OBJECT, 1.f/20.f );
	g_lpLib3d->Scale( MATRIX_OBJECT, 0.9f );

	renderAircraftRoute();												//JON 8Nov00

//DeadCode JON 8Nov00 	cornerVert->setPosition(
//DeadCode JON 8Nov00 		MAP_SCALE( -(horizDistToCorner+LandScape::_blockWidth)+xOff ),
//DeadCode JON 8Nov00 		MAP_SCALE( -worldY ),
//DeadCode JON 8Nov00 		MAP_SCALE( horizDistToCorner+zOff )
//DeadCode JON 8Nov00 	);
//DeadCode JON 8Nov00 	cornerVert->setIMapCoords( 0, 256 );
//DeadCode JON 8Nov00 	cornerVert++;
//DeadCode JON 8Nov00 
//DeadCode JON 8Nov00 	cornerVert->setPosition(
//DeadCode JON 8Nov00 		MAP_SCALE( horizDistToCorner+xOff ),
//DeadCode JON 8Nov00 		MAP_SCALE( -worldY ),
//DeadCode JON 8Nov00 		MAP_SCALE( horizDistToCorner+zOff )
//DeadCode JON 8Nov00 	);
//DeadCode JON 8Nov00 	cornerVert->setIMapCoords( 256, 256 );
//DeadCode JON 8Nov00 	cornerVert++;
//DeadCode JON 8Nov00 
//DeadCode JON 8Nov00 	cornerVert->setPosition(
//DeadCode JON 8Nov00 		MAP_SCALE( horizDistToCorner+xOff ),
//DeadCode JON 8Nov00 		MAP_SCALE( -worldY ),
//DeadCode JON 8Nov00 		MAP_SCALE( -(horizDistToCorner+LandScape::_blockWidth)+zOff )
//DeadCode JON 8Nov00 	);
//DeadCode JON 8Nov00 
//DeadCode JON 8Nov00 	cornerVert->setIMapCoords( 256, 0 );
//DeadCode JON 8Nov00 	cornerVert++;
//DeadCode JON 8Nov00 
//DeadCode JON 8Nov00 	cornerVert->setPosition(
//DeadCode JON 8Nov00 		MAP_SCALE( -(horizDistToCorner+LandScape::_blockWidth)+xOff ),
//DeadCode JON 8Nov00 		MAP_SCALE( -worldY ),
//DeadCode JON 8Nov00 		MAP_SCALE( -(horizDistToCorner+LandScape::_blockWidth)+zOff )
//DeadCode JON 8Nov00 	);
//DeadCode JON 8Nov00 	cornerVert->setIMapCoords( 0, 0 );

#undef MAP_SCALE

//DeadCode JON 2Oct00 	// now draw the stuff onto the background 
//DeadCode JON 2Oct00 	COORDS3D viewCone[8];
//DeadCode JON 2Oct00 	g_lpLib3d->BackProjectViewCone(viewCone);
//DeadCode JON 2Oct00 
//DeadCode JON 2Oct00 	Lib3DPoint *cornerVert = g_lpLib3d->BeginFan(HMATERIAL(Land_Scape.horizonImg),4 );
//DeadCode JON 2Oct00 	
//DeadCode JON 2Oct00 	cornerVert->setPosition(
//DeadCode JON 2Oct00 		viewCone[4].X,
//DeadCode JON 2Oct00 		viewCone[4].Y+100,
//DeadCode JON 2Oct00 		viewCone[4].Z
//DeadCode JON 2Oct00 	);
//DeadCode JON 2Oct00 	cornerVert->setIMapCoords( 0, 256 );
//DeadCode JON 2Oct00 	cornerVert++;
//DeadCode JON 2Oct00 
//DeadCode JON 2Oct00 	cornerVert->setPosition(
//DeadCode JON 2Oct00 		viewCone[5].X,
//DeadCode JON 2Oct00 		viewCone[5].Y+100,
//DeadCode JON 2Oct00 		viewCone[5].Z
//DeadCode JON 2Oct00 	);
//DeadCode JON 2Oct00 	cornerVert->setIMapCoords( 256, 256 );
//DeadCode JON 2Oct00 	cornerVert++;
//DeadCode JON 2Oct00 
//DeadCode JON 2Oct00 	cornerVert->setPosition(
//DeadCode JON 2Oct00 		viewCone[6].X,
//DeadCode JON 2Oct00 		viewCone[6].Y+100,
//DeadCode JON 2Oct00 		viewCone[6].Z
//DeadCode JON 2Oct00 	);
//DeadCode JON 2Oct00 
//DeadCode JON 2Oct00 	cornerVert->setIMapCoords( 256, 0 );
//DeadCode JON 2Oct00 	cornerVert++;
//DeadCode JON 2Oct00 
//DeadCode JON 2Oct00 	cornerVert->setPosition(
//DeadCode JON 2Oct00 		viewCone[7].X,
//DeadCode JON 2Oct00 		viewCone[7].Y+100,
//DeadCode JON 2Oct00 		viewCone[7].Z
//DeadCode JON 2Oct00 	);
//DeadCode JON 2Oct00 	cornerVert->setIMapCoords( 0, 0 );
//DeadCode JON 2Oct00 
//DeadCode JON 2Oct00 	g_lpLib3d->EndFan();

//DEADCODE JON 6/2/00 	R3DVERTEX *cornerVert;
//DEADCODE JON 6/2/00 	g_lpLib3d->BeginFan(HMATERIAL(Land_Scape.horizonImg),4,cornerVert);
//DEADCODE JON 6/2/00 	
//DEADCODE JON 6/2/00 	cornerVert->bodyx.f = viewCone[4].X;
//DEADCODE JON 6/2/00 	cornerVert->bodyy.f = viewCone[4].Y+100;
//DEADCODE JON 6/2/00 	cornerVert->bodyz.f = viewCone[4].Z;
//DEADCODE JON 6/2/00 	cornerVert->ix = 0;
//DEADCODE JON 6/2/00 	cornerVert->iy = 256;
//DEADCODE JON 6/2/00 	cornerVert++;
//DEADCODE JON 6/2/00 
//DEADCODE JON 6/2/00 	cornerVert->bodyx.f = viewCone[5].X;
//DEADCODE JON 6/2/00 	cornerVert->bodyy.f = viewCone[5].Y+100;
//DEADCODE JON 6/2/00 	cornerVert->bodyz.f = viewCone[5].Z;
//DEADCODE JON 6/2/00 	cornerVert->ix = 256;
//DEADCODE JON 6/2/00 	cornerVert->iy = 256;
//DEADCODE JON 6/2/00 	cornerVert++;
//DEADCODE JON 6/2/00 
//DEADCODE JON 6/2/00 	cornerVert->bodyx.f = viewCone[6].X;
//DEADCODE JON 6/2/00 	cornerVert->bodyy.f = viewCone[6].Y+100;
//DEADCODE JON 6/2/00 	cornerVert->bodyz.f = viewCone[6].Z;
//DEADCODE JON 6/2/00 	cornerVert->ix = 256;
//DEADCODE JON 6/2/00 	cornerVert->iy = 0;
//DEADCODE JON 6/2/00 	cornerVert++;
//DEADCODE JON 6/2/00 
//DEADCODE JON 6/2/00 	cornerVert->bodyx.f = viewCone[7].X;
//DEADCODE JON 6/2/00 	cornerVert->bodyy.f = viewCone[7].Y+100;
//DEADCODE JON 6/2/00 	cornerVert->bodyz.f = viewCone[7].Z;
//DEADCODE JON 6/2/00 	cornerVert->ix = 0;
//DEADCODE JON 6/2/00 	cornerVert->iy = 0;
//DEADCODE JON 6/2/00 
//DEADCODE JON 6/2/00 	g_lpLib3d->EndFan();

	DrawVisibleObjects();

//DEADCODE RJS 4/25/00 	g_lpLib3d->PopMatrix( MATRIX_OBJECT );
//DEADCODE RJS 4/25/00 	g_lpLib3d->PopMatrix( MATRIX_VIEWER );

//DeadCode RJS 19Apr00 	add_map(*vp);

	bt->Clear3DArea();

	g_lpLib3d->End3DScene();

	View_Point->BlockTick(TRUE);
 	OverLay.ProcessUIScreen();
	View_Point->BlockTick(FALSE);

	g_lpLib3d->EndScene();	
	Save_Data.fieldOfView = oldfov;//RJS 09Nov98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		renderzoomedmap
//Author		Robert Slater
//Date			Tue 8 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::renderzoomedmap(ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
	// Satellite view of landscape, with blobs instead of shapes (acs & target)
	ANGLES	oldfov = Save_Data.fieldOfView;
	Save_Data.fieldOfView = ANGLES_90Deg;
	View_Point=vp;


//	g_lpLib3d->BeginScene(RENDERTARGET_PRIMARY);
//	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,50,Land_Scape.view_dist);
//	g_lpLib3d->SetFogColour(fogCol);

	View_Point->BlockTick(TRUE);
	SetFrameTime();
	View_Point->SelectView();									//PD 19Feb96

//	if (Land_Scape.UpdateTexturesWRTViewPos()==false &&
//		Land_Scape.UpdateTexturesWRTViewPos()==false &&
//		Land_Scape.UpdateTexturesWRTViewPos()==false)
//			assert(false&&"Unrecoverable landscape error");

//TempCode PD 24Nov99 	_matrix.SetZScale(current_screen);							
	OverLay.SetViewpoint(View_Point);
	OverLay.SetScreen(g_lpLib3d);
	init_scene(world, vp);
	PaletteBlender((MissManDawnTime() + 2000)*100);						//daytime?

 	GetVisibleMapObjects(true);									//RJS 27Apr00

	add_map(*vp);

//DEADCODE RJS 4/27/00 	View_Point->BlockTick(FALSE);

	Land_Scape.SetUpVisibleCones(	g_lpLib3d,
									View_Point,								
									viewer_x,viewer_y,viewer_z,		
									vp->hdg, true);

	g_lpLib3d->BeginScene(RENDERTARGET_PRIMARY);
	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,NON_COCKPIT_NEARZ,Land_Scape.view_dist);
	g_lpLib3d->EnableFogging( false );
	//	g_lpLib3d->SetFogColour(fogCol);

	SHAPE.SetView(vp,g_lpLib3d);

	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);

	LIGHTFLAG lf = LF_LIGHTSOURCE;
	g_lpLib3d->SetObjectLighting( lf );

	View_Point->BlockTick(FALSE);

	Land_Scape.RenderLandscape(	g_lpLib3d );
//DEADCODE JON 4/6/00 								View_Point,							
//DEADCODE JON 4/6/00 								fpviewer_matrix,					
//DEADCODE JON 4/6/00 								viewer_x,viewer_y,viewer_z,		
//DEADCODE JON 4/6/00 								vp->hdg);
//DEADCODE RJS 4/27/00  	do_objects_map(TRUE);
//DEADCODE RJS 4/25/00 	add_map(*vp,TRUE);

	g_lpLib3d->Scale( MATRIX_OBJECT, 0.3f );
	renderAircraftRoute();

	DrawVisibleObjects();

	bt->Clear3DArea();
	g_lpLib3d->End3DScene();
	View_Point->BlockTick(TRUE);
	OverLay.ProcessUIScreen();
	View_Point->BlockTick(FALSE);
	g_lpLib3d->EndScene();
	Save_Data.fieldOfView = oldfov;//RJS 09Nov98
}

//DeadCode RJS 27Apr00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 27Apr00 //Procedure		do_objects_map
//DeadCode RJS 27Apr00 //Author		Robert Slater
//DeadCode RJS 27Apr00 //Date			Tue 20 Oct 1998
//DeadCode RJS 27Apr00 //
//DeadCode RJS 27Apr00 //Description	
//DeadCode RJS 27Apr00 //
//DeadCode RJS 27Apr00 //Inputs		
//DeadCode RJS 27Apr00 //
//DeadCode RJS 27Apr00 //Returns	
//DeadCode RJS 27Apr00 //
//DeadCode RJS 27Apr00 //------------------------------------------------------------------------------
//DeadCode RJS 27Apr00 void ThreeDee::do_objects_map(Bool	zoomed)
//DeadCode RJS 27Apr00 {
//DeadCode RJS 27Apr00 	ShapeDescPtr	sdptr;
//DeadCode RJS 27Apr00 	int		i,j;
//DeadCode RJS 27Apr00 	item 	tempitem,
//DeadCode RJS 27Apr00 			*tempitemptr;
//DeadCode RJS 27Apr00 	UWord	sector_x,
//DeadCode RJS 27Apr00 			sector_y,
//DeadCode RJS 27Apr00 			current_sector_x,
//DeadCode RJS 27Apr00 			current_sector_y,
//DeadCode RJS 27Apr00 			min_sector_x,
//DeadCode RJS 27Apr00 			max_sector_x,
//DeadCode RJS 27Apr00 			min_sector_y,
//DeadCode RJS 27Apr00 			max_sector_y,
//DeadCode RJS 27Apr00 			this_sector;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 	sdptr = SHAPESTUFF.GetShapePtr(MAPZ);
//DeadCode RJS 27Apr00 	SLong	properdistz = (sdptr->sx << 4)*4;
//DeadCode RJS 27Apr00 	SLong	zoomoffset = (properdistz - mapdistz)>>1;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 	if (zoomed==TRUE)
//DeadCode RJS 27Apr00 	{
//DeadCode RJS 27Apr00 		tempitemptr = &tempitem;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		tempitemptr->World.X = Manual_Pilot.ControlledAC2->World.X;
//DeadCode RJS 27Apr00 		tempitemptr->World.Y = Manual_Pilot.ControlledAC2->World.Y;
//DeadCode RJS 27Apr00 		tempitemptr->World.Z = Manual_Pilot.ControlledAC2->World.Z;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		current_world->getsectornos(tempitemptr,sector_x,sector_y);
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		max_sector_x = sector_x + 1;
//DeadCode RJS 27Apr00 		max_sector_y = sector_y + 1;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		min_sector_x = sector_x - 1;
//DeadCode RJS 27Apr00 		min_sector_y = sector_y - 1;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		if (min_sector_x > 32)		// cos unsigned arithmetic (-1 = 65536)
//DeadCode RJS 27Apr00 			min_sector_x = 0;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		if (min_sector_y > 32)		// cos unsigned arithmetic (-1 = 65536)
//DeadCode RJS 27Apr00 			min_sector_y = 0;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		if (max_sector_x > 32)
//DeadCode RJS 27Apr00 			max_sector_x = 32;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		if (max_sector_y > 32)
//DeadCode RJS 27Apr00 			max_sector_y = 32;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		zoomoffset = 0;//(FT_25000 - FT_20000)>>1;
//DeadCode RJS 27Apr00 		mapoffx = mapoffy = 0;
//DeadCode RJS 27Apr00 		mapdistz = 0;//FT_20000;		// This is how high we want the items on the Landscape map
//DeadCode RJS 27Apr00 	}
//DeadCode RJS 27Apr00 	else
//DeadCode RJS 27Apr00 	{
//DeadCode RJS 27Apr00 		min_sector_x = min_sector_y = 0;
//DeadCode RJS 27Apr00 		max_sector_x = max_sector_y = 32;
//DeadCode RJS 27Apr00 	}
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 	for(current_sector_x = min_sector_x;current_sector_x < max_sector_x; current_sector_x++)
//DeadCode RJS 27Apr00 	{
//DeadCode RJS 27Apr00 		for(current_sector_y = min_sector_y; current_sector_y < max_sector_y;current_sector_y++)
//DeadCode RJS 27Apr00 		{
//DeadCode RJS 27Apr00 			this_sector = current_world->makeindex(current_sector_x,current_sector_y);
//DeadCode RJS 27Apr00 			tempitemptr = current_world->getfirstitem(this_sector);
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 			while (tempitemptr)
//DeadCode RJS 27Apr00 			{
//DeadCode RJS 27Apr00 				if (	(tempitemptr->Status.size==AirStrucSize)
//DeadCode RJS 27Apr00 					/*&&	(tempitemptr != Persons2::PlayerGhostAC)*/	)
//DeadCode RJS 27Apr00 				{
//DeadCode RJS 27Apr00 					switch(SHAPESTUFF.GetShapeScale(sdptr))
//DeadCode RJS 27Apr00 					{
//DeadCode RJS 27Apr00 						case SHP_1CM:
//DeadCode RJS 27Apr00 						case SHP_4CM:
//DeadCode RJS 27Apr00 						case SHP_16CM:
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 							do_map_object(tempitemptr,zoomoffset);
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 							break;
//DeadCode RJS 27Apr00 					}
//DeadCode RJS 27Apr00 				}
//DeadCode RJS 27Apr00 			 	tempitemptr = tempitemptr->Next;
//DeadCode RJS 27Apr00 			}
//DeadCode RJS 27Apr00 		}
//DeadCode RJS 27Apr00 	}
//DeadCode RJS 27Apr00 }

//DeadCode RJS 27Apr00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 27Apr00 //Procedure		do_map_object
//DeadCode RJS 27Apr00 //Author		Robert Slater
//DeadCode RJS 27Apr00 //Date			Tue 20 Oct 1998
//DeadCode RJS 27Apr00 //
//DeadCode RJS 27Apr00 //Description	
//DeadCode RJS 27Apr00 //
//DeadCode RJS 27Apr00 //Inputs		
//DeadCode RJS 27Apr00 //
//DeadCode RJS 27Apr00 //Returns	
//DeadCode RJS 27Apr00 //
//DeadCode RJS 27Apr00 //------------------------------------------------------------------------------
//DeadCode RJS 27Apr00 void	ThreeDee::do_map_object(ItemPtr	tempitemptr,SLong	zoomoffset)
//DeadCode RJS 27Apr00 {
//DeadCode RJS 27Apr00 	Obj3DPtr		obj3dptr;										
//DeadCode RJS 27Apr00 	IFShare			wx,wy,wz;
//DeadCode RJS 27Apr00 	animptr			adptr=tempitemptr->Anim;	 //RJS 4/16/99	//RJS 21Apr99
//DeadCode RJS 27Apr00 	IFShare			bzoffset;
//DeadCode RJS 27Apr00 	ShapeDescPtr	sdptr;
//DeadCode RJS 27Apr00 	MinAnimData*	mad = (MinAnimData*)adptr;
//DeadCode RJS 27Apr00 	SLong			xmax,ymax;
//DeadCode RJS 27Apr00 	SLong			xmap,ymap;
//DeadCode RJS 27Apr00 	SLong			ix,iy;
//DeadCode RJS 27Apr00 	SLong			gridsize = 1 << 21;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 	// Total world is 1 - 8 by 1 - 8
//DeadCode RJS 27Apr00 	// World covered is 2 - 6 by 2 - 8
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 	// Each block is 1 << 21 cm square
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 	xmap = tempitemptr->World.X - (gridsize*11);// cos real map doesn't start til after 11 blocks (8 + 3)
//DeadCode RJS 27Apr00 	ymap = tempitemptr->World.Z;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 	xmax = gridsize * 37;      // Five big blocks of 8 little blocks
//DeadCode RJS 27Apr00 	ymax = gridsize * 64;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 	if ((xmap < xmax) && (ymap < ymax))
//DeadCode RJS 27Apr00 	{
//DeadCode RJS 27Apr00 		xmax /= 312;
//DeadCode RJS 27Apr00 		ymax /= 624;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		ix = (xmap << 2)/xmax;			//Width of map object is 312 cm x 4cm scale
//DeadCode RJS 27Apr00 		iy = (ymap << 2)/ymax;			//Height of map object is double the width
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		ix += mapoffx;
//DeadCode RJS 27Apr00 		iy += mapoffy;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		ix += zoomoffset;
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		wx.f = (-312 * 4) + ix;				//cos map is 4cm scale							
//DeadCode RJS 27Apr00 		wy.f = (-290 * 4) + iy;													
//DeadCode RJS 27Apr00 		wz.f = mapdistz - 4;	
//DeadCode RJS 27Apr00 		
//DeadCode RJS 27Apr00 		bzoffset.f = 1.0;	
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);
//DeadCode RJS 27Apr00 		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		obj3dptr->Shape = MAPRED;
//DeadCode RJS 27Apr00 		obj3dptr->AnimPtr = adptr;	
//DeadCode RJS 27Apr00 
//DeadCode RJS 27Apr00 		bt->insert_object(obj3dptr);
//DeadCode RJS 27Apr00 	}
//DeadCode RJS 27Apr00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_smoke_object
//Author		Robert Slater
//Date			Wed 16 Sep 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
//void	ThreeDee::do_smoke_object(	ItemPtr		theLauncher,
//									Coords3D	*posP,
//									ShapeNum	theShape	)
//{
//	IFShare			wx,wy,wz;
//	ShapeDescPtr	sdptr;
//	SLong			shpsize;
//
//	wx.i = posP->X - viewer_x;
//	wy.i = posP->Y - viewer_y;
//	wz.i = posP->Z - viewer_z;
//
//	_matrix.transform(fpviewer_matrix,wx,wy,wz);
//
//	sdptr = SHAPESTUFF.GetShapePtr(theShape);
//	shpsize = sdptr->Size<<4;
//
//	if(RoughCone(wx,wy,wz,shpsize))
//	{										
//		WorldStuff	*world = mobileitem::currworld;
//	}
//}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		renderreplay
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::renderreplay(ViewPoint* vp,WorldStuff *world)//PD 22Apr96
{
	View_Point=vp;
	bt->SetupBTree(g_lpLib3d,vp);									//AMM 10Feb99
	SHAPE.SetView(vp,g_lpLib3d);

	SHAPE.SetDistScale();										//AMM 10Feb99

	fnum++;

	View_Point->BlockTick(TRUE);

//**********************************************************************
//	Frame Timer Used For Position Predicter
//**********************************************************************

	SetFrameTime();													//RJS 19Sep00

//**********************************************************************
//	Frame Timer Used For Position Predicter	(END)
//**********************************************************************

	View_Point->SelectView();
	
	if (_Replay.UpdateLandscape)
	{
		_Replay.UpdateLandscape=false;
		Land_Scape.PossibleTeleport();
//DeadCode JON 9Oct00 		Land_Scape.RefreshLandscape();
	}

//DEADCODE JON 4/6/00 	if (Land_Scape.UpdateTexturesWRTViewPos()==false &&
//DEADCODE JON 4/6/00 		Land_Scape.UpdateTexturesWRTViewPos()==false &&
//DEADCODE JON 4/6/00 		Land_Scape.UpdateTexturesWRTViewPos()==false)
//DEADCODE JON 4/6/00 		assert(false&&"Unrecoverable landscape error");

//DEADCODE JON 4/6/00 	g_lpLib3d->BeginScene(RENDERTARGET_PRIMARY);

//DEADCODE JON 4/6/00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,50,Land_Scape.view_dist);
//DEADCODE JON 4/6/00 	g_lpLib3d->SetFogColour(fogCol);

	OverLay.SetViewpoint(View_Point);
	OverLay.SetScreen(g_lpLib3d);

	init_scene(world, vp);

//DEADCODE JON 4/14/00 	pTMake->BuildShadowList(world,vp);							//RJS 17Feb99
	pTMake->FrameInit(world,Three_Dee.SunLightVector);

	ShapeNum manualPilotShape=Manual_Pilot.ControlledAC2->shape;
//DeadCode RJS 15Dec99	if (manualPilotShape==CMIG15) Manual_Pilot.ControlledAC2->shape=MIG15;
//DEADCODE PD 15Feb2000	do_objects();		
//DeadCode RJS 31Jul00 	Land_Scape.SetUpVisibleCones(	g_lpLib3d,
//DeadCode RJS 31Jul00 									View_Point,								
//DeadCode RJS 31Jul00 									viewer_x,viewer_y,viewer_z,		
//DeadCode RJS 31Jul00 									vp->hdg);
//DeadCode RJS 31Jul00 
//DeadCode RJS 31Jul00 	g_lpLib3d->BeginScene(RENDERTARGET_PRIMARY);
//DeadCode RJS 31Jul00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,clipNearZ,Land_Scape.view_dist);	//RJS 31Jul00
//DeadCode RJS 31Jul00 	g_lpLib3d->SetFogColour(fogCol);
//DeadCode RJS 31Jul00 
//DeadCode RJS 31Jul00 		g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
//DeadCode RJS 31Jul00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
//DeadCode RJS 31Jul00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
//DeadCode RJS 31Jul00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);
//DeadCode RJS 31Jul00 
//DeadCode RJS 31Jul00 	Smoke_Trails.SetViewPoint(vp);
//DeadCode RJS 31Jul00 	PaletteBlender(View_Point->TimeOfDay()); 
//DeadCode RJS 31Jul00 
//DeadCode RJS 31Jul00 	GetVisibleObjects(world);
//DeadCode RJS 31Jul00 	Manual_Pilot.ControlledAC2->shape=manualPilotShape;
//DeadCode RJS 31Jul00 
//DeadCode RJS 31Jul00 	View_Point->BlockTick(FALSE);

	Land_Scape.SetUpVisibleCones(	g_lpLib3d,
									View_Point,								
									viewer_x,viewer_y,viewer_z,		
									vp->hdg);

	g_lpLib3d->BeginScene(RENDERTARGET_PRIMARY);
	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,NON_COCKPIT_NEARZ,Land_Scape.view_dist);
//DeadCode JON 7Nov00 	g_lpLib3d->SetFogColour(fogCol);

	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);

// Get vector for eye...
	R3DMATRIX	vmat;
	g_lpLib3d->GetMatrix(MATRIX_VIEWER,vmat);
	eye_x = vmat._13;
	eye_y = vmat._23;
	eye_z = vmat._33;

	_Miles.SetUpListener(View_Point->trackeditem,viewer_x,viewer_y,viewer_z,eye_x,eye_y,eye_z,View_Point->hdg,View_Point->pitch);	//RJS 15Sep00

	Smoke_Trails.SetViewPoint(vp);										//RJS 31Jul00
	PaletteBlender(View_Point->TimeOfDay()); 							//RJS 31Jul00
																		//RJS 31Jul00
	GetVisibleObjects(world);											//RJS 31Jul00
	Manual_Pilot.ControlledAC2->shape=manualPilotShape;					//RJS 31Jul00

	View_Point->BlockTick(FALSE);										//RJS 31Jul00

	PaletteBlender(View_Point->TimeOfDay()); 
	Land_Scape.RenderLandscape(	g_lpLib3d );
//DEADCODE JON 4/6/00 								View_Point,							
//DEADCODE JON 4/6/00 								fpviewer_matrix,					
//DEADCODE JON 4/6/00 								viewer_x,viewer_y,viewer_z,		
//DEADCODE JON 4/6/00 								vp->hdg);

	// Shove everything into binary tree and render...
//dEAD,cos gonna use interface stuff instead...	add_replay(*vp);
//DEADCODE RJS 4/20/00 	Add_Sun(*vp,world);										
//DEADCODE RJS 5/8/00 	Land_Scape.CloudLayer(View_Point);						
	SHAPE.InitCloudFade();									
	DrawVisibleObjects();											//RJS 23Feb00
	SHAPE.SetCloudFade();
	bt->Clear3DArea();
	// ...shoved everything into binary tree and rendered

	g_lpLib3d->End3DScene();
	View_Point->BlockTick(TRUE);
	OverLay.ProcessUIScreen();
	View_Point->BlockTick(FALSE);

	g_lpLib3d->EndScene();	
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		add_replay
//Author		Robert Slater
//Date			Tue 20 Oct 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::add_replay(rotitem& viewpoint)
{
	ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(RPLAY);
	if (sdptr)
	{
		Obj3DPtr	obj3dptr;										
		IFShare		wx,wy,wz;
		IFShare		bzoffset;
		item		tempitem,
					*tempitemptr;

		tempitemptr = &tempitem;

		tempitem.World.Z = viewpoint.World.Z;
		tempitem.World.X = viewpoint.World.X;
		tempitem.World.Y = viewpoint.World.Y;
		tempitemptr->Anim = Manual_Pilot.ControlledAC2->Anim;
		tempitem.shape = RPLAY;

		wx.f = 0;								
		wy.f = 0;													
		wz.f = (sdptr->sx << 4);

		obj3dptr = (Obj3DPtr )bt->Get3DArea(STATIC_OBJECT);

		bzoffset.f=0;

		SetObj3D(obj3dptr,tempitemptr,wx,wy,wz,bzoffset);

		obj3dptr->objtype = MAP_OBJECT;
		obj3dptr->AnimPtr= Manual_Pilot.ControlledAC2->Anim;								//RJS 21Apr99

		bt->insert_object2(obj3dptr);

		tempitem.Anim=ANIM_NULL;	
	}
}

//DeadCode RJS 27Mar00 void SetBuffetData(CockpitBuf* newBuffetData)
//DeadCode RJS 27Mar00 {
//DeadCode RJS 27Mar00 	Three_Dee.SetCockpitBuffet(newBuffetData);
//DeadCode RJS 27Mar00 }
//DeadCode RJS 27Mar00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode RJS 27Mar00 //Procedure		SetCockpitBuffet
//DeadCode RJS 27Mar00 //Author		Paul.   
//DeadCode RJS 27Mar00 //Date			Thu 29 Oct 1998
//DeadCode RJS 27Mar00 //------------------------------------------------------------------------------
//DeadCode RJS 27Mar00 void ThreeDee::SetCockpitBuffet(CockpitBuf* newBuffetData)
//DeadCode RJS 27Mar00 {
//DeadCode RJS 27Mar00  	buffetData=*newBuffetData;
//DeadCode RJS 27Mar00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SuperShapeCheat
//Author		Robert Slater
//Date			Mon 9 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::SuperShapeCheat()
{
#if !defined(NDEBUG)
	if (shapecheat)
	{
		if (Key_Tests.KeyPress3d(GROUPINFOMSG))
		{
 			WorldStuff	*worldptr = mobileitem::currworld;
 			ItemPtr		firstitem,nextitem;
 			UWord		nextsector, i, totcount;
 
 			if (supercheatitem)
 			{
				nextitem = supercheatitem->Next;
				while (nextitem)
				{
					if (nextitem->Status.size == TRANSIENTSIZE)
						nextitem = nextitem->Next;
					else
						break;
				}

 				if (nextitem == NULL)
 				{
 					nextsector = worldptr->GetSector(supercheatitem);
 		
 					i = nextsector;
 					totcount = 0;

 					firstitem = worldptr->getfirstitem(nextsector);
					while (firstitem)
					{
						if (firstitem->Status.size == TRANSIENTSIZE)
							firstitem = firstitem->Next;
						else
							break;
					}

 					while (firstitem == NULL)
 					{
 						i++;

 						totcount++;

 						if (i == 32*32)
 							i = 0;

 						firstitem = worldptr->getfirstitem(i);

 						if (totcount == 32*32-1)
 							firstitem = Manual_Pilot.ControlledAC2;

						while (firstitem)
						{
							if (firstitem->Status.size == TRANSIENTSIZE)
								firstitem = firstitem->Next;
							else
								break;
						}
 					}

 					nextitem = firstitem;
 				}

 				supercheatitem = nextitem;

				// Set tracked item to supercheatitem...

				View_Point->SetCheatItem(supercheatitem);

 			}
 			else
 				supercheatitem = Manual_Pilot.ControlledAC2;
		}
	}

#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		do_object_dummy
//Author		Robert Slater
//Date			Wed 11 Nov 1998
//
//Description	Same as do_object, but sets the object's itemptr to NULL,
//				cos it is not real......
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::do_object_dummy(itemptr tempitemptr,SLong objtype, itemptr fiddle)//RJS 04Feb00
{
#ifndef	_ONLYPILOTED_

	if (tempitemptr->Anim==NULL)
		SHAPE.SetAnimData(tempitemptr,0);

//DEADCODE RJS 5/8/00 	MinAnimData*	mad = (MinAnimData*)tempitemptr->Anim;			//RJS 08Feb00
//tempcode	if (!mad->IsInvisible)
	{
		D3DVECTOR 		pos;
//DEADCODE RJS 5/8/00 		ULong 			clipcode;
		SLong			dx,dy,dz;
		SLong			range;
		
		if(tempitemptr->World.Y==0)
			tempitemptr->World.Y=_Collide.AccurateGroundAltitude(tempitemptr->World);

		dx = tempitemptr->World.X-SLong(viewer_x);
		dy = tempitemptr->World.Y-SLong(viewer_y);
		dz = tempitemptr->World.Z-SLong(viewer_z);

		pos.x=dx;
		pos.y=dy;
		pos.z=dz;

		Obj3DPtr	obj3dptr = Obj3DPtr(StuffIntoVisibleList(tempitemptr,D3Distance(dx,dy,dz),pos,objtype));
			
//DeadCode RJS 26May00 		obj3dptr->objtype = (ObjectType)objtype;
		obj3dptr->ItemPtr = fiddle;
//DeadCode RJS 26May00 		if (	(objtype == MOBILE_OBJECT)
//DeadCode RJS 26May00 			&&	(obj3dptr->copySize >= HDGSIZE)	)
//DeadCode RJS 26May00 			obj3dptr->AngH = HdgItemPtr(tempitemptr)->hdg;
	}
#endif

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		NearestAliveThing
//Author		Robert Slater
//Date			Mon 16 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
ItemPtr	ThreeDee::NearestAliveThing(ItemPtr	itm)
{
	WorldStuff	*worldptr = mobileitem::currworld;
 	ItemPtr		firstitem,founditem;
	SLong		x,y,z,dx,dy,dz,dist,mindist;
	MinAnimData*	mad;

	x = itm->World.X;
	y = itm->World.Y;
	z = itm->World.Z;

	founditem = NULL;
	mindist = 100000000;

	firstitem = worldptr->getfirstitem(worldptr->GetSector(itm));
 	while (firstitem)
 	{
		if (	(firstitem != itm)								//RJS 11Jun99
			&&	(firstitem->Status.size < MOVINGSIZE)	)		//RJS 11Jun99
		{
			mad = (MinAnimData*) firstitem->Anim;
			if (mad && (mad->itemstate == ALIVE))
			{
				dx = firstitem->World.X - x;
				dy = firstitem->World.X - y;
				dz = firstitem->World.Z - z;

				dist = Math_Lib.distance3d(dx,dy,dz);
				if (dist < mindist)
				{
					founditem = firstitem;

					mindist = dist;
				}
			}
		}
	
		firstitem = firstitem->Next;
	}

	return (founditem);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetVP
//Author		Robert Slater
//Date			Thu 19 Nov 1998
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::SetVP(ViewPoint*	vp)
{
	View_Point=vp;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		IsItVisible
//Author		Rob.   
//Date			Wed 9 Dec 1998
//
//Description	For effects like barrages....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
bool	ThreeDee::IsItVisible(Coords3D&	worldpos)				//RJS 18May99
{
	bool	retval = false;
	if (havematrix)
	{
		IFShare	wx,wy,wz;

		wx.i = worldpos.X - viewer_x;
		wy.i = worldpos.Y - viewer_y;
		wz.i = worldpos.Z - viewer_z;

		_matrix.transform(fpviewer_matrix,wx,wy,wz);
		if (RoughCone(wx,wy,wz,2000))							//give it about 20m radius
			retval = true;
	}

	return(retval);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StuffInBinaryTree
//Author		Robert Slater
//Date			Fri 23 Apr 1999
//
//Description	Same as do_object,
//				but doesn't perform animdata or invisible check....
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::StuffInBinaryTree(ItemPtr	tempitemptr)
{
#ifndef	_ONLYPILOTED_

	D3DVECTOR 		pos;
	ULong 			clipcode;
	SLong			dx,dy,dz;
	SLong			range;
	SLong			objType;
		
	if(tempitemptr->World.Y==0)
		tempitemptr->World.Y=_Collide.AccurateGroundAltitude(tempitemptr->World);

	dx = tempitemptr->World.X-SLong(viewer_x);
	dy = tempitemptr->World.Y-SLong(viewer_y);
	dz = tempitemptr->World.Z-SLong(viewer_z);

	pos.x=dx;
	pos.y=dy;
	pos.z=dz;

	if (tempitemptr->Status.size > ITEMSIZE)
		objType = MOBILE_OBJECT;
	else
		objType = STATIC_OBJECT;

	Obj3DPtr	obj3dptr = (Obj3DPtr)StuffIntoVisibleList(tempitemptr,D3Distance(dx,dy,dz),pos,objType);
			
//DeadCode RJS 26May00 	obj3dptr->objtype = (ObjectType)MOBILE_OBJECT;

	SHAPE.sfx_shape(tempitemptr,pos,obj3dptr->realbz.f);

#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVisibleObjects
//Author		Robert Slater
//Date			Mon 7 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::GetVisibleObjects(WorldStuff *worldptr)
{
//DeadCode RJS 07Feb00 	g_lpLib3d->PushMatrix(MATRIX_OBJECT);
//DeadCode RJS 07Feb00 	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
	btree::ObjectRec *objectRec;
	ObjectType	objtype;

	objectRec=&bt->objectRec;

	objectRec->numItems=0;

#ifndef _NO_SHAPES_

	UWord	sector_x,			sector_y,
			current_sector_x,	current_sector_y,
			this_sector;

	float	drelx,drely,drelz,fDist;									//RJS 25Sep00

	bool isPiloted=false;
	bool dopilotedshad=false;
	bool fDrawPolyPit=View_Point->PolyPitEnabled()!=FALSE;

	if (!fDrawPolyPit && (View_Point->viewnum.viewmode!=VM_InsideCheat && View_Point->viewnum.viewmode!=VM_Inside))
		dopilotedshad = true;

	item tempitem,*tempitemptr=&tempitem,*previtmptr;

// Get vector for eye...
	R3DMATRIX	vmat;
	g_lpLib3d->GetMatrix(MATRIX_VIEWER,vmat);
	eye_x = vmat._13;
	eye_y = vmat._23;
	eye_z = vmat._33;

// Scan sectors for visible items...

	tempitem.World.X = viewer_x;
	tempitem.World.Y = viewer_y;
	tempitem.World.Z = viewer_z;

	current_world->getsectornos(tempitemptr,sector_x,sector_y);

#ifndef	_NOGRIDOPTIMISE_
// tune 3*3 sector grid depending on where are we in world...

	ULong	tmpsec_x = viewer_x >> WORLD_2_SECTOR_SHIFT;
	ULong	tmpsec_z = viewer_z >> WORLD_2_SECTOR_SHIFT;
	ULong	midw_x = (tmpsec_x << WORLD_2_SECTOR_SHIFT) + (SECTOR_SIZE>>1);
	ULong	midw_z = (tmpsec_z << WORLD_2_SECTOR_SHIFT) + (SECTOR_SIZE>>1);
	SLong	sec_dx = viewer_x - midw_x;
	SLong	sec_dz = viewer_z - midw_z;

//	Z > 0	and	eye_Z > 0	dotproduct = +'ve	extra grid in + Z
//	Z > 0	and	eye_Z < 0	dotproduct = -'ve	no change
//	Z < 0	and	eye_Z > 0	dotproduct = -'ve	no change
//	Z < 0	and	eye_Z < 0	dotproduct = +'ve	extra grid in - Z
//	X > 0	and	eye_X > 0	dotproduct = +'ve	extra grid in + X
//	X > 0	and	eye_X < 0	dotproduct = -'ve	no change
//	X < 0	and	eye_X > 0	dotproduct = -'ve	no change
//	X < 0	and	eye_X < 0	dotproduct = +'ve	extra grid in - X

	if ((float(sec_dx)*eye_x) > 0.f)
	{
		if (sec_dx > 0)
			sector_x++;
		else
			sector_x--;
	}

	if ((float(sec_dz)*eye_z) > 0.f)
	{
		if (sec_dz > 0)
			sector_y++;
		else
			sector_y--;
	}
#endif

	UByte	copySize;
	int	sectorcount = 12;

	previtmptr=NULL;

	for(current_sector_x = sector_x-1;sectorcount;current_sector_x++)
	{
		for(current_sector_y = sector_y-1;--sectorcount&3;current_sector_y++)
		{
			this_sector = current_world->makeindex(current_sector_x,current_sector_y);
			tempitemptr = current_world->getfirstitem(this_sector);
			while (tempitemptr)
			{
				if (current_world->SameSector(tempitemptr,*View_Point))
				{
					SLong rangemax,rng;
					ShapeDesc *sdp;
					sdp=SHAPESTUFF.GetShapePtr(tempitemptr->shape);

					copySize = tempitemptr->Status.size;				//RJS 25Sep00
					if((copySize >= MOBILESIZE)	&& (MobileItemPtr(tempitemptr)->vel_))	//RJS 25Sep00	//CSB 9Nov00
					{
						MobileItemPtr mobitem = MobileItemPtr(tempitemptr);

						velCorrect_x = Float(mobitem->vel_x + wind_x)*fView_dt_frac;
						velCorrect_y = Float(mobitem->vel_y + wind_y)*fView_dt_frac;
						velCorrect_z = Float(mobitem->vel_z + wind_z)*fView_dt_frac;
					}
					else
						velCorrect_x = velCorrect_y = velCorrect_z = 0;
					
					drelx = (float(tempitemptr->World.X)+velCorrect_x) - float(viewer_x);	//RJS 25Sep00
					drely = (float(tempitemptr->World.Y)+velCorrect_y) - float(viewer_y);	//RJS 25Sep00
					drelz = (float(tempitemptr->World.Z)+velCorrect_z) - float(viewer_z);	//RJS 25Sep00
					fDist = drelx*drelx + drely*drely + drelz*drelz;
					fastMath.FloatToInt(&rng,fastMath.FastSqrt(fDist));

					if (copySize==AirStrucSize)							//RJS 25Sep00
					{
						rangemax=RANGE_AIRCRAFT_FLASH;
						isPiloted=true;
 						if (rng<RANGE_SHADOW)						//RJS 04Feb00
							Add_Shadow((AirStrucPtr)tempitemptr,dopilotedshad);//RJS 04Feb00
					
						if (tempitemptr!=Persons2::PlayerGhostAC &&
							tempitemptr!=Persons2::PlayerSeenAC)
						{
							isPiloted=false;
							if (rng < RANGE_FLYBYFAST)		
								DoFlyBySound((AirStrucPtr)tempitemptr,rng);
							if (radarOn && View_Point->PolyPitEnabled())//RJS 09Nov98
								SHAPE.GetRadarItem(tempitemptr,rng);//RJS 09Nov98
						}
					}
					else										//RJS 04Jun98
					{
						rangemax=sdp->MaxDrawRange;
						if (	groundlockOn									//RJS 10Jun99
							&&	(copySize != TRANSIENTSIZE)				//RJS 25Sep00
							&&	View_Point->PolyPitEnabled()	)				//RJS 10Jun99
							SHAPE.GetRadarItem(tempitemptr,rng);//RJS 04Jun99
						isPiloted=false;
					}

					if (rng<=rangemax)							//RJS 04Jun98
					{
						if (dopilotedshad || !isPiloted)
						{
#ifdef	_HEIGHTCHECK_
	if (sdp->Type.scaletype == SHP_GRP)
		::AfxTrace("%d...\n",tempitemptr->World.Y);
#endif
							if (	(copySize!=AIRSTRUCSIZE)			//RJS 25Sep00
								&&	!tempitemptr->World.Y	)			//RJS 25Sep00
								tempitemptr->World.Y=_Collide.AccurateGroundAltitude(tempitemptr->World);


							if (sdp->Type.scaletype == SHP_GRP)	//RJS 15Feb00
								ExpandGroup(objectRec,tempitemptr,rng);
							else
							{		
								AddToObjectRec(objectRec,tempitemptr,sdp->Size<<4,rng);	//RJS 26May00
#ifndef NDEBUG
// dont delete these lines!!!! I use them often for testing
								if (_DPlay.SpookyGhostMode)
								{
									if (tempitemptr==Persons2::PlayerSeenAC)
									{
										AddToObjectRec(objectRec,Persons2::PlayerGhostAC,sdp->Size<<4,rng);	//RJS 26May00
									}
								}
#endif
							}

						}
					}
				}
				previtmptr=tempitemptr;
			 	tempitemptr=tempitemptr->Next;
			}
		}
	}


#ifndef	NDEBUG
#ifdef	_MARKCHEAT_
	if (shapecheat)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(Persons2::PlayerSeenAC->shape);
		SLong	sx = sdptr->sx << 4;
		SLong	sy = sdptr->sy << 4;
		SLong	sz = sdptr->sz << 4;
		DoPointStruc	corner;

		corner.bodyx.f = sx;
		corner.bodyy.f = 0;
		corner.bodyz.f = sz;

		g_lpLib3d->PushMatrix(MATRIX_OBJECT);					//RJS 20Mar00
		g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_ROLL,(Angles)-int(Persons2::PlayerSeenAC->roll));
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_PITCH,(Angles)-int(Persons2::PlayerSeenAC->pitch));
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_HEADING,(Angles)int(Persons2::PlayerSeenAC->hdg));

		g_lpLib3d->Transform(MATRIX_OBJECT,corner);

		g_lpLib3d->PopMatrix(MATRIX_OBJECT);					//RJS 20Mar00

		rotitem	dummyitem;

		dummyitem.World = Persons2::PlayerSeenAC->World;
		dummyitem.Anim = Persons2::PlayerSeenAC->Anim;
		dummyitem.shape = BLOKE;

		dummyitem.hdg = Persons2::PlayerSeenAC->hdg;
		dummyitem.pitch = Persons2::PlayerSeenAC->pitch;
		dummyitem.roll = Persons2::PlayerSeenAC->roll;
		dummyitem.World.X -= corner.bodyx.f;
		dummyitem.World.Y -= corner.bodyy.f;
		dummyitem.World.Z -= corner.bodyz.f;

		StuffInBinaryTree(dummyitem);

//DeadCode RJS 26May00 		objectRec->obj3d[objectRec->numItems-1].ItemPtr = Persons2::PlayerSeenAC;

		dummyitem.Anim = ANIM_NULL;
	}
#endif
#endif

//Extras...

	Add_Sun(View_Point,worldptr);								//RJS 20Apr00
	Land_Scape.CloudLayer(View_Point);							//RJS 08May00
	Land_Scape.DrawSmokeClouds();								//RJS 24May00

//Set visible flags...
	ShapeDescPtr	sdp;
	somethingvisible=false;												//RJS 23Aug00

	if (objectRec->numItems > 0)
	{
		g_lpLib3d->PushMatrix(MATRIX_OBJECT);					//RJS 20Mar00
		g_lpLib3d->LoadIdentity(MATRIX_OBJECT);					//RJS 20Mar00

		g_lpLib3d->VisibleCheck(objectRec->pos,objectRec->rad,objectRec->numItems,objectRec->itemFlag);

		int	drawCnt = objectRec->numItems;								//RJS 23Aug00
		for (int i=0;i<drawCnt;i++)										//RJS 23Aug00
		{
			sdp = SHAPESTUFF.GetShapePtr(objectRec->obj3d[i].Shape);
			tempitemptr=objectRec->obj3d[i].ItemPtr;			//RJS 07Feb00
			if (0L==objectRec->itemFlag[i])						//RJS 04Feb00
			{
				somethingvisible = true;
				SetObjectAngles(&objectRec->obj3d[i]);

				if (tempitemptr)
				{
					tempitemptr->Status.Drawn = TRUE;					//RJS 26May00

					SHAPE.animate_shape(&objectRec->obj3d[i],tempitemptr->World);	//RJS 26May00

//DeadCode JON 17Oct00 					if (	Save_Data.gamedifficulty[GD_TEXTINFO]		//RJS 12Jul00
					if (drawDescText									//JON 17Oct00
						&&	(objectRec->obj3d[i].copySize == AIRSTRUCSIZE)	)	//RJS 23Aug00
						OverLay.PrintID(tempitemptr);
				}
			}
			else
			{
				SHAPE.dummy_animate_shape(tempitemptr,(UByteP)sdp,somethingvisible);//RJS 23Aug00

				if (	(objectRec->obj3d[i].copySize == AIRSTRUCSIZE)	//RJS 1Sep00
					&&	Save_Data.gamedifficulty[GD_PERIPHERALVISION]
					&&	(objectRec->range[i] < PERIPHBLOB_RANGE)		//RJS 6Sep00
					&&	(objectRec->obj3d[i].AnimPtr.GetItemState() < DYING)	)
						Add_PeripheralVision(objectRec->obj3d[i].ItemPtr,objectRec->pos[i]);
			}
		}
		
// Fix to see your own smoke trails in the cockpit view
		if (fDrawPolyPit)
			SHAPE.animate_shape_cockpit();

		g_lpLib3d->PopMatrix(MATRIX_OBJECT);					//RJS 20Mar00
	}

	objectRec->somethingvisible = somethingvisible;
#else
	objectRec->somethingvisible = false;
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		DrawVisibleObjects
//Author		Robert Slater
//Date			Mon 7 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::DrawVisibleObjects()
{
#ifdef	_PROCDEBUG_
	Bollox2("0");
#endif
	ShapeDescPtr	sdp;
	btree::ObjectRec *objectRec;

	objectRec=&bt->objectRec;

// Ensure smoke trail points are all sampled once if paused....
	if (!IsPaused())														//RJS 16Apr98
		SHAPE.SamplePntTime = TRUE;											//RJS 16Apr98

//Render...
	g_lpLib3d->PushMatrix(MATRIX_OBJECT);
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

#ifdef	_SHAPE_DEBUG_
	int	polytest;

	shpdebugline[0]=0;
	playerPolys = 0;
	viewDist = 0.;
	noShapesVisible = 0;
	noShapes = objectRec->numItems;

	g_lpLib3d->GivePolyCount(polytest);
	totalPolys = polytest;					//should be the landscape

#endif

	if (objectRec->somethingvisible)							//RJS 04Feb00
	{
		int	drawCnt = objectRec->numItems;								//RJS 23Aug00
		for (int i=0;i<drawCnt;i++)										//RJS 23Aug00
		{
#ifdef	_SHAPE_DEBUG_
			if (	(objectRec->obj3d[i].ItemPtr == View_Point->trackeditem)
				&&	(objectRec->obj3d[i].Shape == ((ItemPtr)View_Point->trackeditem)->shape))
			{
				viewDist = objectRec->obj3d[i].realbz.f;
			}
#endif

			if (0L==objectRec->itemFlag[i])						//RJS 04Feb00
			{		
				sdp=SHAPESTUFF.GetShapePtr((ShapeNum)objectRec->obj3d[i].Shape);
				switch (SHAPESTUFF.GetShapeScale(sdp))
				{
				case SHP_GRP:
					_Error.EmitSysErr(__FILE__":  Should not be group here!!");//RJS 15Feb00
//DeadCode RJS 15Feb00 					AddVisibleGroup((void*)objectRec,i);
 					break;
				case SHP_1CM:
					AddVisibleShape((void*)objectRec,i,1);		//RJS 04Feb00
					break;
				case SHP_4CM:
					AddVisibleShape((void*)objectRec,i,4);		//RJS 04Feb00
					break;
				case SHP_16CM:
					AddVisibleShape((void*)objectRec,i,16);		//RJS 04Feb00
					break;
				}
#ifdef	_SHAPE_DEBUG_
	g_lpLib3d->GivePolyCount(polytest);
	noShapesVisible++;
	totalPolys += polytest;
	if (objectRec->obj3d[i].ItemPtr == View_Point->trackeditem)
		playerPolys = polytest;
#endif
			}
		}
	}

#ifdef	_SHAPE_DEBUG_
	if (shapecheat)
	{
		if (global_cheatbitsoff > -1)
		{
			sprintf(shpdebugline,"Shapes: %d   Visible: %d   Tot Polys: %d   Player... Shape: %d  (Dist: %d   Scaled: %d)  Polys: %d  BitsOff: %d",
				noShapes,noShapesVisible,totalPolys,int(View_Point->trackeditem->shape),int(viewDist),int(viewDist*SHAPE.GetDistScale()),playerPolys,global_cheatbitsoff);
		}
		else
		{
			sprintf(shpdebugline,"Shapes: %d   Visible: %d   Tot Polys: %d   Player... Shape: %d  (Dist: %d   Scaled: %d)  Polys: %d",
				noShapes,noShapesVisible,totalPolys,int(View_Point->trackeditem->shape),int(viewDist),int(viewDist*SHAPE.GetDistScale()),playerPolys);
		}
		OverLay.ShapeCheat(shpdebugline);
	}
#endif
	g_lpLib3d->PopMatrix(MATRIX_OBJECT);

	// Lock smoke trail point sampling....
	if (IsPaused())															//RJS 16Apr98
		SHAPE.SamplePntTime = FALSE;										//RJS 16Apr98
	else
		SHAPE.SamplePntTime = TRUE;								//RJS 23Nov98
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddVisibleShape
//Author		Robert Slater
//Date			Mon 7 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::AddVisibleShape(void *pvoid,int index, int realscale)
{
	Obj3DPtr	thisobj = &((btree::ObjectRec*)pvoid)->obj3d[index];//RJS 07Feb00
#ifdef _ONLY_PLAYER_SHAPE
	if (!( thisobj->ItemPtr == Persons2::PlayerSeenAC && thisobj->Shape == Persons2::PlayerSeenAC->shape ))
		return;
#endif
#ifdef _NOT_PLAYER_SHAPE
	if (( thisobj->ItemPtr == Persons2::PlayerSeenAC && thisobj->Shape == Persons2::PlayerSeenAC->shape ))
		return;
#endif
	
	D3DVECTOR	t;

//just draw
	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

//DeadCode RJS 23Oct00 	if (realscale > 1)
//DeadCode RJS 23Oct00 		g_lpLib3d->Scale(MATRIX_OBJECT,D3DVALUE(realscale));

	if (thisobj->objtype != SMOKE_OBJECT)
	{
		MinAnimData*	mad = (MinAnimData*)thisobj->AnimPtr;
		if (	mad->repair
			&&	(mad->itemstate == DEAD)	)
		{
			R3DMATRIX		dmat;
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(ShapeNum(thisobj->Shape));
			float			sx = float(sdptr->sx);
			float			sz = float(sdptr->sz);

			sdptr = SHAPESTUFF.GetShapePtr(ShapeNum(RUBBLE));

			sx /= float(sdptr->sx);
			sz /= float(sdptr->sz);

			g_lpLib3d->GetMatrix(MATRIX_OBJECT,dmat);

			dmat._11 = sx;
			dmat._33 = sz;

			g_lpLib3d->SetMatrix(MATRIX_OBJECT,dmat);

			thisobj->Shape = RUBBLE;
		}
		else
			g_lpLib3d->Scale(MATRIX_OBJECT,D3DVALUE(realscale));
	}

	switch (thisobj->objtype)
	{
	case STATIC_OBJECT:
		t.dvX=thisobj->Body.X.f;									//RJS 12May00
		t.dvY=thisobj->Body.Y.f;
		t.dvZ=thisobj->Body.Z.f;
		thisobj->Body.X.f = 0;
		thisobj->Body.Y.f = 0;
		thisobj->Body.Z.f = 0;
		break;
	case SMOKE_OBJECT:
		//We don't want to null the object body, cos this is actually the viewpos
		t.dvX=0;													//RJS 12May00
		t.dvY=0;
		t.dvZ=0;
	break;
	case SHADOW_OBJECT:
	{
		rotitem*	itm = (rotitem*)thisobj->ItemPtr;
		Angles		relroll,relpitch;									//RJS 20Apr99
		R3DMATRIX	dmat;

		relpitch = (Angles)int(thisobj->AngC - itm->pitch);// - thisobj->AngC);	//RJS 13Jun00
		relroll = (Angles)int(thisobj->AngR - itm->roll);// - thisobj->AngR);	//RJS 13Jun00

//Tilt the shadow with the ac
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_ROLL,relroll);
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_PITCH,relpitch);

//Zap Y info
 		g_lpLib3d->GetMatrix(MATRIX_OBJECT,dmat);
  		dmat._12 = dmat._21= dmat._22 = dmat._23 = dmat._32 = 0.0;
  		g_lpLib3d->SetMatrix(MATRIX_OBJECT,dmat);

//Place on landscape plane
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_ROLL,(Angles)(int)-thisobj->AngR);
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_PITCH,(Angles)(int)-thisobj->AngC);
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_HEADING,(Angles)(int)thisobj->AngH);

		t.dvX=thisobj->Body.X.f;									//RJS 12May00
		t.dvY=thisobj->Body.Y.f;
		t.dvZ=thisobj->Body.Z.f;
		thisobj->Body.X.f = 0;
		thisobj->Body.Y.f = 0;
		thisobj->Body.Z.f = 0;
		break;
	}
	default:
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_ROLL,(Angles)-(int)thisobj->AngR);
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_PITCH,(Angles)-(int)thisobj->AngC);
		g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_HEADING,(Angles)(int)thisobj->AngH);
		t.dvX=thisobj->Body.X.f;									//RJS 12May00
		t.dvY=thisobj->Body.Y.f;
		t.dvZ=thisobj->Body.Z.f;
		thisobj->Body.X.f = 0;
		thisobj->Body.Y.f = 0;
		thisobj->Body.Z.f = 0;
	break;
	}

	g_lpLib3d->Translate(MATRIX_OBJECT,t);

	SHAPE.process_shape(g_lpLib3d,View_Point,thisobj,NULL,FALSE,NULL);
}

//DEADCODE RJS 4/28/00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DEADCODE RJS 4/28/00 //Procedure		AddVisibleGroup
//DEADCODE RJS 4/28/00 //Author		Paul.   
//DEADCODE RJS 4/28/00 //Date			Thu 3 Feb 2000
//DEADCODE RJS 4/28/00 //
//DEADCODE RJS 4/28/00 //------------------------------------------------------------------------------
//DEADCODE RJS 4/28/00 void ThreeDee::AddVisibleGroup(void *pvoid,int index)
//DEADCODE RJS 4/28/00 {
//DeadCode RJS 15Feb00 	btree::ObjectRec *objRec=(btree::ObjectRec*)pvoid;
//DeadCode RJS 15Feb00 	item *tempitemptr;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	UByte*		groupjump;										//RJS 18Oct96
//DeadCode RJS 15Feb00 	SWord		instruction;									//RJS 18Oct96
//DeadCode RJS 15Feb00 	DOGROUP_PTR 	tempgrp;									//RJS 18Oct96
//DeadCode RJS 15Feb00 	DRAWBETWEEN_PTR	dobetptr;									//RJS 18Oct96
//DeadCode RJS 15Feb00 	SWord		heading;										//RJS 14Aug97
//DeadCode RJS 15Feb00 	SByte		ydelta;											//RJS 20Nov97
//DeadCode RJS 15Feb00 	UByteP		adptrold;
//DeadCode RJS 15Feb00 	COORDS3D	tmpworld;
//DeadCode RJS 15Feb00 	SLong		heightfix;
//DeadCode RJS 15Feb00 	MinAnimData*	mad;										//RJS 16Nov98
//DeadCode RJS 15Feb00 	SWord		realPitch,realRoll,realHdg;						//RJS 23Nov99
//DeadCode RJS 15Feb00 	SLong		dx,dz;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	tempitemptr=objRec->obj3d->ItemPtr;							//RJS 08Feb00
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	if (tempitemptr->Anim==NULL)								//RJS 21Apr99
//DeadCode RJS 15Feb00 		SHAPE.SetAnimData(tempitemptr,0);						//RDH 23Sep96
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	animptr	adptr=tempitemptr->Anim;							//RJS 21Apr99
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	ShapeNum oldshape;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	ShapeDescPtr	header_ptr =
//DeadCode RJS 15Feb00 		SHAPESTUFF.GetShapePtr(oldshape = tempitemptr->shape);
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	UByte *instr_ptr = (UByte *)header_ptr + header_ptr->liveshpref;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	R3DVALUE a;
//DeadCode RJS 15Feb00 	a=objRec->pos[index].x*objRec->pos[index].x+
//DeadCode RJS 15Feb00 		objRec->pos[index].y*objRec->pos[index].y+
//DeadCode RJS 15Feb00 		objRec->pos[index].z*objRec->pos[index].z;
//DeadCode RJS 15Feb00 	a=fastMath.FastSqrt(a);
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	SLong	grouprange = (SLong)a;
//DeadCode RJS 15Feb00 	Bool	notinrange;											//RJS 04Dec96
//DeadCode RJS 15Feb00 	SLong	shpsize;											//RJS 09Jul98
//DeadCode RJS 15Feb00 	Bool	isFiddled;
//DeadCode RJS 15Feb00 	bool	noHeightFix = false;								//RJS 23Nov99
//DeadCode RJS 15Feb00 	SWord	rotateitem;											//RJS 23Nov99
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	groupjump = NULL;											//RJS 05Dec96
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	if (	(tempitemptr->Status.size == AIRSTRUCSIZE)
//DeadCode RJS 15Feb00 		||	(tempitemptr->Status.size == TRANSIENTSIZE)	)
//DeadCode RJS 15Feb00 	{
//DeadCode RJS 15Feb00 		mobileitem*	hdgitem = (mobileitem*) tempitemptr;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		realHdg = hdgitem->hdg;
//DeadCode RJS 15Feb00 		realPitch = hdgitem->pitch;
//DeadCode RJS 15Feb00 		realRoll = hdgitem->roll;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		noHeightFix = true;
//DeadCode RJS 15Feb00 	}
//DeadCode RJS 15Feb00 	else
//DeadCode RJS 15Feb00 	{
//DeadCode RJS 15Feb00 		realPitch = 0;
//DeadCode RJS 15Feb00 		realRoll = 0;
//DeadCode RJS 15Feb00 		realHdg = 0;
//DeadCode RJS 15Feb00 	}
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 	forever	//while(TRUE)
//DeadCode RJS 15Feb00 	{
//DeadCode RJS 15Feb00 		Obj3D thisObj;
//DeadCode RJS 15Feb00 //DeadCode RJS 08Feb00		thisObj.lptr=NULL;
//DeadCode RJS 15Feb00 //DeadCode RJS 08Feb00		thisObj.rptr=NULL;
//DeadCode RJS 15Feb00 		thisObj.ItemPtr=tempitemptr;
//DeadCode RJS 15Feb00 		thisObj.IsTransient=0;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		instruction = *instr_ptr;
//DeadCode RJS 15Feb00 		instr_ptr++;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		if (instruction!=dogroupno)
//DeadCode RJS 15Feb00 			break;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		tempgrp = (DOGROUP_PTR)instr_ptr;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		ShapeNum newshape = (ShapeNum )tempgrp->shapenum;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		heading = tempgrp->angle;								//RJS 14Aug97
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		tempitemptr->shape = newshape;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		thisObj.Shape=tempitemptr->shape;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		thisObj.Body.X.f=objRec->pos[index].x+tempgrp->xoffset;
//DeadCode RJS 15Feb00 		thisObj.Body.Y.f=objRec->pos[index].y+tempgrp->yoffset;
//DeadCode RJS 15Feb00 		thisObj.Body.Z.f=objRec->pos[index].z+tempgrp->zoffset;
//DeadCode RJS 15Feb00 		thisObj.AngH=
//DeadCode RJS 15Feb00 		thisObj.AngC=
//DeadCode RJS 15Feb00 		thisObj.AngR=ANGLES_0Deg;
//DeadCode RJS 15Feb00 		thisObj.objtype=STATIC_OBJECT;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		SHAPE.SetGrpTokenVisibility((UByteP)tempgrp,tempitemptr->Anim,adptr);//RJS 21Apr99
//DeadCode RJS 15Feb00 		mad = (MinAnimData*) adptr;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		if (!noHeightFix)										//RJS 23Nov99
//DeadCode RJS 15Feb00 		{
//DeadCode RJS 15Feb00 			//Eliminate cocked-up deltas
//DeadCode RJS 15Feb00 			ydelta = SHAPE.GetElementYDelta(newshape,adptr,tmpworld,tempitemptr->World.Y);//RJS 09Jun99
//DeadCode RJS 15Feb00 			rotateitem = heading;
//DeadCode RJS 15Feb00 		}
//DeadCode RJS 15Feb00 		else
//DeadCode RJS 15Feb00 		{
//DeadCode RJS 15Feb00 			heading += realHdg;
//DeadCode RJS 15Feb00 			ydelta = 0;
//DeadCode RJS 15Feb00 			adptr += SHAPE.GetElementAnimOffset(newshape);
//DeadCode RJS 15Feb00 			rotateitem = 1;
//DeadCode RJS 15Feb00 		}
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 		if (	(grouprange >= tempgrp->range_min)				//MS 27May98
//DeadCode RJS 15Feb00 			&&	(grouprange < tempgrp->range_max)	)			//MS 27May98
//DeadCode RJS 15Feb00 		{
//DeadCode RJS 15Feb00 			// Delta calc moved to 3dcom.cpp					//DAW 01Dec98
//DeadCode RJS 15Feb00 			heightfix = ydelta<<4;								//DAW 01Dec98
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 			if (!mad->IsInvisible)								//RJS 21Apr99
//DeadCode RJS 15Feb00 			{
//DeadCode RJS 15Feb00 				thisObj.Body.Y.f+=heightfix;
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 				ShapeDescPtr sdptr = SHAPESTUFF.GetShapePtr(newshape);			//RJS 17Nov98
//DeadCode RJS 15Feb00 				shpsize = sdptr->Size << 4;							//RJS 17Nov98
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 				#pragma message(__HERE__"Fix wire problem")
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 				if (rotateitem)									//RJS 23Nov99
//DeadCode RJS 15Feb00 				{												//RJS 20Nov97
//DeadCode RJS 15Feb00 					thisObj.AngH = (Angles) heading;			//RJS 20Nov97
//DeadCode RJS 15Feb00 					thisObj.AngC = (Angles) realPitch;		//RJS 23Nov99
//DeadCode RJS 15Feb00 					thisObj.AngR = (Angles) realRoll;			//RJS 23Nov99
//DeadCode RJS 15Feb00 					thisObj.objtype = MOBILE_OBJECT;			//RJS 14Aug97
//DeadCode RJS 15Feb00 				}												//RJS 14Aug97
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 				//Make sure animdata inherits sizefield too	//RJS 21Apr99
//DeadCode RJS 15Feb00 				thisObj.AnimPtr = tempitemptr->Anim;		//RJS 21Apr99
//DeadCode RJS 15Feb00 				thisObj.AnimPtr = (UByteP)mad;				//RJS 20Nov97
//DeadCode RJS 15Feb00 				SHAPE.animate_shape(&thisObj,tmpworld);		//RJS 01Dec99
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 				g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
//DeadCode RJS 15Feb00 				switch (SHAPESTUFF.GetShapeScale(sdptr))
//DeadCode RJS 15Feb00 				{
//DeadCode RJS 15Feb00 				case SHP_4CM:
//DeadCode RJS 15Feb00 					g_lpLib3d->Scale(MATRIX_OBJECT,D3DVALUE(4));
//DeadCode RJS 15Feb00 					break;
//DeadCode RJS 15Feb00 				case SHP_16CM:
//DeadCode RJS 15Feb00 					g_lpLib3d->Scale(MATRIX_OBJECT,D3DVALUE(16));
//DeadCode RJS 15Feb00 					break;
//DeadCode RJS 15Feb00 				default:
//DeadCode RJS 15Feb00 					break;
//DeadCode RJS 15Feb00 				}
//DeadCode RJS 15Feb00 				g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_ROLL,(Angles)-(int)thisObj.AngR);
//DeadCode RJS 15Feb00 				g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_PITCH,(Angles)-(int)thisObj.AngC);
//DeadCode RJS 15Feb00 				g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_HEADING,(Angles)(int)thisObj.AngH);
//DeadCode RJS 15Feb00 				D3DVECTOR t;
//DeadCode RJS 15Feb00 				t.dvX=thisObj.Body.X.f;
//DeadCode RJS 15Feb00 				t.dvY=thisObj.Body.Y.f;
//DeadCode RJS 15Feb00 				t.dvZ=thisObj.Body.Z.f;
//DeadCode RJS 15Feb00 				g_lpLib3d->Translate(MATRIX_OBJECT,t);
//DeadCode RJS 15Feb00 
//DeadCode RJS 15Feb00 				SHAPE.process_shape(g_lpLib3d,View_Point,&thisObj,NULL,FALSE,NULL);
//DeadCode RJS 15Feb00 				tempitemptr->Status.Drawn = TRUE;//RJS 05Oct98
//DeadCode RJS 15Feb00 			}
//DeadCode RJS 15Feb00 		}
//DeadCode RJS 15Feb00 		instr_ptr += sizeof(DOGROUP);							//RJS 22Aug97
//DeadCode RJS 15Feb00 	}
//DeadCode RJS 15Feb00 	tempitemptr->shape = oldshape;
//DEADCODE RJS 4/28/00 }

//DeadCode JON 17Oct00 //컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//DeadCode JON 17Oct00 //Procedure		InitMirror
//DeadCode JON 17Oct00 //Author		Paul.   
//DeadCode JON 17Oct00 //Date			Tue 7 Dec 1999
//DeadCode JON 17Oct00 //
//DeadCode JON 17Oct00 //------------------------------------------------------------------------------
//DeadCode JON 17Oct00 void ThreeDee::InitMirror()
//DeadCode JON 17Oct00 {
//DeadCode JON 17Oct00 	mdMirror.w=256;
//DeadCode JON 17Oct00 	mdMirror.h=256;
//DeadCode JON 17Oct00 	mdMirror.alpha=0L;
//DeadCode JON 17Oct00 	mdMirror.body=0L;
//DeadCode JON 17Oct00 	mdMirror.isMasked=0;
//DeadCode JON 17Oct00 	mdMirror.hTextureMap=0L;
//DeadCode JON 17Oct00 	mdMirror.palette=0L;
//DeadCode JON 17Oct00 	mdMirror.paletteindex=0;
//DeadCode JON 17Oct00 //tempcode	g_lpLib3d->CreateTexture(&mdMirror,TC_RENDERTARGET);
//DeadCode JON 17Oct00 //DeadCode JON 17Sep00 	hrtMirror=HRENDERTARGET(&mdMirror);
//DeadCode JON 17Oct00 #pragma warnmsg ( "what does this do - is it used???" )
//DeadCode JON 17Oct00 }

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		UseMirror
//Author		Paul.   
//Date			Tue 7 Dec 1999
//
//------------------------------------------------------------------------------
void ThreeDee::UseMirror(SWord	material, COORDS3D& pos,SWord dx,SWord dy,SWord dz,Angles fov)
{
	mirrorSeen = true;

	mirrorMaterial = material;
	mirrorPos = pos;
	mirrorOri.X = dx;
	mirrorOri.Y = dy;
	mirrorOri.Z = dz;
	mirrorFoV = fov;


//	static UByte doit=0xFF;
//	if ((doit^=0xFF)==0) return;
//DeadCode RJS 12Jul00 	const SLong MIRROR_RANGE=100000;
//DeadCode RJS 12Jul00 	D3DMATRIX mat;
//DeadCode RJS 12Jul00 	D3DVECTOR view,upvec,rightvec;
//DeadCode RJS 12Jul00 	D3DVALUE mag;
//DeadCode RJS 12Jul00 	ImageMapDescPtr	imap = Image_Map.GetImageMapPtr(ImageMapNumber(material));
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 	g_lpLib3d->BeginScene(RENDERTARGET_MIRROR);
//DeadCode RJS 12Jul00 	//set new projection matrix
//DeadCode RJS 12Jul00 	g_lpLib3d->SetProjectionMatrix((Angles)(int)Save_Data.fieldOfView,1,100,135184);
//DeadCode RJS 12Jul00 	g_lpLib3d->SetFogColour(fogCol);
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 	//set new view matrix
//DeadCode RJS 12Jul00 	//create matrix using view orientation vector v (dx,dy,dz)
//DeadCode RJS 12Jul00 	view.dvX=dx;
//DeadCode RJS 12Jul00 	view.dvY=dy;
//DeadCode RJS 12Jul00 	view.dvZ=dz;
//DeadCode RJS 12Jul00 	//normalise the view vector
//DeadCode RJS 12Jul00 	mag=view.dvX*view.dvX+view.dvY*view.dvY+view.dvZ*view.dvZ;
//DeadCode RJS 12Jul00 	mag=fastMath.FastInvSqrt(mag);
//DeadCode RJS 12Jul00 	view.dvX*=mag;
//DeadCode RJS 12Jul00 	view.dvY*=mag;
//DeadCode RJS 12Jul00 	view.dvZ*=mag;
//DeadCode RJS 12Jul00 	//dot product of up vector (0,1,0) with view vector
//DeadCode RJS 12Jul00 	upvec.dvX=0-view.dvY*view.dvX;
//DeadCode RJS 12Jul00 	upvec.dvY=1-view.dvY*view.dvY;
//DeadCode RJS 12Jul00 	upvec.dvZ=0-view.dvY*view.dvZ;
//DeadCode RJS 12Jul00 	mag=upvec.dvX*upvec.dvX+upvec.dvY*upvec.dvY+upvec.dvZ*upvec.dvZ;
//DeadCode RJS 12Jul00 	mag=fastMath.FastInvSqrt(mag);
//DeadCode RJS 12Jul00 	upvec.dvX*=mag;
//DeadCode RJS 12Jul00 	upvec.dvY*=mag;
//DeadCode RJS 12Jul00 	upvec.dvZ*=mag;
//DeadCode RJS 12Jul00 	rightvec.dvX=upvec.dvY*view.dvZ-upvec.dvZ*view.dvY;
//DeadCode RJS 12Jul00 	rightvec.dvY=upvec.dvX*view.dvZ-upvec.dvZ*view.dvX;
//DeadCode RJS 12Jul00 	rightvec.dvZ=upvec.dvX*view.dvY-upvec.dvY*view.dvX;
//DeadCode RJS 12Jul00 	mat._11=rightvec.dvX;
//DeadCode RJS 12Jul00 	mat._12=upvec.dvX;
//DeadCode RJS 12Jul00 	mat._13=view.dvX;
//DeadCode RJS 12Jul00 	mat._21=rightvec.dvY;
//DeadCode RJS 12Jul00 	mat._22=upvec.dvY;
//DeadCode RJS 12Jul00 	mat._23=view.dvY;
//DeadCode RJS 12Jul00 	mat._31=rightvec.dvZ;
//DeadCode RJS 12Jul00 	mat._32=upvec.dvZ;
//DeadCode RJS 12Jul00 	mat._33=view.dvZ;
//DeadCode RJS 12Jul00 	mat._14=mat._24=mat._34=mat._41=mat._42=mat._43=0;
//DeadCode RJS 12Jul00 	mat._44=1;
//DeadCode RJS 12Jul00 	g_lpLib3d->SetMatrix(MATRIX_VIEWER,mat);
//DeadCode RJS 12Jul00 	//add in the aircrafts orientation
//DeadCode RJS 12Jul00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);
//DeadCode RJS 12Jul00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)(int)View_Point->pitch);
//DeadCode RJS 12Jul00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
//DeadCode RJS 12Jul00 	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
//DeadCode RJS 12Jul00 	//step through sector list looking for objects to render on the mirror
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 	UWord sector_x, sector_y, current_sector_x, current_sector_y, this_sector;
//DeadCode RJS 12Jul00 	item tempitem,*tempitemptr=&tempitem;
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 	btree::ObjectRec *objectRec;
//DeadCode RJS 12Jul00 	objectRec=&bt->objectRec;
//DeadCode RJS 12Jul00 	objectRec->numItems=0;
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 	ShapeDescPtr sdptr;
//DeadCode RJS 12Jul00 	int	sectorcount=12;
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 	tempitem.World=pos;
//DeadCode RJS 12Jul00 	current_world->getsectornos(tempitemptr,sector_x,sector_y);
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 	for(current_sector_x=sector_x-1;sectorcount;current_sector_x++)
//DeadCode RJS 12Jul00 	{
//DeadCode RJS 12Jul00 		//sc test&dec occurs 4 times per yloop of 3 times
//DeadCode RJS 12Jul00 		for(current_sector_y=sector_y-1;--sectorcount&3;current_sector_y++)
//DeadCode RJS 12Jul00 		{
//DeadCode RJS 12Jul00 			this_sector=current_world->makeindex(current_sector_x,current_sector_y);
//DeadCode RJS 12Jul00 			tempitemptr=current_world->getfirstitem(this_sector);
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 			while (tempitemptr)
//DeadCode RJS 12Jul00 			{
//DeadCode RJS 12Jul00 				if (current_world->SameSector(tempitemptr,*View_Point))
//DeadCode RJS 12Jul00 				{
//DeadCode RJS 12Jul00 					if (tempitemptr->Status.size==AirStrucSize &&
//DeadCode RJS 12Jul00 						tempitemptr!=Persons2::PlayerGhostAC &&
//DeadCode RJS 12Jul00 						tempitemptr!=Persons2::PlayerSeenAC)
//DeadCode RJS 12Jul00 					{
//DeadCode RJS 12Jul00 						SLong dx,dy,dz;
//DeadCode RJS 12Jul00 						dx=tempitemptr->World.X-pos.X;
//DeadCode RJS 12Jul00 						dy=tempitemptr->World.Y-pos.Y;
//DeadCode RJS 12Jul00 						dz=tempitemptr->World.Z-pos.Z;
//DeadCode RJS 12Jul00 						SLong rng=D3Distance(dx,dy,dz);
//DeadCode RJS 12Jul00 						if (rng<=MIRROR_RANGE)
//DeadCode RJS 12Jul00 						{
//DeadCode RJS 12Jul00 							SLong index=objectRec->numItems++;
//DeadCode RJS 12Jul00 							sdptr=SHAPESTUFF.GetShapePtr(tempitemptr->shape);
//DeadCode RJS 12Jul00 							objectRec->pos[index].x=dx;
//DeadCode RJS 12Jul00 							objectRec->pos[index].y=dy;
//DeadCode RJS 12Jul00 							objectRec->pos[index].z=dz;
//DeadCode RJS 12Jul00 							objectRec->rad[index]=sdptr->Size<<4;
//DeadCode RJS 12Jul00 							objectRec->obj3d[index].ItemPtr=tempitemptr;//RJS 07Feb00
//DeadCode RJS 12Jul00 							objectRec->range[index]=rng;
//DeadCode RJS 12Jul00 						}
//DeadCode RJS 12Jul00 					}
//DeadCode RJS 12Jul00 				}
//DeadCode RJS 12Jul00 			 	tempitemptr=tempitemptr->Next;
//DeadCode RJS 12Jul00 			}
//DeadCode RJS 12Jul00 		}
//DeadCode RJS 12Jul00 	}
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 	if (objectRec->numItems>0)
//DeadCode RJS 12Jul00 	{
//DeadCode RJS 12Jul00 		g_lpLib3d->VisibleCheck(objectRec->pos,objectRec->rad,objectRec->numItems,objectRec->itemFlag);
//DeadCode RJS 12Jul00 
//DeadCode RJS 12Jul00 		for (int i=int(objectRec->numItems)-1;i>=0;i--)
//DeadCode RJS 12Jul00 		{
//DeadCode RJS 12Jul00 			if (0==objectRec->itemFlag[i])
//DeadCode RJS 12Jul00 			{
//DeadCode RJS 12Jul00 				Obj3D thisObj;
//DeadCode RJS 12Jul00 				tempitemptr=objectRec->obj3d[i].ItemPtr;		//RJS 07Feb00
//DeadCode RJS 12Jul00 				sdptr=SHAPESTUFF.GetShapePtr(tempitemptr->shape);
//DeadCode RJS 12Jul00 //DeadCode RJS 07Feb00				thisObj.lptr=NULL;
//DeadCode RJS 12Jul00 //DeadCode RJS 07Feb00				thisObj.rptr=NULL;
//DeadCode RJS 12Jul00 				thisObj.ItemPtr=tempitemptr;
//DeadCode RJS 12Jul00 				thisObj.Shape=tempitemptr->shape;
//DeadCode RJS 12Jul00 				thisObj.Body.X.f=objectRec->pos[i].x;
//DeadCode RJS 12Jul00 				thisObj.Body.Y.f=objectRec->pos[i].y;
//DeadCode RJS 12Jul00 				thisObj.Body.Z.f=objectRec->pos[i].z;
//DeadCode RJS 12Jul00 				thisObj.AngH=ANGLES_0Deg;
//DeadCode RJS 12Jul00 				thisObj.AngC=ANGLES_0Deg;
//DeadCode RJS 12Jul00 				thisObj.AngR=ANGLES_0Deg;
//DeadCode RJS 12Jul00 //DeadCode RJS 26May00 				thisObj.IsTransient=0;
//DeadCode RJS 12Jul00 				thisObj.AnimPtr=tempitemptr->Anim;
//DeadCode RJS 12Jul00 				switch (tempitemptr->Status.size)
//DeadCode RJS 12Jul00 				{
//DeadCode RJS 12Jul00 				default:
//DeadCode RJS 12Jul00 				case ItemSize:
//DeadCode RJS 12Jul00 					thisObj.objtype=STATIC_OBJECT;
//DeadCode RJS 12Jul00 					break;
//DeadCode RJS 12Jul00 				case TransientSize:
//DeadCode RJS 12Jul00 //DeadCode RJS 26May00 					thisObj.IsTransient=1;
//DeadCode RJS 12Jul00 				case RotatedSize:
//DeadCode RJS 12Jul00 				case MovingSize:
//DeadCode RJS 12Jul00 				case MobileSize:
//DeadCode RJS 12Jul00 				case FormationSize:
//DeadCode RJS 12Jul00 				case ShipSize:
//DeadCode RJS 12Jul00 				case AirStrucSize:
//DeadCode RJS 12Jul00 					thisObj.AngR=((rotitem *)tempitemptr)->roll;
//DeadCode RJS 12Jul00 				case HPSize:
//DeadCode RJS 12Jul00 					thisObj.AngC=((hpitem *)tempitemptr)->pitch;
//DeadCode RJS 12Jul00 				case HdgSize:
//DeadCode RJS 12Jul00 					thisObj.AngH=((hdgitem *)tempitemptr)->hdg;
//DeadCode RJS 12Jul00 					thisObj.objtype=MOBILE_OBJECT;
//DeadCode RJS 12Jul00 					break;
//DeadCode RJS 12Jul00 				}
//DeadCode RJS 12Jul00 				SHAPE.animate_shape(&thisObj,tempitemptr->World);
//DeadCode RJS 12Jul00 				//just draw
//DeadCode RJS 12Jul00 				g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
//DeadCode RJS 12Jul00 				g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_ROLL,(Angles)-(int)thisObj.AngR);
//DeadCode RJS 12Jul00 				g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_PITCH,(Angles)(int)thisObj.AngC);
//DeadCode RJS 12Jul00 				g_lpLib3d->Rotate(MATRIX_OBJECT,AXIS_HEADING,(Angles)(int)thisObj.AngH);
//DeadCode RJS 12Jul00 				D3DVECTOR t;
//DeadCode RJS 12Jul00 				t.dvX=thisObj.Body.X.f;
//DeadCode RJS 12Jul00 				t.dvY=thisObj.Body.Y.f;
//DeadCode RJS 12Jul00 				t.dvZ=thisObj.Body.Z.f;
//DeadCode RJS 12Jul00 				g_lpLib3d->Translate(MATRIX_OBJECT,t);
//DeadCode RJS 12Jul00 				SHAPE.process_shape(g_lpLib3d,View_Point,&thisObj,NULL,FALSE,NULL);
//DeadCode RJS 12Jul00 				tempitemptr->Status.Drawn=TRUE;
//DeadCode RJS 12Jul00 			}
//DeadCode RJS 12Jul00 		}
//DeadCode RJS 12Jul00 	}
//DeadCode RJS 12Jul00 	g_lpLib3d->EndScene();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddToObjectRec
//Author		Robert Slater
//Date			Fri 4 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::AddToObjectRec(void* objRec,ItemPtr	tempitemptr, SLong size, SLong rng)
{
#ifdef	_ONLYPILOTED_
	if (tempitemptr == Persons2::PlayerSeenAC)
	{
#endif
	if (tempitemptr->Anim==NULL)
		SHAPE.SetAnimData(tempitemptr,0);

	//New test to see if we want to draw or not...
	MinAnimData*	mad = (MinAnimData*)tempitemptr->Anim;
	if (!mad->IsInvisible)
	{
		UByte		copySize = tempitemptr->Status.size;					//RJS 26May00
		ObjectType	objtype = STATIC_OBJECT;

		btree::ObjectRec *objectRec = (btree::ObjectRec*)objRec;

		objectRec->pos[objectRec->numItems].x = velCorrect_x + float(tempitemptr->World.X - SLong(viewer_x));
		objectRec->pos[objectRec->numItems].y = velCorrect_y + float(tempitemptr->World.Y - SLong(viewer_y));
		objectRec->pos[objectRec->numItems].z = velCorrect_z + float(tempitemptr->World.Z - SLong(viewer_z));
		if(copySize > ITEMSIZE)											//RJS 25Sep00
			objtype = MOBILE_OBJECT;									//RJS 25Sep00

		if (ConeCheck(objectRec->pos[objectRec->numItems],rng,size))	//RJS 23Aug00
		{
//DeadCode RJS 25Sep00 			if(copySize > ITEMSIZE)										//RJS 26May00
//DeadCode RJS 25Sep00 			{	
//DeadCode RJS 25Sep00 				objtype = MOBILE_OBJECT;									//RJS 26May00
//DeadCode RJS 25Sep00 				if(copySize >= MOBILESIZE)
//DeadCode RJS 25Sep00 				{
//DeadCode RJS 25Sep00 					MobileItemPtr mobitem = MobileItemPtr(tempitemptr);			//CSB 01/03/00
//DeadCode RJS 25Sep00 
//DeadCode RJS 25Sep00 					objectRec->pos[objectRec->numItems].x += Float(mobitem->vel_x + wind_x)*fView_dt_frac;
//DeadCode RJS 25Sep00 					objectRec->pos[objectRec->numItems].y += Float(mobitem->vel_y + wind_y)*fView_dt_frac;
//DeadCode RJS 25Sep00 					objectRec->pos[objectRec->numItems].z += Float(mobitem->vel_z + wind_z)*fView_dt_frac;
//DeadCode RJS 25Sep00 				}
//DeadCode RJS 25Sep00 			}										
			
			objectRec->rad[objectRec->numItems]   = size;
			objectRec->range[objectRec->numItems] = rng;

// simulate old SetObj3D

			Obj3D*	smpoptr = &objectRec->obj3d[objectRec->numItems];

			smpoptr->Body.X.f = objectRec->pos[objectRec->numItems].x;
			smpoptr->Body.Y.f = objectRec->pos[objectRec->numItems].y;
			smpoptr->Body.Z.f = objectRec->pos[objectRec->numItems].z;
			smpoptr->ItemPtr = tempitemptr;
			smpoptr->Shape = tempitemptr->shape;
			smpoptr->AngH=ANGLES_0Deg;
			smpoptr->AngC=ANGLES_0Deg;
			smpoptr->AngR=ANGLES_0Deg;
 			smpoptr->copySize=copySize;										//RJS 26May00
			smpoptr->AnimPtr=tempitemptr->Anim;
			smpoptr->objtype = objtype;							//RJS 26May00
			smpoptr->realbz.f = Float(rng);
		 
			SHAPE.sfx_shape(tempitemptr,objectRec->pos[objectRec->numItems],smpoptr->realbz.f);

			if (objectRec->numItems < btree::ObjectRec::MAX_OBJECTS-1)
				objectRec->numItems++;
#ifdef	_BTREEFULL_
			else
				INT3;
#endif
		}
		else
		{
			float	floatyRange = float(rng);

			SHAPE.sfx_shape(tempitemptr,objectRec->pos[objectRec->numItems],floatyRange);
			SHAPE.dummy_animate_shape(tempitemptr,UByteP(SHAPESTUFF.GetShapePtr(tempitemptr->shape)),somethingvisible);
		}
	}
#ifdef	_ONLYPILOTED_
	}
#endif
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetObjectAngles
//Author		Robert Slater
//Date			Mon 7 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline void ThreeDee::SetObjectAngles(Obj3DPtr	objptr)
{
	switch (objptr->copySize)											//RJS 26May00
	{
	default:
		break;
	case TransientSize:
	case RotatedSize:
	case MovingSize:
	case MobileSize:
	case FormationSize:
	case ShipSize:
	case AirStrucSize:
		objptr->AngR = ((rotitem *)objptr->ItemPtr)->roll;
	case HPSize:
		objptr->AngC = ((hpitem *)objptr->ItemPtr)->pitch;
	case HdgSize:
		objptr->AngH = ((hdgitem *)objptr->ItemPtr)->hdg;
		break;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StuffIntoVisibleList
//Author		Robert Slater
//Date			Mon 7 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
UByteP	ThreeDee::StuffIntoVisibleList(ItemPtr	tempitemptr, SLong range, D3DVECTOR&	pos, const SLong objtype)
{
	ShapeDescPtr		sdptr=SHAPESTUFF.GetShapePtr(tempitemptr->shape);
	btree::ObjectRec*	objectRec = &bt->objectRec;

	objectRec->somethingvisible = true;									//RJS 6Nov00

	objectRec->pos[objectRec->numItems]=pos;
	objectRec->rad[objectRec->numItems]=sdptr->Size<<4;
	objectRec->range[objectRec->numItems]=range;
	objectRec->itemFlag[objectRec->numItems]=0;

// simulate old SetObj3D

	Obj3D*	smpoptr = &objectRec->obj3d[objectRec->numItems];
	
	smpoptr->Body.X.f = pos.x;
	smpoptr->Body.Y.f = pos.y;
	smpoptr->Body.Z.f = pos.z;
	smpoptr->ItemPtr = tempitemptr;
	smpoptr->Shape = tempitemptr->shape;
	smpoptr->AngH=ANGLES_0Deg;
	smpoptr->AngC=ANGLES_0Deg;
	smpoptr->AngR=ANGLES_0Deg;
 	smpoptr->copySize=tempitemptr->Status.size;							//RJS 26May00
	smpoptr->AnimPtr=tempitemptr->Anim;
	smpoptr->realbz.f = Float(range);
	smpoptr->objtype = ObjectType(objtype);								//RJS 26May00

	SetObjectAngles(smpoptr);											//RJS 26May00
	smpoptr->copySize = 0;												//cludge
	

	if (range < sdptr->MaxDrawRange)
	{
		if (objectRec->numItems < btree::ObjectRec::MAX_OBJECTS-1)
			objectRec->numItems++;
#ifdef _BTREEFULL_
		else
			INT3;
#endif
	}

	return (UByteP)smpoptr;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddNewVapourObject
//Author		Robert Slater
//Date			Tue 8 Feb 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::AddNewVapourObject(	ShapeNum	shape,
									void*		apoint1,
									UByteP		&thisobj3d,
									Coords3D&	worldpos,
									SLong		radius,
									ItemPtr		theLauncher	)
{
	thisobj3d = NULL;													//RJS 10Aug00
	if (Save_Data.detail_3d[DETAIL3D_TRANSSMOKE] != 0)					//RJS 9Aug00
	{
		SLong			dx, dy, dz;
		SLong			range;
		Obj3DPtr		obj3dptr;
		D3DVECTOR		pos;
//DeadCode RJS 20Oct00 		ULong			clipcode=0;
//DeadCode RJS 20Oct00 		Coords3DList*	apoint = (Coords3DList*)apoint1;
	  	SLong			vdx=0;											//RJS 12Sep00
		SLong			vdy=0;											//RJS 12Sep00
		SLong			vdz=0;											//RJS 12Sep00

		dx = worldpos.X-SLong(viewer_x);
		dy = worldpos.Y-SLong(viewer_y);
		dz = worldpos.Z-SLong(viewer_z);

		range = D3Distance(dx,dy,dz);

		pos.x = dx;
		pos.y = dy;
		pos.z = dz;

		if (theLauncher->Status.size >= MOBILESIZE)						//RJS 12Sep00
		{
			MobileItemPtr mobitem = MobileItemPtr(theLauncher);
  
	  		fastMath.FloatToInt(&vdx,float(Float(mobitem->vel_x + wind_x)*fView_dt_frac));
  			fastMath.FloatToInt(&vdy,float(Float(mobitem->vel_y + wind_y)*fView_dt_frac));
  			fastMath.FloatToInt(&vdz,float(Float(mobitem->vel_z + wind_z)*fView_dt_frac));
		}

//	g_lpLib3d->PushMatrix(MATRIX_OBJECT);
//	g_lpLib3d->LoadIdentity(MATRIX_OBJECT);
//	g_lpLib3d->VisibleCheck(&pos,1,&clipcode);
//	g_lpLib3d->PopMatrix(MATRIX_OBJECT);

//DeadCode RJS 10Aug00 		thisobj3d = NULL;
//	if (clipcode==0)
//DeadCode RJS 9Aug00 	{
		btree::ObjectRec*	objectRec = &bt->objectRec;

		objectRec->pos[objectRec->numItems]=pos;
		objectRec->rad[objectRec->numItems]=radius;
		objectRec->range[objectRec->numItems]=range;
		objectRec->itemFlag[objectRec->numItems]=0;

// simulate old SetObj3D

		obj3dptr = &objectRec->obj3d[objectRec->numItems];

		obj3dptr->ItemPtr = NULL;
		obj3dptr->Shape = shape;
		obj3dptr->Body.X.i = viewer_x-vdx;								//RJS 12Sep00
		obj3dptr->Body.Y.i = viewer_y-vdy;								//RJS 12Sep00
		obj3dptr->Body.Z.i = viewer_z-vdz;								//RJS 12Sep00
		obj3dptr->AngH = ANGLES_0Deg;
		obj3dptr->AngC = ANGLES_0Deg;
		obj3dptr->AngR = ANGLES_0Deg;
		obj3dptr->copySize=0;							//RJS 26May00
		obj3dptr->AnimPtr = UByteP(apoint1);
		obj3dptr->AnimPtr = AnimFlagField(1<<MINANIM);
		obj3dptr->realbz.f = Float(range);
		obj3dptr->objtype = SMOKE_OBJECT;

		if (objectRec->numItems < btree::ObjectRec::MAX_OBJECTS-1)
		{
			thisobj3d = (UByteP)obj3dptr;
			objectRec->numItems++;
		}
#ifdef	_BTREEFULL_
		else
			INT3;
#endif
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandGroup
//Author		Robert Slater
//Date			Tue 15 Feb 2000
//
//Description	Fixed version of do_object_grp (and AddVisibleGroup)
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::ExpandGroup(void *pvoid,ItemPtr tempitemptr, SLong grouprange)
{
	UByte*			groupjump;						  
	SWord			instruction;					  
	DOGROUP_PTR 	tempgrp;						  
	DRAWBETWEEN_PTR	dobetptr;						  
	SWord			heading;						  
	SByte			ydelta;							  
	UByteP			adptrold;
	COORDS3D		tmpworld;
//DEADCODE RJS 4/7/00 	Coords3D		relworld;
	SLong			heightfix;
	MinAnimData*	mad;							  
	SWord			realPitch,realRoll,realHdg;		  
	SLong			dx,dz;
	SLong			elmtrange;
	Float			relworld_x;
	Float			relworld_y;
	Float			relworld_z;
	Float			fDist;
 	SLong			velCorrectX;
 	SLong			velCorrectY;
 	SLong			velCorrectZ;

	if (tempitemptr->Anim==NULL)					  
		SHAPE.SetAnimData(tempitemptr,0);			  

	animptr	adptr=tempitemptr->Anim;				  

	ShapeNum oldshape, oldShape;

	ShapeDescPtr	header_ptr =
		SHAPESTUFF.GetShapePtr(oldshape = tempitemptr->shape);

	UByte *instr_ptr = (UByte *)header_ptr + header_ptr->liveshpref;

	Bool	notinrange;											
	SLong	shpsize;											
	Bool	isFiddled;
//DeadCode RJS 26May00 	bool	noHeightFix = false;								
	SWord	rotateitem;
	R3DVALUE	rng;
	UByte		copySize = tempitemptr->Status.size;					//RJS 26May00

	groupjump = NULL;											

	if (copySize >= MOBILESIZE)											//RJS 26May00
	{
		mobileitem*	hdgitem = (mobileitem*) tempitemptr;

		realHdg = hdgitem->hdg;
		realPitch = hdgitem->pitch;
		realRoll = hdgitem->roll;

//DeadCode RJS 25Sep00 		velCorrectX = float(hdgitem->vel_x + wind_x)*float(fView_dt_frac);		//RJS 7Jun00
//DeadCode RJS 25Sep00 		velCorrectY = float(hdgitem->vel_y + wind_y)*float(fView_dt_frac);		//RJS 7Jun00
//DeadCode RJS 25Sep00 		velCorrectZ = float(hdgitem->vel_z + wind_z)*float(fView_dt_frac);		//RJS 7Jun00
		fastMath.FloatToInt(&velCorrectX,velCorrect_x);
		fastMath.FloatToInt(&velCorrectY,velCorrect_y);
		fastMath.FloatToInt(&velCorrectZ,velCorrect_z);

//DeadCode RJS 26May00 		noHeightFix = true;
	}
	else
	{
		realPitch = 0;
		realRoll = 0;
		realHdg = 0;

		velCorrectX = velCorrectY = velCorrectZ = 0;					//RJS 7Jun00
	}

	Coords3D	oldWorld = tempitemptr->World;							//RJS 8Nov00

#ifdef	_HEIGHTCHECK_
::AfxTrace("%x  (%d)  %d\n",int(tempitemptr->SGT),int(tempitemptr->shape),tempitemptr->World.Y);
#endif

	btree::ObjectRec *objectRec=(btree::ObjectRec*)pvoid;

	forever
	{
		instruction = *instr_ptr;
		instr_ptr++;

		if (instruction!=dogroupno)
			break;

		tempgrp = (DOGROUP_PTR)instr_ptr;

		ShapeNum newshape = (ShapeNum )tempgrp->shapenum;

		heading = tempgrp->angle;

		tempitemptr->shape = newshape;

// Add vel correction here...

		tmpworld.X = velCorrectX + tempitemptr->World.X + tempgrp->xoffset;	//RJS 25Sep00
		tmpworld.Y = velCorrectY + tempitemptr->World.Y + tempgrp->yoffset;	//RJS 25Sep00
		tmpworld.Z = velCorrectZ + tempitemptr->World.Z + tempgrp->zoffset;	//RJS 25Sep00

		SHAPE.SetGrpTokenVisibility((UByteP)tempgrp,tempitemptr->Anim,adptr);
		mad = (MinAnimData*) adptr;

		if (copySize < MOBILESIZE)										//RJS 26May00
		{
			//Eliminate cocked-up deltas
			ydelta = SHAPE.GetElementYDelta(newshape,adptr,tmpworld,tempitemptr->World.Y);//RJS 09Jun99
			rotateitem = heading;
		}
		else
		{
			heading += realHdg;
			ydelta = 0;
			adptr += SHAPE.GetElementAnimOffset(newshape);
			rotateitem = 1;
		}

		if (	(grouprange >= tempgrp->range_min)
			&&	(grouprange < tempgrp->range_max)	)
		{
			// Delta calc moved to 3dcom.cpp
			heightfix = ydelta<<4;

#ifdef	_HEIGHTCHECK_
::AfxTrace("      %d\n",heightfix);
#endif
			if (!mad->IsInvisible)
			{
				tmpworld.Y += heightfix;

				relworld_x = tmpworld.X - SLong(viewer_x);
				relworld_y = tmpworld.Y - SLong(viewer_y);
				relworld_z = tmpworld.Z - SLong(viewer_z);

				ShapeDescPtr sdptr = SHAPESTUFF.GetShapePtr(newshape);

				fDist = relworld_x*relworld_x + relworld_z*relworld_z;
				if (sdptr->Type.hasWire)
				{
					if (fDist < BALLOON_WIRE_RANGE_SQD)					//RJS 8Nov00
					{
						oldShape = tempitemptr->shape;

						tempitemptr->shape = BALWIR;
						tempitemptr->World = tmpworld;

						do_object_dummy(tempitemptr,STATIC_OBJECT,tempitemptr);

						tempitemptr->shape = oldShape;
						tempitemptr->World = oldWorld;
					}
				}

				fDist += relworld_y*relworld_y;							//RJS 8Nov00
				rng = fastMath.FastSqrt(R3DVALUE(fDist));
				fastMath.FloatToInt(&elmtrange,rng);

				objectRec->pos[objectRec->numItems].x=relworld_x;// + velCorrectX;	//RJS 7Jun00
				objectRec->pos[objectRec->numItems].y=relworld_y;// + velCorrectY;	//RJS 7Jun00
				objectRec->pos[objectRec->numItems].z=relworld_z;// + velCorrectZ;	//RJS 7Jun00
				objectRec->rad[objectRec->numItems]=sdptr->Size<<4;
				objectRec->range[objectRec->numItems]=elmtrange;

				if (ConeCheck(objectRec->pos[objectRec->numItems],elmtrange,sdptr->Size<<4))//RJS 23Aug00
				{
// simulate old SetObj3D

					Obj3D*	smpoptr = &objectRec->obj3d[objectRec->numItems];

					smpoptr->Body.X.f = objectRec->pos[objectRec->numItems].x;
					smpoptr->Body.Y.f = objectRec->pos[objectRec->numItems].y;
					smpoptr->Body.Z.f = objectRec->pos[objectRec->numItems].z;
					smpoptr->ItemPtr = tempitemptr;//NULL;			//RJS 09May00
					smpoptr->Shape = newshape;
					if (rotateitem)
					{
						smpoptr->AngH = (Angles) heading;
						smpoptr->AngC = (Angles) realPitch;
						smpoptr->AngR = (Angles) realRoll;
						smpoptr->objtype = MOBILE_OBJECT;
					}
					else
					{
						smpoptr->AngH=
							smpoptr->AngC=
							smpoptr->AngR=ANGLES_0Deg;
						smpoptr->objtype = STATIC_OBJECT;
					}
		
//DeadCode RJS 2Jun00  				smpoptr->copySize=copySize;								//RJS 26May00
 					smpoptr->copySize=0;								//RJS 26May00
					smpoptr->AnimPtr=tempitemptr->Anim;
					smpoptr->AnimPtr=(UByteP)mad;
					smpoptr->realbz.f = Float(rng);

//DeadCode RJS 23Aug00 					SHAPE.animate_shape(smpoptr,tmpworld);
//DeadCode RJS 23Aug00 
//DeadCode RJS 23Aug00 					smpoptr->ItemPtr = NULL;

					tempitemptr->Status.Drawn = TRUE;
					
					if (objectRec->numItems < btree::ObjectRec::MAX_OBJECTS-1)
						objectRec->numItems++;
#ifdef _BTREEFULL_
	 				else
						INT3;
#endif

// numItems MUST be incremented before we animate...
					SHAPE.animate_shape(smpoptr,tmpworld);
					smpoptr->ItemPtr = NULL;
				}
				else
				{
// Peripheral Vision...
					if (	(copySize == AIRSTRUCSIZE)
						&&	Save_Data.gamedifficulty[GD_PERIPHERALVISION]
						&&	(elmtrange < PERIPHBLOB_RANGE)				//RJS 6Sep00
						&&	(mad->itemstate < DYING)	)
						Add_PeripheralVision(tempitemptr,objectRec->pos[objectRec->numItems]);
				}
			}
		}
		instr_ptr += sizeof(DOGROUP);
	}
	tempitemptr->shape = oldshape;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		StuffInBinaryTree
//Author		Robert Slater
//Date			Wed 26 Apr 2000
//
//Description	Alternative which locks 3d pos to known pos
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::StuffInBinaryTree(ItemPtr	tempitemptr, Obj3DPtr	theobj3dptr)
{
	D3DVECTOR 		pos;
	SLong			range;
	SLong			objType;

	pos.x = theobj3dptr->Body.X.f;
	pos.y = theobj3dptr->Body.Y.f;
	pos.z = theobj3dptr->Body.Z.f;

	fastMath.FloatToInt(&range,float(theobj3dptr->realbz.f));
	if (tempitemptr->Status.size > ITEMSIZE)
		objType = MOBILE_OBJECT;
	else
		objType = STATIC_OBJECT;
		
//DeadCode RJS 23Oct00 	Obj3DPtr	obj3dptr = (Obj3DPtr)StuffIntoVisibleList(tempitemptr,range,pos,objType);
	StuffIntoVisibleList(tempitemptr,range,pos,objType);				//RJS 23Oct00
			
//DeadCode RJS 26May00 	obj3dptr->objtype = (ObjectType)MOBILE_OBJECT;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetVisibleMapObjects
//Author		Robert Slater
//Date			Thu 27 Apr 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::GetVisibleMapObjects(bool	isZoomed)
{
	btree::ObjectRec *objectRec;
	ObjectType	objtype;

	objectRec=&bt->objectRec;

	objectRec->numItems=0;

	ShapeNum	theShape;
	MobileItemPtr tempitemptr;											//JIM 31Jul00
	ShapeDesc *sdp;

//DeadCode RJS 25Aug00 	if (mobileitem::GetSAGList())
//DeadCode RJS 25Aug00 		tempitemptr = mobileitem::GetSAGList();
//DeadCode RJS 25Aug00 	else
//DeadCode RJS 25Aug00 		tempitemptr = mobileitem::GetACList();

	float	rangecheck=METRES20KM*METRES20KM;
	if (!isZoomed && Save_Data.gamedifficulty[GD_VISIBLEMIGSCHEAT])
		rangecheck=MILES1000*MILES1000;

// Normal ACs
	tempitemptr = mobileitem::GetACList();								//RJS 25Aug00
	while (tempitemptr)
	{
		if (!tempitemptr->Status.deadtime)						//RJS 14Jul00
		{
//DeadCode CSB 27Jul00 			if (!isZoomed || current_world->SameSector(tempitemptr,*View_Point))
				if (Math_Lib.DistanceSquared(View_Point->World.X-tempitemptr->World.X,View_Point->World.Z-tempitemptr->World.Z)<rangecheck)
				{
					sdp=SHAPESTUFF.GetShapePtr(tempitemptr->shape);
				
					if (AirStrucPtr(tempitemptr)->nationality == NAT_RAF)
					{
						theShape = MAPRAF;
					}
					else
					{
						theShape = MAPLW;
					}
					AddMapToObjectRec(tempitemptr,theShape,MOBILE_OBJECT);
				}
		}
		tempitemptr=tempitemptr->nextmobile;							//JIM 31Jul00
	}

// SaggyWaggys
	tempitemptr = mobileitem::GetSAGList();								//RJS 25Aug00
	while (tempitemptr)
	{
		if (	!tempitemptr->Status.deadtime
			&&	(Math_Lib.DistanceSquared(View_Point->World.X-tempitemptr->World.X,View_Point->World.Z-tempitemptr->World.Z)<rangecheck)	)
		{
			sdp=SHAPESTUFF.GetShapePtr(tempitemptr->shape);
				
			if (AirStrucPtr(tempitemptr)->nationality == NAT_RAF)
				theShape = SMPRAF;
			else
				theShape = SMPLW;

			AddMapToObjectRec(tempitemptr,theShape,MOBILE_OBJECT);
		}
		tempitemptr=tempitemptr->nextmobile;							//JIM 31Jul00
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		AddMapToObjectRec
//Author		Robert Slater
//Date			Thu 27 Apr 2000
//
//Description	Fake 2D (90 degree FoV)
//
//				Map Screen Artwork is at 320 z
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::AddMapToObjectRec(ItemPtr	tempitemptr, ShapeNum theShape, SLong objflag)
{
	MobileItemPtr	mobitem = MobileItemPtr(tempitemptr);
	Float	dy = Float(viewer_y) - (Float(tempitemptr->World.Y) + (Float(mobitem->vel_y)*fView_dt_frac));

//dy will eventually become screenz because we are always looking straight down...	
	if (dy > 0.0)
	{
		Float	dx = Float(tempitemptr->World.X) + (Float(mobitem->vel_x + wind_x)*fView_dt_frac) - Float(viewer_x);
		Float	dz = Float(tempitemptr->World.Z) + (Float(mobitem->vel_z + wind_z)*fView_dt_frac) - Float(viewer_z);
		Float	screenx,screeny;
		Float	recipz;

		btree::ObjectRec *objectRec = &bt->objectRec;

		recipz = 1./(dy+321);

		// +Z is north (screen Y)
		// +X is east  (screen X)

		screenx = dx*recipz;
		screeny = dz*recipz;

		if (	(screenx <= 1.)
			&&	(screenx >= -1.)
			&&	(screeny <= 1.)
			&&	(screeny >= -1.)	)
		{
			ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
			SLong			size = sdptr->Size << 4;

			objectRec->pos[objectRec->numItems].x = screenx*320.;
			objectRec->pos[objectRec->numItems].y = -321;
			objectRec->pos[objectRec->numItems].z = screeny*240.;
			objectRec->rad[objectRec->numItems]   = size;
			objectRec->range[objectRec->numItems] = 321;
			objectRec->itemFlag[objectRec->numItems] = 0;

// Obj3D...
			Obj3D*	smpoptr = &objectRec->obj3d[objectRec->numItems];

			smpoptr->Body.X.f = objectRec->pos[objectRec->numItems].x;
			smpoptr->Body.Y.f = objectRec->pos[objectRec->numItems].y;
			smpoptr->Body.Z.f = objectRec->pos[objectRec->numItems].z;
			smpoptr->ItemPtr = tempitemptr;
			smpoptr->Shape = theShape;
			smpoptr->AngH=mobitem->hdg;
			smpoptr->AngC=ANGLES_0Deg;
			smpoptr->AngR=ANGLES_0Deg;
 			smpoptr->copySize = tempitemptr->Status.size;				//RJS 26May00
			smpoptr->AnimPtr=tempitemptr->Anim;
			smpoptr->objtype = ObjectType(objflag);
			smpoptr->realbz.f = 321;
 
			objectRec->somethingvisible = true;
	 
			if (objectRec->numItems < btree::ObjectRec::MAX_OBJECTS-1)
				objectRec->numItems++;
#ifdef	_BTREEFULL_
			else
				INT3;
#endif
		}
	}
}

void	ThreeDee::AddObject(const ShapeNum&	theShape, const D3DVECTOR& pos, const ANGLES& hdg, const ANGLES& pitch, const ANGLES& roll)
{
	btree::ObjectRec *objectRec = &bt->objectRec;

	objectRec->pos[objectRec->numItems] = pos;

	ULong	clipcode;
	g_lpLib3d->VisibleCheck(&objectRec->pos[objectRec->numItems],1,&clipcode);
	if (clipcode == 0)
	{
		ShapeDescPtr	sdptr = SHAPESTUFF.GetShapePtr(theShape);
		SLong			size = sdptr->Size << 4;
		D3DVALUE		range = fastMath.FastSqrt(pos.x*pos.x + pos.y*pos.y + pos.z*pos.z);
		
		objectRec->itemFlag[objectRec->numItems] = 0;
		objectRec->rad[objectRec->numItems]   = size;
		objectRec->range[objectRec->numItems] = fastMath.DoubleToULong(Float(range));

// Obj3D...
		Obj3D*	smpoptr = &objectRec->obj3d[objectRec->numItems];

		smpoptr->Body.X.f = objectRec->pos[objectRec->numItems].x;
		smpoptr->Body.Y.f = objectRec->pos[objectRec->numItems].y;
		smpoptr->Body.Z.f = objectRec->pos[objectRec->numItems].z;
		smpoptr->ItemPtr = NULL;
		smpoptr->copySize = 0;					//cludge
		smpoptr->Shape = theShape;
		smpoptr->AngH=hdg;
		smpoptr->AngC=pitch;
		smpoptr->AngR=roll;
		smpoptr->AnimPtr=DummyAnimP;
		if (hdg || pitch || roll)
			smpoptr->objtype = MOBILE_OBJECT;
		else
			smpoptr->objtype = STATIC_OBJECT;

		smpoptr->realbz.f = range;

		if (objectRec->numItems < btree::ObjectRec::MAX_OBJECTS-1)
			objectRec->numItems++;
#ifdef	_BTREEFULL_
		else
			INT3;
#endif
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		RenderMirror
//Author		Robert Slater
//Date			Tue 20 Jun 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void	ThreeDee::RenderMirror()
{
#ifdef _NO_MIRROR
	return;
#endif

//DeadCode RJS 30Aug00 	static bool hasBeenMirror = false;
//DeadCode RJS 12Jul00 const	Angles	mirrorFoV = ANGLES_45Deg;

	if ( !Save_Data.cockpit3Ddetail[COCK3D_SKYIMAGES] || !mirrorSeen )
	{
		if ( hasBeenMirror )
		{ // just clear the mirror texture then..
			g_lpLib3d->SetMirrorTexture( HMATERIAL( Image_Map.GetImageMapPtr(ImageMapNumber(mirrorMaterial)) ) );//RJS 12Jul00
			g_lpLib3d->BeginScene(RENDERTARGET_MIRROR);
			g_lpLib3d->Wipe( fogCol );
			g_lpLib3d->EndScene();
//DeadCode JON 17Sep00 			g_lpLib3d->UploadMirror();
			g_lpLib3d->UploadTexture();

			hasBeenMirror = false;										//RJS 23Aug00
		}

		includeClippedObjects = false;
		return;
	}

	mirrorSeen = false;
	hasBeenMirror = true;
	includeClippedObjects = true;										//RJS 23Aug00

//DeadCode JON 1Nov00 // Clever stuff...
//DeadCode JON 1Nov00 	R3DMATRIX 	mat;
//DeadCode JON 1Nov00 	D3DVECTOR 	view,upvec,rightvec;
//DeadCode JON 1Nov00 	D3DVALUE 	mag;
//DeadCode JON 1Nov00 
//DeadCode JON 1Nov00 //set new view matrix
//DeadCode JON 1Nov00 //create matrix using view orientation vector v (dx,dy,dz)
//DeadCode JON 1Nov00 
//DeadCode JON 1Nov00 	view.dvX=mirrorOri.X;
//DeadCode JON 1Nov00 	view.dvY=mirrorOri.Y;
//DeadCode JON 1Nov00 	view.dvZ=mirrorOri.Z;
//DeadCode JON 1Nov00 	
//DeadCode JON 1Nov00 //normalise the view vector
//DeadCode JON 1Nov00 	
//DeadCode JON 1Nov00 	mag=view.dvX*view.dvX+view.dvY*view.dvY+view.dvZ*view.dvZ;
//DeadCode JON 1Nov00 	mag=fastMath.FastInvSqrt(mag);
//DeadCode JON 1Nov00 
//DeadCode JON 1Nov00 	view.dvX*=mag;
//DeadCode JON 1Nov00 	view.dvY*=mag;
//DeadCode JON 1Nov00 	view.dvZ*=mag;
//DeadCode JON 1Nov00 	
//DeadCode JON 1Nov00 //dot product of up vector (0,1,0) with view vector
//DeadCode JON 1Nov00 
//DeadCode JON 1Nov00 	upvec.dvX=0-view.dvY*view.dvX;
//DeadCode JON 1Nov00 	upvec.dvY=1-view.dvY*view.dvY;
//DeadCode JON 1Nov00 	upvec.dvZ=0-view.dvY*view.dvZ;
//DeadCode JON 1Nov00 
//DeadCode JON 1Nov00 	mag=upvec.dvX*upvec.dvX+upvec.dvY*upvec.dvY+upvec.dvZ*upvec.dvZ;
//DeadCode JON 1Nov00 	mag=fastMath.FastInvSqrt(mag);
//DeadCode JON 1Nov00 
//DeadCode JON 1Nov00 	upvec.dvX*=mag;
//DeadCode JON 1Nov00 	upvec.dvY*=mag;
//DeadCode JON 1Nov00 	upvec.dvZ*=mag;
//DeadCode JON 1Nov00 
//DeadCode JON 1Nov00 	rightvec.dvX=upvec.dvY*view.dvZ-upvec.dvZ*view.dvY;
//DeadCode JON 1Nov00 	rightvec.dvY=upvec.dvX*view.dvZ-upvec.dvZ*view.dvX;
//DeadCode JON 1Nov00 	rightvec.dvZ=upvec.dvX*view.dvY-upvec.dvY*view.dvX;
//DeadCode JON 1Nov00 
//DeadCode JON 1Nov00 	mat._11=rightvec.dvX;	mat._12=upvec.dvX;	mat._13=view.dvX;
//DeadCode JON 1Nov00 	mat._21=rightvec.dvY;	mat._22=upvec.dvY;	mat._23=view.dvY;
//DeadCode JON 1Nov00 	mat._31=rightvec.dvZ;	mat._32=upvec.dvZ;	mat._33=view.dvZ;
//DeadCode JON 1Nov00 	mat._14=mat._24=mat._34=mat._41=mat._42=mat._43=0;
//DeadCode JON 1Nov00 	mat._44=1;

	g_lpLib3d->SetMirrorTexture( HMATERIAL( Image_Map.GetImageMapPtr(ImageMapNumber(mirrorMaterial)) ) );
//set up the mirror matrices
	g_lpLib3d->BeginScene(RENDERTARGET_MIRROR);
	g_lpLib3d->LoadIdentity( MATRIX_OBJECT );
	
 	g_lpLib3d->LoadIdentity(MATRIX_VIEWER);

	// this does stuff from the current view point...
//DeadCode JON 1Nov00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)(int)View_Point->hdg);
//DeadCode JON 1Nov00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)-(int)View_Point->pitch);
//DeadCode JON 1Nov00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)-(int)View_Point->roll);



//TempCode JON 1Nov00 	g_lpLib3d->SetMatrix(MATRIX_VIEWER,mat);
//TempCode JON 1Nov00 
	//add in the aircrafts orientation - so we're pointing backwards down it. 
	//- note pitch,roll are all inverted as they are delta's to the camera...
	//- Then we add 180deg to the heading to reverse that
	//- and the the pitch needs to be made to point down not up
	//- finally, to make the image mirror( as the imap coords are swapped left/right in the shape)
	//- we need to invert the roll
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)((-(int)Persons2::PlayerSeenAC->hdg)+(int)ANGLES_180Deg));
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)(-(int)Persons2::PlayerSeenAC->pitch));
	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)(-(int)Persons2::PlayerSeenAC->roll));

	// these are correct to give a 'camera view - but not a reflected one' with imagemap coords messed wiv.
//TempCode JON 2Nov00  	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_HEADING,(Angles)((-(int)Persons2::PlayerSeenAC->hdg)+(int)ANGLES_180Deg));
//TempCode JON 2Nov00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_PITCH,(Angles)(-(int)Persons2::PlayerSeenAC->pitch/*+(int)ANGLES_180Deg*/));
//TempCode JON 2Nov00 	g_lpLib3d->Rotate(MATRIX_VIEWER,AXIS_ROLL,(Angles)(int)Persons2::PlayerSeenAC->roll);

	g_lpLib3d->SetProjectionMatrix( mirrorFoV,5.f/2.f,NON_COCKPIT_NEARZ, D3DVALUE(RANGE_FAR_MIRROR) );

	R3DMATRIX	vmat;
	g_lpLib3d->GetMatrix(MATRIX_VIEWER,vmat);
	eye_x = vmat._13;
	eye_y = vmat._23;
	eye_z = vmat._33;

//	g_lpLib3d->SetFogColour(fogCol);

//draw the landscape
//	g_lpLib3d->EnableFogging( false );
	Land_Scape.RenderMirrorLandscape();

//draw the shapes
	GetMirrorObjects();
	DrawVisibleObjects();

//render the mirror scene
	g_lpLib3d->EndScene();
	
//DeadCode JON 17Sep00 	g_lpLib3d->UploadMirror();
	g_lpLib3d->UploadTexture();
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		GetMirrorObjects
//Author		Robert Slater
//Date			Tue 20 Jun 2000
//
//Description	Must be called AFTER the original objects have been rendered.
//				... re-uses the object list
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::GetMirrorObjects()
{
	btree::ObjectRec *objectRec;

	objectRec=&bt->objectRec;

#define _DO_ALL_MIRROR_ITEMS
#ifndef _DO_ALL_MIRROR_ITEMS

	int		oldCnt = objectRec->numItems;

	objectRec->numItems = 0;

// Scan old list...
	for (int i=0; i < oldCnt; i++)
	{
		if (	(objectRec->obj3d[i].realbz.f < MIRROR_RANGE)
			&&	(objectRec->itemFlag[i] != 0)						)	// was not seen normally
		{
			if (objectRec->numItems < i)
			{
				objectRec->pos[objectRec->numItems] = objectRec->pos[i];
				objectRec->rad[objectRec->numItems] = objectRec->rad[i];
				objectRec->itemFlag[objectRec->numItems] = 0;
				objectRec->obj3d[objectRec->numItems] = objectRec->obj3d[i];
				objectRec->numItems++;
			}
		}
	}
#endif

// Clip elements...
	somethingvisible = false;											//RJS 23Aug00
	ItemPtr	tempitemptr;

	if (objectRec->numItems > 0)
	{
		g_lpLib3d->PushMatrix(MATRIX_OBJECT);
		g_lpLib3d->LoadIdentity(MATRIX_OBJECT);

		g_lpLib3d->VisibleCheck(objectRec->pos,objectRec->rad,objectRec->numItems,objectRec->itemFlag);

		for (int i=int(objectRec->numItems)-1;i>=0;i--)
		{
			tempitemptr=objectRec->obj3d[i].ItemPtr;
			if (0L==objectRec->itemFlag[i])
			{
// Push the range out to draw simple shapes...
//DeadCode JON 1Nov00 				objectRec->obj3d[i].realbz.f += 4000;

				somethingvisible = true;
				if (tempitemptr)
				{
					SetObjectAngles(&objectRec->obj3d[i]);

					tempitemptr->Status.Drawn = TRUE;
				}
			}
		}
		
		g_lpLib3d->PopMatrix(MATRIX_OBJECT);
	}

	objectRec->somethingvisible = somethingvisible;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ConeCheck
//Author		Robert Slater
//Date			Wed 22 Aug 2000
//
//Description	Checks to see if near objects are infront of the camera
//
//				... 60 degree half angle viewcone
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline	bool	ThreeDee::ConeCheck(const D3DVECTOR& pos, const SLong& range, const SLong& size)
{
	if (	(range < (size<<1))											//RJS 23Aug00
		||	includeClippedObjects	)									//RJS 23Aug00
		return true;

	float	dotProduct = pos.z*eye_z + pos.x*eye_x + pos.y*eye_y;
	if (dotProduct > float(range>>1))
		return true;

	return false;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		SetFrameTime
//Author		Robert Slater
//Date			Tue 19 Sep 2000
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
inline	void	ThreeDee::SetFrameTime()
{
	ULong time_now = timeGetTime();										
																		
	draw_time = time_now - last_time;									
			 
	View_Point->SetDrawFrameTime(draw_time);

//TEMPCODE JIM 06/06/00 #ifndef NDEBUG
//TEMPCODE JIM 06/06/00 	static int ftl=0;
//TEMPCODE JIM 06/06/00 	PrintVar(60, ftl," ",0UL);
//TEMPCODE JIM 06/06/00 	PrintVar(63, ftl++, " %3i ms", draw_time);
//TEMPCODE JIM 06/06/00 	PrintVar(60, ftl,">",0UL);
//TEMPCODE JIM 06/06/00 	if (ftl>20)
//TEMPCODE JIM 06/06/00 		ftl=0;
//TEMPCODE JIM 06/06/00 #endif
																		
//DeadCode RJS 20Sep00 	if(draw_time > 256)	draw_time = 256;					//256 ms	
	last_time = time_now;												
	if(!IsPaused())														
	{																	
		const SLong frametime_ms = Timer_Code.FRAMETIME * 10;//40 ms	
		const SLong max_ms       = frametime_ms * 25;		//400 ms	
																		
		SLong delta_ms = time_now - SLong(View_Point->move_time_ms);	
 		if((delta_ms < 0) || (delta_ms > max_ms))						
 		{
 			View_Point->move_time_ms += delta_ms;						
  			view_dt = 0;												
 		}																
  		else															
		{
 			view_dt = delta_ms;											
		}

		if(View_Point->trackeditem)
			MissManCampSky().GetWind(View_Point->trackeditem->World.Y, wind_x, wind_y, wind_z);
	}																	

//DEADCODE CSB 08/03/00 PrintVar(65, 21, "tn %.0f ", FP(time_now));								
//DEADCODE CSB 08/03/00 PrintVar(65, 23, "dt %.0f  ", FP(view_dt));								
//DEADCODE CSB 08/03/00 static ULong longest_dt = 0;											
//DEADCODE CSB 08/03/00 if(view_dt > longest_dt)												
//DEADCODE CSB 08/03/00 {																		
//DEADCODE CSB 08/03/00 longest_dt = view_dt;													
//DEADCODE CSB 08/03/00 PrintVar(60, 24, "%.0f", FP(longest_dt));								
//DEADCODE CSB 08/03/00 }

	if (_DPlay.Implemented || View_Point->Accel())									//RJS 26Sep00
	{
		view_dt = 0;
		wind_x = wind_y = wind_z = 0;
	}

	fView_dt_frac = Float(view_dt) / 1e5;
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		ExpandPhotoGroup
//Author		Robert Slater
//Date			Wed 08 Nov 2000
//
//Description	Alternative ExpandGroup for PHOTO use only...
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
void ThreeDee::ExpandPhotoGroup(void *pvoid,ItemPtr tempitemptr, SLong grouprange)
{
	UByte*			groupjump;						  
	SWord			instruction;					  
	DOGROUP_PTR 	tempgrp;						  
	DRAWBETWEEN_PTR	dobetptr;						  
	SWord			heading;						  
	SByte			ydelta;							  
	UByteP			adptrold;
	COORDS3D		tmpworld;
//DEADCODE RJS 4/7/00 	Coords3D		relworld;
	SLong			heightfix;
	MinAnimData*	mad;							  
	SWord			realPitch,realRoll,realHdg;		  
	SLong			dx,dz;
	SLong			elmtrange;
	Float			relworld_x;
	Float			relworld_y;
	Float			relworld_z;
	Float			fDist;
 	SLong			velCorrectX;
 	SLong			velCorrectY;
 	SLong			velCorrectZ;

	if (tempitemptr->Anim==NULL)					  
		SHAPE.SetAnimData(tempitemptr,0);			  

	animptr	adptr=tempitemptr->Anim;				  

	ShapeNum oldshape, oldShape;

	ShapeDescPtr	header_ptr =
		SHAPESTUFF.GetShapePtr(oldshape = tempitemptr->shape);

	UByte *instr_ptr = (UByte *)header_ptr + header_ptr->liveshpref;

	Bool	notinrange;											
	SLong	shpsize;											
	Bool	isFiddled;
//DeadCode RJS 26May00 	bool	noHeightFix = false;								
	SWord	rotateitem;
	R3DVALUE	rng;
	UByte		copySize = tempitemptr->Status.size;					//RJS 26May00

	groupjump = NULL;											

	if (copySize >= MOBILESIZE)											//RJS 26May00
	{
		mobileitem*	hdgitem = (mobileitem*) tempitemptr;

		realHdg = hdgitem->hdg;
		realPitch = hdgitem->pitch;
		realRoll = hdgitem->roll;

//DeadCode RJS 25Sep00 		velCorrectX = float(hdgitem->vel_x + wind_x)*float(fView_dt_frac);		//RJS 7Jun00
//DeadCode RJS 25Sep00 		velCorrectY = float(hdgitem->vel_y + wind_y)*float(fView_dt_frac);		//RJS 7Jun00
//DeadCode RJS 25Sep00 		velCorrectZ = float(hdgitem->vel_z + wind_z)*float(fView_dt_frac);		//RJS 7Jun00
		fastMath.FloatToInt(&velCorrectX,velCorrect_x);
		fastMath.FloatToInt(&velCorrectY,velCorrect_y);
		fastMath.FloatToInt(&velCorrectZ,velCorrect_z);

//DeadCode RJS 26May00 		noHeightFix = true;
	}
	else
	{
		realPitch = 0;
		realRoll = 0;
		realHdg = 0;

		velCorrectX = velCorrectY = velCorrectZ = 0;					//RJS 7Jun00
	}

#ifdef	_HEIGHTCHECK_
::AfxTrace("%x  (%d)  %d\n",int(tempitemptr->SGT),int(tempitemptr->shape),tempitemptr->World.Y);
#endif

	btree::ObjectRec *objectRec=(btree::ObjectRec*)pvoid;

	forever
	{
		instruction = *instr_ptr;
		instr_ptr++;

		if (instruction!=dogroupno)
			break;

		tempgrp = (DOGROUP_PTR)instr_ptr;

		ShapeNum newshape = (ShapeNum )tempgrp->shapenum;

		heading = tempgrp->angle;

		tempitemptr->shape = newshape;

// Add vel correction here...

		tmpworld.X = velCorrectX + tempitemptr->World.X + tempgrp->xoffset;	//RJS 25Sep00
		tmpworld.Y = velCorrectY + tempitemptr->World.Y + tempgrp->yoffset;	//RJS 25Sep00
		tmpworld.Z = velCorrectZ + tempitemptr->World.Z + tempgrp->zoffset;	//RJS 25Sep00

		SHAPE.SetGrpTokenVisibility((UByteP)tempgrp,tempitemptr->Anim,adptr);
		mad = (MinAnimData*) adptr;

		if (copySize < MOBILESIZE)										//RJS 26May00
		{
			//Eliminate cocked-up deltas
			ydelta = SHAPE.GetElementYDelta(newshape,adptr,tmpworld,tempitemptr->World.Y);//RJS 09Jun99
			rotateitem = heading;
		}
		else
		{
			heading += realHdg;
			ydelta = 0;
			adptr += SHAPE.GetElementAnimOffset(newshape);
			rotateitem = 1;
		}

		if (	(grouprange >= tempgrp->range_min)
			&&	(grouprange < tempgrp->range_max)	)
		{
			// Delta calc moved to 3dcom.cpp
			heightfix = ydelta<<4;

#ifdef	_HEIGHTCHECK_
::AfxTrace("      %d\n",heightfix);
#endif
			if (!mad->IsInvisible)
			{
				tmpworld.Y += heightfix;

				relworld_x = tmpworld.X - SLong(viewer_x);
				relworld_y = tmpworld.Y - SLong(viewer_y);
				relworld_z = tmpworld.Z - SLong(viewer_z);

				ShapeDescPtr sdptr = SHAPESTUFF.GetShapePtr(newshape);

				fDist = relworld_x*relworld_x + relworld_y*relworld_y + relworld_z*relworld_z;
				rng = fastMath.FastSqrt(R3DVALUE(fDist));
				fastMath.FloatToInt(&elmtrange,rng);

				objectRec->pos[objectRec->numItems].x=relworld_x;
				objectRec->pos[objectRec->numItems].y=relworld_y;
				objectRec->pos[objectRec->numItems].z=relworld_z;
				objectRec->rad[objectRec->numItems]=sdptr->Size<<4;
				objectRec->range[objectRec->numItems]=elmtrange;

				if (ConeCheck(objectRec->pos[objectRec->numItems],elmtrange,sdptr->Size<<4))//RJS 23Aug00
				{
					Obj3D*	smpoptr = &objectRec->obj3d[objectRec->numItems];

					smpoptr->Body.X.f = objectRec->pos[objectRec->numItems].x;
					smpoptr->Body.Y.f = objectRec->pos[objectRec->numItems].y;
					smpoptr->Body.Z.f = objectRec->pos[objectRec->numItems].z;
					smpoptr->ItemPtr = tempitemptr;
					smpoptr->Shape = newshape;
					if (rotateitem)
					{
						smpoptr->AngH = (Angles) heading;
						smpoptr->AngC = (Angles) realPitch;
						smpoptr->AngR = (Angles) realRoll;
						smpoptr->objtype = MOBILE_OBJECT;
					}
					else
					{
						smpoptr->AngH=
							smpoptr->AngC=
							smpoptr->AngR=ANGLES_0Deg;
						smpoptr->objtype = STATIC_OBJECT;
					}
		
 					smpoptr->copySize=0;								//RJS 26May00
					smpoptr->AnimPtr=tempitemptr->Anim;
					smpoptr->AnimPtr=(UByteP)mad;
					smpoptr->realbz.f = Float(rng);

					tempitemptr->Status.Drawn = TRUE;
					
					if (objectRec->numItems < btree::ObjectRec::MAX_OBJECTS-1)
						objectRec->numItems++;
#ifdef _BTREEFULL_
	 				else
						INT3;
#endif

					smpoptr->ItemPtr = NULL;
				}
			}
		}
		instr_ptr += sizeof(DOGROUP);
	}
	tempitemptr->shape = oldshape;
}

inline WayPointPtr FindFirstWP(UniqueID uid,WayPointPtr wp)					//RJS 27Jun00
{
	WayPointPtr nwp=wp;
	//return straight away if no waypoint
	if (nwp==NULL)
		return nwp;
	//skip back until prev wp is NULL
	while (nwp->prev!=NULL) 
		nwp=nwp->prev;
	//skip forward 'til get a valid waypoint
	while(nwp!=wp && (uid<nwp->skipunder || uid>nwp->skipover))			//RJS 27Jun00
		nwp=nwp->next;
	return nwp;
}
//////////////////////////////////////////////////////////////////////
//
// Function:    renderAircraftRoute

// Date:		11/8/00
// Author:		JON
//
//Description:  draws on the aircraft route for the loverly mapscreen...
//
//////////////////////////////////////////////////////////////////////
void ThreeDee::renderAircraftRoute( void )
{

	const HMATERIAL lineMat(UByte(252));
	const HMATERIAL waypointMat(UByte(144));
	const float depth = -float(viewer_y);
	const AirStrucPtr itemPtr = Manual_Pilot.ControlledAC2;
	//skip to itemPtr's first waypoint...
	WayPointPtr lastwaypt=NULL,waypt=itemPtr->waypoint;

	if (waypt!=NULL)
	{

		UniqueID	itemUID = itemPtr->uniqueID.count;					//RJS 27Jun00
		if (	itemPtr->fly.expandedsag
			&& (itemPtr->fly.numinsag==0)	)
			itemUID = itemPtr->fly.expandedsag->uniqueID.count;			//RJS 27Jun00

		waypt=FindFirstWP(itemUID,waypt);	//while (waypt->prev) waypt=waypt->prev;	//RJS 27Jun00
		COORDS3D end_pos=*waypt->FindDesPos();


		DoPointStruc* startP = SHAPE.newco;
		DoPointStruc* endP = &SHAPE.newco[1];

		endP->setPosition(
			SLong(end_pos.X-viewer_x),
			depth,
			SLong(end_pos.Z-viewer_z)	);

		Land_Scape.DrawWayPointIcon( end_pos, viewer_x, viewer_y, viewer_z, 0 );
		renderWaypointTargets( waypt );

		lastwaypt=waypt;
		waypt = waypt->NextWP(itemPtr);									//RJS 27Jun00

		while (waypt!=lastwaypt)										//RJS 27Jun00
		{
			DoPointStruc* tmp = startP;
			startP = endP;
			endP = tmp;
			COORDS3D end_pos=*waypt->FindDesPos();
			endP->setPosition(
				SLong(end_pos.X-viewer_x),
				depth,
				SLong(end_pos.Z-viewer_z)	);

			Land_Scape.DrawWayPointIcon( end_pos, viewer_x, viewer_y, viewer_z,
				(waypt==OverLay.curr_waypoint)?2:0 
				);
			renderWaypointTargets( waypt );

			g_lpLib3d->DrawLine( lineMat, *startP, *endP );
			lastwaypt=waypt;
			waypt = waypt->NextWP(itemPtr);										//RJS 27Jun00
		}
	}
	{
		COORDS3D home_pos;
		COORDS3D start_pos;

		if (itemPtr->waypoint)
		{
			home_pos=*(itemPtr->waypoint->FindDesPos());
			renderWaypointTargets( itemPtr->waypoint );
		}
		else
			home_pos=itemPtr->ai.homebase->World;

		start_pos=itemPtr->World;
		//draw a line from home_pos to start_pos

		Land_Scape.DrawWayPointIcon( home_pos, viewer_x, viewer_y, viewer_z,
				(itemPtr->waypoint==OverLay.curr_waypoint)?3:1  
			);

		DoPointStruc* startP = SHAPE.newco;
		DoPointStruc* endP = &SHAPE.newco[1];

		startP->setPosition(
			SLong(start_pos.X-viewer_x),
			depth,
			SLong(start_pos.Z-viewer_z)	);

		endP->setPosition(
			SLong(home_pos.X-viewer_x),
			depth,
			SLong(home_pos.Z-viewer_z)	);

		g_lpLib3d->DrawLine( lineMat, *startP, *endP );

	}
}

void ThreeDee::renderWaypointTargets( const WayPointPtr waypt )			//JON 8Nov00
{
	if ( waypt->target )
	{ // the yaypoint has a target to draw..
		UniqueID targetUIDMatch;
		if ( waypt->target->SGT != UID_NULL )
			targetUIDMatch=waypt->target->SGT;
		else
			targetUIDMatch=waypt->target->uniqueID.count;

		for ( int i = 0; i<0x4000; i++ )
		{
			if ( current_world->pItem[i] != NULL &&
				 current_world->pItem[i]->Status.size >= ITEMSIZE && // it's visible
				 (
					 ((Item*)current_world->pItem[i])->SGT == targetUIDMatch ||
					 current_world->pItem[i]->uniqueID.count == targetUIDMatch
				 )
				)
			{
//TempCode JON 8Nov00 					Item* itemPtr = (Item*)(current_world->pItem[i]);
//TempCode JON 8Nov00 					ShapeDescPtr shapePtr=SHAPESTUFF.GetShapePtr(itemPtr->shape);
//TempCode JON 8Nov00 
//TempCode JON 8Nov00 					if (SHAPESTUFF.GetShapeScale(shapePtr)==SHP_GRP)
//TempCode JON 8Nov00 					{
//TempCode JON 8Nov00 						UByte* inst_ptr=(UByte*)shapePtr+shapePtr->liveshpref;
//TempCode JON 8Nov00 
//TempCode JON 8Nov00 						for (SWord inst=*inst_ptr++;inst==dogroupno;inst=*inst_ptr++)
//TempCode JON 8Nov00 						{
//TempCode JON 8Nov00 							DOGROUP_PTR gptr=(DOGROUP_PTR)inst_ptr;
//TempCode JON 8Nov00 
//TempCode JON 8Nov00 							COORDS3D tmp = itemPtr->World;
//TempCode JON 8Nov00 							tmp.X+=gptr->xoffset;
//TempCode JON 8Nov00 							tmp.Z+=gptr->zoffset;
//TempCode JON 8Nov00 
//TempCode JON 8Nov00 							Land_Scape.DrawWayPointIcon( tmp, viewer_x, viewer_y, viewer_z, 2 );
//TempCode JON 8Nov00 							inst_ptr+=sizeof(DOGROUP);
//TempCode JON 8Nov00 						}
//TempCode JON 8Nov00 					} else
//TempCode JON 8Nov00 					{
					Land_Scape.DrawWayPointIcon( current_world->pItem[i]->World, viewer_x, viewer_y, viewer_z, 4 );
//TempCode JON 8Nov00 					}
			}
		}
	}

}
